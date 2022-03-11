//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_emouchel.priv.p34x_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/chip_control/cgu_pdi_def.xml
// Register File Name  : CGU_PDI
// Register File Title : CHIP CGU Module Level Registers
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _CGU_PDI_GPY24X_H
#define _CGU_PDI_GPY24X_H

//! \defgroup CGU_PDI Register File CGU_PDI - CHIP CGU Module Level Registers
//! @{

//! Base Address of CGU_PDI
#define CGU_PDI_MODULE_BASE 0x00D29000u

//! \defgroup CGU_PDI_GPC0_OUT_CONF Register CGU_PDI_GPC0_OUT_CONF - GPC0 Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_GPC0_OUT_CONF 0x0
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_GPC0_OUT_CONF 0x00D29000u

//! Register Reset Value
#define CGU_PDI_GPC0_OUT_CONF_RST 0x00000005u

//! Field SEL - GPC Output Clock Selection
#define CGU_PDI_GPC0_OUT_CONF_SEL_POS 0
//! Field SEL - GPC Output Clock Selection
#define CGU_PDI_GPC0_OUT_CONF_SEL_MASK 0xFu
//! Constant PPS0 - SLICE_0_PPS_O
#define CONST_CGU_PDI_GPC0_OUT_CONF_SEL_PPS0 0x0
//! Constant PPS1 - SLICE_1_PPS_O
#define CONST_CGU_PDI_GPC0_OUT_CONF_SEL_PPS1 0x1
//! Constant PPS2 - SLICE_2_PPS_O
#define CONST_CGU_PDI_GPC0_OUT_CONF_SEL_PPS2 0x2
//! Constant PPS3 - SLICE_3_PPS_O
#define CONST_CGU_PDI_GPC0_OUT_CONF_SEL_PPS3 0x3
//! Constant SYNCE0 - OUT TIMER Slice 0
#define CONST_CGU_PDI_GPC0_OUT_CONF_SEL_SYNCE0 0x4
//! Constant SYNCE1 - OUT TIMER Slice 1
#define CONST_CGU_PDI_GPC0_OUT_CONF_SEL_SYNCE1 0x5
//! Constant SYNCE2 - OUT TIMER Slice 2
#define CONST_CGU_PDI_GPC0_OUT_CONF_SEL_SYNCE2 0x6
//! Constant SYNCE3 - OUT TIMER Slice 3
#define CONST_CGU_PDI_GPC0_OUT_CONF_SEL_SYNCE3 0x7
//! Constant SYSCLK_DIV8 - SYSCLK divide by 8 is 50.78 MHz
#define CONST_CGU_PDI_GPC0_OUT_CONF_SEL_SYSCLK_DIV8 0x8

//! @}

//! \defgroup CGU_PDI_GPC1_OUT_CONF Register CGU_PDI_GPC1_OUT_CONF - GPC1 Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_GPC1_OUT_CONF 0x4
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_GPC1_OUT_CONF 0x00D29004u

//! Register Reset Value
#define CGU_PDI_GPC1_OUT_CONF_RST 0x00000005u

//! Field SEL - GPC Output Clock Selection
#define CGU_PDI_GPC1_OUT_CONF_SEL_POS 0
//! Field SEL - GPC Output Clock Selection
#define CGU_PDI_GPC1_OUT_CONF_SEL_MASK 0xFu
//! Constant PPS0 - SLICE_0_PPS_O
#define CONST_CGU_PDI_GPC1_OUT_CONF_SEL_PPS0 0x0
//! Constant PPS1 - SLICE_1_PPS_O
#define CONST_CGU_PDI_GPC1_OUT_CONF_SEL_PPS1 0x1
//! Constant PPS2 - SLICE_2_PPS_O
#define CONST_CGU_PDI_GPC1_OUT_CONF_SEL_PPS2 0x2
//! Constant PPS3 - SLICE_3_PPS_O
#define CONST_CGU_PDI_GPC1_OUT_CONF_SEL_PPS3 0x3
//! Constant SYNCE0 - OUT TIMER Slice 0
#define CONST_CGU_PDI_GPC1_OUT_CONF_SEL_SYNCE0 0x4
//! Constant SYNCE1 - OUT TIMER Slice 1
#define CONST_CGU_PDI_GPC1_OUT_CONF_SEL_SYNCE1 0x5
//! Constant SYNCE2 - OUT TIMER Slice 2
#define CONST_CGU_PDI_GPC1_OUT_CONF_SEL_SYNCE2 0x6
//! Constant SYNCE3 - OUT TIMER Slice 3
#define CONST_CGU_PDI_GPC1_OUT_CONF_SEL_SYNCE3 0x7
//! Constant SYSCLK_DIV8 - SYSCLK divide by 8 is 50.78 MHz
#define CONST_CGU_PDI_GPC1_OUT_CONF_SEL_SYSCLK_DIV8 0x8

//! @}

