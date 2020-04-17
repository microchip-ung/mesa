// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_HOST_KR_DEV1_H_
#define _VTSS_MALIBU_REGS_HOST_KR_DEV1_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a HOST_KR_DEV1
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a HOST_KR_DEV1:KR_1x0096
 *
 * Not documented
 */


/** 
 * \brief KR PMD control
 *
 * \details
 * Register: \a HOST_KR_DEV1:KR_1x0096:KR_1x0096
 */
#define VTSS_HOST_KR_DEV1_KR_1x0096_KR_1x0096  VTSS_IOREG(0x09, 0, 0x0096)

/** 
 * \brief
 * Training enable  
 *
 * \details 
 * 1: Enable KR start-up protocol 
 * 0: Disable KR start-up protocol
 *
 * Field: VTSS_HOST_KR_DEV1_KR_1x0096_KR_1x0096 . tr_enable
 */
#define  VTSS_F_HOST_KR_DEV1_KR_1x0096_KR_1x0096_tr_enable  VTSS_BIT(1)

/** 
 * \brief
 * Restart training (SC) 
 *
 * \details 
 * 1: Reset KR start-up protocol 
 * 0: Normal operation
 *
 * Field: VTSS_HOST_KR_DEV1_KR_1x0096_KR_1x0096 . tr_restart
 */
#define  VTSS_F_HOST_KR_DEV1_KR_1x0096_KR_1x0096_tr_restart  VTSS_BIT(0)

/**
 * Register Group: \a HOST_KR_DEV1:KR_1x0097
 *
 * Not documented
 */


/** 
 * \brief KR PMD status
 *
 * \details
 * Register: \a HOST_KR_DEV1:KR_1x0097:KR_1x0097
 */
#define VTSS_HOST_KR_DEV1_KR_1x0097_KR_1x0097  VTSS_IOREG(0x09, 0, 0x0097)

/** 
 * \brief
 * Training failure 
 *
 * \details 
 * 1: Training failure has been detected 
 * 0: Training failure has not been detected
 *
 * Field: VTSS_HOST_KR_DEV1_KR_1x0097_KR_1x0097 . tr_fail
 */
#define  VTSS_F_HOST_KR_DEV1_KR_1x0097_KR_1x0097_tr_fail  VTSS_BIT(3)

/** 
 * \brief
 * Startup protocol status 
 *
 * \details 
 * 1: Start-up protocol in progress 
 * 0: Start-up protocol complete
 *
 * Field: VTSS_HOST_KR_DEV1_KR_1x0097_KR_1x0097 . stprot
 */
#define  VTSS_F_HOST_KR_DEV1_KR_1x0097_KR_1x0097_stprot  VTSS_BIT(2)

/** 
 * \brief
 * Frame lock 
 *
 * \details 
 * 1: Training frame delineation detected, 
 * 0: Training frame delineation not detected
 *
 * Field: VTSS_HOST_KR_DEV1_KR_1x0097_KR_1x0097 . frlock
 */
#define  VTSS_F_HOST_KR_DEV1_KR_1x0097_KR_1x0097_frlock  VTSS_BIT(1)

/** 
 * \brief
 * Receiver status 
 *
 * \details 
 * 1: Receiver trained and ready to receive data 
 * 0: Receiver training
 *
 * Field: VTSS_HOST_KR_DEV1_KR_1x0097_KR_1x0097 . rcvr_rdy
 */
#define  VTSS_F_HOST_KR_DEV1_KR_1x0097_KR_1x0097_rcvr_rdy  VTSS_BIT(0)

/**
 * Register Group: \a HOST_KR_DEV1:KR_1x0098
 *
 * Not documented
 */


/** 
 * \brief KR LP coefficient update
 *
 * \details
 * Register: \a HOST_KR_DEV1:KR_1x0098:KR_1x0098
 */
#define VTSS_HOST_KR_DEV1_KR_1x0098_KR_1x0098  VTSS_IOREG(0x09, 0, 0x0098)

/** 
 * \brief
 * Received coefficient update field
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_KR_1x0098_KR_1x0098 . lpcoef
 */
#define  VTSS_F_HOST_KR_DEV1_KR_1x0098_KR_1x0098_lpcoef(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_KR_1x0098_KR_1x0098_lpcoef     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_KR_1x0098_KR_1x0098_lpcoef(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_KR_DEV1:KR_1x0099
 *
 * Not documented
 */


/** 
 * \brief KR LP status report
 *
 * \details
 * Register: \a HOST_KR_DEV1:KR_1x0099:KR_1x0099
 */
#define VTSS_HOST_KR_DEV1_KR_1x0099_KR_1x0099  VTSS_IOREG(0x09, 0, 0x0099)

/** 
 * \brief
 * Received status report field
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_KR_1x0099_KR_1x0099 . lpstat
 */
#define  VTSS_F_HOST_KR_DEV1_KR_1x0099_KR_1x0099_lpstat(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_KR_1x0099_KR_1x0099_lpstat     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_KR_1x0099_KR_1x0099_lpstat(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_KR_DEV1:KR_1x009A
 *
 * Not documented
 */


/** 
 * \brief KR LD coefficient update
 *
 * \details
 * Register: \a HOST_KR_DEV1:KR_1x009A:KR_1x009A
 */
#define VTSS_HOST_KR_DEV1_KR_1x009A_KR_1x009A  VTSS_IOREG(0x09, 0, 0x009a)

