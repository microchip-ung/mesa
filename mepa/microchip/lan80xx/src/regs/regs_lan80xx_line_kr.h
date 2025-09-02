// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN80XX_MALIBU25G_REGS_LINE_KR_H_
#define LAN80XX_MALIBU25G_REGS_LINE_KR_H_

#include "regs_lan80xx_common.h"

/***********************************************************************
 *
 * Target: \a LINE_KR
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a LINE_KR:KR_PMD_CTRL
 *
 * 10GBASE-KR PMD Control register
 */


/**
 * \brief KR PMD control
 *
 * \details
 * Register: \a LINE_KR:KR_PMD_CTRL:KR_PMD_CTRL
 */
#define LAN80XX_LINE_KR_KR_PMD_CTRL                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x96))

/**
 * \brief
 * Training enable
 *
 * \details
 * 1: Enable KR start-up protocol
 * 0: Disable KR start-up protocol

 *
 * Field: ::LAN80XX_LINE_KR_KR_PMD_CTRL . TR_ENABLE
 */
#define  LAN80XX_F_LINE_KR_KR_PMD_CTRL_TR_ENABLE(x)                                                 (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_KR_KR_PMD_CTRL_TR_ENABLE                                                    (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_KR_KR_PMD_CTRL_TR_ENABLE(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Restart training (Self Clear)
 *
 * \details
 * 1: Reset KR start-up protocol
 * 0: Normal operation

 *
 * Field: ::LAN80XX_LINE_KR_KR_PMD_CTRL . TR_RESTART
 */
#define  LAN80XX_F_LINE_KR_KR_PMD_CTRL_TR_RESTART(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_KR_KR_PMD_CTRL_TR_RESTART                                                   (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_KR_KR_PMD_CTRL_TR_RESTART(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a LINE_KR:KR_PMD_STS
 *
 * 10GBASE-KR PMD status register
 */


/**
 * \brief KR PMD status
 *
 * \details
 * Register: \a LINE_KR:KR_PMD_STS:KR_PMD_STS
 */
#define LAN80XX_LINE_KR_KR_PMD_STS                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x97))

/**
 * \brief
 * Training failure
 *
 * \details
 * 1: Training failure has been detected
 * 0: Training failure has not been detected

 *
 * Field: ::LAN80XX_LINE_KR_KR_PMD_STS . TR_FAIL
 */
#define  LAN80XX_F_LINE_KR_KR_PMD_STS_TR_FAIL(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_KR_KR_PMD_STS_TR_FAIL                                                       (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_KR_KR_PMD_STS_TR_FAIL(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Startup protocol status
 *
 * \details
 * 1: Start-up protocol in progress
 * 0: Start-up protocol complete

 *
 * Field: ::LAN80XX_LINE_KR_KR_PMD_STS . STPROT
 */
#define  LAN80XX_F_LINE_KR_KR_PMD_STS_STPROT(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_KR_KR_PMD_STS_STPROT                                                        (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_KR_KR_PMD_STS_STPROT(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Frame lock
 *
 * \details
 * 1: Training frame delineation detected
 * 0: Training frame delineation not detected

 *
 * Field: ::LAN80XX_LINE_KR_KR_PMD_STS . FRLOCK
 */
#define  LAN80XX_F_LINE_KR_KR_PMD_STS_FRLOCK(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_KR_KR_PMD_STS_FRLOCK                                                        (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_KR_KR_PMD_STS_FRLOCK(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Receiver status
 *
 * \details
 * 1: Receiver trained and ready to receive data
 * 0: Receiver training

 *
 * Field: ::LAN80XX_LINE_KR_KR_PMD_STS . RCVR_RDY
 */
#define  LAN80XX_F_LINE_KR_KR_PMD_STS_RCVR_RDY(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_KR_KR_PMD_STS_RCVR_RDY                                                      (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_KR_KR_PMD_STS_RCVR_RDY(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a LINE_KR:LP_COEF_UPD
 *
 * BASE-R LP coefficient register
 */


/**
 * \brief KR LP coefficient update
 *
 * \details
 * Register: \a LINE_KR:LP_COEF_UPD:LP_COEF_UPD
 */
#define LAN80XX_LINE_KR_LP_COEF_UPD                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x98))

/**
 * \brief
 * Received coefficient update field
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LP_COEF_UPD . LPCOEF
 */
#define  LAN80XX_F_LINE_KR_LP_COEF_UPD_LPCOEF(x)                                                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LP_COEF_UPD_LPCOEF                                                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LP_COEF_UPD_LPCOEF(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:LP_STS_RPT
 *
 * BASE-R LP status register
 */


/**
 * \brief KR LP status report
 *
 * \details
 * Register: \a LINE_KR:LP_STS_RPT:LP_STS_RPT
 */
#define LAN80XX_LINE_KR_LP_STS_RPT                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x99))

/**
 * \brief
 * Received status report field
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LP_STS_RPT . LPSTAT
 */
#define  LAN80XX_F_LINE_KR_LP_STS_RPT_LPSTAT(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LP_STS_RPT_LPSTAT                                                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LP_STS_RPT_LPSTAT(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:LD_COEF_UPD
 *
 * BASE-R LD coefficient register
 */


/**
 * \brief KR LD coefficient update
 *
 * \details
 * Register: \a LINE_KR:LD_COEF_UPD:LD_COEF_UPD
 */
#define LAN80XX_LINE_KR_LD_COEF_UPD                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x9a))

/**
 * \brief
 * Transmitted coefficient update field
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LD_COEF_UPD . LDCOEF
 */
#define  LAN80XX_F_LINE_KR_LD_COEF_UPD_LDCOEF(x)                                                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LD_COEF_UPD_LDCOEF                                                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LD_COEF_UPD_LDCOEF(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:LD_STS_RPT
 *
 * BASE-R LD status register
 */


/**
 * \brief KR LD status report
 *
 * \details
 * Register: \a LINE_KR:LD_STS_RPT:LD_STS_RPT
 */
#define LAN80XX_LINE_KR_LD_STS_RPT                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x9b))

/**
 * \brief
 * Transmitted status report field
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LD_STS_RPT . LDSTAT
 */
#define  LAN80XX_F_LINE_KR_LD_STS_RPT_LDSTAT(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LD_STS_RPT_LDSTAT                                                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LD_STS_RPT_LDSTAT(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:CLK_EN
 *
 * PMD Vendor Clock Control register
 */


/**
 * \brief clock enable
 *
 * \details
 * Register: \a LINE_KR:CLK_EN:CLK_EN
 */
#define LAN80XX_LINE_KR_CLK_EN                                                                      (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x9100))

/**
 * \brief
 * Enable 64:66 gearbox clock
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_CLK_EN . CLK_GBOX_ENABLE
 */
#define  LAN80XX_F_LINE_KR_CLK_EN_CLK_GBOX_ENABLE(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_KR_CLK_EN_CLK_GBOX_ENABLE                                                   (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_KR_CLK_EN_CLK_GBOX_ENABLE(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Enable AN state machine clock
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_CLK_EN . CLK_CSR_ENABLE
 */
#define  LAN80XX_F_LINE_KR_CLK_EN_CLK_CSR_ENABLE(x)                                                 (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_KR_CLK_EN_CLK_CSR_ENABLE                                                    (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_KR_CLK_EN_CLK_CSR_ENABLE(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Enable Tx core clock
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_CLK_EN . CLK_TX64_ENABLE
 */
#define  LAN80XX_F_LINE_KR_CLK_EN_CLK_TX64_ENABLE(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_KR_CLK_EN_CLK_TX64_ENABLE                                                   (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_KR_CLK_EN_CLK_TX64_ENABLE(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Enable Rx core clock
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_CLK_EN . CLK_RX64_ENABLE
 */
#define  LAN80XX_F_LINE_KR_CLK_EN_CLK_RX64_ENABLE(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_KR_CLK_EN_CLK_RX64_ENABLE                                                   (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_KR_CLK_EN_CLK_RX64_ENABLE(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Enable 8b10b sync clock
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_CLK_EN . CLK_SYNC8B10B_ENABLE
 */
#define  LAN80XX_F_LINE_KR_CLK_EN_CLK_SYNC8B10B_ENABLE(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_KR_CLK_EN_CLK_SYNC8B10B_ENABLE                                              (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_KR_CLK_EN_CLK_SYNC8B10B_ENABLE(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Enable 64b66b sync clock
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_CLK_EN . CLK_SYNC10G_ENABLE
 */
#define  LAN80XX_F_LINE_KR_CLK_EN_CLK_SYNC10G_ENABLE(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_KR_CLK_EN_CLK_SYNC10G_ENABLE                                                (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_KR_CLK_EN_CLK_SYNC10G_ENABLE(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a LINE_KR:TMR_HOLD
 *
 * PMD Vendor Timer Hold Mask register
 */


/**
 * \brief timer hold mask
 *
 * \details
 * Register: \a LINE_KR:TMR_HOLD:TMR_HOLD
 */
#define LAN80XX_LINE_KR_TMR_HOLD                                                                    (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x9101))

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
 * 7: an_wait/FW_resolve
 * 8: break_link
 * 9: gen0
 * 10: gen1

 *
 * Field: ::LAN80XX_LINE_KR_TMR_HOLD . TMR_HOLD
 */
#define  LAN80XX_F_LINE_KR_TMR_HOLD_TMR_HOLD(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,11))
#define  LAN80XX_M_LINE_KR_TMR_HOLD_TMR_HOLD                                                        (LAN80XX_ENCODE_BITMASK(0,11))
#define  LAN80XX_X_LINE_KR_TMR_HOLD_TMR_HOLD(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,11))

/**
 * Register Group: \a LINE_KR:TR_CFG0
 *
 * PMD Vendor Training Configuration register 0
 */


/**
 * \brief training config 0
 *
 * \details
 * Register: \a LINE_KR:TR_CFG0:TR_CFG0
 */
#define LAN80XX_LINE_KR_TR_CFG0                                                                     (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x9102))

