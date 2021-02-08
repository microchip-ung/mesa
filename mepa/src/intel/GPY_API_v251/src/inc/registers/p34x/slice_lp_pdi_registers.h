//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_emouchel.priv.p34x_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/slice_control/slice_lp_registers_def.xml
// Register File Name  : SLICE_LP_PDI_REGISTERS
// Register File Title : SLICE_LP Control Registers
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _SLICE_LP_PDI_REGISTERS_H
#define _SLICE_LP_PDI_REGISTERS_H

//! \defgroup SLICE_LP_PDI_REGISTERS Register File SLICE_LP_PDI_REGISTERS - SLICE_LP Control Registers
//! @{

//! Base Address of SLICE_LP_PDI_REGISTERS
#define SLICE_LP_PDI_REGISTERS_MODULE_BASE 0x00A4CF20u

//! \defgroup SLICE_LP_PDI_REGISTERS_CTRL Register SLICE_LP_PDI_REGISTERS_CTRL - PMU LP Configuration Register
//! @{

//! Register Offset (relative)
#define SLICE_LP_PDI_REGISTERS_CTRL 0x0
//! Register Offset (absolute) for 1st Instance SLICE_LP_PDI_REGISTERS
#define SLICE_LP_PDI_REGISTERS_SLICE_LP_PDI_REGISTERS_CTRL 0x00A4CF20u

//! Register Reset Value
#define SLICE_LP_PDI_REGISTERS_CTRL_RST 0x00000D00u

//! Field OFFMSK3 - Power Off Mask Phy Energy Detect
#define SLICE_LP_PDI_REGISTERS_CTRL_OFFMSK3_POS 3
//! Field OFFMSK3 - Power Off Mask Phy Energy Detect
#define SLICE_LP_PDI_REGISTERS_CTRL_OFFMSK3_MASK 0x8u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_CTRL_OFFMSK3_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_CTRL_OFFMSK3_MSK 0x1

//! Field ONMSK3 - Power On Mask Phy Energy Detect
#define SLICE_LP_PDI_REGISTERS_CTRL_ONMSK3_POS 7
//! Field ONMSK3 - Power On Mask Phy Energy Detect
#define SLICE_LP_PDI_REGISTERS_CTRL_ONMSK3_MASK 0x80u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_CTRL_ONMSK3_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_CTRL_ONMSK3_MSK 0x1

//! Field BCON_EN - Beacon Enable
#define SLICE_LP_PDI_REGISTERS_CTRL_BCON_EN_POS 8
//! Field BCON_EN - Beacon Enable
#define SLICE_LP_PDI_REGISTERS_CTRL_BCON_EN_MASK 0x100u
//! Constant DIS - Beacon Disable
#define CONST_SLICE_LP_PDI_REGISTERS_CTRL_BCON_EN_DIS 0x0
//! Constant EN - Beacon Enable
#define CONST_SLICE_LP_PDI_REGISTERS_CTRL_BCON_EN_EN 0x1

//! Field ULP_EN - ULP Enable
#define SLICE_LP_PDI_REGISTERS_CTRL_ULP_EN_POS 9
//! Field ULP_EN - ULP Enable
#define SLICE_LP_PDI_REGISTERS_CTRL_ULP_EN_MASK 0x200u
//! Constant DIS - Normal operation
#define CONST_SLICE_LP_PDI_REGISTERS_CTRL_ULP_EN_DIS 0x0
//! Constant EN - Enable ULP
#define CONST_SLICE_LP_PDI_REGISTERS_CTRL_ULP_EN_EN 0x1

//! Field PMU_EN - PMU Enable
#define SLICE_LP_PDI_REGISTERS_CTRL_PMU_EN_POS 10
//! Field PMU_EN - PMU Enable
#define SLICE_LP_PDI_REGISTERS_CTRL_PMU_EN_MASK 0x400u
//! Constant DIS - PMU Disable
#define CONST_SLICE_LP_PDI_REGISTERS_CTRL_PMU_EN_DIS 0x0
//! Constant EN - PMU Enable
#define CONST_SLICE_LP_PDI_REGISTERS_CTRL_PMU_EN_EN 0x1

