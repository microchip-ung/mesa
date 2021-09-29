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
// LSD Source          : /home/p31g/p31g_chip/v_hksim.priv.p31g_chip.top/ipg_lsd/lsd_sys/source_mdio/xml/reg_files/ethsw_flow25g_mii_pdi_def.xml
// Register File Name  : ETHSW_FLOW25G_MII_PDI
// Register File Title : xMII Control Registers
// Register Width      : 16
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _ETHSW_FLOW25G_MII_PDI_H
#define _ETHSW_FLOW25G_MII_PDI_H

//! \defgroup ETHSW_FLOW25G_MII_PDI Register File ETHSW_FLOW25G_MII_PDI - xMII Control Registers
//! @{

//! Base Address of ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_MODULE_BASE 0x0001E200u

//! \defgroup ETHSW_FLOW25G_MII_PDI_MII_CFG_5 Register ETHSW_FLOW25G_MII_PDI_MII_CFG_5 - xMII Port 5 Configuration Register
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5 0x0
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_MII_CFG_5 0x0001E200u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_RST 0x2044u

//! Field MIIMODE - xMII Interface Mode
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIMODE_POS 0
//! Field MIIMODE - xMII Interface Mode
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIMODE_MASK 0xFu
//! Constant MIIP - MII PHY mode, connected to external PHY
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIMODE_MIIP 0x0
//! Constant MIIM - MII MAC mode, connected to external PHY
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIMODE_MIIM 0x1
//! Constant RMIIM - RMII MAC mode, connected to external PHY
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIMODE_RMIIM 0x3
//! Constant RGMII - RGMII MAC mode, connected to external PHY
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIMODE_RGMII 0x4
//! Constant GMIIP - GMII PHY mode, connected to external PHY
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIMODE_GMIIP 0x8
//! Constant GMIIM - GMII MAC mode, connected to external PHY
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIMODE_GMIIM 0x9

//! Field MIIRATE - xMII Port Interface Clock Rate
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIRATE_POS 4
//! Field MIIRATE - xMII Port Interface Clock Rate
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIRATE_MASK 0x70u
//! Constant M2P5 - 2.5 MHz
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIRATE_M2P5 0x0
//! Constant M25 - 25 MHz
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIRATE_M25 0x1
//! Constant M125 - 125 MHz
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIRATE_M125 0x2
//! Constant M50 - 50 MHz
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIRATE_M50 0x3
//! Constant AUTO - Speed used from Autopolling
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIRATE_AUTO 0x4
//! Constant M62P5 - 500Mbps
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIRATE_M62P5 0x5
//! Constant M31P25 - 250Mbps
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_MIIRATE_M31P25 0x6

//! Field RMII - RMII Reference Clock Direction of the Port
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_RMII_POS 7
//! Field RMII - RMII Reference Clock Direction of the Port
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_RMII_MASK 0x80u
//! Constant IN - RMII clock is input
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_RMII_IN 0x0
//! Constant OUT - RMII clock is output
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_RMII_OUT 0x1

//! Field RGMII_IBS - RGMII In Band Status
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_RGMII_IBS_POS 8
//! Field RGMII_IBS - RGMII In Band Status
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_RGMII_IBS_MASK 0x100u
//! Constant OFF - RGMII In Band Status off
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_RGMII_IBS_OFF 0x0
//! Constant ON - RGMII In Band Satus on
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_RGMII_IBS_ON 0x1

//! Field CRS - CRS Sensitivity Configuration
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_CRS_POS 9
//! Field CRS - CRS Sensitivity Configuration
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_CRS_MASK 0x600u
//! Constant MODE1 - HDX:TX+RX, FDX:RX
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_CRS_MODE1 0x0
//! Constant MODE2 - HDX:TX+RX, FDX:0
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_CRS_MODE2 0x1
//! Constant MODE3 - HDX:RX, FDX:RX
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_CRS_MODE3 0x2
//! Constant MODE4 - HDX:RX, FDX:0
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_CRS_MODE4 0x3

