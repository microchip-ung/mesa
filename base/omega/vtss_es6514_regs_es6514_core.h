#ifndef _VTSS_ES6514_REGS_ES6514_CORE_H_
#define _VTSS_ES6514_REGS_ES6514_CORE_H_

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

#include "vtss_es6514_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a ES6514_CORE
 *
 * Configuration and status register collection for common blocks: CORE,
 * PLL5G, RCOMP
 *
 ***********************************************************************/

/**
 * Register Group: \a ES6514_CORE:ES6514_CORE
 *
 * CORE Configuration Registers
 */


/** 
 * \brief ES6514 Los of Lock configuration registers
 *
 * \details
 * Configuration register Los of lock generation or emulation
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_LOL_CFG1
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x0)

/** 
 * \brief
 * Value to be forced to los of lock for channel 3
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1 . CH3_FORCE_LOL_VAL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1_CH3_FORCE_LOL_VAL  VTSS_ES6514_BIT(11)

/** 
 * \brief
 * Value to be forced to los of lock for channel 2
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1 . CH2_FORCE_LOL_VAL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1_CH2_FORCE_LOL_VAL  VTSS_ES6514_BIT(10)

/** 
 * \brief
 * Value to be forced to los of lock for channel 1 if CH1_PLL_LOCK_ENA is
 * set to 1
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1 . CH1_FORCE_LOL_VAL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1_CH1_FORCE_LOL_VAL  VTSS_ES6514_BIT(9)

/** 
 * \brief
 * Enable to force CH1_FORCE_LOL_VAL to los of lock for channel 1
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1 . CH1_FORCE_LOL_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1_CH1_FORCE_LOL_ENA  VTSS_ES6514_BIT(8)

/** 
 * \brief
 * Enable PLL lock form Des0 to contribute to los of lock for channel 1
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1 . CH1_PLL_LOCK_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1_CH1_PLL_LOCK_ENA  VTSS_ES6514_BIT(7)

/** 
 * \brief
 * Enable side detect form Des0 to contribute to los of lock for channel 1
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1 . CH1_SIDE_DET_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1_CH1_SIDE_DET_ENA  VTSS_ES6514_BIT(6)

/** 
 * \brief
 * Enable toggle detect form Des0 to contribute to los of lock for channel
 * 1
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1 . CH1_TOG_DET_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1_CH1_TOG_DET_ENA  VTSS_ES6514_BIT(5)

/** 
 * \brief
 * Value to be forced to los of lock for channel 0 if CH0_PLL_LOCK_ENA is
 * set to 1
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1 . CH0_FORCE_LOL_VAL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1_CH0_FORCE_LOL_VAL  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * Enable to force CH0_FORCE_LOL_VAL to los of lock for channel 0
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1 . CH0_FORCE_LOL_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1_CH0_FORCE_LOL_ENA  VTSS_ES6514_BIT(3)

/** 
 * \brief
 * Enable PLL lock form Des0 to contribute to los of lock for channel 0
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1 . CH0_PLL_LOCK_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1_CH0_PLL_LOCK_ENA  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * Enable side detect form Des0 to contribute to los of lock for channel 0
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1 . CH0_SIDE_DET_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1_CH0_SIDE_DET_ENA  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Enable toggle detect form Des0 to contribute to los of lock for channel
 * 0
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1 . CH0_TOG_DET_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_LOL_CFG1_CH0_TOG_DET_ENA  VTSS_ES6514_BIT(0)


/** 
 * \brief ES6514 Sync Control Generator configuration registers
 *
 * \details
 * Configuration register for Sync Control Generator 0 connected to lane 2
 * input
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_CDR_SYNC_CTRL_GEN_CFG0
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x1)

/** 
 * \brief
 * Connected to i2_clr input of sync control generator
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0 . SCR_GEN0_I2_CLR
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0_SCR_GEN0_I2_CLR  VTSS_ES6514_BIT(14)

/** 
 * \brief
 * Connected to test_count input of sync control generator
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0 . SCR_GEN0_TEST_COUT
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0_SCR_GEN0_TEST_COUT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0_SCR_GEN0_TEST_COUT     VTSS_ES6514_ENCODE_BITMASK(4,10)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0_SCR_GEN0_TEST_COUT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,4,10)

/** 
 * \brief
 * Connected to test_mode input of sync control generator 0: INC, 1: DEC,
 * 2: WOBBLE
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0 . SCR_GEN0_TEST_MODE
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0_SCR_GEN0_TEST_MODE(x)  VTSS_ES6514_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0_SCR_GEN0_TEST_MODE     VTSS_ES6514_ENCODE_BITMASK(2,2)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0_SCR_GEN0_TEST_MODE(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Connected to test_trigger input of sync control generator
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0 . SCR_GEN0_TEST_TRIGGER
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0_SCR_GEN0_TEST_TRIGGER  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Connected to test_enable input of sync control generator
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0 . SCR_GEN0_TEST_ENABLE
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG0_SCR_GEN0_TEST_ENABLE  VTSS_ES6514_BIT(0)


/** 
 * \brief ES6514 Sync Control Generator configuration registers
 *
 * \details
 * Configuration register for Sync Control Generator 1 connected to lane 3
 * input
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_CDR_SYNC_CTRL_GEN_CFG1
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x2)

/** 
 * \brief
 * Connected to i2_clr input of sync control generator
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1 . SCR_GEN1_I2_CLR
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1_SCR_GEN1_I2_CLR  VTSS_ES6514_BIT(14)

/** 
 * \brief
 * Connected to test_count input of sync control generator
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1 . SCR_GEN1_TEST_COUT
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1_SCR_GEN1_TEST_COUT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1_SCR_GEN1_TEST_COUT     VTSS_ES6514_ENCODE_BITMASK(4,10)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1_SCR_GEN1_TEST_COUT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,4,10)

/** 
 * \brief
 * Connected to test_mode input of sync control generator 0: INC, 1: DEC,
 * 2: WOBBLE
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1 . SCR_GEN1_TEST_MODE
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1_SCR_GEN1_TEST_MODE(x)  VTSS_ES6514_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1_SCR_GEN1_TEST_MODE     VTSS_ES6514_ENCODE_BITMASK(2,2)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1_SCR_GEN1_TEST_MODE(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Connected to test_trigger input of sync control generator
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1 . SCR_GEN1_TEST_TRIGGER
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1_SCR_GEN1_TEST_TRIGGER  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Connected to test_enable input of sync control generator
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1 . SCR_GEN1_TEST_ENABLE
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CDR_SYNC_CTRL_GEN_CFG1_SCR_GEN1_TEST_ENABLE  VTSS_ES6514_BIT(0)


/** 
 * \brief ES6514 Core Omega Soft IP control registers
 *
 * \details
 * Configuration register for Omega Soft IP
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_OMG_CTRL_CFG
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x3)

/** 
 * \brief
 * Set input selector for ser 1
 *
 * \details 
 * 0: select channel0 to be source
 * 1: select channel1 to be source
 * 2: select channel2 to be source
 * 3: select channel3 to be source
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG . SER1_MUX_CTRL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_SER1_MUX_CTRL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_SER1_MUX_CTRL     VTSS_ES6514_ENCODE_BITMASK(10,2)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_SER1_MUX_CTRL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Set input selector for ser 0
 *
 * \details 
 * 0: Select Channel0 to be source
 * 1: Select Channel1 to be source
 * 2: Select Channel2 to be source
 * 3: Select Channel3 to be source
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG . SER0_MUX_CTRL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_SER0_MUX_CTRL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_SER0_MUX_CTRL     VTSS_ES6514_ENCODE_BITMASK(8,2)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_SER0_MUX_CTRL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Set input selector for channel 3
 *
 * \details 
 * 0: select des0 to be source
 * 1: select des1 to be source
 * 2: select syn control generator1 to be source
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG . CH3_MUX_CTRL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_CH3_MUX_CTRL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_CH3_MUX_CTRL     VTSS_ES6514_ENCODE_BITMASK(6,2)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_CH3_MUX_CTRL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Set input selector for channel 2
 *
 * \details 
 * 0: select des0 to be source
 * 1: select des1 to be source
 * 2: select syn control generator0 to be source
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG . CH2_MUX_CTRL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_CH2_MUX_CTRL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_CH2_MUX_CTRL     VTSS_ES6514_ENCODE_BITMASK(4,2)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_CH2_MUX_CTRL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Set Omega LOS input to respective value
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG . LOS
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_LOS(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_LOS     VTSS_ES6514_ENCODE_BITMASK(0,4)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_OMG_CTRL_CFG_LOS(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief ES6514 Core Configuration
 *
 * \details
 * Configuration register for ES6514 core logic
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_CORE_CFG
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x4)

/** 
 * \brief
 * Center threshold for RX to TX data fifo. Read or Write will be stopped
 * for n+1 cycles on over- or underflow.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG . FIFO_CENTER_THRESH
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG_FIFO_CENTER_THRESH(x)  VTSS_ES6514_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG_FIFO_CENTER_THRESH     VTSS_ES6514_ENCODE_BITMASK(8,3)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG_FIFO_CENTER_THRESH(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Enable rx_data_valid line (Serdes 0 and 1)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG . RX_DATA_VALID
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG_RX_DATA_VALID(x)  VTSS_ES6514_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG_RX_DATA_VALID     VTSS_ES6514_ENCODE_BITMASK(6,2)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG_RX_DATA_VALID(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Enable PCI_IDLE mode (Serdes 0 and 1)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG . PCI_IDLE
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG_PCI_IDLE(x)  VTSS_ES6514_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG_PCI_IDLE     VTSS_ES6514_ENCODE_BITMASK(4,2)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG_PCI_IDLE(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Enable IDDQ mode (low active)
 *
 * \details 
 * 1: IDDQ inactive
 * 0: IDDQ active
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG . IDDQ_N
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG_IDDQ_N  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Perform a software reset
 *
 * \details 
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG . SOFT_RESET
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_CFG_SOFT_RESET  VTSS_ES6514_BIT(0)


/** 
 * \brief ES6514 core fifo status
 *
 * \details
 * Core fifo status register.
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_CORE_FIFO_STATUS
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_FIFO_STATUS  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x5)

/** 
 * \brief
 * Clear fifo (DES.1 to SER.0) overflow and fifo underflow sticky bits
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_FIFO_STATUS . FIFO_ERR_1TO0_CLR
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_FIFO_STATUS_FIFO_ERR_1TO0_CLR  VTSS_ES6514_BIT(6)

/** 
 * \brief
 * Fifo (DES.1 to SER.0) overflow error occured (sticky bit)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_FIFO_STATUS . FIFO_OF_ERR_1TO0
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_FIFO_STATUS_FIFO_OF_ERR_1TO0  VTSS_ES6514_BIT(5)

/** 
 * \brief
 * Fifo (DES.1 to SER.0) underflow error occured (sticky bit)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_FIFO_STATUS . FIFO_UF_ERR_1TO0
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_FIFO_STATUS_FIFO_UF_ERR_1TO0  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * Clear fifo (DES.0 to SER.1) overflow and fifo underflow sticky bits
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_FIFO_STATUS . FIFO_ERR_0TO1_CLR
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_FIFO_STATUS_FIFO_ERR_0TO1_CLR  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * Fifo (DES.0 to SER.1) overflow error occured (sticky bit)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_FIFO_STATUS . FIFO_OF_ERR_0TO1
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_FIFO_STATUS_FIFO_OF_ERR_0TO1  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Fifo (DES.0 to SER.1) underflow error occured (sticky bit)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_FIFO_STATUS . FIFO_UF_ERR_0TO1
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_FIFO_STATUS_FIFO_UF_ERR_0TO1  VTSS_ES6514_BIT(0)


/** 
 * \brief ES6514 core observe config 0
 *
 * \details
 * Observability configuration register
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_CORE_OBS_CFG0
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x6)

/** 
 * \brief
 * Enable analog output PAD / buffer
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0 . AOUT_BUF_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_AOUT_BUF_ENA  VTSS_ES6514_BIT(30)

/** 
 * \brief
 * Enable test mux output
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0 . DD_TEST_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_DD_TEST_ENA  VTSS_ES6514_BIT(29)

/** 
 * \brief
 * Configure output divider for test output. Divider ratio is
 * 1:2^GPIO_TEST_DIV
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0 . DD_TEST_DIV
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_DD_TEST_DIV(x)  VTSS_ES6514_ENCODE_BITFIELD(x,26,3)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_DD_TEST_DIV     VTSS_ES6514_ENCODE_BITMASK(26,3)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_DD_TEST_DIV(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,26,3)

/** 
 * \brief
 * Select input for test output
 *
 * \details 
 * 0: rx0_clk
 * 1: tx0_clk
 * 2: rx1_clk
 * 3: tx1_clk
 * 4: cp0
 * 5: md0
 * 6: cp1
 * 7: md1
 * 8: rx0_pll_lock
 * 9: tx0_pll_lock
 * 10: rx1_pll_lock
 * 11: tx1_pll_lock
 * 12: f2df0_tog_det
 * 13: f2df0_side_det
 * 14: f2df1_tog_det
 * 15: f2df1_side_det
 * 16: ib0_clip_detect
 * 17: ib1_clip_detect
 * 18: direct_data0
 * 19: direct_data1
 * 20: acjtag0_stat[0]
 * 21: acjtag0_stat[1]
 * 22: acjtag1_stat[0]
 * 23: acjtag1_stat[1]
 * 24: ssc_sync0
 * 25: ssc_sync1
 * 26: sig_det0
 * 27: sig_det1
 * 28: rec_det0
 * 29: rec_det1
 * 30: ib0_offset
 * 31: ib1_offset
 * 32: omega_ip_irq
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0 . DD_TEST_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_DD_TEST_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,20,6)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_DD_TEST_SEL     VTSS_ES6514_ENCODE_BITMASK(20,6)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_DD_TEST_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,20,6)

/** 
 * \brief
 * Enable test mux output
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0 . GPIO_TEST_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_GPIO_TEST_ENA  VTSS_ES6514_BIT(19)

/** 
 * \brief
 * Configure output divider for test output. Divider ratio is
 * 1:2^GPIO_TEST_DIV
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0 . GPIO_TEST_DIV
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_GPIO_TEST_DIV(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_GPIO_TEST_DIV     VTSS_ES6514_ENCODE_BITMASK(16,3)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_GPIO_TEST_DIV(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * Select input for test output
 *
 * \details 
 * 0: rx0_clk
 * 1: tx0_clk
 * 2: rx1_clk
 * 3: tx1_clk
 * 4: cp0
 * 5: md0
 * 6: cp1
 * 7: md1
 * 8: rx0_pll_lock
 * 9: tx0_pll_lock
 * 10: rx1_pll_lock
 * 11: tx1_pll_lock
 * 12: f2df0_tog_det
 * 13: f2df0_side_det
 * 14: f2df1_tog_det
 * 15: f2df1_side_det
 * 16: ib0_clip_detect
 * 17: ib1_clip_detect
 * 18: direct_data0
 * 19: direct_data1
 * 20: acjtag0_stat[0]
 * 21: acjtag0_stat[1]
 * 22: acjtag1_stat[0]
 * 23: acjtag1_stat[1]
 * 24: ssc_sync0
 * 25: ssc_sync1
 * 26: sig_det0
 * 27: sig_det1
 * 28: rec_det0
 * 29: rec_det1
 * 30: ib0_offset
 * 31: ib1_offset
 * 32: omega_ip_irq
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0 . GPIO_TEST_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_GPIO_TEST_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_GPIO_TEST_SEL     VTSS_ES6514_ENCODE_BITMASK(10,6)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_GPIO_TEST_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Enable test mux output
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0 . EXT_TEST_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_EXT_TEST_ENA  VTSS_ES6514_BIT(9)

/** 
 * \brief
 * Configure output divider for test output. Divider ratio is
 * 1:2^EXT_TEST_DIV
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0 . EXT_TEST_DIV
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_EXT_TEST_DIV(x)  VTSS_ES6514_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_EXT_TEST_DIV     VTSS_ES6514_ENCODE_BITMASK(6,3)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_EXT_TEST_DIV(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Select input for test output
 *
 * \details 
 * 0: rx0_clk
 * 1: tx0_clk
 * 2: rx1_clk
 * 3: tx1_clk
 * 4: cp0
 * 5: md0
 * 6: cp1
 * 7: md1
 * 8: rx0_pll_lock
 * 9: tx0_pll_lock
 * 10: rx1_pll_lock
 * 11: tx1_pll_lock
 * 12: f2df0_tog_det
 * 13: f2df0_side_det
 * 14: f2df1_tog_det
 * 15: f2df1_side_det
 * 16: ib0_clip_detect
 * 17: ib1_clip_detect
 * 18: direct_data0
 * 19: direct_data1
 * 20: acjtag0_stat[0]
 * 21: acjtag0_stat[1]
 * 22: acjtag1_stat[0]
 * 23: acjtag1_stat[1]
 * 24: ssc_sync0
 * 25: ssc_sync1
 * 26: sig_det0
 * 27: sig_det1
 * 28: rec_det0
 * 29: rec_det1
 * 30: ib0_offset
 * 31: ib1_offset
 * 32: omega_ip_irq
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0 . EXT_TEST_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_EXT_TEST_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_EXT_TEST_SEL     VTSS_ES6514_ENCODE_BITMASK(0,6)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG0_EXT_TEST_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief ES6514 core observe config 1
 *
 * \details
 * Observability configuration register
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_CORE_OBS_CFG1
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x7)

/** 
 * \brief
 * SerDes0: Optional source of cp/md signals.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . CPMD0_FRC
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_CPMD0_FRC(x)  VTSS_ES6514_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_CPMD0_FRC     VTSS_ES6514_ENCODE_BITMASK(26,2)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_CPMD0_FRC(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * SerDes0: Select cp/md source: 0: cpmd0_frc; 1: loopback cp/md form macro
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . CPMD0_SRC_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_CPMD0_SRC_SEL  VTSS_ES6514_BIT(25)

/** 
 * \brief
 * SerDes0: Select sync. source for SSC generator: 0: ss0_frc; 1: sync
 * signal from SSC generator of SerDes1
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . SS0_SRC_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_SS0_SRC_SEL  VTSS_ES6514_BIT(24)

/** 
 * \brief
 * SerDes0: Optional sync. source for SSC generator.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . SS0_FRC
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_SS0_FRC  VTSS_ES6514_BIT(23)

/** 
 * \brief
 * SerDes0: Enable TX direct data path.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . DD0_TX_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_DD0_TX_ENA  VTSS_ES6514_BIT(22)

/** 
 * \brief
 * SerDes0: Enable RX direct data path.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . DD0_RX_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_DD0_RX_ENA  VTSS_ES6514_BIT(21)

/** 
 * \brief
 * SerDes0: Optional source for direct data out.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . DD0_FRC
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_DD0_FRC  VTSS_ES6514_BIT(20)

/** 
 * \brief
 * SerDes0: Select source signal for direct data output: 0: DD0_FRC output,
 * 1: Direct data in from Serdes1, 2: Core_clk/8, 3: Ddr_clk
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . DD0_SRC_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_DD0_SRC_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_DD0_SRC_SEL     VTSS_ES6514_ENCODE_BITMASK(18,2)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_DD0_SRC_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * SerDes1: Optional source of cp/md signals.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . CPMD1_FRC
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_CPMD1_FRC(x)  VTSS_ES6514_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_CPMD1_FRC     VTSS_ES6514_ENCODE_BITMASK(10,2)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_CPMD1_FRC(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * SerDes1: Select cp/md source: 0: cpmd1_frc; 1: loopback cp/md form macro
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . CPMD1_SRC_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_CPMD1_SRC_SEL  VTSS_ES6514_BIT(9)

/** 
 * \brief
 * SerDes1: Select sync. source for SSC generator: 0: ss1_frc; 1: sync
 * signal from SSC generator of SerDes0
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . SS1_SRC_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_SS1_SRC_SEL  VTSS_ES6514_BIT(8)

/** 
 * \brief
 * SerDes1: Optional sync. source for SSC generator.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . SS1_FRC
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_SS1_FRC  VTSS_ES6514_BIT(7)

/** 
 * \brief
 * SerDes1: Enable TX direct data path.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . DD1_TX_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_DD1_TX_ENA  VTSS_ES6514_BIT(6)

/** 
 * \brief
 * SerDes1: Enable RX direct data path.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . DD1_RX_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_DD1_RX_ENA  VTSS_ES6514_BIT(5)

/** 
 * \brief
 * SerDes1: Optional source for direct data (see dd_test_*)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1 . DD1_FRC
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_OBS_CFG1_DD1_FRC  VTSS_ES6514_BIT(4)


/** 
 * \brief ES6514 core smooth config 0
 *
 * \details
 * Smooth feature configuration register
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_CORE_SMOOTH0
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x8)

/** 
 * \brief
 * SerDes0: AC JTAG b0: enable, b1: init clock, b2: init data P, b3: init
 * data N
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0 . ACJTAG0_CFG
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0_ACJTAG0_CFG(x)  VTSS_ES6514_ENCODE_BITFIELD(x,26,4)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0_ACJTAG0_CFG     VTSS_ES6514_ENCODE_BITMASK(26,4)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0_ACJTAG0_CFG(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,26,4)

/** 
 * \brief
 * SerDes0: AC JTAG b0: capture data P, b1: capture data N
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0 . ACJTAG0_STAT
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0_ACJTAG0_STAT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0_ACJTAG0_STAT     VTSS_ES6514_ENCODE_BITMASK(24,2)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0_ACJTAG0_STAT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * SerDes0: Smooth generator update flag
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0 . SMOOTH0_UPDATE
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0_SMOOTH0_UPDATE  VTSS_ES6514_BIT(23)

/** 
 * \brief
 * SerDes0: Smooth generator control value
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0 . SMOOTH0_VALUE
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0_SMOOTH0_VALUE(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,23)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0_SMOOTH0_VALUE     VTSS_ES6514_ENCODE_BITMASK(0,23)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH0_SMOOTH0_VALUE(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,23)


/** 
 * \brief ES6514 core smooth config 1
 *
 * \details
 * Smooth feature configuration register
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_CORE_SMOOTH1
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x9)

/** 
 * \brief
 * SerDes0: AC JTAG b0: enable, b1: init clock, b2: init data P, b3: init
 * data N
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1 . ACJTAG1_CFG
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1_ACJTAG1_CFG(x)  VTSS_ES6514_ENCODE_BITFIELD(x,26,4)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1_ACJTAG1_CFG     VTSS_ES6514_ENCODE_BITMASK(26,4)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1_ACJTAG1_CFG(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,26,4)

/** 
 * \brief
 * SerDes0: AC JTAG b0: capture data P, b1: capture data N
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1 . ACJTAG1_STAT
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1_ACJTAG1_STAT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1_ACJTAG1_STAT     VTSS_ES6514_ENCODE_BITMASK(24,2)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1_ACJTAG1_STAT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * SerDes0: Smooth generator update flag
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1 . SMOOTH1_UPDATE
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1_SMOOTH1_UPDATE  VTSS_ES6514_BIT(23)

/** 
 * \brief
 * SerDes0: Smooth generator control value
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1 . SMOOTH1_VALUE
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1_SMOOTH1_VALUE(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,23)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1_SMOOTH1_VALUE     VTSS_ES6514_ENCODE_BITMASK(0,23)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_SMOOTH1_SMOOTH1_VALUE(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,23)


/** 
 * \brief ES6514 clock compare config
 *
 * \details
 * Configuration register for Clock Compare logic
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_CORE_CLK_CFG
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0xa)

/** 
 * \brief
 * Clock compare value updated toggle bit. Toggles on each update of
 * CLK_CMP_VALUE
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG . CLK_CMP_UPDTOG
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG_CLK_CMP_UPDTOG  VTSS_ES6514_BIT(16)

/** 
 * \brief
 * Select comparison clock 1
 *
 * \details 
 * 0: rx0_clk
 * 1: tx0_clk
 * 2: rx1_clk
 * 3: tx1_clk
 * 4-7: no clk
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG . CLK_CMP_SEL1
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG_CLK_CMP_SEL1(x)  VTSS_ES6514_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG_CLK_CMP_SEL1     VTSS_ES6514_ENCODE_BITMASK(7,3)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG_CLK_CMP_SEL1(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,7,3)

/** 
 * \brief
 * Select comparison clock 0
 *
 * \details 
 * 0: rx0_clk
 * 1: tx0_clk
 * 2: rx1_clk
 * 3: tx1_clk
 * 4-7: no clk
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG . CLK_CMP_SEL0
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG_CLK_CMP_SEL0(x)  VTSS_ES6514_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG_CLK_CMP_SEL0     VTSS_ES6514_ENCODE_BITMASK(4,3)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG_CLK_CMP_SEL0(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * Clock comparison mode
 *
 * \details 
 * 0: single shot
 * 1: continuous
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG . CLK_CMP_MODE
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG_CLK_CMP_MODE  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Enable clock comparison (enabling automatically clears comparison
 * counter)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG . CLK_CMP_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CFG_CLK_CMP_ENA  VTSS_ES6514_BIT(0)


/** 
 * \brief ES6514 clock compare timer
 *
 * \details
 * Clock comparison timer. After timer has expired, current clock
 * comparison value is stored. The timer is clocked with core_clk
 * (typically f=250MHz or 4ns period)
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_CORE_CLK_TIMER
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_TIMER  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0xb)


/** 
 * \brief ES6514 clock comparison value
 *
 * \details
 * Clock comparison result. This register is updated after clock comparison
 * timer has expired. In continuous mode this register is periodically
 * updated.
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_CORE_CLK_CMPVAL
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_CORE_CLK_CMPVAL  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0xc)


/** 
 * \brief ES6514 PLL5G config
 *
 * \details
 * Additional configuration for PLL5G in ES6514
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_PLL5G_CFG
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_PLL5G_CFG  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0xd)

/** 
 * \brief
 * Ref-Clk Selection
 *
 * \details 
 * 0: 125 MHz
 * 1: 156.25MHz
 * 2: 250MHz
 * 3:312.5MHz
 * 4: 25MHz
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_PLL5G_CFG . REF_CLK_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_PLL5G_CFG_REF_CLK_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_PLL5G_CFG_REF_CLK_SEL     VTSS_ES6514_ENCODE_BITMASK(0,3)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_PLL5G_CFG_REF_CLK_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Ref-Src Selection
 *
 * \details 
 * 0: PAD
 * 1: CML input
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_PLL5G_CFG . REF_CLK_SRC
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_PLL5G_CFG_REF_CLK_SRC  VTSS_ES6514_BIT(3)


/** 
 * \brief ES6514 ID register
 *
 * \details
 * Chip identification register
 *
 * Register: \a ES6514_CORE:ES6514_CORE:ES6514_ID
 */
