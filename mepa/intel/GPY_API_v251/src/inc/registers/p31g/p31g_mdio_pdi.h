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
// LSD Source          : /home/p31g/p31g_chip/v_hksim.priv.p31g_chip.top/ipg_lsd/lsd_sys/source_mdio/xml/reg_files/p31g_mdio_pdi_def.xml
// Register File Name  : P31G_MDIO_PDI
// Register File Title : MDIO Master and Global Control and Status Registers
// Register Width      : 16
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _P31G_MDIO_PDI_H
#define _P31G_MDIO_PDI_H

//! \defgroup P31G_MDIO_PDI Register File P31G_MDIO_PDI - MDIO Master and Global Control and Status Registers
//! @{

//! Base Address of P31G_MDIO_PDI
#define P31G_MDIO_PDI_MODULE_BASE 0x0001E800u

//! \defgroup P31G_MDIO_PDI_GLOB_CTRL Register P31G_MDIO_PDI_GLOB_CTRL - Global Control Register 0
//! @{

//! Register Offset (relative)
#define P31G_MDIO_PDI_GLOB_CTRL 0x0
//! Register Offset (absolute) for 1st Instance P31G_MDIO_PDI
#define P31G_MDIO_PDI_P31G_MDIO_PDI_GLOB_CTRL 0x0001E800u

//! Register Reset Value
#define P31G_MDIO_PDI_GLOB_CTRL_RST 0x0100u

//! Field SWRES - Global PM Software Reset
#define P31G_MDIO_PDI_GLOB_CTRL_SWRES_POS 0
//! Field SWRES - Global PM Software Reset
#define P31G_MDIO_PDI_GLOB_CTRL_SWRES_MASK 0x1u
//! Constant OFF - reset is off
#define CONST_P31G_MDIO_PDI_GLOB_CTRL_SWRES_OFF 0x0
//! Constant ON - reset is active
#define CONST_P31G_MDIO_PDI_GLOB_CTRL_SWRES_ON 0x1

//! Field HWRES - Global PM Hardware Reset
#define P31G_MDIO_PDI_GLOB_CTRL_HWRES_POS 1
//! Field HWRES - Global PM Hardware Reset
#define P31G_MDIO_PDI_GLOB_CTRL_HWRES_MASK 0x2u
//! Constant OFF - reset is off
#define CONST_P31G_MDIO_PDI_GLOB_CTRL_HWRES_OFF 0x0
//! Constant ON - reset is active
#define CONST_P31G_MDIO_PDI_GLOB_CTRL_HWRES_ON 0x1

//! Field FXVL_EN - Global FXVL IP Enable
#define P31G_MDIO_PDI_GLOB_CTRL_FXVL_EN_POS 8
//! Field FXVL_EN - Global FXVL IP Enable
#define P31G_MDIO_PDI_GLOB_CTRL_FXVL_EN_MASK 0x100u
//! Constant DISABLE - Disable
#define CONST_P31G_MDIO_PDI_GLOB_CTRL_FXVL_EN_DISABLE 0x0
//! Constant ENABLE - Enable
#define CONST_P31G_MDIO_PDI_GLOB_CTRL_FXVL_EN_ENABLE 0x1

//! Field PM_EN - Global PM Enable
#define P31G_MDIO_PDI_GLOB_CTRL_PM_EN_POS 9
//! Field PM_EN - Global PM Enable
#define P31G_MDIO_PDI_GLOB_CTRL_PM_EN_MASK 0x200u
//! Constant DISABLE - Disable
#define CONST_P31G_MDIO_PDI_GLOB_CTRL_PM_EN_DISABLE 0x0
//! Constant ENABLE - Enable
#define CONST_P31G_MDIO_PDI_GLOB_CTRL_PM_EN_ENABLE 0x1

//! @}

//! \defgroup P31G_MDIO_PDI_MDIO_CTRL Register P31G_MDIO_PDI_MDIO_CTRL - MDIO Control Register
//! @{

//! Register Offset (relative)
#define P31G_MDIO_PDI_MDIO_CTRL 0x10
//! Register Offset (absolute) for 1st Instance P31G_MDIO_PDI
#define P31G_MDIO_PDI_P31G_MDIO_PDI_MDIO_CTRL 0x0001E810u

//! Register Reset Value
#define P31G_MDIO_PDI_MDIO_CTRL_RST 0x0000u

//! Field REGAD - Register Address
#define P31G_MDIO_PDI_MDIO_CTRL_REGAD_POS 0
//! Field REGAD - Register Address
#define P31G_MDIO_PDI_MDIO_CTRL_REGAD_MASK 0x1Fu

//! Field PHYAD - PHY Address
#define P31G_MDIO_PDI_MDIO_CTRL_PHYAD_POS 5
//! Field PHYAD - PHY Address
#define P31G_MDIO_PDI_MDIO_CTRL_PHYAD_MASK 0x3E0u

//! Field OP - Operation Code
#define P31G_MDIO_PDI_MDIO_CTRL_OP_POS 10
//! Field OP - Operation Code
#define P31G_MDIO_PDI_MDIO_CTRL_OP_MASK 0xC00u
//! Constant RES0 - reserved, do not use
#define CONST_P31G_MDIO_PDI_MDIO_CTRL_OP_RES0 0x0
//! Constant WR - write access
#define CONST_P31G_MDIO_PDI_MDIO_CTRL_OP_WR 0x1
//! Constant RD - read access
#define CONST_P31G_MDIO_PDI_MDIO_CTRL_OP_RD 0x2
//! Constant RES3 - reserved, do not use
#define CONST_P31G_MDIO_PDI_MDIO_CTRL_OP_RES3 0x3

