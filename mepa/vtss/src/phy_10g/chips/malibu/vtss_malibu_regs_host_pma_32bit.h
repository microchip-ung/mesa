// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_HOST_PMA_32BIT_H_
#define _VTSS_MALIBU_REGS_HOST_PMA_32BIT_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a HOST_PMA_32BIT
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a HOST_PMA_32BIT:SD10G65_APC
 *
 * SD10G65 APC Configuration and Status Register set
 */


/** 
 * \brief APC top control configuration register
 *
 * \details
 * Configuration register for top control logic
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_TOP_CTRL_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_TOP_CTRL_CFG  VTSS_IOREG(0x09, 1, 0xf000)

/** 
 * \brief
 * Delay time required to power up auxilliary channels
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_TOP_CTRL_CFG . PWR_UP_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_TOP_CTRL_CFG_PWR_UP_TIME(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_TOP_CTRL_CFG_PWR_UP_TIME     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_TOP_CTRL_CFG_PWR_UP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * Delay time required to power down auxilliary channels
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_TOP_CTRL_CFG . PWR_DN_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_TOP_CTRL_CFG_PWR_DN_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_TOP_CTRL_CFG_PWR_DN_TIME     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_TOP_CTRL_CFG_PWR_DN_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * APC top-control sleep-time (power-down). Given in number of clock cycles
 * (typically 2.5 ... 5 ns)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_TOP_CTRL_CFG . SLEEP_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_TOP_CTRL_CFG_SLEEP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_TOP_CTRL_CFG_SLEEP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_TOP_CTRL_CFG_SLEEP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC common configuration register 0
 *
 * \details
 * Common configurations 0 for APC logic. Note: For HML error correction
 * logic HML=000/001/011/111 are considered valid, 010 and 101 are
 * considered correctable (010 correctable to 011; 101 correctable to 001)
 * and 100 and 110 are considered incorrectable.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_COMMON_CFG0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0  VTSS_IOREG(0x09, 1, 0xf001)

/** 
 * \brief
 * Clear HML sampling error counter
 *
 * \details 
 * 1: Clear counter
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . HML_CLR_CNT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_HML_CLR_CNT  VTSS_BIT(31)

/** 
 * \brief
 * HML sampling error correction mode. Correctable sampling errors can be
 * automatically corrected.
 *
 * \details 
 * 0: Disable auto-correctin
 * 1: Enable auto-correction
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . HML_ERRCORR_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_HML_ERRCORR_MODE  VTSS_BIT(30)

/** 
 * \brief
 * HML sampling error correction enable. Invalid samples are not used for
 * parameter control (smart sampling).
 *
 * \details 
 * 0: Disable smart sampling
 * 1: Enable smart sampling
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . HML_ERRCORR_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_HML_ERRCORR_ENA  VTSS_BIT(29)

/** 
 * \brief
 * H/L swapping in HML sampling error correction logic
 *
 * \details 
 * 0: No H/L swapping
 * 1: H/L swapped
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . HML_SWAP_HL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_HML_SWAP_HL  VTSS_BIT(28)

/** 
 * \brief
 * Top-ctrl FSM recovery behavior
 *
 * \details 
 * 0: No auto-recovery
 * 1: Auto-restart on missing input signal after Restart-Delay-Timer has
 * expired
 * 2: Auto-restart on missing input signal
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . APC_FSM_RECOVER_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_APC_FSM_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_APC_FSM_RECOVER_MODE     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_APC_FSM_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * Signal detect valid configuration (Offs/AGC/L/C/DFE)
 *
 * \details 
 * 0: Signal_detect input directly used
 * 1: Signal_detect input gated with gain_ctrl ramp-up done
 * (EQZ_GAIN_CTRL_DONE)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . SIG_DET_VALID_CFG
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_SIG_DET_VALID_CFG  VTSS_BIT(25)

/** 
 * \brief
 * Signal lost delay timer configuration used for APC recovery. The signal
 * lost delay time specifies the time when a missing input signal is
 * considered a lost input signal on sig_det = 0. The delay time is T =
 * (2^sig_lost_delay_time) * T_rx_clk_per
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . SIG_LOST_DELAY_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_SIG_LOST_DELAY_TIME(x)  VTSS_ENCODE_BITFIELD(x,20,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_SIG_LOST_DELAY_TIME     VTSS_ENCODE_BITMASK(20,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_SIG_LOST_DELAY_TIME(x)  VTSS_EXTRACT_BITFIELD(x,20,5)

/** 
 * \brief
 * Current state of APC top control state machine
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . TOP_CTRL_STATE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_TOP_CTRL_STATE(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_TOP_CTRL_STATE     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_TOP_CTRL_STATE(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Select flexctrl block in order to read internal counters. Counter values
 * readable from APC_FLEXCTRL_CNT_STATUS.
 *
 * \details 
 * 0: Offset-ctrl
 * 1: L-ctrl
 * 2: C-ctrl
 * 3: AGC-ctrl
 * 4: DFE1-ctrl
 * 5: DFE2-ctrl
 * 6: DFE3-ctrl
 * 7: DFE4-ctrl
 * 8: SAM_Offset-cal
 * 9: Level-cal
 * 10: HML sampling errors
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . BLOCK_READ_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_BLOCK_READ_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_BLOCK_READ_SEL     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_BLOCK_READ_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Reset APC core logic (configuration registers are not reset)
 *
 * \details 
 * 1: Reset APC
 * 0: Normal operation (mission mode)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . RESET_APC
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_RESET_APC  VTSS_BIT(11)

/** 
 * \brief
 * Freeze current state
 *
 * \details 
 * 0: Normal operation
 * 1: Freeze APC
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . FREEZE_APC
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_FREEZE_APC  VTSS_BIT(10)

/** 
 * \brief
 * Interface bit-width
 *
 * \details 
 * 0: 8-bit
 * 1: 10-bit
 * 2: 16-bit
 * 3: 20-bit
 * 4: 32-bit
 * 5: 40-bit
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . IF_WIDTH
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_IF_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_IF_WIDTH     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_IF_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * APC throttling mode
 *
 * \details 
 * 0: Disable
 * no power reduction (continuous operation)
 * 1: Enable
 * power reduced operation (pulsed operation)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . THROTTLE_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_THROTTLE_MODE  VTSS_BIT(4)

/** 
 * \brief
 * Enable APC direct connections instead of local IB configuration
 * registers.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . APC_DIRECT_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_APC_DIRECT_ENA  VTSS_BIT(3)

/** 
 * \brief
 * APC operation mode
 *
 * \details 
 * 0: Off
 * 1: Manual mode
 * 2: Perform calibrarion and run FSM1
 * 3: Perform calibration and run FSM2
 * 4: Perform calibration and run FSM1 and FSM2 in ping-pong operation
 * 5: Perform calibration and then enter manual mode
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0 . APC_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_APC_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_APC_MODE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_APC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief APC parameter control synchronization register
 *
 * \details
 * Configuration register for common flexible parameter control FSMs
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_PARCTRL_SYNC_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG  VTSS_IOREG(0x09, 1, 0xf002)

/** 
 * \brief
 * Parameter control mode for FSM2
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM2_CTRL_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_CTRL_MODE  VTSS_BIT(15)

/** 
 * \brief
 * Parameter control mode for FSM1
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM1_CTRL_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_CTRL_MODE  VTSS_BIT(14)

/** 
 * \brief
 * FSM2 recovery behavior
 *
 * \details 
 * 0: No auto-recovery
 * 1: Freeze FSM2 on weak (eqz_gain > eqz_gain_freeze_thres) or missing
 * input signal
 * 2: Freeze FSM2 on weak signal and restart on missing input signal
 * 3: Freeze FSM2 on missing input signal
 * 4: Freeze FSM2 on missing input signal and auto-restart after
 * Restart-Delay-Timer has expired
 * 5: Auto-restart FSM2 on missing input signal
 * 6-7: Reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM2_RECOVER_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_RECOVER_MODE     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/** 
 * \brief
 * FSM1 recovery behavior
 *
 * \details 
 * 0: No auto-recovery
 * 1: Freeze FSM1 on weak (eqz_gain > eqz_gain_freeze_thres) or missing
 * input signal
 * 2: Freeze FSM1 on weak signal and restart on missing input signal
 * 3: Freeze FSM1 on missing input signal
 * 4: Freeze FSM1 on missing input signal and auto-restart after
 * Restart-Delay-Timer has expired
 * 5: Auto-restart FSM1 on missing input signal
 * 6-7: Reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM1_RECOVER_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_RECOVER_MODE     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Parameter control state of FSM2 in one-time mode
 *
 * \details 
 * 1: finished
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM2_CTRL_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_CTRL_DONE  VTSS_BIT(7)

/** 
 * \brief
 * Start operation of FSM2 (parameter update). Should be cleared afterwards
 * in One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM2_START_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_START_CTRL  VTSS_BIT(6)

/** 
 * \brief
 * Operation mode of FSM2
 *
 * \details 
 * 0: Off
 * 1: One-time
 * 2: Non-stop
 * 3: Paused
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM2_OP_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_OP_MODE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Parameter control state of FSM1 in one-time mode
 *
 * \details 
 * 1: finished
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM1_CTRL_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_CTRL_DONE  VTSS_BIT(3)

/** 
 * \brief
 * Start operation of FSM1 (parameter update). Should be cleared afterwards
 * in One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM1_START_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_START_CTRL  VTSS_BIT(2)

/** 
 * \brief
 * Operation mode of FSM1
 *
 * \details 
 * 0: Off
 * 1: One-time
 * 2: Non-stop
 * 3: Paused
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM1_OP_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC parctrl FSM1 Timer config
 *
 * \details
 * Timing configuration register for common flexible parameter control FSM1
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_PARCTRL_FSM1_TIMER_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG  VTSS_IOREG(0x09, 1, 0xf003)

/** 
 * \brief
 * FSM1 Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG . FSM1_PS_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG_FSM1_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG_FSM1_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG_FSM1_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * FSM1 Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG . FSM1_OP_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG_FSM1_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG_FSM1_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG_FSM1_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC parctrl FSM2 Timer config
 *
 * \details
 * Timing configuration register for common flexible parameter control FSM2
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_PARCTRL_FSM2_TIMER_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG  VTSS_IOREG(0x09, 1, 0xf004)

/** 
 * \brief
 * FSM2 Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG . FSM2_PS_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG_FSM2_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG_FSM2_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG_FSM2_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * FSM2 Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG . FSM2_OP_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG_FSM2_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG_FSM2_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG_FSM2_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC FLEXCTRL read counter register
 *
 * \details
 * Observation register for multiple counters. The selection is done via
 * APC_COMMON_CFG.BLOCK_READ_SEL (select flexctrl block to be read) and
 * APC_XXX_CTRL.XXX_READ_CNT_SEL (counter within flexctrl block XXX) or
 * APC_COMMON_CFG.OFFSCAL_READ_CNT_SEL. Note that the EQZ and DFE counters
 * hit_cnt and err_cnt make only sense in DISCRETE control mode.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_FLEXCTRL_CNT_STATUS
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_FLEXCTRL_CNT_STATUS  VTSS_IOREG(0x09, 1, 0xf005)


/** 
 * \brief APC level detect calibration configuration register
 *
 * \details
 * Configuration register for APC level detect calibrations logic
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_LD_CAL_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG  VTSS_IOREG(0x09, 1, 0xf006)

/** 
 * \brief
 * Calibration clock divider. Clock used in calibration blocks is divided
 * by 2^(2*CAL_CLK_DIV)
 *
 * \details 
 * 0: No clock division
 * 1: Clock is divided by 4
 * 2: Clock is divided by 16
 * ...
 * 7: Clock is divided by 16384
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG . CAL_CLK_DIV
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG_CAL_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,28,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG_CAL_CLK_DIV     VTSS_ENCODE_BITMASK(28,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG_CAL_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,28,3)

/** 
 * \brief
 * Detect level calibration state
 *
 * \details 
 * 1: finished
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG . DETLEV_CAL_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG_DETLEV_CAL_DONE  VTSS_BIT(19)

/** 
 * \brief
 * Skip signal detect calibration
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG . SKIP_SDET_CAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG_SKIP_SDET_CAL  VTSS_BIT(12)

/** 
 * \brief
 * Skip level detect calibration
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG . SKIP_LD_CAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG_SKIP_LD_CAL  VTSS_BIT(11)

/** 
 * \brief
 * Level for IE signal detect (when controlled by APC)
 *
 * \details 
 * 0: 20mV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG . IE_SDET_LEVEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG_IE_SDET_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG_IE_SDET_LEVEL     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG_IE_SDET_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/** 
 * \brief
 * Timer for calibration process
 *
 * \details 
 * 14: Use for 400MHz rx_clk
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG . DETLVL_TIMER
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG_DETLVL_TIMER(x)  VTSS_ENCODE_BITFIELD(x,1,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG_DETLVL_TIMER     VTSS_ENCODE_BITMASK(1,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG_DETLVL_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,1,4)

/** 
 * \brief
 * Start signal and level detect calibration process (sampling stage; only
 * in manual mode, see apc_mode)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG . START_DETLVL_CAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LD_CAL_CFG_START_DETLVL_CAL  VTSS_BIT(0)


/** 
 * \brief APC sampling stage calibration configuration register 0
 *
 * \details
 * Configuration register 0 for APC sampling stage calibrations logic
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_IS_CAL_CFG0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0  VTSS_IOREG(0x09, 1, 0xf007)

/** 
 * \brief
 * Gain adjustent for DFE amplifier
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0 . IB_DFE_GAIN_ADJ
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_IB_DFE_GAIN_ADJ(x)  VTSS_ENCODE_BITFIELD(x,20,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_IB_DFE_GAIN_ADJ     VTSS_ENCODE_BITMASK(20,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_IB_DFE_GAIN_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,20,6)

/** 
 * \brief
 * Initial value for CP/MD FF threshold calibration.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0 . CPMD_THRES_INIT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_CPMD_THRES_INIT(x)  VTSS_ENCODE_BITFIELD(x,14,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_CPMD_THRES_INIT     VTSS_ENCODE_BITMASK(14,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_CPMD_THRES_INIT(x)  VTSS_EXTRACT_BITFIELD(x,14,6)

/** 
 * \brief
 * Initial value for VScope FF threshold calibration.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0 . VSC_THRES_INIT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_VSC_THRES_INIT(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_VSC_THRES_INIT     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_VSC_THRES_INIT(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Skip observe block initialization
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_OBSERVE_INIT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OBSERVE_INIT  VTSS_BIT(7)

/** 
 * \brief
 * Skip sample FF offset initialization
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_OFFSET_INIT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OFFSET_INIT  VTSS_BIT(6)

/** 
 * \brief
 * Skip sample FF threshold initialization
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_THRESHOLD_INIT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_THRESHOLD_INIT  VTSS_BIT(5)

/** 
 * \brief
 * Skip DFE buffer 0db initialization
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_DFE_BUFFER_INIT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_DFE_BUFFER_INIT  VTSS_BIT(4)

/** 
 * \brief
 * Skip observe block calibration
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_OBSERVE_CAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OBSERVE_CAL  VTSS_BIT(3)

/** 
 * \brief
 * Skip sample FF offset calibration
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_OFFSET_CAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OFFSET_CAL  VTSS_BIT(2)

/** 
 * \brief
 * Skip sample FF threshold calibration
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_THRESHOLD_CAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_THRESHOLD_CAL  VTSS_BIT(1)

/** 
 * \brief
 * Skip DFE buffer 0db calibration
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_DFE_BUFFER_CAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_DFE_BUFFER_CAL  VTSS_BIT(0)


/** 
 * \brief APC sampling stage calibration configuration register 1
 *
 * \details
 * Configuration register 1 for APC sampling stage calibrations logic
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_IS_CAL_CFG1
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1  VTSS_IOREG(0x09, 1, 0xf008)

/** 
 * \brief
 * Controls number of calibrations iterations to settle values that depend
 * on each other (offset vs threshold). Coding number of iterations =
 * cal_num_iterations + 1.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1 . CAL_NUM_ITERATIONS
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_CAL_NUM_ITERATIONS(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_CAL_NUM_ITERATIONS     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_CAL_NUM_ITERATIONS(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Selects the number of ones threshold when using parallel data. Value for
 * rising ramp from zero to one. The value for the falling ramp (one ->
 * zero) is half the interface width minus par_data_num_ones_thres.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1 . PAR_DATA_NUM_ONES_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_PAR_DATA_NUM_ONES_THRES(x)  VTSS_ENCODE_BITFIELD(x,9,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_PAR_DATA_NUM_ONES_THRES     VTSS_ENCODE_BITMASK(9,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_PAR_DATA_NUM_ONES_THRES(x)  VTSS_EXTRACT_BITFIELD(x,9,5)

/** 
 * \brief
 * Controls whether the parallel data from the deserializer or the signal
 * from the observe multiplexer in the sample stage is used. Coding: 0:
 * observe multiplexer, 1: parallel data.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1 . PAR_DATA_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_PAR_DATA_SEL  VTSS_BIT(8)

/** 
 * \brief
 * Select offset calibration result to be read (BLOCK_READ_SEL = 8
 * required)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1 . OFFSCAL_READ_CNT_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,3,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_READ_CNT_SEL     VTSS_ENCODE_BITMASK(3,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,5)

/** 
 * \brief
 * Swaps disp with disn used during calibration
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1 . OFFSCAL_DIS_SWAP
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_DIS_SWAP  VTSS_BIT(2)

/** 
 * \brief
 * Offset calibration state
 *
 * \details 
 * 1: finished
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1 . OFFSCAL_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_DONE  VTSS_BIT(1)

/** 
 * \brief
 * Start offset calibration process (sampling stage; only in manual mode,
 * see apc_mode)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1 . START_OFFSCAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_START_OFFSCAL  VTSS_BIT(0)


/** 
 * \brief APC EQZ CTRL config
 *
 * \details
 * Configuration register for gain control logic
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_COMMON_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG  VTSS_IOREG(0x09, 1, 0xf009)

/** 
 * \brief
 * Gain freeze threshold, used in APC recovery mode for low input signals
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_FREEZE_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_FREEZE_THRES(x)  VTSS_ENCODE_BITFIELD(x,13,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_FREEZE_THRES     VTSS_ENCODE_BITMASK(13,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_FREEZE_THRES(x)  VTSS_EXTRACT_BITFIELD(x,13,10)

/** 
 * \brief
 * Gain recovery behavior
 *
 * \details 
 * 0: No auto-recovery
 * 1: Freeze gain on missing input signal and auto-restart after
 * Restart-Delay-Timer has expired
 * 2: Auto-restart Gain control on missing input signal
 * 3: Reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_RECOVER_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_RECOVER_MODE     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * Stop update of gain_adj
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_ADJ_HALT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_ADJ_HALT  VTSS_BIT(10)

/** 
 * \brief
 * Gain calibration mode
 *
 * \details 
 * 0: Use successive approximation to find required gain
 * 1: use max gain and reduce linearly to find required gain
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_CAL_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_CAL_MODE  VTSS_BIT(9)

/** 
 * \brief
 * Start (initiate) gain_adj update process (on rising edge of cfg bit)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_ADJ_START_UPDATE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_ADJ_START_UPDATE  VTSS_BIT(8)

/** 
 * \brief
 * Start (initiate) gain update process (on rising edge of cfg bit)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_START_UPDATE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_START_UPDATE  VTSS_BIT(7)

/** 
 * \brief
 * (Re-)start (initiate) main gain/gain_adj calibration process (on rising
 * edge of cfg bit)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_START_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_START_CTRL  VTSS_BIT(6)

/** 
 * \brief
 * Operation mode (only when EQZ_GAIN_STOP_CTRL = 1)
 *
 * \details 
 * 0: Idle
 * 1: Calibrate and work
 * 2: Work
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_OP_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_OP_MODE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Stop main gain control machine immediately
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_STOP_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_STOP_CTRL  VTSS_BIT(3)

/** 
 * \brief
 * Restart gain/gain_adj calibration automatically on rising edge of
 * signal_detect
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_AUTO_RESTART
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_AUTO_RESTART  VTSS_BIT(2)

/** 
 * \brief
 * Parameter change mode
 *
 * \details 
 * 0: Automatic update
 * 1: Preset (use PAR_INI as fix value
 * internal processing continues)
 * 2: Freeze (internal processing stops
 * parameter stays at current value)
 * 3: No update (internal processing continues but parameter is not
 * updated)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_CHG_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_CHG_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC EQZ CTRL configuration register
 *
 * \details
 * Configuration register for gain
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_GAIN_CTRL_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG  VTSS_IOREG(0x09, 1, 0xf00a)

/** 
 * \brief
 * Maximum gain in normal operation (should be not greater then 895
 * (512+3*128-1)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG . EQZ_GAIN_MAX
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_MAX(x)  VTSS_ENCODE_BITFIELD(x,20,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_MAX     VTSS_ENCODE_BITMASK(20,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_MAX(x)  VTSS_EXTRACT_BITFIELD(x,20,10)

/** 
 * \brief
 * Minimum gain in normal operation
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG . EQZ_GAIN_MIN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_MIN(x)  VTSS_ENCODE_BITFIELD(x,10,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_MIN     VTSS_ENCODE_BITMASK(10,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_MIN(x)  VTSS_EXTRACT_BITFIELD(x,10,10)

/** 
 * \brief
 * Gain initial value (used if EQZ_GAIN_CHG_MODE = 1)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG . EQZ_GAIN_INI
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_INI(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_INI     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief APC EQZ ADJ CTRL configuration register
 *
 * \details
 * Configuration register for gain_adj
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_GAIN_ADJ_CTRL_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG  VTSS_IOREG(0x09, 1, 0xf00b)

/** 
 * \brief
 * Maximum gain_adj in normal operation
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG . EQZ_GAIN_ADJ_MAX
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_MAX(x)  VTSS_ENCODE_BITFIELD(x,20,7)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_MAX     VTSS_ENCODE_BITMASK(20,7)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_MAX(x)  VTSS_EXTRACT_BITFIELD(x,20,7)

/** 
 * \brief
 * Minimum gain_adj in normal operation
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG . EQZ_GAIN_ADJ_MIN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_MIN(x)  VTSS_ENCODE_BITFIELD(x,10,7)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_MIN     VTSS_ENCODE_BITMASK(10,7)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_MIN(x)  VTSS_EXTRACT_BITFIELD(x,10,7)

/** 
 * \brief
 * Gain_adj initial value (used if EQZ_GAIN_CHG_MODE = 1)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG . EQZ_GAIN_ADJ_INI
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_INI(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_INI     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief APC EQZ CTRL status register
 *
 * \details
 * Observation register for controlled settings
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_CTRL_STATUS
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS  VTSS_IOREG(0x09, 1, 0xf00c)

/** 
 * \brief
 * Status flag indicating main gain/gain_adj ramp-up process has finished
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS . EQZ_GAIN_CTRL_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_CTRL_DONE  VTSS_BIT(23)

/** 
 * \brief
 * Parameter value (controlled/computed gain adjustment value)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS . EQZ_GAIN_ADJ_ACTVAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ADJ_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ADJ_ACTVAL     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ADJ_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \brief
 * Parameter value (controlled/computed gain value)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS . EQZ_GAIN_ACTVAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,6,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ACTVAL     VTSS_ENCODE_BITMASK(6,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,6,10)

/** 
 * \brief
 * Parameter value (controlled/computed level for level-detect logic)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS . LD_LEV_ACTVAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS_LD_LEV_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS_LD_LEV_ACTVAL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_CTRL_STATUS_LD_LEV_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief APC EQZ LD control
 *
 * \details
 * Configuration register for level-detect (LD) control, timing and
 * behavior (timing: number of rx_clk cycles, used for LD toggling)
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_LD_CTRL
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL  VTSS_IOREG(0x09, 1, 0xf00d)

/** 
 * \brief
 * Captured toggling of LD-EQ
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL . LD_EQ_TOGGLE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_EQ_TOGGLE  VTSS_BIT(31)

/** 
 * \brief
 * Captured toggling of LD-IB
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL . LD_IB_TOGGLE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_IB_TOGGLE  VTSS_BIT(30)

/** 
 * \brief
 * Bypass LD catch circuitry (allows capturing pulses shorter then one
 * rx_clk cycle)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL . LD_CATCH_BYPASS
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_CATCH_BYPASS  VTSS_BIT(29)

/** 
 * \brief
 * Max value for LD updates in gain_adjust (watch-dog; prevent endless loop
 * of LD adjustment; max is 2^value - 1)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL . LD_WD_CNT_MAX
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_WD_CNT_MAX(x)  VTSS_ENCODE_BITFIELD(x,26,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_WD_CNT_MAX     VTSS_ENCODE_BITMASK(26,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_WD_CNT_MAX(x)  VTSS_EXTRACT_BITFIELD(x,26,3)

/** 
 * \brief
 * Number of required toggles before toggling is considered valid
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL . LD_TOG_THRESHOLD
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_TOG_THRESHOLD(x)  VTSS_ENCODE_BITFIELD(x,22,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_TOG_THRESHOLD     VTSS_ENCODE_BITMASK(22,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_TOG_THRESHOLD(x)  VTSS_EXTRACT_BITFIELD(x,22,4)

/** 
 * \brief
 * Sensitivity deadtime between two toggles (value is multiplied by 2)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL . LD_T_TOGGLE_DEADTIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_T_TOGGLE_DEADTIME(x)  VTSS_ENCODE_BITFIELD(x,14,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_T_TOGGLE_DEADTIME     VTSS_ENCODE_BITMASK(14,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_T_TOGGLE_DEADTIME(x)  VTSS_EXTRACT_BITFIELD(x,14,8)

/** 
 * \brief
 * Update internal LD_lev value with LD_LEV_INI
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL . LD_LEV_UPDATE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_LEV_UPDATE  VTSS_BIT(8)

/** 
 * \brief
 * Start (initiate) a LD-EQ toggle check (for present LD-level)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL . LD_EQ_START_TOG_CHK
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_EQ_START_TOG_CHK  VTSS_BIT(7)

/** 
 * \brief
 * Start (initiate) a LD-IB toggle check (for present LD-level)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL . LD_IB_START_TOG_CHK
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_IB_START_TOG_CHK  VTSS_BIT(6)

/** 
 * \brief
 * LD_lev initial value (used as preset value if EQZ_GAIN_CHG_MODE = 1)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL . LD_LEV_INI
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_LEV_INI(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_LEV_INI     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_LD_LEV_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief APC EQZ LD CTRL config0
 *
 * \details
 * Configuration register 0 for level-detect (LD) controller timing (number
 * of rx_clk cycles, used for operation timing). Important note: For small
 * ld_t_* values it might be necessary to change IB configuration bit-group
 * IB_LDSD_DIVSEL to higher values!
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_LD_CTRL_CFG0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0  VTSS_IOREG(0x09, 1, 0xf00e)

/** 
 * \brief
 * Minimum activity for LD in work mode (value is multiplied by 8)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0 . LD_T_DEADTIME_WRK
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0_LD_T_DEADTIME_WRK(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0_LD_T_DEADTIME_WRK     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0_LD_T_DEADTIME_WRK(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Activity timeout threshold for LD in work mode (value is multiplied by
 * 8)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0 . LD_T_TIMEOUT_WRK
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0_LD_T_TIMEOUT_WRK(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0_LD_T_TIMEOUT_WRK     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0_LD_T_TIMEOUT_WRK(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC EQZ LD CTRL config1
 *
 * \details
 * Configuration register 1 for level-detect (LD) controller timing (number
 * of rx_clk cycles, used for calibration timing). Important note: For
 * small ld_t_* values it might be necessary to change IB configuration
 * bit-group IB_LDSD_DIVSEL to higher values!
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_LD_CTRL_CFG1
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1  VTSS_IOREG(0x09, 1, 0xf00f)

/** 
 * \brief
 * Minimum activity for LD in calibration mode (value is multiplied by 8)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1 . LD_T_DEADTIME_CAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1_LD_T_DEADTIME_CAL(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1_LD_T_DEADTIME_CAL     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1_LD_T_DEADTIME_CAL(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Activity timeout threshold for LD in calibration mode (value is
 * multiplied by 8)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1 . LD_T_TIMEOUT_CAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1_LD_T_TIMEOUT_CAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1_LD_T_TIMEOUT_CAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1_LD_T_TIMEOUT_CAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC EQZ Pattern matching cfg register0
 *
 * \details
 * Pattern matching configuration register for eqz_c and eqz_l control
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_PAT_MATCH_CFG0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0  VTSS_IOREG(0x09, 1, 0xf010)

/** 
 * \brief
 * EQZ-C-control pattern mask (only those bits are used for pattern
 * matching whose mask bit is set)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0 . EQZ_C_PAT_MASK
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_C_PAT_MASK(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_C_PAT_MASK     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_C_PAT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * EQZ-C-control pattern used for pattern matching (corresponding mask bits
 * must be set)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0 . EQZ_C_PAT_MATCH
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_C_PAT_MATCH(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_C_PAT_MATCH     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_C_PAT_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * EQZ-L-control pattern mask (only those bits are used for pattern
 * matching whose mask bit is set)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0 . EQZ_L_PAT_MASK
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_L_PAT_MASK(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_L_PAT_MASK     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_L_PAT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * EQZ-L-control pattern used for pattern matching (corresponding mask bits
 * must be set)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0 . EQZ_L_PAT_MATCH
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_L_PAT_MATCH(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_L_PAT_MATCH     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_L_PAT_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC EQZ Pattern matching cfg register1
 *
 * \details
 * Pattern matching configuration register for eqz_offs and eqz_agc control
 * Note, if mask is set to 0, all bits are "matching" and taken into
 * account for parameter contol.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_PAT_MATCH_CFG1
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1  VTSS_IOREG(0x09, 1, 0xf011)

/** 
 * \brief
 * EQZ-Offset-control pattern mask (only those bits are used for pattern
 * matching whose mask bit is set)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1 . EQZ_OFFS_PAT_MASK
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_OFFS_PAT_MASK(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_OFFS_PAT_MASK     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_OFFS_PAT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * EQZ-Offset-control pattern used for pattern matching (corresponding mask
 * bits must be set)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1 . EQZ_OFFS_PAT_MATCH
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_OFFS_PAT_MATCH(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_OFFS_PAT_MATCH     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_OFFS_PAT_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * EQZ-AGC-control pattern mask (only those bits are used for pattern
 * matching whose mask bit is set)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1 . EQZ_AGC_PAT_MASK
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_AGC_PAT_MASK(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_AGC_PAT_MASK     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_AGC_PAT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * EQZ-AGC-control pattern used for pattern matching (corresponding mask
 * bits must be set)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1 . EQZ_AGC_PAT_MATCH
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_AGC_PAT_MATCH(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_AGC_PAT_MATCH     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_AGC_PAT_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC EQZ_OFFS Control registers
 *
 * \details
 * General behavior control for EQZ_OFFS parameter control.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_OFFS_CTRL
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL  VTSS_IOREG(0x09, 1, 0xf012)

/** 
 * \brief
 * EQZ_OFFS recovery behavior
 *
 * \details 
 * 0: No auto-recovery
 * 1: Freeze EQZ_OFFS on weak (eqz_gain > eqz_gain_freeze_thres) or missing
 * input signal
 * 2: Freeze EQZ_OFFS on weak signal and restart on missing input signal
 * 3: Freeze EQZ_OFFS on missing input signal
 * 4: Freeze EQZ_OFFS on missing input signal and auto-restart after
 * Restart-Delay-Timer has expired
 * 5: Auto-restart EQZ_OFFS on missing input signal
 * 6-7: Reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_RECOVER_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_CTRL_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_DONE  VTSS_BIT(26)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_ACTVAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Synchronization mode
 *
 * \details 
 * 0: Independent
 * 1: Attached to parctrl FSM 1
 * 2: Attached to parctrl FSM 2
 * 3: Attached to both parctrl FSMs
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_SYNC_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: eqz_offs_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_READ_CNT_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for EQZ_OFFS parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_CTRL_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_MODE  VTSS_BIT(10)

/** 
 * \brief
 * Alternative threshold for EQZ_OFFS parameter (controller goal: err_cnt =
 * 0.5*EQZ_OFFS_THRES)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_CTRL_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for EQZ_OFFS parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_CTRL_THRES_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_THRES_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_START_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_START_CTRL  VTSS_BIT(2)

/** 
 * \brief
 * Operation mode
 *
 * \details 
 * 0: Off
 * 1: One-time
 * 2: Non-stop
 * 3: Paused
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_OP_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC EQZ_OFFS Timer config
 *
 * \details
 * Configuration registers for EQZ_OFFS controller timing.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_OFFS_TIMER_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG  VTSS_IOREG(0x09, 1, 0xf013)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG . EQZ_OFFS_PS_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG_EQZ_OFFS_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG_EQZ_OFFS_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG_EQZ_OFFS_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG . EQZ_OFFS_OP_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG_EQZ_OFFS_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG_EQZ_OFFS_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG_EQZ_OFFS_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC EQZ_OFFS Parameter control register
 *
 * \details
 * Configuration register for controlled EQZ_OFFS parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_OFFS_PAR_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG  VTSS_IOREG(0x09, 1, 0xf014)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG . EQZ_OFFS_DIR_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_DIR_SEL  VTSS_BIT(31)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG . EQZ_OFFS_RANGE_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

/** 
 * \brief
 * Parameter change mode
 *
 * \details 
 * 0: Automatic update
 * 1: Preset (use EQZ_OFFS_INI as fix value
 * internal processing continues)
 * 2: Freeze (internal processing stops
 * parameter stays at current value)
 * 3: No update (internal processing continues but parameter is not
 * updated)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG . EQZ_OFFS_CHG_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG . EQZ_OFFS_MAX
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG . EQZ_OFFS_MIN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG . EQZ_OFFS_INI
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC EQZ_C Control registers
 *
 * \details
 * General behavior control for EQZ_C parameter control.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_C_CTRL
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL  VTSS_IOREG(0x09, 1, 0xf015)

/** 
 * \brief
 * EQZ_C recovery behavior
 *
 * \details 
 * 0: No auto-recovery
 * 1: Freeze EQZ_C on weak (eqz_gain > eqz_gain_freeze_thres) or missing
 * input signal
 * 2: Freeze EQZ_C on weak signal and restart on missing input signal
 * 3: Freeze EQZ_C on missing input signal
 * 4: Freeze EQZ_C on missing input signal and auto-restart after
 * Restart-Delay-Timer has expired
 * 5: Auto-restart EQZ_C on missing input signal
 * 6-7: Reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_RECOVER_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_CTRL_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_DONE  VTSS_BIT(26)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_ACTVAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Synchronization mode
 *
 * \details 
 * 0: Independent
 * 1: Attached to parctrl FSM 1
 * 2: Attached to parctrl FSM 2
 * 3: Attached to both parctrl FSMs
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_SYNC_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: eqz_c_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_READ_CNT_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for EQZ_C parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_CTRL_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_MODE  VTSS_BIT(10)

/** 
 * \brief
 * Alternative threshold for EQZ_C parameter (controller goal: err_cnt =
 * 0.5*EQZ_C_THRES)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_CTRL_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for EQZ_C parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_CTRL_THRES_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_THRES_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_START_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_START_CTRL  VTSS_BIT(2)

/** 
 * \brief
 * Operation mode
 *
 * \details 
 * 0: Off
 * 1: One-time
 * 2: Non-stop
 * 3: Paused
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_OP_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC EQZ_C Timer config
 *
 * \details
 * Configuration registers for EQZ_C controller timing.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_C_TIMER_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_TIMER_CFG  VTSS_IOREG(0x09, 1, 0xf016)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_TIMER_CFG . EQZ_C_PS_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_TIMER_CFG_EQZ_C_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_TIMER_CFG_EQZ_C_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_TIMER_CFG_EQZ_C_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_TIMER_CFG . EQZ_C_OP_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_TIMER_CFG_EQZ_C_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_TIMER_CFG_EQZ_C_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_TIMER_CFG_EQZ_C_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC EQZ_C Parameter control register
 *
 * \details
 * Configuration register for controlled EQZ_C parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_C_PAR_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG  VTSS_IOREG(0x09, 1, 0xf017)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG . EQZ_C_DIR_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_DIR_SEL  VTSS_BIT(31)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG . EQZ_C_RANGE_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

/** 
 * \brief
 * Parameter change mode
 *
 * \details 
 * 0: Automatic update
 * 1: Preset (use EQZ_C_INI as fix value
 * internal processing continues)
 * 2: Freeze (internal processing stops
 * parameter stays at current value)
 * 3: No update (internal processing continues but parameter is not
 * updated)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG . EQZ_C_CHG_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG . EQZ_C_MAX
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG . EQZ_C_MIN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG . EQZ_C_INI
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC EQZ_L Control registers
 *
 * \details
 * General behavior control for EQZ_L parameter control.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_L_CTRL
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL  VTSS_IOREG(0x09, 1, 0xf018)

/** 
 * \brief
 * EQZ_L recovery behavior
 *
 * \details 
 * 0: No auto-recovery
 * 1: Freeze EQZ_L on weak (eqz_gain > eqz_gain_freeze_thres) or missing
 * input signal
 * 2: Freeze EQZ_L on weak signal and restart on missing input signal
 * 3: Freeze EQZ_L on missing input signal
 * 4: Freeze EQZ_L on missing input signal and auto-restart after
 * Restart-Delay-Timer has expired
 * 5: Auto-restart EQZ_L on missing input signal
 * 6-7: Reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_RECOVER_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_CTRL_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_DONE  VTSS_BIT(26)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_ACTVAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Synchronization mode
 *
 * \details 
 * 0: Independent
 * 1: Attached to parctrl FSM 1
 * 2: Attached to parctrl FSM 2
 * 3: Attached to both parctrl FSMs
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_SYNC_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: eqz_l_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_READ_CNT_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for EQZ_L parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_CTRL_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_MODE  VTSS_BIT(10)

/** 
 * \brief
 * Alternative threshold for EQZ_L parameter (controller goal: err_cnt =
 * 0.5*EQZ_L_THRES)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_CTRL_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for EQZ_L parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_CTRL_THRES_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_THRES_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_START_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_START_CTRL  VTSS_BIT(2)

/** 
 * \brief
 * Operation mode
 *
 * \details 
 * 0: Off
 * 1: One-time
 * 2: Non-stop
 * 3: Paused
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_OP_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC EQZ_L Timer config
 *
 * \details
 * Configuration registers for EQZ_L controller timing.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_L_TIMER_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_TIMER_CFG  VTSS_IOREG(0x09, 1, 0xf019)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_TIMER_CFG . EQZ_L_PS_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_TIMER_CFG_EQZ_L_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_TIMER_CFG_EQZ_L_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_TIMER_CFG_EQZ_L_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_TIMER_CFG . EQZ_L_OP_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_TIMER_CFG_EQZ_L_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_TIMER_CFG_EQZ_L_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_TIMER_CFG_EQZ_L_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC EQZ_L Parameter control register
 *
 * \details
 * Configuration register for controlled EQZ_L parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_L_PAR_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG  VTSS_IOREG(0x09, 1, 0xf01a)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG . EQZ_L_DIR_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_DIR_SEL  VTSS_BIT(31)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG . EQZ_L_RANGE_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

/** 
 * \brief
 * Parameter change mode
 *
 * \details 
 * 0: Automatic update
 * 1: Preset (use EQZ_L_INI as fix value
 * internal processing continues)
 * 2: Freeze (internal processing stops
 * parameter stays at current value)
 * 3: No update (internal processing continues but parameter is not
 * updated)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG . EQZ_L_CHG_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG . EQZ_L_MAX
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG . EQZ_L_MIN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG . EQZ_L_INI
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC EQZ_AGC Control registers
 *
 * \details
 * General behavior control for EQZ_AGC parameter control.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_AGC_CTRL
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL  VTSS_IOREG(0x09, 1, 0xf01b)

/** 
 * \brief
 * EQZ_AGC recovery behavior
 *
 * \details 
 * 0: No auto-recovery
 * 1: Freeze EQZ_AGC on weak (eqz_gain > eqz_gain_freeze_thres) or missing
 * input signal
 * 2: Freeze EQZ_AGC on weak signal and restart on missing input signal
 * 3: Freeze EQZ_AGC on missing input signal
 * 4: Freeze EQZ_AGC on missing input signal and auto-restart after
 * Restart-Delay-Timer has expired
 * 5: Auto-restart EQZ_AGC on missing input signal
 * 6-7: Reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_RECOVER_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_CTRL_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_DONE  VTSS_BIT(26)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_ACTVAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Synchronization mode
 *
 * \details 
 * 0: Independent
 * 1: Attached to parctrl FSM 1
 * 2: Attached to parctrl FSM 2
 * 3: Attached to both parctrl FSMs
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_SYNC_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: eqz_agc_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_READ_CNT_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for EQZ_AGC parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_CTRL_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_MODE  VTSS_BIT(10)

/** 
 * \brief
 * Alternative threshold for EQZ_AGC parameter (controller goal: err_cnt =
 * 0.5*EQZ_AGC_THRES)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_CTRL_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for EQZ_AGC parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_CTRL_THRES_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_THRES_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_START_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_START_CTRL  VTSS_BIT(2)

/** 
 * \brief
 * Operation mode
 *
 * \details 
 * 0: Off
 * 1: One-time
 * 2: Non-stop
 * 3: Paused
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_OP_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC EQZ_AGC Timer config
 *
 * \details
 * Configuration registers for EQZ_AGC controller timing.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_AGC_TIMER_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG  VTSS_IOREG(0x09, 1, 0xf01c)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG . EQZ_AGC_PS_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG_EQZ_AGC_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG_EQZ_AGC_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG_EQZ_AGC_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG . EQZ_AGC_OP_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG_EQZ_AGC_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG_EQZ_AGC_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG_EQZ_AGC_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC EQZ_AGC Parameter control register
 *
 * \details
 * Configuration register for controlled EQZ_AGC parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_EQZ_AGC_PAR_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG  VTSS_IOREG(0x09, 1, 0xf01d)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG . EQZ_AGC_DIR_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_DIR_SEL  VTSS_BIT(31)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG . EQZ_AGC_RANGE_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

/** 
 * \brief
 * Parameter change mode
 *
 * \details 
 * 0: Automatic update
 * 1: Preset (use EQZ_AGC_INI as fix value
 * internal processing continues)
 * 2: Freeze (internal processing stops
 * parameter stays at current value)
 * 3: No update (internal processing continues but parameter is not
 * updated)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG . EQZ_AGC_CHG_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG . EQZ_AGC_MAX
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG . EQZ_AGC_MIN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG . EQZ_AGC_INI
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC DFE1 Control registers
 *
 * \details
 * General behavior control for DFE1 parameter control.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_DFE1_CTRL
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL  VTSS_IOREG(0x09, 1, 0xf01e)

/** 
 * \brief
 * DFE1 recovery behavior
 *
 * \details 
 * 0: No auto-recovery
 * 1: Freeze DFE1 on weak (eqz_gain > eqz_gain_freeze_thres) or missing
 * input signal
 * 2: Freeze DFE1 on weak signal and restart on missing input signal
 * 3: Freeze DFE1 on missing input signal
 * 4: Freeze DFE1 on missing input signal and auto-restart after
 * Restart-Delay-Timer has expired
 * 5: Auto-restart DFE1 on missing input signal
 * 6-7: Reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL . DFE1_RECOVER_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL . DFE1_CTRL_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_DONE  VTSS_BIT(26)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL . DFE1_ACTVAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Synchronization mode
 *
 * \details 
 * 0: Independent
 * 1: Attached to parctrl FSM 1
 * 2: Attached to parctrl FSM 2
 * 3: Attached to both parctrl FSMs
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL . DFE1_SYNC_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: dfe1_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL . DFE1_READ_CNT_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for DFE1 parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL . DFE1_CTRL_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_MODE  VTSS_BIT(10)

/** 
 * \brief
 * Alternative threshold for DFE1 parameter (controller goal: err_cnt =
 * 0.5*DFE1_THRES)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL . DFE1_CTRL_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for DFE1 parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL . DFE1_CTRL_THRES_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_THRES_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL . DFE1_START_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_START_CTRL  VTSS_BIT(2)

/** 
 * \brief
 * Operation mode
 *
 * \details 
 * 0: Off
 * 1: One-time
 * 2: Non-stop
 * 3: Paused
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL . DFE1_OP_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_CTRL_DFE1_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC DFE1 Timer config
 *
 * \details
 * Configuration registers for DFE1 controller timing.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_DFE1_TIMER_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_TIMER_CFG  VTSS_IOREG(0x09, 1, 0xf01f)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_TIMER_CFG . DFE1_PS_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_TIMER_CFG_DFE1_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_TIMER_CFG_DFE1_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_TIMER_CFG_DFE1_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_TIMER_CFG . DFE1_OP_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_TIMER_CFG_DFE1_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_TIMER_CFG_DFE1_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_TIMER_CFG_DFE1_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC DFE1 Parameter control register
 *
 * \details
 * Configuration register for controlled DFE1 parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_DFE1_PAR_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG  VTSS_IOREG(0x09, 1, 0xf020)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG . DFE1_DIR_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_DIR_SEL  VTSS_BIT(31)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG . DFE1_RANGE_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

/** 
 * \brief
 * Parameter change mode
 *
 * \details 
 * 0: Automatic update
 * 1: Preset (use DFE1_INI as fix value
 * internal processing continues)
 * 2: Freeze (internal processing stops
 * parameter stays at current value)
 * 3: No update (internal processing continues but parameter is not
 * updated)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG . DFE1_CHG_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG . DFE1_MAX
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG . DFE1_MIN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG . DFE1_INI
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC DFE2 Control registers
 *
 * \details
 * General behavior control for DFE2 parameter control.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_DFE2_CTRL
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL  VTSS_IOREG(0x09, 1, 0xf021)

/** 
 * \brief
 * DFE2 recovery behavior
 *
 * \details 
 * 0: No auto-recovery
 * 1: Freeze DFE2 on weak (eqz_gain > eqz_gain_freeze_thres) or missing
 * input signal
 * 2: Freeze DFE2 on weak signal and restart on missing input signal
 * 3: Freeze DFE2 on missing input signal
 * 4: Freeze DFE2 on missing input signal and auto-restart after
 * Restart-Delay-Timer has expired
 * 5: Auto-restart DFE2 on missing input signal
 * 6-7: Reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL . DFE2_RECOVER_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL . DFE2_CTRL_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_DONE  VTSS_BIT(26)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL . DFE2_ACTVAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Synchronization mode
 *
 * \details 
 * 0: Independent
 * 1: Attached to parctrl FSM 1
 * 2: Attached to parctrl FSM 2
 * 3: Attached to both parctrl FSMs
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL . DFE2_SYNC_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: dfe2_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL . DFE2_READ_CNT_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for DFE2 parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL . DFE2_CTRL_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_MODE  VTSS_BIT(10)

/** 
 * \brief
 * Alternative threshold for DFE2 parameter (controller goal: err_cnt =
 * 0.5*DFE2_THRES)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL . DFE2_CTRL_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for DFE2 parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL . DFE2_CTRL_THRES_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_THRES_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL . DFE2_START_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_START_CTRL  VTSS_BIT(2)

/** 
 * \brief
 * Operation mode
 *
 * \details 
 * 0: Off
 * 1: One-time
 * 2: Non-stop
 * 3: Paused
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL . DFE2_OP_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_CTRL_DFE2_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC DFE2 Timer config
 *
 * \details
 * Configuration registers for DFE2 controller timing.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_DFE2_TIMER_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_TIMER_CFG  VTSS_IOREG(0x09, 1, 0xf022)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_TIMER_CFG . DFE2_PS_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_TIMER_CFG_DFE2_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_TIMER_CFG_DFE2_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_TIMER_CFG_DFE2_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_TIMER_CFG . DFE2_OP_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_TIMER_CFG_DFE2_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_TIMER_CFG_DFE2_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_TIMER_CFG_DFE2_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC DFE2 Parameter control register
 *
 * \details
 * Configuration register for controlled DFE2 parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_DFE2_PAR_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG  VTSS_IOREG(0x09, 1, 0xf023)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG . DFE2_DIR_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_DIR_SEL  VTSS_BIT(31)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG . DFE2_RANGE_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

/** 
 * \brief
 * Parameter change mode
 *
 * \details 
 * 0: Automatic update
 * 1: Preset (use DFE2_INI as fix value
 * internal processing continues)
 * 2: Freeze (internal processing stops
 * parameter stays at current value)
 * 3: No update (internal processing continues but parameter is not
 * updated)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG . DFE2_CHG_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG . DFE2_MAX
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG . DFE2_MIN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG . DFE2_INI
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC DFE3 Control registers
 *
 * \details
 * General behavior control for DFE3 parameter control.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_DFE3_CTRL
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL  VTSS_IOREG(0x09, 1, 0xf024)

/** 
 * \brief
 * DFE3 recovery behavior
 *
 * \details 
 * 0: No auto-recovery
 * 1: Freeze DFE3 on weak (eqz_gain > eqz_gain_freeze_thres) or missing
 * input signal
 * 2: Freeze DFE3 on weak signal and restart on missing input signal
 * 3: Freeze DFE3 on missing input signal
 * 4: Freeze DFE3 on missing input signal and auto-restart after
 * Restart-Delay-Timer has expired
 * 5: Auto-restart DFE3 on missing input signal
 * 6-7: Reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL . DFE3_RECOVER_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL . DFE3_CTRL_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_DONE  VTSS_BIT(26)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL . DFE3_ACTVAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Synchronization mode
 *
 * \details 
 * 0: Independent
 * 1: Attached to parctrl FSM 1
 * 2: Attached to parctrl FSM 2
 * 3: Attached to both parctrl FSMs
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL . DFE3_SYNC_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: dfe3_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL . DFE3_READ_CNT_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for DFE3 parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL . DFE3_CTRL_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_MODE  VTSS_BIT(10)

/** 
 * \brief
 * Alternative threshold for DFE3 parameter (controller goal: err_cnt =
 * 0.5*DFE3_THRES)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL . DFE3_CTRL_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for DFE3 parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL . DFE3_CTRL_THRES_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_THRES_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL . DFE3_START_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_START_CTRL  VTSS_BIT(2)

/** 
 * \brief
 * Operation mode
 *
 * \details 
 * 0: Off
 * 1: One-time
 * 2: Non-stop
 * 3: Paused
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL . DFE3_OP_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_CTRL_DFE3_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC DFE3 Timer config
 *
 * \details
 * Configuration registers for DFE3 controller timing.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_DFE3_TIMER_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_TIMER_CFG  VTSS_IOREG(0x09, 1, 0xf025)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_TIMER_CFG . DFE3_PS_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_TIMER_CFG_DFE3_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_TIMER_CFG_DFE3_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_TIMER_CFG_DFE3_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_TIMER_CFG . DFE3_OP_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_TIMER_CFG_DFE3_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_TIMER_CFG_DFE3_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_TIMER_CFG_DFE3_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC DFE3 Parameter control register
 *
 * \details
 * Configuration register for controlled DFE3 parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_DFE3_PAR_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG  VTSS_IOREG(0x09, 1, 0xf026)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG . DFE3_DIR_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_DIR_SEL  VTSS_BIT(31)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG . DFE3_RANGE_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

/** 
 * \brief
 * Parameter change mode
 *
 * \details 
 * 0: Automatic update
 * 1: Preset (use DFE3_INI as fix value
 * internal processing continues)
 * 2: Freeze (internal processing stops
 * parameter stays at current value)
 * 3: No update (internal processing continues but parameter is not
 * updated)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG . DFE3_CHG_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG . DFE3_MAX
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG . DFE3_MIN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG . DFE3_INI
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC DFE4 Control registers
 *
 * \details
 * General behavior control for DFE4 parameter control.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_DFE4_CTRL
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL  VTSS_IOREG(0x09, 1, 0xf027)

/** 
 * \brief
 * DFE4 recovery behavior
 *
 * \details 
 * 0: No auto-recovery
 * 1: Freeze DFE4 on weak (eqz_gain > eqz_gain_freeze_thres) or missing
 * input signal
 * 2: Freeze DFE4 on weak signal and restart on missing input signal
 * 3: Freeze DFE4 on missing input signal
 * 4: Freeze DFE4 on missing input signal and auto-restart after
 * Restart-Delay-Timer has expired
 * 5: Auto-restart DFE4 on missing input signal
 * 6-7: Reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL . DFE4_RECOVER_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL . DFE4_CTRL_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_DONE  VTSS_BIT(26)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL . DFE4_ACTVAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Synchronization mode
 *
 * \details 
 * 0: Independent
 * 1: Attached to parctrl FSM 1
 * 2: Attached to parctrl FSM 2
 * 3: Attached to both parctrl FSMs
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL . DFE4_SYNC_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: dfe4_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL . DFE4_READ_CNT_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for DFE4 parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL . DFE4_CTRL_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_MODE  VTSS_BIT(10)

/** 
 * \brief
 * Alternative threshold for DFE4 parameter (controller goal: err_cnt =
 * 0.5*DFE4_THRES)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL . DFE4_CTRL_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for DFE4 parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL . DFE4_CTRL_THRES_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_THRES_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL . DFE4_START_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_START_CTRL  VTSS_BIT(2)

/** 
 * \brief
 * Operation mode
 *
 * \details 
 * 0: Off
 * 1: One-time
 * 2: Non-stop
 * 3: Paused
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL . DFE4_OP_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_CTRL_DFE4_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC DFE4 Timer config
 *
 * \details
 * Configuration registers for DFE4 controller timing.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_DFE4_TIMER_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_TIMER_CFG  VTSS_IOREG(0x09, 1, 0xf028)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_TIMER_CFG . DFE4_PS_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_TIMER_CFG_DFE4_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_TIMER_CFG_DFE4_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_TIMER_CFG_DFE4_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_TIMER_CFG . DFE4_OP_TIME
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_TIMER_CFG_DFE4_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_TIMER_CFG_DFE4_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_TIMER_CFG_DFE4_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC DFE4 Parameter control register
 *
 * \details
 * Configuration register for controlled DFE4 parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_APC:APC_DFE4_PAR_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG  VTSS_IOREG(0x09, 1, 0xf029)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG . DFE4_DIR_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_DIR_SEL  VTSS_BIT(31)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG . DFE4_RANGE_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

/** 
 * \brief
 * Parameter change mode
 *
 * \details 
 * 0: Automatic update
 * 1: Preset (use DFE4_INI as fix value
 * internal processing continues)
 * 2: Freeze (internal processing stops
 * parameter stays at current value)
 * 3: No update (internal processing continues but parameter is not
 * updated)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG . DFE4_CHG_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG . DFE4_MAX
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG . DFE4_MIN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG . DFE4_INI
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a HOST_PMA_32BIT:SD10G65_DES
 *
 * SD10G65 DES Configuration and Status Register set
 */


