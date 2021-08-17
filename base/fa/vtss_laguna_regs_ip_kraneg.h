/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

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

#ifndef _VTSS_LAGUNA_REGS_IP_KRANEG_H_
#define _VTSS_LAGUNA_REGS_IP_KRANEG_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a IP_KRANEG
 *
 * \see vtss_target_IP_KRANEG_e
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a IP_KRANEG:KR_PMD_CTRL
 *
 * Not documented
 */


/**
 * \brief KR PMD control
 *
 * \details
 * Register: \a IP_KRANEG:KR_PMD_CTRL:KR_PMD_CTRL
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_KR_PMD_CTRL(target)   VTSS_IOREG(target,0x196)

/**
 * \brief
 * Training enable
 *
 * \details
 * 1: Enable KR start-up protocol
 * 0: Disable KR start-up protocol

 *
 * Field: ::VTSS_IP_KRANEG_KR_PMD_CTRL . TR_ENABLE
 */
#define  VTSS_F_IP_KRANEG_KR_PMD_CTRL_TR_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_IP_KRANEG_KR_PMD_CTRL_TR_ENABLE  VTSS_BIT(1)
#define  VTSS_X_IP_KRANEG_KR_PMD_CTRL_TR_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Restart training (SC)
 *
 * \details
 * 1: Reset KR start-up protocol
 * 0: Normal operation

 *
 * Field: ::VTSS_IP_KRANEG_KR_PMD_CTRL . TR_RESTART
 */
#define  VTSS_F_IP_KRANEG_KR_PMD_CTRL_TR_RESTART(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_IP_KRANEG_KR_PMD_CTRL_TR_RESTART  VTSS_BIT(0)
#define  VTSS_X_IP_KRANEG_KR_PMD_CTRL_TR_RESTART(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a IP_KRANEG:KR_PMD_STS
 *
 * Not documented
 */


/**
 * \brief KR PMD status
 *
 * \details
 * Register: \a IP_KRANEG:KR_PMD_STS:KR_PMD_STS
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_KR_PMD_STS(target)    VTSS_IOREG(target,0x197)

/**
 * \brief
 * Training failure
 *
 * \details
 * 1: Training failure has been detected
 * 0: Training failure has not been detected

 *
 * Field: ::VTSS_IP_KRANEG_KR_PMD_STS . TR_FAIL
 */
#define  VTSS_F_IP_KRANEG_KR_PMD_STS_TR_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_IP_KRANEG_KR_PMD_STS_TR_FAIL  VTSS_BIT(3)
#define  VTSS_X_IP_KRANEG_KR_PMD_STS_TR_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Startup protocol status
 *
 * \details
 * 1: Start-up protocol in progress
 * 0: Start-up protocol complete

 *
 * Field: ::VTSS_IP_KRANEG_KR_PMD_STS . STPROT
 */
#define  VTSS_F_IP_KRANEG_KR_PMD_STS_STPROT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_IP_KRANEG_KR_PMD_STS_STPROT   VTSS_BIT(2)
#define  VTSS_X_IP_KRANEG_KR_PMD_STS_STPROT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Frame lock
 *
 * \details
 * 1: Training frame delineation detected
 * 0: Training frame delineation not detected

 *
 * Field: ::VTSS_IP_KRANEG_KR_PMD_STS . FRLOCK
 */
#define  VTSS_F_IP_KRANEG_KR_PMD_STS_FRLOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_IP_KRANEG_KR_PMD_STS_FRLOCK   VTSS_BIT(1)
#define  VTSS_X_IP_KRANEG_KR_PMD_STS_FRLOCK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Receiver status
 *
 * \details
 * 1: Receiver trained and ready to receive data
 * 0: Receiver training

 *
 * Field: ::VTSS_IP_KRANEG_KR_PMD_STS . RCVR_RDY
 */
#define  VTSS_F_IP_KRANEG_KR_PMD_STS_RCVR_RDY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_IP_KRANEG_KR_PMD_STS_RCVR_RDY  VTSS_BIT(0)
#define  VTSS_X_IP_KRANEG_KR_PMD_STS_RCVR_RDY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a IP_KRANEG:LP_COEF_UPD
 *
 * Not documented
 */


/**
 * \brief KR LP coefficient update
 *
 * \details
 * Register: \a IP_KRANEG:LP_COEF_UPD:LP_COEF_UPD
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LP_COEF_UPD(target)   VTSS_IOREG(target,0x198)

/**
 * \brief
 * Received coefficient update field
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LP_COEF_UPD . LPCOEF
 */
#define  VTSS_F_IP_KRANEG_LP_COEF_UPD_LPCOEF(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LP_COEF_UPD_LPCOEF     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LP_COEF_UPD_LPCOEF(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a IP_KRANEG:LP_STS_RPT
 *
 * Not documented
 */


/**
 * \brief KR LP status report
 *
 * \details
 * Register: \a IP_KRANEG:LP_STS_RPT:LP_STS_RPT
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LP_STS_RPT(target)    VTSS_IOREG(target,0x199)

/**
 * \brief
 * Received status report field
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LP_STS_RPT . LPSTAT
 */
#define  VTSS_F_IP_KRANEG_LP_STS_RPT_LPSTAT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LP_STS_RPT_LPSTAT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LP_STS_RPT_LPSTAT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a IP_KRANEG:LD_COEF_UPD
 *
 * Not documented
 */


/**
 * \brief KR LD coefficient update
 *
 * \details
 * Register: \a IP_KRANEG:LD_COEF_UPD:LD_COEF_UPD
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LD_COEF_UPD(target)   VTSS_IOREG(target,0x19a)

/**
 * \brief
 * Transmitted coefficient update field
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LD_COEF_UPD . LDCOEF
 */
#define  VTSS_F_IP_KRANEG_LD_COEF_UPD_LDCOEF(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LD_COEF_UPD_LDCOEF     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LD_COEF_UPD_LDCOEF(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a IP_KRANEG:LD_STS_RPT
 *
 * Not documented
 */


/**
 * \brief KR LD status report
 *
 * \details
 * Register: \a IP_KRANEG:LD_STS_RPT:LD_STS_RPT
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LD_STS_RPT(target)    VTSS_IOREG(target,0x19b)

/**
 * \brief
 * Transmitted status report field
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LD_STS_RPT . LDSTAT
 */
#define  VTSS_F_IP_KRANEG_LD_STS_RPT_LDSTAT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LD_STS_RPT_LDSTAT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LD_STS_RPT_LDSTAT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a IP_KRANEG:CLK_EN
 *
 * Not documented
 */


/**
 * \brief clock enable
 *
 * \details
 * Register: \a IP_KRANEG:CLK_EN:CLK_EN
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_CLK_EN(target)        VTSS_IOREG(target,0x1100)

/**
 * \brief
 * Enable 64:66 gearbox clock
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_CLK_EN . CLK_GBOX_ENABLE
 */
#define  VTSS_F_IP_KRANEG_CLK_EN_CLK_GBOX_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_IP_KRANEG_CLK_EN_CLK_GBOX_ENABLE  VTSS_BIT(5)
#define  VTSS_X_IP_KRANEG_CLK_EN_CLK_GBOX_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable AN state machine clock
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_CLK_EN . CLK_CSR_ENABLE
 */
#define  VTSS_F_IP_KRANEG_CLK_EN_CLK_CSR_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_IP_KRANEG_CLK_EN_CLK_CSR_ENABLE  VTSS_BIT(4)
#define  VTSS_X_IP_KRANEG_CLK_EN_CLK_CSR_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable Tx core clock
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_CLK_EN . CLK_TX64_ENABLE
 */
#define  VTSS_F_IP_KRANEG_CLK_EN_CLK_TX64_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_IP_KRANEG_CLK_EN_CLK_TX64_ENABLE  VTSS_BIT(3)
#define  VTSS_X_IP_KRANEG_CLK_EN_CLK_TX64_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable Rx core clock
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_CLK_EN . CLK_RX64_ENABLE
 */
