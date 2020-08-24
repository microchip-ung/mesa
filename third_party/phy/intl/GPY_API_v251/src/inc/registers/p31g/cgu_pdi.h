//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/cgu_pdi_def.xml
// Register File Name  : CGU_PDI
// Register File Title : CGU Module Level Registers
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _CGU_PDI_H
#define _CGU_PDI_H

//! \defgroup CGU_PDI Register File CGU_PDI - CGU Module Level Registers
//! @{

//! Base Address of CGU_PDI
#define CGU_PDI_MODULE_BASE 0x00D29000u

//! \defgroup CGU_PDI_CGU_CFG Register CGU_PDI_CGU_CFG - CGU Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_CGU_CFG 0x0
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_CGU_CFG 0x00D29000u

//! Register Reset Value
#define CGU_PDI_CGU_CFG_RST 0x00000000u

//! Field NCO1_CFG - NCO1 Configuration
#define CGU_PDI_CGU_CFG_NCO1_CFG_POS 0
//! Field NCO1_CFG - NCO1 Configuration
#define CGU_PDI_CGU_CFG_NCO1_CFG_MASK 0x7u
//! Constant DR10 - Data Rate is 10Mbps
#define CONST_CGU_PDI_CGU_CFG_NCO1_CFG_DR10 0x0
//! Constant DR100 - Data Rate is 100Mbps
#define CONST_CGU_PDI_CGU_CFG_NCO1_CFG_DR100 0x1
//! Constant DR1000 - Data Rate is 1000Mbps
#define CONST_CGU_PDI_CGU_CFG_NCO1_CFG_DR1000 0x2
//! Constant DR2500 - Data Rate is 2500Mbps
#define CONST_CGU_PDI_CGU_CFG_NCO1_CFG_DR2500 0x4

//! Field NCO1_SEL - NCO1 Select
#define CGU_PDI_CGU_CFG_NCO1_SEL_POS 3
//! Field NCO1_SEL - NCO1 Select
#define CGU_PDI_CGU_CFG_NCO1_SEL_MASK 0x8u
//! Constant GPHY - GPHY control
#define CONST_CGU_PDI_CGU_CFG_NCO1_SEL_GPHY 0x0
//! Constant REG - Register control
#define CONST_CGU_PDI_CGU_CFG_NCO1_SEL_REG 0x1

//! Field NCO2_CFG - NCO2 Configuration
#define CGU_PDI_CGU_CFG_NCO2_CFG_POS 4
//! Field NCO2_CFG - NCO2 Configuration
#define CGU_PDI_CGU_CFG_NCO2_CFG_MASK 0x70u
//! Constant DR10 - Data Rate is 10Mbps
#define CONST_CGU_PDI_CGU_CFG_NCO2_CFG_DR10 0x0
//! Constant DR100 - Data Rate is 100Mbps
#define CONST_CGU_PDI_CGU_CFG_NCO2_CFG_DR100 0x1
//! Constant DR1000 - Data Rate is 1000Mbps
#define CONST_CGU_PDI_CGU_CFG_NCO2_CFG_DR1000 0x2
//! Constant DR2500 - Data Rate is 2500Mbps
#define CONST_CGU_PDI_CGU_CFG_NCO2_CFG_DR2500 0x5

//! Field NCO2_SEL - NCO2 Select
#define CGU_PDI_CGU_CFG_NCO2_SEL_POS 7
//! Field NCO2_SEL - NCO2 Select
#define CGU_PDI_CGU_CFG_NCO2_SEL_MASK 0x80u
//! Constant SGMII - SGMII control
#define CONST_CGU_PDI_CGU_CFG_NCO2_SEL_SGMII 0x0
//! Constant REG - Register control
#define CONST_CGU_PDI_CGU_CFG_NCO2_SEL_REG 0x1

//! @}

//! \defgroup CGU_PDI_SYNCE_CONF Register CGU_PDI_SYNCE_CONF - Synchronous Ethernet Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_SYNCE_CONF 0x4
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_SYNCE_CONF 0x00D29004u

//! Register Reset Value
#define CGU_PDI_SYNCE_CONF_RST 0x00000000u

