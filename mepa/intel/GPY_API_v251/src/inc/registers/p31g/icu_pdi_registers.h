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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/icu_pdi_registers_def.xml
// Register File Name  : ICU_PDI_REGISTERS
// Register File Title : Registers Interrupt controller
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _ICU_PDI_REGISTERS_H
#define _ICU_PDI_REGISTERS_H

//! \defgroup ICU_PDI_REGISTERS Register File ICU_PDI_REGISTERS - Registers Interrupt controller
//! @{

//! Base Address of ICU_PDI_REGISTERS
#define ICU_PDI_REGISTERS_MODULE_BASE 0x00D3CF00u

//! \defgroup ICU_PDI_REGISTERS_IM0_ISR Register ICU_PDI_REGISTERS_IM0_ISR - IM0 Interrupt Status Register
//! @{

//! Register Offset (relative)
#define ICU_PDI_REGISTERS_IM0_ISR 0x0
//! Register Offset (absolute) for 1st Instance ICU_PDI_REGISTERS
#define ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM0_ISR 0x00D3CF00u

//! Register Reset Value
#define ICU_PDI_REGISTERS_IM0_ISR_RST 0x00000000u

//! Field IR0 - Status of Interrupt Request GPHY
#define ICU_PDI_REGISTERS_IM0_ISR_IR0_POS 0
//! Field IR0 - Status of Interrupt Request GPHY
#define ICU_PDI_REGISTERS_IM0_ISR_IR0_MASK 0x1u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR0_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR0_ACTIVE 0x1

//! Field IR1 - Status of Interrupt Request PM
#define ICU_PDI_REGISTERS_IM0_ISR_IR1_POS 1
//! Field IR1 - Status of Interrupt Request PM
#define ICU_PDI_REGISTERS_IM0_ISR_IR1_MASK 0x2u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR1_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR1_ACTIVE 0x1

//! Field IR2 - Status of Interrupt Request MGE
#define ICU_PDI_REGISTERS_IM0_ISR_IR2_POS 2
//! Field IR2 - Status of Interrupt Request MGE
#define ICU_PDI_REGISTERS_IM0_ISR_IR2_MASK 0x4u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR2_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR2_ACTIVE 0x1

//! Field IR3 - Status of Interrupt Request External Interrupt 0
#define ICU_PDI_REGISTERS_IM0_ISR_IR3_POS 3
//! Field IR3 - Status of Interrupt Request External Interrupt 0
#define ICU_PDI_REGISTERS_IM0_ISR_IR3_MASK 0x8u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR3_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR3_ACTIVE 0x1

//! Field IR4 - Status of Interrupt Request External Interrupt 1
#define ICU_PDI_REGISTERS_IM0_ISR_IR4_POS 4
//! Field IR4 - Status of Interrupt Request External Interrupt 1
#define ICU_PDI_REGISTERS_IM0_ISR_IR4_MASK 0x10u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR4_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR4_ACTIVE 0x1

//! Field IR5 - Status of Interrupt Request SGMII
#define ICU_PDI_REGISTERS_IM0_ISR_IR5_POS 5
//! Field IR5 - Status of Interrupt Request SGMII
#define ICU_PDI_REGISTERS_IM0_ISR_IR5_MASK 0x20u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR5_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR5_ACTIVE 0x1

//! Field IR6 - Status of Interrupt Request FXVL IP
#define ICU_PDI_REGISTERS_IM0_ISR_IR6_POS 6
//! Field IR6 - Status of Interrupt Request FXVL IP
#define ICU_PDI_REGISTERS_IM0_ISR_IR6_MASK 0x40u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR6_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR6_ACTIVE 0x1

//! Field IR7 - Status of Interrupt Request Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_ISR_IR7_POS 7
//! Field IR7 - Status of Interrupt Request Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_ISR_IR7_MASK 0x80u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR7_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR7_ACTIVE 0x1

//! Field IR8 - Status of Interrupt Request CDB
#define ICU_PDI_REGISTERS_IM0_ISR_IR8_POS 8
//! Field IR8 - Status of Interrupt Request CDB
#define ICU_PDI_REGISTERS_IM0_ISR_IR8_MASK 0x100u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR8_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR8_ACTIVE 0x1

//! Field IR9 - Status of Interrupt Request DCDC
#define ICU_PDI_REGISTERS_IM0_ISR_IR9_POS 9
//! Field IR9 - Status of Interrupt Request DCDC
#define ICU_PDI_REGISTERS_IM0_ISR_IR9_MASK 0x200u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR9_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR9_ACTIVE 0x1

//! Field IR10 - Status of Interrupt Request Wake-Up
#define ICU_PDI_REGISTERS_IM0_ISR_IR10_POS 10
//! Field IR10 - Status of Interrupt Request Wake-Up
#define ICU_PDI_REGISTERS_IM0_ISR_IR10_MASK 0x400u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR10_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR10_ACTIVE 0x1

//! Field IR11 - Status of Interrupt Request XO/DCPM
#define ICU_PDI_REGISTERS_IM0_ISR_IR11_POS 11
//! Field IR11 - Status of Interrupt Request XO/DCPM
#define ICU_PDI_REGISTERS_IM0_ISR_IR11_MASK 0x800u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR11_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR11_ACTIVE 0x1

//! Field IR12 - Reserved
#define ICU_PDI_REGISTERS_IM0_ISR_IR12_POS 12
//! Field IR12 - Reserved
#define ICU_PDI_REGISTERS_IM0_ISR_IR12_MASK 0x1000u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR12_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_ISR_IR12_ACTIVE 0x1

//! @}

//! \defgroup ICU_PDI_REGISTERS_IM0_IER_0 Register ICU_PDI_REGISTERS_IM0_IER_0 - IM0 Interrupt Enable Register
//! @{

//! Register Offset (relative)
#define ICU_PDI_REGISTERS_IM0_IER_0 0x4
//! Register Offset (absolute) for 1st Instance ICU_PDI_REGISTERS
#define ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM0_IER_0 0x00D3CF04u

//! Register Reset Value
#define ICU_PDI_REGISTERS_IM0_IER_0_RST 0x00000000u

//! Field IR0 - Interrupt Enable GPHY
#define ICU_PDI_REGISTERS_IM0_IER_0_IR0_POS 0
//! Field IR0 - Interrupt Enable GPHY
#define ICU_PDI_REGISTERS_IM0_IER_0_IR0_MASK 0x1u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR0_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR0_ACTIVE 0x1

