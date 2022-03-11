//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/p31g_chipid_def.xml
// Register File Name  : CHIPID
// Register File Title : Chip ID Register Description
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _CHIPID_H
#define _CHIPID_H

//! \defgroup CHIPID Register File CHIPID - Chip ID Register Description
//! @{

//! Base Address of CHIPID
#define CHIPID_MODULE_BASE 0x00D28880u

//! \defgroup CHIPID_MPS_MANID Register CHIPID_MPS_MANID - Manufacturer Identification Register
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_MANID 0x0
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_MANID 0x00D28880u

//! Register Reset Value
#define CHIPID_MPS_MANID_RST 0x00001120u

//! Field MANUF - Manufacturer Identification Number (JEDEC)
#define CHIPID_MPS_MANID_MANUF_POS 5
//! Field MANUF - Manufacturer Identification Number (JEDEC)
#define CHIPID_MPS_MANID_MANUF_MASK 0xFFE0u

//! @}

//! \defgroup CHIPID_MPS_CHIPID_L Register CHIPID_MPS_CHIPID_L - Chip ID LSB
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_CHIPID_L 0x4
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_CHIPID_L 0x00D28884u

//! Register Reset Value
#define CHIPID_MPS_CHIPID_L_RST 0x00000113u

//! Field V1 - Fixed to 1
#define CHIPID_MPS_CHIPID_L_V1_POS 0
//! Field V1 - Fixed to 1
#define CHIPID_MPS_CHIPID_L_V1_MASK 0x1u

//! Field MANID - Manufacturer ID
#define CHIPID_MPS_CHIPID_L_MANID_POS 1
//! Field MANID - Manufacturer ID
#define CHIPID_MPS_CHIPID_L_MANID_MASK 0xFFEu

//! Field PNUML - Part Number LSB
#define CHIPID_MPS_CHIPID_L_PNUML_POS 12
//! Field PNUML - Part Number LSB
#define CHIPID_MPS_CHIPID_L_PNUML_MASK 0xF000u
//! Constant UNFUSED - Unfused
#define CONST_CHIPID_MPS_CHIPID_L_PNUML_UNFUSED 0x0
//! Constant SWVL_DEBUG - SwanVille Debug
#define CONST_CHIPID_MPS_CHIPID_L_PNUML_SWVL_DEBUG 0x1
//! Constant P34X_DEBUG - P34X debug
#define CONST_CHIPID_MPS_CHIPID_L_PNUML_P34X_DEBUG 0x1
//! Constant P34X - P34X production
#define CONST_CHIPID_MPS_CHIPID_L_PNUML_P34X 0x2
//! Constant P31G - P31G Swanville SGMII
#define CONST_CHIPID_MPS_CHIPID_L_PNUML_P31G 0x9
//! Constant N31G - N31G Swanville PCIe
#define CONST_CHIPID_MPS_CHIPID_L_PNUML_N31G 0xA
//! Constant FXVL_V - FOXVL V no VPRO
#define CONST_CHIPID_MPS_CHIPID_L_PNUML_FXVL_V 0xB
//! Constant FXVL_LM - FOXVL_LM with VPRO
#define CONST_CHIPID_MPS_CHIPID_L_PNUML_FXVL_LM 0xC

//! @}

//! \defgroup CHIPID_MPS_CHIPID_M Register CHIPID_MPS_CHIPID_M - Chip ID MSB
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_CHIPID_M 0x8
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_CHIPID_M 0x00D28888u

//! Register Reset Value
#define CHIPID_MPS_CHIPID_M_RST 0x00000000u

//! Field PNUMM - Part Number MSB
#define CHIPID_MPS_CHIPID_M_PNUMM_POS 0
//! Field PNUMM - Part Number MSB
#define CHIPID_MPS_CHIPID_M_PNUMM_MASK 0xFFFu

//! Field VERSION - Chip Version Number
#define CHIPID_MPS_CHIPID_M_VERSION_POS 12
//! Field VERSION - Chip Version Number
#define CHIPID_MPS_CHIPID_M_VERSION_MASK 0x7000u

//! Field V0 - Fixed to 0
#define CHIPID_MPS_CHIPID_M_V0_POS 15
//! Field V0 - Fixed to 0
#define CHIPID_MPS_CHIPID_M_V0_MASK 0x8000u

