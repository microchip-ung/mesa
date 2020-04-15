/************************************************************************************
*
* Copyright (c) 2017 Aquantia Corp.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy 
* of this software and associated documentation files (the "Software"), to deal 
* in the Software without restriction, including without limitation the rights 
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
* copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all 
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
* SOFTWARE.
*
************************************************************************************/

/*! \file 
*   This file contains the compiler assist macros and doxygen comments
*   for the PCS Registers block.
*/

/*! \defgroup PCS_registers_Defines PCS Registers Defines
*   This module contains the compiler assist macros and doxygen comments
*   for the PCS Registers block.
*/
/***********************************************************************
*                     Copyright Aquantia Corp.
*                             Freeware
*
* $File: //depot/icm/proj/Dena/rev1.0/c/Systems/tools/windows/regMapParser/src/gencheaders.py $
*
* $Revision: #13 $
*
* $DateTime: 2016/09/23 10:49:54 $
*
* $Author: wxia $
*
* $Label: $
*
* Description:
*
*   This file contains the compiler assist macros for the registers contained in the PCS Registers block.
*
*
***********************************************************************/


/*@{*/
#ifndef AQ_EUR_PCS_REGS_DEFINES_HEADER
#define AQ_EUR_PCS_REGS_DEFINES_HEADER


/*-----------------------------------------------------------------------------*/
/*Access macro definitions                                                     */
/*-----------------------------------------------------------------------------*/
/*! \brief Base register address of structure AQ_PcsStandardControl_1_EUR */
#define AQ_PcsStandardControl_1_EUR_baseRegisterAddress 0x0000
/*! \brief MMD address of structure AQ_PcsStandardControl_1_EUR */
#define AQ_PcsStandardControl_1_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reset in AQ_PcsStandardControl_1_EUR */
#define AQ_PcsStandardControl_1_EUR_reset 0
/*! \brief Preprocessor variable to relate field to bit position in structure reset in AQ_PcsStandardControl_1_EUR */
#define bits_AQ_PcsStandardControl_1_EUR_reset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reset in AQ_PcsStandardControl_1_EUR */
#define word_AQ_PcsStandardControl_1_EUR_reset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure loopback in AQ_PcsStandardControl_1_EUR */
#define AQ_PcsStandardControl_1_EUR_loopback 0
/*! \brief Preprocessor variable to relate field to bit position in structure loopback in AQ_PcsStandardControl_1_EUR */
#define bits_AQ_PcsStandardControl_1_EUR_loopback u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure loopback in AQ_PcsStandardControl_1_EUR */
#define word_AQ_PcsStandardControl_1_EUR_loopback u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure speedSelectionLsb in AQ_PcsStandardControl_1_EUR */
#define AQ_PcsStandardControl_1_EUR_speedSelectionLsb 0
/*! \brief Preprocessor variable to relate field to bit position in structure speedSelectionLsb in AQ_PcsStandardControl_1_EUR */
#define bits_AQ_PcsStandardControl_1_EUR_speedSelectionLsb u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure speedSelectionLsb in AQ_PcsStandardControl_1_EUR */
#define word_AQ_PcsStandardControl_1_EUR_speedSelectionLsb u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved0a in AQ_PcsStandardControl_1_EUR */
#define AQ_PcsStandardControl_1_EUR_reserved0a 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved0a in AQ_PcsStandardControl_1_EUR */
#define bits_AQ_PcsStandardControl_1_EUR_reserved0a u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved0a in AQ_PcsStandardControl_1_EUR */
#define word_AQ_PcsStandardControl_1_EUR_reserved0a u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowPower in AQ_PcsStandardControl_1_EUR */
#define AQ_PcsStandardControl_1_EUR_lowPower 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowPower in AQ_PcsStandardControl_1_EUR */
#define bits_AQ_PcsStandardControl_1_EUR_lowPower u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowPower in AQ_PcsStandardControl_1_EUR */
#define word_AQ_PcsStandardControl_1_EUR_lowPower u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clockStopEnable in AQ_PcsStandardControl_1_EUR */
#define AQ_PcsStandardControl_1_EUR_clockStopEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure clockStopEnable in AQ_PcsStandardControl_1_EUR */
#define bits_AQ_PcsStandardControl_1_EUR_clockStopEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clockStopEnable in AQ_PcsStandardControl_1_EUR */
#define word_AQ_PcsStandardControl_1_EUR_clockStopEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved0b in AQ_PcsStandardControl_1_EUR */
#define AQ_PcsStandardControl_1_EUR_reserved0b 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved0b in AQ_PcsStandardControl_1_EUR */
#define bits_AQ_PcsStandardControl_1_EUR_reserved0b u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved0b in AQ_PcsStandardControl_1_EUR */
#define word_AQ_PcsStandardControl_1_EUR_reserved0b u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure speedSelectionMsb in AQ_PcsStandardControl_1_EUR */
#define AQ_PcsStandardControl_1_EUR_speedSelectionMsb 0
/*! \brief Preprocessor variable to relate field to bit position in structure speedSelectionMsb in AQ_PcsStandardControl_1_EUR */
#define bits_AQ_PcsStandardControl_1_EUR_speedSelectionMsb u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure speedSelectionMsb in AQ_PcsStandardControl_1_EUR */
#define word_AQ_PcsStandardControl_1_EUR_speedSelectionMsb u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gSpeedSelection in AQ_PcsStandardControl_1_EUR */
#define AQ_PcsStandardControl_1_EUR__10gSpeedSelection 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gSpeedSelection in AQ_PcsStandardControl_1_EUR */
#define bits_AQ_PcsStandardControl_1_EUR__10gSpeedSelection u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gSpeedSelection in AQ_PcsStandardControl_1_EUR */
#define word_AQ_PcsStandardControl_1_EUR__10gSpeedSelection u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved0c in AQ_PcsStandardControl_1_EUR */
#define AQ_PcsStandardControl_1_EUR_reserved0c 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved0c in AQ_PcsStandardControl_1_EUR */
#define bits_AQ_PcsStandardControl_1_EUR_reserved0c u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved0c in AQ_PcsStandardControl_1_EUR */
#define word_AQ_PcsStandardControl_1_EUR_reserved0c u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardStatus_1_EUR */
#define AQ_PcsStandardStatus_1_EUR_baseRegisterAddress 0x0001
/*! \brief MMD address of structure AQ_PcsStandardStatus_1_EUR */
#define AQ_PcsStandardStatus_1_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reserved01a in AQ_PcsStandardStatus_1_EUR */
#define AQ_PcsStandardStatus_1_EUR_reserved01a 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved01a in AQ_PcsStandardStatus_1_EUR */
#define bits_AQ_PcsStandardStatus_1_EUR_reserved01a u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved01a in AQ_PcsStandardStatus_1_EUR */
#define word_AQ_PcsStandardStatus_1_EUR_reserved01a u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure txLpiReceived in AQ_PcsStandardStatus_1_EUR */
#define AQ_PcsStandardStatus_1_EUR_txLpiReceived 0
/*! \brief Preprocessor variable to relate field to bit position in structure txLpiReceived in AQ_PcsStandardStatus_1_EUR */
#define bits_AQ_PcsStandardStatus_1_EUR_txLpiReceived u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure txLpiReceived in AQ_PcsStandardStatus_1_EUR */
#define word_AQ_PcsStandardStatus_1_EUR_txLpiReceived u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rxLpiReceived in AQ_PcsStandardStatus_1_EUR */
#define AQ_PcsStandardStatus_1_EUR_rxLpiReceived 0
/*! \brief Preprocessor variable to relate field to bit position in structure rxLpiReceived in AQ_PcsStandardStatus_1_EUR */
#define bits_AQ_PcsStandardStatus_1_EUR_rxLpiReceived u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rxLpiReceived in AQ_PcsStandardStatus_1_EUR */
#define word_AQ_PcsStandardStatus_1_EUR_rxLpiReceived u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure txLpiIndication in AQ_PcsStandardStatus_1_EUR */
#define AQ_PcsStandardStatus_1_EUR_txLpiIndication 0
/*! \brief Preprocessor variable to relate field to bit position in structure txLpiIndication in AQ_PcsStandardStatus_1_EUR */
#define bits_AQ_PcsStandardStatus_1_EUR_txLpiIndication u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure txLpiIndication in AQ_PcsStandardStatus_1_EUR */
#define word_AQ_PcsStandardStatus_1_EUR_txLpiIndication u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rxLpiIndication in AQ_PcsStandardStatus_1_EUR */
#define AQ_PcsStandardStatus_1_EUR_rxLpiIndication 0
/*! \brief Preprocessor variable to relate field to bit position in structure rxLpiIndication in AQ_PcsStandardStatus_1_EUR */
#define bits_AQ_PcsStandardStatus_1_EUR_rxLpiIndication u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rxLpiIndication in AQ_PcsStandardStatus_1_EUR */
#define word_AQ_PcsStandardStatus_1_EUR_rxLpiIndication u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure fault in AQ_PcsStandardStatus_1_EUR */
#define AQ_PcsStandardStatus_1_EUR_fault 0
/*! \brief Preprocessor variable to relate field to bit position in structure fault in AQ_PcsStandardStatus_1_EUR */
#define bits_AQ_PcsStandardStatus_1_EUR_fault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure fault in AQ_PcsStandardStatus_1_EUR */
#define word_AQ_PcsStandardStatus_1_EUR_fault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clockStopCapable in AQ_PcsStandardStatus_1_EUR */
#define AQ_PcsStandardStatus_1_EUR_clockStopCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure clockStopCapable in AQ_PcsStandardStatus_1_EUR */
#define bits_AQ_PcsStandardStatus_1_EUR_clockStopCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clockStopCapable in AQ_PcsStandardStatus_1_EUR */
#define word_AQ_PcsStandardStatus_1_EUR_clockStopCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved01b in AQ_PcsStandardStatus_1_EUR */
#define AQ_PcsStandardStatus_1_EUR_reserved01b 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved01b in AQ_PcsStandardStatus_1_EUR */
#define bits_AQ_PcsStandardStatus_1_EUR_reserved01b u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved01b in AQ_PcsStandardStatus_1_EUR */
#define word_AQ_PcsStandardStatus_1_EUR_reserved01b u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsReceiveLinkStatus in AQ_PcsStandardStatus_1_EUR */
#define AQ_PcsStandardStatus_1_EUR_pcsReceiveLinkStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsReceiveLinkStatus in AQ_PcsStandardStatus_1_EUR */
#define bits_AQ_PcsStandardStatus_1_EUR_pcsReceiveLinkStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsReceiveLinkStatus in AQ_PcsStandardStatus_1_EUR */
#define word_AQ_PcsStandardStatus_1_EUR_pcsReceiveLinkStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowPowerAbility in AQ_PcsStandardStatus_1_EUR */
#define AQ_PcsStandardStatus_1_EUR_lowPowerAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowPowerAbility in AQ_PcsStandardStatus_1_EUR */
#define bits_AQ_PcsStandardStatus_1_EUR_lowPowerAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowPowerAbility in AQ_PcsStandardStatus_1_EUR */
#define word_AQ_PcsStandardStatus_1_EUR_lowPowerAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved01c in AQ_PcsStandardStatus_1_EUR */
#define AQ_PcsStandardStatus_1_EUR_reserved01c 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved01c in AQ_PcsStandardStatus_1_EUR */
#define bits_AQ_PcsStandardStatus_1_EUR_reserved01c u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved01c in AQ_PcsStandardStatus_1_EUR */
#define word_AQ_PcsStandardStatus_1_EUR_reserved01c u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardDeviceIdentifier_EUR */
#define AQ_PcsStandardDeviceIdentifier_EUR_baseRegisterAddress 0x0002
/*! \brief MMD address of structure AQ_PcsStandardDeviceIdentifier_EUR */
#define AQ_PcsStandardDeviceIdentifier_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdMSW in AQ_PcsStandardDeviceIdentifier_EUR */
#define AQ_PcsStandardDeviceIdentifier_EUR_deviceIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdMSW in AQ_PcsStandardDeviceIdentifier_EUR */
#define bits_AQ_PcsStandardDeviceIdentifier_EUR_deviceIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdMSW in AQ_PcsStandardDeviceIdentifier_EUR */
#define word_AQ_PcsStandardDeviceIdentifier_EUR_deviceIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdLSW in AQ_PcsStandardDeviceIdentifier_EUR */
#define AQ_PcsStandardDeviceIdentifier_EUR_deviceIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdLSW in AQ_PcsStandardDeviceIdentifier_EUR */
#define bits_AQ_PcsStandardDeviceIdentifier_EUR_deviceIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdLSW in AQ_PcsStandardDeviceIdentifier_EUR */
#define word_AQ_PcsStandardDeviceIdentifier_EUR_deviceIdLSW u1.word_1

/*! \brief Base register address of structure AQ_PcsStandardSpeedAbility_EUR */
#define AQ_PcsStandardSpeedAbility_EUR_baseRegisterAddress 0x0004
/*! \brief MMD address of structure AQ_PcsStandardSpeedAbility_EUR */
#define AQ_PcsStandardSpeedAbility_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reserved4a in AQ_PcsStandardSpeedAbility_EUR */
#define AQ_PcsStandardSpeedAbility_EUR_reserved4a 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved4a in AQ_PcsStandardSpeedAbility_EUR */
#define bits_AQ_PcsStandardSpeedAbility_EUR_reserved4a u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved4a in AQ_PcsStandardSpeedAbility_EUR */
#define word_AQ_PcsStandardSpeedAbility_EUR_reserved4a u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _5gCapable in AQ_PcsStandardSpeedAbility_EUR */
#define AQ_PcsStandardSpeedAbility_EUR__5gCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _5gCapable in AQ_PcsStandardSpeedAbility_EUR */
#define bits_AQ_PcsStandardSpeedAbility_EUR__5gCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _5gCapable in AQ_PcsStandardSpeedAbility_EUR */
#define word_AQ_PcsStandardSpeedAbility_EUR__5gCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _2_5gCapable in AQ_PcsStandardSpeedAbility_EUR */
#define AQ_PcsStandardSpeedAbility_EUR__2_5gCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _2_5gCapable in AQ_PcsStandardSpeedAbility_EUR */
#define bits_AQ_PcsStandardSpeedAbility_EUR__2_5gCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _2_5gCapable in AQ_PcsStandardSpeedAbility_EUR */
#define word_AQ_PcsStandardSpeedAbility_EUR__2_5gCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved4b in AQ_PcsStandardSpeedAbility_EUR */
#define AQ_PcsStandardSpeedAbility_EUR_reserved4b 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved4b in AQ_PcsStandardSpeedAbility_EUR */
#define bits_AQ_PcsStandardSpeedAbility_EUR_reserved4b u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved4b in AQ_PcsStandardSpeedAbility_EUR */
#define word_AQ_PcsStandardSpeedAbility_EUR_reserved4b u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10pass_ts__2base_tlCapable in AQ_PcsStandardSpeedAbility_EUR */
#define AQ_PcsStandardSpeedAbility_EUR__10pass_ts__2base_tlCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10pass_ts__2base_tlCapable in AQ_PcsStandardSpeedAbility_EUR */
#define bits_AQ_PcsStandardSpeedAbility_EUR__10pass_ts__2base_tlCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10pass_ts__2base_tlCapable in AQ_PcsStandardSpeedAbility_EUR */
#define word_AQ_PcsStandardSpeedAbility_EUR__10pass_ts__2base_tlCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gCapable in AQ_PcsStandardSpeedAbility_EUR */
#define AQ_PcsStandardSpeedAbility_EUR__10gCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gCapable in AQ_PcsStandardSpeedAbility_EUR */
#define bits_AQ_PcsStandardSpeedAbility_EUR__10gCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gCapable in AQ_PcsStandardSpeedAbility_EUR */
#define word_AQ_PcsStandardSpeedAbility_EUR__10gCapable u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardDevicesInPackage_EUR */
#define AQ_PcsStandardDevicesInPackage_EUR_baseRegisterAddress 0x0005
/*! \brief MMD address of structure AQ_PcsStandardDevicesInPackage_EUR */
#define AQ_PcsStandardDevicesInPackage_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define AQ_PcsStandardDevicesInPackage_EUR_autonegotiationPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define bits_AQ_PcsStandardDevicesInPackage_EUR_autonegotiationPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define word_AQ_PcsStandardDevicesInPackage_EUR_autonegotiationPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tcPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define AQ_PcsStandardDevicesInPackage_EUR_tcPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure tcPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define bits_AQ_PcsStandardDevicesInPackage_EUR_tcPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tcPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define word_AQ_PcsStandardDevicesInPackage_EUR_tcPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure dteXsPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define AQ_PcsStandardDevicesInPackage_EUR_dteXsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure dteXsPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define bits_AQ_PcsStandardDevicesInPackage_EUR_dteXsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure dteXsPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define word_AQ_PcsStandardDevicesInPackage_EUR_dteXsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_Present in AQ_PcsStandardDevicesInPackage_EUR */
#define AQ_PcsStandardDevicesInPackage_EUR_phyXS_Present 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_Present in AQ_PcsStandardDevicesInPackage_EUR */
#define bits_AQ_PcsStandardDevicesInPackage_EUR_phyXS_Present u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_Present in AQ_PcsStandardDevicesInPackage_EUR */
#define word_AQ_PcsStandardDevicesInPackage_EUR_phyXS_Present u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define AQ_PcsStandardDevicesInPackage_EUR_pcsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define bits_AQ_PcsStandardDevicesInPackage_EUR_pcsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define word_AQ_PcsStandardDevicesInPackage_EUR_pcsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure wisPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define AQ_PcsStandardDevicesInPackage_EUR_wisPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure wisPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define bits_AQ_PcsStandardDevicesInPackage_EUR_wisPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure wisPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define word_AQ_PcsStandardDevicesInPackage_EUR_wisPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define AQ_PcsStandardDevicesInPackage_EUR_pmaPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define bits_AQ_PcsStandardDevicesInPackage_EUR_pmaPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define word_AQ_PcsStandardDevicesInPackage_EUR_pmaPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clause_22RegistersPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define AQ_PcsStandardDevicesInPackage_EUR_clause_22RegistersPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22RegistersPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define bits_AQ_PcsStandardDevicesInPackage_EUR_clause_22RegistersPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clause_22RegistersPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define word_AQ_PcsStandardDevicesInPackage_EUR_clause_22RegistersPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_2Present in AQ_PcsStandardDevicesInPackage_EUR */
#define AQ_PcsStandardDevicesInPackage_EUR_vendorSpecificDevice_2Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_2Present in AQ_PcsStandardDevicesInPackage_EUR */
#define bits_AQ_PcsStandardDevicesInPackage_EUR_vendorSpecificDevice_2Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_2Present in AQ_PcsStandardDevicesInPackage_EUR */
#define word_AQ_PcsStandardDevicesInPackage_EUR_vendorSpecificDevice_2Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_1Present in AQ_PcsStandardDevicesInPackage_EUR */
#define AQ_PcsStandardDevicesInPackage_EUR_vendorSpecificDevice_1Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_1Present in AQ_PcsStandardDevicesInPackage_EUR */
#define bits_AQ_PcsStandardDevicesInPackage_EUR_vendorSpecificDevice_1Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_1Present in AQ_PcsStandardDevicesInPackage_EUR */
#define word_AQ_PcsStandardDevicesInPackage_EUR_vendorSpecificDevice_1Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure clause_22ExtensionPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define AQ_PcsStandardDevicesInPackage_EUR_clause_22ExtensionPresent 1
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22ExtensionPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define bits_AQ_PcsStandardDevicesInPackage_EUR_clause_22ExtensionPresent u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure clause_22ExtensionPresent in AQ_PcsStandardDevicesInPackage_EUR */
#define word_AQ_PcsStandardDevicesInPackage_EUR_clause_22ExtensionPresent u1.word_1