#define VTSS_ES6514_CORE_ES6514_CORE_ES6514_ID  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0xe)

/** 
 * \brief
 * Revision number
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_ID . REV_ID
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_ID_REV_ID(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_ID_REV_ID     VTSS_ES6514_ENCODE_BITMASK(16,4)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_ID_REV_ID(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Chip identification number
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_CORE_ES6514_ID . CHIP_ID
 */
#define  VTSS_F_ES6514_CORE_ES6514_CORE_ES6514_ID_CHIP_ID(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ES6514_CORE_ES6514_CORE_ES6514_ID_CHIP_ID     VTSS_ES6514_ENCODE_BITMASK(0,16)
#define  VTSS_X_ES6514_CORE_ES6514_CORE_ES6514_ID_CHIP_ID(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a ES6514_CORE:ES6514_PLL5G
 *
 * PLL5G Configuration Registers
 */


/** 
 * \brief PLL5G Configuration 0
 *
 * \details
 * Configuration register 0 for PLL5G
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G:PLL5GL_CFG0
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x20)

/** 
 * \brief
 * setting for core clock divider, division factors for [5:4]
 *
 * \details 
 * 0: 2
 * 1: 4
 * 2: 1
 * 3: 3
 * for [3:0]
 * 0: 4
 * 1: 8
 * 2: 5
 * 3: 9
 * 4: 5
 * 5: 10
 * 6: 6
 * 7: 11
 * 8: 6
 * 9: 12
 * 10: 7
 * 11: 13
 * 12: 7
 * 13: 14
 * 14: 8
 * 15: 15
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . CORE_CLK_DIV
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_CORE_CLK_DIV(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_CORE_CLK_DIV     VTSS_ES6514_ENCODE_BITMASK(0,6)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_CORE_CLK_DIV(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * setting for CPU clock divider (see core_clk_div)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . CPU_CLK_DIV
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_CPU_CLK_DIV(x)  VTSS_ES6514_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_CPU_CLK_DIV     VTSS_ES6514_ENCODE_BITMASK(6,6)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_CPU_CLK_DIV(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * enable BIAS circuitry incl. Bandgap, voltage regulators, etc.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . ENA_BIAS
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_ENA_BIAS  VTSS_ES6514_BIT(12)

/** 
 * \brief
 * enable BIAS for LCPLL VCO output buffer
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . ENA_VCO_BUF
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_ENA_VCO_BUF  VTSS_ES6514_BIT(13)

/** 
 * \brief
 * enable current mode chargepump, mission mode
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . ENA_CP1
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_ENA_CP1  VTSS_ES6514_BIT(14)

/** 
 * \brief
 * enable fine VCO operating point regulator
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . ENA_VCO_CONTRH
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_ENA_VCO_CONTRH  VTSS_ES6514_BIT(15)

/** 
 * \brief
 * setting for chargepump current
 *
 * \details 
 * 0: lowest current
 * 3: highest current
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . SELCPI
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_SELCPI(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_SELCPI     VTSS_ES6514_ENCODE_BITMASK(16,2)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_SELCPI(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * setting for filter resistor value
 *
 * \details 
 * 0: biggest resistance
 * 31: lowest resistance
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . LOOP_BW_RES
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_LOOP_BW_RES(x)  VTSS_ES6514_ENCODE_BITFIELD(x,18,5)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_LOOP_BW_RES     VTSS_ES6514_ENCODE_BITMASK(18,5)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_LOOP_BW_RES(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,18,5)

/** 
 * \brief
 * fine tune of bandgap voltage distribution
 *
 * \details 
 * 0: highest voltage
 * 15: lowest voltage
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . SELBGV820
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_SELBGV820(x)  VTSS_ES6514_ENCODE_BITFIELD(x,23,4)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_SELBGV820     VTSS_ES6514_ENCODE_BITMASK(23,4)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_SELBGV820(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,23,4)

/** 
 * \brief
 * enable fine locking, last stage in startup locking sequence
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . ENA_LOCK_FINE
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_ENA_LOCK_FINE  VTSS_ES6514_BIT(27)

/** 
 * \brief
 * RCPLL feedback divider setting
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . DIV4
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_DIV4  VTSS_ES6514_BIT(28)

/** 
 * \brief
 * RCPLL enable BIAS for clocktree buffer (active low)
 *
 * \details 
 * 0: enable BIAS
 * 1: disable BIAS
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . ENA_CLKTREE
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_ENA_CLKTREE  VTSS_ES6514_BIT(29)

/** 
 * \brief
 * RCPLL Global enable for serdes lane.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . ENA_LANE
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_ENA_LANE  VTSS_ES6514_BIT(30)

/** 
 * \brief
 * RCPLL feedback divider setting
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0 . ENA_ROT
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG0_ENA_ROT  VTSS_ES6514_BIT(31)


/** 
 * \brief PLL5G Configuration 1
 *
 * \details
 * Configuration register 1 for PLL5G
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G:PLL5GL_CFG1
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x21)

/** 
 * \brief
 * RCPLL When set to '1' the value at sx_pll_fsm_ctrl_data_i is not taken
 * as reference value for the FSM, but is directly apllied to the PLL as
 * frequency range setting.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1 . FORCE_SET_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_FORCE_SET_ENA  VTSS_ES6514_BIT(0)

/** 
 * \brief
 * RCPLL Enable for half rate mode
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1 . HALF_RATE
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_HALF_RATE  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * RCPLL Enable recalibration of PLL when out of range is detected
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1 . OUT_OF_RANGE_RECAL_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_OUT_OF_RANGE_RECAL_ENA  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * RCPLL Power down for the RX-path
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1 . PWD_RX
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_PWD_RX  VTSS_ES6514_BIT(3)

/** 
 * \brief
 * RCPLL Power down for the TX-path
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1 . PWD_TX
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_PWD_TX  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * RCPLL Enable for quarter rate mode
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1 . QUARTER_RATE
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_QUARTER_RATE  VTSS_ES6514_BIT(5)

/** 
 * \brief
 * RCPLL Control input for startup FSM
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1 . RC_CTRL_DATA
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_RC_CTRL_DATA(x)  VTSS_ES6514_ENCODE_BITFIELD(x,6,8)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_RC_CTRL_DATA     VTSS_ES6514_ENCODE_BITMASK(6,8)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_RC_CTRL_DATA(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,6,8)

/** 
 * \brief
 * RCPLL Enable for startup FSM
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1 . RC_ENABLE
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_RC_ENABLE  VTSS_ES6514_BIT(14)

/** 
 * \brief
 * RCPLL Selects whether (when set to '1') the frequency range setting from
 * the FSM can be read back at sx_pll_rb_data_o or (when cleared to '0')
 * the measured period.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1 . READBACK_DATA_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_READBACK_DATA_SEL  VTSS_ES6514_BIT(15)

/** 
 * \brief
 * RCPLL feedback divider setting
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1 . ROT_DIR
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_ROT_DIR  VTSS_ES6514_BIT(16)

/** 
 * \brief
 * RCPLL feedback divider setting
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1 . ROT_SPEED
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_ROT_SPEED  VTSS_ES6514_BIT(17)

/** 
 * \brief
 * enable for direct data mode (ATPG/JTAG) reference clock input buffer and
 * test output buffer
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1 . ENA_DIRECT
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG1_ENA_DIRECT  VTSS_ES6514_BIT(18)


/** 
 * \brief PLL5G Configuration 2
 *
 * \details
 * Configuration register 2 for PLL5G
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G:PLL5GL_CFG2
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x22)

/** 
 * \brief
 * enable static VCO frequency stepping
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . ENA_GAIN_TEST
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_ENA_GAIN_TEST  VTSS_ES6514_BIT(0)

/** 
 * \brief
 * disable automatic FSM startup frequency stepping
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . DISABLE_FSM
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_DISABLE_FSM  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * enable FSM frequency deviation detection
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . EN_RESET_FRQ_DET
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_EN_RESET_FRQ_DET  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * enable FSM limiter detection
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . EN_RESET_LIM_DET
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_EN_RESET_LIM_DET  VTSS_ES6514_BIT(3)

/** 
 * \brief
 * enable FSM frequency deviation overrun
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . EN_RESET_OVERRUN
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_EN_RESET_OVERRUN  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * setting for static VCO frequency stepping
 *
 * \details 
 * 0: lowest frequency
 * 31: highest frequency
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . GAIN_TEST
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_GAIN_TEST(x)  VTSS_ES6514_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_GAIN_TEST     VTSS_ES6514_ENCODE_BITMASK(5,5)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_GAIN_TEST(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * disables the startup FSM to start ramp up the frequency from POR
 *
 * \details 
 * 0: normal
 * 1: disable
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . DISABLE_FSM_POR
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_DISABLE_FSM_POR  VTSS_ES6514_BIT(10)

/** 
 * \brief
 * forces the startup FSM to start ramp up the frequency by POR
 *
 * \details 
 * 0: no force
 * 1: force
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . FRC_FSM_POR
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_FRC_FSM_POR  VTSS_ES6514_BIT(11)

/** 
 * \brief
 * enable static VCO amplitude control
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . ENA_AMP_CTRL_FORCE
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_ENA_AMP_CTRL_FORCE  VTSS_ES6514_BIT(12)

/** 
 * \brief
 * enable automatic VCO amplitude control
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . ENA_AMPCTRL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_ENA_AMPCTRL  VTSS_ES6514_BIT(13)

/** 
 * \brief
 * force VCO amplitude control output to low (no VCO current)
 *
 * \details 
 * 0: force
 * 1: no force
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . PWD_AMPCTRL_N
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_PWD_AMPCTRL_N  VTSS_ES6514_BIT(14)

/** 
 * \brief
 * enable clock bypass for all output clocks to come from ref clock pad
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . ENA_CLK_BYPASS
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_ENA_CLK_BYPASS  VTSS_ES6514_BIT(15)

/** 
 * \brief
 * static VCO amplitude control, active w/ ena_amp_ctrl_force
 *
 * \details 
 * 0: lowest current
 * 255: highest current
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . AMPC_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_AMPC_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_AMPC_SEL     VTSS_ES6514_ENCODE_BITMASK(16,8)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_AMPC_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * enable clock bypass for all output clocks to come from extra dividers
 * (125MHz, 250MHz, 312.5MHz)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . ENA_CLK_BYPASS1
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_ENA_CLK_BYPASS1  VTSS_ES6514_BIT(24)

/** 
 * \brief
 * enable resistor mode chargepump, test mode
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . ENA_CP2
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_ENA_CP2  VTSS_ES6514_BIT(25)

/** 
 * \brief
 * enable RCPLL clock buffer in LCPLL VCO (sx_ena_vco_buf_i must be set to
 * 0)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . ENA_RCPLL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_ENA_RCPLL  VTSS_ES6514_BIT(26)

/** 
 * \brief
 * enable feedback divider output to test output buffer
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . ENA_FBTESTOUT
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_ENA_FBTESTOUT  VTSS_ES6514_BIT(27)

/** 
 * \brief
 * enable VCO frequency control output
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . ENA_VCO_NREF_TESTOUT
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_ENA_VCO_NREF_TESTOUT  VTSS_ES6514_BIT(28)

/** 
 * \brief
 * enable flip of refclk and fbclk at PFD, used for 2nd chargepump
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . ENA_PFD_IN_FLIP
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_ENA_PFD_IN_FLIP  VTSS_ES6514_BIT(29)

/** 
 * \brief
 * enables test modes, e.g. fbdivsel
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2 . ENA_TEST_MODE
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG2_ENA_TEST_MODE  VTSS_ES6514_BIT(30)


/** 
 * \brief PLL5G Configuration 3
 *
 * \details
 * Configuration register 3 for PLL5G
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G:PLL5GL_CFG3
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x23)

/** 
 * \brief
 * setting for feedback divider, divide by 8,10,12,13,14,15,..,255
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . FBDIVSEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_FBDIVSEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_FBDIVSEL     VTSS_ES6514_ENCODE_BITMASK(0,8)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_FBDIVSEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * enable feedback divider testmode
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . FBDIVSEL_TST_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_FBDIVSEL_TST_ENA  VTSS_ES6514_BIT(8)

/** 
 * \brief
 * force chargepump output to nominal VCO operating point
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . FORCE_CP
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_FORCE_CP  VTSS_ES6514_BIT(9)

/** 
 * \brief
 * enable force VCO frequency high/low (force_hi/lo)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . FORCE_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_FORCE_ENA  VTSS_ES6514_BIT(10)

/** 
 * \brief
 * force chargepump output to high, gives highest VCO frequency
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . FORCE_HI
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_FORCE_HI  VTSS_ES6514_BIT(11)

/** 
 * \brief
 * force chargepump output to low, gives lowest VCO frequency
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . FORCE_LO
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_FORCE_LO  VTSS_ES6514_BIT(12)

/** 
 * \brief
 * force vco contrh input to mid level (mid CML level)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . FORCE_VCO_CONTRH
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_FORCE_VCO_CONTRH  VTSS_ES6514_BIT(13)

/** 
 * \brief
 * reset for feedback divider, active low
 *
 * \details 
 * 0: reset
 * 1:no reset
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . RST_FB_N
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_RST_FB_N  VTSS_ES6514_BIT(14)

/** 
 * \brief
 * select CML or CMOS phase/frequency detector
 *
 * \details 
 * 0: CML
 * 1: CMOS
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . SEL_CML_CMOS_PFD
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_SEL_CML_CMOS_PFD  VTSS_ES6514_BIT(15)

/** 
 * \brief
 * enable symmetric feedback divider clock output
 *
 * \details 
 * 0: fbclk/2
 * 1: fbclk
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . SEL_FBDCLK
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_SEL_FBDCLK  VTSS_ES6514_BIT(16)

/** 
 * \brief
 * enable differential test output
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . ENA_TEST_OUT
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_ENA_TEST_OUT  VTSS_ES6514_BIT(17)

/** 
 * \brief
 * enable analog test output
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . ENA_ANA_TEST_OUT
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_ENA_ANA_TEST_OUT  VTSS_ES6514_BIT(18)

/** 
 * \brief
 * select test output buffer input signal
 *
 * \details 
 * 0: feedback clock
 * 1: pad reference clock
 * 2: core clock
 * 3: CPU clock
 * 4: lock toggle
 * 5: DDR clock
 * 6: reference clock / 2
 * 7: ext. test input
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . TESTOUT_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_TESTOUT_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_TESTOUT_SEL     VTSS_ES6514_ENCODE_BITMASK(19,3)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_TESTOUT_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,19,3)

/** 
 * \brief
 * select analog test output input signal
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3 . TEST_ANA_OUT_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_TEST_ANA_OUT_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_TEST_ANA_OUT_SEL     VTSS_ES6514_ENCODE_BITMASK(22,2)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG3_TEST_ANA_OUT_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,22,2)


/** 
 * \brief PLL5G Configuration 4
 *
 * \details
 * Configuration register 4 for PLL5G
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G:PLL5GL_CFG4
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG4  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x24)

/** 
 * \brief
 * settings for reference clock input buffer
 *
 * \details 
 * [1:0]: sel_vref490m
 * [9]: ena_cmv_term
 * [10]: ena_ib (not supported in ES6514)
 * [15:12]: r_adj
 * all other bits reserved
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG4 . IB_CTRL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG4_IB_CTRL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG4_IB_CTRL     VTSS_ES6514_ENCODE_BITMASK(0,16)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG4_IB_CTRL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * settings for reference clock input buffer
 *
 * \details 
 * [0]: single_p
 * [1]: single_n
 * [3]: ena_term
 * all other bits reserved
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG4 . IB_BIAS_CTRL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG4_IB_BIAS_CTRL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG4_IB_BIAS_CTRL     VTSS_ES6514_ENCODE_BITMASK(16,8)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG4_IB_BIAS_CTRL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,8)


/** 
 * \brief PLL5G Configuration 5
 *
 * \details
 * Configuration register 5 for PLL5G
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G:PLL5GL_CFG5
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG5  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x25)

/** 
 * \brief
 * settings for test output buffer
 *
 * \details 
 * [3:0]: rsel
 * [8]: ena_cterm_drv
 * [10]: enable_ob
 * [11]: ena_1v
 * [15:12]: sel
 * all other bits reserved
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG5 . OB_CTRL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG5_OB_CTRL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG5_OB_CTRL     VTSS_ES6514_ENCODE_BITMASK(0,16)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG5_OB_CTRL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * settings for test output buffer
 *
 * \details 
 * [1:0]: sel_vref490m
 * [3]: ena_data_cml2cmos
 * [5:4]: sel_ena_abc
 * all other bits reserved
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG5 . OB_BIAS_CTRL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG5_OB_BIAS_CTRL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG5_OB_BIAS_CTRL     VTSS_ES6514_ENCODE_BITMASK(16,8)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG5_OB_BIAS_CTRL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,8)


/** 
 * \brief PLL5G Configuration 6
 *
 * \details
 * Configuration register 6 for PLL5G
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G:PLL5GL_CFG6
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x26)

/** 
 * \brief
 * Setting for DDR clock divider (see core_clk_div)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6 . DDR_CLK_DIV
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_DDR_CLK_DIV(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_DDR_CLK_DIV     VTSS_ES6514_ENCODE_BITMASK(0,6)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_DDR_CLK_DIV(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * enable feedback divider CMOS 1/2 clock (for FSM)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6 . ENA_FBCLKC2
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_ENA_FBCLKC2  VTSS_ES6514_BIT(6)

/** 
 * \brief
 * enable reference CMOS 1/2 clock
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6 . ENA_REFCLKC2
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_ENA_REFCLKC2  VTSS_ES6514_BIT(7)

/** 
 * \brief
 * CML 125MHz refclk divider factor selection 8,10,12,13,14,15,..,255
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6 . DIV125REF_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_DIV125REF_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_DIV125REF_SEL     VTSS_ES6514_ENCODE_BITMASK(8,8)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_DIV125REF_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * select POR delay
 *
 * \details 
 * 0: 500us
 * 1: 1ms
 * 2: 4ms
 * 3: 64ms
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6 . POR_DEL_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_POR_DEL_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_POR_DEL_SEL     VTSS_ES6514_ENCODE_BITMASK(16,2)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_POR_DEL_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * enable clock tree buffer from pll5g to SBUSes
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6 . ENA_CLKTREE_BUF
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_ENA_CLKTREE_BUF  VTSS_ES6514_BIT(18)

/** 
 * \brief
 * select internal ref.clk input buffer or external input
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6 . REFCLK_SRC
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_REFCLK_SRC  VTSS_ES6514_BIT(19)

/** 
 * \brief
 * select ref.clk frequency, 0: 125MHz 1: 156.25MHz 2: 250MHz 3: 312.5MHz
 * 4: 25MHz
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6 . REFCLK_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_REFCLK_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_REFCLK_SEL     VTSS_ES6514_ENCODE_BITMASK(20,3)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_CFG6_REFCLK_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,20,3)


/** 
 * \brief PLL5G Status 0
 *
 * \details
 * Status register 0 for the PLL5G
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G:PLL5GL_STATUS0
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x27)

/** 
 * \brief
 * PLL lock status
 *
 * \details 
 * 0: not locked
 * 1: locked
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0 . LOCK_STATUS
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0_LOCK_STATUS  VTSS_ES6514_BIT(0)

/** 
 * \brief
 * RCPLL Interface to read back internal data of the FSM.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0 . READBACK_DATA
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0_READBACK_DATA(x)  VTSS_ES6514_ENCODE_BITFIELD(x,1,8)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0_READBACK_DATA     VTSS_ES6514_ENCODE_BITMASK(1,8)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0_READBACK_DATA(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,1,8)

/** 
 * \brief
 * RCPLL Flag that indicates that the calibration procedure has finished.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0 . CALIBRATION_DONE
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0_CALIBRATION_DONE  VTSS_ES6514_BIT(9)

/** 
 * \brief
 * RCPLL Flag that indicates errors that may occur during the calibration
 * procedure.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0 . CALIBRATION_ERR
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0_CALIBRATION_ERR  VTSS_ES6514_BIT(10)

/** 
 * \brief
 * RCPLL Flag that indicates a out of range condition while NOT in
 * calibration mode.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0 . OUT_OF_RANGE_ERR
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0_OUT_OF_RANGE_ERR  VTSS_ES6514_BIT(11)

/** 
 * \brief
 * RCPLL Flag range limiter signaling
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0 . RANGE_LIM
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS0_RANGE_LIM  VTSS_ES6514_BIT(12)


/** 
 * \brief PLL5G Status 1
 *
 * \details
 * Status register 1 for the PLL5G
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G:PLL5GL_STATUS1
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x28)

/** 
 * \brief
 * startup FSM lock status
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1 . FSM_LOCK
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1_FSM_LOCK  VTSS_ES6514_BIT(0)

/** 
 * \brief
 * startup FSM internal status
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1 . FSM_STAT
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1_FSM_STAT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1_FSM_STAT     VTSS_ES6514_ENCODE_BITMASK(1,3)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1_FSM_STAT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * VCO frequency difference to refclk
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1 . FBCNT_DIF
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1_FBCNT_DIF(x)  VTSS_ES6514_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1_FBCNT_DIF     VTSS_ES6514_ENCODE_BITMASK(4,10)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1_FBCNT_DIF(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,4,10)

/** 
 * \brief
 * VCO frequency step stop
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1 . GAIN_STAT
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1_GAIN_STAT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1_GAIN_STAT     VTSS_ES6514_ENCODE_BITMASK(16,5)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1_GAIN_STAT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * sigma delta ADC output
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1 . SIG_DEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1_SIG_DEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,21,8)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1_SIG_DEL     VTSS_ES6514_ENCODE_BITMASK(21,8)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_PLL5GL_STATUS1_SIG_DEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,21,8)

/**
 * Register Group: \a ES6514_CORE:ES6514_PLL5G_BIST
 *
 * PLL5G BIST Configuration and Status Register set
 */


