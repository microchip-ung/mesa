/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#include "gpy211_common.h"
#include "gpy211_phy.h"
#include "gpy211_regs.h"

#if ENABLE_CHIP_FUNC
extern int __gpy211_chip_init(struct gpy211_device *phy);
#endif

static int __gpy211_read_supported(struct gpy211_device *phy)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	data->link.supported = 0;
	// TODO: double check the supported connection type
	data->link.supported = (GPY2XX_SUPPORTED_Pause |
				GPY2XX_SUPPORTED_Asym_Pause);

	ret = PHY_READ_MMD(phy, MDIO_MMD_PMAPMD, PMA_SPEED_ABILITY);

	if (ret < 0) {
		LOG_CRIT("ERROR: PMA_SPEED_ABILITY read fails\n");
		return ret;
	}

	if (ret & PMA_SPEED_ABILITY_CAP_5G_MASK) {
		data->link.supported |= GPY2XX_SUPPORTED_5000baseT_Full;
		//data->link.supported |= GPY2XX_SUPPORTED_5000baseT_FR;
	}

	if (ret & PMA_SPEED_ABILITY_CAP_2G5_MASK) {
		data->link.supported |= GPY2XX_SUPPORTED_2500baseT_Full;
		//data->link.supported |= GPY2XX_SUPPORTED_2500baseT_FR;
	}

	ret = PHY_READ(phy, STD_STD_STAT);

	if (ret < 0) {
		LOG_CRIT("ERROR: STD_STAT read fails\n");
		return ret;
	}

	if (ret & STD_STAT_ANAB_MASK)
		data->link.supported |= GPY2XX_SUPPORTED_Autoneg;

	if (ret & STD_STAT_CBTXF_MASK)
		data->link.supported |= GPY2XX_SUPPORTED_100baseT_Full;

	if (ret & STD_STAT_CBTXH_MASK)
		data->link.supported |= GPY2XX_SUPPORTED_100baseT_Half;

	if (ret & STD_STAT_XBTF_MASK)
		data->link.supported |= GPY2XX_SUPPORTED_10baseT_Full;

	if (ret & STD_STAT_XBTH_MASK)
		data->link.supported |= GPY2XX_SUPPORTED_10baseT_Half;

	if (ret & STD_STAT_EXT_MASK) {
		ret = PHY_READ(phy, STD_STD_XSTAT);

		if (ret < 0) {
			LOG_CRIT("ERROR: STD_XSTAT read fails\n");
			return ret;
		}

		if (ret & STD_XSTAT_MBTF_MASK)
			data->link.supported |= GPY2XX_SUPPORTED_1000baseT_Full;

		if (ret & STD_XSTAT_MBTH_MASK) {
			//data->link.supported |= GPY2XX_SUPPORTED_1000baseT_Half;
		}
	}

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

static int __gpy211_read_advertising(struct gpy211_device *phy)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int adv, status;
	LOG_INFO("Entering func name :- %s\n", __func__);

	data->link.advertising = 0;
	/* 10/100M */
	adv = PHY_READ(phy, STD_STD_AN_ADV);

	if (adv < 0) {
		LOG_CRIT("ERROR: STD_AN_ADV read fails\n");
		return adv;
	}

	if (adv & (CONST_STD_AN_ADV_TAF_XBT_HDX << STD_AN_ADV_TAF_POS))
		data->link.advertising |= GPY2XX_ADVERTISED_10baseT_Half;

	if (adv & (CONST_STD_AN_ADV_TAF_XBT_FDX << STD_AN_ADV_TAF_POS))
		data->link.advertising |= GPY2XX_ADVERTISED_10baseT_Full;

	if (adv & (CONST_STD_AN_ADV_TAF_DBT_HDX << STD_AN_ADV_TAF_POS))
		data->link.advertising |= GPY2XX_ADVERTISED_100baseT_Half;

	if (adv & (CONST_STD_AN_ADV_TAF_DBT_FDX << STD_AN_ADV_TAF_POS))
		data->link.advertising |= GPY2XX_ADVERTISED_100baseT_Full;

	if (adv & (CONST_STD_AN_ADV_TAF_PS_SYM << STD_AN_ADV_TAF_POS))
		data->link.advertising |= GPY2XX_ADVERTISED_Pause;

	if (adv & (CONST_STD_AN_ADV_TAF_PS_ASYM << STD_AN_ADV_TAF_POS))
		data->link.advertising |= GPY2XX_ADVERTISED_Asym_Pause;

	status = PHY_READ_MMD(phy, MDIO_MMD_AN, ANEG_STAT);

	if (status < 0) {
		LOG_CRIT("ERROR: ANEG_STAT read fails\n");
		return status;
	}

	if (status & ANEG_STAT_ANEG_ABLE_MASK)
		data->link.advertising |= GPY2XX_ADVERTISED_Autoneg;

	/* 1G */
	status = PHY_READ(phy, STD_STD_STAT);

	if (status < 0) {
		LOG_CRIT("ERROR: STD_STAT read fails\n");
		return status;
	}

	if (status & STD_STAT_EXT_MASK) {
		adv = PHY_READ(phy, STD_STD_GCTRL);

		if (adv < 0) {
			LOG_CRIT("ERROR: STD_GCTRL read fails\n");
			return adv;
		}

		if (adv & STD_GCTRL_MBTHD_MASK)
			data->link.advertising |= GPY2XX_ADVERTISED_1000baseT_Half;

		if (adv & STD_GCTRL_MBTFD_MASK)
			data->link.advertising |= GPY2XX_ADVERTISED_1000baseT_Full;
	}

	/* 2.5/5G */
	adv = PHY_READ_MMD(phy, MDIO_MMD_AN, ANEG_MGBT_AN_CTRL);

	if (adv < 0) {
		LOG_CRIT("ERROR: ANEG_MGBT_AN_CTRL read fails\n");
		return adv;
	}

	if (adv & ANEG_MGBT_AN_CTRL_AB_2G5BT_MASK)
		data->link.advertising |= GPY2XX_ADVERTISED_2500baseT_Full;

	if (adv & ANEG_MGBT_AN_CTRL_AB_5GBT_MASK)
		data->link.advertising |= GPY2XX_ADVERTISED_5000baseT_Full;

	if (adv & ANEG_MGBT_AN_CTRL_FR_2G5BT_MASK)
		data->link.advertising |= GPY2XX_ADVERTISED_2500baseT_FR;

	if (adv & ANEG_MGBT_AN_CTRL_FR_5GBT_MASK)
		data->link.advertising |= GPY2XX_ADVERTISED_5000baseT_FR;

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

static int __gpy211_read_status_mg(struct gpy211_device *phy)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int ret;
	u64 supported;
#ifndef READ_VENDOR_SPECIFIC_LINK_STATUS
	int lpa, adv;
#endif
	LOG_INFO("Entering func name :- %s\n", __func__);

	supported = data->link.supported;
	supported &= GPY2XX_SUPPORTED_2500baseT_Full |
		     GPY2XX_SUPPORTED_5000baseT_Full;

	if (supported == 0)
		return 0;

	ret = PHY_READ_MMD(phy, MDIO_MMD_AN, ANEG_STAT);

	if (ret < 0) {
		LOG_CRIT("ERROR: ANEG_STAT read fails\n");
		return ret;
	}

	if (ret & ANEG_STAT_ANEG_COMPLETE_MASK) {
		ret = PHY_READ_MMD(phy, MDIO_MMD_AN, ANEG_MGBT_AN_STA);

		if (ret < 0) {
			LOG_CRIT("ERROR: ANEG_MGBT_AN_STA read fails\n");
			return ret;
		}

		if (ret & ANEG_MGBT_AN_STA_FR_2G5BT_MASK)
			data->link.lp_advertising |= GPY2XX_ADVERTISED_2500baseT_FR;

		if (ret & ANEG_MGBT_AN_STA_FR_5GBT_MASK)
			data->link.lp_advertising |= GPY2XX_ADVERTISED_5000baseT_FR;

		if (ret & ANEG_MGBT_AN_STA_AB_2G5BT_MASK)
			data->link.lp_advertising |= GPY2XX_ADVERTISED_2500baseT_Full;

		if (ret & ANEG_MGBT_AN_STA_AB_5GBT_MASK)
			data->link.lp_advertising |= GPY2XX_ADVERTISED_5000baseT_Full;

#ifndef READ_VENDOR_SPECIFIC_LINK_STATUS

		if (data->link.speed != SPEED_UNKNOWN)
			return 0;

		lpa = ret;

		ret = PHY_READ_MMD(phy, MDIO_MMD_AN, ANEG_MGBT_AN_CTRL);

		if (ret < 0) {
			LOG_CRIT("ERROR: ANEG_MGBT_AN_CTRL read fails\n");
			return ret;
		}

		adv = (ret >> 2) & lpa;

		if (adv & ANEG_MGBT_AN_STA_AB_2G5BT_MASK) {
			data->link.speed = SPEED_2500;
			data->link.duplex = DUPLEX_FULL;
		} else if (adv & ANEG_MGBT_AN_STA_FR_5GBT_MASK) {
			data->link.speed = SPEED_5000;
			data->link.duplex = DUPLEX_FULL;
		}

#endif
	}

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

static int __gpy211_read_status_g(struct gpy211_device *phy)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int ret;
	u64 supported;
#ifndef READ_VENDOR_SPECIFIC_LINK_STATUS
	int lpa, adv;
#endif
	LOG_INFO("Entering func name :- %s\n", __func__);

	supported = data->link.supported;
	supported &= GPY2XX_SUPPORTED_1000baseT_Half |
		     GPY2XX_SUPPORTED_1000baseT_Full;

	if (supported == 0)
		return 0;

	ret = PHY_READ(phy, STD_STD_GSTAT);

	if (ret < 0) {
		LOG_CRIT("ERROR: STD_GSTAT read fails\n");
		return ret;
	}

	if (ret & STD_GSTAT_MBTHD_MASK)
		data->link.lp_advertising |= GPY2XX_ADVERTISED_1000baseT_Half;

	if (ret & STD_GSTAT_MBTFD_MASK)
		data->link.lp_advertising |= GPY2XX_ADVERTISED_1000baseT_Full;

#ifndef READ_VENDOR_SPECIFIC_LINK_STATUS

	if (data->link.speed != SPEED_UNKNOWN)
		return 0;

	lpa = ret;

	ret = PHY_READ(phy, STD_STD_GCTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: STD_GCTRL read fails\n");
		return ret;
	}

	adv = (ret << 2) & lpa;

	if (adv & STD_GSTAT_MBTHD_MASK) {
		data->link.speed = SPEED_1000;
		data->link.duplex = DUPLEX_HALF;
	} else if (adv & STD_GSTAT_MBTFD_MASK) {
		data->link.speed = SPEED_1000;
		data->link.duplex = DUPLEX_FULL;
	}

#endif

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

static int __gpy211_update_link(struct gpy211_device *phy)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	ret = PHY_READ(phy, STD_STD_STAT);

	if (ret < 0) {
		LOG_CRIT("ERROR: STD_STAT read fails\n");
		return ret;
	}

	if ((ret & STD_STAT_LS_MASK) == 0)
		data->link.link = 0;
	else
		data->link.link = 1;

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

static int __gpy211_read_status(struct gpy211_device *phy)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int ret;
	int lpa, taf, ssl = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	ret = __gpy211_update_link(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_update_link fail\n");
		return ret;
	}

	data->link.speed = SPEED_UNKNOWN;
	data->link.duplex = DUPLEX_INVALID;
	data->link.lp_advertising = 0;
	data->link.pause = 0;
	data->link.asym_pause = 0;

	if (data->link.autoneg) {
		ret = __gpy211_read_status_mg(phy);

		if (ret < 0) {
			LOG_CRIT("ERROR: api __gpy211_read_status_mg fail\n");
			return ret;
		}

		ret = __gpy211_read_status_g(phy);

		if (ret < 0) {
			LOG_CRIT("ERROR: api __gpy211_read_status_g fail\n");
			return ret;
		}

#ifdef USE_STD_AN_EXP	// need clarification
		ret = PHY_READ(phy, STD_STD_AN_EXP);

		if (ret < 0) {
			LOG_CRIT("ERROR: STD_AN_EXP fails\n");
			return ret;
		}

		if (ret & STD_AN_EXP_LPANC_MASK)
			data->link.lp_advertising |= GPY2XX_ADVERTISED_Autoneg;

#endif
		ret = PHY_READ(phy, STD_STD_AN_LPA);

		if (ret < 0) {
			LOG_CRIT("ERROR: STD_AN_LPA fails\n");
			return ret;
		}

#ifndef USE_STD_AN_EXP

		if (ret & STD_AN_LPA_ACK_MASK)
			data->link.lp_advertising |= GPY2XX_ADVERTISED_Autoneg;

#endif
		lpa = ret;

		taf = FIELD_GET(lpa, STD_AN_LPA_TAF);

		if (taf & CONST_STD_AN_LPA_TAF_XBT_HDX)
			data->link.lp_advertising |= GPY2XX_ADVERTISED_10baseT_Half;

		if (taf & CONST_STD_AN_LPA_TAF_XBT_FDX)
			data->link.lp_advertising |= GPY2XX_ADVERTISED_10baseT_Full;

		if (taf & CONST_STD_AN_LPA_TAF_DBT_HDX)
			data->link.lp_advertising |= GPY2XX_ADVERTISED_100baseT_Half;

		if (taf & CONST_STD_AN_LPA_TAF_DBT_FDX)
			data->link.lp_advertising |= GPY2XX_ADVERTISED_100baseT_Full;

		if (taf & CONST_STD_AN_LPA_TAF_PS_SYM) {
			data->link.lp_advertising |= GPY2XX_ADVERTISED_Pause;
			data->link.pause = 1;
		}

		if (taf & CONST_STD_AN_LPA_TAF_PS_ASYM) {
			data->link.lp_advertising |= GPY2XX_ADVERTISED_Asym_Pause;
			data->link.asym_pause = 1;
		}

#ifndef READ_VENDOR_SPECIFIC_LINK_STATUS

		if (data->link.speed != SPEED_UNKNOWN)
			return 0;

		ret = PHY_READ(phy, STD_STD_AN_ADV);

		if (ret < 0) {
			LOG_CRIT("ERROR: STD_AN_ADV fails\n");
			return ret;
		}

		taf &= FIELD_GET(ret, STD_AN_ADV_TAF);

		if (taf & GPY2XX_ADVERTISED_100baseT_Full) {
			data->link.speed = SPEED_100;
			data->link.duplex = DUPLEX_FULL;
		} else if (taf & GPY2XX_ADVERTISED_100baseT_Half) {
			data->link.speed = SPEED_100;
			data->link.duplex = DUPLEX_HALF;
		} else if (taf & GPY2XX_ADVERTISED_10baseT_Full) {
			data->link.speed = SPEED_10;
			data->link.duplex = DUPLEX_FULL;
		} else if (taf & GPY2XX_ADVERTISED_10baseT_Half) {
			data->link.speed = SPEED_10;
			data->link.duplex = DUPLEX_HALF;
		}

#else
		ret = PHY_READ(phy, PHY_PHY_MIISTAT);

		if (ret < 0) {
			LOG_CRIT("ERROR: PHY_MIISTAT read fails\n");
			return ret;
		}

		switch (FIELD_GET(ret, PHY_MIISTAT_SPEED)) {
		case CONST_PHY_MIISTAT_SPEED_TEN:
			data->link.speed = SPEED_10;
			break;

		case CONST_PHY_MIISTAT_SPEED_FAST:
			data->link.speed = SPEED_100;
			break;

		case CONST_PHY_MIISTAT_SPEED_GIGA:
			data->link.speed = SPEED_1000;
			break;

		case CONST_PHY_MIISTAT_SPEED_BZ2G5:
			data->link.speed = SPEED_2500;
			break;
		}

		if (FIELD_GET(ret, PHY_MIISTAT_DPX) == CONST_PHY_MIISTAT_DPX_FDX)
			data->link.duplex = DUPLEX_FULL;
		else
			data->link.duplex = DUPLEX_HALF;

#endif
	} else {
		ret = PHY_READ_MMD(phy, MDIO_MMD_PMAPMD, PMA_CTRL1);

		if (ret < 0) {
			LOG_CRIT("ERROR: PMA_CTRL1 read fails\n");
			return ret;
		}

		ssl = FIELD_GET(ret, PMA_CTRL1_SSL);
		ssl |= (FIELD_GET(ret, PMA_CTRL1_SSM)) << 1;

		if (ssl == 3) {
			switch (FIELD_GET(ret, PMA_CTRL1_SPEED_SEL)) {
			case 7:
				data->link.speed = SPEED_5000;
				data->link.duplex = DUPLEX_FULL;
				break;

			case 6:
				data->link.speed = SPEED_2500;
				data->link.duplex = DUPLEX_FULL;
				break;
			}
		} else {
			ret = PHY_READ(phy, STD_STD_CTRL);

			if (ret < 0) {
				LOG_CRIT("ERROR: STD_CTRL read fails\n");
				return ret;
			}

			if (ret & STD_CTRL_DPLX_MASK)
				data->link.duplex = DUPLEX_FULL;
			else
				data->link.duplex = DUPLEX_HALF;

			ssl = FIELD_GET(ret, STD_CTRL_SSL);
			ssl |= FIELD_GET(ret, STD_CTRL_SSM) << 1;

			switch (ssl) {
			case 0:
				data->link.speed = SPEED_10;
				break;

			case 1:
				data->link.speed = SPEED_100;
				break;

			case 2:
				data->link.speed = SPEED_1000;
				break;
			}
		}
	}

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

int __gpy211_config_init(struct gpy211_device *phy)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int ret;
	int wd1, wd2, ctrl;
	u8 byte, byte_c, nibble, nibble_c;
	u32 _ns_oui = 0, _bs_oui = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Get PHY ID (MII) */
	wd1 = PHY_READ(phy, STD_STD_PHYID1);

	if (wd1 < 0) {
		LOG_CRIT("ERROR: STD_PHYID1 read fails\n");
		return wd1;
	}

	wd2 = PHY_READ(phy, STD_STD_PHYID2);

	if (wd2 < 0) {
		LOG_CRIT("ERROR: STD_PHYID2 read fails\n");
		return wd2;
	}

	wd1 = (wd1 << 6) | (wd2 >> 10);

	if ((wd1 | 0x800000) != 0x00984FEE) {
		/* For backward compatibility of FW version 0x0744 and earlier */
		/* Swap byte nibbles in all three bytes */
		for (byte_c = 0; byte_c < 3; byte_c++) {
			/* Get byte */
			byte = (wd1 >> (byte_c << 3)) & 0xFF;
			/* Swap byte nibbles */
			byte = ((byte & 0x0F) << 4) | ((byte & 0xF0) >> 4);
			/* Store in OUI */
			_ns_oui |= (byte << (byte_c << 3));
		}

		/* Swap nibble bits in all six nibbles. 3 <-> 0, 2 <-> 1 */
		for (nibble_c = 0; nibble_c < 6; nibble_c++) {
			/* Get nibble */
			nibble = (_ns_oui >> (nibble_c << 2)) & 0xF;
			/* Swap nibble bits */
			nibble = (((nibble & 0x1) << 3) | ((nibble & 0x8) >> 3) |
				  ((nibble & 0x2) << 1) | ((nibble & 0x4) >> 1));
			/* Store in OUI */
			_bs_oui |= (nibble << (nibble_c << 2));
		}

		data->id.OUI = _bs_oui;
	} else {
		/* From new FW version 0x0745 and above */
		data->id.OUI = (wd1 | 0x800000);
	}

	if (data->id.OUI != 0x00984FEE) {
		LOG_CRIT("ERROR: OUI mismatch: 0x%x != 0x00984FEE\n", data->id.OUI);
		return -ENXIO;
	}

	data->id.model_no = (wd2 & STD_PHYID2_LDN_MASK) >> STD_PHYID2_LDN_POS;
	data->id.revision = (wd2 & STD_PHYID2_LDRN_MASK) >> STD_PHYID2_LDRN_POS;

	/* Get Firmware Version */
	wd1 = PHY_READ(phy, PHY_PHY_FWV);

	if (wd1 < 0) {
		LOG_CRIT("ERROR: PHY_FWV read fails\n");
		return wd1;
	}

	data->id.fw_major = (wd1 & PHY_FWV_MAJOR_MASK) >> PHY_FWV_MAJOR_POS;
	data->id.fw_minor = (wd1 & PHY_FWV_MINOR_MASK) >> PHY_FWV_MINOR_POS;
	data->id.fw_release = (wd1 & PHY_FWV_REL_MASK) ? 1 : 0;

	data->id.drv_major = DRV_MAJOR;
	data->id.drv_minor = DRV_MINOR;
	data->id.drv_release = DRV_RELEASE;

	/* Get Link Status */
	ctrl = PHY_READ(phy, STD_STD_CTRL);

	if (ctrl < 0) {
		LOG_CRIT("ERROR: STD_CTRL read fails\n");
		return ctrl;
	}

	if ((ctrl & STD_CTRL_ANEN_MASK) == 0)
		data->link.autoneg = 0;
	else
		data->link.autoneg = 1;

	ret = __gpy211_read_supported(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_read_supported fail\n");
		return ret;
	}

	ret = __gpy211_read_advertising(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_read_advertising fail\n");
		return ret;
	}

	ret = __gpy211_read_status(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_read_status fail\n");
		return ret;
	}

	/* Wake-on-LAN Config */
	data->wol_supported = WAKE_MAGIC | WAKE_MAGICSECURE;

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

