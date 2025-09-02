// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN80XX_MALIBU25G_REGS_HOST_PCS_CFG_H_
#define LAN80XX_MALIBU25G_REGS_HOST_PCS_CFG_H_

#include "regs_lan80xx_common.h"

/***********************************************************************
 *
 * Target: \a HOST_PCS_CFG
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a HOST_PCS_CFG:PCS1G_CFG_STATUS
 *
 * PCS 1G Configuration Status Registers
 */


/**
 * \brief PCS1G Configuration
 *
 * \details
 * PCS1G main configuration register
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_CFG
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_CFG                                                              (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe002))

/**
 * \brief
 * Set type of link_status indication at CPU-System. Malibu-25G only
 * support LINK_STATUS_TYPE 0
 *
 * \details
 * 0: Sync_status (from PCS synchronization state machine)
 * 1: Bit 15 of PCS1G_ANEG_STATUS.lp_adv_ability (Link up/down)
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_CFG . LINK_STATUS_TYPE
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_CFG_LINK_STATUS_TYPE(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_CFG_LINK_STATUS_TYPE                                          (LAN80XX_BIT(4))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_CFG_LINK_STATUS_TYPE(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Enable Link control using Backplane Ethernet ANEG. Not in use
 *
 * \details
 * 0: Disable link control
 * 1: Enable link control
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_CFG . AN_LINK_CTRL_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_CFG_AN_LINK_CTRL_ENA(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_CFG_AN_LINK_CTRL_ENA                                          (LAN80XX_BIT(1))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_CFG_AN_LINK_CTRL_ENA(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * PCS enable
 *
 * \details
 * 0: Disable PCS
 * 1: Enable PCS
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_CFG . PCS_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_CFG_PCS_ENA(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_CFG_PCS_ENA                                                   (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_CFG_PCS_ENA(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief PCS1G Mode Configuration
 *
 * \details
 * PCS1G mode configuration
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_MODE_CFG
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_MODE_CFG                                                         (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe003))

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
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_MODE_CFG . UNIDIR_MODE_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_MODE_CFG_UNIDIR_MODE_ENA(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_MODE_CFG_UNIDIR_MODE_ENA                                      (LAN80XX_BIT(4))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_MODE_CFG_UNIDIR_MODE_ENA(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Save preamble. Preamble is fully transmitted and not shorted due to IDLE
 * sequencing
 *
 * \details
 * 0: Disable
 * 1: Enable
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_MODE_CFG . SAVE_PREAMBLE_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_MODE_CFG_SAVE_PREAMBLE_ENA(x)                                 (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_MODE_CFG_SAVE_PREAMBLE_ENA                                    (LAN80XX_BIT(1))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_MODE_CFG_SAVE_PREAMBLE_ENA(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Selection of PCS operation. Debug Purpose
 *
 * \details
 * 0: PCS is used in SERDES mode
 * 1: PCS is used in SGMII mode
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_MODE_CFG . SGMII_MODE_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_MODE_CFG_SGMII_MODE_ENA(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_MODE_CFG_SGMII_MODE_ENA                                       (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_MODE_CFG_SGMII_MODE_ENA(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief PCS1G Signal Detect Configuration
 *
 * \details
 * PCS1G signal_detect configuration
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_SD_CFG
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_SD_CFG                                                           (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe004))

/**
 * \brief
 * Signal detect selection (select input for internal signal_detect line)
 *
 * \details
 * 0: Select signal_detect line from hardmacro
 * 1: Select external signal_detect line
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_SD_CFG . SD_SEL
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_SD_CFG_SD_SEL(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_SD_CFG_SD_SEL                                                 (LAN80XX_BIT(8))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_SD_CFG_SD_SEL(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Signal detect polarity: The signal level on signal_detect input pin must
 * be equal to SD_POL to indicate signal detection (SD_ENA must be set)
 *
 * \details
 * 0: Signal Detect input pin must be '0' to indicate a signal detection
 * 1: Signal Detect input pin must be '1' to indicate a signal detection
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_SD_CFG . SD_POL
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_SD_CFG_SD_POL(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_SD_CFG_SD_POL                                                 (LAN80XX_BIT(4))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_SD_CFG_SD_POL(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,4,1))

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
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_SD_CFG . SD_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_SD_CFG_SD_ENA(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_SD_CFG_SD_ENA                                                 (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_SD_CFG_SD_ENA(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief PCS1G Aneg Configuration
 *
 * \details
 * PCS1G Auto-negotiation configuration register
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_ANEG_CFG_0
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_CFG_0                                                       (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe005))
/**
 * \brief
 * Software Resolve Abilities
 *
 * \details
 * 0: If Auto Negotiation fails (no matching HD or FD capabilities) the
 * link is disabled.
 * 1: The result of an Auto Negotiation is ignored - the link can be setup
 * through software.
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_CFG_0 . SW_RESOLVE_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_SW_RESOLVE_ENA(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_SW_RESOLVE_ENA                                     (LAN80XX_BIT(8))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_SW_RESOLVE_ENA(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,8,1))
/**
 * \brief
 * Auto Negotiation Restart
 *
 * \details
 * 0: No action
 * 1: Restart Auto Negotiation
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_CFG_0 . ANEG_RESTART_ONE_SHOT
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_RESTART_ONE_SHOT(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_RESTART_ONE_SHOT                              (LAN80XX_BIT(1))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_RESTART_ONE_SHOT(x)                           (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Auto Negotiation Enable
 *
 * \details
 * 0: Auto Negotiation Disabled
 * 1: Auto Negotiation Enabled
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_CFG_0 . ANEG_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_ENA(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_ENA                                           (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_ENA(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief PCS1G Aneg Configuration
 *
 * \details
 * PCS1G Auto-negotiation configuration register
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_ANEG_CFG_1
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_CFG_1                                                       (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0, 0xe006))
/**
 * \brief
 * Advertised Ability Register: Holds the capabilities of the device as
 * described IEEE 802.3, Clause 37.
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_CFG_1 . ADV_ABILITY
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_CFG_1_ADV_ABILITY(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_CFG_1_ADV_ABILITY                                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_ANEG_CFG_1_ADV_ABILITY(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * \brief PCS1G Aneg Next Page Configuration
 *
 * \details
 * PCS1G Auto-negotiation configuration register for next-page function
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_ANEG_NP_CFG_0
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_0                                                    (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe007))

/**
 * \brief
 * Next page loaded
 *
 * \details
 * 0: Next page is free and can be loaded
 * 1: Next page register has been filled (to be set after np_tx has been
 * filled)
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_0 . NP_LOADED_ONE_SHOT
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_0_NP_LOADED_ONE_SHOT(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_0_NP_LOADED_ONE_SHOT                              (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_0_NP_LOADED_ONE_SHOT(x)                           (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief PCS1G Aneg Next Page Configuration
 *
 * \details
 * PCS1G Auto-negotiation configuration register for next-page function
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_ANEG_NP_CFG_1
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_1                                                    (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe008))

/**
 * \brief
 * Next page register: Holds the next-page information as described in IEEE
 * 802.3, Clause 37
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_1 . NP_TX
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_1_NP_TX(x)                                        (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_1_NP_TX                                           (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_1_NP_TX(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief DBG: PCS1G Loopback Configuration.
 *
 * \details
 * DBG: PCS1G loopback configuration register.
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_LB_CFG
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_LB_CFG                                                           (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe009))

/**
 * \brief
 * Enable rate adaptation capability in PCS receive direction explicitely
 *
 * \details
 * 0: Disable
 * 1: Enable
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LB_CFG . RA_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LB_CFG_RA_ENA(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LB_CFG_RA_ENA                                                 (LAN80XX_BIT(4))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LB_CFG_RA_ENA(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Loops data in PCS (GMII side) from ingress direction to egress
 * direction. Rate adaptation is automatically performed in a FIFO within
 * the PCS
 *
 * \details
 * 0: GMII Loopback Disabled
 * 1: GMII Loopback Enabled
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LB_CFG . GMII_PHY_LB_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LB_CFG_GMII_PHY_LB_ENA(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LB_CFG_GMII_PHY_LB_ENA                                        (LAN80XX_BIT(1))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LB_CFG_GMII_PHY_LB_ENA(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Loops data in PCS (TBI side) from egress direction to ingress direction.
 * The Rx clock is automatically set equal to the Tx clock
 *
 * \details
 * 0: TBI Loopback Disabled
 * 1: TBI Loopback Enabled
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LB_CFG . TBI_HOST_LB_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LB_CFG_TBI_HOST_LB_ENA(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LB_CFG_TBI_HOST_LB_ENA                                        (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LB_CFG_TBI_HOST_LB_ENA(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief PCS1G Debug Configuration
 *
 * \details
 * PCS1G Debug configuration register
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_DBG_CFG
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_DBG_CFG                                                          (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe00a))

/**
 * \brief
 * Use Debug Link Timer
 *
 * \details
 * 0: Normal 10 ms timer is selected
 * 1: Reduced 9.77 us timer is selected
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_DBG_CFG . UDLT
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_DBG_CFG_UDLT(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_DBG_CFG_UDLT                                                  (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_DBG_CFG_UDLT(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief PCS1G comma detection Configuration
 *
 * \details
 * PCS1G comma detection configuration
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_CDET_CFG
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_CDET_CFG                                                         (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe00b))

/**
 * \brief
 * Enable comma detection and code-group alignment. Not in use
 *
 * \details
 * 0: Comma detection disabled
 * 1: Comma detection enabled
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_CDET_CFG . CDET_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_CDET_CFG_CDET_ENA(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_CDET_CFG_CDET_ENA                                             (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_CDET_CFG_CDET_ENA(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief PCS1G ANEG Status Register
 *
 * \details
 * PCS1G Auto-negotiation status register
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_ANEG_STATUS_0
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_STATUS_0                                                    (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe00c))

/**
 * \brief
 * Resolve priority
 *
 * \details
 * 0: ANEG is in progress
 * 1: ANEG nearly finished - priority can be resolved (through software)
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_STATUS_0 . PR
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_STATUS_0_PR(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_STATUS_0_PR                                              (LAN80XX_BIT(4))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_ANEG_STATUS_0_PR(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Status indicating whether a new page has been received.
 *
 * \details
 * 0: No new page received
 * 1: New page received
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_STATUS_0 . PAGE_RX_STICKY
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_STATUS_0_PAGE_RX_STICKY(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_STATUS_0_PAGE_RX_STICKY                                  (LAN80XX_BIT(3))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_ANEG_STATUS_0_PAGE_RX_STICKY(x)                               (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Auto Negotiation Complete
 *
 * \details
 * 0: No Auto Negotiation has been completed
 * 1: Indicates that an Auto Negotiation has completed successfully
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_STATUS_0 . ANEG_COMPLETE
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_STATUS_0_ANEG_COMPLETE(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_STATUS_0_ANEG_COMPLETE                                   (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_ANEG_STATUS_0_ANEG_COMPLETE(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief PCS1G ANEG Status Register
 *
 * \details
 * PCS1G Auto-negotiation status register
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_ANEG_STATUS_1
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_STATUS_1                                                    (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe00d))

/**
 * \brief
 * Advertised abilities from link partner as described in IEEE 802.3,
 * Clause 37
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_STATUS_1 . LP_ADV_ABILITY
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_STATUS_1_LP_ADV_ABILITY(x)                               (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_STATUS_1_LP_ADV_ABILITY                                  (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_ANEG_STATUS_1_LP_ADV_ABILITY(x)                               (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PCS1G Aneg Next Page Status Register
 *
 * \details
 * PCS1G Auto-negotiation next page status register
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_ANEG_NP_STATUS
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_NP_STATUS                                                   (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe00e))

/**
 * \brief
 * Next page ability register from link partner as described in IEEE 802.3,
 * Clause 37
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_NP_STATUS . LP_NP_RX
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_NP_STATUS_LP_NP_RX(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_NP_STATUS_LP_NP_RX                                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_ANEG_NP_STATUS_LP_NP_RX(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PCS1G link status
 *
 * \details
 * PCS1G link status register
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_LINK_STATUS
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_LINK_STATUS                                                      (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0, 0xe00f))

/**
 * \brief
 * Additional delay in rx-path; multiply the value of this field by the
 * line-rate bit-period (800ps for 10/100/1000, 320ps for 2G5 mode.) This
 * field is valid when the link is up, it remains constant for as long as
 * the link is up, value may change on link-down event.This field shows the
 * number of data bits that is stored in the rx comma-alignment block,
 * values of 0-9 is possible.
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LINK_STATUS . DELAY_VAR
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LINK_STATUS_DELAY_VAR(x)                                      (LAN80XX_ENCODE_BITFIELD(x,12,4))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LINK_STATUS_DELAY_VAR                                         (LAN80XX_ENCODE_BITMASK(12,4))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LINK_STATUS_DELAY_VAR(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,12,4))

/**
 * \brief
 * Indicates whether or not the selected Signal Detect input line is
 * asserted; does not consider the Polarity
 *
 * \details
 * 0: No signal detected
 * 1: Signal detected
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LINK_STATUS . SIGNAL_DETECT
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LINK_STATUS_SIGNAL_DETECT(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LINK_STATUS_SIGNAL_DETECT                                     (LAN80XX_BIT(8))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LINK_STATUS_SIGNAL_DETECT(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,8,1))

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
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LINK_STATUS . XMIT_MODE
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LINK_STATUS_XMIT_MODE(x)                                      (LAN80XX_ENCODE_BITFIELD(x,6,2))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LINK_STATUS_XMIT_MODE                                         (LAN80XX_ENCODE_BITMASK(6,2))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LINK_STATUS_XMIT_MODE(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,6,2))

/**
 * \brief
 * Indicates whether the link is up or down. A link is up when ANEG state
 * machine is in state LINK_OK or AN_DISABLE_LINK_OK
 *
 * \details
 * 0: Link down
 * 1: Link up
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LINK_STATUS . LINK_STATUS
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LINK_STATUS_LINK_STATUS(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LINK_STATUS_LINK_STATUS                                       (LAN80XX_BIT(4))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LINK_STATUS_LINK_STATUS(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Indicates if PCS has successfully synchronized
 *
 * \details
 * 0: PCS is out of sync
 * 1: PCS has synchronized
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LINK_STATUS . SYNC_STATUS
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LINK_STATUS_SYNC_STATUS(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LINK_STATUS_SYNC_STATUS                                       (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LINK_STATUS_SYNC_STATUS(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief PCS1G link down counter
 *
 * \details
 * PCS1G link down counter register
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_LINK_DOWN_CNT
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_LINK_DOWN_CNT                                                    (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe010))

/**
 * \brief
 * Link Down Counter. A counter that counts the number of times a link has
 * been down. The counter does not saturate at 255 and is only cleared when
 * writing 0 to the register
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LINK_DOWN_CNT . LINK_DOWN_CNT
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LINK_DOWN_CNT_LINK_DOWN_CNT(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LINK_DOWN_CNT_LINK_DOWN_CNT                                   (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LINK_DOWN_CNT_LINK_DOWN_CNT(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief PCS1G sticky bits
 *
 * \details
 * PCS1G status register for sticky bits
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_STICKY
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_STICKY                                                           (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe011))

/**
 * \brief
 * The sticky bit is set when the link has been down - i.e. if the ANEG
 * state machine has not been in the AN_DISABLE_LINK_OK or LINK_OK state
 * for one or more clock cycles. This occurs if e.g. ANEG is restarted or
 * for example if signal-detect or synchronization has been lost for more
 * than 10 ms. By setting the UDLT bit, the required down time can be
 * reduced to 9,77 us
 *
 * \details
 * 0: Link is up
 * 1: Link has been down
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_STICKY . LINK_DOWN_STICKY
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_STICKY_LINK_DOWN_STICKY(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_STICKY_LINK_DOWN_STICKY                                       (LAN80XX_BIT(1))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_STICKY_LINK_DOWN_STICKY(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Sticky bit indicating if PCS synchronization has been lost
 *
 * \details
 * 0: Synchronization has not been lost at any time
 * 1: Synchronization has been lost for one or more clock cycles
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_STICKY . OUT_OF_SYNC_STICKY
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_STICKY_OUT_OF_SYNC_STICKY(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_STICKY_OUT_OF_SYNC_STICKY                                     (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_STICKY_OUT_OF_SYNC_STICKY(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief PCS1G sticky mask
 *
 * \details
 * PCS1G sticky mask
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_STICKY_MASK
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_STICKY_MASK                                                      (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe012))

/**
 * \brief
 * Interrupt enable for link_down_sticky_intr_en
 *
 * \details
 * 0 = link_down_sticky_intr will not propagate to interrupt
 * 1 = link_down_sticky_intr will propagate to interrupt
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_STICKY_MASK . LINK_DOWN_STICKY_INTR_EN
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_STICKY_MASK_LINK_DOWN_STICKY_INTR_EN(x)                       (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_STICKY_MASK_LINK_DOWN_STICKY_INTR_EN                          (LAN80XX_BIT(5))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_STICKY_MASK_LINK_DOWN_STICKY_INTR_EN(x)                       (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Interrupt enable for out_of_sync_sticky
 *
 * \details
 * 0 = out_of_sync_sticky will not propagate to interrupt
 * 1 = out_of_sync_sticky will propagate to interrupt
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_STICKY_MASK . OUT_OF_SYNC_STICKY_INTR_EN
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_STICKY_MASK_OUT_OF_SYNC_STICKY_INTR_EN(x)                     (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_STICKY_MASK_OUT_OF_SYNC_STICKY_INTR_EN                        (LAN80XX_BIT(4))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_STICKY_MASK_OUT_OF_SYNC_STICKY_INTR_EN(x)                     (LAN80XX_EXTRACT_BITFIELD(x,4,1))


/**
 * \brief DBG: PCS1G Low Power Idle Configuration
 *
 * \details
 * DBG: Configuration register for Low Power Idle (Energy Efficient
 * Ethernet)
 *
 * Register: \a HOST_PCS_CFG:PCS1G_CFG_STATUS:PCS1G_LPI_CFG
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_LPI_CFG                                                          (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe013))

/**
 * \brief
 * QSGMII master/slave selection (only one master allowed per QSGMII). The
 * master drives LPI timing on serdes.
 *
 * \details
 * 0: Slave
 * 1: Master
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LPI_CFG . QSGMII_MS_SEL
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LPI_CFG_QSGMII_MS_SEL(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LPI_CFG_QSGMII_MS_SEL                                         (LAN80XX_BIT(15))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LPI_CFG_QSGMII_MS_SEL(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * Disable output of Low-Power Idle in receive direction (to core)
 *
 * \details
 * 0: Enable
 * 1: Disable
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LPI_CFG . RX_LPI_OUT_DIS
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LPI_CFG_RX_LPI_OUT_DIS(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LPI_CFG_RX_LPI_OUT_DIS                                        (LAN80XX_BIT(9))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LPI_CFG_RX_LPI_OUT_DIS(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * LPI-Timer test mode.
 *
 * \details
 * 0: Normal timing constants are used
 * 1: Shortened timing constants are used
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LPI_CFG . LPI_TESTMODE
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LPI_CFG_LPI_TESTMODE(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LPI_CFG_LPI_TESTMODE                                          (LAN80XX_BIT(8))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LPI_CFG_LPI_TESTMODE(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,8,1))

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
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LPI_CFG . LPI_RX_WTIM
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LPI_CFG_LPI_RX_WTIM(x)                                        (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LPI_CFG_LPI_RX_WTIM                                           (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LPI_CFG_LPI_RX_WTIM(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,4,2))

/**
 * \brief
 * Assert Low-Power Idle (LPI) in transmit mode
 *
 * \details
 * 0: Disable LPI transmission
 * 1: Enable LPI transmission
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_LPI_CFG . TX_ASSERT_LPIDLE
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_LPI_CFG_TX_ASSERT_LPIDLE(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_LPI_CFG_TX_ASSERT_LPIDLE                                      (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_LPI_CFG_TX_ASSERT_LPIDLE(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a HOST_PCS_CFG:PCS1G_TSTPAT_CFG_STATUS
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
 * Register: \a HOST_PCS_CFG:PCS1G_TSTPAT_CFG_STATUS:PCS1G_TSTPAT_MODE_CFG
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_TSTPAT_MODE_CFG                                                  (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe016))

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
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_TSTPAT_MODE_CFG . JTP_SEL
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_TSTPAT_MODE_CFG_JTP_SEL(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_TSTPAT_MODE_CFG_JTP_SEL                                       (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_TSTPAT_MODE_CFG_JTP_SEL(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,3))


/**
 * \brief PCS1G TSTPAT STATUS
 *
 * \details
 * PCS1G testpattern status register
 *
 * Register: \a HOST_PCS_CFG:PCS1G_TSTPAT_CFG_STATUS:PCS1G_TSTPAT_STATUS
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_TSTPAT_STATUS                                                    (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe017))

/**
 * \brief
 * Jitter Test Pattern Error Counter. Due to re-sync measures it might
 * happen that single errors are not counted (applies for 2.5gpbs mode).
 * The counter saturates at 255 and is only cleared when writing 0 to the
 * register
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_TSTPAT_STATUS . JTP_ERR_CNT
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_TSTPAT_STATUS_JTP_ERR_CNT(x)                                  (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_TSTPAT_STATUS_JTP_ERR_CNT                                     (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_TSTPAT_STATUS_JTP_ERR_CNT(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,8,8))

/**
 * \brief
 * Jitter Test Pattern Error
 *
 * \details
 * 0: Jitter pattern checker has found no error
 * 1: Jitter pattern checker has found an error
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_TSTPAT_STATUS . JTP_ERR
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_TSTPAT_STATUS_JTP_ERR(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_TSTPAT_STATUS_JTP_ERR                                         (LAN80XX_BIT(4))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_TSTPAT_STATUS_JTP_ERR(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Jitter Test Pattern Lock
 *
 * \details
 * 0: Jitter pattern checker has not locked
 * 1: Jitter pattern checker has locked
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_TSTPAT_STATUS . JTP_LOCK
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_TSTPAT_STATUS_JTP_LOCK(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_TSTPAT_STATUS_JTP_LOCK                                        (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_TSTPAT_STATUS_JTP_LOCK(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a HOST_PCS_CFG:PCS1G_XGMII_CFG_STATUS
 *
 * PCS1G XGMII Configuration Status Registers
 */