#define  VTSS_F_IP_KRANEG_CLK_EN_CLK_RX64_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_IP_KRANEG_CLK_EN_CLK_RX64_ENABLE  VTSS_BIT(2)
#define  VTSS_X_IP_KRANEG_CLK_EN_CLK_RX64_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable 8b10b sync clock
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_CLK_EN . CLK_SYNC8B10B_ENABLE
 */
#define  VTSS_F_IP_KRANEG_CLK_EN_CLK_SYNC8B10B_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_IP_KRANEG_CLK_EN_CLK_SYNC8B10B_ENABLE  VTSS_BIT(1)
#define  VTSS_X_IP_KRANEG_CLK_EN_CLK_SYNC8B10B_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable 64b66b sync clock
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_CLK_EN . CLK_SYNC10G_ENABLE
 */
#define  VTSS_F_IP_KRANEG_CLK_EN_CLK_SYNC10G_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_IP_KRANEG_CLK_EN_CLK_SYNC10G_ENABLE  VTSS_BIT(0)
#define  VTSS_X_IP_KRANEG_CLK_EN_CLK_SYNC10G_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a IP_KRANEG:TMR_HOLD
 *
 * Not documented
 */


/**
 * \brief timer hold mask
 *
 * \details
 * Register: \a IP_KRANEG:TMR_HOLD:TMR_HOLD
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_TMR_HOLD(target)      VTSS_IOREG(target,0x1101)

/**
 * \brief
 * Freeze timers. Bit set...
 *
 * \details
 * 0: wait
 * 1: max_wait
 * 2: rate_detect
 * 3: training
 * 4: page_detect
 * 5: link_pass
 * 6: link_fail
 * 7: an_wait
 * 8: break_link
 * 9: gen0
 * 10: gen1

 *
 * Field: ::VTSS_IP_KRANEG_TMR_HOLD . TMR_HOLD
 */
#define  VTSS_F_IP_KRANEG_TMR_HOLD_TMR_HOLD(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_IP_KRANEG_TMR_HOLD_TMR_HOLD     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_IP_KRANEG_TMR_HOLD_TMR_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * Register Group: \a IP_KRANEG:TR_CFG0
 *
 * Not documented
 */


/**
 * \brief training config 0
 *
 * \details
 * Register: \a IP_KRANEG:TR_CFG0:TR_CFG0
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_TR_CFG0(target)       VTSS_IOREG(target,0x1102)

/**
 * \brief
 * Configuration for the number of Link Training frames with receiver ready
 * bit (of control channel status report) is set to assert remote receiver
 * ready interrupt.(IRQ_VEC.REM_RDY_1)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_TR_CFG0 . REM_RDY_THRESH
 */
#define  VTSS_F_IP_KRANEG_TR_CFG0_REM_RDY_THRESH(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_IP_KRANEG_TR_CFG0_REM_RDY_THRESH     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_IP_KRANEG_TR_CFG0_REM_RDY_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Configuration to select the condition to cause IRQ_VEC.LPSVALID
 * Interrupt
 *
 * \details
 * 1 : Generate Interrupt when a change in any of the 16 bits of the
 * received status report is observed.
 * 0 : Generate Interrupt when a change in any of the 6 LSB bits i.e. [5:0]
 * of the status report is observed. Change in other bits does not cause an
 * interrupt.
 *
 * Field: ::VTSS_IP_KRANEG_TR_CFG0 . LPSVLD_INT_CFG
 */
#define  VTSS_F_IP_KRANEG_TR_CFG0_LPSVLD_INT_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_IP_KRANEG_TR_CFG0_LPSVLD_INT_CFG  VTSS_BIT(20)
#define  VTSS_X_IP_KRANEG_TR_CFG0_LPSVLD_INT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Training pattern polynomial selection
 *
 * \details
 * 0: x^11 + x^10 + x^6 + x^5 + 1 (100G - lane 0)
 * 1: x^11 + x^9  + x^6 + x^5 + 1 (100G - lane 1)
 * 2: x^11 + x^8  + x^6 + x^4 + 1 (100G - lane 2)
 * 3: x^11 + x^7  + x^6 + x^4 + 1 (100G - lane 3)
 * 4: x^11 + x^9 + 1 (10G)

 *
 * Field: ::VTSS_IP_KRANEG_TR_CFG0 . PRBS_SEL
 */
#define  VTSS_F_IP_KRANEG_TR_CFG0_PRBS_SEL(x)  VTSS_ENCODE_BITFIELD(x,17,3)
#define  VTSS_M_IP_KRANEG_TR_CFG0_PRBS_SEL     VTSS_ENCODE_BITMASK(17,3)
#define  VTSS_X_IP_KRANEG_TR_CFG0_PRBS_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,3)

/**
 * \brief
 * Training pattern seed
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_TR_CFG0 . PRBS_SEED
 */
#define  VTSS_F_IP_KRANEG_TR_CFG0_PRBS_SEED(x)  VTSS_ENCODE_BITFIELD(x,6,11)
#define  VTSS_M_IP_KRANEG_TR_CFG0_PRBS_SEED     VTSS_ENCODE_BITMASK(6,11)
#define  VTSS_X_IP_KRANEG_TR_CFG0_PRBS_SEED(x)  VTSS_EXTRACT_BITFIELD(x,6,11)

/**
 * \brief
 * Invert Rx prbs11 in training frame
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_TR_CFG0 . RX_INV
 */
#define  VTSS_F_IP_KRANEG_TR_CFG0_RX_INV(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_IP_KRANEG_TR_CFG0_RX_INV      VTSS_BIT(1)
#define  VTSS_X_IP_KRANEG_TR_CFG0_RX_INV(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Invert Tx prbs11 in training frame
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_TR_CFG0 . TX_INV
 */
#define  VTSS_F_IP_KRANEG_TR_CFG0_TX_INV(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_IP_KRANEG_TR_CFG0_TX_INV      VTSS_BIT(0)
#define  VTSS_X_IP_KRANEG_TR_CFG0_TX_INV(x)   VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a IP_KRANEG:FRCNT_BER
 *
 * Not documented
 */


/**
 * \brief Frame count for BER
 *
 * \details
 * Register: \a IP_KRANEG:FRCNT_BER:FRCNT_BER
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_FRCNT_BER(target)     VTSS_IOREG(target,0x1103)

/**
 * \brief
 * Number of training frames used for BER calc.
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_FRCNT_BER . FRCNT_BER
 */
#define  VTSS_F_IP_KRANEG_FRCNT_BER_FRCNT_BER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_FRCNT_BER_FRCNT_BER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_FRCNT_BER_FRCNT_BER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a IP_KRANEG:TR_FRSENT
 *
 * Not documented
 */


/**
 * \brief training frames sent
 *
 * \details
 * Register: \a IP_KRANEG:TR_FRSENT:TR_FRSENT
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_TR_FRSENT(target)     VTSS_IOREG(target,0x1104)

/**
 * \brief
 * Number of training frames sent during link training.
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_TR_FRSENT . FRSENT
 */
#define  VTSS_F_IP_KRANEG_TR_FRSENT_FRSENT(x)  (x)
#define  VTSS_M_IP_KRANEG_TR_FRSENT_FRSENT     0xffffffff
#define  VTSS_X_IP_KRANEG_TR_FRSENT_FRSENT(x)  (x)

/**
 * Register Group: \a IP_KRANEG:TR_ERRCNT
 *
 * Not documented
 */


/**
 * \brief training prbs11 error_count
 *
 * \details
 * Register: \a IP_KRANEG:TR_ERRCNT:TR_ERRCNT
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_TR_ERRCNT(target)     VTSS_IOREG(target,0x1105)

/**
 * \brief
 * bit error count of prbs11 checker
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_TR_ERRCNT . ERRCNT
 */
