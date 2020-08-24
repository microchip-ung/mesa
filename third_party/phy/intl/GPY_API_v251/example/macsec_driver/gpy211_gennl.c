/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#define DEBUG

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/platform_device.h>
#include <uapi/linux/if_macsec.h>
//#include <linux/rtnetlink.h>
#include <net/genetlink.h>
//#include <net/gpy211/gpy211_ops.h>

#include "gpy211_common.h"
#include "gpy211_driver.h"
#include "gpy211_gennl.h"

extern struct gpy2xx_priv gpy212_data;

static const struct nla_policy gpy211_macsec_genl_rxsc_policy[NUM_MACSEC_RXSC_ATTR] = {
	[MACSEC_RXSC_ATTR_SCI] = { .type = NLA_U64 },
	[MACSEC_RXSC_ATTR_ACTIVE] = { .type = NLA_U8 },
};

static const struct nla_policy gpy211_macsec_genl_sa_policy[NUM_MACSEC_SA_ATTR] = {
	[MACSEC_SA_ATTR_AN] = { .type = NLA_U8 },
	[MACSEC_SA_ATTR_ACTIVE] = { .type = NLA_U8 },
	[MACSEC_SA_ATTR_PN] = { .type = NLA_U32 },
	[MACSEC_SA_ATTR_KEYID] = {
		.type = NLA_BINARY,
		.len = MACSEC_KEYID_LEN,
	},
	[MACSEC_SA_ATTR_KEY] = {
		.type = NLA_BINARY,
		.len = MACSEC_MAX_KEY_LEN,
	},
};

static int gpy211_parse_sa_config(struct nlattr **attrs,
				  struct nlattr **tb_sa)
{
	if (!attrs[MACSEC_ATTR_SA_CONFIG])
		return -EINVAL;

	if (nla_parse_nested(tb_sa, MACSEC_SA_ATTR_MAX,
			     attrs[MACSEC_ATTR_SA_CONFIG],
			     gpy211_macsec_genl_sa_policy, NULL))
		return -EINVAL;

	return 0;
}

static int gpy211_parse_rxsc_config(struct nlattr **attrs,
				    struct nlattr **tb_rxsc)
{
	if (!attrs[MACSEC_ATTR_RXSC_CONFIG])
		return -EINVAL;

	if (nla_parse_nested(tb_rxsc, MACSEC_RXSC_ATTR_MAX,
			     attrs[MACSEC_ATTR_RXSC_CONFIG],
			     gpy211_macsec_genl_rxsc_policy, NULL))
		return -EINVAL;

	return 0;
}

static bool gpy211_validate_upd_sa(struct nlattr **attrs)
{
	if (!attrs[MACSEC_SA_ATTR_AN] ||
	    attrs[MACSEC_SA_ATTR_KEY] ||
	    attrs[MACSEC_SA_ATTR_KEYID])
		return false;

	if (nla_get_u8(attrs[MACSEC_SA_ATTR_AN]) >= MACSEC_MAX_AN)
		return false;

	if (attrs[MACSEC_SA_ATTR_PN] &&
	    nla_get_u32(attrs[MACSEC_SA_ATTR_PN]) == 0)
		return false;

	if (attrs[MACSEC_SA_ATTR_ACTIVE]) {
		if (nla_get_u8(attrs[MACSEC_SA_ATTR_ACTIVE]) > 1)
			return false;
	}

	return true;
}

static bool gpy211_validate_add_txsa(struct nlattr **attrs)
{
	if (!attrs[MACSEC_SA_ATTR_AN] ||
	    !attrs[MACSEC_SA_ATTR_PN] ||
	    !attrs[MACSEC_SA_ATTR_KEY] ||
	    !attrs[MACSEC_SA_ATTR_KEYID])
		return false;

	if (nla_get_u8(attrs[MACSEC_SA_ATTR_AN]) >= MACSEC_MAX_AN)
		return false;

	if (nla_get_u32(attrs[MACSEC_SA_ATTR_PN]) == 0)
		return false;

	if (attrs[MACSEC_SA_ATTR_ACTIVE]) {
		if (nla_get_u8(attrs[MACSEC_SA_ATTR_ACTIVE]) > 1)
			return false;
	}

	if (nla_len(attrs[MACSEC_SA_ATTR_KEYID]) != MACSEC_KEYID_LEN)
		return false;

	return true;
}

static bool gpy211_validate_add_rxsc(struct nlattr **attrs)
{
	if (!attrs[MACSEC_RXSC_ATTR_SCI])
		return false;

	if (attrs[MACSEC_RXSC_ATTR_ACTIVE]) {
		if (nla_get_u8(attrs[MACSEC_RXSC_ATTR_ACTIVE]) > 1)
			return false;
	}

	return true;
}

static bool gpy211_validate_add_rxsa(struct nlattr **attrs)
{

	if (!attrs[MACSEC_SA_ATTR_AN] ||
	    !attrs[MACSEC_SA_ATTR_KEY] ||
	    !attrs[MACSEC_SA_ATTR_KEYID])
		return false;

	if (nla_get_u8(attrs[MACSEC_SA_ATTR_AN]) >= MACSEC_MAX_AN)
		return false;

	if (attrs[MACSEC_SA_ATTR_PN] &&
	    nla_get_u32(attrs[MACSEC_SA_ATTR_PN]) == 0)
		return false;

	if (attrs[MACSEC_SA_ATTR_ACTIVE]) {
		if (nla_get_u8(attrs[MACSEC_SA_ATTR_ACTIVE]) > 1)
			return false;
	}

	if (nla_len(attrs[MACSEC_SA_ATTR_KEYID]) != MACSEC_KEYID_LEN)
		return false;

	return true;
}

