// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_VENICE_REGS_VENICE_KR_DEV1_H_
#define _VTSS_VENICE_REGS_VENICE_KR_DEV1_H_


#include "vtss_venice_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a VENICE_KR_DEV1
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a VENICE_KR_DEV1:KR_1X0096
 *
 * Not documented
 */


/** 
 * \brief KR PMD control
 *
 * \details
 * Register: \a VENICE_KR_DEV1:KR_1X0096:KR_1X0096
 */
#define VTSS_VENICE_KR_DEV1_KR_1X0096_KR_1X0096  VTSS_IOREG(0x01, 0, 0x0096)

/** 
 * \brief
 * Training enable  
 *
 * \details 
 * 1: Enable KR start-up protocol 
 * 0: Disable KR start-up protocol
 *
 * Field: VTSS_VENICE_KR_DEV1_KR_1X0096_KR_1X0096 . TR_ENABLE
 */
#define  VTSS_F_VENICE_KR_DEV1_KR_1X0096_KR_1X0096_TR_ENABLE  VTSS_BIT(1)

/** 
 * \brief
 * Restart training (SC) 
 *
 * \details 
 * 1: Reset KR start-up protocol 
 * 0: Normal operation
 *
 * Field: VTSS_VENICE_KR_DEV1_KR_1X0096_KR_1X0096 . TR_RESTART
 */
#define  VTSS_F_VENICE_KR_DEV1_KR_1X0096_KR_1X0096_TR_RESTART  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_KR_DEV1:KR_1X0097
 *
 * Not documented
 */


/** 
 * \brief KR PMD status
 *
 * \details
 * Register: \a VENICE_KR_DEV1:KR_1X0097:KR_1X0097
 */
#define VTSS_VENICE_KR_DEV1_KR_1X0097_KR_1X0097  VTSS_IOREG(0x01, 0, 0x0097)

/** 
 * \brief
 * Training failure 
 *
 * \details 
 * 1: Training failure has been detected 
 * 0: Training failure has not been detected
 *
 * Field: VTSS_VENICE_KR_DEV1_KR_1X0097_KR_1X0097 . TR_FAIL
 */
#define  VTSS_F_VENICE_KR_DEV1_KR_1X0097_KR_1X0097_TR_FAIL  VTSS_BIT(3)

/** 
 * \brief
 * Startup protocol status 
 *
 * \details 
 * 1: Start-up protocol in progress 
 * 0: Start-up protocol complete
 *
 * Field: VTSS_VENICE_KR_DEV1_KR_1X0097_KR_1X0097 . STPROT
 */
#define  VTSS_F_VENICE_KR_DEV1_KR_1X0097_KR_1X0097_STPROT  VTSS_BIT(2)

/** 
 * \brief
 * Frame lock 
 *
 * \details 
 * 1: Training frame delineation detected, 
 * 0: Training frame delineation not detected
 *
 * Field: VTSS_VENICE_KR_DEV1_KR_1X0097_KR_1X0097 . FRLOCK
 */
#define  VTSS_F_VENICE_KR_DEV1_KR_1X0097_KR_1X0097_FRLOCK  VTSS_BIT(1)

/** 
 * \brief
 * Receiver status 
 *
 * \details 
 * 1: Receiver trained and ready to receive data 
 * 0: Receiver training
 *
 * Field: VTSS_VENICE_KR_DEV1_KR_1X0097_KR_1X0097 . RCVR_RDY
 */
#define  VTSS_F_VENICE_KR_DEV1_KR_1X0097_KR_1X0097_RCVR_RDY  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_KR_DEV1:KR_1X0098
 *
 * Not documented
 */


/** 
 * \brief KR LP coefficient update
 *
 * \details
 * Register: \a VENICE_KR_DEV1:KR_1X0098:KR_1X0098
 */
#define VTSS_VENICE_KR_DEV1_KR_1X0098_KR_1X0098  VTSS_IOREG(0x01, 0, 0x0098)

/** 
 * \brief
 * Received coefficient update field
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_KR_1X0098_KR_1X0098 . LPCOEF
 */
#define  VTSS_F_VENICE_KR_DEV1_KR_1X0098_KR_1X0098_LPCOEF(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_KR_1X0098_KR_1X0098_LPCOEF     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_KR_1X0098_KR_1X0098_LPCOEF(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:KR_1X0099
 *
 * Not documented
 */


/** 
 * \brief KR LP status report
 *
 * \details
 * Register: \a VENICE_KR_DEV1:KR_1X0099:KR_1X0099
 */
#define VTSS_VENICE_KR_DEV1_KR_1X0099_KR_1X0099  VTSS_IOREG(0x01, 0, 0x0099)

/** 
 * \brief
 * Received status report field
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_KR_1X0099_KR_1X0099 . LPSTAT
 */
#define  VTSS_F_VENICE_KR_DEV1_KR_1X0099_KR_1X0099_LPSTAT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_KR_1X0099_KR_1X0099_LPSTAT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_KR_1X0099_KR_1X0099_LPSTAT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:KR_1X009A
 *
 * Not documented
 */


/** 
 * \brief KR LD coefficient update
 *
 * \details
 * Register: \a VENICE_KR_DEV1:KR_1X009A:KR_1X009A
 */
#define VTSS_VENICE_KR_DEV1_KR_1X009A_KR_1X009A  VTSS_IOREG(0x01, 0, 0x009a)

/** 
 * \brief
 * Transmitted coefficient update field
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_KR_1X009A_KR_1X009A . LDCOEF
 */
#define  VTSS_F_VENICE_KR_DEV1_KR_1X009A_KR_1X009A_LDCOEF(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_KR_1X009A_KR_1X009A_LDCOEF     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_KR_1X009A_KR_1X009A_LDCOEF(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:KR_1X009B
 *
 * Not documented
 */


