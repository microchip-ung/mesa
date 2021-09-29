// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_MACSEC_EGR_H_
#define _VTSS_MALIBU_REGS_MACSEC_EGR_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a MACSEC_EGR
 *
 * Flow-through MACsec egress and ingress IP registers
 *
 ***********************************************************************/

/**
 * Register Group: \a MACSEC_EGR:MACSEC_CTL_REGS
 *
 * MACsec Ingress and Egress wrapper control registers.
 */


/** 
 * \brief Mode configuration register
 *
 * \details
 * Register: \a MACSEC_EGR:MACSEC_CTL_REGS:MACSEC_ENA_CFG
 */
#define VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG  VTSS_IOREG(0x1f, 1, 0x8800)

/** 
 * \brief
 * MACsec clock enable.
 *
 * \details 
 * 0: All clocks for this module with the exception of CSR clock are
 * disabled.
 * 1: All clocks for this module are enabled.
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG . CLK_ENA
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA  VTSS_BIT(0)

/** 
 * \brief
 * MACsec software reset
 *
 * \details 
 * 0: Block operates normally.
 * 1: All logic (other than CSR target) is held in reset, clocks are not
 * disabled.
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG . SW_RST
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST  VTSS_BIT(1)

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
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG . MACSEC_BYPASS_ENA
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA  VTSS_BIT(8)

/** 
 * \brief
 * MACsec block enable.
 * To enable the MACsec block, also write MACSEC_BYPASS_ENA = 0.
 *
 * \details 
 * 0: MACSEC block is not enabled.
 * 1: MACSEC block is enabled.
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG . MACSEC_ENA
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA  VTSS_BIT(9)

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
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG . MACSEC_SPEED_MODE
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,3)


/** 
 * \brief MACsec control configuration register
 *
 * \details
 * Register: \a MACSEC_EGR:MACSEC_CTL_REGS:MACSEC_CTL_CFG
 */