/**
 * \brief PCS1G_XGMII_CFG
 *
 * \details
 * PCS1G_XGMII_CFG
 *
 * Register: \a HOST_PCS_CFG:PCS1G_XGMII_CFG_STATUS:PCS1G_XGMII_CFG
 */
#define LAN80XX_HOST_PCS_CFG_PCS1G_XGMII_CFG                                                        (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe018))

/**
 * \brief
 * Enable re-alignment of START symbols to lane 0 of the internal XGMII
 * interface. This is required if the internal MAC is being used. This may
 * cause the interpacket gap to be reduced by up to 3 bytes. Not in use
 *
 * \details
 * 0=Alignment of START is disabled
 * 1=Alignment of START is enabled
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_XGMII_CFG . ALIGN_START_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_XGMII_CFG_ALIGN_START_ENA(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_XGMII_CFG_ALIGN_START_ENA                                     (LAN80XX_BIT(1))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_XGMII_CFG_ALIGN_START_ENA(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,1,1))

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
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS1G_XGMII_CFG . REGEN_PREAMBLE_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS1G_XGMII_CFG_REGEN_PREAMBLE_ENA(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS1G_XGMII_CFG_REGEN_PREAMBLE_ENA                                  (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS1G_XGMII_CFG_REGEN_PREAMBLE_ENA(x)                               (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a HOST_PCS_CFG:PCS25G_CFG_STATUS
 *
 * PCS25G Wrapper Config and Status registers
 */