//! Field SCLK_SEL - Synchronous Ethernet Master Reference Clock Selection
#define CGU_PDI_SYNCE_CONF_SCLK_SEL_POS 0
//! Field SCLK_SEL - Synchronous Ethernet Master Reference Clock Selection
#define CGU_PDI_SYNCE_CONF_SCLK_SEL_MASK 0x3u
//! Constant PHY - PHY
#define CONST_CGU_PDI_SYNCE_CONF_SCLK_SEL_PHY 0x0
//! Constant GPC0 - GPC0
#define CONST_CGU_PDI_SYNCE_CONF_SCLK_SEL_GPC0 0x1
//! Constant GPC1 - GPC1
#define CONST_CGU_PDI_SYNCE_CONF_SCLK_SEL_GPC1 0x2
//! Constant GPC2 - GPC2
#define CONST_CGU_PDI_SYNCE_CONF_SCLK_SEL_GPC2 0x3

//! Field INTIMER_SEL - Time Stamp Capture Input Signal Selection
#define CGU_PDI_SYNCE_CONF_INTIMER_SEL_POS 4
//! Field INTIMER_SEL - Time Stamp Capture Input Signal Selection
#define CGU_PDI_SYNCE_CONF_INTIMER_SEL_MASK 0x30u
//! Constant OUTTIMER - OUT TIMER
#define CONST_CGU_PDI_SYNCE_CONF_INTIMER_SEL_OUTTIMER 0x0
//! Constant GPC0 - GPC0
#define CONST_CGU_PDI_SYNCE_CONF_INTIMER_SEL_GPC0 0x1
//! Constant GPC1 - GPC1
#define CONST_CGU_PDI_SYNCE_CONF_INTIMER_SEL_GPC1 0x2
//! Constant GPC2 - GPC2
#define CONST_CGU_PDI_SYNCE_CONF_INTIMER_SEL_GPC2 0x3

//! @}

//! \defgroup CGU_PDI_GPC0_CONF Register CGU_PDI_GPC0_CONF - GPC0 Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_GPC0_CONF 0x8
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_GPC0_CONF 0x00D29008u

//! Register Reset Value
#define CGU_PDI_GPC0_CONF_RST 0x00000005u

//! Field SEL - GPC Output Clock Selection
#define CGU_PDI_GPC0_CONF_SEL_POS 0
//! Field SEL - GPC Output Clock Selection
#define CGU_PDI_GPC0_CONF_SEL_MASK 0x7u
//! Constant GPHY - GPHY
#define CONST_CGU_PDI_GPC0_CONF_SEL_GPHY 0x0
//! Constant RES1 - Reserved
#define CONST_CGU_PDI_GPC0_CONF_SEL_RES1 0x1
//! Constant RES2 - Reserved
#define CONST_CGU_PDI_GPC0_CONF_SEL_RES2 0x2
//! Constant RES3 - Reserved
#define CONST_CGU_PDI_GPC0_CONF_SEL_RES3 0x3
//! Constant OUTTIMER - OUT TIMER
#define CONST_CGU_PDI_GPC0_CONF_SEL_OUTTIMER 0x4
//! Constant SYSCLK - SYSCLK
#define CONST_CGU_PDI_GPC0_CONF_SEL_SYSCLK 0x5
//! Constant XO - XO
#define CONST_CGU_PDI_GPC0_CONF_SEL_XO 0x6
//! Constant XL_OSC - XTAL-less Oscillator Clock
#define CONST_CGU_PDI_GPC0_CONF_SEL_XL_OSC 0x7

//! Field DETECT - Detection
#define CGU_PDI_GPC0_CONF_DETECT_POS 4
//! Field DETECT - Detection
#define CGU_PDI_GPC0_CONF_DETECT_MASK 0x70u
//! Constant EDGELEVEL - Edge/Level Disable
#define CONST_CGU_PDI_GPC0_CONF_DETECT_EDGELEVEL 0x0
//! Constant RISING_EDGE - Rising Edge
#define CONST_CGU_PDI_GPC0_CONF_DETECT_RISING_EDGE 0x1
//! Constant FALLING_EDGE - Falling Edge
#define CONST_CGU_PDI_GPC0_CONF_DETECT_FALLING_EDGE 0x2
//! Constant RISINGFALLING_EDGE - Rising/Falling Edge
#define CONST_CGU_PDI_GPC0_CONF_DETECT_RISINGFALLING_EDGE 0x3
//! Constant RESERVED - Res
#define CONST_CGU_PDI_GPC0_CONF_DETECT_RESERVED 0x4
//! Constant HIGH_LEVEL - High Level
#define CONST_CGU_PDI_GPC0_CONF_DETECT_HIGH_LEVEL 0x5
//! Constant LOW_LEVEL - Low Level
#define CONST_CGU_PDI_GPC0_CONF_DETECT_LOW_LEVEL 0x6
//! Constant RES - Res
#define CONST_CGU_PDI_GPC0_CONF_DETECT_RES 0x7