/** 
 * \brief
 * Transmitted coefficient update field
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_KR_1x009A_KR_1x009A . ldcoef
 */
#define  VTSS_F_HOST_KR_DEV1_KR_1x009A_KR_1x009A_ldcoef(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_KR_1x009A_KR_1x009A_ldcoef     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_KR_1x009A_KR_1x009A_ldcoef(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_KR_DEV1:KR_1x009B
 *
 * Not documented
 */


/** 
 * \brief KR LD status report
 *
 * \details
 * Register: \a HOST_KR_DEV1:KR_1x009B:KR_1x009B
 */
#define VTSS_HOST_KR_DEV1_KR_1x009B_KR_1x009B  VTSS_IOREG(0x09, 0, 0x009b)

/** 
 * \brief
 * Transmitted status report field
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_KR_1x009B_KR_1x009B . ldstat
 */
#define  VTSS_F_HOST_KR_DEV1_KR_1x009B_KR_1x009B_ldstat(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_KR_1x009B_KR_1x009B_ldstat     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_KR_1x009B_KR_1x009B_ldstat(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_KR_DEV1:tr_cfg0
 *
 * Not documented
 */


/** 
 * \brief VS training config 0
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_cfg0:tr_cfg0
 */
#define VTSS_HOST_KR_DEV1_tr_cfg0_tr_cfg0    VTSS_IOREG(0x09, 0, 0x8200)

/** 
 * \brief
 * Clock divider value for timer clocks.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg0_tr_cfg0 . tmr_dvdr
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg0_tr_cfg0_tmr_dvdr(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg0_tr_cfg0_tmr_dvdr     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg0_tr_cfg0_tmr_dvdr(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Invert recieved prbs11 within training frame
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg0_tr_cfg0 . rx_inv
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg0_tr_cfg0_rx_inv  VTSS_BIT(10)

/** 
 * \brief
 * Invert transmitted prbs11 within training frame
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg0_tr_cfg0 . tx_inv
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg0_tr_cfg0_tx_inv  VTSS_BIT(9)

/** 
 * \brief
 * Set local taps starting point 
 *
 * \details 
 * 0: Set to INITIALIZE 
 * 1: Set to PRESET
 *
 * Field: VTSS_HOST_KR_DEV1_tr_cfg0_tr_cfg0 . ld_pre_init
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg0_tr_cfg0_ld_pre_init  VTSS_BIT(4)

/** 
 * \brief
 * Send first LP request 
 *
 * \details 
 * 0: Send   INITIALIZE 
 * 1: Send   PRESET
 *
 * Field: VTSS_HOST_KR_DEV1_tr_cfg0_tr_cfg0 . lp_pre_init
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg0_tr_cfg0_lp_pre_init  VTSS_BIT(3)

/** 
 * \brief
 * Update taps regardless of v2,vp sum.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg0_tr_cfg0 . nosum
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg0_tr_cfg0_nosum  VTSS_BIT(2)

/** 
 * \brief
 * Enable partial OB tap configuration.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg0_tr_cfg0 . part_cfg_en
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg0_tr_cfg0_part_cfg_en  VTSS_BIT(1)

/** 
 * \brief
 * Allow LP to to control tap settings.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg0_tr_cfg0 . tapctl_en
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg0_tr_cfg0_tapctl_en  VTSS_BIT(0)

/**
 * Register Group: \a HOST_KR_DEV1:tr_cfg1
 *
 * Not documented
 */


/** 
 * \brief VS training config 1
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_cfg1:tr_cfg1
 */
#define VTSS_HOST_KR_DEV1_tr_cfg1_tr_cfg1    VTSS_IOREG(0x09, 0, 0x8201)

/** 
 * \brief
 * Freeze timers. Bit set... 
 *
 * \details 
 * 0: wait 
 * 1: max_wait 
 * 2: 1g 
 * 3: 3g 
 * 4: 10g 
 * 5: training
 * 6: pgdet 
 * 7: link_pass 
 * 8: link_fail 
 * 9: an_wait 
 * 10: break_link
 *
 * Field: VTSS_HOST_KR_DEV1_tr_cfg1_tr_cfg1 . tmr_hold
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg1_tr_cfg1_tmr_hold(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg1_tr_cfg1_tmr_hold     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg1_tr_cfg1_tmr_hold(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * Register Group: \a HOST_KR_DEV1:tr_cfg2
 *
 * Not documented
 */


/** 
 * \brief VS training config 2
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_cfg2:tr_cfg2
 */
#define VTSS_HOST_KR_DEV1_tr_cfg2_tr_cfg2    VTSS_IOREG(0x09, 0, 0x8202)

/** 
 * \brief
 * max	settings for vp sum.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg2_tr_cfg2 . vp_max
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg2_tr_cfg2_vp_max(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg2_tr_cfg2_vp_max     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg2_tr_cfg2_vp_max(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * min	settings for v2 sum.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg2_tr_cfg2 . v2_min
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg2_tr_cfg2_v2_min(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg2_tr_cfg2_v2_min     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg2_tr_cfg2_v2_min(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a HOST_KR_DEV1:tr_cfg3
 *
 * Not documented
 */


/** 
 * \brief VS training config 3
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_cfg3:tr_cfg3
 */
#define VTSS_HOST_KR_DEV1_tr_cfg3_tr_cfg3    VTSS_IOREG(0x09, 0, 0x8203)

