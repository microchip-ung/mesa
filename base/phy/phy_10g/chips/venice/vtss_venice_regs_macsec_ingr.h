// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_VENICE_REGS_MACSEC_INGR_H_
#define _VTSS_VENICE_REGS_MACSEC_INGR_H_


#include "vtss_venice_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a MACSEC_INGR
 *
 * Flow-through MACsec egress and ingress IP registers
 *
 ***********************************************************************/

/**
 * Register Group: \a MACSEC_INGR:MACSEC_CTL_REGS
 *
 * MACsec Ingress and Egress wrapper control registers.
 */


/** 
 * \brief Mode configuration register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_CTL_REGS:MACSEC_ENA_CFG
 */
#define VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG  VTSS_IOREG(0x1f, 1, 0x0800)

/** 
 * \brief
 * MACsec clock enable.
 *
 * \details 
 * 0: All clocks for this module with the exception of CSR clock are
 * disabled.
 * 1: All clocks for this module are enabled.
 *
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG . CLK_ENA
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA  VTSS_BIT(0)

/** 
 * \brief
 * MACsec software reset
 *
 * \details 
 * 0: Block operates normally.
 * 1: All logic (other than CSR target) is held in reset, clocks are not
 * disabled.
 *
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG . SW_RST
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST  VTSS_BIT(1)

/** 
 * \brief
 * MACsec bypass enable.
 * This bit gets higher priority over MACSEC_ENA.
 *
 * \details 
 * 0: MACsec block is not in bypass mode. Write MACSEC_ENA = 1 to pass data
 * through the MACsec block.
 * 1: MACsec block is in bypass mode.
 *
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG . MACSEC_BYPASS_ENA
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA  VTSS_BIT(8)

/** 
 * \brief
 * MACsec block enable.
 * To enable the MACsec block, also write MACSEC_BYPASS_ENA = 0.
 *
 * \details 
 * 0: MACSEC block is not enabled.
 * 1: MACSEC block is enabled.
 *
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG . MACSEC_ENA
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA  VTSS_BIT(9)

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
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG . MACSEC_SPEED_MODE
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,3)


/** 
 * \brief MACsec control configuration register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_CTL_REGS:MACSEC_CTL_CFG
 */
