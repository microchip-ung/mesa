/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

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
// LSD Source          : /home/p31g/p31g_chip/v_hksim.priv.p31g_chip.top/ipg_lsd/lsd_sys/source_mdio/xml/reg_files/gphy_ropll_pdi_def.xml
// Register File Name  : GPHY_ROPLL_PDI
// Register File Title : Control/Status registers of GPHY CDB ROPLL
// Register Width      : 16
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _GPHY_ROPLL_PDI_H
#define _GPHY_ROPLL_PDI_H

//! \defgroup GPHY_ROPLL_PDI Register File GPHY_ROPLL_PDI - Control/Status registers of GPHY CDB ROPLL
//! @{

//! Base Address of GPHY_ROPLL_PDI
#define GPHY_ROPLL_PDI_MODULE_BASE 0x0001F100u

//! \defgroup GPHY_ROPLL_PDI_PLL_CFG0 Register GPHY_ROPLL_PDI_PLL_CFG0 - Configuration Register 0 of CDB ROPLL
//! @{

//! Register Offset (relative)
#define GPHY_ROPLL_PDI_PLL_CFG0 0x0
//! Register Offset (absolute) for 1st Instance GPHY_ROPLL_PDI
#define GPHY_ROPLL_PDI_GPHY_ROPLL_PDI_PLL_CFG0 0x0001F100u

//! Register Reset Value
#define GPHY_ROPLL_PDI_PLL_CFG0_RST 0x00CDu

//! Field PLL_RST - Resets the ROPLL
#define GPHY_ROPLL_PDI_PLL_CFG0_PLL_RST_POS 0
//! Field PLL_RST - Resets the ROPLL
#define GPHY_ROPLL_PDI_PLL_CFG0_PLL_RST_MASK 0x1u
//! Constant RSTN - Reset ROPLL requested
#define CONST_GPHY_ROPLL_PDI_PLL_CFG0_PLL_RST_RSTN 0x0
//! Constant NONE - no action
#define CONST_GPHY_ROPLL_PDI_PLL_CFG0_PLL_RST_NONE 0x1

//! Field PLL_L - Locked indication of PLL
#define GPHY_ROPLL_PDI_PLL_CFG0_PLL_L_POS 1
//! Field PLL_L - Locked indication of PLL
#define GPHY_ROPLL_PDI_PLL_CFG0_PLL_L_MASK 0x2u
//! Constant FREE - Free Running
#define CONST_GPHY_ROPLL_PDI_PLL_CFG0_PLL_L_FREE 0x0
//! Constant LOCK - ROPLL is locked
#define CONST_GPHY_ROPLL_PDI_PLL_CFG0_PLL_L_LOCK 0x1

//! Field PLL_N - Integer N factor, bits 6:0
#define GPHY_ROPLL_PDI_PLL_CFG0_PLL_N_POS 2
//! Field PLL_N - Integer N factor, bits 6:0
#define GPHY_ROPLL_PDI_PLL_CFG0_PLL_N_MASK 0x1FCu

//! Field PLL_K - Fractional K factor, bits 6:0
#define GPHY_ROPLL_PDI_PLL_CFG0_PLL_K_POS 9
//! Field PLL_K - Fractional K factor, bits 6:0
#define GPHY_ROPLL_PDI_PLL_CFG0_PLL_K_MASK 0xFE00u

//! @}

//! \defgroup GPHY_ROPLL_PDI_PLL_CFG1 Register GPHY_ROPLL_PDI_PLL_CFG1 - Configuration Register 1 of CDB ROPLL
//! @{

//! Register Offset (relative)
#define GPHY_ROPLL_PDI_PLL_CFG1 0x2
//! Register Offset (absolute) for 1st Instance GPHY_ROPLL_PDI
#define GPHY_ROPLL_PDI_GPHY_ROPLL_PDI_PLL_CFG1 0x0001F102u

//! Register Reset Value
#define GPHY_ROPLL_PDI_PLL_CFG1_RST 0x0000u