static int __gpy211_init(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

#if ENABLE_CHIP_FUNC
	ret = __gpy211_chip_init(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_chip_init fail\n");
		return ret;
	}

#endif

	ret = __gpy211_config_init(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_config_init fail\n");
		return ret;
	}

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_init(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || phy->mdiobus_read == NULL || phy->mdiobus_write == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	if (phy->lock == NULL || phy->unlock == NULL) {
		phy->lock = none_lock;
		phy->unlock = none_unlock;
	}

	phy->lock(phy->lock_data);

	if (phy->priv_data == NULL) {
		ret = __gpy211_init(phy);

		if (ret < 0) {
			LOG_CRIT("ERROR: api __gpy211_init fail\n");
			goto END;
		}

		if (ret == 0)
			phy->priv_data = (void *)~0; // Application has to populate this?
	}

	//Enable MBOX interrupt mask
	ret = PHY_SET_BIT(phy, PHY_PHY_IMASK, PHY_IMASK_MBOX_POS);

	if (ret < 0) {
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_uninit(struct gpy211_device *phy)
{
	int ret = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	phy->priv_data = 0;
	/* TODO: add uninit code if necessary */

	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_soft_reset(struct gpy211_device *phy)
{
	struct gpy211_device *data;
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	data = phy->shared_data == NULL ? phy : phy->shared_data;

	ret = PHY_SET_BIT(phy, STD_STD_CTRL, STD_CTRL_RST_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: STD_CTRL (RST) write fails\n");
		goto END;
	}

	data->link.autoneg = 1;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_poll_reset(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	ret = PHY_READ(phy, STD_STD_CTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: STD_CTRL read fails\n");
		goto END;
	}

	if (ret >= 0)
		ret = (ret & STD_CTRL_RST_MASK) ? 0 : 1;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

/* 4.7.3 Standard Auto-Negotiation Registers for MMD=0x07 */
/* return 1 - changed, 0 - not changed, <0 - error code */
static int __gpy211_config_advert(struct gpy211_device *phy)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int ret, changed = 0;
	int adv, oldadv;
	int status;
	LOG_INFO("Entering func name :- %s\n", __func__);

	data->link.advertising &= data->link.supported;

	/* 10/100M */
	adv = PHY_READ(phy, STD_STD_AN_ADV);

	if (adv < 0) {
		LOG_CRIT("ERROR: STD_AN_ADV read fails\n");
		return adv;
	}

	oldadv = adv;
	adv &=  ~STD_AN_ADV_TAF_MASK;

	if (data->link.advertising & GPY2XX_ADVERTISED_10baseT_Half)
		adv |= CONST_STD_AN_ADV_TAF_XBT_HDX << STD_AN_ADV_TAF_POS;

	if (data->link.advertising & GPY2XX_ADVERTISED_10baseT_Full)
		adv |= CONST_STD_AN_ADV_TAF_XBT_FDX << STD_AN_ADV_TAF_POS;

	if (data->link.advertising & GPY2XX_ADVERTISED_100baseT_Half)
		adv |= CONST_STD_AN_ADV_TAF_DBT_HDX << STD_AN_ADV_TAF_POS;

	if (data->link.advertising & GPY2XX_ADVERTISED_100baseT_Full)
		adv |= CONST_STD_AN_ADV_TAF_DBT_FDX << STD_AN_ADV_TAF_POS;

	if (data->link.advertising & GPY2XX_ADVERTISED_Pause)
		adv |= CONST_STD_AN_ADV_TAF_PS_SYM << STD_AN_ADV_TAF_POS;

	if (data->link.advertising & GPY2XX_ADVERTISED_Asym_Pause)
		adv |= CONST_STD_AN_ADV_TAF_PS_ASYM << STD_AN_ADV_TAF_POS;

	if (adv != oldadv) {
		ret = PHY_WRITE(phy, STD_STD_AN_ADV, adv);

		if (ret < 0) {
			LOG_CRIT("ERROR: STD_AN_ADV write fails\n");
			return ret;
		}

		changed = 1;
	}

	/* 1G */
	status = PHY_READ(phy, STD_STD_STAT);

	if (status < 0) {
		LOG_CRIT("ERROR: STD_STAT read fails\n");
		return status;
	}

	if (status & STD_STAT_EXT_MASK) {
		adv = PHY_READ(phy, STD_STD_GCTRL);

		if (adv < 0) {
			LOG_CRIT("ERROR: STD_GCTRL read fails\n");
			return adv;
		}

		oldadv = adv;
		adv &= ~(STD_GCTRL_MBTHD_MASK | STD_GCTRL_MBTFD_MASK);

		if (data->link.advertising & GPY2XX_ADVERTISED_1000baseT_Half)
			adv |= 1 << STD_GCTRL_MBTHD_POS;

		if (data->link.advertising & GPY2XX_ADVERTISED_1000baseT_Full)
			adv |= 1 << STD_GCTRL_MBTFD_POS;

		if (adv != oldadv) {
			ret = PHY_WRITE(phy, STD_STD_GCTRL, adv);

			if (ret < 0) {
				LOG_CRIT("ERROR: STD_GCTRL write fails\n");
				return ret;
			}

			changed = 1;
		}
	}

	/* 2.5/5G */
	adv = PHY_READ_MMD(phy, MDIO_MMD_AN, ANEG_MGBT_AN_CTRL);

	if (adv < 0) {
		LOG_CRIT("ERROR: ANEG_MGBT_AN_CTRL read fails\n");
		return adv;
	}

	oldadv = adv;
	adv &= ~ANEG_MGBT_AN_CTRL_FR_2G5BT_MASK;
	adv &= ~ANEG_MGBT_AN_CTRL_FR_5GBT_MASK;
	adv &= ~ANEG_MGBT_AN_CTRL_AB_2G5BT_MASK;
	adv &= ~ANEG_MGBT_AN_CTRL_AB_5GBT_MASK;

	if (data->link.advertising & GPY2XX_ADVERTISED_2500baseT_Full)
		adv |= 1 << ANEG_MGBT_AN_CTRL_AB_2G5BT_POS;

	if (data->link.advertising & GPY2XX_ADVERTISED_5000baseT_Full)
		adv |= 1 << ANEG_MGBT_AN_CTRL_AB_5GBT_POS;

	if (data->link.advertising & GPY2XX_ADVERTISED_2500baseT_FR)
		adv |= 1 << ANEG_MGBT_AN_CTRL_FR_2G5BT_POS;

	if (data->link.advertising & GPY2XX_ADVERTISED_5000baseT_FR)
		adv |= 1 << ANEG_MGBT_AN_CTRL_FR_5GBT_POS;

	if (adv != oldadv) {
		ret = PHY_WRITE_MMD(phy, MDIO_MMD_AN, ANEG_MGBT_AN_CTRL, adv);

		if (ret < 0) {
			LOG_CRIT("ERROR: ANEG_MGBT_AN_CTRL write fails\n");
			return adv;
		}

		changed = 1;
	}

	ret = changed; //Klocwork fix.
	return ret;
}

int gpy2xx_config_advert(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	ret = __gpy211_config_advert(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_config_advert fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int __gpy211_setup_forced(struct gpy211_device *phy)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int ctrl1, ctrl2, ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (data->link.speed == SPEED_UNKNOWN
	    || data->link.duplex == DUPLEX_INVALID) {
		LOG_WARN("WARN: Link's Speed or Duplex unknown\n");
		return -EINVAL;
	}

	if (data->link.speed > SPEED_5000) {
		LOG_WARN("WARN: Link's Speed > 5Gbps\n");
		return -EINVAL;
	}

	/* Half duplex is supported for 10/100Mbps only */
	if (data->link.speed > SPEED_100
	    && data->link.duplex != DUPLEX_FULL) {
		LOG_WARN("WARN: Link's Speed & Duplex mismatch\n");
		return -EINVAL;
	}

	ret = PHY_READ(phy, STD_STD_CTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: STD_CTRL read fails\n");
		return ret;
	}

	ctrl1 = ret;

	if (data->link.speed <= SPEED_1000) {
		/* Disable auto-negotiation */
		ctrl1 &= STD_CTRL_LB_MASK | STD_CTRL_ISOL_MASK
			 | STD_CTRL_PD_MASK;
		data->link.pause = 0;
		data->link.asym_pause = 0;

		switch (data->link.speed) {
		case SPEED_10:
			break;

		case SPEED_100:
			ctrl1 |= 1 << STD_CTRL_SSL_POS;
			break;

		case SPEED_1000:
			ctrl1 |= 1 << STD_CTRL_SSM_POS;
			break;

		default:
			LOG_WARN("WARN: Link's Speed invalid\n");
			return -EINVAL;
		}

		/* Set duplex mode */
		if (data->link.duplex == DUPLEX_FULL)
			ctrl1 |= 1 << STD_CTRL_DPLX_POS;

		ret = PHY_WRITE(phy, STD_STD_CTRL, ctrl1);

		if (ret < 0) {
			LOG_CRIT("ERROR: STD_CTRL write fails\n");
			return ret;
		}
	} else {
		/* Full duplex only */
		ctrl1 &= STD_CTRL_SSM_MASK | STD_CTRL_SSL_MASK
			 | STD_CTRL_LB_MASK | STD_CTRL_ISOL_MASK
			 | STD_CTRL_PD_MASK;
		/* Set duplex mode */
		ctrl1 |= 1 << STD_CTRL_DPLX_POS;
		ret = PHY_WRITE(phy, STD_STD_CTRL, ctrl1);

		if (ret < 0) {
			LOG_CRIT("ERROR: STD_CTRL write fails\n");
			return ret;
		}

		ret = PHY_READ_MMD(phy, MDIO_MMD_PMAPMD, PMA_CTRL1);

		if (ret < 0) {
			LOG_CRIT("ERROR: PMA_CTRL1 read fails\n");
			return ret;
		}

		ctrl1 = ret;

		ret = PHY_READ_MMD(phy, MDIO_MMD_PMAPMD, PMA_CTL2);

		if (ret < 0) {
			LOG_CRIT("ERROR: PMA_CTRL2 read fails\n");
			return ret;
		}

		ctrl2 = ret;

		ctrl1 &= ~PMA_CTRL1_SPEED_SEL_MASK;
		ctrl1 &= ~PMA_CTRL1_SSM_MASK;
		ctrl1 &= ~PMA_CTRL1_SSL_MASK;
		ctrl2 &= ~PMA_CTL2_PMA_PMD_TYPE_SEL_MASK;

		ctrl1 |= 1 << PMA_CTRL1_SSM_POS;
		ctrl1 |= 1 << PMA_CTRL1_SSL_POS;

		if (data->link.supported & GPY2XX_SUPPORTED_5000baseT_Full
		    && data->link.speed == SPEED_5000) {
			ctrl1 |= 7 << PMA_CTRL1_SPEED_SEL_POS;
			ctrl2 |= 0x31 << PMA_CTL2_PMA_PMD_TYPE_SEL_POS;
		} else {
			ctrl1 |= 6 << PMA_CTRL1_SPEED_SEL_POS;
			ctrl2 |= 0x30 << PMA_CTL2_PMA_PMD_TYPE_SEL_POS;
		}

		ret = PHY_WRITE_MMD(phy, MDIO_MMD_PMAPMD, PMA_CTRL1, ctrl1);

		if (ret < 0) {
			LOG_CRIT("ERROR: PMA_CTRL1 write fails\n");
			return ret;
		}

		ret = PHY_WRITE_MMD(phy, MDIO_MMD_PMAPMD, PMA_CTL2, ctrl2);

		if (ret < 0) {
			LOG_CRIT("ERROR: PMA_CTRL2 write fails\n");
			return ret;
		}
	}

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_setup_forced(struct gpy211_device *phy)
{
	struct gpy211_device *data;
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	data = phy->shared_data == NULL ? phy : phy->shared_data;

	data->link.autoneg = 0;
	ret = __gpy211_setup_forced(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_setup_forced fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int __gpy211_restart_aneg(struct gpy211_device *phy)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int ctrl1, ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	ctrl1 = PHY_READ(phy, STD_STD_CTRL);

	if (ctrl1 < 0) {
		LOG_CRIT("ERROR: STD_CTRL write fails\n");
		return ctrl1;
	}

	ctrl1 |= 1 << STD_CTRL_ANEN_POS;
	ctrl1 |= 1 << STD_CTRL_ANRS_POS;

	/* Don't isolate if we are negotiating */
	ctrl1 &= ~STD_CTRL_ISOL_MASK;

	ret = PHY_WRITE(phy, STD_STD_CTRL, ctrl1);

	if (ret < 0) {
		LOG_CRIT("ERROR: STD_CTRL write fails\n");
		return ret;
	}

	if (ret == 0)
		data->link.autoneg = 1;

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_restart_aneg(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	ret = __gpy211_restart_aneg(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_restart_aneg fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_config_aneg(struct gpy211_device *phy)
{
	struct gpy211_device *data;
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	data = phy->shared_data == NULL ? phy : phy->shared_data;

	if (data->link.autoneg == 0) {
		/* If AN not set, force link speed */
		ret = __gpy211_setup_forced(phy);

		if (ret < 0) {
			LOG_CRIT("ERROR: api __gpy211_setup_forced fails\n");
		}

		goto END;
	}

	/* Configure auto-negotiation */
	ret = __gpy211_config_advert(phy);

	if (ret > 0) {
		ret = __gpy211_restart_aneg(phy);

		if (ret < 0) {
			LOG_CRIT("ERROR: api __gpy211_restart_aneg fails\n");
			goto END;
		}
	} else if (ret == 0) {
		ret = PHY_READ(phy, STD_STD_CTRL);

		if (ret < 0) {
			LOG_CRIT("ERROR: STD_CTRL read fails\n");
			goto END;
		}

		if (!(ret & STD_CTRL_ANEN_MASK) || (ret & STD_CTRL_ISOL_MASK)) {
			ret = __gpy211_restart_aneg(phy);

			if (ret < 0) {
				LOG_CRIT("ERROR: api __gpy211_restart_aneg fails\n");
				goto END;
			}
		} else
			ret = 0;
	} else {
		LOG_CRIT("ERROR: api __gpy211_config_advert fails\n");
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_aneg_done(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);
	ret = PHY_READ(phy, STD_STD_STAT);

	if (ret < 0) {
		LOG_CRIT("ERROR: STD_STAT read fails\n");
		goto END;
	}

	ret = (ret & STD_STAT_ANOK_MASK) ? 1 : 0;
END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_update_link(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	ret = __gpy211_update_link(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_update_link fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_read_status(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	ret = __gpy211_read_status(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_read_status fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int __gpy211_get_fw_info(struct gpy211_device *phy)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Get Firmware Version */
	ret = PHY_READ(phy, PHY_PHY_FWV);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_FWV read fails\n");
		return ret;
	}

	data->id.fw_major = (ret & PHY_FWV_MAJOR_MASK) >> PHY_FWV_MAJOR_POS;
	data->id.fw_minor = (ret & PHY_FWV_MINOR_MASK) >> PHY_FWV_MINOR_POS;
	data->id.fw_release = (ret & PHY_FWV_REL_MASK) ? 1 : 0;

	ret = PHY_READ(phy, PHY_PHY_STAT1);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_STAT1 read fails\n");
		return ret;
	}

	data->id.fw_memory = (ret >> 2) & 0x3;

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

int gpy2xx_read_fw_info(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	ret = __gpy211_get_fw_info(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_get_fw_info fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_test_mode_cfg(struct gpy211_device *phy,
			 enum gpy211_test_mode mode)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate Transmitter Test Mode range */
	if (mode < TEST_NOP || mode > TEST_DIST) {
		LOG_WARN("WARN: Invalid input (testTxMode) - Transmitter Test Mode\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	ret = PHY_SET_MASK_BITS(phy, STD_STD_GCTRL, STD_GCTRL_TM_MASK,
				FIELD_SET((u16)mode, STD_GCTRL_TM));

	if (ret < 0) {
		LOG_CRIT("ERROR: STD_GCTRL (TM) write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_cdiag_start(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	ret = PHY_WRITE(phy, PHY_PHY_TEST,
			(FIELD_SET((u16)TEST_CDIAG, PHY_TEST_TM) + 0x1));

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_TEST write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int __gpy211_cdiag_get_pair(struct gpy211_device *phy, int idx,
				   struct gpy211_cdiag_pair *pair)
{
	int ret;
	int j;
	u32 base = 0x400 + (0x8 * idx);
	LOG_INFO("Entering func name :- %s\n", __func__);

	for (j = 0; j < 5; j++) {
		ret = PHY_READ_MMD(phy, MDIO_MMD_VEND2, (base + j) * 2);

		if (ret < 0) {
			LOG_CRIT("ERROR: MMD_VEND2 rd of distance, state details fail\n");
			//return ret;
		} else if (ret == 0)
			break;

		pair->num_valid_result++;
		pair->results[j].distance = (u8)(ret & 0xff);
		ret = ret >> 8;

		if (ret & 0x01)
			pair->results[j].state |= 0;//CDIAG_REFLECTION; //P31GSYS-1450 fix.

		if (ret & 0x02)
			pair->results[j].state |= CDIAG_OPEN;

		if (ret & 0x04)
			pair->results[j].state |= CDIAG_SHORT;

		if (ret & 0x08)
			pair->results[j].state |= CDIAG_MATCHED;

		ret = PHY_READ_MMD(phy, MDIO_MMD_VEND2, (base + j + 0x20) * 2);

		if (ret < 0) {
			LOG_CRIT("ERROR: MMD_VEND2 rd of echo peak detected fails\n");
			return ret;
		}

		pair->results[j].peak = (s16)ret & 0xFFFF;
	}

	for (j = 0; j < 3; j++) {
		ret = PHY_READ_MMD(phy, MDIO_MMD_VEND2, (base + j + 5) * 2);

		if (ret < 0) {
			LOG_CRIT("ERROR: MMD_VEND2 rd fails for iteration %d\n", j);
			return ret;
		}

		pair->xc_pwr[j] = (s16)ret & 0xFFFF;
	}

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

int gpy2xx_cdiag_read(struct gpy211_device *phy,
		      struct gpy211_cdiag_report *report)
{
	int ret;
	int i;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || report == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	memset(report, 0, sizeof(*report));

	phy->lock(phy->lock_data);

	for (i = 0; i < 4; i++) {
		ret = __gpy211_cdiag_get_pair(phy, i, &(report->pair[i]));

		if (ret < 0) {
			LOG_CRIT("ERROR: api __gpy211_cdiag_get_pair fails for iteration % d\n", i);
			goto END;
		}
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_abist_start(struct gpy211_device *phy,
		       struct gpy211_abist_param *param)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || param == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate ABIS Test flags range */
	if (!(param->test >= ABIST_ANALOG_IPV_0 &&
	      param->test <= ABIST_DC_2500BT_MAX_NVE)) {
		LOG_WARN("WARN: Invalid input (txTestMode) - ABIS Test flags\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	ret = PHY_READ(phy, PHY_PHY_TEST);

	if (ret >= 0) {
		FIELD_REPLACE(ret, TEST_ABIST, PHY_TEST_TM);

		if (param->restart)
			FIELD_REPLACE(ret, 1, PHY_TEST_ABRET);
		else
			FIELD_REPLACE(ret, 0, PHY_TEST_ABRET);

		if (param->uart_report)
			FIELD_REPLACE(ret, 1, PHY_TEST_ABUART);
		else
			FIELD_REPLACE(ret, 0, PHY_TEST_ABUART);

		// Populate ABIST_SEL, ABIST_OPT
		ret |= param->test;
		ret = PHY_WRITE(phy, PHY_PHY_TEST, ret);

		if (ret < 0) {
			LOG_CRIT("ERROR: PHY_TEST write fails\n");
			goto END;
		}
	} else {
		LOG_CRIT("ERROR: PHY_TEST read fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int __gpy211_abist_get_pair(struct gpy211_device *phy, int idx,
				   struct gpy211_abist_pair *pair)
{
	int ret;
	u32 base = 0x400 + (0x40 * idx);
	u8 data[64] = {0};
	int j;
	LOG_INFO("Entering func name :- %s\n", __func__);

	// TODO: need double check endianess
	for (j = 0; j < 60; j += 2) {
		ret = PHY_READ_MMD(phy, MDIO_MMD_VEND2, (base + j) * 2);

		if (ret < 0) {
			LOG_CRIT("ERROR: MMD_VEND2 rd of mag n other details fail\n");
			return ret;
		}

		data[j] = (u8)(ret >> 8);
		data[j + 1] = (u8)(ret & 0xFF);
	}

	for (j = 0x3C; j <= 0x3F; j++) {
		ret = PHY_READ_MMD(phy, MDIO_MMD_VEND2, (base + j) * 2);

		if (data[j] != 0x4D) {
			LOG_CRIT("ERROR: mmd vend-2 rd of reserved	values != 0x4D\n");
			//return -EAGAIN;
		}
	}

	pair->icn_gmax.mag_max = data[0];
	pair->icn_gmax.mag_min = data[1];
	pair->icn_gmax.mag_avg = data[2];
	pair->icn_gmax.mag_dc = data[3];
	pair->icn_gmin.mag_max = data[4];
	pair->icn_gmin.mag_min = data[5];
	pair->icn_gmin.mag_avg = data[6];
	pair->icn_gmin.mag_dc = data[7];

	for (j = 0; j < 6; j++)
		pair->agc_hyb.agc_pwr[j] = data[j + 0x08];

	pair->agc_hyb.agc_mean = data[0x0E];
	pair->agc_hyb.agc_std = data[0x0F];

	for (j = 0; j < 6; j++)
		pair->agc_nohyb.agc_pwr[j] = data[j + 0x10];

	pair->agc_nohyb.agc_mean = data[0x16];
	pair->agc_nohyb.agc_std = data[0x17];

	pair->nohyb_10bt.dc_mag = data[0x18];
	pair->nohyb_10bt.nyq_mag = data[0x19];
	pair->nohyb_10bt.k1_mag = data[0x1A];
	pair->nohyb_10bt.k2_mag = data[0x1B];
	pair->nohyb_10bt.k3_mag = data[0x1C];
	pair->nohyb_10bt.k4_mag = data[0x1D];

	pair->nohyb_100bt.dc_mag = data[0x1E];
	pair->nohyb_100bt.nyq_mag = data[0x1F];
	pair->nohyb_100bt.k1_mag = data[0x20];
	pair->nohyb_100bt.k2_mag = data[0x21];
	pair->nohyb_100bt.k3_mag = data[0x22];
	pair->nohyb_100bt.k4_mag = data[0x23];

	pair->hyb_1000bt.dc_mag = data[0x24];
	pair->hyb_1000bt.nyq_mag = data[0x25];
	pair->hyb_1000bt.k1_mag = data[0x26];
	pair->hyb_1000bt.k2_mag = data[0x27];
	pair->hyb_1000bt.k3_mag = data[0x28];
	pair->hyb_1000bt.k4_mag = data[0x29];

	pair->nohyb_1000bt.dc_mag = data[0x2A];
	pair->nohyb_1000bt.nyq_mag = data[0x2B];
	pair->nohyb_1000bt.k1_mag = data[0x2C];
	pair->nohyb_1000bt.k2_mag = data[0x2D];
	pair->nohyb_1000bt.k3_mag = data[0x2E];
	pair->nohyb_1000bt.k4_mag = data[0x2F];

	pair->hyb_2500bt.dc_mag = data[0x30];
	pair->hyb_2500bt.nyq_mag = data[0x31];
	pair->hyb_2500bt.k1_mag = data[0x32];
	pair->hyb_2500bt.k2_mag = data[0x33];
	pair->hyb_2500bt.k3_mag = data[0x34];
	pair->hyb_2500bt.k4_mag = data[0x35];

	pair->nohyb_2500bt.dc_mag = data[0x36];
	pair->nohyb_2500bt.nyq_mag = data[0x37];
	pair->nohyb_2500bt.k1_mag = data[0x38];
	pair->nohyb_2500bt.k2_mag = data[0x39];
	pair->nohyb_2500bt.k3_mag = data[0x3A];
	pair->nohyb_2500bt.k4_mag = data[0x3B];

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

int gpy2xx_abist_read(struct gpy211_device *phy,
		      struct gpy211_abist_report *report)
{
	int ret;
	int i;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || report == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	memset(report, 0, sizeof(*report));

	phy->lock(phy->lock_data);

	for (i = 0; i < 4; i++) {
		ret = __gpy211_abist_get_pair(phy, i, &(report->pair[i]));

		if (ret < 0) {
			LOG_CRIT("ERROR: api __gpy211_abist_get_pair fails\n");
			goto END;
		}
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_loopback_cfg(struct gpy211_device *phy,
			enum gpy211_test_loop tloop)
{
	int ret, data = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate Loopback Test modes range */
	if (!(tloop >= TLOOP_OFF && tloop <= TLOOP_NETLI)) {
		LOG_WARN("WARN: Invalid input (loopbackMode) - Loopback Test mode\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	if (tloop == TLOOP_NETLI) {
		ret = PHY_SET_BIT(phy, STD_STD_CTRL, STD_CTRL_LB_POS);
	} else {
		ret = PHY_CLR_BIT(phy, STD_STD_CTRL, STD_CTRL_LB_POS);
	}

	if (ret < 0) {
		LOG_CRIT("ERROR: STD_CTRL write fails\n");
		goto END;
	} else if (tloop == TLOOP_NETLI) {
		goto END;
	}

	/* tloop != TLOOP_NETLI, set TLOOP and restart aneg */
	data = FIELD_SET((u16)tloop, PHY_CTL1_TLOOP);

	ret = PHY_SET_MASK_BITS(phy, PHY_PHY_CTL1, PHY_CTL1_TLOOP_MASK, data);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_CTL1 write fails\n");
		goto END;
	}

	gpy2xx_restart_aneg(phy);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_errcnt_cfg(struct gpy211_device *phy,
		      enum gpy211_errcnt_event event)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate Error or Event mode range */
	if (!(event >= ERRCNT_RXERR && event <= ERRCNT_TTL)) {
		LOG_WARN("WARN: Invalid input (errCountMode) - Error or Event mode\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	ret = PHY_SET_MASK_BITS(phy, PHY_PHY_ERRCNT, PHY_ERRCNT_SEL_MASK,
				FIELD_SET((u16)event, PHY_ERRCNT_SEL));

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_ERRCNT (SEL) write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_errcnt_read(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);
	ret = PHY_READ(phy, PHY_PHY_ERRCNT);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_ERRCNT read fails\n");
		goto END;
	}

	if (ret >= 0)
		ret = FIELD_GET(ret, PHY_ERRCNT_COUNT);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_pcs_status_read(struct gpy211_device *phy,
			   struct gpy211_pcs_status *status)
{
	int ret;
	u32 regaddr[2] = {
		PCS_2G5_STAT1,
		PCS_2G5_STAT2,
	};
	u16 data[2];
	size_t i;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || status == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	memset(status, 0, sizeof(struct gpy211_pcs_status));

	phy->lock(phy->lock_data);

	for (i = 0; i < ARRAY_SIZE(data); i++) {
		ret = PHY_READ_MMD(phy, MDIO_MMD_PCS, regaddr[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: %s read fails for iteration\n",
				 (i == 0) ? "PCS_STAT1" : "PCS_STAT2");
			goto END;
		}

		data[i] = (u16)ret;
	}

	if (data[0] & PCS_2G5_STAT1_PCS2G5_LINK_STATUS_MASK)
		status->rcv_link_up = 1; // DOUBT - is it not bit 2 in PCS_STAT1?

	if (data[1] & PCS_2G5_STAT1_PCS2G5_HI_BER_MASK) // DOUBT - is it not bit 14 in data[1]?
		status->high_ber = 1;

	if (data[1] & PCS_2G5_STAT1_PCS2G5_BLO_LOCK_MASK) // DOUBT - is it not bit 15 in data[1]?
		status->block_lock = 1;

	status->errored_block = FIELD_GET(data[1], PCS_2G5_STAT2_ERRED_BLK);
	status->ber = FIELD_GET(data[1], PCS_2G5_STAT2_BER);
	ret = 0;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int __gpy211_wol_reg_wr(struct gpy211_device *phy, u32 *reg,
			       u8 *data)
{
	int ret;
	u16 wd;
	int i;
	LOG_INFO("Entering func name :- %s\n", __func__);

	for (i = 0; i < 3; i++) {
		wd = (u16)((data[0] << 8) | data[1]);
		ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND2, *reg, wd);

		if (ret < 0) {
			LOG_CRIT("ERROR: MMD_VEND2 WOL write fails for iteration %d\n", i);
			return ret;
		}

		data += 2;
		reg++;
	}

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

int gpy2xx_wol_cfg(struct gpy211_device *phy, struct gpy211_wolinfo *wol)
{
	struct gpy211_device *data;
	int ret = 0, ret1;
	u32 mac_reg[3] = {
		VPSPEC2_WOL_AD45,
		VPSPEC2_WOL_AD23,
		VPSPEC2_WOL_AD01
	};
	u32 pwd_reg[3] = {
		VPSPEC2_WOL_PW45,
		VPSPEC2_WOL_PW23,
		VPSPEC2_WOL_PW01
	};
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || wol == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate WOL flags range */
	if (wol->wolopts < GPY211_WOL_FLAG_MIN ||
	    wol->wolopts > GPY211_WOL_FLAG_MAX) {
		LOG_WARN("WARN: Invalid input (wolOptions) - WOL flags\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	data = phy->shared_data == NULL ? phy : phy->shared_data;

	wol->wolopts &= data->wol_supported;

	if (wol->wolopts == 0) {
		/* disable wake-on-lan */
		ret = PHY_CLR_MMD_BIT(phy, MDIO_MMD_VEND2, VPSPEC2_WOL_CTL,
				      VPSPEC2_WOL_CTL_EN_POS);

		if (ret < 0) {
			LOG_CRIT("ERROR: VPSPEC2_WOL_CTL (EN) clear fails\n");
			//return ret1;
		}

		// Disable MDIO.PHY.IMASK.WOL interrupt
		ret1 = PHY_CLR_BIT(phy, PHY_PHY_IMASK, PHY_IMASK_WOL_MASK);

		if (ret1 < 0) {
			LOG_CRIT("ERROR: PHY_IMASK WOL flag clear fails\n");
			goto END;
		}

		if (ret == 0)
			ret = ret1;
	} else if (wol->wolopts & WAKE_MAGIC) {
		/* set MAC on which to wake-on-lan  */
		ret = __gpy211_wol_reg_wr(phy, mac_reg, wol->mac);

		if (ret < 0) {
			LOG_CRIT("ERROR: api __gpy211_wol_reg_wr mac fails\n");
			goto END;
		}

		if (wol->wolopts & WAKE_MAGICSECURE) {
			/* enable secure magic */
			ret = __gpy211_wol_reg_wr(phy, pwd_reg, wol->sopass);

			if (ret < 0) {
				LOG_CRIT("ERROR: api __gpy211_wol_reg_wr passworead fails\n");
				goto END;
			}

			/* enable secure-on password */
			ret = PHY_SET_MMD_BIT(phy, MDIO_MMD_VEND2, VPSPEC2_WOL_CTL,
					      VPSPEC2_WOL_CTL_SPWD_EN_POS);

			if (ret < 0) {
				LOG_CRIT("ERROR: VPSPEC2_WOL_CTL (SPWD_EN) set fails\n");
				goto END;
			}
		}

		// Enable MDIO.PHY.IMASK.WOL interrupt
		ret = PHY_SET_BIT(phy, PHY_PHY_IMASK, PHY_IMASK_WOL_POS);

		if (ret < 0) {
			LOG_CRIT("ERROR: PHY_IMASK WOL flag set fails\n");
			goto END;
		}

		/* enable wake-on-lan functionality */
		ret1 = PHY_SET_MMD_BIT(phy, MDIO_MMD_VEND2, VPSPEC2_WOL_CTL,
				       VPSPEC2_WOL_CTL_EN_POS);

		if (ret1 < 0) {
			LOG_CRIT("ERROR: VPSPEC2_WOL_CTL (EN) set fails\n");
			//return ret;
		}

		if (ret == 0)
			ret = ret1;
	} else
		ret = -EINVAL;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int __gpy211_wol_reg_rd(struct gpy211_device *phy, u32 *reg,
			       u8 *data)
{
	int ret;
	int i;
	LOG_INFO("Entering func name :- %s\n", __func__);

	for (i = 0; i < 3; i++) {
		ret = PHY_READ_MMD(phy, MDIO_MMD_VEND2, *reg);

		if (ret < 0) {
			LOG_CRIT("ERROR: MMD_VEND2 WOL read fails for iteration %d\n", i);
			return ret;
		}

		data[1] = ret & 0xFF;
		data[0] = (ret >> 8) & 0xFF;

		data += 2;
		reg++;
	}

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

int gpy2xx_wol_get(struct gpy211_device *phy, struct gpy211_wolinfo *wol)
{
	int ret, ret1;
	u32 mac_reg[3] = {
		VPSPEC2_WOL_AD45,
		VPSPEC2_WOL_AD23,
		VPSPEC2_WOL_AD01
	};
	u32 pwd_reg[3] = {
		VPSPEC2_WOL_PW45,
		VPSPEC2_WOL_PW23,
		VPSPEC2_WOL_PW01
	};
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || wol == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	memset(wol, 0, sizeof(struct gpy211_wolinfo));

	phy->lock(phy->lock_data);

	ret = PHY_READ_MMD(phy, MDIO_MMD_VEND2, VPSPEC2_WOL_CTL);

	if (ret < 0) {
		LOG_CRIT("ERROR: VPSPEC2_WOL_CTL read fails\n");
		goto END;
	}

	if (ret & VPSPEC2_WOL_CTL_EN_MASK) {
		wol->wolopts |= WAKE_MAGIC;
		ret1 = __gpy211_wol_reg_rd(phy, mac_reg, wol->mac);

		if (ret1 < 0) {
			LOG_CRIT("ERROR: api __gpy211_wol_reg_rd mac fails\n");
			//goto END;
		}

		if (ret & VPSPEC2_WOL_CTL_SPWD_EN_MASK) {
			wol->wolopts |= WAKE_MAGICSECURE;
			ret = __gpy211_wol_reg_rd(phy, pwd_reg, wol->sopass);

			if (ret < 0) {
				LOG_CRIT("ERROR: api __gpy211_wol_reg_rd passworead fails\n");
				//goto END;
			}
		} else {
			LOG_CRIT("WARN: SPWD is disabled\n");
			ret = 0;
		}

		if (ret1 < 0)
			ret = ret1;
	} else {
		LOG_CRIT("WARN: WOL is disabled\n");
		ret = 0;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ads_cfg(struct gpy211_device *phy, struct gpy211_ads_ctrl *ads)
{
	int ret;
	u16 _ds_setting;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || ads == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate ADS (Link's Auto Down Speed) adv enable */
	if (ads->no_nrg_rst < ADS_NO_ENERGY_ADV_DIS || ads->no_nrg_rst  > ADS_NO_ENERGY_ADV_EN) {
		LOG_WARN("WARN: Invalid input of RESET (boolean) to advertise all speeds.\n");
		return -EINVAL;
	}

	/* Validate ADS downshift enable */
	if (ads->downshift_en < ADS_NBT_DOWNSHIFT_DIS || ads->downshift_en > ADS_NBT_DOWNSHIFT_EN) {
		LOG_WARN("WARN: Invalid input of DOWNSHIFT (boolean) enable.\n");
		return -EINVAL;
	}

	/* Validate ADS downshift threshold */
	if (ads->downshift_thr > ADS_DOWNSHIFT_THR_MAX) {
		LOG_WARN("WARN: Invalid input of DOWNSHIFT threshold (0-15).\n");
		return -EINVAL;
	}

	/* Validate ADS force reset enable */
	if (ads->force_rst < ADS_FORCE_RST_DIS || ads->force_rst > ADS_FORCE_RST_EN) {
		LOG_WARN("WARN: Invalid input of FORCE_RST (boolean) enable.\n");
		return -EINVAL;
	}

	/* Validate ADS Timer (to Reset the Downshift process) */
	if (ads->nrg_rst_cnt > ADS_NRG_RST_CNT_MAX) {
		LOG_WARN("WARN: Invalid input of TIMER value (0-255) to reset downshift process.\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);
	/* Read NBT_DS_CTRL  */
	ret = PHY_READ_MMD(phy,  MDIO_MMD_VEND1, VSPEC1_NBT_DS_CTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_NBT_DS_CTRL read fails\n");
		goto END;
	}

	_ds_setting = (u16) ret;
	/* update NBT_DS_CTRL */
	FIELD_REPLACE(_ds_setting, ads->no_nrg_rst, VSPEC1_NBT_DS_CTRL_NO_NRG_RST);
	FIELD_REPLACE(_ds_setting, ads->downshift_en, VSPEC1_NBT_DS_CTRL_DOWNSHIFT_EN);
	FIELD_REPLACE(_ds_setting, ads->downshift_thr, VSPEC1_NBT_DS_CTRL_DOWNSHIFT_THR);
	FIELD_REPLACE(_ds_setting, ads->force_rst, VSPEC1_NBT_DS_CTRL_FORCE_RST);
	FIELD_REPLACE(_ds_setting, ads->nrg_rst_cnt, VSPEC1_NBT_DS_CTRL_NRG_RST_CNT);

	/* Write NBT_DS_CTRL*/
	ret = PHY_WRITE_MMD(phy,  MDIO_MMD_VEND1, VSPEC1_NBT_DS_CTRL, _ds_setting);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_NBT_DS_CTRL write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ads_get(struct gpy211_device *phy, struct gpy211_ads_sta *ads)
{
	int ret;
	u16 _ads_ctrl;
	u16 _ads_sta;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || ads == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);
	/* Read NBT_DS_CTRL */

	ret = PHY_READ_MMD(phy,  MDIO_MMD_VEND1, VSPEC1_NBT_DS_CTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_NBT_DS_CTRL read fails\n");
		goto END;
	}

	_ads_ctrl = (u16) ret;

	ads->ads_ctrl.no_nrg_rst = FIELD_GET(_ads_ctrl, VSPEC1_NBT_DS_CTRL_NO_NRG_RST);
	ads->ads_ctrl.downshift_en = FIELD_GET(_ads_ctrl, VSPEC1_NBT_DS_CTRL_DOWNSHIFT_EN);
	ads->ads_ctrl.downshift_thr = FIELD_GET(_ads_ctrl, VSPEC1_NBT_DS_CTRL_DOWNSHIFT_THR);
	ads->ads_ctrl.force_rst = FIELD_GET(_ads_ctrl, VSPEC1_NBT_DS_CTRL_FORCE_RST);
	ads->ads_ctrl.nrg_rst_cnt = FIELD_GET(_ads_ctrl, VSPEC1_NBT_DS_CTRL_NRG_RST_CNT);

	/* Read NBT_DS_STA */

	ret = PHY_READ_MMD(phy,  MDIO_MMD_VEND1, VSPEC1_NBT_DS_STA);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_NBT_DS_STA read fails\n");
		goto END;
	}

	_ads_sta = (u16) ret;

	ads->downshift_cnt = FIELD_GET(_ads_sta, VSPEC1_NBT_DS_STA_DOWNSHIFT_CNT);
	ads->downshift_2G5 = FIELD_GET(_ads_sta, VSPEC1_NBT_DS_STA_DOWNSHIFT_2G5);
	ads->downshift_1G = FIELD_GET(_ads_sta, VSPEC1_NBT_DS_STA_DOWNSHIFT_1G);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ads_detected(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);
	ret = PHY_READ(phy, PHY_PHY_STAT1);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_STAT1 (LSADS) read fails\n");
		goto END;
	}

	if (ret >= 0)
		ret = FIELD_GET(ret, PHY_STAT1_LSADS) ? 1 : 0;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ulp_cfg(struct gpy211_device *phy, struct gpy211_ulp_ctrl *ulp)
{
	int ret;
	u16 _ulp_ctrl;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || ulp == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate ULP boolean variables */
	if (ulp->ulp_en > 1 || ulp->ulp_sta_block > 1) {
		LOG_WARN("WARN: Invalid input of ULP (boolean) controls.\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	/* Read PHY_CTL2  */
	ret = PHY_READ(phy, PHY_PHY_CTL2);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_CTL2 read fails\n");
		goto END;
	}

	_ulp_ctrl = ret;
	FIELD_REPLACE(_ulp_ctrl, ulp->ulp_en, PHY_CTL2_ULP);
	FIELD_REPLACE(_ulp_ctrl, ulp->ulp_sta_block, PHY_CTL2_ULP_STA_BLOCK);

	/* Write PHY_CTL2*/
	ret = PHY_WRITE(phy, PHY_PHY_CTL2, _ulp_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_PHY_CTL2 write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ulp_get(struct gpy211_device *phy, struct gpy211_ulp_ctrl *ulp)
{
	int ret;
	u16 _ulp_ctrl;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || ulp == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);

	/* Read PHY_CTL2  */
	ret = PHY_READ(phy, PHY_PHY_CTL2);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_CTL2 read fails\n");
		goto END;
	}

	_ulp_ctrl = ret;
	ulp->ulp_en = FIELD_GET(_ulp_ctrl, PHY_CTL2_ULP);
	ulp->ulp_sta_block = FIELD_GET(_ulp_ctrl, PHY_CTL2_ULP_STA_BLOCK);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_extin_mask(struct gpy211_device *phy,
		      struct gpy211_phy_extin *extin)
{
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
#ifdef SMDIO_FOR_PHY

	/* Validate Interrupt ID range */
	if (extin->id < EXT_INT_ID_0 || extin->id > EXT_INT_ID_1) {
		LOG_WARN("WARN: Invalid input (extIntId) - Interrupt ID\n");
		return -EINVAL;
	}

	/* Validate Pin's output characteristics */
	if (extin->op_char < MDIO_INT_POL_LOW ||
	    extin->op_char > MDIO_INT_POL_HIGH) {
		LOG_WARN("WARN: Invalid input (opChar) - Pin's OP characteristics\n");
		return -EINVAL;
	}

#endif

	/* Validate Interrupt Trigger range */
	if (!(extin->imask_istat >= EXTIN_PHY_EVENT_MIN &&
	      extin->imask_istat <= EXTIN_PHY_EVENT_MAX)) {
		LOG_WARN("WARN: Invalid input (imaskIstat) - Interrupt Trigger\n");
		return -EINVAL;
	}

	if (!(extin->im2_imask_istat >= EXTIN_IM2_EVENT_MIN &&
	      extin->im2_imask_istat <= EXTIN_IM2_EVENT_MAX)) {
		LOG_WARN("WARN: Invalid input (im2ImaskIstat) - Interrupt Trigger\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);
	/* Enable given interrupts */
	ret = PHY_WRITE(phy, PHY_PHY_IMASK, extin->imask_istat);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_IMASK write fails\n");
		goto END;
	}

	/* Enable given interrupts in IM2 module */
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, 0x22, extin->im2_imask_istat); //VSPEC1_IMASK

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_IMASK write fails\n");
		goto END;
	}

#ifdef SMDIO_FOR_PHY

	/* Check if EXINT is configured as Input or Output */
	// TODO
	//1.Output
	/* Configure the active 'level' of EXINT output pin */
	if (extin->id == EXT_INT_ID_0) {
		ret = SMDIO_SET_MASK_BITS(phy,
					  ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_EIU_EXIN_CONF,
					  ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT0_MASK,
					  FIELD_SET(extin->op_char, ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT0));
	} else {
		ret = SMDIO_SET_MASK_BITS(phy,
					  ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_EIU_EXIN_CONF,
					  ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT1_MASK,
					  FIELD_SET(extin->op_char, ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT1));
	}

	if (ret < 0) {
		LOG_CRIT("ERROR: %s write fails\n",
			 (extin->id == EXT_INT_ID_0) ? "EXIN_EOUT0" : "EXIN_EOUT1");
		goto END;
	}

#endif

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_extin_get(struct gpy211_device *phy,
		     struct gpy211_phy_extin *extin)
{
#ifdef SMDIO_FOR_PHY
	u16 val;
#endif
	s32 ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
#ifdef SMDIO_FOR_PHY

	/* Validate Interrupt ID range */
	if (extin->id < EXT_INT_ID_0 || extin->id > EXT_INT_ID_1) {
		LOG_WARN("WARN: Invalid input (extIntId) - Interrupt ID\n");
		return -EINVAL;
	}

#endif

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* Get interrupt's status or mask */
	if (((extin->gpio_flags) & 0xFF) == EXT_INT_IMASK) {
		ret = PHY_READ(phy, PHY_PHY_IMASK);
	} else if (((extin->gpio_flags) & 0xFF) == EXT_INT_ISTAT) {
		ret = PHY_READ(phy, PHY_PHY_ISTAT);
	} else if (((extin->gpio_flags) & 0xFF) == EXT_INT_IM2_IMASK) {
		ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, 0x22);
	} else if (((extin->gpio_flags) & 0xFF) == EXT_INT_IM2_ISTAT) {
		ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, 0x24);
	}

	if (ret < 0) {
		LOG_CRIT("ERROR: %s read fails\n",
			 (extin->gpio_flags & EXT_INT_ISTAT) ? "PHY_ISTAT" : "PHY_IMASK");
		goto END;
	}

	if (((extin->gpio_flags) & 0xFF) <= EXT_INT_ISTAT)
		extin->imask_istat = (u16)ret;
	else
		extin->im2_imask_istat = (u16)ret;

#ifdef SMDIO_FOR_PHY
	/* Check if EXINT is configured as Input or Output */
	// TODO
	//1.Output
	/* Get the polarity of EXINT output pin */

	ret = SMDIO_READ(phy, ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_EIU_EXIN_CONF);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIU_EXIN_CONF read fails\n");
		goto END;
	}

	val = (u16)ret;

	/* Get the Level detection of EXINT output pin */
	if (extin->id == EXT_INT_ID_0) {
		extin->op_char = FIELD_GET(val, ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT0);
	} else {
		extin->op_char = FIELD_GET(val, ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT1);
	}

#endif

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

#if defined(EN_GMAC_DEBUG_ACCESS) && EN_GMAC_DEBUG_ACCESS
int gpy2xx_extin_clr(struct gpy211_device *phy,
		     struct gpy211_phy_extin *extin)
{
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate Interrupt Trigger range */
	if (!(extin->imask_istat >= EXTIN_PHY_EVENT_MIN &&
	      extin->imask_istat <= EXTIN_PHY_EVENT_MAX)) {
		LOG_WARN("WARN: Invalid input (imaskIstat) - Interrupt Status\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);
	/* Enable given interrupts */
	ret = PHY_WRITE(phy, PHY_PHY_ISTAT, extin->imask_istat);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_IMASK write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}
#endif
#if defined(EN_LED_TOP_CFG) && EN_LED_TOP_CFG
int gpy2xx_led_top_cfg(struct gpy211_device *phy,
		       struct gpy211_led_gcfg *cfg)
{
	u16 led_cfg;
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate Slow Blinking Frequency range */
	if (!(cfg->slow_blink_freq >= LED_BFRQ_MIN &&
	      cfg->slow_blink_freq <= LED_BFRQ_MAX)) {
		LOG_WARN("WARN: Invalid input (slowBlinkFreq) - Slow Blink Frequency\n");
		return -EINVAL;
	}

	/* Validate Fast Blinking Frequency range */
	if (!(cfg->fast_blink_freq >= LED_BFRQ_MIN &&
	      cfg->fast_blink_freq <= LED_BFRQ_MAX)) {
		LOG_WARN("WARN: Invalid input (fastBlinkFreq) - Fast Blink Frequency\n");
		return -EINVAL;
	}

	/* Validate Complex Scan range */
	if (!(cfg->complex_scan >= LED_SCAN_SRC_MIN &&
	      cfg->complex_scan <= LED_SCAN_SRC_MAX)) {
		LOG_WARN("WARN: Invalid input (complexScan) - Complex Scan\n");
		return -EINVAL;
	}

	/* Validate Inverse Scan range */
	if (!(cfg->inverse_scan >= LED_SCAN_SRC_MIN &&
	      cfg->inverse_scan <= LED_SCAN_SRC_MAX)) {
		LOG_WARN("WARN: Invalid input (inverseScan) - Inverse Scan\n");
		return -EINVAL;
	}

	/* Validate Complex Blink range */
	if (!(cfg->complex_blink >= LED_SCAN_SRC_MIN &&
	      cfg->complex_blink <= LED_SCAN_SRC_MAX)) {
		LOG_WARN("WARN: Invalid input (complexBlink) - Complex Blink\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* Set to enable Integrated function of LEDs  */
	// DOUBT - How to unset if we wish to?
	ret = PHY_SET_MASK_BITS(phy, PHY_PHY_LED, 0x0F00, 0x0F00);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_LED read fails \n");
		goto END;
	}

	/* Read LED configuration */
	ret = PHY_READ_MMD(phy,  MDIO_MMD_VEND1, VSPEC1_LEDC);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_LEDC read fails\n");
		goto END;
	}

	led_cfg = (u16)ret;

	/* Modify LED configuration */
	/* Set complex-scan function */
	FIELD_REPLACE(led_cfg, cfg->complex_scan, VSPEC1_LEDC_SCAN);
	/* Set inverse complex-scan function */
	FIELD_REPLACE(led_cfg, cfg->inverse_scan, VSPEC1_LEDC_NACS);
	/* Set complex-blink function */
	FIELD_REPLACE(led_cfg, cfg->complex_blink, VSPEC1_LEDC_CBLINK);
	/* Set slow-blink frequency */
	FIELD_REPLACE(led_cfg, cfg->slow_blink_freq, VSPEC1_LEDC_SBF);
	/* Set fast-blink frequency */
	FIELD_REPLACE(led_cfg, cfg->fast_blink_freq, VSPEC1_LEDC_FBF);

	/* Write LED configuration */
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_LEDC, led_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_LEDC write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_led_top_get(struct gpy211_device *phy,
		       struct gpy211_led_gcfg *cfg)
{
	u16 led_cfg;
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);
	/* Read LED configuration */
	ret = PHY_READ_MMD(phy,  MDIO_MMD_VEND1, VSPEC1_LEDC);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_LEDC read fails\n");
		goto END;
	}

	led_cfg = (u16)ret;

	/* Get complex-scan function */
	cfg->complex_scan = FIELD_GET(led_cfg, VSPEC1_LEDC_SCAN);
	/* Get inverse complex-scan function */
	cfg->inverse_scan = FIELD_GET(led_cfg, VSPEC1_LEDC_NACS);
	/* Get complex-blink function */
	cfg->complex_blink = FIELD_GET(led_cfg, VSPEC1_LEDC_CBLINK);
	/* Get slow-blink frequency */
	cfg->slow_blink_freq = FIELD_GET(led_cfg, VSPEC1_LEDC_SBF);
	/* Get fast-blink frequency */
	cfg->fast_blink_freq = FIELD_GET(led_cfg, VSPEC1_LEDC_FBF);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}
#endif /* EN_LED_TOP_CFG */
int gpy2xx_led_if_cfg(struct gpy211_device *phy,
		      struct gpy211_led_cfg *cfg)
{
	u16 led_cfg;
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate LED ID range */
	if (cfg->id < LED_ID_MIN || cfg->id > LED_ID_MAX) {
		LOG_WARN("WARN: Invalid input (ledId) - LED ID\n");
		return -EINVAL;
	}

	/* Validate Pulse ID range */
	if (cfg->pulse > LED_PULSE_MAX) {
		LOG_WARN("WARN: Invalid input (pulseFlags) - Pulse Flags\n");
		return -EINVAL;
	}

	/* Validate Color Mode range */
	if (!(cfg->color_mode >= LED_CM_MIN && cfg->color_mode <= LED_CM_MAX)) {
		LOG_WARN("WARN: Invalid input (colorMode) - Color Mode\n");
		return -EINVAL;
	}

	/* Validate PHY blinking trigger range */
	if (!(cfg->const_on >= LED_BSRC_MIN && cfg->const_on <= LED_BSRC_MAX)) {
		LOG_WARN("WARN: Invalid input (constantlyOn) - Blinking Trigger Src\n");
		return -EINVAL;
	}

	/* Validate PHY blinking trigger range */
	if (!(cfg->slow_blink_src >= LED_BSRC_MIN &&
	      cfg->slow_blink_src <= LED_BSRC_MAX)) {
		LOG_WARN("WARN: Invalid input (slowBlinkSrc) - Blinking Trigger Src\n");
		return -EINVAL;
	}

	/* Validate PHY blinking trigger range */
	if (!(cfg->fast_blink_src >= LED_BSRC_MIN &&
	      cfg->fast_blink_src <= LED_BSRC_MAX)) {
		LOG_WARN("WARN: Invalid input (fastBlinkSrc) - Blinking Trigger Src\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* Set to enable Integrated function of LEDs  */
	ret = PHY_READ(phy, PHY_PHY_LED);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_LED read fails \n");
		goto END;
	}

	led_cfg = ret;
	/* Disable LEDxDA */
	led_cfg = (led_cfg & (~(1 << cfg->id)));
	/* Enable LEDxEN */
	led_cfg = (led_cfg | (1 << (cfg->id + 8)));
	/* Set given LED's color-mode */
	led_cfg = (led_cfg & (~(1 << (cfg->id + 12))));
	led_cfg = (led_cfg | (cfg->color_mode << (cfg->id + 12)));

	ret = PHY_WRITE(phy, PHY_PHY_LED, led_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_LED write fails \n");
		goto END;
	}

	/* Set given LED's config */
	/* Read LED configuration */
	ret = PHY_READ_MMD(phy,  MDIO_MMD_VEND1, (VSPEC1_LED0 + ((cfg->id) * 2)));

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_LEDx read fails for LED = %d\n", cfg->id);
		goto END;
	}

	led_cfg = (u16)ret;

	/* Modify LED configuration */
	/* Set given LED's fast-blink source */
	FIELD_REPLACE(led_cfg, cfg->fast_blink_src, VSPEC1_LED0_BLINKF);
	/* Set given LED's slow-blink source */
	FIELD_REPLACE(led_cfg, cfg->slow_blink_src, VSPEC1_LED0_BLINKS);
	/* Set given LED's constantly on (i.e., no blink) source */
	FIELD_REPLACE(led_cfg, cfg->const_on, VSPEC1_LED0_CON);
	/* Set given LED's Pulse source */
	FIELD_REPLACE(led_cfg, cfg->pulse, VSPEC1_LED0_PULSE);

	/* Write LED configuration */
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, (VSPEC1_LED0 + ((cfg->id) * 2)),
			    led_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_LEDx write fails for LED = %d\n", cfg->id);
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_led_if_get(struct gpy211_device *phy,
		      struct gpy211_led_cfg *cfg)
{
	u16 led_cfg;
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate LED ID range */
	if (cfg->id < LED_ID_MIN || cfg->id > LED_ID_MAX) {
		LOG_WARN("WARN: Invalid input (ledId) - LED ID\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* Get LEDs color-mode */
	ret = PHY_READ(phy, PHY_PHY_LED);

	if (ret < 0) {
		LOG_CRIT("ERROR: PHY_LED read fails \n");
		goto END;
	}

	led_cfg = ret;
	/* Get given LED's color-mode */
	cfg->color_mode = (led_cfg >> (cfg->id + 12)) & 0x1;

	/* Read given LED's config */
	ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, (VSPEC1_LED0 + ((cfg->id) * 2)));

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_LEDx read fails for LED = %d\n", cfg->id);
		goto END;
	}

	led_cfg = (u16)ret;

	/* Get given LED's fast-blink source */
	cfg->fast_blink_src = FIELD_GET(led_cfg, VSPEC1_LED0_BLINKF);
	/* Get given LED's slow-blink source */
	cfg->slow_blink_src = FIELD_GET(led_cfg, VSPEC1_LED0_BLINKS);
	/* Get given LED's constantly on (i.e., no blink) source */
	cfg->const_on = FIELD_GET(led_cfg, VSPEC1_LED0_CON);
	/* Get given LED's Pulse source */
	cfg->pulse = FIELD_GET(led_cfg, VSPEC1_LED0_PULSE);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_synce_cfg(struct gpy211_device *phy,
		     struct gpy211_synce *synce_cfg)
{
	u16 _synce_cfg;
	u16 _synce_gpio_dir;
	u16 _synce_gpio_altsel0;
	u16 _synce_gpio_altsel1;
	u16 _sysce_master_mode;
	u16 _sysce_restart;
	u32 _read_data;
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || synce_cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate Ref Clock's ref i/p frequency range */
	if (!(synce_cfg->synce_refclk >= SYNCE_REFCLK_MIN &&
	      synce_cfg->synce_refclk <= SYNCE_REFCLK_MAX)) {
		LOG_WARN("WARN: Invalid input (synceClocl) - Ref Clock's i/p selection\n");
		return -EINVAL;
	}

	/* Validate data rate */
	if (!(synce_cfg->data_rate >= SYNCE_1G &&
	      synce_cfg->data_rate <= SYNCE_2G5)) {
		LOG_WARN("WARN: Invalid data rate\n");
		return -EINVAL;
	}

	/* Validate GPC select */
	if (!(synce_cfg->gpc_sel >= SYNCE_GPC1 &&
	      synce_cfg->gpc_sel <= SYNCE_GPC2)) {
		LOG_WARN("WARN: Invalid input GPC selection\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* Disable EEE for 2.5G */
	ret = PHY_CLR_MMD_BIT(phy, MDIO_MMD_AN, ANEG_EEE_AN_ADV2,
			      ANEG_EEE_AN_ADV2_EEE2G5_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: Disable EEE for 2.5G fails\n");
		goto END;
	}

	/* Disable EEE for 1G */
	ret = PHY_CLR_MMD_BIT(phy, MDIO_MMD_AN, ANEG_EEE_AN_ADV1,
			      ANEG_EEE_AN_ADV1_EEE_1000BT_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: Disable EEE for 1000BT fails\n");
		goto END;
	}

	/* Set data rate to 1G or 2.5G */
	if (synce_cfg->data_rate == SYNCE_1G) {
		ret = PHY_CLR_MMD_BIT(phy, MDIO_MMD_AN, ANEG_MGBT_AN_CTRL, ANEG_MGBT_AN_CTRL_AB_2G5BT_POS);
	} else {
		ret = PHY_SET_MMD_BIT(phy, MDIO_MMD_AN, ANEG_MGBT_AN_CTRL, ANEG_MGBT_AN_CTRL_AB_2G5BT_POS);
	}

	if (ret < 0) {
		LOG_CRIT("ERROR: ANEG_MGBT_AN_CTRL modify fails\n");
		goto END;
	}

	/* Read PM SyncE configuration */
	ret = PHY_READ_MMD(phy,  MDIO_MMD_VEND1, VSPEC1_PM_CTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: PM_CTRL read fails\n");
		goto END;
	}

	_synce_cfg = (u16)ret;

	/* Modify SyncE configuration */
	/* Enable SyncE & set clksel */
	if (synce_cfg->synce_enable == 0) {
		FIELD_REPLACE(_synce_cfg, CONST_VSPEC1_PM_CTRL_SYNCE_EN_DISABLE, VSPEC1_PM_CTRL_SYNCE_EN);
	} else {
		FIELD_REPLACE(_synce_cfg, CONST_VSPEC1_PM_CTRL_SYNCE_EN_ENABLE, VSPEC1_PM_CTRL_SYNCE_EN);
	}

	FIELD_REPLACE(_synce_cfg, synce_cfg->synce_refclk, VSPEC1_PM_CTRL_SYNCE_CLK);

	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_PM_CTRL, _synce_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: PM_CTRL write fails\n");
		goto END;
	}

	/* Read CGU PDI */
#if defined(P31G_B0) && P31G_B0
	ret = PHY_MBOX_HWRD(phy, CGU_PDI_MODULE_BASE + CGU_PDI_SYNCE_CONF, &_read_data);
#elif defined(P34X_A0) && P34X_A0
	ret = PHY_MBOX_HWRD(phy, SLICE_CGU_PDI_REGISTERS_MODULE_BASE + SLICE_CGU_PDI_SYNCE_CONF, &_read_data);
#endif
	_synce_cfg = (u16) _read_data;

	if (ret < 0) {
		LOG_CRIT("ERROR: Read CGU PDI CFG fails\n");
		goto END;
	}

	/* Read GPIO DIRECTION */
	ret = PHY_MBOX_HWRD(phy, GPIO_PDI_REGISTERS_MODULE_BASE + GPIO_PDI_REGISTERS_GPIO_DIR, &_read_data);
	_synce_gpio_dir = (u16) _read_data;

	if (ret < 0) {
		LOG_CRIT("ERROR: Read GPIO PDI DIR fails\n");
		goto END;
	}

	/* Read GPIO ALTSEL0 */
	ret = PHY_MBOX_HWRD(phy, GPIO_PDI_REGISTERS_MODULE_BASE + GPIO_PDI_REGISTERS_GPIO_ALTSEL0, &_read_data);
	_synce_gpio_altsel0 = (u16) _read_data;

	if (ret < 0) {
		LOG_CRIT("ERROR: Read GPIO PDI ALTSEL0 fails\n");
		goto END;
	}

	/* Read GPIO ALTSEL1 */
	ret = PHY_MBOX_HWRD(phy, GPIO_PDI_REGISTERS_MODULE_BASE + GPIO_PDI_REGISTERS_GPIO_ALTSEL1, &_read_data);
	_synce_gpio_altsel1 = (u16) _read_data;

	if (ret < 0) {
		LOG_CRIT("ERROR: Read GPIO PDI ALTSEL1 fails\n");
		goto END;
	}


	/* Modify CGU_PDI_SYNCE_CONF_SCLK_SEL */
	_sysce_master_mode = (CONST_STD_GCTRL_MSEN_ENABLED << STD_GCTRL_MSEN_POS) + (CONST_STD_GCTRL_MBTFD_ENABLED << STD_GCTRL_MBTFD_POS) + (CONST_STD_GCTRL_MBTHD_ENABLED << STD_GCTRL_MBTHD_POS);

	if (synce_cfg->master_sel == SYNCE_MASTER) {
		_synce_gpio_dir = _synce_gpio_dir & ~((u16)0x0001u << (GPIO_PIN10_SYNCE_FUN + synce_cfg->gpc_sel));
		_sysce_master_mode = _sysce_master_mode + (CONST_STD_GCTRL_MS_MASTER << STD_GCTRL_MS_POS);
	} else {
		_synce_gpio_dir = _synce_gpio_dir | ((u16)0x0001u << (GPIO_PIN10_SYNCE_FUN + synce_cfg->gpc_sel));
	}

#if defined(P31G_B0) && P31G_B0
	FIELD_REPLACE(_synce_cfg, (synce_cfg->gpc_sel + 1), CGU_PDI_SYNCE_CONF_SCLK_SEL);
#elif defined(P34X_A0) && P34X_A0
	FIELD_REPLACE(_synce_cfg, (synce_cfg->gpc_sel + 1), SLICE_CGU_PDI_SYNCE_CONF_SCLK_SEL);
#endif
	_synce_gpio_altsel0 = _synce_gpio_altsel0 & ~((u16)0x0001u << (GPIO_PIN10_SYNCE_FUN + synce_cfg->gpc_sel));
	_synce_gpio_altsel1 = _synce_gpio_altsel1 | ((u16)0x0001u << (GPIO_PIN10_SYNCE_FUN + synce_cfg->gpc_sel));

	/* Write GPIO DIRECTION */
	ret = PHY_MBOX_HWWR(phy, GPIO_PDI_REGISTERS_MODULE_BASE + GPIO_PDI_REGISTERS_GPIO_DIR, _synce_gpio_dir);

	if (ret < 0) {
		LOG_CRIT("ERROR: Write GPIO PDI DIR fails\n");
		goto END;
	}

	/* Write GPIO ALTSEL0 */
	ret = PHY_MBOX_HWWR(phy, GPIO_PDI_REGISTERS_MODULE_BASE + GPIO_PDI_REGISTERS_GPIO_ALTSEL0, _synce_gpio_altsel0);

	if (ret < 0) {
		LOG_CRIT("ERROR: Write GPIO PDI ALTSEL0 fails\n");
		goto END;
	}

	/* Write GPIO ALTSEL1 */
	ret = PHY_MBOX_HWWR(phy, GPIO_PDI_REGISTERS_MODULE_BASE + GPIO_PDI_REGISTERS_GPIO_ALTSEL1, _synce_gpio_altsel1);

	if (ret < 0) {
		LOG_CRIT("ERROR: Write GPIO PDI ALTSEL1 fails\n");
		goto END;
	}

	/* Write STD_GCTRL */
	ret = PHY_WRITE(phy, STD_GCTRL, _sysce_master_mode);

	if (ret < 0) {
		LOG_CRIT("ERROR: Write STD_GCTRL fails\n");
		goto END;
	}

	/* Write CGU PDI CONFIG */
#if defined(P31G_B0) && P31G_B0
	ret = PHY_MBOX_HWWR(phy, CGU_PDI_MODULE_BASE + CGU_PDI_SYNCE_CONF, _synce_cfg);
#elif defined(P34X_A0) && P34X_A0
	ret = PHY_MBOX_HWWR(phy, SLICE_CGU_PDI_REGISTERS_MODULE_BASE + SLICE_CGU_PDI_SYNCE_CONF, _synce_cfg);
#endif

	if (ret < 0) {
		LOG_CRIT("ERROR: Write CGU PDI CFG fails\n");
		goto END;
	}

	/* Write restart */
	_sysce_restart = 0x1200;

	ret = PHY_WRITE(phy, STD_CTRL, _sysce_restart);

	if (ret < 0) {
		LOG_CRIT("ERROR: Write Restart Auto-Negotiation fails\n");
		goto END;
	}


END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_synce_get(struct gpy211_device *phy,
		     struct gpy211_synce *synce_cfg)
{
	u16 _synce_cfg;
	u16 _sysce_master_mode;
	u16 _gpc_sel;
	u32 _read_info;
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || synce_cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* Read SyncE configuration */
	ret = PHY_READ_MMD(phy,  MDIO_MMD_VEND1, VSPEC1_PM_CTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1 PM CTRL read fails\n");
		goto END;
	}

	_synce_cfg = (u16)ret;

	/* Get synce_en state */
	synce_cfg->synce_enable = FIELD_GET(_synce_cfg, VSPEC1_PM_CTRL_SYNCE_EN);
	/* Get synce_refclk value */
	synce_cfg->synce_refclk = FIELD_GET(_synce_cfg, VSPEC1_PM_CTRL_SYNCE_CLK);


	/* Read GCTRL mode*/
	ret = PHY_READ(phy, STD_GCTRL);
	_sysce_master_mode = ret;

	if (ret < 0) {
		LOG_CRIT("ERROR: STD_GCTRL read fails\n");
		goto END;
	}

	/* Get master mode */
	synce_cfg->master_sel = FIELD_GET(_sysce_master_mode, STD_GCTRL_MS);

	ret = PHY_READ_MMD(phy,  MDIO_MMD_AN, ANEG_MGBT_AN_CTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: ANEG_MGBT_AN_CTRL read fails\n");
		goto END;
	}

	synce_cfg->data_rate = ((u16)ret & ANEG_MGBT_AN_CTRL_AB_2G5BT_MASK) > 0 ? SYNCE_2G5 : SYNCE_1G;


	/* Read GPC_Sel  */
#if defined(P31G_B0) && P31G_B0
	ret = PHY_MBOX_HWRD(phy, CGU_PDI_MODULE_BASE + CGU_PDI_SYNCE_CONF, &_read_info);
#elif defined(P34X_A0) && P34X_A0
	ret = PHY_MBOX_HWRD(phy, SLICE_CGU_PDI_REGISTERS_MODULE_BASE + SLICE_CGU_PDI_SYNCE_CONF, &_read_info);
#endif

	if (ret < 0) {
		LOG_CRIT("ERROR: CGU_PDI_SYNCE_CONF read fails\n");
		goto END;
	}

	_gpc_sel = (u16) _read_info;
#if defined(P31G_B0) && P31G_B0
	synce_cfg->gpc_sel = FIELD_GET(_gpc_sel, CGU_PDI_SYNCE_CONF_SCLK_SEL) - 1;
#elif defined(P34X_A0) && P34X_A0
	synce_cfg->gpc_sel = FIELD_GET(_gpc_sel, SLICE_CGU_PDI_SYNCE_CONF_SCLK_SEL) - 1;
#endif

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int __gpy211_sgmii_restart_aneg(struct gpy211_device *phy)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int ret;
	int ctrl;

	ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL read fails\n");
		return ret;
	}

	ctrl = ret;
	FIELD_REPLACE(ctrl, CONST_VSPEC1_SGMII_CTRL_ANEN_ON, VSPEC1_SGMII_CTRL_ANEN);
	FIELD_REPLACE(ctrl, CONST_VSPEC1_SGMII_CTRL_ANRS_RESTART, VSPEC1_SGMII_CTRL_ANRS);
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL, ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL write fails\n");
	}

	if (ret == 0)
		data->link.autoneg = 1;

	return ret;
}

int gpy2xx_sgmii_restart_aneg(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);
	ret = __gpy211_sgmii_restart_aneg(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_sgmii_restart_aneg fail\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int __gpy211_sgmii_linkcfgdir_set(struct gpy211_device *phy,
		struct gpy211_sgmii *sgmii)
{
	int ret, ctrl;

	ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL read fails\n");
		return ret;
	}

	ctrl = ret;

	if (sgmii->linkcfg_dir == SGMII_LINKCFG_SGMII) {
		FIELD_REPLACE(ctrl, CONST_VSPEC1_SGMII_CTRL_CFGDIR_SGMII, VSPEC1_SGMII_CTRL_CFGDIR);
	} else {
		FIELD_REPLACE(ctrl, CONST_VSPEC1_SGMII_CTRL_CFGDIR_TPI, VSPEC1_SGMII_CTRL_CFGDIR);
	}

	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL, ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL write fails\n");
	}

	return ret;
}

static int __gpy211_sgmii_setup_forced(struct gpy211_device *phy,
				       struct gpy211_sgmii *sgmii)
{
	int ret, ctrl;

	printf("__gpy211_sgmii_setup_forced, speed: %d\n", sgmii->link.speed);

	ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL read fails\n");
		return ret;
	}

	ctrl = ret;
	FIELD_REPLACE(ctrl, CONST_VSPEC1_SGMII_CTRL_ANEN_OFF, VSPEC1_SGMII_CTRL_ANEN);

	if (sgmii->linkcfg_dir != SGMII_LINKCFG_TPI) {
		switch (sgmii->link.speed) {
		case SPEED_2500:
			FIELD_REPLACE(ctrl, 1, VSPEC1_SGMII_CTRL_SSM);
			FIELD_REPLACE(ctrl, 1, VSPEC1_SGMII_CTRL_SSL);
			break;

		case SPEED_1000:
		default:
			printf("1g speed\n");
			FIELD_REPLACE(ctrl, 1, VSPEC1_SGMII_CTRL_SSM);
			FIELD_REPLACE(ctrl, 0, VSPEC1_SGMII_CTRL_SSL);
			break;

		case SPEED_100:
			FIELD_REPLACE(ctrl, 0, VSPEC1_SGMII_CTRL_SSM);
			FIELD_REPLACE(ctrl, 1, VSPEC1_SGMII_CTRL_SSL);
			break;

		case SPEED_10:
			FIELD_REPLACE(ctrl, 0, VSPEC1_SGMII_CTRL_SSM);
			FIELD_REPLACE(ctrl, 0, VSPEC1_SGMII_CTRL_SSL);
			break;
		};

		if (sgmii->link.duplex == DUPLEX_FULL)
			FIELD_REPLACE(ctrl, CONST_VSPEC1_SGMII_CTRL_DPLX_ON, VSPEC1_SGMII_CTRL_DPLX);
		else
			FIELD_REPLACE(ctrl, CONST_VSPEC1_SGMII_CTRL_DPLX_OFF, VSPEC1_SGMII_CTRL_DPLX);
	}

	FIELD_REPLACE(ctrl, sgmii->link.fixed2g5, VSPEC1_SGMII_CTRL_SGMII_FIXED2G5);

	printf("reg: %x\n", ctrl);

	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL, ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL write fails\n");
	}

	return ret;
}

static int __gpy211_sgmii_config_advert(struct gpy211_device *phy,
					struct gpy211_sgmii *sgmii)
{
	int ret, ctrl;
	int ctrl_mask = 0, ctrl_set = 0;

	ctrl_mask = VSPEC1_SGMII_CTRL_ANMODE_MASK | VSPEC1_SGMII_CTRL_EEE_CAP_MASK;

	switch (sgmii->aneg_mode) {
	case SGMII_ANEG_1000BX:
		FIELD_REPLACE(ctrl_set, CONST_VSPEC1_SGMII_CTRL_ANMODE_AN_1000BX, VSPEC1_SGMII_CTRL_ANMODE);
		break;

	case SGMII_ANEG_CISCO_PHY:
	default:
		FIELD_REPLACE(ctrl_set, CONST_VSPEC1_SGMII_CTRL_ANMODE_AN_CIS_PHY, VSPEC1_SGMII_CTRL_ANMODE);
		break;

	case SGMII_ANEG_CISCO_MAC:
		FIELD_REPLACE(ctrl_set, CONST_VSPEC1_SGMII_CTRL_ANMODE_AN_CIS_MAC, VSPEC1_SGMII_CTRL_ANMODE);
		break;
	}

	if (sgmii->eee_enable)
		FIELD_REPLACE(ctrl_set, CONST_VSPEC1_SGMII_CTRL_EEE_CAP_ON, VSPEC1_SGMII_CTRL_EEE_CAP);
	else
		FIELD_REPLACE(ctrl_set, CONST_VSPEC1_SGMII_CTRL_EEE_CAP_OFF, VSPEC1_SGMII_CTRL_EEE_CAP);

	/* Seems nothing to configure for speed and duplex */

	ctrl = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL);

	if (ctrl < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL read fails\n");
		return ctrl;
	}

	if ((ctrl & ctrl_mask) == ctrl_set)
		return 0;

	ctrl &= ~ctrl_mask;
	ctrl |= ctrl_set;
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL, ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL write fail\n");
	}

	return ret < 0 ? ret : 1;
}

static int __gpy211_sgmii_config_aneg(struct gpy211_device *phy,
				      struct gpy211_sgmii *sgmii)
{
	int ret, ctrl;

	printf("__gpy211_sgmii_config_aneg, speed: %d\n", sgmii->link.speed);
	ret = __gpy211_sgmii_linkcfgdir_set(phy, sgmii);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_sgmii_linkcfgdir_set fail\n");
		return ret;
	}

	if (sgmii->link.autoneg == 0) {
		printf("autoneg == 0\n");
		ret = __gpy211_sgmii_setup_forced(phy, sgmii);

		if (ret < 0) {
			LOG_CRIT("ERROR: api __gpy211_sgmii_setup_forced fail\n");
		}

		return ret;
	}

	ret = __gpy211_sgmii_config_advert(phy, sgmii);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_sgmii_config_advert fail\n");
		return ret;
	} else if (ret > 0) {
		ret = __gpy211_sgmii_restart_aneg(phy);

		if (ret < 0) {
			LOG_CRIT("ERROR: api __gpy211_sgmii_restart_aneg fail\n");
		}

		return ret;
	}

	ctrl = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL);

	if (ctrl < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL read fails\n");
		return ctrl;
	}

	if (FIELD_GET(ctrl, VSPEC1_SGMII_CTRL_ANRS) != CONST_VSPEC1_SGMII_CTRL_ANRS_RESTART) {
		ret = __gpy211_sgmii_restart_aneg(phy);

		if (ret < 0) {
			LOG_CRIT("ERROR: api __gpy211_sgmii_restart_aneg fail\n");
		}

		return ret;
	} else
		return 0;
}

int gpy2xx_sgmii_config_aneg(struct gpy211_device *phy,
			     struct gpy211_sgmii *sgmii)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sgmii == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SGMII Link Configuration Direction range */
	if (!(sgmii->linkcfg_dir >= SGMII_LINKCFG_TPI &&
	      sgmii->linkcfg_dir <= SGMII_LINKCFG_SGMII)) {
		LOG_WARN("WARN: Invalid input (linkcfg_dir) - SGMII Link Config Direction\n");
		return -EINVAL;
	}

	/* Validate SGMII Auto-negotiation Mode range */
	if (!(sgmii->aneg_mode >= SGMII_ANEG_1000BX &&
	      sgmii->aneg_mode <= SGMII_ANEG_CISCO_MAC)) {
		LOG_WARN("WARN: Invalid input (aneg_mode) - SGMII Auto-negotiation Mode\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);
	ret = __gpy211_sgmii_config_aneg(phy, sgmii);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_sgmii_config_aneg fail\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_sgmii_aneg_done(struct gpy211_device *phy)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);
	ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_STAT);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_STAT read fails\n");
		goto END;
	}

	ret = FIELD_GET(ret, VSPEC1_SGMII_STAT_ANOK) == CONST_VSPEC1_SGMII_STAT_ANOK_COMPLETED ? 1 : 0;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int __gpy211_sgmii_read_status(struct gpy211_device *phy,
				      struct gpy211_sgmii *sgmii)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int ret;
	int ctrl, stat;
	enum gpy211_sgmii_aneg_mode mode[] = {
		SGMII_ANEG_CISCO_PHY,
		SGMII_ANEG_1000BX,
		SGMII_ANEG_CISCO_PHY,
		SGMII_ANEG_CISCO_MAC
	};
	int speed[] = {SPEED_10, SPEED_100, SPEED_1000, SPEED_2500,
		       SPEED_2500, SPEED_UNKNOWN, SPEED_UNKNOWN, SPEED_UNKNOWN
		      };

	ctrl = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL);

	if (ctrl < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL read fails\n");
		return ctrl;
	}

	stat = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_STAT);

	if (stat < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_STAT read fails\n");
		return stat;
	}

	if (FIELD_GET(stat, VSPEC1_SGMII_STAT_LS) == CONST_VSPEC1_SGMII_STAT_LS_ACTIVE)
		sgmii->link.link = 1;
	else
		sgmii->link.link = 0;

	if (FIELD_GET(ctrl, VSPEC1_SGMII_CTRL_CFGDIR) == CONST_VSPEC1_SGMII_CTRL_CFGDIR_TPI)
		sgmii->linkcfg_dir = SGMII_LINKCFG_TPI;
	else
		sgmii->linkcfg_dir = SGMII_LINKCFG_SGMII;

	if (FIELD_GET(ctrl, VSPEC1_SGMII_CTRL_ANEN) == CONST_VSPEC1_SGMII_CTRL_ANEN_OFF)
		sgmii->link.autoneg = 0;
	else
		sgmii->link.autoneg = 1;

	sgmii->link.fixed2g5 = FIELD_GET(ctrl, VSPEC1_SGMII_CTRL_SGMII_FIXED2G5);

	sgmii->aneg_mode = mode[FIELD_GET(ctrl, VSPEC1_SGMII_CTRL_ANMODE)];

	sgmii->eee_enable = 0;

	if (sgmii->aneg_mode == CONST_VSPEC1_SGMII_CTRL_ANMODE_AN_CIS_PHY)
		sgmii->eee_enable = FIELD_GET(ctrl, VSPEC1_SGMII_CTRL_EEE_CAP) == CONST_VSPEC1_SGMII_CTRL_EEE_CAP_ON ? 1 : 0;

	sgmii->link.speed = SPEED_UNKNOWN;
	sgmii->link.supported = 0;

	if (sgmii->link.autoneg) {
		sgmii->link.speed = speed[FIELD_GET(stat, VSPEC1_SGMII_STAT_DR)];
	} else if (sgmii->linkcfg_dir == SGMII_LINKCFG_TPI) {
		ret = PHY_READ(phy, PHY_PHY_MIISTAT);

		if (ret < 0) {
			LOG_CRIT("ERROR: PHY_MIISTAT read fails\n");
			return ret;
		}

		sgmii->link.speed = speed[FIELD_GET(ret, PHY_MIISTAT_SPEED)];

		if (sgmii->link.speed == CONST_PHY_MIISTAT_SPEED_ANEG)
			sgmii->link.speed = SPEED_UNKNOWN;

		if (FIELD_GET(ret, PHY_MIISTAT_DPX) == CONST_PHY_MIISTAT_DPX_FDX)
			sgmii->link.duplex = DUPLEX_FULL;
		else
			sgmii->link.duplex = DUPLEX_HALF;
	} else {
		int ssl;

		ssl = FIELD_GET(ctrl, VSPEC1_SGMII_CTRL_SSL);
		ssl |= FIELD_GET(ctrl, VSPEC1_SGMII_CTRL_SSM) << 1;
		sgmii->link.speed = speed[ssl];

		if (FIELD_GET(ctrl, VSPEC1_SGMII_CTRL_DPLX) == CONST_VSPEC1_SGMII_CTRL_DPLX_OFF)
			sgmii->link.duplex = DUPLEX_HALF;
		else
			sgmii->link.duplex = DUPLEX_FULL;
	}

	if (stat & VSPEC1_SGMII_STAT_ANAB_MASK)
		data->link.supported |= GPY2XX_SUPPORTED_Autoneg;

	return 0;
}

int gpy2xx_sgmii_read_status(struct gpy211_device *phy,
			     struct gpy211_sgmii *sgmii)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sgmii == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);
	ret = __gpy211_sgmii_read_status(phy, sgmii);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_sgmii_read_status fail\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int __gpy211_sgmii_opmode(struct gpy211_device *phy,
				 enum gpy211_sgmii_operation mode)
{
	int i, ret;
	int set = 0, clr = 0, ctrl = 0;

	switch (mode) {
	case SGMII_OP_NORMAL:
		set |= CONST_VSPEC1_SGMII_CTRL_RST_NORM << VSPEC1_SGMII_CTRL_RST_POS;
		FIELD_REPLACE(set, CONST_VSPEC1_SGMII_CTRL_LB_OFF, VSPEC1_SGMII_CTRL_LB);
		FIELD_REPLACE(set, CONST_VSPEC1_SGMII_CTRL_PD_OFF, VSPEC1_SGMII_CTRL_PD);
		break;

	case SGMII_OP_DOWN:
		set |= CONST_VSPEC1_SGMII_CTRL_RST_NORM << VSPEC1_SGMII_CTRL_RST_POS;
		FIELD_REPLACE(set, CONST_VSPEC1_SGMII_CTRL_LB_OFF, VSPEC1_SGMII_CTRL_LB);
		FIELD_REPLACE(set, CONST_VSPEC1_SGMII_CTRL_PD_ON, VSPEC1_SGMII_CTRL_PD);
		break;

	case SGMII_OP_LOOPBACK:
		set |= CONST_VSPEC1_SGMII_CTRL_RST_NORM << VSPEC1_SGMII_CTRL_RST_POS;
		FIELD_REPLACE(set, CONST_VSPEC1_SGMII_CTRL_LB_ON, VSPEC1_SGMII_CTRL_LB);
		FIELD_REPLACE(set, CONST_VSPEC1_SGMII_CTRL_PD_OFF, VSPEC1_SGMII_CTRL_PD);
		break;

	case SGMII_OP_RESET:
		ret = PHY_SET_MMD_BIT(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL,
				      VSPEC1_SGMII_CTRL_RST_POS);

		if (ret < 0) {
			LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL (RST) set fails\n");
			return ret;
		}

		for (i = 0; i < 30; i++) {
			ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL);

			if (ret < 0) {
				LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL read fails\n");
				return ret;
			}

			ctrl = ret & VSPEC1_SGMII_CTRL_RST_MASK;

			if (!ctrl)
				return 0;

			udelay(10);
		}

		if (ctrl) {
			LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL Reset is still in RST state\n");
			return -EIO;
		} else
			return 0;

	default:
		return -EINVAL;
	}

	ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL read fails\n");
		return ret;
	}

	ctrl = ret;
	clr = VSPEC1_SGMII_CTRL_RST_MASK | VSPEC1_SGMII_CTRL_LB_MASK |
	      VSPEC1_SGMII_CTRL_PD_MASK;

	ctrl &= ~clr;
	ctrl |= set;

	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_SGMII_CTRL, ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: VSPEC1_SGMII_CTRL write fails\n");
	}

	return ret;
}

int gpy2xx_sgmii_opmode(struct gpy211_device *phy,
			enum gpy211_sgmii_operation mode)
{
	int ret;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SGMII Operation Mode range */
	if (!(mode >= SGMII_OP_NORMAL &&
	      mode <= SGMII_OP_RESET)) {
		LOG_WARN("WARN: Invalid input (mode) - SGMII Operation Mode\n");
		return -EINVAL;
	}

	phy->lock(phy->lock_data);
	ret = __gpy211_sgmii_opmode(phy, mode);

	if (ret < 0) {
		LOG_CRIT("ERROR: api __gpy211_sgmii_opmode fail\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_pvt_get(struct gpy211_device *phy, struct gpy211_pvt *pvt)
{
	struct {
		unsigned int data;
		int temp;
	} static const cnv_tbl[] = {
		{0, -52}, {3, -51}, {6, -50}, {9, -49},
		{12, -48}, {16, -47}, {19, -46}, {22, -45},
		{26, -44}, {29, -43}, {33, -42}, {36, -41},
		{39, -40}, {43, -39}, {46, -38}, {50, -37},
		{53, -36}, {57, -35}, {60, -34}, {64, -33},
		{67, -32}, {71, -31}, {74, -30}, {78, -29},
		{81, -28}, {85, -27}, {89, -26}, {92, -25},
		{96, -24}, {99, -23}, {103, -22}, {107, -21},
		{111, -20}, {114, -19}, {118, -18}, {122, -17},
		{126, -16}, {129, -15}, {133, -14}, {137, -13},
		{141, -12}, {145, -11}, {149, -10}, {152, -9},
		{156, -8}, {160, -7}, {164, -6}, {168, -5},
		{172, -4}, {176, -3}, {180, -2}, {184, -1},
		{188, 0}, {193, 1}, {197, 2}, {201, 3},
		{205, 4}, {209, 5}, {213, 6}, {217, 7},
		{222, 8}, {226, 9}, {230, 10}, {234, 11},
		{239, 12}, {243, 13}, {247, 14}, {252, 15},
		{256, 16}, {261, 17}, {265, 18}, {270, 19},
		{274, 20}, {279, 21}, {283, 22}, {288, 23},
		{292, 24}, {297, 25}, {301, 26}, {306, 27},
		{311, 28}, {315, 29}, {320, 30}, {325, 31},
		{330, 32}, {334, 33}, {339, 34}, {344, 35},
		{349, 36}, {354, 37}, {359, 38}, {364, 39},
		{369, 40}, {374, 41}, {379, 42}, {384, 43},
		{389, 44}, {394, 45}, {399, 46}, {404, 47},
		{409, 48}, {414, 49}, {420, 50}, {425, 51},
		{430, 52}, {436, 53}, {441, 54}, {446, 55},
		{452, 56}, {457, 57}, {463, 58}, {468, 59},
		{474, 60}, {479, 61}, {485, 62}, {490, 63},
		{496, 64}, {502, 65}, {507, 66}, {513, 67},
		{519, 68}, {525, 69}, {530, 70}, {536, 71},
		{542, 72}, {548, 73}, {554, 74}, {560, 75},
		{566, 76}, {572, 77}, {578, 78}, {584, 79},
		{591, 80}, {597, 81}, {603, 82}, {609, 83},
		{616, 84}, {622, 85}, {628, 86}, {635, 87},
		{641, 88}, {648, 89}, {654, 90}, {661, 91},
		{667, 92}, {674, 93}, {680, 94}, {687, 95},
		{694, 96}, {701, 97}, {708, 98}, {714, 99},
		{721, 100}, {728, 101}, {735, 102}, {742, 103},
		{749, 104}, {756, 105}, {764, 106}, {771, 107},
		{778, 108}, {785, 109}, {793, 110}, {800, 111},
		{807, 112}, {815, 113}, {822, 114}, {830, 115},
		{838, 116}, {845, 117}, {853, 118}, {861, 119},
		{869, 120}, {876, 121}, {884, 122}, {892, 123},
		{900, 124}, {908, 125}, {917, 126}, {925, 127},
		{933, 128}, {941, 129}, {950, 130}, {958, 131},
		{967, 132}, {975, 133}, {984, 134}, {993, 135},
		{1002, 136}, {1010, 137}, {1019, 138},
	};

	int ret = -EIO;
	//unsigned int temp_mode;
	unsigned int pvt_data;
	unsigned int i, retry = 100;
	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* Sensor data */
	do {
		ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_TEMP_STA);

		if (ret < 0) {
			LOG_CRIT("ERROR: VSPEC1_TEMP_STA read fails\n");
			goto END;
		}
	} while ((--retry > 0) && (!(ret & VSPEC1_TEMP_STA_TEMP_DATA_MASK)));

	pvt_data = (unsigned int)ret & VSPEC1_TEMP_STA_TEMP_DATA_MASK;

	for (i = 0; i < ARRAY_SIZE(cnv_tbl) && pvt_data >= cnv_tbl[i].data; i++)
		pvt->temperature = cnv_tbl[i].temp;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_fw_frw_init(struct gpy211_device *phy, u32 timeout)
{
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	if (timeout > ((u32)(~0) / 2)) {
		LOG_WARN("WARN: timeout (%u) overflow\n", timeout);
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_CMD, 0x800);

	if (ret < 0) {
		LOG_CRIT("ERROR: Entering fast firmware download mode fails\n");
		goto END;
	}

	if (timeout == 0) {
		ret = 0;
		goto END;
	}

	timeout *= 2;

	do {
		udelay(500);
		ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_DATA_HIGH);

		if (ret < 0) {
			LOG_CRIT("ERROR: Reading erase status fails\n");
			goto END;
		}

		timeout--;
	} while (!(ret & 0x8000) && timeout > 0);

	if (timeout <= 0) {
		LOG_CRIT("ERROR: Erase timeout\n");
		ret = -EIO;
		goto END;
	}

	ret = 0;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_fw_fwr_page(struct gpy211_device *phy, u8 buf[256], u32 timeout)
{
	int ret = -EINVAL;
	int size;
	u8 *p;
	u16 data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || buf == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	if (timeout > ((u32)(~0) / 10)) {
		LOG_WARN("WARN: timeout (%u) overflow\n", timeout);
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = PHY_READ_MMD(phy, MDIO_MMD_VEND2, 0x0f01 * 2);

	if (ret < 0) {
		LOG_CRIT("ERROR: Reading 0xf01 fails\n");
		goto END;
	}

	data = ret & 0xFFFE;
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND2, 0x0f01 * 2, data);

	if (ret < 0) {
		LOG_CRIT("ERROR: Write	0xf01 fails\n");
		goto END;
	}

	for (size = 0, p = buf; size < 256; size += 4, p += 4) {
		ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_DATA, ((u32)p[0] << 8) | p[1]);

		if (ret < 0) {
			LOG_CRIT("ERROR: Write fails\n");
			goto END;
		}

		ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_CMD, ((u32)p[2] << 8) | p[3]);

		if (ret < 0) {
			LOG_CRIT("ERROR: Write fails\n");
			goto END;
		}
	}

	data |= 1;
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND2, 0x0f01 * 2, data);

	if (ret < 0) {
		LOG_CRIT("ERROR: Write	0xf01 fails\n");
		goto END;
	}

	if (timeout == 0) {
		ret = 0;
		goto END;
	}

	timeout *= 10;

	do {
		udelay(100);
		ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_DATA_HIGH);

		if (ret < 0) {
			LOG_CRIT("ERROR: Reading page program status fails\n");
			goto END;
		}

		timeout--;
	} while (!(ret == 0x8000) && (timeout > 0));

	if (timeout <= 0) {
		LOG_CRIT("ERROR: Page program timeout\n");
		ret = -EIO;
		goto END;
	}

	ret = 0;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_fw_fwr_status(struct gpy211_device *phy)
{
	int ret = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_DATA_HIGH);

	if (ret < 0) {
		LOG_CRIT("ERROR: Reading page program status fails\n");
		goto END;
	}

	ret = ret & 0x8000;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_fw_frw_uninit(struct gpy211_device *phy)
{
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = PHY_WRITE(phy, STD_STD_CTRL, STD_CTRL_RST_MASK);

	if (ret < 0) {
		LOG_CRIT("ERROR: Reset fails\n");
		goto END;
	}

	ret = 0;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int __is_mbox_busy(struct gpy211_device *phy, u8 action)
{
	int retCode = 0;

	do {
		u32 value = 0;
		u32 busyRetry = MAX_BUSY_RETRY;

		do {
			retCode = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_CMD);

			if (retCode < 0)
				return retCode;

			value = retCode;
			value = value & VSPEC1_MBOX_CMD_READY_MASK;
		} while ((!value) && (--busyRetry));

		if ((!value && !busyRetry)) {
			LOG_CRIT("\nERROR: MBOX busy for too long @ ");
			LOG_CRIT("%s %d\n", __func__, __LINE__);

			if (RETURN_FROM_FUNC == action)
				return -1;

			retCode = -1;
		} else {
			retCode = PHY_CLR_MMD_BIT(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_CMD, VSPEC1_MBOX_CMD_READY_POS);

			if (retCode < 0)
				return retCode;
		}
	} while (0);

	return retCode;
}

/* IP_MDIO read */
int gpy2xx_mbox_read16(struct gpy211_device *phy, u32 regaddr, u32 *data)
{
	int ret;
	u32 _mbox_cmd = 0;

	u16 data_low = 0;
	u16 addr_high = regaddr >> 16;
	u16 addr_low = regaddr & 0xFFFF;

	//Address to read
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_ADDRLO, addr_low);

	if (ret < 0)
		return ret;

	FIELD_REPLACE(_mbox_cmd, addr_high, VSPEC1_MBOX_CMD_ADDRHI);
	FIELD_REPLACE(_mbox_cmd, CONST_VSPEC1_MBOX_CMD_CMD_READ, VSPEC1_MBOX_CMD_CMD);

	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_CMD, _mbox_cmd);

	if (ret < 0)
		return ret;

#if defined(P31G_OPT_SPEED) && P31G_OPT_SPEED
	u32 _phy_istat = 0;

	//Read MBOX interrupt status
	do {
		ret = PHY_READ(phy, PHY_PHY_ISTAT);

		if (ret < 0)
			return ret;

	} while ((_phy_istat & PHY_ISTAT_MBOX_POS) != CONST_PHY_ISTAT_MBOX_INACTIVE);

	_phy_istat = 0;
#else

	if (__is_mbox_busy(phy, RETURN_FROM_FUNC) < 0) {
		return -1;
	}

#endif
	//Read Low-Data
	ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_DATA);

	if (ret < 0)
		return ret;

	data_low = ret;

	*data = data_low;

	return 0;
}

/* IP_MDIO read */
int gpy2xx_mbox_write16(struct gpy211_device *phy, u32 regaddr, u32 data)
{
	int ret;
	u32 _mbox_cmd = 0;

	u16 data_low = data & 0xFFFF;
	u16 addr_high = regaddr >> 16;
	u16 addr_low = regaddr & 0xFFFF;

	//Write Low-Data
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_DATA, data_low);

	if (ret < 0)
		return ret;

	//Address to write
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_ADDRLO, addr_low);

	if (ret < 0)
		return ret;

	FIELD_REPLACE(_mbox_cmd, addr_high, VSPEC1_MBOX_CMD_ADDRHI);
	FIELD_REPLACE(_mbox_cmd, CONST_VSPEC1_MBOX_CMD_CMD_WRITE, VSPEC1_MBOX_CMD_CMD);
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_CMD, _mbox_cmd);

	if (ret < 0)
		return ret;

#if defined(P31G_OPT_SPEED) && P31G_OPT_SPEED
	u32 _phy_istat = 0;

	//Read MBOX interrupt status
	do {
		ret = PHY_READ(phy, PHY_PHY_ISTAT);

		if (ret < 0)
			return ret;
	} while ((_phy_istat & PHY_IMASK_MBOX_MASK) != CONST_PHY_ISTAT_MBOX_INACTIVE);

#else

	if (__is_mbox_busy(phy, RETURN_FROM_FUNC) < 0) {
		return -1;
	}

#endif

	return 0;
}

/* IP_MDIO read */
int gpy2xx_mbox_read32(struct gpy211_device *phy, u32 regaddr, u32 *data)
{
	int ret;
	u32 _mbox_cmd = 0;

	u16 data_low = 0;
	u16 data_high = 0;
	u16 addr_high = regaddr >> 16;
	u16 addr_low = regaddr & 0xFFFF;

	//Address to read
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_ADDRLO, addr_low);

	if (ret < 0)
		return ret;

	FIELD_REPLACE(_mbox_cmd, addr_high, VSPEC1_MBOX_CMD_ADDRHI);
	FIELD_REPLACE(_mbox_cmd, CONST_VSPEC1_MBOX_CMD_CMD_READ32, VSPEC1_MBOX_CMD_CMD);
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_CMD, _mbox_cmd);

	if (ret < 0)
		return ret;

#if defined(P31G_OPT_SPEED) && P31G_OPT_SPEED
	u32 _phy_istat = 0;

	//Read MBOX interrupt status
	do {
		ret = PHY_READ(phy, PHY_PHY_ISTAT);

		if (ret < 0)
			return ret;

	} while ((_phy_istat & PHY_ISTAT_MBOX_POS) != CONST_PHY_ISTAT_MBOX_INACTIVE);

	_phy_istat = 0;
#else

	if (__is_mbox_busy(phy, RETURN_FROM_FUNC) < 0) {
		return -1;
	}

#endif
	//Read Low-Data
	ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_DATA);

	if (ret < 0)
		return ret;

	data_low = ret;
	//Read High-Data
	ret = PHY_READ_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_DATA_HIGH);

	if (ret < 0)
		return ret;

	data_high = ret;

	*data = (data_high << 16) | data_low;

	return 0;
}

/* IP_MDIO read */
int gpy2xx_mbox_write32(struct gpy211_device *phy, u32 regaddr, u32 data)
{
	int ret;
	u32 _mbox_cmd = 0;

	u16 data_low = data & 0xFFFF;
	u16 data_high = data >> 16;
	u16 addr_high = regaddr >> 16;
	u16 addr_low = regaddr & 0xFFFF;

	//Write Low-Data
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_DATA, data_low);

	if (ret < 0)
		return ret;

	//Write High-Data
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_DATA_HIGH, data_high);

	if (ret < 0)
		return ret;

	//Address to write
	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_ADDRLO, addr_low);

	if (ret < 0)
		return ret;

	FIELD_REPLACE(_mbox_cmd, addr_high, VSPEC1_MBOX_CMD_ADDRHI);
	FIELD_REPLACE(_mbox_cmd, CONST_VSPEC1_MBOX_CMD_CMD_WRITE32, VSPEC1_MBOX_CMD_CMD);

	ret = PHY_WRITE_MMD(phy, MDIO_MMD_VEND1, VSPEC1_MBOX_CMD, _mbox_cmd);

	if (ret < 0)
		return ret;

#if defined(P31G_OPT_SPEED) && P31G_OPT_SPEED
	u32 _phy_istat = 0;

	//Read MBOX interrupt status
	do {
		ret = PHY_READ(phy, PHY_PHY_ISTAT);

		if (ret < 0)
			return ret;
	} while ((_phy_istat & PHY_IMASK_MBOX_MASK) != CONST_PHY_ISTAT_MBOX_INACTIVE);

#else

	if (__is_mbox_busy(phy, RETURN_FROM_FUNC) < 0) {
		return -1;
	}

#endif

	return 0;
}

int gpy2xx_gmacf_pm_cfg(struct gpy211_device *phy,
			const struct pm_gmac_cfg *gmac_ctrl)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	u16 gmacf_cfg = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || gmac_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = PM_PDI_MODULE_BASE;
	//Get PM GMAC Configuration.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_GMAC_CFG, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMAC_CFG read fails\n");
		goto END;
	}

	gmacf_cfg = _data;

	FIELD_REPLACE(gmacf_cfg, gmac_ctrl->crc_pad_ctrl, PM_PDI_GMAC_CFG_GMAC_CRC_PAD);
	FIELD_REPLACE(gmacf_cfg, gmac_ctrl->tx_err_input, PM_PDI_GMAC_CFG_GMAC_ERR);
	FIELD_REPLACE(gmacf_cfg, gmac_ctrl->big_endian, PM_PDI_GMAC_CFG_GMAC_ENDIAN);

	//Set PM GMAC Configuration.
	ret = PHY_MBOX_HWWR(phy, _base_addr + PM_PDI_GMAC_CFG, gmacf_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMAC_CFG write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacf_pm_get(struct gpy211_device *phy,
			struct pm_gmac_cfg *gmac_ctrl)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	u16 gmacf_cfg = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || gmac_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = PM_PDI_MODULE_BASE;;
	//Get PM GMAC Configuration.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_GMAC_CFG, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMAC_CFG read fails\n");
		goto END;
	}

	gmacf_cfg = _data;

	gmac_ctrl->crc_pad_ctrl = FIELD_GET(gmacf_cfg, PM_PDI_GMAC_CFG_GMAC_CRC_PAD);
	gmac_ctrl->tx_err_input = FIELD_GET(gmacf_cfg, PM_PDI_GMAC_CFG_GMAC_ERR);
	gmac_ctrl->big_endian = FIELD_GET(gmacf_cfg, PM_PDI_GMAC_CFG_GMAC_ENDIAN);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacl_pm_cfg(struct gpy211_device *phy,
			const struct pm_gmac_cfg *gmac_ctrl)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	u16 gmacl_cfg = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || gmac_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = PM_PDI_MODULE_BASE;
	//Get PM GMACL Configuration.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_GMACL_CFG, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMACL_CFG read fails\n");
		goto END;
	}

	gmacl_cfg = _data;

	FIELD_REPLACE(gmacl_cfg, gmac_ctrl->crc_pad_ctrl, PM_PDI_GMACL_CFG_GMACL_CRC_PAD);
	FIELD_REPLACE(gmacl_cfg, gmac_ctrl->tx_err_input, PM_PDI_GMACL_CFG_GMACL_ERR);
	FIELD_REPLACE(gmacl_cfg, gmac_ctrl->big_endian, PM_PDI_GMACL_CFG_GMACL_ENDIAN);

	//Set PM GMACL Configuration.
	ret = PHY_MBOX_HWWR(phy, _base_addr + PM_PDI_GMACL_CFG, gmacl_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMACL_CFG write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacl_pm_get(struct gpy211_device *phy,
			struct pm_gmac_cfg *gmac_ctrl)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	u16 gmacl_cfg = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || gmac_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = PM_PDI_MODULE_BASE;
	//Get PM GMACL Configuration.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_GMACL_CFG, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMACL_CFG read fails\n");
		goto END;
	}

	gmacl_cfg = _data;

	gmac_ctrl->crc_pad_ctrl = FIELD_GET(gmacl_cfg, PM_PDI_GMACL_CFG_GMACL_CRC_PAD);
	gmac_ctrl->tx_err_input = FIELD_GET(gmacl_cfg, PM_PDI_GMACL_CFG_GMACL_ERR);
	gmac_ctrl->big_endian = FIELD_GET(gmacl_cfg, PM_PDI_GMACL_CFG_GMACL_ENDIAN);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacf_pkt_cfg(struct gpy211_device *phy,
			 const struct gmac_pkt_cfg *pcfg)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	u16 mac_cfg_h = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || pcfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = GMACF_EQOS_MAC_MODULE_BASE;
	//Get MAC Pkt Config info.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_MAC_CONFIGURATION_H, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_CONFIGURATION_H read fails\n");
		goto END;
	}

	mac_cfg_h = _data;

	FIELD_REPLACE(mac_cfg_h, pcfg->jumbo_en, GMACF_MAC_CONFIGURATION_H_JE);
	FIELD_REPLACE(mac_cfg_h, pcfg->tx_jabber_dis, GMACF_MAC_CONFIGURATION_H_JD);
	FIELD_REPLACE(mac_cfg_h, pcfg->watchdog_dis, GMACF_MAC_CONFIGURATION_H_WD);
	FIELD_REPLACE(mac_cfg_h, pcfg->pad_crc_strip_en, GMACF_MAC_CONFIGURATION_H_ACS);
	FIELD_REPLACE(mac_cfg_h, pcfg->crc_strip_en, GMACF_MAC_CONFIGURATION_H_CST);
	FIELD_REPLACE(mac_cfg_h, pcfg->support_2kp, GMACF_MAC_CONFIGURATION_H_S2KP);
	FIELD_REPLACE(mac_cfg_h, pcfg->mac_ipg, GMACF_MAC_CONFIGURATION_H_IPG);

	//Set MAC Pkt Config info.
	ret = PHY_MBOX_HWWR(phy, _base_addr + GMACF_MAC_CONFIGURATION_H, mac_cfg_h);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_CONFIGURATION_H write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacf_pkt_get(struct gpy211_device *phy,
			 struct gmac_pkt_cfg *pcfg)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	u16 mac_cfg_h = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || pcfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = GMACF_EQOS_MAC_MODULE_BASE;
	//Get MAC Pkt Config info.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_MAC_CONFIGURATION_H, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_CONFIGURATION_H read fails\n");
		goto END;
	}

	mac_cfg_h = _data;

	pcfg->jumbo_en = FIELD_GET(mac_cfg_h, GMACF_MAC_CONFIGURATION_H_JE);
	pcfg->tx_jabber_dis = FIELD_GET(mac_cfg_h, GMACF_MAC_CONFIGURATION_H_JD);
	pcfg->watchdog_dis = FIELD_GET(mac_cfg_h, GMACF_MAC_CONFIGURATION_H_WD);
	pcfg->pad_crc_strip_en = FIELD_GET(mac_cfg_h, GMACF_MAC_CONFIGURATION_H_ACS);
	pcfg->crc_strip_en = FIELD_GET(mac_cfg_h, GMACF_MAC_CONFIGURATION_H_CST);
	pcfg->support_2kp = FIELD_GET(mac_cfg_h, GMACF_MAC_CONFIGURATION_H_S2KP);
	pcfg->mac_ipg = FIELD_GET(mac_cfg_h, GMACF_MAC_CONFIGURATION_H_IPG);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacx_pm_pdi_cfg(struct gpy211_device *phy,
			    const struct pm_config *pm_cfg)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	u16 pm_pdi_cfg = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || pm_cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = PM_PDI_MODULE_BASE;
	//Get PM Configuration.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_CFG, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: PM_PDI_CFG read fails\n");
		goto END;
	}

	pm_pdi_cfg = _data;

	FIELD_REPLACE(pm_pdi_cfg, pm_cfg->bypass_gmac, PM_PDI_CFG_GMAC_BYP);
	FIELD_REPLACE(pm_pdi_cfg, pm_cfg->bypass_gmac, PM_PDI_CFG_GMACL_BYP);
	FIELD_REPLACE(pm_pdi_cfg, pm_cfg->bypass_macsec, PM_PDI_CFG_MACSECE_BYP);
	FIELD_REPLACE(pm_pdi_cfg, pm_cfg->bypass_macsec, PM_PDI_CFG_MACSECI_BYP);
	FIELD_REPLACE(pm_pdi_cfg, pm_cfg->bypass_macsec, PM_PDI_CFG_MACSEC_RST);
	FIELD_REPLACE(pm_pdi_cfg, pm_cfg->drop_on_crc_err, PM_PDI_CFG_CRC_ERR);
	FIELD_REPLACE(pm_pdi_cfg, pm_cfg->drop_on_pkt_err, PM_PDI_CFG_PKT_ERR);
	FIELD_REPLACE(pm_pdi_cfg, pm_cfg->drop_on_sec_fail, PM_PDI_CFG_SEC_FAIL);
	FIELD_REPLACE(pm_pdi_cfg, pm_cfg->class_drop, PM_PDI_CFG_CLASS_DROP);
	FIELD_REPLACE(pm_pdi_cfg, pm_cfg->cust_3g_en, PM_PDI_CFG_CUST_3G);
	FIELD_REPLACE(pm_pdi_cfg, pm_cfg->sgmii_lb_en, PM_PDI_CFG_SGMII_LOOP);

	//Set PM Configuration.
	ret = PHY_MBOX_HWWR(phy, _base_addr + PM_PDI_CFG, pm_pdi_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: PM_PDI_CFG write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacx_pm_pdi_get(struct gpy211_device *phy,
			    struct pm_config *pm_cfg)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	u16 pm_pdi_cfg = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || pm_cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = PM_PDI_MODULE_BASE;

	//Get PM Configuration.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_CFG, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: PM_PDI_CFG read fails\n");
		goto END;
	}

	pm_pdi_cfg = _data;

	pm_cfg->bypass_gmac = FIELD_GET(pm_pdi_cfg, PM_PDI_CFG_GMAC_BYP);
	pm_cfg->bypass_gmac = FIELD_GET(pm_pdi_cfg, PM_PDI_CFG_GMACL_BYP);
	pm_cfg->bypass_macsec = FIELD_GET(pm_pdi_cfg, PM_PDI_CFG_MACSECE_BYP);
	pm_cfg->bypass_macsec = FIELD_GET(pm_pdi_cfg, PM_PDI_CFG_MACSECI_BYP);
	pm_cfg->drop_on_crc_err = FIELD_GET(pm_pdi_cfg, PM_PDI_CFG_CRC_ERR);
	pm_cfg->drop_on_pkt_err = FIELD_GET(pm_pdi_cfg, PM_PDI_CFG_PKT_ERR);
	pm_cfg->drop_on_sec_fail = FIELD_GET(pm_pdi_cfg, PM_PDI_CFG_SEC_FAIL);
	pm_cfg->class_drop = FIELD_GET(pm_pdi_cfg, PM_PDI_CFG_CLASS_DROP);
	pm_cfg->cust_3g_en = FIELD_GET(pm_pdi_cfg, PM_PDI_CFG_CUST_3G);
	pm_cfg->sgmii_lb_en = FIELD_GET(pm_pdi_cfg, PM_PDI_CFG_SGMII_LOOP);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacl_pause_cfg(struct gpy211_device *phy,
			   const struct pause_cfg *pcfg)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	u16 q0_tx_fctrl = 0, mac_addr = 0, gmacl_pcfg = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || pcfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = PM_PDI_MODULE_BASE;
	//Get GMAC-Lite's Pause Control info.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_GMACL_CFG, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMACL_CFG read fails\n");
		goto END;
	}

	gmacl_pcfg = _data;

	FIELD_REPLACE(gmacl_pcfg, pcfg->pm_gmacl_fc, PM_PDI_GMACL_CFG_GMACL_FLW_CTRL);

	//Set GMAC-Lite's Pause Control info.
	ret = PHY_MBOX_HWWR(phy, _base_addr + PM_PDI_GMACL_CFG, gmacl_pcfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMACL_CFG write fails\n");
		goto END;
	}

	_base_addr = GMACL_EQOS_MAC_MODULE_BASE;

	//Get Pause Control info.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACL_MAC_Q0_TX_FLOW_CTRL_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_Q0_TX_FLOW_CTRL_L read fails\n");
		goto END;
	}

	q0_tx_fctrl = _data;

	FIELD_REPLACE(q0_tx_fctrl, pcfg->flow_ctrl_busy, GMACL_MAC_Q0_TX_FLOW_CTRL_L_FCB_BPA);
	FIELD_REPLACE(q0_tx_fctrl, pcfg->tx_flow_ctrl, GMACL_MAC_Q0_TX_FLOW_CTRL_L_TFE);
	FIELD_REPLACE(q0_tx_fctrl, pcfg->pause_low_thresh, GMACL_MAC_Q0_TX_FLOW_CTRL_L_PLT);
	FIELD_REPLACE(q0_tx_fctrl, pcfg->dis_zquanta_pause, GMACL_MAC_Q0_TX_FLOW_CTRL_L_DZPQ);

	//Set Pause Control info.
	ret = PHY_MBOX_HWWR(phy, _base_addr + GMACL_MAC_Q0_TX_FLOW_CTRL_L, q0_tx_fctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_Q0_TX_FLOW_CTRL_L write fails\n");
		goto END;
	}

	//Set Pause Time.
	ret = PHY_MBOX_HWWR(phy, _base_addr + GMACL_MAC_Q0_TX_FLOW_CTRL_H, pcfg->pause_time);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_Q0_TX_FLOW_CTRL_H write fails\n");
		goto END;
	}

	mac_addr = (u16)((pcfg->tx_fc_mac[4] << 8) | pcfg->tx_fc_mac[5]);
	//Set MAC addr [15:0].
	ret = PHY_MBOX_HWWR(phy, _base_addr + GMACL_MAC_ADDRESS0_HIGH_L, mac_addr);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_ADDRESS0_HIGH_L write fails\n");
		goto END;
	}

	mac_addr = (u16)((pcfg->tx_fc_mac[2] << 8) | pcfg->tx_fc_mac[3]);
	//Set MAC addr [31:16].
	ret = PHY_MBOX_HWWR(phy, _base_addr + GMACL_MAC_ADDRESS0_LOW_L, mac_addr);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_ADDRESS0_LOW_L write fails\n");
		goto END;
	}

	mac_addr = (u16)((pcfg->tx_fc_mac[0] << 8) | pcfg->tx_fc_mac[1]);
	//Set MAC addr [47:32].
	ret = PHY_MBOX_HWWR(phy, _base_addr + GMACL_MAC_ADDRESS0_LOW_H, mac_addr);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_ADDRESS0_LOW_H write fails\n");
		goto END;
	}

	_base_addr = PM_PDI_MODULE_BASE;

	//Set Pause Asset Threshold.
	ret = PHY_MBOX_HWWR(phy, _base_addr + PM_PDI_PAUSE_THRES, pcfg->pause_assert_thresh);

	if (ret < 0) {
		LOG_CRIT("ERROR: PAUSE_THRES write fails\n");
		goto END;
	}

	//Set Pause De-Asset Threshold.
	ret = PHY_MBOX_HWWR(phy, _base_addr + PM_PDI_PAUSE_DEASSERT_THRES, pcfg->pause_deassert_thresh);

	if (ret < 0) {
		LOG_CRIT("ERROR: PAUSE_DEASSERT_THRES write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacl_pause_get(struct gpy211_device *phy,
			   struct pause_cfg *pcfg)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	u16 q0_tx_fctrl = 0, gmacl_pcfg = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || pcfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = PM_PDI_MODULE_BASE;
	//Get GMAC-Lite's Pause Control info.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_GMACL_CFG, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMACL_CFG read fails\n");
		goto END;
	}

	gmacl_pcfg = _data;

	pcfg->pm_gmacl_fc = FIELD_GET(gmacl_pcfg, PM_PDI_GMACL_CFG_GMACL_FLW_CTRL);

	_base_addr = GMACL_EQOS_MAC_MODULE_BASE;

	//Get Pause Control info.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACL_MAC_Q0_TX_FLOW_CTRL_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_Q0_TX_FLOW_CTRL_L read fails\n");
		goto END;
	}

	q0_tx_fctrl = _data;

	pcfg->flow_ctrl_busy = FIELD_GET(q0_tx_fctrl, GMACL_MAC_Q0_TX_FLOW_CTRL_L_FCB_BPA);
	pcfg->tx_flow_ctrl = FIELD_GET(q0_tx_fctrl, GMACL_MAC_Q0_TX_FLOW_CTRL_L_TFE);
	pcfg->pause_low_thresh = FIELD_GET(q0_tx_fctrl, GMACL_MAC_Q0_TX_FLOW_CTRL_L_PLT);
	pcfg->dis_zquanta_pause = FIELD_GET(q0_tx_fctrl, GMACL_MAC_Q0_TX_FLOW_CTRL_L_DZPQ);

	//Get Pause Time.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACL_MAC_Q0_TX_FLOW_CTRL_H, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_Q0_TX_FLOW_CTRL_H read fails\n");
		goto END;
	}

	pcfg->pause_time = _data;

	//Get MAC addr [15:0].
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACL_MAC_ADDRESS0_HIGH_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_ADDRESS0_HIGH_L read fails\n");
		goto END;
	}

	pcfg->tx_fc_mac[4] = (ret >> 8) & 0xFF;
	pcfg->tx_fc_mac[5] = (ret >> 0) & 0xFF;

	//Get MAC addr [31:16].
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACL_MAC_ADDRESS0_LOW_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_ADDRESS0_LOW_L read fails\n");
		goto END;
	}

	pcfg->tx_fc_mac[2] = (ret >> 8) & 0xFF;
	pcfg->tx_fc_mac[3] = (ret >> 0) & 0xFF;

	//Get MAC addr [47:32].
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACL_MAC_ADDRESS0_LOW_H, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_ADDRESS0_LOW_H read fails\n");
		goto END;
	}

	pcfg->tx_fc_mac[0] = (ret >> 8) & 0xFF;
	pcfg->tx_fc_mac[1] = (ret >> 0) & 0xFF;

	_base_addr = PM_PDI_MODULE_BASE;

	//Get Pause Asset Threshold.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_PAUSE_THRES, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: PAUSE_THRES read fails\n");
		goto END;
	}

	pcfg->pause_assert_thresh = _data;

	//Get Pause De-Asset Threshold.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_PAUSE_DEASSERT_THRES, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: PAUSE_DEASSERT_THRES read fails\n");
		goto END;
	}

	pcfg->pause_deassert_thresh = _data;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacx_bm_status_get(struct gpy211_device *phy,
			       struct pm_bm_status *bmstat)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	u16 bm_stat = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || bmstat == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = PM_PDI_MODULE_BASE;

	//Get shared buffer and registers status;
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_BM_STAT, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: PDI_BM_STAT read fails\n");
		goto END;
	}

	bm_stat = _data;

	bmstat->sb0_ov = FIELD_GET(bm_stat, PM_PDI_BM_STAT_SB0_OV);
	bmstat->sb0_tx_reg_ov = FIELD_GET(bm_stat, PM_PDI_BM_STAT_SB0_TX_REG_OV);
	bmstat->sb0_rx_reg_ov = FIELD_GET(bm_stat, PM_PDI_BM_STAT_SB0_RX_REG_OV);
	bmstat->sb1_ov = FIELD_GET(bm_stat, PM_PDI_BM_STAT_SB1_OV);
	bmstat->sb1_tx_reg_ov = FIELD_GET(bm_stat, PM_PDI_BM_STAT_SB1_TX_REG_OV);
	bmstat->sb1_rx_reg_ov = FIELD_GET(bm_stat, PM_PDI_BM_STAT_SB1_RX_REG_OV);
	bmstat->sb0_retry = FIELD_GET(bm_stat, PM_PDI_BM_STAT_SB0_RETRY);
	bmstat->sb0_sent = FIELD_GET(bm_stat, PM_PDI_BM_STAT_SB0_SENT);
	bmstat->sb1_retry = FIELD_GET(bm_stat, PM_PDI_BM_STAT_SB1_RETRY);
	bmstat->sb1_sent = FIELD_GET(bm_stat, PM_PDI_BM_STAT_SB1_SENT);
	bmstat->sb0_complete = FIELD_GET(bm_stat, PM_PDI_BM_STAT_SB0_COMPLETE);
	bmstat->sb1_complete = FIELD_GET(bm_stat, PM_PDI_BM_STAT_SB1_COMPLETE);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacx_bm_cfg(struct gpy211_device *phy,
			const struct bm_cfg *bmcfg)
{
	int ret = -EINVAL;
	u32 _base_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || bmcfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = PM_PDI_MODULE_BASE;

	//Set SB 0 Start offset.
	ret = PHY_MBOX_HWWR(phy, _base_addr + PM_PDI_SB0_START, bmcfg->sb0_start);

	if (ret < 0) {
		LOG_CRIT("ERROR: SB0_START write fails\n");
		goto END;
	}

	//Set SB 0 End offset.
	ret = PHY_MBOX_HWWR(phy, _base_addr + PM_PDI_SB0_END, bmcfg->sb0_end);

	if (ret < 0) {
		LOG_CRIT("ERROR: SB0_END write fails\n");
		goto END;
	}

	//Set SB 0 Packet Threshold to start the dequeue.
	ret = PHY_MBOX_HWWR(phy, _base_addr + PM_PDI_SB0_PKT_THRES, bmcfg->sb0_pkt_thresh);

	if (ret < 0) {
		LOG_CRIT("ERROR: SB0_PKT_THRES write fails\n");
		goto END;
	}

	//Set SB 1 Start offset.
	ret = PHY_MBOX_HWWR(phy, _base_addr + PM_PDI_SB1_START, bmcfg->sb1_start);

	if (ret < 0) {
		LOG_CRIT("ERROR: SB1_START write fails\n");
		goto END;
	}

	//Set SB 1 End offset.
	ret = PHY_MBOX_HWWR(phy, _base_addr + PM_PDI_SB1_END, bmcfg->sb1_end);

	if (ret < 0) {
		LOG_CRIT("ERROR: SB1_END write fails\n");
		goto END;
	}

	//Set SB 1 Packet Threshold to start the dequeue.
	ret = PHY_MBOX_HWWR(phy, _base_addr + PM_PDI_SB1_PKT_THRES, bmcfg->sb1_pkt_thresh);

	if (ret < 0) {
		LOG_CRIT("ERROR: SB1_PKT_THRES write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacx_bm_get(struct gpy211_device *phy, struct bm_cfg *bmcfg)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || bmcfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = PM_PDI_MODULE_BASE;
	//Get SB 0 Start offset.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_SB0_START, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: SB0_START read fails\n");
		goto END;
	}

	bmcfg->sb0_start = _data;

	//Get SB 0 End offset.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_SB0_END, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: SB0_END read fails\n");
		goto END;
	}

	bmcfg->sb0_end = _data;

	//Get SB 0 Packet Threshold to start the dequeue.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_SB0_PKT_THRES, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: SB0_PKT_THRES read fails\n");
		goto END;
	}

	bmcfg->sb0_pkt_thresh = _data;

	//Get SB 1 Start offset.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_SB1_START, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: SB1_START read fails\n");
		goto END;
	}

	bmcfg->sb1_start = _data;

	//Get SB 1 End offset.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_SB1_END, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: SB1_END read fails\n");
		goto END;
	}

	bmcfg->sb1_end = _data;

	//Get SB 1 Packet Threshold to start the dequeue.
	ret = PHY_MBOX_HWRD(phy, _base_addr + PM_PDI_SB1_PKT_THRES, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: SB1_PKT_THRES read fails\n");
		goto END;
	}

	bmcfg->sb1_pkt_thresh = _data;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacf_count_ctrl_cfg(struct gpy211_device *phy,
				const struct gmacf_counter_ctrl *cctrl)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	u16 counter_ctrl = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = GMACF_EQOS_MAC_MODULE_BASE;
	//Get Counter Control info.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_MMC_CONTROL_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: MMC_CONTROL_L read fails\n");
		goto END;
	}

	counter_ctrl = _data;

	FIELD_REPLACE(counter_ctrl, cctrl->reset_counters, GMACF_MMC_CONTROL_L_CNTRST);
	FIELD_REPLACE(counter_ctrl, cctrl->stop_rollover, GMACF_MMC_CONTROL_L_CNTSTOPRO);
	FIELD_REPLACE(counter_ctrl, cctrl->clear_on_read, GMACF_MMC_CONTROL_L_RSTONRD);
	FIELD_REPLACE(counter_ctrl, cctrl->freeze_counters, GMACF_MMC_CONTROL_L_CNTFREEZ);
	FIELD_REPLACE(counter_ctrl, cctrl->preset_counters, GMACF_MMC_CONTROL_L_CNTPRST);
	FIELD_REPLACE(counter_ctrl, cctrl->preset_half_full, GMACF_MMC_CONTROL_L_CNTPRSTLVL);
	FIELD_REPLACE(counter_ctrl, cctrl->count_dropped_bc, GMACF_MMC_CONTROL_L_UCDBC);

	//Set Counter Control info.
	ret = PHY_MBOX_HWWR(phy, _base_addr + GMACF_MMC_CONTROL_L, counter_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: MMC_CONTROL_L write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacf_count_ctrl_get(struct gpy211_device *phy,
				struct gmacf_counter_ctrl *cctrl)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	u16 counter_ctrl = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = GMACF_EQOS_MAC_MODULE_BASE;
	//Get Counter Control info.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_MMC_CONTROL_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: MMC_CONTROL_L read fails\n");
		goto END;
	}

	counter_ctrl = _data;

	cctrl->reset_counters = FIELD_GET(counter_ctrl, GMACF_MMC_CONTROL_L_CNTRST);
	cctrl->stop_rollover = FIELD_GET(counter_ctrl, GMACF_MMC_CONTROL_L_CNTSTOPRO);
	cctrl->clear_on_read = FIELD_GET(counter_ctrl, GMACF_MMC_CONTROL_L_RSTONRD);
	cctrl->freeze_counters = FIELD_GET(counter_ctrl, GMACF_MMC_CONTROL_L_CNTFREEZ);
	cctrl->preset_counters = FIELD_GET(counter_ctrl, GMACF_MMC_CONTROL_L_CNTPRST);
	cctrl->preset_half_full = FIELD_GET(counter_ctrl, GMACF_MMC_CONTROL_L_CNTPRSTLVL);
	cctrl->count_dropped_bc = FIELD_GET(counter_ctrl, GMACF_MMC_CONTROL_L_UCDBC);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gmacf_count_get(struct gpy211_device *phy,
			   struct gmacf_counters *counters)
{
	int ret = -EINVAL;
	u32 _base_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || counters == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = GMACF_EQOS_MAC_MODULE_BASE;
	//Get Tx Good-Bad frame count.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_TX_PACKET_COUNT_GOOD_BAD_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: TX_PACKET_COUNT_GOOD_BAD_L read fails\n");
		goto END;
	}

	counters->tx_good_bad = _data;

	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_TX_PACKET_COUNT_GOOD_BAD_H, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: TX_PACKET_COUNT_GOOD_BAD_H read fails\n");
		goto END;
	}

	counters->tx_good_bad = (_data << 16) | counters->tx_good_bad;

	//Get Tx Underflow error frame count.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_TX_UNDERFLOW_ERROR_PACKETS_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: TX_UNDERFLOW_ERROR_L read fails\n");
		goto END;
	}

	counters->tx_uflow_err = _data;

	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_TX_UNDERFLOW_ERROR_PACKETS_H, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: TX_UNDERFLOW_ERROR_H read fails\n");
		goto END;
	}

	counters->tx_uflow_err = (_data << 16) | counters->tx_uflow_err;

	//Get Tx Good frame count.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_TX_PACKET_COUNT_GOOD_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: TX_PACKET_COUNT_GOOD_L read fails\n");
		goto END;
	}

	counters->tx_good = _data;

	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_TX_PACKET_COUNT_GOOD_H, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: TX_PACKET_COUNT_GOOD_H read fails\n");
		goto END;
	}

	counters->tx_good = (_data << 16) | counters->tx_good;

	//Get Tx Oversize Good frame count.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_TX_OSIZE_PACKETS_GOOD_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: TX_OSIZE_PACKETS_GOOD_L read fails\n");
		goto END;
	}

	counters->tx_osize_good = _data;

	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_TX_OSIZE_PACKETS_GOOD_H, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: TX_OSIZE_PACKETS_GOOD_H read fails\n");
		goto END;
	}

	counters->tx_osize_good = (_data << 16) | counters->tx_osize_good;

	//Get Rx Good-Bad frame count.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_RX_PACKETS_COUNT_GOOD_BAD_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: RX_PACKETS_COUNT_GOOD_BAD_L read fails\n");
		goto END;
	}

	counters->rx_good_bad = _data;

	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_RX_PACKETS_COUNT_GOOD_BAD_H, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: RX_PACKETS_COUNT_GOOD_BAD read fails\n");
		goto END;
	}

	counters->rx_good_bad = (_data << 16) | counters->rx_good_bad;

	//Get Rx CRC error frame count;
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_RX_CRC_ERROR_PACKETS_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: RX_CRC_ERROR_PACKETS_L read fails\n");
		goto END;
	}

	counters->rx_crc_err = _data;

	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_RX_CRC_ERROR_PACKETS_H, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: RX_CRC_ERROR_PACKETS_H read fails\n");
		goto END;
	}

	counters->rx_crc_err = (_data << 16) | counters->rx_crc_err;

	//Get Rx Undersize frame count.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_RX_UNDERSIZE_PACKETS_GOOD_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: RX_UNDERSIZE_PACKETS_L read fails\n");
		goto END;
	}

	counters->rx_usize_good = _data;

	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_RX_UNDERSIZE_PACKETS_GOOD_H, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: RX_UNDERSIZE_PACKETS_H read fails\n");
		goto END;
	}

	counters->rx_usize_good = (_data << 16) | counters->rx_usize_good;

	//Get Rx Oversize Good frame count.
	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_RX_OVERSIZE_PACKETS_GOOD_L, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: RX_OVERSIZE_PACKETS_L read fails\n");
		goto END;
	}

	counters->rx_osize_good = _data;

	ret = PHY_MBOX_HWRD(phy, _base_addr + GMACF_RX_OVERSIZE_PACKETS_GOOD_H, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: RX_OVERSIZE_PACKETS read fails\n");
		goto END;
	}

	counters->rx_osize_good = (_data << 16) | counters->rx_osize_good;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

