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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/EIPI_EIP_160s_i_32_SAM_enable_ctrl_def.xml
// Register File Name  : EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL
// Register File Title : EIPI EIP_160s_i_32_SAM_enable_ctrl
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL_H
#define _EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL_H

//! \defgroup EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL Register File EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL - EIPI EIP_160s_i_32_SAM_enable_ctrl
//! @{

//! Base Address of EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL
#define EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL_MODULE_BASE 0x00B06000u

//! \defgroup EIPI_SAM_ENTRY_ENABLE1 Register EIPI_SAM_ENTRY_ENABLE1 - EIPI SAM ENTRY ENABLE1
//! @{

//! Register Offset (relative)
#define EIPI_SAM_ENTRY_ENABLE1 0x0
//! Register Offset (absolute) for 1st Instance EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL
#define EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL_EIPI_SAM_ENTRY_ENABLE1 0x00B06000u

//! Register Reset Value
#define EIPI_SAM_ENTRY_ENABLE1_RST 0x00000000u

//! Field ENABLE_31_0 - No Content.
#define EIPI_SAM_ENTRY_ENABLE1_ENABLE_31_0_POS 0
//! Field ENABLE_31_0 - No Content.
#define EIPI_SAM_ENTRY_ENABLE1_ENABLE_31_0_MASK 0xFFFFFFFFu

//! @}

//! \defgroup EIPI_SAM_ENTRY_TOGGLE1 Register EIPI_SAM_ENTRY_TOGGLE1 - EIPI SAM ENTRY TOGGLE1
//! @{

//! Register Offset (relative)
#define EIPI_SAM_ENTRY_TOGGLE1 0x40
//! Register Offset (absolute) for 1st Instance EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL
#define EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL_EIPI_SAM_ENTRY_TOGGLE1 0x00B06040u

//! Register Reset Value
#define EIPI_SAM_ENTRY_TOGGLE1_RST 0x00000000u

//! Field TOGGLE_31_0 - No Content.
#define EIPI_SAM_ENTRY_TOGGLE1_TOGGLE_31_0_POS 0
//! Field TOGGLE_31_0 - No Content.
#define EIPI_SAM_ENTRY_TOGGLE1_TOGGLE_31_0_MASK 0xFFFFFFFFu

//! @}

//! \defgroup EIPI_SAM_ENTRY_SET1 Register EIPI_SAM_ENTRY_SET1 - EIPI SAM ENTRY SET1
//! @{

//! Register Offset (relative)
#define EIPI_SAM_ENTRY_SET1 0x80
//! Register Offset (absolute) for 1st Instance EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL
#define EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL_EIPI_SAM_ENTRY_SET1 0x00B06080u

//! Register Reset Value
#define EIPI_SAM_ENTRY_SET1_RST 0x00000000u

//! Field SET_31_0 - No Content.
#define EIPI_SAM_ENTRY_SET1_SET_31_0_POS 0
//! Field SET_31_0 - No Content.
#define EIPI_SAM_ENTRY_SET1_SET_31_0_MASK 0xFFFFFFFFu

//! @}

//! \defgroup EIPI_SAM_ENTRY_CLEAR1 Register EIPI_SAM_ENTRY_CLEAR1 - EIPI SAM ENTRY CLEAR1
//! @{

//! Register Offset (relative)
#define EIPI_SAM_ENTRY_CLEAR1 0xC0
//! Register Offset (absolute) for 1st Instance EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL
#define EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL_EIPI_SAM_ENTRY_CLEAR1 0x00B060C0u

//! Register Reset Value
#define EIPI_SAM_ENTRY_CLEAR1_RST 0x00000000u

//! Field CLEAR_31_0 - No Content.
#define EIPI_SAM_ENTRY_CLEAR1_CLEAR_31_0_POS 0
//! Field CLEAR_31_0 - No Content.
#define EIPI_SAM_ENTRY_CLEAR1_CLEAR_31_0_MASK 0xFFFFFFFFu

//! @}

