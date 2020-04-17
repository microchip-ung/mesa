// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_JAGUAR2C_REGS_PCS_10GBASE_R_H_
#define _VTSS_JAGUAR2C_REGS_PCS_10GBASE_R_H_


#include "vtss_jaguar2c_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a PCS_10GBASE_R
 *
 * \see vtss_target_PCS_10GBASE_R_e
 *
 * PCS configuration and status registers and counters
 *
 ***********************************************************************/

/**
 * Register Group: \a PCS_10GBASE_R:PCS_10GBR_CFG
 *
 * PCS configuration
 */


/** 
 * \brief PCS configuration
 *
 * \details
 * Configuration register
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:PCS_CFG
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG(target)  VTSS_IOREG(target,0x0)

/** 
 * \brief
 * Global PCS Enable/Disable configuration bit.
 *
 * \details 
 * 0 = Disable PCS
 * 1 = Enable PCS
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG . PCS_ENA
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_PCS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_PCS_ENA  VTSS_BIT(31)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_PCS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Enable PMA loopback operation. When set, Transmit PMA data is loopbacked
 * to Receive PMA data.
 *
 * \details 
 * 0 = Normal mode
 * 1 = Loopback Tx PMA to Rx PMA
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG . PMA_LOOPBACK_ENA
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_PMA_LOOPBACK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_PMA_LOOPBACK_ENA  VTSS_BIT(30)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_PMA_LOOPBACK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Number of sync headers required for block lock. The actual number used
 * is this number plus 1. i.e. entering 63 implies a value of 64.
 *
 * \details 
 * Binary number
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG . SH_CNT_MAX
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_SH_CNT_MAX(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_SH_CNT_MAX     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_SH_CNT_MAX(x)  VTSS_EXTRACT_BITFIELD(x,24,6)

/** 
 * \brief
 * Flip the data bus bits at the WIS/PMA interface such that bit 63 is
 * mapped to bit 0 and bit 0 to 63. i.e. the output bus (63 down to 0) is
 * remapped to (0 to 63) and bit 63 is the first bit.
 *
 * \details 
 * 0: No flip (LSB first)
 * 1: Flip bus (MSB first)
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG . RX_DATA_FLIP
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_RX_DATA_FLIP(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_RX_DATA_FLIP  VTSS_BIT(18)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_RX_DATA_FLIP(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Force re-synchronization of receive logic. When asserted, the receive
 * sync state machine is forced into the LOCK_INIT state and block_lock is
 * lost.
 *
 * \details 
 * 0: Normal operation
 * 1: Reset synchronization
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG . RESYNC_ENA
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_RESYNC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_RESYNC_ENA  VTSS_BIT(15)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_RESYNC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Disable RX local fault generation when no alignment has been reached
 *
 * \details 
 * 0: Output local fault symbol at XGMII when not aligned
 * 1: Output IDLE symbols at XGMII when not aligned
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG . LF_GEN_DIS
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_LF_GEN_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_LF_GEN_DIS  VTSS_BIT(14)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_LF_GEN_DIS(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Enable test pattern checking mode.
 *
 * \details 
 * 0: Normal operation
 * 1: Test pattern mode
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG . RX_TEST_MODE
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_RX_TEST_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_RX_TEST_MODE  VTSS_BIT(13)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_RX_TEST_MODE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Disable the descrambler. When disabled, the data is passed through
 * without being descrambled.
 *
 * \details 
 * 0: Decrambler active
 * 1: Decrambler disabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG . RX_SCR_DISABLE
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_RX_SCR_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_RX_SCR_DISABLE  VTSS_BIT(12)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_RX_SCR_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Flip the data bus bits at the WIS/PMA interface such that bit 63 is
 * mapped to bit 0 and bit 0 to 63. i.e. the output bus (63 downto 0) is
 * remapped to (0 to 63) and bit 63 is the first bit.
 *
 * \details 
 * 0 = No flip (LSB first)
 * 1 = Flip bus (MSB first)
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG . TX_DATA_FLIP
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_TX_DATA_FLIP(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_TX_DATA_FLIP  VTSS_BIT(7)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_TX_DATA_FLIP(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Enable link control using backplane Ethernet ANEG (Auto-Negotiation)
 *
 * \details 
 * 0: Disable link control
 * 1: Enable link control
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG . AN_LINK_CTRL_ENA
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_AN_LINK_CTRL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_AN_LINK_CTRL_ENA  VTSS_BIT(6)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_AN_LINK_CTRL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Enable test pattern generation mode
 *
 * \details 
 * 0: Normal operation
 * 1: Test pattern mode
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG . TX_TEST_MODE
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_TX_TEST_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_TX_TEST_MODE  VTSS_BIT(4)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_TX_TEST_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Disable the scrambler. When disabled, the data is passed through without
 * being scrambled.
 *
 * \details 
 * 0: Scrambler active
 * 1: Scrambler disabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG . TX_SCR_DISABLE
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_TX_SCR_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_TX_SCR_DISABLE  VTSS_BIT(3)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_CFG_TX_SCR_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief PCS SignalDetect Configuration
 *
 * \details
 * PCS signal_detect configuration
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:PCS_SD_CFG
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG(target)  VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Signal detect selection (select input for internal signal_detect line)
 *
 * \details 
 * 0: Select signal_detect line from hardmacro
 * 1: Select external signal_detect line
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG . SD_SEL
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG_SD_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG_SD_SEL  VTSS_BIT(8)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG_SD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Signal detect polarity: The signal level on signal_detect input pin must
 * be equal to SD_POL to indicate signal detection (SD_ENA must be set)
 *
 * \details 
 * 0: Signal Detect input pin must be '0' to indicate a signal detection
 * 1: Signal Detect input pin must be '1' to indicate a signal detection
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG . SD_POL
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG_SD_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG_SD_POL  VTSS_BIT(4)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG_SD_POL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

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
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG . SD_ENA
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG_SD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG_SD_ENA  VTSS_BIT(0)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_SD_CFG_SD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Scrambler initialization
 *
 * \details
 * Most significant bits of the scrambler
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:TX_SEEDA_MSB
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDA_MSB(target)  VTSS_IOREG(target,0x2)

/** 
 * \brief
 * Most significant bits of scrambler used to initialize it during test
 * mode
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDA_MSB . TX_SEEDA_MSB
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDA_MSB_TX_SEEDA_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,26)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDA_MSB_TX_SEEDA_MSB     VTSS_ENCODE_BITMASK(0,26)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDA_MSB_TX_SEEDA_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,26)


/** 
 * \brief Scrambler initialization
 *
 * \details
 * Least significant bits of the scrambler. Used in pseudo-random and
 * PRBS31 modes.
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:TX_SEEDA_LSB
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDA_LSB(target)  VTSS_IOREG(target,0x3)

/** 
 * \brief
 * Least significant bits of scrambler used to initialize it during test
 * mode
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDA_LSB . TX_SEEDA_LSB
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDA_LSB_TX_SEEDA_LSB(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDA_LSB_TX_SEEDA_LSB     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDA_LSB_TX_SEEDA_LSB(x)  (x)


/** 
 * \brief Scrambler initialization
 *
 * \details
 * Most significant bits of the scrambler
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:TX_SEEDB_MSB
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDB_MSB(target)  VTSS_IOREG(target,0x4)

/** 
 * \brief
 * Most significant bits of scrambler used to initialize it during test
 * mode
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDB_MSB . TX_SEEDB_MSB
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDB_MSB_TX_SEEDB_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,26)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDB_MSB_TX_SEEDB_MSB     VTSS_ENCODE_BITMASK(0,26)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDB_MSB_TX_SEEDB_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,26)


/** 
 * \brief Scrambler initialization
 *
 * \details
 * Least significant bits of the scrambler
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:TX_SEEDB_LSB
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDB_LSB(target)  VTSS_IOREG(target,0x5)

/** 
 * \brief
 * Least significant bits of scrambler used to initialize it during test
 * mode
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDB_LSB . TX_SEEDB_LSB
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDB_LSB_TX_SEEDB_LSB(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDB_LSB_TX_SEEDB_LSB     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_TX_SEEDB_LSB_TX_SEEDB_LSB(x)  (x)


/** 
 * \brief PRBS31 initialization
 *
 * \details
 * Initial value to load into the PRBS31 linear-feedback shift register
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:RX_PRBS31_INIT
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_RX_PRBS31_INIT(target)  VTSS_IOREG(target,0x6)

/** 
 * \brief
 * PRBS31 initial value.
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_RX_PRBS31_INIT . RX_PRBS31_INIT
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_RX_PRBS31_INIT_RX_PRBS31_INIT(x)  VTSS_ENCODE_BITFIELD(x,0,31)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_RX_PRBS31_INIT_RX_PRBS31_INIT     VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_RX_PRBS31_INIT_RX_PRBS31_INIT(x)  VTSS_EXTRACT_BITFIELD(x,0,31)


/** 
 * \brief MSB of test pattern
 *
 * \details
 * Most significant Tx bits of test pattern
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:TX_DATAPAT_MSB
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TX_DATAPAT_MSB(target)  VTSS_IOREG(target,0x7)

/** 
 * \brief
 * Most significant 32 bits of 64-bit data pattern used in pseudo-random
 * and user-defined test pattern mode
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TX_DATAPAT_MSB . TX_DATAPAT_MSB
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_TX_DATAPAT_MSB_TX_DATAPAT_MSB(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_TX_DATAPAT_MSB_TX_DATAPAT_MSB     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_TX_DATAPAT_MSB_TX_DATAPAT_MSB(x)  (x)


/** 
 * \brief LSB of test pattern
 *
 * \details
 * Least significant Tx bits of test pattern
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:TX_DATAPAT_LSB
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TX_DATAPAT_LSB(target)  VTSS_IOREG(target,0x8)

/** 
 * \brief
 * Least significant 32 bits of 64-bit data pattern used in pseudo-random
 * and user-defined test pattern mode
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TX_DATAPAT_LSB . TX_DATAPAT_LSB
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_TX_DATAPAT_LSB_TX_DATAPAT_LSB(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_TX_DATAPAT_LSB_TX_DATAPAT_LSB     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_TX_DATAPAT_LSB_TX_DATAPAT_LSB(x)  (x)


/** 
 * \brief MSB of test pattern
 *
 * \details
 * Most significant Rx bits of test pattern
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:RX_DATAPAT_MSB
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_RX_DATAPAT_MSB(target)  VTSS_IOREG(target,0x9)

/** 
 * \brief
 * Most significant 32 bits of 64-bit data pattern used in pseudo-random
 * and user-defined test pattern mode
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_RX_DATAPAT_MSB . RX_DATAPAT_MSB
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_RX_DATAPAT_MSB_RX_DATAPAT_MSB(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_RX_DATAPAT_MSB_RX_DATAPAT_MSB     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_RX_DATAPAT_MSB_RX_DATAPAT_MSB(x)  (x)


/** 
 * \brief LSB of test pattern
 *
 * \details
 * Least significant Rx bits of test pattern
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:RX_DATAPAT_LSB
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_RX_DATAPAT_LSB(target)  VTSS_IOREG(target,0xa)

/** 
 * \brief
 * Least significant 32 bits of 64-bit data pattern used in pseudo-random
 * and user-defined test pattern mode
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_RX_DATAPAT_LSB . RX_DATAPAT_LSB
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_RX_DATAPAT_LSB_RX_DATAPAT_LSB(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_RX_DATAPAT_LSB_RX_DATAPAT_LSB     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_RX_DATAPAT_LSB_RX_DATAPAT_LSB(x)  (x)


/** 
 * \brief Test pattern mode configuration
 *
 * \details
 * Select test patterns when test mode is enabled
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:TEST_CFG
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG(target)  VTSS_IOREG(target,0xb)

/** 
 * \brief
 * Disables inversion of seeds and data in the pseudo-random test pattern
 *
 * \details 
 * 0: Inversion enabled
 * 1: Inversion disabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG . RX_DSBL_INV
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_RX_DSBL_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_RX_DSBL_INV  VTSS_BIT(18)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_RX_DSBL_INV(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Select the test pattern used by the test pattern checker. This register
 * is only used if RX_TEST_MODE is active.
 *
 * \details 
 * 0: unused
 * 1: Pseudo random
 * 2: PRBS31
 * 3: User defined
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG . RX_TESTPAT_SEL
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_RX_TESTPAT_SEL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_RX_TESTPAT_SEL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_RX_TESTPAT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Disables inversion of seeds and data in the pseudo-random test pattern
 *
 * \details 
 * 0: Inversion enabled
 * 1: Inversion disabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG . TX_DSBL_INV
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_TX_DSBL_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_TX_DSBL_INV  VTSS_BIT(5)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_TX_DSBL_INV(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Period of square wave. Value in the register is (Period-4). Valid values
 * of period are 4 to 11.
 *
 * \details 
 * Period = (TX_SQPW_4B+4)
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG . TX_SQPW_4B
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_TX_SQPW_4B(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_TX_SQPW_4B     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_TX_SQPW_4B(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/** 
 * \brief
 * Select the test pattern used by the test pattern generator. This
 * register is only used if TX_TEST_MODE is active.
 *
 * \details 
 * 0: Square wave
 * 1: Pseudo random
 * 2: PRBS31
 * 3: User defined
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG . TX_TESTPAT_SEL
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_TX_TESTPAT_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_TX_TESTPAT_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_TEST_CFG_TX_TESTPAT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief PCS interrupt mask register
 *
 * \details
 * Masks for PCS interrupt sources and sticky bits in PCS_INTR_STAT
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:PCS_INTR_MASK
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK(target)  VTSS_IOREG(target,0xc)

/** 
 * \brief
 * Mask for the RX_FSET_FIFO_FULL_STICKY bit
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK . RX_FSET_FIFO_FULL_MASK
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_FSET_FIFO_FULL_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_FSET_FIFO_FULL_MASK  VTSS_BIT(12)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_FSET_FIFO_FULL_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Mask for the RX_FSET_STICKY bit
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK . RX_FSET_MASK
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_FSET_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_FSET_MASK  VTSS_BIT(11)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_FSET_MASK(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Mask for the XGMII_ERR_STICKY bit
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK . XGMII_ERR_MASK
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_XGMII_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_XGMII_ERR_MASK  VTSS_BIT(10)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_XGMII_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Mask for RX_OSET_FIFO_FULL_STICKY
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK . RX_OSET_FIFO_FULL_MASK
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_OSET_FIFO_FULL_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_OSET_FIFO_FULL_MASK  VTSS_BIT(6)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_OSET_FIFO_FULL_MASK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Mask for the RX_OSET_STICKY bit
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK . RX_OSET_MASK
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_OSET_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_OSET_MASK  VTSS_BIT(5)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_OSET_MASK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Mask for the C64B66B_ERR_STICKY bit
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK . C64B66B_ERR_MASK
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_C64B66B_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_C64B66B_ERR_MASK  VTSS_BIT(4)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_C64B66B_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Mask for the LOCK_CHANGED_STICKY bit
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK . LOCK_CHANGED_MASK
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_LOCK_CHANGED_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_LOCK_CHANGED_MASK  VTSS_BIT(3)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_LOCK_CHANGED_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Mask for the RX_HI_BER_STICKY bit
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK . RX_HI_BER_MASK
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_HI_BER_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_HI_BER_MASK  VTSS_BIT(0)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_PCS_INTR_MASK_RX_HI_BER_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Counter for 125 microsecond period
 *
 * \details
 * This register sets the number of WIS/PMA divide-by-2 clocks in one 125
 * microsecond interval. The counter increments and wraps. It should be set
 * to (125 * freq_Mhz/2) where freq_Mhz is the WIS/PMA frequency in
 * Megahertz. 0 disables the counter.
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_CFG:TIMER_125
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TIMER_125(target)  VTSS_IOREG(target,0xd)

/** 
 * \brief
 * Sets the maximum count for the 125 microsecond counter. Counts input
 * clocks.
 *
 * \details 
 * 16-bit binary number
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_CFG_TIMER_125 . TIMER_125
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_CFG_TIMER_125_TIMER_125(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_CFG_TIMER_125_TIMER_125     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_CFG_TIMER_125_TIMER_125(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a PCS_10GBASE_R:PCS_10GBR_STATUS
 *
 * PCS status
 */