#if defined(EN_BACKWARD_COMP_API) && EN_BACKWARD_COMP_API
/* Deprecated but defined for backword compatible */
int gpy211_init(struct gpy211_device *phy)
{
	return gpy2xx_init(phy);
}

int gpy211_uinit(struct gpy211_device *phy)
{
	return gpy2xx_uninit(phy);
}

int gpy211_soft_reset(struct gpy211_device *phy)
{
	return gpy2xx_soft_reset(phy);
}

int gpy211_poll_reset(struct gpy211_device *phy)
{
	return gpy2xx_poll_reset(phy);
}

int gpy211_loopback_cfg(struct gpy211_device *phy,
			enum gpy211_test_loop tloop)
{
	return gpy2xx_loopback_cfg(phy, tloop);
}

int gpy211_abist_start(struct gpy211_device *phy,
		       struct gpy211_abist_param *param)
{
	return gpy2xx_abist_start(phy, param);
}

int gpy211_abist_read(struct gpy211_device *phy,
		      struct gpy211_abist_report *report)
{
	return gpy2xx_abist_read(phy, report);
}

int gpy211_test_mode_cfg(struct gpy211_device *phy,
			 enum gpy211_test_mode mode)
{
	return gpy2xx_test_mode_cfg(phy, mode);
}