static struct gpy211_macsec_rx_sc *gpy211_find_rx_sc_rtnl(struct gpy211_macsec_secy *secy, sci_t sci)
{
	struct gpy211_macsec_rx_sc *rx_sc;

	for (rx_sc = secy->rx_sc; rx_sc; rx_sc = secy->rx_sc->next) {
		if (rx_sc->sci == sci)
			return rx_sc;
	}

	return NULL;
}

static struct net_device *gpy211_get_dev_from_nl(struct net *net,
		struct nlattr **attrs)
{
	int ifindex = nla_get_u32(attrs[MACSEC_ATTR_IFINDEX]);
	struct net_device *dev;

	dev = __dev_get_by_index(net, ifindex);

	if (!dev)
		return ERR_PTR(-ENODEV);

	if (!netif_is_macsec(dev))
		return ERR_PTR(-ENODEV);

	return dev;
}

void gpy211_get_smac_from_sci(sci_t sci, u8 *mac_addr)
{
	u32 val_0, val_1;
	val_0 = ((sci & 0xFFFFFFFF00000000) >> 32);
	val_1 = (sci & 0x00000000FFFFFFFF);

	mac_addr[0] = ((val_0 >> 24) & 0xff);
	mac_addr[1] = ((val_0 >> 16) & 0xff);
	mac_addr[2] = ((val_0 >> 8) & 0xff);
	mac_addr[3] = (val_0 & 0xff);
	mac_addr[4] = ((val_1 >> 24) & 0xff);
	mac_addr[5] = ((val_1 >> 16) & 0xff);
}

static void gpy211_parse_dev_secy_data(struct nlattr *data[],
				       struct gpy211_macsec_secy *secy)
{
	struct gpy211_macsec_tx_sc *tx_sc = &secy->tx_sc;

	if (!data)
		return;

	if (data[IFLA_MACSEC_ENCODING_SA]) {
		tx_sc->encoding_sa = nla_get_u8(data[IFLA_MACSEC_ENCODING_SA]);
		secy->operational = 1;
	}

	if (data[IFLA_MACSEC_WINDOW])
		secy->replay_window = nla_get_u32(data[IFLA_MACSEC_WINDOW]);

	if (data[IFLA_MACSEC_PROTECT])
		secy->protect_frames = !!nla_get_u8(data[IFLA_MACSEC_PROTECT]);

	if (data[IFLA_MACSEC_REPLAY_PROTECT])
		secy->replay_protect = !!nla_get_u8(data[IFLA_MACSEC_REPLAY_PROTECT]);

	if (data[IFLA_MACSEC_VALIDATION])
		secy->validate_frames = nla_get_u8(data[IFLA_MACSEC_VALIDATION]);

	if (data[IFLA_MACSEC_ENCRYPT])
		tx_sc->encrypt = !!nla_get_u8(data[IFLA_MACSEC_ENCRYPT]);

	if (data[IFLA_MACSEC_INC_SCI])
		tx_sc->send_sci = !!nla_get_u8(data[IFLA_MACSEC_INC_SCI]);

	if (data[IFLA_MACSEC_ES])
		tx_sc->end_station = !!nla_get_u8(data[IFLA_MACSEC_ES]);

	if (data[IFLA_MACSEC_SCB])
		tx_sc->scb = !!nla_get_u8(data[IFLA_MACSEC_SCB]);
}

static void gpy211_copy_dev_secy_data(struct gpy211_macsec_secy *dst_secy,
			       struct gpy211_macsec_secy *src_secy)
{
	dst_secy->operational = src_secy->operational;
	dst_secy->replay_window = src_secy->replay_window;
	dst_secy->protect_frames = src_secy->protect_frames;
	dst_secy->replay_protect = src_secy->replay_protect;
	dst_secy->validate_frames = src_secy->validate_frames;
	dst_secy->key_len = src_secy->key_len;
	dst_secy->icv_len = src_secy->icv_len;
	dst_secy->sci = src_secy->sci;
	dst_secy->tx_sc.encoding_sa = src_secy->tx_sc.encoding_sa;
	dst_secy->tx_sc.encrypt = src_secy->tx_sc.encrypt;
	dst_secy->tx_sc.send_sci = src_secy->tx_sc.send_sci;
	dst_secy->tx_sc.end_station = src_secy->tx_sc.end_station;
	dst_secy->tx_sc.scb = src_secy->tx_sc.scb;
}

static struct gpy211_macsec_rx_sc *gpy211_create_rx_sc(sci_t sci)
{
	struct gpy211_macsec_rx_sc *rx_sc;
	struct gpy211_macsec_secy *secy;
	struct gpy2xx_priv_data *pdata;
	pr_debug("Entering %s %d\n", __func__, __LINE__);

	rx_sc = kzalloc(sizeof(*rx_sc), in_atomic() ? GFP_ATOMIC : GFP_KERNEL);

	if (!rx_sc)
		return ERR_PTR(-ENOMEM);

	rx_sc->sci = sci;
	rx_sc->active = true;
	atomic_set(&rx_sc->refcnt, 1);

	/* Update to private data */
	pdata = (struct gpy2xx_priv_data *)platform_get_drvdata(gpy212_data.pdev[0]);

	secy = &pdata->secy;
	rx_sc->next = secy->rx_sc;
	secy->rx_sc = rx_sc;

	if (rx_sc->active)
		secy->n_rx_sc++;

	pr_debug("Exiting %s %d\n", __func__, __LINE__);
	return rx_sc;
}