/** 
 * \brief SD10G65 DES Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 DES.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_DES:SD10G65_DES_CFG0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0  VTSS_IOREG(0x09, 1, 0xf100)

/** 
 * \brief
 * Invert output of high auxillary deserializer
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0 . DES_INV_H
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0_DES_INV_H  VTSS_BIT(7)

/** 
 * \brief
 * Invert output of low auxillary deserializer
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0 . DES_INV_L
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0_DES_INV_L  VTSS_BIT(6)

/** 
 * \brief
 * Invert output of main deserializer
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0 . DES_INV_M
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0_DES_INV_M  VTSS_BIT(5)

/** 
 * \brief
 * Interface width
 *
 * \details 
 * 0: 8
 * 1: 10
 * 2: 16 (energy efficient)
 * 3: 20 (energy efficient)
 * 4: 32
 * 5: 40
 * 6: 16 bit (fast)
 * 7: 20 bit (fast)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0 . DES_IF_MODE_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0_DES_IF_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0_DES_IF_MODE_SEL     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0_DES_IF_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/** 
 * \brief
 * Auxillary deserializer channels disable.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0 . DES_VSC_DIS
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0_DES_VSC_DIS  VTSS_BIT(1)

/** 
 * \brief
 * Deserializer disable.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0 . DES_DIS
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_DES_SD10G65_DES_CFG0_DES_DIS  VTSS_BIT(0)


/** 
 * \brief SD10G65 MOEBDIV Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 MoebiusDivider
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_DES:SD10G65_MOEBDIV_CFG0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0  VTSS_IOREG(0x09, 1, 0xf101)

/** 
 * \brief
 * Bandwidth selection for cp/md of cdr loop when core NOT flags valid data
 * detected
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0 . MOEBDIV_BW_CDR_SEL_A
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_A(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_A     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_A(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * Bandwidth selection for cp/md of cdr loop when core flags valid data
 * detected
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0 . MOEBDIV_BW_CDR_SEL_B
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_B(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_B     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_B(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Bandwidth selection for cp/md signals towards core
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0 . MOEBDIV_BW_CORE_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CORE_SEL(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CORE_SEL     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CORE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * CP/MD swapping
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0 . MOEBDIV_CPMD_SWAP
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_CPMD_SWAP  VTSS_BIT(2)

/** 
 * \brief
 * MD divider enable
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0 . MOEBDIV_DIV32_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_DIV32_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Divider disable
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0 . MOEBDIV_DIS
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_DIS  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PMA_32BIT:SD10G65_OB
 *
 * SD10G65 OB Configuration and Status Register set
 */