/** 
 * \brief PCS interrupt status register
 *
 * \details
 * Contains the sticky bits representing interrupts from the PCS. Set by
 * logic. Write 1 to clear.
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_STATUS:PCS_INTR_STAT
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT(target)  VTSS_IOREG(target,0xe)

/** 
 * \brief
 * Interrupt generated when the Rx signal ordered set FIFO is full or
 * becomes not full
 * Interrupt occurs whenever there is ANY change in the underlying status
 *
 * \details 
 * 0: Rx ordered set FIFO full status unchanged
 * 1: Rx ordered set FIFO full status changed
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT . RX_FSET_FIFO_FULL_STICKY
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_FSET_FIFO_FULL_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_FSET_FIFO_FULL_STICKY  VTSS_BIT(12)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_FSET_FIFO_FULL_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Interrupt indicating that a signal ordered set was received and captured
 * (||Fsig||)
 *
 * \details 
 * 0: No ordered set captured
 * 1: Ordered set captured in FIFO
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT . RX_FSET_STICKY
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_FSET_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_FSET_STICKY  VTSS_BIT(11)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_FSET_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Interrupt if an invalid Tx XGMII character is detected
 *
 * \details 
 * 0: No invalid character
 * 1: Invalid character detected
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT . XGMII_ERR_STICKY
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_XGMII_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_XGMII_ERR_STICKY  VTSS_BIT(10)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_XGMII_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Interrupt generated when the Rx sequence ordered set FIFO is full or
 * becomes not full
 * Interrupt occurs whenever there is ANY change in the underlying status
 *
 * \details 
 * 0: Rx ordered set FIFO full status unchanged
 * 1: Rx ordered set FIFO full status changed
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT . RX_OSET_FIFO_FULL_STICKY
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_OSET_FIFO_FULL_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_OSET_FIFO_FULL_STICKY  VTSS_BIT(6)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_OSET_FIFO_FULL_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Interrupt indicating that a sequence ordered set was received and
 * captured (||Q||)
 *
 * \details 
 * 0: No ordered set captured
 * 1: Ordered set captured in FIFO
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT . RX_OSET_STICKY
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_OSET_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_OSET_STICKY  VTSS_BIT(5)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_OSET_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Interrupt when an invalid Rx block is detected
 *
 * \details 
 * 0: No invalid blocks
 * 1: Invalid block detected
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT . C64B66B_ERR_STICKY
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_C64B66B_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_C64B66B_ERR_STICKY  VTSS_BIT(4)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_C64B66B_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Lock (loss of synchronization) changed interrupt
 * Interrupt occurs whenever there is ANY change in the underlying status
 * of the LOCK signal
 *
 * \details 
 * 0: Synchronization has not changed
 * 1: Synchronization (lock) status changed
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT . LOCK_CHANGED_STICKY
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_LOCK_CHANGED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_LOCK_CHANGED_STICKY  VTSS_BIT(3)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_LOCK_CHANGED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set by the Rx BER state machine when a high bit error rate condition is
 * detected or cleared
 * Interrupt occurs whenever there is ANY change in the underlying status
 *
 * \details 
 * 0: High BER status unchanged
 * 1: High BER status changed
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT . RX_HI_BER_STICKY
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_HI_BER_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_HI_BER_STICKY  VTSS_BIT(0)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_INTR_STAT_RX_HI_BER_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS status register
 *
 * \details
 * Contains status information from the PCS core
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_STATUS:PCS_STATUS
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS(target)  VTSS_IOREG(target,0xf)

/** 
 * \brief
 * When in test pattern check mode, this bit will read 1 if the test
 * pattern checker detects a match. When 0, the test pattern does not
 * match. The test pattern error counts should still be used along with
 * this register bit to determine proper test match status. The bit will
 * read back 1 only when the test pattern is matching. This may happen even
 * while test pattern errors are counted on other clock cycles.
 *
 * \details 
 * 0: Test pattern mismatch
 * 1: Test pattern match
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS . TESTPAT_MATCH
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_TESTPAT_MATCH(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_TESTPAT_MATCH  VTSS_BIT(4)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_TESTPAT_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * The block_lock status from the synchronization state machine
 *
 * \details 
 * 0: Not synchronized
 * 1: Synchronized, lock obtained
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS . RX_BLOCK_LOCK
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_RX_BLOCK_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_RX_BLOCK_LOCK  VTSS_BIT(3)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_RX_BLOCK_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set by the Rx BER state machine when a high bit-error-rate condition is
 * detected
 *
 * \details 
 * 0: Normal BER
 * 1: High BER
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS . RX_HI_BER
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_RX_HI_BER(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_RX_HI_BER  VTSS_BIT(0)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_STATUS_PCS_STATUS_RX_HI_BER(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a PCS_10GBASE_R:PCS_10GBR_HA_STATUS
 *
 * PCS status registers and counters
 */


