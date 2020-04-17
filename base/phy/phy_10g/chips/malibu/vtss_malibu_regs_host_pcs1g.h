// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_HOST_PCS1G_H_
#define _VTSS_MALIBU_REGS_HOST_PCS1G_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a HOST_PCS1G
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a HOST_PCS1G:PCS1G_CFG_STATUS
 *
 * PCS 1G Configuration Status Registers
 */


/** 
 * \brief PCS1G Configuration
 *
 * \details
 * PCS1G main configuration register
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_CFG
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_CFG  VTSS_IOREG(0x03, 0, 0xe000)

/** 
 * \brief
 * Set type of link_status indication at CPU-System
 *
 * \details 
 * 0: Sync_status (from PCS synchronization state machine)
 * 1: Bit 15 of PCS1G_ANEG_STATUS.lp_adv_ability (Link up/down)
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_CFG . LINK_STATUS_TYPE
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_CFG_LINK_STATUS_TYPE  VTSS_BIT(4)

/** 
 * \brief
 * PCS enable
 *
 * \details 
 * 0: Disable PCS
 * 1: Enable PCS
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_CFG . PCS_ENA
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA  VTSS_BIT(0)


/** 
 * \brief PCS1G Mode Configuration
 *
 * \details
 * PCS1G mode configuration
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_MODE_CFG
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG  VTSS_IOREG(0x03, 0, 0xe001)

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
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG . UNIDIR_MODE_ENA
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG_UNIDIR_MODE_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Selection of PCS operation
 *
 * \details 
 * 0: PCS is used in SERDES mode
 * 1: PCS is used in SGMII mode. Configuration bit
 * PCS1G_ANEG_CFG.SW_RESOLVE_ENA must be set additionally
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG . SGMII_MODE_ENA
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_MODE_CFG_SGMII_MODE_ENA  VTSS_BIT(0)


/** 
 * \brief PCS1G Signal Detect Configuration
 *
 * \details
 * PCS1G signal_detect configuration
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_SD_CFG
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG  VTSS_IOREG(0x03, 0, 0xe002)

/** 
 * \brief
 * Signal detect selection (select input for internal signal_detect line)
 *
 * \details 
 * 0: Select signal_detect line from hardmacro
 * 1: Select external signal_detect line
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG . SD_SEL
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_SEL  VTSS_BIT(8)

/** 
 * \brief
 * Signal detect polarity: The signal level on signal_detect input pin must
 * be equal to SD_POL to indicate signal detection (SD_ENA must be set)
 *
 * \details 
 * 0: Signal Detect input pin must be '0' to indicate a signal detection
 * 1: Signal Detect input pin must be '1' to indicate a signal detection
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG . SD_POL
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_POL  VTSS_BIT(4)

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
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG . SD_ENA
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA  VTSS_BIT(0)


/** 
 * \brief PCS1G Aneg Configuration
 *
 * \details
 * PCS1G Auto-negotiation configuration register
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_ANEG_CFG
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG  VTSS_IOREG(0x03, 0, 0xe003)

/** 
 * \brief
 * Software Resolve Abilities
 *
 * \details 
 * 0: If Auto Negotiation fails (no matching HD or FD capabilities) the
 * link is disabled
 * 1: The result of an Auto Negotiation is ignored - the link can be setup
 * via software. This bit must be set in SGMII mode.
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG . SW_RESOLVE_ENA
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_SW_RESOLVE_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Auto Negotiation Restart
 *
 * \details 
 * 0: No action
 * 1: Restart Auto Negotiation
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG . ANEG_RESTART_ONE_SHOT
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT  VTSS_BIT(1)

/** 
 * \brief
 * Auto Negotiation Enable
 *
 * \details 
 * 0: Auto Negotiation Disabled
 * 1: Auto Negotiation Enabled
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG . ANEG_ENA
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA  VTSS_BIT(0)


/** 
 * \brief PCS1G Aneg Configuration
 *
 * \details
 * PCS1G Auto-negotiation configuration register
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_ANEG_CFG2
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG2  VTSS_IOREG(0x03, 0, 0xe004)

/** 
 * \brief
 * Advertised Ability Register: Holds the capabilities of the device as
 * described IEEE 802.3, Clause 37. If SGMII mode is selected
 * (PCS1G_MODE_CFG.SGMII_MODE_ENA = 1), SW_RESOLVE_ENA must be set.
 *
 * \details 
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG2 . ADV_ABILITY
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG2_ADV_ABILITY(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG2_ADV_ABILITY     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG2_ADV_ABILITY(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS1G Aneg Next Page Configuration
 *
 * \details
 * PCS1G Auto-negotiation configuration register for next-page function
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_ANEG_NP_CFG
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG  VTSS_IOREG(0x03, 0, 0xe005)

/** 
 * \brief
 * Next page loaded
 *
 * \details 
 * 0: next page is free and can be loaded
 * 1: next page register has been filled (to be set after np_tx has been
 * filled)
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG . NP_LOADED_ONE_SHOT
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG_NP_LOADED_ONE_SHOT  VTSS_BIT(0)


/** 
 * \brief PCS1G Aneg Next Page Configuration
 *
 * \details
 * PCS1G Auto-negotiation configuration register for next-page function
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_ANEG_NP_CFG2
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG2  VTSS_IOREG(0x03, 0, 0xe006)

/** 
 * \brief
 * Next page register: Holds the next-page information as described in IEEE
 * 802.3, Clause 37
 *
 * \details 
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG2 . NP_TX
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG2_NP_TX(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG2_NP_TX     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_CFG2_NP_TX(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS1G Loopback Configuration
 *
 * \details
 * PCS1G Loop-Back configuration register
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_LB_CFG
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG  VTSS_IOREG(0x03, 0, 0xe007)

/** 
 * \brief
 * Loops data in PCS (TBI side) from egress direction to ingress direction.
 * The Rx clock is automatically set equal to the Tx clock
 *
 * \details 
 * 0: TBI Loopback Disabled
 * 1:TBI Loopback Enabled
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG . TBI_HOST_LB_ENA
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LB_CFG_TBI_HOST_LB_ENA  VTSS_BIT(0)


/** 
 * \brief PCS1G Debug Configuration
 *
 * \details
 * PCS1G Debug configuration register
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_DBG_CFG
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_DBG_CFG  VTSS_IOREG(0x03, 0, 0xe008)


/** 
 * \brief PCS1G comma detection Configuration
 *
 * \details
 * PCS1G comma detection configuration
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_CDET_CFG
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_CDET_CFG  VTSS_IOREG(0x03, 0, 0xe009)

/** 
 * \brief
 * Enable comma detection and code-group alignment
 *
 * \details 
 * 0: Comma detection disabled
 * 1: Comma detection enabled
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_CDET_CFG . CDET_ENA
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_CDET_CFG_CDET_ENA  VTSS_BIT(0)


/** 
 * \brief PCS1G ANEG Status Register
 *
 * \details
 * PCS1G Auto-negotiation status register
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_ANEG_STATUS
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS  VTSS_IOREG(0x03, 0, 0xe00a)

/** 
 * \brief
 * Resolve priority
 *
 * \details 
 * 0: ANEG is in progress
 * 1: ANEG nearly finished - priority can be resolved (via software)
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS . PR
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_PR  VTSS_BIT(4)

/** 
 * \brief
 * Status indicating whether a new page has been received.
 *
 * \details 
 * 0: No new page received
 * 1: New page received
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS . PAGE_RX_STICKY
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_PAGE_RX_STICKY  VTSS_BIT(3)

/** 
 * \brief
 * Auto Negotiation Complete
 *
 * \details 
 * 0: No Auto Negotiation has been completed
 * 1: Indicates that an Auto Negotiation has completed successfully
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS . ANEG_COMPLETE
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_ANEG_COMPLETE  VTSS_BIT(0)


/** 
 * \brief PCS1G ANEG Status Register
 *
 * \details
 * PCS1G Auto-negotiation status register
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_ANEG_STATUS2
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS2  VTSS_IOREG(0x03, 0, 0xe00b)

/** 
 * \brief
 * Advertised abilities from link partner as described in IEEE 802.3,
 * Clause 37
 *
 * \details 
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS2 . LP_ADV_ABILITY
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS2_LP_ADV_ABILITY(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS2_LP_ADV_ABILITY     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS2_LP_ADV_ABILITY(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS1G Aneg Next Page Status Register
 *
 * \details
 * PCS1G Auto-negotiation next page status register
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_ANEG_NP_STATUS
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_STATUS  VTSS_IOREG(0x03, 0, 0xe00c)

/** 
 * \brief
 * Next page ability register from link partner as described in IEEE 802.3,
 * Clause 37
 *
 * \details 
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_STATUS . LP_NP_RX
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_STATUS_LP_NP_RX(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_STATUS_LP_NP_RX     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_ANEG_NP_STATUS_LP_NP_RX(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS1G link status
 *
 * \details
 * PCS1G link status register
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_LINK_STATUS
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS  VTSS_IOREG(0x03, 0, 0xe00d)

/** 
 * \brief
 * Indicates whether or not the selected Signal Detect input line is
 * asserted
 *
 * \details 
 * 0: No signal detected
 * 1: Signal detected
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS . SIGNAL_DETECT
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SIGNAL_DETECT  VTSS_BIT(8)

/** 
 * \brief
 * Indicates whether the link is up or down. A link is up when ANEG state
 * machine is in state LINK_OK or AN_DISABLE_LINK_OK
 *
 * \details 
 * 0: Link down
 * 1: Link up
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS . LINK_STATUS
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_LINK_STATUS  VTSS_BIT(4)

/** 
 * \brief
 * Indicates if PCS has successfully synchronized
 *
 * \details 
 * 0: PCS is out of sync
 * 1: PCS has synchronized
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS . SYNC_STATUS
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SYNC_STATUS  VTSS_BIT(0)


/** 
 * \brief PCS1G link down counter
 *
 * \details
 * PCS1G link down counter register
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_LINK_DOWN_CNT
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LINK_DOWN_CNT  VTSS_IOREG(0x03, 0, 0xe00e)

/** 
 * \brief
 * Link Down Counter. A counter that counts the number of times a link has
 * been down. The counter does not saturate at 255 and is only cleared when
 * writing 0 to the register
 *
 * \details 
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LINK_DOWN_CNT . LINK_DOWN_CNT
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LINK_DOWN_CNT_LINK_DOWN_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LINK_DOWN_CNT_LINK_DOWN_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LINK_DOWN_CNT_LINK_DOWN_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief PCS1G sticky register
 *
 * \details
 * PCS1G status register for sticky bits
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_STICKY
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_STICKY  VTSS_IOREG(0x03, 0, 0xe00f)

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
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_STICKY . LINK_DOWN_STICKY
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY  VTSS_BIT(4)

/** 
 * \brief
 * Sticky bit indicating if PCS synchronization has been lost
 *
 * \details 
 * 0: Synchronization has not been lost at any time
 * 1: Synchronization has been lost for one or more clock cycles
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_STICKY . OUT_OF_SYNC_STICKY
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_STICKY_OUT_OF_SYNC_STICKY  VTSS_BIT(0)


/** 
 * \brief PCS1G debug status
 *
 * \details
 * PCS1G debug status register
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_DEBUG_STATUS
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_DEBUG_STATUS  VTSS_IOREG(0x03, 0, 0xe010)

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
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_DEBUG_STATUS . XMIT_MODE
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_DEBUG_STATUS_XMIT_MODE(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_DEBUG_STATUS_XMIT_MODE     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_DEBUG_STATUS_XMIT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,12,2)


/** 
 * \brief PCS1G Low Power Idle Configuration
 *
 * \details
 * Configuration register for Low Power Idle (Energy Efficient Ethernet)
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_LPI_CFG
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG  VTSS_IOREG(0x03, 0, 0xe011)

/** 
 * \brief
 * Max wake-up time before link_fail
 *
 * \details 
 * 00: 10 us
 * 01: 13 us
 * 10: 17 us
 * 11: 20 us
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG . LPI_RX_WTIM
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_LPI_RX_WTIM(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_LPI_RX_WTIM     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_LPI_RX_WTIM(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Assert Low-Power Idle (LPI) in transmit mode
 *
 * \details 
 * 0: Disable LPI transmission
 * 1: Enable LPI transmission
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG . TX_ASSERT_LPIDLE
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG_TX_ASSERT_LPIDLE  VTSS_BIT(0)


/** 
 * \brief PCS1G Low Power Idle Configuration
 *
 * \details
 * Configuration register for Low Power Idle (Energy Efficient Ethernet)
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_LPI_CFG2
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG2  VTSS_IOREG(0x03, 0, 0xe012)

/** 
 * \brief
 * QSGMII master/slave selection (only one master allowed per QSGMII). The
 * master drives LPI timing on serdes
 *
 * \details 
 * 0: Slave
 * 1: Master
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG2 . QSGMII_MS_SEL
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_CFG2_QSGMII_MS_SEL  VTSS_BIT(4)


/** 
 * \brief PCS1G wake error counter
 *
 * \details
 * PCS1G Low Power Idle wake error counter (Energy Efficient Ethernet)
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_LPI_WAKE_ERROR_CNT
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_WAKE_ERROR_CNT  VTSS_IOREG(0x03, 0, 0xe013)

/** 
 * \brief
 * Wake Error Counter. A counter that is incremented when the link partner
 * does not send wake-up burst in due time. The counter saturates at 65535
 * and is cleared when writing 0 to the register
 *
 * \details 
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_WAKE_ERROR_CNT . WAKE_ERROR_CNT
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_WAKE_ERROR_CNT_WAKE_ERROR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_WAKE_ERROR_CNT_WAKE_ERROR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_WAKE_ERROR_CNT_WAKE_ERROR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS1G Low Power Idle Status
 *
 * \details
 * Status register for Low Power Idle (Energy Efficient Ethernet)
 *
 * Register: \a HOST_PCS1G:PCS1G_CFG_STATUS:PCS1G_LPI_STATUS
 */