//! \defgroup CGU_PDI_GPC2_OUT_CONF Register CGU_PDI_GPC2_OUT_CONF - GPC2 Configuration Register
//! @{

//! Register Offset (relative)
#define CGU_PDI_GPC2_OUT_CONF 0x8
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_GPC2_OUT_CONF 0x00D29008u

//! Register Reset Value
#define CGU_PDI_GPC2_OUT_CONF_RST 0x00000005u

//! Field SEL - GPC Output Clock Selection
#define CGU_PDI_GPC2_OUT_CONF_SEL_POS 0
//! Field SEL - GPC Output Clock Selection
#define CGU_PDI_GPC2_OUT_CONF_SEL_MASK 0xFu
//! Constant PPS0 - SLICE_0_PPS_O
#define CONST_CGU_PDI_GPC2_OUT_CONF_SEL_PPS0 0x0
//! Constant PPS1 - SLICE_1_PPS_O
#define CONST_CGU_PDI_GPC2_OUT_CONF_SEL_PPS1 0x1
//! Constant PPS2 - SLICE_2_PPS_O
#define CONST_CGU_PDI_GPC2_OUT_CONF_SEL_PPS2 0x2
//! Constant PPS3 - SLICE_3_PPS_O
#define CONST_CGU_PDI_GPC2_OUT_CONF_SEL_PPS3 0x3
//! Constant SYNCE0 - OUT TIMER Slice 0
#define CONST_CGU_PDI_GPC2_OUT_CONF_SEL_SYNCE0 0x4
//! Constant SYNCE1 - OUT TIMER Slice 1
#define CONST_CGU_PDI_GPC2_OUT_CONF_SEL_SYNCE1 0x5
//! Constant SYNCE2 - OUT TIMER Slice 2
#define CONST_CGU_PDI_GPC2_OUT_CONF_SEL_SYNCE2 0x6
//! Constant SYNCE3 - OUT TIMER Slice 3
#define CONST_CGU_PDI_GPC2_OUT_CONF_SEL_SYNCE3 0x7
//! Constant SYSCLK_DIV8 - SYSCLK divide by 8 is 50.78 MHz
#define CONST_CGU_PDI_GPC2_OUT_CONF_SEL_SYSCLK_DIV8 0x8

//! @}

//! \defgroup LJPLL_CFG0L Register LJPLL_CFG0L - LJ PLL3 Configuration Register 0
//! @{

//! Register Offset (relative)
#define LJPLL_CFG0L 0xC
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_LJPLL_CFG0L 0x00D2900Cu

//! Register Reset Value
#define LJPLL_CFG0L_RST 0x00000000u

//! Field PLLEN - PLL Enable
#define LJPLL_CFG0L_PLLEN_POS 0
//! Field PLLEN - PLL Enable
#define LJPLL_CFG0L_PLLEN_MASK 0x1u
//! Constant DIS - PLL Power Down (Disabled)
#define CONST_LJPLL_CFG0L_PLLEN_DIS 0x0
//! Constant EN - PLL Enabled
#define CONST_LJPLL_CFG0L_PLLEN_EN 0x1

//! Field LOCK - PLL Lock Status
#define LJPLL_CFG0L_LOCK_POS 1
//! Field LOCK - PLL Lock Status
#define LJPLL_CFG0L_LOCK_MASK 0x2u
//! Constant FREE - Free running
#define CONST_LJPLL_CFG0L_LOCK_FREE 0x0
//! Constant LOCK - Locked
#define CONST_LJPLL_CFG0L_LOCK_LOCK 0x1

//! Field FRACL - PLL Fractional Divider
#define LJPLL_CFG0L_FRACL_POS 2
//! Field FRACL - PLL Fractional Divider
#define LJPLL_CFG0L_FRACL_MASK 0xFFFCu

//! @}

//! \defgroup LJPLL_CFG0H Register LJPLL_CFG0H - LJ PLL3 Configuration Register 0
//! @{

//! Register Offset (relative)
#define LJPLL_CFG0H 0x10
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_LJPLL_CFG0H 0x00D29010u

//! Register Reset Value
#define LJPLL_CFG0H_RST 0x00000800u

//! Field FRACH - PLL Fractional Divider
#define LJPLL_CFG0H_FRACH_POS 0
//! Field FRACH - PLL Fractional Divider
#define LJPLL_CFG0H_FRACH_MASK 0x3FFu

//! Field DSMEN - Enable Delta-Sigma Modulator
#define LJPLL_CFG0H_DSMEN_POS 10
//! Field DSMEN - Enable Delta-Sigma Modulator
#define LJPLL_CFG0H_DSMEN_MASK 0x400u
//! Constant DIS
#define CONST_LJPLL_CFG0H_DSMEN_DIS 0x0
//! Constant EN
#define CONST_LJPLL_CFG0H_DSMEN_EN 0x1