//! Field LDCLKDIS - Link Down Clock Disable
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_LDCLKDIS_POS 12
//! Field LDCLKDIS - Link Down Clock Disable
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_LDCLKDIS_MASK 0x1000u
//! Constant OFF - No automatic disable in case of link down
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_LDCLKDIS_OFF 0x0
//! Constant ON - Disable clocks in case of link down and switch interface off
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_LDCLKDIS_ON 0x1

//! Field ISOL - ISOLATE xMII Interface
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_ISOL_POS 13
//! Field ISOL - ISOLATE xMII Interface
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_ISOL_MASK 0x2000u
//! Constant ENABLE - Interface active
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_ISOL_ENABLE 0x0
//! Constant ISOLATE - Interface outputs isolated
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_ISOL_ISOLATE 0x1

//! Field EN - xMII Interface Enable
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_EN_POS 14
//! Field EN - xMII Interface Enable
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_EN_MASK 0x4000u
//! Constant DIS - disable the interface
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_EN_DIS 0x0
//! Constant EN - enable the interface
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_EN_EN 0x1

//! Field RES - Hardware Reset
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_RES_POS 15
//! Field RES - Hardware Reset
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_5_RES_MASK 0x8000u
//! Constant OFF - reset is off
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_RES_OFF 0x0
//! Constant ON - reset is active
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_5_RES_ON 0x1

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_5 Register ETHSW_FLOW25G_MII_PDI_PCDU_5 - Configuration of Clock Delay for Port 5
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_5 0x2
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_5 0x0001E202u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_5_RST 0x0000u

//! Field TXDLY - Configure Transmit PCDU
#define ETHSW_FLOW25G_MII_PDI_PCDU_5_TXDLY_POS 0
//! Field TXDLY - Configure Transmit PCDU
#define ETHSW_FLOW25G_MII_PDI_PCDU_5_TXDLY_MASK 0x7u

//! Field RXDLY - Configure Receive Clock Delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_5_RXDLY_POS 7
//! Field RXDLY - Configure Receive Clock Delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_5_RXDLY_MASK 0x380u

//! Field DELMD - PCDU Delay Setting Mode
#define ETHSW_FLOW25G_MII_PDI_PCDU_5_DELMD_POS 10
//! Field DELMD - PCDU Delay Setting Mode
#define ETHSW_FLOW25G_MII_PDI_PCDU_5_DELMD_MASK 0x400u
//! Constant DELAY - use delay value
#define CONST_ETHSW_FLOW25G_MII_PDI_PCDU_5_DELMD_DELAY 0x0
//! Constant MK - use MK values
#define CONST_ETHSW_FLOW25G_MII_PDI_PCDU_5_DELMD_MK 0x1

//! Field TXLOCK - Lock Status of MDL of Transmit PCDU
#define ETHSW_FLOW25G_MII_PDI_PCDU_5_TXLOCK_POS 14
//! Field TXLOCK - Lock Status of MDL of Transmit PCDU
#define ETHSW_FLOW25G_MII_PDI_PCDU_5_TXLOCK_MASK 0x4000u
//! Constant UNLOCK - Transmit MDL is out of sync
#define CONST_ETHSW_FLOW25G_MII_PDI_PCDU_5_TXLOCK_UNLOCK 0x0
//! Constant LOCKED - Transmit MDL is LOCKED
#define CONST_ETHSW_FLOW25G_MII_PDI_PCDU_5_TXLOCK_LOCKED 0x1

