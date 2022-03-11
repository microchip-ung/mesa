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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/led_bctrl_pdi_registers_def.xml
// Register File Name  : LED_BCTRL_PDI_REGISTERS
// Register File Title : Config Registers for LED brightness control
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _LED_BCTRL_PDI_REGISTERS_H
#define _LED_BCTRL_PDI_REGISTERS_H

//! \defgroup LED_BCTRL_PDI_REGISTERS Register File LED_BCTRL_PDI_REGISTERS - Config Registers for LED brightness control
//! @{

//! Base Address of LED_BCTRL_PDI_REGISTERS
#define LED_BCTRL_PDI_REGISTERS_MODULE_BASE 0x00D3CF80u

//! \defgroup LED_BCTRL_PDI_REGISTERS_LED_MD_CFG Register LED_BCTRL_PDI_REGISTERS_LED_MD_CFG - LED Single color mode Configuration Register
//! @{

//! Register Offset (relative)
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG 0x0
//! Register Offset (absolute) for 1st Instance LED_BCTRL_PDI_REGISTERS
#define LED_BCTRL_PDI_REGISTERS_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG 0x00D3CF80u

//! Register Reset Value
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_RST 0x00000000u

//! Field LED0 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED0_POS 0
//! Field LED0 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED0_MASK 0x1u
//! Constant GROUND - LED connect to Ground
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED0_GROUND 0x0
//! Constant POWER - LED connect to POWER
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED0_POWER 0x1

//! Field LED1 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED1_POS 1
//! Field LED1 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED1_MASK 0x2u
//! Constant GROUND - LED connect to Ground
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED1_GROUND 0x0
//! Constant POWER - LED connect to POWER
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED1_POWER 0x1

//! Field LED2 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED2_POS 2
//! Field LED2 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED2_MASK 0x4u
//! Constant GROUND - LED connect to Ground
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED2_GROUND 0x0
//! Constant POWER - LED connect to POWER
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED2_POWER 0x1

//! Field LED3 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED3_POS 3
//! Field LED3 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED3_MASK 0x8u
//! Constant GROUND - LED connect to Ground
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED3_GROUND 0x0
//! Constant POWER - LED connect to POWER
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED3_POWER 0x1

//! Field LED4 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED4_POS 4
//! Field LED4 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED4_MASK 0x10u
//! Constant GROUND - LED connect to Ground
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED4_GROUND 0x0
//! Constant POWER - LED connect to POWER
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED4_POWER 0x1

//! Field LED5 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED5_POS 5
//! Field LED5 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED5_MASK 0x20u
//! Constant GROUND - LED connect to Ground
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED5_GROUND 0x0
//! Constant POWER - LED connect to POWER
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED5_POWER 0x1

//! Field LED6 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED6_POS 6
//! Field LED6 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED6_MASK 0x40u
//! Constant GROUND - LED connect to Ground
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED6_GROUND 0x0
//! Constant POWER - LED connect to POWER
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED6_POWER 0x1

//! Field LED7 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED7_POS 7
//! Field LED7 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED7_MASK 0x80u
//! Constant GROUND - LED connect to Ground
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED7_GROUND 0x0
//! Constant POWER - LED connect to POWER
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED7_POWER 0x1

//! Field LED8 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED8_POS 8
//! Field LED8 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED8_MASK 0x100u
//! Constant GROUND - LED connect to Ground
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED8_GROUND 0x0
//! Constant POWER - LED connect to POWER
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED8_POWER 0x1

//! Field LED9 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED9_POS 9
//! Field LED9 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED9_MASK 0x200u
//! Constant GROUND - LED connect to Ground
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED9_GROUND 0x0
//! Constant POWER - LED connect to POWER
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED9_POWER 0x1

//! Field LED10 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED10_POS 10
//! Field LED10 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED10_MASK 0x400u
//! Constant GROUND - LED connect to Ground
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED10_GROUND 0x0
//! Constant POWER - LED connect to POWER
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED10_POWER 0x1

//! Field LED11 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED11_POS 11
//! Field LED11 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED11_MASK 0x800u
//! Constant GROUND - LED connect to Ground
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED11_GROUND 0x0
//! Constant POWER - LED connect to POWER
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED11_POWER 0x1