//! Field IR1 - Interrupt Enable PM
#define ICU_PDI_REGISTERS_IM0_IER_0_IR1_POS 1
//! Field IR1 - Interrupt Enable PM
#define ICU_PDI_REGISTERS_IM0_IER_0_IR1_MASK 0x2u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR1_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR1_ACTIVE 0x1

//! Field IR2 - Interrupt Enable MGE
#define ICU_PDI_REGISTERS_IM0_IER_0_IR2_POS 2
//! Field IR2 - Interrupt Enable MGE
#define ICU_PDI_REGISTERS_IM0_IER_0_IR2_MASK 0x4u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR2_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR2_ACTIVE 0x1

//! Field IR3 - Interrupt Enable External Interrupt 0
#define ICU_PDI_REGISTERS_IM0_IER_0_IR3_POS 3
//! Field IR3 - Interrupt Enable External Interrupt 0
#define ICU_PDI_REGISTERS_IM0_IER_0_IR3_MASK 0x8u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR3_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR3_ACTIVE 0x1

//! Field IR4 - Interrupt Enable External Interrupt 1
#define ICU_PDI_REGISTERS_IM0_IER_0_IR4_POS 4
//! Field IR4 - Interrupt Enable External Interrupt 1
#define ICU_PDI_REGISTERS_IM0_IER_0_IR4_MASK 0x10u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR4_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR4_ACTIVE 0x1

//! Field IR5 - Interrupt Enable SGMII
#define ICU_PDI_REGISTERS_IM0_IER_0_IR5_POS 5
//! Field IR5 - Interrupt Enable SGMII
#define ICU_PDI_REGISTERS_IM0_IER_0_IR5_MASK 0x20u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR5_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR5_ACTIVE 0x1

//! Field IR6 - Interrupt Enable FXVL IP
#define ICU_PDI_REGISTERS_IM0_IER_0_IR6_POS 6
//! Field IR6 - Interrupt Enable FXVL IP
#define ICU_PDI_REGISTERS_IM0_IER_0_IR6_MASK 0x40u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR6_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR6_ACTIVE 0x1

//! Field IR7 - Interrupt Enable Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_IER_0_IR7_POS 7
//! Field IR7 - Interrupt Enable Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_IER_0_IR7_MASK 0x80u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR7_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR7_ACTIVE 0x1

//! Field IR8 - Interrupt Enable CDB
#define ICU_PDI_REGISTERS_IM0_IER_0_IR8_POS 8
//! Field IR8 - Interrupt Enable CDB
#define ICU_PDI_REGISTERS_IM0_IER_0_IR8_MASK 0x100u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR8_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR8_ACTIVE 0x1

//! Field IR9 - Interrupt Enable DCDC
#define ICU_PDI_REGISTERS_IM0_IER_0_IR9_POS 9
//! Field IR9 - Interrupt Enable DCDC
#define ICU_PDI_REGISTERS_IM0_IER_0_IR9_MASK 0x200u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR9_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR9_ACTIVE 0x1

//! Field IR10 - Interrupt Enable Wake-Up
#define ICU_PDI_REGISTERS_IM0_IER_0_IR10_POS 10
//! Field IR10 - Interrupt Enable Wake-Up
#define ICU_PDI_REGISTERS_IM0_IER_0_IR10_MASK 0x400u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR10_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR10_ACTIVE 0x1

//! Field IR11 - Interrupt Enable XO/DCPM
#define ICU_PDI_REGISTERS_IM0_IER_0_IR11_POS 11
//! Field IR11 - Interrupt Enable XO/DCPM
#define ICU_PDI_REGISTERS_IM0_IER_0_IR11_MASK 0x800u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR11_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR11_ACTIVE 0x1

//! Field IR12 - Reserved
#define ICU_PDI_REGISTERS_IM0_IER_0_IR12_POS 12
//! Field IR12 - Reserved
#define ICU_PDI_REGISTERS_IM0_IER_0_IR12_MASK 0x1000u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR12_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_0_IR12_ACTIVE 0x1

//! @}

//! \defgroup ICU_PDI_REGISTERS_IM0_IER_1 Register ICU_PDI_REGISTERS_IM0_IER_1 - IM0 Interrupt Enable Register
//! @{

//! Register Offset (relative)
#define ICU_PDI_REGISTERS_IM0_IER_1 0x8
//! Register Offset (absolute) for 1st Instance ICU_PDI_REGISTERS
#define ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM0_IER_1 0x00D3CF08u

//! Register Reset Value
#define ICU_PDI_REGISTERS_IM0_IER_1_RST 0x00000000u

//! Field IR0 - Interrupt Enable GPHY
#define ICU_PDI_REGISTERS_IM0_IER_1_IR0_POS 0
//! Field IR0 - Interrupt Enable GPHY
#define ICU_PDI_REGISTERS_IM0_IER_1_IR0_MASK 0x1u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR0_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR0_ACTIVE 0x1

//! Field IR1 - Interrupt Enable PM
#define ICU_PDI_REGISTERS_IM0_IER_1_IR1_POS 1
//! Field IR1 - Interrupt Enable PM
#define ICU_PDI_REGISTERS_IM0_IER_1_IR1_MASK 0x2u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR1_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR1_ACTIVE 0x1

//! Field IR2 - Interrupt Enable MGE
#define ICU_PDI_REGISTERS_IM0_IER_1_IR2_POS 2
//! Field IR2 - Interrupt Enable MGE
#define ICU_PDI_REGISTERS_IM0_IER_1_IR2_MASK 0x4u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR2_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR2_ACTIVE 0x1

//! Field IR3 - Interrupt Enable External Interrupt 0
#define ICU_PDI_REGISTERS_IM0_IER_1_IR3_POS 3
//! Field IR3 - Interrupt Enable External Interrupt 0
#define ICU_PDI_REGISTERS_IM0_IER_1_IR3_MASK 0x8u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR3_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR3_ACTIVE 0x1

//! Field IR4 - Interrupt Enable External Interrupt 1
#define ICU_PDI_REGISTERS_IM0_IER_1_IR4_POS 4
//! Field IR4 - Interrupt Enable External Interrupt 1
#define ICU_PDI_REGISTERS_IM0_IER_1_IR4_MASK 0x10u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR4_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR4_ACTIVE 0x1

