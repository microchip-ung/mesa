#ifndef _VTSS_JAGUAR2_REGS_KR_DEV1_H_
#define _VTSS_JAGUAR2_REGS_KR_DEV1_H_

/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "vtss_jaguar2_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a KR_DEV1
 *
 * \see vtss_target_KR_DEV1_e
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a KR_DEV1:KR_1X0096
 *
 * Not documented
 */


/** 
 * \brief KR PMD control
 *
 * \details
 * Register: \a KR_DEV1:KR_1X0096:KR_1X0096
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_KR_1X0096_KR_1X0096(target)  VTSS_IOREG(target,0x6)

/** 
 * \brief
 * Training enable  
 *
 * \details 
 * 1: Enable KR start-up protocol 
 * 0: Disable KR start-up protocol
 *
 * Field: ::VTSS_KR_DEV1_KR_1X0096_KR_1X0096 . TR_ENABLE
 */
#define  VTSS_F_KR_DEV1_KR_1X0096_KR_1X0096_TR_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_KR_DEV1_KR_1X0096_KR_1X0096_TR_ENABLE  VTSS_BIT(1)
#define  VTSS_X_KR_DEV1_KR_1X0096_KR_1X0096_TR_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Restart training (SC) 
 *
 * \details 
 * 1: Reset KR start-up protocol 
 * 0: Normal operation
 *
 * Field: ::VTSS_KR_DEV1_KR_1X0096_KR_1X0096 . TR_RESTART
 */
#define  VTSS_F_KR_DEV1_KR_1X0096_KR_1X0096_TR_RESTART(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_KR_DEV1_KR_1X0096_KR_1X0096_TR_RESTART  VTSS_BIT(0)
#define  VTSS_X_KR_DEV1_KR_1X0096_KR_1X0096_TR_RESTART(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a KR_DEV1:KR_1X0097
 *
 * Not documented
 */


/** 
 * \brief KR PMD status
 *
 * \details
 * Register: \a KR_DEV1:KR_1X0097:KR_1X0097
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_KR_1X0097_KR_1X0097(target)  VTSS_IOREG(target,0xf)

/** 
 * \brief
 * Training failure 
 *
 * \details 
 * 1: Training failure has been detected 
 * 0: Training failure has not been detected
 *
 * Field: ::VTSS_KR_DEV1_KR_1X0097_KR_1X0097 . TR_FAIL
 */
#define  VTSS_F_KR_DEV1_KR_1X0097_KR_1X0097_TR_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_KR_DEV1_KR_1X0097_KR_1X0097_TR_FAIL  VTSS_BIT(3)
#define  VTSS_X_KR_DEV1_KR_1X0097_KR_1X0097_TR_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Startup protocol status 
 *
 * \details 
 * 1: Start-up protocol in progress 
 * 0: Start-up protocol complete
 *
 * Field: ::VTSS_KR_DEV1_KR_1X0097_KR_1X0097 . STPROT
 */
#define  VTSS_F_KR_DEV1_KR_1X0097_KR_1X0097_STPROT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_KR_DEV1_KR_1X0097_KR_1X0097_STPROT  VTSS_BIT(2)
#define  VTSS_X_KR_DEV1_KR_1X0097_KR_1X0097_STPROT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Frame lock 
 *
 * \details 
 * 1: Training frame delineation detected, 
 * 0: Training frame delineation not detected
 *
 * Field: ::VTSS_KR_DEV1_KR_1X0097_KR_1X0097 . FRLOCK
 */
#define  VTSS_F_KR_DEV1_KR_1X0097_KR_1X0097_FRLOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_KR_DEV1_KR_1X0097_KR_1X0097_FRLOCK  VTSS_BIT(1)
#define  VTSS_X_KR_DEV1_KR_1X0097_KR_1X0097_FRLOCK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Receiver status 
 *
 * \details 
 * 1: Receiver trained and ready to receive data 
 * 0: Receiver training
 *
 * Field: ::VTSS_KR_DEV1_KR_1X0097_KR_1X0097 . RCVR_RDY
 */
#define  VTSS_F_KR_DEV1_KR_1X0097_KR_1X0097_RCVR_RDY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_KR_DEV1_KR_1X0097_KR_1X0097_RCVR_RDY  VTSS_BIT(0)
#define  VTSS_X_KR_DEV1_KR_1X0097_KR_1X0097_RCVR_RDY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a KR_DEV1:KR_1X0098
 *
 * Not documented
 */


/** 
 * \brief KR LP coefficient update
 *
 * \details
 * Register: \a KR_DEV1:KR_1X0098:KR_1X0098
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_KR_1X0098_KR_1X0098(target)  VTSS_IOREG(target,0x7)

/** 
 * \brief
 * Received coefficient update field
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_KR_1X0098_KR_1X0098 . LPCOEF
 */
#define  VTSS_F_KR_DEV1_KR_1X0098_KR_1X0098_LPCOEF(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_KR_1X0098_KR_1X0098_LPCOEF     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_KR_1X0098_KR_1X0098_LPCOEF(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV1:KR_1X0099
 *
 * Not documented
 */


/** 
 * \brief KR LP status report
 *
 * \details
 * Register: \a KR_DEV1:KR_1X0099:KR_1X0099
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_KR_1X0099_KR_1X0099(target)  VTSS_IOREG(target,0x8)

/** 
 * \brief
 * Received status report field
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_KR_1X0099_KR_1X0099 . LPSTAT
 */
#define  VTSS_F_KR_DEV1_KR_1X0099_KR_1X0099_LPSTAT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_KR_1X0099_KR_1X0099_LPSTAT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_KR_1X0099_KR_1X0099_LPSTAT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV1:KR_1X009A
 *
 * Not documented
 */


/** 
 * \brief KR LD coefficient update
 *
 * \details
 * Register: \a KR_DEV1:KR_1X009A:KR_1X009A
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_KR_1X009A_KR_1X009A(target)  VTSS_IOREG(target,0x9)

/** 
 * \brief
 * Transmitted coefficient update field
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_KR_1X009A_KR_1X009A . LDCOEF
 */
#define  VTSS_F_KR_DEV1_KR_1X009A_KR_1X009A_LDCOEF(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_KR_1X009A_KR_1X009A_LDCOEF     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_KR_1X009A_KR_1X009A_LDCOEF(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV1:KR_1X009B
 *
 * Not documented
 */


/** 
 * \brief KR LD status report
 *
 * \details
 * Register: \a KR_DEV1:KR_1X009B:KR_1X009B
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_KR_1X009B_KR_1X009B(target)  VTSS_IOREG(target,0xa)

/** 
 * \brief
 * Transmitted status report field
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_KR_1X009B_KR_1X009B . LDSTAT
 */