/** 
 * \brief KR LD status report
 *
 * \details
 * Register: \a VENICE_KR_DEV1:KR_1X009B:KR_1X009B
 */
#define VTSS_VENICE_KR_DEV1_KR_1X009B_KR_1X009B  VTSS_IOREG(0x01, 0, 0x009b)

/** 
 * \brief
 * Transmitted status report field
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_KR_1X009B_KR_1X009B . LDSTAT
 */
#define  VTSS_F_VENICE_KR_DEV1_KR_1X009B_KR_1X009B_LDSTAT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_KR_1X009B_KR_1X009B_LDSTAT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_KR_1X009B_KR_1X009B_LDSTAT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_CFG0
 *
 * Not documented
 */


/** 
 * \brief VS training config 0
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_CFG0:TR_CFG0
 */
#define VTSS_VENICE_KR_DEV1_TR_CFG0_TR_CFG0  VTSS_IOREG(0x01, 0, 0x8200)

/** 
 * \brief
 * Clock divider value for timer clocks.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG0_TR_CFG0 . TMR_DVDR
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG0_TR_CFG0_TMR_DVDR(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG0_TR_CFG0_TMR_DVDR     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG0_TR_CFG0_TMR_DVDR(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Invert recieved prbs11 within training frame
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG0_TR_CFG0 . RX_INV
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG0_TR_CFG0_RX_INV  VTSS_BIT(10)

/** 
 * \brief
 * Invert transmitted prbs11 within training frame
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG0_TR_CFG0 . TX_INV
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG0_TR_CFG0_TX_INV  VTSS_BIT(9)

/** 
 * \brief
 * Clear all state machine history
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG0_TR_CFG0 . SM_HIST_CLR
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG0_TR_CFG0_SM_HIST_CLR  VTSS_BIT(5)

/** 
 * \brief
 * Set local taps starting point 
 *
 * \details 
 * 0: Set to INITIALIZE 
 * 1: Set to PRESET
 *
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG0_TR_CFG0 . LD_PRE_INIT
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG0_TR_CFG0_LD_PRE_INIT  VTSS_BIT(4)

/** 
 * \brief
 * Send first LP request 
 *
 * \details 
 * 0: Send   INITIALIZE 
 * 1: Send   PRESET
 *
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG0_TR_CFG0 . LP_PRE_INIT
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG0_TR_CFG0_LP_PRE_INIT  VTSS_BIT(3)

/** 
 * \brief
 * Update taps regardless of v2,vp sum.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG0_TR_CFG0 . NOSUM
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG0_TR_CFG0_NOSUM  VTSS_BIT(2)

/** 
 * \brief
 * Enable partial OB tap configuration.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG0_TR_CFG0 . PART_CFG_EN
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG0_TR_CFG0_PART_CFG_EN  VTSS_BIT(1)

/** 
 * \brief
 * Allow LP to to control tap settings.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG0_TR_CFG0 . TAPCTL_EN
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG0_TR_CFG0_TAPCTL_EN  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_CFG1
 *
 * Not documented
 */


/** 
 * \brief VS training config 1
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_CFG1:TR_CFG1
 */