/** 
 * \brief Test pattern mode error counts
 *
 * \details
 * Count of the errors detected in test pattern mode
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_HA_STATUS:TEST_ERR_CNT
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TEST_ERR_CNT(target)  VTSS_IOREG(target,0x10)

/** 
 * \brief
 * Count of detected test pattern errors in Rx test pattern checker. Write
 * 0 to clear.
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TEST_ERR_CNT . TEST_ERR_CNT
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TEST_ERR_CNT_TEST_ERR_CNT(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TEST_ERR_CNT_TEST_ERR_CNT     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TEST_ERR_CNT_TEST_ERR_CNT(x)  (x)


/** 
 * \brief Tx errored block counter
 *
 * \details
 * Count of the Tx errored blocks
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_HA_STATUS:TX_ERRBLK_CNT
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TX_ERRBLK_CNT(target)  VTSS_IOREG(target,0x11)

/** 
 * \brief
 * Count of the errored Tx blocks
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TX_ERRBLK_CNT . TX_ERRBLK_CNT
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TX_ERRBLK_CNT_TX_ERRBLK_CNT(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TX_ERRBLK_CNT_TX_ERRBLK_CNT     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TX_ERRBLK_CNT_TX_ERRBLK_CNT(x)  (x)


/** 
 * \brief Invalid character counter
 *
 * \details
 * Counts the number of invalid control characters
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_HA_STATUS:TX_CHARERR_CNT
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TX_CHARERR_CNT(target)  VTSS_IOREG(target,0x12)

/** 
 * \brief
 * Count of the number of invalid control characters
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TX_CHARERR_CNT . TX_CHARERR_CNT
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TX_CHARERR_CNT_TX_CHARERR_CNT(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TX_CHARERR_CNT_TX_CHARERR_CNT     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_TX_CHARERR_CNT_TX_CHARERR_CNT(x)  (x)


/** 
 * \brief ber_count
 *
 * \details
 * ber_count from IEEE802.3 section 49.2.14.2.
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_HA_STATUS:RX_BER_CNT
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_BER_CNT(target)  VTSS_IOREG(target,0x13)

/** 
 * \brief
 * ber_count from the BER state machine
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_BER_CNT . RX_BER_CNT
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_BER_CNT_RX_BER_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_BER_CNT_RX_BER_CNT     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_BER_CNT_RX_BER_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief Rx errored block counter
 *
 * \details
 * Count of the Rx errored blocks
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_HA_STATUS:RX_ERRBLK_CNT
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_ERRBLK_CNT(target)  VTSS_IOREG(target,0x14)

/** 
 * \brief
 * Count of the errored Rx blocks
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_ERRBLK_CNT . RX_ERRBLK_CNT
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_ERRBLK_CNT_RX_ERRBLK_CNT(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_ERRBLK_CNT_RX_ERRBLK_CNT     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_ERRBLK_CNT_RX_ERRBLK_CNT(x)  (x)


/** 
 * \brief Invalid character counter
 *
 * \details
 * Counts the number of invalid control characters
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_HA_STATUS:RX_CHARERR_CNT
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_CHARERR_CNT(target)  VTSS_IOREG(target,0x15)

/** 
 * \brief
 * Count of the number of invalid control characters
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_CHARERR_CNT . RX_CHARERR_CNT
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_CHARERR_CNT_RX_CHARERR_CNT(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_CHARERR_CNT_RX_CHARERR_CNT     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_CHARERR_CNT_RX_CHARERR_CNT(x)  (x)


/** 
 * \brief Status of Rx sequence ordered set FIFO
 *
 * \details
 * Contains status information for the FIFO containing captured Rx ordered
 * sets
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_HA_STATUS:RX_OSET_FIFO_STAT
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_STAT(target)  VTSS_IOREG(target,0x16)

/** 
 * \brief
 * Indicates if the FIFO is full
 *
 * \details 
 * 0: FIFO not full
 * 1: FIFO full
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_STAT . RX_OSET_FIFO_FULL
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_STAT_RX_OSET_FIFO_FULL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_STAT_RX_OSET_FIFO_FULL  VTSS_BIT(4)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_STAT_RX_OSET_FIFO_FULL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Number of valid ordered sets in the FIFO that can be read
 *
 * \details 
 * Binary number
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_STAT . RX_OSET_FIFO_NUM
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_STAT_RX_OSET_FIFO_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_STAT_RX_OSET_FIFO_NUM     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_STAT_RX_OSET_FIFO_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Rx ordered set FIFO data
 *
 * \details
 * The register interface to the ordered set data
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_HA_STATUS:RX_OSET_FIFO_DATA
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_DATA(target)  VTSS_IOREG(target,0x17)

/** 
 * \brief
 * Register interface to the FIFO containing captured ordered sets. Each
 * read of this register pops a 24-bit ordered set off the FIFO and
 * increments the FIFO pointer.
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_DATA . RX_OSET_FIFO_DATA
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_DATA_RX_OSET_FIFO_DATA(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_DATA_RX_OSET_FIFO_DATA     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_OSET_FIFO_DATA_RX_OSET_FIFO_DATA(x)  VTSS_EXTRACT_BITFIELD(x,8,24)


/** 
 * \brief Status of Rx signal ordered set FIFO
 *
 * \details
 * Contains status information for the FIFO containing captured Rx ordered
 * sets
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_HA_STATUS:RX_FSET_FIFO_STAT
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_STAT(target)  VTSS_IOREG(target,0x18)

/** 
 * \brief
 * Indicates if the FIFO is full
 *
 * \details 
 * 0: FIFO not full
 * 1: FIFO full
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_STAT . RX_FSET_FIFO_FULL
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_STAT_RX_FSET_FIFO_FULL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_STAT_RX_FSET_FIFO_FULL  VTSS_BIT(4)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_STAT_RX_FSET_FIFO_FULL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Number of valid ordered sets in the FIFO that can be read
 *
 * \details 
 * Binary number
 *
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_STAT . RX_FSET_FIFO_NUM
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_STAT_RX_FSET_FIFO_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_STAT_RX_FSET_FIFO_NUM     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_STAT_RX_FSET_FIFO_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Rx ordered set FIFO data
 *
 * \details
 * The register interface to the ordered set data
 *
 * Register: \a PCS_10GBASE_R:PCS_10GBR_HA_STATUS:RX_FSET_FIFO_DATA
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_DATA(target)  VTSS_IOREG(target,0x19)

/** 
 * \brief
 * Register interface to the FIFO containing captured ordered sets. Each
 * read of this register pops a 24-bit ordered set off the FIFO and
 * increments the FIFO pointer.
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_DATA . RX_FSET_FIFO_DATA
 */
