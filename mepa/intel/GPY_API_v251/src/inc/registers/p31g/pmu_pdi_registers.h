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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/pmu_pdi_registers_def.xml
// Register File Name  : PMU_PDI_REGISTERS
// Register File Title : Registers for PMU
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _PMU_PDI_REGISTERS_H
#define _PMU_PDI_REGISTERS_H

//! \defgroup PMU_PDI_REGISTERS Register File PMU_PDI_REGISTERS - Registers for PMU
//! @{

//! Base Address of PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_MODULE_BASE 0x00D28C00u

//! \defgroup PMU_PDI_REGISTERS_PMU_ULP Register PMU_PDI_REGISTERS_PMU_ULP - PMU ULP Configuration Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_PMU_ULP 0x0
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_PMU_ULP 0x00D28C00u

//! Register Reset Value
#define PMU_PDI_REGISTERS_PMU_ULP_RST 0x0000ED77u

//! Field OFFMSK0 - Power Off Mask 0
#define PMU_PDI_REGISTERS_PMU_ULP_OFFMSK0_POS 0
//! Field OFFMSK0 - Power Off Mask 0
#define PMU_PDI_REGISTERS_PMU_ULP_OFFMSK0_MASK 0x1u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_OFFMSK0_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_OFFMSK0_MSK 0x1

//! Field OFFMSK1 - Power Off Mask 1
#define PMU_PDI_REGISTERS_PMU_ULP_OFFMSK1_POS 1
//! Field OFFMSK1 - Power Off Mask 1
#define PMU_PDI_REGISTERS_PMU_ULP_OFFMSK1_MASK 0x2u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_OFFMSK1_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_OFFMSK1_MSK 0x1

//! Field OFFMSK2 - Power Off Mask 2
#define PMU_PDI_REGISTERS_PMU_ULP_OFFMSK2_POS 2
//! Field OFFMSK2 - Power Off Mask 2
#define PMU_PDI_REGISTERS_PMU_ULP_OFFMSK2_MASK 0x4u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_OFFMSK2_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_OFFMSK2_MSK 0x1

//! Field OFFMSK3 - Power Off Mask 3
#define PMU_PDI_REGISTERS_PMU_ULP_OFFMSK3_POS 3
//! Field OFFMSK3 - Power Off Mask 3
#define PMU_PDI_REGISTERS_PMU_ULP_OFFMSK3_MASK 0x8u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_OFFMSK3_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_OFFMSK3_MSK 0x1

//! Field ONMSK0 - Power On Mask 0
#define PMU_PDI_REGISTERS_PMU_ULP_ONMSK0_POS 4
//! Field ONMSK0 - Power On Mask 0
#define PMU_PDI_REGISTERS_PMU_ULP_ONMSK0_MASK 0x10u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_ONMSK0_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_ONMSK0_MSK 0x1

//! Field ONMSK1 - Power On Mask 1
#define PMU_PDI_REGISTERS_PMU_ULP_ONMSK1_POS 5
//! Field ONMSK1 - Power On Mask 1
#define PMU_PDI_REGISTERS_PMU_ULP_ONMSK1_MASK 0x20u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_ONMSK1_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_ONMSK1_MSK 0x1

//! Field ONMSK2 - Power On Mask 2
#define PMU_PDI_REGISTERS_PMU_ULP_ONMSK2_POS 6
//! Field ONMSK2 - Power On Mask 2
#define PMU_PDI_REGISTERS_PMU_ULP_ONMSK2_MASK 0x40u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_ONMSK2_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_ONMSK2_MSK 0x1

//! Field ONMSK3 - Power On Mask 3
#define PMU_PDI_REGISTERS_PMU_ULP_ONMSK3_POS 7
//! Field ONMSK3 - Power On Mask 3
#define PMU_PDI_REGISTERS_PMU_ULP_ONMSK3_MASK 0x80u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_ONMSK3_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_ONMSK3_MSK 0x1

//! Field BCON_EN - Beacon Enable
#define PMU_PDI_REGISTERS_PMU_ULP_BCON_EN_POS 8
//! Field BCON_EN - Beacon Enable
#define PMU_PDI_REGISTERS_PMU_ULP_BCON_EN_MASK 0x100u
//! Constant DIS - Beacon Disable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_BCON_EN_DIS 0x0
//! Constant EN - Beacon Enable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_BCON_EN_EN 0x1

//! Field ULP_EN - ULP Enable
#define PMU_PDI_REGISTERS_PMU_ULP_ULP_EN_POS 9
//! Field ULP_EN - ULP Enable
#define PMU_PDI_REGISTERS_PMU_ULP_ULP_EN_MASK 0x200u
//! Constant DIS - Normal operation
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_ULP_EN_DIS 0x0
//! Constant EN - Enable ULP
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_ULP_EN_EN 0x1

//! Field PMU_EN - PMU Enable
#define PMU_PDI_REGISTERS_PMU_ULP_PMU_EN_POS 10
//! Field PMU_EN - PMU Enable
#define PMU_PDI_REGISTERS_PMU_ULP_PMU_EN_MASK 0x400u
//! Constant DIS - PMU Disable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_PMU_EN_DIS 0x0
//! Constant EN - PMU Enable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_PMU_EN_EN 0x1

//! Field BCON_TOG - Beacon Toggle
#define PMU_PDI_REGISTERS_PMU_ULP_BCON_TOG_POS 11
//! Field BCON_TOG - Beacon Toggle
#define PMU_PDI_REGISTERS_PMU_ULP_BCON_TOG_MASK 0x800u
//! Constant DIS - Toggle Disable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_BCON_TOG_DIS 0x0
//! Constant EN - Toggle Enable
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_BCON_TOG_EN 0x1

