// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN80XX_MALIBU25G_REGS_MACSEC_INGR_H_
#define LAN80XX_MALIBU25G_REGS_MACSEC_INGR_H_

#include "regs_lan80xx_common.h"

/***********************************************************************
 *
 * Target: \a MACSEC_INGR
 *
 * ARRAY(0x43b9ce0)
 *
 ***********************************************************************/

/**
 * Register Group: \a MACSEC_INGR:MACSEC_INGR_MACSEC_CTL_REGS
 *
 * MACsec Ingress and Egress wrapper control registers.
 */


/**
 * \brief Mode configuration register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_CTL_REGS:MACSEC_INGR_MACSEC_ENA_CFG
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG                                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,0xc40))

/**
 * \brief
 * MACsec clock enable.
 *
 * \details
 * 0: All clocks for MACsec block with the exception of CSR clock are
 * disabled.
 * 1: All clocks for MACsec block are enabled.
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG . CLK_ENA
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CLK_ENA(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CLK_ENA                                   (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CLK_ENA(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * MACsec software reset
 *
 * \details
 * 0: Block operates normally.
 * 1: All logic (other than CSR target) is held in reset, clocks are not
 * disabled.
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG . SW_RST
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SW_RST(x)                                 (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SW_RST                                    (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SW_RST(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * MACsec bypass enable, implemented in the MACsec Wrapper.
 *
 * \details
 * 0: MACsec IP is not bypassed in the MACsec Wrapper. MACSEC_ENA must be
 * set to 1 to enable MACsec functions.
 * 1: MACsec IP is bypassed in the MACsec Wrapper. MACsec functions are not
 * available regardless of the value of MACSEC_ENA.
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG . MACSEC_BYPASS_ENA
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA                         (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA(x)                      (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * MACsec block enable.To enable MACsec write MACSEC_ENA = 1 and
 * MACSEC_BYPASS_ENA = 0.
 *
 * \details
 * 0: MACSEC IP is not enabled.
 * 1: MACSEC IP is enabled.
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG . MACSEC_ENA
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_ENA(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_ENA                                (LAN80XX_BIT(9))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_ENA(x)                             (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * MACsec speed mode register.
 *
 * \details
 * 000: 10G
 * 001: 10G_1G
 * 101: 1G
 * 110: 1G_100M
 * 111: 1G_10M
 * others: illegal
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG . MACSEC_SPEED_MODE
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(x)                      (LAN80XX_ENCODE_BITFIELD(x,10,3))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_SPEED_MODE                         (LAN80XX_ENCODE_BITMASK(10,3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(x)                      (LAN80XX_EXTRACT_BITFIELD(x,10,3))

/**
 * \brief
 * initial Classifier Statistics RAM with all 0s
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG . CSTAT_INIT
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CSTAT_INIT(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),16,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CSTAT_INIT                                (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CSTAT_INIT(x)                             (LAN80XX_EXTRACT_BITFIELD(x,16,1))

/**
 * \brief
 * initial SA Statistics RAM with all 0s
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG . SSTAT_INIT
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SSTAT_INIT(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),17,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SSTAT_INIT                                (LAN80XX_BIT(17))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SSTAT_INIT(x)                             (LAN80XX_EXTRACT_BITFIELD(x,17,1))

/**
 * \brief
 * initial Vport Statistics RAM with all 0s
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG . VSTAT_INIT
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_VSTAT_INIT(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),18,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_VSTAT_INIT                                (LAN80XX_BIT(18))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_VSTAT_INIT(x)                             (LAN80XX_EXTRACT_BITFIELD(x,18,1))

/**
 * \brief
 * Classifier Statistics RAM initialization in progress
 *
 * \details
 * 1 = in progress
 * 0 = not in progress
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG . CSTAT_INIT_BUSY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CSTAT_INIT_BUSY(x)                        (LAN80XX_ENCODE_BITFIELD(!!(x),20,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CSTAT_INIT_BUSY                           (LAN80XX_BIT(20))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CSTAT_INIT_BUSY(x)                        (LAN80XX_EXTRACT_BITFIELD(x,20,1))

/**
 * \brief
 * SA Statistics RAM initialization in progress
 *
 * \details
 * 1 = in progress
 * 0 = not in progress
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG . SSTAT_INIT_BUSY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SSTAT_INIT_BUSY(x)                        (LAN80XX_ENCODE_BITFIELD(!!(x),21,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SSTAT_INIT_BUSY                           (LAN80XX_BIT(21))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SSTAT_INIT_BUSY(x)                        (LAN80XX_EXTRACT_BITFIELD(x,21,1))

/**
 * \brief
 * Vport Statistics RAM initialization in progress
 *
 * \details
 * 1 = in progress
 * 0 = not in progress
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG . VSTAT_INIT_BUSY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_VSTAT_INIT_BUSY(x)                        (LAN80XX_ENCODE_BITFIELD(!!(x),22,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_VSTAT_INIT_BUSY                           (LAN80XX_BIT(22))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_VSTAT_INIT_BUSY(x)                        (LAN80XX_EXTRACT_BITFIELD(x,22,1))


/**
 * \brief MACsec control configuration register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_CTL_REGS:MACSEC_INGR_MACSEC_CTL_CFG
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_CFG                                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,0xc41))

/**
 * \brief
 * Source port used for all MAC control frames
 *
 * \details
 * 00: Common port
 * 01: Reserved port
 * 10: Controlled port
 * 11: Uncontrolled port
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_CFG . MAC_CTRL_FRAMES_SRC_PORT
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_CFG_MAC_CTRL_FRAMES_SRC_PORT(x)               (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_CFG_MAC_CTRL_FRAMES_SRC_PORT                  (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_CFG_MAC_CTRL_FRAMES_SRC_PORT(x)               (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * Source port used for all MAC data frames
 *
 * \details
 * 00: Common port
 * 01: Reserved port
 * 10: Controlled port
 * 11: Uncontrolled port
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_CFG . MAC_DATA_FRAMES_SRC_PORT
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_CFG_MAC_DATA_FRAMES_SRC_PORT(x)               (LAN80XX_ENCODE_BITFIELD(x,2,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_CFG_MAC_DATA_FRAMES_SRC_PORT                  (LAN80XX_ENCODE_BITMASK(2,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_CFG_MAC_DATA_FRAMES_SRC_PORT(x)               (LAN80XX_EXTRACT_BITFIELD(x,2,2))

/**
 * \brief
 * Ingress packets failing security check are transmitted to the Host with
 * corrupted FCS, which can be either an inverted FCS or a fault code to
 * debug the security failing packet.The format of the fault code is as
 * follows:{1'b0, pkt_tx_sa_hit (1-bit), pkt_tx_sa_index(6-bits),
 * pkt_tx_global_stat_event (14-bits),pkt_tx_stat_event (10-bits)};The 32nd
 * bit is a reserved bit used by theMAC to make sure that the FCS is
 * corrupted.
 *
 * \details
 * 0: Invert FCS for ingress packets failing security checks
 * 1: Insert security fault code for ingress packets failing security check
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_CFG . ENA_SEC_FAIL_DEBUG_CODE_IN_FCS
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_CFG_ENA_SEC_FAIL_DEBUG_CODE_IN_FCS(x)         (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_CFG_ENA_SEC_FAIL_DEBUG_CODE_IN_FCS            (LAN80XX_BIT(4))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_CFG_ENA_SEC_FAIL_DEBUG_CODE_IN_FCS(x)         (LAN80XX_EXTRACT_BITFIELD(x,4,1))


/**
 * \brief Error sticky bits of MACsec register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_CTL_REGS:MACSEC_INGR_MACSEC_STICKY
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY                                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc42))

/**
 * \brief
 * Indicates packet drop from classification logic. Write one to clear.
 *
 * \details
 * 0: No packet drop from classification logic
 * 1: Indicates packet drop from classification logic
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY . DROP_CLASS_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_DROP_CLASS_STICKY(x)                       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_DROP_CLASS_STICKY                          (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_DROP_CLASS_STICKY(x)                       (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Indicates packet drop from post-processor logic. Write one to clear.
 *
 * \details
 * 0: No packet drop from post-processor logic
 * 1: Indicates packet drop from post-processor logic
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY . DROP_PP_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_DROP_PP_STICKY(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_DROP_PP_STICKY                             (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_DROP_PP_STICKY(x)                          (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Indicates packet drop from MTU checking logic. Write one to clear.
 *
 * \details
 * 0: No packet drop from MTU checking logic
 * 1: Indicates packet drop from MTU checking logic
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY . DROP_MTU_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_DROP_MTU_STICKY(x)                         (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_DROP_MTU_STICKY                            (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_DROP_MTU_STICKY(x)                         (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Indicates interrupt from MACsec IP. Write one to clear.
 *
 * \details
 * 0: No interrupt from MACsec IP
 * 1: Indicates interrupt sticky from MACsec IP
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY . ENG_IRQ_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_ENG_IRQ_STICKY(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_ENG_IRQ_STICKY                             (LAN80XX_BIT(3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_ENG_IRQ_STICKY(x)                          (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Indicates packet drop from consistency checking logic (not present in
 * egress). Write one to clear.
 *
 * \details
 * 0: No packet drop from consistency checking logic
 * 1: Indicates packet drop from consistency checking logic
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY . DROP_CC_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_DROP_CC_STICKY(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_DROP_CC_STICKY                             (LAN80XX_BIT(4))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_DROP_CC_STICKY(x)                          (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Indicates pkt64to128 FIFO overflowThe FIFO block will still work
 * properly after abort marking a frame. Most likely cause of this is a
 * misconfiguration. Write one to clear.
 *
 * \details
 * 0: No overflow in pkt64to128 FIFO
 * 1: pkt64to128 FIFO overflowed at least once
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY . PKT64TO128_FIFO_OVERFLOW_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_PKT64TO128_FIFO_OVERFLOW_STICKY(x)         (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_PKT64TO128_FIFO_OVERFLOW_STICKY            (LAN80XX_BIT(5))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_PKT64TO128_FIFO_OVERFLOW_STICKY(x)         (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Indicates ECC error in SA store RAM while reading SA. Write one to
 * clear.
 *
 * \details
 * 0: No ECC error
 * 1: ECC error occurred at least once
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY . SA_STORE_RAM_INTEGRITY_ERROR_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_SA_STORE_RAM_INTEGRITY_ERROR_STICKY(x)     (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_SA_STORE_RAM_INTEGRITY_ERROR_STICKY        (LAN80XX_BIT(6))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_SA_STORE_RAM_INTEGRITY_ERROR_STICKY(x)     (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Indicates ECC error in STAT RAM while reading statistics. Write one to
 * clear.
 *
 * \details
 * 0: No ECC error
 * 1: ECC error occurred at least once
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY . STAT_RAM_INTEGRITY_ERROR_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_STAT_RAM_INTEGRITY_ERROR_STICKY(x)         (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_STAT_RAM_INTEGRITY_ERROR_STICKY            (LAN80XX_BIT(7))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_STAT_RAM_INTEGRITY_ERROR_STICKY(x)         (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * Indicates ECC interrupt status. Write one to clear.
 *
 * \details
 * 0: No ECC interrupt
 * 1: ECC interrupt
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY . ECC_INTERRUPT_STATUS
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_ECC_INTERRUPT_STATUS(x)                    (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_ECC_INTERRUPT_STATUS                       (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_ECC_INTERRUPT_STATUS(x)                    (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Classifier Statistics RAM initialization done status bit.
 *
 * \details
 * This bit is set by initialization done event. Write one to clear.
 * 0 = interrupt not pending
 * 1 = interrupt pending

 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY . CSTAT_INIT_DONE_INTERRUPT_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_CSTAT_INIT_DONE_INTERRUPT_STICKY(x)        (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_CSTAT_INIT_DONE_INTERRUPT_STICKY           (LAN80XX_BIT(9))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_CSTAT_INIT_DONE_INTERRUPT_STICKY(x)        (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * SA Statistics RAM initialization done status bit.
 *
 * \details
 * This bit is set by initialization done event. Write one to clear.
 * 0 = interrupt not pending
 * 1 = interrupt pending

 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY . SSTAT_INIT_DONE_INTERRUPT_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_SSTAT_INIT_DONE_INTERRUPT_STICKY(x)        (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_SSTAT_INIT_DONE_INTERRUPT_STICKY           (LAN80XX_BIT(10))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_SSTAT_INIT_DONE_INTERRUPT_STICKY(x)        (LAN80XX_EXTRACT_BITFIELD(x,10,1))

/**
 * \brief
 * Vport Statistics RAM initialization done status bit.
 *
 * \details
 * This bit is set by initialization done event. Write one to clear.
 * 0 = interrupt not pending
 * 1 = interrupt pending

 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY . VSTAT_INIT_DONE_INTERRUPT_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_VSTAT_INIT_DONE_INTERRUPT_STICKY(x)        (LAN80XX_ENCODE_BITFIELD(!!(x),11,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_VSTAT_INIT_DONE_INTERRUPT_STICKY           (LAN80XX_BIT(11))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_VSTAT_INIT_DONE_INTERRUPT_STICKY(x)        (LAN80XX_EXTRACT_BITFIELD(x,11,1))


/**
 * \brief Interrupt mask sticky bits register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_CTL_REGS:MACSEC_INGR_MACSEC_STICKY_MASK
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK                                          (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc43))

/**
 * \brief
 * Interrupt mask for DROP_CLASS_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK . DROP_CLASS_STICKY_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_DROP_CLASS_STICKY_MASK(x)             (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_DROP_CLASS_STICKY_MASK                (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_DROP_CLASS_STICKY_MASK(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Interrupt mask for DROP_PP_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK . DROP_PP_STICKY_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_DROP_PP_STICKY_MASK(x)                (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_DROP_PP_STICKY_MASK                   (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_DROP_PP_STICKY_MASK(x)                (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Interrupt mask for DROP_MTU_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK . DROP_MTU_STICKY_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_DROP_MTU_STICKY_MASK(x)               (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_DROP_MTU_STICKY_MASK                  (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_DROP_MTU_STICKY_MASK(x)               (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Interrupt mask for ENG_IRQ_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK . ENG_IRQ_STICKY_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_ENG_IRQ_STICKY_MASK(x)                (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_ENG_IRQ_STICKY_MASK                   (LAN80XX_BIT(3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_ENG_IRQ_STICKY_MASK(x)                (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Interrupt mask for DROP_CC_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK . DROP_CC_STICKY_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_DROP_CC_STICKY_MASK(x)                (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_DROP_CC_STICKY_MASK                   (LAN80XX_BIT(4))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_DROP_CC_STICKY_MASK(x)                (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Interrupt mask for PKT64TO128_FIFO_OVERFLOW_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK . PKT64TO128_FIFO_OVERFLOW_STICKY_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_PKT64TO128_FIFO_OVERFLOW_STICKY_MASK(x) (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_PKT64TO128_FIFO_OVERFLOW_STICKY_MASK  (LAN80XX_BIT(5))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_PKT64TO128_FIFO_OVERFLOW_STICKY_MASK(x) (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Interrupt mask for SA_STORE_RAM_INTEGRITY_ERROR_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK . SA_STORE_RAM_INTEGRITY_ERROR_STICKY_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_SA_STORE_RAM_INTEGRITY_ERROR_STICKY_MASK(x) (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_SA_STORE_RAM_INTEGRITY_ERROR_STICKY_MASK (LAN80XX_BIT(6))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_SA_STORE_RAM_INTEGRITY_ERROR_STICKY_MASK(x) (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Interrupt mask for STAT_RAM_INTEGRITY_ERROR_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK . STAT_RAM_INTEGRITY_ERROR_STICKY_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_STAT_RAM_INTEGRITY_ERROR_STICKY_MASK(x) (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_STAT_RAM_INTEGRITY_ERROR_STICKY_MASK  (LAN80XX_BIT(7))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_STAT_RAM_INTEGRITY_ERROR_STICKY_MASK(x) (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * Interrupt mask for ECC_INTERRUPT_STATUS
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK . ECC_INTERRUPT_STATUS_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_ECC_INTERRUPT_STATUS_MASK(x)          (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_ECC_INTERRUPT_STATUS_MASK             (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_ECC_INTERRUPT_STATUS_MASK(x)          (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Interrupt mask for CSTAT_INIT_DONE_INTERRUPT_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK . CSTAT_INIT_DONE_INTERRUPT_STICKY_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_CSTAT_INIT_DONE_INTERRUPT_STICKY_MASK(x) (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_CSTAT_INIT_DONE_INTERRUPT_STICKY_MASK (LAN80XX_BIT(9))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_CSTAT_INIT_DONE_INTERRUPT_STICKY_MASK(x) (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * Interrupt mask for SSTAT_INIT_DONE_INTERRUPT_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK . SSTAT_INIT_DONE_INTERRUPT_STICKY_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_SSTAT_INIT_DONE_INTERRUPT_STICKY_MASK(x) (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_SSTAT_INIT_DONE_INTERRUPT_STICKY_MASK (LAN80XX_BIT(10))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_SSTAT_INIT_DONE_INTERRUPT_STICKY_MASK(x) (LAN80XX_EXTRACT_BITFIELD(x,10,1))

/**
 * \brief
 * Interrupt mask for VSTAT_INIT_DONE_INTERRUPT_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK . VSTAT_INIT_DONE_INTERRUPT_STICKY_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_VSTAT_INIT_DONE_INTERRUPT_STICKY_MASK(x) (LAN80XX_ENCODE_BITFIELD(!!(x),11,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_VSTAT_INIT_DONE_INTERRUPT_STICKY_MASK (LAN80XX_BIT(11))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_STICKY_MASK_VSTAT_INIT_DONE_INTERRUPT_STICKY_MASK(x) (LAN80XX_EXTRACT_BITFIELD(x,11,1))


/**
 * \brief MACsec ingress latency configuration register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_CTL_REGS:MACSEC_INGR_MACSEC_IGR_LATENCY_CFG
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_IGR_LATENCY_CFG                                      (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc44))

/**
 * \brief
 * Fixed latency of ingress MACsec blockThe minimum latency the frame will
 * undergo, specified in terms of enabled clocks.Variable latency of a
 * frame is calculated by measuring the actual latency of the SOF and
 * subtracting fixed latency.  Var_latency = measured latency - fixed
 * latencyThe maximum possible variable latency is MAX_LATENCY - FIXED
 * LATENCY.
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_IGR_LATENCY_CFG . IGR_MSEC_LATENCY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_IGR_LATENCY_CFG_IGR_MSEC_LATENCY(x)               (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_IGR_LATENCY_CFG_IGR_MSEC_LATENCY                  (LAN80XX_ENCODE_BITMASK(0,6))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_IGR_LATENCY_CFG_IGR_MSEC_LATENCY(x)               (LAN80XX_EXTRACT_BITFIELD(x,0,6))

/**
 * \brief
 * Maximum latency of ingress MACsec blockThe maximum latency the frame can
 * undergo, specified in terms of enabled clocks.Variable latency of a
 * frame is calculated by measuring the actual latency of the SOF and
 * subtracting fixed latency.  Var_latency = measured latency - fixed
 * latencyThe maximum possible variable latency is MAX_LATENCY - FIXED
 * LATENCY.If a frame's SOF is not seen in the FIXED LATENCY-to-MAX_LATENCY
 * window, the frame is deemed to have been dropped within the MACsec
 * block.
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_IGR_LATENCY_CFG . IGR_MSEC_MAX_LATENCY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_IGR_LATENCY_CFG_IGR_MSEC_MAX_LATENCY(x)           (LAN80XX_ENCODE_BITFIELD(x,6,6))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_IGR_LATENCY_CFG_IGR_MSEC_MAX_LATENCY              (LAN80XX_ENCODE_BITMASK(6,6))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_IGR_LATENCY_CFG_IGR_MSEC_MAX_LATENCY(x)           (LAN80XX_EXTRACT_BITFIELD(x,6,6))


/**
 * \brief MACsec IP debug register read/write address.
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_CTL_REGS:MACSEC_INGR_MACSEC_DEBUG_REG_ADDR
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG_REG_ADDR                                       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc45))

/**
 * \brief
 * MACsec IP debug register read/write address.To access the register first
 * write the address then read or write the Data.
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG_REG_ADDR . MACSEC_DEBUG_REG_ADDR
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG_REG_ADDR_MACSEC_DEBUG_REG_ADDR(x)           (x)
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG_REG_ADDR_MACSEC_DEBUG_REG_ADDR              (0xFFFFFFFFU)
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG_REG_ADDR_MACSEC_DEBUG_REG_ADDR(x)           (x)


/**
 * \brief MACsec IP debug register read/write Data
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_CTL_REGS:MACSEC_INGR_MACSEC_DEBUG_REG_DATA
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG_REG_DATA                                       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc46))

/**
 * \brief
 * MACsec IP debug register read/write Data.To access the register first
 * write the address then read or write the Data.
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG_REG_DATA . MACSEC_DEBUG_REG_DATA
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG_REG_DATA_MACSEC_DEBUG_REG_DATA(x)           (x)
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG_REG_DATA_MACSEC_DEBUG_REG_DATA              (0xFFFFFFFFU)
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG_REG_DATA_MACSEC_DEBUG_REG_DATA(x)           (x)

/**
 * Register Group: \a MACSEC_INGR:MACSEC_INGR_MACSEC_DEBUG
 *
 * MACSEC debug registers
 */


/**
 * \brief Place holder, for latched debug data
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_DEBUG:MACSEC_INGR_MACSEC_DEBUG0
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG0                                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc48))

/**
 * \brief
 * Place holder, for latched debug data
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG0 . MACSEC_DEBUG0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG0_MACSEC_DEBUG0(x)                           (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG0_MACSEC_DEBUG0                              (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG0_MACSEC_DEBUG0(x)                           (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Place holder, for latched debug data
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_DEBUG:MACSEC_INGR_MACSEC_DEBUG1
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG1                                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc49))

/**
 * \brief
 * Place holder, for latched debug data
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG1 . MACSEC_DEBUG1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG1_MACSEC_DEBUG1(x)                           (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG1_MACSEC_DEBUG1                              (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG1_MACSEC_DEBUG1(x)                           (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Place holder, for latched debug data
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_DEBUG:MACSEC_INGR_MACSEC_DEBUG2
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG2                                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc4a))

/**
 * \brief
 * Place holder, for latched debug data
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG2 . MACSEC_DEBUG2
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG2_MACSEC_DEBUG2(x)                           (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG2_MACSEC_DEBUG2                              (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG2_MACSEC_DEBUG2(x)                           (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Place holder, for latched debug data
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_DEBUG:MACSEC_INGR_MACSEC_DEBUG3
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG3                                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc4b))

/**
 * \brief
 * Place holder, for latched debug data
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG3 . MACSEC_DEBUG3
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG3_MACSEC_DEBUG3(x)                           (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG3_MACSEC_DEBUG3                              (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG3_MACSEC_DEBUG3(x)                           (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Place holder, for latched debug data
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_DEBUG:MACSEC_INGR_MACSEC_DEBUG4
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG4                                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc4c))

/**
 * \brief
 * Place holder, for latched debug data
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG4 . MACSEC_DEBUG4
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG4_MACSEC_DEBUG4(x)                           (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG4_MACSEC_DEBUG4                              (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG4_MACSEC_DEBUG4(x)                           (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Place holder, for latched debug data
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_DEBUG:MACSEC_INGR_MACSEC_DEBUG5
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG5                                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc4d))

/**
 * \brief
 * Place holder, for latched debug data
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG5 . MACSEC_DEBUG5
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG5_MACSEC_DEBUG5(x)                           (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG5_MACSEC_DEBUG5                              (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG5_MACSEC_DEBUG5(x)                           (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Place holder, for latched debug data
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_DEBUG:MACSEC_INGR_MACSEC_DEBUG6
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG6                                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc4e))

/**
 * \brief
 * Place holder, for latched debug data
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG6 . MACSEC_DEBUG6
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG6_MACSEC_DEBUG6(x)                           (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG6_MACSEC_DEBUG6                              (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG6_MACSEC_DEBUG6(x)                           (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Place holder, for trigger condition
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_DEBUG:MACSEC_INGR_MACSEC_DEBUG7
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG7                                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc4f))

/**
 * \brief
 * Place holder, for trigger condition
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG7 . MACSEC_DEBUG7
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG7_MACSEC_DEBUG7(x)                           (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG7_MACSEC_DEBUG7                              (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG7_MACSEC_DEBUG7(x)                           (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC
 *
 * MACSEC ECC registers
 */