//! @}

//! \defgroup CHIPID_MPS_CHIP_LOC0 Register CHIPID_MPS_CHIP_LOC0 - Chip Location Register
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_CHIP_LOC0 0xC
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_CHIP_LOC0 0x00D2888Cu

//! Register Reset Value
#define CHIPID_MPS_CHIP_LOC0_RST 0x00000000u

//! Field DD - Day
#define CHIPID_MPS_CHIP_LOC0_DD_POS 1
//! Field DD - Day
#define CHIPID_MPS_CHIP_LOC0_DD_MASK 0x3Eu

//! Field MM - Month
#define CHIPID_MPS_CHIP_LOC0_MM_POS 6
//! Field MM - Month
#define CHIPID_MPS_CHIP_LOC0_MM_MASK 0x3C0u

//! Field YYYYY - Year
#define CHIPID_MPS_CHIP_LOC0_YYYYY_POS 10
//! Field YYYYY - Year
#define CHIPID_MPS_CHIP_LOC0_YYYYY_MASK 0x7C00u

//! @}

//! \defgroup CHIPID_MPS_CHIP_LOC1 Register CHIPID_MPS_CHIP_LOC1 - Chip Location Register
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_CHIP_LOC1 0x10
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_CHIP_LOC1 0x00D28890u

//! Register Reset Value
#define CHIPID_MPS_CHIP_LOC1_RST 0x00000000u

//! Field CHIP_X - Chip X Location
#define CHIPID_MPS_CHIP_LOC1_CHIP_X_POS 0
//! Field CHIP_X - Chip X Location
#define CHIPID_MPS_CHIP_LOC1_CHIP_X_MASK 0x7Fu

//! Field CHIP_Y - Chip Y Location
#define CHIPID_MPS_CHIP_LOC1_CHIP_Y_POS 7
//! Field CHIP_Y - Chip Y Location
#define CHIPID_MPS_CHIP_LOC1_CHIP_Y_MASK 0x3F80u

//! @}

//! \defgroup CHIPID_MPS_CHIP_LOC2 Register CHIPID_MPS_CHIP_LOC2 - Chip Location Register
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_CHIP_LOC2 0x14
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_CHIP_LOC2 0x00D28894u

//! Register Reset Value
#define CHIPID_MPS_CHIP_LOC2_RST 0x00000000u

//! Field WAFER_ID - Wafer ID
#define CHIPID_MPS_CHIP_LOC2_WAFER_ID_POS 0
//! Field WAFER_ID - Wafer ID
#define CHIPID_MPS_CHIP_LOC2_WAFER_ID_MASK 0x1Fu

//! Field FUTURE_USE - For future use
#define CHIPID_MPS_CHIP_LOC2_FUTURE_USE_POS 5
//! Field FUTURE_USE - For future use
#define CHIPID_MPS_CHIP_LOC2_FUTURE_USE_MASK 0x1FE0u

//! Field CODING_T - Coding type
#define CHIPID_MPS_CHIP_LOC2_CODING_T_POS 13
//! Field CODING_T - Coding type
#define CHIPID_MPS_CHIP_LOC2_CODING_T_MASK 0xE000u

//! @}

//! \defgroup CHIPID_FAB_LOT_ID0 Register CHIPID_FAB_LOT_ID0 - FAB LOT ID Register 0
//! @{

//! Register Offset (relative)
#define CHIPID_FAB_LOT_ID0 0x18
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_FAB_LOT_ID0 0x00D28898u

//! Register Reset Value
#define CHIPID_FAB_LOT_ID0_RST 0x00000000u

//! Field LOTID0 - Lot ID bit 15 to 0
#define CHIPID_FAB_LOT_ID0_LOTID0_POS 0
//! Field LOTID0 - Lot ID bit 15 to 0
#define CHIPID_FAB_LOT_ID0_LOTID0_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_FAB_LOT_ID1 Register CHIPID_FAB_LOT_ID1 - FAB LOT ID Register 1
//! @{

//! Register Offset (relative)
#define CHIPID_FAB_LOT_ID1 0x1C
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_FAB_LOT_ID1 0x00D2889Cu

//! Register Reset Value
#define CHIPID_FAB_LOT_ID1_RST 0x00000000u

