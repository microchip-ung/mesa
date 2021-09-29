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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/rcu_pdi_registers_def.xml
// Register File Name  : RCU_PDI_REGISTERS
// Register File Title : Config Registers RCU
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _RCU_PDI_REGISTERS_H
#define _RCU_PDI_REGISTERS_H

//! \defgroup RCU_PDI_REGISTERS Register File RCU_PDI_REGISTERS - Config Registers RCU
//! @{

//! Base Address of RCU_PDI_REGISTERS
#define RCU_PDI_REGISTERS_MODULE_BASE 0x00D29404u

//! \defgroup RCU_PDI_REGISTERS_RST_REQ Register RCU_PDI_REGISTERS_RST_REQ - Reset Request
//! @{

//! Register Offset (relative)
#define RCU_PDI_REGISTERS_RST_REQ 0x0
//! Register Offset (absolute) for 1st Instance RCU_PDI_REGISTERS
#define RCU_PDI_REGISTERS_RCU_PDI_REGISTERS_RST_REQ 0x00D29404u

//! Register Reset Value
#define RCU_PDI_REGISTERS_RST_REQ_RST 0x00000001u

//! Field RD0 - Reset Request for Reset Domain RD0
#define RCU_PDI_REGISTERS_RST_REQ_RD0_POS 0
//! Field RD0 - Reset Request for Reset Domain RD0
#define RCU_PDI_REGISTERS_RST_REQ_RD0_MASK 0x1u
//! Constant DISABLED - Disabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD0_DISABLED 0x0
//! Constant ENABLED - Enabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD0_ENABLED 0x1

//! Field RD1 - Reset Request for Reset Domain RD1
#define RCU_PDI_REGISTERS_RST_REQ_RD1_POS 1
//! Field RD1 - Reset Request for Reset Domain RD1
#define RCU_PDI_REGISTERS_RST_REQ_RD1_MASK 0x2u
//! Constant DISABLED - Disabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD1_DISABLED 0x0
//! Constant ENABLED - Enabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD1_ENABLED 0x1

//! Field RD4 - Reset Request for Reset Domain RD4
#define RCU_PDI_REGISTERS_RST_REQ_RD4_POS 4
//! Field RD4 - Reset Request for Reset Domain RD4
#define RCU_PDI_REGISTERS_RST_REQ_RD4_MASK 0x10u
//! Constant DISABLED - Disabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD4_DISABLED 0x0
//! Constant ENABLED - Enabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD4_ENABLED 0x1

//! Field RD5 - Reset Request for Reset Domain RD5
#define RCU_PDI_REGISTERS_RST_REQ_RD5_POS 5
//! Field RD5 - Reset Request for Reset Domain RD5
#define RCU_PDI_REGISTERS_RST_REQ_RD5_MASK 0x20u
//! Constant DISABLED - Disabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD5_DISABLED 0x0
//! Constant ENABLED - Enabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD5_ENABLED 0x1

//! Field RD9 - Reset Request for Reset Domain RD9
#define RCU_PDI_REGISTERS_RST_REQ_RD9_POS 9
//! Field RD9 - Reset Request for Reset Domain RD9
#define RCU_PDI_REGISTERS_RST_REQ_RD9_MASK 0x200u
//! Constant DISABLED - Disabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD9_DISABLED 0x0
//! Constant ENABLED - Enabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD9_ENABLED 0x1

//! Field RD10 - Reset Request for Reset Domain RD10
#define RCU_PDI_REGISTERS_RST_REQ_RD10_POS 10
//! Field RD10 - Reset Request for Reset Domain RD10
#define RCU_PDI_REGISTERS_RST_REQ_RD10_MASK 0x400u
//! Constant DISABLED - Disabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD10_DISABLED 0x0
//! Constant ENABLED - Enabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD10_ENABLED 0x1

//! Field G0RST - Reset Request GPHY
#define RCU_PDI_REGISTERS_RST_REQ_G0RST_POS 12
//! Field G0RST - Reset Request GPHY
#define RCU_PDI_REGISTERS_RST_REQ_G0RST_MASK 0x1000u
//! Constant NIL - Nil
#define CONST_RCU_PDI_REGISTERS_RST_REQ_G0RST_NIL 0x0
//! Constant REQ - REQ
#define CONST_RCU_PDI_REGISTERS_RST_REQ_G0RST_REQ 0x1

