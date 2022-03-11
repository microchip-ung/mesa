/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#ifdef __KERNEL__
#define DEBUG
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#endif

#include "gpy211_common.h"
#include "gpy211_macsec.h"
#include "gpy211_regs.h"

#if defined(SAFE_C_LIB) && SAFE_C_LIB
errno_t memcpy_s(void *restrict dest, rsize_t dmax, const void *restrict src,
		 rsize_t smax);
#endif

//#include "aes.h" //For AES_Encrypt prototype declation
//AES_Encrypt func definition presents in aes.c
void
AES_Encrypt(const unsigned char *const pInput, unsigned char *const pOutput,
	    const unsigned char *const pKey, unsigned int nKeyLen);


static int _is_sam_in_flight_safe(struct gpy211_device *phy, enum msec_dir dir)
{
	int ret = 0;
	u32 unsafe, busy_retry = IN_FLIGHT_BUSY_RETRY;
	u32 _base_addr, _offset, _target_addr, _data;

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	if (dir == INGRESS_DIR) {
		_base_addr = EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL_MODULE_BASE;
	} else {
		_base_addr = EIPE_EIP_160S_E_32_SAM_ENABLE_CTRL_MODULE_BASE;
	}

	_offset = EIPI_SAM_IN_FLIGHT;
	_target_addr = _base_addr + _offset;

	/* Read and Write test */
	ret = PHY_MBOX_WRITE(phy, _target_addr, EIPI_SAM_IN_FLIGHT_LOAD_UNSAFE_MASK);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_IN_FLIGHT unsafe write fails\n");
		goto END;
	}

	do {
		/* Read and Write test */
		ret = PHY_MBOX_READ(phy, _target_addr, &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: SAM_IN_FLIGHT unsafe read fails\n");
			goto END;
		}

		unsafe = _data & EIPI_SAM_IN_FLIGHT_UNSAFE_MASK;
		busy_retry--;

		if (busy_retry == 0) {
			LOG_CRIT("ERROR: EIP-160 device sync failed\n");
			ret = -1;
			break;
		}

	} while (unsafe);

END:
	return ret;
}

static int _gpy2xx_msec_detect_ing_eip160(struct gpy211_device *phy)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	struct eip160_config2 ext_cfg;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIPI_EIP_160S_I_32_SYSTEM_CONTROL_MODULE_BASE;
	_offset =  EIPI_EIP160_VERSION;
	_target_addr = _base_addr + _offset;

	/* Check EIP160 nuber and it's complement */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160_VERSION read fails for iteration\n");
		goto END;
	}

#ifdef VERIFY_ENDIANNESS
	{
		u32 x = 1, y = 0;
		y = (int)(((char *)&x)[0]);
		printf("%s", (y == 1) ? "LITTLE_ENDIAN" : "BIG_ENDIAN");
	}
	struct eip160_version eip_ver;
	eip_ver.raw_eip160_ver = _data;
	LOG_CRIT("EIP num raw %x, stored %x\n", _data, eip_ver.raw_eip160_ver);
	LOG_CRIT("EIP num %x compliment %x, patch-level %x, minor-ver %x, major-ver %x, reserved %x\n",
		 eip_ver.eip_nr, eip_ver.eip_nr_complement, eip_ver.patch_level, eip_ver.minor_version, eip_ver.major_version, eip_ver.reserved);