/** 
 * \brief SD10G65 OB Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 OB.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_OB:SD10G65_OB_CFG0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0  VTSS_IOREG(0x09, 1, 0xf110)

/** 
 * \brief
 * Invert input to serializer
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0 . SER_INV
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_SER_INV  VTSS_BIT(23)

/** 
 * \brief
 * Control of common mode voltage of clock buffer between synthesizer and
 * OB.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0 . CLK_BUF_CMV
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_CLK_BUF_CMV(x)  VTSS_ENCODE_BITFIELD(x,21,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_CLK_BUF_CMV     VTSS_ENCODE_BITMASK(21,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_CLK_BUF_CMV(x)  VTSS_EXTRACT_BITFIELD(x,21,2)

/** 
 * \brief
 * Set digital part into pseudo reset
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0 . RST
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_RST  VTSS_BIT(17)

/** 
 * \brief
 * Enable pad loop
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0 . EN_PAD_LOOP
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_EN_PAD_LOOP  VTSS_BIT(16)

/** 
 * \brief
 * Enable input loop
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0 . EN_INP_LOOP
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_EN_INP_LOOP  VTSS_BIT(15)

/** 
 * \brief
 * Enable direct path
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0 . EN_DIRECT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_EN_DIRECT  VTSS_BIT(14)

/** 
 * \brief
 * Enable output buffer and serializer
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0 . EN_OB
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_EN_OB  VTSS_BIT(13)

/** 
 * \brief
 * Selects amplitude range controled via levn. See description of levn.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0 . INCR_LEVN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_INCR_LEVN  VTSS_BIT(8)

/** 
 * \brief
 * Interface width
 *
 * \details 
 * 0: 8
 * 1: 10
 * 2: 16
 * 3: 20
 * 4: 32
 * 5: 40
 * 6-7: Reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0 . SEL_IFW
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_SEL_IFW(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_SEL_IFW     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_SEL_IFW(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * Amplitude control value. Step size is 25 mVpp, decreasing amplitude with
 * increasing control value. Range depends on incr_levn. Coding for
 * incr_levn=0: 31: 500mVpp, 30: 525mVpp, 29: 550mVpp, ..., 0: 1275mVpp.
 * Coding for incr_levn=1: 31: 300mVpp, 30: 325mVpp, 29: 350mVpp, .., 0:
 * 1075mVpp. (Note: maximum achievable amplitude depends on the supply
 * voltage)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0 . LEVN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_LEVN(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_LEVN     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG0_LEVN(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief SD10G65 OB Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 OB.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_OB:SD10G65_OB_CFG1
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1  VTSS_IOREG(0x09, 1, 0xf111)

/** 
 * \brief
 * Enable amplitude compensation of AB bleed current
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1 . AB_COMP_EN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_AB_COMP_EN  VTSS_BIT(26)

/** 
 * \brief
 * Bleed current for class AB operation of driver
 *
 * \details 
 * 0: 1%
 * 1: 0.5%
 * 2: 2%
 * 3: reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1 . DIODE_CUR
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_DIODE_CUR(x)  VTSS_ENCODE_BITFIELD(x,23,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_DIODE_CUR     VTSS_ENCODE_BITMASK(23,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_DIODE_CUR(x)  VTSS_EXTRACT_BITFIELD(x,23,3)

/** 
 * \brief
 * Level shift ctrl of class AB bias generator
 *
 * \details 
 * 0: 50mV
 * 1: 100mV
 * 2:150mV
 * 3: 200mV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1 . LEV_SHFT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_LEV_SHFT(x)  VTSS_ENCODE_BITFIELD(x,21,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_LEV_SHFT     VTSS_ENCODE_BITMASK(21,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_LEV_SHFT(x)  VTSS_EXTRACT_BITFIELD(x,21,2)

/** 
 * \brief
 * Slew rate ctrl of OB (R), encoding see PREDRV_C_CTRL
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1 . PREDRV_R_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_PREDRV_R_CTRL(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_PREDRV_R_CTRL     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_PREDRV_R_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * Slew rate ctrl of OB (C)
 *
 * \details 
 * C=3 R=3: 25ps
 * C=3 R=0: 35ps
 * C=0 R=3: 55ps
 * C=1 R=0: 70ps
 * C=0 R=0: 120 ps
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1 . PREDRV_C_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_PREDRV_C_CTRL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_PREDRV_C_CTRL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_PREDRV_C_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Tail voltage driver settings
 *
 * \details 
 * 0: reserved
 * 1: 75mV
 * 2: 100mV
 * 4: 125mV
 * 8: 150mV
 * 16: 175mV
 * 32: 200mV
 * Intermediate values possible when setting two bits
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1 . VTAIL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_VTAIL(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_VTAIL     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_VTAIL(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Ctrl of cascade volt in drv stage
 *
 * \details 
 * 0: reserved
 * 1: 0
 * 2: 1/12
 * 4: 2/12
 * 8: 3/12
 * 16: 4/12
 * Intermediate values possible when setting two bits
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1 . VCAS
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_VCAS(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_VCAS     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_VCAS(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Additional resistor calibration trim
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1 . R_COR
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_R_COR  VTSS_BIT(4)

/** 
 * \brief
 * Offset resistance adjustment for CML cells (two-complement)
 *
 * \details 
 * 1000: -8
 * 1111: -1
 * 0000: 0
 * 0111: 7
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1 . R_I
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_R_I(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_R_I     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG1_R_I(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SD10G65 OB Configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 OB. D_filter contains four 6-bit
 * precalculated DA input values. Please note the differences in
 * programming for various interface (IF) bit widths. For calculation
 * details see documentation of OB10G.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_OB:SD10G65_OB_CFG2
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG2  VTSS_IOREG(0x09, 1, 0xf112)

/** 
 * \brief
 * Transmit filter coefficients for FIR taps. Suggested start value (no
 * emphasis, max amplitude)
 *
 * \details 
 * 0x820820: for I/F width 8/10 bits
 * 0x7DF820: for I/F width 16/20/32/40 bits
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG2 . D_FILTER
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG2_D_FILTER(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG2_D_FILTER     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG2_D_FILTER(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief SD10G65 OB Configuration register 3  access to receiver detect functionality
 *
 * \details
 * Configuration register 3 for SD10G65 OB.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_OB:SD10G65_OB_CFG3
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG3  VTSS_IOREG(0x09, 1, 0xf113)

/** 
 * \brief
 * Indicates a completed receiver detect measurement. Should be one few us
 * after rec_det_start is set.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG3 . REC_DET_DONE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_DONE  VTSS_BIT(18)

/** 
 * \brief
 * Rising edge starts receiver detect measurement. Has to be keept set
 * until rec_det_value has been read.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG3 . REC_DET_START
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_START  VTSS_BIT(17)

/** 
 * \brief
 * Enable reciver detect function. MUST be disabled for normal operation
 * !!!
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG3 . REC_DET_ENABLE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_ENABLE  VTSS_BIT(16)

/** 
 * \brief
 * Holds the time between the start and the flag of the receiver detect
 * measuremnet. Time [ns +/- 4 ns] = 8 * value - 12
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG3 . REC_DET_VALUE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_VALUE(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_VALUE     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief SD10G65 SBUS TX CFG Service-Bus related setting
 *
 * \details
 * Configuration register for Service-Bus related setting. Note: this
 * register is only used for configuration if Tx is used stand alone,
 * otherwise SD10G65_SBUS_RX_CFG (Rx macro) is used for configuration!
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_OB:SD10G65_SBUS_TX_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG  VTSS_IOREG(0x09, 1, 0xf114)


/** 
 * \brief SD10G65_TX subversion revision number
 *
 * \details
 * Subversion revision number for the RTL used in SD10G65_TX
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_OB:SD10G65_TX_SVN_ID
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_SVN_ID  VTSS_IOREG(0x09, 1, 0xf115)


/** 
 * \brief SD10G65_TX Revision ID
 *
 * \details
 * Revision numbers of the analog sub IPs used in the SD10G65_TX
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_OB:SD10G65_TX_REV_ID
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID  VTSS_IOREG(0x09, 1, 0xf116)

/** 
 * \brief
 * Feature set number of output buffer (ob10g_N)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID . OB_REV_ID
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID_OB_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,20,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID_OB_REV_ID     VTSS_ENCODE_BITMASK(20,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID_OB_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,20,6)

/** 
 * \brief
 * Feature set number of synthesizer (syn_N)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID . SYNTH_REV_ID
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID_SYNTH_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,14,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID_SYNTH_REV_ID     VTSS_ENCODE_BITMASK(14,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID_SYNTH_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,14,6)

/** 
 * \brief
 * Feature set number of RC-PLL (pll10g_N)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID . RCPLL_REV_ID
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID_RCPLL_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID_RCPLL_REV_ID     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID_RCPLL_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Feature set number of Toplevel (sd10g65_N)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID . TOP_REV_ID
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID_TOP_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID_TOP_REV_ID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_OB_SD10G65_TX_REV_ID_TOP_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a HOST_PMA_32BIT:SD10G65_IB
 *
 * SD10G65 IB Configuration and Status Register set
 */