/**
 * \brief
 * Training pattern polynomial selection
 *
 * \details
 * 0: x^11 + x^10 + x^6 + x^5 + 1 (100G - lane 0)
 * 1: x^11 + x^9  + x^6 + x^5 + 1 (100G - lane 1)
 * 2: x^11 + x^8  + x^6 + x^4 + 1 (100G - lane 2)
 * 3: x^11 + x^7  + x^6 + x^4 + 1 (100G - lane 3)
 * 4: x^11 + x^9 + 1 (10G/25G)

 *
 * Field: ::LAN80XX_LINE_KR_TR_CFG0 . PRBS_SEL
 */
#define  LAN80XX_F_LINE_KR_TR_CFG0_PRBS_SEL(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,13,3))
#define  LAN80XX_M_LINE_KR_TR_CFG0_PRBS_SEL                                                         (LAN80XX_ENCODE_BITMASK(13,3))
#define  LAN80XX_X_LINE_KR_TR_CFG0_PRBS_SEL(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,13,3))

/**
 * \brief
 * Training pattern seed
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_TR_CFG0 . PRBS_SEED
 */
#define  LAN80XX_F_LINE_KR_TR_CFG0_PRBS_SEED(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,2,11))
#define  LAN80XX_M_LINE_KR_TR_CFG0_PRBS_SEED                                                        (LAN80XX_ENCODE_BITMASK(2,11))
#define  LAN80XX_X_LINE_KR_TR_CFG0_PRBS_SEED(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,2,11))

/**
 * \brief
 * Invert Rx prbs11 in training frame
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_TR_CFG0 . RX_INV
 */
#define  LAN80XX_F_LINE_KR_TR_CFG0_RX_INV(x)                                                        (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_KR_TR_CFG0_RX_INV                                                           (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_KR_TR_CFG0_RX_INV(x)                                                        (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Invert Tx prbs11 in training frame
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_TR_CFG0 . TX_INV
 */
#define  LAN80XX_F_LINE_KR_TR_CFG0_TX_INV(x)                                                        (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_KR_TR_CFG0_TX_INV                                                           (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_KR_TR_CFG0_TX_INV(x)                                                        (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a LINE_KR:TR_CFG1
 *
 * PMD Vendor Training Configuration register 1
 */


/**
 * \brief training config 0
 *
 * \details
 * Register: \a LINE_KR:TR_CFG1:TR_CFG1
 */
#define LAN80XX_LINE_KR_TR_CFG1                                                                     (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x9103))

/**
 * \brief
 * Configuration for the number of Link Training frames with receiver ready
 * bit (of control channel status report) is set to assert remote receiver
 * ready interrupt.(IRQ_VEC.REM_RDY_1)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_TR_CFG1 . REM_RDY_THRESH
 */
#define  LAN80XX_F_LINE_KR_TR_CFG1_REM_RDY_THRESH(x)                                                (LAN80XX_ENCODE_BITFIELD(x,8,4))
#define  LAN80XX_M_LINE_KR_TR_CFG1_REM_RDY_THRESH                                                   (LAN80XX_ENCODE_BITMASK(8,4))
#define  LAN80XX_X_LINE_KR_TR_CFG1_REM_RDY_THRESH(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,8,4))

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
 * Field: ::LAN80XX_LINE_KR_TR_CFG1 . LPSVLD_INT_CFG
 */
#define  LAN80XX_F_LINE_KR_TR_CFG1_LPSVLD_INT_CFG(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_KR_TR_CFG1_LPSVLD_INT_CFG                                                   (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_KR_TR_CFG1_LPSVLD_INT_CFG(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * Register Group: \a LINE_KR:FRCNT_BER
 *
 * PMD Vendor Frame Count for BER register
 */


/**
 * \brief Frame count for BER
 *
 * \details
 * Register: \a LINE_KR:FRCNT_BER:FRCNT_BER
 */
#define LAN80XX_LINE_KR_FRCNT_BER                                                                   (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x9104))

/**
 * \brief
 * Number of training frames used for BER calc.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FRCNT_BER . FRCNT_BER
 */
#define  LAN80XX_F_LINE_KR_FRCNT_BER_FRCNT_BER(x)                                                   (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_FRCNT_BER_FRCNT_BER                                                      (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_FRCNT_BER_FRCNT_BER(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:TR_FRSENT
 *
 * PMD Vendor Training Frame Count register
 */


/**
 * \brief training frames sent
 *
 * \details
 * Register: \a LINE_KR:TR_FRSENT:TR_FRSENT_L
 */
#define LAN80XX_LINE_KR_TR_FRSENT_L                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x9105))

/**
 * \brief
 * Low 16 bits of training frames number sent during link training.The
 * internal 32 bits training frame counter is non roll-over counter. The
 * counter is cleared to zero when trainning is restarted. The internal
 * training frame counter[15:0] is latched for reading from this register.
 * The upper 16 bits are saved when the lower bits are read (the user reads
 * TR_FRSENT_L (live) then TR_FRSENT_H (saved)).
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_TR_FRSENT_L . FRSENT_L
 */
#define  LAN80XX_F_LINE_KR_TR_FRSENT_L_FRSENT_L(x)                                                  (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_TR_FRSENT_L_FRSENT_L                                                     (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_TR_FRSENT_L_FRSENT_L(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief training frames sent
 *
 * \details
 * Register: \a LINE_KR:TR_FRSENT:TR_FRSENT_H
 */
#define LAN80XX_LINE_KR_TR_FRSENT_H                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x9106))

/**
 * \brief
 * High 16 bits of training frames number sent during link training.The
 * internal 32 bits training frame counter is non roll-over counter. The
 * counter is cleared to zero when trainning is restartrd.  The internal
 * training frame counter[31:16] is latched for reading from this register.
 * The upper 16 bits are saved when the lower bits are read (the user reads
 * TR_FRSENT_L (live) then TR_FRSENT_H (saved)).
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_TR_FRSENT_H . FRSENT_H
 */
#define  LAN80XX_F_LINE_KR_TR_FRSENT_H_FRSENT_H(x)                                                  (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_TR_FRSENT_H_FRSENT_H                                                     (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_TR_FRSENT_H_FRSENT_H(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:TR_ERRCNT
 *
 * PMD Vendor Training Prbs11 Error Count register
 */


/**
 * \brief training prbs11 error_count
 *
 * \details
 * Register: \a LINE_KR:TR_ERRCNT:TR_ERRCNT
 */
#define LAN80XX_LINE_KR_TR_ERRCNT                                                                   (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x9107))

/**
 * \brief
 * Bit error count of prbs11 checker. The counter is actived by set BER_EN
 * in FW_REQ register.The counter is stopped at 16'hffff. The counter is
 * started from zero when BER_EN is turned on.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_TR_ERRCNT . ERRCNT
 */
#define  LAN80XX_F_LINE_KR_TR_ERRCNT_ERRCNT(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_TR_ERRCNT_ERRCNT                                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_TR_ERRCNT_ERRCNT(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:AN_CFG0
 *
 * Auto-Negotiation Control register
 */


/**
 * \brief AN config 0
 *
 * \details
 * Register: \a LINE_KR:AN_CFG0:AN_CFG0
 */
#define LAN80XX_LINE_KR_AN_CFG0                                                                     (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x0))

/**
 * \brief
 * AN reset   (Self Clear)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_CFG0 . AN_RESET
 */
#define  LAN80XX_F_LINE_KR_AN_CFG0_AN_RESET(x)                                                      (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_LINE_KR_AN_CFG0_AN_RESET                                                         (LAN80XX_BIT(15))
#define  LAN80XX_X_LINE_KR_AN_CFG0_AN_RESET(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * Extended next page control
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_CFG0 . NPCTL
 */
#define  LAN80XX_F_LINE_KR_AN_CFG0_NPCTL(x)                                                         (LAN80XX_ENCODE_BITFIELD(!!(x),13,1))
#define  LAN80XX_M_LINE_KR_AN_CFG0_NPCTL                                                            (LAN80XX_BIT(13))
#define  LAN80XX_X_LINE_KR_AN_CFG0_NPCTL(x)                                                         (LAN80XX_EXTRACT_BITFIELD(x,13,1))

/**
 * \brief
 * AN enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_CFG0 . AN_ENABLE
 */
#define  LAN80XX_F_LINE_KR_AN_CFG0_AN_ENABLE(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),12,1))
#define  LAN80XX_M_LINE_KR_AN_CFG0_AN_ENABLE                                                        (LAN80XX_BIT(12))
#define  LAN80XX_X_LINE_KR_AN_CFG0_AN_ENABLE(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,12,1))

/**
 * \brief
 * AN restart (Self Clear)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_CFG0 . AN_RESTART
 */
#define  LAN80XX_F_LINE_KR_AN_CFG0_AN_RESTART(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_KR_AN_CFG0_AN_RESTART                                                       (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_KR_AN_CFG0_AN_RESTART(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * Register Group: \a LINE_KR:AN_STS0
 *
 * Auto-Negotiation Status register
 */


/**
 * \brief AN status 0
 *
 * \details
 * Register: \a LINE_KR:AN_STS0:AN_STS0
 */
#define LAN80XX_LINE_KR_AN_STS0                                                                     (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x1))

/**
 * \brief
 * Parallel detection fault (LH)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_STS0 . PARDETFLT
 */
#define  LAN80XX_F_LINE_KR_AN_STS0_PARDETFLT(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_KR_AN_STS0_PARDETFLT                                                        (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_KR_AN_STS0_PARDETFLT(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * Extended next page status
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_STS0 . NPSTAT
 */
#define  LAN80XX_F_LINE_KR_AN_STS0_NPSTAT(x)                                                        (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_KR_AN_STS0_NPSTAT                                                           (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_KR_AN_STS0_NPSTAT(x)                                                        (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * Page received (LH)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_STS0 . PG_RCVD
 */
#define  LAN80XX_F_LINE_KR_AN_STS0_PG_RCVD(x)                                                       (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_KR_AN_STS0_PG_RCVD                                                          (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_KR_AN_STS0_PG_RCVD(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * AN complete
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_STS0 . AN_COMPLETE
 */