#define  VTSS_F_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_DATA_RX_FSET_FIFO_DATA(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_DATA_RX_FSET_FIFO_DATA     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_PCS_10GBASE_R_PCS_10GBR_HA_STATUS_RX_FSET_FIFO_DATA_RX_FSET_FIFO_DATA(x)  VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * Register Group: \a PCS_10GBASE_R:KR_FEC_CFG
 *
 * KR FEC IEEE CONTROL REGISTER
 */


/** 
 * \brief KR FEC configuration regsiter
 *
 * \details
 * Register: \a PCS_10GBASE_R:KR_FEC_CFG:KR_FEC_CFG
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG(target)  VTSS_IOREG(target,0x1a)

/** 
 * \brief
 * Enables FEC decoder to indicate errors to PCS by sync bits
 *
 * \details 
 * 
 * 0: FEC Decoding errors have no effect on PCS sync bits
 * 1: Enable FEC decoder to indicate errors to PCS sync bits

 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG . ENABLE_ERROR_INDICATION
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_ENABLE_ERROR_INDICATION(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_ENABLE_ERROR_INDICATION  VTSS_BIT(16)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_ENABLE_ERROR_INDICATION(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * When set FEC counters are reset.
 *
 * \details 
 * 
 * 0: no effect
 * 1: reset FEC counters

 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG . RESET_MONITOR_COUNTERS
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_RESET_MONITOR_COUNTERS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_RESET_MONITOR_COUNTERS  VTSS_BIT(12)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_RESET_MONITOR_COUNTERS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Flip the data bus bits at PCS interface such that bit 65 is mapped to
 * bit 0 and bit 0 to 65. i.e. the output bus (65 downto 0) is remapped to
 * (0 to 65) and bit 65 is the first bit.
 *
 * \details 
 * 0 = No flip (LSB first)
 * 1 = Flip bus (MSB first)
 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG . TX_DATA_FLIP
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_TX_DATA_FLIP(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_TX_DATA_FLIP  VTSS_BIT(8)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_TX_DATA_FLIP(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Flip the data bus bits at PCS interface such that bit 65 is mapped to
 * bit 0 and bit 0 to 65. i.e. the output bus (65 downto 0) is remapped to
 * (0 to 65) and bit 65 is the first bit.
 *
 * \details 
 * 0 = No flip (LSB first)
 * 1 = Flip bus (MSB first)
 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG . RX_DATA_FLIP
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_RX_DATA_FLIP(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_RX_DATA_FLIP  VTSS_BIT(4)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_RX_DATA_FLIP(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enables enabling/disabling FEC using backplane Ethernet ANEG
 * (Auto-Negotiation)
 *
 * \details 
 * 0: ANEG doesn't control Enable/Disable of FEC
 * 1: ANEG controls Enable/Diable of FEC
 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG . AN_FEC_CTRL_ENA
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_AN_FEC_CTRL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_AN_FEC_CTRL_ENA  VTSS_BIT(2)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_AN_FEC_CTRL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Global FEC Enable/Disable configuration bit.
 *
 * \details 
 * 0 = Disable FEC
 * 1 = Enable FEC
 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG . FEC_ENA
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_FEC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_FEC_ENA  VTSS_BIT(0)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_CFG_KR_FEC_CFG_FEC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a PCS_10GBASE_R:KR_FEC_THRESHOLD_CFG
 *
 * KR FEC counters threshold configurations
 */