//! Field LOTID1 - Lot ID bit 31 to 16
#define CHIPID_FAB_LOT_ID1_LOTID1_POS 0
//! Field LOTID1 - Lot ID bit 31 to 16
#define CHIPID_FAB_LOT_ID1_LOTID1_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_FAB_LOT_ID2 Register CHIPID_FAB_LOT_ID2 - FAB LOT ID Register 2
//! @{

//! Register Offset (relative)
#define CHIPID_FAB_LOT_ID2 0x20
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_FAB_LOT_ID2 0x00D288A0u

//! Register Reset Value
#define CHIPID_FAB_LOT_ID2_RST 0x00000000u

//! Field LOTID2 - Lot ID bit 47 to 32
#define CHIPID_FAB_LOT_ID2_LOTID2_POS 0
//! Field LOTID2 - Lot ID bit 47 to 32
#define CHIPID_FAB_LOT_ID2_LOTID2_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_FAB_LOT_ID3 Register CHIPID_FAB_LOT_ID3 - FAB LOT ID Register 3
//! @{

//! Register Offset (relative)
#define CHIPID_FAB_LOT_ID3 0x24
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_FAB_LOT_ID3 0x00D288A4u

//! Register Reset Value
#define CHIPID_FAB_LOT_ID3_RST 0x00000000u

//! Field LOTID3 - Lot ID bit 59 to 48
#define CHIPID_FAB_LOT_ID3_LOTID3_POS 0
//! Field LOTID3 - Lot ID bit 59 to 48
#define CHIPID_FAB_LOT_ID3_LOTID3_MASK 0xFFFu

//! Field PARITY - Parity of Lot ID
#define CHIPID_FAB_LOT_ID3_PARITY_POS 12
//! Field PARITY - Parity of Lot ID
#define CHIPID_FAB_LOT_ID3_PARITY_MASK 0x1000u

//! @}

//! \defgroup CHIPID_FAB_BELOT_ID0 Register CHIPID_FAB_BELOT_ID0 - FAB BELOT ID Register 0
//! @{

//! Register Offset (relative)
#define CHIPID_FAB_BELOT_ID0 0x28
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_FAB_BELOT_ID0 0x00D288A8u

//! Register Reset Value
#define CHIPID_FAB_BELOT_ID0_RST 0x00000000u

//! Field BELOTID0 - BE Lot ID bit 15 to 0
#define CHIPID_FAB_BELOT_ID0_BELOTID0_POS 0
//! Field BELOTID0 - BE Lot ID bit 15 to 0
#define CHIPID_FAB_BELOT_ID0_BELOTID0_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_FAB_BELOT_ID1 Register CHIPID_FAB_BELOT_ID1 - FAB BELOT ID Register 1
//! @{

//! Register Offset (relative)
#define CHIPID_FAB_BELOT_ID1 0x2C
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_FAB_BELOT_ID1 0x00D288ACu

//! Register Reset Value
#define CHIPID_FAB_BELOT_ID1_RST 0x00000000u

//! Field BELOTID1 - BE Lot ID bit 31 to 16
#define CHIPID_FAB_BELOT_ID1_BELOTID1_POS 0
//! Field BELOTID1 - BE Lot ID bit 31 to 16
#define CHIPID_FAB_BELOT_ID1_BELOTID1_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_FAB_BELOT_ID2 Register CHIPID_FAB_BELOT_ID2 - FAB BELOT ID Register 2
//! @{

//! Register Offset (relative)
#define CHIPID_FAB_BELOT_ID2 0x30
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_FAB_BELOT_ID2 0x00D288B0u

//! Register Reset Value
#define CHIPID_FAB_BELOT_ID2_RST 0x00000000u

//! Field BELOTID2 - BE Lot ID bit 47 to 32
#define CHIPID_FAB_BELOT_ID2_BELOTID2_POS 0
//! Field BELOTID2 - BE Lot ID bit 47 to 32
#define CHIPID_FAB_BELOT_ID2_BELOTID2_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_FAB_PVT Register CHIPID_FAB_PVT - FAB PVT
//! @{

//! Register Offset (relative)
#define CHIPID_FAB_PVT 0x34
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_FAB_PVT 0x00D288B4u