/**
 * \brief MACSEC ECC Control Register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_CTL
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL                                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc50))

/**
 * \brief
 * Disable ECC decoder features
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL . MACSEC_ECC_EN_CLR
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_ECC_EN_CLR(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),16,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_ECC_EN_CLR                         (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_ECC_EN_CLR(x)                      (LAN80XX_EXTRACT_BITFIELD(x,16,1))

/**
 * \brief
 * Reset error counters
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL . MACSEC_CNTRST
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_CNTRST(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_CNTRST                             (LAN80XX_BIT(3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_CNTRST(x)                          (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Soft reset ECC controller core logic
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL . MACSEC_SWRST
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_SWRST(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_SWRST                              (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_SWRST(x)                           (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * initial SRAM with all 0s
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL . MACSEC_INIT
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_INIT(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_INIT                               (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_INIT(x)                            (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Enable ECC decoder features
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL . MACSEC_ECC_EN_SET
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_ECC_EN_SET(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_ECC_EN_SET                         (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_CTL_MACSEC_ECC_EN_SET(x)                      (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MACSEC ECC Status Register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_SR
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_SR                                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc51))

/**
 * \brief
 * SRAM initialization in progress
 *
 * \details
 * 1 = in progress
 * 0 = not in progress
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_SR . MACSEC_INIT_BUSY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_SR_MACSEC_INIT_BUSY(x)                        (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_SR_MACSEC_INIT_BUSY                           (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_SR_MACSEC_INIT_BUSY(x)                        (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * ECC decoder features are currently enabled
 *
 * \details
 * 1 = enabled
 * 0 = not enabled
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_SR . MACSEC_ECC_EN
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_SR_MACSEC_ECC_EN(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_SR_MACSEC_ECC_EN                              (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_SR_MACSEC_ECC_EN(x)                           (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MACSEC ECC Initialization Done Interrupt Enable register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_EN
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_EN                                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc54))

/**
 * \brief
 * initialization done interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_EN . MACSEC_INIT_DONE_INTR_EN
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_EN_MACSEC_INIT_DONE_INTR_EN(x) (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_EN_MACSEC_INIT_DONE_INTR_EN    (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_EN_MACSEC_INIT_DONE_INTR_EN(x) (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MACSEC ECC Initialization Done Interrupt Status register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_STS
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_STS                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc55))

/**
 * \brief
 * initialization done status bit
 *
 * \details
 * this bit is set by initialization done event, write 1 will clear this
 * bit
 * 0 = interrupt not pending
 * 1 = interrupt pending

 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_STS . MACSEC_INIT_DONE_INTR_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_STS_MACSEC_INIT_DONE_INTR_STICKY(x) (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_STS_MACSEC_INIT_DONE_INTR_STICKY (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_STS_MACSEC_INIT_DONE_INTR_STICKY(x) (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MACSEC ECC Interrupt Enable Register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_INTR_EN
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN                                          (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc56))

/**
 * \brief
 * Lane 3 interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN . MACSEC_LN3_INTR_EN
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN_MACSEC_LN3_INTR_EN(x)                 (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN_MACSEC_LN3_INTR_EN                    (LAN80XX_BIT(3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN_MACSEC_LN3_INTR_EN(x)                 (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Lane 2 interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN . MACSEC_LN2_INTR_EN
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN_MACSEC_LN2_INTR_EN(x)                 (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN_MACSEC_LN2_INTR_EN                    (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN_MACSEC_LN2_INTR_EN(x)                 (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Lane 1 interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN . MACSEC_LN1_INTR_EN
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN_MACSEC_LN1_INTR_EN(x)                 (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN_MACSEC_LN1_INTR_EN                    (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN_MACSEC_LN1_INTR_EN(x)                 (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Lane 0 interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN . MACSEC_LN0_INTR_EN
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN_MACSEC_LN0_INTR_EN(x)                 (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN_MACSEC_LN0_INTR_EN                    (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_EN_MACSEC_LN0_INTR_EN(x)                 (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MACSEC ECC Interrupt Status Register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_INTR_STS
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS                                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc57))

/**
 * \brief
 * Lane 3 interrupt status
 *
 * \details
 * 1 = interrupt is pending
 * 0 = interrupt is not pending
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS . MACSEC_LN3_INTR_STS
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS_MACSEC_LN3_INTR_STS(x)               (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS_MACSEC_LN3_INTR_STS                  (LAN80XX_BIT(3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS_MACSEC_LN3_INTR_STS(x)               (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Lane 2 interrupt status
 *
 * \details
 * 1 = interrupt is pending
 * 0 = interrupt is not pending
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS . MACSEC_LN2_INTR_STS
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS_MACSEC_LN2_INTR_STS(x)               (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS_MACSEC_LN2_INTR_STS                  (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS_MACSEC_LN2_INTR_STS(x)               (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Lane 1 interrupt status
 *
 * \details
 * 1 = interrupt is pending
 * 0 = interrupt is not pending
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS . MACSEC_LN1_INTR_STS
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS_MACSEC_LN1_INTR_STS(x)               (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS_MACSEC_LN1_INTR_STS                  (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS_MACSEC_LN1_INTR_STS(x)               (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Lane 0 interrupt status
 *
 * \details
 * 1 = interrupt is pending
 * 0 = interrupt is not pending
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS . MACSEC_LN0_INTR_STS
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS_MACSEC_LN0_INTR_STS(x)               (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS_MACSEC_LN0_INTR_STS                  (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_INTR_STS_MACSEC_LN0_INTR_STS(x)               (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MACSEC ECC Lane Fault Configuration Register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_LANE_FCR
 *
 * @param ri Register: MACSEC_INGR_MACSEC_ECC_LANE_FCR (??), 0-3
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FCR(ri)                                     (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc60 + (ri)))

/**
 * \brief
 * Select double bit or single bit fault injection
 *
 * \details
 * if corresponding MACSEC_LN_FAULT_EN is set
 * 1 = inject double bit fault
 * 0 = inject single bit fault
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FCR . MACSEC_FAULT_DBL
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FCR_MACSEC_FAULT_DBL(x)                  (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FCR_MACSEC_FAULT_DBL                     (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FCR_MACSEC_FAULT_DBL(x)                  (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * enable fault injection controller
 *
 * \details
 * 1 = enabled
 * 0 = not enabled
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FCR . MACSEC_FAULT_EN
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FCR_MACSEC_FAULT_EN(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FCR_MACSEC_FAULT_EN                      (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FCR_MACSEC_FAULT_EN(x)                   (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MACSEC ECC Lane Error Address Register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_LANE_EADDR
 *
 * @param ri Register: MACSEC_INGR_MACSEC_ECC_LANE_EADDR (??), 0-3
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_EADDR(ri)                                   (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc64 + (ri)))

/**
 * \brief
 * address of last error (sec or ded) occurred
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_EADDR . MACSEC_ERR_ADDR
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_EADDR_MACSEC_ERR_ADDR(x)                 (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_EADDR_MACSEC_ERR_ADDR                    (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_EADDR_MACSEC_ERR_ADDR(x)                 (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief MACSEC ECC Lane Error Data Pointer Register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_LANE_EDPTR
 *
 * @param ri Register: MACSEC_INGR_MACSEC_ECC_LANE_EDPTR (??), 0-3
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_EDPTR(ri)                                   (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc65 + (ri)))

/**
 * \brief
 * bit number of corrected bit, read back 0 if DED.
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_EDPTR . MACSEC_ERR_DPTR
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_EDPTR_MACSEC_ERR_DPTR(x)                 (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_EDPTR_MACSEC_ERR_DPTR                    (LAN80XX_ENCODE_BITMASK(0,6))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_EDPTR_MACSEC_ERR_DPTR(x)                 (LAN80XX_EXTRACT_BITFIELD(x,0,6))


/**
 * \brief MACSEC ECC Lane SEC Count Register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_LANE_SCNT
 *
 * @param ri Register: MACSEC_INGR_MACSEC_ECC_LANE_SCNT (??), 0-3
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_SCNT(ri)                                    (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc66 + (ri)))

/**
 * \brief
 * number of single bit errors.this counter can be cleared by MACSEC_SWRST
 * or MACSEC_CNTRST
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_SCNT . MACSEC_SEC_CNT
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_SCNT_MACSEC_SEC_CNT(x)                   (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_SCNT_MACSEC_SEC_CNT                      (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_SCNT_MACSEC_SEC_CNT(x)                   (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief MACSEC ECC Lane DED Count Register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_LANE_DCNT
 *
 * @param ri Register: MACSEC_INGR_MACSEC_ECC_LANE_DCNT (??), 0-3
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_DCNT(ri)                                    (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc67 + (ri)))

/**
 * \brief
 * number of double bit errors.this counter can be cleared by MACSEC_SWRST
 * or MACSEC_CNTRST
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_DCNT . MACSEC_DED_CNT
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_DCNT_MACSEC_DED_CNT(x)                   (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_DCNT_MACSEC_DED_CNT                      (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_DCNT_MACSEC_DED_CNT(x)                   (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief MACSEC ECC Lane Interrupt Enable Register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN
 *
 * @param ri Register: MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN (??), 0-3
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN(ri)                                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc68 + (ri)))

/**
 * \brief
 * fault read interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN . MACSEC_FAULT_READ_INTR_EN
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN_MACSEC_FAULT_READ_INTR_EN(x)     (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN_MACSEC_FAULT_READ_INTR_EN        (LAN80XX_BIT(3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN_MACSEC_FAULT_READ_INTR_EN(x)     (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Double Error Detection interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN . MACSEC_DED_INTR_EN
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN_MACSEC_DED_INTR_EN(x)            (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN_MACSEC_DED_INTR_EN               (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN_MACSEC_DED_INTR_EN(x)            (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Single Error Correction interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN . MACSEC_SEC_INTR_EN
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN_MACSEC_SEC_INTR_EN(x)            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN_MACSEC_SEC_INTR_EN               (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN_MACSEC_SEC_INTR_EN(x)            (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MACSEC ECC Lane Interrupt Status Register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS
 *
 * @param ri Register: MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS (??), 0-3
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS(ri)                                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc69 + (ri)))

/**
 * \brief
 * fault read interrupt status
 *
 * \details
 * this bit is set by fault read event, write 1 will clear this bit
 * 1 = interrupt is pending
 * 0 = no interrupt is pending
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS . MACSEC_FAULT_READ_INTR_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS_MACSEC_FAULT_READ_INTR_STICKY(x) (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS_MACSEC_FAULT_READ_INTR_STICKY   (LAN80XX_BIT(3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS_MACSEC_FAULT_READ_INTR_STICKY(x) (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Double Error Detection interrupt status
 *
 * \details
 * this bit is set by double-bit detect event, write 1 will clear this bit
 * 1 = interrupt is pending
 * 0 = no interrupt is pending
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS . MACSEC_DED_INTR_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS_MACSEC_DED_INTR_STICKY(x)       (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS_MACSEC_DED_INTR_STICKY          (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS_MACSEC_DED_INTR_STICKY(x)       (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Single Error Correction interrupt status
 *
 * \details
 * this bit is set by single-bit error event, write 1 will clear this bit
 * 1 = interrupt is pending
 * 0 = no interrupt is pending
 *
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS . MACSEC_SEC_INTR_STICKY
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS_MACSEC_SEC_INTR_STICKY(x)       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS_MACSEC_SEC_INTR_STICKY          (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS_MACSEC_SEC_INTR_STICKY(x)       (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MACSEC ECC Lane Fault Address Register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_LANE_FADDR
 *
 * @param ri Register: MACSEC_INGR_MACSEC_ECC_LANE_FADDR (??), 0-3
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FADDR(ri)                                   (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc6c + (ri)))

/**
 * \brief
 * the address to inject the fault
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FADDR . MACSEC_FAULT_ADDR
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FADDR_MACSEC_FAULT_ADDR(x)               (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FADDR_MACSEC_FAULT_ADDR                  (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FADDR_MACSEC_FAULT_ADDR(x)               (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief MACSEC ECC Lane Fault Data Pointer Register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_INGR_MACSEC_ECC:MACSEC_INGR_MACSEC_ECC_LANE_FDPTR
 *
 * @param ri Register: MACSEC_INGR_MACSEC_ECC_LANE_FDPTR (??), 0-3
 */
#define LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FDPTR(ri)                                   (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xc6d + (ri)))

/**
 * \brief
 * the bit number to inject the fault
 *
 * \details
 * Field: ::LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FDPTR . MACSEC_FAULT_DPTR
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FDPTR_MACSEC_FAULT_DPTR(x)               (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FDPTR_MACSEC_FAULT_DPTR                  (LAN80XX_ENCODE_BITMASK(0,6))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC_LANE_FDPTR_MACSEC_FAULT_DPTR(x)               (LAN80XX_EXTRACT_BITFIELD(x,0,6))

/**
 * \brief
 * Context Control Register
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP161_EIP62_EIP62_REGISTERS:MACSEC_INGR_CORE_EIP62_CONTEXT_CTRL
 */

#define LAN80XX_MACSEC_INGR_CORE_CONTEXT_CTRL                                                       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x3D02))

/**
 *\brief
 *Select sequence number threshold mode
 *
 *\details
 *  1b = the E8 is triggered only when the next packet number equals the threshold value in the threshold register.
 *  0b =  the E8 is triggered when the next packet number equals or exceeds the threshold value in the threshold register
 *
 * Field: ::LAN80XX_MACSEC_INGR_CORE_CONTEXT_CTRL . PKT_NUM_THR_MODE_0
 */

#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_CONTEXT_CTRL_PKT_NUM_THR_MODE_0(x)                       (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_CONTEXT_CTRL_PKT_NUM_THR_MODE_0                          (LAN80XX_BIT(10))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_CONTEXT_CTRL_PKT_NUM_THR_MODE_0(x)                       (LAN80XX_EXTRACT_BITFIELD(x,10,1))

/**
 * \brief
 * Ethertype field of MACsec.
 *
 * \details
 * This field is inserted in the SecTAG when processing a MACsec outbound token
 *
 * * Field: ::LAN80XX_MACSEC_INGR_CORE_CONTEXT_CTRL . MACSEC_ETHERTYPE_0
 */

#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_CONTEXT_CTRL_MACSEC_ETHERTYPE_0(x)                       (LAN80XX_ENCODE_BITFIELD(x,16,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_CONTEXT_CTRL_MACSEC_ETHERTYPE_0                          (LAN80XX_ENCODE_BITMASK(16,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_CONTEXT_CTRL_MACSEC_ETHERTYPE_0(x)                       (LAN80XX_EXTRACT_BITFIELD(x,16,16))

/**
 * \brief
 * Interrupt Control/Status Register.
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP161_EIP62_EIP62_REGISTERS:MACSEC_INGR_CORE_EIP62_INT_CTRL_STAT
 */

#define LAN80XX_MACSEC_INGR_CORE_INT_CTRL_STAT                                                      (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x3D04))
/**
 * \brief
 * Transform record 0 (0 - 64 SAs)
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:TRANSFORM_RECORDS_PAGE0 .XFORM_REC_X_W0
 */
#define LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE0_XFORM_REC_X_W0(ri)                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x0000 | (ri * 32))))

/**
 * \brief
 * Transform record 0 (65 - 127 SAs)
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:TRANSFORM_RECORDS_PAGE1 .XFORM_REC_X_W0
 */
#define LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE1_XFORM_REC_X_W0(ri)                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x4000 | (ri * 32))))

/**
 * \brief
 * Transform record 14 (0 - 64 SAs)
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:TRANSFORM_RECORDS_PAGE0 .XFORM_REC_X_W14
 */
#define LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE0_XFORM_REC_X_W14(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x000E | (ri * 32))))
/**
 * \brief
 * Transform record 15 (0 - 64 SAs)
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:TRANSFORM_RECORDS_PAGE0 .XFORM_REC_X_W15
 */
#define LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE0_XFORM_REC_X_W15(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x000F | (ri * 32))))

/**
 * \brief
 * Transform record 14 (65 - 127 SAs)
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:TRANSFORM_RECORDS_PAGE1 .XFORM_REC_X_W14
 */
#define LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE1_XFORM_REC_X_W14(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x400E | (ri * 32))))
/**
 * \brief
 * Transform record 14 (65 - 127 SAs)
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:TRANSFORM_RECORDS_PAGE1 .XFORM_REC_X_W15
 */
#define LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE1_XFORM_REC_X_W15(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x400F | (ri * 32))))

/**
 * \brief
 * MISC_CONTROL register
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_VARIOUS_CONTROL_REGS:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_VARIOUS_CONTROL_REGS
 *
 */

#define LAN80XX_MACSEC_INGR_CORE_MISC_CONTROL                                                       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1E5F))

/**
 * \brief
 * Alias to lower 8 bits of mc_latency_fix value
 *
 * \details
 *
 * Field: ::LAN80XX_MACSEC_INGR_CORE_MISC_CONTROL . MACSEC_MC_LATENCY_FIX_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_MC_LATENCY_FIX_1(x)                  (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_MC_LATENCY_FIX_1                     (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_MC_LATENCY_FIX_1(x)                  (LAN80XX_EXTRACT_BITFIELD(x,0,7))

/**
 * \brief
 * Debug feature
 *
 *  \details
 *  1b = disable the MACsec crypto core, feeding frame data around it to minimize latency while leaving classification functionality (including MACsec post-processing)  *  intact if bypass_noclass is set to 0b.
 * Field: ::LAN80XX_MACSEC_INGR_CORE_MISC_CONTROL . MACSEC_STATIC_BYPASS_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_STATIC_BYPASS_0(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_STATIC_BYPASS_0                      (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_STATIC_BYPASS_0(x)                   (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Non-match MACsec enable
 *
 * \details
 * 1b: Enable 802.1AE compliant processing for correctly tagged MACsec
 * packets for which no valid MACsec secure channel is found (no MACsec
 * flow in SA table or SA table is not hit).
 * Processing is done according to the global validation (validate_frames
 * field in this register).
 * 0b: Packet is processed as defined by the flow for this packet. Only
 * 802.1AE compliant statistics are counted, based on the global validation
 * (InPktsNoSCI or InPktsUnknownSCI).
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MISC_CONTROL . NM_MACSEC_EN
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_NM_MACSEC_EN(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_NM_MACSEC_EN                         (LAN80XX_BIT(9))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_NM_MACSEC_EN(x)                      (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * This value is used for 802.1AE compliant processing when no MACsec
 * secure channel is found. If a MACsec secure channel is found, the

 * validate_frames field from the corresponding flow control register is
 * used.
 *
 * \details
 * 00b: Disabled
 * 01b: Check
 * 10b: Strict
 * 11b: Reserved
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MISC_CONTROL . VALIDATE_FRAMES
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_VALIDATE_FRAMES_0(x)                 (LAN80XX_ENCODE_BITFIELD(x,10,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_VALIDATE_FRAMES_0                    (LAN80XX_ENCODE_BITMASK(10,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_VALIDATE_FRAMES_0(x)                 (LAN80XX_EXTRACT_BITFIELD(x,10,2))

/**
 *  \brief
 *  This disables any MACsec post-processing as well. All frames will be 'c'assified' as non-match, non-control, untagged and bypassed.
 *
 *  \details
 *  0b: static_bypass is disabled
 *  1b: Bypass the header parser and classifier in static bypass mode, further reducing latency.
 *
 *  Field: LAN80XX_MACSEC_INGR_CORE_MISC_CONTROL . BYPASS_NOCLASS_0
 */

#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_BYPASS_NOCLASS_0(x)                  (LAN80XX_ENCODE_BITFIELD(!!(x),12,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_BYPASS_NOCLASS_0                     (LAN80XX_BIT(12))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_BYPASS_NOCLASS_0(x)                  (LAN80XX_EXTRACT_BITFIELD(x,12,1))

/**
 *  \brief
 *   Longer frames with errors beyond the parsed header will still be processed normally (bypass, MACsec) and tagged with this error by the post-processor.
 *
 *  \details
 *  1b = Drop frame on input packet error detected.
 *
 *
 *  Field: LAN80XX_MACSEC_INGR_CORE_MISC_CONTROL . DROP_ON_PKTERR
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_DROP_ON_PKTERR_0(x)                  (LAN80XX_ENCODE_BITFIELD(!!(x),14,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_DROP_ON_PKTERR_0                     (LAN80XX_BIT(14))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_DROP_ON_PKTERR_0(x)                  (LAN80XX_EXTRACT_BITFIELD(x,14,1))

/**
 *  \brief
 *   Longer frames with errors beyond the parsed header will still be processed normally (bypass, MACsec) and tagged with this error by the post-processor.
 *
 *  \details
 *  1b = Drop frame on input CRC error detect.
 *  0b = No Drop
 *
 *  Field: LAN80XX_MACSEC_INGR_CORE_MISC_CONTROL . DROP_ON_CRCERR
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_DROP_ON_CRCERR_0(x)                  (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_DROP_ON_CRCERR_0                     (LAN80XX_BIT(15))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_DROP_ON_CRCERR_0(x)                  (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * Defines the way the drop operation for header parser and (short) input packet/CRC error frames is performed.
 *
 * \details
 * 00b/01b = bypass with appropriate error tagging,
 * 10b = internal drop by crypto-core (frame is not seen outside),
 * 11b = do not drop (bypass, statistics updated as if not dropped).
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MISC_CONTROL .ERR_DROP_ACTION
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_ERR_DROP_ACTION_0(x)                 (LAN80XX_ENCODE_BITFIELD(x,16,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_ERR_DROP_ACTION_0                    (LAN80XX_ENCODE_BITMASK(16,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_ERR_DROP_ACTION_0(x)                 (LAN80XX_EXTRACT_BITFIELD(x,16,2))

/**
 * \brief
 * Dest port for header parser and (short) input packet/CRC error frames if not internal dropping.
 *
 * \details
 * 00b: Send frame to the Tx MAC
 * 01b: Send frame to the redirect (loopback) path
 * 10b: Send frame to the debug capture FIFO
 * 11b: Send frame to the Tx MAC and copy to debug capture FIFO.
 *
 *  Field: LAN80XX_MACSEC_INGR_CORE_MISC_CONTROL .ERR_DEST_PORT_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ERR_DEST_PORT_0(x)                                (LAN80XX_ENCODE_BITFIELD(x,18,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ERR_DEST_PORT_0                                   (LAN80XX_ENCODE_BITMASK(18,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ERR_DEST_PORT_0(x)                                (LAN80XX_EXTRACT_BITFIELD(x,18,2))

/**
 *  \brief
 *  Capture reason for header parser and (short) input packet/CRC error frames if not internal dropping: 4-bit reason code for capturing frames into the debug capture
 *  FIFO, to be used freely. Only relevant if dest_port is 10b.
 *
 *  Field: LAN80XX_MACSEC_INGR_CORE_MISC_CONTROL .ERR_CAPT_REASON_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_ERR_CAPT_REASON_0(x)                              (LAN80XX_ENCODE_BITFIELD(x,20,4))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ERR_CAPT_REASON_0                                 (LAN80XX_ENCODE_BITMASK(20,4))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_ERR_CAPT_REASON_0(x)                              (LAN80XX_EXTRACT_BITFIELD(x,20,4))

/**
 *  \brief
 *  Alias to bits [13:8] of mc_latency_fix value (for backward compatibility purposes).
 *
 *  Field: LAN80XX_MACSEC_INGR_CORE_MISC_CONTROL .LATENCY_FIX_HI_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MACSEC_MC_LATENCY_FIX_HI_0(x)                            (LAN80XX_ENCODE_BITFIELD(x,26,6))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_MC_LATENCY_FIX_HI_0                               (LAN80XX_ENCODE_BITMASK(26,6))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_MACSEC_MC_LATENCY_FIX_HI_0(x)                            (LAN80XX_EXTRACT_BITFIELD(x,26,6))

/**
 * \brief
 *  PBB_ENB_SELECT register
 *  This register controls the PBB parsing
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_VARIOUS_CONTROL_REGS:MACSEC_INGR_CORE_PBB_ENB_SELECT
 */