/** 
 * \brief
 * max	settings for local transmitter.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg3_tr_cfg3 . cp_max
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg3_tr_cfg3_cp_max(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg3_tr_cfg3_cp_max     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg3_tr_cfg3_cp_max(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * min	settings for local transmitter.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg3_tr_cfg3 . cp_min
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg3_tr_cfg3_cp_min(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg3_tr_cfg3_cp_min     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg3_tr_cfg3_cp_min(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a HOST_KR_DEV1:tr_cfg4
 *
 * Not documented
 */


/** 
 * \brief VS training config 4
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_cfg4:tr_cfg4
 */
#define VTSS_HOST_KR_DEV1_tr_cfg4_tr_cfg4    VTSS_IOREG(0x09, 0, 0x8204)

/** 
 * \brief
 * max	settings for local transmitter.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg4_tr_cfg4 . c0_max
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg4_tr_cfg4_c0_max(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg4_tr_cfg4_c0_max     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg4_tr_cfg4_c0_max(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * min	settings for local transmitter.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg4_tr_cfg4 . c0_min
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg4_tr_cfg4_c0_min(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg4_tr_cfg4_c0_min     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg4_tr_cfg4_c0_min(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a HOST_KR_DEV1:tr_cfg5
 *
 * Not documented
 */


/** 
 * \brief VS training config 5
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_cfg5:tr_cfg5
 */
#define VTSS_HOST_KR_DEV1_tr_cfg5_tr_cfg5    VTSS_IOREG(0x09, 0, 0x8205)

/** 
 * \brief
 * max	settings for local transmitter.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg5_tr_cfg5 . cm_max
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg5_tr_cfg5_cm_max(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg5_tr_cfg5_cm_max     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg5_tr_cfg5_cm_max(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * min	settings for local transmitter.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg5_tr_cfg5 . cm_min
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg5_tr_cfg5_cm_min(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg5_tr_cfg5_cm_min     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg5_tr_cfg5_cm_min(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a HOST_KR_DEV1:tr_cfg6
 *
 * Not documented
 */


/** 
 * \brief VS training config 6
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_cfg6:tr_cfg6
 */
#define VTSS_HOST_KR_DEV1_tr_cfg6_tr_cfg6    VTSS_IOREG(0x09, 0, 0x8206)

/** 
 * \brief
 * initialize settings for local transmitter.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg6_tr_cfg6 . cp_init
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg6_tr_cfg6_cp_init(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg6_tr_cfg6_cp_init     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg6_tr_cfg6_cp_init(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * initialize settings for local transmitter.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg6_tr_cfg6 . c0_init
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg6_tr_cfg6_c0_init(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg6_tr_cfg6_c0_init     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg6_tr_cfg6_c0_init(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a HOST_KR_DEV1:tr_cfg7
 *
 * Not documented
 */


/** 
 * \brief VS training config 7
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_cfg7:tr_cfg7
 */
#define VTSS_HOST_KR_DEV1_tr_cfg7_tr_cfg7    VTSS_IOREG(0x09, 0, 0x8207)

/** 
 * \brief
 * initialize settings for local transmitter.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg7_tr_cfg7 . cm_init
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg7_tr_cfg7_cm_init(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg7_tr_cfg7_cm_init     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg7_tr_cfg7_cm_init(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Signed value to adjust final LP C(+1) tap position from calculated
 * optimal setting.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg7_tr_cfg7 . dfe_ofs
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg7_tr_cfg7_dfe_ofs(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg7_tr_cfg7_dfe_ofs     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg7_tr_cfg7_dfe_ofs(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a HOST_KR_DEV1:tr_cfg8
 *
 * Not documented
 */


/** 
 * \brief VS training config 8
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_cfg8:tr_cfg8
 */
#define VTSS_HOST_KR_DEV1_tr_cfg8_tr_cfg8    VTSS_IOREG(0x09, 0, 0x8208)

/** 
 * \brief
 * Weighted average calculation of DFE tap 1
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg8_tr_cfg8 . wt1
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg8_tr_cfg8_wt1(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg8_tr_cfg8_wt1     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg8_tr_cfg8_wt1(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Weighted average calculation of DFE tap 2
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg8_tr_cfg8 . wt2
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg8_tr_cfg8_wt2(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg8_tr_cfg8_wt2     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg8_tr_cfg8_wt2(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Weighted average calculation of DFE tap 3
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg8_tr_cfg8 . wt3
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg8_tr_cfg8_wt3(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg8_tr_cfg8_wt3     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg8_tr_cfg8_wt3(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Weighted average calculation of DFE tap 4
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg8_tr_cfg8 . wt4
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg8_tr_cfg8_wt4(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg8_tr_cfg8_wt4     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg8_tr_cfg8_wt4(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a HOST_KR_DEV1:tr_cfg9
 *
 * Not documented
 */


/** 
 * \brief VS training config 9
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_cfg9:tr_cfg9
 */
#define VTSS_HOST_KR_DEV1_tr_cfg9_tr_cfg9    VTSS_IOREG(0x09, 0, 0x8209)

/** 
 * \brief
 * Number of training frames used for BER calculation.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_cfg9_tr_cfg9 . frcnt_ber
 */
#define  VTSS_F_HOST_KR_DEV1_tr_cfg9_tr_cfg9_frcnt_ber(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_tr_cfg9_tr_cfg9_frcnt_ber     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_tr_cfg9_tr_cfg9_frcnt_ber(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_KR_DEV1:tr_gain
 *
 * Not documented
 */