//! Field PLL_K - Fractional K factor, bits 20:7
#define GPHY_ROPLL_PDI_PLL_CFG1_PLL_K_POS 0
//! Field PLL_K - Fractional K factor, bits 20:7
#define GPHY_ROPLL_PDI_PLL_CFG1_PLL_K_MASK 0x3FFFu

//! Field PLL_BP - PLL Bypass
#define GPHY_ROPLL_PDI_PLL_CFG1_PLL_BP_POS 14
//! Field PLL_BP - PLL Bypass
#define GPHY_ROPLL_PDI_PLL_CFG1_PLL_BP_MASK 0x4000u
//! Constant NORMAL - ROPLL is in normal operation with clocks from VCO
#define CONST_GPHY_ROPLL_PDI_PLL_CFG1_PLL_BP_NORMAL 0x0
//! Constant BYPASS - ROPLL output clocks are bypassed and only CLKREF is provided on all outpu...
#define CONST_GPHY_ROPLL_PDI_PLL_CFG1_PLL_BP_BYPASS 0x1

//! Field PLL_BUFF_OUT - Enable the CML REF_CLK output buffer
#define GPHY_ROPLL_PDI_PLL_CFG1_PLL_BUFF_OUT_POS 15
//! Field PLL_BUFF_OUT - Enable the CML REF_CLK output buffer
#define GPHY_ROPLL_PDI_PLL_CFG1_PLL_BUFF_OUT_MASK 0x8000u
//! Constant DISABLE - disable CLKREF CML output
#define CONST_GPHY_ROPLL_PDI_PLL_CFG1_PLL_BUFF_OUT_DISABLE 0x0
//! Constant ENABLE - CLKREF CML output buffer enable
#define CONST_GPHY_ROPLL_PDI_PLL_CFG1_PLL_BUFF_OUT_ENABLE 0x1

//! @}

//! \defgroup GPHY_ROPLL_PDI_PLL_CFG2 Register GPHY_ROPLL_PDI_PLL_CFG2 - Configuration Register 2 of CDB ROPLL
//! @{

//! Register Offset (relative)
#define GPHY_ROPLL_PDI_PLL_CFG2 0x4
//! Register Offset (absolute) for 1st Instance GPHY_ROPLL_PDI
#define GPHY_ROPLL_PDI_GPHY_ROPLL_PDI_PLL_CFG2 0x0001F104u

//! Register Reset Value
#define GPHY_ROPLL_PDI_PLL_CFG2_RST 0x3531u

//! Field PLL_CLK1 - ROPLL output frequency select,CLK1
#define GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_POS 0
//! Field PLL_CLK1 - ROPLL output frequency select,CLK1
#define GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_MASK 0xFu
//! Constant REF - input reference clock
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_REF 0x0
//! Constant DIV2 - VCO Clock divide by 2
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV2 0x1
//! Constant DIV3 - VCO Clock divide by 3
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV3 0x2
//! Constant DIV4 - VCO Clock divide by 4
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV4 0x3
//! Constant DIV5 - VCO Clock divide by 5
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV5 0x4
//! Constant DIV6 - VCO Clock divide by 6
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV6 0x5
//! Constant DIV8 - VCO Clock divide by 8
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV8 0x6
//! Constant DIV10 - VCO Clock divide by 10
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV10 0x7
//! Constant DIV12 - VCO Clock divide by 12
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV12 0x8
//! Constant DIV16 - VCO Clock divide by 16
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV16 0x9
//! Constant DIV20 - VCO Clock divide by 20
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV20 0xA
//! Constant DIV24 - VCO Clock divide by 24
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV24 0xB
//! Constant DIV32 - VCO Clock divide by 32
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV32 0xC
//! Constant DIV40 - VCO Clock divide by 40
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV40 0xD
//! Constant DIV48 - VCO Clock divide by 48
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV48 0xE
//! Constant DIV64 - VCO Clock divide by 64
#define CONST_GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK1_DIV64 0xF

//! Field PLL_CLK2 - ROPLL output frequency select,CLK2
#define GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK2_POS 4
//! Field PLL_CLK2 - ROPLL output frequency select,CLK2
#define GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK2_MASK 0xF0u

