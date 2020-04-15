#ifndef _VTSS_SERVAL_REGS_HSIO_H_
#define _VTSS_SERVAL_REGS_HSIO_H_

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

#include "vtss_serval_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a HSIO
 *
 * Register Collection for Control of Macros (SERDES1G, SERDES6G, LCPLL)
 *
 ***********************************************************************/

/**
 * Register Group: \a HSIO:PLL5G_CFG
 *
 * PLL5G Configuration Registers
 */


/** 
 * \brief PLL5G Configuration 0
 *
 * \details
 * Configuration register 0 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG0
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0       VTSS_IOREG(VTSS_TO_HSIO,0x0)


/** 
 * \brief PLL5G Configuration 1
 *
 * \details
 * Configuration register 1 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG1
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1       VTSS_IOREG(VTSS_TO_HSIO,0x1)


/** 
 * \brief PLL5G Configuration 2
 *
 * \details
 * Configuration register 2 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG2
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2       VTSS_IOREG(VTSS_TO_HSIO,0x2)


/** 
 * \brief PLL5G Configuration 3
 *
 * \details
 * Configuration register 3 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG3
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3       VTSS_IOREG(VTSS_TO_HSIO,0x3)


/** 
 * \brief PLL5G Configuration 4
 *
 * \details
 * Configuration register 4 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG4
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG4       VTSS_IOREG(VTSS_TO_HSIO,0x4)


/** 
 * \brief PLL5G Configuration 5
 *
 * \details
 * Configuration register 5 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG5
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG5       VTSS_IOREG(VTSS_TO_HSIO,0x5)


/** 
 * \brief PLL5G Configuration 6
 *
 * \details
 * Configuration register 6 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG6
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG6       VTSS_IOREG(VTSS_TO_HSIO,0x6)

/**
 * Register Group: \a HSIO:PLL5G_STATUS
 *
 * PLL5G Status Registers
 */


/** 
 * \brief PLL5G Status 0
 *
 * \details
 * Status register 0 for the PLL5G
 *
 * Register: \a HSIO:PLL5G_STATUS:PLL5G_STATUS0
 */
#define VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0  VTSS_IOREG(VTSS_TO_HSIO,0x7)

/** 
 * \brief
 * PLL lock status 0: not locked, 1: locked
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0 . LOCK_STATUS
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS0_LOCK_STATUS  VTSS_BIT(0)

/** 
 * \brief
 * RCPLL Interface to read back internal data of the FSM.
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0 . READBACK_DATA
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS0_READBACK_DATA(x)  VTSS_ENCODE_BITFIELD(x,1,8)
#define  VTSS_M_HSIO_PLL5G_STATUS_PLL5G_STATUS0_READBACK_DATA     VTSS_ENCODE_BITMASK(1,8)
#define  VTSS_X_HSIO_PLL5G_STATUS_PLL5G_STATUS0_READBACK_DATA(x)  VTSS_EXTRACT_BITFIELD(x,1,8)

/** 
 * \brief
 * RCPLL Flag that indicates that the calibration procedure has finished.
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0 . CALIBRATION_DONE
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS0_CALIBRATION_DONE  VTSS_BIT(9)

/** 
 * \brief
 * RCPLL Flag that indicates errors that may occur during the calibration
 * procedure.
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0 . CALIBRATION_ERR
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS0_CALIBRATION_ERR  VTSS_BIT(10)

/** 
 * \brief
 * RCPLL Flag that indicates a out of range condition while NOT in
 * calibration mode.
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0 . OUT_OF_RANGE_ERR
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS0_OUT_OF_RANGE_ERR  VTSS_BIT(11)

/** 
 * \brief
 * RCPLL Flag range limiter signaling
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0 . RANGE_LIM
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS0_RANGE_LIM  VTSS_BIT(12)

/**
 * Register Group: \a HSIO:RCOMP_CFG
 *
 * RCOMP Configuration Registers
 */


/** 
 * \brief RCOMP Configuration 0
 *
 * \details
 * Configuration register 0 for RCOMP
 *
 * Register: \a HSIO:RCOMP_CFG:RCOMP_CFG0
 */
#define VTSS_HSIO_RCOMP_CFG_RCOMP_CFG0       VTSS_IOREG(VTSS_TO_HSIO,0x9)

/** 
 * \brief
 * Start calibration
 *
 * \details 
 * 0: idle/inactive
 * 1: start (activate)
 *
 * Field: ::VTSS_HSIO_RCOMP_CFG_RCOMP_CFG0 . RUN_CAL
 */
#define  VTSS_F_HSIO_RCOMP_CFG_RCOMP_CFG0_RUN_CAL  VTSS_BIT(12)

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
 * Field: ::VTSS_HSIO_RCOMP_CFG_RCOMP_CFG0 . MODE_SEL
 */
#define  VTSS_F_HSIO_RCOMP_CFG_RCOMP_CFG0_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HSIO_RCOMP_CFG_RCOMP_CFG0_MODE_SEL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HSIO_RCOMP_CFG_RCOMP_CFG0_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * Register Group: \a HSIO:RCOMP_STATUS
 *
 * RCOMP Status Registers
 */


/** 
 * \brief RCOMP Status
 *
 * \details
 * Status register bits for the RCOMP
 *
 * Register: \a HSIO:RCOMP_STATUS:RCOMP_STATUS
 */
#define VTSS_HSIO_RCOMP_STATUS_RCOMP_STATUS  VTSS_IOREG(VTSS_TO_HSIO,0xa)

/** 
 * \brief
 * Resistor comparison activity
 *
 * \details 
 * 0: resistor measurement finished or inactive
 * 1: resistor measurement in progress
 *
 * Field: ::VTSS_HSIO_RCOMP_STATUS_RCOMP_STATUS . BUSY
 */
#define  VTSS_F_HSIO_RCOMP_STATUS_RCOMP_STATUS_BUSY  VTSS_BIT(12)

/** 
 * \brief
 * Alarm signal if rcomp isn't best choice anymore
 *
 * \details 
 * 0: inactive
 * 1: active
 *
 * Field: ::VTSS_HSIO_RCOMP_STATUS_RCOMP_STATUS . DELTA_ALERT
 */
#define  VTSS_F_HSIO_RCOMP_STATUS_RCOMP_STATUS_DELTA_ALERT  VTSS_BIT(7)

