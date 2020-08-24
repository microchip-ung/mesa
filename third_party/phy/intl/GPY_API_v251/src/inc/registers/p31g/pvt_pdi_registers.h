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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/pvt_pdi_def.xml
// Register File Name  : PVT_PDI_REGISTERS
// Register File Title : PVT Module Registers Description
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _PVT_PDI_REGISTERS_H
#define _PVT_PDI_REGISTERS_H

//! \defgroup PVT_PDI_REGISTERS Register File PVT_PDI_REGISTERS - PVT Module Registers Description
//! @{

//! Base Address of PVT_PDI_REGISTERS
#define PVT_PDI_REGISTERS_MODULE_BASE 0x00D28400u

//! \defgroup PVT_SENSOR Register PVT_SENSOR - Temperature voltage process sensor control
//! @{

//! Register Offset (relative)
#define PVT_SENSOR 0x0
//! Register Offset (absolute) for 1st Instance PVT_PDI_REGISTERS
#define PVT_PDI_REGISTERS_PVT_SENSOR 0x00D28400u

//! Register Reset Value
#define PVT_SENSOR_RST 0x00000008u

//! Field T_EN - Temperature measurement enable
#define PVT_SENSOR_T_EN_POS 0
//! Field T_EN - Temperature measurement enable
#define PVT_SENSOR_T_EN_MASK 0x3u
//! Constant DIS - Disable PVT
#define CONST_PVT_SENSOR_T_EN_DIS 0x0
//! Constant EN - Manual PVT Enable
#define CONST_PVT_SENSOR_T_EN_EN 0x1
//! Constant T_EN - Enable Automatic Temperature Sensor Mode
#define CONST_PVT_SENSOR_T_EN_T_EN 0x2

//! Field VSAMPLE - Voltage Sampling Mode
#define PVT_SENSOR_VSAMPLE_POS 2
//! Field VSAMPLE - Voltage Sampling Mode
#define PVT_SENSOR_VSAMPLE_MASK 0x4u
//! Constant NV - Not Voltage mode
#define CONST_PVT_SENSOR_VSAMPLE_NV 0x0
//! Constant V - Voltage Sample mode
#define CONST_PVT_SENSOR_VSAMPLE_V 0x1

//! Field TSOVH_INT_EN - Enable the TS overheat interrupt
#define PVT_SENSOR_TSOVH_INT_EN_POS 3
//! Field TSOVH_INT_EN - Enable the TS overheat interrupt
#define PVT_SENSOR_TSOVH_INT_EN_MASK 0x8u
//! Constant DIS
#define CONST_PVT_SENSOR_TSOVH_INT_EN_DIS 0x0
//! Constant EN
#define CONST_PVT_SENSOR_TSOVH_INT_EN_EN 0x1

//! Field PSAMPLE_PN - Process PN Sampling Mode
#define PVT_SENSOR_PSAMPLE_PN_POS 4
//! Field PSAMPLE_PN - Process PN Sampling Mode
#define PVT_SENSOR_PSAMPLE_PN_MASK 0x30u
//! Constant B - P and N Average
#define CONST_PVT_SENSOR_PSAMPLE_PN_B 0x0
//! Constant N - N device
#define CONST_PVT_SENSOR_PSAMPLE_PN_N 0x1
//! Constant P - P device
#define CONST_PVT_SENSOR_PSAMPLE_PN_P 0x2

//! Field PSAMPLE_CNR - Process Corner Sampling Mode
#define PVT_SENSOR_PSAMPLE_CNR_POS 6
//! Field PSAMPLE_CNR - Process Corner Sampling Mode
#define PVT_SENSOR_PSAMPLE_CNR_MASK 0xC0u
//! Constant T - Temperature sensor mode together with VSAMLE is 0
#define CONST_PVT_SENSOR_PSAMPLE_CNR_T 0x0
//! Constant LP - LVT device
#define CONST_PVT_SENSOR_PSAMPLE_CNR_LP 0x1
//! Constant HP - HVT device
#define CONST_PVT_SENSOR_PSAMPLE_CNR_HP 0x2
//! Constant S - SVT
#define CONST_PVT_SENSOR_PSAMPLE_CNR_S 0x3

