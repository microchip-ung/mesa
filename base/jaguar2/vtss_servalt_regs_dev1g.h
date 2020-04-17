// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SERVALT_REGS_DEV1G_H_
#define _VTSS_SERVALT_REGS_DEV1G_H_


#include "vtss_servalt_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a DEV1G
 *
 * \see vtss_target_DEV1G_e
 *
 * The device operates as an interface between the TAXI bus and SGMII macro
 * supporting data rates of 10M, 100M, 1000Mbps, and 2.5 Gbps. The device
 * includes PCS, MAC and rate adaption logic.
 *
 ***********************************************************************/

/**
 * Register Group: \a DEV1G:DEV_CFG_STATUS
 *
 * Dev1g Configuration and Status Registers
 */


/** 
 * \brief DEV_RST_CTRL register
 *
 * \details
 * Clock/Reset Control Register
 *
 * Register: \a DEV1G:DEV_CFG_STATUS:DEV_RST_CTRL
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL(target)  VTSS_IOREG(target,0x0)

/** 
 * \brief
 * "This register selects the port data rate. The no clock options is
 * intended to save power for unused ports.
 * Note: The speed is also dependent on the clock the device is provided
 * with. If the device is connected to a VAUI2 lane running normal XAUI
 * speed, all values must be multiplied by a factor of 2.5. The VAUI2 clock
 * speed is setup in HSIO::SERDES6G_COMMON_CFG and HSIO::SERDES6G_PLL_CFG."
 *
 * \details 
 * 0: 10 Mbps
 * 1: 100 Mbps
 * 2: 1000 Mbps
 * 3: No clock.
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL . SPEED_SEL
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_SPEED_SEL     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_SPEED_SEL(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * Reset the PCS tx clock domain in the DEV1G. The setup registers in the
 * DEV1G is not affected by this reset.
 *
 * \details 
 * 0: No reset
 * 1: Reset. Note: PCS_TX_RST is NOT a one-shot operation. The clock domain
 * remains reset until a '0' is written to PCS_TX_RST.
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL . PCS_TX_RST
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST  VTSS_BIT(12)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Reset the PCS rx clock domain in the DEV1G. The setup registers in the
 * DEV1G is not affected by this reset.
 *
 * \details 
 * 0: No reset
 * 1: Reset. Note: PCS_RX_RST is NOT a one-shot operation. The clock domain
 * remains reset until a '0' is written to PCS_RX_RST.
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL . PCS_RX_RST
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_RX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_RX_RST  VTSS_BIT(8)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_RX_RST(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Reset the MAC tx clock domain in the DEV1G. The setup registers in the
 * DEV1G is not affected by this reset.
 *
 * \details 
 * 0: No reset
 * 1: Reset. Note: MAC_TX_RST is NOT a one-shot operation. The clock domain
 * remains reset until a '0' is written to MAC_TX_RST.
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL . MAC_TX_RST
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_TX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_TX_RST  VTSS_BIT(4)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_TX_RST(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Reset the MAC rx clock domain in the DEV1G. The setup registers in the
 * DEV1G is not affected by this reset.
 *
 * \details 
 * 0: No reset
 * 1: Reset. Note: MAC_RX_RST is NOT a one-shot operation. The clock domain
 * remains reset until a '0' is written to MAC_RX_RST.
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL . MAC_RX_RST
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_RX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_RX_RST  VTSS_BIT(0)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_RX_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Sticky bit Register
 *
 * \details
 * Clear the sticky bits by writing a '1' in the relevant bitgroups.
 *
 * Register: \a DEV1G:DEV_CFG_STATUS:DEV_STICKY
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_DEV_CFG_STATUS_DEV_STICKY(target)  VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Signal detect failure sticky bit.
 *
 * \details 
 * 0: No signal detect failure occurred
 * 1: Signal detect failures occurred
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_STICKY . SD_STICKY
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_STICKY_SD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_STICKY_SD_STICKY  VTSS_BIT(14)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_STICKY_SD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Sticky bit that indicates a protocol error on the taxi input interface.
 *
 * \details 
 * 0: No tx taxi protocol error has occured
 * 1: One or more tx taxi protocol errors have occured
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_STICKY . TX_TAXI_PROT_ERR_STICKY
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_TAXI_PROT_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_TAXI_PROT_ERR_STICKY  VTSS_BIT(12)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_TAXI_PROT_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Will be set if one of the statistics pre counter have an overflow.
 *
 * \details 
 * 0: No pre counter had an overflow
 * 1: (At least) one of the pre counters had an overflow
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_STICKY . PRE_CNT_OFLW_STICKY
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_STICKY_PRE_CNT_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_STICKY_PRE_CNT_OFLW_STICKY  VTSS_BIT(11)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_STICKY_PRE_CNT_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Indicates that an overflow has occured in the Rx Taxi FIFO.
 *
 * \details 
 * 0: No overflow has occured in the Rx Taxi FIFO
 * 1: An overflow has occured in the Rx Taxi FIFO
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_STICKY . RX_OFLW_STICKY
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_STICKY_RX_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_STICKY_RX_OFLW_STICKY  VTSS_BIT(10)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_STICKY_RX_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Indicates that a missing EOF has been detected in the Tx path of the
 * DEV1G.
 *
 * \details 
 * 0: Missing EOF has not been detected
 * 1: Missing EOF has been detected
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_STICKY . TX_EOF_STICKY
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_EOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_EOF_STICKY  VTSS_BIT(3)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_EOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Indicates that a missing SOF has been detected in the Tx path of the
 * DEV1G.
 *
 * \details 
 * 0: Missing SOF has not been detected
 * 1: Missing SOF has been detected
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_STICKY . TX_SOF_STICKY
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_SOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_SOF_STICKY  VTSS_BIT(2)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_SOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Indicates that an overflow has occured in the Tx FIFO.
 *
 * \details 
 * 0: No buffer overflow has occured
 * 1: A buffer overflow has occured
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_STICKY . TX_OFLW_STICKY
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_OFLW_STICKY  VTSS_BIT(1)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Indicates that the Tx Resync FIFO has not been able to supply enough
 * data to the MAC during frame transmission. The device automatically
 * aborts the frame transmission.
 *
 * \details 
 * 0: No buffer underflow detected
 * 1: Buffer underflow detected
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_STICKY . TX_UFLW_STICKY
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_UFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_UFLW_STICKY  VTSS_BIT(0)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_STICKY_TX_UFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Device Debug Config
 *
 * \details
 * Device1G Debug Configuration Register
 *
 * Register: \a DEV1G:DEV_CFG_STATUS:DEV_DBG_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG(target)  VTSS_IOREG(target,0x2)

/** 
 * \brief
 * Holds the ID of the last pre counter that had an overflow. The user has
 * to check the PRE_CNT_OFLW_STICKY up front. See the IS0076 for a mapping
 * of the counter ID to the counter type.
 *
 * \details 
 * 0: Pre counter 0 had an overflow (if sticky bit is set)
 * 1: Pre counter 1 had an overflow
 * ...
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG . PRE_CNT_OFLW_ID
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_PRE_CNT_OFLW_ID(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_PRE_CNT_OFLW_ID     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_PRE_CNT_OFLW_ID(x)  VTSS_EXTRACT_BITFIELD(x,24,6)

/** 
 * \brief
 * Determines the required fill level that must be EXCEEDED before the
 * buffer full signal to the DSM is asserted.
 *
 * \details 
 * 0: The 'buffer full' signal is asserted as soon as the Tx FIFO holds any
 * data
 * 1: The 'buffer full' signal is asserted if the Tx FIFO holds more than 1
 * data word
 * 2: The 'buffer full' signal is asserted if the Tx FIFO holds more than 2
 * data word
 * ...
 * 31: The 'buffer full' signal is disabled
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG . TX_BUF_HIGH_WM
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_TX_BUF_HIGH_WM(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_TX_BUF_HIGH_WM     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_TX_BUF_HIGH_WM(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Controls the FCS update function of the device.
 *
 * \details 
 * 0: Use information from DSM to control FCS updating
 * 1: Always update FCS
 * 2: Never update FCS
 * 3: Reserved
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG . FCS_UPDATE_CFG
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_FCS_UPDATE_CFG(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_FCS_UPDATE_CFG     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_FCS_UPDATE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Disable of advanced rate control feature.
 *
 * \details 
 * 0: Advanced rate control active
 * 1: Advanced rate control disabled
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG . IFG_LEN_DIS
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_IFG_LEN_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_IFG_LEN_DIS  VTSS_BIT(1)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_IFG_LEN_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * The TX_Size and the TX_Backoff events share the same counters. Per
 * default the counters count TX_SIZE events. BACKOFF_CNT_ENA switches the
 * counter to count backup events instead.
 *
 * \details 
 * 0: Count TX_SIZE events
 * 1: Count TX_BACKOFF events
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG . BACKOFF_CNT_ENA
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_BACKOFF_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_BACKOFF_CNT_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_DBG_CFG_BACKOFF_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration for the port protectio feature
 *
 * \details
 * This register is used to configure the port protection feature of the
 * device.
 *
 * Register: \a DEV1G:DEV_CFG_STATUS:DEV_PORT_PROTECT
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_DEV_CFG_STATUS_DEV_PORT_PROTECT(target)  VTSS_IOREG(target,0x3)

/** 
 * \brief
 * Indicates from which port egress data must be copied and transmitted at
 * this Ethernet port. The port from which egress data is copied must
 * always be a port that is closer to the ASM. I.e. DEV_X may be configured
 * to snoop egress data destined for DEV_X+n, where DEV_X+n is closer to
 * the ASM - but NOT vice versa.
 *
 * \details 
 * 0: Reserved
 * 1: Egress data destined for DEV_1 is also transmitted by this device
 * 2: Egress data destined for DEV_2 is also transmitted by this device
 * ...
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_PORT_PROTECT . PORT_PROTECT_ID
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_PORT_PROTECT_PORT_PROTECT_ID(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_PORT_PROTECT_PORT_PROTECT_ID     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_PORT_PROTECT_PORT_PROTECT_ID(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * Enables snooping of egress data from another port. The port from which
 * egress data is copied and transmitted at the Ethernet port is determined
 * by the PORT_PROTECT_ID configuration.
 *
 * \details 
 * 0: Port protection is disabled
 * 1: Port protection is enabled
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_PORT_PROTECT . PORT_PROTECT_ENA
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_PORT_PROTECT_PORT_PROTECT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_PORT_PROTECT_PORT_PROTECT_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_PORT_PROTECT_PORT_PROTECT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Loopback configuration
 *
 * \details
 * Register: \a DEV1G:DEV_CFG_STATUS:DEV_LB_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_DEV_CFG_STATUS_DEV_LB_CFG(target)  VTSS_IOREG(target,0x4)

/** 
 * \brief
 * When taxi loopback is enabled data received on the taxi input will be
 * passed through untouched to the taxi output. The loopback will work
 * without an active MAC clock. The device statistics will not be updated
 * when the loopback is enabled.
 *
 * \details 
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_DEV_LB_CFG . TAXI_LB_ENA
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_DEV_LB_CFG_TAXI_LB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_DEV_LB_CFG_TAXI_LB_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_DEV_LB_CFG_TAXI_LB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Control Energy Efficient Ethernet operation.
 *
 * \details
 * Register: \a DEV1G:DEV_CFG_STATUS:EEE_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_DEV_CFG_STATUS_EEE_CFG(target)  VTSS_IOREG(target,0x5)

/** 
 * \brief
 * Enable EEE operation on the port.
 * 
 * A port enters the low power mode when no egress queues have data ready.
 * 
 * The port is activated when one of the following conditions is true:
 * - A queue has been non-empty for EEE_TIMER_AGE.
 * - A queue has more than EEE_HIGH_FRAMES frames pending.
 * - A queue has more than EEE_HIGH_BYTES bytes pending.
 * - A queue is marked as a fast queue, and has data pending.

 *
 * \details 
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_EEE_CFG . EEE_ENA
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_ENA  VTSS_BIT(22)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Maximum time frames in any queue must wait before the port is activated.
 * The default value corresponds to 48 us.

 *
 * \details 
 * Time = 4**(EEE_TIMER_AGE/16) * (EEE_TIMER_AGE mod 16) microseconds
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_EEE_CFG . EEE_TIMER_AGE
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_AGE(x)  VTSS_ENCODE_BITFIELD(x,15,7)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_AGE     VTSS_ENCODE_BITMASK(15,7)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_AGE(x)  VTSS_EXTRACT_BITFIELD(x,15,7)

/** 
 * \brief
 * Time from the egress port is activated until frame transmission is
 * restarted. Default value corresponds to 16 us.
 *
 * \details 
 * Time = 4**(EEE_TIMER_WAKEUP/16) * (EEE_TIMER_WAKEUP mod 16) microseconds
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_EEE_CFG . EEE_TIMER_WAKEUP
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_WAKEUP(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_WAKEUP     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_WAKEUP(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * When all queues are empty, the port is kept active until this time has
 * passed. Default value corresponds to 5 us.
 *
 * \details 
 * Time = 4**(EEE_TIMER_HOLDOFF/16) * (EEE_TIMER_HOLDOFF mod 16)
 * microseconds
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_EEE_CFG . EEE_TIMER_HOLDOFF
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_HOLDOFF(x)  VTSS_ENCODE_BITFIELD(x,1,7)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_HOLDOFF     VTSS_ENCODE_BITMASK(1,7)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_HOLDOFF(x)  VTSS_EXTRACT_BITFIELD(x,1,7)

/** 
 * \brief
 * Status bit indicating whether port is in low-power-idle due to the LPI
 * algorithm (EEE_CFG). If set, transmissions are held back.
 *
 * \details 
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_EEE_CFG . PORT_LPI
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_EEE_CFG_PORT_LPI(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_EEE_CFG_PORT_LPI  VTSS_BIT(0)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_EEE_CFG_PORT_LPI(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PTP Configuration per port
 *
 * \details
 * Register: \a DEV1G:DEV_CFG_STATUS:PTP_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_DEV_CFG_STATUS_PTP_CFG(target)  VTSS_IOREG(target,0x6)

/** 
 * \brief
 * Disable PTP on the port
 *
 * \details 
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_PTP_CFG . PTP_ENA
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_ENA  VTSS_BIT(22)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Configures the time domain this port is assigned to. This domain
 * assignment must be made before the central counters in DEVCPU block is
 * enabled.
 *
 * \details 
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_PTP_CFG . PTP_DOM
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_DOM(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_DOM     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_DOM(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * Bit rate for the physical interface. 0: 5Gbps(QSGMII), 1: 1.25Gbps
 * SGMII), 2: 3.125 Gbps, 3: reserved
 *
 * \details 
 * 0: 5Gbps (QSGMII)
 * 1: 1.125 Gbps (SGMII)
 * 2: 3.125 Gbps (SGMII-2.5)
 * 3: Reserved
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_PTP_CFG . PTP_IF_MODE
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_IF_MODE(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_IF_MODE     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_IF_MODE(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * Time in ns to subtract from timestamper in the ingress direction to
 * compensate for static delay through the physical encoding layers.
 *
 * \details 
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_PTP_CFG . PTP_RX_IO_DLY
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_RX_IO_DLY(x)  VTSS_ENCODE_BITFIELD(x,9,9)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_RX_IO_DLY     VTSS_ENCODE_BITMASK(9,9)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_RX_IO_DLY(x)  VTSS_EXTRACT_BITFIELD(x,9,9)

/** 
 * \brief
 * Time in ns to add to timestamper in the egress direction to compensate
 * for static delay through the physical encoding layers.
 *
 * \details 
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_PTP_CFG . PTP_TX_IO_DLY
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_TX_IO_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_TX_IO_DLY     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_TX_IO_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/** 
 * \brief PTP Predictor Configuration per port
 *
 * \details
 * Register: \a DEV1G:DEV_CFG_STATUS:PTP_PREEDICT_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG(target)  VTSS_IOREG(target,0x7)

/** 
 * \brief
 * Enables various informations from internal phy when finding the right
 * ingress delayTime in ns to add to timestamper in the egress direction to
 * compensate for static delay through the physical encoding layers.
 * ffe1000, ffe100, rx_pkt, nibbl40, nibb400, add_delay200
 *
 * \details 
 * xxxxxxx1: FFE1000 value will be added
 * xxxxxx1x: FFE100 value will be added 
 * xxxxx1xx: Rx_Pkt delay x8 will be added
 * xxxx1xxx: 40 ns will be added if nibble_inserted is set
 * xxx1xxxx: 400 ns will be added if nibble inserted is set
 * xx1xxxxx: 200 ns will be added if add_delay200 is set
 * x1xxxxxx: Nibble inserted will be inverted
 * 1xxxxxxx: RxPkt delay will be negated
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG . PTP_PHY_PREDICT_CFG
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHY_PREDICT_CFG(x)  VTSS_ENCODE_BITFIELD(x,4,8)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHY_PREDICT_CFG     VTSS_ENCODE_BITMASK(4,8)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHY_PREDICT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,4,8)

/** 
 * \brief
 * Enables increased accuracy in the time stamping logic, by finding the
 * dynamic phase between port and 1588 clocks.
 *
 * \details 
 * 0001: 125 MHz port clock
 * 0010:  25 MHz port clock
 * 0011:  2.5 MHz port clock
 * 0100:  161.13 MHz port clock
 * 0101:  156.25 MHz port clock
 * others: Disabled
 *
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG . PTP_PHASE_PREDICT_CFG
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHASE_PREDICT_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHASE_PREDICT_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHASE_PREDICT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief PTP events per port
 *
 * \details
 * Register: \a DEV1G:DEV_CFG_STATUS:PTP_EVENTS
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_DEV_CFG_STATUS_PTP_EVENTS(target)  VTSS_IOREG(target,0x8)

/** 
 * \brief
 * The correction field update went out of range. Valid range is -2^47 to
 * 2^48-1. The frame CF will be changed to the maximum value. This range
 * check is bypassed if ADDS48 mode is in use on the ingress or egress
 * port.
 *
 * \details 
 * Field: ::VTSS_DEV1G_DEV_CFG_STATUS_PTP_EVENTS . CF_TOO_BIG_STICKY
 */