//! Field DACEN - DAC Enable
#define LJPLL_CFG0H_DACEN_POS 11
//! Field DACEN - DAC Enable
#define LJPLL_CFG0H_DACEN_MASK 0x800u
//! Constant DISABLE - Disable
#define CONST_LJPLL_CFG0H_DACEN_DISABLE 0x0
//! Constant ENABLE - Enable
#define CONST_LJPLL_CFG0H_DACEN_ENABLE 0x1

//! Field UNLOCKED_EVENT - PLL unlocked since the last read of this register
#define LJPLL_CFG0H_UNLOCKED_EVENT_POS 12
//! Field UNLOCKED_EVENT - PLL unlocked since the last read of this register
#define LJPLL_CFG0H_UNLOCKED_EVENT_MASK 0x1000u
//! Constant NIL - No Unlock happened
#define CONST_LJPLL_CFG0H_UNLOCKED_EVENT_NIL 0x0
//! Constant UNLOCKED - PLL unlocked
#define CONST_LJPLL_CFG0H_UNLOCKED_EVENT_UNLOCKED 0x1

//! @}

//! \defgroup LJPLL_CFG1L Register LJPLL_CFG1L - LJ PLL3 Configuration Register 1
//! @{

//! Register Offset (relative)
#define LJPLL_CFG1L 0x14
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_LJPLL_CFG1L 0x00D29014u

//! Register Reset Value
#define LJPLL_CFG1L_RST 0x00000039u

//! Field POST_DIV0A - Post Divider 0A
#define LJPLL_CFG1L_POST_DIV0A_POS 0
//! Field POST_DIV0A - Post Divider 0A
#define LJPLL_CFG1L_POST_DIV0A_MASK 0x7u
//! Constant DIV1 - Divide by 1
#define CONST_LJPLL_CFG1L_POST_DIV0A_DIV1 0x0
//! Constant DIV2 - Divide by 2
#define CONST_LJPLL_CFG1L_POST_DIV0A_DIV2 0x1
//! Constant DIV3 - Divide by 3
#define CONST_LJPLL_CFG1L_POST_DIV0A_DIV3 0x2
//! Constant DIV4 - Divide by 4
#define CONST_LJPLL_CFG1L_POST_DIV0A_DIV4 0x3
//! Constant DIV5 - Divide by 5
#define CONST_LJPLL_CFG1L_POST_DIV0A_DIV5 0x4
//! Constant DIV6 - Divide by 6
#define CONST_LJPLL_CFG1L_POST_DIV0A_DIV6 0x5
//! Constant DIV7 - Divide by 7
#define CONST_LJPLL_CFG1L_POST_DIV0A_DIV7 0x6
//! Constant DIV8 - Divide by 8
#define CONST_LJPLL_CFG1L_POST_DIV0A_DIV8 0x7

//! Field POST_DIV0B - Post Divider 0B
#define LJPLL_CFG1L_POST_DIV0B_POS 3
//! Field POST_DIV0B - Post Divider 0B
#define LJPLL_CFG1L_POST_DIV0B_MASK 0x38u
//! Constant DIV1 - Divide by 1
#define CONST_LJPLL_CFG1L_POST_DIV0B_DIV1 0x0
//! Constant DIV2 - Divide by 2
#define CONST_LJPLL_CFG1L_POST_DIV0B_DIV2 0x1
//! Constant DIV3 - Divide by 3
#define CONST_LJPLL_CFG1L_POST_DIV0B_DIV3 0x2
//! Constant DIV4 - Divide by 4
#define CONST_LJPLL_CFG1L_POST_DIV0B_DIV4 0x3
//! Constant DIV5 - Divide by 5
#define CONST_LJPLL_CFG1L_POST_DIV0B_DIV5 0x4
//! Constant DIV6 - Divide by 6
#define CONST_LJPLL_CFG1L_POST_DIV0B_DIV6 0x5
//! Constant DIV7 - Divide by 7
#define CONST_LJPLL_CFG1L_POST_DIV0B_DIV7 0x6
//! Constant DIV8 - Divide by 8
#define CONST_LJPLL_CFG1L_POST_DIV0B_DIV8 0x7

//! Field POST_DIV1A - Post Divider 1A
#define LJPLL_CFG1L_POST_DIV1A_POS 6
//! Field POST_DIV1A - Post Divider 1A
#define LJPLL_CFG1L_POST_DIV1A_MASK 0x1C0u
//! Constant DIV1 - Divide by 1
#define CONST_LJPLL_CFG1L_POST_DIV1A_DIV1 0x0
//! Constant DIV2 - Divide by 2
#define CONST_LJPLL_CFG1L_POST_DIV1A_DIV2 0x1
//! Constant DIV3 - Divide by 3
#define CONST_LJPLL_CFG1L_POST_DIV1A_DIV3 0x2
//! Constant DIV4 - Divide by 4
#define CONST_LJPLL_CFG1L_POST_DIV1A_DIV4 0x3
//! Constant DIV5 - Divide by 5
#define CONST_LJPLL_CFG1L_POST_DIV1A_DIV5 0x4
//! Constant DIV6 - Divide by 6
#define CONST_LJPLL_CFG1L_POST_DIV1A_DIV6 0x5
//! Constant DIV7 - Divide by 7
#define CONST_LJPLL_CFG1L_POST_DIV1A_DIV7 0x6
//! Constant DIV8 - Divide by 8
#define CONST_LJPLL_CFG1L_POST_DIV1A_DIV8 0x7

