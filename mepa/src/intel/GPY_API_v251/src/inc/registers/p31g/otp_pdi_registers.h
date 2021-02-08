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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/otp_pdi_def.xml
// Register File Name  : OTP_PDI_REGISTERS
// Register File Title : OTP Control Registers
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _OTP_PDI_REGISTERS_H
#define _OTP_PDI_REGISTERS_H

//! \defgroup OTP_PDI_REGISTERS Register File OTP_PDI_REGISTERS - OTP Control Registers
//! @{

//! Base Address of OTP_PDI_REGISTERS
#define OTP_PDI_REGISTERS_MODULE_BASE 0x00D3DB00u

//! \defgroup OTP_PDI_CTRL Register OTP_PDI_CTRL - OTP Interface Control Register
//! @{

//! Register Offset (relative)
#define OTP_PDI_CTRL 0x0
//! Register Offset (absolute) for 1st Instance OTP_PDI_REGISTERS
#define OTP_PDI_REGISTERS_OTP_PDI_CTRL 0x00D3DB00u

//! Register Reset Value
#define OTP_PDI_CTRL_RST 0x00000009u

//! Field DCTRL - Select User interface or PMC
#define OTP_PDI_CTRL_DCTRL_POS 0
//! Field DCTRL - Select User interface or PMC
#define OTP_PDI_CTRL_DCTRL_MASK 0x1u
//! Constant PMC - UI Disabled PMC is used
#define CONST_OTP_PDI_CTRL_DCTRL_PMC 0x0
//! Constant UI - User Interface Enabled
#define CONST_OTP_PDI_CTRL_DCTRL_UI 0x1

//! Field RST - Reset the SBPI and OTP controller
#define OTP_PDI_CTRL_RST_POS 1
//! Field RST - Reset the SBPI and OTP controller
#define OTP_PDI_CTRL_RST_MASK 0x2u
//! Constant DIS - No reset
#define CONST_OTP_PDI_CTRL_RST_DIS 0x0
//! Constant EN - Reset
#define CONST_OTP_PDI_CTRL_RST_EN 0x1

//! Field PD - Power Down
#define OTP_PDI_CTRL_PD_POS 2
//! Field PD - Power Down
#define OTP_PDI_CTRL_PD_MASK 0x4u
//! Constant NOPD - No Power Down
#define CONST_OTP_PDI_CTRL_PD_NOPD 0x0
//! Constant PD - Power Down
#define CONST_OTP_PDI_CTRL_PD_PD 0x1

//! Field SBPI_CLK_DIS - Clock Gate OTP Controller
#define OTP_PDI_CTRL_SBPI_CLK_DIS_POS 3
//! Field SBPI_CLK_DIS - Clock Gate OTP Controller
#define OTP_PDI_CTRL_SBPI_CLK_DIS_MASK 0x8u
//! Constant ENABLE - SBPI clock is ON
#define CONST_OTP_PDI_CTRL_SBPI_CLK_DIS_ENABLE 0x0
//! Constant DISABLE - SBPI clock is OFF
#define CONST_OTP_PDI_CTRL_SBPI_CLK_DIS_DISABLE 0x1

//! Field SLAVE_ID - SBPI Slave ID
#define OTP_PDI_CTRL_SLAVE_ID_POS 4
//! Field SLAVE_ID - SBPI Slave ID
#define OTP_PDI_CTRL_SLAVE_ID_MASK 0x10u
//! Constant PMC - PMC
#define CONST_OTP_PDI_CTRL_SLAVE_ID_PMC 0x0
//! Constant DAP - DAP
#define CONST_OTP_PDI_CTRL_SLAVE_ID_DAP 0x1

//! Field NB_DATA_XFER - Number of Data transfer in the transaction
#define OTP_PDI_CTRL_NB_DATA_XFER_POS 5
//! Field NB_DATA_XFER - Number of Data transfer in the transaction
#define OTP_PDI_CTRL_NB_DATA_XFER_MASK 0xFE0u

//! Field WAIT_FLAG - OTP Controller waits for FLAG before finishing SBPI transfer
#define OTP_PDI_CTRL_WAIT_FLAG_POS 12
//! Field WAIT_FLAG - OTP Controller waits for FLAG before finishing SBPI transfer
#define OTP_PDI_CTRL_WAIT_FLAG_MASK 0x1000u
//! Constant NO_WAIT - no wait for flag
#define CONST_OTP_PDI_CTRL_WAIT_FLAG_NO_WAIT 0x0
//! Constant WAIT - wait for flag
#define CONST_OTP_PDI_CTRL_WAIT_FLAG_WAIT 0x1

//! Field RNW - Read or Write
#define OTP_PDI_CTRL_RNW_POS 13
//! Field RNW - Read or Write
#define OTP_PDI_CTRL_RNW_MASK 0x2000u
//! Constant WRITE - Write Transaction
#define CONST_OTP_PDI_CTRL_RNW_WRITE 0x0
//! Constant READ - Read Transaction
#define CONST_OTP_PDI_CTRL_RNW_READ 0x1