/** 
 * \brief FEC fixed error count threshold value
 *
 * \details
 * Register: \a PCS_10GBASE_R:KR_FEC_THRESHOLD_CFG:FIXED_ERROR_COUNT_THRESHOLD
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_KR_FEC_THRESHOLD_CFG_FIXED_ERROR_COUNT_THRESHOLD(target)  VTSS_IOREG(target,0x1b)

/** 
 * \brief
 * When fixed error count exceeds or equal to this value, then
 * FEC_FIXED_ERROR_COUNT_STICKY sticky bit is set and interrupt is
 * generated if enabled through FEC_FIXED_ERROR_COUNT_STICKY_MASK
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_THRESHOLD_CFG_FIXED_ERROR_COUNT_THRESHOLD . FIXED_ERROR_COUNT_THRESHOLD
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_THRESHOLD_CFG_FIXED_ERROR_COUNT_THRESHOLD_FIXED_ERROR_COUNT_THRESHOLD(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_THRESHOLD_CFG_FIXED_ERROR_COUNT_THRESHOLD_FIXED_ERROR_COUNT_THRESHOLD     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_THRESHOLD_CFG_FIXED_ERROR_COUNT_THRESHOLD_FIXED_ERROR_COUNT_THRESHOLD(x)  (x)


/** 
 * \brief FEC unfixable error count threshold value
 *
 * \details
 * Register: \a PCS_10GBASE_R:KR_FEC_THRESHOLD_CFG:UNFIXABLE_ERROR_COUNT_THRESHOLD
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_KR_FEC_THRESHOLD_CFG_UNFIXABLE_ERROR_COUNT_THRESHOLD(target)  VTSS_IOREG(target,0x1c)

/** 
 * \brief
 * When fixed error count exceeds or equal to this value, then
 * FEC_UNFIXABLE_ERROR_COUNT_STICKY sticky bit is set and interrupt is
 * generated if enabled through FEC_UNFIXABLE_ERROR_COUNT_STICKY_MASK
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_THRESHOLD_CFG_UNFIXABLE_ERROR_COUNT_THRESHOLD . UNFIXABLE_ERROR_COUNT_THRESHOLD
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_THRESHOLD_CFG_UNFIXABLE_ERROR_COUNT_THRESHOLD_UNFIXABLE_ERROR_COUNT_THRESHOLD(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_THRESHOLD_CFG_UNFIXABLE_ERROR_COUNT_THRESHOLD_UNFIXABLE_ERROR_COUNT_THRESHOLD     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_THRESHOLD_CFG_UNFIXABLE_ERROR_COUNT_THRESHOLD_UNFIXABLE_ERROR_COUNT_THRESHOLD(x)  (x)

/**
 * Register Group: \a PCS_10GBASE_R:KR_FEC_HA_STATUS
 *
 * KR FEC IEEE status registers
 */


/** 
 * \brief FEC corrected block cout
 *
 * \details
 * Register: \a PCS_10GBASE_R:KR_FEC_HA_STATUS:KR_FEC_CORRECTED
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_KR_FEC_HA_STATUS_KR_FEC_CORRECTED(target)  VTSS_IOREG(target,0x1d)

/** 
 * \brief
 * FEC corrected block count.
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_HA_STATUS_KR_FEC_CORRECTED . FEC_CORRECTED_BLOCKS
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_HA_STATUS_KR_FEC_CORRECTED_FEC_CORRECTED_BLOCKS(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_HA_STATUS_KR_FEC_CORRECTED_FEC_CORRECTED_BLOCKS     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_HA_STATUS_KR_FEC_CORRECTED_FEC_CORRECTED_BLOCKS(x)  (x)


/** 
 * \brief KR FEC uncorrected block count
 *
 * \details
 * Register: \a PCS_10GBASE_R:KR_FEC_HA_STATUS:KR_FEC_UNCORRECTED
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_KR_FEC_HA_STATUS_KR_FEC_UNCORRECTED(target)  VTSS_IOREG(target,0x1e)

/** 
 * \brief
 * FEC uncorrectable block count.
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_HA_STATUS_KR_FEC_UNCORRECTED . FEC_UNCORRECTED_BLOCKS
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_HA_STATUS_KR_FEC_UNCORRECTED_FEC_UNCORRECTED_BLOCKS(x)  (x)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_HA_STATUS_KR_FEC_UNCORRECTED_FEC_UNCORRECTED_BLOCKS     0xffffffff
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_HA_STATUS_KR_FEC_UNCORRECTED_FEC_UNCORRECTED_BLOCKS(x)  (x)

/**
 * Register Group: \a PCS_10GBASE_R:KR_FEC_STATUS
 *
 * KR FEC sticky bit regsiter
 */


