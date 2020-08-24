/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/fxvl_pdi_registers_def.xml
// Register File Name  : FXVL_PDI_REGISTERS
// Register File Title : Control Registers FXVL
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _FXVL_PDI_REGISTERS_H
#define _FXVL_PDI_REGISTERS_H

//! \defgroup FXVL_PDI_REGISTERS Register File FXVL_PDI_REGISTERS - Control Registers FXVL
//! @{

//! Base Address of FXVL_PDI_REGISTERS
#define FXVL_PDI_REGISTERS_MODULE_BASE 0x00D2C000u

//! \defgroup FXVL_PDI_REGISTERS_CTRL_OUT Register FXVL_PDI_REGISTERS_CTRL_OUT - FXVL Control Output Register from FXVL to GPHY
//! @{

//! Register Offset (relative)
#define FXVL_PDI_REGISTERS_CTRL_OUT 0x0
//! Register Offset (absolute) for 1st Instance FXVL_PDI_REGISTERS
#define FXVL_PDI_REGISTERS_FXVL_PDI_REGISTERS_CTRL_OUT 0x00D2C000u

//! Register Reset Value
#define FXVL_PDI_REGISTERS_CTRL_OUT_RST 0x000000C0u

//! Field FCO0 - Ultra Low Power
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO0_POS 0
//! Field FCO0 - Ultra Low Power
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO0_MASK 0x1u
//! Constant OFF - ULP_EN is off
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO0_OFF 0x0
//! Constant ON - ULP_EN is on
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO0_ON 0x1

//! Field FCO1 - Smart Power Down Back to Back
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO1_POS 1
//! Field FCO1 - Smart Power Down Back to Back
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO1_MASK 0x2u
//! Constant DIS - Disable beacon generation
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO1_DIS 0x0
//! Constant EN - Enable beacon generation
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO1_EN 0x1

//! Field FCO2 - Restart Auto-negotiation Now
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO2_POS 2
//! Field FCO2 - Restart Auto-negotiation Now
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO2_MASK 0x4u
//! Constant DIS - Disable
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO2_DIS 0x0
//! Constant EN - Enable
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO2_EN 0x1

//! Field FCO3 - Disable 2500Base-T Auto-negotiation
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO3_POS 3
//! Field FCO3 - Disable 2500Base-T Auto-negotiation
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO3_MASK 0x8u
//! Constant EN - Enable
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO3_EN 0x0
//! Constant DIS - Disable
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO3_DIS 0x1

//! Field FCO4 - Disable 1000Base-T Auto-negotiation
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO4_POS 4
//! Field FCO4 - Disable 1000Base-T Auto-negotiation
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO4_MASK 0x10u
//! Constant EN - Enable
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO4_EN 0x0
//! Constant DIS - Disable
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO4_DIS 0x1

//! Field FCO5 - Disable 100Base-TX Auto-negotiation
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO5_POS 5
//! Field FCO5 - Disable 100Base-TX Auto-negotiation
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO5_MASK 0x20u
//! Constant EN - Enable
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO5_EN 0x0
//! Constant DIS - Disable
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO5_DIS 0x1

//! Field FCO6 - Link Disconnect
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO6_POS 6
//! Field FCO6 - Link Disconnect
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO6_MASK 0x40u
//! Constant ACTIVE - Link Connect
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO6_ACTIVE 0x0
//! Constant DISC - Go Link Disconnect
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO6_DISC 0x1

//! Field FCO7 - MDI Flip Enable
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO7_POS 7
//! Field FCO7 - MDI Flip Enable
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO7_MASK 0x80u
//! Constant DIS - Disable Auto Crossover
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO7_DIS 0x0
//! Constant EN - Enable Auto Crossover
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO7_EN 0x1

//! Field FCO8 - 10Base-Te Low Power
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO8_POS 8
//! Field FCO8 - 10Base-Te Low Power
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO8_MASK 0x100u
//! Constant DIS - Disable low power
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO8_DIS 0x0
//! Constant EN - Enable low power
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO8_EN 0x1

//! Field FCO9 - 100BT EEE Enable
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO9_POS 9
//! Field FCO9 - 100BT EEE Enable
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO9_MASK 0x200u
//! Constant DIS - Disable 100BaseT EEE capability
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO9_DIS 0x0
//! Constant EN - Enable 100BaseT EEE capability
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO9_EN 0x1

//! Field FCO10 - 1000BT EEE Enable
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO10_POS 10
//! Field FCO10 - 1000BT EEE Enable
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO10_MASK 0x400u
//! Constant DIS - Disable 1000BaseT EEE capability
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO10_DIS 0x0
//! Constant EN - Enable 1000BaseT EEE capability
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO10_EN 0x1