/** 
 * \brief SD10G65 IB Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 IB. Note: Configuration bit-grp
 * IB_CLKDIV_ENA was named IB_VSCOPE_CLK_ENA in an early revision of the
 * input buffer.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_IB_CFG0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0  VTSS_IOREG(0x09, 1, 0xf120)

/** 
 * \brief
 * Offset resistance adjustment for CML cells (two-complement)
 *
 * \details 
 * 1000: -8
 * 1111: -1
 * 0000: 0
 * 0111: 7
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_RCML_ADJ
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_RCML_ADJ(x)  VTSS_ENCODE_BITFIELD(x,27,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_RCML_ADJ     VTSS_ENCODE_BITMASK(27,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_RCML_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,27,4)

/** 
 * \brief
 * Select termination voltage
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_TERM_V_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_TERM_V_SEL(x)  VTSS_ENCODE_BITFIELD(x,23,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_TERM_V_SEL     VTSS_ENCODE_BITMASK(23,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_TERM_V_SEL(x)  VTSS_EXTRACT_BITFIELD(x,23,4)

/** 
 * \brief
 * Enable common mode termination
 *
 * \details 
 * 0: no common mode termination (only AC-common mode termination)
 * 1: termination to VDDI
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_TERM_VDD_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_TERM_VDD_ENA  VTSS_BIT(22)

/** 
 * \brief
 * Shifts resistance adjustment value ib_rib_adj by +1
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_RIB_SHIFT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_RIB_SHIFT  VTSS_BIT(21)

/** 
 * \brief
 * Offset resistance adjustment for termination (two-complement)
 *
 * \details 
 * 1000: -8
 * 1111: -1
 * 0000: 0
 * 0111: 7
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_RIB_ADJ
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_RIB_ADJ(x)  VTSS_ENCODE_BITFIELD(x,17,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_RIB_ADJ     VTSS_ENCODE_BITMASK(17,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_RIB_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,17,4)

/** 
 * \brief
 * Enable DFE stage (gates IB_ISEL_DFE)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_DFE_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_DFE_ENA  VTSS_BIT(14)

/** 
 * \brief
 * Select input buffer input signal
 *
 * \details 
 * 0: normal operation
 * 1: -6dB input
 * 2: OB->IB data loop or test signal
 * 3: RESERVED
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_SIG_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_SIG_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_SIG_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_SIG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Controls Bulk Voltage of High Speed Cells
 *
 * \details 
 * 0: High
 * 1: Low (mission mode)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_VBULK_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_VBULK_SEL  VTSS_BIT(11)

/** 
 * \brief
 * Enable for IA including ACJtag
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_IA_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_IA_ENA  VTSS_BIT(10)

/** 
 * \brief
 * Enable for IA signal detect circuit (IB_SDET_SEL = 0 required)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_IA_SDET_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_IA_SDET_ENA  VTSS_BIT(9)

/** 
 * \brief
 * Enable for IA signal detect circuit (IB_SDET_SEL = 1 required)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_IE_SDET_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_IE_SDET_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Enable for level detect circuit
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_LD_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_LD_ENA  VTSS_BIT(7)

/** 
 * \brief
 * Enable for 1V mode
 *
 * \details 
 * 0: VDDI=1.2V
 * 1: VDDI=1.0V
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_1V_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_1V_ENA  VTSS_BIT(6)

/** 
 * \brief
 * Enable clock dividers in sampling stag
 *
 * \details 
 * 0: Disable (use in double rate mode)
 * 1: Enable (use in full rate mode)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_CLKDIV_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_CLKDIV_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Enable VScope Path of Sampling-Stage
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_VSCOPE_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_VSCOPE_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Enable SAMpling stage
 *
 * \details 
 * 0: Disable
 * 1: Enable (mission mode)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_SAM_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_SAM_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Enable EQualiZation stage
 *
 * \details 
 * 0: Disable
 * 1: Enable (mission mode)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0 . IB_EQZ_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG0_IB_EQZ_ENA  VTSS_BIT(1)


/** 
 * \brief SD10G65 IB Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 IB.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_IB_CFG1
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1  VTSS_IOREG(0x09, 1, 0xf121)

/** 
 * \brief
 * Inductor peaking of 1. stage Input buffer
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking > 3db at 8GHz
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1 . IB_AMP_L
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_AMP_L(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_AMP_L     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_AMP_L(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * Inductor peaking of EQ-Buffer0 (over all 2. stage)
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking > 3db at 8GHz
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1 . IB_EQZ_L0
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L0(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L0     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L0(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/** 
 * \brief
 * Inductor peaking of EQ-Buffer1 (over all 3. stage)
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking > 3dB at 8GHz
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1 . IB_EQZ_L1
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L1(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L1     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L1(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * Inductor peaking of EQ-Buffer2 (over all 4. stage)
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking > 3dB at 8GHz
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1 . IB_EQZ_L2
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L2(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L2     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L2(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Inductor peaking of EQ-Buffer3 (over all 5. stage)
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking > 3dB at 8GHz
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1 . IB_AGC_L
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_AGC_L(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_AGC_L     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_AGC_L(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * C-gain peaking for IB-stage
 *
 * \details 
 * 0: no peaking
 * 7: max. peaking
 * corner frequency adjustment with ib_eqz_c_adj_ib
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1 . IB_AMP_C
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_AMP_C(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_AMP_C     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_AMP_C(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * C-gain peaking for EQ-stage0
 *
 * \details 
 * 0: no peaking
 * 7: max. peaking
 * corner frequency adjustment with ib_eqz_c_adj_es0
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1 . IB_EQZ_C0
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C0(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C0     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C0(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * C-gain peaking for EQ-stage1
 *
 * \details 
 * 0: no peaking
 * 7: max. peaking
 * corner frequency adjustment with ib_eqz_c_adj_es1
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1 . IB_EQZ_C1
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C1(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C1     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C1(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * C-gain peaking for EQ-stage2
 *
 * \details 
 * 0: no peaking
 * 7: max. peaking
 * corner frequency adjustment with ib_eqz_c_adj_es2
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1 . IB_EQZ_C2
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C2(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C2     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C2(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief SD10G65 IB Configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 IB.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_IB_CFG2
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG2  VTSS_IOREG(0x09, 1, 0xf122)

/** 
 * \brief
 * Gain of Input Buffer
 *
 * \details 
 * 0-511 gain adjustment only in first stage > 511 gain in first stage at
 * max.
 * 512-639 gain in 2.stage increased from 1 to 2 > 639 gain = 2
 * 640-767 gain in 3.stage increased from 1 to 2 > 767 gain = 2
 * 768-895 gain in 4.stage increased from 1 to 2
 * >895 gain at max.
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG2 . IB_EQZ_GAIN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_GAIN(x)  VTSS_ENCODE_BITFIELD(x,18,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_GAIN     VTSS_ENCODE_BITMASK(18,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_GAIN(x)  VTSS_EXTRACT_BITFIELD(x,18,10)

/** 
 * \brief
 * Amplification (gain) of AGC in Input Buffer (normal operation)
 *
 * \details 
 * after gain calibration
 * 0: gain = 0.3
 * 255: gain = 1.5
 * if disp/disn is active dac function for dfe gain calibration
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG2 . IB_EQZ_AGC
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_AGC(x)  VTSS_ENCODE_BITFIELD(x,10,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_AGC     VTSS_ENCODE_BITMASK(10,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_AGC(x)  VTSS_EXTRACT_BITFIELD(x,10,8)

/** 
 * \brief
 * Offset value for IB-stage of Input Buffer
 *
 * \details 
 * 512: neutral
 * > 512: positive
 * < 512: negative
 * range +/- 600mV (low gain) to +/-30mV (high gain)
 * gain dependent offset sensitivity requiered for Base line wander
 * compensation
 * not supported in test chip
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG2 . IB_EQZ_OFFSET
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_OFFSET     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief SD10G65 IB Configuration register 3
 *
 * \details
 * Configuration register 1 for SD10G65 IB. Note: the behavior of
 * IB_EQ_LD1_OFFSET changes when APC is disabled. In this case
 * IB_EQ_LD1_OFFSET directly controls the level for Level-Detect circuitry
 * 1. Coding: 0: 20mV, 1: 25mV, ... 63: 340mV.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_IB_CFG3
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3  VTSS_IOREG(0x09, 1, 0xf123)

/** 
 * \brief
 * Dividing factor for SDET and LD circuits of IE.
 *
 * \details 
 * 0: 128
 * 1: 32
 * 2: 8
 * 3: 4
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3 . IB_LDSD_DIVSEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_LDSD_DIVSEL(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_LDSD_DIVSEL     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_LDSD_DIVSEL(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/** 
 * \brief
 * Clock dividing factor for Signal Detect circuit of IA
 *
 * \details 
 * 0: 2
 * ...
 * 7: 256
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3 . IB_SDET_CLK_DIV
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_SDET_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_SDET_CLK_DIV     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_SDET_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Force Signal-Detect output to high level
 *
 * \details 
 * 0: Normal operation
 * 1: Force sigdet high
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3 . IB_SET_SDET
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_SET_SDET  VTSS_BIT(26)

/** 
 * \brief
 * Selects source of signal detect (ib_X_sdet_ena must be enabled
 * accordingly)
 *
 * \details 
 * 0: IA
 * 1: IE
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3 . IB_SDET_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_SDET_SEL  VTSS_BIT(24)

/** 
 * \brief
 * Selects source of direct data path to core
 *
 * \details 
 * 0: IE
 * 1: IA
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3 . IB_DIRECT_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_DIRECT_SEL  VTSS_BIT(23)

/** 
 * \brief
 * With APC enabled level offset (6bit-signed) compared to IB_EQ_LD0_LEVEL
 * for Level-Detect circuitry 1. Saturating between 20mV and 340mV. See
 * also note in register description.
 *
 * \details 
 * 0: no offset
 * 1: +5mV
 * 31: +155mV
 * 63(= -1): -5mV
 * 32(= -32): -160mV.
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3 . IB_EQ_LD1_OFFSET
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_EQ_LD1_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,17,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_EQ_LD1_OFFSET     VTSS_ENCODE_BITMASK(17,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_EQ_LD1_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,17,6)

/** 
 * \brief
 * Level for Level-Detect circuitry 0.
 *
 * \details 
 * 0: 20mV
 * 1: 25mV
 * ...
 * 40: 220mV
 * ...
 * 63: 340mV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3 . IB_EQ_LD0_LEVEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_EQ_LD0_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,11,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_EQ_LD0_LEVEL     VTSS_ENCODE_BITMASK(11,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_EQ_LD0_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,11,6)

/** 
 * \brief
 * Threshold value for IE Signal-Detect.
 *
 * \details 
 * 0: 20mV
 * 1: 25mV
 * 2: 30mV
 * ...
 * 63: 340mV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3 . IB_IE_SDET_LEVEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_IE_SDET_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_IE_SDET_LEVEL     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_IE_SDET_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/** 
 * \brief
 * Threshold value for IA Signal-Detect.
 *
 * \details 
 * 0: 0mV
 * ...
 * 8: 80mV
 * ...
 * 31: 310mV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3 . IB_IA_SDET_LEVEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_IA_SDET_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_IA_SDET_LEVEL     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG3_IB_IA_SDET_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief SD10G65 IB Configuration register 4
 *
 * \details
 * Configuration register 4 for SD10G65 IB.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_IB_CFG4
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4  VTSS_IOREG(0x09, 1, 0xf124)

/** 
 * \brief
 * corner frequency selection for c-gain peaking 1.stage
 *
 * \details 
 * 0: lowest corner frequency
 * 3: highest corner frequency
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4 . IB_EQZ_C_ADJ_IB
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_IB(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_IB     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_IB(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/** 
 * \brief
 * corner frequency selection for c-gain peaking 2.stage
 *
 * \details 
 * 0: lowest corner frequency
 * 3: highest corner frequency
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4 . IB_EQZ_C_ADJ_ES2
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES2(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES2     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES2(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/** 
 * \brief
 * corner frequency selection for c-gain peaking 3.stage
 *
 * \details 
 * 0: lowest corner frequency
 * 3: highest corner frequency
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4 . IB_EQZ_C_ADJ_ES1
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES1(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES1     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES1(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * corner frequency selection for c-gain peaking 4.stage
 *
 * \details 
 * 0: lowest corner frequency
 * 3: highest corner frequency
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4 . IB_EQZ_C_ADJ_ES0
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES0(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES0     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES0(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Coder mode: APC L value to IE inductance
 *
 * \details 
 * 0: equ. distributed (double step 3->4)
 * 1: equ. distributed (no change 6+7)
 * 2: 1st buffer max - 2nd buffer max - ...
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4 . IB_EQZ_L_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_L_MODE(x)  VTSS_ENCODE_BITFIELD(x,21,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_L_MODE     VTSS_ENCODE_BITMASK(21,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_L_MODE(x)  VTSS_EXTRACT_BITFIELD(x,21,3)

/** 
 * \brief
 * Coder mode: APC C value to IE capacitance
 *
 * \details 
 * 0: equ. distributed
 * 2: 1st buffer max - 2nd buffer max - ...
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4 . IB_EQZ_C_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_MODE(x)  VTSS_ENCODE_BITFIELD(x,18,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_MODE     VTSS_ENCODE_BITMASK(18,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_MODE(x)  VTSS_EXTRACT_BITFIELD(x,18,3)

/** 
 * \brief
 * Threshold value (offset) for vscope-high sampling path
 *
 * \details 
 * 0: -max
 * 31: -0
 * 32: +0
 * 63: +max (depending on calibration)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4 . IB_VSCOPE_H_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_VSCOPE_H_THRES(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_VSCOPE_H_THRES     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_VSCOPE_H_THRES(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/** 
 * \brief
 * Threshold value (offset) for vscope-low sampling path
 *
 * \details 
 * 0: -max
 * 31: -0
 * 32: +0
 * 63: +max (depending on calibration)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4 . IB_VSCOPE_L_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_VSCOPE_L_THRES(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_VSCOPE_L_THRES     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_VSCOPE_L_THRES(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Threshold value (offset) for main sampling path
 *
 * \details 
 * 0: -max
 * 31: -0
 * 32: +0
 * 63: +max (depending on calibration)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4 . IB_MAIN_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_MAIN_THRES(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_MAIN_THRES     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG4_IB_MAIN_THRES(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SD10G65 IB Configuration register 5
 *
 * \details
 * Configuration register 5 for SD10G65 IB.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_IB_CFG5
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5  VTSS_IOREG(0x09, 1, 0xf125)

/** 
 * \brief
 * Test generator amplitude setting
 *
 * \details 
 * 0: 0mV
 * ...
 * 15: 150mV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_TSTGEN_AMPL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_AMPL(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_AMPL     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_AMPL(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * Test generator enable but data path selected with 'ib_sig_sel' (disable
 * input loop if testgenerator is used)
 *
 * \details 
 * 0: inactive
 * 1: active
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_TSTGEN_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_ENA  VTSS_BIT(27)

/** 
 * \brief
 * Test generator data
 *
 * \details 
 * 0: low
 * 1: high
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_TSTGEN_DATA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_DATA  VTSS_BIT(26)

/** 
 * \brief
 * Test generator data toggle enable
 *
 * \details 
 * 0: inactive
 * 1: active
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_TSTGEN_TOGGLE_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_TOGGLE_ENA  VTSS_BIT(25)

/** 
 * \brief
 * Enable jump to opposite half of h-channel
 *
 * \details 
 * 0: Post main sampler
 * 1: Pre main sampler
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_JUMPH_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_JUMPH_ENA  VTSS_BIT(22)

/** 
 * \brief
 * Enable jump to opposite half of l-channel
 *
 * \details 
 * 0: Post main sampler
 * 1: Pre main sampler
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_JUMPL_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_JUMPL_ENA  VTSS_BIT(21)

/** 
 * \brief
 * DFE output disable required to calibrate IS
 *
 * \details 
 * 0: mission mode
 * 3: Vout = 0V
 * 1: Vout= xx*ampldfe/64
 * 2: Vout=-xx*ampldfe/64
 * 
 * ampldfe=196mV if ena1V = '1' (1V mode)
 * ampldfe=260mV if ena1V = '0' (1.2V mode)
 * 
 * xx= TBD
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_DFE_DIS
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_DFE_DIS(x)  VTSS_ENCODE_BITFIELD(x,19,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_DFE_DIS     VTSS_ENCODE_BITMASK(19,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_DFE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,19,2)

/** 
 * \brief
 * AGC output disable required to calibrate DFE-gain
 *
 * \details 
 * 0: mission mode
 * 3: Vout = 0V
 * 1: Vout= xx*ampldfe/64
 * 2: Vout=-xx*ampldfe/64
 * 
 * ampldfe=270mV if ena1V = '1' (1V mode)
 * ampldfe=360mV if ena1V = '0' (1.2V mode)
 * 
 * xx=
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_AGC_DIS
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_AGC_DIS(x)  VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_AGC_DIS     VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_AGC_DIS(x)  VTSS_EXTRACT_BITFIELD(x,17,2)

/** 
 * \brief
 * Selects EQ Level Detect for calibration
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_EQ_LD_CAL_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_EQ_LD_CAL_ENA  VTSS_BIT(16)

/** 
 * \brief
 * Selects IS threshold circuit for calibration
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_THRES_CAL_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_THRES_CAL_ENA  VTSS_BIT(15)

/** 
 * \brief
 * Selects IS offset circuit for calibration
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_IS_OFFS_CAL_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_IS_OFFS_CAL_ENA  VTSS_BIT(14)

/** 
 * \brief
 * Selects IA offset circuit for calibration
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_IA_OFFS_CAL_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_IA_OFFS_CAL_ENA  VTSS_BIT(13)

/** 
 * \brief
 * Selects IE Signal Detect for calibration
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_IE_SDET_CAL_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_IE_SDET_CAL_ENA  VTSS_BIT(12)

/** 
 * \brief
 * Enable calibration in order to eliminate hysteresis
 *
 * \details 
 * 1: Enable
 * 0: Disable
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_HYS_CAL_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_HYS_CAL_ENA  VTSS_BIT(11)

/** 
 * \brief
 * Enables IS MUX in detblk1
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_CALMUX_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_CALMUX_ENA  VTSS_BIT(10)

/** 
 * \brief
 * Selects calibration target (sample stage threshold, sample stage offset,
 * aux.-stage offset), dependend on calibration group, see encoding.
 *
 * \details 
 * When ib_thres_cal_ena = 1
 * 0: MD0 threshold
 * 1: MD1 threshold
 * 2: CP0 threshold
 * 3: CP1 threshold
 * 4: VH0 threshold
 * 5: VH1 threshold
 * 6: VL0 threshold
 * 7: VL1 threshold
 * When ib_is_offs_cal_ena = 1
 * 0: MD0 offset
 * 1: MD1 offset
 * 2: CP0 offset
 * 3: CP1 offset
 * 4: VH0 offset
 * 5: VH1 offset
 * 6: VL0 offset
 * 7: VL1 offset
 * When ib_ia_offs_cal_ena = 1
 * 0: Observe0 offset
 * 1: Observe1 offset
 * 2: Observe0 threshold
 * 3: Observe1 threshold
 * (MSB not used)
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_OFFS_BLKSEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_OFFS_BLKSEL(x)  VTSS_ENCODE_BITFIELD(x,6,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_OFFS_BLKSEL     VTSS_ENCODE_BITMASK(6,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_OFFS_BLKSEL(x)  VTSS_EXTRACT_BITFIELD(x,6,4)

/** 
 * \brief
 * Calibration value for IA/IS. Values for threshold calibration get
 * inverted for negative threshold voltages (ib_vscope_h_thres,
 * ib_vscope_l_thres or ib_main_thres).
 *
 * \details 
 * For offset calibration
 * 0: -max_offset * 32/32
 * 31: -max_offset * 1/32
 * 32: +max_offset * 1/32
 * 63: +max_offset * 32/32
 * For threshold calibration
 * 0: min_threshold
 * 63: max_threshold
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5 . IB_OFFS_VALUE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_OFFS_VALUE(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_OFFS_VALUE     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG5_IB_OFFS_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SD10G65 IB Configuration register 6
 *
 * \details
 * Configuration register 6 for SD10G65 IB.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_IB_CFG6
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6  VTSS_IOREG(0x09, 1, 0xf126)

/** 
 * \brief
 * 0dB Gain adjustment for EQZ-stages of Input Buffer
 *
 * \details 
 * level at LD0 = LD1 -> 0dB
 * level range 160mV-220mV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6 . IB_EQZ_GAIN_ADJ
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6_IB_EQZ_GAIN_ADJ(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6_IB_EQZ_GAIN_ADJ     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6_IB_EQZ_GAIN_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \brief
 * Enable automatic AGC adjustment
 *
 * \details 
 * 1: AGC is adjusted automatically (IB_EQZ_AGC_ADJ value is not used)
 * 0: AGC is adjusted with value stored in IB_EQZ_AGC_ADJ
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6 . IB_AUTO_AGC_ADJ
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6_IB_AUTO_AGC_ADJ  VTSS_BIT(12)

/** 
 * \brief
 * Gain adjustment of AGC-amplifier
 *
 * \details 
 * Bitgroup should be set to 2*IB_DFE_GAIN_ADJ
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6 . IB_EQZ_AGC_ADJ
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6_IB_EQZ_AGC_ADJ(x)  VTSS_ENCODE_BITFIELD(x,5,7)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6_IB_EQZ_AGC_ADJ     VTSS_ENCODE_BITMASK(5,7)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6_IB_EQZ_AGC_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,5,7)

/** 
 * \brief
 * Range for offset calibration of all sampling pathes
 *
 * \details 
 * 0: 0mV
 * 32: 80mV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6 . IB_SAM_OFFS_ADJ
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6_IB_SAM_OFFS_ADJ(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6_IB_SAM_OFFS_ADJ     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG6_IB_SAM_OFFS_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief SD10G65 IB Configuration register 7
 *
 * \details
 * Configuration register 7 for SD10G65 IB.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_IB_CFG7
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7  VTSS_IOREG(0x09, 1, 0xf127)

/** 
 * \brief
 * Initial value for calibration of main sampling path
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7 . IB_MAIN_THRES_CAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_MAIN_THRES_CAL(x)  VTSS_ENCODE_BITFIELD(x,23,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_MAIN_THRES_CAL     VTSS_ENCODE_BITMASK(23,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_MAIN_THRES_CAL(x)  VTSS_EXTRACT_BITFIELD(x,23,6)

/** 
 * \brief
 * Selects higher or lower DFE offset for IS calibration
 *
 * \details 
 * 0: ib_dfe_offset_l
 * 1: ib_dfe_offset_h
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7 . IB_DFE_OFFSET_H_L
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_H_L  VTSS_BIT(22)

/** 
 * \brief
 * Gain adjustment of DFEamplifier
 *
 * \details 
 * DFE Gain 1 Volt mode = 0dB
 * 1.2 Volt mode 1dB
 * measurement with int. DAC and Vscope Channels
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7 . IB_DFE_GAIN_ADJ
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_GAIN_ADJ(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_GAIN_ADJ     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_GAIN_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/** 
 * \brief
 * Higher threshold offset of DFE buffer for IS calibration
 *
 * \details 
 * 0: 0mv
 * 63: 200mV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7 . IB_DFE_OFFSET_H
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_H(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_H     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_H(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Lower sample offset of DFE buffer for IS calibration
 *
 * \details 
 * 0: 0mv
 * 63: 200mV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7 . IB_DFE_OFFSET_L
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_L(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_L     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_L(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SD10G65 IB Configuration register 8
 *
 * \details
 * Configuration register 8 for SD10G65 IB.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_IB_CFG8
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8  VTSS_IOREG(0x09, 1, 0xf128)

/** 
 * \brief
 * Use separate vscope clock for vscope-channels
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8 . IB_SEL_VCLK
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_SEL_VCLK  VTSS_BIT(20)

/** 
 * \brief
 * Bias regulation mode
 *
 * \details 
 * 0: constant resistor
 * 1: constant current
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8 . IB_BIAS_MODE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_BIAS_MODE  VTSS_BIT(19)

/** 
 * \brief
 * Enables neutral setting of latches
 *
 * \details 
 * 1: Reset to mid values
 * 0: Normal operation
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8 . IB_LAT_NEUTRAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_LAT_NEUTRAL  VTSS_BIT(18)

/** 
 * \brief
 * Amplitude of cml stages inside IS
 *
 * \details 
 * 0: 200mVppd
 * 7: 240mVppd
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8 . IB_CML_AMPL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_CML_AMPL(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_CML_AMPL     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_CML_AMPL(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * Gain of cml stages inside IS
 *
 * \details 
 * 0: 3dB
 * 31: 6dB
 * 63: 9dB
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8 . IB_BIAS_ADJ
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_BIAS_ADJ(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_BIAS_ADJ     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_BIAS_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Current through CML Cells
 *
 * \details 
 * 0: 150%
 * 5: 100%
 * 15: 50%
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8 . IB_CML_CURR
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_CML_CURR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_CML_CURR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_CML_CURR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SD10G65 IB Configuration register 9  automatically adapted DFE coefficients
 *
 * \details
 * Configuration register 9 for SD10G65 IB.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_IB_CFG9
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9  VTSS_IOREG(0x09, 1, 0xf129)

/** 
 * \brief
 * Weighting for fourth DFE coefficient
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9 . IB_DFE_COEF4
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF4(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF4     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF4(x)  VTSS_EXTRACT_BITFIELD(x,24,5)

/** 
 * \brief
 * Weighting for third DFE coefficient
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9 . IB_DFE_COEF3
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF3(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF3     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF3(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * Weighting for second DFE coefficient
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9 . IB_DFE_COEF2
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF2(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF2     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF2(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Weighting for first DFE coefficient
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9 . IB_DFE_COEF1
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF1(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF1     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF1(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief SD10G65 IB Configuration register 10 JTAG related setting
 *
 * \details
 * Configuration register 10 for SD10G65 IB.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_IB_CFG10
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10  VTSS_IOREG(0x09, 1, 0xf12a)

/** 
 * \brief
 * Data offset calibration result IA stage
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_IA_DOFFS_CAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_DOFFS_CAL  VTSS_BIT(31)

/** 
 * \brief
 * Data offset calibration result IS stage
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_IS_DOFFS_CAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_IS_DOFFS_CAL  VTSS_BIT(30)

/** 
 * \brief
 * Detection of toggling signal at PADP and PADN
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_IE_SDET_PEDGE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_SDET_PEDGE  VTSS_BIT(29)

/** 
 * \brief
 * Detection of toggling signal at PADP and PADN
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_IE_SDET_NEDGE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_SDET_NEDGE  VTSS_BIT(28)

/** 
 * \brief
 * Result signal detect of IE stage
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_IE_SDET
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_SDET  VTSS_BIT(27)

/** 
 * \brief
 * Result signal detect of IA stage
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_IA_SDET
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_SDET  VTSS_BIT(26)

/** 
 * \brief
 * Result of Level-Detect1 (after ES2-stage of EQZ) circuitry
 *
 * \details 
 * 1: Input level above threshold defined by IB_EQ_LD_LEV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_EQZ_LD1_PEDGE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD1_PEDGE  VTSS_BIT(25)

/** 
 * \brief
 * Result of Level-Detect1 (after ES2-stage of EQZ) circuitry
 *
 * \details 
 * 1: Input level above threshold defined by IB_EQ_LD_LEV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_EQZ_LD1_NEDGE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD1_NEDGE  VTSS_BIT(24)

/** 
 * \brief
 * Result of Level-Detect0 (after IB-stage of EQZ) circuitry
 *
 * \details 
 * 1: Input level above threshold defined by IB_EQ_LD_LEV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_EQZ_LD0_PEDGE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD0_PEDGE  VTSS_BIT(23)

/** 
 * \brief
 * Result of Level-Detect0 (after IB-stage of EQZ) circuitry
 *
 * \details 
 * 1: Input level above threshold defined by IB_EQ_LD_LEV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_EQZ_LD0_NEDGE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD0_NEDGE  VTSS_BIT(22)

/** 
 * \brief
 * Direct Data output from IE block
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_IE_DIRECT_DATA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_DIRECT_DATA  VTSS_BIT(21)

/** 
 * \brief
 * Direct Data output from IA block
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_IA_DIRECT_DATA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_DIRECT_DATA  VTSS_BIT(20)

/** 
 * \brief
 * Receive enable for BiDi loop (a.k.a. PAD loop o. TX->RX loop). Is or'ed
 * with primary input: ib_pad_loop_ena_i. Disable testgenerator
 * 'ib_tstgen_ena' if input loop is used
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_LOOP_REC
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_LOOP_REC  VTSS_BIT(17)

/** 
 * \brief
 * Drive enable for BiDi loop (a.k.a. Input loop o. RX->TX loop). Is or'ed
 * with primary input: ib_inp_loop_ena_i. Is overruled by PAD loop.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_LOOP_DRV
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_LOOP_DRV  VTSS_BIT(16)

/** 
 * \brief
 * JTAG debug p-output
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_OUT_P
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_OUT_P  VTSS_BIT(10)

/** 
 * \brief
 * JTAG debug n-output
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_OUT_N
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_OUT_N  VTSS_BIT(9)

/** 
 * \brief
 * JTAG debug threshold
 *
 * \details 
 * 0: 0mV
 * 1: 10mV
 * 31: 310mV
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_THRES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_THRES     VTSS_ENCODE_BITMASK(4,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,5)

/** 
 * \brief
 * JTAG debug p-input
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_IN_P
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_IN_P  VTSS_BIT(3)

/** 
 * \brief
 * JTAG debug n-input
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_IN_N
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_IN_N  VTSS_BIT(2)

/** 
 * \brief
 * JTAG debug clk
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_CLK
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_CLK  VTSS_BIT(1)

/** 
 * \brief
 * JTAG debug enable
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_ENA  VTSS_BIT(0)


/** 
 * \brief SD10G65 IB Configuration register 11 JTAG related setting
 *
 * \details
 * Configuration register 11 for SD10G65 IB.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_IB_CFG11
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11  VTSS_IOREG(0x09, 1, 0xf12b)

/** 
 * \brief
 * DFE Bias current settings (bit-group is gated with IB_DFE_ENA)
 *
 * \details 
 * 0: DFE disabled
 * 1: Minimum current
 * 15: Maximum current
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11 . IB_DFE_ISEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11_IB_DFE_ISEL(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11_IB_DFE_ISEL     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11_IB_DFE_ISEL(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Increase current in first stage (only available in 1.2 Volt mode)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11 . IB_ENA_400_INP
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11_IB_ENA_400_INP  VTSS_BIT(11)

/** 
 * \brief
 * Gain temperature coefficient for DFE stage
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11 . IB_TC_DFE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11_IB_TC_DFE(x)  VTSS_ENCODE_BITFIELD(x,6,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11_IB_TC_DFE     VTSS_ENCODE_BITMASK(6,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11_IB_TC_DFE(x)  VTSS_EXTRACT_BITFIELD(x,6,5)

/** 
 * \brief
 * Gain temperature coefficient for AGC stage
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11 . IB_TC_EQ
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11_IB_TC_EQ(x)  VTSS_ENCODE_BITFIELD(x,1,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11_IB_TC_EQ     VTSS_ENCODE_BITMASK(1,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG11_IB_TC_EQ(x)  VTSS_EXTRACT_BITFIELD(x,1,5)


/** 
 * \brief SD10G65 SBUS RX CFG Service-Bus related setting
 *
 * \details
 * Configuration register for Service-Bus related setting. Note: SBUS
 * configuration applies for RX/TX aggregates only, any configuration
 * applied to SBUS_TX_CFG (output buffer cfg space) will be ignored.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_SBUS_RX_CFG
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG  VTSS_IOREG(0x09, 1, 0xf12c)

/** 
 * \brief
 * Enable BiDi loop driver for F2DF testing
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG . SBUS_LOOPDRV_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_LOOPDRV_ENA  VTSS_BIT(12)

/** 
 * \brief
 * Analog test output
 *
 * \details 
 * 0: l0_ctrlspeed[0]
 * 1: vbulk
 * 2: nref
 * 3: vref820m
 * 4: vddfilt
 * 5: vddfilt
 * 6: ie_aout
 * 7: ib_aout
 * 8: ob_aout2
 * 9: pll_frange
 * 10: pll_srange
 * 11: pll_vreg820m_tx
 * 12: pll_vreg820m_rx
 * 13: ob_aout_n
 * 14: ob_aout_p
 * 15: vddfilt
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG . SBUS_ANAOUT_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_ANAOUT_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_ANAOUT_SEL     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_ANAOUT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Enable analog test output multiplexer
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG . SBUS_ANAOUT_EN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_ANAOUT_EN  VTSS_BIT(7)

/** 
 * \brief
 * Offset value for BIAS resistor calibration (2-complement)
 *
 * \details 
 * 1000: -8
 * 1111: -1
 * 0000: 0
 * 0111: 7
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG . SBUS_RCOMP
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_RCOMP(x)  VTSS_ENCODE_BITFIELD(x,3,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_RCOMP     VTSS_ENCODE_BITMASK(3,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_RCOMP(x)  VTSS_EXTRACT_BITFIELD(x,3,4)

/** 
 * \brief
 * Bias speed selection
 *
 * \details 
 * 0: Below 4Gbps
 * 1: 4Gbps to 6Gbps
 * 2: 6Gbps to 9Gbps
 * 3: Above 9Gbps
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG . SBUS_BIAS_SPEED_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_BIAS_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_BIAS_SPEED_SEL     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_BIAS_SPEED_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Bias enable
 *
 * \details 
 * 1: Enable
 * 0: Disable
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG . SBUS_BIAS_EN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_BIAS_EN  VTSS_BIT(0)


/** 
 * \brief SD10G65_RX subversion revision number
 *
 * \details
 * Subversion revision number for the RTL used in SD10G65_RX
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_RX_SVN_ID
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_SVN_ID  VTSS_IOREG(0x09, 1, 0xf12d)


/** 
 * \brief SD10G65_RX Revision ID
 *
 * \details
 * Revision numbers of the analog sub IPs used in the SD10G65_RX
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_IB:SD10G65_RX_REV_ID
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID  VTSS_IOREG(0x09, 1, 0xf12e)

/** 
 * \brief
 * Feature set number of deserializer (des10g_N)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID . DES_REV_ID
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_DES_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,26,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_DES_REV_ID     VTSS_ENCODE_BITMASK(26,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_DES_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,26,6)

/** 
 * \brief
 * Feature set number of input buffer (ib10g_N)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID . IB_REV_ID
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_IB_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,20,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_IB_REV_ID     VTSS_ENCODE_BITMASK(20,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_IB_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,20,6)

/** 
 * \brief
 * Feature set number of synthesizer (syn_N)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID . SYNTH_REV_ID
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_SYNTH_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,14,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_SYNTH_REV_ID     VTSS_ENCODE_BITMASK(14,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_SYNTH_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,14,6)

/** 
 * \brief
 * Feature set number of RC-PLL (pll10g_N)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID . RCPLL_REV_ID
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_RCPLL_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_RCPLL_REV_ID     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_RCPLL_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Feature set number of Toplevel (sd10g65_N)
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID . TOP_REV_ID
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_TOP_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_TOP_REV_ID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_IB_SD10G65_RX_REV_ID_TOP_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a HOST_PMA_32BIT:SD10G65_RX_RCPLL
 *
 * SD10G65 RX RCPLL Configuration and Status Register set
 */