//! Field BCON_TOG - Beacon Toggle
#define SLICE_LP_PDI_REGISTERS_CTRL_BCON_TOG_POS 11
//! Field BCON_TOG - Beacon Toggle
#define SLICE_LP_PDI_REGISTERS_CTRL_BCON_TOG_MASK 0x800u
//! Constant DIS - Toggle Disable
#define CONST_SLICE_LP_PDI_REGISTERS_CTRL_BCON_TOG_DIS 0x0
//! Constant EN - Toggle Enable
#define CONST_SLICE_LP_PDI_REGISTERS_CTRL_BCON_TOG_EN 0x1

//! @}

//! \defgroup SLICE_LP_PDI_REGISTERS_PMU_CFG Register SLICE_LP_PDI_REGISTERS_PMU_CFG - PMU Configuration Register
//! @{

//! Register Offset (relative)
#define SLICE_LP_PDI_REGISTERS_PMU_CFG 0x4
//! Register Offset (absolute) for 1st Instance SLICE_LP_PDI_REGISTERS
#define SLICE_LP_PDI_REGISTERS_SLICE_LP_PDI_REGISTERS_PMU_CFG 0x00A4CF24u

//! Register Reset Value
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_RST 0x00000F5Au

//! Field WMSKA - Twisted Pair A Wake Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKA_POS 0
//! Field WMSKA - Twisted Pair A Wake Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKA_MASK 0x1u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKA_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKA_MSK 0x1

//! Field WMSKB - Twisted Pair B Wake Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKB_POS 1
//! Field WMSKB - Twisted Pair B Wake Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKB_MASK 0x2u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKB_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKB_MSK 0x1

//! Field WMSKC - Twisted Pair C Wake Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKC_POS 2
//! Field WMSKC - Twisted Pair C Wake Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKC_MASK 0x4u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKC_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKC_MSK 0x1

//! Field WMSKD - Twisted Pair D Wake Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKD_POS 3
//! Field WMSKD - Twisted Pair D Wake Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKD_MASK 0x8u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKD_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_WMSKD_MSK 0x1

//! Field BMSKAP - Twisted Pair A Positive Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKAP_POS 4
//! Field BMSKAP - Twisted Pair A Positive Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKAP_MASK 0x10u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKAP_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKAP_MSK 0x1

//! Field BMSKBP - Twisted Pair B Positive Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKBP_POS 5
//! Field BMSKBP - Twisted Pair B Positive Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKBP_MASK 0x20u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKBP_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKBP_MSK 0x1

//! Field BMSKCP - Twisted Pair C Positive Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKCP_POS 6
//! Field BMSKCP - Twisted Pair C Positive Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKCP_MASK 0x40u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKCP_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKCP_MSK 0x1

//! Field BMSKDP - Twisted Pair D Positive Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKDP_POS 7
//! Field BMSKDP - Twisted Pair D Positive Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKDP_MASK 0x80u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKDP_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKDP_MSK 0x1

//! Field BMSKAN - Twisted Pair A Negative Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKAN_POS 8
//! Field BMSKAN - Twisted Pair A Negative Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKAN_MASK 0x100u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKAN_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKAN_MSK 0x1

//! Field BMSKBN - Twisted Pair B Negative Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKBN_POS 9
//! Field BMSKBN - Twisted Pair B Negative Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKBN_MASK 0x200u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKBN_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKBN_MSK 0x1

//! Field BMSKCN - Twisted Pair C Negative Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKCN_POS 10
//! Field BMSKCN - Twisted Pair C Negative Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKCN_MASK 0x400u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKCN_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKCN_MSK 0x1

//! Field BMSKDN - Twisted Pair D Negative Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKDN_POS 11
//! Field BMSKDN - Twisted Pair D Negative Beacon Mask
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKDN_MASK 0x800u
//! Constant NOMSK - Mask Disable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKDN_NOMSK 0x0
//! Constant MSK - Mask Enable
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_BMSKDN_MSK 0x1

//! Field RES - Reserved
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_RES_POS 12
//! Field RES - Reserved
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_RES_MASK 0x3000u