/*! \brief Base register address of structure AQ_PcsStandardControl_2_EUR */
#define AQ_PcsStandardControl_2_EUR_baseRegisterAddress 0x0007
/*! \brief MMD address of structure AQ_PcsStandardControl_2_EUR */
#define AQ_PcsStandardControl_2_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reserved7 in AQ_PcsStandardControl_2_EUR */
#define AQ_PcsStandardControl_2_EUR_reserved7 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved7 in AQ_PcsStandardControl_2_EUR */
#define bits_AQ_PcsStandardControl_2_EUR_reserved7 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved7 in AQ_PcsStandardControl_2_EUR */
#define word_AQ_PcsStandardControl_2_EUR_reserved7 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsDeviceType in AQ_PcsStandardControl_2_EUR */
#define AQ_PcsStandardControl_2_EUR_pcsDeviceType 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsDeviceType in AQ_PcsStandardControl_2_EUR */
#define bits_AQ_PcsStandardControl_2_EUR_pcsDeviceType u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsDeviceType in AQ_PcsStandardControl_2_EUR */
#define word_AQ_PcsStandardControl_2_EUR_pcsDeviceType u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardStatus_2_EUR */
#define AQ_PcsStandardStatus_2_EUR_baseRegisterAddress 0x0008
/*! \brief MMD address of structure AQ_PcsStandardStatus_2_EUR */
#define AQ_PcsStandardStatus_2_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure devicePresent in AQ_PcsStandardStatus_2_EUR */
#define AQ_PcsStandardStatus_2_EUR_devicePresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure devicePresent in AQ_PcsStandardStatus_2_EUR */
#define bits_AQ_PcsStandardStatus_2_EUR_devicePresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure devicePresent in AQ_PcsStandardStatus_2_EUR */
#define word_AQ_PcsStandardStatus_2_EUR_devicePresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _5gbase_tCapable in AQ_PcsStandardStatus_2_EUR */
#define AQ_PcsStandardStatus_2_EUR__5gbase_tCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _5gbase_tCapable in AQ_PcsStandardStatus_2_EUR */
#define bits_AQ_PcsStandardStatus_2_EUR__5gbase_tCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _5gbase_tCapable in AQ_PcsStandardStatus_2_EUR */
#define word_AQ_PcsStandardStatus_2_EUR__5gbase_tCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _2_5gbase_tCapable in AQ_PcsStandardStatus_2_EUR */
#define AQ_PcsStandardStatus_2_EUR__2_5gbase_tCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _2_5gbase_tCapable in AQ_PcsStandardStatus_2_EUR */
#define bits_AQ_PcsStandardStatus_2_EUR__2_5gbase_tCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _2_5gbase_tCapable in AQ_PcsStandardStatus_2_EUR */
#define word_AQ_PcsStandardStatus_2_EUR__2_5gbase_tCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitFault in AQ_PcsStandardStatus_2_EUR */
#define AQ_PcsStandardStatus_2_EUR_transmitFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure transmitFault in AQ_PcsStandardStatus_2_EUR */
#define bits_AQ_PcsStandardStatus_2_EUR_transmitFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure transmitFault in AQ_PcsStandardStatus_2_EUR */
#define word_AQ_PcsStandardStatus_2_EUR_transmitFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure receiveFault in AQ_PcsStandardStatus_2_EUR */
#define AQ_PcsStandardStatus_2_EUR_receiveFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure receiveFault in AQ_PcsStandardStatus_2_EUR */
#define bits_AQ_PcsStandardStatus_2_EUR_receiveFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure receiveFault in AQ_PcsStandardStatus_2_EUR */
#define word_AQ_PcsStandardStatus_2_EUR_receiveFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved8 in AQ_PcsStandardStatus_2_EUR */
#define AQ_PcsStandardStatus_2_EUR_reserved8 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved8 in AQ_PcsStandardStatus_2_EUR */
#define bits_AQ_PcsStandardStatus_2_EUR_reserved8 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved8 in AQ_PcsStandardStatus_2_EUR */
#define word_AQ_PcsStandardStatus_2_EUR_reserved8 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tCapable in AQ_PcsStandardStatus_2_EUR */
#define AQ_PcsStandardStatus_2_EUR__10gbase_tCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tCapable in AQ_PcsStandardStatus_2_EUR */
#define bits_AQ_PcsStandardStatus_2_EUR__10gbase_tCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tCapable in AQ_PcsStandardStatus_2_EUR */
#define word_AQ_PcsStandardStatus_2_EUR__10gbase_tCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_wCapable in AQ_PcsStandardStatus_2_EUR */
#define AQ_PcsStandardStatus_2_EUR__10gbase_wCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_wCapable in AQ_PcsStandardStatus_2_EUR */
#define bits_AQ_PcsStandardStatus_2_EUR__10gbase_wCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_wCapable in AQ_PcsStandardStatus_2_EUR */
#define word_AQ_PcsStandardStatus_2_EUR__10gbase_wCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_xCapable in AQ_PcsStandardStatus_2_EUR */
#define AQ_PcsStandardStatus_2_EUR__10gbase_xCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_xCapable in AQ_PcsStandardStatus_2_EUR */
#define bits_AQ_PcsStandardStatus_2_EUR__10gbase_xCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_xCapable in AQ_PcsStandardStatus_2_EUR */
#define word_AQ_PcsStandardStatus_2_EUR__10gbase_xCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_rCapable in AQ_PcsStandardStatus_2_EUR */
#define AQ_PcsStandardStatus_2_EUR__10gbase_rCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_rCapable in AQ_PcsStandardStatus_2_EUR */
#define bits_AQ_PcsStandardStatus_2_EUR__10gbase_rCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_rCapable in AQ_PcsStandardStatus_2_EUR */
#define word_AQ_PcsStandardStatus_2_EUR__10gbase_rCapable u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardPackageIdentifier_EUR */
#define AQ_PcsStandardPackageIdentifier_EUR_baseRegisterAddress 0x000E
/*! \brief MMD address of structure AQ_PcsStandardPackageIdentifier_EUR */
#define AQ_PcsStandardPackageIdentifier_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure packageIdMSW in AQ_PcsStandardPackageIdentifier_EUR */
#define AQ_PcsStandardPackageIdentifier_EUR_packageIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdMSW in AQ_PcsStandardPackageIdentifier_EUR */
#define bits_AQ_PcsStandardPackageIdentifier_EUR_packageIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure packageIdMSW in AQ_PcsStandardPackageIdentifier_EUR */
#define word_AQ_PcsStandardPackageIdentifier_EUR_packageIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure packageIdLSW in AQ_PcsStandardPackageIdentifier_EUR */
#define AQ_PcsStandardPackageIdentifier_EUR_packageIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdLSW in AQ_PcsStandardPackageIdentifier_EUR */
#define bits_AQ_PcsStandardPackageIdentifier_EUR_packageIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure packageIdLSW in AQ_PcsStandardPackageIdentifier_EUR */
#define word_AQ_PcsStandardPackageIdentifier_EUR_packageIdLSW u1.word_1

/*! \brief Base register address of structure AQ_PcsEeeCapabilityRegister_EUR */
#define AQ_PcsEeeCapabilityRegister_EUR_baseRegisterAddress 0x0014
/*! \brief MMD address of structure AQ_PcsEeeCapabilityRegister_EUR */
#define AQ_PcsEeeCapabilityRegister_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_krEee in AQ_PcsEeeCapabilityRegister_EUR */
#define AQ_PcsEeeCapabilityRegister_EUR__10gbase_krEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_krEee in AQ_PcsEeeCapabilityRegister_EUR */
#define bits_AQ_PcsEeeCapabilityRegister_EUR__10gbase_krEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_krEee in AQ_PcsEeeCapabilityRegister_EUR */
#define word_AQ_PcsEeeCapabilityRegister_EUR__10gbase_krEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_kx4Eee in AQ_PcsEeeCapabilityRegister_EUR */
#define AQ_PcsEeeCapabilityRegister_EUR__10gbase_kx4Eee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_kx4Eee in AQ_PcsEeeCapabilityRegister_EUR */
#define bits_AQ_PcsEeeCapabilityRegister_EUR__10gbase_kx4Eee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_kx4Eee in AQ_PcsEeeCapabilityRegister_EUR */
#define word_AQ_PcsEeeCapabilityRegister_EUR__10gbase_kx4Eee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _1000base_kxEee in AQ_PcsEeeCapabilityRegister_EUR */
#define AQ_PcsEeeCapabilityRegister_EUR__1000base_kxEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _1000base_kxEee in AQ_PcsEeeCapabilityRegister_EUR */
#define bits_AQ_PcsEeeCapabilityRegister_EUR__1000base_kxEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _1000base_kxEee in AQ_PcsEeeCapabilityRegister_EUR */
#define word_AQ_PcsEeeCapabilityRegister_EUR__1000base_kxEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tEee in AQ_PcsEeeCapabilityRegister_EUR */
#define AQ_PcsEeeCapabilityRegister_EUR__10gbase_tEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tEee in AQ_PcsEeeCapabilityRegister_EUR */
#define bits_AQ_PcsEeeCapabilityRegister_EUR__10gbase_tEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tEee in AQ_PcsEeeCapabilityRegister_EUR */
#define word_AQ_PcsEeeCapabilityRegister_EUR__10gbase_tEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _1000base_tEee in AQ_PcsEeeCapabilityRegister_EUR */
#define AQ_PcsEeeCapabilityRegister_EUR__1000base_tEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _1000base_tEee in AQ_PcsEeeCapabilityRegister_EUR */
#define bits_AQ_PcsEeeCapabilityRegister_EUR__1000base_tEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _1000base_tEee in AQ_PcsEeeCapabilityRegister_EUR */
#define word_AQ_PcsEeeCapabilityRegister_EUR__1000base_tEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _100base_txEee in AQ_PcsEeeCapabilityRegister_EUR */
#define AQ_PcsEeeCapabilityRegister_EUR__100base_txEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _100base_txEee in AQ_PcsEeeCapabilityRegister_EUR */
#define bits_AQ_PcsEeeCapabilityRegister_EUR__100base_txEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _100base_txEee in AQ_PcsEeeCapabilityRegister_EUR */
#define word_AQ_PcsEeeCapabilityRegister_EUR__100base_txEee u0.word_0

/*! \brief Base register address of structure AQ_PcsEeeCapability_2Register_EUR */
#define AQ_PcsEeeCapability_2Register_EUR_baseRegisterAddress 0x0015
/*! \brief MMD address of structure AQ_PcsEeeCapability_2Register_EUR */
#define AQ_PcsEeeCapability_2Register_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reserved15 in AQ_PcsEeeCapability_2Register_EUR */
#define AQ_PcsEeeCapability_2Register_EUR_reserved15 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved15 in AQ_PcsEeeCapability_2Register_EUR */
#define bits_AQ_PcsEeeCapability_2Register_EUR_reserved15 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved15 in AQ_PcsEeeCapability_2Register_EUR */
#define word_AQ_PcsEeeCapability_2Register_EUR_reserved15 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _5gbase_tEee in AQ_PcsEeeCapability_2Register_EUR */
#define AQ_PcsEeeCapability_2Register_EUR__5gbase_tEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _5gbase_tEee in AQ_PcsEeeCapability_2Register_EUR */
#define bits_AQ_PcsEeeCapability_2Register_EUR__5gbase_tEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _5gbase_tEee in AQ_PcsEeeCapability_2Register_EUR */
#define word_AQ_PcsEeeCapability_2Register_EUR__5gbase_tEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _2_5gbase_tEee in AQ_PcsEeeCapability_2Register_EUR */
#define AQ_PcsEeeCapability_2Register_EUR__2_5gbase_tEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _2_5gbase_tEee in AQ_PcsEeeCapability_2Register_EUR */
#define bits_AQ_PcsEeeCapability_2Register_EUR__2_5gbase_tEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _2_5gbase_tEee in AQ_PcsEeeCapability_2Register_EUR */
#define word_AQ_PcsEeeCapability_2Register_EUR__2_5gbase_tEee u0.word_0

/*! \brief Base register address of structure AQ_PcsEeeWakeErrorCounter_EUR */
#define AQ_PcsEeeWakeErrorCounter_EUR_baseRegisterAddress 0x0016
/*! \brief MMD address of structure AQ_PcsEeeWakeErrorCounter_EUR */
#define AQ_PcsEeeWakeErrorCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure eeeWakeErrorCounter in AQ_PcsEeeWakeErrorCounter_EUR */
#define AQ_PcsEeeWakeErrorCounter_EUR_eeeWakeErrorCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeWakeErrorCounter in AQ_PcsEeeWakeErrorCounter_EUR */
#define bits_AQ_PcsEeeWakeErrorCounter_EUR_eeeWakeErrorCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeWakeErrorCounter in AQ_PcsEeeWakeErrorCounter_EUR */
#define word_AQ_PcsEeeWakeErrorCounter_EUR_eeeWakeErrorCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsReserved_17Register_EUR */
#define AQ_PcsReserved_17Register_EUR_baseRegisterAddress 0x0017
/*! \brief MMD address of structure AQ_PcsReserved_17Register_EUR */
#define AQ_PcsReserved_17Register_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reserved17 in AQ_PcsReserved_17Register_EUR */
#define AQ_PcsReserved_17Register_EUR_reserved17 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved17 in AQ_PcsReserved_17Register_EUR */
#define bits_AQ_PcsReserved_17Register_EUR_reserved17 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved17 in AQ_PcsReserved_17Register_EUR */
#define word_AQ_PcsReserved_17Register_EUR_reserved17 u0.word_0

/*! \brief Base register address of structure AQ_PcsReserved_18Register_EUR */
#define AQ_PcsReserved_18Register_EUR_baseRegisterAddress 0x0018
/*! \brief MMD address of structure AQ_PcsReserved_18Register_EUR */
#define AQ_PcsReserved_18Register_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reserved18 in AQ_PcsReserved_18Register_EUR */
#define AQ_PcsReserved_18Register_EUR_reserved18 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved18 in AQ_PcsReserved_18Register_EUR */
#define bits_AQ_PcsReserved_18Register_EUR_reserved18 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved18 in AQ_PcsReserved_18Register_EUR */
#define word_AQ_PcsReserved_18Register_EUR_reserved18 u0.word_0

/*! \brief Base register address of structure AQ_PcsReserved_19Register_EUR */
#define AQ_PcsReserved_19Register_EUR_baseRegisterAddress 0x0019
/*! \brief MMD address of structure AQ_PcsReserved_19Register_EUR */
#define AQ_PcsReserved_19Register_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reserved19 in AQ_PcsReserved_19Register_EUR */
#define AQ_PcsReserved_19Register_EUR_reserved19 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved19 in AQ_PcsReserved_19Register_EUR */
#define bits_AQ_PcsReserved_19Register_EUR_reserved19 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved19 in AQ_PcsReserved_19Register_EUR */
#define word_AQ_PcsReserved_19Register_EUR_reserved19 u0.word_0

/*! \brief Base register address of structure AQ_PcsReserved_1aRegister_EUR */
#define AQ_PcsReserved_1aRegister_EUR_baseRegisterAddress 0x001A
/*! \brief MMD address of structure AQ_PcsReserved_1aRegister_EUR */
#define AQ_PcsReserved_1aRegister_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reserved1a in AQ_PcsReserved_1aRegister_EUR */
#define AQ_PcsReserved_1aRegister_EUR_reserved1a 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved1a in AQ_PcsReserved_1aRegister_EUR */
#define bits_AQ_PcsReserved_1aRegister_EUR_reserved1a u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved1a in AQ_PcsReserved_1aRegister_EUR */
#define word_AQ_PcsReserved_1aRegister_EUR_reserved1a u0.word_0

/*! \brief Base register address of structure AQ_Pcs10G_Status_EUR */
#define AQ_Pcs10G_Status_EUR_baseRegisterAddress 0x0020
/*! \brief MMD address of structure AQ_Pcs10G_Status_EUR */
#define AQ_Pcs10G_Status_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reserved20a in AQ_Pcs10G_Status_EUR */
#define AQ_Pcs10G_Status_EUR_reserved20a 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved20a in AQ_Pcs10G_Status_EUR */
#define bits_AQ_Pcs10G_Status_EUR_reserved20a u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved20a in AQ_Pcs10G_Status_EUR */
#define word_AQ_Pcs10G_Status_EUR_reserved20a u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gReceiveLinkStatus in AQ_Pcs10G_Status_EUR */
#define AQ_Pcs10G_Status_EUR__10gReceiveLinkStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gReceiveLinkStatus in AQ_Pcs10G_Status_EUR */
#define bits_AQ_Pcs10G_Status_EUR__10gReceiveLinkStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gReceiveLinkStatus in AQ_Pcs10G_Status_EUR */
#define word_AQ_Pcs10G_Status_EUR__10gReceiveLinkStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved20b in AQ_Pcs10G_Status_EUR */
#define AQ_Pcs10G_Status_EUR_reserved20b 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved20b in AQ_Pcs10G_Status_EUR */
#define bits_AQ_Pcs10G_Status_EUR_reserved20b u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved20b in AQ_Pcs10G_Status_EUR */
#define word_AQ_Pcs10G_Status_EUR_reserved20b u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_rPrbs9PatternTestingAbility in AQ_Pcs10G_Status_EUR */
#define AQ_Pcs10G_Status_EUR__10gbase_rPrbs9PatternTestingAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_rPrbs9PatternTestingAbility in AQ_Pcs10G_Status_EUR */
#define bits_AQ_Pcs10G_Status_EUR__10gbase_rPrbs9PatternTestingAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_rPrbs9PatternTestingAbility in AQ_Pcs10G_Status_EUR */
#define word_AQ_Pcs10G_Status_EUR__10gbase_rPrbs9PatternTestingAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_rPrbs31PatternTestingAbility in AQ_Pcs10G_Status_EUR */
#define AQ_Pcs10G_Status_EUR__10gbase_rPrbs31PatternTestingAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_rPrbs31PatternTestingAbility in AQ_Pcs10G_Status_EUR */
#define bits_AQ_Pcs10G_Status_EUR__10gbase_rPrbs31PatternTestingAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_rPrbs31PatternTestingAbility in AQ_Pcs10G_Status_EUR */
#define word_AQ_Pcs10G_Status_EUR__10gbase_rPrbs31PatternTestingAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gHighBer in AQ_Pcs10G_Status_EUR */
#define AQ_Pcs10G_Status_EUR__10gHighBer 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gHighBer in AQ_Pcs10G_Status_EUR */
#define bits_AQ_Pcs10G_Status_EUR__10gHighBer u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gHighBer in AQ_Pcs10G_Status_EUR */
#define word_AQ_Pcs10G_Status_EUR__10gHighBer u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gPcsBlockLock in AQ_Pcs10G_Status_EUR */
#define AQ_Pcs10G_Status_EUR__10gPcsBlockLock 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gPcsBlockLock in AQ_Pcs10G_Status_EUR */
#define bits_AQ_Pcs10G_Status_EUR__10gPcsBlockLock u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gPcsBlockLock in AQ_Pcs10G_Status_EUR */
#define word_AQ_Pcs10G_Status_EUR__10gPcsBlockLock u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsBlockLockLatched in AQ_Pcs10G_Status_EUR */
#define AQ_Pcs10G_Status_EUR_pcsBlockLockLatched 1
/*! \brief Preprocessor variable to relate field to bit position in structure pcsBlockLockLatched in AQ_Pcs10G_Status_EUR */
#define bits_AQ_Pcs10G_Status_EUR_pcsBlockLockLatched u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pcsBlockLockLatched in AQ_Pcs10G_Status_EUR */
#define word_AQ_Pcs10G_Status_EUR_pcsBlockLockLatched u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure highBerLatched in AQ_Pcs10G_Status_EUR */
#define AQ_Pcs10G_Status_EUR_highBerLatched 1
/*! \brief Preprocessor variable to relate field to bit position in structure highBerLatched in AQ_Pcs10G_Status_EUR */
#define bits_AQ_Pcs10G_Status_EUR_highBerLatched u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure highBerLatched in AQ_Pcs10G_Status_EUR */
#define word_AQ_Pcs10G_Status_EUR_highBerLatched u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure erroredFrameCounter in AQ_Pcs10G_Status_EUR */
#define AQ_Pcs10G_Status_EUR_erroredFrameCounter 1
/*! \brief Preprocessor variable to relate field to bit position in structure erroredFrameCounter in AQ_Pcs10G_Status_EUR */
#define bits_AQ_Pcs10G_Status_EUR_erroredFrameCounter u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure erroredFrameCounter in AQ_Pcs10G_Status_EUR */
#define word_AQ_Pcs10G_Status_EUR_erroredFrameCounter u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure erroredBlockCounter in AQ_Pcs10G_Status_EUR */
#define AQ_Pcs10G_Status_EUR_erroredBlockCounter 1
/*! \brief Preprocessor variable to relate field to bit position in structure erroredBlockCounter in AQ_Pcs10G_Status_EUR */
#define bits_AQ_Pcs10G_Status_EUR_erroredBlockCounter u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure erroredBlockCounter in AQ_Pcs10G_Status_EUR */
#define word_AQ_Pcs10G_Status_EUR_erroredBlockCounter u1.word_1