/** 
 * \brief SD10G65 RX RCPLL Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 RX RCPLL.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_RCPLL:SD10G65_RX_RCPLL_CFG0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0  VTSS_IOREG(0x09, 1, 0xf130)

/** 
 * \brief
 * Preload value of the ramp up counter, reduces ramp up time for higher
 * frequencies
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_START_CNT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_START_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_START_CNT     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_START_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Sets the ramp characteristic of the FSM, higher values give faster ramp
 * up but less accuracy,
 *
 * \details 
 * 0: normal (default) ramping
 * 1: faster ramping
 * 2: fastest ramping
 * 3: slow ramping
 * uses all possible values of r_ctrl
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_RAMP_MODE_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/** 
 * \brief
 * Enable RCPLL FSM
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_ENA  VTSS_BIT(0)


/** 
 * \brief SD10G65 RX RCPLL Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 RX RCPLL.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_RCPLL:SD10G65_RX_RCPLL_CFG1
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1  VTSS_IOREG(0x09, 1, 0xf131)

/** 
 * \brief
 * Target value: 1/vco_frq * par.bit.width * 512 * ref_clk_frq
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1 . PLLF_REF_CNT_END
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_REF_CNT_END(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_REF_CNT_END     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_REF_CNT_END(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief SD10G65 RX RCPLL Configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 RX RCPLL.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_RCPLL:SD10G65_RX_RCPLL_CFG2
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2  VTSS_IOREG(0x09, 1, 0xf132)

/** 
 * \brief
 * Select chargepump current,
 *
 * \details 
 * 0: 50uA
 * 1: 100uA
 * 2: 150uA
 * 3: 200uA
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_LPF_CUR
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_LPF_CUR(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_LPF_CUR     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_LPF_CUR(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * Select loop filter resistor value,
 *
 * \details 
 * 0: not allowed
 * 1: 2400
 * 2: 1600
 * 3: 960
 * 4: 1200
 * 5: 800
 * 6: 685
 * 7: 533
 * 8: 800
 * 9: 600
 * 10: 533
 * 11: 436
 * 12: 480
 * 13: 400
 * 14: 369
 * 15: 320
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_LPF_RES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_LPF_RES(x)  VTSS_ENCODE_BITFIELD(x,7,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_LPF_RES     VTSS_ENCODE_BITMASK(7,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_LPF_RES(x)  VTSS_EXTRACT_BITFIELD(x,7,4)

/** 
 * \brief
 * Enable analog RCPLL part
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_ENA  VTSS_BIT(0)


/** 
 * \brief SD10G65 RX RCPLL Status register 0
 *
 * \details
 * Status register 0 for SD10G65 RX RCPLL.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_RCPLL:SD10G65_RX_RCPLL_STAT0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0  VTSS_IOREG(0x09, 1, 0xf133)

/** 
 * \brief
 * PLL lock status,
 *
 * \details 
 * 0: not locked
 * 1: locked
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0 . PLLF_LOCK_STAT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLLF_LOCK_STAT  VTSS_BIT(31)


/** 
 * \brief SD10G65 RX RCPLL Status register 1
 *
 * \details
 * Status register 1 for SD10G65 RX RCPLL.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_RCPLL:SD10G65_RX_RCPLL_STAT1
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1  VTSS_IOREG(0x09, 1, 0xf134)

/**
 * Register Group: \a HOST_PMA_32BIT:SD10G65_RX_SYNTH
 *
 * SD10G65 RX SYNTH Configuration and Status Register set
 */