#define  VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_EVENTS_CF_TOO_BIG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_DEV_CFG_STATUS_PTP_EVENTS_CF_TOO_BIG_STICKY  VTSS_BIT(0)
#define  VTSS_X_DEV1G_DEV_CFG_STATUS_PTP_EVENTS_CF_TOO_BIG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a DEV1G:MAC_CFG_STATUS
 *
 * MAC1G Configuration and Status Registers
 */


/** 
 * \brief Mode Configuration Register
 *
 * \details
 * Register: \a DEV1G:MAC_CFG_STATUS:MAC_ENA_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG(target)  VTSS_IOREG(target,0x9)

/** 
 * \brief
 * Receiver Module Enable.
 *
 * \details 
 * '0': Receiver Module Disabled
 * '1': Receiver Module Enabled
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG . RX_ENA
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Transmitter Module Enable.
 *
 * \details 
 * '0': Transmitter Module Disabled
 * '1': Transmitter Module Enabled
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG . TX_ENA
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG_TX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG_TX_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_ENA_CFG_TX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Mode Configuration Register
 *
 * \details
 * Register: \a DEV1G:MAC_CFG_STATUS:MAC_MODE_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG(target)  VTSS_IOREG(target,0xa)

/** 
 * \brief
 * This bit enables synchronization of Flow Control Jamming to currently
 * used word boundaries (10/100 Mbps mode).
 *
 * \details 
 * '0' Normal mode, Flow Control Jamming is output as soon as possible
 * '1' Word sync mode, Flow Control Jamming is synchronized 10/100 Mbps
 * word boundaries

 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG . FC_WORD_SYNC_ENA
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG_FC_WORD_SYNC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG_FC_WORD_SYNC_ENA  VTSS_BIT(8)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG_FC_WORD_SYNC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Enables 1 Gbps mode.
 *
 * \details 
 * '0': 10/100 Mbps mode
 * '1': 1 Gbps and 2.5 Gbps mode. Note: FDX MUST be asserted.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG . GIGA_MODE_ENA
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG_GIGA_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG_GIGA_MODE_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG_GIGA_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enables Full-Duplex:
 *
 * \details 
 * '0': Half-duplex
 * '1': Full-duplex.

 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG . FDX_ENA
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG_FDX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG_FDX_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_MODE_CFG_FDX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Max Length Configuration Register
 *
 * \details
 * Register: \a DEV1G:MAC_CFG_STATUS:MAC_MAXLEN_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_MAC_CFG_STATUS_MAC_MAXLEN_CFG(target)  VTSS_IOREG(target,0xb)

/** 
 * \brief
 * The maximum frame length accepted by the Receive Module of the MAC. If
 * the length is exceeded, this is indicated in the Statistics Engine
 * (RX_OVERSIZE). The maximum length is automatically adjusted to
 * accommodate maximum sized frames containing single/double VLAN tag(s) -
 * given that the MAC is configured to be single/double VLAN aware.
 *
 * \details 
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_MAXLEN_CFG . MAX_LEN
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VLAN / Service tag configuration register
 *
 * \details
 * The MAC can be configured to accept 0, 1 and 2 tags and the TAG value
 * can be user-defined.
 *
 * Register: \a DEV1G:MAC_CFG_STATUS:MAC_TAGS_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG(target)  VTSS_IOREG(target,0xc)

/** 
 * \brief
 * This field defines a 1st programmable VLAN/Service tag (custom TPID
 * 1).\nThis field together with the TAG_ID2 and TAG_ID3 - as well as the
 * default tags 0x8100 and 0x88A8 - are used for ALL possible tag positions
 * (up to 3). Any order of known VLAN/Service tags (0x8100, 0x88A8, TAG_ID,
 * TAG_ID2, TAG_ID3) is found. VLAN/Service tag awareness depends on
 * VLAN_AWR_ENA and PB_ENA.
 *
 * \details 
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG . TAG_ID
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * When set, single, double and triple tagged frames are allowed to be
 * 4/8/12 bytes longer than the MAXLEN configuration.
 *
 * \details 
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG . VLAN_LEN_AWR_ENA
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_LEN_AWR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_LEN_AWR_ENA  VTSS_BIT(3)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_LEN_AWR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Provider Bridge Enable (multiple VLAN awareness)
 *
 * \details 
 * 0: The MAC operates in a single VLAN aware mode.
 * 1: The MAC operates in a double VLAN aware mode.
 * 2: The MAC operates in a triple VLAN aware mode.
 * 3: Reserved.
 * For VLAN awareness to take effect VLAN_AWR_ENA must be set to '1'.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG . PB_ENA
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_PB_ENA(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_PB_ENA     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_PB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * VLAN Awareness: Enables the MAC to work in a VLAN aware environment.
 *
 * \details 
 * '0': VLAN awareness disabled.
 * '1': VLAN awareness enabled.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG . VLAN_AWR_ENA
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_AWR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_AWR_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_AWR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief VLAN / Service tag configuration register2
 *
 * \details
 * This register contains two additional freely programmable custom VLAN
 * tags.
 *
 * Register: \a DEV1G:MAC_CFG_STATUS:MAC_TAGS_CFG2
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG2(target)  VTSS_IOREG(target,0xd)

/** 
 * \brief
 * This field defines a 3rd programmable VLAN/Service tag (custom TPID 3).
 *
 * \details 
 * tbd
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG2 . TAG_ID3
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG2_TAG_ID3(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG2_TAG_ID3     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG2_TAG_ID3(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * This field defines a 2nd programmable VLAN/Service tag (custom TPID 2).
 *
 * \details 
 * tbd
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG2 . TAG_ID2
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG2_TAG_ID2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG2_TAG_ID2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_TAGS_CFG2_TAG_ID2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Advanced Check Feature Configuration Register
 *
 * \details
 * Register: \a DEV1G:MAC_CFG_STATUS:MAC_ADV_CHK_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG(target)  VTSS_IOREG(target,0xe)

/** 
 * \brief
 * Length Drop Enable:\nConfigures the Receive Module to drop frames in
 * reference to in-range and out-of-range errors:
 *
 * \details 
 * '0': Length Drop Disabled
 * '1': Length Drop Enabled.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG . LEN_DROP_ENA
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_LEN_DROP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_LEN_DROP_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_LEN_DROP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Inter Frame Gap Configuration Register
 *
 * \details
 * Register: \a DEV1G:MAC_CFG_STATUS:MAC_IFG_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG(target)  VTSS_IOREG(target,0xf)

/** 
 * \brief
 * This configuration bit allows to relax the minimum IPG check to 11
 * symbols instead of 12. If the IPG is below 12 (or 11 if relaxed mode is
 * enabled) the IPG_SHRINK statistics counter is incremented. 
 *
 * \details 
 * '0' Normal mode (check for minimum IPG of 12 symbols)
 * '1' Relaxed mode (check for minimum IPG of 11 symbols)
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG . RESTORE_OLD_IPG_CHECK
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_RESTORE_OLD_IPG_CHECK(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_RESTORE_OLD_IPG_CHECK  VTSS_BIT(17)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_RESTORE_OLD_IPG_CHECK(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Used to adjust the duration of the inter-frame gap in the Tx direction
 * and must be set according to the speed and duplex settings.
 *
 * \details 
 * TBA: Add correct values found by validation. 10/100 Mbps, HDX, FDX 0xXX,
 * 0xXX
 * 1000/2500 Mbps: 0xXX.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG . TX_IFG
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_TX_IFG(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_TX_IFG     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_TX_IFG(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Used to adjust the duration of the second part of the inter-frame gap in
 * the Rx direction and must be set according to the speed and duplex
 * settings.
 *
 * \details 
 * TBA: Add correct values found by validation. 10/100 Mbps, HDX, FDX:
 * 0xXX, 0xXX
 * 1000/2500 Mbps: 0xXX.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG . RX_IFG2
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG2(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG2     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG2(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Used to adjust the duration of the first part of the inter-frame gap in
 * the Rx direction and must be set according to the speed settings.
 *
 * \details 
 * TBA: Add correct values found by validation. 10/100 Mbps: 0xXX
 * 1000/2500 Mbps: 0xXX.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG . RX_IFG1
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief half-duplex Configuration Register
 *
 * \details
 * Register: \a DEV1G:MAC_CFG_STATUS:MAC_HDX_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG(target)  VTSS_IOREG(target,0x10)

/** 
 * \brief
 * Bypass 2-step synchronization of collision signal gmii_col in defer and
 * backoff logic to allow for optimized collision handling in half-duplex
 * modes
 *
 * \details 
 * '0': Do not bypass gmii_col sync stage
 * '1': Bypass gmii_col sync stage
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG . BYPASS_COL_SYNC
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_BYPASS_COL_SYNC(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_BYPASS_COL_SYNC  VTSS_BIT(26)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_BYPASS_COL_SYNC(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Seed value loaded into the PRBS of the MAC.
 *
 * \details 
 * Used to prevent excessive collision events.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG . SEED
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_SEED(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_SEED     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_SEED(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Load SEED value into PRNG register. A SEED value is loaded into the PRNG
 * register of the MAC, when SEED_LOAD is asserted. After a load, the
 * SEED_LOAD must be deasserted.
 *
 * \details 
 * '0': Do not load SEED value
 * '1': Load SEED value.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG . SEED_LOAD
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_SEED_LOAD(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_SEED_LOAD  VTSS_BIT(12)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_SEED_LOAD(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * This bit is used to setup the MAC to retransmit a frame after an early
 * collision even though 16 (or more) early collisions have occurred. This
 * feature violates the IEEE 802.3 standard and should only be used when
 * running in HDX flow control, which is not defined in the IEEE standard
 * anyway.
 *
 * \details 
 * '0': A frame will be discarded and counted as an excessive collision if
 * 16 collisions occur for this frame.
 * '1': The MAC will retransmit a frame after an early collision,
 * regardless of the number of previous early collisions. The backoff
 * sequence will be reset after every 16 collisions.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG . RETRY_AFTER_EXC_COL_ENA
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA  VTSS_BIT(8)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Adjustment of early/late collision boundary:\nThis bitgroup is used to
 * adjust the MAC so that a collision on a shared transmission medium
 * before bit 512 is handled as an early collision, whereas a collision
 * after bit 512 is handled as a late collision, i.e. no retransmission is
 * performed.
 *
 * \details 
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG . LATE_COL_POS
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_LATE_COL_POS(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_LATE_COL_POS     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_HDX_CFG_LATE_COL_POS(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief Sticky Bit Register
 *
 * \details
 * Register: \a DEV1G:MAC_CFG_STATUS:MAC_STICKY
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_MAC_CFG_STATUS_MAC_STICKY(target)  VTSS_IOREG(target,0x11)

/** 
 * \brief
 * Sticky bit indicating that an inter packet gap shrink was detected (IPG
 * < 12 bytes).
 *
 * \details 
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_STICKY . RX_IPG_SHRINK_STICKY
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_STICKY_RX_IPG_SHRINK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_STICKY_RX_IPG_SHRINK_STICKY  VTSS_BIT(9)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_STICKY_RX_IPG_SHRINK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Sticky bit indicating that a preamble shrink was detected (preamble < 8
 * bytes).
 *
 * \details 
 * '0': no preamble shrink was detected
 * '1': a preamble shrink was detected one or more times
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_STICKY . RX_PREAM_SHRINK_STICKY
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_STICKY_RX_PREAM_SHRINK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_STICKY_RX_PREAM_SHRINK_STICKY  VTSS_BIT(8)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_STICKY_RX_PREAM_SHRINK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Sticky bit indicating that junk was received (bytes not recognized as a
 * frame).
 *
 * \details 
 * '0': no junk was received
 * '1': junk was received one or more times
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_STICKY . RX_JUNK_STICKY
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_STICKY_RX_JUNK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_STICKY_RX_JUNK_STICKY  VTSS_BIT(5)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_STICKY_RX_JUNK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Sticky bit indicating that the transmit MAC asked the host for a frame
 * retransmission.
 *
 * \details 
 * '0': no tx retransmission was initiated
 * '1': one or more tx retransmissions were initiated
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_STICKY . TX_RETRANSMIT_STICKY
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_STICKY_TX_RETRANSMIT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_STICKY_TX_RETRANSMIT_STICKY  VTSS_BIT(4)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_STICKY_TX_RETRANSMIT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Sticky bit indicating that the transmit host issued a jamming signal.
 *
 * \details 
 * '0': the transmit host issued no jamming signal
 * '1': the transmit host issued one or morejamming signals
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_STICKY . TX_JAM_STICKY
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_STICKY_TX_JAM_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_STICKY_TX_JAM_STICKY  VTSS_BIT(3)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_STICKY_TX_JAM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Sticky bit indicating that the MAC transmit FIFO has overrun.
 *
 * \details 
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_STICKY . TX_FIFO_OFLW_STICKY
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_STICKY_TX_FIFO_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_STICKY_TX_FIFO_OFLW_STICKY  VTSS_BIT(2)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_STICKY_TX_FIFO_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Sticky bit indicating that the transmit host initiated abort was
 * executed.
 *
 * \details 
 * Field: ::VTSS_DEV1G_MAC_CFG_STATUS_MAC_STICKY . TX_ABORT_STICKY
 */