/** 
 * \brief
 * Measured resistor value
 *
 * \details 
 * 0: maximum resistance value
 * 15: minimum resistance value
 *
 * Field: ::VTSS_HSIO_RCOMP_STATUS_RCOMP_STATUS . RCOMP
 */
#define  VTSS_F_HSIO_RCOMP_STATUS_RCOMP_STATUS_RCOMP(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSIO_RCOMP_STATUS_RCOMP_STATUS_RCOMP     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSIO_RCOMP_STATUS_RCOMP_STATUS_RCOMP(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a HSIO:SYNC_ETH_CFG
 *
 * SYNC_ETH Configuration Registers
 */


/** 
 * \brief SYNC ETH Configuration 0
 *
 * \details
 * Configuration register for RCVRD_CLK pad enable (1 bit per recovered
 * clock output)
 *
 * Register: \a HSIO:SYNC_ETH_CFG:SYNC_ETH_CFG0
 */
#define VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG0  VTSS_IOREG(VTSS_TO_HSIO,0xb)

/** 
 * \brief
 * Enable recovered clock pads
 *
 * \details 
 * 0: Disable (high-impedance)
 * 1: Enable (output recovered clock)
 *
 * Field: ::VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG0 . RECO_CLK_ENA
 */
#define  VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG0_RECO_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG0_RECO_CLK_ENA     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG0_RECO_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief SYNC ETH Configuration 1
 *
 * \details
 * Configuration register for RCVRD_CLK selection (1 bit per recovered
 * clock output)
 *
 * Register: \a HSIO:SYNC_ETH_CFG:SYNC_ETH_CFG1
 */
#define VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG1  VTSS_IOREG(VTSS_TO_HSIO,0xc)

/** 
 * \brief
 * select recovered clock source for RCVD_CLK[0] 0-9: select cource
 *
 * \details 
 * 10-15: reserved
 *
 * Field: ::VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG1 . RECO_CLK_SEL0
 */
#define  VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG1_RECO_CLK_SEL0(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG1_RECO_CLK_SEL0     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG1_RECO_CLK_SEL0(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * select common recovered clock source
 *
 * \details 
 * 0: Use individual clock source
 * 1: Use common clock source
 *
 * Field: ::VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG1 . RECO_CLK_SEL
 */
#define  VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG1_RECO_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG1_RECO_CLK_SEL     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG1_RECO_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief SYNC ETH Configuration 2
 *
 * \details
 * Selection register for SYNC_ETH.
 *
 * Register: \a HSIO:SYNC_ETH_CFG:SYNC_ETH_CFG2
 */
#define VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG2  VTSS_IOREG(VTSS_TO_HSIO,0xd)

/** 
 * \brief
 * Select recovered clock divider B
 *
 * \details 
 * 0: No clock dividing
 * 1: Divide clock by 5
 * 2: Divide clock by 4
 * 3: Reserved
 *
 * Field: ::VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG2 . SEL_RECO_CLK_B
 */
#define  VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG2_SEL_RECO_CLK_B(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG2_SEL_RECO_CLK_B     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG2_SEL_RECO_CLK_B(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a HSIO:MCB_PLL5G_RCOMP_CFG
 *
 * MCB PLL5G_RCOMP Configuration Register
 */


/** 
 * \brief MCB PLL5G RCOMP Address Cfg
 *
 * \details
 * Configuration of PLL5G_RCOMP MCB slaves to be accessed
 *
 * Register: \a HSIO:MCB_PLL5G_RCOMP_CFG:MCB_PLL5G_RCOMP_ADDR_CFG
 */
#define VTSS_HSIO_MCB_PLL5G_RCOMP_CFG_MCB_PLL5G_RCOMP_ADDR_CFG  VTSS_IOREG(VTSS_TO_HSIO,0xe)

/** 
 * \brief
 * Initiate a write access to marked PLL5G_RCOMP slaves
 *
 * \details 
 * 0: No write operation pending
 * 1: Initiate write to slaves (kept 1 until write operation has finished)
 *
 * Field: ::VTSS_HSIO_MCB_PLL5G_RCOMP_CFG_MCB_PLL5G_RCOMP_ADDR_CFG . PLL5G_RCOMP_WR_ONE_SHOT
 */
#define  VTSS_F_HSIO_MCB_PLL5G_RCOMP_CFG_MCB_PLL5G_RCOMP_ADDR_CFG_PLL5G_RCOMP_WR_ONE_SHOT  VTSS_BIT(31)

/** 
 * \brief
 * Initiate a read access to marked PLL5G_RCOMP slaves
 *
 * \details 
 * 0: No read operation pending (read op finished after bit has been set)
 * 1: Initiate a read access (kept 1 until read operation has finished)
 *
 * Field: ::VTSS_HSIO_MCB_PLL5G_RCOMP_CFG_MCB_PLL5G_RCOMP_ADDR_CFG . PLL5G_RCOMP_RD_ONE_SHOT
 */
#define  VTSS_F_HSIO_MCB_PLL5G_RCOMP_CFG_MCB_PLL5G_RCOMP_ADDR_CFG_PLL5G_RCOMP_RD_ONE_SHOT  VTSS_BIT(30)

/** 
 * \brief
 * Activation vector for PLL5G_RCOMP-Slaves, one-hot coded, each bit is
 * related to one macro, e.g. bit 0 enables/disables access to macro No. 0
 *
 * \details 
 * 0: Disable macro access via MCB
 * 1: Enable macro access via MCB
 *
 * Field: ::VTSS_HSIO_MCB_PLL5G_RCOMP_CFG_MCB_PLL5G_RCOMP_ADDR_CFG . PLL5G_RCOMP_ADDR
 */
#define  VTSS_F_HSIO_MCB_PLL5G_RCOMP_CFG_MCB_PLL5G_RCOMP_ADDR_CFG_PLL5G_RCOMP_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HSIO_MCB_PLL5G_RCOMP_CFG_MCB_PLL5G_RCOMP_ADDR_CFG_PLL5G_RCOMP_ADDR     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HSIO_MCB_PLL5G_RCOMP_CFG_MCB_PLL5G_RCOMP_ADDR_CFG_PLL5G_RCOMP_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a HSIO:SERDES1G_ANA_CFG
 *
 * SERDES1G Analog Configuration Registers
 */