/** 
 * \brief SD10G65 RX Synthesizer Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 RX SYNTH.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_CFG0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0  VTSS_IOREG(0x09, 1, 0xf140)

/** 
 * \brief
 * selects feedback divider setting.
 *
 * \details 
 * 0: divide by 1
 * 1: divide by 2
 * 2: divide by 4
 * 3: reserved
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_FBDIV_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FBDIV_SEL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FBDIV_SEL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FBDIV_SEL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * selects step width for sync output
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_FB_STEP
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FB_STEP(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FB_STEP     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FB_STEP(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * selects step width for integrator2
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_I2_STEP
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I2_STEP(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I2_STEP     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I2_STEP(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * enable contribution of integral2 part
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_I2_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I2_ENA  VTSS_BIT(9)

/** 
 * \brief
 * selects step width for integrator1
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_I1_STEP
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I1_STEP  VTSS_BIT(8)

/** 
 * \brief
 * selects step width for propotional
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_P_STEP
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_P_STEP  VTSS_BIT(6)

/** 
 * \brief
 * Selects circuit speed.
 *
 * \details 
 * 0: for settings with synth_fbdiv_sel = 2
 * 1: for setting with synth_fbdiv_sel less than 2
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_SPEED_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_SPEED_SEL  VTSS_BIT(4)

/** 
 * \brief
 * enables half rate mode
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_HRATE_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_HRATE_ENA  VTSS_BIT(3)

/** 
 * \brief
 * synthesizer enable
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_ENA  VTSS_BIT(0)


/** 
 * \brief SD10G65 RX Synthesizer Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 RX SYNTH.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_CFG1
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1  VTSS_IOREG(0x09, 1, 0xf141)

/** 
 * \brief
 * frequency multiplier
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1 . SYNTH_FREQ_MULT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT(x)  VTSS_ENCODE_BITFIELD(x,8,14)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT     VTSS_ENCODE_BITMASK(8,14)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT(x)  VTSS_EXTRACT_BITFIELD(x,8,14)

/** 
 * \brief
 * frequency m setting bits 35:32
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1 . SYNTH_FREQM_1
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQM_1(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQM_1     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQM_1(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * frequency n setting bits 35:32
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1 . SYNTH_FREQN_1
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQN_1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQN_1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQN_1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SD10G65 RX Synthesizer Configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 RX SYNTH.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_CFG2
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2  VTSS_IOREG(0x09, 1, 0xf142)

/** 
 * \brief
 * Rising edge triggers bit skip forward in serial data stream. Used to
 * align data to parallel interface boundaries.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_SKIP_BIT_FWD
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_SKIP_BIT_FWD  VTSS_BIT(31)

/** 
 * \brief
 * Rising edge triggers bit skip reverse in serial data stream. Used to
 * align data to parallel interface boundaries.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_SKIP_BIT_REV
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_SKIP_BIT_REV  VTSS_BIT(30)

/** 
 * \brief
 * Controls the data valid behavior for the CDRLF I2 enable function: b0 =
 * 0 => external signal controls, 1 => b1 controls
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_DV_CTRL_I2E
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I2E(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I2E     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I2E(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * Controls the data valid behavior for the CDRLF I1 max function: b0 = 0
 * => external signal controls, 1 => b1 controls
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_DV_CTRL_I1M
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1M(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1M     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1M(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Controls the data valid behavior for the CDRLF I1 enable function: b0 =
 * 0 => external signal controls, 1 => b1 controls
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_DV_CTRL_I1E
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1E(x)  VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1E     VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1E(x)  VTSS_EXTRACT_BITFIELD(x,22,2)

/** 
 * \brief
 * Controls the data valid behavior for the moebdiv select function: b0 = 0
 * => external signal controls, 1 => b1 controls
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_DV_CTRL_MD
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_MD(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_MD     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_MD(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * Cp/md dig select. Coding 0: select Bit 0/5 as cp/md (FX100 mode); 1: use
 * cp/md from core
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_CPMD_DIG_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_CPMD_DIG_SEL  VTSS_BIT(18)

/** 
 * \brief
 * uses cp/md selected via synth_cpmd_dig_sel instead of cp/md from sample
 * stage
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_CPMD_DIG_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_CPMD_DIG_ENA  VTSS_BIT(17)

/** 
 * \brief
 * enables clock for VScope / APC auxillary data chanels
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_AUX_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_AUX_ENA  VTSS_BIT(16)

/** 
 * \brief
 * relationship phase center/edge
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_PHASE_DATA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_PHASE_DATA(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_PHASE_DATA     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_PHASE_DATA(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * relationship phase center/aux
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_PHASE_AUX
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_PHASE_AUX(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_PHASE_AUX     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_PHASE_AUX(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief SD10G65 RX Synthesizer Configuration register 3
 *
 * \details
 * Configuration register 3 for SD10G65 RX SYNTH.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_CFG3
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG3  VTSS_IOREG(0x09, 1, 0xf143)


/** 
 * \brief SD10G65 RX Synthesizer Configuration register 4
 *
 * \details
 * Configuration register 4 for SD10G65 RX SYNTH.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_CFG4
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG4  VTSS_IOREG(0x09, 1, 0xf144)


/** 
 * \brief SD10G65 RX Synthesizer Register CDR loopfilter control
 *
 * \details
 * Register for CDR loopfilter control for SD10G65 RX SYNTH.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_CDRLF
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF  VTSS_IOREG(0x09, 1, 0xf145)

/** 
 * \brief
 * max value of integrator 1 during normal operation
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF . SYNTH_INTEG1_MAX1
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX1(x)  VTSS_ENCODE_BITFIELD(x,21,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX1     VTSS_ENCODE_BITMASK(21,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX1(x)  VTSS_EXTRACT_BITFIELD(x,21,5)

/** 
 * \brief
 * max value of integrator 1 during init phase
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF . SYNTH_INTEG1_MAX0
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX0(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX0     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX0(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * limit of integrator 1
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF . SYNTH_INTEG1_LIM
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_LIM(x)  VTSS_ENCODE_BITFIELD(x,11,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_LIM     VTSS_ENCODE_BITMASK(11,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_LIM(x)  VTSS_EXTRACT_BITFIELD(x,11,5)

/** 
 * \brief
 * frequency select of integrator 1
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF . SYNTH_INTEG1_FSEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_FSEL(x)  VTSS_ENCODE_BITFIELD(x,6,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_FSEL     VTSS_ENCODE_BITMASK(6,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_FSEL(x)  VTSS_EXTRACT_BITFIELD(x,6,5)

/** 
 * \brief
 * frequency select of integrator 2
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF . SYNTH_INTEG2_FSEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG2_FSEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG2_FSEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG2_FSEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SD10G65 RX Synthesizer Register 0 for qualifier access
 *
 * \details
 * Register 0 for qualifier access for SD10G65 RX SYNTH.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_QUALIFIER0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0  VTSS_IOREG(0x09, 1, 0xf146)

/** 
 * \brief
 * Clear for sticky flag "synth_i1_sat_det"
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_I1_SAT_DET_CLR
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I1_SAT_DET_CLR  VTSS_BIT(25)

/** 
 * \brief
 * Sticky flag to indicate saturating of Integrator1
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_I1_SAT_DET
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I1_SAT_DET  VTSS_BIT(24)

/** 
 * \brief
 * Controls Integrator2 behavior: '0': wrapping; '1': saturating.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_I2_WRAP_INHIBIT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I2_WRAP_INHIBIT  VTSS_BIT(23)

/** 
 * \brief
 * Clear for sticky flag "synth_I2_wrap_det"
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_I2_WRAP_DET_CLR
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I2_WRAP_DET_CLR  VTSS_BIT(22)

/** 
 * \brief
 * Sticky flag to indicate a wrap/saturating of Integrator2
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_I2_WRAP_DET
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I2_WRAP_DET  VTSS_BIT(21)

/** 
 * \brief
 * Rising edge captures qualifier for readback
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_CAPTURE_QUAL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_CAPTURE_QUAL  VTSS_BIT(20)

/** 
 * \brief
 * MS Bits of captured integrator 2
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_QUAL_I2_MSB
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I2_MSB(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I2_MSB     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I2_MSB(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Captured integrator 1 value
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_QUAL_I1
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 RX Synthesizer Register 1 for qualifier access
 *
 * \details
 * Register 1 for qualifier access for SD10G65 RX SYNTH.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_QUALIFIER1
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER1  VTSS_IOREG(0x09, 1, 0xf147)


/** 
 * \brief SD10G65 RX Synthesizer Register for sync control data
 *
 * \details
 * Register 0 for sync control data for SD10G65 RX SYNTH.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_SYNC_CTRL
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL  VTSS_IOREG(0x09, 1, 0xf148)

/** 
 * \brief
 * Selects the synchronization period for the I2 value via sync control
 * bus. Must be disabled (0) when sync control test generator is used.
 * Coding in 312.5MHz clock cycles: 0: disabled, 1: 2^6, 2: 2^7, .., 15:
 * 2^20.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL . SYNTH_SC_SYNC_TIMER_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_SYNC_TIMER_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_SYNC_TIMER_SEL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_SYNC_TIMER_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief F2DF Configuration / status register
 *
 * \details
 * Configuration / status register for the F2DF control logic.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_RX_SYNTH:F2DF_CFG_STAT
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT  VTSS_IOREG(0x09, 1, 0xf149)

/** 
 * \brief
 * Sampling divider: sample every 2^f2df_sample_div parallel data word.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_SAMPLE_DIV
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SAMPLE_DIV(x)  VTSS_ENCODE_BITFIELD(x,25,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SAMPLE_DIV     VTSS_ENCODE_BITMASK(25,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SAMPLE_DIV(x)  VTSS_EXTRACT_BITFIELD(x,25,3)

/** 
 * \brief
 * Select bit from input data used for side detection. Debug feature: '31'
 * select constant zero, '30' select constant one.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_SIDE_DET_BIT_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_BIT_SEL(x)  VTSS_ENCODE_BITFIELD(x,17,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_BIT_SEL     VTSS_ENCODE_BITMASK(17,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_BIT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,5)

/** 
 * \brief
 * Sample '1' => increment 8bit filter saturating counter by 2**n. Cnt >=
 * 0xC0 => PropperSide detected.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_SIDE_DET_ONES_WEIGHT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ONES_WEIGHT(x)  VTSS_ENCODE_BITFIELD(x,14,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ONES_WEIGHT     VTSS_ENCODE_BITMASK(14,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ONES_WEIGHT(x)  VTSS_EXTRACT_BITFIELD(x,14,3)

/** 
 * \brief
 * Sample '0' => decrement 8bit filter saturating counter by 2**n. Cnt <
 *
 * \details 
 * 0x40 => WrongSide detected.
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_SIDE_DET_ZEROS_WEIGHT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ZEROS_WEIGHT(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ZEROS_WEIGHT     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ZEROS_WEIGHT(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/** 
 * \brief
 * Determines the number of samples that have to show at least one toggle.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_TOG_DET_CNT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_TOG_DET_CNT(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_TOG_DET_CNT     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_TOG_DET_CNT(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Data valid value in "PropperSide" state. '0': data valid flaged only in
 * "Lock" state; '1' data valid also flaged in "PropperSide" state.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_DATA_VALID_PROPPER_SIDE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_DATA_VALID_PROPPER_SIDE  VTSS_BIT(3)

/** 
 * \brief
 * F2df enable. Enabling the f2df circuit automatically switches the input
 * of the CDR-loop to the f2df control block (overrules synth_cpmd_dig_sel
 * and synth_cpmd_dig_ena) and replaces the data valid signal from the core
 * logic by the data valid signal generated by the f2df control logic.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_ENABLE
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_ENABLE  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PMA_32BIT:SD10G65_TX_SYNTH
 *
 * SD10G65 TX SYNTH Configuration and Status Register set
 */