/*! \brief Base register address of structure AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define AQ_Pcs10G_base_rTestPatternSeedA_EUR_baseRegisterAddress 0x0022
/*! \brief MMD address of structure AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define AQ_Pcs10G_base_rTestPatternSeedA_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedABits_15_0 in AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define AQ_Pcs10G_base_rTestPatternSeedA_EUR_testPatternSeedABits_15_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedABits_15_0 in AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define bits_AQ_Pcs10G_base_rTestPatternSeedA_EUR_testPatternSeedABits_15_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedABits_15_0 in AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define word_AQ_Pcs10G_base_rTestPatternSeedA_EUR_testPatternSeedABits_15_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedABits_31_16 in AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define AQ_Pcs10G_base_rTestPatternSeedA_EUR_testPatternSeedABits_31_16 1
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedABits_31_16 in AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define bits_AQ_Pcs10G_base_rTestPatternSeedA_EUR_testPatternSeedABits_31_16 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedABits_31_16 in AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define word_AQ_Pcs10G_base_rTestPatternSeedA_EUR_testPatternSeedABits_31_16 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedABits_47_32 in AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define AQ_Pcs10G_base_rTestPatternSeedA_EUR_testPatternSeedABits_47_32 2
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedABits_47_32 in AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define bits_AQ_Pcs10G_base_rTestPatternSeedA_EUR_testPatternSeedABits_47_32 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedABits_47_32 in AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define word_AQ_Pcs10G_base_rTestPatternSeedA_EUR_testPatternSeedABits_47_32 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedABits_57_48 in AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define AQ_Pcs10G_base_rTestPatternSeedA_EUR_testPatternSeedABits_57_48 3
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedABits_57_48 in AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define bits_AQ_Pcs10G_base_rTestPatternSeedA_EUR_testPatternSeedABits_57_48 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedABits_57_48 in AQ_Pcs10G_base_rTestPatternSeedA_EUR */
#define word_AQ_Pcs10G_base_rTestPatternSeedA_EUR_testPatternSeedABits_57_48 u3.word_3

/*! \brief Base register address of structure AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define AQ_Pcs10G_base_rTestPatternSeedB_EUR_baseRegisterAddress 0x0026
/*! \brief MMD address of structure AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define AQ_Pcs10G_base_rTestPatternSeedB_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedBBits_15_0 in AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define AQ_Pcs10G_base_rTestPatternSeedB_EUR_testPatternSeedBBits_15_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedBBits_15_0 in AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define bits_AQ_Pcs10G_base_rTestPatternSeedB_EUR_testPatternSeedBBits_15_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedBBits_15_0 in AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define word_AQ_Pcs10G_base_rTestPatternSeedB_EUR_testPatternSeedBBits_15_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedBBits_31_16 in AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define AQ_Pcs10G_base_rTestPatternSeedB_EUR_testPatternSeedBBits_31_16 1
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedBBits_31_16 in AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define bits_AQ_Pcs10G_base_rTestPatternSeedB_EUR_testPatternSeedBBits_31_16 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedBBits_31_16 in AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define word_AQ_Pcs10G_base_rTestPatternSeedB_EUR_testPatternSeedBBits_31_16 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedBBits_47_32 in AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define AQ_Pcs10G_base_rTestPatternSeedB_EUR_testPatternSeedBBits_47_32 2
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedBBits_47_32 in AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define bits_AQ_Pcs10G_base_rTestPatternSeedB_EUR_testPatternSeedBBits_47_32 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedBBits_47_32 in AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define word_AQ_Pcs10G_base_rTestPatternSeedB_EUR_testPatternSeedBBits_47_32 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedBBits_57_48 in AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define AQ_Pcs10G_base_rTestPatternSeedB_EUR_testPatternSeedBBits_57_48 3
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedBBits_57_48 in AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define bits_AQ_Pcs10G_base_rTestPatternSeedB_EUR_testPatternSeedBBits_57_48 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedBBits_57_48 in AQ_Pcs10G_base_rTestPatternSeedB_EUR */
#define word_AQ_Pcs10G_base_rTestPatternSeedB_EUR_testPatternSeedBBits_57_48 u3.word_3

/*! \brief Base register address of structure AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define AQ_Pcs10G_base_rPcsTest_patternControl_EUR_baseRegisterAddress 0x002A
/*! \brief MMD address of structure AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define AQ_Pcs10G_base_rPcsTest_patternControl_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure prbs9TransmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define AQ_Pcs10G_base_rPcsTest_patternControl_EUR_prbs9TransmitTest_patternEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure prbs9TransmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_prbs9TransmitTest_patternEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure prbs9TransmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_prbs9TransmitTest_patternEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure prbs31ReceiveTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define AQ_Pcs10G_base_rPcsTest_patternControl_EUR_prbs31ReceiveTest_patternEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure prbs31ReceiveTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_prbs31ReceiveTest_patternEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure prbs31ReceiveTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_prbs31ReceiveTest_patternEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure prbs31TransmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define AQ_Pcs10G_base_rPcsTest_patternControl_EUR_prbs31TransmitTest_patternEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure prbs31TransmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_prbs31TransmitTest_patternEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure prbs31TransmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_prbs31TransmitTest_patternEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define AQ_Pcs10G_base_rPcsTest_patternControl_EUR_transmitTest_patternEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure transmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_transmitTest_patternEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure transmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_transmitTest_patternEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure receiveTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define AQ_Pcs10G_base_rPcsTest_patternControl_EUR_receiveTest_patternEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure receiveTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_receiveTest_patternEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure receiveTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_receiveTest_patternEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure test_patternSelect in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define AQ_Pcs10G_base_rPcsTest_patternControl_EUR_test_patternSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure test_patternSelect in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_test_patternSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure test_patternSelect in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_test_patternSelect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure dataPatternSelect in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define AQ_Pcs10G_base_rPcsTest_patternControl_EUR_dataPatternSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure dataPatternSelect in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_dataPatternSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure dataPatternSelect in AQ_Pcs10G_base_rPcsTest_patternControl_EUR */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_EUR_dataPatternSelect u0.word_0

/*! \brief Base register address of structure AQ_Pcs10G_base_rPcsTest_patternErrorCounter_EUR */
#define AQ_Pcs10G_base_rPcsTest_patternErrorCounter_EUR_baseRegisterAddress 0x002B
/*! \brief MMD address of structure AQ_Pcs10G_base_rPcsTest_patternErrorCounter_EUR */
#define AQ_Pcs10G_base_rPcsTest_patternErrorCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure test_patternErrorCounter in AQ_Pcs10G_base_rPcsTest_patternErrorCounter_EUR */
#define AQ_Pcs10G_base_rPcsTest_patternErrorCounter_EUR_test_patternErrorCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure test_patternErrorCounter in AQ_Pcs10G_base_rPcsTest_patternErrorCounter_EUR */
#define bits_AQ_Pcs10G_base_rPcsTest_patternErrorCounter_EUR_test_patternErrorCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure test_patternErrorCounter in AQ_Pcs10G_base_rPcsTest_patternErrorCounter_EUR */
#define word_AQ_Pcs10G_base_rPcsTest_patternErrorCounter_EUR_test_patternErrorCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsReserved_2eRegister_EUR */
#define AQ_PcsReserved_2eRegister_EUR_baseRegisterAddress 0x002E
/*! \brief MMD address of structure AQ_PcsReserved_2eRegister_EUR */
#define AQ_PcsReserved_2eRegister_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reserved2e in AQ_PcsReserved_2eRegister_EUR */
#define AQ_PcsReserved_2eRegister_EUR_reserved2e 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved2e in AQ_PcsReserved_2eRegister_EUR */
#define bits_AQ_PcsReserved_2eRegister_EUR_reserved2e u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved2e in AQ_PcsReserved_2eRegister_EUR */
#define word_AQ_PcsReserved_2eRegister_EUR_reserved2e u0.word_0

/*! \brief Base register address of structure AQ_PcsReserved_2fRegister_EUR */
#define AQ_PcsReserved_2fRegister_EUR_baseRegisterAddress 0x002F
/*! \brief MMD address of structure AQ_PcsReserved_2fRegister_EUR */
#define AQ_PcsReserved_2fRegister_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reserved2f in AQ_PcsReserved_2fRegister_EUR */
#define AQ_PcsReserved_2fRegister_EUR_reserved2f 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved2f in AQ_PcsReserved_2fRegister_EUR */
#define bits_AQ_PcsReserved_2fRegister_EUR_reserved2f u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved2f in AQ_PcsReserved_2fRegister_EUR */
#define word_AQ_PcsReserved_2fRegister_EUR_reserved2f u0.word_0

/*! \brief Base register address of structure AQ_PcsReserved_30Register_EUR */
#define AQ_PcsReserved_30Register_EUR_baseRegisterAddress 0x0030
/*! \brief MMD address of structure AQ_PcsReserved_30Register_EUR */
#define AQ_PcsReserved_30Register_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reserved30 in AQ_PcsReserved_30Register_EUR */
#define AQ_PcsReserved_30Register_EUR_reserved30 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved30 in AQ_PcsReserved_30Register_EUR */
#define bits_AQ_PcsReserved_30Register_EUR_reserved30 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved30 in AQ_PcsReserved_30Register_EUR */
#define word_AQ_PcsReserved_30Register_EUR_reserved30 u0.word_0

/*! \brief Base register address of structure AQ_PcsReserved_31Register_EUR */
#define AQ_PcsReserved_31Register_EUR_baseRegisterAddress 0x0031
/*! \brief MMD address of structure AQ_PcsReserved_31Register_EUR */
#define AQ_PcsReserved_31Register_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reserved31 in AQ_PcsReserved_31Register_EUR */
#define AQ_PcsReserved_31Register_EUR_reserved31 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved31 in AQ_PcsReserved_31Register_EUR */
#define bits_AQ_PcsReserved_31Register_EUR_reserved31 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved31 in AQ_PcsReserved_31Register_EUR */
#define word_AQ_PcsReserved_31Register_EUR_reserved31 u0.word_0

/*! \brief Base register address of structure AQ_TimesyncPcsCapability_EUR */
#define AQ_TimesyncPcsCapability_EUR_baseRegisterAddress 0x0708
/*! \brief MMD address of structure AQ_TimesyncPcsCapability_EUR */
#define AQ_TimesyncPcsCapability_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure timesyncTransmitPathDataDelay in AQ_TimesyncPcsCapability_EUR */
#define AQ_TimesyncPcsCapability_EUR_timesyncTransmitPathDataDelay 0
/*! \brief Preprocessor variable to relate field to bit position in structure timesyncTransmitPathDataDelay in AQ_TimesyncPcsCapability_EUR */
#define bits_AQ_TimesyncPcsCapability_EUR_timesyncTransmitPathDataDelay u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure timesyncTransmitPathDataDelay in AQ_TimesyncPcsCapability_EUR */
#define word_AQ_TimesyncPcsCapability_EUR_timesyncTransmitPathDataDelay u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure timesyncReceivePathDataDelay in AQ_TimesyncPcsCapability_EUR */
#define AQ_TimesyncPcsCapability_EUR_timesyncReceivePathDataDelay 0
/*! \brief Preprocessor variable to relate field to bit position in structure timesyncReceivePathDataDelay in AQ_TimesyncPcsCapability_EUR */
#define bits_AQ_TimesyncPcsCapability_EUR_timesyncReceivePathDataDelay u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure timesyncReceivePathDataDelay in AQ_TimesyncPcsCapability_EUR */
#define word_AQ_TimesyncPcsCapability_EUR_timesyncReceivePathDataDelay u0.word_0

/*! \brief Base register address of structure AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define AQ_TimesyncPcsTransmitPathDataDelay_EUR_baseRegisterAddress 0x0709
/*! \brief MMD address of structure AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define AQ_TimesyncPcsTransmitPathDataDelay_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure maximumPcsTransmitPathDataDelayLSW in AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define AQ_TimesyncPcsTransmitPathDataDelay_EUR_maximumPcsTransmitPathDataDelayLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure maximumPcsTransmitPathDataDelayLSW in AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define bits_AQ_TimesyncPcsTransmitPathDataDelay_EUR_maximumPcsTransmitPathDataDelayLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure maximumPcsTransmitPathDataDelayLSW in AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define word_AQ_TimesyncPcsTransmitPathDataDelay_EUR_maximumPcsTransmitPathDataDelayLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure maximumPcsTransmitPathDataDelayMSW in AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define AQ_TimesyncPcsTransmitPathDataDelay_EUR_maximumPcsTransmitPathDataDelayMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure maximumPcsTransmitPathDataDelayMSW in AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define bits_AQ_TimesyncPcsTransmitPathDataDelay_EUR_maximumPcsTransmitPathDataDelayMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure maximumPcsTransmitPathDataDelayMSW in AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define word_AQ_TimesyncPcsTransmitPathDataDelay_EUR_maximumPcsTransmitPathDataDelayMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure minimumPcsTransmitPathDataDelayLSW in AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define AQ_TimesyncPcsTransmitPathDataDelay_EUR_minimumPcsTransmitPathDataDelayLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure minimumPcsTransmitPathDataDelayLSW in AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define bits_AQ_TimesyncPcsTransmitPathDataDelay_EUR_minimumPcsTransmitPathDataDelayLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure minimumPcsTransmitPathDataDelayLSW in AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define word_AQ_TimesyncPcsTransmitPathDataDelay_EUR_minimumPcsTransmitPathDataDelayLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure minimumPcsTransmitPathDataDelayMSW in AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define AQ_TimesyncPcsTransmitPathDataDelay_EUR_minimumPcsTransmitPathDataDelayMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure minimumPcsTransmitPathDataDelayMSW in AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define bits_AQ_TimesyncPcsTransmitPathDataDelay_EUR_minimumPcsTransmitPathDataDelayMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure minimumPcsTransmitPathDataDelayMSW in AQ_TimesyncPcsTransmitPathDataDelay_EUR */
#define word_AQ_TimesyncPcsTransmitPathDataDelay_EUR_minimumPcsTransmitPathDataDelayMSW u3.word_3

/*! \brief Base register address of structure AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define AQ_TimesyncPcsReceivePathDataDelay_EUR_baseRegisterAddress 0x070D
/*! \brief MMD address of structure AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define AQ_TimesyncPcsReceivePathDataDelay_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure maximumPcsReceivePathDataDelayLSW in AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define AQ_TimesyncPcsReceivePathDataDelay_EUR_maximumPcsReceivePathDataDelayLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure maximumPcsReceivePathDataDelayLSW in AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define bits_AQ_TimesyncPcsReceivePathDataDelay_EUR_maximumPcsReceivePathDataDelayLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure maximumPcsReceivePathDataDelayLSW in AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define word_AQ_TimesyncPcsReceivePathDataDelay_EUR_maximumPcsReceivePathDataDelayLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure maximumPcsReceivePathDataDelayMSW in AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define AQ_TimesyncPcsReceivePathDataDelay_EUR_maximumPcsReceivePathDataDelayMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure maximumPcsReceivePathDataDelayMSW in AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define bits_AQ_TimesyncPcsReceivePathDataDelay_EUR_maximumPcsReceivePathDataDelayMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure maximumPcsReceivePathDataDelayMSW in AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define word_AQ_TimesyncPcsReceivePathDataDelay_EUR_maximumPcsReceivePathDataDelayMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure minimumPcsReceivePathDataDelayLSW in AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define AQ_TimesyncPcsReceivePathDataDelay_EUR_minimumPcsReceivePathDataDelayLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure minimumPcsReceivePathDataDelayLSW in AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define bits_AQ_TimesyncPcsReceivePathDataDelay_EUR_minimumPcsReceivePathDataDelayLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure minimumPcsReceivePathDataDelayLSW in AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define word_AQ_TimesyncPcsReceivePathDataDelay_EUR_minimumPcsReceivePathDataDelayLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure minimumPcsReceivePathDataDelayMSW in AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define AQ_TimesyncPcsReceivePathDataDelay_EUR_minimumPcsReceivePathDataDelayMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure minimumPcsReceivePathDataDelayMSW in AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define bits_AQ_TimesyncPcsReceivePathDataDelay_EUR_minimumPcsReceivePathDataDelayMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure minimumPcsReceivePathDataDelayMSW in AQ_TimesyncPcsReceivePathDataDelay_EUR */
#define word_AQ_TimesyncPcsReceivePathDataDelay_EUR_minimumPcsReceivePathDataDelayMSW u3.word_3

/*! \brief Base register address of structure AQ_PcsTransmitVendorProvisioning_EUR */
#define AQ_PcsTransmitVendorProvisioning_EUR_baseRegisterAddress 0xC400
/*! \brief MMD address of structure AQ_PcsTransmitVendorProvisioning_EUR */
#define AQ_PcsTransmitVendorProvisioning_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsTxAuxilliaryBitValue in AQ_PcsTransmitVendorProvisioning_EUR */
#define AQ_PcsTransmitVendorProvisioning_EUR_pcsTxAuxilliaryBitValue 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTxAuxilliaryBitValue in AQ_PcsTransmitVendorProvisioning_EUR */
#define bits_AQ_PcsTransmitVendorProvisioning_EUR_pcsTxAuxilliaryBitValue u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTxAuxilliaryBitValue in AQ_PcsTransmitVendorProvisioning_EUR */
#define word_AQ_PcsTransmitVendorProvisioning_EUR_pcsTxAuxilliaryBitValue u0.word_0

/*! \brief Base register address of structure AQ_PcsTransmitReservedVendorProvisioning_EUR */
#define AQ_PcsTransmitReservedVendorProvisioning_EUR_baseRegisterAddress 0xC410
/*! \brief MMD address of structure AQ_PcsTransmitReservedVendorProvisioning_EUR */
#define AQ_PcsTransmitReservedVendorProvisioning_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reservedTransmitProvisioning_1 in AQ_PcsTransmitReservedVendorProvisioning_EUR */
#define AQ_PcsTransmitReservedVendorProvisioning_EUR_reservedTransmitProvisioning_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedTransmitProvisioning_1 in AQ_PcsTransmitReservedVendorProvisioning_EUR */
#define bits_AQ_PcsTransmitReservedVendorProvisioning_EUR_reservedTransmitProvisioning_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedTransmitProvisioning_1 in AQ_PcsTransmitReservedVendorProvisioning_EUR */
#define word_AQ_PcsTransmitReservedVendorProvisioning_EUR_reservedTransmitProvisioning_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsIEEE_LoopbackPassthroughDisable in AQ_PcsTransmitReservedVendorProvisioning_EUR */
#define AQ_PcsTransmitReservedVendorProvisioning_EUR_pcsIEEE_LoopbackPassthroughDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsIEEE_LoopbackPassthroughDisable in AQ_PcsTransmitReservedVendorProvisioning_EUR */
#define bits_AQ_PcsTransmitReservedVendorProvisioning_EUR_pcsIEEE_LoopbackPassthroughDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsIEEE_LoopbackPassthroughDisable in AQ_PcsTransmitReservedVendorProvisioning_EUR */
#define word_AQ_PcsTransmitReservedVendorProvisioning_EUR_pcsIEEE_LoopbackPassthroughDisable u0.word_0

/*! \brief Base register address of structure AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define AQ_PcsTransmitXfiVendorProvisioning_EUR_baseRegisterAddress 0xC455
/*! \brief MMD address of structure AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define AQ_PcsTransmitXfiVendorProvisioning_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedAWord_0 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedAWord_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedAWord_0 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedAWord_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedAWord_0 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedAWord_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedAWord_1 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedAWord_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedAWord_1 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedAWord_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedAWord_1 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedAWord_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedAWord_2 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedAWord_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedAWord_2 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedAWord_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedAWord_2 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedAWord_2 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedAWord_3 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedAWord_3 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedAWord_3 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedAWord_3 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedAWord_3 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedAWord_3 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedBWord_0 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedBWord_0 4
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedBWord_0 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedBWord_0 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedBWord_0 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedBWord_0 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedBWord_1 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedBWord_1 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedBWord_1 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedBWord_1 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedBWord_1 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedBWord_1 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedBWord_2 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedBWord_2 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedBWord_2 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedBWord_2 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedBWord_2 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedBWord_2 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedBWord_3 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedBWord_3 7
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedBWord_3 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedBWord_3 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedBWord_3 in AQ_PcsTransmitXfiVendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfiVendorProvisioning_EUR_xfiTestPatternSeedBWord_3 u7.word_7

/*! \brief Base register address of structure AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi0VendorProvisioning_EUR_baseRegisterAddress 0xC460
/*! \brief MMD address of structure AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi0VendorProvisioning_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi0PcsScramblerDisable in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0PcsScramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0PcsScramblerDisable in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0PcsScramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi0PcsScramblerDisable in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0PcsScramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestSqaureWaveTestDuration in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestSqaureWaveTestDuration 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestSqaureWaveTestDuration in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestSqaureWaveTestDuration u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestSqaureWaveTestDuration in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestSqaureWaveTestDuration u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestDataSelect in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestDataSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestDataSelect in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestDataSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestDataSelect in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestDataSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestModeSelect in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestModeSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestModeSelect in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestModeSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestModeSelect in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestModeSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPrbs_9Enable in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestPrbs_9Enable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPrbs_9Enable in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestPrbs_9Enable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPrbs_9Enable in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestPrbs_9Enable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPrbs_31Enable in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestPrbs_31Enable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPrbs_31Enable in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestPrbs_31Enable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPrbs_31Enable in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestPrbs_31Enable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPatternEnable in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestPatternEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPatternEnable in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestPatternEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPatternEnable in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0TestPatternEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0LocalFaultInject in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0LocalFaultInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0LocalFaultInject in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0LocalFaultInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0LocalFaultInject in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0LocalFaultInject u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0InjectSingleError in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0InjectSingleError 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0InjectSingleError in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0InjectSingleError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0InjectSingleError in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0InjectSingleError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0PcsHighBerInject in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0PcsHighBerInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0PcsHighBerInject in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0PcsHighBerInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0PcsHighBerInject in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0PcsHighBerInject u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0PcsLossOfLockInject in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0PcsLossOfLockInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0PcsLossOfLockInject in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0PcsLossOfLockInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0PcsLossOfLockInject in AQ_PcsTransmitXfi0VendorProvisioning_EUR */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_EUR_xfi0PcsLossOfLockInject u1.word_1

