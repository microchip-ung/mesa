//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_reddydev.priv.p34x_chip.chip_work/ipg_lsd/lsd_sys/source_32b/xml/reg_files/chip_usxgmii/XPCS_VS_MMD1_def.xml
// Register File Name  : XPCS_VS_MMD1
// Register File Title : XPCS VS MMD1
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _XPCS_VS_MMD1_H
#define _XPCS_VS_MMD1_H

//! \defgroup XPCS_VS_MMD1 Register File XPCS_VS_MMD1 - XPCS VS MMD1
//! @{

//! Base Address of XPCS_VS_MMD1
#define XPCS_VS_MMD1_MODULE_BASE 0x00780000u

//! \defgroup XPCS_SR_VSMMD_PMA_ID1 Register XPCS_SR_VSMMD_PMA_ID1 - XPCS SR VSMMD PMA ID1
//! @{

//! Register Offset (relative)
#define XPCS_SR_VSMMD_PMA_ID1 0x0
//! Register Offset (absolute) for 1st Instance XPCS_VS_MMD1
#define XPCS_VS_MMD1_XPCS_SR_VSMMD_PMA_ID1 0x00780000u

//! Register Reset Value
#define XPCS_SR_VSMMD_PMA_ID1_RST 0x00000000u

//! Field PMADOUI_3_18 - PMADOUI_3_18
#define XPCS_SR_VSMMD_PMA_ID1_PMADOUI_3_18_POS 0
//! Field PMADOUI_3_18 - PMADOUI_3_18
#define XPCS_SR_VSMMD_PMA_ID1_PMADOUI_3_18_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_VSMMD_PMA_ID2 Register XPCS_SR_VSMMD_PMA_ID2 - XPCS SR VSMMD PMA ID2
//! @{

//! Register Offset (relative)
#define XPCS_SR_VSMMD_PMA_ID2 0x4
//! Register Offset (absolute) for 1st Instance XPCS_VS_MMD1
#define XPCS_VS_MMD1_XPCS_SR_VSMMD_PMA_ID2 0x00780004u

//! Register Reset Value
#define XPCS_SR_VSMMD_PMA_ID2_RST 0x00000000u

//! Field PMADRN_3_0 - PMADRN_3_0
#define XPCS_SR_VSMMD_PMA_ID2_PMADRN_3_0_POS 0
//! Field PMADRN_3_0 - PMADRN_3_0
#define XPCS_SR_VSMMD_PMA_ID2_PMADRN_3_0_MASK 0xFu

//! Field PMADMMN_5_0 - PMADMMN_5_0
#define XPCS_SR_VSMMD_PMA_ID2_PMADMMN_5_0_POS 4
//! Field PMADMMN_5_0 - PMADMMN_5_0
#define XPCS_SR_VSMMD_PMA_ID2_PMADMMN_5_0_MASK 0x3F0u

//! Field PMADOUI_19_24 - PMADOUI_19_24
#define XPCS_SR_VSMMD_PMA_ID2_PMADOUI_19_24_POS 10
//! Field PMADOUI_19_24 - PMADOUI_19_24
#define XPCS_SR_VSMMD_PMA_ID2_PMADOUI_19_24_MASK 0xFC00u

//! @}

//! \defgroup XPCS_SR_VSMMD_DEV_ID1 Register XPCS_SR_VSMMD_DEV_ID1 - XPCS SR VSMMD DEV ID1
//! @{

//! Register Offset (relative)
#define XPCS_SR_VSMMD_DEV_ID1 0x8
//! Register Offset (absolute) for 1st Instance XPCS_VS_MMD1
#define XPCS_VS_MMD1_XPCS_SR_VSMMD_DEV_ID1 0x00780008u

//! Register Reset Value
#define XPCS_SR_VSMMD_DEV_ID1_RST 0x00000000u

//! Field VSDOUI_3_18 - VSDOUI_3_18
#define XPCS_SR_VSMMD_DEV_ID1_VSDOUI_3_18_POS 0
//! Field VSDOUI_3_18 - VSDOUI_3_18
#define XPCS_SR_VSMMD_DEV_ID1_VSDOUI_3_18_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_VSMMD_DEV_ID2 Register XPCS_SR_VSMMD_DEV_ID2 - XPCS SR VSMMD DEV ID2
//! @{

