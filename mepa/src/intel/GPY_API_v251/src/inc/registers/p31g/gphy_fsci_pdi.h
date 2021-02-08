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
// LSD Source          : /home/p31g/p31g_chip/v_hksim.priv.p31g_chip.top/ipg_lsd/lsd_sys/source_mdio/xml/reg_files/gphy_fsci_pdi_def.xml
// Register File Name  : GPHY_FSCI_PDI
// Register File Title : FSCI interface Control
// Register Width      : 16
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _GPHY_FSCI_PDI_H
#define _GPHY_FSCI_PDI_H

//! \defgroup GPHY_FSCI_PDI Register File GPHY_FSCI_PDI - FSCI interface Control
//! @{

//! Base Address of GPHY_FSCI_PDI
#define GPHY_FSCI_PDI_MODULE_BASE 0x0001F000u

//! \defgroup GPHY_FSCI_PDI_CTRL Register GPHY_FSCI_PDI_CTRL - FSCI Control
//! @{

//! Register Offset (relative)
#define GPHY_FSCI_PDI_CTRL 0x0
//! Register Offset (absolute) for 1st Instance GPHY_FSCI_PDI
#define GPHY_FSCI_PDI_GPHY_FSCI_PDI_CTRL 0x0001F000u

//! Register Reset Value
#define GPHY_FSCI_PDI_CTRL_RST 0x0000u

//! Field XR - XR interupt enable
#define GPHY_FSCI_PDI_CTRL_XR_POS 0
//! Field XR - XR interupt enable
#define GPHY_FSCI_PDI_CTRL_XR_MASK 0x1u
//! Constant DIS - disable
#define CONST_GPHY_FSCI_PDI_CTRL_XR_DIS 0x0
//! Constant EN - enable
#define CONST_GPHY_FSCI_PDI_CTRL_XR_EN 0x1

//! Field XE - XE interupt enable
#define GPHY_FSCI_PDI_CTRL_XE_POS 1
//! Field XE - XE interupt enable
#define GPHY_FSCI_PDI_CTRL_XE_MASK 0x2u
//! Constant DIS - disable
#define CONST_GPHY_FSCI_PDI_CTRL_XE_DIS 0x0
//! Constant EN - enable
#define CONST_GPHY_FSCI_PDI_CTRL_XE_EN 0x1

//! Field RR - RR interupt enable
#define GPHY_FSCI_PDI_CTRL_RR_POS 2
//! Field RR - RR interupt enable
#define GPHY_FSCI_PDI_CTRL_RR_MASK 0x4u
//! Constant DIS - disable
#define CONST_GPHY_FSCI_PDI_CTRL_RR_DIS 0x0
//! Constant EN - enable
#define CONST_GPHY_FSCI_PDI_CTRL_RR_EN 0x1

//! Field ERR - ERR interupt enable
#define GPHY_FSCI_PDI_CTRL_ERR_POS 3
//! Field ERR - ERR interupt enable
#define GPHY_FSCI_PDI_CTRL_ERR_MASK 0x8u
//! Constant DIS - disable
#define CONST_GPHY_FSCI_PDI_CTRL_ERR_DIS 0x0
//! Constant EN - enable
#define CONST_GPHY_FSCI_PDI_CTRL_ERR_EN 0x1

//! Field FSC0 - Full Custom Status 0 interupt enable
#define GPHY_FSCI_PDI_CTRL_FSC0_POS 4
//! Field FSC0 - Full Custom Status 0 interupt enable
#define GPHY_FSCI_PDI_CTRL_FSC0_MASK 0x10u
//! Constant DIS - disable
#define CONST_GPHY_FSCI_PDI_CTRL_FSC0_DIS 0x0
//! Constant EN - enable
#define CONST_GPHY_FSCI_PDI_CTRL_FSC0_EN 0x1

//! Field FSC1 - Full custom Status 1 interupt enable
#define GPHY_FSCI_PDI_CTRL_FSC1_POS 5
//! Field FSC1 - Full custom Status 1 interupt enable
#define GPHY_FSCI_PDI_CTRL_FSC1_MASK 0x20u
//! Constant DIS - disable
#define CONST_GPHY_FSCI_PDI_CTRL_FSC1_DIS 0x0
//! Constant EN - enable
#define CONST_GPHY_FSCI_PDI_CTRL_FSC1_EN 0x1

//! @}

//! \defgroup GPHY_FSCI_PDI_STAT Register GPHY_FSCI_PDI_STAT - FCSI STATUS
//! @{

//! Register Offset (relative)
#define GPHY_FSCI_PDI_STAT 0x2
//! Register Offset (absolute) for 1st Instance GPHY_FSCI_PDI
#define GPHY_FSCI_PDI_GPHY_FSCI_PDI_STAT 0x0001F002u