//! Field IR5 - Interrupt Enable SGMII
#define ICU_PDI_REGISTERS_IM0_IER_1_IR5_POS 5
//! Field IR5 - Interrupt Enable SGMII
#define ICU_PDI_REGISTERS_IM0_IER_1_IR5_MASK 0x20u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR5_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR5_ACTIVE 0x1

//! Field IR6 - Interrupt Enable FXVL IP
#define ICU_PDI_REGISTERS_IM0_IER_1_IR6_POS 6
//! Field IR6 - Interrupt Enable FXVL IP
#define ICU_PDI_REGISTERS_IM0_IER_1_IR6_MASK 0x40u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR6_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR6_ACTIVE 0x1

//! Field IR7 - Interrupt Enable Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_IER_1_IR7_POS 7
//! Field IR7 - Interrupt Enable Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_IER_1_IR7_MASK 0x80u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR7_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR7_ACTIVE 0x1

//! Field IR8 - Interrupt Enable CDB
#define ICU_PDI_REGISTERS_IM0_IER_1_IR8_POS 8
//! Field IR8 - Interrupt Enable CDB
#define ICU_PDI_REGISTERS_IM0_IER_1_IR8_MASK 0x100u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR8_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR8_ACTIVE 0x1

//! Field IR9 - Interrupt Enable DCDC
#define ICU_PDI_REGISTERS_IM0_IER_1_IR9_POS 9
//! Field IR9 - Interrupt Enable DCDC
#define ICU_PDI_REGISTERS_IM0_IER_1_IR9_MASK 0x200u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR9_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR9_ACTIVE 0x1

//! Field IR10 - Interrupt Enable Wake-Up
#define ICU_PDI_REGISTERS_IM0_IER_1_IR10_POS 10
//! Field IR10 - Interrupt Enable Wake-Up
#define ICU_PDI_REGISTERS_IM0_IER_1_IR10_MASK 0x400u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR10_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR10_ACTIVE 0x1

//! Field IR11 - Interrupt Enable XO/DCPM
#define ICU_PDI_REGISTERS_IM0_IER_1_IR11_POS 11
//! Field IR11 - Interrupt Enable XO/DCPM
#define ICU_PDI_REGISTERS_IM0_IER_1_IR11_MASK 0x800u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR11_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR11_ACTIVE 0x1

//! Field IR12 - Reserved
#define ICU_PDI_REGISTERS_IM0_IER_1_IR12_POS 12
//! Field IR12 - Reserved
#define ICU_PDI_REGISTERS_IM0_IER_1_IR12_MASK 0x1000u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR12_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_1_IR12_ACTIVE 0x1

//! @}

//! \defgroup ICU_PDI_REGISTERS_IM0_IER_2 Register ICU_PDI_REGISTERS_IM0_IER_2 - IM0 Interrupt Enable Register
//! @{

//! Register Offset (relative)
#define ICU_PDI_REGISTERS_IM0_IER_2 0xC
//! Register Offset (absolute) for 1st Instance ICU_PDI_REGISTERS
#define ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM0_IER_2 0x00D3CF0Cu

//! Register Reset Value
#define ICU_PDI_REGISTERS_IM0_IER_2_RST 0x00000000u

//! Field IR0 - Interrupt Enable GPHY
#define ICU_PDI_REGISTERS_IM0_IER_2_IR0_POS 0
//! Field IR0 - Interrupt Enable GPHY
#define ICU_PDI_REGISTERS_IM0_IER_2_IR0_MASK 0x1u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR0_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR0_ACTIVE 0x1

//! Field IR1 - Interrupt Enable PM
#define ICU_PDI_REGISTERS_IM0_IER_2_IR1_POS 1
//! Field IR1 - Interrupt Enable PM
#define ICU_PDI_REGISTERS_IM0_IER_2_IR1_MASK 0x2u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR1_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR1_ACTIVE 0x1

//! Field IR2 - Interrupt Enable MGE
#define ICU_PDI_REGISTERS_IM0_IER_2_IR2_POS 2
//! Field IR2 - Interrupt Enable MGE
#define ICU_PDI_REGISTERS_IM0_IER_2_IR2_MASK 0x4u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR2_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR2_ACTIVE 0x1

//! Field IR3 - Interrupt Enable External Interrupt 0
#define ICU_PDI_REGISTERS_IM0_IER_2_IR3_POS 3
//! Field IR3 - Interrupt Enable External Interrupt 0
#define ICU_PDI_REGISTERS_IM0_IER_2_IR3_MASK 0x8u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR3_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR3_ACTIVE 0x1

//! Field IR4 - Interrupt Enable External Interrupt 1
#define ICU_PDI_REGISTERS_IM0_IER_2_IR4_POS 4
//! Field IR4 - Interrupt Enable External Interrupt 1
#define ICU_PDI_REGISTERS_IM0_IER_2_IR4_MASK 0x10u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR4_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR4_ACTIVE 0x1

//! Field IR5 - Interrupt Enable SGMII
#define ICU_PDI_REGISTERS_IM0_IER_2_IR5_POS 5
//! Field IR5 - Interrupt Enable SGMII
#define ICU_PDI_REGISTERS_IM0_IER_2_IR5_MASK 0x20u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR5_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR5_ACTIVE 0x1

//! Field IR6 - Interrupt Enable FXVL IP
#define ICU_PDI_REGISTERS_IM0_IER_2_IR6_POS 6
//! Field IR6 - Interrupt Enable FXVL IP
#define ICU_PDI_REGISTERS_IM0_IER_2_IR6_MASK 0x40u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR6_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR6_ACTIVE 0x1

//! Field IR7 - Interrupt Enable Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_IER_2_IR7_POS 7
//! Field IR7 - Interrupt Enable Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_IER_2_IR7_MASK 0x80u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR7_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR7_ACTIVE 0x1

//! Field IR8 - Interrupt Enable CDB
#define ICU_PDI_REGISTERS_IM0_IER_2_IR8_POS 8
//! Field IR8 - Interrupt Enable CDB
#define ICU_PDI_REGISTERS_IM0_IER_2_IR8_MASK 0x100u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR8_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR8_ACTIVE 0x1

//! Field IR9 - Interrupt Enable DCDC
#define ICU_PDI_REGISTERS_IM0_IER_2_IR9_POS 9
//! Field IR9 - Interrupt Enable DCDC
#define ICU_PDI_REGISTERS_IM0_IER_2_IR9_MASK 0x200u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR9_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR9_ACTIVE 0x1