#define  LAN80XX_F_LINE_KR_AN_STS0_AN_COMPLETE(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_KR_AN_STS0_AN_COMPLETE                                                      (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_KR_AN_STS0_AN_COMPLETE(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Remote fault (LH)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_STS0 . REM_FLT
 */
#define  LAN80XX_F_LINE_KR_AN_STS0_REM_FLT(x)                                                       (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_KR_AN_STS0_REM_FLT                                                          (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_KR_AN_STS0_REM_FLT(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * AN ability
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_STS0 . AN_ABLE
 */
#define  LAN80XX_F_LINE_KR_AN_STS0_AN_ABLE(x)                                                       (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_KR_AN_STS0_AN_ABLE                                                          (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_KR_AN_STS0_AN_ABLE(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Link status (LL)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_STS0 . LINKSTAT
 */
#define  LAN80XX_F_LINE_KR_AN_STS0_LINKSTAT(x)                                                      (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_KR_AN_STS0_LINKSTAT                                                         (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_KR_AN_STS0_LINKSTAT(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * LP AN ability
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_STS0 . AN_LP_ABLE
 */
#define  LAN80XX_F_LINE_KR_AN_STS0_AN_LP_ABLE(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_KR_AN_STS0_AN_LP_ABLE                                                       (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_KR_AN_STS0_AN_LP_ABLE(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a LINE_KR:LD_ADV
 *
 * Auto-Negotiation advertisement register
 */


/**
 * \brief LD advertised abilities 15-0
 *
 * \details
 * Register: \a LINE_KR:LD_ADV:LD_ADV0
 */
#define LAN80XX_LINE_KR_LD_ADV0                                                                     (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x10))

/**
 * \brief
 * Local advertised abilities D[15:0].
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LD_ADV0 . ADV0
 */
#define  LAN80XX_F_LINE_KR_LD_ADV0_ADV0(x)                                                          (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LD_ADV0_ADV0                                                             (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LD_ADV0_ADV0(x)                                                          (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief LD advertised abilities 31-16
 *
 * \details
 * Register: \a LINE_KR:LD_ADV:LD_ADV1
 */
#define LAN80XX_LINE_KR_LD_ADV1                                                                     (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x11))

/**
 * \brief
 * Local advertised abilities D[31:16].
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LD_ADV1 . ADV1
 */
#define  LAN80XX_F_LINE_KR_LD_ADV1_ADV1(x)                                                          (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LD_ADV1_ADV1                                                             (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LD_ADV1_ADV1(x)                                                          (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief LD advertised abilities 47-32
 *
 * \details
 * Register: \a LINE_KR:LD_ADV:LD_ADV2
 */
#define LAN80XX_LINE_KR_LD_ADV2                                                                     (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x12))

/**
 * \brief
 * Local advertised abilities D[47:32].
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LD_ADV2 . ADV2
 */
#define  LAN80XX_F_LINE_KR_LD_ADV2_ADV2(x)                                                          (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LD_ADV2_ADV2                                                             (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LD_ADV2_ADV2(x)                                                          (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:LP_BP
 *
 * Auto-Negotiation LP Base Page ability register
 */


/**
 * \brief LP base page abilities 15-0
 *
 * \details
 * Register: \a LINE_KR:LP_BP:LP_BP0
 */
#define LAN80XX_LINE_KR_LP_BP0                                                                      (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x13))

/**
 * \brief
 * LP base page abilities D[15:0]. When this register is read, the values
 * of LP_BP1 and LP_BP2 are latched. Reads of those registers return their
 * latched values rather than the active value.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LP_BP0 . ADV0
 */
#define  LAN80XX_F_LINE_KR_LP_BP0_ADV0(x)                                                           (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LP_BP0_ADV0                                                              (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LP_BP0_ADV0(x)                                                           (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief LP base page abilities 31-16
 *
 * \details
 * Register: \a LINE_KR:LP_BP:LP_BP1
 */
#define LAN80XX_LINE_KR_LP_BP1                                                                      (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x14))

/**
 * \brief
 * LP base page abilities D[31:16]. The value of this register is latched
 * when register LP_BP0 is read. Reads of this register return the latched
 * value rather than the current value.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LP_BP1 . ADV1
 */
#define  LAN80XX_F_LINE_KR_LP_BP1_ADV1(x)                                                           (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LP_BP1_ADV1                                                              (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LP_BP1_ADV1(x)                                                           (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief LP base page abilities 47-32
 *
 * \details
 * Register: \a LINE_KR:LP_BP:LP_BP2
 */
#define LAN80XX_LINE_KR_LP_BP2                                                                      (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x15))

/**
 * \brief
 * LP base page abilities D[47:32]. The value of this register is latched
 * when register LP_BP0 is read. Reads of this register return the latched
 * value rather than the current value.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LP_BP2 . ADV2
 */
#define  LAN80XX_F_LINE_KR_LP_BP2_ADV2(x)                                                           (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LP_BP2_ADV2                                                              (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LP_BP2_ADV2(x)                                                           (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:LD_NP
 *
 * Auto-Negotiation Local Device Next Page register
 */


/**
 * \brief NxtPg transmit 15-0
 *
 * \details
 * Register: \a LINE_KR:LD_NP:LD_NP0
 */
#define LAN80XX_LINE_KR_LD_NP0                                                                      (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x16))

/**
 * \brief
 * Next page to transmit D[15:0], A write to LD_NP0 initiates the next page
 * transmission. LD_NP1 amd LD_NP2 should be written before LD_NP0
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LD_NP0 . NP0
 */
#define  LAN80XX_F_LINE_KR_LD_NP0_NP0(x)                                                            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LD_NP0_NP0                                                               (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LD_NP0_NP0(x)                                                            (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief NxtPg transmit 31-16
 *
 * \details
 * Register: \a LINE_KR:LD_NP:LD_NP1
 */
#define LAN80XX_LINE_KR_LD_NP1                                                                      (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x17))

/**
 * \brief
 * Next page to transmit D[31:16], A write to LD_NP0 initiates the next
 * page transmission. This register should be written before LD_NP0
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LD_NP1 . NP1
 */
#define  LAN80XX_F_LINE_KR_LD_NP1_NP1(x)                                                            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LD_NP1_NP1                                                               (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LD_NP1_NP1(x)                                                            (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief NxtPg transmit 47-32
 *
 * \details
 * Register: \a LINE_KR:LD_NP:LD_NP2
 */
#define LAN80XX_LINE_KR_LD_NP2                                                                      (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x18))

/**
 * \brief
 * Next page to transmit D[47:32], A write to LD_NP0 initiates the next
 * page transmission. This register should be written before LD_NP0
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LD_NP2 . NP2
 */
#define  LAN80XX_F_LINE_KR_LD_NP2_NP2(x)                                                            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LD_NP2_NP2                                                               (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LD_NP2_NP2(x)                                                            (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:LP_NP
 *
 * Auto-Negotiation Remote Device Next Page register
 */


/**
 * \brief LP next page ability 15-0
 *
 * \details
 * Register: \a LINE_KR:LP_NP:LP_NP0
 */
#define LAN80XX_LINE_KR_LP_NP0                                                                      (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x19))

/**
 * \brief
 * LP next page D[15:0]. When this register is read, the values of LP_NP1
 * and LP_NP2 are latched. Reads of those registers return their latched
 * values rather than the active value.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LP_NP0 . NP0
 */
#define  LAN80XX_F_LINE_KR_LP_NP0_NP0(x)                                                            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LP_NP0_NP0                                                               (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LP_NP0_NP0(x)                                                            (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief LP next page ability 31-16
 *
 * \details
 * Register: \a LINE_KR:LP_NP:LP_NP1
 */
#define LAN80XX_LINE_KR_LP_NP1                                                                      (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x1a))

/**
 * \brief
 * LP next page D[31:16]. The value of this register is latched when
 * register LP_NP0 is read. Reads of this register return the latched value
 * rather than the current value.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LP_NP1 . NP1
 */
#define  LAN80XX_F_LINE_KR_LP_NP1_NP1(x)                                                            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LP_NP1_NP1                                                               (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LP_NP1_NP1(x)                                                            (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief LP next page ability 47-32
 *
 * \details
 * Register: \a LINE_KR:LP_NP:LP_NP2
 */
#define LAN80XX_LINE_KR_LP_NP2                                                                      (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x1b))

/**
 * \brief
 * LP next page D[47:32]. The value of this register is latched when
 * register LP_NP0 is read. Reads of this register return the latched value
 * rather than the current value.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LP_NP2 . NP2
 */
#define  LAN80XX_F_LINE_KR_LP_NP2_NP2(x)                                                            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LP_NP2_NP2                                                               (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LP_NP2_NP2(x)                                                            (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:BP_ETH_STS
 *
 * Auto-Negotiation Backplane ethernet BASE-R status register
 */


/**
 * \brief Backplane ethernet BASE-R status
 *
 * \details
 * Register: \a LINE_KR:BP_ETH_STS:BP_ETH_STS
 */
#define LAN80XX_LINE_KR_BP_ETH_STS                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x30))