#define  VTSS_F_IP_KRANEG_TR_ERRCNT_ERRCNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_TR_ERRCNT_ERRCNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_TR_ERRCNT_ERRCNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a IP_KRANEG:AN_CFG0
 *
 * Not documented
 */


/**
 * \brief AN config 0
 *
 * \details
 * Register: \a IP_KRANEG:AN_CFG0:AN_CFG0
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_AN_CFG0(target)       VTSS_IOREG(target,0x0)

/**
 * \brief
 * AN reset   (SC)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_CFG0 . AN_RESET
 */
#define  VTSS_F_IP_KRANEG_AN_CFG0_AN_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_IP_KRANEG_AN_CFG0_AN_RESET    VTSS_BIT(15)
#define  VTSS_X_IP_KRANEG_AN_CFG0_AN_RESET(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Extended next page control
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_CFG0 . NPCTL
 */
#define  VTSS_F_IP_KRANEG_AN_CFG0_NPCTL(x)    VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_IP_KRANEG_AN_CFG0_NPCTL       VTSS_BIT(13)
#define  VTSS_X_IP_KRANEG_AN_CFG0_NPCTL(x)    VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * AN enable
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_CFG0 . AN_ENABLE
 */
#define  VTSS_F_IP_KRANEG_AN_CFG0_AN_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_IP_KRANEG_AN_CFG0_AN_ENABLE   VTSS_BIT(12)
#define  VTSS_X_IP_KRANEG_AN_CFG0_AN_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * AN restart (SC)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_CFG0 . AN_RESTART
 */
#define  VTSS_F_IP_KRANEG_AN_CFG0_AN_RESTART(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_IP_KRANEG_AN_CFG0_AN_RESTART  VTSS_BIT(9)
#define  VTSS_X_IP_KRANEG_AN_CFG0_AN_RESTART(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * Register Group: \a IP_KRANEG:AN_STS0
 *
 * Not documented
 */


/**
 * \brief AN status 0
 *
 * \details
 * Register: \a IP_KRANEG:AN_STS0:AN_STS0
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_AN_STS0(target)       VTSS_IOREG(target,0x1)

/**
 * \brief
 * Parallel detection fault (LH)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_STS0 . PARDETFLT
 */
#define  VTSS_F_IP_KRANEG_AN_STS0_PARDETFLT(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_IP_KRANEG_AN_STS0_PARDETFLT   VTSS_BIT(9)
#define  VTSS_X_IP_KRANEG_AN_STS0_PARDETFLT(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Extended next page status
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_STS0 . NPSTAT
 */
#define  VTSS_F_IP_KRANEG_AN_STS0_NPSTAT(x)   VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_IP_KRANEG_AN_STS0_NPSTAT      VTSS_BIT(7)
#define  VTSS_X_IP_KRANEG_AN_STS0_NPSTAT(x)   VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Page received (LH)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_STS0 . PG_RCVD
 */
#define  VTSS_F_IP_KRANEG_AN_STS0_PG_RCVD(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_IP_KRANEG_AN_STS0_PG_RCVD     VTSS_BIT(6)
#define  VTSS_X_IP_KRANEG_AN_STS0_PG_RCVD(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * AN complete
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_STS0 . AN_COMPLETE
 */
#define  VTSS_F_IP_KRANEG_AN_STS0_AN_COMPLETE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_IP_KRANEG_AN_STS0_AN_COMPLETE  VTSS_BIT(5)
#define  VTSS_X_IP_KRANEG_AN_STS0_AN_COMPLETE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Remote fault (LH)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_STS0 . REM_FLT
 */
#define  VTSS_F_IP_KRANEG_AN_STS0_REM_FLT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_IP_KRANEG_AN_STS0_REM_FLT     VTSS_BIT(4)
#define  VTSS_X_IP_KRANEG_AN_STS0_REM_FLT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * AN ability
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_STS0 . AN_ABLE
 */
#define  VTSS_F_IP_KRANEG_AN_STS0_AN_ABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_IP_KRANEG_AN_STS0_AN_ABLE     VTSS_BIT(3)
#define  VTSS_X_IP_KRANEG_AN_STS0_AN_ABLE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Link status (LL)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_STS0 . LINKSTAT
 */
#define  VTSS_F_IP_KRANEG_AN_STS0_LINKSTAT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_IP_KRANEG_AN_STS0_LINKSTAT    VTSS_BIT(2)
#define  VTSS_X_IP_KRANEG_AN_STS0_LINKSTAT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LP AN ability
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_STS0 . AN_LP_ABLE
 */
#define  VTSS_F_IP_KRANEG_AN_STS0_AN_LP_ABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_IP_KRANEG_AN_STS0_AN_LP_ABLE  VTSS_BIT(0)
#define  VTSS_X_IP_KRANEG_AN_STS0_AN_LP_ABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a IP_KRANEG:LD_ADV
 *
 * Local Device advertised abilities
 */


/**
 * \brief LD advertised abilities 15-0
 *
 * \details
 * Register: \a IP_KRANEG:LD_ADV:LD_ADV0
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LD_ADV0(target)       VTSS_IOREG(target,0x10)

/**
 * \brief
 * Local advertised abilities D[15:0]
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LD_ADV0 . ADV0
 */
#define  VTSS_F_IP_KRANEG_LD_ADV0_ADV0(x)     VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LD_ADV0_ADV0        VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LD_ADV0_ADV0(x)     VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LD advertised abilities 31-16
 *
 * \details
 * Register: \a IP_KRANEG:LD_ADV:LD_ADV1
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LD_ADV1(target)       VTSS_IOREG(target,0x11)

/**
 * \brief
 * Local advertised abilities D[31:16]
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LD_ADV1 . ADV1
 */
#define  VTSS_F_IP_KRANEG_LD_ADV1_ADV1(x)     VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LD_ADV1_ADV1        VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LD_ADV1_ADV1(x)     VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LD advertised abilities 47-32
 *
 * \details
 * Register: \a IP_KRANEG:LD_ADV:LD_ADV2
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LD_ADV2(target)       VTSS_IOREG(target,0x12)

/**
 * \brief
 * Local advertised abilities D[47:32]
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LD_ADV2 . ADV2
 */
#define  VTSS_F_IP_KRANEG_LD_ADV2_ADV2(x)     VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LD_ADV2_ADV2        VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LD_ADV2_ADV2(x)     VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a IP_KRANEG:LP_BP0
 *
 * Not documented
 */


/**
 * \brief LP base page advertised abilities 15-0
 *
 * \details
 * Register: \a IP_KRANEG:LP_BP0:LP_BP0
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LP_BP0(target)        VTSS_IOREG(target,0x13)

/**
 * \brief
 * LP advertised abilities D[15:0]
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LP_BP0 . ADV0
 */
#define  VTSS_F_IP_KRANEG_LP_BP0_ADV0(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LP_BP0_ADV0         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LP_BP0_ADV0(x)      VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a IP_KRANEG:LP_BP1
 *
 * Not documented
 */


/**
 * \brief LP base page advertised abilities 31-16
 *
 * \details
 * Register: \a IP_KRANEG:LP_BP1:LP_BP1
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LP_BP1(target)        VTSS_IOREG(target,0x14)

/**
 * \brief
 * LP advertised abilities D[31:16]
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LP_BP1 . ADV1
 */
#define  VTSS_F_IP_KRANEG_LP_BP1_ADV1(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LP_BP1_ADV1         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LP_BP1_ADV1(x)      VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a IP_KRANEG:LP_BP2
 *
 * Not documented
 */


/**
 * \brief LP base page advertised abilities 47-32
 *
 * \details
 * Register: \a IP_KRANEG:LP_BP2:LP_BP2
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LP_BP2(target)        VTSS_IOREG(target,0x15)

/**
 * \brief
 * LP advertised abilities D[47:32]
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LP_BP2 . ADV2
 */
#define  VTSS_F_IP_KRANEG_LP_BP2_ADV2(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LP_BP2_ADV2         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LP_BP2_ADV2(x)      VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a IP_KRANEG:LD_NP
 *
 * Local Device Next Page
 */