//! @}

//! \defgroup CGU_PDI_GPC1_CONF Register CGU_PDI_GPC1_CONF - GPC1 Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_GPC1_CONF 0xC
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_GPC1_CONF 0x00D2900Cu

//! Register Reset Value
#define CGU_PDI_GPC1_CONF_RST 0x00000005u

//! Field SEL - GPC Output Clock Selection
#define CGU_PDI_GPC1_CONF_SEL_POS 0
//! Field SEL - GPC Output Clock Selection
#define CGU_PDI_GPC1_CONF_SEL_MASK 0x7u
//! Constant GPHY - GPHY
#define CONST_CGU_PDI_GPC1_CONF_SEL_GPHY 0x0
//! Constant RES1 - Reserved
#define CONST_CGU_PDI_GPC1_CONF_SEL_RES1 0x1
//! Constant RES2 - Reserved
#define CONST_CGU_PDI_GPC1_CONF_SEL_RES2 0x2
//! Constant RES3 - Reserved
#define CONST_CGU_PDI_GPC1_CONF_SEL_RES3 0x3
//! Constant OUTTIMER - OUT TIMER
#define CONST_CGU_PDI_GPC1_CONF_SEL_OUTTIMER 0x4
//! Constant SYSCLK - SYSCLK
#define CONST_CGU_PDI_GPC1_CONF_SEL_SYSCLK 0x5
//! Constant XO - XO
#define CONST_CGU_PDI_GPC1_CONF_SEL_XO 0x6
//! Constant XL_OSC - XTAL-less Oscillator Clock
#define CONST_CGU_PDI_GPC1_CONF_SEL_XL_OSC 0x7

//! Field DETECT - Detection
#define CGU_PDI_GPC1_CONF_DETECT_POS 4
//! Field DETECT - Detection
#define CGU_PDI_GPC1_CONF_DETECT_MASK 0x70u
//! Constant EDGELEVEL - Edge/Level Disable
#define CONST_CGU_PDI_GPC1_CONF_DETECT_EDGELEVEL 0x0
//! Constant RISING_EDGE - Rising Edge
#define CONST_CGU_PDI_GPC1_CONF_DETECT_RISING_EDGE 0x1
//! Constant FALLING_EDGE - Falling Edge
#define CONST_CGU_PDI_GPC1_CONF_DETECT_FALLING_EDGE 0x2
//! Constant RISINGFALLING_EDGE - Rising/Falling Edge
#define CONST_CGU_PDI_GPC1_CONF_DETECT_RISINGFALLING_EDGE 0x3
//! Constant RESERVED - Res
#define CONST_CGU_PDI_GPC1_CONF_DETECT_RESERVED 0x4
//! Constant HIGH_LEVEL - High Level
#define CONST_CGU_PDI_GPC1_CONF_DETECT_HIGH_LEVEL 0x5
//! Constant LOW_LEVEL - Low Level
#define CONST_CGU_PDI_GPC1_CONF_DETECT_LOW_LEVEL 0x6
//! Constant RES - Res
#define CONST_CGU_PDI_GPC1_CONF_DETECT_RES 0x7

//! @}

//! \defgroup CGU_PDI_GPC2_CONF Register CGU_PDI_GPC2_CONF - GPC2 Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_GPC2_CONF 0x10
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_GPC2_CONF 0x00D29010u

//! Register Reset Value
#define CGU_PDI_GPC2_CONF_RST 0x00000005u

