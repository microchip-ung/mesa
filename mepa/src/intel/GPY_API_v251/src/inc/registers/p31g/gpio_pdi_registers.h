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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/gpio_pdi_registers_def.xml
// Register File Name  : GPIO_PDI_REGISTERS
// Register File Title : Config Registers GPIO
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _GPIO_PDI_REGISTERS_H
#define _GPIO_PDI_REGISTERS_H

//! \defgroup GPIO_PDI_REGISTERS Register File GPIO_PDI_REGISTERS - Config Registers GPIO
//! @{

//! Base Address of GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_MODULE_BASE 0x00D3CE00u

//! \defgroup GPIO_PDI_REGISTERS_GPIO_OUT Register GPIO_PDI_REGISTERS_GPIO_OUT - Data Output Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO_OUT 0x0
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_OUT 0x00D3CE00u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO_OUT_RST 0x00000000u

//! Field GPIO - GPIO OUT
#define GPIO_PDI_REGISTERS_GPIO_OUT_GPIO_POS 0
//! Field GPIO - GPIO OUT
#define GPIO_PDI_REGISTERS_GPIO_OUT_GPIO_MASK 0xFFFFu

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO_IN Register GPIO_PDI_REGISTERS_GPIO_IN - GPIO Data Input Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO_IN 0x4
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_IN 0x00D3CE04u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO_IN_RST 0x00000000u

//! Field GPIO - GPIO Input Value
#define GPIO_PDI_REGISTERS_GPIO_IN_GPIO_POS 0
//! Field GPIO - GPIO Input Value
#define GPIO_PDI_REGISTERS_GPIO_IN_GPIO_MASK 0xFFFFu
//! Constant LOW - LOW
#define CONST_GPIO_PDI_REGISTERS_GPIO_IN_GPIO_LOW 0x0000u
//! Constant HIGH - HIGH
#define CONST_GPIO_PDI_REGISTERS_GPIO_IN_GPIO_HIGH 0x0001u

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO_DIR Register GPIO_PDI_REGISTERS_GPIO_DIR - GPIO Direction Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO_DIR 0x8
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_DIR 0x00D3CE08u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO_DIR_RST 0x00000387u

//! Field GPIO - GPIO Direction Control
#define GPIO_PDI_REGISTERS_GPIO_DIR_GPIO_POS 0
//! Field GPIO - GPIO Direction Control
#define GPIO_PDI_REGISTERS_GPIO_DIR_GPIO_MASK 0xFFFFu
//! Constant IN - Input
#define CONST_GPIO_PDI_REGISTERS_GPIO_DIR_GPIO_IN 0x0000u
//! Constant OUT - Output
#define CONST_GPIO_PDI_REGISTERS_GPIO_DIR_GPIO_OUT 0x0001u

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO_ALTSEL0 Register GPIO_PDI_REGISTERS_GPIO_ALTSEL0 - Port 0 Alternate Function Select Register 0
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO_ALTSEL0 0xC
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_ALTSEL0 0x00D3CE0Cu

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO_ALTSEL0_RST 0x0000FFFFu

//! Field GPIO - GPIO Alternate Function Selection LSB
#define GPIO_PDI_REGISTERS_GPIO_ALTSEL0_GPIO_POS 0
//! Field GPIO - GPIO Alternate Function Selection LSB
#define GPIO_PDI_REGISTERS_GPIO_ALTSEL0_GPIO_MASK 0xFFFFu

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO_ALTSEL1 Register GPIO_PDI_REGISTERS_GPIO_ALTSEL1 - Port 0 Alternate Function Select Register 1
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO_ALTSEL1 0x10
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_ALTSEL1 0x00D3CE10u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO_ALTSEL1_RST 0x00000000u

//! Field GPIO - GPIO Alternate Function Selection MSB
#define GPIO_PDI_REGISTERS_GPIO_ALTSEL1_GPIO_POS 0
//! Field GPIO - GPIO Alternate Function Selection MSB
#define GPIO_PDI_REGISTERS_GPIO_ALTSEL1_GPIO_MASK 0xFFFFu

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO_OD Register GPIO_PDI_REGISTERS_GPIO_OD - GPIO Open Drain Control Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO_OD 0x14
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_OD 0x00D3CE14u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO_OD_RST 0x0000A7CFu

