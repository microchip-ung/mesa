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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/mspi_pdi_registers_def.xml
// Register File Name  : MSPI_PDI_REGISTERS
// Register File Title : Config Registers for Master SPI
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _MSPI_PDI_REGISTERS_H
#define _MSPI_PDI_REGISTERS_H

//! \defgroup MSPI_PDI_REGISTERS Register File MSPI_PDI_REGISTERS - Config Registers for Master SPI
//! @{

//! Base Address of MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MODULE_BASE 0x00D3D400u

//! \defgroup MSPI_PDI_REGISTERS_MSPI_CFG Register MSPI_PDI_REGISTERS_MSPI_CFG - SPI Master Interface Configuration Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_CFG 0x40
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_CFG 0x00D3D440u

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_CFG_RST 0x00009019u

//! Field CLKDIV - SPI Clock Divider
#define MSPI_PDI_REGISTERS_MSPI_CFG_CLKDIV_POS 0
//! Field CLKDIV - SPI Clock Divider
#define MSPI_PDI_REGISTERS_MSPI_CFG_CLKDIV_MASK 0xFFu

//! Field CLKEN - Clock Enable
#define MSPI_PDI_REGISTERS_MSPI_CFG_CLKEN_POS 12
//! Field CLKEN - Clock Enable
#define MSPI_PDI_REGISTERS_MSPI_CFG_CLKEN_MASK 0x1000u

//! Field ADDRMD - SPI Master Addressing Mode
#define MSPI_PDI_REGISTERS_MSPI_CFG_ADDRMD_POS 14
//! Field ADDRMD - SPI Master Addressing Mode
#define MSPI_PDI_REGISTERS_MSPI_CFG_ADDRMD_MASK 0xC000u
//! Constant BITS_24 - BITS_24
#define CONST_MSPI_PDI_REGISTERS_MSPI_CFG_ADDRMD_BITS_24 0x2
//! Constant BITS_24H - BITS_24H
#define CONST_MSPI_PDI_REGISTERS_MSPI_CFG_ADDRMD_BITS_24H 0x3

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_OP Register MSPI_PDI_REGISTERS_MSPI_OP - SPI Master Operating Mode Configuration Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_OP 0x44
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_OP 0x00D3D444u

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_OP_RST 0x00000000u

//! Field MDSEL - SPI Master Operation Mode Selection
#define MSPI_PDI_REGISTERS_MSPI_OP_MDSEL_POS 0
//! Field MDSEL - SPI Master Operation Mode Selection
#define MSPI_PDI_REGISTERS_MSPI_OP_MDSEL_MASK 0x1u
//! Constant AUTO - AUTO
#define CONST_MSPI_PDI_REGISTERS_MSPI_OP_MDSEL_AUTO 0x0
//! Constant MANU - MANU
#define CONST_MSPI_PDI_REGISTERS_MSPI_OP_MDSEL_MANU 0x1

//! Field MDSTA - SPI Master Operation Mode Status
#define MSPI_PDI_REGISTERS_MSPI_OP_MDSTA_POS 1
//! Field MDSTA - SPI Master Operation Mode Status
#define MSPI_PDI_REGISTERS_MSPI_OP_MDSTA_MASK 0x2u
//! Constant AUTO - AUTO
#define CONST_MSPI_PDI_REGISTERS_MSPI_OP_MDSTA_AUTO 0x0
//! Constant MANU - MANU
#define CONST_MSPI_PDI_REGISTERS_MSPI_OP_MDSTA_MANU 0x1

//! Field BUSY - SPI Master Transaction Ongoing
#define MSPI_PDI_REGISTERS_MSPI_OP_BUSY_POS 2
//! Field BUSY - SPI Master Transaction Ongoing
#define MSPI_PDI_REGISTERS_MSPI_OP_BUSY_MASK 0x4u
//! Constant IDLE - IDLE
#define CONST_MSPI_PDI_REGISTERS_MSPI_OP_BUSY_IDLE 0x0
//! Constant PEND - PEND
#define CONST_MSPI_PDI_REGISTERS_MSPI_OP_BUSY_PEND 0x1

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_MANCTRL Register MSPI_PDI_REGISTERS_MSPI_MANCTRL - SPI Master Manual Mode Control Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_MANCTRL 0x48
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_MANCTRL 0x00D3D448u

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_MANCTRL_RST 0x00000000u