/**
 * \brief PCS25G enable Configuration
 *
 * \details
 * Register: \a HOST_PCS_CFG:PCS25G_CFG_STATUS:PCS25G_CFG
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_CFG                                                             (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe019))

/**
 * \brief
 * Global PCS Enable/Disable configuration bit.
 *
 * \details
 * 0 = Disable PCS
 * 1 = Enable PCS
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_CFG . PCS25G_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_CFG_PCS25G_ENA(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_CFG_PCS25G_ENA                                               (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_CFG_PCS25G_ENA(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief PCS SignalDetect Configuration
 *
 * \details
 * PCS signal_detect configuration
 *
 * Register: \a HOST_PCS_CFG:PCS25G_CFG_STATUS:PCS25G_SD_CFG
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_SD_CFG                                                          (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe01a))

/**
 * \brief
 * Signal detect selection (select input for internal signal_detect line)
 *
 * \details
 * 0: Select signal_detect line from hardmacro
 * 1: Select external signal_detect line
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_SD_CFG . SD_SEL
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_SD_CFG_SD_SEL(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_SD_CFG_SD_SEL                                                (LAN80XX_BIT(8))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_SD_CFG_SD_SEL(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Signal detect polarity: The signal level on signal_detect input pin must
 * be equal to SD_POL to indicate signal detection (SD_ENA must be set)
 *
 * \details
 * 0: Signal Detect input pin must be '0' to indicate a signal detection
 * 1: Signal Detect input pin must be '1' to indicate a signal detection
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_SD_CFG . SD_POL
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_SD_CFG_SD_POL(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_SD_CFG_SD_POL                                                (LAN80XX_BIT(4))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_SD_CFG_SD_POL(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,4,1))

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
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_SD_CFG . SD_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_SD_CFG_SD_ENA(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_SD_CFG_SD_ENA                                                (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_SD_CFG_SD_ENA(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief Receive PCS Status
 *
 * \details
 * Register: \a HOST_PCS_CFG:PCS25G_CFG_STATUS:PCS25G_STATUS
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_STATUS                                                          (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe01b))

/**
 * \brief
 * Alignment Marker Lock indication. When asserted (1) the alignment marker
 * lock state machines could successfully lock onto detection of alignment
 * markers on all virtual lanes. The signal stays asserted as long as
 * alignment marker lock is maintained.Relevant only when MLD mode of
 * operation is active (i.e. using RS-FEC).
 *
 * \details
 * 0 - Alignment lock is achieved
 * 1 - Alignment lock is not achieved
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_STATUS . ALIGN_DONE
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_STATUS_ALIGN_DONE(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_STATUS_ALIGN_DONE                                            (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_STATUS_ALIGN_DONE(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * 66b Block synchronization indication. When asserted (1) the block
 * synchronization state machines could successfully lock onto 66-bit block
 * boundaries. The signal stays asserted as long as block lock is
 * maintained.Relevant only when MLD is not used (i.e. not using RS-FEC).
 *
 * \details
 * 0 - Block lock is achieved
 * 1 - Block lock is not achieved
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_STATUS . BLOCK_LOCK
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_STATUS_BLOCK_LOCK(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_STATUS_BLOCK_LOCK                                            (LAN80XX_BIT(1))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_STATUS_BLOCK_LOCK(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * High Bit Error Rate indication for all lanes. If asserted sync header
 * errors exceeding the allowed maximum during the measurement time (125
 * micro seconds;1.25ms) have occurred indicating a high bit error rate
 * from the line.As long as hi_ber stays asserted, local fault is signaled
 * on XGMII.hi_ber deasserts again when the bit error rate falls below the
 * limit again.
 *
 * \details
 * 0 - HI BER is not asserted.
 * 1 - HI BER is asserted.
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_STATUS . HI_BER
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_STATUS_HI_BER(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_STATUS_HI_BER                                                (LAN80XX_BIT(2))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_STATUS_HI_BER(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * Register Group: \a HOST_PCS_CFG:PCS25G_FEC74
 *
 * PCS25G FEC74 Configuration
 */


