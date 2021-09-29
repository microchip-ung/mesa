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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/GPHYDCPM_FCSI.xml
// Register File Name  : GPHYDCPM_FCSI
// Register File Title : DCPM FCSI-Interface
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _GPHYDCPM_FCSI_H
#define _GPHYDCPM_FCSI_H

//! \defgroup GPHYDCPM_FCSI Register File GPHYDCPM_FCSI - DCPM FCSI-Interface
//! @{

//! Base Address of GPHYDCPM_FCSI
#define GPHYDCPM_FCSI_MODULE_BASE 0x00D29880u

//! \defgroup GPHYDCPM_FCSI_VREGCFG Register GPHYDCPM_FCSI_VREGCFG - DCPM 0.9V Voltage regulator configuration register
//! @{

//! Register Offset (relative)
#define GPHYDCPM_FCSI_VREGCFG 0x0
//! Register Offset (absolute) for 1st Instance GPHYDCPM_FCSI
#define GPHYDCPM_FCSI_GPHYDCPM_FCSI_VREGCFG 0x00D29880u

//! Register Reset Value
#define GPHYDCPM_FCSI_VREGCFG_RST 0x00000200u

//! Field RES0 - Reserved ReadWrite
#define GPHYDCPM_FCSI_VREGCFG_RES0_POS 0
//! Field RES0 - Reserved ReadWrite
#define GPHYDCPM_FCSI_VREGCFG_RES0_MASK 0xFFu

//! Field VREGPROG0V9 - 0.9V Vreg Voltage Programming
#define GPHYDCPM_FCSI_VREGCFG_VREGPROG0V9_POS 8
//! Field VREGPROG0V9 - 0.9V Vreg Voltage Programming
#define GPHYDCPM_FCSI_VREGCFG_VREGPROG0V9_MASK 0x700u
//! Constant V0V900 - 0.9 V REG. OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_VREGCFG_VREGPROG0V9_V0V900 0x0
//! Constant V0V915 - 0.915 V REG. OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_VREGCFG_VREGPROG0V9_V0V915 0x1
//! Constant V0V930 - 0.93 V REG. OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_VREGCFG_VREGPROG0V9_V0V930 0x2
//! Constant V0V945 - 0.945 V REG. OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_VREGCFG_VREGPROG0V9_V0V945 0x3
//! Constant V0V840 - 0.84 V REG. OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_VREGCFG_VREGPROG0V9_V0V840 0x4
//! Constant V0V855 - 0.855 V REG. OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_VREGCFG_VREGPROG0V9_V0V855 0x5
//! Constant V0V870 - 0.87 V REG. OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_VREGCFG_VREGPROG0V9_V0V870 0x6
//! Constant V0V885 - 0.885 V REG. OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_VREGCFG_VREGPROG0V9_V0V885 0x7

//! Field RES1 - Reserved ReadWrite
#define GPHYDCPM_FCSI_VREGCFG_RES1_POS 11
//! Field RES1 - Reserved ReadWrite
#define GPHYDCPM_FCSI_VREGCFG_RES1_MASK 0xF800u

//! @}

//! \defgroup GPHYDCPM_FCSI_OBSDCPM Register GPHYDCPM_FCSI_OBSDCPM - Configuration Register for the Observation
//! @{

//! Register Offset (relative)
#define GPHYDCPM_FCSI_OBSDCPM 0x4
//! Register Offset (absolute) for 1st Instance GPHYDCPM_FCSI
#define GPHYDCPM_FCSI_GPHYDCPM_FCSI_OBSDCPM 0x00D29884u

//! Register Reset Value
#define GPHYDCPM_FCSI_OBSDCPM_RST 0x00000000u

