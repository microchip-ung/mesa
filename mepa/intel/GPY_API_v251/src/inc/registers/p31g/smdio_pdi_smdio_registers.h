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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/smdio_pdi_smdio_registers_def.xml
// Register File Name  : SMDIO_PDI_SMDIO_REGISTERS
// Register File Title : Config Registers for Slave MDIO
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _SMDIO_PDI_SMDIO_REGISTERS_H
#define _SMDIO_PDI_SMDIO_REGISTERS_H

//! \defgroup SMDIO_PDI_SMDIO_REGISTERS Register File SMDIO_PDI_SMDIO_REGISTERS - Config Registers for Slave MDIO
//! @{

//! Base Address of SMDIO_PDI_SMDIO_REGISTERS
#define SMDIO_PDI_SMDIO_REGISTERS_MODULE_BASE 0x00D3D200u

//! \defgroup SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG Register SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG - MDC Clock Configuration Register
//! @{

//! Register Offset (relative)
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG 0x0
//! Register Offset (absolute) for 1st Instance SMDIO_PDI_SMDIO_REGISTERS
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG 0x00D3D200u

//! Register Reset Value
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_RST 0x000001F5u

//! Field EN - SMDIO Interface Enable
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_EN_POS 0
//! Field EN - SMDIO Interface Enable
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_EN_MASK 0x1u
//! Constant DIS - dis enable
#define CONST_SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_EN_DIS 0x0
//! Constant EN - enable
#define CONST_SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_EN_EN 0x1

//! Field PREN - Preamble Enable
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_PREN_POS 1
//! Field PREN - Preamble Enable
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_PREN_MASK 0x2u
//! Constant DIS - Accurate Preamble Checking is disabled
#define CONST_SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_PREN_DIS 0x0
//! Constant EN - Accurate Preamble Checking is enabled
#define CONST_SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_PREN_EN 0x1

//! Field GPHYISO - GPHY MDIO Isolation Mode
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_GPHYISO_POS 2
//! Field GPHYISO - GPHY MDIO Isolation Mode
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_GPHYISO_MASK 0x4u
//! Constant NM - NM
#define CONST_SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_GPHYISO_NM 0x0
//! Constant GPHYISO - GPHYISO
#define CONST_SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_GPHYISO_GPHYISO 0x1

//! Field ADDR - address
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_ADDR_POS 4
//! Field ADDR - address
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_ADDR_MASK 0x1F0u

//! Field RST - MDIO Slave Hardware Reset
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_RST_POS 15
//! Field RST - MDIO Slave Hardware Reset
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_RST_MASK 0x8000u
//! Constant OFF - OFF
#define CONST_SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_RST_OFF 0x0
//! Constant ON - ON
#define CONST_SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_RST_ON 0x1

//! @}

//! \defgroup SMDIO_PDI_SMDIO_REGISTERS_SMDIO_BADR Register SMDIO_PDI_SMDIO_REGISTERS_SMDIO_BADR - mdc slave target base address
//! @{

//! Register Offset (relative)
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_BADR 0x4
//! Register Offset (absolute) for 1st Instance SMDIO_PDI_SMDIO_REGISTERS
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_PDI_SMDIO_REGISTERS_SMDIO_BADR 0x00D3D204u

//! Register Reset Value
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_BADR_RST 0x00000000u

//! Field ADDR - Target Base Address
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_BADR_ADDR_POS 0
//! Field ADDR - Target Base Address
#define SMDIO_PDI_SMDIO_REGISTERS_SMDIO_BADR_ADDR_MASK 0xFFFFu

//! @}

//! @}

#endif
