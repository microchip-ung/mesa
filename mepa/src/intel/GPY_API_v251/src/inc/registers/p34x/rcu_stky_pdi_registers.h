//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_emouchel.priv.p34x_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/chip_control/rcu_stky_pdi_registers_def.xml
// Register File Name  : RCU_STKY_PDI_REGISTERS
// Register File Title : Sticky Registers RCU
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _RCU_STKY_PDI_REGISTERS_H
#define _RCU_STKY_PDI_REGISTERS_H

//! \defgroup RCU_STKY_PDI_REGISTERS Register File RCU_STKY_PDI_REGISTERS - Sticky Registers RCU
//! @{

//! Base Address of RCU_STKY_PDI_REGISTERS
#define RCU_STKY_PDI_REGISTERS_MODULE_BASE 0x00D29400u

//! \defgroup RCU_STKY_PDI_REGISTERS_RESET_STATUS Register RCU_STKY_PDI_REGISTERS_RESET_STATUS - Reset Status Register
//! @{

//! Register Offset (relative)
#define RCU_STKY_PDI_REGISTERS_RESET_STATUS 0x0
//! Register Offset (absolute) for 1st Instance RCU_STKY_PDI_REGISTERS
#define RCU_STKY_PDI_REGISTERS_RCU_STKY_PDI_REGISTERS_RESET_STATUS 0x00D29400u

//! Register Reset Value
#define RCU_STKY_PDI_REGISTERS_RESET_STATUS_RST 0x00008000u

//! Field INIT - Initialization Done Flag
#define RCU_STKY_PDI_REGISTERS_RESET_STATUS_INIT_POS 0
//! Field INIT - Initialization Done Flag
#define RCU_STKY_PDI_REGISTERS_RESET_STATUS_INIT_MASK 0x1u
//! Constant NO - NO
#define CONST_RCU_STKY_PDI_REGISTERS_RESET_STATUS_INIT_NO 0x0
//! Constant DONE - DONE
#define CONST_RCU_STKY_PDI_REGISTERS_RESET_STATUS_INIT_DONE 0x1

//! Field RECORD - Last Reset Record
#define RCU_STKY_PDI_REGISTERS_RESET_STATUS_RECORD_POS 1
//! Field RECORD - Last Reset Record
#define RCU_STKY_PDI_REGISTERS_RESET_STATUS_RECORD_MASK 0x7FFEu

//! Field HRST - Hardware Reset Cause Flag
#define RCU_STKY_PDI_REGISTERS_RESET_STATUS_HRST_POS 15
//! Field HRST - Hardware Reset Cause Flag
#define RCU_STKY_PDI_REGISTERS_RESET_STATUS_HRST_MASK 0x8000u
//! Constant SRST - SRST
#define CONST_RCU_STKY_PDI_REGISTERS_RESET_STATUS_HRST_SRST 0x0
//! Constant HRST - HRST
#define CONST_RCU_STKY_PDI_REGISTERS_RESET_STATUS_HRST_HRST 0x1

//! @}

//! @}

#endif