/** 
 * \brief PLL5G BIST Configuration register 0
 *
 * \details
 * Configuration register 0 for PLL5G BIST.
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G_BIST:ES6514_PLL5G_BIST_CFG0
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x30)

/** 
 * \brief
 * BIST start, 0: reset BIST, 1: start/enable BIST
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0 . PLLB_START_BIST
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0_PLLB_START_BIST  VTSS_ES6514_BIT(31)

/** 
 * \brief
 * BIST measure mode, 0: frequency, 1: phase
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0 . PLLB_MEAS_MODE
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0_PLLB_MEAS_MODE  VTSS_ES6514_BIT(30)

/** 
 * \brief
 * BIST compare divider repeat count
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0 . PLLB_LOCK_REPEAT
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0_PLLB_LOCK_REPEAT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0_PLLB_LOCK_REPEAT     VTSS_ES6514_ENCODE_BITMASK(20,4)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0_PLLB_LOCK_REPEAT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * BIST compare divider phase uncertainty
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0 . PLLB_LOCK_UNCERT
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0_PLLB_LOCK_UNCERT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0_PLLB_LOCK_UNCERT     VTSS_ES6514_ENCODE_BITMASK(16,4)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0_PLLB_LOCK_UNCERT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * BIST compare pre divider M
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0 . PLLB_DIV_FACTOR_PRE
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0_PLLB_DIV_FACTOR_PRE(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0_PLLB_DIV_FACTOR_PRE     VTSS_ES6514_ENCODE_BITMASK(0,16)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG0_PLLB_DIV_FACTOR_PRE(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PLL5G BIST Configuration register 1
 *
 * \details
 * Configuration register 1 for PLL5G BIST.
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G_BIST:ES6514_PLL5G_BIST_CFG1
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG1  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x31)

/** 
 * \brief
 * BIST compare divider M
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG1 . PLLB_DIV_FACTOR_M
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG1_PLLB_DIV_FACTOR_M(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG1_PLLB_DIV_FACTOR_M     VTSS_ES6514_ENCODE_BITMASK(0,16)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG1_PLLB_DIV_FACTOR_M(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PLL5G BIST Configuration register 2
 *
 * \details
 * Configuration register 2 for PLL5G BIST.
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G_BIST:ES6514_PLL5G_BIST_CFG2
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG2  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x32)

/** 
 * \brief
 * BIST compare divider N
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG2 . PLLB_DIV_FACTOR_N
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG2_PLLB_DIV_FACTOR_N(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG2_PLLB_DIV_FACTOR_N     VTSS_ES6514_ENCODE_BITMASK(0,16)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_CFG2_PLLB_DIV_FACTOR_N(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PLL5G BIST Status register 0
 *
 * \details
 * Status register 0 for PLL5G BIST.
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G_BIST:ES6514_PLL5G_BIST_STAT0
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT0  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x33)

/** 
 * \brief
 * BIST pll_cnt upper limit at max. frequency
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT0 . PLLB_FSM_STAT
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT0_PLLB_FSM_STAT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT0_PLLB_FSM_STAT     VTSS_ES6514_ENCODE_BITMASK(4,4)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT0_PLLB_FSM_STAT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * BIST busy, 0: not busy, 1: busy
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT0 . PLLB_BUSY
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT0_PLLB_BUSY  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * BIST done, 0: done, 1: not done
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT0 . PLLB_DONE_N
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT0_PLLB_DONE_N  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * BIST pass/fail, 0: passed, 1: failed
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT0 . PLLB_FAIL
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT0_PLLB_FAIL  VTSS_ES6514_BIT(0)


/** 
 * \brief PLL5G BIST Status register 1
 *
 * \details
 * Status register 1 for PLL5G BIST.
 *
 * Register: \a ES6514_CORE:ES6514_PLL5G_BIST:ES6514_PLL5G_BIST_STAT1
 */