/**
 * \brief
 * 5G-KR      negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_5G_KR
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_5G_KR(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_5G_KR                                                  (LAN80XX_BIT(15))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_5G_KR(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * 2.5G-KX    negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_2P5G_KX
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_2P5G_KX(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),14,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_2P5G_KX                                                (LAN80XX_BIT(14))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_2P5G_KX(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,14,1))

/**
 * \brief
 * 25G-KR     negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_25G_KR
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_25G_KR(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),13,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_25G_KR                                                 (LAN80XX_BIT(13))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_25G_KR(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,13,1))

/**
 * \brief
 * 25G-KR-S   negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_25G_KR_S
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_25G_KR_S(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),12,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_25G_KR_S                                               (LAN80XX_BIT(12))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_25G_KR_S(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,12,1))

/**
 * \brief
 * 100G-CR4   negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_100G_CR4
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_100G_CR4(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),11,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_100G_CR4                                               (LAN80XX_BIT(11))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_100G_CR4(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,11,1))

/**
 * \brief
 * 100G-KR4   negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_100G_KR4
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_100G_KR4(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_100G_KR4                                               (LAN80XX_BIT(10))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_100G_KR4(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,10,1))

/**
 * \brief
 * 100G-KP4   negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_100G_KP4
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_100G_KP4(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_100G_KP4                                               (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_100G_KP4(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * 100G-CR10  negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_100G_CR10
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_100G_CR10(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_100G_CR10                                              (LAN80XX_BIT(8))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_100G_CR10(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * RS-FEC     negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_RS_FEC
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_RS_FEC(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_RS_FEC                                                 (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_RS_FEC(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * 40G-CR4    negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_40G_CR4
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_40G_CR4(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_40G_CR4                                                (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_40G_CR4(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * 40G-KR4    negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_40G_KR4
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_40G_KR4(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_40G_KR4                                                (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_40G_KR4(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * BASE-R FEC negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_R_FEC
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_R_FEC(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_R_FEC                                                  (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_R_FEC(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * 10G-KR     negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_10G_KR
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_10G_KR(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_10G_KR                                                 (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_10G_KR(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * 10G-KX4    negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_10G_KX4
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_10G_KX4(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_10G_KX4                                                (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_10G_KX4(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * 1G-KX      negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_NEG_1G_KX
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_NEG_1G_KX(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_NEG_1G_KX                                                  (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_NEG_1G_KX(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * BP AN ability
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BP_ETH_STS . AN_BP_ABLE
 */
#define  LAN80XX_F_LINE_KR_BP_ETH_STS_AN_BP_ABLE(x)                                                 (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_KR_BP_ETH_STS_AN_BP_ABLE                                                    (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_KR_BP_ETH_STS_AN_BP_ABLE(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a LINE_KR:AN_CFG1
 *
 * Auto-Negotiation Vendor Control register 1
 */


/**
 * \brief AN config 1
 *
 * \details
 * Register: \a LINE_KR:AN_CFG1:AN_CFG1
 */
#define LAN80XX_LINE_KR_AN_CFG1                                                                     (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8000))

/**
 * \brief
 * Enable 16-bit data input for 5G mode
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_CFG1 . RCV_16B_FOR_5G
 */
#define  LAN80XX_F_LINE_KR_AN_CFG1_RCV_16B_FOR_5G(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),14,1))
#define  LAN80XX_M_LINE_KR_AN_CFG1_RCV_16B_FOR_5G                                                   (LAN80XX_BIT(14))
#define  LAN80XX_X_LINE_KR_AN_CFG1_RCV_16B_FOR_5G(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,14,1))

/**
 * \brief
 * Clock divider value for timer clocks, base clk is 300MHz
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_CFG1 . TMR_DVDR
 */
#define  LAN80XX_F_LINE_KR_AN_CFG1_TMR_DVDR(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,10,4))
#define  LAN80XX_M_LINE_KR_AN_CFG1_TMR_DVDR                                                         (LAN80XX_ENCODE_BITMASK(10,4))
#define  LAN80XX_X_LINE_KR_AN_CFG1_TMR_DVDR(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,10,4))

/**
 * \brief
 * Clear ABILITY_DETECT state counter
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_CFG1 . ABDET_CLR
 */
#define  LAN80XX_F_LINE_KR_AN_CFG1_ABDET_CLR(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_KR_AN_CFG1_ABDET_CLR                                                        (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_KR_AN_CFG1_ABDET_CLR(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * Clear AN state machine history
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_CFG1 . AN_SM_HIST_CLR
 */
#define  LAN80XX_F_LINE_KR_AN_CFG1_AN_SM_HIST_CLR(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_LINE_KR_AN_CFG1_AN_SM_HIST_CLR                                                   (LAN80XX_BIT(8))
#define  LAN80XX_X_LINE_KR_AN_CFG1_AN_SM_HIST_CLR(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Bypass training if 10G/25G negotiated
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_CFG1 . TR_DISABLE
 */
#define  LAN80XX_F_LINE_KR_AN_CFG1_TR_DISABLE(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_KR_AN_CFG1_TR_DISABLE                                                       (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_KR_AN_CFG1_TR_DISABLE(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Select source of 10G/25G sync signal (Used for HCD Technology PCS using
 * 64b66b Encoding Eg. 10GBaseKR, 5GBaseKR, 25GBaseKR etc.,)
 *
 * \details
 * 0: KR internal
 * 1: External

 *
 * Field: ::LAN80XX_LINE_KR_AN_CFG1 . SYNC10G_SEL
 */
#define  LAN80XX_F_LINE_KR_AN_CFG1_SYNC10G_SEL(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_KR_AN_CFG1_SYNC10G_SEL                                                      (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_KR_AN_CFG1_SYNC10G_SEL(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Select source of 1G sync signal (Used for HCD Technology PCS using 8b10b
 * Encoding. Eg. 1000BaseX, 10GBaseKX4, 2.5GBaseX etc.,)
 *
 * \details
 * 0: KR internal
 * 1: External

 *
 * Field: ::LAN80XX_LINE_KR_AN_CFG1 . SYNC8B10B_SEL
 */
#define  LAN80XX_F_LINE_KR_AN_CFG1_SYNC8B10B_SEL(x)                                                 (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_KR_AN_CFG1_SYNC8B10B_SEL                                                    (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_KR_AN_CFG1_SYNC8B10B_SEL(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,4,1))

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
 * Field: ::LAN80XX_LINE_KR_AN_CFG1 . RATE
 */
#define  LAN80XX_F_LINE_KR_AN_CFG1_RATE(x)                                                          (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_KR_AN_CFG1_RATE                                                             (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_KR_AN_CFG1_RATE(x)                                                          (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * Register Group: \a LINE_KR:AN_CFG2
 *
 * Auto-Negotiation Vendor Control register 2
 */


/**
 * \brief AN config 2
 *
 * \details
 * Register: \a LINE_KR:AN_CFG2:AN_CFG2
 */
#define LAN80XX_LINE_KR_AN_CFG2                                                                     (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8002))

/**
 * \brief
 * Configuration to specify if RSFEC is to be enabled for the HCD
 * Technology when FW_RESOLVE_ENA is set to 1. RSFEC ena should be set to 1
 * only when the HCD technology in FW_HCD is 25GBaseKR or 100GBaseKR4
 *
 * \details
 * 1 :- RS-FEC is to be enabled for HCD Technology (used only when
 * FW_RESOLVE_ENA is set to 1)
 * 0 :- RS-FEC is to be disabled for HCD Technology
 *
 * Field: ::LAN80XX_LINE_KR_AN_CFG2 . FW_RSFEC_ENA
 */
#define  LAN80XX_F_LINE_KR_AN_CFG2_FW_RSFEC_ENA(x)                                                  (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_KR_AN_CFG2_FW_RSFEC_ENA                                                     (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_KR_AN_CFG2_FW_RSFEC_ENA(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * Configuration to specify if RFEC is to be enabled for the HCD Technology
 * when FW_RESOLVE_ENA is set to 1. RFEC ena should be set to 1 only when
 * the HCD technology in FW_HCD is 10GBaseKR or greater
 *
 * \details
 * 1 :- KR-FEC is to be enabled for HCD Technology (used only when
 * FW_RESOLVE_ENA is set to 1)
 * 0 :- KR-FEC is to be disabled for HCD Technology
 *
 * Field: ::LAN80XX_LINE_KR_AN_CFG2 . FW_RFEC_ENA
 */
#define  LAN80XX_F_LINE_KR_AN_CFG2_FW_RFEC_ENA(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_LINE_KR_AN_CFG2_FW_RFEC_ENA                                                      (LAN80XX_BIT(8))
#define  LAN80XX_X_LINE_KR_AN_CFG2_FW_RFEC_ENA(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Configuration to control the HCD value from FW when FW_RESOLVE_ENA is
 * set to 1. This field is unused when FW_RESOLVE_ENA is set to 0.
 *
 * \details
 * 0: Incompatible Link 1 : 100G-CR4
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
 * Field: ::LAN80XX_LINE_KR_AN_CFG2 . FW_HCD
 */
#define  LAN80XX_F_LINE_KR_AN_CFG2_FW_HCD(x)                                                        (LAN80XX_ENCODE_BITFIELD(x,4,4))
#define  LAN80XX_M_LINE_KR_AN_CFG2_FW_HCD                                                           (LAN80XX_ENCODE_BITMASK(4,4))
#define  LAN80XX_X_LINE_KR_AN_CFG2_FW_HCD(x)                                                        (LAN80XX_EXTRACT_BITFIELD(x,4,4))

/**
 * \brief
 * Configuration to control the Priority Resolution function by HW or SW.
 *
 * \details
 * 1:- SW Decides the HCD technology
 * 0:- HW Decides the HCD technology (Default)
 *
 * Field: ::LAN80XX_LINE_KR_AN_CFG2 . FW_RESOLVE_ENA
 */
#define  LAN80XX_F_LINE_KR_AN_CFG2_FW_RESOLVE_ENA(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_KR_AN_CFG2_FW_RESOLVE_ENA                                                   (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_KR_AN_CFG2_FW_RESOLVE_ENA(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Specifies the number of pages to be transmitted in COMPLETE_ACKNOWLEDGE
 * state before the ack_finished is asserted.
 *
 * \details
 * 0 : 1 Page
 * 1 : 2 Pages
 * 2 : 3 Pages
 * 7 : 8 Pages
 *
 * Valid values as per the protocol are 5 to 7. Others are for Debug
 * purpose.
 *
 * Field: ::LAN80XX_LINE_KR_AN_CFG2 . ACK_FIN_PAGE_CNT
 */
#define  LAN80XX_F_LINE_KR_AN_CFG2_ACK_FIN_PAGE_CNT(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_KR_AN_CFG2_ACK_FIN_PAGE_CNT                                                 (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_KR_AN_CFG2_ACK_FIN_PAGE_CNT(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * Register Group: \a LINE_KR:BL_TMR
 *
 * Auto-Negotiation Vendor break_link timer register
 */