//! Field GPIO - GPIO Open Drain Mode
#define GPIO_PDI_REGISTERS_GPIO_OD_GPIO_POS 0
//! Field GPIO - GPIO Open Drain Mode
#define GPIO_PDI_REGISTERS_GPIO_OD_GPIO_MASK 0xFFFFu
//! Constant OD - Open Drain Mode
#define CONST_GPIO_PDI_REGISTERS_GPIO_OD_GPIO_OD 0x0000u
//! Constant PP - Normal Mode
#define CONST_GPIO_PDI_REGISTERS_GPIO_OD_GPIO_PP 0x0001u

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO_PUDSEL Register GPIO_PDI_REGISTERS_GPIO_PUDSEL - GPIO Pull-Up/Pull-Down Select Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO_PUDSEL 0x18
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_PUDSEL 0x00D3CE18u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO_PUDSEL_RST 0x0000FFFFu

//! Field GPIO - GPIO Pull Up/Down Mode
#define GPIO_PDI_REGISTERS_GPIO_PUDSEL_GPIO_POS 0
//! Field GPIO - GPIO Pull Up/Down Mode
#define GPIO_PDI_REGISTERS_GPIO_PUDSEL_GPIO_MASK 0xFFFFu
//! Constant PD - Pull Down
#define CONST_GPIO_PDI_REGISTERS_GPIO_PUDSEL_GPIO_PD 0x0000u
//! Constant PU - Pull Up
#define CONST_GPIO_PDI_REGISTERS_GPIO_PUDSEL_GPIO_PU 0x0001u

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO_PUDEN Register GPIO_PDI_REGISTERS_GPIO_PUDEN - GPIO Pull-Up/Pull-Down Enable Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO_PUDEN 0x1C
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_PUDEN 0x00D3CE1Cu

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO_PUDEN_RST 0x0000A7C8u

//! Field GPIO - GPIO Pull Up/Down Enable
#define GPIO_PDI_REGISTERS_GPIO_PUDEN_GPIO_POS 0
//! Field GPIO - GPIO Pull Up/Down Enable
#define GPIO_PDI_REGISTERS_GPIO_PUDEN_GPIO_MASK 0xFFFFu
//! Constant DIS - Disable
#define CONST_GPIO_PDI_REGISTERS_GPIO_PUDEN_GPIO_DIS 0x0000u
//! Constant EN - Enable
#define CONST_GPIO_PDI_REGISTERS_GPIO_PUDEN_GPIO_EN 0x0001u

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO2_OUT Register GPIO_PDI_REGISTERS_GPIO2_OUT - GPIO2 Data Output Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO2_OUT 0x20
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_OUT 0x00D3CE20u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO2_OUT_RST 0x00000000u

//! Field GPIO - GPIO Output Value
#define GPIO_PDI_REGISTERS_GPIO2_OUT_GPIO_POS 0
//! Field GPIO - GPIO Output Value
#define GPIO_PDI_REGISTERS_GPIO2_OUT_GPIO_MASK 0x7u
//! Constant LOW - LOW
#define CONST_GPIO_PDI_REGISTERS_GPIO2_OUT_GPIO_LOW 0x0
//! Constant HIGH - HIGH
#define CONST_GPIO_PDI_REGISTERS_GPIO2_OUT_GPIO_HIGH 0x1

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO2_IN Register GPIO_PDI_REGISTERS_GPIO2_IN - GPIO2 Data Input Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO2_IN 0x24
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_IN 0x00D3CE24u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO2_IN_RST 0x00000000u

//! Field GPIO - GPIO Input Value
#define GPIO_PDI_REGISTERS_GPIO2_IN_GPIO_POS 0
//! Field GPIO - GPIO Input Value
#define GPIO_PDI_REGISTERS_GPIO2_IN_GPIO_MASK 0x7u
//! Constant LOW - LOW
#define CONST_GPIO_PDI_REGISTERS_GPIO2_IN_GPIO_LOW 0x0
//! Constant HIGH - HIGH
#define CONST_GPIO_PDI_REGISTERS_GPIO2_IN_GPIO_HIGH 0x1

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO2_DIR Register GPIO_PDI_REGISTERS_GPIO2_DIR - GPIO2 Direction Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO2_DIR 0x28
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_DIR 0x00D3CE28u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO2_DIR_RST 0x00000002u