#define LAN80XX_MACSEC_INGR_CORE_PBB_ENB_SELECT                                                     (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1E45))

/**
 * \brief
 * Handling of packets that were not classified as
 * control packets and that also do not contain a MACsec tag
 *
 * \details
 * 0b: Bypass
 * 1b: Perform drop_action
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_PBB_ENB_SELECT . PARSE_PBB
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_PBB_ENB_SELECT_PARSE_PBB(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),24,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_PBB_ENB_SELECT_PARSE_PBB                                        (LAN80XX_BIT(24))
#define  LAN80XX_X_MACSEC_INGR_CORE_PBB_ENB_SELECT_PARSE_PBB(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,24,1))

/**
 * \brief
 *  MPLS_ENB_SELECT register
 *  This register controls the PBB parsing
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_VARIOUS_CONTROL_REGS:MACSEC_INGR_CORE_MPLS_ENB_SELECT
 */
#define LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT                                                    (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1E4b))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 * If three MPLS labels are detected:
 * 0 = 'first selected' label is actual first label,
 * 1 = 'first selected' label is actual second label,
 * 2 = 'first selected' label is actual third label,
 * 3 = not allowed
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT . MPLS3_SELECT1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS3_SELECT1(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),0,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS3_SELECT1                                   (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS3_SELECT1(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 * If three MPLS labels are detected:
 * 0 = 'second selected' label is actual first label,
 * 1 = 'second selected' label is actual second label,
 * 2 = 'second selected' label is actual third label,
 * 3 = not allowed
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT . MPLS3_SELECT2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS3_SELECT2(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),2,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS3_SELECT2                                   (LAN80XX_ENCODE_BITMASK(2,2))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS3_SELECT2(x)                                (LAN80XX_EXTRACT_BITFIELD(x,2,2))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 * If four MPLS labels are detected:
 * 0 = 'first selected' label is actual first label,
 * 1 = 'first selected' label is actual second label,
 * 2 = 'first selected' label is actual third label,
 * 3 = 'first selected' label is actual fourth label
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT . MPLS4_SELECT1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS4_SELECT1(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),4,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS4_SELECT1                                   (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS4_SELECT1(x)                                (LAN80XX_EXTRACT_BITFIELD(x,4,2))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 * If four MPLS labels are detected:
 * 0 = 'second selected' label is actual first label,
 * 1 = 'second selected' label is actual second label,
 * 2 = 'second selected' label is actual third label,
 * 3 = 'second selected' label is actual fourth label
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT . MPLS4_SELECT2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS4_SELECT2(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),6,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS4_SELECT2                                   (LAN80XX_ENCODE_BITMASK(6,2))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS4_SELECT2(x)                                (LAN80XX_EXTRACT_BITFIELD(x,6,2))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 * If five MPLS labels are detected:
 * 0 = ‘first selected’ label is actual first label
 * 1 = ‘first selected’ label is actual second label
 * 2 = ‘first selected’ label is actual third label
 * 3 = ‘first selected’ label is actual fourth label
 * 4 = ‘first selected’ label is actual fifth label
 * 5…7 = not allowed, do not use
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT . MPLS5_SELECT1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS5_SELECT1(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),8,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS5_SELECT1                                   (LAN80XX_ENCODE_BITMASK(8,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS5_SELECT1(x)                                (LAN80XX_EXTRACT_BITFIELD(x,8,3))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 *  * If five MPLS labels are detected:
 * 0 = ‘second selected’ label is actual first label
 * 1 = ‘second selected’ label is actual second label
 * 2 = ‘second selected’ label is actual third label
 * 3 = ‘second selected’ label is actual fourth label
 * 4 = ‘second selected’ label is actual fifth label
 * 5…7 = not allowed, do not use
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT . MPLS5_SELECT2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS5_SELECT2(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),11,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS5_SELECT2                                   (LAN80XX_ENCODE_BITMASK(11,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT_MPLS5_SELECT2(x)                                (LAN80XX_EXTRACT_BITFIELD(x,11,3))

/**
 * \brief
 * Detect entropy label (RFC6790):
 *
 * \details
 * 1b = Allow detecting ELI+EL labels at bottom of the stack and signal that as ‘MPLS with entropy label’ type to TCAM.
 * 0b = ELI/EL are considered just another labels in the stack.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT . PARSE_ELI
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_ELI(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_ELI                                       (LAN80XX_BIT(15))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_ELI(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 *
 *
 * \details
 * 0b: disable comparison of mpls_etype1
 * 1b: enable comparison of mpls_etype1
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT . PARSE_MPLS1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS1(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),24,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS1                                     (LAN80XX_BIT(24))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS1(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,24,1))

/**
 * \brief
 *
 *
 * \details
 * 0b: disable comparison of mpls_etype2
 * 1b: enable comparison of mpls_etype2
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT . PARSE_MPLS2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS2(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),25,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS2                                     (LAN80XX_BIT(25))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS2(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,25,1))

/**
 * \brief
 *
 *
 * \details
 * 0b: disable comparison of mpls_etype3
 * 1b: enable comparison of mpls_etype4
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT . PARSE_MPLS3
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS3(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),26,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS3                                     (LAN80XX_BIT(26))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS3(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,26,1))

/**
 * \brief
 *
 *
 * \details
 * 0b: disable comparison of mpls_etype2
 * 1b: enable comparison of mpls_etype2
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT . PARSE_MPLS4
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS4(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),27,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS4                                     (LAN80XX_BIT(27))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS4(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,27,1))

/**
 * \brief
 *  MPLS_ENB_SELECT2 register
 *  This register controls the MPLS parsing
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_VARIOUS_CONTROL_REGS:MACSEC_INGR_CORE_MPLS_ENB_SELECT2
 */
#define LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT2                                                   (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1E54))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 * If six MPLS labels are detected:
 * 0 = ‘first selected’ label is actual first label
 * 1 = ‘first selected’ label is actual second label
 * 2 = ‘first selected’ label is actual third label
 * 3 = ‘first selected’ label is actual fourth label
 * 4 = ‘first selected’ label is actual fifth label
 * 5 = ‘first selected’ label is actual sixth label.
 * 6…7 = not allowed, do not use
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT2 . MPLS6_SELECT1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS6_SELECT1(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),0,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS6_SELECT1                                  (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS6_SELECT1(x)                               (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 *  * If six MPLS labels are detected:
 * 0 = ‘second selected’ label is actual first label
 * 1 = ‘second selected’ label is actual second label
 * 2 = ‘second selected’ label is actual third label
 * 3 = ‘second selected’ label is actual fourth label
 * 4 = ‘second selected’ label is actual fifth label
 * 5 = ‘second selected’ label is actual sixth label.
 * 6…7 = not allowed, do not use
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT2 . MPLS6_SELECT2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS6_SELECT2(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),3,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS6_SELECT2                                  (LAN80XX_ENCODE_BITMASK(3,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS6_SELECT2(x)                               (LAN80XX_EXTRACT_BITFIELD(x,3,3))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 * If seven MPLS labels are detected:
 * 0 = ‘first selected’ label is actual first label
 * 1 = ‘first selected’ label is actual second label
 * 2 = ‘first selected’ label is actual third label
 * 3 = ‘first selected’ label is actual fourth label
 * 4 = ‘first selected’ label is actual fifth label
 * 5 = ‘first selected’ label is actual sixth label.
 * 6 = ‘first selected’ label is actual seventh label.
 * 7 = not allowed, do not use
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT2 . MPLS7_SELECT1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS7_SELECT1(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),6,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS7_SELECT1                                  (LAN80XX_ENCODE_BITMASK(6,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS7_SELECT1(x)                               (LAN80XX_EXTRACT_BITFIELD(x,6,3))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 * If seven MPLS labels are detected:
 * 0 = ‘second selected’ label is actual first label
 * 1 = ‘second selected’ label is actual second label
 * 2 = ‘second selected’ label is actual third label
 * 3 = ‘second selected’ label is actual fourth label
 * 4 = ‘second selected’ label is actual fifth label
 * 5 = ‘second selected’ label is actual sixth label.
 * 6 = ‘second selected’ label is actual seventh label.
 * 7 = not allowed, do not use
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT2 . MPLS7_SELECT2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS7_SELECT2(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),9,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS7_SELECT2                                  (LAN80XX_ENCODE_BITMASK(9,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS7_SELECT2(x)                               (LAN80XX_EXTRACT_BITFIELD(x,9,3))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 * If eight MPLS labels are detected:
 * 0 = ‘first selected’ label is actual first label
 * 1 = ‘first selected’ label is actual second label
 * 2 = ‘first selected’ label is actual third label
 * 3 = ‘first selected’ label is actual fourth label
 * 4 = ‘first selected’ label is actual fifth label
 * 5 = ‘first selected’ label is actual sixth label.
 * 6 = ‘first selected’ label is actual seventh label.
 * 7 =  ‘first selected’ label is actual eighth label
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT2 . MPLS8_SELECT1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS8_SELECT1(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),12,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS8_SELECT1                                  (LAN80XX_ENCODE_BITMASK(12,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS8_SELECT1(x)                               (LAN80XX_EXTRACT_BITFIELD(x,12,3))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 * If eight MPLS labels are detected:
 * 0 = ‘second selected’ label is actual first label
 * 1 = ‘second selected’ label is actual second label
 * 2 = ‘second selected’ label is actual third label
 * 3 = ‘second selected’ label is actual fourth label
 * 4 = ‘second selected’ label is actual fifth label
 * 5 = ‘second selected’ label is actual sixth label.
 * 6 = ‘second selected’ label is actual seventh label.
 * 7 =  ‘second selected’ label is actual eighth label.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT2 . MPLS8_SELECT2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS8_SELECT2(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),15,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS8_SELECT2                                  (LAN80XX_ENCODE_BITMASK(15,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS8_SELECT2(x)                               (LAN80XX_EXTRACT_BITFIELD(x,15,3))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 * If Nine MPLS labels are detected:
 * 0 = ‘first selected’ label is actual first label
 * 1 = ‘first selected’ label is actual second label
 * 2 = ‘first selected’ label is actual third label
 * 3 = ‘first selected’ label is actual fourth label
 * 4 = ‘first selected’ label is actual fifth label
 * 5 = ‘first selected’ label is actual sixth label.
 * 6 = ‘first selected’ label is actual seventh label.
 * 7 = ‘first selected’ label is actual eighth label
 * 8 = ‘first selected’ label is actual ninenth label
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT2 . MPLS9_SELECT1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS9_SELECT1(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),18,4))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS9_SELECT1                                  (LAN80XX_ENCODE_BITMASK(18,4))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS9_SELECT1(x)                               (LAN80XX_EXTRACT_BITFIELD(x,18,4))

/**
 * \brief
 *  MPLS Label Select for TCAM Matching
 *
 * \details
 * If Nine MPLS labels are detected:
 * 0 = ‘second selected’ label is actual first label
 * 1 = ‘second selected’ label is actual second label
 * 2 = ‘second selected’ label is actual third label
 * 3 = ‘second selected’ label is actual fourth label
 * 4 = ‘second selected’ label is actual fifth label
 * 5 = ‘second selected’ label is actual sixth label.
 * 6 = ‘second selected’ label is actual seventh label.
 * 7 =  ‘second selected’ label is actual eighth label.
 * 8 = ‘second selected’ label is actual ninenth label.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_MPLS_ENB_SELECT2 . MPLS9_SELECT2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS9_SELECT2(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),22,4))
#define  LAN80XX_M_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS9_SELECT2                                  (LAN80XX_ENCODE_BITMASK(22,4))
#define  LAN80XX_X_MACSEC_INGR_CORE_MPLS_ENB_SELECT2_MPLS9_SELECT2(x)                               (LAN80XX_EXTRACT_BITFIELD(x,22,4))

/**
 * \brief
 * SAM_NM_FLOW_NCP register
 * Secure Association non-match flow control
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_VARIOUS_CONTROL_REGS:MACSEC_INGR_CORE_SAM_NM_FLOW_NCP
 */
#define LAN80XX_MACSEC_INGR_CORE_SAM_NM_FLOW_NCP                                                    (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1E51))

/**
 * \brief
 * Flow (action) type
 * Handling of packets that were not classified as
 * control packets and that also do not contain a MACsec tag
 *
 * \details
 * 0b: Bypass
 * 1b: Perform drop_action
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_UNTAGGED_FLOW_TYPE
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE0_0(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE0_0                             (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE0_0(x)                          (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Destination Port
 *
 * \details
 * 00b: Send frame to the Tx MAC
 * 01b: Send frame to the redirect (loopback) path
 * 10b: Send frame to the debug capture FIFO
 * 11b: Send frame to the Tx MAC and copy to debug capture FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_DEST_PORT0_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT0_0(x)                          (LAN80XX_ENCODE_BITFIELD(x,2,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT0_0                             (LAN80XX_ENCODE_BITMASK(2,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT0_0(x)                          (LAN80XX_EXTRACT_BITFIELD(x,2,2))

/**
 * \brief
 * Perform drop_action if frame is not from the redirect FIFO.
 *
 * Field:  LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_DROP_NON_REDIR0_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR0_0(x)                     (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR0_0                        (LAN80XX_BIT(4))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR0_0(x)                     (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Defines the way the drop operation is performed
 *
 * \details
 * 00b = bypass with CRC corruption signaling
 * 01b = bypass with bad frame indicator
 * 10b = internal drop by crypto-core (frame is not seen outside)
 * 11b = do not drop (for debugging only).
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_DROP_ACTION0_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION0_0(x)                        (LAN80XX_ENCODE_BITFIELD(x,6,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION0_0                           (LAN80XX_ENCODE_BITMASK(6,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION0_0(x)                        (LAN80XX_EXTRACT_BITFIELD(x,6,2))

/**
 * \brief
 * Flow type (action type)
 *
 * \details
 * 0b = bypass
 * 1b = perform drop_action
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_FLOW_TYPE1_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE1_0(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE1_0                             (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE1_0(x)                          (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Destination Port
 *
 * \details
 * 00b: Send frame to the Tx MAC
 * 01b: Send frame to the redirect (loopback) path
 * 10b: Send frame to the debug capture FIFO
 * 11b: Send frame to the Tx MAC and copy to debug capture FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_DEST_PORT1_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT1_0(x)                          (LAN80XX_ENCODE_BITFIELD(x,10,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT1_0                             (LAN80XX_ENCODE_BITMASK(10,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT1_0(x)                          (LAN80XX_EXTRACT_BITFIELD(x,10,2))

/**
 * \brief
 * Perform drop_action if frame is not from the redirect FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_DROP_NON_REDIR1_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR1_0(x)                     (LAN80XX_ENCODE_BITFIELD(!!(x),12,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR1_0                        (LAN80XX_BIT(12))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR1_0(x)                     (LAN80XX_EXTRACT_BITFIELD(x,12,1))

/**
 * \brief
 * Defines the way the drop operation is performed
 *
 * \details
 * 00b = bypass with CRC corruption signaling
 * 01b = bypass with bad frame indicator
 * 10b = internal drop by crypto-core (frame is not seen outside)
 * 11b = do not drop (for debugging only)
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_DROP_ACTION1_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION1_0(x)                        (LAN80XX_ENCODE_BITFIELD(x,14,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION1_0                           (LAN80XX_ENCODE_BITMASK(14,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION1_0(x)                        (LAN80XX_EXTRACT_BITFIELD(x,14,2))

/**
 * \brief
 * Flow type (action type)
 *
 * \details
 * 0b = bypass
 * 1b = perform drop_action
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_FLOW_TYPE2_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE2_0(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),16,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE2_0                             (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE2_0(x)                          (LAN80XX_EXTRACT_BITFIELD(x,16,1))

/**
 * \brief
 * Destination port
 *
 * \details
 * 00b: Send frame to the Tx MAC
 * 01b: Send frame to the redirect (loopback) path
 * 10b: Send frame to the debug capture FIFO
 * 11b: Send frame to the Tx MAC and copy to debug capture FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_DEST_PORT2_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT2_0(x)                          (LAN80XX_ENCODE_BITFIELD(x,18,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT2_0                             (LAN80XX_ENCODE_BITMASK(18,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT2_0(x)                          (LAN80XX_EXTRACT_BITFIELD(x,18,2))

/**
 * \brief
 * Perform drop_action if frame is not from the redirect FIFO
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_DROP_NON_REDIR2_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR2_0(x)                     (LAN80XX_ENCODE_BITFIELD(!!(x),20,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR2_0                        (LAN80XX_BIT(20))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR2_0(x)                     (LAN80XX_EXTRACT_BITFIELD(x,20,1))

/**
 * \brief
 * Defines the way the drop operation is performed
 *
 * \details
 * 00b = bypass with CRC corruption signaling
 * 01b = bypass with bad frame indicator
 * 10b = internal drop by crypto-core (frame is not seen outside)
 * 11b = do not drop (for debugging only)
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_DROP_ACTION2_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION2_0(x)                        (LAN80XX_ENCODE_BITFIELD(x,22,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION2_0                           (LAN80XX_ENCODE_BITMASK(22,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION2_0(x)                        (LAN80XX_EXTRACT_BITFIELD(x,22,2))

/**
 * \brief
 * Flow type (action type)
 *
 * \details
 * 0b = bypass
 * 1b = perform drop_action
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_FLOW_TYPE3_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE3_0(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),24,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE3_0                             (LAN80XX_BIT(24))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE3_0(x)                          (LAN80XX_EXTRACT_BITFIELD(x,24,1))

/**
 * \brief
 * Destination port_3
 *
 * \details
 * 00b: Send frame to the Tx MAC
 * 01b: Send frame to the redirect (loopback) path
 * 10b: Send frame to the debug capture FIFO
 * 11b: Send frame to the Tx MAC and copy to debug capture FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_DEST_PORT3_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT3_0(x)                          (LAN80XX_ENCODE_BITFIELD(x,26,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT3_0                             (LAN80XX_ENCODE_BITMASK(26,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT3_0(x)                          (LAN80XX_EXTRACT_BITFIELD(x,26,2))

/**
 * \brief
 * Perform drop_action if frame is not from the redirect FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_DROP_NON_REDIR3_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR3_0(x)                     (LAN80XX_ENCODE_BITFIELD(!!(x),28,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR3_0                        (LAN80XX_BIT(28))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR3_0(x)                     (LAN80XX_EXTRACT_BITFIELD(x,28,1))

/**
 *  \brief
 *  Defines the way the drop operation is performed
 *
 *  \details
 *  00b = bypass with CRC corruption signaling
 *  01b = bypass with bad frame indicator
 *  10b = internal drop by crypto-core (frame is not seen outside)
 *  11b = do not drop (for debugging only).
 *
 *  Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_DROP_NON_ACTION3_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION3_0(x)                        (LAN80XX_ENCODE_BITFIELD(x,30,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION3_0                           (LAN80XX_ENCODE_BITMASK(30,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION3_0(x)                        (LAN80XX_EXTRACT_BITFIELD(x,30,2))

/**
 * \brief
 * SAM_NM_FLOW_CP register
 * Secure Association non-match flow control
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_VARIOUS_CONTROL_REGS:MACSEC_INGR_CORE_SAM_NM_FLOW_CP
 */
#define LAN80XX_MACSEC_INGR_CORE_SAM_NM_FLOW_CP                                                     (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1E52))

/**
 * \brief
 * Flow (action) type
 * Handling of packets that were not classified as
 * control packets and that also do not contain a MACsec tag
 *
 * \details
 * 0b: Bypass
 * 1b: Perform drop_action
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_UNTAGGED_FLOW_TYPE0_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE0_1(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE0_1                              (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE0_1(x)                           (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Destination Port
 *
 * \details
 * 00b: Send frame to the Tx MAC
 * 01b: Send frame to the redirect (loopback) path
 * 10b: Send frame to the debug capture FIFO
 * 11b: Send frame to the Tx MAC and copy to debug capture FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_DEST_PORT0_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT0_1(x)                           (LAN80XX_ENCODE_BITFIELD(x,2,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT0_1                              (LAN80XX_ENCODE_BITMASK(2,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT0_1(x)                           (LAN80XX_EXTRACT_BITFIELD(x,2,2))

/**
 * \brief
 * Perform drop_action if frame is not from the redirect FIFO.
 *
 * Field:  LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_DROP_NON_REDIR0_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR0_1(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR0_1                         (LAN80XX_BIT(4))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR0_1(x)                      (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Defines the way the drop operation is performed
 *
 * \details
 * 00b = bypass with CRC corruption signaling
 * 01b = bypass with bad frame indicator
 * 10b = internal drop by crypto-core (frame is not seen outside)
 * 11b = do not drop (for debugging only).
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_DROP_ACTION0_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION0_1(x)                         (LAN80XX_ENCODE_BITFIELD(x,6,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION0_1                            (LAN80XX_ENCODE_BITMASK(6,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION0_1(x)                         (LAN80XX_EXTRACT_BITFIELD(x,6,2))

/**
 * \brief
 * Flow type (action type)
 *
 * \details
 * 0b = bypass
 * 1b = perform drop_action
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_FLOW_TYPE1_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE1_1(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE1_1                              (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE1_1(x)                           (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Destination Port
 *
 * \details
 * 00b: Send frame to the Tx MAC
 * 01b: Send frame to the redirect (loopback) path
 * 10b: Send frame to the debug capture FIFO
 * 11b: Send frame to the Tx MAC and copy to debug capture FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_DEST_PORT1_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT1_1(x)                           (LAN80XX_ENCODE_BITFIELD(x,10,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT1_1                              (LAN80XX_ENCODE_BITMASK(10,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT1_1(x)                           (LAN80XX_EXTRACT_BITFIELD(x,10,2))

/**
 * \brief
 * Perform drop_action if frame is not from the redirect FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_DROP_NON_REDIR1_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR1_1(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),12,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR1_1                         (LAN80XX_BIT(12))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR1_1(x)                      (LAN80XX_EXTRACT_BITFIELD(x,12,1))

/**
 * \brief
 * Defines the way the drop operation is performed
 *
 * \details
 * 00b = bypass with CRC corruption signaling
 * 01b = bypass with bad frame indicator
 * 10b = internal drop by crypto-core (frame is not seen outside)
 * 11b = do not drop (for debugging only)
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_DROP_ACTION1_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION1_1(x)                         (LAN80XX_ENCODE_BITFIELD(x,14,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION1_1                            (LAN80XX_ENCODE_BITMASK(14,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION1_1(x)                         (LAN80XX_EXTRACT_BITFIELD(x,14,2))

/**
 * \brief
 * Flow type (action type)
 *
 *  \details
 * 0b = bypass
 * 1b = perform drop_action
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_FLOW_TYPE2_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE2_1(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),16,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE2_1                              (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE2_1(x)                           (LAN80XX_EXTRACT_BITFIELD(x,16,1))

/**
 * \brief
 * Destination port
 *
 * \details
 * 00b: Send frame to the Tx MAC
 * 01b: Send frame to the redirect (loopback) path
 * 10b: Send frame to the debug capture FIFO
 * 11b: Send frame to the Tx MAC and copy to debug capture FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_DEST_PORT2_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT2_1(x)                           (LAN80XX_ENCODE_BITFIELD(x,18,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT2_1                              (LAN80XX_ENCODE_BITMASK(18,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT2_1(x)                           (LAN80XX_EXTRACT_BITFIELD(x,18,2))
/**
 * \brief
 * Perform drop_action if frame is not from the redirect FIFO
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_DROP_NON_REDIR2_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR2_1(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),20,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR2_1                         (LAN80XX_BIT(20))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR2_1(x)                      (LAN80XX_EXTRACT_BITFIELD(x,20,1))
/**
 *\brief
 * Defines the way the drop operation is performed
 *
 * \details
 * 00b = bypass with CRC corruption signaling
 * 01b = bypass with bad frame indicator
 * 10b = internal drop by crypto-core (frame is not seen outside)
 * 11b = do not drop (for debugging only)
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_DROP_ACTION2_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION2_1(x)                         (LAN80XX_ENCODE_BITFIELD(x,22,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION2_1                            (LAN80XX_ENCODE_BITMASK(22,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION2_1(x)                         (LAN80XX_EXTRACT_BITFIELD(x,22,2))

/**
 * \brief
 * Flow type (action type)
 *
 * \details
 * 0b = bypass
 * 1b = perform drop_action
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_FLOW_TYPE3_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE3_1(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),24,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE3_1                              (LAN80XX_BIT(24))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE3_1(x)                           (LAN80XX_EXTRACT_BITFIELD(x,24,1))

/**
 * * \brief
 * * Destination port_3
 * *
 * \details
 * 00b: Send frame to the Tx MAC
 * 01b: Send frame to the redirect (loopback) path
 * 10b: Send frame to the debug capture FIFO
 * 11b: Send frame to the Tx MAC and copy to debug capture FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_DEST_PORT3_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT3_1(x)                           (LAN80XX_ENCODE_BITFIELD(x,26,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT3_1                              (LAN80XX_ENCODE_BITMASK(26,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT3_1(x)                           (LAN80XX_EXTRACT_BITFIELD(x,26,2))

/**
 * \brief
 * Perform drop_action if frame is not from the redirect FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_DROP_NON_REDIR3_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR3_1(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),28,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR3_1                         (LAN80XX_BIT(28))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR3_1(x)                      (LAN80XX_EXTRACT_BITFIELD(x,28,1))

/**
 * *  \brief
 * *  Defines the way the drop operation is performed
 * *
 * \details
 * 00b = bypass with CRC corruption signaling
 * 01b = bypass with bad frame indicator
 * 10b = internal drop by crypto-core (frame is not seen outside)
 * 11b = do not drop (for debugging only).
 *
 * Field: LAN80XX_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_DROP_NON_ACTION3_1
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION3_1(x)                         (LAN80XX_ENCODE_BITFIELD(x,30,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION3_1                            (LAN80XX_ENCODE_BITMASK(30,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION3_1(x)                         (LAN80XX_EXTRACT_BITFIELD(x,30,2))

/**
 * \brief
 * Count control register
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP161_STAT_TCAM_COUNT_CONTROL
 */
#define LAN80XX_MACSEC_INGR_CORE_TCAM_COUNT_CONTROL                                                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1104))

/**
 * \brief
 * Reset all statistics counters to zero and clear statistics summary registers.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_TCAM_COUNT_CONTROL . RESET_ALL_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_RESET_ALL_0(x)                        (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_RESET_ALL_0                           (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_RESET_ALL_0(x)                        (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Enable normal read/write access to the counter memory for debugging purposes
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_TCAM_COUNT_CONTROL . DEBUG_ACCESS_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_DEBUG_ACCESS_0(x)                     (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_DEBUG_ACCESS_0                        (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_DEBUG_ACCESS_0(x)                     (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 *  \brief
 *  counters
 *
 * \details
 * 0b = Counters wrap back to zero on overflow
 * 1b = Counters do not increment past maximum value
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_TCAM_COUNT_CONTROL . SATURATE_CNTRS_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_SATURATE_CNTRS_0(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_SATURATE_CNTRS_0                      (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_SATURATE_CNTRS_0(x)                   (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Auto counters reset
 *
 * \details
 * 0b = Reading counters does not change them
 * 1b = Counters are cleared on a read access
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_TCAM_COUNT_CONTROL . AUTO_CNTR_RESET_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_AUTO_CNTR_RESET_0(x)                  (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_AUTO_CNTR_RESET_0                     (LAN80XX_BIT(3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_AUTO_CNTR_RESET_0(x)                  (LAN80XX_EXTRACT_BITFIELD(x,3,1))


/**
 * \brief
 * Count control register
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP161_STAT_SA_COUNT_CONTROL
 */
#define LAN80XX_MACSEC_INGR_CORE_SA_COUNT_CONTROL                                                   (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x3884))

/**
 * \brief
 * Reset all statistics counters to zero and clear statistics summary registers.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SA_COUNT_CONTROL . RESET_ALL_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_RESET_ALL_0(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_RESET_ALL_0                             (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_RESET_ALL_0(x)                          (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Enable normal read/write access to the counter memory for debugging purposes
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SA_COUNT_CONTROL . DEBUG_ACCESS_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_DEBUG_ACCESS_0(x)                       (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_DEBUG_ACCESS_0                          (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_DEBUG_ACCESS_0(x)                       (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 *  \brief
 *  counters
 *
 * \details
 * 0b = Counters wrap back to zero on overflow
 * 1b = Counters do not increment past maximum value
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SA_COUNT_CONTROL . SATURATE_CNTRS_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_SATURATE_CNTRS_0(x)                     (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_SATURATE_CNTRS_0                        (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_SATURATE_CNTRS_0(x)                     (LAN80XX_EXTRACT_BITFIELD(x,2,1))
/**
 * \brief
 * Auto counters reset
 *
 * \details
 * 0b = Reading counters does not change them
 * 1b = Counters are cleared on a read access
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SA_COUNT_CONTROL . AUTO_CNTR_RESET_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_AUTO_CNTR_RESET_0(x)                    (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_AUTO_CNTR_RESET_0                       (LAN80XX_BIT(3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_AUTO_CNTR_RESET_0(x)                    (LAN80XX_EXTRACT_BITFIELD(x,3,1))


/**
 * \brief
 * Count control register
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP161_STAT_SECY_COUNT_CONTROL
 */
#define LAN80XX_MACSEC_INGR_CORE_SECY_COUNT_CONTROL                                                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x3904))

/**
 * \brief
 * Reset all statistics counters to zero and clear statistics summary registers.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SECY_COUNT_CONTROL . RESET_ALL_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_RESET_ALL_0(x)                        (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_RESET_ALL_0                           (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_RESET_ALL_0(x)                        (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Enable normal read/write access to the counter memory for debugging purposes
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SECY_COUNT_CONTROL . DEBUG_ACCESS_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_DEBUG_ACCESS_0(x)                     (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_DEBUG_ACCESS_0                        (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_DEBUG_ACCESS_0(x)                     (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 *  \brief
 *  counters
 *
 * \details
 * 0b = Counters wrap back to zero on overflow
 * 1b = Counters do not increment past maximum value
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SECY_COUNT_CONTROL . SATURATE_CNTRS_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_SATURATE_CNTRS_0(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_SATURATE_CNTRS_0                      (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_SATURATE_CNTRS_0(x)                   (LAN80XX_EXTRACT_BITFIELD(x,2,1))
/**
 * \brief
 * Auto counters reset
 *
 * \details
 * 0b = Reading counters does not change them
 * 1b = Counters are cleared on a read access
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SECY_COUNT_CONTROL . AUTO_CNTR_RESET_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_AUTO_CNTR_RESET_0(x)                  (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_AUTO_CNTR_RESET_0                     (LAN80XX_BIT(3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_AUTO_CNTR_RESET_0(x)                  (LAN80XX_EXTRACT_BITFIELD(x,3,1))


/**
 * \brief
 * Count control register
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP161_STAT_IFC_COUNT_CONTROL
 */
#define LAN80XX_MACSEC_INGR_CORE_IFC_COUNT_CONTROL                                                  (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x3984))

/**
 * \brief
 * Reset all statistics counters to zero and clear statistics summary registers.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_IFC_COUNT_CONTROL . RESET_ALL_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_RESET_ALL_0(x)                         (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_RESET_ALL_0                            (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_RESET_ALL_0(x)                         (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Enable normal read/write access to the counter memory for debugging purposes
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_IFC_COUNT_CONTROL . DEBUG_ACCESS_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_DEBUG_ACCESS_0(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_DEBUG_ACCESS_0                         (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_DEBUG_ACCESS_0(x)                      (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 *  \brief
 *  counters
 *
 * \details
 * 0b = Counters wrap back to zero on overflow
 * 1b = Counters do not increment past maximum value
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_IFC_COUNT_CONTROL . SATURATE_CNTRS_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_SATURATE_CNTRS_0(x)                    (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_SATURATE_CNTRS_0                       (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_SATURATE_CNTRS_0(x)                    (LAN80XX_EXTRACT_BITFIELD(x,2,1))
/**
 * \brief
 * Auto counters reset
 *
 * \details
 * 0b = Reading counters does not change them
 * 1b = Counters are cleared on a read access
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_IFC_COUNT_CONTROL . AUTO_CNTR_RESET_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_AUTO_CNTR_RESET_0(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_AUTO_CNTR_RESET_0                      (LAN80XX_BIT(3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_AUTO_CNTR_RESET_0(x)                   (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * VLAN tag detection
 *
 * \details
 * Register: \a MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_VARIOUS_CONTROL_REGS:MACSEC_INGR_CORE_SAM_CP_TAG
 */
#define LAN80XX_MACSEC_INGR_CORE_SAM_CP_TAG                                                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 0x1E40))

/**
 * \brief
 * Translate one priority value into another using map table
 *
 * \details
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_CP_TAG . MAP_TBL_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_CP_TAG_MAP_TBL_0(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,24))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_CP_TAG_MAP_TBL_0                                     (LAN80XX_ENCODE_BITMASK(0,24))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_CP_TAG_MAP_TBL_0(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,24))

/**
 * \brief
 * STAG user priority enable
 *
 * \details
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_CP_TAG . STAG_UP_EN_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_CP_TAG_STAG_UP_EN_0(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),27,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_CP_TAG_STAG_UP_EN_0                                  (LAN80XX_BIT(27))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_CP_TAG_STAG_UP_EN_0(x)                               (LAN80XX_EXTRACT_BITFIELD(x,27,1))

/**
 * \brief
 * QTAG user priority map enable
 *
 * \details
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_CP_TAG . QTAG_UP_EN_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_CP_TAG_QTAG_UP_EN_0(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),28,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_CP_TAG_QTAG_UP_EN_0                                  (LAN80XX_BIT(28))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SAM_CP_TAG_QTAG_UP_EN_0(x)                               (LAN80XX_EXTRACT_BITFIELD(x,28,1))

/**
 * \brief
 * Latency Control Register
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_VARIOUS_CONTROL_REGS:MACSEC_INGR_CORE_LATENCY_CONTROL
 */

#define LAN80XX_MACSEC_INGR_CORE_LATENCY_CONTROL                                                    (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1E5D))

/**
 * \brief
 * Fixed latency forcing value for the MACsec core, representing the latency fixing range from 0 to 65535.
 *
 * \details
 * Streaming out of a frame is blocked for this number of clock cycles after it started streaming into the MACsec core. An out-of-range value or backpressure from the   * MAC side (temporarily) disables latency fixing. Normally, this value will be set to just above the maximum latency of the operations to be performed.
 * The range 0, 1..., 255 corresponds to 0, 5, ..., 259 module clock cycles for static bypass mode.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_LATENCY_CONTROL . MC_LATENCY_FIX_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_LATENCY_CONTROL_MC_LATENCY_FIX_0(x)                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_LATENCY_CONTROL_MC_LATENCY_FIX_0                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_LATENCY_CONTROL_MC_LATENCY_FIX_0(x)                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * \brief
 * Dynamic Latency Control Register
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_VARIOUS_CONTROL_REGS:MACSEC_INGR_CORE_DYN_LATENCY_CONTROL
 */

#define LAN80XX_MACSEC_INGR_CORE_DYN_LATENCY_CONTROL                                                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1E5E))

/**
 * \brief
 * Value for 'd'namic latency mode' (TX underrun protection). This value represents the number of words that are required to be present in the output buffer
 * before a packet is released. This allows prevention of buffer underruns in the connected MAC. Note: The maximum allowed value for this field is 0x1E.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_DYN_LATENCY_CONTROL . MC_DYN_LATENCY_WORDS_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_LATENCY_CONTROL_MC_DYN_LATENCY_WORDS_0(x)                (LAN80XX_ENCODE_BITFIELD(x,0,5))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_LATENCY_CONTROL_MC_DYN_LATENCY_WORDS_0                   (LAN80XX_ENCODE_BITMASK(0,5))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_LATENCY_CONTROL_MC_DYN_LATENCY_WORDS_0(x)                (LAN80XX_EXTRACT_BITFIELD(x,0,5))

/**
 * brief
 * Dynamic latency fixing mode
 *
 * \details
 * 1b = enable dynamic latency fixing mode.
 * 0b = disable dynamic latency fixing mode.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_DYN_LATENCY_CONTROL . DYN_LAT_ENABLE_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_DYN_LAT_ENABLE_0(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),31,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_DYN_LAT_ENABLE_0                                         (LAN80XX_BIT(31))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_DYN_LAT_ENABLE_0(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,31,1))

/**
 * \brief
 * MAC_DA match compare register
 *
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_CONTROL_PACKET:MACSEC_INGR_CORE_CP_MAC_DA_MATCH
 */
#define LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH(ri)                      (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 , (0x1e00 | (ri*2))))

/**
 * brief
 * Bits [47:40] of one MAC_DA compare value, first byte received.
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_MATCH. MAC_DA_MATCH_47_40
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH_MAC_DA_MATCH_47_40(x) (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH_MAC_DA_MATCH_47_40    (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH_MAC_DA_MATCH_47_40(x) (LAN80XX_EXTRACT_BITFIELD(x,0,7))

/**
 * brief
 * Bits [39:32] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_MATCH. MAC_DA_MATCH_39_32
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH_MAC_DA_MATCH_39_32(x) (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH_MAC_DA_MATCH_39_32    (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH_MAC_DA_MATCH_39_32(x) (LAN80XX_EXTRACT_BITFIELD(x,8,8))
/**
 * brief
 * Bits [31:24] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_MATCH. MAC_DA_MATCH_31_24
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH_MAC_DA_MATCH_31_24(x) (LAN80XX_ENCODE_BITFIELD(x,16,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH_MAC_DA_MATCH_31_24    (LAN80XX_ENCODE_BITMASK(16,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH_MAC_DA_MATCH_31_24(x) (LAN80XX_EXTRACT_BITFIELD(x,16,8))
/**
 * brief
 * Bits [31:23] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_MATCH. MAC_DA_MATCH_23_16
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH_MAC_DA_MATCH_23_16(x) (LAN80XX_ENCODE_BITFIELD(x,24,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH_MAC_DA_MATCH_23_16    (LAN80XX_ENCODE_BITMASK(24,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH_MAC_DA_MATCH_23_16(x) (LAN80XX_EXTRACT_BITFIELD(x,24,8))

/**
 * \brief
 * MAC_DA and Ethertype match compare register
 *
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_CONTROL_PACKET:MACSEC_INGR_CORE_CP_MAC_DA_ET_MATCH
 */
#define LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH(ri)                   (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 , (0x1e01 | (ri*2))))

/**
 * brief
 * Bits [15:8] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_ET_MATCH. MAC_DA_MATCH_15_8
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_8(x) (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_8  (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_8(x) (LAN80XX_EXTRACT_BITFIELD(x,0,8))
/**
 * brief
 * Bits [7:0] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_ET_MATCH. MAC_DA_MATCH_7_0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_7_0(x) (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_7_0   (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_7_0(x) (LAN80XX_EXTRACT_BITFIELD(x,8,8))
/**
 * brief
 * Ethertype compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_ET_MATCH. ETHER_TYPE_MATCH
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH(x) (LAN80XX_ENCODE_BITFIELD(x,16,16))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH   (LAN80XX_ENCODE_BITMASK(16,16))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH(x) (LAN80XX_EXTRACT_BITFIELD(x,16,16))

/**
 * \brief
 * MAC_DA range start value low register
 *
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_CONTROL_PACKET:CP_MAC_DA_START_0_1_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO(ri)               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 , (0x1e18 | (ri*4))))

/**
 * brief
 * Bits [47:40] of one MAC_DA compare value, first byte received.
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_START_0_1_LO. MAC_DA_MATCH_47_40
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO_MAC_DA_MATCH_47_40(x) (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO_MAC_DA_MATCH_47_40 (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO_MAC_DA_MATCH_47_40(x) (LAN80XX_EXTRACT_BITFIELD(x,0,7))

/**
 * brief
 * Bits [39:32] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_START_0_1_LO. MAC_DA_MATCH_39_32
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO_MAC_DA_MATCH_39_32(x) (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO_MAC_DA_MATCH_39_32 (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO_MAC_DA_MATCH_39_32(x) (LAN80XX_EXTRACT_BITFIELD(x,8,8))
/**
 * brief
 * Bits [31:24] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_START_0_1_LO. MAC_DA_MATCH_31_24
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO_MAC_DA_MATCH_31_24(x) (LAN80XX_ENCODE_BITFIELD(x,16,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO_MAC_DA_MATCH_31_24 (LAN80XX_ENCODE_BITMASK(16,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO_MAC_DA_MATCH_31_24(x) (LAN80XX_EXTRACT_BITFIELD(x,16,8))
/**
 * brief
 * Bits [31:23] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_START_0_1_LO. MAC_DA_MATCH_23_16
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO_MAC_DA_MATCH_23_16(x) (LAN80XX_ENCODE_BITFIELD(x,24,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO_MAC_DA_MATCH_23_16 (LAN80XX_ENCODE_BITMASK(24,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO_MAC_DA_MATCH_23_16(x) (LAN80XX_EXTRACT_BITFIELD(x,24,8))

/**
 * \brief
 * MAC_DA range start value high register
 *
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_CONTROL_PACKET:CP_MAC_DA_START_0_1_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI(ri)               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 , (0x1e19 | (ri*4))))

/**
 * brief
 * Bits [15:8] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_START_0_1_HI. MAC_DA_MATCH_15_8
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_MAC_DA_MATCH_15_8(x) (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_MAC_DA_MATCH_15_8 (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_MAC_DA_MATCH_15_8(x) (LAN80XX_EXTRACT_BITFIELD(x,0,8))
/**
 * brief
 * Bits [7:0] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_START_0_1_HI. MAC_DA_MATCH_7_0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_MAC_DA_MATCH_7_0(x) (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_MAC_DA_MATCH_7_0 (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_MAC_DA_MATCH_7_0(x) (LAN80XX_EXTRACT_BITFIELD(x,8,8))
/**
 * brief
 * Ethertype compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_START_0_1_HI. ETHER_TYPE_MATCH
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_ETHER_TYPE_MATCH(x) (LAN80XX_ENCODE_BITFIELD(x,16,16))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_ETHER_TYPE_MATCH (LAN80XX_ENCODE_BITMASK(16,16))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_ETHER_TYPE_MATCH(x) (LAN80XX_EXTRACT_BITFIELD(x,16,16))


/**
 * \brief
 * Primary VLAN Parser control. This register controls the VLAN parsing but note that the actual tag values used for parsing are in
 * the SAM_PP_TAGS & SAM_PP_TAGS2 registers.
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_CONTROL_PACKET:MACSEC_INGR_CORE_CP_TAG_ENB
 */
#define LAN80XX_MACSEC_INGR_CORE_CP_TAG_ENB                                                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1E3C))

/**
 * brief
 * Enable detection of VLAN tags matching qtag_value field from SAM_PP_TAGS.
 *
 * \details
 * 1b = enable detection of VLAN tags matching qtag value.
 * 0b = disable detection of VLAN tags matching qtag value.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_TAG_ENB. PARSE_STAG0_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG0_0(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG0_0                                 (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG0_0(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,1))
/**
 * brief
 * Enable detection of VLAN tags matching stag_value field from SAM_PP_TAGS.
 *
 * \details
 * 1b = enable detection of VLAN tags matching stag value.
 * 0b = disable detection of VLAN tags matching stag value.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_TAG_ENB. PARSE_STAG1_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG1_0(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG1_0                                 (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG1_0(x)                              (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * brief
 * Enable detection of VLAN tags matching stag_value2 field from SAM_PP_TAGS2.
 *
 * \details
 * 1b = enable detection of VLAN tags matching stag value2.
 * 0b = disable detection of VLAN tags matching stag value2.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_TAG_ENB . PARSE_STAG2_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG2_0(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG2_0                                 (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG2_0(x)                              (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * brief
 * Enable detection of VLAN tags matching stag_value3 field from SAM_PP_TAGS2.
 *
 * \details
 * 1b = enable detection of VLAN tags matching stag value3.
 * 0b = disable detection of VLAN tags matching stag value3.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_TAG_ENB . PARSE_STAG3_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG3_0(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG3_0                                 (LAN80XX_BIT(3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG3_0(x)                              (LAN80XX_EXTRACT_BITFIELD(x,3,1))
/**
 * brief
 * Enable detection of multiple back-2-back VLAN tags (Q-in-Q and beyond).
 *
 * \details
 * 1b = enable detection of multiple back-2-back VLAN tags.
 * 0b = disable detection of multiple back-2-back VLAN tags..
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_TAG_ENB . PARSE_QINQ_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_QINQ_0(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),31,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_QINQ_0                                  (LAN80XX_BIT(31))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_QINQ_0(x)                               (LAN80XX_EXTRACT_BITFIELD(x,31,1))


/**
 * \brief
 * MAC_DA range END value low register
 *
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_CONTROL_PACKET:CP_MAC_DA_END_0_1_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO(ri)                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 , (0x1e1a | (ri*4))))

/**
 * brief
 * Bits [47:40] of one MAC_DA compare value, first byte received.
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_END_0_1_LO. MAC_DA_MATCH_47_40
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO_MAC_DA_MATCH_47_40(x) (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO_MAC_DA_MATCH_47_40 (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO_MAC_DA_MATCH_47_40(x) (LAN80XX_EXTRACT_BITFIELD(x,0,7))

/**
 * brief
 * Bits [39:32] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_END_0_1_LO. MAC_DA_MATCH_39_32
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO_MAC_DA_MATCH_39_32(x) (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO_MAC_DA_MATCH_39_32 (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO_MAC_DA_MATCH_39_32(x) (LAN80XX_EXTRACT_BITFIELD(x,8,8))
/**
 * brief
 * Bits [31:24] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_END_0_1_LO. MAC_DA_MATCH_31_24
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO_MAC_DA_MATCH_31_24(x) (LAN80XX_ENCODE_BITFIELD(x,16,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO_MAC_DA_MATCH_31_24 (LAN80XX_ENCODE_BITMASK(16,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO_MAC_DA_MATCH_31_24(x) (LAN80XX_EXTRACT_BITFIELD(x,16,8))
/**
 * brief
 * Bits [31:23] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_END_0_1_LO. MAC_DA_MATCH_23_16
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO_MAC_DA_MATCH_23_16(x) (LAN80XX_ENCODE_BITFIELD(x,24,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO_MAC_DA_MATCH_23_16 (LAN80XX_ENCODE_BITMASK(24,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO_MAC_DA_MATCH_23_16(x) (LAN80XX_EXTRACT_BITFIELD(x,24,8))

/**
 * \brief
 * MAC_DA range END value high register
 *
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_CONTROL_PACKET:CP_MAC_DA_END_0_1_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI(ri)                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 , (0x1e1b | (ri*4))))

/**
 * brief
 * Bits [15:8] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_END_0_1_HI. MAC_DA_MATCH_15_8
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_MAC_DA_MATCH_15_8(x) (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_MAC_DA_MATCH_15_8 (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_MAC_DA_MATCH_15_8(x) (LAN80XX_EXTRACT_BITFIELD(x,0,8))
/**
 * brief
 * Bits [7:0] of one MAC_DA compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_END_0_1_HI. MAC_DA_MATCH_7_0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_MAC_DA_MATCH_7_0(x) (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_MAC_DA_MATCH_7_0 (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_MAC_DA_MATCH_7_0(x) (LAN80XX_EXTRACT_BITFIELD(x,8,8))
/**
 * brief
 * Ethertype compare value
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CP_MAC_DA_END_0_1_HI. ETHER_TYPE_MATCH
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_ETHER_TYPE_MATCH(x) (LAN80XX_ENCODE_BITFIELD(x,16,16))
#define  LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_ETHER_TYPE_MATCH (LAN80XX_ENCODE_BITMASK(16,16))
#define  LAN80XX_X_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_ETHER_TYPE_MATCH(x) (LAN80XX_EXTRACT_BITFIELD(x,16,16))

/**
 * \brief
 * Secondary VLAN Parser control. This register controls the VLAN parsing but note that the actual tag values used for parsing are in
 * the SAM_PP_TAGS & SAM_PP_TAGS2 registers.
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_CONTROL_PACKET:MACSEC_INGR_CORE_SCP_TAG_ENB
 */

#define LAN80XX_MACSEC_INGR_CORE_SCP_TAG_ENB                                                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1E38))

/**
 * brief
 * Enable detection of VLAN tags matching qtag_value field from SAM_PP_TAGS.
 *
 * \details
 * 1b = enable detection of VLAN tags matching qtag value.
 * 0b = disable detection of VLAN tags matching qtag value.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SCP_TAG_ENB. PARSE_STAG0_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG0_0(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG0_0                                (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG0_0(x)                             (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * brief
 * Enable detection of VLAN tags matching stag_value field from SAM_PP_TAGS.
 *
 * \details
 * 1b = enable detection of VLAN tags matching stag value.
 * 0b = disable detection of VLAN tags matching stag value.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SCP_TAG_ENB. PARSE_STAG1_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG1_0(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG1_0                                (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG1_0(x)                             (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * brief
 * Enable detection of VLAN tags matching stag_value2 field from SAM_PP_TAGS2.
 *
 * \details
 * 1b = enable detection of VLAN tags matching stag value2.
 * 0b = disable detection of VLAN tags matching stag value2.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SCP_TAG_ENB . PARSE_STAG2_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG2_0(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG2_0                                (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG2_0(x)                             (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * brief
 * Enable detection of VLAN tags matching stag_value3 field from SAM_PP_TAGS2.
 *
 * \details
 * 1b = enable detection of VLAN tags matching stag value3.
 * 0b = disable detection of VLAN tags matching stag value3.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SCP_TAG_ENB . PARSE_STAG3_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG3_0(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG3_0                                (LAN80XX_BIT(3))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG3_0(x)                             (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * brief
 * Enable detection of multiple back-2-back VLAN tags (Q-in-Q and beyond).
 *
 * \details
 * 1b = enable detection of multiple back-2-back VLAN tags.
 * 0b = disable detection of multiple back-2-back VLAN tags..
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SCP_TAG_ENB . PARSE_QINQ_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_QINQ_0(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),31,1))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_QINQ_0                                 (LAN80XX_BIT(31))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_QINQ_0(x)                              (LAN80XX_EXTRACT_BITFIELD(x,31,1))

/**
 * \brief
 * Control frame match mode register for primary control packet detector
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_CONTROL_PACKET:MACSEC_INGR_CORE_CP_MATCH_MODE
 */
#define LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MATCH_MODE                            (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1E3E))

/**
 * \brief
 * Control frame match enable register for primary control packet detector
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP_161B_I_128_CT_P_MCHP_CLASSIFIER_CONTROL_PACKET:MACSEC_INGR_CORE_CP_MATCH_ENABLE
 */
#define LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MATCH_ENABLE                          (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1E3F))

/**
 * \brief
 * Block context updates
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP161_EIP62_EIP62_REGISTERS:MACSEC_INGR_CORE_EIP62_CONTEXT_UPD_CTRL
 */
#define LAN80XX_MACSEC_INGR_CORE_CONTEXT_UPD_CTRL                                                   (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x3D0C))

/**
 * brief
 * If both the bit in this register and the related input bit for a frame are set to one, the context update for that frame is blocked.
 *
 * \details
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_CONTEXT_UPD_CTRL . BLOCK_CONTEXT_UPDATES_0
 */
#define  LAN80XX_F_MACSEC_INGR_MACSEC_INGR_CONTEXT_UPD_CTRL_BLOCK_CONTEXT_UPDATES_0(x)              (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_MACSEC_INGR_MACSEC_INGR_CONTEXT_UPD_CTRL_BLOCK_CONTEXT_UPDATES_0                 (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_MACSEC_INGR_MACSEC_INGR_CONTEXT_UPD_CTRL_BLOCK_CONTEXT_UPDATES_0(x)              (LAN80XX_EXTRACT_BITFIELD(x,0,2))
/**
 * brief
 * Secure Association match entry enable control registers for 1-32 SA.
 *
 * \details
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . ENTRY_SET_1
 */

#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_ENTRY_SET_1                                           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,0x1820))

/**
 * brief
 * Secure Association match entry enable control registers for 32-64 SA.
 *
 * \details
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . ENTRY_SET_2
 */

#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_ENTRY_SET_2                                           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,0x1821))

/**
 * brief
 * Secure Association match entry enable control registers for 64-96 SA.
 *
 * \details
 *
 *  Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . ENTRY_SET_3
 */

#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_ENTRY_SET_3                                           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,0x1822))

/**
 * brief
 * Secure Association match entry enable control registers for 96-128 SA.
 *
 * \details
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . ENTRY_SET_4
 */

#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_ENTRY_SET_4                                           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,0x1823))

/**
 * brief
 * Secure Association match entry clear control registers for 1-32 SA.
 *
 * \details
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . ENTRY_CLEAR_1
 */

#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_ENTRY_CLEAR_1                                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,0x1830))

/**
 * brief
 * Secure Association match entry clear control registers for 32-64 SA.
 *
 * details
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . ENTRY_CLEAR_2
 */
#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_ENTRY_CLEAR_2                                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,0x1831))

/**
 * brief
 * Secure Association match entry clear control registers for 64-96 SA.
 *
 * \details
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . ENTRY_CLEAR_3
 */
#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_ENTRY_CLEAR_3                                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,0x1832))

/**
  * brief
  * Secure Association match entry clear control registers for 96-128 SA.
  *
  * \details
  *
  * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . ENTRY_CLEAR_1
  */
#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_ENTRY_CLEAR_4                                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,0x1833))

/**
 * brief
 * TCAM Entry enable modification 1 register for 0 - 31 SA
 *
 * \details
 * 1b = Toggle TCAM match for the corresponding entry
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . ENTRY_TOGGLE_1
 */
#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_ENTRY_TOGGLE_1                                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,0x1810))
/**
 * brief
 * TCAM Entry enable modification 1 register for 0 - 31 SA
 *
 * \details
 * 1b = Toggle TCAM match for the corresponding entry
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . ENTRY_TOGGLE_2
 */
#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_ENTRY_TOGGLE_2                                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,0x1811))
/**
 * brief
 * TCAM Entry enable modification 3 register for 63 - 95 SA
 *
 * \details
 * 1b = Toggle TCAM match for the corresponding entry
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . ENTRY_TOGGLE_3
 */
#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_ENTRY_TOGGLE_3                                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,0x1812))
/**
 * brief
 * TCAM Entry enable modification 4 register for 96 - 127 SA
 *
 * \details
 * 1b = Toggle TCAM match for the corresponding entry
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . ENTRY_TOGGLE_4
 */
#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_ENTRY_TOGGLE_4                                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,0x1813))

/**
 * brief
 * Secure Association match entry enable control register
 *
 * \details
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . SAM_ENTRY_ENABLE_CTRL
 */
#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL                                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1840))
/**
 * brief
 * Secure Assosiation match index
 *
 * \details
 * 1b = Index of a TCAM entry to enable when set_enable.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL. SAM_INDEX_SET_0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_SET_0(x)           (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_SET_0              (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_SET_0(x)           (LAN80XX_EXTRACT_BITFIELD(x,0,7))
/**
 * brief
 * TCAM Enable
 *
 * \details
 * 1b = Enable the TCAM entry with index sam_index_set
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL. SET_ENABLE_0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SET_ENABLE_0(x)              (LAN80XX_ENCODE_BITFIELD(x,14,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SET_ENABLE_0                 (LAN80XX_BIT(14))
#define  LAN80XX_X_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SET_ENABLE_0(x)              (LAN80XX_EXTRACT_BITFIELD(x,14,1))
/**
 * brief
 * Secure Assosiation match index
 *
 * \details
 * 1b = Index of a TCAM entry to clear when clear_enable is set.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL. SAM_INDEX_CLEAR_0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_CLEAR_0(x)         (LAN80XX_ENCODE_BITFIELD(x,16,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_CLEAR_0            (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_CLEAR_0(x)         (LAN80XX_EXTRACT_BITFIELD(x,16,7))
/**
 * brief
 * TCAM Disable
 *
 * \details
 * 1b = Clear the TCAM entry with index sam_index_set
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL. CLEAR_ENABLE_0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_CLEAR_ENABLE_0(x)            (LAN80XX_ENCODE_BITFIELD(x,30,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_CLEAR_ENABLE_0               (LAN80XX_BIT(30))
#define  LAN80XX_X_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_CLEAR_ENABLE_0(x)            (LAN80XX_EXTRACT_BITFIELD(x,30,1))

/**
 * brief
 * In-Flight Counter register
 *
 * \details
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . SAM_IN_FLIGHT
 */
#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT                                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1841))

/**
 * brief
 * Unsafe indicator
 *
 * \details
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT. UNSAFE
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_UNSAFE(x)                            (LAN80XX_ENCODE_BITFIELD((x),0,6))
#define  LAN80XX_M_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_UNSAFE                               (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_UNSAFE(x)                            (LAN80XX_EXTRACT_BITFIELD(x,0,6))
/**
 * brief
 * Load unsafe
 *
 * \details
 * Loads the value in in_flight field to unsafe field
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT. LOAD_UNSAFE
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_LOAD_UNSAFE(x)                       (LAN80XX_ENCODE_BITFIELD(x,31,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_LOAD_UNSAFE                          (LAN80XX_BIT(31))
#define  LAN80XX_X_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_LOAD_UNSAFE(x)                       (LAN80XX_EXTRACT_BITFIELD(x,31,1))

/**
 * brief
 * TCAM KEY for SA 0 - 64.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0 . MACSEC_TCAM_KEY0
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0(ri)                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x800 | (ri*16))))
/**
 * brief
 * Number of VLAN tags
 *
 * \details
 * Selects Number of VLAN Tags
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0 . NUM_TAGS
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_NUM_TAGS(x)                   (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_NUM_TAGS                      (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_NUM_TAGS(x)                   (LAN80XX_EXTRACT_BITFIELD(x,0,6))


/**
 * brief
 * Type of packet
 *
 * \details
 * 11b = MPLS packet with entropy label
 * 10b = PBB packet
 * 01b = MPLS packet (with or without entropy label)
 * 00b = Other
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0 . PACKET_TYPE
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_PACKET_TYPE(x)                (LAN80XX_ENCODE_BITFIELD(x,8,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_PACKET_TYPE                   (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_PACKET_TYPE(x)                (LAN80XX_EXTRACT_BITFIELD(x,8,2))
/**
 * brief
 * MACsec EtherType is matched)
 *
 * \details
 * 1b - MACsec frame detected
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0 . MACSEC_TAGGED
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_MACSEC_TAGGED(x)              (LAN80XX_ENCODE_BITFIELD(x,13,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_MACSEC_TAGGED                 (LAN80XX_BIT(13))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_MACSEC_TAGGED(x)              (LAN80XX_EXTRACT_BITFIELD(x,13,1))

/**
 * brief
 * Frame Preempt
 *
 * \details
 * 1b - Frame is preemptable
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0 . PREEMPT_FRAME
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_PREEMPT_FRAME(x)              (LAN80XX_ENCODE_BITFIELD(x,15,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_PREEMPT_FRAME                 (LAN80XX_BIT(15))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_PREEMPT_FRAME(x)              (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * brief
 *  An extension for the num_tags field, when the 9-label MPLS parser is present and enabled.
 *
 * \details
 * This field must be enabled for comparison only for MPLS packet types
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_INGR_CORE_TCAM_KEY0 . NUM_TAGS_EXT
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_NUM_TAGS_EXT(x)               (LAN80XX_ENCODE_BITFIELD(x,24,4))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_NUM_TAGS_EXT                  (LAN80XX_BIT(24))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_NUM_TAGS_EXT(x)               (LAN80XX_EXTRACT_BITFIELD(x,24,4))

/**
 * brief
 * TCAM KEY for SA 0 - 64.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0 . MACSEC_TCAM_KEY1
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY1(ri)                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x801 | (ri*16))))
/**
 * brief
 * MAC Destination address
 *
 * \details
 * Macsec DA in little-endian byte order
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY1 . MAC_DA_31_0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY1_MAC_DA_31_0(x)                (LAN80XX_ENCODE_BITFIELD(x,0,32))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY1_MAC_DA_31_0                   (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY1_MAC_DA_31_0(x)                (LAN80XX_EXTRACT_BITFIELD(x,0,32))

/**
 * brief
 * TCAM KEY for SA 0 - 64.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0 . MACSEC_TCAM_KEY2
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY2(ri)                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x802 | (ri*16))))
/**
 * brief
 * MACSEC Destination address
 *
 * \details
 * Destination address 47 - 32
 *
 *  Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY2 . MAC_DA_47_32
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY2_MAC_DA_47_32(x)               (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY2_MAC_DA_47_32                  (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY2_MAC_DA_47_32(x)               (LAN80XX_EXTRACT_BITFIELD(x,0,16))
/**
 * brief
 * TCAM KEY for SA 0 - 64.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0 . MACSEC_TCAM_KEY4
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4(ri)                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x804 | (ri*16))))
/**
 * brief
 * MAC packet data
 *
 * \details
 *  MAC packet data 31 - 0
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_PACKET_DATA_LO(x)             (LAN80XX_ENCODE_BITFIELD(x,0,32))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_PACKET_DATA_LO                (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_PACKET_DATA_LO(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,32))

/**
 * brief
 * Backbone VLAN tag VLAN_ID[11:8]
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_ID_11_8(x)              (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_ID_11_8                 (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_ID_11_8(x)              (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * brief
 * Backbone VLAN tag DEI
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_DEI(x)                  (LAN80XX_ENCODE_BITFIELD(x,4,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_DEI                     (LAN80XX_BIT(4))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_DEI(x)                  (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * brief
 * Backbone VLAN tag PCP[2:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_PCP(x)                  (LAN80XX_ENCODE_BITFIELD(x,5,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_PCP                     (LAN80XX_ENCODE_BITMASK(5,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_PCP(x)                  (LAN80XX_EXTRACT_BITFIELD(x,5,3))

/**
 * brief
 * Backbone VLAN tag VLANID[7:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_ID_7_0(x)               (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_ID_7_0                  (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_ID_7_0(x)               (LAN80XX_EXTRACT_BITFIELD(x,8,8))

/**
 * brief
 * Service Instance ID SID[23:16]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_SID_23_16(x)                  (LAN80XX_ENCODE_BITFIELD(x,16,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_SID_23_16                     (LAN80XX_ENCODE_BITMASK(16,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_SID_23_16(x)                  (LAN80XX_EXTRACT_BITFIELD(x,16,8))

/**
 * brief
 * Service Instance ID SID[15:8]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_SID_15_8(x)                   (LAN80XX_ENCODE_BITFIELD(x,24,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_SID_15_8                      (LAN80XX_ENCODE_BITMASK(24,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_SID_15_8(x)                   (LAN80XX_EXTRACT_BITFIELD(x,24,8))

/**
 * brief
 * 1st selected MPLS label MPLS_LABEL[19:12]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_19_12(x)         (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_19_12            (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_19_12(x)         (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * brief
 * 1st selected MPLS label MPLS_LABEL[11:4]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_11_4(x)          (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_11_4             (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_11_4(x)          (LAN80XX_EXTRACT_BITFIELD(x,8,8))

/**
 * brief
 * 1st selected MPLS label MPLS_LABEL_S
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_S(x)             (LAN80XX_ENCODE_BITFIELD(x,16,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_S                (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_S(x)             (LAN80XX_EXTRACT_BITFIELD(x,16,1))

/**
 * brief
 * 1st selected MPLS label MPLS_EXP[2:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_EXP(x)           (LAN80XX_ENCODE_BITFIELD(x,17,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_EXP              (LAN80XX_ENCODE_BITMASK(17,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_EXP(x)           (LAN80XX_EXTRACT_BITFIELD(x,17,3))

/**
 * brief
 * 1st selected MPLS label MPLS_LABEL[3:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_3_0(x)           (LAN80XX_ENCODE_BITFIELD(x,20,4))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_3_0              (LAN80XX_ENCODE_BITMASK(20,4))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_3_0(x)           (LAN80XX_EXTRACT_BITFIELD(x,20,4))

/**
 * brief
 * TCAM KEY for SA 0 - 64.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0 . MACSEC_TCAM_KEY5
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5(ri)                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x805 | (ri*16))))
/**
 * brief
 * MAC packet data
 *
 * \details
 * MAC packet data msb
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5 . PACKET_DATA_HI
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_PACKET_DATA_HI(x)             (LAN80XX_ENCODE_BITFIELD(x,0,24))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_PACKET_DATA_HI                (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_PACKET_DATA_HI(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,24))

/**
 * brief
 * Service Instance ID SID[7:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_SID_7_0(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_SID_7_0                       (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_SID_7_0(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * brief
 * Backbone service instance drop eligibility indicator
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_IDEI(x)                       (LAN80XX_ENCODE_BITFIELD(x,8,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_IDEI                          (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_IDEI(x)                       (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * brief
 * Backbone service instance priority code point
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_IPCP(x)                       (LAN80XX_ENCODE_BITFIELD(x,9,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_IPCP                          (LAN80XX_ENCODE_BITMASK(9,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_IPCP(x)                       (LAN80XX_EXTRACT_BITFIELD(x,9,3))

/**
 * brief
 * Outer Customer VLAN_ID[11:8]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_OUT_VID_11_8(x)               (LAN80XX_ENCODE_BITFIELD(x,12,4))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_OUT_VID_11_8                  (LAN80XX_ENCODE_BITMASK(12,4))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_OUT_VID_11_8(x)               (LAN80XX_EXTRACT_BITFIELD(x,12,4))

/**
 * brief
 * Outer Customer VLAN_ID[7:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_OUT_VID_7_0(x)                (LAN80XX_ENCODE_BITFIELD(x,16,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_OUT_VID_7_0                   (LAN80XX_ENCODE_BITMASK(16,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_OUT_VID_7_0(x)                (LAN80XX_EXTRACT_BITFIELD(x,16,8))

/**
 * brief
 * 2nd selected MPLS label MPLS_LABEL[19:12]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_19_12(x)         (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_19_12            (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_19_12(x)         (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * brief
 * 2nd selected MPLS label MPLS_LABEL[11:4]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_11_4(x)          (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_11_4             (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_11_4(x)          (LAN80XX_EXTRACT_BITFIELD(x,8,8))
/**
 * brief
 * 2nd selected MPLS label MPLS_LABEL_S
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_S(x)             (LAN80XX_ENCODE_BITFIELD(x,16,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_S                (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_S(x)             (LAN80XX_EXTRACT_BITFIELD(x,16,1))

/**
 * brief
 * 2nd selected MPLS label MPLS_EXP[2:0],
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_EXP(x)           (LAN80XX_ENCODE_BITFIELD(x,17,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_EXP              (LAN80XX_ENCODE_BITMASK(17,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_EXP(x)           (LAN80XX_EXTRACT_BITFIELD(x,17,3))

/**
 * brief
 * 2nd selected MPLS label MPLS_LABEL[3:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_3_0(x)           (LAN80XX_ENCODE_BITFIELD(x,20,4))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_3_0              (LAN80XX_ENCODE_BITMASK(20,4))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_3_0(x)           (LAN80XX_EXTRACT_BITFIELD(x,20,4))

/**
 * brief
 * TCAM MASK for SA 0 - 64.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0 . MACSEC_TCAM_MASK0
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK0(ri)                             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x808 | (ri*16))))

/**
 * brief
 * Mask for number of VLAN Tags in the packet
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK0 . NUM_TAGS
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK0_NUM_TAGS(x)                  (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK0_NUM_TAGS                     (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK0_NUM_TAGS(x)                  (LAN80XX_EXTRACT_BITFIELD(x,0,7))

/**
 * brief
 * TCAM MASK for SA 0 - 64.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0 . MACSEC_TCAM_MASK1
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK1(ri)                             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x809 | (ri*16))))

/**
 * brief
 * Mask for Destination Address Match (0 - 32 bit)
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK1 . DEST_ADDR
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK1_DEST_ADDR(x)                 (LAN80XX_ENCODE_BITFIELD(x,0,32))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK1_DEST_ADDR                    (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK1_DEST_ADDR(x)                 (LAN80XX_EXTRACT_BITFIELD(x,0,32))

/**
 * brief
 * TCAM MASK for SA 0 - 64.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0 . MACSEC_TCAM_MASK2
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK2(ri)                             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x80A | (ri*16))))

/**
 * brief
 * Mask for Destination Address Match (33 - 48 bit)
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK2 . DEST_ADDR
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK2_DEST_ADDR(x)                 (LAN80XX_ENCODE_BITFIELD(x,0,32))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK2_DEST_ADDR                    (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK2_DEST_ADDR(x)                 (LAN80XX_EXTRACT_BITFIELD(x,0,32))

/**
 * brief
 * TCAM MASK for SA 0 - 64.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0 . MACSEC_TCAM_MASK4
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4(ri)                             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x80C | (ri*16))))



/**
 * brief
 * MASK for Ethetype match
 *
 * \details
 *  This Enables the Ethertype match with the value in TCAM KEY4(0 - 16)
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4 . ETHERTYPE_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_ETHERTYPE_MASK(x)            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_ETHERTYPE_MASK               (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_ETHERTYPE_MASK(x)            (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * brief
 * MASK for VLAN Tag match
 *
 * \details
 *  This Enables the VLAN Tag match with the value in TCAM KEY4(16 - 32)
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4 . VLANTAG_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_VLANTAG_MASK(x)              (LAN80XX_ENCODE_BITFIELD(x,16,16))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_VLANTAG_MASK                 (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_VLANTAG_MASK(x)              (LAN80XX_EXTRACT_BITFIELD(x,16,16))

/**
 * brief
 * Backbone VLAN tag MASK
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4 . BVLAN_MASK
 */
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_BVLAN_MASK                   (LAN80XX_ENCODE_BITMASK(0,16))

/**
 * brief
 * Service Instance ID SID MASK
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4 . SID_MASK
 */
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_SID_MASK                     (LAN80XX_ENCODE_BITMASK(16,16))

/**
 * brief
 * 1st selected MPLS label MPLS_LABEL MASK
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4 . 1_MPLS_MASK
 */
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_1_MPLS_MASK                  (LAN80XX_ENCODE_BITMASK(0,24))

/**
 * brief
 * TCAM MASK for SA 0 - 64.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0 . MACSEC_TCAM_MASK5
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5(ri)                             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x80D | (ri*16))))

/**
 * brief
 * MASK for Inner VLAN Tag match
 *
 * \details
 *  This Enables the Inner VLAN Tag match with the value in TCAM KEY5
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5 . INNER_VLANTAG_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5_INNER_VLANTAG_MASK(x)        (LAN80XX_ENCODE_BITFIELD(x,8,16))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5_INNER_VLANTAG_MASK           (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5_INNER_VLANTAG_MASK(x)        (LAN80XX_EXTRACT_BITFIELD(x,8,16))
/**
 * brief
 * Service Instance ID SID[7:0] MASK
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5 . SID_MASK
 */
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5_SID_MASK                     (LAN80XX_ENCODE_BITMASK(0,8))

/**
 * brief
 * Outer coustomer VLAN MASK
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5 . OUT_VID_MASK
 */
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5_OUT_VID_MASK                 (LAN80XX_ENCODE_BITMASK(12,12))

/**
 * brief
 * 2nd selected MPLS label MASK
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5 . 2_MPLS_MASK
 */
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5_2_MPLS_MASK                  (LAN80XX_ENCODE_BITMASK(0,24))

/**
 * TCAM KEY for SA 64 - 128.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1 . MACSEC_TCAM_KEY0
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0(ri)                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x4800 | (ri*16))))
/**
 * brief
 * Number of VLAN tags
 *
 * \details
 * Selects Number of VLAN Tags
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0 . NUM_TAGS
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_NUM_TAGS(x)                   (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_NUM_TAGS                      (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_NUM_TAGS(x)                   (LAN80XX_EXTRACT_BITFIELD(x,0,6))


/**
 * brief
 * Type of packet
 *
 * \details
 * 11b = MPLS packet with entropy label
 * 10b = PBB packet
 * 01b = MPLS packet (with or without entropy label)
 * 00b = Other
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0 . PACKET_TYPE
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_PACKET_TYPE(x)                (LAN80XX_ENCODE_BITFIELD(x,8,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_PACKET_TYPE                   (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_PACKET_TYPE(x)                (LAN80XX_EXTRACT_BITFIELD(x,8,2))
/**
 * brief
 * MACsec EtherType is matched)
 *
 * \details
 * 1b - MACsec frame detected
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0 . MACSEC_TAGGED
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_MACSEC_TAGGED(x)              (LAN80XX_ENCODE_BITFIELD(x,13,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_MACSEC_TAGGED                 (LAN80XX_BIT(13))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_MACSEC_TAGGED(x)              (LAN80XX_EXTRACT_BITFIELD(x,13,1))

/**
 * brief
 * Frame Preempt
 *
 * \details
 * 1b - Frame is preemptable
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0 . PREEMPT_FRAME
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_PREEMPT_FRAME(x)              (LAN80XX_ENCODE_BITFIELD(x,15,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_PREEMPT_FRAME                 (LAN80XX_BIT(15))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_PREEMPT_FRAME(x)              (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * brief
 *  An extension for the num_tags field, when the 9-label MPLS parser is present and enabled.
 *
 * \details
 * This field must be enabled for comparison only for MPLS packet types
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE0_INGR_CORE_TCAM_KEY0 . NUM_TAGS_EXT
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_NUM_TAGS_EXT(x)               (LAN80XX_ENCODE_BITFIELD(x,24,4))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_NUM_TAGS_EXT                  (LAN80XX_BIT(24))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_NUM_TAGS_EXT(x)               (LAN80XX_EXTRACT_BITFIELD(x,24,4))

/**
 * brief
 * TCAM KEY for SA 64 - 128.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1 . MACSEC_TCAM_KEY1
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY1(ri)                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x4801 | (ri*16))))
/**
 * brief
 * MAC Destination address
 *
 * \details
 * Macsec DA in little-endian byte order
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY1 . MAC_DA_31_0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY1_MAC_DA_31_0(x)                (LAN80XX_ENCODE_BITFIELD(x,0,32))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY1_MAC_DA_31_0                   (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY1_MAC_DA_31_0(x)                (LAN80XX_EXTRACT_BITFIELD(x,0,32))

/**
 * brief
 * TCAM KEY for SA 64 - 128.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1 . MACSEC_TCAM_KEY2
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY2(ri)                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x4802 | (ri*16))))
/**
 * brief
 * MACSEC Destination address
 *
 * \details
 * Destination address 47 - 32
 *
 *  Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY2 . MAC_DA_47_32
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY2_MAC_DA_47_32(x)               (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY2_MAC_DA_47_32                  (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY2_MAC_DA_47_32(x)               (LAN80XX_EXTRACT_BITFIELD(x,0,16))
/**
 * brief
 * TCAM KEY for SA 64 - 128.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1 . MACSEC_TCAM_KEY4
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4(ri)                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x4804 | (ri*16))))
/**
 * brief
 * MAC packet data
 *
 * \details
 *  MAC packet data 31 - 0
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_PACKET_DATA_LO(x)             (LAN80XX_ENCODE_BITFIELD(x,0,32))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_PACKET_DATA_LO                (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_PACKET_DATA_LO(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,32))

/**
 * brief
 * Backbone VLAN tag VLAN_ID[11:8]
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_BVLAN_ID_11_8(x)              (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_BVLAN_ID_11_8                 (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_BVLAN_ID_11_8(x)              (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * brief
 * Backbone VLAN tag DEI
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_BVLAN_DEI(x)                  (LAN80XX_ENCODE_BITFIELD(x,4,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_BVLAN_DEI                     (LAN80XX_BIT(4))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_BVLAN_DEI(x)                  (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * brief
 * Backbone VLAN tag PCP[2:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_BVLAN_PCP(x)                  (LAN80XX_ENCODE_BITFIELD(x,5,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_BVLAN_PCP                     (LAN80XX_ENCODE_BITMASK(5,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_BVLAN_PCP(x)                  (LAN80XX_EXTRACT_BITFIELD(x,5,3))

/**
 * brief
 * Backbone VLAN tag VLANID[7:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_BVLAN_ID_7_0(x)               (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_BVLAN_ID_7_0                  (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_BVLAN_ID_7_0(x)               (LAN80XX_EXTRACT_BITFIELD(x,8,8))

/**
 * brief
 * Service Instance ID SID[23:16]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_SID_23_16(x)                  (LAN80XX_ENCODE_BITFIELD(x,16,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_SID_23_16                     (LAN80XX_ENCODE_BITMASK(16,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_SID_23_16(x)                  (LAN80XX_EXTRACT_BITFIELD(x,16,8))

/**
 * brief
 * Service Instance ID SID[15:8]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_SID_15_8(x)                   (LAN80XX_ENCODE_BITFIELD(x,24,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_SID_15_8                      (LAN80XX_ENCODE_BITMASK(24,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_SID_15_8(x)                   (LAN80XX_EXTRACT_BITFIELD(x,24,8))

/**
 * brief
 * 1st selected MPLS label MPLS_LABEL[19:12]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_19_12(x)         (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_19_12            (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_19_12(x)         (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * brief
 * 1st selected MPLS label MPLS_LABEL[11:4]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_11_4(x)          (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_11_4             (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_11_4(x)          (LAN80XX_EXTRACT_BITFIELD(x,8,8))

/**
 * brief
 * 1st selected MPLS label MPLS_LABEL_S
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_S(x)             (LAN80XX_ENCODE_BITFIELD(x,16,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_S                (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_S(x)             (LAN80XX_EXTRACT_BITFIELD(x,16,1))

/**
 * brief
 * 1st selected MPLS label MPLS_EXP[2:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_EXP(x)           (LAN80XX_ENCODE_BITFIELD(x,17,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_EXP              (LAN80XX_ENCODE_BITMASK(17,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_EXP(x)           (LAN80XX_EXTRACT_BITFIELD(x,17,3))

/**
 * brief
 * 1st selected MPLS label MPLS_LABEL[3:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_3_0(x)           (LAN80XX_ENCODE_BITFIELD(x,20,4))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_3_0              (LAN80XX_ENCODE_BITMASK(20,4))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4_1_MPLS_LABEL_3_0(x)           (LAN80XX_EXTRACT_BITFIELD(x,20,4))

/**
 * brief
 * TCAM KEY for SA 64 - 128.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1 . MACSEC_TCAM_KEY5
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5(ri)                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x4805 | (ri*16))))
/**
 * brief
 * MAC packet data
 *
 * \details
 * MAC packet data msb
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5 . PACKET_DATA_HI
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_PACKET_DATA_HI(x)             (LAN80XX_ENCODE_BITFIELD(x,0,24))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_PACKET_DATA_HI                (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_PACKET_DATA_HI(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,24))

/**
 * brief
 * Service Instance ID SID[7:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_SID_7_0(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_SID_7_0                       (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_SID_7_0(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * brief
 * Backbone service instance drop eligibility indicator
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_IDEI(x)                       (LAN80XX_ENCODE_BITFIELD(x,8,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_IDEI                          (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_IDEI(x)                       (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * brief
 * Backbone service instance priority code point
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_IPCP(x)                       (LAN80XX_ENCODE_BITFIELD(x,9,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_IPCP                          (LAN80XX_ENCODE_BITMASK(9,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_IPCP(x)                       (LAN80XX_EXTRACT_BITFIELD(x,9,3))

/**
 * brief
 * Outer Customer VLAN_ID[11:8]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_OUT_VID_11_8(x)               (LAN80XX_ENCODE_BITFIELD(x,12,4))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_OUT_VID_11_8                  (LAN80XX_ENCODE_BITMASK(12,4))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_OUT_VID_11_8(x)               (LAN80XX_EXTRACT_BITFIELD(x,12,4))

/**
 * brief
 * Outer Customer VLAN_ID[7:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_OUT_VID_7_0(x)                (LAN80XX_ENCODE_BITFIELD(x,16,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_OUT_VID_7_0                   (LAN80XX_ENCODE_BITMASK(16,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_OUT_VID_7_0(x)                (LAN80XX_EXTRACT_BITFIELD(x,16,8))

/**
 * brief
 * 2nd selected MPLS label MPLS_LABEL[19:12]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_19_12(x)         (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_19_12            (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_19_12(x)         (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * brief
 * 2nd selected MPLS label MPLS_LABEL[11:4]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_11_4(x)          (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_11_4             (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_11_4(x)          (LAN80XX_EXTRACT_BITFIELD(x,8,8))
/**
 * brief
 * 2nd selected MPLS label MPLS_LABEL_S
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_S(x)             (LAN80XX_ENCODE_BITFIELD(x,16,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_S                (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_S(x)             (LAN80XX_EXTRACT_BITFIELD(x,16,1))

/**
 * brief
 * 2nd selected MPLS label MPLS_EXP[2:0],
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_EXP(x)           (LAN80XX_ENCODE_BITFIELD(x,17,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_EXP              (LAN80XX_ENCODE_BITMASK(17,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_EXP(x)           (LAN80XX_EXTRACT_BITFIELD(x,17,3))

/**
 * brief
 * 2nd selected MPLS label MPLS_LABEL[3:0]
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4 . PACKET_DATA_LO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_3_0(x)           (LAN80XX_ENCODE_BITFIELD(x,20,4))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_3_0              (LAN80XX_ENCODE_BITMASK(20,4))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5_2_MPLS_LABEL_3_0(x)           (LAN80XX_EXTRACT_BITFIELD(x,20,4))

/**
 * brief
 * TCAM MASK for SA 64 - 128.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1 . MACSEC_TCAM_MASK0
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK0(ri)                             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x4808 | (ri*16))))

/**
 * brief
 * Mask for number of VLAN Tags in the packet
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK0 . NUM_TAGS
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK0_NUM_TAGS(x)                  (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK0_NUM_TAGS                     (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK0_NUM_TAGS(x)                  (LAN80XX_EXTRACT_BITFIELD(x,0,7))

/**
 * brief
 * TCAM MASK for SA 64 - 128.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1 . MACSEC_TCAM_MASK1
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK1(ri)                             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x4809 | (ri*16))))

/**
 * brief
 * Mask for Destination Address Match (0 - 32 bit)
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK1 . DEST_ADDR
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK1_DEST_ADDR(x)                 (LAN80XX_ENCODE_BITFIELD(x,0,32))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK1_DEST_ADDR                    (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK1_DEST_ADDR(x)                 (LAN80XX_EXTRACT_BITFIELD(x,0,32))

/**
 * brief
 * TCAM MASK for SA 64 - 128.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1 . MACSEC_TCAM_MASK2
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK2(ri)                             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x480A | (ri*16))))

/**
 * brief
 * Mask for Destination Address Match (33 - 48 bit)
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK2 . DEST_ADDR
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK2_DEST_ADDR(x)                 (LAN80XX_ENCODE_BITFIELD(x,0,32))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK2_DEST_ADDR                    (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK2_DEST_ADDR(x)                 (LAN80XX_EXTRACT_BITFIELD(x,0,32))

/**
 * brief
 * TCAM MASK for SA 64 - 128.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1 . MACSEC_TCAM_MASK4
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4(ri)                             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x480C | (ri*16))))

/**
 * brief
 * MASK for Ethetype match
 *
 * \details
 *  This Enables the Ethertype match with the value in TCAM KEY4(0 - 16)
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4 . ETHERTYPE_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4_ETHERTYPE_MASK(x)            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4_ETHERTYPE_MASK               (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4_ETHERTYPE_MASK(x)            (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * brief
 * MASK for VLAN Tag match
 *
 * \details
 *  This Enables the VLAN Tag match with the value in TCAM KEY4(16 - 32)
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4 . VLANTAG_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4_VLANTAG_MASK(x)              (LAN80XX_ENCODE_BITFIELD(x,16,16))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4_VLANTAG_MASK                 (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4_VLANTAG_MASK(x)              (LAN80XX_EXTRACT_BITFIELD(x,16,16))

/**
 * brief
 * Backbone VLAN tag MASK
 *
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4 . BVLAN_MASK
 */
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4_BVLAN_MASK                   (LAN80XX_ENCODE_BITMASK(0,16))

/**
 * brief
 * Service Instance ID SID MASK
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4 . SID_MASK
 */
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4_SID_MASK                     (LAN80XX_ENCODE_BITMASK(16,16))

/**
 * brief
 * 1st selected MPLS label MPLS_LABEL MASK
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4 . 1_MPLS_MASK
 */
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4_1_MPLS_MASK                  (LAN80XX_ENCODE_BITMASK(0,24))

/**
 * brief
 * TCAM MASK for SA 64 - 128.
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1 . MACSEC_TCAM_MASK5
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5(ri)                             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x480D | (ri*16))))

/**
 * brief
 * MASK for Inner VLAN Tag match
 *
 * \details
 *  This Enables the Inner VLAN Tag match with the value in TCAM KEY5
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5 . INNER_VLANTAG_MASK
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5_INNER_VLANTAG_MASK(x)        (LAN80XX_ENCODE_BITFIELD(x,8,16))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5_INNER_VLANTAG_MASK           (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5_INNER_VLANTAG_MASK(x)        (LAN80XX_EXTRACT_BITFIELD(x,8,16))

/**
 * brief
 * Service Instance ID SID[7:0] MASK
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5 . SID_MASK
 */
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5_SID_MASK                     (LAN80XX_ENCODE_BITMASK(0,8))

/**
 * brief
 * Outer coustomer VLAN MASK
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5 . OUT_VID_MASK
 */
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5_OUT_VID_MASK                 (LAN80XX_ENCODE_BITMASK(12,12))

/**
 * brief
 * 2nd selected MPLS label MASK
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5 . 2_MPLS_MASK
 */
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5_2_MPLS_MASK                  (LAN80XX_ENCODE_BITMASK(0,24))

/**
 * brief
 * TCAM POLICY 0 - 64 SAs
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0 . TCAM_POLICY
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY(ri)                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0xC00 | (ri*1))))

/**
 * brief
 * SecY Index
 *
 * \details
 * Sub-port (SecY) index assigned to the frame that matched the corresponding entry.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY . VPORT_INDEX
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_VPORT_INDEX(x)                (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_VPORT_INDEX                   (LAN80XX_ENCODE_BITMASK(0,6))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_VPORT_INDEX(x)                (LAN80XX_EXTRACT_BITFIELD(x,0,6))

/**
 * brief
 * Match Priority
 *
 * \details
 * Priority field that is used to resolve multiple matches on TCAM
 * 15 - High priority
 * 0 - Low priority
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY . PRIO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_PRIO(x)                       (LAN80XX_ENCODE_BITFIELD(x,27,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_PRIO                          (LAN80XX_ENCODE_BITMASK(27,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_PRIO(x)                       (LAN80XX_EXTRACT_BITFIELD(x,27,29))

/**
 * brief
 * DROP Packet
 *
 * \details
 * Drop the frame when packet matches on TCAM
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY . DROP
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_DROP(x)                       (LAN80XX_ENCODE_BITFIELD(x,30,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_DROP                          (LAN80XX_BIT(30))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_DROP(x)                       (LAN80XX_EXTRACT_BITFIELD(x,30,1))

/**
 * brief
 * Control Packet
 *
 * \details
 * Force the frame to be a “control” frame
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY . CONTROL_PKT
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_CONTROL_PKT(x)                (LAN80XX_ENCODE_BITFIELD(x,31,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_CONTROL_PKT                   (LAN80XX_BIT(31))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_CONTROL_PKT(x)                (LAN80XX_EXTRACT_BITFIELD(x,31,1))

/**
 * brief
 * TCAM POLICY 64 - 128 SAS
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1 . TCAM_POLICY
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY(ri)                              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x4C00 | (ri*1))))

/**
 * brief
 * SecY Index
 *
 * \details
 * Sub-port (SecY) index assigned to the frame that matched the corresponding entry.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY . VPORT_INDEX
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_VPORT_INDEX(x)                (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_VPORT_INDEX                   (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_VPORT_INDEX(x)                (LAN80XX_EXTRACT_BITFIELD(x,0,6))

/**
 * brief
 * Match Priority
 *
 * \details
 * Priority field that is used to resolve multiple matches on TCAM
 * 15 - High priority
 * 0 - Low priority
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY . PRIO
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_PRIO(x)                       (LAN80XX_ENCODE_BITFIELD(x,27,3))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_PRIO                          (LAN80XX_ENCODE_BITMASK(27,3))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_PRIO(x)                       (LAN80XX_EXTRACT_BITFIELD(x,27,29))

/**
 * brief
 * DROP Packet
 *
 * \details
 * Drop the frame when packet matches on TCAM
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY . DROP
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_DROP(x)                       (LAN80XX_ENCODE_BITFIELD(x,30,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_DROP                          (LAN80XX_BIT(30))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_DROP(x)                       (LAN80XX_EXTRACT_BITFIELD(x,30,1))

/**
 * brief
 * Control Packet
 *
 * \details
 * Force the frame to be a “control” frame
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY . CONTROL_PKT
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_CONTROL_PKT(x)                (LAN80XX_ENCODE_BITFIELD(x,31,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_CONTROL_PKT                   (LAN80XX_BIT(31))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_CONTROL_PKT(x)                (LAN80XX_EXTRACT_BITFIELD(x,31,1))

/**
 * brief
 * In-Flight Counter register
 *
 * \details
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENABLE_CTRL . SAM_IN_FLIGHT
 */
#define LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT                                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x1841))

/**
 * brief
 * Unsafe indicator
 *
 * \details
 *
 *  Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT. UNSAFE
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_UNSAFE(x)                            (LAN80XX_ENCODE_BITFIELD((x),0,6))
#define  LAN80XX_M_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_UNSAFE                               (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_UNSAFE(x)                            (LAN80XX_EXTRACT_BITFIELD(x,0,6))

/**
 * brief
 * Load unsafe
 *
 * \details
 * Loads the value in in_flight field to unsafe field
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT. LOAD_UNSAFE
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_LOAD_UNSAFE(x)                       (LAN80XX_ENCODE_BITFIELD(x,31,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_LOAD_UNSAFE                          (LAN80XX_BIT(31))
#define  LAN80XX_X_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_LOAD_UNSAFE(x)                       (LAN80XX_EXTRACT_BITFIELD(x,31,1))
/**
 * brief
 * Flow control page 0 registers 0-31 SC..
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : MACSEC_INGR_CORE_EIP_161B_E_128_CT_P_MCHP_FLOW_CONTROL_PAGE0 .MACSEC_INGR_CORE_SAM_FLOW_CTRL1
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1(ri)                                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,  (0x1c00 | (ri*2))))

/**
 * brief
 * Flow type (action type)
 *
 * \details
 * 00b = bypass operation.
 * 01b = Drop operation.
 * 10b = MACsec INGRess.
 * 11b = MACsec INGRess
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1.FLOW_TYPE
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_FLOW_TYPE(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_FLOW_TYPE                       (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_FLOW_TYPE(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * brief
 * Destination port
 *
 * \details
 * 00b: Send frame to the Tx MAC
 * 01b: Send frame to the redirect (loopback) path
 * 10b: Send frame to the debug capture FIFO
 * 11b: Send frame to the Tx MAC and copy to debug capture FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1.DEST_PORT
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_DEST_PORT(x)                    (LAN80XX_ENCODE_BITFIELD(x,2,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_DEST_PORT                       (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_DEST_PORT(x)                    (LAN80XX_EXTRACT_BITFIELD(x,2,2))
/**
 * brief
 * Drop action
 *
 * \details
 * 1b - Perform drop_action if frame is not from the redirect FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1.DROP_NON_REDIR
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_DROP_NON_REDIR(x)               (LAN80XX_ENCODE_BITFIELD(x,4,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_DROP_NON_REDIR                  (LAN80XX_BIT(4))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_DROP_NON_REDIR(x)               (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * brief
 * crypt-authenticate mode
 *
 * \details
 * 0b = Disables crypt-authenticate mode
 * 1b = Enable crypt-authenticate mode
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1.CRYPT_AUTH
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_FLOW_CRYPT_AUTH(x)              (LAN80XX_ENCODE_BITFIELD(x,5,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_FLOW_CRYPT_AUTH                 (LAN80XX_BIT(5))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_FLOW_CRYPT_AUTH(x)              (LAN80XX_EXTRACT_BITFIELD(x,5,1))
/**
 *  brief
 *  Drop action (action type)
 *
 * \details
 *  00b = bypass with CRC corruption signaling
 *  01b = bypass with bad frame indicator
 *  10b = internal drop by crypto-core (frame is not seen outside)
 *  11b = do not drop (for debugging only).
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1.DROP_ACTION
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_DROP_ACTION(x)                  (LAN80XX_ENCODE_BITFIELD(x,6,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_DROP_ACTION                     (LAN80XX_BIT(6))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_DROP_ACTION(x)                  (LAN80XX_EXTRACT_BITFIELD(x,6,2))
/**
 * brief
 * Replay Protection enable
 *
 * \details
 * 1b = enable replay protection
 * 0b = disable replay protection
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1.REPLAY_PROTECT
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_REPLAY_PROTECT(x)               (LAN80XX_ENCODE_BITFIELD(x,16,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_REPLAY_PROTECT                  (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_REPLAY_PROTECT(x)               (LAN80XX_EXTRACT_BITFIELD(x,16,1))
/**
 * brief
 * Controls processing of 'data' frames that have a SecTAG.
 *
 * \details
 * 1b = pass for the further processing by SecY Controlled port
 * 0b = drop.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1.ALLOW_TAGGED_DATA
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_ALLOW_TAGGED_DATA(x)            (LAN80XX_ENCODE_BITFIELD(x,17,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_ALLOW_TAGGED_DATA               (LAN80XX_BIT(17))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_ALLOW_TAGGED_DATA(x)            (LAN80XX_EXTRACT_BITFIELD(x,17,1))
/**
 * brief
 * Controls processing of 'data' frames that do not have SecTAG.
 *
 * \details
 * 1b = bypass unmodified
 * 0b = drop
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1.ALLOW_UNTAGGED_DATA
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_ALLOW_UNTAGGED_DATA(x)          (LAN80XX_ENCODE_BITFIELD(x,18,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_ALLOW_UNTAGGED_DATA             (LAN80XX_BIT(18))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_ALLOW_UNTAGGED_DATA(x)          (LAN80XX_EXTRACT_BITFIELD(x,18,1))
/**
 * brief
 * Frame validation level for the tagged frames
 *
 * \details
 *  00b = disabled
 *  01b = check
 *  10b = strict
 *  11b = null
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1.VALIDATE_FRAMES_TAGGED
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_VALIDATE_FRAMES_TAGGED(x)       (LAN80XX_ENCODE_BITFIELD(x,19,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_VALIDATE_FRAMES_TAGGED          (LAN80XX_BIT(19))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_VALIDATE_FRAMES_TAGGED(x)       (LAN80XX_EXTRACT_BITFIELD(x,19,2))

/**
 * brief
 * There exists a 32-bit control word between the last MPLS label and the inner Ethernet header.
 *
 * \details
 * 1b = 32-bit control word present.
 * 0b = 32-bit control word not present.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1.EOMPLS_CTRL_WORD
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_EOMPLS_CTRL_WORD(x)             (LAN80XX_ENCODE_BITFIELD(x,22,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_EOMPLS_CTRL_WORD                (LAN80XX_BIT(22))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_EOMPLS_CTRL_WORD(x)             (LAN80XX_EXTRACT_BITFIELD(x,22,1))

/**
 * brief
 * MPLS frame is assumed Ethernet over MPLS
 *
 * \details
 * 1b =  the MPLS frame is assumed Ethernet over MPLS.
 * 0b =  the MPLS frame is assumed as MPLS.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1.EOMPLS_SUBPORT
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_EOMPLS_SUBPORT(x)               (LAN80XX_ENCODE_BITFIELD(x,23,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_EOMPLS_SUBPORT                  (LAN80XX_BIT(23))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_EOMPLS_SUBPORT(x)               (LAN80XX_EXTRACT_BITFIELD(x,23,1))

/**
 * brief
 * Flow control 2 page 0 registers 0-31 SC..
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : MACSEC_INGR_CORE_EIP_161B_E_128_CT_P_MCHP_FLOW_CONTROL_PAGE0 .MACSEC_INGR_CORE_SAM_FLOW_CTRL2
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2(ri)                                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x1c01 | (ri*2))))


/**
 * brief
 * Pre-SecTAG Authentication Start
 *
 * \details
 * Specifies number of bytes from the start of the frame to be bypassed without MACsec protection.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2.PRE_SECTAG_AUTH_START
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_PRE_SECTAG_AUTH_START(x)        (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_PRE_SECTAG_AUTH_START           (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_PRE_SECTAG_AUTH_START(x)        (LAN80XX_EXTRACT_BITFIELD(x,0,6))

/**
 * brief
 * Pre-SecTAG Authentication length
 *
 * \details
 * Specifies number of bytes to be authenticated in the pre-SecTAG area.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2.PRE_SECTAG_AUTH_LEN
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_PRE_SECTAG_AUTH_LEN(x)          (LAN80XX_ENCODE_BITFIELD(x,8,6))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_PRE_SECTAG_AUTH_LEN             (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_PRE_SECTAG_AUTH_LEN(x)          (LAN80XX_EXTRACT_BITFIELD(x,8,6))
/**
 * brief
 * Sectag offset length
 *
 * \details
 *  7-bit wide, absolute offset from the start of the frame where to insert the SecTAG
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2.SECTAG_OFFSET
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_SECTAG_OFFSET(x)                (LAN80XX_ENCODE_BITFIELD(x,16,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_SECTAG_OFFSET                   (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_SECTAG_OFFSET(x)                (LAN80XX_EXTRACT_BITFIELD(x,16,7))

/**
 * brief
 * Confidentiality offset
 *
 * \details
 * The number of bytes (in the range of 0-127) to be authenticated but not encrypted following the SecTAG in the encrypted MACsec frame.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2.CONFIDENTIALITY_OFFSET
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_CONFIDENTIALITY_OFFSET(x)       (LAN80XX_ENCODE_BITFIELD(x,24,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_CONFIDENTIALITY_OFFSET          (LAN80XX_BIT(24))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_CONFIDENTIALITY_OFFSET(x)       (LAN80XX_EXTRACT_BITFIELD(x,24,8))

/**
 * brief
 * Flow control page 1 registers 0-31 SC..
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : MACSEC_INGR_CORE_EIP_161B_E_128_CT_P_MCHP_FLOW_CONTROL_PAGE1 .MACSEC_INGR_CORE_SAM_FLOW_CTRL1
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1(ri)                                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,  (0x1c00 | (ri*2))))

/**
 * brief
 * Flow type (action type)
 *
 * \details
 * 00b = bypass operation.
 * 01b = Drop operation.
 * 10b = MACsec INGRess.
 * 11b = MACsec INGRess
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1.FLOW_TYPE
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_FLOW_TYPE(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_FLOW_TYPE                       (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_FLOW_TYPE(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * brief
 * Destination port
 *
 * \details
 * 00b: Send frame to the Tx MAC
 * 01b: Send frame to the redirect (loopback) path
 * 10b: Send frame to the debug capture FIFO
 * 11b: Send frame to the Tx MAC and copy to debug capture FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1.DEST_PORT
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_DEST_PORT(x)                    (LAN80XX_ENCODE_BITFIELD(x,2,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_DEST_PORT                       (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_DEST_PORT(x)                    (LAN80XX_EXTRACT_BITFIELD(x,2,2))
/**
 * brief
 * Drop action
 *
 * \details
 * 1b - Perform drop_action if frame is not from the redirect FIFO.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1.DROP_NON_REDIR
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_DROP_NON_REDIR(x)               (LAN80XX_ENCODE_BITFIELD(x,4,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_DROP_NON_REDIR                  (LAN80XX_BIT(4))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_DROP_NON_REDIR(x)               (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * brief
 * crypt-authenticate mode
 *
 * \details
 * 0b = Disables crypt-authenticate mode
 * 1b = Enable crypt-authenticate mode
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1.CRYPT_AUTH
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_FLOW_CRYPT_AUTH(x)              (LAN80XX_ENCODE_BITFIELD(x,5,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_FLOW_CRYPT_AUTH                 (LAN80XX_BIT(5))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_FLOW_CRYPT_AUTH(x)              (LAN80XX_EXTRACT_BITFIELD(x,5,1))
/**
 *  brief
 *  Drop action (action type)
 *
 * \details
 *  00b = bypass with CRC corruption signaling
 *  01b = bypass with bad frame indicator
 *  10b = internal drop by crypto-core (frame is not seen outside)
 *  11b = do not drop (for debugging only).
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1.DROP_ACTION
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_DROP_ACTION(x)                  (LAN80XX_ENCODE_BITFIELD(x,6,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_DROP_ACTION                     (LAN80XX_BIT(6))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_DROP_ACTION(x)                  (LAN80XX_EXTRACT_BITFIELD(x,6,2))
/**
 * brief
 * Replay Protection enable
 *
 * \details
 * 1b = enable replay protection
 * 0b = disable replay protection
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1.REPLAY_PROTECT
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_REPLAY_PROTECT(x)               (LAN80XX_ENCODE_BITFIELD(x,16,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_REPLAY_PROTECT                  (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_REPLAY_PROTECT(x)               (LAN80XX_EXTRACT_BITFIELD(x,16,1))
/**
 * brief
 * Controls processing of 'data' frames that have a SecTAG.
 *
 * \details
 * 1b = pass for the further processing by SecY Controlled port
 * 0b = drop.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1.ALLOW_TAGGED_DATA
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_ALLOW_TAGGED_DATA(x)            (LAN80XX_ENCODE_BITFIELD(x,17,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_ALLOW_TAGGED_DATA               (LAN80XX_BIT(17))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_ALLOW_TAGGED_DATA(x)            (LAN80XX_EXTRACT_BITFIELD(x,17,1))
/**
 * brief
 * Controls processing of 'data' frames that do not have SecTAG.
 *
 * \details
 * 1b = bypass unmodified
 * 0b = drop
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1.ALLOW_UNTAGGED_DATA
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_ALLOW_UNTAGGED_DATA(x)          (LAN80XX_ENCODE_BITFIELD(x,18,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_ALLOW_UNTAGGED_DATA             (LAN80XX_BIT(18))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_ALLOW_UNTAGGED_DATA(x)          (LAN80XX_EXTRACT_BITFIELD(x,18,1))
/**
 * brief
 * Frame validation level for the tagged frames
 *
 * \details
 *  00b = disabled
 *  01b = check
 *  10b = strict
 *  11b = null
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1.VALIDATE_FRAMES_TAGGED
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_VALIDATE_FRAMES_TAGGED(x)       (LAN80XX_ENCODE_BITFIELD(x,19,2))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_VALIDATE_FRAMES_TAGGED          (LAN80XX_BIT(19))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_VALIDATE_FRAMES_TAGGED(x)       (LAN80XX_EXTRACT_BITFIELD(x,19,2))

/**
 * brief
 * There exists a 32-bit control word between the last MPLS label and the inner Ethernet header.
 *
 * \details
 * 1b = 32-bit control word present.
 * 0b = 32-bit control word not present.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1.EOMPLS_CTRL_WORD
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_EOMPLS_CTRL_WORD(x)             (LAN80XX_ENCODE_BITFIELD(x,22,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_EOMPLS_CTRL_WORD                (LAN80XX_BIT(22))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_EOMPLS_CTRL_WORD(x)             (LAN80XX_EXTRACT_BITFIELD(x,22,1))

/**
 * brief
 * MPLS frame is assumed Ethernet over MPLS
 *
 * \details
 * 1b =  the MPLS frame is assumed Ethernet over MPLS.
 * 0b =  the MPLS frame is assumed as MPLS.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1.EOMPLS_SUBPORT
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_EOMPLS_SUBPORT(x)               (LAN80XX_ENCODE_BITFIELD(x,23,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_EOMPLS_SUBPORT                  (LAN80XX_BIT(23))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_EOMPLS_SUBPORT(x)               (LAN80XX_EXTRACT_BITFIELD(x,23,1))

/**
 * brief
 * Flow control 2 page 0 registers 0-31 SC..
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : MACSEC_INGR_CORE_EIP_161B_E_128_CT_P_MCHP_FLOW_CONTROL_PAGE1 .MACSEC_INGR_CORE_SAM_FLOW_CTRL2
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2(ri)                                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x1c01 | (ri*2))))


/**
 * brief
 * Pre-SecTAG Authentication Start
 *
 * \details
 * Specifies number of bytes from the start of the frame to be bypassed without MACsec protection.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2.PRE_SECTAG_AUTH_START
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_PRE_SECTAG_AUTH_START(x)        (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_PRE_SECTAG_AUTH_START           (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_PRE_SECTAG_AUTH_START(x)        (LAN80XX_EXTRACT_BITFIELD(x,0,6))
/**
 * brief
 * Pre-SecTAG Authentication length
 *
 * \details
 * Specifies number of bytes to be authenticated in the pre-SecTAG area.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2.PRE_SECTAG_AUTH_LEN
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_PRE_SECTAG_AUTH_LEN(x)          (LAN80XX_ENCODE_BITFIELD(x,8,6))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_PRE_SECTAG_AUTH_LEN             (LAN80XX_BIT(8))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_PRE_SECTAG_AUTH_LEN(x)          (LAN80XX_EXTRACT_BITFIELD(x,8,6))
/**
 * brief
 * Sectag offset length
 *
 * \details
 *  7-bit wide, absolute offset from the start of the frame where to insert the SecTAG
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2.SECTAG_OFFSET
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_SECTAG_OFFSET(x)                (LAN80XX_ENCODE_BITFIELD(x,16,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_SECTAG_OFFSET                   (LAN80XX_BIT(16))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_SECTAG_OFFSET(x)                (LAN80XX_EXTRACT_BITFIELD(x,16,7))

/**
 * brief
 * Confidentiality offset
 *
 * \details
 * The number of bytes (in the range of 0-127) to be authenticated but not encrypted following the SecTAG in the encrypted MACsec frame.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2.CONFIDENTIALITY_OFFSET
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_CONFIDENTIALITY_OFFSET(x)       (LAN80XX_ENCODE_BITFIELD(x,24,8))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_CONFIDENTIALITY_OFFSET          (LAN80XX_BIT(24))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_CONFIDENTIALITY_OFFSET(x)       (LAN80XX_EXTRACT_BITFIELD(x,24,8))
/**
 * brief
 * SC to SA MAP for 0 - 31 SCs
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0. SAM_SC_SA_MAP1_X
 */
#define LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X(ri)                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0xE00 | (ri*2))))

/**
 * brief
 * Index of secure Assosiation for AN = 0
 *
 * \details
 *  Specifies the which secure assosiation is mapped
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X . SA_INDEX0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX0(x)                   (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX0                      (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX0(x)                   (LAN80XX_EXTRACT_BITFIELD(x,0,7))
/**
 * brief
 * Secure Assosiation Index Update for AN =0
 *
 * \details
 *  1b = update sa_index0 and update_time0 but do not change sa_in_use0
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X . SA_INDEX_UPDATE0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX_UPDATE0(x)            (LAN80XX_ENCODE_BITFIELD(x,13,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX_UPDATE0               (LAN80XX_BIT(13))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX_UPDATE0(x)            (LAN80XX_EXTRACT_BITFIELD(x,13,1))
/**
 * brief
 * Update Time of Secure Assosiation for AN = 0
 *
 * \details
 *  1b = Update time stamp for SA
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X . UPDATE_TIME0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_UPDATE_TIME0(x)             (LAN80XX_ENCODE_BITFIELD(x,14,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_UPDATE_TIME0                (LAN80XX_BIT(14))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_UPDATE_TIME0(x)             (LAN80XX_EXTRACT_BITFIELD(x,14,1))
/**
 * brief
 * SA in use for AN =0
 *
 * \details
 * 1b = MACsec SA0 inUse for the looked-up SA.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X . SA_IN_USE0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_IN_USE0(x)                  (LAN80XX_ENCODE_BITFIELD(x,15,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_IN_USE0                     (LAN80XX_BIT(15))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_IN_USE0(x)                  (LAN80XX_EXTRACT_BITFIELD(x,15,1))
/**
 * brief
 * Index of secure Assosiation for AN = 1
 *
 * \details
 *  Specifies the which secure assosiation is mapped
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X . SA_INDEX1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX1(x)                   (LAN80XX_ENCODE_BITFIELD(x,16,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX1                      (LAN80XX_ENCODE_BITMASK(16,7))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX1(x)                   (LAN80XX_EXTRACT_BITFIELD(x,16,7))
/**
 * brief
 * Secure Assosiation Index Update for AN = 1
 *
 * \details
 *  1b = update sa_index1 and update_time1 but do not change sa_in_use1
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X . SA_INDEX_UPDATE1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX_UPDATE1(x)            (LAN80XX_ENCODE_BITFIELD(x,29,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX_UPDATE1               (LAN80XX_BIT(29))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX_UPDATE1(x)            (LAN80XX_EXTRACT_BITFIELD(x,29,1))
/**
 * brief
 * Update Time of Secure Assosiation for AN = 1
 *
 * \details
 *  1b = Update time stamp for SA
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X . UPDATE_TIME1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_UPDATE_TIME1(x)             (LAN80XX_ENCODE_BITFIELD(x,30,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_UPDATE_TIME1                (LAN80XX_BIT(30))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_UPDATE_TIME1(x)             (LAN80XX_EXTRACT_BITFIELD(x,30,1))
/**
 * brief
 * SA in use for AN = 1
 *
 * \details
 * 1b = MACsec SA1 inUse for the looked-up SA.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X . SA_IN_USE1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_IN_USE1(x)                  (LAN80XX_ENCODE_BITFIELD(x,31,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_IN_USE1                     (LAN80XX_BIT(31))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_IN_USE1(x)                  (LAN80XX_EXTRACT_BITFIELD(x,31,1))

/**
 * brief
 * SC to SA MAP for 0 - 31 SCs when AN = 2 and AN =3
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0. SAM_SC_SA_MAP1_X
 */
#define LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X(ri)                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0xE01 | (ri*2))))
/**
 * brief
 * Index of secure Assosiation for AN = 2
 *
 * \details
 *  Specifies the which secure assosiation is mapped
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X . SA_INDEX1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX2(x)                   (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX2                      (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX2(x)                   (LAN80XX_EXTRACT_BITFIELD(x,0,7))
/**
 * brief
 * Secure Assosiation Index Update for AN = 2
 *
 * \details
 *  1b = update sa_index2 and update_time2 but do not change sa_in_use2
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X . SA_INDEX_UPDATE2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX_UPDATE2(x)            (LAN80XX_ENCODE_BITFIELD(x,13,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX_UPDATE2               (LAN80XX_BIT(13))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX_UPDATE2(x)            (LAN80XX_EXTRACT_BITFIELD(x,13,1))
/**
 * brief
 * Update Time of Secure Assosiation for AN = 2
 *
 * \details
 *  1b = Update time stamp for SA
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X . UPDATE_TIME2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_UPDATE_TIME2(x)             (LAN80XX_ENCODE_BITFIELD(x,14,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_UPDATE_TIME2                (LAN80XX_BIT(14))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_UPDATE_TIME2(x)             (LAN80XX_EXTRACT_BITFIELD(x,14,1))
/**
 * brief
 * SA in use for AN = 2
 *
 * \details
 * 1b = MACsec SA1 inUse for the looked-up SA.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X . SA_IN_USE2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_IN_USE2(x)                  (LAN80XX_ENCODE_BITFIELD(x,15,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_IN_USE2                     (LAN80XX_BIT(15))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_IN_USE2(x)                  (LAN80XX_EXTRACT_BITFIELD(x,15,1))
/**
 * brief
 * Index of secure Assosiation for AN = 3
 *
 * \details
 *  Specifies the which secure assosiation is mapped
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X . SA_INDEX3
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX3(x)                   (LAN80XX_ENCODE_BITFIELD(x,16,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX3                      (LAN80XX_ENCODE_BITMASK(16,7))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX3(x)                   (LAN80XX_EXTRACT_BITFIELD(x,16,7))
/**
 * brief
 * Secure Assosiation Index Update for AN = 3
 *
 * \details
 *  1b = update sa_index3 and update_time3 but do not change sa_in_use3
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X . SA_INDEX_UPDATE3
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX_UPDATE3(x)            (LAN80XX_ENCODE_BITFIELD(x,29,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX_UPDATE3               (LAN80XX_BIT(29))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX_UPDATE3(x)            (LAN80XX_EXTRACT_BITFIELD(x,29,1))
/**
 * brief
 * Update Time of Secure Assosiation for AN = 3
 *
 * \details
 *  1b = Update time stamp for SA
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X . UPDATE_TIME3
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_UPDATE_TIME3(x)             (LAN80XX_ENCODE_BITFIELD(x,30,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_UPDATE_TIME3                (LAN80XX_BIT(30))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_UPDATE_TIME3(x)             (LAN80XX_EXTRACT_BITFIELD(x,30,1))
/**
 * brief
 * SA in use for AN = 3
 *
 * \details
 * 1b = MACsec SA1 inUse for the looked-up SA.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X . SA_IN_USE3
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_IN_USE3(x)                  (LAN80XX_ENCODE_BITFIELD(x,31,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_IN_USE3                     (LAN80XX_BIT(31))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_IN_USE3(x)                  (LAN80XX_EXTRACT_BITFIELD(x,31,1))






/**
 * brief
 * SC to SA MAP for 32 - 63 SCs
 * \details
 * Secure Assosiation map to secure channel
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1. SAM_SC_SA_MAP1_X
 */
#define LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X(ri)                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x4E00 | (ri*2))))
/**
 * brief
 * Index of secure Assosiation for AN = 0
 *
 * \details
 *  Specifies the which secure assosiation is mapped
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X . SA_INDEX0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX0(x)                   (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX0                      (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX0(x)                   (LAN80XX_EXTRACT_BITFIELD(x,0,7))
/**
 * brief
 * Secure Assosiation Index Update for AN =0
 *
 * \details
 *  1b = update sa_index0 and update_time0 but do not change sa_in_use0
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X . SA_INDEX_UPDATE0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX_UPDATE0(x)            (LAN80XX_ENCODE_BITFIELD(x,13,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX_UPDATE0               (LAN80XX_BIT(13))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX_UPDATE0(x)            (LAN80XX_EXTRACT_BITFIELD(x,13,1))
/**
 * brief
 * Update Time of Secure Assosiation for AN = 0
 *
 * \details
 *  1b = Update time stamp for SA
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X . UPDATE_TIME0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_UPDATE_TIME0(x)             (LAN80XX_ENCODE_BITFIELD(x,14,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_UPDATE_TIME0                (LAN80XX_BIT(14))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_UPDATE_TIME0(x)             (LAN80XX_EXTRACT_BITFIELD(x,14,1))

/**
 * brief
 * SA in use for AN =0
 *
 * \details
 * 1b = MACsec SA0 inUse for the looked-up SA.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X . SA_IN_USE0
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_IN_USE0(x)                  (LAN80XX_ENCODE_BITFIELD(x,15,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_IN_USE0                     (LAN80XX_BIT(15))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_IN_USE0(x)                  (LAN80XX_EXTRACT_BITFIELD(x,15,1))
/**
 * brief
 * Index of secure Assosiation for AN = 1
 *
 * \details
 *  Specifies the which secure assosiation is mapped
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X . SA_INDEX1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX1(x)                   (LAN80XX_ENCODE_BITFIELD(x,16,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX1                      (LAN80XX_ENCODE_BITMASK(16,7))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX1(x)                   (LAN80XX_EXTRACT_BITFIELD(x,16,7))
/**
 * brief
 * Secure Assosiation Index Update for AN = 1
 *
 * \details
 *  1b = update sa_index1 and update_time1 but do not change sa_in_use1
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X . SA_INDEX_UPDATE1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX_UPDATE1(x)            (LAN80XX_ENCODE_BITFIELD(x,29,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX_UPDATE1               (LAN80XX_BIT(29))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX_UPDATE1(x)            (LAN80XX_EXTRACT_BITFIELD(x,29,1))
/**
 * brief
 * Update Time of Secure Assosiation for AN = 1
 *
 * \details
 *  1b = Update time stamp for SA
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X . UPDATE_TIME1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_UPDATE_TIME1(x)             (LAN80XX_ENCODE_BITFIELD(x,30,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_UPDATE_TIME1                (LAN80XX_BIT(30))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_UPDATE_TIME1(x)             (LAN80XX_EXTRACT_BITFIELD(x,30,1))
/**
 * brief
 * SA in use for AN = 1
 *
 * \details
 * 1b = MACsec SA1 inUse for the looked-up SA.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X . SA_IN_USE1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_IN_USE1(x)                  (LAN80XX_ENCODE_BITFIELD(x,31,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_IN_USE1                     (LAN80XX_BIT(31))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_IN_USE1(x)                  (LAN80XX_EXTRACT_BITFIELD(x,31,1))

/**
 * brief
 * SC to SA MAP for 0 - 31 SCs when AN = 2 and AN =3
 *
 * \details
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1. SAM_SC_SA_MAP1_X
 */
#define LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X(ri)                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x4E01 | (ri*2))))
/**
 * brief
 * Index of secure Assosiation for AN = 2
 *
 * \details
 *  Specifies the which secure assosiation is mapped
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X . SA_INDEX1
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX2(x)                   (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX2                      (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX2(x)                   (LAN80XX_EXTRACT_BITFIELD(x,0,7))
/**
 * brief
 * Secure Assosiation Index Update for AN = 2
 *
 * \details
 *  1b = update sa_index2 and update_time2 but do not change sa_in_use2
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X . SA_INDEX_UPDATE2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX_UPDATE2(x)            (LAN80XX_ENCODE_BITFIELD(x,13,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX_UPDATE2               (LAN80XX_BIT(13))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX_UPDATE2(x)            (LAN80XX_EXTRACT_BITFIELD(x,13,1))
/**
 * brief
 * Update Time of Secure Assosiation for AN = 2
 *
 * \details
 *  1b = Update time stamp for SA
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X . UPDATE_TIME2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_UPDATE_TIME2(x)             (LAN80XX_ENCODE_BITFIELD(x,14,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_UPDATE_TIME2                (LAN80XX_BIT(14))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_UPDATE_TIME2(x)             (LAN80XX_EXTRACT_BITFIELD(x,14,1))
/**
 * brief
 * SA in use for AN = 2
 *
 * \details
 * 1b = MACsec SA1 inUse for the looked-up SA
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X . SA_IN_USE2
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_IN_USE2(x)                  (LAN80XX_ENCODE_BITFIELD(x,15,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_IN_USE2                     (LAN80XX_BIT(15))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_IN_USE2(x)                  (LAN80XX_EXTRACT_BITFIELD(x,15,1))
/**
 * brief
 * Index of secure Assosiation for AN = 3
 *
 * \details
 *  Specifies the which secure assosiation is mapped
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X . SA_INDEX3
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX3(x)                   (LAN80XX_ENCODE_BITFIELD(x,16,7))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX3                      (LAN80XX_ENCODE_BITMASK(16,7))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX3(x)                   (LAN80XX_EXTRACT_BITFIELD(x,16,7))
/**
 * brief
 * Secure Assosiation Index Update for AN = 3
 *
 * \details
 *  1b = update sa_index3 and update_time3 but do not change sa_in_use3
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X . SA_INDEX_UPDATE3
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX_UPDATE3(x)            (LAN80XX_ENCODE_BITFIELD(x,29,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX_UPDATE3               (LAN80XX_BIT(29))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX_UPDATE3(x)            (LAN80XX_EXTRACT_BITFIELD(x,29,1))
/**
 * brief
 * Update Time of Secure Assosiation for AN = 3
 *
 * \details
 *  1b = Update time stamp for SA
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X . UPDATE_TIME3
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_UPDATE_TIME3(x)             (LAN80XX_ENCODE_BITFIELD(x,30,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_UPDATE_TIME3                (LAN80XX_BIT(30))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_UPDATE_TIME3(x)             (LAN80XX_EXTRACT_BITFIELD(x,30,1))
/**
 * brief
 * SA in use for AN = 3
 *
 * \details
 * 1b = MACsec SA1 inUse for the looked-up SA.
 *
 * Field: LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X . SA_IN_USE3
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_IN_USE3(x)                  (LAN80XX_ENCODE_BITFIELD(x,31,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_IN_USE3                     (LAN80XX_BIT(31))
#define  LAN80XX_X_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_IN_USE3(x)                  (LAN80XX_EXTRACT_BITFIELD(x,31,1))

/**
 * \brief
 * Rx SC Secure channel Identifier LSB - page 0
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0 : RXSC_SCI_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0_RXSC_SCI_LO(ri)                                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0xD00 | (ri*4))))

/**
 * \brief
 * Rx SC Secure channel Identifier MSB - page 0
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0 : RXSC_SCI_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0_RXSC_SCI_HI(ri)                                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0xD01 | (ri*4))))

/**
 * \brief
 * Rx SC Control Register - Page 0
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0 : RXSC_CAM_CTRL
 */
#define LAN80XX_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0_RXSC_CAM_CTRL(ri)                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0xD02 | (ri*4))))

/**
 * \brief
 * Rx SC Secure channel Identifier LSB - page 1
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE1 : RXSC_SCI_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE1_RXSC_SCI_LO(ri)                                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x4D00 | (ri*4))))

/**
 * \brief
 * Rx SC Secure channel Identifier MSB - page 1
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE1 : RXSC_SCI_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE1_RXSC_SCI_HI(ri)                                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x4D01 | (ri*4))))

/**
 * \brief
 * Rx SC Control Register - Page 1
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE1 : RXSC_CAM_CTRL
 */
#define LAN80XX_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE1_RXSC_CAM_CTRL(ri)                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, (0x4D02 | (ri*4))))

/**
 * \brief
 * Rx SC Secy Index
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0_RXSC_CAM_CTRL : VPORT_INDEX
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0_RXSC_CAM_CTRL_VPORT_INDEX(x)                 (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0_RXSC_CAM_CTRL_VPORT_INDEX                    (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0_RXSC_CAM_CTRL_VPORT_INDEX(x)                 (LAN80XX_EXTRACT_BITFIELD(x,0,6))

/**
 * \brief
 * Rx SC Secy Index
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_RXSC_ENTRY_ENABLE_CTRL
 */
#define LAN80XX_MACSEC_INGR_CORE_RXSC_ENTRY_ENABLE_CTRL                                             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0xDC0))

/**
 * \brief
 * Rx SC Index
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_RXSC_ENTRY_ENABLE_CTRL : SC_INDEX_SET
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_RXSC_ENTRY_ENABLE_CTRL_SC_INDEX_SET(x)                          (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_MACSEC_INGR_CORE_RXSC_ENTRY_ENABLE_CTRL_SC_INDEX_SET                             (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_RXSC_ENTRY_ENABLE_CTRL_SC_INDEX_SET(x)                          (LAN80XX_EXTRACT_BITFIELD(x,0,6))

/**
 * \brief
 * Rx SC Enable
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_RXSC_ENTRY_ENABLE_CTR : SET_ENABLE
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_RXSC_ENTRY_ENABLE_CTRL_SET_ENABLE(x)                            (LAN80XX_ENCODE_BITFIELD(x,14,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_RXSC_ENTRY_ENABLE_CTRL_SET_ENABLE                               (LAN80XX_BIT(14))
#define  LAN80XX_X_MACSEC_INGR_CORE_RXSC_ENTRY_ENABLE_CTRL_SET_ENABLE(x)                            (LAN80XX_EXTRACT_BITFIELD(x,14,1))


/**
 * \brief
 * Sequence Number (low part)
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP161_EIP62_EIP62_REGISTERS:MACSEC_INGR_CORE_EIP62_NEXTPN_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXTPN_LO                                          (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x3D20))

/**
 * \brief
 * Sequence Number (MSB part)
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP161_EIP62_EIP62_REGISTERS:MACSEC_INGR_CORE_EIP62_NEXTPN_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXTPN_HI                                          (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x3D21))
/**
 * \brief
 * Sequence Number (MSB part)
 *
 * \details
 * Register: MACSEC_INGR_CORE:MACSEC_INGR_CORE_EIP161_EIP62_EIP62_REGISTERS:MACSEC_INGR_CORE_EIP62_NEXTPN_CTRL
 */
#define LAN80XX_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL                          (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1, 0x3D23))

/**
 * brief
 * When read it provides the status of the nextPN update. After enabling the update this bit automatically flips to zero when the action is completed.
 *
 *
 * Field: MACSEC_INGR_CORE_EIP62_NEXTPN_CTRL . ENABLE_UPDATE
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_ENABLE_UPDATE(x)      (LAN80XX_ENCODE_BITFIELD(x,0,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_ENABLE_UPDATE         (LAN80XX_BIT(0))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_ENABLE_UPDATE(x)      (LAN80XX_EXTRACT_BITFIELD(x,0,1))
/**
 * brief
 * This read only bit indicates if the previous update action resulted in a sequence number update into the context memory.
 *
 *
 * Field: MACSEC_INGR_CORE_EIP62_NEXTPN_CTRL . NEXTPN_WRITTEN
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_NEXTPN_WRITTEN(x)     (LAN80XX_ENCODE_BITFIELD(x,1,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_NEXTPN_WRITTEN        (LAN80XX_BIT(1))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_NEXTPN_WRITTEN(x)     (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * brief
 * This bit must be set to '1' if the nextPN is a 64-bit sequence number. This bit must be written with a '0' if the nextPN is a 32-bit sequence number.
 *
 *
 * Field: MACSEC_INGR_CORE_EIP62_NEXTPN_CTRL . SEQUENCE_NUMBER_SIZE
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_SEQUENCE_NUMBER_SIZE(x) (LAN80XX_ENCODE_BITFIELD(x,2,1))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_SEQUENCE_NUMBER_SIZE  (LAN80XX_BIT(2))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_SEQUENCE_NUMBER_SIZE(x) (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * brief
 * This field must contain the 16B (128-bit) aligned pointer to the context word containing the sequence number that must be validated and
 * potentially updated with the programmed nextPN.
 *
 * Field: MACSEC_INGR_CORE_EIP62_NEXTPN_CTRL . NEXTPN_CONTEXT_ADDRESS
 */
#define  LAN80XX_F_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_NEXTPN_CONTEXT_ADDRESS(x) (LAN80XX_ENCODE_BITFIELD(x,4,28))
#define  LAN80XX_M_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_NEXTPN_CONTEXT_ADDRESS (LAN80XX_BIT(4))
#define  LAN80XX_X_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_NEXTPN_CONTEXT_ADDRESS(x) (LAN80XX_EXTRACT_BITFIELD(x,4,28))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Octets Decrypted LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INOCTETSDECRYPTED_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INOCTETSDECRYPTED_LO(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2000 | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Octets Decrypted MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INOCTETSDECRYPTED_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INOCTETSDECRYPTED_HI(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2001 | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Octets validated LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INOCTETSVALIDATED_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INOCTETSVALIDATED_LO(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2002 | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Octets validated MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INOCTETSVALIDATED_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INOCTETSVALIDATED_HI(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2003 | (ri*32))))
/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Unchecked LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSUNCHECKED_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSUNCHECKED_LO(ri)                          (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2004 | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Unchecked MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSUNCHECKED_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSUNCHECKED_HI(ri)                          (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2005 | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Delayed LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSDELAYED_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSDELAYED_LO(ri)                            (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2006 | (ri*32))))
/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Delayed MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSDELAYED_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSDELAYED_HI(ri)                            (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2007 | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Late LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSLATE_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSLATE_LO(ri)                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2008 | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Late MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSLATE_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSLATE_HI(ri)                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2009 | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Ok LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSOK_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSOK_LO(ri)                                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x200a | (ri*32))))
/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Ok MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSOK_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSOK_HI(ri)                                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x200b | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Invalid LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSINVALID_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSINVALID_LO(ri)                            (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x200c | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Invalid MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSINVALID_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSINVALID_HI(ri)                            (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x200d | (ri*32))))
/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Not Valid LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSNOTVALID_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSNOTVALID_LO(ri)                           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x200e | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Not Valid MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSNOTVALID_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSNOTVALID_HI(ri)                           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x200f | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Not Using SA LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSNOTUSINGSA_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSNOTUSINGSA_LO(ri)                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2010 | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Not Using SA MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSNOTUSINGSA_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSNOTUSINGSA_HI(ri)                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2011 | (ri*32))))
/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Unused SA LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSUNUSEDSA_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSUNUSEDSA_LO(ri)                           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2012 | (ri*32))))

/**
 * \brief
 * SA Statistics 0 - 64
 *
 * \details
 * Packets Unused SA MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE0 . INPKTSUNUSEDSA_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSUNUSEDSA_HI(ri)                           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x2013 | (ri*32))))



/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Octets Decrypted LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INOCTETSDECRYPTED_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INOCTETSDECRYPTED_LO(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x6000 | (ri*32))))
/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Octets Decrypted MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INOCTETSDECRYPTED_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INOCTETSDECRYPTED_HI(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x6001 | (ri*32))))

/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Octets validated LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INOCTETSVALIDATED_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INOCTETSVALIDATED_LO(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x6002 | (ri*32))))

/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Octets validated MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INOCTETSVALIDATED_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INOCTETSVALIDATED_HI(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x6003 | (ri*32))))

/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Unchecked LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSUNCHECKED_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSUNCHECKED_LO(ri)                          (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x6004 | (ri*32))))
/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Unchecked MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSUNCHECKED_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSUNCHECKED_HI(ri)                          (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x6005 | (ri*32))))

/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Delayed LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSDELAYED_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSDELAYED_LO(ri)                            (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x6006 | (ri*32))))
/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Delayed MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSDELAYED_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSDELAYED_HI(ri)                            (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x6007 | (ri*32))))

/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Late LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSLATE_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSLATE_LO(ri)                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x6008 | (ri*32))))
/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Late MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSLATE_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSLATE_HI(ri)                               (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x6009 | (ri*32))))

/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Ok LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSOK_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSOK_LO(ri)                                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x600a | (ri*32))))

/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Ok MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSOK_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSOK_HI(ri)                                 (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x600b | (ri*32))))

/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Invalid LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSINVALID_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSINVALID_LO(ri)                            (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x600c | (ri*32))))
/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Invalid MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSINVALID_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSINVALID_HI(ri)                            (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x600d | (ri*32))))
/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Not Valid LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSNOTVALID_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSNOTVALID_LO(ri)                           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x600e | (ri*32))))

/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Not Valid MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSNOTVALID_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSNOTVALID_HI(ri)                           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x600f | (ri*32))))

/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Not Using SA LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSNOTUSINGSA_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSNOTUSINGSA_LO(ri)                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x6010 | (ri*32))))
/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Not Using SA MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSNOTUSINGSA_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSNOTUSINGSA_HI(ri)                         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x6011 | (ri*32))))

/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Unused SA LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSUNUSEDSA_LO
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSUNUSEDSA_LO(ri)                           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1,(0x6012 | (ri*32))))

/**
 * \brief
 * SA Statistics 64 - 128
 *
 * \details
 * Packets Unused SA MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_INGR_STAT_SA_COUNTERS_PAGE1 . INPKTSUNUSEDSA_HI
 */
#define  LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSUNUSEDSA_HI(ri)                           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x6013 | (ri*32))))
/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Transform error packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . TRANSFORMERRORPKTS_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_TRANSFORMERRORPKTS_LO(ri)                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x2800 | (ri*32))))

/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Transform error packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . TRANSFORMERRORPKTS_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_TRANSFORMERRORPKTS_HI(ri)                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x2801 | (ri*32))))

/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Controlled In packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSCTRL_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSCTRL_LO(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x2802 | (ri*32))))