//! Field PIN0_POL - Pin 0 Polarity
#define PMU_PDI_REGISTERS_PMU_ULP_PIN0_POL_POS 12
//! Field PIN0_POL - Pin 0 Polarity
#define PMU_PDI_REGISTERS_PMU_ULP_PIN0_POL_MASK 0x1000u
//! Constant LOW - Low Polarity
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_PIN0_POL_LOW 0x0
//! Constant HIGH - High Polarity
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_PIN0_POL_HIGH 0x1

//! Field PIN1_POL - Pin 1 Polarity
#define PMU_PDI_REGISTERS_PMU_ULP_PIN1_POL_POS 13
//! Field PIN1_POL - Pin 1 Polarity
#define PMU_PDI_REGISTERS_PMU_ULP_PIN1_POL_MASK 0x2000u
//! Constant LOW - Low Polarity
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_PIN1_POL_LOW 0x0
//! Constant HIGH - High Polarity
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_PIN1_POL_HIGH 0x1

//! Field PIN2_POL - Pin 2 Polarity
#define PMU_PDI_REGISTERS_PMU_ULP_PIN2_POL_POS 14
//! Field PIN2_POL - Pin 2 Polarity
#define PMU_PDI_REGISTERS_PMU_ULP_PIN2_POL_MASK 0x4000u
//! Constant LOW - Low Polarity
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_PIN2_POL_LOW 0x0
//! Constant HIGH - High Polarity
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_PIN2_POL_HIGH 0x1

//! Field DCPM_PD - DCPM Power Down
#define PMU_PDI_REGISTERS_PMU_ULP_DCPM_PD_POS 15
//! Field DCPM_PD - DCPM Power Down
#define PMU_PDI_REGISTERS_PMU_ULP_DCPM_PD_MASK 0x8000u
//! Constant NORMAL - No power down
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_DCPM_PD_NORMAL 0x0
//! Constant PD - Power Down
#define CONST_PMU_PDI_REGISTERS_PMU_ULP_DCPM_PD_PD 0x1

//! @}

//! \defgroup PMU_PDI_REGISTERS_PMU_CFG Register PMU_PDI_REGISTERS_PMU_CFG - PMU Configuration Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_PMU_CFG 0x4
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_PMU_CFG 0x00D28C04u

//! Register Reset Value
#define PMU_PDI_REGISTERS_PMU_CFG_RST 0x00000F5Au

//! Field WMSKA - Twisted Pair A Wake Mask
#define PMU_PDI_REGISTERS_PMU_CFG_WMSKA_POS 0
//! Field WMSKA - Twisted Pair A Wake Mask
#define PMU_PDI_REGISTERS_PMU_CFG_WMSKA_MASK 0x1u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_WMSKA_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_WMSKA_MSK 0x1

//! Field WMSKB - Twisted Pair B Wake Mask
#define PMU_PDI_REGISTERS_PMU_CFG_WMSKB_POS 1
//! Field WMSKB - Twisted Pair B Wake Mask
#define PMU_PDI_REGISTERS_PMU_CFG_WMSKB_MASK 0x2u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_WMSKB_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_WMSKB_MSK 0x1

//! Field WMSKC - Twisted Pair C Wake Mask
#define PMU_PDI_REGISTERS_PMU_CFG_WMSKC_POS 2
//! Field WMSKC - Twisted Pair C Wake Mask
#define PMU_PDI_REGISTERS_PMU_CFG_WMSKC_MASK 0x4u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_WMSKC_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_WMSKC_MSK 0x1

//! Field WMSKD - Twisted Pair D Wake Mask
#define PMU_PDI_REGISTERS_PMU_CFG_WMSKD_POS 3
//! Field WMSKD - Twisted Pair D Wake Mask
#define PMU_PDI_REGISTERS_PMU_CFG_WMSKD_MASK 0x8u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_WMSKD_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_WMSKD_MSK 0x1

//! Field BMSKAP - Twisted Pair A Positive Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKAP_POS 4
//! Field BMSKAP - Twisted Pair A Positive Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKAP_MASK 0x10u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKAP_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKAP_MSK 0x1

//! Field BMSKBP - Twisted Pair B Positive Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKBP_POS 5
//! Field BMSKBP - Twisted Pair B Positive Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKBP_MASK 0x20u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKBP_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKBP_MSK 0x1

//! Field BMSKCP - Twisted Pair C Positive Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKCP_POS 6
//! Field BMSKCP - Twisted Pair C Positive Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKCP_MASK 0x40u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKCP_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKCP_MSK 0x1

//! Field BMSKDP - Twisted Pair D Positive Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKDP_POS 7
//! Field BMSKDP - Twisted Pair D Positive Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKDP_MASK 0x80u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKDP_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKDP_MSK 0x1

//! Field BMSKAN - Twisted Pair A Negative Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKAN_POS 8
//! Field BMSKAN - Twisted Pair A Negative Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKAN_MASK 0x100u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKAN_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKAN_MSK 0x1

//! Field BMSKBN - Twisted Pair B Negative Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKBN_POS 9
//! Field BMSKBN - Twisted Pair B Negative Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKBN_MASK 0x200u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKBN_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKBN_MSK 0x1

//! Field BMSKCN - Twisted Pair C Negative Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKCN_POS 10
//! Field BMSKCN - Twisted Pair C Negative Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKCN_MASK 0x400u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKCN_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKCN_MSK 0x1

//! Field BMSKDN - Twisted Pair D Negative Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKDN_POS 11
//! Field BMSKDN - Twisted Pair D Negative Beacon Mask
#define PMU_PDI_REGISTERS_PMU_CFG_BMSKDN_MASK 0x800u
//! Constant NOMSK - Mask Disable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKDN_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_BMSKDN_MSK 0x1

//! Field CLKSEL - Clock Select
#define PMU_PDI_REGISTERS_PMU_CFG_CLKSEL_POS 12
//! Field CLKSEL - Clock Select
#define PMU_PDI_REGISTERS_PMU_CFG_CLKSEL_MASK 0x3000u
//! Constant SEL0 - Internal Clock
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_CLKSEL_SEL0 0x0
//! Constant SEL1 - External Clock from GPIO11
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_CLKSEL_SEL1 0x1
//! Constant SEL2 - External Clock from GPIO12
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_CLKSEL_SEL2 0x2
//! Constant SEL3 - External Clock from GPIO18
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_CLKSEL_SEL3 0x3