//! Field GPIO - GPIO Direction Control
#define GPIO_PDI_REGISTERS_GPIO2_DIR_GPIO_POS 0
//! Field GPIO - GPIO Direction Control
#define GPIO_PDI_REGISTERS_GPIO2_DIR_GPIO_MASK 0x7u
//! Constant IN - Input
#define CONST_GPIO_PDI_REGISTERS_GPIO2_DIR_GPIO_IN 0x0
//! Constant OUT - Output
#define CONST_GPIO_PDI_REGISTERS_GPIO2_DIR_GPIO_OUT 0x1

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO2_ALTSEL0 Register GPIO_PDI_REGISTERS_GPIO2_ALTSEL0 - Port 2 Alternate Function Select Register 0
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO2_ALTSEL0 0x2C
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_ALTSEL0 0x00D3CE2Cu

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO2_ALTSEL0_RST 0x00000007u

//! Field GPIO - GPIO Alternate Function Selection LSB
#define GPIO_PDI_REGISTERS_GPIO2_ALTSEL0_GPIO_POS 0
//! Field GPIO - GPIO Alternate Function Selection LSB
#define GPIO_PDI_REGISTERS_GPIO2_ALTSEL0_GPIO_MASK 0x7u

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO2_ALTSEL1 Register GPIO_PDI_REGISTERS_GPIO2_ALTSEL1 - Port 2 Alternate Function Select Register 1
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO2_ALTSEL1 0x30
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_ALTSEL1 0x00D3CE30u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO2_ALTSEL1_RST 0x00000000u

//! Field GPIO - GPIO Alternate Function Selection MSB
#define GPIO_PDI_REGISTERS_GPIO2_ALTSEL1_GPIO_POS 0
//! Field GPIO - GPIO Alternate Function Selection MSB
#define GPIO_PDI_REGISTERS_GPIO2_ALTSEL1_GPIO_MASK 0x7u

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO2_OD Register GPIO_PDI_REGISTERS_GPIO2_OD - GPIO2 Open Drain Control Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO2_OD 0x34
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_OD 0x00D3CE34u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO2_OD_RST 0x00000007u

//! Field GPIO - GPIO Open Drain Mode
#define GPIO_PDI_REGISTERS_GPIO2_OD_GPIO_POS 0
//! Field GPIO - GPIO Open Drain Mode
#define GPIO_PDI_REGISTERS_GPIO2_OD_GPIO_MASK 0x7u
//! Constant OD - Open Drain Mode
#define CONST_GPIO_PDI_REGISTERS_GPIO2_OD_GPIO_OD 0x0
//! Constant PP - Normal Mode
#define CONST_GPIO_PDI_REGISTERS_GPIO2_OD_GPIO_PP 0x1

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO2_PUDSEL Register GPIO_PDI_REGISTERS_GPIO2_PUDSEL - GPIO2 Pull-Up/Pull-Down Select Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO2_PUDSEL 0x38
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_PUDSEL 0x00D3CE38u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO2_PUDSEL_RST 0x00000007u

//! Field GPIO - GPIO Pull Up/Down Mode
#define GPIO_PDI_REGISTERS_GPIO2_PUDSEL_GPIO_POS 0
//! Field GPIO - GPIO Pull Up/Down Mode
#define GPIO_PDI_REGISTERS_GPIO2_PUDSEL_GPIO_MASK 0x7u
//! Constant PD - Pull Down
#define CONST_GPIO_PDI_REGISTERS_GPIO2_PUDSEL_GPIO_PD 0x0
//! Constant PU - Pull Up
#define CONST_GPIO_PDI_REGISTERS_GPIO2_PUDSEL_GPIO_PU 0x1

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO2_PUDEN Register GPIO_PDI_REGISTERS_GPIO2_PUDEN - GPIO2 Pull-Up/Pull-Down Enable Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO2_PUDEN 0x3C
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_PUDEN 0x00D3CE3Cu

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO2_PUDEN_RST 0x00000007u

//! Field GPIO - GPIO Pull Up/Down Enable
#define GPIO_PDI_REGISTERS_GPIO2_PUDEN_GPIO_POS 0
//! Field GPIO - GPIO Pull Up/Down Enable
#define GPIO_PDI_REGISTERS_GPIO2_PUDEN_GPIO_MASK 0x7u
//! Constant DIS - Disable
#define CONST_GPIO_PDI_REGISTERS_GPIO2_PUDEN_GPIO_DIS 0x0
//! Constant EN - Enable
#define CONST_GPIO_PDI_REGISTERS_GPIO2_PUDEN_GPIO_EN 0x1

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO_DRIVE0_CFG Register GPIO_PDI_REGISTERS_GPIO_DRIVE0_CFG - GPIO PAD Driver Strength 0 Control Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO_DRIVE0_CFG 0x40
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_DRIVE0_CFG 0x00D3CE40u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO_DRIVE0_CFG_RST 0x0000FFFFu