/** 
 * \brief SD10G65 TX Synthesizer Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 TX SYNTH.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_TX_SYNTH:SD10G65_TX_SYNTH_CFG0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0  VTSS_IOREG(0x09, 1, 0xf150)

/** 
 * \brief
 * selects feedback divider setting
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_FBDIV_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_FBDIV_SEL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_FBDIV_SEL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_FBDIV_SEL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * comon sync speed
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_CS_SPEED
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CS_SPEED(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CS_SPEED     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CS_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/** 
 * \brief
 * lane sync speed
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_LS_SPEED
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_SPEED  VTSS_BIT(10)

/** 
 * \brief
 * lane sync enable
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_LS_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_ENA  VTSS_BIT(8)

/** 
 * \brief
 * dig. sync speed
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_DS_SPEED
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_SPEED  VTSS_BIT(7)

/** 
 * \brief
 * dig. sync enable
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_DS_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Selects circuit speed. Coding: 0 for settings with synth_fbdiv_sel = 2;
 * 1 for setting with synth_fbdiv_sel smaller than 2.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_SPEED_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_SPEED_SEL  VTSS_BIT(4)

/** 
 * \brief
 * half rate enable
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_HRATE_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_HRATE_ENA  VTSS_BIT(3)

/** 
 * \brief
 * synthesizer enable
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_ENA  VTSS_BIT(0)


/** 
 * \brief SD10G65 TX Synthesizer Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 TX SYNTH.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_TX_SYNTH:SD10G65_TX_SYNTH_CFG1
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1  VTSS_IOREG(0x09, 1, 0xf151)

/** 
 * \brief
 * frequency multiplier
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1 . SYNTH_FREQ_MULT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT(x)  VTSS_ENCODE_BITFIELD(x,8,14)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT     VTSS_ENCODE_BITMASK(8,14)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT(x)  VTSS_EXTRACT_BITFIELD(x,8,14)

/** 
 * \brief
 * frequency m setting bits 35:32
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1 . SYNTH_FREQM_1
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQM_1(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQM_1     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQM_1(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * frequency n setting bits 35:32
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1 . SYNTH_FREQN_1
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQN_1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQN_1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQN_1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SD10G65 TX Synthesizer Configuration register 3
 *
 * \details
 * Configuration register 3 for SD10G65 TX SYNTH.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_TX_SYNTH:SD10G65_TX_SYNTH_CFG3
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3  VTSS_IOREG(0x09, 1, 0xf152)


/** 
 * \brief SD10G65 TX Synthesizer Configuration register 4
 *
 * \details
 * Configuration register 4 for SD10G65 TX SYNTH.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_TX_SYNTH:SD10G65_TX_SYNTH_CFG4
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4  VTSS_IOREG(0x09, 1, 0xf153)


/** 
 * \brief SD10G65 SSC generator Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 SSC generator.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_TX_SYNTH:SD10G65_SSC_CFG0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0  VTSS_IOREG(0x09, 1, 0xf154)

/** 
 * \brief
 * SSC modulation amplitude limiter
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0 . SSC_MOD_LIM
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_LIM(x)  VTSS_ENCODE_BITFIELD(x,19,13)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_LIM     VTSS_ENCODE_BITMASK(19,13)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_LIM(x)  VTSS_EXTRACT_BITFIELD(x,19,13)

/** 
 * \brief
 * SSC modulation period / amplitude.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0 . SSC_MOD_PERIOD
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,7,12)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_PERIOD     VTSS_ENCODE_BITMASK(7,12)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,7,12)

/** 
 * \brief
 * SSC modulation frequency fine tuning control
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0 . SSC_MOD_FREQ
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_FREQ(x)  VTSS_ENCODE_BITFIELD(x,1,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_FREQ     VTSS_ENCODE_BITMASK(1,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,1,6)

/** 
 * \brief
 * SSC generator enable.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0 . SSC_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_ENA  VTSS_BIT(0)


/** 
 * \brief SD10G65 SSC generator Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 SSC generator.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_TX_SYNTH:SD10G65_SSC_CFG1
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1  VTSS_IOREG(0x09, 1, 0xf155)

/** 
 * \brief
 * Select between the internal and external MLD phase detector: 0:
 * internal; 1: external
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . MLD_SYNC_SRC_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_SRC_SEL  VTSS_BIT(29)

/** 
 * \brief
 * Control of the internal MLD phase detector: b0: enable; b1: enable hyst.
 * b2: enable window function; b3: select window size
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . MLD_SYNC_CTRL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_CTRL(x)  VTSS_ENCODE_BITFIELD(x,25,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_CTRL     VTSS_ENCODE_BITMASK(25,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,25,4)

/** 
 * \brief
 * Select the MLD clock source for the internal MLD phase detector
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . MLD_SYNC_CLK_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(x,23,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_CLK_SEL     VTSS_ENCODE_BITMASK(23,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,23,2)

/** 
 * \brief
 * Controls integrator 2 replica behavior: '0': wrapping; '1': saturating.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SYNC_CTRL_WRAP_INHIBIT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_WRAP_INHIBIT  VTSS_BIT(22)

/** 
 * \brief
 * Frequency select of integrator 2 replica used for lane sync.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SYNC_CTRL_FSEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_FSEL(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_FSEL     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_FSEL(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/** 
 * \brief
 * Enables Smooth generator
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SMOOTH_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SMOOTH_ENA  VTSS_BIT(10)

/** 
 * \brief
 * SSC sigma delta gain.
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SSC_SD_GAIN
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_SD_GAIN(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_SD_GAIN     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_SD_GAIN(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * SSC modulation start position on synchronization trigger
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SSC_SYNC_POS
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_SYNC_POS(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_SYNC_POS     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_SYNC_POS(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * SSC modulation period multiplier encoded 2**n: 0 => 1; 1 => 2; 2 => 4, 3
 * => 8 ...
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SSC_MOD_MUL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_MOD_MUL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_MOD_MUL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_MOD_MUL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a HOST_PMA_32BIT:SD10G65_TX_RCPLL
 *
 * SD10G65 TX RCPLL Configuration and Status Register set
 */