//! Field SIZE - SPI Manual Mode Transaction Size
#define MSPI_PDI_REGISTERS_MSPI_MANCTRL_SIZE_POS 0
//! Field SIZE - SPI Manual Mode Transaction Size
#define MSPI_PDI_REGISTERS_MSPI_MANCTRL_SIZE_MASK 0x7u

//! Field START - SPI Manual Mode Transaction Start Request
#define MSPI_PDI_REGISTERS_MSPI_MANCTRL_START_POS 3
//! Field START - SPI Manual Mode Transaction Start Request
#define MSPI_PDI_REGISTERS_MSPI_MANCTRL_START_MASK 0x8u
//! Constant NIL - NIL
#define CONST_MSPI_PDI_REGISTERS_MSPI_MANCTRL_START_NIL 0x0
//! Constant START - START
#define CONST_MSPI_PDI_REGISTERS_MSPI_MANCTRL_START_START 0x1

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_ISR Register MSPI_PDI_REGISTERS_MSPI_ISR - SPI Master Interrupt Status Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_ISR 0x4C
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_ISR 0x00D3D44Cu

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_ISR_RST 0x00000000u

//! Field DONE - SPI Manual Operation Transaction Done
#define MSPI_PDI_REGISTERS_MSPI_ISR_DONE_POS 0
//! Field DONE - SPI Manual Operation Transaction Done
#define MSPI_PDI_REGISTERS_MSPI_ISR_DONE_MASK 0x1u
//! Constant NONE - NONE
#define CONST_MSPI_PDI_REGISTERS_MSPI_ISR_DONE_NONE 0x0
//! Constant DONE - DONE
#define CONST_MSPI_PDI_REGISTERS_MSPI_ISR_DONE_DONE 0x1

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_IER Register MSPI_PDI_REGISTERS_MSPI_IER - SPI Master Interrupt Enable Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_IER 0x50
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_IER 0x00D3D450u

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_IER_RST 0x00000000u

//! Field DONE - SPI 8-bit Access Done
#define MSPI_PDI_REGISTERS_MSPI_IER_DONE_POS 0
//! Field DONE - SPI 8-bit Access Done
#define MSPI_PDI_REGISTERS_MSPI_IER_DONE_MASK 0x1u
//! Constant DIS - DIS
#define CONST_MSPI_PDI_REGISTERS_MSPI_IER_DONE_DIS 0x0
//! Constant EN - EN
#define CONST_MSPI_PDI_REGISTERS_MSPI_IER_DONE_EN 0x1

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_FASTCTRL Register MSPI_PDI_REGISTERS_MSPI_FASTCTRL - SPI Master Manual Fast Mode Control Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_FASTCTRL 0x54
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_FASTCTRL 0x00D3D454u

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_FASTCTRL_RST 0x00000000u

//! Field FAST - SPI Manual Mode Fast Transaction Enable
#define MSPI_PDI_REGISTERS_MSPI_FASTCTRL_FAST_POS 0
//! Field FAST - SPI Manual Mode Fast Transaction Enable
#define MSPI_PDI_REGISTERS_MSPI_FASTCTRL_FAST_MASK 0x1u
//! Constant DIS - Normal Manual Mode Transaction
#define CONST_MSPI_PDI_REGISTERS_MSPI_FASTCTRL_FAST_DIS 0x0
//! Constant EN - Fast Transaction Enable
#define CONST_MSPI_PDI_REGISTERS_MSPI_FASTCTRL_FAST_EN 0x1

