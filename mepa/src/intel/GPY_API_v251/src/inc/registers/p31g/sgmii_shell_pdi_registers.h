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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/sgmii_shell_pdi_def.xml
// Register File Name  : SGMII_SHELL_PDI_REGISTERS
// Register File Title : SGMII Shell Registers Description
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _SGMII_SHELL_PDI_REGISTERS_H
#define _SGMII_SHELL_PDI_REGISTERS_H

//! \defgroup SGMII_SHELL_PDI_REGISTERS Register File SGMII_SHELL_PDI_REGISTERS - SGMII Shell Registers Description
//! @{

//! Base Address of SGMII_SHELL_PDI_REGISTERS
#define SGMII_SHELL_PDI_REGISTERS_MODULE_BASE 0x00D37000u

//! \defgroup SGMII_CFG Register SGMII_CFG - SGMII configuration register
//! @{

//! Register Offset (relative)
#define SGMII_CFG 0x0
//! Register Offset (absolute) for 1st Instance SGMII_SHELL_PDI_REGISTERS
#define SGMII_SHELL_PDI_REGISTERS_SGMII_CFG 0x00D37000u

//! Register Reset Value
#define SGMII_CFG_RST 0x00000008u

//! Field TR_DR - Data Rate
#define SGMII_CFG_TR_DR_POS 0
//! Field TR_DR - Data Rate
#define SGMII_CFG_TR_DR_MASK 0x7u
//! Constant MII10 - MII mode with 10Mbps data rate
#define CONST_SGMII_CFG_TR_DR_MII10 0x0
//! Constant MII100 - MII mode with 100Mbps data rate
#define CONST_SGMII_CFG_TR_DR_MII100 0x1
//! Constant GMII1000 - GMII mode with 1000Mbps data rate
#define CONST_SGMII_CFG_TR_DR_GMII1000 0x2
//! Constant GMII2500M - GMII mode with 2500Mbps data rate
#define CONST_SGMII_CFG_TR_DR_GMII2500M 0x5

//! Field SGMII_DIS - SGMII Macro Disable
#define SGMII_CFG_SGMII_DIS_POS 3
//! Field SGMII_DIS - SGMII Macro Disable
#define SGMII_CFG_SGMII_DIS_MASK 0x8u
//! Constant EN - SGMII macro is enabled
#define CONST_SGMII_CFG_SGMII_DIS_EN 0x0
//! Constant DIS - SGMII macro is disabled
#define CONST_SGMII_CFG_SGMII_DIS_DIS 0x1

//! Field FREQ_SEL - Frequency Select
#define SGMII_CFG_FREQ_SEL_POS 4
//! Field FREQ_SEL - Frequency Select
#define SGMII_CFG_FREQ_SEL_MASK 0x10u
//! Constant F25 - Input clock from internal REFCLK_ALT at 25 MHz
#define CONST_SGMII_CFG_FREQ_SEL_F25 0x0
//! Constant F40 - Input clock from internal REFCLK_ALT at 40 MHz
#define CONST_SGMII_CFG_FREQ_SEL_F40 0x1

//! @}

//! \defgroup SGMII_PREAMBLE_CFG Register SGMII_PREAMBLE_CFG
//! @{

//! Register Offset (relative)
#define SGMII_PREAMBLE_CFG 0x4
//! Register Offset (absolute) for 1st Instance SGMII_SHELL_PDI_REGISTERS
#define SGMII_SHELL_PDI_REGISTERS_SGMII_PREAMBLE_CFG 0x00D37004u

//! Register Reset Value
#define SGMII_PREAMBLE_CFG_RST 0x000000D5u

//! Field SFD_VALUE - SFD Value Pattern for realignment
#define SGMII_PREAMBLE_CFG_SFD_VALUE_POS 0
//! Field SFD_VALUE - SFD Value Pattern for realignment
#define SGMII_PREAMBLE_CFG_SFD_VALUE_MASK 0xFFu

//! Field SFD_REALIGN_EN - Enable the search and realignment mechanism
#define SGMII_PREAMBLE_CFG_SFD_REALIGN_EN_POS 8
//! Field SFD_REALIGN_EN - Enable the search and realignment mechanism
#define SGMII_PREAMBLE_CFG_SFD_REALIGN_EN_MASK 0x100u
//! Constant DISABLE - Disabled
#define CONST_SGMII_PREAMBLE_CFG_SFD_REALIGN_EN_DISABLE 0x0
//! Constant ENABLE - Enabled
#define CONST_SGMII_PREAMBLE_CFG_SFD_REALIGN_EN_ENABLE 0x1

//! Field SFD_NOT_FOUND - SFD pattern not found
#define SGMII_PREAMBLE_CFG_SFD_NOT_FOUND_POS 9
//! Field SFD_NOT_FOUND - SFD pattern not found
#define SGMII_PREAMBLE_CFG_SFD_NOT_FOUND_MASK 0x200u
//! Constant NORMAL - Normal operation
#define CONST_SGMII_PREAMBLE_CFG_SFD_NOT_FOUND_NORMAL 0x0
//! Constant NOT_FOUND - SFD pattern not found
#define CONST_SGMII_PREAMBLE_CFG_SFD_NOT_FOUND_NOT_FOUND 0x1

//! @}

//! @}

#endif