/**
 * \brief AN break_link timer
 *
 * \details
 * Register: \a LINE_KR:BL_TMR:BL_TMR_LOW
 */
#define LAN80XX_LINE_KR_BL_TMR_LOW                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8010))

/**
 * \brief
 * break_link_timer setting. Default value corresponds to 70ms for a System
 * clock of 3.3ns and Timer Divider of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BL_TMR_LOW . TMR_L
 */
#define  LAN80XX_F_LINE_KR_BL_TMR_LOW_TMR_L(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_BL_TMR_LOW_TMR_L                                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_BL_TMR_LOW_TMR_L(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief AN break_link timer
 *
 * \details
 * Register: \a LINE_KR:BL_TMR:BL_TMR_HIGH
 */
#define LAN80XX_LINE_KR_BL_TMR_HIGH                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8011))

/**
 * \brief
 * break_link_timer setting. Default value corresponds to 70ms for a System
 * clock of 3.3ns and Timer Divider of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_BL_TMR_HIGH . TMR_H
 */
#define  LAN80XX_F_LINE_KR_BL_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_BL_TMR_HIGH_TMR_H                                                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_BL_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:AW_TMR
 *
 * Auto-Negotiation Vendor aneg_wait timer register
 */


/**
 * \brief AN aneg_wait timer
 *
 * \details
 * Register: \a LINE_KR:AW_TMR:AW_TMR_LOW
 */
#define LAN80XX_LINE_KR_AW_TMR_LOW                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8012))

/**
 * \brief
 * an_wait_timer setting.Default value corresponds to 38ms for system clock
 * period of 3.3ns and timer divider of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AW_TMR_LOW . TMR_L
 */
#define  LAN80XX_F_LINE_KR_AW_TMR_LOW_TMR_L(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_AW_TMR_LOW_TMR_L                                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_AW_TMR_LOW_TMR_L(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief AN aneg_wait timer
 *
 * \details
 * Register: \a LINE_KR:AW_TMR:AW_TMR_HIGH
 */
#define LAN80XX_LINE_KR_AW_TMR_HIGH                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8013))

/**
 * \brief
 * an_wait_timer setting.Default value corresponds to 38ms for system clock
 * period of 3.3ns and timer divider of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AW_TMR_HIGH . TMR_H
 */
#define  LAN80XX_F_LINE_KR_AW_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_AW_TMR_HIGH_TMR_H                                                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_AW_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:LF_TMR
 *
 * Auto-Negotiation Vendor link_fail_inhibit timer register
 */


/**
 * \brief AN link_fail_inhibit_timer
 *
 * \details
 * Register: \a LINE_KR:LF_TMR:LF_TMR_LOW
 */
#define LAN80XX_LINE_KR_LF_TMR_LOW                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8014))

/**
 * \brief
 * link_fail_inhibit_timer settingDefault value is set to 50ms for a system
 * clock period of 3.3ns and Timer Divider of 2. Time shall not be modified
 * whether Training is run or not as there is a training timer in TRAIN
 * state which takes care of the training time of 500ms.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LF_TMR_LOW . TMR_L
 */
#define  LAN80XX_F_LINE_KR_LF_TMR_LOW_TMR_L(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LF_TMR_LOW_TMR_L                                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LF_TMR_LOW_TMR_L(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief AN link_fail_inhibit_timer
 *
 * \details
 * Register: \a LINE_KR:LF_TMR:LF_TMR_HIGH
 */
#define LAN80XX_LINE_KR_LF_TMR_HIGH                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8015))

/**
 * \brief
 * 1g link_fail_inhibit_timer settingDefault value is set to 50ms for a
 * system clock period of 3.3ns and Timer Divider of 2. Time shall not be
 * modified whether Training is run or not as there is a training timer in
 * TRAIN state which takes care of the training time of 500ms.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LF_TMR_HIGH . TMR_H
 */
#define  LAN80XX_F_LINE_KR_LF_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LF_TMR_HIGH_TMR_H                                                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LF_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:FR_TMR
 *
 * Auto-Negotiation Vendor firmware_inhibit timer register
 */


/**
 * \brief AN firmware_inhibit timer
 *
 * \details
 * Register: \a LINE_KR:FR_TMR:FR_TMR_LOW
 */
#define LAN80XX_LINE_KR_FR_TMR_LOW                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8016))

/**
 * \brief
 * Timeout Value before which Firmware is expected to complete Priority
 * Resolution when FW_RESOLVE_ENA is set to 1.Default value is set to 5ms
 * for a system clock period of 3.3ns and Timer Divider of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FR_TMR_LOW . TMR_L
 */
#define  LAN80XX_F_LINE_KR_FR_TMR_LOW_TMR_L(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_FR_TMR_LOW_TMR_L                                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_FR_TMR_LOW_TMR_L(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief AN firmware_inhibit timer
 *
 * \details
 * Register: \a LINE_KR:FR_TMR:FR_TMR_HIGH
 */
#define LAN80XX_LINE_KR_FR_TMR_HIGH                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8017))

/**
 * \brief
 * Timeout Value before which Firmware is expected to complete Priority
 * Resolution when FW_RESOLVE_ENA is set to 1.Default value is set to 5ms
 * for a system clock period of 3.3ns and Timer Divider of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FR_TMR_HIGH . TMR_H
 */
#define  LAN80XX_F_LINE_KR_FR_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_FR_TMR_HIGH_TMR_H                                                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_FR_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:LP_TMR
 *
 * Auto-Negotiation Vendor link_pass_inhibit timer register
 */


/**
 * \brief AN link_pass_inhibit timer
 *
 * \details
 * Register: \a LINE_KR:LP_TMR:LP_TMR_LOW
 */
#define LAN80XX_LINE_KR_LP_TMR_LOW                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8018))

/**
 * \brief
 * link_pass_inhibit_timer setting
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LP_TMR_LOW . TMR_L
 */
#define  LAN80XX_F_LINE_KR_LP_TMR_LOW_TMR_L(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LP_TMR_LOW_TMR_L                                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LP_TMR_LOW_TMR_L(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief AN link_pass_inhibit timer
 *
 * \details
 * Register: \a LINE_KR:LP_TMR:LP_TMR_HIGH
 */
#define LAN80XX_LINE_KR_LP_TMR_HIGH                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8019))

/**
 * \brief
 * link_pass_inhibit_timer setting
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_LP_TMR_HIGH . TMR_H
 */
#define  LAN80XX_F_LINE_KR_LP_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_LP_TMR_HIGH_TMR_H                                                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_LP_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:TR_TMR
 *
 * Auto-Negotiation Vendor training state timer register
 */


/**
 * \brief AN training state timer
 *
 * \details
 * Register: \a LINE_KR:TR_TMR:TR_TMR_LOW
 */
#define LAN80XX_LINE_KR_TR_TMR_LOW                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x801a))

/**
 * \brief
 * training_state_timer settingDefault value corresponds to 450ms for a
 * system clock period of 3.3ns and Timer Divider of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_TR_TMR_LOW . TMR_L
 */
#define  LAN80XX_F_LINE_KR_TR_TMR_LOW_TMR_L(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_TR_TMR_LOW_TMR_L                                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_TR_TMR_LOW_TMR_L(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief AN training state timer
 *
 * \details
 * Register: \a LINE_KR:TR_TMR:TR_TMR_HIGH
 */
#define LAN80XX_LINE_KR_TR_TMR_HIGH                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x801b))

/**
 * \brief
 * training_state_timer settingDefault value corresponds to 450ms for a
 * system clock period of 3.3ns and Timer Divider of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_TR_TMR_HIGH . TMR_H
 */
#define  LAN80XX_F_LINE_KR_TR_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_TR_TMR_HIGH_TMR_H                                                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_TR_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:PD_TMR
 *
 * Auto-Negotiation Vendor page_detect timer register
 */


/**
 * \brief AN page_detect timer
 *
 * \details
 * Register: \a LINE_KR:PD_TMR:PD_TMR_LOW
 */
#define LAN80XX_LINE_KR_PD_TMR_LOW                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x801c))

/**
 * \brief
 * page_detect_timer setting. Time the state machine stays in ABILITY
 * DETECT for ability match before entering into RATE_DETECT state to
 * perform parallel detection.Default value corresponds to 500ms for system
 * clock period of 3.3ns and Timer Divider of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_PD_TMR_LOW . TMR_L
 */
#define  LAN80XX_F_LINE_KR_PD_TMR_LOW_TMR_L(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_PD_TMR_LOW_TMR_L                                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_PD_TMR_LOW_TMR_L(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief AN page_detect timer
 *
 * \details
 * Register: \a LINE_KR:PD_TMR:PD_TMR_HIGH
 */
#define LAN80XX_LINE_KR_PD_TMR_HIGH                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x801d))

/**
 * \brief
 * page_detect_timer setting. Time the state machine stays in ABILITY
 * DETECT for ability match before entering into RATE_DETECT state to
 * perform parallel detection.Default value corresponds to 500ms for system
 * clock period of 3.3ns and Timer Divider of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_PD_TMR_HIGH . TMR_H
 */
#define  LAN80XX_F_LINE_KR_PD_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_PD_TMR_HIGH_TMR_H                                                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_PD_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:RD_TMR
 *
 * Auto-Negotiation Vendor rate_detect timer register
 */


/**
 * \brief AN rate_detect timer
 *
 * \details
 * Register: \a LINE_KR:RD_TMR:RD_TMR_LOW
 */
#define LAN80XX_LINE_KR_RD_TMR_LOW                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x801e))

/**
 * \brief
 * rate_detect_timer setting. Time the state machine stays in RATE DETECT
 * for speed match .Default value corresponds to 10ms for system clock
 * period of 3.3ns and Timer Divider of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_RD_TMR_LOW . TMR_L
 */
#define  LAN80XX_F_LINE_KR_RD_TMR_LOW_TMR_L(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_RD_TMR_LOW_TMR_L                                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_RD_TMR_LOW_TMR_L(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief AN rate_detect timer
 *
 * \details
 * Register: \a LINE_KR:RD_TMR:RD_TMR_HIGH
 */