//! Field RD14 - Reset Request for Reset Domain RD14
#define RCU_PDI_REGISTERS_RST_REQ_RD14_POS 14
//! Field RD14 - Reset Request for Reset Domain RD14
#define RCU_PDI_REGISTERS_RST_REQ_RD14_MASK 0x4000u
//! Constant DISABLED - Disabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD14_DISABLED 0x0
//! Constant ENABLED - Enabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_RD14_ENABLED 0x1

//! Field SRST - Software Reset Request
#define RCU_PDI_REGISTERS_RST_REQ_SRST_POS 15
//! Field SRST - Software Reset Request
#define RCU_PDI_REGISTERS_RST_REQ_SRST_MASK 0x8000u
//! Constant NIL - There is no pending command
#define CONST_RCU_PDI_REGISTERS_RST_REQ_SRST_NIL 0x0
//! Constant REQ - Request
#define CONST_RCU_PDI_REGISTERS_RST_REQ_SRST_REQ 0x1

//! @}

//! \defgroup RCU_PDI_REGISTERS_RST_REQ2 Register RCU_PDI_REGISTERS_RST_REQ2 - Reset Request 2
//! @{

//! Register Offset (relative)
#define RCU_PDI_REGISTERS_RST_REQ2 0x4
//! Register Offset (absolute) for 1st Instance RCU_PDI_REGISTERS
#define RCU_PDI_REGISTERS_RCU_PDI_REGISTERS_RST_REQ2 0x00D29408u

//! Register Reset Value
#define RCU_PDI_REGISTERS_RST_REQ2_RST 0x00000000u

//! Field OTP_RD - OTP Reset
#define RCU_PDI_REGISTERS_RST_REQ2_OTP_RD_POS 0
//! Field OTP_RD - OTP Reset
#define RCU_PDI_REGISTERS_RST_REQ2_OTP_RD_MASK 0x1u
//! Constant ENABLE - Not Reset
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_OTP_RD_ENABLE 0x0
//! Constant RESET - Reset
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_OTP_RD_RESET 0x1

//! @}

//! \defgroup RCU_PDI_REGISTERS_SPARE1 Register RCU_PDI_REGISTERS_SPARE1 - spare config
//! @{

//! Register Offset (relative)
#define RCU_PDI_REGISTERS_SPARE1 0x8
//! Register Offset (absolute) for 1st Instance RCU_PDI_REGISTERS
#define RCU_PDI_REGISTERS_RCU_PDI_REGISTERS_SPARE1 0x00D2940Cu

//! Register Reset Value
#define RCU_PDI_REGISTERS_SPARE1_RST 0x00000000u

//! Field SPARE - spare config register
#define RCU_PDI_REGISTERS_SPARE1_SPARE_POS 0
//! Field SPARE - spare config register
#define RCU_PDI_REGISTERS_SPARE1_SPARE_MASK 0xFFFFu

//! @}

//! \defgroup RCU_PDI_REGISTERS_DBG0 Register RCU_PDI_REGISTERS_DBG0 - Debug Register
//! @{

//! Register Offset (relative)
#define RCU_PDI_REGISTERS_DBG0 0xC
//! Register Offset (absolute) for 1st Instance RCU_PDI_REGISTERS
#define RCU_PDI_REGISTERS_RCU_PDI_REGISTERS_DBG0 0x00D29410u

//! Register Reset Value
#define RCU_PDI_REGISTERS_DBG0_RST 0x00000000u

//! Field DBG - spare config register
#define RCU_PDI_REGISTERS_DBG0_DBG_POS 0
//! Field DBG - spare config register
#define RCU_PDI_REGISTERS_DBG0_DBG_MASK 0xFFFFu

//! @}

//! \defgroup RCU_PDI_REGISTERS_DBG1 Register RCU_PDI_REGISTERS_DBG1 - Debug Register
//! @{

//! Register Offset (relative)
#define RCU_PDI_REGISTERS_DBG1 0x10
//! Register Offset (absolute) for 1st Instance RCU_PDI_REGISTERS
#define RCU_PDI_REGISTERS_RCU_PDI_REGISTERS_DBG1 0x00D29414u

//! Register Reset Value
#define RCU_PDI_REGISTERS_DBG1_RST 0x00000000u

//! Field DBG - spare config register
#define RCU_PDI_REGISTERS_DBG1_DBG_POS 0
//! Field DBG - spare config register
#define RCU_PDI_REGISTERS_DBG1_DBG_MASK 0xFFFFu

//! @}

//! @}

#endif