/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Controlled In packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSCTRL_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSCTRL_HI(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x2803 | (ri*32))))
/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Untagged In packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSUNTAGGED_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSUNTAGGED_LO(ri)                    (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x2804 | (ri*32))))

/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Untagged In packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSUNTAGGED_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSUNTAGGED_HI(ri)                    (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x2805 | (ri*32))))

/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Packets with No tag LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSNOTAG_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSNOTAG_LO(ri)                       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x2806 | (ri*32))))

/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Packets with No tag MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSNOTAG_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSNOTAG_HI(ri)                       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x2807 | (ri*32))))
/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Packets with Bad tag LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSBADTAG_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSBADTAG_LO(ri)                      (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x2808 | (ri*32))))

/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Packets with Bad tag MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSBADTAG_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSBADTAG_HI(ri)                      (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x2809 | (ri*32))))

/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Packets with No SCI LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSNOSCI_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSNOSCI_LO(ri)                       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x280a | (ri*32))))

/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Packets with No SCI MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSNOSCI_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSNOSCI_HI(ri)                       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x280b | (ri*32))))
/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Packets with Unknown SCI LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSUNKNOWNSCI_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSUNKNOWNSCI_LO(ri)                  (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x280c | (ri*32))))

/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Packets with Unknown SCI MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSUNKNOWNSCI_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSUNKNOWNSCI_HI(ri)                  (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x280d | (ri*32))))