//! Field ISO_OFF - Isolation Off
#define PMU_PDI_REGISTERS_PMU_CFG_ISO_OFF_POS 14
//! Field ISO_OFF - Isolation Off
#define PMU_PDI_REGISTERS_PMU_CFG_ISO_OFF_MASK 0x4000u
//! Constant ON - Isolation On
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_ISO_OFF_ON 0x0
//! Constant OFF - Isolation Off
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_ISO_OFF_OFF 0x1

//! Field DCDC_OFF_DIS - Disable DCDC Off
#define PMU_PDI_REGISTERS_PMU_CFG_DCDC_OFF_DIS_POS 15
//! Field DCDC_OFF_DIS - Disable DCDC Off
#define PMU_PDI_REGISTERS_PMU_CFG_DCDC_OFF_DIS_MASK 0x8000u
//! Constant EN - DCDC Off Enable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_DCDC_OFF_DIS_EN 0x0
//! Constant DIS - DCDC Off Disable
#define CONST_PMU_PDI_REGISTERS_PMU_CFG_DCDC_OFF_DIS_DIS 0x1

//! @}

//! \defgroup PMU_PDI_REGISTERS_PMU_STAT Register PMU_PDI_REGISTERS_PMU_STAT - PMU Status Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_PMU_STAT 0x8
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_PMU_STAT 0x00D28C08u

//! Register Reset Value
#define PMU_PDI_REGISTERS_PMU_STAT_RST 0x00000000u

//! Field WAKE0 - Wake 0
#define PMU_PDI_REGISTERS_PMU_STAT_WAKE0_POS 0
//! Field WAKE0 - Wake 0
#define PMU_PDI_REGISTERS_PMU_STAT_WAKE0_MASK 0x1u
//! Constant NOWAKE - Not the wake up cause
#define CONST_PMU_PDI_REGISTERS_PMU_STAT_WAKE0_NOWAKE 0x0
//! Constant WAKE - Wake up condition met
#define CONST_PMU_PDI_REGISTERS_PMU_STAT_WAKE0_WAKE 0x1

//! Field WAKE1 - Wake 1
#define PMU_PDI_REGISTERS_PMU_STAT_WAKE1_POS 1
//! Field WAKE1 - Wake 1
#define PMU_PDI_REGISTERS_PMU_STAT_WAKE1_MASK 0x2u
//! Constant NOWAKE - Not the wake up cause
#define CONST_PMU_PDI_REGISTERS_PMU_STAT_WAKE1_NOWAKE 0x0
//! Constant WAKE - Wake up condition met
#define CONST_PMU_PDI_REGISTERS_PMU_STAT_WAKE1_WAKE 0x1

//! Field WAKE2 - Wake 2
#define PMU_PDI_REGISTERS_PMU_STAT_WAKE2_POS 2
//! Field WAKE2 - Wake 2
#define PMU_PDI_REGISTERS_PMU_STAT_WAKE2_MASK 0x4u
//! Constant NOWAKE - Not the wake up cause
#define CONST_PMU_PDI_REGISTERS_PMU_STAT_WAKE2_NOWAKE 0x0
//! Constant WAKE - Wake up condition met
#define CONST_PMU_PDI_REGISTERS_PMU_STAT_WAKE2_WAKE 0x1

//! Field WAKE3 - Wake 3
#define PMU_PDI_REGISTERS_PMU_STAT_WAKE3_POS 3
//! Field WAKE3 - Wake 3
#define PMU_PDI_REGISTERS_PMU_STAT_WAKE3_MASK 0x8u
//! Constant NOWAKE - Not the wake up cause
#define CONST_PMU_PDI_REGISTERS_PMU_STAT_WAKE3_NOWAKE 0x0
//! Constant WAKE - Wake up condition met
#define CONST_PMU_PDI_REGISTERS_PMU_STAT_WAKE3_WAKE 0x1

//! Field STRAP_DONE - Pin Strapping Done
#define PMU_PDI_REGISTERS_PMU_STAT_STRAP_DONE_POS 4
//! Field STRAP_DONE - Pin Strapping Done
#define PMU_PDI_REGISTERS_PMU_STAT_STRAP_DONE_MASK 0x10u
//! Constant NOTDONE - Strapping not done
#define CONST_PMU_PDI_REGISTERS_PMU_STAT_STRAP_DONE_NOTDONE 0x0
//! Constant DONE - Strapping Done
#define CONST_PMU_PDI_REGISTERS_PMU_STAT_STRAP_DONE_DONE 0x1

//! @}

//! \defgroup PMU_PDI_REGISTERS_BCON_CFG Register PMU_PDI_REGISTERS_BCON_CFG - PMU Beacon Configuration Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_BCON_CFG 0xC
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_BCON_CFG 0x00D28C0Cu

//! Register Reset Value
#define PMU_PDI_REGISTERS_BCON_CFG_RST 0x00001F30u

//! Field BWIDTH - Beacon Width
#define PMU_PDI_REGISTERS_BCON_CFG_BWIDTH_POS 0
//! Field BWIDTH - Beacon Width
#define PMU_PDI_REGISTERS_BCON_CFG_BWIDTH_MASK 0xFu

//! Field BITVL - Beacon Interval
#define PMU_PDI_REGISTERS_BCON_CFG_BITVL_POS 4
//! Field BITVL - Beacon Interval
#define PMU_PDI_REGISTERS_BCON_CFG_BITVL_MASK 0xFFF0u

//! @}

//! \defgroup PMU_PDI_REGISTERS_BCON_STAT Register PMU_PDI_REGISTERS_BCON_STAT - PMU Beacon Status Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_BCON_STAT 0x10
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_BCON_STAT 0x00D28C10u