int gpy211_cdiag_start(struct gpy211_device *phy)
{
	return gpy2xx_cdiag_start(phy);
}

int gpy211_cdiag_read(struct gpy211_device *phy,
		      struct gpy211_cdiag_report *report)
{
	return gpy2xx_cdiag_read(phy, report);
}

int gpy211_errcnt_cfg(struct gpy211_device *phy,
		      enum gpy211_errcnt_event event)
{
	return gpy2xx_errcnt_cfg(phy, event);
}

int gpy211_wol_cfg(struct gpy211_device *phy, struct gpy211_wolinfo *wol)
{
	return gpy2xx_wol_cfg(phy, wol);
}

int gpy211_wol_get(struct gpy211_device *phy, struct gpy211_wolinfo *wol)
{
	return gpy2xx_wol_get(phy, wol);
}

int gpy211_setup_forced(struct gpy211_device *phy)
{
	return gpy2xx_setup_forced(phy);
}

int gpy211_config_aneg(struct gpy211_device *phy)
{
	return gpy2xx_config_aneg(phy);
}

int gpy211_config_advert(struct gpy211_device *phy)
{
	return gpy2xx_config_advert(phy);
}

int gpy211_restart_aneg(struct gpy211_device *phy)
{
	return gpy2xx_restart_aneg(phy);
}