//! Field ACTIVE - SPI Manual Mode Fast Transaction Start/Stop
#define MSPI_PDI_REGISTERS_MSPI_FASTCTRL_ACTIVE_POS 1
//! Field ACTIVE - SPI Manual Mode Fast Transaction Start/Stop
#define MSPI_PDI_REGISTERS_MSPI_FASTCTRL_ACTIVE_MASK 0x2u
//! Constant OFF - Stop Transaction
#define CONST_MSPI_PDI_REGISTERS_MSPI_FASTCTRL_ACTIVE_OFF 0x0
//! Constant ON - Start Transaction
#define CONST_MSPI_PDI_REGISTERS_MSPI_FASTCTRL_ACTIVE_ON 0x1

//! Field ERROR - SPI Manual Fast Transaction Error
#define MSPI_PDI_REGISTERS_MSPI_FASTCTRL_ERROR_POS 2
//! Field ERROR - SPI Manual Fast Transaction Error
#define MSPI_PDI_REGISTERS_MSPI_FASTCTRL_ERROR_MASK 0x4u
//! Constant NONE - NONE
#define CONST_MSPI_PDI_REGISTERS_MSPI_FASTCTRL_ERROR_NONE 0x0
//! Constant ERR - ERROR
#define CONST_MSPI_PDI_REGISTERS_MSPI_FASTCTRL_ERROR_ERR 0x1

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_DOUT Register MSPI_PDI_REGISTERS_MSPI_DOUT - SPI Master Data Out Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_DOUT 0x58
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_DOUT 0x00D3D458u

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_DOUT_RST 0x00000000u

//! Field DATA - Data Out
#define MSPI_PDI_REGISTERS_MSPI_DOUT_DATA_POS 0
//! Field DATA - Data Out
#define MSPI_PDI_REGISTERS_MSPI_DOUT_DATA_MASK 0xFFFFu

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_PAGE Register MSPI_PDI_REGISTERS_MSPI_PAGE - SPI Master Interface Page Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_PAGE 0x5C
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_PAGE 0x00D3D45Cu

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_PAGE_RST 0x00000000u

//! Field PAGE - Page Number
#define MSPI_PDI_REGISTERS_MSPI_PAGE_PAGE_POS 0
//! Field PAGE - Page Number
#define MSPI_PDI_REGISTERS_MSPI_PAGE_PAGE_MASK 0xFFFFu

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_DIN01 Register MSPI_PDI_REGISTERS_MSPI_DIN01 - SPI Master Data In 0/1 Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_DIN01 0x60
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_DIN01 0x00D3D460u

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_DIN01_RST 0x00000000u

//! Field DIN1 - byte 1
#define MSPI_PDI_REGISTERS_MSPI_DIN01_DIN1_POS 0
//! Field DIN1 - byte 1
#define MSPI_PDI_REGISTERS_MSPI_DIN01_DIN1_MASK 0xFFu

//! Field DIN0 - byte 0
#define MSPI_PDI_REGISTERS_MSPI_DIN01_DIN0_POS 8
//! Field DIN0 - byte 0
#define MSPI_PDI_REGISTERS_MSPI_DIN01_DIN0_MASK 0xFF00u

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_DIN23 Register MSPI_PDI_REGISTERS_MSPI_DIN23 - SPI Master Data In 2/3 Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_DIN23 0x64
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_DIN23 0x00D3D464u

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_DIN23_RST 0x00000000u

//! Field DIN3 - byte
#define MSPI_PDI_REGISTERS_MSPI_DIN23_DIN3_POS 0
//! Field DIN3 - byte
#define MSPI_PDI_REGISTERS_MSPI_DIN23_DIN3_MASK 0xFFu

//! Field DIN2 - byte
#define MSPI_PDI_REGISTERS_MSPI_DIN23_DIN2_POS 8
//! Field DIN2 - byte
#define MSPI_PDI_REGISTERS_MSPI_DIN23_DIN2_MASK 0xFF00u

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_DIN45 Register MSPI_PDI_REGISTERS_MSPI_DIN45 - SPI Master Data In 4/5 Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_DIN45 0x68
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_DIN45 0x00D3D468u

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_DIN45_RST 0x00000000u