#define  VTSS_F_DEV1G_MAC_CFG_STATUS_MAC_STICKY_TX_ABORT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_MAC_CFG_STATUS_MAC_STICKY_TX_ABORT_STICKY  VTSS_BIT(0)
#define  VTSS_X_DEV1G_MAC_CFG_STATUS_MAC_STICKY_TX_ABORT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a DEV1G:PCS1G_CFG_STATUS
 *
 * PCS 1G Configuration Status Registers
 */


/** 
 * \brief PCS1G Configuration
 *
 * \details
 * PCS1G main configuration register
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG(target)  VTSS_IOREG(target,0x12)

/** 
 * \brief
 * Set type of link_status indication at CPU-System
 *
 * \details 
 * 0: Sync_status (from PCS synchronization state machine)
 * 1: Bit 15 of PCS1G_ANEG_STATUS.lp_adv_ability (Link up/down)
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG . LINK_STATUS_TYPE
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_LINK_STATUS_TYPE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_LINK_STATUS_TYPE  VTSS_BIT(4)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_LINK_STATUS_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable Link control using Backplane Ethernet ANEG
 *
 * \details 
 * 0: Disable link control
 * 1: Enable link control
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG . AN_LINK_CTRL_ENA
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_AN_LINK_CTRL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_AN_LINK_CTRL_ENA  VTSS_BIT(1)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_AN_LINK_CTRL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * PCS enable
 *
 * \details 
 * 0: Disable PCS
 * 1: Enable PCS
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG . PCS_ENA
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS1G Mode Configuration
 *
 * \details
 * PCS1G mode configuration
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_MODE_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG(target)  VTSS_IOREG(target,0x13)

/** 
 * \brief
 * Unidirectional mode enable. Implementation of 802.3, Clause 66. When
 * asserted, this enables MAC to transmit data independent of the state of
 * the receive link.
 *
 * \details 
 * 0: Unidirectional mode disabled
 * 1: Unidirectional mode enabled
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG . UNIDIR_MODE_ENA
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG_UNIDIR_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG_UNIDIR_MODE_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG_UNIDIR_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Selection of PCS operation
 *
 * \details 
 * 0: PCS is used in SERDES mode
 * 1: PCS is used in SGMII mode
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG . SGMII_MODE_ENA
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG_SGMII_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG_SGMII_MODE_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG_SGMII_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS1G Signal Detect Configuration
 *
 * \details
 * PCS1G signal_detect configuration
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_SD_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG(target)  VTSS_IOREG(target,0x14)

/** 
 * \brief
 * Signal detect selection (select input for internal signal_detect line)
 *
 * \details 
 * 0: Select signal_detect line from hardmacro
 * 1: Select external signal_detect line
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG . SD_SEL
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_SEL  VTSS_BIT(8)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Signal detect polarity: The signal level on signal_detect input pin must
 * be equal to SD_POL to indicate signal detection (SD_ENA must be set)
 *
 * \details 
 * 0: Signal Detect input pin must be '0' to indicate a signal detection
 * 1: Signal Detect input pin must be '1' to indicate a signal detection
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG . SD_POL
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_POL  VTSS_BIT(4)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_POL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Signal Detect Enable
 *
 * \details 
 * 0: The Signal Detect input pin is ignored. The PCS assumes an active
 * Signal Detect at all times
 * 1: The Signal Detect input pin is used to determine if a signal is
 * detected
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG . SD_ENA
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS1G Aneg Configuration
 *
 * \details
 * PCS1G Auto-negotiation configuration register
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_ANEG_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(target)  VTSS_IOREG(target,0x15)

/** 
 * \brief
 * Advertised Ability Register: Holds the capabilities of the device as
 * described IEEE 802.3, Clause 37.
 *
 * \details 
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG . ADV_ABILITY
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Software Resolve Abilities
 *
 * \details 
 * 0: If Auto Negotiation fails (no matching HD or FD capabilities) the
 * link is disabled.
 * 1: The result of an Auto Negotiation is ignored - the link can be setup
 * through software. This bit must be set in SGMII mode.
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG . SW_RESOLVE_ENA
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_SW_RESOLVE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_SW_RESOLVE_ENA  VTSS_BIT(8)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_SW_RESOLVE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Auto Negotiation Restart
 *
 * \details 
 * 0: No action
 * 1: Restart Auto Negotiation
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG . ANEG_RESTART_ONE_SHOT
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT  VTSS_BIT(1)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Auto Negotiation Enable
 *
 * \details 
 * 0: Auto Negotiation Disabled
 * 1: Auto Negotiation Enabled
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG . ANEG_ENA
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS1G Aneg Next Page Configuration
 *
 * \details
 * PCS1G Auto-negotiation configuration register for next-page function
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_ANEG_NP_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG(target)  VTSS_IOREG(target,0x16)

/** 
 * \brief
 * Next page register: Holds the next-page information as described in IEEE
 * 802.3, Clause 37
 *
 * \details 
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG . NP_TX
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG_NP_TX(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG_NP_TX     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG_NP_TX(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Next page loaded
 *
 * \details 
 * 0: next page is free and can be loaded
 * 1: next page register has been filled (to be set after np_tx has been
 * filled)
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG . NP_LOADED_ONE_SHOT
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG_NP_LOADED_ONE_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG_NP_LOADED_ONE_SHOT  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG_NP_LOADED_ONE_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS1G Loopback Configuration
 *
 * \details
 * PCS1G loopback configuration register
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_LB_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG(target)  VTSS_IOREG(target,0x17)

/** 
 * \brief
 * Enable rate adaption capability in PCS receive direction explicitely
 * (required when PHY data looped back within MAC)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG . RA_ENA
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG_RA_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG_RA_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG_RA_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Loops data in PCS (GMII side) from ingress direction to egress
 * direction. Rate adaption is automatically performed in a FIFO within the
 * PCS
 *
 * \details 
 * 0: GMII Loopback Disabled
 * 1:GMII Loopback Enabled
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG . GMII_PHY_LB_ENA
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG_GMII_PHY_LB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG_GMII_PHY_LB_ENA  VTSS_BIT(1)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG_GMII_PHY_LB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Loops data in PCS (TBI side) from egress direction to ingress direction.
 * The Rx clock is automatically set equal to the Tx clock
 *
 * \details 
 * 0: TBI Loopback Disabled
 * 1:TBI Loopback Enabled
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG . TBI_HOST_LB_ENA
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG_TBI_HOST_LB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG_TBI_HOST_LB_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG_TBI_HOST_LB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS1G Debug Configuration
 *
 * \details
 * PCS1G Debug configuration register
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_DBG_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_DBG_CFG(target)  VTSS_IOREG(target,0x18)

/** 
 * \brief
 * Use Debug Link Timer
 *
 * \details 
 * 0: Normal 10 ms (1.6 ms in sgmii mode) timer is selected
 * 1: Reduced 9.77 us (1.56 us in sgmii mode) timer is selected
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_DBG_CFG . UDLT
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_DBG_CFG_UDLT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_DBG_CFG_UDLT  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_DBG_CFG_UDLT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS1G comma detection Configuration
 *
 * \details
 * PCS1G comma detection configuration
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_CDET_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_CDET_CFG(target)  VTSS_IOREG(target,0x19)

/** 
 * \brief
 * Enable comma detection and code-group alignment
 *
 * \details 
 * 0: Comma detection disabled
 * 1: Comma detection enabled
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_CDET_CFG . CDET_ENA
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_CDET_CFG_CDET_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_CDET_CFG_CDET_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_CDET_CFG_CDET_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS1G ANEG Status Register
 *
 * \details
 * PCS1G Auto-negotiation status register
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_ANEG_STATUS
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS(target)  VTSS_IOREG(target,0x1a)

/** 
 * \brief
 * Advertised abilities from link partner as described in IEEE 802.3,
 * Clause 37
 *
 * \details 
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS . LP_ADV_ABILITY
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_LP_ADV_ABILITY(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_LP_ADV_ABILITY     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_LP_ADV_ABILITY(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Resolve priority
 *
 * \details 
 * 0: ANEG is in progress
 * 1: ANEG nearly finished - priority can be resolved (through software)
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS . PR
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_PR(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_PR  VTSS_BIT(4)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_PR(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Status indicating whether a new page has been received.
 *
 * \details 
 * 0: No new page received
 * 1: New page received
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS . PAGE_RX_STICKY
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_PAGE_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_PAGE_RX_STICKY  VTSS_BIT(3)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_PAGE_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Auto Negotiation Complete
 *
 * \details 
 * 0: No Auto Negotiation has been completed
 * 1: Indicates that an Auto Negotiation has completed successfully
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS . ANEG_COMPLETE
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_ANEG_COMPLETE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_ANEG_COMPLETE  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_ANEG_COMPLETE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS1G Aneg Next Page Status Register
 *
 * \details
 * PCS1G Auto-negotiation next page status register
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_ANEG_NP_STATUS
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_STATUS(target)  VTSS_IOREG(target,0x1b)

/** 
 * \brief
 * Next page ability register from link partner as described in IEEE 802.3,
 * Clause 37
 *
 * \details 
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_STATUS . LP_NP_RX
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_STATUS_LP_NP_RX(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_STATUS_LP_NP_RX     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_STATUS_LP_NP_RX(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief PCS1G link status
 *
 * \details
 * PCS1G link status register
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_LINK_STATUS
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(target)  VTSS_IOREG(target,0x1c)

/** 
 * \brief
 * Additional delay in rx-path; multiply the value of this field by the
 * line-rate bit-period (800ps for 10/100/1000, 320ps for 2G5 mode.) This
 * field is valid when the link is up, it remains constant for as long as
 * the link is up, value may cange on link-down event.
 * This field shows the number of data bits that is stored in the rx
 * comma-alignment block, values of 0-9 is possible.
 *
 * \details 
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS . DELAY_VAR
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_DELAY_VAR(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_DELAY_VAR     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_DELAY_VAR(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Indicates whether or not the selected Signal Detect input line is
 * asserted; doesn't consider the Polarity
 *
 * \details 
 * 0: No signal detected
 * 1: Signal detected
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS . SIGNAL_DETECT
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SIGNAL_DETECT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SIGNAL_DETECT  VTSS_BIT(8)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SIGNAL_DETECT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Indicates whether the link is up or down. A link is up when ANEG state
 * machine is in state LINK_OK or AN_DISABLE_LINK_OK
 *
 * \details 
 * 0: Link down
 * 1: Link up
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS . LINK_STATUS
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_LINK_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_LINK_STATUS  VTSS_BIT(4)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_LINK_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Indicates if PCS has successfully synchronized
 *
 * \details 
 * 0: PCS is out of sync
 * 1: PCS has synchronized
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS . SYNC_STATUS
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SYNC_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SYNC_STATUS  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SYNC_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS1G link down counter
 *
 * \details
 * PCS1G link down counter register
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_LINK_DOWN_CNT
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_DOWN_CNT(target)  VTSS_IOREG(target,0x1d)

/** 
 * \brief
 * Link Down Counter. A counter that counts the number of times a link has
 * been down. The counter does not saturate at 255 and is only cleared when
 * writing 0 to the register
 *
 * \details 
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_DOWN_CNT . LINK_DOWN_CNT
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_DOWN_CNT_LINK_DOWN_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_DOWN_CNT_LINK_DOWN_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_DOWN_CNT_LINK_DOWN_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief PCS1G sticky register
 *
 * \details
 * PCS1G status register for sticky bits
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_STICKY
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY(target)  VTSS_IOREG(target,0x1e)

/** 
 * \brief
 * The sticky bit is set when the link has been down - i.e. if the ANEG
 * state machine has not been in the AN_DISABLE_LINK_OK or LINK_OK state
 * for one or more clock cycles. This occurs if e.g. ANEG is restarted or
 * for example if signal-detect or synchronization has been lost for more
 * than 10 ms (1.6 ms in SGMII mode). By setting the UDLT bit, the required
 * down time can be reduced to 9,77 us (1.56 us)
 *
 * \details 
 * 0: Link is up
 * 1: Link has been down
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY . LINK_DOWN_STICKY
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY  VTSS_BIT(4)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Sticky bit indicating if PCS synchronization has been lost
 *
 * \details 
 * 0: Synchronization has not been lost at any time
 * 1: Synchronization has been lost for one or more clock cycles
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY . OUT_OF_SYNC_STICKY
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY_OUT_OF_SYNC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY_OUT_OF_SYNC_STICKY  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_STICKY_OUT_OF_SYNC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS1G debug status
 *
 * \details
 * PCS1G debug status register
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_DEBUG_STATUS
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_DEBUG_STATUS(target)  VTSS_IOREG(target,0x1f)

/** 
 * \brief
 * Indicates the mode of the TBI
 *
 * \details 
 * 00: Idle mode
 * 01: Configuration mode
 * 10: Reserved
 * 11: Data mode
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_DEBUG_STATUS . XMIT_MODE
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_DEBUG_STATUS_XMIT_MODE(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_DEBUG_STATUS_XMIT_MODE     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_DEBUG_STATUS_XMIT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,12,2)


/** 
 * \brief PCS1G Low Power Idle Configuration
 *
 * \details
 * Configuration register for Low Power Idle (Energy Efficient Ethernet)
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_LPI_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG(target)  VTSS_IOREG(target,0x20)

/** 
 * \brief
 * QSGMII master/slave selection (only one master allowed per QSGMII). The
 * master drives LPI timing on serdes
 *
 * \details 
 * 0: Slave
 * 1: Master
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG . QSGMII_MS_SEL
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_QSGMII_MS_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_QSGMII_MS_SEL  VTSS_BIT(20)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_QSGMII_MS_SEL(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Disable output of Low-Power Idle in receive direction (to core)
 *
 * \details 
 * 0: Enable
 * 1: Disable
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG . RX_LPI_OUT_DIS
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_RX_LPI_OUT_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_RX_LPI_OUT_DIS  VTSS_BIT(17)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_RX_LPI_OUT_DIS(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * LPI-Timer test mode.
 *
 * \details 
 * 0: Normal timing constants are used
 * 1: Shortened timing constants are used
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG . LPI_TESTMODE
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_LPI_TESTMODE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_LPI_TESTMODE  VTSS_BIT(16)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_LPI_TESTMODE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Assert Low-Power Idle (LPI) in transmit mode
 *
 * \details 
 * 0: Disable LPI transmission
 * 1: Enable LPI transmission
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG . TX_ASSERT_LPIDLE
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_TX_ASSERT_LPIDLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_TX_ASSERT_LPIDLE  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_TX_ASSERT_LPIDLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS1G wake error counter
 *
 * \details
 * PCS1G Low Power Idle wake error counter (Energy Efficient Ethernet)
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_LPI_WAKE_ERROR_CNT
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_WAKE_ERROR_CNT(target)  VTSS_IOREG(target,0x21)

/** 
 * \brief
 * Wake Error Counter. A counter that is incremented when the link partner
 * does not send wake-up burst in due time. The counter saturates at 65535
 * and is cleared when writing 0 to the register
 *
 * \details 
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_WAKE_ERROR_CNT . WAKE_ERROR_CNT
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_WAKE_ERROR_CNT_WAKE_ERROR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_WAKE_ERROR_CNT_WAKE_ERROR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_WAKE_ERROR_CNT_WAKE_ERROR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS1G Low Power Idle Status
 *
 * \details
 * Status register for Low Power Idle (Energy Efficient Ethernet)
 *
 * Register: \a DEV1G:PCS1G_CFG_STATUS:PCS1G_LPI_STATUS
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS(target)  VTSS_IOREG(target,0x22)

/** 
 * \brief
 * Receiver Low-Power idle occurrence
 *
 * \details 
 * 0: No LPI symbols received
 * 1: Receiver has received LPI symbols
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS . RX_LPI_EVENT_STICKY
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_RX_LPI_EVENT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_RX_LPI_EVENT_STICKY  VTSS_BIT(12)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_RX_LPI_EVENT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Receiver Low-Power Quiet mode
 *
 * \details 
 * 0: Receiver not in quiet mode
 * 1: Receiver is in quiet mode
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS . RX_QUIET
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_RX_QUIET(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_RX_QUIET  VTSS_BIT(9)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_RX_QUIET(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Receiver Low-Power Idle mode
 *
 * \details 
 * 0: Receiver not in low power idle mode
 * 1: Receiver is in low power idle mode
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS . RX_LPI_MODE
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_RX_LPI_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_RX_LPI_MODE  VTSS_BIT(8)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_RX_LPI_MODE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Transmitter Low-Power idle occurrence
 *
 * \details 
 * 0: No LPI symbols transmitted
 * 1: Transmitter has transmitted LPI symbols
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS . TX_LPI_EVENT_STICKY
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_TX_LPI_EVENT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_TX_LPI_EVENT_STICKY  VTSS_BIT(4)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_TX_LPI_EVENT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Transmitter Low-Power Quiet mode
 *
 * \details 
 * 0: Transmitter not in quiet mode
 * 1: Transmitter is in quiet mode
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS . TX_QUIET
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_TX_QUIET(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_TX_QUIET  VTSS_BIT(1)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_TX_QUIET(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Transmitter Low-Power Idle mode
 *
 * \details 
 * 0: Transmitter not in low power idle mode
 * 1: Transmitter is in low power idle mode
 *
 * Field: ::VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS . TX_LPI_MODE
 */