//! Field IR10 - Interrupt Enable Wake-Up
#define ICU_PDI_REGISTERS_IM0_IER_2_IR10_POS 10
//! Field IR10 - Interrupt Enable Wake-Up
#define ICU_PDI_REGISTERS_IM0_IER_2_IR10_MASK 0x400u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR10_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR10_ACTIVE 0x1

//! Field IR11 - Interrupt Enable XO/DCPM
#define ICU_PDI_REGISTERS_IM0_IER_2_IR11_POS 11
//! Field IR11 - Interrupt Enable XO/DCPM
#define ICU_PDI_REGISTERS_IM0_IER_2_IR11_MASK 0x800u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR11_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR11_ACTIVE 0x1

//! Field IR12 - Reserved
#define ICU_PDI_REGISTERS_IM0_IER_2_IR12_POS 12
//! Field IR12 - Reserved
#define ICU_PDI_REGISTERS_IM0_IER_2_IR12_MASK 0x1000u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR12_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_2_IR12_ACTIVE 0x1

//! @}

//! \defgroup ICU_PDI_REGISTERS_IM0_IER_3 Register ICU_PDI_REGISTERS_IM0_IER_3 - IM0 Interrupt Enable Register
//! @{

//! Register Offset (relative)
#define ICU_PDI_REGISTERS_IM0_IER_3 0x10
//! Register Offset (absolute) for 1st Instance ICU_PDI_REGISTERS
#define ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM0_IER_3 0x00D3CF10u

//! Register Reset Value
#define ICU_PDI_REGISTERS_IM0_IER_3_RST 0x00000000u

//! Field IR0 - Interrupt Enable GPHY
#define ICU_PDI_REGISTERS_IM0_IER_3_IR0_POS 0
//! Field IR0 - Interrupt Enable GPHY
#define ICU_PDI_REGISTERS_IM0_IER_3_IR0_MASK 0x1u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR0_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR0_ACTIVE 0x1

//! Field IR1 - Interrupt Enable PM
#define ICU_PDI_REGISTERS_IM0_IER_3_IR1_POS 1
//! Field IR1 - Interrupt Enable PM
#define ICU_PDI_REGISTERS_IM0_IER_3_IR1_MASK 0x2u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR1_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR1_ACTIVE 0x1

//! Field IR2 - Interrupt Enable MGE
#define ICU_PDI_REGISTERS_IM0_IER_3_IR2_POS 2
//! Field IR2 - Interrupt Enable MGE
#define ICU_PDI_REGISTERS_IM0_IER_3_IR2_MASK 0x4u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR2_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR2_ACTIVE 0x1

//! Field IR3 - Interrupt Enable External Interrupt 0
#define ICU_PDI_REGISTERS_IM0_IER_3_IR3_POS 3
//! Field IR3 - Interrupt Enable External Interrupt 0
#define ICU_PDI_REGISTERS_IM0_IER_3_IR3_MASK 0x8u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR3_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR3_ACTIVE 0x1

//! Field IR4 - Interrupt Enable External Interrupt 1
#define ICU_PDI_REGISTERS_IM0_IER_3_IR4_POS 4
//! Field IR4 - Interrupt Enable External Interrupt 1
#define ICU_PDI_REGISTERS_IM0_IER_3_IR4_MASK 0x10u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR4_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR4_ACTIVE 0x1

//! Field IR5 - Interrupt Enable SGMII
#define ICU_PDI_REGISTERS_IM0_IER_3_IR5_POS 5
//! Field IR5 - Interrupt Enable SGMII
#define ICU_PDI_REGISTERS_IM0_IER_3_IR5_MASK 0x20u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR5_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR5_ACTIVE 0x1

//! Field IR6 - Interrupt Enable FXVL IP
#define ICU_PDI_REGISTERS_IM0_IER_3_IR6_POS 6
//! Field IR6 - Interrupt Enable FXVL IP
#define ICU_PDI_REGISTERS_IM0_IER_3_IR6_MASK 0x40u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR6_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR6_ACTIVE 0x1

//! Field IR7 - Interrupt Enable Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_IER_3_IR7_POS 7
//! Field IR7 - Interrupt Enable Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_IER_3_IR7_MASK 0x80u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR7_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR7_ACTIVE 0x1

//! Field IR8 - Interrupt Enable CDB
#define ICU_PDI_REGISTERS_IM0_IER_3_IR8_POS 8
//! Field IR8 - Interrupt Enable CDB
#define ICU_PDI_REGISTERS_IM0_IER_3_IR8_MASK 0x100u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR8_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR8_ACTIVE 0x1

//! Field IR9 - Interrupt Enable DCDC
#define ICU_PDI_REGISTERS_IM0_IER_3_IR9_POS 9
//! Field IR9 - Interrupt Enable DCDC
#define ICU_PDI_REGISTERS_IM0_IER_3_IR9_MASK 0x200u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR9_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR9_ACTIVE 0x1

//! Field IR10 - Interrupt Enable Wake-Up
#define ICU_PDI_REGISTERS_IM0_IER_3_IR10_POS 10
//! Field IR10 - Interrupt Enable Wake-Up
#define ICU_PDI_REGISTERS_IM0_IER_3_IR10_MASK 0x400u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR10_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR10_ACTIVE 0x1

//! Field IR11 - Interrupt Enable XO/DCPM
#define ICU_PDI_REGISTERS_IM0_IER_3_IR11_POS 11
//! Field IR11 - Interrupt Enable XO/DCPM
#define ICU_PDI_REGISTERS_IM0_IER_3_IR11_MASK 0x800u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR11_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR11_ACTIVE 0x1

//! Field IR12 - Reserved
#define ICU_PDI_REGISTERS_IM0_IER_3_IR12_POS 12
//! Field IR12 - Reserved
#define ICU_PDI_REGISTERS_IM0_IER_3_IR12_MASK 0x1000u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR12_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_IER_3_IR12_ACTIVE 0x1

//! @}

//! \defgroup ICU_PDI_REGISTERS_IM0_EINT0_IER Register ICU_PDI_REGISTERS_IM0_EINT0_IER - IM0 EINT0 Interrupt Enable Register
//! @{

//! Register Offset (relative)
#define ICU_PDI_REGISTERS_IM0_EINT0_IER 0x14
//! Register Offset (absolute) for 1st Instance ICU_PDI_REGISTERS
#define ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM0_EINT0_IER 0x00D3CF14u