/*! \brief Base register address of structure AQ_PcsTransmitXfi1VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi1VendorProvisioning_EUR_baseRegisterAddress 0xC470
/*! \brief MMD address of structure AQ_PcsTransmitXfi1VendorProvisioning_EUR */
#define AQ_PcsTransmitXfi1VendorProvisioning_EUR_mmdAddress 0x03

/*! \brief Base register address of structure AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define AQ_PcsSerdesMuxSwapTxrxRegister_EUR_baseRegisterAddress 0xC4F0
/*! \brief MMD address of structure AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define AQ_PcsSerdesMuxSwapTxrxRegister_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapTxLane_3 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapTxLane_3 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapTxLane_3 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapTxLane_3 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapTxLane_3 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapTxLane_3 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapTxLane_2 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapTxLane_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapTxLane_2 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapTxLane_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapTxLane_2 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapTxLane_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapTxLane_1 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapTxLane_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapTxLane_1 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapTxLane_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapTxLane_1 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapTxLane_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapTxLane_0 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapTxLane_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapTxLane_0 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapTxLane_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapTxLane_0 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapTxLane_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapRxLane_3 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapRxLane_3 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapRxLane_3 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapRxLane_3 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapRxLane_3 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapRxLane_3 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapRxLane_2 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapRxLane_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapRxLane_2 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapRxLane_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapRxLane_2 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapRxLane_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapRxLane_1 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapRxLane_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapRxLane_1 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapRxLane_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapRxLane_1 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapRxLane_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapRxLane_0 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapRxLane_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapRxLane_0 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapRxLane_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapRxLane_0 in AQ_PcsSerdesMuxSwapTxrxRegister_EUR */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_EUR_serdesMuxSwapRxLane_0 u0.word_0

/*! \brief Base register address of structure AQ_PcsTransmitTplTimestampCounter_EUR */
#define AQ_PcsTransmitTplTimestampCounter_EUR_baseRegisterAddress 0xC548
/*! \brief MMD address of structure AQ_PcsTransmitTplTimestampCounter_EUR */
#define AQ_PcsTransmitTplTimestampCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure tplEgressAverageTimestampCounter in AQ_PcsTransmitTplTimestampCounter_EUR */
#define AQ_PcsTransmitTplTimestampCounter_EUR_tplEgressAverageTimestampCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure tplEgressAverageTimestampCounter in AQ_PcsTransmitTplTimestampCounter_EUR */
#define bits_AQ_PcsTransmitTplTimestampCounter_EUR_tplEgressAverageTimestampCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tplEgressAverageTimestampCounter in AQ_PcsTransmitTplTimestampCounter_EUR */
#define word_AQ_PcsTransmitTplTimestampCounter_EUR_tplEgressAverageTimestampCounter u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tplEgressMaxTimestampCounter in AQ_PcsTransmitTplTimestampCounter_EUR */
#define AQ_PcsTransmitTplTimestampCounter_EUR_tplEgressMaxTimestampCounter 1
/*! \brief Preprocessor variable to relate field to bit position in structure tplEgressMaxTimestampCounter in AQ_PcsTransmitTplTimestampCounter_EUR */
#define bits_AQ_PcsTransmitTplTimestampCounter_EUR_tplEgressMaxTimestampCounter u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure tplEgressMaxTimestampCounter in AQ_PcsTransmitTplTimestampCounter_EUR */
#define word_AQ_PcsTransmitTplTimestampCounter_EUR_tplEgressMaxTimestampCounter u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure tplEgressMinTimestampCounter in AQ_PcsTransmitTplTimestampCounter_EUR */
#define AQ_PcsTransmitTplTimestampCounter_EUR_tplEgressMinTimestampCounter 2
/*! \brief Preprocessor variable to relate field to bit position in structure tplEgressMinTimestampCounter in AQ_PcsTransmitTplTimestampCounter_EUR */
#define bits_AQ_PcsTransmitTplTimestampCounter_EUR_tplEgressMinTimestampCounter u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure tplEgressMinTimestampCounter in AQ_PcsTransmitTplTimestampCounter_EUR */
#define word_AQ_PcsTransmitTplTimestampCounter_EUR_tplEgressMinTimestampCounter u2.word_2

/*! \brief Base register address of structure AQ_PcsTransmitTgeVendorTimestampCounter_EUR */
#define AQ_PcsTransmitTgeVendorTimestampCounter_EUR_baseRegisterAddress 0xC568
/*! \brief MMD address of structure AQ_PcsTransmitTgeVendorTimestampCounter_EUR */
#define AQ_PcsTransmitTgeVendorTimestampCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure tgeEgressAverageTimestampCounter in AQ_PcsTransmitTgeVendorTimestampCounter_EUR */
#define AQ_PcsTransmitTgeVendorTimestampCounter_EUR_tgeEgressAverageTimestampCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure tgeEgressAverageTimestampCounter in AQ_PcsTransmitTgeVendorTimestampCounter_EUR */
#define bits_AQ_PcsTransmitTgeVendorTimestampCounter_EUR_tgeEgressAverageTimestampCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tgeEgressAverageTimestampCounter in AQ_PcsTransmitTgeVendorTimestampCounter_EUR */
#define word_AQ_PcsTransmitTgeVendorTimestampCounter_EUR_tgeEgressAverageTimestampCounter u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tgeEgressMaxTimestampCounter in AQ_PcsTransmitTgeVendorTimestampCounter_EUR */
#define AQ_PcsTransmitTgeVendorTimestampCounter_EUR_tgeEgressMaxTimestampCounter 1
/*! \brief Preprocessor variable to relate field to bit position in structure tgeEgressMaxTimestampCounter in AQ_PcsTransmitTgeVendorTimestampCounter_EUR */
#define bits_AQ_PcsTransmitTgeVendorTimestampCounter_EUR_tgeEgressMaxTimestampCounter u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure tgeEgressMaxTimestampCounter in AQ_PcsTransmitTgeVendorTimestampCounter_EUR */
#define word_AQ_PcsTransmitTgeVendorTimestampCounter_EUR_tgeEgressMaxTimestampCounter u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure tgeEgressMinTimestampCounter in AQ_PcsTransmitTgeVendorTimestampCounter_EUR */
#define AQ_PcsTransmitTgeVendorTimestampCounter_EUR_tgeEgressMinTimestampCounter 2
/*! \brief Preprocessor variable to relate field to bit position in structure tgeEgressMinTimestampCounter in AQ_PcsTransmitTgeVendorTimestampCounter_EUR */
#define bits_AQ_PcsTransmitTgeVendorTimestampCounter_EUR_tgeEgressMinTimestampCounter u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure tgeEgressMinTimestampCounter in AQ_PcsTransmitTgeVendorTimestampCounter_EUR */
#define word_AQ_PcsTransmitTgeVendorTimestampCounter_EUR_tgeEgressMinTimestampCounter u2.word_2

/*! \brief Base register address of structure AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_baseRegisterAddress 0xC620
/*! \brief MMD address of structure AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressVlanTaggingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressVlanTaggingEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressVlanTaggingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressVlanTaggingEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressVlanTaggingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressVlanTaggingEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv6_udpEncapsulatedEnabled in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6_udpEncapsulatedEnabled 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv6_udpEncapsulatedEnabled in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6_udpEncapsulatedEnabled u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv6_udpEncapsulatedEnabled in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6_udpEncapsulatedEnabled u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv4_udpEncapsulatedEnabled in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv4_udpEncapsulatedEnabled 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv4_udpEncapsulatedEnabled in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv4_udpEncapsulatedEnabled u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv4_udpEncapsulatedEnabled in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv4_udpEncapsulatedEnabled u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressEthernetEncapsulatedEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressEthernetEncapsulatedEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressEthernetEncapsulatedEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressEthernetEncapsulatedEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressEthernetEncapsulatedEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressEthernetEncapsulatedEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressNtpConfiguration in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtpConfiguration 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressNtpConfiguration in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtpConfiguration u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressNtpConfiguration in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtpConfiguration u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressBackPressureEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressBackPressureEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressBackPressureEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressBackPressureEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressBackPressureEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressBackPressureEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressNtpEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtpEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressNtpEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtpEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressNtpEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtpEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgress_1588Version_2Enable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_2Enable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgress_1588Version_2Enable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_2Enable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgress_1588Version_2Enable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_2Enable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgress_1588Version_1Enable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_1Enable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgress_1588Version_1Enable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_1Enable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgress_1588Version_1Enable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_1Enable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv6DestinationAddressMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressMatchingEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv6DestinationAddressMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressMatchingEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv6DestinationAddressMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressMatchingEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv4DestinationAddressMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv4DestinationAddressMatchingEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv4DestinationAddressMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv4DestinationAddressMatchingEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv4DestinationAddressMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv4DestinationAddressMatchingEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressMacDestinationAddressMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressMacDestinationAddressMatchingEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressMacDestinationAddressMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressMacDestinationAddressMatchingEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressMacDestinationAddressMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressMacDestinationAddressMatchingEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressEthertypeMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressEthertypeMatchingEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressEthertypeMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressEthertypeMatchingEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressEthertypeMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressEthertypeMatchingEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressNtp_sntpVersion in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtp_sntpVersion 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressNtp_sntpVersion in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtp_sntpVersion u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressNtp_sntpVersion in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtp_sntpVersion u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgress_1588Version in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgress_1588Version in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgress_1588Version in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgress_1588_2StepEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588_2StepEnable 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgress_1588_2StepEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588_2StepEnable u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgress_1588_2StepEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588_2StepEnable u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgress_1588Version_2DomainMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_2DomainMatchingEnable 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgress_1588Version_2DomainMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_2DomainMatchingEnable u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgress_1588Version_2DomainMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_2DomainMatchingEnable u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressUdpDestinationPortMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressUdpDestinationPortMatchingEnable 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressUdpDestinationPortMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressUdpDestinationPortMatchingEnable u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressUdpDestinationPortMatchingEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressUdpDestinationPortMatchingEnable u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressEthertype in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressEthertype 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressEthertype in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressEthertype u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressEthertype in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressEthertype u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressMacDestinationAddressBits_15_0 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressMacDestinationAddressBits_15_0 4
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressMacDestinationAddressBits_15_0 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressMacDestinationAddressBits_15_0 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressMacDestinationAddressBits_15_0 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressMacDestinationAddressBits_15_0 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressMacDestinationAddressBits_31_16 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressMacDestinationAddressBits_31_16 5
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressMacDestinationAddressBits_31_16 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressMacDestinationAddressBits_31_16 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressMacDestinationAddressBits_31_16 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressMacDestinationAddressBits_31_16 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressMacDestinationAddressBits_47_32 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressMacDestinationAddressBits_47_32 6
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressMacDestinationAddressBits_47_32 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressMacDestinationAddressBits_47_32 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressMacDestinationAddressBits_47_32 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressMacDestinationAddressBits_47_32 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv4DestinationAddressLSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv4DestinationAddressLSW 7
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv4DestinationAddressLSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv4DestinationAddressLSW u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv4DestinationAddressLSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv4DestinationAddressLSW u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv4DestinationAddressMSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv4DestinationAddressMSW 8
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv4DestinationAddressMSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv4DestinationAddressMSW u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv4DestinationAddressMSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv4DestinationAddressMSW u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv6DestinationAddressBits_15_0 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_15_0 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv6DestinationAddressBits_15_0 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_15_0 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv6DestinationAddressBits_15_0 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_15_0 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv6DestinationAddressBits_31_16 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_31_16 10
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv6DestinationAddressBits_31_16 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_31_16 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv6DestinationAddressBits_31_16 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_31_16 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv6DestinationAddressBits_47_32 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_47_32 11
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv6DestinationAddressBits_47_32 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_47_32 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv6DestinationAddressBits_47_32 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_47_32 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv6DestinationAddressBits_63_48 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_63_48 12
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv6DestinationAddressBits_63_48 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_63_48 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv6DestinationAddressBits_63_48 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_63_48 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv6DestinationAddressBits_79_64 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_79_64 13
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv6DestinationAddressBits_79_64 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_79_64 u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv6DestinationAddressBits_79_64 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_79_64 u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv6DestinationAddressBits_95_80 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_95_80 14
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv6DestinationAddressBits_95_80 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_95_80 u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv6DestinationAddressBits_95_80 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_95_80 u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv6DestinationAddressBits_111_96 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_111_96 15
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv6DestinationAddressBits_111_96 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_111_96 u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv6DestinationAddressBits_111_96 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_111_96 u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressIpv6DestinationAddressBits_127_112 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_127_112 16
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressIpv6DestinationAddressBits_127_112 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_127_112 u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressIpv6DestinationAddressBits_127_112 in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressIpv6DestinationAddressBits_127_112 u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressUdpDestinationPort in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressUdpDestinationPort 17
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressUdpDestinationPort in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressUdpDestinationPort u17.bits_17
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressUdpDestinationPort in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressUdpDestinationPort u17.word_17
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgress_1588Version_2Domain in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_2Domain 18
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgress_1588Version_2Domain in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_2Domain u18.bits_18
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgress_1588Version_2Domain in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_2Domain u18.word_18
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressCorrectionOffsetSign in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressCorrectionOffsetSign 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressCorrectionOffsetSign in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressCorrectionOffsetSign u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressCorrectionOffsetSign in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressCorrectionOffsetSign u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressTimeStampOffsetSign in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressTimeStampOffsetSign 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressTimeStampOffsetSign in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressTimeStampOffsetSign u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressTimeStampOffsetSign in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressTimeStampOffsetSign u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressSetTimeStampOffset in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressSetTimeStampOffset 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressSetTimeStampOffset in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressSetTimeStampOffset u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressSetTimeStampOffset in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressSetTimeStampOffset u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressByteSwap in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressByteSwap 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressByteSwap in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressByteSwap u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressByteSwap in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressByteSwap u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressTimeStampNanosecondOffset in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressTimeStampNanosecondOffset 20
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressTimeStampNanosecondOffset in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressTimeStampNanosecondOffset u20.bits_20
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressTimeStampNanosecondOffset in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressTimeStampNanosecondOffset u20.word_20
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressTimeStampFractionalSecondOffsetLSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressTimeStampFractionalSecondOffsetLSW 21
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressTimeStampFractionalSecondOffsetLSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressTimeStampFractionalSecondOffsetLSW u21.bits_21
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressTimeStampFractionalSecondOffsetLSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressTimeStampFractionalSecondOffsetLSW u21.word_21
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressTimeStampFractionalSecondOffsetMSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressTimeStampFractionalSecondOffsetMSW 22
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressTimeStampFractionalSecondOffsetMSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressTimeStampFractionalSecondOffsetMSW u22.bits_22
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressTimeStampFractionalSecondOffsetMSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressTimeStampFractionalSecondOffsetMSW u22.word_22
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressCorrectionOffsetLSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressCorrectionOffsetLSW 23
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressCorrectionOffsetLSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressCorrectionOffsetLSW u23.bits_23
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressCorrectionOffsetLSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressCorrectionOffsetLSW u23.word_23
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressCorrectionOffsetMSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressCorrectionOffsetMSW 24
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressCorrectionOffsetMSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressCorrectionOffsetMSW u24.bits_24
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressCorrectionOffsetMSW in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressCorrectionOffsetMSW u24.word_24
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketAction in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketAction 25
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketAction in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketAction u25.bits_25
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketAction in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketAction u25.word_25
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressNtp_sntpTimeStampAction in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtp_sntpTimeStampAction 26
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressNtp_sntpTimeStampAction in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtp_sntpTimeStampAction u26.bits_26
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressNtp_sntpTimeStampAction in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtp_sntpTimeStampAction u26.word_26
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressNtp_sntpPacketAction in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtp_sntpPacketAction 26
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressNtp_sntpPacketAction in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtp_sntpPacketAction u26.bits_26
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressNtp_sntpPacketAction in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressNtp_sntpPacketAction u26.word_26
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketBufferReset in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketBufferReset 30
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketBufferReset in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketBufferReset u30.bits_30
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketBufferReset in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketBufferReset u30.word_30
/*! \brief Preprocessor variable to relate field to word number in structure ptpUsxTimestampFifoReset in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpUsxTimestampFifoReset 30
/*! \brief Preprocessor variable to relate field to bit position in structure ptpUsxTimestampFifoReset in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpUsxTimestampFifoReset u30.bits_30
/*! \brief Preprocessor variable to relate field to word position in structure ptpUsxTimestampFifoReset in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpUsxTimestampFifoReset u30.word_30
/*! \brief Preprocessor variable to relate field to word number in structure ptpUsxTimestampFifoSelect in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpUsxTimestampFifoSelect 30
/*! \brief Preprocessor variable to relate field to bit position in structure ptpUsxTimestampFifoSelect in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpUsxTimestampFifoSelect u30.bits_30
/*! \brief Preprocessor variable to relate field to word position in structure ptpUsxTimestampFifoSelect in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpUsxTimestampFifoSelect u30.word_30
/*! \brief Preprocessor variable to relate field to word number in structure ptpUsxTimestampFifoReadEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpUsxTimestampFifoReadEnable 30
/*! \brief Preprocessor variable to relate field to bit position in structure ptpUsxTimestampFifoReadEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpUsxTimestampFifoReadEnable u30.bits_30
/*! \brief Preprocessor variable to relate field to word position in structure ptpUsxTimestampFifoReadEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpUsxTimestampFifoReadEnable u30.word_30
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketBufferReadEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketBufferReadEnable 30
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketBufferReadEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketBufferReadEnable u30.bits_30
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketBufferReadEnable in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketBufferReadEnable u30.word_30
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketPause in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketPause 31
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketPause in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketPause u31.bits_31
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketPause in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketPause u31.word_31
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketSizeLimit in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketSizeLimit 31
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketSizeLimit in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketSizeLimit u31.bits_31
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketSizeLimit in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgressPacketSizeLimit u31.word_31
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgress_1588Version_2MessageMask in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_2MessageMask 38
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgress_1588Version_2MessageMask in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_2MessageMask u38.bits_38
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgress_1588Version_2MessageMask in AQ_PcsPtpEgressVendorProvisioning_EUR */
#define word_AQ_PcsPtpEgressVendorProvisioning_EUR_ptpEgress_1588Version_2MessageMask u38.word_38