#define LAN80XX_LINE_KR_RD_TMR_HIGH                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x801f))

/**
 * \brief
 * rate_detect_timer setting. Time the state machine stays in RATE DETECT
 * for speed match .Default value corresponds to 10ms for system clock
 * period of 3.3ns and Timer Divider of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_RD_TMR_HIGH . TMR_H
 */
#define  LAN80XX_F_LINE_KR_RD_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_RD_TMR_HIGH_TMR_H                                                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_RD_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:WT_TMR
 *
 * Auto-Negotiation Vendor wait timer register
 */


/**
 * \brief training wait_timer
 *
 * \details
 * Register: \a LINE_KR:WT_TMR:WT_TMR
 */
#define LAN80XX_LINE_KR_WT_TMR                                                                      (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8024))

/**
 * \brief
 * wait_timer for training.The default value corresponds to a period of
 * around 200 10GBaseKR Training frames for a system clock period of 3.3ns
 * and Timer Divider of 2.This value needs to be reconfigured to an
 * appropriate value by Firmware for HCD (using KR Link Training) other
 * than 10GBaseKR
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_WT_TMR . TMR
 */
#define  LAN80XX_F_LINE_KR_WT_TMR_TMR(x)                                                            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_WT_TMR_TMR                                                               (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_WT_TMR_TMR(x)                                                            (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:MW_TMR
 *
 * Auto-Negotiation Vendor training max wait timer register
 */


/**
 * \brief training maxwait_timer
 *
 * \details
 * Register: \a LINE_KR:MW_TMR:MW_TMR_LOW
 */
#define LAN80XX_LINE_KR_MW_TMR_LOW                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8026))

/**
 * \brief
 * maxwait_timer for trainingDefault value corresponds to 500ms for a
 * system clock period of 3.3ns and a Timer Divider value of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_MW_TMR_LOW . TMR_L
 */
#define  LAN80XX_F_LINE_KR_MW_TMR_LOW_TMR_L(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_MW_TMR_LOW_TMR_L                                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_MW_TMR_LOW_TMR_L(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief training maxwait_timer
 *
 * \details
 * Register: \a LINE_KR:MW_TMR:MW_TMR_HIGH
 */
#define LAN80XX_LINE_KR_MW_TMR_HIGH                                                                 (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8027))

/**
 * \brief
 * maxwait_timer for trainingDefault value corresponds to 500ms for a
 * system clock period of 3.3ns and a Timer Divider value of 2.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_MW_TMR_HIGH . TMR_H
 */
#define  LAN80XX_F_LINE_KR_MW_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_MW_TMR_HIGH_TMR_H                                                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_MW_TMR_HIGH_TMR_H(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:GEN0_TMR
 *
 * Auto-Negotiation Vendor generic_0  timer register
 */


/**
 * \brief generic_0 timer
 *
 * \details
 * Register: \a LINE_KR:GEN0_TMR:GEN0_TMR_LOW
 */
#define LAN80XX_LINE_KR_GEN0_TMR_LOW                                                                (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8028))

/**
 * \brief
 * generic timer
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_GEN0_TMR_LOW . TMR_L
 */
#define  LAN80XX_F_LINE_KR_GEN0_TMR_LOW_TMR_L(x)                                                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_GEN0_TMR_LOW_TMR_L                                                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_GEN0_TMR_LOW_TMR_L(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief generic_0 timer
 *
 * \details
 * Register: \a LINE_KR:GEN0_TMR:GEN0_TMR_HIGH
 */
#define LAN80XX_LINE_KR_GEN0_TMR_HIGH                                                               (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8029))

/**
 * \brief
 * generic timer
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_GEN0_TMR_HIGH . TMR_H
 */
#define  LAN80XX_F_LINE_KR_GEN0_TMR_HIGH_TMR_H(x)                                                   (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_GEN0_TMR_HIGH_TMR_H                                                      (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_GEN0_TMR_HIGH_TMR_H(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:GEN1_TMR
 *
 * Auto-Negotiation Vendor generic_1  timer register
 */


/**
 * \brief generic_1 timer
 *
 * \details
 * Register: \a LINE_KR:GEN1_TMR:GEN1_TMR_LOW
 */
#define LAN80XX_LINE_KR_GEN1_TMR_LOW                                                                (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x802a))

/**
 * \brief
 * generic timer
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_GEN1_TMR_LOW . TMR_L
 */
#define  LAN80XX_F_LINE_KR_GEN1_TMR_LOW_TMR_L(x)                                                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_GEN1_TMR_LOW_TMR_L                                                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_GEN1_TMR_LOW_TMR_L(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief generic_1 timer
 *
 * \details
 * Register: \a LINE_KR:GEN1_TMR:GEN1_TMR_HIGH
 */
#define LAN80XX_LINE_KR_GEN1_TMR_HIGH                                                               (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x802b))

/**
 * \brief
 * generic timer
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_GEN1_TMR_HIGH . TMR_H
 */
#define  LAN80XX_F_LINE_KR_GEN1_TMR_HIGH_TMR_H(x)                                                   (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_GEN1_TMR_HIGH_TMR_H                                                      (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_GEN1_TMR_HIGH_TMR_H(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:AN_HIST
 *
 * Auto-Negotiation Vendor state machine history register
 */


/**
 * \brief AN arb state mach history
 *
 * \details
 * Register: \a LINE_KR:AN_HIST:AN_HIST
 */
#define LAN80XX_LINE_KR_AN_HIST                                                                     (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8030))

/**
 * \brief
 * AN state machine history. Bits are set for each of the states entered.
 *
 * \details
 * Bit 0   :   AN_ENABLE
 *  Bit 1   :   XMT_DISABLE
 *  Bit 2   :   ABILITY_DET
 *  Bit 3   :   ACK_DET
 *  Bit 4   :   COMPLETE_ACK
 *  Bit 5   :   TRAIN
 *  Bit 6   :   AN_GOOD_CHK
 *  Bit 7   :   AN_GOOD
 *  Bit 8   :   RATE_DET
 *  Bit 11  :   LINK_STAT_CHK
 *  Bit 12  :   PARLL_DET_FAULT
 *  Bit 13  :   WAIT_RATE_DONE
 *  Bit 14  :   NXTPG_WAIT
 *  Bit 15  :   WAIT_FW_RES
 *
 * Field: ::LAN80XX_LINE_KR_AN_HIST . AN_SM_HIST
 */
#define  LAN80XX_F_LINE_KR_AN_HIST_AN_SM_HIST(x)                                                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_KR_AN_HIST_AN_SM_HIST                                                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_KR_AN_HIST_AN_SM_HIST(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_KR:AN_SM
 *
 * Auto-Negotiation Vendor arb state machine history register
 */


/**
 * \brief AN arb state machine
 *
 * \details
 * Register: \a LINE_KR:AN_SM:AN_SM
 */
#define LAN80XX_LINE_KR_AN_SM                                                                       (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8031))

/**
 * \brief
 * ABILITY_DETECT state counter
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_SM . ABDET_CNT
 */
#define  LAN80XX_F_LINE_KR_AN_SM_ABDET_CNT(x)                                                       (LAN80XX_ENCODE_BITFIELD(x,4,4))
#define  LAN80XX_M_LINE_KR_AN_SM_ABDET_CNT                                                          (LAN80XX_ENCODE_BITMASK(4,4))
#define  LAN80XX_X_LINE_KR_AN_SM_ABDET_CNT(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,4,4))

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
 *  4'd15  :   WAIT_FW_RES
 *
 * Field: ::LAN80XX_LINE_KR_AN_SM . AN_SM
 */
#define  LAN80XX_F_LINE_KR_AN_SM_AN_SM(x)                                                           (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_KR_AN_SM_AN_SM                                                              (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_KR_AN_SM_AN_SM(x)                                                           (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * Register Group: \a LINE_KR:AN_STS1
 *
 * Auto-Negotiation Vendor training history register
 */


/**
 * \brief AN status 1
 *
 * \details
 * Register: \a LINE_KR:AN_STS1:AN_STS1
 */
#define LAN80XX_LINE_KR_AN_STS1                                                                     (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8032))

/**
 * \brief
 * AN or Training frames are being exchanged
 *
 * \details
 * 0: External mux should switch to egress traffic
 * 1: External mux should switch to KR output

 *
 * Field: ::LAN80XX_LINE_KR_AN_STS1 . KR_ACTV
 */
#define  LAN80XX_F_LINE_KR_AN_STS1_KR_ACTV(x)                                                       (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_LINE_KR_AN_STS1_KR_ACTV                                                          (LAN80XX_BIT(8))
#define  LAN80XX_X_LINE_KR_AN_STS1_KR_ACTV(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * 1G or 3G sync status of local detector
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_STS1 . SYNC8B10B
 */
#define  LAN80XX_F_LINE_KR_AN_STS1_SYNC8B10B(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_KR_AN_STS1_SYNC8B10B                                                        (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_KR_AN_STS1_SYNC8B10B(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * 10G sync status of local detector
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_STS1 . SYNC10G
 */
#define  LAN80XX_F_LINE_KR_AN_STS1_SYNC10G(x)                                                       (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_KR_AN_STS1_SYNC10G                                                          (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_KR_AN_STS1_SYNC10G(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Nonce match (LH)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_STS1 . NONCE_MATCH
 */
#define  LAN80XX_F_LINE_KR_AN_STS1_NONCE_MATCH(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_KR_AN_STS1_NONCE_MATCH                                                      (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_KR_AN_STS1_NONCE_MATCH(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Incompatible link (LH)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_AN_STS1 . INCP_LINK
 */
#define  LAN80XX_F_LINE_KR_AN_STS1_INCP_LINK(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_KR_AN_STS1_INCP_LINK                                                        (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_KR_AN_STS1_INCP_LINK(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,4,1))

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
 * Field: ::LAN80XX_LINE_KR_AN_STS1 . LINK_HCD
 */