static struct gpy211_macsec_rx_sc *gpy211_del_rx_sc(struct gpy211_macsec_secy *secy, sci_t sci)
{
	struct gpy211_macsec_rx_sc *rx_sc, **rx_scp;

	for (rx_scp = &secy->rx_sc, rx_sc = *rx_scp;
	     rx_sc;
	     rx_scp = &rx_sc->next, rx_sc = *rx_scp) {
		if (rx_sc->sci == sci) {
			if (rx_sc->active)
				secy->n_rx_sc--;

			*rx_scp = rx_sc->next;
			return rx_sc;
		}
	}

	return NULL;
}

static void gpy211_free_rx_sc(struct gpy211_macsec_rx_sc *rx_sc)
{
	kfree(rx_sc);
}

#ifdef SUPPORT_ALL_NLM_CMDS
int gpy211_upd_rxsa(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **attrs = info->attrs;
	struct gpy211_macsec_secy *secy;
	struct gpy211_macsec_rx_sc *rx_sc;
	struct gpy211_macsec_rx_sa *rx_sa;
	u8 assoc_num;
	struct nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	struct nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	sci_t sci;
	struct gpy2xx_priv_data *pdata;

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (gpy211_parse_rxsc_config(attrs, tb_rxsc))
		return -EINVAL;

	if (gpy211_parse_sa_config(attrs, tb_sa))
		return -EINVAL;

	if (!gpy211_validate_upd_sa(tb_sa))
		return -EINVAL;

	assoc_num = nla_get_u8(tb_sa[MACSEC_SA_ATTR_AN]);

	if (assoc_num >= MACSEC_MAX_AN)
		return -EINVAL;

	pdata = (struct gpy2xx_priv_data *)platform_get_drvdata(gpy212_data.pdev[0]);
	secy = &pdata->secy;

	if (!tb_rxsc[MACSEC_RXSC_ATTR_SCI])
		return -EINVAL;

	sci = nla_get_u64(tb_rxsc[MACSEC_RXSC_ATTR_SCI]);

	rx_sc = gpy211_find_rx_sc_rtnl(secy, sci);

	if (!rx_sc)
		return -ENODEV;

	rx_sa = rx_sc->sa[assoc_num];

	if (!rx_sa)
		return -ENODEV;

	if (tb_sa[MACSEC_SA_ATTR_PN])
		rx_sa->next_pn = nla_get_u32(tb_sa[MACSEC_SA_ATTR_PN]);

	if (tb_sa[MACSEC_SA_ATTR_ACTIVE])
		rx_sa->active = nla_get_u8(tb_sa[MACSEC_SA_ATTR_ACTIVE]);

	/* TODO: Update the parsed params to SA */
	gpy211_update_transrec(&pdata->ops, assoc_num);

	return 0;
}

int gpy211_del_rxsa(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **attrs = info->attrs;
	struct gpy211_macsec_secy *secy;
	struct gpy211_macsec_rx_sc *rx_sc;
	struct gpy211_macsec_rx_sa *rx_sa;
	u8 assoc_num;
	struct nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	struct nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	sci_t sci;
	struct gpy2xx_priv_data *pdata);

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (gpy211_parse_sa_config(attrs, tb_sa))
		return -EINVAL;

	if (gpy211_parse_rxsc_config(attrs, tb_rxsc))
		return -EINVAL;

	if (!tb_sa[MACSEC_SA_ATTR_AN])
		return -EINVAL;

	assoc_num = nla_get_u8(tb_sa[MACSEC_SA_ATTR_AN]);

	if (assoc_num >= MACSEC_MAX_AN)
	return -EINVAL;

	pdata = (struct gpy2xx_priv_data *)platform_get_drvdata(gpy212_data.pdev[0]);
	secy = &pdata->secy;

	if (!tb_rxsc[MACSEC_RXSC_ATTR_SCI])
		return -EINVAL;

	sci = nla_get_u64(tb_rxsc[MACSEC_RXSC_ATTR_SCI]);

	rx_sc = gpy211_find_rx_sc_rtnl(secy, sci);

	if (!rx_sc)
	return -ENODEV;

	rx_sa = rx_sc->sa[assoc_num];

	if (!rx_sa)
		return -ENODEV;

	if (rx_sa->active)
		return -EBUSY;

	if (gpy211_remove_flowrec(&pdata->ops, assoc_num))
			return -EINVAL;

	if (gpy211_remove_transrec(&pdata->ops, assoc_num))
		return -EINVAL;

	kfree(rx_sc->sa[assoc_num]);

	rx_sc->sa[assoc_num] = NULL;
	rx_sa->active = false;

	return 0;
}

int gpy211_upd_txsa(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **attrs = info->attrs;
	struct gpy211_macsec_secy *secy;
	struct gpy211_macsec_tx_sc *tx_sc;
	struct gpy211_macsec_tx_sa *tx_sa;
	struct nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	u8 assoc_num;
	struct gpy2xx_priv_data *pdata;
	struct net_device *dev;
	struct gpy2xx_priv_data *macsec;

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	dev = gpy211_get_dev_from_nl(genl_info_net(info), attrs);

	if (IS_ERR(dev))
		return PTR_ERR(dev);

	macsec = netdev_priv(dev);

	pdata = (struct gpy2xx_priv_data *)platform_get_drvdata(gpy212_data.pdev[0]);

	gpy211_copy_dev_secy_data(&pdata->secy, &macsec->secy);

	if (gpy211_parse_sa_config(attrs, tb_sa))
		return -EINVAL;

	if (!gpy211_validate_upd_sa(tb_sa))
		return -EINVAL;

	assoc_num = nla_get_u8(tb_sa[MACSEC_SA_ATTR_AN]);

	if (assoc_num >= MACSEC_MAX_AN)
		return -EINVAL;

	tx_sa = pdata->secy.tx_sc.sa[assoc_num];

	if (!tx_sa)
		return -ENODEV;

	tx_sc = &pdata->secy.tx_sc;
	secy = &pdata->secy;

	if (tb_sa[MACSEC_SA_ATTR_PN])
		tx_sa->next_pn = nla_get_u32(tb_sa[MACSEC_SA_ATTR_PN]);

	if (tb_sa[MACSEC_SA_ATTR_ACTIVE])
		tx_sa->active = nla_get_u8(tb_sa[MACSEC_SA_ATTR_ACTIVE]);

	if (assoc_num == tx_sc->encoding_sa)
		secy->operational = tx_sa->active;

	/* TODO: Update the parsed params to SA */
	gpy211_update_transrec(&pdata->ops, assoc_num);

	return 0;
}

