// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_JAGUAR2_REGS_VAUI_CHANNEL_H_
#define _VTSS_JAGUAR2_REGS_VAUI_CHANNEL_H_


#include "vtss_jaguar2_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a VAUI_CHANNEL
 *
 * \see vtss_target_VAUI_CHANNEL_e
 *
 * Vaui channel configuration and status register set
 *
 ***********************************************************************/

/**
 * Register Group: \a VAUI_CHANNEL:VAUI_CHANNEL_CFG
 *
 * VAUI channel Configuration Registers
 */


/** 
 * \brief Configuration for VAUI channel
 *
 * \details
 * Configuration register for specific vaui channel settings
 *
 * Register: \a VAUI_CHANNEL:VAUI_CHANNEL_CFG:VAUI_CHANNEL_CFG
 *
 * @param target A \a ::vtss_target_VAUI_CHANNEL_e target
 * @param ri Replicator: x_CH_INST (??), 0-1
 */
#define VTSS_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG(target,ri)  VTSS_IOREG(target,0x0 + (ri))

/** 
 * \brief
 * Enable alignment of lane to a common clock (e.g. XAUI mode) and dock
 * lane with ANEG of lane 0 (Master-ANEG)
 *
 * \details 
 * 0: Off
 * 1: On
 *
 * Field: ::VTSS_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG . LANE_SYNC_ENA
 */
#define  VTSS_F_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG_LANE_SYNC_ENA(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG_LANE_SYNC_ENA     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG_LANE_SYNC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Combine signal_detect information for lanes 0 and 2.
 *
 * \details 
 * 0: Lane 0 and 2 provides own signal_detect
 * 1: Signal_detect of lanes 0 and 2 are ANDed
 *
 * Field: ::VTSS_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG . SIGDET_MODE_R
 */
#define  VTSS_F_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG_SIGDET_MODE_R(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG_SIGDET_MODE_R  VTSS_BIT(1)
#define  VTSS_X_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG_SIGDET_MODE_R(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Combine signal_detect information for all 4 lanes.
 *
 * \details 
 * 0: Each lane provides own signal_detect
 * 1: Signal_detect of all four lanes are ANDed
 *
 * Field: ::VTSS_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG . SIGDET_MODE
 */
#define  VTSS_F_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG_SIGDET_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG_SIGDET_MODE  VTSS_BIT(0)
#define  VTSS_X_VAUI_CHANNEL_VAUI_CHANNEL_CFG_VAUI_CHANNEL_CFG_SIGDET_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a VAUI_CHANNEL:ANEG_CFG
 *
 * ANEG Configuration Registers
 */


/** 
 * \brief ANEG Configuration
 *
 * \details
 * Auto-negotiation configuration register. Note: Setting one of the
 * parallel detect wait times to 0 disables parallel detect function for
 * that specific mode.
 *
 * Register: \a VAUI_CHANNEL:ANEG_CFG:ANEG_CFG
 *
 * @param target A \a ::vtss_target_VAUI_CHANNEL_e target
 * @param gi Replicator: x_ANEG_INST (??), 0-7
 */
#define VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG(gi)  VTSS_IOREG_IX(target,0x2,gi,5,0,0)