//! Register Reset Value
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_RST 0x00000000u

//! Field IR0 - Interrupt Enable GPHY
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR0_POS 0
//! Field IR0 - Interrupt Enable GPHY
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR0_MASK 0x1u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR0_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR0_ACTIVE 0x1

//! Field IR1 - Interrupt Enable PM
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR1_POS 1
//! Field IR1 - Interrupt Enable PM
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR1_MASK 0x2u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR1_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR1_ACTIVE 0x1

//! Field IR2 - Interrupt Enable MGE
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR2_POS 2
//! Field IR2 - Interrupt Enable MGE
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR2_MASK 0x4u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR2_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR2_ACTIVE 0x1

//! Field IR3 - Reserved
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR3_POS 3
//! Field IR3 - Reserved
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR3_MASK 0x8u

//! Field IR4 - Interrupt Enable External Interrupt 1
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR4_POS 4
//! Field IR4 - Interrupt Enable External Interrupt 1
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR4_MASK 0x10u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR4_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR4_ACTIVE 0x1

//! Field IR5 - Interrupt Enable SGMII
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR5_POS 5
//! Field IR5 - Interrupt Enable SGMII
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR5_MASK 0x20u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR5_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR5_ACTIVE 0x1

//! Field IR6 - Interrupt Enable FXVL IP
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR6_POS 6
//! Field IR6 - Interrupt Enable FXVL IP
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR6_MASK 0x40u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR6_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR6_ACTIVE 0x1

//! Field IR7 - Interrupt Enable Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR7_POS 7
//! Field IR7 - Interrupt Enable Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR7_MASK 0x80u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR7_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR7_ACTIVE 0x1

//! Field IR8 - Interrupt Enable CDB
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR8_POS 8
//! Field IR8 - Interrupt Enable CDB
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR8_MASK 0x100u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR8_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR8_ACTIVE 0x1

//! Field IR9 - Interrupt Enable DCDC
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR9_POS 9
//! Field IR9 - Interrupt Enable DCDC
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR9_MASK 0x200u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR9_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR9_ACTIVE 0x1

//! Field IR10 - Interrupt Enable Wake-Up
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR10_POS 10
//! Field IR10 - Interrupt Enable Wake-Up
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR10_MASK 0x400u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR10_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR10_ACTIVE 0x1

//! Field IR11 - Interrupt Enable XO/DCPM
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR11_POS 11
//! Field IR11 - Interrupt Enable XO/DCPM
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR11_MASK 0x800u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR11_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR11_ACTIVE 0x1

//! Field IR12 - Interrupt Enable Timestamp
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR12_POS 12
//! Field IR12 - Interrupt Enable Timestamp
#define ICU_PDI_REGISTERS_IM0_EINT0_IER_IR12_MASK 0x1000u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR12_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT0_IER_IR12_ACTIVE 0x1

//! @}

//! \defgroup ICU_PDI_REGISTERS_IM0_EINT1_IER Register ICU_PDI_REGISTERS_IM0_EINT1_IER - IM0 EINT1 Interrupt Enable Register
//! @{

//! Register Offset (relative)
#define ICU_PDI_REGISTERS_IM0_EINT1_IER 0x18
//! Register Offset (absolute) for 1st Instance ICU_PDI_REGISTERS
#define ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM0_EINT1_IER 0x00D3CF18u

//! Register Reset Value
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_RST 0x00000000u

//! Field IR0 - Interrupt Enable GPHY
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR0_POS 0
//! Field IR0 - Interrupt Enable GPHY
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR0_MASK 0x1u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR0_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR0_ACTIVE 0x1

//! Field IR1 - Interrupt Enable PM
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR1_POS 1
//! Field IR1 - Interrupt Enable PM
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR1_MASK 0x2u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR1_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR1_ACTIVE 0x1

//! Field IR2 - Interrupt Enable MGE
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR2_POS 2
//! Field IR2 - Interrupt Enable MGE
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR2_MASK 0x4u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR2_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR2_ACTIVE 0x1

//! Field IR3 - Interrupt Enable External Interrupt 0
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR3_POS 3
//! Field IR3 - Interrupt Enable External Interrupt 0
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR3_MASK 0x8u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR3_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR3_ACTIVE 0x1

//! Field IR4 - Reserved
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR4_POS 4
//! Field IR4 - Reserved
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR4_MASK 0x10u

//! Field IR5 - Interrupt Enable SGMII
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR5_POS 5
//! Field IR5 - Interrupt Enable SGMII
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR5_MASK 0x20u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR5_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR5_ACTIVE 0x1

//! Field IR6 - Interrupt Enable FXVL IP
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR6_POS 6
//! Field IR6 - Interrupt Enable FXVL IP
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR6_MASK 0x40u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR6_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR6_ACTIVE 0x1

//! Field IR7 - Interrupt Enable Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR7_POS 7
//! Field IR7 - Interrupt Enable Temperature Sensor
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR7_MASK 0x80u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR7_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR7_ACTIVE 0x1

//! Field IR8 - Interrupt Enable CDB
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR8_POS 8
//! Field IR8 - Interrupt Enable CDB
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR8_MASK 0x100u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR8_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR8_ACTIVE 0x1

//! Field IR9 - Interrupt Enable DCDC
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR9_POS 9
//! Field IR9 - Interrupt Enable DCDC
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR9_MASK 0x200u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR9_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR9_ACTIVE 0x1

//! Field IR10 - Interrupt Enable Wake-Up
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR10_POS 10
//! Field IR10 - Interrupt Enable Wake-Up
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR10_MASK 0x400u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR10_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR10_ACTIVE 0x1

//! Field IR11 - Interrupt Enable XO/DCPM
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR11_POS 11
//! Field IR11 - Interrupt Enable XO/DCPM
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR11_MASK 0x800u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR11_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR11_ACTIVE 0x1

//! Field IR12 - Interrupt Enable Timestamp
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR12_POS 12
//! Field IR12 - Interrupt Enable Timestamp
#define ICU_PDI_REGISTERS_IM0_EINT1_IER_IR12_MASK 0x1000u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR12_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM0_EINT1_IER_IR12_ACTIVE 0x1

//! @}

//! \defgroup ICU_PDI_REGISTERS_EIU_EXIN_CONF Register ICU_PDI_REGISTERS_EIU_EXIN_CONF - EIU External Interrupt Controller Register
//! @{