/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Tagged Packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSTAGGEDCTRL_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSTAGGEDCTRL_LO(ri)                  (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x280e | (ri*32))))

/**
 * \brief
 * SecY Counters 0 - 32
 *
 * \details
 * Tagged Packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0 . INPKTSTAGGEDCTRL_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSTAGGEDCTRL_HI(ri)                  (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x280f | (ri*32))))
/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Transform error packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . TRANSFORMERRORPKTS_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_TRANSFORMERRORPKTS_LO(ri)                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x6800 | (ri*32))))

/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Transform error packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . TRANSFORMERRORPKTS_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_TRANSFORMERRORPKTS_HI(ri)                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x6801 | (ri*32))))

/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Controlled In packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSCTRL_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSCTRL_LO(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x6802 | (ri*32))))
/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Controlled In packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSCTRL_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSCTRL_HI(ri)                        (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x6803 | (ri*32))))
/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Untagged In packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSUNTAGGED_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSUNTAGGED_LO(ri)                    (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x6804 | (ri*32))))

/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Untagged In packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSUNTAGGED_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSUNTAGGED_HI(ri)                    (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x6805 | (ri*32))))
/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Packets with No tag LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSNOTAG_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSNOTAG_LO(ri)                       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x6806 | (ri*32))))

/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Packets with No tag MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSNOTAG_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSNOTAG_HI(ri)                       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x6807 | (ri*32))))
/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Packets with Bad tag LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSBADTAG_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSBADTAG_LO(ri)                      (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x6808 | (ri*32))))

/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Packets with Bad tag MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSBADTAG_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSBADTAG_HI(ri)                      (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x6809 | (ri*32))))
/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Packets with No SCI LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSNOSCI_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSNOSCI_LO(ri)                       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x680a | (ri*32))))

/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Packets with No SCI MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSNOSCI_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSNOSCI_HI(ri)                       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x680b | (ri*32))))
/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Packets with Unknown SCI LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSUNKNOWNSCI_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSUNKNOWNSCI_LO(ri)                  (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x680c | (ri*32))))
/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Packets with Unknown SCI MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSUNKNOWNSCI_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSUNKNOWNSCI_HI(ri)                  (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x680d | (ri*32))))

/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Tagged Packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSTAGGEDCTRL_LO
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSTAGGEDCTRL_LO(ri)                  (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x680e | (ri*32))))

/**
 * \brief
 * SecY Counters 32 - 64
 *
 * \details
 * Tagged Packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1 . INPKTSTAGGEDCTRL_HI
 */
