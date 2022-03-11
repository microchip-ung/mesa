//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_reddydev.priv.p34x_chip.chip_work/ipg_lsd/lsd_sys/source_32b/xml/reg_files/chip_usxgmii/XPCS_AN_MMD_def.xml
// Register File Name  : XPCS_AN_MMD
// Register File Title : XPCS AN MMD
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _XPCS_AN_MMD_H
#define _XPCS_AN_MMD_H

//! \defgroup XPCS_AN_MMD Register File XPCS_AN_MMD - XPCS AN MMD
//! @{

//! Base Address of XPCS_AN_MMD
#define XPCS_AN_MMD_MODULE_BASE 0x001C0000u

//! \defgroup XPCS_SR_AN_CTRL Register XPCS_SR_AN_CTRL - XPCS SR AN CTRL
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_CTRL 0x0
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_CTRL 0x001C0000u

//! Register Reset Value
#define XPCS_SR_AN_CTRL_RST 0x00003000u

//! Field RESERVED_8_0 - Reserved_8_0
#define XPCS_SR_AN_CTRL_RESERVED_8_0_POS 0
//! Field RESERVED_8_0 - Reserved_8_0
#define XPCS_SR_AN_CTRL_RESERVED_8_0_MASK 0x1FFu

//! Field RSTRT_AN - RSTRT_AN
#define XPCS_SR_AN_CTRL_RSTRT_AN_POS 9
//! Field RSTRT_AN - RSTRT_AN
#define XPCS_SR_AN_CTRL_RSTRT_AN_MASK 0x200u

//! Field RESERVED_10 - Reserved_10
#define XPCS_SR_AN_CTRL_RESERVED_10_POS 10
//! Field RESERVED_10 - Reserved_10
#define XPCS_SR_AN_CTRL_RESERVED_10_MASK 0x400u

//! Field LPM - LPM
#define XPCS_SR_AN_CTRL_LPM_POS 11
//! Field LPM - LPM
#define XPCS_SR_AN_CTRL_LPM_MASK 0x800u

//! Field AN_EN - AN_EN
#define XPCS_SR_AN_CTRL_AN_EN_POS 12
//! Field AN_EN - AN_EN
#define XPCS_SR_AN_CTRL_AN_EN_MASK 0x1000u

//! Field EXT_NP_CTL - EXT_NP_CTL
#define XPCS_SR_AN_CTRL_EXT_NP_CTL_POS 13
//! Field EXT_NP_CTL - EXT_NP_CTL
#define XPCS_SR_AN_CTRL_EXT_NP_CTL_MASK 0x2000u

//! Field RESERVED_14 - Reserved_14
#define XPCS_SR_AN_CTRL_RESERVED_14_POS 14
//! Field RESERVED_14 - Reserved_14
#define XPCS_SR_AN_CTRL_RESERVED_14_MASK 0x4000u

//! Field AN_RST - AN_RST
#define XPCS_SR_AN_CTRL_AN_RST_POS 15
//! Field AN_RST - AN_RST
#define XPCS_SR_AN_CTRL_AN_RST_MASK 0x8000u

//! @}

//! \defgroup XPCS_SR_AN_STS Register XPCS_SR_AN_STS - XPCS SR AN STS
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_STS 0x4
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_STS 0x001C0004u

//! Register Reset Value
#define XPCS_SR_AN_STS_RST 0x00000008u

//! Field LP_AN_ABL - LP_AN_ABL
#define XPCS_SR_AN_STS_LP_AN_ABL_POS 0
//! Field LP_AN_ABL - LP_AN_ABL
#define XPCS_SR_AN_STS_LP_AN_ABL_MASK 0x1u

//! Field RESERVED_1 - Reserved_1
#define XPCS_SR_AN_STS_RESERVED_1_POS 1
//! Field RESERVED_1 - Reserved_1
#define XPCS_SR_AN_STS_RESERVED_1_MASK 0x2u

//! Field AN_LS - AN_LS
#define XPCS_SR_AN_STS_AN_LS_POS 2
//! Field AN_LS - AN_LS
#define XPCS_SR_AN_STS_AN_LS_MASK 0x4u

//! Field AN_ABL - AN_ABL
#define XPCS_SR_AN_STS_AN_ABL_POS 3
//! Field AN_ABL - AN_ABL
#define XPCS_SR_AN_STS_AN_ABL_MASK 0x8u

//! Field AN_RF - AN_RF
#define XPCS_SR_AN_STS_AN_RF_POS 4
//! Field AN_RF - AN_RF
#define XPCS_SR_AN_STS_AN_RF_MASK 0x10u

//! Field ANC - ANC
#define XPCS_SR_AN_STS_ANC_POS 5
//! Field ANC - ANC
#define XPCS_SR_AN_STS_ANC_MASK 0x20u

//! Field PR - PR
#define XPCS_SR_AN_STS_PR_POS 6
//! Field PR - PR
#define XPCS_SR_AN_STS_PR_MASK 0x40u

//! Field EXT_NP_STS - EXT_NP_STS
#define XPCS_SR_AN_STS_EXT_NP_STS_POS 7
//! Field EXT_NP_STS - EXT_NP_STS
#define XPCS_SR_AN_STS_EXT_NP_STS_MASK 0x80u

//! Field RESERVED_8 - Reserved_8
#define XPCS_SR_AN_STS_RESERVED_8_POS 8
//! Field RESERVED_8 - Reserved_8
#define XPCS_SR_AN_STS_RESERVED_8_MASK 0x100u

//! Field PDF - PDF
#define XPCS_SR_AN_STS_PDF_POS 9
//! Field PDF - PDF
#define XPCS_SR_AN_STS_PDF_MASK 0x200u

//! Field RESERVED_15_10 - Reserved_15_10
#define XPCS_SR_AN_STS_RESERVED_15_10_POS 10
//! Field RESERVED_15_10 - Reserved_15_10
#define XPCS_SR_AN_STS_RESERVED_15_10_MASK 0xFC00u

//! @}

//! \defgroup XPCS_SR_AN_DEV_ID1 Register XPCS_SR_AN_DEV_ID1 - XPCS SR AN DEV ID1
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_DEV_ID1 0x8
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_DEV_ID1 0x001C0008u