#define  VTSS_F_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_TX_LPI_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_TX_LPI_MODE  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_TX_LPI_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a DEV1G:PCS1G_TSTPAT_CFG_STATUS
 *
 * PCS1G Testpattern Configuration and Status Registers
 */


/** 
 * \brief PCS1G TSTPAT MODE CFG
 *
 * \details
 * PCS1G testpattern mode configuration register (Frame based pattern 4 and
 * 5 might be not available depending on chip type)
 *
 * Register: \a DEV1G:PCS1G_TSTPAT_CFG_STATUS:PCS1G_TSTPAT_MODE_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_MODE_CFG(target)  VTSS_IOREG(target,0x23)

/** 
 * \brief
 * Jitter Test Pattern Select: Enables and selects the jitter test pattern
 * to be transmitted. The jitter test patterns are according to the IEEE
 * 802.3, Annex 36A
 *
 * \details 
 * 0: Disable transmission of test patterns
 * 1: High frequency test pattern - repeated transmission of D21.5 code
 * group
 * 2: Low frequency test pattern - repeated transmission of K28.7 code
 * group
 * 3: Mixed frequency test pattern - repeated transmission of K28.5 code
 * group
 * 4: Long continuous random test pattern (packet length is 1524 bytes)
 * 5: Short continuous random test pattern (packet length is 360 bytes)
 *
 * Field: ::VTSS_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_MODE_CFG . JTP_SEL
 */