#define  LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSTAGGEDCTRL_HI(ri)                  (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x680f | (ri*32))))
/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * Uncontrolled Port out octets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINOCTETSUNCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINOCTETSUNCONTROLLED_LO(ri)              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x3000 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * Uncontrolled Port out octets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINOCTETSUNCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINOCTETSUNCONTROLLED_HI(ri)              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x3001 | (ri*32))))
/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * Controlled Port out octets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINOCTETSCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINOCTETSCONTROLLED_LO(ri)                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x3002 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * Controlled Port out octets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINOCTETSCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINOCTETSCONTROLLED_HI(ri)                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x3003 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * Uncontrolled Port out unicast packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINUCASTPKTSUNCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINUCASTPKTSUNCONTROLLED_LO(ri)           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x3004 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * Uncontrolled Port out unicast packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINUCASTPKTSUNCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINUCASTPKTSUNCONTROLLED_HI(ri)           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x3005 | (ri*32))))
/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * Uncontrolled Port out multicast packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINMULTICASTPKTSUNCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINMULTICASTPKTSUNCONTROLLED_LO(ri)       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x3006 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * Uncontrolled Port out multicast packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINMULTICASTPKTSUNCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINMULTICASTPKTSUNCONTROLLED_HI(ri)       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x3007 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * Uncontrolled Port out broadcast packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINBROADCASTPKTSUNCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINBROADCASTPKTSUNCONTROLLED_LO(ri)       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x3008 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * Uncontrolled Port out broadcast packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINBROADCASTPKTSUNCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINBROADCASTPKTSUNCONTROLLED_HI(ri)       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x3009 | (ri*32))))
/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * controlled Port out unicast packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINUCASTPKTSCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINUCASTPKTSCONTROLLED_LO(ri)             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x300a | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * controlled Port out unicast packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINUCASTPKTSCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINUCASTPKTSCONTROLLED_HI(ri)             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x300b | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * controlled Port out multicast packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINMULTICASTPKTSCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINMULTICASTPKTSCONTROLLED_LO(ri)         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x300c | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * controlled Port out multicast packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINMULTICASTPKTSCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINMULTICASTPKTSCONTROLLED_HI(ri)         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x300d | (ri*32))))
/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * controlled Port out broadcast packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINBROADCASTPKTSCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINBROADCASTPKTSCONTROLLED_LO(ri)         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x300e | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 0 - 32 SecY
 *
 * \details
 * controlled Port out broadcast packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0 . IFINBROADCASTPKTSCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINBROADCASTPKTSCONTROLLED_HI(ri)         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x300f | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * Uncontrolled Port out octets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINOCTETSUNCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINOCTETSUNCONTROLLED_LO(ri)              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x7000 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * Uncontrolled Port out octets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINOCTETSUNCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINOCTETSUNCONTROLLED_HI(ri)              (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x7001 | (ri*32))))