int gpy211_del_txsa(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **attrs = info->attrs;
	struct gpy211_macsec_tx_sa *tx_sa;
	u8 assoc_num;
	struct nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	struct gpy2xx_priv_data *pdata;
	pr_debug("Entering %s %d\n", __func__, __LINE__);

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (gpy211_parse_sa_config(attrs, tb_sa))
		return -EINVAL;

	assoc_num = nla_get_u8(tb_sa[MACSEC_SA_ATTR_AN]);

	if (assoc_num >= MACSEC_MAX_AN)
		return -EINVAL;

	pdata = (struct gpy2xx_priv_data *)platform_get_drvdata(gpy212_data.pdev[0]);
	tx_sa = pdata->secy.tx_sc.sa[assoc_num];

	if (!tx_sa)
		return -ENODEV;

	if (gpy211_remove_flowrec(&pdata->ops, assoc_num))
		return -EINVAL;

	if (gpy211_remove_transrec(&pdata->ops, assoc_num))
		return -EINVAL;

	kfree(tx_sa);

	pdata->secy.tx_sc.sa[assoc_num] = NULL;
	tx_sa->active = false;

	pr_debug("Exiting %s %d\n", __func__, __LINE__);
	return 0;
}
#endif

int gpy211_upd_rxsc(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **attrs = info->attrs;
	struct gpy211_macsec_secy *secy;
	struct gpy211_macsec_rx_sc *rx_sc;
	struct nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	sci_t sci;
	struct gpy2xx_priv_data *pdata;
	bool new;
	pr_debug("Entering %s %d\n", __func__, __LINE__);

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (gpy211_parse_rxsc_config(attrs, tb_rxsc))
		return -EINVAL;

	if (!gpy211_validate_add_rxsc(tb_rxsc))
		return -EINVAL;

	pdata = (struct gpy2xx_priv_data *)platform_get_drvdata(gpy212_data.pdev[0]);

	secy = &pdata->secy;

	if (!tb_rxsc[MACSEC_RXSC_ATTR_SCI])
		return -EINVAL;

	sci = nla_get_u64(tb_rxsc[MACSEC_RXSC_ATTR_SCI]);
	rx_sc = gpy211_find_rx_sc_rtnl(secy, sci);

	if (IS_ERR(rx_sc))
		return PTR_ERR(rx_sc);

	if (tb_rxsc[MACSEC_RXSC_ATTR_ACTIVE]) {
		new = !!nla_get_u8(tb_rxsc[MACSEC_RXSC_ATTR_ACTIVE]);

		if (rx_sc->active != new)
			secy->n_rx_sc += new ? 1 : -1;

		rx_sc->active = new;
	}

	pr_debug("Exiting %s %d\n", __func__, __LINE__);
	return 0;
}

int gpy211_del_rxsc(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **attrs = info->attrs;
	struct gpy211_macsec_secy *secy;
	struct gpy211_macsec_rx_sc *rx_sc;
	sci_t sci;
	struct nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	struct gpy2xx_priv_data *pdata;
	pr_debug("Entering %s %d\n", __func__, __LINE__);

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (gpy211_parse_rxsc_config(attrs, tb_rxsc))
		return -EINVAL;

	if (!tb_rxsc[MACSEC_RXSC_ATTR_SCI])
		return -EINVAL;

	pdata = (struct gpy2xx_priv_data *)platform_get_drvdata(gpy212_data.pdev[0]);
	secy = &pdata->secy;
	sci = nla_get_u64(tb_rxsc[MACSEC_RXSC_ATTR_SCI]);

	rx_sc = gpy211_del_rx_sc(secy, sci);

	if (!rx_sc)
		return -ENODEV;

	gpy211_free_rx_sc(rx_sc);

	pr_debug("Exiting %s %d\n", __func__, __LINE__);
	return 0;
}

