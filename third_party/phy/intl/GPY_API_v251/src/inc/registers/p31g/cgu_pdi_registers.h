/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  For licensing information, see the file 'LICENSE'
  in the root folder of this software module.

INTEL CONFIDENTIAL

The source code contained or described herein and all documents related to the
source code ("Material") are owned by Intel Corporation or its suppliers or
licensors. Title to the Material remains with Intel Corporation or its suppliers
and licensors. The Material contains trade secrets and proprietary and
confidential information of Intel or its suppliers and licensors. The Material
is protected by worldwide copyright and trade secret laws and treaty provisions.
No part of the Material may be used, copied, reproduced, modified, published,
uploaded, posted, transmitted, distributed, or disclosed in any way without
Intel's prior express written permission.

No license under any patent, copyright, trade secret or other intellectual
property right is granted to or conferred upon you by disclosure or delivery of
the Materials, either expressly, by implication, inducement, estoppel or
otherwise. Any license under such intellectual property rights must be express
and approved by Intel in writing.

*******************************************************************************/
//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p31g/p31g_chip/v_hksim.priv.p31g_chip.top/ipg_lsd/lsd_sys/source_mdio/xml/reg_files/cgu_pdi_def.xml
// Register File Name  : CGU_PDI_REGISTERS
// Register File Title : CGU Module Level Registers
// Register Width      : 16
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _CGU_PDI_REGISTERS_H
#define _CGU_PDI_REGISTERS_H

//! \defgroup CGU_PDI_REGISTERS Register File CGU_PDI_REGISTERS - CGU Module Level Registers
//! @{

//! Base Address of CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_MODULE_BASE 0x00015400u

//! \defgroup CGU_CFG Register CGU_CFG - CGU Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_CFG 0x0
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_CGU_CFG 0x00015400u

//! Register Reset Value
#define CGU_CFG_RST 0x0000u

//! Field NCO1_CFG - NCO1 Configuration
#define CGU_CFG_NCO1_CFG_POS 0
//! Field NCO1_CFG - NCO1 Configuration
#define CGU_CFG_NCO1_CFG_MASK 0x7u
//! Constant DR10 - Data Rate is 10Mbps
#define CONST_CGU_CFG_NCO1_CFG_DR10 0x0
//! Constant DR100 - Data Rate is 100Mbps
#define CONST_CGU_CFG_NCO1_CFG_DR100 0x1
//! Constant DR1000 - Data Rate is 1000Mbps
#define CONST_CGU_CFG_NCO1_CFG_DR1000 0x2
//! Constant DR2500 - Data Rate is 2500Mbps
#define CONST_CGU_CFG_NCO1_CFG_DR2500 0x4

//! Field NCO1_SEL - NCO1 Select
#define CGU_CFG_NCO1_SEL_POS 3
//! Field NCO1_SEL - NCO1 Select
#define CGU_CFG_NCO1_SEL_MASK 0x8u
//! Constant GPHY - GPHY control
#define CONST_CGU_CFG_NCO1_SEL_GPHY 0x0
//! Constant REG - Register control
#define CONST_CGU_CFG_NCO1_SEL_REG 0x1

//! Field NCO2_CFG - NCO2 Configuration
#define CGU_CFG_NCO2_CFG_POS 4
//! Field NCO2_CFG - NCO2 Configuration
#define CGU_CFG_NCO2_CFG_MASK 0x70u
//! Constant DR10 - Data Rate is 10Mbps
#define CONST_CGU_CFG_NCO2_CFG_DR10 0x0
//! Constant DR100 - Data Rate is 100Mbps
#define CONST_CGU_CFG_NCO2_CFG_DR100 0x1
//! Constant DR1000 - Data Rate is 1000Mbps
#define CONST_CGU_CFG_NCO2_CFG_DR1000 0x2
//! Constant DR2500 - Data Rate is 2500Mbps
#define CONST_CGU_CFG_NCO2_CFG_DR2500 0x5

//! Field NCO2_SEL - NCO2 Select
#define CGU_CFG_NCO2_SEL_POS 7
//! Field NCO2_SEL - NCO2 Select
#define CGU_CFG_NCO2_SEL_MASK 0x80u
//! Constant SGMII - SGMII control
#define CONST_CGU_CFG_NCO2_SEL_SGMII 0x0
//! Constant REG - Register control
#define CONST_CGU_CFG_NCO2_SEL_REG 0x1

//! @}

//! \defgroup SYNCE_CONF Register SYNCE_CONF - Synchronous Ethernet Configuration Register
//! @{

//! Register Offset (relative)
#define SYNCE_CONF 0x2
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_SYNCE_CONF 0x00015402u