//! Field POST_DIV1B - Post Divider 1B
#define LJPLL_CFG1L_POST_DIV1B_POS 9
//! Field POST_DIV1B - Post Divider 1B
#define LJPLL_CFG1L_POST_DIV1B_MASK 0xE00u
//! Constant DIV1 - Divide by 1
#define CONST_LJPLL_CFG1L_POST_DIV1B_DIV1 0x0
//! Constant DIV2 - Divide by 2
#define CONST_LJPLL_CFG1L_POST_DIV1B_DIV2 0x1
//! Constant DIV3 - Divide by 3
#define CONST_LJPLL_CFG1L_POST_DIV1B_DIV3 0x2
//! Constant DIV4 - Divide by 4
#define CONST_LJPLL_CFG1L_POST_DIV1B_DIV4 0x3
//! Constant DIV5 - Divide by 5
#define CONST_LJPLL_CFG1L_POST_DIV1B_DIV5 0x4
//! Constant DIV6 - Divide by 6
#define CONST_LJPLL_CFG1L_POST_DIV1B_DIV6 0x5
//! Constant DIV7 - Divide by 7
#define CONST_LJPLL_CFG1L_POST_DIV1B_DIV7 0x6
//! Constant DIV8 - Divide by 8
#define CONST_LJPLL_CFG1L_POST_DIV1B_DIV8 0x7

//! Field POST_DIV2A - Post Divider 2A
#define LJPLL_CFG1L_POST_DIV2A_POS 12
//! Field POST_DIV2A - Post Divider 2A
#define LJPLL_CFG1L_POST_DIV2A_MASK 0x7000u
//! Constant DIV1 - Divide by 1
#define CONST_LJPLL_CFG1L_POST_DIV2A_DIV1 0x0
//! Constant DIV2 - Divide by 2
#define CONST_LJPLL_CFG1L_POST_DIV2A_DIV2 0x1
//! Constant DIV3 - Divide by 3
#define CONST_LJPLL_CFG1L_POST_DIV2A_DIV3 0x2
//! Constant DIV4 - Divide by 4
#define CONST_LJPLL_CFG1L_POST_DIV2A_DIV4 0x3
//! Constant DIV5 - Divide by 5
#define CONST_LJPLL_CFG1L_POST_DIV2A_DIV5 0x4
//! Constant DIV6 - Divide by 6
#define CONST_LJPLL_CFG1L_POST_DIV2A_DIV6 0x5
//! Constant DIV7 - Divide by 7
#define CONST_LJPLL_CFG1L_POST_DIV2A_DIV7 0x6
//! Constant DIV8 - Divide by 8
#define CONST_LJPLL_CFG1L_POST_DIV2A_DIV8 0x7

//! @}

//! \defgroup LJPLL_CFG1H Register LJPLL_CFG1H - LJ PLL3 Configuration Register 1
//! @{

//! Register Offset (relative)
#define LJPLL_CFG1H 0x18
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_LJPLL_CFG1H 0x00D29018u

//! Register Reset Value
#define LJPLL_CFG1H_RST 0x00000008u

//! Field POST_DIV2BH - Post Divider 2B
#define LJPLL_CFG1H_POST_DIV2BH_POS 0
//! Field POST_DIV2BH - Post Divider 2B
#define LJPLL_CFG1H_POST_DIV2BH_MASK 0x7u
//! Constant DIV1 - Divide by 1
#define CONST_LJPLL_CFG1H_POST_DIV2BH_DIV1 0x0
//! Constant DIV2 - Divide by 2
#define CONST_LJPLL_CFG1H_POST_DIV2BH_DIV2 0x1
//! Constant DIV3 - Divide by 3
#define CONST_LJPLL_CFG1H_POST_DIV2BH_DIV3 0x2
//! Constant DIV4 - Divide by 4
#define CONST_LJPLL_CFG1H_POST_DIV2BH_DIV4 0x3
//! Constant DIV5 - Divide by 5
#define CONST_LJPLL_CFG1H_POST_DIV2BH_DIV5 0x4
//! Constant DIV6 - Divide by 6
#define CONST_LJPLL_CFG1H_POST_DIV2BH_DIV6 0x5
//! Constant DIV7 - Divide by 7
#define CONST_LJPLL_CFG1H_POST_DIV2BH_DIV7 0x6
//! Constant DIV8 - Divide by 8
#define CONST_LJPLL_CFG1H_POST_DIV2BH_DIV8 0x7