//! Field RXLOCK - Lock Status MDL of Receive PCDU
#define ETHSW_FLOW25G_MII_PDI_PCDU_5_RXLOCK_POS 15
//! Field RXLOCK - Lock Status MDL of Receive PCDU
#define ETHSW_FLOW25G_MII_PDI_PCDU_5_RXLOCK_MASK 0x8000u
//! Constant UNLOCK - Receive MDL is out of sync
#define CONST_ETHSW_FLOW25G_MII_PDI_PCDU_5_RXLOCK_UNLOCK 0x0
//! Constant LOCKED - Receive MDL is LOCKED
#define CONST_ETHSW_FLOW25G_MII_PDI_PCDU_5_RXLOCK_LOCKED 0x1

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_MII_CFG_6 Register ETHSW_FLOW25G_MII_PDI_MII_CFG_6 - xMII Port 6 Configuration Register
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6 0x14
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_MII_CFG_6 0x0001E214u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_RST 0x2044u

//! Field MIIMODE - xMII Interface Mode
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIMODE_POS 0
//! Field MIIMODE - xMII Interface Mode
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIMODE_MASK 0xFu
//! Constant MIIM - MII MAC mode, connected to internal GPHY
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIMODE_MIIM 0x1
//! Constant RMIIM - RMII MAC mode, connected to external PHY
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIMODE_RMIIM 0x3
//! Constant RGMII - RGMII MAC mode, connected to external PHY
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIMODE_RGMII 0x4

//! Field MIIRATE - xMII Port Interface Clock Rate
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIRATE_POS 4
//! Field MIIRATE - xMII Port Interface Clock Rate
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIRATE_MASK 0x70u
//! Constant M2P5 - 2.5 MHz
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIRATE_M2P5 0x0
//! Constant M25 - 25 MHz
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIRATE_M25 0x1
//! Constant M125 - 125 MHz
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIRATE_M125 0x2
//! Constant M50 - 50 MHz
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIRATE_M50 0x3
//! Constant AUTO - Speed used from Autopolling
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIRATE_AUTO 0x4
//! Constant M62P5 - 500Mbps
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIRATE_M62P5 0x5
//! Constant M31P25 - 250Mbps
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_MIIRATE_M31P25 0x6

//! Field RMII - RMII Reference Clock Direction of the Port
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_RMII_POS 7
//! Field RMII - RMII Reference Clock Direction of the Port
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_RMII_MASK 0x80u
//! Constant IN - RMII clock is input
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_RMII_IN 0x0
//! Constant OUT - RMII clock is output
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_RMII_OUT 0x1

//! Field RGMII_IBS - RGMII In Band Status
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_RGMII_IBS_POS 8
//! Field RGMII_IBS - RGMII In Band Status
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_RGMII_IBS_MASK 0x100u
//! Constant OFF - RGMII In Band Status off
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_RGMII_IBS_OFF 0x0
//! Constant ON - RGMII In Band Satus on
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_RGMII_IBS_ON 0x1

//! Field CRS - CRS Sensitivity Configuration
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_CRS_POS 9
//! Field CRS - CRS Sensitivity Configuration
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_CRS_MASK 0x600u
//! Constant MODE1 - HDX:TX+RX, FDX:RX
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_CRS_MODE1 0x0
//! Constant MODE2 - HDX:TX+RX, FDX:0
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_CRS_MODE2 0x1
//! Constant MODE3 - HDX:RX, FDX:RX
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_CRS_MODE3 0x2
//! Constant MODE4 - HDX:RX, FDX:0
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_CRS_MODE4 0x3

//! Field LDCLKDIS - Link Down Clock Disable
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_LDCLKDIS_POS 12
//! Field LDCLKDIS - Link Down Clock Disable
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_LDCLKDIS_MASK 0x1000u
//! Constant OFF - No automatic disable in case of link down
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_LDCLKDIS_OFF 0x0
//! Constant ON - Disable clocks in case of link down and switch interface off
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_LDCLKDIS_ON 0x1

//! Field ISOL - ISOLATE xMII Interface
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_ISOL_POS 13
//! Field ISOL - ISOLATE xMII Interface
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_ISOL_MASK 0x2000u
//! Constant ENABLE - Interface active
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_ISOL_ENABLE 0x0
//! Constant ISOLATE - Interface outputs isolated
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_ISOL_ISOLATE 0x1