#define  VTSS_F_KR_DEV1_KR_1X009B_KR_1X009B_LDSTAT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_KR_1X009B_KR_1X009B_LDSTAT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_KR_1X009B_KR_1X009B_LDSTAT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV1:TR_CFG0
 *
 * Not documented
 */


/** 
 * \brief VS training config 0
 *
 * \details
 * Register: \a KR_DEV1:TR_CFG0:TR_CFG0
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_CFG0_TR_CFG0(target)  VTSS_IOREG(target,0x10)

/** 
 * \brief
 * Clock divider value for timer clocks.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG0_TR_CFG0 . TMR_DVDR
 */
#define  VTSS_F_KR_DEV1_TR_CFG0_TR_CFG0_TMR_DVDR(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_KR_DEV1_TR_CFG0_TR_CFG0_TMR_DVDR     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_KR_DEV1_TR_CFG0_TR_CFG0_TMR_DVDR(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Use directly connected APC signals
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG0_TR_CFG0 . APC_DRCT_EN
 */
#define  VTSS_F_KR_DEV1_TR_CFG0_TR_CFG0_APC_DRCT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_KR_DEV1_TR_CFG0_TR_CFG0_APC_DRCT_EN  VTSS_BIT(11)
#define  VTSS_X_KR_DEV1_TR_CFG0_TR_CFG0_APC_DRCT_EN(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Invert recieved prbs11 within training frame
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG0_TR_CFG0 . RX_INV
 */
#define  VTSS_F_KR_DEV1_TR_CFG0_TR_CFG0_RX_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_KR_DEV1_TR_CFG0_TR_CFG0_RX_INV  VTSS_BIT(10)
#define  VTSS_X_KR_DEV1_TR_CFG0_TR_CFG0_RX_INV(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Invert transmitted prbs11 within training frame
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG0_TR_CFG0 . TX_INV
 */
#define  VTSS_F_KR_DEV1_TR_CFG0_TR_CFG0_TX_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_KR_DEV1_TR_CFG0_TR_CFG0_TX_INV  VTSS_BIT(9)
#define  VTSS_X_KR_DEV1_TR_CFG0_TR_CFG0_TX_INV(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set local taps starting point 
 *
 * \details 
 * 0: Set to INITIALIZE 
 * 1: Set to PRESET
 *
 * Field: ::VTSS_KR_DEV1_TR_CFG0_TR_CFG0 . LD_PRE_INIT
 */
#define  VTSS_F_KR_DEV1_TR_CFG0_TR_CFG0_LD_PRE_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_KR_DEV1_TR_CFG0_TR_CFG0_LD_PRE_INIT  VTSS_BIT(4)
#define  VTSS_X_KR_DEV1_TR_CFG0_TR_CFG0_LD_PRE_INIT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Send first LP request 
 *
 * \details 
 * 0: Send   INITIALIZE 
 * 1: Send   PRESET
 *
 * Field: ::VTSS_KR_DEV1_TR_CFG0_TR_CFG0 . LP_PRE_INIT
 */
#define  VTSS_F_KR_DEV1_TR_CFG0_TR_CFG0_LP_PRE_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_KR_DEV1_TR_CFG0_TR_CFG0_LP_PRE_INIT  VTSS_BIT(3)
#define  VTSS_X_KR_DEV1_TR_CFG0_TR_CFG0_LP_PRE_INIT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Update taps regardless of v2,vp sum.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG0_TR_CFG0 . NOSUM
 */
#define  VTSS_F_KR_DEV1_TR_CFG0_TR_CFG0_NOSUM(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_KR_DEV1_TR_CFG0_TR_CFG0_NOSUM  VTSS_BIT(2)
#define  VTSS_X_KR_DEV1_TR_CFG0_TR_CFG0_NOSUM(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable partial OB tap configuration.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG0_TR_CFG0 . PART_CFG_EN
 */
#define  VTSS_F_KR_DEV1_TR_CFG0_TR_CFG0_PART_CFG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_KR_DEV1_TR_CFG0_TR_CFG0_PART_CFG_EN  VTSS_BIT(1)
#define  VTSS_X_KR_DEV1_TR_CFG0_TR_CFG0_PART_CFG_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Allow LP to to control tap settings.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG0_TR_CFG0 . TAPCTL_EN
 */
#define  VTSS_F_KR_DEV1_TR_CFG0_TR_CFG0_TAPCTL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_KR_DEV1_TR_CFG0_TR_CFG0_TAPCTL_EN  VTSS_BIT(0)
#define  VTSS_X_KR_DEV1_TR_CFG0_TR_CFG0_TAPCTL_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a KR_DEV1:TR_CFG1
 *
 * Not documented
 */


/** 
 * \brief VS training config 1
 *
 * \details
 * Register: \a KR_DEV1:TR_CFG1:TR_CFG1
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_CFG1_TR_CFG1(target)  VTSS_IOREG(target,0x11)

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
 * 5: pgdet 
 * 6: link_fail 
 * 7: an_wait 
 * 8: break_link
 *
 * Field: ::VTSS_KR_DEV1_TR_CFG1_TR_CFG1 . TMR_HOLD
 */
#define  VTSS_F_KR_DEV1_TR_CFG1_TR_CFG1_TMR_HOLD(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_KR_DEV1_TR_CFG1_TR_CFG1_TMR_HOLD     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_KR_DEV1_TR_CFG1_TR_CFG1_TMR_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * Register Group: \a KR_DEV1:TR_CFG2
 *
 * Not documented
 */


/** 
 * \brief VS training config 2
 *
 * \details
 * Register: \a KR_DEV1:TR_CFG2:TR_CFG2
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_CFG2_TR_CFG2(target)  VTSS_IOREG(target,0x12)

/** 
 * \brief
 * max	settings for vp sum.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG2_TR_CFG2 . VP_MAX
 */
#define  VTSS_F_KR_DEV1_TR_CFG2_TR_CFG2_VP_MAX(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_KR_DEV1_TR_CFG2_TR_CFG2_VP_MAX     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_KR_DEV1_TR_CFG2_TR_CFG2_VP_MAX(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * min	settings for v2 sum.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG2_TR_CFG2 . V2_MIN
 */
#define  VTSS_F_KR_DEV1_TR_CFG2_TR_CFG2_V2_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_KR_DEV1_TR_CFG2_TR_CFG2_V2_MIN     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_KR_DEV1_TR_CFG2_TR_CFG2_V2_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a KR_DEV1:TR_CFG3
 *
 * Not documented
 */


