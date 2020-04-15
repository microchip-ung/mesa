#ifndef _VTSS_SERVALT_REGS_SD10G65_DIG_H_
#define _VTSS_SERVALT_REGS_SD10G65_DIG_H_

/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "vtss_servalt_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a SD10G65_DIG
 *
 * \see vtss_target_SD10G65_DIG_e
 *
 * Configuration and status of digital peripherals for high speed macro.
 *
 ***********************************************************************/

/**
 * Register Group: \a SD10G65_DIG:SD10G65_APC
 *
 * SD10G65 APC Configuration and Status Register set
 */


/** 
 * \brief APC top control configuration register
 *
 * \details
 * Configuration register for top control logic
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_TOP_CTRL_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_TOP_CTRL_CFG(target)  VTSS_IOREG(target,0x0)

/** 
 * \brief
 * Delay time required to power up auxilliary channels
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_TOP_CTRL_CFG . PWR_UP_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_TOP_CTRL_CFG_PWR_UP_TIME(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_TOP_CTRL_CFG_PWR_UP_TIME     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_TOP_CTRL_CFG_PWR_UP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * Delay time required to power down auxilliary channels
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_TOP_CTRL_CFG . PWR_DN_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_TOP_CTRL_CFG_PWR_DN_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_TOP_CTRL_CFG_PWR_DN_TIME     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_TOP_CTRL_CFG_PWR_DN_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * APC top-control sleep-time (power-down). Given in number of clock cycles
 * (typically 2.5 ... 5 ns)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_TOP_CTRL_CFG . SLEEP_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_TOP_CTRL_CFG_SLEEP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_TOP_CTRL_CFG_SLEEP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_TOP_CTRL_CFG_SLEEP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC common configuration register 0
 *
 * \details
 * Common configurations 0 for APC logic. Note: For HML error correction
 * logic HML=000/001/011/111 are considered valid, 010 and 101 are
 * considered correctable (010 correctable to 011; 101 correctable to 001)
 * and 100 and 110 are considered incorrectable.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_COMMON_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0(target)  VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Clear HML sampling error counter
 *
 * \details 
 * 1: Clear counter
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . HML_CLR_CNT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_HML_CLR_CNT(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_HML_CLR_CNT  VTSS_BIT(31)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_HML_CLR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * HML sampling error correction mode. Correctable sampling errors can be
 * automatically corrected.
 *
 * \details 
 * 0: Disable auto-correctin
 * 1: Enable auto-correction
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . HML_ERRCORR_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_HML_ERRCORR_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_HML_ERRCORR_MODE  VTSS_BIT(30)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_HML_ERRCORR_MODE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * HML sampling error correction enable. Invalid samples are not used for
 * parameter control (smart sampling).
 *
 * \details 
 * 0: Disable smart sampling
 * 1: Enable smart sampling
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . HML_ERRCORR_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_HML_ERRCORR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_HML_ERRCORR_ENA  VTSS_BIT(29)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_HML_ERRCORR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * H/L swapping in HML sampling error correction logic
 *
 * \details 
 * 0: No H/L swapping
 * 1: H/L swapped
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . HML_SWAP_HL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_HML_SWAP_HL(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_HML_SWAP_HL  VTSS_BIT(28)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_HML_SWAP_HL(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . APC_FSM_RECOVER_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_APC_FSM_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_APC_FSM_RECOVER_MODE     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_APC_FSM_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * Signal detect valid configuration (Offs/AGC/L/C/DFE)
 *
 * \details 
 * 0: Signal_detect input directly used
 * 1: Signal_detect input gated with gain_ctrl ramp-up done
 * (EQZ_GAIN_CTRL_DONE)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . SIG_DET_VALID_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_SIG_DET_VALID_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_SIG_DET_VALID_CFG  VTSS_BIT(25)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_SIG_DET_VALID_CFG(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Signal lost delay timer configuration used for APC recovery. The signal
 * lost delay time specifies the time when a missing input signal is
 * considered a lost input signal on sig_det = 0. The delay time is T =
 * (2^sig_lost_delay_time) * T_rx_clk_per
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . SIG_LOST_DELAY_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_SIG_LOST_DELAY_TIME(x)  VTSS_ENCODE_BITFIELD(x,20,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_SIG_LOST_DELAY_TIME     VTSS_ENCODE_BITMASK(20,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_SIG_LOST_DELAY_TIME(x)  VTSS_EXTRACT_BITFIELD(x,20,5)

/** 
 * \brief
 * Current state of APC top control state machine
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . TOP_CTRL_STATE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_TOP_CTRL_STATE(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_TOP_CTRL_STATE     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_TOP_CTRL_STATE(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . BLOCK_READ_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_BLOCK_READ_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_BLOCK_READ_SEL     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_BLOCK_READ_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Reset APC core logic (configuration registers are not reset)
 *
 * \details 
 * 1: Reset APC
 * 0: Normal operation (mission mode)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . RESET_APC
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_RESET_APC(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_RESET_APC  VTSS_BIT(11)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_RESET_APC(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Freeze current state
 *
 * \details 
 * 0: Normal operation
 * 1: Freeze APC
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . FREEZE_APC
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_FREEZE_APC(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_FREEZE_APC  VTSS_BIT(10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_FREEZE_APC(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Skip calibration process in top control state machine (applies for
 * apc_modes 2, 3 and 4)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . SKIP_CAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_SKIP_CAL(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_SKIP_CAL  VTSS_BIT(9)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_SKIP_CAL(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . IF_WIDTH
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_IF_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_IF_WIDTH     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_IF_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Obsolete. Replaced by dedicated and independent ctrl_mode bits for each
 * parameter control block.
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . CTRL_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_CTRL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_CTRL_MODE  VTSS_BIT(5)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_CTRL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . THROTTLE_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_THROTTLE_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_THROTTLE_MODE  VTSS_BIT(4)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_THROTTLE_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable APC direct connections instead of local IB configuration
 * registers.
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . APC_DIRECT_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_APC_DIRECT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_APC_DIRECT_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_APC_DIRECT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0 . APC_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_APC_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_APC_MODE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_APC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief APC parameter control synchronization register
 *
 * \details
 * Configuration register for common flexible parameter control FSMs
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_PARCTRL_SYNC_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG(target)  VTSS_IOREG(target,0x2)

/** 
 * \brief
 * APC spare register pool
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG . APC_SPARE_POOL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_APC_SPARE_POOL(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_APC_SPARE_POOL     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_APC_SPARE_POOL(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * Parameter control mode for FSM2
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM2_CTRL_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_CTRL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_CTRL_MODE  VTSS_BIT(15)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_CTRL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Parameter control mode for FSM1
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM1_CTRL_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_CTRL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_CTRL_MODE  VTSS_BIT(14)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_CTRL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM2_RECOVER_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_RECOVER_MODE     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM1_RECOVER_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_RECOVER_MODE     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Parameter control state of FSM2 in one-time mode
 *
 * \details 
 * 1: finished
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM2_CTRL_DONE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_CTRL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_CTRL_DONE  VTSS_BIT(7)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_CTRL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Start operation of FSM2 (parameter update). Should be cleared afterwards
 * in One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM2_START_CTRL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_START_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_START_CTRL  VTSS_BIT(6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_START_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM2_OP_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_OP_MODE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM2_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Parameter control state of FSM1 in one-time mode
 *
 * \details 
 * 1: finished
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM1_CTRL_DONE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_CTRL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_CTRL_DONE  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_CTRL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Start operation of FSM1 (parameter update). Should be cleared afterwards
 * in One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM1_START_CTRL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_START_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_START_CTRL  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_START_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG . FSM1_OP_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_SYNC_CFG_FSM1_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC parctrl FSM1 Timer config
 *
 * \details
 * Timing configuration register for common flexible parameter control FSM1
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_PARCTRL_FSM1_TIMER_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG(target)  VTSS_IOREG(target,0x3)

/** 
 * \brief
 * FSM1 Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG . FSM1_PS_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG_FSM1_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG_FSM1_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG_FSM1_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * FSM1 Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG . FSM1_OP_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG_FSM1_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG_FSM1_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM1_TIMER_CFG_FSM1_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC parctrl FSM2 Timer config
 *
 * \details
 * Timing configuration register for common flexible parameter control FSM2
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_PARCTRL_FSM2_TIMER_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG(target)  VTSS_IOREG(target,0x4)

/** 
 * \brief
 * FSM2 Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG . FSM2_PS_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG_FSM2_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG_FSM2_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG_FSM2_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * FSM2 Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG . FSM2_OP_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG_FSM2_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG_FSM2_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_PARCTRL_FSM2_TIMER_CFG_FSM2_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC FLEXCTRL read counter register
 *
 * \details
 * Observation register for multiple counters. The selection is done via
 * APC_COMMON_CFG0.BLOCK_READ_SEL (select flexctrl block to be read) and
 * APC_XXX_CTRL.XXX_READ_CNT_SEL (counter within flexctrl block XXX) or
 * APC_COMMON_CFG0.OFFSCAL_READ_CNT_SEL. Notice that for EQZ and DFE
 * counters hit_cnt and err_cnt make only sense in DISCRETE control mode.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_FLEXCTRL_CNT_STATUS
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_FLEXCTRL_CNT_STATUS(target)  VTSS_IOREG(target,0x5)

/** 
 * \brief
 * Current counter value
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_FLEXCTRL_CNT_STATUS . APC_CTRL_CNTVAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_FLEXCTRL_CNT_STATUS_APC_CTRL_CNTVAL(x)  (x)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_FLEXCTRL_CNT_STATUS_APC_CTRL_CNTVAL     0xffffffff
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_FLEXCTRL_CNT_STATUS_APC_CTRL_CNTVAL(x)  (x)


/** 
 * \brief APC level detect calibration configuration register
 *
 * \details
 * Configuration register for APC level detect calibrations logic
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_LD_CAL_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG(target)  VTSS_IOREG(target,0x6)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG . CAL_CLK_DIV
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_CAL_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,28,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_CAL_CLK_DIV     VTSS_ENCODE_BITMASK(28,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_CAL_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,28,3)

/** 
 * \brief
 * Detect level calibration state
 *
 * \details 
 * 1: finished
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG . DETLEV_CAL_DONE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_DETLEV_CAL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_DETLEV_CAL_DONE  VTSS_BIT(19)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_DETLEV_CAL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Skip signal detect calibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG . SKIP_SDET_CAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_SKIP_SDET_CAL(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_SKIP_SDET_CAL  VTSS_BIT(12)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_SKIP_SDET_CAL(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Skip level detect calibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG . SKIP_LD_CAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_SKIP_LD_CAL(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_SKIP_LD_CAL  VTSS_BIT(11)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_SKIP_LD_CAL(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Level for IE signal detect (when controlled by APC)
 *
 * \details 
 * 0: 20mV
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG . IE_SDET_LEVEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_IE_SDET_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_IE_SDET_LEVEL     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_IE_SDET_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/** 
 * \brief
 * Timer for calibration process
 *
 * \details 
 * 14: Use for 400MHz rx_clk
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG . DETLVL_TIMER
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_DETLVL_TIMER(x)  VTSS_ENCODE_BITFIELD(x,1,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_DETLVL_TIMER     VTSS_ENCODE_BITMASK(1,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_DETLVL_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,1,4)

/** 
 * \brief
 * Start signal and level detect calibration process (sampling stage; only
 * in manual mode, see apc_mode)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG . START_DETLVL_CAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_START_DETLVL_CAL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_START_DETLVL_CAL  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_LD_CAL_CFG_START_DETLVL_CAL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief APC sampling stage calibration configuration register 0
 *
 * \details
 * Configuration register 0 for APC sampling stage calibrations logic
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_IS_CAL_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0(target)  VTSS_IOREG(target,0x7)

/** 
 * \brief
 * Gain adjustent for DFE amplifier
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0 . IB_DFE_GAIN_ADJ
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_IB_DFE_GAIN_ADJ(x)  VTSS_ENCODE_BITFIELD(x,20,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_IB_DFE_GAIN_ADJ     VTSS_ENCODE_BITMASK(20,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_IB_DFE_GAIN_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,20,6)

/** 
 * \brief
 * Initial value for CP/MD FF threshold calibration.
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0 . CPMD_THRES_INIT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_CPMD_THRES_INIT(x)  VTSS_ENCODE_BITFIELD(x,14,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_CPMD_THRES_INIT     VTSS_ENCODE_BITMASK(14,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_CPMD_THRES_INIT(x)  VTSS_EXTRACT_BITFIELD(x,14,6)

/** 
 * \brief
 * Initial value for VScope FF threshold calibration.
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0 . VSC_THRES_INIT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_VSC_THRES_INIT(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_VSC_THRES_INIT     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_VSC_THRES_INIT(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Skip observe block initialization
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_OBSERVE_INIT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OBSERVE_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OBSERVE_INIT  VTSS_BIT(7)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OBSERVE_INIT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Skip sample FF offset initialization
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_OFFSET_INIT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OFFSET_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OFFSET_INIT  VTSS_BIT(6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OFFSET_INIT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Skip sample FF threshold initialization
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_THRESHOLD_INIT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_THRESHOLD_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_THRESHOLD_INIT  VTSS_BIT(5)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_THRESHOLD_INIT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Skip DFE buffer 0db initialization
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_DFE_BUFFER_INIT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_DFE_BUFFER_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_DFE_BUFFER_INIT  VTSS_BIT(4)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_DFE_BUFFER_INIT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Skip observe block calibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_OBSERVE_CAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OBSERVE_CAL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OBSERVE_CAL  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OBSERVE_CAL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Skip sample FF offset calibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_OFFSET_CAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OFFSET_CAL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OFFSET_CAL  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_OFFSET_CAL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Skip sample FF threshold calibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_THRESHOLD_CAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_THRESHOLD_CAL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_THRESHOLD_CAL  VTSS_BIT(1)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_THRESHOLD_CAL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Skip DFE buffer 0db calibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0 . SKIP_DFE_BUFFER_CAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_DFE_BUFFER_CAL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_DFE_BUFFER_CAL  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG0_SKIP_DFE_BUFFER_CAL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief APC sampling stage calibration configuration register 1
 *
 * \details
 * Configuration register 1 for APC sampling stage calibrations logic
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_IS_CAL_CFG1
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1(target)  VTSS_IOREG(target,0x8)

/** 
 * \brief
 * Selects ramp used to calculate calibration value. Coding: 0: both, 1:
 * rising, 2: falling, 3: reserved.
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1 . CAL_RAMP_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_CAL_RAMP_SEL(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_CAL_RAMP_SEL     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_CAL_RAMP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * Controls number of calibrations iterations to settle values that depend
 * on each other (offset vs threshold). Coding number of iterations =
 * cal_num_iterations + 1.
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1 . CAL_NUM_ITERATIONS
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_CAL_NUM_ITERATIONS(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_CAL_NUM_ITERATIONS     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_CAL_NUM_ITERATIONS(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Controls the offset calibration target of the VScope FFs. Coding: 0:
 * calibration target is zero, 1: calibration target is the programmed
 * VScope threshold.
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1 . CAL_VSC_OFFSET_TGT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_CAL_VSC_OFFSET_TGT(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_CAL_VSC_OFFSET_TGT  VTSS_BIT(15)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_CAL_VSC_OFFSET_TGT(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Swaps the mapping of even resp. odd bits of parallel data to the every
 * two sample FFs of the DDR sampling stage.
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1 . PAR_DATA_SWAP_EVEN_ODD
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_PAR_DATA_SWAP_EVEN_ODD(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_PAR_DATA_SWAP_EVEN_ODD  VTSS_BIT(14)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_PAR_DATA_SWAP_EVEN_ODD(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Selects the number of ones threshold when using parallel data. Value for
 * rising ramp from zero to one. The value for the falling ramp (one ->
 * zero) is half the interface width minus par_data_num_ones_thres.
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1 . PAR_DATA_NUM_ONES_THRES
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_PAR_DATA_NUM_ONES_THRES(x)  VTSS_ENCODE_BITFIELD(x,9,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_PAR_DATA_NUM_ONES_THRES     VTSS_ENCODE_BITMASK(9,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_PAR_DATA_NUM_ONES_THRES(x)  VTSS_EXTRACT_BITFIELD(x,9,5)

/** 
 * \brief
 * Controls whether the parallel data from the deserializer or the signal
 * from the observe multiplexer in the sample stage is used. Coding: 0:
 * observe multiplexer, 1: parallel data.
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1 . PAR_DATA_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_PAR_DATA_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_PAR_DATA_SEL  VTSS_BIT(8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_PAR_DATA_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Select offset calibration result to be read (BLOCK_READ_SEL = 8
 * required)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1 . OFFSCAL_READ_CNT_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,3,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_READ_CNT_SEL     VTSS_ENCODE_BITMASK(3,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,5)

/** 
 * \brief
 * Swaps disp with disn used during calibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1 . OFFSCAL_DIS_SWAP
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_DIS_SWAP(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_DIS_SWAP  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_DIS_SWAP(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Offset calibration state
 *
 * \details 
 * 1: finished
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1 . OFFSCAL_DONE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_DONE  VTSS_BIT(1)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_OFFSCAL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Start offset calibration process (sampling stage; only in manual mode,
 * see apc_mode)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1 . START_OFFSCAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_START_OFFSCAL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_START_OFFSCAL  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_IS_CAL_CFG1_START_OFFSCAL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief APC EQZ CTRL config
 *
 * \details
 * Configuration register for gain control logic
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_COMMON_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG(target)  VTSS_IOREG(target,0x9)

/** 
 * \brief
 * Gain freeze threshold, used in APC recovery mode for low input signals
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_FREEZE_THRES
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_FREEZE_THRES(x)  VTSS_ENCODE_BITFIELD(x,13,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_FREEZE_THRES     VTSS_ENCODE_BITMASK(13,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_FREEZE_THRES(x)  VTSS_EXTRACT_BITFIELD(x,13,10)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_RECOVER_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_RECOVER_MODE     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * Stop update of gain_adj
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_ADJ_HALT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_ADJ_HALT(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_ADJ_HALT  VTSS_BIT(10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_ADJ_HALT(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Gain calibration mode
 *
 * \details 
 * 0: Use successive approximation to find required gain
 * 1: use max gain and reduce linearly to find required gain
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_CAL_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_CAL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_CAL_MODE  VTSS_BIT(9)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_CAL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Start (initiate) gain_adj update process (on rising edge of cfg bit)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_ADJ_START_UPDATE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_ADJ_START_UPDATE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_ADJ_START_UPDATE  VTSS_BIT(8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_ADJ_START_UPDATE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Start (initiate) gain update process (on rising edge of cfg bit)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_START_UPDATE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_START_UPDATE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_START_UPDATE  VTSS_BIT(7)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_START_UPDATE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * (Re-)start (initiate) main gain/gain_adj calibration process (on rising
 * edge of cfg bit)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_START_CTRL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_START_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_START_CTRL  VTSS_BIT(6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_START_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Operation mode (only when EQZ_GAIN_STOP_CTRL = 1)
 *
 * \details 
 * 0: Idle
 * 1: Calibrate and work
 * 2: Work
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_OP_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_OP_MODE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Stop main gain control machine immediately
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_STOP_CTRL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_STOP_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_STOP_CTRL  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_STOP_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Restart gain/gain_adj calibration automatically on rising edge of
 * signal_detect
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_AUTO_RESTART
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_AUTO_RESTART(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_AUTO_RESTART  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_AUTO_RESTART(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG . EQZ_GAIN_CHG_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_CHG_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_COMMON_CFG_EQZ_GAIN_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC EQZ CTRL configuration register
 *
 * \details
 * Configuration register for gain
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_GAIN_CTRL_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG(target)  VTSS_IOREG(target,0xa)

/** 
 * \brief
 * Maximum gain in normal operation (should be not greater then 895
 * (512+3*128-1)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG . EQZ_GAIN_MAX
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_MAX(x)  VTSS_ENCODE_BITFIELD(x,20,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_MAX     VTSS_ENCODE_BITMASK(20,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_MAX(x)  VTSS_EXTRACT_BITFIELD(x,20,10)

/** 
 * \brief
 * Minimum gain in normal operation
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG . EQZ_GAIN_MIN
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_MIN(x)  VTSS_ENCODE_BITFIELD(x,10,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_MIN     VTSS_ENCODE_BITMASK(10,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_MIN(x)  VTSS_EXTRACT_BITFIELD(x,10,10)

/** 
 * \brief
 * Gain initial value (used if EQZ_GAIN_CHG_MODE = 1)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG . EQZ_GAIN_INI
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_INI(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_INI     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_CTRL_CFG_EQZ_GAIN_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief APC EQZ ADJ CTRL configuration register
 *
 * \details
 * Configuration register for gain_adj
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_GAIN_ADJ_CTRL_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG(target)  VTSS_IOREG(target,0xb)

/** 
 * \brief
 * Maximum gain_adj in normal operation
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG . EQZ_GAIN_ADJ_MAX
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_MAX(x)  VTSS_ENCODE_BITFIELD(x,20,7)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_MAX     VTSS_ENCODE_BITMASK(20,7)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_MAX(x)  VTSS_EXTRACT_BITFIELD(x,20,7)

/** 
 * \brief
 * Minimum gain_adj in normal operation
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG . EQZ_GAIN_ADJ_MIN
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_MIN(x)  VTSS_ENCODE_BITFIELD(x,10,7)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_MIN     VTSS_ENCODE_BITMASK(10,7)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_MIN(x)  VTSS_EXTRACT_BITFIELD(x,10,7)

/** 
 * \brief
 * Gain_adj initial value (used if EQZ_GAIN_CHG_MODE = 1)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG . EQZ_GAIN_ADJ_INI
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_INI(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_INI     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_GAIN_ADJ_CTRL_CFG_EQZ_GAIN_ADJ_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief APC EQZ CTRL status register
 *
 * \details
 * Observation register for controlled settings
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_CTRL_STATUS
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS(target)  VTSS_IOREG(target,0xc)

/** 
 * \brief
 * Status flag indicating main gain/gain_adj ramp-up process has finished
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS . EQZ_GAIN_CTRL_DONE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_CTRL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_CTRL_DONE  VTSS_BIT(23)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_CTRL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Parameter value (controlled/computed gain adjustment value)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS . EQZ_GAIN_ADJ_ACTVAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ADJ_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ADJ_ACTVAL     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ADJ_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \brief
 * Parameter value (controlled/computed gain value)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS . EQZ_GAIN_ACTVAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,6,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ACTVAL     VTSS_ENCODE_BITMASK(6,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,6,10)

/** 
 * \brief
 * Parameter value (controlled/computed level for level-detect logic)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS . LD_LEV_ACTVAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_LD_LEV_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_LD_LEV_ACTVAL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_LD_LEV_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief APC EQZ LD control
 *
 * \details
 * Configuration register for level-detect (LD) control, timing and
 * behavior (timing: number of rx_clk cycles, used for LD toggling)
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_LD_CTRL
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL(target)  VTSS_IOREG(target,0xd)

/** 
 * \brief
 * Captured toggling of LD-EQ
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL . LD_EQ_TOGGLE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_EQ_TOGGLE(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_EQ_TOGGLE  VTSS_BIT(31)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_EQ_TOGGLE(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Captured toggling of LD-IB
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL . LD_IB_TOGGLE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_IB_TOGGLE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_IB_TOGGLE  VTSS_BIT(30)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_IB_TOGGLE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Bypass LD catch circuitry (allows capturing pulses shorter then one
 * rx_clk cycle)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL . LD_CATCH_BYPASS
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_CATCH_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_CATCH_BYPASS  VTSS_BIT(29)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_CATCH_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * Max value for LD updates in gain_adjust (watch-dog; prevent endless loop
 * of LD adjustment; max is 2^value - 1)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL . LD_WD_CNT_MAX
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_WD_CNT_MAX(x)  VTSS_ENCODE_BITFIELD(x,26,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_WD_CNT_MAX     VTSS_ENCODE_BITMASK(26,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_WD_CNT_MAX(x)  VTSS_EXTRACT_BITFIELD(x,26,3)

/** 
 * \brief
 * Number of required toggles before toggling is considered valid
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL . LD_TOG_THRESHOLD
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_TOG_THRESHOLD(x)  VTSS_ENCODE_BITFIELD(x,22,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_TOG_THRESHOLD     VTSS_ENCODE_BITMASK(22,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_TOG_THRESHOLD(x)  VTSS_EXTRACT_BITFIELD(x,22,4)

/** 
 * \brief
 * Sensitivity deadtime between two toggles (value is multiplied by 2)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL . LD_T_TOGGLE_DEADTIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_T_TOGGLE_DEADTIME(x)  VTSS_ENCODE_BITFIELD(x,14,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_T_TOGGLE_DEADTIME     VTSS_ENCODE_BITMASK(14,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_T_TOGGLE_DEADTIME(x)  VTSS_EXTRACT_BITFIELD(x,14,8)

/** 
 * \brief
 * Update internal LD_lev value with LD_LEV_INI
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL . LD_LEV_UPDATE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_LEV_UPDATE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_LEV_UPDATE  VTSS_BIT(8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_LEV_UPDATE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Start (initiate) a LD-EQ toggle check (for present LD-level)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL . LD_EQ_START_TOG_CHK
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_EQ_START_TOG_CHK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_EQ_START_TOG_CHK  VTSS_BIT(7)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_EQ_START_TOG_CHK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Start (initiate) a LD-IB toggle check (for present LD-level)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL . LD_IB_START_TOG_CHK
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_IB_START_TOG_CHK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_IB_START_TOG_CHK  VTSS_BIT(6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_IB_START_TOG_CHK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * LD_lev initial value (used as preset value if EQZ_GAIN_CHG_MODE = 1)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL . LD_LEV_INI
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_LEV_INI(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_LEV_INI     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_LD_LEV_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief APC EQZ LD CTRL config0
 *
 * \details
 * Configuration register 0 for level-detect (LD) controller timing (number
 * of rx_clk cycles, used for operation timing). Important note: For small
 * ld_t_* values it might be necessary to change IB configuration bit-group
 * IB_LDSD_DIVSEL to higher values!
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_LD_CTRL_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0(target)  VTSS_IOREG(target,0xe)

/** 
 * \brief
 * Minimum activity for LD in work mode (value is multiplied by 8)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0 . LD_T_DEADTIME_WRK
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0_LD_T_DEADTIME_WRK(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0_LD_T_DEADTIME_WRK     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0_LD_T_DEADTIME_WRK(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Activity timeout threshold for LD in work mode (value is multiplied by
 * 8)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0 . LD_T_TIMEOUT_WRK
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0_LD_T_TIMEOUT_WRK(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0_LD_T_TIMEOUT_WRK     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG0_LD_T_TIMEOUT_WRK(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC EQZ LD CTRL config1
 *
 * \details
 * Configuration register 1 for level-detect (LD) controller timing (number
 * of rx_clk cycles, used for calibration timing). Important note: For
 * small ld_t_* values it might be necessary to change IB configuration
 * bit-group IB_LDSD_DIVSEL to higher values!
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_LD_CTRL_CFG1
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1(target)  VTSS_IOREG(target,0xf)

/** 
 * \brief
 * Minimum activity for LD in calibration mode (value is multiplied by 8)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1 . LD_T_DEADTIME_CAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1_LD_T_DEADTIME_CAL(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1_LD_T_DEADTIME_CAL     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1_LD_T_DEADTIME_CAL(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Activity timeout threshold for LD in calibration mode (value is
 * multiplied by 8)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1 . LD_T_TIMEOUT_CAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1_LD_T_TIMEOUT_CAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1_LD_T_TIMEOUT_CAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_LD_CTRL_CFG1_LD_T_TIMEOUT_CAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC EQZ Pattern matching cfg register0
 *
 * \details
 * Pattern matching configuration register for eqz_c and eqz_l control
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_PAT_MATCH_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0(target)  VTSS_IOREG(target,0x10)

/** 
 * \brief
 * EQZ-C-control pattern mask (only those bits are used for pattern
 * matching whose mask bit is set)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0 . EQZ_C_PAT_MASK
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_C_PAT_MASK(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_C_PAT_MASK     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_C_PAT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * EQZ-C-control pattern used for pattern matching (corresponding mask bits
 * must be set)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0 . EQZ_C_PAT_MATCH
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_C_PAT_MATCH(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_C_PAT_MATCH     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_C_PAT_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * EQZ-L-control pattern mask (only those bits are used for pattern
 * matching whose mask bit is set)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0 . EQZ_L_PAT_MASK
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_L_PAT_MASK(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_L_PAT_MASK     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_L_PAT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * EQZ-L-control pattern used for pattern matching (corresponding mask bits
 * must be set)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0 . EQZ_L_PAT_MATCH
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_L_PAT_MATCH(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_L_PAT_MATCH     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG0_EQZ_L_PAT_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC EQZ Pattern matching cfg register1
 *
 * \details
 * Pattern matching configuration register for eqz_offs and eqz_agc control
 * Note, if mask is set to 0, all bits are "matching" and taken into
 * account for parameter contol.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_PAT_MATCH_CFG1
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1(target)  VTSS_IOREG(target,0x11)

/** 
 * \brief
 * EQZ-Offset-control pattern mask (only those bits are used for pattern
 * matching whose mask bit is set)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1 . EQZ_OFFS_PAT_MASK
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_OFFS_PAT_MASK(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_OFFS_PAT_MASK     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_OFFS_PAT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * EQZ-Offset-control pattern used for pattern matching (corresponding mask
 * bits must be set)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1 . EQZ_OFFS_PAT_MATCH
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_OFFS_PAT_MATCH(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_OFFS_PAT_MATCH     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_OFFS_PAT_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * EQZ-AGC-control pattern mask (only those bits are used for pattern
 * matching whose mask bit is set)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1 . EQZ_AGC_PAT_MASK
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_AGC_PAT_MASK(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_AGC_PAT_MASK     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_AGC_PAT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * EQZ-AGC-control pattern used for pattern matching (corresponding mask
 * bits must be set)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1 . EQZ_AGC_PAT_MATCH
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_AGC_PAT_MATCH(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_AGC_PAT_MATCH     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_PAT_MATCH_CFG1_EQZ_AGC_PAT_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC EQZ_OFFS Control registers
 *
 * \details
 * General behavior control for EQZ_OFFS parameter control.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_OFFS_CTRL
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL(target)  VTSS_IOREG(target,0x12)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_RECOVER_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_CTRL_DONE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_DONE  VTSS_BIT(26)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_ACTVAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_SYNC_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: eqz_offs_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_READ_CNT_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for EQZ_OFFS parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_CTRL_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_MODE  VTSS_BIT(10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Alternative threshold for EQZ_OFFS parameter (controller goal: err_cnt =
 * 0.5*EQZ_OFFS_THRES)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_CTRL_THRES
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for EQZ_OFFS parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_CTRL_THRES_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_THRES_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_THRES_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_CTRL_THRES_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_START_CTRL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_START_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_START_CTRL  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_START_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL . EQZ_OFFS_OP_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC EQZ_OFFS Timer config
 *
 * \details
 * Configuration registers for EQZ_OFFS controller timing.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_OFFS_TIMER_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG(target)  VTSS_IOREG(target,0x13)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG . EQZ_OFFS_PS_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG_EQZ_OFFS_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG_EQZ_OFFS_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG_EQZ_OFFS_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG . EQZ_OFFS_OP_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG_EQZ_OFFS_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG_EQZ_OFFS_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_TIMER_CFG_EQZ_OFFS_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC EQZ_OFFS Parameter control register
 *
 * \details
 * Configuration register for controlled EQZ_OFFS parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_OFFS_PAR_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG(target)  VTSS_IOREG(target,0x14)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG . EQZ_OFFS_DIR_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_DIR_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_DIR_SEL  VTSS_BIT(31)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_DIR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG . EQZ_OFFS_RANGE_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG . EQZ_OFFS_CHG_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG . EQZ_OFFS_MAX
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG . EQZ_OFFS_MIN
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG . EQZ_OFFS_INI
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_PAR_CFG_EQZ_OFFS_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC EQZ_C Control registers
 *
 * \details
 * General behavior control for EQZ_C parameter control.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_C_CTRL
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL(target)  VTSS_IOREG(target,0x15)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_RECOVER_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_CTRL_DONE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_DONE  VTSS_BIT(26)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_ACTVAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_SYNC_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: eqz_c_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_READ_CNT_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for EQZ_C parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_CTRL_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_MODE  VTSS_BIT(10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Alternative threshold for EQZ_C parameter (controller goal: err_cnt =
 * 0.5*EQZ_C_THRES)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_CTRL_THRES
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for EQZ_C parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_CTRL_THRES_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_THRES_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_THRES_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_CTRL_THRES_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_START_CTRL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_START_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_START_CTRL  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_START_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL . EQZ_C_OP_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC EQZ_C Timer config
 *
 * \details
 * Configuration registers for EQZ_C controller timing.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_C_TIMER_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_TIMER_CFG(target)  VTSS_IOREG(target,0x16)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_TIMER_CFG . EQZ_C_PS_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_TIMER_CFG_EQZ_C_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_TIMER_CFG_EQZ_C_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_TIMER_CFG_EQZ_C_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_TIMER_CFG . EQZ_C_OP_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_TIMER_CFG_EQZ_C_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_TIMER_CFG_EQZ_C_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_TIMER_CFG_EQZ_C_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC EQZ_C Parameter control register
 *
 * \details
 * Configuration register for controlled EQZ_C parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_C_PAR_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG(target)  VTSS_IOREG(target,0x17)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG . EQZ_C_DIR_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_DIR_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_DIR_SEL  VTSS_BIT(31)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_DIR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG . EQZ_C_RANGE_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG . EQZ_C_CHG_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG . EQZ_C_MAX
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG . EQZ_C_MIN
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG . EQZ_C_INI
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC EQZ_L Control registers
 *
 * \details
 * General behavior control for EQZ_L parameter control.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_L_CTRL
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL(target)  VTSS_IOREG(target,0x18)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_RECOVER_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_CTRL_DONE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_DONE  VTSS_BIT(26)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_ACTVAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_SYNC_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: eqz_l_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_READ_CNT_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for EQZ_L parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_CTRL_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_MODE  VTSS_BIT(10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Alternative threshold for EQZ_L parameter (controller goal: err_cnt =
 * 0.5*EQZ_L_THRES)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_CTRL_THRES
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for EQZ_L parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_CTRL_THRES_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_THRES_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_THRES_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_CTRL_THRES_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_START_CTRL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_START_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_START_CTRL  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_START_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL . EQZ_L_OP_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC EQZ_L Timer config
 *
 * \details
 * Configuration registers for EQZ_L controller timing.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_L_TIMER_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_TIMER_CFG(target)  VTSS_IOREG(target,0x19)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_TIMER_CFG . EQZ_L_PS_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_TIMER_CFG_EQZ_L_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_TIMER_CFG_EQZ_L_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_TIMER_CFG_EQZ_L_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_TIMER_CFG . EQZ_L_OP_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_TIMER_CFG_EQZ_L_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_TIMER_CFG_EQZ_L_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_TIMER_CFG_EQZ_L_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC EQZ_L Parameter control register
 *
 * \details
 * Configuration register for controlled EQZ_L parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_L_PAR_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG(target)  VTSS_IOREG(target,0x1a)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG . EQZ_L_DIR_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_DIR_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_DIR_SEL  VTSS_BIT(31)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_DIR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG . EQZ_L_RANGE_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG . EQZ_L_CHG_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG . EQZ_L_MAX
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG . EQZ_L_MIN
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG . EQZ_L_INI
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC EQZ_AGC Control registers
 *
 * \details
 * General behavior control for EQZ_AGC parameter control.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_AGC_CTRL
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL(target)  VTSS_IOREG(target,0x1b)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_RECOVER_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_CTRL_DONE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_DONE  VTSS_BIT(26)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_ACTVAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_SYNC_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: eqz_agc_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_READ_CNT_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for EQZ_AGC parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_CTRL_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_MODE  VTSS_BIT(10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Alternative threshold for EQZ_AGC parameter (controller goal: err_cnt =
 * 0.5*EQZ_AGC_THRES)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_CTRL_THRES
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for EQZ_AGC parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_CTRL_THRES_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_THRES_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_THRES_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_CTRL_THRES_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_START_CTRL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_START_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_START_CTRL  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_START_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL . EQZ_AGC_OP_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC EQZ_AGC Timer config
 *
 * \details
 * Configuration registers for EQZ_AGC controller timing.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_AGC_TIMER_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG(target)  VTSS_IOREG(target,0x1c)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG . EQZ_AGC_PS_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG_EQZ_AGC_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG_EQZ_AGC_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG_EQZ_AGC_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG . EQZ_AGC_OP_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG_EQZ_AGC_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG_EQZ_AGC_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_TIMER_CFG_EQZ_AGC_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC EQZ_AGC Parameter control register
 *
 * \details
 * Configuration register for controlled EQZ_AGC parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_EQZ_AGC_PAR_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG(target)  VTSS_IOREG(target,0x1d)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG . EQZ_AGC_DIR_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_DIR_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_DIR_SEL  VTSS_BIT(31)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_DIR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG . EQZ_AGC_RANGE_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG . EQZ_AGC_CHG_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG . EQZ_AGC_MAX
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG . EQZ_AGC_MIN
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG . EQZ_AGC_INI
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_PAR_CFG_EQZ_AGC_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC DFE1 Control registers
 *
 * \details
 * General behavior control for DFE1 parameter control.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_DFE1_CTRL
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL(target)  VTSS_IOREG(target,0x1e)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL . DFE1_RECOVER_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL . DFE1_CTRL_DONE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_DONE  VTSS_BIT(26)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL . DFE1_ACTVAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL . DFE1_SYNC_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: dfe1_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL . DFE1_READ_CNT_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for DFE1 parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL . DFE1_CTRL_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_MODE  VTSS_BIT(10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Alternative threshold for DFE1 parameter (controller goal: err_cnt =
 * 0.5*DFE1_THRES)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL . DFE1_CTRL_THRES
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for DFE1 parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL . DFE1_CTRL_THRES_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_THRES_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_THRES_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_CTRL_THRES_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL . DFE1_START_CTRL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_START_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_START_CTRL  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_START_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL . DFE1_OP_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC DFE1 Timer config
 *
 * \details
 * Configuration registers for DFE1 controller timing.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_DFE1_TIMER_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_TIMER_CFG(target)  VTSS_IOREG(target,0x1f)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_TIMER_CFG . DFE1_PS_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_TIMER_CFG_DFE1_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_TIMER_CFG_DFE1_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_TIMER_CFG_DFE1_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_TIMER_CFG . DFE1_OP_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_TIMER_CFG_DFE1_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_TIMER_CFG_DFE1_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_TIMER_CFG_DFE1_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC DFE1 Parameter control register
 *
 * \details
 * Configuration register for controlled DFE1 parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_DFE1_PAR_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG(target)  VTSS_IOREG(target,0x20)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG . DFE1_DIR_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_DIR_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_DIR_SEL  VTSS_BIT(31)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_DIR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG . DFE1_RANGE_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG . DFE1_CHG_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG . DFE1_MAX
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG . DFE1_MIN
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG . DFE1_INI
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_PAR_CFG_DFE1_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC DFE2 Control registers
 *
 * \details
 * General behavior control for DFE2 parameter control.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_DFE2_CTRL
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL(target)  VTSS_IOREG(target,0x21)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL . DFE2_RECOVER_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL . DFE2_CTRL_DONE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_DONE  VTSS_BIT(26)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL . DFE2_ACTVAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL . DFE2_SYNC_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: dfe2_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL . DFE2_READ_CNT_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for DFE2 parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL . DFE2_CTRL_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_MODE  VTSS_BIT(10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Alternative threshold for DFE2 parameter (controller goal: err_cnt =
 * 0.5*DFE2_THRES)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL . DFE2_CTRL_THRES
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for DFE2 parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL . DFE2_CTRL_THRES_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_THRES_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_THRES_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_CTRL_THRES_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL . DFE2_START_CTRL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_START_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_START_CTRL  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_START_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL . DFE2_OP_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC DFE2 Timer config
 *
 * \details
 * Configuration registers for DFE2 controller timing.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_DFE2_TIMER_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_TIMER_CFG(target)  VTSS_IOREG(target,0x22)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_TIMER_CFG . DFE2_PS_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_TIMER_CFG_DFE2_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_TIMER_CFG_DFE2_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_TIMER_CFG_DFE2_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_TIMER_CFG . DFE2_OP_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_TIMER_CFG_DFE2_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_TIMER_CFG_DFE2_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_TIMER_CFG_DFE2_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC DFE2 Parameter control register
 *
 * \details
 * Configuration register for controlled DFE2 parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_DFE2_PAR_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG(target)  VTSS_IOREG(target,0x23)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG . DFE2_DIR_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_DIR_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_DIR_SEL  VTSS_BIT(31)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_DIR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG . DFE2_RANGE_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG . DFE2_CHG_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG . DFE2_MAX
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG . DFE2_MIN
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG . DFE2_INI
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_PAR_CFG_DFE2_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC DFE3 Control registers
 *
 * \details
 * General behavior control for DFE3 parameter control.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_DFE3_CTRL
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL(target)  VTSS_IOREG(target,0x24)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL . DFE3_RECOVER_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL . DFE3_CTRL_DONE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_DONE  VTSS_BIT(26)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL . DFE3_ACTVAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL . DFE3_SYNC_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: dfe3_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL . DFE3_READ_CNT_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for DFE3 parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL . DFE3_CTRL_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_MODE  VTSS_BIT(10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Alternative threshold for DFE3 parameter (controller goal: err_cnt =
 * 0.5*DFE3_THRES)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL . DFE3_CTRL_THRES
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for DFE3 parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL . DFE3_CTRL_THRES_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_THRES_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_THRES_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_CTRL_THRES_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL . DFE3_START_CTRL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_START_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_START_CTRL  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_START_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL . DFE3_OP_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC DFE3 Timer config
 *
 * \details
 * Configuration registers for DFE3 controller timing.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_DFE3_TIMER_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_TIMER_CFG(target)  VTSS_IOREG(target,0x25)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_TIMER_CFG . DFE3_PS_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_TIMER_CFG_DFE3_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_TIMER_CFG_DFE3_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_TIMER_CFG_DFE3_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_TIMER_CFG . DFE3_OP_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_TIMER_CFG_DFE3_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_TIMER_CFG_DFE3_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_TIMER_CFG_DFE3_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC DFE3 Parameter control register
 *
 * \details
 * Configuration register for controlled DFE3 parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_DFE3_PAR_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG(target)  VTSS_IOREG(target,0x26)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG . DFE3_DIR_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_DIR_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_DIR_SEL  VTSS_BIT(31)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_DIR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG . DFE3_RANGE_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG . DFE3_CHG_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG . DFE3_MAX
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG . DFE3_MIN
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG . DFE3_INI
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_PAR_CFG_DFE3_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief APC DFE4 Control registers
 *
 * \details
 * General behavior control for DFE4 parameter control.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_DFE4_CTRL
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL(target)  VTSS_IOREG(target,0x27)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL . DFE4_RECOVER_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_RECOVER_MODE(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_RECOVER_MODE     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_RECOVER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Parameter control state in one-time mode
 *
 * \details 
 * 1: Finished
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL . DFE4_CTRL_DONE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_DONE  VTSS_BIT(26)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Parameter value (controlled/computed value)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL . DFE4_ACTVAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_ACTVAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_ACTVAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_ACTVAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL . DFE4_SYNC_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_SYNC_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_SYNC_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_SYNC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Select counter to be read
 *
 * \details 
 * 0: dfe4_value
 * 1: Hit counter
 * 2: Error counter
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL . DFE4_READ_CNT_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_READ_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_READ_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_READ_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Parameter control mode for DFE4 parameter
 *
 * \details 
 * 0: Discrete
 * 1: Continuous
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL . DFE4_CTRL_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_MODE  VTSS_BIT(10)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Alternative threshold for DFE4 parameter (controller goal: err_cnt =
 * 0.5*DFE4_THRES)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL . DFE4_CTRL_THRES
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_THRES     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Enable use of alternative threshold for DFE4 parameter
 *
 * \details 
 * 0: Use default threshold
 * 1: Use alternative threshold
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL . DFE4_CTRL_THRES_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_THRES_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_THRES_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_CTRL_THRES_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Start operation (parameter update). Should be cleared afterwards in
 * One-time mode and stay set in Non-stop and Paused mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL . DFE4_START_CTRL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_START_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_START_CTRL  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_START_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL . DFE4_OP_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_OP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC DFE4 Timer config
 *
 * \details
 * Configuration registers for DFE4 controller timing.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_DFE4_TIMER_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_TIMER_CFG(target)  VTSS_IOREG(target,0x28)

/** 
 * \brief
 * Pause time
 *
 * \details 
 * (in number of rx_clk cycles)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_TIMER_CFG . DFE4_PS_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_TIMER_CFG_DFE4_PS_TIME(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_TIMER_CFG_DFE4_PS_TIME     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_TIMER_CFG_DFE4_PS_TIME(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Operation time (in number of rx_clk cycles)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_TIMER_CFG . DFE4_OP_TIME
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_TIMER_CFG_DFE4_OP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_TIMER_CFG_DFE4_OP_TIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_TIMER_CFG_DFE4_OP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief APC DFE4 Parameter control register
 *
 * \details
 * Configuration register for controlled DFE4 parameter. Note, for
 * parameters larger than 8 bits, ini/min/max values are shifted to the
 * left. For parameters smaller than 8 bits only the lower bits of
 * ini/min/max are used.
 *
 * Register: \a SD10G65_DIG:SD10G65_APC:APC_DFE4_PAR_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG(target)  VTSS_IOREG(target,0x29)

/** 
 * \brief
 * Select parameter update direction
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG . DFE4_DIR_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_DIR_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_DIR_SEL  VTSS_BIT(31)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_DIR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Parameter range selection (only when CTRL_MODE = continuous). Value
 * complies to number of left-shifts
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG . DFE4_RANGE_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_RANGE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_RANGE_SEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_RANGE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

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
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG . DFE4_CHG_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_CHG_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Maximum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG . DFE4_MAX
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_MAX     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Minimum value of paramter
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG . DFE4_MIN
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_MIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_MIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_MIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Parameter initial value
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG . DFE4_INI
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_INI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_INI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_PAR_CFG_DFE4_INI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a SD10G65_DIG:SD10G65_VSCOPE2
 *
 * SD10G65 VSCOPE Configuration and Status Register set
 */


