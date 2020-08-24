//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_emouchel.priv.p34x_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/slice_sgmii/sgmii_phy_registers_def.xml
// Register File Name  : SGMII_PHY_REGISTERS
// Register File Title : SGMII_PHY Registers
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _SGMII_PHY_REGISTERS_H
#define _SGMII_PHY_REGISTERS_H

//! \defgroup SGMII_PHY_REGISTERS Register File SGMII_PHY_REGISTERS - SGMII_PHY Registers
//! @{

//! Base Address of SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_MODULE_BASE 0x00A34000u

//! \defgroup SGMII_PHY_RESETN Register SGMII_PHY_RESETN - SGMII PHY RESETN
//! @{

//! Register Offset (relative)
#define SGMII_PHY_RESETN 0x0
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_RESETN 0x00A34000u

//! Register Reset Value
#define SGMII_PHY_RESETN_RST 0x00000001u

//! Field RESET_N - RESET_N
#define SGMII_PHY_RESETN_RESET_N_POS 0
//! Field RESET_N - RESET_N
#define SGMII_PHY_RESETN_RESET_N_MASK 0x1u
//! Constant RESET - RESET
#define CONST_SGMII_PHY_RESETN_RESET_N_RESET 0x0
//! Constant NOT_RESET - NO_RESET
#define CONST_SGMII_PHY_RESETN_RESET_N_NOT_RESET 0x1

//! @}

//! \defgroup SGMII_PHY_MPLL_CFG1 Register SGMII_PHY_MPLL_CFG1 - SGMII PHY MPLL CFG1
//! @{

//! Register Offset (relative)
#define SGMII_PHY_MPLL_CFG1 0x4
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_MPLL_CFG1 0x00A34004u

//! Register Reset Value
#define SGMII_PHY_MPLL_CFG1_RST 0x00000000u

//! Field MPLL_EN - mpll_en
#define SGMII_PHY_MPLL_CFG1_MPLL_EN_POS 0
//! Field MPLL_EN - mpll_en
#define SGMII_PHY_MPLL_CFG1_MPLL_EN_MASK 0x1u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_MPLL_CFG1_MPLL_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_MPLL_CFG1_MPLL_EN_ENABLE 0x1

//! Field MPLL_MULTIPLIER - mpll_multiplier
#define SGMII_PHY_MPLL_CFG1_MPLL_MULTIPLIER_POS 1
//! Field MPLL_MULTIPLIER - mpll_multiplier
#define SGMII_PHY_MPLL_CFG1_MPLL_MULTIPLIER_MASK 0xFEu

//! Field REF_CLKDIV2 - ref_clkdiv2
#define SGMII_PHY_MPLL_CFG1_REF_CLKDIV2_POS 8
//! Field REF_CLKDIV2 - ref_clkdiv2
#define SGMII_PHY_MPLL_CFG1_REF_CLKDIV2_MASK 0x100u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_MPLL_CFG1_REF_CLKDIV2_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_MPLL_CFG1_REF_CLKDIV2_ENABLE 0x1

//! Field REF_USE_PAD - ref_use_pad
#define SGMII_PHY_MPLL_CFG1_REF_USE_PAD_POS 10
//! Field REF_USE_PAD - ref_use_pad
#define SGMII_PHY_MPLL_CFG1_REF_USE_PAD_MASK 0x400u
//! Constant USE_ALT - DISABLE
#define CONST_SGMII_PHY_MPLL_CFG1_REF_USE_PAD_USE_ALT 0x0
//! Constant USE_EXT_PAD - ENABLE
#define CONST_SGMII_PHY_MPLL_CFG1_REF_USE_PAD_USE_EXT_PAD 0x1

//! @}

//! \defgroup SGMII_PHY_MPLL_CFG2 Register SGMII_PHY_MPLL_CFG2 - SGMII PHY MPLL CFG2
//! @{

//! Register Offset (relative)
#define SGMII_PHY_MPLL_CFG2 0x8
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_MPLL_CFG2 0x00A34008u

//! Register Reset Value
#define SGMII_PHY_MPLL_CFG2_RST 0x00000000u