int gpy211_add_txsa(struct sk_buff *skb, struct genl_info *info)
{
	int ret;

	struct net_device *dev;
	struct nlattr **attrs = info->attrs;
	struct nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	struct gpy211_macsec_secy *secy, *dev_secy;
	struct gpy211_macsec_tx_sc *tx_sc;
	struct gpy211_macsec_tx_sa *tx_sa;
	struct gpy2xx_priv_data *pdata;
	struct gpy211_macsec_data *msec_data;
	pr_debug("Entering %s %d\n", __func__, __LINE__);

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (gpy211_parse_sa_config(attrs, tb_sa))
		return -EINVAL;

	if (!gpy211_validate_add_txsa(tb_sa))
		return -EINVAL;

	dev = gpy211_get_dev_from_nl(genl_info_net(info), attrs);

	if (IS_ERR(dev))
		return PTR_ERR(dev);

	dev_secy = netdev_priv(dev);

	pdata = (struct gpy2xx_priv_data *)platform_get_drvdata(gpy212_data.pdev[0]);

	gpy211_copy_dev_secy_data(&pdata->secy, dev_secy);

#ifdef DEBUG_PRINT //Delete later
	pr_debug("No.of rx SCs %d\n", pdata->secy.n_rx_sc);
	pr_debug("SCI %llx\n", pdata->secy.sci);
	pr_debug("Key len %d\n", pdata->secy.key_len);
	pr_debug("ICV len %d\n", pdata->secy.icv_len);
	pr_debug("Val lvl %d\n", pdata->secy.validate_frames);
	pr_debug("Protect %d\n", pdata->secy.protect_frames);
#endif

	secy = &pdata->secy;
	tx_sc = &secy->tx_sc;

	msec_data = (struct gpy211_macsec_data *)&pdata->gdev.macsec_data;

	msec_data->egr_data.trans_rec.ccw.an = nla_get_u8(tb_sa[MACSEC_SA_ATTR_AN]);

	tx_sa = tx_sc->sa[msec_data->egr_data.trans_rec.ccw.an];

	if (tx_sa) {
		pr_warn("SA %d is already in use\n", msec_data->egr_data.trans_rec.ccw.an);
		return -EBUSY;
	}

	tx_sa =  kzalloc(sizeof(*tx_sa), in_atomic() ? GFP_ATOMIC : GFP_KERNEL);

	if (!tx_sa)
		return -ENOMEM;

	tx_sc->sa[msec_data->egr_data.trans_rec.ccw.an] = tx_sa;

	msec_data->egr_data.trans_rec.pn_rc.seq0 = nla_get_u32(tb_sa[MACSEC_SA_ATTR_PN]);

	memcpy(msec_data->egr_data.sam_param.da_mac, dev->dev_addr, 6);

#ifdef DEBUG_PRINT //Delete later
	pr_debug("The parsed AN = %d", msec_data->egr_data.trans_rec.ccw.an);
	pr_debug("The parsed Seq0 = %x", msec_data->egr_data.trans_rec.pn_rc.seq0);
	pr_debug("The dst MAC1 = %2x:%2x:%2x:%2x:%2x:%2x", msec_data->egr_data.sam_param.da_mac[5], msec_data->egr_data.sam_param.da_mac[4],
		 msec_data->egr_data.sam_param.da_mac[3], msec_data->egr_data.sam_param.da_mac[2], msec_data->egr_data.sam_param.da_mac[1],
		 msec_data->egr_data.sam_param.da_mac[0]);
	pr_debug("The dst MAC2 = %pM", msec_data->egr_data.sam_param.da_mac);
	pr_debug("The dst MAC3 = %pMR", msec_data->egr_data.sam_param.da_mac);
#endif

	if (nla_len(tb_sa[MACSEC_SA_ATTR_KEY]) != secy->key_len) {
		pr_notice("nl: add_txsa: bad key length: %d != %d\n",
			  nla_len(tb_sa[MACSEC_SA_ATTR_KEY]), secy->key_len);
		return -EINVAL;
	}

	memcpy(tx_sc->sa[msec_data->egr_data.trans_rec.ccw.an]->key.key,
	       (u8 *)nla_data(tb_sa[MACSEC_SA_ATTR_KEY]),
	       secy->key_len);

	memcpy(msec_data->egr_data.trans_rec.cp.key, (u8 *)nla_data(tb_sa[MACSEC_SA_ATTR_KEY]), secy->key_len);
	//memcpy(msec_data->egr_data.trans_rec.cp.sci, (char *)&pdata->secy.sci, MACSEC_SCI_LEN_BYTE);
	msec_data->egr_data.trans_rec.cp.scid = pdata->secy.sci;
	gpy211_get_smac_from_sci(msec_data->egr_data.trans_rec.cp.scid, msec_data->egr_data.sam_param.sa_mac);

#ifdef DEBUG_PRINT //Delete later
	pr_debug("The linuxp key = %16phN", tx_sc->sa[msec_data->egr_data.trans_rec.ccw.an]->key.key);
	pr_debug("The copied key = %16phN", msec_data->egr_data.trans_rec.cp.key);
	pr_debug("Copied SCI %llx\n", msec_data->egr_data.trans_rec.cp.scid);

	pr_debug("The src MAC1 = %2x:%2x:%2x:%2x:%2x:%2x", msec_data->egr_data.sam_param.sa_mac[5], msec_data->egr_data.sam_param.sa_mac[4],
		 msec_data->egr_data.sam_param.sa_mac[3], msec_data->egr_data.sam_param.sa_mac[2], msec_data->egr_data.sam_param.sa_mac[1],
		 msec_data->egr_data.sam_param.sa_mac[0]);
	pr_debug("The src MAC2 = %pM", msec_data->egr_data.sam_param.sa_mac);
	pr_debug("The src MAC3 = %pMR", msec_data->egr_data.sam_param.sa_mac);
#endif
	//Set to default values
	msec_data->egr_data.trans_rec.ccw.ca_type = CA_AES_CTR_128;
	msec_data->egr_data.trans_rec.ccw.sn_type = SN_32_BIT;
	//msec_data->egr_data.trans_rec.pn_rc.mask = pdata->secy.replay_window;

	//User need update all below vars.
	msec_data->egr_data.trans_rec.sarule_num = 0;
	msec_data->egr_data.trans_rec.sa_update.sa_index = 0;
	msec_data->egr_data.trans_rec.sa_update.sa_expired_irq = 1;
	msec_data->egr_data.trans_rec.sa_update.sa_index_valid = 0;
	msec_data->egr_data.trans_rec.sa_update.flow_index = 0;
	msec_data->egr_data.trans_rec.sa_update.sa_ind_update_en = 1;

	ret = gpy2xx_msec_config_egr_tr(&pdata->gdev, &msec_data->egr_data.trans_rec);

	if (ret < 0) {
		pr_err("ERROR: Egress TR set failed.\n");
		return -1;
	}

	//User need update all below vars.
	msec_data->egr_data.sam_param.sarule_num = 0;
	msec_data->egr_data.sam_param.eth_type = 0x0800;
	msec_data->egr_data.sam_param.misc_par.misc = 0xf00;
	msec_data->egr_data.sam_param.scid = pdata->secy.sci;
	msec_data->egr_data.sam_param.mask_par.mask = 0x03f;
	msec_data->egr_data.sam_param.extn_par.flow_index = 0;

	ret = gpy2xx_msec_config_egr_sam_rule(&pdata->gdev, &msec_data->egr_data.sam_param);

	if (ret < 0) {
		pr_err("ERROR: Egress SAM set failed.\n");
		return -1;
	}

	//User need update all below vars.
	msec_data->egr_data.sam_fca.sarule_num = 0;
	msec_data->egr_data.sam_fca.flow_type = SAM_FCA_FLOW_EGRESS;
	msec_data->egr_data.sam_fca.dest_port = SAM_FCA_DPT_COMMON;
	msec_data->egr_data.sam_fca.protect_frame = 1;
	msec_data->egr_data.sam_fca.sa_in_use = 1;
	msec_data->egr_data.sam_fca.include_sci = 1;
	msec_data->egr_data.sam_fca.use_es = 0;
	msec_data->egr_data.sam_fca.use_scb = 0;
	msec_data->egr_data.sam_fca.conf_protect = 1;
#if defined(ENABLE_ON_TARGET) &&  ENABLE_ON_TARGET //Need enable on target
	ret = gpy2xx_msec_config_egr_sam_fca(&pdata->gdev, &msec_data->egr_data.sam_fca);
#endif

	if (ret < 0) {
		pr_err("ERROR: Egress SAM FCA set failed.\n");
		return -1;
	}

	msec_data->egr_data.sam_eex.eex_type = SAM_EE_SET;
	msec_data->egr_data.sam_eex.raw_sam_ee[0] = 1;
#if defined(ENABLE_ON_TARGET) &&  ENABLE_ON_TARGET //Need enable on target
	ret = gpy2xx_msec_config_egr_sam_eex(&pdata->gdev, &msec_data->egr_data.sam_eex);
#endif

	if (ret < 0) {
		pr_err("ERROR: Egress SAM EEX set failed.\n");
		return -1;
	}

	pr_debug("Exiting %s %d\n", __func__, __LINE__);
	return 0;
}