//! Register Reset Value
#define CHIPID_FAB_PVT_RST 0x00000000u

//! Field PVT - PVT value
#define CHIPID_FAB_PVT_PVT_POS 0
//! Field PVT - PVT value
#define CHIPID_FAB_PVT_PVT_MASK 0x3FFu

//! @}

//! \defgroup CHIPID_FAB_PVT_DVS Register CHIPID_FAB_PVT_DVS - FAB PVT DVS
//! @{

//! Register Offset (relative)
#define CHIPID_FAB_PVT_DVS 0x38
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_FAB_PVT_DVS 0x00D288B8u

//! Register Reset Value
#define CHIPID_FAB_PVT_DVS_RST 0x00000000u

//! Field PVT_DVS - PVT DVS
#define CHIPID_FAB_PVT_DVS_PVT_DVS_POS 0
//! Field PVT_DVS - PVT DVS
#define CHIPID_FAB_PVT_DVS_PVT_DVS_MASK 0x7FFu

//! @}

//! \defgroup CHIPID_FAB_PVT_DVF Register CHIPID_FAB_PVT_DVF - FAB PVT DVF
//! @{

//! Register Offset (relative)
#define CHIPID_FAB_PVT_DVF 0x3C
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_FAB_PVT_DVF 0x00D288BCu

//! Register Reset Value
#define CHIPID_FAB_PVT_DVF_RST 0x00000000u

//! Field PVT_DVF - PVT DVF
#define CHIPID_FAB_PVT_DVF_PVT_DVF_POS 0
//! Field PVT_DVF - PVT DVF
#define CHIPID_FAB_PVT_DVF_PVT_DVF_MASK 0x7FFu

//! @}

//! \defgroup CHIPID_ID_CFG Register CHIPID_ID_CFG - Chip Configuration Register
//! @{

//! Register Offset (relative)
#define CHIPID_ID_CFG 0x40
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_ID_CFG 0x00D288C0u

//! Register Reset Value
#define CHIPID_ID_CFG_RST 0x00000000u

// For P31G
//! Field FXVL - FXVL
#define CHIPID_ID_CFG_FXVL_POS 0
//! Field FXVL - FXVL
#define CHIPID_ID_CFG_FXVL_MASK 0x3u
// For P34X
//! Field RES - Reserved
#define CHIPID_ID_CFG_RES_POS 0
//! Field RES - Reserved
#define CHIPID_ID_CFG_RES_MASK 0x3u

//! Field SEC_EN - Security Enable
#define CHIPID_ID_CFG_SEC_EN_POS 2
//! Field SEC_EN - Security Enable
#define CHIPID_ID_CFG_SEC_EN_MASK 0x4u
//! Constant DISABLED - Disable Security.
#define CONST_CHIPID_ID_CFG_SEC_EN_DISABLED 0x0
//! Constant ENABLED - Enable Security
#define CONST_CHIPID_ID_CFG_SEC_EN_ENABLED 0x1
// For P31G
//! Field G2_5_DIS - Disable GPHY 2.5G Mode
#define CHIPID_ID_CFG_G2_5_DIS_POS 3
//! Field G2_5_DIS - Disable GPHY 2.5G Mode
#define CHIPID_ID_CFG_G2_5_DIS_MASK 0x8u
//! Constant ENABLED - Enabled
#define CONST_CHIPID_ID_CFG_G2_5_DIS_ENABLED 0x0
//! Constant DISABLED - Disable GPHY 2.5G support.
#define CONST_CHIPID_ID_CFG_G2_5_DIS_DISABLED 0x1
// For P34X
//! Field G2_5_DIS0 - Disable GPHY 2.5G Mode for slice 0
#define CHIPID_ID_CFG_G2_5_DIS0_POS 3
//! Field G2_5_DIS0 - Disable GPHY 2.5G Mode for slice 0
#define CHIPID_ID_CFG_G2_5_DIS0_MASK 0x8u
//! Constant ENABLED - Enabled
#define CONST_CHIPID_ID_CFG_G2_5_DIS0_ENABLED 0x0
//! Constant DISABLED - Disable GPHY 2.5G support.
#define CONST_CHIPID_ID_CFG_G2_5_DIS0_DISABLED 0x1