//! Field PLL_CLK3 - ROPLL output frequency select,CLK3
#define GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK3_POS 8
//! Field PLL_CLK3 - ROPLL output frequency select,CLK3
#define GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK3_MASK 0xF00u

//! Field PLL_CLK4 - ROPLL output frequency select,CLK4
#define GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK4_POS 12
//! Field PLL_CLK4 - ROPLL output frequency select,CLK4
#define GPHY_ROPLL_PDI_PLL_CFG2_PLL_CLK4_MASK 0xF000u

//! @}

//! \defgroup GPHY_ROPLL_PDI_PLL_CFG3 Register GPHY_ROPLL_PDI_PLL_CFG3 - Configuration Register 3 of CDB ROPLL
//! @{

//! Register Offset (relative)
#define GPHY_ROPLL_PDI_PLL_CFG3 0x6
//! Register Offset (absolute) for 1st Instance GPHY_ROPLL_PDI
#define GPHY_ROPLL_PDI_GPHY_ROPLL_PDI_PLL_CFG3 0x0001F106u

//! Register Reset Value
#define GPHY_ROPLL_PDI_PLL_CFG3_RST 0x0160u

//! Field PLL_CLK5 - ROPLL CML CLK5 output buffer frequency selection
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_CLK5_POS 0
//! Field PLL_CLK5 - ROPLL CML CLK5 output buffer frequency selection
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_CLK5_MASK 0x3u
//! Constant DIV4 - VCO Clock divide by 4
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_CLK5_DIV4 0x0
//! Constant DIV6 - VCO Clock divide by 6
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_CLK5_DIV6 0x1
//! Constant DIV8 - VCO Clock divide by 8
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_CLK5_DIV8 0x2
//! Constant DIV12 - VCO Clock divide by 12
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_CLK5_DIV12 0x3

//! Field PLL_OPD1 - ROPLL CLK1 output buffer power down
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD1_POS 2
//! Field PLL_OPD1 - ROPLL CLK1 output buffer power down
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD1_MASK 0x4u
//! Constant NORMAL - buffer is active
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD1_NORMAL 0x0
//! Constant PD - buffer is power down
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD1_PD 0x1

//! Field PLL_OPD2 - ROPLL CLK2 output buffer power down
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD2_POS 3
//! Field PLL_OPD2 - ROPLL CLK2 output buffer power down
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD2_MASK 0x8u
//! Constant NORMAL - buffer is active
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD2_NORMAL 0x0
//! Constant PD - buffer is power down
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD2_PD 0x1

//! Field PLL_OPD3 - ROPLL CLK3 output buffer power down
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD3_POS 4
//! Field PLL_OPD3 - ROPLL CLK3 output buffer power down
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD3_MASK 0x10u
//! Constant NORMAL - buffer is active
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD3_NORMAL 0x0
//! Constant PD - buffer is power down
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD3_PD 0x1

//! Field PLL_OPD4 - ROPLL CLK4 output buffer power down
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD4_POS 5
//! Field PLL_OPD4 - ROPLL CLK4 output buffer power down
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD4_MASK 0x20u
//! Constant NORMAL - buffer is active
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD4_NORMAL 0x0
//! Constant PD - buffer is power down
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD4_PD 0x1

//! Field PLL_OPD5 - ROPLL CLK5 output buffer power down
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD5_POS 6
//! Field PLL_OPD5 - ROPLL CLK5 output buffer power down
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD5_MASK 0x40u
//! Constant NORMAL - buffer is active
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD5_NORMAL 0x0
//! Constant PD - buffer is power down
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_OPD5_PD 0x1

//! Field PLL_N_MODE - Integer N mode En
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_N_MODE_POS 7
//! Field PLL_N_MODE - Integer N mode En
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_N_MODE_MASK 0x80u
//! Constant FRAC - Fractional Mode with SSC
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_N_MODE_FRAC 0x0
//! Constant INT - Integer-N Mode only
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_N_MODE_INT 0x1

//! Field PLL_SSC - Spread Spectrum Clocking disable
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_SSC_POS 8
//! Field PLL_SSC - Spread Spectrum Clocking disable
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_SSC_MASK 0x100u
//! Constant ENABLE - Enable SSC
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_SSC_ENABLE 0x0
//! Constant DISABLE - DISABLE SSC
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_SSC_DISABLE 0x1