//! Field FOUT0EN - PLL Clock Output 0 Enable
#define LJPLL_CFG1H_FOUT0EN_POS 3
//! Field FOUT0EN - PLL Clock Output 0 Enable
#define LJPLL_CFG1H_FOUT0EN_MASK 0x8u
//! Constant M0 - output power down
#define CONST_LJPLL_CFG1H_FOUT0EN_M0 0x0
//! Constant M1 - output enabled
#define CONST_LJPLL_CFG1H_FOUT0EN_M1 0x1

//! Field FOUT1EN - PLL Clock Output 1 Enable
#define LJPLL_CFG1H_FOUT1EN_POS 4
//! Field FOUT1EN - PLL Clock Output 1 Enable
#define LJPLL_CFG1H_FOUT1EN_MASK 0x10u
//! Constant M0 - output power down
#define CONST_LJPLL_CFG1H_FOUT1EN_M0 0x0
//! Constant M1 - output enabled
#define CONST_LJPLL_CFG1H_FOUT1EN_M1 0x1

//! Field FOUT2EN - PLL Clock Output 2 Enable
#define LJPLL_CFG1H_FOUT2EN_POS 5
//! Field FOUT2EN - PLL Clock Output 2 Enable
#define LJPLL_CFG1H_FOUT2EN_MASK 0x20u
//! Constant M0 - output power down
#define CONST_LJPLL_CFG1H_FOUT2EN_M0 0x0
//! Constant M1 - output enabled
#define CONST_LJPLL_CFG1H_FOUT2EN_M1 0x1

//! Field FOUT3EN - PLL Clock Output 3 Enable
#define LJPLL_CFG1H_FOUT3EN_POS 6
//! Field FOUT3EN - PLL Clock Output 3 Enable
#define LJPLL_CFG1H_FOUT3EN_MASK 0x40u
//! Constant M0 - output power down
#define CONST_LJPLL_CFG1H_FOUT3EN_M0 0x0
//! Constant M1 - output enabled
#define CONST_LJPLL_CFG1H_FOUT3EN_M1 0x1

//! Field POST_DIV3A - Post Divider 3A
#define LJPLL_CFG1H_POST_DIV3A_POS 7
//! Field POST_DIV3A - Post Divider 3A
#define LJPLL_CFG1H_POST_DIV3A_MASK 0x380u
//! Constant DIV1 - Divide by 1
#define CONST_LJPLL_CFG1H_POST_DIV3A_DIV1 0x0
//! Constant DIV2 - Divide by 2
#define CONST_LJPLL_CFG1H_POST_DIV3A_DIV2 0x1
//! Constant DIV3 - Divide by 3
#define CONST_LJPLL_CFG1H_POST_DIV3A_DIV3 0x2
//! Constant DIV4 - Divide by 4
#define CONST_LJPLL_CFG1H_POST_DIV3A_DIV4 0x3
//! Constant DIV5 - Divide by 5
#define CONST_LJPLL_CFG1H_POST_DIV3A_DIV5 0x4
//! Constant DIV6 - Divide by 6
#define CONST_LJPLL_CFG1H_POST_DIV3A_DIV6 0x5
//! Constant DIV7 - Divide by 7
#define CONST_LJPLL_CFG1H_POST_DIV3A_DIV7 0x6
//! Constant DIV8 - Divide by 8
#define CONST_LJPLL_CFG1H_POST_DIV3A_DIV8 0x7

//! Field POST_DIV3B - Post Divider 3B
#define LJPLL_CFG1H_POST_DIV3B_POS 10
//! Field POST_DIV3B - Post Divider 3B
#define LJPLL_CFG1H_POST_DIV3B_MASK 0x1C00u
//! Constant DIV1 - Divide by 1
#define CONST_LJPLL_CFG1H_POST_DIV3B_DIV1 0x0
//! Constant DIV2 - Divide by 2
#define CONST_LJPLL_CFG1H_POST_DIV3B_DIV2 0x1
//! Constant DIV3 - Divide by 3
#define CONST_LJPLL_CFG1H_POST_DIV3B_DIV3 0x2
//! Constant DIV4 - Divide by 4
#define CONST_LJPLL_CFG1H_POST_DIV3B_DIV4 0x3
//! Constant DIV5 - Divide by 5
#define CONST_LJPLL_CFG1H_POST_DIV3B_DIV5 0x4
//! Constant DIV6 - Divide by 6
#define CONST_LJPLL_CFG1H_POST_DIV3B_DIV6 0x5
//! Constant DIV7 - Divide by 7
#define CONST_LJPLL_CFG1H_POST_DIV3B_DIV7 0x6
//! Constant DIV8 - Divide by 8
#define CONST_LJPLL_CFG1H_POST_DIV3B_DIV8 0x7

//! Field POST_DIV0PRE - Enable for Pre-Divide for FOUTCML0N/P
#define LJPLL_CFG1H_POST_DIV0PRE_POS 13
//! Field POST_DIV0PRE - Enable for Pre-Divide for FOUTCML0N/P
#define LJPLL_CFG1H_POST_DIV0PRE_MASK 0x2000u
//! Constant DIS - Disable
#define CONST_LJPLL_CFG1H_POST_DIV0PRE_DIS 0x0
//! Constant EN - Enable
#define CONST_LJPLL_CFG1H_POST_DIV0PRE_EN 0x1