/** 
 * \brief
 * Asynchronous reset reseting all auto-negotiation logic
 *
 * \details 
 * 1: Reset
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . ANEG_RESET_ONE_SHOT
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_RESET_ONE_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_RESET_ONE_SHOT  VTSS_BIT(31)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_RESET_ONE_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Reserved for test purposes. Transmit data 0 on all bit positions if ANEG
 * is active
 *
 * \details 
 * 1: Bypass ANEG data
 * 0: Normal operation
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . TXBYP_TESTMODE
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_TXBYP_TESTMODE(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_TXBYP_TESTMODE  VTSS_BIT(23)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_TXBYP_TESTMODE(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Reserved for test purposes. Disable nonce/link_status checks
 *
 * \details 
 * 1: Disable checks
 * 0: Normal operation
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . ATE_TESTMODE
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ATE_TESTMODE(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ATE_TESTMODE  VTSS_BIT(22)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ATE_TESTMODE(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Reserved for test purposes. Control of page_test_max_timer_done check
 *
 * \details 
 * 1: Disable check
 * 0: Normal operation
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . RX_TESTMODE
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_RX_TESTMODE(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_RX_TESTMODE  VTSS_BIT(21)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_RX_TESTMODE(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Reserved for test purposes. ANEG wait timer values are divided by 2^15
 * and the parallel detect timers are divided by 2^10
 *
 * \details 
 * 1: Enable division
 * 0: Normal operation
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . ARB_TESTMODE
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ARB_TESTMODE(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ARB_TESTMODE  VTSS_BIT(20)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ARB_TESTMODE(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Disable automatic ANEG OB configuration
 *
 * \details 
 * 0: Allow ANEG block to control OB during auto-negotiation
 * 1: OB settings are not touched by ANEG block
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . ANEG_OB_CTRL_DIS
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_OB_CTRL_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_OB_CTRL_DIS  VTSS_BIT(16)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_OB_CTRL_DIS(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Disable automatic ANEG speed setting
 *
 * \details 
 * 0: Allow ANEG to select frequency
 * 1: Frequency is programmed using mode2g5_ena and hr_mode_ena
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . ANEG_FREQSEL_DIS
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_FREQSEL_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_FREQSEL_DIS  VTSS_BIT(15)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_FREQSEL_DIS(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Disable automatic power down of lane controlled by ANEG
 *
 * \details 
 * 0: Allow ANEG to power down unused lane
 * 1: Power down is not controlled by ANEG
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . ANEG_PWDN_DIS
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_PWDN_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_PWDN_DIS  VTSS_BIT(14)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_PWDN_DIS(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Parallel detect wait time for 10G using four lanes
 *
 * \details 
 * 0: 0 ms
 * 1: 10 ms
 * 2: 20 ms
 * 3: 40 ms
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . PD_TIMER_10GKX4
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_PD_TIMER_10GKX4(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_PD_TIMER_10GKX4     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_PD_TIMER_10GKX4(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parallel detect wait time for 1G using single lane
 *
 * \details 
 * 0: 0 ms
 * 1: 10 ms
 * 2: 20 ms
 * 3: 40 ms
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . PD_TIMER_1GKX
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_PD_TIMER_1GKX(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_PD_TIMER_1GKX     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_PD_TIMER_1GKX(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Parallel detect wait time for 2.5G using single lane
 *
 * \details 
 * 0: 0 ms
 * 1: 10 ms
 * 2: 20 ms
 * 3: 40 ms
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . PD_TIMER_2G5
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_PD_TIMER_2G5(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_PD_TIMER_2G5     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_PD_TIMER_2G5(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . BLTD_ENA
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_BLTD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_BLTD_ENA  VTSS_BIT(7)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_BLTD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Restart negotiation process
 *
 * \details 
 * 1: Restart
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . RESTART_ANEG_ONE_SHOT
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_RESTART_ANEG_ONE_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_RESTART_ANEG_ONE_SHOT  VTSS_BIT(1)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_RESTART_ANEG_ONE_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Auto-negotiation enable
 *
 * \details 
 * 1: Enable
 * 0: Disable
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG . ANEG_ENA
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_ENA  VTSS_BIT(0)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_CFG_ANEG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief ANEG Advertised Ability 0
 *
 * \details
 * 48 bits that contain the advertised abilities link code word for
 * auto-negotiation (here: lower 32 bit).
 *
 * Register: \a VAUI_CHANNEL:ANEG_CFG:ANEG_ADV_ABILITY_0
 *
 * @param target A \a ::vtss_target_VAUI_CHANNEL_e target
 * @param gi Replicator: x_ANEG_INST (??), 0-7
 */
#define VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0(gi)  VTSS_IOREG_IX(target,0x2,gi,5,0,1)