/** 
 * \brief Vscope main config register
 *
 * \details
 * Vscope main configuration register
 *
 * Register: \a SD10G65_DIG:SD10G65_VSCOPE2:VSCOPE_MAIN_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG(target)  VTSS_IOREG(target,0x2a)

/** 
 * \brief
 * Disables writing of synth_phase_aux in synthesizer
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . SYN_PHASE_WR_DIS
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_SYN_PHASE_WR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_SYN_PHASE_WR_DIS  VTSS_BIT(31)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_SYN_PHASE_WR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Disables writing of ib_auxl_offset and ib_auxh_offset in IB
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . IB_AUX_OFFS_WR_DIS
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_IB_AUX_OFFS_WR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_IB_AUX_OFFS_WR_DIS  VTSS_BIT(30)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_IB_AUX_OFFS_WR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Disables writing of ib_jumpl_ena and ib_jumph_ena in IB
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . IB_JUMP_ENA_WR_DIS
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_IB_JUMP_ENA_WR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_IB_JUMP_ENA_WR_DIS  VTSS_BIT(29)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_IB_JUMP_ENA_WR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * Counter output selection
 *
 * \details 
 * 0-3: error counter 0-3
 * 4: hit counter
 * 5: clock counter
 * 6: 8 LSBs of error counter 3-1 and hit counter
 * 7: 8 LSBs of error counter 3-0
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . CNT_OUT_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_CNT_OUT_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_CNT_OUT_SEL     VTSS_ENCODE_BITMASK(26,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_CNT_OUT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,3)

/** 
 * \brief
 * Comparator input selection
 *
 * \details 
 * [REF]
 * 0 or 1: auxL
 * 4 or 5: auxH
 * 2 or 7: main
 * [SUB]
 * 5 or 7: auxL
 * 0 or 2: auxH
 * 1 or 4: main
 * (3 or 6: reserved)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . COMP_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_COMP_SEL(x)  VTSS_ENCODE_BITFIELD(x,23,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_COMP_SEL     VTSS_ENCODE_BITMASK(23,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_COMP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,23,3)

/** 
 * \brief
 * Select GP reg input
 *
 * \details 
 * 0: rx (main)
 * 1: low aux
 * 2: high aux
 * 3: counter
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . GP_SELECT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_GP_SELECT(x)  VTSS_ENCODE_BITFIELD(x,21,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_GP_SELECT     VTSS_ENCODE_BITMASK(21,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_GP_SELECT(x)  VTSS_EXTRACT_BITFIELD(x,21,2)

/** 
 * \brief
 * Allows to freeze the GP register value to assure valid reading
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . GP_REG_FREEZE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_GP_REG_FREEZE(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_GP_REG_FREEZE  VTSS_BIT(20)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_GP_REG_FREEZE(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Scan limit, selects which counter saturation limits the other counters
 *
 * \details 
 * 0: clock counter
 * 1: hit counter
 * 2: error counters
 * 3: no limit
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . SCAN_LIM
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_SCAN_LIM(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_SCAN_LIM     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_SCAN_LIM(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * Preload value for error counter
 *
 * \details 
 * After preload error counter = 2**32 - 2**(preload_val + 1)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . PRELOAD_VAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_PRELOAD_VAL(x)  VTSS_ENCODE_BITFIELD(x,13,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_PRELOAD_VAL     VTSS_ENCODE_BITMASK(13,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_PRELOAD_VAL(x)  VTSS_EXTRACT_BITFIELD(x,13,5)

/** 
 * \brief
 * Disable interrupt output
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . INTR_DIS
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_INTR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_INTR_DIS  VTSS_BIT(12)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_INTR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Enable trigger
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . TRIG_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_TRIG_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_TRIG_ENA  VTSS_BIT(11)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_TRIG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Counter output assignment and internal counter reset implicitly done by
 * reading the counter; unused in hw-scan mode where this function is
 * permanently enabled
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . QUICK_SCAN
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_QUICK_SCAN(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_QUICK_SCAN  VTSS_BIT(10)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_QUICK_SCAN(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Counter period: preload value for clock counter
 *
 * \details 
 * After preload clock counter = 2**32 - 2**(count_per + 1)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . COUNT_PER
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_COUNT_PER(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_COUNT_PER     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_COUNT_PER(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Enable Counting
 *
 * \details 
 * 0: disable counting and assign counter output; internal counters get
 * their preload value
 * 1: enable counting
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . CNT_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_CNT_ENA  VTSS_BIT(4)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Interface Width
 *
 * \details 
 * 0: 8 bit
 * 1: 10 bit
 * 2: 16 bit
 * 3: 20 bit
 * 4: 32 bit
 * 5: 40 bit
 * others: reserved
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . IF_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_IF_MODE(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_IF_MODE     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_IF_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * Enable Vscope
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG . VSCOPE_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_VSCOPE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_VSCOPE_ENA  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_VSCOPE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Vscope pattern lock config register
 *
 * \details
 * Vscope pattern lock configuration register
 *
 * Register: \a SD10G65_DIG:SD10G65_VSCOPE2:VSCOPE_PAT_LOCK_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG(target)  VTSS_IOREG(target,0x2b)

/** 
 * \brief
 * Preload value for hit counter
 *
 * \details 
 * After preload hit counter = 2**32 - 2**(preload_hit_cnt + 1)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG . PRELOAD_HIT_CNT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_PRELOAD_HIT_CNT(x)  VTSS_ENCODE_BITFIELD(x,20,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_PRELOAD_HIT_CNT     VTSS_ENCODE_BITMASK(20,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_PRELOAD_HIT_CNT(x)  VTSS_EXTRACT_BITFIELD(x,20,5)

/** 
 * \brief
 * Don't Care mask: Enable history mask usage.
 *
 * \details 
 * 0: enable history mask bit
 * 1: history mask bit is "don't care"
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG . DC_MASK
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_DC_MASK(x)  VTSS_ENCODE_BITFIELD(x,10,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_DC_MASK     VTSS_ENCODE_BITMASK(10,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_DC_MASK(x)  VTSS_EXTRACT_BITFIELD(x,10,10)

/** 
 * \brief
 * History mask: Respective sequence is expected in reference input
 * (comp_sel); if enabled (dc_mask) before hit and error counting is
 * enabled
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG . HIST_MASK
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_HIST_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_HIST_MASK     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_HIST_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Vscope hw scan config register 1
 *
 * \details
 * Vscope HW scan configuration register 1
 *
 * Register: \a SD10G65_DIG:SD10G65_VSCOPE2:VSCOPE_HW_SCAN_CFG1
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1(target)  VTSS_IOREG(target,0x2c)

/** 
 * \brief
 * Invert the jumph_ena and jumpl_ena bit in HW scan mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1 . PHASE_JUMP_INV
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_PHASE_JUMP_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_PHASE_JUMP_INV  VTSS_BIT(31)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_PHASE_JUMP_INV(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Offset between AuxL amplitude (reference) and AuxH amplitude, signed
 * (2s-complement), +- 1/4 amplitude max.
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1 . AMPL_OFFS_VAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_AMPL_OFFS_VAL(x)  VTSS_ENCODE_BITFIELD(x,25,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_AMPL_OFFS_VAL     VTSS_ENCODE_BITMASK(25,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_AMPL_OFFS_VAL(x)  VTSS_EXTRACT_BITFIELD(x,25,5)

/** 
 * \brief
 * Maximum phase increment value before wrapping
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1 . MAX_PHASE_INCR_VAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_MAX_PHASE_INCR_VAL(x)  VTSS_ENCODE_BITFIELD(x,17,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_MAX_PHASE_INCR_VAL     VTSS_ENCODE_BITMASK(17,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_MAX_PHASE_INCR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,17,8)

/** 
 * \brief
 * Maximum amplitude increment value before wrapping
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1 . MAX_AMPL_INCR_VAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_MAX_AMPL_INCR_VAL(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_MAX_AMPL_INCR_VAL     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_MAX_AMPL_INCR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Phase increment per scan step
 *
 * \details 
 * Increment = phase_incr + 1
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1 . PHASE_INCR
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_PHASE_INCR(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_PHASE_INCR     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_PHASE_INCR(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/** 
 * \brief
 * Amplitude increment per scan step
 *
 * \details 
 * Increment = ampl_incr + 1
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1 . AMPL_INCR
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_AMPL_INCR(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_AMPL_INCR     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_AMPL_INCR(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * Number of scans per iteration in N-point-scan mode
 *
 * \details 
 * 0: 1
 * 1: 2
 * 2: 4
 * 3: 8
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1 . NUM_SCANS_PER_ITR
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_NUM_SCANS_PER_ITR(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_NUM_SCANS_PER_ITR     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_NUM_SCANS_PER_ITR(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Enables HW scan with N results per scan or fast-scan
 *
 * \details 
 * 0: off
 * 1: N-point scan
 * 2: fast-scan (sq)
 * 3: fast-scan (diag)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1 . HW_SCAN_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_HW_SCAN_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_HW_SCAN_ENA     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG1_HW_SCAN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Vscope hw config register 2
 *
 * \details
 * Vscope HW scan configuration register 2
 *
 * Register: \a SD10G65_DIG:SD10G65_VSCOPE2:VSCOPE_HW_SCAN_CFG2
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2(target)  VTSS_IOREG(target,0x2d)

/** 
 * \brief
 * Threshold for error_counter in fast-scan mode
 *
 * \details 
 * N+1
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2 . FAST_SCAN_THRES
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_FAST_SCAN_THRES(x)  VTSS_ENCODE_BITFIELD(x,29,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_FAST_SCAN_THRES     VTSS_ENCODE_BITMASK(29,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_FAST_SCAN_THRES(x)  VTSS_EXTRACT_BITFIELD(x,29,3)

/** 
 * \brief
 * Left shift for threshold of error_counter in fast-scan mode
 *
 * \details 
 * threshold = (fast_scan_thres+1) shift_left fs_thres_shift
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2 . FS_THRES_SHIFT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_FS_THRES_SHIFT(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_FS_THRES_SHIFT     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_FS_THRES_SHIFT(x)  VTSS_EXTRACT_BITFIELD(x,24,5)

/** 
 * \brief
 * Value at which jumpl_ena and jumph_ena in IB must be toggled
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2 . PHASE_JUMP_VAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_PHASE_JUMP_VAL(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_PHASE_JUMP_VAL     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_PHASE_JUMP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Disable IB amplitude symmetry compensation for AuxH and AuxL
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2 . AUX_AMPL_SYM_DIS
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_AUX_AMPL_SYM_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_AUX_AMPL_SYM_DIS  VTSS_BIT(15)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_AUX_AMPL_SYM_DIS(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Start value for VScope amplitude in N-point-scan mode and fast-scan mode
 * (before IB amplitude symmetry compensation)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2 . AMPL_START_VAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_AMPL_START_VAL(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_AMPL_START_VAL     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_AMPL_START_VAL(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Start value for VScope phase in N-point-scan mode and fast-scan mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2 . PHASE_START_VAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_PHASE_START_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_PHASE_START_VAL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG2_PHASE_START_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Vscope status register
 *
 * \details
 * Vscope status register
 *
 * Register: \a SD10G65_DIG:SD10G65_VSCOPE2:VSCOPE_STAT
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_STAT(target)  VTSS_IOREG(target,0x2e)

/** 
 * \brief
 * 8 MSBs of general purpose register
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_STAT . GP_REG_MSB
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_STAT_GP_REG_MSB(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_STAT_GP_REG_MSB     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_STAT_GP_REG_MSB(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Fast scan mode: Indicator per cursor position whether threshold was
 * reached
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_STAT . FAST_SCAN_HIT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_STAT_FAST_SCAN_HIT(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_STAT_FAST_SCAN_HIT     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_STAT_FAST_SCAN_HIT(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Done sticky
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_STAT . DONE_STICKY
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_STAT_DONE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_STAT_DONE_STICKY  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_STAT_DONE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Vscope counter register
 *
 * \details
 * Vscope counter register
 *
 * Register: \a SD10G65_DIG:SD10G65_VSCOPE2:VSCOPE_CNT
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_CNT(target)  VTSS_IOREG(target,0x2f)

/** 
 * \brief
 * Counter value
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_CNT . COUNTER
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_CNT_COUNTER(x)  (x)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_CNT_COUNTER     0xffffffff
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_CNT_COUNTER(x)  (x)


/** 
 * \brief Vscope general purpose register
 *
 * \details
 * Vscope general purpose  register
 *
 * Register: \a SD10G65_DIG:SD10G65_VSCOPE2:VSCOPE_DBG_LSB
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_DBG_LSB(target)  VTSS_IOREG(target,0x30)

/** 
 * \brief
 * 32 LSBs of general purpose register
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_DBG_LSB . GP_REG_LSB
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_DBG_LSB_GP_REG_LSB(x)  (x)
#define  VTSS_M_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_DBG_LSB_GP_REG_LSB     0xffffffff
#define  VTSS_X_SD10G65_DIG_SD10G65_VSCOPE2_VSCOPE_DBG_LSB_GP_REG_LSB(x)  (x)

/**
 * Register Group: \a SD10G65_DIG:SD10G65_DFT
 *
 * SD10G65 DFT Configuration and Status Register set
 */