#endif

	if ((_data & 0xFFFFu) != EIP160_NR_CNR) {
		LOG_CRIT("EIP160 number mismatch\n");
		ret = -1;
		goto END;
	}

	_base_addr = EIPI_EIP_160S_I_32_SYSTEM_CONTROL_MODULE_BASE;
	_offset = EIPI_EIP160_CONFIG2;
	_target_addr = _base_addr + _offset;

	/* Gt EIP160_CONFIG2 data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160_CONFIG2 word get fails\n");
		goto END;
	}

	ext_cfg.raw_eip160_cfg2 = _data;

	if (ext_cfg.ingress_only != 1) {
		LOG_CRIT("It is not configured for ingress only\n");
		ret = -1;
		goto END;
	}

	_base_addr = EIP_160S_IG_TR_PAGE0_BASE;
	_offset =  EIP_160S_IG_TR_PAGE0_OFFSET;
	_target_addr = _base_addr + _offset;

	/* Read and Write test */
	ret = PHY_MBOX_WRITE(phy, _target_addr, 0xfedcba98);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160 test write fails\n");
		goto END;
	}

	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160 test read fails\n");
		goto END;
	}

	if (_data != 0xfedcba98) {
		LOG_CRIT("EIP160 test write & read fails\n");
		ret = -1;
		goto END;
	}

	/* Reset */
	ret = PHY_MBOX_WRITE(phy, _target_addr, 0x0);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160 test reset fails\n");
		ret = -1;
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_detect_ing_eip62(struct gpy211_device *phy)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIPI_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;
	_offset =  EIPI_EIP62_VERSION;
	_target_addr = _base_addr + _offset;

	/* Check EIP62 nuber and it's complement */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_VERSION read fails\n");
		goto END;
	}

	if ((_data & 0xFFFFu) != EIP62_NR_CNR) {
		LOG_CRIT("EIP62 number mismatch\n");
		ret = -1;
		goto END;
	}

	_base_addr = EIPI_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;
	_offset =  EIPI_EIP62_SEQ_NUM_THRESHOLD;
	_target_addr = _base_addr + _offset;

	/* Read and Write test */
	ret = PHY_MBOX_WRITE(phy, _target_addr, 0x89abcdef);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62 test write fails\n");
		goto END;
	}

	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62 test read fails\n");
		goto END;
	}

	if (_data != 0x89abcdef) {
		LOG_CRIT("EIP160 test write & read fails\n");
		ret = -1;
		goto END;
	}

	/* Reset */
	ret = PHY_MBOX_WRITE(phy, _target_addr, 0x0);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62 test reset fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_clear_ing_tr_ram(struct gpy211_device *phy)
{
	int i, j, ret = 0;
	u32 _base_addr, _offset, _target_addr;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIP_160S_IG_TR_PAGE0_BASE;

	/* Clear Transform Record RAM */
	for (i = 0; i < (phy->nr_of_sas); i++) {
		_offset = ((i > 127) ? 0x10000 : 0) + EIP_160S_IG_TR_PAGE0_OFFSET + (i * ING_MAX_TR_SIZE_BYTES);
		_target_addr = _base_addr + _offset;

		for (j = 0; j < 1; j++) { /* No-Need init full segment 'ING_MAX_TR_SIZE_WORDS' */
			ret = PHY_MBOX_WRITE(phy, _target_addr + (j * 4), 0x0);

			if (ret < 0) {
				LOG_CRIT("ERROR: TR mem init fails\n");
				goto END;
			}
		}
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_config_ing_ctx_size(struct gpy211_device *phy)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _ctx_ctrl = 0;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIPI_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;
	_offset =  EIPI_EIP62_CONTEXT_CTRL;
	_target_addr = _base_addr + _offset;

	/* Get EIP62_CONTEXT_CTRL */
	ret = PHY_MBOX_READ(phy, _target_addr, &_ctx_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: Get EIP62_CONTEXT_CTRL fails\n");
		goto END;
	}

	FIELD_REPLACE(_ctx_ctrl, ING_MAX_TR_SIZE_WORDS, EIPI_EIP62_CONTEXT_CTRL_CONTEXT_SIZE);

	/* Set EIP62_CONTEXT_CTRL.context_size */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _ctx_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: Set context_size fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_config_ing_ctx_upd(struct gpy211_device *phy)
{
	int ret;
	u32 _base_addr, _offset, _target_addr;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIPI_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;
	_offset =  EIPI_EIP62_CONTEXT_UPD_CTRL;
	_target_addr = _base_addr + _offset;

	/* Set 'EIP62_CONTEXT_UPD_CTRL.block_context_updates' to do not update the
		context for bad packets */
	ret = PHY_MBOX_WRITE(phy, _target_addr, 0x3);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_CONTEXT_UPD_CTRL set fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_config_ing_misc_ctrl(struct gpy211_device *phy)
{
	int ret;
	struct misc_control misc_ctrl = {
		.mc_latency_fix = 128,
		.static_bypass = 0,
		.nm_macsec_en = 1,
		.validate_frames = SAM_FCA_VALIDATE_STRICT,
		.sectag_after_vlan = 1,
	};

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Set 'MISC_CONTROL' to do not update the context for bad packets */
	ret = gpy2xx_msec_config_ing_misc_ctrl(phy, &misc_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_config_ing_misc_ctrl fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_config_ing_sa_nm_xcp(struct gpy211_device *phy)
{
	int ret;
	struct sa_nonmatch_fca nm_xcp = {
		.pkt_type = SA_NM_SECY_ALL_TAGGED,
		.flow_type = SA_NM_FCA_FLOW_DROP,
		.dest_port = SA_NM_FCA_DPT_CONTROL,
		.drop_non_reserved = 0,
		.drop_action = SA_NM_FCA_DROP_AS_CRC,
	};

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Set 'SA_NM_FLOW_NCP' flow control action */
	ret = gpy2xx_msec_config_ing_sa_nm_ncp(phy, &nm_xcp);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_config_ing_sa_nm_ncp fails\n");
		goto END;
	}

	/* Set 'SA_NM_FLOW_CP' flow control action */
	ret = gpy2xx_msec_config_ing_sa_nm_cp(phy, &nm_xcp);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_config_ing_sa_nm_cp fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_clear_ing_stats_summ(struct gpy211_device *phy)
{
	int ret;
	struct stats_summary xxx_summ = {
		.psa_sum_word = {0xFFFFFFFF},
		.glb_summ_word = 0xFFFFFFFF,
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
		.vlan_summ_word = {0},
#endif
	};

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Set SA expired/pn-thr/psa summary */
	ret = gpy2xx_msec_clear_ing_stats_summ(phy, &xxx_summ);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_clear_ing_stats_summ fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_config_ing_cc_ctrl(struct gpy211_device *phy)
{
	int ret;
	struct ing_cc_ctrl cc_ctrl = {
		.nm_act = 1,
		.nm_ctrl_act = 1,
	};

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Set 'IG_CC_CONTRO' for non-match action of ctrl & non-ctrl frames */
	ret = gpy2xx_msec_config_ing_cc_ctrl(phy, &cc_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_config_ing_misc_ctrl fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_clear_ing_psa_summ(struct gpy211_device *phy)
{
	int i, ret = 0;
	u32 _base_addr, _offset, _target_addr;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < (phy->nr_of_sas); i++) {
		_offset =  i * 4 + EIPI_COUNT_SUMMARY_SA0;
		_target_addr = _base_addr + _offset;
		/* Set 'COUNT_SUMMARY_SAx' for SA counters statistics summary */
		ret = PHY_MBOX_WRITE(phy, _target_addr, EIPI_COUNT_SUMMARY_SA0_SA_CNT_MASK);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_SAx set fails\n");
			goto END;
		}
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_check_ing_dev_sync_status(struct gpy211_device *phy)
{
	int i = 0, ret;
	u32 _base_addr, _offset, _target_addr, _sync_done;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset =  EIPI_COUNT_CONTROL;
	_target_addr = _base_addr + _offset;

	do {
		/* Check 'COUNT_CONTROL.reset_all' for sunc done */
		ret = PHY_MBOX_READ(phy, _target_addr, &_sync_done);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_CONTROL get fails\n");
			goto END;
		}

		_sync_done = FIELD_GET(_sync_done, EIPI_COUNT_CONTROL_RESET_ALL);
	} while ((_sync_done) && (++i < EIP160_MAX_SYNC_RETRY_COUNT));

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_config_ing_count_ctrl(struct gpy211_device *phy)
{
	int ret;
	struct count_control cnt_ctrl = {
		.reset_all = 0,
		.saturate_cntrs = 1,
		.auto_cntr_reset = 1,
		.reset_summary = 0,
	};

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Set 'COUNT_CONTROL' to set control options */
	ret = gpy2xx_msec_config_ing_count_ctrl(phy, &cnt_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_config_ing_count_ctrl fails\n");
		goto END;
	}

	cnt_ctrl.reset_all = 1;
	/* Set 'COUNT_CONTROL' to set control options */
	ret = gpy2xx_msec_config_ing_count_ctrl(phy, &cnt_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_config_ing_count_ctrl fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_config_ing_count_incen(struct gpy211_device *phy)
{
	int ret;
	struct count_incen cnt_inc = {
		.sa_inc_en = 0x7ff,
		.vlan_inc_en = 0,
		.global_inc_en = 0x3fff,
	};

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Set 'MISC_CONTROL' to do not update the context for bad packets */
	ret = gpy2xx_msec_config_ing_count_incen(phy, &cnt_inc);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_config_ing_count_incen fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_init_ing_dev(struct gpy211_device *phy)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	if (!phy->macsec_supported) {
		LOG_WARN("ERROR: MACSEC is not supported.\n");
		return -EINVAL;
	}

#if defined(NO_TARGET_TEST) && NO_TARGET_TEST
	return 1;
#endif

	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = _gpy2xx_msec_detect_ing_eip160(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_detect_ing_eip160 fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_detect_ing_eip62(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_detect_ing_eip62 fails\n");
		goto END;
	}

	_base_addr = EIPI_EIP_160S_I_32_SYSTEM_CONTROL_MODULE_BASE;
	_offset =  EIPI_EIP160_CONFIG;
	_target_addr = _base_addr + _offset;

	/* Read max no.of SA supported */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160_CONFIG read fails\n");
		goto END;
	}

	phy->nr_of_sas = FIELD_GET(_data, EIPI_EIP160_CONFIG_NR_OF_SAS);
#ifdef VERIFY_ENDIANNESS
	struct eip160_config eip_cfg;
	eip_cfg.raw_eip160_cfg = _data;
	LOG_CRIT("EIP cfg raw %x, stored %x\n", _data, eip_cfg.raw_eip160_cfg);
	LOG_CRIT("SA nums %x CCs %x, match-sci %x, reserved %x\n",
		 eip_cfg.nr_of_sas, eip_cfg.consist_checks, eip_cfg.match_sci, eip_cfg.reserved);
#endif
	ret = _gpy2xx_msec_clear_ing_tr_ram(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_clear_ing_tr_ram fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_config_ing_count_ctrl(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_config_ing_count_ctrl fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_config_ing_ctx_size(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_config_ing_ctx_size fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_config_ing_misc_ctrl(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_config_ing_misc_ctrl fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_config_ing_ctx_upd(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_config_ing_ctx_upd fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_config_ing_sa_nm_xcp(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_config_ing_sa_nm_xcp fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_config_ing_cc_ctrl(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_config_ing_cc_ctrl fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_clear_ing_stats_summ(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_clear_ing_stats_summ fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_clear_ing_psa_summ(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_clear_ing_psa_summ fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_check_ing_dev_sync_status(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_check_ing_dev_sync_status fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_config_ing_count_incen(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_config_ing_count_incen fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_detect_egr_eip160(struct gpy211_device *phy)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	struct eip160_config2 ext_cfg;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIPE_EIP_160S_E_32_SYSTEM_CONTROL_MODULE_BASE;
	_offset =  EIPE_EIP160_VERSION;
	_target_addr = _base_addr + _offset;

	/* Check EIP160 nuber and it's complement */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160_VERSION read fails for iteration\n");
		goto END;
	}

#ifdef VERIFY_ENDIANNESS
	{
		u32 x = 1, y = 0;
		y = (int)(((char *)&x)[0]);
		printf("%s", (y == 1) ? "LITTLE_ENDIAN" : "BIG_ENDIAN");
	}
	struct eip160_version eip_ver;
	eip_ver.raw_eip160_ver = _data;
	LOG_CRIT("EIP num raw %x, stored %x\n", _data, eip_ver.raw_eip160_ver);
	LOG_CRIT("EIP num %x compliment %x, patch-level %x, minor-ver %x, major-ver %x, reserved %x\n",
		 eip_ver.eip_nr, eip_ver.eip_nr_complement, eip_ver.patch_level, eip_ver.minor_version, eip_ver.major_version, eip_ver.reserved);
#endif

	if ((_data & 0xFFFFu) != EIP160_NR_CNR) {
		LOG_CRIT("EIP160 number mismatch\n");
		goto END;
	}

	_base_addr = EIPE_EIP_160S_E_32_SYSTEM_CONTROL_MODULE_BASE;
	_offset = EIPE_EIP160_CONFIG2;
	_target_addr = _base_addr + _offset;

	/* Gt EIP160_CONFIG2 data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160_CONFIG2 word get fails\n");
		goto END;
	}

	ext_cfg.raw_eip160_cfg2 = _data;

	if (ext_cfg.egress_only != 1) {
		LOG_CRIT("It is not configured for egress only\n");
		ret = -1;
		goto END;
	}

	_base_addr =  EIP_160S_EG_TR_PAGE0_BASE;
	_offset = EIP_160S_EG_TR_PAGE0_OFFSET;
	_target_addr = _base_addr + _offset;

	/* Read and Write test */
	ret = PHY_MBOX_WRITE(phy, _target_addr, 0xfedcba98);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160 test write fails\n");
		goto END;
	}

	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160 test read fails\n");
		goto END;
	}

	if (_data != 0xfedcba98) {
		LOG_CRIT("EIP160 test write & read fails\n");
		ret = -1;
		goto END;
	}

	/* Reset */
	ret = PHY_MBOX_WRITE(phy, _target_addr, 0x0);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160 test reset fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_detect_egr_eip62(struct gpy211_device *phy)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIPE_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;
	_offset =  EIPE_EIP62_VERSION;
	_target_addr = _base_addr + _offset;

	/* Check EIP62 nuber and it's complement */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_VERSION read fails\n");
		goto END;
	}

	if ((_data & 0xFFFFu) != EIP62_NR_CNR) {
		LOG_CRIT("EIP62 number mismatch\n");
		ret = -1;
		goto END;
	}

	_base_addr = EIPE_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;
	_offset =  EIPE_EIP62_SEQ_NUM_THRESHOLD;
	_target_addr = _base_addr + _offset;

	/* Read and Write test */
	ret = PHY_MBOX_WRITE(phy, _target_addr, 0x89abcdef);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62 test write fails\n");
		goto END;
	}

	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62 test read fails\n");
		goto END;
	}

	if (_data != 0x89abcdef) {
		LOG_CRIT("EIP160 test write & read fails\n");
		ret = -1;
		goto END;
	}

	/* Reset */
	ret = PHY_MBOX_WRITE(phy, _target_addr, 0x0);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62 test reset fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_clear_egr_tr_ram(struct gpy211_device *phy)
{
	int i, j, ret = 0;
	u32 _base_addr, _offset, _target_addr;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIP_160S_EG_TR_PAGE0_BASE;

	/* Clear Transform Record RAM */
	for (i = 0; i < (phy->nr_of_sas); i++) {
		_offset = ((i > 127) ? 0x10000 : 0) + EIP_160S_EG_TR_PAGE0_OFFSET + (i * EGR_MAX_TR_SIZE_BYTES);
		_target_addr = _base_addr + _offset;

		for (j = 0; j < 1; j++) { /* No-Need init full segment 'EGR_MAX_TR_SIZE_WORDS' */
			ret = PHY_MBOX_WRITE(phy, _target_addr + (j * 4), 0x0);

			if (ret < 0) {
				LOG_CRIT("ERROR: TR mem init fails\n");
				goto END;
			}
		}
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_config_egr_ctx_size(struct gpy211_device *phy)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _ctx_ctrl = 0;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIPE_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;
	_offset =  EIPE_EIP62_CONTEXT_CTRL;
	_target_addr = _base_addr + _offset;

	/* Get EIP62_CONTEXT_CTRL */
	ret = PHY_MBOX_READ(phy, _target_addr, &_ctx_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: Get EIP62_CONTEXT_CTRL fails\n");
		goto END;
	}

	FIELD_REPLACE(_ctx_ctrl, EGR_MAX_TR_SIZE_WORDS, EIPE_EIP62_CONTEXT_CTRL_CONTEXT_SIZE);

	/* Set EIP62_CONTEXT_CTRL.context_size */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _ctx_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: Set context_size fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_config_egr_ctx_upd(struct gpy211_device *phy)
{
	int ret;
	u32 _base_addr, _offset, _target_addr;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIPE_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;
	_offset =  EIPE_EIP62_CONTEXT_UPD_CTRL;
	_target_addr = _base_addr + _offset;

	/* Set 'EIP62_CONTEXT_UPD_CTRL.block_context_updates' to do not update the
		context for bad packets */
	ret = PHY_MBOX_WRITE(phy, _target_addr, 0x3);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_CONTEXT_UPD_CTRL set fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_config_egr_misc_ctrl(struct gpy211_device *phy)
{
	int ret;
	struct misc_control misc_ctrl = {
		.mc_latency_fix = 0,
		.static_bypass = 0,
		.nm_macsec_en = 1,
		.validate_frames = SAM_FCA_VALIDATE_STRICT,
		.sectag_after_vlan = 1,
	};

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Set 'MISC_CONTROL' to do not update the context for bad packets */
	ret = gpy2xx_msec_config_egr_misc_ctrl(phy, &misc_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_config_egr_misc_ctrl fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_config_egr_sa_nm_xcp(struct gpy211_device *phy)
{
	int ret;
	struct sa_nonmatch_fca nm_xcp = {
		.pkt_type = SA_NM_SECY_ALL_TAGGED,
		.flow_type = SA_NM_FCA_FLOW_DROP,
		.dest_port = SA_NM_FCA_DPT_COMMON,
		.drop_non_reserved = 0,
		.drop_action = SA_NM_FCA_DROP_AS_INTERNAL,
	};

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Set 'SA_NM_FLOW_NCP' flow control action */
	ret = gpy2xx_msec_config_egr_sa_nm_ncp(phy, &nm_xcp);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_config_egr_sa_nm_ncp fails\n");
		goto END;
	}

	/* Set 'SA_NM_FLOW_CP' flow control action */
	ret = gpy2xx_msec_config_egr_sa_nm_cp(phy, &nm_xcp);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_config_egr_sa_nm_cp fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_clear_egr_stats_summ(struct gpy211_device *phy)
{
	int ret;
	struct stats_summary xxx_summ = {
		.psa_sum_word = {0xFFFFFFFF},
		.glb_summ_word = 0xFFFFFFFF,
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
		.vlan_summ_word = {0},
#endif
	};

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Set SA expired/pn-thr/psa summary */
	ret = gpy2xx_msec_clear_egr_stats_summ(phy, &xxx_summ);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_clear_egr_stats_summ fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_clear_egr_psa_summ(struct gpy211_device *phy)
{
	int i, ret = 0;
	u32 _base_addr, _offset, _target_addr;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < (phy->nr_of_sas); i++) {
		_offset =  i * 4 + EIPE_COUNT_SUMMARY_SA0;
		_target_addr = _base_addr + _offset;
		/* Set 'COUNT_SUMMARY_SAx' for SA counters statistics summary */
		ret = PHY_MBOX_WRITE(phy, _target_addr, EIPE_COUNT_SUMMARY_SA0_SA_CNT_MASK);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_SAx set fails\n");
			goto END;
		}
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_check_egr_dev_sync_status(struct gpy211_device *phy)
{
	int i = 0, ret;
	u32 _base_addr, _offset, _target_addr, _sync_done;

	LOG_INFO("Entering func name :- %s\n", __func__);

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset =  EIPE_COUNT_CONTROL;
	_target_addr = _base_addr + _offset;

	do {
		/* Check 'COUNT_CONTROL.reset_all' for sunc done */
		ret = PHY_MBOX_READ(phy, _target_addr, &_sync_done);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_CONTROL get fails\n");
			goto END;
		}

		_sync_done = FIELD_GET(_sync_done, EIPE_COUNT_CONTROL_RESET_ALL);
	} while ((_sync_done) && (++i < EIP160_MAX_SYNC_RETRY_COUNT));

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_config_egr_count_ctrl(struct gpy211_device *phy)
{
	int ret;
	struct count_control cnt_ctrl = {
		.reset_all = 0,
		.saturate_cntrs = 1,
		.auto_cntr_reset = 1,
		.reset_summary = 0,
	};

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Set 'COUNT_CONTROL' to set control options */
	ret = gpy2xx_msec_config_egr_count_ctrl(phy, &cnt_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_config_egr_count_ctrl fails\n");
		goto END;
	}

	cnt_ctrl.reset_all = 1;
	/* Set 'COUNT_CONTROL' to set control options */
	ret = gpy2xx_msec_config_egr_count_ctrl(phy, &cnt_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_config_egr_count_ctrl fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_msec_config_egr_count_incen(struct gpy211_device *phy)
{
	int ret;
	struct count_incen cnt_inc = {
		.sa_inc_en = 0xf,
		.vlan_inc_en = 0,
		.global_inc_en = 0x1f,
	};

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Set 'COUNT_INCEN1x' to do not update the context for bad packets */
	ret = gpy2xx_msec_config_egr_count_incen(phy, &cnt_inc);

	if (ret < 0) {
		LOG_CRIT("ERROR: api gpy2xx_msec_config_egr_count_incen fails\n");
		goto END;
	}

END:
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_init_egr_dev(struct gpy211_device *phy)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	if (!phy->macsec_supported) {
		LOG_WARN("ERROR: MACSEC is not supported.\n");
		return -EINVAL;
	}

#if defined(NO_TARGET_TEST) && NO_TARGET_TEST
	return 1;
#endif

	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = _gpy2xx_msec_detect_egr_eip160(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_detect_egr_eip160 fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_detect_egr_eip62(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_detect_egr_eip62 fails\n");
		goto END;
	}

	_base_addr = EIPE_EIP_160S_E_32_SYSTEM_CONTROL_MODULE_BASE;
	_offset =  EIPE_EIP160_CONFIG;
	_target_addr = _base_addr + _offset;

	/* Read max no.of SA supported */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160_CONFIG read fails\n");
		goto END;
	}

	phy->nr_of_sas = FIELD_GET(_data, EIPE_EIP160_CONFIG_NR_OF_SAS);
#ifdef VERIFY_ENDIANNESS
	struct eip160_config eip_cfg;
	eip_cfg.raw_eip160_cfg = _data;
	LOG_CRIT("EIP cfg raw %x, stored %x\n", _data, eip_cfg.raw_eip160_cfg);
	LOG_CRIT("SA nums %x CCs %x, match-sci %x, reserved %x\n",
		 eip_cfg.nr_of_sas, eip_cfg.consist_checks, eip_cfg.match_sci, eip_cfg.reserved);
	/* Output
	EIP cfg raw 20, stored 20
	SA nums 20 CCs 0, match-sci 0, reserved 0
	*/
#endif
	ret = _gpy2xx_msec_clear_egr_tr_ram(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_clear_egr_tr_ram fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_config_egr_count_ctrl(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_config_egr_count_ctrl fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_config_egr_ctx_size(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_config_egr_ctx_size fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_config_egr_misc_ctrl(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_config_egr_misc_ctrl fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_config_egr_ctx_upd(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_config_egr_ctx_upd fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_config_egr_sa_nm_xcp(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_config_egr_sa_nm_xcp fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_clear_egr_stats_summ(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_clear_egr_stats_summ fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_clear_egr_psa_summ(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_clear_egr_psa_summ fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_check_egr_dev_sync_status(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_check_egr_dev_sync_status fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_config_egr_count_incen(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_config_egr_count_incen fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_cap(struct gpy211_device *phy,
			    struct eip160_hwcap *hw_cap)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || hw_cap == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_SYSTEM_CONTROL_MODULE_BASE;
	_offset = EIPI_EIP160_VERSION;
	_target_addr = _base_addr + _offset;

	/* Get EIP160_VERSION data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160_VERSION word get fails\n");
		goto END;
	}

	hw_cap->eip_ver.raw_eip160_ver = _data;

	_base_addr = EIPI_EIP_160S_I_32_SYSTEM_CONTROL_MODULE_BASE;
	_offset = EIPI_EIP160_CONFIG;
	_target_addr = _base_addr + _offset;

	/* Get EIP160_CONFIG data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160_CONFIG word get fails\n");
		goto END;
	}

	hw_cap->eip_cfg.raw_eip160_cfg = _data;

	_base_addr = EIPI_EIP_160S_I_32_SYSTEM_CONTROL_MODULE_BASE;
	_offset = EIPI_EIP160_CONFIG2;
	_target_addr = _base_addr + _offset;

	/* Gt EIP160_CONFIG2 data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160_CONFIG2 word get fails\n");
		goto END;
	}

	hw_cap->eip_cfg2.raw_eip160_cfg2 = _data;

	_base_addr = EIPI_EIP_201_EIP201_REGISTERS_MODULE_BASE;
	_offset = EIPI_AIC_OPTIONS;
	_target_addr = _base_addr + _offset;

	/* Get AIC_OPTIONS data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_OPTIONS word get fails\n");
		goto END;
	}

	hw_cap->aic_opt.raw_aic_opt = _data;

	_base_addr = EIPI_EIP_201_EIP201_REGISTERS_MODULE_BASE;
	_offset = EIPI_AIC_VERSION;
	_target_addr = _base_addr + _offset;

	/* Get AIC_VERSION data */
	ret = PHY_MBOX_READ(phy, _target_addr,	&_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_VERSION word get fails\n");
		goto END;
	}

	hw_cap->aic_ver.raw_aic_ver = _data;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_cap(struct gpy211_device *phy,
			    struct eip160_hwcap *hw_cap)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || hw_cap == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_SYSTEM_CONTROL_MODULE_BASE;
	_offset = EIPE_EIP160_VERSION;
	_target_addr = _base_addr + _offset;

	/* Get EIP160_VERSION data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160_VERSION word get fails\n");
		goto END;
	}

	hw_cap->eip_ver.raw_eip160_ver = _data;

	_base_addr = EIPE_EIP_160S_E_32_SYSTEM_CONTROL_MODULE_BASE;
	_offset = EIPE_EIP160_CONFIG;
	_target_addr = _base_addr + _offset;

	/* Get EIP160_CONFIG data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160_CONFIG word get fails\n");
		goto END;
	}

	hw_cap->eip_cfg.raw_eip160_cfg = _data;

	_base_addr = EIPE_EIP_160S_E_32_SYSTEM_CONTROL_MODULE_BASE;
	_offset = EIPE_EIP160_CONFIG2;
	_target_addr = _base_addr + _offset;

	/* Gt EIP160_CONFIG2 data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP160_CONFIG2 word get fails\n");
		goto END;
	}

	hw_cap->eip_cfg2.raw_eip160_cfg2 = _data;

	_base_addr = EIPE_EIP_201_EIP201_REGISTERS_MODULE_BASE;
	_offset = EIPE_AIC_OPTIONS;
	_target_addr = _base_addr + _offset;

	/* Get AIC_OPTIONS data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_OPTIONS word get fails\n");
		goto END;
	}

	hw_cap->aic_opt.raw_aic_opt = _data;

	_base_addr = EIPE_EIP_201_EIP201_REGISTERS_MODULE_BASE;
	_offset = EIPE_AIC_VERSION;
	_target_addr = _base_addr + _offset;

	/* Get AIC_VERSION data */
	ret = PHY_MBOX_READ(phy, _target_addr,	&_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_VERSION word get fails\n");
		goto END;
	}

	hw_cap->aic_ver.raw_aic_ver = _data;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

/* Populate CCW */
static int _gpy2xx_msec_pop_ccw(enum msec_dir dir, struct ctx_ctrl_word *ccw,
				u32 *_ccw)
{
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (dir == INGRESS_DIR) {
		if (ccw->ca_type == CA_AES_CTR_128) {
			if (ccw->sn_type == SN_32_BIT)
				*_ccw = ING_32BPN_128KEY_DEF_CCW;
			else if (ccw->sn_type == SN_64_BIT)
				*_ccw = ING_64BPN_128KEY_DEF_CCW;
			else
				return -1;
		} else if (ccw->ca_type == CA_AES_CTR_256) {
			if (ccw->sn_type == SN_32_BIT)
				*_ccw = ING_32BPN_256KEY_DEF_CCW;
			else if (ccw->sn_type == SN_64_BIT)
				*_ccw = ING_64BPN_256KEY_DEF_CCW;
			else
				return -1;
		} else {
			return -1;
		}
	} else {
		if (ccw->ca_type == CA_AES_CTR_128) {
			if (ccw->sn_type == SN_32_BIT)
				*_ccw = EGR_32BPN_128KEY_DEF_CCW;
			else if (ccw->sn_type == SN_64_BIT)
				*_ccw = EGR_64BPN_128KEY_DEF_CCW;
			else
				return -1;
		} else if (ccw->ca_type == CA_AES_CTR_256) {
			if (ccw->sn_type == SN_32_BIT)
				*_ccw = EGR_32BPN_256KEY_DEF_CCW;
			else if (ccw->sn_type == SN_64_BIT)
				*_ccw = EGR_64BPN_256KEY_DEF_CCW;
			else
				return -1;
		} else
			return -1;

		/* Insert the variable field 'AN' */
		if (ccw->an < MACSEC_MAX_AN) {
			*_ccw = *_ccw | (ccw->an << CCW_EIPX_TR_CCW_AN_POS);
			/* FIELD_REPLACE(*_ccw, ccw->an, CCW_EIPX_TR_CCW_AN); */
		}  else
			return -1;
	}

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

/* Populate Ingress CCW */
static int _gpy2xx_msec_pop_ing_ccw(struct ctx_ctrl_word *ccw, u32 *_ccw)
{
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	ret = _gpy2xx_msec_pop_ccw(INGRESS_DIR, ccw, _ccw);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_build_ccw fails\n");
	}

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

/* Populate Egress CCW */
static int _gpy2xx_msec_pop_egr_ccw(struct ctx_ctrl_word *ccw, u32 *_ccw)
{
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	ret = _gpy2xx_msec_pop_ccw(EGRESS_DIR, ccw, _ccw);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_build_ccw fails\n");
	}

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

/* Populate AES Key */
static int _gpy2xx_msec_pop_key(struct crypto_params *cp, u32 *le_key)
{
#ifdef __KERNEL__
	int i;
#endif
	LOG_INFO("Entering func name :- %s\n", __func__);

#if defined(SAFE_C_LIB) && SAFE_C_LIB
	memcpy_s((u8 *)le_key, MACSEC_KEY_LEN_BYTE, cp->key, MACSEC_KEY_LEN_BYTE);
#else
	memcpy((u8 *)le_key, cp->key, MACSEC_KEY_LEN_BYTE);
#endif
#ifdef __KERNEL__

	for (i = 0; i < (MACSEC_KEY_LEN_BYTE / 4); i++)
		le_key[i] = cpu_to_le32(le_key[i]);

#endif

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

/* Populate AES HKey */
static int _gpy2xx_msec_pop_hkey(struct crypto_params *cp, u32 *le_hkey)
{
#ifdef __KERNEL__
	int i;
#endif
	LOG_INFO("Entering func name :- %s\n", __func__);

#if defined(SAFE_C_LIB) && SAFE_C_LIB
	memcpy_s((u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE, cp->hkey, MACSEC_HKEY_LEN_BYTE);
#else
	memcpy((u8 *)le_hkey, cp->hkey, MACSEC_HKEY_LEN_BYTE);
#endif
#ifdef __KERNEL__

	for (i = 0; i < (MACSEC_HKEY_LEN_BYTE / 4); i++)
		le_hkey[i] = cpu_to_le32(le_hkey[i]);

#endif

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

/* Populate IV */
static int _gpy2xx_msec_pop_iv(struct crypto_params *cp, u32 *le_iv)
{
#ifdef __KERNEL__
	int i;
#endif
	LOG_INFO("Entering func name :- %s\n", __func__);

#if defined(SAFE_C_LIB) && SAFE_C_LIB
	memcpy_s((u8 *)le_iv, MACSEC_SCI_LEN_BYTE, cp->sci, MACSEC_SCI_LEN_BYTE);
#else
	memcpy((u8 *)le_iv, cp->sci, MACSEC_SCI_LEN_BYTE);
#endif
#ifdef __KERNEL__

	for (i = 0; i < (MACSEC_SCI_LEN_BYTE / 4); i++)
		le_iv[i] = cpu_to_le32(le_iv[i]);

#endif

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

/* Populate Context Salt */
static int _gpy2xx_msec_pop_csalt(struct crypto_params *cp, u32 *le_ctx_salt)
{
#ifdef __KERNEL__
	int i;
#endif
	u32 le_short_sci;
	LOG_INFO("Entering func name :- %s\n", __func__);

#if defined(SAFE_C_LIB) && SAFE_C_LIB
	memcpy_s((u8 *)le_ctx_salt, MACSEC_SALT_LEN_BYTE, cp->c_salt.salt, MACSEC_SALT_LEN_BYTE);
	memcpy_s((u8 *)&le_short_sci, MACSEC_SSCI_LEN_BYTE, cp->c_salt.s_sci, MACSEC_SSCI_LEN_BYTE);
#else
	memcpy((u8 *)le_ctx_salt, cp->c_salt.salt, MACSEC_SALT_LEN_BYTE);
	memcpy((u8 *)&le_short_sci, cp->c_salt.s_sci, MACSEC_SSCI_LEN_BYTE);
#endif
	le_ctx_salt[0] = le_ctx_salt[0] ^ le_short_sci;
#ifdef __KERNEL__

	for (i = 0; i < (MACSEC_SALT_LEN_BYTE / 4); i++)
		le_ctx_salt[i] = cpu_to_le32(le_ctx_salt[i]);

#endif

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

/* Populate SA Control Word */
static int _gpy2xx_msec_pop_sa_upd_ctrl(struct sa_update_ctrl *sa_uctrl,
					u32 *_sa_upd_ctrl)
{
	LOG_INFO("Entering func name :- %s\n", __func__);
	*_sa_upd_ctrl = 0;
	FIELD_REPLACE(*_sa_upd_ctrl, sa_uctrl->sa_index, SA_UPDATE_SA_INDEX);
	FIELD_REPLACE(*_sa_upd_ctrl, sa_uctrl->sa_expired_irq,
		      SA_UPDATE_SA_EXPIRED_IRQ);
	FIELD_REPLACE(*_sa_upd_ctrl, sa_uctrl->sa_index_valid,
		      SA_UPDATE_SA_INDEX_VALID);
	FIELD_REPLACE(*_sa_upd_ctrl, sa_uctrl->flow_index, SA_UPDATE_FLOW_INDEX);
	FIELD_REPLACE(*_sa_upd_ctrl, sa_uctrl->sa_ind_update_en,
		      SA_UPDATE_SA_INDEX_UPDATE_EN);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

#pragma GCC push_options
#pragma GCC optimize ("O0")
int gpy2xx_msec_config_ing_tr(struct gpy211_device *phy,
			      struct transform_rec *in_tr)
{
	int i, _ctx_id, ret = -EINVAL;
	u8 _key_len;
	u32 _base_addr, _offset, _target_addr;
	u32 _ccw;
	u32 le_key[MACSEC_CA256_KEY_LEN_WORD], le_hkey[MACSEC_HKEY_LEN_WORD];
	u32 le_iv[MACSEC_SCI_LEN_WORD], le_ctx_salt[MACSEC_CSALT_LEN_WORD];
	u32 *_tr = NULL;
	u8 hkeyinput[1][16] = {
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
	};
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_tr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

#if !defined(NO_TARGET_TEST)

	/* Validate input params */
	/* Validate SA rule num range */
	if (in_tr->sa_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (sa_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);
#endif

	ret = _gpy2xx_msec_pop_ing_ccw(&in_tr->ccw, &_ccw);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_pop_ing_ccw fails\n");
		ret = -EINVAL;
		goto END;
	}

	ret = _gpy2xx_msec_pop_key(&in_tr->cp, le_key);
	_key_len = (in_tr->ccw.ca_type == CA_AES_CTR_128) ? 16 : 32;
	AES_Encrypt((u8 *)hkeyinput, in_tr->cp.hkey, in_tr->cp.key, _key_len);
	ret = _gpy2xx_msec_pop_hkey(&in_tr->cp, le_hkey);
	ret = _gpy2xx_msec_pop_iv(&in_tr->cp, le_iv);
	ret = _gpy2xx_msec_pop_csalt(&in_tr->cp, le_ctx_salt);

	_tr = os_alloc(ING_MAX_TR_SIZE_BYTES);

	if (!_tr) {
		LOG_CRIT("Memory alloc failed :- %s\n", __func__);
		ret = -ENOMEM;
		goto END;
	}

	memset(_tr, 0, ING_MAX_TR_SIZE_BYTES);

	/* Generate unique context_id */
#ifdef __KERNEL__
	get_random_bytes(&_ctx_id, 4);
#else
	_ctx_id = ((rand() & 0xff) << 0) | ((rand() & 0xff) << 8) |
		  ((rand() & 0xff) << 16) | ((rand() & 0xff) << 24);
#endif
	_ctx_id = _ctx_id & (~0x000000FF);
	_ctx_id = _ctx_id | (in_tr->sa_index);

	/* Build TR */
	if (in_tr->ccw.ca_type == CA_AES_CTR_128) {
		if (in_tr->ccw.sn_type == SN_32_BIT) {
			struct ing_tr_32bpn_128bak *target_tr =
				(struct ing_tr_32bpn_128bak *)_tr;
			target_tr->ccw = _ccw;
			target_tr->ctx_id = _ctx_id;
#if defined(SAFE_C_LIB) && SAFE_C_LIB
			memcpy_s(target_tr->key, MACSEC_CA128_KEY_LEN_BYTE, (u8 *)le_key, MACSEC_CA128_KEY_LEN_BYTE);
			memcpy_s(target_tr->hkey, MACSEC_HKEY_LEN_BYTE, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#else
			memcpy(target_tr->key, (u8 *)le_key, MACSEC_CA128_KEY_LEN_BYTE);
			memcpy(target_tr->hkey, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#endif

			if (in_tr->pn_rc.seq0 != 0)
				target_tr->seq = in_tr->pn_rc.seq0; /* Must be 1 for Ingress */
			else
				target_tr->seq = 1; /* Must be 1 for Ingress */

			target_tr->mask = in_tr->pn_rc.mask;
			target_tr->iv0 = le_iv[0];
			target_tr->iv1 = le_iv[1];
		} else {
			struct ing_tr_64bpn_128bak *target_tr =
				(struct ing_tr_64bpn_128bak *)_tr;
			target_tr->ccw = _ccw;
			target_tr->ctx_id = _ctx_id;
#if defined(SAFE_C_LIB) && SAFE_C_LIB
			memcpy_s(target_tr->key, MACSEC_CA128_KEY_LEN_BYTE, (u8 *)le_key, MACSEC_CA128_KEY_LEN_BYTE);
			memcpy_s(target_tr->hkey, MACSEC_HKEY_LEN_BYTE, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#else
			memcpy(target_tr->key, (u8 *)le_key, MACSEC_CA128_KEY_LEN_BYTE);
			memcpy(target_tr->hkey, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#endif

			if (in_tr->pn_rc.seq0 != 0)
				target_tr->seq0 = in_tr->pn_rc.seq0; /* Must be 1 for Ingress */
			else
				target_tr->seq0 = 1; /* Must be 1 for Ingress */

			target_tr->seq1 = in_tr->pn_rc.seq1; /* Must be 0 for Ingress */

			if (in_tr->pn_rc.mask > 0x40000000) /* According to IEEE 802.1AEbw */
				target_tr->mask = 0x40000000;
			else
				target_tr->mask = in_tr->pn_rc.mask;

			target_tr->iv0 = le_ctx_salt[0];
			target_tr->iv1 = le_ctx_salt[1];
			target_tr->iv2 = le_ctx_salt[2];
		}
	} else {
		if (in_tr->ccw.sn_type == SN_32_BIT) {
			struct ing_tr_32bpn_256bak *target_tr =
				(struct ing_tr_32bpn_256bak *)_tr;
			target_tr->ccw = _ccw;
			target_tr->ctx_id = _ctx_id;
#if defined(SAFE_C_LIB) && SAFE_C_LIB
			memcpy_s(target_tr->key, MACSEC_CA256_KEY_LEN_BYTE, (u8 *)le_key, MACSEC_CA256_KEY_LEN_BYTE);
			memcpy_s(target_tr->hkey, MACSEC_HKEY_LEN_BYTE, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#else
			memcpy(target_tr->key, (u8 *)le_key, MACSEC_CA256_KEY_LEN_BYTE);
			memcpy(target_tr->hkey, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#endif

			if (in_tr->pn_rc.seq0 != 0)
				target_tr->seq = in_tr->pn_rc.seq0; /* Must be 1 for Ingress */
			else
				target_tr->seq = 1; /* Must be 1 for Ingress */

			target_tr->mask = in_tr->pn_rc.mask;
			target_tr->iv0 = le_iv[0];
			target_tr->iv1 = le_iv[1];
		} else {
			struct ing_tr_64bpn_256bak *target_tr =
				(struct ing_tr_64bpn_256bak *)_tr;
			target_tr->ccw = _ccw;
			target_tr->ctx_id = _ctx_id;
#if defined(SAFE_C_LIB) && SAFE_C_LIB
			memcpy_s(target_tr->key, MACSEC_CA256_KEY_LEN_BYTE, (u8 *)le_key, MACSEC_CA256_KEY_LEN_BYTE);
			memcpy_s(target_tr->hkey, MACSEC_HKEY_LEN_BYTE, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#else
			memcpy(target_tr->key, (u8 *)le_key, MACSEC_CA256_KEY_LEN_BYTE);
			memcpy(target_tr->hkey, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#endif

			if (in_tr->pn_rc.seq0 != 0)
				target_tr->seq0 = in_tr->pn_rc.seq0; /* Must be 1 for Ingress */
			else
				target_tr->seq0 = 1; /* Must be 1 for Ingress */

			target_tr->seq1 = in_tr->pn_rc.seq1; /* Must be 0 for Ingress */

			if (in_tr->pn_rc.mask > 0x40000000) /* According to IEEE 802.1AEbw */
				target_tr->mask = 0x40000000;
			else
				target_tr->mask = in_tr->pn_rc.mask;

			target_tr->iv0 = le_ctx_salt[0];
			target_tr->iv1 = le_ctx_salt[1];
			target_tr->iv2 = le_ctx_salt[2];
		}
	}

	_base_addr = EIP_160S_IG_TR_PAGE0_BASE + EIP_160S_IG_TR_PAGE0_OFFSET +
		     ((in_tr->sa_index > 127) ? 0x10000 : 0);
	_offset = (in_tr->sa_index) * ING_MAX_TR_SIZE_BYTES;
	_target_addr = _base_addr + _offset;

#if defined(NO_TARGET_TEST) && NO_TARGET_TEST

	for (i = 0; i < ING_MAX_TR_SIZE_WORDS; i++) {
		pr_info("TRec[%02d] = %8x\n", i, _tr[i]);
	}

#else

	/* Set TR's data */
	for (i = 0; i < ING_MAX_TR_SIZE_WORDS; i++) {
		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), _tr[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: TR's write fails for iteration %d\n", i);
			goto END;
		}
	}

#endif

END:

	if (_tr != NULL) {
		memset(_tr, 0, sizeof(*_tr));
		os_free(_tr);
	}

#if !defined(NO_TARGET_TEST)
	phy->unlock(phy->lock_data);
	ret = 0;
#endif

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}
#pragma GCC pop_options

#pragma GCC push_options
#pragma GCC optimize ("O0")
int gpy2xx_msec_config_egr_tr(struct gpy211_device *phy,
			      struct transform_rec *in_tr)
{
	int i, _ctx_id, ret = -EINVAL;
	u8 _key_len;
	u32 _base_addr, _offset, _target_addr;
	u32 _ccw, _sa_upd_ctrl;
	u32 le_key[MACSEC_CA256_KEY_LEN_WORD], le_hkey[MACSEC_HKEY_LEN_WORD];
	u32 le_iv[MACSEC_SCI_LEN_WORD], le_ctx_salt[MACSEC_CSALT_LEN_WORD];
	u32 *_tr = NULL;
	u8 hkeyinput[1][16] = {
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
	};
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_tr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

#if !defined(NO_TARGET_TEST)

	/* Validate input params */
	/* Validate SA rule num range */
	if (in_tr->sa_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (sa_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);
#endif

	ret = _gpy2xx_msec_pop_egr_ccw(&in_tr->ccw, &_ccw);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_msec_pop_egr_ccw fails\n");
		goto END;
	}

	ret = _gpy2xx_msec_pop_key(&in_tr->cp, le_key);
	_key_len = (in_tr->ccw.ca_type == CA_AES_CTR_128) ? 16 : 32;
	AES_Encrypt((u8 *)hkeyinput, in_tr->cp.hkey, in_tr->cp.key, _key_len);
	ret = _gpy2xx_msec_pop_hkey(&in_tr->cp, le_hkey);
	ret = _gpy2xx_msec_pop_iv(&in_tr->cp, le_iv);
	ret = _gpy2xx_msec_pop_csalt(&in_tr->cp, le_ctx_salt);
	ret = _gpy2xx_msec_pop_sa_upd_ctrl(&in_tr->sa_update, &_sa_upd_ctrl);

	_tr = os_alloc(EGR_MAX_TR_SIZE_BYTES);

	if (!_tr) {
		LOG_CRIT("Memory alloc failed :- %s\n", __func__);
		ret = -ENOMEM;
		goto END;
	}

	memset(_tr, 0, EGR_MAX_TR_SIZE_BYTES);

	/* Generate unique context_id */
#ifdef __KERNEL__
	get_random_bytes(&_ctx_id, 4);
#else
	_ctx_id = ((rand() & 0xff) << 0) | ((rand() & 0xff) << 8) |
		  ((rand() & 0xff) << 16) | ((rand() & 0xff) << 24);
#endif
	_ctx_id = _ctx_id & (~0x000000FF);
	_ctx_id = _ctx_id | (in_tr->sa_index);

	/* Build TR */
	if (in_tr->ccw.ca_type == CA_AES_CTR_128) {
		if (in_tr->ccw.sn_type == SN_32_BIT) {
			struct egr_tr_32bpn_128bak *target_tr =
				(struct egr_tr_32bpn_128bak *)_tr;
			target_tr->ccw = _ccw;
			target_tr->ctx_id = _ctx_id;
#if defined(SAFE_C_LIB) && SAFE_C_LIB
			memcpy_s(target_tr->key, MACSEC_CA128_KEY_LEN_BYTE, (u8 *)le_key, MACSEC_CA128_KEY_LEN_BYTE);
			memcpy_s(target_tr->hkey, MACSEC_HKEY_LEN_BYTE, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#else
			memcpy(target_tr->key, (u8 *)le_key, MACSEC_CA128_KEY_LEN_BYTE);
			memcpy(target_tr->hkey, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#endif
			target_tr->seq = in_tr->pn_rc.seq0;
			target_tr->iv0 = le_iv[0];
			target_tr->iv1 = le_iv[1];
			target_tr->sa_upd_ctrl = _sa_upd_ctrl;
		} else {
			struct egr_tr_64bpn_128bak *target_tr =
				(struct egr_tr_64bpn_128bak *)_tr;
			target_tr->ccw = _ccw;
			target_tr->ctx_id = _ctx_id;
#if defined(SAFE_C_LIB) && SAFE_C_LIB
			memcpy_s(target_tr->key, MACSEC_CA128_KEY_LEN_BYTE, (u8 *)le_key, MACSEC_CA128_KEY_LEN_BYTE);
			memcpy_s(target_tr->hkey, MACSEC_HKEY_LEN_BYTE, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#else
			memcpy(target_tr->key, (u8 *)le_key, MACSEC_CA128_KEY_LEN_BYTE);
			memcpy(target_tr->hkey, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#endif
			target_tr->seq0 = in_tr->pn_rc.seq0;
			target_tr->seq1 = in_tr->pn_rc.seq1;
			target_tr->is0 = le_ctx_salt[0];
			target_tr->is1 = le_ctx_salt[1];
			target_tr->is2 = le_ctx_salt[2];
			target_tr->iv0 = le_iv[0];
			target_tr->iv1 = le_iv[1];
			target_tr->sa_upd_ctrl = _sa_upd_ctrl;
		}
	} else {
		if (in_tr->ccw.sn_type == SN_32_BIT) {
			struct egr_tr_32bpn_256bak *target_tr =
				(struct egr_tr_32bpn_256bak *)_tr;
			target_tr->ccw = _ccw;
			target_tr->ctx_id = _ctx_id;
#if defined(SAFE_C_LIB) && SAFE_C_LIB
			memcpy_s(target_tr->key, MACSEC_CA256_KEY_LEN_BYTE, (u8 *)le_key, MACSEC_CA256_KEY_LEN_BYTE);
			memcpy_s(target_tr->hkey, MACSEC_HKEY_LEN_BYTE, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#else
			memcpy(target_tr->key, (u8 *)le_key, MACSEC_CA256_KEY_LEN_BYTE);
			memcpy(target_tr->hkey, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#endif
			target_tr->seq = in_tr->pn_rc.seq0;
			target_tr->iv0 = le_iv[0];
			target_tr->iv1 = le_iv[1];
			target_tr->sa_upd_ctrl = _sa_upd_ctrl;
		} else {
			struct egr_tr_64bpn_256bak *target_tr =
				(struct egr_tr_64bpn_256bak *)_tr;
			target_tr->ccw = _ccw;
			target_tr->ctx_id = _ctx_id;
#if defined(SAFE_C_LIB) && SAFE_C_LIB
			memcpy_s(target_tr->key, MACSEC_CA256_KEY_LEN_BYTE, (u8 *)le_key, MACSEC_CA256_KEY_LEN_BYTE);
			memcpy_s(target_tr->hkey, MACSEC_HKEY_LEN_BYTE, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#else
			memcpy(target_tr->key, (u8 *)le_key, MACSEC_CA256_KEY_LEN_BYTE);
			memcpy(target_tr->hkey, (u8 *)le_hkey, MACSEC_HKEY_LEN_BYTE);
#endif
			target_tr->seq0 = in_tr->pn_rc.seq0;
			target_tr->seq1 = in_tr->pn_rc.seq1;
			target_tr->is0 = le_ctx_salt[0];
			target_tr->is1 = le_ctx_salt[1];
			target_tr->is2 = le_ctx_salt[2];
			target_tr->iv0 = le_iv[0];
			target_tr->iv1 = le_iv[1];
			target_tr->sa_upd_ctrl = _sa_upd_ctrl;
		}
	}

	_base_addr = EIP_160S_EG_TR_PAGE0_BASE + EIP_160S_EG_TR_PAGE0_OFFSET +
		     ((in_tr->sa_index > 127) ? 0x10000 : 0);
	_offset = (in_tr->sa_index) * EGR_MAX_TR_SIZE_BYTES;
	_target_addr = _base_addr + _offset;

#if defined(NO_TARGET_TEST) && NO_TARGET_TEST

	for (i = 0; i < EGR_MAX_TR_SIZE_WORDS; i++) {
		pr_info("TRec[%02d] = %8x\n", i, _tr[i]);
	}

#else

	/* Set TR's data */
	for (i = 0; i < EGR_MAX_TR_SIZE_WORDS; i++) {
		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), _tr[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: TR's write fails for iteration %d\n", i);
			goto END;
		}
	}

#endif

END:

	if (_tr != NULL) {
		memset(_tr, 0, sizeof(*_tr));
		os_free(_tr);
	}

#if !defined(NO_TARGET_TEST)
	phy->unlock(phy->lock_data);
	ret = 0;
#endif

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}
#pragma GCC pop_options

int gpy2xx_msec_update_egr_sa_cw(struct gpy211_device *phy,
				 struct transform_rec *in_tr)
{
	int ret = -EINVAL;
	u32 _base_addr, _offset, _target_addr;
	u32 _sa_upd_ctrl, _sa_upd_offset;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_tr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (in_tr->sa_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (sa_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = _gpy2xx_msec_pop_sa_upd_ctrl(&in_tr->sa_update, &_sa_upd_ctrl);

	/* Compute  SA Update Control word offset */
	if (in_tr->ccw.ca_type == CA_AES_CTR_128) {
		if (in_tr->ccw.sn_type == SN_32_BIT) {
			//struct egr_tr_32bpn_128bak *target_tr;
			_sa_upd_offset = 15 * 4;
		} else {
			//struct egr_tr_64bpn_128bak *target_tr;
			_sa_upd_offset = 19 * 4;
		}
	} else {
		if (in_tr->ccw.sn_type == SN_32_BIT) {
			//struct egr_tr_32bpn_256bak *target_tr;
			_sa_upd_offset = 19 * 4;
		} else {
			//struct egr_tr_64bpn_256bak *target_tr;
			_sa_upd_offset = 23 * 4;
		}
	}

	_base_addr = EIP_160S_EG_TR_PAGE0_BASE + EIP_160S_EG_TR_PAGE0_OFFSET +
		     ((in_tr->sa_index > 127) ? 0x10000 : 0);
	_offset = (in_tr->sa_index % 128) * EGR_MAX_TR_SIZE_BYTES;
	_target_addr = _base_addr + _offset + _sa_upd_offset;

	/* Set TR's SA Update Control word */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _sa_upd_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: TR's Sa Update Control word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_tr(struct gpy211_device *phy,
			   struct raw_trans_rec *out_tr)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || out_tr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (out_tr->sa_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (sa_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	memset(out_tr->raw_trans_rec, 0, (EGR_MAX_TR_SIZE_WORDS * sizeof(u32)));

	_base_addr = EIP_160S_IG_TR_PAGE0_BASE + EIP_160S_IG_TR_PAGE0_OFFSET +
		     ((out_tr->sa_index > 127) ? 0x10000 : 0);
	_offset = ((out_tr->sa_index) % 128) * (ING_MAX_TR_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

	/* Get TR's data */
	for (i = 0; i < ING_MAX_TR_SIZE_WORDS; i++) {
		ret = PHY_MBOX_READ(phy, _target_addr + (i * 4), &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: TR read fails for iteration %d\n", i);
			goto END;
		}

		out_tr->raw_trans_rec[i] = _data;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_tr(struct gpy211_device *phy,
			   struct raw_trans_rec *out_tr)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || out_tr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (out_tr->sa_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (sa_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	memset(out_tr->raw_trans_rec, 0, (EGR_MAX_TR_SIZE_WORDS * sizeof(u32)));

	_base_addr = EIP_160S_EG_TR_PAGE0_BASE + EIP_160S_EG_TR_PAGE0_OFFSET +
		     ((out_tr->sa_index > 127) ? 0x10000 : 0);
	_offset = ((out_tr->sa_index) % 128) * EGR_MAX_TR_SIZE_BYTES;
	_target_addr = _base_addr + _offset;

	/* Get TR's data */
	for (i = 0; i < EGR_MAX_TR_SIZE_WORDS; i++) {
		ret = PHY_MBOX_READ(phy, _target_addr + (i * 4), &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: TR read fails for iteration %d\n", i);
			goto END;
		}

		out_tr->raw_trans_rec[i] = _data;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_pn(struct gpy211_device *phy,
			   struct sa_current_pn *curr_pn)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data, _sn_type, _ca_type;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || curr_pn == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (curr_pn->sa_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (sa_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIP_160S_IG_TR_PAGE0_BASE + EIP_160S_IG_TR_PAGE0_OFFSET +
		     ((curr_pn->sa_index > 127) ? 0x10000 : 0);
	_offset = ((curr_pn->sa_index) % 128) * (ING_MAX_TR_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

	/* Get TR's CCW */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: CCW read fails\n");
		goto END;
	}

	_sn_type = FIELD_GET(_data, CCW_EIPX_TR_CCW_SN);
	_ca_type = FIELD_GET(_data, CCW_EIPX_TR_CCW_CA);

	/* Compute Current Sequence Number word offset */
	if (_ca_type == CA_AES_CTR_128) {
		//struct egr_tr_32bpn_128bak *target_tr;
		//struct egr_tr_64bpn_128bak *target_tr;
		_offset += 10 * 4;
	} else {
		//struct egr_tr_32bpn_256bak *target_tr;
		//struct egr_tr_64bpn_256bak *target_tr;
		_offset += 14 * 4;
	}

	_target_addr = _base_addr + _offset;

	/* Get TR's SN-0 */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: SN-0 read fails\n");
		goto END;
	}

	curr_pn->curr_pn = _data;

	if (_sn_type == SN_64_BIT) {
		/* Get TR's SN-1 */
		ret = PHY_MBOX_READ(phy, _target_addr + 4, &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN-1 read fails\n");
			goto END;
		}

		curr_pn->curr_pn |= ((u64)_data << 32);
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_pn(struct gpy211_device *phy,
			   struct sa_current_pn *curr_pn)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data, _sn_type, _ca_type;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || curr_pn == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (curr_pn->sa_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (sa_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIP_160S_EG_TR_PAGE0_BASE + EIP_160S_EG_TR_PAGE0_OFFSET +
		     ((curr_pn->sa_index > 127) ? 0x10000 : 0);
	_offset = ((curr_pn->sa_index) % 128) * (EGR_MAX_TR_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

	/* Get TR's CCW */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: CCW read fails\n");
		goto END;
	}

	_sn_type = FIELD_GET(_data, CCW_EIPX_TR_CCW_SN);
	_ca_type = FIELD_GET(_data, CCW_EIPX_TR_CCW_CA);

	/* Compute Current Sequence Number word offset */
	if (_ca_type == CA_AES_CTR_128) {
		//struct egr_tr_32bpn_128bak *target_tr;
		//struct egr_tr_64bpn_128bak *target_tr;
		_offset += 10 * 4;
	} else {
		//struct egr_tr_32bpn_256bak *target_tr;
		//struct egr_tr_64bpn_256bak *target_tr;
		_offset += 14 * 4;
	}

	_target_addr = _base_addr + _offset;

	/* Get TR's SN-0 */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: SN-0 read fails\n");
		goto END;
	}

	curr_pn->curr_pn = _data;

	if (_sn_type == SN_64_BIT) {
		/* Get TR's SN-1 */
		ret = PHY_MBOX_READ(phy, _target_addr + 4, &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN-1 read fails\n");
			goto END;
		}

		curr_pn->curr_pn |= ((u64)_data << 32);
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_ing_tr(struct gpy211_device *phy,
			     const struct transform_rec *in_tr)
{
	int i, ret = -EINVAL;
	u32 _base_addr, _offset, _target_addr;
	u32 *_tr = NULL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_tr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (in_tr->sa_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (sa_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = _is_sam_in_flight_safe(phy, INGRESS_DIR);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _is_sam_in_flight_safe fails\n");
		goto END;
	}

	_tr = os_alloc(ING_MAX_TR_SIZE_BYTES);

	if (!_tr) {
		LOG_CRIT("Memory alloc failed :- %s\n", __func__);
		ret = -ENOMEM;
		goto END;
	}

	memset(_tr, 0, ING_MAX_TR_SIZE_BYTES);

	_base_addr = EIP_160S_IG_TR_PAGE0_BASE + EIP_160S_IG_TR_PAGE0_OFFSET +
		     ((in_tr->sa_index > 127) ? 0x10000 : 0);
	_offset = (in_tr->sa_index) * ING_MAX_TR_SIZE_BYTES;
	_target_addr = _base_addr + _offset;

	/* Set TR's data */
	for (i = 0; i < ING_MAX_TR_SIZE_WORDS; i++) {
		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), _tr[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: TR's write fails for iteration %d\n", i);
			goto END;
		}
	}

END:

	if (_tr != NULL) {
		memset(_tr, 0, sizeof(*_tr));
		os_free(_tr);
	}

	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_egr_tr(struct gpy211_device *phy,
			     const struct transform_rec *in_tr)
{
	int i, ret = -EINVAL;
	u32 _base_addr, _offset, _target_addr;
	u32 *_tr = NULL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_tr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (in_tr->sa_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (sa_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = _is_sam_in_flight_safe(phy, EGRESS_DIR);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _is_sam_in_flight_safe fails\n");
		goto END;
	}

	_tr = os_alloc(EGR_MAX_TR_SIZE_BYTES);

	if (!_tr) {
		LOG_CRIT("Memory alloc failed :- %s\n", __func__);
		ret = -ENOMEM;
		goto END;
	}

	memset(_tr, 0, EGR_MAX_TR_SIZE_BYTES);

	_base_addr = EIP_160S_EG_TR_PAGE0_BASE + EIP_160S_EG_TR_PAGE0_OFFSET +
		     ((in_tr->sa_index > 127) ? 0x10000 : 0);
	_offset = (in_tr->sa_index) * EGR_MAX_TR_SIZE_BYTES;
	_target_addr = _base_addr + _offset;

	/* Set TR's data */
	for (i = 0; i < EGR_MAX_TR_SIZE_WORDS; i++) {
		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), _tr[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: TR's write fails for iteration %d\n", i);
			goto END;
		}
	}

END:

	if (_tr != NULL) {
		memset(_tr, 0, sizeof(*_tr));
		os_free(_tr);
	}

	phy->unlock(phy->lock_data);
	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_sam_rule(struct gpy211_device *phy,
				    const struct sa_match_param *in_sam)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr;
	u32 *_sam = NULL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_sam == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

#if !defined(NO_TARGET_TEST)

	/* Validate input params */
	/* Validate SA rule num range */
	if (in_sam->rule_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (rule_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);
#endif

#ifdef DEBUG_PRINT
	LOG_CRIT("Raw misc %x mask %x extn %x\n", in_sam->misc_par.misc, in_sam->mask_par.mask, in_sam->extn_par.extn);
	LOG_CRIT("TCI-AN %x Match-pri %x Src-port %d K %d B %d T %d U %d C %d\n",
		 in_sam->misc_par.macsec_tci_an, in_sam->misc_par.match_priority,
		 in_sam->misc_par.source_port, in_sam->misc_par.kay_tag,
		 in_sam->misc_par.bad_tag, in_sam->misc_par.tagged,
		 in_sam->misc_par.untagged, in_sam->misc_par.control_packet);
	LOG_CRIT("TCI-mask %x SCI-mask %d CP-mask %d SP-mask %d ET-mask %d DA5-mask %d"
		 " DA2-mask %d DA0-mask %d SA4-mask %d SA3-mask %d SA1-mask %d\n",
		 in_sam->mask_par.tci_an_mask, in_sam->mask_par.macsec_sci_mask,
		 in_sam->mask_par.ctrl_packet_mask, in_sam->mask_par.source_port_mask,
		 in_sam->mask_par.mac_etype_mask, in_sam->mask_par.mac_da_5_mask,
		 in_sam->mask_par.mac_da_2_mask, in_sam->mask_par.mac_da_0_mask,
		 in_sam->mask_par.mac_sa_4_mask, in_sam->mask_par.mac_sa_3_mask,
		 in_sam->mask_par.mac_sa_1_mask);
	LOG_CRIT("Flow-ind %x Vlan-in-up %d Vlan-in %d\n", in_sam->extn_par.flow_index,
		 in_sam->extn_par.vlan_up_inner, in_sam->extn_par.vlan_id_inner);
#endif

	_sam = os_alloc(IE_MAX_SAM_SIZE_BYTES);

	if (!_sam) {
		LOG_CRIT("Memory alloc failed :- %s\n", __func__);
		ret = -ENOMEM;
		goto END;
	}

	memset(_sam, 0, IE_MAX_SAM_SIZE_BYTES);

	_sam[0] = ((in_sam->sa_mac[0] << 00) | (in_sam->sa_mac[1] <<  8) |
		   (in_sam->sa_mac[2] << 16) | (in_sam->sa_mac[3] << 24));
	_sam[1] = ((in_sam->sa_mac[4] << 00) | (in_sam->sa_mac[5] <<  8) |
		   (BYTE_SWAP_16BIT(in_sam->eth_type) << 16));
	_sam[2] = ((in_sam->da_mac[0] << 00) | (in_sam->da_mac[1] <<  8) |
		   (in_sam->da_mac[2] << 16) | (in_sam->da_mac[3] << 24));
	_sam[3] = ((in_sam->da_mac[4] << 00) | (in_sam->da_mac[5] <<  8) |
		   (in_sam->vlan_id << 16));
	_sam[4] = in_sam->misc_par.misc;
	/* Below two words (SCI) is only applicable to IG rule */
	_sam[5] = ((in_sam->sci[0] << 00) | (in_sam->sci[1] <<  8) |
		   (in_sam->sci[2] << 16) | (in_sam->sci[3] << 24));
	_sam[6] = ((in_sam->sci[4] << 00) | (in_sam->sci[5] <<  8) |
		   (in_sam->sci[6] << 16) | (in_sam->sci[7] << 24));
	_sam[7] = in_sam->mask_par.mask;
	_sam[8] = in_sam->extn_par.extn;

	_base_addr = EIPI_EIP_160S_I_32_SAM_RULES_PAGE0_MODULE_BASE +
		     ((in_sam->rule_index > 127) ? 0x10000 : 0);
	_offset = ((in_sam->rule_index) % 128) * (IE_MAX_SAM_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

#if defined(NO_TARGET_TEST) && NO_TARGET_TEST

	for (i = 0; i < IE_MAX_SAM_SIZE_WORDS; i++) {
		pr_info("SAM-Par[%02d] = %8x\n", i, _sam[i]);
	}

#else

	/* Set SAM's data */
	for (i = 0; i < IE_MAX_SAM_SIZE_WORDS; i++) {
		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), _sam[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: SAM write fails for iteration %d\n", i);
			goto END;
		}
	}

#endif

END:

	if (_sam != NULL) {
		memset(_sam, 0, sizeof(*_sam));
		os_free(_sam);
	}

#if !defined(NO_TARGET_TEST)
	phy->unlock(phy->lock_data);
	ret = 0;
#endif

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_sam_rule(struct gpy211_device *phy,
				    const struct sa_match_param *in_sam)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr;
	u32 *_sam = NULL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_sam == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

#if !defined(NO_TARGET_TEST)

	/* Validate input params */
	/* Validate SA rule num range */
	if (in_sam->rule_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (rule_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);
#endif

	_sam = os_alloc(IE_MAX_SAM_SIZE_BYTES);

	if (!_sam) {
		LOG_CRIT("Memory alloc failed :- %s\n", __func__);
		ret = -ENOMEM;
		goto END;
	}

	memset(_sam, 0, IE_MAX_SAM_SIZE_BYTES);

	_sam[0] = ((in_sam->sa_mac[0] << 00) | (in_sam->sa_mac[1] <<  8) |
		   (in_sam->sa_mac[2] << 16) | (in_sam->sa_mac[3] << 24));
	_sam[1] = ((in_sam->sa_mac[4] << 00) | (in_sam->sa_mac[5] <<  8) |
		   (BYTE_SWAP_16BIT(in_sam->eth_type) << 16));
	_sam[2] = ((in_sam->da_mac[0] << 00) | (in_sam->da_mac[1] <<  8) |
		   (in_sam->da_mac[2] << 16) | (in_sam->da_mac[3] << 24));
	_sam[3] = ((in_sam->da_mac[4] << 00) | (in_sam->da_mac[5] <<  8) |
		   (in_sam->vlan_id << 16));
	_sam[4] = in_sam->misc_par.misc;
	/* Below two words (SCI) are not applicable to EG rule */
	_sam[5] = ((in_sam->sci[0] << 00) | (in_sam->sci[1] <<  8) |
		   (in_sam->sci[2] << 16) | (in_sam->sci[3] << 24));
	_sam[6] = ((in_sam->sci[4] << 00) | (in_sam->sci[5] <<  8) |
		   (in_sam->sci[6] << 16) | (in_sam->sci[7] << 24));
	_sam[7] = in_sam->mask_par.mask;
	_sam[8] = in_sam->extn_par.extn;

	_base_addr = EIPE_EIP_160S_E_32_SAM_RULES_PAGE0_MODULE_BASE +
		     ((in_sam->rule_index > 127) ? 0x10000 : 0);
	_offset = ((in_sam->rule_index) % 128) * (IE_MAX_SAM_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

#if defined(NO_TARGET_TEST) && NO_TARGET_TEST

	for (i = 0; i < IE_MAX_SAM_SIZE_WORDS; i++) {
		pr_info("SAM-Par[%02d] = %8x\n", i, _sam[i]);
	}

#else

	/* Set SAM's data */
	for (i = 0; i < IE_MAX_SAM_SIZE_WORDS; i++) {
		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), _sam[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: SAM write fails for iteration %d\n", i);
			goto END;
		}
	}

#endif

END:

	if (_sam != NULL) {
		memset(_sam, 0, sizeof(*_sam));
		os_free(_sam);
	}

#if !defined(NO_TARGET_TEST)
	phy->unlock(phy->lock_data);
	ret = 0;
#endif

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_sam_rule(struct gpy211_device *phy,
				 struct raw_sam_param *out_sam)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || out_sam == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (out_sam->rule_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (rule_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	memset(out_sam->raw_sam_param, 0, IE_MAX_SAM_SIZE_BYTES);

	_base_addr = EIPI_EIP_160S_I_32_SAM_RULES_PAGE0_MODULE_BASE +
		     ((out_sam->rule_index > 127) ? 0x10000 : 0);
	_offset = ((out_sam->rule_index) % 128) * (IE_MAX_SAM_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

	/* Get SAM's data */
	for (i = 0; i < IE_MAX_SAM_SIZE_WORDS; i++) {
		ret = PHY_MBOX_READ(phy, _target_addr + (i * 4), &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: SAM read fails for iteration %d\n", i);
			goto END;
		}

		out_sam->raw_sam_param[i] = _data;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_sam_rule(struct gpy211_device *phy,
				 struct raw_sam_param *out_sam)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || out_sam == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (out_sam->rule_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (rule_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	memset(out_sam->raw_sam_param, 0, IE_MAX_SAM_SIZE_BYTES);

	_base_addr = EIPE_EIP_160S_E_32_SAM_RULES_PAGE0_MODULE_BASE +
		     ((out_sam->rule_index > 127) ? 0x10000 : 0);
	_offset = ((out_sam->rule_index) % 128) * (IE_MAX_SAM_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

	/* Get SAM's data */
	for (i = 0; i < IE_MAX_SAM_SIZE_WORDS; i++) {
		ret = PHY_MBOX_READ(phy, _target_addr + (i * 4), &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: SAM read fails for iteration %d\n", i);
			goto END;
		}

		out_sam->raw_sam_param[i] = _data;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_ing_sam_rule(struct gpy211_device *phy,
				   const struct sa_match_param *in_sam)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr;
	u32 *_sam = NULL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_sam == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (in_sam->rule_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (rule_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = _is_sam_in_flight_safe(phy, INGRESS_DIR);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _is_sam_in_flight_safe fails\n");
		goto END;
	}

	_sam = os_alloc(IE_MAX_SAM_SIZE_BYTES);

	if (!_sam) {
		LOG_CRIT("Memory alloc failed :- %s\n", __func__);
		ret = -ENOMEM;
		goto END;
	}

	memset(_sam, 0, IE_MAX_SAM_SIZE_BYTES);

	_base_addr = EIPI_EIP_160S_I_32_SAM_RULES_PAGE0_MODULE_BASE +
		     ((in_sam->rule_index > 127) ? 0x10000 : 0);
	_offset = ((in_sam->rule_index) % 128) * (IE_MAX_SAM_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

	/* Set SAM's data */
	for (i = 0; i < IE_MAX_SAM_SIZE_WORDS; i++) {
		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), _sam[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: SAM write fails for iteration %d\n", i);
			goto END;
		}
	}

END:

	if (_sam != NULL) {
		memset(_sam, 0, sizeof(*_sam));
		os_free(_sam);
	}

	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_egr_sam_rule(struct gpy211_device *phy,
				   const struct sa_match_param *in_sam)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr;
	u32 *_sam = NULL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_sam == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (in_sam->rule_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (rule_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = _is_sam_in_flight_safe(phy, EGRESS_DIR);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _is_sam_in_flight_safe fails\n");
		goto END;
	}

	_sam = os_alloc(IE_MAX_SAM_SIZE_BYTES);

	if (!_sam) {
		LOG_CRIT("Memory alloc failed :- %s\n", __func__);
		ret = -ENOMEM;
		goto END;
	}

	memset(_sam, 0, IE_MAX_SAM_SIZE_BYTES);

	_base_addr = EIPE_EIP_160S_E_32_SAM_RULES_PAGE0_MODULE_BASE +
		     ((in_sam->rule_index > 127) ? 0x10000 : 0);
	_offset = ((in_sam->rule_index) % 128) * (IE_MAX_SAM_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

	/* Set SAM's data */
	for (i = 0; i < IE_MAX_SAM_SIZE_WORDS; i++) {
		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), _sam[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: SAM write fails for iteration %d\n", i);
			goto END;
		}
	}

END:

	if (_sam != NULL) {
		memset(_sam, 0, sizeof(*_sam));
		os_free(_sam);
	}

	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_vlan_parse(struct gpy211_device *phy,
				      const struct sam_vlan_parse *parse_vlan)
{
	int ret;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || parse_vlan == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
	_offset = EIPI_SAM_CP_TAG;
	_target_addr = _base_addr + _offset;

	ret = PHY_MBOX_WRITE(phy, _target_addr, parse_vlan->outer_tag.raw_ocp_tag);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM VLAN control write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_vlan_parse(struct gpy211_device *phy,
				      const struct sam_vlan_parse *parse_vlan)
{
	int ret;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || parse_vlan == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
	_offset = EIPE_SAM_CP_TAG;
	_target_addr = _base_addr + _offset;

	ret = PHY_MBOX_WRITE(phy, _target_addr, parse_vlan->outer_tag.raw_ocp_tag);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM VLAN control write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_sam_fca(struct gpy211_device *phy,
				   const struct sa_match_fca *sam_fca)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _flow_ctrl = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sam_fca == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (sam_fca->flow_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (flow_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Validate Flow Control Action params */
	if ((sam_fca->flow_type > SAM_FCA_FLOW_EGRESS) || (sam_fca->dest_port > SAM_FCA_DPT_UNCONTROL) ||
	    (sam_fca->drop_non_reserved > 1) || (sam_fca->flow_crypt_auth > 1) ||
#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	    (sam_fca->drop_action > SAM_FCA_NO_DROP) ||
#else
	    (sam_fca->drop_action > SAM_FCA_DROP_AS_INTERNAL) ||
#endif
	    (sam_fca->replay_protect > 1) || (sam_fca->sa_in_use > 1) ||
	    (sam_fca->validate_frames > SAM_FCA_VALIDATE_STRICT)) {
		LOG_WARN("WARN: Invalid input Flow Control Action params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_FLOW_CONTROL_PAGE0_MODULE_BASE +
		     ((sam_fca->flow_index > 127) ? 0x10000 : 0);
	_offset = (sam_fca->flow_index) * IE_MAX_SAM_FCA_BYTES;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_flow_ctrl, sam_fca->flow_type, EIPI_SAM_FLOW_CTRL_0_FLOW_TYPE);
	FIELD_REPLACE(_flow_ctrl, sam_fca->dest_port, EIPI_SAM_FLOW_CTRL_0_DEST_PORT);
	FIELD_REPLACE(_flow_ctrl, sam_fca->drop_non_reserved, EIPI_SAM_FLOW_CTRL_0_DROP_NON_RESERVED);
	FIELD_REPLACE(_flow_ctrl, sam_fca->flow_crypt_auth, EIPI_SAM_FLOW_CTRL_0_FLOW_CRYPT_AUTH);
	FIELD_REPLACE(_flow_ctrl, sam_fca->drop_action, EIPI_SAM_FLOW_CTRL_0_DROP_ACTION);
	FIELD_REPLACE(_flow_ctrl, sam_fca->sa_index, EIPI_SAM_FLOW_CTRL_0_SA_INDEX);
	FIELD_REPLACE(_flow_ctrl, sam_fca->replay_protect, EIPI_SAM_FLOW_CTRL_0_REPLAY_PROTECT);
	FIELD_REPLACE(_flow_ctrl, sam_fca->sa_in_use, EIPI_SAM_FLOW_CTRL_0_SA_IN_USE);
	FIELD_REPLACE(_flow_ctrl, sam_fca->validate_frames, EIPI_SAM_FLOW_CTRL_0_VALIDATE_FRAMES);

	/* Set Flow Ctrl Action data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _flow_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: Flow Control Action word set fails\n");
		goto END;
	}

	if ((sam_fca->flow_type == SAM_FCA_FLOW_BYPASS) &&
	    (sam_fca->flow_crypt_auth == 1)) {
		_base_addr = EIPI_EIP_160S_I_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
		_offset = EIPI_CRYPT_AUTH_CTRL;
		_target_addr = _base_addr + _offset;

		/* Set CRYPT_AUTH_CTRL data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, sam_fca->crypt_auth_bypass_len);

		if (ret < 0) {
			LOG_CRIT("ERROR: CRYPT_AUTH_CTRL word set fails\n");
			goto END;
		}
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_sam_fca(struct gpy211_device *phy,
				   const struct sa_match_fca *sam_fca)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _flow_ctrl = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sam_fca == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (sam_fca->flow_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (flow_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Validate Flow Control Action params */
	if ((sam_fca->flow_type > SAM_FCA_FLOW_EGRESS) || (sam_fca->dest_port > SAM_FCA_DPT_UNCONTROL) ||
	    (sam_fca->include_sci > 1) || (sam_fca->flow_crypt_auth > 1) ||
#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	    (sam_fca->drop_action > SAM_FCA_NO_DROP) ||
#else
	    (sam_fca->drop_action > SAM_FCA_DROP_AS_INTERNAL) ||
#endif
	    (sam_fca->protect_frame > 1) || (sam_fca->use_es > 1) ||
	    (sam_fca->use_scb > 1) || (sam_fca->tag_bypass_size > 1) ||
	    (sam_fca->sa_index_update > 1) || (sam_fca->conf_offset > 1) ||
	    (sam_fca->conf_protect > 1) || (sam_fca->sa_in_use > 1)) {
		LOG_WARN("WARN: Invalid input Flow Control Action params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_FLOW_CONTROL_PAGE0_MODULE_BASE +
		     ((sam_fca->flow_index > 127) ? 0x10000 : 0);
	_offset = (sam_fca->flow_index) * IE_MAX_SAM_FCA_BYTES;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_flow_ctrl, sam_fca->flow_type, EIPE_SAM_FLOW_CTRL_0_FLOW_TYPE);
	FIELD_REPLACE(_flow_ctrl, sam_fca->dest_port, EIPE_SAM_FLOW_CTRL_0_DEST_PORT);
	FIELD_REPLACE(_flow_ctrl, sam_fca->flow_crypt_auth, EIPE_SAM_FLOW_CTRL_0_FLOW_CRYPT_AUTH);
	FIELD_REPLACE(_flow_ctrl, sam_fca->drop_action, EIPE_SAM_FLOW_CTRL_0_DROP_ACTION);
	FIELD_REPLACE(_flow_ctrl, sam_fca->sa_index, EIPE_SAM_FLOW_CTRL_0_SA_INDEX);
	FIELD_REPLACE(_flow_ctrl, sam_fca->protect_frame, EIPE_SAM_FLOW_CTRL_0_PROTECT_FRAME);
	FIELD_REPLACE(_flow_ctrl, sam_fca->sa_in_use, EIPE_SAM_FLOW_CTRL_0_SA_IN_USE);
	FIELD_REPLACE(_flow_ctrl, sam_fca->include_sci, EIPE_SAM_FLOW_CTRL_0_INCLUDE_SCI);
	FIELD_REPLACE(_flow_ctrl, sam_fca->use_es, EIPE_SAM_FLOW_CTRL_0_USE_ES);
	FIELD_REPLACE(_flow_ctrl, sam_fca->use_scb, EIPE_SAM_FLOW_CTRL_0_USE_SCB);
	FIELD_REPLACE(_flow_ctrl, sam_fca->tag_bypass_size, EIPE_SAM_FLOW_CTRL_0_TAG_BYPASS_LEN);
	FIELD_REPLACE(_flow_ctrl, sam_fca->sa_index_update, EIPE_SAM_FLOW_CTRL_0_SA_INDEX_UPDATE);
	FIELD_REPLACE(_flow_ctrl, sam_fca->conf_offset, EIPE_SAM_FLOW_CTRL_0_CONFIDENTIALITY_OFFSET);
	FIELD_REPLACE(_flow_ctrl, sam_fca->conf_protect, EIPE_SAM_FLOW_CTRL_0_CONF_PROTECT);

	/* Set Flow Ctrl Action data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _flow_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: Flow Control Action word set fails\n");
		goto END;
	}

	if ((sam_fca->flow_type == SAM_FCA_FLOW_BYPASS) &&
	    (sam_fca->flow_crypt_auth == 1)) {
		_base_addr = EIPE_EIP_160S_E_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
		_offset = EIPE_CRYPT_AUTH_CTRL;
		_target_addr = _base_addr + _offset;

		/* Set CRYPT_AUTH_CTRL data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, sam_fca->crypt_auth_bypass_len);

		if (ret < 0) {
			LOG_CRIT("ERROR: CRYPT_AUTH_CTRL word set fails\n");
			goto END;
		}
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_sam_fca(struct gpy211_device *phy,
				struct sam_pkt_fca *sam_fca)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sam_fca == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (sam_fca->flow_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (flow_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_FLOW_CONTROL_PAGE0_MODULE_BASE +
		     ((sam_fca->flow_index > 127) ? 0x10000 : 0);
	_offset = (sam_fca->flow_index) * IE_MAX_SAM_FCA_BYTES;
	_target_addr = _base_addr + _offset;

	/* Get Flow Ctrl Action data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: Flow Control Action word get fails\n");
		goto END;
	}

	sam_fca->dec_enc.raw_fca_macsec = _data;

	if ((sam_fca->dec_enc.flow_type == SAM_FCA_FLOW_BYPASS) &&
	    (sam_fca->dec_enc.flow_crypt_auth == 1)) {
		_base_addr = EIPI_EIP_160S_I_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
		_offset = EIPI_CRYPT_AUTH_CTRL;
		_target_addr = _base_addr + _offset;

		/* Get CRYPT_AUTH_CTRL data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: CRYPT_AUTH_CTRL word get fails\n");
			goto END;
		}

		sam_fca->cabp_len.raw_fca_cac = _data;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_sam_fca(struct gpy211_device *phy,
				struct sam_pkt_fca *sam_fca)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sam_fca == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (sam_fca->flow_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (flow_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_FLOW_CONTROL_PAGE0_MODULE_BASE +
		     ((sam_fca->flow_index > 127) ? 0x10000 : 0);
	_offset = (sam_fca->flow_index) * IE_MAX_SAM_FCA_BYTES;
	_target_addr = _base_addr + _offset;

	/* Get Flow Ctrl Action data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: Flow Control Action word get fails\n");
		goto END;
	}

	sam_fca->dec_enc.raw_fca_macsec = _data;

	if ((sam_fca->dec_enc.flow_type == SAM_FCA_FLOW_BYPASS) &&
	    (sam_fca->dec_enc.flow_crypt_auth == 1)) {
		_base_addr = EIPE_EIP_160S_E_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
		_offset = EIPE_CRYPT_AUTH_CTRL;
		_target_addr = _base_addr + _offset;

		/* Get CRYPT_AUTH_CTRL data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: CRYPT_AUTH_CTRL word get fails\n");
			goto END;
		}

		sam_fca->cabp_len.raw_fca_cac = _data;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_ing_sam_fca(struct gpy211_device *phy,
				  const struct sa_match_fca *sam_fca)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _flow_ctrl = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sam_fca == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (sam_fca->flow_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (flow_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = _is_sam_in_flight_safe(phy, INGRESS_DIR);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _is_sam_in_flight_safe fails\n");
		goto END;
	}

	_base_addr = EIPI_EIP_160S_I_32_FLOW_CONTROL_PAGE0_MODULE_BASE +
		     ((sam_fca->flow_index > 127) ? 0x10000 : 0);
	_offset = (sam_fca->flow_index) * IE_MAX_SAM_FCA_BYTES;
	_target_addr = _base_addr + _offset;

	/* Set Flow Ctrl Action data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _flow_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: Flow Control Action word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_egr_sam_fca(struct gpy211_device *phy,
				  const struct sa_match_fca *sam_fca)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _flow_ctrl = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sam_fca == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (sam_fca->flow_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (flow_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = _is_sam_in_flight_safe(phy, EGRESS_DIR);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _is_sam_in_flight_safe fails\n");
		goto END;
	}

	_base_addr = EIPE_EIP_160S_E_32_FLOW_CONTROL_PAGE0_MODULE_BASE +
		     ((sam_fca->flow_index > 127) ? 0x10000 : 0);
	_offset = (sam_fca->flow_index) * IE_MAX_SAM_FCA_BYTES;
	_target_addr = _base_addr + _offset;

	/* Set Flow Ctrl Action data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _flow_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: Flow Control Action word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_sam_eex(struct gpy211_device *phy,
				   const struct raw_sam_ee *in_ee)
{
	int i, ret = 0;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_ee == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SAM Entry Enable feature range */
	if (in_ee->eex_type > SAM_ENTRY_CLEAR) {
		LOG_WARN("WARN: Invalid input (eex_type) - SAM Entry Enable feature\n");
		return -EINVAL;
	}

#if !defined(EN_MSEC_DEBUG_ACCESS)

	if (in_ee->eex_type == SAM_ENTRY_ENABLE) {
		LOG_WARN("WARN: SAM Entry Enable option is for debugging only\n");
		return -EINVAL;
	}

#endif

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL_MODULE_BASE;

#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS

	if (in_ee->eex_type == SAM_ENTRY_ENABLE)
		_offset = EIPI_SAM_ENTRY_ENABLE1;
	else if (in_ee->eex_type == SAM_ENTRY_TOGGLE)
#else
	if (in_ee->eex_type == SAM_ENTRY_TOGGLE)
#endif
		_offset = EIPI_SAM_ENTRY_TOGGLE1;
	else if (in_ee->eex_type == SAM_ENTRY_SET)
		_offset = EIPI_SAM_ENTRY_SET1;
	else
		_offset = EIPI_SAM_ENTRY_CLEAR1;

	_target_addr = _base_addr + _offset;

	/* Set SAM EE flags data */
	for (i = 0; i < (phy->nr_of_sas / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), in_ee->raw_sam_ee[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: SAM EE x write fails for iteration %d\n", i);
			goto END;
		}
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_sam_eex(struct gpy211_device *phy,
				   const struct raw_sam_ee *in_ee)
{
	int i, ret = 0;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_ee == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SAM Entry Enable feature range */
	if (in_ee->eex_type > SAM_ENTRY_CLEAR) {
		LOG_WARN("WARN: Invalid input (eex_type) - SAM Entry Enable feature\n");
		return -EINVAL;
	}

#if !defined(EN_MSEC_DEBUG_ACCESS)

	if (in_ee->eex_type == SAM_ENTRY_ENABLE) {
		LOG_WARN("WARN: SAM Entry Enable option is for debugging only\n");
		return -EINVAL;
	}

#endif

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_SAM_ENABLE_CTRL_MODULE_BASE;

#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS

	if (in_ee->eex_type == SAM_ENTRY_ENABLE)
		_offset = EIPI_SAM_ENTRY_ENABLE1;
	else if (in_ee->eex_type == SAM_ENTRY_TOGGLE)
#else
	if (in_ee->eex_type == SAM_ENTRY_TOGGLE)
#endif
		_offset = EIPI_SAM_ENTRY_TOGGLE1;
	else if (in_ee->eex_type == SAM_ENTRY_SET)
		_offset = EIPI_SAM_ENTRY_SET1;
	else
		_offset = EIPI_SAM_ENTRY_CLEAR1;

	_target_addr = _base_addr + _offset;

	/* Set SAM EE flags data */
	for (i = 0; i < (phy->nr_of_sas / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), in_ee->raw_sam_ee[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: SAM EE x write fails for iteration %d\n", i);
			goto END;
		}
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_sam_eef(struct gpy211_device *phy,
				struct raw_sam_ee *out_ee)
{
	int i, ret = 0;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || out_ee == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	memset(out_ee->raw_sam_ee, 0, (IE_MAX_SAM_SIZE_BYTES / 2));

	_base_addr = EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL_MODULE_BASE;
	_offset = EIPI_SAM_ENTRY_ENABLE1;
	_target_addr = _base_addr + _offset;

	/* Get SAM EE flags data */
	for (i = 0; i < (phy->nr_of_sas / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		ret = PHY_MBOX_READ(phy, _target_addr + (i * 4), &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: SAM EE read fails for iteration %d\n", i);
			goto END;
		}

		out_ee->raw_sam_ee[i] = _data;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_sam_eef(struct gpy211_device *phy,
				struct raw_sam_ee *out_ee)
{
	int i, ret = 0;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || out_ee == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	memset(out_ee->raw_sam_ee, 0, (IE_MAX_SAM_SIZE_BYTES / 2));

	_base_addr = EIPE_EIP_160S_E_32_SAM_ENABLE_CTRL_MODULE_BASE;
	_offset = EIPE_SAM_ENTRY_ENABLE1;
	_target_addr = _base_addr + _offset;

	/* Get SAM EE flags data */
	for (i = 0; i < (phy->nr_of_sas / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		ret = PHY_MBOX_READ(phy, _target_addr + (i * 4), &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: SAM EE read fails for iteration %d\n", i);
			goto END;
		}

		out_ee->raw_sam_ee[i] = _data;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_sam_eec(struct gpy211_device *phy,
				   const struct sam_ee_ctrl *ee_ctrl)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _eec_data = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || ee_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validation
	It is not allowed to write the register with the sam_index_set field equal to
	sam_index_clear while both set_enable and clear_enable are 1b. */
	if (ee_ctrl->set_enable && ee_ctrl->clear_enable) {
		if (ee_ctrl->sam_index_set == ee_ctrl->sam_index_clear) {
			LOG_WARN("WARN: Set & Clear indexes can't be same at a time\n");
			return -EINVAL;
		}
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL_MODULE_BASE;
	_offset = EIPI_SAM_ENTRY_ENABLE_CTRL;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_eec_data, ee_ctrl->sam_index_set, EIPI_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_SET);
	FIELD_REPLACE(_eec_data, ee_ctrl->set_enable, EIPI_SAM_ENTRY_ENABLE_CTRL_SET_ENABLE);
	FIELD_REPLACE(_eec_data, ee_ctrl->set_all, EIPI_SAM_ENTRY_ENABLE_CTRL_SET_ALL);

	FIELD_REPLACE(_eec_data, ee_ctrl->sam_index_clear, EIPI_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_CLEAR);
	FIELD_REPLACE(_eec_data, ee_ctrl->clear_enable, EIPI_SAM_ENTRY_ENABLE_CTRL_CLEAR_ENABLE);
	FIELD_REPLACE(_eec_data, ee_ctrl->clear_all, EIPI_SAM_ENTRY_ENABLE_CTRL_CLEAR_ALL);

	/* Set SAM EE control data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _eec_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM EE control write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_sam_eec(struct gpy211_device *phy,
				   const struct sam_ee_ctrl *ee_ctrl)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _eec_data = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || ee_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validation
	It is not allowed to write the register with the sam_index_set field equal to
	sam_index_clear while both set_enable and clear_enable are 1b. */
	if (ee_ctrl->set_enable && ee_ctrl->clear_enable) {
		if (ee_ctrl->sam_index_set == ee_ctrl->sam_index_clear) {
			LOG_WARN("WARN: Set & Clear indexes can't be same at a time\n");
			return -EINVAL;
		}
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_SAM_ENABLE_CTRL_MODULE_BASE;
	_offset = EIPE_SAM_ENTRY_ENABLE_CTRL;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_eec_data, ee_ctrl->sam_index_set, EIPE_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_SET);
	FIELD_REPLACE(_eec_data, ee_ctrl->set_enable, EIPE_SAM_ENTRY_ENABLE_CTRL_SET_ENABLE);
	FIELD_REPLACE(_eec_data, ee_ctrl->set_all, EIPE_SAM_ENTRY_ENABLE_CTRL_SET_ALL);

	FIELD_REPLACE(_eec_data, ee_ctrl->sam_index_clear, EIPE_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_CLEAR);
	FIELD_REPLACE(_eec_data, ee_ctrl->clear_enable, EIPE_SAM_ENTRY_ENABLE_CTRL_CLEAR_ENABLE);
	FIELD_REPLACE(_eec_data, ee_ctrl->clear_all, EIPE_SAM_ENTRY_ENABLE_CTRL_CLEAR_ALL);

	/* Set SAM EE control data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _eec_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM EE control write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_sa_stats(struct gpy211_device *phy,
				 struct ing_sa_stats *sa_stats)
{
	int i, ret, rule_num;
	u32 _base_addr, _offset, _target_addr, _data, _data2;
	u64 _sa_stats[MAX_ING_SA_COUNTERS];
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sa_stats == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (sa_stats->rule_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (sa_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	rule_num = sa_stats->rule_index;
	memset(sa_stats, 0, sizeof(struct ing_sa_stats));
	sa_stats->rule_index = rule_num;

	_base_addr = EIPI_EIP_160S_I_32_STAT_SA_PAGE0_MODULE_BASE +
		     ((sa_stats->rule_index > 127) ? 0x10000 : 0);
	_offset = ((sa_stats->rule_index) % 128) * (MAX_SA_STATS_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

	/* Get given SA stats */
	for (i = 0; i < MAX_ING_SA_COUNTERS; i++) {
		ret = PHY_MBOX_READ(phy, _target_addr + (i * 8), &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: SA stats low read fails for iteration %d\n", i);
			goto END;
		}

		ret = PHY_MBOX_READ(phy, _target_addr + (i * 8) + 4, &_data2);

		if (ret < 0) {
			LOG_CRIT("ERROR: SA stats high read fails for iteration %d\n", i);
			goto END;
		}

		_sa_stats[i] = ((u64)_data2 << 32) | _data;
	}

	sa_stats->InOctetsDecrypted = _sa_stats[0];
	sa_stats->InOctetsDecrypted2 = _sa_stats[1];
	sa_stats->InPktsUnchecked = _sa_stats[2];
	sa_stats->InPktsDelayed = _sa_stats[3];
	sa_stats->InPktsLate = _sa_stats[4];
	sa_stats->InPktsOK = _sa_stats[5];
	sa_stats->InPktsInvalid = _sa_stats[6];
	sa_stats->InPktsNotValid = _sa_stats[7];
	sa_stats->InPktsNotUsingSA = _sa_stats[8];
	sa_stats->InPktsUnusedSA = _sa_stats[9];
	sa_stats->InPktsUntaggedHit = _sa_stats[10];

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_sa_stats(struct gpy211_device *phy,
				 struct egr_sa_stats *sa_stats)
{
	int i, ret, rule_num;
	u32 _base_addr, _offset, _target_addr, _data, _data2;
	u64 _sa_stats[MAX_EGR_SA_COUNTERS];
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sa_stats == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (sa_stats->rule_index >= phy->nr_of_sas) {
		LOG_WARN("WARN: Invalid input (sa_index) - SA rule num\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	rule_num = sa_stats->rule_index;
	memset(sa_stats, 0, sizeof(struct egr_sa_stats));
	sa_stats->rule_index = rule_num;

	_base_addr = EIPE_EIP_160S_E_32_STAT_SA_PAGE0_MODULE_BASE +
		     ((sa_stats->rule_index > 127) ? 0x10000 : 0);
	_offset = ((sa_stats->rule_index) % 128) * (MAX_SA_STATS_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

	/* Get given SA stats */
	for (i = 0; i < MAX_EGR_SA_COUNTERS; i++) {
		ret = PHY_MBOX_READ(phy, _target_addr + (i * 8), &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: SA stats low read fails for iteration %d\n", i);
			goto END;
		}

		ret = PHY_MBOX_READ(phy, _target_addr + (i * 8) + 4, &_data2);

		if (ret < 0) {
			LOG_CRIT("ERROR: SA stats high read fails for iteration %d\n", i);
			goto END;
		}

		_sa_stats[i] = ((u64)_data2 << 32) | _data;
	}

	sa_stats->OutOctetsEncrypted = _sa_stats[0];
	sa_stats->OutOctetsEncrypted2 = _sa_stats[1];
	sa_stats->OutPktsEncrypted = _sa_stats[2];
	sa_stats->OutPktsTooLong = _sa_stats[3];

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}
int gpy2xx_msec_get_ing_global_stats(struct gpy211_device *phy,
				     struct ing_global_stats *glob_stats)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr, _data, _data2;
	u64 _global_stats[MAX_ING_GLOBAL_COUNTERS];
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || glob_stats == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	memset(glob_stats, 0, sizeof(struct ing_global_stats));

	_base_addr = EIPI_EIP_160S_I_32_STAT_GLOBAL_MODULE_BASE;
	_offset =  EIPI_TRANSFORMERRORPKTS_LO;
	_target_addr = _base_addr + _offset;

	/* Get GLOBAL stats */
	for (i = 0; i < MAX_ING_GLOBAL_COUNTERS; i++) {
		ret = PHY_MBOX_READ(phy, _target_addr + (i * 8), &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: GLOBAL stats low read fails for iteration %d\n", i);
			goto END;
		}

		ret = PHY_MBOX_READ(phy, _target_addr + (i * 8) + 4, &_data2);

		if (ret < 0) {
			LOG_CRIT("ERROR: GLOBAL stats high read fails for iteration %d\n", i);
			goto END;
		}

		_global_stats[i] = ((u64)_data2 << 32) | _data;
	}

	glob_stats->TransformErrorPkts = _global_stats[0];
	glob_stats->InPktsCtrl = _global_stats[1];
	glob_stats->InPktsNoTag = _global_stats[2];
	glob_stats->InPktsUntagged = _global_stats[3];
	glob_stats->InPktsTagged = _global_stats[4];
	glob_stats->InPktsBadTag = _global_stats[5];
	glob_stats->InPktsUntaggedMiss = _global_stats[6];
	glob_stats->InPktsNoSCI = _global_stats[7];
	glob_stats->InPktsUnknownSCI = _global_stats[8];
	glob_stats->InConsistCheckControlledNotPass = _global_stats[9];
	glob_stats->InConsistCheckUncontrolledNotPass = _global_stats[10];
	glob_stats->InConsistCheckControlledPass = _global_stats[11];
	glob_stats->InConsistCheckUncontrolledPass = _global_stats[12];
	glob_stats->InOverSizePkts = _global_stats[13];

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_global_stats(struct gpy211_device *phy,
				     struct egr_global_stats *glob_stats)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr, _data, _data2;
	u64 _global_stats[MAX_EGR_GLOBAL_COUNTERS];
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || glob_stats == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	memset(glob_stats, 0, sizeof(struct egr_global_stats));

	_base_addr = EIPE_EIP_160S_E_32_STAT_GLOBAL_MODULE_BASE;
	_offset =  EIPE_TRANSFORMERRORPKTS_LO;
	_target_addr = _base_addr + _offset;

	/* Get GLOBAL stats */
	for (i = 0; i < MAX_EGR_GLOBAL_COUNTERS; i++) {
		ret = PHY_MBOX_READ(phy, _target_addr + (i * 8), &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: GLOBAL stats low read fails for iteration %d\n", i);
			goto END;
		}

		ret = PHY_MBOX_READ(phy, _target_addr + (i * 8) + 4, &_data2);

		if (ret < 0) {
			LOG_CRIT("ERROR: GLOBAL stats high read fails for iteration %d\n", i);
			goto END;
		}

		_global_stats[i] = ((u64)_data2 << 32) | _data;
	}

	glob_stats->TransformErrorPkts = _global_stats[0];
	glob_stats->OutPktsCtrl = _global_stats[1];
	glob_stats->OutPktsUnknownSA = _global_stats[2];
	glob_stats->OutPktsUntagged = _global_stats[3];
	glob_stats->OutOverSizePkts = _global_stats[4];

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
int gpy2xx_msec_get_ing_vlan_stats(struct gpy211_device *phy,
				   struct ing_vlan_stats *vlan_stats)
{
	int i, ret, vlan_up;
	u32 _base_addr, _offset, _target_addr, _data, _data2;
	u64 _vlan_stats[MAX_VLAN_COUNTERS];
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || vlan_stats == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate VLAN User Priority range */
	if (vlan_stats->vlan_up >= MAX_VLAN_USER_PRIORITIES) {
		LOG_WARN("WARN: Invalid input (vlan_up) - VLAN User Priority\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	vlan_up = vlan_stats->vlan_up;
	memset(vlan_stats, 0, sizeof(struct ing_vlan_stats));
	vlan_stats->vlan_up = vlan_up;

	_base_addr = EIPI_EIP_160S_I_32_STAT_VLAN_MODULE_BASE;
	_offset = (vlan_stats->vlan_up) * (MAX_SA_STATS_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

	/* Get VLAN stats */
	for (i = 0; i < MAX_VLAN_COUNTERS; i++) {
		ret = PHY_MBOX_READ(phy, _target_addr + (i * 8), &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: VLAN stats low read fails for iteration %d\n", i);
			goto END;
		}

		ret = PHY_MBOX_READ(phy, _target_addr + (i * 8) + 4, &_data2);

		if (ret < 0) {
			LOG_CRIT("ERROR: VLAN stats high read fails for iteration %d\n", i);
			goto END;
		}

		_vlan_stats[i] = ((u64)_data2 << 32) | _data;
	}

	vlan_stats->InOctetsVL = _vlan_stats[0];
	vlan_stats->InOctetsVL2 = _vlan_stats[1];
	vlan_stats->InPktsVL = _vlan_stats[2];
	vlan_stats->InDroppedPktsVL = _vlan_stats[3];
	vlan_stats->InOverSizePktsVL = _vlan_stats[4];

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_vlan_stats(struct gpy211_device *phy,
				   struct egr_vlan_stats *vlan_stats)
{
	int i, ret, vlan_up;
	u32 _base_addr, _offset, _target_addr, _data, _data2;
	u64 _vlan_stats[MAX_VLAN_COUNTERS];
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || vlan_stats == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate VLAN User Priority range */
	if (vlan_stats->vlan_up >= MAX_VLAN_USER_PRIORITIES) {
		LOG_WARN("WARN: Invalid input (vlan_up) - VLAN User Priority\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	vlan_up = vlan_stats->vlan_up;
	memset(vlan_stats, 0, sizeof(struct egr_vlan_stats));
	vlan_stats->vlan_up = vlan_up;

	_base_addr = EIPE_EIP_160S_E_32_STAT_VLAN_MODULE_BASE;
	_offset = (vlan_stats->vlan_up) * (MAX_SA_STATS_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

	/* Get VLAN stats */
	for (i = 0; i < MAX_VLAN_COUNTERS; i++) {
		ret = PHY_MBOX_READ(phy, _target_addr + (i * 8), &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: VLAN stats low read fails for iteration %d\n", i);
			goto END;
		}

		ret = PHY_MBOX_READ(phy, _target_addr + (i * 8) + 4, &_data2);

		if (ret < 0) {
			LOG_CRIT("ERROR: VLAN stats high read fails for iteration %d\n", i);
			goto END;
		}

		_vlan_stats[i] = ((u64)_data2 << 32) | _data;
	}

	vlan_stats->OutOctetsVL = _vlan_stats[0];
	vlan_stats->OutOctetsVL2 = _vlan_stats[1];
	vlan_stats->OutPktsVL = _vlan_stats[2];
	vlan_stats->OutDroppedPktsVL = _vlan_stats[3];
	vlan_stats->OutOverSizePktsVL = _vlan_stats[4];

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}
#endif

#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
int gpy2xx_msec_get_ing_debug_stats(struct gpy211_device *phy,
				    struct stats_debug_regs *dbg_stats)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || dbg_stats == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	memset(dbg_stats, 0, sizeof(struct stats_debug_regs));

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset =  EIPI_COUNT_DEBUG1;
	_target_addr = _base_addr + _offset;

	/* Get COUNT_DEBUG1 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: COUNT_DEBUG1 stats read fails for iteration\n");
		goto END;
	}

	dbg_stats->cdb1.raw_cdb1 = _data;

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset =  EIPI_COUNT_DEBUG2;
	_target_addr = _base_addr + _offset;

	/* Get COUNT_DEBUG2 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: COUNT_DEBUG2 stats read fails for iteration\n");
		goto END;
	}

	dbg_stats->cdb2.raw_cdb2 = _data;

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset =  EIPI_COUNT_DEBUG3;
	_target_addr = _base_addr + _offset;

	/* Get COUNT_DEBUG3 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: COUNT_DEBUG3 stats read fails for iteration\n");
		goto END;
	}

	dbg_stats->global_inc_mask = _data;

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset =  EIPI_COUNT_DEBUG4;
	_target_addr = _base_addr + _offset;

	/* Get COUNT_DEBUG4 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: COUNT_DEBUG4 stats read fails for iteration\n");
		goto END;
	}

	dbg_stats->cdb4.raw_cdb4 = _data;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_debug_stats(struct gpy211_device *phy,
				    struct stats_debug_regs *dbg_stats)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || dbg_stats == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	memset(dbg_stats, 0, sizeof(struct stats_debug_regs));

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset =  EIPE_COUNT_DEBUG1;
	_target_addr = _base_addr + _offset;

	/* Get COUNT_DEBUG1 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: COUNT_DEBUG1 stats read fails for iteration\n");
		goto END;
	}

	dbg_stats->cdb1.raw_cdb1 = _data;

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset =  EIPE_COUNT_DEBUG2;
	_target_addr = _base_addr + _offset;

	/* Get COUNT_DEBUG2 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: COUNT_DEBUG2 stats read fails for iteration\n");
		goto END;
	}

	dbg_stats->cdb2.raw_cdb2 = _data;

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset =  EIPE_COUNT_DEBUG3;
	_target_addr = _base_addr + _offset;

	/* Get COUNT_DEBUG3 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: COUNT_DEBUG3 stats read fails for iteration\n");
		goto END;
	}

	dbg_stats->global_inc_mask = _data;

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset =  EIPE_COUNT_DEBUG4;
	_target_addr = _base_addr + _offset;

	/* Get COUNT_DEBUG4 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: COUNT_DEBUG4 stats read fails for iteration\n");
		goto END;
	}

	dbg_stats->cdb4.raw_cdb4 = _data;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}
#endif

int gpy2xx_msec_config_ing_count_ctrl(struct gpy211_device *phy,
				      const struct count_control *cnt_ctrl)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _count_ctrl = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cnt_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate Counter Control params */
	if ((cnt_ctrl->reset_all > 1) || (cnt_ctrl->saturate_cntrs > 1) ||
	    (cnt_ctrl->auto_cntr_reset > 1) || (cnt_ctrl->reset_summary > 1) ||
	    (cnt_ctrl->debug_access > 1)) {
		LOG_WARN("WARN: Invalid input Counter Control params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPI_COUNT_CONTROL;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_count_ctrl, cnt_ctrl->reset_all, EIPI_COUNT_CONTROL_RESET_ALL);
#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	FIELD_REPLACE(_count_ctrl, cnt_ctrl->debug_access, EIPI_COUNT_CONTROL_DEBUG_ACCESS);
#endif
	FIELD_REPLACE(_count_ctrl, cnt_ctrl->saturate_cntrs, EIPI_COUNT_CONTROL_SATURATE_CNTRS);
	FIELD_REPLACE(_count_ctrl, cnt_ctrl->auto_cntr_reset, EIPI_COUNT_CONTROL_AUTO_CNTR_RESET);
	FIELD_REPLACE(_count_ctrl, cnt_ctrl->reset_summary, EIPI_COUNT_CONTROL_RESET_SUMMARY);

	/* Set Counter Ctrl flags data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _count_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: Counter Control word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_count_ctrl(struct gpy211_device *phy,
				      const struct count_control *cnt_ctrl)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _count_ctrl = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cnt_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate Counter Control params */
	if ((cnt_ctrl->reset_all > 1) || (cnt_ctrl->saturate_cntrs > 1) ||
	    (cnt_ctrl->auto_cntr_reset > 1) || (cnt_ctrl->reset_summary > 1) ||
	    (cnt_ctrl->debug_access > 1)) {
		LOG_WARN("WARN: Invalid input Counter Control params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPE_COUNT_CONTROL;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_count_ctrl, cnt_ctrl->reset_all, EIPI_COUNT_CONTROL_RESET_ALL);
#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	FIELD_REPLACE(_count_ctrl, cnt_ctrl->debug_access, EIPI_COUNT_CONTROL_DEBUG_ACCESS);
#endif
	FIELD_REPLACE(_count_ctrl, cnt_ctrl->saturate_cntrs, EIPI_COUNT_CONTROL_SATURATE_CNTRS);
	FIELD_REPLACE(_count_ctrl, cnt_ctrl->auto_cntr_reset, EIPI_COUNT_CONTROL_AUTO_CNTR_RESET);
	FIELD_REPLACE(_count_ctrl, cnt_ctrl->reset_summary, EIPI_COUNT_CONTROL_RESET_SUMMARY);

	/* Set Counter Ctrl flags data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _count_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: Counter Control word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_count_incen(struct gpy211_device *phy,
				       const struct count_incen *cnt_incen)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _count_inc1 = 0, _count_inc2 = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cnt_incen == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPI_COUNT_INCEN1;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_count_inc1, cnt_incen->sa_inc_en, EIPI_COUNT_INCEN1_SA_INCREMENT_ENABLE);
	FIELD_REPLACE(_count_inc1, cnt_incen->vlan_inc_en, EIPI_COUNT_INCEN1_VLAN_INCREMENT_ENABLE);

	/* Set COUNT_INCEN1 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _count_inc1);

	if (ret < 0) {
		LOG_CRIT("ERROR: Counter Incremental Enable1 word set fails\n");
		goto END;
	}

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPI_COUNT_INCEN2;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_count_inc2, cnt_incen->global_inc_en, EIPI_COUNT_INCEN2_GLOBAL_INCREMENT_ENABLE);

	/* Set COUNT_INCEN2 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _count_inc2);

	if (ret < 0) {
		LOG_CRIT("ERROR: Counter Incremental Enable2 word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_count_incen(struct gpy211_device *phy,
				       const struct count_incen *cnt_incen)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _count_inc1 = 0, _count_inc2 = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cnt_incen == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPE_COUNT_INCEN1;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_count_inc1, cnt_incen->sa_inc_en, EIPE_COUNT_INCEN1_SA_INCREMENT_ENABLE);
	FIELD_REPLACE(_count_inc1, cnt_incen->vlan_inc_en, EIPE_COUNT_INCEN1_VLAN_INCREMENT_ENABLE);

	/* Set COUNT_INCEN1 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _count_inc1);

	if (ret < 0) {
		LOG_CRIT("ERROR: Counter Incremental Enable1 word set fails\n");
		goto END;
	}

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPE_COUNT_INCEN2;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_count_inc2, cnt_incen->global_inc_en, EIPE_COUNT_INCEN2_GLOBAL_INCREMENT_ENABLE);

	/* Set COUNT_INCEN2 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _count_inc2);

	if (ret < 0) {
		LOG_CRIT("ERROR: Counter Incremental Enable2 word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_count_thresh(struct gpy211_device *phy,
					const struct frame_octet_thr *cnt_thr)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _low_word, _high_word;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cnt_thr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPI_COUNT_FRAME_THR1;
	_target_addr = _base_addr + _offset;

	_low_word = (cnt_thr->frame_threshold) & 0xFFFFFFFFu;
	_high_word = cnt_thr->frame_threshold >> 32;
	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _low_word);

	if (ret < 0) {
		LOG_CRIT("ERROR: Frame Treshold lower word set fails\n");
		goto END;
	}

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPI_COUNT_FRAME_THR2;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _high_word);

	if (ret < 0) {
		LOG_CRIT("ERROR: Frame Treshold higher word set fails\n");
		goto END;
	}

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPI_COUNT_OCTET_THR1;
	_target_addr = _base_addr + _offset;

	_low_word = (cnt_thr->octet_threshold) & 0xFFFFFFFFu;
	_high_word = cnt_thr->octet_threshold >> 32;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _low_word);

	if (ret < 0) {
		LOG_CRIT("ERROR: Octet Treshold lower word set fails\n");
		goto END;
	}

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPI_COUNT_OCTET_THR2;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _high_word);

	if (ret < 0) {
		LOG_CRIT("ERROR: Octet Treshold higher word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_count_thresh(struct gpy211_device *phy,
				     struct frame_octet_thr *cnt_thr)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cnt_thr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPI_COUNT_FRAME_THR1;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: Frame Treshold lower word set fails\n");
		goto END;
	}

	cnt_thr->frame_threshold = _data;

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPI_COUNT_FRAME_THR2;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: Frame Treshold higher word set fails\n");
		goto END;
	}

	cnt_thr->frame_threshold |= ((u64)_data << 32);

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPI_COUNT_OCTET_THR1;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: Octet Treshold lower word set fails\n");
		goto END;
	}

	cnt_thr->octet_threshold = _data;

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPI_COUNT_OCTET_THR2;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: Octet Treshold higher word set fails\n");
		goto END;
	}

	cnt_thr->octet_threshold |= ((u64)_data << 32);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_count_thresh(struct gpy211_device *phy,
					const struct frame_octet_thr *cnt_thr)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _low_word, _high_word;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cnt_thr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPE_COUNT_FRAME_THR1;
	_target_addr = _base_addr + _offset;

	_low_word = (cnt_thr->frame_threshold) & 0xFFFFFFFFu;
	_high_word = cnt_thr->frame_threshold >> 32;
	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _low_word);

	if (ret < 0) {
		LOG_CRIT("ERROR: Frame Treshold lower word set fails\n");
		goto END;
	}

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPE_COUNT_FRAME_THR2;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _high_word);

	if (ret < 0) {
		LOG_CRIT("ERROR: Frame Treshold higher word set fails\n");
		goto END;
	}

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPE_COUNT_OCTET_THR1;
	_target_addr = _base_addr + _offset;

	_low_word = (cnt_thr->octet_threshold) & 0xFFFFFFFFu;
	_high_word = cnt_thr->octet_threshold >> 32;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _low_word);

	if (ret < 0) {
		LOG_CRIT("ERROR: Octet Treshold lower word set fails\n");
		goto END;
	}

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPE_COUNT_OCTET_THR2;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _high_word);

	if (ret < 0) {
		LOG_CRIT("ERROR: Octet Treshold higher word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}


int gpy2xx_msec_get_egr_count_thresh(struct gpy211_device *phy,
				     struct frame_octet_thr *cnt_thr)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cnt_thr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPE_COUNT_FRAME_THR1;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: Frame Treshold lower word set fails\n");
		goto END;
	}

	cnt_thr->frame_threshold = _data;

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPE_COUNT_FRAME_THR2;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: Frame Treshold higher word set fails\n");
		goto END;
	}

	cnt_thr->frame_threshold |= ((u64)_data << 32);

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPE_COUNT_OCTET_THR1;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: Octet Treshold lower word set fails\n");
		goto END;
	}

	cnt_thr->octet_threshold = _data;

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPE_COUNT_OCTET_THR2;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_FRAME_THR_1 data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: Octet Treshold higher word set fails\n");
		goto END;
	}

	cnt_thr->octet_threshold |= ((u64)_data << 32);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}


int gpy2xx_msec_config_ing_misc_ctrl(struct gpy211_device *phy,
				     const struct misc_control *misc_ctrl)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _misc_ctrl = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || misc_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate Counter Control params */
	if ((misc_ctrl->static_bypass > 1) || (misc_ctrl->nm_macsec_en > 1) ||
	    (misc_ctrl->validate_frames > SAM_FCA_VALIDATE_STRICT) ||
	    (misc_ctrl->sectag_after_vlan > 1)) {
		LOG_WARN("WARN: Invalid input Misc Control params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
	_offset = EIPI_MISC_CONTROL;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_misc_ctrl, misc_ctrl->mc_latency_fix, EIPI_MISC_CONTROL_MC_LATENCY_FIX_7_0);
#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	FIELD_REPLACE(_misc_ctrl, misc_ctrl->static_bypass, EIPI_MISC_CONTROL_STATIC_BYPASS);
#endif
	FIELD_REPLACE(_misc_ctrl, misc_ctrl->nm_macsec_en, EIPI_MISC_CONTROL_NM_MACSEC_EN);
	FIELD_REPLACE(_misc_ctrl, misc_ctrl->validate_frames, EIPI_MISC_CONTROL_VALIDATE_FRAMES);
	FIELD_REPLACE(_misc_ctrl, misc_ctrl->sectag_after_vlan, EIPI_MISC_CONTROL_SECTAG_AFTER_VLAN);
	FIELD_REPLACE(_misc_ctrl, 1, EIPI_MISC_CONTROL_XFORM_REC_SIZE);

	/* Set Counter Ctrl flags data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _misc_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: Misc Control word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_misc_ctrl(struct gpy211_device *phy,
				     const struct misc_control *misc_ctrl)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _misc_ctrl = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || misc_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate Counter Control params */
	if ((misc_ctrl->static_bypass > 1) || (misc_ctrl->nm_macsec_en > 1) ||
	    (misc_ctrl->validate_frames > SAM_FCA_VALIDATE_STRICT) ||
	    (misc_ctrl->sectag_after_vlan > 1)) {
		LOG_WARN("WARN: Invalid input Misc Control params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
	_offset = EIPE_MISC_CONTROL;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_misc_ctrl, misc_ctrl->mc_latency_fix, EIPI_MISC_CONTROL_MC_LATENCY_FIX_7_0);
#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	FIELD_REPLACE(_misc_ctrl, misc_ctrl->static_bypass, EIPI_MISC_CONTROL_STATIC_BYPASS);
#endif
	FIELD_REPLACE(_misc_ctrl, misc_ctrl->nm_macsec_en, EIPI_MISC_CONTROL_NM_MACSEC_EN);
	FIELD_REPLACE(_misc_ctrl, misc_ctrl->validate_frames, EIPI_MISC_CONTROL_VALIDATE_FRAMES);
	FIELD_REPLACE(_misc_ctrl, misc_ctrl->sectag_after_vlan, EIPI_MISC_CONTROL_SECTAG_AFTER_VLAN);
	FIELD_REPLACE(_misc_ctrl, 2, EIPI_MISC_CONTROL_XFORM_REC_SIZE);

	/* Set Counter Ctrl flags data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _misc_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: Misc Control word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_sa_nm_ctrl(struct gpy211_device *phy,
				      const struct sa_nm_params *sanm_ctrl)
{
	int ret;
	u32 _sanmn_par = 0;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sanm_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA non-match EXPL params */
	if (sanm_ctrl->msec_tag_value != ETH_PROTO_MACSEC) {
		LOG_WARN("WARN: Invalid input SA non-match params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
	_offset = EIPI_SAM_NM_PARAMS;
	_target_addr = _base_addr + _offset;
#ifdef VERIFY_ENDIANNESS
	/* Get SAM_NM_PARAMS */
	printf("Input values eth_type %x, comp_eth %d, v %d, kay %d, c_e %d, sc %d, sl %d, pn %d\n",
	       sanm_ctrl->msec_tag_value, sanm_ctrl->comp_etype, sanm_ctrl->check_v, sanm_ctrl->check_kay,
	       sanm_ctrl->check_c_e, sanm_ctrl->check_sc, sanm_ctrl->check_sl, sanm_ctrl->check_pn);
	printf("Input raw %x\n", sanm_ctrl->raw_sanm_ctrl);

	struct sa_nm_params _read_nmpar;

	ret = PHY_MBOX_READ(phy, _target_addr, &_sanmn_par);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_PARAMS get fails\n");
		goto END;
	}

	_read_nmpar.raw_sanm_ctrl = _sanmn_par;

	printf("Existing raw %x, stored %x\n", _sanmn_par, _read_nmpar.raw_sanm_ctrl);
	printf("Existing values eth_type %x, comp_eth %d, v %d, kay %d, c_e %d, sc %d, sl %d, pn %d\n",
	       _read_nmpar.msec_tag_value, _read_nmpar.comp_etype, _read_nmpar.check_v, _read_nmpar.check_kay,
	       _read_nmpar.check_c_e, _read_nmpar.check_sc, _read_nmpar.check_sl, _read_nmpar.check_pn);
#endif
	_sanmn_par = sanm_ctrl->raw_sanm_ctrl;
	FIELD_REPLACE(_sanmn_par, ETH_PROTO_MACSEC_BYTE_SWAPPED, EIPI_SAM_NM_PARAMS_MSEC_TAG_VALUE);
	/* Set SAM_NM_PARAMS data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _sanmn_par);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_PARAMS set fails\n");
		goto END;
	}

#ifdef VERIFY_ENDIANNESS
	/* Get SAM_NM_PARAMS */
	_read_nmpar.raw_sanm_ctrl = _sanmn_par = 0;
	ret = PHY_MBOX_READ(phy, _target_addr, &_sanmn_par);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_PARAMS get fails\n");
		goto END;
	}

	_read_nmpar.raw_sanm_ctrl = _sanmn_par;
	printf("New raw %x, stored %x\n", _sanmn_par, _read_nmpar.raw_sanm_ctrl);
	printf("New values eth_type %x, comp_eth %d, v %d, kay %d, c_e %d, sc %d, sl %d, pn %d\n",
	       _read_nmpar.msec_tag_value, _read_nmpar.comp_etype, _read_nmpar.check_v, _read_nmpar.check_kay,
	       _read_nmpar.check_c_e, _read_nmpar.check_sc, _read_nmpar.check_sl, _read_nmpar.check_pn);
#endif

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_sa_nm_ctrl(struct gpy211_device *phy,
				      const struct sa_nm_params *sanm_ctrl)
{
	int ret;
	u32 _sanmn_par = 0;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sanm_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA non-match EXPL params */
	if (sanm_ctrl->msec_tag_value != ETH_PROTO_MACSEC) {
		LOG_WARN("WARN: Invalid input SA non-match params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
	_offset = EIPE_SAM_NM_PARAMS;
	_target_addr = _base_addr + _offset;
#ifdef VERIFY_ENDIANNESS
	/* Get SAM_NM_PARAMS */
	printf("Input values eth_type %x, comp_eth %d, v %d, kay %d, c_e %d, sc %d, sl %d, pn %d\n",
	       sanm_ctrl->msec_tag_value, sanm_ctrl->comp_etype, sanm_ctrl->check_v, sanm_ctrl->check_kay,
	       sanm_ctrl->check_c_e, sanm_ctrl->check_sc, sanm_ctrl->check_sl, sanm_ctrl->check_pn);
	printf("Input raw %x\n", sanm_ctrl->raw_sanm_ctrl);

	struct sa_nm_params _read_nmpar;

	ret = PHY_MBOX_READ(phy, _target_addr, &_sanmn_par);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_PARAMS get fails\n");
		goto END;
	}

	_read_nmpar.raw_sanm_ctrl = _sanmn_par;

	printf("Existing raw %x, stored %x\n", _sanmn_par, _read_nmpar.raw_sanm_ctrl);
	printf("Existing values eth_type %x, comp_eth %d, v %d, kay %d, c_e %d, sc %d, sl %d, pn %d\n",
	       _read_nmpar.msec_tag_value, _read_nmpar.comp_etype, _read_nmpar.check_v, _read_nmpar.check_kay,
	       _read_nmpar.check_c_e, _read_nmpar.check_sc, _read_nmpar.check_sl, _read_nmpar.check_pn);
#endif
	_sanmn_par = sanm_ctrl->raw_sanm_ctrl;
	FIELD_REPLACE(_sanmn_par, ETH_PROTO_MACSEC_BYTE_SWAPPED, EIPI_SAM_NM_PARAMS_MSEC_TAG_VALUE);
	/* Set SAM_NM_PARAMS data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _sanmn_par);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_PARAMS set fails\n");
		goto END;
	}

#ifdef VERIFY_ENDIANNESS
	/* Get SAM_NM_PARAMS */
	_read_nmpar.raw_sanm_ctrl = _sanmn_par = 0;
	ret = PHY_MBOX_READ(phy, _target_addr, &_sanmn_par);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_PARAMS get fails\n");
		goto END;
	}

	_read_nmpar.raw_sanm_ctrl = _sanmn_par;
	printf("New raw %x, stored %x\n", _sanmn_par, _read_nmpar.raw_sanm_ctrl);
	printf("New values eth_type %x, comp_eth %d, v %d, kay %d, c_e %d, sc %d, sl %d, pn %d\n",
	       _read_nmpar.msec_tag_value, _read_nmpar.comp_etype, _read_nmpar.check_v, _read_nmpar.check_kay,
	       _read_nmpar.check_c_e, _read_nmpar.check_sc, _read_nmpar.check_sl, _read_nmpar.check_pn);
#endif

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_sa_nm_ncp(struct gpy211_device *phy,
				     const struct sa_nonmatch_fca *nm_ncp)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _nm_ncp = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || nm_ncp == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA non-match NCP params */
	if ((nm_ncp->pkt_type > SA_NM_SECY_ALL_TAGGED) ||
	    (nm_ncp->flow_type > SA_NM_FCA_FLOW_DROP) ||
	    (nm_ncp->dest_port > SA_NM_FCA_DPT_UNCONTROL) ||
	    (nm_ncp->drop_non_reserved > 1) ||
	    (nm_ncp->drop_action > SA_NM_FCA_NO_DROP)) {
		LOG_WARN("WARN: Invalid input SA non-match NCP params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
	_offset = EIPI_SAM_NM_FLOW_NCP;
	_target_addr = _base_addr + _offset;

	/* Get SAM_NM_FLOW_NCP */
	ret = PHY_MBOX_READ(phy, _target_addr, &_nm_ncp);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_FLOW_NCP get fails\n");
		goto END;
	}

	if ((nm_ncp->pkt_type == SA_NM_SECY_UNTAGGED) ||
	    (nm_ncp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_ncp, nm_ncp->flow_type, EIPI_SAM_NM_FLOW_NCP_FLOW_TYPE0);
		FIELD_REPLACE(_nm_ncp, nm_ncp->dest_port, EIPI_SAM_NM_FLOW_NCP_DEST_PORT0);
		FIELD_REPLACE(_nm_ncp, nm_ncp->drop_non_reserved, EIPI_SAM_NM_FLOW_NCP_DROP_NON_RESERVED0);
		FIELD_REPLACE(_nm_ncp, nm_ncp->drop_action, EIPI_SAM_NM_FLOW_NCP_DROP_ACTION0);
	}

	if ((nm_ncp->pkt_type == SA_NM_SECY_TAGGED) ||
	    (nm_ncp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_ncp, nm_ncp->flow_type, EIPI_SAM_NM_FLOW_NCP_FLOW_TYPE1);
		FIELD_REPLACE(_nm_ncp, nm_ncp->dest_port, EIPI_SAM_NM_FLOW_NCP_DEST_PORT1);
		FIELD_REPLACE(_nm_ncp, nm_ncp->drop_non_reserved, EIPI_SAM_NM_FLOW_NCP_DROP_NON_RESERVED1);
		FIELD_REPLACE(_nm_ncp, nm_ncp->drop_action, EIPI_SAM_NM_FLOW_NCP_DROP_ACTION1);
	}

	if ((nm_ncp->pkt_type == SA_NM_SECY_BAD_TAGGED) ||
	    (nm_ncp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_ncp, nm_ncp->flow_type, EIPI_SAM_NM_FLOW_NCP_FLOW_TYPE2);
		FIELD_REPLACE(_nm_ncp, nm_ncp->dest_port, EIPI_SAM_NM_FLOW_NCP_DEST_PORT2);
		FIELD_REPLACE(_nm_ncp, nm_ncp->drop_non_reserved, EIPI_SAM_NM_FLOW_NCP_DROP_NON_RESERVED2);
		FIELD_REPLACE(_nm_ncp, nm_ncp->drop_action, EIPI_SAM_NM_FLOW_NCP_DROP_ACTION2);
	}

	if ((nm_ncp->pkt_type == SA_NM_SECY_KAY_TAGGED) ||
	    (nm_ncp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_ncp, nm_ncp->flow_type, EIPI_SAM_NM_FLOW_NCP_FLOW_TYPE3);
		FIELD_REPLACE(_nm_ncp, nm_ncp->dest_port, EIPI_SAM_NM_FLOW_NCP_DEST_PORT3);
		FIELD_REPLACE(_nm_ncp, nm_ncp->drop_non_reserved, EIPI_SAM_NM_FLOW_NCP_DROP_NON_RESERVED3);
		FIELD_REPLACE(_nm_ncp, nm_ncp->drop_action, EIPI_SAM_NM_FLOW_NCP_DROP_ACTION3);
	}

	/* Set SAM_NM_FLOW_NCP data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _nm_ncp);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_FLOW_NCP set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_sa_nm_ncp(struct gpy211_device *phy,
				     const struct sa_nonmatch_fca *nm_ncp)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _nm_ncp = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || nm_ncp == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA non-match NCP params */
	if ((nm_ncp->pkt_type > SA_NM_SECY_ALL_TAGGED) ||
	    (nm_ncp->flow_type > SA_NM_FCA_FLOW_DROP) ||
	    (nm_ncp->dest_port > SA_NM_FCA_DPT_UNCONTROL) ||
	    (nm_ncp->drop_action > SA_NM_FCA_NO_DROP)) {
		LOG_WARN("WARN: Invalid input SA non-match NCP params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
	_offset = EIPE_SAM_NM_FLOW_NCP;
	_target_addr = _base_addr + _offset;

	/* Get SAM_NM_FLOW_NCP */
	ret = PHY_MBOX_READ(phy, _target_addr, &_nm_ncp);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_FLOW_NCP get fails\n");
		goto END;
	}

	if ((nm_ncp->pkt_type == SA_NM_SECY_UNTAGGED) ||
	    (nm_ncp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_ncp, nm_ncp->flow_type, EIPE_SAM_NM_FLOW_NCP_FLOW_TYPE0);
		FIELD_REPLACE(_nm_ncp, nm_ncp->dest_port, EIPE_SAM_NM_FLOW_NCP_DEST_PORT0);
		FIELD_REPLACE(_nm_ncp, nm_ncp->drop_action, EIPE_SAM_NM_FLOW_NCP_DROP_ACTION0);
	}

	if ((nm_ncp->pkt_type == SA_NM_SECY_TAGGED) ||
	    (nm_ncp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_ncp, nm_ncp->flow_type, EIPE_SAM_NM_FLOW_NCP_FLOW_TYPE1);
		FIELD_REPLACE(_nm_ncp, nm_ncp->dest_port, EIPE_SAM_NM_FLOW_NCP_DEST_PORT1);
		FIELD_REPLACE(_nm_ncp, nm_ncp->drop_action, EIPE_SAM_NM_FLOW_NCP_DROP_ACTION1);
	}

	if ((nm_ncp->pkt_type == SA_NM_SECY_BAD_TAGGED) ||
	    (nm_ncp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_ncp, nm_ncp->flow_type, EIPE_SAM_NM_FLOW_NCP_FLOW_TYPE2);
		FIELD_REPLACE(_nm_ncp, nm_ncp->dest_port, EIPE_SAM_NM_FLOW_NCP_DEST_PORT2);
		FIELD_REPLACE(_nm_ncp, nm_ncp->drop_action, EIPE_SAM_NM_FLOW_NCP_DROP_ACTION2);
	}

	if ((nm_ncp->pkt_type == SA_NM_SECY_KAY_TAGGED) ||
	    (nm_ncp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_ncp, nm_ncp->flow_type, EIPE_SAM_NM_FLOW_NCP_FLOW_TYPE3);
		FIELD_REPLACE(_nm_ncp, nm_ncp->dest_port, EIPE_SAM_NM_FLOW_NCP_DEST_PORT3);
		FIELD_REPLACE(_nm_ncp, nm_ncp->drop_action, EIPE_SAM_NM_FLOW_NCP_DROP_ACTION3);
	}

	/* Set SAM_NM_FLOW_NCP data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _nm_ncp);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_FLOW_NCP set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_sa_nm_cp(struct gpy211_device *phy,
				    const struct sa_nonmatch_fca *nm_cp)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _nm_cp = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || nm_cp == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA non-match CP params */
	if ((nm_cp->pkt_type > SA_NM_SECY_ALL_TAGGED) ||
	    (nm_cp->flow_type > SA_NM_FCA_FLOW_DROP) ||
	    (nm_cp->dest_port > SA_NM_FCA_DPT_UNCONTROL) ||
	    (nm_cp->drop_non_reserved > 1) ||
	    (nm_cp->drop_action > SA_NM_FCA_NO_DROP)) {
		LOG_WARN("WARN: Invalid input SA non-match CP params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
	_offset = EIPI_SAM_NM_FLOW_CP;
	_target_addr = _base_addr + _offset;

	/* Get SAM_NM_FLOW_CP */
	ret = PHY_MBOX_READ(phy, _target_addr, &_nm_cp);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_FLOW_CP get fails\n");
		goto END;
	}

	if ((nm_cp->pkt_type == SA_NM_SECY_UNTAGGED) ||
	    (nm_cp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_cp, nm_cp->flow_type, EIPI_SAM_NM_FLOW_CP_FLOW_TYPE0);
		FIELD_REPLACE(_nm_cp, nm_cp->dest_port, EIPI_SAM_NM_FLOW_CP_DEST_PORT0);
		FIELD_REPLACE(_nm_cp, nm_cp->drop_non_reserved, EIPI_SAM_NM_FLOW_CP_DROP_NON_RESERVED0);
		FIELD_REPLACE(_nm_cp, nm_cp->drop_action, EIPI_SAM_NM_FLOW_CP_DROP_ACTION0);
	}

	if ((nm_cp->pkt_type == SA_NM_SECY_TAGGED) ||
	    (nm_cp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_cp, nm_cp->flow_type, EIPI_SAM_NM_FLOW_CP_FLOW_TYPE1);
		FIELD_REPLACE(_nm_cp, nm_cp->dest_port, EIPI_SAM_NM_FLOW_CP_DEST_PORT1);
		FIELD_REPLACE(_nm_cp, nm_cp->drop_non_reserved, EIPI_SAM_NM_FLOW_CP_DROP_NON_RESERVED1);
		FIELD_REPLACE(_nm_cp, nm_cp->drop_action, EIPI_SAM_NM_FLOW_CP_DROP_ACTION1);
	}

	if ((nm_cp->pkt_type == SA_NM_SECY_BAD_TAGGED) ||
	    (nm_cp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_cp, nm_cp->flow_type, EIPI_SAM_NM_FLOW_CP_FLOW_TYPE2);
		FIELD_REPLACE(_nm_cp, nm_cp->dest_port, EIPI_SAM_NM_FLOW_CP_DEST_PORT2);
		FIELD_REPLACE(_nm_cp, nm_cp->drop_non_reserved, EIPI_SAM_NM_FLOW_CP_DROP_NON_RESERVED2);
		FIELD_REPLACE(_nm_cp, nm_cp->drop_action, EIPI_SAM_NM_FLOW_CP_DROP_ACTION2);
	}

	if ((nm_cp->pkt_type == SA_NM_SECY_KAY_TAGGED) ||
	    (nm_cp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_cp, nm_cp->flow_type, EIPI_SAM_NM_FLOW_CP_FLOW_TYPE3);
		FIELD_REPLACE(_nm_cp, nm_cp->dest_port, EIPI_SAM_NM_FLOW_CP_DEST_PORT3);
		FIELD_REPLACE(_nm_cp, nm_cp->drop_non_reserved, EIPI_SAM_NM_FLOW_CP_DROP_NON_RESERVED3);
		FIELD_REPLACE(_nm_cp, nm_cp->drop_action, EIPI_SAM_NM_FLOW_CP_DROP_ACTION3);
	}

	/* Set SAM_NM_FLOW_CP data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _nm_cp);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_FLOW_CP set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_sa_nm_cp(struct gpy211_device *phy,
				    const struct sa_nonmatch_fca *nm_cp)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _nm_cp = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || nm_cp == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA non-match CP params */
	if ((nm_cp->pkt_type > SA_NM_SECY_ALL_TAGGED) ||
	    (nm_cp->flow_type > SA_NM_FCA_FLOW_DROP) ||
	    (nm_cp->dest_port > SA_NM_FCA_DPT_UNCONTROL) ||
	    (nm_cp->drop_action > SA_NM_FCA_NO_DROP)) {
		LOG_WARN("WARN: Invalid input SA non-match CP params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;
	_offset = EIPE_SAM_NM_FLOW_CP;
	_target_addr = _base_addr + _offset;

	/* Get SAM_NM_FLOW_CP */
	ret = PHY_MBOX_READ(phy, _target_addr, &_nm_cp);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_FLOW_CP get fails\n");
		goto END;
	}

	if ((nm_cp->pkt_type == SA_NM_SECY_UNTAGGED) ||
	    (nm_cp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_cp, nm_cp->flow_type, EIPE_SAM_NM_FLOW_CP_FLOW_TYPE0);
		FIELD_REPLACE(_nm_cp, nm_cp->dest_port, EIPE_SAM_NM_FLOW_CP_DEST_PORT0);
		FIELD_REPLACE(_nm_cp, nm_cp->drop_action, EIPE_SAM_NM_FLOW_CP_DROP_ACTION0);
	}

	if ((nm_cp->pkt_type == SA_NM_SECY_TAGGED) ||
	    (nm_cp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_cp, nm_cp->flow_type, EIPE_SAM_NM_FLOW_CP_FLOW_TYPE1);
		FIELD_REPLACE(_nm_cp, nm_cp->dest_port, EIPE_SAM_NM_FLOW_CP_DEST_PORT1);
		FIELD_REPLACE(_nm_cp, nm_cp->drop_action, EIPE_SAM_NM_FLOW_CP_DROP_ACTION1);
	}

	if ((nm_cp->pkt_type == SA_NM_SECY_BAD_TAGGED) ||
	    (nm_cp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_cp, nm_cp->flow_type, EIPE_SAM_NM_FLOW_CP_FLOW_TYPE2);
		FIELD_REPLACE(_nm_cp, nm_cp->dest_port, EIPE_SAM_NM_FLOW_CP_DEST_PORT2);
		FIELD_REPLACE(_nm_cp, nm_cp->drop_action, EIPE_SAM_NM_FLOW_CP_DROP_ACTION2);
	}

	if ((nm_cp->pkt_type == SA_NM_SECY_KAY_TAGGED) ||
	    (nm_cp->pkt_type == SA_NM_SECY_ALL_TAGGED)) {
		FIELD_REPLACE(_nm_cp, nm_cp->flow_type, EIPE_SAM_NM_FLOW_CP_FLOW_TYPE3);
		FIELD_REPLACE(_nm_cp, nm_cp->dest_port, EIPE_SAM_NM_FLOW_CP_DEST_PORT3);
		FIELD_REPLACE(_nm_cp, nm_cp->drop_action, EIPE_SAM_NM_FLOW_CP_DROP_ACTION3);
	}

	/* Set SAM_NM_FLOW_CP data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _nm_cp);

	if (ret < 0) {
		LOG_CRIT("ERROR: SAM_NM_FLOW_CP set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_ing_stats_summ(struct gpy211_device *phy,
				     const struct stats_summary *xxx_sum)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || xxx_sum == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < ((phy->nr_of_sas) / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		_offset = i * 4 + EIPI_COUNT_SUMMARY_PSA1;
		_target_addr = _base_addr + _offset;
		/* Set COUNT_SUMMARY_PSA1x data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, xxx_sum->psa_sum_word[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_PSA1x set fails\n");
			goto END;
		}
	}

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPI_COUNT_SUMMARY_GL;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_SUMMARY_GL data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, xxx_sum->glb_summ_word);

	if (ret < 0) {
		LOG_CRIT("ERROR: COUNT_SUMMARY_GL set fails\n");
		goto END;
	}

#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < MAX_VLAN_COUNT_SUMM_WORDS; i++) {
		_offset = i * 4 + EIPI_COUNT_SUMMARY_VL1;
		_target_addr = _base_addr + _offset;
		/* Set COUNT_SUMMARY_VLx data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, xxx_sum->vlan_summ_word[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_VLx set fails\n");
			goto END;
		}
	}

#endif

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_egr_stats_summ(struct gpy211_device *phy,
				     const struct stats_summary *xxx_sum)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || xxx_sum == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPE_COUNT_SUMMARY_GL;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_SUMMARY_GL data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, xxx_sum->glb_summ_word);

	if (ret < 0) {
		LOG_CRIT("ERROR: COUNT_SUMMARY_GL set fails\n");
		goto END;
	}

#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < MAX_VLAN_COUNT_SUMM_WORDS; i++) {
		_offset = i * 4 + EIPE_COUNT_SUMMARY_VL1;
		_target_addr = _base_addr + _offset;
		/* Set COUNT_SUMMARY_VLx data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, xxx_sum->vlan_summ_word[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_VLx set fails\n");
			goto END;
		}
	}

#endif

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < ((phy->nr_of_sas) / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		_offset = i * 4 + EIPE_COUNT_SUMMARY_PSA1;
		_target_addr = _base_addr + _offset;
		/* Set COUNT_SUMMARY_PSA1x data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, xxx_sum->psa_sum_word[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_PSA1x set fails\n");
			goto END;
		}
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_stats_summ(struct gpy211_device *phy,
				   struct stats_summary *xxx_sum)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || xxx_sum == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < ((phy->nr_of_sas) / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		_offset = i * 4 + EIPI_COUNT_SUMMARY_PSA1;
		_target_addr = _base_addr + _offset;
		/* Get COUNT_SUMMARY_PSA1x data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_PSA1x get fails\n");
			goto END;
		}

		xxx_sum->psa_sum_word[i] = _data;
	}

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPI_COUNT_SUMMARY_GL;
	_target_addr = _base_addr + _offset;

	/* Get COUNT_SUMMARY_GL data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: COUNT_SUMMARY_GL get fails\n");
		goto END;
	}

	xxx_sum->glb_summ_word = _data;

#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < MAX_VLAN_COUNT_SUMM_WORDS; i++) {
		_offset = i * 4 + EIPI_COUNT_SUMMARY_VL1;
		_target_addr = _base_addr + _offset;
		/* Get COUNT_SUMMARY_VLx data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_VLx get fails\n");
			goto END;
		}

		xxx_sum->vlan_summ_word[i] = _data;
	}

#endif

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_stats_summ(struct gpy211_device *phy,
				   struct stats_summary *xxx_sum)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || xxx_sum == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;
	_offset = EIPE_COUNT_SUMMARY_GL;
	_target_addr = _base_addr + _offset;

	/* Get COUNT_SUMMARY_GL data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: COUNT_SUMMARY_GL get fails\n");
		goto END;
	}

	xxx_sum->glb_summ_word = _data;

#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < MAX_VLAN_COUNT_SUMM_WORDS; i++) {
		_offset = i * 4 + EIPE_COUNT_SUMMARY_VL1;
		_target_addr = _base_addr + _offset;
		/* Get COUNT_SUMMARY_VLx data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_VLx get fails\n");
			goto END;
		}

		xxx_sum->vlan_summ_word[i] = _data;
	}

#endif

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < ((phy->nr_of_sas) / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		_offset = i * 4 + EIPE_COUNT_SUMMARY_PSA1;
		_target_addr = _base_addr + _offset;
		/* Get COUNT_SUMMARY_PSA1x data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_PSA1x get fails\n");
			goto END;
		}

		xxx_sum->psa_sum_word[i] = _data;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_ing_psa_stats_summ(struct gpy211_device *phy,
		const struct psa_summary *psa_sum)
{
	int i, ret = 0;
	u32 _base_addr, _offset, _target_addr;

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < (phy->nr_of_sas); i++) {
		if (i == MACSEC_MAX_SA_RULES)
			break;

		if (psa_sum->psa_type == PSA_SUMM_GET_GIVEN)
			_offset = (psa_sum->rule_index) * 4 + EIPI_COUNT_SUMMARY_SA0;
		else
			_offset =  i * 4 + EIPI_COUNT_SUMMARY_SA0;

		_target_addr = _base_addr + _offset;
		/* Set 'COUNT_SUMMARY_SAx' for SA counters statistics summary */
		ret = PHY_MBOX_WRITE(phy, _target_addr, psa_sum->count_summ_psa[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_SAx set fails\n");
			goto END;
		}

		if (psa_sum->psa_type == PSA_SUMM_GET_GIVEN)
			break;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_psa_stats_summ(struct gpy211_device *phy,
				       struct psa_summary *psa_sum)
{
	int i, ret = 0;
	u32 _base_addr, _offset, _target_addr, _data;

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < (phy->nr_of_sas); i++) {
		if (i == MACSEC_MAX_SA_RULES)
			break;

		if (psa_sum->psa_type == PSA_SUMM_GET_GIVEN)
			_offset = (psa_sum->rule_index) * 4 + EIPI_COUNT_SUMMARY_SA0;
		else
			_offset =  i * 4 + EIPI_COUNT_SUMMARY_SA0;

		_target_addr = _base_addr + _offset;
		/* Set 'COUNT_SUMMARY_SAx' for SA counters statistics summary */
		ret = PHY_MBOX_READ(phy, _target_addr, &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_SAx get fails\n");
			goto END;
		}

		psa_sum->count_summ_psa[i] = _data;

		if (psa_sum->psa_type == PSA_SUMM_GET_GIVEN)
			break;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_egr_psa_stats_summ(struct gpy211_device *phy,
		const struct psa_summary *psa_sum)
{
	int i, ret = 0;
	u32 _base_addr, _offset, _target_addr;

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < (phy->nr_of_sas); i++) {
		if (i == MACSEC_MAX_SA_RULES)
			break;

		if (psa_sum->psa_type == PSA_SUMM_GET_GIVEN)
			_offset = (psa_sum->rule_index) * 4 + EIPE_COUNT_SUMMARY_SA0;
		else
			_offset =  i * 4 + EIPE_COUNT_SUMMARY_SA0;

		_target_addr = _base_addr + _offset;
		/* Set 'COUNT_SUMMARY_SAx' for SA counters statistics summary */
		ret = PHY_MBOX_WRITE(phy, _target_addr, psa_sum->count_summ_psa[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_SAx get fails\n");
			goto END;
		}

		if (psa_sum->psa_type == PSA_SUMM_GET_GIVEN)
			break;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_psa_stats_summ(struct gpy211_device *phy,
				       struct psa_summary *psa_sum)
{
	int i, ret = 0;
	u32 _base_addr, _offset, _target_addr, _data;

	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_STAT_CONTROL_MODULE_BASE;

	for (i = 0; i < (phy->nr_of_sas); i++) {
		if (i == MACSEC_MAX_SA_RULES)
			break;

		if (psa_sum->psa_type == PSA_SUMM_GET_GIVEN)
			_offset = (psa_sum->rule_index) * 4 + EIPE_COUNT_SUMMARY_SA0;
		else
			_offset =  i * 4 + EIPE_COUNT_SUMMARY_SA0;

		_target_addr = _base_addr + _offset;
		/* Set 'COUNT_SUMMARY_SAx' for SA counters statistics summary */
		ret = PHY_MBOX_READ(phy, _target_addr, &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: COUNT_SUMMARY_SAx get fails\n");
			goto END;
		}

		psa_sum->count_summ_psa[i] = _data;

		if (psa_sum->psa_type == PSA_SUMM_GET_GIVEN)
			break;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_cp_rule(struct gpy211_device *phy,
				   const struct cp_class_param *in_cpc)
{
	int i, num_words = 0, ret;
	u32 _base_addr, _offset, _target_addr;
	u32 *_cpc_rule = NULL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_cpc == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (in_cpc->cpc_type > CPC_ENTRY_ETH) {
		LOG_WARN("WARN: Invalid input (cpc_type) - CPC entry type\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_CLASSIFIER_CONTROL_PACKET_MODULE_BASE;

	/* Set Control Packet Classification rule */
	_cpc_rule = os_alloc(IE_MAX_CPC_SIZE_BYTES);

	if (!_cpc_rule) {
		LOG_CRIT("Memory alloc failed :- %s\n", __func__);
		ret = -ENOMEM;
		goto END;
	}

	memset(_cpc_rule, 0, IE_MAX_CPC_SIZE_BYTES);

	/* Populate the 'num_words' to write */
	num_words = 2;

	if (in_cpc->cpc_type != CPC_ENTRY_ETH) {
		/* Populate DA_MAC / DA_MAC_START / DA_MAC_CONST44 / DAM_MAC_CONST48 */
		_cpc_rule[0] = ((in_cpc->mac_da[0] << 00) | (in_cpc->mac_da[1] <<  8) |
				(in_cpc->mac_da[2] << 16) | (in_cpc->mac_da[3] << 24));
		_cpc_rule[1] = ((in_cpc->mac_da[4] << 00) | (in_cpc->mac_da[5] <<  8));
		_offset = 0;
	} else if (in_cpc->cpc_type == CPC_ENTRY_ETH) {
		if ((in_cpc->cpc_index < 10) || (in_cpc->cpc_index < 17)) {
			LOG_WARN("WARN: Invalid input (entry_num) - CPC ETH num\n");
			ret = -EINVAL;
			goto END;
		}

		_offset = ((in_cpc->cpc_index - 10) * IE_CPC_ETH_SIZE_BYTES) +
			  EIPI_CP_MAC_ET_MATCH_10;
		/* Overwrite the populated '_cpc_rule[0]' with EthType only */
		_cpc_rule[0] = BYTE_SWAP_16BIT(in_cpc->ether_type) << 16;
		/* Reset the populated '_cpc_rule[1]' with 0 */
		_cpc_rule[1] = 0; /* Not required */
		/* Update the populated 'num_words' to write */
		num_words = 1;
	}

	if (in_cpc->cpc_type == CPC_ENTRY_DA_ETH) {
		if (in_cpc->cpc_index > 9) {
			LOG_WARN("WARN: Invalid input (entry_num) - CPC DA_ETH num\n");
			ret = -EINVAL;
			goto END;
		}

		_offset = (in_cpc->cpc_index) * IE_CPC_DA_ETH_SIZE_BYTES;
		/* DA_MAC is already populated in '_cpc_rule[0 & 1]' */
		/* Now populate EthType field */
		_cpc_rule[1] = (_cpc_rule[1] | (BYTE_SWAP_16BIT(in_cpc->ether_type) << 16));
	} else if (in_cpc->cpc_type == CPC_ENTRY_DA_RANGE) {
		_offset =  EIPI_CP_MAC_DA_START_LO;

		/* DA_MAC_START is already populated in '_cpc_rule[2 & 3]' */
		/* Now populate DA_MAC_END in '_cpc_rule[01]' */
		_cpc_rule[2] = ((in_cpc->mac_da_end[0] << 00) |
				(in_cpc->mac_da_end[1] <<  8) |
				(in_cpc->mac_da_end[2] << 16) |
				(in_cpc->mac_da_end[3] << 24));
		_cpc_rule[3] = ((in_cpc->mac_da_end[4] << 00) |
				(in_cpc->mac_da_end[5] <<  8));
		/* Update the populated 'num_words' to write */
		num_words = 4;
	} else if (in_cpc->cpc_type == CPC_ENTRY_DA_CONST44)
		/* DA_MAC_CONST44 is already populated in '_cpc_rule[0 & 1]' */
		_offset =  EIPI_CP_MAC_DA_44_BITS_LO;
	else if (in_cpc->cpc_type == CPC_ENTRY_DA_CONST48)
		/* DA_MAC_CONST48 is already populated in '_cpc_rule[0 & 1]' */
		_offset =  EIPI_CP_MAC_DA_48_BITS_LO;

	_target_addr = _base_addr + _offset;

	for (i = 0; i < num_words; i++) {
		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), _cpc_rule[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: CPC write fails for iteration %d\n", i);
			goto END;
		}
	}

	_offset = EIPI_CP_MATCH_MODE;
	_target_addr = _base_addr + _offset;
	/* Set Control Packet Classification match mode */
	ret = PHY_MBOX_WRITE(phy, _target_addr,
			     in_cpc->cpm_mode.cp_match_mask);

	if (ret < 0) {
		LOG_CRIT("ERROR: CP match mode set failed\n");
		goto END;
	}

	_offset = EIPI_CP_MATCH_ENABLE;
	_target_addr = _base_addr + _offset;
	/* Set Control Packet Classification match enable */
	ret = PHY_MBOX_WRITE(phy, _target_addr,
			     in_cpc->cpm_enable.cp_match_en);

	if (ret < 0) {
		LOG_CRIT("ERROR: CP match enable set failed\n");
		goto END;
	}

END:

	if (_cpc_rule != NULL) {
		memset(_cpc_rule, 0, sizeof(*_cpc_rule));
		os_free(_cpc_rule);
	}

	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_cp_rule(struct gpy211_device *phy,
				   const struct cp_class_param *in_cpc)
{
	int i, num_words = 0, ret;
	u32 _base_addr, _offset, _target_addr;
	u32 *_cpc_rule = NULL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_cpc == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA rule num range */
	if (in_cpc->cpc_type > CPC_ENTRY_ETH) {
		LOG_WARN("WARN: Invalid input (cpc_type) - CPC entry type\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_CLASSIFIER_CONTROL_PACKET_MODULE_BASE;

	/* Set Control Packet Classification rule */
	_cpc_rule = os_alloc(IE_MAX_CPC_SIZE_BYTES);

	if (!_cpc_rule) {
		LOG_CRIT("Memory alloc failed :- %s\n", __func__);
		ret = -ENOMEM;
		goto END;
	}

	memset(_cpc_rule, 0, IE_MAX_CPC_SIZE_BYTES);

	/* Populate the 'num_words' to write */
	num_words = 2;

	if (in_cpc->cpc_type != CPC_ENTRY_ETH) {
		/* Populate DA_MAC / DA_MAC_START / DA_MAC_CONST44 / DAM_MAC_CONST48 */
		_cpc_rule[0] = ((in_cpc->mac_da[0] << 00) | (in_cpc->mac_da[1] <<  8) |
				(in_cpc->mac_da[2] << 16) | (in_cpc->mac_da[3] << 24));
		_cpc_rule[1] = ((in_cpc->mac_da[4] << 00) | (in_cpc->mac_da[5] <<  8));
		_offset = 0;
	} else if (in_cpc->cpc_type == CPC_ENTRY_ETH) {
		if ((in_cpc->cpc_index < 10) || (in_cpc->cpc_index < 17)) {
			LOG_WARN("WARN: Invalid input (entry_num) - CPC ETH num\n");
			ret = -EINVAL;
			goto END;
		}

		_offset = ((in_cpc->cpc_index - 10) * IE_CPC_ETH_SIZE_BYTES) +
			  EIPE_CP_MAC_ET_MATCH_10;
		/* Overwrite the populated '_cpc_rule[0]' with EthType only */
		_cpc_rule[0] = BYTE_SWAP_16BIT(in_cpc->ether_type) << 16;
		/* Reset the populated '_cpc_rule[1]' with 0 */
		_cpc_rule[1] = 0; /* Not required */
		/* Update the populated 'num_words' to write */
		num_words = 1;
	}

	if (in_cpc->cpc_type == CPC_ENTRY_DA_ETH) {
		if (in_cpc->cpc_index > 9) {
			LOG_WARN("WARN: Invalid input (entry_num) - CPC DA_ETH num\n");
			ret = -EINVAL;
			goto END;
		}

		_offset = (in_cpc->cpc_index) * IE_CPC_DA_ETH_SIZE_BYTES;
		/* DA_MAC is already populated in '_cpc_rule[0 & 1]' */
		/* Now populate EthType field */
		_cpc_rule[1] = (_cpc_rule[1] | (BYTE_SWAP_16BIT(in_cpc->ether_type) << 16));
	} else if (in_cpc->cpc_type == CPC_ENTRY_DA_RANGE) {
		_offset =  EIPE_CP_MAC_DA_START_LO;

		/* DA_MAC_START is already populated in '_cpc_rule[2 & 3]' */
		/* Now populate DA_MAC_END in '_cpc_rule[01]' */
		_cpc_rule[2] = ((in_cpc->mac_da_end[0] << 00) |
				(in_cpc->mac_da_end[1] <<  8) |
				(in_cpc->mac_da_end[2] << 16) |
				(in_cpc->mac_da_end[3] << 24));
		_cpc_rule[3] = ((in_cpc->mac_da_end[4] << 00) |
				(in_cpc->mac_da_end[5] <<  8));
		/* Update the populated 'num_words' to write */
		num_words = 4;
	} else if (in_cpc->cpc_type == CPC_ENTRY_DA_CONST44)
		/* DA_MAC_CONST44 is already populated in '_cpc_rule[0 & 1]' */
		_offset =  EIPE_CP_MAC_DA_44_BITS_LO;
	else if (in_cpc->cpc_type == CPC_ENTRY_DA_CONST48)
		/* DA_MAC_CONST48 is already populated in '_cpc_rule[0 & 1]' */
		_offset =  EIPE_CP_MAC_DA_48_BITS_LO;

	_target_addr = _base_addr + _offset;

	for (i = 0; i < num_words; i++) {
		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), _cpc_rule[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: CPC write fails for iteration %d\n", i);
			goto END;
		}
	}

	_offset = EIPE_CP_MATCH_MODE;
	_target_addr = _base_addr + _offset;
	/* Set Control Packet Classification match mode */
	ret = PHY_MBOX_WRITE(phy, _target_addr,
			     in_cpc->cpm_mode.cp_match_mask);

	if (ret < 0) {
		LOG_CRIT("ERROR: CP match mode set failed\n");
		goto END;
	}

	_offset = EIPE_CP_MATCH_ENABLE;
	_target_addr = _base_addr + _offset;
	/* Set Control Packet Classification match enable */
	ret = PHY_MBOX_WRITE(phy, _target_addr,
			     in_cpc->cpm_enable.cp_match_en);

	if (ret < 0) {
		LOG_CRIT("ERROR: CP match enable set failed\n");
		goto END;
	}

END:

	if (_cpc_rule != NULL) {
		memset(_cpc_rule, 0, sizeof(*_cpc_rule));
		os_free(_cpc_rule);
	}

	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_cc_rule(struct gpy211_device *phy,
				   const struct icc_match_param *in_cc)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr, _byte_swapped = 0;
	u32 _icc_match[ICC_MAX_MATCH_SIZE_WORDS - 1];
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_cc == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_CC_RULES_PAGE0_MODULE_BASE +
		     ((in_cc->icc_index > 127) ? 0x10000 : 0);
	_offset = ((in_cc->icc_index) % 128) * (ICC_MAX_MATCH_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

	_byte_swapped = ((((in_cc->vlan_eth.payload_e_type >> 8) & 0xFF) << 0) |
			 (((in_cc->vlan_eth.payload_e_type) & 0xFF) << 8));

#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
	_icc_match[0] = in_cc->vlan_eth.vlan_id | (_byte_swapped << 16);
#else
	_icc_match[0] = _byte_swapped << 16;
#endif
	_icc_match[1] = in_cc->icc_misc.raw_iccm_misc;
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
	_icc_match[2] = in_cc->icc_ivl.raw_iccm_ivl;
#else
	_icc_match[2] = 0;
#endif

	/* Set ICC's rule data */
	for (i = 0; i < (ICC_MAX_MATCH_SIZE_WORDS - 1); i++) {
		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), _icc_match[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: ICC write fails for iteration %d\n", i);
			goto END;
		}
	}

END:

	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_cc_rule(struct gpy211_device *phy,
				struct icc_match_param *in_cc)
{
	int i, ret;
	u32 _base_addr, _offset, _target_addr, _byte_swapped = 0;
	u32 _icc_match[ICC_MAX_MATCH_SIZE_WORDS - 1];
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_cc == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_CC_RULES_PAGE0_MODULE_BASE +
		     ((in_cc->icc_index > 127) ? 0x10000 : 0);
	_offset = ((in_cc->icc_index) % 128) * (ICC_MAX_MATCH_SIZE_BYTES);
	_target_addr = _base_addr + _offset;

	/* Set ICC's rule data */
	for (i = 0; i < (ICC_MAX_MATCH_SIZE_WORDS - 1); i++) {
		ret = PHY_MBOX_READ(phy, _target_addr + (i * 4), &_icc_match[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: ICC read fails for iteration %d\n", i);
			goto END;
		}
	}

	_byte_swapped = ((((_icc_match[0] >> 24) & 0xFF) << 8) |
			 (((_icc_match[0] >> 16) & 0xFF) << 0));

#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
	in_cc->vlan_eth.vlan_id = _icc_match[0] & 0xFFFu;
#endif
	in_cc->vlan_eth.payload_e_type = _byte_swapped;
	in_cc->icc_misc.raw_iccm_misc = _icc_match[1];
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
	in_cc->icc_ivl.raw_iccm_ivl = _icc_match[2];
#endif

END:

	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_cc_eef(struct gpy211_device *phy,
				  const struct raw_icc_ee *in_cc)
{
	int i, ret = 0;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_cc == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_CC_CONTROL_MODULE_BASE;
	_offset = EIPI_IG_CC_ENABLE1;
	_target_addr = _base_addr + _offset;

	/* Set SAM EE flags data */
	for (i = 0; i < (phy->nr_of_sas / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		ret = PHY_MBOX_WRITE(phy, _target_addr + (i * 4), in_cc->raw_icc_ee[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: ICC EE Flags write fails for iteration %d\n", i);
			goto END;
		}
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_cc_eef(struct gpy211_device *phy,
			       struct raw_icc_ee *in_cc)
{
	int i, ret = 0;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_cc == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_CC_CONTROL_MODULE_BASE;
	_offset = EIPI_IG_CC_ENABLE1;
	_target_addr = _base_addr + _offset;

	/* Set SAM EE flags data */
	for (i = 0; i < (phy->nr_of_sas / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		ret = PHY_MBOX_READ(phy, _target_addr + (i * 4), &in_cc->raw_icc_ee[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: ICC EE Flags get fails for iteration %d\n", i);
			goto END;
		}
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_cc_ctrl(struct gpy211_device *phy,
				   const struct ing_cc_ctrl *in_ccc)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _cc_ctrl = 0, _etype_mlen = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || in_ccc == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate NM action range */
	if ((in_ccc->nm_act > 1) || (in_ccc->nm_ctrl_act > 1)) {
		LOG_WARN("WARN: Invalid input (nm_act / nm_ctrl_ac) - NM action\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_CC_CONTROL_MODULE_BASE;
	_offset = EIPI_IG_CC_CONTROL;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_cc_ctrl, in_ccc->nm_ctrl_act, EIPI_IG_CC_CONTROL_NON_MATCH_CTRL_ACT);
	FIELD_REPLACE(_cc_ctrl, in_ccc->nm_act, EIPI_IG_CC_CONTROL_NON_MATCH_ACT);

	/* Set IG CC Ctrl flags data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _cc_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: IG CC Control word set fails\n");
		goto END;
	}

	_base_addr = EIPI_EIP_160S_I_32_CC_CONTROL_MODULE_BASE;
	_offset = EIPI_IG_CC_TAGS;
	_target_addr = _base_addr + _offset;

	FIELD_REPLACE(_etype_mlen, in_ccc->cp_etype_max_len, EIPI_IG_CC_TAGS_CP_ETYPE_MAX_LEN);

	/* Set IG CC Ctrl flags data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, _etype_mlen);

	if (ret < 0) {
		LOG_CRIT("ERROR: IG CC Control word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_cc_eec(struct gpy211_device *phy,
				  const struct icc_ee_ctrl *ee_ctrl)
{
	int ret;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || ee_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_CC_CONTROL_MODULE_BASE;
	_offset = EIPI_CC_ENTRY_ENABLE_CTRL;
	_target_addr = _base_addr + _offset;

	/* Set SAM EE control data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, ee_ctrl->raw_icc_eec);

	if (ret < 0) {
		LOG_CRIT("ERROR: ICC EE control write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_sa_pn_thr_summ(struct gpy211_device *phy,
				     const struct sa_pn_thr_summ *pnthr_sum)
{
	int i, ret = -EINVAL;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || pnthr_sum == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_OPPE_MODULE_BASE;

	for (i = 0; i < ((phy->nr_of_sas) / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		_offset = i * 4 + EIPE_SA_PN_THR_SUMMARY1;
		_target_addr = _base_addr + _offset;
		/* Set SA_PN_THR_SUMMARYx data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, pnthr_sum->pnthr_sum_word[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: SA_PN_THR_SUMMARYx set fails\n");
			goto END;
		}
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_sa_pn_thr_summ(struct gpy211_device *phy,
				   struct sa_pn_thr_summ *pnthr_sum)
{
	int i, ret = -EINVAL;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || pnthr_sum == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_OPPE_MODULE_BASE;

	for (i = 0; i < ((phy->nr_of_sas) / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		_offset = i * 4 + EIPE_SA_PN_THR_SUMMARY1;
		_target_addr = _base_addr + _offset;
		/* Get SA_PN_THR_SUMMARYx data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: SA_PN_THR_SUMMARYx get fails\n");
			goto END;
		}

		pnthr_sum->pnthr_sum_word[i] = _data;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_egr_sa_exp_summ(struct gpy211_device *phy,
				      const struct sa_exp_summ *saexp_sum)
{
	int i, ret = -EINVAL;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || saexp_sum == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;

	for (i = 0; i < ((phy->nr_of_sas) / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		_offset = i * 4 + EIPE_SA_EXP_SUMMARY1;
		_target_addr = _base_addr + _offset;
		/* Set SA_EXP_SUMMARYx data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, saexp_sum->sa_expsum_word[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: SA_EXP_SUMMARYx set fails\n");
			goto END;
		}
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_sa_exp_summ(struct gpy211_device *phy,
				    struct sa_exp_summ *saexp_sum)
{
	int i, ret = -EINVAL;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || saexp_sum == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_CLASSIFIER_VARIOUS_CONTROL_REGS_MODULE_BASE;

	for (i = 0; i < ((phy->nr_of_sas) / 32); i++) {
		if (i == (MACSEC_MAX_SA_RULES / 32))
			break;

		_offset = i * 4 + EIPE_SA_EXP_SUMMARY1;
		_target_addr = _base_addr + _offset;
		/* Get SA_EXP_SUMMARYx data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_data);

		if (ret < 0) {
			LOG_CRIT("ERROR: SA_EXP_SUMMARYx get fails\n");
			goto END;
		}

		saexp_sum->sa_expsum_word[i] = _data;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_count_secfail(struct gpy211_device *phy,
		const struct count_secfail *cnt_secfail)
{
	int ret;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cnt_secfail == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_160S_I_32_OPPE_MODULE_BASE;
	_offset = EIPI_COUNT_SECFAIL1;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_SECFAIL1 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, cnt_secfail->secfail_1.raw_secfail1);

	if (ret < 0) {
		LOG_CRIT("ERROR: Counter Secfail Enable1 word set fails\n");
		goto END;
	}

	_base_addr = EIPI_EIP_160S_I_32_OPPE_MODULE_BASE;
	_offset = EIPI_COUNT_SECFAIL2;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_SECFAIL2 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, cnt_secfail->global_secfaill_mask);

	if (ret < 0) {
		LOG_CRIT("ERROR: Counter Secfail Enable2 word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_count_secfail(struct gpy211_device *phy,
		const struct count_secfail *cnt_secfail)
{
	int ret;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cnt_secfail == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_160S_E_32_OPPE_MODULE_BASE;
	_offset = EIPE_COUNT_SECFAIL1;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_SECFAIL1 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, cnt_secfail->secfail_1.raw_secfail1);

	if (ret < 0) {
		LOG_CRIT("ERROR: Counter Secfail Enable1 word set fails\n");
		goto END;
	}

	_base_addr = EIPE_EIP_160S_E_32_OPPE_MODULE_BASE;
	_offset = EIPE_COUNT_SECFAIL2;
	_target_addr = _base_addr + _offset;

	/* Set COUNT_SECFAIL2 data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, cnt_secfail->global_secfaill_mask);

	if (ret < 0) {
		LOG_CRIT("ERROR: Counter Secfail Enable2 word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_ing_cc_int_stat(struct gpy211_device *phy,
				      const struct crypto_core_stat *cc_stat)
{
	int ret;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cc_stat == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;

#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	_offset = EIPI_EIP62_CONTEXT_STAT;

	_target_addr = _base_addr + _offset;

	/* Clear Context status */
	ret = PHY_MBOX_WRITE(phy, _target_addr, cc_stat->ctx_stat.raw_ctx_stat);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_CONTEXT_STAT clear fails\n");
		goto END;
	}

#endif

	_offset = EIPI_EIP62_INT_CTRL_STAT;

	_target_addr = _base_addr + _offset;

	/* Clear Interrupt status */
	ret = PHY_MBOX_WRITE(phy, _target_addr, cc_stat->int_stat.raw_int_stat);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_INT_CTRL_STAT clear fails\n");
		goto END;
	}

#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	_offset = EIPI_EIP62_SW_INTERRUPT;

	_target_addr = _base_addr + _offset;

	/* Clear SW Interrupt */
	ret = PHY_MBOX_WRITE(phy, _target_addr, cc_stat->sw_interrupt);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_SW_INTERRUPT clear fails\n");
		goto END;
	}

#endif

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_cc_int_stat(struct gpy211_device *phy,
				    struct crypto_core_stat *cc_stat)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cc_stat == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;

#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	_offset = EIPI_EIP62_CONTEXT_STAT;

	_target_addr = _base_addr + _offset;

	/* Get Context status */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_CONTEXT_STAT clear fails\n");
		goto END;
	}

	cc_stat->ctx_stat.raw_ctx_stat = _data;
#endif

	_offset = EIPI_EIP62_INT_CTRL_STAT;

	_target_addr = _base_addr + _offset;

	/* Get Interrupt status */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_INT_CTRL_STAT clear fails\n");
		goto END;
	}

	cc_stat->int_stat.raw_int_stat = _data;

#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	_offset = EIPI_EIP62_SW_INTERRUPT;

	_target_addr = _base_addr + _offset;

	/* Get SW Interrupt */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_SW_INTERRUPT clear fails\n");
		goto END;
	}

	cc_stat->sw_interrupt = _data;
#endif

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_clear_egr_cc_int_stat(struct gpy211_device *phy,
				      const struct crypto_core_stat *cc_stat)
{
	int ret;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cc_stat == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;

#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	_offset = EIPE_EIP62_CONTEXT_STAT;

	_target_addr = _base_addr + _offset;

	/* Clear Context status */
	ret = PHY_MBOX_WRITE(phy, _target_addr, cc_stat->ctx_stat.raw_ctx_stat);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_CONTEXT_STAT clear fails\n");
		goto END;
	}

#endif

	_offset = EIPE_EIP62_INT_CTRL_STAT;

	_target_addr = _base_addr + _offset;

	/* Clear Interrupt status */
	ret = PHY_MBOX_WRITE(phy, _target_addr, cc_stat->int_stat.raw_int_stat);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_INT_CTRL_STAT clear fails\n");
		goto END;
	}

#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	_offset = EIPE_EIP62_SW_INTERRUPT;

	_target_addr = _base_addr + _offset;

	/* Clear SW Interrupt data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, cc_stat->sw_interrupt);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_SW_INTERRUPT clear fails\n");
		goto END;
	}

#endif

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_cc_int_stat(struct gpy211_device *phy,
				    struct crypto_core_stat *cc_stat)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || cc_stat == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;

#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	_offset = EIPE_EIP62_CONTEXT_STAT;

	_target_addr = _base_addr + _offset;

	/* Get Context status */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_CONTEXT_STAT clear fails\n");
		goto END;
	}

	cc_stat->ctx_stat.raw_ctx_stat = _data;
#endif

	_offset = EIPE_EIP62_INT_CTRL_STAT;

	_target_addr = _base_addr + _offset;

	/* Get Interrupt status */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_INT_CTRL_STAT clear fails\n");
		goto END;
	}

	cc_stat->int_stat.raw_int_stat = _data;

#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	_offset = EIPE_EIP62_SW_INTERRUPT;

	_target_addr = _base_addr + _offset;

	/* Get SW Interrupt data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIP62_SW_INTERRUPT clear fails\n");
		goto END;
	}

	cc_stat->sw_interrupt = _data;
#endif

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_sn_thresh(struct gpy211_device *phy,
				     const struct seq_num_thr *sn_thr)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _low_word, _high_word;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sn_thr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA non-match EXPL params */
	if (sn_thr->sn_type != SN_32_BIT && sn_thr->sn_type != SN_64_BIT) {
		LOG_WARN("WARN: Invalid input SN type params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;
	_low_word = (sn_thr->sn_threshold) & 0xFFFFFFFFu;

	if (sn_thr->sn_type == SN_32_BIT) {
		_offset = EIPI_EIP62_SEQ_NUM_THRESHOLD;
		_target_addr = _base_addr + _offset;
		/* Set EIP62_SEQ_NUM_THRESHOLD data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, _low_word);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN Treshold lower word set fails\n");
			goto END;
		}
	} else {
		_high_word = sn_thr->sn_threshold >> 32;

		_offset = EIPI_EIP62_SEQ_NUM_THRESHOLD64_LO;
		_target_addr = _base_addr + _offset;
		/* Set EIP62_SEQ_NUM_THRESHOLD64_LO data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, _low_word);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN Treshold lower word set fails\n");
			goto END;
		}

		_offset = EIPI_EIP62_SEQ_NUM_THRESHOLD64_HI;
		_target_addr = _base_addr + _offset;
		/* Set EIP62_SEQ_NUM_THRESHOLD data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, _high_word);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN Treshold lower word set fails\n");
			goto END;
		}
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_sn_thresh(struct gpy211_device *phy,
				  struct seq_num_thr *sn_thr)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _low_word, _high_word;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sn_thr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA non-match EXPL params */
	if (sn_thr->sn_type != SN_32_BIT && sn_thr->sn_type != SN_64_BIT) {
		LOG_WARN("WARN: Invalid input SN type params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;

	if (sn_thr->sn_type == SN_32_BIT) {
		_offset = EIPI_EIP62_SEQ_NUM_THRESHOLD;
		_target_addr = _base_addr + _offset;
		/* Set EIP62_SEQ_NUM_THRESHOLD data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_low_word);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN Treshold lower word set fails\n");
			goto END;
		}

		sn_thr->sn_threshold = _low_word;
	} else {
		_offset = EIPI_EIP62_SEQ_NUM_THRESHOLD64_LO;
		_target_addr = _base_addr + _offset;
		/* Set EIP62_SEQ_NUM_THRESHOLD64_LO data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_low_word);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN Treshold lower word set fails\n");
			goto END;
		}

		sn_thr->sn_threshold = _low_word;

		_offset = EIPI_EIP62_SEQ_NUM_THRESHOLD64_HI;
		_target_addr = _base_addr + _offset;
		/* Set EIP62_SEQ_NUM_THRESHOLD data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_high_word);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN Treshold lower word set fails\n");
			goto END;
		}

		sn_thr->sn_threshold |= ((u64)_high_word << 32);
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_sn_thresh(struct gpy211_device *phy,
				     const struct seq_num_thr *sn_thr)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _low_word, _high_word;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sn_thr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA non-match EXPL params */
	if (sn_thr->sn_type != SN_32_BIT && sn_thr->sn_type != SN_64_BIT) {
		LOG_WARN("WARN: Invalid input SN type params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;
	_low_word = (sn_thr->sn_threshold) & 0xFFFFFFFFu;

	if (sn_thr->sn_type == SN_32_BIT) {
		_offset = EIPE_EIP62_SEQ_NUM_THRESHOLD;
		_target_addr = _base_addr + _offset;
		/* Set EIP62_SEQ_NUM_THRESHOLD data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, _low_word);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN Treshold lower word set fails\n");
			goto END;
		}
	} else {
		_high_word = sn_thr->sn_threshold >> 32;

		_offset = EIPE_EIP62_SEQ_NUM_THRESHOLD64_LO;
		_target_addr = _base_addr + _offset;
		/* Set EIP62_SEQ_NUM_THRESHOLD64_LO data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, _low_word);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN Treshold lower word set fails\n");
			goto END;
		}

		_offset = EIPE_EIP62_SEQ_NUM_THRESHOLD64_HI;
		_target_addr = _base_addr + _offset;
		/* Set EIP62_SEQ_NUM_THRESHOLD data */
		ret = PHY_MBOX_WRITE(phy, _target_addr, _high_word);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN Treshold lower word set fails\n");
			goto END;
		}
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_sn_thresh(struct gpy211_device *phy,
				  struct seq_num_thr *sn_thr)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _low_word, _high_word;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || sn_thr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate SA non-match EXPL params */
	if (sn_thr->sn_type != SN_32_BIT && sn_thr->sn_type != SN_64_BIT) {
		LOG_WARN("WARN: Invalid input SN type params\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP160_EIP62_EIP62_REGISTERS_MODULE_BASE;

	if (sn_thr->sn_type == SN_32_BIT) {
		_offset = EIPE_EIP62_SEQ_NUM_THRESHOLD;
		_target_addr = _base_addr + _offset;
		/* Set EIP62_SEQ_NUM_THRESHOLD data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_low_word);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN Treshold lower word set fails\n");
			goto END;
		}

		sn_thr->sn_threshold = _low_word;
	} else {
		_offset = EIPE_EIP62_SEQ_NUM_THRESHOLD64_LO;
		_target_addr = _base_addr + _offset;
		/* Set EIP62_SEQ_NUM_THRESHOLD64_LO data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_low_word);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN Treshold lower word set fails\n");
			goto END;
		}

		sn_thr->sn_threshold = _low_word;

		_offset = EIPE_EIP62_SEQ_NUM_THRESHOLD64_HI;
		_target_addr = _base_addr + _offset;
		/* Set EIP62_SEQ_NUM_THRESHOLD data */
		ret = PHY_MBOX_READ(phy, _target_addr, &_high_word);

		if (ret < 0) {
			LOG_CRIT("ERROR: SN Treshold lower word set fails\n");
			goto END;
		}

		sn_thr->sn_threshold |= ((u64)_high_word << 32);
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_ing_aic_csr(struct gpy211_device *phy,
				   const struct aic_control_stat *aic_csr)
{
	int ret;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || aic_csr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_201_EIP201_REGISTERS_MODULE_BASE;
	_offset = EIPI_AIC_ENABLE_CTRL;
	_target_addr = _base_addr + _offset;

	/* Set AIC_ENABLE_CTRL data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, aic_csr->enable_ctrl.raw_aic_bits);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_ENABLE_CTRL word set fails\n");
		goto END;
	}

	_offset = EIPI_AIC_RAW_STAT_ENABLE_SET;
	_target_addr = _base_addr + _offset;

	/* Set AIC_ENABLE_SET data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, aic_csr->enable_set.raw_aic_bits);

	if (ret < 0) {
		LOG_CRIT("ERROR: ENABLED_STAT_ACK word set fails\n");
		goto END;
	}

	_offset = EIPI_AIC_ENABLED_STAT_ACK;
	_target_addr = _base_addr + _offset;

	/* Set AIC_ACK data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, aic_csr->ack.raw_aic_bits);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_ACK word set fails\n");
		goto END;
	}

	_offset = EIPI_AIC_ENABLE_CLR;
	_target_addr = _base_addr + _offset;

	/* Set AIC_ENABLE_CLR data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, aic_csr->enable_clr.raw_aic_bits);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_ENABLE_CLR word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_ing_aic_csr(struct gpy211_device *phy,
				struct aic_control_stat *aic_csr)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || aic_csr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPI_EIP_201_EIP201_REGISTERS_MODULE_BASE;
	_offset = EIPI_AIC_POL_CTRL;
	_target_addr = _base_addr + _offset;

	/* Get AIC_POL_CTRL data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_POL_CTRL word get fails\n");
		goto END;
	}

	aic_csr->pol_ctrl.raw_aic_bits = _data;

	_offset = EIPI_AIC_TYPE_CTRL;
	_target_addr = _base_addr + _offset;

	/* Get AIC_TYPE_CTRL data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_TYPE_CTRL word get fails\n");
		goto END;
	}

	aic_csr->type_ctrl.raw_aic_bits = _data;

	_offset = EIPI_AIC_ENABLE_CTRL;
	_target_addr = _base_addr + _offset;

	/* Gt AIC_ENABLE_CTRL data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_ENABLE_CTRL word get fails\n");
		goto END;
	}

	aic_csr->enable_ctrl.raw_aic_bits = _data;

	_offset = EIPI_AIC_RAW_STAT_ENABLE_SET;
	_target_addr = _base_addr + _offset;

	/* Get AIC_RAW_STAT data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_RAW_STAT word get fails\n");
		goto END;
	}

	aic_csr->raw_stat.raw_aic_bits = _data;

	_offset = EIPI_AIC_ENABLED_STAT_ACK;
	_target_addr = _base_addr + _offset;

	/* Get AIC_ENABLED_STAT data */
	ret = PHY_MBOX_READ(phy, _target_addr,	&_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_ENABLED_STAT word get fails\n");
		goto END;
	}

	aic_csr->enabled_stat.raw_aic_bits = _data;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_config_egr_aic_csr(struct gpy211_device *phy,
				   const struct aic_control_stat *aic_csr)
{
	int ret;
	u32 _base_addr, _offset, _target_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || aic_csr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_201_EIP201_REGISTERS_MODULE_BASE;
	_offset = EIPE_AIC_ENABLE_CTRL;
	_target_addr = _base_addr + _offset;

	/* Set AIC_ENABLE_CTRL data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, aic_csr->enable_ctrl.raw_aic_bits);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_ENABLE_CTRL word set fails\n");
		goto END;
	}

	_offset = EIPE_AIC_RAW_STAT_ENABLE_SET;
	_target_addr = _base_addr + _offset;

	/* Set AIC_ENABLE_SET data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, aic_csr->enable_set.raw_aic_bits);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_ENABLE_SET word set fails\n");
		goto END;
	}

	_offset = EIPE_AIC_ENABLED_STAT_ACK;
	_target_addr = _base_addr + _offset;

	/* Set AIC_ACK data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, aic_csr->ack.raw_aic_bits);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_ACK word set fails\n");
		goto END;
	}

	_offset = EIPE_AIC_ENABLE_CLR;
	_target_addr = _base_addr + _offset;

	/* Set AIC_ENABLE_CLR data */
	ret = PHY_MBOX_WRITE(phy, _target_addr, aic_csr->enable_clr.raw_aic_bits);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_ENABLE_CLR word set fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_msec_get_egr_aic_csr(struct gpy211_device *phy,
				struct aic_control_stat *aic_csr)
{
	int ret;
	u32 _base_addr, _offset, _target_addr, _data;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || aic_csr == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_base_addr = EIPE_EIP_201_EIP201_REGISTERS_MODULE_BASE;
	_offset = EIPE_AIC_POL_CTRL;
	_target_addr = _base_addr + _offset;

	/* Get AIC_POL_CTRL data */
	ret = PHY_MBOX_READ(phy, _target_addr, &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_POL_CTRL word get fails\n");
		goto END;
	}

	aic_csr->pol_ctrl.raw_aic_bits = _data;

	_offset = EIPE_AIC_TYPE_CTRL;
	_target_addr = _base_addr + _offset;

	/* Get AIC_TYPE_CTRL data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_TYPE_CTRL word get fails\n");
		goto END;
	}

	aic_csr->type_ctrl.raw_aic_bits = _data;

	_offset = EIPE_AIC_ENABLE_CTRL;
	_target_addr = _base_addr + _offset;

	/* Gt AIC_ENABLE_CTRL data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_ENABLE_CTRL word get fails\n");
		goto END;
	}

	aic_csr->enable_ctrl.raw_aic_bits = _data;

	_offset = EIPE_AIC_RAW_STAT_ENABLE_SET;
	_target_addr = _base_addr + _offset;

	/* Get AIC_RAW_STAT data */
	ret = PHY_MBOX_READ(phy, _target_addr,  &_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_RAW_STAT word get fails\n");
		goto END;
	}

	aic_csr->raw_stat.raw_aic_bits = _data;

	_offset = EIPE_AIC_ENABLED_STAT_ACK;
	_target_addr = _base_addr + _offset;

	/* Get AIC_ENABLED_STAT data */
	ret = PHY_MBOX_READ(phy, _target_addr,	&_data);

	if (ret < 0) {
		LOG_CRIT("ERROR: AIC_ENABLED_STAT word get fails\n");
		goto END;
	}

	aic_csr->enabled_stat.raw_aic_bits = _data;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}