//! Register Reset Value
#define SYNCE_CONF_RST 0x0000u

//! Field SCLK_SEL - Synchronous Ethernet Master Reference Clock Selection
#define SYNCE_CONF_SCLK_SEL_POS 0
//! Field SCLK_SEL - Synchronous Ethernet Master Reference Clock Selection
#define SYNCE_CONF_SCLK_SEL_MASK 0x3u
//! Constant PHY - PHY
#define CONST_SYNCE_CONF_SCLK_SEL_PHY 0x0
//! Constant GPC0 - GPC0
#define CONST_SYNCE_CONF_SCLK_SEL_GPC0 0x1
//! Constant GPC1 - GPC1
#define CONST_SYNCE_CONF_SCLK_SEL_GPC1 0x2
//! Constant GPC2 - GPC2
#define CONST_SYNCE_CONF_SCLK_SEL_GPC2 0x3

//! Field INTIMER_SEL - Time Stamp Capture Input Signal Selection
#define SYNCE_CONF_INTIMER_SEL_POS 4
//! Field INTIMER_SEL - Time Stamp Capture Input Signal Selection
#define SYNCE_CONF_INTIMER_SEL_MASK 0x30u
//! Constant DIS - DIS
#define CONST_SYNCE_CONF_INTIMER_SEL_DIS 0x0
//! Constant GPC0 - GPC0
#define CONST_SYNCE_CONF_INTIMER_SEL_GPC0 0x1
//! Constant GPC1 - GPC1
#define CONST_SYNCE_CONF_INTIMER_SEL_GPC1 0x2
//! Constant GPC2 - GPC2
#define CONST_SYNCE_CONF_INTIMER_SEL_GPC2 0x3

//! @}

//! \defgroup GPC0_CONF Register GPC0_CONF - GPC0 Configuration Register
//! @{

//! Register Offset (relative)
#define GPC0_CONF 0x4
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_GPC0_CONF 0x00015404u

//! Register Reset Value
#define GPC0_CONF_RST 0x0005u

//! Field SEL - GPC Output Clock Selection
#define GPC0_CONF_SEL_POS 0
//! Field SEL - GPC Output Clock Selection
#define GPC0_CONF_SEL_MASK 0x7u
//! Constant GPHY - GPHY
#define CONST_GPC0_CONF_SEL_GPHY 0x0
//! Constant RES1 - Reserved
#define CONST_GPC0_CONF_SEL_RES1 0x1
//! Constant RES2 - Reserved
#define CONST_GPC0_CONF_SEL_RES2 0x2
//! Constant RES3 - Reserved
#define CONST_GPC0_CONF_SEL_RES3 0x3
//! Constant TIMEOUT - TIMEOUT
#define CONST_GPC0_CONF_SEL_TIMEOUT 0x4
//! Constant SYSCLK - SYSCLK
#define CONST_GPC0_CONF_SEL_SYSCLK 0x5
//! Constant XO - XO
#define CONST_GPC0_CONF_SEL_XO 0x6
//! Constant XL_OSC - XTAL-less Oscillator Clock
#define CONST_GPC0_CONF_SEL_XL_OSC 0x7

//! @}

//! \defgroup GPC1_CONF Register GPC1_CONF - GPC1 Configuration Register
//! @{

//! Register Offset (relative)
#define GPC1_CONF 0x6
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_GPC1_CONF 0x00015406u

//! Register Reset Value
#define GPC1_CONF_RST 0x0005u

//! Field SEL - GPC Output Clock Selection
#define GPC1_CONF_SEL_POS 0
//! Field SEL - GPC Output Clock Selection
#define GPC1_CONF_SEL_MASK 0x7u
//! Constant GPHY - GPHY
#define CONST_GPC1_CONF_SEL_GPHY 0x0
//! Constant RES1 - Reserved
#define CONST_GPC1_CONF_SEL_RES1 0x1
//! Constant RES2 - Reserved
#define CONST_GPC1_CONF_SEL_RES2 0x2
//! Constant RES3 - Reserved
#define CONST_GPC1_CONF_SEL_RES3 0x3
//! Constant TIMEOUT - TIMEOUT
#define CONST_GPC1_CONF_SEL_TIMEOUT 0x4
//! Constant SYSCLK - SYSCLK
#define CONST_GPC1_CONF_SEL_SYSCLK 0x5
//! Constant XO - XO
#define CONST_GPC1_CONF_SEL_XO 0x6
//! Constant XL_OSC - XTAL-less Oscillator Clock
#define CONST_GPC1_CONF_SEL_XL_OSC 0x7

//! @}

//! \defgroup GPC2_CONF Register GPC2_CONF - GPC2 Configuration Register
//! @{