/** 
 * \brief DFT Main configuration register
 *
 * \details
 * Main configuration register for SD10G65 DFT.
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_RX_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG(target)  VTSS_IOREG(target,0x31)

/** 
 * \brief
 * Disables error generation based on stuck_at_par errors,
 *
 * \details 
 * 0: stuck_at_par error generates 63 errors per clock cycle (in PRBS mode
 * only)
 * 1: stuck_at_par error does not generate errors
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . STUCK_AT_PAR_MASK_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_STUCK_AT_PAR_MASK_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_STUCK_AT_PAR_MASK_CFG  VTSS_BIT(27)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_STUCK_AT_PAR_MASK_CFG(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * Disables error generation based on stuck_at_01 errors,
 *
 * \details 
 * 0: stuck_at_01 error generates 63 errors per clock cycle (in PRBS mode
 * only)
 * 1: stuck_at_01 error does not generate errors
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . STUCK_AT_01_MASK_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_STUCK_AT_01_MASK_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_STUCK_AT_01_MASK_CFG  VTSS_BIT(26)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_STUCK_AT_01_MASK_CFG(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Enables data through from gearbox to gearbox
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . DIRECT_THROUGH_ENA_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_DIRECT_THROUGH_ENA_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_DIRECT_THROUGH_ENA_CFG  VTSS_BIT(25)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_DIRECT_THROUGH_ENA_CFG(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Captures data from error counter to allow reading of stable data
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . ERR_CNT_CAPT_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_ERR_CNT_CAPT_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_ERR_CNT_CAPT_CFG  VTSS_BIT(24)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_ERR_CNT_CAPT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Data source selection
 *
 * \details 
 * 0: main path
 * 1: vscope high path
 * 2: vscope low path
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . RX_DATA_SRC_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_RX_DATA_SRC_SEL(x)  VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_RX_DATA_SRC_SEL     VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_RX_DATA_SRC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,22,2)

/** 
 * \brief
 * States in which error counting is enabled
 *
 * \details 
 * 3:all but IDLE; 2:check 1:stable+check
 * 0:wait_stable+stable+check
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . BIST_CNT_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_BIST_CNT_CFG(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_BIST_CNT_CFG     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_BIST_CNT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * Disable change of stored patterns (e.g. to avoid changes during
 * read-out)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . FREEZE_PATTERN_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_FREEZE_PATTERN_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_FREEZE_PATTERN_CFG  VTSS_BIT(19)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_FREEZE_PATTERN_CFG(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Selects pattern to check
 *
 * \details 
 * 0: PRBS pattern
 * 1: constant pattern
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . CHK_MODE_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_CHK_MODE_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_CHK_MODE_CFG  VTSS_BIT(18)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_CHK_MODE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Selects DES interface width
 *
 * \details 
 * 0:8
 * 1:10
 * 2:16
 * 3:20
 * 4:32
 * 5:40 (default)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . RX_WID_SEL_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_RX_WID_SEL_CFG(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_RX_WID_SEL_CFG     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_RX_WID_SEL_CFG(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/** 
 * \brief
 * Pattern generator: 0:bytes mode; 1:10-bits word mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . RX_WORD_MODE_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_RX_WORD_MODE_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_RX_WORD_MODE_CFG  VTSS_BIT(14)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_RX_WORD_MODE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Selects PRBS check
 *
 * \details 
 * 0: prbs7
 * 1: prbs15
 * 2: prbs23
 * 3: prbs11
 * 4: prbs31 (default)
 * 5: prbs9
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . RX_PRBS_SEL_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_RX_PRBS_SEL_CFG(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_RX_PRBS_SEL_CFG     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_RX_PRBS_SEL_CFG(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/** 
 * \brief
 * Enables PRBS checker input inversion
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . INV_ENA_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_INV_ENA_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_INV_ENA_CFG  VTSS_BIT(10)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_INV_ENA_CFG(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Selects compare mode
 *
 * \details 
 * 0: compare mode possible
 * 1 learn mode is forced
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . CMP_MODE_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_CMP_MODE_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_CMP_MODE_CFG  VTSS_BIT(9)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_CMP_MODE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Number of consecutive errors/non-errors before transitioning to
 * respective state
 *
 * \details 
 * value = num-40-bits-words + 1
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . LRN_CNT_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_LRN_CNT_CFG(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_LRN_CNT_CFG     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_LRN_CNT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * SW reset of error counter; rising edge activates reset
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . CNT_RST
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_CNT_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_CNT_RST  VTSS_BIT(5)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_CNT_RST(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Selects modes in which error counter is active
 *
 * \details 
 * 0:learn and compare mode
 * 1:transition between modes
 * 2:learn mode
 * 3:compare mode
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . CNT_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_CNT_CFG(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_CNT_CFG     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_CNT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * BIST mode
 *
 * \details 
 * 0: off
 * 1: BIST
 * 2: BER
 * 3:CONT (infinite mode)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . BIST_MODE_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_BIST_MODE_CFG(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_BIST_MODE_CFG     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_BIST_MODE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Enable RX DFT capability
 *
 * \details 
 * 0: Disable DFT
 * 1: Enable DFT
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG . DFT_RX_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_DFT_RX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_DFT_RX_ENA  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_CFG_DFT_RX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief DFT pattern mask configuration register
 *
 * \details
 * Configuration register for SD10G65 DFT to mask data bits preventing
 * error counting for these bits.
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_RX_MASK_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_MASK_CFG(target)  VTSS_IOREG(target,0x32)

/** 
 * \brief
 * Mask out (active high) errors in 32 LSB data bits
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_MASK_CFG . LSB_MASK_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_MASK_CFG_LSB_MASK_CFG(x)  (x)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_MASK_CFG_LSB_MASK_CFG     0xffffffff
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_MASK_CFG_LSB_MASK_CFG(x)  (x)


/** 
 * \brief DFT Pattern checker configuration register
 *
 * \details
 * Pattern checker configuration register for SD10G65 DFT.
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_RX_PAT_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG(target)  VTSS_IOREG(target,0x33)

/** 
 * \brief
 * Mask out (active high) errors in 8 MSB data bits
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG . MSB_MASK_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG_MSB_MASK_CFG(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG_MSB_MASK_CFG     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG_MSB_MASK_CFG(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * Pattern read enable
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG . PAT_READ_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG_PAT_READ_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG_PAT_READ_CFG  VTSS_BIT(16)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG_PAT_READ_CFG(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Maximum address in Checker (before continuing with address 0)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG . MAX_ADDR_CHK_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG_MAX_ADDR_CHK_CFG(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG_MAX_ADDR_CHK_CFG     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG_MAX_ADDR_CHK_CFG(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Address to read patterns from used by SW
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG . READ_ADDR_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG_READ_ADDR_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG_READ_ADDR_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_RX_PAT_CFG_READ_ADDR_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief DFT BIST configuration register 0
 *
 * \details
 * BIST configuration register for SD10G65 DFT controlling 'check and
 * wait-stable' mode.
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_BIST_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG0(target)  VTSS_IOREG(target,0x34)

/** 
 * \brief
 * BIST FSM: threshold to leave DOZE state
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG0 . WAKEUP_DLY_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG0_WAKEUP_DLY_CFG(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG0_WAKEUP_DLY_CFG     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG0_WAKEUP_DLY_CFG(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * BIST FSM: threshold to enter FINISHED state
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG0 . MAX_BIST_FRAMES_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG0_MAX_BIST_FRAMES_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG0_MAX_BIST_FRAMES_CFG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG0_MAX_BIST_FRAMES_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief DFT BIST configuration register 1
 *
 * \details
 * BIST configuration register for SD10G65 DFT	controlling 'stable' mode.
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_BIST_CFG1
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG1(target)  VTSS_IOREG(target,0x35)

/** 
 * \brief
 * BIST FSM: threshold to iterate counter for max_stable_attempts
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG1 . MAX_UNSTABLE_CYC_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG1_MAX_UNSTABLE_CYC_CFG(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG1_MAX_UNSTABLE_CYC_CFG     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG1_MAX_UNSTABLE_CYC_CFG(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * BIST FSM: threshold to enter CHECK state
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG1 . STABLE_THRES_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG1_STABLE_THRES_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG1_STABLE_THRES_CFG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG1_STABLE_THRES_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief DFT BIST configuration register 2
 *
 * \details
 * BIST configuration register for SD10G65 DFT controlling frame length in
 * 'check' mode.
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_BIST_CFG2
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG2(target)  VTSS_IOREG(target,0x36)

/** 
 * \brief
 * BIST FSM: threshold to iterate counter for max_bist_frames
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG2 . FRAME_LEN_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG2_FRAME_LEN_CFG(x)  (x)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG2_FRAME_LEN_CFG     0xffffffff
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG2_FRAME_LEN_CFG(x)  (x)


/** 
 * \brief DFT BIST configuration register 3
 *
 * \details
 * BIST configuration register for SD10G65 DFT controlling stable attempts
 * in ' wait-stable' mode.
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_BIST_CFG3
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG3(target)  VTSS_IOREG(target,0x37)

/** 
 * \brief
 * BIST FSM: threshold to enter SYNC_ERR state
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG3 . MAX_STABLE_ATTEMPTS_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG3_MAX_STABLE_ATTEMPTS_CFG(x)  (x)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG3_MAX_STABLE_ATTEMPTS_CFG     0xffffffff
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_BIST_CFG3_MAX_STABLE_ATTEMPTS_CFG(x)  (x)


/** 
 * \brief DFT error status register
 *
 * \details
 * Status register for SD10G65 DFT containing the error counter value
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_ERR_STAT
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_ERR_STAT(target)  VTSS_IOREG(target,0x38)

/** 
 * \brief
 * Counter output depending on cnt_cfg
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_ERR_STAT . ERR_CNT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_ERR_STAT_ERR_CNT(x)  (x)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_ERR_STAT_ERR_CNT     0xffffffff
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_ERR_STAT_ERR_CNT(x)  (x)


/** 
 * \brief DFT PRBS status register
 *
 * \details
 * Status register for SD10G65 DFT containing the PRBS data related to 1st
 * sync lost event
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_PRBS_STAT
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_PRBS_STAT(target)  VTSS_IOREG(target,0x39)

/** 
 * \brief
 * PRBS data after first sync lost
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_PRBS_STAT . PRBS_DATA_STAT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_PRBS_STAT_PRBS_DATA_STAT(x)  (x)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_PRBS_STAT_PRBS_DATA_STAT     0xffffffff
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_PRBS_STAT_PRBS_DATA_STAT(x)  (x)


/** 
 * \brief DFT miscellaneous status register
 *
 * \details
 * Status register for SD10G65 DFT
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_MAIN_STAT
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT(target)  VTSS_IOREG(target,0x3a)

/** 
 * \brief
 * 10 bits data word at address 'read_addr_cfg' used for further
 * observation by SW
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT . CMP_DATA_STAT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_CMP_DATA_STAT(x)  VTSS_ENCODE_BITFIELD(x,8,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_CMP_DATA_STAT     VTSS_ENCODE_BITMASK(8,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_CMP_DATA_STAT(x)  VTSS_EXTRACT_BITFIELD(x,8,10)

/** 
 * \brief
 * Data input is unchanged for all 40 parallel bits for at least 7 clock
 * cycles (defined by c_STCK_CNT_THRES)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT . STUCK_AT_PAR
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_STUCK_AT_PAR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_STUCK_AT_PAR  VTSS_BIT(5)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_STUCK_AT_PAR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Data input is constantly 0 or constantly 1 for all 40 parallel bits for
 * at least 7 clock cycles (defined by c_STCK_CNT_THRES)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT . STUCK_AT_01
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_STUCK_AT_01(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_STUCK_AT_01  VTSS_BIT(4)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_STUCK_AT_01(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * BIST: no sync found since BIST enabled
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT . NO_SYNC
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_NO_SYNC(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_NO_SYNC  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_NO_SYNC(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * BIST: input data not stable
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT . INSTABLE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_INSTABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_INSTABLE  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_INSTABLE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * BIST not complete (i.e. not reached stable state or following)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT . INCOMPLETE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_INCOMPLETE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_INCOMPLETE  VTSS_BIT(1)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_INCOMPLETE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * BIST is active (i.e. left DOZE but did not enter a final state)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT . ACTIVE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_ACTIVE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_ACTIVE  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_MAIN_STAT_ACTIVE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief DFT Main configuration register
 *
 * \details
 * Main configuration register for SD10G65 DFT.
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_TX_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG(target)  VTSS_IOREG(target,0x3b)

/** 
 * \brief
 * Enables (1) reset of PRBS generator in case of unchanged data
 * ('stuck-at') for at least 511 clock cycles. Can be disabled (0) e.g. in
 * scrambler mode to avoid the very rare case that input patterns allow to
 * keep the generator's shift register filled with a constant value.
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG . RST_ON_STUCK_AT_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_RST_ON_STUCK_AT_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_RST_ON_STUCK_AT_CFG  VTSS_BIT(12)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_RST_ON_STUCK_AT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Selects SER interface width
 *
 * \details 
 * 0:8
 * 1:10
 * 2:16
 * 3:20
 * 4:32
 * 5:40 (default)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG . TX_WID_SEL_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_TX_WID_SEL_CFG(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_TX_WID_SEL_CFG     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_TX_WID_SEL_CFG(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * Selects PRBS generator
 *
 * \details 
 * 0: prbs7
 * 1: prbs15
 * 2: prbs23
 * 3: prbs11
 * 4: prbs31 (default)
 * 5: prbs9
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG . TX_PRBS_SEL_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_TX_PRBS_SEL_CFG(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_TX_PRBS_SEL_CFG     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_TX_PRBS_SEL_CFG(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Inverts the scrambler output
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG . SCRAM_INV_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_SCRAM_INV_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_SCRAM_INV_CFG  VTSS_BIT(5)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_SCRAM_INV_CFG(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Selects PRBS generator input
 *
 * \details 
 * 0:pat-gen
 * 1:core
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG . IPATH_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_IPATH_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_IPATH_CFG  VTSS_BIT(4)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_IPATH_CFG(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Selects DFT-TX output
 *
 * \details 
 * 0:PRBS/scrambler (default)
 * 1:bypass

 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG . OPATH_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_OPATH_CFG(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_OPATH_CFG     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_OPATH_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Word width of constant pattern generator
 *
 * \details 
 * 0:bytes mode; 1:10-bits word mode
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG . TX_WORD_MODE_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_TX_WORD_MODE_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_TX_WORD_MODE_CFG  VTSS_BIT(1)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_TX_WORD_MODE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable TX DFT capability
 *
 * \details 
 * 0: Disable DFT
 * 1: Enable DFT
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG . DFT_TX_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_DFT_TX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_DFT_TX_ENA  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_CFG_DFT_TX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief DFT TX Constant pattern configuration register
 *
 * \details
 * TX Constant MSB pattern configuration register for SD10G65 DFT.
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_TX_PAT_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG(target)  VTSS_IOREG(target,0x3c)

/** 
 * \brief
 * Constant patterns are valid to store
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG . PAT_VLD_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG_PAT_VLD_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG_PAT_VLD_CFG  VTSS_BIT(26)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG_PAT_VLD_CFG(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Maximum address in generator (before continuing with address 0)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG . MAX_ADDR_GEN_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG_MAX_ADDR_GEN_CFG(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG_MAX_ADDR_GEN_CFG     VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG_MAX_ADDR_GEN_CFG(x)  VTSS_EXTRACT_BITFIELD(x,18,4)

/** 
 * \brief
 * Current storage address for patterns in generator
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG . STORE_ADDR_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG_STORE_ADDR_CFG(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG_STORE_ADDR_CFG     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG_STORE_ADDR_CFG(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/** 
 * \brief
 * 10 bits word of constant patterns for transmission
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG . PATTERN_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG_PATTERN_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG_PATTERN_CFG     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_PAT_CFG_PATTERN_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief DFT TX constant pattern status register
 *
 * \details
 * Status register for SD10G65 DFT containing the constant patterns used
 * for comparison (last in LEARN mode)
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_TX_CMP_DAT_STAT
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_CMP_DAT_STAT(target)  VTSS_IOREG(target,0x3d)

/** 
 * \brief
 * Scrambler/PRBS generator output unchanged for at least 511 clock cycles
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_CMP_DAT_STAT . TX_STUCK_AT_STICKY
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_CMP_DAT_STAT_TX_STUCK_AT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_CMP_DAT_STAT_TX_STUCK_AT_STICKY  VTSS_BIT(12)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_CMP_DAT_STAT_TX_STUCK_AT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * 10 bits data word at address 'store_addr_cfg' used for further
 * observation by SW
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_CMP_DAT_STAT . PAT_STAT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_CMP_DAT_STAT_PAT_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_CMP_DAT_STAT_PAT_STAT     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_CMP_DAT_STAT_PAT_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief DFT clock compare config
 *
 * \details
 * Configuration register for Clock Compare logic. Compared clocks are
 * always divided by 4 before any further processing. A clock edge on
 * tx_clk increments the counter, a clock edge on rx_clk decrements the
 * counter. If only one clock is selected for clock comparison, the number
 * of clock cycles within a given time can be measured.
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_CLK_CMP_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG(target)  VTSS_IOREG(target,0x3e)

/** 
 * \brief
 * Clock compare value updated toggle bit. Toggles on each update of
 * CLK_CMP_VALUE
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG . CLK_CMP_UPDTOG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_UPDTOG(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_UPDTOG  VTSS_BIT(16)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_UPDTOG(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Clock compare selection
 *
 * \details 
 * 0: rx_clk vs. tx_clk
 * 1: rx_clk
 * 2: tx_clk
 * 3: Reserved
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG . CLK_CMP_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Clock comparison mode
 *
 * \details 
 * 0: single shot
 * 1: continuous
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG . CLK_CMP_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_MODE  VTSS_BIT(1)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable clock comparison (enabling automatically clears comparison
 * counter)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG . CLK_CMP_ENA
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_ENA  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief DFT clock compare timer
 *
 * \details
 * Clock comparison timer. After timer has expired, current clock
 * comparison value is stored. The timer is clocked with core_clk
 * (typically f=250MHz or 4ns period)
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_CLK_CMP_TIMER
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_TIMER(target)  VTSS_IOREG(target,0x3f)

/** 
 * \brief
 * Clock comparison timer
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_TIMER . CLK_CMP_TIMER
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_TIMER_CLK_CMP_TIMER(x)  (x)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_TIMER_CLK_CMP_TIMER     0xffffffff
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_TIMER_CLK_CMP_TIMER(x)  (x)


/** 
 * \brief DFT clock comparison value
 *
 * \details
 * Clock comparison result. This register is updated after clock comparison
 * timer has expired. In continuous mode this register is periodically
 * updated.
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_CLK_CMP_VALUE
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_VALUE(target)  VTSS_IOREG(target,0x40)

/** 
 * \brief
 * Clock comparison value (difference between clk0 and clk1)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_VALUE . CLK_CMP_VALUE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_VALUE_CLK_CMP_VALUE(x)  (x)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_VALUE_CLK_CMP_VALUE     0xffffffff
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_VALUE_CLK_CMP_VALUE(x)  (x)


/** 
 * \brief DFT clock comparison maximum value
 *
 * \details
 * Clock comparison max result. Can be used to judge e.g. SSC clock
 * deviation. This register is updated after clock comparison timer has
 * expired. In continuous mode this register is periodically updated.
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_CLK_CMP_MAXVAL
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_MAXVAL(target)  VTSS_IOREG(target,0x41)

/** 
 * \brief
 * Clock comparison max value (maximum measured difference between clk0 and
 * clk1)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_MAXVAL . CLK_CMP_MAXVAL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_MAXVAL_CLK_CMP_MAXVAL(x)  (x)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_MAXVAL_CLK_CMP_MAXVAL     0xffffffff
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_CLK_CMP_MAXVAL_CLK_CMP_MAXVAL(x)  (x)


/** 
 * \brief DFT TX Error insertion configuration register
 *
 * \details
 * Configuration register for explicit error insertion into DFT driven data
 * stream. Allows to insert expected errors to check e.g. TX/RX
 * connectivity
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_TX_ERR_INSERT_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG(target)  VTSS_IOREG(target,0x42)

/** 
 * \brief
 * Preload value for clock generator timer
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG . CG_TIMER_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_CG_TIMER_CFG(x)  VTSS_ENCODE_BITFIELD(x,22,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_CG_TIMER_CFG     VTSS_ENCODE_BITMASK(22,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_CG_TIMER_CFG(x)  VTSS_EXTRACT_BITFIELD(x,22,10)

/** 
 * \brief
 * Trigger a single error or a burst of errors (refer to num_err_cfg)
 *
 * \details 
 * 0 to 1 (edge) activates this function
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG . ERR_TRIG_ONESHOT_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_ERR_TRIG_ONESHOT_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_ERR_TRIG_ONESHOT_CFG  VTSS_BIT(20)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_ERR_TRIG_ONESHOT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Frequency of continous/limited error insertion in steps of 40 bits
 *
 * \details 
 * 0: disable continous insertion 1-15: step between 2 errors =
 * 2^(err_freq_cfg + 5) 40 bit words (refer also to err_posit_offs_cfg)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG . ERR_FREQ_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_ERR_FREQ_CFG(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_ERR_FREQ_CFG     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_ERR_FREQ_CFG(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Position within 40 bit word where an error is inserted by inverting the
 * bit value
 *
 * \details 
 * 0: LSB
 * 39: MSB
 * 40-63: reserved
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG . ERR_POSIT_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_ERR_POSIT_CFG(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_ERR_POSIT_CFG     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_ERR_POSIT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Offset of bitposition increased per inserted error; allows 'walking'
 * error. Offset is reset when continous/limited error insertion is
 * disabled or burst mode is enabled and burst insertion is finished or
 * err_posit_offs_cfg = 0
 *
 * \details 
 * 0: disabled
 * 1: move 1 bit (from LSB to MSB)
 * ...
 * 39: move 39 bit (from LSB to MSB)
 * 40-63: reserved
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG . ERR_POSIT_OFFS_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_ERR_POSIT_OFFS_CFG(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_ERR_POSIT_OFFS_CFG     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_ERR_POSIT_OFFS_CFG(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * limited error insertion: burst mode (err_freq_cfg must be > 0)
 *
 * \details 
 * 0: burst mode is disabled 1-15: number of errors after each error
 * triggering = 2^(num_err_cfg + 5)
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG . NUM_ERR_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_NUM_ERR_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_NUM_ERR_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_NUM_ERR_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief DFT clock generator configuration register
 *
 * \details
 * Configuration register for clock generator to build a low speed clock
 * signal of variable length and variable duty cycle provided on all data
 * bits simultaniously
 *
 * Register: \a SD10G65_DIG:SD10G65_DFT:DFT_CLK_GEN_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG(target)  VTSS_IOREG(target,0x43)

/** 
 * \brief
 * (Half) clock period cfg in normal mode: high period = cg_per_cfg +
 * cg_dcd_cfg, low period = cg_per_cfg - cg_dcd_cfg
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG . CG_PER_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG_CG_PER_CFG(x)  VTSS_ENCODE_BITFIELD(x,22,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG_CG_PER_CFG     VTSS_ENCODE_BITMASK(22,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG_CG_PER_CFG(x)  VTSS_EXTRACT_BITFIELD(x,22,10)

/** 
 * \brief
 * (Half) clock period cfg in jump mode: high period = cg_per_cfg +
 * cg_dcd_cfg, low period = cg_per_cfg - cg_dcd_cfg
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG . CG_PER_JUMP_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG_CG_PER_JUMP_CFG(x)  VTSS_ENCODE_BITFIELD(x,12,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG_CG_PER_JUMP_CFG     VTSS_ENCODE_BITMASK(12,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG_CG_PER_JUMP_CFG(x)  VTSS_EXTRACT_BITFIELD(x,12,10)

/** 
 * \brief
 * Duty cycle distortion: high period = cg_per_cfg + cg_dcd_cfg, low period
 * = cg_per_cfg - cg_dcd_cfg
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG . CG_DCD_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG_CG_DCD_CFG(x)  VTSS_ENCODE_BITFIELD(x,2,10)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG_CG_DCD_CFG     VTSS_ENCODE_BITMASK(2,10)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG_CG_DCD_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,10)

/** 
 * \brief
 * clock generator mode
 *
 * \details 
 * 0: normal operation
 * cg_per_cfg controls period; 0->1 transition: after current period has
 * finished (only) the next period is controlled by cg_per_jump_cfg
 * afterwards normal operation; 2: every N'th period the high value is
 * replaced by a low value
 * N is defined by cg_timer_cfg; 3: every N'th period the low value is
 * replaced by a high value
 * N is defined by cg_timer_cfg
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG . CG_MODE_CFG
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG_CG_MODE_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG_CG_MODE_CFG     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_DFT_DFT_CLK_GEN_CFG_CG_MODE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a SD10G65_DIG:SD10G65_SYNC_CTRL
 *
 * SYNC_CTRL Configuration and Status Register set
 */


