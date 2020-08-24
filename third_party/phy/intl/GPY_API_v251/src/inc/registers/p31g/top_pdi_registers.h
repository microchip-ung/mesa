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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/top_pdi_def.xml
// Register File Name  : TOP_PDI_REGISTERS
// Register File Title : Top Level Registers Description
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _TOP_PDI_REGISTERS_H
#define _TOP_PDI_REGISTERS_H

//! \defgroup TOP_PDI_REGISTERS Register File TOP_PDI_REGISTERS - Top Level Registers Description
//! @{

//! Base Address of TOP_PDI_REGISTERS
#define TOP_PDI_REGISTERS_MODULE_BASE 0x00D28800u

//! \defgroup TOP_CFG Register TOP_CFG - Top level configuration register
//! @{

//! Register Offset (relative)
#define TOP_CFG 0x0
//! Register Offset (absolute) for 1st Instance TOP_PDI_REGISTERS
#define TOP_PDI_REGISTERS_TOP_CFG 0x00D28800u

//! Register Reset Value
#define TOP_CFG_RST 0x00000000u

//! Field MDIO_SEL - MDIO Select
#define TOP_CFG_MDIO_SEL_POS 0
//! Field MDIO_SEL - MDIO Select
#define TOP_CFG_MDIO_SEL_MASK 0x1u
//! Constant FXVL - From FXVL IP
#define CONST_TOP_CFG_MDIO_SEL_FXVL 0x0
//! Constant PAD - From Pad
#define CONST_TOP_CFG_MDIO_SEL_PAD 0x1

//! Field GMII_SEL - GMII Select
#define TOP_CFG_GMII_SEL_POS 1
//! Field GMII_SEL - GMII Select
#define TOP_CFG_GMII_SEL_MASK 0x2u
//! Constant FXVL - Connect to FXVL IP
#define CONST_TOP_CFG_GMII_SEL_FXVL 0x0
//! Constant PM - Connect to PM
#define CONST_TOP_CFG_GMII_SEL_PM 0x1

//! Field PCS_SEL - PCS Select
#define TOP_CFG_PCS_SEL_POS 2
//! Field PCS_SEL - PCS Select
#define TOP_CFG_PCS_SEL_MASK 0x4u
//! Constant PCIE - Connect to PCIe PCS
#define CONST_TOP_CFG_PCS_SEL_PCIE 0x0
//! Constant SGMII - Connect to SGMII PCS
#define CONST_TOP_CFG_PCS_SEL_SGMII 0x1

//! Field SB_SEL - Shared Buffer Select
#define TOP_CFG_SB_SEL_POS 3
//! Field SB_SEL - Shared Buffer Select
#define TOP_CFG_SB_SEL_MASK 0x8u
//! Constant FXVL - FXVL IP has access to shared buffer
#define CONST_TOP_CFG_SB_SEL_FXVL 0x0
//! Constant PM - Packet Manager has access to shared buffer
#define CONST_TOP_CFG_SB_SEL_PM 0x1

//! Field SB0_SD - Shared Buffer 0 Shutdown
#define TOP_CFG_SB0_SD_POS 4
//! Field SB0_SD - Shared Buffer 0 Shutdown
#define TOP_CFG_SB0_SD_MASK 0x10u
//! Constant ON - Normal operation
#define CONST_TOP_CFG_SB0_SD_ON 0x0
//! Constant OFF - Shutdown mode
#define CONST_TOP_CFG_SB0_SD_OFF 0x1

//! Field SB1_SD - Shared Buffer 1 Shutdown
#define TOP_CFG_SB1_SD_POS 5
//! Field SB1_SD - Shared Buffer 1 Shutdown
#define TOP_CFG_SB1_SD_MASK 0x20u
//! Constant ON - Normal operation
#define CONST_TOP_CFG_SB1_SD_ON 0x0
//! Constant OFF - Shutdown mode
#define CONST_TOP_CFG_SB1_SD_OFF 0x1