#define VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS  VTSS_IOREG(0x03, 0, 0xe014)

/** 
 * \brief
 * Receiver has failed to recover from Low-Power Idle mode
 *
 * \details 
 * 0: No failure
 * 1: Failed to recover from LPI mode
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS . RX_LPI_FAIL
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_RX_LPI_FAIL  VTSS_BIT(15)

/** 
 * \brief
 * Receiver Low-Power idle occurrence
 *
 * \details 
 * 0: No LPI symbols received
 * 1: Receiver has received LPI symbols
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS . RX_LPI_EVENT_STICKY
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_RX_LPI_EVENT_STICKY  VTSS_BIT(12)

/** 
 * \brief
 * Receiver Low-Power Quiet mode
 *
 * \details 
 * 0: Receiver not in quiet mode
 * 1: Receiver is in quiet mode
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS . RX_QUIET
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_RX_QUIET  VTSS_BIT(9)

/** 
 * \brief
 * Receiver Low-Power Idle mode
 *
 * \details 
 * 0: Receiver not in low power idle mode
 * 1: Receiver is in low power idle mode
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS . RX_LPI_MODE
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_RX_LPI_MODE  VTSS_BIT(8)

/** 
 * \brief
 * Transmitter Low-Power idle occurrence
 *
 * \details 
 * 0: No LPI symbols transmitted
 * 1: Transmitter has transmitted LPI symbols
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS . TX_LPI_EVENT_STICKY
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_TX_LPI_EVENT_STICKY  VTSS_BIT(4)

/** 
 * \brief
 * Transmitter Low-Power Quiet mode
 *
 * \details 
 * 0: Transmitter not in quiet mode
 * 1: Transmitter is in quiet mode
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS . TX_QUIET
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_TX_QUIET  VTSS_BIT(1)

/** 
 * \brief
 * Transmitter Low-Power Idle mode
 *
 * \details 
 * 0: Transmitter not in low power idle mode
 * 1: Transmitter is in low power idle mode
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS . TX_LPI_MODE
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_CFG_STATUS_PCS1G_LPI_STATUS_TX_LPI_MODE  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS1G:PCS1G_TSTPAT_CFG_STATUS
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
 * Register: \a HOST_PCS1G:PCS1G_TSTPAT_CFG_STATUS:PCS1G_TSTPAT_MODE_CFG
 */