/*! \brief Base register address of structure AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR */
#define AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR_baseRegisterAddress 0xC820
/*! \brief MMD address of structure AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR */
#define AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR */
#define AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR__10gbase_tGoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR */
#define bits_AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR__10gbase_tGoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR */
#define word_AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR__10gbase_tGoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR */
#define AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR__10gbase_tGoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR */
#define bits_AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR__10gbase_tGoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR */
#define word_AQ_PcsTransmitVendorFcsNoErrorFrameCounter_EUR__10gbase_tGoodFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR */
#define AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR_baseRegisterAddress 0xC822
/*! \brief MMD address of structure AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR */
#define AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR */
#define AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR__10gbase_tErrorFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR */
#define bits_AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR__10gbase_tErrorFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR */
#define word_AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR__10gbase_tErrorFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR */
#define AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR__10gbase_tErrorFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR */
#define bits_AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR__10gbase_tErrorFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR */
#define word_AQ_PcsTransmitVendorFcsErrorFrameCounter_EUR__10gbase_tErrorFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsTransmitXfi0VendorState_EUR */
#define AQ_PcsTransmitXfi0VendorState_EUR_baseRegisterAddress 0xC860
/*! \brief MMD address of structure AQ_PcsTransmitXfi0VendorState_EUR */
#define AQ_PcsTransmitXfi0VendorState_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi0GoodFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_EUR */
#define AQ_PcsTransmitXfi0VendorState_EUR_xfi0GoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0GoodFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_EUR */
#define bits_AQ_PcsTransmitXfi0VendorState_EUR_xfi0GoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi0GoodFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_EUR */
#define word_AQ_PcsTransmitXfi0VendorState_EUR_xfi0GoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi0GoodFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_EUR */
#define AQ_PcsTransmitXfi0VendorState_EUR_xfi0GoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0GoodFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_EUR */
#define bits_AQ_PcsTransmitXfi0VendorState_EUR_xfi0GoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0GoodFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_EUR */
#define word_AQ_PcsTransmitXfi0VendorState_EUR_xfi0GoodFrameCounterMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BadFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_EUR */
#define AQ_PcsTransmitXfi0VendorState_EUR_xfi0BadFrameCounterLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BadFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_EUR */
#define bits_AQ_PcsTransmitXfi0VendorState_EUR_xfi0BadFrameCounterLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BadFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_EUR */
#define word_AQ_PcsTransmitXfi0VendorState_EUR_xfi0BadFrameCounterLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BadFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_EUR */
#define AQ_PcsTransmitXfi0VendorState_EUR_xfi0BadFrameCounterMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BadFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_EUR */
#define bits_AQ_PcsTransmitXfi0VendorState_EUR_xfi0BadFrameCounterMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BadFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_EUR */
#define word_AQ_PcsTransmitXfi0VendorState_EUR_xfi0BadFrameCounterMSW u3.word_3

/*! \brief Base register address of structure AQ_PcsTransmitXfi1VendorState_EUR */
#define AQ_PcsTransmitXfi1VendorState_EUR_baseRegisterAddress 0xC870
/*! \brief MMD address of structure AQ_PcsTransmitXfi1VendorState_EUR */
#define AQ_PcsTransmitXfi1VendorState_EUR_mmdAddress 0x03

/*! \brief Base register address of structure AQ_PcsTransmitXgsVendorState_EUR */
#define AQ_PcsTransmitXgsVendorState_EUR_baseRegisterAddress 0xC880
/*! \brief MMD address of structure AQ_PcsTransmitXgsVendorState_EUR */
#define AQ_PcsTransmitXgsVendorState_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_0 in AQ_PcsTransmitXgsVendorState_EUR */
#define AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_0 in AQ_PcsTransmitXgsVendorState_EUR */
#define bits_AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_0 in AQ_PcsTransmitXgsVendorState_EUR */
#define word_AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_1 in AQ_PcsTransmitXgsVendorState_EUR */
#define AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_1 in AQ_PcsTransmitXgsVendorState_EUR */
#define bits_AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_1 in AQ_PcsTransmitXgsVendorState_EUR */
#define word_AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_2 in AQ_PcsTransmitXgsVendorState_EUR */
#define AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_2 in AQ_PcsTransmitXgsVendorState_EUR */
#define bits_AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_2 in AQ_PcsTransmitXgsVendorState_EUR */
#define word_AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_2 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_3 in AQ_PcsTransmitXgsVendorState_EUR */
#define AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_3 3
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_3 in AQ_PcsTransmitXgsVendorState_EUR */
#define bits_AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_3 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_3 in AQ_PcsTransmitXgsVendorState_EUR */
#define word_AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_3 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_4 in AQ_PcsTransmitXgsVendorState_EUR */
#define AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_4 4
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_4 in AQ_PcsTransmitXgsVendorState_EUR */
#define bits_AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_4 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_4 in AQ_PcsTransmitXgsVendorState_EUR */
#define word_AQ_PcsTransmitXgsVendorState_EUR_xgsCollisionEventsCounter_4 u4.word_4

/*! \brief Base register address of structure AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_baseRegisterAddress 0xC900
/*! \brief MMD address of structure AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockSecondsCountBits_15_0 in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpDigitalClockSecondsCountBits_15_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockSecondsCountBits_15_0 in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpDigitalClockSecondsCountBits_15_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockSecondsCountBits_15_0 in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpDigitalClockSecondsCountBits_15_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockSecondsCountBits_31_16 in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpDigitalClockSecondsCountBits_31_16 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockSecondsCountBits_31_16 in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpDigitalClockSecondsCountBits_31_16 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockSecondsCountBits_31_16 in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpDigitalClockSecondsCountBits_31_16 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockSecondsCountBits_47_32 in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpDigitalClockSecondsCountBits_47_32 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockSecondsCountBits_47_32 in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpDigitalClockSecondsCountBits_47_32 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockSecondsCountBits_47_32 in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpDigitalClockSecondsCountBits_47_32 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpDigitalClockNanosecondsCountLSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpDigitalClockNanosecondsCountLSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpDigitalClockNanosecondsCountLSW u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpDigitalClockNanosecondsCountMSW 4
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpDigitalClockNanosecondsCountMSW u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpDigitalClockNanosecondsCountMSW u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpDigitalClockFractionalNanosecondsCountLSW 5
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpDigitalClockFractionalNanosecondsCountLSW u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpDigitalClockFractionalNanosecondsCountLSW u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpDigitalClockFractionalNanosecondsCountMSW 6
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpDigitalClockFractionalNanosecondsCountMSW u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpDigitalClockFractionalNanosecondsCountMSW u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpDigitalClockFractionalSecondsCountLSW 7
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpDigitalClockFractionalSecondsCountLSW u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpDigitalClockFractionalSecondsCountLSW u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpDigitalClockFractionalSecondsCountMSW 8
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpDigitalClockFractionalSecondsCountMSW u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpDigitalClockFractionalSecondsCountMSW u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockCountLSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalClockCountLSW 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockCountLSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalClockCountLSW u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockCountLSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalClockCountLSW u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockCountMSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalClockCountMSW 10
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockCountMSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalClockCountMSW u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockCountMSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalClockCountMSW u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockSecondsCountBits_15_0 in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalClockSecondsCountBits_15_0 11
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockSecondsCountBits_15_0 in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalClockSecondsCountBits_15_0 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockSecondsCountBits_15_0 in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalClockSecondsCountBits_15_0 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockSecondsCountBits_31_16 in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalClockSecondsCountBits_31_16 12
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockSecondsCountBits_31_16 in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalClockSecondsCountBits_31_16 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockSecondsCountBits_31_16 in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalClockSecondsCountBits_31_16 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockSecondsCountBits_47_32 in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalClockSecondsCountBits_47_32 13
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockSecondsCountBits_47_32 in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalClockSecondsCountBits_47_32 u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockSecondsCountBits_47_32 in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalClockSecondsCountBits_47_32 u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalClockNanosecondsCountLSW 14
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalClockNanosecondsCountLSW u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalClockNanosecondsCountLSW u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalClockNanosecondsCountMSW 15
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalClockNanosecondsCountMSW u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalClockNanosecondsCountMSW u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalClockFractionalNanosecondsCountLSW 16
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalClockFractionalNanosecondsCountLSW u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalClockFractionalNanosecondsCountLSW u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalClockFractionalNanosecondsCountMSW 17
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalClockFractionalNanosecondsCountMSW u17.bits_17
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalClockFractionalNanosecondsCountMSW u17.word_17
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalClockFractionalSecondsCountLSW 18
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalClockFractionalSecondsCountLSW u18.bits_18
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalClockFractionalSecondsCountLSW u18.word_18
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalClockFractionalSecondsCountMSW 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalClockFractionalSecondsCountMSW u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalClockFractionalSecondsCountMSW u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockSecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockSecondsCountLSW 20
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockSecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockSecondsCountLSW u20.bits_20
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockSecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockSecondsCountLSW u20.word_20
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockSecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockSecondsCountMSW 21
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockSecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockSecondsCountMSW u21.bits_21
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockSecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockSecondsCountMSW u21.word_21
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockNanosecondsCountLSW 22
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockNanosecondsCountLSW u22.bits_22
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockNanosecondsCountLSW u22.word_22
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockNanosecondsCountMSW 23
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockNanosecondsCountMSW u23.bits_23
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockNanosecondsCountMSW u23.word_23
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockFractionalNanosecondsCountLSW 24
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockFractionalNanosecondsCountLSW u24.bits_24
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockFractionalNanosecondsCountLSW u24.word_24
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockFractionalNanosecondsCountMSW 25
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockFractionalNanosecondsCountMSW u25.bits_25
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockFractionalNanosecondsCountMSW u25.word_25
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockFractionalSecondsCountLSW 26
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockFractionalSecondsCountLSW u26.bits_26
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockFractionalSecondsCountLSW u26.word_26
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockFractionalSecondsCountMSW 27
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockFractionalSecondsCountMSW u27.bits_27
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockFractionalSecondsCountMSW u27.word_27
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockUpdateDone in AQ_PcsPtpVendorState_EUR */
#define AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockUpdateDone 28
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockUpdateDone in AQ_PcsPtpVendorState_EUR */
#define bits_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockUpdateDone u28.bits_28
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockUpdateDone in AQ_PcsPtpVendorState_EUR */
#define word_AQ_PcsPtpVendorState_EUR_ptpExternalGpioClockUpdateDone u28.word_28

/*! \brief Base register address of structure AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_baseRegisterAddress 0xC930
/*! \brief MMD address of structure AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketCount in AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketCount 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketCount in AQ_PcsPtpEgressVendorState_EUR */
#define bits_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketCount u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketCount in AQ_PcsPtpEgressVendorState_EUR */
#define word_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketCount u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketDataLSW in AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketDataLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketDataLSW in AQ_PcsPtpEgressVendorState_EUR */
#define bits_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketDataLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketDataLSW in AQ_PcsPtpEgressVendorState_EUR */
#define word_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketDataLSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketDataMSW in AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketDataMSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketDataMSW in AQ_PcsPtpEgressVendorState_EUR */
#define bits_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketDataMSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketDataMSW in AQ_PcsPtpEgressVendorState_EUR */
#define word_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketDataMSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketTruncated in AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketTruncated 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketTruncated in AQ_PcsPtpEgressVendorState_EUR */
#define bits_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketTruncated u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketTruncated in AQ_PcsPtpEgressVendorState_EUR */
#define word_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketTruncated u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketEop in AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketEop 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketEop in AQ_PcsPtpEgressVendorState_EUR */
#define bits_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketEop u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketEop in AQ_PcsPtpEgressVendorState_EUR */
#define word_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketEop u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketSop in AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketSop 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketSop in AQ_PcsPtpEgressVendorState_EUR */
#define bits_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketSop u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketSop in AQ_PcsPtpEgressVendorState_EUR */
#define word_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketSop u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketTimeStampCount in AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketTimeStampCount 4
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketTimeStampCount in AQ_PcsPtpEgressVendorState_EUR */
#define bits_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketTimeStampCount u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketTimeStampCount in AQ_PcsPtpEgressVendorState_EUR */
#define word_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketTimeStampCount u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketTimeStamp in AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketTimeStamp 5
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketTimeStamp in AQ_PcsPtpEgressVendorState_EUR */
#define bits_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketTimeStamp u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketTimeStamp in AQ_PcsPtpEgressVendorState_EUR */
#define word_AQ_PcsPtpEgressVendorState_EUR_ptpEgressPacketTimeStamp u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressRxPacketInformation in AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_ptpEgressRxPacketInformation 6
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressRxPacketInformation in AQ_PcsPtpEgressVendorState_EUR */
#define bits_AQ_PcsPtpEgressVendorState_EUR_ptpEgressRxPacketInformation u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressRxPacketInformation in AQ_PcsPtpEgressVendorState_EUR */
#define word_AQ_PcsPtpEgressVendorState_EUR_ptpEgressRxPacketInformation u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure ptpUsxTimestampFifoCount in AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_ptpUsxTimestampFifoCount 7
/*! \brief Preprocessor variable to relate field to bit position in structure ptpUsxTimestampFifoCount in AQ_PcsPtpEgressVendorState_EUR */
#define bits_AQ_PcsPtpEgressVendorState_EUR_ptpUsxTimestampFifoCount u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure ptpUsxTimestampFifoCount in AQ_PcsPtpEgressVendorState_EUR */
#define word_AQ_PcsPtpEgressVendorState_EUR_ptpUsxTimestampFifoCount u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure ptpUsxTimestampFifoData_0 in AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_ptpUsxTimestampFifoData_0 8
/*! \brief Preprocessor variable to relate field to bit position in structure ptpUsxTimestampFifoData_0 in AQ_PcsPtpEgressVendorState_EUR */
#define bits_AQ_PcsPtpEgressVendorState_EUR_ptpUsxTimestampFifoData_0 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure ptpUsxTimestampFifoData_0 in AQ_PcsPtpEgressVendorState_EUR */
#define word_AQ_PcsPtpEgressVendorState_EUR_ptpUsxTimestampFifoData_0 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure ptpUsxTimestampFifoData_1 in AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_ptpUsxTimestampFifoData_1 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpUsxTimestampFifoData_1 in AQ_PcsPtpEgressVendorState_EUR */
#define bits_AQ_PcsPtpEgressVendorState_EUR_ptpUsxTimestampFifoData_1 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpUsxTimestampFifoData_1 in AQ_PcsPtpEgressVendorState_EUR */
#define word_AQ_PcsPtpEgressVendorState_EUR_ptpUsxTimestampFifoData_1 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpUsxTimestampFifoData_2 in AQ_PcsPtpEgressVendorState_EUR */
#define AQ_PcsPtpEgressVendorState_EUR_ptpUsxTimestampFifoData_2 10
/*! \brief Preprocessor variable to relate field to bit position in structure ptpUsxTimestampFifoData_2 in AQ_PcsPtpEgressVendorState_EUR */
#define bits_AQ_PcsPtpEgressVendorState_EUR_ptpUsxTimestampFifoData_2 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure ptpUsxTimestampFifoData_2 in AQ_PcsPtpEgressVendorState_EUR */
#define word_AQ_PcsPtpEgressVendorState_EUR_ptpUsxTimestampFifoData_2 u10.word_10

/*! \brief Base register address of structure AQ_PcsTransmitSecVendorTimestampCounter_EUR */
#define AQ_PcsTransmitSecVendorTimestampCounter_EUR_baseRegisterAddress 0xC980
/*! \brief MMD address of structure AQ_PcsTransmitSecVendorTimestampCounter_EUR */
#define AQ_PcsTransmitSecVendorTimestampCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure secIngressAverageTimestampCounter in AQ_PcsTransmitSecVendorTimestampCounter_EUR */
#define AQ_PcsTransmitSecVendorTimestampCounter_EUR_secIngressAverageTimestampCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure secIngressAverageTimestampCounter in AQ_PcsTransmitSecVendorTimestampCounter_EUR */
#define bits_AQ_PcsTransmitSecVendorTimestampCounter_EUR_secIngressAverageTimestampCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure secIngressAverageTimestampCounter in AQ_PcsTransmitSecVendorTimestampCounter_EUR */
#define word_AQ_PcsTransmitSecVendorTimestampCounter_EUR_secIngressAverageTimestampCounter u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure secIngressMaxTimestampCounter in AQ_PcsTransmitSecVendorTimestampCounter_EUR */
#define AQ_PcsTransmitSecVendorTimestampCounter_EUR_secIngressMaxTimestampCounter 1
/*! \brief Preprocessor variable to relate field to bit position in structure secIngressMaxTimestampCounter in AQ_PcsTransmitSecVendorTimestampCounter_EUR */
#define bits_AQ_PcsTransmitSecVendorTimestampCounter_EUR_secIngressMaxTimestampCounter u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure secIngressMaxTimestampCounter in AQ_PcsTransmitSecVendorTimestampCounter_EUR */
#define word_AQ_PcsTransmitSecVendorTimestampCounter_EUR_secIngressMaxTimestampCounter u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure secIngressMinTimestampCounter in AQ_PcsTransmitSecVendorTimestampCounter_EUR */
#define AQ_PcsTransmitSecVendorTimestampCounter_EUR_secIngressMinTimestampCounter 2
/*! \brief Preprocessor variable to relate field to bit position in structure secIngressMinTimestampCounter in AQ_PcsTransmitSecVendorTimestampCounter_EUR */
#define bits_AQ_PcsTransmitSecVendorTimestampCounter_EUR_secIngressMinTimestampCounter u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure secIngressMinTimestampCounter in AQ_PcsTransmitSecVendorTimestampCounter_EUR */
#define word_AQ_PcsTransmitSecVendorTimestampCounter_EUR_secIngressMinTimestampCounter u2.word_2

/*! \brief Base register address of structure AQ_PcsSecL2StatisticsConfiguration_EUR */
#define AQ_PcsSecL2StatisticsConfiguration_EUR_baseRegisterAddress 0xC9A0
/*! \brief MMD address of structure AQ_PcsSecL2StatisticsConfiguration_EUR */
#define AQ_PcsSecL2StatisticsConfiguration_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure secIngressL2CounterSelect in AQ_PcsSecL2StatisticsConfiguration_EUR */
#define AQ_PcsSecL2StatisticsConfiguration_EUR_secIngressL2CounterSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure secIngressL2CounterSelect in AQ_PcsSecL2StatisticsConfiguration_EUR */
#define bits_AQ_PcsSecL2StatisticsConfiguration_EUR_secIngressL2CounterSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure secIngressL2CounterSelect in AQ_PcsSecL2StatisticsConfiguration_EUR */
#define word_AQ_PcsSecL2StatisticsConfiguration_EUR_secIngressL2CounterSelect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure secEgressL2CounterSelect in AQ_PcsSecL2StatisticsConfiguration_EUR */
#define AQ_PcsSecL2StatisticsConfiguration_EUR_secEgressL2CounterSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure secEgressL2CounterSelect in AQ_PcsSecL2StatisticsConfiguration_EUR */
#define bits_AQ_PcsSecL2StatisticsConfiguration_EUR_secEgressL2CounterSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure secEgressL2CounterSelect in AQ_PcsSecL2StatisticsConfiguration_EUR */
#define word_AQ_PcsSecL2StatisticsConfiguration_EUR_secEgressL2CounterSelect u0.word_0