/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * Controlled Port out octets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINOCTETSCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINOCTETSCONTROLLED_LO(ri)                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x7002 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * Controlled Port out octets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINOCTETSCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINOCTETSCONTROLLED_HI(ri)                (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x7003 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * Uncontrolled Port out unicast packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINUCASTPKTSUNCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINUCASTPKTSUNCONTROLLED_LO(ri)           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x7004 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * Uncontrolled Port out unicast packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINUCASTPKTSUNCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINUCASTPKTSUNCONTROLLED_HI(ri)           (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x7005 | (ri*32))))
/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * Uncontrolled Port out multicast packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINMULTICASTPKTSUNCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINMULTICASTPKTSUNCONTROLLED_LO(ri)       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x7006 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * Uncontrolled Port out multicast packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINMULTICASTPKTSUNCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINMULTICASTPKTSUNCONTROLLED_HI(ri)       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x7007 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * Uncontrolled Port out broadcast packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINBROADCASTPKTSUNCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINBROADCASTPKTSUNCONTROLLED_LO(ri)       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x7008 | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * Uncontrolled Port out broadcast packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINBROADCASTPKTSUNCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINBROADCASTPKTSUNCONTROLLED_HI(ri)       (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x7009 | (ri*32))))
/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * controlled Port out unicast packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINUCASTPKTSCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINUCASTPKTSCONTROLLED_LO(ri)             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x700a | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * controlled Port out unicast packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINUCASTPKTSCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINUCASTPKTSCONTROLLED_HI(ri)             (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x700b | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * controlled Port out multicast packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINMULTICASTPKTSCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINMULTICASTPKTSCONTROLLED_LO(ri)         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x700c | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * controlled Port out multicast packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINMULTICASTPKTSCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINMULTICASTPKTSCONTROLLED_HI(ri)         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x700d | (ri*32))))
/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * controlled Port out broadcast packets LSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINBROADCASTPKTSCONTROLLED_LO
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINBROADCASTPKTSCONTROLLED_LO(ri)         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x700e | (ri*32))))

/**
 * brief
 * Interface Statistcs(IFC) for 33 - 64 SecY
 *
 * \details
 * controlled Port out broadcast packets MSB
 *
 * Field: MACSEC_INGR_CORE : LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1 . IFINBROADCASTPKTSCONTROLLED_HI
 */
#define LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINBROADCASTPKTSCONTROLLED_HI(ri)         (LAN80XX_IOREG(MMD_ID_MACSEC_INGR, 1 ,(0x700f | (ri*32))))

#endif /* _LAN80XX_MALIBU25G_REGS_MACSEC_INGR_H_ */