#define VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG  VTSS_IOREG(0x1f, 1, 0x0801)

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
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG . MAC_CTRL_FRAMES_SRC_PORT
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_MAC_CTRL_FRAMES_SRC_PORT(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_MAC_CTRL_FRAMES_SRC_PORT     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_MAC_CTRL_FRAMES_SRC_PORT(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

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
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG . MAC_DATA_FRAMES_SRC_PORT
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_MAC_DATA_FRAMES_SRC_PORT(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_MAC_DATA_FRAMES_SRC_PORT     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_MAC_DATA_FRAMES_SRC_PORT(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Enables all the packets failing security check to be transmitted with
 * corrupted FCS, which consists of a debug fault code to debug the
 * security failing packet. The format of the fault code is as follows:
 *  {
 *   1'b0, pkt_tx_sa_hit (1-bit), pkt_tx_sa_index (6-bits),
 * pkt_tx_global_stat_event (14-bits), pkt_tx_stat_event (10-bits)
 *   };
 * The 32nd bit is a reserved bit used by the MAC to make sure that the FCS
 * is corrupted.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG . ENA_SEC_FAIL_DEBUG_CODE_IN_FCS
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_ENA_SEC_FAIL_DEBUG_CODE_IN_FCS  VTSS_BIT(4)


/** 
 * \brief Error sticky bits of MACsec register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_CTL_REGS:MACSEC_STICKY
 */
#define VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY  VTSS_IOREG(0x1f, 1, 0x0802)

/** 
 * \brief
 * Indicates pkt64to128 FIFO overflow
 * The block will still work properly after abort marking a frame. Most
 * likely cause of this is a misconfiguration.
 *
 * \details 
 * 0: No overflow in pkt64to128 FIFO
 * 1: pkt64to128 FIFO overflowed at least once
 *
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY . PKT64TO128_FIFO_OVERFLOW_STICKY
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY_PKT64TO128_FIFO_OVERFLOW_STICKY  VTSS_BIT(5)

/** 
 * \brief
 * Indicates ECC error in SA store RAM while reading SA
 *
 * \details 
 * 0: No ECC error
 * 1: ECC error occurred at least once
 *
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY . SA_STORE_RAM_INTEGRITY_ERROR_STICKY
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY_SA_STORE_RAM_INTEGRITY_ERROR_STICKY  VTSS_BIT(6)

/** 
 * \brief
 * Indicates ECC error in STAT RAM while reading statistics
 *
 * \details 
 * 0: No ECC error
 * 1: ECC error occurred at least once
 *
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY . STAT_RAM_INTEGRITY_ERROR_STICKY
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY_STAT_RAM_INTEGRITY_ERROR_STICKY  VTSS_BIT(7)


/** 
 * \brief Interrupt mask sticky bits register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_CTL_REGS:MACSEC_STICKY_MASK
 */
#define VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK  VTSS_IOREG(0x1f, 1, 0x0803)

/** 
 * \brief
 * Interrupt mask for PKT64TO128_FIFO_OVERFLOW_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK . PKT64TO128_FIFO_OVERFLOW_STICKY_MASK
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK_PKT64TO128_FIFO_OVERFLOW_STICKY_MASK  VTSS_BIT(5)

/** 
 * \brief
 * Interrupt mask for SA_STORE_RAM_INTEGRITY_ERROR_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK . SA_STORE_RAM_INTEGRITY_ERROR_STICKY_MASK
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK_SA_STORE_RAM_INTEGRITY_ERROR_STICKY_MASK  VTSS_BIT(6)

/** 
 * \brief
 * Interrupt mask for STAT_RAM_INTEGRITY_ERROR_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK . STAT_RAM_INTEGRITY_ERROR_STICKY_MASK
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK_STAT_RAM_INTEGRITY_ERROR_STICKY_MASK  VTSS_BIT(7)


/** 
 * \brief MACsec ingress latency configuration register
 *
 * \details
 * Register: \a MACSEC_INGR:MACSEC_CTL_REGS:MACSEC_IGR_LATENCY_CFG
 */
#define VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_IGR_LATENCY_CFG  VTSS_IOREG(0x1f, 1, 0x0804)

/** 
 * \brief
 * Fixed latency of ingress MACsec block
 * The minimum latency the frame will undergo, specified in terms of
 * enabled clocks.
 * Variable latency of a frame is calculated by measuring the actual
 * latency of the SOF and subtracting fixed latency.
 *   Var_latency = measured latency - fixed latency
 * The maximum possible variable latency is MAX_LATENCY - FIXED LATENCY.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_IGR_LATENCY_CFG . IGR_MSEC_LATENCY
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_IGR_LATENCY_CFG_IGR_MSEC_LATENCY(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_IGR_LATENCY_CFG_IGR_MSEC_LATENCY     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_IGR_LATENCY_CFG_IGR_MSEC_LATENCY(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Maximum latency of ingress MACsec block
 * The maximum latency the frame can undergo, specified in terms of enabled
 * clocks.
 * Variable latency of a frame is calculated by measuring the actual
 * latency of the SOF and subtracting fixed latency.
 *   Var_latency = measured latency - fixed latency
 * The maximum possible variable latency is MAX_LATENCY - FIXED LATENCY.
 * If a frame's SOF is not seen in the FIXED LATENCY-to-MAX_LATENCY window,
 * the frame is deemed to have been dropped within the MACsec block.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_IGR_LATENCY_CFG . IGR_MSEC_MAX_LATENCY
 */
#define  VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_IGR_LATENCY_CFG_IGR_MSEC_MAX_LATENCY(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_IGR_LATENCY_CFG_IGR_MSEC_MAX_LATENCY     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_IGR_LATENCY_CFG_IGR_MSEC_MAX_LATENCY(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * Register Group: \a MACSEC_INGR:XFORM_RECORD_REGS
 *
 * Transform context records
 */


/** 
 * \brief Transform record data 0
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA0
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA0(ri)  VTSS_IOREG(0x1f, 1, 0x0000 | (ri * 32))


/** 
 * \brief Transform record data 1
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA1
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA1(ri)  VTSS_IOREG(0x1f, 1, 0x0001 | (ri * 32))


/** 
 * \brief Transform record data 2
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA2
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA2(ri)  VTSS_IOREG(0x1f, 1, 0x0002 | (ri * 32))


/** 
 * \brief Transform record data 3
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA3
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA3(ri)  VTSS_IOREG(0x1f, 1, 0x0003 | (ri * 32))


/** 
 * \brief Transform record data 4
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA4
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA4(ri)  VTSS_IOREG(0x1f, 1, 0x0004 | (ri * 32))


/** 
 * \brief Transform record data 5
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA5
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA5(ri)  VTSS_IOREG(0x1f, 1, 0x0005 | (ri * 32))


/** 
 * \brief Transform record data 6
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA6
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA6(ri)  VTSS_IOREG(0x1f, 1, 0x0006 | (ri * 32))


/** 
 * \brief Transform record data 7
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA7
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA7(ri)  VTSS_IOREG(0x1f, 1, 0x0007 | (ri * 32))


/** 
 * \brief Transform record data 8
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA8
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA8(ri)  VTSS_IOREG(0x1f, 1, 0x0008 | (ri * 32))


/** 
 * \brief Transform record data 9
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA9
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA9(ri)  VTSS_IOREG(0x1f, 1, 0x0009 | (ri * 32))


/** 
 * \brief Transform record data 10
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA10
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA10(ri)  VTSS_IOREG(0x1f, 1, 0x000a | (ri * 32))


/** 
 * \brief Transform record data 11
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA11
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA11(ri)  VTSS_IOREG(0x1f, 1, 0x000b | (ri * 32))


/** 
 * \brief Transform record data 12
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA12
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA12(ri)  VTSS_IOREG(0x1f, 1, 0x000c | (ri * 32))


/** 
 * \brief Transform record data 13
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA13
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA13(ri)  VTSS_IOREG(0x1f, 1, 0x000d | (ri * 32))


/** 
 * \brief Transform record data 14
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA14
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA14(ri)  VTSS_IOREG(0x1f, 1, 0x000e | (ri * 32))


/** 
 * \brief Transform record data 15
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA15
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA15(ri)  VTSS_IOREG(0x1f, 1, 0x000f | (ri * 32))


/** 
 * \brief Transform record data 16
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA16
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA16(ri)  VTSS_IOREG(0x1f, 1, 0x0010 | (ri * 32))


/** 
 * \brief Transform record data 17
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA17
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA17(ri)  VTSS_IOREG(0x1f, 1, 0x0011 | (ri * 32))


/** 
 * \brief Transform record data 18
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA18
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA18(ri)  VTSS_IOREG(0x1f, 1, 0x0012 | (ri * 32))


/** 
 * \brief Transform record data 19
 *
 * \details
 * Register: \a MACSEC_INGR:XFORM_RECORD_REGS:XFORM_REC_DATA19
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA19(ri)  VTSS_IOREG(0x1f, 1, 0x0013 | (ri * 32))

/**
 * Register Group: \a MACSEC_INGR:SA_MATCH_PARAMS
 *
 * Programmable Secure Association compare parameters
 */


/** 
 * \brief Secure Association match MAC_SA & Ether-type compare registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_PARAMS:SAM_MAC_SA_MATCH_LO
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_LO(ri)  VTSS_IOREG(0x1f, 1, 0x1000 | (ri * 16))


/** 
 * \brief Secure Association match MAC_SA & Ether-type compare registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_PARAMS:SAM_MAC_SA_MATCH_HI
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI(ri)  VTSS_IOREG(0x1f, 1, 0x1001 | (ri * 16))

/** 
 * \brief
 * Bits [7:0] :: mac_sa_match[15:8] :: Bits [15:8] of one MAC_SA compare
 * value (compare-enabled per byte) 
 * Bits [15:8] :: mac_sa_match[7:0] :: Bits [7:0] of one MAC_SA compare
 * value (compare-enabled per byte), last byte received
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI . MAC_SA_MATCH_15_TO_0
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_MAC_SA_MATCH_15_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_MAC_SA_MATCH_15_TO_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_MAC_SA_MATCH_15_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Parsed Ether-type compare value (stored byte swapped, for instance
 * MACsec tag value 0x88E5 
 * would be stored as 0xE588 in this field) 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI . ETHER_TYPE
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_ETHER_TYPE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_ETHER_TYPE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_ETHER_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Secure Association match MAC_DA & VLAN ID compare registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_PARAMS:SAM_MAC_DA_MATCH_LO
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_LO(ri)  VTSS_IOREG(0x1f, 1, 0x1002 | (ri * 16))


/** 
 * \brief Secure Association match MAC_DA & VLAN ID compare registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_PARAMS:SAM_MAC_DA_MATCH_HI
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI(ri)  VTSS_IOREG(0x1f, 1, 0x1003 | (ri * 16))

/** 
 * \brief
 * Bits [7:0] :: mac_da_match[15:8] :: Bits [15:8] of one MAC_DA compare
 * value (compare-enabled per byte) 
 * Bits [15:8] :: mac_da_match[7:0] :: Bits [7:0] of one MAC_DA compare
 * value (compare-enabled per byte), last byte received
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI . MAC_DA_MATCH_15_TO_0
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_MAC_DA_MATCH_15_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_MAC_DA_MATCH_15_TO_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_MAC_DA_MATCH_15_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Parsed VLAN ID compare value
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI . VLAN_ID
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_VLAN_ID(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_VLAN_ID     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_VLAN_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,12)


/** 
 * \brief Secure Association match miscellaneous compare registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_PARAMS:SAM_MISC_MATCH
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH(ri)  VTSS_IOREG(0x1f, 1, 0x1004 | (ri * 16))

/** 
 * \brief
 * Parsed VLAN valid flag compare value.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . VLAN_VALID
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_VLAN_VALID  VTSS_BIT(0)

/** 
 * \brief
 * Parsed Q-in-Q found flag compare value.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . QINQ_FOUND
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_QINQ_FOUND  VTSS_BIT(1)

/** 
 * \brief
 * Parsed STAG valid flag compare value.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . STAG_VALID
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_STAG_VALID  VTSS_BIT(2)

/** 
 * \brief
 * Parsed QTAG valid flag compare value.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . QTAG_VALID
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_QTAG_VALID  VTSS_BIT(3)

/** 
 * \brief
 * Parsed VLAN User Priority compare value.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . VLAN_UP
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_VLAN_UP(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_VLAN_UP     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_VLAN_UP(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * Control packet (as pre-decoded) compare value.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . CONTROL_PACKET
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_CONTROL_PACKET  VTSS_BIT(7)

/** 
 * \brief
 * Untagged packet match enable.
 *
 * \details 
 * 1b: Allow packets without a MACsec tag to match (MACsec tag
 * classification logic output).
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . UNTAGGED
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_UNTAGGED  VTSS_BIT(8)

/** 
 * \brief
 * Tagged packet match enable.
 *
 * \details 
 * 1b: Allow packets with a standard and valid MACsec tag to match (MACsec
 * tag classification logic output).
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . TAGGED
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_TAGGED  VTSS_BIT(9)

/** 
 * \brief
 * Invalid tag match enable.
 *
 * \details 
 * 1b: Allow packets with an invalid MACsec tag to match (MACsec tag
 * classification logic output).
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . BAD_TAG
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_BAD_TAG  VTSS_BIT(10)

/** 
 * \brief
 * Kay handling tag match enable.
 *
 * \details 
 * 1b: Allow packets with a MACsec tag indicating Kay handling to be done
 * to match (MACsec tag classification logic output).
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . KAY_TAG
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_KAY_TAG  VTSS_BIT(11)

/** 
 * \brief
 * Source port compare value.
 *
 * \details 
 * 00b: Common port
 * 01b: Reserved port 
 * 10b: Controlled port 
 * 11b: Uncontrolled port
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . SOURCE_PORT
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_SOURCE_PORT(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_SOURCE_PORT     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_SOURCE_PORT(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Priority of this entry for determining the actual transform used on a
 * match when multiple entries match.
 * In case of identical priorities, the lowest numbered entry takes
 * precedence. 
 *
 * \details 
 * 0: Lowest 
 * 15: Highest
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . MATCH_PRIORITY
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_MATCH_PRIORITY(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_MATCH_PRIORITY     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_MATCH_PRIORITY(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * MACsec tag control information (TCI)/association number (AN) byte
 * compare value bits are individually masked for comparing. The tag
 * control information bits are in bits [31:26] while the association
 * number bits are in bits [25:24]. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . MACSEC_TCI_AN
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_MACSEC_TCI_AN(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_MACSEC_TCI_AN     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_MACSEC_TCI_AN(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/** 
 * \brief Secure Association match MACsec secure channels identifier compare registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_PARAMS:SAM_SCI_MATCH_LO
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_SCI_MATCH_LO(ri)  VTSS_IOREG(0x1f, 1, 0x1005 | (ri * 16))


/** 
 * \brief Secure Association match MACsec secure channels identifier compare registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_PARAMS:SAM_SCI_MATCH_HI
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_SCI_MATCH_HI(ri)  VTSS_IOREG(0x1f, 1, 0x1006 | (ri * 16))


/** 
 * \brief Secure Association match mask registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_PARAMS:SAM_MASK
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK(ri)  VTSS_IOREG(0x1f, 1, 0x1007 | (ri * 16))

/** 
 * \brief
 * MAC source address mask bits.
 * Bit[0] is the last byte received of the source address; bit[5] is the
 * first byte received of the source address.
 *
 * \details 
 * 1b: Enable compare of corresponding source address byte in
 * SAM_MAC_SA_MATCH_HI / LO register
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . MAC_SA_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_MAC_SA_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_MAC_SA_MASK     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_MAC_SA_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * MAC destination address mask bits.
 * Bit[0] is the last byte received of the destination address; bit[5] is
 * the first byte received of the destination address.
 *
 * \details 
 * 1b: Enable compare of corresponding destination address byte in
 * SAM_MAC_DA_MATCH_HI / LO register
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . MAC_DA_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_MAC_DA_MASK(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_MAC_DA_MASK     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_MAC_DA_MASK(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \details 
 * 1b: Enable parsed Ether-type field compare with ether_type field in the
 * SAM_MAC_DA_MATCH_LO register
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . MAC_ETYPE_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_MAC_ETYPE_MASK  VTSS_BIT(12)

/** 
 * \details 
 * 1b: Enable parsed VLAN valid flag compare with vlan_valid bit in the
 * SAM_MISC_MATCH register 
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . VLAN_VLD_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_VLAN_VLD_MASK  VTSS_BIT(13)

/** 
 * \details 
 * 1b: Enable parsed Q-in-Q found flag compare with qinq_found field in the
 * SAM_MISC_MATCH register 
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . QINQ_FOUND_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_QINQ_FOUND_MASK  VTSS_BIT(14)

/** 
 * \details 
 * 1b: Enable parsed STAG valid flag compare with stag_valid bit in the
 * SAM_MISC_MATCH register
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . STAG_VLD_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_STAG_VLD_MASK  VTSS_BIT(15)

/** 
 * \details 
 * 1b: Enable parsed QTAG valid flag compare with qtag_valid bit in the
 * SAM_MISC_MATCH register 
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . QTAG_VLD_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_QTAG_VLD_MASK  VTSS_BIT(16)

/** 
 * \details 
 * 1b: Enable parsed VLAN user priority value compare with vlan_up field in
 * the SAM_MISC_MATCH register 
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . VLAN_UP_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_VLAN_UP_MASK  VTSS_BIT(17)

/** 
 * \details 
 * 1b: Enable parsed VLAN ID value compare with vlan_id field in the
 * SAM_MAC_DA_MATCH_HI register
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . VLAN_ID_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_VLAN_ID_MASK  VTSS_BIT(18)

/** 
 * \details 
 * 1b: Enable source port compare with source_port field in the
 * SAM_MISC_MATCH register
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . SOURCE_PORT_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_SOURCE_PORT_MASK  VTSS_BIT(19)

/** 
 * \details 
 * 1b: Enable control packet status compare with control_packet bit in the
 * SAM_MISC_MATCH register 
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . CTL_PACKET_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_CTL_PACKET_MASK  VTSS_BIT(20)

/** 
 * \brief
 * The VLAN user priority inner mask comparison needs Q-in-Q found flag
 * comparison enabled.
 *
 * \details 
 * 1b: Enable parsed inner VLAN user priority value compare with
 * vlan_up_inner field in the 
 * SAM_EXT_MATCH_x register
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . VLAN_UP_INNER_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_VLAN_UP_INNER_MASK  VTSS_BIT(21)

/** 
 * \brief
 * The VLAN ID inner mask comparison needs QinQ found flag comparison
 * enabled
 *
 * \details 
 * 1b: Enable parsed inner VLAN ID value compare with vlan_up_inner field
 * in the SAM_EXT_MATCH_x register
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . VLAN_ID_INNER_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_VLAN_ID_INNER_MASK  VTSS_BIT(22)

/** 
 * \brief
 * Enable comparison only for an actual MACsec packet
 *
 * \details 
 * 1b: Enable MACsec header secure channel identifier value compare with 64
 * bits secure channel identifier value in the SAM_SCI_MATCH_LO/HI
 * registers
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . MACSEC_SCI_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_MACSEC_SCI_MASK  VTSS_BIT(23)

/** 
 * \brief
 * Separate compare enable bits for the macsec_tci_an field in the
 * SAM_MISC_MATCH register should only be set to non-zero for an actual
 * MACsec packet. Tag control information is in bits [31:26] while the
 * association number is in bits [25:24]. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK . TCI_AN_MASK
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_TCI_AN_MASK(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_TCI_AN_MASK     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_TCI_AN_MASK(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/** 
 * \brief Secure Association match extended.
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_PARAMS:SAM_EXT_MATCH
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_EXT_MATCH(ri)  VTSS_IOREG(0x1f, 1, 0x1008 | (ri * 16))

/** 
 * \brief
 * Parsed inner VLAN ID compare value
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_EXT_MATCH . VLAN_ID_INNER
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_ID_INNER(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_ID_INNER     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_ID_INNER(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/** 
 * \brief
 * Parsed inner VLAN Up compare value 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_EXT_MATCH . VLAN_UP_INNER
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_UP_INNER(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_UP_INNER     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_UP_INNER(x)  VTSS_EXTRACT_BITFIELD(x,12,3)


/** 
 * \brief Secure Association header bypass match register
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_PARAMS:SAM_HDR_BYPASS_MATCH1
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MATCH1(ri)  VTSS_IOREG(0x1f, 1, 0x1009 | (ri * 16))


/** 
 * \brief Secure Association header bypass match register
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_PARAMS:SAM_HDR_BYPASS_MATCH2
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MATCH2(ri)  VTSS_IOREG(0x1f, 1, 0x100a | (ri * 16))


/** 
 * \brief Secure Association match header bypass mask register
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_PARAMS:SAM_HDR_BYPASS_MASK1
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK1(ri)  VTSS_IOREG(0x1f, 1, 0x100b | (ri * 16))


/** 
 * \brief Secure Association match header bypass mask register
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_PARAMS:SAM_HDR_BYPASS_MASK2
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK2(ri)  VTSS_IOREG(0x1f, 1, 0x100c | (ri * 16))

/**
 * Register Group: \a MACSEC_INGR:SA_MATCH_CTL_PARAMS
 *
 * Programmable Secure Association compare parameters
 */


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_ENABLE1
 */
#define VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE1  VTSS_IOREG(0x1f, 1, 0x1800)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_ENABLE2
 */
#define VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE2  VTSS_IOREG(0x1f, 1, 0x1801)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_TOGGLE1
 */
#define VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE1  VTSS_IOREG(0x1f, 1, 0x1804)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_TOGGLE2
 */
#define VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE2  VTSS_IOREG(0x1f, 1, 0x1805)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_SET1
 */
#define VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_SET1  VTSS_IOREG(0x1f, 1, 0x1808)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_SET2
 */
#define VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_SET2  VTSS_IOREG(0x1f, 1, 0x1809)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_CLEAR1
 */
#define VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_CLEAR1  VTSS_IOREG(0x1f, 1, 0x180c)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_INGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_CLEAR2
 */
#define VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_CLEAR2  VTSS_IOREG(0x1f, 1, 0x180d)


/** 
 * \brief Secure Association match in flights register
 *
 * \details
 * This register provides the possibility to track the number of packets in
 * the pipeline for hardware/software synchronization purposes.
 *
 * Register: \a MACSEC_INGR:SA_MATCH_CTL_PARAMS:SAM_IN_FLIGHT
 */
#define VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT  VTSS_IOREG(0x1f, 1, 0x1810)

/** 
 * \brief
 * Unsafe 
 * Number of packets in the MACsec IP pipeline that might want to use a SA
 * that has been disabled. This counter is copied from the in_flight
 * counter when any of the enable_X bits drop from 1b to 0b and then
 * decrements towards zero on every packet that has been handled by  the
 * statistics counters module (this includes packets that are officially
 * dropped). 
 * After disabling a SA, the host software should wait until this field is
 * zero before final readout of the SA statistics and re-using the
 * transform record.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT . UNSAFE
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_UNSAFE(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_UNSAFE     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_UNSAFE(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Inflight
 * Number of packets in the MACsec IP pipeline. This counter increments on
 * every packet entering the pipeline for classification and decrements on
 * every packet that has been handled by the statistics counters module,
 * including packets that are officially dropped.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT . IN_FLIGHT
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_IN_FLIGHT(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_IN_FLIGHT     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_IN_FLIGHT(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Load unsafe
 * Debug functionality: 1b = Load unsafe field in this register with
 * contents of in_flight field of that 
 * same register to start counting down. Just like when disabling a SA
 * match entry, writing 0b has no effect.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT . LOAD_UNSAFE
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_LOAD_UNSAFE  VTSS_BIT(31)

/**
 * Register Group: \a MACSEC_INGR:SA_MATCH_FLOW_CONTROL_PARAMS_IGR
 *
 * 16/64 flow control words for frames that matched a Secure Association parameter set
 */


/** 
 * \brief Secure Association match flow control
 *
 * \details
 * This register provides control over the processing of packets that
 * matched one of the 16/64 SA matching entries.
 *
 * Register: \a MACSEC_INGR:SA_MATCH_FLOW_CONTROL_PARAMS_IGR:SAM_FLOW_CTRL_IGR
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR(ri)  VTSS_IOREG(0x1f, 1, 0x1c00 | (ri))

/** 
 * \brief
 * Flow type
 * The static_bypass bit in the MISC_CONTROL register can disable the
 * MACsec crypto-core, forcing 
 * the MACsec operation to bypass. The contents of this field are not
 * influenced by this overruling.
 *
 * \details 
 * 00b: Bypass
 * 01b: Perform drop_action
 * 10b: MACsec ingress (do not use in an egress-only core)
 * 11b: MACsec egress (do not use in an ingress-only core)
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR . FLOW_TYPE
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_FLOW_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_FLOW_TYPE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_FLOW_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Destination port
 *
 * \details 
 * 00b: Common port
 * 01b: Reserved port
 * 10b: Controlled port
 * 11b: Uncontrolled port
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR . DEST_PORT
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_DEST_PORT     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Perform drop_action if packet is not from the reserved port. This bit is
 * reserved for an egress-only (-e) configuration.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR . DROP_NON_RESERVED
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_DROP_NON_RESERVED  VTSS_BIT(4)

/** 
 * \brief
 * Enables basic crypt-authenticate mode. Must be set to 0b for all non
 * crypt-authenticate actions.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR . FLOW_CRYPT_AUTH
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_FLOW_CRYPT_AUTH  VTSS_BIT(5)

/** 
 * \brief
 * Defines the way the drop operation is performed.
 * If drop_action 10b (internal drop) is selected in static_bypass mode,
 * the drop operation is forced to CRC corruption (mode 00b) the actual
 * field value is not influenced here.
 *
 * \details 
 * 00b: Bypass with CRC corruption signaling
 * 01b: Bypass with bad packet indicator
 * 10b: Internal drop by crypto-core (packet is not seen outside)
 * 11b: Do not drop (for debugging only)
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR . DROP_ACTION
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_DROP_ACTION     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * This function is used for MACsec ingress processing only (flow_type =
 * 10b) 
 *
 * \details 
 * 1b: Enable replay protection
 * 0b: Disable replay protection 
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR . REPLAY_PROTECT
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_REPLAY_PROTECT  VTSS_BIT(16)

/** 
 * \details 
 * 1b: MACsec Secure Association in use for the looked-up Secure
 * Association
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR . SA_IN_USE
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_SA_IN_USE  VTSS_BIT(17)

/** 
 * \brief
 * Frame validation level for MACsec ingress processing only (flow_type =
 * 10b) 
 *
 * \details 
 * 00b: Disabled
 * 01b: Check
 * 10b: Strict
 * 11b: Reserved 
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR . VALIDATE_FRAMES
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_VALIDATE_FRAMES(x)  VTSS_ENCODE_BITFIELD(x,19,2)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_VALIDATE_FRAMES     VTSS_ENCODE_BITMASK(19,2)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_VALIDATE_FRAMES(x)  VTSS_EXTRACT_BITFIELD(x,19,2)

/** 
 * \brief
 * The number of bytes (in the range of 0-64) that are be authenticated but
 * not encrypted following the SecTag in the encrypted MACsec packet.
 *
 * \details 
 * 65-127: Reserved (do not use)
 *
 * Field: VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR . CONFIDENTIALITY_OFFSET
 */
#define  VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_CONFIDENTIALITY_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_CONFIDENTIALITY_OFFSET     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_CONFIDENTIALITY_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * Register Group: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS
 *
 * Control packet classification parameters
 */


/** 
 * \brief Control packet individual MAC_DA and Ethertype match compare register
 *
 * \details
 * Register: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS:CP_MAC_DA_MATCH
 *
 * @param ri Register: CP_MAC_DA_MATCH, 0-9
 */
#define VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_MATCH(ri)  VTSS_IOREG(0x1f, 1, 0x1e00 | (ri * 2))


/** 
 * \brief Control packet individual MAC_DA and Ethertype match compare register
 *
 * \details
 * Register: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS:CP_MAC_DA_ET_MATCH
 *
 * @param ri Register: CP_MAC_DA_ET_MATCH, 0-9
 */
#define VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH(ri)  VTSS_IOREG(0x1f, 1, 0x1e01 | (ri * 2))

/** 
 * \brief
 * Bits [7:0] :: mac_da_match[15:8] :: Bits [15:8] of one MAC_DA compare
 * value 
 * Bits [15:8] :: mac_da_match[7:0] :: Bits [7:0] of one MAC_DA compare
 * value, last byte received
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH . MAC_DA_MATCH_15_TO_0
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_TO_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * One Ethertype compare value (for the Ethertype field directly following
 * the MAC_SA), stored byte swapped, for instance MACsec tag value 0x88E5
 * is stored as 0xE588 in this field.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH . ETHER_TYPE_MATCH
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Ethertype match register
 *
 * \details
 * Covers the individual Ethertype compare values from 10 to 17.
 *
 * Register: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS:CP_MAC_ET_MATCH
 *
 * @param ri Register: CP_MAC_ET_MATCH, 0-7
 */
#define VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_ET_MATCH(ri)  VTSS_IOREG(0x1f, 1, 0x1e14 | (ri))

/** 
 * \brief
 * One Ethertype compare value (for the Ethertype field directly following
 * the MAC_SA), stored 
 * byte swapped, for instance MACsec tag value 0x88E5 is stored as 0xE588
 * in this field
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_ET_MATCH . ETHER_TYPE
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_ET_MATCH_ETHER_TYPE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_ET_MATCH_ETHER_TYPE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_ET_MATCH_ETHER_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * Register Group: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS2
 *
 * Control packet classification parameters
 */


/** 
 * \brief Control packet MAC_DA range check compare register
 *
 * \details
 * Register: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_START_LO
 */
#define VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_START_LO  VTSS_IOREG(0x1f, 1, 0x1e20)


/** 
 * \brief Control packet MAC_DA range check compare registers
 *
 * \details
 * Register: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_START_HI
 */
#define VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_START_HI  VTSS_IOREG(0x1f, 1, 0x1e21)

/** 
 * \brief
 * Bits [7:0] = mac_da_start[15:8]
 * Bits [15:8] of one MAC_DA range compare value.
 * Bits [15:8] = mac_da_start[7:0]
 * Bits [7:0] of one MAC_DA range compare value (last byte received).
 * Total match is when start value <= MAC_DA <= end value.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_START_HI . MAC_DA_START_15_TO_0
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_START_HI_MAC_DA_START_15_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_START_HI_MAC_DA_START_15_TO_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_START_HI_MAC_DA_START_15_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Control packet MAC_DA range check compare register
 *
 * \details
 * Register: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_END_LO
 */
#define VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_END_LO  VTSS_IOREG(0x1f, 1, 0x1e22)


/** 
 * \brief Control packet MAC_DA range check compare register
 *
 * \details
 * Register: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_END_HI
 */
#define VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_END_HI  VTSS_IOREG(0x1f, 1, 0x1e23)

/** 
 * \brief
 * Bits [7:0] = mac_da_end[15:8]
 * Bits [15:8] of one MAC_DA range compare value.
 * Bits [15:8] = mac_da_end[7:0]
 * Bits [7:0] of one MAC_DA range compare value (last byte received).
 * Total match is when start value <= MAC_DA <= end value.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_END_HI . MAC_DA_END_15_TO_0
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_END_HI_MAC_DA_END_15_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_END_HI_MAC_DA_END_15_TO_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_END_HI_MAC_DA_END_15_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Control packet MAC_DA constant 01_80_C2_00_00_0? compare register
 *
 * \details
 * Register: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_44_BITS_LO
 */
#define VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_LO  VTSS_IOREG(0x1f, 1, 0x1e24)


/** 
 * \brief Control packet MAC_DA constant 01_80_C2_00_00_0? compare register
 *
 * \details
 * Register: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_44_BITS_HI
 */
#define VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI  VTSS_IOREG(0x1f, 1, 0x1e25)

/** 
 * \brief
 * Bits [15:8] of MAC_DA 44 bits constant 01_80_C2_00_00_0? compare value
 * (byte swapped) reset value matches the given constant. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI . MAC_DA_44_BITS_15_TO_8
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI_MAC_DA_44_BITS_15_TO_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI_MAC_DA_44_BITS_15_TO_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI_MAC_DA_44_BITS_15_TO_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Bits [7:4] of MAC_DA 44 bits constant 01_80_C2_00_00_0? compare value
 * (byte swapped, last byte received) reset value matches the given
 * constant.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI . MAC_DA_44_BITS_7_TO_4
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI_MAC_DA_44_BITS_7_TO_4(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI_MAC_DA_44_BITS_7_TO_4     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI_MAC_DA_44_BITS_7_TO_4(x)  VTSS_EXTRACT_BITFIELD(x,12,4)


/** 
 * \brief Control packet MAC_DA constant 01_00_0C_CC_CC_CC compare register
 *
 * \details
 * Register: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_48_BITS_LO
 */
#define VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_48_BITS_LO  VTSS_IOREG(0x1f, 1, 0x1e26)


/** 
 * \brief Control packet MAC_DA constant 01_00_0C_CC_CC_CC compare register
 *
 * \details
 * Register: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_48_BITS_HI
 */
#define VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_48_BITS_HI  VTSS_IOREG(0x1f, 1, 0x1e27)

/** 
 * \brief
 * [7:0] mac_da_match[15:8] 
 * Bits [15:8] of MAC_DA 48 bits constant 01_00_0C_CC_CC_CC compare value
 * (byte swapped) reset value matches the given constant. 
 * [15:8] mac_da_match[7:0] 
 * Bits [7:0] of MAC_DA 48 bits constant 01_00_0C_CC_CC_CC compare value
 * (byte swapped, last byte received) reset value matches the given
 * constant. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_48_BITS_HI . MAC_DA_48_BITS_15_TO_0
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_48_BITS_HI_MAC_DA_48_BITS_15_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_48_BITS_HI_MAC_DA_48_BITS_15_TO_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_48_BITS_HI_MAC_DA_48_BITS_15_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Control packet match mode register
 *
 * \details
 * Register: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS2:CP_MATCH_MODE
 */
#define VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE  VTSS_IOREG(0x1f, 1, 0x1e3e)

/** 
 * \brief
 * Select which Ether-type to compare with 16 bit value in
 * CP_MAC_DA_ET_MATCH_x register
 *
 * \details 
 * 0b: Packet Ethertype (the first Ethertype in the packet) 
 * 1b: Parsed Ethertype (the parsed Ethertype as detected by algorithm)
 *
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE . ETYPE_SEL_9_TO_0
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_9_TO_0(x)  VTSS_ENCODE_BITFIELD(x,8,10)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_9_TO_0     VTSS_ENCODE_BITMASK(8,10)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_9_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,8,10)

/** 
 * \brief
 * Functionality equivalent to bits [17:8], but applicable for 16 bit value
 * in CP_MAC_ET_MATCH_10 to CP_MAC_ET_MATCH_17 registers respectively.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE . ETYPE_SEL_17_TO_10
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_17_TO_10(x)  VTSS_ENCODE_BITFIELD(x,21,8)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_17_TO_10     VTSS_ENCODE_BITMASK(21,8)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_17_TO_10(x)  VTSS_EXTRACT_BITFIELD(x,21,8)


/** 
 * \brief Control packet match enable register
 *
 * \details
 * Register: \a MACSEC_INGR:CTL_PACKET_CLASS_PARAMS2:CP_MATCH_ENABLE
 */
#define VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE  VTSS_IOREG(0x1f, 1, 0x1e3f)

/** 
 * \brief
 * [0] mac_da_0 
 * 1b = Enable MAC_DA compare with 48 bits value in CP_MAC_DA_MATCH_0 and
 * CP_MAC_DA_ET_MATCH_0 registers 
 * [1] mac_da_1 
 * 1b = Enable MAC_DA compare with 48 bits value in CP_MAC_DA_MATCH_1 and
 * CP_MAC_DA_ET_MATCH_1 registers 
 * [2] mac_da_2 
 * 1b = Enable MAC_DA compare with 48 bits value in CP_MAC_DA_MATCH_2 and
 * CP_MAC_DA_ET_MATCH_2 registers 
 * [3] mac_da_3 
 * 1b = Enable MAC_DA compare with 48 bits value in CP_MAC_DA_MATCH_3 and
 * CP_MAC_DA_ET_MATCH_3 registers 
 * [4] mac_da_4 
 * 1b = Enable MAC_DA compare with 48 bits value in CP_MAC_DA_MATCH_4 and
 * CP_MAC_DA_ET_MATCH_4 registers 
 * [5] mac_da_5 
 * 1b = Enable MAC_DA compare with 48 bits value in CP_MAC_DA_MATCH_5 and
 * CP_MAC_DA_ET_MATCH_5 registers 
 * [6] mac_da_6 
 * 1b = Enable MAC_DA compare with 48 bits value in CP_MAC_DA_MATCH_6 and
 * CP_MAC_DA_ET_MATCH_6 registers 
 * [7] mac_da_7 
 * 1b = Enable MAC_DA compare with 48 bits value in CP_MAC_DA_MATCH_7 and
 * CP_MAC_DA_ET_MATCH_7 registers
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . MAC_DA_ENABLE_7_TO_0
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_MAC_DA_ENABLE_7_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_MAC_DA_ENABLE_7_TO_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_MAC_DA_ENABLE_7_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * [8] e_type_0 
 * 1b = Enable Ether-type compare with 16 bits value in
 * CP_MAC_DA_ET_MATCH_0 register 
 * [9] e_type_1 
 * 1b = Enable Ether-type compare with 16 bits value in
 * CP_MAC_DA_ET_MATCH_1 register 
 * [10] e_type_2 
 * 1b = Enable Ether-type compare with 16 bits value in
 * CP_MAC_DA_ET_MATCH_2 register 
 * [11] e_type_3 
 * 1b = Enable Ether-type compare with 16 bits value in
 * CP_MAC_DA_ET_MATCH_3 register 
 * [12] e_type_4 
 * 1b = Enable Ether-type compare with 16 bits value in
 * CP_MAC_DA_ET_MATCH_4 register 
 * [13] e_type_5 
 * 1b = Enable Ether-type compare with 16 bits value in
 * CP_MAC_DA_ET_MATCH_5 register 
 * [14] e_type_6 
 * 1b = Enable Ether-type compare with 16 bits value in
 * CP_MAC_DA_ET_MATCH_6 register 
 * [15] e_type_7 
 * 1b = Enable Ether-type compare with 16 bits value in
 * CP_MAC_DA_ET_MATCH_7 register
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . ETYPE_ENABLE_7_TO_0
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_7_TO_0(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_7_TO_0     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_7_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * [16] comb_8 
 * 1b = Enable combined MAC_DA/Ether-type compare with 48 + 16 bits values
 * in CP_MAC_DA_MATCH_8 and CP_MAC_DA_ET_MATCH_8 registers 
 * [17] comb_9 
 * 1b = Enable combined MAC_DA/Ether-type compare with 48 + 16 bits values
 * in CP_MAC_DA_MATCH_9 and CP_MAC_DA_ET_MATCH_9 registers
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . COMB_ENABLE_9_TO_8
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_COMB_ENABLE_9_TO_8(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_COMB_ENABLE_9_TO_8     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_COMB_ENABLE_9_TO_8(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Match is found when START = MAC_DA = END
 *
 * \details 
 * 1b: Enable MAC_DA range compare with lower and upper bound values in
 * CP_MAC_DA_START_LO/HI and CP_MAC_DA_END_LO/HI registers
 *
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . RANGE_ENABLE
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_RANGE_ENABLE  VTSS_BIT(18)

/** 
 * \brief
 * The lowest 4 bits of MAC_DA are not compared
 *
 * \details 
 * 1b: Enable MAC_DA compare against programmable 44 bits constant.
 * 01_80_C2_00_00_0 in CP_MAC_DA_44_BITS_LO/HI registers
 *
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . CONST_44_ENABLE
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_CONST_44_ENABLE  VTSS_BIT(19)

/** 
 * \details 
 * 1b: Enable MAC_DA compare against programmable 48 bits constant.
 * 01_00_0C_CC_CC_CC in CP_MAC_DA_48_BITS_LO/HI registers
 *
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . CONST_48_ENABLE
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_CONST_48_ENABLE  VTSS_BIT(20)

/** 
 * \details 
 * 1b: Enable Ethertype compare with 16 bits value in CP_MAC_ET_MATCH_x
 * register
 *
 * Field: VTSS_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . ETYPE_ENABLE_17_TO_10
 */
#define  VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_17_TO_10(x)  VTSS_ENCODE_BITFIELD(x,21,8)
#define  VTSS_M_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_17_TO_10     VTSS_ENCODE_BITMASK(21,8)
#define  VTSS_X_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_17_TO_10(x)  VTSS_EXTRACT_BITFIELD(x,21,8)

/**
 * Register Group: \a MACSEC_INGR:FRAME_MATCHING_HANDLING_CTRL
 *
 * Frame matching and handling control registers
 */


/** 
 * \brief VLAN tag detection
 *
 * \details
 * Register: \a MACSEC_INGR:FRAME_MATCHING_HANDLING_CTRL:SAM_CP_TAG
 */
#define VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG  VTSS_IOREG(0x1f, 1, 0x1e40)

/** 
 * \brief
 * Translate one priority value into another using map table
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . MAP_TBL
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_MAP_TBL(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_MAP_TBL     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_MAP_TBL(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

/** 
 * \brief
 * Default user priority
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . DEF_UP
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_DEF_UP(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_DEF_UP     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_DEF_UP(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/** 
 * \brief
 * STAG user priority enable
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . STAG_UP_EN
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_STAG_UP_EN  VTSS_BIT(27)

/** 
 * \brief
 * QTAG user priority map enable
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . QTAG_UP_EN
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_QTAG_UP_EN  VTSS_BIT(28)

/** 
 * \brief
 * Parse Q-in-Q enable
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . PARSE_QINQ
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_PARSE_QINQ  VTSS_BIT(29)

/** 
 * \brief
 * Parse STAG enable
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . PARSE_STAG
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_PARSE_STAG  VTSS_BIT(30)

/** 
 * \brief
 * Parse QTAG enable
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . PARSE_QTAG
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_PARSE_QTAG  VTSS_BIT(31)


/** 
 * \brief VLAN tag detection 
 *
 * \details
 * Register: \a MACSEC_INGR:FRAME_MATCHING_HANDLING_CTRL:SAM_PP_TAGS
 */
#define VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS  VTSS_IOREG(0x1f, 1, 0x1e41)

/** 
 * \brief
 * Ethertype value used for 802.1Q tag type comparison in the additional
 * fields parsing algorithm. As this is the VLAN tag, the default value is
 * 0x8100 (stored byte swapped as value 0x0081). 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS . QTAG_VALUE
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS_QTAG_VALUE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS_QTAG_VALUE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS_QTAG_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Ethertype value used for 802.1s tag type comparison in the additional
 * fields parsing algorithm. The default value is 0x88A8 (stored byte
 * swapped as value 0xA888) to allow stacked VLAN tags, but it can be
 * re-programmed to another value if user-specific VLAN tags are used.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS . STAG_VALUE
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS_STAG_VALUE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS_STAG_VALUE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS_STAG_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief VLAN tag detection 
 *
 * \details
 * Register: \a MACSEC_INGR:FRAME_MATCHING_HANDLING_CTRL:SAM_PP_TAGS2
 */
#define VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2  VTSS_IOREG(0x1f, 1, 0x1e42)

/** 
 * \brief
 * Secondary Ethertype value used for 802.1s-tag type comparison in the
 * additional fields parsing algorithm. The default value is 0x9100 (stored
 * byte swapped as value 0x0091). 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2 . STAG_VALUE2
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2_STAG_VALUE2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2_STAG_VALUE2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2_STAG_VALUE2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Tertiary Ethertype value used for 802.1s-tag type comparison in the
 * additional fields parsing algorithm. The default value is 0x9200 (stored
 * byte swapped as value 0x0092). 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2 . STAG_VALUE3
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2_STAG_VALUE3(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2_STAG_VALUE3     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2_STAG_VALUE3(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief VLAN tag detection
 *
 * \details
 * Register: \a MACSEC_INGR:FRAME_MATCHING_HANDLING_CTRL:SAM_CP_TAG2
 */
#define VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG2  VTSS_IOREG(0x1f, 1, 0x1e43)

/** 
 * \brief
 * Translate one priority value into another using the inner tag map table
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG2 . MAP_TBL2
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG2_MAP_TBL2(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG2_MAP_TBL2     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG2_MAP_TBL2(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief Secure Association non-match flow control 
 *
 * \details
 * Register: \a MACSEC_INGR:FRAME_MATCHING_HANDLING_CTRL:SAM_NM_PARAMS
 */
#define VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS  VTSS_IOREG(0x1f, 1, 0x1e50)

/** 
 * \details 
 * 1b: Compare Ethertype in packet against msec_tag_value value (default)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . COMP_ETYPE
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_COMP_ETYPE  VTSS_BIT(0)

/** 
 * \details 
 * 1b: Check version bit is 0b (default)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . CHECK_V
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_CHECK_V  VTSS_BIT(1)

/** 
 * \details 
 * 1b: Check if packet is meant to be handled by KaY (C & E bits) (default)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . CHECK_KAY
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_CHECK_KAY  VTSS_BIT(2)

/** 
 * \details 
 * 1b: Check illegal C == 1 & E == 0 flags combination (default)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . CHECK_C_E
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_CHECK_C_E  VTSS_BIT(3)

/** 
 * \details 
 * 1b: Check illegal SC/ES/SCB bit combinations (default)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . CHECK_SC
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_CHECK_SC  VTSS_BIT(4)

/** 
 * \details 
 * 1b: Check short length field contents out-of-range (default)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . CHECK_SL
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_CHECK_SL  VTSS_BIT(5)

/** 
 * \details 
 * 1b: Check PN (Packet Number) to be non-zero for all cipher suites and
 * regardless of SA hit. This value should be used if only cipher suites
 * with 32-bit packet numbering are used. Otherwise, this flag must be set
 * to 0b.
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . CHECK_PN
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_CHECK_PN  VTSS_BIT(6)

/** 
 * \brief
 * Ethertype value used for MACsec tag type comparison (stored byte
 * swapped) default value 0x88E5 (stored as 0xE588) is the standard MACsec
 * tag value.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . MACSEC_TAG_VALUE
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_MACSEC_TAG_VALUE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_MACSEC_TAG_VALUE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_MACSEC_TAG_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Secure Association non-match flow control 
 *
 * \details
 * Register: \a MACSEC_INGR:FRAME_MATCHING_HANDLING_CTRL:SAM_NM_FLOW_NCP
 */
#define VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP  VTSS_IOREG(0x1f, 1, 0x1e51)

/** 
 * \brief
 * Flow (action) type
 * Bits [7:0] control the handling of packets that were not classified as
 * control packets and that also do not contain a MACsec tag
 *
 * \details 
 * 0b: Bypass
 * 1b: Perform drop_action
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_UNTAGGED_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_FLOW_TYPE  VTSS_BIT(0)

/** 
 * \brief
 * Destination port
 *
 * \details 
 * 00b: Common port
 * 01b: Reserved port
 * 10b: Controlled port
 * 11b: Uncontrolled port
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_UNTAGGED_DEST_PORT
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DEST_PORT     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Perform drop_action if packet is not from the reserved port. This bit is
 * reserved in an egress-only (-e) core.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_UNTAGGED_DROP_NON_RESERVED
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DROP_NON_RESERVED  VTSS_BIT(4)

/** 
 * \brief
 * Defines how the drop operation is performed.
 * If drop_action 10b (internal drop) is selected in static_bypass mode,
 * the drop operation is forced to CRC corruption (mode 00b) the actual
 * field value is not influenced here.
 *
 * \details 
 * 00b: Bypass with CRC corruption signaling
 * 01b: Bypass with bad packet indicator
 * 10b: Internal drop by crypto-core (packet is not seen outside)
 * 11b: Do not drop (for debugging only)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_UNTAGGED_DROP_ACTION
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DROP_ACTION     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Flow (action) type 
 * Bits [15:8] control the handling of packets that were not classified as
 * control packets and	contain a valid MACsec tag
 *
 * \details 
 * 0b: Bypass
 * 1b: Perform drop_action
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_TAGGED_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_FLOW_TYPE  VTSS_BIT(8)

/** 
 * \brief
 * Destination port
 *
 * \details 
 * 00b: Common port
 * 01b: Reserved port
 * 10b: Controlled port
 * 11b: Uncontrolled port
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_TAGGED_DEST_PORT
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DEST_PORT     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Perform drop_action if packet is not from the reserved port. This bit is
 * reserved in an egress-only (-e) core.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_TAGGED_DROP_NON_RESERVED
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DROP_NON_RESERVED  VTSS_BIT(12)

/** 
 * \brief
 * Defines how the drop operation is performed.
 * If drop_action 10b (internal drop) is selected in static_bypass mode,
 * the drop operation is forced to CRC corruption (mode 00b) the actual
 * field value is not influenced here.
 *
 * \details 
 * 00b: Bypass with CRC corruption signaling
 * 01b: Bypass with bad packet indicator
 * 10b: Internal drop by crypto-core (packet is not seen outside)
 * 11b: Do not drop (for debugging only)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_TAGGED_DROP_ACTION
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DROP_ACTION     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Flow type
 * Bits [23:16] control the handling of packets that were not classified as
 * control packets and contain an invalid MACsec tag
 *
 * \details 
 * 0b: Bypass
 * 1b: Perform drop_action
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_BADTAG_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_FLOW_TYPE  VTSS_BIT(16)

/** 
 * \brief
 * Destination port
 *
 * \details 
 * 00b: Common port
 * 01b: Reserved port
 * 10b: Controlled port 
 * 11b: Uncontrolled port
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_BADTAG_DEST_PORT
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DEST_PORT     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * Perform drop_action if packet is not from the reserved port. This bit is
 * reserved in an egress-only (-e) core.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_BADTAG_DROP_NON_RESERVED
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DROP_NON_RESERVED  VTSS_BIT(20)

/** 
 * \brief
 * Defines how the drop operation is performed.
 * If drop_action 10b (internal drop) is selected in static_bypass mode,
 * the drop operation is forced to CRC corruption (mode 00b) the actual
 * field value is not influenced here.
 *
 * \details 
 * 00b: Bypass with CRC corruption signaling
 * 01b: Bypass with bad packet indicator
 * 10b: Internal drop by crypto-core (packet is not seen outside)
 * 11b: Do not drop (for debugging only)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_BADTAG_DROP_ACTION
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DROP_ACTION     VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,22,2)

/** 
 * \brief
 * Flow type
 * Bits [31:24] control the handling of packets that were not classified as
 * control packets, contain a valid MACsec tag, and must be handled by the
 * KaY.
 *
 * \details 
 * 0b: Bypass
 * 1b: Perform drop_action
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_KAY_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_FLOW_TYPE  VTSS_BIT(24)

/** 
 * \brief
 * Destination port
 *
 * \details 
 * 00b: Common port
 * 01b: Reserved port
 * 10b: Controlled port 
 * 11b: Uncontrolled port
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_KAY_DEST_PORT
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DEST_PORT     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * Perform drop_action if packet is not from the reserved port. This bit is
 * reserved in an egress-only (-e) core.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_KAY_DROP_NON_RESERVED
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DROP_NON_RESERVED  VTSS_BIT(28)

/** 
 * \brief
 * Defines how the drop operation is performed.
 * If drop_action 10b (internal drop) is selected in static_bypass mode,
 * the drop operation is forced to CRC corruption (mode 00b) the actual
 * field value is not influenced here.
 *
 * \details 
 * 00b: Bypass with CRC corruption signaling
 * 01b: Bypass with bad packet indicator
 * 10b: Internal drop by crypto-core (packet is not seen outside)
 * 11b: Do not drop (for debugging only)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_KAY_DROP_ACTION
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DROP_ACTION     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,30,2)


/** 
 * \brief Secure Association non-match flow control 
 *
 * \details
 * Register: \a MACSEC_INGR:FRAME_MATCHING_HANDLING_CTRL:SAM_NM_FLOW_CP
 */
#define VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP  VTSS_IOREG(0x1f, 1, 0x1e52)

/** 
 * \brief
 * Flow (action) type
 * Bits [7:0] control the handling of packets that were classified as
 * control packets and that also do not contain a MACsec tag
 *
 * \details 
 * 0b: Bypass
 * 1b: Perform drop_action
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_UNTAGGED_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_FLOW_TYPE  VTSS_BIT(0)

/** 
 * \brief
 * Destination port
 *
 * \details 
 * 00b: Common port
 * 01b: Reserved port
 * 10b: Controlled port
 * 11b: Uncontrolled port
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_UNTAGGED_DEST_PORT
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DEST_PORT     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Perform drop_action if packet is not from the reserved port. This bit is
 * reserved in an egress-only (-e) core.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_UNTAGGED_DROP_NON_RESERVED
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DROP_NON_RESERVED  VTSS_BIT(4)

/** 
 * \brief
 * Defines how the drop operation is performed.
 * If drop_action 10b (internal drop) is selected in static_bypass mode,
 * the drop operation is forced to CRC corruption (mode 00b) the actual
 * field value is not influenced here.
 *
 * \details 
 * 00b: Bypass with CRC corruption signaling
 * 01b: Bypass with bad packet indicator
 * 10b: Internal drop by crypto-core (packet is not seen outside)
 * 11b: Do not drop (for debugging only)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_UNTAGGED_DROP_ACTION
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DROP_ACTION     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Flow (action) type 
 * Bits [15:8] control the handling of packets that were not classified as
 * control packets and	contain a valid MACsec tag
 *
 * \details 
 * 0b: Bypass
 * 1b: Perform drop_action
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_TAGGED_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_FLOW_TYPE  VTSS_BIT(8)

/** 
 * \brief
 * Destination port
 *
 * \details 
 * 00b: Common port
 * 01b: Reserved port
 * 10b: Controlled port
 * 11b: Uncontrolled port
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_TAGGED_DEST_PORT
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DEST_PORT     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Perform drop_action if packet is not from the reserved port. This bit is
 * reserved in an egress-only (-e) core.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_TAGGED_DROP_NON_RESERVED
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DROP_NON_RESERVED  VTSS_BIT(12)

/** 
 * \brief
 * Defines how the drop operation is performed.
 * If drop_action 10b (internal drop) is selected in static_bypass mode,
 * the drop operation is forced to CRC corruption (mode 00b) the actual
 * field value is not influenced here.
 *
 * \details 
 * 00b: Bypass with CRC corruption signaling
 * 01b: Bypass with bad packet indicator
 * 10b: Internal drop by crypto-core (packet is not seen outside)
 * 11b: Do not drop (for debugging only)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_TAGGED_DROP_ACTION
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DROP_ACTION     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Flow (action) type
 * Bits [23:16] control the handling of packets that were classified as
 * control packets and contain an invalid MACsec tag
 *
 * \details 
 * 0b: Bypass
 * 1b: Perform drop_action
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_BADTAG_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_FLOW_TYPE  VTSS_BIT(16)

/** 
 * \brief
 * Destination port
 *
 * \details 
 * 00b: Common port
 * 01b: Reserved port
 * 10b: Controlled port
 * 11b: Uncontrolled port
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_BADTAG_DEST_PORT
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DEST_PORT     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * Perform drop_action if packet is not from the reserved port. This bit is
 * reserved in an egress-only (-e) core.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_BADTAG_DROP_NON_RESERVED
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DROP_NON_RESERVED  VTSS_BIT(20)

/** 
 * \brief
 * Defines how the drop operation is performed.
 * If drop_action 10b (internal drop) is selected in static_bypass mode,
 * the drop operation is forced to CRC corruption (mode 00b) the actual
 * field value is not influenced here.
 *
 * \details 
 * 00b: Bypass with CRC corruption signaling
 * 01b: Bypass with bad packet indicator
 * 10b: Internal drop by crypto-core (packet is not seen outside)
 * 11b: Do not drop (for debugging only)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_BADTAG_DROP_ACTION
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DROP_ACTION     VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,22,2)

/** 
 * \brief
 * Flow (action) type
 * Bits [31:24] control the handling of packets that were classified as
 * control packets, contain a valid MACsec tag and must be handled by the
 * KaY
 *
 * \details 
 * 0b: Bypass
 * 1b: Perform drop_action
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_KAY_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_FLOW_TYPE  VTSS_BIT(24)

/** 
 * \brief
 * Destination port
 *
 * \details 
 * 00b: Common port
 * 01b: Reserved port
 * 10b: Controlled port
 * 11b: Uncontrolled port
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_KAY_DEST_PORT
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DEST_PORT     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * Perform drop_action if packet is not from the reserved port. This bit is
 * reserved in an egress-only (-e) core.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_KAY_DROP_NON_RESERVED
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DROP_NON_RESERVED  VTSS_BIT(28)

/** 
 * \brief
 * Defines how the drop operation is performed.
 * If drop_action 10b (internal drop) is selected in static_bypass mode,
 * the drop operation is forced to CRC corruption (mode 00b) the actual
 * field value is not influenced here.
 *
 * \details 
 * 00b: Bypass with CRC corruption signaling
 * 01b: Bypass with bad packet indicator
 * 10b: Internal drop by crypto-core (packet is not seen outside)
 * 11b: Do not drop (for debugging only)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_KAY_DROP_ACTION
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DROP_ACTION     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,30,2)


/** 
 * \brief Misc control register
 *
 * \details
 * Register: \a MACSEC_INGR:FRAME_MATCHING_HANDLING_CTRL:MISC_CONTROL
 */
#define VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL  VTSS_IOREG(0x1f, 1, 0x1e5f)

/** 
 * \brief
 * Streaming out of a packet is blocked for this number of clock cycles
 * after it started streaming into the MACsec core. An out-of-range value
 * or backpressure from the MAC side (temporarily) disables latency fixing.
 * Normally, this value will be set to just above the maximum latency of
 * the operations to be performed.
 * 
 * For non-static bypass the range is 0, 1, to 95, which corresponds to 0,
 * 38, to 127 module clock cycles mode. 
 * Setting to values from 96 will 127 corresponds to 127 module clock
 * cycles.
 * 
 * For static bypass mode the range is 0, 5, to 127 module clock cycles.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL . MC_LATENCY_FIX
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_MC_LATENCY_FIX(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_MC_LATENCY_FIX     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_MC_LATENCY_FIX(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Static bypass
 * Packet dropping within the MACsec core is not possible if the MACsec
 * core is diabled. When this drop_action is selected (with field value
 * 10b) for a packet, the CRC corruption drop mode (00b) is used instead.
 * Other modes of dropping a packet remain functional. 
 *
 * \details 
 * 1b: Disable the MACsec crypto-core, feeding packet data around it to
 * minimize latency while leaving classification functionality (including
 * consistency checking and MACsec post-processing) intact. 
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL . STATIC_BYPASS
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_STATIC_BYPASS  VTSS_BIT(8)

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
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL . NM_MACSEC_EN
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_NM_MACSEC_EN  VTSS_BIT(9)

/** 
 * \brief
 * Global frame validation level
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
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL . VALIDATE_FRAMES
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_VALIDATE_FRAMES(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_VALIDATE_FRAMES     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_VALIDATE_FRAMES(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Transform record size to match the record size programmed in the MACsec
 * crypto engine's CONTEXT_CTRL register.
 *
 * \details 
 * 00b: 64 Bytes (4 words of 128 bits)
 * 01b: 80 Bytes (5 words of 128 bits)
 * 10b: 96  bytes (6 words of 128 bits)
 * 11b: 48 Bytes (3 words of 128 bits)
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL . XFORM_REC_SIZE
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_XFORM_REC_SIZE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_XFORM_REC_SIZE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_XFORM_REC_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)


/** 
 * \brief Header bypass configuration
 *
 * \details
 * Register: \a MACSEC_INGR:FRAME_MATCHING_HANDLING_CTRL:HDR_EXT_CTRL
 */
#define VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL  VTSS_IOREG(0x1f, 1, 0x1e60)

/** 
 * \brief
 * Compare value for Etype2 field in header bypass mode (for the Ethertype
 * field directly following the MAC_SA). 
 * If header bypass is enabled, the inner ETYPE value is used in control
 * packet detector algorithm. 
 * If header bypass is not enabled, this field is ignored. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL . HB_ETYPE_MATCH
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HB_ETYPE_MATCH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HB_ETYPE_MATCH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HB_ETYPE_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Size of the bypassed header in header bypass mode in 2-byte units
 *
 * \details 
 * The allowed values are 0 (no header bypass), 8, 9, 10, 11 to 15. 
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL . HDR_BYPASS_LEN
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HDR_BYPASS_LEN(x)  VTSS_ENCODE_BITFIELD(x,17,4)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HDR_BYPASS_LEN     VTSS_ENCODE_BITMASK(17,4)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HDR_BYPASS_LEN(x)  VTSS_EXTRACT_BITFIELD(x,17,4)

/** 
 * \brief
 * Enables detecting the MACsec SecTAG after VLAN tags. 
 * When set to 1b, MACsec SecTAG that resides after one or two VLAN tags is
 * detected and this information is used to determine how many VLAN tags
 * need to bypass the MACsec ingress processing.
 * When set to 0b, MACsec SecTAG is only detected when residing immediately
 * after MAC SA/DA.
 * Note: This flag must be 0b if hdr_bypass_len is non-zero.
 * Note: For the egress-only configuration, setting this flag to 1b is not
 * needed if no MACsec tagged packets with VLAN tags before SecTAG are
 * expected. The number of VLAN tags to bypass the MACsec egress processing
 * is determined by the flow control register (SA_FLOW_CTRL_EGR). If MACsec
 * tagged packets with VLAN tags before SecTAG are expected (e.g. KaY
 * packets) this flag needs to be set to 1b.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL . SECTAG_AFTER_VLAN
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_SECTAG_AFTER_VLAN  VTSS_BIT(21)

/** 
 * \brief
 * Enables matching the Etype2 field with the hb_e_type_match value in
 * header bypass mode.
 * If header bypass is enabled, the value must be set to 1b.
 *
 * \details 
 * 0b: For debug only
 *
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL . HB_E_TYPE_MATCH_EN
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HB_E_TYPE_MATCH_EN  VTSS_BIT(22)


/** 
 * \brief Crypt Authentication control register
 *
 * \details
 * Register: \a MACSEC_INGR:FRAME_MATCHING_HANDLING_CTRL:CRYPT_AUTH_CTRL
 */
#define VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_CRYPT_AUTH_CTRL  VTSS_IOREG(0x1f, 1, 0x1e61)

/** 
 * \brief
 * Specifies length (in bytes) of the bypass data during crypt-authenticate
 * operation. The bypass data should contain MAC header to be able to
 * classify the packet into the corresponding crypto-authenticate flow
 * control register and additionally it might include the IV used in the
 * transformation.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_CRYPT_AUTH_CTRL . CRYPT_AUTH_BYPASS_LEN
 */
#define  VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_CRYPT_AUTH_CTRL_CRYPT_AUTH_BYPASS_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_CRYPT_AUTH_CTRL_CRYPT_AUTH_BYPASS_LEN     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_CRYPT_AUTH_CTRL_CRYPT_AUTH_BYPASS_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a MACSEC_INGR:SA_STATS_IGR
 *
 * Secure Association ingress statistics registers
 */


/** 
 * \brief sa.InOctetsDecrypted/InOctetsValidated (chained, 1st counter) - lower 32 bits
 *
 * \details
 * InOctetsValidated: The number of octets of plaintext recovered from
 * received packets that were integrity protected but not encrypted.
 * InOctetsDecrypted: The number of octets of plaintext recovered from
 * received packets that were integrity protected and encrypted.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_OCTETS_DECRYPTED_FIRST_CNTR_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_FIRST_CNTR_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x2000 | (ri * 32))


/** 
 * \brief sa.InOctetsDecrypted/InOctetsValidated (chained, 1st counter) - upper 8 bits
 *
 * \details
 * InOctetsValidated: The number of octets of plaintext recovered from
 * received packets that were integrity protected but not encrypted.
 * InOctetsDecrypted: The number of octets of plaintext recovered from
 * received packets that were integrity protected and encrypted.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_OCTETS_DECRYPTED_FIRST_CNTR_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_FIRST_CNTR_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x2001 | (ri * 32))

/** 
 * \brief
 * sa.InOctetsDecrypted/sa.InOctetsValidated - upper 8 bits of the chained,
 * first 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_FIRST_CNTR_UPPER . IN_OCTETS_DECRYPTED_FIRST_CNTR_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_FIRST_CNTR_UPPER_IN_OCTETS_DECRYPTED_FIRST_CNTR_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_FIRST_CNTR_UPPER_IN_OCTETS_DECRYPTED_FIRST_CNTR_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_FIRST_CNTR_UPPER_IN_OCTETS_DECRYPTED_FIRST_CNTR_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.InOctetsDecrypted/InOctetsValidated (chained, 2nd counter) - lower 32 bits
 *
 * \details
 * InOctetsValidated: The number of octets of plaintext recovered from
 * received packets that were integrity protected but not encrypted.
 * InOctetsDecrypted: The number of octets of plaintext recovered from
 * received packets that were integrity protected and encrypted.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_OCTETS_DECRYPTED_SECOND_CNTR_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_SECOND_CNTR_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x2002 | (ri * 32))


/** 
 * \brief sa.InOctetsDecrypted/InOctetsValidated (chained, 2nd counter) - upper 8 bits
 *
 * \details
 * InOctetsValidated: The number of octets of plaintext recovered from
 * received packets that were integrity protected but not encrypted.
 * InOctetsDecrypted: The number of octets of plaintext recovered from
 * received packets that were integrity protected and encrypted.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_OCTETS_DECRYPTED_SECOND_CNTR_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_SECOND_CNTR_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x2003 | (ri * 32))

/** 
 * \brief
 * sa.InOctetsDecrypted/sa.InOctetsValidated - upper 8 bits of the chained,
 * second 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_SECOND_CNTR_UPPER . IN_OCTETS_DECRYPTED_SECOND_CNTR_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_SECOND_CNTR_UPPER_IN_OCTETS_DECRYPTED_SECOND_CNTR_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_SECOND_CNTR_UPPER_IN_OCTETS_DECRYPTED_SECOND_CNTR_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_SECOND_CNTR_UPPER_IN_OCTETS_DECRYPTED_SECOND_CNTR_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.InPktsUnchecked/InPktsHitDropReserved - lower 32 bits
 *
 * \details
 * InPktsUnchecked: For this SA, the number of packets with the following
 * condition:
 * ValidateFrames is disabled or
 * ValidateFrames is not disabled and the packet is not encrypted and the
 * integrity check has failed or
 * ValidateFrames is not disable and the packet is encrypted and integrity
 * check has failed.
 * InPktsHitDropReserved: Bypass/drop flow was found in SA table.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_UNCHECKED_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNCHECKED_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x2004 | (ri * 32))


/** 
 * \brief sa.InPktsUnchecked/InPktsHitDropReserved - upper 8 bits
 *
 * \details
 * InPktsUnchecked: For this SA, the number of packets with the following
 * condition:
 * ValidateFrames is disabled or
 * ValidateFrames is not disabled and the packet is not encrypted and the
 * integrity check has failed or
 * ValidateFrames is not disable and the packet is encrypted and integrity
 * check has failed.
 * InPktsHitDropReserved: Bypass/drop flow was found in SA table.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_UNCHECKED_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNCHECKED_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x2005 | (ri * 32))

/** 
 * \brief
 * sa.InPktsUnchecked/InPktsHitDropReserved - upper 8 bits of the 40-bit
 * counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNCHECKED_UPPER . IN_PKTS_UNCHECKED_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNCHECKED_UPPER_IN_PKTS_UNCHECKED_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNCHECKED_UPPER_IN_PKTS_UNCHECKED_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNCHECKED_UPPER_IN_PKTS_UNCHECKED_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.InPktsDelayed - lower 32 bits
 *
 * \details
 * InPktsDelayed: For this SA, the number of packets with the condition
 * that the PN of the packets is lower than the lower bound replay
 * protection PN.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_DELAYED_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_DELAYED_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x2006 | (ri * 32))


/** 
 * \brief sa.InPktsDelayed - upper 8 bits
 *
 * \details
 * InPktsDelayed: For this SA, the number of packets with the condition
 * that the PN of the packets is lower than the lower bound replay
 * protection PN.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_DELAYED_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_DELAYED_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x2007 | (ri * 32))

/** 
 * \brief
 * sa.InPktsDelayed - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_DELAYED_UPPER . IN_PKTS_DELAYED_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_DELAYED_UPPER_IN_PKTS_DELAYED_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_DELAYED_UPPER_IN_PKTS_DELAYED_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_DELAYED_UPPER_IN_PKTS_DELAYED_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.InPktsLate - lower 32 bits
 *
 * \details
 * InPktsLate: For this SA, the number of received packets that have been
 * discarded with the condition that ReplayProtect is equal to true and the
 * PN of the packet is lower than the lower bound replay check PN.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_LATE_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_LATE_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x2008 | (ri * 32))


/** 
 * \brief sa.InPktsLate - upper 8 bits
 *
 * \details
 * InPktsLate: For this SA, the number of received packets that have been
 * discarded with the condition that ReplayProtect is equal to true and the
 * PN of the packet is lower than the lower bound replay check PN.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_LATE_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_LATE_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x2009 | (ri * 32))

/** 
 * \brief
 * sa.InPktsLate - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_LATE_UPPER . IN_PKTS_LATE_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_LATE_UPPER_IN_PKTS_LATE_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_LATE_UPPER_IN_PKTS_LATE_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_LATE_UPPER_IN_PKTS_LATE_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.InPktsOk - lower 32 bits.
 *
 * \details
 * InPktsOK: For this SA, the number of validated packets.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_OK_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_OK_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x200a | (ri * 32))


/** 
 * \brief sa.InPktsOk - upper 8 bits
 *
 * \details
 * InPktsOK: For this SA, the number of validated packets.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_OK_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_OK_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x200b | (ri * 32))

/** 
 * \brief
 * sa.InPktsOK - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_OK_UPPER . IN_PKTS_OK_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_OK_UPPER_IN_PKTS_OK_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_OK_UPPER_IN_PKTS_OK_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_OK_UPPER_IN_PKTS_OK_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.InPktsInvalid - lower 32 bits
 *
 * \details
 * InPktsInvalid: For this SA, the number of packets with the condition
 * that the packets are not valid and ValidateFrames is in check mode.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_INVALID_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_INVALID_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x200c | (ri * 32))


/** 
 * \brief sa.InPktsInvalid - upper 8 bits
 *
 * \details
 * InPktsInvalid: For this SA, the number of packets with the condition
 * that the packets are not valid and ValidateFrames is in check mode.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_INVALID_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_INVALID_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x200d | (ri * 32))

/** 
 * \brief
 * sa.InPktsInvalid - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_INVALID_UPPER . IN_PKTS_INVALID_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_INVALID_UPPER_IN_PKTS_INVALID_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_INVALID_UPPER_IN_PKTS_INVALID_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_INVALID_UPPER_IN_PKTS_INVALID_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.InPktsNotValid - lower 32 bits
 *
 * \details
 * InPktsNotInvalid: For this SA, the number discarded packets with the
 * condition that the packets are not valid and one of the following
 * conditions are true: either ValidateFrames in strict mode or the packets
 * encrypted.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_NOT_VALID_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_VALID_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x200e | (ri * 32))


/** 
 * \brief sa.InPktsNotValid - upper 8 bits
 *
 * \details
 * InPktsNotInvalid: For this SA, the number discarded packets with the
 * condition that the packets are not valid and one of the following
 * conditions are true: either ValidateFrames in strict mode or the packets
 * encrypted.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_NOT_VALID_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_VALID_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x200f | (ri * 32))

/** 
 * \brief
 * sa.InPktsNotInvalid - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_VALID_UPPER . IN_PKTS_NOT_VALID_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_VALID_UPPER_IN_PKTS_NOT_VALID_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_VALID_UPPER_IN_PKTS_NOT_VALID_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_VALID_UPPER_IN_PKTS_NOT_VALID_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.InPktsNotUsingSA - lower 32 bits
 *
 * \details
 * InPktsNotUsingSA: For this SA which is not currently in use, the number
 * of received packets that have been discarded, and have either the
 * packets encrypted or the ValidateFrames set to strict mode.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_NOT_USING_SA_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_USING_SA_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x2010 | (ri * 32))


/** 
 * \brief sa.InPktsNotUsingSA - upper 8 bits
 *
 * \details
 * InPktsNotUsingSA: For this SA which is not currently in use, the number
 * of received packets that have been discarded, and have either the
 * packets encrypted or the ValidateFrames set to strict mode.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_NOT_USING_SA_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_USING_SA_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x2011 | (ri * 32))

/** 
 * \brief
 * sa.InPktsNotUsingSA - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_USING_SA_UPPER . IN_PKTS_NOT_USING_SA_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_USING_SA_UPPER_IN_PKTS_NOT_USING_SA_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_USING_SA_UPPER_IN_PKTS_NOT_USING_SA_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_USING_SA_UPPER_IN_PKTS_NOT_USING_SA_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.InPktsUnusedSA - lower 32 bits
 *
 * \details
 * InPktsUnusedSA: For this SA which is not currently in use, the number of
 * received, unencrypted, packets with ValidateFrames not in the strict
 * mode.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_UNUSED_SA_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNUSED_SA_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x2012 | (ri * 32))


/** 
 * \brief sa.InPktsUnusedSA - upper 8 bits
 *
 * \details
 * InPktsUnusedSA: For this SA which is not currently in use, the number of
 * received, unencrypted, packets with ValidateFrames not in the strict
 * mode.
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_UNUSED_SA_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNUSED_SA_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x2013 | (ri * 32))

/** 
 * \brief
 * sa.InPktsUnusedSA - upper 8 bits of 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNUSED_SA_UPPER . IN_PKTS_UNUSED_SA_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNUSED_SA_UPPER_IN_PKTS_UNUSED_SA_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNUSED_SA_UPPER_IN_PKTS_UNUSED_SA_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNUSED_SA_UPPER_IN_PKTS_UNUSED_SA_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.InPktsUntaggedHit - lower 32 bits
 *
 * \details
 * sa.InPktsUntaggedHit: For this SA, the number of received packets
 * without the MAC security tag (SecTAG).
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_UNTAGGED_HIT_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNTAGGED_HIT_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x2014 | (ri * 32))


/** 
 * \brief sa.InPktsUntaggedHit - upper 8 bits
 *
 * \details
 * sa.InPktsUntaggedHit: For this SA, the number of received packets
 * without the MAC security tag (SecTAG).
 *
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_PKTS_UNTAGGED_HIT_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNTAGGED_HIT_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x2015 | (ri * 32))

/** 
 * \brief
 * sa.InPktsUntaggedHit - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNTAGGED_HIT_UPPER . IN_PKTS_UNTAGGED_HIT_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNTAGGED_HIT_UPPER_IN_PKTS_UNTAGGED_HIT_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNTAGGED_HIT_UPPER_IN_PKTS_UNTAGGED_HIT_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNTAGGED_HIT_UPPER_IN_PKTS_UNTAGGED_HIT_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.ifInUcastPkts - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_UNICAST_PKTS_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_UNICAST_PKTS_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x2016 | (ri * 32))


/** 
 * \brief sa.ifInUcastPkts - upper 8 bits
 *
 * \details
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_UNICAST_PKTS_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_UNICAST_PKTS_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x2017 | (ri * 32))

/** 
 * \brief
 * sa.ifInUcastPkts - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_UNICAST_PKTS_UPPER . IN_UNICAST_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_UNICAST_PKTS_UPPER_IN_UNICAST_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_UNICAST_PKTS_UPPER_IN_UNICAST_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_UNICAST_PKTS_UPPER_IN_UNICAST_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.ifInMulticastPkts - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_MULTICAST_PKTS_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_MULTICAST_PKTS_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x2018 | (ri * 32))


/** 
 * \brief sa.ifInMulticastPkts - upper 8 bits
 *
 * \details
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_MULTICAST_PKTS_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_MULTICAST_PKTS_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x2019 | (ri * 32))

/** 
 * \brief
 * sa.ifInMulticastPkts - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_MULTICAST_PKTS_UPPER . IN_MULTICAST_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_MULTICAST_PKTS_UPPER_IN_MULTICAST_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_MULTICAST_PKTS_UPPER_IN_MULTICAST_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_MULTICAST_PKTS_UPPER_IN_MULTICAST_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.ifInBroadcastPkts - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_BROADCAST_PKTS_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_BROADCAST_PKTS_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x201a | (ri * 32))


/** 
 * \brief sa.ifInBroadcastPkts - upper 8 bits
 *
 * \details
 * Register: \a MACSEC_INGR:SA_STATS_IGR:IN_BROADCAST_PKTS_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_SA_STATS_IGR_IN_BROADCAST_PKTS_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x201b | (ri * 32))

/** 
 * \brief
 * sa.ifInBroadcastPkts - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_SA_STATS_IGR_IN_BROADCAST_PKTS_UPPER . IN_BROADCAST_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_INGR_SA_STATS_IGR_IN_BROADCAST_PKTS_UPPER_IN_BROADCAST_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_SA_STATS_IGR_IN_BROADCAST_PKTS_UPPER_IN_BROADCAST_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_SA_STATS_IGR_IN_BROADCAST_PKTS_UPPER_IN_BROADCAST_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a MACSEC_INGR:VLAN_STATS_IGR
 *
 * VLAN ingress statistics registers
 */


/** 
 * \brief vlan.InOctetsVL (chained, 1st counter)  - lower 32 bits
 *
 * \details
 * InOctetsVL: Number of Incoming Octets processed for VLAN_VALID frames
 * per User Priority. Total 8 sets of these counters are available for each
 * of the User priority.
 *
 * Register: \a MACSEC_INGR:VLAN_STATS_IGR:IN_OCTETS_VL_FIRST_CNTR_LOWER
 *
 * @param ri Register: IN_OCTETS_VL_FIRST_CNTR_LOWER, 0-7
 */
#define VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_OCTETS_VL_FIRST_CNTR_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x3000 | (ri * 32))


/** 
 * \brief vlan.InOctetsVL (chained, 1st counter)  - upper 8 bits
 *
 * \details
 * InOctetsVL: Number of Incoming Octets processed for VLAN_VALID frames
 * per User Priority. Total 8 sets of these counters are available for each
 * of the User priority.
 *
 * Register: \a MACSEC_INGR:VLAN_STATS_IGR:IN_OCTETS_VL_FIRST_CNTR_UPPER
 *
 * @param ri Register: IN_OCTETS_VL_FIRST_CNTR_UPPER, 0-7
 */
#define VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_OCTETS_VL_FIRST_CNTR_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x3001 | (ri * 32))

/** 
 * \brief
 * vlan.InOctetsVL (chained, 1st counter) - upper 8 bits of the chained,
 * first 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_OCTETS_VL_FIRST_CNTR_UPPER . IN_OCTETS_VL_FIRST_CNTR_UPPER
 */
#define  VTSS_F_MACSEC_INGR_VLAN_STATS_IGR_IN_OCTETS_VL_FIRST_CNTR_UPPER_IN_OCTETS_VL_FIRST_CNTR_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_VLAN_STATS_IGR_IN_OCTETS_VL_FIRST_CNTR_UPPER_IN_OCTETS_VL_FIRST_CNTR_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_VLAN_STATS_IGR_IN_OCTETS_VL_FIRST_CNTR_UPPER_IN_OCTETS_VL_FIRST_CNTR_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief vlan.InOctetsVL (chained, 2nd counter) - lower 32 bits
 *
 * \details
 * InOctetsVL: Number of Incoming Octets processed for VLAN_VALID frames
 * per User Priority. Total 8 sets of these counters are available for each
 * of the User priority.
 *
 * Register: \a MACSEC_INGR:VLAN_STATS_IGR:IN_OCTETS_VL_SECOND_CNTR_LOWER
 *
 * @param ri Register: IN_OCTETS_VL_SECOND_CNTR_LOWER, 0-7
 */
#define VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_OCTETS_VL_SECOND_CNTR_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x3002 | (ri * 32))


/** 
 * \brief vlan.InOctetsVL (chained, 2nd counter) - upper 8 bits
 *
 * \details
 * InOctetsVL: Number of Incoming Octets processed for VLAN_VALID frames
 * per User Priority. Total 8 sets of these counters are available for each
 * of the User priority.
 *
 * Register: \a MACSEC_INGR:VLAN_STATS_IGR:IN_OCTETS_VL_SECOND_CNTR_UPPER
 *
 * @param ri Register: IN_OCTETS_VL_SECOND_CNTR_UPPER, 0-7
 */
#define VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_OCTETS_VL_SECOND_CNTR_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x3003 | (ri * 32))

/** 
 * \brief
 * vlan.InOctetsVL (chained, 2nd counter) - upper 8 bits of the chained,
 * second 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_OCTETS_VL_SECOND_CNTR_UPPER . IN_OCTETS_VL_SECOND_CNTR_UPPER
 */
#define  VTSS_F_MACSEC_INGR_VLAN_STATS_IGR_IN_OCTETS_VL_SECOND_CNTR_UPPER_IN_OCTETS_VL_SECOND_CNTR_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_VLAN_STATS_IGR_IN_OCTETS_VL_SECOND_CNTR_UPPER_IN_OCTETS_VL_SECOND_CNTR_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_VLAN_STATS_IGR_IN_OCTETS_VL_SECOND_CNTR_UPPER_IN_OCTETS_VL_SECOND_CNTR_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief vlan.InPktsVL - lower 32 bits
 *
 * \details
 * InPktsVL: Number of Incoming frame received with VLAN_VALID per User
 * Priority.
 *
 * Register: \a MACSEC_INGR:VLAN_STATS_IGR:IN_PKTS_VL_LOWER
 *
 * @param ri Register: IN_PKTS_VL_LOWER, 0-7
 */
#define VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_PKTS_VL_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x3004 | (ri * 32))


/** 
 * \brief vlan.InPktsVL - upper 8 bits
 *
 * \details
 * InPktsVL: Number of Incoming frame received with VLAN_VALID per User
 * Priority.
 *
 * Register: \a MACSEC_INGR:VLAN_STATS_IGR:IN_PKTS_VL_UPPER
 *
 * @param ri Register: IN_PKTS_VL_UPPER, 0-7
 */
#define VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_PKTS_VL_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x3005 | (ri * 32))

/** 
 * \brief
 * vlan.InPktsVL - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_PKTS_VL_UPPER . IN_PKTS_VL_UPPER
 */
#define  VTSS_F_MACSEC_INGR_VLAN_STATS_IGR_IN_PKTS_VL_UPPER_IN_PKTS_VL_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_VLAN_STATS_IGR_IN_PKTS_VL_UPPER_IN_PKTS_VL_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_VLAN_STATS_IGR_IN_PKTS_VL_UPPER_IN_PKTS_VL_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief vlan.InDroppedPktsVL - lower 32 bits
 *
 * \details
 * InDroppedPktsVL: Number of Incoming frames with VLAN_VALID dropped per
 * User Priority.
 *
 * Register: \a MACSEC_INGR:VLAN_STATS_IGR:IN_DROPPED_PKTS_VL_LOWER
 *
 * @param ri Register: IN_DROPPED_PKTS_VL_LOWER, 0-7
 */
#define VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_DROPPED_PKTS_VL_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x3006 | (ri * 32))


/** 
 * \brief vlan.InDroppedPktsVL - upper 8 bits
 *
 * \details
 * InDroppedPktsVL: Number of Incoming frames with VLAN_VALID dropped per
 * User Priority.
 *
 * Register: \a MACSEC_INGR:VLAN_STATS_IGR:IN_DROPPED_PKTS_VL_UPPER
 *
 * @param ri Register: IN_DROPPED_PKTS_VL_UPPER, 0-7
 */
#define VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_DROPPED_PKTS_VL_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x3007 | (ri * 32))

/** 
 * \brief
 * vlan.InDroppedPktsVL - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_DROPPED_PKTS_VL_UPPER . IN_DROPPED_PKTS_VL_UPPER
 */
#define  VTSS_F_MACSEC_INGR_VLAN_STATS_IGR_IN_DROPPED_PKTS_VL_UPPER_IN_DROPPED_PKTS_VL_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_VLAN_STATS_IGR_IN_DROPPED_PKTS_VL_UPPER_IN_DROPPED_PKTS_VL_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_VLAN_STATS_IGR_IN_DROPPED_PKTS_VL_UPPER_IN_DROPPED_PKTS_VL_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief vlan.InOverSizePktsVL (MTU check) - lower 32 bits
 *
 * \details
 * InOverSizePktsVL: Number of Incoming frames with VLAN_VALID which are
 * detected OverSize due to VLAN MTU check per User Priority.
 *
 * Register: \a MACSEC_INGR:VLAN_STATS_IGR:IN_OVERSIZE_PKTS_VL_LOWER
 *
 * @param ri Register: IN_OVERSIZE_PKTS_VL_LOWER, 0-7
 */
#define VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_OVERSIZE_PKTS_VL_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0x3008 | (ri * 32))


/** 
 * \brief vlan.InOverSizePktsVL (MTU check) - upper 8 bits
 *
 * \details
 * InOverSizePktsVL: Number of Incoming frames with VLAN_VALID which are
 * detected OverSize due to VLAN MTU check per User Priority.
 *
 * Register: \a MACSEC_INGR:VLAN_STATS_IGR:IN_OVERSIZE_PKTS_VL_UPPER
 *
 * @param ri Register: IN_OVERSIZE_PKTS_VL_UPPER, 0-7
 */
#define VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_OVERSIZE_PKTS_VL_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0x3009 | (ri * 32))

/** 
 * \brief
 * vlan.InOverSizePktsVL (MTU check) - upper bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_VLAN_STATS_IGR_IN_OVERSIZE_PKTS_VL_UPPER . IN_OVERSIZE_PKTS_VL_UPPER
 */
#define  VTSS_F_MACSEC_INGR_VLAN_STATS_IGR_IN_OVERSIZE_PKTS_VL_UPPER_IN_OVERSIZE_PKTS_VL_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_VLAN_STATS_IGR_IN_OVERSIZE_PKTS_VL_UPPER_IN_OVERSIZE_PKTS_VL_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_VLAN_STATS_IGR_IN_OVERSIZE_PKTS_VL_UPPER_IN_OVERSIZE_PKTS_VL_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a MACSEC_INGR:GLOBAL_STATS_IGR
 *
 * Global ingress statistics registers
 */


/** 
 * \brief global.TransformErrorPkts - lower 32 bits
 *
 * \details
 * TransformErrorPkts: Drop due to internal errors in MACsec core.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:TRANSFORM_ERROR_PKTS_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_TRANSFORM_ERROR_PKTS_LOWER  VTSS_IOREG(0x1f, 1, 0x3100)


/** 
 * \brief global.TransformErrorPkts - upper 8 bits
 *
 * \details
 * TransformErrorPkts: Drop due to internal errors in MACsec core.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:TRANSFORM_ERROR_PKTS_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_TRANSFORM_ERROR_PKTS_UPPER  VTSS_IOREG(0x1f, 1, 0x3101)

/** 
 * \brief
 * global.TransformErrorPkts - upper 8 bits of 40-bit counter
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_TRANSFORM_ERROR_PKTS_UPPER . TRANSFORM_ERROR_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_TRANSFORM_ERROR_PKTS_UPPER_TRANSFORM_ERROR_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_TRANSFORM_ERROR_PKTS_UPPER_TRANSFORM_ERROR_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_TRANSFORM_ERROR_PKTS_UPPER_TRANSFORM_ERROR_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.InPktsCtrl - lower 32 bits
 *
 * \details
 * InPktsCtrl: Ingress packet was also classified as a control packet.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_CTRL_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_CTRL_LOWER  VTSS_IOREG(0x1f, 1, 0x3102)


/** 
 * \brief global.InPktsCtrl - upper 8 bits
 *
 * \details
 * InPktsCtrl: Ingress packet was also classified as a control packet.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_CTRL_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_CTRL_UPPER  VTSS_IOREG(0x1f, 1, 0x3103)

/** 
 * \brief
 * global.InPktsCtrl - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_CTRL_UPPER . IN_PKTS_CTRL_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_CTRL_UPPER_IN_PKTS_CTRL_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_CTRL_UPPER_IN_PKTS_CTRL_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_CTRL_UPPER_IN_PKTS_CTRL_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.InPktsNoTag - lower 32 bits
 *
 * \details
 * InPktsNoTag: The number of received packets discarded without the MAC
 * security tag (SecTAG) with ValidateFrames which is in the strict mode.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_NO_TAG_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_TAG_LOWER  VTSS_IOREG(0x1f, 1, 0x3104)


/** 
 * \brief global.InPktsNoTag - upper 8 bits
 *
 * \details
 * InPktsNoTag: The number of received packets discarded without the MAC
 * security tag (SecTAG) with ValidateFrames which is in the strict mode.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_NO_TAG_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_TAG_UPPER  VTSS_IOREG(0x1f, 1, 0x3105)

/** 
 * \brief
 * global.InPktsNoTag - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_TAG_UPPER . IN_PKTS_NO_TAG_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_TAG_UPPER_IN_PKTS_NO_TAG_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_TAG_UPPER_IN_PKTS_NO_TAG_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_TAG_UPPER_IN_PKTS_NO_TAG_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.InPktsUntagged - lower 32 bits
 *
 * \details
 * InPktsUntagged: The number of received packets without the MAC security
 * tag (SecTAG) with ValidateFrames which is not in the strict mode.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_UNTAGGED_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_LOWER  VTSS_IOREG(0x1f, 1, 0x3106)


/** 
 * \brief global.InPktsUntagged - upper 8 bits
 *
 * \details
 * InPktsUntagged: The number of received packets without the MAC security
 * tag (SecTAG) with ValidateFrames which is not in the strict mode.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_UNTAGGED_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_UPPER  VTSS_IOREG(0x1f, 1, 0x3107)

/** 
 * \brief
 * global.InPktsUntagged - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_UPPER . IN_PKTS_UNTAGGED_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_UPPER_IN_PKTS_UNTAGGED_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_UPPER_IN_PKTS_UNTAGGED_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_UPPER_IN_PKTS_UNTAGGED_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.InPktsTagged - lower 32 bits
 *
 * \details
 * InPktsTagged: The number of received packets with the MAC security tag
 * (SecTAG).
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_TAGGED_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_TAGGED_LOWER  VTSS_IOREG(0x1f, 1, 0x3108)


/** 
 * \brief global.InPktsTagged - upper 8 bits
 *
 * \details
 * InPktsTagged: The number of received packets with the MAC security tag
 * (SecTAG).
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_TAGGED_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_TAGGED_UPPER  VTSS_IOREG(0x1f, 1, 0x3109)

/** 
 * \brief
 * global.InPktsTagged - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_TAGGED_UPPER . IN_PKTS_TAGGED_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_TAGGED_UPPER_IN_PKTS_TAGGED_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_TAGGED_UPPER_IN_PKTS_TAGGED_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_TAGGED_UPPER_IN_PKTS_TAGGED_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.InPktsBadTag - lower 32 bits
 *
 * \details
 * InPktsBadTag: The number of received packets discarded with an invalid
 * SecTAG or a zero value PN or an invalid ICV.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_BAD_TAG_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_BAD_TAG_LOWER  VTSS_IOREG(0x1f, 1, 0x310a)


/** 
 * \brief global.InPktsBadTag - upper 8 bits
 *
 * \details
 * InPktsBadTag: The number of received packets discarded with an invalid
 * SecTAG or a zero value PN or an invalid ICV.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_BAD_TAG_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_BAD_TAG_UPPER  VTSS_IOREG(0x1f, 1, 0x310b)

/** 
 * \brief
 * global.InPktsBadTag - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_BAD_TAG_UPPER . IN_PKTS_BAD_TAG_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_BAD_TAG_UPPER_IN_PKTS_BAD_TAG_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_BAD_TAG_UPPER_IN_PKTS_BAD_TAG_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_BAD_TAG_UPPER_IN_PKTS_BAD_TAG_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.InPktsUntaggedMiss - lower 32 bits
 *
 * \details
 * InPktsUntaggedMiss: The number of received packets without the MAC
 * security tag (SecTAG) for which no SA was hit.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_UNTAGGED_MISS_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_MISS_LOWER  VTSS_IOREG(0x1f, 1, 0x310c)


/** 
 * \brief global.InPktsUntaggedMiss - upper 8 bits
 *
 * \details
 * InPktsUntaggedMiss: The number of received packets without the MAC
 * security tag (SecTAG) for which no SA was hit.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_UNTAGGED_MISS_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_MISS_UPPER  VTSS_IOREG(0x1f, 1, 0x310d)

/** 
 * \brief
 * global.InPktsUntaggedMiss - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_MISS_UPPER . IN_PKTS_UNTAGGED_MISS_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_MISS_UPPER_IN_PKTS_UNTAGGED_MISS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_MISS_UPPER_IN_PKTS_UNTAGGED_MISS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_MISS_UPPER_IN_PKTS_UNTAGGED_MISS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.InPktsNoSCI - lower 32 bits
 *
 * \details
 * InPktsNoSCI: The number of received packets discarded with unknown SCI
 * information with the condition, validateFrames is in the strict mode or
 * the C bit in the SecTAG is set.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_NO_SCI_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_SCI_LOWER  VTSS_IOREG(0x1f, 1, 0x310e)


/** 
 * \brief global.InPktsNoSCI - upper 8 bits
 *
 * \details
 * InPktsNoSCI: The number of received packets discarded with unknown SCI
 * information with the condition, validateFrames is in the strict mode or
 * the C bit in the SecTAG is set.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_NO_SCI_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_SCI_UPPER  VTSS_IOREG(0x1f, 1, 0x310f)

/** 
 * \brief
 * global.InPktsNoSCI - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_SCI_UPPER . IN_PKTS_NO_SCI_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_SCI_UPPER_IN_PKTS_NO_SCI_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_SCI_UPPER_IN_PKTS_NO_SCI_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_SCI_UPPER_IN_PKTS_NO_SCI_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.InPktsUnknownSCI - lower 32 bits
 *
 * \details
 * InPktsUnknownSCI: The number of received packets with unknown SCI with
 * the condition, ValidateFrames is not in the strict mode and the C bit in
 * the SecTAG is not set.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_UNKNOWN_SCI_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNKNOWN_SCI_LOWER  VTSS_IOREG(0x1f, 1, 0x3110)


/** 
 * \brief global.InPktsUnknownSCI - upper 8 bits
 *
 * \details
 * InPktsUnknownSCI: The number of received packets with unknown SCI with
 * the condition, ValidateFrames is not in the strict mode and the C bit in
 * the SecTAG is not set.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_PKTS_UNKNOWN_SCI_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNKNOWN_SCI_UPPER  VTSS_IOREG(0x1f, 1, 0x3111)

/** 
 * \brief
 * global.InPktsUnknownSCI - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNKNOWN_SCI_UPPER . IN_PKTS_UNKNOWN_SCI_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNKNOWN_SCI_UPPER_IN_PKTS_UNKNOWN_SCI_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNKNOWN_SCI_UPPER_IN_PKTS_UNKNOWN_SCI_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNKNOWN_SCI_UPPER_IN_PKTS_UNKNOWN_SCI_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.InConsistCheckControlledNotPass - lower 32 bits
 *
 * \details
 * InConsistCheckControlledNotPass: The number of received packets with
 * Ingress consistency check failed when the destination port is controlled
 * port.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:ICC_CONTROLLED_NOT_PASS_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_CONTROLLED_NOT_PASS_LOWER  VTSS_IOREG(0x1f, 1, 0x3112)


/** 
 * \brief global.InConsistCheckControlledNotPass - upper 8 bits
 *
 * \details
 * InConsistCheckControlledNotPass: The number of received packets with
 * Ingress consistency check failed when the destination port is controlled
 * port.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:ICC_CONTROLLED_NOT_PASS_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_CONTROLLED_NOT_PASS_UPPER  VTSS_IOREG(0x1f, 1, 0x3113)

/** 
 * \brief
 * global.InConsistCheckControlledNotPass - upper 8 bits of the 40-bit
 * counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_CONTROLLED_NOT_PASS_UPPER . ICC_CONTROLLED_NOT_PASS_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_CONTROLLED_NOT_PASS_UPPER_ICC_CONTROLLED_NOT_PASS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_CONTROLLED_NOT_PASS_UPPER_ICC_CONTROLLED_NOT_PASS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_CONTROLLED_NOT_PASS_UPPER_ICC_CONTROLLED_NOT_PASS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.InConsistCheckUncontrolledNotPass - lower 32 bits
 *
 * \details
 * InConsistCheckUncontrolledNotPass: The number of received packets with
 * Ingress consistency check failed when the destination port is
 * uncontrolled port.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:ICC_UNCONTROLLED_NOT_PASS_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_UNCONTROLLED_NOT_PASS_LOWER  VTSS_IOREG(0x1f, 1, 0x3114)


/** 
 * \brief global.InConsistCheckUncontrolledNotPass - upper 8 bits
 *
 * \details
 * InConsistCheckUncontrolledNotPass: The number of received packets with
 * Ingress consistency check failed when the destination port is
 * uncontrolled port.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:ICC_UNCONTROLLED_NOT_PASS_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_UNCONTROLLED_NOT_PASS_UPPER  VTSS_IOREG(0x1f, 1, 0x3115)

/** 
 * \brief
 * global.InConsistCheckUncontrolledNotPass - upper 8 bits of the 40-bit
 * counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_UNCONTROLLED_NOT_PASS_UPPER . ICC_UNCONTROLLED_NOT_PASS_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_UNCONTROLLED_NOT_PASS_UPPER_ICC_UNCONTROLLED_NOT_PASS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_UNCONTROLLED_NOT_PASS_UPPER_ICC_UNCONTROLLED_NOT_PASS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_UNCONTROLLED_NOT_PASS_UPPER_ICC_UNCONTROLLED_NOT_PASS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.InConsistCheckControlledPass - lower 32 bits
 *
 * \details
 * InConsistCheckControlledPass: The number of received packets with
 * Ingress consistency check passed when the destination port is controlled
 * port.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:ICC_CONTROLLED_PASS_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_CONTROLLED_PASS_LOWER  VTSS_IOREG(0x1f, 1, 0x3116)


/** 
 * \brief global.InConsistCheckControlledPass - upper 8 bits
 *
 * \details
 * InConsistCheckControlledPass: The number of received packets with
 * Ingress consistency check passed when the destination port is controlled
 * port.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:ICC_CONTROLLED_PASS_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_CONTROLLED_PASS_UPPER  VTSS_IOREG(0x1f, 1, 0x3117)

/** 
 * \brief
 * global.InConsistCheckControlledPass - upper 8 bits of the 40-bit
 * counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_CONTROLLED_PASS_UPPER . ICC_CONTROLLED_PASS_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_CONTROLLED_PASS_UPPER_ICC_CONTROLLED_PASS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_CONTROLLED_PASS_UPPER_ICC_CONTROLLED_PASS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_CONTROLLED_PASS_UPPER_ICC_CONTROLLED_PASS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.InConsistCheckUncontrolledPass - lower 32 bits
 *
 * \details
 * InConsistCheckUncontrolledPass: The number of received packets with
 * Ingress consistency check pass when the destination port is uncontrolled
 * port.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:ICC_UNCONTROLLED_PASS_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_UNCONTROLLED_PASS_LOWER  VTSS_IOREG(0x1f, 1, 0x3118)


/** 
 * \brief global.InConsistCheckUncontrolledPass - upper 8 bits
 *
 * \details
 * InConsistCheckUncontrolledPass: The number of received packets with
 * Ingress consistency check pass when the destination port is uncontrolled
 * port.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:ICC_UNCONTROLLED_PASS_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_UNCONTROLLED_PASS_UPPER  VTSS_IOREG(0x1f, 1, 0x3119)

/** 
 * \brief
 * global.InConsistCheckUncontrolledPass - upper 8 bits of the 40-bit
 * counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_UNCONTROLLED_PASS_UPPER . ICC_UNCONTROLLED_PASS_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_UNCONTROLLED_PASS_UPPER_ICC_UNCONTROLLED_PASS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_UNCONTROLLED_PASS_UPPER_ICC_UNCONTROLLED_PASS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_ICC_UNCONTROLLED_PASS_UPPER_ICC_UNCONTROLLED_PASS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.InOverSizePkts - lower 32 bits
 *
 * \details
 * InOverSizePkts: Number of Incoming frames without VLAN_VALID which are
 * detected OverSize due to NON VLAN MTU check.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_OVERSIZE_PKTS_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_OVERSIZE_PKTS_LOWER  VTSS_IOREG(0x1f, 1, 0x311a)


/** 
 * \brief global.InOverSizePkts - upper 8 bits
 *
 * \details
 * InOverSizePkts: Number of Incoming frames without VLAN_VALID which are
 * detected OverSize due to NON VLAN MTU check.
 *
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IN_OVERSIZE_PKTS_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_OVERSIZE_PKTS_UPPER  VTSS_IOREG(0x1f, 1, 0x311b)

/** 
 * \brief
 * global.InOverSizePkts - upper 8 bits of  the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_OVERSIZE_PKTS_UPPER . IN_OVERSIZE_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_IN_OVERSIZE_PKTS_UPPER_IN_OVERSIZE_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_IN_OVERSIZE_PKTS_UPPER_IN_OVERSIZE_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_IN_OVERSIZE_PKTS_UPPER_IN_OVERSIZE_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.ifInUcastPkts - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IF_IN_UNICAST_PKTS_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_UNICAST_PKTS_LOWER  VTSS_IOREG(0x1f, 1, 0x311c)


/** 
 * \brief global.ifInUcastPkts - upper 8 bits
 *
 * \details
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IF_IN_UNICAST_PKTS_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_UNICAST_PKTS_UPPER  VTSS_IOREG(0x1f, 1, 0x311d)

/** 
 * \brief
 * global.ifInUcastPkts - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_UNICAST_PKTS_UPPER . IF_IN_UNICAST_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_UNICAST_PKTS_UPPER_IF_IN_UNICAST_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_UNICAST_PKTS_UPPER_IF_IN_UNICAST_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_UNICAST_PKTS_UPPER_IF_IN_UNICAST_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.ifInMulticastPkts - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IF_IN_MULTICAST_PKTS_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_MULTICAST_PKTS_LOWER  VTSS_IOREG(0x1f, 1, 0x311e)


/** 
 * \brief global.ifInMulticastPkts - upper 8 bits
 *
 * \details
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IF_IN_MULTICAST_PKTS_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_MULTICAST_PKTS_UPPER  VTSS_IOREG(0x1f, 1, 0x311f)

/** 
 * \brief
 * global.ifInMulticastPkts - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_MULTICAST_PKTS_UPPER . IF_IN_MULTICAST_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_MULTICAST_PKTS_UPPER_IF_IN_MULTICAST_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_MULTICAST_PKTS_UPPER_IF_IN_MULTICAST_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_MULTICAST_PKTS_UPPER_IF_IN_MULTICAST_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.ifInBroadcastPkts - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IF_IN_BROADCAST_PKTS_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_BROADCAST_PKTS_LOWER  VTSS_IOREG(0x1f, 1, 0x3120)


/** 
 * \brief global.ifInBroadcastPkts - upper 8 bits
 *
 * \details
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IF_IN_BROADCAST_PKTS_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_BROADCAST_PKTS_UPPER  VTSS_IOREG(0x1f, 1, 0x3121)

/** 
 * \brief
 * global.ifInBroadcastPkts - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_BROADCAST_PKTS_UPPER . IF_IN_BROADCAST_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_BROADCAST_PKTS_UPPER_IF_IN_BROADCAST_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_BROADCAST_PKTS_UPPER_IF_IN_BROADCAST_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_BROADCAST_PKTS_UPPER_IF_IN_BROADCAST_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.ifInOctets - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IF_IN_OCTETS_LOWER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_OCTETS_LOWER  VTSS_IOREG(0x1f, 1, 0x3122)


/** 
 * \brief global.ifInOctets - upper 32 bits
 *
 * \details
 * Register: \a MACSEC_INGR:GLOBAL_STATS_IGR:IF_IN_OCTETS_UPPER
 */
#define VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IF_IN_OCTETS_UPPER  VTSS_IOREG(0x1f, 1, 0x3123)

/**
 * Register Group: \a MACSEC_INGR:CNTR_CTRL_DEBUG_REGS
 *
 * Statistics counters, control, and debug registers
 */


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_INGR:CNTR_CTRL_DEBUG_REGS:COUNT_DEBUG1
 */
#define VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1  VTSS_IOREG(0x1f, 1, 0x3200)

/** 
 * \brief
 * SA increment mask
 * The order of the bits here follows the order of the SA counters and each
 * bit corresponds to one of the SA counter depending on the SA counter
 * position in the SA statistics.
 * READING: Indicates the SA counters that were incremented for the last
 * packet that passed through. Note that the upper 40-bits counters of an
 * octet counter are automatically incremented on a lower 40-bits counter
 * overflow. 
 * WRITING: The mask sets up the counters to increment for a test of the
 * counters module. Upper 40-bits counters of an octet counter can be
 * tested separately, although they automatically increment on a lower
 * 40-bits counter overflow. This written value can be read back until a
 * test is actually performed. Performing an actual test requires writing
 * to the COUNT_DEBUG4 register. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1 . SA_INCREMENT_MASK
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1_SA_INCREMENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1_SA_INCREMENT_MASK     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1_SA_INCREMENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,14)

/** 
 * \brief
 * SA octet increment
 * READING: Indicates the octet increment value for SA related octet
 * counters that were incremented for the last packet that passed through.
 * If more than one SA related octet counter was incremented, they all used
 * this value. 
 * WRITING: The written value is the octet increment for SA related octet
 * counters for a test of the counters module. This written value can be
 * read back until a test is actually performed. Performing an actual test
 * requires writing to the COUNT_DEBUG4 register.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1 . SA_OCTET_INCREMENT
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1_SA_OCTET_INCREMENT(x)  VTSS_ENCODE_BITFIELD(x,16,15)
#define  VTSS_M_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1_SA_OCTET_INCREMENT     VTSS_ENCODE_BITMASK(16,15)
#define  VTSS_X_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1_SA_OCTET_INCREMENT(x)  VTSS_EXTRACT_BITFIELD(x,16,15)


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_INGR:CNTR_CTRL_DEBUG_REGS:COUNT_DEBUG2
 */
#define VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2  VTSS_IOREG(0x1f, 1, 0x3201)

/** 
 * \brief
 * VLAN increment mask
 * The order of the bits here follows the order of the VLAN counters and
 * each bit corresponds to one of the VLAN counter depending on the VLAN
 * counter position in the VLAN statistics.
 * READING: Indicates the VLAN counters that were incremented for the last
 * packet that passed through. The upper 40-bits counters of an octet
 * counter are automatically incremented on a lower 40-bits counter
 * overflow. 
 * WRITING: The mask sets up the counters to increment for a test of the
 * counters module. Upper 40-bits counters of an octet counter can be
 * tested separately, although they automatically increment on a lower
 * 40-bits counter overflow. This written value can be read back until a
 * test is actually performed. Performing an actual test requires writing
 * to the COUNT_DEBUG4 register. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2 . VLAN_INCREMENT_MASK
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2_VLAN_INCREMENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2_VLAN_INCREMENT_MASK     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2_VLAN_INCREMENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/** 
 * \brief
 * VLAN octet increment
 * READING: Indicates the octet increment value for VLAN-related octet
 * counters that were incremented for the last packet that passed through.
 * If more than one VLAN-related octet counter was incremented, they all
 * used this value. 
 * WRITING: The written value is the octet increment for VLAN-related octet
 * counters for a test of the counters module. This written value can be
 * read back until a test is actually performed. Performing an actual test
 * requires writing to the COUNT_DEBUG4 register.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2 . VLAN_OCTET_INCREMENT
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2_VLAN_OCTET_INCREMENT(x)  VTSS_ENCODE_BITFIELD(x,16,15)
#define  VTSS_M_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2_VLAN_OCTET_INCREMENT     VTSS_ENCODE_BITMASK(16,15)
#define  VTSS_X_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2_VLAN_OCTET_INCREMENT(x)  VTSS_EXTRACT_BITFIELD(x,16,15)


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_INGR:CNTR_CTRL_DEBUG_REGS:COUNT_DEBUG3
 */
#define VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG3  VTSS_IOREG(0x1f, 1, 0x3202)

/** 
 * \brief
 * Global increment mask
 * The order of the bits here follows the order of the global counters and
 * each bit corresponds to one of the global counter depending on the
 * global counter position in the global statistics.
 * READING: Indicates the global counters that were incremented for the
 * last packet that passed through. The upper 40-bits counters of an octet
 * counter are automatically incremented on a lower 40-bits counter
 * overflow. 
 * WRITING: The mask sets up the global counters to increment for a test of
 * the counters module. Upper 40-bits counters of an octet counter can be
 * tested separately, although they automatically increment on a lower
 * 40-bits counter overflow. This written value can be read back until a
 * test is actually performed. Performing an actual test requires writing
 * to the COUNT_DEBUG4 register. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG3 . GLOBAL_INCREMENT_MASK
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG3_GLOBAL_INCREMENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG3_GLOBAL_INCREMENT_MASK     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG3_GLOBAL_INCREMENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_INGR:CNTR_CTRL_DEBUG_REGS:COUNT_DEBUG4
 */
#define VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4  VTSS_IOREG(0x1f, 1, 0x3203)

/** 
 * \brief
 * Read/clear Reading a 1b indicates that the COUNT_DEBUG1 register has
 * been written with test data (and will return this test data when read). 
 * Writing a 1b performs a SA related counters test using the sa_nr written
 * here and the last value written to the COUNT_DEBUG1 register bit falls
 * back to 0b automatically when all requested increments have been
 * performed. While 1b, normal increment requests are ignored. Writing a 0b
 * has no effect.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4 . SA_TEST
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_SA_TEST  VTSS_BIT(0)

/** 
 * \brief
 * Read/clear, Reading a 1b indicates that the COUNT_DEBUG2 register has
 * been written with test data (and will return this test data when read). 
 * Writing a 1b performs a VLAN-related counters test using the vlan_up
 * written here and the last value written to the COUNT_DEBUG2 register bit
 * falls back to 0b automatically when all requested increments have been
 * performed. While 1b, normal increment requests are ignored. Writing a 0b
 * has no effect.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4 . VLAN_TEST
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_VLAN_TEST  VTSS_BIT(1)

/** 
 * \brief
 * Read/clear, Reading a 1b indicates that the COUNT_DEBUG3 register has
 * been written with test data (and will return this test data when read). 
 * Writing a 1b performs a global counters test using the
 * global_octet_increment written here and the last value written to the
 * COUNT_DEBUG3 register bit falls back to 0b automatically when all
 * requested increments have been performed. While 1b, normal increment
 * requests are ignored. Writing a 0b has no effect.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4 . GLOBAL_TEST
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_GLOBAL_TEST  VTSS_BIT(2)

/** 
 * \brief
 * READING: Indicates the SA index used for SA-related counters that were
 * incremented for the last packet that passed through. Width of the field
 * depends on number of SA in configuration:
 * 16 SA = 4 bits
 * 32 SA = 5 bits
 * 64 SA = 6 bits
 * If no SA was hit, bits [5:4] indicate the result of the MACsec
 * classification 
 * 00b = untagged
 * 01b = tagged
 * 10b = bad tag
 * 11b = KaY)
 * Bit [6] indicates the packet was classified as a control packet and bit
 * [7] is reserved (should be ignored). 
 * WRITING: The written value is the SA index for a test of the SA-related
 * counters in the module.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4 . SA_NR
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_SA_NR(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_SA_NR     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_SA_NR(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * READING: Indicates the VLAN user priority used for VLAN-related counters
 * that were incremented for the last packet that passed through. 
 * WRITING: The written value is the VLAN user priority for a test of the
 * VLAN-related counters in the module.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4 . VLAN_UP
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_VLAN_UP(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_VLAN_UP     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_VLAN_UP(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * When reading, indicates the octet increment value for global octet
 * counters that were incremented for the last packet that passed through
 * the MACsec block. If more than one global octet counter was incremented,
 * they all used this value. When writing, the written value is the octet
 * increment for global octet counters for a test of the counters module.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4 . GLOBAL_OCTET_INCREMENT
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_GLOBAL_OCTET_INCREMENT(x)  VTSS_ENCODE_BITFIELD(x,16,15)
#define  VTSS_M_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_GLOBAL_OCTET_INCREMENT     VTSS_ENCODE_BITMASK(16,15)
#define  VTSS_X_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_GLOBAL_OCTET_INCREMENT(x)  VTSS_EXTRACT_BITFIELD(x,16,15)


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_INGR:CNTR_CTRL_DEBUG_REGS:COUNT_CONTROL
 */
#define VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL  VTSS_IOREG(0x1f, 1, 0x3204)

/** 
 * \brief
 * Reset all
 * Set-only: 1b = Reset all statistics counters to zero (increments are
 * ignored while doing this, reading any counter returns zeroes),
 * automatically falls back to 0b when done. Writing 0b has no effect.
 * Default state of 1b coming out of reset clears all counters after
 * power-up. Writing this bit with a 1b keeps other fields in this register
 * intact, irrespective of the value written.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL . RESET_ALL
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_RESET_ALL  VTSS_BIT(0)

/** 
 * \brief
 * 1b: Enable normal read/write access to the counter memory for debugging
 * purposes (reset_all has priority). In this mode, increment operation
 * requests (as well as test increment requests made via the COUNT_DEBUG4
 * register) are ignored and clear-on-read is suppressed.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL . DEBUG_ACCESS
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_DEBUG_ACCESS  VTSS_BIT(1)

/** 
 * \details 
 * 0b: Counters wrap back to zero on overflow
 * 1b: Counters do not increment past maximum value 
 *
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL . SATURATE_CNTRS
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_SATURATE_CNTRS  VTSS_BIT(2)

/** 
 * \details 
 * 0b: Reading counters does not change them
 * 1b: Counters are cleared on a read access
 *
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL . AUTO_CNTR_RESET
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_AUTO_CNTR_RESET  VTSS_BIT(3)


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_INGR:CNTR_CTRL_DEBUG_REGS:COUNT_INCEN1
 */
#define VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1  VTSS_IOREG(0x1f, 1, 0x3205)

/** 
 * \brief
 * SA increment enable
 * Controls which SA related counters may be incremented. The default (1b)
 * enables all available counters. The order of the counter enable bits
 * follows that of the sa_increment_mask field in the COUNT_DEBUG1
 * register. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1 . SA_INCREMENT_ENABLE
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1_SA_INCREMENT_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1_SA_INCREMENT_ENABLE     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1_SA_INCREMENT_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,14)

/** 
 * \brief
 * VLAN increment enable
 * Controls which of the VLAN-related counters may be incremented. The
 * default (1b) enables all available counters. The order of the counter
 * enable bits follows that of the vlan_increment_mask field in the
 * COUNT_DEBUG2 register. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1 . VLAN_INCREMENT_ENABLE
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1_VLAN_INCREMENT_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1_VLAN_INCREMENT_ENABLE     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1_VLAN_INCREMENT_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,16,5)


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_INGR:CNTR_CTRL_DEBUG_REGS:COUNT_INCEN2
 */
#define VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN2  VTSS_IOREG(0x1f, 1, 0x3206)

/** 
 * \brief
 * Global increment enable
 * Controls which of the global counters may be incremented. The default
 * (1b) enables all available counters. The order of the counter enable
 * bits follows that of the global_increment_mask field in the COUNT_DEBUG3
 * register. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN2 . GLOBAL_INCREMENT_ENABLE
 */
#define  VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN2_GLOBAL_INCREMENT_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN2_GLOBAL_INCREMENT_ENABLE     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN2_GLOBAL_INCREMENT_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,18)

/**
 * Register Group: \a MACSEC_INGR:IG_CC_PARAMS
 *
 * Ingress consistency check parameters 
 */


/** 
 * \brief Ingress consistency check entry registers
 *
 * \details
 * Register: \a MACSEC_INGR:IG_CC_PARAMS:IG_CC_ENTRY_LO
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_LO(ri)  VTSS_IOREG(0x1f, 1, 0x3800 | (ri * 4))

/** 
 * \brief
 * VLAN ID compare value
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_LO . VLAN_ID
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_LO_VLAN_ID(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_LO_VLAN_ID     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_LO_VLAN_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/** 
 * \brief
 * Ethertype compare value (stored byte swapped, for instance MACsec tag
 * value 0x88E5 is stored as 0xE588 in this field), compared against actual
 * Ethertype field in a non-VLAN packet, compared against the next
 * Ethertype field in a VLAN packet (or even a third Ethertype field in
 * case two VLAN tags are found).
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_LO . PAYLOAD_ETYPE
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_LO_PAYLOAD_ETYPE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_LO_PAYLOAD_ETYPE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_LO_PAYLOAD_ETYPE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Ingress consistency check entry registers
 *
 * \details
 * Register: \a MACSEC_INGR:IG_CC_PARAMS:IG_CC_ENTRY_HI
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI(ri)  VTSS_IOREG(0x1f, 1, 0x3801 | (ri * 4))

/** 
 * \details 
 * 1b: SAI table lookup entry matched for this packet
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . SAI_HIT
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_SAI_HIT  VTSS_BIT(0)

/** 
 * \details 
 * 1b: Packet is tagged as 802.1Q or 802.1s VLAN packet (using the tags
 * stored in SAM_PP_TAGS and SAM_PP_TAGS2 registers for comparison).
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . VLAN_VALID
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_VLAN_VALID  VTSS_BIT(1)

/** 
 * \details 
 * 1b: First Ethertype in packet > cp_etype_max_len (as defined in the
 * IG_CC_CONTROL register)
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . ETYPE_VALID
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_ETYPE_VALID  VTSS_BIT(2)

/** 
 * \details 
 * 1b: Packet was classified as control packet by control packet
 * classification logic
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . CTRL_PACKET
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_CTRL_PACKET  VTSS_BIT(3)

/** 
 * \details 
 * 1b: Enable sai_hit field compare
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . SAI_HIT_MASK
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_SAI_HIT_MASK  VTSS_BIT(4)

/** 
 * \details 
 * 1b: Enable sai_nr field compare (do not set to 1b if SAI miss is
 * expected)
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . SAI_NR_MASK
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_SAI_NR_MASK  VTSS_BIT(5)

/** 
 * \details 
 * 1b: Enable vlan_valid field compare 
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . VLAN_VALID_MASK
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_VLAN_VALID_MASK  VTSS_BIT(6)

/** 
 * \details 
 * 1b: Enable vlan_id field compare (do not set to 1b if no VLAN packet is
 * expected here)
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . VLAN_ID_MASK
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_VLAN_ID_MASK  VTSS_BIT(7)

/** 
 * \details 
 * 1b: Enable etype_valid field compare
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . ETYPE_VALID_MASK
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_ETYPE_VALID_MASK  VTSS_BIT(8)

/** 
 * \details 
 * 1b: Enable payload_e_type field compare
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . PAYL_ETYPE_MASK
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_PAYL_ETYPE_MASK  VTSS_BIT(9)

/** 
 * \details 
 * 1b: Enable ctrl_packet field compare
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . CTRL_PACKET_MASK
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_CTRL_PACKET_MASK  VTSS_BIT(10)

/** 
 * \brief
 * Priority of this entry for determining the match action on a match
 *
 * \details 
 * 0: Lowest
 * 7: Highest
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . MATCH_PRIORITY
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_MATCH_PRIORITY(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_MATCH_PRIORITY     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_MATCH_PRIORITY(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * Action to perform on packet. If multiple entries match, then the
 * match_priority fields determine which entry actually determines the
 * action to take. If match_priority fields are equal, then the lowest
 * numbered entry takes precedence.
 *
 * \details 
 * 0b: Drop
 * 1b: Pass
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . MATCH_ACTION
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_MATCH_ACTION  VTSS_BIT(15)

/** 
 * \brief
 * Compare value for SAI entry number that matched
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . SAI_NR
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_SAI_NR(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_SAI_NR     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_SAI_NR(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/** 
 * \details 
 * 1b: Enable parsed inner VLAN user priority value compare with
 * vlan_up_inner field in the IG_CC_ENTRY2_x register. If Q-in-Q is not
 * found, this comparison is not performed.
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . VLAN_UP_INNER_MASK
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_VLAN_UP_INNER_MASK  VTSS_BIT(24)

/** 
 * \details 
 * 1b: Enable parsed inner VLAN ID value compare with vlan_up_inner field
 * in the IG_CC_ENTRY2_x register. If Q-in-Q is not found, this comparison
 * is not performed.
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI . VLAN_ID_INNER_MASK
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY_HI_VLAN_ID_INNER_MASK  VTSS_BIT(25)


/** 
 * \brief Ingress consistency check entry registers.
 *
 * \details
 * Register: \a MACSEC_INGR:IG_CC_PARAMS:IG_CC_ENTRY2
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY2(ri)  VTSS_IOREG(0x1f, 1, 0x3802 | (ri * 4))

/** 
 * \brief
 * Parsed inner VLAN ID compare value
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY2 . VLAN_ID_INNER
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY2_VLAN_ID_INNER(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY2_VLAN_ID_INNER     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY2_VLAN_ID_INNER(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/** 
 * \brief
 * Parsed inner VLAN Up compare value
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY2 . VLAN_UP_INNER
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY2_VLAN_UP_INNER(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY2_VLAN_UP_INNER     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS_IG_CC_ENTRY2_VLAN_UP_INNER(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * Register Group: \a MACSEC_INGR:IG_CC_PARAMS2
 *
 * Ingress consistency check parameters 
 */


/** 
 * \brief Ingress consistency check control register
 *
 * \details
 * Register: \a MACSEC_INGR:IG_CC_PARAMS2:IG_CC_ENABLE1
 */
#define VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_ENABLE1  VTSS_IOREG(0x1f, 1, 0x3a00)


/** 
 * \brief Ingress consistency check control register
 *
 * \details
 * Register: \a MACSEC_INGR:IG_CC_PARAMS2:IG_CC_ENABLE2
 */
#define VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_ENABLE2  VTSS_IOREG(0x1f, 1, 0x3a01)


/** 
 * \brief Ingress consistency check control register
 *
 * \details
 * Register: \a MACSEC_INGR:IG_CC_PARAMS2:IG_CC_CONTROL
 */
#define VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_CONTROL  VTSS_IOREG(0x1f, 1, 0x3a10)

/** 
 * \brief
 * Action to perform on control packet (as defined by the control packet
 * classification logic) when none of the entries match.
 *
 * \details 
 * 0b: Drop
 * 1b: Pass
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_CONTROL . NON_MATCH_CTRL_ACT
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_CONTROL_NON_MATCH_CTRL_ACT  VTSS_BIT(14)

/** 
 * \brief
 * Action to perform on non-control packet (as defined by the control
 * packet classification logic) when none of the entries match.
 *
 * \details 
 * 0b: Drop
 * 1b: Pass
 *
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_CONTROL . NON_MATCH_ACT
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_CONTROL_NON_MATCH_ACT  VTSS_BIT(15)


/** 
 * \brief Ingress consistency check control register 
 *
 * \details
 * Register: \a MACSEC_INGR:IG_CC_PARAMS2:IG_CC_TAGS
 */
#define VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_TAGS  VTSS_IOREG(0x1f, 1, 0x3a11)

/** 
 * \brief
 * Ether-type field compare value for the etype_valid comparison (global
 * for all entries), default value 0x05FF indicates the maximum length that
 * can be encoded in the Ethertype field, which is 1535 Bytes as this is a
 * length compare, this field is not swapped
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_TAGS . CP_ETYPE_MAX_LEN
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_TAGS_CP_ETYPE_MAX_LEN(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_TAGS_CP_ETYPE_MAX_LEN     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_TAGS_CP_ETYPE_MAX_LEN(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Ingress VLAN tag detection parameter and debug register
 *
 * \details
 * Register: \a MACSEC_INGR:IG_CC_PARAMS2:IG_CP_TAG
 */
#define VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG  VTSS_IOREG(0x1f, 1, 0x3a14)

/** 
 * \brief
 * Translate one priority value into another using map table
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG . MAP_TBL
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_MAP_TBL(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_MAP_TBL     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_MAP_TBL(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

/** 
 * \brief
 * Default user priority
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG . DEF_UP
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_DEF_UP(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_DEF_UP     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_DEF_UP(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/** 
 * \brief
 * STAG user priority enable
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG . STAG_UP_EN
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_STAG_UP_EN  VTSS_BIT(27)

/** 
 * \brief
 * QTAG user priority map enable
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG . QTAG_UP_EN
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_QTAG_UP_EN  VTSS_BIT(28)

/** 
 * \brief
 * Parse Q-in-Q enable
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG . PARSE_QINQ
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_PARSE_QINQ  VTSS_BIT(29)

/** 
 * \brief
 * Parse STAG enable
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG . PARSE_STAG
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_PARSE_STAG  VTSS_BIT(30)

/** 
 * \brief
 * Parse QTAG enable
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG . PARSE_QTAG
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_PARSE_QTAG  VTSS_BIT(31)


/** 
 * \brief Ingress VLAN tag detection parameter and debug register
 *
 * \details
 * Register: \a MACSEC_INGR:IG_CC_PARAMS2:IG_PP_TAGS
 */
#define VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS  VTSS_IOREG(0x1f, 1, 0x3a15)

/** 
 * \brief
 * Ether-type value used for 802.1Q tag type comparison in the additional
 * fields parsing algorithm. As this is the VLAN tag, the default value is
 * 0x8100 (stored byte swapped as value 0x0081). 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS . QTAG_VALUE
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS_QTAG_VALUE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS_QTAG_VALUE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS_QTAG_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Ether-type value used for 802.1s tag type comparison in the additional
 * fields parsing algorithm. The default value is 0x88A8 (stored byte
 * swapped as value 0xA888) to allow stacked VLAN tags, but it can be
 * re-programmed to another value if user-specific VLAN tags are used.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS . STAG_VALUE
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS_STAG_VALUE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS_STAG_VALUE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS_STAG_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief VLAN tag detection parameters
 *
 * \details
 * Register: \a MACSEC_INGR:IG_CC_PARAMS2:IG_PP_TAGS2
 */
#define VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS2  VTSS_IOREG(0x1f, 1, 0x3a16)

/** 
 * \brief
 * Secondary Ethertype value used for 802.1s tag type comparison in the
 * additional fields parsing algorithm. The default value is 0x9100 (stored
 * byte swapped as value 0x0091). 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS2 . STAG_VALUE2
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS2_STAG_VALUE2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS2_STAG_VALUE2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS2_STAG_VALUE2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Tertiary Ethertype value used for 802.1s tag type comparison in the
 * additional fields parsing algorithm. The default value is 0x9200 (stored
 * byte swapped as value 0x0092). 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS2 . STAG_VALUE3
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS2_STAG_VALUE3(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS2_STAG_VALUE3     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS2_IG_PP_TAGS2_STAG_VALUE3(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \details
 * Register: \a MACSEC_INGR:IG_CC_PARAMS2:IG_CP_TAG2
 */
#define VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG2  VTSS_IOREG(0x1f, 1, 0x3a17)

/** 
 * \brief
 * Translate one priority value into another using MAP Table. This is MAP
 * table for inner tag.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG2 . MAP_TBL2
 */
#define  VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG2_MAP_TBL2(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG2_MAP_TBL2     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG2_MAP_TBL2(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

/**
 * Register Group: \a MACSEC_INGR:POST_PROC_CTL_DEBUG_REGS
 *
 * Output post processor control and debug registers
 */


/** 
 * \brief VLAN MTU check register
 *
 * \details
 * Register: \a MACSEC_INGR:POST_PROC_CTL_DEBUG_REGS:VLAN_MTU_CHECK
 *
 * @param ri Register: VLAN_MTU_CHECK, 0-7
 */
#define VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK(ri)  VTSS_IOREG(0x1f, 1, 0x3c40 | (ri))

/** 
 * \brief
 * Maximum packet size (in bytes) allowed for VLAN packets with a user
 * priority matching the number indicated in the register name. Default
 * value 1518 (decimal, or 0x05EE) allows standard Ethernet frames (without
 * CRC) incorporating one VLAN tag. Packets longer than the value
 * programmed here will be counted as oversized. packets and can optionally
 * be truncated and dropped under control of the mtu_comp_drop bit 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK . MTU_COMPARE
 */
#define  VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK_MTU_COMPARE(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK_MTU_COMPARE     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK_MTU_COMPARE(x)  VTSS_EXTRACT_BITFIELD(x,0,15)

/** 
 * \brief
 * 1b = drop (by corrupting the CRC) VLAN packets with a user priority
 * matching the number indicated in the register name that are longer than
 * the maximum packet size defined by the mtu_compare field.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK . MTU_COMP_DROP
 */
#define  VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK_MTU_COMP_DROP  VTSS_BIT(15)


/** 
 * \brief Non VLAN MTU check register
 *
 * \details
 * Register: \a MACSEC_INGR:POST_PROC_CTL_DEBUG_REGS:NON_VLAN_MTU_CHECK
 */
#define VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK  VTSS_IOREG(0x1f, 1, 0x3c48)

/** 
 * \brief
 * Maximum packet size (in bytes) allowed for all non-VLAN packets. Default
 * value 1514 (decimal, or 0x05EA) allows standard Ethernet frames (without
 * CRC) without a VLAN tag. Packets longer than the value programmed here
 * will be counted as oversized. packets and can optionally be truncated
 * and dropped under control of the mtu_comp_drop bit.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK . NV_MTU_COMPARE
 */
#define  VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMPARE(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMPARE     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMPARE(x)  VTSS_EXTRACT_BITFIELD(x,0,15)

/** 
 * \brief
 * 1b = drop (by corrupting the CRC) all non-VLAN packets that are longer
 * than the maximum packet size defined by the mtu_compare field.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK . NV_MTU_COMP_DROP
 */
#define  VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMP_DROP  VTSS_BIT(15)


/** 
 * \brief Security fail and error mask registers
 *
 * \details
 * Register: \a MACSEC_INGR:POST_PROC_CTL_DEBUG_REGS:COUNT_SECFAIL1
 */
#define VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1  VTSS_IOREG(0x1f, 1, 0x3c49)

/** 
 * \brief
 * This mask specifies which SA-related counter increments are regarded a
 * security fail event bit 
 * [0] is for the first 40-bits counter of an SA-related counter set. The
 * upper 40-bits counters of an octet counter should not have their mask
 * bit set here. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1 . SA_SECFAIL_MASK
 */
#define  VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_SA_SECFAIL_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_SA_SECFAIL_MASK     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_SA_SECFAIL_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,14)

/** 
 * \details 
 * 0b: Do not update any VLAN counters for a non-VLAN packet
 * 1b: Update VLAN counters for non-VLAN packets using the default user
 * priority assigned to them
 *
 * Field: VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1 . VLAN_CNTR_UPDATE
 */
#define  VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_VLAN_CNTR_UPDATE  VTSS_BIT(15)

/** 
 * \brief
 * This bit is reserved in an egress-only (e) core (write with zero and
 * ignore on read)
 *
 * \details 
 * 0b: Always use result of consistency checking module
 * 1b: Force outputs of consistency checking module to non-consistent. and
 * no VLAN tag found. if a MACsec packet fails integrity check,performed by
 * the MACsec crypto core. 
 *
 * Field: VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1 . GATE_CONS_CHECK
 */
#define  VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_GATE_CONS_CHECK  VTSS_BIT(16)

/** 
 * \brief
 * Mask for MACsec crypto-core first result token word bits [31:17] these
 * are the error bits of that module's processing. The default value
 * selects the errors that are deemed fatal. Do not change the contents of
 * this field.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1 . ERROR_MASK
 */
#define  VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_ERROR_MASK(x)  VTSS_ENCODE_BITFIELD(x,17,15)
#define  VTSS_M_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_ERROR_MASK     VTSS_ENCODE_BITMASK(17,15)
#define  VTSS_X_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_ERROR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,17,15)


/** 
 * \brief Security fail and error mask registers
 *
 * \details
 * Register: \a MACSEC_INGR:POST_PROC_CTL_DEBUG_REGS:COUNT_SECFAIL2
 */
#define VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL2  VTSS_IOREG(0x1f, 1, 0x3c4a)

/** 
 * \brief
 * This mask specifies which global counter increments are regarded a
 * security fail event bit [0] is for the first 40-bits global counter. The
 * upper 40-bits counters of an octet counter should not have their mask
 * bit set here.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL2 . GLOBAL_SECFAIL_MASK
 */
#define  VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL2_GLOBAL_SECFAIL_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL2_GLOBAL_SECFAIL_MASK     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL2_GLOBAL_SECFAIL_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Post Processor control register
 *
 * \details
 * Register: \a MACSEC_INGR:POST_PROC_CTL_DEBUG_REGS:PP_CTRL
 */
#define VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_PP_CTRL  VTSS_IOREG(0x1f, 1, 0x3c4b)

/** 
 * \brief
 * MACsec octet counters increment mode:
 * Egress configuration:
 * 0b = OutOctetsProtected/OutOctetsEncrypted is incremented only if
 * protectedFrames=True (as required by IEEE 802.1AE)
 * 1b = OutOctetsProtected/OutOctetsEncrypted is incremented if SA is hit
 * and flow type is MACsec egress.
 * Ingress configuration:
 * 0b = InOctetsDecrypted/InOctetsValidated is incremented only if
 * validateFrames=True (as required by IEEE 802.1AE)
 * 1b = InOctetsDecrypted/InOctetsValidated is incremented SA is hit and
 * flow type is MACsec ingress.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_PP_CTRL . MACSEC_OCTET_INCR_MODE
 */
#define  VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_PP_CTRL_MACSEC_OCTET_INCR_MODE  VTSS_BIT(0)

/**
 * Register Group: \a MACSEC_INGR:ADV_INTR_CTRL_REGS
 *
 * Advanced interrupt controller registers
 */


/** 
 * \brief AIC input polarity control
 *
 * \details
 * Register: \a MACSEC_INGR:ADV_INTR_CTRL_REGS:AIC_POL_CTRL
 */
#define VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_POL_CTRL  VTSS_IOREG(0x1f, 1, 0x3e00)

/** 
 * \brief
 * Individual polarity control. bits per interrupt input
 *
 * \details 
 * 0b: Low level or falling edge 
 * 1b: High level or rising edge (all bits fixed to this value) 
 *
 * Field: VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_POL_CTRL . POLARITY_CONTROL
 */
#define  VTSS_F_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_POL_CTRL_POLARITY_CONTROL(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_POL_CTRL_POLARITY_CONTROL     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_POL_CTRL_POLARITY_CONTROL(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief AIC input type control
 *
 * \details
 * Register: \a MACSEC_INGR:ADV_INTR_CTRL_REGS:AIC_TYPE_CTRL
 */
#define VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_TYPE_CTRL  VTSS_IOREG(0x1f, 1, 0x3e01)

/** 
 * \brief
 * Individual type control. bits per interrupt input
 *
 * \details 
 * 0b: Level 
 * 1b: Edge detect (all bits are fixed to this value) 
 *
 * Field: VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_TYPE_CTRL . TYPE_CONTROL
 */
#define  VTSS_F_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_TYPE_CTRL_TYPE_CONTROL(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_TYPE_CTRL_TYPE_CONTROL     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_TYPE_CTRL_TYPE_CONTROL(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief AIC interrupt enable control
 *
 * \details
 * Register: \a MACSEC_INGR:ADV_INTR_CTRL_REGS:AIC_ENABLE_CTRL
 */
#define VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CTRL  VTSS_IOREG(0x1f, 1, 0x3e02)

/** 
 * \brief
 * Individual enable control. bits per interrupt input
 *
 * \details 
 * 0b: Disabled 
 * 1b: Enabled 
 *
 * Field: VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CTRL . ENABLE_CONTROL
 */
#define  VTSS_F_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CTRL_ENABLE_CONTROL(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CTRL_ENABLE_CONTROL     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CTRL_ENABLE_CONTROL(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief AIC raw interrupt pending status
 *
 * \details
 * Register: \a MACSEC_INGR:ADV_INTR_CTRL_REGS:AIC_RAW_STAT
 */
#define VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_RAW_STAT  VTSS_IOREG(0x1f, 1, 0x3e03)

/** 
 * \brief
 * When read, this register indicates individual raw status bits per
 * interrupt input, as follows:
 * 0b: Inactive 
 * 1b: Pending
 * When written, this register is called AIC_ENABLE_SET and this field is
 * Interrupt Enabled
 *
 * \details 
 * 1b: Enable the interrupt by setting the corresponding AIC_ENABLE_CTRL
 * register bit
 * 0b: Writing a 0b has no effect; after writing a 1b it is not necessary
 * to write a 0b
 *
 * Field: VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_RAW_STAT . RAW_STATUS
 */
#define  VTSS_F_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_RAW_STAT_RAW_STATUS(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_RAW_STAT_RAW_STATUS     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_RAW_STAT_RAW_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief AIC masked interrupt pending status
 *
 * \details
 * Register: \a MACSEC_INGR:ADV_INTR_CTRL_REGS:AIC_ENABLED_STAT
 */
#define VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLED_STAT  VTSS_IOREG(0x1f, 1, 0x3e04)

/** 
 * \brief
 * Individual enabled status bits per interrupt input (i.e. the status
 * after masking). Software should write a 1 to clear the corresponding
 * interrupt in AIC_RAW_STAT (and this register as well).
 *
 * \details 
 * 0b: Inactive 
 * 1b: Pending
 *
 * Field: VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLED_STAT . ENABLED_STATUS
 */
#define  VTSS_F_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLED_STAT_ENABLED_STATUS(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLED_STAT_ENABLED_STATUS     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLED_STAT_ENABLED_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief AIC interrupt disable 
 *
 * \details
 * Register: \a MACSEC_INGR:ADV_INTR_CTRL_REGS:AIC_ENABLE_CLR
 */
#define VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CLR  VTSS_IOREG(0x1f, 1, 0x3e05)

/** 
 * \brief
 * Individual interrupt disable. bits per interrupt input
 *
 * \details 
 * 1b: Disable the interrupt by clearing the corresponding AIC_ENABLE_CTRL
 * register bit
 * 0b: Writing a 0b has no effect; after writing a 1b it is not necessary
 * to write a 0b
 *
 * Field: VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CLR . INTERRUPT_DISABLE
 */
#define  VTSS_F_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CLR_INTERRUPT_DISABLE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CLR_INTERRUPT_DISABLE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CLR_INTERRUPT_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief AIC module configuration 
 *
 * \details
 * Register: \a MACSEC_INGR:ADV_INTR_CTRL_REGS:AIC_OPTIONS
 */
#define VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_OPTIONS  VTSS_IOREG(0x1f, 1, 0x3e06)

/** 
 * \brief
 * Direct indication of the number of interrupt inputs
 *
 * \details 
 * ingress: 5 interrupt inputs
 * egress: 4 interrupt inputs
 *
 * Field: VTSS_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_OPTIONS . NUMBER_OF_INPUTS
 */
#define  VTSS_F_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_OPTIONS_NUMBER_OF_INPUTS(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_OPTIONS_NUMBER_OF_INPUTS     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MACSEC_INGR_ADV_INTR_CTRL_REGS_AIC_OPTIONS_NUMBER_OF_INPUTS(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a MACSEC_INGR:CRYPTO_CTRL_STATUS_REGS
 *
 * MACsec crypto core control and status registers
 */


/** 
 * \brief Context size and fetching mode configuration
 *
 * \details
 * Register: \a MACSEC_INGR:CRYPTO_CTRL_STATUS_REGS:CONTEXT_CTRL
 */
#define VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL  VTSS_IOREG(0x1f, 1, 0x3d02)

/** 
 * \brief
 * Context size 
 * Indicates the size (in dwords) of the context that must be fetched. This
 * field must be programmed with the value that corresponds to the used
 * context with the maximum size for the supported contexts. Note that the
 * MACsec crypto engine always fetches a multiple of 16 bytes. This means
 * that the programmed value is rounded up to the next multiple of four
 * (32-bit words), if needed.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL . CTX_SIZE
 */
#define  VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_CTX_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_CTX_SIZE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_CTX_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Select sequence number threshold mode.
 * If this value is 1b, the E8 is triggered only when the next packet
 * number equals the threshold value in the threshold register.
 * If this value is 0b, the E8 is triggered when the next packet number
 * equals or exceeds the threshold value in the threshold register.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL . THRESHOLD_MODE
 */
#define  VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_THRESHOLD_MODE  VTSS_BIT(10)

/** 
 * \brief
 * MACsec EtherType 
 * Contains the EtherType field for MACsec. This field is inserted in the
 * SecTAG when processing a MACsec outbound token. It is reset to 0xE588
 * (EtherType 88-E5 represented in little endian format) and should not be
 * changed.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL . MACSEC_ETYPE
 */
#define  VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_MACSEC_ETYPE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_MACSEC_ETYPE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_MACSEC_ETYPE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Interrupt control status register
 *
 * \details
 * Register: \a MACSEC_INGR:CRYPTO_CTRL_STATUS_REGS:INTR_CTRL_STATUS
 */
#define VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS  VTSS_IOREG(0x1f, 1, 0x3d04)

/** 
 * \brief
 * [0] Input error 
 * Input data read module does not properly receive all data. (E2) 
 * [1] Output error 
 * This error cannot occur in the MACsec crypto engine and is therefore
 * always zero. 
 * [2] Processing 
 * An error occurred while processing the frame or parsing the token.
 * Combination of the errors E0, E1, E3 and E4 
 * [3] Context Error 
 * An invalid or Prohibited token has been fetched (Combination of the
 * errors E5 and E6) 
 * [4] Outbound Sequence Number Threshold 
 * If a sequence number exceeds the programmed sequence number threshold
 * (refer to SEQ_NUM_THRESH) due to an outbound sequence number increment
 * this interrupt is triggered. 
 * [5] Outbound Sequence Number roll-over 
 * If a sequence number roll-over (increment from maximum to zero) due to
 * an outbound sequence number increment this interrupt is triggered 
 * [13:6] Reserved 
 * [14] Fatal error 
 * Reset of engine required. This error is reserved in the MACsec crypto
 * engine and will not occur. 
 * [15] Interrupt output (pin) 
 * This is an OR of the enabled interrupts. If this signal is set to level.
 * (TOKEN_CTRL_STATUS: bit 17 = 1.) it must be separately cleared. If the
 * interrupt output is a pulse. (TOKEN_CTRL_STATUS: bit 17 = 0.) this
 * status 
 * bit is always zero. Bit [31] must be enabled (set to 1.) to assert the
 * interrupt output. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS . INTR_CLR_STATUS
 */
#define  VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS_INTR_CLR_STATUS(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS_INTR_CLR_STATUS     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS_INTR_CLR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * INTR_ENABLE register for INTR_CLR_STATUS.
 * [16] Input error 
 * Input data read module does not properly receive all data. (E2) 
 * [17] Output error 
 * This error cannot occur in the MACsec crypto engine and is therefore
 * always zero. 
 * [18] Processing 
 * An error occurred while processing the frame or parsing the token.
 * Combination of the errors E0, E1, E3 and E4 
 * [19] Context Error 
 * An invalid or Prohibited token has been fetched (Combination of the
 * errors E5 and E6) 
 * [20] Outbound Sequence Number Threshold 
 * If a sequence number exceeds the programmed sequence number threshold
 * (refer to SEQ_NUM_THRESH) due to an outbound sequence number increment
 * this interrupt is triggered. 
 * [21] Outbound Sequence Number roll-over 
 * If a sequence number roll-over (increment from maximum to zero) due to
 * an outbound sequence number increment this interrupt is triggered 
 * [29:22] Reserved 
 * [30] Fatal error 
 * Reset of engine required. This error is reserved in the MACsec crypto
 * engine and will not occur. 
 * [31] Interrupt output (pin) 
 * This is an OR of the enabled interrupts. If this signal is set to level.
 * (TOKEN_CTRL_STATUS: bit 17 = 1.) it must be separately cleared. If the
 * interrupt output is a pulse. (TOKEN_CTRL_STATUS: bit 17 = 0.) this
 * status 
 * bit is always zero. Bit [31] must be enabled (set to 1.) to assert the
 * interrupt output. 
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS . INTR_ENABLE
 */
#define  VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS_INTR_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS_INTR_ENABLE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS_INTR_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Sequence number threshold
 *
 * \details
 * This register can be configured to trigger an informative error E8
 * indicating the outbound sequence number equals the programmed value in
 * this register. With this error, the system has time to start a re-key
 * before the roll-over error fires. If the next (incremented) sequence
 * number equals this value, the sequence number threshold overflow bit E10
 * in the result token is set.
 *
 * Register: \a MACSEC_INGR:CRYPTO_CTRL_STATUS_REGS:SEQ_NUM_THRESH
 */
#define VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_SEQ_NUM_THRESH  VTSS_IOREG(0x1f, 1, 0x3d08)


/** 
 * \brief Sequence number threshold lower 32 bits for 64-bit register
 *
 * \details
 * Register: \a MACSEC_INGR:CRYPTO_CTRL_STATUS_REGS:SEQ_NUM_THRESH_LOWER
 */
#define VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_SEQ_NUM_THRESH_LOWER  VTSS_IOREG(0x1f, 1, 0x3d09)


/** 
 * \brief Sequence number threshold upper 32 bits for 64-bit register
 *
 * \details
 * Register: \a MACSEC_INGR:CRYPTO_CTRL_STATUS_REGS:SEQ_NUM_THRESH_UPPER
 */
#define VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_SEQ_NUM_THRESH_UPPER  VTSS_IOREG(0x1f, 1, 0x3d0a)


/** 
 * \brief NextPN autonomous update registers
 *
 * \details
 * Register: \a MACSEC_INGR:CRYPTO_CTRL_STATUS_REGS:NEXT_PN_LOWER
 */
#define VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_LOWER  VTSS_IOREG(0x1f, 1, 0x3d20)


/** 
 * \brief NextPN autonomous update registers
 *
 * \details
 * Register: \a MACSEC_INGR:CRYPTO_CTRL_STATUS_REGS:NEXT_PN_UPPER
 */
#define VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_UPPER  VTSS_IOREG(0x1f, 1, 0x3d21)


/** 
 * \brief NextPN Context ID register
 *
 * \details
 * Register: \a MACSEC_INGR:CRYPTO_CTRL_STATUS_REGS:NEXT_PN_CONTEXT_ID
 */
#define VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CONTEXT_ID  VTSS_IOREG(0x1f, 1, 0x3d22)


/** 
 * \brief NextPN control register
 *
 * \details
 * Register: \a MACSEC_INGR:CRYPTO_CTRL_STATUS_REGS:NEXT_PN_CTRL
 */
#define VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL  VTSS_IOREG(0x1f, 1, 0x3d23)

/** 
 * \brief
 * When read it provides the status of the nextPN update. After enabling
 * the update this bit automatically flips to zero when the action is
 * completed.
 * When written, the nextPN update action is started (enabled). It is not
 * allowed to start another update before the current action is completed.
 * The programmed sequence number, ID, address and size are used for the
 * update.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL . ENABLE_UPDATE
 */
#define  VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_ENABLE_UPDATE  VTSS_BIT(0)

/** 
 * \brief
 * This read only bit indicates if the previous update action resulted in a
 * sequence number update into the context memory. In other words the
 * programmed nextPN exceeded the current nextPN in the context record,
 * such that a context udapte was required. This bit is valid when bit [0]
 * of this register is zero (update done).
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL . NEXT_PN_WRITTEN
 */
#define  VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_NEXT_PN_WRITTEN  VTSS_BIT(1)

/** 
 * \brief
 * This bit must be set to 1 if the nextPN is a 64-bit sequence number.
 * This bit must be written with a 0 if the nextPN is a 32-bit sequence
 * number.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL . SEQ_NUM_SIZE
 */
#define  VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_SEQ_NUM_SIZE  VTSS_BIT(2)

/** 
 * \brief
 * This field must contain the 16B (128-bit) aligned pointer to the context
 * word containing the sequence number that must be validated and
 * potentially updated with the programmed nextPN.
 *
 * \details 
 * Field: VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL . NEXT_PN_CTX_ADDR
 */
#define  VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_NEXT_PN_CTX_ADDR(x)  VTSS_ENCODE_BITFIELD(x,4,28)
#define  VTSS_M_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_NEXT_PN_CTX_ADDR     VTSS_ENCODE_BITMASK(4,28)
#define  VTSS_X_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_NEXT_PN_CTX_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,4,28)


#endif /* _VTSS_VENICE_REGS_MACSEC_INGR_H_ */
