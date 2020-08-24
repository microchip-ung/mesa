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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/uart_pdi_registers_def.xml
// Register File Name  : UART_PDI_REGISTERS
// Register File Title : Config Registers for Uart
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _UART_PDI_REGISTERS_H
#define _UART_PDI_REGISTERS_H

//! \defgroup UART_PDI_REGISTERS Register File UART_PDI_REGISTERS - Config Registers for Uart
//! @{

//! Base Address of UART_PDI_REGISTERS
#define UART_PDI_REGISTERS_MODULE_BASE 0x00D3DA00u

//! \defgroup UART_PDI_REGISTERS_UART_CFG Register UART_PDI_REGISTERS_UART_CFG - UART Master Interface Configuration Register
//! @{

//! Register Offset (relative)
#define UART_PDI_REGISTERS_UART_CFG 0x0
//! Register Offset (absolute) for 1st Instance UART_PDI_REGISTERS
#define UART_PDI_REGISTERS_UART_PDI_REGISTERS_UART_CFG 0x00D3DA00u

//! Register Reset Value
#define UART_PDI_REGISTERS_UART_CFG_RST 0x00000001u

//! Field EN - UART Interface Enable
#define UART_PDI_REGISTERS_UART_CFG_EN_POS 0
//! Field EN - UART Interface Enable
#define UART_PDI_REGISTERS_UART_CFG_EN_MASK 0x1u
//! Constant DIS - disable
#define CONST_UART_PDI_REGISTERS_UART_CFG_EN_DIS 0x0
//! Constant EN - enable
#define CONST_UART_PDI_REGISTERS_UART_CFG_EN_EN 0x1

//! Field PAREN - UART Parity Enable
#define UART_PDI_REGISTERS_UART_CFG_PAREN_POS 1
//! Field PAREN - UART Parity Enable
#define UART_PDI_REGISTERS_UART_CFG_PAREN_MASK 0x2u
//! Constant DIS - disable
#define CONST_UART_PDI_REGISTERS_UART_CFG_PAREN_DIS 0x0
//! Constant EN - enable
#define CONST_UART_PDI_REGISTERS_UART_CFG_PAREN_EN 0x1

//! Field STOP - Additional Stop Bits
#define UART_PDI_REGISTERS_UART_CFG_STOP_POS 4
//! Field STOP - Additional Stop Bits
#define UART_PDI_REGISTERS_UART_CFG_STOP_MASK 0xF0u

//! Field CR_DIS - CR As Enter Disable
#define UART_PDI_REGISTERS_UART_CFG_CR_DIS_POS 8
//! Field CR_DIS - CR As Enter Disable
#define UART_PDI_REGISTERS_UART_CFG_CR_DIS_MASK 0x100u
//! Constant EN - CR as echoed enter is enabled.
#define CONST_UART_PDI_REGISTERS_UART_CFG_CR_DIS_EN 0x0
//! Constant DIS - CR as echoed enter is disabled.
#define CONST_UART_PDI_REGISTERS_UART_CFG_CR_DIS_DIS 0x1

//! Field LF_DIS - LF As Enter Disable
#define UART_PDI_REGISTERS_UART_CFG_LF_DIS_POS 9
//! Field LF_DIS - LF As Enter Disable
#define UART_PDI_REGISTERS_UART_CFG_LF_DIS_MASK 0x200u
//! Constant EN - LF as echoed enter is enabled.
#define CONST_UART_PDI_REGISTERS_UART_CFG_LF_DIS_EN 0x0
//! Constant DIS - LF as echoed enter is disabled.
#define CONST_UART_PDI_REGISTERS_UART_CFG_LF_DIS_DIS 0x1

//! @}

//! \defgroup UART_PDI_REGISTERS_UART_BD Register UART_PDI_REGISTERS_UART_BD - UART Baudrate Register
//! @{

//! Register Offset (relative)
#define UART_PDI_REGISTERS_UART_BD 0x4
//! Register Offset (absolute) for 1st Instance UART_PDI_REGISTERS
#define UART_PDI_REGISTERS_UART_PDI_REGISTERS_UART_BD 0x00D3DA04u

//! Register Reset Value
#define UART_PDI_REGISTERS_UART_BD_RST 0x00000DC6u

//! Field BD - Baudrate Divider
#define UART_PDI_REGISTERS_UART_BD_BD_POS 0
//! Field BD - Baudrate Divider
#define UART_PDI_REGISTERS_UART_BD_BD_MASK 0xFFFFu

//! @}

//! \defgroup UART_PDI_REGISTERS_UART_FDIV Register UART_PDI_REGISTERS_UART_FDIV - UART Baudrate Fractional Divider Register
//! @{

//! Register Offset (relative)
#define UART_PDI_REGISTERS_UART_FDIV 0x8
//! Register Offset (absolute) for 1st Instance UART_PDI_REGISTERS
#define UART_PDI_REGISTERS_UART_PDI_REGISTERS_UART_FDIV 0x00D3DA08u

//! Register Reset Value
#define UART_PDI_REGISTERS_UART_FDIV_RST 0x0000007Au

//! Field FDIV - Baudrate Fractional Divider
#define UART_PDI_REGISTERS_UART_FDIV_FDIV_POS 0
//! Field FDIV - Baudrate Fractional Divider
#define UART_PDI_REGISTERS_UART_FDIV_FDIV_MASK 0xFFu

//! @}

//! \defgroup UART_PDI_REGISTERS_UART_PROMPT Register UART_PDI_REGISTERS_UART_PROMPT - UART PROPMT Register
//! @{

//! Register Offset (relative)
#define UART_PDI_REGISTERS_UART_PROMPT 0xC
//! Register Offset (absolute) for 1st Instance UART_PDI_REGISTERS
#define UART_PDI_REGISTERS_UART_PDI_REGISTERS_UART_PROMPT 0x00D3DA0Cu

//! Register Reset Value
#define UART_PDI_REGISTERS_UART_PROMPT_RST 0x0000003Eu

//! Field PROMPT0 - First Prompt Character
#define UART_PDI_REGISTERS_UART_PROMPT_PROMPT0_POS 0
//! Field PROMPT0 - First Prompt Character
#define UART_PDI_REGISTERS_UART_PROMPT_PROMPT0_MASK 0xFFu

//! Field PROMPT1 - Second Prompt Character
#define UART_PDI_REGISTERS_UART_PROMPT_PROMPT1_POS 8
//! Field PROMPT1 - Second Prompt Character
#define UART_PDI_REGISTERS_UART_PROMPT_PROMPT1_MASK 0xFF00u

//! @}

//! \defgroup UART_PDI_REGISTERS_UART_ERRCNT Register UART_PDI_REGISTERS_UART_ERRCNT - UART Error Counter Register
//! @{

//! Register Offset (relative)
#define UART_PDI_REGISTERS_UART_ERRCNT 0x10
//! Register Offset (absolute) for 1st Instance UART_PDI_REGISTERS
#define UART_PDI_REGISTERS_UART_PDI_REGISTERS_UART_ERRCNT 0x00D3DA10u

//! Register Reset Value
#define UART_PDI_REGISTERS_UART_ERRCNT_RST 0x00000000u

//! Field ERRCNT - Error Counter
#define UART_PDI_REGISTERS_UART_ERRCNT_ERRCNT_POS 0
//! Field ERRCNT - Error Counter
#define UART_PDI_REGISTERS_UART_ERRCNT_ERRCNT_MASK 0xFFFFu

//! @}

//! @}

#endif
