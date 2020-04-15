/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

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

#ifndef _VTSS_FA_REGS_PCS25G_RSFEC_H_
#define _VTSS_FA_REGS_PCS25G_RSFEC_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a PCS25G_RSFEC
 *
 * \see vtss_target_PCS25G_RSFEC_e
 *
 * PCS Control, Configuration and Status Registers; All registers are 16-bit
 * wide only.
 *
 ***********************************************************************/

/**
 * Register Group: \a PCS25G_RSFEC:PCS_REGISTERS
 *
 * All registers are 16-bit wide; Address space is given in 32-bit register steps.
 */


/** 
 * \brief PCS Control.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:CONTROL1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_CONTROL1(target)   VTSS_IOREG(target,0x0)

/** 
 * \brief
 * 0101=25G; 0000=10G. Read value depends on currently active configuration
 * (see PCS_MODE or pins).
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_CONTROL1 . SPEED_SELECTION
 */
#define  VTSS_F_PCS25G_RSFEC_CONTROL1_SPEED_SELECTION(x)  VTSS_ENCODE_BITFIELD(x,2,4)
#define  VTSS_M_PCS25G_RSFEC_CONTROL1_SPEED_SELECTION     VTSS_ENCODE_BITMASK(2,4)
#define  VTSS_X_PCS25G_RSFEC_CONTROL1_SPEED_SELECTION(x)  VTSS_EXTRACT_BITFIELD(x,2,4)

/** 
 * \brief
 * Always 1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_CONTROL1 . SPEED_ALWAYS1
 */
#define  VTSS_F_PCS25G_RSFEC_CONTROL1_SPEED_ALWAYS1(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCS25G_RSFEC_CONTROL1_SPEED_ALWAYS1  VTSS_BIT(6)
#define  VTSS_X_PCS25G_RSFEC_CONTROL1_SPEED_ALWAYS1(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * 0=normal operation (Always 0).
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_CONTROL1 . LOW_POWER
 */
#define  VTSS_F_PCS25G_RSFEC_CONTROL1_LOW_POWER(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PCS25G_RSFEC_CONTROL1_LOW_POWER  VTSS_BIT(11)
#define  VTSS_X_PCS25G_RSFEC_CONTROL1_LOW_POWER(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Always 1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_CONTROL1 . SPEED_SELECT_ALWAYS1
 */
#define  VTSS_F_PCS25G_RSFEC_CONTROL1_SPEED_SELECT_ALWAYS1(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCS25G_RSFEC_CONTROL1_SPEED_SELECT_ALWAYS1  VTSS_BIT(13)
#define  VTSS_X_PCS25G_RSFEC_CONTROL1_SPEED_SELECT_ALWAYS1(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * 1=Enable loopback, 0=disable loopback.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_CONTROL1 . LOOPBACK
 */
#define  VTSS_F_PCS25G_RSFEC_CONTROL1_LOOPBACK(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCS25G_RSFEC_CONTROL1_LOOPBACK  VTSS_BIT(14)
#define  VTSS_X_PCS25G_RSFEC_CONTROL1_LOOPBACK(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * 1=PCS reset, 0=normal; Self clearing.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_CONTROL1 . RESET
 */