#define VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT1  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x34)

/** 
 * \brief
 * BIST compare divider phase difference
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT1 . PLLB_CNT_OUT
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT1_PLLB_CNT_OUT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT1_PLLB_CNT_OUT     VTSS_ES6514_ENCODE_BITMASK(16,16)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT1_PLLB_CNT_OUT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * BIST compare divider phase difference
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT1 . PLLB_CNT_REF_DIFF
 */
#define  VTSS_F_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT1_PLLB_CNT_REF_DIFF(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT1_PLLB_CNT_REF_DIFF     VTSS_ES6514_ENCODE_BITMASK(0,16)
#define  VTSS_X_ES6514_CORE_ES6514_PLL5G_BIST_ES6514_PLL5G_BIST_STAT1_PLLB_CNT_REF_DIFF(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a ES6514_CORE:ES6514_RCOMP
 *
 * RCOMP Configuration Registers
 */


/** 
 * \brief RCOMP Configuration 0
 *
 * \details
 * Configuration register 0 for RCOMP
 *
 * Register: \a ES6514_CORE:ES6514_RCOMP:RCOMP_CFG0
 */
#define VTSS_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x40)

/** 
 * \brief
 * Enable power-down after calibration was done
 *
 * \details 
 * 0: disable power-down
 * 1: enable power-down
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0 . PWD_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0_PWD_ENA  VTSS_ES6514_BIT(13)

/** 
 * \brief
 * Start calibration
 *
 * \details 
 * 0: idle/inactive
 * 1: start (activate)
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0 . RUN_CAL
 */