//! Field SEL - GPC Output Clock Selection
#define CGU_PDI_GPC2_CONF_SEL_POS 0
//! Field SEL - GPC Output Clock Selection
#define CGU_PDI_GPC2_CONF_SEL_MASK 0x7u
//! Constant GPHY - GPHY
#define CONST_CGU_PDI_GPC2_CONF_SEL_GPHY 0x0
//! Constant RES1 - Reserved
#define CONST_CGU_PDI_GPC2_CONF_SEL_RES1 0x1
//! Constant RES2 - Reserved
#define CONST_CGU_PDI_GPC2_CONF_SEL_RES2 0x2
//! Constant RES3 - Reserved
#define CONST_CGU_PDI_GPC2_CONF_SEL_RES3 0x3
//! Constant OUTTIMER - OUT TIMER
#define CONST_CGU_PDI_GPC2_CONF_SEL_OUTTIMER 0x4
//! Constant SYSCLK - SYSCLK
#define CONST_CGU_PDI_GPC2_CONF_SEL_SYSCLK 0x5
//! Constant XO - XO
#define CONST_CGU_PDI_GPC2_CONF_SEL_XO 0x6
//! Constant XL_OSC - XTAL-less Oscillator Clock
#define CONST_CGU_PDI_GPC2_CONF_SEL_XL_OSC 0x7

//! Field DETECT - Detection
#define CGU_PDI_GPC2_CONF_DETECT_POS 4
//! Field DETECT - Detection
#define CGU_PDI_GPC2_CONF_DETECT_MASK 0x70u
//! Constant EDGELEVEL - Edge/Level Disable
#define CONST_CGU_PDI_GPC2_CONF_DETECT_EDGELEVEL 0x0
//! Constant RISING_EDGE - Rising Edge
#define CONST_CGU_PDI_GPC2_CONF_DETECT_RISING_EDGE 0x1
//! Constant FALLING_EDGE - Falling Edge
#define CONST_CGU_PDI_GPC2_CONF_DETECT_FALLING_EDGE 0x2
//! Constant RISINGFALLING_EDGE - Rising/Falling Edge
#define CONST_CGU_PDI_GPC2_CONF_DETECT_RISINGFALLING_EDGE 0x3
//! Constant RESERVED - Res
#define CONST_CGU_PDI_GPC2_CONF_DETECT_RESERVED 0x4
//! Constant HIGH_LEVEL - High Level
#define CONST_CGU_PDI_GPC2_CONF_DETECT_HIGH_LEVEL 0x5
//! Constant LOW_LEVEL - Low Level
#define CONST_CGU_PDI_GPC2_CONF_DETECT_LOW_LEVEL 0x6
//! Constant RES - Res
#define CONST_CGU_PDI_GPC2_CONF_DETECT_RES 0x7

//! @}

//! \defgroup CGU_PDI_NCO1_LSB_2500 Register CGU_PDI_NCO1_LSB_2500 - NCO1 LSB Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_NCO1_LSB_2500 0x14
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_NCO1_LSB_2500 0x00D29014u

//! Register Reset Value
#define CGU_PDI_NCO1_LSB_2500_RST 0x0000EC4Fu

//! Field NCO1_LSB - NCO1 LSB
#define CGU_PDI_NCO1_LSB_2500_NCO1_LSB_POS 0
//! Field NCO1_LSB - NCO1 LSB
#define CGU_PDI_NCO1_LSB_2500_NCO1_LSB_MASK 0xFFFFu

//! @}

//! \defgroup CGU_PDI_NCO1_MSB_2500 Register CGU_PDI_NCO1_MSB_2500 - NCO1 MSB Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_NCO1_MSB_2500 0x18
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_NCO1_MSB_2500 0x00D29018u

//! Register Reset Value
#define CGU_PDI_NCO1_MSB_2500_RST 0x000000C4u

//! Field NCO1_MSB - NCO1 MSB
#define CGU_PDI_NCO1_MSB_2500_NCO1_MSB_POS 0
//! Field NCO1_MSB - NCO1 MSB
#define CGU_PDI_NCO1_MSB_2500_NCO1_MSB_MASK 0xFFu

//! @}

//! \defgroup CGU_PDI_NCO1_LSB_1000 Register CGU_PDI_NCO1_LSB_1000 - NCO1 LSB Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_NCO1_LSB_1000 0x1C
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_NCO1_LSB_1000 0x00D2901Cu

//! Register Reset Value
#define CGU_PDI_NCO1_LSB_1000_RST 0x0000C4ECu