/** 
 * \brief VS training config 3
 *
 * \details
 * Register: \a KR_DEV1:TR_CFG3:TR_CFG3
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_CFG3_TR_CFG3(target)  VTSS_IOREG(target,0x13)

/** 
 * \brief
 * max	settings for local transmitter.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG3_TR_CFG3 . CP_MAX
 */
#define  VTSS_F_KR_DEV1_TR_CFG3_TR_CFG3_CP_MAX(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_KR_DEV1_TR_CFG3_TR_CFG3_CP_MAX     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_KR_DEV1_TR_CFG3_TR_CFG3_CP_MAX(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * min	settings for local transmitter.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG3_TR_CFG3 . CP_MIN
 */
#define  VTSS_F_KR_DEV1_TR_CFG3_TR_CFG3_CP_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_KR_DEV1_TR_CFG3_TR_CFG3_CP_MIN     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_KR_DEV1_TR_CFG3_TR_CFG3_CP_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a KR_DEV1:TR_CFG4
 *
 * Not documented
 */


/** 
 * \brief VS training config 4
 *
 * \details
 * Register: \a KR_DEV1:TR_CFG4:TR_CFG4
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_CFG4_TR_CFG4(target)  VTSS_IOREG(target,0x14)

/** 
 * \brief
 * max	settings for local transmitter.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG4_TR_CFG4 . C0_MAX
 */
#define  VTSS_F_KR_DEV1_TR_CFG4_TR_CFG4_C0_MAX(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_KR_DEV1_TR_CFG4_TR_CFG4_C0_MAX     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_KR_DEV1_TR_CFG4_TR_CFG4_C0_MAX(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * min	settings for local transmitter.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG4_TR_CFG4 . C0_MIN
 */
#define  VTSS_F_KR_DEV1_TR_CFG4_TR_CFG4_C0_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_KR_DEV1_TR_CFG4_TR_CFG4_C0_MIN     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_KR_DEV1_TR_CFG4_TR_CFG4_C0_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a KR_DEV1:TR_CFG5
 *
 * Not documented
 */


/** 
 * \brief VS training config 5
 *
 * \details
 * Register: \a KR_DEV1:TR_CFG5:TR_CFG5
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_CFG5_TR_CFG5(target)  VTSS_IOREG(target,0x15)

/** 
 * \brief
 * max	settings for local transmitter.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG5_TR_CFG5 . CM_MAX
 */
#define  VTSS_F_KR_DEV1_TR_CFG5_TR_CFG5_CM_MAX(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_KR_DEV1_TR_CFG5_TR_CFG5_CM_MAX     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_KR_DEV1_TR_CFG5_TR_CFG5_CM_MAX(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * min	settings for local transmitter.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG5_TR_CFG5 . CM_MIN
 */
#define  VTSS_F_KR_DEV1_TR_CFG5_TR_CFG5_CM_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_KR_DEV1_TR_CFG5_TR_CFG5_CM_MIN     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_KR_DEV1_TR_CFG5_TR_CFG5_CM_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a KR_DEV1:TR_CFG6
 *
 * Not documented
 */


/** 
 * \brief VS training config 6
 *
 * \details
 * Register: \a KR_DEV1:TR_CFG6:TR_CFG6
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_CFG6_TR_CFG6(target)  VTSS_IOREG(target,0x16)

/** 
 * \brief
 * initialize settings for local transmitter.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG6_TR_CFG6 . CP_INIT
 */
#define  VTSS_F_KR_DEV1_TR_CFG6_TR_CFG6_CP_INIT(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_KR_DEV1_TR_CFG6_TR_CFG6_CP_INIT     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_KR_DEV1_TR_CFG6_TR_CFG6_CP_INIT(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * initialize settings for local transmitter.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG6_TR_CFG6 . C0_INIT
 */
#define  VTSS_F_KR_DEV1_TR_CFG6_TR_CFG6_C0_INIT(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_KR_DEV1_TR_CFG6_TR_CFG6_C0_INIT     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_KR_DEV1_TR_CFG6_TR_CFG6_C0_INIT(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a KR_DEV1:TR_CFG7
 *
 * Not documented
 */


/** 
 * \brief VS training config 7
 *
 * \details
 * Register: \a KR_DEV1:TR_CFG7:TR_CFG7
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_CFG7_TR_CFG7(target)  VTSS_IOREG(target,0x17)

/** 
 * \brief
 * initialize settings for local transmitter.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG7_TR_CFG7 . CM_INIT
 */
#define  VTSS_F_KR_DEV1_TR_CFG7_TR_CFG7_CM_INIT(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_KR_DEV1_TR_CFG7_TR_CFG7_CM_INIT     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_KR_DEV1_TR_CFG7_TR_CFG7_CM_INIT(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Signed value to adjust final LP C(+1) tap position from calculated
 * optimal setting.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG7_TR_CFG7 . DFE_OFS
 */
#define  VTSS_F_KR_DEV1_TR_CFG7_TR_CFG7_DFE_OFS(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_KR_DEV1_TR_CFG7_TR_CFG7_DFE_OFS     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_KR_DEV1_TR_CFG7_TR_CFG7_DFE_OFS(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a KR_DEV1:TR_CFG8
 *
 * Not documented
 */


/** 
 * \brief VS training config 8
 *
 * \details
 * Register: \a KR_DEV1:TR_CFG8:TR_CFG8
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_CFG8_TR_CFG8(target)  VTSS_IOREG(target,0x18)

/** 
 * \brief
 * Weighted average calculation of DFE tap 1
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG8_TR_CFG8 . WT1
 */
#define  VTSS_F_KR_DEV1_TR_CFG8_TR_CFG8_WT1(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_KR_DEV1_TR_CFG8_TR_CFG8_WT1     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_KR_DEV1_TR_CFG8_TR_CFG8_WT1(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Weighted average calculation of DFE tap 2
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG8_TR_CFG8 . WT2
 */
#define  VTSS_F_KR_DEV1_TR_CFG8_TR_CFG8_WT2(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_KR_DEV1_TR_CFG8_TR_CFG8_WT2     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_KR_DEV1_TR_CFG8_TR_CFG8_WT2(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Weighted average calculation of DFE tap 3
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG8_TR_CFG8 . WT3
 */
#define  VTSS_F_KR_DEV1_TR_CFG8_TR_CFG8_WT3(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_KR_DEV1_TR_CFG8_TR_CFG8_WT3     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_KR_DEV1_TR_CFG8_TR_CFG8_WT3(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Weighted average calculation of DFE tap 4
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG8_TR_CFG8 . WT4
 */