#define  VTSS_F_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_MODE_CFG_JTP_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_MODE_CFG_JTP_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_MODE_CFG_JTP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief PCS1G TSTPAT STATUS
 *
 * \details
 * PCS1G testpattern status register
 *
 * Register: \a DEV1G:PCS1G_TSTPAT_CFG_STATUS:PCS1G_TSTPAT_STATUS
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS(target)  VTSS_IOREG(target,0x24)

/** 
 * \brief
 * Jitter Test Pattern Error Counter. Due to re-sync measures it might
 * happen that single errors are not counted (applies for 2.5gpbs mode).
 * The counter saturates at 255 and is only cleared when writing 0 to the
 * register
 *
 * \details 
 * Field: ::VTSS_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS . JTP_ERR_CNT
 */
#define  VTSS_F_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_ERR_CNT     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Jitter Test Pattern Error
 *
 * \details 
 * 0: Jitter pattern checker has found no error
 * 1: Jitter pattern checker has found an error
 *
 * Field: ::VTSS_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS . JTP_ERR
 */
#define  VTSS_F_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_ERR  VTSS_BIT(4)
#define  VTSS_X_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_ERR(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Jitter Test Pattern Lock
 *
 * \details 
 * 0: Jitter pattern checker has not locked
 * 1: Jitter pattern checker has locked
 *
 * Field: ::VTSS_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS . JTP_LOCK
 */