//! Field G2_5_DIS1 - Disable GPHY 2.5G Mode for slice 1
#define CHIPID_ID_CFG_G2_5_DIS1_POS 4
//! Field G2_5_DIS1 - Disable GPHY 2.5G Mode for slice 1
#define CHIPID_ID_CFG_G2_5_DIS1_MASK 0x10u
//! Constant ENABLED - Enabled
#define CONST_CHIPID_ID_CFG_G2_5_DIS1_ENABLED 0x0
//! Constant DISABLED - Disable GPHY 2.5G support.
#define CONST_CHIPID_ID_CFG_G2_5_DIS1_DISABLED 0x1

//! Field G2_5_DIS2 - Disable GPHY 2.5G Mode for slice 2
#define CHIPID_ID_CFG_G2_5_DIS2_POS 5
//! Field G2_5_DIS2 - Disable GPHY 2.5G Mode for slice 2
#define CHIPID_ID_CFG_G2_5_DIS2_MASK 0x20u
//! Constant ENABLED - Enabled
#define CONST_CHIPID_ID_CFG_G2_5_DIS2_ENABLED 0x0
//! Constant DISABLED - Disable GPHY 2.5G support.
#define CONST_CHIPID_ID_CFG_G2_5_DIS2_DISABLED 0x1

//! Field G2_5_DIS3 - Disable GPHY 2.5G Mode for slice 3
#define CHIPID_ID_CFG_G2_5_DIS3_POS 6
//! Field G2_5_DIS3 - Disable GPHY 2.5G Mode for slice 3
#define CHIPID_ID_CFG_G2_5_DIS3_MASK 0x40u
//! Constant ENABLED - Enabled
#define CONST_CHIPID_ID_CFG_G2_5_DIS3_ENABLED 0x0
//! Constant DISABLED - Disable GPHY 2.5G support.
#define CONST_CHIPID_ID_CFG_G2_5_DIS3_DISABLED 0x1

//! Field SLICE_DIS1 - Disable slice 1
#define CHIPID_ID_CFG_SLICE_DIS1_POS 7
//! Field SLICE_DIS1 - Disable slice 1
#define CHIPID_ID_CFG_SLICE_DIS1_MASK 0x80u
//! Constant ENABLED - Enabled
#define CONST_CHIPID_ID_CFG_SLICE_DIS1_ENABLED 0x0
//! Constant DISABLED - Disable slice 1
#define CONST_CHIPID_ID_CFG_SLICE_DIS1_DISABLED 0x1

//! Field SLICE_DIS2 - Disable slice 2
#define CHIPID_ID_CFG_SLICE_DIS2_POS 8
//! Field SLICE_DIS2 - Disable slice 2
#define CHIPID_ID_CFG_SLICE_DIS2_MASK 0x100u
//! Constant ENABLED - Enabled
#define CONST_CHIPID_ID_CFG_SLICE_DIS2_ENABLED 0x0
//! Constant DISABLED - Disable slice 1
#define CONST_CHIPID_ID_CFG_SLICE_DIS2_DISABLED 0x1

//! Field SLICE_DIS3 - Disable slice 3
#define CHIPID_ID_CFG_SLICE_DIS3_POS 9
//! Field SLICE_DIS3 - Disable slice 3
#define CHIPID_ID_CFG_SLICE_DIS3_MASK 0x200u
//! Constant ENABLED - Enabled
#define CONST_CHIPID_ID_CFG_SLICE_DIS3_ENABLED 0x0
//! Constant DISABLED - Disable slice 1
#define CONST_CHIPID_ID_CFG_SLICE_DIS3_DISABLED 0x1