//! Field FXVL_MEM_SD - FXVL Memory Shutdown
#define TOP_CFG_FXVL_MEM_SD_POS 6
//! Field FXVL_MEM_SD - FXVL Memory Shutdown
#define TOP_CFG_FXVL_MEM_SD_MASK 0x40u
//! Constant ON - Normal operation
#define CONST_TOP_CFG_FXVL_MEM_SD_ON 0x0
//! Constant OFF - Shutdown mode
#define CONST_TOP_CFG_FXVL_MEM_SD_OFF 0x1

//! Field SPI_SECURE_EN - SPI Security Enable
#define TOP_CFG_SPI_SECURE_EN_POS 7
//! Field SPI_SECURE_EN - SPI Security Enable
#define TOP_CFG_SPI_SECURE_EN_MASK 0x80u
//! Constant DIS - Security Disable
#define CONST_TOP_CFG_SPI_SECURE_EN_DIS 0x0
//! Constant EN - Security Enable
#define CONST_TOP_CFG_SPI_SECURE_EN_EN 0x1

//! @}

//! \defgroup TOP_STATUS Register TOP_STATUS - Top level Status register
//! @{

//! Register Offset (relative)
#define TOP_STATUS 0x4
//! Register Offset (absolute) for 1st Instance TOP_PDI_REGISTERS
#define TOP_PDI_REGISTERS_TOP_STATUS 0x00D28804u

//! Register Reset Value
#define TOP_STATUS_RST 0x00000000u

//! Field VOLT_OK - Voltage Ok
#define TOP_STATUS_VOLT_OK_POS 0
//! Field VOLT_OK - Voltage Ok
#define TOP_STATUS_VOLT_OK_MASK 0x1u
//! Constant NOK - Voltage 0.9V is not ok
#define CONST_TOP_STATUS_VOLT_OK_NOK 0x0
//! Constant OK - Voltage 0.9V is ok
#define CONST_TOP_STATUS_VOLT_OK_OK 0x1

//! Field DCDC_WP - DCDC Working Point
#define TOP_STATUS_DCDC_WP_POS 1
//! Field DCDC_WP - DCDC Working Point
#define TOP_STATUS_DCDC_WP_MASK 0x2u
//! Constant OFF - Working point is 0V
#define CONST_TOP_STATUS_DCDC_WP_OFF 0x0
//! Constant ON - Working point is 0.9V
#define CONST_TOP_STATUS_DCDC_WP_ON 0x1

//! Field DCPM_RDY - DCPM Ready
#define TOP_STATUS_DCPM_RDY_POS 2
//! Field DCPM_RDY - DCPM Ready
#define TOP_STATUS_DCPM_RDY_MASK 0x4u
//! Constant NRDY - 0.95V Power is not ready
#define CONST_TOP_STATUS_DCPM_RDY_NRDY 0x0
//! Constant RDY - 0.95V Power is ready
#define CONST_TOP_STATUS_DCPM_RDY_RDY 0x1

//! Field DCDC_WP_STRB - DCDC Working Point Strobe
#define TOP_STATUS_DCDC_WP_STRB_POS 3
//! Field DCDC_WP_STRB - DCDC Working Point Strobe
#define TOP_STATUS_DCDC_WP_STRB_MASK 0x8u
//! Constant NORMAL - No Strobe
#define CONST_TOP_STATUS_DCDC_WP_STRB_NORMAL 0x0
//! Constant STRB - Strobe
#define CONST_TOP_STATUS_DCDC_WP_STRB_STRB 0x1

//! Field PMU_FSM_STATE - PMU FSM State
#define TOP_STATUS_PMU_FSM_STATE_POS 4
//! Field PMU_FSM_STATE - PMU FSM State
#define TOP_STATUS_PMU_FSM_STATE_MASK 0x70u

//! @}

//! @}

#endif