//! Field ISO_OFF - Isolation Off
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_ISO_OFF_POS 14
//! Field ISO_OFF - Isolation Off
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_ISO_OFF_MASK 0x4000u
//! Constant ON - Isolation On
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_ISO_OFF_ON 0x0
//! Constant OFF - Isolation Off
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_ISO_OFF_OFF 0x1

//! Field SLICE_PD_DIS - Disable SxLP slice power down
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_SLICE_PD_DIS_POS 15
//! Field SLICE_PD_DIS - Disable SxLP slice power down
#define SLICE_LP_PDI_REGISTERS_PMU_CFG_SLICE_PD_DIS_MASK 0x8000u
//! Constant NORMAL - SxLP is changed by LP_AON
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_SLICE_PD_DIS_NORMAL 0x0
//! Constant DISABLE - SxLP is not changed by LP_AON
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_CFG_SLICE_PD_DIS_DISABLE 0x1

//! @}

//! \defgroup SLICE_LP_PDI_REGISTERS_PMU_STAT Register SLICE_LP_PDI_REGISTERS_PMU_STAT - PMU Status Register
//! @{

//! Register Offset (relative)
#define SLICE_LP_PDI_REGISTERS_PMU_STAT 0x8
//! Register Offset (absolute) for 1st Instance SLICE_LP_PDI_REGISTERS
#define SLICE_LP_PDI_REGISTERS_SLICE_LP_PDI_REGISTERS_PMU_STAT 0x00A4CF28u

//! Register Reset Value
#define SLICE_LP_PDI_REGISTERS_PMU_STAT_RST 0x00000000u

//! Field LP - LP status
#define SLICE_LP_PDI_REGISTERS_PMU_STAT_LP_POS 0
//! Field LP - LP status
#define SLICE_LP_PDI_REGISTERS_PMU_STAT_LP_MASK 0x1u
//! Constant NORMAL - Slice is active
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_STAT_LP_NORMAL 0x0
//! Constant LP - Slice is in LP mode
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_STAT_LP_LP 0x1

//! Field WAKELP - Wake from LP
#define SLICE_LP_PDI_REGISTERS_PMU_STAT_WAKELP_POS 3
//! Field WAKELP - Wake from LP
#define SLICE_LP_PDI_REGISTERS_PMU_STAT_WAKELP_MASK 0x8u
//! Constant NOWAKE - Not the wake up cause
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_STAT_WAKELP_NOWAKE 0x0
//! Constant WAKE - Wake up condition met
#define CONST_SLICE_LP_PDI_REGISTERS_PMU_STAT_WAKELP_WAKE 0x1

//! @}

//! \defgroup SLICE_LP_PDI_REGISTERS_BCON_CFG Register SLICE_LP_PDI_REGISTERS_BCON_CFG - PMU Beacon Configuration Register
//! @{

//! Register Offset (relative)
#define SLICE_LP_PDI_REGISTERS_BCON_CFG 0xC
//! Register Offset (absolute) for 1st Instance SLICE_LP_PDI_REGISTERS
#define SLICE_LP_PDI_REGISTERS_SLICE_LP_PDI_REGISTERS_BCON_CFG 0x00A4CF2Cu

//! Register Reset Value
#define SLICE_LP_PDI_REGISTERS_BCON_CFG_RST 0x00001F30u

//! Field BWIDTH - Beacon Width
#define SLICE_LP_PDI_REGISTERS_BCON_CFG_BWIDTH_POS 0
//! Field BWIDTH - Beacon Width
#define SLICE_LP_PDI_REGISTERS_BCON_CFG_BWIDTH_MASK 0xFu

//! Field BITVL - Beacon Interval
#define SLICE_LP_PDI_REGISTERS_BCON_CFG_BITVL_POS 4
//! Field BITVL - Beacon Interval
#define SLICE_LP_PDI_REGISTERS_BCON_CFG_BITVL_MASK 0xFFF0u

//! @}