/** 
 * \brief SERDES1G Deserializer Cfg
 *
 * \details
 * Configuration register for SERDES1G deserializer
 *
 * Register: \a HSIO:SERDES1G_ANA_CFG:SERDES1G_DES_CFG
 */
#define VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG  VTSS_IOREG(VTSS_TO_HSIO,0xf)

/** 
 * \brief
 * Control of phase regulator logic (bit 3 selects input to integrator
 * block - 0: cp/md from DES, 1: cp/md from core)
 *
 * \details 
 * 0: Disabled
 * 1: Enabled with 99 ppm limit
 * 2: Enabled with 202 ppm limit
 * 3: Enabled with 485 ppm limit
 * 4: Enabled if corresponding PCS is in sync with 50 ppm limit
 * 5: Enabled if corresponding PCS is in sync with 99 ppm limit
 * 6: Enabled if corresponding PCS is in sync with 202 ppm limit
 * 7: Enabled if corresponding PCS is in sync with 485 ppm limit
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG . DES_PHS_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_PHS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,13,4)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_PHS_CTRL     VTSS_ENCODE_BITMASK(13,4)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_PHS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,13,4)

/** 
 * \brief
 * Deserializer phase control, main cp/md select
 *
 * \details 
 * 00: Directly from DES
 * 01: Through hysteresis stage from DES
 * 10: From core
 * 11: Disabled
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG . DES_CPMD_SEL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_CPMD_SEL(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_CPMD_SEL     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_CPMD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * Des phase control for 180 degrees deadlock block mode of operation
 *
 * \details 
 * 000: Depending on density of input pattern
 * 001: Active until PCS has synchronized
 * 010: Depending on density of input pattern until PCS has synchronized
 * 011: Never
 * 100: Always
 * 111: Debug feature: Add cp/md of DES and cp/md from core
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG . DES_MBTR_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_MBTR_CTRL(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_MBTR_CTRL     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_MBTR_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Bandwidth selection. Selects dividing factor for non-hysteresis CP/MD
 * outputs.
 *
 * \details 
 * 0: No division
 * 1: Divide by 2
 * 2: Divide by 4
 * 3: Divide by 8
 * 4: Divide by 16
 * 5: Divide by 32
 * 6: Divide by 64
 * 7: Divide by 128
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG . DES_BW_ANA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_ANA(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_ANA     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * Bandwidth selection. Selects dividing factor for hysteresis CP/MD
 * outputs.
 *
 * \details 
 * 0: Divide by 2
 * 1: Divide by 4
 * 2: Divide by 8
 * 3: Divide by 16
 * 4: Divide by 32
 * 5: Divide by 64
 * 6: Divide by 128
 * 7: Divide by 256
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG . DES_BW_HYST
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_HYST(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_HYST     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_HYST(x)  VTSS_EXTRACT_BITFIELD(x,1,3)


/** 
 * \brief SERDES1G Input Buffer Cfg
 *
 * \details
 * Configuration register for SERDES1G input buffer
 *
 * Register: \a HSIO:SERDES1G_ANA_CFG:SERDES1G_IB_CFG
 */
#define VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x10)

/** 
 * \brief
 * Switches signal detect circuit into low frequency mode, must be used in
 * fx100 mode
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_FX100_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_FX100_ENA  VTSS_BIT(27)

/** 
 * \brief
 * Detect thresholds. Preliminary values:
 *
 * \details 
 * 00: 159-189mVppd
 * 01: 138-164mVppd
 * 10: 109-124mVppd
 * 11: 74-89mVppd
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_DET_LEV
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_DET_LEV(x)  VTSS_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_DET_LEV     VTSS_ENCODE_BITMASK(19,3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_DET_LEV(x)  VTSS_EXTRACT_BITFIELD(x,19,3)

/** 
 * \brief
 * Input buffer hysteresis levels. Preliminary values:
 *
 * \details 
 * 0: 59-79mV
 * 1: 81-124mV
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_HYST_LEV
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_HYST_LEV  VTSS_BIT(14)

/** 
 * \brief
 * Enable common mode voltage termination
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_ENA_CMV_TERM
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_CMV_TERM  VTSS_BIT(13)

/** 
 * \brief
 * Enable dc-coupling of input signal
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_ENA_DC_COUPLING
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DC_COUPLING  VTSS_BIT(12)

/** 
 * \brief
 * Enable detect level circuit
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_ENA_DETLEV
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DETLEV  VTSS_BIT(11)

/** 
 * \brief
 * Enable hysteresis for input signal
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_ENA_HYST
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_HYST  VTSS_BIT(10)

/** 
 * \brief
 * Enable offset compensation of input stage
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_ENA_OFFSET_COMP
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_OFFSET_COMP  VTSS_BIT(9)

/** 
 * \brief
 * Selects weighting between AC and DC input path. Preliminary values:
 *
 * \details 
 * 0: Reserved
 * 1: Reserved
 * 2: 0dB
 * 3: 1.5dB
 * 4: 3dB
 * 5: 6dB
 * 6: 9dB
 * 12.5dB
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_EQ_GAIN
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_EQ_GAIN(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_EQ_GAIN     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_EQ_GAIN(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Corner frequencies of AC path. Preliminary values:
 *
 * \details 
 * 0: 1.3GHz
 * 1: 1.5GHz
 * 2: 1.6GHz
 * 3: 1.8GHz
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_SEL_CORNER_FREQ
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_SEL_CORNER_FREQ(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_SEL_CORNER_FREQ     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_SEL_CORNER_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Resistor control. Value must be taken from RCOMP_STATUS.RCOMP. (default:
 * -3)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_RESISTOR_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_RESISTOR_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_RESISTOR_CTRL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_RESISTOR_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SERDES1G Output Buffer Cfg
 *
 * \details
 * Configuration register for SERDES1G output buffer
 *
 * Register: \a HSIO:SERDES1G_ANA_CFG:SERDES1G_OB_CFG
 */
#define VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x11)