/** 
 * \brief Sticky bit register
 *
 * \details
 * Register: \a PCS_10GBASE_R:KR_FEC_STATUS:KR_FEC_STICKY
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY(target)  VTSS_IOREG(target,0x1f)

/** 
 * \brief
 * This sticky bit is set whenever fixed error count crosses configured
 * FIXED_ERROR_COUNT_THRESHOLD.
 * Note: write '1' to clear this bit.
 *
 * \details 
 * 0: Error counter has not exceeded threshold since the last time this bit
 * was cleared.
 * 1: Error count exceeded threshold since the last time this bit was
 * cleared.
 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY . FEC_FIXED_ERROR_COUNT_STICKY
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_FEC_FIXED_ERROR_COUNT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_FEC_FIXED_ERROR_COUNT_STICKY  VTSS_BIT(8)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_FEC_FIXED_ERROR_COUNT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * This sticky bit is set whenever fixed error count crosses configured
 * UNFIXABLE_ERROR_COUNT_THRESHOLD.
 * Note: write '1' to clear this bit.
 *
 * \details 
 * 0: Error counter has not exceeded threshold since the last time this bit
 * was cleared.
 * 1: Error count exceeded threshold since the last time this bit was
 * cleared.
 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY . FEC_UNFIXABLE_ERROR_COUNT_STICKY
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_FEC_UNFIXABLE_ERROR_COUNT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_FEC_UNFIXABLE_ERROR_COUNT_STICKY  VTSS_BIT(4)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_FEC_UNFIXABLE_ERROR_COUNT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * FEC in frame lock indication
 * This is a sticky bit that latches the low state.
 *
 * \details 
 * 
 * 0: FEC decoder has not achieved lock
 * 1: FEC decoder has achieved lock

 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY . FEC_FRAME_LOCK_STICKY
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_FEC_FRAME_LOCK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_FEC_FRAME_LOCK_STICKY  VTSS_BIT(0)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_FEC_FRAME_LOCK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Sticky bit mask register
 *
 * \details
 * Register: \a PCS_10GBASE_R:KR_FEC_STATUS:KR_FEC_STICKY_MASK
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_MASK(target)  VTSS_IOREG(target,0x20)

/** 
 * \brief
 * Enable interruput generation when FEC_FIXED_ERROR_COUNT_STICKY is set
 *
 * \details 
 * 0: Disable interrupt generation
 * 1: Enable interrupt generation
 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_MASK . FEC_FIXED_ERROR_COUNT_STICKY_MASK
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_MASK_FEC_FIXED_ERROR_COUNT_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_MASK_FEC_FIXED_ERROR_COUNT_STICKY_MASK  VTSS_BIT(8)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_MASK_FEC_FIXED_ERROR_COUNT_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Enable interruput generation when FEC_UNFIXABLE_ERROR_COUNT_STICKY is
 * set
 *
 * \details 
 * 0: Disable interrupt generation
 * 1: Enable interrupt generation
 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_MASK . FEC_UNFIXABLE_ERROR_COUNT_STICKY_MASK
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_MASK_FEC_UNFIXABLE_ERROR_COUNT_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_MASK_FEC_UNFIXABLE_ERROR_COUNT_STICKY_MASK  VTSS_BIT(4)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_MASK_FEC_UNFIXABLE_ERROR_COUNT_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable interruput generation when FEC_FRAME_LOCK_STICKY is set
 *
 * \details 
 * 0: Disable interrupt generation
 * 1: Enable interrupt generation
 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_MASK . FEC_FRAME_LOCK_STICKY_MASK
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_MASK_FEC_FRAME_LOCK_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_MASK_FEC_FRAME_LOCK_STICKY_MASK  VTSS_BIT(0)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STICKY_MASK_FEC_FRAME_LOCK_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief KR FEC status register
 *
 * \details
 * Register: \a PCS_10GBASE_R:KR_FEC_STATUS:KR_FEC_STATUS
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STATUS(target)  VTSS_IOREG(target,0x21)

/** 
 * \brief
 * Result of comparing KR FEC's corrected block count (1x00AC/1x00AD) to
 * the threshold setting in 3x8E0A/3x8E0B.
 *
 * \details 
 * 0: count did not exceed threshold setting
 * 1: count exceeded threshold setting
 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STATUS . FEC_FIXED_ERROR_COUNT_ERROR_STATUS
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STATUS_FEC_FIXED_ERROR_COUNT_ERROR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STATUS_FEC_FIXED_ERROR_COUNT_ERROR_STATUS  VTSS_BIT(1)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STATUS_FEC_FIXED_ERROR_COUNT_ERROR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Result of comparing KR FEC's uncorrectable block count (1x00AE/1x00AF)
 * to the threshold setting in 3x8E0C/3x8E0D.
 *
 * \details 
 * 0: count did not exceed threshold setting
 * 1: count exceeded threshold setting
 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STATUS . FEC_UNFIXABLE_ERROR_COUNT_ERROR_STATUS
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STATUS_FEC_UNFIXABLE_ERROR_COUNT_ERROR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STATUS_FEC_UNFIXABLE_ERROR_COUNT_ERROR_STATUS  VTSS_BIT(0)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_STATUS_KR_FEC_STATUS_FEC_UNFIXABLE_ERROR_COUNT_ERROR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a PCS_10GBASE_R:KR_FEC_CAPABILITY
 *
 * KR FEC capability register group
 */


/** 
 * \brief FEC ability register
 *
 * \details
 * Register: \a PCS_10GBASE_R:KR_FEC_CAPABILITY:KR_FEC_CAPABILITY
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_KR_FEC_CAPABILITY_KR_FEC_CAPABILITY(target)  VTSS_IOREG(target,0x22)

/** 
 * \brief
 * This is a status bit indicating whether PHY supports FEC or not.
 *
 * \details 
 * 
 * 0: This PHY device does not support FEC.
 * 1: This PHY device supports FEC.

 *
 * Field: ::VTSS_PCS_10GBASE_R_KR_FEC_CAPABILITY_KR_FEC_CAPABILITY . FEC_CAPABLE
 */
#define  VTSS_F_PCS_10GBASE_R_KR_FEC_CAPABILITY_KR_FEC_CAPABILITY_FEC_CAPABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS_10GBASE_R_KR_FEC_CAPABILITY_KR_FEC_CAPABILITY_FEC_CAPABLE  VTSS_BIT(0)
#define  VTSS_X_PCS_10GBASE_R_KR_FEC_CAPABILITY_KR_FEC_CAPABILITY_FEC_CAPABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a PCS_10GBASE_R:EEE_TIMER_CFG
 *
 * Register group for timer configurations related to EEE of 10G Base-R PCS
 */