int gpy211_aneg_done(struct gpy211_device *phy)
{
	return gpy2xx_aneg_done(phy);
}

int gpy211_update_link(struct gpy211_device *phy)
{
	return gpy2xx_update_link(phy);
}

int gpy211_read_status(struct gpy211_device *phy)
{
	return gpy2xx_read_status(phy);
}

int gpy211_pcs_status_read(struct gpy211_device *phy,
			   struct gpy211_pcs_status *status)
{
	return gpy2xx_pcs_status_read(phy, status);
}

int gpy211_ads_cfg(struct gpy211_device *phy, struct gpy211_ads_ctrl *ads)
{
	return gpy2xx_ads_cfg(phy, ads);
}

int gpy211_ads_get(struct gpy211_device *phy, struct gpy211_ads_sta *ads)
{
	return gpy2xx_ads_get(phy, ads);
}

int gpy211_ads_detected(struct gpy211_device *phy)
{
	return gpy2xx_ads_detected(phy);
}

int gpy211_led_top_cfg(struct gpy211_device *phy,
		       struct gpy211_led_gcfg *cfg)
{
	return gpy2xx_led_top_cfg(phy, cfg);
}

int gpy211_led_top_get(struct gpy211_device *phy,
		       struct gpy211_led_gcfg *cfg)
{
	return gpy2xx_led_top_get(phy, cfg);
}