/** 
 * \brief
 * Slope / slew rate control. Preliminary values:
 *
 * \details 
 * 0: 45ps
 * 1: 85ps
 * 2: 105ps
 * 3: 115ps
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG . OB_SLP
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_SLP(x)  VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_SLP     VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_SLP(x)  VTSS_EXTRACT_BITFIELD(x,17,2)

/** 
 * \brief
 * Amplitude control. Preliminary values ranging from 0.4Vppd to 1.1Vppd in
 * steps of 50mVppd. 0: 0.4Vppd, 15: 1.1Vppd
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG . OB_AMP_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_AMP_CTRL(x)  VTSS_ENCODE_BITFIELD(x,13,4)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_AMP_CTRL     VTSS_ENCODE_BITMASK(13,4)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_AMP_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,13,4)

/** 
 * \brief
 * Common mode voltage control. Preliminary values:
 *
 * \details 
 * 0: Reserved
 * 1: 440mV
 * 2: 480mV
 * 3: 460mV
 * 4: 530mV
 * 5: 500mV
 * 6: 570mV
 * 7: 550mV
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG . OB_VCM_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_VCM_CTRL(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_VCM_CTRL     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_VCM_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Resistor control. Value must be taken from RCOMP_STATUS.RCOMP. (default:
 * +1)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG . OB_RESISTOR_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_RESISTOR_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_RESISTOR_CTRL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_RESISTOR_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SERDES1G Serializer Cfg
 *
 * \details
 * Configuration register for SERDES1G serializer
 *
 * Register: \a HSIO:SERDES1G_ANA_CFG:SERDES1G_SER_CFG
 */
#define VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x12)

/** 
 * \brief
 * Invert output D0b for idle-mode of OB
 *
 * \details 
 * 0: Non-inverting
 * 1. Inverting
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_IDLE
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_IDLE  VTSS_BIT(9)

/** 
 * \brief
 * Invert and delays (one clk cycle) output D1 for de-emphasis of OB
 *
 * \details 
 * 0: Non-inverting and non-delaying
 * 1: Inverting and delaying
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_DEEMPH
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_DEEMPH  VTSS_BIT(8)

/** 
 * \brief
 * Enable hysteresis for phase alignment
 *
 * \details 
 * 0: Disable hysteresis
 * 1: Enable hysteresis
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_ENHYS
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ENHYS  VTSS_BIT(3)

/** 
 * \brief
 * Use wider window for phase alignment
 *
 * \details 
 * 0: Use small window for low jitter (100 to 200ps)
 * 1: Use wide window for higher jitter (150 to 300 ps)
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_BIG_WIN
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_BIG_WIN  VTSS_BIT(2)

/** 
 * \brief
 * Enable window for phase alignment
 *
 * \details 
 * 0: Disable window
 * 1: Enable window
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_EN_WIN
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_EN_WIN  VTSS_BIT(1)

/** 
 * \brief
 * Enable phase alignment
 *
 * \details 
 * 0: Disable phase alignment
 * 1: Enable phase alignment
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_ENALI
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ENALI  VTSS_BIT(0)


/** 
 * \brief SERDES1G Common Cfg
 *
 * \details
 * Configuration register for common SERDES1G functions Note: When enabling
 * the facility loop (ena_floop) also the phase alignment in the serializer
 * has to be enabled and configured adequate.
 *
 * Register: \a HSIO:SERDES1G_ANA_CFG:SERDES1G_COMMON_CFG
 */
#define VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x13)

/** 
 * \brief
 * System reset (low active)
 *
 * \details 
 * 0: Apply reset (not self-clearing)
 * 1: Reset released
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . SYS_RST
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SYS_RST  VTSS_BIT(31)

/** 
 * \brief
 * Enable auto-squelching for sync. ethernet bus B
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . SE_AUTO_SQUELCH_B_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SE_AUTO_SQUELCH_B_ENA  VTSS_BIT(22)

/** 
 * \brief
 * Enable auto-squelching for sync. ethernet bus A
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . SE_AUTO_SQUELCH_A_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SE_AUTO_SQUELCH_A_ENA  VTSS_BIT(21)

/** 
 * \brief
 * Select recovered clock of this lane on sync. ethernet bus B
 *
 * \details 
 * 0: Lane not selected
 * 1: Lane selected
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . RECO_SEL_B
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_RECO_SEL_B  VTSS_BIT(20)

/** 
 * \brief
 * Select recovered clock of this lane on sync. ethernet bus A
 *
 * \details 
 * 0: Lane not selected
 * 1: Lane selected
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . RECO_SEL_A
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_RECO_SEL_A  VTSS_BIT(19)

/** 
 * \brief
 * Enable lane
 *
 * \details 
 * 0: Disable lane
 * 1: Enable line
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . ENA_LANE
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_LANE  VTSS_BIT(18)

/** 
 * \brief
 * Enable equipment loop
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . ENA_ELOOP
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_ELOOP  VTSS_BIT(11)

/** 
 * \brief
 * Enable facility loop
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . ENA_FLOOP
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_FLOOP  VTSS_BIT(10)


/** 
 * \brief SERDES1G Pll Cfg
 *
 * \details
 * Configuration register for SERDES1G RCPLL
 *
 * Register: \a HSIO:SERDES1G_ANA_CFG:SERDES1G_PLL_CFG
 */
#define VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x14)

/** 
 * \brief
 * Control data for FSM
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG . PLL_FSM_CTRL_DATA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_CTRL_DATA(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_CTRL_DATA     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_CTRL_DATA(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Enable FSM
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG . PLL_FSM_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_ENA  VTSS_BIT(7)

/**
 * Register Group: \a HSIO:SERDES1G_ANA_STATUS
 *
 * SERDES1G Analog Status Register
 */


/** 
 * \brief SERDES1G Pll Status
 *
 * \details
 * Status register of SERDES1G RCPLL
 *
 * Register: \a HSIO:SERDES1G_ANA_STATUS:SERDES1G_PLL_STATUS
 */
#define VTSS_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS  VTSS_IOREG(VTSS_TO_HSIO,0x15)

/**
 * Register Group: \a HSIO:SERDES1G_DIG_CFG
 *
 * SERDES1G Digital Configuration Register
 */


/** 
 * \brief SERDES1G DFT Configuration register 0
 *
 * \details
 * Configuration register 0 for SERDES1G DFT functions
 *
 * Register: \a HSIO:SERDES1G_DIG_CFG:SERDES1G_DFT_CFG0
 */
#define VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0  VTSS_IOREG(VTSS_TO_HSIO,0x16)