/** 
 * \brief VS training gain target and margin values
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_gain:tr_gain
 */
#define VTSS_HOST_KR_DEV1_tr_gain_tr_gain    VTSS_IOREG(0x09, 0, 0x820a)

/** 
 * \brief
 * LP C(0) optimized when GAIN is gain_targ +/- 2*gain_marg
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_gain_tr_gain . gain_marg
 */
#define  VTSS_F_HOST_KR_DEV1_tr_gain_tr_gain_gain_marg(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_HOST_KR_DEV1_tr_gain_tr_gain_gain_marg     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_HOST_KR_DEV1_tr_gain_tr_gain_gain_marg(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Target value of GAIN setting during LP C(0) optimization.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_gain_tr_gain . gain_targ
 */
#define  VTSS_F_HOST_KR_DEV1_tr_gain_tr_gain_gain_targ(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_HOST_KR_DEV1_tr_gain_tr_gain_gain_targ     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_HOST_KR_DEV1_tr_gain_tr_gain_gain_targ(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * Register Group: \a HOST_KR_DEV1:tr_coef_ovrd
 *
 * Not documented
 */


/** 
 * \brief VS training coefficient update override
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_coef_ovrd:tr_coef_ovrd
 */
#define VTSS_HOST_KR_DEV1_tr_coef_ovrd_tr_coef_ovrd  VTSS_IOREG(0x09, 0, 0x820b)

/** 
 * \brief
 * Override Coef_update field to transmit
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_coef_ovrd_tr_coef_ovrd . coef_ovrd
 */
#define  VTSS_F_HOST_KR_DEV1_tr_coef_ovrd_tr_coef_ovrd_coef_ovrd(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_tr_coef_ovrd_tr_coef_ovrd_coef_ovrd     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_tr_coef_ovrd_tr_coef_ovrd_coef_ovrd(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_KR_DEV1:tr_stat_ovrd
 *
 * Not documented
 */


/** 
 * \brief VS training status report override
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_stat_ovrd:tr_stat_ovrd
 */
#define VTSS_HOST_KR_DEV1_tr_stat_ovrd_tr_stat_ovrd  VTSS_IOREG(0x09, 0, 0x820c)

/** 
 * \brief
 * Override Stat_report field to transmit
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_stat_ovrd_tr_stat_ovrd . stat_ovrd
 */
#define  VTSS_F_HOST_KR_DEV1_tr_stat_ovrd_tr_stat_ovrd_stat_ovrd(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_tr_stat_ovrd_tr_stat_ovrd_stat_ovrd     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_tr_stat_ovrd_tr_stat_ovrd_stat_ovrd(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_KR_DEV1:tr_ovrd
 *
 * Not documented
 */


/** 
 * \brief VS training override
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_ovrd:tr_ovrd
 */
#define VTSS_HOST_KR_DEV1_tr_ovrd_tr_ovrd    VTSS_IOREG(0x09, 0, 0x820d)

/** 
 * \brief
 * Enable manual training
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_ovrd_tr_ovrd . ovrd_en
 */
#define  VTSS_F_HOST_KR_DEV1_tr_ovrd_tr_ovrd_ovrd_en  VTSS_BIT(4)

/** 
 * \brief
 * Control of rx_trained variable for training SM
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_ovrd_tr_ovrd . rxtrained_ovrd
 */
#define  VTSS_F_HOST_KR_DEV1_tr_ovrd_tr_ovrd_rxtrained_ovrd  VTSS_BIT(3)

/** 
 * \brief
 * Generate BER enable pulse (SC)
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_ovrd_tr_ovrd . ber_en_ovrd
 */
#define  VTSS_F_HOST_KR_DEV1_tr_ovrd_tr_ovrd_ber_en_ovrd  VTSS_BIT(2)

/** 
 * \brief
 * Generate Coef_update_valid pulse (SC)
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_ovrd_tr_ovrd . coef_ovrd_vld
 */
#define  VTSS_F_HOST_KR_DEV1_tr_ovrd_tr_ovrd_coef_ovrd_vld  VTSS_BIT(1)

/** 
 * \brief
 * Generate Stat_report_valid pulse (SC)
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_ovrd_tr_ovrd . stat_ovrd_vld
 */
#define  VTSS_F_HOST_KR_DEV1_tr_ovrd_tr_ovrd_stat_ovrd_vld  VTSS_BIT(0)

/**
 * Register Group: \a HOST_KR_DEV1:tr_step
 *
 * Not documented
 */


/** 
 * \brief VS training state step
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_step:tr_step
 */
#define VTSS_HOST_KR_DEV1_tr_step_tr_step    VTSS_IOREG(0x09, 0, 0x820e)

/** 
 * \brief
 * Step to next lptrain state (if at breakpoint) (SC)
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_step_tr_step . step
 */
#define  VTSS_F_HOST_KR_DEV1_tr_step_tr_step_step  VTSS_BIT(0)

/**
 * Register Group: \a HOST_KR_DEV1:tr_mthd
 *
 * Not documented
 */


/** 
 * \brief VS training method
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_mthd:tr_mthd
 */
#define VTSS_HOST_KR_DEV1_tr_mthd_tr_mthd    VTSS_IOREG(0x09, 0, 0x820f)