/**
 * \brief NxtPg transmit 15-0
 *
 * \details
 * Register: \a IP_KRANEG:LD_NP:LD_NP0
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LD_NP0(target)        VTSS_IOREG(target,0x16)

/**
 * \brief
 * Next page to transmit D[15:0]
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LD_NP0 . NP0
 */
#define  VTSS_F_IP_KRANEG_LD_NP0_NP0(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LD_NP0_NP0          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LD_NP0_NP0(x)       VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief NxtPg transmit 31-16
 *
 * \details
 * Register: \a IP_KRANEG:LD_NP:LD_NP1
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LD_NP1(target)        VTSS_IOREG(target,0x17)

/**
 * \brief
 * Next page to transmit D[31:16]
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LD_NP1 . NP1
 */
#define  VTSS_F_IP_KRANEG_LD_NP1_NP1(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LD_NP1_NP1          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LD_NP1_NP1(x)       VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief NxtPg transmit 47-32
 *
 * \details
 * Register: \a IP_KRANEG:LD_NP:LD_NP2
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LD_NP2(target)        VTSS_IOREG(target,0x18)

/**
 * \brief
 * Next page to transmit D[47:32]
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LD_NP2 . NP2
 */
#define  VTSS_F_IP_KRANEG_LD_NP2_NP2(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LD_NP2_NP2          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LD_NP2_NP2(x)       VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a IP_KRANEG:LP_NP
 *
 * Link Partner Next Page
 */


/**
 * \brief LP next page ability 15-0
 *
 * \details
 * Register: \a IP_KRANEG:LP_NP:LP_NP0
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LP_NP0(target)        VTSS_IOREG(target,0x19)

/**
 * \brief
 * LP next page D[15:0]
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LP_NP0 . NP0
 */
#define  VTSS_F_IP_KRANEG_LP_NP0_NP0(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LP_NP0_NP0          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LP_NP0_NP0(x)       VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LP next page ability 31-16
 *
 * \details
 * Register: \a IP_KRANEG:LP_NP:LP_NP1
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LP_NP1(target)        VTSS_IOREG(target,0x1a)

/**
 * \brief
 * LP next page D[31:16]
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LP_NP1 . NP1
 */
#define  VTSS_F_IP_KRANEG_LP_NP1_NP1(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LP_NP1_NP1          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LP_NP1_NP1(x)       VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LP next page ability 47-32
 *
 * \details
 * Register: \a IP_KRANEG:LP_NP:LP_NP2
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LP_NP2(target)        VTSS_IOREG(target,0x1b)

/**
 * \brief
 * LP next page D[47:32]
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LP_NP2 . NP2
 */
#define  VTSS_F_IP_KRANEG_LP_NP2_NP2(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_LP_NP2_NP2          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_LP_NP2_NP2(x)       VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a IP_KRANEG:BP_ETH_STS
 *
 * Not documented
 */


/**
 * \brief Backplane ethernet BASE-R status
 *
 * \details
 * Register: \a IP_KRANEG:BP_ETH_STS:BP_ETH_STS
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_BP_ETH_STS(target)    VTSS_IOREG(target,0x30)

/**
 * \brief
 * 5G-KR      negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_5G_KR
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_5G_KR(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_5G_KR  VTSS_BIT(15)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_5G_KR(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * 2.5G-KX    negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_2P5G_KX
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_2P5G_KX(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_2P5G_KX  VTSS_BIT(14)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_2P5G_KX(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * 25G-KR     negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_25G_KR
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_25G_KR(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_25G_KR  VTSS_BIT(13)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_25G_KR(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * 25G-KR-S   negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_25G_KR_S
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_25G_KR_S(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_25G_KR_S  VTSS_BIT(12)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_25G_KR_S(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * 100G-CR4   negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_100G_CR4
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_100G_CR4(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_100G_CR4  VTSS_BIT(11)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_100G_CR4(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * 100G-KR4   negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_100G_KR4
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_100G_KR4(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_100G_KR4  VTSS_BIT(10)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_100G_KR4(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * 100G-KP4   negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_100G_KP4
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_100G_KP4(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_100G_KP4  VTSS_BIT(9)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_100G_KP4(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * 100G-CR10  negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_100G_CR10
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_100G_CR10(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_100G_CR10  VTSS_BIT(8)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_100G_CR10(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * RS-FEC     negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_RS_FEC
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_RS_FEC(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_RS_FEC  VTSS_BIT(7)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_RS_FEC(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * 40G-CR4    negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_40G_CR4
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_40G_CR4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_40G_CR4  VTSS_BIT(6)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_40G_CR4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * 40G-KR4    negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_40G_KR4
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_40G_KR4(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_40G_KR4  VTSS_BIT(5)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_40G_KR4(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * BASE-R FEC negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_R_FEC
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_R_FEC(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_R_FEC  VTSS_BIT(4)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_R_FEC(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * 10G-KR     negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_10G_KR
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_10G_KR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_10G_KR  VTSS_BIT(3)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_10G_KR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * 10G-KX4    negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_10G_KX4
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_10G_KX4(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_10G_KX4  VTSS_BIT(2)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_10G_KX4(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * 1G-KX      negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_NEG_1G_KX
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_NEG_1G_KX(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_NEG_1G_KX  VTSS_BIT(1)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_1G_KX(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BP AN ability
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BP_ETH_STS . AN_BP_ABLE
 */
#define  VTSS_F_IP_KRANEG_BP_ETH_STS_AN_BP_ABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_IP_KRANEG_BP_ETH_STS_AN_BP_ABLE  VTSS_BIT(0)
#define  VTSS_X_IP_KRANEG_BP_ETH_STS_AN_BP_ABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a IP_KRANEG:AN_CFG1
 *
 * Not documented
 */


/**
 * \brief AN config 1
 *
 * \details
 * Register: \a IP_KRANEG:AN_CFG1:AN_CFG1
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_AN_CFG1(target)       VTSS_IOREG(target,0x1000)

/**
 * \brief
 * Enable 16-bit data input for 5G mode
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_CFG1 . RCV_16B_FOR_5G
 */
#define  VTSS_F_IP_KRANEG_AN_CFG1_RCV_16B_FOR_5G(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_IP_KRANEG_AN_CFG1_RCV_16B_FOR_5G  VTSS_BIT(14)
#define  VTSS_X_IP_KRANEG_AN_CFG1_RCV_16B_FOR_5G(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Clock divider value for timer clocks
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_CFG1 . TMR_DVDR
 */
#define  VTSS_F_IP_KRANEG_AN_CFG1_TMR_DVDR(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_IP_KRANEG_AN_CFG1_TMR_DVDR     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_IP_KRANEG_AN_CFG1_TMR_DVDR(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/**
 * \brief
 * Clear ABILITY_DETECT state counter
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_CFG1 . ABDET_CLR
 */
#define  VTSS_F_IP_KRANEG_AN_CFG1_ABDET_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_IP_KRANEG_AN_CFG1_ABDET_CLR   VTSS_BIT(9)
#define  VTSS_X_IP_KRANEG_AN_CFG1_ABDET_CLR(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Clear AN state machine history
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_CFG1 . AN_SM_HIST_CLR
 */
#define  VTSS_F_IP_KRANEG_AN_CFG1_AN_SM_HIST_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_IP_KRANEG_AN_CFG1_AN_SM_HIST_CLR  VTSS_BIT(8)
#define  VTSS_X_IP_KRANEG_AN_CFG1_AN_SM_HIST_CLR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Bypass training if 10G negotiated
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_CFG1 . TR_DISABLE
 */