//! Register Reset Value
#define PMU_PDI_REGISTERS_BCON_STAT_RST 0x00000000u

//! Field BWCNT - Beacon Width Count
#define PMU_PDI_REGISTERS_BCON_STAT_BWCNT_POS 0
//! Field BWCNT - Beacon Width Count
#define PMU_PDI_REGISTERS_BCON_STAT_BWCNT_MASK 0xFu

//! Field BICNT - Beacon Interval Count
#define PMU_PDI_REGISTERS_BCON_STAT_BICNT_POS 4
//! Field BICNT - Beacon Interval Count
#define PMU_PDI_REGISTERS_BCON_STAT_BICNT_MASK 0xFFF0u

//! @}

//! \defgroup PMU_PDI_REGISTERS_BCON_TOG Register PMU_PDI_REGISTERS_BCON_TOG - PMU Beacon Toggle Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_BCON_TOG 0x14
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_BCON_TOG 0x00D28C14u

//! Register Reset Value
#define PMU_PDI_REGISTERS_BCON_TOG_RST 0x00000008u

//! Field TOG_CFG - Beacon Toggle Configuration
#define PMU_PDI_REGISTERS_BCON_TOG_TOG_CFG_POS 0
//! Field TOG_CFG - Beacon Toggle Configuration
#define PMU_PDI_REGISTERS_BCON_TOG_TOG_CFG_MASK 0xFFu

//! Field TOG_CNT - Beacon Toggle Count
#define PMU_PDI_REGISTERS_BCON_TOG_TOG_CNT_POS 8
//! Field TOG_CNT - Beacon Toggle Count
#define PMU_PDI_REGISTERS_BCON_TOG_TOG_CNT_MASK 0xFF00u

//! @}

//! \defgroup PMU_PDI_REGISTERS_CLK_TRIM Register PMU_PDI_REGISTERS_CLK_TRIM - PMU Xtal-less Oscillator Trim
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_CLK_TRIM 0x18
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_CLK_TRIM 0x00D28C18u

//! Register Reset Value
#define PMU_PDI_REGISTERS_CLK_TRIM_RST 0x00000007u

//! Field TRIM - Trim Code
#define PMU_PDI_REGISTERS_CLK_TRIM_TRIM_POS 0
//! Field TRIM - Trim Code
#define PMU_PDI_REGISTERS_CLK_TRIM_TRIM_MASK 0xFu
//! Constant MIN - Lowest Frequency
#define CONST_PMU_PDI_REGISTERS_CLK_TRIM_TRIM_MIN 0x0
//! Constant DEF - Default Center Frequency
#define CONST_PMU_PDI_REGISTERS_CLK_TRIM_TRIM_DEF 0x7
//! Constant MAX - Highest Frequency
#define CONST_PMU_PDI_REGISTERS_CLK_TRIM_TRIM_MAX 0xF

//! Field BYP - Bypass
#define PMU_PDI_REGISTERS_CLK_TRIM_BYP_POS 4
//! Field BYP - Bypass
#define PMU_PDI_REGISTERS_CLK_TRIM_BYP_MASK 0x10u

//! @}

//! \defgroup PMU_PDI_REGISTERS_PS Register PMU_PDI_REGISTERS_PS - Pin Strapping Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_PS 0x1C
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_PS 0x00D28C1Cu

//! Register Reset Value
#define PMU_PDI_REGISTERS_PS_RST 0x00000000u

//! Field PS - Pin Strapping of GPIO0 to GPIO15
#define PMU_PDI_REGISTERS_PS_PS_POS 0
//! Field PS - Pin Strapping of GPIO0 to GPIO15
#define PMU_PDI_REGISTERS_PS_PS_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_PS2 Register PMU_PDI_REGISTERS_PS2 - Pin Strapping Register 2
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_PS2 0x20
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_PS2 0x00D28C20u

//! Register Reset Value
#define PMU_PDI_REGISTERS_PS2_RST 0x00000000u

//! Field PS - Pin Strapping of GPIO16 to GPIO18
#define PMU_PDI_REGISTERS_PS2_PS_POS 0
//! Field PS - Pin Strapping of GPIO16 to GPIO18
#define PMU_PDI_REGISTERS_PS2_PS_MASK 0x7u

//! @}

//! \defgroup PMU_PDI_REGISTERS_DCDC_CFG Register PMU_PDI_REGISTERS_DCDC_CFG - DCDC Configuration
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_DCDC_CFG 0x24
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_DCDC_CFG 0x00D28C24u

//! Register Reset Value
#define PMU_PDI_REGISTERS_DCDC_CFG_RST 0x00000002u

//! Field WP_RAMP - DCDC Working Point Ramp
#define PMU_PDI_REGISTERS_DCDC_CFG_WP_RAMP_POS 0
//! Field WP_RAMP - DCDC Working Point Ramp
#define PMU_PDI_REGISTERS_DCDC_CFG_WP_RAMP_MASK 0x3u

//! @}

//! \defgroup PMU_PDI_REGISTERS_DCDC_CTRL_CFG Register PMU_PDI_REGISTERS_DCDC_CTRL_CFG - DCDC Indirect Register Access Configuration
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_DCDC_CTRL_CFG 0x28
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_DCDC_CTRL_CFG 0x00D28C28u

//! Register Reset Value
#define PMU_PDI_REGISTERS_DCDC_CTRL_CFG_RST 0x00000000u

//! Field RW - DCDC Read/Write Access
#define PMU_PDI_REGISTERS_DCDC_CTRL_CFG_RW_POS 0
//! Field RW - DCDC Read/Write Access
#define PMU_PDI_REGISTERS_DCDC_CTRL_CFG_RW_MASK 0x1u
//! Constant READ - Read Access
#define CONST_PMU_PDI_REGISTERS_DCDC_CTRL_CFG_RW_READ 0x0
//! Constant WRITE - Write Access
#define CONST_PMU_PDI_REGISTERS_DCDC_CTRL_CFG_RW_WRITE 0x1