//! Register Reset Value
#define XPCS_SR_AN_DEV_ID1_RST 0x00000000u

//! Field AN_DEV_OUI_3_18 - AN_DEV_OUI_3_18
#define XPCS_SR_AN_DEV_ID1_AN_DEV_OUI_3_18_POS 0
//! Field AN_DEV_OUI_3_18 - AN_DEV_OUI_3_18
#define XPCS_SR_AN_DEV_ID1_AN_DEV_OUI_3_18_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_AN_DEV_ID2 Register XPCS_SR_AN_DEV_ID2 - XPCS SR AN DEV ID2
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_DEV_ID2 0xC
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_DEV_ID2 0x001C000Cu

//! Register Reset Value
#define XPCS_SR_AN_DEV_ID2_RST 0x00000000u

//! Field AN_DEV_RN_3_0 - AN_DEV_RN_3_0
#define XPCS_SR_AN_DEV_ID2_AN_DEV_RN_3_0_POS 0
//! Field AN_DEV_RN_3_0 - AN_DEV_RN_3_0
#define XPCS_SR_AN_DEV_ID2_AN_DEV_RN_3_0_MASK 0xFu

//! Field AN_DEV_MMN_5_0 - AN_DEV_MMN_5_0
#define XPCS_SR_AN_DEV_ID2_AN_DEV_MMN_5_0_POS 4
//! Field AN_DEV_MMN_5_0 - AN_DEV_MMN_5_0
#define XPCS_SR_AN_DEV_ID2_AN_DEV_MMN_5_0_MASK 0x3F0u

//! Field AN_DEV_OUI_19_24 - AN_DEV_OUI_19_24
#define XPCS_SR_AN_DEV_ID2_AN_DEV_OUI_19_24_POS 10
//! Field AN_DEV_OUI_19_24 - AN_DEV_OUI_19_24
#define XPCS_SR_AN_DEV_ID2_AN_DEV_OUI_19_24_MASK 0xFC00u

//! @}

//! \defgroup XPCS_SR_AN_DEV_PKG1 Register XPCS_SR_AN_DEV_PKG1 - XPCS SR AN DEV PKG1
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_DEV_PKG1 0x14
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_DEV_PKG1 0x001C0014u

//! Register Reset Value
#define XPCS_SR_AN_DEV_PKG1_RST 0x0000008Au

//! Field CLS22 - CLS22
#define XPCS_SR_AN_DEV_PKG1_CLS22_POS 0
//! Field CLS22 - CLS22
#define XPCS_SR_AN_DEV_PKG1_CLS22_MASK 0x1u

//! Field PMA_PMD - PMA_PMD
#define XPCS_SR_AN_DEV_PKG1_PMA_PMD_POS 1
//! Field PMA_PMD - PMA_PMD
#define XPCS_SR_AN_DEV_PKG1_PMA_PMD_MASK 0x2u

//! Field WIS - WIS
#define XPCS_SR_AN_DEV_PKG1_WIS_POS 2
//! Field WIS - WIS
#define XPCS_SR_AN_DEV_PKG1_WIS_MASK 0x4u

//! Field PCS - PCS
#define XPCS_SR_AN_DEV_PKG1_PCS_POS 3
//! Field PCS - PCS
#define XPCS_SR_AN_DEV_PKG1_PCS_MASK 0x8u

//! Field PHYXS - PHYXS
#define XPCS_SR_AN_DEV_PKG1_PHYXS_POS 4
//! Field PHYXS - PHYXS
#define XPCS_SR_AN_DEV_PKG1_PHYXS_MASK 0x10u

//! Field DTEXS - DTEXS
#define XPCS_SR_AN_DEV_PKG1_DTEXS_POS 5
//! Field DTEXS - DTEXS
#define XPCS_SR_AN_DEV_PKG1_DTEXS_MASK 0x20u

//! Field TC - TC
#define XPCS_SR_AN_DEV_PKG1_TC_POS 6
//! Field TC - TC
#define XPCS_SR_AN_DEV_PKG1_TC_MASK 0x40u

//! Field AN - AN
#define XPCS_SR_AN_DEV_PKG1_AN_POS 7
//! Field AN - AN
#define XPCS_SR_AN_DEV_PKG1_AN_MASK 0x80u

//! Field RESERVED_15_8 - Reserved_15_8
#define XPCS_SR_AN_DEV_PKG1_RESERVED_15_8_POS 8
//! Field RESERVED_15_8 - Reserved_15_8
#define XPCS_SR_AN_DEV_PKG1_RESERVED_15_8_MASK 0xFF00u

//! @}

//! \defgroup XPCS_SR_AN_DEV_PKG2 Register XPCS_SR_AN_DEV_PKG2 - XPCS SR AN DEV PKG2
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_DEV_PKG2 0x18
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_DEV_PKG2 0x001C0018u

//! Register Reset Value
#define XPCS_SR_AN_DEV_PKG2_RST 0x0000C000u

//! Field RESERVED_13_0 - Reserved_13_0
#define XPCS_SR_AN_DEV_PKG2_RESERVED_13_0_POS 0
//! Field RESERVED_13_0 - Reserved_13_0
#define XPCS_SR_AN_DEV_PKG2_RESERVED_13_0_MASK 0x3FFFu

//! Field VSD1 - VSD1
#define XPCS_SR_AN_DEV_PKG2_VSD1_POS 14
//! Field VSD1 - VSD1
#define XPCS_SR_AN_DEV_PKG2_VSD1_MASK 0x4000u

//! Field VSD2 - VSD2
#define XPCS_SR_AN_DEV_PKG2_VSD2_POS 15
//! Field VSD2 - VSD2
#define XPCS_SR_AN_DEV_PKG2_VSD2_MASK 0x8000u

//! @}

//! \defgroup XPCS_SR_AN_PKG1 Register XPCS_SR_AN_PKG1 - XPCS SR AN PKG1
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_PKG1 0x38
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_PKG1 0x001C0038u

//! Register Reset Value
#define XPCS_SR_AN_PKG1_RST 0x00000000u