#define  VTSS_F_KR_DEV1_TR_CFG8_TR_CFG8_WT4(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_KR_DEV1_TR_CFG8_TR_CFG8_WT4     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_KR_DEV1_TR_CFG8_TR_CFG8_WT4(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a KR_DEV1:TR_CFG9
 *
 * Not documented
 */


/** 
 * \brief VS training config 9
 *
 * \details
 * Register: \a KR_DEV1:TR_CFG9:TR_CFG9
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_CFG9_TR_CFG9(target)  VTSS_IOREG(target,0x19)

/** 
 * \brief
 * Number of training frames used for BER calculation.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_CFG9_TR_CFG9 . FRCNT_BER
 */
#define  VTSS_F_KR_DEV1_TR_CFG9_TR_CFG9_FRCNT_BER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_TR_CFG9_TR_CFG9_FRCNT_BER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_TR_CFG9_TR_CFG9_FRCNT_BER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV1:TR_GAIN
 *
 * Not documented
 */


/** 
 * \brief VS training gain target and margin values
 *
 * \details
 * Register: \a KR_DEV1:TR_GAIN:TR_GAIN
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_GAIN_TR_GAIN(target)  VTSS_IOREG(target,0x1a)

/** 
 * \brief
 * LP C(0) optimized when GAIN is gain_targ +/- 2*gain_marg
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_GAIN_TR_GAIN . GAIN_MARG
 */
#define  VTSS_F_KR_DEV1_TR_GAIN_TR_GAIN_GAIN_MARG(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_KR_DEV1_TR_GAIN_TR_GAIN_GAIN_MARG     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_KR_DEV1_TR_GAIN_TR_GAIN_GAIN_MARG(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Target value of GAIN setting during LP C(0) optimization.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_GAIN_TR_GAIN . GAIN_TARG
 */
#define  VTSS_F_KR_DEV1_TR_GAIN_TR_GAIN_GAIN_TARG(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_KR_DEV1_TR_GAIN_TR_GAIN_GAIN_TARG     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_KR_DEV1_TR_GAIN_TR_GAIN_GAIN_TARG(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * Register Group: \a KR_DEV1:TR_COEF_OVRD
 *
 * Not documented
 */


/** 
 * \brief VS training coefficient update override
 *
 * \details
 * Register: \a KR_DEV1:TR_COEF_OVRD:TR_COEF_OVRD
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_COEF_OVRD_TR_COEF_OVRD(target)  VTSS_IOREG(target,0x1b)

/** 
 * \brief
 * Override Coef_update field to transmit
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_COEF_OVRD_TR_COEF_OVRD . COEF_OVRD
 */
#define  VTSS_F_KR_DEV1_TR_COEF_OVRD_TR_COEF_OVRD_COEF_OVRD(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_TR_COEF_OVRD_TR_COEF_OVRD_COEF_OVRD     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_TR_COEF_OVRD_TR_COEF_OVRD_COEF_OVRD(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV1:TR_STAT_OVRD
 *
 * Not documented
 */


/** 
 * \brief VS training status report override
 *
 * \details
 * Register: \a KR_DEV1:TR_STAT_OVRD:TR_STAT_OVRD
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_STAT_OVRD_TR_STAT_OVRD(target)  VTSS_IOREG(target,0x1c)

/** 
 * \brief
 * Override Stat_report field to transmit
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_STAT_OVRD_TR_STAT_OVRD . STAT_OVRD
 */
#define  VTSS_F_KR_DEV1_TR_STAT_OVRD_TR_STAT_OVRD_STAT_OVRD(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_TR_STAT_OVRD_TR_STAT_OVRD_STAT_OVRD     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_TR_STAT_OVRD_TR_STAT_OVRD_STAT_OVRD(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV1:TR_OVRD
 *
 * Not documented
 */


/** 
 * \brief VS training override
 *
 * \details
 * Register: \a KR_DEV1:TR_OVRD:TR_OVRD
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_OVRD_TR_OVRD(target)  VTSS_IOREG(target,0xb)

/** 
 * \brief
 * Enable manual training
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_OVRD_TR_OVRD . OVRD_EN
 */
#define  VTSS_F_KR_DEV1_TR_OVRD_TR_OVRD_OVRD_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_KR_DEV1_TR_OVRD_TR_OVRD_OVRD_EN  VTSS_BIT(4)
#define  VTSS_X_KR_DEV1_TR_OVRD_TR_OVRD_OVRD_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Control of rx_trained variable for training SM
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_OVRD_TR_OVRD . RXTRAINED_OVRD
 */
#define  VTSS_F_KR_DEV1_TR_OVRD_TR_OVRD_RXTRAINED_OVRD(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_KR_DEV1_TR_OVRD_TR_OVRD_RXTRAINED_OVRD  VTSS_BIT(3)
#define  VTSS_X_KR_DEV1_TR_OVRD_TR_OVRD_RXTRAINED_OVRD(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Generate BER enable pulse (SC)
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_OVRD_TR_OVRD . BER_EN_OVRD
 */
#define  VTSS_F_KR_DEV1_TR_OVRD_TR_OVRD_BER_EN_OVRD(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_KR_DEV1_TR_OVRD_TR_OVRD_BER_EN_OVRD  VTSS_BIT(2)
#define  VTSS_X_KR_DEV1_TR_OVRD_TR_OVRD_BER_EN_OVRD(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Generate Coef_update_valid pulse (SC)
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_OVRD_TR_OVRD . COEF_OVRD_VLD
 */
#define  VTSS_F_KR_DEV1_TR_OVRD_TR_OVRD_COEF_OVRD_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_KR_DEV1_TR_OVRD_TR_OVRD_COEF_OVRD_VLD  VTSS_BIT(1)
#define  VTSS_X_KR_DEV1_TR_OVRD_TR_OVRD_COEF_OVRD_VLD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Generate Stat_report_valid pulse (SC)
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_OVRD_TR_OVRD . STAT_OVRD_VLD
 */
#define  VTSS_F_KR_DEV1_TR_OVRD_TR_OVRD_STAT_OVRD_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_KR_DEV1_TR_OVRD_TR_OVRD_STAT_OVRD_VLD  VTSS_BIT(0)
#define  VTSS_X_KR_DEV1_TR_OVRD_TR_OVRD_STAT_OVRD_VLD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a KR_DEV1:TR_STEP
 *
 * Not documented
 */