/** 
 * \brief One micro-second timer configuration register
 *
 * \details
 * This register value is used to elaps 1us time as specified in
 * IEEE802.3az-2010 clause 49.
 *
 * Register: \a PCS_10GBASE_R:EEE_TIMER_CFG:ONE_US_TIMER_REG
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_ONE_US_TIMER_REG(target)  VTSS_IOREG(target,0x23)

/** 
 * \brief
 * This holds no.of 64-bit PMA clocks required to achieve 1 micro-second (1
 * us) time interval.
 * 
 * As per IEEE 803.3az-2010, min and max values are as follows:
 * 
 * MIN : 1.1 us = 178
 * MAX: 1.3 us = 209
 * 
 * Note: Default value is ~1.1 us = 178
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_ONE_US_TIMER_REG . ONE_US_TIMER
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_TIMER_CFG_ONE_US_TIMER_REG_ONE_US_TIMER(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_PCS_10GBASE_R_EEE_TIMER_CFG_ONE_US_TIMER_REG_ONE_US_TIMER     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_PCS_10GBASE_R_EEE_TIMER_CFG_ONE_US_TIMER_REG_ONE_US_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief EEE TX Sleep timer configuration register
 *
 * \details
 * This register value is used to elaps time in TX_SLEEP state of EEE
 * TX-FSM as specified in IEEE802.3az-2010 clause 49.
 *
 * Register: \a PCS_10GBASE_R:EEE_TIMER_CFG:TX_TS_TIMER_REG
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TS_TIMER_REG(target)  VTSS_IOREG(target,0x24)

/** 
 * \brief
 * This holds no.of 64-bit PMA clocks required to achieve specified sleep
 * time interval.
 * 
 * As per IEEE 803.3az-2010, min and max values are as follows:
 * 
 * MIN : 4.9 us = 790
 * MAX: 5.1 us = 821
 * 
 * Note: Default value is ~5 us = 806
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TS_TIMER_REG . TX_TS_TIMER
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TS_TIMER_REG_TX_TS_TIMER(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TS_TIMER_REG_TX_TS_TIMER     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TS_TIMER_REG_TX_TS_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief EEE TX Quiet timer configuration register
 *
 * \details
 * This register value is used to elaps time in TX_QUIET state of EEE
 * TX-FSM as specified in IEEE802.3az-2010 clause 49.
 *
 * Register: \a PCS_10GBASE_R:EEE_TIMER_CFG:TX_TQ_TIMER_REG
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TQ_TIMER_REG(target)  VTSS_IOREG(target,0x25)

/** 
 * \brief
 * This holds no.of 64-bit PMA clocks required to achieve specified quiet
 * time interval.
 * 
 * As per IEEE 803.3az-2010, min and max values are as follows:
 * 
 * MIN : 1.7 ms = 273926
 * MAX: 1.8 ms = 290039
 * 
 * Note: Default value is ~1.7 ms = 273926
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TQ_TIMER_REG . TX_TQ_TIMER
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TQ_TIMER_REG_TX_TQ_TIMER(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TQ_TIMER_REG_TX_TQ_TIMER     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TQ_TIMER_REG_TX_TQ_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief EEE TX Wake timer configuration register
 *
 * \details
 * This register value is used to elaps time in TX_WAKE state of EEE TX-FSM
 * as specified in IEEE802.3az-2010 clause 49.
 *
 * Register: \a PCS_10GBASE_R:EEE_TIMER_CFG:TX_TW_TIMER_REG
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TW_TIMER_REG(target)  VTSS_IOREG(target,0x26)

/** 
 * \brief
 * This holds no.of 64-bit PMA clocks required to achieve specified wake
 * time interval.
 * 
 * As per IEEE 803.3az-2010, min and max values are as follows:
 * 
 * MIN : 10.9 us = 1757
 * MAX: 11.1 us = 1788
 * 
 * Note: Default value is ~11 us = 1773
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TW_TIMER_REG . TX_TW_TIMER
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TW_TIMER_REG_TX_TW_TIMER(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TW_TIMER_REG_TX_TW_TIMER     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_PCS_10GBASE_R_EEE_TIMER_CFG_TX_TW_TIMER_REG_TX_TW_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief EEE RX Quiet timer configuration register
 *
 * \details
 * This register value is used to elaps time in RX_SLEEP and RX_QUIET
 * states of EEE RX-FSM as specified in IEEE802.3az-2010 clause 49.
 *
 * Register: \a PCS_10GBASE_R:EEE_TIMER_CFG:RX_TQ_TIMER_REG
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_RX_TQ_TIMER_REG(target)  VTSS_IOREG(target,0x27)

/** 
 * \brief
 * This holds no.of 64-bit PMA clocks required to achieve specified
 * sleep+quiet time interval.
 * 
 * As per IEEE 803.3az-2010, min and max values are as follows:
 * 
 * MIN : 2 ms = 322266
 * MAX: 3 ms = 483398
 * 
 * Note: Default value is ~2.5 ms = 402832
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_RX_TQ_TIMER_REG . RX_TQ_TIMER
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_TIMER_CFG_RX_TQ_TIMER_REG_RX_TQ_TIMER(x)  VTSS_ENCODE_BITFIELD(x,0,21)
#define  VTSS_M_PCS_10GBASE_R_EEE_TIMER_CFG_RX_TQ_TIMER_REG_RX_TQ_TIMER     VTSS_ENCODE_BITMASK(0,21)
#define  VTSS_X_PCS_10GBASE_R_EEE_TIMER_CFG_RX_TQ_TIMER_REG_RX_TQ_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,0,21)


/** 
 * \brief EEE RX Wake timer configuration register
 *
 * \details
 * This register value is used to elaps time in RX_WAKE state of EEE RX-FSM
 * as specified in IEEE802.3az-2010 clause 49.
 *
 * Register: \a PCS_10GBASE_R:EEE_TIMER_CFG:RX_TW_TIMER_REG
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_RX_TW_TIMER_REG(target)  VTSS_IOREG(target,0x28)

/** 
 * \brief
 * This holds no.of 64-bit PMA clocks required to achieve specified wake
 * time interval.
 * 
 * As per IEEE 803.3az-2010, this timer values are as follows:
 * 
 * Without scrambler bypassed (or Without FEC): 11.5 us = 1853
 * With scrambler bypassed (or With FEC): 13.7 us = 2207
 * 
 * Note: Default value is ~11.5 us = 1853
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_RX_TW_TIMER_REG . RX_TW_TIMER
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_TIMER_CFG_RX_TW_TIMER_REG_RX_TW_TIMER(x)  VTSS_ENCODE_BITFIELD(x,0,21)
#define  VTSS_M_PCS_10GBASE_R_EEE_TIMER_CFG_RX_TW_TIMER_REG_RX_TW_TIMER     VTSS_ENCODE_BITMASK(0,21)
#define  VTSS_X_PCS_10GBASE_R_EEE_TIMER_CFG_RX_TW_TIMER_REG_RX_TW_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,0,21)


/** 
 * \brief EEE RX Sleep timer configuration register
 *
 * \details
 * This register value is used to elaps time in RX_WTF state of EEE RX-FSM
 * as specified in IEEE802.3az-2010 clause 49.
 *
 * Register: \a PCS_10GBASE_R:EEE_TIMER_CFG:RX_WF_TIMER_REG
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_RX_WF_TIMER_REG(target)  VTSS_IOREG(target,0x29)

/** 
 * \brief
 * This holds no.of 64-bit PMA clocks required to achieve specified wake
 * time fault time interval.
 * 
 * As per IEEE 803.3az-2010, this value is:
 * 
 * MAX: 10 ms = 1611328
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_EEE_TIMER_CFG_RX_WF_TIMER_REG . RX_WF_TIMER
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_TIMER_CFG_RX_WF_TIMER_REG_RX_WF_TIMER(x)  VTSS_ENCODE_BITFIELD(x,0,21)
#define  VTSS_M_PCS_10GBASE_R_EEE_TIMER_CFG_RX_WF_TIMER_REG_RX_WF_TIMER     VTSS_ENCODE_BITMASK(0,21)
#define  VTSS_X_PCS_10GBASE_R_EEE_TIMER_CFG_RX_WF_TIMER_REG_RX_WF_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,0,21)

/**
 * Register Group: \a PCS_10GBASE_R:EEE_STATS
 *
 * Register group to indicate EEE FSM status
 */