//! \defgroup SLICE_LP_PDI_REGISTERS_BCON_STAT Register SLICE_LP_PDI_REGISTERS_BCON_STAT - PMU Beacon Status Register
//! @{

//! Register Offset (relative)
#define SLICE_LP_PDI_REGISTERS_BCON_STAT 0x10
//! Register Offset (absolute) for 1st Instance SLICE_LP_PDI_REGISTERS
#define SLICE_LP_PDI_REGISTERS_SLICE_LP_PDI_REGISTERS_BCON_STAT 0x00A4CF30u

//! Register Reset Value
#define SLICE_LP_PDI_REGISTERS_BCON_STAT_RST 0x00000000u

//! Field BWCNT - Beacon Width Count
#define SLICE_LP_PDI_REGISTERS_BCON_STAT_BWCNT_POS 0
//! Field BWCNT - Beacon Width Count
#define SLICE_LP_PDI_REGISTERS_BCON_STAT_BWCNT_MASK 0xFu

//! Field BICNT - Beacon Interval Count
#define SLICE_LP_PDI_REGISTERS_BCON_STAT_BICNT_POS 4
//! Field BICNT - Beacon Interval Count
#define SLICE_LP_PDI_REGISTERS_BCON_STAT_BICNT_MASK 0xFFF0u

//! @}

//! \defgroup SLICE_LP_PDI_REGISTERS_BCON_TOG Register SLICE_LP_PDI_REGISTERS_BCON_TOG - PMU Beacon Toggle Register
//! @{

//! Register Offset (relative)
#define SLICE_LP_PDI_REGISTERS_BCON_TOG 0x14
//! Register Offset (absolute) for 1st Instance SLICE_LP_PDI_REGISTERS
#define SLICE_LP_PDI_REGISTERS_SLICE_LP_PDI_REGISTERS_BCON_TOG 0x00A4CF34u

//! Register Reset Value
#define SLICE_LP_PDI_REGISTERS_BCON_TOG_RST 0x00000008u

//! Field TOG_CFG - Beacon Toggle Configuration
#define SLICE_LP_PDI_REGISTERS_BCON_TOG_TOG_CFG_POS 0
//! Field TOG_CFG - Beacon Toggle Configuration
#define SLICE_LP_PDI_REGISTERS_BCON_TOG_TOG_CFG_MASK 0xFFu

//! Field TOG_CNT - Beacon Toggle Count
#define SLICE_LP_PDI_REGISTERS_BCON_TOG_TOG_CNT_POS 8
//! Field TOG_CNT - Beacon Toggle Count
#define SLICE_LP_PDI_REGISTERS_BCON_TOG_TOG_CNT_MASK 0xFF00u

//! @}

//! \defgroup SLICE_LP_PDI_REGISTERS_GUARD_CFG Register SLICE_LP_PDI_REGISTERS_GUARD_CFG - Configure the non-listening guard window around beacon transmit window
//! @{

//! Register Offset (relative)
#define SLICE_LP_PDI_REGISTERS_GUARD_CFG 0x18
//! Register Offset (absolute) for 1st Instance SLICE_LP_PDI_REGISTERS
#define SLICE_LP_PDI_REGISTERS_SLICE_LP_PDI_REGISTERS_GUARD_CFG 0x00A4CF38u

//! Register Reset Value
#define SLICE_LP_PDI_REGISTERS_GUARD_CFG_RST 0x000083FFu

//! Field GWIDTH - Guard width
#define SLICE_LP_PDI_REGISTERS_GUARD_CFG_GWIDTH_POS 0
//! Field GWIDTH - Guard width
#define SLICE_LP_PDI_REGISTERS_GUARD_CFG_GWIDTH_MASK 0x3FFu

//! Field GUARD_EN - Enable non listen guard window
#define SLICE_LP_PDI_REGISTERS_GUARD_CFG_GUARD_EN_POS 15
//! Field GUARD_EN - Enable non listen guard window
#define SLICE_LP_PDI_REGISTERS_GUARD_CFG_GUARD_EN_MASK 0x8000u
//! Constant DISABLE - Guard window is not active
#define CONST_SLICE_LP_PDI_REGISTERS_GUARD_CFG_GUARD_EN_DISABLE 0x0
//! Constant ENABLE - Guard Window is active
#define CONST_SLICE_LP_PDI_REGISTERS_GUARD_CFG_GUARD_EN_ENABLE 0x1