//! Register Offset (relative)
#define XPCS_SR_VSMMD_DEV_ID2 0xC
//! Register Offset (absolute) for 1st Instance XPCS_VS_MMD1
#define XPCS_VS_MMD1_XPCS_SR_VSMMD_DEV_ID2 0x0078000Cu

//! Register Reset Value
#define XPCS_SR_VSMMD_DEV_ID2_RST 0x00000000u

//! Field VSDRN_3_0 - VSDRN_3_0
#define XPCS_SR_VSMMD_DEV_ID2_VSDRN_3_0_POS 0
//! Field VSDRN_3_0 - VSDRN_3_0
#define XPCS_SR_VSMMD_DEV_ID2_VSDRN_3_0_MASK 0xFu

//! Field VSDMMN_5_0 - VSDMMN_5_0
#define XPCS_SR_VSMMD_DEV_ID2_VSDMMN_5_0_POS 4
//! Field VSDMMN_5_0 - VSDMMN_5_0
#define XPCS_SR_VSMMD_DEV_ID2_VSDMMN_5_0_MASK 0x3F0u

//! Field VSDOUI_19_24 - VSDOUI_19_24
#define XPCS_SR_VSMMD_DEV_ID2_VSDOUI_19_24_POS 10
//! Field VSDOUI_19_24 - VSDOUI_19_24
#define XPCS_SR_VSMMD_DEV_ID2_VSDOUI_19_24_MASK 0xFC00u

//! @}

//! \defgroup XPCS_SR_VSMMD_PCS_ID1 Register XPCS_SR_VSMMD_PCS_ID1 - XPCS SR VSMMD PCS ID1
//! @{

//! Register Offset (relative)
#define XPCS_SR_VSMMD_PCS_ID1 0x10
//! Register Offset (absolute) for 1st Instance XPCS_VS_MMD1
#define XPCS_VS_MMD1_XPCS_SR_VSMMD_PCS_ID1 0x00780010u

//! Register Reset Value
#define XPCS_SR_VSMMD_PCS_ID1_RST 0x00007996u

//! Field PCSDOUI_3_18 - PCSDOUI_3_18
#define XPCS_SR_VSMMD_PCS_ID1_PCSDOUI_3_18_POS 0
//! Field PCSDOUI_3_18 - PCSDOUI_3_18
#define XPCS_SR_VSMMD_PCS_ID1_PCSDOUI_3_18_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_VSMMD_PCS_ID2 Register XPCS_SR_VSMMD_PCS_ID2 - XPCS SR VSMMD PCS ID2
//! @{

//! Register Offset (relative)
#define XPCS_SR_VSMMD_PCS_ID2 0x14
//! Register Offset (absolute) for 1st Instance XPCS_VS_MMD1
#define XPCS_VS_MMD1_XPCS_SR_VSMMD_PCS_ID2 0x00780014u

//! Register Reset Value
#define XPCS_SR_VSMMD_PCS_ID2_RST 0x0000CED0u

//! Field PCSDRN_3_0 - PCSDRN_3_0
#define XPCS_SR_VSMMD_PCS_ID2_PCSDRN_3_0_POS 0
//! Field PCSDRN_3_0 - PCSDRN_3_0
#define XPCS_SR_VSMMD_PCS_ID2_PCSDRN_3_0_MASK 0xFu

//! Field PCSDMMN_5_0 - PCSDMMN_5_0
#define XPCS_SR_VSMMD_PCS_ID2_PCSDMMN_5_0_POS 4
//! Field PCSDMMN_5_0 - PCSDMMN_5_0
#define XPCS_SR_VSMMD_PCS_ID2_PCSDMMN_5_0_MASK 0x3F0u

//! Field PCSDOUI_19_24 - PCSDOUI_19_24
#define XPCS_SR_VSMMD_PCS_ID2_PCSDOUI_19_24_POS 10
//! Field PCSDOUI_19_24 - PCSDOUI_19_24
#define XPCS_SR_VSMMD_PCS_ID2_PCSDOUI_19_24_MASK 0xFC00u

//! @}

//! \defgroup XPCS_SR_VSMMD_AN_ID1 Register XPCS_SR_VSMMD_AN_ID1 - XPCS SR VSMMD AN ID1
//! @{