//! Field INVCLK - Output Clock Inversion
#define GPHY_ROPLL_PDI_PLL_CFG3_INVCLK_POS 9
//! Field INVCLK - Output Clock Inversion
#define GPHY_ROPLL_PDI_PLL_CFG3_INVCLK_MASK 0x1E00u

//! Field PLL_BW - PLL Bandwidth Select
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_BW_POS 14
//! Field PLL_BW - PLL Bandwidth Select
#define GPHY_ROPLL_PDI_PLL_CFG3_PLL_BW_MASK 0xC000u
//! Constant BW0 - 25MHz X0: 500kHz, 36/40MHz XO: 700kHz
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_BW_BW0 0x0
//! Constant BW1 - 25MHz X0: 577kHz, 36/40MHz XO: 780kHz
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_BW_BW1 0x1
//! Constant BW2 - 25MHz X0: 408kHz, 36/40MHz XO: 495kHz
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_BW_BW2 0x2
//! Constant BW3 - 25MHz X0: 645kHz, 36/40MHz XO: 606kHz
#define CONST_GPHY_ROPLL_PDI_PLL_CFG3_PLL_BW_BW3 0x3

//! @}

//! \defgroup GPHY_ROPLL_PDI_PLL_MISC Register GPHY_ROPLL_PDI_PLL_MISC - Miscellaneous control register of ROPLL
//! @{

//! Register Offset (relative)
#define GPHY_ROPLL_PDI_PLL_MISC 0x8
//! Register Offset (absolute) for 1st Instance GPHY_ROPLL_PDI
#define GPHY_ROPLL_PDI_GPHY_ROPLL_PDI_PLL_MISC 0x0001F108u

//! Register Reset Value
#define GPHY_ROPLL_PDI_PLL_MISC_RST 0x00D4u

//! Field MPROG - PLL Mode Sel
#define GPHY_ROPLL_PDI_PLL_MISC_MPROG_POS 0
//! Field MPROG - PLL Mode Sel
#define GPHY_ROPLL_PDI_PLL_MISC_MPROG_MASK 0x7u
//! Constant TM - Test Mode
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_MPROG_TM 0x0
//! Constant PLL0A - GRX application, PLL0A mode
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_MPROG_PLL0A 0x1
//! Constant PLL0B - GRX application, PLL0B mode
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_MPROG_PLL0B 0x2
//! Constant PLL1 - GRX application, PLL1 mode
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_MPROG_PLL1 0x3
//! Constant GPHY - GPHY ROPLL mode
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_MPROG_GPHY 0x4
//! Constant WLAN - WAVE application mode
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_MPROG_WLAN 0x5

//! Field MODE - Selects CML/CMOS input Clock
#define GPHY_ROPLL_PDI_PLL_MISC_MODE_POS 3
//! Field MODE - Selects CML/CMOS input Clock
#define GPHY_ROPLL_PDI_PLL_MISC_MODE_MASK 0x8u
//! Constant CML - CML differential input clock selected
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_MODE_CML 0x0
//! Constant CMOS - CMOS differential input clock selected
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_MODE_CMOS 0x1

//! Field CLKSEL - PLL input clock select
#define GPHY_ROPLL_PDI_PLL_MISC_CLKSEL_POS 4
//! Field CLKSEL - PLL input clock select
#define GPHY_ROPLL_PDI_PLL_MISC_CLKSEL_MASK 0x30u
//! Constant XTAL36 - RefCLK is 36MHz
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_CLKSEL_XTAL36 0x0
//! Constant XTAL40 - RefCLK is 40MHz
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_CLKSEL_XTAL40 0x1
//! Constant XTAL25 - RefCLK is 25MHz
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_CLKSEL_XTAL25 0x2
//! Constant XTAL125 - RefCLK is 125MHz
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_CLKSEL_XTAL125 0x3