//! Field SSC_REF_CLK_SEL - ssc_ref_clk_sel
#define SGMII_PHY_MPLL_CFG2_SSC_REF_CLK_SEL_POS 0
//! Field SSC_REF_CLK_SEL - ssc_ref_clk_sel
#define SGMII_PHY_MPLL_CFG2_SSC_REF_CLK_SEL_MASK 0x1FFu

//! @}

//! \defgroup SGMII_PHY_RX0_CFG1 Register SGMII_PHY_RX0_CFG1 - SGMII PHY RX0 CFG1
//! @{

//! Register Offset (relative)
#define SGMII_PHY_RX0_CFG1 0xC
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_RX0_CFG1 0x00A3400Cu

//! Register Reset Value
#define SGMII_PHY_RX0_CFG1_RST 0x00000000u

//! Field RX0_ALIGN_EN - rx0_align_en
#define SGMII_PHY_RX0_CFG1_RX0_ALIGN_EN_POS 0
//! Field RX0_ALIGN_EN - rx0_align_en
#define SGMII_PHY_RX0_CFG1_RX0_ALIGN_EN_MASK 0x1u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_RX0_CFG1_RX0_ALIGN_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_RX0_CFG1_RX0_ALIGN_EN_ENABLE 0x1

//! Field RX0_DATA_EN - rx0_data_en
#define SGMII_PHY_RX0_CFG1_RX0_DATA_EN_POS 1
//! Field RX0_DATA_EN - rx0_data_en
#define SGMII_PHY_RX0_CFG1_RX0_DATA_EN_MASK 0x2u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_RX0_CFG1_RX0_DATA_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_RX0_CFG1_RX0_DATA_EN_ENABLE 0x1

//! Field RX0_PLL_EN - rx0_pll_en
#define SGMII_PHY_RX0_CFG1_RX0_PLL_EN_POS 2
//! Field RX0_PLL_EN - rx0_pll_en
#define SGMII_PHY_RX0_CFG1_RX0_PLL_EN_MASK 0x4u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_RX0_CFG1_RX0_PLL_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_RX0_CFG1_RX0_PLL_EN_ENABLE 0x1

//! Field RX0_RATE - rx0_rate
#define SGMII_PHY_RX0_CFG1_RX0_RATE_POS 3
//! Field RX0_RATE - rx0_rate
#define SGMII_PHY_RX0_CFG1_RX0_RATE_MASK 0x18u

//! Field RX0_RESET - rx0_reset
#define SGMII_PHY_RX0_CFG1_RX0_RESET_POS 5
//! Field RX0_RESET - rx0_reset
#define SGMII_PHY_RX0_CFG1_RX0_RESET_MASK 0x20u
//! Constant NOT_RESET - NO_RESET
#define CONST_SGMII_PHY_RX0_CFG1_RX0_RESET_NOT_RESET 0x0
//! Constant RESET - RESET
#define CONST_SGMII_PHY_RX0_CFG1_RX0_RESET_RESET 0x1

//! @}

//! \defgroup SGMII_PHY_RX0_CFG2 Register SGMII_PHY_RX0_CFG2 - SGMII PHY RX0 CFG2
//! @{

//! Register Offset (relative)
#define SGMII_PHY_RX0_CFG2 0x10
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_RX0_CFG2 0x00A34010u

//! Register Reset Value
#define SGMII_PHY_RX0_CFG2_RST 0x00000532u

//! Field RX0_EQ - rx0_eq
#define SGMII_PHY_RX0_CFG2_RX0_EQ_POS 0
//! Field RX0_EQ - rx0_eq
#define SGMII_PHY_RX0_CFG2_RX0_EQ_MASK 0x7u

//! Field RX0_INVERT - rx0_invert
#define SGMII_PHY_RX0_CFG2_RX0_INVERT_POS 3
//! Field RX0_INVERT - rx0_invert
#define SGMII_PHY_RX0_CFG2_RX0_INVERT_MASK 0x8u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_RX0_CFG2_RX0_INVERT_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_RX0_CFG2_RX0_INVERT_ENABLE 0x1

//! Field RX0_LOS_EN - rx0_los_en
#define SGMII_PHY_RX0_CFG2_RX0_LOS_EN_POS 4
//! Field RX0_LOS_EN - rx0_los_en
#define SGMII_PHY_RX0_CFG2_RX0_LOS_EN_MASK 0x10u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_RX0_CFG2_RX0_LOS_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_RX0_CFG2_RX0_LOS_EN_ENABLE 0x1