//! Field LED12 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED12_POS 12
//! Field LED12 - LED Color Mode
#define LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED12_MASK 0x1000u
//! Constant GROUND - LED connect to Ground
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED12_GROUND 0x0
//! Constant POWER - LED connect to POWER
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_MD_CFG_LED12_POWER 0x1

//! @}

//! \defgroup LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL Register LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL - LED Brightness Control
//! @{

//! Register Offset (relative)
#define LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL 0x4
//! Register Offset (absolute) for 1st Instance LED_BCTRL_PDI_REGISTERS
#define LED_BCTRL_PDI_REGISTERS_LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL 0x00D3CF84u

//! Register Reset Value
#define LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_RST 0x0000F430u

//! Field TWOSWEN - LED Brightness 2 Level Switch Enable
#define LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_TWOSWEN_POS 4
//! Field TWOSWEN - LED Brightness 2 Level Switch Enable
#define LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_TWOSWEN_MASK 0x10u
//! Constant DISABLE - Disable
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_TWOSWEN_DISABLE 0x0
//! Constant ENABLE - Enable
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_TWOSWEN_ENABLE 0x1

//! Field EN - LED Brightness Control Enable
#define LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EN_POS 5
//! Field EN - LED Brightness Control Enable
#define LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EN_MASK 0x20u
//! Constant DISABLE - Disable
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EN_DISABLE 0x0
//! Constant ENABLE - Enable
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EN_ENABLE 0x1

//! Field EDGE_DET - Switch edge detect
#define LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EDGE_DET_POS 6
//! Field EDGE_DET - Switch edge detect
#define LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EDGE_DET_MASK 0x40u
//! Constant FALLING - Falling
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EDGE_DET_FALLING 0x0
//! Constant RISING - Rising
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EDGE_DET_RISING 0x1

//! Field MINLEVEL - Minimum LED Brightness Value
#define LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_MINLEVEL_POS 8
//! Field MINLEVEL - Minimum LED Brightness Value
#define LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_MINLEVEL_MASK 0xF00u

//! Field MAXLEVEL - Max LED Brightness Value
#define LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_MAXLEVEL_POS 12
//! Field MAXLEVEL - Max LED Brightness Value
#define LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_MAXLEVEL_MASK 0xF000u

//! @}

//! \defgroup LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL Register LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL - LED Light Sensing Control Register
//! @{

//! Register Offset (relative)
#define LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL 0x8
//! Register Offset (absolute) for 1st Instance LED_BCTRL_PDI_REGISTERS
#define LED_BCTRL_PDI_REGISTERS_LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL 0x00D3CF88u

//! Register Reset Value
#define LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_RST 0x00000D09u

//! Field PERIOD - LED Sensing Period
#define LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_PERIOD_POS 0
//! Field PERIOD - LED Sensing Period
#define LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_PERIOD_MASK 0x7u
//! Constant V1360 - 1360
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_PERIOD_V1360 0x0
//! Constant V680 - 680
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_PERIOD_V680 0x1
//! Constant V453 - 453
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_PERIOD_V453 0x2
//! Constant V340 - 340
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_PERIOD_V340 0x3
//! Constant V272 - 272
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_PERIOD_V272 0x4
//! Constant V226 - 226
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_PERIOD_V226 0x5
//! Constant V194 - 194
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_PERIOD_V194 0x6
//! Constant V170 - 170
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_PERIOD_V170 0x7

//! Field SENS_EN - Light Sensing Enable
#define LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_SENS_EN_POS 3
//! Field SENS_EN - Light Sensing Enable
#define LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_SENS_EN_MASK 0x8u
//! Constant DISABLE - Disable
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_SENS_EN_DISABLE 0x0
//! Constant ENABLE - Enable
#define CONST_LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_SENS_EN_ENABLE 0x1

//! Field CURLEVEL - Current Brightness Level
#define LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_CURLEVEL_POS 4
//! Field CURLEVEL - Current Brightness Level
#define LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_CURLEVEL_MASK 0xF0u

//! Field TD - The Number of Slots for Discharge
#define LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_TD_POS 8
//! Field TD - The Number of Slots for Discharge
#define LED_BCTRL_PDI_REGISTERS_LED_LSENS_CTRL_TD_MASK 0x3F00u

//! @}

//! @}

#endif