/** 
 * \brief
 * Training method for remote C(+1) 
 *
 * \details 
 * 0 : BER method
 * 1 : Gain method
 * 2 : DFE method
 *
 * Field: VTSS_HOST_KR_DEV1_tr_mthd_tr_mthd . mthd_cp
 */
#define  VTSS_F_HOST_KR_DEV1_tr_mthd_tr_mthd_mthd_cp(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_HOST_KR_DEV1_tr_mthd_tr_mthd_mthd_cp     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_HOST_KR_DEV1_tr_mthd_tr_mthd_mthd_cp(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Training method for remote C(0)
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_mthd_tr_mthd . mthd_c0
 */
#define  VTSS_F_HOST_KR_DEV1_tr_mthd_tr_mthd_mthd_c0(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HOST_KR_DEV1_tr_mthd_tr_mthd_mthd_c0     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HOST_KR_DEV1_tr_mthd_tr_mthd_mthd_c0(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Training method for remote C(-1)
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_mthd_tr_mthd . mthd_cm
 */
#define  VTSS_F_HOST_KR_DEV1_tr_mthd_tr_mthd_mthd_cm(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_HOST_KR_DEV1_tr_mthd_tr_mthd_mthd_cm     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_HOST_KR_DEV1_tr_mthd_tr_mthd_mthd_cm(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * remote tap to optimize first 
 *
 * \details 
 * 0 : C(-1)
 * 1 : C(0)
 * 2 : C(+1)
 *
 * Field: VTSS_HOST_KR_DEV1_tr_mthd_tr_mthd . ord1
 */
#define  VTSS_F_HOST_KR_DEV1_tr_mthd_tr_mthd_ord1(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HOST_KR_DEV1_tr_mthd_tr_mthd_ord1     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HOST_KR_DEV1_tr_mthd_tr_mthd_ord1(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * remote tap to optimize second
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_mthd_tr_mthd . ord2
 */
#define  VTSS_F_HOST_KR_DEV1_tr_mthd_tr_mthd_ord2(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_HOST_KR_DEV1_tr_mthd_tr_mthd_ord2     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_HOST_KR_DEV1_tr_mthd_tr_mthd_ord2(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * remote tap to optimize third
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_mthd_tr_mthd . ord3
 */
#define  VTSS_F_HOST_KR_DEV1_tr_mthd_tr_mthd_ord3(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_KR_DEV1_tr_mthd_tr_mthd_ord3     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_KR_DEV1_tr_mthd_tr_mthd_ord3(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a HOST_KR_DEV1:tr_ber_thr
 *
 * Not documented
 */


/** 
 * \brief VS training BER threshold settings
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_ber_thr:tr_ber_thr
 */
#define VTSS_HOST_KR_DEV1_tr_ber_thr_tr_ber_thr  VTSS_IOREG(0x09, 0, 0x8210)

/** 
 * \brief
 * Only consider error count > ber_err_th
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_ber_thr_tr_ber_thr . ber_err_th
 */
#define  VTSS_F_HOST_KR_DEV1_tr_ber_thr_tr_ber_thr_ber_err_th(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HOST_KR_DEV1_tr_ber_thr_tr_ber_thr_ber_err_th     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HOST_KR_DEV1_tr_ber_thr_tr_ber_thr_ber_err_th(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Only consider errored range > ber_wid_th
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_ber_thr_tr_ber_thr . ber_wid_th
 */
#define  VTSS_F_HOST_KR_DEV1_tr_ber_thr_tr_ber_thr_ber_wid_th(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_KR_DEV1_tr_ber_thr_tr_ber_thr_ber_wid_th     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_KR_DEV1_tr_ber_thr_tr_ber_thr_ber_wid_th(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a HOST_KR_DEV1:tr_ber_ofs
 *
 * Not documented
 */


/** 
 * \brief VS training BER offset setting
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_ber_ofs:tr_ber_ofs
 */
#define VTSS_HOST_KR_DEV1_tr_ber_ofs_tr_ber_ofs  VTSS_IOREG(0x09, 0, 0x8211)

/** 
 * \brief
 * Signed value to adjust final cp tap position from calculated optimal
 * setting.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_ber_ofs_tr_ber_ofs . cp_ber_ofs
 */
#define  VTSS_F_HOST_KR_DEV1_tr_ber_ofs_tr_ber_ofs_cp_ber_ofs(x)  VTSS_ENCODE_BITFIELD(x,10,5)
#define  VTSS_M_HOST_KR_DEV1_tr_ber_ofs_tr_ber_ofs_cp_ber_ofs     VTSS_ENCODE_BITMASK(10,5)
#define  VTSS_X_HOST_KR_DEV1_tr_ber_ofs_tr_ber_ofs_cp_ber_ofs(x)  VTSS_EXTRACT_BITFIELD(x,10,5)

/** 
 * \brief
 * Signed value to adjust final c0 tap position from calculated optimal
 * setting.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_ber_ofs_tr_ber_ofs . c0_ber_ofs
 */
#define  VTSS_F_HOST_KR_DEV1_tr_ber_ofs_tr_ber_ofs_c0_ber_ofs(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_HOST_KR_DEV1_tr_ber_ofs_tr_ber_ofs_c0_ber_ofs     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_HOST_KR_DEV1_tr_ber_ofs_tr_ber_ofs_c0_ber_ofs(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Signed value to adjust final cm tap position from calculated optimal
 * setting.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_ber_ofs_tr_ber_ofs . cm_ber_ofs
 */