//! Field DIN5 - byte
#define MSPI_PDI_REGISTERS_MSPI_DIN45_DIN5_POS 0
//! Field DIN5 - byte
#define MSPI_PDI_REGISTERS_MSPI_DIN45_DIN5_MASK 0xFFu

//! Field DIN4 - byte
#define MSPI_PDI_REGISTERS_MSPI_DIN45_DIN4_POS 8
//! Field DIN4 - byte
#define MSPI_PDI_REGISTERS_MSPI_DIN45_DIN4_MASK 0xFF00u

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_DIN67 Register MSPI_PDI_REGISTERS_MSPI_DIN67 - SPI Master Data In 6/7Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_DIN67 0x6C
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_DIN67 0x00D3D46Cu

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_DIN67_RST 0x00000000u

//! Field DIN7 - byte
#define MSPI_PDI_REGISTERS_MSPI_DIN67_DIN7_POS 0
//! Field DIN7 - byte
#define MSPI_PDI_REGISTERS_MSPI_DIN67_DIN7_MASK 0xFFu

//! Field DIN6 - byte
#define MSPI_PDI_REGISTERS_MSPI_DIN67_DIN6_POS 8
//! Field DIN6 - byte
#define MSPI_PDI_REGISTERS_MSPI_DIN67_DIN6_MASK 0xFF00u

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_DOUT01 Register MSPI_PDI_REGISTERS_MSPI_DOUT01 - SPI Master Data Out 0/1 Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_DOUT01 0x70
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_DOUT01 0x00D3D470u

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_DOUT01_RST 0x00000000u

//! Field DOUT1 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT01_DOUT1_POS 0
//! Field DOUT1 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT01_DOUT1_MASK 0xFFu

//! Field DOUT0 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT01_DOUT0_POS 8
//! Field DOUT0 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT01_DOUT0_MASK 0xFF00u

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_DOUT23 Register MSPI_PDI_REGISTERS_MSPI_DOUT23 - SPI Master Data Out 2/3 Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_DOUT23 0x74
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_DOUT23 0x00D3D474u

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_DOUT23_RST 0x00000000u

//! Field DOUT3 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT23_DOUT3_POS 0
//! Field DOUT3 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT23_DOUT3_MASK 0xFFu

//! Field DOUT2 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT23_DOUT2_POS 8
//! Field DOUT2 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT23_DOUT2_MASK 0xFF00u

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_DOUT45 Register MSPI_PDI_REGISTERS_MSPI_DOUT45 - SPI Master Data Out 4/5 Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_DOUT45 0x78
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_DOUT45 0x00D3D478u

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_DOUT45_RST 0x00000000u

//! Field DOUT5 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT45_DOUT5_POS 0
//! Field DOUT5 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT45_DOUT5_MASK 0xFFu

//! Field DOUT4 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT45_DOUT4_POS 8
//! Field DOUT4 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT45_DOUT4_MASK 0xFF00u

//! @}

//! \defgroup MSPI_PDI_REGISTERS_MSPI_DOUT67 Register MSPI_PDI_REGISTERS_MSPI_DOUT67 - SPI Master Data Out 6/7 Register
//! @{

//! Register Offset (relative)
#define MSPI_PDI_REGISTERS_MSPI_DOUT67 0x7C
//! Register Offset (absolute) for 1st Instance MSPI_PDI_REGISTERS
#define MSPI_PDI_REGISTERS_MSPI_PDI_REGISTERS_MSPI_DOUT67 0x00D3D47Cu

//! Register Reset Value
#define MSPI_PDI_REGISTERS_MSPI_DOUT67_RST 0x00000000u

//! Field DOUT7 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT67_DOUT7_POS 0
//! Field DOUT7 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT67_DOUT7_MASK 0xFFu

//! Field DOUT6 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT67_DOUT6_POS 8
//! Field DOUT6 - byte
#define MSPI_PDI_REGISTERS_MSPI_DOUT67_DOUT6_MASK 0xFF00u

//! @}

//! @}

#endif