//! Register Offset (relative)
#define GPC2_CONF 0x8
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_GPC2_CONF 0x00015408u

//! Register Reset Value
#define GPC2_CONF_RST 0x0005u

//! Field SEL - GPC Output Clock Selection
#define GPC2_CONF_SEL_POS 0
//! Field SEL - GPC Output Clock Selection
#define GPC2_CONF_SEL_MASK 0x7u
//! Constant GPHY - GPHY
#define CONST_GPC2_CONF_SEL_GPHY 0x0
//! Constant RES1 - Reserved
#define CONST_GPC2_CONF_SEL_RES1 0x1
//! Constant RES2 - Reserved
#define CONST_GPC2_CONF_SEL_RES2 0x2
//! Constant RES3 - Reserved
#define CONST_GPC2_CONF_SEL_RES3 0x3
//! Constant TIMEOUT - TIMEOUT
#define CONST_GPC2_CONF_SEL_TIMEOUT 0x4
//! Constant SYSCLK - SYSCLK
#define CONST_GPC2_CONF_SEL_SYSCLK 0x5
//! Constant XO - XO
#define CONST_GPC2_CONF_SEL_XO 0x6
//! Constant XL_OSC - XTAL-less Oscillator Clock
#define CONST_GPC2_CONF_SEL_XL_OSC 0x7

//! @}

//! \defgroup NCO1_LSB_2500 Register NCO1_LSB_2500 - NCO1 LSB Configuration Register
//! @{

//! Register Offset (relative)
#define NCO1_LSB_2500 0xA
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_NCO1_LSB_2500 0x0001540Au

//! Register Reset Value
#define NCO1_LSB_2500_RST 0xEC4Eu

//! Field NCO1_LSB - NCO1 LSB
#define NCO1_LSB_2500_NCO1_LSB_POS 0
//! Field NCO1_LSB - NCO1 LSB
#define NCO1_LSB_2500_NCO1_LSB_MASK 0xFFFFu

//! @}

//! \defgroup NCO1_MSB_2500 Register NCO1_MSB_2500 - NCO1 MSB Configuration Register
//! @{

//! Register Offset (relative)
#define NCO1_MSB_2500 0xC
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_NCO1_MSB_2500 0x0001540Cu

//! Register Reset Value
#define NCO1_MSB_2500_RST 0x00C4u

//! Field NCO1_MSB - NCO1 MSB
#define NCO1_MSB_2500_NCO1_MSB_POS 0
//! Field NCO1_MSB - NCO1 MSB
#define NCO1_MSB_2500_NCO1_MSB_MASK 0xFFu

//! @}

//! \defgroup NCO1_LSB_1000 Register NCO1_LSB_1000 - NCO1 LSB Configuration Register
//! @{

//! Register Offset (relative)
#define NCO1_LSB_1000 0xE
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_NCO1_LSB_1000 0x0001540Eu

//! Register Reset Value
#define NCO1_LSB_1000_RST 0xC4ECu

//! Field NCO1_LSB - NCO1 LSB
#define NCO1_LSB_1000_NCO1_LSB_POS 0
//! Field NCO1_LSB - NCO1 LSB
#define NCO1_LSB_1000_NCO1_LSB_MASK 0xFFFFu

//! @}

//! \defgroup NCO1_MSB_1000 Register NCO1_MSB_1000 - NCO1 MSB Configuration Register
//! @{

//! Register Offset (relative)
#define NCO1_MSB_1000 0x10
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_NCO1_MSB_1000 0x00015410u

//! Register Reset Value
#define NCO1_MSB_1000_RST 0x004Eu

//! Field NCO1_MSB - NCO1 MSB
#define NCO1_MSB_1000_NCO1_MSB_POS 0
//! Field NCO1_MSB - NCO1 MSB
#define NCO1_MSB_1000_NCO1_MSB_MASK 0xFFu

//! @}

//! \defgroup NCO2_LSB_2500 Register NCO2_LSB_2500 - NCO2 LSB Configuration Register
//! @{

//! Register Offset (relative)
#define NCO2_LSB_2500 0x12
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_NCO2_LSB_2500 0x00015412u

//! Register Reset Value
#define NCO2_LSB_2500_RST 0xEC4Eu

//! Field NCO2_LSB - NCO2 LSB
#define NCO2_LSB_2500_NCO2_LSB_POS 0
//! Field NCO2_LSB - NCO2 LSB
#define NCO2_LSB_2500_NCO2_LSB_MASK 0xFFFFu

//! @}

//! \defgroup NCO2_MSB_2500 Register NCO2_MSB_2500 - NCO2 MSB Configuration Register
//! @{