/**
 * \brief BASE-R FEC ability indication for (FEC clause 74) configuration
 *
 * \details
 * Register: \a HOST_PCS_CFG:PCS25G_FEC74:PCS25G_BASE_R_FEC_ABILITY
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_BASE_R_FEC_ABILITY                                              (LAN80XX_IOREG(MMD_ID_HOST_RSFEC, 0,0xaa))

/**
 * \brief
 * If set to 1, the sublayer supprt BASE-R FEC.
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_BASE_R_FEC_ABILITY . BASE_R_FEC_ABILITY
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_BASE_R_FEC_ABILITY_BASE_R_FEC_ABILITY(x)                     (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_BASE_R_FEC_ABILITY_BASE_R_FEC_ABILITY                        (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_BASE_R_FEC_ABILITY_BASE_R_FEC_ABILITY(x)                     (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * If set to 1, the sublayer is able to report FEC decoding error in the
 * PCS layer.
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_BASE_R_FEC_ABILITY . BASE_R_FEC_ERROR_INDICATION_ABILITY
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_BASE_R_FEC_ABILITY_BASE_R_FEC_ERROR_INDICATION_ABILITY(x)    (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_BASE_R_FEC_ABILITY_BASE_R_FEC_ERROR_INDICATION_ABILITY       (LAN80XX_BIT(1))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_BASE_R_FEC_ABILITY_BASE_R_FEC_ERROR_INDICATION_ABILITY(x)    (LAN80XX_EXTRACT_BITFIELD(x,1,1))


/**
 * \brief Forward Error correction (FEC clause 74) configuration
 *
 * \details
 * Register: \a HOST_PCS_CFG:PCS25G_FEC74:PCS25G_BASE_R_FEC_CONTROL
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL                                              (LAN80XX_IOREG(MMD_ID_HOST_RSFEC, 0,0xab))

/**
 * \brief
 * If set to 1, FEC encapsulation is enabled on the receive lane.
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL . FEC74_ENA_RX
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL_FEC74_ENA_RX(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL_FEC74_ENA_RX                              (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL_FEC74_ENA_RX(x)                           (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * If set to 1, FEC encapsulation is enabled on the transmit lane.
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL . FEC74_ENA_TX
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL_FEC74_ENA_TX(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL_FEC74_ENA_TX                              (LAN80XX_BIT(1))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL_FEC74_ENA_TX(x)                           (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * FEC module optional function to forward indication of uncorrectable
 * errors to the PCS layer by corrupting sync headers.
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL . FEC74_ERR_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL_FEC74_ERR_ENA(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL_FEC74_ERR_ENA                             (LAN80XX_BIT(2))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL_FEC74_ERR_ENA(x)                          (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * Register Group: \a HOST_PCS_CFG:PCS25G_FEC74_ERROR
 *
 * PCS25G FEC74 Corrected error and Non_Corrected error
 */