//! Field RX0_TERM_EN - rx0_term_en
#define SGMII_PHY_RX0_CFG2_RX0_TERM_EN_POS 5
//! Field RX0_TERM_EN - rx0_term_en
#define SGMII_PHY_RX0_CFG2_RX0_TERM_EN_MASK 0x20u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_RX0_CFG2_RX0_TERM_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_RX0_CFG2_RX0_TERM_EN_ENABLE 0x1

//! Field RX0_LOS_FILT_CNT - rx0_los_filt_cnt
#define SGMII_PHY_RX0_CFG2_RX0_LOS_FILT_CNT_POS 6
//! Field RX0_LOS_FILT_CNT - rx0_los_filt_cnt
#define SGMII_PHY_RX0_CFG2_RX0_LOS_FILT_CNT_MASK 0x1FC0u

//! @}

//! \defgroup SGMII_PHY_TX0_CFG1 Register SGMII_PHY_TX0_CFG1 - SGMII PHY TX0 CFG1
//! @{

//! Register Offset (relative)
#define SGMII_PHY_TX0_CFG1 0x14
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_TX0_CFG1 0x00A34014u

//! Register Reset Value
#define SGMII_PHY_TX0_CFG1_RST 0x00000000u

//! Field TX0_CM_EN - tx0_cm_en
#define SGMII_PHY_TX0_CFG1_TX0_CM_EN_POS 0
//! Field TX0_CM_EN - tx0_cm_en
#define SGMII_PHY_TX0_CFG1_TX0_CM_EN_MASK 0x1u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_TX0_CFG1_TX0_CM_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_TX0_CFG1_TX0_CM_EN_ENABLE 0x1

//! Field TX0_DATA_EN - tx0_data_en
#define SGMII_PHY_TX0_CFG1_TX0_DATA_EN_POS 1
//! Field TX0_DATA_EN - tx0_data_en
#define SGMII_PHY_TX0_CFG1_TX0_DATA_EN_MASK 0x2u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_TX0_CFG1_TX0_DATA_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_TX0_CFG1_TX0_DATA_EN_ENABLE 0x1

//! Field TX0_EN - tx0_en
#define SGMII_PHY_TX0_CFG1_TX0_EN_POS 2
//! Field TX0_EN - tx0_en
#define SGMII_PHY_TX0_CFG1_TX0_EN_MASK 0x4u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_TX0_CFG1_TX0_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_TX0_CFG1_TX0_EN_ENABLE 0x1

//! Field TX0_RATE - tx0_rate
#define SGMII_PHY_TX0_CFG1_TX0_RATE_POS 3
//! Field TX0_RATE - tx0_rate
#define SGMII_PHY_TX0_CFG1_TX0_RATE_MASK 0x18u

//! Field TX0_RESET - tx0_reset
#define SGMII_PHY_TX0_CFG1_TX0_RESET_POS 5
//! Field TX0_RESET - tx0_reset
#define SGMII_PHY_TX0_CFG1_TX0_RESET_MASK 0x20u
//! Constant NOT_RESET - NO_RESET
#define CONST_SGMII_PHY_TX0_CFG1_TX0_RESET_NOT_RESET 0x0
//! Constant RESET - RESET
#define CONST_SGMII_PHY_TX0_CFG1_TX0_RESET_RESET 0x1

//! @}

//! \defgroup SGMII_PHY_TX0_CFG2 Register SGMII_PHY_TX0_CFG2 - SGMII PHY TX0 CFG2
//! @{

//! Register Offset (relative)
#define SGMII_PHY_TX0_CFG2 0x18
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_TX0_CFG2 0x00A34018u

//! Register Reset Value
#define SGMII_PHY_TX0_CFG2_RST 0x0000007Fu

//! Field TX0_AMPLITUDE - tx0_amplitude
#define SGMII_PHY_TX0_CFG2_TX0_AMPLITUDE_POS 0
//! Field TX0_AMPLITUDE - tx0_amplitude
#define SGMII_PHY_TX0_CFG2_TX0_AMPLITUDE_MASK 0x7Fu