//! Field AN_PKG_OUI_3_18 - AN_PKG_OUI_3_18
#define XPCS_SR_AN_PKG1_AN_PKG_OUI_3_18_POS 0
//! Field AN_PKG_OUI_3_18 - AN_PKG_OUI_3_18
#define XPCS_SR_AN_PKG1_AN_PKG_OUI_3_18_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_AN_PKG2 Register XPCS_SR_AN_PKG2 - XPCS SR AN PKG2
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_PKG2 0x3C
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_PKG2 0x001C003Cu

//! Register Reset Value
#define XPCS_SR_AN_PKG2_RST 0x00000000u

//! Field AN_PKG_RN_3_0 - AN_PKG_RN_3_0
#define XPCS_SR_AN_PKG2_AN_PKG_RN_3_0_POS 0
//! Field AN_PKG_RN_3_0 - AN_PKG_RN_3_0
#define XPCS_SR_AN_PKG2_AN_PKG_RN_3_0_MASK 0xFu

//! Field AN_PKG_MMN_5_0 - AN_PKG_MMN_5_0
#define XPCS_SR_AN_PKG2_AN_PKG_MMN_5_0_POS 4
//! Field AN_PKG_MMN_5_0 - AN_PKG_MMN_5_0
#define XPCS_SR_AN_PKG2_AN_PKG_MMN_5_0_MASK 0x3F0u

//! Field AN_PKG_OUI_19_24 - AN_PKG_OUI_19_24
#define XPCS_SR_AN_PKG2_AN_PKG_OUI_19_24_POS 10
//! Field AN_PKG_OUI_19_24 - AN_PKG_OUI_19_24
#define XPCS_SR_AN_PKG2_AN_PKG_OUI_19_24_MASK 0xFC00u

//! @}

//! \defgroup XPCS_SR_AN_ADV1 Register XPCS_SR_AN_ADV1 - XPCS SR AN ADV1
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_ADV1 0x40
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_ADV1 0x001C0040u

//! Register Reset Value
#define XPCS_SR_AN_ADV1_RST 0x00000001u

//! Field AN_ADV_SF - AN_ADV_SF
#define XPCS_SR_AN_ADV1_AN_ADV_SF_POS 0
//! Field AN_ADV_SF - AN_ADV_SF
#define XPCS_SR_AN_ADV1_AN_ADV_SF_MASK 0x1Fu

//! Field DATA - DATA
#define XPCS_SR_AN_ADV1_DATA_POS 5
//! Field DATA - DATA
#define XPCS_SR_AN_ADV1_DATA_MASK 0xFE0u

//! Field RESERVED_12 - Reserved_12
#define XPCS_SR_AN_ADV1_RESERVED_12_POS 12
//! Field RESERVED_12 - Reserved_12
#define XPCS_SR_AN_ADV1_RESERVED_12_MASK 0x1000u

//! Field AN_ADV_RF_13 - AN_ADV_RF_13
#define XPCS_SR_AN_ADV1_AN_ADV_RF_13_POS 13
//! Field AN_ADV_RF_13 - AN_ADV_RF_13
#define XPCS_SR_AN_ADV1_AN_ADV_RF_13_MASK 0x2000u

//! Field AN_ADV_ACK - AN_ADV_ACK
#define XPCS_SR_AN_ADV1_AN_ADV_ACK_POS 14
//! Field AN_ADV_ACK - AN_ADV_ACK
#define XPCS_SR_AN_ADV1_AN_ADV_ACK_MASK 0x4000u

//! Field AN_ADV_NP - AN_ADV_NP
#define XPCS_SR_AN_ADV1_AN_ADV_NP_POS 15
//! Field AN_ADV_NP - AN_ADV_NP
#define XPCS_SR_AN_ADV1_AN_ADV_NP_MASK 0x8000u

//! @}

//! \defgroup XPCS_SR_AN_ADV2 Register XPCS_SR_AN_ADV2 - XPCS SR AN ADV2
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_ADV2 0x44
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_ADV2 0x001C0044u

//! Register Reset Value
#define XPCS_SR_AN_ADV2_RST 0x000000A0u

//! Field DATA_31_16 - DATA_31_16
#define XPCS_SR_AN_ADV2_DATA_31_16_POS 0
//! Field DATA_31_16 - DATA_31_16
#define XPCS_SR_AN_ADV2_DATA_31_16_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_AN_ADV3 Register XPCS_SR_AN_ADV3 - XPCS SR AN ADV3
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_ADV3 0x48
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_ADV3 0x001C0048u

//! Register Reset Value
#define XPCS_SR_AN_ADV3_RST 0x00000002u

//! Field DATA_47_32 - DATA_47_32
#define XPCS_SR_AN_ADV3_DATA_47_32_POS 0
//! Field DATA_47_32 - DATA_47_32
#define XPCS_SR_AN_ADV3_DATA_47_32_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_AN_LP_ABL1 Register XPCS_SR_AN_LP_ABL1 - XPCS SR AN LP ABL1
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_LP_ABL1 0x4C
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_LP_ABL1 0x001C004Cu

//! Register Reset Value
#define XPCS_SR_AN_LP_ABL1_RST 0x00000000u

//! Field AN_LP_ADV_SF - AN_LP_ADV_SF
#define XPCS_SR_AN_LP_ABL1_AN_LP_ADV_SF_POS 0
//! Field AN_LP_ADV_SF - AN_LP_ADV_SF
#define XPCS_SR_AN_LP_ABL1_AN_LP_ADV_SF_MASK 0x1Fu

//! Field DATA - DATA
#define XPCS_SR_AN_LP_ABL1_DATA_POS 5
//! Field DATA - DATA
#define XPCS_SR_AN_LP_ABL1_DATA_MASK 0xFE0u

//! Field RESERVED_12 - Reserved_12
#define XPCS_SR_AN_LP_ABL1_RESERVED_12_POS 12
//! Field RESERVED_12 - Reserved_12
#define XPCS_SR_AN_LP_ABL1_RESERVED_12_MASK 0x1000u