#define  VTSS_F_HOST_KR_DEV1_tr_ber_ofs_tr_ber_ofs_cm_ber_ofs(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_HOST_KR_DEV1_tr_ber_ofs_tr_ber_ofs_cm_ber_ofs     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_HOST_KR_DEV1_tr_ber_ofs_tr_ber_ofs_cm_ber_ofs(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a HOST_KR_DEV1:tr_lutsel
 *
 * Not documented
 */


/** 
 * \brief VS training LUT selection
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_lutsel:tr_lutsel
 */
#define VTSS_HOST_KR_DEV1_tr_lutsel_tr_lutsel  VTSS_IOREG(0x09, 0, 0x8212)

/** 
 * \brief
 * Selects LUT table entry (0 to 63).
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_lutsel_tr_lutsel . lut_row
 */
#define  VTSS_F_HOST_KR_DEV1_tr_lutsel_tr_lutsel_lut_row(x)  VTSS_ENCODE_BITFIELD(x,3,6)
#define  VTSS_M_HOST_KR_DEV1_tr_lutsel_tr_lutsel_lut_row     VTSS_ENCODE_BITMASK(3,6)
#define  VTSS_X_HOST_KR_DEV1_tr_lutsel_tr_lutsel_lut_row(x)  VTSS_EXTRACT_BITFIELD(x,3,6)

/** 
 * \brief
 * Selects LUT for lut_o 
 *
 * \details 
 * 0: Gain 
 * 1: DFE_1
 * 2: DFE_2
 * 3: DFE_avg_1 
 * 4: DFE_avg_2 
 * 5: BER_1
 * 6: BER_2
 * 7: BER_3
 *
 * Field: VTSS_HOST_KR_DEV1_tr_lutsel_tr_lutsel . lut_sel
 */
#define  VTSS_F_HOST_KR_DEV1_tr_lutsel_tr_lutsel_lut_sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HOST_KR_DEV1_tr_lutsel_tr_lutsel_lut_sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HOST_KR_DEV1_tr_lutsel_tr_lutsel_lut_sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a HOST_KR_DEV1:tr_brkmask
 *
 * Not documented
 */


/** 
 * \brief VS training break_mask lsw
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_brkmask:brkmask_lsw
 */
#define VTSS_HOST_KR_DEV1_tr_brkmask_brkmask_lsw  VTSS_IOREG(0x09, 0, 0x8213)

/** 
 * \brief
 * Select lptrain state machine breakpoints. Each bit correpsonds to a
 * state (see design doc)
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_brkmask_brkmask_lsw . brkmask_lsw
 */
#define  VTSS_F_HOST_KR_DEV1_tr_brkmask_brkmask_lsw_brkmask_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_tr_brkmask_brkmask_lsw_brkmask_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_tr_brkmask_brkmask_lsw_brkmask_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS training break_mask msw
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_brkmask:brkmask_msw
 */
#define VTSS_HOST_KR_DEV1_tr_brkmask_brkmask_msw  VTSS_IOREG(0x09, 0, 0x8214)

/** 
 * \brief
 * Select lptrain state machine breakpoints. Each bit correpsonds to a
 * state (see design doc)
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_brkmask_brkmask_msw . brkmask_msw
 */
#define  VTSS_F_HOST_KR_DEV1_tr_brkmask_brkmask_msw_brkmask_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_tr_brkmask_brkmask_msw_brkmask_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_tr_brkmask_brkmask_msw_brkmask_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_KR_DEV1:obcfg_addr
 *
 * Not documented
 */


/** 
 * \brief VS training ROM address for end and obcfg
 *
 * \details
 * Register: \a HOST_KR_DEV1:obcfg_addr:obcfg_addr
 */
#define VTSS_HOST_KR_DEV1_obcfg_addr_obcfg_addr  VTSS_IOREG(0x09, 0, 0x8230)

/** 
 * \brief
 * Address of OB tap configuration settings
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_obcfg_addr_obcfg_addr . obcfg_addr
 */
#define  VTSS_F_HOST_KR_DEV1_obcfg_addr_obcfg_addr_obcfg_addr(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_HOST_KR_DEV1_obcfg_addr_obcfg_addr_obcfg_addr     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_HOST_KR_DEV1_obcfg_addr_obcfg_addr_obcfg_addr(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a HOST_KR_DEV1:apc_tmr
 *
 * Not documented
 */


/** 
 * \brief VS training apc_timer
 *
 * \details
 * Register: \a HOST_KR_DEV1:apc_tmr:apc_tmr
 */
#define VTSS_HOST_KR_DEV1_apc_tmr_apc_tmr    VTSS_IOREG(0x09, 0, 0x8240)

/** 
 * \brief
 * Delay between LP tap update, and capture of direct-connect apc values
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_apc_tmr_apc_tmr . apc_tmr
 */
#define  VTSS_F_HOST_KR_DEV1_apc_tmr_apc_tmr_apc_tmr(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_apc_tmr_apc_tmr_apc_tmr     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_apc_tmr_apc_tmr_apc_tmr(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_KR_DEV1:wt_tmr
 *
 * Not documented
 */


/** 
 * \brief VS training wait_timer
 *
 * \details
 * Register: \a HOST_KR_DEV1:wt_tmr:wt_tmr
 */