#define  VTSS_F_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0_RUN_CAL  VTSS_ES6514_BIT(12)

/** 
 * \brief
 * Speed selection. Setting time for analog circuit after changing resistor
 * settings.
 *
 * \details 
 * 0: max period
 * 1: max period/2
 * 2: max period/4
 * 3: max period/8
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0 . SPEED_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0_SPEED_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0_SPEED_SEL     VTSS_ES6514_ENCODE_BITMASK(10,2)
#define  VTSS_X_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0_SPEED_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * RCOMP operation mode
 *
 * \details 
 * 0: inactive
 * 1: perform calibration permanently
 * 2: perform calibration once
 * 3: perform calibration once and generate alarm if necessary
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0 . MODE_SEL
 */
#define  VTSS_F_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0_MODE_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0_MODE_SEL     VTSS_ES6514_ENCODE_BITMASK(8,2)
#define  VTSS_X_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0_MODE_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Overwrite measured resistor value with value programmed in rcomp_val
 *
 * \details 
 * 0: normal mode
 * 1: overwrite mode
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0 . FORCE_ENA
 */
#define  VTSS_F_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0_FORCE_ENA  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * Resistor comparator value
 *
 * \details 
 * 0: maximum resistance value
 * 15: minimum resistance value
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0 . RCOMP_VAL
 */