#define  VTSS_F_IP_KRANEG_AN_CFG1_TR_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_IP_KRANEG_AN_CFG1_TR_DISABLE  VTSS_BIT(6)
#define  VTSS_X_IP_KRANEG_AN_CFG1_TR_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Select source of 10G sync signal (Used for HCD Technology PCS using
 * 64b66b Encoding Eg. 10GBaseKR, 5GBaseKR, 25GBaseKR etc.,)
 *
 * \details
 * 0: KR internal
 * 1: External

 *
 * Field: ::VTSS_IP_KRANEG_AN_CFG1 . SYNC10G_SEL
 */
#define  VTSS_F_IP_KRANEG_AN_CFG1_SYNC10G_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_IP_KRANEG_AN_CFG1_SYNC10G_SEL  VTSS_BIT(5)
#define  VTSS_X_IP_KRANEG_AN_CFG1_SYNC10G_SEL(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Select source of 1G sync signal (Used for HCD Technology PCS using 8b10b
 * Encoding. Eg. 1000BaseX, 10GBaseKX4, 2.5GBaseX etc.,)
 *
 * \details
 * 0: KR internal
 * 1: External

 *
 * Field: ::VTSS_IP_KRANEG_AN_CFG1 . SYNC8B10B_SEL
 */
#define  VTSS_F_IP_KRANEG_AN_CFG1_SYNC8B10B_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_IP_KRANEG_AN_CFG1_SYNC8B10B_SEL  VTSS_BIT(4)
#define  VTSS_X_IP_KRANEG_AN_CFG1_SYNC8B10B_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * rate setting
 *
 * \details
 * 1 : 100G-CR4
 * 2 : 100G-KR4
 * 3 : 100G-KP4
 * 4 : 100G-CR10
 * 5 : 40G-CR4
 * 6 : 40G-KR4
 * 7 : 25G-KR
 * 8 : 25G-KR-S
 * 9 : 10G-KR
 * 10 : 10G-KX4
 * 11 : 5G-KR
 * 12 : 2.5G-KX
 * 13 : 1G-KX

 *
 * Field: ::VTSS_IP_KRANEG_AN_CFG1 . RATE
 */
#define  VTSS_F_IP_KRANEG_AN_CFG1_RATE(x)     VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_IP_KRANEG_AN_CFG1_RATE        VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_IP_KRANEG_AN_CFG1_RATE(x)     VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a IP_KRANEG:BL_TMR
 *
 * Not documented
 */


/**
 * \brief AN break_link timer
 *
 * \details
 * Register: \a IP_KRANEG:BL_TMR:BL_TMR
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_BL_TMR(target)        VTSS_IOREG(target,0x1010)

/**
 * \brief
 * break_link_timer setting. Default value corresponds to 70ms for a System
 * clock of 1.6ns and Timer Divider of 4.
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_BL_TMR . TMR
 */
#define  VTSS_F_IP_KRANEG_BL_TMR_TMR(x)       (x)
#define  VTSS_M_IP_KRANEG_BL_TMR_TMR          0xffffffff
#define  VTSS_X_IP_KRANEG_BL_TMR_TMR(x)       (x)

/**
 * Register Group: \a IP_KRANEG:AW_TMR
 *
 * Not documented
 */


/**
 * \brief AN aneg_wait timer
 *
 * \details
 * Register: \a IP_KRANEG:AW_TMR:AW_TMR
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_AW_TMR(target)        VTSS_IOREG(target,0x1012)

/**
 * \brief
 * an_wait_timer setting.Default value corresponds to 38ms for system clock
 * period of 1.6ns and timer divider of 4.
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AW_TMR . TMR
 */
#define  VTSS_F_IP_KRANEG_AW_TMR_TMR(x)       (x)
#define  VTSS_M_IP_KRANEG_AW_TMR_TMR          0xffffffff
#define  VTSS_X_IP_KRANEG_AW_TMR_TMR(x)       (x)

/**
 * Register Group: \a IP_KRANEG:LFLONG_TMR
 *
 * Not documented
 */


/**
 * \brief AN link_fail_inhibit timer
 *
 * \details
 * Register: \a IP_KRANEG:LFLONG_TMR:LFLONG_TMR
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LFLONG_TMR(target)    VTSS_IOREG(target,0x1014)

/**
 * \brief
 * 10g link_fail_inhibit_timer setting. Default value is set to 50ms for a
 * system clock period of 1.6ns and a timer divider value of 4. Long timer
 * and short timer are set to same values as there is a training timer in
 * TRAIN state which takes care of the training time of 500ms.
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LFLONG_TMR . TMR
 */
#define  VTSS_F_IP_KRANEG_LFLONG_TMR_TMR(x)   (x)
#define  VTSS_M_IP_KRANEG_LFLONG_TMR_TMR      0xffffffff
#define  VTSS_X_IP_KRANEG_LFLONG_TMR_TMR(x)   (x)

/**
 * Register Group: \a IP_KRANEG:LFSHORT_TMR
 *
 * Not documented
 */


/**
 * \brief AN link_fail_inhibit_short timer
 *
 * \details
 * Register: \a IP_KRANEG:LFSHORT_TMR:LFSHORT_TMR
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LFSHORT_TMR(target)   VTSS_IOREG(target,0x1016)

/**
 * \brief
 * 1g link_fail_inhibit_timer settingDefault value is set to 50ms for a
 * system clock period of 1.6ns and a timer divider value of 4.
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LFSHORT_TMR . TMR
 */
#define  VTSS_F_IP_KRANEG_LFSHORT_TMR_TMR(x)  (x)
#define  VTSS_M_IP_KRANEG_LFSHORT_TMR_TMR     0xffffffff
#define  VTSS_X_IP_KRANEG_LFSHORT_TMR_TMR(x)  (x)

/**
 * Register Group: \a IP_KRANEG:LP_TMR
 *
 * Not documented
 */


/**
 * \brief AN link_pass_inhibit timer
 *
 * \details
 * Register: \a IP_KRANEG:LP_TMR:LP_TMR
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_LP_TMR(target)        VTSS_IOREG(target,0x1018)

/**
 * \brief
 * link_pass_inhibit_timer setting
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_LP_TMR . TMR
 */
#define  VTSS_F_IP_KRANEG_LP_TMR_TMR(x)       (x)
#define  VTSS_M_IP_KRANEG_LP_TMR_TMR          0xffffffff
#define  VTSS_X_IP_KRANEG_LP_TMR_TMR(x)       (x)

/**
 * Register Group: \a IP_KRANEG:TR_TMR
 *
 * Not documented
 */


/**
 * \brief AN training state timer
 *
 * \details
 * Register: \a IP_KRANEG:TR_TMR:TR_TMR
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_TR_TMR(target)        VTSS_IOREG(target,0x101a)

/**
 * \brief
 * training_state_timer settingDefault value corresponds to 500ms for a
 * system clock period of 1.6ns and a timer divider value of 4.
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_TR_TMR . TMR
 */
#define  VTSS_F_IP_KRANEG_TR_TMR_TMR(x)       (x)
#define  VTSS_M_IP_KRANEG_TR_TMR_TMR          0xffffffff
#define  VTSS_X_IP_KRANEG_TR_TMR_TMR(x)       (x)

/**
 * Register Group: \a IP_KRANEG:PD_TMR
 *
 * Not documented
 */


/**
 * \brief AN page_detect timer
 *
 * \details
 * Register: \a IP_KRANEG:PD_TMR:PD_TMR
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_PD_TMR(target)        VTSS_IOREG(target,0x101c)

/**
 * \brief
 * page_detect_timer setting. Time the state machine stays in ABILITY
 * DETECT for ability match before entering into RATE_DETECT state to
 * perform parallel detection.Default value corresponds to 500ms for system
 * clock period of 1.6ns and a timer divider value of 4.
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_PD_TMR . TMR
 */
#define  VTSS_F_IP_KRANEG_PD_TMR_TMR(x)       (x)
#define  VTSS_M_IP_KRANEG_PD_TMR_TMR          0xffffffff
#define  VTSS_X_IP_KRANEG_PD_TMR_TMR(x)       (x)

/**
 * Register Group: \a IP_KRANEG:WT_TMR
 *
 * Not documented
 */


