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
// LSD Source          : /home/p31g/p31g_ip/v_reddydev.priv.p31g_ip.vp_model/ipg_lsd/lsd_sys/source_mdio/xml/reg_files/vspec2_def.xml
// Register File Name  : VSPEC2
// Register File Title : Vendor Specific 2 Device for MMD=0x1F
// Register Width      : 16
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _VSPEC2_H
#define _VSPEC2_H

//! \defgroup VSPEC2 Register File VSPEC2 - Vendor Specific 2 Device for MMD=0x1F
//! @{

//! Base Address of VSPEC2
#define VSPEC2_MODULE_BASE 0x03E00000u

//! \defgroup VPSPEC2_WOL_CTL Register VPSPEC2_WOL_CTL - Wake-on-LAN Control Register (Register 31.3590)
//! @{

//! Register Offset (relative)
#define VPSPEC2_WOL_CTL 0x1C0C
//! Register Offset (absolute) for 1st Instance VSPEC2
#define VSPEC2_VPSPEC2_WOL_CTL 0x03E01C0Cu

//! Register Reset Value
#define VPSPEC2_WOL_CTL_RST 0x0000u

//! Field EN - Enables the Wake-on-LAN functionality
#define VPSPEC2_WOL_CTL_EN_POS 0
//! Field EN - Enables the Wake-on-LAN functionality
#define VPSPEC2_WOL_CTL_EN_MASK 0x1u
//! Constant DISABLED - Wake-on-LAN functionality is disabled
#define CONST_VPSPEC2_WOL_CTL_EN_DISABLED 0x0
//! Constant ENABLED - Wake-on-LAN functionality is enabled
#define CONST_VPSPEC2_WOL_CTL_EN_ENABLED 0x1

//! Field RES - Reserved
#define VPSPEC2_WOL_CTL_RES_POS 1
//! Field RES - Reserved
#define VPSPEC2_WOL_CTL_RES_MASK 0x2u

//! Field SPWD_EN - Secure-ON Password Enable
#define VPSPEC2_WOL_CTL_SPWD_EN_POS 2
//! Field SPWD_EN - Secure-ON Password Enable
#define VPSPEC2_WOL_CTL_SPWD_EN_MASK 0x4u
//! Constant DISABLED - Secure-On password check is disabled
#define CONST_VPSPEC2_WOL_CTL_SPWD_EN_DISABLED 0x0
//! Constant ENABLED - Secure-On password check is enabled
#define CONST_VPSPEC2_WOL_CTL_SPWD_EN_ENABLED 0x1

//! @}

//! \defgroup VPSPEC2_WOL_AD01 Register VPSPEC2_WOL_AD01 - Wake-On-LAN Address Byte 0 and 1 (Register 31.3592)
//! @{

//! Register Offset (relative)
#define VPSPEC2_WOL_AD01 0x1C10
//! Register Offset (absolute) for 1st Instance VSPEC2
#define VSPEC2_VPSPEC2_WOL_AD01 0x03E01C10u

//! Register Reset Value
#define VPSPEC2_WOL_AD01_RST 0x0000u

//! Field AD0 - Address Byte 0
#define VPSPEC2_WOL_AD01_AD0_POS 0
//! Field AD0 - Address Byte 0
#define VPSPEC2_WOL_AD01_AD0_MASK 0xFFu

//! Field AD1 - Address Byte 1
#define VPSPEC2_WOL_AD01_AD1_POS 8
//! Field AD1 - Address Byte 1
#define VPSPEC2_WOL_AD01_AD1_MASK 0xFF00u

//! @}

//! \defgroup VPSPEC2_WOL_AD23 Register VPSPEC2_WOL_AD23 - Wake-on-LAN Address Byte 2 and 3 (Register 31.3593)
//! @{

//! Register Offset (relative)
#define VPSPEC2_WOL_AD23 0x1C12
//! Register Offset (absolute) for 1st Instance VSPEC2
#define VSPEC2_VPSPEC2_WOL_AD23 0x03E01C12u

//! Register Reset Value
#define VPSPEC2_WOL_AD23_RST 0x0000u

//! Field AD2 - Address Byte 2
#define VPSPEC2_WOL_AD23_AD2_POS 0
//! Field AD2 - Address Byte 2
#define VPSPEC2_WOL_AD23_AD2_MASK 0xFFu

//! Field AD3 - Address Byte 3
#define VPSPEC2_WOL_AD23_AD3_POS 8
//! Field AD3 - Address Byte 3
#define VPSPEC2_WOL_AD23_AD3_MASK 0xFF00u