int gpy211_led_if_cfg(struct gpy211_device *phy,
		      struct gpy211_led_cfg *cfg)
{
	return gpy2xx_led_if_cfg(phy, cfg);
}

int gpy211_led_if_get(struct gpy211_device *phy,
		      struct gpy211_led_cfg *cfg)
{
	return gpy2xx_led_if_get(phy, cfg);
}

int gpy211_extin_mask(struct gpy211_device *phy,
		      struct gpy211_phy_extin *extin)
{
	return gpy2xx_extin_mask(phy, extin);
}

int gpy211_extin_get(struct gpy211_device *phy,
		     struct gpy211_phy_extin *extin)
{
	return gpy2xx_extin_get(phy, extin);
}

#if defined(EN_GMAC_DEBUG_ACCESS) && EN_GMAC_DEBUG_ACCESS
int gpy211_extin_clr(struct gpy211_device *phy,
		     struct gpy211_phy_extin *extin)
{
	return gpy2xx_extin_clr(phy, extin);
}
#endif

int gpy211_pvt_get(struct gpy211_device *phy, struct gpy211_pvt *pvt)
{
	return gpy2xx_pvt_get(phy, pvt);
}

int gpy211_gpio_cfg(struct gpy211_device *phy, struct gpy211_gpio *gpio)
{
	return gpy2xx_gpio_cfg(phy, gpio);
}