/**
 * \brief training wait_timer
 *
 * \details
 * Register: \a IP_KRANEG:WT_TMR:WT_TMR
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_WT_TMR(target)        VTSS_IOREG(target,0x1024)

/**
 * \brief
 * wait_timer for training.The default value corresponds to a period of
 * around 200 10GBaseKR Training frames for a system clock period of 1.6ns
 * and a timer divider value of 4.This value needs to be reconfigured to an
 * appropriate value by Firmware for HCD (using KR Link Training) other
 * than 10GBaseKR
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_WT_TMR . TMR
 */
#define  VTSS_F_IP_KRANEG_WT_TMR_TMR(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_IP_KRANEG_WT_TMR_TMR          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_IP_KRANEG_WT_TMR_TMR(x)       VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a IP_KRANEG:MW_TMR
 *
 * Not documented
 */


/**
 * \brief training maxwait_timer
 *
 * \details
 * Register: \a IP_KRANEG:MW_TMR:MW_TMR
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_MW_TMR(target)        VTSS_IOREG(target,0x1026)

/**
 * \brief
 * maxwait_timer for trainingDefault value corresponds to 500ms for a
 * system clock period of 1.6ns and a Timer Divider value of 4.
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_MW_TMR . TMR
 */
#define  VTSS_F_IP_KRANEG_MW_TMR_TMR(x)       (x)
#define  VTSS_M_IP_KRANEG_MW_TMR_TMR          0xffffffff
#define  VTSS_X_IP_KRANEG_MW_TMR_TMR(x)       (x)

/**
 * Register Group: \a IP_KRANEG:GEN0_TMR
 *
 * Not documented
 */


/**
 * \brief generic_0 timer
 *
 * \details
 * Register: \a IP_KRANEG:GEN0_TMR:GEN0_TMR
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_GEN0_TMR(target)      VTSS_IOREG(target,0x1028)

/**
 * \brief
 * generic timer
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_GEN0_TMR . TMR
 */
#define  VTSS_F_IP_KRANEG_GEN0_TMR_TMR(x)     (x)
#define  VTSS_M_IP_KRANEG_GEN0_TMR_TMR        0xffffffff
#define  VTSS_X_IP_KRANEG_GEN0_TMR_TMR(x)     (x)

/**
 * Register Group: \a IP_KRANEG:GEN1_TMR
 *
 * Not documented
 */


/**
 * \brief generic_1 timer
 *
 * \details
 * Register: \a IP_KRANEG:GEN1_TMR:GEN1_TMR
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_GEN1_TMR(target)      VTSS_IOREG(target,0x102a)

/**
 * \brief
 * generic timer
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_GEN1_TMR . TMR
 */
#define  VTSS_F_IP_KRANEG_GEN1_TMR_TMR(x)     (x)
#define  VTSS_M_IP_KRANEG_GEN1_TMR_TMR        0xffffffff
#define  VTSS_X_IP_KRANEG_GEN1_TMR_TMR(x)     (x)

/**
 * Register Group: \a IP_KRANEG:AN_HIST
 *
 * Not documented
 */


/**
 * \brief AN arb state mach history
 *
 * \details
 * Register: \a IP_KRANEG:AN_HIST:AN_HIST
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_AN_HIST(target)       VTSS_IOREG(target,0x1030)

/**
 * \brief
 * AN state machine history. Bits are set for each of the states entered.
 *
 * \details
 * Bit 0   :   AN_ENABLE
 *  Bit 1   :	XMT_DISABLE
 *  Bit 2   :	ABILITY_DET
 *  Bit 3   :	ACK_DET
 *  Bit 4   :	COMPLETE_ACK
 *  Bit 5   :	TRAIN
 *  Bit 6   :	AN_GOOD_CHK
 *  Bit 7   :	AN_GOOD
 *  Bit 8   :	RATE_DET
 *  Bit 11  :	LINK_STAT_CHK
 *  Bit 12  :	PARLL_DET_FAULT
 *  Bit 13  :	WAIT_RATE_DONE
 *  Bit 14  :	NXTPG_WAIT
 *
 * Field: ::VTSS_IP_KRANEG_AN_HIST . AN_SM_HIST
 */
#define  VTSS_F_IP_KRANEG_AN_HIST_AN_SM_HIST(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_IP_KRANEG_AN_HIST_AN_SM_HIST     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_IP_KRANEG_AN_HIST_AN_SM_HIST(x)  VTSS_EXTRACT_BITFIELD(x,0,15)

/**
 * Register Group: \a IP_KRANEG:AN_SM
 *
 * Not documented
 */


/**
 * \brief AN arb state machine
 *
 * \details
 * Register: \a IP_KRANEG:AN_SM:AN_SM
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_AN_SM(target)         VTSS_IOREG(target,0x1031)

/**
 * \brief
 * ABILITY_DETECT state counter
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_SM . ABDET_CNT
 */
#define  VTSS_F_IP_KRANEG_AN_SM_ABDET_CNT(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_IP_KRANEG_AN_SM_ABDET_CNT     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_IP_KRANEG_AN_SM_ABDET_CNT(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * AN state machine State.
 *
 * \details
 * 4'd0   :   AN_ENABLE
 *  4'd1   :   XMT_DISABLE
 *  4'd2   :   ABILITY_DET
 *  4'd3   :   ACK_DET
 *  4'd4   :   COMPLETE_ACK
 *  4'd5   :   TRAIN
 *  4'd6   :   AN_GOOD_CHK
 *  4'd7   :   AN_GOOD
 *  4'd8   :   RATE_DET
 *  4'd11  :   LINK_STAT_CHK
 *  4'd12  :   PARLL_DET_FAULT
 *  4'd13  :   WAIT_RATE_DONE
 *  4'd14  :   NXTPG_WAIT
 *
 * Field: ::VTSS_IP_KRANEG_AN_SM . AN_SM
 */
#define  VTSS_F_IP_KRANEG_AN_SM_AN_SM(x)      VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_IP_KRANEG_AN_SM_AN_SM         VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_IP_KRANEG_AN_SM_AN_SM(x)      VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a IP_KRANEG:AN_STS1
 *
 * Not documented
 */


/**
 * \brief AN status 1
 *
 * \details
 * Register: \a IP_KRANEG:AN_STS1:AN_STS1
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_AN_STS1(target)       VTSS_IOREG(target,0x1032)

/**
 * \brief
 * AN or Training frames are being exchanged
 *
 * \details
 * 0: External mux should switch to egress traffic
 * 1: External mux should switch to KR output

 *
 * Field: ::VTSS_IP_KRANEG_AN_STS1 . KR_ACTV
 */
#define  VTSS_F_IP_KRANEG_AN_STS1_KR_ACTV(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_IP_KRANEG_AN_STS1_KR_ACTV     VTSS_BIT(8)
#define  VTSS_X_IP_KRANEG_AN_STS1_KR_ACTV(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * 1G or 3G sync status of local detector
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_STS1 . SYNC8B10B
 */
#define  VTSS_F_IP_KRANEG_AN_STS1_SYNC8B10B(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_IP_KRANEG_AN_STS1_SYNC8B10B   VTSS_BIT(7)
#define  VTSS_X_IP_KRANEG_AN_STS1_SYNC8B10B(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * 10G sync status of local detector
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_STS1 . SYNC10G
 */
#define  VTSS_F_IP_KRANEG_AN_STS1_SYNC10G(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_IP_KRANEG_AN_STS1_SYNC10G     VTSS_BIT(6)
#define  VTSS_X_IP_KRANEG_AN_STS1_SYNC10G(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Nonce match (LH)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_STS1 . NONCE_MATCH
 */
#define  VTSS_F_IP_KRANEG_AN_STS1_NONCE_MATCH(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_IP_KRANEG_AN_STS1_NONCE_MATCH  VTSS_BIT(5)
#define  VTSS_X_IP_KRANEG_AN_STS1_NONCE_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Incompatible link (LH)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_AN_STS1 . INCP_LINK
 */