//! @}

//! \defgroup VPSPEC2_WOL_AD45 Register VPSPEC2_WOL_AD45 - Wake-On-LAN Address Byte 4 and 5 (Register 31.3594)
//! @{

//! Register Offset (relative)
#define VPSPEC2_WOL_AD45 0x1C14
//! Register Offset (absolute) for 1st Instance VSPEC2
#define VSPEC2_VPSPEC2_WOL_AD45 0x03E01C14u

//! Register Reset Value
#define VPSPEC2_WOL_AD45_RST 0x0000u

//! Field AD4 - Address Byte 4
#define VPSPEC2_WOL_AD45_AD4_POS 0
//! Field AD4 - Address Byte 4
#define VPSPEC2_WOL_AD45_AD4_MASK 0xFFu

//! Field AD5 - Address Byte 5
#define VPSPEC2_WOL_AD45_AD5_POS 8
//! Field AD5 - Address Byte 5
#define VPSPEC2_WOL_AD45_AD5_MASK 0xFF00u

//! @}

//! \defgroup VPSPEC2_WOL_PW01 Register VPSPEC2_WOL_PW01 - Wake-On-LAN SecureON Password Byte 0 (Register 31.3595)
//! @{

//! Register Offset (relative)
#define VPSPEC2_WOL_PW01 0x1C16
//! Register Offset (absolute) for 1st Instance VSPEC2
#define VSPEC2_VPSPEC2_WOL_PW01 0x03E01C16u

//! Register Reset Value
#define VPSPEC2_WOL_PW01_RST 0x0000u

//! Field PW0 - SecureON Password Byte 0
#define VPSPEC2_WOL_PW01_PW0_POS 0
//! Field PW0 - SecureON Password Byte 0
#define VPSPEC2_WOL_PW01_PW0_MASK 0xFFu

//! Field PW1 - SecureON Password Byte 1
#define VPSPEC2_WOL_PW01_PW1_POS 8
//! Field PW1 - SecureON Password Byte 1
#define VPSPEC2_WOL_PW01_PW1_MASK 0xFF00u

//! @}

//! \defgroup VPSPEC2_WOL_PW23 Register VPSPEC2_WOL_PW23 - Wake-on-LAN SecureON Password Byte 2 and 3 (Register 31.3596)
//! @{

//! Register Offset (relative)
#define VPSPEC2_WOL_PW23 0x1C18
//! Register Offset (absolute) for 1st Instance VSPEC2
#define VSPEC2_VPSPEC2_WOL_PW23 0x03E01C18u

//! Register Reset Value
#define VPSPEC2_WOL_PW23_RST 0x0000u

//! Field PW2 - SecureON Password Byte 2
#define VPSPEC2_WOL_PW23_PW2_POS 0
//! Field PW2 - SecureON Password Byte 2
#define VPSPEC2_WOL_PW23_PW2_MASK 0xFFu

//! Field PW3 - SecureON Password Byte 3
#define VPSPEC2_WOL_PW23_PW3_POS 8
//! Field PW3 - SecureON Password Byte 3
#define VPSPEC2_WOL_PW23_PW3_MASK 0xFF00u

//! @}

//! \defgroup VPSPEC2_WOL_PW45 Register VPSPEC2_WOL_PW45 - Wake-on-LAN SecureON Password Byte 4 and 5 (Register 31.3597)
//! @{

//! Register Offset (relative)
#define VPSPEC2_WOL_PW45 0x1C1A
//! Register Offset (absolute) for 1st Instance VSPEC2
#define VSPEC2_VPSPEC2_WOL_PW45 0x03E01C1Au

//! Register Reset Value
#define VPSPEC2_WOL_PW45_RST 0x0000u

//! Field PW4 - SecureON Password Byte 4
#define VPSPEC2_WOL_PW45_PW4_POS 0
//! Field PW4 - SecureON Password Byte 4
#define VPSPEC2_WOL_PW45_PW4_MASK 0xFFu

//! Field PW5 - SecureON Password Byte 5
#define VPSPEC2_WOL_PW45_PW5_POS 8
//! Field PW5 - SecureON Password Byte 5
#define VPSPEC2_WOL_PW45_PW5_MASK 0xFF00u

//! @}

//! \defgroup VSPEC2_TGU_PDI_TGU_CTL Register VSPEC2_TGU_PDI_TGU_CTL - TGU Control. (Register 31.3984)
//! @{