//! Field FCO11 - 2500BT EEE Enable
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO11_POS 11
//! Field FCO11 - 2500BT EEE Enable
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO11_MASK 0x800u
//! Constant DIS - Disable 2500BaseT EEE capability
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO11_DIS 0x0
//! Constant EN - Enable 2500BaseT EEE capability
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO11_EN 0x1

//! Field FCO12 - PHY Reset
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO12_POS 12
//! Field FCO12 - PHY Reset
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO12_MASK 0x1000u
//! Constant INACTIVE - GPHY in power down
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO12_INACTIVE 0x0
//! Constant ACTIVE - GPHY operational
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO12_ACTIVE 0x1

//! Field FCO13 - PHY Power Down
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO13_POS 13
//! Field FCO13 - PHY Power Down
#define FXVL_PDI_REGISTERS_CTRL_OUT_FCO13_MASK 0x2000u
//! Constant INACTIVE - Inactive
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO13_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_FXVL_PDI_REGISTERS_CTRL_OUT_FCO13_ACTIVE 0x1

//! @}

//! \defgroup FXVL_PDI_REGISTERS_CTRL_IN Register FXVL_PDI_REGISTERS_CTRL_IN - FXVL Control Input Register from GPHY to FXVL
//! @{

//! Register Offset (relative)
#define FXVL_PDI_REGISTERS_CTRL_IN 0x4
//! Register Offset (absolute) for 1st Instance FXVL_PDI_REGISTERS
#define FXVL_PDI_REGISTERS_FXVL_PDI_REGISTERS_CTRL_IN 0x00D2C004u

//! Register Reset Value
#define FXVL_PDI_REGISTERS_CTRL_IN_RST 0x00000002u

//! Field FCI0 - PHY is in Power Down
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI0_POS 0
//! Field FCI0 - PHY is in Power Down
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI0_MASK 0x1u
//! Constant ACTIVE - PHY is not in not in power down
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI0_ACTIVE 0x0
//! Constant PD - PHY is in power down
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI0_PD 0x1

//! Field FCI1 - PHY interrupt
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI1_POS 1
//! Field FCI1 - PHY interrupt
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI1_MASK 0x2u
//! Constant INT - Interrupt
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI1_INT 0x0
//! Constant NOINT - No interrupt
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI1_NOINT 0x1

//! Field FCI2 - PHY Link Energy Detect
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI2_POS 2
//! Field FCI2 - PHY Link Energy Detect
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI2_MASK 0x4u
//! Constant NONRG - No Link Energy is detected
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI2_NONRG 0x0
//! Constant ENERGY - Link energy is detected
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI2_ENERGY 0x1

//! Field FCI3 - PHY Reset Complete
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI3_POS 3
//! Field FCI3 - PHY Reset Complete
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI3_MASK 0x8u
//! Constant NRDY - PHY in reset
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI3_NRDY 0x0
//! Constant RDY - PHY Ready
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI3_RDY 0x1

//! Field FCI4 - Link From PHY
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI4_POS 4
//! Field FCI4 - Link From PHY
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI4_MASK 0x10u
//! Constant DOWN - Link not established
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI4_DOWN 0x0
//! Constant UP - Link established
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI4_UP 0x1

//! Field FCI5 - Full Duplex
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI5_POS 5
//! Field FCI5 - Full Duplex
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI5_MASK 0x20u
//! Constant HALF - Half Duplex
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI5_HALF 0x0
//! Constant FULL - Full Duplex
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI5_FULL 0x1

//! Field FCI6 - Speed
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI6_POS 6
//! Field FCI6 - Speed
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI6_MASK 0xC0u
//! Constant BT10 - 10BASE-T or no link
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI6_BT10 0x0
//! Constant BT100 - 100BASE-TX
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI6_BT100 0x1
//! Constant BT1000 - 1000BASE-T or 2500BASE-T
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI6_BT1000 0x2

//! Field FCI8 - Speed 2.5G
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI8_POS 8
//! Field FCI8 - Speed 2.5G
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI8_MASK 0x100u
//! Constant NG2_5 - Not 2.5Gbps speed
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI8_NG2_5 0x0
//! Constant G2_5 - 2.5Gbps speed
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI8_G2_5 0x1

//! Field FCI9 - PHY EEE
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI9_POS 9
//! Field FCI9 - PHY EEE
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI9_MASK 0x200u
//! Constant NEEE - EEE not negotiated
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI9_NEEE 0x0
//! Constant EEE - EEE negotiated
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI9_EEE 0x1

//! Field FCI10 - PHY Link Disconnect
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI10_POS 10
//! Field FCI10 - PHY Link Disconnect
#define FXVL_PDI_REGISTERS_CTRL_IN_FCI10_MASK 0x400u
//! Constant NONRG - No Link Energy is detected
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI10_NONRG 0x0
//! Constant ENERGY - Link Energy is detected
#define CONST_FXVL_PDI_REGISTERS_CTRL_IN_FCI10_ENERGY 0x1

//! @}

//! @}

#endif