#define  VTSS_F_IP_KRANEG_AN_STS1_INCP_LINK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_IP_KRANEG_AN_STS1_INCP_LINK   VTSS_BIT(4)
#define  VTSS_X_IP_KRANEG_AN_STS1_INCP_LINK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Negotiated HCD
 *
 * \details
 * 1 : 100G-CR4
 * 2 : 100G-KR4
 * 3 : 100G-KP4
 * 4 : 100G-CR10
 * 5 : 40G-CR4
 * 6 : 40G-KR4
 * 7 : 25G-KR
 * 8 : 25G-KR-S
 * 9 : 10G-KR
 * 10 : 10G-KX4
 * 11 : 5G-KR
 * 12 : 2.5G-KX
 * 13 : 1G-KX

 *
 * Field: ::VTSS_IP_KRANEG_AN_STS1 . LINK_HCD
 */
#define  VTSS_F_IP_KRANEG_AN_STS1_LINK_HCD(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_IP_KRANEG_AN_STS1_LINK_HCD     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_IP_KRANEG_AN_STS1_LINK_HCD(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a IP_KRANEG:FW_MSG
 *
 * Not documented
 */


/**
 * \brief Firmware SC messages
 *
 * \details
 * Register: \a IP_KRANEG:FW_MSG:FW_MSG
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_FW_MSG(target)        VTSS_IOREG(target,0x1040)

/**
 * \brief
 * Indicates that training has completed (SC)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_FW_MSG . TR_DONE
 */
#define  VTSS_F_IP_KRANEG_FW_MSG_TR_DONE(x)   VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_IP_KRANEG_FW_MSG_TR_DONE      VTSS_BIT(4)
#define  VTSS_X_IP_KRANEG_FW_MSG_TR_DONE(x)   VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Indicates that LDCOEF is stable (SC)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_FW_MSG . LDCOEF_VLD
 */
#define  VTSS_F_IP_KRANEG_FW_MSG_LDCOEF_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_IP_KRANEG_FW_MSG_LDCOEF_VLD   VTSS_BIT(3)
#define  VTSS_X_IP_KRANEG_FW_MSG_LDCOEF_VLD(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Indicates that LDSTAT is stable (SC)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_FW_MSG . LDSTAT_VLD
 */
#define  VTSS_F_IP_KRANEG_FW_MSG_LDSTAT_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_IP_KRANEG_FW_MSG_LDSTAT_VLD   VTSS_BIT(2)
#define  VTSS_X_IP_KRANEG_FW_MSG_LDSTAT_VLD(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Indicates that next_page is loaded (SC)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_FW_MSG . NP_LOADED
 */
#define  VTSS_F_IP_KRANEG_FW_MSG_NP_LOADED(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_IP_KRANEG_FW_MSG_NP_LOADED    VTSS_BIT(1)
#define  VTSS_X_IP_KRANEG_FW_MSG_NP_LOADED(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * rate setting is done (sc)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_FW_MSG . RATE_DONE
 */
#define  VTSS_F_IP_KRANEG_FW_MSG_RATE_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_IP_KRANEG_FW_MSG_RATE_DONE    VTSS_BIT(0)
#define  VTSS_X_IP_KRANEG_FW_MSG_RATE_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a IP_KRANEG:FW_REQ
 *
 * Not documented
 */


/**
 * \brief Firmware SC request
 *
 * \details
 * Register: \a IP_KRANEG:FW_REQ:FW_REQ
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_FW_REQ(target)        VTSS_IOREG(target,0x1041)

/**
 * \brief
 * Start BER checker (SC)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_FW_REQ . BER_EN
 */
#define  VTSS_F_IP_KRANEG_FW_REQ_BER_EN(x)    VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_IP_KRANEG_FW_REQ_BER_EN       VTSS_BIT(12)
#define  VTSS_X_IP_KRANEG_FW_REQ_BER_EN(x)    VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * start generic timer 1 (SC)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_FW_REQ . GEN1_TMR_START
 */
#define  VTSS_F_IP_KRANEG_FW_REQ_GEN1_TMR_START(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_IP_KRANEG_FW_REQ_GEN1_TMR_START  VTSS_BIT(11)
#define  VTSS_X_IP_KRANEG_FW_REQ_GEN1_TMR_START(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * start generic timer 0 (SC)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_FW_REQ . GEN0_TMR_START
 */
#define  VTSS_F_IP_KRANEG_FW_REQ_GEN0_TMR_START(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_IP_KRANEG_FW_REQ_GEN0_TMR_START  VTSS_BIT(10)
#define  VTSS_X_IP_KRANEG_FW_REQ_GEN0_TMR_START(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * start wait timer (SC)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_FW_REQ . WT_START
 */
#define  VTSS_F_IP_KRANEG_FW_REQ_WT_START(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_IP_KRANEG_FW_REQ_WT_START     VTSS_BIT(9)
#define  VTSS_X_IP_KRANEG_FW_REQ_WT_START(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * start maxwait timer (SC)
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_FW_REQ . MW_START
 */
#define  VTSS_F_IP_KRANEG_FW_REQ_MW_START(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_IP_KRANEG_FW_REQ_MW_START     VTSS_BIT(8)
#define  VTSS_X_IP_KRANEG_FW_REQ_MW_START(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * Register Group: \a IP_KRANEG:IRQ_VEC
 *
 * Not documented
 */


/**
 * \brief interrupt vector. All sticky
 *
 * \details
 * Register: \a IP_KRANEG:IRQ_VEC:IRQ_VEC
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_IRQ_VEC(target)       VTSS_IOREG(target,0x1042)

/**
 * \brief
 * interrupt for kr_active toggle
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . KR_ACTV
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_KR_ACTV(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_KR_ACTV     VTSS_BIT(29)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_KR_ACTV(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * interrupt for new LP status report
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . LPSVALID
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_LPSVALID(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_LPSVALID    VTSS_BIT(28)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_LPSVALID(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * interrupt for new LP coeff update
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . LPCVALID
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_LPCVALID(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_LPCVALID    VTSS_BIT(27)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_LPCVALID(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * interrupt for wait timer done
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . WT_DONE
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_WT_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_WT_DONE     VTSS_BIT(26)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_WT_DONE(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * interrupt for maxwait timer done
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . MW_DONE
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_MW_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_MW_DONE     VTSS_BIT(25)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_MW_DONE(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * interrupt for ber_busy = 0
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . BER_BUSY_0
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_BER_BUSY_0(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_BER_BUSY_0  VTSS_BIT(24)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_BER_BUSY_0(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * interrupt for ber_busy = 1
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . BER_BUSY_1
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_BER_BUSY_1(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_BER_BUSY_1  VTSS_BIT(23)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_BER_BUSY_1(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * interrupt for rem_ready = 0
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . REM_RDY_0
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_REM_RDY_0(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_REM_RDY_0   VTSS_BIT(22)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_REM_RDY_0(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * interrupt for rem_ready = 1
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . REM_RDY_1
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_REM_RDY_1(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_REM_RDY_1   VTSS_BIT(21)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_REM_RDY_1(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * interrupt for frlock = 0
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . FRLOCK_0
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_FRLOCK_0(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_FRLOCK_0    VTSS_BIT(20)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_FRLOCK_0(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * interrupt for frlock = 1
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . FRLOCK_1
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_FRLOCK_1(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_FRLOCK_1    VTSS_BIT(19)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_FRLOCK_1(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * interrupt for dme_viol = 0
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . DME_VIOL_0
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_DME_VIOL_0(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_DME_VIOL_0  VTSS_BIT(18)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_DME_VIOL_0(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * interrupt for dme_viol = 1
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . DME_VIOL_1
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_DME_VIOL_1(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_DME_VIOL_1  VTSS_BIT(17)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_DME_VIOL_1(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * interrupt for AN_SM = XMIT_DISABLE
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . AN_XMIT_DISABLE
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_AN_XMIT_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_AN_XMIT_DISABLE  VTSS_BIT(16)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_AN_XMIT_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * interrupt for AN_SM = TRAIN
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . AN_TRAIN
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_AN_TRAIN(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_AN_TRAIN    VTSS_BIT(15)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_AN_TRAIN(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * interrupt for AN_SM = RATE_DET
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . AN_RATE_DET
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_AN_RATE_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_AN_RATE_DET  VTSS_BIT(14)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_AN_RATE_DET(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * interrupt for AN_SM = COMPLETE_ACK
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . CMPL_ACK
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_CMPL_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_CMPL_ACK    VTSS_BIT(13)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_CMPL_ACK(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * interrupt for AN_SM = AN_GOOD
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . AN_GOOD
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_AN_GOOD(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_AN_GOOD     VTSS_BIT(12)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_AN_GOOD(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * interrupt for AN link fail
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . LINK_FAIL
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_LINK_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_LINK_FAIL   VTSS_BIT(11)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_LINK_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * interrupt for AN ABILITY_DETECT fail
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . ABD_FAIL
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_ABD_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_ABD_FAIL    VTSS_BIT(10)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_ABD_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * interrupt for AN ACK_DETECT fail
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . ACK_FAIL
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_ACK_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_ACK_FAIL    VTSS_BIT(9)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_ACK_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * interrupt for AN NEXT_PAGE fail
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . NP_FAIL
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_NP_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_NP_FAIL     VTSS_BIT(8)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_NP_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * interrupt for AN LP NEXT_PAGE received
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . NP_RX
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_NP_RX(x)    VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_NP_RX       VTSS_BIT(7)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_NP_RX(x)    VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * interrupt for AN incompatible link
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . INCP_LINK
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_INCP_LINK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_INCP_LINK   VTSS_BIT(6)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_INCP_LINK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * interrupt for gen0 timer done
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . GEN0_DONE
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_GEN0_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_GEN0_DONE   VTSS_BIT(5)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_GEN0_DONE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * interrupt for gen1 timer done
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . GEN1_DONE
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_GEN1_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_GEN1_DONE   VTSS_BIT(4)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_GEN1_DONE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * interrupt for rate change request
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_VEC . AN_RATE
 */