/** 
 * \brief SERDES1G DFT Configuration register 1
 *
 * \details
 * Configuration register 1 for SERDES1G DFT functions (TX direction)
 *
 * Register: \a HSIO:SERDES1G_DIG_CFG:SERDES1G_DFT_CFG1
 */
#define VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1  VTSS_IOREG(VTSS_TO_HSIO,0x17)


/** 
 * \brief SERDES1G DFT Configuration register 2
 *
 * \details
 * Configuration register 2 for SERDES1G DFT functions (RX direction)
 *
 * Register: \a HSIO:SERDES1G_DIG_CFG:SERDES1G_DFT_CFG2
 */
#define VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2  VTSS_IOREG(VTSS_TO_HSIO,0x18)


/** 
 * \brief SERDES1G Test Pattern Configuration
 *
 * \details
 * Test bits (pattern) for SERDES1G lane. These bits are used when
 * Lane_Test_cfg.Test_mode is set to 2 (fixed pattern)
 *
 * Register: \a HSIO:SERDES1G_DIG_CFG:SERDES1G_TP_CFG
 */
#define VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_TP_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x19)


/** 
 * \brief SERDES1G RCPLL BIST Configuration
 *
 * \details
 * Configuration register for the 1G RC-PLL BIST
 *
 * Register: \a HSIO:SERDES1G_DIG_CFG:SERDES1G_RC_PLL_BIST_CFG
 */
#define VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x1a)


/** 
 * \brief SERDES1G Misc Configuration
 *
 * \details
 * Configuration register for miscellaneous functions
 *
 * Register: \a HSIO:SERDES1G_DIG_CFG:SERDES1G_MISC_CFG
 */
#define VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x1b)

/** 
 * \brief
 * Select recovered clock divider
 *
 * \details 
 * 0: No clock dividing
 * 1: Divide clock by 5
 * 2: Divide clock by 4
 * 3: Reserved
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . SEL_RECO_CLK
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_SEL_RECO_CLK(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_SEL_RECO_CLK     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_SEL_RECO_CLK(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Enable deserializer cp/md handling for 100fx mode
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . DES_100FX_CPMD_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Enable RX-Low-Power feature (Power control by LPI-FSM in connected PCS)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . RX_LPI_MODE_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_RX_LPI_MODE_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Enable TX-Low-Power feature (Power control by LPI-FSM in connected PCS)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . TX_LPI_MODE_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_TX_LPI_MODE_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Enable data inversion received from Deserializer
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . RX_DATA_INV_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_RX_DATA_INV_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Enable data inversion sent to Serializer
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . TX_DATA_INV_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_TX_DATA_INV_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Lane Reset
 *
 * \details 
 * 0: No reset
 * 1: Reset (not self-clearing)
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . LANE_RST
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST  VTSS_BIT(0)

/**
 * Register Group: \a HSIO:SERDES1G_DIG_STATUS
 *
 * SERDES1G Digital Status Register
 */


/** 
 * \brief SERDES1G DFT Status
 *
 * \details
 * Status register of SERDES1G DFT functions
 *
 * Register: \a HSIO:SERDES1G_DIG_STATUS:SERDES1G_DFT_STATUS
 */
#define VTSS_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS  VTSS_IOREG(VTSS_TO_HSIO,0x1c)

/** 
 * \brief
 * BIST sync result
 *
 * \details 
 * 0: Synchronization successful
 * 1: Synchronization on BIST data failed
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS . BIST_NOSYNC
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_BIST_NOSYNC  VTSS_BIT(2)

/**
 * Register Group: \a HSIO:MCB_SERDES1G_CFG
 *
 * MCB SERDES1G Configuration Register
 */


/** 
 * \brief MCB SERDES1G Address Cfg
 *
 * \details
 * Configuration of SERDES1G MCB slaves to be accessed
 *
 * Register: \a HSIO:MCB_SERDES1G_CFG:MCB_SERDES1G_ADDR_CFG
 */
#define VTSS_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x1d)

/** 
 * \brief
 * Initiate a write access to marked SERDES1G slaves
 *
 * \details 
 * 0: No write operation pending
 * 1: Initiate write to slaves (kept 1 until write operation has finished)
 *
 * Field: ::VTSS_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG . SERDES1G_WR_ONE_SHOT
 */
#define  VTSS_F_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_WR_ONE_SHOT  VTSS_BIT(31)

/** 
 * \brief
 * Initiate a read access to marked SERDES1G slaves
 *
 * \details 
 * 0: No read operation pending (read op finished after bit has been set)
 * 1: Initiate a read access (kept 1 until read operation has finished)
 *
 * Field: ::VTSS_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG . SERDES1G_RD_ONE_SHOT
 */
#define  VTSS_F_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_RD_ONE_SHOT  VTSS_BIT(30)

/** 
 * \brief
 * Activation vector for SERDES1G-Slaves, one-hot coded, each bit is
 * related to one macro, e.g. bit 0 enables/disables access to macro No. 0
 *
 * \details 
 * 0: Disable macro access via MCB
 * 1: Enable macro access via MCB
 *
 * Field: ::VTSS_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG . SERDES1G_ADDR
 */
#define  VTSS_F_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,25)
#define  VTSS_M_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_ADDR     VTSS_ENCODE_BITMASK(0,25)
#define  VTSS_X_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,25)

/**
 * Register Group: \a HSIO:SERDES6G_ANA_CFG
 *
 * SERDES6G Analog Configuration Registers
 */


