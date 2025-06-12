// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU25G_REGS_PTP_PROC_H_
#define _VTSS_MALIBU25G_REGS_PTP_PROC_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a PTP_PROC
 *
 * 1588 IP block configuration and status registers
 *
 ***********************************************************************/

/**
 * Register Group: \a PTP_PROC:IP_1588_TOP_CFG_STAT
 *
 * 1588 IP control and status registers
 */


/**
 * \brief Interface control register
 *
 * \details
 * Register: \a PTP_PROC:IP_1588_TOP_CFG_STAT:INTERFACE_CTL
 */
#define VTSS_PTP_PROC_INTERFACE_CTL          VTSS_IOREG(VTSS_TO_PTP_PROC,0x9000)
#define LAN80XX_PTP_PROC_INTERFACE_CTL       LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1, 0x9000)

/**
 * \brief
 * If this bit is 0, then EGR_BYPASS is treated as a single bypass control
 * for both egress and ingress directions. If this bit is 1, then bypass
 * for individual direction is controlled by EGR_BYPASS and INGR_BYPASS.
 *
 * \details
 * 0: Single bypass control
 * 1: Separate bypass control
 *
 * Field: ::VTSS_PTP_PROC_INTERFACE_CTL . SPLIT_BYPASS
 */
#define  VTSS_F_PTP_PROC_INTERFACE_CTL_SPLIT_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PTP_PROC_INTERFACE_CTL_SPLIT_BYPASS  VTSS_BIT(7)
#define  VTSS_X_PTP_PROC_INTERFACE_CTL_SPLIT_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Clock enable for the 1588 IP block. This bit is an output of the IP and
 * can be used externally to gate the clocks to the block off when the
 * block is disabled. This bit is not used inside the IP block.
 *
 * \details
 * 0: Clocks disabled
 * 1: Clocks enabled
 *
 * Field: ::VTSS_PTP_PROC_INTERFACE_CTL . CLK_ENA
 */

#define  LAN80XX_F_PTP_PROC_INTERFACE_CTL_CLK_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_PTP_PROC_INTERFACE_CTL_CLK_ENA  LAN80XX_BIT(6)
#define  LAN80XX_X_PTP_PROC_INTERFACE_CTL_CLK_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)
/**
 * \brief
 * Indicate the HIH mode (if any) or if standard pramble is used
 *
 * \details
 * 0: No HIH, standard preamble
 * 1: HIH in preamble before the SFD
 * 2: HIH after SFD, HIH not included in the CRC
 * 3: HIH after SFD, HIH is included in the CRC
 *
 * Field: ::VTSS_PTP_PROC_INTERFACE_CTL . PREAMBLE_HIH_MODE
 */
#define  VTSS_F_PTP_PROC_INTERFACE_CTL_PREAMBLE_HIH_MODE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_PTP_PROC_INTERFACE_CTL_PREAMBLE_HIH_MODE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_PTP_PROC_INTERFACE_CTL_PREAMBLE_HIH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * When 1, the 1588 IP block in the ingress direction is bypassed. Changing
 * this bit to 0 allows 1588 processed data to flow out of the block. This
 * bit is internally registered so that it only takes effect during an IDLE
 * period in the data stream. This allows for a more seamless transition
 * from bypass to data passing modes.
 *
 * \details
 * 0 = Data mode
 * 1 = Bypass mode (Default)
 *
 * Field: ::VTSS_PTP_PROC_INTERFACE_CTL . INGR_BYPASS
 */
#define  VTSS_F_PTP_PROC_INTERFACE_CTL_INGR_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PTP_PROC_INTERFACE_CTL_INGR_BYPASS  VTSS_BIT(3)
#define  VTSS_X_PTP_PROC_INTERFACE_CTL_INGR_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

#define  LAN80XX_F_PTP_PROC_INTERFACE_CTL_INGR_BYPASS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_PTP_PROC_INTERFACE_CTL_INGR_BYPASS  LAN80XX_BIT(3)
#define  LAN80XX_X_PTP_PROC_INTERFACE_CTL_INGR_BYPASS(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)
/**
 * \brief
 * When 1, the 1588 IP block in the egress direction is bypassed. Changing
 * this bit to 0 allows 1588 processed data to flow out of the block. This
 * bit is internally registered so that it only takes effect during an IDLE
 * period in the data stream. This allows for a more seamless transition
 * from bypass to data passing modes.
 *
 * \details
 * 0 = Data mode
 * 1 = Bypass mode (Default)
 *
 * Field: ::VTSS_PTP_PROC_INTERFACE_CTL . EGR_BYPASS
 */
#define  VTSS_F_PTP_PROC_INTERFACE_CTL_EGR_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PTP_PROC_INTERFACE_CTL_EGR_BYPASS  VTSS_BIT(2)
#define  VTSS_X_PTP_PROC_INTERFACE_CTL_EGR_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

#define  LAN80XX_F_PTP_PROC_INTERFACE_CTL_EGR_BYPASS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_PTP_PROC_INTERFACE_CTL_EGR_BYPASS  LAN80XX_BIT(2)
#define  LAN80XX_X_PTP_PROC_INTERFACE_CTL_EGR_BYPASS(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)
/**
 * \brief
 * Defines the operating mode in which the attached PCS block operates
 *
 * \details
 * 0: XGMII-64
 * 1: Reserved
 * 2: GMII
 * 3: MII
 *
 * Field: ::VTSS_PTP_PROC_INTERFACE_CTL . MII_PROTOCOL
 */
#define  VTSS_F_PTP_PROC_INTERFACE_CTL_MII_PROTOCOL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_PTP_PROC_INTERFACE_CTL_MII_PROTOCOL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_PTP_PROC_INTERFACE_CTL_MII_PROTOCOL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Analyzer mode register
 *
 * \details
 * Register: \a PTP_PROC:IP_1588_TOP_CFG_STAT:ANALYZER_MODE
 */
#define VTSS_PTP_PROC_ANALYZER_MODE          VTSS_IOREG(VTSS_TO_PTP_PROC,0x9001)

/**
 * \brief
 * If this bit is 0, then INGR_ENCAP_FLOW_ENA controls both ingress and
 * egress side of encapsulations. If this bit is 1, then flows for the
 * respective direction are set by INGR_ENCAP_FLOW_ENA and
 * EGR_ENCAP_FLOW_ENA.
 *
 * \details
 * 0: Single encap flow for both directions
 * 1: Individual encap flow enables
 *
 * Field: ::VTSS_PTP_PROC_ANALYZER_MODE . SPLIT_ENCAP_FLOW
 */
#define  VTSS_F_PTP_PROC_ANALYZER_MODE_SPLIT_ENCAP_FLOW(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_PTP_PROC_ANALYZER_MODE_SPLIT_ENCAP_FLOW  VTSS_BIT(24)
#define  VTSS_X_PTP_PROC_ANALYZER_MODE_SPLIT_ENCAP_FLOW(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Defines how flow matching is performed in each encapsulation engine for
 * egress side.  Only valid values are: 111 : Strict flow for all engines.
 * 000 : Non-strict flow for all engines.
 *
 * \details
 * 0: Match any flow
 * 1: Strict matching
 *
 * Field: ::VTSS_PTP_PROC_ANALYZER_MODE . EGR_ENCAP_FLOW_MODE
 */
#define  VTSS_F_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_FLOW_MODE(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_FLOW_MODE     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_FLOW_MODE(x)  VTSS_EXTRACT_BITFIELD(x,20,3)

/**
 * \brief
 * Defines how flow matching is performed in each encapsulation engine for
 * ingress side. Only valid values are:111: Strict flow for all engines000:
 * Non-strict flow for all engines
 *
 * \details
 * 0: Match any flow
 * 1: Strict matching
 *
 * Field: ::VTSS_PTP_PROC_ANALYZER_MODE . INGR_ENCAP_FLOW_MODE
 */
#define  VTSS_F_PTP_PROC_ANALYZER_MODE_INGR_ENCAP_FLOW_MODE(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_PTP_PROC_ANALYZER_MODE_INGR_ENCAP_FLOW_MODE     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_PTP_PROC_ANALYZER_MODE_INGR_ENCAP_FLOW_MODE(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * Enables for the egress encapsulation engines. Enable bit 0, 1, and 2 are
 * for the PTP engines, respectively
 *
 * \details
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_PTP_PROC_ANALYZER_MODE . EGR_ENCAP_ENGINE_ENA
 */
#define  VTSS_F_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_ENGINE_ENA(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_ENGINE_ENA     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_ENGINE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

#define  LAN80XX_F_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_ENGINE_ENA(x)  LAN80XX_ENCODE_BITFIELD(x,4,3)
#define  LAN80XX_M_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_ENGINE_ENA     LAN80XX_ENCODE_BITMASK(4,3)
#define  LAN80XX_X_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_ENGINE_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,4,3)
/**
 * \brief
 * Enables for the egress encapsulation engines. Enable bit 0, 1, and 2 are
 * for the PTP engines, respectively
 *
 * \details
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_PTP_PROC_ANALYZER_MODE . INGR_ENCAP_ENGINE_ENA
 */
#define  VTSS_F_PTP_PROC_ANALYZER_MODE_INGR_ENCAP_ENGINE_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_PROC_ANALYZER_MODE_INGR_ENCAP_ENGINE_ENA     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_PROC_ANALYZER_MODE_INGR_ENCAP_ENGINE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

#define  LAN80XX_F_PTP_PROC_ANALYZER_MODE_INGR_ENCAP_ENGINE_ENA(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_PTP_PROC_ANALYZER_MODE_INGR_ENCAP_ENGINE_ENA     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_PTP_PROC_ANALYZER_MODE_INGR_ENCAP_ENGINE_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief Mode of the 1588
 *
 * \details
 * This register has the duplicate information for MII_MODE of
 * INTERFACE_CTL. Final mode for 1588 will be this 3-bit register ORed with
 * 2-bit MII_MODE of INTERFACE_CTL
 *
 * Register: \a PTP_PROC:IP_1588_TOP_CFG_STAT:MODE_CTL
 */
#define VTSS_PTP_PROC_MODE_CTL               VTSS_IOREG(VTSS_TO_PTP_PROC,0x9002)
#define LAN80XX_PTP_PROC_MODE_CTL            LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1, 0x9002)

/**
 * \brief
 * This register has the duplicate information for MII_MODE of
 * INTERFACE_CTL. Final mode for 1588 will be this 3-bit register ORed with
 * 2-bit MII_MODE of INTERFACE_CTL
 *
 * \details
 * 0: XGMII-64, used in M25 PCS timing mode
 * 1: XGMII-32
 * 2: GMII
 * 3: MII
 * 4: PKT_MODE, used in M25 MAC timing mode
 *
 * Field: ::VTSS_PTP_PROC_MODE_CTL . PROTOCOL_MODE
 */
#define  VTSS_F_PTP_PROC_MODE_CTL_PROTOCOL_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_PROC_MODE_CTL_PROTOCOL_MODE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_PROC_MODE_CTL_PROTOCOL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

#define  LAN80XX_F_PTP_PROC_MODE_CTL_PROTOCOL_MODE(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_PTP_PROC_MODE_CTL_PROTOCOL_MODE     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_PTP_PROC_MODE_CTL_PROTOCOL_MODE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief Version of the 1588
 *
 * \details
 * This register has the Version code.
 * The version_code register value is [Version_MSB],[Version_LSB] =
 * [0x3][0x0].
 *
 * Register: \a PTP_PROC:IP_1588_TOP_CFG_STAT:VERSION_CODE
 */
#define VTSS_PTP_PROC_VERSION_CODE           VTSS_IOREG(VTSS_TO_PTP_PROC,0x9003)
#define LAN80XX_PTP_PROC_VERSION_CODE        LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1, 0x9003)
/**
 * \brief
 * Indicates the current MSB version of IP1588
 *
 * \details
 * Field: ::VTSS_PTP_PROC_VERSION_CODE . VERSION_MSB
 */
#define  LAN80XX_F_PTP_PROC_VERSION_CODE_VERSION_MSB(x)  LAN80XX_ENCODE_BITFIELD(x,4,4)
#define  LAN80XX_M_PTP_PROC_VERSION_CODE_VERSION_MSB     LAN80XX_ENCODE_BITMASK(4,4)
#define  LAN80XX_X_PTP_PROC_VERSION_CODE_VERSION_MSB(x)  LAN80XX_EXTRACT_BITFIELD(x,4,4)




/**
 * \brief
 * Indicates the current LSB version of IP1588
 *
 * \details
 * Field: ::VTSS_PTP_PROC_VERSION_CODE . VERSION_LSB
 */
#define  LAN80xx_F_PTP_PROC_VERSION_CODE_VERSION_LSB(x)  LAN80XX_ENCODE_BITFIELD(x,0,4)
#define  LAN80XX_M_PTP_PROC_VERSION_CODE_VERSION_LSB     LAN80XX_ENCODE_BITMASK(0,4)
#define  LAN80XX_X_PTP_PROC_VERSION_CODE_VERSION_LSB(x)  LAN80XX_EXTRACT_BITFIELD(x,0,4)





/**
 * Register Group: \a PTP_PROC:INGR_IP_1588_CFG_STAT
 *
 * 1588 IP control and status registers
 */


/**
 * \brief configure operation mode in IP 1588
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_CFG_STAT:INGR_CFG_OPERATION_MODE
 */
#define LAN80XX_PTP_PROC_INGR_CFG_OPERATION_MODE  LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1, 0x9020)

/**
 * \brief
 * 1'b1 PCS retiming mode, X/25GMII interface without MacSec1'b0 MAC
 * retiming mode, Packet interface with MacSec
 *
 * \details
 * Field: ::LAN80XX_PTP_PROC_INGR_CFG_OPERATION_MODE . INGR_CFG_RETIMING_MODE
 */
#define  LAN80XX_F_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_RETIMING_MODE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_RETIMING_MODE     LAN80XX_BIT(1)
#define  LAN80XX_X_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_RETIMING_MODE(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * 1'b1 enable preemption
 *
 * \details
 * Field: ::LAN80XX_PTP_PROC_INGR_CFG_OPERATION_MODE . INGR_CFG_PREEMPTION
 */
#define  LAN80XX_F_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_PREEMPTION(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_PREEMPTION     LAN80XX_BIT(0)
#define  LAN80XX_X_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_PREEMPTION(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief 1588 IP interrupt status register
 *
 * \details
 * Status sticky conditions for the 1588 IP
 *
 * Register: \a PTP_PROC:INGR_IP_1588_CFG_STAT:INGR_INT_STATUS
 */
#define VTSS_PTP_PROC_INGR_INT_STATUS        VTSS_IOREG(VTSS_TO_PTP_PROC,0x9021)
#define LAN80XX_PTP_PROC_INGR_INT_STATUS     (0x21)

/**
 * \brief
 * When set, indicates the CRC  in MCH header of EGR frame is not correct.
 * The sticky bit should be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_MCH_CRC_ERROR_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_MCH_CRC_ERROR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_MCH_CRC_ERROR_STICKY  VTSS_BIT(17)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_MCH_CRC_ERROR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * When set, indicates that the extty field in the MCH header does not
 * match preempt frame type. The sticky bit should be reset by writing it
 * to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_MCH_EXTTY_MISMATCH_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_MCH_EXTTY_MISMATCH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_MCH_EXTTY_MISMATCH_STICKY  VTSS_BIT(16)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_MCH_EXTTY_MISMATCH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * When set, indicates an underflow in the bypass logic. The sticky bit
 * should be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_BYPASS_UNDERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_BYPASS_UNDERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_BYPASS_UNDERFLOW_STICKY  VTSS_BIT(15)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_BYPASS_UNDERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * When set, indicates either an overflow in the bypass logic or short
 * frame within 1588. Read TSP_PUSH_FLAG bit to know whether short frame
 * came by. The sticky bit should be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_BYPASS_OVERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_BYPASS_OVERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_BYPASS_OVERFLOW_STICKY  VTSS_BIT(14)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_BYPASS_OVERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * When set, indicates an underflow in the analyzer command processor. The
 * sticky bit should be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_ANA_CMD_UNDERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_ANA_CMD_UNDERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_ANA_CMD_UNDERFLOW_STICKY  VTSS_BIT(13)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_ANA_CMD_UNDERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * When set, indicates an overflow in the analyzer command processor. The
 * sticky bit should be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_ANA_CMD_OVERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_ANA_CMD_OVERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_ANA_CMD_OVERFLOW_STICKY  VTSS_BIT(12)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_ANA_CMD_OVERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * When set, indicates  a frame was processed by rewriter command before
 * SOF arrives. Increase the fifo depth. The sticky bit should be reset by
 * writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_TSP_CMD_UNDERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_TSP_CMD_UNDERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_TSP_CMD_UNDERFLOW_STICKY  VTSS_BIT(11)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_TSP_CMD_UNDERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * When set, indicates an overflow in the Timestamp command processor. The
 * sticky bit should be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_TSP_CMD_OVERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_TSP_CMD_OVERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_TSP_CMD_OVERFLOW_STICKY  VTSS_BIT(10)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_TSP_CMD_OVERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * When set, indicates an a frame was processed by analyzer command before
 * a timestamp was taken. Underflow in the Timestamp. The sticky bit should
 * be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_TSP_FIFO_UNDERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_TSP_FIFO_UNDERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_TSP_FIFO_UNDERFLOW_STICKY  VTSS_BIT(9)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_TSP_FIFO_UNDERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * When set, indicates an overflow in the Timestamp processor. More than
 * four frames within 1588. The sticky bit should be reset by writing it to
 * 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_TSP_FIFO_OVERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_TSP_FIFO_OVERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_TSP_FIFO_OVERFLOW_STICKY  VTSS_BIT(8)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_TSP_FIFO_OVERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When set indicates that a frame was received with non-zero data in the
 * reserved field. The sticky bit should be reset by writing it to 1.
 *
 * \details
 * 0 = No data in reserved field
 * 1 = Data in reserved field.
 *   Reserved Field = messageTypeSpecific
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_RSVD_NONZERO_STICKY
 */
#define  LAN80XX_F_PTP_PROC_INGR_INT_STATUS_INGR_RSVD_NONZERO_STICKY(x)  LAN80XX_ENCODE_BITFIELD((x),7,1)
#define  LAN80XX_M_PTP_PROC_INGR_INT_STATUS_INGR_RSVD_NONZERO_STICKY     LAN80XX_BIT(7)
#define  LAN80XX_X_PTP_PROC_INGR_INT_STATUS_INGR_RSVD_NONZERO_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Indicates that more than one engine has produced a match. The sticky bit
 * should be reset by writing it to 1.
 *
 * \details
 * 0: No error found
 * 1: Duplicate match found
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_ANALYZER_ERROR_STICKY
 */
#define  LAN80XX_F_PTP_PROC_INGR_INT_STATUS_INGR_ANALYZER_ERROR_STICKY(x)  LAN80XX_ENCODE_BITFIELD((x),6,1)
#define  LAN80XX_M_PTP_PROC_INGR_INT_STATUS_INGR_ANALYZER_ERROR_STICKY     LAN80XX_BIT(6)
#define  LAN80XX_X_PTP_PROC_INGR_INT_STATUS_INGR_ANALYZER_ERROR_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * When set, indicates that a preamble that was too short to modify was
 * detected in a PTP frame. Write to 1 to clear. This occurs when the
 * rewriter needs to shrink the preamble to append a timestamp but cannot
 * because the preamble is too short. A short preamble is any preamble that
 * is less than eight characters long including the XGMII /S/ character and
 * the ending SFD of 0xD5. Other preamble values are not checked, only the
 * GMII length.
 *
 * \details
 * 0: No error
 * 1: Preamble too short error
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_RW_PREAMBLE_ERR_STICKY
 */
#define  LAN80XX_F_PTP_PROC_INGR_INT_STATUS_INGR_RW_PREAMBLE_ERR_STICKY(x)  LAN80XX_ENCODE_BITFIELD((x),5,1)
#define  LAN80XX_M_PTP_PROC_INGR_INT_STATUS_INGR_RW_PREAMBLE_ERR_STICKY     LAN80XX_BIT(5)
#define  LAN80XX_X_PTP_PROC_INGR_INT_STATUS_INGR_RW_PREAMBLE_ERR_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * When set, indicates that an FCS error was detected in a PTP frame. Write
 * to 1 to clear
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_RW_FCS_ERR_STICKY
 */
#define  LAN80XX_F_PTP_PROC_INGR_INT_STATUS_INGR_RW_FCS_ERR_STICKY(x)  LAN80XX_ENCODE_BITFIELD((x),4,1)
#define  LAN80XX_M_PTP_PROC_INGR_INT_STATUS_INGR_RW_FCS_ERR_STICKY     LAN80XX_BIT(4)
#define  LAN80XX_X_PTP_PROC_INGR_INT_STATUS_INGR_RW_FCS_ERR_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * When set, indicates that the level in the Timestamp FIFO has reached the
 * threshold TS_THRESH. The sticky bit should be reset by writing it to 1.
 *
 * \details
 * 0: No overflow
 * 1: Overflow
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_TS_LEVEL_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_TS_LEVEL_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_TS_LEVEL_STICKY  VTSS_BIT(3)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_TS_LEVEL_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * When set, indicates a timestamp was captured in the Timestamp FIFO. The
 * sticky bit should be reset by writing it to 1.
 *
 * \details
 * 0: No loaded
 * 1: Loaded
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_TS_LOADED_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_TS_LOADED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_TS_LOADED_STICKY  VTSS_BIT(2)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_TS_LOADED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * When set, indicates an underflow in the Timestamp FIFO. The sticky bit
 * should be reset by writing it to 1.
 *
 * \details
 * 0: No overflow
 * 1: Overflow
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_TS_UNDERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_TS_UNDERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_TS_UNDERFLOW_STICKY  VTSS_BIT(1)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_TS_UNDERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When set, indicates an overflow in the Timestamp FIFO. The sticky bit
 * should be reset by writing it to 1.
 *
 * \details
 * 0: No overflow
 * 1: Overflow
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_STATUS . INGR_TS_OVERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_INT_STATUS_INGR_TS_OVERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_INGR_INT_STATUS_INGR_TS_OVERFLOW_STICKY  VTSS_BIT(0)
#define  VTSS_X_PTP_PROC_INGR_INT_STATUS_INGR_TS_OVERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief 1588 IP interrupt mask register
 *
 * \details
 * Masks that enable and disable the interrupts
 *
 * Register: \a PTP_PROC:INGR_IP_1588_CFG_STAT:INGR_INT_MASK
 */
#define VTSS_PTP_PROC_INGR_INT_MASK          VTSS_IOREG(VTSS_TO_PTP_PROC, 0x9022)
#define LAN80XX_PTP_PROC_INGR_INT_MASK       (0x22)
/**
 * \brief
 * Mask for MCH_CRC_ERROR_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_MCH_CRC_ERROR_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_MCH_CRC_ERROR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_MCH_CRC_ERROR_MASK  VTSS_BIT(17)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_MCH_CRC_ERROR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Mask for MCH_EXTTY_MISMATCH_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_MCH_EXTTY_MISMATCH_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_MCH_EXTTY_MISMATCH_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_MCH_EXTTY_MISMATCH_MASK  VTSS_BIT(16)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_MCH_EXTTY_MISMATCH_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Mask for BYPASS_UNDERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_BYPASS_UNDERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_BYPASS_UNDERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_BYPASS_UNDERFLOW_MASK  VTSS_BIT(15)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_BYPASS_UNDERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Mask for BYPASS_OVERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_BYPASS_OVERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_BYPASS_OVERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_BYPASS_OVERFLOW_MASK  VTSS_BIT(14)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_BYPASS_OVERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Mask for ANA_CMD_UNDERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_ANA_CMD_UNDERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_ANA_CMD_UNDERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_ANA_CMD_UNDERFLOW_MASK  VTSS_BIT(13)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_ANA_CMD_UNDERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Mask for ANA_CMD_OVERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_ANA_CMD_OVERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_ANA_CMD_OVERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_ANA_CMD_OVERFLOW_MASK  VTSS_BIT(12)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_ANA_CMD_OVERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Mask bit for TSP_CMD_UNDERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_TSP_CMD_UNDERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_TSP_CMD_UNDERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_TSP_CMD_UNDERFLOW_MASK  VTSS_BIT(11)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_TSP_CMD_UNDERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Mask bit for TSP_CMD_OVERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_TSP_CMD_OVERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_TSP_CMD_OVERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_TSP_CMD_OVERFLOW_MASK  VTSS_BIT(10)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_TSP_CMD_OVERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Mask for TSP_FIFO_UNDERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_TSP_FIFO_UNDERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_TSP_FIFO_UNDERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_TSP_FIFO_UNDERFLOW_MASK  VTSS_BIT(9)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_TSP_FIFO_UNDERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Mask bit for TSP_FIFO_OVERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_TSP_FIFO_OVERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_TSP_FIFO_OVERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_TSP_FIFO_OVERFLOW_MASK  VTSS_BIT(8)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_TSP_FIFO_OVERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Mask bit for RSVD_NONZERO_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_RSVD_NONZERO_MASK
 */
#define  LAN80XX_F_PTP_PROC_INGR_INT_MASK_INGR_RSVD_NONZERO_MASK(x)   LAN80XX_ENCODE_BITFIELD((x),7,1)
#define  LAN80XX_M_PTP_PROC_INGR_INT_MASK_INGR_RSVD_NONZERO_MASK      LAN80XX_BIT(7)
#define  LAN80XXS_X_PTP_PROC_INGR_INT_MASK_INGR_RSVD_NONZERO_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Mask bit for ANALYZER_ERROR_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_ANALYZER_ERROR_MASK
 */
#define  LAN80XX_F_PTP_PROC_INGR_INT_MASK_INGR_ANALYZER_ERROR_MASK(x)  LAN80XX_ENCODE_BITFIELD((x),6,1)
#define  LAN80XX_M_PTP_PROC_INGR_INT_MASK_INGR_ANALYZER_ERROR_MASK     LAN80XX_BIT(6)
#define  LAN80XX_X_PTP_PROC_INGR_INT_MASK_INGR_ANALYZER_ERROR_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Mask for the RW_PREAMBLE_ERR_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_RW_PREAMBLE_ERR_MASK
 */
#define  LAN80XX_F_PTP_PROC_INGR_INT_MASK_INGR_RW_PREAMBLE_ERR_MASK(x)  LAN80XX_ENCODE_BITFIELD((x),5,1)
#define  LAN80XX_M_PTP_PROC_INGR_INT_MASK_INGR_RW_PREAMBLE_ERR_MASK     LAN80XX_BIT(5)
#define  LAN80XX_X_PTP_PROC_INGR_INT_MASK_INGR_RW_PREAMBLE_ERR_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Mask for the RW_FCS_ERR_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_RW_FCS_ERR_MASK
 */
#define  LAN80XX_F_PTP_PROC_INGR_INT_MASK_INGR_RW_FCS_ERR_MASK(x)  LAN80XX_ENCODE_BITFIELD((x),4,1)
#define  LAN80XX_M_PTP_PROC_INGR_INT_MASK_INGR_RW_FCS_ERR_MASK     LAN80XX_BIT(4)
#define  LAN80XX_X_PTP_PROC_INGR_INT_MASK_INGR_RW_FCS_ERR_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Mask bit for TS_LEVEL_STICKY. When 1, the interrupt is enabled.
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_TS_LEVEL_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_TS_LEVEL_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_TS_LEVEL_MASK  VTSS_BIT(3)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_TS_LEVEL_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Mask bit for TS_LOADED_STICKY. When 1, the interrupt is enabled.
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_TS_LOADED_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_TS_LOADED_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_TS_LOADED_MASK  VTSS_BIT(2)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_TS_LOADED_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Mask bit for TS_UNDERFLOW_STICKY. When 1, the interrupt is enabled.
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_TS_UNDERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_TS_UNDERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_TS_UNDERFLOW_MASK  VTSS_BIT(1)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_TS_UNDERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Mask bit for TS_OVERFLOW_STICKY. When 1, the interrupt is enabled.
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_INT_MASK . INGR_TS_OVERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_INGR_INT_MASK_INGR_TS_OVERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_INGR_INT_MASK_INGR_TS_OVERFLOW_MASK  VTSS_BIT(0)
#define  VTSS_X_PTP_PROC_INGR_INT_MASK_INGR_TS_OVERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Egress side stall latency
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_CFG_STAT:INGR_CFG_STALL_LATENCY
 */
#define VTSS_PTP_PROC_INGR_CFG_STALL_LATENCY  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9023)

/**
 * \brief
 * Stall latency (nanoseconds) denotes the latency experienced by a PTP
 * frame when going through a MACSec block. Only needed in the egress
 * direction. When MACSec is bypassed, this latency should be configured to
 * zero. In ingress side this value is not used.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_CFG_STALL_LATENCY . INGR_CFG_STALL_LATENCY
 */
#define  VTSS_F_PTP_PROC_INGR_CFG_STALL_LATENCY_INGR_CFG_STALL_LATENCY(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_CFG_STALL_LATENCY_INGR_CFG_STALL_LATENCY     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_CFG_STALL_LATENCY_INGR_CFG_STALL_LATENCY(x)  (x)


/**
 * \brief Egress side stall latency sub-nanosecond
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_CFG_STAT:INGR_CFG_STALL_LATENCY_SNS
 */
#define VTSS_PTP_PROC_INGR_CFG_STALL_LATENCY_SNS  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9024)

/**
 * \brief
 * Stall latency (sub-nanoseconds) denotes the latency experienced by a PTP
 * frame when going through a MACSec block. Only needed in the egress
 * direction. When MACSec is bypassed, this latency should be configured to
 * zero. In ingress side this value is not used.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_CFG_STALL_LATENCY_SNS . INGR_CFG_STALL_LATENCY_SNS
 */
#define  VTSS_F_PTP_PROC_INGR_CFG_STALL_LATENCY_SNS_INGR_CFG_STALL_LATENCY_SNS(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PROC_INGR_CFG_STALL_LATENCY_SNS_INGR_CFG_STALL_LATENCY_SNS     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PROC_INGR_CFG_STALL_LATENCY_SNS_INGR_CFG_STALL_LATENCY_SNS(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a PTP_PROC:INGR_IP_1588_TSP
 *
 * 1588 IP timestamp processor
 */


/**
 * \brief TSP control
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_TSP_CTRL
 */
#define VTSS_PTP_PROC_INGR_TSP_CTRL         (0x28)
#define LAN80XX_PTP_PROC_INGR_TSP_CTRL         (0x28)
#define LAN80XX_PTP_PROC_INGR_TSP_CTRL_REG     LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1, 0x9028)

/**
 * \brief
 * specify the type of frame that can be timestamped01: e-frame10:
 * unfragmented p-frame11: both e-frame and unfragmented p-frame00: none
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSP_CTRL . INGR_TS_FRAME_TYPE
 */