/** 
 * \brief VS training state step
 *
 * \details
 * Register: \a KR_DEV1:TR_STEP:TR_STEP
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_STEP_TR_STEP(target)  VTSS_IOREG(target,0xc)

/** 
 * \brief
 * Step to next lptrain state (if at breakpoint) (SC)
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_STEP_TR_STEP . STEP
 */
#define  VTSS_F_KR_DEV1_TR_STEP_TR_STEP_STEP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_KR_DEV1_TR_STEP_TR_STEP_STEP  VTSS_BIT(0)
#define  VTSS_X_KR_DEV1_TR_STEP_TR_STEP_STEP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a KR_DEV1:TR_MTHD
 *
 * Not documented
 */


/** 
 * \brief VS training method
 *
 * \details
 * Register: \a KR_DEV1:TR_MTHD:TR_MTHD
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_MTHD_TR_MTHD(target)  VTSS_IOREG(target,0x1d)

/** 
 * \brief
 * Training method for remote C(+1) 
 *
 * \details 
 * 0 : BER method
 * 1 : Gain method
 * 2 : DFE method
 *
 * Field: ::VTSS_KR_DEV1_TR_MTHD_TR_MTHD . MTHD_CP
 */
#define  VTSS_F_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CP(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CP     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CP(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Training method for remote C(0)
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_MTHD_TR_MTHD . MTHD_C0
 */
#define  VTSS_F_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_C0(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_C0     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_C0(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Training method for remote C(-1)
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_MTHD_TR_MTHD . MTHD_CM
 */
#define  VTSS_F_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CM(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CM     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_KR_DEV1_TR_MTHD_TR_MTHD_MTHD_CM(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * remote tap to optimize first 
 *
 * \details 
 * 0 : C(-1)
 * 1 : C(0)
 * 2 : C(+1)
 *
 * Field: ::VTSS_KR_DEV1_TR_MTHD_TR_MTHD . ORD1
 */
#define  VTSS_F_KR_DEV1_TR_MTHD_TR_MTHD_ORD1(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_KR_DEV1_TR_MTHD_TR_MTHD_ORD1     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_KR_DEV1_TR_MTHD_TR_MTHD_ORD1(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * remote tap to optimize second
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_MTHD_TR_MTHD . ORD2
 */
#define  VTSS_F_KR_DEV1_TR_MTHD_TR_MTHD_ORD2(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_KR_DEV1_TR_MTHD_TR_MTHD_ORD2     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_KR_DEV1_TR_MTHD_TR_MTHD_ORD2(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * remote tap to optimize third
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_MTHD_TR_MTHD . ORD3
 */
#define  VTSS_F_KR_DEV1_TR_MTHD_TR_MTHD_ORD3(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_KR_DEV1_TR_MTHD_TR_MTHD_ORD3     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_KR_DEV1_TR_MTHD_TR_MTHD_ORD3(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a KR_DEV1:TR_BER_THR
 *
 * Not documented
 */


/** 
 * \brief VS training BER threshold settings
 *
 * \details
 * Register: \a KR_DEV1:TR_BER_THR:TR_BER_THR
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_BER_THR_TR_BER_THR(target)  VTSS_IOREG(target,0x1e)

/** 
 * \brief
 * Only consider error count > ber_err_th
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_BER_THR_TR_BER_THR . BER_ERR_TH
 */
#define  VTSS_F_KR_DEV1_TR_BER_THR_TR_BER_THR_BER_ERR_TH(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_KR_DEV1_TR_BER_THR_TR_BER_THR_BER_ERR_TH     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_KR_DEV1_TR_BER_THR_TR_BER_THR_BER_ERR_TH(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Only consider errored range > ber_wid_th
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_BER_THR_TR_BER_THR . BER_WID_TH
 */
#define  VTSS_F_KR_DEV1_TR_BER_THR_TR_BER_THR_BER_WID_TH(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_KR_DEV1_TR_BER_THR_TR_BER_THR_BER_WID_TH     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_KR_DEV1_TR_BER_THR_TR_BER_THR_BER_WID_TH(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a KR_DEV1:TR_BER_OFS
 *
 * Not documented
 */


/** 
 * \brief VS training BER offset setting
 *
 * \details
 * Register: \a KR_DEV1:TR_BER_OFS:TR_BER_OFS
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_BER_OFS_TR_BER_OFS(target)  VTSS_IOREG(target,0x1f)

/** 
 * \brief
 * Signed value to adjust final tap position from calculated optimal
 * setting.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_BER_OFS_TR_BER_OFS . BER_OFS
 */
#define  VTSS_F_KR_DEV1_TR_BER_OFS_TR_BER_OFS_BER_OFS(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_KR_DEV1_TR_BER_OFS_TR_BER_OFS_BER_OFS     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_KR_DEV1_TR_BER_OFS_TR_BER_OFS_BER_OFS(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a KR_DEV1:TR_LUTSEL
 *
 * Not documented
 */


/** 
 * \brief VS training LUT selection
 *
 * \details
 * Register: \a KR_DEV1:TR_LUTSEL:TR_LUTSEL
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_LUTSEL_TR_LUTSEL(target)  VTSS_IOREG(target,0x20)

/** 
 * \brief
 * Selects LUT table entry (0 to 63).
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_LUTSEL_TR_LUTSEL . LUT_ROW
 */
#define  VTSS_F_KR_DEV1_TR_LUTSEL_TR_LUTSEL_LUT_ROW(x)  VTSS_ENCODE_BITFIELD(x,3,6)
#define  VTSS_M_KR_DEV1_TR_LUTSEL_TR_LUTSEL_LUT_ROW     VTSS_ENCODE_BITMASK(3,6)
#define  VTSS_X_KR_DEV1_TR_LUTSEL_TR_LUTSEL_LUT_ROW(x)  VTSS_EXTRACT_BITFIELD(x,3,6)

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
 * Field: ::VTSS_KR_DEV1_TR_LUTSEL_TR_LUTSEL . LUT_SEL
 */
#define  VTSS_F_KR_DEV1_TR_LUTSEL_TR_LUTSEL_LUT_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_KR_DEV1_TR_LUTSEL_TR_LUTSEL_LUT_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_KR_DEV1_TR_LUTSEL_TR_LUTSEL_LUT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a KR_DEV1:TR_BRKMASK
 *
 * Not documented
 */


/** 
 * \brief VS training break_mask lsw
 *
 * \details
 * Register: \a KR_DEV1:TR_BRKMASK:BRKMASK_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_BRKMASK_BRKMASK_LSW(target)  VTSS_IOREG(target,0x21)

/** 
 * \brief
 * Select lptrain state machine breakpoints. Each bit correpsonds to a
 * state (see design doc)
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_BRKMASK_BRKMASK_LSW . BRKMASK_LSW
 */