/**
 * \brief FEC74 correctable error counter (Non Roll-over)
 *
 * \details
 * Register: \a HOST_PCS_CFG:PCS25G_FEC74_ERROR:PCS25G_FEC74_CERR_CNT_L
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_FEC74_CERR_CNT_L                                                (LAN80XX_IOREG(MMD_ID_HOST_RSFEC, 0,0xac))

/**
 * \brief
 * FEC corrected error counter(Non-Rollover). The FEC could detect and
 * correct receive errors in a block. The correctable error is counted max
 * once per FEC block (32 66-bit blocks). When this register is read bits
 * 31:16 of the internal FEC74_CERR_CNT counter are latched for reading
 * from PCS25G_FEC74_CERR_CNT_H and the entire 32-bit internal
 * FEC74_CERR_CNT counter is reset
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_FEC74_CERR_CNT_L . FEC74_CERR_CNT_L
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_FEC74_CERR_CNT_L_FEC74_CERR_CNT_L(x)                         (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_FEC74_CERR_CNT_L_FEC74_CERR_CNT_L                            (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_FEC74_CERR_CNT_L_FEC74_CERR_CNT_L(x)                         (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief FEC74 correctable error counter (Non Roll-over)
 *
 * \details
 * Register: \a HOST_PCS_CFG:PCS25G_FEC74_ERROR:PCS25G_FEC74_CERR_CNT_H
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_FEC74_CERR_CNT_H                                                (LAN80XX_IOREG(MMD_ID_HOST_RSFEC, 0,0xad))

/**
 * \brief
 * FEC corrected error counter(Non-Rollover). The FEC could detect and
 * correct receive errors in a block. The correctable error is counted max
 * once per FEC block (32 66-bit blocks). When PCS25G_FEC74_CERR_CNT_L is
 * read bits 31:16 of the internal FEC74_CERR_CNT counter are latched for
 * reading from this register and entire 32-bit internal
 * FEC74_CERR_CERR_CNT counter is reset
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_FEC74_CERR_CNT_H . FEC74_CERR_CNT_H
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_FEC74_CERR_CNT_H_FEC74_CERR_CNT_H(x)                         (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_FEC74_CERR_CNT_H_FEC74_CERR_CNT_H                            (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_FEC74_CERR_CNT_H_FEC74_CERR_CNT_H(x)                         (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief FEC74 uncorrectable error counter (Non Roll-over)
 *
 * \details
 * Register: \a HOST_PCS_CFG:PCS25G_FEC74_ERROR:PCS25G_FEC74_NCERR_CNT_L
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_FEC74_NCERR_CNT_L                                               (LAN80XX_IOREG(MMD_ID_HOST_RSFEC, 0,0xae))

/**
 * \brief
 * FEC uncorrected error counter(Non-Rollover). The FEC could detect but
 * could not correct receive errors in a block. The uncorrectable error is
 * counted max once per FEC block (32 66-bit blocks). When this register is
 * read bits 31:16 of the internal FEC74_NCERR_CNT counter are latched for
 * reading from PCS25G_FEC74_NCERR_CNT_H and the entire 32-bit internal
 * FEC74_NCERR_CNT counter is reset
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_FEC74_NCERR_CNT_L . FEC74_NCERR_CNT_L
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_FEC74_NCERR_CNT_L_FEC74_NCERR_CNT_L(x)                       (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_FEC74_NCERR_CNT_L_FEC74_NCERR_CNT_L                          (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_FEC74_NCERR_CNT_L_FEC74_NCERR_CNT_L(x)                       (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief FEC74 uncorrectable error counter (Non Roll-over)
 *
 * \details
 * Register: \a HOST_PCS_CFG:PCS25G_FEC74_ERROR:PCS25G_FEC74_NCERR_CNT_H
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_FEC74_NCERR_CNT_H                                               (LAN80XX_IOREG(MMD_ID_HOST_RSFEC, 0,0xaf))

/**
 * \brief
 * FEC uncorrected error counter(Non-Rollover). The FEC could detect but
 * could not correct receive errors in a block. The uncorrectable error is
 * counted max once per FEC block (32 66-bit blocks).  When
 * PCS25G_FEC74_NCERR_CNT_L is read bits 31:16 of the internal
 * FEC74_NCERR_CNT counter are latched for reading from this register and
 * the entire 32-bit internal FEC74_NCERR_CNT counter is reset
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_FEC74_NCERR_CNT_H . FEC74_NCERR_CNT_H
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_FEC74_NCERR_CNT_H_FEC74_NCERR_CNT_H(x)                       (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_FEC74_NCERR_CNT_H_FEC74_NCERR_CNT_H                          (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_FEC74_NCERR_CNT_H_FEC74_NCERR_CNT_H(x)                       (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a HOST_PCS_CFG:PCS25G_FEC74_STATUS
 *
 * PCS25G FEC74 Status
 */


/**
 * \brief Forward Error correction (FEC clause 74) Status
 *
 * \details
 * Register: \a HOST_PCS_CFG:PCS25G_FEC74_STATUS:PCS25G_FEC74_STATUS
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_FEC74_STATUS                                                    (LAN80XX_IOREG(MMD_ID_HOST_RSFEC, 0,0xe021))

/**
 * \brief
 * Indication that FEC has achieved lock on the FEC block boundaries and
 * valid data is being decoded.
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_FEC74_STATUS . FEC74_LOCKED
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_FEC74_STATUS_FEC74_LOCKED(x)                                 (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_FEC74_STATUS_FEC74_LOCKED                                    (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_FEC74_STATUS_FEC74_LOCKED(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a HOST_PCS_CFG:PCS25G_RSFEC_CFG
 *
 * PCS25G RSFEC Configuration
 */