//! Field GPIO - GPIO PAD Drive Strength Bit 0
#define GPIO_PDI_REGISTERS_GPIO_DRIVE0_CFG_GPIO_POS 0
//! Field GPIO - GPIO PAD Drive Strength Bit 0
#define GPIO_PDI_REGISTERS_GPIO_DRIVE0_CFG_GPIO_MASK 0xFFFFu
//! Constant V2MA - 2mA
#define CONST_GPIO_PDI_REGISTERS_GPIO_DRIVE0_CFG_GPIO_V2MA 0x0000u
//! Constant V4MA - 4mA
#define CONST_GPIO_PDI_REGISTERS_GPIO_DRIVE0_CFG_GPIO_V4MA 0x0001u
//! Constant V8MA - 8mA
#define CONST_GPIO_PDI_REGISTERS_GPIO_DRIVE0_CFG_GPIO_V8MA 0x0002u
//! Constant V12MA - 12mA
#define CONST_GPIO_PDI_REGISTERS_GPIO_DRIVE0_CFG_GPIO_V12MA 0x0003u

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO_DRIVE1_CFG Register GPIO_PDI_REGISTERS_GPIO_DRIVE1_CFG - GPIO PAD Driver Strength 1 Control Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO_DRIVE1_CFG 0x44
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_DRIVE1_CFG 0x00D3CE44u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO_DRIVE1_CFG_RST 0x0000FFFFu

//! Field GPIO - GPIO PAD Drive Strength Bit 1
#define GPIO_PDI_REGISTERS_GPIO_DRIVE1_CFG_GPIO_POS 0
//! Field GPIO - GPIO PAD Drive Strength Bit 1
#define GPIO_PDI_REGISTERS_GPIO_DRIVE1_CFG_GPIO_MASK 0xFFFFu
//! Constant V2MA - 2mA
#define CONST_GPIO_PDI_REGISTERS_GPIO_DRIVE1_CFG_GPIO_V2MA 0x0000u
//! Constant V4MA - 4mA
#define CONST_GPIO_PDI_REGISTERS_GPIO_DRIVE1_CFG_GPIO_V4MA 0x0001u
//! Constant V8MA - 8mA
#define CONST_GPIO_PDI_REGISTERS_GPIO_DRIVE1_CFG_GPIO_V8MA 0x0002u
//! Constant V12MA - 12mA
#define CONST_GPIO_PDI_REGISTERS_GPIO_DRIVE1_CFG_GPIO_V12MA 0x0003u

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO_SLEW_CFG Register GPIO_PDI_REGISTERS_GPIO_SLEW_CFG - GPIO PAD Slew Control Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO_SLEW_CFG 0x48
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_SLEW_CFG 0x00D3CE48u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO_SLEW_CFG_RST 0x0000FFFFu

//! Field GPIO - GPIO PAD Slew Control
#define GPIO_PDI_REGISTERS_GPIO_SLEW_CFG_GPIO_POS 0
//! Field GPIO - GPIO PAD Slew Control
#define GPIO_PDI_REGISTERS_GPIO_SLEW_CFG_GPIO_MASK 0xFFFFu
//! Constant SLOW - Slow
#define CONST_GPIO_PDI_REGISTERS_GPIO_SLEW_CFG_GPIO_SLOW 0x0000u
//! Constant FAST - Fast
#define CONST_GPIO_PDI_REGISTERS_GPIO_SLEW_CFG_GPIO_FAST 0x0001u

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO_VOL_CFG Register GPIO_PDI_REGISTERS_GPIO_VOL_CFG - GPIO PAD Voltage Control Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO_VOL_CFG 0x4C
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_VOL_CFG 0x00D3CE4Cu

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO_VOL_CFG_RST 0x00000000u