#define  VTSS_F_KR_DEV1_TR_BRKMASK_BRKMASK_LSW_BRKMASK_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_TR_BRKMASK_BRKMASK_LSW_BRKMASK_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_TR_BRKMASK_BRKMASK_LSW_BRKMASK_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS training break_mask msw
 *
 * \details
 * Register: \a KR_DEV1:TR_BRKMASK:TR_BRKMASK_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_BRKMASK_TR_BRKMASK_MSW(target)  VTSS_IOREG(target,0x22)

/** 
 * \brief
 * Select lptrain state machine breakpoints. Each bit correpsonds to a
 * state (see design doc)
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_BRKMASK_TR_BRKMASK_MSW . BRKMASK_MSW
 */
#define  VTSS_F_KR_DEV1_TR_BRKMASK_TR_BRKMASK_MSW_BRKMASK_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_TR_BRKMASK_TR_BRKMASK_MSW_BRKMASK_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_TR_BRKMASK_TR_BRKMASK_MSW_BRKMASK_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV1:TR_ROMADR
 *
 * Not documented
 */


/** 
 * \brief VS training ROM address for gain
 *
 * \details
 * Register: \a KR_DEV1:TR_ROMADR:ROMADR1
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_ROMADR_ROMADR1(target)  VTSS_IOREG(target,0x0)

/** 
 * \brief
 * ROM starting address of Initial GAIN routine
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_ROMADR_ROMADR1 . ROMADR_GAIN1
 */
#define  VTSS_F_KR_DEV1_TR_ROMADR_ROMADR1_ROMADR_GAIN1(x)  VTSS_ENCODE_BITFIELD(x,7,7)
#define  VTSS_M_KR_DEV1_TR_ROMADR_ROMADR1_ROMADR_GAIN1     VTSS_ENCODE_BITMASK(7,7)
#define  VTSS_X_KR_DEV1_TR_ROMADR_ROMADR1_ROMADR_GAIN1(x)  VTSS_EXTRACT_BITFIELD(x,7,7)

/** 
 * \brief
 * ROM starting address of Iterative GAIN routine
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_ROMADR_ROMADR1 . ROMADR_GAIN2
 */
#define  VTSS_F_KR_DEV1_TR_ROMADR_ROMADR1_ROMADR_GAIN2(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_KR_DEV1_TR_ROMADR_ROMADR1_ROMADR_GAIN2     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_KR_DEV1_TR_ROMADR_ROMADR1_ROMADR_GAIN2(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS training ROM address for dfe
 *
 * \details
 * Register: \a KR_DEV1:TR_ROMADR:ROMADR2
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_ROMADR_ROMADR2(target)  VTSS_IOREG(target,0x1)

/** 
 * \brief
 * ROM starting address of Initial DFE routine
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_ROMADR_ROMADR2 . ROMADR_DFE1
 */
#define  VTSS_F_KR_DEV1_TR_ROMADR_ROMADR2_ROMADR_DFE1(x)  VTSS_ENCODE_BITFIELD(x,7,7)
#define  VTSS_M_KR_DEV1_TR_ROMADR_ROMADR2_ROMADR_DFE1     VTSS_ENCODE_BITMASK(7,7)
#define  VTSS_X_KR_DEV1_TR_ROMADR_ROMADR2_ROMADR_DFE1(x)  VTSS_EXTRACT_BITFIELD(x,7,7)

/** 
 * \brief
 * ROM starting address of Iterative DFE routine
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_ROMADR_ROMADR2 . ROMADR_DFE2
 */
#define  VTSS_F_KR_DEV1_TR_ROMADR_ROMADR2_ROMADR_DFE2(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_KR_DEV1_TR_ROMADR_ROMADR2_ROMADR_DFE2     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_KR_DEV1_TR_ROMADR_ROMADR2_ROMADR_DFE2(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS training ROM address for ber
 *
 * \details
 * Register: \a KR_DEV1:TR_ROMADR:ROMADR3
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_ROMADR_ROMADR3(target)  VTSS_IOREG(target,0x2)

/** 
 * \brief
 * ROM starting address of Initial BER routine
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_ROMADR_ROMADR3 . ROMADR_BER1
 */
#define  VTSS_F_KR_DEV1_TR_ROMADR_ROMADR3_ROMADR_BER1(x)  VTSS_ENCODE_BITFIELD(x,7,7)
#define  VTSS_M_KR_DEV1_TR_ROMADR_ROMADR3_ROMADR_BER1     VTSS_ENCODE_BITMASK(7,7)
#define  VTSS_X_KR_DEV1_TR_ROMADR_ROMADR3_ROMADR_BER1(x)  VTSS_EXTRACT_BITFIELD(x,7,7)

/** 
 * \brief
 * ROM starting address of Iterative BER routine
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_ROMADR_ROMADR3 . ROMADR_BER2
 */
#define  VTSS_F_KR_DEV1_TR_ROMADR_ROMADR3_ROMADR_BER2(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_KR_DEV1_TR_ROMADR_ROMADR3_ROMADR_BER2     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_KR_DEV1_TR_ROMADR_ROMADR3_ROMADR_BER2(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS training ROM address for end and obcfg
 *
 * \details
 * Register: \a KR_DEV1:TR_ROMADR:ROMADR4
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_ROMADR_ROMADR4(target)  VTSS_IOREG(target,0x3)

/** 
 * \brief
 * ROM starting address of post-training routing
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_ROMADR_ROMADR4 . ROMADR_END
 */
#define  VTSS_F_KR_DEV1_TR_ROMADR_ROMADR4_ROMADR_END(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_KR_DEV1_TR_ROMADR_ROMADR4_ROMADR_END     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_KR_DEV1_TR_ROMADR_ROMADR4_ROMADR_END(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a KR_DEV1:OBCFG_ADDR
 *
 * Not documented
 */


/** 
 * \brief VS training ROM address for end and obcfg
 *
 * \details
 * Register: \a KR_DEV1:OBCFG_ADDR:OBCFG_ADDR
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_OBCFG_ADDR_OBCFG_ADDR(target)  VTSS_IOREG(target,0x23)

/** 
 * \brief
 * Address of OB tap configuration settings
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_OBCFG_ADDR_OBCFG_ADDR . OBCFG_ADDR
 */