//! Register Reset Value
#define GPHY_FSCI_PDI_STAT_RST 0x0000u

//! Field XR - Transmitter Ready
#define GPHY_FSCI_PDI_STAT_XR_POS 0
//! Field XR - Transmitter Ready
#define GPHY_FSCI_PDI_STAT_XR_MASK 0x1u
//! Constant FNOTREADY - nothing
#define CONST_GPHY_FSCI_PDI_STAT_XR_FNOTREADY 0x0
//! Constant FREADY - ready
#define CONST_GPHY_FSCI_PDI_STAT_XR_FREADY 0x1

//! Field XE - Transmitter Empty
#define GPHY_FSCI_PDI_STAT_XE_POS 1
//! Field XE - Transmitter Empty
#define GPHY_FSCI_PDI_STAT_XE_MASK 0x2u
//! Constant FNOTEMPTY - nothing
#define CONST_GPHY_FSCI_PDI_STAT_XE_FNOTEMPTY 0x0
//! Constant FEMPTY - EMPTY
#define CONST_GPHY_FSCI_PDI_STAT_XE_FEMPTY 0x1

//! Field RR - Receiver Ready
#define GPHY_FSCI_PDI_STAT_RR_POS 2
//! Field RR - Receiver Ready
#define GPHY_FSCI_PDI_STAT_RR_MASK 0x4u
//! Constant FNOTREADY - nothing
#define CONST_GPHY_FSCI_PDI_STAT_RR_FNOTREADY 0x0
//! Constant FREADY - Ready
#define CONST_GPHY_FSCI_PDI_STAT_RR_FREADY 0x1

//! Field ERR - Error
#define GPHY_FSCI_PDI_STAT_ERR_POS 3
//! Field ERR - Error
#define GPHY_FSCI_PDI_STAT_ERR_MASK 0x8u
//! Constant NORMAL - nothing
#define CONST_GPHY_FSCI_PDI_STAT_ERR_NORMAL 0x0
//! Constant EVOCC - Read Event Error
#define CONST_GPHY_FSCI_PDI_STAT_ERR_EVOCC 0x1

//! Field FSC0 - Status of input signal FC_STAT0
#define GPHY_FSCI_PDI_STAT_FSC0_POS 4
//! Field FSC0 - Status of input signal FC_STAT0
#define GPHY_FSCI_PDI_STAT_FSC0_MASK 0x10u

//! Field FSC1 - status of input signal FC_STAT1
#define GPHY_FSCI_PDI_STAT_FSC1_POS 5
//! Field FSC1 - status of input signal FC_STAT1
#define GPHY_FSCI_PDI_STAT_FSC1_MASK 0x20u

//! @}

//! \defgroup GPHY_FSCI_PDI_INTR Register GPHY_FSCI_PDI_INTR - FCSI Interrupt Register
//! @{

//! Register Offset (relative)
#define GPHY_FSCI_PDI_INTR 0x4
//! Register Offset (absolute) for 1st Instance GPHY_FSCI_PDI
#define GPHY_FSCI_PDI_GPHY_FSCI_PDI_INTR 0x0001F004u

//! Register Reset Value
#define GPHY_FSCI_PDI_INTR_RST 0x0000u

//! Field XR - XR interupt event
#define GPHY_FSCI_PDI_INTR_XR_POS 0
//! Field XR - XR interupt event
#define GPHY_FSCI_PDI_INTR_XR_MASK 0x1u
//! Constant DIS - disable
#define CONST_GPHY_FSCI_PDI_INTR_XR_DIS 0x0
//! Constant EN - enable
#define CONST_GPHY_FSCI_PDI_INTR_XR_EN 0x1

//! Field XE - XE interupt event
#define GPHY_FSCI_PDI_INTR_XE_POS 1
//! Field XE - XE interupt event
#define GPHY_FSCI_PDI_INTR_XE_MASK 0x2u
//! Constant DIS - disable
#define CONST_GPHY_FSCI_PDI_INTR_XE_DIS 0x0
//! Constant EN - enable
#define CONST_GPHY_FSCI_PDI_INTR_XE_EN 0x1

//! Field RR - RR interupt event
#define GPHY_FSCI_PDI_INTR_RR_POS 2
//! Field RR - RR interupt event
#define GPHY_FSCI_PDI_INTR_RR_MASK 0x4u
//! Constant DIS - disable
#define CONST_GPHY_FSCI_PDI_INTR_RR_DIS 0x0
//! Constant EN - enable
#define CONST_GPHY_FSCI_PDI_INTR_RR_EN 0x1