//! Register Offset (relative)
#define ICU_PDI_REGISTERS_EIU_EXIN_CONF 0x1C
//! Register Offset (absolute) for 1st Instance ICU_PDI_REGISTERS
#define ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_EIU_EXIN_CONF 0x00D3CF1Cu

//! Register Reset Value
#define ICU_PDI_REGISTERS_EIU_EXIN_CONF_RST 0x00000000u

//! Field EIN0 - External Interrupt Input EINT0
#define ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN0_POS 0
//! Field EIN0 - External Interrupt Input EINT0
#define ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN0_MASK 0x7u
//! Constant EDGELEVEL - Edge/Level Disable
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN0_EDGELEVEL 0x0
//! Constant RISING_EDGE - Rising Edge
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN0_RISING_EDGE 0x1
//! Constant FALLING_EDGE - Falling Edge
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN0_FALLING_EDGE 0x2
//! Constant RISINGFALLING_EDGE - Rising/Falling Edge
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN0_RISINGFALLING_EDGE 0x3
//! Constant RESERVED - Reserved
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN0_RESERVED 0x4
//! Constant HIGH_LEVEL - High Level
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN0_HIGH_LEVEL 0x5
//! Constant LOW_LEVEL - Low Level
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN0_LOW_LEVEL 0x6
//! Constant RES - Res
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN0_RES 0x7

//! Field EIN1 - External Interrupt Input EINT1
#define ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN1_POS 4
//! Field EIN1 - External Interrupt Input EINT1
#define ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN1_MASK 0x70u
//! Constant EDGELEVEL - Edge/Level Disable
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN1_EDGELEVEL 0x0
//! Constant RISING_EDGE - Rising Edge
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN1_RISING_EDGE 0x1
//! Constant FALLING_EDGE - Falling Edge
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN1_FALLING_EDGE 0x2
//! Constant RISINGFALLING_EDGE - Rising/Falling Edge
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN1_RISINGFALLING_EDGE 0x3
//! Constant RESERVED - Reserved
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN1_RESERVED 0x4
//! Constant HIGH_LEVEL - High Level
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN1_HIGH_LEVEL 0x5
//! Constant LOW_LEVEL - Low Level
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN1_LOW_LEVEL 0x6
//! Constant RES - Res
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN1_RES 0x7

//! Field EOUT0 - External Interrupt Output EINT0
#define ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT0_POS 8
//! Field EOUT0 - External Interrupt Output EINT0
#define ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT0_MASK 0x100u
//! Constant HIGH_LEVEL - High Level
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT0_HIGH_LEVEL 0x0
//! Constant LOW_LEVEL - Low Level
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT0_LOW_LEVEL 0x1

//! Field EOUT1 - External Interrupt Output EINT1
#define ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT1_POS 9
//! Field EOUT1 - External Interrupt Output EINT1
#define ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT1_MASK 0x200u
//! Constant HIGH_LEVEL - High Level
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT1_HIGH_LEVEL 0x0
//! Constant LOW_LEVEL - Low Level
#define CONST_ICU_PDI_REGISTERS_EIU_EXIN_CONF_EOUT1_LOW_LEVEL 0x1

//! @}

//! \defgroup ICU_PDI_REGISTERS_IM1_ISR Register ICU_PDI_REGISTERS_IM1_ISR - IM1 Interrupt Status Register
//! @{

//! Register Offset (relative)
#define ICU_PDI_REGISTERS_IM1_ISR 0x20
//! Register Offset (absolute) for 1st Instance ICU_PDI_REGISTERS
#define ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM1_ISR 0x00D3CF20u

//! Register Reset Value
#define ICU_PDI_REGISTERS_IM1_ISR_RST 0x00000000u

//! Field IR0 - Status of Interrupt Request SPD
#define ICU_PDI_REGISTERS_IM1_ISR_IR0_POS 0
//! Field IR0 - Status of Interrupt Request SPD
#define ICU_PDI_REGISTERS_IM1_ISR_IR0_MASK 0x1u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR0_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR0_ACTIVE 0x1

//! Field IR1 - Status of Interrupt Request SPD B2B
#define ICU_PDI_REGISTERS_IM1_ISR_IR1_POS 1
//! Field IR1 - Status of Interrupt Request SPD B2B
#define ICU_PDI_REGISTERS_IM1_ISR_IR1_MASK 0x2u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR1_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR1_ACTIVE 0x1

//! Field IR2 - Status of Interrupt Request Restart ANEG
#define ICU_PDI_REGISTERS_IM1_ISR_IR2_POS 2
//! Field IR2 - Status of Interrupt Request Restart ANEG
#define ICU_PDI_REGISTERS_IM1_ISR_IR2_MASK 0x4u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR2_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR2_ACTIVE 0x1

//! Field IR3 - Status of Interrupt Request Disable 2.5G
#define ICU_PDI_REGISTERS_IM1_ISR_IR3_POS 3
//! Field IR3 - Status of Interrupt Request Disable 2.5G
#define ICU_PDI_REGISTERS_IM1_ISR_IR3_MASK 0x8u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR3_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR3_ACTIVE 0x1

//! Field IR4 - Status of Interrupt Request Disable 1G
#define ICU_PDI_REGISTERS_IM1_ISR_IR4_POS 4
//! Field IR4 - Status of Interrupt Request Disable 1G
#define ICU_PDI_REGISTERS_IM1_ISR_IR4_MASK 0x10u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR4_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR4_ACTIVE 0x1

//! Field IR5 - Status of Interrupt Request Disable 100M
#define ICU_PDI_REGISTERS_IM1_ISR_IR5_POS 5
//! Field IR5 - Status of Interrupt Request Disable 100M
#define ICU_PDI_REGISTERS_IM1_ISR_IR5_MASK 0x20u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR5_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR5_ACTIVE 0x1

//! Field IR6 - Status of Interrupt Request Link Disconnect
#define ICU_PDI_REGISTERS_IM1_ISR_IR6_POS 6
//! Field IR6 - Status of Interrupt Request Link Disconnect
#define ICU_PDI_REGISTERS_IM1_ISR_IR6_MASK 0x40u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR6_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR6_ACTIVE 0x1

//! Field IR7 - Status of Interrupt Request MDI Flip
#define ICU_PDI_REGISTERS_IM1_ISR_IR7_POS 7
//! Field IR7 - Status of Interrupt Request MDI Flip
#define ICU_PDI_REGISTERS_IM1_ISR_IR7_MASK 0x80u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR7_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR7_ACTIVE 0x1