//! Register Offset (relative)
#define XPCS_SR_VSMMD_AN_ID1 0x18
//! Register Offset (absolute) for 1st Instance XPCS_VS_MMD1
#define XPCS_VS_MMD1_XPCS_SR_VSMMD_AN_ID1 0x00780018u

//! Register Reset Value
#define XPCS_SR_VSMMD_AN_ID1_RST 0x00000000u

//! Field ANDOUI_3_18 - ANDOUI_3_18
#define XPCS_SR_VSMMD_AN_ID1_ANDOUI_3_18_POS 0
//! Field ANDOUI_3_18 - ANDOUI_3_18
#define XPCS_SR_VSMMD_AN_ID1_ANDOUI_3_18_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_VSMMD_AN_ID2 Register XPCS_SR_VSMMD_AN_ID2 - XPCS SR VSMMD AN ID2
//! @{

//! Register Offset (relative)
#define XPCS_SR_VSMMD_AN_ID2 0x1C
//! Register Offset (absolute) for 1st Instance XPCS_VS_MMD1
#define XPCS_VS_MMD1_XPCS_SR_VSMMD_AN_ID2 0x0078001Cu

//! Register Reset Value
#define XPCS_SR_VSMMD_AN_ID2_RST 0x00000000u

//! Field ANDRN_3_0 - ANDRN_3_0
#define XPCS_SR_VSMMD_AN_ID2_ANDRN_3_0_POS 0
//! Field ANDRN_3_0 - ANDRN_3_0
#define XPCS_SR_VSMMD_AN_ID2_ANDRN_3_0_MASK 0xFu

//! Field ANDMMN_5_0 - ANDMMN_5_0
#define XPCS_SR_VSMMD_AN_ID2_ANDMMN_5_0_POS 4
//! Field ANDMMN_5_0 - ANDMMN_5_0
#define XPCS_SR_VSMMD_AN_ID2_ANDMMN_5_0_MASK 0x3F0u

//! Field ANDOUI_19_24 - ANDOUI_19_24
#define XPCS_SR_VSMMD_AN_ID2_ANDOUI_19_24_POS 10
//! Field ANDOUI_19_24 - ANDOUI_19_24
#define XPCS_SR_VSMMD_AN_ID2_ANDOUI_19_24_MASK 0xFC00u

//! @}

//! \defgroup XPCS_SR_VSMMD_STS Register XPCS_SR_VSMMD_STS - XPCS SR VSMMD STS
//! @{

//! Register Offset (relative)
#define XPCS_SR_VSMMD_STS 0x20
//! Register Offset (absolute) for 1st Instance XPCS_VS_MMD1
#define XPCS_VS_MMD1_XPCS_SR_VSMMD_STS 0x00780020u

//! Register Reset Value
#define XPCS_SR_VSMMD_STS_RST 0x00008000u

//! Field RESERVED_13_0 - Reserved_13_0
#define XPCS_SR_VSMMD_STS_RESERVED_13_0_POS 0
//! Field RESERVED_13_0 - Reserved_13_0
#define XPCS_SR_VSMMD_STS_RESERVED_13_0_MASK 0x3FFFu

//! Field VSDP - VSDP
#define XPCS_SR_VSMMD_STS_VSDP_POS 14
//! Field VSDP - VSDP
#define XPCS_SR_VSMMD_STS_VSDP_MASK 0xC000u

//! @}

//! \defgroup XPCS_SR_VSMMD_CTRL Register XPCS_SR_VSMMD_CTRL - XPCS SR VSMMD CTRL
//! @{

//! Register Offset (relative)
#define XPCS_SR_VSMMD_CTRL 0x24
//! Register Offset (absolute) for 1st Instance XPCS_VS_MMD1
#define XPCS_VS_MMD1_XPCS_SR_VSMMD_CTRL 0x00780024u

//! Register Reset Value
#define XPCS_SR_VSMMD_CTRL_RST 0x0000000Fu

//! Field AN_MMD_EN - AN_MMD_EN
#define XPCS_SR_VSMMD_CTRL_AN_MMD_EN_POS 0
//! Field AN_MMD_EN - AN_MMD_EN
#define XPCS_SR_VSMMD_CTRL_AN_MMD_EN_MASK 0x1u