#define VTSS_HOST_KR_DEV1_wt_tmr_wt_tmr      VTSS_IOREG(0x09, 0, 0x8241)

/** 
 * \brief
 * wait_timer for training state machine to allow extra training frames to
 * be exchanged
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_wt_tmr_wt_tmr . wt_tmr
 */
#define  VTSS_F_HOST_KR_DEV1_wt_tmr_wt_tmr_wt_tmr(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_wt_tmr_wt_tmr_wt_tmr     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_wt_tmr_wt_tmr_wt_tmr(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_KR_DEV1:mw_tmr
 *
 * Not documented
 */


/** 
 * \brief VS training maxwait_timer lsw
 *
 * \details
 * Register: \a HOST_KR_DEV1:mw_tmr:mw_tmr_lsw
 */
#define VTSS_HOST_KR_DEV1_mw_tmr_mw_tmr_lsw  VTSS_IOREG(0x09, 0, 0x8242)

/** 
 * \brief
 * maxwait_timer, when training expires and failure declared. 500ms
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_mw_tmr_mw_tmr_lsw . mw_tmr_lsw
 */
#define  VTSS_F_HOST_KR_DEV1_mw_tmr_mw_tmr_lsw_mw_tmr_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_mw_tmr_mw_tmr_lsw_mw_tmr_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_mw_tmr_mw_tmr_lsw_mw_tmr_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS training maxwait_timer msw
 *
 * \details
 * Register: \a HOST_KR_DEV1:mw_tmr:mw_tmr_msw
 */
#define VTSS_HOST_KR_DEV1_mw_tmr_mw_tmr_msw  VTSS_IOREG(0x09, 0, 0x8243)

/** 
 * \brief
 * maxwait_timer, when training expires and failure declared. 500ms
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_mw_tmr_mw_tmr_msw . mw_tmr_msw
 */
#define  VTSS_F_HOST_KR_DEV1_mw_tmr_mw_tmr_msw_mw_tmr_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_mw_tmr_mw_tmr_msw_mw_tmr_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_mw_tmr_mw_tmr_msw_mw_tmr_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_KR_DEV1:tr_sts1
 *
 * Not documented
 */


/** 
 * \brief VS training status 1
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_sts1:tr_sts1
 */
#define VTSS_HOST_KR_DEV1_tr_sts1_tr_sts1    VTSS_IOREG(0x09, 0, 0x8250)

/** 
 * \brief
 * Indicates prbs11 checker is active
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_sts1_tr_sts1 . ber_busy
 */
#define  VTSS_F_HOST_KR_DEV1_tr_sts1_tr_sts1_ber_busy  VTSS_BIT(12)

/** 
 * \brief
 * Training state machine
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_sts1_tr_sts1 . tr_sm
 */
#define  VTSS_F_HOST_KR_DEV1_tr_sts1_tr_sts1_tr_sm(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_HOST_KR_DEV1_tr_sts1_tr_sts1_tr_sm     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_HOST_KR_DEV1_tr_sts1_tr_sts1_tr_sm(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * LP training state machine
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_sts1_tr_sts1 . lptrain_sm
 */
#define  VTSS_F_HOST_KR_DEV1_tr_sts1_tr_sts1_lptrain_sm(x)  VTSS_ENCODE_BITFIELD(x,4,5)
#define  VTSS_M_HOST_KR_DEV1_tr_sts1_tr_sts1_lptrain_sm     VTSS_ENCODE_BITMASK(4,5)
#define  VTSS_X_HOST_KR_DEV1_tr_sts1_tr_sts1_lptrain_sm(x)  VTSS_EXTRACT_BITFIELD(x,4,5)

/** 
 * \brief
 * Indicates gain_target was not reached during LP training
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_sts1_tr_sts1 . gain_fail
 */
#define  VTSS_F_HOST_KR_DEV1_tr_sts1_tr_sts1_gain_fail  VTSS_BIT(3)

/** 
 * \brief
 * training variable from training state machine
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_sts1_tr_sts1 . training
 */
#define  VTSS_F_HOST_KR_DEV1_tr_sts1_tr_sts1_training  VTSS_BIT(2)

/** 
 * \brief
 * Indicates a DME violation has occured (LH)
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_sts1_tr_sts1 . dme_viol
 */
#define  VTSS_F_HOST_KR_DEV1_tr_sts1_tr_sts1_dme_viol  VTSS_BIT(1)

/** 
 * \brief
 * Indicates that local and remote training has completed
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_sts1_tr_sts1 . tr_done
 */
#define  VTSS_F_HOST_KR_DEV1_tr_sts1_tr_sts1_tr_done  VTSS_BIT(0)

/**
 * Register Group: \a HOST_KR_DEV1:tr_sts2
 *
 * Not documented
 */


/** 
 * \brief VS training status 2
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_sts2:tr_sts2
 */
#define VTSS_HOST_KR_DEV1_tr_sts2_tr_sts2    VTSS_IOREG(0x09, 0, 0x8251)

/** 
 * \brief
 * CP range error (LH)
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_sts2_tr_sts2 . cp_range_err
 */
#define  VTSS_F_HOST_KR_DEV1_tr_sts2_tr_sts2_cp_range_err  VTSS_BIT(2)

/** 
 * \brief
 * C0 range error (LH)
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_sts2_tr_sts2 . c0_range_err
 */
#define  VTSS_F_HOST_KR_DEV1_tr_sts2_tr_sts2_c0_range_err  VTSS_BIT(1)