//! Field IR8 - Status of Interrupt Request 10BT EEE
#define ICU_PDI_REGISTERS_IM1_ISR_IR8_POS 8
//! Field IR8 - Status of Interrupt Request 10BT EEE
#define ICU_PDI_REGISTERS_IM1_ISR_IR8_MASK 0x100u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR8_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR8_ACTIVE 0x1

//! Field IR9 - Status of Interrupt Request 100BT EEE
#define ICU_PDI_REGISTERS_IM1_ISR_IR9_POS 9
//! Field IR9 - Status of Interrupt Request 100BT EEE
#define ICU_PDI_REGISTERS_IM1_ISR_IR9_MASK 0x200u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR9_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR9_ACTIVE 0x1

//! Field IR10 - Status of Interrupt Request 1000BT EEE
#define ICU_PDI_REGISTERS_IM1_ISR_IR10_POS 10
//! Field IR10 - Status of Interrupt Request 1000BT EEE
#define ICU_PDI_REGISTERS_IM1_ISR_IR10_MASK 0x400u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR10_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR10_ACTIVE 0x1

//! Field IR11 - Status of Interrupt Request 2500BT EEE
#define ICU_PDI_REGISTERS_IM1_ISR_IR11_POS 11
//! Field IR11 - Status of Interrupt Request 2500BT EEE
#define ICU_PDI_REGISTERS_IM1_ISR_IR11_MASK 0x800u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR11_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR11_ACTIVE 0x1

//! Field IR12 - Status of Interrupt Request PHY Reset
#define ICU_PDI_REGISTERS_IM1_ISR_IR12_POS 12
//! Field IR12 - Status of Interrupt Request PHY Reset
#define ICU_PDI_REGISTERS_IM1_ISR_IR12_MASK 0x1000u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR12_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR12_ACTIVE 0x1

//! Field IR13 - Status of Interrupt Request PHY Power Down
#define ICU_PDI_REGISTERS_IM1_ISR_IR13_POS 13
//! Field IR13 - Status of Interrupt Request PHY Power Down
#define ICU_PDI_REGISTERS_IM1_ISR_IR13_MASK 0x2000u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR13_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_ISR_IR13_ACTIVE 0x1

//! @}

//! \defgroup ICU_PDI_REGISTERS_IM1_IER Register ICU_PDI_REGISTERS_IM1_IER - IM1 Interrupt Enable Register
//! @{

//! Register Offset (relative)
#define ICU_PDI_REGISTERS_IM1_IER 0x24
//! Register Offset (absolute) for 1st Instance ICU_PDI_REGISTERS
#define ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM1_IER 0x00D3CF24u

//! Register Reset Value
#define ICU_PDI_REGISTERS_IM1_IER_RST 0x00000000u

//! Field IR0 - Interrupt Enable SPD
#define ICU_PDI_REGISTERS_IM1_IER_IR0_POS 0
//! Field IR0 - Interrupt Enable SPD
#define ICU_PDI_REGISTERS_IM1_IER_IR0_MASK 0x1u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR0_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR0_ACTIVE 0x1

//! Field IR1 - Interrupt Enable SPD B2B
#define ICU_PDI_REGISTERS_IM1_IER_IR1_POS 1
//! Field IR1 - Interrupt Enable SPD B2B
#define ICU_PDI_REGISTERS_IM1_IER_IR1_MASK 0x2u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR1_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR1_ACTIVE 0x1

//! Field IR2 - Interrupt Enable Restart ANEG
#define ICU_PDI_REGISTERS_IM1_IER_IR2_POS 2
//! Field IR2 - Interrupt Enable Restart ANEG
#define ICU_PDI_REGISTERS_IM1_IER_IR2_MASK 0x4u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR2_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR2_ACTIVE 0x1

//! Field IR3 - Interrupt Enable Disable 2.5G
#define ICU_PDI_REGISTERS_IM1_IER_IR3_POS 3
//! Field IR3 - Interrupt Enable Disable 2.5G
#define ICU_PDI_REGISTERS_IM1_IER_IR3_MASK 0x8u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR3_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR3_ACTIVE 0x1

//! Field IR4 - Interrupt Enable Disable 1G
#define ICU_PDI_REGISTERS_IM1_IER_IR4_POS 4
//! Field IR4 - Interrupt Enable Disable 1G
#define ICU_PDI_REGISTERS_IM1_IER_IR4_MASK 0x10u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR4_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR4_ACTIVE 0x1

//! Field IR5 - Interrupt Enable Disable 100M
#define ICU_PDI_REGISTERS_IM1_IER_IR5_POS 5
//! Field IR5 - Interrupt Enable Disable 100M
#define ICU_PDI_REGISTERS_IM1_IER_IR5_MASK 0x20u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR5_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR5_ACTIVE 0x1

//! Field IR6 - Interrupt Enable Link Disconnect
#define ICU_PDI_REGISTERS_IM1_IER_IR6_POS 6
//! Field IR6 - Interrupt Enable Link Disconnect
#define ICU_PDI_REGISTERS_IM1_IER_IR6_MASK 0x40u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR6_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR6_ACTIVE 0x1

//! Field IR7 - Interrupt Enable MDI Flip
#define ICU_PDI_REGISTERS_IM1_IER_IR7_POS 7
//! Field IR7 - Interrupt Enable MDI Flip
#define ICU_PDI_REGISTERS_IM1_IER_IR7_MASK 0x80u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR7_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR7_ACTIVE 0x1

//! Field IR8 - Interrupt Enable 10BT EEE
#define ICU_PDI_REGISTERS_IM1_IER_IR8_POS 8
//! Field IR8 - Interrupt Enable 10BT EEE
#define ICU_PDI_REGISTERS_IM1_IER_IR8_MASK 0x100u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR8_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR8_ACTIVE 0x1

//! Field IR9 - Interrupt Enable 100BT EEE
#define ICU_PDI_REGISTERS_IM1_IER_IR9_POS 9
//! Field IR9 - Interrupt Enable 100BT EEE
#define ICU_PDI_REGISTERS_IM1_IER_IR9_MASK 0x200u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR9_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR9_ACTIVE 0x1

//! Field IR10 - Interrupt Enable 1000BT EEE
#define ICU_PDI_REGISTERS_IM1_IER_IR10_POS 10
//! Field IR10 - Interrupt Enable 1000BT EEE
#define ICU_PDI_REGISTERS_IM1_IER_IR10_MASK 0x400u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR10_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR10_ACTIVE 0x1