//! \defgroup EIPI_SAM_ENTRY_ENABLE_CTRL Register EIPI_SAM_ENTRY_ENABLE_CTRL - EIPI SAM ENTRY ENABLE CTRL
//! @{

//! Register Offset (relative)
#define EIPI_SAM_ENTRY_ENABLE_CTRL 0x100
//! Register Offset (absolute) for 1st Instance EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL
#define EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL_EIPI_SAM_ENTRY_ENABLE_CTRL 0x00B06100u

//! Register Reset Value
#define EIPI_SAM_ENTRY_ENABLE_CTRL_RST 0x00000000u

//! Field SAM_INDEX_SET - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_SET_POS 0
//! Field SAM_INDEX_SET - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_SET_MASK 0x1Fu

//! Field RESERVED_0 - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_RESERVED_0_POS 5
//! Field RESERVED_0 - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_RESERVED_0_MASK 0x3FE0u

//! Field SET_ENABLE - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_SET_ENABLE_POS 14
//! Field SET_ENABLE - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_SET_ENABLE_MASK 0x4000u

//! Field SET_ALL - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_SET_ALL_POS 15
//! Field SET_ALL - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_SET_ALL_MASK 0x8000u

//! Field SAM_INDEX_CLEAR - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_CLEAR_POS 16
//! Field SAM_INDEX_CLEAR - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_CLEAR_MASK 0x1F0000u

//! Field RESERVED_1 - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_RESERVED_1_POS 21
//! Field RESERVED_1 - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_RESERVED_1_MASK 0x3FE00000u

//! Field CLEAR_ENABLE - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_CLEAR_ENABLE_POS 30
//! Field CLEAR_ENABLE - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_CLEAR_ENABLE_MASK 0x40000000u

//! Field CLEAR_ALL - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_CLEAR_ALL_POS 31
//! Field CLEAR_ALL - No Content.
#define EIPI_SAM_ENTRY_ENABLE_CTRL_CLEAR_ALL_MASK 0x80000000u

//! @}

//! \defgroup EIPI_SAM_IN_FLIGHT Register EIPI_SAM_IN_FLIGHT - EIPI SAM IN FLIGHT
//! @{

//! Register Offset (relative)
#define EIPI_SAM_IN_FLIGHT 0x104
//! Register Offset (absolute) for 1st Instance EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL
#define EIPI_EIP_160S_I_32_SAM_ENABLE_CTRL_EIPI_SAM_IN_FLIGHT 0x00B06104u

//! Register Reset Value
#define EIPI_SAM_IN_FLIGHT_RST 0x00000000u

//! Field UNSAFE - No Content.
#define EIPI_SAM_IN_FLIGHT_UNSAFE_POS 0
//! Field UNSAFE - No Content.
#define EIPI_SAM_IN_FLIGHT_UNSAFE_MASK 0x3Fu

//! Field RESERVED_0 - No Content.
#define EIPI_SAM_IN_FLIGHT_RESERVED_0_POS 6
//! Field RESERVED_0 - No Content.
#define EIPI_SAM_IN_FLIGHT_RESERVED_0_MASK 0xC0u

//! Field IN_FLIGHT - No Content.
#define EIPI_SAM_IN_FLIGHT_IN_FLIGHT_POS 8
//! Field IN_FLIGHT - No Content.
#define EIPI_SAM_IN_FLIGHT_IN_FLIGHT_MASK 0x3F00u

//! Field RESERVED_1 - No Content.
#define EIPI_SAM_IN_FLIGHT_RESERVED_1_POS 14
//! Field RESERVED_1 - No Content.
#define EIPI_SAM_IN_FLIGHT_RESERVED_1_MASK 0x7FFFC000u

//! Field LOAD_UNSAFE - No Content.
#define EIPI_SAM_IN_FLIGHT_LOAD_UNSAFE_POS 31
//! Field LOAD_UNSAFE - No Content.
#define EIPI_SAM_IN_FLIGHT_LOAD_UNSAFE_MASK 0x80000000u

//! @}

//! @}

#endif