/** 
 * \brief SD10G65 TX RCPLL Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 TX RCPLL.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_TX_RCPLL:SD10G65_TX_RCPLL_CFG0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0  VTSS_IOREG(0x09, 1, 0xf160)

/** 
 * \brief
 * Preload value of the ramp up counter, reduces ramp up time for higher
 * frequencies
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_START_CNT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_START_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_START_CNT     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_START_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Sets the ramp characteristic of the FSM, higher values give faster ramp
 * up but less accuracy,
 *
 * \details 
 * 0: normal (default) ramping
 * 1: faster ramping
 * 2: fastest ramping
 * 3: slow ramping
 * uses all possible values of r_ctrl
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_RAMP_MODE_SEL
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/** 
 * \brief
 * Enable RCPLL FSM
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_ENA  VTSS_BIT(0)


/** 
 * \brief SD10G65 TX RCPLL Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 TX RCPLL.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_TX_RCPLL:SD10G65_TX_RCPLL_CFG1
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1  VTSS_IOREG(0x09, 1, 0xf161)

/** 
 * \brief
 * Target value: 1/vco_frq * par.bit.width * 512 * ref_clk_frq
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1 . PLLF_REF_CNT_END
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_REF_CNT_END(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_REF_CNT_END     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_REF_CNT_END(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief SD10G65 TX RCPLL Configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 TX RCPLL.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_TX_RCPLL:SD10G65_TX_RCPLL_CFG2
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2  VTSS_IOREG(0x09, 1, 0xf162)

/** 
 * \brief
 * Select chargepump current,
 *
 * \details 
 * 0: 50uA
 * 1: 100uA
 * 2: 150uA
 * 3: 200uA
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_LPF_CUR
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_LPF_CUR(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_LPF_CUR     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_LPF_CUR(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * Select loop filter resistor value,
 *
 * \details 
 * 0: not allowed
 * 1: 2400
 * 2: 1600
 * 3: 960
 * 4: 1200
 * 5: 800
 * 6: 685
 * 7: 533
 * 8: 800
 * 9: 600
 * 10: 533
 * 11: 436
 * 12: 480
 * 13: 400
 * 14: 369
 * 15: 320
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_LPF_RES
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_LPF_RES(x)  VTSS_ENCODE_BITFIELD(x,7,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_LPF_RES     VTSS_ENCODE_BITMASK(7,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_LPF_RES(x)  VTSS_EXTRACT_BITFIELD(x,7,4)

/** 
 * \brief
 * Enable analog RCPLL part
 *
 * \details 
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_ENA
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_ENA  VTSS_BIT(0)


/** 
 * \brief SD10G65 TX RCPLL Status register 0
 *
 * \details
 * Status register 0 for SD10G65 TX RCPLL.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_TX_RCPLL:SD10G65_TX_RCPLL_STAT0
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0  VTSS_IOREG(0x09, 1, 0xf163)

/** 
 * \brief
 * PLL lock status,
 *
 * \details 
 * 0: not locked
 * 1: locked
 *
 * Field: VTSS_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0 . PLLF_LOCK_STAT
 */
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLLF_LOCK_STAT  VTSS_BIT(31)


/** 
 * \brief SD10G65 TX RCPLL Status register 1
 *
 * \details
 * Status register 1 for SD10G65 TX RCPLL.
 *
 * Register: \a HOST_PMA_32BIT:SD10G65_TX_RCPLL:SD10G65_TX_RCPLL_STAT1
 */
#define VTSS_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1  VTSS_IOREG(0x09, 1, 0xf164)


#endif /* _VTSS_MALIBU_REGS_HOST_PMA_32BIT_H_ */