//! Field START - DCDC Indirect Register Access Start
#define PMU_PDI_REGISTERS_DCDC_CTRL_CFG_START_POS 1
//! Field START - DCDC Indirect Register Access Start
#define PMU_PDI_REGISTERS_DCDC_CTRL_CFG_START_MASK 0x2u
//! Constant NIL - NIL
#define CONST_PMU_PDI_REGISTERS_DCDC_CTRL_CFG_START_NIL 0x0
//! Constant START - START
#define CONST_PMU_PDI_REGISTERS_DCDC_CTRL_CFG_START_START 0x1

//! @}

//! \defgroup PMU_PDI_REGISTERS_DCDC_CTRL_ISR Register PMU_PDI_REGISTERS_DCDC_CTRL_ISR - DCDC Indirect Register Access Interrupt Status Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_DCDC_CTRL_ISR 0x2C
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_DCDC_CTRL_ISR 0x00D28C2Cu

//! Register Reset Value
#define PMU_PDI_REGISTERS_DCDC_CTRL_ISR_RST 0x00000000u

//! Field DONE - DCDC Indirect Register Access Done
#define PMU_PDI_REGISTERS_DCDC_CTRL_ISR_DONE_POS 0
//! Field DONE - DCDC Indirect Register Access Done
#define PMU_PDI_REGISTERS_DCDC_CTRL_ISR_DONE_MASK 0x1u
//! Constant NONE - NONE
#define CONST_PMU_PDI_REGISTERS_DCDC_CTRL_ISR_DONE_NONE 0x0
//! Constant DONE - DONE
#define CONST_PMU_PDI_REGISTERS_DCDC_CTRL_ISR_DONE_DONE 0x1

//! @}

//! \defgroup PMU_PDI_REGISTERS_DCDC_CTRL_IER Register PMU_PDI_REGISTERS_DCDC_CTRL_IER - DCDC Indirect Register Access Interrupt Enable Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_DCDC_CTRL_IER 0x30
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_DCDC_CTRL_IER 0x00D28C30u

//! Register Reset Value
#define PMU_PDI_REGISTERS_DCDC_CTRL_IER_RST 0x00000000u

//! Field DONE - DCDC Indirect Register Access Done
#define PMU_PDI_REGISTERS_DCDC_CTRL_IER_DONE_POS 0
//! Field DONE - DCDC Indirect Register Access Done
#define PMU_PDI_REGISTERS_DCDC_CTRL_IER_DONE_MASK 0x1u
//! Constant DIS - DIS
#define CONST_PMU_PDI_REGISTERS_DCDC_CTRL_IER_DONE_DIS 0x0
//! Constant EN - EN
#define CONST_PMU_PDI_REGISTERS_DCDC_CTRL_IER_DONE_EN 0x1

//! @}

//! \defgroup PMU_PDI_REGISTERS_DCDC_CTRL_ADDR Register PMU_PDI_REGISTERS_DCDC_CTRL_ADDR - DCDC Indirect Register Access Address
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_DCDC_CTRL_ADDR 0x34
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_DCDC_CTRL_ADDR 0x00D28C34u

//! Register Reset Value
#define PMU_PDI_REGISTERS_DCDC_CTRL_ADDR_RST 0x00000000u

//! Field ADDR - DCDC Control Interface Address
#define PMU_PDI_REGISTERS_DCDC_CTRL_ADDR_ADDR_POS 0
//! Field ADDR - DCDC Control Interface Address
#define PMU_PDI_REGISTERS_DCDC_CTRL_ADDR_ADDR_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_DCDC_CTRL_DATA Register PMU_PDI_REGISTERS_DCDC_CTRL_DATA - DCDC Indirect Register Access Data
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_DCDC_CTRL_DATA 0x38
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_DCDC_CTRL_DATA 0x00D28C38u

//! Register Reset Value
#define PMU_PDI_REGISTERS_DCDC_CTRL_DATA_RST 0x00000000u

//! Field DATA - Data
#define PMU_PDI_REGISTERS_DCDC_CTRL_DATA_DATA_POS 0
//! Field DATA - Data
#define PMU_PDI_REGISTERS_DCDC_CTRL_DATA_DATA_MASK 0xFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_GPHY_GPS0 Register PMU_PDI_REGISTERS_GPHY_GPS0 - GPHY General Purpose Pin Strapping 0 Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_GPHY_GPS0 0x3C
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_GPHY_GPS0 0x00D28C3Cu

//! Register Reset Value
#define PMU_PDI_REGISTERS_GPHY_GPS0_RST 0x00004000u

//! Field BFDEV - Base Frequency Deviation
#define PMU_PDI_REGISTERS_GPHY_GPS0_BFDEV_POS 0
//! Field BFDEV - Base Frequency Deviation
#define PMU_PDI_REGISTERS_GPHY_GPS0_BFDEV_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_GPHY_GPS1 Register PMU_PDI_REGISTERS_GPHY_GPS1 - GPHY General Purpose Pin Strapping 1 Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_GPHY_GPS1 0x40
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_GPHY_GPS1 0x00D28C40u

//! Register Reset Value
#define PMU_PDI_REGISTERS_GPHY_GPS1_RST 0x00000000u

//! Field CHIP_ID - Chip ID
#define PMU_PDI_REGISTERS_GPHY_GPS1_CHIP_ID_POS 0
//! Field CHIP_ID - Chip ID
#define PMU_PDI_REGISTERS_GPHY_GPS1_CHIP_ID_MASK 0xFu
//! Constant P31G - Single GPHY in Swanville Chip
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS1_CHIP_ID_P31G 0x0
//! Constant GNIC - Gigabit NIC in FoxVille Chip
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS1_CHIP_ID_GNIC 0x4
//! Constant GPON - GPHY IP in Falcon IP only
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS1_CHIP_ID_GPON 0xD
//! Constant GRX - GPHY IP in Twin Mountain
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS1_CHIP_ID_GRX 0xE