/**
 * \brief RSFEC datapath Config
 *
 * \details
 * Register: \a HOST_PCS_CFG:PCS25G_RSFEC_CFG:PCS25G_RSFEC_CFG
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_RSFEC_CFG                                                       (LAN80XX_IOREG(MMD_ID_HOST_RSFEC, 0,0xe022))

/**
 * \brief
 * Enable RS-FEC datapath. The input is OR'ed with the RS FEC VENDOR
 * CONTROL register bit 2.
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_RSFEC_CFG . FEC91_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_RSFEC_CFG_FEC91_ENA(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_RSFEC_CFG_FEC91_ENA                                          (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_RSFEC_CFG_FEC91_ENA(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * The 25G PCS implementation does not perform compensation for the
 * inserted alignment markers. Enabling this bit would perform rate
 * compensation. This should be enabled when FEC91 is enabled.Note:
 * Codeword Marker Insertion is identical to Alignment Marker Insertion in
 * Multi-Lane Distribution(MLD) using four marker patterns and internally
 * assuming calculations for the marker interval as if usingfour virtual
 * lanes, as used in 40G Clause 82.
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_RSFEC_CFG . FEC91_RADAPT_ENA
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_RSFEC_CFG_FEC91_RADAPT_ENA(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_RSFEC_CFG_FEC91_RADAPT_ENA                                   (LAN80XX_BIT(1))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_RSFEC_CFG_FEC91_RADAPT_ENA(x)                                (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * Register Group: \a HOST_PCS_CFG:PCS25G_STICKY
 *
 * PCS25G Sticky Signals
 */


/**
 * \brief PCS25G sticky register
 *
 * \details
 * PCS25G status register for sticky bits
 *
 * Register: \a HOST_PCS_CFG:PCS25G_STICKY:PCS25G_STICKY_SIG
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_STICKY_SIG                                                      (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe02d))

/**
 * \brief
 * The sticky bit is set when the pcs25g data has been aligned
 *
 * \details
 * 0: align isn't up
 * 1: align has been setup
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_STICKY_SIG . ALIGN_DONE_STICKY
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_STICKY_SIG_ALIGN_DONE_STICKY(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_STICKY_SIG_ALIGN_DONE_STICKY                                 (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_STICKY_SIG_ALIGN_DONE_STICKY(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * The sticky bit is set when the pcs25g signal has been sync
 *
 * \details
 * 0: sync isn't up
 * 1: sync has been setup
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_STICKY_SIG . BLOCK_LOCK_STICKY
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_STICKY_SIG_BLOCK_LOCK_STICKY(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_STICKY_SIG_BLOCK_LOCK_STICKY                                 (LAN80XX_BIT(1))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_STICKY_SIG_BLOCK_LOCK_STICKY(x)                              (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Sticky bit indicating if PCS has been high bit error rate
 *
 * \details
 * 0: bit error rate is not high
 * 1: bit error rate is over theshold set: 16/32/97
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_STICKY_SIG . HI_BER_STICKY
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_STICKY_SIG_HI_BER_STICKY(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_STICKY_SIG_HI_BER_STICKY                                     (LAN80XX_BIT(2))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_STICKY_SIG_HI_BER_STICKY(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,2,1))


/**
 * \brief PCS25G sticky register mask
 *
 * \details
 * PCS25G status register mask for sticky bits
 *
 * Register: \a HOST_PCS_CFG:PCS25G_STICKY:PCS25G_STICKY_SIG_MASK
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK                                                 (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe02e))

/**
 * \brief
 * The sticky bit mask of align sticky
 *
 * \details
 * 0: align will no propagate to interrupt
 * 1: align will propagate to interrupt
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK . ALIGN_DONE_STICKY_MASK
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_ALIGN_DONE_STICKY_MASK(x)                    (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_ALIGN_DONE_STICKY_MASK                       (LAN80XX_BIT(0))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_ALIGN_DONE_STICKY_MASK(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * The sticky bit mask of block lock sticky
 *
 * \details
 * 0: block lock will no propagate to interrupt
 * 1: block lock will propagate to interrupt
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK . BLOCK_LOCK_STICKY_MASK
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_BLOCK_LOCK_STICKY_MASK(x)                    (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_BLOCK_LOCK_STICKY_MASK                       (LAN80XX_BIT(1))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_BLOCK_LOCK_STICKY_MASK(x)                    (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * The sticky bit mask of hi ber sticky
 *
 * \details
 * 0: hi ber will no propagate to interrupt
 * 1: hi ber will propagate to interrupt
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK . HI_BER_STICKY_MASK
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_HI_BER_STICKY_MASK(x)                        (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_HI_BER_STICKY_MASK                           (LAN80XX_BIT(2))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_HI_BER_STICKY_MASK(x)                        (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * Register Group: \a HOST_PCS_CFG:PCS25G_DEBUG
 *
 * PCS25G debug registers
 */


/**
 * \brief Debug registers
 *
 * \details
 * PCS25G debug register 7
 *
 * Register: \a HOST_PCS_CFG:PCS25G_DEBUG:PCS25G_DEBUG_REG_7
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_7                                                     (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe0f8))

/**
 * \brief
 * PCS25G debug register 7
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_7 . PCS25G_DBG_REG_7
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_DEBUG_REG_7_PCS25G_DBG_REG_7(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_DEBUG_REG_7_PCS25G_DBG_REG_7                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_DEBUG_REG_7_PCS25G_DBG_REG_7(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * PCS25G debug register 6
 *
 * Register: \a HOST_PCS_CFG:PCS25G_DEBUG:PCS25G_DEBUG_REG_6
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_6                                                     (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe0f9))

/**
 * \brief
 * PCS25G debug register 6
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_6 . PCS25G_DBG_REG_6
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_DEBUG_REG_6_PCS25G_DBG_REG_6(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_DEBUG_REG_6_PCS25G_DBG_REG_6                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_DEBUG_REG_6_PCS25G_DBG_REG_6(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * PCS25G debug register 5
 *
 * Register: \a HOST_PCS_CFG:PCS25G_DEBUG:PCS25G_DEBUG_REG_5
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_5                                                     (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe0fa))

/**
 * \brief
 * PCS25G debug register 5
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_5 . PCS25G_DBG_REG_5
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_DEBUG_REG_5_PCS25G_DBG_REG_5(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_DEBUG_REG_5_PCS25G_DBG_REG_5                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_DEBUG_REG_5_PCS25G_DBG_REG_5(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * PCS25G debug register 4
 *
 * Register: \a HOST_PCS_CFG:PCS25G_DEBUG:PCS25G_DEBUG_REG_4
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_4                                                     (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe0fb))

/**
 * \brief
 * PCS25G debug register 4
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_4 . PCS25G_DBG_REG_4
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_DEBUG_REG_4_PCS25G_DBG_REG_4(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_DEBUG_REG_4_PCS25G_DBG_REG_4                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_DEBUG_REG_4_PCS25G_DBG_REG_4(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * PCS25G debug register 3
 *
 * Register: \a HOST_PCS_CFG:PCS25G_DEBUG:PCS25G_DEBUG_REG_3
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_3                                                     (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe0fc))

/**
 * \brief
 * PCS25G debug register 3
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_3 . PCS25G_DBG_REG_3
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_DEBUG_REG_3_PCS25G_DBG_REG_3(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_DEBUG_REG_3_PCS25G_DBG_REG_3                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_DEBUG_REG_3_PCS25G_DBG_REG_3(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * PCS25G debug register 2
 *
 * Register: \a HOST_PCS_CFG:PCS25G_DEBUG:PCS25G_DEBUG_REG_2
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_2                                                     (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe0fd))

/**
 * \brief
 * PCS25G debug register 2
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_2 . PCS25G_DBG_REG_2
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_DEBUG_REG_2_PCS25G_DBG_REG_2(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_DEBUG_REG_2_PCS25G_DBG_REG_2                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_DEBUG_REG_2_PCS25G_DBG_REG_2(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * PCS25G debug register 1
 *
 * Register: \a HOST_PCS_CFG:PCS25G_DEBUG:PCS25G_DEBUG_REG_1
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_1                                                     (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe0fe))

/**
 * \brief
 * PCS25G debug register 1
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_1 . PCS25G_DBG_REG_1
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_DEBUG_REG_1_PCS25G_DBG_REG_1(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_DEBUG_REG_1_PCS25G_DBG_REG_1                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_DEBUG_REG_1_PCS25G_DBG_REG_1(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * PCS25G debug register 0
 *
 * Register: \a HOST_PCS_CFG:PCS25G_DEBUG:PCS25G_DEBUG_REG_0
 */