//! Field TX0_TERM_OFFSET - tx0_term_offset
#define SGMII_PHY_TX0_CFG2_TX0_TERM_OFFSET_POS 7
//! Field TX0_TERM_OFFSET - tx0_term_offset
#define SGMII_PHY_TX0_CFG2_TX0_TERM_OFFSET_MASK 0xF80u

//! @}

//! \defgroup SGMII_PHY_TX0_CFG3 Register SGMII_PHY_TX0_CFG3 - SGMII PHY TX0 CFG3
//! @{

//! Register Offset (relative)
#define SGMII_PHY_TX0_CFG3 0x1C
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_TX0_CFG3 0x00A3401Cu

//! Register Reset Value
#define SGMII_PHY_TX0_CFG3_RST 0x00000800u

//! Field TX0_PREEMPHASIS - tx0_preemph
#define SGMII_PHY_TX0_CFG3_TX0_PREEMPHASIS_POS 0
//! Field TX0_PREEMPHASIS - tx0_preemph
#define SGMII_PHY_TX0_CFG3_TX0_PREEMPHASIS_MASK 0x7Fu

//! Field TX0_DETECT_RX_REQ - tx0_detect_rx_req
#define SGMII_PHY_TX0_CFG3_TX0_DETECT_RX_REQ_POS 7
//! Field TX0_DETECT_RX_REQ - tx0_detect_rx_req
#define SGMII_PHY_TX0_CFG3_TX0_DETECT_RX_REQ_MASK 0x80u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_TX0_CFG3_TX0_DETECT_RX_REQ_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_TX0_CFG3_TX0_DETECT_RX_REQ_ENABLE 0x1

//! Field TX0_INVERT - tx0_invert
#define SGMII_PHY_TX0_CFG3_TX0_INVERT_POS 8
//! Field TX0_INVERT - tx0_invert
#define SGMII_PHY_TX0_CFG3_TX0_INVERT_MASK 0x100u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_TX0_CFG3_TX0_INVERT_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_TX0_CFG3_TX0_INVERT_ENABLE 0x1

//! Field TX0_VBOOST_LEVEL - tx0_vboost_lvl
#define SGMII_PHY_TX0_CFG3_TX0_VBOOST_LEVEL_POS 9
//! Field TX0_VBOOST_LEVEL - tx0_vboost_lvl
#define SGMII_PHY_TX0_CFG3_TX0_VBOOST_LEVEL_MASK 0xE00u

//! Field TX0_VBOOST_EN - tx0_vboost_en
#define SGMII_PHY_TX0_CFG3_TX0_VBOOST_EN_POS 12
//! Field TX0_VBOOST_EN - tx0_vboost_en
#define SGMII_PHY_TX0_CFG3_TX0_VBOOST_EN_MASK 0x1000u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_TX0_CFG3_TX0_VBOOST_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_TX0_CFG3_TX0_VBOOST_EN_ENABLE 0x1

//! @}

//! \defgroup SGMII_PHY_MISC Register SGMII_PHY_MISC - SGMII PHY MISC
//! @{

//! Register Offset (relative)
#define SGMII_PHY_MISC 0x20
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_MISC 0x00A34020u

//! Register Reset Value
#define SGMII_PHY_MISC_RST 0x00000254u

//! Field VREG_BYPASS - vreg_bypass
#define SGMII_PHY_MISC_VREG_BYPASS_POS 0
//! Field VREG_BYPASS - vreg_bypass
#define SGMII_PHY_MISC_VREG_BYPASS_MASK 0x1u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_MISC_VREG_BYPASS_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_MISC_VREG_BYPASS_ENABLE 0x1

//! Field LANE_LOOPBACK_EN - lane_lpbk_en
#define SGMII_PHY_MISC_LANE_LOOPBACK_EN_POS 1
//! Field LANE_LOOPBACK_EN - lane_lpbk_en
#define SGMII_PHY_MISC_LANE_LOOPBACK_EN_MASK 0x2u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_MISC_LANE_LOOPBACK_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_MISC_LANE_LOOPBACK_EN_ENABLE 0x1

