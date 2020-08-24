//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_emouchel.priv.p34x_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/slice_pm/sb_pdi_registers_def.xml
// Register File Name  : SB_PDI_REGISTERS
// Register File Title : Slice Config Registers for Shared Buffer
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _SB_PDI_REGISTERS_H
#define _SB_PDI_REGISTERS_H

//! \defgroup SB_PDI_REGISTERS Register File SB_PDI_REGISTERS - Slice Config Registers for Shared Buffer
//! @{

//! Base Address of SB_PDI_REGISTERS
#define SB_PDI_REGISTERS_MODULE_BASE 0x00A38200u

//! \defgroup SB_PDI_REGISTERS_SB_CTRL Register SB_PDI_REGISTERS_SB_CTRL - Shared Buffer Control Register
//! @{

//! Register Offset (relative)
#define SB_PDI_REGISTERS_SB_CTRL 0x0
//! Register Offset (absolute) for 1st Instance SB_PDI_REGISTERS
#define SB_PDI_REGISTERS_SB_PDI_REGISTERS_SB_CTRL 0x00A38200u

//! Register Reset Value
#define SB_PDI_REGISTERS_SB_CTRL_RST 0x00000000u

//! Field REN - Read Enable
#define SB_PDI_REGISTERS_SB_CTRL_REN_POS 0
//! Field REN - Read Enable
#define SB_PDI_REGISTERS_SB_CTRL_REN_MASK 0x1u
//! Constant DIS - Read Disable
#define CONST_SB_PDI_REGISTERS_SB_CTRL_REN_DIS 0x0
//! Constant EN - Read Enable
#define CONST_SB_PDI_REGISTERS_SB_CTRL_REN_EN 0x1

//! Field WEN - Write Enable
#define SB_PDI_REGISTERS_SB_CTRL_WEN_POS 1
//! Field WEN - Write Enable
#define SB_PDI_REGISTERS_SB_CTRL_WEN_MASK 0x2u
//! Constant DIS - Write Disable
#define CONST_SB_PDI_REGISTERS_SB_CTRL_WEN_DIS 0x0
//! Constant EN - Write Enable
#define CONST_SB_PDI_REGISTERS_SB_CTRL_WEN_EN 0x1

//! Field DBG_ACC - Debug Access
#define SB_PDI_REGISTERS_SB_CTRL_DBG_ACC_POS 2
//! Field DBG_ACC - Debug Access
#define SB_PDI_REGISTERS_SB_CTRL_DBG_ACC_MASK 0x4u
//! Constant DIS - Disable access
#define CONST_SB_PDI_REGISTERS_SB_CTRL_DBG_ACC_DIS 0x0
//! Constant EN - Enable access
#define CONST_SB_PDI_REGISTERS_SB_CTRL_DBG_ACC_EN 0x1

//! @}

//! \defgroup SB_PDI_REGISTERS_SB_ADDR Register SB_PDI_REGISTERS_SB_ADDR - Shared Buffer Address Register
//! @{

//! Register Offset (relative)
#define SB_PDI_REGISTERS_SB_ADDR 0x4
//! Register Offset (absolute) for 1st Instance SB_PDI_REGISTERS
#define SB_PDI_REGISTERS_SB_PDI_REGISTERS_SB_ADDR 0x00A38204u

//! Register Reset Value
#define SB_PDI_REGISTERS_SB_ADDR_RST 0x00000000u

//! Field ADDR - Shared Buffer Address
#define SB_PDI_REGISTERS_SB_ADDR_ADDR_POS 0
//! Field ADDR - Shared Buffer Address
#define SB_PDI_REGISTERS_SB_ADDR_ADDR_MASK 0xFFFFu

//! @}

//! \defgroup SB_PDI_REGISTERS_SB_DATA Register SB_PDI_REGISTERS_SB_DATA - Shared Buffer Data Register
//! @{

//! Register Offset (relative)
#define SB_PDI_REGISTERS_SB_DATA 0x8
//! Register Offset (absolute) for 1st Instance SB_PDI_REGISTERS
#define SB_PDI_REGISTERS_SB_PDI_REGISTERS_SB_DATA 0x00A38208u

//! Register Reset Value
#define SB_PDI_REGISTERS_SB_DATA_RST 0x00000000u

//! Field DATA - Data
#define SB_PDI_REGISTERS_SB_DATA_DATA_POS 0
//! Field DATA - Data
#define SB_PDI_REGISTERS_SB_DATA_DATA_MASK 0xFFFFu

//! @}

//! @}

#endif