#define  VTSS_F_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0_RCOMP_VAL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0_RCOMP_VAL     VTSS_ES6514_ENCODE_BITMASK(0,4)
#define  VTSS_X_ES6514_CORE_ES6514_RCOMP_RCOMP_CFG0_RCOMP_VAL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief RCOMP Status
 *
 * \details
 * Status register bits for the RCOMP
 *
 * Register: \a ES6514_CORE:ES6514_RCOMP:RCOMP_STATUS
 */
#define VTSS_ES6514_CORE_ES6514_RCOMP_RCOMP_STATUS  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x41)

/** 
 * \brief
 * Resistor comparison activity
 *
 * \details 
 * 0: resistor measurement finished or inactive
 * 1: resistor measurement in progress
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_RCOMP_RCOMP_STATUS . BUSY
 */
#define  VTSS_F_ES6514_CORE_ES6514_RCOMP_RCOMP_STATUS_BUSY  VTSS_ES6514_BIT(12)

/** 
 * \brief
 * Alarm signal if rcomp isn't best choice anymore
 *
 * \details 
 * 0: inactive
 * 1: active
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_RCOMP_RCOMP_STATUS . DELTA_ALERT
 */
#define  VTSS_F_ES6514_CORE_ES6514_RCOMP_RCOMP_STATUS_DELTA_ALERT  VTSS_ES6514_BIT(7)

