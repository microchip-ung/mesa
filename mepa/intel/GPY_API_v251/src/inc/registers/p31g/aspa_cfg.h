//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/fcsi2c_pdi_def.xml
// Register File Name  : ASPA_CFG
// Register File Title : FCSI Master Register File
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _ASPA_CFG_H
#define _ASPA_CFG_H

//! \defgroup ASPA_CFG Register File ASPA_CFG - FCSI Master Register File
//! @{

//! Base Address of CDB_CFG
#define CDB_CFG_MODULE_BASE 0x00D20000u
//! Base Address of XO_CFG
#define XO_CFG_MODULE_BASE 0x00D28000u
//! Base Address of DCPM_CFG
#define DCPM_CFG_MODULE_BASE 0x00D29800u

//! \defgroup ASPA_CFG_CTRL Register ASPA_CFG_CTRL - CONTROL REGISTER
//! @{

//! Register Offset (relative)
#define ASPA_CFG_CTRL 0x0
//! Register Offset (absolute) for 1st Instance CDB_CFG
#define CDB_CFG_ASPA_CFG_CTRL 0x00D20000u

//! Register Reset Value
#define ASPA_CFG_CTRL_RST 0x00000010u

//! Field BUSY - BUSY STATUS
#define ASPA_CFG_CTRL_BUSY_POS 0
//! Field BUSY - BUSY STATUS
#define ASPA_CFG_CTRL_BUSY_MASK 0x1u
//! Constant FREE - Serial line free
#define CONST_ASPA_CFG_CTRL_BUSY_FREE 0x0
//! Constant BUSY - Serial line busy
#define CONST_ASPA_CFG_CTRL_BUSY_BUSY 0x1

//! Field MOD_INIT - MODULE INIT
#define ASPA_CFG_CTRL_MOD_INIT_POS 1
//! Field MOD_INIT - MODULE INIT
#define ASPA_CFG_CTRL_MOD_INIT_MASK 0x2u
//! Constant DIS - Disable
#define CONST_ASPA_CFG_CTRL_MOD_INIT_DIS 0x0
//! Constant EN - Enable
#define CONST_ASPA_CFG_CTRL_MOD_INIT_EN 0x1

//! Field RST_SLAVE - RESET AFE
#define ASPA_CFG_CTRL_RST_SLAVE_POS 2
//! Field RST_SLAVE - RESET AFE
#define ASPA_CFG_CTRL_RST_SLAVE_MASK 0x4u
//! Constant NO_RST - No reset
#define CONST_ASPA_CFG_CTRL_RST_SLAVE_NO_RST 0x0
//! Constant RST - Reset
#define CONST_ASPA_CFG_CTRL_RST_SLAVE_RST 0x1

//! Field BUS_BLOCK - CONTROL Bus Access Block
#define ASPA_CFG_CTRL_BUS_BLOCK_POS 3
//! Field BUS_BLOCK - CONTROL Bus Access Block
#define ASPA_CFG_CTRL_BUS_BLOCK_MASK 0x8u
//! Constant NO_BLOCK_ACC - Non blocking access
#define CONST_ASPA_CFG_CTRL_BUS_BLOCK_NO_BLOCK_ACC 0x0
//! Constant BLOCK_ACC - Blocking access
#define CONST_ASPA_CFG_CTRL_BUS_BLOCK_BLOCK_ACC 0x1

//! Field CLK_DIV - CLOCK DIVIDER
#define ASPA_CFG_CTRL_CLK_DIV_POS 4
//! Field CLK_DIV - CLOCK DIVIDER
#define ASPA_CFG_CTRL_CLK_DIV_MASK 0xF0u
//! Constant DEFAULT - Default value
#define CONST_ASPA_CFG_CTRL_CLK_DIV_DEFAULT 0x1

//! @}

//! \defgroup ASPA_CFG_DATA Register ASPA_CFG_DATA - READ DATA REGISTER
//! @{