//! Field LANE_10BIT_SEL - lane_10bit_sel
#define SGMII_PHY_MISC_LANE_10BIT_SEL_POS 2
//! Field LANE_10BIT_SEL - lane_10bit_sel
#define SGMII_PHY_MISC_LANE_10BIT_SEL_MASK 0x4u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_MISC_LANE_10BIT_SEL_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_MISC_LANE_10BIT_SEL_ENABLE 0x1

//! Field LOS_BIAS - los_bias
#define SGMII_PHY_MISC_LOS_BIAS_POS 3
//! Field LOS_BIAS - los_bias
#define SGMII_PHY_MISC_LOS_BIAS_MASK 0x38u

//! Field LOS_LEVEL - los_level
#define SGMII_PHY_MISC_LOS_LEVEL_POS 6
//! Field LOS_LEVEL - los_level
#define SGMII_PHY_MISC_LOS_LEVEL_MASK 0x7C0u

//! @}

//! \defgroup SGMII_PHY_HWBU_CTRL Register SGMII_PHY_HWBU_CTRL - SGMII PHY HWBU CTRL
//! @{

//! Register Offset (relative)
#define SGMII_PHY_HWBU_CTRL 0x24
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_HWBU_CTRL 0x00A34024u

//! Register Reset Value
#define SGMII_PHY_HWBU_CTRL_RST 0x00000188u

//! Field EN_HWBU_FSM - en_hwbu_fsm
#define SGMII_PHY_HWBU_CTRL_EN_HWBU_FSM_POS 0
//! Field EN_HWBU_FSM - en_hwbu_fsm
#define SGMII_PHY_HWBU_CTRL_EN_HWBU_FSM_MASK 0x1u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_HWBU_CTRL_EN_HWBU_FSM_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_HWBU_CTRL_EN_HWBU_FSM_ENABLE 0x1

//! Field EN_PD_FSM - en_pd_fsm
#define SGMII_PHY_HWBU_CTRL_EN_PD_FSM_POS 1
//! Field EN_PD_FSM - en_pd_fsm
#define SGMII_PHY_HWBU_CTRL_EN_PD_FSM_MASK 0x2u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_HWBU_CTRL_EN_PD_FSM_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_HWBU_CTRL_EN_PD_FSM_ENABLE 0x1

//! Field EN_LP_FSM - en_lp_fsm
#define SGMII_PHY_HWBU_CTRL_EN_LP_FSM_POS 2
//! Field EN_LP_FSM - en_lp_fsm
#define SGMII_PHY_HWBU_CTRL_EN_LP_FSM_MASK 0x4u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_HWBU_CTRL_EN_LP_FSM_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_HWBU_CTRL_EN_LP_FSM_ENABLE 0x1

//! Field OVEERIDE_HWBU_FSM - en_hwbu_fsm
#define SGMII_PHY_HWBU_CTRL_OVEERIDE_HWBU_FSM_POS 3
//! Field OVEERIDE_HWBU_FSM - en_hwbu_fsm
#define SGMII_PHY_HWBU_CTRL_OVEERIDE_HWBU_FSM_MASK 0x8u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_HWBU_CTRL_OVEERIDE_HWBU_FSM_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_HWBU_CTRL_OVEERIDE_HWBU_FSM_ENABLE 0x1

//! Field OVEERIDE_HW_FSM_EN - _override_hw_fsm_en
#define SGMII_PHY_HWBU_CTRL_OVEERIDE_HW_FSM_EN_POS 4
//! Field OVEERIDE_HW_FSM_EN - _override_hw_fsm_en
#define SGMII_PHY_HWBU_CTRL_OVEERIDE_HW_FSM_EN_MASK 0x10u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_HWBU_CTRL_OVEERIDE_HW_FSM_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_HWBU_CTRL_OVEERIDE_HW_FSM_EN_ENABLE 0x1

//! Field FSM_DONE_CK_GATING_OVERIDE - fsm_done_ck_gating_overide
#define SGMII_PHY_HWBU_CTRL_FSM_DONE_CK_GATING_OVERIDE_POS 5
//! Field FSM_DONE_CK_GATING_OVERIDE - fsm_done_ck_gating_overide
#define SGMII_PHY_HWBU_CTRL_FSM_DONE_CK_GATING_OVERIDE_MASK 0x20u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_PHY_HWBU_CTRL_FSM_DONE_CK_GATING_OVERIDE_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_PHY_HWBU_CTRL_FSM_DONE_CK_GATING_OVERIDE_ENABLE 0x1