//! Field PAD_VOL - GPIO PAD Voltage Supply Level
#define GPIO_PDI_REGISTERS_GPIO_VOL_CFG_PAD_VOL_POS 0
//! Field PAD_VOL - GPIO PAD Voltage Supply Level
#define GPIO_PDI_REGISTERS_GPIO_VOL_CFG_PAD_VOL_MASK 0xFu
//! Constant HIGH - min 2.5v
#define CONST_GPIO_PDI_REGISTERS_GPIO_VOL_CFG_PAD_VOL_HIGH 0x0
//! Constant LOW - max 1.8v
#define CONST_GPIO_PDI_REGISTERS_GPIO_VOL_CFG_PAD_VOL_LOW 0x1

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO2_DRIVE0_CFG Register GPIO_PDI_REGISTERS_GPIO2_DRIVE0_CFG - GPIO2 PAD Driver Strength 0 Control Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO2_DRIVE0_CFG 0x50
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_DRIVE0_CFG 0x00D3CE50u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO2_DRIVE0_CFG_RST 0x00000007u

//! Field GPIO2 - GPIO2 PAD Drive Strength Bit 0
#define GPIO_PDI_REGISTERS_GPIO2_DRIVE0_CFG_GPIO2_POS 0
//! Field GPIO2 - GPIO2 PAD Drive Strength Bit 0
#define GPIO_PDI_REGISTERS_GPIO2_DRIVE0_CFG_GPIO2_MASK 0x7u
//! Constant V2MA - 2mA
#define CONST_GPIO_PDI_REGISTERS_GPIO2_DRIVE0_CFG_GPIO2_V2MA 0x0
//! Constant V4MA - 4mA
#define CONST_GPIO_PDI_REGISTERS_GPIO2_DRIVE0_CFG_GPIO2_V4MA 0x1
//! Constant V8MA - 8mA
#define CONST_GPIO_PDI_REGISTERS_GPIO2_DRIVE0_CFG_GPIO2_V8MA 0x2
//! Constant V12MA - 12mA
#define CONST_GPIO_PDI_REGISTERS_GPIO2_DRIVE0_CFG_GPIO2_V12MA 0x3

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO2_DRIVE1_CFG Register GPIO_PDI_REGISTERS_GPIO2_DRIVE1_CFG - GPIO2 PAD Driver Strength 1 Control Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO2_DRIVE1_CFG 0x54
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_DRIVE1_CFG 0x00D3CE54u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO2_DRIVE1_CFG_RST 0x00000007u

//! Field GPIO2 - GPIO2 PAD Drive Strength Bit 1
#define GPIO_PDI_REGISTERS_GPIO2_DRIVE1_CFG_GPIO2_POS 0
//! Field GPIO2 - GPIO2 PAD Drive Strength Bit 1
#define GPIO_PDI_REGISTERS_GPIO2_DRIVE1_CFG_GPIO2_MASK 0x7u
//! Constant V2MA - 2mA
#define CONST_GPIO_PDI_REGISTERS_GPIO2_DRIVE1_CFG_GPIO2_V2MA 0x0
//! Constant V4MA - 4mA
#define CONST_GPIO_PDI_REGISTERS_GPIO2_DRIVE1_CFG_GPIO2_V4MA 0x1
//! Constant V8MA - 8mA
#define CONST_GPIO_PDI_REGISTERS_GPIO2_DRIVE1_CFG_GPIO2_V8MA 0x2
//! Constant V12MA - 12mA
#define CONST_GPIO_PDI_REGISTERS_GPIO2_DRIVE1_CFG_GPIO2_V12MA 0x3

//! @}

//! \defgroup GPIO_PDI_REGISTERS_GPIO2_SLEW_CFG Register GPIO_PDI_REGISTERS_GPIO2_SLEW_CFG - GPIO2 Slew Control Register
//! @{

//! Register Offset (relative)
#define GPIO_PDI_REGISTERS_GPIO2_SLEW_CFG 0x58
//! Register Offset (absolute) for 1st Instance GPIO_PDI_REGISTERS
#define GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_SLEW_CFG 0x00D3CE58u

//! Register Reset Value
#define GPIO_PDI_REGISTERS_GPIO2_SLEW_CFG_RST 0x00000007u

//! Field GPIO2 - GPIO PAD Slew Control
#define GPIO_PDI_REGISTERS_GPIO2_SLEW_CFG_GPIO2_POS 0
//! Field GPIO2 - GPIO PAD Slew Control
#define GPIO_PDI_REGISTERS_GPIO2_SLEW_CFG_GPIO2_MASK 0x7u
//! Constant SLOW - Slow
#define CONST_GPIO_PDI_REGISTERS_GPIO2_SLEW_CFG_GPIO2_SLOW 0x0
//! Constant FAST - Fast
#define CONST_GPIO_PDI_REGISTERS_GPIO2_SLEW_CFG_GPIO2_FAST 0x1

//! @}

//! @}

#endif