/** 
 * \brief
 * Reserved for future technology as defined in IEEE 802.3ap clause 73.
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0 . ADV_ABIL_LSB
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_ADV_ABIL_LSB(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_ADV_ABIL_LSB     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_ADV_ABIL_LSB(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * Technology Ability to be advertised (here: 10GBase-KR)
 *
 * \details 
 * 0: Do not advertise 10GB-KR capability
 * 1: Advertise 10GB-KR capability
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0 . CAP_10GKR
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_CAP_10GKR(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_CAP_10GKR  VTSS_BIT(23)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_CAP_10GKR(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Technology Ability to be advertised (here: 10GBase-KX4)
 *
 * \details 
 * 0: Do not advertise 10GB-KX4 capability
 * 1: Advertise 10GB-KX4 capability
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0 . CAP_10GKX4
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_CAP_10GKX4(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_CAP_10GKX4  VTSS_BIT(22)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_CAP_10GKX4(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Technology Ability to be advertised (here: 1000Base-KX)
 *
 * \details 
 * 0: Do not advertise 1GB-KX capability
 * 1: Advertise 1GB-KX capability
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0 . CAP_1GKX
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_CAP_1GKX(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_CAP_1GKX  VTSS_BIT(21)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_CAP_1GKX(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Initial value for Transmit-Nonce field
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0 . TX_NONCE
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_TX_NONCE(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_TX_NONCE     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_TX_NONCE(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * Next page exchange desired
 *
 * \details 
 * 0: Disable NP exchange
 * 1: Enable NP exchange
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0 . NP
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_NP(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_NP  VTSS_BIT(15)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_NP(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Acknowledge bit (this bit is automatically overwritten by ANEG)
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0 . ACKN
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_ACKN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_ACKN  VTSS_BIT(14)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_ACKN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * RF bit (initial value)
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0 . RF
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_RF(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_RF  VTSS_BIT(13)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_RF(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Pause field
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0 . PAUSE
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_PAUSE(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_PAUSE     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_PAUSE(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * Reserved for echoed nonce field (must be cleared)
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0 . ECHOED_NONCE
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_ECHOED_NONCE(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_ECHOED_NONCE     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_ECHOED_NONCE(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Selector field (must be 0x1)
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0 . SEL_FIELD
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_SEL_FIELD(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_SEL_FIELD     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_0_SEL_FIELD(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief ANEG Advertised Ability 1
 *
 * \details
 * 48 bits that contain the advertised abilities link code word for
 * auto-negotiation (here: upper 16 bit).
 *
 * Register: \a VAUI_CHANNEL:ANEG_CFG:ANEG_ADV_ABILITY_1
 *
 * @param target A \a ::vtss_target_VAUI_CHANNEL_e target
 * @param gi Replicator: x_ANEG_INST (??), 0-7
 */
#define VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_1(gi)  VTSS_IOREG_IX(target,0x2,gi,5,0,2)

/** 
 * \brief
 * FEC capability (bit 14: FEC ability, bit 15: FEC requested) - Only used
 * with 10GBase-KR
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_1 . FEC
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_1_FEC(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_1_FEC     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_1_FEC(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Reserved for future technology as defined in IEEE 802.3ap clause 73.
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_1 . ADV_ABIL_MSB
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_1_ADV_ABIL_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_1_ADV_ABIL_MSB     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_ADV_ABILITY_1_ADV_ABIL_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,14)


/** 
 * \brief ANEG Next Page 0
 *
 * \details
 * 48 bits that contain the new next page to transmit during
 * auto-negotiation (here: lower 32 bits).
 *
 * Register: \a VAUI_CHANNEL:ANEG_CFG:ANEG_NEXT_PAGE_0
 *
 * @param target A \a ::vtss_target_VAUI_CHANNEL_e target
 * @param gi Replicator: x_ANEG_INST (??), 0-7
 */
#define VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_0(gi)  VTSS_IOREG_IX(target,0x2,gi,5,0,3)

/** 
 * \brief
 * Lower 32 bits of next page link code word
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_0 . NP_TX_LSB
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_0_NP_TX_LSB(x)  (x)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_0_NP_TX_LSB     0xffffffff
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_0_NP_TX_LSB(x)  (x)


/** 
 * \brief ANEG Next Page 1
 *
 * \details
 * 48 bits that contain the new next page to transmit during
 * auto-negotiation (here: upper 16 bits).
 *
 * Register: \a VAUI_CHANNEL:ANEG_CFG:ANEG_NEXT_PAGE_1
 *
 * @param target A \a ::vtss_target_VAUI_CHANNEL_e target
 * @param gi Replicator: x_ANEG_INST (??), 0-7
 */
#define VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_1(gi)  VTSS_IOREG_IX(target,0x2,gi,5,0,4)

/** 
 * \brief
 * Must be set when a new next page is programmed (self-clearing)
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_1 . NEXT_PAGE_LOADED_ONE_SHOT
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_1_NEXT_PAGE_LOADED_ONE_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_1_NEXT_PAGE_LOADED_ONE_SHOT  VTSS_BIT(31)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_1_NEXT_PAGE_LOADED_ONE_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Upper 16 bits of next page link code word
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_1 . NP_TX_MSB
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_1_NP_TX_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_1_NP_TX_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VAUI_CHANNEL_ANEG_CFG_ANEG_NEXT_PAGE_1_NP_TX_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VAUI_CHANNEL:ANEG_STATUS
 *
 * ANEG Status Registers
 */