//! Field EN - xMII Interface Enable
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_EN_POS 14
//! Field EN - xMII Interface Enable
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_EN_MASK 0x4000u
//! Constant DIS - disable the interface
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_EN_DIS 0x0
//! Constant EN - enable the interface
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_EN_EN 0x1

//! Field RES - Hardware Reset
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_RES_POS 15
//! Field RES - Hardware Reset
#define ETHSW_FLOW25G_MII_PDI_MII_CFG_6_RES_MASK 0x8000u
//! Constant OFF - reset is off
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_RES_OFF 0x0
//! Constant ON - reset is active
#define CONST_ETHSW_FLOW25G_MII_PDI_MII_CFG_6_RES_ON 0x1

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_6 Register ETHSW_FLOW25G_MII_PDI_PCDU_6 - Configuration of Clock Delay for External Port 1
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_6 0x16
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_6 0x0001E216u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_6_RST 0x0000u

//! Field TXDLY - Configure Transmit PCDU
#define ETHSW_FLOW25G_MII_PDI_PCDU_6_TXDLY_POS 0
//! Field TXDLY - Configure Transmit PCDU
#define ETHSW_FLOW25G_MII_PDI_PCDU_6_TXDLY_MASK 0x7u

//! Field RXDLY - Configure Receive Clock Delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_6_RXDLY_POS 7
//! Field RXDLY - Configure Receive Clock Delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_6_RXDLY_MASK 0x380u

//! Field DELMD - PCDU Delay Setting Mode
#define ETHSW_FLOW25G_MII_PDI_PCDU_6_DELMD_POS 10
//! Field DELMD - PCDU Delay Setting Mode
#define ETHSW_FLOW25G_MII_PDI_PCDU_6_DELMD_MASK 0x400u
//! Constant DELAY - use delay value
#define CONST_ETHSW_FLOW25G_MII_PDI_PCDU_6_DELMD_DELAY 0x0
//! Constant MK - use MK values
#define CONST_ETHSW_FLOW25G_MII_PDI_PCDU_6_DELMD_MK 0x1

//! Field TXLOCK - Lock Status of MDL of Transmit PCDU
#define ETHSW_FLOW25G_MII_PDI_PCDU_6_TXLOCK_POS 14
//! Field TXLOCK - Lock Status of MDL of Transmit PCDU
#define ETHSW_FLOW25G_MII_PDI_PCDU_6_TXLOCK_MASK 0x4000u
//! Constant UNLOCK - Transmit MDL is out of sync
#define CONST_ETHSW_FLOW25G_MII_PDI_PCDU_6_TXLOCK_UNLOCK 0x0
//! Constant LOCKED - Transmit MDL is LOCKED
#define CONST_ETHSW_FLOW25G_MII_PDI_PCDU_6_TXLOCK_LOCKED 0x1

//! Field RXLOCK - Lock Status MDL of Receive PCDU
#define ETHSW_FLOW25G_MII_PDI_PCDU_6_RXLOCK_POS 15
//! Field RXLOCK - Lock Status MDL of Receive PCDU
#define ETHSW_FLOW25G_MII_PDI_PCDU_6_RXLOCK_MASK 0x8000u
//! Constant UNLOCK - Receive MDL is out of sync
#define CONST_ETHSW_FLOW25G_MII_PDI_PCDU_6_RXLOCK_UNLOCK 0x0
//! Constant LOCKED - Receive MDL is LOCKED
#define CONST_ETHSW_FLOW25G_MII_PDI_PCDU_6_RXLOCK_LOCKED 0x1

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_RXB_CTL_5 Register ETHSW_FLOW25G_MII_PDI_RXB_CTL_5 - Receive Buffer Control Register for Port 5
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5 0x40
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_RXB_CTL_5 0x0001E240u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_RST 0x0009u

