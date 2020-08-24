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
// LSD Source          : /home/p31g/p31g_chip/v_hksim.priv.p31g_chip.top/ipg_lsd/lsd_sys/source_mdio/xml/reg_files/sspi_pdi_registers_def.xml
// Register File Name  : SSPI_PDI_REGISTERS
// Register File Title : Config Registers for Slave SPI
// Register Width      : 16
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _SSPI_PDI_REGISTERS_H
#define _SSPI_PDI_REGISTERS_H

//! \defgroup SSPI_PDI_REGISTERS Register File SSPI_PDI_REGISTERS - Config Registers for Slave SPI
//! @{

//! Base Address of SSPI_PDI_REGISTERS
#define SSPI_PDI_REGISTERS_MODULE_BASE 0x0001EB00u

//! \defgroup SSPI_PDI_REGISTERS_SSPI_CFG Register SSPI_PDI_REGISTERS_SSPI_CFG - SPI Slave Configuration Register
//! @{

//! Register Offset (relative)
#define SSPI_PDI_REGISTERS_SSPI_CFG 0x0
//! Register Offset (absolute) for 1st Instance SSPI_PDI_REGISTERS
#define SSPI_PDI_REGISTERS_SSPI_PDI_REGISTERS_SSPI_CFG 0x0001EB00u

//! Register Reset Value
#define SSPI_PDI_REGISTERS_SSPI_CFG_RST 0x0200u

//! Field EN - enable
#define SSPI_PDI_REGISTERS_SSPI_CFG_EN_POS 0
//! Field EN - enable
#define SSPI_PDI_REGISTERS_SSPI_CFG_EN_MASK 0x1u
//! Constant DISABLE - DISABLE
#define CONST_SSPI_PDI_REGISTERS_SSPI_CFG_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SSPI_PDI_REGISTERS_SSPI_CFG_EN_ENABLE 0x1

//! Field DRVDLY - delay
#define SSPI_PDI_REGISTERS_SSPI_CFG_DRVDLY_POS 1
//! Field DRVDLY - delay
#define SSPI_PDI_REGISTERS_SSPI_CFG_DRVDLY_MASK 0xFEu

//! Field REFCYC - SDO output cycle
#define SSPI_PDI_REGISTERS_SSPI_CFG_REFCYC_POS 8
//! Field REFCYC - SDO output cycle
#define SSPI_PDI_REGISTERS_SSPI_CFG_REFCYC_MASK 0x300u

//! Field SDIEGSEL - SDI Edge Select
#define SSPI_PDI_REGISTERS_SSPI_CFG_SDIEGSEL_POS 14
//! Field SDIEGSEL - SDI Edge Select
#define SSPI_PDI_REGISTERS_SSPI_CFG_SDIEGSEL_MASK 0x4000u
//! Constant FALL - FALL
#define CONST_SSPI_PDI_REGISTERS_SSPI_CFG_SDIEGSEL_FALL 0x0
//! Constant RISE - RISE
#define CONST_SSPI_PDI_REGISTERS_SSPI_CFG_SDIEGSEL_RISE 0x1

//! Field SDOEGSEL - SDO Edge Select
#define SSPI_PDI_REGISTERS_SSPI_CFG_SDOEGSEL_POS 15
//! Field SDOEGSEL - SDO Edge Select
#define SSPI_PDI_REGISTERS_SSPI_CFG_SDOEGSEL_MASK 0x8000u
//! Constant FALL - FALL
#define CONST_SSPI_PDI_REGISTERS_SSPI_CFG_SDOEGSEL_FALL 0x0
//! Constant RISE - RISE
#define CONST_SSPI_PDI_REGISTERS_SSPI_CFG_SDOEGSEL_RISE 0x1

//! @}

//! \defgroup SSPI_PDI_REGISTERS_SSPI_DEBUG Register SSPI_PDI_REGISTERS_SSPI_DEBUG - SPI Slave Debug Register
//! @{

//! Register Offset (relative)
#define SSPI_PDI_REGISTERS_SSPI_DEBUG 0x2
//! Register Offset (absolute) for 1st Instance SSPI_PDI_REGISTERS
#define SSPI_PDI_REGISTERS_SSPI_PDI_REGISTERS_SSPI_DEBUG 0x0001EB02u

//! Register Reset Value
#define SSPI_PDI_REGISTERS_SSPI_DEBUG_RST 0x0000u

//! Field PERIOD - SPI clock cycles
#define SSPI_PDI_REGISTERS_SSPI_DEBUG_PERIOD_POS 0
//! Field PERIOD - SPI clock cycles
#define SSPI_PDI_REGISTERS_SSPI_DEBUG_PERIOD_MASK 0x7Fu

//! Field SAMPLE - Synco delay
#define SSPI_PDI_REGISTERS_SSPI_DEBUG_SAMPLE_POS 8
//! Field SAMPLE - Synco delay
#define SSPI_PDI_REGISTERS_SSPI_DEBUG_SAMPLE_MASK 0x7F00u

//! Field FRELOW - SPI Slave Bus Frequency Low
#define SSPI_PDI_REGISTERS_SSPI_DEBUG_FRELOW_POS 15
//! Field FRELOW - SPI Slave Bus Frequency Low
#define SSPI_PDI_REGISTERS_SSPI_DEBUG_FRELOW_MASK 0x8000u
//! Constant HIGH - HIGH
#define CONST_SSPI_PDI_REGISTERS_SSPI_DEBUG_FRELOW_HIGH 0x0
//! Constant LOW - LOW
#define CONST_SSPI_PDI_REGISTERS_SSPI_DEBUG_FRELOW_LOW 0x1

//! @}

//! @}

#endif