//! Field AN_LP_ADV_RF - AN_LP_ADV_RF
#define XPCS_SR_AN_LP_ABL1_AN_LP_ADV_RF_POS 13
//! Field AN_LP_ADV_RF - AN_LP_ADV_RF
#define XPCS_SR_AN_LP_ABL1_AN_LP_ADV_RF_MASK 0x2000u

//! Field AN_LP_ADV_ACK - AN_LP_ADV_ACK
#define XPCS_SR_AN_LP_ABL1_AN_LP_ADV_ACK_POS 14
//! Field AN_LP_ADV_ACK - AN_LP_ADV_ACK
#define XPCS_SR_AN_LP_ABL1_AN_LP_ADV_ACK_MASK 0x4000u

//! Field AN_LP_ADV_NP - AN_LP_ADV_NP
#define XPCS_SR_AN_LP_ABL1_AN_LP_ADV_NP_POS 15
//! Field AN_LP_ADV_NP - AN_LP_ADV_NP
#define XPCS_SR_AN_LP_ABL1_AN_LP_ADV_NP_MASK 0x8000u

//! @}

//! \defgroup XPCS_SR_AN_LP_ABL2 Register XPCS_SR_AN_LP_ABL2 - XPCS SR AN LP ABL2
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_LP_ABL2 0x50
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_LP_ABL2 0x001C0050u

//! Register Reset Value
#define XPCS_SR_AN_LP_ABL2_RST 0x00000000u

//! Field DATA_31_16 - DATA_31_16
#define XPCS_SR_AN_LP_ABL2_DATA_31_16_POS 0
//! Field DATA_31_16 - DATA_31_16
#define XPCS_SR_AN_LP_ABL2_DATA_31_16_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_AN_LP_ABL3 Register XPCS_SR_AN_LP_ABL3 - XPCS SR AN LP ABL3
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_LP_ABL3 0x54
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_LP_ABL3 0x001C0054u

//! Register Reset Value
#define XPCS_SR_AN_LP_ABL3_RST 0x00000000u

//! Field DATA_47_32 - DATA_47_32
#define XPCS_SR_AN_LP_ABL3_DATA_47_32_POS 0
//! Field DATA_47_32 - DATA_47_32
#define XPCS_SR_AN_LP_ABL3_DATA_47_32_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_AN_XNP_TX1 Register XPCS_SR_AN_XNP_TX1 - XPCS SR AN XNP TX1
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_XNP_TX1 0x58
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_XNP_TX1 0x001C0058u

//! Register Reset Value
#define XPCS_SR_AN_XNP_TX1_RST 0x00000000u

//! Field MCF - MCF
#define XPCS_SR_AN_XNP_TX1_MCF_POS 0
//! Field MCF - MCF
#define XPCS_SR_AN_XNP_TX1_MCF_MASK 0x7FFu

//! Field TB - TB
#define XPCS_SR_AN_XNP_TX1_TB_POS 11
//! Field TB - TB
#define XPCS_SR_AN_XNP_TX1_TB_MASK 0x800u

//! Field AN_XNP_ACK2 - AN_XNP_ACK2
#define XPCS_SR_AN_XNP_TX1_AN_XNP_ACK2_POS 12
//! Field AN_XNP_ACK2 - AN_XNP_ACK2
#define XPCS_SR_AN_XNP_TX1_AN_XNP_ACK2_MASK 0x1000u

//! Field AN_XNP_MP - AN_XNP_MP
#define XPCS_SR_AN_XNP_TX1_AN_XNP_MP_POS 13
//! Field AN_XNP_MP - AN_XNP_MP
#define XPCS_SR_AN_XNP_TX1_AN_XNP_MP_MASK 0x2000u

//! Field RESERVED_14 - Reserved_14
#define XPCS_SR_AN_XNP_TX1_RESERVED_14_POS 14
//! Field RESERVED_14 - Reserved_14
#define XPCS_SR_AN_XNP_TX1_RESERVED_14_MASK 0x4000u

//! Field AN_XNP_NP - AN_XNP_NP
#define XPCS_SR_AN_XNP_TX1_AN_XNP_NP_POS 15
//! Field AN_XNP_NP - AN_XNP_NP
#define XPCS_SR_AN_XNP_TX1_AN_XNP_NP_MASK 0x8000u

//! @}

//! \defgroup XPCS_SR_AN_XNP_TX2 Register XPCS_SR_AN_XNP_TX2 - XPCS SR AN XNP TX2
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_XNP_TX2 0x5C
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_XNP_TX2 0x001C005Cu

//! Register Reset Value
#define XPCS_SR_AN_XNP_TX2_RST 0x00000000u

//! Field UMCF1 - UMCF1
#define XPCS_SR_AN_XNP_TX2_UMCF1_POS 0
//! Field UMCF1 - UMCF1
#define XPCS_SR_AN_XNP_TX2_UMCF1_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_AN_XNP_TX3 Register XPCS_SR_AN_XNP_TX3 - XPCS SR AN XNP TX3
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_XNP_TX3 0x60
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_XNP_TX3 0x001C0060u

//! Register Reset Value
#define XPCS_SR_AN_XNP_TX3_RST 0x00000000u

//! Field UMCF2 - UMCF2
#define XPCS_SR_AN_XNP_TX3_UMCF2_POS 0
//! Field UMCF2 - UMCF2
#define XPCS_SR_AN_XNP_TX3_UMCF2_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_AN_LP_XNP_ABL1 Register XPCS_SR_AN_LP_XNP_ABL1 - XPCS SR AN LP XNP ABL1
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_LP_XNP_ABL1 0x64
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_LP_XNP_ABL1 0x001C0064u

//! Register Reset Value
#define XPCS_SR_AN_LP_XNP_ABL1_RST 0x00000000u

//! Field MCF - MCF
#define XPCS_SR_AN_LP_XNP_ABL1_MCF_POS 0
//! Field MCF - MCF
#define XPCS_SR_AN_LP_XNP_ABL1_MCF_MASK 0x7FFu

//! Field TB - TB
#define XPCS_SR_AN_LP_XNP_ABL1_TB_POS 11
//! Field TB - TB
#define XPCS_SR_AN_LP_XNP_ABL1_TB_MASK 0x800u