/** 
 * \brief SYNC_CTRL config register
 *
 * \details
 * Sync control configuration register
 *
 * Register: \a SD10G65_DIG:SD10G65_SYNC_CTRL:SYNC_CTRL_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_SYNC_CTRL_SYNC_CTRL_CFG(target)  VTSS_IOREG(target,0x44)

/** 
 * \brief
 * Source selection for lane synchronization
 *
 * \details 
 * 0: Select external DES
 * 1: Select F2DF
 * 2: Select local DES
 * 3: Disable sync_ctrl
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_SYNC_CTRL_SYNC_CTRL_CFG . LANE_SYNC_SRC
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_SYNC_CTRL_SYNC_CTRL_CFG_LANE_SYNC_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_SYNC_CTRL_SYNC_CTRL_CFG_LANE_SYNC_SRC     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_SYNC_CTRL_SYNC_CTRL_CFG_LANE_SYNC_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief SYNC_CTRL status register
 *
 * \details
 * Sync control status register
 *
 * Register: \a SD10G65_DIG:SD10G65_SYNC_CTRL:SYNC_CTRL_STAT
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_SYNC_CTRL_SYNC_CTRL_STAT(target)  VTSS_IOREG(target,0x45)

/** 
 * \brief
 * Lane synchronization fifo overflow
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_SYNC_CTRL_SYNC_CTRL_STAT . LANE_SYNC_FIFO_OF_STICKY
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_SYNC_CTRL_SYNC_CTRL_STAT_LANE_SYNC_FIFO_OF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_SYNC_CTRL_SYNC_CTRL_STAT_LANE_SYNC_FIFO_OF_STICKY  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_SYNC_CTRL_SYNC_CTRL_STAT_LANE_SYNC_FIFO_OF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief RX_SYNC_CTRL config register
 *
 * \details
 * RX Sync control configuration register, synchronize I2 of one RX to the
 * I2 of another RX
 *
 * Register: \a SD10G65_DIG:SD10G65_SYNC_CTRL:RX_SYNC_CTRL_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_CFG(target)  VTSS_IOREG(target,0x46)

/** 
 * \brief
 * Keep current RX I2 value constant
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_CFG . RX_I2_HOLD
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_CFG_RX_I2_HOLD(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_CFG_RX_I2_HOLD  VTSS_BIT(9)
#define  VTSS_X_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_CFG_RX_I2_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Clear RX I2 value
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_CFG . RX_I2_CLR
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_CFG_RX_I2_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_CFG_RX_I2_CLR  VTSS_BIT(8)
#define  VTSS_X_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_CFG_RX_I2_CLR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Source selection for RX lane synchronization
 *
 * \details 
 * 0: Do not use external sync_ctrl info
 * 1: Select sync_ctrl info from external DES
 *
 * Field: ::VTSS_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_CFG . RX_LANE_SYNC_SRC
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_CFG_RX_LANE_SYNC_SRC(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_CFG_RX_LANE_SYNC_SRC  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_CFG_RX_LANE_SYNC_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief RX_SYNC_CTRL status register
 *
 * \details
 * RX Sync control status register
 *
 * Register: \a SD10G65_DIG:SD10G65_SYNC_CTRL:RX_SYNC_CTRL_STAT
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_STAT(target)  VTSS_IOREG(target,0x47)

/** 
 * \brief
 * RX Lane synchronization fifo overflow
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_STAT . RX_LANE_SYNC_FIFO_OF_STICKY
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_STAT_RX_LANE_SYNC_FIFO_OF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_STAT_RX_LANE_SYNC_FIFO_OF_STICKY  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_SYNC_CTRL_RX_SYNC_CTRL_STAT_RX_LANE_SYNC_FIFO_OF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a SD10G65_DIG:SD10G65_RCPLL_BIST
 *
 * SD10G65 RX and TX RCPLL BIST Configuration and Status Register set
 */