int gpy211_add_rxsa(struct sk_buff *skb, struct genl_info *info)
{
	int ret;

	struct net_device *dev;
	struct nlattr **attrs = info->attrs;
	struct gpy211_macsec_secy *secy, *dev_secy;
	struct gpy211_macsec_rx_sc *rx_sc;
	struct gpy211_macsec_rx_sa *rx_sa;
	struct nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	struct nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	struct gpy2xx_priv_data *pdata;
	struct gpy211_macsec_data *msec_data;
	pr_debug("Entering %s %d\n", __func__, __LINE__);

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (gpy211_parse_sa_config(attrs, tb_sa))
		return -EINVAL;

	if (gpy211_parse_rxsc_config(attrs, tb_rxsc))
		return -EINVAL;

	if (!gpy211_validate_add_rxsa(tb_sa))
		return -EINVAL;

	dev = gpy211_get_dev_from_nl(genl_info_net(info), attrs);

	if (IS_ERR(dev))
		return PTR_ERR(dev);

	dev_secy = netdev_priv(dev);

	pdata = (struct gpy2xx_priv_data *)platform_get_drvdata(gpy212_data.pdev[0]);

	gpy211_copy_dev_secy_data(&pdata->secy, dev_secy);

#ifdef DEBUG_PRINT //Delete later
	pr_debug("No.of rx SCs %d\n", pdata->secy.n_rx_sc);
	pr_debug("SCI %llx\n", pdata->secy.sci);
	pr_debug("Key len %d\n", pdata->secy.key_len);
	pr_debug("ICV len %d\n", pdata->secy.icv_len);
	pr_debug("Val lvl %d\n", pdata->secy.validate_frames);
	pr_debug("Rep protect %d\n", pdata->secy.replay_protect);
	pr_debug("Rep window %d\n", pdata->secy.replay_window);
#endif

	secy = &pdata->secy;

	if (!tb_rxsc[MACSEC_RXSC_ATTR_SCI])
		return -EINVAL;

	msec_data = (struct gpy211_macsec_data *)&pdata->gdev.macsec_data;

	//memcpy(msec_data->ing_data.trans_rec.cp.sci, (char *)&pdata->secy.sci, MACSEC_SCI_LEN_BYTE);
	//msec_data->ing_data.trans_rec.cp.scid = pdata->secy.sci;
	msec_data->ing_data.trans_rec.cp.scid = nla_get_u64(tb_rxsc[MACSEC_RXSC_ATTR_SCI]);
	gpy211_get_smac_from_sci(msec_data->ing_data.trans_rec.cp.scid, msec_data->ing_data.sam_param.sa_mac);

	rx_sc = gpy211_find_rx_sc_rtnl(secy, msec_data->ing_data.trans_rec.cp.scid);

	if (IS_ERR(rx_sc))
		return PTR_ERR(rx_sc);

	msec_data->ing_data.trans_rec.ccw.an = nla_get_u8(tb_sa[MACSEC_SA_ATTR_AN]);

	rx_sa = rx_sc->sa[msec_data->ing_data.trans_rec.ccw.an];

	if (rx_sa) {
		LOG_INFO("SA %d is already  in use\n", msec_data->ing_data.trans_rec.ccw.an);
		return -EBUSY;
	}

	rx_sa = kzalloc(sizeof(*rx_sa), in_atomic() ? GFP_ATOMIC : GFP_KERNEL);

	if (!rx_sa)
		return -ENOMEM;

	rx_sa->sc = rx_sc;
	rx_sc->sa[msec_data->ing_data.trans_rec.ccw.an] = rx_sa;

	msec_data->ing_data.trans_rec.pn_rc.seq0 = nla_get_u32(tb_sa[MACSEC_SA_ATTR_PN]);

	memcpy(msec_data->ing_data.sam_param.da_mac, dev->dev_addr, 6);

#ifdef DEBUG_PRINT //Delete later
	pr_debug("The parsed AN = %d", msec_data->ing_data.trans_rec.ccw.an);
	pr_debug("The parsed Seq0 = %x", msec_data->ing_data.trans_rec.pn_rc.seq0);
	pr_debug("The dst MAC1 = %2x:%2x:%2x:%2x:%2x:%2x", msec_data->ing_data.sam_param.da_mac[5], msec_data->ing_data.sam_param.da_mac[4],
		 msec_data->ing_data.sam_param.da_mac[3], msec_data->ing_data.sam_param.da_mac[2], msec_data->ing_data.sam_param.da_mac[1],
		 msec_data->ing_data.sam_param.da_mac[0]);
	pr_debug("The dst MAC2 = %pM", msec_data->ing_data.sam_param.da_mac);
	pr_debug("The dst MAC3 = %pMR", msec_data->ing_data.sam_param.da_mac);
#endif

	if (nla_len(tb_sa[MACSEC_SA_ATTR_KEY]) != secy->key_len) {
		pr_notice("macsec: nl: add_rxsa: bad key length: %d != %d\n",
			  nla_len(tb_sa[MACSEC_SA_ATTR_KEY]), secy->key_len);
		return -EINVAL;
	}

#if 0
	if (tb_sa[MACSEC_SA_ATTR_PN])
		rx_sa->next_pn = nla_get_u32(tb_sa[MACSEC_SA_ATTR_PN]);

	if (tb_sa[MACSEC_SA_ATTR_ACTIVE])
		rx_sa->active = !!nla_get_u8(tb_sa[MACSEC_SA_ATTR_ACTIVE]);

	nla_memcpy(rx_sa->key.id, tb_sa[MACSEC_SA_ATTR_KEYID],
		   MACSEC_KEYID_LEN);

	memcpy(rx_sc->sa[msec_data->ing_data.trans_rec.ccw.an]->key.key,
	   (u8 *)nla_data(tb_sa[MACSEC_SA_ATTR_KEY]),
	   secy->key_len);

	memcpy(rx_sa->key.key, (u8 *)nla_data(tb_sa[MACSEC_SA_ATTR_KEY]),
	       secy->key_len);
#endif

	memcpy(msec_data->ing_data.trans_rec.cp.key, (u8 *)nla_data(tb_sa[MACSEC_SA_ATTR_KEY]), secy->key_len);

#ifdef DEBUG_PRINT //Delete later
	pr_debug("The copied key = %16phN", msec_data->ing_data.trans_rec.cp.key);
	pr_debug("Copied SCI %llx\n", msec_data->ing_data.trans_rec.cp.scid);

	pr_debug("The src MAC1 = %2x:%2x:%2x:%2x:%2x:%2x", msec_data->ing_data.sam_param.sa_mac[5], msec_data->ing_data.sam_param.sa_mac[4],
		 msec_data->ing_data.sam_param.sa_mac[3], msec_data->ing_data.sam_param.sa_mac[2], msec_data->ing_data.sam_param.sa_mac[1],
		 msec_data->ing_data.sam_param.sa_mac[0]);
	pr_debug("The src MAC2 = %pM", msec_data->ing_data.sam_param.sa_mac);
	pr_debug("The src MAC3 = %pMR", msec_data->ing_data.sam_param.sa_mac);

#endif

	//Set to default values
	msec_data->ing_data.trans_rec.ccw.ca_type = CA_AES_CTR_128;
	msec_data->ing_data.trans_rec.ccw.sn_type = SN_32_BIT;
	//msec_data->ing_data.trans_rec.pn_rc.mask = pdata->secy.replay_window;

	//User need update all below vars.
	msec_data->ing_data.trans_rec.sa_index = 0;
	msec_data->ing_data.trans_rec.sa_update.sa_index = 0;
	msec_data->ing_data.trans_rec.sa_update.sa_expired_irq = 1;
	msec_data->ing_data.trans_rec.sa_update.sa_index_valid = 0;
	msec_data->ing_data.trans_rec.sa_update.flow_index = 0;
	msec_data->ing_data.trans_rec.sa_update.sa_ind_update_en = 1;

	ret = gpy2xx_msec_config_ing_tr(&pdata->gdev, &msec_data->ing_data.trans_rec);

	if (ret < 0) {
		pr_err("ERROR: Egress TR set failed.\n");
		return -1;
	}

	//User need update all below vars.
	msec_data->ing_data.sam_param.rule_index = 0;
	msec_data->ing_data.sam_param.eth_type = 0x0800;
	msec_data->ing_data.sam_param.misc_par.misc = 0xf00;
	msec_data->ing_data.sam_param.scid = pdata->secy.sci;
	msec_data->ing_data.sam_param.mask_par.mask = 0x03f;
	msec_data->ing_data.sam_param.extn_par.flow_index = 0;

	ret = gpy2xx_msec_config_ing_sam_rule(&pdata->gdev, &msec_data->ing_data.sam_param);

	if (ret < 0) {
		pr_err("ERROR: Egress SAM set failed.\n");
		return -1;
	}

	//User need update all below vars.
	msec_data->ing_data.sam_fca.flow_index = 0;
	msec_data->ing_data.sam_fca.flow_type = SAM_FCA_FLOW_INGRESS;
	msec_data->ing_data.sam_fca.dest_port = SAM_FCA_DPT_COMMON;
	msec_data->ing_data.sam_fca.protect_frame = 1;
	msec_data->ing_data.sam_fca.sa_index = 0;
	msec_data->ing_data.sam_fca.sa_in_use = 1;
	msec_data->ing_data.sam_fca.include_sci = 1;
	msec_data->ing_data.sam_fca.use_es = 0;
	msec_data->ing_data.sam_fca.use_scb = 0;
	msec_data->ing_data.sam_fca.conf_protect = 1;
#if defined(ENABLE_ON_TARGET) &&  ENABLE_ON_TARGET //Need enable on target
	ret = gpy2xx_msec_config_ing_sam_fca(&pdata->gdev, &msec_data->ing_data.sam_fca);
#endif

	if (ret < 0) {
		pr_err("ERROR: Egress SAM FCA set failed.\n");
		return -1;
	}

	msec_data->ing_data.sam_eex.eex_type = SAM_EE_SET;
	msec_data->ing_data.sam_eex.raw_sam_ee[0] = 1;
#if defined(ENABLE_ON_TARGET) &&  ENABLE_ON_TARGET //Need enable on target
	ret = gpy2xx_msec_config_ing_sam_eex(&pdata->gdev, &msec_data->ing_data.sam_eex);
#endif

	if (ret < 0) {
		pr_err("ERROR: Egress SAM EEX set failed.\n");
		return -1;
	}

	pr_debug("Exiting %s %d\n", __func__, __LINE__);
	return 0;
}