/** 
 * \brief
 * CM range error (LH)
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_sts2_tr_sts2 . cm_range_err
 */
#define  VTSS_F_HOST_KR_DEV1_tr_sts2_tr_sts2_cm_range_err  VTSS_BIT(0)

/**
 * Register Group: \a HOST_KR_DEV1:tr_tapval
 *
 * Not documented
 */


/** 
 * \brief VS tap CM value
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_tapval:tr_cmval
 */
#define VTSS_HOST_KR_DEV1_tr_tapval_tr_cmval  VTSS_IOREG(0x09, 0, 0x8254)

/** 
 * \brief
 * CM value
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_tapval_tr_cmval . cm_val
 */
#define  VTSS_F_HOST_KR_DEV1_tr_tapval_tr_cmval_cm_val(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_HOST_KR_DEV1_tr_tapval_tr_cmval_cm_val     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_HOST_KR_DEV1_tr_tapval_tr_cmval_cm_val(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS tap C0 value
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_tapval:tr_c0val
 */
#define VTSS_HOST_KR_DEV1_tr_tapval_tr_c0val  VTSS_IOREG(0x09, 0, 0x8255)

/** 
 * \brief
 * C0 value
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_tapval_tr_c0val . c0_val
 */
#define  VTSS_F_HOST_KR_DEV1_tr_tapval_tr_c0val_c0_val(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_HOST_KR_DEV1_tr_tapval_tr_c0val_c0_val     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_HOST_KR_DEV1_tr_tapval_tr_c0val_c0_val(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS tap CP value
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_tapval:tr_cpval
 */
#define VTSS_HOST_KR_DEV1_tr_tapval_tr_cpval  VTSS_IOREG(0x09, 0, 0x8256)

/** 
 * \brief
 * CP value
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_tapval_tr_cpval . cp_val
 */
#define  VTSS_F_HOST_KR_DEV1_tr_tapval_tr_cpval_cp_val(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_HOST_KR_DEV1_tr_tapval_tr_cpval_cp_val     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_HOST_KR_DEV1_tr_tapval_tr_cpval_cp_val(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a HOST_KR_DEV1:tr_frames_sent
 *
 * Not documented
 */


/** 
 * \brief VS training frames_sent lsw
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_frames_sent:frsent_lsw
 */
#define VTSS_HOST_KR_DEV1_tr_frames_sent_frsent_lsw  VTSS_IOREG(0x09, 0, 0x8260)

/** 
 * \brief
 * Number of training frames sent to complete training.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_frames_sent_frsent_lsw . frsent_lsw
 */
#define  VTSS_F_HOST_KR_DEV1_tr_frames_sent_frsent_lsw_frsent_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_tr_frames_sent_frsent_lsw_frsent_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_tr_frames_sent_frsent_lsw_frsent_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS training frames_sent lsw
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_frames_sent:frsent_msw
 */
#define VTSS_HOST_KR_DEV1_tr_frames_sent_frsent_msw  VTSS_IOREG(0x09, 0, 0x8261)

/** 
 * \brief
 * Number of training frames sent to complete training.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_frames_sent_frsent_msw . frsent_msw
 */
#define  VTSS_F_HOST_KR_DEV1_tr_frames_sent_frsent_msw_frsent_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_tr_frames_sent_frsent_msw_frsent_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_tr_frames_sent_frsent_msw_frsent_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_KR_DEV1:tr_lut
 *
 * Not documented
 */


/** 
 * \brief VS training lut_read lsw
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_lut:lut_lsw
 */
#define VTSS_HOST_KR_DEV1_tr_lut_lut_lsw     VTSS_IOREG(0x09, 0, 0x8270)

/** 
 * \brief
 * Measured value of selected LUT.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_lut_lut_lsw . lut_lsw
 */
#define  VTSS_F_HOST_KR_DEV1_tr_lut_lut_lsw_lut_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_tr_lut_lut_lsw_lut_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_tr_lut_lut_lsw_lut_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS training lut_read msw
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_lut:lut_msw
 */
#define VTSS_HOST_KR_DEV1_tr_lut_lut_msw     VTSS_IOREG(0x09, 0, 0x8271)

/** 
 * \brief
 * Measured value of selected LUT.
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_lut_lut_msw . lut_msw
 */
#define  VTSS_F_HOST_KR_DEV1_tr_lut_lut_msw_lut_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_tr_lut_lut_msw_lut_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_tr_lut_lut_msw_lut_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_KR_DEV1:tr_errcnt
 *
 * Not documented
 */


/** 
 * \brief VS training prbs11 error_count
 *
 * \details
 * Register: \a HOST_KR_DEV1:tr_errcnt:tr_errcnt
 */
#define VTSS_HOST_KR_DEV1_tr_errcnt_tr_errcnt  VTSS_IOREG(0x09, 0, 0x8272)

/** 
 * \brief
 * bit error count of prbs11 checker
 *
 * \details 
 * Field: VTSS_HOST_KR_DEV1_tr_errcnt_tr_errcnt . errcnt
 */
#define  VTSS_F_HOST_KR_DEV1_tr_errcnt_tr_errcnt_errcnt(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_KR_DEV1_tr_errcnt_tr_errcnt_errcnt     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_KR_DEV1_tr_errcnt_tr_errcnt_errcnt(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_MALIBU_REGS_HOST_KR_DEV1_H_ */