#define  LAN80XX_F_LINE_KR_AN_STS1_LINK_HCD(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_KR_AN_STS1_LINK_HCD                                                         (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_KR_AN_STS1_LINK_HCD(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * Register Group: \a LINE_KR:FW_MSG
 *
 * Auto-Negotiation Vendor firmware message register
 */


/**
 * \brief Firmware Self Clear messages
 *
 * \details
 * Register: \a LINE_KR:FW_MSG:FW_MSG
 */
#define LAN80XX_LINE_KR_FW_MSG                                                                      (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8040))

/**
 * \brief
 * Indicates that the FW has completed the Priority Resolution function and
 * updated the HCD Capabilities of the Link Partners in AN_CFG1.FW_HCD,
 * AN_CFG1.FW_RFEC_ENA, AN_CFG1.FW_RSFEC_ENA.  It is expected that the
 * RFEC_ENA and RSFEC_ENA are not set to 1 at the same time.
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FW_MSG . FW_RESOLVE_DONE
 */
#define  LAN80XX_F_LINE_KR_FW_MSG_FW_RESOLVE_DONE(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_KR_FW_MSG_FW_RESOLVE_DONE                                                   (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_KR_FW_MSG_FW_RESOLVE_DONE(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Indicates that training has completed (Self Clear)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FW_MSG . TR_DONE
 */
#define  LAN80XX_F_LINE_KR_FW_MSG_TR_DONE(x)                                                        (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_KR_FW_MSG_TR_DONE                                                           (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_KR_FW_MSG_TR_DONE(x)                                                        (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Indicates that LDCOEF is stable (Self Clear)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FW_MSG . LDCOEF_VLD
 */
#define  LAN80XX_F_LINE_KR_FW_MSG_LDCOEF_VLD(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_KR_FW_MSG_LDCOEF_VLD                                                        (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_KR_FW_MSG_LDCOEF_VLD(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Indicates that LDSTAT is stable (Self Clear)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FW_MSG . LDSTAT_VLD
 */
#define  LAN80XX_F_LINE_KR_FW_MSG_LDSTAT_VLD(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_KR_FW_MSG_LDSTAT_VLD                                                        (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_KR_FW_MSG_LDSTAT_VLD(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Indicates that next_page is loaded (Self Clear)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FW_MSG . NP_LOADED
 */
#define  LAN80XX_F_LINE_KR_FW_MSG_NP_LOADED(x)                                                      (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_KR_FW_MSG_NP_LOADED                                                         (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_KR_FW_MSG_NP_LOADED(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * rate setting is done (Self Clear)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FW_MSG . RATE_DONE
 */
#define  LAN80XX_F_LINE_KR_FW_MSG_RATE_DONE(x)                                                      (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_KR_FW_MSG_RATE_DONE                                                         (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_KR_FW_MSG_RATE_DONE(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a LINE_KR:FW_REQ
 *
 * Auto-Negotiation Vendor firmware request register
 */


/**
 * \brief Firmware Self Clear request
 *
 * \details
 * Register: \a LINE_KR:FW_REQ:FW_REQ
 */
#define LAN80XX_LINE_KR_FW_REQ                                                                      (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8041))

/**
 * \brief
 * Start BER checker (Self Clear)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FW_REQ . BER_EN
 */
#define  LAN80XX_F_LINE_KR_FW_REQ_BER_EN(x)                                                         (LAN80XX_ENCODE_BITFIELD(!!(x),12,1))
#define  LAN80XX_M_LINE_KR_FW_REQ_BER_EN                                                            (LAN80XX_BIT(12))
#define  LAN80XX_X_LINE_KR_FW_REQ_BER_EN(x)                                                         (LAN80XX_EXTRACT_BITFIELD(x,12,1))

/**
 * \brief
 * start generic timer 1 (Self Clear)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FW_REQ . GEN1_TMR_START
 */
#define  LAN80XX_F_LINE_KR_FW_REQ_GEN1_TMR_START(x)                                                 (LAN80XX_ENCODE_BITFIELD(!!(x),11,1))
#define  LAN80XX_M_LINE_KR_FW_REQ_GEN1_TMR_START                                                    (LAN80XX_BIT(11))
#define  LAN80XX_X_LINE_KR_FW_REQ_GEN1_TMR_START(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,11,1))

/**
 * \brief
 * start generic timer 0 (Self Clear)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FW_REQ . GEN0_TMR_START
 */
#define  LAN80XX_F_LINE_KR_FW_REQ_GEN0_TMR_START(x)                                                 (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_LINE_KR_FW_REQ_GEN0_TMR_START                                                    (LAN80XX_BIT(10))
#define  LAN80XX_X_LINE_KR_FW_REQ_GEN0_TMR_START(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,10,1))

/**
 * \brief
 * start wait timer (Self Clear)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FW_REQ . WT_START
 */
#define  LAN80XX_F_LINE_KR_FW_REQ_WT_START(x)                                                       (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_KR_FW_REQ_WT_START                                                          (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_KR_FW_REQ_WT_START(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * start maxwait timer (Self Clear)
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_FW_REQ . MW_START
 */
#define  LAN80XX_F_LINE_KR_FW_REQ_MW_START(x)                                                       (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_LINE_KR_FW_REQ_MW_START                                                          (LAN80XX_BIT(8))
#define  LAN80XX_X_LINE_KR_FW_REQ_MW_START(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * Register Group: \a LINE_KR:IRQ_VEC
 *
 * Auto-Negotiation Vendor interrupt vector register
 */


/**
 * \brief interrupt vector. All sticky
 *
 * \details
 * Register: \a LINE_KR:IRQ_VEC:IRQ_VEC_0
 */
#define LAN80XX_LINE_KR_IRQ_VEC_0                                                                   (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8042))

/**
 * \brief
 * interrupt for AN_SM = TRAIN, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_0 . AN_TRAIN
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_0_AN_TRAIN(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_0_AN_TRAIN                                                       (LAN80XX_BIT(15))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_0_AN_TRAIN(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * interrupt for AN_SM = RATE_DET, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_0 . AN_RATE_DET
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_0_AN_RATE_DET(x)                                                 (LAN80XX_ENCODE_BITFIELD(!!(x),14,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_0_AN_RATE_DET                                                    (LAN80XX_BIT(14))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_0_AN_RATE_DET(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,14,1))

/**
 * \brief
 * interrupt for AN_SM = COMPLETE_ACK, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_0 . CMPL_ACK
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_0_CMPL_ACK(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),13,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_0_CMPL_ACK                                                       (LAN80XX_BIT(13))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_0_CMPL_ACK(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,13,1))

/**
 * \brief
 * interrupt for AN_SM = AN_GOOD, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_0 . AN_GOOD
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_0_AN_GOOD(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),12,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_0_AN_GOOD                                                        (LAN80XX_BIT(12))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_0_AN_GOOD(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,12,1))

/**
 * \brief
 * interrupt for AN link fail, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_0 . LINK_FAIL
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_0_LINK_FAIL(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),11,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_0_LINK_FAIL                                                      (LAN80XX_BIT(11))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_0_LINK_FAIL(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,11,1))

/**
 * \brief
 * interrupt for AN ABILITY_DETECT fail, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_0 . ABD_FAIL
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_0_ABD_FAIL(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_0_ABD_FAIL                                                       (LAN80XX_BIT(10))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_0_ABD_FAIL(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,10,1))

/**
 * \brief
 * interrupt for AN ACK_DETECT fail, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_0 . ACK_FAIL
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_0_ACK_FAIL(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_0_ACK_FAIL                                                       (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_0_ACK_FAIL(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * interrupt for AN NEXT_PAGE fail, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_0 . NP_FAIL
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_0_NP_FAIL(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_0_NP_FAIL                                                        (LAN80XX_BIT(8))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_0_NP_FAIL(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * interrupt for AN LP NEXT_PAGE received, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_0 . NP_RX
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_0_NP_RX(x)                                                       (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_0_NP_RX                                                          (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_0_NP_RX(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * interrupt for AN incompatible link, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_0 . INCP_LINK
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_0_INCP_LINK(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_0_INCP_LINK                                                      (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_0_INCP_LINK(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * interrupt for gen0 timer done, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_0 . GEN0_DONE
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_0_GEN0_DONE(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_0_GEN0_DONE                                                      (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_0_GEN0_DONE(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * interrupt for gen1 timer done, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_0 . GEN1_DONE
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_0_GEN1_DONE(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_0_GEN1_DONE                                                      (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_0_GEN1_DONE(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * interrupt for rate change request, write 1 to clear.    7 = 25G-KR
 * 8 = 25G-KR-S    9 = 10G-KR      13 = 1G-KX      others reserved
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_0 . AN_RATE
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_0_AN_RATE(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_0_AN_RATE                                                        (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_0_AN_RATE(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,4))


/**
 * \brief interrupt vector. All sticky
 *
 * \details
 * Register: \a LINE_KR:IRQ_VEC:IRQ_VEC_1
 */
#define LAN80XX_LINE_KR_IRQ_VEC_1                                                                   (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8043))