//! Field NCO1_LSB - NCO1 LSB
#define CGU_PDI_NCO1_LSB_1000_NCO1_LSB_POS 0
//! Field NCO1_LSB - NCO1 LSB
#define CGU_PDI_NCO1_LSB_1000_NCO1_LSB_MASK 0xFFFFu

//! @}

//! \defgroup CGU_PDI_NCO1_MSB_1000 Register CGU_PDI_NCO1_MSB_1000 - NCO1 MSB Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_NCO1_MSB_1000 0x20
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_NCO1_MSB_1000 0x00D29020u

//! Register Reset Value
#define CGU_PDI_NCO1_MSB_1000_RST 0x0000004Eu

//! Field NCO1_MSB - NCO1 MSB
#define CGU_PDI_NCO1_MSB_1000_NCO1_MSB_POS 0
//! Field NCO1_MSB - NCO1 MSB
#define CGU_PDI_NCO1_MSB_1000_NCO1_MSB_MASK 0xFFu

//! @}

//! \defgroup CGU_PDI_NCO2_LSB_2500 Register CGU_PDI_NCO2_LSB_2500 - NCO2 LSB Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_NCO2_LSB_2500 0x24
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_NCO2_LSB_2500 0x00D29024u

//! Register Reset Value
#define CGU_PDI_NCO2_LSB_2500_RST 0x0000EC4Fu

//! Field NCO2_LSB - NCO2 LSB
#define CGU_PDI_NCO2_LSB_2500_NCO2_LSB_POS 0
//! Field NCO2_LSB - NCO2 LSB
#define CGU_PDI_NCO2_LSB_2500_NCO2_LSB_MASK 0xFFFFu

//! @}

//! \defgroup CGU_PDI_NCO2_MSB_2500 Register CGU_PDI_NCO2_MSB_2500 - NCO2 MSB Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_NCO2_MSB_2500 0x28
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_NCO2_MSB_2500 0x00D29028u

//! Register Reset Value
#define CGU_PDI_NCO2_MSB_2500_RST 0x000000C4u

//! Field NCO2_MSB - NCO2 MSB
#define CGU_PDI_NCO2_MSB_2500_NCO2_MSB_POS 0
//! Field NCO2_MSB - NCO2 MSB
#define CGU_PDI_NCO2_MSB_2500_NCO2_MSB_MASK 0xFFu

//! @}

//! \defgroup CGU_PDI_NCO2_LSB_1000 Register CGU_PDI_NCO2_LSB_1000 - NCO2 LSB Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_NCO2_LSB_1000 0x2C
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_NCO2_LSB_1000 0x00D2902Cu

//! Register Reset Value
#define CGU_PDI_NCO2_LSB_1000_RST 0x0000C4ECu

//! Field NCO2_LSB - NCO2 LSB
#define CGU_PDI_NCO2_LSB_1000_NCO2_LSB_POS 0
//! Field NCO2_LSB - NCO2 LSB
#define CGU_PDI_NCO2_LSB_1000_NCO2_LSB_MASK 0xFFFFu

//! @}

//! \defgroup CGU_PDI_NCO2_MSB_1000 Register CGU_PDI_NCO2_MSB_1000 - NCO2 MSB Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_NCO2_MSB_1000 0x30
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_NCO2_MSB_1000 0x00D29030u

//! Register Reset Value
#define CGU_PDI_NCO2_MSB_1000_RST 0x0000004Eu

//! Field NCO2_MSB - NCO2 MSB
#define CGU_PDI_NCO2_MSB_1000_NCO2_MSB_POS 0
//! Field NCO2_MSB - NCO2 MSB
#define CGU_PDI_NCO2_MSB_1000_NCO2_MSB_MASK 0xFFu

//! @}

//! \defgroup CGU_PDI_NCO_CTRL Register CGU_PDI_NCO_CTRL - NCO Control
//! @{

//! Register Offset (relative)
#define CGU_PDI_NCO_CTRL 0x34
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_NCO_CTRL 0x00D29034u

//! Register Reset Value
#define CGU_PDI_NCO_CTRL_RST 0x00000000u