//! Field CHIP_VER - Chip Version
#define PMU_PDI_REGISTERS_GPHY_GPS1_CHIP_VER_POS 4
//! Field CHIP_VER - Chip Version
#define PMU_PDI_REGISTERS_GPHY_GPS1_CHIP_VER_MASK 0xF0u

//! Field MDIO_PHY_ADDR - MDIO PHY Address
#define PMU_PDI_REGISTERS_GPHY_GPS1_MDIO_PHY_ADDR_POS 8
//! Field MDIO_PHY_ADDR - MDIO PHY Address
#define PMU_PDI_REGISTERS_GPHY_GPS1_MDIO_PHY_ADDR_MASK 0x1F00u

//! Field MDIO_INT_POL - MDIO Interrupt Polarity
#define PMU_PDI_REGISTERS_GPHY_GPS1_MDIO_INT_POL_POS 13
//! Field MDIO_INT_POL - MDIO Interrupt Polarity
#define PMU_PDI_REGISTERS_GPHY_GPS1_MDIO_INT_POL_MASK 0x2000u
//! Constant HIGH - Interrupt is active high.
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS1_MDIO_INT_POL_HIGH 0x0
//! Constant LOW - Interrupt is active low.
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS1_MDIO_INT_POL_LOW 0x1

//! Field G2_5_DIS - Disable 2.5G mode support
#define PMU_PDI_REGISTERS_GPHY_GPS1_G2_5_DIS_POS 14
//! Field G2_5_DIS - Disable 2.5G mode support
#define PMU_PDI_REGISTERS_GPHY_GPS1_G2_5_DIS_MASK 0x4000u
//! Constant EN - Enable 2.5G mode
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS1_G2_5_DIS_EN 0x0
//! Constant DIS - Disable 2.5G mode
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS1_G2_5_DIS_DIS 0x1

//! Field LED_EN - Led startup enable
#define PMU_PDI_REGISTERS_GPHY_GPS1_LED_EN_POS 15
//! Field LED_EN - Led startup enable
#define PMU_PDI_REGISTERS_GPHY_GPS1_LED_EN_MASK 0x8000u
//! Constant DISABLE - LED is disabled at startup
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS1_LED_EN_DISABLE 0x0
//! Constant ENABLE - LED is enabled at startup
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS1_LED_EN_ENABLE 0x1

//! @}

//! \defgroup PMU_PDI_REGISTERS_GPHY_GPS2 Register PMU_PDI_REGISTERS_GPHY_GPS2 - GPHY General Purpose Pin Strapping 2 Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_GPHY_GPS2 0x44
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_GPHY_GPS2 0x00D28C44u

//! Register Reset Value
#define PMU_PDI_REGISTERS_GPHY_GPS2_RST 0x00000000u

//! Field RCAL - RCAL
#define PMU_PDI_REGISTERS_GPHY_GPS2_RCAL_POS 0
//! Field RCAL - RCAL
#define PMU_PDI_REGISTERS_GPHY_GPS2_RCAL_MASK 0xFu

//! Field RC_COUNT - RC Count
#define PMU_PDI_REGISTERS_GPHY_GPS2_RC_COUNT_POS 4
//! Field RC_COUNT - RC Count
#define PMU_PDI_REGISTERS_GPHY_GPS2_RC_COUNT_MASK 0x3FF0u

//! Field MDIO_I2C - MDIO/I2C Select
#define PMU_PDI_REGISTERS_GPHY_GPS2_MDIO_I2C_POS 14
//! Field MDIO_I2C - MDIO/I2C Select
#define PMU_PDI_REGISTERS_GPHY_GPS2_MDIO_I2C_MASK 0x4000u
//! Constant MDIO - MDIO
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS2_MDIO_I2C_MDIO 0x0
//! Constant I2C - I2C
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS2_MDIO_I2C_I2C 0x1

//! Field RJ45_TAP - RJ45 Tap Configuration
#define PMU_PDI_REGISTERS_GPHY_GPS2_RJ45_TAP_POS 15
//! Field RJ45_TAP - RJ45 Tap Configuration
#define PMU_PDI_REGISTERS_GPHY_GPS2_RJ45_TAP_MASK 0x8000u
//! Constant DOWN - TAP-DOWN RJ45
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS2_RJ45_TAP_DOWN 0x0
//! Constant UP - TAP-UP RJ45
#define CONST_PMU_PDI_REGISTERS_GPHY_GPS2_RJ45_TAP_UP 0x1

//! @}

//! \defgroup PMU_PDI_REGISTERS_STORAGE_0 Register PMU_PDI_REGISTERS_STORAGE_0 - PMU Storage Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_STORAGE_0 0x48
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_STORAGE_0 0x00D28C48u

//! Register Reset Value
#define PMU_PDI_REGISTERS_STORAGE_0_RST 0x00000000u

//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_0_STORE_POS 0
//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_0_STORE_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_STORAGE_1 Register PMU_PDI_REGISTERS_STORAGE_1 - PMU Storage Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_STORAGE_1 0x4C
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_STORAGE_1 0x00D28C4Cu

//! Register Reset Value
#define PMU_PDI_REGISTERS_STORAGE_1_RST 0x00000000u

//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_1_STORE_POS 0
//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_1_STORE_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_STORAGE_2 Register PMU_PDI_REGISTERS_STORAGE_2 - PMU Storage Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_STORAGE_2 0x50
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_STORAGE_2 0x00D28C50u

//! Register Reset Value
#define PMU_PDI_REGISTERS_STORAGE_2_RST 0x00000000u