//! Field PLL_CFG_SEL - enable custom programming mode of SGMII PHY for PLL bring up
#define SGMII_PHY_HWBU_CTRL_PLL_CFG_SEL_POS 6
//! Field PLL_CFG_SEL - enable custom programming mode of SGMII PHY for PLL bring up
#define SGMII_PHY_HWBU_CTRL_PLL_CFG_SEL_MASK 0x40u
//! Constant NORMAL - config by HWBU based on TR_DR and FREQ_SEL
#define CONST_SGMII_PHY_HWBU_CTRL_PLL_CFG_SEL_NORMAL 0x0
//! Constant CUSTOM - config values based on CUSTOM registers
#define CONST_SGMII_PHY_HWBU_CTRL_PLL_CFG_SEL_CUSTOM 0x1

//! Field RX_CLK_SEL - GMII Rx clock speed
#define SGMII_PHY_HWBU_CTRL_RX_CLK_SEL_POS 7
//! Field RX_CLK_SEL - GMII Rx clock speed
#define SGMII_PHY_HWBU_CTRL_RX_CLK_SEL_MASK 0x180u
//! Constant GMII125 - GMII clock is 125 MHz
#define CONST_SGMII_PHY_HWBU_CTRL_RX_CLK_SEL_GMII125 0x0
//! Constant GMII250 - GMII clock is 250 MHz
#define CONST_SGMII_PHY_HWBU_CTRL_RX_CLK_SEL_GMII250 0x1
//! Constant GMII3125 - GMII clock is 312.5 MHz
#define CONST_SGMII_PHY_HWBU_CTRL_RX_CLK_SEL_GMII3125 0x2
//! Constant GMII375 - GMII clock is 375 MHz
#define CONST_SGMII_PHY_HWBU_CTRL_RX_CLK_SEL_GMII375 0x3

//! @}

//! \defgroup SGMII_PHY_STATUS Register SGMII_PHY_STATUS - SGMII PHY STATUS
//! @{

//! Register Offset (relative)
#define SGMII_PHY_STATUS 0x28
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_STATUS 0x00A34028u

//! Register Reset Value
#define SGMII_PHY_STATUS_RST 0x00002000u

//! Field MPLL_STATE - mpll_state
#define SGMII_PHY_STATUS_MPLL_STATE_POS 0
//! Field MPLL_STATE - mpll_state
#define SGMII_PHY_STATUS_MPLL_STATE_MASK 0x1u

//! Field RX0_LOS - rx0_los
#define SGMII_PHY_STATUS_RX0_LOS_POS 1
//! Field RX0_LOS - rx0_los
#define SGMII_PHY_STATUS_RX0_LOS_MASK 0x2u

//! Field RX0_PLL_STATE - rx0_pll_state
#define SGMII_PHY_STATUS_RX0_PLL_STATE_POS 2
//! Field RX0_PLL_STATE - rx0_pll_state
#define SGMII_PHY_STATUS_RX0_PLL_STATE_MASK 0x4u

//! Field TX0_CM_STATE - tx0_cm_state
#define SGMII_PHY_STATUS_TX0_CM_STATE_POS 3
//! Field TX0_CM_STATE - tx0_cm_state
#define SGMII_PHY_STATUS_TX0_CM_STATE_MASK 0x8u

//! Field TX0_DETECT_RX_ACK - tx0_detect_rx_ack
#define SGMII_PHY_STATUS_TX0_DETECT_RX_ACK_POS 4
//! Field TX0_DETECT_RX_ACK - tx0_detect_rx_ack
#define SGMII_PHY_STATUS_TX0_DETECT_RX_ACK_MASK 0x10u

//! Field TX0_DETECT_RX_RESULT - tx0_detect_rx_result
#define SGMII_PHY_STATUS_TX0_DETECT_RX_RESULT_POS 5
//! Field TX0_DETECT_RX_RESULT - tx0_detect_rx_result
#define SGMII_PHY_STATUS_TX0_DETECT_RX_RESULT_MASK 0x20u