#define  VTSS_F_PCS25G_RSFEC_CONTROL1_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCS25G_RSFEC_CONTROL1_RESET   VTSS_BIT(15)
#define  VTSS_X_PCS25G_RSFEC_CONTROL1_RESET(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/** 
 * \brief PCS Status.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:STATUS1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_STATUS1(target)    VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Set to 1 to indicate that the PCS implements a low power mode.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS1 . LOW_POWER_ABILITY
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS1_LOW_POWER_ABILITY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS1_LOW_POWER_ABILITY  VTSS_BIT(1)
#define  VTSS_X_PCS25G_RSFEC_STATUS1_LOW_POWER_ABILITY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When 1, indicates PCS receive link up; When 0, indicates PCS receive
 * link is or was down (latching low).
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS1 . PCS_RECEIVE_LINK
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS1_PCS_RECEIVE_LINK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS1_PCS_RECEIVE_LINK  VTSS_BIT(2)
#define  VTSS_X_PCS25G_RSFEC_STATUS1_PCS_RECEIVE_LINK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * When 1, indicates a fault condition detected; When 0, indicates that no
 * fault condition is detected.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS1 . FAULT
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS1_FAULT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS1_FAULT    VTSS_BIT(7)
#define  VTSS_X_PCS25G_RSFEC_STATUS1_FAULT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * 1: receive is currently in LPI state; 0: normal operation.

 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS1 . RX_LPI_ACTIVE
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS1_RX_LPI_ACTIVE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS1_RX_LPI_ACTIVE  VTSS_BIT(8)
#define  VTSS_X_PCS25G_RSFEC_STATUS1_RX_LPI_ACTIVE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * 1: transmit is currently in LPI state; 0: normal operation.

 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS1 . TX_LPI_ACTIVE
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS1_TX_LPI_ACTIVE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS1_TX_LPI_ACTIVE  VTSS_BIT(9)
#define  VTSS_X_PCS25G_RSFEC_STATUS1_TX_LPI_ACTIVE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * 1: receive is or was in LPI state; 0: normal operation; Latching high.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS1 . RX_LPI
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS1_RX_LPI(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS1_RX_LPI   VTSS_BIT(10)
#define  VTSS_X_PCS25G_RSFEC_STATUS1_RX_LPI(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * 1: transmit is or was in LPI state; 0: normal operation; Latching high.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS1 . TX_LPI
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS1_TX_LPI(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS1_TX_LPI   VTSS_BIT(11)
#define  VTSS_X_PCS25G_RSFEC_STATUS1_TX_LPI(x)  VTSS_EXTRACT_BITFIELD(x,11,1)


/** 
 * \brief PHY Identifier constant from package parameter PHY_IDENTIFIER bits 15:4. Bits 3:0 always 0. 
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:DEVICE_ID0
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_DEVICE_ID0(target)  VTSS_IOREG(target,0x2)

/** 
 * \brief
 * Bits 15:0 of Device Identifier defined by parameter PHY_IDENTIFIER in
 * PCS package file.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_DEVICE_ID0 . DEVICE_ID0_IDENTIFIER
 */
#define  VTSS_F_PCS25G_RSFEC_DEVICE_ID0_DEVICE_ID0_IDENTIFIER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_DEVICE_ID0_DEVICE_ID0_IDENTIFIER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_DEVICE_ID0_DEVICE_ID0_IDENTIFIER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PHY Identifier constant from package parameter PHY_IDENTIFIER bits 31:16.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:DEVICE_ID1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_DEVICE_ID1(target)  VTSS_IOREG(target,0x3)

/** 
 * \brief
 * Bits 31:16 of Device Identifier defined by parameter PHY_IDENTIFIER in
 * PCS package file.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_DEVICE_ID1 . DEVICE_ID1_IDENTIFIER
 */
#define  VTSS_F_PCS25G_RSFEC_DEVICE_ID1_DEVICE_ID1_IDENTIFIER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_DEVICE_ID1_DEVICE_ID1_IDENTIFIER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_DEVICE_ID1_DEVICE_ID1_IDENTIFIER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS supported speeds (values as defined by standard only, no proprietary speeds).
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:SPEED_ABILITY
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_SPEED_ABILITY(target)  VTSS_IOREG(target,0x4)

/** 
 * \brief
 * When 1, this PCS is 10Geth capable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_SPEED_ABILITY . C10GETH
 */
#define  VTSS_F_PCS25G_RSFEC_SPEED_ABILITY_C10GETH(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS25G_RSFEC_SPEED_ABILITY_C10GETH  VTSS_BIT(0)
#define  VTSS_X_PCS25G_RSFEC_SPEED_ABILITY_C10GETH(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * When 1, this PCS is 10PASS-TS/2Base-TL capable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_SPEED_ABILITY . C10PASS_TS
 */
#define  VTSS_F_PCS25G_RSFEC_SPEED_ABILITY_C10PASS_TS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCS25G_RSFEC_SPEED_ABILITY_C10PASS_TS  VTSS_BIT(1)
#define  VTSS_X_PCS25G_RSFEC_SPEED_ABILITY_C10PASS_TS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When 1, this PCS is 40G capable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_SPEED_ABILITY . C40G
 */
#define  VTSS_F_PCS25G_RSFEC_SPEED_ABILITY_C40G(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCS25G_RSFEC_SPEED_ABILITY_C40G  VTSS_BIT(2)
#define  VTSS_X_PCS25G_RSFEC_SPEED_ABILITY_C40G(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * When 1, this PCS is 100G capable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_SPEED_ABILITY . C100G
 */
#define  VTSS_F_PCS25G_RSFEC_SPEED_ABILITY_C100G(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCS25G_RSFEC_SPEED_ABILITY_C100G  VTSS_BIT(3)
#define  VTSS_X_PCS25G_RSFEC_SPEED_ABILITY_C100G(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * When 1, this PCS is 25G capable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_SPEED_ABILITY . C25G
 */
#define  VTSS_F_PCS25G_RSFEC_SPEED_ABILITY_C25G(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS25G_RSFEC_SPEED_ABILITY_C25G  VTSS_BIT(4)
#define  VTSS_X_PCS25G_RSFEC_SPEED_ABILITY_C25G(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief Constant indicating PCS presence.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:DEVICES_IN_PKG1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_DEVICES_IN_PKG1(target)  VTSS_IOREG(target,0x5)

/** 
 * \brief
 * WIS present when 1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_DEVICES_IN_PKG1 . WIS_PRES
 */
#define  VTSS_F_PCS25G_RSFEC_DEVICES_IN_PKG1_WIS_PRES(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCS25G_RSFEC_DEVICES_IN_PKG1_WIS_PRES  VTSS_BIT(2)
#define  VTSS_X_PCS25G_RSFEC_DEVICES_IN_PKG1_WIS_PRES(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * TC present when 1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_DEVICES_IN_PKG1 . TC_PRES
 */
#define  VTSS_F_PCS25G_RSFEC_DEVICES_IN_PKG1_TC_PRES(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCS25G_RSFEC_DEVICES_IN_PKG1_TC_PRES  VTSS_BIT(6)
#define  VTSS_X_PCS25G_RSFEC_DEVICES_IN_PKG1_TC_PRES(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * PMD/PMA present when 1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_DEVICES_IN_PKG1 . PMD_PMA
 */
#define  VTSS_F_PCS25G_RSFEC_DEVICES_IN_PKG1_PMD_PMA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCS25G_RSFEC_DEVICES_IN_PKG1_PMD_PMA  VTSS_BIT(1)
#define  VTSS_X_PCS25G_RSFEC_DEVICES_IN_PKG1_PMD_PMA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * PHY XS present when 1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_DEVICES_IN_PKG1 . PHY_XS
 */
#define  VTSS_F_PCS25G_RSFEC_DEVICES_IN_PKG1_PHY_XS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS25G_RSFEC_DEVICES_IN_PKG1_PHY_XS  VTSS_BIT(4)
#define  VTSS_X_PCS25G_RSFEC_DEVICES_IN_PKG1_PHY_XS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * PCS present when 1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_DEVICES_IN_PKG1 . PCS_PRES
 */
#define  VTSS_F_PCS25G_RSFEC_DEVICES_IN_PKG1_PCS_PRES(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCS25G_RSFEC_DEVICES_IN_PKG1_PCS_PRES  VTSS_BIT(3)
#define  VTSS_X_PCS25G_RSFEC_DEVICES_IN_PKG1_PCS_PRES(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * DTE XS present when 1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_DEVICES_IN_PKG1 . DTE_XS
 */
#define  VTSS_F_PCS25G_RSFEC_DEVICES_IN_PKG1_DTE_XS(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCS25G_RSFEC_DEVICES_IN_PKG1_DTE_XS  VTSS_BIT(5)
#define  VTSS_X_PCS25G_RSFEC_DEVICES_IN_PKG1_DTE_XS(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Clause 22 registers present when 1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_DEVICES_IN_PKG1 . DEVICES_IN_PKG1_CLAUSE22
 */
#define  VTSS_F_PCS25G_RSFEC_DEVICES_IN_PKG1_DEVICES_IN_PKG1_CLAUSE22(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS25G_RSFEC_DEVICES_IN_PKG1_DEVICES_IN_PKG1_CLAUSE22  VTSS_BIT(0)
#define  VTSS_X_PCS25G_RSFEC_DEVICES_IN_PKG1_DEVICES_IN_PKG1_CLAUSE22(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Vendor specific presence.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:DEVICES_IN_PKG2
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_DEVICES_IN_PKG2(target)  VTSS_IOREG(target,0x6)

/** 
 * \brief
 * Clause 22 extension present
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_DEVICES_IN_PKG2 . DEVICES_IN_PKG2_CLAUSE22
 */
#define  VTSS_F_PCS25G_RSFEC_DEVICES_IN_PKG2_DEVICES_IN_PKG2_CLAUSE22(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCS25G_RSFEC_DEVICES_IN_PKG2_DEVICES_IN_PKG2_CLAUSE22  VTSS_BIT(13)
#define  VTSS_X_PCS25G_RSFEC_DEVICES_IN_PKG2_DEVICES_IN_PKG2_CLAUSE22(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Vendor specific device 1 present
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_DEVICES_IN_PKG2 . DEVICE1
 */
#define  VTSS_F_PCS25G_RSFEC_DEVICES_IN_PKG2_DEVICE1(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCS25G_RSFEC_DEVICES_IN_PKG2_DEVICE1  VTSS_BIT(14)
#define  VTSS_X_PCS25G_RSFEC_DEVICES_IN_PKG2_DEVICE1(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Vendor specific device 2 present
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_DEVICES_IN_PKG2 . DEVICE2
 */
#define  VTSS_F_PCS25G_RSFEC_DEVICES_IN_PKG2_DEVICE2(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCS25G_RSFEC_DEVICES_IN_PKG2_DEVICE2  VTSS_BIT(15)
#define  VTSS_X_PCS25G_RSFEC_DEVICES_IN_PKG2_DEVICE2(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/** 
 * \brief Operating speed indication/control.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:CONTROL2
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_CONTROL2(target)   VTSS_IOREG(target,0x7)

/** 
 * \brief
 * Not writeable; Reflects PCS mode from PCS_MODE or external pin
 * configurations if possible.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_CONTROL2 . PCS_TYPE
 */
#define  VTSS_F_PCS25G_RSFEC_CONTROL2_PCS_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PCS25G_RSFEC_CONTROL2_PCS_TYPE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PCS25G_RSFEC_CONTROL2_PCS_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Fault status; Device capabilities
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:STATUS2
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_STATUS2(target)    VTSS_IOREG(target,0x8)

/** 
 * \brief
 * When 1, this PCS is 10GBase-R capable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS2 . C10GBASE_R
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS2_C10GBASE_R(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS2_C10GBASE_R  VTSS_BIT(0)
#define  VTSS_X_PCS25G_RSFEC_STATUS2_C10GBASE_R(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * When 1, this PCS is 10GBase-X capable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS2 . C10GBASE_X
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS2_C10GBASE_X(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS2_C10GBASE_X  VTSS_BIT(1)
#define  VTSS_X_PCS25G_RSFEC_STATUS2_C10GBASE_X(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When 1, this PCS is 10GBase-W capable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS2 . C10GBASE_W
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS2_C10GBASE_W(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS2_C10GBASE_W  VTSS_BIT(2)
#define  VTSS_X_PCS25G_RSFEC_STATUS2_C10GBASE_W(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * When 1, this PCS is 10GBase-T capable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS2 . C10GBASE_T
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS2_C10GBASE_T(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS2_C10GBASE_T  VTSS_BIT(3)
#define  VTSS_X_PCS25G_RSFEC_STATUS2_C10GBASE_T(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * When 1, this PCS is 40GBase-R capable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS2 . C40GBASE_R
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS2_C40GBASE_R(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS2_C40GBASE_R  VTSS_BIT(4)
#define  VTSS_X_PCS25G_RSFEC_STATUS2_C40GBASE_R(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * When 1, this PCS is 100GBase-R capable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS2 . C100GBASE_R
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS2_C100GBASE_R(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS2_C100GBASE_R  VTSS_BIT(5)
#define  VTSS_X_PCS25G_RSFEC_STATUS2_C100GBASE_R(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * When 1, this PCS is 25GBase-R capable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS2 . C25GBASE_R
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS2_C25GBASE_R(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS2_C25GBASE_R  VTSS_BIT(7)
#define  VTSS_X_PCS25G_RSFEC_STATUS2_C25GBASE_R(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Receive fault. 1=Fault condition on receive path. Latched high
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS2 . RECEIVE_FAULT
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS2_RECEIVE_FAULT(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS2_RECEIVE_FAULT  VTSS_BIT(10)
#define  VTSS_X_PCS25G_RSFEC_STATUS2_RECEIVE_FAULT(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Transmit fault. 1=Fault condition on transmit path. Latched high
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS2 . TRANSMIT_FAULT
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS2_TRANSMIT_FAULT(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PCS25G_RSFEC_STATUS2_TRANSMIT_FAULT  VTSS_BIT(11)
#define  VTSS_X_PCS25G_RSFEC_STATUS2_TRANSMIT_FAULT(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Device present. When bits are 10 = device responding at this address.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_STATUS2 . DEVICE_PRESENT
 */
#define  VTSS_F_PCS25G_RSFEC_STATUS2_DEVICE_PRESENT(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_PCS25G_RSFEC_STATUS2_DEVICE_PRESENT     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_PCS25G_RSFEC_STATUS2_DEVICE_PRESENT(x)  VTSS_EXTRACT_BITFIELD(x,14,2)


/** 
 * \brief Constant from package parameter PACK_IDENTIFIER bits 15:0.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:PKG_ID0
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_PKG_ID0(target)    VTSS_IOREG(target,0xe)

/** 
 * \brief
 * Constant from package parameter PACK_IDENTIFIER bits 15:0.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_PKG_ID0 . PKG_ID0_IDENTIFIER
 */
#define  VTSS_F_PCS25G_RSFEC_PKG_ID0_PKG_ID0_IDENTIFIER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_PKG_ID0_PKG_ID0_IDENTIFIER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_PKG_ID0_PKG_ID0_IDENTIFIER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Constant from package parameter PACK_IDENTIFIER bits 31:16.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:PKG_ID1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_PKG_ID1(target)    VTSS_IOREG(target,0xf)

/** 
 * \brief
 * Constant from package parameter PACK_IDENTIFIER bits 31:16.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_PKG_ID1 . PKG_ID1_IDENTIFIER
 */
#define  VTSS_F_PCS25G_RSFEC_PKG_ID1_PKG_ID1_IDENTIFIER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_PKG_ID1_PKG_ID1_IDENTIFIER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_PKG_ID1_PKG_ID1_IDENTIFIER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief EEE Control and Capabilities (exists only if EEE is available).
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:EEE_CTRL_CAPABILITY
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_EEE_CTRL_CAPABILITY(target)  VTSS_IOREG(target,0x14)

/** 
 * \brief
 * Mode for selecting select 40G EEE mode; 1 = Fast wake mode; 0 = Deep
 * sleep for LPI function.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_EEE_CTRL_CAPABILITY . LPI_FW
 */
#define  VTSS_F_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_LPI_FW(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_LPI_FW  VTSS_BIT(0)
#define  VTSS_X_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_LPI_FW(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * When 1, EEE is supported for 10GBASE-KR.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_EEE_CTRL_CAPABILITY . EEE_10GBASE_KR
 */
#define  VTSS_F_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_10GBASE_KR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_10GBASE_KR  VTSS_BIT(6)
#define  VTSS_X_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_10GBASE_KR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * When 1, EEE fast wake is supported for 40GBASE-R.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_EEE_CTRL_CAPABILITY . EEE_40GBASE_RAWAKE
 */
#define  VTSS_F_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_40GBASE_RAWAKE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_40GBASE_RAWAKE  VTSS_BIT(8)
#define  VTSS_X_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_40GBASE_RAWAKE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * When 1, EEE deep sleep is supported for 40GBASE-R.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_EEE_CTRL_CAPABILITY . EEE_40GBASE_RSLEEP
 */
#define  VTSS_F_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_40GBASE_RSLEEP(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_40GBASE_RSLEEP  VTSS_BIT(9)
#define  VTSS_X_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_40GBASE_RSLEEP(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * When 1, EEE fast wake is supported for 25GBASE-R.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_EEE_CTRL_CAPABILITY . EEE_25GBASE_RAWAKE
 */
#define  VTSS_F_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_25GBASE_RAWAKE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_25GBASE_RAWAKE  VTSS_BIT(10)
#define  VTSS_X_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_25GBASE_RAWAKE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * When 1, EEE deep sleep is supported for 25GBASE-R.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_EEE_CTRL_CAPABILITY . EEE_25GBASE_RSLEEP
 */
#define  VTSS_F_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_25GBASE_RSLEEP(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_25GBASE_RSLEEP  VTSS_BIT(11)
#define  VTSS_X_PCS25G_RSFEC_EEE_CTRL_CAPABILITY_EEE_25GBASE_RSLEEP(x)  VTSS_EXTRACT_BITFIELD(x,11,1)


/** 
 * \brief EEE Wake error counter (exists only if EEE is available); Clears on read.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:WAKE_ERR_COUNTER
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_WAKE_ERR_COUNTER(target)  VTSS_IOREG(target,0x16)

/** 
 * \brief
 * Increments each time the LPI enters the RX_WTF state indicating a wake
 * time fault; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_WAKE_ERR_COUNTER . WAKE_ERR_COUNTER_COUNTER
 */
#define  VTSS_F_PCS25G_RSFEC_WAKE_ERR_COUNTER_WAKE_ERR_COUNTER_COUNTER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_WAKE_ERR_COUNTER_WAKE_ERR_COUNTER_COUNTER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_WAKE_ERR_COUNTER_WAKE_ERR_COUNTER_COUNTER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Link Status Information.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:BASER_STATUS1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_BASER_STATUS1(target)  VTSS_IOREG(target,0x20)

/** 
 * \brief
 * 1=PCS locked to received blocks.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BASER_STATUS1 . BASER_STATUS1_BLOCK_LOCK
 */
#define  VTSS_F_PCS25G_RSFEC_BASER_STATUS1_BASER_STATUS1_BLOCK_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS25G_RSFEC_BASER_STATUS1_BASER_STATUS1_BLOCK_LOCK  VTSS_BIT(0)
#define  VTSS_X_PCS25G_RSFEC_BASER_STATUS1_BASER_STATUS1_BLOCK_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * 1=PCS reporting a high BER.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BASER_STATUS1 . BASER_STATUS1_HIGH_BER
 */
#define  VTSS_F_PCS25G_RSFEC_BASER_STATUS1_BASER_STATUS1_HIGH_BER(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCS25G_RSFEC_BASER_STATUS1_BASER_STATUS1_HIGH_BER  VTSS_BIT(1)
#define  VTSS_X_PCS25G_RSFEC_BASER_STATUS1_BASER_STATUS1_HIGH_BER(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Receive link status. 1=Link up; 0=link down.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BASER_STATUS1 . RECEIVE_LINK
 */
#define  VTSS_F_PCS25G_RSFEC_BASER_STATUS1_RECEIVE_LINK(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCS25G_RSFEC_BASER_STATUS1_RECEIVE_LINK  VTSS_BIT(12)
#define  VTSS_X_PCS25G_RSFEC_BASER_STATUS1_RECEIVE_LINK(x)  VTSS_EXTRACT_BITFIELD(x,12,1)


/** 
 * \brief Link Status latches and error counters.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:BASER_STATUS2
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_BASER_STATUS2(target)  VTSS_IOREG(target,0x21)

/** 
 * \brief
 * Errored blocks counter; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BASER_STATUS2 . ERRORED_CNT
 */
#define  VTSS_F_PCS25G_RSFEC_BASER_STATUS2_ERRORED_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCS25G_RSFEC_BASER_STATUS2_ERRORED_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCS25G_RSFEC_BASER_STATUS2_ERRORED_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * BER counter; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BASER_STATUS2 . BASER_STATUS2_BER_COUNTER
 */
#define  VTSS_F_PCS25G_RSFEC_BASER_STATUS2_BASER_STATUS2_BER_COUNTER(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_PCS25G_RSFEC_BASER_STATUS2_BASER_STATUS2_BER_COUNTER     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_PCS25G_RSFEC_BASER_STATUS2_BASER_STATUS2_BER_COUNTER(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * BER flag; Latched high.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BASER_STATUS2 . BASER_STATUS2_HIGH_BER
 */
#define  VTSS_F_PCS25G_RSFEC_BASER_STATUS2_BASER_STATUS2_HIGH_BER(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCS25G_RSFEC_BASER_STATUS2_BASER_STATUS2_HIGH_BER  VTSS_BIT(14)
#define  VTSS_X_PCS25G_RSFEC_BASER_STATUS2_BASER_STATUS2_HIGH_BER(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Block Lock; Latched low.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BASER_STATUS2 . BASER_STATUS2_BLOCK_LOCK
 */
#define  VTSS_F_PCS25G_RSFEC_BASER_STATUS2_BASER_STATUS2_BLOCK_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCS25G_RSFEC_BASER_STATUS2_BASER_STATUS2_BLOCK_LOCK  VTSS_BIT(15)
#define  VTSS_X_PCS25G_RSFEC_BASER_STATUS2_BASER_STATUS2_BLOCK_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/** 
 * \brief 10G Base-R Test Pattern Seed A bits 15:0.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:SEED_A0
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_SEED_A0(target)    VTSS_IOREG(target,0x22)

/** 
 * \brief
 * 10GBase-R Test Pattern Seed A: Bits 15:0.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_SEED_A0 . SEED_A0_SEED
 */
#define  VTSS_F_PCS25G_RSFEC_SEED_A0_SEED_A0_SEED(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_SEED_A0_SEED_A0_SEED     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_SEED_A0_SEED_A0_SEED(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief 10G Base-R Test Pattern Seed A bits 31:16.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:SEED_A1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_SEED_A1(target)    VTSS_IOREG(target,0x23)

/** 
 * \brief
 * 10GBase-R Test Pattern Seed A: Bits 31:16.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_SEED_A1 . SEED_A1_SEED
 */
#define  VTSS_F_PCS25G_RSFEC_SEED_A1_SEED_A1_SEED(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_SEED_A1_SEED_A1_SEED     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_SEED_A1_SEED_A1_SEED(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief 10G Base-R Test Pattern Seed A bits 47:32.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:SEED_A2
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_SEED_A2(target)    VTSS_IOREG(target,0x24)

/** 
 * \brief
 * 10GBase-R Test Pattern Seed A: Bits 47:32.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_SEED_A2 . SEED_A2_SEED
 */
#define  VTSS_F_PCS25G_RSFEC_SEED_A2_SEED_A2_SEED(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_SEED_A2_SEED_A2_SEED     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_SEED_A2_SEED_A2_SEED(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief 10G Base-R Test Pattern Seed A bits 57:48.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:SEED_A3
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_SEED_A3(target)    VTSS_IOREG(target,0x25)

/** 
 * \brief
 * 10GBase-R Test Pattern Seed A: Bits 57:48.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_SEED_A3 . SEED_A3_SEED
 */
#define  VTSS_F_PCS25G_RSFEC_SEED_A3_SEED_A3_SEED(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_PCS25G_RSFEC_SEED_A3_SEED_A3_SEED     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_PCS25G_RSFEC_SEED_A3_SEED_A3_SEED(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief 10G Base-R Test Pattern Seed B bits 15:0.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:SEED_B0
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_SEED_B0(target)    VTSS_IOREG(target,0x26)

/** 
 * \brief
 * 10GBase-R Test Pattern Seed B: Bits 15:0.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_SEED_B0 . SEED_B0_SEED
 */
#define  VTSS_F_PCS25G_RSFEC_SEED_B0_SEED_B0_SEED(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_SEED_B0_SEED_B0_SEED     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_SEED_B0_SEED_B0_SEED(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief 10G Base-R Test Pattern Seed B bits 31:16.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:SEED_B1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_SEED_B1(target)    VTSS_IOREG(target,0x27)

/** 
 * \brief
 * 10GBase-R Test Pattern Seed B: Bits 31:16.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_SEED_B1 . SEED_B1_SEED
 */
#define  VTSS_F_PCS25G_RSFEC_SEED_B1_SEED_B1_SEED(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_SEED_B1_SEED_B1_SEED     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_SEED_B1_SEED_B1_SEED(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief 10G Base-R Test Pattern Seed B bits 47:32.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:SEED_B2
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_SEED_B2(target)    VTSS_IOREG(target,0x28)

/** 
 * \brief
 * 10GBase-R Test Pattern Seed B: Bits 47:32.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_SEED_B2 . SEED_B2_SEED
 */
#define  VTSS_F_PCS25G_RSFEC_SEED_B2_SEED_B2_SEED(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_SEED_B2_SEED_B2_SEED     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_SEED_B2_SEED_B2_SEED(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief 10G Base-R Test Pattern Seed B bits 57:48.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:SEED_B3
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_SEED_B3(target)    VTSS_IOREG(target,0x29)

/** 
 * \brief
 * 10GBase-R Test Pattern Seed B: Bits 57:48.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_SEED_B3 . SEED_B3_SEED
 */
#define  VTSS_F_PCS25G_RSFEC_SEED_B3_SEED_B3_SEED(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_PCS25G_RSFEC_SEED_B3_SEED_B3_SEED     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_PCS25G_RSFEC_SEED_B3_SEED_B3_SEED(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Test Pattern Generator and Checker controls.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:BASER_TEST_CONTROL
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_BASER_TEST_CONTROL(target)  VTSS_IOREG(target,0x2a)

/** 
 * \brief
 * Data Pattern Select: 1=all Zero, 0=2x Local Fault; 10G only.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BASER_TEST_CONTROL . DATA_PATTERN_SEL
 */
#define  VTSS_F_PCS25G_RSFEC_BASER_TEST_CONTROL_DATA_PATTERN_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS25G_RSFEC_BASER_TEST_CONTROL_DATA_PATTERN_SEL  VTSS_BIT(0)
#define  VTSS_X_PCS25G_RSFEC_BASER_TEST_CONTROL_DATA_PATTERN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Select Square Wave (1) or Pseudo Random (0) test pattern; 10G only.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BASER_TEST_CONTROL . SELECT_SQUARE
 */
#define  VTSS_F_PCS25G_RSFEC_BASER_TEST_CONTROL_SELECT_SQUARE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCS25G_RSFEC_BASER_TEST_CONTROL_SELECT_SQUARE  VTSS_BIT(1)
#define  VTSS_X_PCS25G_RSFEC_BASER_TEST_CONTROL_SELECT_SQUARE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Receive test-pattern enable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BASER_TEST_CONTROL . RX_TESTPATTERN
 */
#define  VTSS_F_PCS25G_RSFEC_BASER_TEST_CONTROL_RX_TESTPATTERN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCS25G_RSFEC_BASER_TEST_CONTROL_RX_TESTPATTERN  VTSS_BIT(2)
#define  VTSS_X_PCS25G_RSFEC_BASER_TEST_CONTROL_RX_TESTPATTERN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Transmit test-pattern enable.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BASER_TEST_CONTROL . TX_TESTPATTERN
 */
#define  VTSS_F_PCS25G_RSFEC_BASER_TEST_CONTROL_TX_TESTPATTERN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCS25G_RSFEC_BASER_TEST_CONTROL_TX_TESTPATTERN  VTSS_BIT(3)
#define  VTSS_X_PCS25G_RSFEC_BASER_TEST_CONTROL_TX_TESTPATTERN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Select Random Idle test pattern (40G); Overrides bits 1:0 when set.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BASER_TEST_CONTROL . SELECT_RANDOM
 */
#define  VTSS_F_PCS25G_RSFEC_BASER_TEST_CONTROL_SELECT_RANDOM(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCS25G_RSFEC_BASER_TEST_CONTROL_SELECT_RANDOM  VTSS_BIT(7)
#define  VTSS_X_PCS25G_RSFEC_BASER_TEST_CONTROL_SELECT_RANDOM(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief Test Pattern Error Counter; Clears on read; None roll-over.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:BASER_TEST_ERR_CNT
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_BASER_TEST_ERR_CNT(target)  VTSS_IOREG(target,0x2b)

/** 
 * \brief
 * Test pattern error counter; Clears on read; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BASER_TEST_ERR_CNT . BASER_TEST_ERR_CNT_COUNTER
 */
#define  VTSS_F_PCS25G_RSFEC_BASER_TEST_ERR_CNT_BASER_TEST_ERR_CNT_COUNTER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_BASER_TEST_ERR_CNT_BASER_TEST_ERR_CNT_COUNTER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_BASER_TEST_ERR_CNT_BASER_TEST_ERR_CNT_COUNTER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief BER High Order Counter of BER bits 21:6; None roll-over.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:BER_HIGH_ORDER_CNT
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_BER_HIGH_ORDER_CNT(target)  VTSS_IOREG(target,0x2c)

/** 
 * \brief
 * Bits 21:6 of BER counter; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BER_HIGH_ORDER_CNT . BER_HIGH_ORDER_CNT_BER_COUNTER
 */
#define  VTSS_F_PCS25G_RSFEC_BER_HIGH_ORDER_CNT_BER_HIGH_ORDER_CNT_BER_COUNTER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_BER_HIGH_ORDER_CNT_BER_HIGH_ORDER_CNT_BER_COUNTER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_BER_HIGH_ORDER_CNT_BER_HIGH_ORDER_CNT_BER_COUNTER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Error Blocks High Order Counter bits 21:8; None roll-over.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:ERR_BLK_HIGH_ORDER_CNT
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_ERR_BLK_HIGH_ORDER_CNT(target)  VTSS_IOREG(target,0x2d)

/** 
 * \brief
 * Bits 21:8 of Error Blocks counter; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_ERR_BLK_HIGH_ORDER_CNT . ERRORED_BLOCKS_COUNTER
 */
#define  VTSS_F_PCS25G_RSFEC_ERR_BLK_HIGH_ORDER_CNT_ERRORED_BLOCKS_COUNTER(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_PCS25G_RSFEC_ERR_BLK_HIGH_ORDER_CNT_ERRORED_BLOCKS_COUNTER     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_PCS25G_RSFEC_ERR_BLK_HIGH_ORDER_CNT_ERRORED_BLOCKS_COUNTER(x)  VTSS_EXTRACT_BITFIELD(x,0,14)

/** 
 * \brief
 * High order counter present; Always 1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_ERR_BLK_HIGH_ORDER_CNT . HIGH_ORDER_PRESENT
 */
#define  VTSS_F_PCS25G_RSFEC_ERR_BLK_HIGH_ORDER_CNT_HIGH_ORDER_PRESENT(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCS25G_RSFEC_ERR_BLK_HIGH_ORDER_CNT_HIGH_ORDER_PRESENT  VTSS_BIT(15)
#define  VTSS_X_PCS25G_RSFEC_ERR_BLK_HIGH_ORDER_CNT_HIGH_ORDER_PRESENT(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/** 
 * \brief Lane Alignment Status Bits and Block Lock.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:MULTILANE_ALIGN_STAT1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_MULTILANE_ALIGN_STAT1(target)  VTSS_IOREG(target,0x32)

/** 
 * \brief
 * Lane alignment status; 1=All Receive lanes locked and aligned.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_MULTILANE_ALIGN_STAT1 . LANE_ALIGN_STATUS
 */
#define  VTSS_F_PCS25G_RSFEC_MULTILANE_ALIGN_STAT1_LANE_ALIGN_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCS25G_RSFEC_MULTILANE_ALIGN_STAT1_LANE_ALIGN_STATUS  VTSS_BIT(12)
#define  VTSS_X_PCS25G_RSFEC_MULTILANE_ALIGN_STAT1_LANE_ALIGN_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)


/** 
 * \brief Lane Alignment Marker Lock Status bits.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:MULTILANE_ALIGN_STAT3
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3(target)  VTSS_IOREG(target,0x34)

/** 
 * \brief
 * Lane 0 alignment marker lock.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3 . LANE0_MARKER_LOCK
 */
#define  VTSS_F_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3_LANE0_MARKER_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3_LANE0_MARKER_LOCK  VTSS_BIT(0)
#define  VTSS_X_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3_LANE0_MARKER_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Lane 1 alignment marker lock.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3 . LANE1_MARKER_LOCK
 */
#define  VTSS_F_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3_LANE1_MARKER_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3_LANE1_MARKER_LOCK  VTSS_BIT(1)
#define  VTSS_X_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3_LANE1_MARKER_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Lane 2 alignment marker lock.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3 . LANE2_MARKER_LOCK
 */
#define  VTSS_F_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3_LANE2_MARKER_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3_LANE2_MARKER_LOCK  VTSS_BIT(2)
#define  VTSS_X_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3_LANE2_MARKER_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Lane 3 alignment marker lock.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3 . LANE3_MARKER_LOCK
 */
#define  VTSS_F_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3_LANE3_MARKER_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3_LANE3_MARKER_LOCK  VTSS_BIT(3)
#define  VTSS_X_PCS25G_RSFEC_MULTILANE_ALIGN_STAT3_LANE3_MARKER_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief BIP Error Counter Lane 0; Clears on read; None roll-over.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:BIP_ERR_CNT_LANE0
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_BIP_ERR_CNT_LANE0(target)  VTSS_IOREG(target,0xc8)

/** 
 * \brief
 * BIP error counter lane 0; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BIP_ERR_CNT_LANE0 . BIP_ERR_CNT_LANE0_BIP_ERROR_COUNTER
 */
#define  VTSS_F_PCS25G_RSFEC_BIP_ERR_CNT_LANE0_BIP_ERR_CNT_LANE0_BIP_ERROR_COUNTER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_BIP_ERR_CNT_LANE0_BIP_ERR_CNT_LANE0_BIP_ERROR_COUNTER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_BIP_ERR_CNT_LANE0_BIP_ERR_CNT_LANE0_BIP_ERROR_COUNTER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief BIP Error Counter Lane 1; Clears on read; None roll-over.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:BIP_ERR_CNT_LANE1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_BIP_ERR_CNT_LANE1(target)  VTSS_IOREG(target,0xc9)

/** 
 * \brief
 * BIP error counter lane 1; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BIP_ERR_CNT_LANE1 . BIP_ERR_CNT_LANE1_BIP_ERROR_COUNTER
 */
#define  VTSS_F_PCS25G_RSFEC_BIP_ERR_CNT_LANE1_BIP_ERR_CNT_LANE1_BIP_ERROR_COUNTER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_BIP_ERR_CNT_LANE1_BIP_ERR_CNT_LANE1_BIP_ERROR_COUNTER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_BIP_ERR_CNT_LANE1_BIP_ERR_CNT_LANE1_BIP_ERROR_COUNTER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief BIP Error Counter Lane 2; Clears on read; None roll-over.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:BIP_ERR_CNT_LANE2
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_BIP_ERR_CNT_LANE2(target)  VTSS_IOREG(target,0xca)

/** 
 * \brief
 * BIP error counter lane 2; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BIP_ERR_CNT_LANE2 . BIP_ERR_CNT_LANE2_BIP_ERROR_COUNTER
 */
#define  VTSS_F_PCS25G_RSFEC_BIP_ERR_CNT_LANE2_BIP_ERR_CNT_LANE2_BIP_ERROR_COUNTER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_BIP_ERR_CNT_LANE2_BIP_ERR_CNT_LANE2_BIP_ERROR_COUNTER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_BIP_ERR_CNT_LANE2_BIP_ERR_CNT_LANE2_BIP_ERROR_COUNTER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief BIP Error Counter Lane 3; Clears on read; None roll-over.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:BIP_ERR_CNT_LANE3
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_BIP_ERR_CNT_LANE3(target)  VTSS_IOREG(target,0xcb)

/** 
 * \brief
 * BIP error counter lane 3; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_BIP_ERR_CNT_LANE3 . BIP_ERR_CNT_LANE3_BIP_ERROR_COUNTER
 */
#define  VTSS_F_PCS25G_RSFEC_BIP_ERR_CNT_LANE3_BIP_ERR_CNT_LANE3_BIP_ERROR_COUNTER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_BIP_ERR_CNT_LANE3_BIP_ERR_CNT_LANE3_BIP_ERROR_COUNTER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_BIP_ERR_CNT_LANE3_BIP_ERR_CNT_LANE3_BIP_ERROR_COUNTER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Vendor Specific Reg; Scratch Register.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:VENDOR_SCRATCH
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_VENDOR_SCRATCH(target)  VTSS_IOREG(target,0x100)

/** 
 * \brief
 * Scratch Register; Register address to test read and write operation.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_SCRATCH . SCRATCH
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_SCRATCH_SCRATCH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_SCRATCH_SCRATCH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_SCRATCH_SCRATCH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Vendor Specific Reg; Core Revision derived from DEV_VERSION package parameter.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:VENDOR_CORE_REV
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_VENDOR_CORE_REV(target)  VTSS_IOREG(target,0x101)

/** 
 * \brief
 * Core Design version as defined by DEV_VERSION parameter in PCS package
 * file.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_CORE_REV . REVISION
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_CORE_REV_REVISION(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_CORE_REV_REVISION     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_CORE_REV_REVISION(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Vendor Specific Reg; Set the amount of data between markers. (I.e. distance of markers-1).
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:VENDOR_VL_INTVL
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_VENDOR_VL_INTVL(target)  VTSS_IOREG(target,0x102)

/** 
 * \brief
 * A 16-bit value defining the amount of data between markers; (distance of
 * markers-1).
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_VL_INTVL . MARKER_COUNTER
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_VL_INTVL_MARKER_COUNTER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_VL_INTVL_MARKER_COUNTER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_VL_INTVL_MARKER_COUNTER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Vendor Specific Reg; Defines the transmit line decoupling FIFOs almost full threshold.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:VENDOR_TXLANE_THRESH
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_VENDOR_TXLANE_THRESH(target)  VTSS_IOREG(target,0x103)

/** 
 * \brief
 * A 4-bit value to define the transmit line decoupling FIFOs almost full
 * threshold; Valid values are 4..9.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_TXLANE_THRESH . THRESHOLD
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_TXLANE_THRESH_THRESHOLD(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_TXLANE_THRESH_THRESHOLD     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_TXLANE_THRESH_THRESHOLD(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Vendor Specific Reg; Marker pattern for PCS Virtual Lane 0.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:VENDOR_VL0_0
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_VENDOR_VL0_0(target)  VTSS_IOREG(target,0x108)

/** 
 * \brief
 * Lane 0 Marker pattern for m0.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_VL0_0 . VENDOR_VL0_0_M0
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_VL0_0_VENDOR_VL0_0_M0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_VL0_0_VENDOR_VL0_0_M0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_VL0_0_VENDOR_VL0_0_M0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Lane 0 Marker pattern for m1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_VL0_0 . VENDOR_VL0_0_M1
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_VL0_0_VENDOR_VL0_0_M1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_VL0_0_VENDOR_VL0_0_M1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_VL0_0_VENDOR_VL0_0_M1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)


/** 
 * \brief Vendor Specific Reg; Last byte of PCS Virtual Lane 0 marker pattern.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:VENDOR_VL0_1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_VENDOR_VL0_1(target)  VTSS_IOREG(target,0x109)

/** 
 * \brief
 * Lane 0 Marker pattern for m2.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_VL0_1 . VENDOR_VL0_1_M2
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_VL0_1_VENDOR_VL0_1_M2(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_VL0_1_VENDOR_VL0_1_M2     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_VL0_1_VENDOR_VL0_1_M2(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Vendor Specific Reg; Marker pattern for PCS Virtual Lane 1.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:VENDOR_VL1_0
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_VENDOR_VL1_0(target)  VTSS_IOREG(target,0x10a)

/** 
 * \brief
 * Lane 1 Marker pattern for m0.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_VL1_0 . VENDOR_VL1_0_M0
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_VL1_0_VENDOR_VL1_0_M0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_VL1_0_VENDOR_VL1_0_M0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_VL1_0_VENDOR_VL1_0_M0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Lane 1 Marker pattern for m1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_VL1_0 . VENDOR_VL1_0_M1
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_VL1_0_VENDOR_VL1_0_M1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_VL1_0_VENDOR_VL1_0_M1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_VL1_0_VENDOR_VL1_0_M1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)


/** 
 * \brief Vendor Specific Reg; Last byte of PCS Virtual Lane 1 marker pattern.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:VENDOR_VL1_1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_VENDOR_VL1_1(target)  VTSS_IOREG(target,0x10b)

/** 
 * \brief
 * Lane 1 last btye of Marker pattern for m2.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_VL1_1 . VENDOR_VL1_1_M2
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_VL1_1_VENDOR_VL1_1_M2(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_VL1_1_VENDOR_VL1_1_M2     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_VL1_1_VENDOR_VL1_1_M2(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Vendor Specific Reg; Marker pattern for PCS Virtual Lane 2.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:VENDOR_VL2_0
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_VENDOR_VL2_0(target)  VTSS_IOREG(target,0x10c)

/** 
 * \brief
 * Lane 2 Marker pattern for m0.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_VL2_0 . VENDOR_VL2_0_M0
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_VL2_0_VENDOR_VL2_0_M0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_VL2_0_VENDOR_VL2_0_M0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_VL2_0_VENDOR_VL2_0_M0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Lane 2 Marker pattern for m1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_VL2_0 . VENDOR_VL2_0_M1
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_VL2_0_VENDOR_VL2_0_M1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_VL2_0_VENDOR_VL2_0_M1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_VL2_0_VENDOR_VL2_0_M1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)


/** 
 * \brief Vendor Specific Reg; Last byte of PCS Virtual Lane 2 marker pattern.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:VENDOR_VL2_1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_VENDOR_VL2_1(target)  VTSS_IOREG(target,0x10d)

/** 
 * \brief
 * Lane 2 last btye of Marker pattern for m2.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_VL2_1 . VENDOR_VL2_1_M2
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_VL2_1_VENDOR_VL2_1_M2(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_VL2_1_VENDOR_VL2_1_M2     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_VL2_1_VENDOR_VL2_1_M2(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Vendor Specific Reg; Marker pattern for PCS Virtual Lane 3.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:VENDOR_VL3_0
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_VENDOR_VL3_0(target)  VTSS_IOREG(target,0x10e)

/** 
 * \brief
 * Lane 3 Marker pattern for m0.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_VL3_0 . VENDOR_VL3_0_M0
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_VL3_0_VENDOR_VL3_0_M0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_VL3_0_VENDOR_VL3_0_M0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_VL3_0_VENDOR_VL3_0_M0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Lane 3 Marker pattern for m1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_VL3_0 . VENDOR_VL3_0_M1
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_VL3_0_VENDOR_VL3_0_M1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_VL3_0_VENDOR_VL3_0_M1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_VL3_0_VENDOR_VL3_0_M1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)


/** 
 * \brief Vendor Specific Reg; Last byte of PCS Virtual Lane 3 marker pattern.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:VENDOR_VL3_1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_VENDOR_VL3_1(target)  VTSS_IOREG(target,0x10f)

/** 
 * \brief
 * Lane 3 last btye of Marker pattern for m2.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_VL3_1 . VENDOR_VL3_1_M2
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_VL3_1_VENDOR_VL3_1_M2(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_VL3_1_VENDOR_VL3_1_M2     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_VL3_1_VENDOR_VL3_1_M2(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Vendor Specific Reg; Configure PCS supporting Clause 49 or 82 Encoder/Decoder, MLD.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:VENDOR_PCS_MODE
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_VENDOR_PCS_MODE(target)  VTSS_IOREG(target,0x110)

/** 
 * \brief
 * When 0 PCS uses Clause 82 encoder/decoder functions; When 1 PCS uses
 * Clause 49 encoder/decoder functions.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_PCS_MODE . ENA_CLAUSE49
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_PCS_MODE_ENA_CLAUSE49(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_PCS_MODE_ENA_CLAUSE49  VTSS_BIT(0)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_PCS_MODE_ENA_CLAUSE49(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * When 0 PCS 4-lane MLD function is active; When 1 the MLD function is
 * disabled.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_PCS_MODE . DISABLE_MLD
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_PCS_MODE_DISABLE_MLD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_PCS_MODE_DISABLE_MLD  VTSS_BIT(1)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_PCS_MODE_DISABLE_MLD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When 1 PCS implements 25G Hi-Ber (2ms, 97 errors). When 0 PCS implements
 * 10G Hi-Ber (125us, 16 errors);
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_PCS_MODE . HI_BER25
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_PCS_MODE_HI_BER25(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_PCS_MODE_HI_BER25  VTSS_BIT(2)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_PCS_MODE_HI_BER25(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Current status of Clause 49 setting.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_PCS_MODE . ST_ENA_CLAUSE49
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_PCS_MODE_ST_ENA_CLAUSE49(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_PCS_MODE_ST_ENA_CLAUSE49  VTSS_BIT(8)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_PCS_MODE_ST_ENA_CLAUSE49(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Current status of MLD setting.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_VENDOR_PCS_MODE . ST_DISABLE_MLD
 */
#define  VTSS_F_PCS25G_RSFEC_VENDOR_PCS_MODE_ST_DISABLE_MLD(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PCS25G_RSFEC_VENDOR_PCS_MODE_ST_DISABLE_MLD  VTSS_BIT(9)
#define  VTSS_X_PCS25G_RSFEC_VENDOR_PCS_MODE_ST_DISABLE_MLD(x)  VTSS_EXTRACT_BITFIELD(x,9,1)


/** 
 * \brief Vendor Specific Reg; Value shifted for block lock.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:GB_SHIFT
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_GB_SHIFT(target)   VTSS_IOREG(target,0x111)

/** 
 * \brief
 * Number of bits SERDES input is shifted for block lock.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_GB_SHIFT . GB_SHIFT_1
 */
#define  VTSS_F_PCS25G_RSFEC_GB_SHIFT_GB_SHIFT_1(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_PCS25G_RSFEC_GB_SHIFT_GB_SHIFT_1     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_PCS25G_RSFEC_GB_SHIFT_GB_SHIFT_1(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief Vendor Specific Reg; Latency measurement.
 *
 * \details
 * Register: \a PCS25G_RSFEC:PCS_REGISTERS:LATENCY
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_LATENCY(target)    VTSS_IOREG(target,0x112)

/** 
 * \brief
 * PCS Rx and Tx latency w.r.t SERDES clock. TX latency is on 15:9 and RX
 * latency is on 8:0
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_LATENCY . LATENCY_1
 */
#define  VTSS_F_PCS25G_RSFEC_LATENCY_LATENCY_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_LATENCY_LATENCY_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_LATENCY_LATENCY_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a PCS25G_RSFEC:RS_FEC_REGISTERS
 *
 * RS_FEC Sub-module Configuration, Control and Status Registers; All registers are 16-bit wide.
 */


/** 
 * \brief Control register for enabling FEC functions.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_CONTROL
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_CONTROL(target)  VTSS_IOREG(target,0x200)

/** 
 * \brief
 * When 1, bypass the decoder's correction function for reduced latency;
 * When 
 * 0, normal FEC operation; Bit is writeable only if capability in
 * FEC_STATUS indicates this feature.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_CONTROL . RS_FEC_CONTROL_BYPASS_CORRECTION
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_CONTROL_RS_FEC_CONTROL_BYPASS_CORRECTION(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_CONTROL_RS_FEC_CONTROL_BYPASS_CORRECTION  VTSS_BIT(0)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_CONTROL_RS_FEC_CONTROL_BYPASS_CORRECTION(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * When 1, configure the FEC decoder to not indicate errors to the PCS
 * layer; When
 *  0, the FEC decoder indicates errors to the PCS layer; Bit is writeable
 * only if capability in FEC_STATUS indicates this feature.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_CONTROL . BYPASS_ERROR_INDICATION
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_CONTROL_BYPASS_ERROR_INDICATION(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_CONTROL_BYPASS_ERROR_INDICATION  VTSS_BIT(1)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_CONTROL_BYPASS_ERROR_INDICATION(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When 1, enable RSFEC datapath; When 0 normal PCS datapath;
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_CONTROL . RS_FEC_ENABLE
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_CONTROL_RS_FEC_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_CONTROL_RS_FEC_ENABLE  VTSS_BIT(2)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_CONTROL_RS_FEC_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/** 
 * \brief RS FEC Status register.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_STATUS
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_STATUS(target)  VTSS_IOREG(target,0x201)

/** 
 * \brief
 * Always 1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_STATUS . PCS_ALIGN_STATUS
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_STATUS_PCS_ALIGN_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_STATUS_PCS_ALIGN_STATUS  VTSS_BIT(15)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_STATUS_PCS_ALIGN_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Indicates existence of the receive correction bypass option; The bypass
 * function allows a reduced latency operation.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_STATUS . RS_FEC_STATUS_BYPASS_CORRECTION
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_STATUS_RS_FEC_STATUS_BYPASS_CORRECTION(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_STATUS_RS_FEC_STATUS_BYPASS_CORRECTION  VTSS_BIT(0)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_STATUS_RS_FEC_STATUS_BYPASS_CORRECTION(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Indicates the ability to disable error propagation to the PCS layer.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_STATUS . BYPASS_INDICATION
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_STATUS_BYPASS_INDICATION(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_STATUS_BYPASS_INDICATION  VTSS_BIT(1)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_STATUS_BYPASS_INDICATION(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Asserts when error indication bypass is enabled and high symbol error
 * rate is found;
 *  Clear on read.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_STATUS . HIGH_SER
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_STATUS_HIGH_SER(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_STATUS_HIGH_SER  VTSS_BIT(2)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_STATUS_HIGH_SER(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * RS-FEC receive lane locked and aligned; One bit per lane: Bit 8 = lane
 * 0, Bit 9 = lane 1, Bit 10= lane 2, Bit 11 = lane 3.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_STATUS . RS_FEC_STATUS_AMPS_LOCK
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_STATUS_RS_FEC_STATUS_AMPS_LOCK(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_STATUS_RS_FEC_STATUS_AMPS_LOCK     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_STATUS_RS_FEC_STATUS_AMPS_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Indicates, when 1 that the RS-FEC receiver has locked on incoming data
 * and deskew completed.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_STATUS . FEC_ALIGN_STATUS
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_STATUS_FEC_ALIGN_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_STATUS_FEC_ALIGN_STATUS  VTSS_BIT(14)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_STATUS_FEC_ALIGN_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,14,1)


/** 
 * \brief Counts number of corrected FEC codewords lower 16-bits; None roll-over when upper 16-bits are 0xffff.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_CCW_LO
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_CCW_LO(target)  VTSS_IOREG(target,0x202)

/** 
 * \brief
 * Counts number of corrected FEC codewords lower 16-bits; Must be read
 * before upper 16-bits; None roll-over when upper 16-bits are 0xffff
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_CCW_LO . RS_FEC_CCW_LO_COUNTER
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_CCW_LO_RS_FEC_CCW_LO_COUNTER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_CCW_LO_RS_FEC_CCW_LO_COUNTER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_CCW_LO_RS_FEC_CCW_LO_COUNTER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Counts number of corrected FEC codewords upper 16-bits; Clears on read; None roll-over.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_CCW_HI
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_CCW_HI(target)  VTSS_IOREG(target,0x203)

/** 
 * \brief
 * Counts number of corrected FEC codewords upper 16-bits; None roll-over;
 * Clears when read.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_CCW_HI . RS_FEC_CCW_HI_COUNTER_HI
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_CCW_HI_RS_FEC_CCW_HI_COUNTER_HI(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_CCW_HI_RS_FEC_CCW_HI_COUNTER_HI     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_CCW_HI_RS_FEC_CCW_HI_COUNTER_HI(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Counts number of uncorrected FEC codewords lower 16-bits; None roll-over when upper 16-bits are 0xffff.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_NCCW_LO
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_NCCW_LO(target)  VTSS_IOREG(target,0x204)

/** 
 * \brief
 * Counts number of uncorrected FEC codewords lower 16-bits; Must be read
 * before upper 16-bits; None roll-over when upper 16-bits are 0xffff
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_NCCW_LO . RS_FEC_NCCW_LO_COUNTER
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_NCCW_LO_RS_FEC_NCCW_LO_COUNTER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_NCCW_LO_RS_FEC_NCCW_LO_COUNTER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_NCCW_LO_RS_FEC_NCCW_LO_COUNTER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Counts number of uncorrected FEC codewords upper 16-bits; Clears on read; None roll-over.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_NCCW_HI
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_NCCW_HI(target)  VTSS_IOREG(target,0x205)

/** 
 * \brief
 * Counts number of uncorrected FEC codewords upper 16-bits; None
 * roll-over; Clears when read.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_NCCW_HI . RS_FEC_NCCW_HI_COUNTER_HI
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_NCCW_HI_RS_FEC_NCCW_HI_COUNTER_HI(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_NCCW_HI_RS_FEC_NCCW_HI_COUNTER_HI     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_NCCW_HI_RS_FEC_NCCW_HI_COUNTER_HI(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief FEC alignment status and lane mappings.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_LANEMAP
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_LANEMAP(target)  VTSS_IOREG(target,0x206)

/** 
 * \brief
 * FEC lane mapped to PMA lane 0.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_LANEMAP . PMA_LANE_0
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_LANEMAP_PMA_LANE_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_LANEMAP_PMA_LANE_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_LANEMAP_PMA_LANE_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * FEC lane mapped to PMA lane 1.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_LANEMAP . PMA_LANE_1
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_LANEMAP_PMA_LANE_1(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_LANEMAP_PMA_LANE_1     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_LANEMAP_PMA_LANE_1(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * FEC lane mapped to PMA lane 2.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_LANEMAP . PMA_LANE_2
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_LANEMAP_PMA_LANE_2(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_LANEMAP_PMA_LANE_2     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_LANEMAP_PMA_LANE_2(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * FEC lane mapped to PMA lane 3.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_LANEMAP . PMA_LANE_3
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_LANEMAP_PMA_LANE_3(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_LANEMAP_PMA_LANE_3     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_LANEMAP_PMA_LANE_3(x)  VTSS_EXTRACT_BITFIELD(x,6,2)


/** 
 * \brief Counts number of (corrected) 10-bit symbol errors found in lane 0; None roll-over when upper 16-bits are 0xffff.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_SYMBLERR0_LO
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR0_LO(target)  VTSS_IOREG(target,0x20a)

/** 
 * \brief
 * Counts number of (corrected) 10-bit symbol errors found in lane 0 for
 * correctable codewords only; Lower 16-bit of counter; Must be read first;
 * None roll-over when upper word is 0xffff.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR0_LO . RS_FEC_SYMBLERR0_LO_SYMBOL_ERRORS
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_SYMBLERR0_LO_RS_FEC_SYMBLERR0_LO_SYMBOL_ERRORS(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_SYMBLERR0_LO_RS_FEC_SYMBLERR0_LO_SYMBOL_ERRORS     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_SYMBLERR0_LO_RS_FEC_SYMBLERR0_LO_SYMBOL_ERRORS(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16-bit of counter (with above register); Clears on read; None roll-over.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_SYMBLERR0_HI
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR0_HI(target)  VTSS_IOREG(target,0x20b)

/** 
 * \brief
 * Upper 16-bits of the 32-bit Symbol error counter for lane 0; Clears on
 * read; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR0_HI . RS_FEC_SYMBLERR0_HI_SYMBOL_ERROR_HI
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_SYMBLERR0_HI_RS_FEC_SYMBLERR0_HI_SYMBOL_ERROR_HI(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_SYMBLERR0_HI_RS_FEC_SYMBLERR0_HI_SYMBOL_ERROR_HI     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_SYMBLERR0_HI_RS_FEC_SYMBLERR0_HI_SYMBOL_ERROR_HI(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Counts number of (corrected) 10-bit symbol errors found in lane 1; None roll-over when upper 16-bits are 0xffff.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_SYMBLERR1_LO
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR1_LO(target)  VTSS_IOREG(target,0x20c)

/** 
 * \brief
 * Counts number of (corrected) 10-bit symbol errors found in lane 1 for
 * correctable codewords only; Lower 16-bit of counter; Must be read first;
 * None roll-over when upper word is 0xffff.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR1_LO . RS_FEC_SYMBLERR1_LO_SYMBOL_ERRORS
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_SYMBLERR1_LO_RS_FEC_SYMBLERR1_LO_SYMBOL_ERRORS(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_SYMBLERR1_LO_RS_FEC_SYMBLERR1_LO_SYMBOL_ERRORS     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_SYMBLERR1_LO_RS_FEC_SYMBLERR1_LO_SYMBOL_ERRORS(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16-bit of counter (with above register); Clears on read; None roll-over.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_SYMBLERR1_HI
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR1_HI(target)  VTSS_IOREG(target,0x20d)

/** 
 * \brief
 * Upper 16-bits of the 32-bit Symbol error counter for lane 1; Clears on
 * read; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR1_HI . RS_FEC_SYMBLERR1_HI_SYMBOL_ERROR_HI
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_SYMBLERR1_HI_RS_FEC_SYMBLERR1_HI_SYMBOL_ERROR_HI(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_SYMBLERR1_HI_RS_FEC_SYMBLERR1_HI_SYMBOL_ERROR_HI     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_SYMBLERR1_HI_RS_FEC_SYMBLERR1_HI_SYMBOL_ERROR_HI(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Counts number of (corrected) 10-bit symbol errors found in lane 2; None roll-over when upper 16-bits are 0xffff.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_SYMBLERR2_LO
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR2_LO(target)  VTSS_IOREG(target,0x20e)

/** 
 * \brief
 * Counts number of (corrected) 10-bit symbol errors found in lane 2 for
 * correctable codewords only; Lower 16-bit of counter; Must be read first;
 * None roll-over when upper word is 0xffff.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR2_LO . RS_FEC_SYMBLERR2_LO_SYMBOL_ERRORS
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_SYMBLERR2_LO_RS_FEC_SYMBLERR2_LO_SYMBOL_ERRORS(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_SYMBLERR2_LO_RS_FEC_SYMBLERR2_LO_SYMBOL_ERRORS     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_SYMBLERR2_LO_RS_FEC_SYMBLERR2_LO_SYMBOL_ERRORS(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16-bit of counter (with above register); Clears on read; None roll-over.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_SYMBLERR2_HI
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR2_HI(target)  VTSS_IOREG(target,0x20f)

/** 
 * \brief
 * Upper 16-bits of the 32-bit Symbol error counter for lane 2; Clears on
 * read; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR2_HI . RS_FEC_SYMBLERR2_HI_SYMBOL_ERROR_HI
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_SYMBLERR2_HI_RS_FEC_SYMBLERR2_HI_SYMBOL_ERROR_HI(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_SYMBLERR2_HI_RS_FEC_SYMBLERR2_HI_SYMBOL_ERROR_HI     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_SYMBLERR2_HI_RS_FEC_SYMBLERR2_HI_SYMBOL_ERROR_HI(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Counts number of (corrected) 10-bit symbol errors found in lane 3; None roll-over when upper 16-bits are 0xffff.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_SYMBLERR3_LO
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR3_LO(target)  VTSS_IOREG(target,0x210)

/** 
 * \brief
 * Counts number of (corrected) 10-bit symbol errors found in lane 3 for
 * correctable codewords only; Lower 16-bit of counter; Must be read first;
 * None roll-over when upper word is 0xffff.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR3_LO . RS_FEC_SYMBLERR3_LO_SYMBOL_ERRORS
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_SYMBLERR3_LO_RS_FEC_SYMBLERR3_LO_SYMBOL_ERRORS(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_SYMBLERR3_LO_RS_FEC_SYMBLERR3_LO_SYMBOL_ERRORS     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_SYMBLERR3_LO_RS_FEC_SYMBLERR3_LO_SYMBOL_ERRORS(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16 bit of counter (with above register); Clears on read; None roll-over.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_SYMBLERR3_HI
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR3_HI(target)  VTSS_IOREG(target,0x211)

/** 
 * \brief
 * Upper 16-bits of the 32-bit Symbol error counter for lane 3; Clears on
 * read; None roll-over.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_SYMBLERR3_HI . RS_FEC_SYMBLERR3_HI_SYMBOL_ERROR_HI
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_SYMBLERR3_HI_RS_FEC_SYMBLERR3_HI_SYMBOL_ERROR_HI(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_SYMBLERR3_HI_RS_FEC_SYMBLERR3_HI_SYMBOL_ERROR_HI     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_SYMBLERR3_HI_RS_FEC_SYMBLERR3_HI_SYMBOL_ERROR_HI(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Additional control to enable RS-FEC operation.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_VENDOR_CONTROL
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL(target)  VTSS_IOREG(target,0x280)

/** 
 * \brief
 * When 1, enable RSFEC datapath of Channel 0; This is a legacy bit only,
 * ORed with Channel 0 RS_FEC_CONTROL bit 2. Should not be used any more.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL . RS_FEC_ENABLE0
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL_RS_FEC_ENABLE0(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL_RS_FEC_ENABLE0  VTSS_BIT(2)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL_RS_FEC_ENABLE0(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Channel 0; When 1 use RSFEC over single lane 0 (25G); When 0 use RSFEC
 * over 2 lanes 0,1 (50G).
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL . CH0_1LANE_MODE
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE  VTSS_BIT(4)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Channel 2; When 1 use RSFEC over single lane 2 (25G); When 0 use RSFEC
 * over 2 lanes 2,3 (50G).
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL . CH2_1LANE_MODE
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL_CH2_1LANE_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL_CH2_1LANE_MODE  VTSS_BIT(5)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL_CH2_1LANE_MODE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Indicates per channel if RSFEC is currently enabled (1) or not (0).
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL . RS_FEC_STATUS
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL_RS_FEC_STATUS(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL_RS_FEC_STATUS     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_CONTROL_RS_FEC_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,12,4)


/** 
 * \brief Implementation specific information that may be useful for debugging link problems; Clears on read.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_VENDOR_INFO1
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1(target)  VTSS_IOREG(target,0x281)

/** 
 * \brief
 * Per PMA lane FEC synchronization status; Bit 0=lane 0 up to Bit 3 = lane
 * 3; Latched high; Clear on read.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1 . RS_FEC_VENDOR_INFO1_AMPS_LOCK
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_RS_FEC_VENDOR_INFO1_AMPS_LOCK(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_RS_FEC_VENDOR_INFO1_AMPS_LOCK     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_RS_FEC_VENDOR_INFO1_AMPS_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * FEC alignment status; Latched high; Clear on read.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1 . FEC_ALIGN_STATUS_LH
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_FEC_ALIGN_STATUS_LH(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_FEC_ALIGN_STATUS_LH  VTSS_BIT(4)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_FEC_ALIGN_STATUS_LH(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * The marker_check function (PCS sublayer) caused an alignment restart to
 * the FEC; Latched high; Clear on read.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1 . MARKER_CHECK_RESTART
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_MARKER_CHECK_RESTART(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_MARKER_CHECK_RESTART  VTSS_BIT(5)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_MARKER_CHECK_RESTART(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * RX datapath (sync) reset occured; Latched high; Clear on read.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1 . RX_DATAPATH_RESTART
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_RX_DATAPATH_RESTART(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_RX_DATAPATH_RESTART  VTSS_BIT(6)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_RX_DATAPATH_RESTART(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * TX datapath (sync) reset occured; Latched high; Clear on read.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1 . TX_DATAPATH_RESTART
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_TX_DATAPATH_RESTART(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_TX_DATAPATH_RESTART  VTSS_BIT(7)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_TX_DATAPATH_RESTART(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * RX datapath 4x66 pacing fifo overflow fatal error; Latched high; Clear
 * on read.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1 . RX_DP_OVERFLOW
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_RX_DP_OVERFLOW(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_RX_DP_OVERFLOW  VTSS_BIT(8)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_RX_DP_OVERFLOW(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * TX datapath 4x66 input fifo overflow fatal error; Latched high; Clear on
 * read.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1 . TX_DP_OVERFLOW
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_TX_DP_OVERFLOW(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_TX_DP_OVERFLOW  VTSS_BIT(9)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_TX_DP_OVERFLOW(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * FEC alignment status; Latched high; Sets on read.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1 . FEC_ALIGN_STATUS_LL
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_FEC_ALIGN_STATUS_LL(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_FEC_ALIGN_STATUS_LL  VTSS_BIT(10)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_FEC_ALIGN_STATUS_LL(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * reserved, unused.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1 . DESKEW_EMPTY
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_DESKEW_EMPTY(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_DESKEW_EMPTY     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_INFO1_DESKEW_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,12,4)


/** 
 * \brief Implementation specific status information; Clears on read.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_VENDOR_INFO2
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_INFO2(target)  VTSS_IOREG(target,0x282)

/** 
 * \brief
 * Per PMA lane FEC synchronization status; Realtime updates;
 *  Bit  0 = lane 0 upto bit 3 = lane 3;
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_INFO2 . RS_FEC_VENDOR_INFO2_AMPS_LOCK
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_INFO2_RS_FEC_VENDOR_INFO2_AMPS_LOCK(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_INFO2_RS_FEC_VENDOR_INFO2_AMPS_LOCK     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_INFO2_RS_FEC_VENDOR_INFO2_AMPS_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Per PMA lane RSFEC decoder internal error; Latched-high;
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_INFO2 . RS_DECODER_WRITE_ERR
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_INFO2_RS_DECODER_WRITE_ERR(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_INFO2_RS_DECODER_WRITE_ERR     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_INFO2_RS_DECODER_WRITE_ERR(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief A version information taken from package file parameter FEC91_DEV_VERSION.
 *
 * \details
 * Register: \a PCS25G_RSFEC:RS_FEC_REGISTERS:RS_FEC_VENDOR_REVISION
 *
 * @param target A \a ::vtss_target_PCS25G_RSFEC_e target
 */
#define VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_REVISION(target)  VTSS_IOREG(target,0x283)

/** 
 * \brief
 * A version information taken from package file parameter
 * FEC91_DEV_VERSION.
 *
 * \details 
 * Field: ::VTSS_PCS25G_RSFEC_RS_FEC_VENDOR_REVISION . REVISION
 */
#define  VTSS_F_PCS25G_RSFEC_RS_FEC_VENDOR_REVISION_REVISION(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS25G_RSFEC_RS_FEC_VENDOR_REVISION_REVISION     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS25G_RSFEC_RS_FEC_VENDOR_REVISION_REVISION(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_FA_REGS_PCS25G_RSFEC_H_ */