int gpy211_add_rxsc(struct sk_buff *skb, struct genl_info *info)
{
	sci_t sci = 0xffffffffffffffffULL;
	struct nlattr **attrs = info->attrs;
	struct gpy211_macsec_rx_sc *rx_sc;
	struct nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	pr_debug("Entering %s %d\n", __func__, __LINE__);

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (gpy211_parse_rxsc_config(attrs, tb_rxsc))
		return -EINVAL;

	if (!gpy211_validate_add_rxsc(tb_rxsc))
		return -EINVAL;

	sci = nla_get_u64(tb_rxsc[MACSEC_RXSC_ATTR_SCI]);

	rx_sc = gpy211_create_rx_sc(sci);

	if (IS_ERR(rx_sc))
		return PTR_ERR(rx_sc);

	if (tb_rxsc[MACSEC_RXSC_ATTR_ACTIVE])
		rx_sc->active = !!nla_get_u8(tb_rxsc[MACSEC_RXSC_ATTR_ACTIVE]);

	pr_debug("Exiting %s %d\n", __func__, __LINE__);
	return 0;
}

void gpy211_macsec_postdoit(const struct genl_ops *ops,
			    struct sk_buff *skb,
			    struct genl_info *info)
{
	pr_debug("Entering %s %d\n", __func__, __LINE__);