//! Field RES2 - Reserved
#define CHIPID_ID_CFG_RES2_POS 10
//! Field RES2 - Reserved
#define CHIPID_ID_CFG_RES2_MASK 0x400u
// For P31G
//! Field MACSEC_DIS - Disable MAC Sec
#define CHIPID_ID_CFG_MACSEC_DIS_POS 11
//! Field MACSEC_DIS - Disable MAC Sec
#define CHIPID_ID_CFG_MACSEC_DIS_MASK 0x800u
//! Constant ENABLE - MACsec feature is enabled
#define CONST_CHIPID_ID_CFG_MACSEC_DIS_ENABLE 0x0
//! Constant DISABLE - MACsec feature is disabled
#define CONST_CHIPID_ID_CFG_MACSEC_DIS_DISABLE 0x1
//For P34X
//! Field MACSEC_DIS0 - Disable MAC Sec for Slice 0
#define CHIPID_ID_CFG_MACSEC_DIS0_POS 11
//! Field MACSEC_DIS0 - Disable MAC Sec for Slice 0
#define CHIPID_ID_CFG_MACSEC_DIS0_MASK 0x800u
//! Constant ENABLE - MACsec feature is enabled
#define CONST_CHIPID_ID_CFG_MACSEC_DIS0_ENABLE 0x0
//! Constant DISABLE - MACsec feature is disabled
#define CONST_CHIPID_ID_CFG_MACSEC_DIS0_DISABLE 0x1

//! Field MACSEC_DIS1 - Disable MAC Sec for Slice 1
#define CHIPID_ID_CFG_MACSEC_DIS1_POS 12
//! Field MACSEC_DIS1 - Disable MAC Sec for Slice 1
#define CHIPID_ID_CFG_MACSEC_DIS1_MASK 0x1000u
//! Constant ENABLE - MACsec feature is enabled
#define CONST_CHIPID_ID_CFG_MACSEC_DIS1_ENABLE 0x0
//! Constant DISABLE - MACsec feature is disabled
#define CONST_CHIPID_ID_CFG_MACSEC_DIS1_DISABLE 0x1

//! Field MACSEC_DIS2 - Disable MAC Sec for Slice 2
#define CHIPID_ID_CFG_MACSEC_DIS2_POS 13
//! Field MACSEC_DIS2 - Disable MAC Sec for Slice 2
#define CHIPID_ID_CFG_MACSEC_DIS2_MASK 0x2000u
//! Constant ENABLE - MACsec feature is enabled
#define CONST_CHIPID_ID_CFG_MACSEC_DIS2_ENABLE 0x0
//! Constant DISABLE - MACsec feature is disabled
#define CONST_CHIPID_ID_CFG_MACSEC_DIS2_DISABLE 0x1

//! Field MACSEC_DIS3 - Disable MAC Sec for Slice 3
#define CHIPID_ID_CFG_MACSEC_DIS3_POS 14
//! Field MACSEC_DIS3 - Disable MAC Sec for Slice 3
#define CHIPID_ID_CFG_MACSEC_DIS3_MASK 0x4000u
//! Constant ENABLE - MACsec feature is enabled
#define CONST_CHIPID_ID_CFG_MACSEC_DIS3_ENABLE 0x0
//! Constant DISABLE - MACsec feature is disabled
#define CONST_CHIPID_ID_CFG_MACSEC_DIS3_DISABLE 0x1

//! Field RES4 - Reserved
#define CHIPID_ID_CFG_RES4_POS 15
//! Field RES4 - Reserved
#define CHIPID_ID_CFG_RES4_MASK 0x8000u

//! @}
// For P31G
//! \defgroup CHIPID_RM_RME_CTRL Register CHIPID_RM_RME_CTRL - RM/RME Fuse Control Register
//! @{

//! Register Offset (relative)
#define CHIPID_RM_RME_CTRL 0x48
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_RM_RME_CTRL 0x00D288C8u

//! Register Reset Value
#define CHIPID_RM_RME_CTRL_RST 0x00000000u

//! Field RM0 - Other FXVL Memories RM Control
#define CHIPID_RM_RME_CTRL_RM0_POS 0
//! Field RM0 - Other FXVL Memories RM Control
#define CHIPID_RM_RME_CTRL_RM0_MASK 0x3u

//! Field RME0 - Other FXVL Memories RME Control
#define CHIPID_RM_RME_CTRL_RME0_POS 2
//! Field RME0 - Other FXVL Memories RME Control
#define CHIPID_RM_RME_CTRL_RME0_MASK 0x4u

//! Field RM1 - Shared Buffer Memories RM Control
#define CHIPID_RM_RME_CTRL_RM1_POS 3
//! Field RM1 - Shared Buffer Memories RM Control
#define CHIPID_RM_RME_CTRL_RM1_MASK 0x18u

//! Field RME1 - Shared Buffer Memories RME Control
#define CHIPID_RM_RME_CTRL_RME1_POS 5
//! Field RME1 - Shared Buffer Memories RME Control
#define CHIPID_RM_RME_CTRL_RME1_MASK 0x20u