//! Field VREGSEL - Select the DCPM 1V8 voltage for Observation tests
#define GPHYDCPM_FCSI_OBSDCPM_VREGSEL_POS 0
//! Field VREGSEL - Select the DCPM 1V8 voltage for Observation tests
#define GPHYDCPM_FCSI_OBSDCPM_VREGSEL_MASK 0x1u
//! Constant DISABLE - FUNCTION IS DISABLED
#define CONST_GPHYDCPM_FCSI_OBSDCPM_VREGSEL_DISABLE 0x0
//! Constant ENABLE - FUNCTION IS ENABLED
#define CONST_GPHYDCPM_FCSI_OBSDCPM_VREGSEL_ENABLE 0x1

//! Field VDDSEL - Select the DCPM VDD 0V93 always on domain for Observation tests
#define GPHYDCPM_FCSI_OBSDCPM_VDDSEL_POS 1
//! Field VDDSEL - Select the DCPM VDD 0V93 always on domain for Observation tests
#define GPHYDCPM_FCSI_OBSDCPM_VDDSEL_MASK 0x2u
//! Constant DISABLE - FUNCTION IS DISABLED
#define CONST_GPHYDCPM_FCSI_OBSDCPM_VDDSEL_DISABLE 0x0
//! Constant ENABLE - FUNCTION IS ENABLED
#define CONST_GPHYDCPM_FCSI_OBSDCPM_VDDSEL_ENABLE 0x1

//! Field VREFSEL - Select the VREF0V5 for Observation tests
#define GPHYDCPM_FCSI_OBSDCPM_VREFSEL_POS 2
//! Field VREFSEL - Select the VREF0V5 for Observation tests
#define GPHYDCPM_FCSI_OBSDCPM_VREFSEL_MASK 0x4u
//! Constant DISABLE - FUNCTION IS DISABLED
#define CONST_GPHYDCPM_FCSI_OBSDCPM_VREFSEL_DISABLE 0x0
//! Constant ENABLE - FUNCTION IS ENABLED
#define CONST_GPHYDCPM_FCSI_OBSDCPM_VREFSEL_ENABLE 0x1

//! Field ICONSTSEL - Select the ICONST 5uA current for Observation tests (the Direct path must be
#define GPHYDCPM_FCSI_OBSDCPM_ICONSTSEL_POS 3
//! Field ICONSTSEL - Select the ICONST 5uA current for Observation tests (the Direct path must be
#define GPHYDCPM_FCSI_OBSDCPM_ICONSTSEL_MASK 0x8u
//! Constant DISABLE - FUNCTION IS DISABLED
#define CONST_GPHYDCPM_FCSI_OBSDCPM_ICONSTSEL_DISABLE 0x0
//! Constant ENABLE - FUNCTION IS ENABLED
#define CONST_GPHYDCPM_FCSI_OBSDCPM_ICONSTSEL_ENABLE 0x1

//! Field RES0 - Reserved ReadWrite
#define GPHYDCPM_FCSI_OBSDCPM_RES0_POS 4
//! Field RES0 - Reserved ReadWrite
#define GPHYDCPM_FCSI_OBSDCPM_RES0_MASK 0xFFF0u

//! @}

//! \defgroup GPHYDCPM_FCSI_BIASCFG Register GPHYDCPM_FCSI_BIASCFG - Biasing configuration register
//! @{

//! Register Offset (relative)
#define GPHYDCPM_FCSI_BIASCFG 0x8
//! Register Offset (absolute) for 1st Instance GPHYDCPM_FCSI
#define GPHYDCPM_FCSI_GPHYDCPM_FCSI_BIASCFG 0x00D29888u

//! Register Reset Value
#define GPHYDCPM_FCSI_BIASCFG_RST 0x00000402u

//! Field RES0 - Reserved ReadWrite
#define GPHYDCPM_FCSI_BIASCFG_RES0_POS 0
//! Field RES0 - Reserved ReadWrite
#define GPHYDCPM_FCSI_BIASCFG_RES0_MASK 0x1u