//! Register Offset (relative)
#define VSPEC2_TGU_PDI_TGU_CTL 0x1F20
//! Register Offset (absolute) for 1st Instance VSPEC2
#define VSPEC2_VSPEC2_TGU_PDI_TGU_CTL 0x03E01F20u

//! Register Reset Value
#define VSPEC2_TGU_PDI_TGU_CTL_RST 0x0000u

//! Field EN - TGU Enable
#define VSPEC2_TGU_PDI_TGU_CTL_EN_POS 0
//! Field EN - TGU Enable
#define VSPEC2_TGU_PDI_TGU_CTL_EN_MASK 0x1u
//! Constant DIS - Disable
#define CONST_VSPEC2_TGU_PDI_TGU_CTL_EN_DIS 0x0
//! Constant EN - Enable
#define CONST_VSPEC2_TGU_PDI_TGU_CTL_EN_EN 0x1

//! Field INIT - TGU Init
#define VSPEC2_TGU_PDI_TGU_CTL_INIT_POS 1
//! Field INIT - TGU Init
#define VSPEC2_TGU_PDI_TGU_CTL_INIT_MASK 0x2u

//! Field LFUPD - LF UPDATE Mode
#define VSPEC2_TGU_PDI_TGU_CTL_LFUPD_POS 2
//! Field LFUPD - LF UPDATE Mode
#define VSPEC2_TGU_PDI_TGU_CTL_LFUPD_MASK 0x4u
//! Constant ENBAUD - Update LF at every baud
#define CONST_VSPEC2_TGU_PDI_TGU_CTL_LFUPD_ENBAUD 0x0
//! Constant EN125U - Update LF at every 125us when TERR is available
#define CONST_VSPEC2_TGU_PDI_TGU_CTL_LFUPD_EN125U 0x1

//! Field TXRX - Selects TX Baud or RX Baud for PD
#define VSPEC2_TGU_PDI_TGU_CTL_TXRX_POS 3
//! Field TXRX - Selects TX Baud or RX Baud for PD
#define VSPEC2_TGU_PDI_TGU_CTL_TXRX_MASK 0x8u
//! Constant TX - Tx Baud Selected
#define CONST_VSPEC2_TGU_PDI_TGU_CTL_TXRX_TX 0x0
//! Constant RX - Rx Baud Selected
#define CONST_VSPEC2_TGU_PDI_TGU_CTL_TXRX_RX 0x1

//! Field TST - Reserved
#define VSPEC2_TGU_PDI_TGU_CTL_TST_POS 4
//! Field TST - Reserved
#define VSPEC2_TGU_PDI_TGU_CTL_TST_MASK 0x10u

//! Field LB - REF_CLK_O loopback as REF_CLK_I
#define VSPEC2_TGU_PDI_TGU_CTL_LB_POS 5
//! Field LB - REF_CLK_O loopback as REF_CLK_I
#define VSPEC2_TGU_PDI_TGU_CTL_LB_MASK 0x20u
//! Constant DISABLE - REF_CLK_I must come from GPHY IP interface
#define CONST_VSPEC2_TGU_PDI_TGU_CTL_LB_DISABLE 0x0
//! Constant ENABLE - REF_CLK_O is loopback as REF_CLK_I
#define CONST_VSPEC2_TGU_PDI_TGU_CTL_LB_ENABLE 0x1

//! Field EXT - Extend Clk selection
#define VSPEC2_TGU_PDI_TGU_CTL_EXT_POS 6
//! Field EXT - Extend Clk selection
#define VSPEC2_TGU_PDI_TGU_CTL_EXT_MASK 0xC0u
//! Constant REF25M - Reference 25MHz Clock
#define CONST_VSPEC2_TGU_PDI_TGU_CTL_EXT_REF25M 0x0
//! Constant REF40M - Reference 40MHz Clock
#define CONST_VSPEC2_TGU_PDI_TGU_CTL_EXT_REF40M 0x1
//! Constant PD_DIVSEL2 - Taken from TGU_PDI_PD_DIV
#define CONST_VSPEC2_TGU_PDI_TGU_CTL_EXT_PD_DIVSEL2 0x2
//! Constant PD_DIVSEL3 - Taken from TGU_PDI_PD_DIV
#define CONST_VSPEC2_TGU_PDI_TGU_CTL_EXT_PD_DIVSEL3 0x3

//! @}

//! @}

#endif