#define VTSS_VENICE_KR_DEV1_TR_CFG1_TR_CFG1  VTSS_IOREG(0x01, 0, 0x8201)

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
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG1_TR_CFG1 . TMR_HOLD
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG1_TR_CFG1_TMR_HOLD(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG1_TR_CFG1_TMR_HOLD     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG1_TR_CFG1_TMR_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_CFG2
 *
 * Not documented
 */


/** 
 * \brief VS training config 2
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_CFG2:TR_CFG2
 */
#define VTSS_VENICE_KR_DEV1_TR_CFG2_TR_CFG2  VTSS_IOREG(0x01, 0, 0x8202)

/** 
 * \brief
 * max	settings for vp sum.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG2_TR_CFG2 . VP_MAX
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG2_TR_CFG2_VP_MAX(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG2_TR_CFG2_VP_MAX     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG2_TR_CFG2_VP_MAX(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * min	settings for v2 sum.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG2_TR_CFG2 . V2_MIN
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG2_TR_CFG2_V2_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG2_TR_CFG2_V2_MIN     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG2_TR_CFG2_V2_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_CFG3
 *
 * Not documented
 */


/** 
 * \brief VS training config 3
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_CFG3:TR_CFG3
 */
#define VTSS_VENICE_KR_DEV1_TR_CFG3_TR_CFG3  VTSS_IOREG(0x01, 0, 0x8203)

/** 
 * \brief
 * max	settings for local transmitter.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG3_TR_CFG3 . CP_MAX
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG3_TR_CFG3_CP_MAX(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG3_TR_CFG3_CP_MAX     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG3_TR_CFG3_CP_MAX(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * min	settings for local transmitter.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG3_TR_CFG3 . CP_MIN
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG3_TR_CFG3_CP_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG3_TR_CFG3_CP_MIN     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG3_TR_CFG3_CP_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_CFG4
 *
 * Not documented
 */


/** 
 * \brief VS training config 4
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_CFG4:TR_CFG4
 */
#define VTSS_VENICE_KR_DEV1_TR_CFG4_TR_CFG4  VTSS_IOREG(0x01, 0, 0x8204)

/** 
 * \brief
 * max	settings for local transmitter.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG4_TR_CFG4 . C0_MAX
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG4_TR_CFG4_C0_MAX(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG4_TR_CFG4_C0_MAX     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG4_TR_CFG4_C0_MAX(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * min	settings for local transmitter.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG4_TR_CFG4 . C0_MIN
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG4_TR_CFG4_C0_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG4_TR_CFG4_C0_MIN     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG4_TR_CFG4_C0_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_CFG5
 *
 * Not documented
 */


/** 
 * \brief VS training config 5
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_CFG5:TR_CFG5
 */
#define VTSS_VENICE_KR_DEV1_TR_CFG5_TR_CFG5  VTSS_IOREG(0x01, 0, 0x8205)

/** 
 * \brief
 * max	settings for local transmitter.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG5_TR_CFG5 . CM_MAX
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG5_TR_CFG5_CM_MAX(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG5_TR_CFG5_CM_MAX     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG5_TR_CFG5_CM_MAX(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * min	settings for local transmitter.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG5_TR_CFG5 . CM_MIN
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG5_TR_CFG5_CM_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG5_TR_CFG5_CM_MIN     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG5_TR_CFG5_CM_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_CFG6
 *
 * Not documented
 */


/** 
 * \brief VS training config 6
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_CFG6:TR_CFG6
 */
#define VTSS_VENICE_KR_DEV1_TR_CFG6_TR_CFG6  VTSS_IOREG(0x01, 0, 0x8206)

/** 
 * \brief
 * initialize settings for local transmitter.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG6_TR_CFG6 . CP_INIT
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG6_TR_CFG6_CP_INIT(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG6_TR_CFG6_CP_INIT     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG6_TR_CFG6_CP_INIT(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * initialize settings for local transmitter.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG6_TR_CFG6 . C0_INIT
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG6_TR_CFG6_C0_INIT(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG6_TR_CFG6_C0_INIT     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG6_TR_CFG6_C0_INIT(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_CFG7
 *
 * Not documented
 */


/** 
 * \brief VS training config 7
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_CFG7:TR_CFG7
 */
#define VTSS_VENICE_KR_DEV1_TR_CFG7_TR_CFG7  VTSS_IOREG(0x01, 0, 0x8207)

/** 
 * \brief
 * initialize settings for local transmitter.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG7_TR_CFG7 . CM_INIT
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG7_TR_CFG7_CM_INIT(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG7_TR_CFG7_CM_INIT     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG7_TR_CFG7_CM_INIT(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Signed value to adjust final LP C(+1) tap position from calculated
 * optimal setting.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG7_TR_CFG7 . DFE_OFS
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG7_TR_CFG7_DFE_OFS(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG7_TR_CFG7_DFE_OFS     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG7_TR_CFG7_DFE_OFS(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_CFG8
 *
 * Not documented
 */


/** 
 * \brief VS training config 8
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_CFG8:TR_CFG8
 */
#define VTSS_VENICE_KR_DEV1_TR_CFG8_TR_CFG8  VTSS_IOREG(0x01, 0, 0x8208)

/** 
 * \brief
 * Weighted average calculation of DFE tap 1
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG8_TR_CFG8 . WT1
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG8_TR_CFG8_WT1(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG8_TR_CFG8_WT1     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG8_TR_CFG8_WT1(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Weighted average calculation of DFE tap 2
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG8_TR_CFG8 . WT2
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG8_TR_CFG8_WT2(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG8_TR_CFG8_WT2     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG8_TR_CFG8_WT2(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Weighted average calculation of DFE tap 3
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG8_TR_CFG8 . WT3
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG8_TR_CFG8_WT3(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG8_TR_CFG8_WT3     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG8_TR_CFG8_WT3(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Weighted average calculation of DFE tap 4
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG8_TR_CFG8 . WT4
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG8_TR_CFG8_WT4(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG8_TR_CFG8_WT4     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG8_TR_CFG8_WT4(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_CFG9
 *
 * Not documented
 */


/** 
 * \brief VS training config 9
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_CFG9:TR_CFG9
 */
#define VTSS_VENICE_KR_DEV1_TR_CFG9_TR_CFG9  VTSS_IOREG(0x01, 0, 0x8209)

/** 
 * \brief
 * Number of training frames used for BER calculation.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_CFG9_TR_CFG9 . FRCNT_BER
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_CFG9_TR_CFG9_FRCNT_BER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_TR_CFG9_TR_CFG9_FRCNT_BER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_TR_CFG9_TR_CFG9_FRCNT_BER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_GAIN
 *
 * Not documented
 */


/** 
 * \brief VS training gain target and margin values
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_GAIN:TR_GAIN
 */
#define VTSS_VENICE_KR_DEV1_TR_GAIN_TR_GAIN  VTSS_IOREG(0x01, 0, 0x820a)

/** 
 * \brief
 * LP C(0) optimized when GAIN is gain_targ +/- 2*gain_marg
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_GAIN_TR_GAIN . GAIN_MARG
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_GAIN_TR_GAIN_GAIN_MARG(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_GAIN_TR_GAIN_GAIN_MARG     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_GAIN_TR_GAIN_GAIN_MARG(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Target value of GAIN setting during LP C(0) optimization.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_GAIN_TR_GAIN . GAIN_TARG
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_GAIN_TR_GAIN_GAIN_TARG(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VENICE_KR_DEV1_TR_GAIN_TR_GAIN_GAIN_TARG     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VENICE_KR_DEV1_TR_GAIN_TR_GAIN_GAIN_TARG(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_COEF_OVRD
 *
 * Not documented
 */


/** 
 * \brief VS training coefficient update override
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_COEF_OVRD:TR_COEF_OVRD
 */
#define VTSS_VENICE_KR_DEV1_TR_COEF_OVRD_TR_COEF_OVRD  VTSS_IOREG(0x01, 0, 0x820b)

/** 
 * \brief
 * Override Coef_update field to transmit
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_COEF_OVRD_TR_COEF_OVRD . COEF_OVRD
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_COEF_OVRD_TR_COEF_OVRD_COEF_OVRD(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_TR_COEF_OVRD_TR_COEF_OVRD_COEF_OVRD     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_TR_COEF_OVRD_TR_COEF_OVRD_COEF_OVRD(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_STAT_OVRD
 *
 * Not documented
 */


/** 
 * \brief VS training status report override
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_STAT_OVRD:TR_STAT_OVRD
 */
#define VTSS_VENICE_KR_DEV1_TR_STAT_OVRD_TR_STAT_OVRD  VTSS_IOREG(0x01, 0, 0x820c)

/** 
 * \brief
 * Override Stat_report field to transmit
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_STAT_OVRD_TR_STAT_OVRD . STAT_OVRD
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_STAT_OVRD_TR_STAT_OVRD_STAT_OVRD(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_TR_STAT_OVRD_TR_STAT_OVRD_STAT_OVRD     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_TR_STAT_OVRD_TR_STAT_OVRD_STAT_OVRD(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_OVRD
 *
 * Not documented
 */


/** 
 * \brief VS training override
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_OVRD:TR_OVRD
 */
#define VTSS_VENICE_KR_DEV1_TR_OVRD_TR_OVRD  VTSS_IOREG(0x01, 0, 0x820d)

/** 
 * \brief
 * Enable manual training
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_OVRD_TR_OVRD . OVRD_EN
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_OVRD_TR_OVRD_OVRD_EN  VTSS_BIT(4)

/** 
 * \brief
 * Control of rx_trained variable for training SM
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_OVRD_TR_OVRD . RXTRAINED_OVRD
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_OVRD_TR_OVRD_RXTRAINED_OVRD  VTSS_BIT(3)

/** 
 * \brief
 * Generate BER enable pulse (SC)
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_OVRD_TR_OVRD . BER_EN_OVRD
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_OVRD_TR_OVRD_BER_EN_OVRD  VTSS_BIT(2)

/** 
 * \brief
 * Generate Coef_update_valid pulse (SC)
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_OVRD_TR_OVRD . COEF_OVRD_VLD
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_OVRD_TR_OVRD_COEF_OVRD_VLD  VTSS_BIT(1)

/** 
 * \brief
 * Generate Stat_report_valid pulse (SC)
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_OVRD_TR_OVRD . STAT_OVRD_VLD
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_OVRD_TR_OVRD_STAT_OVRD_VLD  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_STEP
 *
 * Not documented
 */


/** 
 * \brief VS training state step
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_STEP:TR_STEP
 */
#define VTSS_VENICE_KR_DEV1_TR_STEP_TR_STEP  VTSS_IOREG(0x01, 0, 0x820e)

/** 
 * \brief
 * Step to next lptrain state (if at breakpoint) (SC)
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_STEP_TR_STEP . STEP
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_STEP_TR_STEP_STEP  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_MTHD
 *
 * Not documented
 */


/** 
 * \brief VS training method
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_MTHD:TR_MTHD
 */
#define VTSS_VENICE_KR_DEV1_TR_MTHD_TR_MTHD  VTSS_IOREG(0x01, 0, 0x820f)

/** 
 * \brief
 * Training method for remote C(+1) 
 *
 * \details 
 * 0 : BER method
 * 1 : Gain method
 * 2 : DFE method
 *
 * Field: VTSS_VENICE_KR_DEV1_TR_MTHD_TR_MTHD . MTHD_CP
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CP(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CP     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CP(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Training method for remote C(0)
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_MTHD_TR_MTHD . MTHD_C0
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_C0(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_C0     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_C0(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Training method for remote C(-1)
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_MTHD_TR_MTHD . MTHD_CM
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CM(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CM     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CM(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * remote tap to optimize first 
 *
 * \details 
 * 0 : C(-1)
 * 1 : C(0)
 * 2 : C(+1)
 *
 * Field: VTSS_VENICE_KR_DEV1_TR_MTHD_TR_MTHD . ORD1
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_ORD1(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_ORD1     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_ORD1(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * remote tap to optimize second
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_MTHD_TR_MTHD . ORD2
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_ORD2(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_ORD2     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_ORD2(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * remote tap to optimize third
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_MTHD_TR_MTHD . ORD3
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_ORD3(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_ORD3     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VENICE_KR_DEV1_TR_MTHD_TR_MTHD_ORD3(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_BER_THR
 *
 * Not documented
 */


/** 
 * \brief VS training BER threshold settings
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_BER_THR:TR_BER_THR
 */
#define VTSS_VENICE_KR_DEV1_TR_BER_THR_TR_BER_THR  VTSS_IOREG(0x01, 0, 0x8210)

/** 
 * \brief
 * Only consider error count > ber_err_th
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_BER_THR_TR_BER_THR . BER_ERR_TH
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_BER_THR_TR_BER_THR_BER_ERR_TH(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VENICE_KR_DEV1_TR_BER_THR_TR_BER_THR_BER_ERR_TH     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VENICE_KR_DEV1_TR_BER_THR_TR_BER_THR_BER_ERR_TH(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Only consider errored range > ber_wid_th
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_BER_THR_TR_BER_THR . BER_WID_TH
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_BER_THR_TR_BER_THR_BER_WID_TH(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_KR_DEV1_TR_BER_THR_TR_BER_THR_BER_WID_TH     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_KR_DEV1_TR_BER_THR_TR_BER_THR_BER_WID_TH(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_BER_OFS
 *
 * Not documented
 */


/** 
 * \brief VS training BER offset setting
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_BER_OFS:TR_BER_OFS
 */
#define VTSS_VENICE_KR_DEV1_TR_BER_OFS_TR_BER_OFS  VTSS_IOREG(0x01, 0, 0x8211)

/** 
 * \brief
 * Signed value to adjust final cp tap position from calculated optimal
 * setting.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_BER_OFS_TR_BER_OFS . CP_BER_OFS
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_BER_OFS_TR_BER_OFS_CP_BER_OFS(x)  VTSS_ENCODE_BITFIELD(x,10,5)
#define  VTSS_M_VENICE_KR_DEV1_TR_BER_OFS_TR_BER_OFS_CP_BER_OFS     VTSS_ENCODE_BITMASK(10,5)
#define  VTSS_X_VENICE_KR_DEV1_TR_BER_OFS_TR_BER_OFS_CP_BER_OFS(x)  VTSS_EXTRACT_BITFIELD(x,10,5)

/** 
 * \brief
 * Signed value to adjust final c0 tap position from calculated optimal
 * setting.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_BER_OFS_TR_BER_OFS . C0_BER_OFS
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_BER_OFS_TR_BER_OFS_C0_BER_OFS(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_VENICE_KR_DEV1_TR_BER_OFS_TR_BER_OFS_C0_BER_OFS     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_VENICE_KR_DEV1_TR_BER_OFS_TR_BER_OFS_C0_BER_OFS(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Signed value to adjust final cm tap position from calculated optimal
 * setting.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_BER_OFS_TR_BER_OFS . CM_BER_OFS
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_BER_OFS_TR_BER_OFS_CM_BER_OFS(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_VENICE_KR_DEV1_TR_BER_OFS_TR_BER_OFS_CM_BER_OFS     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_VENICE_KR_DEV1_TR_BER_OFS_TR_BER_OFS_CM_BER_OFS(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_LUTSEL
 *
 * Not documented
 */


/** 
 * \brief VS training LUT selection
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_LUTSEL:TR_LUTSEL
 */
#define VTSS_VENICE_KR_DEV1_TR_LUTSEL_TR_LUTSEL  VTSS_IOREG(0x01, 0, 0x8212)

/** 
 * \brief
 * Clears LUT table
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_LUTSEL_TR_LUTSEL . LUT_CLR
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_LUTSEL_TR_LUTSEL_LUT_CLR  VTSS_BIT(12)

/** 
 * \brief
 * Selects LUT table entry (0 to 63).
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_LUTSEL_TR_LUTSEL . LUT_ROW
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_LUTSEL_TR_LUTSEL_LUT_ROW(x)  VTSS_ENCODE_BITFIELD(x,3,6)
#define  VTSS_M_VENICE_KR_DEV1_TR_LUTSEL_TR_LUTSEL_LUT_ROW     VTSS_ENCODE_BITMASK(3,6)
#define  VTSS_X_VENICE_KR_DEV1_TR_LUTSEL_TR_LUTSEL_LUT_ROW(x)  VTSS_EXTRACT_BITFIELD(x,3,6)

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
 * Field: VTSS_VENICE_KR_DEV1_TR_LUTSEL_TR_LUTSEL . LUT_SEL
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_LUTSEL_TR_LUTSEL_LUT_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_KR_DEV1_TR_LUTSEL_TR_LUTSEL_LUT_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_KR_DEV1_TR_LUTSEL_TR_LUTSEL_LUT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_BRKMASK
 *
 * Not documented
 */


/** 
 * \brief VS training break_mask lsw
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_BRKMASK:BRKMASK_LSW
 */
#define VTSS_VENICE_KR_DEV1_TR_BRKMASK_BRKMASK_LSW  VTSS_IOREG(0x01, 0, 0x8213)

/** 
 * \brief
 * Select lptrain state machine breakpoints. Each bit correpsonds to a
 * state (see design doc)
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_BRKMASK_BRKMASK_LSW . BRKMASK_LSW
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_BRKMASK_BRKMASK_LSW_BRKMASK_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_TR_BRKMASK_BRKMASK_LSW_BRKMASK_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_TR_BRKMASK_BRKMASK_LSW_BRKMASK_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS training break_mask msw
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_BRKMASK:BRKMASK_MSW
 */
#define VTSS_VENICE_KR_DEV1_TR_BRKMASK_BRKMASK_MSW  VTSS_IOREG(0x01, 0, 0x8214)

/** 
 * \brief
 * Select lptrain state machine breakpoints. Each bit correpsonds to a
 * state (see design doc)
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_BRKMASK_BRKMASK_MSW . BRKMASK_MSW
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_BRKMASK_BRKMASK_MSW_BRKMASK_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_TR_BRKMASK_BRKMASK_MSW_BRKMASK_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_TR_BRKMASK_BRKMASK_MSW_BRKMASK_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:OBCFG_ADDR
 *
 * Not documented
 */


/** 
 * \brief VS training ROM address for end and obcfg
 *
 * \details
 * Register: \a VENICE_KR_DEV1:OBCFG_ADDR:OBCFG_ADDR
 */
#define VTSS_VENICE_KR_DEV1_OBCFG_ADDR_OBCFG_ADDR  VTSS_IOREG(0x01, 0, 0x8230)

/** 
 * \brief
 * Address of OB tap configuration settings
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_OBCFG_ADDR_OBCFG_ADDR . OBCFG_ADDR
 */
#define  VTSS_F_VENICE_KR_DEV1_OBCFG_ADDR_OBCFG_ADDR_OBCFG_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VENICE_KR_DEV1_OBCFG_ADDR_OBCFG_ADDR_OBCFG_ADDR     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VENICE_KR_DEV1_OBCFG_ADDR_OBCFG_ADDR_OBCFG_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a VENICE_KR_DEV1:APC_TMR
 *
 * Not documented
 */


/** 
 * \brief VS training apc_timer
 *
 * \details
 * Register: \a VENICE_KR_DEV1:APC_TMR:APC_TMR
 */
#define VTSS_VENICE_KR_DEV1_APC_TMR_APC_TMR  VTSS_IOREG(0x01, 0, 0x8240)

/** 
 * \brief
 * Delay between LP tap update, and capture of direct-connect apc values
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_APC_TMR_APC_TMR . APC_TMR
 */
#define  VTSS_F_VENICE_KR_DEV1_APC_TMR_APC_TMR_APC_TMR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_APC_TMR_APC_TMR_APC_TMR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_APC_TMR_APC_TMR_APC_TMR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:WT_TMR
 *
 * Not documented
 */


/** 
 * \brief VS training wait_timer
 *
 * \details
 * Register: \a VENICE_KR_DEV1:WT_TMR:WT_TMR
 */
#define VTSS_VENICE_KR_DEV1_WT_TMR_WT_TMR    VTSS_IOREG(0x01, 0, 0x8241)

/** 
 * \brief
 * wait_timer for training state machine to allow extra training frames to
 * be exchanged
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_WT_TMR_WT_TMR . WT_TMR
 */
#define  VTSS_F_VENICE_KR_DEV1_WT_TMR_WT_TMR_WT_TMR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_WT_TMR_WT_TMR_WT_TMR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_WT_TMR_WT_TMR_WT_TMR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:MW_TMR
 *
 * Not documented
 */


/** 
 * \brief VS training maxwait_timer lsw
 *
 * \details
 * Register: \a VENICE_KR_DEV1:MW_TMR:MW_TMR_LSW
 */
#define VTSS_VENICE_KR_DEV1_MW_TMR_MW_TMR_LSW  VTSS_IOREG(0x01, 0, 0x8242)

/** 
 * \brief
 * maxwait_timer, when training expires and failure declared. 500ms
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_MW_TMR_MW_TMR_LSW . MW_TMR_LSW
 */
#define  VTSS_F_VENICE_KR_DEV1_MW_TMR_MW_TMR_LSW_MW_TMR_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_MW_TMR_MW_TMR_LSW_MW_TMR_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_MW_TMR_MW_TMR_LSW_MW_TMR_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS training maxwait_timer msw
 *
 * \details
 * Register: \a VENICE_KR_DEV1:MW_TMR:MW_TMR_MSW
 */
#define VTSS_VENICE_KR_DEV1_MW_TMR_MW_TMR_MSW  VTSS_IOREG(0x01, 0, 0x8243)

/** 
 * \brief
 * maxwait_timer, when training expires and failure declared. 500ms
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_MW_TMR_MW_TMR_MSW . MW_TMR_MSW
 */
#define  VTSS_F_VENICE_KR_DEV1_MW_TMR_MW_TMR_MSW_MW_TMR_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_MW_TMR_MW_TMR_MSW_MW_TMR_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_MW_TMR_MW_TMR_MSW_MW_TMR_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_STS1
 *
 * Not documented
 */


/** 
 * \brief VS training status 1
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_STS1:TR_STS1
 */
#define VTSS_VENICE_KR_DEV1_TR_STS1_TR_STS1  VTSS_IOREG(0x01, 0, 0x8250)

/** 
 * \brief
 * Indicates loss of training frames (LH)
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_STS1_TR_STS1 . FRLOSS
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_STS1_TR_STS1_FRLOSS  VTSS_BIT(13)

/** 
 * \brief
 * Indicates prbs11 checker is active
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_STS1_TR_STS1 . BER_BUSY
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_STS1_TR_STS1_BER_BUSY  VTSS_BIT(12)

/** 
 * \brief
 * Training state machine
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_STS1_TR_STS1 . TR_SM
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_STS1_TR_STS1_TR_SM(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_VENICE_KR_DEV1_TR_STS1_TR_STS1_TR_SM     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_VENICE_KR_DEV1_TR_STS1_TR_STS1_TR_SM(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * LP training state machine
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_STS1_TR_STS1 . LPT_SM
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_STS1_TR_STS1_LPT_SM(x)  VTSS_ENCODE_BITFIELD(x,4,5)
#define  VTSS_M_VENICE_KR_DEV1_TR_STS1_TR_STS1_LPT_SM     VTSS_ENCODE_BITMASK(4,5)
#define  VTSS_X_VENICE_KR_DEV1_TR_STS1_TR_STS1_LPT_SM(x)  VTSS_EXTRACT_BITFIELD(x,4,5)

/** 
 * \brief
 * Indicates gain_target was not reached during LP training
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_STS1_TR_STS1 . GAIN_FAIL
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_STS1_TR_STS1_GAIN_FAIL  VTSS_BIT(3)

/** 
 * \brief
 * training variable from training state machine
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_STS1_TR_STS1 . TRAINING
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_STS1_TR_STS1_TRAINING  VTSS_BIT(2)

/** 
 * \brief
 * Indicates a DME violation has occured (LH)
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_STS1_TR_STS1 . DME_VIOL
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_STS1_TR_STS1_DME_VIOL  VTSS_BIT(1)

/** 
 * \brief
 * Indicates that local and remote training has completed
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_STS1_TR_STS1 . TR_DONE
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_STS1_TR_STS1_TR_DONE  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_STS2
 *
 * Not documented
 */


/** 
 * \brief VS training status 2
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_STS2:TR_STS2
 */
#define VTSS_VENICE_KR_DEV1_TR_STS2_TR_STS2  VTSS_IOREG(0x01, 0, 0x8251)

/** 
 * \brief
 * CP range error (LH)
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_STS2_TR_STS2 . CP_RANGE_ERR
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_STS2_TR_STS2_CP_RANGE_ERR  VTSS_BIT(2)

/** 
 * \brief
 * C0 range error (LH)
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_STS2_TR_STS2 . C0_RANGE_ERR
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_STS2_TR_STS2_C0_RANGE_ERR  VTSS_BIT(1)

/** 
 * \brief
 * CM range error (LH)
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_STS2_TR_STS2 . CM_RANGE_ERR
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_STS2_TR_STS2_CM_RANGE_ERR  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_TAPVAL
 *
 * Not documented
 */


/** 
 * \brief VS tap CM value
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_TAPVAL:TR_CMVAL
 */
#define VTSS_VENICE_KR_DEV1_TR_TAPVAL_TR_CMVAL  VTSS_IOREG(0x01, 0, 0x8254)

/** 
 * \brief
 * CM value
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_TAPVAL_TR_CMVAL . CM_VAL
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_TAPVAL_TR_CMVAL_CM_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VENICE_KR_DEV1_TR_TAPVAL_TR_CMVAL_CM_VAL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VENICE_KR_DEV1_TR_TAPVAL_TR_CMVAL_CM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS tap C0 value
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_TAPVAL:TR_C0VAL
 */
#define VTSS_VENICE_KR_DEV1_TR_TAPVAL_TR_C0VAL  VTSS_IOREG(0x01, 0, 0x8255)

/** 
 * \brief
 * C0 value
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_TAPVAL_TR_C0VAL . C0_VAL
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_TAPVAL_TR_C0VAL_C0_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VENICE_KR_DEV1_TR_TAPVAL_TR_C0VAL_C0_VAL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VENICE_KR_DEV1_TR_TAPVAL_TR_C0VAL_C0_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS tap CP value
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_TAPVAL:TR_CPVAL
 */
#define VTSS_VENICE_KR_DEV1_TR_TAPVAL_TR_CPVAL  VTSS_IOREG(0x01, 0, 0x8256)

/** 
 * \brief
 * CP value
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_TAPVAL_TR_CPVAL . CP_VAL
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_TAPVAL_TR_CPVAL_CP_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VENICE_KR_DEV1_TR_TAPVAL_TR_CPVAL_CP_VAL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VENICE_KR_DEV1_TR_TAPVAL_TR_CPVAL_CP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_FRAMES_SENT
 *
 * Not documented
 */


/** 
 * \brief VS training frames_sent lsw
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_FRAMES_SENT:FRSENT_LSW
 */
#define VTSS_VENICE_KR_DEV1_TR_FRAMES_SENT_FRSENT_LSW  VTSS_IOREG(0x01, 0, 0x8260)

/** 
 * \brief
 * Number of training frames sent to complete training.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_FRAMES_SENT_FRSENT_LSW . FRSENT_LSW
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_FRAMES_SENT_FRSENT_LSW_FRSENT_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_TR_FRAMES_SENT_FRSENT_LSW_FRSENT_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_TR_FRAMES_SENT_FRSENT_LSW_FRSENT_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS training frames_sent lsw
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_FRAMES_SENT:FRSENT_MSW
 */
#define VTSS_VENICE_KR_DEV1_TR_FRAMES_SENT_FRSENT_MSW  VTSS_IOREG(0x01, 0, 0x8261)

/** 
 * \brief
 * Number of training frames sent to complete training.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_FRAMES_SENT_FRSENT_MSW . FRSENT_MSW
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_FRAMES_SENT_FRSENT_MSW_FRSENT_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_TR_FRAMES_SENT_FRSENT_MSW_FRSENT_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_TR_FRAMES_SENT_FRSENT_MSW_FRSENT_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_LUT
 *
 * Not documented
 */


/** 
 * \brief VS training lut_read lsw
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_LUT:LUT_LSW
 */
#define VTSS_VENICE_KR_DEV1_TR_LUT_LUT_LSW   VTSS_IOREG(0x01, 0, 0x8270)

/** 
 * \brief
 * Measured value of selected LUT.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_LUT_LUT_LSW . LUT_LSW
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_LUT_LUT_LSW_LUT_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_TR_LUT_LUT_LSW_LUT_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_TR_LUT_LUT_LSW_LUT_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS training lut_read msw
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_LUT:LUT_MSW
 */
#define VTSS_VENICE_KR_DEV1_TR_LUT_LUT_MSW   VTSS_IOREG(0x01, 0, 0x8271)

/** 
 * \brief
 * Measured value of selected LUT.
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_LUT_LUT_MSW . LUT_MSW
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_LUT_LUT_MSW_LUT_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_TR_LUT_LUT_MSW_LUT_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_TR_LUT_LUT_MSW_LUT_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_ERRCNT
 *
 * Not documented
 */


/** 
 * \brief VS training prbs11 error_count
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_ERRCNT:TR_ERRCNT
 */
#define VTSS_VENICE_KR_DEV1_TR_ERRCNT_TR_ERRCNT  VTSS_IOREG(0x01, 0, 0x8272)

/** 
 * \brief
 * bit error count of prbs11 checker
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_ERRCNT_TR_ERRCNT . ERRCNT
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_ERRCNT_TR_ERRCNT_ERRCNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_TR_ERRCNT_TR_ERRCNT_ERRCNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_TR_ERRCNT_TR_ERRCNT_ERRCNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_SM_HIST
 *
 * Not documented
 */


/** 
 * \brief VS lptrain state machine history lsw
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_SM_HIST:HIST_LSW
 */
#define VTSS_VENICE_KR_DEV1_TR_SM_HIST_HIST_LSW  VTSS_IOREG(0x01, 0, 0x8274)

/** 
 * \brief
 * lptrain state machine history
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_SM_HIST_HIST_LSW . LPTSM_HIST_LSW
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_SM_HIST_HIST_LSW_LPTSM_HIST_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_KR_DEV1_TR_SM_HIST_HIST_LSW_LPTSM_HIST_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_KR_DEV1_TR_SM_HIST_HIST_LSW_LPTSM_HIST_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS training lptrain state machine history msw
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_SM_HIST:HIST_MSW
 */
#define VTSS_VENICE_KR_DEV1_TR_SM_HIST_HIST_MSW  VTSS_IOREG(0x01, 0, 0x8275)

/** 
 * \brief
 * training state machine history
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_SM_HIST_HIST_MSW . SM_HIST
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_SM_HIST_HIST_MSW_SM_HIST(x)  VTSS_ENCODE_BITFIELD(x,4,7)
#define  VTSS_M_VENICE_KR_DEV1_TR_SM_HIST_HIST_MSW_SM_HIST     VTSS_ENCODE_BITMASK(4,7)
#define  VTSS_X_VENICE_KR_DEV1_TR_SM_HIST_HIST_MSW_SM_HIST(x)  VTSS_EXTRACT_BITFIELD(x,4,7)

/** 
 * \brief
 * lptrain state machine history
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_SM_HIST_HIST_MSW . LPTSM_HIST_MSW
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_SM_HIST_HIST_MSW_LPTSM_HIST_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VENICE_KR_DEV1_TR_SM_HIST_HIST_MSW_LPTSM_HIST_MSW     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VENICE_KR_DEV1_TR_SM_HIST_HIST_MSW_LPTSM_HIST_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a VENICE_KR_DEV1:TR_REC
 *
 * Not documented
 */


/** 
 * \brief VS recorded min,max positions for CM
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_REC:TR_CM_LIM_REC
 */
#define VTSS_VENICE_KR_DEV1_TR_REC_TR_CM_LIM_REC  VTSS_IOREG(0x01, 0, 0x8276)

/** 
 * \brief
 * Recorded position of MAX event for CM
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_REC_TR_CM_LIM_REC . CM_MAX_REC
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_REC_TR_CM_LIM_REC_CM_MAX_REC(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_VENICE_KR_DEV1_TR_REC_TR_CM_LIM_REC_CM_MAX_REC     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_VENICE_KR_DEV1_TR_REC_TR_CM_LIM_REC_CM_MAX_REC(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * Recorded position of MIN event for CM
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_REC_TR_CM_LIM_REC . CM_MIN_REC
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_REC_TR_CM_LIM_REC_CM_MIN_REC(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VENICE_KR_DEV1_TR_REC_TR_CM_LIM_REC_CM_MIN_REC     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VENICE_KR_DEV1_TR_REC_TR_CM_LIM_REC_CM_MIN_REC(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS recorded dme violation positions for CM
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_REC:TR_CM_DME_REC
 */
#define VTSS_VENICE_KR_DEV1_TR_REC_TR_CM_DME_REC  VTSS_IOREG(0x01, 0, 0x8277)

/** 
 * \brief
 * Recorded position of DME_viol event for CM
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_REC_TR_CM_DME_REC . CM_DME_REC
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_REC_TR_CM_DME_REC_CM_DME_REC(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VENICE_KR_DEV1_TR_REC_TR_CM_DME_REC_CM_DME_REC     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VENICE_KR_DEV1_TR_REC_TR_CM_DME_REC_CM_DME_REC(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS recorded min,max positions for C0
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_REC:TR_C0_LIM_REC
 */
#define VTSS_VENICE_KR_DEV1_TR_REC_TR_C0_LIM_REC  VTSS_IOREG(0x01, 0, 0x8278)

/** 
 * \brief
 * Recorded position of MAX event for C0
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_REC_TR_C0_LIM_REC . C0_MAX_REC
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_REC_TR_C0_LIM_REC_C0_MAX_REC(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_VENICE_KR_DEV1_TR_REC_TR_C0_LIM_REC_C0_MAX_REC     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_VENICE_KR_DEV1_TR_REC_TR_C0_LIM_REC_C0_MAX_REC(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * Recorded position of MIN event for C0
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_REC_TR_C0_LIM_REC . C0_MIN_REC
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_REC_TR_C0_LIM_REC_C0_MIN_REC(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VENICE_KR_DEV1_TR_REC_TR_C0_LIM_REC_C0_MIN_REC     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VENICE_KR_DEV1_TR_REC_TR_C0_LIM_REC_C0_MIN_REC(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS recorded dme violation positions for C0
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_REC:TR_C0_DME_REC
 */
#define VTSS_VENICE_KR_DEV1_TR_REC_TR_C0_DME_REC  VTSS_IOREG(0x01, 0, 0x8279)

/** 
 * \brief
 * Recorded position of DME_viol event for C0
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_REC_TR_C0_DME_REC . C0_DME_REC
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_REC_TR_C0_DME_REC_C0_DME_REC(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VENICE_KR_DEV1_TR_REC_TR_C0_DME_REC_C0_DME_REC     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VENICE_KR_DEV1_TR_REC_TR_C0_DME_REC_C0_DME_REC(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS recorded min,max positions for CP
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_REC:TR_CP_LIM_REC
 */
#define VTSS_VENICE_KR_DEV1_TR_REC_TR_CP_LIM_REC  VTSS_IOREG(0x01, 0, 0x827a)

/** 
 * \brief
 * Recorded position of MAX event for CP
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_REC_TR_CP_LIM_REC . CP_MAX_REC
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_REC_TR_CP_LIM_REC_CP_MAX_REC(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_VENICE_KR_DEV1_TR_REC_TR_CP_LIM_REC_CP_MAX_REC     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_VENICE_KR_DEV1_TR_REC_TR_CP_LIM_REC_CP_MAX_REC(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * Recorded position of MIN event for CP
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_REC_TR_CP_LIM_REC . CP_MIN_REC
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_REC_TR_CP_LIM_REC_CP_MIN_REC(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VENICE_KR_DEV1_TR_REC_TR_CP_LIM_REC_CP_MIN_REC     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VENICE_KR_DEV1_TR_REC_TR_CP_LIM_REC_CP_MIN_REC(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS recorded dme violation positions for CP
 *
 * \details
 * Register: \a VENICE_KR_DEV1:TR_REC:TR_CP_DME_REC
 */
#define VTSS_VENICE_KR_DEV1_TR_REC_TR_CP_DME_REC  VTSS_IOREG(0x01, 0, 0x827b)

/** 
 * \brief
 * Recorded position of DME_viol event for CP
 *
 * \details 
 * Field: VTSS_VENICE_KR_DEV1_TR_REC_TR_CP_DME_REC . CP_DME_REC
 */
#define  VTSS_F_VENICE_KR_DEV1_TR_REC_TR_CP_DME_REC_CP_DME_REC(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VENICE_KR_DEV1_TR_REC_TR_CP_DME_REC_CP_DME_REC     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VENICE_KR_DEV1_TR_REC_TR_CP_DME_REC_CP_DME_REC(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


#endif /* _VTSS_VENICE_REGS_VENICE_KR_DEV1_H_ */