/** 
 * \brief
 * Measured resistor value
 *
 * \details 
 * 0: maximum resistance value
 * 15: minimum resistance value
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_RCOMP_RCOMP_STATUS . RCOMP
 */
#define  VTSS_F_ES6514_CORE_ES6514_RCOMP_RCOMP_STATUS_RCOMP(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ES6514_CORE_ES6514_RCOMP_RCOMP_STATUS_RCOMP     VTSS_ES6514_ENCODE_BITMASK(0,4)
#define  VTSS_X_ES6514_CORE_ES6514_RCOMP_RCOMP_STATUS_RCOMP(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a ES6514_CORE:ES6514_TMON
 *
 * Register group ES6514_TMON
 */


/** 
 * \brief TMON 0 Configuration register 0
 *
 * \details
 * Configuration register 0 for TMON 0.
 *
 * Register: \a ES6514_CORE:ES6514_TMON:TMON_CFG0
 */
#define VTSS_ES6514_CORE_ES6514_TMON_TMON_CFG0  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x60)

/** 
 * \brief
 * Upper TMON threshold value
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_CFG0 . TMON0_HI_THR
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_CFG0_TMON0_HI_THR(x)  VTSS_ES6514_ENCODE_BITFIELD(x,20,12)
#define  VTSS_M_ES6514_CORE_ES6514_TMON_TMON_CFG0_TMON0_HI_THR     VTSS_ES6514_ENCODE_BITMASK(20,12)
#define  VTSS_X_ES6514_CORE_ES6514_TMON_TMON_CFG0_TMON0_HI_THR(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,20,12)

/** 
 * \brief
 * Lower TMON threshold value
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_CFG0 . TMON0_LO_THR
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_CFG0_TMON0_LO_THR(x)  VTSS_ES6514_ENCODE_BITFIELD(x,8,12)
#define  VTSS_M_ES6514_CORE_ES6514_TMON_TMON_CFG0_TMON0_LO_THR     VTSS_ES6514_ENCODE_BITMASK(8,12)
#define  VTSS_X_ES6514_CORE_ES6514_TMON_TMON_CFG0_TMON0_LO_THR(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,8,12)

/** 
 * \brief
 * Reserved bits for future control setting.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_CFG0 . TMON0_SPARE_CTRL
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_CFG0_TMON0_SPARE_CTRL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_ES6514_CORE_ES6514_TMON_TMON_CFG0_TMON0_SPARE_CTRL     VTSS_ES6514_ENCODE_BITMASK(2,6)
#define  VTSS_X_ES6514_CORE_ES6514_TMON_TMON_CFG0_TMON0_SPARE_CTRL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,2,6)

/** 
 * \brief
 * Start a temperature reading (should be self-clearing)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_CFG0 . TMON0_START
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_CFG0_TMON0_START  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Power Down TMON
 *
 * \details 
 * 0: On
 * 1: Off
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_CFG0 . TMON0_POWER_DOWN
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_CFG0_TMON0_POWER_DOWN  VTSS_ES6514_BIT(0)


/** 
 * \brief TMON 1 Configuration register 0
 *
 * \details
 * Configuration register 1 for TMON 1.
 *
 * Register: \a ES6514_CORE:ES6514_TMON:TMON_CFG1
 */