//! Field TX0_STATE - tx0_state
#define SGMII_PHY_STATUS_TX0_STATE_POS 6
//! Field TX0_STATE - tx0_state
#define SGMII_PHY_STATUS_TX0_STATE_MASK 0x40u

//! Field HWBU_FSM_STATE - hwbu_fsm_state
#define SGMII_PHY_STATUS_HWBU_FSM_STATE_POS 7
//! Field HWBU_FSM_STATE - hwbu_fsm_state
#define SGMII_PHY_STATUS_HWBU_FSM_STATE_MASK 0xF80u

//! Field FSM_DONE - hwbu_fsm_done
#define SGMII_PHY_STATUS_FSM_DONE_POS 12
//! Field FSM_DONE - hwbu_fsm_done
#define SGMII_PHY_STATUS_FSM_DONE_MASK 0x1000u

//! Field MFSM_DONE - imask_fsm_done
#define SGMII_PHY_STATUS_MFSM_DONE_POS 13
//! Field MFSM_DONE - imask_fsm_done
#define SGMII_PHY_STATUS_MFSM_DONE_MASK 0x2000u
//! Constant UMASK - Unmask FSM_DONE Interrupt
#define CONST_SGMII_PHY_STATUS_MFSM_DONE_UMASK 0x0
//! Constant MASK - Mask FSM_DONE Interrupt
#define CONST_SGMII_PHY_STATUS_MFSM_DONE_MASK 0x1

//! Field RX0_VALID - rx0_valid
#define SGMII_PHY_STATUS_RX0_VALID_POS 14
//! Field RX0_VALID - rx0_valid
#define SGMII_PHY_STATUS_RX0_VALID_MASK 0x4000u

//! @}

//! \defgroup SGMII_PHY_CUSTOM Register SGMII_PHY_CUSTOM - Custom configuration of CEI PHY SERDES
//! @{

//! Register Offset (relative)
#define SGMII_PHY_CUSTOM 0x2C
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_CUSTOM 0x00A3402Cu

//! Register Reset Value
#define SGMII_PHY_CUSTOM_RST 0x00000000u

//! Field REF_USE_PAD_1
#define SGMII_PHY_CUSTOM_REF_USE_PAD_1_POS 0
//! Field REF_USE_PAD_1
#define SGMII_PHY_CUSTOM_REF_USE_PAD_1_MASK 0x1u

//! Field REF_CLKDIV2_1
#define SGMII_PHY_CUSTOM_REF_CLKDIV2_1_POS 1
//! Field REF_CLKDIV2_1
#define SGMII_PHY_CUSTOM_REF_CLKDIV2_1_MASK 0x2u

//! Field TX_RATE
#define SGMII_PHY_CUSTOM_TX_RATE_POS 2
//! Field TX_RATE
#define SGMII_PHY_CUSTOM_TX_RATE_MASK 0xCu

//! Field RX_RATE
#define SGMII_PHY_CUSTOM_RX_RATE_POS 4
//! Field RX_RATE
#define SGMII_PHY_CUSTOM_RX_RATE_MASK 0x30u

//! @}

//! \defgroup SGMII_PHY_CUSTOM2 Register SGMII_PHY_CUSTOM2 - Custom configuration 2 of CEI PHY SERDES
//! @{

//! Register Offset (relative)
#define SGMII_PHY_CUSTOM2 0x30
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_CUSTOM2 0x00A34030u

//! Register Reset Value
#define SGMII_PHY_CUSTOM2_RST 0x0000004Bu

//! Field MPLL_MULTIPLIER_1 - multiplier setting for PLL
#define SGMII_PHY_CUSTOM2_MPLL_MULTIPLIER_1_POS 0
//! Field MPLL_MULTIPLIER_1 - multiplier setting for PLL
#define SGMII_PHY_CUSTOM2_MPLL_MULTIPLIER_1_MASK 0x7Fu

//! Field SSC_REF_CLKSEL_1
#define SGMII_PHY_CUSTOM2_SSC_REF_CLKSEL_1_POS 7
//! Field SSC_REF_CLKSEL_1
#define SGMII_PHY_CUSTOM2_SSC_REF_CLKSEL_1_MASK 0xFF80u

//! @}

//! \defgroup SGMII_PHY_D Register SGMII_PHY_D - SGMII_PHY_D
//! @{