//! Field AN_LP_XNP_ACK2 - AN_LP_XNP_ACK2
#define XPCS_SR_AN_LP_XNP_ABL1_AN_LP_XNP_ACK2_POS 12
//! Field AN_LP_XNP_ACK2 - AN_LP_XNP_ACK2
#define XPCS_SR_AN_LP_XNP_ABL1_AN_LP_XNP_ACK2_MASK 0x1000u

//! Field AN_LP_XNP_MP - AN_LP_XNP_MP
#define XPCS_SR_AN_LP_XNP_ABL1_AN_LP_XNP_MP_POS 13
//! Field AN_LP_XNP_MP - AN_LP_XNP_MP
#define XPCS_SR_AN_LP_XNP_ABL1_AN_LP_XNP_MP_MASK 0x2000u

//! Field AN_LP_XNP_ACK - AN_LP_XNP_ACK
#define XPCS_SR_AN_LP_XNP_ABL1_AN_LP_XNP_ACK_POS 14
//! Field AN_LP_XNP_ACK - AN_LP_XNP_ACK
#define XPCS_SR_AN_LP_XNP_ABL1_AN_LP_XNP_ACK_MASK 0x4000u

//! Field AN_LP_XNP_NP - AN_LP_XNP_NP
#define XPCS_SR_AN_LP_XNP_ABL1_AN_LP_XNP_NP_POS 15
//! Field AN_LP_XNP_NP - AN_LP_XNP_NP
#define XPCS_SR_AN_LP_XNP_ABL1_AN_LP_XNP_NP_MASK 0x8000u

//! @}

//! \defgroup XPCS_SR_AN_LP_XNP_ABL2 Register XPCS_SR_AN_LP_XNP_ABL2 - XPCS SR AN LP XNP ABL2
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_LP_XNP_ABL2 0x68
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_LP_XNP_ABL2 0x001C0068u

//! Register Reset Value
#define XPCS_SR_AN_LP_XNP_ABL2_RST 0x00000000u

//! Field UCF1 - UCF1
#define XPCS_SR_AN_LP_XNP_ABL2_UCF1_POS 0
//! Field UCF1 - UCF1
#define XPCS_SR_AN_LP_XNP_ABL2_UCF1_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_AN_LP_XNP_ABL3 Register XPCS_SR_AN_LP_XNP_ABL3 - XPCS SR AN LP XNP ABL3
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_LP_XNP_ABL3 0x6C
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_LP_XNP_ABL3 0x001C006Cu

//! Register Reset Value
#define XPCS_SR_AN_LP_XNP_ABL3_RST 0x00000000u

//! Field UCF2 - UCF2
#define XPCS_SR_AN_LP_XNP_ABL3_UCF2_POS 0
//! Field UCF2 - UCF2
#define XPCS_SR_AN_LP_XNP_ABL3_UCF2_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_AN_COMP_STS Register XPCS_SR_AN_COMP_STS - XPCS SR AN COMP STS
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_COMP_STS 0xC0
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_COMP_STS 0x001C00C0u

//! Register Reset Value
#define XPCS_SR_AN_COMP_STS_RST 0x00000001u

//! Field BP_AN_ABL - BP_AN_ABL
#define XPCS_SR_AN_COMP_STS_BP_AN_ABL_POS 0
//! Field BP_AN_ABL - BP_AN_ABL
#define XPCS_SR_AN_COMP_STS_BP_AN_ABL_MASK 0x1u

//! Field AN_COMP_KX - AN_COMP_KX
#define XPCS_SR_AN_COMP_STS_AN_COMP_KX_POS 1
//! Field AN_COMP_KX - AN_COMP_KX
#define XPCS_SR_AN_COMP_STS_AN_COMP_KX_MASK 0x2u

//! Field AN_COMP_KX4 - AN_COMP_KX4
#define XPCS_SR_AN_COMP_STS_AN_COMP_KX4_POS 2
//! Field AN_COMP_KX4 - AN_COMP_KX4
#define XPCS_SR_AN_COMP_STS_AN_COMP_KX4_MASK 0x4u

//! Field AN_COMP_KR - AN_COMP_KR
#define XPCS_SR_AN_COMP_STS_AN_COMP_KR_POS 3
//! Field AN_COMP_KR - AN_COMP_KR
#define XPCS_SR_AN_COMP_STS_AN_COMP_KR_MASK 0x8u

//! Field AN_COMP_FEC - AN_COMP_FEC
#define XPCS_SR_AN_COMP_STS_AN_COMP_FEC_POS 4
//! Field AN_COMP_FEC - AN_COMP_FEC
#define XPCS_SR_AN_COMP_STS_AN_COMP_FEC_MASK 0x10u

//! Field RESERVED_13_5 - Reserved_13_5
#define XPCS_SR_AN_COMP_STS_RESERVED_13_5_POS 5
//! Field RESERVED_13_5 - Reserved_13_5
#define XPCS_SR_AN_COMP_STS_RESERVED_13_5_MASK 0x3FE0u

//! Field AN_COMP_2PT5G - AN_COMP_2PT5G
#define XPCS_SR_AN_COMP_STS_AN_COMP_2PT5G_POS 14
//! Field AN_COMP_2PT5G - AN_COMP_2PT5G
#define XPCS_SR_AN_COMP_STS_AN_COMP_2PT5G_MASK 0x4000u

//! Field AN_COMP_5G - AN_COMP_5G
#define XPCS_SR_AN_COMP_STS_AN_COMP_5G_POS 15
//! Field AN_COMP_5G - AN_COMP_5G
#define XPCS_SR_AN_COMP_STS_AN_COMP_5G_MASK 0x8000u

//! @}

//! \defgroup XPCS_SR_AN_EEE_ABL1 Register XPCS_SR_AN_EEE_ABL1 - XPCS SR AN EEE ABL1
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_EEE_ABL1 0xF0
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_EEE_ABL1 0x001C00F0u

//! Register Reset Value
#define XPCS_SR_AN_EEE_ABL1_RST 0x00000050u