#define VTSS_ES6514_CORE_ES6514_TMON_TMON_CFG1  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x61)

/** 
 * \brief
 * Upper TMON threshold value
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_CFG1 . TMON1_HI_THR
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_CFG1_TMON1_HI_THR(x)  VTSS_ES6514_ENCODE_BITFIELD(x,20,12)
#define  VTSS_M_ES6514_CORE_ES6514_TMON_TMON_CFG1_TMON1_HI_THR     VTSS_ES6514_ENCODE_BITMASK(20,12)
#define  VTSS_X_ES6514_CORE_ES6514_TMON_TMON_CFG1_TMON1_HI_THR(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,20,12)

/** 
 * \brief
 * Lower TMON threshold value
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_CFG1 . TMON1_LO_THR
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_CFG1_TMON1_LO_THR(x)  VTSS_ES6514_ENCODE_BITFIELD(x,8,12)
#define  VTSS_M_ES6514_CORE_ES6514_TMON_TMON_CFG1_TMON1_LO_THR     VTSS_ES6514_ENCODE_BITMASK(8,12)
#define  VTSS_X_ES6514_CORE_ES6514_TMON_TMON_CFG1_TMON1_LO_THR(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,8,12)

/** 
 * \brief
 * Reserved bits for future control setting.
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_CFG1 . TMON1_SPARE_CTRL
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_CFG1_TMON1_SPARE_CTRL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_ES6514_CORE_ES6514_TMON_TMON_CFG1_TMON1_SPARE_CTRL     VTSS_ES6514_ENCODE_BITMASK(2,6)
#define  VTSS_X_ES6514_CORE_ES6514_TMON_TMON_CFG1_TMON1_SPARE_CTRL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,2,6)

/** 
 * \brief
 * Start a temperature reading (should be self-clearing)
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_CFG1 . TMON1_START
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_CFG1_TMON1_START  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Power Down TMON
 *
 * \details 
 * 0: On
 * 1: Off
 *
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_CFG1 . TMON1_POWER_DOWN
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_CFG1_TMON1_POWER_DOWN  VTSS_ES6514_BIT(0)


/** 
 * \brief TMON 0 Status 0
 *
 * \details
 * Status register 0 of TMON 0.
 *
 * Register: \a ES6514_CORE:ES6514_TMON:TMON_STATUS0
 */
#define VTSS_ES6514_CORE_ES6514_TMON_TMON_STATUS0  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x62)

/** 
 * \brief
 * Spare status bits for TMON
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_STATUS0 . TMON0_SPARE_STATUS
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_STATUS0_TMON0_SPARE_STATUS(x)  VTSS_ES6514_ENCODE_BITFIELD(x,15,8)
#define  VTSS_M_ES6514_CORE_ES6514_TMON_TMON_STATUS0_TMON0_SPARE_STATUS     VTSS_ES6514_ENCODE_BITMASK(15,8)
#define  VTSS_X_ES6514_CORE_ES6514_TMON_TMON_STATUS0_TMON0_SPARE_STATUS(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,15,8)

/** 
 * \brief
 * Indicates that the high threshold was violated
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_STATUS0 . TMON0_ALARM_HI
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_STATUS0_TMON0_ALARM_HI  VTSS_ES6514_BIT(14)

/** 
 * \brief
 * Indicates that the low threshold was violated
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_STATUS0 . TMON0_ALARM_LO
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_STATUS0_TMON0_ALARM_LO  VTSS_ES6514_BIT(13)

/** 
 * \brief
 * Indicates the TMON output is valid
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_STATUS0 . TMON0_DONE
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_STATUS0_TMON0_DONE  VTSS_ES6514_BIT(12)

/** 
 * \brief
 * Value of the TMON output
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_STATUS0 . TMON0_OUTPUT
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_STATUS0_TMON0_OUTPUT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_ES6514_CORE_ES6514_TMON_TMON_STATUS0_TMON0_OUTPUT     VTSS_ES6514_ENCODE_BITMASK(0,12)
#define  VTSS_X_ES6514_CORE_ES6514_TMON_TMON_STATUS0_TMON0_OUTPUT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief TMON 1 Status 1
 *
 * \details
 * Status register 1 of TMON 1.
 *
 * Register: \a ES6514_CORE:ES6514_TMON:TMON_STATUS1
 */
#define VTSS_ES6514_CORE_ES6514_TMON_TMON_STATUS1  VTSS_ES6514_IOREG(VTSS_TO_ES6514_CORE,0x63)

/** 
 * \brief
 * Spare status bits for TMON
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_STATUS1 . TMON1_SPARE_STATUS
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_STATUS1_TMON1_SPARE_STATUS(x)  VTSS_ES6514_ENCODE_BITFIELD(x,15,8)
#define  VTSS_M_ES6514_CORE_ES6514_TMON_TMON_STATUS1_TMON1_SPARE_STATUS     VTSS_ES6514_ENCODE_BITMASK(15,8)
#define  VTSS_X_ES6514_CORE_ES6514_TMON_TMON_STATUS1_TMON1_SPARE_STATUS(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,15,8)

/** 
 * \brief
 * Indicates that the high threshold was violated
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_STATUS1 . TMON1_ALARM_HI
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_STATUS1_TMON1_ALARM_HI  VTSS_ES6514_BIT(14)

/** 
 * \brief
 * Indicates that the low threshold was violated
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_STATUS1 . TMON1_ALARM_LO
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_STATUS1_TMON1_ALARM_LO  VTSS_ES6514_BIT(13)

/** 
 * \brief
 * Indicates the TMON output is valid
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_STATUS1 . TMON1_DONE
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_STATUS1_TMON1_DONE  VTSS_ES6514_BIT(12)

/** 
 * \brief
 * Value of the TMON output
 *
 * \details 
 * Field: ::VTSS_ES6514_CORE_ES6514_TMON_TMON_STATUS1 . TMON1_OUTPUT
 */
#define  VTSS_F_ES6514_CORE_ES6514_TMON_TMON_STATUS1_TMON1_OUTPUT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_ES6514_CORE_ES6514_TMON_TMON_STATUS1_TMON1_OUTPUT     VTSS_ES6514_ENCODE_BITMASK(0,12)
#define  VTSS_X_ES6514_CORE_ES6514_TMON_TMON_STATUS1_TMON1_OUTPUT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,12)


#endif /* _VTSS_ES6514_REGS_ES6514_CORE_H_ */