#define VTSS_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_MODE_CFG  VTSS_IOREG(0x03, 0, 0xe015)

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
 * Field: VTSS_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_MODE_CFG . JTP_SEL
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_MODE_CFG_JTP_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_MODE_CFG_JTP_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_MODE_CFG_JTP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief PCS1G TSTPAT STATUS
 *
 * \details
 * PCS1G testpattern status register
 *
 * Register: \a HOST_PCS1G:PCS1G_TSTPAT_CFG_STATUS:PCS1G_TSTPAT_STATUS
 */
#define VTSS_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS  VTSS_IOREG(0x03, 0, 0xe016)

/** 
 * \brief
 * Jitter Test Pattern Error Counter. Due to re-sync measures it might
 * happen that single errors are not counted (applies for 2.5gpbs mode).
 * The counter saturates at 255 and is only cleared when writing 0 to the
 * register
 *
 * \details 
 * Field: VTSS_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS . JTP_ERR_CNT
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_ERR_CNT     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Jitter Test Pattern Error
 *
 * \details 
 * 0: Jitter pattern checker has found no error
 * 1: Jitter pattern checker has found an error
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS . JTP_ERR
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_ERR  VTSS_BIT(4)

/** 
 * \brief
 * Jitter Test Pattern Lock
 *
 * \details 
 * 0: Jitter pattern checker has not locked
 * 1: Jitter pattern checker has locked
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS . JTP_LOCK
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_TSTPAT_CFG_STATUS_PCS1G_TSTPAT_STATUS_JTP_LOCK  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS1G:PCS1G_XGMII_CFG_STATUS
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a HOST_PCS1G:PCS1G_XGMII_CFG_STATUS:PCS1G_XGMII_CFG
 */