#define  VTSS_F_IP_KRANEG_IRQ_VEC_AN_RATE(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_IP_KRANEG_IRQ_VEC_AN_RATE     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_IP_KRANEG_IRQ_VEC_AN_RATE(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a IP_KRANEG:IRQ_MASK
 *
 * Not documented
 */


/**
 * \brief interrupt mask
 *
 * \details
 * Register: \a IP_KRANEG:IRQ_MASK:IRQ_MASK
 *
 * @param target A \a ::vtss_target_IP_KRANEG_e target
 */
#define VTSS_IP_KRANEG_IRQ_MASK(target)      VTSS_IOREG(target,0x1043)

/**
 * \brief
 * interrupt mask for kr_active toggle
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . KR_ACTV
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_KR_ACTV(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_KR_ACTV    VTSS_BIT(29)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_KR_ACTV(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * interrupt mask for new LP status report
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . LPSVALID
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_LPSVALID(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_LPSVALID   VTSS_BIT(28)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_LPSVALID(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * interrupt mask for new LP coeff update
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . LPCVALID
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_LPCVALID(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_LPCVALID   VTSS_BIT(27)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_LPCVALID(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * interrupt mask for wait timer done
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . WT_DONE
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_WT_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_WT_DONE    VTSS_BIT(26)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_WT_DONE(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * interrupt mask for maxwait timer done
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . MW_DONE
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_MW_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_MW_DONE    VTSS_BIT(25)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_MW_DONE(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * interrupt mask for ber_busy = 0
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . BER_BUSY_0
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_BER_BUSY_0(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_BER_BUSY_0  VTSS_BIT(24)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_BER_BUSY_0(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * interrupt mask for ber_busy = 1
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . BER_BUSY_1
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_BER_BUSY_1(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_BER_BUSY_1  VTSS_BIT(23)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_BER_BUSY_1(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * interrupt mask for rem_ready = 0
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . REM_RDY_0
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_REM_RDY_0(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_REM_RDY_0  VTSS_BIT(22)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_REM_RDY_0(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * interrupt mask for rem_ready = 1
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . REM_RDY_1
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_REM_RDY_1(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_REM_RDY_1  VTSS_BIT(21)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_REM_RDY_1(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * interrupt mask for frlock = 0
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . FRLOCK_0
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_FRLOCK_0(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_FRLOCK_0   VTSS_BIT(20)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_FRLOCK_0(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * interrupt mask for frlock = 1
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . FRLOCK_1
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_FRLOCK_1(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_FRLOCK_1   VTSS_BIT(19)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_FRLOCK_1(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * interrupt mask for dme_viol = 0
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . DME_VIOL_0
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_DME_VIOL_0(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_DME_VIOL_0  VTSS_BIT(18)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_DME_VIOL_0(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * interrupt mask for dme_viol = 1
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . DME_VIOL_1
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_DME_VIOL_1(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_DME_VIOL_1  VTSS_BIT(17)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_DME_VIOL_1(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * interrupt mask for AN_SM = XMIT_DISABLE
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . AN_XMIT_DISABLE
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_AN_XMIT_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_AN_XMIT_DISABLE  VTSS_BIT(16)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_AN_XMIT_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * interrupt mask for AN_SM = TRAIN
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . AN_TRAIN
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_AN_TRAIN(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_AN_TRAIN   VTSS_BIT(15)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_AN_TRAIN(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * interrupt mask for AN_SM = RATE_DET
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . AN_RATE_DET
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_AN_RATE_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_AN_RATE_DET  VTSS_BIT(14)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_AN_RATE_DET(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * interrupt mask for AN_SM = COMPLETE_ACK
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . CMPL_ACK
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_CMPL_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_CMPL_ACK   VTSS_BIT(13)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_CMPL_ACK(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * interrupt mask for AN_SM = AN_GOOD
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . AN_GOOD
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_AN_GOOD(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_AN_GOOD    VTSS_BIT(12)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_AN_GOOD(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * interrupt mask for AN link fail
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . LINK_FAIL
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_LINK_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_LINK_FAIL  VTSS_BIT(11)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_LINK_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * interrupt mask for AN ABILITY_DETECT fail
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . ABD_FAIL
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_ABD_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_ABD_FAIL   VTSS_BIT(10)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_ABD_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * interrupt mask for AN ACK_DETECT fail
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . ACK_FAIL
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_ACK_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_ACK_FAIL   VTSS_BIT(9)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_ACK_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * interrupt mask for AN NEXT_PAGE fail
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . NP_FAIL
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_NP_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_NP_FAIL    VTSS_BIT(8)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_NP_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * interrupt mask for AN LP NEXT_PAGE received
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . NP_RX
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_NP_RX(x)   VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_NP_RX      VTSS_BIT(7)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_NP_RX(x)   VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * interrupt mask for AN incompatible link
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . INCP_LINK
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_INCP_LINK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_INCP_LINK  VTSS_BIT(6)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_INCP_LINK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * interrupt mask for gen0 timer done
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . GEN0_DONE
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_GEN0_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_GEN0_DONE  VTSS_BIT(5)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_GEN0_DONE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * interrupt mask for gen1 timer done
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . GEN1_DONE
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_GEN1_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_GEN1_DONE  VTSS_BIT(4)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_GEN1_DONE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * interrupt mask rate change request
 *
 * \details
 * Field: ::VTSS_IP_KRANEG_IRQ_MASK . AN_RATE
 */
#define  VTSS_F_IP_KRANEG_IRQ_MASK_AN_RATE(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_IP_KRANEG_IRQ_MASK_AN_RATE     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_IP_KRANEG_IRQ_MASK_AN_RATE(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


#endif /* _VTSS_LAGUNA_REGS_IP_KRANEG_H_ */