//! @}

//! \defgroup LJPLL_CFG2L Register LJPLL_CFG2L - LJ PLL3 Configuration Register 2
//! @{

//! Register Offset (relative)
#define LJPLL_CFG2L 0x1C
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_LJPLL_CFG2L 0x00D2901Cu

//! Register Reset Value
#define LJPLL_CFG2L_RST 0x00000190u

//! Field FBDIV - LJPLL Feedback Divider
#define LJPLL_CFG2L_FBDIV_POS 0
//! Field FBDIV - LJPLL Feedback Divider
#define LJPLL_CFG2L_FBDIV_MASK 0xFFFu

//! @}

//! \defgroup LJPLL_CFG2H Register LJPLL_CFG2H - LJ PLL3 Configuration Register 2
//! @{

//! Register Offset (relative)
#define LJPLL_CFG2H 0x20
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_LJPLL_CFG2H 0x00D29020u

//! Register Reset Value
#define LJPLL_CFG2H_RST 0x00000381u

//! Field REFDIV - PLL Reference Clock Input Divider
#define LJPLL_CFG2H_REFDIV_POS 0
//! Field REFDIV - PLL Reference Clock Input Divider
#define LJPLL_CFG2H_REFDIV_MASK 0x3Fu

//! Field BYPASS0 - FOUT0 Bypass
#define LJPLL_CFG2H_BYPASS0_POS 6
//! Field BYPASS0 - FOUT0 Bypass
#define LJPLL_CFG2H_BYPASS0_MASK 0x40u
//! Constant DIS - Disable Bypass
#define CONST_LJPLL_CFG2H_BYPASS0_DIS 0x0
//! Constant EN - Enable Bypass
#define CONST_LJPLL_CFG2H_BYPASS0_EN 0x1

//! Field BYPASS1 - FOUT1 Bypass
#define LJPLL_CFG2H_BYPASS1_POS 7
//! Field BYPASS1 - FOUT1 Bypass
#define LJPLL_CFG2H_BYPASS1_MASK 0x80u
//! Constant DIS - Disable Bypass
#define CONST_LJPLL_CFG2H_BYPASS1_DIS 0x0
//! Constant EN - Enable Bypass
#define CONST_LJPLL_CFG2H_BYPASS1_EN 0x1

//! Field BYPASS2 - FOUT2 Bypass
#define LJPLL_CFG2H_BYPASS2_POS 8
//! Field BYPASS2 - FOUT2 Bypass
#define LJPLL_CFG2H_BYPASS2_MASK 0x100u
//! Constant DIS - Disable Bypass
#define CONST_LJPLL_CFG2H_BYPASS2_DIS 0x0
//! Constant EN - Enable Bypass
#define CONST_LJPLL_CFG2H_BYPASS2_EN 0x1

//! Field BYPASS3 - FOUT3 Bypass
#define LJPLL_CFG2H_BYPASS3_POS 9
//! Field BYPASS3 - FOUT3 Bypass
#define LJPLL_CFG2H_BYPASS3_MASK 0x200u
//! Constant DIS - Disable Bypass
#define CONST_LJPLL_CFG2H_BYPASS3_DIS 0x0
//! Constant EN - Enable Bypass
#define CONST_LJPLL_CFG2H_BYPASS3_EN 0x1

//! Field FREFCMLEN - Enable Reference Clock CML Mode
#define LJPLL_CFG2H_FREFCMLEN_POS 10
//! Field FREFCMLEN - Enable Reference Clock CML Mode
#define LJPLL_CFG2H_FREFCMLEN_MASK 0x400u
//! Constant DIS - CMOS Mode
#define CONST_LJPLL_CFG2H_FREFCMLEN_DIS 0x0
//! Constant EN - CML Mode
#define CONST_LJPLL_CFG2H_FREFCMLEN_EN 0x1

//! @}

//! \defgroup LJPLL_CFG3L Register LJPLL_CFG3L - LJ PLL3 Configuration Register 3
//! @{

//! Register Offset (relative)
#define LJPLL_CFG3L 0x24
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_LJPLL_CFG3L 0x00D29024u

//! Register Reset Value
#define LJPLL_CFG3L_RST 0x00000000u

//! Field DSKCAIN - 12 b value for calibration override
#define LJPLL_CFG3L_DSKCAIN_POS 0
//! Field DSKCAIN - 12 b value for calibration override
#define LJPLL_CFG3L_DSKCAIN_MASK 0xFFFu

//! Field DSKCALOUTL - 12b value for calibration read out
#define LJPLL_CFG3L_DSKCALOUTL_POS 12
//! Field DSKCALOUTL - 12b value for calibration read out
#define LJPLL_CFG3L_DSKCALOUTL_MASK 0xF000u