/*! \brief Base register address of structure AQ_PcsIngressSecL2Counter_EUR */
#define AQ_PcsIngressSecL2Counter_EUR_baseRegisterAddress 0xC9A4
/*! \brief MMD address of structure AQ_PcsIngressSecL2Counter_EUR */
#define AQ_PcsIngressSecL2Counter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure secIngressL2CounterLSW in AQ_PcsIngressSecL2Counter_EUR */
#define AQ_PcsIngressSecL2Counter_EUR_secIngressL2CounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure secIngressL2CounterLSW in AQ_PcsIngressSecL2Counter_EUR */
#define bits_AQ_PcsIngressSecL2Counter_EUR_secIngressL2CounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure secIngressL2CounterLSW in AQ_PcsIngressSecL2Counter_EUR */
#define word_AQ_PcsIngressSecL2Counter_EUR_secIngressL2CounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure secIngressL2CounterMSW in AQ_PcsIngressSecL2Counter_EUR */
#define AQ_PcsIngressSecL2Counter_EUR_secIngressL2CounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure secIngressL2CounterMSW in AQ_PcsIngressSecL2Counter_EUR */
#define bits_AQ_PcsIngressSecL2Counter_EUR_secIngressL2CounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure secIngressL2CounterMSW in AQ_PcsIngressSecL2Counter_EUR */
#define word_AQ_PcsIngressSecL2Counter_EUR_secIngressL2CounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsEgressSecL2Counter_EUR */
#define AQ_PcsEgressSecL2Counter_EUR_baseRegisterAddress 0xC9B0
/*! \brief MMD address of structure AQ_PcsEgressSecL2Counter_EUR */
#define AQ_PcsEgressSecL2Counter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure secEgressL2CounterLSW in AQ_PcsEgressSecL2Counter_EUR */
#define AQ_PcsEgressSecL2Counter_EUR_secEgressL2CounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure secEgressL2CounterLSW in AQ_PcsEgressSecL2Counter_EUR */
#define bits_AQ_PcsEgressSecL2Counter_EUR_secEgressL2CounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure secEgressL2CounterLSW in AQ_PcsEgressSecL2Counter_EUR */
#define word_AQ_PcsEgressSecL2Counter_EUR_secEgressL2CounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure secEgressL2CounterMSW in AQ_PcsEgressSecL2Counter_EUR */
#define AQ_PcsEgressSecL2Counter_EUR_secEgressL2CounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure secEgressL2CounterMSW in AQ_PcsEgressSecL2Counter_EUR */
#define bits_AQ_PcsEgressSecL2Counter_EUR_secEgressL2CounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure secEgressL2CounterMSW in AQ_PcsEgressSecL2Counter_EUR */
#define word_AQ_PcsEgressSecL2Counter_EUR_secEgressL2CounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsTransmitVendorAlarms_EUR */
#define AQ_PcsTransmitVendorAlarms_EUR_baseRegisterAddress 0xCC00
/*! \brief MMD address of structure AQ_PcsTransmitVendorAlarms_EUR */
#define AQ_PcsTransmitVendorAlarms_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_1 in AQ_PcsTransmitVendorAlarms_EUR */
#define AQ_PcsTransmitVendorAlarms_EUR_reservedPcsTransmitVendorAlarms_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_1 in AQ_PcsTransmitVendorAlarms_EUR */
#define bits_AQ_PcsTransmitVendorAlarms_EUR_reservedPcsTransmitVendorAlarms_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_1 in AQ_PcsTransmitVendorAlarms_EUR */
#define word_AQ_PcsTransmitVendorAlarms_EUR_reservedPcsTransmitVendorAlarms_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tdeLaneMuxFifoParityError in AQ_PcsTransmitVendorAlarms_EUR */
#define AQ_PcsTransmitVendorAlarms_EUR_tdeLaneMuxFifoParityError 0
/*! \brief Preprocessor variable to relate field to bit position in structure tdeLaneMuxFifoParityError in AQ_PcsTransmitVendorAlarms_EUR */
#define bits_AQ_PcsTransmitVendorAlarms_EUR_tdeLaneMuxFifoParityError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tdeLaneMuxFifoParityError in AQ_PcsTransmitVendorAlarms_EUR */
#define word_AQ_PcsTransmitVendorAlarms_EUR_tdeLaneMuxFifoParityError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tdeLaneMuxFifoSyncError in AQ_PcsTransmitVendorAlarms_EUR */
#define AQ_PcsTransmitVendorAlarms_EUR_tdeLaneMuxFifoSyncError 0
/*! \brief Preprocessor variable to relate field to bit position in structure tdeLaneMuxFifoSyncError in AQ_PcsTransmitVendorAlarms_EUR */
#define bits_AQ_PcsTransmitVendorAlarms_EUR_tdeLaneMuxFifoSyncError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tdeLaneMuxFifoSyncError in AQ_PcsTransmitVendorAlarms_EUR */
#define word_AQ_PcsTransmitVendorAlarms_EUR_tdeLaneMuxFifoSyncError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTransmitInvalid_512bBlockDetected in AQ_PcsTransmitVendorAlarms_EUR */
#define AQ_PcsTransmitVendorAlarms_EUR_xauiTransmitInvalid_512bBlockDetected 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTransmitInvalid_512bBlockDetected in AQ_PcsTransmitVendorAlarms_EUR */
#define bits_AQ_PcsTransmitVendorAlarms_EUR_xauiTransmitInvalid_512bBlockDetected u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTransmitInvalid_512bBlockDetected in AQ_PcsTransmitVendorAlarms_EUR */
#define word_AQ_PcsTransmitVendorAlarms_EUR_xauiTransmitInvalid_512bBlockDetected u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTransmitInvalid_64bBlockDetected in AQ_PcsTransmitVendorAlarms_EUR */
#define AQ_PcsTransmitVendorAlarms_EUR_xauiTransmitInvalid_64bBlockDetected 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTransmitInvalid_64bBlockDetected in AQ_PcsTransmitVendorAlarms_EUR */
#define bits_AQ_PcsTransmitVendorAlarms_EUR_xauiTransmitInvalid_64bBlockDetected u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTransmitInvalid_64bBlockDetected in AQ_PcsTransmitVendorAlarms_EUR */
#define word_AQ_PcsTransmitVendorAlarms_EUR_xauiTransmitInvalid_64bBlockDetected u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_2 in AQ_PcsTransmitVendorAlarms_EUR */
#define AQ_PcsTransmitVendorAlarms_EUR_reservedPcsTransmitVendorAlarms_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_2 in AQ_PcsTransmitVendorAlarms_EUR */
#define bits_AQ_PcsTransmitVendorAlarms_EUR_reservedPcsTransmitVendorAlarms_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_2 in AQ_PcsTransmitVendorAlarms_EUR */
#define word_AQ_PcsTransmitVendorAlarms_EUR_reservedPcsTransmitVendorAlarms_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_3 in AQ_PcsTransmitVendorAlarms_EUR */
#define AQ_PcsTransmitVendorAlarms_EUR_reservedPcsTransmitVendorAlarms_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_3 in AQ_PcsTransmitVendorAlarms_EUR */
#define bits_AQ_PcsTransmitVendorAlarms_EUR_reservedPcsTransmitVendorAlarms_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_3 in AQ_PcsTransmitVendorAlarms_EUR */
#define word_AQ_PcsTransmitVendorAlarms_EUR_reservedPcsTransmitVendorAlarms_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_EUR */
#define AQ_PcsTransmitVendorAlarms_EUR_xfi0TransmitInvalidXgmiiCharacterReceived 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_EUR */
#define bits_AQ_PcsTransmitVendorAlarms_EUR_xfi0TransmitInvalidXgmiiCharacterReceived u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_EUR */
#define word_AQ_PcsTransmitVendorAlarms_EUR_xfi0TransmitInvalidXgmiiCharacterReceived u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_EUR */
#define AQ_PcsTransmitVendorAlarms_EUR_xfi0TransmitReservedXgmiiCharacterReceived 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_EUR */
#define bits_AQ_PcsTransmitVendorAlarms_EUR_xfi0TransmitReservedXgmiiCharacterReceived u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_EUR */
#define word_AQ_PcsTransmitVendorAlarms_EUR_xfi0TransmitReservedXgmiiCharacterReceived u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_EUR */
#define AQ_PcsTransmitVendorAlarms_EUR_xfi0Transmit_64bEncodeError 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_EUR */
#define bits_AQ_PcsTransmitVendorAlarms_EUR_xfi0Transmit_64bEncodeError u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_EUR */
#define word_AQ_PcsTransmitVendorAlarms_EUR_xfi0Transmit_64bEncodeError u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitLofDetected in AQ_PcsTransmitVendorAlarms_EUR */
#define AQ_PcsTransmitVendorAlarms_EUR_xfi0TransmitLofDetected 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitLofDetected in AQ_PcsTransmitVendorAlarms_EUR */
#define bits_AQ_PcsTransmitVendorAlarms_EUR_xfi0TransmitLofDetected u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitLofDetected in AQ_PcsTransmitVendorAlarms_EUR */
#define word_AQ_PcsTransmitVendorAlarms_EUR_xfi0TransmitLofDetected u3.word_3

/*! \brief Base register address of structure AQ_PcsStandardInterruptMask_EUR */
#define AQ_PcsStandardInterruptMask_EUR_baseRegisterAddress 0xD000
/*! \brief MMD address of structure AQ_PcsStandardInterruptMask_EUR */
#define AQ_PcsStandardInterruptMask_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure txLpiReceivedMask in AQ_PcsStandardInterruptMask_EUR */
#define AQ_PcsStandardInterruptMask_EUR_txLpiReceivedMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure txLpiReceivedMask in AQ_PcsStandardInterruptMask_EUR */
#define bits_AQ_PcsStandardInterruptMask_EUR_txLpiReceivedMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure txLpiReceivedMask in AQ_PcsStandardInterruptMask_EUR */
#define word_AQ_PcsStandardInterruptMask_EUR_txLpiReceivedMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rxLpiReceivedMask in AQ_PcsStandardInterruptMask_EUR */
#define AQ_PcsStandardInterruptMask_EUR_rxLpiReceivedMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure rxLpiReceivedMask in AQ_PcsStandardInterruptMask_EUR */
#define bits_AQ_PcsStandardInterruptMask_EUR_rxLpiReceivedMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rxLpiReceivedMask in AQ_PcsStandardInterruptMask_EUR */
#define word_AQ_PcsStandardInterruptMask_EUR_rxLpiReceivedMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsReceiveLinkStatusMask in AQ_PcsStandardInterruptMask_EUR */
#define AQ_PcsStandardInterruptMask_EUR_pcsReceiveLinkStatusMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsReceiveLinkStatusMask in AQ_PcsStandardInterruptMask_EUR */
#define bits_AQ_PcsStandardInterruptMask_EUR_pcsReceiveLinkStatusMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsReceiveLinkStatusMask in AQ_PcsStandardInterruptMask_EUR */
#define word_AQ_PcsStandardInterruptMask_EUR_pcsReceiveLinkStatusMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitFaultMask in AQ_PcsStandardInterruptMask_EUR */
#define AQ_PcsStandardInterruptMask_EUR_transmitFaultMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure transmitFaultMask in AQ_PcsStandardInterruptMask_EUR */
#define bits_AQ_PcsStandardInterruptMask_EUR_transmitFaultMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure transmitFaultMask in AQ_PcsStandardInterruptMask_EUR */
#define word_AQ_PcsStandardInterruptMask_EUR_transmitFaultMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure receiveFaultMask in AQ_PcsStandardInterruptMask_EUR */
#define AQ_PcsStandardInterruptMask_EUR_receiveFaultMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure receiveFaultMask in AQ_PcsStandardInterruptMask_EUR */
#define bits_AQ_PcsStandardInterruptMask_EUR_receiveFaultMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure receiveFaultMask in AQ_PcsStandardInterruptMask_EUR */
#define word_AQ_PcsStandardInterruptMask_EUR_receiveFaultMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tPcsBlockLockLatchedMask in AQ_PcsStandardInterruptMask_EUR */
#define AQ_PcsStandardInterruptMask_EUR__10gbase_tPcsBlockLockLatchedMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tPcsBlockLockLatchedMask in AQ_PcsStandardInterruptMask_EUR */
#define bits_AQ_PcsStandardInterruptMask_EUR__10gbase_tPcsBlockLockLatchedMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tPcsBlockLockLatchedMask in AQ_PcsStandardInterruptMask_EUR */
#define word_AQ_PcsStandardInterruptMask_EUR__10gbase_tPcsBlockLockLatchedMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tHighBerLatchedMask in AQ_PcsStandardInterruptMask_EUR */
#define AQ_PcsStandardInterruptMask_EUR__10gbase_tHighBerLatchedMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tHighBerLatchedMask in AQ_PcsStandardInterruptMask_EUR */
#define bits_AQ_PcsStandardInterruptMask_EUR__10gbase_tHighBerLatchedMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tHighBerLatchedMask in AQ_PcsStandardInterruptMask_EUR */
#define word_AQ_PcsStandardInterruptMask_EUR__10gbase_tHighBerLatchedMask u2.word_2

/*! \brief Base register address of structure AQ_PcsTransmitVendorInterruptMask_EUR */
#define AQ_PcsTransmitVendorInterruptMask_EUR_baseRegisterAddress 0xD400
/*! \brief MMD address of structure AQ_PcsTransmitVendorInterruptMask_EUR */
#define AQ_PcsTransmitVendorInterruptMask_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_1Mask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define AQ_PcsTransmitVendorInterruptMask_EUR_reservedPcsTransmitVendorAlarms_1Mask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_1Mask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define bits_AQ_PcsTransmitVendorInterruptMask_EUR_reservedPcsTransmitVendorAlarms_1Mask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_1Mask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define word_AQ_PcsTransmitVendorInterruptMask_EUR_reservedPcsTransmitVendorAlarms_1Mask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tdeLaneMuxFifoParityErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define AQ_PcsTransmitVendorInterruptMask_EUR_tdeLaneMuxFifoParityErrorMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure tdeLaneMuxFifoParityErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define bits_AQ_PcsTransmitVendorInterruptMask_EUR_tdeLaneMuxFifoParityErrorMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tdeLaneMuxFifoParityErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define word_AQ_PcsTransmitVendorInterruptMask_EUR_tdeLaneMuxFifoParityErrorMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tdeLaneMuxFifoSyncErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define AQ_PcsTransmitVendorInterruptMask_EUR_tdeLaneMuxFifoSyncErrorMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure tdeLaneMuxFifoSyncErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define bits_AQ_PcsTransmitVendorInterruptMask_EUR_tdeLaneMuxFifoSyncErrorMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tdeLaneMuxFifoSyncErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define word_AQ_PcsTransmitVendorInterruptMask_EUR_tdeLaneMuxFifoSyncErrorMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTransmitInvalid_512bBlockDetectedMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define AQ_PcsTransmitVendorInterruptMask_EUR_xauiTransmitInvalid_512bBlockDetectedMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTransmitInvalid_512bBlockDetectedMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define bits_AQ_PcsTransmitVendorInterruptMask_EUR_xauiTransmitInvalid_512bBlockDetectedMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTransmitInvalid_512bBlockDetectedMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define word_AQ_PcsTransmitVendorInterruptMask_EUR_xauiTransmitInvalid_512bBlockDetectedMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTransmitInvalid_64bBlockDetectedMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define AQ_PcsTransmitVendorInterruptMask_EUR_xauiTransmitInvalid_64bBlockDetectedMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTransmitInvalid_64bBlockDetectedMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define bits_AQ_PcsTransmitVendorInterruptMask_EUR_xauiTransmitInvalid_64bBlockDetectedMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTransmitInvalid_64bBlockDetectedMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define word_AQ_PcsTransmitVendorInterruptMask_EUR_xauiTransmitInvalid_64bBlockDetectedMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_2Mask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define AQ_PcsTransmitVendorInterruptMask_EUR_reservedPcsTransmitVendorAlarms_2Mask 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_2Mask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define bits_AQ_PcsTransmitVendorInterruptMask_EUR_reservedPcsTransmitVendorAlarms_2Mask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_2Mask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define word_AQ_PcsTransmitVendorInterruptMask_EUR_reservedPcsTransmitVendorAlarms_2Mask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_3Mask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define AQ_PcsTransmitVendorInterruptMask_EUR_reservedPcsTransmitVendorAlarms_3Mask 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_3Mask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define bits_AQ_PcsTransmitVendorInterruptMask_EUR_reservedPcsTransmitVendorAlarms_3Mask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_3Mask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define word_AQ_PcsTransmitVendorInterruptMask_EUR_reservedPcsTransmitVendorAlarms_3Mask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define AQ_PcsTransmitVendorInterruptMask_EUR_xfi0TransmitInvalidXgmiiCharacterErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define bits_AQ_PcsTransmitVendorInterruptMask_EUR_xfi0TransmitInvalidXgmiiCharacterErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define word_AQ_PcsTransmitVendorInterruptMask_EUR_xfi0TransmitInvalidXgmiiCharacterErrorMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define AQ_PcsTransmitVendorInterruptMask_EUR_xfi0TransmitReservedXgmiiCharacterErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define bits_AQ_PcsTransmitVendorInterruptMask_EUR_xfi0TransmitReservedXgmiiCharacterErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define word_AQ_PcsTransmitVendorInterruptMask_EUR_xfi0TransmitReservedXgmiiCharacterErrorMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define AQ_PcsTransmitVendorInterruptMask_EUR_xfi0TransmitEncode_64bErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define bits_AQ_PcsTransmitVendorInterruptMask_EUR_xfi0TransmitEncode_64bErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_EUR */
#define word_AQ_PcsTransmitVendorInterruptMask_EUR_xfi0TransmitEncode_64bErrorMask u3.word_3

/*! \brief Base register address of structure AQ_PcsTransmitVendorDebug_EUR */
#define AQ_PcsTransmitVendorDebug_EUR_baseRegisterAddress 0xD800
/*! \brief MMD address of structure AQ_PcsTransmitVendorDebug_EUR */
#define AQ_PcsTransmitVendorDebug_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsTxScramblerDisable in AQ_PcsTransmitVendorDebug_EUR */
#define AQ_PcsTransmitVendorDebug_EUR_pcsTxScramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTxScramblerDisable in AQ_PcsTransmitVendorDebug_EUR */
#define bits_AQ_PcsTransmitVendorDebug_EUR_pcsTxScramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTxScramblerDisable in AQ_PcsTransmitVendorDebug_EUR */
#define word_AQ_PcsTransmitVendorDebug_EUR_pcsTxScramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsTxInjectCrcError in AQ_PcsTransmitVendorDebug_EUR */
#define AQ_PcsTransmitVendorDebug_EUR_pcsTxInjectCrcError 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTxInjectCrcError in AQ_PcsTransmitVendorDebug_EUR */
#define bits_AQ_PcsTransmitVendorDebug_EUR_pcsTxInjectCrcError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTxInjectCrcError in AQ_PcsTransmitVendorDebug_EUR */
#define word_AQ_PcsTransmitVendorDebug_EUR_pcsTxInjectCrcError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsTxInjectFrameError in AQ_PcsTransmitVendorDebug_EUR */
#define AQ_PcsTransmitVendorDebug_EUR_pcsTxInjectFrameError 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTxInjectFrameError in AQ_PcsTransmitVendorDebug_EUR */
#define bits_AQ_PcsTransmitVendorDebug_EUR_pcsTxInjectFrameError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTxInjectFrameError in AQ_PcsTransmitVendorDebug_EUR */
#define word_AQ_PcsTransmitVendorDebug_EUR_pcsTxInjectFrameError u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorProvisioning_EUR */
#define AQ_PcsReceiveVendorProvisioning_EUR_baseRegisterAddress 0xE400
/*! \brief MMD address of structure AQ_PcsReceiveVendorProvisioning_EUR */
#define AQ_PcsReceiveVendorProvisioning_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsRxErrorLdpcFrameEnable in AQ_PcsReceiveVendorProvisioning_EUR */
#define AQ_PcsReceiveVendorProvisioning_EUR_pcsRxErrorLdpcFrameEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsRxErrorLdpcFrameEnable in AQ_PcsReceiveVendorProvisioning_EUR */
#define bits_AQ_PcsReceiveVendorProvisioning_EUR_pcsRxErrorLdpcFrameEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsRxErrorLdpcFrameEnable in AQ_PcsReceiveVendorProvisioning_EUR */
#define word_AQ_PcsReceiveVendorProvisioning_EUR_pcsRxErrorLdpcFrameEnable u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveXfi0Provisioning_EUR */
#define AQ_PcsReceiveXfi0Provisioning_EUR_baseRegisterAddress 0xE460
/*! \brief MMD address of structure AQ_PcsReceiveXfi0Provisioning_EUR */
#define AQ_PcsReceiveXfi0Provisioning_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi0RxDescramblerDisable in AQ_PcsReceiveXfi0Provisioning_EUR */
#define AQ_PcsReceiveXfi0Provisioning_EUR_xfi0RxDescramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0RxDescramblerDisable in AQ_PcsReceiveXfi0Provisioning_EUR */
#define bits_AQ_PcsReceiveXfi0Provisioning_EUR_xfi0RxDescramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi0RxDescramblerDisable in AQ_PcsReceiveXfi0Provisioning_EUR */
#define word_AQ_PcsReceiveXfi0Provisioning_EUR_xfi0RxDescramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestDataSource in AQ_PcsReceiveXfi0Provisioning_EUR */
#define AQ_PcsReceiveXfi0Provisioning_EUR_xfi0TestDataSource 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestDataSource in AQ_PcsReceiveXfi0Provisioning_EUR */
#define bits_AQ_PcsReceiveXfi0Provisioning_EUR_xfi0TestDataSource u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestDataSource in AQ_PcsReceiveXfi0Provisioning_EUR */
#define word_AQ_PcsReceiveXfi0Provisioning_EUR_xfi0TestDataSource u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestModeSelect in AQ_PcsReceiveXfi0Provisioning_EUR */
#define AQ_PcsReceiveXfi0Provisioning_EUR_xfi0TestModeSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestModeSelect in AQ_PcsReceiveXfi0Provisioning_EUR */
#define bits_AQ_PcsReceiveXfi0Provisioning_EUR_xfi0TestModeSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestModeSelect in AQ_PcsReceiveXfi0Provisioning_EUR */
#define word_AQ_PcsReceiveXfi0Provisioning_EUR_xfi0TestModeSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPatternEnable in AQ_PcsReceiveXfi0Provisioning_EUR */
#define AQ_PcsReceiveXfi0Provisioning_EUR_xfi0TestPatternEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPatternEnable in AQ_PcsReceiveXfi0Provisioning_EUR */
#define bits_AQ_PcsReceiveXfi0Provisioning_EUR_xfi0TestPatternEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPatternEnable in AQ_PcsReceiveXfi0Provisioning_EUR */
#define word_AQ_PcsReceiveXfi0Provisioning_EUR_xfi0TestPatternEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0LocalFaultInject in AQ_PcsReceiveXfi0Provisioning_EUR */
#define AQ_PcsReceiveXfi0Provisioning_EUR_xfi0LocalFaultInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0LocalFaultInject in AQ_PcsReceiveXfi0Provisioning_EUR */
#define bits_AQ_PcsReceiveXfi0Provisioning_EUR_xfi0LocalFaultInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0LocalFaultInject in AQ_PcsReceiveXfi0Provisioning_EUR */
#define word_AQ_PcsReceiveXfi0Provisioning_EUR_xfi0LocalFaultInject u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveXfi1Provisioning_EUR */
#define AQ_PcsReceiveXfi1Provisioning_EUR_baseRegisterAddress 0xE470
/*! \brief MMD address of structure AQ_PcsReceiveXfi1Provisioning_EUR */
#define AQ_PcsReceiveXfi1Provisioning_EUR_mmdAddress 0x03