//! @}

//! \defgroup SLICE_LP_PDI_REGISTERS_BEACON_TEST Register SLICE_LP_PDI_REGISTERS_BEACON_TEST - Expose the Beacon signals to/from ASP for test purpose
//! @{

//! Register Offset (relative)
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST 0x1C
//! Register Offset (absolute) for 1st Instance SLICE_LP_PDI_REGISTERS
#define SLICE_LP_PDI_REGISTERS_SLICE_LP_PDI_REGISTERS_BEACON_TEST 0x00A4CF3Cu

//! Register Reset Value
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_RST 0x00000000u

//! Field BEACON_AP_O - Output Beacon Positive to ASPA
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_AP_O_POS 0
//! Field BEACON_AP_O - Output Beacon Positive to ASPA
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_AP_O_MASK 0x1u

//! Field BEACON_AN_O - Output Beacon Negative to ASPA
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_AN_O_POS 1
//! Field BEACON_AN_O - Output Beacon Negative to ASPA
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_AN_O_MASK 0x2u

//! Field BEACON_BP_O - Output Beacon Positive to ASPB
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_BP_O_POS 2
//! Field BEACON_BP_O - Output Beacon Positive to ASPB
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_BP_O_MASK 0x4u

//! Field BEACON_BN_O - Output Beacon Negative to ASPB
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_BN_O_POS 3
//! Field BEACON_BN_O - Output Beacon Negative to ASPB
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_BN_O_MASK 0x8u

//! Field BEACON_CP_O - Output Beacon Positive to ASPC
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_CP_O_POS 4
//! Field BEACON_CP_O - Output Beacon Positive to ASPC
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_CP_O_MASK 0x10u

//! Field BEACON_CN_O - Output Beacon Negative to ASPC
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_CN_O_POS 5
//! Field BEACON_CN_O - Output Beacon Negative to ASPC
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_CN_O_MASK 0x20u

//! Field BEACON_DP_O - Output Beacon Positive to ASPD
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_DP_O_POS 6
//! Field BEACON_DP_O - Output Beacon Positive to ASPD
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_DP_O_MASK 0x40u

//! Field BEACON_DN_O - Output Beacon Negative to ASPD
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_DN_O_POS 7
//! Field BEACON_DN_O - Output Beacon Negative to ASPD
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_DN_O_MASK 0x80u

//! Field BEACON_A_WAKE - Reflects the output of ASP wake signal
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_A_WAKE_POS 8
//! Field BEACON_A_WAKE - Reflects the output of ASP wake signal
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_A_WAKE_MASK 0x100u

//! Field BEACON_B_WAKE - Reflects the output of ASP wake signal
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_B_WAKE_POS 9
//! Field BEACON_B_WAKE - Reflects the output of ASP wake signal
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_B_WAKE_MASK 0x200u

//! Field BEACON_C_WAKE - Reflects the output of ASP wake signal
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_C_WAKE_POS 10
//! Field BEACON_C_WAKE - Reflects the output of ASP wake signal
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_C_WAKE_MASK 0x400u

//! Field BEACON_D_WAKE - Reflects the output of ASP wake signal
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_D_WAKE_POS 11
//! Field BEACON_D_WAKE - Reflects the output of ASP wake signal
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_D_WAKE_MASK 0x800u

//! Field BEACON_TEST - Beacon Test Enabling
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_TEST_POS 15
//! Field BEACON_TEST - Beacon Test Enabling
#define SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_TEST_MASK 0x8000u
//! Constant DISABLE - Beacon test is disabled
#define CONST_SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_TEST_DISABLE 0x0
//! Constant ENABLE - Beacon Test is enabled
#define CONST_SLICE_LP_PDI_REGISTERS_BEACON_TEST_BEACON_TEST_ENABLE 0x1

//! @}

//! @}

#endif