//! Field FPUP - Force Power up of all Divider chains
#define GPHY_ROPLL_PDI_PLL_MISC_FPUP_POS 6
//! Field FPUP - Force Power up of all Divider chains
#define GPHY_ROPLL_PDI_PLL_MISC_FPUP_MASK 0x40u
//! Constant NORMAL - Power up the divider chains according to mode select LUT
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_FPUP_NORMAL 0x0
//! Constant FORCE - All divider chain output are forced to power up
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_FPUP_FORCE 0x1

//! Field INKSEL - selects if ROPLL internal mapped N,K or based on PLL_CFG0/1 N,K
#define GPHY_ROPLL_PDI_PLL_MISC_INKSEL_POS 7
//! Field INKSEL - selects if ROPLL internal mapped N,K or based on PLL_CFG0/1 N,K
#define GPHY_ROPLL_PDI_PLL_MISC_INKSEL_MASK 0x80u

//! Field IOPFSEL - Selects if ROPLL internal digital allocates the default output frequecies.
#define GPHY_ROPLL_PDI_PLL_MISC_IOPFSEL_POS 8
//! Field IOPFSEL - Selects if ROPLL internal digital allocates the default output frequecies.
#define GPHY_ROPLL_PDI_PLL_MISC_IOPFSEL_MASK 0x100u
//! Constant EXT - PDI selected output frequencies are used for CLK1-CLK4
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_IOPFSEL_EXT 0x0
//! Constant INT - Internal LUT used for the CLK1-CLK4 frequency selection
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_IOPFSEL_INT 0x1

//! Field IPOK - Internal POK Override
#define GPHY_ROPLL_PDI_PLL_MISC_IPOK_POS 9
//! Field IPOK - Internal POK Override
#define GPHY_ROPLL_PDI_PLL_MISC_IPOK_MASK 0x200u
//! Constant ENABLE - Internal check for Power OK state of the LDO
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_IPOK_ENABLE 0x0
//! Constant OVR - Internal Power OK module disabled
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_IPOK_OVR 0x1

//! Field LCKOVR - PLL Lock Overwrite
#define GPHY_ROPLL_PDI_PLL_MISC_LCKOVR_POS 10
//! Field LCKOVR - PLL Lock Overwrite
#define GPHY_ROPLL_PDI_PLL_MISC_LCKOVR_MASK 0x400u

//! Field EXTREF - Select External Reference Current
#define GPHY_ROPLL_PDI_PLL_MISC_EXTREF_POS 11
//! Field EXTREF - Select External Reference Current
#define GPHY_ROPLL_PDI_PLL_MISC_EXTREF_MASK 0x800u
//! Constant INT - Use Internally generated REFERENCE BIASING current
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_EXTREF_INT 0x0
//! Constant EXT - Use Externally generated REFERENCE BIASING current
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_EXTREF_EXT 0x1

//! Field VEXT - PLL output buffer power supply
#define GPHY_ROPLL_PDI_PLL_MISC_VEXT_POS 12
//! Field VEXT - PLL output buffer power supply
#define GPHY_ROPLL_PDI_PLL_MISC_VEXT_MASK 0x1000u
//! Constant INT - Use Internally generated 1.2V supply
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_VEXT_INT 0x0
//! Constant EXT - Use Externally generated 1.2V supply
#define CONST_GPHY_ROPLL_PDI_PLL_MISC_VEXT_EXT 0x1

//! Field FORCE - Force Latching Of Shadow Registers
#define GPHY_ROPLL_PDI_PLL_MISC_FORCE_POS 13
//! Field FORCE - Force Latching Of Shadow Registers
#define GPHY_ROPLL_PDI_PLL_MISC_FORCE_MASK 0x2000u

//! Field UNLCK - Sticky bit for unlock status
#define GPHY_ROPLL_PDI_PLL_MISC_UNLCK_POS 14
//! Field UNLCK - Sticky bit for unlock status
#define GPHY_ROPLL_PDI_PLL_MISC_UNLCK_MASK 0x4000u

//! Field PSOVR - Pinstrap overwrite
#define GPHY_ROPLL_PDI_PLL_MISC_PSOVR_POS 15
//! Field PSOVR - Pinstrap overwrite
#define GPHY_ROPLL_PDI_PLL_MISC_PSOVR_MASK 0x8000u

//! @}

//! @}

#endif