/** 
 * \brief SD10G65 RX RCPLL BIST Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 RX RCPLL BIST.
 *
 * Register: \a SD10G65_DIG:SD10G65_RCPLL_BIST:SD10G65_RCPLL_BIST_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0(target)  VTSS_IOREG(target,0x48)

/** 
 * \brief
 * BIST frequency deviation limit, correlates to compare dividers
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0 . PLLB_FREQ_DEVI
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0_PLLB_FREQ_DEVI(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0_PLLB_FREQ_DEVI     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0_PLLB_FREQ_DEVI(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * BIST compare uncertainty
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0 . PLLB_COMP_UNCERT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0_PLLB_COMP_UNCERT(x)  VTSS_ENCODE_BITFIELD(x,4,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0_PLLB_COMP_UNCERT     VTSS_ENCODE_BITMASK(4,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0_PLLB_COMP_UNCERT(x)  VTSS_EXTRACT_BITFIELD(x,4,8)

/** 
 * \brief
 * BIST ramp-up/down mode, 0: ramp up and down, 1: ramp-up only, 2:
 * ramp-down only, 3: reserved
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0 . PLLB_INC_DEC_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0_PLLB_INC_DEC_MODE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0_PLLB_INC_DEC_MODE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0_PLLB_INC_DEC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * BIST start, 0: reset BIST, 1: start/enable BIST
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0 . PLLB_START_BIST
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0_PLLB_START_BIST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0_PLLB_START_BIST  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG0_PLLB_START_BIST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65 RX RCPLL BIST Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 RX RCPLL BIST.
 *
 * Register: \a SD10G65_DIG:SD10G65_RCPLL_BIST:SD10G65_RCPLL_BIST_CFG1
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG1(target)  VTSS_IOREG(target,0x49)

/** 
 * \brief
 * BIST compare divider repeat count
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG1 . PLLB_LOCK_REPEAT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG1_PLLB_LOCK_REPEAT(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG1_PLLB_LOCK_REPEAT     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG1_PLLB_LOCK_REPEAT(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * BIST compare divider phase uncertainty
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG1 . PLLB_LOCK_UNCERT
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG1_PLLB_LOCK_UNCERT(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG1_PLLB_LOCK_UNCERT     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG1_PLLB_LOCK_UNCERT(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * BIST compare pre divider M
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG1 . PLLB_DIV_FACTOR_PRE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG1_PLLB_DIV_FACTOR_PRE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG1_PLLB_DIV_FACTOR_PRE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG1_PLLB_DIV_FACTOR_PRE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 RX RCPLL BIST Configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 RX RCPLL BIST.
 *
 * Register: \a SD10G65_DIG:SD10G65_RCPLL_BIST:SD10G65_RCPLL_BIST_CFG2
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG2(target)  VTSS_IOREG(target,0x4a)

/** 
 * \brief
 * BIST compare divider M
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG2 . PLLB_DIV_FACTOR_M
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG2_PLLB_DIV_FACTOR_M(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG2_PLLB_DIV_FACTOR_M     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG2_PLLB_DIV_FACTOR_M(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 RX RCPLL BIST Configuration register 3
 *
 * \details
 * Configuration register 3 for SD10G65 RX RCPLL BIST.
 *
 * Register: \a SD10G65_DIG:SD10G65_RCPLL_BIST:SD10G65_RCPLL_BIST_CFG3
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG3(target)  VTSS_IOREG(target,0x4b)

/** 
 * \brief
 * BIST compare divider N
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG3 . PLLB_DIV_FACTOR_N
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG3_PLLB_DIV_FACTOR_N(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG3_PLLB_DIV_FACTOR_N     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_CFG3_PLLB_DIV_FACTOR_N(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 RX RCPLL BIST Configuration register 4
 *
 * \details
 * Configuration register 4 for SD10G65 RX RCPLL BIST.
 *
 * Register: \a SD10G65_DIG:SD10G65_RCPLL_BIST:SD10G65_RX_RCPLL_BIST_CFG4
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4(target)  VTSS_IOREG(target,0x4c)

/** 
 * \brief
 * BIST SPI base address for rcpll10g FSM inside the macro (e.g. RX or TX)
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4 . PLLB_SPI_BASE_ADDR
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_SPI_BASE_ADDR(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_SPI_BASE_ADDR     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_SPI_BASE_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * BIST select 125MHz feedback clock from synthesizer
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4 . PLLB_SEL125CLK
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_SEL125CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_SEL125CLK  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_SEL125CLK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * BIST start measure, 1: start
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4 . PLLB_START_MEAS
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_START_MEAS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_START_MEAS  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_START_MEAS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * BIST measure mode, 0: frequency, 1: phase
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4 . PLLB_MEAS_MODE
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_MEAS_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_MEAS_MODE  VTSS_BIT(1)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_MEAS_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * BIST macro clock (parallel) clock selection, 0: RX, 1: TX
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4 . PLLB_CLOCK_SEL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_CLOCK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_CLOCK_SEL  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4_PLLB_CLOCK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65 RX RCPLL BIST Status register 0
 *
 * \details
 * Status register 0 for SD10G65 RX RCPLL BIST.
 *
 * Register: \a SD10G65_DIG:SD10G65_RCPLL_BIST:SD10G65_RCPLL_BIST_STAT0
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0(target)  VTSS_IOREG(target,0x4d)

/** 
 * \brief
 * BIST pll_cnt upper limit at max. frequency
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0 . PLLB_PLL_CNT_HIGH
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_PLL_CNT_HIGH(x)  VTSS_ENCODE_BITFIELD(x,16,11)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_PLL_CNT_HIGH     VTSS_ENCODE_BITMASK(16,11)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_PLL_CNT_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,16,11)

/** 
 * \brief
 * BIST pll_cnt lower limit at min. frequency
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0 . PLLB_PLL_CNT_LOW
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_PLL_CNT_LOW(x)  VTSS_ENCODE_BITFIELD(x,5,11)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_PLL_CNT_LOW     VTSS_ENCODE_BITMASK(5,11)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_PLL_CNT_LOW(x)  VTSS_EXTRACT_BITFIELD(x,5,11)

/** 
 * \brief
 * BIST compare divider phase lock
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0 . PLLB_PHASE_LOCK
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_PHASE_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_PHASE_LOCK  VTSS_BIT(3)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_PHASE_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * BIST busy, 0: not busy, 1: busy
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0 . PLLB_BUSY
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_BUSY  VTSS_BIT(2)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * BIST done (inverted), 0: done, 1: not done
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0 . PLLB_DONE_N
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_DONE_N(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_DONE_N  VTSS_BIT(1)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_DONE_N(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * BIST pass/fail, 0: passed, 1: failed
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0 . PLLB_FAIL
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_FAIL  VTSS_BIT(0)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT0_PLLB_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65 RX RCPLL BIST Status register 1
 *
 * \details
 * Status register 1 for SD10G65 RX RCPLL BIST.
 *
 * Register: \a SD10G65_DIG:SD10G65_RCPLL_BIST:SD10G65_RCPLL_BIST_STAT1
 *
 * @param target A \a ::vtss_target_SD10G65_DIG_e target
 */
#define VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT1(target)  VTSS_IOREG(target,0x4e)

/** 
 * \brief
 * BIST compare divider phase difference
 *
 * \details 
 * Field: ::VTSS_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT1 . PLLB_PHASE_DIFF
 */
#define  VTSS_F_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT1_PLLB_PHASE_DIFF(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT1_PLLB_PHASE_DIFF     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_DIG_SD10G65_RCPLL_BIST_SD10G65_RCPLL_BIST_STAT1_PLLB_PHASE_DIFF(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_SERVALT_REGS_SD10G65_DIG_H_ */