/*! \brief Base register address of structure AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_baseRegisterAddress 0xE600
/*! \brief MMD address of structure AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressVlanTaggingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressVlanTaggingEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressVlanTaggingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressVlanTaggingEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressVlanTaggingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressVlanTaggingEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6_udpEncapsulatedEnabled in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6_udpEncapsulatedEnabled 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6_udpEncapsulatedEnabled in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6_udpEncapsulatedEnabled u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6_udpEncapsulatedEnabled in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6_udpEncapsulatedEnabled u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv4_udpEncapsulatedEnabled in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv4_udpEncapsulatedEnabled 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv4_udpEncapsulatedEnabled in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv4_udpEncapsulatedEnabled u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv4_udpEncapsulatedEnabled in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv4_udpEncapsulatedEnabled u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressEthernetEncapsulatedEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressEthernetEncapsulatedEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressEthernetEncapsulatedEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressEthernetEncapsulatedEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressEthernetEncapsulatedEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressEthernetEncapsulatedEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressNtpConfiguration in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtpConfiguration 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressNtpConfiguration in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtpConfiguration u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressNtpConfiguration in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtpConfiguration u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressBackPressureEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressBackPressureEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressBackPressureEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressBackPressureEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressBackPressureEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressBackPressureEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressNtpEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtpEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressNtpEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtpEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressNtpEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtpEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_2Enable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2Enable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_2Enable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2Enable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_2Enable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2Enable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_1Enable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_1Enable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_1Enable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_1Enable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_1Enable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_1Enable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressMatchingEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressMatchingEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressMatchingEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv4DestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv4DestinationAddressMatchingEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv4DestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv4DestinationAddressMatchingEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv4DestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv4DestinationAddressMatchingEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressMacDestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressMacDestinationAddressMatchingEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressMacDestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressMacDestinationAddressMatchingEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressMacDestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressMacDestinationAddressMatchingEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressEthertypeMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressEthertypeMatchingEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressEthertypeMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressEthertypeMatchingEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressEthertypeMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressEthertypeMatchingEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressNtp_sntpVersion in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtp_sntpVersion 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressNtp_sntpVersion in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtp_sntpVersion u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressNtp_sntpVersion in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtp_sntpVersion u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588_2StepEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588_2StepEnable 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588_2StepEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588_2StepEnable u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588_2StepEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588_2StepEnable u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_2DomainMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2DomainMatchingEnable 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_2DomainMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2DomainMatchingEnable u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_2DomainMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2DomainMatchingEnable u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressUdpDestinationPortMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressUdpDestinationPortMatchingEnable 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressUdpDestinationPortMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressUdpDestinationPortMatchingEnable u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressUdpDestinationPortMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressUdpDestinationPortMatchingEnable u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressEthertype in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressEthertype 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressEthertype in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressEthertype u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressEthertype in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressEthertype u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressMacDestinationAddressBits_15_0 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressMacDestinationAddressBits_15_0 4
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressMacDestinationAddressBits_15_0 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressMacDestinationAddressBits_15_0 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressMacDestinationAddressBits_15_0 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressMacDestinationAddressBits_15_0 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressMacDestinationAddressBits_31_16 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressMacDestinationAddressBits_31_16 5
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressMacDestinationAddressBits_31_16 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressMacDestinationAddressBits_31_16 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressMacDestinationAddressBits_31_16 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressMacDestinationAddressBits_31_16 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressMacDestinationAddressBits_47_32 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressMacDestinationAddressBits_47_32 6
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressMacDestinationAddressBits_47_32 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressMacDestinationAddressBits_47_32 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressMacDestinationAddressBits_47_32 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressMacDestinationAddressBits_47_32 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv4DestinationAddressLSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv4DestinationAddressLSW 7
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv4DestinationAddressLSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv4DestinationAddressLSW u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv4DestinationAddressLSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv4DestinationAddressLSW u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv4DestinationAddressMSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv4DestinationAddressMSW 8
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv4DestinationAddressMSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv4DestinationAddressMSW u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv4DestinationAddressMSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv4DestinationAddressMSW u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_15_0 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_15_0 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_15_0 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_15_0 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_15_0 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_15_0 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_31_16 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_31_16 10
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_31_16 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_31_16 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_31_16 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_31_16 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_47_32 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_47_32 11
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_47_32 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_47_32 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_47_32 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_47_32 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_63_48 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_63_48 12
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_63_48 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_63_48 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_63_48 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_63_48 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_79_64 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_79_64 13
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_79_64 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_79_64 u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_79_64 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_79_64 u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_95_80 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_95_80 14
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_95_80 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_95_80 u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_95_80 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_95_80 u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_111_96 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_111_96 15
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_111_96 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_111_96 u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_111_96 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_111_96 u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_127_112 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_127_112 16
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_127_112 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_127_112 u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_127_112 in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressIpv6DestinationAddressBits_127_112 u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressUdpDestinationPort in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressUdpDestinationPort 17
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressUdpDestinationPort in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressUdpDestinationPort u17.bits_17
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressUdpDestinationPort in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressUdpDestinationPort u17.word_17
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_2Domain in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2Domain 18
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_2Domain in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2Domain u18.bits_18
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_2Domain in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2Domain u18.word_18
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressCorrectionOffsetSign in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressCorrectionOffsetSign 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressCorrectionOffsetSign in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressCorrectionOffsetSign u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressCorrectionOffsetSign in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressCorrectionOffsetSign u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampOffsetSign in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampOffsetSign 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampOffsetSign in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampOffsetSign u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampOffsetSign in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampOffsetSign u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressSetTimeStampOffset in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressSetTimeStampOffset 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressSetTimeStampOffset in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressSetTimeStampOffset u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressSetTimeStampOffset in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressSetTimeStampOffset u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressByteSwap in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressByteSwap 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressByteSwap in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressByteSwap u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressByteSwap in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressByteSwap u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampNanosecondOffset in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampNanosecondOffset 20
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampNanosecondOffset in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampNanosecondOffset u20.bits_20
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampNanosecondOffset in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampNanosecondOffset u20.word_20
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampFractionalSecondOffsetLSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampFractionalSecondOffsetLSW 21
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampFractionalSecondOffsetLSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampFractionalSecondOffsetLSW u21.bits_21
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampFractionalSecondOffsetLSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampFractionalSecondOffsetLSW u21.word_21
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampFractionalSecondOffsetMSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampFractionalSecondOffsetMSW 22
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampFractionalSecondOffsetMSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampFractionalSecondOffsetMSW u22.bits_22
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampFractionalSecondOffsetMSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampFractionalSecondOffsetMSW u22.word_22
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressCorrectionOffsetLSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressCorrectionOffsetLSW 23
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressCorrectionOffsetLSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressCorrectionOffsetLSW u23.bits_23
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressCorrectionOffsetLSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressCorrectionOffsetLSW u23.word_23
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressCorrectionOffsetMSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressCorrectionOffsetMSW 24
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressCorrectionOffsetMSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressCorrectionOffsetMSW u24.bits_24
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressCorrectionOffsetMSW in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressCorrectionOffsetMSW u24.word_24
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketAction 25
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketAction u25.bits_25
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketAction u25.word_25
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressNtp_sntpTimeStampAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtp_sntpTimeStampAction 26
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressNtp_sntpTimeStampAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtp_sntpTimeStampAction u26.bits_26
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressNtp_sntpTimeStampAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtp_sntpTimeStampAction u26.word_26
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressNtp_sntpPacketAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtp_sntpPacketAction 26
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressNtp_sntpPacketAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtp_sntpPacketAction u26.bits_26
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressNtp_sntpPacketAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressNtp_sntpPacketAction u26.word_26
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketBufferReset in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketBufferReset 30
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketBufferReset in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketBufferReset u30.bits_30
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketBufferReset in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketBufferReset u30.word_30
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketBufferReadEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketBufferReadEnable 30
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketBufferReadEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketBufferReadEnable u30.bits_30
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketBufferReadEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketBufferReadEnable u30.word_30
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketPause in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketPause 31
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketPause in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketPause u31.bits_31
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketPause in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketPause u31.word_31
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketSizeLimit in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketSizeLimit 31
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketSizeLimit in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketSizeLimit u31.bits_31
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketSizeLimit in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketSizeLimit u31.word_31
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketTimeStampReadEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketTimeStampReadEnable 32
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketTimeStampReadEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketTimeStampReadEnable u32.bits_32
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketTimeStampReadEnable in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressPacketTimeStampReadEnable u32.word_32
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_1TimeStampAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_1TimeStampAction 33
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_1TimeStampAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_1TimeStampAction u33.bits_33
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_1TimeStampAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_1TimeStampAction u33.word_33
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_1PacketAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_1PacketAction 33
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_1PacketAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_1PacketAction u33.bits_33
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_1PacketAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_1PacketAction u33.word_33
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressStackedVlanID in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressStackedVlanID 34
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressStackedVlanID in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressStackedVlanID u34.bits_34
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressStackedVlanID in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressStackedVlanID u34.word_34
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressCorrectionAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressCorrectionAction 35
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressCorrectionAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressCorrectionAction u35.bits_35
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressCorrectionAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressCorrectionAction u35.word_35
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampAction 36
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampAction u36.bits_36
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampAction in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngressTimeStampAction u36.word_36
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_2MessageType in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2MessageType 37
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_2MessageType in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2MessageType u37.bits_37
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_2MessageType in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2MessageType u37.word_37
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_2MessageMask in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2MessageMask 38
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_2MessageMask in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define bits_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2MessageMask u38.bits_38
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_2MessageMask in AQ_PcsPtpIngressVendorProvisioning_EUR */
#define word_AQ_PcsPtpIngressVendorProvisioning_EUR_ptpIngress_1588Version_2MessageMask u38.word_38

/*! \brief Base register address of structure AQ_PcsReceiveVendorState_EUR */
#define AQ_PcsReceiveVendorState_EUR_baseRegisterAddress 0xE800
/*! \brief MMD address of structure AQ_PcsReceiveVendorState_EUR */
#define AQ_PcsReceiveVendorState_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsRxCurrentValueOfAuxilliaryBit in AQ_PcsReceiveVendorState_EUR */
#define AQ_PcsReceiveVendorState_EUR_pcsRxCurrentValueOfAuxilliaryBit 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsRxCurrentValueOfAuxilliaryBit in AQ_PcsReceiveVendorState_EUR */
#define bits_AQ_PcsReceiveVendorState_EUR_pcsRxCurrentValueOfAuxilliaryBit u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsRxCurrentValueOfAuxilliaryBit in AQ_PcsReceiveVendorState_EUR */
#define word_AQ_PcsReceiveVendorState_EUR_pcsRxCurrentValueOfAuxilliaryBit u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveReservedVendorState_EUR */
#define AQ_PcsReceiveReservedVendorState_EUR_baseRegisterAddress 0xE808
/*! \brief MMD address of structure AQ_PcsReceiveReservedVendorState_EUR */
#define AQ_PcsReceiveReservedVendorState_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure averageLdpcIterationCount in AQ_PcsReceiveReservedVendorState_EUR */
#define AQ_PcsReceiveReservedVendorState_EUR_averageLdpcIterationCount 0
/*! \brief Preprocessor variable to relate field to bit position in structure averageLdpcIterationCount in AQ_PcsReceiveReservedVendorState_EUR */
#define bits_AQ_PcsReceiveReservedVendorState_EUR_averageLdpcIterationCount u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure averageLdpcIterationCount in AQ_PcsReceiveReservedVendorState_EUR */
#define word_AQ_PcsReceiveReservedVendorState_EUR_averageLdpcIterationCount u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR */
#define AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR_baseRegisterAddress 0xE810
/*! \brief MMD address of structure AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR */
#define AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure crc_8ErrorCounterLSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR */
#define AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR_crc_8ErrorCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure crc_8ErrorCounterLSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR */
#define bits_AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR_crc_8ErrorCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure crc_8ErrorCounterLSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR */
#define word_AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR_crc_8ErrorCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure crc_8ErrorCounterMSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR */
#define AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR_crc_8ErrorCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure crc_8ErrorCounterMSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR */
#define bits_AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR_crc_8ErrorCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure crc_8ErrorCounterMSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR */
#define word_AQ_PcsReceiveVendorCrc_8ErrorCounter_EUR_crc_8ErrorCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR */
#define AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR_baseRegisterAddress 0xE812
/*! \brief MMD address of structure AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR */
#define AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR */
#define AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR__10gbase_tGoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR */
#define bits_AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR__10gbase_tGoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR */
#define word_AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR__10gbase_tGoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR */
#define AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR__10gbase_tGoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR */
#define bits_AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR__10gbase_tGoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR */
#define word_AQ_PcsReceiveVendorFcsNoErrorFrameCounter_EUR__10gbase_tGoodFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR */
#define AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR_baseRegisterAddress 0xE814
/*! \brief MMD address of structure AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR */
#define AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR */
#define AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR__10gbase_tErrorFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR */
#define bits_AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR__10gbase_tErrorFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR */
#define word_AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR__10gbase_tErrorFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR */
#define AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR__10gbase_tErrorFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR */
#define bits_AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR__10gbase_tErrorFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR */
#define word_AQ_PcsReceiveVendorFcsErrorFrameCounter_EUR__10gbase_tErrorFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR */
#define AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR_baseRegisterAddress 0xE816
/*! \brief MMD address of structure AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR */
#define AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure rsCorrectedErrorCounterLSW in AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR */
#define AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR_rsCorrectedErrorCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure rsCorrectedErrorCounterLSW in AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR */
#define bits_AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR_rsCorrectedErrorCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rsCorrectedErrorCounterLSW in AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR */
#define word_AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR_rsCorrectedErrorCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rsCorrectedErrorCounterMSW in AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR */
#define AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR_rsCorrectedErrorCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure rsCorrectedErrorCounterMSW in AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR */
#define bits_AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR_rsCorrectedErrorCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure rsCorrectedErrorCounterMSW in AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR */
#define word_AQ_PcsReceiveVendorRsCorrectedErrorFrameCounter_EUR_rsCorrectedErrorCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR */
#define AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR_baseRegisterAddress 0xE820
/*! \brief MMD address of structure AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR */
#define AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure uncorrectedFrameCounterLSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR */
#define AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR_uncorrectedFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure uncorrectedFrameCounterLSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR */
#define bits_AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR_uncorrectedFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure uncorrectedFrameCounterLSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR */
#define word_AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR_uncorrectedFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure uncorrectedFrameCounterMSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR */
#define AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR_uncorrectedFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure uncorrectedFrameCounterMSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR */
#define bits_AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR_uncorrectedFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure uncorrectedFrameCounterMSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR */
#define word_AQ_PcsReceiveVendorUncorrectedFrameCounter_EUR_uncorrectedFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR_baseRegisterAddress 0xE840
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_1IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR_correctedFrames_1IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_1IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR_correctedFrames_1IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_1IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR_correctedFrames_1IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_1IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR_correctedFrames_1IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_1IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR_correctedFrames_1IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_1IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_EUR_correctedFrames_1IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR_baseRegisterAddress 0xE842
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_2IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR_correctedFrames_2IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_2IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR_correctedFrames_2IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_2IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR_correctedFrames_2IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_2IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR_correctedFrames_2IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_2IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR_correctedFrames_2IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_2IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_EUR_correctedFrames_2IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR_baseRegisterAddress 0xE844
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_3IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR_correctedFrames_3IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_3IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR_correctedFrames_3IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_3IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR_correctedFrames_3IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_3IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR_correctedFrames_3IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_3IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR_correctedFrames_3IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_3IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_EUR_correctedFrames_3IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR_baseRegisterAddress 0xE846
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_4IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR_correctedFrames_4IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_4IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR_correctedFrames_4IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_4IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR_correctedFrames_4IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_4IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR_correctedFrames_4IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_4IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR_correctedFrames_4IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_4IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_EUR_correctedFrames_4IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR_baseRegisterAddress 0xE848
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_5IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR_correctedFrames_5IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_5IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR_correctedFrames_5IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_5IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR_correctedFrames_5IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_5IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR_correctedFrames_5IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_5IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR_correctedFrames_5IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_5IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_EUR_correctedFrames_5IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_EUR_baseRegisterAddress 0xE84A
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_6IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_EUR_correctedFrames_6IterationCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_6IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_EUR_correctedFrames_6IterationCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_6IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_EUR_correctedFrames_6IterationCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_EUR_baseRegisterAddress 0xE84B
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_7IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_EUR_correctedFrames_7IterationCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_7IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_EUR_correctedFrames_7IterationCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_7IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_EUR_correctedFrames_7IterationCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_EUR_baseRegisterAddress 0xE84C
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_8IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_EUR_correctedFrames_8IterationCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_8IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_EUR_correctedFrames_8IterationCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_8IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_EUR_correctedFrames_8IterationCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_9IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_9IterationCounter_EUR_baseRegisterAddress 0xE84D
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_9IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_9IterationCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_9IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_9IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_9IterationCounter_EUR_correctedFrames_9IterationCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_9IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_9IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_9IterationCounter_EUR_correctedFrames_9IterationCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_9IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_9IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_9IterationCounter_EUR_correctedFrames_9IterationCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_10IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_10IterationCounter_EUR_baseRegisterAddress 0xE84E
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_10IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_10IterationCounter_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_10IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_10IterationCounter_EUR */
#define AQ_PcsReceiveVendorCorrectedFrame_10IterationCounter_EUR_correctedFrames_10IterationCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_10IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_10IterationCounter_EUR */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_10IterationCounter_EUR_correctedFrames_10IterationCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_10IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_10IterationCounter_EUR */
#define word_AQ_PcsReceiveVendorCorrectedFrame_10IterationCounter_EUR_correctedFrames_10IterationCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveXfi0VendorState_EUR */
#define AQ_PcsReceiveXfi0VendorState_EUR_baseRegisterAddress 0xE860
/*! \brief MMD address of structure AQ_PcsReceiveXfi0VendorState_EUR */
#define AQ_PcsReceiveXfi0VendorState_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi0GoodFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_EUR */
#define AQ_PcsReceiveXfi0VendorState_EUR_xfi0GoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0GoodFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_EUR */
#define bits_AQ_PcsReceiveXfi0VendorState_EUR_xfi0GoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi0GoodFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_EUR */
#define word_AQ_PcsReceiveXfi0VendorState_EUR_xfi0GoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi0GoodFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_EUR */
#define AQ_PcsReceiveXfi0VendorState_EUR_xfi0GoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0GoodFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_EUR */
#define bits_AQ_PcsReceiveXfi0VendorState_EUR_xfi0GoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0GoodFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_EUR */
#define word_AQ_PcsReceiveXfi0VendorState_EUR_xfi0GoodFrameCounterMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BadFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_EUR */
#define AQ_PcsReceiveXfi0VendorState_EUR_xfi0BadFrameCounterLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BadFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_EUR */
#define bits_AQ_PcsReceiveXfi0VendorState_EUR_xfi0BadFrameCounterLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BadFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_EUR */
#define word_AQ_PcsReceiveXfi0VendorState_EUR_xfi0BadFrameCounterLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BadFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_EUR */
#define AQ_PcsReceiveXfi0VendorState_EUR_xfi0BadFrameCounterMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BadFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_EUR */
#define bits_AQ_PcsReceiveXfi0VendorState_EUR_xfi0BadFrameCounterMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BadFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_EUR */
#define word_AQ_PcsReceiveXfi0VendorState_EUR_xfi0BadFrameCounterMSW u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BerCounter in AQ_PcsReceiveXfi0VendorState_EUR */
#define AQ_PcsReceiveXfi0VendorState_EUR_xfi0BerCounter 4
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BerCounter in AQ_PcsReceiveXfi0VendorState_EUR */
#define bits_AQ_PcsReceiveXfi0VendorState_EUR_xfi0BerCounter u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BerCounter in AQ_PcsReceiveXfi0VendorState_EUR */
#define word_AQ_PcsReceiveXfi0VendorState_EUR_xfi0BerCounter u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure xfi0ErroredBlockCounter in AQ_PcsReceiveXfi0VendorState_EUR */
#define AQ_PcsReceiveXfi0VendorState_EUR_xfi0ErroredBlockCounter 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0ErroredBlockCounter in AQ_PcsReceiveXfi0VendorState_EUR */
#define bits_AQ_PcsReceiveXfi0VendorState_EUR_xfi0ErroredBlockCounter u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi0ErroredBlockCounter in AQ_PcsReceiveXfi0VendorState_EUR */
#define word_AQ_PcsReceiveXfi0VendorState_EUR_xfi0ErroredBlockCounter u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPatternErrorCounter in AQ_PcsReceiveXfi0VendorState_EUR */
#define AQ_PcsReceiveXfi0VendorState_EUR_xfi0TestPatternErrorCounter 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPatternErrorCounter in AQ_PcsReceiveXfi0VendorState_EUR */
#define bits_AQ_PcsReceiveXfi0VendorState_EUR_xfi0TestPatternErrorCounter u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPatternErrorCounter in AQ_PcsReceiveXfi0VendorState_EUR */
#define word_AQ_PcsReceiveXfi0VendorState_EUR_xfi0TestPatternErrorCounter u6.word_6