/**
 * \brief
 * Interrupt to indicate that a new request to configure the NP_TX
 * registers is being made. Asserted along with CMPL_ACK Interrupt if a
 * Next Page is to be transmitted. Write 1 to clear.
 *
 * \details
 * 1 :- A next page is to be transmitted next and np_tx registers are
 * requested to be configured.
 * 0 :- No Next page is to be transmitted next and the Auto-negotiation
 * would enter into Priority Resolution now.
 *
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . NP_REQ
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_NP_REQ(x)                                                      (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_NP_REQ                                                         (LAN80XX_BIT(15))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_NP_REQ(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * Interrupt Sticky bit to indicate the assertion of ack_finished signal.
 * Write 1 to clear.
 *
 * \details
 * 1 : ack_finished asserted since the last clearing of the same.
 * 0 : ack_finished is not asserted since the last clearing of the same.
 *
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . ACK_FIN
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_ACK_FIN(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),14,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_ACK_FIN                                                        (LAN80XX_BIT(14))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_ACK_FIN(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,14,1))

/**
 * \brief
 * interrupt for kr_active toggle, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . KR_ACTV
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_KR_ACTV(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),13,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_KR_ACTV                                                        (LAN80XX_BIT(13))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_KR_ACTV(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,13,1))

/**
 * \brief
 * interrupt for new LP status report, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . LPSVALID
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_LPSVALID(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),12,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_LPSVALID                                                       (LAN80XX_BIT(12))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_LPSVALID(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,12,1))

/**
 * \brief
 * interrupt for new LP coeff update, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . LPCVALID
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_LPCVALID(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),11,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_LPCVALID                                                       (LAN80XX_BIT(11))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_LPCVALID(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,11,1))

/**
 * \brief
 * interrupt for wait timer done, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . WT_DONE
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_WT_DONE(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_WT_DONE                                                        (LAN80XX_BIT(10))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_WT_DONE(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,10,1))

/**
 * \brief
 * interrupt for maxwait timer done, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . MW_DONE
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_MW_DONE(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_MW_DONE                                                        (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_MW_DONE(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * interrupt for ber_busy = 0, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . BER_BUSY_0
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_BER_BUSY_0(x)                                                  (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_BER_BUSY_0                                                     (LAN80XX_BIT(8))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_BER_BUSY_0(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * interrupt for ber_busy = 1, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . BER_BUSY_1
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_BER_BUSY_1(x)                                                  (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_BER_BUSY_1                                                     (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_BER_BUSY_1(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * interrupt for rem_ready = 0, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . REM_RDY_0
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_REM_RDY_0(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_REM_RDY_0                                                      (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_REM_RDY_0(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * interrupt for rem_ready = 1, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . REM_RDY_1
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_REM_RDY_1(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_REM_RDY_1                                                      (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_REM_RDY_1(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * interrupt for frlock = 0, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . FRLOCK_0
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_FRLOCK_0(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_FRLOCK_0                                                       (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_FRLOCK_0(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * interrupt for frlock = 1, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . FRLOCK_1
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_FRLOCK_1(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_FRLOCK_1                                                       (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_FRLOCK_1(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * interrupt for dme_viol = 0, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . DME_VIOL_0
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_DME_VIOL_0(x)                                                  (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_DME_VIOL_0                                                     (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_DME_VIOL_0(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * interrupt for dme_viol = 1, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . DME_VIOL_1
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_DME_VIOL_1(x)                                                  (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_DME_VIOL_1                                                     (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_DME_VIOL_1(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * interrupt for AN_SM = XMIT_DISABLE, write 1 to clear
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_VEC_1 . AN_XMIT_DISABLE
 */
#define  LAN80XX_F_LINE_KR_IRQ_VEC_1_AN_XMIT_DISABLE(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_KR_IRQ_VEC_1_AN_XMIT_DISABLE                                                (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_KR_IRQ_VEC_1_AN_XMIT_DISABLE(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a LINE_KR:IRQ_MASK
 *
 * Auto-Negotiation Vendor interrupt mask register
 */


/**
 * \brief interrupt mask
 *
 * \details
 * Register: \a LINE_KR:IRQ_MASK:IRQ_MASK_0
 */
#define LAN80XX_LINE_KR_IRQ_MASK_0                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8044))

/**
 * \brief
 * interrupt mask for AN_SM = TRAIN, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_0 . AN_TRAIN
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_0_AN_TRAIN(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_0_AN_TRAIN                                                      (LAN80XX_BIT(15))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_0_AN_TRAIN(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * interrupt mask for AN_SM = RATE_DET, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_0 . AN_RATE_DET
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_0_AN_RATE_DET(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),14,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_0_AN_RATE_DET                                                   (LAN80XX_BIT(14))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_0_AN_RATE_DET(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,14,1))

/**
 * \brief
 * interrupt mask for AN_SM = COMPLETE_ACK, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_0 . CMPL_ACK
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_0_CMPL_ACK(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),13,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_0_CMPL_ACK                                                      (LAN80XX_BIT(13))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_0_CMPL_ACK(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,13,1))

/**
 * \brief
 * interrupt mask for AN_SM = AN_GOOD, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_0 . AN_GOOD
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_0_AN_GOOD(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),12,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_0_AN_GOOD                                                       (LAN80XX_BIT(12))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_0_AN_GOOD(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,12,1))

/**
 * \brief
 * interrupt mask for AN link fail, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_0 . LINK_FAIL
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_0_LINK_FAIL(x)                                                  (LAN80XX_ENCODE_BITFIELD(!!(x),11,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_0_LINK_FAIL                                                     (LAN80XX_BIT(11))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_0_LINK_FAIL(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,11,1))

/**
 * \brief
 * interrupt mask for AN ABILITY_DETECT fail, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_0 . ABD_FAIL
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_0_ABD_FAIL(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_0_ABD_FAIL                                                      (LAN80XX_BIT(10))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_0_ABD_FAIL(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,10,1))

/**
 * \brief
 * interrupt mask for AN ACK_DETECT fail, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_0 . ACK_FAIL
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_0_ACK_FAIL(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_0_ACK_FAIL                                                      (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_0_ACK_FAIL(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * interrupt mask for AN NEXT_PAGE fail, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_0 . NP_FAIL
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_0_NP_FAIL(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_0_NP_FAIL                                                       (LAN80XX_BIT(8))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_0_NP_FAIL(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * interrupt mask for AN LP NEXT_PAGE received, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_0 . NP_RX
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_0_NP_RX(x)                                                      (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_0_NP_RX                                                         (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_0_NP_RX(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * interrupt mask for AN incompatible link, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_0 . INCP_LINK
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_0_INCP_LINK(x)                                                  (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_0_INCP_LINK                                                     (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_0_INCP_LINK(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * interrupt mask for gen0 timer done, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_0 . GEN0_DONE
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_0_GEN0_DONE(x)                                                  (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_0_GEN0_DONE                                                     (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_0_GEN0_DONE(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * interrupt mask for gen1 timer done, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_0 . GEN1_DONE
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_0_GEN1_DONE(x)                                                  (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_0_GEN1_DONE                                                     (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_0_GEN1_DONE(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * interrupt mask rate change request, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_0 . AN_RATE
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_0_AN_RATE(x)                                                    (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_0_AN_RATE                                                       (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_0_AN_RATE(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,0,4))


/**
 * \brief interrupt mask
 *
 * \details
 * Register: \a LINE_KR:IRQ_MASK:IRQ_MASK_1
 */
#define LAN80XX_LINE_KR_IRQ_MASK_1                                                                  (LAN80XX_IOREG(MMD_ID_LINE_KR, 0, 0x8045))

/**
 * \brief
 * Interrupt mask for NP_REQ Interrupt, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . NP_REQ
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_NP_REQ(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_NP_REQ                                                        (LAN80XX_BIT(15))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_NP_REQ(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * Interrupt mask for ACK_FIN Interrupt, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . ACK_FIN
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_ACK_FIN(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),14,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_ACK_FIN                                                       (LAN80XX_BIT(14))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_ACK_FIN(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,14,1))

/**
 * \brief
 * interrupt mask for kr_active toggle, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . KR_ACTV
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_KR_ACTV(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),13,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_KR_ACTV                                                       (LAN80XX_BIT(13))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_KR_ACTV(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,13,1))

/**
 * \brief
 * interrupt mask for new LP status report, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . LPSVALID
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_LPSVALID(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),12,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_LPSVALID                                                      (LAN80XX_BIT(12))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_LPSVALID(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,12,1))

/**
 * \brief
 * interrupt mask for new LP coeff update, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . LPCVALID
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_LPCVALID(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),11,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_LPCVALID                                                      (LAN80XX_BIT(11))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_LPCVALID(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,11,1))

/**
 * \brief
 * interrupt mask for wait timer done, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . WT_DONE
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_WT_DONE(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_WT_DONE                                                       (LAN80XX_BIT(10))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_WT_DONE(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,10,1))

/**
 * \brief
 * interrupt mask for maxwait timer done, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . MW_DONE
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_MW_DONE(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_MW_DONE                                                       (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_MW_DONE(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * interrupt mask for ber_busy = 0, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . BER_BUSY_0
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_BER_BUSY_0(x)                                                 (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_BER_BUSY_0                                                    (LAN80XX_BIT(8))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_BER_BUSY_0(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * interrupt mask for ber_busy = 1, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . BER_BUSY_1
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_BER_BUSY_1(x)                                                 (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_BER_BUSY_1                                                    (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_BER_BUSY_1(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * interrupt mask for rem_ready = 0, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . REM_RDY_0
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_REM_RDY_0(x)                                                  (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_REM_RDY_0                                                     (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_REM_RDY_0(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * interrupt mask for rem_ready = 1, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . REM_RDY_1
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_REM_RDY_1(x)                                                  (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_REM_RDY_1                                                     (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_REM_RDY_1(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * interrupt mask for frlock = 0, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . FRLOCK_0
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_FRLOCK_0(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_FRLOCK_0                                                      (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_FRLOCK_0(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * interrupt mask for frlock = 1, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . FRLOCK_1
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_FRLOCK_1(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_FRLOCK_1                                                      (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_FRLOCK_1(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * interrupt mask for dme_viol = 0, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . DME_VIOL_0
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_DME_VIOL_0(x)                                                 (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_DME_VIOL_0                                                    (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_DME_VIOL_0(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * interrupt mask for dme_viol = 1, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . DME_VIOL_1
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_DME_VIOL_1(x)                                                 (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_DME_VIOL_1                                                    (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_DME_VIOL_1(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * interrupt mask for AN_SM = XMIT_DISABLE, 1 is enable
 *
 * \details
 * Field: ::LAN80XX_LINE_KR_IRQ_MASK_1 . AN_XMIT_DISABLE
 */
#define  LAN80XX_F_LINE_KR_IRQ_MASK_1_AN_XMIT_DISABLE(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_KR_IRQ_MASK_1_AN_XMIT_DISABLE                                               (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_KR_IRQ_MASK_1_AN_XMIT_DISABLE(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,1))


#endif /* _LAN80XX_MALIBU25G_REGS_LINE_KR_H_ */
