//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_emouchel.priv.p34x_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/slice_gphy_shell/gphy_shell_pdi_def.xml
// Register File Name  : GPHY_SHELL_PDI
// Register File Title : Slice Config Registers for GPHYs Shells
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _GPHY_SHELL_PDI_H
#define _GPHY_SHELL_PDI_H

//! \defgroup GPHY_SHELL_PDI Register File GPHY_SHELL_PDI - Slice Config Registers for GPHYs Shells
//! @{

//! Base Address of GPHY_SHELL_PDI
#define GPHY_SHELL_PDI_MODULE_BASE 0x00A44000u

//! \defgroup GPHY_SHELL_PDI_CTRL Register GPHY_SHELL_PDI_CTRL - GPHY Shell control
//! @{

//! Register Offset (relative)
#define GPHY_SHELL_PDI_CTRL 0x0
//! Register Offset (absolute) for 1st Instance GPHY_SHELL_PDI
#define GPHY_SHELL_PDI_GPHY_SHELL_PDI_CTRL 0x00A44000u

//! Register Reset Value
#define GPHY_SHELL_PDI_CTRL_RST 0x00000000u

//! Field RES - placeholder
#define GPHY_SHELL_PDI_CTRL_RES_POS 0
//! Field RES - placeholder
#define GPHY_SHELL_PDI_CTRL_RES_MASK 0xFFFFu

//! @}

//! \defgroup GPHY_SHELL_PDI_STA Register GPHY_SHELL_PDI_STA - GPHY Shell Status
//! @{

//! Register Offset (relative)
#define GPHY_SHELL_PDI_STA 0x4
//! Register Offset (absolute) for 1st Instance GPHY_SHELL_PDI
#define GPHY_SHELL_PDI_GPHY_SHELL_PDI_STA 0x00A44004u

//! Register Reset Value
#define GPHY_SHELL_PDI_STA_RST 0x00000002u

//! Field RES - placeholder
#define GPHY_SHELL_PDI_STA_RES_POS 1
//! Field RES - placeholder
#define GPHY_SHELL_PDI_STA_RES_MASK 0x2u

//! @}

//! \defgroup GPHY_SHELL_PDI_FCR_SD Register GPHY_SHELL_PDI_FCR_SD - Shadow Register from Top FCR and BOOTSEL
//! @{

//! Register Offset (relative)
#define GPHY_SHELL_PDI_FCR_SD 0x8
//! Register Offset (absolute) for 1st Instance GPHY_SHELL_PDI
#define GPHY_SHELL_PDI_GPHY_SHELL_PDI_FCR_SD 0x00A44008u

//! Register Reset Value
#define GPHY_SHELL_PDI_FCR_SD_RST 0x00000000u

//! Field FCR - Firmware address offset MSB
#define GPHY_SHELL_PDI_FCR_SD_FCR_POS 0
//! Field FCR - Firmware address offset MSB
#define GPHY_SHELL_PDI_FCR_SD_FCR_MASK 0x3FFFu

//! Field BOOTSEL - Boot Select
#define GPHY_SHELL_PDI_FCR_SD_BOOTSEL_POS 14
//! Field BOOTSEL - Boot Select
#define GPHY_SHELL_PDI_FCR_SD_BOOTSEL_MASK 0xC000u
//! Constant ROM - GPHY Macro loads firmware memory from internal ROM
#define CONST_GPHY_SHELL_PDI_FCR_SD_BOOTSEL_ROM 0x0
//! Constant RAM - GPHY Macro loads firmware memory from internal RAM.
#define CONST_GPHY_SHELL_PDI_FCR_SD_BOOTSEL_RAM 0x1
//! Constant FLASH - GPHY Macro loads firmware memory by external E2PROM.
#define CONST_GPHY_SHELL_PDI_FCR_SD_BOOTSEL_FLASH 0x2
//! Constant OTP - GPHY Macro loads firmware memory from OTP
#define CONST_GPHY_SHELL_PDI_FCR_SD_BOOTSEL_OTP 0x3

//! @}

//! \defgroup GPHY_SHELL_PDI_SHADOW Register GPHY_SHELL_PDI_SHADOW - Second Shadow Code Register
//! @{

//! Register Offset (relative)
#define GPHY_SHELL_PDI_SHADOW 0xC
//! Register Offset (absolute) for 1st Instance GPHY_SHELL_PDI
#define GPHY_SHELL_PDI_GPHY_SHELL_PDI_SHADOW 0x00A4400Cu

//! Register Reset Value
#define GPHY_SHELL_PDI_SHADOW_RST 0x00000002u

//! Field NOWAIT - No Wait
#define GPHY_SHELL_PDI_SHADOW_NOWAIT_POS 1
//! Field NOWAIT - No Wait
#define GPHY_SHELL_PDI_SHADOW_NOWAIT_MASK 0x2u
//! Constant HALT - Halt mode enable
#define CONST_GPHY_SHELL_PDI_SHADOW_NOWAIT_HALT 0x0
//! Constant NOWAIT - Halt mode disable
#define CONST_GPHY_SHELL_PDI_SHADOW_NOWAIT_NOWAIT 0x1

//! Field RES - Reserved
#define GPHY_SHELL_PDI_SHADOW_RES_POS 2
//! Field RES - Reserved
#define GPHY_SHELL_PDI_SHADOW_RES_MASK 0x1FFFCu

//! @}

//! @}

#endif