#define LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_0                                                     (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe0ff))

/**
 * \brief
 * PCS25G debug register 0
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_PCS25G_DEBUG_REG_0 . PCS25G_DBG_REG_0
 */
#define  LAN80XX_F_HOST_PCS_CFG_PCS25G_DEBUG_REG_0_PCS25G_DBG_REG_0(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_PCS25G_DEBUG_REG_0_PCS25G_DBG_REG_0                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_PCS25G_DEBUG_REG_0_PCS25G_DBG_REG_0(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a HOST_PCS_CFG:PCS25G_CWM_RADAPT
 *
 * CWM Rate Adaptation Configuration and Status Registers
 */


/**
 * \brief CWM Rata Adaptation FIFO threshold control
 *
 * \details
 * Set the add and drop thresholds for the CWM rate adaptation (CWM RA)
 * FIFO
 *
 * Register: \a HOST_PCS_CFG:PCS25G_CWM_RADAPT:CWM_RADAPT_CFG
 */
#define LAN80XX_HOST_PCS_CFG_CWM_RADAPT_CFG                                                         (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe023))

/**
 * \brief
 * Disable TX local fault generation when no alignment has been reached
 *
 * \details
 * 0: Output local fault symbol at XGMII when not aligned
 * 1: Output IDLE symbols at XGMII when not aligned
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_CWM_RADAPT_CFG . CWM_LF_GEN_DIS
 */
#define  LAN80XX_F_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_LF_GEN_DIS(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_LF_GEN_DIS                                       (LAN80XX_BIT(15))
#define  LAN80XX_X_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_LF_GEN_DIS(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * One-shot that causes the CWM RA FIFO to be cleared and reset. Bit is
 * reset by hardware.
 *
 * \details
 * 0: No action
 * 1: Clear FIFO
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_CWM_RADAPT_CFG . CWM_RADAPT_FIFO_FLUSH
 */
#define  LAN80XX_F_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_FIFO_FLUSH(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),14,1))
#define  LAN80XX_M_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_FIFO_FLUSH                                (LAN80XX_BIT(14))
#define  LAN80XX_X_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_FIFO_FLUSH(x)                             (LAN80XX_EXTRACT_BITFIELD(x,14,1))

/**
 * \brief
 * Set the minimum inter-frame gap to maintain during CWM rate adaptation
 * when dropping transactions. Setting the value to 1 means that 1 idle or
 * ordered set is kept after a terminate. When set to 2 or 3, that many
 * idle or ordered set transactions are kept. Each transaction is 4 bytes.
 *
 * \details
 * 0: INVALID
 * 1: 1 Idle/O set column maintained
 * 2: 2 Idle/O set column maintained
 * 3: 3 Idle/O set column maintained
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_CWM_RADAPT_CFG . CWM_RADAPT_MIN_IFG
 */
#define  LAN80XX_F_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_MIN_IFG(x)                                (LAN80XX_ENCODE_BITFIELD(x,12,2))
#define  LAN80XX_M_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_MIN_IFG                                   (LAN80XX_ENCODE_BITMASK(12,2))
#define  LAN80XX_X_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_MIN_IFG(x)                                (LAN80XX_EXTRACT_BITFIELD(x,12,2))

/**
 * \brief
 * Set the add threshold in the CWM RA FIFO. Level is in 72-bit words.
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_CWM_RADAPT_CFG . CWM_RADAPT_ADD_LVL
 */
#define  LAN80XX_F_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_ADD_LVL(x)                                (LAN80XX_ENCODE_BITFIELD(x,4,4))
#define  LAN80XX_M_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_ADD_LVL                                   (LAN80XX_ENCODE_BITMASK(4,4))
#define  LAN80XX_X_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_ADD_LVL(x)                                (LAN80XX_EXTRACT_BITFIELD(x,4,4))

/**
 * \brief
 * Set the drop threshold in the CWM RA FIFO. Level is in 72-bit words.
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_CWM_RADAPT_CFG . CWM_RADAPT_DROP_LVL
 */
#define  LAN80XX_F_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_DROP_LVL(x)                               (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_DROP_LVL                                  (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_DROP_LVL(x)                               (LAN80XX_EXTRACT_BITFIELD(x,0,4))


/**
 * \brief CWM RA FIFO Sticky Bit Register
 *
 * \details
 * Clear the sticky bits by writing a '1' in the relevant bitgroups.
 *
 * Register: \a HOST_PCS_CFG:PCS25G_CWM_RADAPT:CWM_RADAPT_STICKY
 */
#define LAN80XX_HOST_PCS_CFG_CWM_RADAPT_STICKY                                                      (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe024))

/**
 * \brief
 * CWM RA FIFO underflow sticky bit. Write one to clear.
 *
 * \details
 * 0: No underflow
 * 1: FIFO underflow
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_CWM_RADAPT_STICKY . CWM_RADAPT_FIFO_UFLOW_STICKY
 */
#define  LAN80XX_F_HOST_PCS_CFG_CWM_RADAPT_STICKY_CWM_RADAPT_FIFO_UFLOW_STICKY(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_HOST_PCS_CFG_CWM_RADAPT_STICKY_CWM_RADAPT_FIFO_UFLOW_STICKY                      (LAN80XX_BIT(3))
#define  LAN80XX_X_HOST_PCS_CFG_CWM_RADAPT_STICKY_CWM_RADAPT_FIFO_UFLOW_STICKY(x)                   (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * CWM RA FIFO overflow sticky bit. Write one to clear.
 *
 * \details
 * 0: No overflow
 * 1: FIFO overflow
 *
 * Field: ::LAN80XX_HOST_PCS_CFG_CWM_RADAPT_STICKY . CWM_RADAPT_FIFO_OFLOW_STICKY
 */