#define VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG  VTSS_IOREG(0x1f, 1, 0x8801)

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
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG . MAC_CTRL_FRAMES_SRC_PORT
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_MAC_CTRL_FRAMES_SRC_PORT(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_MAC_CTRL_FRAMES_SRC_PORT     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_MAC_CTRL_FRAMES_SRC_PORT(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

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
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG . MAC_DATA_FRAMES_SRC_PORT
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_MAC_DATA_FRAMES_SRC_PORT(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_MAC_DATA_FRAMES_SRC_PORT     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_MAC_DATA_FRAMES_SRC_PORT(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

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
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG . ENA_SEC_FAIL_DEBUG_CODE_IN_FCS
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_CTL_CFG_ENA_SEC_FAIL_DEBUG_CODE_IN_FCS  VTSS_BIT(4)


/** 
 * \brief Error sticky bits of MACsec register
 *
 * \details
 * Register: \a MACSEC_EGR:MACSEC_CTL_REGS:MACSEC_STICKY
 */
#define VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY  VTSS_IOREG(0x1f, 1, 0x8802)

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
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY . PKT64TO128_FIFO_OVERFLOW_STICKY
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_PKT64TO128_FIFO_OVERFLOW_STICKY  VTSS_BIT(5)

/** 
 * \brief
 * Indicates ECC error in SA store RAM while reading SA
 *
 * \details 
 * 0: No ECC error
 * 1: ECC error occurred at least once
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY . SA_STORE_RAM_INTEGRITY_ERROR_STICKY
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_SA_STORE_RAM_INTEGRITY_ERROR_STICKY  VTSS_BIT(6)

/** 
 * \brief
 * Indicates ECC error in STAT RAM while reading statistics
 *
 * \details 
 * 0: No ECC error
 * 1: ECC error occurred at least once
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY . STAT_RAM_INTEGRITY_ERROR_STICKY
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_STAT_RAM_INTEGRITY_ERROR_STICKY  VTSS_BIT(7)


/** 
 * \brief Interrupt mask sticky bits register
 *
 * \details
 * Register: \a MACSEC_EGR:MACSEC_CTL_REGS:MACSEC_STICKY_MASK
 */
#define VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK  VTSS_IOREG(0x1f, 1, 0x8803)

/** 
 * \brief
 * Interrupt mask for PKT64TO128_FIFO_OVERFLOW_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK . PKT64TO128_FIFO_OVERFLOW_STICKY_MASK
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK_PKT64TO128_FIFO_OVERFLOW_STICKY_MASK  VTSS_BIT(5)

/** 
 * \brief
 * Interrupt mask for SA_STORE_RAM_INTEGRITY_ERROR_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK . SA_STORE_RAM_INTEGRITY_ERROR_STICKY_MASK
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK_SA_STORE_RAM_INTEGRITY_ERROR_STICKY_MASK  VTSS_BIT(6)

/** 
 * \brief
 * Interrupt mask for STAT_RAM_INTEGRITY_ERROR_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK . STAT_RAM_INTEGRITY_ERROR_STICKY_MASK
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK_STAT_RAM_INTEGRITY_ERROR_STICKY_MASK  VTSS_BIT(7)


/** 
 * \brief MACsec flow control configuration register
 *
 * \details
 * Register: \a MACSEC_EGR:MACSEC_CTL_REGS:MACSEC_FC_CFG
 */
#define VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG  VTSS_IOREG(0x1f, 1, 0x8804)

/** 
 * \brief
 * Enable flow control towards flow control buffer
 * The following algorithm is used to control flow control backpressure
 * feedback to handle the incoming data rate for MACsec frame expansion.
 * The fill_lvl value at the time of receiving SOF on MACsec IO is taken
 * into account.
 *   if fill_lvl < low tresh [No flow control backpressure feedback]
 *   if low tresh <= fill_lvl < high tresh then trigger flow control
 * backpressure feedback for 24 bytes (3clocks) [Conservative flow control
 * feedback]
 *   if fill_lvl > high tresh then trigger flow control backpressure
 * feedback for 40 bytes (5clocks) 
 * [aggressive flow control feedback]
 * The 24 bytes (conservative feedback) and 40 bytes (aggressive feedback)
 * mention is configurable using FC_LOW_BYTES_VAL and FC_HIGH_BYTES_VAL.
 *
 * \details 
 * 0: Use stalling to handle incoming data rate
 * 1: Use flow control backpressure feedback signal to FCBUF to handle
 * incoming data rate
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG . MACSEC_FCBUF_FC_ENA
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_MACSEC_FCBUF_FC_ENA  VTSS_BIT(0)

/** 
 * \brief
 * Flow control signalling will use the Packet expansion indication from RX
 * port as soon as classification is done.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG . FC_USE_PKT_EXPANSION_INDICATION
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_FC_USE_PKT_EXPANSION_INDICATION  VTSS_BIT(1)

/** 
 * \brief
 * Flow control low threshold value
 *
 * \details 
 * Value in terms of 128-bit words
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG . FC_LOW_THRESH
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_FC_LOW_THRESH(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_FC_LOW_THRESH     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_FC_LOW_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Flow control low threshold value
 *
 * \details 
 * Value in terms of 128-bit words
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG . FC_HIGH_THRESH
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_FC_HIGH_THRESH(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_FC_HIGH_THRESH     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_FC_HIGH_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Flow control low bytes value
 * Specifies conservative flow control feedback in 8 byte steps
 *
 * \details 
 * 0: 0 bytes
 * 1: 8 bytes
 * 2: 16 bytes
 * 3: 24 bytes
 * ...
 * 7: 56 bytes
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG . FC_LOW_BYTES_VAL
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_FC_LOW_BYTES_VAL(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_FC_LOW_BYTES_VAL     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_FC_LOW_BYTES_VAL(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * Flow control low bytes value
 * Specifies aggressive flow control feedback in 8 byte steps
 *
 * \details 
 * 0: 0 bytes
 * 1: 8 bytes
 * 2: 16 bytes
 * 3: 24 bytes
 * ...
 * 7: 56 bytes
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG . FC_HIGH_BYTES_VAL
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_FC_HIGH_BYTES_VAL(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_FC_HIGH_BYTES_VAL     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG_FC_HIGH_BYTES_VAL(x)  VTSS_EXTRACT_BITFIELD(x,16,3)


/** 
 * \brief MACsec 1588 PTP stall configuration register
 *
 * \details
 * Register: \a MACSEC_EGR:MACSEC_CTL_REGS:MACSEC_PTP_STALL_CFG
 */
#define VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_PTP_STALL_CFG  VTSS_IOREG(0x1f, 1, 0x8805)

/** 
 * \brief
 * Enable stalling for 1588 timestamped frames 
 * Stalling timestamped frames to  ensure fixed latency through the MACsec
 * block leads to timestamp accuracy. Disabling stalling leads to timestamp
 * inaccuracy.
 *
 * \details 
 * 0: Stalling not used for PTP timestamp frames
 * 1: Stalling used for PTP timestamp frames
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_PTP_STALL_CFG . STALL_PTP_TS_FRM_ENA
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_PTP_STALL_CFG_STALL_PTP_TS_FRM_ENA  VTSS_BIT(0)

/** 
 * \brief
 * Specifies number of clocks to stall for fixed latency
 *
 * \details 
 * Value in terms of enabled clock cycles
 *
 * Field: VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_PTP_STALL_CFG . PTP_STALL_CLKS_DURATION
 */
#define  VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_PTP_STALL_CFG_PTP_STALL_CLKS_DURATION(x)  VTSS_ENCODE_BITFIELD(x,1,6)
#define  VTSS_M_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_PTP_STALL_CFG_PTP_STALL_CLKS_DURATION     VTSS_ENCODE_BITMASK(1,6)
#define  VTSS_X_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_PTP_STALL_CFG_PTP_STALL_CLKS_DURATION(x)  VTSS_EXTRACT_BITFIELD(x,1,6)


/** 
 * \brief MACsec IP debug register read/write address.
 *
 * \details
 * Register: \a MACSEC_EGR:MACSEC_CTL_REGS:MACSEC_DEBUG_REG_ADDR
 */
#define VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_DEBUG_REG_ADDR  VTSS_IOREG(0x1f, 1, 0x8806)


/** 
 * \brief MACsec IP debug register read/write Data
 *
 * \details
 * Register: \a MACSEC_EGR:MACSEC_CTL_REGS:MACSEC_DEBUG_REG_DATA
 */
#define VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_DEBUG_REG_DATA  VTSS_IOREG(0x1f, 1, 0x8807)

/**
 * Register Group: \a MACSEC_EGR:CAPT_DEBUG_REGS
 *
 * Capture debug Fifo control / status registers
 */


/** 
 * \brief Capture debug data register.
 *
 * \details
 * Register: \a MACSEC_EGR:CAPT_DEBUG_REGS:CAPT_DEBUG_DATA
 *
 * @param ri Register: CAPT_DEBUG_DATA, 0-127
 */
#define VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_DATA(ri)  VTSS_IOREG(0x1f, 1, 0x8900 | (ri))


/** 
 * \brief Capture debug control register
 *
 * \details
 * Register: \a MACSEC_EGR:CAPT_DEBUG_REGS:CAPT_DEBUG_CTRL
 */
#define VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_CTRL  VTSS_IOREG(0x1f, 1, 0x8980)

/** 
 * \brief
 * Selects the side the capture debug memory is capturing packets from, 1b
 * = ingress, 0b = egress. This bit cannot be changed while the enable bit
 * in the CAPT_DEBUG_TRIGGER register is 1b.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_CTRL . SIDE
 */
#define  VTSS_F_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_CTRL_SIDE  VTSS_BIT(0)

/** 
 * \brief
 * Controls the maximum number of 64 bits words captured for a packet, must
 * be in range 2-63 words (16-504 Bytes). This field cannot be changed
 * while the enable bit in the CAPT_DEBUG_TRIGGER register is 1b.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_CTRL . MAX_PKT_SIZE
 */
#define  VTSS_F_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_CTRL_MAX_PKT_SIZE(x)  VTSS_ENCODE_BITFIELD(x,1,6)
#define  VTSS_M_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_CTRL_MAX_PKT_SIZE     VTSS_ENCODE_BITMASK(1,6)
#define  VTSS_X_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_CTRL_MAX_PKT_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,1,6)


/** 
 * \brief Capture debug status register
 *
 * \details
 * Register: \a MACSEC_EGR:CAPT_DEBUG_REGS:CAPT_DEBUG_STATUS
 */
#define VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS  VTSS_IOREG(0x1f, 1, 0x8981)

/** 
 * \brief
 * Read-only, 1b indicates the memory is completely filled, will be reset
 * to 0b when the enable bit in the CAPT_DEBUG_TRIGGER register is written
 * from 0b to 1b.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS . FULL
 */
#define  VTSS_F_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS_FULL  VTSS_BIT(0)

/** 
 * \brief
 * Read-only, indexes the next 64 bits word to be written in the memory
 * (and thus indicates the number of words already written), will be reset
 * to zero when the enable bit in the CAPT_DEBUG_TRIGGER register is
 * written from 0b to 1b.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS . WR_PTR
 */
#define  VTSS_F_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS_WR_PTR(x)  VTSS_ENCODE_BITFIELD(x,1,6)
#define  VTSS_M_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS_WR_PTR     VTSS_ENCODE_BITMASK(1,6)
#define  VTSS_X_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS_WR_PTR(x)  VTSS_EXTRACT_BITFIELD(x,1,6)

/** 
 * \brief
 * Read-only, indicates the number of packets captured in the memory, will
 * be reset to zero when the enable bit in the CAPT_DEBUG_TRIGGER register
 * is written from 0b to 1b.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS . PKT_COUNT
 */
#define  VTSS_F_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS_PKT_COUNT(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS_PKT_COUNT     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS_PKT_COUNT(x)  VTSS_EXTRACT_BITFIELD(x,8,5)


/** 
 * \brief Capture debug trigger SA register
 *
 * \details
 * Register: \a MACSEC_EGR:CAPT_DEBUG_REGS:CAPT_DEBUG_TRIGGER_SA1
 */
#define VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA1  VTSS_IOREG(0x1f, 1, 0x8982)


/** 
 * \brief Capture debug trigger SA register
 *
 * \details
 * Register: \a MACSEC_EGR:CAPT_DEBUG_REGS:CAPT_DEBUG_TRIGGER_SA2
 */
#define VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA2  VTSS_IOREG(0x1f, 1, 0x8983)


/** 
 * \brief Capture debug trigger enable register.
 *
 * \details
 * Register: \a MACSEC_EGR:CAPT_DEBUG_REGS:CAPT_DEBUG_TRIGGER
 */
#define VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER  VTSS_IOREG(0x1f, 1, 0x8984)

/** 
 * \brief
 * 1b = Enable the capture debug memory functionality, locking the side and
 * max_pkt_size fields in the CAPT_DEBUG_CTRL register against changes and
 * disabling access to the CAPT_DEBUG_DATA area. Setting this bit from 0b
 * to 1b resets both the write_pointer and packet_count fields in the
 * CAPT_DEBUG_STATUS register to zero.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER . ENABLE
 */
#define  VTSS_F_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_ENABLE  VTSS_BIT(0)

/**
 * Register Group: \a MACSEC_EGR:XFORM_RECORD_REGS
 *
 * Transform context records
 */


/** 
 * \brief Transform record data 0
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA0
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA0(ri)  VTSS_IOREG(0x1f, 1, 0x8000 | (ri * 32))


/** 
 * \brief Transform record data 1
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA1
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA1(ri)  VTSS_IOREG(0x1f, 1, 0x8001 | (ri * 32))


/** 
 * \brief Transform record data 2
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA2
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA2(ri)  VTSS_IOREG(0x1f, 1, 0x8002 | (ri * 32))


/** 
 * \brief Transform record data 3
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA3
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA3(ri)  VTSS_IOREG(0x1f, 1, 0x8003 | (ri * 32))


/** 
 * \brief Transform record data 4
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA4
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA4(ri)  VTSS_IOREG(0x1f, 1, 0x8004 | (ri * 32))


/** 
 * \brief Transform record data 5
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA5
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA5(ri)  VTSS_IOREG(0x1f, 1, 0x8005 | (ri * 32))


/** 
 * \brief Transform record data 6
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA6
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA6(ri)  VTSS_IOREG(0x1f, 1, 0x8006 | (ri * 32))


/** 
 * \brief Transform record data 7
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA7
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA7(ri)  VTSS_IOREG(0x1f, 1, 0x8007 | (ri * 32))


/** 
 * \brief Transform record data 8
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA8
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA8(ri)  VTSS_IOREG(0x1f, 1, 0x8008 | (ri * 32))


/** 
 * \brief Transform record data 9
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA9
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA9(ri)  VTSS_IOREG(0x1f, 1, 0x8009 | (ri * 32))


/** 
 * \brief Transform record data 10
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA10
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA10(ri)  VTSS_IOREG(0x1f, 1, 0x800a | (ri * 32))


/** 
 * \brief Transform record data 11
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA11
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA11(ri)  VTSS_IOREG(0x1f, 1, 0x800b | (ri * 32))


/** 
 * \brief Transform record data 12
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA12
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA12(ri)  VTSS_IOREG(0x1f, 1, 0x800c | (ri * 32))


/** 
 * \brief Transform record data 13
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA13
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA13(ri)  VTSS_IOREG(0x1f, 1, 0x800d | (ri * 32))


/** 
 * \brief Transform record data 14
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA14
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA14(ri)  VTSS_IOREG(0x1f, 1, 0x800e | (ri * 32))


/** 
 * \brief Transform record data 15
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA15
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA15(ri)  VTSS_IOREG(0x1f, 1, 0x800f | (ri * 32))


/** 
 * \brief Transform record data 16
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA16
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA16(ri)  VTSS_IOREG(0x1f, 1, 0x8010 | (ri * 32))


/** 
 * \brief Transform record data 17
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA17
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA17(ri)  VTSS_IOREG(0x1f, 1, 0x8011 | (ri * 32))


/** 
 * \brief Transform record data 18
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA18
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA18(ri)  VTSS_IOREG(0x1f, 1, 0x8012 | (ri * 32))


/** 
 * \brief Transform record data 19
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA19
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA19(ri)  VTSS_IOREG(0x1f, 1, 0x8013 | (ri * 32))


/** 
 * \brief Transform record data 20
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA20
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA20(ri)  VTSS_IOREG(0x1f, 1, 0x8014 | (ri * 32))


/** 
 * \brief Transform record data 21
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA21
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA21(ri)  VTSS_IOREG(0x1f, 1, 0x8015 | (ri * 32))


/** 
 * \brief Transform record data 22
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA22
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA22(ri)  VTSS_IOREG(0x1f, 1, 0x8016 | (ri * 32))


/** 
 * \brief Transform record data 23
 *
 * \details
 * Register: \a MACSEC_EGR:XFORM_RECORD_REGS:XFORM_REC_DATA23
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA23(ri)  VTSS_IOREG(0x1f, 1, 0x8017 | (ri * 32))

/**
 * Register Group: \a MACSEC_EGR:SA_MATCH_PARAMS
 *
 * Programmable Secure Association compare parameters
 */


/** 
 * \brief Secure Association match MAC_SA & Ether-type compare registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_PARAMS:SAM_MAC_SA_MATCH_LO
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_LO(ri)  VTSS_IOREG(0x1f, 1, 0x9000 | (ri * 16))


/** 
 * \brief Secure Association match MAC_SA & Ether-type compare registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_PARAMS:SAM_MAC_SA_MATCH_HI
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI(ri)  VTSS_IOREG(0x1f, 1, 0x9001 | (ri * 16))

/** 
 * \brief
 * Bits [7:0] :: mac_sa_match[15:8] :: Bits [15:8] of one MAC_SA compare
 * value (compare-enabled per byte) 
 * Bits [15:8] :: mac_sa_match[7:0] :: Bits [7:0] of one MAC_SA compare
 * value (compare-enabled per byte), last byte received
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI . MAC_SA_MATCH_15_TO_0
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_MAC_SA_MATCH_15_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_MAC_SA_MATCH_15_TO_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_MAC_SA_MATCH_15_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Parsed Ether-type compare value (stored byte swapped, for instance
 * MACsec tag value 0x88E5 
 * would be stored as 0xE588 in this field) 
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI . ETHER_TYPE
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_ETHER_TYPE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_ETHER_TYPE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_ETHER_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Secure Association match MAC_DA & VLAN ID compare registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_PARAMS:SAM_MAC_DA_MATCH_LO
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_LO(ri)  VTSS_IOREG(0x1f, 1, 0x9002 | (ri * 16))


/** 
 * \brief Secure Association match MAC_DA & VLAN ID compare registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_PARAMS:SAM_MAC_DA_MATCH_HI
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI(ri)  VTSS_IOREG(0x1f, 1, 0x9003 | (ri * 16))

/** 
 * \brief
 * Bits [7:0] :: mac_da_match[15:8] :: Bits [15:8] of one MAC_DA compare
 * value (compare-enabled per byte) 
 * Bits [15:8] :: mac_da_match[7:0] :: Bits [7:0] of one MAC_DA compare
 * value (compare-enabled per byte), last byte received
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI . MAC_DA_MATCH_15_TO_0
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_MAC_DA_MATCH_15_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_MAC_DA_MATCH_15_TO_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_MAC_DA_MATCH_15_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Parsed VLAN ID compare value
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI . VLAN_ID
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_VLAN_ID(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_VLAN_ID     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_VLAN_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,12)


/** 
 * \brief Secure Association match miscellaneous compare registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_PARAMS:SAM_MISC_MATCH
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH(ri)  VTSS_IOREG(0x1f, 1, 0x9004 | (ri * 16))

/** 
 * \brief
 * Parsed VLAN valid flag compare value.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . VLAN_VALID
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_VLAN_VALID  VTSS_BIT(0)

/** 
 * \brief
 * Parsed Q-in-Q found flag compare value.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . QINQ_FOUND
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_QINQ_FOUND  VTSS_BIT(1)

/** 
 * \brief
 * Parsed STAG valid flag compare value.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . STAG_VALID
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_STAG_VALID  VTSS_BIT(2)

/** 
 * \brief
 * Parsed QTAG valid flag compare value.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . QTAG_VALID
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_QTAG_VALID  VTSS_BIT(3)

/** 
 * \brief
 * Parsed VLAN User Priority compare value.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . VLAN_UP
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_VLAN_UP(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_VLAN_UP     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_VLAN_UP(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * Control packet (as pre-decoded) compare value.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . CONTROL_PACKET
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_CONTROL_PACKET  VTSS_BIT(7)

/** 
 * \brief
 * Untagged packet match enable.
 *
 * \details 
 * 1b: Allow packets without a MACsec tag to match (MACsec tag
 * classification logic output).
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . UNTAGGED
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_UNTAGGED  VTSS_BIT(8)

/** 
 * \brief
 * Tagged packet match enable.
 *
 * \details 
 * 1b: Allow packets with a standard and valid MACsec tag to match (MACsec
 * tag classification logic output).
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . TAGGED
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_TAGGED  VTSS_BIT(9)

/** 
 * \brief
 * Invalid tag match enable.
 *
 * \details 
 * 1b: Allow packets with an invalid MACsec tag to match (MACsec tag
 * classification logic output).
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . BAD_TAG
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_BAD_TAG  VTSS_BIT(10)

/** 
 * \brief
 * Kay handling tag match enable.
 *
 * \details 
 * 1b: Allow packets with a MACsec tag indicating Kay handling to be done
 * to match (MACsec tag classification logic output).
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . KAY_TAG
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_KAY_TAG  VTSS_BIT(11)

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
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . SOURCE_PORT
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_SOURCE_PORT(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_SOURCE_PORT     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_SOURCE_PORT(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

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
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH . MATCH_PRIORITY
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_MATCH_PRIORITY(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_MATCH_PRIORITY     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_MATCH_PRIORITY(x)  VTSS_EXTRACT_BITFIELD(x,16,4)


/** 
 * \brief Reserved register
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_PARAMS:SAM_SCI_MATCH_LO_RESERVED
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_SCI_MATCH_LO_RESERVED(ri)  VTSS_IOREG(0x1f, 1, 0x9005 | (ri * 16))


/** 
 * \brief Reserved register
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_PARAMS:SAM_SCI_MATCH_HI_RESERVED
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_SCI_MATCH_HI_RESERVED(ri)  VTSS_IOREG(0x1f, 1, 0x9006 | (ri * 16))


/** 
 * \brief Secure Association match mask registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_PARAMS:SAM_MASK
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK(ri)  VTSS_IOREG(0x1f, 1, 0x9007 | (ri * 16))

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
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK . MAC_SA_MASK
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_MAC_SA_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_MAC_SA_MASK     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_MAC_SA_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

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
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK . MAC_DA_MASK
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_MAC_DA_MASK(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_MAC_DA_MASK     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_MAC_DA_MASK(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \details 
 * 1b: Enable parsed Ether-type field compare with ether_type field in the
 * SAM_MAC_DA_MATCH_LO register
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK . MAC_ETYPE_MASK
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_MAC_ETYPE_MASK  VTSS_BIT(12)

/** 
 * \details 
 * 1b: Enable parsed VLAN valid flag compare with vlan_valid bit in the
 * SAM_MISC_MATCH register 
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK . VLAN_VLD_MASK
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_VLAN_VLD_MASK  VTSS_BIT(13)

/** 
 * \details 
 * 1b: Enable parsed Q-in-Q found flag compare with qinq_found field in the
 * SAM_MISC_MATCH register 
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK . QINQ_FOUND_MASK
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_QINQ_FOUND_MASK  VTSS_BIT(14)

/** 
 * \details 
 * 1b: Enable parsed STAG valid flag compare with stag_valid bit in the
 * SAM_MISC_MATCH register
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK . STAG_VLD_MASK
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_STAG_VLD_MASK  VTSS_BIT(15)

/** 
 * \details 
 * 1b: Enable parsed QTAG valid flag compare with qtag_valid bit in the
 * SAM_MISC_MATCH register 
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK . QTAG_VLD_MASK
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_QTAG_VLD_MASK  VTSS_BIT(16)

/** 
 * \details 
 * 1b: Enable parsed VLAN user priority value compare with vlan_up field in
 * the SAM_MISC_MATCH register 
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK . VLAN_UP_MASK
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_VLAN_UP_MASK  VTSS_BIT(17)

/** 
 * \details 
 * 1b: Enable parsed VLAN ID value compare with vlan_id field in the
 * SAM_MAC_DA_MATCH_HI register
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK . VLAN_ID_MASK
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_VLAN_ID_MASK  VTSS_BIT(18)

/** 
 * \details 
 * 1b: Enable source port compare with source_port field in the
 * SAM_MISC_MATCH register
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK . SOURCE_PORT_MASK
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_SOURCE_PORT_MASK  VTSS_BIT(19)

/** 
 * \details 
 * 1b: Enable control packet status compare with control_packet bit in the
 * SAM_MISC_MATCH register 
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK . CTL_PACKET_MASK
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_CTL_PACKET_MASK  VTSS_BIT(20)

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
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK . VLAN_UP_INNER_MASK
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_VLAN_UP_INNER_MASK  VTSS_BIT(21)

/** 
 * \brief
 * The VLAN ID inner mask comparison needs QinQ found flag comparison
 * enabled
 *
 * \details 
 * 1b: Enable parsed inner VLAN ID value compare with vlan_up_inner field
 * in the SAM_EXT_MATCH_x register
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK . VLAN_ID_INNER_MASK
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK_VLAN_ID_INNER_MASK  VTSS_BIT(22)


/** 
 * \brief Secure Association match extended.
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_PARAMS:SAM_EXT_MATCH
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_EXT_MATCH(ri)  VTSS_IOREG(0x1f, 1, 0x9008 | (ri * 16))

/** 
 * \brief
 * Parsed inner VLAN ID compare value
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_EXT_MATCH . VLAN_ID_INNER
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_ID_INNER(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_ID_INNER     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_ID_INNER(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/** 
 * \brief
 * Parsed inner VLAN Up compare value 
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_EXT_MATCH . VLAN_UP_INNER
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_UP_INNER(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_UP_INNER     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_UP_INNER(x)  VTSS_EXTRACT_BITFIELD(x,12,3)


/** 
 * \brief Secure Association header bypass match register
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_PARAMS:SAM_HDR_BYPASS_MATCH1
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MATCH1(ri)  VTSS_IOREG(0x1f, 1, 0x9009 | (ri * 16))


/** 
 * \brief Secure Association header bypass match register
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_PARAMS:SAM_HDR_BYPASS_MATCH2
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MATCH2(ri)  VTSS_IOREG(0x1f, 1, 0x900a | (ri * 16))


/** 
 * \brief Secure Association match header bypass mask register
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_PARAMS:SAM_HDR_BYPASS_MASK1
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK1(ri)  VTSS_IOREG(0x1f, 1, 0x900b | (ri * 16))


/** 
 * \brief Secure Association match header bypass mask register
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_PARAMS:SAM_HDR_BYPASS_MASK2
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK2(ri)  VTSS_IOREG(0x1f, 1, 0x900c | (ri * 16))

/**
 * Register Group: \a MACSEC_EGR:SA_MATCH_CTL_PARAMS
 *
 * Programmable Secure Association compare parameters
 */


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_ENABLE1
 */
#define VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE1  VTSS_IOREG(0x1f, 1, 0x9800)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_ENABLE2
 */
#define VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE2  VTSS_IOREG(0x1f, 1, 0x9801)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_TOGGLE1
 */
#define VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE1  VTSS_IOREG(0x1f, 1, 0x9804)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_TOGGLE2
 */
#define VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE2  VTSS_IOREG(0x1f, 1, 0x9805)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_SET1
 */
#define VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_SET1  VTSS_IOREG(0x1f, 1, 0x9808)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_SET2
 */
#define VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_SET2  VTSS_IOREG(0x1f, 1, 0x9809)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_CLEAR1
 */
#define VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_CLEAR1  VTSS_IOREG(0x1f, 1, 0x980c)


/** 
 * \brief Secure Association match entry enable control registers
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_CTL_PARAMS:SAM_ENTRY_CLEAR2
 */
#define VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_CLEAR2  VTSS_IOREG(0x1f, 1, 0x980d)


/** 
 * \brief Secure Association match in flights register
 *
 * \details
 * This register provides the possibility to track the number of packets in
 * the pipeline for hardware/software synchronization purposes.
 *
 * Register: \a MACSEC_EGR:SA_MATCH_CTL_PARAMS:SAM_IN_FLIGHT
 */
#define VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT  VTSS_IOREG(0x1f, 1, 0x9810)

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
 * Field: VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT . UNSAFE
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_UNSAFE(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_UNSAFE     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_UNSAFE(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Inflight
 * Number of packets in the MACsec IP pipeline. This counter increments on
 * every packet entering the pipeline for classification and decrements on
 * every packet that has been handled by the statistics counters module,
 * including packets that are officially dropped.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT . IN_FLIGHT
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_IN_FLIGHT(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_IN_FLIGHT     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_IN_FLIGHT(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Load unsafe
 * Debug functionality: 1b = Load unsafe field in this register with
 * contents of in_flight field of that 
 * same register to start counting down. Just like when disabling a SA
 * match entry, writing 0b has no effect.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT . LOAD_UNSAFE
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_LOAD_UNSAFE  VTSS_BIT(31)

/**
 * Register Group: \a MACSEC_EGR:SA_MATCH_FLOW_CONTROL_PARAMS_EGR
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
 * Register: \a MACSEC_EGR:SA_MATCH_FLOW_CONTROL_PARAMS_EGR:SAM_FLOW_CTRL_EGR
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR(ri)  VTSS_IOREG(0x1f, 1, 0x9c00 | (ri))

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
 * Field: VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR . FLOW_TYPE
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_FLOW_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_FLOW_TYPE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_FLOW_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

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
 * Field: VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR . DEST_PORT
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_DEST_PORT     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Enables basic crypt-authenticate mode. Must be set to 0b for all non
 * crypt-authenticate actions.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR . FLOW_CRYPT_AUTH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_FLOW_CRYPT_AUTH  VTSS_BIT(5)

/** 
 * \brief
 * Defines the way the drop operation is performed.
 * If drop_action 10b (internal drop) is selected in static_bypass mode
 * (see section 6.2.6), the drop 
 * operation is forced to CRC corruption (mode 00b) the actual field value
 * is not influenced 
 * here.
 *
 * \details 
 * 00b: Bypass with CRC corruption signaling
 * 01b: Bypass with bad packet indicator
 * 10b: Internal drop by crypto-core (packet is not seen outside)
 * 11b: Do not drop (for debugging only)
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR . DROP_ACTION
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_DROP_ACTION     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * This function is used for MACsec egress processing only (flow_type =
 * 11b) 
 *
 * \details 
 * 1b: Enable frame protection
 * 0b: Bypass frame through crypto-core 
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR . PROTECT_FRAME
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_PROTECT_FRAME  VTSS_BIT(16)

/** 
 * \details 
 * 1b: MACsec Secure Association in use for the looked-up Secure
 * Association
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR . SA_IN_USE
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_SA_IN_USE  VTSS_BIT(17)

/** 
 * \brief
 * This function is used for MACsec egress processing only (flow_type =
 * 11b)
 *
 * \details 
 * 1b: Include explicit secure channel identifier in packet
 * 0b: Use implicit secure channel identifier (not transmitted in packet) 
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR . INCLUDE_SCI
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_INCLUDE_SCI  VTSS_BIT(18)

/** 
 * \brief
 * This function is used for MACsec egress processing only (flow_type =
 * 11b).

 *
 * \details 
 * 1b: Set end station bit in tag control information field
 * 0b: Clear end station bit in tag control information field
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR . USE_ES
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_USE_ES  VTSS_BIT(19)

/** 
 * \brief
 * This function is used for MACsec egress processing only (flow_type =
 * 11b) 

 *
 * \details 
 * 1b: Set single copy broadcast bit in tag control information field
 * 0b: Clear single copy broadcast bit in tag control information field
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR . USE_SCB
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_USE_SCB  VTSS_BIT(20)

/** 
 * \brief
 * The number of 4-byte tags (allowed values are 0, 1 and 2) that are
 * bypassed without authentication and encryption for packet going to be
 * MACsec protected. Value 0 corresponds to the regular MACsec processing.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR . TAG_BYPASS_SIZE
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_TAG_BYPASS_SIZE(x)  VTSS_ENCODE_BITFIELD(x,21,2)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_TAG_BYPASS_SIZE     VTSS_ENCODE_BITMASK(21,2)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_TAG_BYPASS_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,21,2)

/** 
 * \brief
 * The number of bytes (in the range of 0-64) that are be authenticated but
 * not encrypted following the SecTag in the encrypted MACsec packet. 
 *
 * \details 
 * 65-127: Reserved (do not use)
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR . CONFIDENTIALITY_OFFSET
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_CONFIDENTIALITY_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_CONFIDENTIALITY_OFFSET     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_CONFIDENTIALITY_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/** 
 * \brief
 * This function is used for MACsec egress processing only (flow_type =
 * 11b) 
 *
 * \details 
 * 1b: Enable confidentiality protection
 * 0b: Disable confidentiality protection 
 *
 * Field: VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR . CONF_PROTECT
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_CONF_PROTECT  VTSS_BIT(31)

/**
 * Register Group: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS
 *
 * Control packet classification parameters
 */


/** 
 * \brief Control packet individual MAC_DA and Ethertype match compare register
 *
 * \details
 * Register: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS:CP_MAC_DA_MATCH
 *
 * @param ri Register: CP_MAC_DA_MATCH, 0-9
 */
#define VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_MATCH(ri)  VTSS_IOREG(0x1f, 1, 0x9e00 | (ri * 2))


/** 
 * \brief Control packet individual MAC_DA and Ethertype match compare register
 *
 * \details
 * Register: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS:CP_MAC_DA_ET_MATCH
 *
 * @param ri Register: CP_MAC_DA_ET_MATCH, 0-9
 */
#define VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH(ri)  VTSS_IOREG(0x1f, 1, 0x9e01 | (ri * 2))

/** 
 * \brief
 * Bits [7:0] :: mac_da_match[15:8] :: Bits [15:8] of one MAC_DA compare
 * value 
 * Bits [15:8] :: mac_da_match[7:0] :: Bits [7:0] of one MAC_DA compare
 * value, last byte received
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH . MAC_DA_MATCH_15_TO_0
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_TO_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * One Ethertype compare value (for the Ethertype field directly following
 * the MAC_SA), stored byte swapped, for instance MACsec tag value 0x88E5
 * is stored as 0xE588 in this field.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH . ETHER_TYPE_MATCH
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Ethertype match register
 *
 * \details
 * Covers the individual Ethertype compare values from 10 to 17.
 *
 * Register: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS:CP_MAC_ET_MATCH
 *
 * @param ri Register: CP_MAC_ET_MATCH, 0-7
 */
#define VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_ET_MATCH(ri)  VTSS_IOREG(0x1f, 1, 0x9e14 | (ri))

/** 
 * \brief
 * One Ethertype compare value (for the Ethertype field directly following
 * the MAC_SA), stored 
 * byte swapped, for instance MACsec tag value 0x88E5 is stored as 0xE588
 * in this field
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_ET_MATCH . ETHER_TYPE
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_ET_MATCH_ETHER_TYPE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_ET_MATCH_ETHER_TYPE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_ET_MATCH_ETHER_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * Register Group: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS2
 *
 * Control packet classification parameters
 */


/** 
 * \brief Control packet MAC_DA range check compare register
 *
 * \details
 * Register: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_START_LO
 */
#define VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_START_LO  VTSS_IOREG(0x1f, 1, 0x9e20)


/** 
 * \brief Control packet MAC_DA range check compare registers
 *
 * \details
 * Register: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_START_HI
 */
#define VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_START_HI  VTSS_IOREG(0x1f, 1, 0x9e21)

/** 
 * \brief
 * Bits [7:0] = mac_da_start[15:8]
 * Bits [15:8] of one MAC_DA range compare value.
 * Bits [15:8] = mac_da_start[7:0]
 * Bits [7:0] of one MAC_DA range compare value (last byte received).
 * Total match is when start value <= MAC_DA <= end value.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_START_HI . MAC_DA_START_15_TO_0
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_START_HI_MAC_DA_START_15_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_START_HI_MAC_DA_START_15_TO_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_START_HI_MAC_DA_START_15_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Control packet MAC_DA range check compare register
 *
 * \details
 * Register: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_END_LO
 */
#define VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_END_LO  VTSS_IOREG(0x1f, 1, 0x9e22)


/** 
 * \brief Control packet MAC_DA range check compare register
 *
 * \details
 * Register: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_END_HI
 */
#define VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_END_HI  VTSS_IOREG(0x1f, 1, 0x9e23)

/** 
 * \brief
 * Bits [7:0] = mac_da_end[15:8]
 * Bits [15:8] of one MAC_DA range compare value.
 * Bits [15:8] = mac_da_end[7:0]
 * Bits [7:0] of one MAC_DA range compare value (last byte received).
 * Total match is when start value <= MAC_DA <= end value.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_END_HI . MAC_DA_END_15_TO_0
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_END_HI_MAC_DA_END_15_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_END_HI_MAC_DA_END_15_TO_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_END_HI_MAC_DA_END_15_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Control packet MAC_DA constant 01_80_C2_00_00_0? compare register
 *
 * \details
 * Register: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_44_BITS_LO
 */
#define VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_LO  VTSS_IOREG(0x1f, 1, 0x9e24)


/** 
 * \brief Control packet MAC_DA constant 01_80_C2_00_00_0? compare register
 *
 * \details
 * Register: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_44_BITS_HI
 */
#define VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI  VTSS_IOREG(0x1f, 1, 0x9e25)

/** 
 * \brief
 * Bits [15:8] of MAC_DA 44 bits constant 01_80_C2_00_00_0? compare value
 * (byte swapped) reset value matches the given constant. 
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI . MAC_DA_44_BITS_15_TO_8
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI_MAC_DA_44_BITS_15_TO_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI_MAC_DA_44_BITS_15_TO_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI_MAC_DA_44_BITS_15_TO_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Bits [7:4] of MAC_DA 44 bits constant 01_80_C2_00_00_0? compare value
 * (byte swapped, last byte received) reset value matches the given
 * constant.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI . MAC_DA_44_BITS_7_TO_4
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI_MAC_DA_44_BITS_7_TO_4(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI_MAC_DA_44_BITS_7_TO_4     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_44_BITS_HI_MAC_DA_44_BITS_7_TO_4(x)  VTSS_EXTRACT_BITFIELD(x,12,4)


/** 
 * \brief Control packet MAC_DA constant 01_00_0C_CC_CC_CC compare register
 *
 * \details
 * Register: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_48_BITS_LO
 */
#define VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_48_BITS_LO  VTSS_IOREG(0x1f, 1, 0x9e26)


/** 
 * \brief Control packet MAC_DA constant 01_00_0C_CC_CC_CC compare register
 *
 * \details
 * Register: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS2:CP_MAC_DA_48_BITS_HI
 */
#define VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_48_BITS_HI  VTSS_IOREG(0x1f, 1, 0x9e27)

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
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_48_BITS_HI . MAC_DA_48_BITS_15_TO_0
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_48_BITS_HI_MAC_DA_48_BITS_15_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_48_BITS_HI_MAC_DA_48_BITS_15_TO_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MAC_DA_48_BITS_HI_MAC_DA_48_BITS_15_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Control packet match mode register
 *
 * \details
 * Register: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS2:CP_MATCH_MODE
 */
#define VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE  VTSS_IOREG(0x1f, 1, 0x9e3e)

/** 
 * \brief
 * Select which Ether-type to compare with 16 bit value in
 * CP_MAC_DA_ET_MATCH_x register
 *
 * \details 
 * 0b: Packet Ethertype (the first Ethertype in the packet) 
 * 1b: Parsed Ethertype (the parsed Ethertype as detected by algorithm)
 *
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE . ETYPE_SEL_9_TO_0
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_9_TO_0(x)  VTSS_ENCODE_BITFIELD(x,8,10)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_9_TO_0     VTSS_ENCODE_BITMASK(8,10)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_9_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,8,10)

/** 
 * \brief
 * Functionality equivalent to bits [17:8], but applicable for 16 bit value
 * in CP_MAC_ET_MATCH_10 to CP_MAC_ET_MATCH_17 registers respectively.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE . ETYPE_SEL_17_TO_10
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_17_TO_10(x)  VTSS_ENCODE_BITFIELD(x,21,8)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_17_TO_10     VTSS_ENCODE_BITMASK(21,8)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_17_TO_10(x)  VTSS_EXTRACT_BITFIELD(x,21,8)


/** 
 * \brief Control packet match enable register
 *
 * \details
 * Register: \a MACSEC_EGR:CTL_PACKET_CLASS_PARAMS2:CP_MATCH_ENABLE
 */
#define VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE  VTSS_IOREG(0x1f, 1, 0x9e3f)

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
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . MAC_DA_ENABLE_7_TO_0
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_MAC_DA_ENABLE_7_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_MAC_DA_ENABLE_7_TO_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_MAC_DA_ENABLE_7_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

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
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . ETYPE_ENABLE_7_TO_0
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_7_TO_0(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_7_TO_0     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_7_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

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
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . COMB_ENABLE_9_TO_8
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_COMB_ENABLE_9_TO_8(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_COMB_ENABLE_9_TO_8     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_COMB_ENABLE_9_TO_8(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Match is found when START = MAC_DA = END
 *
 * \details 
 * 1b: Enable MAC_DA range compare with lower and upper bound values in
 * CP_MAC_DA_START_LO/HI and CP_MAC_DA_END_LO/HI registers
 *
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . RANGE_ENABLE
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_RANGE_ENABLE  VTSS_BIT(18)

/** 
 * \brief
 * The lowest 4 bits of MAC_DA are not compared
 *
 * \details 
 * 1b: Enable MAC_DA compare against programmable 44 bits constant.
 * 01_80_C2_00_00_0 in CP_MAC_DA_44_BITS_LO/HI registers
 *
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . CONST_44_ENABLE
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_CONST_44_ENABLE  VTSS_BIT(19)

/** 
 * \details 
 * 1b: Enable MAC_DA compare against programmable 48 bits constant.
 * 01_00_0C_CC_CC_CC in CP_MAC_DA_48_BITS_LO/HI registers
 *
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . CONST_48_ENABLE
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_CONST_48_ENABLE  VTSS_BIT(20)

/** 
 * \details 
 * 1b: Enable Ethertype compare with 16 bits value in CP_MAC_ET_MATCH_x
 * register
 *
 * Field: VTSS_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE . ETYPE_ENABLE_17_TO_10
 */
#define  VTSS_F_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_17_TO_10(x)  VTSS_ENCODE_BITFIELD(x,21,8)
#define  VTSS_M_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_17_TO_10     VTSS_ENCODE_BITMASK(21,8)
#define  VTSS_X_MACSEC_EGR_CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_17_TO_10(x)  VTSS_EXTRACT_BITFIELD(x,21,8)

/**
 * Register Group: \a MACSEC_EGR:FRAME_MATCHING_HANDLING_CTRL
 *
 * Frame matching and handling control registers
 */


/** 
 * \brief VLAN tag detection
 *
 * \details
 * Register: \a MACSEC_EGR:FRAME_MATCHING_HANDLING_CTRL:SAM_CP_TAG
 */
#define VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG  VTSS_IOREG(0x1f, 1, 0x9e40)

/** 
 * \brief
 * Translate one priority value into another using map table
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . MAP_TBL
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_MAP_TBL(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_MAP_TBL     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_MAP_TBL(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

/** 
 * \brief
 * Default user priority
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . DEF_UP
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_DEF_UP(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_DEF_UP     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_DEF_UP(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/** 
 * \brief
 * STAG user priority enable
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . STAG_UP_EN
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_STAG_UP_EN  VTSS_BIT(27)

/** 
 * \brief
 * QTAG user priority map enable
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . QTAG_UP_EN
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_QTAG_UP_EN  VTSS_BIT(28)

/** 
 * \brief
 * Parse Q-in-Q enable
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . PARSE_QINQ
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_PARSE_QINQ  VTSS_BIT(29)

/** 
 * \brief
 * Parse STAG enable
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . PARSE_STAG
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_PARSE_STAG  VTSS_BIT(30)

/** 
 * \brief
 * Parse QTAG enable
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG . PARSE_QTAG
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_PARSE_QTAG  VTSS_BIT(31)


/** 
 * \brief VLAN tag detection 
 *
 * \details
 * Register: \a MACSEC_EGR:FRAME_MATCHING_HANDLING_CTRL:SAM_PP_TAGS
 */
#define VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS  VTSS_IOREG(0x1f, 1, 0x9e41)

/** 
 * \brief
 * Ethertype value used for 802.1Q tag type comparison in the additional
 * fields parsing algorithm. As this is the VLAN tag, the default value is
 * 0x8100 (stored byte swapped as value 0x0081). 
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS . QTAG_VALUE
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS_QTAG_VALUE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS_QTAG_VALUE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS_QTAG_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Ethertype value used for 802.1s tag type comparison in the additional
 * fields parsing algorithm. The default value is 0x88A8 (stored byte
 * swapped as value 0xA888) to allow stacked VLAN tags, but it can be
 * re-programmed to another value if user-specific VLAN tags are used.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS . STAG_VALUE
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS_STAG_VALUE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS_STAG_VALUE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS_STAG_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief VLAN tag detection 
 *
 * \details
 * Register: \a MACSEC_EGR:FRAME_MATCHING_HANDLING_CTRL:SAM_PP_TAGS2
 */
#define VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2  VTSS_IOREG(0x1f, 1, 0x9e42)

/** 
 * \brief
 * Secondary Ethertype value used for 802.1s-tag type comparison in the
 * additional fields parsing algorithm. The default value is 0x9100 (stored
 * byte swapped as value 0x0091). 
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2 . STAG_VALUE2
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2_STAG_VALUE2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2_STAG_VALUE2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2_STAG_VALUE2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Tertiary Ethertype value used for 802.1s-tag type comparison in the
 * additional fields parsing algorithm. The default value is 0x9200 (stored
 * byte swapped as value 0x0092). 
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2 . STAG_VALUE3
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2_STAG_VALUE3(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2_STAG_VALUE3     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_PP_TAGS2_STAG_VALUE3(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief VLAN tag detection
 *
 * \details
 * Register: \a MACSEC_EGR:FRAME_MATCHING_HANDLING_CTRL:SAM_CP_TAG2
 */
#define VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG2  VTSS_IOREG(0x1f, 1, 0x9e43)

/** 
 * \brief
 * Translate one priority value into another using the inner tag map table
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG2 . MAP_TBL2
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG2_MAP_TBL2(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG2_MAP_TBL2     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG2_MAP_TBL2(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief Secure Association non-match flow control 
 *
 * \details
 * Register: \a MACSEC_EGR:FRAME_MATCHING_HANDLING_CTRL:SAM_NM_PARAMS
 */
#define VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS  VTSS_IOREG(0x1f, 1, 0x9e50)

/** 
 * \details 
 * 1b: Compare Ethertype in packet against msec_tag_value value (default)
 *
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . COMP_ETYPE
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_COMP_ETYPE  VTSS_BIT(0)

/** 
 * \details 
 * 1b: Check version bit is 0b (default)
 *
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . CHECK_V
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_CHECK_V  VTSS_BIT(1)

/** 
 * \details 
 * 1b: Check if packet is meant to be handled by KaY (C & E bits) (default)
 *
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . CHECK_KAY
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_CHECK_KAY  VTSS_BIT(2)

/** 
 * \details 
 * 1b: Check illegal C == 1 & E == 0 flags combination (default)
 *
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . CHECK_C_E
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_CHECK_C_E  VTSS_BIT(3)

/** 
 * \details 
 * 1b: Check illegal SC/ES/SCB bit combinations (default)
 *
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . CHECK_SC
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_CHECK_SC  VTSS_BIT(4)

/** 
 * \details 
 * 1b: Check short length field contents out-of-range (default)
 *
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . CHECK_SL
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_CHECK_SL  VTSS_BIT(5)

/** 
 * \details 
 * 1b: Check PN (Packet Number) to be non-zero for all cipher suites and
 * regardless of SA hit. This value should be used if only cipher suites
 * with 32-bit packet numbering are used. Otherwise, this flag must be set
 * to 0b.
 *
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . CHECK_PN
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_CHECK_PN  VTSS_BIT(6)

/** 
 * \brief
 * Ethertype value used for MACsec tag type comparison (stored byte
 * swapped) default value 0x88E5 (stored as 0xE588) is the standard MACsec
 * tag value.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS . MACSEC_TAG_VALUE
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_MACSEC_TAG_VALUE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_MACSEC_TAG_VALUE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_PARAMS_MACSEC_TAG_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Secure Association non-match flow control 
 *
 * \details
 * Register: \a MACSEC_EGR:FRAME_MATCHING_HANDLING_CTRL:SAM_NM_FLOW_NCP
 */
#define VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP  VTSS_IOREG(0x1f, 1, 0x9e51)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_UNTAGGED_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_FLOW_TYPE  VTSS_BIT(0)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_UNTAGGED_DEST_PORT
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DEST_PORT     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_UNTAGGED_DROP_ACTION
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DROP_ACTION     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_TAGGED_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_FLOW_TYPE  VTSS_BIT(8)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_TAGGED_DEST_PORT
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DEST_PORT     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_TAGGED_DROP_ACTION
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DROP_ACTION     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_BADTAG_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_FLOW_TYPE  VTSS_BIT(16)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_BADTAG_DEST_PORT
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DEST_PORT     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_BADTAG_DROP_ACTION
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DROP_ACTION     VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,22,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_KAY_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_FLOW_TYPE  VTSS_BIT(24)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_KAY_DEST_PORT
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DEST_PORT     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP . NCP_KAY_DROP_ACTION
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DROP_ACTION     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,30,2)


/** 
 * \brief Secure Association non-match flow control 
 *
 * \details
 * Register: \a MACSEC_EGR:FRAME_MATCHING_HANDLING_CTRL:SAM_NM_FLOW_CP
 */
#define VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP  VTSS_IOREG(0x1f, 1, 0x9e52)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_UNTAGGED_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_FLOW_TYPE  VTSS_BIT(0)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_UNTAGGED_DEST_PORT
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DEST_PORT     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_UNTAGGED_DROP_ACTION
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DROP_ACTION     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_TAGGED_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_FLOW_TYPE  VTSS_BIT(8)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_TAGGED_DEST_PORT
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DEST_PORT     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_TAGGED_DROP_ACTION
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DROP_ACTION     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_BADTAG_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_FLOW_TYPE  VTSS_BIT(16)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_BADTAG_DEST_PORT
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DEST_PORT     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_BADTAG_DROP_ACTION
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DROP_ACTION     VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,22,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_KAY_FLOW_TYPE
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_FLOW_TYPE  VTSS_BIT(24)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_KAY_DEST_PORT
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DEST_PORT(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DEST_PORT     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DEST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP . CP_KAY_DROP_ACTION
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DROP_ACTION(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DROP_ACTION     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DROP_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,30,2)


/** 
 * \brief Misc control register
 *
 * \details
 * Register: \a MACSEC_EGR:FRAME_MATCHING_HANDLING_CTRL:MISC_CONTROL
 */
#define VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL  VTSS_IOREG(0x1f, 1, 0x9e5f)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL . MC_LATENCY_FIX
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_MC_LATENCY_FIX(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_MC_LATENCY_FIX     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_MC_LATENCY_FIX(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL . STATIC_BYPASS
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_STATIC_BYPASS  VTSS_BIT(8)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL . NM_MACSEC_EN
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_NM_MACSEC_EN  VTSS_BIT(9)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL . VALIDATE_FRAMES
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_VALIDATE_FRAMES(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_VALIDATE_FRAMES     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_VALIDATE_FRAMES(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL . XFORM_REC_SIZE
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_XFORM_REC_SIZE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_XFORM_REC_SIZE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_XFORM_REC_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)


/** 
 * \brief Header bypass configuration
 *
 * \details
 * Register: \a MACSEC_EGR:FRAME_MATCHING_HANDLING_CTRL:HDR_EXT_CTRL
 */
#define VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL  VTSS_IOREG(0x1f, 1, 0x9e60)

/** 
 * \brief
 * Compare value for Etype2 field in header bypass mode (for the Ethertype
 * field directly following the MAC_SA). 
 * If header bypass is enabled, the inner ETYPE value is used in control
 * packet detector algorithm. 
 * If header bypass is not enabled, this field is ignored. 
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL . HB_ETYPE_MATCH
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HB_ETYPE_MATCH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HB_ETYPE_MATCH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HB_ETYPE_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Size of the bypassed header in header bypass mode in 2-byte units
 *
 * \details 
 * The allowed values are 0 (no header bypass), 8, 9, 10, 11 to 15. 
 *
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL . HDR_BYPASS_LEN
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HDR_BYPASS_LEN(x)  VTSS_ENCODE_BITFIELD(x,17,4)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HDR_BYPASS_LEN     VTSS_ENCODE_BITMASK(17,4)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HDR_BYPASS_LEN(x)  VTSS_EXTRACT_BITFIELD(x,17,4)

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
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL . SECTAG_AFTER_VLAN
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_SECTAG_AFTER_VLAN  VTSS_BIT(21)

/** 
 * \brief
 * Enables matching the Etype2 field with the hb_e_type_match value in
 * header bypass mode.
 * If header bypass is enabled, the value must be set to 1b.
 *
 * \details 
 * 0b: For debug only
 *
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL . HB_E_TYPE_MATCH_EN
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HB_E_TYPE_MATCH_EN  VTSS_BIT(22)


/** 
 * \brief Crypt Authentication control register
 *
 * \details
 * Register: \a MACSEC_EGR:FRAME_MATCHING_HANDLING_CTRL:CRYPT_AUTH_CTRL
 */
#define VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_CRYPT_AUTH_CTRL  VTSS_IOREG(0x1f, 1, 0x9e61)

/** 
 * \brief
 * Specifies length (in bytes) of the bypass data during crypt-authenticate
 * operation. The bypass data should contain MAC header to be able to
 * classify the packet into the corresponding crypto-authenticate flow
 * control register and additionally it might include the IV used in the
 * transformation.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_CRYPT_AUTH_CTRL . CRYPT_AUTH_BYPASS_LEN
 */
#define  VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_CRYPT_AUTH_CTRL_CRYPT_AUTH_BYPASS_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_CRYPT_AUTH_CTRL_CRYPT_AUTH_BYPASS_LEN     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_CRYPT_AUTH_CTRL_CRYPT_AUTH_BYPASS_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a MACSEC_EGR:FRM_CLASS_DEBUG
 *
 * Classification and token generation debug registers
 */


/** 
 * \brief Control packet match debug register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:CP_MATCH_DEBUG
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG  VTSS_IOREG(0x1f, 1, 0x9f00)

/** 
 * \brief
 * These bits correspond to the bits in the CP_MATCH_ENABLE register. They
 * give the matching state for all comparisons (irrespective of whether or
 * not those were enabled) for the last packet that passed through the
 * classification engine, with a 1b indicating a match.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG . MAC_DA_7_TO_0
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_MAC_DA_7_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_MAC_DA_7_TO_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_MAC_DA_7_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * These bits correspond to the bits in the CP_MATCH_ENABLE register. They
 * give the matching state for all comparisons (irrespective of whether or
 * not those were enabled) for the last packet that passed through the
 * classification engine, with a 1b indicating a match.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG . ETYPE_7_TO_0
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_ETYPE_7_TO_0(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_ETYPE_7_TO_0     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_ETYPE_7_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * These bits correspond to the bits in the CP_MATCH_ENABLE register. They
 * give the matching state for all comparisons (irrespective of whether or
 * not those were enabled) for the last packet that passed through the
 * classification engine, with a 1b indicating a match.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG . COMB_9_TO_8
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_COMB_9_TO_8(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_COMB_9_TO_8     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_COMB_9_TO_8(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * These bits correspond to the bits in the CP_MATCH_ENABLE register. They
 * give the matching state for all comparisons (irrespective of whether or
 * not those were enabled) for the last packet that passed through the
 * classification engine, with a 1b indicating a match.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG . DA_RANGE
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_DA_RANGE  VTSS_BIT(18)

/** 
 * \brief
 * These bits correspond to the bits in the CP_MATCH_ENABLE register. They
 * give the matching state for all comparisons (irrespective of whether or
 * not those were enabled) for the last packet that passed through the
 * classification engine, with a 1b indicating a match.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG . CONST_44
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_CONST_44  VTSS_BIT(19)

/** 
 * \brief
 * These bits correspond to the bits in the CP_MATCH_ENABLE register. They
 * give the matching state for all comparisons (irrespective of whether or
 * not those were enabled) for the last packet that passed through the
 * classification engine, with a 1b indicating a match.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG . CONST_48
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_CONST_48  VTSS_BIT(20)

/** 
 * \brief
 * These bits correspond to the bits in the CP_MATCH_ENABLE register. They
 * give the matching state for all comparisons (irrespective of whether or
 * not those were enabled) for the last packet that passed through the
 * classification engine, with a 1b indicating a match.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG . ETYPE_17_TO_10
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_ETYPE_17_TO_10(x)  VTSS_ENCODE_BITFIELD(x,21,8)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_ETYPE_17_TO_10     VTSS_ENCODE_BITMASK(21,8)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_ETYPE_17_TO_10(x)  VTSS_EXTRACT_BITFIELD(x,21,8)

/** 
 * \brief
 * Valid header bypass
 *
 * \details 
 * 1b: Valid bypass header in last packet if header bypass mode is enabled.
 *
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG . HB_VALID
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_HB_VALID  VTSS_BIT(30)

/** 
 * \brief
 * his bit gives the matching state for Etype2 comparison (hb_e_type_match
 * field in the HDR_EXT_CTRL register) for the last packet that passed
 * through the classification engine, with a 1b indicating a match.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG . HB_ETYPE2
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_CP_MATCH_DEBUG_HB_ETYPE2  VTSS_BIT(31)


/** 
 * \brief Secure Association match debug register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:SAM_DEBUG
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG  VTSS_IOREG(0x1f, 1, 0x9f08)

/** 
 * \brief
 * Secure Association entry index used for processing the last packet that
 * was classified, only valid if sa_hit 
 * equals 1b.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG . SA_NR
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG_SA_NR(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG_SA_NR     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG_SA_NR(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \details 
 * 1b: The last packet that was classified hit an enabled SA match
 * parameter set
 *
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG . SA_HIT
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG_SA_HIT  VTSS_BIT(23)

/** 
 * \brief
 * Source port for the last packet that was classified
 *
 * \details 
 * 00b: Common port
 * 01b: Reserved port
 * 10b: Controlled port
 * 11b: Uncontrolled port
 *
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG . SOURCE_PORT
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG_SOURCE_PORT(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG_SOURCE_PORT     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG_SOURCE_PORT(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Classification of the MACsec packet classification algorithm.

 *
 * \details 
 * 00b: Untagged
 * 01b: Tagged
 * 10b: Bad tag
 * 11b: KaY
 *
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG . MACSEC_CLASS
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG_MACSEC_CLASS(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG_MACSEC_CLASS     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG_MACSEC_CLASS(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * Classification of the programmable control packet classification logic
 * for the last packet that was classified 

 *
 * \details 
 * 1b: Control packet
 *
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG . CONTROL_PACKET
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_DEBUG_CONTROL_PACKET  VTSS_BIT(28)


/** 
 * \brief Secure Association match debug register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:SAM_MATCH_DEBUG1
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_MATCH_DEBUG1  VTSS_IOREG(0x1f, 1, 0x9f10)


/** 
 * \brief Secure Association match debug register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:SAM_MATCH_DEBUG2
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_MATCH_DEBUG2  VTSS_IOREG(0x1f, 1, 0x9f11)


/** 
 * \brief VLAN tag detection debug register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:SAM_PP_DEBUG1
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG1  VTSS_IOREG(0x1f, 1, 0x9f20)

/** 
 * \brief
 * Parsed ethertype
 * Ethertype value as parsed for the last packet that was classified, byte
 * swapped as usual
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG1 . PARSED_ETHERTYPE
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG1_PARSED_ETHERTYPE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG1_PARSED_ETHERTYPE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG1_PARSED_ETHERTYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Parsed VLAN
 * VLAN tag VID field value as parsed for the last packet that was
 * classified
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG1 . PARSED_VLAN
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG1_PARSED_VLAN(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG1_PARSED_VLAN     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG1_PARSED_VLAN(x)  VTSS_EXTRACT_BITFIELD(x,16,12)

/** 
 * \brief
 * Parsed user priority
 * User priority (after post-processing) as parsed for the last packet that
 * was classified
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG1 . PARSED_UP
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG1_PARSED_UP(x)  VTSS_ENCODE_BITFIELD(x,28,3)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG1_PARSED_UP     VTSS_ENCODE_BITMASK(28,3)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG1_PARSED_UP(x)  VTSS_EXTRACT_BITFIELD(x,28,3)


/** 
 * \brief VLAN Tag detection debug register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:SAM_PP_DEBUG2
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2  VTSS_IOREG(0x1f, 1, 0x9f21)

/** 
 * \brief
 * VLAN valid flag as parsed for the last packet that was classified
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2 . VLAN_VALID
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_VLAN_VALID  VTSS_BIT(0)

/** 
 * \brief
 * Q-in-Q tags found as parsed for the last packet that was classified
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2 . QINQ_FOUND
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_QINQ_FOUND  VTSS_BIT(1)

/** 
 * \brief
 * 802.1s-tag found as parsed for the last packet that was classified
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2 . STAG_VALID
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_STAG_VALID  VTSS_BIT(2)

/** 
 * \brief
 * 802.1Q-tag found flag as parsed for the last packet that was classified
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2 . QTAG_VALID
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_QTAG_VALID  VTSS_BIT(3)

/** 
 * \brief
 * Last packet that was classified was an LPidle/fault status packet
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2 . LPIDLE_PKT
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_LPIDLE_PKT  VTSS_BIT(4)

/** 
 * \brief
 * Last packet that was classified had 16 bytes or less
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2 . ONE_WORD_PKT
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_ONE_WORD_PKT  VTSS_BIT(5)

/** 
 * \brief
 * This field contains the value of the pkt_rx_mty signal that is captured
 * with the last word of the last parsed packet.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2 . LAST_MTY
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_LAST_MTY(x)  VTSS_ENCODE_BITFIELD(x,6,4)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_LAST_MTY     VTSS_ENCODE_BITMASK(6,4)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_LAST_MTY(x)  VTSS_EXTRACT_BITFIELD(x,6,4)

/** 
 * \brief
 * The valid MAC Ethertype was parsed.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2 . PKT_ET_VALID
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_PKT_ET_VALID  VTSS_BIT(10)

/** 
 * \brief
 * The valid MAC source address was parsed.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2 . PKT_SA_VALID
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_PKT_SA_VALID  VTSS_BIT(11)

/** 
 * \brief
 * The valid MAC destination address was parsed.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2 . PKT_DA_VALID
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_PKT_DA_VALID  VTSS_BIT(12)

/** 
 * \brief
 * When set to 1b, the MAC destination address of the input packet that is
 * used in control packet matching is a broadcast address:
 * FF:FF:FF:FF:FF:FF
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2 . MAC_DA_BROADCAST
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_MAC_DA_BROADCAST  VTSS_BIT(13)

/** 
 * \brief
 * This flags equals to bit 0 of the MAC destination address of the input
 * packet that is used in control packet matching:

 *
 * \details 
 * 1b: multicast packet.
 * 0b: unicast packet.
 *
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2 . MAC_DA_MULTICAST
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_MAC_DA_MULTICAST  VTSS_BIT(14)

/** 
 * \brief
 * Single step enable
 * When written with 1b, the classifier will stall its data input after
 * each packet until another write to this register occurs, keeping all
 * other status registers stable. This allows classifying one frame at a
 * time under software control.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2 . SINGLE_STEP_EN
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG2_SINGLE_STEP_EN  VTSS_BIT(31)


/** 
 * \brief VLAN tag detection debug register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:SAM_PP_DEBUG3
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG3  VTSS_IOREG(0x1f, 1, 0x9f22)

/** 
 * \brief
 * Inner VLAN tag VID field value as parsed for the last packet that was
 * classified
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG3 . PARSED_VLAN_INNER
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG3_PARSED_VLAN_INNER(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG3_PARSED_VLAN_INNER     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG3_PARSED_VLAN_INNER(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/** 
 * \brief
 * Inner VLAN tag user priority (after post-processing) as parsed for the
 * last packet that was classified
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG3 . PARSED_UP_INNER
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG3_PARSED_UP_INNER(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG3_PARSED_UP_INNER     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_SAM_PP_DEBUG3_PARSED_UP_INNER(x)  VTSS_EXTRACT_BITFIELD(x,12,3)


/** 
 * \brief Debug parsed destination address register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:DBG_PARSED_DA_LO
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_DA_LO  VTSS_IOREG(0x1f, 1, 0x9f40)


/** 
 * \brief Debug parsed destination address ethtype register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:DBG_PARSED_DA_HI
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_DA_HI  VTSS_IOREG(0x1f, 1, 0x9f41)

/** 
 * \brief
 * Bits [47:32] of MAC_DA extracted from the last packet
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_DA_HI . PARSED_MAC_DA_47_TO_32
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_DA_HI_PARSED_MAC_DA_47_TO_32(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_DA_HI_PARSED_MAC_DA_47_TO_32     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_DA_HI_PARSED_MAC_DA_47_TO_32(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Original Ethertype field as extracted from the last packet
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_DA_HI . ORIG_ETH_TYPE
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_DA_HI_ORIG_ETH_TYPE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_DA_HI_ORIG_ETH_TYPE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_DA_HI_ORIG_ETH_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Debug parsed source address register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:DBG_PARSED_SA_LO
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_SA_LO  VTSS_IOREG(0x1f, 1, 0x9f42)


/** 
 * \brief Debug parsed source address HI register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:DBG_PARSED_SA_HI
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_SA_HI  VTSS_IOREG(0x1f, 1, 0x9f43)

/** 
 * \brief
 * Bits [47:32] of MAC_SA extracted from the last packet
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_SA_HI . PARSED_MAC_SA_47_TO_32
 */
#define  VTSS_F_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_SA_HI_PARSED_MAC_SA_47_TO_32(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_SA_HI_PARSED_MAC_SA_47_TO_32     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_SA_HI_PARSED_MAC_SA_47_TO_32(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Debug parsed Sectag register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:DBG_PARSED_SECTAG_LO
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_SECTAG_LO  VTSS_IOREG(0x1f, 1, 0x9f44)


/** 
 * \brief Debug parsed Sectag HI register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:DBG_PARSED_SECTAG_HI
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_SECTAG_HI  VTSS_IOREG(0x1f, 1, 0x9f45)


/** 
 * \brief Debug parsed secure channels identifier register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:DBG_PARSED_SCI_LO
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_SCI_LO  VTSS_IOREG(0x1f, 1, 0x9f46)


/** 
 * \brief Debug parsed secure channel identifier HI register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:DBG_PARSED_SCI_HI
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_PARSED_SCI_HI  VTSS_IOREG(0x1f, 1, 0x9f47)


/** 
 * \brief Debug flow lookup register
 *
 * \details
 * Register: \a MACSEC_EGR:FRM_CLASS_DEBUG:DBG_FLOW_LOOKUP
 */
#define VTSS_MACSEC_EGR_FRM_CLASS_DEBUG_DBG_FLOW_LOOKUP  VTSS_IOREG(0x1f, 1, 0x9f48)

/**
 * Register Group: \a MACSEC_EGR:CRYPTO_HDR_BYPASS_DEBUG
 *
 * Crypto command and header bypass debug registers
 */


/** 
 * \brief MACsec crypto command debug registers
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_HDR_BYPASS_DEBUG:CRYPTO_CMD_DEBUG
 *
 * @param ri Register: CRYPTO_CMD_DEBUG, 0-3
 */
#define VTSS_MACSEC_EGR_CRYPTO_HDR_BYPASS_DEBUG_CRYPTO_CMD_DEBUG(ri)  VTSS_IOREG(0x1f, 1, 0x9f4c | (ri))


/** 
 * \brief Parsed 2B-16B field
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_HDR_BYPASS_DEBUG:DBG_PARSED_2B_16B
 *
 * @param ri Register: DBG_PARSED_2B_16B, 0-3
 */
#define VTSS_MACSEC_EGR_CRYPTO_HDR_BYPASS_DEBUG_DBG_PARSED_2B_16B(ri)  VTSS_IOREG(0x1f, 1, 0x9f50 | (ri))

/**
 * Register Group: \a MACSEC_EGR:SA_MATCH_DEBUG
 *
 * Individual Secure Association match debug registers
 */


/** 
 * \brief Secure Association match debug register
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_DEBUG:DBG_SA_MATCHES1
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1(ri)  VTSS_IOREG(0x1f, 1, 0x9f80 | (ri * 2))

/** 
 * \brief
 * [0] 
 * 
 * mac_sa_0_match 
 * 
 * MAC_SA bits [7:0] equal to bits [15:8] in the SAM_MAC_SA_MATCH_HI_x
 * register 
 * 
 * [1] 
 * 
 * mac_sa_1_match 
 * 
 * MAC_SA bits [15:8] equal to bits [7:0] in the SAM_MAC_SA_MATCH_HI_x
 * register 
 * 
 * [2] 
 * 
 * mac_sa_2_match 
 * 
 * MAC_SA bits [23:16] equal to bits [31:24] in the SAM_MAC_SA_MATCH_LO_x
 * register 
 * 
 * [3] 
 * 
 * mac_sa_3_match 
 * 
 * MAC_SA bits [31:24] equal to bits [23:16] in the SAM_MAC_SA_MATCH_LO_x
 * register 
 * 
 * [4] 
 * 
 * mac_sa_4_match 
 * 
 * MAC_SA bits [39:32] equal to [15:8] in the SAM_MAC_SA_MATCH_LO_x
 * register 
 * 
 * [5] 
 * 
 * mac_sa_5_match 
 * 
 * MAC_SA bits [47:40] equal to [7:0] in the SAM_MAC_SA_MATCH_LO_x
 * register.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . MAC_SA_MATCH_5_TO_0
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_MAC_SA_MATCH_5_TO_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_MAC_SA_MATCH_5_TO_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_MAC_SA_MATCH_5_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * [6] 
 * 
 * mac_da_0_match 
 * 
 * MAC_DA bits [7:0] equal to [15:8] in the SAM_MAC_DA_MATCH_HI_x register 
 * 
 * [7] 
 * 
 * mac_da_1_match 
 * 
 * MAC_DA bits [15:8] equal to [7:0] in the SAM_MAC_DA_MATCH_HI_x register 
 * 
 * [8] 
 * 
 * mac_da_2_match 
 * 
 * MAC_DA bits [23:16] equal to [31:24] in the SAM_MAC_DA_MATCH_LO_x
 * register 
 * 
 * [9] 
 * 
 * mac_da_3_match 
 * 
 * MAC_DA bits [31:24] equal to [23:16] in the SAM_MAC_DA_MATCH_LO_x
 * register 
 * 
 * [10] 
 * 
 * mac_da_4_match 
 * 
 * MAC_DA bits [39:32] equal to [15:8] in the SAM_MAC_DA_MATCH_LO_x
 * register 
 * 
 * [11] 
 * 
 * mac_da_5_match 
 * 
 * MAC_DA bits [47:40] equal to [7:0] in the SAM_MAC_DA_MATCH_LO_x register
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . MAC_DA_MATCH_5_TO_0
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_MAC_DA_MATCH_5_TO_0(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_MAC_DA_MATCH_5_TO_0     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_MAC_DA_MATCH_5_TO_0(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Parsed Ethertype field equal to ether_type field in the
 * SAM_MAC_DA_MATCH_LO_x register
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . MAC_ETYPE_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_MAC_ETYPE_MATCH  VTSS_BIT(12)

/** 
 * \brief
 * Parsed VLAN valid flag equal to vlan_valid bit in the SAM_MISC_MATCH_x
 * register 

 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . VLAN_VLD_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_VLAN_VLD_MATCH  VTSS_BIT(13)

/** 
 * \brief
 * Parsed Q-in-Q found flag equal to qinq_found field in the
 * SAM_MISC_MATCH_x register
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . QINQ_FOUND_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_QINQ_FOUND_MATCH  VTSS_BIT(14)

/** 
 * \brief
 * Parsed STAG valid flag equal to stag_valid bit in the SAM_MISC_MATCH_x
 * register
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . STAG_VLD_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_STAG_VLD_MATCH  VTSS_BIT(15)

/** 
 * \brief
 * Parsed QTAG valid flag equal to qtag_valid bit in the SAM_MISC_MATCH_x
 * register
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . QTAG_VLD_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_QTAG_VLD_MATCH  VTSS_BIT(16)

/** 
 * \brief
 * Parsed VLAN user priority value equal to vlan_up field in the
 * SAM_MISC_MATCH_x register
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . VLAN_UP_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_VLAN_UP_MATCH  VTSS_BIT(17)

/** 
 * \brief
 * Parsed VLAN ID value equal to with vlan_id field in the
 * SAM_MAC_DA_MATCH_HI_x register 

 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . VLAN_ID_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_VLAN_ID_MATCH  VTSS_BIT(18)

/** 
 * \brief
 * Source port equal to source_port field in the SAM_MISC_MATCH_x register
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . SOURCE_PORT_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_SOURCE_PORT_MATCH  VTSS_BIT(19)

/** 
 * \brief
 * Control packet status equal to control_packet bit in the
 * SAM_MISC_MATCH_x register
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . CTRL_PACKET_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_CTRL_PACKET_MATCH  VTSS_BIT(20)

/** 
 * \brief
 * Result of MACsec tag classification algorithm matches the enable bits
 * for MACsec tag classification in SAM_MISC_MATCH_x register: key_tag,
 * bad_tag, tagged, and untagged. 

 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . MACSEC_TAG_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_MACSEC_TAG_MATCH  VTSS_BIT(21)

/** 
 * \brief
 * MACsec header SCI value equal to 64 bits SCI value in the
 * SAM_SCI_MATCH_LO/HI_x registers. 
 * This bit is reserved for an egress-only (-e) core.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . MACSEC_SCI_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_MACSEC_SCI_MATCH  VTSS_BIT(23)

/** 
 * \brief
 * The parsed MACsec TCI/AN field equal to macsec_tci_an field in the
 * SAM_MISC_MATCH_x register
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1 . TCI_AN_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_TCI_AN_MATCH(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_TCI_AN_MATCH     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES1_TCI_AN_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/** 
 * \brief Secure Association match debug register
 *
 * \details
 * Register: \a MACSEC_EGR:SA_MATCH_DEBUG:DBG_SA_MATCHES2
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES2(ri)  VTSS_IOREG(0x1f, 1, 0x9f81 | (ri * 2))

/** 
 * \brief
 * Parsed inner VLAN user priority value equals to vlan_up_inner field in
 * the SAM_EXT_MATCH_x register
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES2 . VLAN_UP_INNER_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES2_VLAN_UP_INNER_MATCH  VTSS_BIT(0)

/** 
 * \brief
 * Parsed inner VLAN ID value equal to with vlan_id_inner field in the
 * SAM_EXT_MATCH_x register
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES2 . VLAN_ID_INNER_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES2_VLAN_ID_INNER_MATCH  VTSS_BIT(1)

/** 
 * \brief
 * For correctly detected bypass header the parsed 2B-16B field is equal to
 * the SAM_HDR_BYPASS_MATCH1/2_x. Only the bits indicated by
 * SAM_HDR_BYPASS_MASK1/2_x are compared.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES2 . HDR_2B_16B_MATCH
 */
#define  VTSS_F_MACSEC_EGR_SA_MATCH_DEBUG_DBG_SA_MATCHES2_HDR_2B_16B_MATCH  VTSS_BIT(2)

/**
 * Register Group: \a MACSEC_EGR:SA_STATS_EGR
 *
 * Secure Association egress statistics registers
 */


/** 
 * \brief sa.OutOctetsEncrypted/OutOctetsProtected (chained, 1st counter) - lower 32 bits
 *
 * \details
 * OutOctetsEncrypted: The number of plain text octets that are integrity
 * protected and encrypted on the transmitting SA.
 * OutOctetsProtected: The number of plain text octets that are integrity
 * protected but not encrypted on the transmitting SA.
 *
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_OCTETS_ENCRYPTED_FIRST_CNTR_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_FIRST_CNTR_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0xa000 | (ri * 32))


/** 
 * \brief sa.OutOctetsEncrypted/OutOctetsProtected (chained, 1st counter) - upper 8 bits
 *
 * \details
 * OutOctetsEncrypted: The number of plain text octets that are integrity
 * protected and encrypted on the transmitting SA.
 * OutOctetsProtected: The number of plain text octets that are integrity
 * protected but not encrypted on the transmitting SA.
 *
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_OCTETS_ENCRYPTED_FIRST_CNTR_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_FIRST_CNTR_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0xa001 | (ri * 32))

/** 
 * \brief
 * sa.OutOctetsEncrypted/OutOctetsProtected - upper 8 bits of the chained,
 * first 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_FIRST_CNTR_UPPER . OUT_OCTETS_ENCRYPTED_FIRST_CNTR_UPPER
 */
#define  VTSS_F_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_FIRST_CNTR_UPPER_OUT_OCTETS_ENCRYPTED_FIRST_CNTR_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_FIRST_CNTR_UPPER_OUT_OCTETS_ENCRYPTED_FIRST_CNTR_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_FIRST_CNTR_UPPER_OUT_OCTETS_ENCRYPTED_FIRST_CNTR_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.OutOctetsEncrypted/OutOctetsProtected (chained, 2nd counter) - lower 32 bits
 *
 * \details
 * OutOctetsEncrypted: The number of plain text octets that are integrity
 * protected and encrypted on the transmitting SA.
 * OutOctetsProtected: The number of plain text octets that are integrity
 * protected but not encrypted on the transmitting SA.
 *
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_OCTETS_ENCRYPTED_SECOND_CNTR_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_SECOND_CNTR_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0xa002 | (ri * 32))


/** 
 * \brief sa.OutOctetsEncrypted/OutOctetsProtected (chained, 2nd counter) - upper 8 bits
 *
 * \details
 * OutOctetsEncrypted: The number of plain text octets that are integrity
 * protected and encrypted on the transmitting SA.
 * OutOctetsProtected: The number of plain text octets that are integrity
 * protected but not encrypted on the transmitting SA.
 *
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_OCTETS_ENCRYPTED_SECOND_CNTR_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_SECOND_CNTR_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0xa003 | (ri * 32))

/** 
 * \brief
 * sa.OutOctetsEncrypted/OutOctetsProtected - upper 8 bits of the chained,
 * second 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_SECOND_CNTR_UPPER . OUT_OCTETS_ENCRYPTED_SECOND_CNTR_UPPER
 */
#define  VTSS_F_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_SECOND_CNTR_UPPER_OUT_OCTETS_ENCRYPTED_SECOND_CNTR_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_SECOND_CNTR_UPPER_OUT_OCTETS_ENCRYPTED_SECOND_CNTR_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_SECOND_CNTR_UPPER_OUT_OCTETS_ENCRYPTED_SECOND_CNTR_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.OutPktsEncrypted/OutPktsProtected/OutPktsHitDropReserved - lower 32 bits
 *
 * \details
 * OutPktsEncrypted: The number of integrity protected and encrypted
 * packets for this transmitting SA.
 * OutPktsProtected: The number of integrity protected but not encrypted
 * packets for this transmitting SA.
 * OutPktsHitDropReserved: Bypass/drop flow was found in SA table.
 *
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_PKTS_ENCRYPTED_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_ENCRYPTED_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0xa004 | (ri * 32))


/** 
 * \brief sa.OutPktsEncrypted/OutPktsProtected/OutPktsHitDropReserved - upper 8 bits
 *
 * \details
 * OutPktsEncrypted: The number of integrity protected and encrypted
 * packets for this transmitting SA.
 * OutPktsProtected: The number of integrity protected but not encrypted
 * packets for this transmitting SA.
 * OutPktsHitDropReserved: Bypass/drop flow was found in SA table.
 *
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_PKTS_ENCRYPTED_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_ENCRYPTED_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0xa005 | (ri * 32))

/** 
 * \brief
 * sa.OutPktsEncrypted/OutPktsProtected/OutPktsHitDropReserved - upper 8
 * bits of 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_ENCRYPTED_UPPER . OUT_PKTS_ENCRYPTED_UPPER
 */
#define  VTSS_F_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_ENCRYPTED_UPPER_OUT_PKTS_ENCRYPTED_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_ENCRYPTED_UPPER_OUT_PKTS_ENCRYPTED_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_ENCRYPTED_UPPER_OUT_PKTS_ENCRYPTED_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.OutPktsTooLong (MTU check) - lower 32 bits
 *
 * \details
 * OutPktsTooLong: For this SA, the number of transmitted packets discarded
 * because the packet length is greater than the MTU of the Common Port
 * interface.
 *
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_PKTS_TOO_LONG_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_TOO_LONG_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0xa006 | (ri * 32))


/** 
 * \brief sa.OutPktsTooLong (MTU check) - upper 8 bits
 *
 * \details
 * OutPktsTooLong: For this SA, the number of transmitted packets discarded
 * because the packet length is greater than the MTU of the Common Port
 * interface.
 *
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_PKTS_TOO_LONG_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_TOO_LONG_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0xa007 | (ri * 32))

/** 
 * \brief
 * sa.OutPktsTooLong (MTU check) - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_TOO_LONG_UPPER . OUT_PKTS_TOO_LONG_UPPER
 */
#define  VTSS_F_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_TOO_LONG_UPPER_OUT_PKTS_TOO_LONG_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_TOO_LONG_UPPER_OUT_PKTS_TOO_LONG_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_TOO_LONG_UPPER_OUT_PKTS_TOO_LONG_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.ifOutUcastPkts - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_UNICAST_PKTS_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_UNICAST_PKTS_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0xa008 | (ri * 32))


/** 
 * \brief sa.ifOutUcastPkts - upper 8 bits
 *
 * \details
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_UNICAST_PKTS_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_UNICAST_PKTS_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0xa009 | (ri * 32))

/** 
 * \brief
 * sa.ifOutUcastPkts - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_UNICAST_PKTS_UPPER . OUT_UNICAST_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_EGR_SA_STATS_EGR_OUT_UNICAST_PKTS_UPPER_OUT_UNICAST_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_SA_STATS_EGR_OUT_UNICAST_PKTS_UPPER_OUT_UNICAST_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_SA_STATS_EGR_OUT_UNICAST_PKTS_UPPER_OUT_UNICAST_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.ifOutMulticastPkts - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_MULTICAST_PKTS_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_MULTICAST_PKTS_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0xa00a | (ri * 32))


/** 
 * \brief sa.ifOutMulticastPkts - upper 8 bits
 *
 * \details
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_MULTICAST_PKTS_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_MULTICAST_PKTS_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0xa00b | (ri * 32))

/** 
 * \brief
 * sa.ifOutMulticastPkts - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_MULTICAST_PKTS_UPPER . OUT_MULTICAST_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_EGR_SA_STATS_EGR_OUT_MULTICAST_PKTS_UPPER_OUT_MULTICAST_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_SA_STATS_EGR_OUT_MULTICAST_PKTS_UPPER_OUT_MULTICAST_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_SA_STATS_EGR_OUT_MULTICAST_PKTS_UPPER_OUT_MULTICAST_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief sa.ifOutBroadcastPkts - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_BROADCAST_PKTS_LOWER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_BROADCAST_PKTS_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0xa00c | (ri * 32))


/** 
 * \brief sa.ifOutBroadcastPkts - upper 8 bits
 *
 * \details
 * Register: \a MACSEC_EGR:SA_STATS_EGR:OUT_BROADCAST_PKTS_UPPER
 *
 * @param ri Replicator: x_NUM_SA_FLOWS, 0-63
 */
#define VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_BROADCAST_PKTS_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0xa00d | (ri * 32))

/** 
 * \brief
 * sa.ifOutBroadcastPkts - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_BROADCAST_PKTS_UPPER . OUT_BROADCAST_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_EGR_SA_STATS_EGR_OUT_BROADCAST_PKTS_UPPER_OUT_BROADCAST_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_SA_STATS_EGR_OUT_BROADCAST_PKTS_UPPER_OUT_BROADCAST_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_SA_STATS_EGR_OUT_BROADCAST_PKTS_UPPER_OUT_BROADCAST_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a MACSEC_EGR:VLAN_STATS_EGR
 *
 * VLAN egress statistics registers
 */


/** 
 * \brief vlan.OutOctetsVL (chained, 1st counter) - lower 32 bits
 *
 * \details
 * OutOctetsVL: Number of outgoing octets processed for VLAN_VALID frames
 * per User Priority. Total 8 sets of these counters are available for each
 * of the User priority.
 *
 * Register: \a MACSEC_EGR:VLAN_STATS_EGR:OUT_OCTETS_VL_FIRST_CNTR_LOWER
 *
 * @param ri Register: OUT_OCTETS_VL_FIRST_CNTR_LOWER, 0-7
 */
#define VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_OCTETS_VL_FIRST_CNTR_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0xb000 | (ri * 32))


/** 
 * \brief vlan.OutOctetsVL (chained, 1st counter) - upper 8 bits
 *
 * \details
 * OutOctetsVL: Number of outgoing octets processed for VLAN_VALID frames
 * per User Priority. Total 8 sets of these counters are available for each
 * of the User priority.
 *
 * Register: \a MACSEC_EGR:VLAN_STATS_EGR:OUT_OCTETS_VL_FIRST_CNTR_UPPER
 *
 * @param ri Register: OUT_OCTETS_VL_FIRST_CNTR_UPPER, 0-7
 */
#define VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_OCTETS_VL_FIRST_CNTR_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0xb001 | (ri * 32))

/** 
 * \brief
 * vlan.OutOctetsVL (chained, 1st counter) - upper 8 bits of the chained,
 * first 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_OCTETS_VL_FIRST_CNTR_UPPER . OUT_OCTETS_VL_FIRST_CNTR_UPPER
 */
#define  VTSS_F_MACSEC_EGR_VLAN_STATS_EGR_OUT_OCTETS_VL_FIRST_CNTR_UPPER_OUT_OCTETS_VL_FIRST_CNTR_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_VLAN_STATS_EGR_OUT_OCTETS_VL_FIRST_CNTR_UPPER_OUT_OCTETS_VL_FIRST_CNTR_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_VLAN_STATS_EGR_OUT_OCTETS_VL_FIRST_CNTR_UPPER_OUT_OCTETS_VL_FIRST_CNTR_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief vlan.OutOctetsVL (chained, 2nd counter) - lower 32 bits
 *
 * \details
 * OutOctetsVL: Number of outgoing octets processed for VLAN_VALID frames
 * per User Priority. Total 8 sets of these counters are available for each
 * of the User priority.
 *
 * Register: \a MACSEC_EGR:VLAN_STATS_EGR:OUT_OCTETS_VL_SECOND_CNTR_LOWER
 *
 * @param ri Register: OUT_OCTETS_VL_SECOND_CNTR_LOWER, 0-7
 */
#define VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_OCTETS_VL_SECOND_CNTR_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0xb002 | (ri * 32))


/** 
 * \brief vlan.OutOctetsVL (chained, 2nd counter) - upper 8 bits
 *
 * \details
 * OutOctetsVL: Number of outgoing octets processed for VLAN_VALID frames
 * per User Priority. Total 8 sets of these counters are available for each
 * of the User priority.
 *
 * Register: \a MACSEC_EGR:VLAN_STATS_EGR:OUT_OCTETS_VL_SECOND_CNTR_UPPER
 *
 * @param ri Register: OUT_OCTETS_VL_SECOND_CNTR_UPPER, 0-7
 */
#define VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_OCTETS_VL_SECOND_CNTR_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0xb003 | (ri * 32))

/** 
 * \brief
 * vlan.OutOctetsVL (chained, 2nd counter) - upper 8 bits of the chained,
 * second 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_OCTETS_VL_SECOND_CNTR_UPPER . OUT_OCTETS_VL_SECOND_CNTR_UPPER
 */
#define  VTSS_F_MACSEC_EGR_VLAN_STATS_EGR_OUT_OCTETS_VL_SECOND_CNTR_UPPER_OUT_OCTETS_VL_SECOND_CNTR_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_VLAN_STATS_EGR_OUT_OCTETS_VL_SECOND_CNTR_UPPER_OUT_OCTETS_VL_SECOND_CNTR_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_VLAN_STATS_EGR_OUT_OCTETS_VL_SECOND_CNTR_UPPER_OUT_OCTETS_VL_SECOND_CNTR_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief vlan.OutPktsVL - lower 32 bits
 *
 * \details
 * OutPktsVL: Number of outgoing frames transmitted with VLAN_VALID per
 * User Priority.
 *
 * Register: \a MACSEC_EGR:VLAN_STATS_EGR:OUT_PKTS_VL_LOWER
 *
 * @param ri Register: OUT_PKTS_VL_LOWER, 0-7
 */
#define VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_PKTS_VL_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0xb004 | (ri * 32))


/** 
 * \brief vlan.OutPktsVL - upper 8 bits
 *
 * \details
 * OutPktsVL: Number of outgoing frames transmitted with VLAN_VALID per
 * User Priority.
 *
 * Register: \a MACSEC_EGR:VLAN_STATS_EGR:OUT_PKTS_VL_UPPER
 *
 * @param ri Register: OUT_PKTS_VL_UPPER, 0-7
 */
#define VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_PKTS_VL_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0xb005 | (ri * 32))

/** 
 * \brief
 * vlan.OutPktsVL - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_PKTS_VL_UPPER . OUT_PKTS_VL_UPPER
 */
#define  VTSS_F_MACSEC_EGR_VLAN_STATS_EGR_OUT_PKTS_VL_UPPER_OUT_PKTS_VL_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_VLAN_STATS_EGR_OUT_PKTS_VL_UPPER_OUT_PKTS_VL_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_VLAN_STATS_EGR_OUT_PKTS_VL_UPPER_OUT_PKTS_VL_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief vlan.OutDroppedPktsVL - lower 32 bits
 *
 * \details
 * OutDroppedPktsVL: Number of outgoing frames with VLAN_VALID dropped per
 * User Priority.
 *
 * Register: \a MACSEC_EGR:VLAN_STATS_EGR:OUT_DROPPED_PKTS_VL_LOWER
 *
 * @param ri Register: OUT_DROPPED_PKTS_VL_LOWER, 0-7
 */
#define VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_DROPPED_PKTS_VL_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0xb006 | (ri * 32))


/** 
 * \brief vlan.OutDroppedPktsVL - upper 8 bits
 *
 * \details
 * OutDroppedPktsVL: Number of outgoing frames with VLAN_VALID dropped per
 * User Priority.
 *
 * Register: \a MACSEC_EGR:VLAN_STATS_EGR:OUT_DROPPED_PKTS_VL_UPPER
 *
 * @param ri Register: OUT_DROPPED_PKTS_VL_UPPER, 0-7
 */
#define VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_DROPPED_PKTS_VL_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0xb007 | (ri * 32))

/** 
 * \brief
 * vlan.OutDroppedPktsVL - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_DROPPED_PKTS_VL_UPPER . OUT_DROPPED_PKTS_VL_UPPER
 */
#define  VTSS_F_MACSEC_EGR_VLAN_STATS_EGR_OUT_DROPPED_PKTS_VL_UPPER_OUT_DROPPED_PKTS_VL_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_VLAN_STATS_EGR_OUT_DROPPED_PKTS_VL_UPPER_OUT_DROPPED_PKTS_VL_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_VLAN_STATS_EGR_OUT_DROPPED_PKTS_VL_UPPER_OUT_DROPPED_PKTS_VL_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief vlan.OutOverSizePktsVL (MTU check) - lower 32 bits
 *
 * \details
 * OutOverSizePktsVL: Number of outgoing frames with VLAN_VALID which  are
 * detected OverSize due to VLAN MTU check per User Priority.
 *
 * Register: \a MACSEC_EGR:VLAN_STATS_EGR:OUT_OVERSIZE_PKTS_VL_LOWER
 *
 * @param ri Register: OUT_OVERSIZE_PKTS_VL_LOWER, 0-7
 */
#define VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_OVERSIZE_PKTS_VL_LOWER(ri)  VTSS_IOREG(0x1f, 1, 0xb008 | (ri * 32))


/** 
 * \brief vlan.OutOverSizePktsVL (MTU check) - upper 8 bits
 *
 * \details
 * OutOverSizePktsVL: Number of outgoing frames with VLAN_VALID which  are
 * detected OverSize due to VLAN MTU check per User Priority.
 *
 * Register: \a MACSEC_EGR:VLAN_STATS_EGR:OUT_OVERSIZE_PKTS_VL_UPPER
 *
 * @param ri Register: OUT_OVERSIZE_PKTS_VL_UPPER, 0-7
 */
#define VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_OVERSIZE_PKTS_VL_UPPER(ri)  VTSS_IOREG(0x1f, 1, 0xb009 | (ri * 32))

/** 
 * \brief
 * vlan.OutOverSizePktsVL (MTU check) - upper 8 bits of 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_VLAN_STATS_EGR_OUT_OVERSIZE_PKTS_VL_UPPER . OUT_OVERSIZE_PKTS_VL_UPPER
 */
#define  VTSS_F_MACSEC_EGR_VLAN_STATS_EGR_OUT_OVERSIZE_PKTS_VL_UPPER_OUT_OVERSIZE_PKTS_VL_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_VLAN_STATS_EGR_OUT_OVERSIZE_PKTS_VL_UPPER_OUT_OVERSIZE_PKTS_VL_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_VLAN_STATS_EGR_OUT_OVERSIZE_PKTS_VL_UPPER_OUT_OVERSIZE_PKTS_VL_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a MACSEC_EGR:GLOBAL_STATS_EGR
 *
 * Global egress statistics registers
 */


/** 
 * \brief global.TransformErrorPkts - lower 32 bits
 *
 * \details
 * TransformErrorPkts: Drop due to internal errors in MACsec core.
 *
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:TRANSFORM_ERR_PKTS_LOWER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_TRANSFORM_ERR_PKTS_LOWER  VTSS_IOREG(0x1f, 1, 0xb100)


/** 
 * \brief global.TransformErrorPkts - upper 8 bits
 *
 * \details
 * TransformErrorPkts: Drop due to internal errors in MACsec core.
 *
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:TRANSFORM_ERR_PKTS_UPPER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_TRANSFORM_ERR_PKTS_UPPER  VTSS_IOREG(0x1f, 1, 0xb101)

/** 
 * \brief
 * global.TransformErrorPkts - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_TRANSFORM_ERR_PKTS_UPPER . TRANSFORM_ERROR_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_EGR_GLOBAL_STATS_EGR_TRANSFORM_ERR_PKTS_UPPER_TRANSFORM_ERROR_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_GLOBAL_STATS_EGR_TRANSFORM_ERR_PKTS_UPPER_TRANSFORM_ERROR_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_GLOBAL_STATS_EGR_TRANSFORM_ERR_PKTS_UPPER_TRANSFORM_ERROR_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.OutPktsCtrl - lower 32 bits
 *
 * \details
 * OutPktsCtrl: Egress packet was classified as a control packet.
 *
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:OUT_PKTS_CTRL_LOWER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_CTRL_LOWER  VTSS_IOREG(0x1f, 1, 0xb102)


/** 
 * \brief global.OutPktsCtrl - upper 8 bits
 *
 * \details
 * OutPktsCtrl: Egress packet was classified as a control packet.
 *
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:OUT_PKTS_CTRL_UPPER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_CTRL_UPPER  VTSS_IOREG(0x1f, 1, 0xb103)

/** 
 * \brief
 * global.OutPktsCtrl - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_CTRL_UPPER . OUT_PKTS_CTRL_UPPER
 */
#define  VTSS_F_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_CTRL_UPPER_OUT_PKTS_CTRL_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_CTRL_UPPER_OUT_PKTS_CTRL_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_CTRL_UPPER_OUT_PKTS_CTRL_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.OutPktsUnknownSA - lower 32 bits
 *
 * \details
 * OutPktsUnknownSA: The number of egress packets for which SA is not
 * found.
 *
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:OUT_PKTS_UNKNOWN_SA_LOWER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNKNOWN_SA_LOWER  VTSS_IOREG(0x1f, 1, 0xb104)


/** 
 * \brief global.OutPktsUnknownSA - upper 8 bits
 *
 * \details
 * OutPktsUnknownSA: The number of egress packets for which SA is not
 * found.
 *
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:OUT_PKTS_UNKNOWN_SA_UPPER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNKNOWN_SA_UPPER  VTSS_IOREG(0x1f, 1, 0xb105)

/** 
 * \brief
 * global.OutPktsUnknownSA - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNKNOWN_SA_UPPER . OUT_PKTS_UNKNOWN_SA_UPPER
 */
#define  VTSS_F_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNKNOWN_SA_UPPER_OUT_PKTS_UNKNOWN_SA_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNKNOWN_SA_UPPER_OUT_PKTS_UNKNOWN_SA_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNKNOWN_SA_UPPER_OUT_PKTS_UNKNOWN_SA_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.OutPktsUntagged - lower 32 bits
 *
 * \details
 * OutPktsUntagged: The number of transmitted packets without the MAC
 * security tag (SecTAG) because ProtectFramesEnable is configured as
 * false.
 *
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:OUT_PKTS_UNTAGGED_LOWER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNTAGGED_LOWER  VTSS_IOREG(0x1f, 1, 0xb106)


/** 
 * \brief global.OutPktsUntagged - upper 8 bits
 *
 * \details
 * OutPktsUntagged: The number of transmitted packets without the MAC
 * security tag (SecTAG) because ProtectFramesEnable is configured as
 * false.
 *
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:OUT_PKTS_UNTAGGED_UPPER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNTAGGED_UPPER  VTSS_IOREG(0x1f, 1, 0xb107)

/** 
 * \brief
 * global.OutPktsUntagged - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNTAGGED_UPPER . OUT_PKTS_UNTAGGED_UPPER
 */
#define  VTSS_F_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNTAGGED_UPPER_OUT_PKTS_UNTAGGED_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNTAGGED_UPPER_OUT_PKTS_UNTAGGED_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNTAGGED_UPPER_OUT_PKTS_UNTAGGED_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.OutOverSizePkts (MTU check) - lower 32 bits
 *
 * \details
 * OutOverSizePkts: Number of outgoing frames without VLAN_VALID which are
 * detected OverSize due to NON VLAN MTU check.
 *
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:OUT_OVERSIZE_PKTS_LOWER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_OVERSIZE_PKTS_LOWER  VTSS_IOREG(0x1f, 1, 0xb108)


/** 
 * \brief global.OutOverSizePkts (MTU check) - upper 8 bits
 *
 * \details
 * OutOverSizePkts: Number of outgoing frames without VLAN_VALID which are
 * detected OverSize due to NON VLAN MTU check.
 *
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:OUT_OVERSIZE_PKTS_UPPER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_OVERSIZE_PKTS_UPPER  VTSS_IOREG(0x1f, 1, 0xb109)

/** 
 * \brief
 * global.OutOverSizePkts (MTU check) - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_OVERSIZE_PKTS_UPPER . OUT_OVERSIZE_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_OVERSIZE_PKTS_UPPER_OUT_OVERSIZE_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_OVERSIZE_PKTS_UPPER_OUT_OVERSIZE_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_OVERSIZE_PKTS_UPPER_OUT_OVERSIZE_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.ifOutUcastPkts - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:IF_OUT_UNICAST_PKTS_LOWER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_UNICAST_PKTS_LOWER  VTSS_IOREG(0x1f, 1, 0xb10a)


/** 
 * \brief global.ifOutUcastPkts - upper 8 bits
 *
 * \details
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:IF_OUT_UNICAST_PKTS_UPPER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_UNICAST_PKTS_UPPER  VTSS_IOREG(0x1f, 1, 0xb10b)

/** 
 * \brief
 * global.ifOutUcastPkts - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_UNICAST_PKTS_UPPER . IF_OUT_UNICAST_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_UNICAST_PKTS_UPPER_IF_OUT_UNICAST_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_UNICAST_PKTS_UPPER_IF_OUT_UNICAST_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_UNICAST_PKTS_UPPER_IF_OUT_UNICAST_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.ifOutMulticastPkts - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:IF_OUT_MULTICAST_PKTS_LOWER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_MULTICAST_PKTS_LOWER  VTSS_IOREG(0x1f, 1, 0xb10c)


/** 
 * \brief global.ifOutMulticastPkts - upper 8 bits
 *
 * \details
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:IF_OUT_MULTICAST_PKTS_UPPER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_MULTICAST_PKTS_UPPER  VTSS_IOREG(0x1f, 1, 0xb10d)

/** 
 * \brief
 * global.ifOutMulticastPkts - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_MULTICAST_PKTS_UPPER . IF_OUT_MULTICAST_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_MULTICAST_PKTS_UPPER_IF_OUT_MULTICAST_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_MULTICAST_PKTS_UPPER_IF_OUT_MULTICAST_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_MULTICAST_PKTS_UPPER_IF_OUT_MULTICAST_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.ifOutBroadcastPkts - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:IF_OUT_BROADCAST_PKTS_LOWER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_BROADCAST_PKTS_LOWER  VTSS_IOREG(0x1f, 1, 0xb10e)


/** 
 * \brief global.ifOutBroadcastPkts - upper 8 bits
 *
 * \details
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:IF_OUT_BROADCAST_PKTS_UPPER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_BROADCAST_PKTS_UPPER  VTSS_IOREG(0x1f, 1, 0xb10f)

/** 
 * \brief
 * global.ifOutBroadcastPkts - upper 8 bits of the 40-bit counter.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_BROADCAST_PKTS_UPPER . IF_OUT_BROADCAST_PKTS_UPPER
 */
#define  VTSS_F_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_BROADCAST_PKTS_UPPER_IF_OUT_BROADCAST_PKTS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_BROADCAST_PKTS_UPPER_IF_OUT_BROADCAST_PKTS_UPPER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_BROADCAST_PKTS_UPPER_IF_OUT_BROADCAST_PKTS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief global.ifOutOctets - lower 32 bits
 *
 * \details
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:IF_OUT_OCTETS_LOWER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_OCTETS_LOWER  VTSS_IOREG(0x1f, 1, 0xb110)


/** 
 * \brief global.ifOutOctets - upper 32 bits
 *
 * \details
 * Register: \a MACSEC_EGR:GLOBAL_STATS_EGR:IF_OUT_OCTETS_UPPER
 */
#define VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_IF_OUT_OCTETS_UPPER  VTSS_IOREG(0x1f, 1, 0xb111)

/**
 * Register Group: \a MACSEC_EGR:CNTR_CTRL_DEBUG_REGS
 *
 * Statistics counters, control, and debug registers
 */


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_EGR:CNTR_CTRL_DEBUG_REGS:COUNT_DEBUG1
 */
#define VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1  VTSS_IOREG(0x1f, 1, 0xb200)

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
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1 . SA_INCREMENT_MASK
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1_SA_INCREMENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1_SA_INCREMENT_MASK     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1_SA_INCREMENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

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
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1 . SA_OCTET_INCREMENT
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1_SA_OCTET_INCREMENT(x)  VTSS_ENCODE_BITFIELD(x,16,15)
#define  VTSS_M_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1_SA_OCTET_INCREMENT     VTSS_ENCODE_BITMASK(16,15)
#define  VTSS_X_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG1_SA_OCTET_INCREMENT(x)  VTSS_EXTRACT_BITFIELD(x,16,15)


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_EGR:CNTR_CTRL_DEBUG_REGS:COUNT_DEBUG2
 */
#define VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2  VTSS_IOREG(0x1f, 1, 0xb201)

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
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2 . VLAN_INCREMENT_MASK
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2_VLAN_INCREMENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2_VLAN_INCREMENT_MASK     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2_VLAN_INCREMENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

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
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2 . VLAN_OCTET_INCREMENT
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2_VLAN_OCTET_INCREMENT(x)  VTSS_ENCODE_BITFIELD(x,16,15)
#define  VTSS_M_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2_VLAN_OCTET_INCREMENT     VTSS_ENCODE_BITMASK(16,15)
#define  VTSS_X_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG2_VLAN_OCTET_INCREMENT(x)  VTSS_EXTRACT_BITFIELD(x,16,15)


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_EGR:CNTR_CTRL_DEBUG_REGS:COUNT_DEBUG3
 */
#define VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG3  VTSS_IOREG(0x1f, 1, 0xb202)

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
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG3 . GLOBAL_INCREMENT_MASK
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG3_GLOBAL_INCREMENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG3_GLOBAL_INCREMENT_MASK     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG3_GLOBAL_INCREMENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_EGR:CNTR_CTRL_DEBUG_REGS:COUNT_DEBUG4
 */
#define VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4  VTSS_IOREG(0x1f, 1, 0xb203)

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
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4 . SA_TEST
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_SA_TEST  VTSS_BIT(0)

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
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4 . VLAN_TEST
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_VLAN_TEST  VTSS_BIT(1)

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
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4 . GLOBAL_TEST
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_GLOBAL_TEST  VTSS_BIT(2)

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
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4 . SA_NR
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_SA_NR(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_SA_NR     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_SA_NR(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * READING: Indicates the VLAN user priority used for VLAN-related counters
 * that were incremented for the last packet that passed through. 
 * WRITING: The written value is the VLAN user priority for a test of the
 * VLAN-related counters in the module.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4 . VLAN_UP
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_VLAN_UP(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_VLAN_UP     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_VLAN_UP(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * When reading, indicates the octet increment value for global octet
 * counters that were incremented for the last packet that passed through
 * the MACsec block. If more than one global octet counter was incremented,
 * they all used this value. When writing, the written value is the octet
 * increment for global octet counters for a test of the counters module.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4 . GLOBAL_OCTET_INCREMENT
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_GLOBAL_OCTET_INCREMENT(x)  VTSS_ENCODE_BITFIELD(x,16,15)
#define  VTSS_M_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_GLOBAL_OCTET_INCREMENT     VTSS_ENCODE_BITMASK(16,15)
#define  VTSS_X_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_DEBUG4_GLOBAL_OCTET_INCREMENT(x)  VTSS_EXTRACT_BITFIELD(x,16,15)


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_EGR:CNTR_CTRL_DEBUG_REGS:COUNT_CONTROL
 */
#define VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL  VTSS_IOREG(0x1f, 1, 0xb204)

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
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL . RESET_ALL
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_RESET_ALL  VTSS_BIT(0)

/** 
 * \brief
 * 1b: Enable normal read/write access to the counter memory for debugging
 * purposes (reset_all has priority). In this mode, increment operation
 * requests (as well as test increment requests made via the COUNT_DEBUG4
 * register) are ignored and clear-on-read is suppressed.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL . DEBUG_ACCESS
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_DEBUG_ACCESS  VTSS_BIT(1)

/** 
 * \details 
 * 0b: Counters wrap back to zero on overflow
 * 1b: Counters do not increment past maximum value 
 *
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL . SATURATE_CNTRS
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_SATURATE_CNTRS  VTSS_BIT(2)

/** 
 * \details 
 * 0b: Reading counters does not change them
 * 1b: Counters are cleared on a read access
 *
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL . AUTO_CNTR_RESET
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_AUTO_CNTR_RESET  VTSS_BIT(3)


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_EGR:CNTR_CTRL_DEBUG_REGS:COUNT_INCEN1
 */
#define VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1  VTSS_IOREG(0x1f, 1, 0xb205)

/** 
 * \brief
 * SA increment enable
 * Controls which SA related counters may be incremented. The default (1b)
 * enables all available counters. The order of the counter enable bits
 * follows that of the sa_increment_mask field in the COUNT_DEBUG1
 * register. 
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1 . SA_INCREMENT_ENABLE
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1_SA_INCREMENT_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1_SA_INCREMENT_ENABLE     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1_SA_INCREMENT_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/** 
 * \brief
 * VLAN increment enable
 * Controls which of the VLAN-related counters may be incremented. The
 * default (1b) enables all available counters. The order of the counter
 * enable bits follows that of the vlan_increment_mask field in the
 * COUNT_DEBUG2 register. 
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1 . VLAN_INCREMENT_ENABLE
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1_VLAN_INCREMENT_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1_VLAN_INCREMENT_ENABLE     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN1_VLAN_INCREMENT_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,16,5)


/** 
 * \brief Counter control and debug register
 *
 * \details
 * Register: \a MACSEC_EGR:CNTR_CTRL_DEBUG_REGS:COUNT_INCEN2
 */
#define VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN2  VTSS_IOREG(0x1f, 1, 0xb206)

/** 
 * \brief
 * Global increment enable
 * Controls which of the global counters may be incremented. The default
 * (1b) enables all available counters. The order of the counter enable
 * bits follows that of the global_increment_mask field in the COUNT_DEBUG3
 * register. 
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN2 . GLOBAL_INCREMENT_ENABLE
 */
#define  VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN2_GLOBAL_INCREMENT_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN2_GLOBAL_INCREMENT_ENABLE     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_INCEN2_GLOBAL_INCREMENT_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * Register Group: \a MACSEC_EGR:POST_PROC_CTL_DEBUG_REGS
 *
 * Output post processor control and debug registers
 */


/** 
 * \brief VLAN MTU check register
 *
 * \details
 * Register: \a MACSEC_EGR:POST_PROC_CTL_DEBUG_REGS:VLAN_MTU_CHECK
 *
 * @param ri Register: VLAN_MTU_CHECK, 0-7
 */
#define VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK(ri)  VTSS_IOREG(0x1f, 1, 0xbc40 | (ri))

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
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK . MTU_COMPARE
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK_MTU_COMPARE(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK_MTU_COMPARE     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK_MTU_COMPARE(x)  VTSS_EXTRACT_BITFIELD(x,0,15)

/** 
 * \brief
 * 1b = drop (by corrupting the CRC) VLAN packets with a user priority
 * matching the number indicated in the register name that are longer than
 * the maximum packet size defined by the mtu_compare field.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK . MTU_COMP_DROP
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK_MTU_COMP_DROP  VTSS_BIT(15)


/** 
 * \brief Non VLAN MTU check register
 *
 * \details
 * Register: \a MACSEC_EGR:POST_PROC_CTL_DEBUG_REGS:NON_VLAN_MTU_CHECK
 */
#define VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK  VTSS_IOREG(0x1f, 1, 0xbc48)

/** 
 * \brief
 * Maximum packet size (in bytes) allowed for all non-VLAN packets. Default
 * value 1514 (decimal, or 0x05EA) allows standard Ethernet frames (without
 * CRC) without a VLAN tag. Packets longer than the value programmed here
 * will be counted as oversized. packets and can optionally be truncated
 * and dropped under control of the mtu_comp_drop bit.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK . NV_MTU_COMPARE
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMPARE(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMPARE     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMPARE(x)  VTSS_EXTRACT_BITFIELD(x,0,15)

/** 
 * \brief
 * 1b = drop (by corrupting the CRC) all non-VLAN packets that are longer
 * than the maximum packet size defined by the mtu_compare field.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK . NV_MTU_COMP_DROP
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMP_DROP  VTSS_BIT(15)


/** 
 * \brief Security fail and error mask registers
 *
 * \details
 * Register: \a MACSEC_EGR:POST_PROC_CTL_DEBUG_REGS:COUNT_SECFAIL1
 */
#define VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1  VTSS_IOREG(0x1f, 1, 0xbc49)

/** 
 * \brief
 * This mask specifies which SA-related counter increments are regarded a
 * security fail event bit 
 * [0] is for the first 40-bits counter of an SA-related counter set. The
 * upper 40-bits counters of an octet counter should not have their mask
 * bit set here. 
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1 . SA_SECFAIL_MASK
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_SA_SECFAIL_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_SA_SECFAIL_MASK     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_SA_SECFAIL_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/** 
 * \details 
 * 0b: Do not update any VLAN counters for a non-VLAN packet
 * 1b: Update VLAN counters for non-VLAN packets using the default user
 * priority assigned to them
 *
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1 . VLAN_CNTR_UPDATE
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_VLAN_CNTR_UPDATE  VTSS_BIT(15)

/** 
 * \brief
 * Mask for MACsec crypto-core first result token word bits [31:17] these
 * are the error bits of that module's processing. The default value
 * selects the errors that are deemed fatal. Do not change the contents of
 * this field.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1 . ERROR_MASK
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_ERROR_MASK(x)  VTSS_ENCODE_BITFIELD(x,17,15)
#define  VTSS_M_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_ERROR_MASK     VTSS_ENCODE_BITMASK(17,15)
#define  VTSS_X_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL1_ERROR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,17,15)


/** 
 * \brief Security fail and error mask registers
 *
 * \details
 * Register: \a MACSEC_EGR:POST_PROC_CTL_DEBUG_REGS:COUNT_SECFAIL2
 */
#define VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL2  VTSS_IOREG(0x1f, 1, 0xbc4a)

/** 
 * \brief
 * This mask specifies which global counter increments are regarded a
 * security fail event bit [0] is for the first 40-bits global counter. The
 * upper 40-bits counters of an octet counter should not have their mask
 * bit set here.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL2 . GLOBAL_SECFAIL_MASK
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL2_GLOBAL_SECFAIL_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL2_GLOBAL_SECFAIL_MASK     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_COUNT_SECFAIL2_GLOBAL_SECFAIL_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/** 
 * \brief Post Processor control register
 *
 * \details
 * Register: \a MACSEC_EGR:POST_PROC_CTL_DEBUG_REGS:PP_CTRL
 */
#define VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_PP_CTRL  VTSS_IOREG(0x1f, 1, 0xbc4b)

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
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_PP_CTRL . MACSEC_OCTET_INCR_MODE
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_PP_CTRL_MACSEC_OCTET_INCR_MODE  VTSS_BIT(0)


/** 
 * \brief First word of result token word
 *
 * \details
 * Register: \a MACSEC_EGR:POST_PROC_CTL_DEBUG_REGS:CRYPTO_RESULT_DEBUG_0
 */
#define VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_CRYPTO_RESULT_DEBUG_0  VTSS_IOREG(0x1f, 1, 0xbc4c)


/** 
 * \brief Second word of result token word
 *
 * \details
 * Register: \a MACSEC_EGR:POST_PROC_CTL_DEBUG_REGS:CRYPTO_RESULT_DEBUG_1
 */
#define VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_CRYPTO_RESULT_DEBUG_1  VTSS_IOREG(0x1f, 1, 0xbc4d)


/** 
 * \brief Third word of result token word
 *
 * \details
 * Register: \a MACSEC_EGR:POST_PROC_CTL_DEBUG_REGS:CRYPTO_RESULT_DEBUG_2
 */
#define VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_CRYPTO_RESULT_DEBUG_2  VTSS_IOREG(0x1f, 1, 0xbc4e)


/** 
 * \brief Crypto debug counter
 *
 * \details
 * Register: \a MACSEC_EGR:POST_PROC_CTL_DEBUG_REGS:CRYPTO_DEBUG_CNTR
 */
#define VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_CRYPTO_DEBUG_CNTR  VTSS_IOREG(0x1f, 1, 0xbc4f)

/** 
 * \brief
 * General packet counter incremented for each packet offered to the
 * ingress-side MACsec crypto engine. Simply wraps back to zero on overflow
 * and is not influenced by reads or writes. 

 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_CRYPTO_DEBUG_CNTR . PACKET_COUNT
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_CRYPTO_DEBUG_CNTR_PACKET_COUNT(x)  VTSS_ENCODE_BITFIELD(x,0,31)
#define  VTSS_M_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_CRYPTO_DEBUG_CNTR_PACKET_COUNT     VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_X_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_CRYPTO_DEBUG_CNTR_PACKET_COUNT(x)  VTSS_EXTRACT_BITFIELD(x,0,31)

/** 
 * \brief
 * Indicates the ResultAction as determined by the post-processing
 * algorithm for the last packet that passed through the MACsec IP.
 *
 * \details 
 * 0b: PKT_DROP
 * 1b: PKT_PASS
 *
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_CRYPTO_DEBUG_CNTR . PP_RESULTACTION
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_CRYPTO_DEBUG_CNTR_PP_RESULTACTION  VTSS_BIT(31)


/** 
 * \brief Post processing drop enable
 *
 * \details
 * Low-level control of the post-processor drop decision logic
 *
 * Register: \a MACSEC_EGR:POST_PROC_CTL_DEBUG_REGS:DBG_PP_DROP_ENABLE
 */
#define VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_ENABLE  VTSS_IOREG(0x1f, 1, 0xbc50)

/** 
 * \brief
 * Drop decision control from the direction-independent processing
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_ENABLE . GL_DROP_ENABLE
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_ENABLE_GL_DROP_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_ENABLE_GL_DROP_ENABLE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_ENABLE_GL_DROP_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/** 
 * \brief
 * Drop decision control during egress MACsec processing
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_ENABLE . EG_DROP_ENABLE
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_ENABLE_EG_DROP_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_ENABLE_EG_DROP_ENABLE     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_ENABLE_EG_DROP_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Drop decision control during ingress MACsec processing
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_ENABLE . IG_DROP_ENABLE
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_ENABLE_IG_DROP_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_ENABLE_IG_DROP_ENABLE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_ENABLE_IG_DROP_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)


/** 
 * \brief Post processing drop status
 *
 * \details
 * Low-level status of the post-processor drop decision logic before gating
 * with the corresponding enable signals.
 *
 * Register: \a MACSEC_EGR:POST_PROC_CTL_DEBUG_REGS:DBG_PP_DROP_STATUS
 */
#define VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS  VTSS_IOREG(0x1f, 1, 0xbc51)

/** 
 * \brief
 * Drop decision status from the direction-independent processing
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS . GL_DROP_FLAGS
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS_GL_DROP_FLAGS(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS_GL_DROP_FLAGS     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS_GL_DROP_FLAGS(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/** 
 * \brief
 * Drop decision status during egress MACsec processing
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS . EG_DROP_FLAGS
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS_EG_DROP_FLAGS(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS_EG_DROP_FLAGS     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS_EG_DROP_FLAGS(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Drop decision status during ingress MACsec processing
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS . IG_DROP_FLAGS
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS_IG_DROP_FLAGS(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS_IG_DROP_FLAGS     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS_IG_DROP_FLAGS(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Drop decision output:
 * Bit [29] - set to 1 the pkt_tx_pkt_err signal
 * Bit [30] - set to 1 the pkt_tx_crc_err signal
 * Bit [31] - set to 1 the pkt_tx_sec_fail signal
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS . RES_OUT
 */
#define  VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS_RES_OUT(x)  VTSS_ENCODE_BITFIELD(x,29,3)
#define  VTSS_M_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS_RES_OUT     VTSS_ENCODE_BITMASK(29,3)
#define  VTSS_X_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_DBG_PP_DROP_STATUS_RES_OUT(x)  VTSS_EXTRACT_BITFIELD(x,29,3)

/**
 * Register Group: \a MACSEC_EGR:ADV_INTR_CTRL_REGS
 *
 * Advanced interrupt controller registers
 */


/** 
 * \brief AIC input polarity control
 *
 * \details
 * Register: \a MACSEC_EGR:ADV_INTR_CTRL_REGS:AIC_POL_CTRL
 */
#define VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_POL_CTRL  VTSS_IOREG(0x1f, 1, 0xbe00)

/** 
 * \brief
 * Individual polarity control. bits per interrupt input
 *
 * \details 
 * 0b: Low level or falling edge 
 * 1b: High level or rising edge (all bits fixed to this value) 
 *
 * Field: VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_POL_CTRL . POLARITY_CONTROL
 */
#define  VTSS_F_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_POL_CTRL_POLARITY_CONTROL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_POL_CTRL_POLARITY_CONTROL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_POL_CTRL_POLARITY_CONTROL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief AIC input type control
 *
 * \details
 * Register: \a MACSEC_EGR:ADV_INTR_CTRL_REGS:AIC_TYPE_CTRL
 */
#define VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_TYPE_CTRL  VTSS_IOREG(0x1f, 1, 0xbe01)

/** 
 * \brief
 * Individual type control. bits per interrupt input
 *
 * \details 
 * 0b: Level 
 * 1b: Edge detect (all bits are fixed to this value) 
 *
 * Field: VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_TYPE_CTRL . TYPE_CONTROL
 */
#define  VTSS_F_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_TYPE_CTRL_TYPE_CONTROL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_TYPE_CTRL_TYPE_CONTROL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_TYPE_CTRL_TYPE_CONTROL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief AIC interrupt enable control
 *
 * \details
 * Register: \a MACSEC_EGR:ADV_INTR_CTRL_REGS:AIC_ENABLE_CTRL
 */
#define VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CTRL  VTSS_IOREG(0x1f, 1, 0xbe02)

/** 
 * \brief
 * Individual enable control. bits per interrupt input
 *
 * \details 
 * 0b: Disabled 
 * 1b: Enabled 
 *
 * Field: VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CTRL . ENABLE_CONTROL
 */
#define  VTSS_F_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CTRL_ENABLE_CONTROL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CTRL_ENABLE_CONTROL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CTRL_ENABLE_CONTROL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief AIC raw interrupt pending status
 *
 * \details
 * Register: \a MACSEC_EGR:ADV_INTR_CTRL_REGS:AIC_RAW_STAT
 */
#define VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_RAW_STAT  VTSS_IOREG(0x1f, 1, 0xbe03)

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
 * Field: VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_RAW_STAT . RAW_STATUS
 */
#define  VTSS_F_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_RAW_STAT_RAW_STATUS(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_RAW_STAT_RAW_STATUS     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_RAW_STAT_RAW_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief AIC masked interrupt pending status
 *
 * \details
 * Register: \a MACSEC_EGR:ADV_INTR_CTRL_REGS:AIC_ENABLED_STAT
 */
#define VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLED_STAT  VTSS_IOREG(0x1f, 1, 0xbe04)

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
 * Field: VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLED_STAT . ENABLED_STATUS
 */
#define  VTSS_F_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLED_STAT_ENABLED_STATUS(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLED_STAT_ENABLED_STATUS     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLED_STAT_ENABLED_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief AIC interrupt disable 
 *
 * \details
 * Register: \a MACSEC_EGR:ADV_INTR_CTRL_REGS:AIC_ENABLE_CLR
 */
#define VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CLR  VTSS_IOREG(0x1f, 1, 0xbe05)

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
 * Field: VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CLR . INTERRUPT_DISABLE
 */
#define  VTSS_F_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CLR_INTERRUPT_DISABLE(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CLR_INTERRUPT_DISABLE     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CLR_INTERRUPT_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief AIC module configuration 
 *
 * \details
 * Register: \a MACSEC_EGR:ADV_INTR_CTRL_REGS:AIC_OPTIONS
 */
#define VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_OPTIONS  VTSS_IOREG(0x1f, 1, 0xbe06)

/** 
 * \brief
 * Direct indication of the number of interrupt inputs
 *
 * \details 
 * ingress: 5 interrupt inputs
 * egress: 4 interrupt inputs
 *
 * Field: VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_OPTIONS . NUMBER_OF_INPUTS
 */
#define  VTSS_F_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_OPTIONS_NUMBER_OF_INPUTS(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_OPTIONS_NUMBER_OF_INPUTS     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_OPTIONS_NUMBER_OF_INPUTS(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief AIC module version
 *
 * \details
 * Register: \a MACSEC_EGR:ADV_INTR_CTRL_REGS:AIC_VERSION
 */
#define VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_VERSION  VTSS_IOREG(0x1f, 1, 0xbe07)

/**
 * Register Group: \a MACSEC_EGR:EIP160_IP_VER_CFG_REGS
 *
 * IP version configuration registers
 */


/** 
 * \brief MACsec IP engine version and config register
 *
 * \details
 * Register: \a MACSEC_EGR:EIP160_IP_VER_CFG_REGS:EIP160_CONFIG2
 */
#define VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2  VTSS_IOREG(0x1f, 1, 0xbffd)

/** 
 * \brief
 * Number of statistics counters per Secure association (range 0 to 15)
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2 . SA_COUNTERS
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_SA_COUNTERS(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_SA_COUNTERS     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_SA_COUNTERS(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Number of statistics counters per VLAN User Priority (range 0 to 15)
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2 . VL_COUNTERS
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_VL_COUNTERS(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_VL_COUNTERS     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_VL_COUNTERS(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Number of global statistics counters (range 0 to 32)
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2 . GLOBAL_COUNTERS
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_GLOBAL_COUNTERS(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_GLOBAL_COUNTERS     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_GLOBAL_COUNTERS(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Programmable locking of counters at maximum value (1b)
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2 . SATURATE_COUNTERS
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_SATURATE_COUNTERS  VTSS_BIT(14)

/** 
 * \brief
 * Programmable enabling of statistics counters reset on read (1b)
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2 . AUTO_COUNTER_RESET
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_AUTO_COUNTER_RESET  VTSS_BIT(15)

/** 
 * \brief
 * Number of octet counters per Secure Association (1 for all
 * configurations)
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2 . SA_OCTET_CNTRS
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_SA_OCTET_CNTRS(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_SA_OCTET_CNTRS     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_SA_OCTET_CNTRS(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Number of octet counters per VLAN user priority

 *
 * \details 
 * i: 1 counter
 * e: 1 counter
 * ie: 2 counters
 *
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2 . VL_OCTET_CNTRS
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_VL_OCTET_CNTRS(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_VL_OCTET_CNTRS     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_VL_OCTET_CNTRS(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * Number of global octet counters (0 for all configurations)
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2 . GLOB_OCTET_CNTRS
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_GLOB_OCTET_CNTRS(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_GLOB_OCTET_CNTRS     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_GLOB_OCTET_CNTRS(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * Specialize the engine for ingress functionality and counters only
 *
 * \details 
 * 1b for i
 * 0b for e
 * 0b for ie
 *
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2 . INGRESS_ONLY
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_INGRESS_ONLY  VTSS_BIT(24)

/** 
 * \brief
 * Specialize the engine for egress functionality and counters only
 *
 * \details 
 * 0b for i
 * 1b for e
 * 0b for ie
 *
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2 . EGRESS_ONLY
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_EGRESS_ONLY  VTSS_BIT(25)

/** 
 * \brief
 * Header bypass
 *
 * \details 
 * 1b: Vitesse header bypass capability. This includes logic to match the
 * 2B-16B field.
 *
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2 . HEADER_BYPASS
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_HEADER_BYPASS  VTSS_BIT(26)

/** 
 * \brief
 * Tag bypass
 *
 * \details 
 * 1b: Vitesse tag bypass capability
 *
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2 . TAG_BYPASS
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG2_TAG_BYPASS  VTSS_BIT(27)


/** 
 * \brief MACsec IP engine version and config register
 *
 * \details
 * Register: \a MACSEC_EGR:EIP160_IP_VER_CFG_REGS:EIP160_CONFIG
 */
#define VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG  VTSS_IOREG(0x1f, 1, 0xbffe)

/** 
 * \brief
 * Number of Secure Association match sets and packet handling
 * configurations. 64 - 10G and 16 - 1G.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG . NR_OF_SA
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG_NR_OF_SA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG_NR_OF_SA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG_NR_OF_SA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Number of consistency check parameter sets. 64 - 10G and 16 - 1G.

 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG . NR_CONSIST_CHECKS
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG_NR_CONSIST_CHECKS(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG_NR_CONSIST_CHECKS     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG_NR_CONSIST_CHECKS(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Enable SCI and TCI/AN matching

 *
 * \details 
 * 1b for i
 * 0b for e
 * 1b for ie
 *
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG . MATCH_SCI
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_CONFIG_MATCH_SCI  VTSS_BIT(16)


/** 
 * \brief MACsec IP engine version and config register
 *
 * \details
 * Register: \a MACSEC_EGR:EIP160_IP_VER_CFG_REGS:EIP160_VERSION
 */
#define VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION  VTSS_IOREG(0x1f, 1, 0xbfff)

/** 
 * \brief
 * 8 bits binary encoded EIP number value, this is the EIP-160, so the
 * value is 0xA0
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION . EIP_NR
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_EIP_NR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_EIP_NR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_EIP_NR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Complement of bits [7:0] for EIP-number signature checking by host
 * software
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION . EIP_NR_COMPLEMENT
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_EIP_NR_COMPLEMENT(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_EIP_NR_COMPLEMENT     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_EIP_NR_COMPLEMENT(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Patch level for module hardware, starts at 0 for first release.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION . PATCH_LEVEL
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_PATCH_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_PATCH_LEVEL     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_PATCH_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Minor version of module hardware
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION . MINOR_VERSION
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_MINOR_VERSION(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_MINOR_VERSION     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_MINOR_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * Major version of module hardware
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION . MAJOR_VERSION
 */
#define  VTSS_F_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_MAJOR_VERSION(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_MAJOR_VERSION     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_MACSEC_EGR_EIP160_IP_VER_CFG_REGS_EIP160_VERSION_MAJOR_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * Register Group: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS
 *
 * MACsec crypto core control and status registers
 */


/** 
 * \brief Token control and status register
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:TOKEN_CTRL_STATUS
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS  VTSS_IOREG(0x1f, 1, 0xbd00)

/** 
 * \brief
 * Active tokens 
 * Number of tokens located in the MACsec crypto engine input and
 * pre-processing phase. The maximum is two.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . ACTIVE_TOKENS
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_ACTIVE_TOKENS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_ACTIVE_TOKENS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_ACTIVE_TOKENS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Token location available.
 * A new token can be read by the MACsec crypto engine. 
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . TOKEN_LOC_AVL
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_TOKEN_LOC_AVL  VTSS_BIT(2)

/** 
 * \brief
 * Result token available 
 * A (partial) result token is available in the MACsec crypto engine.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . RESULT_TOKEN_AVL
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_RESULT_TOKEN_AVL  VTSS_BIT(3)

/** 
 * \brief
 * Token read active 
 * A token is currently read by the MACsec crypto engine.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . TOKEN_READ_ACTIVE
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_TOKEN_READ_ACTIVE  VTSS_BIT(4)

/** 
 * \brief
 * Context cache active 
 * The context cache contains a new context.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . CTX_CACHE_ACTIVE
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_CTX_CACHE_ACTIVE  VTSS_BIT(5)

/** 
 * \brief
 * Context fetch 
 * The context cache is currently filled.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . CTX_FETCH
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_CTX_FETCH  VTSS_BIT(6)

/** 
 * \brief
 * Result context 
 * The context cache contains result context data that needs to be updated.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . RESULT_CTX
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_RESULT_CTX  VTSS_BIT(7)

/** 
 * \brief
 * Frames to be processed 
 * Indicates the remaining number of frames to be processed before the
 * processing is held. Valid in debug mode only.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . FRMS_TO_BE_PROCESSED
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_FRMS_TO_BE_PROCESSED(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_FRMS_TO_BE_PROCESSED     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_FRMS_TO_BE_PROCESSED(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Processing held idle.
 * No (part of) tokens are in the MACsec crypto engine input and
 * pre-processing phase and the MACsec crypto engine is not requesting a
 * new token since it is held.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . PROCESSING_HELD_IDLE
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_PROCESSING_HELD_IDLE  VTSS_BIT(14)

/** 
 * \brief
 * Busy 
 * Frame engine is busy (a token is read or active)
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . BUSY
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_BUSY  VTSS_BIT(15)

/** 
 * \brief
 * Interrupt pulse or level.
 * State of the interrupt output signal level or pulsed.
 *
 * \details 
 * 1: Interrupt output is a level signal.
 * 0: Interrupt output is pulsed for one clock cycle.
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . INTR_PULSE_OR_LVL
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_INTR_PULSE_OR_LVL  VTSS_BIT(17)

/** 
 * \brief
 * Debug mode 
 * Enables the MACsec crypto engine debug mode. In this mode a specific
 * number of frames can be processed while the processing can be stopped
 * after every token. 
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . DEBUG_MODE
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_DEBUG_MODE  VTSS_BIT(23)

/** 
 * \brief
 * Process N frames 
 * A fixed number of frames are processed. A write to this register
 * increments the number of frames that is processed with the written
 * value. 
 * NOTE: Ensure that the sum of process N frames and frames to be processed
 * do not exceed 63. 

 *
 * \details 
 * 0: Minimum
 * ...
 * 63: Maximum
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . PROCESS_N_FRMS
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_PROCESS_N_FRMS(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_PROCESS_N_FRMS     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_PROCESS_N_FRMS(x)  VTSS_EXTRACT_BITFIELD(x,24,6)

/** 
 * \brief
 * Hold processing 
 * Stops processing frames after the currently loaded token. Resumes
 * processing when this bit is cleared. Once the remaining frame counter
 * (frames to be processed) decrements to zero and debug mode is asserted,
 * this bit is automatically set to one.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS . HOLD_PROCESSING
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_TOKEN_CTRL_STATUS_HOLD_PROCESSING  VTSS_BIT(31)


/** 
 * \brief Protocol and algorithm enable register
 *
 * \details
 * This register allows software on the host system to determine the
 * hardware capabilities that it can access.
 *
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:PTCL_ALGO_EN
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN  VTSS_IOREG(0x1f, 1, 0xbd01)

/** 
 * \brief
 * AUTH_ONLY - A value of 1, indicates that this protocol or algorithm is
 * enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . AUTH_ONLY
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_AUTH_ONLY  VTSS_BIT(0)

/** 
 * \brief
 * ENCRYPT_ONLY - A value of 1, indicates that this protocol or algorithm
 * is enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . ENCRYPT_ONLY
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_ENCRYPT_ONLY  VTSS_BIT(1)

/** 
 * \brief
 * AUTH_ENCRYPT - A value of 1, indicates that this protocol or algorithm
 * is enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . AUTH_ENCRYPT
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_AUTH_ENCRYPT  VTSS_BIT(2)

/** 
 * \brief
 * AUTH_DECRYPT - A value of 1, indicates that this protocol or algorithm
 * is enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . AUTH_DECRYPT
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_AUTH_DECRYPT  VTSS_BIT(3)

/** 
 * \brief
 * ENCRYPT_AUTH - A value of 1, indicates that this protocol or algorithm
 * is enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . ENCRYPT_AUTH
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_ENCRYPT_AUTH  VTSS_BIT(4)

/** 
 * \brief
 * DECRYPT_AUTH - A value of 1, indicates that this protocol or algorithm
 * is enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . DECRYPT_AUTH
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_DECRYPT_AUTH  VTSS_BIT(5)

/** 
 * \brief
 * KEY_128 - A value of 1, indicates that this protocol or algorithm is
 * enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . KEY_128
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_KEY_128  VTSS_BIT(6)

/** 
 * \brief
 * KEY_256 - A value of 1, indicates that this protocol or algorithm is
 * enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . KEY_256
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_KEY_256  VTSS_BIT(7)

/** 
 * \brief
 * AES_ECB - A value of 1, indicates that this protocol or algorithm is
 * enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . AES_ECB
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_AES_ECB  VTSS_BIT(8)

/** 
 * \brief
 * AES_CBC - A value of 1, indicates that this protocol or algorithm is
 * enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . AES_CBC
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_AES_CBC  VTSS_BIT(9)

/** 
 * \brief
 * AES_CTR - A value of 1, indicates that this protocol or algorithm is
 * enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . AES_CTR
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_AES_CTR  VTSS_BIT(10)

/** 
 * \brief
 * AES_OFB - A value of 1, indicates that this protocol or algorithm is
 * enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . AES_OFB
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_AES_OFB  VTSS_BIT(11)

/** 
 * \brief
 * AES_CFB - A value of 1, indicates that this protocol or algorithm is
 * enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . AES_CFB
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_AES_CFB  VTSS_BIT(12)

/** 
 * \brief
 * AES_XCBC_MAC - A value of 1, indicates that this protocol or algorithm
 * is enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . AES_XCBC_MAC
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_AES_XCBC_MAC  VTSS_BIT(30)

/** 
 * \brief
 * GCM_HASH - A value of 1, indicates that this protocol or algorithm is
 * enabled. A value of 0 indicates that it is disabled and therefore
 * inaccessible.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN . GCM_HASH
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_PTCL_ALGO_EN_GCM_HASH  VTSS_BIT(31)


/** 
 * \brief Context size and fetching mode configuration
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:CONTEXT_CTRL
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL  VTSS_IOREG(0x1f, 1, 0xbd02)

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
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL . CTX_SIZE
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_CTX_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_CTX_SIZE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_CTX_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Select sequence number threshold mode.
 * If this value is 1b, the E8 is triggered only when the next packet
 * number equals the threshold value in the threshold register.
 * If this value is 0b, the E8 is triggered when the next packet number
 * equals or exceeds the threshold value in the threshold register.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL . THRESHOLD_MODE
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_THRESHOLD_MODE  VTSS_BIT(10)

/** 
 * \brief
 * MACsec EtherType 
 * Contains the EtherType field for MACsec. This field is inserted in the
 * SecTAG when processing a MACsec outbound token. It is reset to 0xE588
 * (EtherType 88-E5 represented in little endian format) and should not be
 * changed.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL . MACSEC_ETYPE
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_MACSEC_ETYPE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_MACSEC_ETYPE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL_MACSEC_ETYPE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Context status of the currently active frame
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:CONTEXT_STATUS
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_STATUS  VTSS_IOREG(0x1f, 1, 0xbd03)

/** 
 * \brief
 * [0] 
 * 
 * E0 
 * 
 * Frame length error: token instructions versus input or input DMA fetch 
 * 
 * [1] 
 * 
 * E1 
 * 
 * Token error: unknown token command/instruction 
 * 
 * [2] 
 * 
 * E2 
 * 
 * Frame input length error: received frame is smaller than specified input
 * 
 * packet length value 
 * 
 * [3] 
 * 
 * E3 
 * 
 * Counter overflow: 32-bit CTR in IV >= 2^32 
 * 
 * [4] 
 * 
 * E4 
 * 
 * (MACsec) Token configuration error: either the MACsec direction bit in 
 * the token does not match with the context, or the identifier bit
 * indicates the 
 * context ID must be used as identifier, but the ID is not available in
 * the 
 * context. 
 * 
 * [5] 
 * 
 * E5 
 * 
 * Invalid command/algorithm/mode/combination 
 * 
 * [6] 
 * 
 * E6 
 * 
 * Prohibited algorithm 
 * 
 * [7] 
 * 
 * E7 
 * 
 * Reserved: does not occur and is therefore always zero 
 * 
 * [8] 
 * 
 * E8 
 * 
 * Sequence number threshold overflow [informative] 
 * 
 * [9] 
 * 
 * E9 
 * 
 * Authentication failed 
 * 
 * [10] 
 * 
 * E10 
 * 
 * Inbound: Sequence number check failed 
 * Outbound: Sequence number roll-over det 
 * 
 * [11] 
 * 
 * E11 
 * 
 * Reserved: does not occur and is therefore always zero. 
 * 
 * [12] 
 * 
 * E12 
 * 
 * Reserved: does not occur and is therefore always zero. 
 * 
 * [13] 
 * 
 * E13 
 * 
 * Reserved: does not occur and is therefore always zero. 
 * 
 * [14] 
 * 
 * E14 
 * 
 * FATAL ERROR - This error cannot occur in the EIP60 
 * and is therefore 
 * always zero. 
 * 
 * [15] 
 * 
 * Reserved.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_STATUS . CURRENT_ERRORS
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_STATUS_CURRENT_ERRORS(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_STATUS_CURRENT_ERRORS     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_STATUS_CURRENT_ERRORS(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * [17:16] 
 * 
 * Number of Active Tokens 
 * 
 * The number of tokens in the pipeline, including result tokens that are 
 * available. 
 * 
 * [18] 
 * 
 * Active Context 
 * 
 * Active context indicates that a context is active in the pipeline. 
 * 
 * [19] 
 * 
 * Pipelined Context 
 * 
 * Pipelined context indicates that a context is (currently) pipelined
 * (phase between 
 * active and result). 
 * 
 * [20] 
 * 
 * Result Context 
 * 
 * If set to 1, indicates that a result context data needs to be stored.
 * Result context 
 * and next context cannot be both active. 
 * 
 * [21] 
 * 
 * Error recovery 
 * 
 * If set to 1, indicates that an existing error condition has not yet been
 * properly 
 * handled to completion. Note that the next context and data fetch can be
 * started. 
 * Also, error bits may still be active due to the previous frame. 
 * 
 * [27:22] 
 * 
 * Reserved 
 * 
 * [31:28] 
 * 
 * Input Frame Current State 
 * 
 * Next frame current state reflects the current state of the next frame.
 * It is out of the 
 * scope of this document to provide the detailed state encoding. This
 * field is read-
 * only and must be treated as reserved. 

 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_STATUS . CURRENT_STATUS
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_STATUS_CURRENT_STATUS(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_STATUS_CURRENT_STATUS     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_STATUS_CURRENT_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Interrupt control status register
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:INTR_CTRL_STATUS
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS  VTSS_IOREG(0x1f, 1, 0xbd04)

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
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS . INTR_CLR_STATUS
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS_INTR_CLR_STATUS(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS_INTR_CLR_STATUS     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS_INTR_CLR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

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
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS . INTR_ENABLE
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS_INTR_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS_INTR_ENABLE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS_INTR_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Software interrupt register
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:SOFTWARE_INTR
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_SOFTWARE_INTR  VTSS_IOREG(0x1f, 1, 0xbd05)


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
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:SEQ_NUM_THRESH
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_SEQ_NUM_THRESH  VTSS_IOREG(0x1f, 1, 0xbd08)


/** 
 * \brief Sequence number threshold lower 32 bits for 64-bit register
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:SEQ_NUM_THRESH_LOWER
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_SEQ_NUM_THRESH_LOWER  VTSS_IOREG(0x1f, 1, 0xbd09)


/** 
 * \brief Sequence number threshold upper 32 bits for 64-bit register
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:SEQ_NUM_THRESH_UPPER
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_SEQ_NUM_THRESH_UPPER  VTSS_IOREG(0x1f, 1, 0xbd0a)


/** 
 * \brief Block context updates register
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:BLOCK_CTX_UPDATE
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_BLOCK_CTX_UPDATE  VTSS_IOREG(0x1f, 1, 0xbd0c)

/** 
 * \brief
 * Block context updates 
 * If both the bit in this register and the related input bit for a frame
 * are set to one, the context update for that frame is blocked.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_BLOCK_CTX_UPDATE . BLOCK_CTX_UPDATES
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_BLOCK_CTX_UPDATE_BLOCK_CTX_UPDATES(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_BLOCK_CTX_UPDATE_BLOCK_CTX_UPDATES     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_BLOCK_CTX_UPDATE_BLOCK_CTX_UPDATES(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief NextPN autonomous update registers
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:NEXT_PN_LOWER
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_LOWER  VTSS_IOREG(0x1f, 1, 0xbd20)


/** 
 * \brief NextPN autonomous update registers
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:NEXT_PN_UPPER
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_UPPER  VTSS_IOREG(0x1f, 1, 0xbd21)


/** 
 * \brief NextPN Context ID register
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:NEXT_PN_CONTEXT_ID
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CONTEXT_ID  VTSS_IOREG(0x1f, 1, 0xbd22)


/** 
 * \brief NextPN control register
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:NEXT_PN_CTRL
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL  VTSS_IOREG(0x1f, 1, 0xbd23)

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
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL . ENABLE_UPDATE
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_ENABLE_UPDATE  VTSS_BIT(0)

/** 
 * \brief
 * This read only bit indicates if the previous update action resulted in a
 * sequence number update into the context memory. In other words the
 * programmed nextPN exceeded the current nextPN in the context record,
 * such that a context udapte was required. This bit is valid when bit [0]
 * of this register is zero (update done).
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL . NEXT_PN_WRITTEN
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_NEXT_PN_WRITTEN  VTSS_BIT(1)

/** 
 * \brief
 * This bit must be set to 1 if the nextPN is a 64-bit sequence number.
 * This bit must be written with a 0 if the nextPN is a 32-bit sequence
 * number.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL . SEQ_NUM_SIZE
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_SEQ_NUM_SIZE  VTSS_BIT(2)

/** 
 * \brief
 * This field must contain the 16B (128-bit) aligned pointer to the context
 * word containing the sequence number that must be validated and
 * potentially updated with the programmed nextPN.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL . NEXT_PN_CTX_ADDR
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_NEXT_PN_CTX_ADDR(x)  VTSS_ENCODE_BITFIELD(x,4,28)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_NEXT_PN_CTX_ADDR     VTSS_ENCODE_BITMASK(4,28)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_NEXT_PN_CTX_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,4,28)


/** 
 * \brief Crypto frame engine type register
 *
 * \details
 * This register is used to determine the available protocols and
 * algorithms. The Crypto engine revision can also be read from this
 * register.
 *
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:FRAME_ENGINE_TYPE
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE  VTSS_IOREG(0x1f, 1, 0xbdfe)

/** 
 * \brief
 * Minor hardware revision number
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . MINOR_REV
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_MINOR_REV(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_MINOR_REV     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_MINOR_REV(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Major hardware revision number
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . MAJOR_REV
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_MAJOR_REV(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_MAJOR_REV     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_MAJOR_REV(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * FPGA solution status
 *
 * \details 
 * 0b: Not optimized for FPGA implementation
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . FPGA_SOLUTION
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_FPGA_SOLUTION  VTSS_BIT(8)

/** 
 * \brief
 * S-box status (Galois field)
 *
 * \details 
 * 0b: S-boxes are not used in the AES cores
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . GF_SBOXES
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_GF_SBOXES  VTSS_BIT(9)

/** 
 * \brief
 * S-box status (lookup table)
 *
 * \details 
 * 1b: S-boxes are used in the AES cores
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . LOOKUP_SBOXES
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_LOOKUP_SBOXES  VTSS_BIT(10)

/** 
 * \brief
 * Encryption standard
 *
 * \details 
 * 1b: Only includes Advanced Encryption Standard (AES) as crypto-algorithm
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . MACSEC_AES_ONLY
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_MACSEC_AES_ONLY  VTSS_BIT(11)

/** 
 * \brief
 * AES status
 *
 * \details 
 * 1b: AES available
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . AES_PRESENT
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_AES_PRESENT  VTSS_BIT(12)

/** 
 * \brief
 * AES feedback status
 *
 * \details 
 * 0b: No feedback modes available for AES
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . AES_FB
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_AES_FB  VTSS_BIT(13)

/** 
 * \brief
 * AES speed
 * The number of AES engines operating in parallel

 *
 * \details 
 * 4: Current engine
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . AES_SPEED
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_AES_SPEED(x)  VTSS_ENCODE_BITFIELD(x,14,4)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_AES_SPEED     VTSS_ENCODE_BITMASK(14,4)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_AES_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,14,4)

/** 
 * \brief
 * AES-256 / AES-192 support
 *
 * \details 
 * 00: AES-128 bit key size supported
 * 01: AES-128 and AES 192-bit key sizes supported
 * 10: AES-128 and AES 256-bit key sizes supported
 * 11: AES-128, AES-192, and AES 256-bit key sizes supported
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . AES_192
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_AES_192  VTSS_BIT(18)

/** 
 * \brief
 * AES-256 / AES-192 support
 *
 * \details 
 * 00: AES-128 bit key size supported
 * 01: AES-128 and AES 192-bit key sizes supported
 * 10: AES-128 and AES 256-bit key sizes supported
 * 11: AES-128, AES-192, and AES 256-bit key sizes supported
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . AES_256
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_AES_256  VTSS_BIT(19)

/** 
 * \brief
 * Parameter pipeline depth
 * Width of the parameter pipeline available at the input data bus and
 * result token. The width of this parameter bus/field is always 2.
 * Therefore this value reads 2 in all configurations.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . PARAM_PIPELINE_DEPTH
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_PARAM_PIPELINE_DEPTH(x)  VTSS_ENCODE_BITFIELD(x,20,5)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_PARAM_PIPELINE_DEPTH     VTSS_ENCODE_BITMASK(20,5)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_PARAM_PIPELINE_DEPTH(x)  VTSS_EXTRACT_BITFIELD(x,20,5)

/** 
 * \brief
 * Header extension status
 * Indicates the availability of header bypass mode and tag bypass mode
 * features. Availability of these header processing features (header
 * bypass mode and tag bypass mode) and the clk_en input provides the
 * ability to stall the processing pipeline.
 *
 * \details 
 * 1: Header bypass mode and tag bypass mode are available
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . HEADER_EXTENSIONS
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_HEADER_EXTENSIONS  VTSS_BIT(26)

/** 
 * \brief
 * GHASH status
 * The GHASH core speed equals the speed required to keep up with the
 * performance of the available number of AES cores. In addition, bit [31]
 * differentiates between two GHASH core speeds, possible for a specific
 * number of AES cores.
 *
 * \details 
 * 1: GHASH available
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . GHASH
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_GHASH  VTSS_BIT(30)

/** 
 * \brief
 * GHASH speed
 * The least significant bit of the power of two to calculate the number of
 * cycles of the GHASH core.

 *
 * \details 
 * 0: One cycle GHASH core
 * 1: Two cycle GHASH core (default)
 *
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE . GHASH_SPEED
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_TYPE_GHASH_SPEED  VTSS_BIT(31)


/** 
 * \brief Crypto frame engine version register
 *
 * \details
 * Register: \a MACSEC_EGR:CRYPTO_CTRL_STATUS_REGS:FRAME_ENGINE_VERSION
 */
#define VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION  VTSS_IOREG(0x1f, 1, 0xbdff)

/** 
 * \brief
 * EIP number 
 * For the EIP62 this 8-bit value is 62, which equals 0x3E.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION . EIP_NUM
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_EIP_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_EIP_NUM     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_EIP_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Complement of EIP number 
 * 8-bit binary complement of 0x3E, which is 0xC1.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION . COMP_EIP_NUM
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_COMP_EIP_NUM(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_COMP_EIP_NUM     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_COMP_EIP_NUM(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Patch level 
 * 4-bit binary encoding of the hardware patch level. Initial release has
 * the level 0000.
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION . PATCH_LEVEL
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_PATCH_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_PATCH_LEVEL     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_PATCH_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Minor hardware revision number
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION . MINOR_REV_NUM
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_MINOR_REV_NUM(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_MINOR_REV_NUM     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_MINOR_REV_NUM(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * Major hardware revision number
 *
 * \details 
 * Field: VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION . MAJOR_REV_NUM
 */
#define  VTSS_F_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_MAJOR_REV_NUM(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_MAJOR_REV_NUM     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_FRAME_ENGINE_VERSION_MAJOR_REV_NUM(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


#endif /* _VTSS_MALIBU_REGS_MACSEC_EGR_H_ */