//! Field RBUF_DLY_WP - Delay
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_RBUF_DLY_WP_POS 0
//! Field RBUF_DLY_WP - Delay
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_RBUF_DLY_WP_MASK 0x7u

//! Field TBUF_DLY_WP - Delay
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_TBUF_DLY_WP_POS 3
//! Field TBUF_DLY_WP - Delay
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_TBUF_DLY_WP_MASK 0x38u

//! Field TBUF_OFL - Transmit Buffer Overflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_TBUF_OFL_POS 12
//! Field TBUF_OFL - Transmit Buffer Overflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_TBUF_OFL_MASK 0x1000u
//! Constant NONE - Overflow never detected
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_TBUF_OFL_NONE 0x0
//! Constant OFL - Overflow occurred at least once
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_TBUF_OFL_OFL 0x1

//! Field TBUF_UFL - Transmit Buffer Underflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_TBUF_UFL_POS 13
//! Field TBUF_UFL - Transmit Buffer Underflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_TBUF_UFL_MASK 0x2000u
//! Constant NONE - Underflow never detected
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_TBUF_UFL_NONE 0x0
//! Constant UFL - Underflow occurred at least once
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_TBUF_UFL_UFL 0x1

//! Field RBUF_OFL - Receive Buffer Overflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_RBUF_OFL_POS 14
//! Field RBUF_OFL - Receive Buffer Overflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_RBUF_OFL_MASK 0x4000u
//! Constant NONE - Overflow never detected
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_RBUF_OFL_NONE 0x0
//! Constant OFL - Overflow occurred at least once
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_RBUF_OFL_OFL 0x1

//! Field RBUF_UFL - Receive Buffer Underflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_RBUF_UFL_POS 15
//! Field RBUF_UFL - Receive Buffer Underflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_RBUF_UFL_MASK 0x8000u
//! Constant NONE - Underflow never detected
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_RBUF_UFL_NONE 0x0
//! Constant UFL - Underflow occurred at least once
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_5_RBUF_UFL_UFL 0x1

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_RXB_CTL_6 Register ETHSW_FLOW25G_MII_PDI_RXB_CTL_6 - Receive Buffer Control Register External Port 6
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6 0x4A
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_RXB_CTL_6 0x0001E24Au

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_RST 0x0009u

//! Field RBUF_DLY_WP - Delay
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_RBUF_DLY_WP_POS 0
//! Field RBUF_DLY_WP - Delay
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_RBUF_DLY_WP_MASK 0x7u

//! Field TBUF_DLY_WP - Delay
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_TBUF_DLY_WP_POS 3
//! Field TBUF_DLY_WP - Delay
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_TBUF_DLY_WP_MASK 0x38u

//! Field TBUF_OFL - Transmit Buffer Overflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_TBUF_OFL_POS 12
//! Field TBUF_OFL - Transmit Buffer Overflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_TBUF_OFL_MASK 0x1000u
//! Constant NONE - Overflow never detected
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_TBUF_OFL_NONE 0x0
//! Constant OFL - Overflow occurred at least once
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_TBUF_OFL_OFL 0x1

//! Field TBUF_UFL - Transmit Buffer Underflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_TBUF_UFL_POS 13
//! Field TBUF_UFL - Transmit Buffer Underflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_TBUF_UFL_MASK 0x2000u
//! Constant NONE - Underflow never detected
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_TBUF_UFL_NONE 0x0
//! Constant UFL - Underflow occurred at least once
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_TBUF_UFL_UFL 0x1

//! Field RBUF_OFL - Receive Buffer Overflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_RBUF_OFL_POS 14
//! Field RBUF_OFL - Receive Buffer Overflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_RBUF_OFL_MASK 0x4000u
//! Constant NONE - Overflow never detected
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_RBUF_OFL_NONE 0x0
//! Constant OFL - Overflow occurred at least once
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_RBUF_OFL_OFL 0x1