/** 
 * \brief Wake Error Counter
 *
 * \details
 * Register: \a PCS_10GBASE_R:EEE_STATS:WAKE_ERR_CNT
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_EEE_STATS_WAKE_ERR_CNT(target)  VTSS_IOREG(target,0x2a)

/** 
 * \brief
 * This reflects wake_error_counter specifed in IEEE 802.3az-2010,
 * 49.2.13.2.4
 * 
 * Value of this counter indicates how many times LPI RX FSM entered RX_WTF
 * state.
 * Note:
 * 1. This counter is cleared when ever it is read.
 * 2. Upon overflow its value remains at 0xFFFF.
 *
 * \details 
 * Field: ::VTSS_PCS_10GBASE_R_EEE_STATS_WAKE_ERR_CNT . WAKE_ERR_CNT
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_STATS_WAKE_ERR_CNT_WAKE_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_10GBASE_R_EEE_STATS_WAKE_ERR_CNT_WAKE_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_10GBASE_R_EEE_STATS_WAKE_ERR_CNT_WAKE_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief EEE Status register
 *
 * \details
 * Register: \a PCS_10GBASE_R:EEE_STATS:EEE_STATUS
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_EEE_STATS_EEE_STATUS(target)  VTSS_IOREG(target,0x2b)

/** 
 * \brief
 * When read as a one, transmit PCS has received LPI signaling one or more
 * times
 * since the register was last read. When read as a zero, PCS has not
 * received LPI
 * signaling.
 *
 * \details 
 * 1 = Tx PCS has received LPI
 * 0 = LPI not received
 *
 * Field: ::VTSS_PCS_10GBASE_R_EEE_STATS_EEE_STATUS . TX_LPI_RECEIVED
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_TX_LPI_RECEIVED(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_TX_LPI_RECEIVED  VTSS_BIT(11)
#define  VTSS_X_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_TX_LPI_RECEIVED(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * When read as a one, receive PCS has received LPI signaling one or more
 * times
 * since the register was last read. When read as a zero, PCS has not
 * received LPI
 * signaling
 *
 * \details 
 * 1 = Rx PCS has received LPI
 * 0 = LPI not received
 *
 * Field: ::VTSS_PCS_10GBASE_R_EEE_STATS_EEE_STATUS . RX_LPI_RECEIVED
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_RX_LPI_RECEIVED(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_RX_LPI_RECEIVED  VTSS_BIT(10)
#define  VTSS_X_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_RX_LPI_RECEIVED(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \details 
 * 1 = Tx PCS is currently receiving LPI
 * 0 = PCS is not currently receiving LPI
 *
 * Field: ::VTSS_PCS_10GBASE_R_EEE_STATS_EEE_STATUS . TX_LPI_INDICATION
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_TX_LPI_INDICATION(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_TX_LPI_INDICATION  VTSS_BIT(9)
#define  VTSS_X_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_TX_LPI_INDICATION(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \details 
 * 1 = Rx PCS is currently receiving LPI
 * 0 = PCS is not currently receiving LPI
 *
 * Field: ::VTSS_PCS_10GBASE_R_EEE_STATS_EEE_STATUS . RX_LPI_INDICATION
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_RX_LPI_INDICATION(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_RX_LPI_INDICATION  VTSS_BIT(8)
#define  VTSS_X_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_RX_LPI_INDICATION(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \details 
 * 1 = The MAC may stop the clock during LPI
 * 0 = Clock not stoppable
 *
 * Field: ::VTSS_PCS_10GBASE_R_EEE_STATS_EEE_STATUS . CLOCK_STOP_CAPABLE
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_CLOCK_STOP_CAPABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_CLOCK_STOP_CAPABLE  VTSS_BIT(6)
#define  VTSS_X_PCS_10GBASE_R_EEE_STATS_EEE_STATUS_CLOCK_STOP_CAPABLE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief 10G Base-R PCS EEE interrupt mask register
 *
 * \details
 * Masks for 10G Base-R PCS EEE interrupt sources and sticky bits in
 * EEE_STATUS
 *
 * Register: \a PCS_10GBASE_R:EEE_STATS:EEE_INTR_MASK
 *
 * @param target A \a ::vtss_target_PCS_10GBASE_R_e target
 */
#define VTSS_PCS_10GBASE_R_EEE_STATS_EEE_INTR_MASK(target)  VTSS_IOREG(target,0x2c)

/** 
 * \brief
 * Mask for the TX_LPI_RECEIVED bit
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_EEE_STATS_EEE_INTR_MASK . TX_LPI_RECEIVED_MASK
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_STATS_EEE_INTR_MASK_TX_LPI_RECEIVED_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS_10GBASE_R_EEE_STATS_EEE_INTR_MASK_TX_LPI_RECEIVED_MASK  VTSS_BIT(4)
#define  VTSS_X_PCS_10GBASE_R_EEE_STATS_EEE_INTR_MASK_TX_LPI_RECEIVED_MASK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Mask for the RX_LPI_RECEIVED bit
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_PCS_10GBASE_R_EEE_STATS_EEE_INTR_MASK . RX_LPI_RECEIVED_MASK
 */
#define  VTSS_F_PCS_10GBASE_R_EEE_STATS_EEE_INTR_MASK_RX_LPI_RECEIVED_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS_10GBASE_R_EEE_STATS_EEE_INTR_MASK_RX_LPI_RECEIVED_MASK  VTSS_BIT(0)
#define  VTSS_X_PCS_10GBASE_R_EEE_STATS_EEE_INTR_MASK_RX_LPI_RECEIVED_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_JAGUAR2C_REGS_PCS_10GBASE_R_H_ */