//! Field RESERVED_0 - Reserved_0
#define XPCS_SR_AN_EEE_ABL1_RESERVED_0_POS 0
//! Field RESERVED_0 - Reserved_0
#define XPCS_SR_AN_EEE_ABL1_RESERVED_0_MASK 0x1u

//! Field EN_100TEE - EN_100TEE
#define XPCS_SR_AN_EEE_ABL1_EN_100TEE_POS 1
//! Field EN_100TEE - EN_100TEE
#define XPCS_SR_AN_EEE_ABL1_EN_100TEE_MASK 0x2u

//! Field EN_1GTEEE - EN_1GTEEE
#define XPCS_SR_AN_EEE_ABL1_EN_1GTEEE_POS 2
//! Field EN_1GTEEE - EN_1GTEEE
#define XPCS_SR_AN_EEE_ABL1_EN_1GTEEE_MASK 0x4u

//! Field TEEE - TEEE
#define XPCS_SR_AN_EEE_ABL1_TEEE_POS 3
//! Field TEEE - TEEE
#define XPCS_SR_AN_EEE_ABL1_TEEE_MASK 0x8u

//! Field KXEEE - KXEEE
#define XPCS_SR_AN_EEE_ABL1_KXEEE_POS 4
//! Field KXEEE - KXEEE
#define XPCS_SR_AN_EEE_ABL1_KXEEE_MASK 0x10u

//! Field KX4EEE - KX4EEE
#define XPCS_SR_AN_EEE_ABL1_KX4EEE_POS 5
//! Field KX4EEE - KX4EEE
#define XPCS_SR_AN_EEE_ABL1_KX4EEE_MASK 0x20u

//! Field KREEE - KREEE
#define XPCS_SR_AN_EEE_ABL1_KREEE_POS 6
//! Field KREEE - KREEE
#define XPCS_SR_AN_EEE_ABL1_KREEE_MASK 0x40u

//! Field RESERVED_15_7 - Reserved_15_7
#define XPCS_SR_AN_EEE_ABL1_RESERVED_15_7_POS 7
//! Field RESERVED_15_7 - Reserved_15_7
#define XPCS_SR_AN_EEE_ABL1_RESERVED_15_7_MASK 0xFF80u

//! @}

//! \defgroup XPCS_SR_AN_EEE_LP_ABL1 Register XPCS_SR_AN_EEE_LP_ABL1 - XPCS SR AN EEE LP ABL1
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_EEE_LP_ABL1 0xF4
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_EEE_LP_ABL1 0x001C00F4u

//! Register Reset Value
#define XPCS_SR_AN_EEE_LP_ABL1_RST 0x00000000u

//! Field RESERVED_0 - Reserved_0
#define XPCS_SR_AN_EEE_LP_ABL1_RESERVED_0_POS 0
//! Field RESERVED_0 - Reserved_0
#define XPCS_SR_AN_EEE_LP_ABL1_RESERVED_0_MASK 0x1u

//! Field LP_100TEE - LP_100TEE
#define XPCS_SR_AN_EEE_LP_ABL1_LP_100TEE_POS 1
//! Field LP_100TEE - LP_100TEE
#define XPCS_SR_AN_EEE_LP_ABL1_LP_100TEE_MASK 0x2u

//! Field LP_1GTEEE - LP_1GTEEE
#define XPCS_SR_AN_EEE_LP_ABL1_LP_1GTEEE_POS 2
//! Field LP_1GTEEE - LP_1GTEEE
#define XPCS_SR_AN_EEE_LP_ABL1_LP_1GTEEE_MASK 0x4u

//! Field LP_TEEE - LP_TEEE
#define XPCS_SR_AN_EEE_LP_ABL1_LP_TEEE_POS 3
//! Field LP_TEEE - LP_TEEE
#define XPCS_SR_AN_EEE_LP_ABL1_LP_TEEE_MASK 0x8u

//! Field LP_KXEEE - LP_KXEEE
#define XPCS_SR_AN_EEE_LP_ABL1_LP_KXEEE_POS 4
//! Field LP_KXEEE - LP_KXEEE
#define XPCS_SR_AN_EEE_LP_ABL1_LP_KXEEE_MASK 0x10u

//! Field LP_KX4EEE - LP_KX4EEE
#define XPCS_SR_AN_EEE_LP_ABL1_LP_KX4EEE_POS 5
//! Field LP_KX4EEE - LP_KX4EEE
#define XPCS_SR_AN_EEE_LP_ABL1_LP_KX4EEE_MASK 0x20u

//! Field LP_KREEE - LP_KREEE
#define XPCS_SR_AN_EEE_LP_ABL1_LP_KREEE_POS 6
//! Field LP_KREEE - LP_KREEE
#define XPCS_SR_AN_EEE_LP_ABL1_LP_KREEE_MASK 0x40u

//! Field RESERVED_15_7 - Reserved_15_7
#define XPCS_SR_AN_EEE_LP_ABL1_RESERVED_15_7_POS 7
//! Field RESERVED_15_7 - Reserved_15_7
#define XPCS_SR_AN_EEE_LP_ABL1_RESERVED_15_7_MASK 0xFF80u

//! @}

//! \defgroup XPCS_SR_AN_EEE_ABL2 Register XPCS_SR_AN_EEE_ABL2 - XPCS SR AN EEE ABL2
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_EEE_ABL2 0xF8
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_EEE_ABL2 0x001C00F8u

//! Register Reset Value
#define XPCS_SR_AN_EEE_ABL2_RST 0x00000008u

//! Field EEE_2PT5GT - EEE_2PT5GT
#define XPCS_SR_AN_EEE_ABL2_EEE_2PT5GT_POS 0
//! Field EEE_2PT5GT - EEE_2PT5GT
#define XPCS_SR_AN_EEE_ABL2_EEE_2PT5GT_MASK 0x1u

//! Field EEE_5GT - EEE_5GT
#define XPCS_SR_AN_EEE_ABL2_EEE_5GT_POS 1
//! Field EEE_5GT - EEE_5GT
#define XPCS_SR_AN_EEE_ABL2_EEE_5GT_MASK 0x2u