#define  VTSS_F_KR_DEV1_OBCFG_ADDR_OBCFG_ADDR_OBCFG_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_KR_DEV1_OBCFG_ADDR_OBCFG_ADDR_OBCFG_ADDR     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_KR_DEV1_OBCFG_ADDR_OBCFG_ADDR_OBCFG_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a KR_DEV1:APC_TMR
 *
 * Not documented
 */


/** 
 * \brief VS training apc_timer
 *
 * \details
 * Register: \a KR_DEV1:APC_TMR:APC_TMR
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_APC_TMR_APC_TMR(target)  VTSS_IOREG(target,0x24)

/** 
 * \brief
 * Delay between LP tap update, and capture of direct-connect apc values
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_APC_TMR_APC_TMR . APC_TMR
 */
#define  VTSS_F_KR_DEV1_APC_TMR_APC_TMR_APC_TMR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_APC_TMR_APC_TMR_APC_TMR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_APC_TMR_APC_TMR_APC_TMR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV1:WT_TMR
 *
 * Not documented
 */


/** 
 * \brief VS training wait_timer
 *
 * \details
 * Register: \a KR_DEV1:WT_TMR:WT_TMR
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_WT_TMR_WT_TMR(target)   VTSS_IOREG(target,0x25)

/** 
 * \brief
 * wait_timer for training state machine to allow extra training frames to
 * be exchanged
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_WT_TMR_WT_TMR . WT_TMR
 */
#define  VTSS_F_KR_DEV1_WT_TMR_WT_TMR_WT_TMR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_WT_TMR_WT_TMR_WT_TMR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_WT_TMR_WT_TMR_WT_TMR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV1:MW_TMR
 *
 * Not documented
 */


/** 
 * \brief VS training maxwait_timer lsw
 *
 * \details
 * Register: \a KR_DEV1:MW_TMR:MW_TMR_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_MW_TMR_MW_TMR_LSW(target)  VTSS_IOREG(target,0x26)

/** 
 * \brief
 * maxwait_timer, when training expires and failure declared. 500ms
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_MW_TMR_MW_TMR_LSW . MW_TMR_LSW
 */
#define  VTSS_F_KR_DEV1_MW_TMR_MW_TMR_LSW_MW_TMR_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_MW_TMR_MW_TMR_LSW_MW_TMR_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_MW_TMR_MW_TMR_LSW_MW_TMR_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS training maxwait_timer msw
 *
 * \details
 * Register: \a KR_DEV1:MW_TMR:MW_TMR_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_MW_TMR_MW_TMR_MSW(target)  VTSS_IOREG(target,0x27)

/** 
 * \brief
 * maxwait_timer, when training expires and failure declared. 500ms
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_MW_TMR_MW_TMR_MSW . MW_TMR_MSW
 */
#define  VTSS_F_KR_DEV1_MW_TMR_MW_TMR_MSW_MW_TMR_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_MW_TMR_MW_TMR_MSW_MW_TMR_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_MW_TMR_MW_TMR_MSW_MW_TMR_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV1:TR_STS1
 *
 * Not documented
 */


/** 
 * \brief VS training status 1
 *
 * \details
 * Register: \a KR_DEV1:TR_STS1:TR_STS1
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_STS1_TR_STS1(target)  VTSS_IOREG(target,0xd)

/** 
 * \brief
 * Indicates prbs11 checker is active
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_STS1_TR_STS1 . BER_BUSY
 */
#define  VTSS_F_KR_DEV1_TR_STS1_TR_STS1_BER_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_KR_DEV1_TR_STS1_TR_STS1_BER_BUSY  VTSS_BIT(12)
#define  VTSS_X_KR_DEV1_TR_STS1_TR_STS1_BER_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Training state machine
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_STS1_TR_STS1 . TR_SM
 */
#define  VTSS_F_KR_DEV1_TR_STS1_TR_STS1_TR_SM(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_KR_DEV1_TR_STS1_TR_STS1_TR_SM     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_KR_DEV1_TR_STS1_TR_STS1_TR_SM(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * LP training state machine
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_STS1_TR_STS1 . LPTRAIN_SM
 */
#define  VTSS_F_KR_DEV1_TR_STS1_TR_STS1_LPTRAIN_SM(x)  VTSS_ENCODE_BITFIELD(x,4,5)
#define  VTSS_M_KR_DEV1_TR_STS1_TR_STS1_LPTRAIN_SM     VTSS_ENCODE_BITMASK(4,5)
#define  VTSS_X_KR_DEV1_TR_STS1_TR_STS1_LPTRAIN_SM(x)  VTSS_EXTRACT_BITFIELD(x,4,5)

/** 
 * \brief
 * Indicates gain_target was not reached during LP training
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_STS1_TR_STS1 . GAIN_FAIL
 */
#define  VTSS_F_KR_DEV1_TR_STS1_TR_STS1_GAIN_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_KR_DEV1_TR_STS1_TR_STS1_GAIN_FAIL  VTSS_BIT(3)
#define  VTSS_X_KR_DEV1_TR_STS1_TR_STS1_GAIN_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * training variable from training state machine
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_STS1_TR_STS1 . TRAINING
 */
#define  VTSS_F_KR_DEV1_TR_STS1_TR_STS1_TRAINING(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_KR_DEV1_TR_STS1_TR_STS1_TRAINING  VTSS_BIT(2)
#define  VTSS_X_KR_DEV1_TR_STS1_TR_STS1_TRAINING(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Indicates a DME violation has occured (LH)
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_STS1_TR_STS1 . DME_VIOL
 */
#define  VTSS_F_KR_DEV1_TR_STS1_TR_STS1_DME_VIOL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_KR_DEV1_TR_STS1_TR_STS1_DME_VIOL  VTSS_BIT(1)
#define  VTSS_X_KR_DEV1_TR_STS1_TR_STS1_DME_VIOL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Indicates that local and remote training has completed
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_STS1_TR_STS1 . TR_DONE
 */
#define  VTSS_F_KR_DEV1_TR_STS1_TR_STS1_TR_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_KR_DEV1_TR_STS1_TR_STS1_TR_DONE  VTSS_BIT(0)
#define  VTSS_X_KR_DEV1_TR_STS1_TR_STS1_TR_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a KR_DEV1:TR_STS2
 *
 * Not documented
 */


/** 
 * \brief VS training status 2
 *
 * \details
 * Register: \a KR_DEV1:TR_STS2:TR_STS2
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_STS2_TR_STS2(target)  VTSS_IOREG(target,0xe)

/** 
 * \brief
 * CP range error (LH)
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_STS2_TR_STS2 . CP_RANGE_ERR
 */