//! Register Offset (relative)
#define SGMII_PHY_D 0x400
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_D 0x00A34400u

//! Register Reset Value
#define SGMII_PHY_D_RST 0x00000000u

//! Field DATA - data
#define SGMII_PHY_D_DATA_POS 0
//! Field DATA - data
#define SGMII_PHY_D_DATA_MASK 0xFFFFu

//! @}

//! \defgroup SGMII_PHY_A Register SGMII_PHY_A - SGMII_PHY_A
//! @{

//! Register Offset (relative)
#define SGMII_PHY_A 0x404
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_A 0x00A34404u

//! Register Reset Value
#define SGMII_PHY_A_RST 0x00000000u

//! Field ADDRESS - address
#define SGMII_PHY_A_ADDRESS_POS 0
//! Field ADDRESS - address
#define SGMII_PHY_A_ADDRESS_MASK 0xFFFFu

//! @}

//! \defgroup SGMII_PHY_C Register SGMII_PHY_C - SGMII_PHY_C
//! @{

//! Register Offset (relative)
#define SGMII_PHY_C 0x408
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_C 0x00A34408u

//! Register Reset Value
#define SGMII_PHY_C_RST 0x00001000u

//! Field STATUS - status
#define SGMII_PHY_C_STATUS_POS 0
//! Field STATUS - status
#define SGMII_PHY_C_STATUS_MASK 0x1u

//! Field ISSUE_READ - issue_read
#define SGMII_PHY_C_ISSUE_READ_POS 4
//! Field ISSUE_READ - issue_read
#define SGMII_PHY_C_ISSUE_READ_MASK 0x10u

//! Field ISSUE_WRITE - issue_write
#define SGMII_PHY_C_ISSUE_WRITE_POS 8
//! Field ISSUE_WRITE - issue_write
#define SGMII_PHY_C_ISSUE_WRITE_MASK 0x100u

//! Field RESET_N1 - resetn
#define SGMII_PHY_C_RESET_N1_POS 12
//! Field RESET_N1 - resetn
#define SGMII_PHY_C_RESET_N1_MASK 0x1000u

//! @}

//! \defgroup SGMII_PHY_WATCHDOG_CTRL Register SGMII_PHY_WATCHDOG_CTRL - SGMII PHY WATCHDOG CONTROL
//! @{

//! Register Offset (relative)
#define SGMII_PHY_WATCHDOG_CTRL 0x444
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_WATCHDOG_CTRL 0x00A34444u

//! Register Reset Value
#define SGMII_PHY_WATCHDOG_CTRL_RST 0x00000000u

//! Field WATCHDOG_ERR - Watchdog error value
#define SGMII_PHY_WATCHDOG_CTRL_WATCHDOG_ERR_POS 0
//! Field WATCHDOG_ERR - Watchdog error value
#define SGMII_PHY_WATCHDOG_CTRL_WATCHDOG_ERR_MASK 0x1u

//! Field WATCHDOG_EN - watchdog enable
#define SGMII_PHY_WATCHDOG_CTRL_WATCHDOG_EN_POS 1
//! Field WATCHDOG_EN - watchdog enable
#define SGMII_PHY_WATCHDOG_CTRL_WATCHDOG_EN_MASK 0x2u

//! @}

//! \defgroup SGMII_PHY_WATCHDOG_TIMER Register SGMII_PHY_WATCHDOG_TIMER - SGMII PHY WATCHDOG TIMER
//! @{

//! Register Offset (relative)
#define SGMII_PHY_WATCHDOG_TIMER 0x448
//! Register Offset (absolute) for 1st Instance SGMII_PHY_REGISTERS
#define SGMII_PHY_REGISTERS_SGMII_PHY_WATCHDOG_TIMER 0x00A34448u

//! Register Reset Value
#define SGMII_PHY_WATCHDOG_TIMER_RST 0x0000FFFFu

//! Field WATCHDOG_VAL - watchdog value
#define SGMII_PHY_WATCHDOG_TIMER_WATCHDOG_VAL_POS 0
//! Field WATCHDOG_VAL - watchdog value
#define SGMII_PHY_WATCHDOG_TIMER_WATCHDOG_VAL_MASK 0xFFFFu

//! @}

//! @}

#endif