//! Field MBUSY - MDIO Busy
#define P31G_MDIO_PDI_MDIO_CTRL_MBUSY_POS 12
//! Field MBUSY - MDIO Busy
#define P31G_MDIO_PDI_MDIO_CTRL_MBUSY_MASK 0x1000u
//! Constant RDY - the bus is available
#define CONST_P31G_MDIO_PDI_MDIO_CTRL_MBUSY_RDY 0x0
//! Constant BUSY - the bus is busy
#define CONST_P31G_MDIO_PDI_MDIO_CTRL_MBUSY_BUSY 0x1

//! @}

//! \defgroup P31G_MDIO_PDI_MDIO_READ Register P31G_MDIO_PDI_MDIO_READ - MDIO Read Data Register
//! @{

//! Register Offset (relative)
#define P31G_MDIO_PDI_MDIO_READ 0x12
//! Register Offset (absolute) for 1st Instance P31G_MDIO_PDI
#define P31G_MDIO_PDI_P31G_MDIO_PDI_MDIO_READ 0x0001E812u

//! Register Reset Value
#define P31G_MDIO_PDI_MDIO_READ_RST 0x0000u

//! Field RDATA - Read Data
#define P31G_MDIO_PDI_MDIO_READ_RDATA_POS 0
//! Field RDATA - Read Data
#define P31G_MDIO_PDI_MDIO_READ_RDATA_MASK 0xFFFFu

//! @}

//! \defgroup P31G_MDIO_PDI_MDIO_WRITE Register P31G_MDIO_PDI_MDIO_WRITE - MDIO Write Data Register
//! @{

//! Register Offset (relative)
#define P31G_MDIO_PDI_MDIO_WRITE 0x14
//! Register Offset (absolute) for 1st Instance P31G_MDIO_PDI
#define P31G_MDIO_PDI_P31G_MDIO_PDI_MDIO_WRITE 0x0001E814u

//! Register Reset Value
#define P31G_MDIO_PDI_MDIO_WRITE_RST 0x0000u

//! Field WDATA - Write Data
#define P31G_MDIO_PDI_MDIO_WRITE_WDATA_POS 0
//! Field WDATA - Write Data
#define P31G_MDIO_PDI_MDIO_WRITE_WDATA_MASK 0xFFFFu

//! @}

//! \defgroup P31G_MDIO_PDI_MDC_CFG_1 Register P31G_MDIO_PDI_MDC_CFG_1 - MDC Clock Configuration Register 1
//! @{

//! Register Offset (relative)
#define P31G_MDIO_PDI_MDC_CFG_1 0x18
//! Register Offset (absolute) for 1st Instance P31G_MDIO_PDI
#define P31G_MDIO_PDI_P31G_MDIO_PDI_MDC_CFG_1 0x0001E818u

//! Register Reset Value
#define P31G_MDIO_PDI_MDC_CFG_1_RST 0x0109u

//! Field FREQ - MDIO Interface Clock Rate
#define P31G_MDIO_PDI_MDC_CFG_1_FREQ_POS 0
//! Field FREQ - MDIO Interface Clock Rate
#define P31G_MDIO_PDI_MDC_CFG_1_FREQ_MASK 0xFFu
//! Constant S6 - 3.571 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S6 0x06u
//! Constant S1 - 12.50 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S1 0x01u
//! Constant S12 - 1.923 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S12 0x0Cu
//! Constant S13 - 1.786 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S13 0x0Du
//! Constant S11 - 2.083 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S11 0x0Bu
//! Constant S0 - 25.0 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S0 0x00u
//! Constant S9 - 2.500 MHz(default)
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S9 0x09u
//! Constant S10 - 2.273 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S10 0x0Au
//! Constant S4 - 5.000 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S4 0x04u
//! Constant S14 - 1.667 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S14 0x0Eu
//! Constant S8 - 2.778 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S8 0x08u
//! Constant S15 - 1.563 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S15 0x0Fu
//! Constant S2 - 8.333 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S2 0x02u
//! Constant S5 - 4.167 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S5 0x05u
//! Constant S255 - 97.6 kHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S255 0xFFu
//! Constant S7 - 3.125 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S7 0x07u
//! Constant S3 - 6.250 MHz
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_FREQ_S3 0x03u

//! Field MCEN - Management Clock Enable
#define P31G_MDIO_PDI_MDC_CFG_1_MCEN_POS 8
//! Field MCEN - Management Clock Enable
#define P31G_MDIO_PDI_MDC_CFG_1_MCEN_MASK 0x100u
//! Constant DIS - clock driver is disabled
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_MCEN_DIS 0x0
//! Constant EN - clock driver is enabled (default)
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_MCEN_EN 0x1

//! Field RES - MDIO Hardware Reset
#define P31G_MDIO_PDI_MDC_CFG_1_RES_POS 15
//! Field RES - MDIO Hardware Reset
#define P31G_MDIO_PDI_MDC_CFG_1_RES_MASK 0x8000u
//! Constant OFF - reset is off
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_RES_OFF 0x0
//! Constant ON - reset is active
#define CONST_P31G_MDIO_PDI_MDC_CFG_1_RES_ON 0x1

//! @}

//! @}

#endif