//! Register Offset (relative)
#define ASPA_CFG_DATA 0x4
//! Register Offset (absolute) for 1st Instance CDB_CFG
#define CDB_CFG_ASPA_CFG_DATA 0x00D20004u

//! Register Reset Value
#define ASPA_CFG_DATA_RST 0x00000000u

//! Field READ_DATA - READ DATA VALUE
#define ASPA_CFG_DATA_READ_DATA_POS 0
//! Field READ_DATA - READ DATA VALUE
#define ASPA_CFG_DATA_READ_DATA_MASK 0xFFFFu

//! @}

//! \defgroup ASPA_CFG_IRQ Register ASPA_CFG_IRQ - INTERRUPT REGISTER
//! @{

//! Register Offset (relative)
#define ASPA_CFG_IRQ 0x8
//! Register Offset (absolute) for 1st Instance CDB_CFG
#define CDB_CFG_ASPA_CFG_IRQ 0x00D20008u

//! Register Reset Value
#define ASPA_CFG_IRQ_RST 0x00000000u

//! Field IRQ1 - TRANSACTION DONE
#define ASPA_CFG_IRQ_IRQ1_POS 0
//! Field IRQ1 - TRANSACTION DONE
#define ASPA_CFG_IRQ_IRQ1_MASK 0x1u
//! Constant NORM - Normal operation
#define CONST_ASPA_CFG_IRQ_IRQ1_NORM 0x0
//! Constant TXD - Transaction done
#define CONST_ASPA_CFG_IRQ_IRQ1_TXD 0x1

//! Field IRQ2 - READ DATA AVAILABLE
#define ASPA_CFG_IRQ_IRQ2_POS 1
//! Field IRQ2 - READ DATA AVAILABLE
#define ASPA_CFG_IRQ_IRQ2_MASK 0x2u
//! Constant NORM - Normal operation
#define CONST_ASPA_CFG_IRQ_IRQ2_NORM 0x0
//! Constant RDA - Read data available
#define CONST_ASPA_CFG_IRQ_IRQ2_RDA 0x1

//! @}

//! \defgroup ASPA_CFG_IRQ_MASK Register ASPA_CFG_IRQ_MASK - INTERRUPT MASK REGISTER
//! @{

//! Register Offset (relative)
#define ASPA_CFG_IRQ_MASK 0xC
//! Register Offset (absolute) for 1st Instance CDB_CFG
#define CDB_CFG_ASPA_CFG_IRQ_MASK 0x00D2000Cu

//! Register Reset Value
#define ASPA_CFG_IRQ_MASK_RST 0x00000000u

//! Field IRQ1_MASK - MASK BIT FOR IRQ1
#define ASPA_CFG_IRQ_MASK_IRQ1_MASK_POS 0
//! Field IRQ1_MASK - MASK BIT FOR IRQ1
#define ASPA_CFG_IRQ_MASK_IRQ1_MASK_MASK 0x1u
//! Constant DIS - Disable
#define CONST_ASPA_CFG_IRQ_MASK_IRQ1_MASK_DIS 0x0
//! Constant EN - Enable
#define CONST_ASPA_CFG_IRQ_MASK_IRQ1_MASK_EN 0x1

//! Field IRQ2_MASK - MASK BIT FOR IRQ2
#define ASPA_CFG_IRQ_MASK_IRQ2_MASK_POS 1
//! Field IRQ2_MASK - MASK BIT FOR IRQ2
#define ASPA_CFG_IRQ_MASK_IRQ2_MASK_MASK 0x2u
//! Constant DIS - Disable
#define CONST_ASPA_CFG_IRQ_MASK_IRQ2_MASK_DIS 0x0
//! Constant EN - Enable
#define CONST_ASPA_CFG_IRQ_MASK_IRQ2_MASK_EN 0x1

//! @}

//! @}

#endif