//! Field EEE_2PT5GKX - EEE_2PT5GKX
#define XPCS_SR_AN_EEE_ABL2_EEE_2PT5GKX_POS 2
//! Field EEE_2PT5GKX - EEE_2PT5GKX
#define XPCS_SR_AN_EEE_ABL2_EEE_2PT5GKX_MASK 0x4u

//! Field EEE_5GKR - EEE_5GKR
#define XPCS_SR_AN_EEE_ABL2_EEE_5GKR_POS 3
//! Field EEE_5GKR - EEE_5GKR
#define XPCS_SR_AN_EEE_ABL2_EEE_5GKR_MASK 0x8u

//! Field RESERVED_15_4 - Reserved_15_4
#define XPCS_SR_AN_EEE_ABL2_RESERVED_15_4_POS 4
//! Field RESERVED_15_4 - Reserved_15_4
#define XPCS_SR_AN_EEE_ABL2_RESERVED_15_4_MASK 0xFFF0u

//! @}

//! \defgroup XPCS_SR_AN_EEE_LP_ABL2 Register XPCS_SR_AN_EEE_LP_ABL2 - XPCS SR AN EEE LP ABL2
//! @{

//! Register Offset (relative)
#define XPCS_SR_AN_EEE_LP_ABL2 0xFC
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_SR_AN_EEE_LP_ABL2 0x001C00FCu

//! Register Reset Value
#define XPCS_SR_AN_EEE_LP_ABL2_RST 0x00000000u

//! Field RESERVED_1_0 - Reserved_1_0
#define XPCS_SR_AN_EEE_LP_ABL2_RESERVED_1_0_POS 0
//! Field RESERVED_1_0 - Reserved_1_0
#define XPCS_SR_AN_EEE_LP_ABL2_RESERVED_1_0_MASK 0x3u

//! Field LP_2PT5GKXEEE - LP_2PT5GKXEEE
#define XPCS_SR_AN_EEE_LP_ABL2_LP_2PT5GKXEEE_POS 2
//! Field LP_2PT5GKXEEE - LP_2PT5GKXEEE
#define XPCS_SR_AN_EEE_LP_ABL2_LP_2PT5GKXEEE_MASK 0x4u

//! Field LP_5GKREEE - LP_5GKREEE
#define XPCS_SR_AN_EEE_LP_ABL2_LP_5GKREEE_POS 3
//! Field LP_5GKREEE - LP_5GKREEE
#define XPCS_SR_AN_EEE_LP_ABL2_LP_5GKREEE_MASK 0x8u

//! Field RESERVED_15_4 - Reserved_15_4
#define XPCS_SR_AN_EEE_LP_ABL2_RESERVED_15_4_POS 4
//! Field RESERVED_15_4 - Reserved_15_4
#define XPCS_SR_AN_EEE_LP_ABL2_RESERVED_15_4_MASK 0xFFF0u

//! @}

//! \defgroup XPCS_VR_AN_DIG_CTRL1 Register XPCS_VR_AN_DIG_CTRL1 - XPCS VR AN DIG CTRL1
//! @{

//! Register Offset (relative)
#define XPCS_VR_AN_DIG_CTRL1 0x20000
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_VR_AN_DIG_CTRL1 0x001E0000u

//! Register Reset Value
#define XPCS_VR_AN_DIG_CTRL1_RST 0x00000000u

//! Field RESERVED_0 - Reserved_0
#define XPCS_VR_AN_DIG_CTRL1_RESERVED_0_POS 0
//! Field RESERVED_0 - Reserved_0
#define XPCS_VR_AN_DIG_CTRL1_RESERVED_0_MASK 0x1u

//! Field BYP_PWRUP - BYP_PWRUP
#define XPCS_VR_AN_DIG_CTRL1_BYP_PWRUP_POS 1
//! Field BYP_PWRUP - BYP_PWRUP
#define XPCS_VR_AN_DIG_CTRL1_BYP_PWRUP_MASK 0x2u

//! Field BYP_NONCE_MAT - BYP_NONCE_MAT
#define XPCS_VR_AN_DIG_CTRL1_BYP_NONCE_MAT_POS 2
//! Field BYP_NONCE_MAT - BYP_NONCE_MAT
#define XPCS_VR_AN_DIG_CTRL1_BYP_NONCE_MAT_MASK 0x4u

//! Field CL73_TMR_OVR_RIDE - CL73_TMR_OVR_RIDE
#define XPCS_VR_AN_DIG_CTRL1_CL73_TMR_OVR_RIDE_POS 3
//! Field CL73_TMR_OVR_RIDE - CL73_TMR_OVR_RIDE
#define XPCS_VR_AN_DIG_CTRL1_CL73_TMR_OVR_RIDE_MASK 0x8u

//! Field RESERVED_10_4 - Reserved_10_4
#define XPCS_VR_AN_DIG_CTRL1_RESERVED_10_4_POS 4
//! Field RESERVED_10_4 - Reserved_10_4
#define XPCS_VR_AN_DIG_CTRL1_RESERVED_10_4_MASK 0x7F0u

//! Field PWRSV - PWRSV
#define XPCS_VR_AN_DIG_CTRL1_PWRSV_POS 11
//! Field PWRSV - PWRSV
#define XPCS_VR_AN_DIG_CTRL1_PWRSV_MASK 0x800u

//! Field RESERVED_14_12 - Reserved_14_12
#define XPCS_VR_AN_DIG_CTRL1_RESERVED_14_12_POS 12
//! Field RESERVED_14_12 - Reserved_14_12
#define XPCS_VR_AN_DIG_CTRL1_RESERVED_14_12_MASK 0x7000u

//! Field VR_RST - VR_RST
#define XPCS_VR_AN_DIG_CTRL1_VR_RST_POS 15
//! Field VR_RST - VR_RST
#define XPCS_VR_AN_DIG_CTRL1_VR_RST_MASK 0x8000u

//! @}

//! \defgroup XPCS_VR_AN_INTR_MSK Register XPCS_VR_AN_INTR_MSK - XPCS VR AN INTR MSK
//! @{

//! Register Offset (relative)
#define XPCS_VR_AN_INTR_MSK 0x20004
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_VR_AN_INTR_MSK 0x001E0004u