#define  LAN80XX_F_HOST_PCS_CFG_CWM_RADAPT_STICKY_CWM_RADAPT_FIFO_OFLOW_STICKY(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_HOST_PCS_CFG_CWM_RADAPT_STICKY_CWM_RADAPT_FIFO_OFLOW_STICKY                      (LAN80XX_BIT(2))
#define  LAN80XX_X_HOST_PCS_CFG_CWM_RADAPT_STICKY_CWM_RADAPT_FIFO_OFLOW_STICKY(x)                   (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * Register Group: \a HOST_PCS_CFG:XGMII_H2L_RA_FIFO_STAT
 *
 * XGMII H2L RA FIFO-Configuration and Status Registers
 */


/**
 * \brief XGMII H2L RA FIFO Interrupt Enables
 *
 * \details
 * XGMII H2L RA FIFO Interrupt Enables
 *
 * Register: \a HOST_PCS_CFG:XGMII_H2L_RA_FIFO_STAT:XGMII_H2L_RA_FIFO_MASK
 */
#define LAN80XX_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_MASK                                                 (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe025))

/**
 * \brief
 * Interrupt enable for XGMII_H2L_RA_FIFO_OVERFLOW
 *
 * \details
 * 0 = XGMII_H2L_RA_FIFO_OVERFLOW will not propagate to interrupt
 * 1 = XGMII_H2L_RA_FIFO_OVERFLOW will propagate to interrupt

 *
 * Field: ::LAN80XX_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_MASK . XGMII_H2L_RA_FIFO_OVERFLOW_INTR_EN
 */
#define  LAN80XX_F_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_MASK_XGMII_H2L_RA_FIFO_OVERFLOW_INTR_EN(x)        (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_MASK_XGMII_H2L_RA_FIFO_OVERFLOW_INTR_EN           (LAN80XX_BIT(3))
#define  LAN80XX_X_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_MASK_XGMII_H2L_RA_FIFO_OVERFLOW_INTR_EN(x)        (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Interrupt enable for XGMII_H2L_RA_FIFO_UNDERFLOW
 *
 * \details
 * 0 = XGMII_H2L_RA_FIFO_UNDERFLOW will not propagate to interrupt
 * 1 = XGMII_H2L_RA_FIFO_UNDERFLOW will propagate to interrupt

 *
 * Field: ::LAN80XX_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_MASK . XGMII_H2L_RA_FIFO_UNDERFLOW_INTR_EN
 */
#define  LAN80XX_F_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_MASK_XGMII_H2L_RA_FIFO_UNDERFLOW_INTR_EN(x)       (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_MASK_XGMII_H2L_RA_FIFO_UNDERFLOW_INTR_EN          (LAN80XX_BIT(2))
#define  LAN80XX_X_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_MASK_XGMII_H2L_RA_FIFO_UNDERFLOW_INTR_EN(x)       (LAN80XX_EXTRACT_BITFIELD(x,2,1))


/**
 * \brief  Status of XGMII_H2L RA FIFO
 *
 * \details
 * Register: \a HOST_PCS_CFG:XGMII_H2L_RA_FIFO_STAT:XGMII_H2L_RA_FIFO_SIGNAL
 */
#define LAN80XX_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_SIGNAL                                               (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe026))

/**
 * \brief
 * Overflow status bit for the XGMII H2L RA FIFO. Write 1 to clear all bits
 *
 * \details
 * Status:
 * 0: No OVERFLOW
 * 1: OVERFLOW

 *
 * Field: ::LAN80XX_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_SIGNAL . XGMII_H2L_RA_FIFO_OVERFLOW
 */
#define  LAN80XX_F_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_SIGNAL_XGMII_H2L_RA_FIFO_OVERFLOW(x)              (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_SIGNAL_XGMII_H2L_RA_FIFO_OVERFLOW                 (LAN80XX_BIT(3))
#define  LAN80XX_X_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_SIGNAL_XGMII_H2L_RA_FIFO_OVERFLOW(x)              (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Underflow status bit for the XGMII H2L RA FIFO. Write 1 to clear all
 * bits
 *
 * \details
 * Status:
 * 0: No UNDERFLOW
 * 1: UNDERFLOW

 *
 * Field: ::LAN80XX_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_SIGNAL . XGMII_H2L_RA_FIFO_UNDERFLOW
 */
#define  LAN80XX_F_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_SIGNAL_XGMII_H2L_RA_FIFO_UNDERFLOW(x)             (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_SIGNAL_XGMII_H2L_RA_FIFO_UNDERFLOW                (LAN80XX_BIT(2))
#define  LAN80XX_X_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_SIGNAL_XGMII_H2L_RA_FIFO_UNDERFLOW(x)             (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * Register Group: \a HOST_PCS_CFG:XGMII_H2L_RA_FIFO_IDLE_COUNTS
 *
 * Idles added and dropped by the XGMII H2L RA FIFO.
 */


/**
 * \brief XGMII H2L RA FIFO Idle Add Count
 *
 * \details
 * Register: \a HOST_PCS_CFG:XGMII_H2L_RA_FIFO_IDLE_COUNTS:XGMII_H2L_RA_FIFO_IDLE_ADD_COUNT
 */
#define LAN80XX_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_IDLE_ADD_COUNT                                       (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe027))

/**
 * \brief
 * Idle group count added in the XGMII H2L RA FIFO for clock rate
 * compensation. The counter saturates when the maximum value is exceeded.
 * The counter is cleared when the register is read. DBG
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_IDLE_ADD_COUNT . XGMII_H2L_RA_FIFO_IDLE_GROUP_ADD_COUNT
 */
#define  LAN80XX_F_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_IDLE_ADD_COUNT_XGMII_H2L_RA_FIFO_IDLE_GROUP_ADD_COUNT(x) (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_IDLE_ADD_COUNT_XGMII_H2L_RA_FIFO_IDLE_GROUP_ADD_COUNT (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_IDLE_ADD_COUNT_XGMII_H2L_RA_FIFO_IDLE_GROUP_ADD_COUNT(x) (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief XGMII_H2L RA FIFO Idle Drop Count
 *
 * \details
 * Register: \a HOST_PCS_CFG:XGMII_H2L_RA_FIFO_IDLE_COUNTS:XGMII_H2L_RA_FIFO_IDLE_DROP_COUNT
 */
#define LAN80XX_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_IDLE_DROP_COUNT                                      (LAN80XX_IOREG(MMD_ID_HOST_PCS_CFG, 0,0xe028))

/**
 * \brief
 * Idle group count dropped in the XGMII H2L RA FIFO for clock rate
 * compensation. The counter saturates when the maximum value is exceeded.
 * The counter is cleared when the register is read.
 *
 * \details
 * Field: ::LAN80XX_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_IDLE_DROP_COUNT . XGMII_H2L_RA_FIFO_IDLE_GROUP_DROP_COUNT
 */
#define  LAN80XX_F_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_IDLE_DROP_COUNT_XGMII_H2L_RA_FIFO_IDLE_GROUP_DROP_COUNT(x) (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_IDLE_DROP_COUNT_XGMII_H2L_RA_FIFO_IDLE_GROUP_DROP_COUNT (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_IDLE_DROP_COUNT_XGMII_H2L_RA_FIFO_IDLE_GROUP_DROP_COUNT(x) (LAN80XX_EXTRACT_BITFIELD(x,0,16))


#endif /* _LAN80XX_MALIBU25G_REGS_HOST_PCS_CFG_H_ */