#define  VTSS_F_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_LOCK  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a DEV1G:PCS_FX100_CONFIGURATION
 *
 * PCS FX100 Configuration Registers
 */


/** 
 * \brief PCS 100Base FX Configuration
 *
 * \details
 * Configuration bit groups for 100Base-FX PCS
 *
 * Register: \a DEV1G:PCS_FX100_CONFIGURATION:PCS_FX100_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(target)  VTSS_IOREG(target,0x25)

/** 
 * \brief
 * Signal detect selection (select input for internal signal_detect line)
 *
 * \details 
 * 0: Select signal_detect line from hardmacro
 * 1: Select external signal_detect line
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG . SD_SEL
 */
#define  VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_SEL  VTSS_BIT(26)
#define  VTSS_X_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Signal detect polarity: The signal level on signal_detect input pin must
 * be equal to SD_POL to indicate signal detection (SD_ENA must be set).
 * Use '1' when SD_SEL is set to hardmacro.
 *
 * \details 
 * 0: Signal Detect input pin must be '0' to indicate a signal detection
 * 1: Signal Detect input pin must be '1' to indicate a signal detection
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG . SD_POL
 */
#define  VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_POL  VTSS_BIT(25)
#define  VTSS_X_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_POL(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Signal Detect Enable
 *
 * \details 
 * 0: The Signal Detect input pin is ignored. The PCS assumes an active
 * Signal Detect at all times
 * 1: The Signal Detect input pin is used to determine if a signal is
 * detected
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG . SD_ENA
 */