	switch (ops->cmd) {
	case MACSEC_CMD_ADD_RXSC:
		LOG_INFO("Recieved MACSEC_CMD_ADD_RXSC\n");
		gpy211_add_rxsc(skb, info);
		break;

	case MACSEC_CMD_DEL_RXSC:
		LOG_INFO("Recieved MACSEC_CMD_DEL_RXSC\n");
		gpy211_del_rxsc(skb, info);
		break;

	case MACSEC_CMD_UPD_RXSC:
		LOG_INFO("Recieved MACSEC_CMD_UPD_RXSC\n");
		gpy211_upd_rxsc(skb, info);
		break;

	case MACSEC_CMD_ADD_TXSA:
		LOG_INFO("Recieved MACSEC_CMD_ADD_TXSA\n");
		gpy211_add_txsa(skb, info);
		break;

	case MACSEC_CMD_DEL_TXSA:
		LOG_INFO("Recieved MACSEC_CMD_DEL_TXSA\n");
		//gpy211_del_txsa(skb, info);
		break;

	case MACSEC_CMD_UPD_TXSA:
		LOG_INFO("Recieved MACSEC_CMD_UPD_TXSA\n");
		//gpy211_upd_txsa(skb, info);
		break;

	case MACSEC_CMD_ADD_RXSA:
		LOG_INFO("Recieved MACSEC_CMD_ADD_RXSA\n");
		gpy211_add_rxsa(skb, info);
		break;

	case MACSEC_CMD_DEL_RXSA:
		LOG_INFO("Recieved MACSEC_CMD_DEL_RXSA\n");
		//gpy211_del_rxsa(skb, info);
		break;

	case MACSEC_CMD_UPD_RXSA:
		LOG_INFO("Recieved MACSEC_CMD_UPD_RXSA\n");
		//gpy211_upd_rxsa(skb, info);
		break;

	default:
		LOG_INFO("Recieved default macsec Postdoit\n");
		break;
	};

	pr_debug("Exiting %s %d\n", __func__, __LINE__);

	return;
}