//! Field CS_EXTEND - select CS behavior at the end of transfer
#define OTP_PDI_CTRL_CS_EXTEND_POS 14
//! Field CS_EXTEND - select CS behavior at the end of transfer
#define OTP_PDI_CTRL_CS_EXTEND_MASK 0x4000u
//! Constant NORMAL - NORMAL
#define CONST_OTP_PDI_CTRL_CS_EXTEND_NORMAL 0x0
//! Constant EXTENDED - Extended
#define CONST_OTP_PDI_CTRL_CS_EXTEND_EXTENDED 0x1

//! Field SBPI_BUSY - Transaction Status Bit Status
#define OTP_PDI_CTRL_SBPI_BUSY_POS 15
//! Field SBPI_BUSY - Transaction Status Bit Status
#define OTP_PDI_CTRL_SBPI_BUSY_MASK 0x8000u
//! Constant DONE - Transaction Complete
#define CONST_OTP_PDI_CTRL_SBPI_BUSY_DONE 0x0
//! Constant BUSY - Busy
#define CONST_OTP_PDI_CTRL_SBPI_BUSY_BUSY 0x1

//! @}

//! \defgroup OTP_PDI_WRITE_DATA Register OTP_PDI_WRITE_DATA - OTP Write Data Register
//! @{

//! Register Offset (relative)
#define OTP_PDI_WRITE_DATA 0x4
//! Register Offset (absolute) for 1st Instance OTP_PDI_REGISTERS
#define OTP_PDI_REGISTERS_OTP_PDI_WRITE_DATA 0x00D3DB04u

//! Register Reset Value
#define OTP_PDI_WRITE_DATA_RST 0x00000000u

//! Field OTP_WRITE_DATA - DATA to write to SBPI
#define OTP_PDI_WRITE_DATA_OTP_WRITE_DATA_POS 0
//! Field OTP_WRITE_DATA - DATA to write to SBPI
#define OTP_PDI_WRITE_DATA_OTP_WRITE_DATA_MASK 0xFFFFu

//! @}

//! \defgroup OTP_PDI_READ_DATA Register OTP_PDI_READ_DATA - OTP Read Data Register
//! @{

//! Register Offset (relative)
#define OTP_PDI_READ_DATA 0x8
//! Register Offset (absolute) for 1st Instance OTP_PDI_REGISTERS
#define OTP_PDI_REGISTERS_OTP_PDI_READ_DATA 0x00D3DB08u

//! Register Reset Value
#define OTP_PDI_READ_DATA_RST 0x00000000u

//! Field OTP_READ_DATA - Read Data for SBPI transaction
#define OTP_PDI_READ_DATA_OTP_READ_DATA_POS 0
//! Field OTP_READ_DATA - Read Data for SBPI transaction
#define OTP_PDI_READ_DATA_OTP_READ_DATA_MASK 0xFFFFu

//! @}

//! \defgroup OTP_PDI_CTRL2 Register OTP_PDI_CTRL2 - OTP Control Register 2
//! @{

//! Register Offset (relative)
#define OTP_PDI_CTRL2 0xC
//! Register Offset (absolute) for 1st Instance OTP_PDI_REGISTERS
#define OTP_PDI_REGISTERS_OTP_PDI_CTRL2 0x00D3DB0Cu

//! Register Reset Value
#define OTP_PDI_CTRL2_RST 0x00000000u

//! Field RES - Reserved
#define OTP_PDI_CTRL2_RES_POS 0
//! Field RES - Reserved
#define OTP_PDI_CTRL2_RES_MASK 0x1u

//! @}

//! \defgroup OTP_PDI_TIMING Register OTP_PDI_TIMING - AHB2OTP bridge timing
//! @{

//! Register Offset (relative)
#define OTP_PDI_TIMING 0x10
//! Register Offset (absolute) for 1st Instance OTP_PDI_REGISTERS
#define OTP_PDI_REGISTERS_OTP_PDI_TIMING 0x00D3DB10u

//! Register Reset Value
#define OTP_PDI_TIMING_RST 0x00000032u

//! Field CK_TIME_HIGH - Access Strobe High Time
#define OTP_PDI_TIMING_CK_TIME_HIGH_POS 0
//! Field CK_TIME_HIGH - Access Strobe High Time
#define OTP_PDI_TIMING_CK_TIME_HIGH_MASK 0xFu

//! Field CK_TIME_LOW - Access Strobe Low Time
#define OTP_PDI_TIMING_CK_TIME_LOW_POS 4
//! Field CK_TIME_LOW - Access Strobe Low Time
#define OTP_PDI_TIMING_CK_TIME_LOW_MASK 0xF0u

//! Field SEL_HOLD - Macro Selection Hold Time
#define OTP_PDI_TIMING_SEL_HOLD_POS 8
//! Field SEL_HOLD - Macro Selection Hold Time
#define OTP_PDI_TIMING_SEL_HOLD_MASK 0xF00u

//! Field DATA_RDY_HOLD - Hold time of data ready
#define OTP_PDI_TIMING_DATA_RDY_HOLD_POS 12
//! Field DATA_RDY_HOLD - Hold time of data ready
#define OTP_PDI_TIMING_DATA_RDY_HOLD_MASK 0xF000u

//! @}

//! @}

#endif