//! Field RBUF_UFL - Receive Buffer Underflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_RBUF_UFL_POS 15
//! Field RBUF_UFL - Receive Buffer Underflow Indicator
#define ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_RBUF_UFL_MASK 0x8000u
//! Constant NONE - Underflow never detected
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_RBUF_UFL_NONE 0x0
//! Constant UFL - Underflow occurred at least once
#define CONST_ETHSW_FLOW25G_MII_PDI_RXB_CTL_6_RBUF_UFL_UFL 0x1

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG Register ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG - Pin and Port Multiplexing Configuration
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG 0x60
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG 0x0001E260u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG_RST 0x0100u

//! Field GPHY0_ISO - GPHY0 Isolation Mode
#define ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG_GPHY0_ISO_POS 0
//! Field GPHY0_ISO - GPHY0 Isolation Mode
#define ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG_GPHY0_ISO_MASK 0x1u
//! Constant DIS - Isolation mode is disabled
#define CONST_ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG_GPHY0_ISO_DIS 0x0
//! Constant EN - Isolation mode is enabled
#define CONST_ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG_GPHY0_ISO_EN 0x1

//! Field CLKMD - Clock Mode for GMII with Internal GPHY
#define ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG_CLKMD_POS 8
//! Field CLKMD - Clock Mode for GMII with Internal GPHY
#define ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG_CLKMD_MASK 0x100u
//! Constant STD - GPHY is not in FRE mode
#define CONST_ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG_CLKMD_STD 0x0
//! Constant STB - The GMII clock is derived from strobe
#define CONST_ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG_CLKMD_STB 0x1

//! Field PIE - Packet Insertion and Extraction Mode
#define ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG_PIE_POS 9
//! Field PIE - Packet Insertion and Extraction Mode
#define ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG_PIE_MASK 0x200u
//! Constant DIS - Debug Mode disabled
#define CONST_ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG_PIE_DIS 0x0
//! Constant EN - Debug Mode enabled
#define CONST_ETHSW_FLOW25G_MII_PDI_XMII_MUX_CFG_PIE_EN 0x1

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PKT_INS Register ETHSW_FLOW25G_MII_PDI_PKT_INS - Packet Insertion Register
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PKT_INS 0x80
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PKT_INS 0x0001E280u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PKT_INS_RST 0x0000u

//! Field RXD - Rx data
#define ETHSW_FLOW25G_MII_PDI_PKT_INS_RXD_POS 0
//! Field RXD - Rx data
#define ETHSW_FLOW25G_MII_PDI_PKT_INS_RXD_MASK 0xFFu

//! Field RXVD - RX Valid
#define ETHSW_FLOW25G_MII_PDI_PKT_INS_RXVD_POS 8
//! Field RXVD - RX Valid
#define ETHSW_FLOW25G_MII_PDI_PKT_INS_RXVD_MASK 0x100u
//! Constant GAP - The data byte is not valid. Writing IPG
#define CONST_ETHSW_FLOW25G_MII_PDI_PKT_INS_RXVD_GAP 0x0
//! Constant VLD - The data byte is valid. Wring Preamble, SFD and packe
#define CONST_ETHSW_FLOW25G_MII_PDI_PKT_INS_RXVD_VLD 0x1

//! Field INSCMD - Packet Insertion Command
#define ETHSW_FLOW25G_MII_PDI_PKT_INS_INSCMD_POS 15
//! Field INSCMD - Packet Insertion Command
#define ETHSW_FLOW25G_MII_PDI_PKT_INS_INSCMD_MASK 0x8000u
//! Constant NIL - Packet insertion is not triggered
#define CONST_ETHSW_FLOW25G_MII_PDI_PKT_INS_INSCMD_NIL 0x0
//! Constant CMD - Go
#define CONST_ETHSW_FLOW25G_MII_PDI_PKT_INS_INSCMD_CMD 0x1

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ Register ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ - Packet Extraction Read Register
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ 0x82
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ 0x0001E282u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ_RST 0x0000u