#define  VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA  VTSS_BIT(24)
#define  VTSS_X_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Testloop, if enabled 4B5B encoded data are looped from TX path to RX
 * path just before the SERDES
 *
 * \details 
 * 1: Enable loop
 * 0: Disable loop
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG . LOOPBACK_ENA
 */
#define  VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_LOOPBACK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_LOOPBACK_ENA  VTSS_BIT(20)
#define  VTSS_X_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_LOOPBACK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Swap transmission/receive order of MII nibbles
 *
 * \details 
 * 0: Lower nibble of GMII byte is transferred/received first
 * 1: Upper nibble of GMII byte is transferred/received first
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG . SWAP_MII_ENA
 */
#define  VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SWAP_MII_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SWAP_MII_ENA  VTSS_BIT(16)
#define  VTSS_X_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SWAP_MII_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Select single bit from incomming 10-bit Deserializer value. Change is
 * only required in case CP/MD handling incorrect in Clock and Data
 * Recovery logic
 *
 * \details 
 * Field: ::VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG . RXBITSEL
 */
#define  VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_RXBITSEL(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_RXBITSEL     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_RXBITSEL(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Influence of rx toggle-rate on signal_detect. Signal detect is forced to
 * 0 after a programable number of missing edges on rx bit-stream
 *
 * \details 
 * 0: No influence
 * 1: Force to 0 after 50 cycles without edge
 * 2: Force to 0 after 10 cycles without edge
 * 3: Force to 0 after 5 cycles without edge
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG . SIGDET_CFG
 */
#define  VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SIGDET_CFG(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SIGDET_CFG     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SIGDET_CFG(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/** 
 * \brief
 * Link hysteresis timer test mode. When enabled, [linkhysttimer] steps are
 * reduced from 65536 ns to 2048 ns.
 *
 * \details 
 * 1: Enable test mode
 * 0: Disable test mode
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG . LINKHYST_TM_ENA
 */
#define  VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_LINKHYST_TM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_LINKHYST_TM_ENA  VTSS_BIT(8)
#define  VTSS_X_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_LINKHYST_TM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Link hysteresis timer configuration. The hysteresis time lasts
 * [linkhysttimer] * 65536 ns + 2320 ns. If linkhysttime is set to 5, the
 * hysteresis lasts the minimum time of 330 us as specified in IEEE 802.3 -
 * 24.3.3.4.
 *
 * \details 
 * Field: ::VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG . LINKHYSTTIMER
 */
#define  VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_LINKHYSTTIMER(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_LINKHYSTTIMER     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_LINKHYSTTIMER(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Unidirectional mode enable. Implementation 0f 802.3 clause 66. When
 * asserted, this enables MAC to transmit data independent of the state of
 * the receive link.
 *
 * \details 
 * 0: Unidirectional mode disabled
 * 1: Unidirectional mode enabled
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG . UNIDIR_MODE_ENA
 */
#define  VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_UNIDIR_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_UNIDIR_MODE_ENA  VTSS_BIT(3)
#define  VTSS_X_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_UNIDIR_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Far-End Fault (FEF) detection enable
 *
 * \details 
 * 0: Disable FEF detection
 * 1 Enable FEF detection
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG . FEFCHK_ENA
 */
#define  VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_FEFCHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_FEFCHK_ENA  VTSS_BIT(2)
#define  VTSS_X_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_FEFCHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Far-End Fault (FEF) generation enable
 *
 * \details 
 * 0: Disable FEF generation
 * 1 Enable FEF generation
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG . FEFGEN_ENA
 */
#define  VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_FEFGEN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_FEFGEN_ENA  VTSS_BIT(1)
#define  VTSS_X_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_FEFGEN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * PCS enable
 *
 * \details 
 * 0: Disable PCS
 * 1: Enable PCS
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG . PCS_ENA
 */
#define  VTSS_F_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a DEV1G:PCS_FX100_STATUS
 *
 * PCS FX100 Status Registers
 */


/** 
 * \brief PCS 100Base FX Status
 *
 * \details
 * Status bit groups for 100Base-FX PCS. Note: If sigdet_cfg != "00" is
 * selected status signal "signal_detect" shows the internal signal_detect
 * value is gated with the status of rx toggle-rate control circuitry.
 *
 * Register: \a DEV1G:PCS_FX100_STATUS:PCS_FX100_STATUS
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS(target)  VTSS_IOREG(target,0x26)

/** 
 * \brief
 * Data change position in the 10bit words received. Must be used for
 * adjusting PTP ingress delays.
 *
 * \details 
 * Field: ::VTSS_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS . EDGE_POS_PTP
 */
#define  VTSS_F_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_EDGE_POS_PTP(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_EDGE_POS_PTP     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_EDGE_POS_PTP(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * PCS error has occurred
 *
 * \details 
 * 1: RX_ER was high while RX_DV active
 * 0: No RX_ER indication found while RX_DV active
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS . PCS_ERROR_STICKY
 */
#define  VTSS_F_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_PCS_ERROR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_PCS_ERROR_STICKY  VTSS_BIT(7)
#define  VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_PCS_ERROR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Far-end Fault state has occurred
 *
 * \details 
 * 1: A Far-End Fault has been detected
 * 0: No Far-End Fault occurred
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS . FEF_FOUND_STICKY
 */
#define  VTSS_F_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_FOUND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_FOUND_STICKY  VTSS_BIT(6)
#define  VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_FOUND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Stream Start Delimiter error occurred
 *
 * \details 
 * 1: A Start-of-Stream Delimiter error has been detected
 * 0: No SSD error occurred
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS . SSD_ERROR_STICKY
 */