#define  LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_TS_FRAME_TYPE(x)  LAN80XX_ENCODE_BITFIELD(x,11,2)
#define  LAN80XX_M_PTP_PROC_INGR_TSP_CTRL_INGR_TS_FRAME_TYPE     LAN80XX_ENCODE_BITMASK(11,2)
#define  LAN80XX_X_PTP_PROC_INGR_TSP_CTRL_INGR_TS_FRAME_TYPE(x)  LAN80XX_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * 1: MACSEC is in bypass mode0: MACSEC is not in bypass mode
 *
 * \details
 * C
 *
 * Field: ::VTSS_PTP_PROC_INGR_TSP_CTRL . INGR_MACSEC_BYPASS
 */
#define  LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_MACSEC_BYPASS(x)  LAN80XX_ENCODE_BITFIELD((x),10,1)
#define  LAN80XX_M_PTP_PROC_INGR_TSP_CTRL_INGR_MACSEC_BYPASS  LAN80XX_BIT(10)
#define  LAN80XX_X_PTP_PROC_INGR_TSP_CTRL_INGR_MACSEC_BYPASS(x)  LAN80XX_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * 1: MACSEC is enabled0: MACSEC is disabled
 *
 * \details
 * C
 *
 * Field: ::VTSS_PTP_PROC_INGR_TSP_CTRL . INGR_MACSEC_ENABLE
 */
#define  LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_MACSEC_ENABLE(x)  LAN80XX_ENCODE_BITFIELD((x),9,1)
#define  LAN80XX_M_PTP_PROC_INGR_TSP_CTRL_INGR_MACSEC_ENABLE     LAN80XX_BIT(7)
#define  LAN80XX_X_PTP_PROC_INGR_TSP_CTRL_INGR_MACSEC_ENABLE(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * 1: in 25G mode0: not in 25G mode
 *
 * \details
 * C
 *
 * Field: ::VTSS_PTP_PROC_INGR_TSP_CTRL . INGR_SPEED_25G
 */
#define  LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_SPEED_25G(x)  LAN80XX_ENCODE_BITFIELD(x,7,2)
#define  LAN80XX_M_PTP_PROC_INGR_TSP_CTRL_INGR_SPEED_25G  LAN80XX_BIT(8)
#define  LAN80XX_X_PTP_PROC_INGR_TSP_CTRL_INGR_SPEED_25G(x)  LAN80XX_EXTRACT_BITFIELD(x,7,2)

/**
 * \brief
 * 1: RSFEC  is enabled0: RSFEC  is disabled
 *
 * \details
 * C
 *
 * Field: ::VTSS_PTP_PROC_INGR_TSP_CTRL . INGR_RSFEC_ENABLE
 */
#define  LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_RSFEC_ENABLE(x)  LAN80XX_ENCODE_BITFIELD((x),6,1)
#define  LAN80XX_M_PTP_PROC_INGR_TSP_CTRL_INGR_RSFEC_ENABLE     LAN80XX_BIT(6)
#define  LAN80XX_X_PTP_PROC_INGR_TSP_CTRL_INGR_RSFEC_ENABLE(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * 1: RSFEC in full mode (Absolute time)0: RSFEC in SFB (start of FEC
 * Block)
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSP_CTRL . INGR_RSFEC_FULL_MODE
 */
#define  VTSS_F_PTP_PROC_INGR_TSP_CTRL_INGR_RSFEC_FULL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PTP_PROC_INGR_TSP_CTRL_INGR_RSFEC_FULL_MODE  VTSS_BIT(3)
#define  VTSS_X_PTP_PROC_INGR_TSP_CTRL_INGR_RSFEC_FULL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Delays the number of clock cycles to process analyzer command
 *
 * \details
 * 1=4 clocks to process analyzer command
 * 0=3 clocks to process analyzer command
 *
 * Field: ::VTSS_PTP_PROC_INGR_TSP_CTRL . INGR_DLY_FIFO_RD
 */
#define  LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_DLY_FIFO_RD(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_PTP_PROC_INGR_TSP_CTRL_INGR_DLY_FIFO_RD     LAN80XX_BIT(2)
#define  LAN80XX_X_PTP_PROC_INGR_TSP_CTRL_INGR_DLY_FIFO_RD(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Selects a mode in which the fractional portion of a second (in units of
 * nanoseconds) is used for timestamping. Only the operation of the
 * WRITE_NS, WRITE_NS_P2P, and SUB_ADD PTP commands are affected by the
 * setting of this mode bit.
 *
 * \details
 * INGR/EGR_FRACT_NS_MODE selects between the two modes
 * 0 = Selects RSVD32, counting 0 to 2^32-1 ns (0-4,294,967,295 ns)
 * 1 = Selects RSVD30, counting 0 to 10^9-1 ns (0-999,999,999 ns)
 *
 * Field: ::VTSS_PTP_PROC_INGR_TSP_CTRL . INGR_FRACT_NS_MODE
 */
#define  LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_FRACT_NS_MODE(x)  LAN80XX_ENCODE_BITFIELD((x),1,1)
#define  LAN80XX_M_PTP_PROC_INGR_TSP_CTRL_INGR_FRACT_NS_MODE     LAN80XX_BIT(1)
#define  LAN80XX_X_PTP_PROC_INGR_TSP_CTRL_INGR_FRACT_NS_MODE(x)  LAN80XX_EXTRACT_BITFIELD((x),1,1)


/**
 * \brief
 * One-shot loads local latency, path delay, and DelayAsymmetry values into
 * the timestamp processor
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSP_CTRL . INGR_LOAD_DELAYS
 */
#define  VTSS_F_PTP_PROC_INGR_TSP_CTRL_INGR_LOAD_DELAYS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_F_PTP_PROC_INGR_TSP_CTRL_INGR_LOAD_DELAYS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_INGR_TSP_CTRL_INGR_LOAD_DELAYS  VTSS_BIT(0)
#define  LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_LOAD_DELAYS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)
#define  LAN80XX_M_PTP_PROC_INGR_TSP_CTRL_INGR_LOAD_DELAYS  LAN80XX_BIT(0)
#define  LAN80XX_X_PTP_PROC_INGR_TSP_CTRL_INGR_LOAD_DELAYS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TSP status
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_TSP_STAT
 */
#define VTSS_PTP_PROC_INGR_TSP_STAT          VTSS_IOREG(VTSS_TO_PTP_PROC,0x9029)

/**
 * \brief
 * Timestamp processor marked a calculated correction field as too big
 *
 * \details
 * 0: A calculated correction field that was too big did not occur
 * 1: A calculated correction field that was too big did occur
 *
 * Field: ::VTSS_PTP_PROC_INGR_TSP_STAT . INGR_CF_TOO_BIG_STICKY
 */
#define  VTSS_F_PTP_PROC_INGR_TSP_STAT_INGR_CF_TOO_BIG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_INGR_TSP_STAT_INGR_CF_TOO_BIG_STICKY  VTSS_BIT(0)
#define  VTSS_X_PTP_PROC_INGR_TSP_STAT_INGR_CF_TOO_BIG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Local latency nanosecond from TSP to RSFEC
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_LOCAL_LATENCY
 */
#define VTSS_PTP_PROC_INGR_LOCAL_LATENCY     VTSS_IOREG(VTSS_TO_PTP_PROC,0x902a)
#define LAN80XX_PTP_PROC_INGR_LOCAL_LATENCY  (0x2A)
/**
 * \brief
 * Local latency (nanoseconds)This registers indicates the nanosecond of
 * latency from TSP to PCS RSFEC module
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_LOCAL_LATENCY . INGR_LOCAL_LATENCY
 */
#define  LAN80XX_F_PTP_PROC_INGR_LOCAL_LATENCY_INGR_LOCAL_LATENCY(x)  LAN80XX_ENCODE_BITFIELD(x,0,22)
#define  LAN80XX_M_PTP_PROC_INGR_LOCAL_LATENCY_INGR_LOCAL_LATENCY     LAN80XX_ENCODE_BITMASK(0,22)
#define  LAN80XX_X_PTP_PROC_INGR_LOCAL_LATENCY_INGR_LOCAL_LATENCY(x)  LAN80XX_EXTRACT_BITFIELD(x,0,22)


/**
 * \brief Local latency sub-nanosecond from TSP to RSFEC
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_LOCAL_LATENCY_SNS
 */
#define VTSS_PTP_PROC_INGR_LOCAL_LATENCY_SNS  VTSS_IOREG(VTSS_TO_PTP_PROC,0x902b)
#define LAN80XX_PTP_PROC_INGR_LOCAL_LATENCY_SNS (0x2B)
/**
 * \brief
 * Local latency (nanoseconds).This registers indicates the fractional
 * nanosecond of latency from TSP to PCS RSFEC module
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_LOCAL_LATENCY_SNS . INGR_LOCAL_LATENCY_SNS
 */
#define  LAN80XX_F_PTP_PROC_INGR_LOCAL_LATENCY_SNS_INGR_LOCAL_LATENCY_SNS(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_PTP_PROC_INGR_LOCAL_LATENCY_SNS_INGR_LOCAL_LATENCY_SNS     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_PTP_PROC_INGR_LOCAL_LATENCY_SNS_INGR_LOCAL_LATENCY_SNS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Local latency through PCS and SERDES
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_PCS_SERDES_LOCAL_LATENCY
 */
#define LAN80XX_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY  (0x2c)
/**
 * \brief
 * Local latency (nanoseconds)This registers indicates the nanosecond of
 * latency through PCS and SERDES
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY . INGR_PS_LOCAL_LATENCY
 */
#define  LAN80XX_F_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_INGR_PS_LOCAL_LATENCY(x)  LAN80XX_ENCODE_BITFIELD(x,0,23)
#define  LAN80XX_M_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_INGR_PS_LOCAL_LATENCY     LAN80XX_ENCODE_BITMASK(0,23)
#define  LAN80XX_X_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_INGR_PS_LOCAL_LATENCY(x)  LAN80XX_EXTRACT_BITFIELD(x,0,23)


/**
 * \brief Local latency sub-nanosecond through PCS and SERDES
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_PCS_SERDES_LOCAL_LATENCY_SNS
 */
#define LAN80XX_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_SNS   (0x2D)

/**
 * \brief
 * Local latency (nanoseconds).This registers indicates the fractional
 * nanosecond of latency through PCS and SERDES
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_SNS . INGR_PS_LOCAL_LATENCY_SNS
 */
#define  LAN80XX_F_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_SNS_INGR_PS_LOCAL_LATENCY_SNS(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_SNS_INGR_PS_LOCAL_LATENCY_SNS     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_SNS_INGR_PS_LOCAL_LATENCY_SNS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Path delay
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_PATH_DELAY
 */
#define VTSS_PTP_PROC_INGR_PATH_DELAY        VTSS_IOREG(VTSS_TO_PTP_PROC,0x902e)
#define LAN80XX_PTP_PROC_INGR_PATH_DELAY     (0x2e)

/**
 * \brief
 * Path delay (nanoseconds)
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_PATH_DELAY . INGR_PATH_DELAY
 */
#define  LAN80XX_F_PTP_PROC_INGR_PATH_DELAY_INGR_PATH_DELAY(x)  (x)
#define  LAN80XX_M_PTP_PROC_INGR_PATH_DELAY_INGR_PATH_DELAY     0xffffffff
#define  LAN80XX_X_PTP_PROC_INGR_PATH_DELAY_INGR_PATH_DELAY(x)  (x)


/**
 * \brief Path delay sub-nanosecond
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_PATH_DELAY_SNS
 */
#define LAN80XX_PTP_PROC_INGR_PATH_DELAY_SNS    (0x2f)

/**
 * \brief
 * Path delay (sub-nanoseconds)
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_PATH_DELAY_SNS . INGR_PATH_DELAY_SNS
 */
#define  LAN80XX_F_PTP_PROC_INGR_PATH_DELAY_SNS_INGR_PATH_DELAY_SNS(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_PTP_PROC_INGR_PATH_DELAY_SNS_INGR_PATH_DELAY_SNS     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_PTP_PROC_INGR_PATH_DELAY_SNS_INGR_PATH_DELAY_SNS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Delay asymmetry
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_DELAY_ASYMMETRY
 */
#define VTSS_PTP_PROC_INGR_DELAY_ASYMMETRY   VTSS_IOREG(VTSS_TO_PTP_PROC,0x9030)
#define LAN80XX_PTP_PROC_INGR_DELAY_ASYMMETRY   (0x30)

/**
 * \brief
 * Delay asymmetry (scaled nanoseconds)
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_DELAY_ASYMMETRY . INGR_DELAY_ASYMMETRY
 */
#define  VTSS_F_PTP_PROC_INGR_DELAY_ASYMMETRY_INGR_DELAY_ASYMMETRY(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_DELAY_ASYMMETRY_INGR_DELAY_ASYMMETRY     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_DELAY_ASYMMETRY_INGR_DELAY_ASYMMETRY(x)  (x)


/**
 * \brief PCS RADPT disable idle drop period
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_RADPT_DROP_IDLE_PIF
 */
#define VTSS_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9031)

/**
 * \brief
 * In packet interface, the duration of no idle drop by PCS rate adapter
 * after frame is timestamped in TSP in 25G mode and with RSFEC enabled,
 * and there are two PTP frames in MACSECThe value is the number PCS clock
 * cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF . INGR_DROP_DISABLE_DURATION_STALL_3
 */
#define  VTSS_F_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF_INGR_DROP_DISABLE_DURATION_STALL_3(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF_INGR_DROP_DISABLE_DURATION_STALL_3     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF_INGR_DROP_DISABLE_DURATION_STALL_3(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * In packet interface, the duration of no idle drop by PCS rate adapter
 * after frame is timestamped in TSP in 25G mode and with RSFEC enabled,
 * and there is one PTP frame in MACSECThe value is the number PCS clock
 * cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF . INGR_DROP_DISABLE_DURATION_STALL_2
 */
#define  VTSS_F_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF_INGR_DROP_DISABLE_DURATION_STALL_2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF_INGR_DROP_DISABLE_DURATION_STALL_2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF_INGR_DROP_DISABLE_DURATION_STALL_2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * In packet interface, the duration of no idle drop by PCS rate adapter
 * after frame is timestamped in TSP in 25G mode and with RSFEC enabled,
 * and there is no PTP frame in MACSECThe value is the number PCS clock
 * cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF . INGR_DROP_DISABLE_DURATION_STALL_1
 */
#define  VTSS_F_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF_INGR_DROP_DISABLE_DURATION_STALL_1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF_INGR_DROP_DISABLE_DURATION_STALL_1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF_INGR_DROP_DISABLE_DURATION_STALL_1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * In packet interface, the duration of no idle drop by PCS rate adapter
 * after frame is timestamped in TSP in 25G mode, with RSFEC enabled, and
 * with MACSEC enabled but in bypass modeThe value is the number PCS clock
 * cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF . INGR_DROP_DISABLE_DURATION_STALL_BYPASS
 */
#define  VTSS_F_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF_INGR_DROP_DISABLE_DURATION_STALL_BYPASS(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF_INGR_DROP_DISABLE_DURATION_STALL_BYPASS     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PROC_INGR_RADPT_DROP_IDLE_PIF_INGR_DROP_DISABLE_DURATION_STALL_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief PCS RADPT disable idle drop period
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_RADPT_DROP_IDLE_XIF
 */
#define VTSS_PTP_PROC_INGR_RADPT_DROP_IDLE_XIF  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9032)

/**
 * \brief
 * In X25GMII interface, the duration of no idle drop by PCS rate adapter
 * after frame is timestamped in TSP in 25G mode and with RSFEC  enabledThe
 * value is the number PCS clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RADPT_DROP_IDLE_XIF . INGR_DROP_DISABLE_DURATION_XIF
 */
#define  VTSS_F_PTP_PROC_INGR_RADPT_DROP_IDLE_XIF_INGR_DROP_DISABLE_DURATION_XIF(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PROC_INGR_RADPT_DROP_IDLE_XIF_INGR_DROP_DISABLE_DURATION_XIF     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PROC_INGR_RADPT_DROP_IDLE_XIF_INGR_DROP_DISABLE_DURATION_XIF(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief PCS CWM insertion early notice to TSP
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_CWM_EARLY_NOTICE_PIF
 */
#define VTSS_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9033)

/**
 * \brief
 * In packet interface, PCS CWM insertion early notice to  TSP in 25G mode
 * and with RSFEC  enabled, and there are two PTP frames in MACSECThe value
 * is the number PCS clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF . INGR_CWM_EARLY_NOTICE_STALL_3
 */
#define  VTSS_F_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF_INGR_CWM_EARLY_NOTICE_STALL_3(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF_INGR_CWM_EARLY_NOTICE_STALL_3     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF_INGR_CWM_EARLY_NOTICE_STALL_3(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * In packet interface, PCS CWM insertion early notice to  TSP in 25G mode
 * and with RSFEC  enabled, and there is one PTP frame in MACSECThe value
 * is the number PCS clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF . INGR_CWM_EARLY_NOTICE_STALL_2
 */
#define  VTSS_F_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF_INGR_CWM_EARLY_NOTICE_STALL_2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF_INGR_CWM_EARLY_NOTICE_STALL_2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF_INGR_CWM_EARLY_NOTICE_STALL_2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * In packet interface, PCS CWM insertion early notice to  TSP in 25G mode
 * and with RSFEC  enabled, and there is no PTP frame in MACSECThe value is
 * the number PCS clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF . INGR_CWM_EARLY_NOTICE_STALL_1
 */
#define  VTSS_F_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF_INGR_CWM_EARLY_NOTICE_STALL_1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF_INGR_CWM_EARLY_NOTICE_STALL_1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF_INGR_CWM_EARLY_NOTICE_STALL_1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * In packet interface, PCS CWM insertion early notice to  TSP in 25G mode,
 * with RSFEC  enabled, and with MACSEC enabled but in bypass modeThe value
 * is the number PCS clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF . INGR_CWM_EARLY_NOTICE_STALL_BYPASS
 */
#define  VTSS_F_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF_INGR_CWM_EARLY_NOTICE_STALL_BYPASS(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF_INGR_CWM_EARLY_NOTICE_STALL_BYPASS     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PROC_INGR_CWM_EARLY_NOTICE_PIF_INGR_CWM_EARLY_NOTICE_STALL_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief PCS CWM insertion early notice to TSP
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_CWM_EARLY_NOTICE_XIF
 */
#define VTSS_PTP_PROC_INGR_CWM_EARLY_NOTICE_XIF  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9034)

/**
 * \brief
 * In X25GMII interface, PCS CWM insertion early notice to  TSP in 25G mode
 * and with RSFEC  enabledThe value is the number PCS clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_CWM_EARLY_NOTICE_XIF . INGR_CWM_EARLY_NOTICE_XIF
 */
#define  VTSS_F_PTP_PROC_INGR_CWM_EARLY_NOTICE_XIF_INGR_CWM_EARLY_NOTICE_XIF(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PROC_INGR_CWM_EARLY_NOTICE_XIF_INGR_CWM_EARLY_NOTICE_XIF     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PROC_INGR_CWM_EARLY_NOTICE_XIF_INGR_CWM_EARLY_NOTICE_XIF(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief delay 32 bit or 34 bit by the SOF position
 *
 * \details
 * A SOF is seen on the pcs output. If the shift input is asserted, it
 * means that only 4 bytes has been transferred so far, and we must
 * reduce the delay 32-34 bit times, depending on how it should regarded
 * that a 66 bit word has a frames staring after 34 bit times (two
 * control bits, and 64 data bits in each word). The 32-34 is selected
 * by a configuration input.

 *
 * Register: \a PTP_PROC:INGR_IP_1588_TSP:INGR_PCS_PREDICTOR_CTRL
 */
#define VTSS_PTP_PROC_INGR_PCS_PREDICTOR_CTRL  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9035)

/**
 * \brief
 * When pcs_shift is true or SOF is at lane-4,  the value of bit delay can
 * be specified.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_PCS_PREDICTOR_CTRL . INGR_TX_PCS_SHIFT_CFG
 */
#define  VTSS_F_PTP_PROC_INGR_PCS_PREDICTOR_CTRL_INGR_TX_PCS_SHIFT_CFG(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_PTP_PROC_INGR_PCS_PREDICTOR_CTRL_INGR_TX_PCS_SHIFT_CFG     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_PTP_PROC_INGR_PCS_PREDICTOR_CTRL_INGR_TX_PCS_SHIFT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * When pcs_shift is true or SOF is at lane-4,  the value of bit delay can
 * be specified.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_PCS_PREDICTOR_CTRL . INGR_RX_PCS_SHIFT_CFG
 */
#define  VTSS_F_PTP_PROC_INGR_PCS_PREDICTOR_CTRL_INGR_RX_PCS_SHIFT_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_PTP_PROC_INGR_PCS_PREDICTOR_CTRL_INGR_RX_PCS_SHIFT_CFG     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_PTP_PROC_INGR_PCS_PREDICTOR_CTRL_INGR_RX_PCS_SHIFT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a PTP_PROC:INGR_IP_1588_DF
 *
 * 1588 IP delay FIFO
 */


/**
 * \brief Configuration and control register for the delay FIFO
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DF:INGR_DF_CTRL
 */
#define VTSS_PTP_PROC_INGR_DF_CTRL           VTSS_IOREG(VTSS_TO_PTP_PROC,0x9037)
#define LAN80XX_PTP_PROC_INGR_DF_CTRL        LAN80XX_IOREG(MMD_ID_PTP_BLOCK,1,0x9037)
/**
>>>>>>> f7f5603e (Full PTP encap implemeted and basic Fun tested)
 * \brief
 * The index of the register stage in the delay FIFO that is used for
 * output. The actual delay through the block is one more than the depth.
 * If depth is set to 2, then the delay is 3 clocks as data is taken from
 * stage 2. The depth MUST be greater than 0 (depth of 0 is not allowed)
 * and MUST be less than 20 (depth of 20 not allowed).
 *
 * \details
 * Binary number >= 1
 *
 * Field: ::VTSS_PTP_PROC_INGR_DF_CTRL . INGR_DF_DEPTH
 */
#define  LAN80XX_F_PTP_PROC_INGR_DF_CTRL_INGR_DF_DEPTH(x)  LAN80XX_ENCODE_BITFIELD(x,0,5)
#define  LAN80XX_M_PTP_PROC_INGR_DF_CTRL_INGR_DF_DEPTH     LAN80XX_ENCODE_BITMASK(0,5)
#define  LAN80XX_X_PTP_PROC_INGR_DF_CTRL_INGR_DF_DEPTH(x)  LAN80XX_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a PTP_PROC:INGR_IP_1588_TSFIFO
 *
 * 1588 IP timestamp FIFO
 */


/**
 * \brief Timestamp FIFO configuration and status
 *
 * \details
 * Configuration and status register for the timestamp FIFO
 *
 * Register: \a PTP_PROC:INGR_IP_1588_TSFIFO:INGR_TSFIFO_CSR
 */
#define VTSS_PTP_PROC_INGR_TSFIFO_CSR        VTSS_IOREG(VTSS_TO_PTP_PROC,0x9037)

/**
 * \brief
 * Selects a timestamp size to be stored in the timestamp FIFO 2'b00: 10
 * bytes2'b01:  4 bytes2'b10:  11 bytes2'b11:  5 bytes
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_CSR . INGR_TS_4BYTES
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_4BYTES(x)  VTSS_ENCODE_BITFIELD(x,19,2)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_4BYTES     VTSS_ENCODE_BITMASK(19,2)
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_4BYTES(x)  VTSS_EXTRACT_BITFIELD(x,19,2)

/**
 * \brief
 * Forces the TS_FIFO into the reset state
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_CSR . INGR_TS_FIFO_RESET
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_FIFO_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_FIFO_RESET  VTSS_BIT(18)
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_FIFO_RESET(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * The FIFO level associated with the last read of the TS_EMPTY status
 * field of the TSFIFO_0 registerTSFIFO has 16 entries
 *
 * \details
 * Binary number (0-8)
 *
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_CSR . INGR_TS_LEVEL
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,13,5)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_LEVEL     VTSS_ENCODE_BITMASK(13,5)
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,13,5)

/**
 * \brief
 * The threshold at which the timestamp FIFO interrupt TS_LEVEL_STICKY will
 * be set. If the FIFO level reaches the threshold, the sticky bit
 * TS_LEVEL_STICKY will be set.TSFIFO has 16 entries
 *
 * \details
 * Binary number (1-8)
 *
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_CSR . INGR_TS_THRESH
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_THRESH(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_THRESH     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 * Indicates the number of signature bytes used for timestamps in the
 * timestamp FIFO In non-MCH mode, the signature can be (0-28) bytesIn MCH
 * mode, the signature has (5-bit) in one byte for 1-step and 15-bit for
 * 2-step
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_CSR . INGR_TS_SIGNAT_BYTES
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_SIGNAT_BYTES(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_SIGNAT_BYTES     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_CSR_INGR_TS_SIGNAT_BYTES(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO along with the FIFO empty flag in
 * the MSB
 *
 * Register: \a PTP_PROC:INGR_IP_1588_TSFIFO:INGR_TSFIFO_0
 */
#define VTSS_PTP_PROC_INGR_TSFIFO_0          VTSS_IOREG(VTSS_TO_PTP_PROC,0x9038)

/**
 * \brief
 * The FIFO empty flag from the Timestamp FIFO. If this bit is set, there
 * is no FIFO data to be read from the FIFO. The data in the TSFIFO_x
 * registers is not valid and should be discarded. When 0, the FIFO has
 * data and the TSFIFO_x has a valid set of data. This register can be
 * polled and when the bit is cleared, the other registers should be read
 * to get a full timestamp. When 1, the last data has already been read out
 * and the current read data should be discarded.Timestamp/Frame signature
 * bytes are packed such that the 4/5/10/11 bytes timestamp resides in the
 * LEAST significant bytes while the frame signature (0 to 28 bytes)
 * resides in the MOST significant bytes. The order of the bytes within
 * each timestamp/frame signature field is also most significant to least
 * significant.For example, 39 bytes timestamp/frame signature pairs are
 * packed with the 11 bytes timestamp field ([87:0]) corresponding to Bits
 * 87:0 in the following registers, and a 28 bytes frame signature field
 * ([223:0]) corresponding to Bits 311:88 in the following registers.
 *
 * \details
 * 0: FIFO not empty, data valid
 * 1: FIFO empty, data invalid
 *
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_0 . INGR_TS_EMPTY
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_0_INGR_TS_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_0_INGR_TS_EMPTY  VTSS_BIT(31)
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_0_INGR_TS_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * FIFO flags from the timestamp FIFO. These bits indicate how many
 * timestamps are valid in the current (not empty) 39 byte FIFO entry.
 *
 * \details
 * 0000: Only the end of a partial timestamp is valid in the current FIFO
 * entry (any remaining data is invalid)
 * 0001: 1 valid timestamp begins in the current FIFO entry (any remaining
 * data is invalid)
 * 0010: 2 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 0011: 3 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 0100: 4 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 0101: 5 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 0110: 6 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 0111: 7 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 1000: 8 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 1001: 9 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 1111: The current FIFO entry is fully packed with timestamps (all data
 * is valid)
 *
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_0 . INGR_TS_FLAGS
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_0_INGR_TS_FLAGS(x)  VTSS_ENCODE_BITFIELD(x,27,4)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_0_INGR_TS_FLAGS     VTSS_ENCODE_BITMASK(27,4)
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_0_INGR_TS_FLAGS(x)  VTSS_EXTRACT_BITFIELD(x,27,4)

/**
 * \brief
 * 24 bits from the timestamp FIFO. Bits 23:0
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_0 . INGR_TSFIFO_0
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_0_INGR_TSFIFO_0(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_0_INGR_TSFIFO_0     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_0_INGR_TSFIFO_0(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:INGR_IP_1588_TSFIFO:INGR_TSFIFO_1
 */