//! Field ICONSTEN - Constant Current Enable
#define GPHYDCPM_FCSI_BIASCFG_ICONSTEN_POS 1
//! Field ICONSTEN - Constant Current Enable
#define GPHYDCPM_FCSI_BIASCFG_ICONSTEN_MASK 0x2u
//! Constant DISABLE - FUNCTION IS DISABLED
#define CONST_GPHYDCPM_FCSI_BIASCFG_ICONSTEN_DISABLE 0x0
//! Constant ENABLE - FUNCTION IS ENABLED
#define CONST_GPHYDCPM_FCSI_BIASCFG_ICONSTEN_ENABLE 0x1

//! Field RES1 - Reserved ReadWrite
#define GPHYDCPM_FCSI_BIASCFG_RES1_POS 2
//! Field RES1 - Reserved ReadWrite
#define GPHYDCPM_FCSI_BIASCFG_RES1_MASK 0x4u

//! Field VREFTRIM - Vref Trimming
#define GPHYDCPM_FCSI_BIASCFG_VREFTRIM_POS 3
//! Field VREFTRIM - Vref Trimming
#define GPHYDCPM_FCSI_BIASCFG_VREFTRIM_MASK 0x78u
//! Constant V449MV6 - 449.6 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V449MV6 0x0
//! Constant V448MV2 - 448.2 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V448MV2 0x1
//! Constant V446MV8 - 446.8 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V446MV8 0x2
//! Constant V445MV4 - 445.4 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V445MV4 0x3
//! Constant V444MV0 - 444.0 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V444MV0 0x4
//! Constant V442MV6 - 442.6 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V442MV6 0x5
//! Constant V441MV2 - 441.2 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V441MV2 0x6
//! Constant V439MV8 - 439.8 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V439MV8 0x7
//! Constant V460MV8 - 460.8 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V460MV8 0x8
//! Constant V459MV4 - 459.4 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V459MV4 0x9
//! Constant V458MV0 - 458.0 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V458MV0 0xA
//! Constant V456MV6 - 456.6 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V456MV6 0xB
//! Constant V455MV2 - 455.2 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V455MV2 0xC
//! Constant V453MV8 - 453.8 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V453MV8 0xD
//! Constant V452MV4 - 452.4 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V452MV4 0xE
//! Constant V451MV0 - 451.0 MV VREF OUTPUT VOLTAGE
#define CONST_GPHYDCPM_FCSI_BIASCFG_VREFTRIM_V451MV0 0xF

//! Field ICONSTPROG - Iconst Programming
#define GPHYDCPM_FCSI_BIASCFG_ICONSTPROG_POS 7
//! Field ICONSTPROG - Iconst Programming
#define GPHYDCPM_FCSI_BIASCFG_ICONSTPROG_MASK 0x780u

//! Field RES2 - Reserved ReadWrite
#define GPHYDCPM_FCSI_BIASCFG_RES2_POS 11
//! Field RES2 - Reserved ReadWrite
#define GPHYDCPM_FCSI_BIASCFG_RES2_MASK 0xF800u

//! @}

//! \defgroup GPHYDCPM_FCSI_VERSION Register GPHYDCPM_FCSI_VERSION - Version Register
//! @{

//! Register Offset (relative)
#define GPHYDCPM_FCSI_VERSION 0xC
//! Register Offset (absolute) for 1st Instance GPHYDCPM_FCSI
#define GPHYDCPM_FCSI_GPHYDCPM_FCSI_VERSION 0x00D2988Cu

//! Register Reset Value
#define GPHYDCPM_FCSI_VERSION_RST 0x00000100u

//! Field MIN - Minor Version
#define GPHYDCPM_FCSI_VERSION_MIN_POS 0
//! Field MIN - Minor Version
#define GPHYDCPM_FCSI_VERSION_MIN_MASK 0xFFu

//! Field MAJ - Major Version
#define GPHYDCPM_FCSI_VERSION_MAJ_POS 8
//! Field MAJ - Major Version
#define GPHYDCPM_FCSI_VERSION_MAJ_MASK 0xFF00u

//! @}

//! @}

#endif