#define  VTSS_F_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SSD_ERROR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SSD_ERROR_STICKY  VTSS_BIT(5)
#define  VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SSD_ERROR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Synchronization lost
 *
 * \details 
 * 1: Synchronization lost
 * 0: No sync lost occurred
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS . SYNC_LOST_STICKY
 */
#define  VTSS_F_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_LOST_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_LOST_STICKY  VTSS_BIT(4)
#define  VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_LOST_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Current status of Far-end Fault detection state
 *
 * \details 
 * 1: Link currently in fault state
 * 0: Link is in normal state
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS . FEF_STATUS
 */
#define  VTSS_F_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_STATUS  VTSS_BIT(2)
#define  VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Current status of selected signal_detect input line
 *
 * \details 
 * 1: Proper signal detected
 * 0: No proper signal found
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS . SIGNAL_DETECT
 */
#define  VTSS_F_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SIGNAL_DETECT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SIGNAL_DETECT  VTSS_BIT(1)
#define  VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SIGNAL_DETECT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Status of synchronization
 *
 * \details 
 * 1: Link established
 * 0: No link found
 *
 * Field: ::VTSS_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS . SYNC_STATUS
 */
#define  VTSS_F_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_STATUS  VTSS_BIT(0)
#define  VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a DEV1G:DEV2G5_INTR_CFG_STATUS
 *
 * Device 1G Interrupt Configuration and Status Registers
 */


/** 
 * \brief Dev1g Intr Configuration
 *
 * \details
 * Interrupt Mask (Enable) register
 *
 * Register: \a DEV1G:DEV2G5_INTR_CFG_STATUS:DEV2G5_INTR_CFG
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG(target)  VTSS_IOREG(target,0x27)

/** 
 * \brief
 * Far-end-fault indication found interrupt enable (only PCS_fx100)
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG . FEF_FOUND_INTR_ENA
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_FEF_FOUND_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_FEF_FOUND_INTR_ENA  VTSS_BIT(8)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_FEF_FOUND_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Low Power Idle Transmit interrupt enable (only PCS1g)
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG . TX_LPI_INTR_ENA
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_TX_LPI_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_TX_LPI_INTR_ENA  VTSS_BIT(6)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_TX_LPI_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Low Power Idle Receive interrupt enable (only PCS1g)
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG . RX_LPI_INTR_ENA
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_RX_LPI_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_RX_LPI_INTR_ENA  VTSS_BIT(5)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_RX_LPI_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * ANEG next page receive interrupt enable (only PCS1g)
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG . AN_PAGE_RX_INTR_ENA
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_AN_PAGE_RX_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_AN_PAGE_RX_INTR_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_AN_PAGE_RX_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * ANEG Link up interrupt enable (only PCS1g)
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG . AN_LINK_UP_INTR_ENA
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_AN_LINK_UP_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_AN_LINK_UP_INTR_ENA  VTSS_BIT(3)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_AN_LINK_UP_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * ANEG Link down interrupt enable (only PCS1g)
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG . AN_LINK_DOWN_INTR_ENA
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_AN_LINK_DOWN_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_AN_LINK_DOWN_INTR_ENA  VTSS_BIT(2)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_AN_LINK_DOWN_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Link up interrupt enable
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG . LINK_UP_INTR_ENA
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_LINK_UP_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_LINK_UP_INTR_ENA  VTSS_BIT(1)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_LINK_UP_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Link down interrupt enable
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG . LINK_DOWN_INTR_ENA
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_LINK_DOWN_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_LINK_DOWN_INTR_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_LINK_DOWN_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Dev1g Interrupt Reg
 *
 * \details
 * Interrupt register
 *
 * Register: \a DEV1G:DEV2G5_INTR_CFG_STATUS:DEV2G5_INTR
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR(target)  VTSS_IOREG(target,0x28)

/** 
 * \brief
 * Far-end-fault indication found interrupt (only PCS_fx100)
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt occured
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR . FEF_FOUND_INTR_STICKY
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_FEF_FOUND_INTR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_FEF_FOUND_INTR_STICKY  VTSS_BIT(8)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_FEF_FOUND_INTR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Low Power Idle Transmit interrupt (only PCS1g)
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt occured
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR . TX_LPI_INTR_STICKY
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_TX_LPI_INTR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_TX_LPI_INTR_STICKY  VTSS_BIT(6)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_TX_LPI_INTR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Low Power Idle Receive interrupt (only PCS1g)
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt occured
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR . RX_LPI_INTR_STICKY
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_RX_LPI_INTR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_RX_LPI_INTR_STICKY  VTSS_BIT(5)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_RX_LPI_INTR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * ANEG next page receive interrupt (only PCS1g)
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt occured
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR . AN_PAGE_RX_INTR_STICKY
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_AN_PAGE_RX_INTR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_AN_PAGE_RX_INTR_STICKY  VTSS_BIT(4)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_AN_PAGE_RX_INTR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * ANEG Link up interrupt (only PCS1g)
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt occured
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR . AN_LINK_UP_INTR_STICKY
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_AN_LINK_UP_INTR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_AN_LINK_UP_INTR_STICKY  VTSS_BIT(3)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_AN_LINK_UP_INTR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * ANEG Link down interrupt (only PCS1g)
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt occured
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR . AN_LINK_DOWN_INTR_STICKY
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_AN_LINK_DOWN_INTR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_AN_LINK_DOWN_INTR_STICKY  VTSS_BIT(2)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_AN_LINK_DOWN_INTR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Link up interrupt
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt occured
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR . LINK_UP_INTR_STICKY
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_LINK_UP_INTR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_LINK_UP_INTR_STICKY  VTSS_BIT(1)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_LINK_UP_INTR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Link down interrupt
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt occured
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR . LINK_DOWN_INTR_STICKY
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_LINK_DOWN_INTR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_LINK_DOWN_INTR_STICKY  VTSS_BIT(0)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_LINK_DOWN_INTR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Dev1g Interrupt Ident
 *
 * \details
 * Pending Interrupts (only enabled interrupts are visible)
 *
 * Register: \a DEV1G:DEV2G5_INTR_CFG_STATUS:DEV2G5_INTR_IDENT
 *
 * @param target A \a ::vtss_target_DEV1G_e target
 */
#define VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT(target)  VTSS_IOREG(target,0x29)

/** 
 * \brief
 * Far-end-fault indication found interrupt (only PCS_fx100)
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt pending
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT . FEF_FOUND_INTR_IDENT
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_FEF_FOUND_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_FEF_FOUND_INTR_IDENT  VTSS_BIT(8)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_FEF_FOUND_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Low Power Idle Transmit interrupt (only PCS1g)
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt pending
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT . TX_LPI_INTR_IDENT
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_TX_LPI_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_TX_LPI_INTR_IDENT  VTSS_BIT(6)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_TX_LPI_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Low Power Idle Receive interrupt (only PCS1g)
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt pending
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT . RX_LPI_INTR_IDENT
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_RX_LPI_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_RX_LPI_INTR_IDENT  VTSS_BIT(5)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_RX_LPI_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * ANEG next page receive interrupt (only PCS1g)
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt pending
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT . AN_PAGE_RX_INTR_IDENT
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_AN_PAGE_RX_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_AN_PAGE_RX_INTR_IDENT  VTSS_BIT(4)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_AN_PAGE_RX_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * ANEG Link up interrupt (only PCS1g)
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt pending
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT . AN_LINK_UP_INTR_IDENT
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_AN_LINK_UP_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_AN_LINK_UP_INTR_IDENT  VTSS_BIT(3)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_AN_LINK_UP_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * ANEG Link down interrupt (only PCS1g)
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt pending
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT . AN_LINK_DOWN_INTR_IDENT
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_AN_LINK_DOWN_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_AN_LINK_DOWN_INTR_IDENT  VTSS_BIT(2)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_AN_LINK_DOWN_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Link up interrupt
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt pending
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT . LINK_UP_INTR_IDENT
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_LINK_UP_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_LINK_UP_INTR_IDENT  VTSS_BIT(1)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_LINK_UP_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Link down interrupt
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt pending
 *
 * Field: ::VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT . LINK_DOWN_INTR_IDENT
 */
#define  VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_LINK_DOWN_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_LINK_DOWN_INTR_IDENT  VTSS_BIT(0)
#define  VTSS_X_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_IDENT_LINK_DOWN_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_SERVALT_REGS_DEV1G_H_ */