int gpy211_gpio_get(struct gpy211_device *phy, struct gpy211_gpio *gpio)
{
	return gpy2xx_gpio_get(phy, gpio);
}

int gpy211_gpio_output(struct gpy211_device *phy,
		       struct gpy211_gpio *gpio)
{
	return gpy2xx_gpio_output(phy, gpio);
}

int gpy211_gpio_input(struct gpy211_device *phy,
		      struct gpy211_gpio *gpio)
{
	return gpy2xx_gpio_input(phy, gpio);
}

int gpy211_led_br_cfg(struct gpy211_device *phy,
		      struct gpy211_led_brlvl_cfg *brtness_cfg)
{
	return gpy2xx_led_br_cfg(phy, brtness_cfg);
}

int gpy211_led_br_get(struct gpy211_device *phy,
		      struct gpy211_led_brlvl_cfg *brtness_cfg)
{
	return gpy2xx_led_br_get(phy, brtness_cfg);
}

#ifdef EN_SUPPORT_TOP_INT
int gpy211_topin_cfg(struct gpy211_device *phy,
		     struct gpy211_extin *extin)
{
	return gpy2xx_topin_cfg(phy, extin);
}

int gpy211_topin_get(struct gpy211_device *phy,
		     struct gpy211_extin *extin)
{
	return gpy2xx_topin_get(phy, extin);
}

int gpy211_topin_clr(struct gpy211_device *phy,
		     struct gpy211_extin *extin)
{
	return gpy2xx_topin_clr(phy, extin);
}
#endif

int gpy211_sgmii_opmode(struct gpy211_device *phy,
			enum gpy211_sgmii_operation mode)
{
	return gpy2xx_sgmii_opmode(phy, mode);
}

int gpy211_sgmii_config_aneg(struct gpy211_device *phy,
			     struct gpy211_sgmii *sgmii)
{
	return gpy2xx_sgmii_config_aneg(phy, sgmii);
}

int gpy211_sgmii_restart_aneg(struct gpy211_device *phy)
{
	return gpy2xx_sgmii_restart_aneg(phy);
}

int gpy211_sgmii_aneg_done(struct gpy211_device *phy)
{
	return gpy2xx_sgmii_aneg_done(phy);
}

int gpy211_sgmii_read_status(struct gpy211_device *phy,
			     struct gpy211_sgmii *sgmii)
{
	return gpy2xx_sgmii_read_status(phy, sgmii);
}
#endif