//! Field IR11 - Interrupt Enable 2500BT EEE
#define ICU_PDI_REGISTERS_IM1_IER_IR11_POS 11
//! Field IR11 - Interrupt Enable 2500BT EEE
#define ICU_PDI_REGISTERS_IM1_IER_IR11_MASK 0x800u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR11_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR11_ACTIVE 0x1

//! Field IR12 - Interrupt Enable PHY Reset
#define ICU_PDI_REGISTERS_IM1_IER_IR12_POS 12
//! Field IR12 - Interrupt Enable PHY Reset
#define ICU_PDI_REGISTERS_IM1_IER_IR12_MASK 0x1000u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR12_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR12_ACTIVE 0x1

//! Field IR13 - Interrupt Enable PHY Power Down
#define ICU_PDI_REGISTERS_IM1_IER_IR13_POS 13
//! Field IR13 - Interrupt Enable PHY Power Down
#define ICU_PDI_REGISTERS_IM1_IER_IR13_MASK 0x2000u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR13_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM1_IER_IR13_ACTIVE 0x1

//! @}

//! \defgroup ICU_PDI_REGISTERS_IM2_ISR Register ICU_PDI_REGISTERS_IM2_ISR - IM2 Interrupt Status Register
//! @{

//! Register Offset (relative)
#define ICU_PDI_REGISTERS_IM2_ISR 0x28
//! Register Offset (absolute) for 1st Instance ICU_PDI_REGISTERS
#define ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM2_ISR 0x00D3CF28u

//! Register Reset Value
#define ICU_PDI_REGISTERS_IM2_ISR_RST 0x00000000u

//! Field IR0 - Status of Interrupt Request MRI TS
#define ICU_PDI_REGISTERS_IM2_ISR_IR0_POS 0
//! Field IR0 - Status of Interrupt Request MRI TS
#define ICU_PDI_REGISTERS_IM2_ISR_IR0_MASK 0x1u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM2_ISR_IR0_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM2_ISR_IR0_ACTIVE 0x1

//! Field IR1 - Status of Interrupt Request LPI
#define ICU_PDI_REGISTERS_IM2_ISR_IR1_POS 1
//! Field IR1 - Status of Interrupt Request LPI
#define ICU_PDI_REGISTERS_IM2_ISR_IR1_MASK 0x2u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM2_ISR_IR1_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM2_ISR_IR1_ACTIVE 0x1

//! Field IR2 - Status of Interrupt Request MCI
#define ICU_PDI_REGISTERS_IM2_ISR_IR2_POS 2
//! Field IR2 - Status of Interrupt Request MCI
#define ICU_PDI_REGISTERS_IM2_ISR_IR2_MASK 0x4u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM2_ISR_IR2_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM2_ISR_IR2_ACTIVE 0x1

//! Field IR3 - Packet Manager Timestamp FIFO full
#define ICU_PDI_REGISTERS_IM2_ISR_IR3_POS 3
//! Field IR3 - Packet Manager Timestamp FIFO full
#define ICU_PDI_REGISTERS_IM2_ISR_IR3_MASK 0x8u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM2_ISR_IR3_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM2_ISR_IR3_ACTIVE 0x1

//! Field IR4 - MACsec Interrupt
#define ICU_PDI_REGISTERS_IM2_ISR_IR4_POS 4
//! Field IR4 - MACsec Interrupt
#define ICU_PDI_REGISTERS_IM2_ISR_IR4_MASK 0x10u
//! Constant INACTIVE - Inactive
#define CONST_ICU_PDI_REGISTERS_IM2_ISR_IR4_INACTIVE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM2_ISR_IR4_ACTIVE 0x1

//! @}

//! \defgroup ICU_PDI_REGISTERS_IM2_IER Register ICU_PDI_REGISTERS_IM2_IER - IM2 Interrupt Enable Register
//! @{

//! Register Offset (relative)
#define ICU_PDI_REGISTERS_IM2_IER 0x2C
//! Register Offset (absolute) for 1st Instance ICU_PDI_REGISTERS
#define ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM2_IER 0x00D3CF2Cu

//! Register Reset Value
#define ICU_PDI_REGISTERS_IM2_IER_RST 0x00000000u

//! Field IR0 - Interrupt Enable MRI TS
#define ICU_PDI_REGISTERS_IM2_IER_IR0_POS 0
//! Field IR0 - Interrupt Enable MRI TS
#define ICU_PDI_REGISTERS_IM2_IER_IR0_MASK 0x1u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM2_IER_IR0_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM2_IER_IR0_ACTIVE 0x1

//! Field IR1 - Interrupt Enable LPI
#define ICU_PDI_REGISTERS_IM2_IER_IR1_POS 1
//! Field IR1 - Interrupt Enable LPI
#define ICU_PDI_REGISTERS_IM2_IER_IR1_MASK 0x2u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM2_IER_IR1_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM2_IER_IR1_ACTIVE 0x1

//! Field IR2 - Interrupt Enable MCI
#define ICU_PDI_REGISTERS_IM2_IER_IR2_POS 2
//! Field IR2 - Interrupt Enable MCI
#define ICU_PDI_REGISTERS_IM2_IER_IR2_MASK 0x4u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM2_IER_IR2_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM2_IER_IR2_ACTIVE 0x1

//! Field IR3 - Packet Manager Timestamp FIFO full
#define ICU_PDI_REGISTERS_IM2_IER_IR3_POS 3
//! Field IR3 - Packet Manager Timestamp FIFO full
#define ICU_PDI_REGISTERS_IM2_IER_IR3_MASK 0x8u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM2_IER_IR3_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM2_IER_IR3_ACTIVE 0x1

//! Field IR4 - MACsec Interrupt
#define ICU_PDI_REGISTERS_IM2_IER_IR4_POS 4
//! Field IR4 - MACsec Interrupt
#define ICU_PDI_REGISTERS_IM2_IER_IR4_MASK 0x10u
//! Constant DISABLE - Disable
#define CONST_ICU_PDI_REGISTERS_IM2_IER_IR4_DISABLE 0x0
//! Constant ACTIVE - Active
#define CONST_ICU_PDI_REGISTERS_IM2_IER_IR4_ACTIVE 0x1

//! @}

//! @}

#endif