//! Field SGMIISEL - SGMII Clock NCO Selection
#define CGU_PDI_NCO_CTRL_SGMIISEL_POS 1
//! Field SGMIISEL - SGMII Clock NCO Selection
#define CGU_PDI_NCO_CTRL_SGMIISEL_MASK 0x2u
//! Constant NCO1 - NCO1
#define CONST_CGU_PDI_NCO_CTRL_SGMIISEL_NCO1 0x0
//! Constant NCO2 - NCO2
#define CONST_CGU_PDI_NCO_CTRL_SGMIISEL_NCO2 0x1

//! Field FORCE1 - Initialize NCO1 counter to 0
#define CGU_PDI_NCO_CTRL_FORCE1_POS 3
//! Field FORCE1 - Initialize NCO1 counter to 0
#define CGU_PDI_NCO_CTRL_FORCE1_MASK 0x8u
//! Constant NIL - NIL
#define CONST_CGU_PDI_NCO_CTRL_FORCE1_NIL 0x0
//! Constant ZERO - ZERO
#define CONST_CGU_PDI_NCO_CTRL_FORCE1_ZERO 0x1

//! Field FORCE2 - Initialize NCO2 counter to 0
#define CGU_PDI_NCO_CTRL_FORCE2_POS 4
//! Field FORCE2 - Initialize NCO2 counter to 0
#define CGU_PDI_NCO_CTRL_FORCE2_MASK 0x10u
//! Constant NIL - NIL
#define CONST_CGU_PDI_NCO_CTRL_FORCE2_NIL 0x0
//! Constant ZERO - ZERO
#define CONST_CGU_PDI_NCO_CTRL_FORCE2_ZERO 0x1

//! Field FORCE3 - Initialize NCO3 counter to 0
#define CGU_PDI_NCO_CTRL_FORCE3_POS 5
//! Field FORCE3 - Initialize NCO3 counter to 0
#define CGU_PDI_NCO_CTRL_FORCE3_MASK 0x20u
//! Constant NIL - NIL
#define CONST_CGU_PDI_NCO_CTRL_FORCE3_NIL 0x0
//! Constant ZERO - ZERO
#define CONST_CGU_PDI_NCO_CTRL_FORCE3_ZERO 0x1

//! Field NCO1_GATE - Clock Gate of NCO1
#define CGU_PDI_NCO_CTRL_NCO1_GATE_POS 6
//! Field NCO1_GATE - Clock Gate of NCO1
#define CGU_PDI_NCO_CTRL_NCO1_GATE_MASK 0x40u
//! Constant RUN - NCO1 Clock Not Gated
#define CONST_CGU_PDI_NCO_CTRL_NCO1_GATE_RUN 0x0
//! Constant GATE - Gate NCO1 Clock
#define CONST_CGU_PDI_NCO_CTRL_NCO1_GATE_GATE 0x1

//! Field NCO2_GATE - Clock Gate of NCO2
#define CGU_PDI_NCO_CTRL_NCO2_GATE_POS 7
//! Field NCO2_GATE - Clock Gate of NCO2
#define CGU_PDI_NCO_CTRL_NCO2_GATE_MASK 0x80u
//! Constant RUN - NCO2 Clock Not Gated
#define CONST_CGU_PDI_NCO_CTRL_NCO2_GATE_RUN 0x0
//! Constant GATE - Gate NCO2 Clock
#define CONST_CGU_PDI_NCO_CTRL_NCO2_GATE_GATE 0x1

//! @}

//! \defgroup CGU_PDI_NCO3_CFG Register CGU_PDI_NCO3_CFG - NCO3 Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_NCO3_CFG 0x38
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_NCO3_CFG 0x00D29038u

//! Register Reset Value
#define CGU_PDI_NCO3_CFG_RST 0x00006064u

//! Field NCO3_CFG0 - NCO3 Configuration 0
#define CGU_PDI_NCO3_CFG_NCO3_CFG0_POS 0
//! Field NCO3_CFG0 - NCO3 Configuration 0
#define CGU_PDI_NCO3_CFG_NCO3_CFG0_MASK 0xFFu

//! Field NCO3_CFG1 - NCO3 Configuration 1
#define CGU_PDI_NCO3_CFG_NCO3_CFG1_POS 8
//! Field NCO3_CFG1 - NCO3 Configuration 1
#define CGU_PDI_NCO3_CFG_NCO3_CFG1_MASK 0xFF00u

//! @}

//! @}

#endif