/** 
 * \brief ANEG Link Partner Advertised Ability 0
 *
 * \details
 * 48 bits that contain the link partner's advertised abilities / next page
 * information (received link code word, lower 32 bits, received during
 * auto-negotiation). The bit groups are only valid for base pages; for
 * next page data exchange a different bit group coding has to be applied.
 *
 * Register: \a VAUI_CHANNEL:ANEG_STATUS:ANEG_LP_ADV_ABILITY_0
 *
 * @param target A \a ::vtss_target_VAUI_CHANNEL_e target
 * @param gi Replicator: x_ANEG_INST (??), 0-7
 */
#define VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0(gi)  VTSS_IOREG_IX(target,0x2a,gi,3,0,0)

/** 
 * \brief
 * Bits 31 down to 24 of link code word received from link partner.
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . LP_ADV_ABIL_LSB
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_LP_ADV_ABIL_LSB(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_LP_ADV_ABIL_LSB     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_LP_ADV_ABIL_LSB(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * Technology Ability advertised by LP (here: 10GBase-KR)
 *
 * \details 
 * 0: LP is not 10GB-KR capable
 * 1: LP is 10GB-KR capable
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . CAP_10GKR
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_CAP_10GKR(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_CAP_10GKR  VTSS_BIT(23)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_CAP_10GKR(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Technology Ability advertised by LP (here: 10GBase-KX4)
 *
 * \details 
 * 0: LP is not 10GB-KX4 capable
 * 1: LP is 10GB-KX4 capable
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . CAP_10GKX4
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_CAP_10GKX4(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_CAP_10GKX4  VTSS_BIT(22)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_CAP_10GKX4(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Technology Ability advertised by LP (here: 1000Base-KX)
 *
 * \details 
 * 0: LP is not 1GB-KX capable
 * 1: LP is 1GB-KX capable
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . CAP_1GKX
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_CAP_1GKX(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_CAP_1GKX  VTSS_BIT(21)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_CAP_1GKX(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Transmit-Nonce field (received from LinkPartner)
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . TX_NONCE
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_TX_NONCE(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_TX_NONCE     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_TX_NONCE(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * Next page exchange desired by LP
 *
 * \details 
 * 0: No NP exchange desired
 * 1: NP exchange desired
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . NP
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_NP(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_NP  VTSS_BIT(15)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_NP(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Acknowledge bit (this bit is automatically overwritten by ANEG)
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . ACKN
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_ACKN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_ACKN  VTSS_BIT(14)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_ACKN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * RF bit
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . RF
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_RF(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_RF  VTSS_BIT(13)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_RF(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Pause field
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . PAUSE
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_PAUSE(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_PAUSE     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_PAUSE(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * Echoed nonce field
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . ECHOED_NONCE
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_ECHOED_NONCE(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_ECHOED_NONCE     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_ECHOED_NONCE(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Selector field
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . SEL_FIELD
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_SEL_FIELD(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_SEL_FIELD     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_SEL_FIELD(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief ANEG Link Partner Advertised Ability 1
 *
 * \details
 * 48 bits that contain the link partner's advertised abilities or next
 * page information (received link code word, upper 16 bits, received
 * during auto-negotiation). The bit groups are only valid for base pages;
 * for next page data exchange a different bit group coding has to be
 * applied.
 *
 * Register: \a VAUI_CHANNEL:ANEG_STATUS:ANEG_LP_ADV_ABILITY_1
 *
 * @param target A \a ::vtss_target_VAUI_CHANNEL_e target
 * @param gi Replicator: x_ANEG_INST (??), 0-7
 */
#define VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1(gi)  VTSS_IOREG_IX(target,0x2a,gi,3,0,1)

/** 
 * \brief
 * FEC capability (bit 14: FEC ability, bit 15: FEC requested) - Only used
 * with 10GBase-KR
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1 . FEC
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1_FEC(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1_FEC     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1_FEC(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Bits 45 down to 32 of link code word received from link partner.
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1 . LP_ADV_ABIL_MSB
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1_LP_ADV_ABIL_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1_LP_ADV_ABIL_MSB     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1_LP_ADV_ABIL_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,14)


/** 
 * \brief ANEG Status
 *
 * \details
 * Auto negotiation status register
 *
 * Register: \a VAUI_CHANNEL:ANEG_STATUS:ANEG_STATUS
 *
 * @param target A \a ::vtss_target_VAUI_CHANNEL_e target
 * @param gi Replicator: x_ANEG_INST (??), 0-7
 */