//! Field PCS_XS_MMD_EN - PCS_XS_MMD_EN
#define XPCS_SR_VSMMD_CTRL_PCS_XS_MMD_EN_POS 1
//! Field PCS_XS_MMD_EN - PCS_XS_MMD_EN
#define XPCS_SR_VSMMD_CTRL_PCS_XS_MMD_EN_MASK 0x2u

//! Field MII_MMD_EN - MII_MMD_EN
#define XPCS_SR_VSMMD_CTRL_MII_MMD_EN_POS 2
//! Field MII_MMD_EN - MII_MMD_EN
#define XPCS_SR_VSMMD_CTRL_MII_MMD_EN_MASK 0x4u

//! Field PMA_MMD_EN - PMA_MMD_EN
#define XPCS_SR_VSMMD_CTRL_PMA_MMD_EN_POS 3
//! Field PMA_MMD_EN - PMA_MMD_EN
#define XPCS_SR_VSMMD_CTRL_PMA_MMD_EN_MASK 0x8u

//! Field FASTSIM - FASTSIM
#define XPCS_SR_VSMMD_CTRL_FASTSIM_POS 4
//! Field FASTSIM - FASTSIM
#define XPCS_SR_VSMMD_CTRL_FASTSIM_MASK 0x10u

//! Field PD_CTRL - PD_CTRL
#define XPCS_SR_VSMMD_CTRL_PD_CTRL_POS 5
//! Field PD_CTRL - PD_CTRL
#define XPCS_SR_VSMMD_CTRL_PD_CTRL_MASK 0x20u

//! Field RESERVED_15_6 - Reserved_15_6
#define XPCS_SR_VSMMD_CTRL_RESERVED_15_6_POS 6
//! Field RESERVED_15_6 - Reserved_15_6
#define XPCS_SR_VSMMD_CTRL_RESERVED_15_6_MASK 0xFFC0u

//! @}

//! \defgroup XPCS_SR_VSMMD_PKGID1 Register XPCS_SR_VSMMD_PKGID1 - XPCS SR VSMMD PKGID1
//! @{

//! Register Offset (relative)
#define XPCS_SR_VSMMD_PKGID1 0x38
//! Register Offset (absolute) for 1st Instance XPCS_VS_MMD1
#define XPCS_VS_MMD1_XPCS_SR_VSMMD_PKGID1 0x00780038u

//! Register Reset Value
#define XPCS_SR_VSMMD_PKGID1_RST 0x00000000u

//! Field MMDPOUI_3_18 - MMDPOUI_3_18
#define XPCS_SR_VSMMD_PKGID1_MMDPOUI_3_18_POS 0
//! Field MMDPOUI_3_18 - MMDPOUI_3_18
#define XPCS_SR_VSMMD_PKGID1_MMDPOUI_3_18_MASK 0xFFFFu

//! @}

//! \defgroup XPCS_SR_VSMMD_PKGID2 Register XPCS_SR_VSMMD_PKGID2 - XPCS SR VSMMD PKGID2
//! @{

//! Register Offset (relative)
#define XPCS_SR_VSMMD_PKGID2 0x3C
//! Register Offset (absolute) for 1st Instance XPCS_VS_MMD1
#define XPCS_VS_MMD1_XPCS_SR_VSMMD_PKGID2 0x0078003Cu

//! Register Reset Value
#define XPCS_SR_VSMMD_PKGID2_RST 0x00000000u

//! Field MMDPRN_3_0 - MMDPRN_3_0
#define XPCS_SR_VSMMD_PKGID2_MMDPRN_3_0_POS 0
//! Field MMDPRN_3_0 - MMDPRN_3_0
#define XPCS_SR_VSMMD_PKGID2_MMDPRN_3_0_MASK 0xFu

//! Field MMDPMMN_5_0 - MMDPMMN_5_0
#define XPCS_SR_VSMMD_PKGID2_MMDPMMN_5_0_POS 4
//! Field MMDPMMN_5_0 - MMDPMMN_5_0
#define XPCS_SR_VSMMD_PKGID2_MMDPMMN_5_0_MASK 0x3F0u

//! Field MMDPOUI_19_24 - MMDPOUI_19_24
#define XPCS_SR_VSMMD_PKGID2_MMDPOUI_19_24_POS 10
//! Field MMDPOUI_19_24 - MMDPOUI_19_24
#define XPCS_SR_VSMMD_PKGID2_MMDPOUI_19_24_MASK 0xFC00u

//! @}

//! @}

#endif