#define  VTSS_F_KR_DEV1_TR_STS2_TR_STS2_CP_RANGE_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_KR_DEV1_TR_STS2_TR_STS2_CP_RANGE_ERR  VTSS_BIT(2)
#define  VTSS_X_KR_DEV1_TR_STS2_TR_STS2_CP_RANGE_ERR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * C0 range error (LH)
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_STS2_TR_STS2 . C0_RANGE_ERR
 */
#define  VTSS_F_KR_DEV1_TR_STS2_TR_STS2_C0_RANGE_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_KR_DEV1_TR_STS2_TR_STS2_C0_RANGE_ERR  VTSS_BIT(1)
#define  VTSS_X_KR_DEV1_TR_STS2_TR_STS2_C0_RANGE_ERR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * CM range error (LH)
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_STS2_TR_STS2 . CM_RANGE_ERR
 */
#define  VTSS_F_KR_DEV1_TR_STS2_TR_STS2_CM_RANGE_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_KR_DEV1_TR_STS2_TR_STS2_CM_RANGE_ERR  VTSS_BIT(0)
#define  VTSS_X_KR_DEV1_TR_STS2_TR_STS2_CM_RANGE_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a KR_DEV1:TR_TAPVAL
 *
 * Not documented
 */


/** 
 * \brief VS tap CM value
 *
 * \details
 * Register: \a KR_DEV1:TR_TAPVAL:TR_CMVAL
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_TAPVAL_TR_CMVAL(target)  VTSS_IOREG(target,0x28)

/** 
 * \brief
 * CM value
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_TAPVAL_TR_CMVAL . CM_VAL
 */
#define  VTSS_F_KR_DEV1_TR_TAPVAL_TR_CMVAL_CM_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_KR_DEV1_TR_TAPVAL_TR_CMVAL_CM_VAL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_KR_DEV1_TR_TAPVAL_TR_CMVAL_CM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS tap C0 value
 *
 * \details
 * Register: \a KR_DEV1:TR_TAPVAL:TR_C0VAL
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_TAPVAL_TR_C0VAL(target)  VTSS_IOREG(target,0x29)

/** 
 * \brief
 * C0 value
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_TAPVAL_TR_C0VAL . C0_VAL
 */
#define  VTSS_F_KR_DEV1_TR_TAPVAL_TR_C0VAL_C0_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_KR_DEV1_TR_TAPVAL_TR_C0VAL_C0_VAL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_KR_DEV1_TR_TAPVAL_TR_C0VAL_C0_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief VS tap CP value
 *
 * \details
 * Register: \a KR_DEV1:TR_TAPVAL:TR_CPVAL
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_TAPVAL_TR_CPVAL(target)  VTSS_IOREG(target,0x2a)

/** 
 * \brief
 * CP value
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_TAPVAL_TR_CPVAL . CP_VAL
 */
#define  VTSS_F_KR_DEV1_TR_TAPVAL_TR_CPVAL_CP_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_KR_DEV1_TR_TAPVAL_TR_CPVAL_CP_VAL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_KR_DEV1_TR_TAPVAL_TR_CPVAL_CP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a KR_DEV1:TR_FRAMES_SENT
 *
 * Not documented
 */


/** 
 * \brief VS training frames_sent lsw
 *
 * \details
 * Register: \a KR_DEV1:TR_FRAMES_SENT:FRSENT_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_FRAMES_SENT_FRSENT_LSW(target)  VTSS_IOREG(target,0x4)

/** 
 * \brief
 * Number of training frames sent to complete training.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_FRAMES_SENT_FRSENT_LSW . FRSENT_LSW
 */
#define  VTSS_F_KR_DEV1_TR_FRAMES_SENT_FRSENT_LSW_FRSENT_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_TR_FRAMES_SENT_FRSENT_LSW_FRSENT_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_TR_FRAMES_SENT_FRSENT_LSW_FRSENT_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS training frames_sent lsw
 *
 * \details
 * Register: \a KR_DEV1:TR_FRAMES_SENT:FRSENT_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_FRAMES_SENT_FRSENT_MSW(target)  VTSS_IOREG(target,0x5)

/** 
 * \brief
 * Number of training frames sent to complete training.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_FRAMES_SENT_FRSENT_MSW . FRSENT_MSW
 */
#define  VTSS_F_KR_DEV1_TR_FRAMES_SENT_FRSENT_MSW_FRSENT_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_TR_FRAMES_SENT_FRSENT_MSW_FRSENT_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_TR_FRAMES_SENT_FRSENT_MSW_FRSENT_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV1:TR_LUT
 *
 * Not documented
 */


/** 
 * \brief VS training lut_read lsw
 *
 * \details
 * Register: \a KR_DEV1:TR_LUT:LUT_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_LUT_LUT_LSW(target)  VTSS_IOREG(target,0x2b)

/** 
 * \brief
 * Measured value of selected LUT.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_LUT_LUT_LSW . LUT_LSW
 */
#define  VTSS_F_KR_DEV1_TR_LUT_LUT_LSW_LUT_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_TR_LUT_LUT_LSW_LUT_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_TR_LUT_LUT_LSW_LUT_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS training lut_read msw
 *
 * \details
 * Register: \a KR_DEV1:TR_LUT:LUT_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_LUT_LUT_MSW(target)  VTSS_IOREG(target,0x2c)

/** 
 * \brief
 * Measured value of selected LUT.
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_LUT_LUT_MSW . LUT_MSW
 */
#define  VTSS_F_KR_DEV1_TR_LUT_LUT_MSW_LUT_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_TR_LUT_LUT_MSW_LUT_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_TR_LUT_LUT_MSW_LUT_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV1:TR_ERRCNT
 *
 * Not documented
 */


/** 
 * \brief VS training prbs11 error_count
 *
 * \details
 * Register: \a KR_DEV1:TR_ERRCNT:TR_ERRCNT
 *
 * @param target A \a ::vtss_target_KR_DEV1_e target
 */
#define VTSS_KR_DEV1_TR_ERRCNT_TR_ERRCNT(target)  VTSS_IOREG(target,0x2d)

/** 
 * \brief
 * bit error count of prbs11 checker
 *
 * \details 
 * Field: ::VTSS_KR_DEV1_TR_ERRCNT_TR_ERRCNT . ERRCNT
 */
#define  VTSS_F_KR_DEV1_TR_ERRCNT_TR_ERRCNT_ERRCNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV1_TR_ERRCNT_TR_ERRCNT_ERRCNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV1_TR_ERRCNT_TR_ERRCNT_ERRCNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_JAGUAR2_REGS_KR_DEV1_H_ */