/** 
 * \brief SERDES6G Deserializer Cfg
 *
 * \details
 * Configuration register for SERDES6G deserializer
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_DES_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x1e)

/** 
 * \brief
 * Control of phase regulator logic (bit 3 selects input to integrator
 * block - 0: cp/md from DES, 1: cp/md from core)
 *
 * \details 
 * 0: Disabled
 * 1: Enabled with 99 ppm limit
 * 2: Enabled with 202 ppm limit
 * 3: Enabled with 485 ppm limit
 * 4: Enabled if corresponding PCS is in sync with 50 ppm limit
 * 5: Enabled if corresponding PCS is in sync with 99 ppm limit
 * 6: Enabled if corresponding PCS is in sync with 202 ppm limit
 * 7: Enabled if corresponding PCS is in sync with 485 ppm limit
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG . DES_PHS_CTRL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,13,4)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL     VTSS_ENCODE_BITMASK(13,4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,13,4)

/** 
 * \brief
 * Des phase control for 180 degrees deadlock block mode of operation
 *
 * \details 
 * 000: Depending on density of input pattern
 * 001: Active until PCS has synchronized
 * 010: Depending on density of input pattern until PCS has synchronized
 * 011: Never
 * 100: Always
 * 111: Debug feature: Add cp/md of DES and cp/md from core
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG . DES_MBTR_CTRL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_MBTR_CTRL(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_MBTR_CTRL     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_MBTR_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * DES phase control, main cp/md select
 *
 * \details 
 * 00: Directly from DES
 * 01: Through hysteresis stage from DES
 * 10: From core
 * 11: Disabled
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG . DES_CPMD_SEL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Bandwidth selection. Selects dividing factor for hysteresis CP/MD
 * outputs.
 *
 * \details 
 * 0: Divide by 2
 * 1: Divide by 4
 * 2: Divide by 8
 * 3: Divide by 16
 * 4: Divide by 32
 * 5: Divide by 64
 * 6: Divide by 128
 * 7: Divide by 256
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG . DES_BW_HYST
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_HYST(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_HYST     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_HYST(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * Bandwidth selection. Selects dividing factor for non-hysteresis CP/MD
 * outputs.
 *
 * \details 
 * 0: No division
 * 1: Divide by 2
 * 2: Divide by 4
 * 3: Divide by 8
 * 4: Divide by 16
 * 5: Divide by 32
 * 6: Divide by 64
 * 7: Divide by 128
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG . DES_BW_ANA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,3)


/** 
 * \brief SERDES6G Input Buffer Cfg
 *
 * \details
 * Configuration register 0 for SERDES6G input buffer
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_IB_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x1f)

/** 
 * \brief
 * Recovery time for AGC of ac path
 *
 * \details 
 * 0: high
 * 7: low
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_IC_AC
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_IC_AC(x)  VTSS_ENCODE_BITFIELD(x,25,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_IC_AC     VTSS_ENCODE_BITMASK(25,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_IC_AC(x)  VTSS_EXTRACT_BITFIELD(x,25,3)

/** 
 * \brief
 * Recovery time for AGC of ac and dc path (also level detection)
 *
 * \details 
 * 0: high
 * 7: low
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_IC_COM
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_IC_COM(x)  VTSS_ENCODE_BITFIELD(x,22,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_IC_COM     VTSS_ENCODE_BITMASK(22,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_IC_COM(x)  VTSS_EXTRACT_BITFIELD(x,22,3)

/** 
 * \brief
 * Recovery time for AGC of dc path
 *
 * \details 
 * 0: high
 * 7: low
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_IC_DC
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_IC_DC(x)  VTSS_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_IC_DC     VTSS_ENCODE_BITMASK(19,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_IC_DC(x)  VTSS_EXTRACT_BITFIELD(x,19,3)

/** 
 * \brief
 * Data rate selector (high pass filter)
 *
 * \details 
 * 0: 8G
 * 15: 1G
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_RF
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RF(x)  VTSS_ENCODE_BITFIELD(x,14,4)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RF     VTSS_ENCODE_BITMASK(14,4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RF(x)  VTSS_EXTRACT_BITFIELD(x,14,4)

/** 
 * \brief
 * Loss correction (low pass filter)
 *
 * \details 
 * 0: high frequencies
 * 15: low frequencies
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_RT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RT(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RT     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RT(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/** 
 * \brief
 * Offset level for ac path (MSB is sign)
 *
 * \details 
 * 000: middle
 * 011: max
 * 111: min
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_VBAC
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_VBAC(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_VBAC     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_VBAC(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/** 
 * \brief
 * Level detection thresholds. Preliminary values in steps of approx. 8mV:
 * 0: 60mV, 7: 120mV
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_VBCOM
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_VBCOM(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_VBCOM     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_VBCOM(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * Resistor control. Value must be taken from RCOMP_STATUS.RCOMP.
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_RESISTOR_CTRL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RESISTOR_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RESISTOR_CTRL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RESISTOR_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SERDES6G Input Buffer Cfg1
 *
 * \details
 * Configuration register 1 for SERDES6G input buffer
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_IB_CFG1
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1  VTSS_IOREG(VTSS_TO_HSIO,0x20)

/** 
 * \brief
 * Filter settings for auto adjust (adapt for data rate).
 *
 * \details 
 * 0: high frequencies (8G)
 * 15: low frequencies (1G)
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_C
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_C(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_C     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_C(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Common mode termination
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_CTERM_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_CTERM_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Disables equalization, use for low frequency modes
 *
 * \details 
 * 0: Enable
 * 1: Disable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_DIS_EQ
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_DIS_EQ  VTSS_BIT(4)

/** 
 * \brief
 * Auto offset compensation for ac path
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_ENA_OFFSAC
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_ENA_OFFSAC  VTSS_BIT(3)

/** 
 * \brief
 * Auto offset compensation for dc path
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_ENA_OFFSDC
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_ENA_OFFSDC  VTSS_BIT(2)

/** 
 * \brief
 * Increases timing constant for level detect circuit, must be used in
 * FX100 mode
 *
 * \details 
 * 0: Normal speed
 * 1: Slow speed (oversampling)
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_FX100_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FX100_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Reset for IB internal state machine
 *
 * \details 
 * 0: Normal operation
 * 1: Apply reset (not self-clearing)
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_RST
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_RST  VTSS_BIT(0)


/** 
 * \brief SERDES6G Output Buffer Cfg
 *
 * \details
 * Configuration register 0 for SERDES6G output buffer
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_OB_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x21)

/** 
 * \brief
 * PCIe support
 *
 * \details 
 * 1: idle - force to 0V differential
 * 0: Normal mode
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_IDLE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_IDLE  VTSS_BIT(31)

/** 
 * \brief
 * Output buffer supply voltage
 *
 * \details 
 * 1: Set to nominal 1V
 * 0: Set to higher voltage
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_ENA1V_MODE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE  VTSS_BIT(30)

/** 
 * \brief
 * Polarity of output signal
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_POL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POL  VTSS_BIT(29)

/** 
 * \brief
 * Coefficients for 1st Post Cursor (MSB is sign)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_POST0
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0(x)  VTSS_ENCODE_BITFIELD(x,23,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0     VTSS_ENCODE_BITMASK(23,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0(x)  VTSS_EXTRACT_BITFIELD(x,23,6)

/** 
 * \brief
 * Coefficients for 2nd Post Cursor (MSB is sign)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_POST1
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST1(x)  VTSS_ENCODE_BITFIELD(x,18,5)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST1     VTSS_ENCODE_BITMASK(18,5)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST1(x)  VTSS_EXTRACT_BITFIELD(x,18,5)

/** 
 * \brief
 * Coefficients for Pre Cursor (MSB is sign)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_PREC
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC(x)  VTSS_ENCODE_BITFIELD(x,13,5)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC     VTSS_ENCODE_BITMASK(13,5)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC(x)  VTSS_EXTRACT_BITFIELD(x,13,5)

/** 
 * \brief
 * Half the predriver speed, use for slew rate control
 *
 * \details 
 * 0: Disable - slew rate < 60 ps
 * 1: Enable - slew rate > 60 ps
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_SR_H
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H  VTSS_BIT(8)

/** 
 * \brief
 * Resistor control. Value must be taken from RCOMP_STATUS.RCOMP.
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_RESISTOR_CTRL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_RESISTOR_CTRL(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_RESISTOR_CTRL     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_RESISTOR_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Driver speed, fine adjustment of slew rate 30-60ps (if OB_SR_H = 0),
 * 60-140ps (if OB_SR_H = 1)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_SR
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SERDES6G Output Buffer Cfg1
 *
 * \details
 * Configuration register 1 for SERDES6G output buffer
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_OB_CFG1
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1  VTSS_IOREG(VTSS_TO_HSIO,0x22)

/** 
 * \brief
 * Output skew, used for skew adjustment in SGMII mode
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1 . OB_ENA_CAS
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Level of output amplitude
 *
 * \details 
 * 0: lowest level
 * 63: highest level
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1 . OB_LEV
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G Serializer Cfg
 *
 * \details
 * Configuration register for SERDES6G serializer
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_SER_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x23)

/** 
 * \brief
 * Enable hysteresis for phase alignment
 *
 * \details 
 * 0: Disable hysteresis
 * 1: Enable hysteresis
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_ENHYS
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENHYS  VTSS_BIT(3)

/** 
 * \brief
 * Enable window for phase alignment
 *
 * \details 
 * 0: Disable window
 * 1: Enable window
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_EN_WIN
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_EN_WIN  VTSS_BIT(1)

/** 
 * \brief
 * Enable phase alignment
 *
 * \details 
 * 0: Disable phase alignment
 * 1: Enable phase alignment
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_ENALI
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI  VTSS_BIT(0)


/** 
 * \brief SERDES6G Common Cfg
 *
 * \details
 * Configuration register for common SERDES6G functions Note: When enabling
 * the facility loop (ena_floop) also the phase alignment in the serializer
 * has to be enabled and configured adequate.
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_COMMON_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x24)

/** 
 * \brief
 * System reset (low active)
 *
 * \details 
 * 0: Apply reset (not self-clearing)
 * 1: Reset released
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . SYS_RST
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST  VTSS_BIT(31)

/** 
 * \brief
 * Enable auto-squelching for sync. ethernet bus B
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . SE_AUTO_SQUELCH_B_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SE_AUTO_SQUELCH_B_ENA  VTSS_BIT(22)

/** 
 * \brief
 * Enable auto-squelching for sync. ethernet bus A
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . SE_AUTO_SQUELCH_A_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SE_AUTO_SQUELCH_A_ENA  VTSS_BIT(21)

/** 
 * \brief
 * Select recovered clock of this lane on sync. ethernet bus B
 *
 * \details 
 * 0: Lane not selected
 * 1: Lane selected
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . RECO_SEL_B
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_RECO_SEL_B  VTSS_BIT(20)

/** 
 * \brief
 * Select recovered clock of this lane on sync. ethernet bus A
 *
 * \details 
 * 0: Lane not selected
 * 1: Lane selected
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . RECO_SEL_A
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_RECO_SEL_A  VTSS_BIT(19)

/** 
 * \brief
 * Enable lane
 *
 * \details 
 * 0: Disable lane
 * 1: Enable line
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . ENA_LANE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE  VTSS_BIT(18)

/** 
 * \brief
 * Enable equipment loop
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . ENA_ELOOP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP  VTSS_BIT(11)

/** 
 * \brief
 * Enable facility loop
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . ENA_FLOOP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP  VTSS_BIT(10)

/** 
 * \brief
 * Enable half rate
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . HRATE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE  VTSS_BIT(7)

/** 
 * \brief
 * Enable quarter rate
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . QRATE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE  VTSS_BIT(6)

/** 
 * \brief
 * Interface mode
 *
 * \details 
 * 0: Reserved
 * 1: 10-bit mode
 * 2: Reserved
 * 3: 20-bit mode
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . IF_MODE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief SERDES6G Pll Cfg
 *
 * \details
 * Configuration register for SERDES6G RCPLL
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_PLL_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x25)

/** 
 * \brief
 * Enable div4 mode
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_DIV4
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_DIV4  VTSS_BIT(20)

/** 
 * \brief
 * Enable rotation
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_ENA_ROT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT  VTSS_BIT(18)

/** 
 * \brief
 * Control data for FSM
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_FSM_CTRL_DATA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Enable FSM
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_FSM_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA  VTSS_BIT(7)

/** 
 * \brief
 * Select rotation direction
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_ROT_DIR
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_DIR  VTSS_BIT(2)

/** 
 * \brief
 * Select rotation frequency
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_ROT_FRQ
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_FRQ  VTSS_BIT(1)

/**
 * Register Group: \a HSIO:SERDES6G_ANA_STATUS
 *
 * SERDES6G Analog Status Register
 */