//! @}

// For P34X
//! \defgroup CHIPID_QRR_HIGH Register CHIPID_QRR_HIGH - QRR HIGH Register
//! @{

//! Register Offset (relative)
#define CHIPID_QRR_HIGH 0x48
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_QRR_HIGH 0x00D288C8u

//! Register Reset Value
#define CHIPID_QRR_HIGH_RST 0x00000000u

//! Field QRR_HIGH - High 16 bits of OTP QRR
#define CHIPID_QRR_HIGH_QRR_HIGH_POS 0
//! Field QRR_HIGH - High 16 bits of OTP QRR
#define CHIPID_QRR_HIGH_QRR_HIGH_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_MPS_FUSE_0 Register CHIPID_MPS_FUSE_0 - FUSE
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_FUSE_0 0x4C
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_FUSE_0 0x00D288CCu

//! Register Reset Value
#define CHIPID_MPS_FUSE_0_RST 0x00000000u

//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_0_FUSE_POS 0
//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_0_FUSE_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_MPS_FUSE_1 Register CHIPID_MPS_FUSE_1 - FUSE
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_FUSE_1 0x50
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_FUSE_1 0x00D288D0u

//! Register Reset Value
#define CHIPID_MPS_FUSE_1_RST 0x00000000u

//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_1_FUSE_POS 0
//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_1_FUSE_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_MPS_FUSE_2 Register CHIPID_MPS_FUSE_2 - FUSE
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_FUSE_2 0x54
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_FUSE_2 0x00D288D4u

//! Register Reset Value
#define CHIPID_MPS_FUSE_2_RST 0x00000000u

//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_2_FUSE_POS 0
//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_2_FUSE_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_MPS_FUSE_3 Register CHIPID_MPS_FUSE_3 - FUSE
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_FUSE_3 0x58
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_FUSE_3 0x00D288D8u

//! Register Reset Value
#define CHIPID_MPS_FUSE_3_RST 0x00000000u

//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_3_FUSE_POS 0
//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_3_FUSE_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_MPS_FUSE_4 Register CHIPID_MPS_FUSE_4 - FUSE
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_FUSE_4 0x5C
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_FUSE_4 0x00D288DCu

//! Register Reset Value
#define CHIPID_MPS_FUSE_4_RST 0x00000000u

//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_4_FUSE_POS 0
//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_4_FUSE_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_MPS_FUSE_5 Register CHIPID_MPS_FUSE_5 - FUSE
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_FUSE_5 0x60
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_FUSE_5 0x00D288E0u

//! Register Reset Value
#define CHIPID_MPS_FUSE_5_RST 0x00000000u

//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_5_FUSE_POS 0
//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_5_FUSE_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_MPS_FUSE_6 Register CHIPID_MPS_FUSE_6 - FUSE
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_FUSE_6 0x64
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_FUSE_6 0x00D288E4u

//! Register Reset Value
#define CHIPID_MPS_FUSE_6_RST 0x00000000u

//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_6_FUSE_POS 0
//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_6_FUSE_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_MPS_FUSE_7 Register CHIPID_MPS_FUSE_7 - FUSE
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_FUSE_7 0x68
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_FUSE_7 0x00D288E8u

//! Register Reset Value
#define CHIPID_MPS_FUSE_7_RST 0x00000000u

//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_7_FUSE_POS 0
//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_7_FUSE_MASK 0xFFFFu

//! @}

//! \defgroup CHIPID_MPS_FUSE_8 Register CHIPID_MPS_FUSE_8 - FUSE
//! @{

//! Register Offset (relative)
#define CHIPID_MPS_FUSE_8 0x6C
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_MPS_FUSE_8 0x00D288ECu

//! Register Reset Value
#define CHIPID_MPS_FUSE_8_RST 0x00000000u

//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_8_FUSE_POS 0
//! Field FUSE - FUSE
#define CHIPID_MPS_FUSE_8_FUSE_MASK 0xFFFFu

//! @}

//For P31G
//! \defgroup CHIPID_DCDC_TRIM Register CHIPID_DCDC_TRIM - DCDC Trimming Register
//! @{

