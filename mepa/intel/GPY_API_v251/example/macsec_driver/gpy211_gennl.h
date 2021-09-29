/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#ifndef _GPY211_GENNL_H_
#define _GPY211_GENNL_H_

#include <linux/types.h>
#include <uapi/linux/if_macsec.h>
//#include <net/gpy211/gpy211_ops.h>

#include "gpy211.h"
#include "gpy211_macsec.h"

typedef u64 __bitwise sci_t;

#define MACSEC_VALIDATE_DEFAULT MACSEC_VALIDATE_STRICT

/**
 * struct gpy211_macsec_key - SA key
 * id: user-provided key identifier
 * key: user-provided key
 * hkey: generated from key
 */
struct gpy211_macsec_key {
	u8 id[MACSEC_KEY_LEN_BYTE];
	u8 key[MACSEC_KEY_LEN_BYTE];
	u8 hkey[MACSEC_HKEY_LEN_BYTE];
};

/**
 * struct gpy211_macsec_rx_sc - receive secure channel
 * sci: secure channel identifier for this SC
 * active: channel is active
 * sa: array of secure associations
 * stats: per-SC stats
 */
struct gpy211_macsec_rx_sc {
	struct gpy211_macsec_rx_sc *next;
	sci_t sci;
	bool active;
	struct gpy211_macsec_rx_sa *sa[MACSEC_MAX_AN];
#ifdef __KERNEL__
	atomic_t refcnt;
#endif
};

/**
 * struct gpy211_macsec_rx_sa - receive secure association
 * active:
 * next_pn: packet number expected for the next packet
 * key: key structure
 * stats: per-SA stats
 */
struct gpy211_macsec_rx_sa {
	struct gpy211_macsec_key key;
	u32 next_pn;
#ifdef __KERNEL__
	atomic_t refcnt;
#endif
	bool active;
	struct gpy211_macsec_rx_sc *sc;
};

/**
 * struct gpy211_macsec_tx_sa - transmit secure association
 * active:
 * next_pn: packet number to use for the next packet
 * key: key structure
 * stats: per-SA stats
 */
struct gpy211_macsec_tx_sa {
	struct gpy211_macsec_key key;
	u32 next_pn;
#ifdef __KERNEL__
	atomic_t refcnt;
#endif
	bool active;
};

/**
 * struct gpy211_macsec_tx_sc - transmit secure channel
 * active:
 * encoding_sa: association number of the SA currently in use
 * encrypt: encrypt packets on transmit, or authenticate only
 * send_sci: always include the SCI in the SecTAG
 * end_station:
 * scb: single copy broadcast flag
 * sa: array of secure associations
 * stats: stats for this TXSC
 */
struct gpy211_macsec_tx_sc {
	bool active;
	u8 encoding_sa;
	bool encrypt;
	bool send_sci;
	bool end_station;
	bool scb;
	struct gpy211_macsec_tx_sa *sa[MACSEC_MAX_AN];
};

/**
 * struct gpy211_macsec_secy - MACsec Security Entity
 * netdev: netdevice for this SecY
 * n_rx_sc: number of receive secure channels configured on this SecY
 * sci: secure channel identifier used for tx
 * key_len: length of keys used by the cipher suite
 * icv_len: length of ICV used by the cipher suite
 * validate_frames: validation mode
 * operational: MAC_Operational flag
 * protect_frames: enable protection for this SecY
 * replay_protect: enable packet number checks on receive
 * replay_window: size of the replay window
 * tx_sc: transmit secure channel
 * rx_sc: linked list of receive secure channels
 */
struct gpy211_macsec_secy {
#ifdef __KERNEL__
	struct net_device *netdev;
#endif
	u32 n_rx_sc;
	sci_t sci;
	u16 key_len;
	u16 icv_len;
	enum macsec_validation_type validate_frames;
	bool operational;
	bool protect_frames;
	bool replay_protect;
	u32 replay_window;
	struct gpy211_macsec_tx_sc tx_sc;
	struct gpy211_macsec_rx_sc *rx_sc;
};

/** \addtogroup GPY211_MSEC_TOP */
/*@{*/
/** \brief GPHY MACsec Information. */
struct macsec_data {
	/** \brief  Max SAs supported */
	u8 nr_of_sas;
	/** \brief EIP160 version info \ref eip160_version */
	struct eip160_version eip_ver;
	/** \brief EIP160 config info \ref eip160_config */
	struct eip160_config eip_cfg;
	/** \brief EIP160 extended config info \ref eip160_config2 */
	struct eip160_config2 eip_cfg2;
	/** \brief Transform record info \ref transform_rec */
	struct transform_rec trans_rec;
	/** \brief SAM parameters info \ref sa_match_param */
	struct sa_match_param sam_param;
	/** \brief SAM flow control action info \ref sa_match_fca */
	struct sa_match_fca sam_fca;
	/** \brief SANM flow control action info \ref sa_nonmatch_fca */
	struct sa_nonmatch_fca sanm_fca;
	/** \brief SAM entry enable control info \ref sam_ee_ctrl */
	struct sam_ee_ctrl sam_eec;
	/** \brief SAM entry enable control flags \ref raw_sam_ee */
	struct raw_sam_ee sam_eex;
	/** \brief Ingress consistency check control info \ref ing_cc_ctrl */
	struct ing_cc_ctrl icc_ctrl;
	/** \brief Counter control info \ref count_control */
	struct count_control cnt_ctrl;
	/** \brief Counter increment enable info \ref count_incen */
	struct count_incen cnt_incx;
	/** \brief Misc control info \ref misc_control */
	struct misc_control misc_ctrl;
	/** \brief SA no-match control info \ref sa_nm_params */
	struct sa_nm_params sanm_ctrl;
	/** \brief SA expiry summary info \ref stats_summary */
	struct stats_summary sax_summ;
	/** \brief Control packet classification info \ref cp_class_param */
	struct cp_class_param cpc_param;
};

/** \brief GPHY MACsec Information. */
struct gpy211_macsec_data {
	/** \brief GPHY MACsec Ingress Information \ref ing_msec_data */
	struct macsec_data ing_data;
	/** \brief GPHY MACsec Egress Information \ref egr_msec_data */
	struct macsec_data egr_data;
};
/*@}*/ /* GPY211_MSEC_TOP */

/**
 * struct macsec_dev - private data
 * secy: SecY config
 * real_dev: pointer to underlying netdevice
 */
struct gpy2xx_priv_data {
	u32 id;

#ifdef __KERNEL__
	struct net_device *real_dev;
#endif

	struct gpy211_macsec_secy secy;
#if defined(SUPPORT_GPY2XX_OPS) && SUPPORT_GPY2XX_OPS
	struct gpy211_gphy_ops ops;
#endif
	struct gpy211_device gdev;
};

#if defined(SUPPORT_GPY2XX_OPS) && SUPPORT_GPY2XX_OPS
int gpy211_ops_init(struct gpy211_gphy_ops *ops);

static inline struct gpy2xx_priv_data *MACSEC_PDATA(void *pdev)
{
	struct gpy2xx_priv_data *pdata;

	struct gpy211_gphy_ops *gphy_ops = (struct gpy211_gphy_ops *)pdev;
	pdata = container_of(gphy_ops, struct gpy2xx_priv_data, ops);

	return pdata;
}
#endif

#endif /* _GPY211_GENNL_H_ */