//! @}

//! \defgroup LJPLL_CFG3H Register LJPLL_CFG3H - LJ PLL3 Configuration Register 3
//! @{

//! Register Offset (relative)
#define LJPLL_CFG3H 0x28
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_LJPLL_CFG3H 0x00D29028u

//! Register Reset Value
#define LJPLL_CFG3H_RST 0x00001000u

//! Field DSKCALOUTH - 12b value for calibration read out
#define LJPLL_CFG3H_DSKCALOUTH_POS 0
//! Field DSKCALOUTH - 12b value for calibration read out
#define LJPLL_CFG3H_DSKCALOUTH_MASK 0xFFu

//! Field DSKEWEN - Enable DSKEW Calibration
#define LJPLL_CFG3H_DSKEWEN_POS 8
//! Field DSKEWEN - Enable DSKEW Calibration
#define LJPLL_CFG3H_DSKEWEN_MASK 0x100u
//! Constant DIS - Disable
#define CONST_LJPLL_CFG3H_DSKEWEN_DIS 0x0
//! Constant EN - Enable
#define CONST_LJPLL_CFG3H_DSKEWEN_EN 0x1

//! Field DSKEWCALBP - Bypass DSKEW calibration
#define LJPLL_CFG3H_DSKEWCALBP_POS 9
//! Field DSKEWCALBP - Bypass DSKEW calibration
#define LJPLL_CFG3H_DSKEWCALBP_MASK 0x200u
//! Constant NBP - NO bypass
#define CONST_LJPLL_CFG3H_DSKEWCALBP_NBP 0x0
//! Constant BP - bypass DSKEW results
#define CONST_LJPLL_CFG3H_DSKEWCALBP_BP 0x1

//! Field FASTDSKEWCALEN - Enable FAST DSKEW CALIBRATION
#define LJPLL_CFG3H_FASTDSKEWCALEN_POS 10
//! Field FASTDSKEWCALEN - Enable FAST DSKEW CALIBRATION
#define LJPLL_CFG3H_FASTDSKEWCALEN_MASK 0x400u
//! Constant DIS - Disable
#define CONST_LJPLL_CFG3H_FASTDSKEWCALEN_DIS 0x0
//! Constant EN - Enable
#define CONST_LJPLL_CFG3H_FASTDSKEWCALEN_EN 0x1

//! Field DSKEWCALCNT - Programmable counter for dskew calibration loop
#define LJPLL_CFG3H_DSKEWCALCNT_POS 11
//! Field DSKEWCALCNT - Programmable counter for dskew calibration loop
#define LJPLL_CFG3H_DSKEWCALCNT_MASK 0x3800u

//! @}

//! \defgroup LJPLL_SSC_CTRLL Register LJPLL_SSC_CTRLL - LJ PLL3 SSC CTRL
//! @{

//! Register Offset (relative)
#define LJPLL_SSC_CTRLL 0x2C
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_LJPLL_SSC_CTRLL 0x00D2902Cu

//! Register Reset Value
#define LJPLL_SSC_CTRLL_RST 0x00000000u

//! Field EN - Enable
#define LJPLL_SSC_CTRLL_EN_POS 0
//! Field EN - Enable
#define LJPLL_SSC_CTRLL_EN_MASK 0x1u
//! Constant DIS - Disable
#define CONST_LJPLL_SSC_CTRLL_EN_DIS 0x0
//! Constant EN - Enable
#define CONST_LJPLL_SSC_CTRLL_EN_EN 0x1

//! Field INIT - Init
#define LJPLL_SSC_CTRLL_INIT_POS 1
//! Field INIT - Init
#define LJPLL_SSC_CTRLL_INIT_MASK 0x2u
//! Constant NONE - No action
#define CONST_LJPLL_SSC_CTRLL_INIT_NONE 0x0
//! Constant START - Start
#define CONST_LJPLL_SSC_CTRLL_INIT_START 0x1

//! Field SPREAD - Spread Depth Control in 0.1% steps
#define LJPLL_SSC_CTRLL_SPREAD_POS 2
//! Field SPREAD - Spread Depth Control in 0.1% steps
#define LJPLL_SSC_CTRLL_SPREAD_MASK 0x7Cu

//! Field DIVVAL - SSC Divider
#define LJPLL_SSC_CTRLL_DIVVAL_POS 8
//! Field DIVVAL - SSC Divider
#define LJPLL_SSC_CTRLL_DIVVAL_MASK 0xF00u

//! Field DOWNSPREAD - Downspread Control
#define LJPLL_SSC_CTRLL_DOWNSPREAD_POS 12
//! Field DOWNSPREAD - Downspread Control
#define LJPLL_SSC_CTRLL_DOWNSPREAD_MASK 0x1000u
//! Constant CENTER - Center-Spread
#define CONST_LJPLL_SSC_CTRLL_DOWNSPREAD_CENTER 0x0
//! Constant DOWN - Downspread
#define CONST_LJPLL_SSC_CTRLL_DOWNSPREAD_DOWN 0x1