//! Field TXD - Tx data
#define ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ_TXD_POS 0
//! Field TXD - Tx data
#define ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ_TXD_MASK 0xFFu

//! Field TXEN - TX Data Valid
#define ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ_TXEN_POS 8
//! Field TXEN - TX Data Valid
#define ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ_TXEN_MASK 0x100u
//! Constant NIL - The extracted byte is not vallid
#define CONST_ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ_TXEN_NIL 0x0
//! Constant EN - valid
#define CONST_ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ_TXEN_EN 0x1

//! Field AVAIL - Packet Available
#define ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ_AVAIL_POS 15
//! Field AVAIL - Packet Available
#define ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ_AVAIL_MASK 0x8000u
//! Constant NAVL - Packet is not available to be available.
#define CONST_ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ_AVAIL_NAVL 0x0
//! Constant AVL - Packet is available to be available
#define CONST_ETHSW_FLOW25G_MII_PDI_PKT_EXT_READ_AVAIL_AVL 0x1

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PKT_EXT_CMD Register ETHSW_FLOW25G_MII_PDI_PKT_EXT_CMD - Packet Extraction Flush Command
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PKT_EXT_CMD 0x84
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PKT_EXT_CMD 0x0001E284u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PKT_EXT_CMD_RST 0x0000u

//! Field FLUSH - Packet Extraction Flush Command
#define ETHSW_FLOW25G_MII_PDI_PKT_EXT_CMD_FLUSH_POS 0
//! Field FLUSH - Packet Extraction Flush Command
#define ETHSW_FLOW25G_MII_PDI_PKT_EXT_CMD_FLUSH_MASK 0x1u
//! Constant NIL - The flush command is not triggered
#define CONST_ETHSW_FLOW25G_MII_PDI_PKT_EXT_CMD_FLUSH_NIL 0x0
//! Constant CMD - The flush command in progress
#define CONST_ETHSW_FLOW25G_MII_PDI_PKT_EXT_CMD_FLUSH_CMD 0x1

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_KVAL Register ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_KVAL - Egress PCDU K Value
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_KVAL 0xC0
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_KVAL 0x0001E2C0u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_KVAL_RST 0x0040u

//! Field K_VAL - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_KVAL_K_VAL_POS 0
//! Field K_VAL - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_KVAL_K_VAL_MASK 0xFFFFu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MREQ Register ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MREQ - Egress PCDU M Required
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MREQ 0xC2
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MREQ 0x0001E2C2u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MREQ_RST 0x0000u

//! Field M_REQ - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MREQ_M_REQ_POS 0
//! Field M_REQ - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MREQ_M_REQ_MASK 0xFFFFu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MBLK Register ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MBLK - Egress PCDU M Blank
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MBLK 0xC4
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MBLK 0x0001E2C4u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MBLK_RST 0x0002u

//! Field M_BLK - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MBLK_M_BLK_POS 0
//! Field M_BLK - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_MBLK_M_BLK_MASK 0xFFFFu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_DELLEN Register ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_DELLEN - Egress PCDU Delay Length
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_DELLEN 0xC6
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_DELLEN 0x0001E2C6u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_DELLEN_RST 0x0000u

//! Field DEL_LEN - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_DELLEN_DEL_LEN_POS 0
//! Field DEL_LEN - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_EG_DELLEN_DEL_LEN_MASK 0x3Fu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_KVAL Register ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_KVAL - Igress PCDU K Value
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_KVAL 0xD0
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_KVAL 0x0001E2D0u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_KVAL_RST 0x0040u

//! Field K_VAL - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_KVAL_K_VAL_POS 0
//! Field K_VAL - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_KVAL_K_VAL_MASK 0xFFFFu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MREQ Register ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MREQ - Igress PCDU M Required
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MREQ 0xD2
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MREQ 0x0001E2D2u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MREQ_RST 0x0000u

