//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_emouchel.priv.p34x_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/slice_sgmii/sgmii_shell_pdi_def.xml
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
#define SGMII_SHELL_PDI_REGISTERS_MODULE_BASE 0x00A37000u

//! \defgroup SGMII_CFG Register SGMII_CFG - SGMII configuration register
//! @{

//! Register Offset (relative)
#define SGMII_CFG 0x0
//! Register Offset (absolute) for 1st Instance SGMII_SHELL_PDI_REGISTERS
#define SGMII_SHELL_PDI_REGISTERS_SGMII_CFG 0x00A37000u

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

//! @}

#endif