//! Register Offset (relative)
#define NCO2_MSB_2500 0x14
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_NCO2_MSB_2500 0x00015414u

//! Register Reset Value
#define NCO2_MSB_2500_RST 0x00C4u

//! Field NCO2_MSB - NCO2 MSB
#define NCO2_MSB_2500_NCO2_MSB_POS 0
//! Field NCO2_MSB - NCO2 MSB
#define NCO2_MSB_2500_NCO2_MSB_MASK 0xFFu

//! @}

//! \defgroup NCO2_LSB_1000 Register NCO2_LSB_1000 - NCO2 LSB Configuration Register
//! @{

//! Register Offset (relative)
#define NCO2_LSB_1000 0x16
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_NCO2_LSB_1000 0x00015416u

//! Register Reset Value
#define NCO2_LSB_1000_RST 0xC4ECu

//! Field NCO2_LSB - NCO2 LSB
#define NCO2_LSB_1000_NCO2_LSB_POS 0
//! Field NCO2_LSB - NCO2 LSB
#define NCO2_LSB_1000_NCO2_LSB_MASK 0xFFFFu

//! @}

//! \defgroup NCO2_MSB_1000 Register NCO2_MSB_1000 - NCO2 MSB Configuration Register
//! @{

//! Register Offset (relative)
#define NCO2_MSB_1000 0x18
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_NCO2_MSB_1000 0x00015418u

//! Register Reset Value
#define NCO2_MSB_1000_RST 0x004Eu

//! Field NCO2_MSB - NCO2 MSB
#define NCO2_MSB_1000_NCO2_MSB_POS 0
//! Field NCO2_MSB - NCO2 MSB
#define NCO2_MSB_1000_NCO2_MSB_MASK 0xFFu

//! @}

//! \defgroup NCO_CTRL Register NCO_CTRL - NCO Control
//! @{

//! Register Offset (relative)
#define NCO_CTRL 0x1A
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_NCO_CTRL 0x0001541Au

//! Register Reset Value
#define NCO_CTRL_RST 0x0000u

//! Field FORCE0 - Initialize NCO1 and NCO2 counter to 0
#define NCO_CTRL_FORCE0_POS 0
//! Field FORCE0 - Initialize NCO1 and NCO2 counter to 0
#define NCO_CTRL_FORCE0_MASK 0x1u
//! Constant NIL - NIL
#define CONST_NCO_CTRL_FORCE0_NIL 0x0
//! Constant ZERO - ZERO
#define CONST_NCO_CTRL_FORCE0_ZERO 0x1

//! Field SGMIISEL - SGMII Clock NCO Selection
#define NCO_CTRL_SGMIISEL_POS 1
//! Field SGMIISEL - SGMII Clock NCO Selection
#define NCO_CTRL_SGMIISEL_MASK 0x2u
//! Constant NCO1 - NCO1
#define CONST_NCO_CTRL_SGMIISEL_NCO1 0x0
//! Constant NCO2 - NCO2
#define CONST_NCO_CTRL_SGMIISEL_NCO2 0x1

//! Field SGMII_HSP - SGMII High Speed Selection
#define NCO_CTRL_SGMII_HSP_POS 2
//! Field SGMII_HSP - SGMII High Speed Selection
#define NCO_CTRL_SGMII_HSP_MASK 0x4u
//! Constant V1GBPS - 1Gbps
#define CONST_NCO_CTRL_SGMII_HSP_V1GBPS 0x0
//! Constant V2_5GBPS - 2_5Gbps
#define CONST_NCO_CTRL_SGMII_HSP_V2_5GBPS 0x1

//! @}

//! \defgroup NCO3_CFG Register NCO3_CFG - NCO3 Configuration Register
//! @{

//! Register Offset (relative)
#define NCO3_CFG 0x1C
//! Register Offset (absolute) for 1st Instance CGU_PDI_REGISTERS
#define CGU_PDI_REGISTERS_NCO3_CFG 0x0001541Cu

//! Register Reset Value
#define NCO3_CFG_RST 0x6064u

//! Field NCO3_CFG0 - NCO3 Configuration 0
#define NCO3_CFG_NCO3_CFG0_POS 0
//! Field NCO3_CFG0 - NCO3 Configuration 0
#define NCO3_CFG_NCO3_CFG0_MASK 0xFFu

//! Field NCO3_CFG1 - NCO3 Configuration 1
#define NCO3_CFG_NCO3_CFG1_POS 8
//! Field NCO3_CFG1 - NCO3 Configuration 1
#define NCO3_CFG_NCO3_CFG1_MASK 0xFF00u

//! @}

//! @}

#endif