#define VTSS_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_CFG  VTSS_IOREG(0x03, 0, 0xe017)

/** 
 * \brief
 * Enable the PCS to regenerate the full preamble when a reduced preamble
 * is detected on the received packet
 *
 * \details 
 * 0=Preamble is not modified
 * 1=Preceeding IDLEs are replaced preamble bytes for the 7 bytes before a
 * start of frame delimiter
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_CFG . REGEN_PREAMBLE_ENA
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_CFG_REGEN_PREAMBLE_ENA  VTSS_BIT(0)


/** 
 * \details
 * Register: \a HOST_PCS1G:PCS1G_XGMII_CFG_STATUS:PCS1G_XGMII_MASK
 */
#define VTSS_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_MASK  VTSS_IOREG(0x03, 0, 0xe018)

/** 
 * \brief
 * Interrupt mask for LINK_DOWN
 *
 * \details 
 * 0=Interrupt disabled
 * 1=Interrupt enabled
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_MASK . LINK_DOWN_MASK
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_MASK_LINK_DOWN_MASK  VTSS_BIT(9)

/** 
 * \brief
 * Interrupt mask for OUT_OF_SYNC_STICKY
 *
 * \details 
 * 0=Interrupt disabled
 * 1=Interrupt enabled
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_MASK . OUT_OF_SYNC_MASK
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_MASK_OUT_OF_SYNC_MASK  VTSS_BIT(8)

/** 
 * \brief
 * Interrupt mask for RX rate adaptation FIFO underflow
 *
 * \details 
 * 0=Interrupt disabled
 * 1=Interrupt enabled
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_MASK . RX_FIFO_UNDERFLOW_MASK
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_MASK_RX_FIFO_UNDERFLOW_MASK  VTSS_BIT(5)

/** 
 * \brief
 * Interrupt mask for Rx rate adaptation FIFO overflow
 *
 * \details 
 * 0=Interrupt disabled
 * 1=Interrupt enabled
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_MASK . RX_FIFO_OVERFLOW_MASK
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_MASK_RX_FIFO_OVERFLOW_MASK  VTSS_BIT(4)


/** 
 * \details
 * Register: \a HOST_PCS1G:PCS1G_XGMII_CFG_STATUS:PCS1G_XGMII_STATUS
 */
#define VTSS_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_STATUS  VTSS_IOREG(0x03, 0, 0xe019)

/** 
 * \brief
 * A FIFO Underflow condition has been detected on the RX Rate Adaptation
 * FIFO
 *
 * \details 
 * 0=No underflow detected
 * 1=Underflow detected
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_STATUS . RX_FIFO_UNDERFLOW_STICKY
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_STATUS_RX_FIFO_UNDERFLOW_STICKY  VTSS_BIT(5)

/** 
 * \brief
 * A FIFO Overflow condition has been detected on the RX Rate-adaptation
 * FIFO
 *
 * \details 
 * 0=No Overflow detected
 * 1=Overflow detected
 *
 * Field: VTSS_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_STATUS . RX_FIFO_OVERFLOW_STICKY
 */
#define  VTSS_F_HOST_PCS1G_PCS1G_XGMII_CFG_STATUS_PCS1G_XGMII_STATUS_RX_FIFO_OVERFLOW_STICKY  VTSS_BIT(4)


#endif /* _VTSS_MALIBU_REGS_HOST_PCS1G_H_ */