#define VTSS_PTP_PROC_INGR_TSFIFO_1          VTSS_IOREG(VTSS_TO_PTP_PROC,0x9039)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 55:24.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_1 . INGR_TSFIFO_1
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_1_INGR_TSFIFO_1(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_1_INGR_TSFIFO_1     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_1_INGR_TSFIFO_1(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:INGR_IP_1588_TSFIFO:INGR_TSFIFO_2
 */
#define VTSS_PTP_PROC_INGR_TSFIFO_2          VTSS_IOREG(VTSS_TO_PTP_PROC,0x903a)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 87:56.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_2 . INGR_TSFIFO_2
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_2_INGR_TSFIFO_2(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_2_INGR_TSFIFO_2     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_2_INGR_TSFIFO_2(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:INGR_IP_1588_TSFIFO:INGR_TSFIFO_3
 */
#define VTSS_PTP_PROC_INGR_TSFIFO_3          VTSS_IOREG(VTSS_TO_PTP_PROC,0x903b)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 119:88.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_3 . INGR_TSFIFO_3
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_3_INGR_TSFIFO_3(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_3_INGR_TSFIFO_3     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_3_INGR_TSFIFO_3(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:INGR_IP_1588_TSFIFO:INGR_TSFIFO_4
 */
#define VTSS_PTP_PROC_INGR_TSFIFO_4          VTSS_IOREG(VTSS_TO_PTP_PROC,0x903c)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 151:120.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_4 . INGR_TSFIFO_4
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_4_INGR_TSFIFO_4(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_4_INGR_TSFIFO_4     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_4_INGR_TSFIFO_4(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:INGR_IP_1588_TSFIFO:INGR_TSFIFO_5
 */
#define VTSS_PTP_PROC_INGR_TSFIFO_5          VTSS_IOREG(VTSS_TO_PTP_PROC,0x903d)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 183:152.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_5 . INGR_TSFIFO_5
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_5_INGR_TSFIFO_5(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_5_INGR_TSFIFO_5     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_5_INGR_TSFIFO_5(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:INGR_IP_1588_TSFIFO:INGR_TSFIFO_6
 */
#define VTSS_PTP_PROC_INGR_TSFIFO_6          VTSS_IOREG(VTSS_TO_PTP_PROC,0x903e)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 215:184.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_6 . INGR_TSFIFO_6
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_6_INGR_TSFIFO_6(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_6_INGR_TSFIFO_6     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_6_INGR_TSFIFO_6(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:INGR_IP_1588_TSFIFO:INGR_TSFIFO_7
 */
#define VTSS_PTP_PROC_INGR_TSFIFO_7          VTSS_IOREG(VTSS_TO_PTP_PROC,0x903f)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 247:216.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_7 . INGR_TSFIFO_7
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_7_INGR_TSFIFO_7(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_7_INGR_TSFIFO_7     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_7_INGR_TSFIFO_7(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:INGR_IP_1588_TSFIFO:INGR_TSFIFO_8
 */
#define VTSS_PTP_PROC_INGR_TSFIFO_8          VTSS_IOREG(VTSS_TO_PTP_PROC,0x9040)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 279:248.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_8 . INGR_TSFIFO_8
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_8_INGR_TSFIFO_8(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_8_INGR_TSFIFO_8     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_8_INGR_TSFIFO_8(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:INGR_IP_1588_TSFIFO:INGR_TSFIFO_9
 */
#define VTSS_PTP_PROC_INGR_TSFIFO_9          VTSS_IOREG(VTSS_TO_PTP_PROC,0x9041)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 311:280
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_9 . INGR_TSFIFO_9
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_9_INGR_TSFIFO_9(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_9_INGR_TSFIFO_9     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_9_INGR_TSFIFO_9(x)  (x)


/**
 * \brief Count of dropped timestamps
 *
 * \details
 * Count of dropped timestamps not enqueued to the TS FIFO
 *
 * Register: \a PTP_PROC:INGR_IP_1588_TSFIFO:INGR_TSFIFO_DROP_CNT
 */
#define VTSS_PTP_PROC_INGR_TSFIFO_DROP_CNT   VTSS_IOREG(VTSS_TO_PTP_PROC,0x9042)

/**
 * \brief
 * Timestamps dropped count
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TSFIFO_DROP_CNT . INGR_TS_FIFO_DROP_CNT
 */
#define  VTSS_F_PTP_PROC_INGR_TSFIFO_DROP_CNT_INGR_TS_FIFO_DROP_CNT(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TSFIFO_DROP_CNT_INGR_TS_FIFO_DROP_CNT     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TSFIFO_DROP_CNT_INGR_TS_FIFO_DROP_CNT(x)  (x)

/**
 * Register Group: \a PTP_PROC:INGR_IP_1588_RW
 *
 * 1588 IP rewriter
 */


/**
 * \brief Rewriter configuration and control
 *
 * \details
 * Configuration for the rewriter
 *
 * Register: \a PTP_PROC:INGR_IP_1588_RW:INGR_RW_CTRL
 */
#define LAN80XX_PTP_PROC_INGR_RW_CTRL           (0x44)

/**
 * \brief
 * Disable the overwriting of the CRC into the matching frames
 *
 * \details
 * 0: CRC write enabled (default)
 * 1: CRC write disabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_RW_CTRL . INGR_RW_DISABLE_CRC_WR
 */
#define  VTSS_F_PTP_PROC_INGR_RW_CTRL_INGR_RW_DISABLE_CRC_WR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PTP_PROC_INGR_RW_CTRL_INGR_RW_DISABLE_CRC_WR  VTSS_BIT(6)
#define  VTSS_X_PTP_PROC_INGR_RW_CTRL_INGR_RW_DISABLE_CRC_WR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Disable the CRC check in the rewriter. When disabled, an invalid CRC
 * will not be detected and a corrected CRC will be written to all matching
 * frames.
 *
 * \details
 * 0: CRC check enabled (default)
 * 1: CRC check disabled
 *
 * Field: ::VTSS_PTP_PROC_INGR_RW_CTRL . INGR_RW_DISABLE_CRC_CHK
 */
#define  VTSS_F_PTP_PROC_INGR_RW_CTRL_INGR_RW_DISABLE_CRC_CHK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PTP_PROC_INGR_RW_CTRL_INGR_RW_DISABLE_CRC_CHK  VTSS_BIT(5)
#define  VTSS_X_PTP_PROC_INGR_RW_CTRL_INGR_RW_DISABLE_CRC_CHK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * When set, the 1588 IP will reduce the preamble of ALL incoming frames by
 * 4 bytes to allow a timestamp to be appended to the ingress data frames.
 * This bit must be set along with the proper configuration of the Analyzer
 * to ensure proper operation. Note: Valid in ingress direction only
 *
 * \details
 * 0: No preamble modification
 * 1: Reduce preamble by 4 bytes
 *
 * Field: ::VTSS_PTP_PROC_INGR_RW_CTRL . INGR_RW_REDUCE_PREAMBLE
 */
#define  LAN80XX_F_PTP_PROC_INGR_RW_CTRL_INGR_RW_REDUCE_PREAMBLE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_PTP_PROC_INGR_RW_CTRL_INGR_RW_REDUCE_PREAMBLE     LAN80XX_BIT(4)
#define  LAN80XX_X_PTP_PROC_INGR_RW_CTRL_INGR_RW_REDUCE_PREAMBLE(x)     LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Value to write to the flag bit when it is overwritten
 *
 * \details
 * 0: 0 will be written to the flag bit
 * 1: 1 will be written to the flag bit
 *
 * Field: ::VTSS_PTP_PROC_INGR_RW_CTRL . INGR_RW_FLAG_VAL
 */
#define  LAN80XX_F_PTP_PROC_INGR_RW_CTRL_INGR_RW_FLAG_VAL(x)  LAN80XX_ENCODE_BITFIELD((x),3,1)
#define  LAN80XX_M_PTP_PROC_INGR_RW_CTRL_INGR_RW_FLAG_VAL     LAN80XX_BIT(3)
#define  LAN80XX_X_PTP_PROC_INGR_RW_CTRL_INGR_RW_FLAG_VAL(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Bit offset within a byte of the flag bit that indicates if the frame has
 * been modified
 *
 * \details
 * Binary number
 *
 * Field: ::VTSS_PTP_PROC_INGR_RW_CTRL . INGR_RW_FLAG_BIT
 */
#define  LAN80XX_F_PTP_PROC_INGR_RW_CTRL_INGR_RW_FLAG_BIT(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_PTP_PROC_INGR_RW_CTRL_INGR_RW_FLAG_BIT     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_PTP_PROC_INGR_RW_CTRL_INGR_RW_FLAG_BIT(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Count of modified frames
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_RW:INGR_RW_MODFRM_CNT
 */
#define VTSS_PTP_PROC_INGR_RW_MODFRM_CNT     VTSS_IOREG(VTSS_TO_PTP_PROC,0x9044)
#define LAN80XX_PTP_PROC_INGR_RW_MODFRM_CNT  (0x45)
/**
 * \brief
 * Count of the number of frames modified by the 1588 IP. The counter
 * wraps.
 *
 * \details
 * Binary number
 *
 * Field: ::VTSS_PTP_PROC_INGR_RW_MODFRM_CNT . INGR_RW_MODFRM_CNT
 */
#define  VTSS_F_PTP_PROC_INGR_RW_MODFRM_CNT_INGR_RW_MODFRM_CNT(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_RW_MODFRM_CNT_INGR_RW_MODFRM_CNT     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_RW_MODFRM_CNT_INGR_RW_MODFRM_CNT(x)  (x)


/**
 * \brief Count of FCS errors
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_RW:INGR_RW_FCS_ERR_CNT
 */
#define VTSS_PTP_PROC_INGR_RW_FCS_ERR_CNT    VTSS_IOREG(VTSS_TO_PTP_PROC,0x9045)
#define LAN80XX_PTP_PROC_INGR_RW_FCS_ERR_CNT  (0x46)

/**
 * \brief
 * Count of the number of FCS errored frames detected by the rewriter.
 * Counts only the FCS errored frames that are modified.
 *
 * \details
 * Binary number
 *
 * Field: ::VTSS_PTP_PROC_INGR_RW_FCS_ERR_CNT . INGR_RW_FCS_ERR_CNT
 */
#define  VTSS_F_PTP_PROC_INGR_RW_FCS_ERR_CNT_INGR_RW_FCS_ERR_CNT(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_RW_FCS_ERR_CNT_INGR_RW_FCS_ERR_CNT     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_RW_FCS_ERR_CNT_INGR_RW_FCS_ERR_CNT(x)  (x)


/**
 * \brief Count of the number of preamble errors
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_RW:INGR_RW_PREAMBLE_ERR_CNT
 */
#define VTSS_PTP_PROC_INGR_RW_PREAMBLE_ERR_CNT  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9046)
#define LAN80XX_PTP_PROC_INGR_RW_PREAMBLE_ERR_CNT (0x47)

/**
 * \brief
 * Count of the number of errored preambles detected. The counter wraps. An
 * errored preamble is a preamble that is too short to shrink that is
 * encountered when RW_REDUCE_PREAMBLE is set.
 *
 * \details
 * Binary number
 *
 * Field: ::VTSS_PTP_PROC_INGR_RW_PREAMBLE_ERR_CNT . INGR_RW_PREAMBLE_ERR_CNT
 */
#define  LAN80XX_F_PTP_PROC_INGR_RW_PREAMBLE_ERR_CNT_INGR_RW_PREAMBLE_ERR_CNT(x)  (x)
#define  LAN80XX_M_PTP_PROC_INGR_RW_PREAMBLE_ERR_CNT_INGR_RW_PREAMBLE_ERR_CNT     0xffffffff
#define  LAN80XX_X_PTP_PROC_INGR_RW_PREAMBLE_ERR_CNT_INGR_RW_PREAMBLE_ERR_CNT(x)  (x)

/**
 * Register Group: \a PTP_PROC:INGR_IP_ANALYZER_STAT
 *
 * Analyzer Counters and Errors
 */


/**
 * \brief Analyzer Modified Frames Counter
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_ANALYZER_STAT:INGR_ANALYZER_MOD_FRAMES_CNT
 */
#define VTSS_PTP_PROC_INGR_ANALYZER_MOD_FRAMES_CNT  VTSS_IOREG(VTSS_TO_PTP_PROC,0x904b)

/**
 * \brief
 * Count of the number of frames for which the analyzer generated a valid
 * command
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_ANALYZER_MOD_FRAMES_CNT . INGR_ANALYZER_MOD_FRAMES_CNT
 */
#define  VTSS_F_PTP_PROC_INGR_ANALYZER_MOD_FRAMES_CNT_INGR_ANALYZER_MOD_FRAMES_CNT(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_ANALYZER_MOD_FRAMES_CNT_INGR_ANALYZER_MOD_FRAMES_CNT     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_ANALYZER_MOD_FRAMES_CNT_INGR_ANALYZER_MOD_FRAMES_CNT(x)  (x)

/**
 * Register Group: \a PTP_PROC:INGR_IP_1588_MCH
 *
 * Configure MCH operation
 */


/**
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_MCH:INGR_MCH_CRC_ERR_CNTR
 */
#define VTSS_PTP_PROC_INGR_MCH_CRC_ERR_CNTR  VTSS_IOREG(VTSS_TO_PTP_PROC,0x904c)

/**
 * \brief
 * EGR MCH header CRC byte checkingcounter increments by 1 if CRC derived
 * from MCH header byte 6 to byte 1 is not the same as MCH header byte 7
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_MCH_CRC_ERR_CNTR . INGR_MCH_CRC_ERR_CNTR
 */
#define  VTSS_F_PTP_PROC_INGR_MCH_CRC_ERR_CNTR_INGR_MCH_CRC_ERR_CNTR(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_MCH_CRC_ERR_CNTR_INGR_MCH_CRC_ERR_CNTR     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_MCH_CRC_ERR_CNTR_INGR_MCH_CRC_ERR_CNTR(x)  (x)


/**
 * \details
 * For egress frame in MCH mode.
 * Counter increments
 * When preemption is enabled, ExtTy=2'b01 or 2'b11
 * When preemption is disabled, ExtTy=2'b10 or 2'b11

 *
 * Register: \a PTP_PROC:INGR_IP_1588_MCH:INGR_MCH_EXTTY_MISMATCH_CNTR
 */
#define VTSS_PTP_PROC_INGR_MCH_EXTTY_MISMATCH_CNTR  VTSS_IOREG(VTSS_TO_PTP_PROC,0x904d)

/**
 * \brief
 * For egress frame in MCH mode.Counter incrementsWhen preemption is
 * enabled, ExtTy field in MCH header =2'b01 or 2'b11When preemption is
 * disabled, ExtTy field in MCH header =2'b10 or 2'b11
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_MCH_EXTTY_MISMATCH_CNTR . INGR_MCH_EXTTY_MISMATCH_CNTR
 */
#define  VTSS_F_PTP_PROC_INGR_MCH_EXTTY_MISMATCH_CNTR_INGR_MCH_EXTTY_MISMATCH_CNTR(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_MCH_EXTTY_MISMATCH_CNTR_INGR_MCH_EXTTY_MISMATCH_CNTR     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_MCH_EXTTY_MISMATCH_CNTR_INGR_MCH_EXTTY_MISMATCH_CNTR(x)  (x)


/**
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_MCH:INGR_MCH_CTRL
 */
#define LAN80XX_PTP_PROC_INGR_MCH_CTRL       LAN80XX_IOREG(MMD_ID_PTP_BLOCK,1, 0x904f)

/**
 * \brief
 * 1'b1: drop the frame if extty (H2L) or preamble (H2L/L2H) checking fails
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_MCH_CTRL . INGR_MCH_DROP_EXTTY_PREAMBLE_MISMATCH
 */
#define  VTSS_F_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_DROP_EXTTY_PREAMBLE_MISMATCH(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_DROP_EXTTY_PREAMBLE_MISMATCH  VTSS_BIT(5)
#define  VTSS_X_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_DROP_EXTTY_PREAMBLE_MISMATCH(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Select the MCH header CRC generator1'b0: USXGMII standard1'b1: From
 * Fireant
 *
 * \details
 * Field: ::LAN80XX_PTP_PROC_INGR_MCH_CTRL . INGR_MCH_CRC_GEN_SEL
 */
#define  LAN80XX_F_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_CRC_GEN_SEL(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_CRC_GEN_SEL     LAN80XX_BIT(4)
#define  LAN80XX_X_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_CRC_GEN_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * 1'b1: drop the frame if H2L MCH header CRC checking fails
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_MCH_CTRL . INGR_MCH_DROP_CRC_ERROR
 */

#define  LAN80XX_F_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_DROP_CRC_ERROR(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_DROP_CRC_ERROR  LAN80XX_BIT(3)
#define  LAN80XX_X_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_DROP_CRC_ERROR(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)
/**
 * \brief
 * enable the MCH mode operation
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_MCH_CTRL . INGR_MCH_ENA
 */
#define  VTSS_F_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_ENA  VTSS_BIT(2)
#define  VTSS_X_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

#define  LAN80XX_F_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_ENA(x)  LAN80XX_ENCODE_BITFIELD(x,2,1)
#define  LAN80XX_M_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_ENA  LAN80XX_BIT(2)
#define  LAN80XX_X_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)



/**
 * \brief
 * Configure the ingress arrival timestamp field in the MCH header
 * extension [31:0]2'b00: 32 bit nsec [0,0, 30-bit nsec] (short format
 * 32.0)2'b01: 28 bit of ns + 4-bit Fractional ns (short format 28.42'b10:
 * 24-bit of ns + 8-bit of Fractional ns (short format 24.8)2'b11: 16-bit
 * of ns + 16-bit of Fractional ns (short format 16.16)Note that the 16-bit
 * fractional ns format is supported for interoperability reason, even
 * though the 16-bit frac-nsresolution is much higher than the timestamp
 * resolution (8-bit frac-ns). The 8 LSB are set to zero.
 *
 * \details
 * Field: ::LAN80XX_PTP_PROC_INGR_MCH_CTRL . INGR_MCH_IGTS_FMT_SEL
 */
#define  LAN80XX_F_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_IGTS_FMT_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,0,2)
#define  LAN80XX_M_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_IGTS_FMT_SEL     LAN80XX_ENCODE_BITMASK(0,2)
#define  LAN80XX_X_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_IGTS_FMT_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a PTP_PROC:INGR_IP_1588_RSFEC_PHAD
 *
 * High precision event detection Configuration and Status Registers
 */


/**
 * \brief Phase detection control
 *
 * \details
 * For timestamping and phase detection to work reliably, the mac clock
 * domains must be reset after clock change, ie when the link is detected
 * up and stable.
 * If high accuracy detection is to be used:
 *   The PHAD_ENA must be set, TWEAKS should be set to 5, and DIV_CFG
 * should be set to 3. LOCK_ACC will define how big an error at realignment
 * is accepted for the PHAD_LOCK indication to be seen.
 * If high accuracy is not to be used:
 *   The PHAD_ENA should be cleared, and TWEAKS should be set to 7.
 *
 * Register: \a PTP_PROC:INGR_IP_1588_RSFEC_PHAD:INGR_RSFEC_PHAD_CTRL
 */
#define VTSS_PTP_PROC_INGR_RSFEC_PHAD_CTRL   VTSS_IOREG(VTSS_TO_PTP_PROC,0x904f)
#define LAN80XX_PTP_PROC_INGR_RSFEC_PHAD_CTRL LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1 ,0x9050)
/**
 * \brief
 * Enable phase detector. The default is enabled
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RSFEC_PHAD_CTRL . INGR_CFG_RX_ENA
 */
#define  VTSS_F_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_RX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_RX_ENA  VTSS_BIT(18)
#define  VTSS_X_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_RX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Accuracy of lock logic 2**-x nsec
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RSFEC_PHAD_CTRL . INGR_CFG_LOCK_ACC
 */
#define  VTSS_F_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_LOCK_ACC(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_LOCK_ACC     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_LOCK_ACC(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * Internal tweaks on how port period is analyzed
 *
 * \details
 * x00: Count once and adjust 0.2 fs at reallignment
 * x01: Count once and adjust 16 fs at reallignment
 * x10: Recount and disable error feedback from allignment
 * x11: Count once after change in reset or phad_ena and keep as fixed
 * 0xx: Count for 1k port cycles when evaluating port period
 * 1xx: Count for 16k port cycle when evaluating port period
 *
 * Field: ::VTSS_PTP_PROC_INGR_RSFEC_PHAD_CTRL . INGR_CFG_TWEAKS
 */
#define  VTSS_F_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_TWEAKS(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_TWEAKS     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_TWEAKS(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * Alignment offset 2**-x nsec
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RSFEC_PHAD_CTRL . INGR_CFG_PHAD_MODE
 */
#define  VTSS_F_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_PHAD_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_PHAD_MODE  VTSS_BIT(11)
#define  VTSS_X_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_PHAD_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Divide port clock by the power of this
 *
 * \details
 * 0: Do not divide.
 * 1: Divide port clock by two.
 * 2: Divide port clock by four
 * 15: Automode.
 *
 * Field: ::VTSS_PTP_PROC_INGR_RSFEC_PHAD_CTRL . INGR_CFG_DIV_MODE
 */
#define  LAN80XX_F_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_DIV_MODE(x)  LAN80XX_ENCODE_BITFIELD(x,8,3)
#define  LAN80XX_M_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_DIV_MODE     LAN80XX_ENCODE_BITMASK(8,3)
#define  VTSS_X_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_DIV_MODE(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * When set, PHAD_ERR_STAT returns the largest error seen since this field
 * is set.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RSFEC_PHAD_CTRL . INGR_CFG_ERR_MAX_ENA
 */
#define  VTSS_F_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_ERR_MAX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_ERR_MAX_ENA  VTSS_BIT(7)
#define  VTSS_X_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_ERR_MAX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Phase detector has lost lock since the clearing of the bit. Can be
 * cleared writing one to this field.
 *       This field become unreliable for event clocks slower than 10
 * MHz, but phase detection can still be trusted. Slow event clocks are
 * only seen in synchronuous PPS detection.

 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RSFEC_PHAD_CTRL . INGR_STAT_FAILED
 */
#define  VTSS_F_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_STAT_FAILED(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_STAT_FAILED  VTSS_BIT(6)
#define  VTSS_X_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_STAT_FAILED(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Phase detector is locked to port clock
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RSFEC_PHAD_CTRL . INGR_STAT_LOCKED
 */
#define  LAN80XX_F_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_STAT_LOCKED(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_STAT_LOCKED  LAN80XX_BIT(5)
#define  LAN80XX_X_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_STAT_LOCKED(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Phase detector has adjusted phase down(bit 0) or up(bit 1).

 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RSFEC_PHAD_CTRL . INGR_STAT_ADJUSTED
 */
#define  VTSS_F_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_STAT_ADJUSTED(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_STAT_ADJUSTED     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_STAT_ADJUSTED(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Event clock is currently divided by the power of this
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RSFEC_PHAD_CTRL . INGR_STAT_DIV_STATE
 */
#define  VTSS_F_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_STAT_DIV_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_STAT_DIV_STATE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_STAT_DIV_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Phase detection status
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP_PROC:INGR_IP_1588_RSFEC_PHAD:INGR_RSFEC_PHAD_CYC_TIME
 */
#define VTSS_PTP_PROC_INGR_RSFEC_PHAD_CYC_TIME  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9050)

/**
 * \brief
 * Detected event clock period in 8.8 fixedpoint format.The lower 8-bit is
 * fnsthe upper 8-bit is ns
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RSFEC_PHAD_CYC_TIME . INGR_STAT_CYC_TIME
 */
#define  VTSS_F_PTP_PROC_INGR_RSFEC_PHAD_CYC_TIME_INGR_STAT_CYC_TIME(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_RSFEC_PHAD_CYC_TIME_INGR_STAT_CYC_TIME     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_RSFEC_PHAD_CYC_TIME_INGR_STAT_CYC_TIME(x)  (x)


/**
 * \brief Phase detection error
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP_PROC:INGR_IP_1588_RSFEC_PHAD:INGR_RSFEC_PHAD_ERR_STATE
 */
#define VTSS_PTP_PROC_INGR_RSFEC_PHAD_ERR_STATE  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9051)

/**
 * \brief
 * Latest or maximum error detected in alignment process, with format 10.8
 * fixedpoint format. ERR_MAX_ENA determines mode.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_RSFEC_PHAD_ERR_STATE . INGR_STAT_ERR_STATE
 */
#define  VTSS_F_PTP_PROC_INGR_RSFEC_PHAD_ERR_STATE_INGR_STAT_ERR_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_PTP_PROC_INGR_RSFEC_PHAD_ERR_STATE_INGR_STAT_ERR_STATE     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_PTP_PROC_INGR_RSFEC_PHAD_ERR_STATE_INGR_STAT_ERR_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,19)

/**
 * Register Group: \a PTP_PROC:INGR_IP_1588_SOF_PHAD
 *
 * High precission event detection Configuration and Status Registers
 */


/**
 * \brief Phase detection control
 *
 * \details
 * For timestamping and phase detection to work reliably, the mac clock
 * domains must be reset after clock change, ie when the link is detected
 * up and stable.
 * If high accuracy detection is to be used:
 *   The PHAD_ENA must be set, TWEAKS should be set to 5, and DIV_CFG
 * should be set to 3. LOCK_ACC will define how big an error at realignment
 * is accepted for the PHAD_LOCK indication to be seen.
 * If high accuracy is not to be used:
 *   The PHAD_ENA should be cleared, and TWEAKS should be set to 7.
 *
 * Register: \a PTP_PROC:INGR_IP_1588_SOF_PHAD:INGR_SOF_PHAD_CTRL
 */
#define VTSS_PTP_PROC_INGR_SOF_PHAD_CTRL     VTSS_IOREG(VTSS_TO_PTP_PROC,0x9052)
#define LAN80XX_PTP_PROC_INGR_SOF_PHAD_CTRL  LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1 ,0x9053)
/**
 * \brief
 * Enable phase detector. The default is enable.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SOF_PHAD_CTRL . INGR_CFG_RX_ENA
 */
#define  VTSS_F_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_RX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_RX_ENA  VTSS_BIT(18)
#define  VTSS_X_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_RX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Accuracy of lock logic 2**-x nsec
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SOF_PHAD_CTRL . INGR_CFG_LOCK_ACC
 */
#define  VTSS_F_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_LOCK_ACC(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_LOCK_ACC     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_LOCK_ACC(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * Internal tweaks on how port period is analyzed
 *
 * \details
 * x00: Count once and adjust 0.2 fs at reallignment
 * x01: Count once and adjust 16 fs at reallignment
 * x10: Recount and disable error feedback from allignment
 * x11: Count once after change in reset or phad_ena and keep as fixed
 * 0xx: Count for 1k port cycles when evaluating port period
 * 1xx: Count for 16k port cycle when evaluating port period
 *
 * Field: ::VTSS_PTP_PROC_INGR_SOF_PHAD_CTRL . INGR_CFG_TWEAKS
 */
#define  VTSS_F_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_TWEAKS(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_TWEAKS     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_TWEAKS(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * Alignment offset 2**-x nsec
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SOF_PHAD_CTRL . INGR_CFG_PHAD_MODE
 */
#define  VTSS_F_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_PHAD_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_PHAD_MODE  VTSS_BIT(11)
#define  VTSS_X_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_PHAD_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Divide port clock by the power of this
 *
 * \details
 * 0: Do not divide.
 * 1: Divide port clock by two.
 * 2: Divide port clock by four
 * 15: Automode.
 *
 * Field: ::VTSS_PTP_PROC_INGR_SOF_PHAD_CTRL . INGR_CFG_DIV_MODE
 */
#define  LAN80XX_F_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_DIV_MODE(x)  LAN80XX_ENCODE_BITFIELD(x,8,3)
#define  LAN80XX_M_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_DIV_MODE   LAN80XX_ENCODE_BITMASK(8,3)
#define  VTSS_X_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_DIV_MODE(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * When set, PHAD_ERR_STAT returns the largest error seen since this field
 * is set.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SOF_PHAD_CTRL . INGR_CFG_ERR_MAX_ENA
 */
#define  VTSS_F_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_ERR_MAX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_ERR_MAX_ENA  VTSS_BIT(7)
#define  VTSS_X_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_ERR_MAX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Phase detector has lost lock since the clearing of the bit. Can be
 * cleared writing one to this field.
 *       This field become unreliable for event clocks slower than 10
 * MHz, but phase detection can still be trusted. Slow event clocks are
 * only seen in synchronuous PPS detection.

 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SOF_PHAD_CTRL . INGR_STAT_FAILED
 */
#define  VTSS_F_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_STAT_FAILED(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_STAT_FAILED  VTSS_BIT(6)
#define  VTSS_X_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_STAT_FAILED(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Phase detector is locked to port clock
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SOF_PHAD_CTRL . INGR_STAT_LOCKED
 */
#define  VTSS_F_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_STAT_LOCKED(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_STAT_LOCKED  VTSS_BIT(5)
#define  LAN80XX_X_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_STAT_LOCKED(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Phase detector has adjusted phase down(bit 0) or up(bit 1).

 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SOF_PHAD_CTRL . INGR_STAT_ADJUSTED
 */
#define  VTSS_F_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_STAT_ADJUSTED(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_STAT_ADJUSTED     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_STAT_ADJUSTED(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Event clock is currently divided by the power of this
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SOF_PHAD_CTRL . INGR_STAT_DIV_STATE
 */
#define  VTSS_F_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_STAT_DIV_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_STAT_DIV_STATE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_STAT_DIV_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Phase detection status
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP_PROC:INGR_IP_1588_SOF_PHAD:INGR_SOF_PHAD_CYC_TIME
 */
#define VTSS_PTP_PROC_INGR_SOF_PHAD_CYC_TIME  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9053)

/**
 * \brief
 * Detected event clock period in 8.8 fixedpoint format.The lower 8-bit is
 * fnsthe upper 8-bit is ns
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SOF_PHAD_CYC_TIME . INGR_STAT_CYC_TIME
 */
#define  VTSS_F_PTP_PROC_INGR_SOF_PHAD_CYC_TIME_INGR_STAT_CYC_TIME(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_SOF_PHAD_CYC_TIME_INGR_STAT_CYC_TIME     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_SOF_PHAD_CYC_TIME_INGR_STAT_CYC_TIME(x)  (x)


/**
 * \brief Phase detection error
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP_PROC:INGR_IP_1588_SOF_PHAD:INGR_SOF_PHAD_ERR_STATE
 */
#define VTSS_PTP_PROC_INGR_SOF_PHAD_ERR_STATE  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9054)

/**
 * \brief
 * Latest or maximum error detected in alignment process, with format 10.8
 * fixedpoint format. ERR_MAX_ENA determines mode.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SOF_PHAD_ERR_STATE . INGR_STAT_ERR_STATE
 */
#define  VTSS_F_PTP_PROC_INGR_SOF_PHAD_ERR_STATE_INGR_STAT_ERR_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_PTP_PROC_INGR_SOF_PHAD_ERR_STATE_INGR_STAT_ERR_STATE     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_PTP_PROC_INGR_SOF_PHAD_ERR_STATE_INGR_STAT_ERR_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,19)

/**
 * Register Group: \a PTP_PROC:EGR_IP_1588_CFG_STAT
 *
 * 1588 IP control and status registers
 */


/**
 * \brief configure operation mode in IP 1588
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_CFG_STAT:EGR_CFG_OPERATION_MODE
 */
#define LAN80XX_PTP_PROC_EGR_CFG_OPERATION_MODE  LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1, 0x9057)

/**
 * \brief
 * 1'b1 PCS retiming mode, X/25GMII interface without MacSec1'b0 MAC
 * retiming mode, Packet interface with MacSec
 *
 * \details
 * Field: ::LAN80XX_PTP_PROC_EGR_CFG_OPERATION_MODE . EGR_CFG_RETIMING_MODE
 */
#define  LAN80XX_F_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_RETIMING_MODE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_RETIMING_MODE     LAN80XX_BIT(1)
#define  LAN80XX_X_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_RETIMING_MODE(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * 1'b1 enable preemption
 *
 * \details
 * Field: ::LAN80XX_PTP_PROC_EGR_CFG_OPERATION_MODE . EGR_CFG_PREEMPTION
 */
#define  LAN80XX_F_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_PREEMPTION(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_PREEMPTION     LAN80XX_BIT(0)
#define  LAN80XX_X_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_PREEMPTION(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief 1588 IP interrupt status register
 *
 * \details
 * Status sticky conditions for the 1588 IP
 *
 * Register: \a PTP_PROC:EGR_IP_1588_CFG_STAT:EGR_INT_STATUS
 */
#define VTSS_PTP_PROC_EGR_INT_STATUS         VTSS_IOREG(VTSS_TO_PTP_PROC,0x9056)
#define LAN80XX_PTP_PROC_EGR_INT_STATUS      (0x58)

/**
 * \brief
 * When set, indicates the CRC  in MCH header of EGR frame is not correct.
 * The sticky bit should be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_MCH_CRC_ERROR_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_MCH_CRC_ERROR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_MCH_CRC_ERROR_STICKY  VTSS_BIT(17)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_MCH_CRC_ERROR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * When set, indicates that the extty field in the MCH header does not
 * match preempt frame type. The sticky bit should be reset by writing it
 * to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_MCH_EXTTY_MISMATCH_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_MCH_EXTTY_MISMATCH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_MCH_EXTTY_MISMATCH_STICKY  VTSS_BIT(16)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_MCH_EXTTY_MISMATCH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * When set, indicates an underflow in the bypass logic. The sticky bit
 * should be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_BYPASS_UNDERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_BYPASS_UNDERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_BYPASS_UNDERFLOW_STICKY  VTSS_BIT(15)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_BYPASS_UNDERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * When set, indicates either an overflow in the bypass logic or short
 * frame within 1588. Read TSP_PUSH_FLAG bit to know whether short frame
 * came by. The sticky bit should be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_BYPASS_OVERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_BYPASS_OVERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_BYPASS_OVERFLOW_STICKY  VTSS_BIT(14)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_BYPASS_OVERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * When set, indicates an underflow in the analyzer command processor. The
 * sticky bit should be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_ANA_CMD_UNDERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_ANA_CMD_UNDERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_ANA_CMD_UNDERFLOW_STICKY  VTSS_BIT(13)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_ANA_CMD_UNDERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * When set, indicates an overflow in the analyzer command processor. The
 * sticky bit should be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_ANA_CMD_OVERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_ANA_CMD_OVERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_ANA_CMD_OVERFLOW_STICKY  VTSS_BIT(12)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_ANA_CMD_OVERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * When set, indicates  a frame was processed by rewriter command before
 * SOF arrives. Increase the fifo depth. The sticky bit should be reset by
 * writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_TSP_CMD_UNDERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_TSP_CMD_UNDERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_TSP_CMD_UNDERFLOW_STICKY  VTSS_BIT(11)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_TSP_CMD_UNDERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * When set, indicates an overflow in the Timestamp command processor. The
 * sticky bit should be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_TSP_CMD_OVERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_TSP_CMD_OVERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_TSP_CMD_OVERFLOW_STICKY  VTSS_BIT(10)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_TSP_CMD_OVERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * When set, indicates an a frame was processed by analyzer command before
 * a timestamp was taken. Underflow in the Timestamp. The sticky bit should
 * be reset by writing it to 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_TSP_FIFO_UNDERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_TSP_FIFO_UNDERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_TSP_FIFO_UNDERFLOW_STICKY  VTSS_BIT(9)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_TSP_FIFO_UNDERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * When set, indicates an overflow in the Timestamp processor. More than
 * four frames within 1588. The sticky bit should be reset by writing it to
 * 1.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_TSP_FIFO_OVERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_TSP_FIFO_OVERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_TSP_FIFO_OVERFLOW_STICKY  VTSS_BIT(8)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_TSP_FIFO_OVERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When set indicates that a frame was received with non-zero data in the
 * reserved field. The sticky bit should be reset by writing it to 1.
 *
 * \details
 * 0 = No data in reserved field
 * 1 = Data in reserved field.
 *   Reserved Field = messageTypeSpecific
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_RSVD_NONZERO_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_RSVD_NONZERO_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_RSVD_NONZERO_STICKY  VTSS_BIT(7)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_RSVD_NONZERO_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Indicates that more than one engine has produced a match. The sticky bit
 * should be reset by writing it to 1.
 *
 * \details
 * 0: No error found
 * 1: Duplicate match found
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_ANALYZER_ERROR_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_ANALYZER_ERROR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_ANALYZER_ERROR_STICKY  VTSS_BIT(6)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_ANALYZER_ERROR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * When set, indicates that a preamble that was too short to modify was
 * detected in a PTP frame. Write to 1 to clear. This occurs when the
 * rewriter needs to shrink the preamble to append a timestamp but cannot
 * because the preamble is too short. A short preamble is any preamble that
 * is less than eight characters long including the XGMII /S/ character and
 * the ending SFD of 0xD5. Other preamble values are not checked, only the
 * GMII length.
 *
 * \details
 * 0: No error
 * 1: Preamble too short error
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_RW_PREAMBLE_ERR_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_RW_PREAMBLE_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_RW_PREAMBLE_ERR_STICKY  VTSS_BIT(5)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_RW_PREAMBLE_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * When set, indicates that an FCS error was detected in a PTP frame. Write
 * to 1 to clear
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_RW_FCS_ERR_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_RW_FCS_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_RW_FCS_ERR_STICKY  VTSS_BIT(4)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_RW_FCS_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * When set, indicates that the level in the Timestamp FIFO has reached the
 * threshold TS_THRESH. The sticky bit should be reset by writing it to 1.
 *
 * \details
 * 0: No overflow
 * 1: Overflow
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_TS_LEVEL_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_TS_LEVEL_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_TS_LEVEL_STICKY  VTSS_BIT(3)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_TS_LEVEL_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * When set, indicates a timestamp was captured in the Timestamp FIFO. The
 * sticky bit should be reset by writing it to 1.
 *
 * \details
 * 0: No loaded
 * 1: Loaded
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_TS_LOADED_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_TS_LOADED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_TS_LOADED_STICKY  VTSS_BIT(2)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_TS_LOADED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * When set, indicates an underflow in the Timestamp FIFO. The sticky bit
 * should be reset by writing it to 1.
 *
 * \details
 * 0: No overflow
 * 1: Overflow
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_TS_UNDERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_TS_UNDERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_TS_UNDERFLOW_STICKY  VTSS_BIT(1)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_TS_UNDERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When set, indicates an overflow in the Timestamp FIFO. The sticky bit
 * should be reset by writing it to 1.
 *
 * \details
 * 0: No overflow
 * 1: Overflow
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_STATUS . EGR_TS_OVERFLOW_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_INT_STATUS_EGR_TS_OVERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_EGR_INT_STATUS_EGR_TS_OVERFLOW_STICKY  VTSS_BIT(0)
#define  VTSS_X_PTP_PROC_EGR_INT_STATUS_EGR_TS_OVERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief 1588 IP interrupt mask register
 *
 * \details
 * Masks that enable and disable the interrupts
 *
 * Register: \a PTP_PROC:EGR_IP_1588_CFG_STAT:EGR_INT_MASK
 */

#define LAN80XX_PTP_PROC_EGR_INT_MASK           (0x59)

/**
 * \brief
 * Mask for MCH_CRC_ERROR_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_MCH_CRC_ERROR_MASK
 */
#define  VTSS_F_PTP_PROC_EGR_INT_MASK_EGR_MCH_CRC_ERROR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PTP_PROC_EGR_INT_MASK_EGR_MCH_CRC_ERROR_MASK  VTSS_BIT(17)
#define  VTSS_X_PTP_PROC_EGR_INT_MASK_EGR_MCH_CRC_ERROR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Mask for MCH_EXTTY_MISMATCH_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_MCH_EXTTY_MISMATCH_MASK
 */
#define  VTSS_F_PTP_PROC_EGR_INT_MASK_EGR_MCH_EXTTY_MISMATCH_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PTP_PROC_EGR_INT_MASK_EGR_MCH_EXTTY_MISMATCH_MASK  VTSS_BIT(16)
#define  VTSS_X_PTP_PROC_EGR_INT_MASK_EGR_MCH_EXTTY_MISMATCH_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Mask for BYPASS_UNDERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_BYPASS_UNDERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_EGR_INT_MASK_EGR_BYPASS_UNDERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PTP_PROC_EGR_INT_MASK_EGR_BYPASS_UNDERFLOW_MASK  VTSS_BIT(15)
#define  VTSS_X_PTP_PROC_EGR_INT_MASK_EGR_BYPASS_UNDERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Mask for BYPASS_OVERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_BYPASS_OVERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_EGR_INT_MASK_EGR_BYPASS_OVERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PTP_PROC_EGR_INT_MASK_EGR_BYPASS_OVERFLOW_MASK  VTSS_BIT(14)
#define  VTSS_X_PTP_PROC_EGR_INT_MASK_EGR_BYPASS_OVERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Mask for ANA_CMD_UNDERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_ANA_CMD_UNDERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_EGR_INT_MASK_EGR_ANA_CMD_UNDERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PTP_PROC_EGR_INT_MASK_EGR_ANA_CMD_UNDERFLOW_MASK  VTSS_BIT(13)
#define  VTSS_X_PTP_PROC_EGR_INT_MASK_EGR_ANA_CMD_UNDERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Mask for ANA_CMD_OVERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_ANA_CMD_OVERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_EGR_INT_MASK_EGR_ANA_CMD_OVERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PTP_PROC_EGR_INT_MASK_EGR_ANA_CMD_OVERFLOW_MASK  VTSS_BIT(12)
#define  VTSS_X_PTP_PROC_EGR_INT_MASK_EGR_ANA_CMD_OVERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Mask bit for TSP_CMD_UNDERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_TSP_CMD_UNDERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_EGR_INT_MASK_EGR_TSP_CMD_UNDERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PTP_PROC_EGR_INT_MASK_EGR_TSP_CMD_UNDERFLOW_MASK  VTSS_BIT(11)
#define  VTSS_X_PTP_PROC_EGR_INT_MASK_EGR_TSP_CMD_UNDERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Mask bit for TSP_CMD_OVERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_TSP_CMD_OVERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_EGR_INT_MASK_EGR_TSP_CMD_OVERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PTP_PROC_EGR_INT_MASK_EGR_TSP_CMD_OVERFLOW_MASK  VTSS_BIT(10)
#define  VTSS_X_PTP_PROC_EGR_INT_MASK_EGR_TSP_CMD_OVERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Mask for TSP_FIFO_UNDERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_TSP_FIFO_UNDERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_EGR_INT_MASK_EGR_TSP_FIFO_UNDERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PTP_PROC_EGR_INT_MASK_EGR_TSP_FIFO_UNDERFLOW_MASK  VTSS_BIT(9)
#define  VTSS_X_PTP_PROC_EGR_INT_MASK_EGR_TSP_FIFO_UNDERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Mask bit for TSP_FIFO_OVERFLOW_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_TSP_FIFO_OVERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_EGR_INT_MASK_EGR_TSP_FIFO_OVERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PTP_PROC_EGR_INT_MASK_EGR_TSP_FIFO_OVERFLOW_MASK  VTSS_BIT(8)
#define  VTSS_X_PTP_PROC_EGR_INT_MASK_EGR_TSP_FIFO_OVERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Mask bit for RSVD_NONZERO_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_RSVD_NONZERO_MASK
 */
#define  LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_RSVD_NONZERO_MASK(x)  LAN80XX_ENCODE_BITFIELD((x),7,1)
#define  LAN80XX_M_PTP_PROC_EGR_INT_MASK_EGR_RSVD_NONZERO_MASK     LAN80XX_BIT(7)
#define  LAN80XX_X_PTP_PROC_EGR_INT_MASK_EGR_RSVD_NONZERO_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Mask bit for ANALYZER_ERROR_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_ANALYZER_ERROR_MASK
 */
#define  LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_ANALYZER_ERROR_MASK(x)  LAN80XX_ENCODE_BITFIELD((x),6,1)
#define  LAN80XX_M_PTP_PROC_EGR_INT_MASK_EGR_ANALYZER_ERROR_MASK     LAN80XX_BIT(6)
#define  LAN80XX_X_PTP_PROC_EGR_INT_MASK_EGR_ANALYZER_ERROR_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Mask for the RW_PREAMBLE_ERR_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_RW_PREAMBLE_ERR_MASK
 */
#define  LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_RW_PREAMBLE_ERR_MASK(x)  LAN80XX_ENCODE_BITFIELD((x),5,1)
#define  LAN80XX_M_PTP_PROC_EGR_INT_MASK_EGR_RW_PREAMBLE_ERR_MASK     LAN80XX_BIT(5)
#define  LAN80XX_X_PTP_PROC_EGR_INT_MASK_EGR_RW_PREAMBLE_ERR_MASK(x)  LNA80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Mask for the RW_FCS_ERR_STICKY bit
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_RW_FCS_ERR_MASK
 */
#define  LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_RW_FCS_ERR_MASK(x)  LAN80XX_ENCODE_BITFIELD((x),4,1)
#define  LAN80XX_M_PTP_PROC_EGR_INT_MASK_EGR_RW_FCS_ERR_MASK     LAN80XX_BIT(4)
#define  LAN80XX_X_PTP_PROC_EGR_INT_MASK_EGR_RW_FCS_ERR_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Mask bit for TS_LEVEL_STICKY. When 1, the interrupt is enabled.
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_TS_LEVEL_MASK
 */
#define  LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_TS_LEVEL_MASK(x)  LAN80XX_ENCODE_BITFIELD((x),3,1)
#define  LAN80XX_M_PTP_PROC_EGR_INT_MASK_EGR_TS_LEVEL_MASK     LAN80XX_BIT(3)
#define  LAN80XX_X_PTP_PROC_EGR_INT_MASK_EGR_TS_LEVEL_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Mask bit for TS_LOADED_STICKY. When 1, the interrupt is enabled.
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_TS_LOADED_MASK
 */
#define  LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_TS_LOADED_MASK(x)  LAN80XX_ENCODE_BITFIELD((x),2,1)
#define  LAN80XX_M_PTP_PROC_EGR_INT_MASK_EGR_TS_LOADED_MASK     LAN80XX_BIT(2)
#define  LAN80XX_X_PTP_PROC_EGR_INT_MASK_EGR_TS_LOADED_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Mask bit for TS_UNDERFLOW_STICKY. When 1, the interrupt is enabled.
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_TS_UNDERFLOW_MASK
 */
#define  VTSS_F_PTP_PROC_EGR_INT_MASK_EGR_TS_UNDERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PTP_PROC_EGR_INT_MASK_EGR_TS_UNDERFLOW_MASK  VTSS_BIT(1)
#define  VTSS_X_PTP_PROC_EGR_INT_MASK_EGR_TS_UNDERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Mask bit for TS_OVERFLOW_STICKY. When 1, the interrupt is enabled.
 *
 * \details
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_INT_MASK . EGR_TS_OVERFLOW_MASK
 */
#define  LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_TS_OVERFLOW_MASK(x)  LAN80XX_ENCODE_BITFIELD((x),0,1)
#define  LAN80XX_M_PTP_PROC_EGR_INT_MASK_EGR_TS_OVERFLOW_MASK     LAN80XX_BIT(0)
#define  LAN80XX_X_PTP_PROC_EGR_INT_MASK_EGR_TS_OVERFLOW_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Egress side stall latency
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_CFG_STAT:EGR_CFG_STALL_LATENCY
 */
#define VTSS_PTP_PROC_EGR_CFG_STALL_LATENCY  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9058)
#define LAN80XX_PTP_PROC_EGR_CFG_STALL_LATENCY (0x60)
/**
 * \brief
 * Stall latency (nanoseconds) denotes the latency experienced by a PTP
 * frame when going through a MACSec block. Only needed in the egress
 * direction. When MACSec is bypassed, this latency should be configured to
 * zero. In ingress side this value is not used.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_CFG_STALL_LATENCY . EGR_CFG_STALL_LATENCY
 */
#define  LAN80XX_F_PTP_PROC_EGR_CFG_STALL_LATENCY_EGR_CFG_STALL_LATENCY(x)  (x)
#define  LAN80XX_M_PTP_PROC_EGR_CFG_STALL_LATENCY_EGR_CFG_STALL_LATENCY     0xffffffff
#define  LAN80XX_X_PTP_PROC_EGR_CFG_STALL_LATENCY_EGR_CFG_STALL_LATENCY(x)  (x)


/**
 * \brief Egress side stall latency sub-nanosecond
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_CFG_STAT:EGR_CFG_STALL_LATENCY_SNS
 */
#define VTSS_PTP_PROC_EGR_CFG_STALL_LATENCY_SNS  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9059)
#define LAN80XX_PTP_PROC_EGR_CFG_STALL_LATENCY_SNS (0x61)
/**
 * \brief
 * Stall latency (sub-nanoseconds) denotes the latency experienced by a PTP
 * frame when going through a MACSec block. Only needed in the egress
 * direction. When MACSec is bypassed, this latency should be configured to
 * zero. In ingress side this value is not used.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_CFG_STALL_LATENCY_SNS . EGR_CFG_STALL_LATENCY_SNS
 */
#define  LAN80XX_F_PTP_PROC_EGR_CFG_STALL_LATENCY_SNS_EGR_CFG_STALL_LATENCY_SNS(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_PTP_PROC_EGR_CFG_STALL_LATENCY_SNS_EGR_CFG_STALL_LATENCY_SNS     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_PTP_PROC_EGR_CFG_STALL_LATENCY_SNS_EGR_CFG_STALL_LATENCY_SNS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a PTP_PROC:EGR_IP_1588_TSP
 *
 * 1588 IP timestamp processor
 */


/**
 * \brief TSP control
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_TSP_CTRL
 */
#define VTSS_PTP_PROC_EGR_TSP_CTRL           VTSS_IOREG(VTSS_TO_PTP_PROC,0x905f)
#define LAN80XX_PTP_PROC_EGR_TSP_CTRL        (0x5f)
#define LAN80XX_PTP_PROC_EGR_TSP_CTRL_REG    LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1, 0x905f)

/**
 * \brief
 * specify the type of frame that can be timestamped01: e-frame10:
 * unfragmented p-frame11: both e-frame and unfragmented p-frame00: none
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSP_CTRL . EGR_TS_FRAME_TYPE
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_TS_FRAME_TYPE(x)  LAN80XX_ENCODE_BITFIELD(x,11,2)
#define  LAN80XX_M_PTP_PROC_EGR_TSP_CTRL_EGR_TS_FRAME_TYPE     LAN80XX_ENCODE_BITMASK(11,2)
#define  LAN80XX_X_PTP_PROC_EGR_TSP_CTRL_EGR_TS_FRAME_TYPE(x)  LAN80XX_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * 1: MACSEC is in bypass mode0: MACSEC is not in bypass mode
 *
 * \details
 * C
 *
 * Field: ::VTSS_PTP_PROC_EGR_TSP_CTRL . EGR_MACSEC_BYPASS
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_MACSEC_BYPASS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),10,1)
#define  LAN80XX_M_PTP_PROC_EGR_TSP_CTRL_EGR_MACSEC_BYPASS  LAN80XX_BIT(10)
#define  LAN80XX_X_PTP_PROC_EGR_TSP_CTRL_EGR_MACSEC_BYPASS(x)  LAN80XX_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * 1: MACSEC is enabled0: MACSEC is disabled
 *
 * \details
 * C
 *
 * Field: ::VTSS_PTP_PROC_EGR_TSP_CTRL . EGR_MACSEC_ENABLE
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_MACSEC_ENABLE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),9,1)
#define  LAN80XX_M_PTP_PROC_EGR_TSP_CTRL_EGR_MACSEC_ENABLE  LAN80XX_BIT(9)
#define  LAN80XX_X_PTP_PROC_EGR_TSP_CTRL_EGR_MACSEC_ENABLE(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * 1: in 25G mode0: not in 25G mode
 *
 * \details
 * C
 *
 * Field: ::VTSS_PTP_PROC_EGR_TSP_CTRL . EGR_SPEED_25G
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_SPEED_25G(x)  LAN80XX_ENCODE_BITFIELD((x),7,2)
#define  LAN80XX_M_PTP_PROC_EGR_TSP_CTRL_EGR_SPEED_25G  LAN80XX_BIT(8)
#define  LAN80XX_X_PTP_PROC_EGR_TSP_CTRL_EGR_SPEED_25G(x)  LAN80XX_EXTRACT_BITFIELD(x,7,2)

/**
 * \brief
 * 1: RSFEC  is enabled0: RSFEC  is disabled
 *
 * \details
 * C
 *
 * Field: ::VTSS_PTP_PROC_EGR_TSP_CTRL . EGR_RSFEC_ENABLE
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_RSFEC_ENABLE(x)  LAN80XX_ENCODE_BITFIELD((x),6,1)
#define  LAN80XX_M_PTP_PROC_EGR_TSP_CTRL_EGR_RSFEC_ENABLE     LAN80XX_BIT(6)
#define  LAN80XX_X_PTP_PROC_EGR_TSP_CTRL_EGR_RSFEC_ENABLE(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * 1: RSFEC in full mode (Absolute time)0: RSFEC in SFB (start of FEC
 * Block)
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSP_CTRL . EGR_RSFEC_FULL_MODE
 */
#define  VTSS_F_PTP_PROC_EGR_TSP_CTRL_EGR_RSFEC_FULL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PTP_PROC_EGR_TSP_CTRL_EGR_RSFEC_FULL_MODE     VTSS_BIT(3)
#define  VTSS_X_PTP_PROC_EGR_TSP_CTRL_EGR_RSFEC_FULL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Delays the number of clock cycles to process analyzer command
 *
 * \details
 * 1=4 clocks to process analyzer command
 * 0=3 clocks to process analyzer command
 *
 * Field: ::VTSS_PTP_PROC_EGR_TSP_CTRL . EGR_DLY_FIFO_RD
 */
#define  VTSS_F_PTP_PROC_EGR_TSP_CTRL_EGR_DLY_FIFO_RD(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PTP_PROC_EGR_TSP_CTRL_EGR_DLY_FIFO_RD  VTSS_BIT(2)
#define  VTSS_X_PTP_PROC_EGR_TSP_CTRL_EGR_DLY_FIFO_RD(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Selects a mode in which the fractional portion of a second (in units of
 * nanoseconds) is used for timestamping. Only the operation of the
 * WRITE_NS, WRITE_NS_P2P, and SUB_ADD PTP commands are affected by the
 * setting of this mode bit.
 *
 * \details
 * INGR/EGR_FRACT_NS_MODE selects between the two modes
 * 0 = Selects RSVD32, counting 0 to 2^32-1 ns (0-4,294,967,295 ns)
 * 1 = Selects RSVD30, counting 0 to 10^9-1 ns (0-999,999,999 ns)
 *
 * Field: ::VTSS_PTP_PROC_EGR_TSP_CTRL . EGR_FRACT_NS_MODE
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_FRACT_NS_MODE(x)  LAN80XX_ENCODE_BITFIELD((x),1,1)
#define  LAN80XX_M_PTP_PROC_EGR_TSP_CTRL_EGR_FRACT_NS_MODE     LAN80XX_BIT(1)
#define  LAN80XX_X_PTP_PROC_EGR_TSP_CTRL_EGR_FRACT_NS_MODE(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSP_CTRL . EGR_RESERVED
 */
#define  VTSS_F_PTP_PROC_EGR_TSP_CTRL_EGR_RESERVED(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PTP_PROC_EGR_TSP_CTRL_EGR_RESERVED  VTSS_BIT(1)
#define  VTSS_X_PTP_PROC_EGR_TSP_CTRL_EGR_RESERVED(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * One-shot loads local latency, path delay, and DelayAsymmetry values into
 * the timestamp processor
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSP_CTRL . EGR_LOAD_DELAYS
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_LOAD_DELAYS(x)  VTSS_ENCODE_BITFIELD((x),0,1)
#define  LAN80XX_M_PTP_PROC_EGR_TSP_CTRL_EGR_LOAD_DELAYS  LAN80XX_BIT(0)
#define  VTSS_X_PTP_PROC_EGR_TSP_CTRL_EGR_LOAD_DELAYS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TSP status
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_TSP_STAT
 */
#define VTSS_PTP_PROC_EGR_TSP_STAT           VTSS_IOREG(VTSS_TO_PTP_PROC,0x905e)
#define LAN80XX_PTP_PROC_EGR_TSP_STAT        (0x60)
/**
 * \brief
 * Timestamp processor marked a calculated correction field as too big
 *
 * \details
 * 0: A calculated correction field that was too big did not occur
 * 1: A calculated correction field that was too big did occur
 *
 * Field: ::VTSS_PTP_PROC_EGR_TSP_STAT . EGR_CF_TOO_BIG_STICKY
 */
#define  VTSS_F_PTP_PROC_EGR_TSP_STAT_EGR_CF_TOO_BIG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_EGR_TSP_STAT_EGR_CF_TOO_BIG_STICKY  VTSS_BIT(0)
#define  VTSS_X_PTP_PROC_EGR_TSP_STAT_EGR_CF_TOO_BIG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Local latency nanosecond from TSP to RSFEC
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_LOCAL_LATENCY
 */
#define VTSS_PTP_PROC_EGR_LOCAL_LATENCY      VTSS_IOREG(VTSS_TO_PTP_PROC,0x905f)
#define LAN80XX_PTP_PROC_EGR_LOCAL_LATENCY   (0x61)
/**
 * \brief
 * Local latency (nanoseconds)This registers indicates the nanosecond of
 * latency from TSP to PCS RSFEC module
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_LOCAL_LATENCY . EGR_LOCAL_LATENCY
 */
#define  LAN80XX_F_PTP_PROC_EGR_LOCAL_LATENCY_EGR_LOCAL_LATENCY(x)  LAN80XX_ENCODE_BITFIELD(x,0,22)
#define  LAN80XX_M_PTP_PROC_EGR_LOCAL_LATENCY_EGR_LOCAL_LATENCY     LAN80XX_ENCODE_BITMASK(0,22)
#define  LAN80XX_X_PTP_PROC_EGR_LOCAL_LATENCY_EGR_LOCAL_LATENCY(x)  LAN80XX_EXTRACT_BITFIELD(x,0,22)


/**
 * \brief Local latency sub-nanosecond from TSP to RSFEC
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_LOCAL_LATENCY_SNS
 */
#define VTSS_PTP_PROC_EGR_LOCAL_LATENCY_SNS      VTSS_IOREG(VTSS_TO_PTP_PROC,0x9060)
#define LAN80XX_PTP_PROC_EGR_LOCAL_LATENCY_SNS   (0x62)

/**
 * \brief
 * Local latency (nanoseconds).This registers indicates the fractional
 * nanosecond of latency from TSP to PCS RSFEC module
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_LOCAL_LATENCY_SNS . EGR_LOCAL_LATENCY_SNS
 */
#define  LAN80XX_F_PTP_PROC_EGR_LOCAL_LATENCY_SNS_EGR_LOCAL_LATENCY_SNS(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_PTP_PROC_EGR_LOCAL_LATENCY_SNS_EGR_LOCAL_LATENCY_SNS     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_PTP_PROC_EGR_LOCAL_LATENCY_SNS_EGR_LOCAL_LATENCY_SNS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Local latency through PCS and SERDES
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_PCS_SERDES_LOCAL_LATENCY
 */
#define VTSS_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9061)
#define LAN80XX_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY (0x63)
/**
 * \brief
 * Local latency (nanoseconds)This registers indicates the nanosecond of
 * latency through PCS and SERDES
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY . EGR_PS_LOCAL_LATENCY
 */
#define  LAN80XX_F_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_EGR_PS_LOCAL_LATENCY(x)  VTSS_ENCODE_BITFIELD(x,0,23)
#define  LAN80XX_M_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_EGR_PS_LOCAL_LATENCY     VTSS_ENCODE_BITMASK(0,23)
#define  LAN80XX_X_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_EGR_PS_LOCAL_LATENCY(x)  VTSS_EXTRACT_BITFIELD(x,0,23)


/**
 * \brief Local latency sub-nanosecond through PCS and SERDES
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_PCS_SERDES_LOCAL_LATENCY_SNS
 */
#define VTSS_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_SNS  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9062)
#define LAN80XX_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_SNS (0x64)
/**
 * \brief
 * Local latency (nanoseconds).This registers indicates the fractional
 * nanosecond of latency through PCS and SERDES
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_SNS . EGR_PS_LOCAL_LATENCY_SNS
 */
#define  LAN80XX_F_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_SNS_EGR_PS_LOCAL_LATENCY_SNS(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_SNS_EGR_PS_LOCAL_LATENCY_SNS     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_SNS_EGR_PS_LOCAL_LATENCY_SNS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Path delay
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_PATH_DELAY
 */
#define VTSS_PTP_PROC_EGR_PATH_DELAY         VTSS_IOREG(VTSS_TO_PTP_PROC,0x9063)
#define LAN80XX_PTP_PROC_EGR_PATH_DELAY      (0x65)

/**
 * \brief
 * Path delay (nanoseconds)
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_PATH_DELAY . EGR_PATH_DELAY
 */
#define  LAN80XX_F_PTP_PROC_EGR_PATH_DELAY_EGR_PATH_DELAY(x)  (x)
#define  LAN80XX_M_PTP_PROC_EGR_PATH_DELAY_EGR_PATH_DELAY     0xffffffff
#define  LAN80XX_X_PTP_PROC_EGR_PATH_DELAY_EGR_PATH_DELAY(x)  (x)


/**
 * \brief Path delay sub-nanosecond
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_PATH_DELAY_SNS
 */
#define VTSS_PTP_PROC_EGR_PATH_DELAY_SNS     VTSS_IOREG(VTSS_TO_PTP_PROC,0x9064)
#define LAN80XX_PTP_PROC_EGR_PATH_DELAY_SNS  (0x66)
/**
 * \brief
 * Path delay (sub-nanoseconds)
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_PATH_DELAY_SNS . EGR_PATH_DELAY_SNS
 */
#define  LAN80XX_F_PTP_PROC_EGR_PATH_DELAY_SNS_EGR_PATH_DELAY_SNS(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_PTP_PROC_EGR_PATH_DELAY_SNS_EGR_PATH_DELAY_SNS     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_PTP_PROC_EGR_PATH_DELAY_SNS_EGR_PATH_DELAY_SNS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Delay asymmetry
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_DELAY_ASYMMETRY
 */
#define VTSS_PTP_PROC_EGR_DELAY_ASYMMETRY    VTSS_IOREG(VTSS_TO_PTP_PROC,0x9065)
#define LAN80XX_PTP_PROC_EGR_DELAY_ASYMMETRY    (0x67)

/**
 * \brief
 * Delay asymmetry (scaled nanoseconds)
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_DELAY_ASYMMETRY . EGR_DELAY_ASYMMETRY
 */
#define  VTSS_F_PTP_PROC_EGR_DELAY_ASYMMETRY_EGR_DELAY_ASYMMETRY(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_DELAY_ASYMMETRY_EGR_DELAY_ASYMMETRY     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_DELAY_ASYMMETRY_EGR_DELAY_ASYMMETRY(x)  (x)


/**
 * \brief PCS RADPT disable idle drop period
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_RADPT_DROP_IDLE_PIF
 */
#define VTSS_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9066)

/**
 * \brief
 * In packet interface, the duration of no idle drop by PCS rate adapter
 * after frame is timestamped in TSP in 25G mode and with RSFEC enabled,
 * and there are two PTP frames in MACSECThe value is the number PCS clock
 * cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF . EGR_DROP_DISABLE_DURATION_STALL_3
 */
#define  VTSS_F_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF_EGR_DROP_DISABLE_DURATION_STALL_3(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF_EGR_DROP_DISABLE_DURATION_STALL_3     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF_EGR_DROP_DISABLE_DURATION_STALL_3(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * In packet interface, the duration of no idle drop by PCS rate adapter
 * after frame is timestamped in TSP in 25G mode and with RSFEC enabled,
 * and there is one PTP frame in MACSECThe value is the number PCS clock
 * cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF . EGR_DROP_DISABLE_DURATION_STALL_2
 */
#define  VTSS_F_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF_EGR_DROP_DISABLE_DURATION_STALL_2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF_EGR_DROP_DISABLE_DURATION_STALL_2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF_EGR_DROP_DISABLE_DURATION_STALL_2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * In packet interface, the duration of no idle drop by PCS rate adapter
 * after frame is timestamped in TSP in 25G mode and with RSFEC enabled,
 * and there is no PTP frame in MACSECThe value is the number PCS clock
 * cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF . EGR_DROP_DISABLE_DURATION_STALL_1
 */
#define  VTSS_F_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF_EGR_DROP_DISABLE_DURATION_STALL_1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF_EGR_DROP_DISABLE_DURATION_STALL_1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF_EGR_DROP_DISABLE_DURATION_STALL_1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * In packet interface, the duration of no idle drop by PCS rate adapter
 * after frame is timestamped in TSP in 25G mode, with RSFEC enabled, and
 * with MACSEC enabled but in bypass modeThe value is the number PCS clock
 * cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF . EGR_DROP_DISABLE_DURATION_STALL_BYPASS
 */
#define  VTSS_F_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF_EGR_DROP_DISABLE_DURATION_STALL_BYPASS(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF_EGR_DROP_DISABLE_DURATION_STALL_BYPASS     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PROC_EGR_RADPT_DROP_IDLE_PIF_EGR_DROP_DISABLE_DURATION_STALL_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief PCS RADPT disable idle drop period
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_RADPT_DROP_IDLE_XIF
 */
#define VTSS_PTP_PROC_EGR_RADPT_DROP_IDLE_XIF  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9067)

/**
 * \brief
 * In X25GMII interface, the duration of no idle drop by PCS rate adapter
 * after frame is timestamped in TSP in 25G mode and with RSFEC  enabledThe
 * value is the number PCS clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RADPT_DROP_IDLE_XIF . EGR_DROP_DISABLE_DURATION_XIF
 */
#define  VTSS_F_PTP_PROC_EGR_RADPT_DROP_IDLE_XIF_EGR_DROP_DISABLE_DURATION_XIF(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PROC_EGR_RADPT_DROP_IDLE_XIF_EGR_DROP_DISABLE_DURATION_XIF     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PROC_EGR_RADPT_DROP_IDLE_XIF_EGR_DROP_DISABLE_DURATION_XIF(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief PCS CWM insertion early notice to TSP
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_CWM_EARLY_NOTICE_PIF
 */
#define VTSS_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9068)

/**
 * \brief
 * In packet interface, PCS CWM insertion early notice to  TSP in 25G mode
 * and with RSFEC  enabled, and there are two PTP frames in MACSECThe value
 * is the number PCS clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF . EGR_CWM_EARLY_NOTICE_STALL_3
 */
#define  VTSS_F_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF_EGR_CWM_EARLY_NOTICE_STALL_3(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF_EGR_CWM_EARLY_NOTICE_STALL_3     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF_EGR_CWM_EARLY_NOTICE_STALL_3(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * In packet interface, PCS CWM insertion early notice to  TSP in 25G mode
 * and with RSFEC  enabled, and there is one PTP frame in MACSECThe value
 * is the number PCS clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF . EGR_CWM_EARLY_NOTICE_STALL_2
 */
#define  VTSS_F_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF_EGR_CWM_EARLY_NOTICE_STALL_2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF_EGR_CWM_EARLY_NOTICE_STALL_2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF_EGR_CWM_EARLY_NOTICE_STALL_2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * In packet interface, PCS CWM insertion early notice to  TSP in 25G mode
 * and with RSFEC  enabled, and there is no PTP frame in MACSECThe value is
 * the number PCS clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF . EGR_CWM_EARLY_NOTICE_STALL_1
 */
#define  VTSS_F_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF_EGR_CWM_EARLY_NOTICE_STALL_1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF_EGR_CWM_EARLY_NOTICE_STALL_1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF_EGR_CWM_EARLY_NOTICE_STALL_1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * In packet interface, PCS CWM insertion early notice to  TSP in 25G mode,
 * with RSFEC  enabled, and with MACSEC enabled but in bypass modeThe value
 * is the number PCS clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF . EGR_CWM_EARLY_NOTICE_STALL_BYPASS
 */
#define  VTSS_F_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF_EGR_CWM_EARLY_NOTICE_STALL_BYPASS(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF_EGR_CWM_EARLY_NOTICE_STALL_BYPASS     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PROC_EGR_CWM_EARLY_NOTICE_PIF_EGR_CWM_EARLY_NOTICE_STALL_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief PCS CWM insertion early notice to TSP
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_CWM_EARLY_NOTICE_XIF
 */
#define VTSS_PTP_PROC_EGR_CWM_EARLY_NOTICE_XIF  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9069)

/**
 * \brief
 * In X25GMII interface, PCS CWM insertion early notice to  TSP in 25G mode
 * and with RSFEC  enabledThe value is the number PCS clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_CWM_EARLY_NOTICE_XIF . EGR_CWM_EARLY_NOTICE_XIF
 */
#define  VTSS_F_PTP_PROC_EGR_CWM_EARLY_NOTICE_XIF_EGR_CWM_EARLY_NOTICE_XIF(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PROC_EGR_CWM_EARLY_NOTICE_XIF_EGR_CWM_EARLY_NOTICE_XIF     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PROC_EGR_CWM_EARLY_NOTICE_XIF_EGR_CWM_EARLY_NOTICE_XIF(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief delay 32 bit or 34 bit by the SOF position
 *
 * \details
 * A SOF is seen on the pcs output. If the shift input is asserted, it
 * means that only 4 bytes has been transferred so far, and we must
 * reduce the delay 32-34 bit times, depending on how it should regarded
 * that a 66 bit word has a frames staring after 34 bit times (two
 * control bits, and 64 data bits in each word). The 32-34 is selected
 * by a configuration input.

 *
 * Register: \a PTP_PROC:EGR_IP_1588_TSP:EGR_PCS_PREDICTOR_CTRL
 */
#define VTSS_PTP_PROC_EGR_PCS_PREDICTOR_CTRL  VTSS_IOREG(VTSS_TO_PTP_PROC,0x906a)

/**
 * \brief
 * When pcs_shift is true or SOF is at lane-4,  the value of bit delay can
 * be specified.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_PCS_PREDICTOR_CTRL . EGR_TX_PCS_SHIFT_CFG
 */
#define  VTSS_F_PTP_PROC_EGR_PCS_PREDICTOR_CTRL_EGR_TX_PCS_SHIFT_CFG(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_PTP_PROC_EGR_PCS_PREDICTOR_CTRL_EGR_TX_PCS_SHIFT_CFG     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_PTP_PROC_EGR_PCS_PREDICTOR_CTRL_EGR_TX_PCS_SHIFT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * When pcs_shift is true or SOF is at lane-4,  the value of bit delay can
 * be specified.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_PCS_PREDICTOR_CTRL . EGR_RX_PCS_SHIFT_CFG
 */
#define  VTSS_F_PTP_PROC_EGR_PCS_PREDICTOR_CTRL_EGR_RX_PCS_SHIFT_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_PTP_PROC_EGR_PCS_PREDICTOR_CTRL_EGR_RX_PCS_SHIFT_CFG     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_PTP_PROC_EGR_PCS_PREDICTOR_CTRL_EGR_RX_PCS_SHIFT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a PTP_PROC:EGR_IP_1588_DF
 *
 * 1588 IP delay FIFO
 */


/**
 * \brief Configuration and control register for the delay FIFO
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DF:EGR_DF_CTRL
 */
#define VTSS_PTP_PROC_EGR_DF_CTRL            VTSS_IOREG(VTSS_TO_PTP_PROC,0x906e)
#define LAN80XX_PTP_PROC_EGR_DF_CTRL         LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1, 0x906e)

/**
 * \brief
 * The index of the register stage in the delay FIFO that is used for
 * output. The actual delay through the block is one more than the depth.
 * If depth is set to 2, then the delay is 3 clocks as data is taken from
 * stage 2. The depth MUST be greater than 0 (depth of 0 is not allowed)
 * and MUST be less than 20 (depth of 20 not allowed).
 *
 * \details
 * Binary number >= 1
 *
 * Field: ::VTSS_PTP_PROC_EGR_DF_CTRL . EGR_DF_DEPTH
 */
#define  LAN80XX_F_PTP_PROC_EGR_DF_CTRL_EGR_DF_DEPTH(x)  LAN80XX_ENCODE_BITFIELD(x,0,5)
#define  LAN80XX_M_PTP_PROC_EGR_DF_CTRL_EGR_DF_DEPTH     LAN80XX_ENCODE_BITMASK(0,5)
#define  LAN80XX_PTP_PROC_EGR_DF_CTRL_EGR_DF_DEPTH(x)    LAN80XX_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a PTP_PROC:EGR_IP_1588_TSFIFO
 *
 * 1588 IP timestamp FIFO
 */


/**
 * \brief Timestamp FIFO configuration and status
 *
 * \details
 * Configuration and status register for the timestamp FIFO
 *
 * Register: \a PTP_PROC:EGR_IP_1588_TSFIFO:EGR_TSFIFO_CSR
 */
#define LAN80XX_PTP_PROC_EGR_TSFIFO_CSR   (0x6f)

/**
 * \brief
 * Selects a timestamp size to be stored in the timestamp FIFO 2'b00: 10
 * bytes2'b01:  4 bytes2'b10:  11 bytes2'b11:  5 bytes
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_CSR . EGR_TS_4BYTES
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_4BYTES(x)  LAN80XX_ENCODE_BITFIELD(x,19,2)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_4BYTES     LAN80XX_ENCODE_BITMASK(19,2)
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_4BYTES(x)  LAN80XX_EXTRACT_BITFIELD(x,19,2)

/**
 * \brief
 * Forces the TS_FIFO into the reset state
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_CSR . EGR_TS_FIFO_RESET
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_FIFO_RESET(x)  LAN80XX_ENCODE_BITFIELD(!!(x),18,1)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_FIFO_RESET  LAN80XX_BIT(18)
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_FIFO_RESET(x)  LAN80XX_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * The FIFO level associated with the last read of the TS_EMPTY status
 * field of the TSFIFO_0 registerTSFIFO has 16 entries
 *
 * \details
 * Binary number (0-8)
 *
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_CSR . EGR_TS_LEVEL
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_LEVEL(x)  LAN80XX_ENCODE_BITFIELD(x,13,5)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_LEVEL     LAN80XX_ENCODE_BITMASK(13,5)
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_LEVEL(x)  LAN80XX_EXTRACT_BITFIELD(x,13,5)

/**
 * \brief
 * The threshold at which the timestamp FIFO interrupt TS_LEVEL_STICKY will
 * be set. If the FIFO level reaches the threshold, the sticky bit
 * TS_LEVEL_STICKY will be set.TSFIFO has 16 entries
 *
 * \details
 * Binary number (1-8)
 *
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_CSR . EGR_TS_THRESH
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_THRESH(x)  LAN80XX_ENCODE_BITFIELD(x,8,5)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_THRESH     LAN80XX_ENCODE_BITMASK(8,5)
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_THRESH(x)  LAN80XX_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 * Indicates the number of signature bytes used for timestamps in the
 * timestamp FIFO In non-MCH mode, the signature can be (0-28) bytesIn MCH
 * mode, the signature has (5-bit) in one byte for 1-step and 15-bit for
 * 2-step
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_CSR . EGR_TS_SIGNAT_BYTES
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_SIGNAT_BYTES(x)  LAN80XX_ENCODE_BITFIELD(x,0,5)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_SIGNAT_BYTES     LAN80XX_ENCODE_BITMASK(0,5)
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_SIGNAT_BYTES(x)  LAN80XX_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO along with the FIFO empty flag in
 * the MSB
 *
 * Register: \a PTP_PROC:EGR_IP_1588_TSFIFO:EGR_TSFIFO_0
 */
#define LAN80XX_PTP_PROC_EGR_TSFIFO_0          (0x70)

/**
 * \brief
 * The FIFO empty flag from the Timestamp FIFO. If this bit is set, there
 * is no FIFO data to be read from the FIFO. The data in the TSFIFO_x
 * registers is not valid and should be discarded. When 0, the FIFO has
 * data and the TSFIFO_x has a valid set of data. This register can be
 * polled and when the bit is cleared, the other registers should be read
 * to get a full timestamp. When 1, the last data has already been read out
 * and the current read data should be discarded.Timestamp/Frame signature
 * bytes are packed such that the 4/5/10/11 bytes timestamp resides in the
 * LEAST significant bytes while the frame signature (0 to 28 bytes)
 * resides in the MOST significant bytes. The order of the bytes within
 * each timestamp/frame signature field is also most significant to least
 * significant.For example, 39 bytes timestamp/frame signature pairs are
 * packed with the 11 bytes timestamp field ([87:0]) corresponding to Bits
 * 87:0 in the following registers, and a 28 bytes frame signature field
 * ([223:0]) corresponding to Bits 311:88 in the following registers.
 *
 * \details
 * 0: FIFO not empty, data valid
 * 1: FIFO empty, data invalid
 *
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_0 . EGR_TS_EMPTY
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_0_EGR_TS_EMPTY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),31,1)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_0_EGR_TS_EMPTY     LAN80XX_BIT(31)
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_0_EGR_TS_EMPTY(x)  LAN80XX_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * FIFO flags from the timestamp FIFO. These bits indicate how many
 * timestamps are valid in the current (not empty) 39 byte FIFO entry.
 *
 * \details
 * 0000: Only the end of a partial timestamp is valid in the current FIFO
 * entry (any remaining data is invalid)
 * 0001: 1 valid timestamp begins in the current FIFO entry (any remaining
 * data is invalid)
 * 0010: 2 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 0011: 3 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 0100: 4 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 0101: 5 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 0110: 6 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 0111: 7 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 1000: 8 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 1001: 9 valid timestamps begin in the current FIFO entry (any remaining
 * data is invalid)
 * 1111: The current FIFO entry is fully packed with timestamps (all data
 * is valid)
 *
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_0 . EGR_TS_FLAGS
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_0_EGR_TS_FLAGS(x)  LAN80XX_ENCODE_BITFIELD(x,27,4)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_0_EGR_TS_FLAGS     LAN80XX_ENCODE_BITMASK(27,4)
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_0_EGR_TS_FLAGS(x)  LAN80XX_EXTRACT_BITFIELD(x,27,4)

/**
 * \brief
 * 24 bits from the timestamp FIFO. Bits 23:0
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_0 . EGR_TSFIFO_0
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_0_EGR_TSFIFO_0(x)  LAN80XX_ENCODE_BITFIELD(x,0,24)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_0_EGR_TSFIFO_0     LAN80XX_ENCODE_BITMASK(0,24)
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_0_EGR_TSFIFO_0(x)  LAN80XX_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:EGR_IP_1588_TSFIFO:EGR_TSFIFO_1
 */
#define LAN80XX_PTP_PROC_EGR_TSFIFO_1           (0x71)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 55:24.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_1 . EGR_TSFIFO_1
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_1_EGR_TSFIFO_1(x)  (x)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_1_EGR_TSFIFO_1     0xffffffff
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_1_EGR_TSFIFO_1(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:EGR_IP_1588_TSFIFO:EGR_TSFIFO_2
 */
#define LAN80XX_PTP_PROC_EGR_TSFIFO_2          (0x72)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 87:56.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_2 . EGR_TSFIFO_2
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_2_EGR_TSFIFO_2(x)  (x)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_2_EGR_TSFIFO_2     0xffffffff
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_2_EGR_TSFIFO_2(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:EGR_IP_1588_TSFIFO:EGR_TSFIFO_3
 */
#define LAN80XX_PTP_PROC_EGR_TSFIFO_3        (0x73)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 119:88.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_3 . EGR_TSFIFO_3
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_3_EGR_TSFIFO_3(x)  (x)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_3_EGR_TSFIFO_3     0xffffffff
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_3_EGR_TSFIFO_3(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:EGR_IP_1588_TSFIFO:EGR_TSFIFO_4
 */
#define LAN80XX_PTP_PROC_EGR_TSFIFO_4           (0x74)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 151:120.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_4 . EGR_TSFIFO_4
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_4_EGR_TSFIFO_4(x)  (x)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_4_EGR_TSFIFO_4     0xffffffff
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_4_EGR_TSFIFO_4(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:EGR_IP_1588_TSFIFO:EGR_TSFIFO_5
 */
#define LAN80XX_PTP_PROC_EGR_TSFIFO_5           (0x75)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 183:152.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_5 . EGR_TSFIFO_5
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_5_EGR_TSFIFO_5(x)  (x)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_5_EGR_TSFIFO_5     0xffffffff
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_5_EGR_TSFIFO_5(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:EGR_IP_1588_TSFIFO:EGR_TSFIFO_6
 */
#define LAN80XX_PTP_PROC_EGR_TSFIFO_6           (0x76)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 215:184.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_6 . EGR_TSFIFO_6
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_6_EGR_TSFIFO_6(x)  (x)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_6_EGR_TSFIFO_6     0xffffffff
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_6_EGR_TSFIFO_6(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:EGR_IP_1588_TSFIFO:EGR_TSFIFO_7
 */
#define LAN80XX_PTP_PROC_EGR_TSFIFO_7          (0x77)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 247:216.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_7 . EGR_TSFIFO_7
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_7_EGR_TSFIFO_7(x)  (x)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_7_EGR_TSFIFO_7     0xffffffff
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_7_EGR_TSFIFO_7(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:EGR_IP_1588_TSFIFO:EGR_TSFIFO_8
 */
#define LAN80XX_PTP_PROC_EGR_TSFIFO_8          (0x78)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 279:248.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_8 . EGR_TSFIFO_8
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_8_EGR_TSFIFO_8(x)  (x)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_8_EGR_TSFIFO_8     0xffffffff
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_8_EGR_TSFIFO_8(x)  (x)


/**
 * \brief Data value from the timestamp FIFO
 *
 * \details
 * Read the data from the timestamp FIFO
 *
 * Register: \a PTP_PROC:EGR_IP_1588_TSFIFO:EGR_TSFIFO_9
 */
#define LAN80XX_PTP_PROC_EGR_TSFIFO_9           (0x79)

/**
 * \brief
 * 32 bits from the timestamp FIFO. Bits 311:280
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_9 . EGR_TSFIFO_9
 */
#define  LAN80XX_F_PTP_PROC_EGR_TSFIFO_9_EGR_TSFIFO_9(x)  (x)
#define  LAN80XX_M_PTP_PROC_EGR_TSFIFO_9_EGR_TSFIFO_9     0xffffffff
#define  LAN80XX_X_PTP_PROC_EGR_TSFIFO_9_EGR_TSFIFO_9(x)  (x)


/**
 * \brief Count of dropped timestamps
 *
 * \details
 * Count of dropped timestamps not enqueued to the TS FIFO
 *
 * Register: \a PTP_PROC:EGR_IP_1588_TSFIFO:EGR_TSFIFO_DROP_CNT
 */
#define VTSS_PTP_PROC_EGR_TSFIFO_DROP_CNT    VTSS_IOREG(VTSS_TO_PTP_PROC,0x9077)
#define LAN80XX_PTP_PROC_EGR_TSFIFO_DROP_CNT (0x7A)
/**
 * \brief
 * Timestamps dropped count
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TSFIFO_DROP_CNT . EGR_TS_FIFO_DROP_CNT
 */
#define  VTSS_F_PTP_PROC_EGR_TSFIFO_DROP_CNT_EGR_TS_FIFO_DROP_CNT(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_TSFIFO_DROP_CNT_EGR_TS_FIFO_DROP_CNT     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_TSFIFO_DROP_CNT_EGR_TS_FIFO_DROP_CNT(x)  (x)

/**
 * Register Group: \a PTP_PROC:EGR_IP_1588_RW
 *
 * 1588 IP rewriter
 */


/**
 * \brief Rewriter configuration and control
 *
 * \details
 * Configuration for the rewriter
 *
 * Register: \a PTP_PROC:EGR_IP_1588_RW:EGR_RW_CTRL
 */
#define LAN80XX_PTP_PROC_EGR_RW_CTRL            (0x7B)

/**
 * \brief
 * Disable the overwriting of the CRC into the matching frames
 *
 * \details
 * 0: CRC write enabled (default)
 * 1: CRC write disabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_RW_CTRL . EGR_RW_DISABLE_CRC_WR
 */
#define  VTSS_F_PTP_PROC_EGR_RW_CTRL_EGR_RW_DISABLE_CRC_WR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PTP_PROC_EGR_RW_CTRL_EGR_RW_DISABLE_CRC_WR  VTSS_BIT(6)
#define  VTSS_X_PTP_PROC_EGR_RW_CTRL_EGR_RW_DISABLE_CRC_WR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Disable the CRC check in the rewriter. When disabled, an invalid CRC
 * will not be detected and a corrected CRC will be written to all matching
 * frames.
 *
 * \details
 * 0: CRC check enabled (default)
 * 1: CRC check disabled
 *
 * Field: ::VTSS_PTP_PROC_EGR_RW_CTRL . EGR_RW_DISABLE_CRC_CHK
 */
#define  VTSS_F_PTP_PROC_EGR_RW_CTRL_EGR_RW_DISABLE_CRC_CHK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PTP_PROC_EGR_RW_CTRL_EGR_RW_DISABLE_CRC_CHK  VTSS_BIT(5)
#define  VTSS_X_PTP_PROC_EGR_RW_CTRL_EGR_RW_DISABLE_CRC_CHK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * When set, the 1588 IP will reduce the preamble of ALL incoming frames by
 * 4 bytes to allow a timestamp to be appended to the ingress data frames.
 * This bit must be set along with the proper configuration of the Analyzer
 * to ensure proper operation. Note: Valid in ingress direction only
 *
 * \details
 * 0: No preamble modification
 * 1: Reduce preamble by 4 bytes
 *
 * Field: ::VTSS_PTP_PROC_EGR_RW_CTRL . EGR_RW_REDUCE_PREAMBLE
 */
#define  VTSS_F_PTP_PROC_EGR_RW_CTRL_EGR_RW_REDUCE_PREAMBLE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PTP_PROC_EGR_RW_CTRL_EGR_RW_REDUCE_PREAMBLE  VTSS_BIT(4)
#define  VTSS_X_PTP_PROC_EGR_RW_CTRL_EGR_RW_REDUCE_PREAMBLE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Value to write to the flag bit when it is overwritten
 *
 * \details
 * 0: 0 will be written to the flag bit
 * 1: 1 will be written to the flag bit
 *
 * Field: ::VTSS_PTP_PROC_EGR_RW_CTRL . EGR_RW_FLAG_VAL
 */
#define  LAN80XX_F_PTP_PROC_EGR_RW_CTRL_EGR_RW_FLAG_VAL(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_PTP_PROC_EGR_RW_CTRL_EGR_RW_FLAG_VAL     LAN80XX_BIT(3)
#define  LAN80XX_X_PTP_PROC_EGR_RW_CTRL_EGR_RW_FLAG_VAL(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Bit offset within a byte of the flag bit that indicates if the frame has
 * been modified
 *
 * \details
 * Binary number
 *
 * Field: ::VTSS_PTP_PROC_EGR_RW_CTRL . EGR_RW_FLAG_BIT
 */
#define  LAN80XX_F_PTP_PROC_EGR_RW_CTRL_EGR_RW_FLAG_BIT(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_PTP_PROC_EGR_RW_CTRL_EGR_RW_FLAG_BIT     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_PTP_PROC_EGR_RW_CTRL_EGR_RW_FLAG_BIT(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Count of modified frames
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_RW:EGR_RW_MODFRM_CNT
 */
#define VTSS_PTP_PROC_EGR_RW_MODFRM_CNT      VTSS_IOREG(VTSS_TO_PTP_PROC,0x9079)
#define LAN80XX_PTP_PROC_EGR_RW_MODFRM_CNT   (0x7C)
/**
 * \brief
 * Count of the number of frames modified by the 1588 IP. The counter
 * wraps.
 *
 * \details
 * Binary number
 *
 * Field: ::VTSS_PTP_PROC_EGR_RW_MODFRM_CNT . EGR_RW_MODFRM_CNT
 */
#define  VTSS_F_PTP_PROC_EGR_RW_MODFRM_CNT_EGR_RW_MODFRM_CNT(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_RW_MODFRM_CNT_EGR_RW_MODFRM_CNT     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_RW_MODFRM_CNT_EGR_RW_MODFRM_CNT(x)  (x)


/**
 * \brief Count of FCS errors
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_RW:EGR_RW_FCS_ERR_CNT
 */
#define VTSS_PTP_PROC_EGR_RW_FCS_ERR_CNT     VTSS_IOREG(VTSS_TO_PTP_PROC,0x907a)
#define LAN80XX_PTP_PROC_EGR_RW_FCS_ERR_CNT  (0x7D)
/**
 * \brief
 * Count of the number of FCS errored frames detected by the rewriter.
 * Counts only the FCS errored frames that are modified.
 *
 * \details
 * Binary number
 *
 * Field: ::VTSS_PTP_PROC_EGR_RW_FCS_ERR_CNT . EGR_RW_FCS_ERR_CNT
 */
#define  VTSS_F_PTP_PROC_EGR_RW_FCS_ERR_CNT_EGR_RW_FCS_ERR_CNT(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_RW_FCS_ERR_CNT_EGR_RW_FCS_ERR_CNT     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_RW_FCS_ERR_CNT_EGR_RW_FCS_ERR_CNT(x)  (x)


/**
 * \brief Count of the number of preamble errors
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_RW:EGR_RW_PREAMBLE_ERR_CNT
 */
#define VTSS_PTP_PROC_EGR_RW_PREAMBLE_ERR_CNT  VTSS_IOREG(VTSS_TO_PTP_PROC,0x907b)
#define LAN80XX_PTP_PROC_EGR_RW_PREAMBLE_ERR_CNT (0x7E)

/**
 * \brief
 * Count of the number of errored preambles detected. The counter wraps. An
 * errored preamble is a preamble that is too short to shrink that is
 * encountered when RW_REDUCE_PREAMBLE is set.
 *
 * \details
 * Binary number
 *
 * Field: ::VTSS_PTP_PROC_EGR_RW_PREAMBLE_ERR_CNT . EGR_RW_PREAMBLE_ERR_CNT
 */
#define  VTSS_F_PTP_PROC_EGR_RW_PREAMBLE_ERR_CNT_EGR_RW_PREAMBLE_ERR_CNT(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_RW_PREAMBLE_ERR_CNT_EGR_RW_PREAMBLE_ERR_CNT     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_RW_PREAMBLE_ERR_CNT_EGR_RW_PREAMBLE_ERR_CNT(x)  (x)

/**
 * Register Group: \a PTP_PROC:EGR_IP_ANALYZER_STAT
 *
 * Analyzer Counters and Errors
 */


/**
 * \brief Analyzer Modified Frames Counter
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_ANALYZER_STAT:EGR_ANALYZER_MOD_FRAMES_CNT
 */
#define VTSS_PTP_PROC_EGR_ANALYZER_MOD_FRAMES_CNT  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9080)

/**
 * \brief
 * Count of the number of frames for which the analyzer generated a valid
 * command
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_ANALYZER_MOD_FRAMES_CNT . EGR_ANALYZER_MOD_FRAMES_CNT
 */
#define  VTSS_F_PTP_PROC_EGR_ANALYZER_MOD_FRAMES_CNT_EGR_ANALYZER_MOD_FRAMES_CNT(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_ANALYZER_MOD_FRAMES_CNT_EGR_ANALYZER_MOD_FRAMES_CNT     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_ANALYZER_MOD_FRAMES_CNT_EGR_ANALYZER_MOD_FRAMES_CNT(x)  (x)

/**
 * Register Group: \a PTP_PROC:EGR_IP_1588_MCH
 *
 * Configure MCH operation
 */


/**
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_MCH:EGR_MCH_CRC_ERR_CNTR
 */
#define VTSS_PTP_PROC_EGR_MCH_CRC_ERR_CNTR   VTSS_IOREG(VTSS_TO_PTP_PROC,0x9081)

/**
 * \brief
 * EGR MCH header CRC byte checkingcounter increments by 1 if CRC derived
 * from MCH header byte 6 to byte 1 is not the same as MCH header byte 7
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_MCH_CRC_ERR_CNTR . EGR_MCH_CRC_ERR_CNTR
 */
#define  VTSS_F_PTP_PROC_EGR_MCH_CRC_ERR_CNTR_EGR_MCH_CRC_ERR_CNTR(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_MCH_CRC_ERR_CNTR_EGR_MCH_CRC_ERR_CNTR     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_MCH_CRC_ERR_CNTR_EGR_MCH_CRC_ERR_CNTR(x)  (x)


/**
 * \details
 * For egress frame in MCH mode.
 * Counter increments
 * When preemption is enabled, ExtTy=2'b01 or 2'b11
 * When preemption is disabled, ExtTy=2'b10 or 2'b11

 *
 * Register: \a PTP_PROC:EGR_IP_1588_MCH:EGR_MCH_EXTTY_MISMATCH_CNTR
 */
#define VTSS_PTP_PROC_EGR_MCH_EXTTY_MISMATCH_CNTR  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9082)

/**
 * \brief
 * For egress frame in MCH mode.Counter incrementsWhen preemption is
 * enabled, ExtTy field in MCH header =2'b01 or 2'b11When preemption is
 * disabled, ExtTy field in MCH header =2'b10 or 2'b11
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_MCH_EXTTY_MISMATCH_CNTR . EGR_MCH_EXTTY_MISMATCH_CNTR
 */
#define  VTSS_F_PTP_PROC_EGR_MCH_EXTTY_MISMATCH_CNTR_EGR_MCH_EXTTY_MISMATCH_CNTR(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_MCH_EXTTY_MISMATCH_CNTR_EGR_MCH_EXTTY_MISMATCH_CNTR     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_MCH_EXTTY_MISMATCH_CNTR_EGR_MCH_EXTTY_MISMATCH_CNTR(x)  (x)


/**
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_MCH:EGR_MCH_CTRL
 */
#define LAN80XX_PTP_PROC_EGR_MCH_CTRL           LAN80XX_IOREG(MMD_ID_PTP_BLOCK,1, 0x9086)


/**
 * \brief
 * 1'b1: drop the frame if extty (H2L) or preamble (H2L/L2H) checking fails
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_MCH_CTRL . EGR_MCH_DROP_EXTTY_PREAMBLE_MISMATCH
 */
#define  VTSS_F_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_DROP_EXTTY_PREAMBLE_MISMATCH(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_DROP_EXTTY_PREAMBLE_MISMATCH  VTSS_BIT(5)
#define  VTSS_X_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_DROP_EXTTY_PREAMBLE_MISMATCH(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Select the MCH header CRC generator1'b0: USXGMII standard1'b1: From
 * Fireant
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_MCH_CTRL . EGR_MCH_CRC_GEN_SEL
 */
#define  LAN80XX_F_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_CRC_GEN_SEL(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_CRC_GEN_SEL     LAN80XX_BIT(4)
#define  LAN80XX_X_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_CRC_GEN_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * 1'b1: drop the frame if H2L MCH header CRC checking fails
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_MCH_CTRL . EGR_MCH_DROP_CRC_ERROR
 */
#define  VTSS_F_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_DROP_CRC_ERROR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_DROP_CRC_ERROR  VTSS_BIT(3)
#define  VTSS_X_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_DROP_CRC_ERROR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

#define  LAN80XX_F_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_DROP_CRC_ERROR(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_DROP_CRC_ERROR  LAN80XX_BIT(3)
#define  LAN80XX_X_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_DROP_CRC_ERROR(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)
/**
 * \brief
 * enable the MCH mode operation
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_MCH_CTRL . EGR_MCH_ENA
 */
#define  VTSS_F_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_ENA  VTSS_BIT(2)
#define  VTSS_X_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

#define  LAN80XX_F_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_ENA(x)  LAN80XX_ENCODE_BITFIELD(x,2,1)
#define  LAN80XX_M_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_ENA  LAN80XX_BIT(2)
#define  LAN80XX_X_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Configure the ingress arrival timestamp field in the MCH header
 * extension [31:0]2'b00: 32 bit nsec [0,0, 30-bit nsec] (short format
 * 32.0)2'b01: 28 bit of ns + 4-bit Fractional ns (short format 28.42'b10:
 * 24-bit of ns + 8-bit of Fractional ns (short format 24.8)2'b11: 16-bit
 * of ns + 16-bit of Fractional ns (short format 16.16)Note that the 16-bit
 * fractional ns format is supported for interoperability reason, even
 * though the 16-bit frac-nsresolution is much higher than the timestamp
 * resolution (8-bit frac-ns). The 8 LSB are set to zero.
 *
 * \details
 * Field: ::LAN80XX_PTP_PROC_EGR_MCH_CTRL . EGR_MCH_IGTS_FMT_SEL
 */
#define  LAN80XX_F_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_IGTS_FMT_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,0,2)
#define  LAN80XX_M_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_IGTS_FMT_SEL     LAN80XX_ENCODE_BITMASK(0,2)
#define  LAN80XX_X_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_IGTS_FMT_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a PTP_PROC:EGR_IP_1588_RSFEC_PHAD
 *
 * High precision event detection Configuration and Status Registers
 */


/**
 * \brief Phase detection control
 *
 * \details
 * For timestamping and phase detection to work reliably, the mac clock
 * domains must be reset after clock change, ie when the link is detected
 * up and stable.
 * If high accuracy detection is to be used:
 *   The PHAD_ENA must be set, TWEAKS should be set to 5, and DIV_CFG
 * should be set to 3. LOCK_ACC will define how big an error at realignment
 * is accepted for the PHAD_LOCK indication to be seen.
 * If high accuracy is not to be used:
 *   The PHAD_ENA should be cleared, and TWEAKS should be set to 7.
 *
 * Register: \a PTP_PROC:EGR_IP_1588_RSFEC_PHAD:EGR_RSFEC_PHAD_CTRL
 */
#define VTSS_PTP_PROC_EGR_RSFEC_PHAD_CTRL    VTSS_IOREG(VTSS_TO_PTP_PROC,0x9084)
#define LAN80XX_PTP_PROC_EGR_RSFEC_PHAD_CTRL LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1, 9087)
/**
 * \brief
 * Enable phase detector. The default is enabled
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RSFEC_PHAD_CTRL . EGR_CFG_RX_ENA
 */
#define  VTSS_F_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_RX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_RX_ENA  VTSS_BIT(18)
#define  VTSS_X_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_RX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Accuracy of lock logic 2**-x nsec
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RSFEC_PHAD_CTRL . EGR_CFG_LOCK_ACC
 */
#define  VTSS_F_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_LOCK_ACC(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_LOCK_ACC     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_LOCK_ACC(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * Internal tweaks on how port period is analyzed
 *
 * \details
 * x00: Count once and adjust 0.2 fs at reallignment
 * x01: Count once and adjust 16 fs at reallignment
 * x10: Recount and disable error feedback from allignment
 * x11: Count once after change in reset or phad_ena and keep as fixed
 * 0xx: Count for 1k port cycles when evaluating port period
 * 1xx: Count for 16k port cycle when evaluating port period
 *
 * Field: ::VTSS_PTP_PROC_EGR_RSFEC_PHAD_CTRL . EGR_CFG_TWEAKS
 */
#define  VTSS_F_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_TWEAKS(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_TWEAKS     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_TWEAKS(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * Alignment offset 2**-x nsec
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RSFEC_PHAD_CTRL . EGR_CFG_PHAD_MODE
 */
#define  VTSS_F_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_PHAD_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_PHAD_MODE  VTSS_BIT(11)
#define  VTSS_X_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_PHAD_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Divide port clock by the power of this
 *
 * \details
 * 0: Do not divide.
 * 1: Divide port clock by two.
 * 2: Divide port clock by four
 * 15: Automode.
 *
 * Field: ::VTSS_PTP_PROC_EGR_RSFEC_PHAD_CTRL . EGR_CFG_DIV_MODE
 */
#define  LAN80XX_F_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_DIV_MODE(x)  LAN80XX_ENCODE_BITFIELD(x,8,3)
#define  LAN80XX_M_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_DIV_MODE     LAN80XX_ENCODE_BITMASK(8,3)
#define  LAN80XX_X_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_DIV_MODE(x)  LAN80XX_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * When set, PHAD_ERR_STAT returns the largest error seen since this field
 * is set.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RSFEC_PHAD_CTRL . EGR_CFG_ERR_MAX_ENA
 */
#define  VTSS_F_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_ERR_MAX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_ERR_MAX_ENA  VTSS_BIT(7)
#define  VTSS_X_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_ERR_MAX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Phase detector has lost lock since the clearing of the bit. Can be
 * cleared writing one to this field.
 *       This field become unreliable for event clocks slower than 10
 * MHz, but phase detection can still be trusted. Slow event clocks are
 * only seen in synchronuous PPS detection.

 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RSFEC_PHAD_CTRL . EGR_STAT_FAILED
 */
#define  VTSS_F_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_STAT_FAILED(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_STAT_FAILED  VTSS_BIT(6)
#define  VTSS_X_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_STAT_FAILED(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Phase detector is locked to port clock
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RSFEC_PHAD_CTRL . EGR_STAT_LOCKED
 */
#define  LAN80XX_F_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_STAT_LOCKED(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_STAT_LOCKED  LAN80XX_BIT(5)
#define  LAN80XX_X_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_STAT_LOCKED(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Phase detector has adjusted phase down(bit 0) or up(bit 1).

 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RSFEC_PHAD_CTRL . EGR_STAT_ADJUSTED
 */
#define  VTSS_F_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_STAT_ADJUSTED(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_STAT_ADJUSTED     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_STAT_ADJUSTED(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Event clock is currently divided by the power of this
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RSFEC_PHAD_CTRL . EGR_STAT_DIV_STATE
 */
#define  VTSS_F_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_STAT_DIV_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_STAT_DIV_STATE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_STAT_DIV_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Phase detection status
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP_PROC:EGR_IP_1588_RSFEC_PHAD:EGR_RSFEC_PHAD_CYC_TIME
 */
#define VTSS_PTP_PROC_EGR_RSFEC_PHAD_CYC_TIME  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9085)

/**
 * \brief
 * Detected event clock period in 8.8 fixedpoint format.The lower 8-bit is
 * fnsthe upper 8-bit is ns
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RSFEC_PHAD_CYC_TIME . EGR_STAT_CYC_TIME
 */
#define  VTSS_F_PTP_PROC_EGR_RSFEC_PHAD_CYC_TIME_EGR_STAT_CYC_TIME(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_RSFEC_PHAD_CYC_TIME_EGR_STAT_CYC_TIME     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_RSFEC_PHAD_CYC_TIME_EGR_STAT_CYC_TIME(x)  (x)


/**
 * \brief Phase detection error
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP_PROC:EGR_IP_1588_RSFEC_PHAD:EGR_RSFEC_PHAD_ERR_STATE
 */
#define VTSS_PTP_PROC_EGR_RSFEC_PHAD_ERR_STATE  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9086)

/**
 * \brief
 * Latest or maximum error detected in alignment process, with format 10.8
 * fixedpoint format. ERR_MAX_ENA determines mode.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_RSFEC_PHAD_ERR_STATE . EGR_STAT_ERR_STATE
 */
#define  VTSS_F_PTP_PROC_EGR_RSFEC_PHAD_ERR_STATE_EGR_STAT_ERR_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_PTP_PROC_EGR_RSFEC_PHAD_ERR_STATE_EGR_STAT_ERR_STATE     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_PTP_PROC_EGR_RSFEC_PHAD_ERR_STATE_EGR_STAT_ERR_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,19)

/**
 * Register Group: \a PTP_PROC:EGR_IP_1588_SOF_PHAD
 *
 * High precission event detection Configuration and Status Registers
 */


/**
 * \brief Phase detection control
 *
 * \details
 * For timestamping and phase detection to work reliably, the mac clock
 * domains must be reset after clock change, ie when the link is detected
 * up and stable.
 * If high accuracy detection is to be used:
 *   The PHAD_ENA must be set, TWEAKS should be set to 5, and DIV_CFG
 * should be set to 3. LOCK_ACC will define how big an error at realignment
 * is accepted for the PHAD_LOCK indication to be seen.
 * If high accuracy is not to be used:
 *   The PHAD_ENA should be cleared, and TWEAKS should be set to 7.
 *
 * Register: \a PTP_PROC:EGR_IP_1588_SOF_PHAD:EGR_SOF_PHAD_CTRL
 */
#define VTSS_PTP_PROC_EGR_SOF_PHAD_CTRL      VTSS_IOREG(VTSS_TO_PTP_PROC,0x9087)
#define LAN80XX_PTP_PROC_EGR_SOF_PHAD_CTRL   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1, 0x908A)

/**
 * \brief
 * Enable phase detector. The default is enable.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SOF_PHAD_CTRL . EGR_CFG_RX_ENA
 */
#define  LAN80XX_F_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_RX_ENA(x)  LAN80XX_ENCODE_BITFIELD((x),18,1)
#define  LAN80XX_M_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_RX_ENA     LAN80XX_BIT(18)
#define  LAN80XX_X_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_RX_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Accuracy of lock logic 2**-x nsec
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SOF_PHAD_CTRL . EGR_CFG_LOCK_ACC
 */
#define  VTSS_F_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_LOCK_ACC(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_LOCK_ACC     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_LOCK_ACC(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * Internal tweaks on how port period is analyzed
 *
 * \details
 * x00: Count once and adjust 0.2 fs at reallignment
 * x01: Count once and adjust 16 fs at reallignment
 * x10: Recount and disable error feedback from allignment
 * x11: Count once after change in reset or phad_ena and keep as fixed
 * 0xx: Count for 1k port cycles when evaluating port period
 * 1xx: Count for 16k port cycle when evaluating port period
 *
 * Field: ::VTSS_PTP_PROC_EGR_SOF_PHAD_CTRL . EGR_CFG_TWEAKS
 */
#define  VTSS_F_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_TWEAKS(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_TWEAKS     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_TWEAKS(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * Alignment offset 2**-x nsec
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SOF_PHAD_CTRL . EGR_CFG_PHAD_MODE
 */
#define  VTSS_F_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_PHAD_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_PHAD_MODE  VTSS_BIT(11)
#define  VTSS_X_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_PHAD_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Divide port clock by the power of this
 *
 * \details
 * 0: Do not divide.
 * 1: Divide port clock by two.
 * 2: Divide port clock by four
 * 15: Automode.
 *
 * Field: ::VTSS_PTP_PROC_EGR_SOF_PHAD_CTRL . EGR_CFG_DIV_MODE
 */
#define  LAN80XX_F_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_DIV_MODE(x)  LAN80XX_ENCODE_BITFIELD(x,8,3)
#define  LAN80XX_M_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_DIV_MODE     LAN80XX_ENCODE_BITMASK(8,3)
#define  LAN80XX_X_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_DIV_MODE(x)  LAN80XX_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * When set, PHAD_ERR_STAT returns the largest error seen since this field
 * is set.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SOF_PHAD_CTRL . EGR_CFG_ERR_MAX_ENA
 */
#define  VTSS_F_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_ERR_MAX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_ERR_MAX_ENA  VTSS_BIT(7)
#define  VTSS_X_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_ERR_MAX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Phase detector has lost lock since the clearing of the bit. Can be
 * cleared writing one to this field.
 *       This field become unreliable for event clocks slower than 10
 * MHz, but phase detection can still be trusted. Slow event clocks are
 * only seen in synchronuous PPS detection.

 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SOF_PHAD_CTRL . EGR_STAT_FAILED
 */
#define  VTSS_F_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_STAT_FAILED(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_STAT_FAILED  VTSS_BIT(6)
#define  VTSS_X_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_STAT_FAILED(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Phase detector is locked to port clock
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SOF_PHAD_CTRL . EGR_STAT_LOCKED
 */
#define  LAN80XX_F_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_STAT_LOCKED(x)  LAN80XX_ENCODE_BITFIELD((x),5,1)
#define  LAN80XX_M_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_STAT_LOCKED     LAN80XX_BIT(5)
#define  LAN80XX_X_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_STAT_LOCKED(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Phase detector has adjusted phase down(bit 0) or up(bit 1).

 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SOF_PHAD_CTRL . EGR_STAT_ADJUSTED
 */
#define  VTSS_F_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_STAT_ADJUSTED(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_STAT_ADJUSTED     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_STAT_ADJUSTED(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Event clock is currently divided by the power of this
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SOF_PHAD_CTRL . EGR_STAT_DIV_STATE
 */
#define  VTSS_F_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_STAT_DIV_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_STAT_DIV_STATE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_STAT_DIV_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Phase detection status
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP_PROC:EGR_IP_1588_SOF_PHAD:EGR_SOF_PHAD_CYC_TIME
 */
#define VTSS_PTP_PROC_EGR_SOF_PHAD_CYC_TIME  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9088)

/**
 * \brief
 * Detected event clock period in 8.8 fixedpoint format.The lower 8-bit is
 * fnsthe upper 8-bit is ns
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SOF_PHAD_CYC_TIME . EGR_STAT_CYC_TIME
 */
#define  VTSS_F_PTP_PROC_EGR_SOF_PHAD_CYC_TIME_EGR_STAT_CYC_TIME(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_SOF_PHAD_CYC_TIME_EGR_STAT_CYC_TIME     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_SOF_PHAD_CYC_TIME_EGR_STAT_CYC_TIME(x)  (x)


/**
 * \brief Phase detection error
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP_PROC:EGR_IP_1588_SOF_PHAD:EGR_SOF_PHAD_ERR_STATE
 */
#define VTSS_PTP_PROC_EGR_SOF_PHAD_ERR_STATE  VTSS_IOREG(VTSS_TO_PTP_PROC,0x9089)

/**
 * \brief
 * Latest or maximum error detected in alignment process, with format 10.8
 * fixedpoint format. ERR_MAX_ENA determines mode.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SOF_PHAD_ERR_STATE . EGR_STAT_ERR_STATE
 */
#define  VTSS_F_PTP_PROC_EGR_SOF_PHAD_ERR_STATE_EGR_STAT_ERR_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_PTP_PROC_EGR_SOF_PHAD_ERR_STATE_EGR_STAT_ERR_STATE     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_PTP_PROC_EGR_SOF_PHAD_ERR_STATE_EGR_STAT_ERR_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,19)

/**
 * Register Group: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS
 *
 * Provides the ability to read the IP1588 internal registers
 */


/**
 * \brief Part1 of command data generated by analyzer
 *
 * \details
 * This will provide the ability to check the command generated by analyzer
 * to the rewriter
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_ANA_CMD_FIFO_DATA1
 */
#define VTSS_PTP_PROC_INGR_ANA_CMD_FIFO_DATA1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90a4)

/**
 * \brief
 * This will provide the ability to check the command generated by analyzer
 * to the rewriter
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_ANA_CMD_FIFO_DATA1 . INGR_ANA_CMD_FIFO_DATA1
 */
#define  VTSS_F_PTP_PROC_INGR_ANA_CMD_FIFO_DATA1_INGR_ANA_CMD_FIFO_DATA1(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_ANA_CMD_FIFO_DATA1_INGR_ANA_CMD_FIFO_DATA1     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_ANA_CMD_FIFO_DATA1_INGR_ANA_CMD_FIFO_DATA1(x)  (x)


/**
 * \brief Part2 of command data generated by analyzer
 *
 * \details
 * This will provide the ability to check the command generated by analyzer
 * to the rewriter
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_ANA_CMD_FIFO_DATA2
 */
#define VTSS_PTP_PROC_INGR_ANA_CMD_FIFO_DATA2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90a5)

/**
 * \brief
 * This will provide the ability to check the command generated by analyzer
 * to the rewriter
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_ANA_CMD_FIFO_DATA2 . INGR_ANA_CMD_FIFO_DATA2
 */
#define  VTSS_F_PTP_PROC_INGR_ANA_CMD_FIFO_DATA2_INGR_ANA_CMD_FIFO_DATA2(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_PTP_PROC_INGR_ANA_CMD_FIFO_DATA2_INGR_ANA_CMD_FIFO_DATA2     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_PTP_PROC_INGR_ANA_CMD_FIFO_DATA2_INGR_ANA_CMD_FIFO_DATA2(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief Status signals of Analyzer
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_ANALYZER_STATUS
 */
#define VTSS_PTP_PROC_INGR_ANALYZER_STATUS   VTSS_IOREG(VTSS_TO_PTP_PROC,0x90a6)

/**
 * \brief
 * The value indicates the flow number when strict flow is enabled
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_ANALYZER_STATUS . INGR_FLOW_NUMBER
 */
#define  VTSS_F_PTP_PROC_INGR_ANALYZER_STATUS_INGR_FLOW_NUMBER(x)  VTSS_ENCODE_BITFIELD(x,6,4)
#define  VTSS_M_PTP_PROC_INGR_ANALYZER_STATUS_INGR_FLOW_NUMBER     VTSS_ENCODE_BITMASK(6,4)
#define  VTSS_X_PTP_PROC_INGR_ANALYZER_STATUS_INGR_FLOW_NUMBER(x)  VTSS_EXTRACT_BITFIELD(x,6,4)

/**
 * \brief
 * The value indicates the analyzer command generated by the analyzer.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_ANALYZER_STATUS . INGR_ANALYZER_CMD
 */
#define  VTSS_F_PTP_PROC_INGR_ANALYZER_STATUS_INGR_ANALYZER_CMD(x)  VTSS_ENCODE_BITFIELD(x,2,4)
#define  VTSS_M_PTP_PROC_INGR_ANALYZER_STATUS_INGR_ANALYZER_CMD     VTSS_ENCODE_BITMASK(2,4)
#define  VTSS_X_PTP_PROC_INGR_ANALYZER_STATUS_INGR_ANALYZER_CMD(x)  VTSS_EXTRACT_BITFIELD(x,2,4)

/**
 * \brief
 * Indicates the matched engine number.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_ANALYZER_STATUS . INGR_ANALYZER_ENGINE
 */
#define  VTSS_F_PTP_PROC_INGR_ANALYZER_STATUS_INGR_ANALYZER_ENGINE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_PTP_PROC_INGR_ANALYZER_STATUS_INGR_ANALYZER_ENGINE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_PTP_PROC_INGR_ANALYZER_STATUS_INGR_ANALYZER_ENGINE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Predictor variable delay1
 *
 * \details
 * Predictor variable stall latency 1.
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_PREDICTOR_VAR_DELAY1
 */
#define VTSS_PTP_PROC_INGR_PREDICTOR_VAR_DELAY1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90a7)

/**
 * \brief
 * Predictor variable stall latency 1.bit [25:8] is ns fieldbit [7:0] is
 * sub-ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_PREDICTOR_VAR_DELAY1 . INGR_PREDICTOR_VAR_DELAY1
 */
#define  VTSS_F_PTP_PROC_INGR_PREDICTOR_VAR_DELAY1_INGR_PREDICTOR_VAR_DELAY1(x)  VTSS_ENCODE_BITFIELD(x,0,26)
#define  VTSS_M_PTP_PROC_INGR_PREDICTOR_VAR_DELAY1_INGR_PREDICTOR_VAR_DELAY1     VTSS_ENCODE_BITMASK(0,26)
#define  VTSS_X_PTP_PROC_INGR_PREDICTOR_VAR_DELAY1_INGR_PREDICTOR_VAR_DELAY1(x)  VTSS_EXTRACT_BITFIELD(x,0,26)


/**
 * \brief Predictor variable delay 2
 *
 * \details
 * Predictor variable stall latency 2
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_PREDICTOR_VAR_DELAY2
 */
#define VTSS_PTP_PROC_INGR_PREDICTOR_VAR_DELAY2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90a8)

/**
 * \brief
 * Predictor variable stall latency 2bit [25:8] is ns fieldbit [7:0] is
 * sub-ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_PREDICTOR_VAR_DELAY2 . INGR_PREDICTOR_VAR_DELAY2
 */
#define  VTSS_F_PTP_PROC_INGR_PREDICTOR_VAR_DELAY2_INGR_PREDICTOR_VAR_DELAY2(x)  VTSS_ENCODE_BITFIELD(x,0,26)
#define  VTSS_M_PTP_PROC_INGR_PREDICTOR_VAR_DELAY2_INGR_PREDICTOR_VAR_DELAY2     VTSS_ENCODE_BITMASK(0,26)
#define  VTSS_X_PTP_PROC_INGR_PREDICTOR_VAR_DELAY2_INGR_PREDICTOR_VAR_DELAY2(x)  VTSS_EXTRACT_BITFIELD(x,0,26)


/**
 * \brief Predictor variable delay 3
 *
 * \details
 * Predictor variable stall latency 3
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_PREDICTOR_VAR_DELAY3
 */
#define VTSS_PTP_PROC_INGR_PREDICTOR_VAR_DELAY3  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90a9)

/**
 * \brief
 * Predictor variable stall latency 3bit [25:8] is ns fieldbit [7:0] is
 * sub-ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_PREDICTOR_VAR_DELAY3 . INGR_PREDICTOR_VAR_DELAY3
 */
#define  VTSS_F_PTP_PROC_INGR_PREDICTOR_VAR_DELAY3_INGR_PREDICTOR_VAR_DELAY3(x)  VTSS_ENCODE_BITFIELD(x,0,26)
#define  VTSS_M_PTP_PROC_INGR_PREDICTOR_VAR_DELAY3_INGR_PREDICTOR_VAR_DELAY3     VTSS_ENCODE_BITMASK(0,26)
#define  VTSS_X_PTP_PROC_INGR_PREDICTOR_VAR_DELAY3_INGR_PREDICTOR_VAR_DELAY3(x)  VTSS_EXTRACT_BITFIELD(x,0,26)


/**
 * \brief Gives rewriter modifications on packet
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_REWRITER_OPMODE
 */
#define VTSS_PTP_PROC_INGR_REWRITER_OPMODE   VTSS_IOREG(VTSS_TO_PTP_PROC,0x90aa)

/**
 * \brief
 * Gives rewriter modifications on packet based on opmode configuration.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_REWRITER_OPMODE . INGR_REWRITER_OPMODE
 */
#define  VTSS_F_PTP_PROC_INGR_REWRITER_OPMODE_INGR_REWRITER_OPMODE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_PROC_INGR_REWRITER_OPMODE_INGR_REWRITER_OPMODE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_PROC_INGR_REWRITER_OPMODE_INGR_REWRITER_OPMODE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Indicates valid cf if asserted.
 *
 * \details
 *
 * Indicates valid cf if asserted.

 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_CORRECTION_FIELD_VLD
 */
#define VTSS_PTP_PROC_INGR_CORRECTION_FIELD_VLD  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90ab)

/**
 * \brief
 * Indicates valid cf if asserted.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_CORRECTION_FIELD_VLD . INGR_CORRECTION_FIELD_VALID
 */
#define  VTSS_F_PTP_PROC_INGR_CORRECTION_FIELD_VLD_INGR_CORRECTION_FIELD_VALID(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_INGR_CORRECTION_FIELD_VLD_INGR_CORRECTION_FIELD_VALID  VTSS_BIT(0)
#define  VTSS_X_PTP_PROC_INGR_CORRECTION_FIELD_VLD_INGR_CORRECTION_FIELD_VALID(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief correction field value lsb [31:0]  of new_cf[63:0] from rewriter fifo.
 *
 * \details
 * correction field value lsb [31:0]  of new_cf[63:0] from rewriter fifo.
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_CORRECTION_FIELD_VALUE1
 */
#define VTSS_PTP_PROC_INGR_CORRECTION_FIELD_VALUE1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90ac)

/**
 * \brief
 * correction field value lsb [31:0]  of new_cf[63:0].
 *
 * \details
 * Binary
 *
 * Field: ::VTSS_PTP_PROC_INGR_CORRECTION_FIELD_VALUE1 . INGR_CORRECTION_FIELD_VALUE_1
 */
#define  VTSS_F_PTP_PROC_INGR_CORRECTION_FIELD_VALUE1_INGR_CORRECTION_FIELD_VALUE_1(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_CORRECTION_FIELD_VALUE1_INGR_CORRECTION_FIELD_VALUE_1     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_CORRECTION_FIELD_VALUE1_INGR_CORRECTION_FIELD_VALUE_1(x)  (x)


/**
 * \brief correction field value lsb [63:32]  of new_cf[63:0] from rewriter fifo
 *
 * \details
 * correction field value lsb [63:32]  of new_cf[63:0] from rewriter fifo
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_CORRECTION_FIELD_VALUE2
 */
#define VTSS_PTP_PROC_INGR_CORRECTION_FIELD_VALUE2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90ad)

/**
 * \brief
 * correction field value lsb [63:32]  of new_cf[63:0]
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_CORRECTION_FIELD_VALUE2 . INGR_CORRECTION_FIELD_VALUE_2
 */
#define  VTSS_F_PTP_PROC_INGR_CORRECTION_FIELD_VALUE2_INGR_CORRECTION_FIELD_VALUE_2(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_CORRECTION_FIELD_VALUE2_INGR_CORRECTION_FIELD_VALUE_2     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_CORRECTION_FIELD_VALUE2_INGR_CORRECTION_FIELD_VALUE_2(x)  (x)


/**
 * \brief lsb (31:0] of new_field_o[79:0] from tsp.v
 *
 * \details
 * lsb (31:0] of new_field_o[79:0] from tsp.v
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_TIMESTAMP_VALUE1
 */
#define VTSS_PTP_PROC_INGR_TIMESTAMP_VALUE1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90ae)

/**
 * \brief
 * lsb (31:0] of new_field_o[79:0] from rewriter fifo
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TIMESTAMP_VALUE1 . INGR_TIMESTAMP_VALUE_1
 */
#define  VTSS_F_PTP_PROC_INGR_TIMESTAMP_VALUE1_INGR_TIMESTAMP_VALUE_1(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TIMESTAMP_VALUE1_INGR_TIMESTAMP_VALUE_1     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TIMESTAMP_VALUE1_INGR_TIMESTAMP_VALUE_1(x)  (x)


/**
 * \brief lsb (63:32] of new_field_o[79:0] from rewriter fifo
 *
 * \details
 * lsb (63:32] of new_field_o[79:0] from rewriter fifo
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_TIMESTAMP_VALUE2
 */
#define VTSS_PTP_PROC_INGR_TIMESTAMP_VALUE2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90af)

/**
 * \brief
 * lsb (63:32] of new_field_o[79:0] from rewriter fifo
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TIMESTAMP_VALUE2 . INGR_TIMESTAMP_VALUE_2
 */
#define  VTSS_F_PTP_PROC_INGR_TIMESTAMP_VALUE2_INGR_TIMESTAMP_VALUE_2(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TIMESTAMP_VALUE2_INGR_TIMESTAMP_VALUE_2     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TIMESTAMP_VALUE2_INGR_TIMESTAMP_VALUE_2(x)  (x)


/**
 * \brief Msb (79:64] of new_field_o[79:0] from rewriter fifo
 *
 * \details
 * Msb (79:64] of new_field_o[79:0] from rewriter fifo
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_TIMESTAMP_VALUE3
 */
#define VTSS_PTP_PROC_INGR_TIMESTAMP_VALUE3  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90b0)

/**
 * \brief
 * Msb (79:64] of new_field_o[79:0] from rewriter fifo
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TIMESTAMP_VALUE3 . INGR_TIMESTAMP_VALUE_3
 */
#define  VTSS_F_PTP_PROC_INGR_TIMESTAMP_VALUE3_INGR_TIMESTAMP_VALUE_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_PROC_INGR_TIMESTAMP_VALUE3_INGR_TIMESTAMP_VALUE_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_PROC_INGR_TIMESTAMP_VALUE3_INGR_TIMESTAMP_VALUE_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Configure LTC read type
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_LTC_READ
 */
#define VTSS_PTP_PROC_INGR_LTC_READ          VTSS_IOREG(VTSS_TO_PTP_PROC,0x90b1)

/**
 * \brief
 * When this bit is 1'b1, LTC value is read into LTC_SEC_H, LTC_SEC_L &
 * LTC_NS registers on every SOF.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_LTC_READ . INGR_LTC_READ_ON_SOF
 */
#define  VTSS_F_PTP_PROC_INGR_LTC_READ_INGR_LTC_READ_ON_SOF(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PTP_PROC_INGR_LTC_READ_INGR_LTC_READ_ON_SOF  VTSS_BIT(1)
#define  VTSS_X_PTP_PROC_INGR_LTC_READ_INGR_LTC_READ_ON_SOF(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When this bit is set to 1'b1, current LTC value is read into LTC_SEC_H,
 * LTC_SEC_L & LTC_NS registers.This bit is cleared by hardware after the
 * operation is completed.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_LTC_READ . INGR_LTC_ONE_SHOT_READ
 */
#define  VTSS_F_PTP_PROC_INGR_LTC_READ_INGR_LTC_ONE_SHOT_READ(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_INGR_LTC_READ_INGR_LTC_ONE_SHOT_READ  VTSS_BIT(0)
#define  VTSS_X_PTP_PROC_INGR_LTC_READ_INGR_LTC_ONE_SHOT_READ(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief LTC seconds (high)
 *
 * \details
 * LTC seconds (high)
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_LTC_SEC_H
 */
#define VTSS_PTP_PROC_INGR_LTC_SEC_H         VTSS_IOREG(VTSS_TO_PTP_PROC,0x90b2)

/**
 * \brief
 * LTC seconds (high) in debug mode
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_LTC_SEC_H . INGR_LTC_SEC_H
 */
#define  VTSS_F_PTP_PROC_INGR_LTC_SEC_H_INGR_LTC_SEC_H(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_PROC_INGR_LTC_SEC_H_INGR_LTC_SEC_H     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_PROC_INGR_LTC_SEC_H_INGR_LTC_SEC_H(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LTC seconds (low)
 *
 * \details
 * LTC seconds (low)
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_LTC_SEC_L
 */
#define VTSS_PTP_PROC_INGR_LTC_SEC_L         VTSS_IOREG(VTSS_TO_PTP_PROC,0x90b3)

/**
 * \brief
 * LTC seconds (low) in debug mode
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_LTC_SEC_L . INGR_LTC_SEC_L
 */
#define  VTSS_F_PTP_PROC_INGR_LTC_SEC_L_INGR_LTC_SEC_L(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_LTC_SEC_L_INGR_LTC_SEC_L     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_LTC_SEC_L_INGR_LTC_SEC_L(x)  (x)


/**
 * \brief LTC nanoseconds
 *
 * \details
 * LTC nanoseconds
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_LTC_NS
 */
#define VTSS_PTP_PROC_INGR_LTC_NS            VTSS_IOREG(VTSS_TO_PTP_PROC,0x90b4)

/**
 * \brief
 * LTC nanoseconds in debug mode
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_LTC_NS . INGR_LTC_NS
 */
#define  VTSS_F_PTP_PROC_INGR_LTC_NS_INGR_LTC_NS(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_LTC_NS_INGR_LTC_NS     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_LTC_NS_INGR_LTC_NS(x)  (x)


/**
 * \brief LTC sub-nanoseconds
 *
 * \details
 * LTC sub-nanoseconds
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_LTC_SNS
 */
#define VTSS_PTP_PROC_INGR_LTC_SNS           VTSS_IOREG(VTSS_TO_PTP_PROC,0x90b5)

/**
 * \brief
 * LTC sub-nanosecond in debug mode
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_LTC_SNS . INGR_LTC_SNS
 */
#define  VTSS_F_PTP_PROC_INGR_LTC_SNS_INGR_LTC_SNS(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PROC_INGR_LTC_SNS_INGR_LTC_SNS     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PROC_INGR_LTC_SNS_INGR_LTC_SNS(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Extracted correction field LSB
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_EXTRACTED_CF1
 */
#define VTSS_PTP_PROC_INGR_EXTRACTED_CF1     VTSS_IOREG(VTSS_TO_PTP_PROC,0x90b6)

/**
 * \brief
 * Extracted correction field value LSB [31:0]
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_EXTRACTED_CF1 . INGR_EXTRACTED_CF1
 */
#define  VTSS_F_PTP_PROC_INGR_EXTRACTED_CF1_INGR_EXTRACTED_CF1(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_EXTRACTED_CF1_INGR_EXTRACTED_CF1     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_EXTRACTED_CF1_INGR_EXTRACTED_CF1(x)  (x)


/**
 * \brief Extracted correction field MSB
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_EXTRACTED_CF2
 */
#define VTSS_PTP_PROC_INGR_EXTRACTED_CF2     VTSS_IOREG(VTSS_TO_PTP_PROC,0x90b7)

/**
 * \brief
 * Extracted correction field value MSB[63:32]
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_EXTRACTED_CF2 . INGR_EXTRACTED_CF2
 */
#define  VTSS_F_PTP_PROC_INGR_EXTRACTED_CF2_INGR_EXTRACTED_CF2(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_EXTRACTED_CF2_INGR_EXTRACTED_CF2     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_EXTRACTED_CF2_INGR_EXTRACTED_CF2(x)  (x)


/**
 * \brief Stored Timestamp
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_STORED_TIMESTAMP
 */
#define VTSS_PTP_PROC_INGR_STORED_TIMESTAMP  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90b8)

/**
 * \brief
 * Stored timestamp value from ingress The associated sub-nan info is
 * included in the CF and can not be decided and provided for debugging
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_STORED_TIMESTAMP . INGR_STORED_TIMESTAMP
 */
#define  VTSS_F_PTP_PROC_INGR_STORED_TIMESTAMP_INGR_STORED_TIMESTAMP(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_STORED_TIMESTAMP_INGR_STORED_TIMESTAMP     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_STORED_TIMESTAMP_INGR_STORED_TIMESTAMP(x)  (x)


/**
 * \brief Active time stamp sub-nans [7:0]
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_ACTIVE_TIMESTAMP0
 */
#define VTSS_PTP_PROC_INGR_ACTIVE_TIMESTAMP0  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90b9)

/**
 * \brief
 * Active time stamp [7:0] of sub-ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_ACTIVE_TIMESTAMP0 . INGR_ACTIVE_TIMESTAMP0
 */
#define  VTSS_F_PTP_PROC_INGR_ACTIVE_TIMESTAMP0_INGR_ACTIVE_TIMESTAMP0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PROC_INGR_ACTIVE_TIMESTAMP0_INGR_ACTIVE_TIMESTAMP0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PROC_INGR_ACTIVE_TIMESTAMP0_INGR_ACTIVE_TIMESTAMP0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Active time stamp ns [31:0]
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_ACTIVE_TIMESTAMP1
 */
#define VTSS_PTP_PROC_INGR_ACTIVE_TIMESTAMP1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90ba)

/**
 * \brief
 * Active time stamp [31:0] of ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_ACTIVE_TIMESTAMP1 . INGR_ACTIVE_TIMESTAMP1
 */
#define  VTSS_F_PTP_PROC_INGR_ACTIVE_TIMESTAMP1_INGR_ACTIVE_TIMESTAMP1(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_ACTIVE_TIMESTAMP1_INGR_ACTIVE_TIMESTAMP1     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_ACTIVE_TIMESTAMP1_INGR_ACTIVE_TIMESTAMP1(x)  (x)


/**
 * \brief Active time stamp ns [46:32]
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_ACTIVE_TIMESTAMP2
 */
#define VTSS_PTP_PROC_INGR_ACTIVE_TIMESTAMP2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90bb)

/**
 * \brief
 * Active time stamp [46:32]  of ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_ACTIVE_TIMESTAMP2 . INGR_ACTIVE_TIMESTAMP2
 */
#define  VTSS_F_PTP_PROC_INGR_ACTIVE_TIMESTAMP2_INGR_ACTIVE_TIMESTAMP2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_PROC_INGR_ACTIVE_TIMESTAMP2_INGR_ACTIVE_TIMESTAMP2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_PROC_INGR_ACTIVE_TIMESTAMP2_INGR_ACTIVE_TIMESTAMP2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Predictor delay used and the number of PTP frames matched
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_PREDICTOR_VALUES
 */
#define VTSS_PTP_PROC_INGR_PREDICTOR_VALUES  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90bc)

/**
 * \brief
 * Indicates a artificial push into timestamp processor. Corresponding
 * offset for this push will be random and calib_error will be asserted.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_PREDICTOR_VALUES . INGR_TSP_PUSH_FLAG
 */
#define  VTSS_F_PTP_PROC_INGR_PREDICTOR_VALUES_INGR_TSP_PUSH_FLAG(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PTP_PROC_INGR_PREDICTOR_VALUES_INGR_TSP_PUSH_FLAG  VTSS_BIT(28)
#define  VTSS_X_PTP_PROC_INGR_PREDICTOR_VALUES_INGR_TSP_PUSH_FLAG(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * The number of matched PTP frames
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_PREDICTOR_VALUES . INGR_PTP_FRM_CNT
 */
#define  VTSS_F_PTP_PROC_INGR_PREDICTOR_VALUES_INGR_PTP_FRM_CNT(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_PTP_PROC_INGR_PREDICTOR_VALUES_INGR_PTP_FRM_CNT     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_PTP_PROC_INGR_PREDICTOR_VALUES_INGR_PTP_FRM_CNT(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/**
 * \brief
 * The value of the predictor variable delay usedbit [25:8] is ns fieldbit
 * [7:0] is sub-ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_PREDICTOR_VALUES . INGR_VAR_DELAY_USED
 */
#define  VTSS_F_PTP_PROC_INGR_PREDICTOR_VALUES_INGR_VAR_DELAY_USED(x)  VTSS_ENCODE_BITFIELD(x,0,26)
#define  VTSS_M_PTP_PROC_INGR_PREDICTOR_VALUES_INGR_VAR_DELAY_USED     VTSS_ENCODE_BITMASK(0,26)
#define  VTSS_X_PTP_PROC_INGR_PREDICTOR_VALUES_INGR_VAR_DELAY_USED(x)  VTSS_EXTRACT_BITFIELD(x,0,26)


/**
 * \brief Current and Next States of FSMs in rw_cmd_write[0:3], rw_cmd_cfwrite[7:4] and rw_cmd_clear[11:8]
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_REWRITER_FSM_STATES
 */
#define VTSS_PTP_PROC_INGR_REWRITER_FSM_STATES  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90bd)

/**
 * \brief
 * Next State[1:0]  of module <rw_cmd_cfwrite.v>
 *
 * \details
 * binary
 *
 * Field: ::VTSS_PTP_PROC_INGR_REWRITER_FSM_STATES . INGR_NEXT_STATE_CMD_CLEAR
 */
#define  VTSS_F_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_NEXT_STATE_CMD_CLEAR(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_NEXT_STATE_CMD_CLEAR     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_NEXT_STATE_CMD_CLEAR(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/**
 * \brief
 * Current State[1:0]  of module <rw_cmd_clear.v>
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_REWRITER_FSM_STATES . INGR_CURRENT_STATE_CMD_CLEAR
 */
#define  VTSS_F_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_CURRENT_STATE_CMD_CLEAR(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_CURRENT_STATE_CMD_CLEAR     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_CURRENT_STATE_CMD_CLEAR(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Next State[1:0]  of module <rw_cmd_cfwrite.v>
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_REWRITER_FSM_STATES . INGR_NEXT_STATE_CMD_CFWRITE
 */
#define  VTSS_F_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_NEXT_STATE_CMD_CFWRITE(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_NEXT_STATE_CMD_CFWRITE     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_NEXT_STATE_CMD_CFWRITE(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * Current State[1:0]  of module <rw_cmd_cfwrite.v>
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_REWRITER_FSM_STATES . INGR_CURRENT_STATE_CMD_CFWRITE
 */
#define  VTSS_F_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_CURRENT_STATE_CMD_CFWRITE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_CURRENT_STATE_CMD_CFWRITE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_CURRENT_STATE_CMD_CFWRITE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Next State[1:0]  of module <rw_cmd_write.v>
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_REWRITER_FSM_STATES . INGR_NEXT_STATE_CMD_WRITE
 */
#define  VTSS_F_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_NEXT_STATE_CMD_WRITE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_NEXT_STATE_CMD_WRITE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_NEXT_STATE_CMD_WRITE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Current State[1:0]  of module <rw_cmd_write.v>
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_REWRITER_FSM_STATES . INGR_CURRENT_STATE_CMD_WRITE
 */
#define  VTSS_F_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_CURRENT_STATE_CMD_WRITE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_CURRENT_STATE_CMD_WRITE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_PTP_PROC_INGR_REWRITER_FSM_STATES_INGR_CURRENT_STATE_CMD_WRITE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Software pop fifo
 *
 * \details
 * Software pop fifo
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_SW_POP_FIFO
 */
#define VTSS_PTP_PROC_INGR_SW_POP_FIFO       VTSS_IOREG(VTSS_TO_PTP_PROC,0x90be)

/**
 * \brief
 * When asserted high, changes to PROTOCOL_MODE take
 *     immediate efect.  When set low, the mode change is a controlled
 *     process that first forces bypass mode, then takes effect, then
 *     releases bypass mode
 *
 * \details
 * 0=Follow controlled mode changes
 * 1=Mode changes take immediate effect
 *
 * Field: ::VTSS_PTP_PROC_INGR_SW_POP_FIFO . INGR_SAFE_MODCHG_DIS
 */
#define  VTSS_F_PTP_PROC_INGR_SW_POP_FIFO_INGR_SAFE_MODCHG_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PTP_PROC_INGR_SW_POP_FIFO_INGR_SAFE_MODCHG_DIS  VTSS_BIT(13)
#define  VTSS_X_PTP_PROC_INGR_SW_POP_FIFO_INGR_SAFE_MODCHG_DIS(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * When asserted high, completely resets majority of datapath after
 * AUTO_CLR_CLKS idle columns.  Datapath is held in reset until non-idle
 * column arrives.
 *
 * \details
 * 0=Do not reset datapath during idle
 * 1=Do reset datapath during idle
 *
 * Field: ::VTSS_PTP_PROC_INGR_SW_POP_FIFO . INGR_AUTO_RST_EN
 */
#define  VTSS_F_PTP_PROC_INGR_SW_POP_FIFO_INGR_AUTO_RST_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PTP_PROC_INGR_SW_POP_FIFO_INGR_AUTO_RST_EN  VTSS_BIT(12)
#define  VTSS_X_PTP_PROC_INGR_SW_POP_FIFO_INGR_AUTO_RST_EN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Indicates 1588 bypass in ON.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SW_POP_FIFO . INGR_BYPASS_ON
 */
#define  VTSS_F_PTP_PROC_INGR_SW_POP_FIFO_INGR_BYPASS_ON(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PTP_PROC_INGR_SW_POP_FIFO_INGR_BYPASS_ON  VTSS_BIT(11)
#define  VTSS_X_PTP_PROC_INGR_SW_POP_FIFO_INGR_BYPASS_ON(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Indicates 1588 has encountered idles at the input and in the process of
 * asserting bypass. Whether bypass switch actually turned ON will be
 * indicated by BYP_1588_ON
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SW_POP_FIFO . INGR_BYPASS_IDLE
 */
#define  VTSS_F_PTP_PROC_INGR_SW_POP_FIFO_INGR_BYPASS_IDLE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PTP_PROC_INGR_SW_POP_FIFO_INGR_BYPASS_IDLE  VTSS_BIT(10)
#define  VTSS_X_PTP_PROC_INGR_SW_POP_FIFO_INGR_BYPASS_IDLE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Indicates if any fifo levels are non zero in steady state.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SW_POP_FIFO . INGR_FIFO_LVL_OFF
 */
#define  VTSS_F_PTP_PROC_INGR_SW_POP_FIFO_INGR_FIFO_LVL_OFF(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PTP_PROC_INGR_SW_POP_FIFO_INGR_FIFO_LVL_OFF  VTSS_BIT(9)
#define  VTSS_X_PTP_PROC_INGR_SW_POP_FIFO_INGR_FIFO_LVL_OFF(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Indicates auto clear operation was completed.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SW_POP_FIFO . INGR_AUTO_CLR_DONE
 */
#define  VTSS_F_PTP_PROC_INGR_SW_POP_FIFO_INGR_AUTO_CLR_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PTP_PROC_INGR_SW_POP_FIFO_INGR_AUTO_CLR_DONE  VTSS_BIT(8)
#define  VTSS_X_PTP_PROC_INGR_SW_POP_FIFO_INGR_AUTO_CLR_DONE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Only valid when AUTO_CLR_EN is high. Will drain out of sync fifos after
 * 'n' number of idle clocks were observed at 1588. Only valid with numbers
 * more than 26.          10G speed : needs 'n+1' clock cycles
 *     1G speed  : needs 'n+1'*8 clock cycles          100M speed  :
 * needs 'n+1'*80 clock cycles          10M speed  : needs 'n+1'*800
 * clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SW_POP_FIFO . INGR_AUTO_CLR_CLKS
 */
#define  VTSS_F_PTP_PROC_INGR_SW_POP_FIFO_INGR_AUTO_CLR_CLKS(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_PTP_PROC_INGR_SW_POP_FIFO_INGR_AUTO_CLR_CLKS     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_PTP_PROC_INGR_SW_POP_FIFO_INGR_AUTO_CLR_CLKS(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/**
 * \brief
 * Enable auto clear of fifos if they do out of sync.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SW_POP_FIFO . INGR_AUTO_CLR_EN
 */
#define  VTSS_F_PTP_PROC_INGR_SW_POP_FIFO_INGR_AUTO_CLR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PTP_PROC_INGR_SW_POP_FIFO_INGR_AUTO_CLR_EN  VTSS_BIT(1)
#define  VTSS_X_PTP_PROC_INGR_SW_POP_FIFO_INGR_AUTO_CLR_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Reset all the fifos. This bit will be cleared after the reset operation
 * is completed. This should only be used if an error pushes the fifo to
 * out of sync.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_SW_POP_FIFO . INGR_SW_POP_FIFO
 */
#define  VTSS_F_PTP_PROC_INGR_SW_POP_FIFO_INGR_SW_POP_FIFO(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_INGR_SW_POP_FIFO_INGR_SW_POP_FIFO  VTSS_BIT(0)
#define  VTSS_X_PTP_PROC_INGR_SW_POP_FIFO_INGR_SW_POP_FIFO(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief lsb (31:0] of ANA_CMD_OUT_S from Rewriter
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_ANA_CMD_FIFO_DATA_OUT1
 */
#define VTSS_PTP_PROC_INGR_ANA_CMD_FIFO_DATA_OUT1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90bf)

/**
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_ANA_CMD_FIFO_DATA_OUT1 . INGR_ANA_CMD_FIFO_DATA_OUT1
 */
#define  VTSS_F_PTP_PROC_INGR_ANA_CMD_FIFO_DATA_OUT1_INGR_ANA_CMD_FIFO_DATA_OUT1(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_ANA_CMD_FIFO_DATA_OUT1_INGR_ANA_CMD_FIFO_DATA_OUT1     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_ANA_CMD_FIFO_DATA_OUT1_INGR_ANA_CMD_FIFO_DATA_OUT1(x)  (x)


/**
 * \brief msb [42:32] of ANA_CMD_OUT_S from Rewriter
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_ANA_CMD_FIFO_DATA_OUT2
 */
#define VTSS_PTP_PROC_INGR_ANA_CMD_FIFO_DATA_OUT2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90c0)

/**
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_ANA_CMD_FIFO_DATA_OUT2 . INGR_ANA_CMD_FIFO_DATA_OUT2
 */
#define  VTSS_F_PTP_PROC_INGR_ANA_CMD_FIFO_DATA_OUT2_INGR_ANA_CMD_FIFO_DATA_OUT2(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_PTP_PROC_INGR_ANA_CMD_FIFO_DATA_OUT2_INGR_ANA_CMD_FIFO_DATA_OUT2     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_PTP_PROC_INGR_ANA_CMD_FIFO_DATA_OUT2_INGR_ANA_CMD_FIFO_DATA_OUT2(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief lsb (31:0] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * \details
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_TIMESTAMP_VALUE_FIFO_INPUT1
 */
#define VTSS_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90c1)

/**
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT1 . INGR_TIMESTAMP_VALUE_FIFO_INPUT1
 */
#define  VTSS_F_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT1_INGR_TIMESTAMP_VALUE_FIFO_INPUT1(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT1_INGR_TIMESTAMP_VALUE_FIFO_INPUT1     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT1_INGR_TIMESTAMP_VALUE_FIFO_INPUT1(x)  (x)


/**
 * \brief lsb (63:32] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * \details
 * lsb (63:32] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_TIMESTAMP_VALUE_FIFO_INPUT2
 */
#define VTSS_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90c2)

/**
 * \brief
 * lsb (63:32] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT2 . INGR_TIMESTAMP_VALUE_FIFO_INPUT2
 */
#define  VTSS_F_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT2_INGR_TIMESTAMP_VALUE_FIFO_INPUT2(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT2_INGR_TIMESTAMP_VALUE_FIFO_INPUT2     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT2_INGR_TIMESTAMP_VALUE_FIFO_INPUT2(x)  (x)


/**
 * \brief lsb (79:63] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * \details
 * lsb (79:63] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_TIMESTAMP_VALUE_FIFO_INPUT3
 */
#define VTSS_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT3  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90c3)

/**
 * \brief
 * lsb (79:63] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT3 . INGR_TIMESTAMP_VALUE_FIFO_INPUT3
 */
#define  VTSS_F_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT3_INGR_TIMESTAMP_VALUE_FIFO_INPUT3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT3_INGR_TIMESTAMP_VALUE_FIFO_INPUT3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_PROC_INGR_TIMESTAMP_VALUE_FIFO_INPUT3_INGR_TIMESTAMP_VALUE_FIFO_INPUT3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief correction field valid of new_cf_valid from tsp to rewriter.
 *
 * \details
 * correction field valid of new_cf_valid from tsp to rewriter.
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_CORRECTION_FIELD_VLD_FIFO_INPUT
 */
#define VTSS_PTP_PROC_INGR_CORRECTION_FIELD_VLD_FIFO_INPUT  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90c4)

/**
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_CORRECTION_FIELD_VLD_FIFO_INPUT . INGR_CORRECTION_FIELD_VLD_FIFO_INPUT
 */
#define  VTSS_F_PTP_PROC_INGR_CORRECTION_FIELD_VLD_FIFO_INPUT_INGR_CORRECTION_FIELD_VLD_FIFO_INPUT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_INGR_CORRECTION_FIELD_VLD_FIFO_INPUT_INGR_CORRECTION_FIELD_VLD_FIFO_INPUT  VTSS_BIT(0)
#define  VTSS_X_PTP_PROC_INGR_CORRECTION_FIELD_VLD_FIFO_INPUT_INGR_CORRECTION_FIELD_VLD_FIFO_INPUT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief correction field value lsb [31:0]  of new_cf[63:0] from tsp to rewriter
 *
 * \details
 * correction field value lsb [31:0]  of new_cf[63:0] from tsp to rewriter
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1
 */
#define VTSS_PTP_PROC_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90c5)

/**
 * \brief
 * correction field value lsb [31:0]  of new_cf[63:0] from tsp to rewriter
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1 . INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1
 */
#define  VTSS_F_PTP_PROC_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1(x)  (x)


/**
 * \brief correction field value lsb [63:32]  of new_cf[63:0] from tsp to rewriter
 *
 * \details
 * correction field value lsb [63:32]  of new_cf[63:0] from tsp to rewriter
 *
 * Register: \a PTP_PROC:INGR_IP_1588_DEBUG_REGISTERS:INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2
 */
#define VTSS_PTP_PROC_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90c6)

/**
 * \brief
 * correction field value lsb [63:32]  of new_cf[63:0] from tsp to rewriter
 *
 * \details
 * Field: ::VTSS_PTP_PROC_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2 . INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2
 */
#define  VTSS_F_PTP_PROC_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2(x)  (x)
#define  VTSS_M_PTP_PROC_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2     0xffffffff
#define  VTSS_X_PTP_PROC_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2_INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2(x)  (x)

/**
 * Register Group: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS
 *
 * Provides the ability to read the IP1588 internal registers
 */


/**
 * \brief Part1 of command data generated by analyzer
 *
 * \details
 * This will provide the ability to check the command generated by analyzer
 * to the rewriter
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_ANA_CMD_FIFO_DATA1
 */
#define VTSS_PTP_PROC_EGR_ANA_CMD_FIFO_DATA1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90c7)

/**
 * \brief
 * This will provide the ability to check the command generated by analyzer
 * to the rewriter
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_ANA_CMD_FIFO_DATA1 . EGR_ANA_CMD_FIFO_DATA1
 */
#define  VTSS_F_PTP_PROC_EGR_ANA_CMD_FIFO_DATA1_EGR_ANA_CMD_FIFO_DATA1(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_ANA_CMD_FIFO_DATA1_EGR_ANA_CMD_FIFO_DATA1     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_ANA_CMD_FIFO_DATA1_EGR_ANA_CMD_FIFO_DATA1(x)  (x)


/**
 * \brief Part2 of command data generated by analyzer
 *
 * \details
 * This will provide the ability to check the command generated by analyzer
 * to the rewriter
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_ANA_CMD_FIFO_DATA2
 */
#define VTSS_PTP_PROC_EGR_ANA_CMD_FIFO_DATA2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90c8)

/**
 * \brief
 * This will provide the ability to check the command generated by analyzer
 * to the rewriter
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_ANA_CMD_FIFO_DATA2 . EGR_ANA_CMD_FIFO_DATA2
 */
#define  VTSS_F_PTP_PROC_EGR_ANA_CMD_FIFO_DATA2_EGR_ANA_CMD_FIFO_DATA2(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_PTP_PROC_EGR_ANA_CMD_FIFO_DATA2_EGR_ANA_CMD_FIFO_DATA2     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_PTP_PROC_EGR_ANA_CMD_FIFO_DATA2_EGR_ANA_CMD_FIFO_DATA2(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief Status signals of Analyzer
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_ANALYZER_STATUS
 */
#define VTSS_PTP_PROC_EGR_ANALYZER_STATUS    VTSS_IOREG(VTSS_TO_PTP_PROC,0x90c9)

/**
 * \brief
 * The value indicates the flow number when strict flow is enabled
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_ANALYZER_STATUS . EGR_FLOW_NUMBER
 */
#define  VTSS_F_PTP_PROC_EGR_ANALYZER_STATUS_EGR_FLOW_NUMBER(x)  VTSS_ENCODE_BITFIELD(x,6,4)
#define  VTSS_M_PTP_PROC_EGR_ANALYZER_STATUS_EGR_FLOW_NUMBER     VTSS_ENCODE_BITMASK(6,4)
#define  VTSS_X_PTP_PROC_EGR_ANALYZER_STATUS_EGR_FLOW_NUMBER(x)  VTSS_EXTRACT_BITFIELD(x,6,4)

/**
 * \brief
 * The value indicates the analyzer command generated by the analyzer.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_ANALYZER_STATUS . EGR_ANALYZER_CMD
 */
#define  VTSS_F_PTP_PROC_EGR_ANALYZER_STATUS_EGR_ANALYZER_CMD(x)  VTSS_ENCODE_BITFIELD(x,2,4)
#define  VTSS_M_PTP_PROC_EGR_ANALYZER_STATUS_EGR_ANALYZER_CMD     VTSS_ENCODE_BITMASK(2,4)
#define  VTSS_X_PTP_PROC_EGR_ANALYZER_STATUS_EGR_ANALYZER_CMD(x)  VTSS_EXTRACT_BITFIELD(x,2,4)

/**
 * \brief
 * Indicates the matched engine number.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_ANALYZER_STATUS . EGR_ANALYZER_ENGINE
 */
#define  VTSS_F_PTP_PROC_EGR_ANALYZER_STATUS_EGR_ANALYZER_ENGINE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_PTP_PROC_EGR_ANALYZER_STATUS_EGR_ANALYZER_ENGINE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_PTP_PROC_EGR_ANALYZER_STATUS_EGR_ANALYZER_ENGINE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Predictor variable delay1
 *
 * \details
 * Predictor variable stall latency 1.
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_PREDICTOR_VAR_DELAY1
 */
#define VTSS_PTP_PROC_EGR_PREDICTOR_VAR_DELAY1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90ca)

/**
 * \brief
 * Predictor variable stall latency 1.bit [25:8] is ns fieldbit [7:0] is
 * sub-ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_PREDICTOR_VAR_DELAY1 . EGR_PREDICTOR_VAR_DELAY1
 */
#define  VTSS_F_PTP_PROC_EGR_PREDICTOR_VAR_DELAY1_EGR_PREDICTOR_VAR_DELAY1(x)  VTSS_ENCODE_BITFIELD(x,0,26)
#define  VTSS_M_PTP_PROC_EGR_PREDICTOR_VAR_DELAY1_EGR_PREDICTOR_VAR_DELAY1     VTSS_ENCODE_BITMASK(0,26)
#define  VTSS_X_PTP_PROC_EGR_PREDICTOR_VAR_DELAY1_EGR_PREDICTOR_VAR_DELAY1(x)  VTSS_EXTRACT_BITFIELD(x,0,26)


/**
 * \brief Predictor variable delay 2
 *
 * \details
 * Predictor variable stall latency 2
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_PREDICTOR_VAR_DELAY2
 */
#define VTSS_PTP_PROC_EGR_PREDICTOR_VAR_DELAY2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90cb)

/**
 * \brief
 * Predictor variable stall latency 2bit [25:8] is ns fieldbit [7:0] is
 * sub-ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_PREDICTOR_VAR_DELAY2 . EGR_PREDICTOR_VAR_DELAY2
 */
#define  VTSS_F_PTP_PROC_EGR_PREDICTOR_VAR_DELAY2_EGR_PREDICTOR_VAR_DELAY2(x)  VTSS_ENCODE_BITFIELD(x,0,26)
#define  VTSS_M_PTP_PROC_EGR_PREDICTOR_VAR_DELAY2_EGR_PREDICTOR_VAR_DELAY2     VTSS_ENCODE_BITMASK(0,26)
#define  VTSS_X_PTP_PROC_EGR_PREDICTOR_VAR_DELAY2_EGR_PREDICTOR_VAR_DELAY2(x)  VTSS_EXTRACT_BITFIELD(x,0,26)


/**
 * \brief Predictor variable delay 3
 *
 * \details
 * Predictor variable stall latency 3
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_PREDICTOR_VAR_DELAY3
 */
#define VTSS_PTP_PROC_EGR_PREDICTOR_VAR_DELAY3  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90cc)

/**
 * \brief
 * Predictor variable stall latency 3bit [25:8] is ns fieldbit [7:0] is
 * sub-ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_PREDICTOR_VAR_DELAY3 . EGR_PREDICTOR_VAR_DELAY3
 */
#define  VTSS_F_PTP_PROC_EGR_PREDICTOR_VAR_DELAY3_EGR_PREDICTOR_VAR_DELAY3(x)  VTSS_ENCODE_BITFIELD(x,0,26)
#define  VTSS_M_PTP_PROC_EGR_PREDICTOR_VAR_DELAY3_EGR_PREDICTOR_VAR_DELAY3     VTSS_ENCODE_BITMASK(0,26)
#define  VTSS_X_PTP_PROC_EGR_PREDICTOR_VAR_DELAY3_EGR_PREDICTOR_VAR_DELAY3(x)  VTSS_EXTRACT_BITFIELD(x,0,26)


/**
 * \brief Gives rewriter modifications on packet
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_REWRITER_OPMODE
 */
#define VTSS_PTP_PROC_EGR_REWRITER_OPMODE    VTSS_IOREG(VTSS_TO_PTP_PROC,0x90cd)

/**
 * \brief
 * Gives rewriter modifications on packet based on opmode configuration.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_REWRITER_OPMODE . EGR_REWRITER_OPMODE
 */
#define  VTSS_F_PTP_PROC_EGR_REWRITER_OPMODE_EGR_REWRITER_OPMODE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_PROC_EGR_REWRITER_OPMODE_EGR_REWRITER_OPMODE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_PROC_EGR_REWRITER_OPMODE_EGR_REWRITER_OPMODE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Indicates valid cf if asserted.
 *
 * \details
 *
 * Indicates valid cf if asserted.

 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_CORRECTION_FIELD_VLD
 */
#define VTSS_PTP_PROC_EGR_CORRECTION_FIELD_VLD  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90ce)

/**
 * \brief
 * Indicates valid cf if asserted.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_CORRECTION_FIELD_VLD . EGR_CORRECTION_FIELD_VALID
 */
#define  VTSS_F_PTP_PROC_EGR_CORRECTION_FIELD_VLD_EGR_CORRECTION_FIELD_VALID(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_EGR_CORRECTION_FIELD_VLD_EGR_CORRECTION_FIELD_VALID  VTSS_BIT(0)
#define  VTSS_X_PTP_PROC_EGR_CORRECTION_FIELD_VLD_EGR_CORRECTION_FIELD_VALID(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief correction field value lsb [31:0]  of new_cf[63:0] from rewriter fifo.
 *
 * \details
 * correction field value lsb [31:0]  of new_cf[63:0] from rewriter fifo.
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_CORRECTION_FIELD_VALUE1
 */
#define VTSS_PTP_PROC_EGR_CORRECTION_FIELD_VALUE1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90cf)

/**
 * \brief
 * correction field value lsb [31:0]  of new_cf[63:0].
 *
 * \details
 * Binary
 *
 * Field: ::VTSS_PTP_PROC_EGR_CORRECTION_FIELD_VALUE1 . EGR_CORRECTION_FIELD_VALUE_1
 */
#define  VTSS_F_PTP_PROC_EGR_CORRECTION_FIELD_VALUE1_EGR_CORRECTION_FIELD_VALUE_1(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_CORRECTION_FIELD_VALUE1_EGR_CORRECTION_FIELD_VALUE_1     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_CORRECTION_FIELD_VALUE1_EGR_CORRECTION_FIELD_VALUE_1(x)  (x)


/**
 * \brief correction field value lsb [63:32]  of new_cf[63:0] from rewriter fifo
 *
 * \details
 * correction field value lsb [63:32]  of new_cf[63:0] from rewriter fifo
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_CORRECTION_FIELD_VALUE2
 */
#define VTSS_PTP_PROC_EGR_CORRECTION_FIELD_VALUE2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90d0)

/**
 * \brief
 * correction field value lsb [63:32]  of new_cf[63:0]
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_CORRECTION_FIELD_VALUE2 . EGR_CORRECTION_FIELD_VALUE_2
 */
#define  VTSS_F_PTP_PROC_EGR_CORRECTION_FIELD_VALUE2_EGR_CORRECTION_FIELD_VALUE_2(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_CORRECTION_FIELD_VALUE2_EGR_CORRECTION_FIELD_VALUE_2     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_CORRECTION_FIELD_VALUE2_EGR_CORRECTION_FIELD_VALUE_2(x)  (x)


/**
 * \brief lsb (31:0] of new_field_o[79:0] from tsp.v
 *
 * \details
 * lsb (31:0] of new_field_o[79:0] from tsp.v
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_TIMESTAMP_VALUE1
 */
#define VTSS_PTP_PROC_EGR_TIMESTAMP_VALUE1   VTSS_IOREG(VTSS_TO_PTP_PROC,0x90d1)

/**
 * \brief
 * lsb (31:0] of new_field_o[79:0] from rewriter fifo
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TIMESTAMP_VALUE1 . EGR_TIMESTAMP_VALUE_1
 */
#define  VTSS_F_PTP_PROC_EGR_TIMESTAMP_VALUE1_EGR_TIMESTAMP_VALUE_1(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_TIMESTAMP_VALUE1_EGR_TIMESTAMP_VALUE_1     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_TIMESTAMP_VALUE1_EGR_TIMESTAMP_VALUE_1(x)  (x)


/**
 * \brief lsb (63:32] of new_field_o[79:0] from rewriter fifo
 *
 * \details
 * lsb (63:32] of new_field_o[79:0] from rewriter fifo
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_TIMESTAMP_VALUE2
 */
#define VTSS_PTP_PROC_EGR_TIMESTAMP_VALUE2   VTSS_IOREG(VTSS_TO_PTP_PROC,0x90d2)

/**
 * \brief
 * lsb (63:32] of new_field_o[79:0] from rewriter fifo
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TIMESTAMP_VALUE2 . EGR_TIMESTAMP_VALUE_2
 */
#define  VTSS_F_PTP_PROC_EGR_TIMESTAMP_VALUE2_EGR_TIMESTAMP_VALUE_2(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_TIMESTAMP_VALUE2_EGR_TIMESTAMP_VALUE_2     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_TIMESTAMP_VALUE2_EGR_TIMESTAMP_VALUE_2(x)  (x)


/**
 * \brief Msb (79:64] of new_field_o[79:0] from rewriter fifo
 *
 * \details
 * Msb (79:64] of new_field_o[79:0] from rewriter fifo
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_TIMESTAMP_VALUE3
 */
#define VTSS_PTP_PROC_EGR_TIMESTAMP_VALUE3   VTSS_IOREG(VTSS_TO_PTP_PROC,0x90d3)

/**
 * \brief
 * Msb (79:64] of new_field_o[79:0] from rewriter fifo
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TIMESTAMP_VALUE3 . EGR_TIMESTAMP_VALUE_3
 */
#define  VTSS_F_PTP_PROC_EGR_TIMESTAMP_VALUE3_EGR_TIMESTAMP_VALUE_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_PROC_EGR_TIMESTAMP_VALUE3_EGR_TIMESTAMP_VALUE_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_PROC_EGR_TIMESTAMP_VALUE3_EGR_TIMESTAMP_VALUE_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Configure LTC read type
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_LTC_READ
 */
#define VTSS_PTP_PROC_EGR_LTC_READ           VTSS_IOREG(VTSS_TO_PTP_PROC,0x90d4)

/**
 * \brief
 * When this bit is 1'b1, LTC value is read into LTC_SEC_H, LTC_SEC_L &
 * LTC_NS registers on every SOF.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_LTC_READ . EGR_LTC_READ_ON_SOF
 */
#define  VTSS_F_PTP_PROC_EGR_LTC_READ_EGR_LTC_READ_ON_SOF(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PTP_PROC_EGR_LTC_READ_EGR_LTC_READ_ON_SOF  VTSS_BIT(1)
#define  VTSS_X_PTP_PROC_EGR_LTC_READ_EGR_LTC_READ_ON_SOF(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When this bit is set to 1'b1, current LTC value is read into LTC_SEC_H,
 * LTC_SEC_L & LTC_NS registers.This bit is cleared by hardware after the
 * operation is completed.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_LTC_READ . EGR_LTC_ONE_SHOT_READ
 */
#define  VTSS_F_PTP_PROC_EGR_LTC_READ_EGR_LTC_ONE_SHOT_READ(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_EGR_LTC_READ_EGR_LTC_ONE_SHOT_READ  VTSS_BIT(0)
#define  VTSS_X_PTP_PROC_EGR_LTC_READ_EGR_LTC_ONE_SHOT_READ(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief LTC seconds (high)
 *
 * \details
 * LTC seconds (high)
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_LTC_SEC_H
 */
#define VTSS_PTP_PROC_EGR_LTC_SEC_H          VTSS_IOREG(VTSS_TO_PTP_PROC,0x90d5)

/**
 * \brief
 * LTC seconds (high) in debug mode
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_LTC_SEC_H . EGR_LTC_SEC_H
 */
#define  VTSS_F_PTP_PROC_EGR_LTC_SEC_H_EGR_LTC_SEC_H(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_PROC_EGR_LTC_SEC_H_EGR_LTC_SEC_H     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_PROC_EGR_LTC_SEC_H_EGR_LTC_SEC_H(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LTC seconds (low)
 *
 * \details
 * LTC seconds (low)
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_LTC_SEC_L
 */
#define VTSS_PTP_PROC_EGR_LTC_SEC_L          VTSS_IOREG(VTSS_TO_PTP_PROC,0x90d6)

/**
 * \brief
 * LTC seconds (low) in debug mode
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_LTC_SEC_L . EGR_LTC_SEC_L
 */
#define  VTSS_F_PTP_PROC_EGR_LTC_SEC_L_EGR_LTC_SEC_L(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_LTC_SEC_L_EGR_LTC_SEC_L     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_LTC_SEC_L_EGR_LTC_SEC_L(x)  (x)


/**
 * \brief LTC nanoseconds
 *
 * \details
 * LTC nanoseconds
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_LTC_NS
 */
#define VTSS_PTP_PROC_EGR_LTC_NS             VTSS_IOREG(VTSS_TO_PTP_PROC,0x90d7)

/**
 * \brief
 * LTC nanoseconds in debug mode
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_LTC_NS . EGR_LTC_NS
 */
#define  VTSS_F_PTP_PROC_EGR_LTC_NS_EGR_LTC_NS(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_LTC_NS_EGR_LTC_NS     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_LTC_NS_EGR_LTC_NS(x)  (x)


/**
 * \brief LTC sub-nanoseconds
 *
 * \details
 * LTC sub-nanoseconds
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_LTC_SNS
 */
#define VTSS_PTP_PROC_EGR_LTC_SNS            VTSS_IOREG(VTSS_TO_PTP_PROC,0x90d8)

/**
 * \brief
 * LTC sub-nanosecond in debug mode
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_LTC_SNS . EGR_LTC_SNS
 */
#define  VTSS_F_PTP_PROC_EGR_LTC_SNS_EGR_LTC_SNS(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PROC_EGR_LTC_SNS_EGR_LTC_SNS     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PROC_EGR_LTC_SNS_EGR_LTC_SNS(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Extracted correction field LSB
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_EXTRACTED_CF1
 */
#define VTSS_PTP_PROC_EGR_EXTRACTED_CF1      VTSS_IOREG(VTSS_TO_PTP_PROC,0x90d9)

/**
 * \brief
 * Extracted correction field value LSB [31:0]
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_EXTRACTED_CF1 . EGR_EXTRACTED_CF1
 */
#define  VTSS_F_PTP_PROC_EGR_EXTRACTED_CF1_EGR_EXTRACTED_CF1(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_EXTRACTED_CF1_EGR_EXTRACTED_CF1     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_EXTRACTED_CF1_EGR_EXTRACTED_CF1(x)  (x)


/**
 * \brief Extracted correction field MSB
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_EXTRACTED_CF2
 */
#define VTSS_PTP_PROC_EGR_EXTRACTED_CF2      VTSS_IOREG(VTSS_TO_PTP_PROC,0x90da)

/**
 * \brief
 * Extracted correction field value MSB[63:32]
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_EXTRACTED_CF2 . EGR_EXTRACTED_CF2
 */
#define  VTSS_F_PTP_PROC_EGR_EXTRACTED_CF2_EGR_EXTRACTED_CF2(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_EXTRACTED_CF2_EGR_EXTRACTED_CF2     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_EXTRACTED_CF2_EGR_EXTRACTED_CF2(x)  (x)


/**
 * \brief Stored Timestamp
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_STORED_TIMESTAMP
 */
#define VTSS_PTP_PROC_EGR_STORED_TIMESTAMP   VTSS_IOREG(VTSS_TO_PTP_PROC,0x90db)

/**
 * \brief
 * Stored timestamp value from ingress The associated sub-nan info is
 * included in the CF and can not be decided and provided for debugging
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_STORED_TIMESTAMP . EGR_STORED_TIMESTAMP
 */
#define  VTSS_F_PTP_PROC_EGR_STORED_TIMESTAMP_EGR_STORED_TIMESTAMP(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_STORED_TIMESTAMP_EGR_STORED_TIMESTAMP     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_STORED_TIMESTAMP_EGR_STORED_TIMESTAMP(x)  (x)


/**
 * \brief Active time stamp sub-nans [7:0]
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_ACTIVE_TIMESTAMP0
 */
#define VTSS_PTP_PROC_EGR_ACTIVE_TIMESTAMP0  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90dc)

/**
 * \brief
 * Active time stamp [7:0] of sub-ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_ACTIVE_TIMESTAMP0 . EGR_ACTIVE_TIMESTAMP0
 */
#define  VTSS_F_PTP_PROC_EGR_ACTIVE_TIMESTAMP0_EGR_ACTIVE_TIMESTAMP0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PROC_EGR_ACTIVE_TIMESTAMP0_EGR_ACTIVE_TIMESTAMP0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PROC_EGR_ACTIVE_TIMESTAMP0_EGR_ACTIVE_TIMESTAMP0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Active time stamp ns [31:0]
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_ACTIVE_TIMESTAMP1
 */
#define VTSS_PTP_PROC_EGR_ACTIVE_TIMESTAMP1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90dd)

/**
 * \brief
 * Active time stamp [31:0] of ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_ACTIVE_TIMESTAMP1 . EGR_ACTIVE_TIMESTAMP1
 */
#define  VTSS_F_PTP_PROC_EGR_ACTIVE_TIMESTAMP1_EGR_ACTIVE_TIMESTAMP1(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_ACTIVE_TIMESTAMP1_EGR_ACTIVE_TIMESTAMP1     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_ACTIVE_TIMESTAMP1_EGR_ACTIVE_TIMESTAMP1(x)  (x)


/**
 * \brief Active time stamp ns [46:32]
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_ACTIVE_TIMESTAMP2
 */
#define VTSS_PTP_PROC_EGR_ACTIVE_TIMESTAMP2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90de)

/**
 * \brief
 * Active time stamp [46:32]  of ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_ACTIVE_TIMESTAMP2 . EGR_ACTIVE_TIMESTAMP2
 */
#define  VTSS_F_PTP_PROC_EGR_ACTIVE_TIMESTAMP2_EGR_ACTIVE_TIMESTAMP2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_PROC_EGR_ACTIVE_TIMESTAMP2_EGR_ACTIVE_TIMESTAMP2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_PROC_EGR_ACTIVE_TIMESTAMP2_EGR_ACTIVE_TIMESTAMP2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Predictor delay used and the number of PTP frames matched
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_PREDICTOR_VALUES
 */
#define VTSS_PTP_PROC_EGR_PREDICTOR_VALUES   VTSS_IOREG(VTSS_TO_PTP_PROC,0x90df)

/**
 * \brief
 * Indicates a artificial push into timestamp processor. Corresponding
 * offset for this push will be random and calib_error will be asserted.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_PREDICTOR_VALUES . EGR_TSP_PUSH_FLAG
 */
#define  VTSS_F_PTP_PROC_EGR_PREDICTOR_VALUES_EGR_TSP_PUSH_FLAG(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PTP_PROC_EGR_PREDICTOR_VALUES_EGR_TSP_PUSH_FLAG  VTSS_BIT(28)
#define  VTSS_X_PTP_PROC_EGR_PREDICTOR_VALUES_EGR_TSP_PUSH_FLAG(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * The number of matched PTP frames
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_PREDICTOR_VALUES . EGR_PTP_FRM_CNT
 */
#define  VTSS_F_PTP_PROC_EGR_PREDICTOR_VALUES_EGR_PTP_FRM_CNT(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_PTP_PROC_EGR_PREDICTOR_VALUES_EGR_PTP_FRM_CNT     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_PTP_PROC_EGR_PREDICTOR_VALUES_EGR_PTP_FRM_CNT(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/**
 * \brief
 * The value of the predictor variable delay usedbit [25:8] is ns fieldbit
 * [7:0] is sub-ns field
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_PREDICTOR_VALUES . EGR_VAR_DELAY_USED
 */
#define  VTSS_F_PTP_PROC_EGR_PREDICTOR_VALUES_EGR_VAR_DELAY_USED(x)  VTSS_ENCODE_BITFIELD(x,0,26)
#define  VTSS_M_PTP_PROC_EGR_PREDICTOR_VALUES_EGR_VAR_DELAY_USED     VTSS_ENCODE_BITMASK(0,26)
#define  VTSS_X_PTP_PROC_EGR_PREDICTOR_VALUES_EGR_VAR_DELAY_USED(x)  VTSS_EXTRACT_BITFIELD(x,0,26)


/**
 * \brief Current and Next States of FSMs in rw_cmd_write[0:3], rw_cmd_cfwrite[7:4] and rw_cmd_clear[11:8]
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_REWRITER_FSM_STATES
 */
#define VTSS_PTP_PROC_EGR_REWRITER_FSM_STATES  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90e0)

/**
 * \brief
 * Next State[1:0]  of module <rw_cmd_cfwrite.v>
 *
 * \details
 * binary
 *
 * Field: ::VTSS_PTP_PROC_EGR_REWRITER_FSM_STATES . EGR_NEXT_STATE_CMD_CLEAR
 */
#define  VTSS_F_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_NEXT_STATE_CMD_CLEAR(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_NEXT_STATE_CMD_CLEAR     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_NEXT_STATE_CMD_CLEAR(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/**
 * \brief
 * Current State[1:0]  of module <rw_cmd_clear.v>
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_REWRITER_FSM_STATES . EGR_CURRENT_STATE_CMD_CLEAR
 */
#define  VTSS_F_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_CURRENT_STATE_CMD_CLEAR(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_CURRENT_STATE_CMD_CLEAR     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_CURRENT_STATE_CMD_CLEAR(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Next State[1:0]  of module <rw_cmd_cfwrite.v>
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_REWRITER_FSM_STATES . EGR_NEXT_STATE_CMD_CFWRITE
 */
#define  VTSS_F_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_NEXT_STATE_CMD_CFWRITE(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_NEXT_STATE_CMD_CFWRITE     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_NEXT_STATE_CMD_CFWRITE(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * Current State[1:0]  of module <rw_cmd_cfwrite.v>
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_REWRITER_FSM_STATES . EGR_CURRENT_STATE_CMD_CFWRITE
 */
#define  VTSS_F_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_CURRENT_STATE_CMD_CFWRITE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_CURRENT_STATE_CMD_CFWRITE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_CURRENT_STATE_CMD_CFWRITE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Next State[1:0]  of module <rw_cmd_write.v>
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_REWRITER_FSM_STATES . EGR_NEXT_STATE_CMD_WRITE
 */
#define  VTSS_F_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_NEXT_STATE_CMD_WRITE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_NEXT_STATE_CMD_WRITE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_NEXT_STATE_CMD_WRITE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Current State[1:0]  of module <rw_cmd_write.v>
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_REWRITER_FSM_STATES . EGR_CURRENT_STATE_CMD_WRITE
 */
#define  VTSS_F_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_CURRENT_STATE_CMD_WRITE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_CURRENT_STATE_CMD_WRITE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_PTP_PROC_EGR_REWRITER_FSM_STATES_EGR_CURRENT_STATE_CMD_WRITE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Software pop fifo
 *
 * \details
 * Software pop fifo
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_SW_POP_FIFO
 */
#define VTSS_PTP_PROC_EGR_SW_POP_FIFO        VTSS_IOREG(VTSS_TO_PTP_PROC,0x90e1)

/**
 * \brief
 * When asserted high, changes to PROTOCOL_MODE take
 *     immediate efect.  When set low, the mode change is a controlled
 *     process that first forces bypass mode, then takes effect, then
 *     releases bypass mode
 *
 * \details
 * 0=Follow controlled mode changes
 * 1=Mode changes take immediate effect
 *
 * Field: ::VTSS_PTP_PROC_EGR_SW_POP_FIFO . EGR_SAFE_MODCHG_DIS
 */
#define  VTSS_F_PTP_PROC_EGR_SW_POP_FIFO_EGR_SAFE_MODCHG_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PTP_PROC_EGR_SW_POP_FIFO_EGR_SAFE_MODCHG_DIS  VTSS_BIT(13)
#define  VTSS_X_PTP_PROC_EGR_SW_POP_FIFO_EGR_SAFE_MODCHG_DIS(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * When asserted high, completely resets majority of datapath after
 * AUTO_CLR_CLKS idle columns.  Datapath is held in reset until non-idle
 * column arrives.
 *
 * \details
 * 0=Do not reset datapath during idle
 * 1=Do reset datapath during idle
 *
 * Field: ::VTSS_PTP_PROC_EGR_SW_POP_FIFO . EGR_AUTO_RST_EN
 */
#define  VTSS_F_PTP_PROC_EGR_SW_POP_FIFO_EGR_AUTO_RST_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PTP_PROC_EGR_SW_POP_FIFO_EGR_AUTO_RST_EN  VTSS_BIT(12)
#define  VTSS_X_PTP_PROC_EGR_SW_POP_FIFO_EGR_AUTO_RST_EN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Indicates 1588 bypass in ON.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SW_POP_FIFO . EGR_BYPASS_ON
 */
#define  VTSS_F_PTP_PROC_EGR_SW_POP_FIFO_EGR_BYPASS_ON(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PTP_PROC_EGR_SW_POP_FIFO_EGR_BYPASS_ON  VTSS_BIT(11)
#define  VTSS_X_PTP_PROC_EGR_SW_POP_FIFO_EGR_BYPASS_ON(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Indicates 1588 has encountered idles at the input and in the process of
 * asserting bypass. Whether bypass switch actually turned ON will be
 * indicated by BYP_1588_ON
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SW_POP_FIFO . EGR_BYPASS_IDLE
 */
#define  VTSS_F_PTP_PROC_EGR_SW_POP_FIFO_EGR_BYPASS_IDLE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PTP_PROC_EGR_SW_POP_FIFO_EGR_BYPASS_IDLE  VTSS_BIT(10)
#define  VTSS_X_PTP_PROC_EGR_SW_POP_FIFO_EGR_BYPASS_IDLE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Indicates if any fifo levels are non zero in steady state.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SW_POP_FIFO . EGR_FIFO_LVL_OFF
 */
#define  VTSS_F_PTP_PROC_EGR_SW_POP_FIFO_EGR_FIFO_LVL_OFF(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PTP_PROC_EGR_SW_POP_FIFO_EGR_FIFO_LVL_OFF  VTSS_BIT(9)
#define  VTSS_X_PTP_PROC_EGR_SW_POP_FIFO_EGR_FIFO_LVL_OFF(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Indicates auto clear operation was completed.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SW_POP_FIFO . EGR_AUTO_CLR_DONE
 */
#define  VTSS_F_PTP_PROC_EGR_SW_POP_FIFO_EGR_AUTO_CLR_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PTP_PROC_EGR_SW_POP_FIFO_EGR_AUTO_CLR_DONE  VTSS_BIT(8)
#define  VTSS_X_PTP_PROC_EGR_SW_POP_FIFO_EGR_AUTO_CLR_DONE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Only valid when AUTO_CLR_EN is high. Will drain out of sync fifos after
 * 'n' number of idle clocks were observed at 1588. Only valid with numbers
 * more than 26.          10G speed : needs 'n+1' clock cycles
 *     1G speed  : needs 'n+1'*8 clock cycles          100M speed  :
 * needs 'n+1'*80 clock cycles          10M speed  : needs 'n+1'*800
 * clock cycles
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SW_POP_FIFO . EGR_AUTO_CLR_CLKS
 */
#define  VTSS_F_PTP_PROC_EGR_SW_POP_FIFO_EGR_AUTO_CLR_CLKS(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_PTP_PROC_EGR_SW_POP_FIFO_EGR_AUTO_CLR_CLKS     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_PTP_PROC_EGR_SW_POP_FIFO_EGR_AUTO_CLR_CLKS(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/**
 * \brief
 * Enable auto clear of fifos if they do out of sync.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SW_POP_FIFO . EGR_AUTO_CLR_EN
 */
#define  VTSS_F_PTP_PROC_EGR_SW_POP_FIFO_EGR_AUTO_CLR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PTP_PROC_EGR_SW_POP_FIFO_EGR_AUTO_CLR_EN  VTSS_BIT(1)
#define  VTSS_X_PTP_PROC_EGR_SW_POP_FIFO_EGR_AUTO_CLR_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Reset all the fifos. This bit will be cleared after the reset operation
 * is completed. This should only be used if an error pushes the fifo to
 * out of sync.
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_SW_POP_FIFO . EGR_SW_POP_FIFO
 */
#define  VTSS_F_PTP_PROC_EGR_SW_POP_FIFO_EGR_SW_POP_FIFO(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_EGR_SW_POP_FIFO_EGR_SW_POP_FIFO  VTSS_BIT(0)
#define  VTSS_X_PTP_PROC_EGR_SW_POP_FIFO_EGR_SW_POP_FIFO(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief lsb (31:0] of ANA_CMD_OUT_S from Rewriter
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_ANA_CMD_FIFO_DATA_OUT1
 */
#define VTSS_PTP_PROC_EGR_ANA_CMD_FIFO_DATA_OUT1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90e2)

/**
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_ANA_CMD_FIFO_DATA_OUT1 . EGR_ANA_CMD_FIFO_DATA_OUT1
 */
#define  VTSS_F_PTP_PROC_EGR_ANA_CMD_FIFO_DATA_OUT1_EGR_ANA_CMD_FIFO_DATA_OUT1(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_ANA_CMD_FIFO_DATA_OUT1_EGR_ANA_CMD_FIFO_DATA_OUT1     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_ANA_CMD_FIFO_DATA_OUT1_EGR_ANA_CMD_FIFO_DATA_OUT1(x)  (x)


/**
 * \brief msb [42:32] of ANA_CMD_OUT_S from Rewriter
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_ANA_CMD_FIFO_DATA_OUT2
 */
#define VTSS_PTP_PROC_EGR_ANA_CMD_FIFO_DATA_OUT2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90e3)

/**
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_ANA_CMD_FIFO_DATA_OUT2 . EGR_ANA_CMD_FIFO_DATA_OUT2
 */
#define  VTSS_F_PTP_PROC_EGR_ANA_CMD_FIFO_DATA_OUT2_EGR_ANA_CMD_FIFO_DATA_OUT2(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_PTP_PROC_EGR_ANA_CMD_FIFO_DATA_OUT2_EGR_ANA_CMD_FIFO_DATA_OUT2     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_PTP_PROC_EGR_ANA_CMD_FIFO_DATA_OUT2_EGR_ANA_CMD_FIFO_DATA_OUT2(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief lsb (31:0] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * \details
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_TIMESTAMP_VALUE_FIFO_INPUT1
 */
#define VTSS_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90e4)

/**
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT1 . EGR_TIMESTAMP_VALUE_FIFO_INPUT1
 */
#define  VTSS_F_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT1_EGR_TIMESTAMP_VALUE_FIFO_INPUT1(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT1_EGR_TIMESTAMP_VALUE_FIFO_INPUT1     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT1_EGR_TIMESTAMP_VALUE_FIFO_INPUT1(x)  (x)


/**
 * \brief lsb (63:32] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * \details
 * lsb (63:32] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_TIMESTAMP_VALUE_FIFO_INPUT2
 */
#define VTSS_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90e5)

/**
 * \brief
 * lsb (63:32] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT2 . EGR_TIMESTAMP_VALUE_FIFO_INPUT2
 */
#define  VTSS_F_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT2_EGR_TIMESTAMP_VALUE_FIFO_INPUT2(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT2_EGR_TIMESTAMP_VALUE_FIFO_INPUT2     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT2_EGR_TIMESTAMP_VALUE_FIFO_INPUT2(x)  (x)


/**
 * \brief lsb (79:63] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * \details
 * lsb (79:63] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_TIMESTAMP_VALUE_FIFO_INPUT3
 */
#define VTSS_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT3  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90e6)

/**
 * \brief
 * lsb (79:63] of new_field_i[79:0] from tsp.v to Rewriter
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT3 . EGR_TIMESTAMP_VALUE_FIFO_INPUT3
 */
#define  VTSS_F_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT3_EGR_TIMESTAMP_VALUE_FIFO_INPUT3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT3_EGR_TIMESTAMP_VALUE_FIFO_INPUT3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_PROC_EGR_TIMESTAMP_VALUE_FIFO_INPUT3_EGR_TIMESTAMP_VALUE_FIFO_INPUT3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief correction field valid of new_cf_valid from tsp to rewriter.
 *
 * \details
 * correction field valid of new_cf_valid from tsp to rewriter.
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_CORRECTION_FIELD_VLD_FIFO_INPUT
 */
#define VTSS_PTP_PROC_EGR_CORRECTION_FIELD_VLD_FIFO_INPUT  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90e7)

/**
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_CORRECTION_FIELD_VLD_FIFO_INPUT . EGR_CORRECTION_FIELD_VLD_FIFO_INPUT
 */
#define  VTSS_F_PTP_PROC_EGR_CORRECTION_FIELD_VLD_FIFO_INPUT_EGR_CORRECTION_FIELD_VLD_FIFO_INPUT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PROC_EGR_CORRECTION_FIELD_VLD_FIFO_INPUT_EGR_CORRECTION_FIELD_VLD_FIFO_INPUT  VTSS_BIT(0)
#define  VTSS_X_PTP_PROC_EGR_CORRECTION_FIELD_VLD_FIFO_INPUT_EGR_CORRECTION_FIELD_VLD_FIFO_INPUT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief correction field value lsb [31:0]  of new_cf[63:0] from tsp to rewriter
 *
 * \details
 * correction field value lsb [31:0]  of new_cf[63:0] from tsp to rewriter
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1
 */
#define VTSS_PTP_PROC_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90e8)

/**
 * \brief
 * correction field value lsb [31:0]  of new_cf[63:0] from tsp to rewriter
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1 . EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1
 */
#define  VTSS_F_PTP_PROC_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1(x)  (x)


/**
 * \brief correction field value lsb [63:32]  of new_cf[63:0] from tsp to rewriter
 *
 * \details
 * correction field value lsb [63:32]  of new_cf[63:0] from tsp to rewriter
 *
 * Register: \a PTP_PROC:EGR_IP_1588_DEBUG_REGISTERS:EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2
 */
#define VTSS_PTP_PROC_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2  VTSS_IOREG(VTSS_TO_PTP_PROC,0x90e9)

/**
 * \brief
 * correction field value lsb [63:32]  of new_cf[63:0] from tsp to rewriter
 *
 * \details
 * Field: ::VTSS_PTP_PROC_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2 . EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2
 */
#define  VTSS_F_PTP_PROC_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2(x)  (x)
#define  VTSS_M_PTP_PROC_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2     0xffffffff
#define  VTSS_X_PTP_PROC_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2_EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2(x)  (x)


/**
 * \brief LTC sequence configuration
 *
 * \details
 * LTC sequence configuration
 *
 * Register: \a PTP_3:IP_1588_LTC:LTC_SEQ
 */
#define LAN80XX_PTP_PROC_IP_1588_LTC_LTC_SEQ       LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1, 0x9017)


/**
 * \brief
 * LTC sequence of increments (nanoseconds).
 *
 * \details
 * Field: LAN80XX_PTP_IP_1588_LTC_LTC_SEQUENCE . LTC_SEQUENCE_A
 */
#define  LAN80XX_F_PTP_IP_1588_LTC_LTC_SEQUENCE_LTC_SEQUENCE_A(x)  LAN80XX_ENCODE_BITFIELD(x,0,4)
#define  LAN80XX_M_PTP_IP_1588_LTC_LTC_SEQUENCE_LTC_SEQUENCE_A     LAN80XX_ENCODE_BITMASK(0,4)
#define  LAN80XX_X_PTP_IP_1588_LTC_LTC_SEQUENCE_LTC_SEQUENCE_A(x)  LAN80XX_EXTRACT_BITFIELD(x,0,4)

#endif /* _VTSS_MALIBU25G_REGS_PTP_PROC_H_ */