//! Register Reset Value
#define XPCS_VR_AN_INTR_MSK_RST 0x00000000u

//! Field AN_INT_CMPLT_IE - AN_INT_CMPLT_IE
#define XPCS_VR_AN_INTR_MSK_AN_INT_CMPLT_IE_POS 0
//! Field AN_INT_CMPLT_IE - AN_INT_CMPLT_IE
#define XPCS_VR_AN_INTR_MSK_AN_INT_CMPLT_IE_MASK 0x1u

//! Field AN_INC_LINK_IE - AN_INC_LINK_IE
#define XPCS_VR_AN_INTR_MSK_AN_INC_LINK_IE_POS 1
//! Field AN_INC_LINK_IE - AN_INC_LINK_IE
#define XPCS_VR_AN_INTR_MSK_AN_INC_LINK_IE_MASK 0x2u

//! Field AN_PG_RCV_IE - AN_PG_RCV_IE
#define XPCS_VR_AN_INTR_MSK_AN_PG_RCV_IE_POS 2
//! Field AN_PG_RCV_IE - AN_PG_RCV_IE
#define XPCS_VR_AN_INTR_MSK_AN_PG_RCV_IE_MASK 0x4u

//! Field RESERVED_15_3 - Reserved_15_3
#define XPCS_VR_AN_INTR_MSK_RESERVED_15_3_POS 3
//! Field RESERVED_15_3 - Reserved_15_3
#define XPCS_VR_AN_INTR_MSK_RESERVED_15_3_MASK 0xFFF8u

//! @}

//! \defgroup XPCS_VR_AN_INTR Register XPCS_VR_AN_INTR - XPCS VR AN INTR
//! @{

//! Register Offset (relative)
#define XPCS_VR_AN_INTR 0x20008
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_VR_AN_INTR 0x001E0008u

//! Register Reset Value
#define XPCS_VR_AN_INTR_RST 0x00000000u

//! Field AN_INT_CMPLT - AN_INT_CMPLT
#define XPCS_VR_AN_INTR_AN_INT_CMPLT_POS 0
//! Field AN_INT_CMPLT - AN_INT_CMPLT
#define XPCS_VR_AN_INTR_AN_INT_CMPLT_MASK 0x1u

//! Field AN_INC_LINK - AN_INC_LINK
#define XPCS_VR_AN_INTR_AN_INC_LINK_POS 1
//! Field AN_INC_LINK - AN_INC_LINK
#define XPCS_VR_AN_INTR_AN_INC_LINK_MASK 0x2u

//! Field AN_PG_RCV - AN_PG_RCV
#define XPCS_VR_AN_INTR_AN_PG_RCV_POS 2
//! Field AN_PG_RCV - AN_PG_RCV
#define XPCS_VR_AN_INTR_AN_PG_RCV_MASK 0x4u

//! Field RESERVED_15_3 - Reserved_15_3
#define XPCS_VR_AN_INTR_RESERVED_15_3_POS 3
//! Field RESERVED_15_3 - Reserved_15_3
#define XPCS_VR_AN_INTR_RESERVED_15_3_MASK 0xFFF8u

//! @}

//! \defgroup XPCS_VR_AN_KR_MODE_CTRL Register XPCS_VR_AN_KR_MODE_CTRL - XPCS VR AN KR MODE CTRL
//! @{

//! Register Offset (relative)
#define XPCS_VR_AN_KR_MODE_CTRL 0x2000C
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_VR_AN_KR_MODE_CTRL 0x001E000Cu

//! Register Reset Value
#define XPCS_VR_AN_KR_MODE_CTRL_RST 0x00000000u

//! Field PDET_EN - PDET_EN
#define XPCS_VR_AN_KR_MODE_CTRL_PDET_EN_POS 0
//! Field PDET_EN - PDET_EN
#define XPCS_VR_AN_KR_MODE_CTRL_PDET_EN_MASK 0x1u

//! Field RESERVED_15_1 - Reserved_15_1
#define XPCS_VR_AN_KR_MODE_CTRL_RESERVED_15_1_POS 1
//! Field RESERVED_15_1 - Reserved_15_1
#define XPCS_VR_AN_KR_MODE_CTRL_RESERVED_15_1_MASK 0xFFFEu

//! @}

//! \defgroup XPCS_VR_AN_TIMER_CTRL0 Register XPCS_VR_AN_TIMER_CTRL0 - XPCS VR AN TIMER CTRL0
//! @{

//! Register Offset (relative)
#define XPCS_VR_AN_TIMER_CTRL0 0x20010
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_VR_AN_TIMER_CTRL0 0x001E0010u

//! Register Reset Value
#define XPCS_VR_AN_TIMER_CTRL0_RST 0x00000000u

//! Field BRK_LINK_TIME - BRK_LINK_TIME
#define XPCS_VR_AN_TIMER_CTRL0_BRK_LINK_TIME_POS 0
//! Field BRK_LINK_TIME - BRK_LINK_TIME
#define XPCS_VR_AN_TIMER_CTRL0_BRK_LINK_TIME_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_VR_AN_TIMER_CTRL1 Register XPCS_VR_AN_TIMER_CTRL1 - XPCS VR AN TIMER CTRL1
//! @{

//! Register Offset (relative)
#define XPCS_VR_AN_TIMER_CTRL1 0x20014
//! Register Offset (absolute) for 1st Instance XPCS_AN_MMD
#define XPCS_AN_MMD_XPCS_VR_AN_TIMER_CTRL1 0x001E0014u

//! Register Reset Value
#define XPCS_VR_AN_TIMER_CTRL1_RST 0x00000000u

//! Field INHBT_OR_WAIT_TIME - INHBT_OR_WAIT_TIME
#define XPCS_VR_AN_TIMER_CTRL1_INHBT_OR_WAIT_TIME_POS 0
//! Field INHBT_OR_WAIT_TIME - INHBT_OR_WAIT_TIME
#define XPCS_VR_AN_TIMER_CTRL1_INHBT_OR_WAIT_TIME_MASK 0xFFFFu

//! @}

//! @}

#endif