//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_2_STORE_POS 0
//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_2_STORE_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_STORAGE_3 Register PMU_PDI_REGISTERS_STORAGE_3 - PMU Storage Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_STORAGE_3 0x54
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_STORAGE_3 0x00D28C54u

//! Register Reset Value
#define PMU_PDI_REGISTERS_STORAGE_3_RST 0x00000000u

//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_3_STORE_POS 0
//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_3_STORE_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_STORAGE_4 Register PMU_PDI_REGISTERS_STORAGE_4 - PMU Storage Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_STORAGE_4 0x58
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_STORAGE_4 0x00D28C58u

//! Register Reset Value
#define PMU_PDI_REGISTERS_STORAGE_4_RST 0x00000000u

//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_4_STORE_POS 0
//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_4_STORE_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_STORAGE_5 Register PMU_PDI_REGISTERS_STORAGE_5 - PMU Storage Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_STORAGE_5 0x5C
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_STORAGE_5 0x00D28C5Cu

//! Register Reset Value
#define PMU_PDI_REGISTERS_STORAGE_5_RST 0x00000000u

//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_5_STORE_POS 0
//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_5_STORE_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_STORAGE_6 Register PMU_PDI_REGISTERS_STORAGE_6 - PMU Storage Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_STORAGE_6 0x60
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_STORAGE_6 0x00D28C60u

//! Register Reset Value
#define PMU_PDI_REGISTERS_STORAGE_6_RST 0x00000000u

//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_6_STORE_POS 0
//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_6_STORE_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_STORAGE_7 Register PMU_PDI_REGISTERS_STORAGE_7 - PMU Storage Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_STORAGE_7 0x64
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_STORAGE_7 0x00D28C64u

//! Register Reset Value
#define PMU_PDI_REGISTERS_STORAGE_7_RST 0x00000000u

//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_7_STORE_POS 0
//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_7_STORE_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_STORAGE_8 Register PMU_PDI_REGISTERS_STORAGE_8 - PMU Storage Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_STORAGE_8 0x68
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_STORAGE_8 0x00D28C68u

//! Register Reset Value
#define PMU_PDI_REGISTERS_STORAGE_8_RST 0x00000000u

//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_8_STORE_POS 0
//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_8_STORE_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_STORAGE_9 Register PMU_PDI_REGISTERS_STORAGE_9 - PMU Storage Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_STORAGE_9 0x6C
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_STORAGE_9 0x00D28C6Cu

//! Register Reset Value
#define PMU_PDI_REGISTERS_STORAGE_9_RST 0x00000000u

//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_9_STORE_POS 0
//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_9_STORE_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_STORAGE_10 Register PMU_PDI_REGISTERS_STORAGE_10 - PMU Storage Register
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_STORAGE_10 0x70
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_STORAGE_10 0x00D28C70u

//! Register Reset Value
#define PMU_PDI_REGISTERS_STORAGE_10_RST 0x00000000u

//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_10_STORE_POS 0
//! Field STORE - Storage Bits
#define PMU_PDI_REGISTERS_STORAGE_10_STORE_MASK 0xFFFFu

//! @}

//! \defgroup PMU_PDI_REGISTERS_BOOTSTAT Register PMU_PDI_REGISTERS_BOOTSTAT - Boot Status Indicators
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_BOOTSTAT 0x74
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_BOOTSTAT 0x00D28C74u

//! Register Reset Value
#define PMU_PDI_REGISTERS_BOOTSTAT_RST 0x00000000u

//! Field FAILCODE - Boot Fail Code
#define PMU_PDI_REGISTERS_BOOTSTAT_FAILCODE_POS 0
//! Field FAILCODE - Boot Fail Code
#define PMU_PDI_REGISTERS_BOOTSTAT_FAILCODE_MASK 0x3u
//! Constant PASS - No Failure
#define CONST_PMU_PDI_REGISTERS_BOOTSTAT_FAILCODE_PASS 0x0
//! Constant OTPBOOT - OTP Shell Boot Failed
#define CONST_PMU_PDI_REGISTERS_BOOTSTAT_FAILCODE_OTPBOOT 0x1
//! Constant FWCRC - OTP FW CRC Check Failed
#define CONST_PMU_PDI_REGISTERS_BOOTSTAT_FAILCODE_FWCRC 0x2
//! Constant RES1 - reserved
#define CONST_PMU_PDI_REGISTERS_BOOTSTAT_FAILCODE_RES1 0x3

//! Field BOOTROM_EXIT - BOOTROM Exit Path
#define PMU_PDI_REGISTERS_BOOTSTAT_BOOTROM_EXIT_POS 2
//! Field BOOTROM_EXIT - BOOTROM Exit Path
#define PMU_PDI_REGISTERS_BOOTSTAT_BOOTROM_EXIT_MASK 0xCu
//! Constant NO - BootROM Exit Not completed Yet
#define CONST_PMU_PDI_REGISTERS_BOOTSTAT_BOOTROM_EXIT_NO 0x0
//! Constant FLASH - BootROM Exit to FLASH
#define CONST_PMU_PDI_REGISTERS_BOOTSTAT_BOOTROM_EXIT_FLASH 0x1
//! Constant ROM - BootROM Exit to ROM
#define CONST_PMU_PDI_REGISTERS_BOOTSTAT_BOOTROM_EXIT_ROM 0x2
//! Constant OTP - BootROM exit to OTP
#define CONST_PMU_PDI_REGISTERS_BOOTSTAT_BOOTROM_EXIT_OTP 0x3