//! @}

//! \defgroup PVT_INT_ON Register PVT_INT_ON - Temperature Interrupt Assertion
//! @{

//! Register Offset (relative)
#define PVT_INT_ON 0x4
//! Register Offset (absolute) for 1st Instance PVT_PDI_REGISTERS
#define PVT_PDI_REGISTERS_PVT_INT_ON 0x00D28404u

//! Register Reset Value
#define PVT_INT_ON_RST 0x00000300u

//! Field INT_LVL_ON - Temperature code for Interrupt assertion
#define PVT_INT_ON_INT_LVL_ON_POS 0
//! Field INT_LVL_ON - Temperature code for Interrupt assertion
#define PVT_INT_ON_INT_LVL_ON_MASK 0x3FFu

//! @}

//! \defgroup PVT_INT_OFF Register PVT_INT_OFF - Temperature Interrupt De-assertion
//! @{

//! Register Offset (relative)
#define PVT_INT_OFF 0x8
//! Register Offset (absolute) for 1st Instance PVT_PDI_REGISTERS
#define PVT_PDI_REGISTERS_PVT_INT_OFF 0x00D28408u

//! Register Reset Value
#define PVT_INT_OFF_RST 0x000002C0u

//! Field INT_LVL_OFF - Temperature code for Interrupt De-assertion
#define PVT_INT_OFF_INT_LVL_OFF_POS 0
//! Field INT_LVL_OFF - Temperature code for Interrupt De-assertion
#define PVT_INT_OFF_INT_LVL_OFF_MASK 0x3FFu

//! @}

//! \defgroup PVT_SENSOR_DATA Register PVT_SENSOR_DATA - sensor read out
//! @{

//! Register Offset (relative)
#define PVT_SENSOR_DATA 0xC
//! Register Offset (absolute) for 1st Instance PVT_PDI_REGISTERS
#define PVT_PDI_REGISTERS_PVT_SENSOR_DATA 0x00D2840Cu

//! Register Reset Value
#define PVT_SENSOR_DATA_RST 0x00000000u

//! Field PVT_CODE - sensor output code
#define PVT_SENSOR_DATA_PVT_CODE_POS 0
//! Field PVT_CODE - sensor output code
#define PVT_SENSOR_DATA_PVT_CODE_MASK 0x3FFu

//! Field TS_DV - Converted Data Available
#define PVT_SENSOR_DATA_TS_DV_POS 15
//! Field TS_DV - Converted Data Available
#define PVT_SENSOR_DATA_TS_DV_MASK 0x8000u
//! Constant NV - data conversion is not ready
#define CONST_PVT_SENSOR_DATA_TS_DV_NV 0x0
//! Constant EOC - Data conversion is done, available for read
#define CONST_PVT_SENSOR_DATA_TS_DV_EOC 0x1

//! @}

//! \defgroup PVT_SENSOR_TBITS Register PVT_SENSOR_TBITS
//! @{

//! Register Offset (relative)
#define PVT_SENSOR_TBITS 0x10
//! Register Offset (absolute) for 1st Instance PVT_PDI_REGISTERS
#define PVT_PDI_REGISTERS_PVT_SENSOR_TBITS 0x00D28410u

//! Register Reset Value
#define PVT_SENSOR_TBITS_RST 0x00000000u

//! Field PVT_TRMBITS - these bits control and configuration of PVT for Trim purpose
#define PVT_SENSOR_TBITS_PVT_TRMBITS_POS 0
//! Field PVT_TRMBITS - these bits control and configuration of PVT for Trim purpose
#define PVT_SENSOR_TBITS_PVT_TRMBITS_MASK 0x1Fu

//! @}

//! @}

#endif