/** 
 * \brief SERDES6G Pll Status
 *
 * \details
 * Status register of SERDES6G RCPLL
 *
 * Register: \a HSIO:SERDES6G_ANA_STATUS:SERDES6G_PLL_STATUS
 */
#define VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS  VTSS_IOREG(VTSS_TO_HSIO,0x26)

/**
 * Register Group: \a HSIO:SERDES6G_DIG_CFG
 *
 * SERDES6G Digital Configuration Registers
 */


/** 
 * \brief SERDES6G Digital Configuration register
 *
 * \details
 * Configuration register for SERDES6G digital functions
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_DIG_CFG
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x27)

/** 
 * \brief
 * Signal detect assertion time
 *
 * \details 
 * 0: 0 us
 * 1: 35 us
 * 2: 70 us
 * 3: 105 us
 * 4: 140 us
 * 5..7: reserved
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG . SIGDET_AST
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_AST(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_AST     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_AST(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * Signal detect de-assertion time
 *
 * \details 
 * 0: 0 us
 * 1: 250 us
 * 2: 350 us
 * 3: 450 us
 * 4: 550 us
 * 5..7: reserved
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG . SIGDET_DST
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_DST(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_DST     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_DST(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief SERDES6G DFT Configuration register 0
 *
 * \details
 * Configuration register 0 for SERDES6G DFT functions
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_DFT_CFG0
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0  VTSS_IOREG(VTSS_TO_HSIO,0x28)


/** 
 * \brief SERDES6G DFT Configuration register 1
 *
 * \details
 * Configuration register 1 for SERDES6G DFT functions (TX direction)
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_DFT_CFG1
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1  VTSS_IOREG(VTSS_TO_HSIO,0x29)


/** 
 * \brief SERDES6G DFT Configuration register 2
 *
 * \details
 * Configuration register 2 for SERDES6G DFT functions (RX direction)
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_DFT_CFG2
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2  VTSS_IOREG(VTSS_TO_HSIO,0x2a)


/** 
 * \brief SERDES6G Test Pattern Configuration
 *
 * \details
 * Test bits (pattern) for SERDES6G lane. These bits are used when
 * Lane_Test_cfg.Test_mode is set to 2 (fixed pattern)
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_TP_CFG0
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG0  VTSS_IOREG(VTSS_TO_HSIO,0x2b)


/** 
 * \brief SERDES6G Test Pattern Configuration
 *
 * \details
 * Test bits (pattern) for SERDES6G lane. These bits are used when
 * Lane_Test_cfg.Test_mode is set to 2 (fixed pattern) and
 * Lane_cfg.hr_mode_ena = '0'. In 20 bit modes bits from static_pattern and
 * static_pattern2 are transmitted alternating.
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_TP_CFG1
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG1  VTSS_IOREG(VTSS_TO_HSIO,0x2c)


/** 
 * \brief SERDES6G RCPLL BIST Configuration
 *
 * \details
 * Configuration register for the 6G RC-PLL BIST
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_RC_PLL_BIST_CFG
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x2d)


/** 
 * \brief SERDES6G Misc Configuration
 *
 * \details
 * Configuration register for miscellaneous functions
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_MISC_CFG
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x2e)

/** 
 * \brief
 * Select recovered clock divider
 *
 * \details 
 * 0: No clock dividing
 * 1: Divide clock by 5
 * 2: Divide clock by 4
 * 3: Reserved
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . SEL_RECO_CLK
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_SEL_RECO_CLK(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_SEL_RECO_CLK     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_SEL_RECO_CLK(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Enable deserializer cp/md handling for 100fx mode
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . DES_100FX_CPMD_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Enable RX-Low-Power feature (Power control by LPI-FSM in connected PCS)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . RX_LPI_MODE_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Enable TX-Low-Power feature (Power control by LPI-FSM in connected PCS)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . TX_LPI_MODE_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Enable data inversion received from Deserializer
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . RX_DATA_INV_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_DATA_INV_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Enable data inversion sent to Serializer
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . TX_DATA_INV_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_DATA_INV_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Lane Reset
 *
 * \details 
 * 0: No reset
 * 1: Reset (not self-clearing)
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . LANE_RST
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST  VTSS_BIT(0)


/** 
 * \brief SERDES6G OB ANEG Configuration
 *
 * \details
 * Configuration register for ANEG Output Buffer overwrite parameter. The
 * values are used during Backplane Ethernet Auto-Negotiation when the
 * output level of transmitter (OB output) have to be reduced.
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_OB_ANEG_CFG
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x2f)

/**
 * Register Group: \a HSIO:SERDES6G_DIG_STATUS
 *
 * SERDES6G Digital Status Register
 */