//! Field BOOTLOADER_EXIT - BOOT Loader Exit Path
#define PMU_PDI_REGISTERS_BOOTSTAT_BOOTLOADER_EXIT_POS 4
//! Field BOOTLOADER_EXIT - BOOT Loader Exit Path
#define PMU_PDI_REGISTERS_BOOTSTAT_BOOTLOADER_EXIT_MASK 0x30u
//! Constant NO - Boot Loader Exit Not completed Yet
#define CONST_PMU_PDI_REGISTERS_BOOTSTAT_BOOTLOADER_EXIT_NO 0x0
//! Constant FLASH - Boot Loader Exit to FLASH
#define CONST_PMU_PDI_REGISTERS_BOOTSTAT_BOOTLOADER_EXIT_FLASH 0x1
//! Constant ROM - Boot Loader Exit to ROM
#define CONST_PMU_PDI_REGISTERS_BOOTSTAT_BOOTLOADER_EXIT_ROM 0x2
//! Constant OTP - Boot Loader Exit to OTP
#define CONST_PMU_PDI_REGISTERS_BOOTSTAT_BOOTLOADER_EXIT_OTP 0x3

//! @}

//! \defgroup PMU_PDI_REGISTERS_GUARD_CFG Register PMU_PDI_REGISTERS_GUARD_CFG - Configure the non-listening guard window around beacon transmit window
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_GUARD_CFG 0x78
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_GUARD_CFG 0x00D28C78u

//! Register Reset Value
#define PMU_PDI_REGISTERS_GUARD_CFG_RST 0x000083FFu

//! Field GWIDTH - Guard width
#define PMU_PDI_REGISTERS_GUARD_CFG_GWIDTH_POS 0
//! Field GWIDTH - Guard width
#define PMU_PDI_REGISTERS_GUARD_CFG_GWIDTH_MASK 0x3FFu

//! Field GUARD_EN - Enable non listen guard window
#define PMU_PDI_REGISTERS_GUARD_CFG_GUARD_EN_POS 15
//! Field GUARD_EN - Enable non listen guard window
#define PMU_PDI_REGISTERS_GUARD_CFG_GUARD_EN_MASK 0x8000u
//! Constant DISABLE - Guard window is not active
#define CONST_PMU_PDI_REGISTERS_GUARD_CFG_GUARD_EN_DISABLE 0x0
//! Constant ENABLE - Guard Window is active
#define CONST_PMU_PDI_REGISTERS_GUARD_CFG_GUARD_EN_ENABLE 0x1

//! @}

//! \defgroup PMU_PDI_REGISTERS_BEACON_TEST Register PMU_PDI_REGISTERS_BEACON_TEST - Expose the Beacon signals to/from ASP for test purpose
//! @{

//! Register Offset (relative)
#define PMU_PDI_REGISTERS_BEACON_TEST 0x7C
//! Register Offset (absolute) for 1st Instance PMU_PDI_REGISTERS
#define PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_BEACON_TEST 0x00D28C7Cu

//! Register Reset Value
#define PMU_PDI_REGISTERS_BEACON_TEST_RST 0x00000000u

//! Field BEACON_AP_O - Output Beacon Positive to ASPA
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_AP_O_POS 0
//! Field BEACON_AP_O - Output Beacon Positive to ASPA
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_AP_O_MASK 0x1u

//! Field BEACON_AN_O - Output Beacon Negative to ASPA
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_AN_O_POS 1
//! Field BEACON_AN_O - Output Beacon Negative to ASPA
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_AN_O_MASK 0x2u

//! Field BEACON_BP_O - Output Beacon Positive to ASPB
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_BP_O_POS 2
//! Field BEACON_BP_O - Output Beacon Positive to ASPB
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_BP_O_MASK 0x4u

//! Field BEACON_BN_O - Output Beacon Negative to ASPB
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_BN_O_POS 3
//! Field BEACON_BN_O - Output Beacon Negative to ASPB
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_BN_O_MASK 0x8u

//! Field BEACON_CP_O - Output Beacon Positive to ASPC
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_CP_O_POS 4
//! Field BEACON_CP_O - Output Beacon Positive to ASPC
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_CP_O_MASK 0x10u

//! Field BEACON_CN_O - Output Beacon Negative to ASPC
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_CN_O_POS 5
//! Field BEACON_CN_O - Output Beacon Negative to ASPC
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_CN_O_MASK 0x20u

//! Field BEACON_DP_O - Output Beacon Positive to ASPD
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_DP_O_POS 6
//! Field BEACON_DP_O - Output Beacon Positive to ASPD
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_DP_O_MASK 0x40u

//! Field BEACON_DN_O - Output Beacon Negative to ASPD
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_DN_O_POS 7
//! Field BEACON_DN_O - Output Beacon Negative to ASPD
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_DN_O_MASK 0x80u

//! Field BEACON_A_WAKE - Reflects the output of ASP wake signal
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_A_WAKE_POS 8
//! Field BEACON_A_WAKE - Reflects the output of ASP wake signal
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_A_WAKE_MASK 0x100u

//! Field BEACON_B_WAKE - Reflects the output of ASP wake signal
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_B_WAKE_POS 9
//! Field BEACON_B_WAKE - Reflects the output of ASP wake signal
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_B_WAKE_MASK 0x200u

//! Field BEACON_C_WAKE - Reflects the output of ASP wake signal
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_C_WAKE_POS 10
//! Field BEACON_C_WAKE - Reflects the output of ASP wake signal
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_C_WAKE_MASK 0x400u

//! Field BEACON_D_WAKE - Reflects the output of ASP wake signal
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_D_WAKE_POS 11
//! Field BEACON_D_WAKE - Reflects the output of ASP wake signal
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_D_WAKE_MASK 0x800u

//! Field BEACON_TEST - Beacon Test Enabling
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_TEST_POS 15
//! Field BEACON_TEST - Beacon Test Enabling
#define PMU_PDI_REGISTERS_BEACON_TEST_BEACON_TEST_MASK 0x8000u
//! Constant DISABLE - Beacon test is disabled
#define CONST_PMU_PDI_REGISTERS_BEACON_TEST_BEACON_TEST_DISABLE 0x0
//! Constant ENABLE - Beacon Test is enabled
#define CONST_PMU_PDI_REGISTERS_BEACON_TEST_BEACON_TEST_ENABLE 0x1

//! @}

//! @}

#endif