//! Field EXT_MAXADDRL - Maximum Address for external wave table
#define LJPLL_SSC_CTRLL_EXT_MAXADDRL_POS 13
//! Field EXT_MAXADDRL - Maximum Address for external wave table
#define LJPLL_SSC_CTRLL_EXT_MAXADDRL_MASK 0xE000u

//! @}

//! \defgroup LJPLL_SSC_CTRLH Register LJPLL_SSC_CTRLH - LJ PLL3 SSC CTRL
//! @{

//! Register Offset (relative)
#define LJPLL_SSC_CTRLH 0x30
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_LJPLL_SSC_CTRLH 0x00D29030u

//! Register Reset Value
#define LJPLL_SSC_CTRLH_RST 0x00000000u

//! Field EXT_MAXADDRH - Maximum Address for external wave table
#define LJPLL_SSC_CTRLH_EXT_MAXADDRH_POS 0
//! Field EXT_MAXADDRH - Maximum Address for external wave table
#define LJPLL_SSC_CTRLH_EXT_MAXADDRH_MASK 0x1Fu

//! Field EXT_WAVEVAL - External Wave Table Input
#define LJPLL_SSC_CTRLH_EXT_WAVEVAL_POS 5
//! Field EXT_WAVEVAL - External Wave Table Input
#define LJPLL_SSC_CTRLH_EXT_WAVEVAL_MASK 0x1FE0u

//! Field SEL_EXTWAVE - Wave Table Select
#define LJPLL_SSC_CTRLH_SEL_EXTWAVE_POS 13
//! Field SEL_EXTWAVE - Wave Table Select
#define LJPLL_SSC_CTRLH_SEL_EXTWAVE_MASK 0x2000u
//! Constant INT - Use internal 128 point triangular table (Use EXTWAVEVAL input)
#define CONST_LJPLL_SSC_CTRLH_SEL_EXTWAVE_INT 0x0
//! Constant EXT - Use external wave table
#define CONST_LJPLL_SSC_CTRLH_SEL_EXTWAVE_EXT 0x1

//! @}

//! \defgroup CGU_PDI_CLK_OBSERVATION Register CGU_PDI_CLK_OBSERVATION - GPIO2 Clock Observation Register Configuration
//! @{

//! Register Offset (relative)
#define CGU_PDI_CLK_OBSERVATION 0x34
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_CLK_OBSERVATION 0x00D29034u

//! Register Reset Value
#define CGU_PDI_CLK_OBSERVATION_RST 0x00000005u

//! Field SEL - GPIO2 Output Clock Selection
#define CGU_PDI_CLK_OBSERVATION_SEL_POS 0
//! Field SEL - GPIO2 Output Clock Selection
#define CGU_PDI_CLK_OBSERVATION_SEL_MASK 0xFu
//! Constant SYSCLK0 - Slice 0 CLKx16 at 406 MHz div 8
#define CONST_CGU_PDI_CLK_OBSERVATION_SEL_SYSCLK0 0x0
//! Constant SYSCLK1 - Slice 1 CLKx16 at 406 MHz div 8
#define CONST_CGU_PDI_CLK_OBSERVATION_SEL_SYSCLK1 0x1
//! Constant SYSCLK2 - Slice 2 CLKx16 at 406 MHz div 8
#define CONST_CGU_PDI_CLK_OBSERVATION_SEL_SYSCLK2 0x2
//! Constant SYSCLK3 - Slice 3 CLKx16 at 406 MHz div 8
#define CONST_CGU_PDI_CLK_OBSERVATION_SEL_SYSCLK3 0x3
//! Constant LJPLL - LJPLL FOUT2
#define CONST_CGU_PDI_CLK_OBSERVATION_SEL_LJPLL 0x4

//! @}

//! \defgroup CGU_PDI_CLK_EN Register CGU_PDI_CLK_EN - Modules clock enable
//! @{

//! Register Offset (relative)
#define CGU_PDI_CLK_EN 0x38
//! Register Offset (absolute) for 1st Instance CGU_PDI
#define CGU_PDI_CGU_PDI_CLK_EN 0x00D29038u

//! Register Reset Value
#define CGU_PDI_CLK_EN_RST 0x00000000u

//! Field USXGMII_CLK_EN - USXGMII XPCS Clock enable
#define CGU_PDI_CLK_EN_USXGMII_CLK_EN_POS 0
//! Field USXGMII_CLK_EN - USXGMII XPCS Clock enable
#define CGU_PDI_CLK_EN_USXGMII_CLK_EN_MASK 0x1u
//! Constant DISABLE - USXGMII clock disable
#define CONST_CGU_PDI_CLK_EN_USXGMII_CLK_EN_DISABLE 0x0
//! Constant ENABLE - USXGMII clock enable
#define CONST_CGU_PDI_CLK_EN_USXGMII_CLK_EN_ENABLE 0x1

//! @}

#endif