/*! \brief Base register address of structure AQ_PcsReceiveXfi1VendorState_EUR */
#define AQ_PcsReceiveXfi1VendorState_EUR_baseRegisterAddress 0xE870
/*! \brief MMD address of structure AQ_PcsReceiveXfi1VendorState_EUR */
#define AQ_PcsReceiveXfi1VendorState_EUR_mmdAddress 0x03

/*! \brief Base register address of structure AQ_PcsPtpIngressVendorState_EUR */
#define AQ_PcsPtpIngressVendorState_EUR_baseRegisterAddress 0xE900
/*! \brief MMD address of structure AQ_PcsPtpIngressVendorState_EUR */
#define AQ_PcsPtpIngressVendorState_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketCount in AQ_PcsPtpIngressVendorState_EUR */
#define AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketCount 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketCount in AQ_PcsPtpIngressVendorState_EUR */
#define bits_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketCount u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketCount in AQ_PcsPtpIngressVendorState_EUR */
#define word_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketCount u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketDataLSW in AQ_PcsPtpIngressVendorState_EUR */
#define AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketDataLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketDataLSW in AQ_PcsPtpIngressVendorState_EUR */
#define bits_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketDataLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketDataLSW in AQ_PcsPtpIngressVendorState_EUR */
#define word_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketDataLSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketDataMSW in AQ_PcsPtpIngressVendorState_EUR */
#define AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketDataMSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketDataMSW in AQ_PcsPtpIngressVendorState_EUR */
#define bits_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketDataMSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketDataMSW in AQ_PcsPtpIngressVendorState_EUR */
#define word_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketDataMSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketTruncated in AQ_PcsPtpIngressVendorState_EUR */
#define AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketTruncated 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketTruncated in AQ_PcsPtpIngressVendorState_EUR */
#define bits_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketTruncated u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketTruncated in AQ_PcsPtpIngressVendorState_EUR */
#define word_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketTruncated u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketEop in AQ_PcsPtpIngressVendorState_EUR */
#define AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketEop 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketEop in AQ_PcsPtpIngressVendorState_EUR */
#define bits_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketEop u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketEop in AQ_PcsPtpIngressVendorState_EUR */
#define word_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketEop u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketSop in AQ_PcsPtpIngressVendorState_EUR */
#define AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketSop 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketSop in AQ_PcsPtpIngressVendorState_EUR */
#define bits_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketSop u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketSop in AQ_PcsPtpIngressVendorState_EUR */
#define word_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketSop u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketTimeStampCount in AQ_PcsPtpIngressVendorState_EUR */
#define AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketTimeStampCount 4
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketTimeStampCount in AQ_PcsPtpIngressVendorState_EUR */
#define bits_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketTimeStampCount u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketTimeStampCount in AQ_PcsPtpIngressVendorState_EUR */
#define word_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketTimeStampCount u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketTimeStamp in AQ_PcsPtpIngressVendorState_EUR */
#define AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketTimeStamp 5
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketTimeStamp in AQ_PcsPtpIngressVendorState_EUR */
#define bits_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketTimeStamp u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketTimeStamp in AQ_PcsPtpIngressVendorState_EUR */
#define word_AQ_PcsPtpIngressVendorState_EUR_ptpIngressPacketTimeStamp u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressRxMacFifoCount in AQ_PcsPtpIngressVendorState_EUR */
#define AQ_PcsPtpIngressVendorState_EUR_ptpIngressRxMacFifoCount 6
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressRxMacFifoCount in AQ_PcsPtpIngressVendorState_EUR */
#define bits_AQ_PcsPtpIngressVendorState_EUR_ptpIngressRxMacFifoCount u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressRxMacFifoCount in AQ_PcsPtpIngressVendorState_EUR */
#define word_AQ_PcsPtpIngressVendorState_EUR_ptpIngressRxMacFifoCount u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressRxPacketInformation in AQ_PcsPtpIngressVendorState_EUR */
#define AQ_PcsPtpIngressVendorState_EUR_ptpIngressRxPacketInformation 6
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressRxPacketInformation in AQ_PcsPtpIngressVendorState_EUR */
#define bits_AQ_PcsPtpIngressVendorState_EUR_ptpIngressRxPacketInformation u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressRxPacketInformation in AQ_PcsPtpIngressVendorState_EUR */
#define word_AQ_PcsPtpIngressVendorState_EUR_ptpIngressRxPacketInformation u6.word_6

/*! \brief Base register address of structure AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_baseRegisterAddress 0xEC00
/*! \brief MMD address of structure AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure crcError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_crcError 0
/*! \brief Preprocessor variable to relate field to bit position in structure crcError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_crcError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure crcError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_crcError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldpcDecodeFailure in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ldpcDecodeFailure 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldpcDecodeFailure in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ldpcDecodeFailure u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldpcDecodeFailure in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ldpcDecodeFailure u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rplLinkFailure in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_rplLinkFailure 0
/*! \brief Preprocessor variable to relate field to bit position in structure rplLinkFailure in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_rplLinkFailure u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rplLinkFailure in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_rplLinkFailure u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _40gBipLock in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR__40gBipLock 0
/*! \brief Preprocessor variable to relate field to bit position in structure _40gBipLock in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR__40gBipLock u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _40gBipLock in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR__40gBipLock u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure localFaultDetect in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_localFaultDetect 0
/*! \brief Preprocessor variable to relate field to bit position in structure localFaultDetect in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_localFaultDetect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure localFaultDetect in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_localFaultDetect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lofDetect in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_lofDetect 0
/*! \brief Preprocessor variable to relate field to bit position in structure lofDetect in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_lofDetect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lofDetect in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_lofDetect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure invalid_513bBlock in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_invalid_513bBlock 0
/*! \brief Preprocessor variable to relate field to bit position in structure invalid_513bBlock in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_invalid_513bBlock u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure invalid_513bBlock in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_invalid_513bBlock u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure invalid_65bBlock in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_invalid_65bBlock 0
/*! \brief Preprocessor variable to relate field to bit position in structure invalid_65bBlock in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_invalid_65bBlock u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure invalid_65bBlock in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_invalid_65bBlock u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiActiveOff in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiActiveOff 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiActiveOff in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiActiveOff u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiActiveOff in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiActiveOff u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiActiveOn in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiActiveOn 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiActiveOn in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiActiveOn u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiActiveOn in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiActiveOn u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldpcConsecutiveErroredFrameExceeded in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ldpcConsecutiveErroredFrameExceeded 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldpcConsecutiveErroredFrameExceeded in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ldpcConsecutiveErroredFrameExceeded u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldpcConsecutiveErroredFrameExceeded in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ldpcConsecutiveErroredFrameExceeded u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiAlert in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiAlert 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiAlert in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiAlert u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiAlert in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiAlert u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiReceivedLatchedLow in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiReceivedLatchedLow 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiReceivedLatchedLow in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiReceivedLatchedLow u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiReceivedLatchedLow in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiReceivedLatchedLow u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiReceivedLatchedHigh in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiReceivedLatchedHigh 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiReceivedLatchedHigh in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiReceivedLatchedHigh u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiReceivedLatchedHigh in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_eeeRxLpiReceivedLatchedHigh u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure changeInAuxilliaryBit in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_changeInAuxilliaryBit 0
/*! \brief Preprocessor variable to relate field to bit position in structure changeInAuxilliaryBit in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_changeInAuxilliaryBit u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure changeInAuxilliaryBit in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_changeInAuxilliaryBit u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rddLaneMuxFifoParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_rddLaneMuxFifoParityError 4
/*! \brief Preprocessor variable to relate field to bit position in structure rddLaneMuxFifoParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_rddLaneMuxFifoParityError u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure rddLaneMuxFifoParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_rddLaneMuxFifoParityError u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure rddLaneMuxFifoSyncError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_rddLaneMuxFifoSyncError 4
/*! \brief Preprocessor variable to relate field to bit position in structure rddLaneMuxFifoSyncError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_rddLaneMuxFifoSyncError u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure rddLaneMuxFifoSyncError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_rddLaneMuxFifoSyncError u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure xfi0Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_xfi0Invalid_66bCharacterReceived 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_xfi0Invalid_66bCharacterReceived u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi0Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_xfi0Invalid_66bCharacterReceived u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi0ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_xfi0ReceiveLinkStatusLatchHigh 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_xfi0ReceiveLinkStatusLatchHigh u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_xfi0ReceiveLinkStatusLatchHigh u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0HighBerStatus in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_xfi0HighBerStatus 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0HighBerStatus in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_xfi0HighBerStatus u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0HighBerStatus in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_xfi0HighBerStatus u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BlockLockStatus in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_xfi0BlockLockStatus 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BlockLockStatus in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_xfi0BlockLockStatus u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BlockLockStatus in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_xfi0BlockLockStatus u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketGapFifoError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketGapFifoError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketGapFifoError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketGapFifoError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketGapFifoError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketGapFifoError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketGapFifoParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketGapFifoParityError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketGapFifoParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketGapFifoParityError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketGapFifoParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketGapFifoParityError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketReadyFifoError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketReadyFifoError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketReadyFifoError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketReadyFifoError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketReadyFifoError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketReadyFifoError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketReadyFifoParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketReadyFifoParityError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketReadyFifoParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketReadyFifoParityError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketReadyFifoParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketReadyFifoParityError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketRemoveError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketRemoveError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketRemoveError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketRemoveError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketRemoveError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketRemoveError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketReceived in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketReceived 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketReceived in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketReceived u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketReceived in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketReceived u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketPipelineFifoError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketPipelineFifoError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketPipelineFifoError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketPipelineFifoError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketPipelineFifoError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketPipelineFifoError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketPipelineParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketPipelineParityError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketPipelineParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketPipelineParityError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketPipelineParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketPipelineParityError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampBufferParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressTimeStampBufferParityError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampBufferParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressTimeStampBufferParityError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampBufferParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressTimeStampBufferParityError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketBufferParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketBufferParityError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketBufferParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketBufferParityError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketBufferParityError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketBufferParityError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketCorrectionFieldError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketCorrectionFieldError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketCorrectionFieldError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketCorrectionFieldError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketCorrectionFieldError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketCorrectionFieldError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketBufferOverflowError in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketBufferOverflowError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketBufferOverflowError in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketBufferOverflowError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketBufferOverflowError in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketBufferOverflowError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampReady in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressTimeStampReady 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampReady in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressTimeStampReady u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampReady in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressTimeStampReady u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketReady in AQ_PcsReceiveVendorAlarms_EUR */
#define AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketReady 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketReady in AQ_PcsReceiveVendorAlarms_EUR */
#define bits_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketReady u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketReady in AQ_PcsReceiveVendorAlarms_EUR */
#define word_AQ_PcsReceiveVendorAlarms_EUR_ptpIngressPacketReady u9.word_9

/*! \brief Base register address of structure AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_baseRegisterAddress 0xF400
/*! \brief MMD address of structure AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure crcErrorMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_crcErrorMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure crcErrorMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_crcErrorMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure crcErrorMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_crcErrorMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldpcDecodeFailureMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_ldpcDecodeFailureMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldpcDecodeFailureMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_ldpcDecodeFailureMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldpcDecodeFailureMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_ldpcDecodeFailureMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rplLinkFailureMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_rplLinkFailureMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure rplLinkFailureMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_rplLinkFailureMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rplLinkFailureMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_rplLinkFailureMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _40gBipLockMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR__40gBipLockMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure _40gBipLockMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR__40gBipLockMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _40gBipLockMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR__40gBipLockMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure localFaultDetectMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_localFaultDetectMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure localFaultDetectMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_localFaultDetectMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure localFaultDetectMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_localFaultDetectMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lofDetectMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_lofDetectMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure lofDetectMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_lofDetectMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lofDetectMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_lofDetectMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure invalid_513bBlockMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_invalid_513bBlockMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure invalid_513bBlockMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_invalid_513bBlockMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure invalid_513bBlockMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_invalid_513bBlockMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure invalid_65bBlockMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_invalid_65bBlockMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure invalid_65bBlockMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_invalid_65bBlockMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure invalid_65bBlockMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_invalid_65bBlockMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiActiveOffMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiActiveOffMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiActiveOffMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiActiveOffMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiActiveOffMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiActiveOffMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiActiveOnMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiActiveOnMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiActiveOnMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiActiveOnMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiActiveOnMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiActiveOnMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldpcConsecutiveErroredFrameExceededMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_ldpcConsecutiveErroredFrameExceededMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldpcConsecutiveErroredFrameExceededMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_ldpcConsecutiveErroredFrameExceededMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldpcConsecutiveErroredFrameExceededMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_ldpcConsecutiveErroredFrameExceededMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiAlertMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiAlertMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiAlertMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiAlertMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiAlertMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiAlertMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiReceivedLatchedLowMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiReceivedLatchedLowMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiReceivedLatchedLowMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiReceivedLatchedLowMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiReceivedLatchedLowMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiReceivedLatchedLowMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiReceivedLatchedHighMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiReceivedLatchedHighMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiReceivedLatchedHighMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiReceivedLatchedHighMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiReceivedLatchedHighMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_eeeRxLpiReceivedLatchedHighMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure changeInAuxilliaryBitMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_changeInAuxilliaryBitMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure changeInAuxilliaryBitMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_changeInAuxilliaryBitMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure changeInAuxilliaryBitMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_changeInAuxilliaryBitMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rddLaneMuxFifoParityError in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_rddLaneMuxFifoParityError 4
/*! \brief Preprocessor variable to relate field to bit position in structure rddLaneMuxFifoParityError in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_rddLaneMuxFifoParityError u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure rddLaneMuxFifoParityError in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_rddLaneMuxFifoParityError u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure rddLaneMuxFifoSyncError in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_rddLaneMuxFifoSyncError 4
/*! \brief Preprocessor variable to relate field to bit position in structure rddLaneMuxFifoSyncError in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_rddLaneMuxFifoSyncError u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure rddLaneMuxFifoSyncError in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_rddLaneMuxFifoSyncError u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure xfi0Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_xfi0Invalid_66bCharacterReceivedMask 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_xfi0Invalid_66bCharacterReceivedMask u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi0Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_xfi0Invalid_66bCharacterReceivedMask u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi0ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_xfi0ReceiveLinkStatusLatchHighMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_xfi0ReceiveLinkStatusLatchHighMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_xfi0ReceiveLinkStatusLatchHighMask u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_xfi0HighBerStatusMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_xfi0HighBerStatusMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_xfi0HighBerStatusMask u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define AQ_PcsReceiveVendorInterruptMask_EUR_xfi0BlockLockStatusMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define bits_AQ_PcsReceiveVendorInterruptMask_EUR_xfi0BlockLockStatusMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_EUR */
#define word_AQ_PcsReceiveVendorInterruptMask_EUR_xfi0BlockLockStatusMask u6.word_6

/*! \brief Base register address of structure AQ_PcsReceiveVendorDebug_EUR */
#define AQ_PcsReceiveVendorDebug_EUR_baseRegisterAddress 0xF800
/*! \brief MMD address of structure AQ_PcsReceiveVendorDebug_EUR */
#define AQ_PcsReceiveVendorDebug_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsRxDescramblerDisable in AQ_PcsReceiveVendorDebug_EUR */
#define AQ_PcsReceiveVendorDebug_EUR_pcsRxDescramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsRxDescramblerDisable in AQ_PcsReceiveVendorDebug_EUR */
#define bits_AQ_PcsReceiveVendorDebug_EUR_pcsRxDescramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsRxDescramblerDisable in AQ_PcsReceiveVendorDebug_EUR */
#define word_AQ_PcsReceiveVendorDebug_EUR_pcsRxDescramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsNetworkLoopbackMerge in AQ_PcsReceiveVendorDebug_EUR */
#define AQ_PcsReceiveVendorDebug_EUR_pcsNetworkLoopbackMerge 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsNetworkLoopbackMerge in AQ_PcsReceiveVendorDebug_EUR */
#define bits_AQ_PcsReceiveVendorDebug_EUR_pcsNetworkLoopbackMerge u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsNetworkLoopbackMerge in AQ_PcsReceiveVendorDebug_EUR */
#define word_AQ_PcsReceiveVendorDebug_EUR_pcsNetworkLoopbackMerge u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsNetworkLoopbackPassThrough in AQ_PcsReceiveVendorDebug_EUR */
#define AQ_PcsReceiveVendorDebug_EUR_pcsNetworkLoopbackPassThrough 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsNetworkLoopbackPassThrough in AQ_PcsReceiveVendorDebug_EUR */
#define bits_AQ_PcsReceiveVendorDebug_EUR_pcsNetworkLoopbackPassThrough u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsNetworkLoopbackPassThrough in AQ_PcsReceiveVendorDebug_EUR */
#define word_AQ_PcsReceiveVendorDebug_EUR_pcsNetworkLoopbackPassThrough u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsNetworkLoopback in AQ_PcsReceiveVendorDebug_EUR */
#define AQ_PcsReceiveVendorDebug_EUR_pcsNetworkLoopback 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsNetworkLoopback in AQ_PcsReceiveVendorDebug_EUR */
#define bits_AQ_PcsReceiveVendorDebug_EUR_pcsNetworkLoopback u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsNetworkLoopback in AQ_PcsReceiveVendorDebug_EUR */
#define word_AQ_PcsReceiveVendorDebug_EUR_pcsNetworkLoopback u0.word_0

/*! \brief Base register address of structure AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_baseRegisterAddress 0xFC00
/*! \brief MMD address of structure AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarm_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_standardAlarm_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarm_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define bits_AQ_PcsVendorGlobalInterruptFlags_EUR_standardAlarm_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarm_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define word_AQ_PcsVendorGlobalInterruptFlags_EUR_standardAlarm_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarm_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_standardAlarm_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarm_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define bits_AQ_PcsVendorGlobalInterruptFlags_EUR_standardAlarm_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarm_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define word_AQ_PcsVendorGlobalInterruptFlags_EUR_standardAlarm_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarm_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_standardAlarm_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarm_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define bits_AQ_PcsVendorGlobalInterruptFlags_EUR_standardAlarm_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarm_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define word_AQ_PcsVendorGlobalInterruptFlags_EUR_standardAlarm_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificTxAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define bits_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificTxAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define word_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificTxAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificTxAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define bits_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificTxAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define word_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificTxAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificTxAlarms_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define bits_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificTxAlarms_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define word_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificTxAlarms_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define bits_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define word_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define bits_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define word_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define bits_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define word_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_4Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_4Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_4Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define bits_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_4Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_4Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define word_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_4Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_5Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_5Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_5Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define bits_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_5Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_5Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define word_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_5Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_6Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_6Interrupt 2
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_6Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define bits_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_6Interrupt u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_6Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define word_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_6Interrupt u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_7Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_7Interrupt 2
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_7Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define bits_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_7Interrupt u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_7Interrupt in AQ_PcsVendorGlobalInterruptFlags_EUR */
#define word_AQ_PcsVendorGlobalInterruptFlags_EUR_vendorSpecificRxAlarms_7Interrupt u2.word_2
#endif
/*@}*/
/*@}*/
