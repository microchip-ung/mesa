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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/gphy_shell_pdi_def.xml
// Register File Name  : GPHY_SHELL_PDI
// Register File Title : Config Registers for GPHYs
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _GPHY_SHELL_PDI_H
#define _GPHY_SHELL_PDI_H

//! \defgroup GPHY_SHELL_PDI Register File GPHY_SHELL_PDI - Config Registers for GPHYs
//! @{

//! Base Address of GPHY_SHELL_PDI
#define GPHY_SHELL_PDI_MODULE_BASE 0x00D24000u

//! \defgroup GPHY_SHELL_PDI_GPHY_FCR Register GPHY_SHELL_PDI_GPHY_FCR - Firmware address offset register
//! @{

//! Register Offset (relative)
#define GPHY_SHELL_PDI_GPHY_FCR 0x0
//! Register Offset (absolute) for 1st Instance GPHY_SHELL_PDI
#define GPHY_SHELL_PDI_GPHY_SHELL_PDI_GPHY_FCR 0x00D24000u

//! Register Reset Value
#define GPHY_SHELL_PDI_GPHY_FCR_RST 0x00000000u

//! Field FCR - Firmware address offset MSB
#define GPHY_SHELL_PDI_GPHY_FCR_FCR_POS 0
//! Field FCR - Firmware address offset MSB
#define GPHY_SHELL_PDI_GPHY_FCR_FCR_MASK 0x3FFFu

//! Field BOOTSEL - Boot Select
#define GPHY_SHELL_PDI_GPHY_FCR_BOOTSEL_POS 14
//! Field BOOTSEL - Boot Select
#define GPHY_SHELL_PDI_GPHY_FCR_BOOTSEL_MASK 0xC000u
//! Constant ROM - GPHY Macro loads firmware memory from internal ROM
#define CONST_GPHY_SHELL_PDI_GPHY_FCR_BOOTSEL_ROM 0x0
//! Constant RAM - GPHY Macro loads firmware memory from internal RAM.
#define CONST_GPHY_SHELL_PDI_GPHY_FCR_BOOTSEL_RAM 0x1
//! Constant FLASH - GPHY Macro loads firmware memory by external E2PROM.
#define CONST_GPHY_SHELL_PDI_GPHY_FCR_BOOTSEL_FLASH 0x2
//! Constant OTP - GPHY Macro loads firmware memory from OTP
#define CONST_GPHY_SHELL_PDI_GPHY_FCR_BOOTSEL_OTP 0x3

//! @}

//! \defgroup GPHY_SHELL_PDI_GPHY_CFG Register GPHY_SHELL_PDI_GPHY_CFG - GPHY Code Configuration Register
//! @{

//! Register Offset (relative)
#define GPHY_SHELL_PDI_GPHY_CFG 0x4
//! Register Offset (absolute) for 1st Instance GPHY_SHELL_PDI
#define GPHY_SHELL_PDI_GPHY_SHELL_PDI_GPHY_CFG 0x00D24004u

//! Register Reset Value
#define GPHY_SHELL_PDI_GPHY_CFG_RST 0x00000002u

//! Field NOWAIT - No Wait
#define GPHY_SHELL_PDI_GPHY_CFG_NOWAIT_POS 1
//! Field NOWAIT - No Wait
#define GPHY_SHELL_PDI_GPHY_CFG_NOWAIT_MASK 0x2u
//! Constant HALT - Halt mode enable
#define CONST_GPHY_SHELL_PDI_GPHY_CFG_NOWAIT_HALT 0x0
//! Constant NOWAIT - Halt mode disable
#define CONST_GPHY_SHELL_PDI_GPHY_CFG_NOWAIT_NOWAIT 0x1

//! @}

//! \defgroup GPHY_SHELL_PDI_GPHY_FCR_SD Register GPHY_SHELL_PDI_GPHY_FCR_SD - GPHY Shadow Address Offset Register
//! @{

//! Register Offset (relative)
#define GPHY_SHELL_PDI_GPHY_FCR_SD 0x8
//! Register Offset (absolute) for 1st Instance GPHY_SHELL_PDI
#define GPHY_SHELL_PDI_GPHY_SHELL_PDI_GPHY_FCR_SD 0x00D24008u

//! Register Reset Value
#define GPHY_SHELL_PDI_GPHY_FCR_SD_RST 0x00000000u

//! Field FCR - Firmware address offset MSB
#define GPHY_SHELL_PDI_GPHY_FCR_SD_FCR_POS 0
//! Field FCR - Firmware address offset MSB
#define GPHY_SHELL_PDI_GPHY_FCR_SD_FCR_MASK 0x3FFFu

//! Field BOOTSEL - Boot Select
#define GPHY_SHELL_PDI_GPHY_FCR_SD_BOOTSEL_POS 14
//! Field BOOTSEL - Boot Select
#define GPHY_SHELL_PDI_GPHY_FCR_SD_BOOTSEL_MASK 0xC000u
//! Constant ROM - GPHY Macro loads firmware memory from internal ROM
#define CONST_GPHY_SHELL_PDI_GPHY_FCR_SD_BOOTSEL_ROM 0x0
//! Constant RAM - GPHY Macro loads firmware memory from internal RAM.
#define CONST_GPHY_SHELL_PDI_GPHY_FCR_SD_BOOTSEL_RAM 0x1
//! Constant FLASH - GPHY Macro loads firmware memory by external E2PROM.
#define CONST_GPHY_SHELL_PDI_GPHY_FCR_SD_BOOTSEL_FLASH 0x2
//! Constant OTP - GPHY Macro loads firmware memory from OTP
#define CONST_GPHY_SHELL_PDI_GPHY_FCR_SD_BOOTSEL_OTP 0x3

//! @}

//! \defgroup GPHY_SHELL_PDI_GPHY_CFG_SD Register GPHY_SHELL_PDI_GPHY_CFG_SD - GPHY Shadow Code Configuration Register
//! @{

//! Register Offset (relative)
#define GPHY_SHELL_PDI_GPHY_CFG_SD 0xC
//! Register Offset (absolute) for 1st Instance GPHY_SHELL_PDI
#define GPHY_SHELL_PDI_GPHY_SHELL_PDI_GPHY_CFG_SD 0x00D2400Cu

//! Register Reset Value
#define GPHY_SHELL_PDI_GPHY_CFG_SD_RST 0x00000002u

//! Field NOWAIT - No Wait
#define GPHY_SHELL_PDI_GPHY_CFG_SD_NOWAIT_POS 1
//! Field NOWAIT - No Wait
#define GPHY_SHELL_PDI_GPHY_CFG_SD_NOWAIT_MASK 0x2u
//! Constant HALT - Halt mode enable
#define CONST_GPHY_SHELL_PDI_GPHY_CFG_SD_NOWAIT_HALT 0x0
//! Constant NOWAIT - Halt mode disable
#define CONST_GPHY_SHELL_PDI_GPHY_CFG_SD_NOWAIT_NOWAIT 0x1

//! @}

//! @}

#endif