//! Register Offset (relative)
#define CHIPID_DCDC_TRIM 0x70
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_DCDC_TRIM 0x00D288F0u

//! Register Reset Value
#define CHIPID_DCDC_TRIM_RST 0x00000000u

//! Field GAIN_CORR - Gain Correction
#define CHIPID_DCDC_TRIM_GAIN_CORR_POS 0
//! Field GAIN_CORR - Gain Correction
#define CHIPID_DCDC_TRIM_GAIN_CORR_MASK 0xFFu

//! Field OFFSET_CORR - Offset Correction
#define CHIPID_DCDC_TRIM_OFFSET_CORR_POS 8
//! Field OFFSET_CORR - Offset Correction
#define CHIPID_DCDC_TRIM_OFFSET_CORR_MASK 0xFF00u

//! @}

// For P34X
//! \defgroup CHIPID_RESERVED Register CHIPID_RESERVED - Reserved
//! @{

//! Register Offset (relative)
#define CHIPID_RESERVED 0x70
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_RESERVED 0x00D288F0u

//! Register Reset Value
#define CHIPID_RESERVED_RST 0x00000000u

//! Field GAIN_CORR - Gain Correction
#define CHIPID_RESERVED_GAIN_CORR_POS 0
//! Field GAIN_CORR - Gain Correction
#define CHIPID_RESERVED_GAIN_CORR_MASK 0xFFu

//! Field OFFSET_CORR - Offset Correction
#define CHIPID_RESERVED_OFFSET_CORR_POS 8
//! Field OFFSET_CORR - Offset Correction
#define CHIPID_RESERVED_OFFSET_CORR_MASK 0xFF00u

//! @}

//! \defgroup CHIPID_CTRL Register CHIPID_CTRL - Control Chip Fuse behaviours
//! @{

//! Register Offset (relative)
#define CHIPID_CTRL 0x74
//! Register Offset (absolute) for 1st Instance CHIPID
#define CHIPID_CHIPID_CTRL 0x00D288F4u

//! Register Reset Value
#define CHIPID_CTRL_RST 0x00000000u

//! Field JTAG_ID - JTAG ID
#define CHIPID_CTRL_JTAG_ID_POS 0
//! Field JTAG_ID - JTAG ID
#define CHIPID_CTRL_JTAG_ID_MASK 0x3u
//! Constant STANDALONE - P34X is a standalone chip
#define CONST_CHIPID_CTRL_JTAG_ID_STANDALONE 0x0
//! Constant MCM_LGM - MGM LGM Mode
#define CONST_CHIPID_CTRL_JTAG_ID_MCM_LGM 0x1
//! Constant MGM_OPT2 - MGM option 2
#define CONST_CHIPID_CTRL_JTAG_ID_MGM_OPT2 0x2
//! Constant MGM_OPT3 - MGM option 3
#define CONST_CHIPID_CTRL_JTAG_ID_MGM_OPT3 0x3

//! Field CHIP_LOCK - Locks the CHIPID register files in RO by firmware
#define CHIPID_CTRL_CHIP_LOCK_POS 3
//! Field CHIP_LOCK - Locks the CHIPID register files in RO by firmware
#define CHIPID_CTRL_CHIP_LOCK_MASK 0x8u
//! Constant UNLOCK - CHIPID registers can be written by firmware
#define CONST_CHIPID_CTRL_CHIP_LOCK_UNLOCK 0x0
//! Constant LOCK - CHIPID registers are read-only from firmware
#define CONST_CHIPID_CTRL_CHIP_LOCK_LOCK 0x1

//! Field QRR_FUSE_SEL - Selects the input of the CHIPID register load from OTP QRR
#define CHIPID_CTRL_QRR_FUSE_SEL_POS 4
//! Field QRR_FUSE_SEL - Selects the input of the CHIPID register load from OTP QRR
#define CHIPID_CTRL_QRR_FUSE_SEL_MASK 0x10u
//! Constant QRR - QRR CHIPID loaded from OTP QRR
#define CONST_CHIPID_CTRL_QRR_FUSE_SEL_QRR 0x0
//! Constant FW - QRR CHIPID write-able by FW
#define CONST_CHIPID_CTRL_QRR_FUSE_SEL_FW 0x1

//! @}

//! @}

#endif