//! Field M_REQ - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MREQ_M_REQ_POS 0
//! Field M_REQ - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MREQ_M_REQ_MASK 0xFFFFu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MBLK Register ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MBLK - Egress PCDU M Blank
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MBLK 0xD4
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MBLK 0x0001E2D4u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MBLK_RST 0x0002u

//! Field M_BLK - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MBLK_M_BLK_POS 0
//! Field M_BLK - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_MBLK_M_BLK_MASK 0xFFFFu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_DELLEN Register ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_DELLEN - Igress PCDU Delay Length
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_DELLEN 0xD6
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_DELLEN 0x0001E2D6u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_DELLEN_RST 0x0000u

//! Field DEL_LEN - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_DELLEN_DEL_LEN_POS 0
//! Field DEL_LEN - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_0_IG_DELLEN_DEL_LEN_MASK 0x3Fu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_KVAL Register ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_KVAL - Egress K Value for Port 1
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_KVAL 0xE0
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_KVAL 0x0001E2E0u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_KVAL_RST 0x0040u

//! Field K_VAL - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_KVAL_K_VAL_POS 0
//! Field K_VAL - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_KVAL_K_VAL_MASK 0xFFFFu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MREQ Register ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MREQ - Egress M Required for Port 1
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MREQ 0xE2
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MREQ 0x0001E2E2u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MREQ_RST 0x0000u

//! Field M_REQ - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MREQ_M_REQ_POS 0
//! Field M_REQ - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MREQ_M_REQ_MASK 0xFFFFu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MBLK Register ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MBLK - Egress M Blank for Port 1
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MBLK 0xE4
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MBLK 0x0001E2E4u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MBLK_RST 0x0002u

//! Field M_BLK - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MBLK_M_BLK_POS 0
//! Field M_BLK - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_MBLK_M_BLK_MASK 0xFFFFu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_DELLEN Register ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_DELLEN - Egress Delay lenght for Port 1
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_DELLEN 0xE6
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_DELLEN 0x0001E2E6u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_DELLEN_RST 0x0000u

//! Field DEL_LEN - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_DELLEN_DEL_LEN_POS 0
//! Field DEL_LEN - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_EG_DELLEN_DEL_LEN_MASK 0x3Fu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_KVAL Register ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_KVAL - Igress K Value for Port 1
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_KVAL 0xF0
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_KVAL 0x0001E2F0u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_KVAL_RST 0x0040u

//! Field K_VAL - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_KVAL_K_VAL_POS 0
//! Field K_VAL - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_KVAL_K_VAL_MASK 0xFFFFu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MREQ Register ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MREQ - Igress M Required for Port 1
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MREQ 0xF2
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MREQ 0x0001E2F2u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MREQ_RST 0x0000u

//! Field M_REQ - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MREQ_M_REQ_POS 0
//! Field M_REQ - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MREQ_M_REQ_MASK 0xFFFFu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MBLK Register ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MBLK - Igress M Blank for Port 1
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MBLK 0xF4
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MBLK 0x0001E2F4u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MBLK_RST 0x0002u

//! Field M_BLK - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MBLK_M_BLK_POS 0
//! Field M_BLK - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_MBLK_M_BLK_MASK 0xFFFFu

//! @}

//! \defgroup ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_DELLEN Register ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_DELLEN - Igress Delay lenght for Port 1
//! @{

//! Register Offset (relative)
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_DELLEN 0xF6
//! Register Offset (absolute) for 1st Instance ETHSW_FLOW25G_MII_PDI
#define ETHSW_FLOW25G_MII_PDI_ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_DELLEN 0x0001E2F6u

//! Register Reset Value
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_DELLEN_RST 0x0000u

//! Field DEL_LEN - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_DELLEN_DEL_LEN_POS 0
//! Field DEL_LEN - delay
#define ETHSW_FLOW25G_MII_PDI_PCDU_1_IG_DELLEN_DEL_LEN_MASK 0x3Fu

//! @}

//! @}

#endif