//! Field ERR - ERR interupt event
#define GPHY_FSCI_PDI_INTR_ERR_POS 3
//! Field ERR - ERR interupt event
#define GPHY_FSCI_PDI_INTR_ERR_MASK 0x8u
//! Constant DIS - disable
#define CONST_GPHY_FSCI_PDI_INTR_ERR_DIS 0x0
//! Constant EN - enable
#define CONST_GPHY_FSCI_PDI_INTR_ERR_EN 0x1

//! Field FSC0 - Full Custom Status 0 interupt event
#define GPHY_FSCI_PDI_INTR_FSC0_POS 4
//! Field FSC0 - Full Custom Status 0 interupt event
#define GPHY_FSCI_PDI_INTR_FSC0_MASK 0x10u
//! Constant DIS - disable
#define CONST_GPHY_FSCI_PDI_INTR_FSC0_DIS 0x0
//! Constant EN - enable
#define CONST_GPHY_FSCI_PDI_INTR_FSC0_EN 0x1

//! Field FSC1 - Full custom Status 1 interupt event
#define GPHY_FSCI_PDI_INTR_FSC1_POS 5
//! Field FSC1 - Full custom Status 1 interupt event
#define GPHY_FSCI_PDI_INTR_FSC1_MASK 0x20u
//! Constant DIS - disable
#define CONST_GPHY_FSCI_PDI_INTR_FSC1_DIS 0x0
//! Constant EN - enable
#define CONST_GPHY_FSCI_PDI_INTR_FSC1_EN 0x1

//! @}

//! \defgroup GPHY_FSCI_PDI_CMD Register GPHY_FSCI_PDI_CMD - FSCI Command Register
//! @{

//! Register Offset (relative)
#define GPHY_FSCI_PDI_CMD 0x6
//! Register Offset (absolute) for 1st Instance GPHY_FSCI_PDI
#define GPHY_FSCI_PDI_GPHY_FSCI_PDI_CMD 0x0001F006u

//! Register Reset Value
#define GPHY_FSCI_PDI_CMD_RST 0x0000u

//! Field ADDR - Address
#define GPHY_FSCI_PDI_CMD_ADDR_POS 0
//! Field ADDR - Address
#define GPHY_FSCI_PDI_CMD_ADDR_MASK 0xFFu

//! Field LEN - length
#define GPHY_FSCI_PDI_CMD_LEN_POS 8
//! Field LEN - length
#define GPHY_FSCI_PDI_CMD_LEN_MASK 0xF00u

//! Field AI - auto-increment
#define GPHY_FSCI_PDI_CMD_AI_POS 12
//! Field AI - auto-increment
#define GPHY_FSCI_PDI_CMD_AI_MASK 0x1000u

//! Field CMD - Command
#define GPHY_FSCI_PDI_CMD_CMD_POS 13
//! Field CMD - Command
#define GPHY_FSCI_PDI_CMD_CMD_MASK 0xE000u
//! Constant WRITE - In this case the ADDR field and the AI field is written to a temporary ad...
#define CONST_GPHY_FSCI_PDI_CMD_CMD_WRITE 0x0
//! Constant READ - In this case a read operation is inserted into the Command-FIFO together ...
#define CONST_GPHY_FSCI_PDI_CMD_CMD_READ 0x1
//! Constant RST - Reset FCSI2C and FCSI2-tree. The reset line of the FCSI2 bus is pulsed lo...
#define CONST_GPHY_FSCI_PDI_CMD_CMD_RST 0x2
//! Constant TREE_RST - Reset FCSI2-tree. The Reset line of the FCSI2 bus is pulsed low. The FCSI...
#define CONST_GPHY_FSCI_PDI_CMD_CMD_TREE_RST 0x3
//! Constant CMD_RST - Reset Command-In FIFO. The Command-In FIFO is reset. The current bus tran...
#define CONST_GPHY_FSCI_PDI_CMD_CMD_CMD_RST 0x4
//! Constant RES_RST - Reset Result-FIFO. The Result-FIFO is reset. The current bus transaction ...
#define CONST_GPHY_FSCI_PDI_CMD_CMD_RES_RST 0x5

//! @}

//! \defgroup GPHY_FSCI_PDI_DATA Register GPHY_FSCI_PDI_DATA - FCSI Data Register
//! @{

//! Register Offset (relative)
#define GPHY_FSCI_PDI_DATA 0x8
//! Register Offset (absolute) for 1st Instance GPHY_FSCI_PDI
#define GPHY_FSCI_PDI_GPHY_FSCI_PDI_DATA 0x0001F008u

//! Register Reset Value
#define GPHY_FSCI_PDI_DATA_RST 0x0000u

//! Field DATA - Read/Write Data
#define GPHY_FSCI_PDI_DATA_DATA_POS 0
//! Field DATA - Read/Write Data
#define GPHY_FSCI_PDI_DATA_DATA_MASK 0xFFFFu

//! @}

//! @}

#endif