/** 
 * \brief SERDES6G DFT Status
 *
 * \details
 * Status register of SERDES6G DFT functions
 *
 * Register: \a HSIO:SERDES6G_DIG_STATUS:SERDES6G_DFT_STATUS
 */
#define VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS  VTSS_IOREG(VTSS_TO_HSIO,0x30)

/**
 * Register Group: \a HSIO:MCB_SERDES6G_CFG
 *
 * MCB SERDES6G Configuration Register
 */


/** 
 * \brief MCB SERDES6G Address Cfg
 *
 * \details
 * Configuration of SERDES6G MCB Slaves to be accessed
 *
 * Register: \a HSIO:MCB_SERDES6G_CFG:MCB_SERDES6G_ADDR_CFG
 */
#define VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x31)

/** 
 * \brief
 * Initiate a write access to marked SERDES6G Slaves
 *
 * \details 
 * 0: No write operation pending
 * 1: Initiate write to slaves (kept 1 until write operation has finished)
 *
 * Field: ::VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG . SERDES6G_WR_ONE_SHOT
 */
#define  VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_WR_ONE_SHOT  VTSS_BIT(31)

/** 
 * \brief
 * Initiate a read access to marked SERDES6G Slaves
 *
 * \details 
 * 0: No read operation pending (read op finished after bit has been set)
 * 1: Initiate a read access (kept 1 until read operation has finished)
 *
 * Field: ::VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG . SERDES6G_RD_ONE_SHOT
 */
#define  VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_RD_ONE_SHOT  VTSS_BIT(30)

/** 
 * \brief
 * Activation vector for SERDES6G-Slaves, one-hot coded, each bit is
 * related to one macro, e.g. bit 0 enables/disables access to macro No. 0
 *
 * \details 
 * 0: Disable macro access via MCB
 * 1: Enable macro access via MCB
 *
 * Field: ::VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG . SERDES6G_ADDR
 */
#define  VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_ADDR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_SERVAL_REGS_HSIO_H_ */