#define VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS(gi)  VTSS_IOREG_IX(target,0x2a,gi,3,0,2)

/** 
 * \brief
 * Link control information for 10G quad lane mode
 *
 * \details 
 * 00: Disabled
 * 01: Enabled
 * 11: Scan for carrier
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS . LINK_CTRL_10GKX4
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_LINK_CTRL_10GKX4(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_LINK_CTRL_10GKX4     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_LINK_CTRL_10GKX4(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/** 
 * \brief
 * Link control information for 1G single lane mode
 *
 * \details 
 * 00: Disabled
 * 01: Enabled
 * 11: Scan for carrier
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS . LINK_CTRL_1GKX
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_LINK_CTRL_1GKX(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_LINK_CTRL_1GKX     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_LINK_CTRL_1GKX(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * Link control information for 2.5G single lane mode
 *
 * \details 
 * 00: Disabled
 * 01: Enabled
 * 11: Scan for carrier
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS . LINK_CTRL_2G5
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_LINK_CTRL_2G5(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_LINK_CTRL_2G5     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_LINK_CTRL_2G5(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Error condition indicating an Arbitration state machine error.
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS . ANEG_ARB_FSM_ERR_STICKY
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ANEG_ARB_FSM_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ANEG_ARB_FSM_ERR_STICKY  VTSS_BIT(20)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ANEG_ARB_FSM_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Error condition indicating a Receive state machine error.
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS . ANEG_RX_FSM_ERR_STICKY
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ANEG_RX_FSM_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ANEG_RX_FSM_ERR_STICKY  VTSS_BIT(19)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ANEG_RX_FSM_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Error condition indicating a Transmit state machine error.
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS . ANEG_TX_FSM_ERR_STICKY
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ANEG_TX_FSM_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ANEG_TX_FSM_ERR_STICKY  VTSS_BIT(18)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ANEG_TX_FSM_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Error condition indicating that no compatible link was found.
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS . INCOMPATIBLE_LINK
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_INCOMPATIBLE_LINK(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_INCOMPATIBLE_LINK  VTSS_BIT(17)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_INCOMPATIBLE_LINK(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Error condition indicating errors during parallel detection.
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS . PAR_DETECT_FAULT_STICKY
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_PAR_DETECT_FAULT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_PAR_DETECT_FAULT_STICKY  VTSS_BIT(16)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_PAR_DETECT_FAULT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Current state of Arbiter State Machine
 *
 * \details 
 * 0000: AUTO_NEG_ENA
 * 0001: TX_DISABLE
 * 0010: ABILITY_DETECT
 * 0011: ACKN_DETECT
 * 0100: COMPLETE_ACKN
 * 0101: AN_GOOD_CHECK
 * 0110: AN_GOOD
 * 0111: NEXT_PAGE_WAIT
 * 1000: LINK_STATUS_CHECK
 * 1001: PARALLEL_DET_FAULT
 * 1010: PD_CHECK10GKR
 * 1011: PD_CHECK2G5
 * 1100: PD_CHECK1GKX
 * 1101: PD_CHECK10GKX4
 *
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS . ARBITER_STATE
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ARBITER_STATE(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ARBITER_STATE     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ARBITER_STATE(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Status indicating whether a new page has been received.
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS . PAGE_RX
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_PAGE_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_PAGE_RX  VTSS_BIT(3)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_PAGE_RX(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Status indicating whether the link partner supports auto-negotiation.
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS . LP_ANEG_ABLE
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_LP_ANEG_ABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_LP_ANEG_ABLE  VTSS_BIT(1)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_LP_ANEG_ABLE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Status indicating whether auto-negotiation has completed.
 *
 * \details 
 * Field: ::VTSS_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS . ANEG_COMPLETE
 */
#define  VTSS_F_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ANEG_COMPLETE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ANEG_COMPLETE  VTSS_BIT(0)
#define  VTSS_X_VAUI_CHANNEL_ANEG_STATUS_ANEG_STATUS_ANEG_COMPLETE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_JAGUAR2_REGS_VAUI_CHANNEL_H_ */
