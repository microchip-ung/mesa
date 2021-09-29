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
#ifndef AQ_HHD_PCS_REGS_DEFINES_HEADER
#define AQ_HHD_PCS_REGS_DEFINES_HEADER


/*-----------------------------------------------------------------------------*/
/*Access macro definitions                                                     */
/*-----------------------------------------------------------------------------*/
/*! \brief Base register address of structure AQ_PcsStandardControl_1_HHD */
#define AQ_PcsStandardControl_1_HHD_baseRegisterAddress 0x0000
/*! \brief MMD address of structure AQ_PcsStandardControl_1_HHD */
#define AQ_PcsStandardControl_1_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reset in AQ_PcsStandardControl_1_HHD */
#define AQ_PcsStandardControl_1_HHD_reset 0
/*! \brief Preprocessor variable to relate field to bit position in structure reset in AQ_PcsStandardControl_1_HHD */
#define bits_AQ_PcsStandardControl_1_HHD_reset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reset in AQ_PcsStandardControl_1_HHD */
#define word_AQ_PcsStandardControl_1_HHD_reset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure loopback in AQ_PcsStandardControl_1_HHD */
#define AQ_PcsStandardControl_1_HHD_loopback 0
/*! \brief Preprocessor variable to relate field to bit position in structure loopback in AQ_PcsStandardControl_1_HHD */
#define bits_AQ_PcsStandardControl_1_HHD_loopback u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure loopback in AQ_PcsStandardControl_1_HHD */
#define word_AQ_PcsStandardControl_1_HHD_loopback u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure speedSelectionLsb in AQ_PcsStandardControl_1_HHD */
#define AQ_PcsStandardControl_1_HHD_speedSelectionLsb 0
/*! \brief Preprocessor variable to relate field to bit position in structure speedSelectionLsb in AQ_PcsStandardControl_1_HHD */
#define bits_AQ_PcsStandardControl_1_HHD_speedSelectionLsb u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure speedSelectionLsb in AQ_PcsStandardControl_1_HHD */
#define word_AQ_PcsStandardControl_1_HHD_speedSelectionLsb u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowPower in AQ_PcsStandardControl_1_HHD */
#define AQ_PcsStandardControl_1_HHD_lowPower 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowPower in AQ_PcsStandardControl_1_HHD */
#define bits_AQ_PcsStandardControl_1_HHD_lowPower u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowPower in AQ_PcsStandardControl_1_HHD */
#define word_AQ_PcsStandardControl_1_HHD_lowPower u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clockStopEnable in AQ_PcsStandardControl_1_HHD */
#define AQ_PcsStandardControl_1_HHD_clockStopEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure clockStopEnable in AQ_PcsStandardControl_1_HHD */
#define bits_AQ_PcsStandardControl_1_HHD_clockStopEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clockStopEnable in AQ_PcsStandardControl_1_HHD */
#define word_AQ_PcsStandardControl_1_HHD_clockStopEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure speedSelectionMsb in AQ_PcsStandardControl_1_HHD */
#define AQ_PcsStandardControl_1_HHD_speedSelectionMsb 0
/*! \brief Preprocessor variable to relate field to bit position in structure speedSelectionMsb in AQ_PcsStandardControl_1_HHD */
#define bits_AQ_PcsStandardControl_1_HHD_speedSelectionMsb u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure speedSelectionMsb in AQ_PcsStandardControl_1_HHD */
#define word_AQ_PcsStandardControl_1_HHD_speedSelectionMsb u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gSpeedSelection in AQ_PcsStandardControl_1_HHD */
#define AQ_PcsStandardControl_1_HHD__10gSpeedSelection 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gSpeedSelection in AQ_PcsStandardControl_1_HHD */
#define bits_AQ_PcsStandardControl_1_HHD__10gSpeedSelection u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gSpeedSelection in AQ_PcsStandardControl_1_HHD */
#define word_AQ_PcsStandardControl_1_HHD__10gSpeedSelection u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardStatus_1_HHD */
#define AQ_PcsStandardStatus_1_HHD_baseRegisterAddress 0x0001
/*! \brief MMD address of structure AQ_PcsStandardStatus_1_HHD */
#define AQ_PcsStandardStatus_1_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure txLpiReceived in AQ_PcsStandardStatus_1_HHD */
#define AQ_PcsStandardStatus_1_HHD_txLpiReceived 0
/*! \brief Preprocessor variable to relate field to bit position in structure txLpiReceived in AQ_PcsStandardStatus_1_HHD */
#define bits_AQ_PcsStandardStatus_1_HHD_txLpiReceived u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure txLpiReceived in AQ_PcsStandardStatus_1_HHD */
#define word_AQ_PcsStandardStatus_1_HHD_txLpiReceived u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rxLpiReceived in AQ_PcsStandardStatus_1_HHD */
#define AQ_PcsStandardStatus_1_HHD_rxLpiReceived 0
/*! \brief Preprocessor variable to relate field to bit position in structure rxLpiReceived in AQ_PcsStandardStatus_1_HHD */
#define bits_AQ_PcsStandardStatus_1_HHD_rxLpiReceived u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rxLpiReceived in AQ_PcsStandardStatus_1_HHD */
#define word_AQ_PcsStandardStatus_1_HHD_rxLpiReceived u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure txLpiIndication in AQ_PcsStandardStatus_1_HHD */
#define AQ_PcsStandardStatus_1_HHD_txLpiIndication 0
/*! \brief Preprocessor variable to relate field to bit position in structure txLpiIndication in AQ_PcsStandardStatus_1_HHD */
#define bits_AQ_PcsStandardStatus_1_HHD_txLpiIndication u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure txLpiIndication in AQ_PcsStandardStatus_1_HHD */
#define word_AQ_PcsStandardStatus_1_HHD_txLpiIndication u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rxLpiIndication in AQ_PcsStandardStatus_1_HHD */
#define AQ_PcsStandardStatus_1_HHD_rxLpiIndication 0
/*! \brief Preprocessor variable to relate field to bit position in structure rxLpiIndication in AQ_PcsStandardStatus_1_HHD */
#define bits_AQ_PcsStandardStatus_1_HHD_rxLpiIndication u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rxLpiIndication in AQ_PcsStandardStatus_1_HHD */
#define word_AQ_PcsStandardStatus_1_HHD_rxLpiIndication u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure fault in AQ_PcsStandardStatus_1_HHD */
#define AQ_PcsStandardStatus_1_HHD_fault 0
/*! \brief Preprocessor variable to relate field to bit position in structure fault in AQ_PcsStandardStatus_1_HHD */
#define bits_AQ_PcsStandardStatus_1_HHD_fault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure fault in AQ_PcsStandardStatus_1_HHD */
#define word_AQ_PcsStandardStatus_1_HHD_fault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clockStopCapable in AQ_PcsStandardStatus_1_HHD */
#define AQ_PcsStandardStatus_1_HHD_clockStopCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure clockStopCapable in AQ_PcsStandardStatus_1_HHD */
#define bits_AQ_PcsStandardStatus_1_HHD_clockStopCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clockStopCapable in AQ_PcsStandardStatus_1_HHD */
#define word_AQ_PcsStandardStatus_1_HHD_clockStopCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsReceiveLinkStatus in AQ_PcsStandardStatus_1_HHD */
#define AQ_PcsStandardStatus_1_HHD_pcsReceiveLinkStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsReceiveLinkStatus in AQ_PcsStandardStatus_1_HHD */
#define bits_AQ_PcsStandardStatus_1_HHD_pcsReceiveLinkStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsReceiveLinkStatus in AQ_PcsStandardStatus_1_HHD */
#define word_AQ_PcsStandardStatus_1_HHD_pcsReceiveLinkStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowPowerAbility in AQ_PcsStandardStatus_1_HHD */
#define AQ_PcsStandardStatus_1_HHD_lowPowerAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowPowerAbility in AQ_PcsStandardStatus_1_HHD */
#define bits_AQ_PcsStandardStatus_1_HHD_lowPowerAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowPowerAbility in AQ_PcsStandardStatus_1_HHD */
#define word_AQ_PcsStandardStatus_1_HHD_lowPowerAbility u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardDeviceIdentifier_HHD */
#define AQ_PcsStandardDeviceIdentifier_HHD_baseRegisterAddress 0x0002
/*! \brief MMD address of structure AQ_PcsStandardDeviceIdentifier_HHD */
#define AQ_PcsStandardDeviceIdentifier_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdMSW in AQ_PcsStandardDeviceIdentifier_HHD */
#define AQ_PcsStandardDeviceIdentifier_HHD_deviceIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdMSW in AQ_PcsStandardDeviceIdentifier_HHD */
#define bits_AQ_PcsStandardDeviceIdentifier_HHD_deviceIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdMSW in AQ_PcsStandardDeviceIdentifier_HHD */
#define word_AQ_PcsStandardDeviceIdentifier_HHD_deviceIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdLSW in AQ_PcsStandardDeviceIdentifier_HHD */
#define AQ_PcsStandardDeviceIdentifier_HHD_deviceIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdLSW in AQ_PcsStandardDeviceIdentifier_HHD */
#define bits_AQ_PcsStandardDeviceIdentifier_HHD_deviceIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdLSW in AQ_PcsStandardDeviceIdentifier_HHD */
#define word_AQ_PcsStandardDeviceIdentifier_HHD_deviceIdLSW u1.word_1

/*! \brief Base register address of structure AQ_PcsStandardSpeedAbility_HHD */
#define AQ_PcsStandardSpeedAbility_HHD_baseRegisterAddress 0x0004
/*! \brief MMD address of structure AQ_PcsStandardSpeedAbility_HHD */
#define AQ_PcsStandardSpeedAbility_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10pass_ts__2base_tlCapable in AQ_PcsStandardSpeedAbility_HHD */
#define AQ_PcsStandardSpeedAbility_HHD__10pass_ts__2base_tlCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10pass_ts__2base_tlCapable in AQ_PcsStandardSpeedAbility_HHD */
#define bits_AQ_PcsStandardSpeedAbility_HHD__10pass_ts__2base_tlCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10pass_ts__2base_tlCapable in AQ_PcsStandardSpeedAbility_HHD */
#define word_AQ_PcsStandardSpeedAbility_HHD__10pass_ts__2base_tlCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gCapable in AQ_PcsStandardSpeedAbility_HHD */
#define AQ_PcsStandardSpeedAbility_HHD__10gCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gCapable in AQ_PcsStandardSpeedAbility_HHD */
#define bits_AQ_PcsStandardSpeedAbility_HHD__10gCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gCapable in AQ_PcsStandardSpeedAbility_HHD */
#define word_AQ_PcsStandardSpeedAbility_HHD__10gCapable u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardDevicesInPackage_HHD */
#define AQ_PcsStandardDevicesInPackage_HHD_baseRegisterAddress 0x0005
/*! \brief MMD address of structure AQ_PcsStandardDevicesInPackage_HHD */
#define AQ_PcsStandardDevicesInPackage_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define AQ_PcsStandardDevicesInPackage_HHD_autonegotiationPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define bits_AQ_PcsStandardDevicesInPackage_HHD_autonegotiationPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define word_AQ_PcsStandardDevicesInPackage_HHD_autonegotiationPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tcPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define AQ_PcsStandardDevicesInPackage_HHD_tcPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure tcPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define bits_AQ_PcsStandardDevicesInPackage_HHD_tcPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tcPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define word_AQ_PcsStandardDevicesInPackage_HHD_tcPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure dteXsPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define AQ_PcsStandardDevicesInPackage_HHD_dteXsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure dteXsPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define bits_AQ_PcsStandardDevicesInPackage_HHD_dteXsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure dteXsPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define word_AQ_PcsStandardDevicesInPackage_HHD_dteXsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_Present in AQ_PcsStandardDevicesInPackage_HHD */
#define AQ_PcsStandardDevicesInPackage_HHD_phyXS_Present 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_Present in AQ_PcsStandardDevicesInPackage_HHD */
#define bits_AQ_PcsStandardDevicesInPackage_HHD_phyXS_Present u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_Present in AQ_PcsStandardDevicesInPackage_HHD */
#define word_AQ_PcsStandardDevicesInPackage_HHD_phyXS_Present u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define AQ_PcsStandardDevicesInPackage_HHD_pcsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define bits_AQ_PcsStandardDevicesInPackage_HHD_pcsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define word_AQ_PcsStandardDevicesInPackage_HHD_pcsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure wisPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define AQ_PcsStandardDevicesInPackage_HHD_wisPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure wisPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define bits_AQ_PcsStandardDevicesInPackage_HHD_wisPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure wisPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define word_AQ_PcsStandardDevicesInPackage_HHD_wisPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define AQ_PcsStandardDevicesInPackage_HHD_pmaPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define bits_AQ_PcsStandardDevicesInPackage_HHD_pmaPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define word_AQ_PcsStandardDevicesInPackage_HHD_pmaPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clause_22RegistersPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define AQ_PcsStandardDevicesInPackage_HHD_clause_22RegistersPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22RegistersPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define bits_AQ_PcsStandardDevicesInPackage_HHD_clause_22RegistersPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clause_22RegistersPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define word_AQ_PcsStandardDevicesInPackage_HHD_clause_22RegistersPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_2Present in AQ_PcsStandardDevicesInPackage_HHD */
#define AQ_PcsStandardDevicesInPackage_HHD_vendorSpecificDevice_2Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_2Present in AQ_PcsStandardDevicesInPackage_HHD */
#define bits_AQ_PcsStandardDevicesInPackage_HHD_vendorSpecificDevice_2Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_2Present in AQ_PcsStandardDevicesInPackage_HHD */
#define word_AQ_PcsStandardDevicesInPackage_HHD_vendorSpecificDevice_2Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_1Present in AQ_PcsStandardDevicesInPackage_HHD */
#define AQ_PcsStandardDevicesInPackage_HHD_vendorSpecificDevice_1Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_1Present in AQ_PcsStandardDevicesInPackage_HHD */
#define bits_AQ_PcsStandardDevicesInPackage_HHD_vendorSpecificDevice_1Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_1Present in AQ_PcsStandardDevicesInPackage_HHD */
#define word_AQ_PcsStandardDevicesInPackage_HHD_vendorSpecificDevice_1Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure clause_22ExtensionPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define AQ_PcsStandardDevicesInPackage_HHD_clause_22ExtensionPresent 1
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22ExtensionPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define bits_AQ_PcsStandardDevicesInPackage_HHD_clause_22ExtensionPresent u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure clause_22ExtensionPresent in AQ_PcsStandardDevicesInPackage_HHD */
#define word_AQ_PcsStandardDevicesInPackage_HHD_clause_22ExtensionPresent u1.word_1

/*! \brief Base register address of structure AQ_PcsStandardControl_2_HHD */
#define AQ_PcsStandardControl_2_HHD_baseRegisterAddress 0x0007
/*! \brief MMD address of structure AQ_PcsStandardControl_2_HHD */
#define AQ_PcsStandardControl_2_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsDeviceType in AQ_PcsStandardControl_2_HHD */
#define AQ_PcsStandardControl_2_HHD_pcsDeviceType 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsDeviceType in AQ_PcsStandardControl_2_HHD */
#define bits_AQ_PcsStandardControl_2_HHD_pcsDeviceType u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsDeviceType in AQ_PcsStandardControl_2_HHD */
#define word_AQ_PcsStandardControl_2_HHD_pcsDeviceType u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardStatus_2_HHD */
#define AQ_PcsStandardStatus_2_HHD_baseRegisterAddress 0x0008
/*! \brief MMD address of structure AQ_PcsStandardStatus_2_HHD */
#define AQ_PcsStandardStatus_2_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure devicePresent in AQ_PcsStandardStatus_2_HHD */
#define AQ_PcsStandardStatus_2_HHD_devicePresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure devicePresent in AQ_PcsStandardStatus_2_HHD */
#define bits_AQ_PcsStandardStatus_2_HHD_devicePresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure devicePresent in AQ_PcsStandardStatus_2_HHD */
#define word_AQ_PcsStandardStatus_2_HHD_devicePresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitFault in AQ_PcsStandardStatus_2_HHD */
#define AQ_PcsStandardStatus_2_HHD_transmitFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure transmitFault in AQ_PcsStandardStatus_2_HHD */
#define bits_AQ_PcsStandardStatus_2_HHD_transmitFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure transmitFault in AQ_PcsStandardStatus_2_HHD */
#define word_AQ_PcsStandardStatus_2_HHD_transmitFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure receiveFault in AQ_PcsStandardStatus_2_HHD */
#define AQ_PcsStandardStatus_2_HHD_receiveFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure receiveFault in AQ_PcsStandardStatus_2_HHD */
#define bits_AQ_PcsStandardStatus_2_HHD_receiveFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure receiveFault in AQ_PcsStandardStatus_2_HHD */
#define word_AQ_PcsStandardStatus_2_HHD_receiveFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tCapable in AQ_PcsStandardStatus_2_HHD */
#define AQ_PcsStandardStatus_2_HHD__10gbase_tCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tCapable in AQ_PcsStandardStatus_2_HHD */
#define bits_AQ_PcsStandardStatus_2_HHD__10gbase_tCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tCapable in AQ_PcsStandardStatus_2_HHD */
#define word_AQ_PcsStandardStatus_2_HHD__10gbase_tCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_wCapable in AQ_PcsStandardStatus_2_HHD */
#define AQ_PcsStandardStatus_2_HHD__10gbase_wCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_wCapable in AQ_PcsStandardStatus_2_HHD */
#define bits_AQ_PcsStandardStatus_2_HHD__10gbase_wCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_wCapable in AQ_PcsStandardStatus_2_HHD */
#define word_AQ_PcsStandardStatus_2_HHD__10gbase_wCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_xCapable in AQ_PcsStandardStatus_2_HHD */
#define AQ_PcsStandardStatus_2_HHD__10gbase_xCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_xCapable in AQ_PcsStandardStatus_2_HHD */
#define bits_AQ_PcsStandardStatus_2_HHD__10gbase_xCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_xCapable in AQ_PcsStandardStatus_2_HHD */
#define word_AQ_PcsStandardStatus_2_HHD__10gbase_xCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_rCapable in AQ_PcsStandardStatus_2_HHD */
#define AQ_PcsStandardStatus_2_HHD__10gbase_rCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_rCapable in AQ_PcsStandardStatus_2_HHD */
#define bits_AQ_PcsStandardStatus_2_HHD__10gbase_rCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_rCapable in AQ_PcsStandardStatus_2_HHD */
#define word_AQ_PcsStandardStatus_2_HHD__10gbase_rCapable u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardPackageIdentifier_HHD */
#define AQ_PcsStandardPackageIdentifier_HHD_baseRegisterAddress 0x000E
/*! \brief MMD address of structure AQ_PcsStandardPackageIdentifier_HHD */
#define AQ_PcsStandardPackageIdentifier_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure packageIdMSW in AQ_PcsStandardPackageIdentifier_HHD */
#define AQ_PcsStandardPackageIdentifier_HHD_packageIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdMSW in AQ_PcsStandardPackageIdentifier_HHD */
#define bits_AQ_PcsStandardPackageIdentifier_HHD_packageIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure packageIdMSW in AQ_PcsStandardPackageIdentifier_HHD */
#define word_AQ_PcsStandardPackageIdentifier_HHD_packageIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure packageIdLSW in AQ_PcsStandardPackageIdentifier_HHD */
#define AQ_PcsStandardPackageIdentifier_HHD_packageIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdLSW in AQ_PcsStandardPackageIdentifier_HHD */
#define bits_AQ_PcsStandardPackageIdentifier_HHD_packageIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure packageIdLSW in AQ_PcsStandardPackageIdentifier_HHD */
#define word_AQ_PcsStandardPackageIdentifier_HHD_packageIdLSW u1.word_1

/*! \brief Base register address of structure AQ_PcsEeeCapabilityRegister_HHD */
#define AQ_PcsEeeCapabilityRegister_HHD_baseRegisterAddress 0x0014
/*! \brief MMD address of structure AQ_PcsEeeCapabilityRegister_HHD */
#define AQ_PcsEeeCapabilityRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_krEee in AQ_PcsEeeCapabilityRegister_HHD */
#define AQ_PcsEeeCapabilityRegister_HHD__10gbase_krEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_krEee in AQ_PcsEeeCapabilityRegister_HHD */
#define bits_AQ_PcsEeeCapabilityRegister_HHD__10gbase_krEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_krEee in AQ_PcsEeeCapabilityRegister_HHD */
#define word_AQ_PcsEeeCapabilityRegister_HHD__10gbase_krEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_kx4Eee in AQ_PcsEeeCapabilityRegister_HHD */
#define AQ_PcsEeeCapabilityRegister_HHD__10gbase_kx4Eee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_kx4Eee in AQ_PcsEeeCapabilityRegister_HHD */
#define bits_AQ_PcsEeeCapabilityRegister_HHD__10gbase_kx4Eee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_kx4Eee in AQ_PcsEeeCapabilityRegister_HHD */
#define word_AQ_PcsEeeCapabilityRegister_HHD__10gbase_kx4Eee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _1000base_kxEee in AQ_PcsEeeCapabilityRegister_HHD */
#define AQ_PcsEeeCapabilityRegister_HHD__1000base_kxEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _1000base_kxEee in AQ_PcsEeeCapabilityRegister_HHD */
#define bits_AQ_PcsEeeCapabilityRegister_HHD__1000base_kxEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _1000base_kxEee in AQ_PcsEeeCapabilityRegister_HHD */
#define word_AQ_PcsEeeCapabilityRegister_HHD__1000base_kxEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tEee in AQ_PcsEeeCapabilityRegister_HHD */
#define AQ_PcsEeeCapabilityRegister_HHD__10gbase_tEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tEee in AQ_PcsEeeCapabilityRegister_HHD */
#define bits_AQ_PcsEeeCapabilityRegister_HHD__10gbase_tEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tEee in AQ_PcsEeeCapabilityRegister_HHD */
#define word_AQ_PcsEeeCapabilityRegister_HHD__10gbase_tEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _1000base_tEee in AQ_PcsEeeCapabilityRegister_HHD */
#define AQ_PcsEeeCapabilityRegister_HHD__1000base_tEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _1000base_tEee in AQ_PcsEeeCapabilityRegister_HHD */
#define bits_AQ_PcsEeeCapabilityRegister_HHD__1000base_tEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _1000base_tEee in AQ_PcsEeeCapabilityRegister_HHD */
#define word_AQ_PcsEeeCapabilityRegister_HHD__1000base_tEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _100base_txEee in AQ_PcsEeeCapabilityRegister_HHD */
#define AQ_PcsEeeCapabilityRegister_HHD__100base_txEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _100base_txEee in AQ_PcsEeeCapabilityRegister_HHD */
#define bits_AQ_PcsEeeCapabilityRegister_HHD__100base_txEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _100base_txEee in AQ_PcsEeeCapabilityRegister_HHD */
#define word_AQ_PcsEeeCapabilityRegister_HHD__100base_txEee u0.word_0

/*! \brief Base register address of structure AQ_PcsEeeWakeErrorCounter_HHD */
#define AQ_PcsEeeWakeErrorCounter_HHD_baseRegisterAddress 0x0016
/*! \brief MMD address of structure AQ_PcsEeeWakeErrorCounter_HHD */
#define AQ_PcsEeeWakeErrorCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure eeeWakeErrorCounter in AQ_PcsEeeWakeErrorCounter_HHD */
#define AQ_PcsEeeWakeErrorCounter_HHD_eeeWakeErrorCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeWakeErrorCounter in AQ_PcsEeeWakeErrorCounter_HHD */
#define bits_AQ_PcsEeeWakeErrorCounter_HHD_eeeWakeErrorCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeWakeErrorCounter in AQ_PcsEeeWakeErrorCounter_HHD */
#define word_AQ_PcsEeeWakeErrorCounter_HHD_eeeWakeErrorCounter u0.word_0

/*! \brief Base register address of structure AQ_Pcs10G_Status_HHD */
#define AQ_Pcs10G_Status_HHD_baseRegisterAddress 0x0020
/*! \brief MMD address of structure AQ_Pcs10G_Status_HHD */
#define AQ_Pcs10G_Status_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gReceiveLinkStatus in AQ_Pcs10G_Status_HHD */
#define AQ_Pcs10G_Status_HHD__10gReceiveLinkStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gReceiveLinkStatus in AQ_Pcs10G_Status_HHD */
#define bits_AQ_Pcs10G_Status_HHD__10gReceiveLinkStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gReceiveLinkStatus in AQ_Pcs10G_Status_HHD */
#define word_AQ_Pcs10G_Status_HHD__10gReceiveLinkStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_rPrbs9PatternTestingAbility in AQ_Pcs10G_Status_HHD */
#define AQ_Pcs10G_Status_HHD__10gbase_rPrbs9PatternTestingAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_rPrbs9PatternTestingAbility in AQ_Pcs10G_Status_HHD */
#define bits_AQ_Pcs10G_Status_HHD__10gbase_rPrbs9PatternTestingAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_rPrbs9PatternTestingAbility in AQ_Pcs10G_Status_HHD */
#define word_AQ_Pcs10G_Status_HHD__10gbase_rPrbs9PatternTestingAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_rPrbs31PatternTestingAbility in AQ_Pcs10G_Status_HHD */
#define AQ_Pcs10G_Status_HHD__10gbase_rPrbs31PatternTestingAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_rPrbs31PatternTestingAbility in AQ_Pcs10G_Status_HHD */
#define bits_AQ_Pcs10G_Status_HHD__10gbase_rPrbs31PatternTestingAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_rPrbs31PatternTestingAbility in AQ_Pcs10G_Status_HHD */
#define word_AQ_Pcs10G_Status_HHD__10gbase_rPrbs31PatternTestingAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gHighBer in AQ_Pcs10G_Status_HHD */
#define AQ_Pcs10G_Status_HHD__10gHighBer 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gHighBer in AQ_Pcs10G_Status_HHD */
#define bits_AQ_Pcs10G_Status_HHD__10gHighBer u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gHighBer in AQ_Pcs10G_Status_HHD */
#define word_AQ_Pcs10G_Status_HHD__10gHighBer u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gPcsBlockLock in AQ_Pcs10G_Status_HHD */
#define AQ_Pcs10G_Status_HHD__10gPcsBlockLock 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gPcsBlockLock in AQ_Pcs10G_Status_HHD */
#define bits_AQ_Pcs10G_Status_HHD__10gPcsBlockLock u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gPcsBlockLock in AQ_Pcs10G_Status_HHD */
#define word_AQ_Pcs10G_Status_HHD__10gPcsBlockLock u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsBlockLockLatched in AQ_Pcs10G_Status_HHD */
#define AQ_Pcs10G_Status_HHD_pcsBlockLockLatched 1
/*! \brief Preprocessor variable to relate field to bit position in structure pcsBlockLockLatched in AQ_Pcs10G_Status_HHD */
#define bits_AQ_Pcs10G_Status_HHD_pcsBlockLockLatched u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pcsBlockLockLatched in AQ_Pcs10G_Status_HHD */
#define word_AQ_Pcs10G_Status_HHD_pcsBlockLockLatched u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure highBerLatched in AQ_Pcs10G_Status_HHD */
#define AQ_Pcs10G_Status_HHD_highBerLatched 1
/*! \brief Preprocessor variable to relate field to bit position in structure highBerLatched in AQ_Pcs10G_Status_HHD */
#define bits_AQ_Pcs10G_Status_HHD_highBerLatched u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure highBerLatched in AQ_Pcs10G_Status_HHD */
#define word_AQ_Pcs10G_Status_HHD_highBerLatched u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure erroredFrameCounter in AQ_Pcs10G_Status_HHD */
#define AQ_Pcs10G_Status_HHD_erroredFrameCounter 1
/*! \brief Preprocessor variable to relate field to bit position in structure erroredFrameCounter in AQ_Pcs10G_Status_HHD */
#define bits_AQ_Pcs10G_Status_HHD_erroredFrameCounter u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure erroredFrameCounter in AQ_Pcs10G_Status_HHD */
#define word_AQ_Pcs10G_Status_HHD_erroredFrameCounter u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure erroredBlockCounter in AQ_Pcs10G_Status_HHD */
#define AQ_Pcs10G_Status_HHD_erroredBlockCounter 1
/*! \brief Preprocessor variable to relate field to bit position in structure erroredBlockCounter in AQ_Pcs10G_Status_HHD */
#define bits_AQ_Pcs10G_Status_HHD_erroredBlockCounter u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure erroredBlockCounter in AQ_Pcs10G_Status_HHD */
#define word_AQ_Pcs10G_Status_HHD_erroredBlockCounter u1.word_1

/*! \brief Base register address of structure AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define AQ_Pcs10G_base_rTestPatternSeedA_HHD_baseRegisterAddress 0x0022
/*! \brief MMD address of structure AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define AQ_Pcs10G_base_rTestPatternSeedA_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedABits_15_0 in AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define AQ_Pcs10G_base_rTestPatternSeedA_HHD_testPatternSeedABits_15_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedABits_15_0 in AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define bits_AQ_Pcs10G_base_rTestPatternSeedA_HHD_testPatternSeedABits_15_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedABits_15_0 in AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define word_AQ_Pcs10G_base_rTestPatternSeedA_HHD_testPatternSeedABits_15_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedABits_31_16 in AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define AQ_Pcs10G_base_rTestPatternSeedA_HHD_testPatternSeedABits_31_16 1
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedABits_31_16 in AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define bits_AQ_Pcs10G_base_rTestPatternSeedA_HHD_testPatternSeedABits_31_16 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedABits_31_16 in AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define word_AQ_Pcs10G_base_rTestPatternSeedA_HHD_testPatternSeedABits_31_16 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedABits_47_32 in AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define AQ_Pcs10G_base_rTestPatternSeedA_HHD_testPatternSeedABits_47_32 2
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedABits_47_32 in AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define bits_AQ_Pcs10G_base_rTestPatternSeedA_HHD_testPatternSeedABits_47_32 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedABits_47_32 in AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define word_AQ_Pcs10G_base_rTestPatternSeedA_HHD_testPatternSeedABits_47_32 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedABits_57_48 in AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define AQ_Pcs10G_base_rTestPatternSeedA_HHD_testPatternSeedABits_57_48 3
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedABits_57_48 in AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define bits_AQ_Pcs10G_base_rTestPatternSeedA_HHD_testPatternSeedABits_57_48 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedABits_57_48 in AQ_Pcs10G_base_rTestPatternSeedA_HHD */
#define word_AQ_Pcs10G_base_rTestPatternSeedA_HHD_testPatternSeedABits_57_48 u3.word_3

/*! \brief Base register address of structure AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define AQ_Pcs10G_base_rTestPatternSeedB_HHD_baseRegisterAddress 0x0026
/*! \brief MMD address of structure AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define AQ_Pcs10G_base_rTestPatternSeedB_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedBBits_15_0 in AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define AQ_Pcs10G_base_rTestPatternSeedB_HHD_testPatternSeedBBits_15_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedBBits_15_0 in AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define bits_AQ_Pcs10G_base_rTestPatternSeedB_HHD_testPatternSeedBBits_15_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedBBits_15_0 in AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define word_AQ_Pcs10G_base_rTestPatternSeedB_HHD_testPatternSeedBBits_15_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedBBits_31_16 in AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define AQ_Pcs10G_base_rTestPatternSeedB_HHD_testPatternSeedBBits_31_16 1
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedBBits_31_16 in AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define bits_AQ_Pcs10G_base_rTestPatternSeedB_HHD_testPatternSeedBBits_31_16 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedBBits_31_16 in AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define word_AQ_Pcs10G_base_rTestPatternSeedB_HHD_testPatternSeedBBits_31_16 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedBBits_47_32 in AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define AQ_Pcs10G_base_rTestPatternSeedB_HHD_testPatternSeedBBits_47_32 2
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedBBits_47_32 in AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define bits_AQ_Pcs10G_base_rTestPatternSeedB_HHD_testPatternSeedBBits_47_32 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedBBits_47_32 in AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define word_AQ_Pcs10G_base_rTestPatternSeedB_HHD_testPatternSeedBBits_47_32 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSeedBBits_57_48 in AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define AQ_Pcs10G_base_rTestPatternSeedB_HHD_testPatternSeedBBits_57_48 3
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSeedBBits_57_48 in AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define bits_AQ_Pcs10G_base_rTestPatternSeedB_HHD_testPatternSeedBBits_57_48 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSeedBBits_57_48 in AQ_Pcs10G_base_rTestPatternSeedB_HHD */
#define word_AQ_Pcs10G_base_rTestPatternSeedB_HHD_testPatternSeedBBits_57_48 u3.word_3

/*! \brief Base register address of structure AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define AQ_Pcs10G_base_rPcsTest_patternControl_HHD_baseRegisterAddress 0x002A
/*! \brief MMD address of structure AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define AQ_Pcs10G_base_rPcsTest_patternControl_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure prbs9TransmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define AQ_Pcs10G_base_rPcsTest_patternControl_HHD_prbs9TransmitTest_patternEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure prbs9TransmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_prbs9TransmitTest_patternEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure prbs9TransmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_prbs9TransmitTest_patternEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure prbs31ReceiveTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define AQ_Pcs10G_base_rPcsTest_patternControl_HHD_prbs31ReceiveTest_patternEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure prbs31ReceiveTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_prbs31ReceiveTest_patternEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure prbs31ReceiveTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_prbs31ReceiveTest_patternEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure prbs31TransmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define AQ_Pcs10G_base_rPcsTest_patternControl_HHD_prbs31TransmitTest_patternEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure prbs31TransmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_prbs31TransmitTest_patternEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure prbs31TransmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_prbs31TransmitTest_patternEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define AQ_Pcs10G_base_rPcsTest_patternControl_HHD_transmitTest_patternEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure transmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_transmitTest_patternEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure transmitTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_transmitTest_patternEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure receiveTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define AQ_Pcs10G_base_rPcsTest_patternControl_HHD_receiveTest_patternEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure receiveTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_receiveTest_patternEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure receiveTest_patternEnable in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_receiveTest_patternEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure test_patternSelect in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define AQ_Pcs10G_base_rPcsTest_patternControl_HHD_test_patternSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure test_patternSelect in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_test_patternSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure test_patternSelect in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_test_patternSelect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure dataPatternSelect in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define AQ_Pcs10G_base_rPcsTest_patternControl_HHD_dataPatternSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure dataPatternSelect in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define bits_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_dataPatternSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure dataPatternSelect in AQ_Pcs10G_base_rPcsTest_patternControl_HHD */
#define word_AQ_Pcs10G_base_rPcsTest_patternControl_HHD_dataPatternSelect u0.word_0

/*! \brief Base register address of structure AQ_Pcs10G_base_rPcsTest_patternErrorCounter_HHD */
#define AQ_Pcs10G_base_rPcsTest_patternErrorCounter_HHD_baseRegisterAddress 0x002B
/*! \brief MMD address of structure AQ_Pcs10G_base_rPcsTest_patternErrorCounter_HHD */
#define AQ_Pcs10G_base_rPcsTest_patternErrorCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure test_patternErrorCounter in AQ_Pcs10G_base_rPcsTest_patternErrorCounter_HHD */
#define AQ_Pcs10G_base_rPcsTest_patternErrorCounter_HHD_test_patternErrorCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure test_patternErrorCounter in AQ_Pcs10G_base_rPcsTest_patternErrorCounter_HHD */
#define bits_AQ_Pcs10G_base_rPcsTest_patternErrorCounter_HHD_test_patternErrorCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure test_patternErrorCounter in AQ_Pcs10G_base_rPcsTest_patternErrorCounter_HHD */
#define word_AQ_Pcs10G_base_rPcsTest_patternErrorCounter_HHD_test_patternErrorCounter u0.word_0

/*! \brief Base register address of structure AQ_TimesyncPcsCapability_HHD */
#define AQ_TimesyncPcsCapability_HHD_baseRegisterAddress 0x1800
/*! \brief MMD address of structure AQ_TimesyncPcsCapability_HHD */
#define AQ_TimesyncPcsCapability_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure timesyncTransmitPathDataDelay in AQ_TimesyncPcsCapability_HHD */
#define AQ_TimesyncPcsCapability_HHD_timesyncTransmitPathDataDelay 0
/*! \brief Preprocessor variable to relate field to bit position in structure timesyncTransmitPathDataDelay in AQ_TimesyncPcsCapability_HHD */
#define bits_AQ_TimesyncPcsCapability_HHD_timesyncTransmitPathDataDelay u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure timesyncTransmitPathDataDelay in AQ_TimesyncPcsCapability_HHD */
#define word_AQ_TimesyncPcsCapability_HHD_timesyncTransmitPathDataDelay u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure timesyncReceivePathDataDelay in AQ_TimesyncPcsCapability_HHD */
#define AQ_TimesyncPcsCapability_HHD_timesyncReceivePathDataDelay 0
/*! \brief Preprocessor variable to relate field to bit position in structure timesyncReceivePathDataDelay in AQ_TimesyncPcsCapability_HHD */
#define bits_AQ_TimesyncPcsCapability_HHD_timesyncReceivePathDataDelay u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure timesyncReceivePathDataDelay in AQ_TimesyncPcsCapability_HHD */
#define word_AQ_TimesyncPcsCapability_HHD_timesyncReceivePathDataDelay u0.word_0

/*! \brief Base register address of structure AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define AQ_TimesyncPcsTransmitPathDataDelay_HHD_baseRegisterAddress 0x1801
/*! \brief MMD address of structure AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define AQ_TimesyncPcsTransmitPathDataDelay_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure maximumPcsTransmitPathDataDelayLSW in AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define AQ_TimesyncPcsTransmitPathDataDelay_HHD_maximumPcsTransmitPathDataDelayLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure maximumPcsTransmitPathDataDelayLSW in AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define bits_AQ_TimesyncPcsTransmitPathDataDelay_HHD_maximumPcsTransmitPathDataDelayLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure maximumPcsTransmitPathDataDelayLSW in AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define word_AQ_TimesyncPcsTransmitPathDataDelay_HHD_maximumPcsTransmitPathDataDelayLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure maximumPcsTransmitPathDataDelayMSW in AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define AQ_TimesyncPcsTransmitPathDataDelay_HHD_maximumPcsTransmitPathDataDelayMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure maximumPcsTransmitPathDataDelayMSW in AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define bits_AQ_TimesyncPcsTransmitPathDataDelay_HHD_maximumPcsTransmitPathDataDelayMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure maximumPcsTransmitPathDataDelayMSW in AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define word_AQ_TimesyncPcsTransmitPathDataDelay_HHD_maximumPcsTransmitPathDataDelayMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure minimumPcsTransmitPathDataDelayLSW in AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define AQ_TimesyncPcsTransmitPathDataDelay_HHD_minimumPcsTransmitPathDataDelayLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure minimumPcsTransmitPathDataDelayLSW in AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define bits_AQ_TimesyncPcsTransmitPathDataDelay_HHD_minimumPcsTransmitPathDataDelayLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure minimumPcsTransmitPathDataDelayLSW in AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define word_AQ_TimesyncPcsTransmitPathDataDelay_HHD_minimumPcsTransmitPathDataDelayLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure minimumPcsTransmitPathDataDelayMSW in AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define AQ_TimesyncPcsTransmitPathDataDelay_HHD_minimumPcsTransmitPathDataDelayMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure minimumPcsTransmitPathDataDelayMSW in AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define bits_AQ_TimesyncPcsTransmitPathDataDelay_HHD_minimumPcsTransmitPathDataDelayMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure minimumPcsTransmitPathDataDelayMSW in AQ_TimesyncPcsTransmitPathDataDelay_HHD */
#define word_AQ_TimesyncPcsTransmitPathDataDelay_HHD_minimumPcsTransmitPathDataDelayMSW u3.word_3

/*! \brief Base register address of structure AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define AQ_TimesyncPcsReceivePathDataDelay_HHD_baseRegisterAddress 0x1805
/*! \brief MMD address of structure AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define AQ_TimesyncPcsReceivePathDataDelay_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure maximumPcsReceivePathDataDelayLSW in AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define AQ_TimesyncPcsReceivePathDataDelay_HHD_maximumPcsReceivePathDataDelayLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure maximumPcsReceivePathDataDelayLSW in AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define bits_AQ_TimesyncPcsReceivePathDataDelay_HHD_maximumPcsReceivePathDataDelayLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure maximumPcsReceivePathDataDelayLSW in AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define word_AQ_TimesyncPcsReceivePathDataDelay_HHD_maximumPcsReceivePathDataDelayLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure maximumPcsReceivePathDataDelayMSW in AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define AQ_TimesyncPcsReceivePathDataDelay_HHD_maximumPcsReceivePathDataDelayMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure maximumPcsReceivePathDataDelayMSW in AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define bits_AQ_TimesyncPcsReceivePathDataDelay_HHD_maximumPcsReceivePathDataDelayMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure maximumPcsReceivePathDataDelayMSW in AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define word_AQ_TimesyncPcsReceivePathDataDelay_HHD_maximumPcsReceivePathDataDelayMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure minimumPcsReceivePathDataDelayLSW in AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define AQ_TimesyncPcsReceivePathDataDelay_HHD_minimumPcsReceivePathDataDelayLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure minimumPcsReceivePathDataDelayLSW in AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define bits_AQ_TimesyncPcsReceivePathDataDelay_HHD_minimumPcsReceivePathDataDelayLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure minimumPcsReceivePathDataDelayLSW in AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define word_AQ_TimesyncPcsReceivePathDataDelay_HHD_minimumPcsReceivePathDataDelayLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure minimumPcsReceivePathDataDelayMSW in AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define AQ_TimesyncPcsReceivePathDataDelay_HHD_minimumPcsReceivePathDataDelayMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure minimumPcsReceivePathDataDelayMSW in AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define bits_AQ_TimesyncPcsReceivePathDataDelay_HHD_minimumPcsReceivePathDataDelayMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure minimumPcsReceivePathDataDelayMSW in AQ_TimesyncPcsReceivePathDataDelay_HHD */
#define word_AQ_TimesyncPcsReceivePathDataDelay_HHD_minimumPcsReceivePathDataDelayMSW u3.word_3

/*! \brief Base register address of structure AQ_PcsTransmitVendorProvisioning_HHD */
#define AQ_PcsTransmitVendorProvisioning_HHD_baseRegisterAddress 0xC400
/*! \brief MMD address of structure AQ_PcsTransmitVendorProvisioning_HHD */
#define AQ_PcsTransmitVendorProvisioning_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsTxAuxilliaryBitValue in AQ_PcsTransmitVendorProvisioning_HHD */
#define AQ_PcsTransmitVendorProvisioning_HHD_pcsTxAuxilliaryBitValue 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTxAuxilliaryBitValue in AQ_PcsTransmitVendorProvisioning_HHD */
#define bits_AQ_PcsTransmitVendorProvisioning_HHD_pcsTxAuxilliaryBitValue u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTxAuxilliaryBitValue in AQ_PcsTransmitVendorProvisioning_HHD */
#define word_AQ_PcsTransmitVendorProvisioning_HHD_pcsTxAuxilliaryBitValue u0.word_0

/*! \brief Base register address of structure AQ_PcsTransmitReservedVendorProvisioning_HHD */
#define AQ_PcsTransmitReservedVendorProvisioning_HHD_baseRegisterAddress 0xC410
/*! \brief MMD address of structure AQ_PcsTransmitReservedVendorProvisioning_HHD */
#define AQ_PcsTransmitReservedVendorProvisioning_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reservedTransmitProvisioning_1 in AQ_PcsTransmitReservedVendorProvisioning_HHD */
#define AQ_PcsTransmitReservedVendorProvisioning_HHD_reservedTransmitProvisioning_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedTransmitProvisioning_1 in AQ_PcsTransmitReservedVendorProvisioning_HHD */
#define bits_AQ_PcsTransmitReservedVendorProvisioning_HHD_reservedTransmitProvisioning_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedTransmitProvisioning_1 in AQ_PcsTransmitReservedVendorProvisioning_HHD */
#define word_AQ_PcsTransmitReservedVendorProvisioning_HHD_reservedTransmitProvisioning_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsIEEE_LoopbackPassthroughDisable in AQ_PcsTransmitReservedVendorProvisioning_HHD */
#define AQ_PcsTransmitReservedVendorProvisioning_HHD_pcsIEEE_LoopbackPassthroughDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsIEEE_LoopbackPassthroughDisable in AQ_PcsTransmitReservedVendorProvisioning_HHD */
#define bits_AQ_PcsTransmitReservedVendorProvisioning_HHD_pcsIEEE_LoopbackPassthroughDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsIEEE_LoopbackPassthroughDisable in AQ_PcsTransmitReservedVendorProvisioning_HHD */
#define word_AQ_PcsTransmitReservedVendorProvisioning_HHD_pcsIEEE_LoopbackPassthroughDisable u0.word_0

/*! \brief Base register address of structure AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define AQ_PcsTransmitXfiVendorProvisioning_HHD_baseRegisterAddress 0xC455
/*! \brief MMD address of structure AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define AQ_PcsTransmitXfiVendorProvisioning_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedAWord_0 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedAWord_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedAWord_0 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedAWord_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedAWord_0 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedAWord_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedAWord_1 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedAWord_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedAWord_1 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedAWord_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedAWord_1 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedAWord_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedAWord_2 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedAWord_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedAWord_2 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedAWord_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedAWord_2 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedAWord_2 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedAWord_3 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedAWord_3 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedAWord_3 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedAWord_3 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedAWord_3 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedAWord_3 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedBWord_0 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedBWord_0 4
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedBWord_0 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedBWord_0 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedBWord_0 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedBWord_0 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedBWord_1 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedBWord_1 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedBWord_1 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedBWord_1 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedBWord_1 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedBWord_1 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedBWord_2 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedBWord_2 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedBWord_2 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedBWord_2 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedBWord_2 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedBWord_2 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedBWord_3 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedBWord_3 7
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedBWord_3 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedBWord_3 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedBWord_3 in AQ_PcsTransmitXfiVendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfiVendorProvisioning_HHD_xfiTestPatternSeedBWord_3 u7.word_7

/*! \brief Base register address of structure AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi0VendorProvisioning_HHD_baseRegisterAddress 0xC460
/*! \brief MMD address of structure AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi0VendorProvisioning_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi0PcsScramblerDisable in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0PcsScramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0PcsScramblerDisable in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0PcsScramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi0PcsScramblerDisable in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0PcsScramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestSqaureWaveTestDuration in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestSqaureWaveTestDuration 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestSqaureWaveTestDuration in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestSqaureWaveTestDuration u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestSqaureWaveTestDuration in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestSqaureWaveTestDuration u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestDataSelect in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestDataSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestDataSelect in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestDataSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestDataSelect in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestDataSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestModeSelect in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestModeSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestModeSelect in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestModeSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestModeSelect in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestModeSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPrbs_9Enable in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestPrbs_9Enable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPrbs_9Enable in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestPrbs_9Enable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPrbs_9Enable in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestPrbs_9Enable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPrbs_31Enable in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestPrbs_31Enable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPrbs_31Enable in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestPrbs_31Enable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPrbs_31Enable in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestPrbs_31Enable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPatternEnable in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestPatternEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPatternEnable in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestPatternEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPatternEnable in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0TestPatternEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0LocalFaultInject in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0LocalFaultInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0LocalFaultInject in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0LocalFaultInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0LocalFaultInject in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0LocalFaultInject u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0InjectSingleError in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0InjectSingleError 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0InjectSingleError in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0InjectSingleError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0InjectSingleError in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0InjectSingleError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0PcsHighBerInject in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0PcsHighBerInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0PcsHighBerInject in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0PcsHighBerInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0PcsHighBerInject in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0PcsHighBerInject u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0PcsLossOfLockInject in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0PcsLossOfLockInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0PcsLossOfLockInject in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0PcsLossOfLockInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0PcsLossOfLockInject in AQ_PcsTransmitXfi0VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_HHD_xfi0PcsLossOfLockInject u1.word_1

/*! \brief Base register address of structure AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi1VendorProvisioning_HHD_baseRegisterAddress 0xC470
/*! \brief MMD address of structure AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi1VendorProvisioning_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi1PcsScramblerDisable in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1PcsScramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1PcsScramblerDisable in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1PcsScramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi1PcsScramblerDisable in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1PcsScramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestSqaureWaveTestDuration in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestSqaureWaveTestDuration 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestSqaureWaveTestDuration in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestSqaureWaveTestDuration u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestSqaureWaveTestDuration in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestSqaureWaveTestDuration u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestDataSelect in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestDataSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestDataSelect in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestDataSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestDataSelect in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestDataSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestModeSelect in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestModeSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestModeSelect in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestModeSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestModeSelect in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestModeSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestPrbs_9Enable in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestPrbs_9Enable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestPrbs_9Enable in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestPrbs_9Enable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestPrbs_9Enable in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestPrbs_9Enable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestPrbs_31Enable in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestPrbs_31Enable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestPrbs_31Enable in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestPrbs_31Enable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestPrbs_31Enable in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestPrbs_31Enable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestPatternEnable in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestPatternEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestPatternEnable in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestPatternEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestPatternEnable in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1TestPatternEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1LocalFaultInject in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1LocalFaultInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1LocalFaultInject in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1LocalFaultInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1LocalFaultInject in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1LocalFaultInject u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1InjectSingleError in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1InjectSingleError 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1InjectSingleError in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1InjectSingleError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1InjectSingleError in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1InjectSingleError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1PcsHighBerInject in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1PcsHighBerInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1PcsHighBerInject in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1PcsHighBerInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1PcsHighBerInject in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1PcsHighBerInject u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1PcsLossOfLockInject in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1PcsLossOfLockInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1PcsLossOfLockInject in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1PcsLossOfLockInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1PcsLossOfLockInject in AQ_PcsTransmitXfi1VendorProvisioning_HHD */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_HHD_xfi1PcsLossOfLockInject u1.word_1

/*! \brief Base register address of structure AQ_PcsUsx0MemoryControlRegister_HHD */
#define AQ_PcsUsx0MemoryControlRegister_HHD_baseRegisterAddress 0xC4C0
/*! \brief MMD address of structure AQ_PcsUsx0MemoryControlRegister_HHD */
#define AQ_PcsUsx0MemoryControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0MemoryPowerDown in AQ_PcsUsx0MemoryControlRegister_HHD */
#define AQ_PcsUsx0MemoryControlRegister_HHD_usx0MemoryPowerDown 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MemoryPowerDown in AQ_PcsUsx0MemoryControlRegister_HHD */
#define bits_AQ_PcsUsx0MemoryControlRegister_HHD_usx0MemoryPowerDown u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0MemoryPowerDown in AQ_PcsUsx0MemoryControlRegister_HHD */
#define word_AQ_PcsUsx0MemoryControlRegister_HHD_usx0MemoryPowerDown u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0MemoryRm in AQ_PcsUsx0MemoryControlRegister_HHD */
#define AQ_PcsUsx0MemoryControlRegister_HHD_usx0MemoryRm 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MemoryRm in AQ_PcsUsx0MemoryControlRegister_HHD */
#define bits_AQ_PcsUsx0MemoryControlRegister_HHD_usx0MemoryRm u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0MemoryRm in AQ_PcsUsx0MemoryControlRegister_HHD */
#define word_AQ_PcsUsx0MemoryControlRegister_HHD_usx0MemoryRm u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0ControlRegister_HHD */
#define AQ_PcsUsx0ControlRegister_HHD_baseRegisterAddress 0xC4C1
/*! \brief MMD address of structure AQ_PcsUsx0ControlRegister_HHD */
#define AQ_PcsUsx0ControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0ClockEnable in AQ_PcsUsx0ControlRegister_HHD */
#define AQ_PcsUsx0ControlRegister_HHD_usx0ClockEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0ClockEnable in AQ_PcsUsx0ControlRegister_HHD */
#define bits_AQ_PcsUsx0ControlRegister_HHD_usx0ClockEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0ClockEnable in AQ_PcsUsx0ControlRegister_HHD */
#define word_AQ_PcsUsx0ControlRegister_HHD_usx0ClockEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0Bypass in AQ_PcsUsx0ControlRegister_HHD */
#define AQ_PcsUsx0ControlRegister_HHD_usx0Bypass 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0Bypass in AQ_PcsUsx0ControlRegister_HHD */
#define bits_AQ_PcsUsx0ControlRegister_HHD_usx0Bypass u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0Bypass in AQ_PcsUsx0ControlRegister_HHD */
#define word_AQ_PcsUsx0ControlRegister_HHD_usx0Bypass u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkFifoMode in AQ_PcsUsx0ControlRegister_HHD */
#define AQ_PcsUsx0ControlRegister_HHD_usx0LinkFifoMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkFifoMode in AQ_PcsUsx0ControlRegister_HHD */
#define bits_AQ_PcsUsx0ControlRegister_HHD_usx0LinkFifoMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkFifoMode in AQ_PcsUsx0ControlRegister_HHD */
#define word_AQ_PcsUsx0ControlRegister_HHD_usx0LinkFifoMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0ReplicationMode in AQ_PcsUsx0ControlRegister_HHD */
#define AQ_PcsUsx0ControlRegister_HHD_usx0ReplicationMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0ReplicationMode in AQ_PcsUsx0ControlRegister_HHD */
#define bits_AQ_PcsUsx0ControlRegister_HHD_usx0ReplicationMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0ReplicationMode in AQ_PcsUsx0ControlRegister_HHD */
#define word_AQ_PcsUsx0ControlRegister_HHD_usx0ReplicationMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0PcsReset in AQ_PcsUsx0ControlRegister_HHD */
#define AQ_PcsUsx0ControlRegister_HHD_usx0PcsReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0PcsReset in AQ_PcsUsx0ControlRegister_HHD */
#define bits_AQ_PcsUsx0ControlRegister_HHD_usx0PcsReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0PcsReset in AQ_PcsUsx0ControlRegister_HHD */
#define word_AQ_PcsUsx0ControlRegister_HHD_usx0PcsReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0PcsLowPower in AQ_PcsUsx0ControlRegister_HHD */
#define AQ_PcsUsx0ControlRegister_HHD_usx0PcsLowPower 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0PcsLowPower in AQ_PcsUsx0ControlRegister_HHD */
#define bits_AQ_PcsUsx0ControlRegister_HHD_usx0PcsLowPower u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0PcsLowPower in AQ_PcsUsx0ControlRegister_HHD */
#define word_AQ_PcsUsx0ControlRegister_HHD_usx0PcsLowPower u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0ParityCheckSense in AQ_PcsUsx0ControlRegister_HHD */
#define AQ_PcsUsx0ControlRegister_HHD_usx0ParityCheckSense 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0ParityCheckSense in AQ_PcsUsx0ControlRegister_HHD */
#define bits_AQ_PcsUsx0ControlRegister_HHD_usx0ParityCheckSense u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0ParityCheckSense in AQ_PcsUsx0ControlRegister_HHD */
#define word_AQ_PcsUsx0ControlRegister_HHD_usx0ParityCheckSense u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0SpeedMode in AQ_PcsUsx0ControlRegister_HHD */
#define AQ_PcsUsx0ControlRegister_HHD_usx0SpeedMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0SpeedMode in AQ_PcsUsx0ControlRegister_HHD */
#define bits_AQ_PcsUsx0ControlRegister_HHD_usx0SpeedMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0SpeedMode in AQ_PcsUsx0ControlRegister_HHD */
#define word_AQ_PcsUsx0ControlRegister_HHD_usx0SpeedMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0AqrateMode in AQ_PcsUsx0ControlRegister_HHD */
#define AQ_PcsUsx0ControlRegister_HHD_usx0AqrateMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0AqrateMode in AQ_PcsUsx0ControlRegister_HHD */
#define bits_AQ_PcsUsx0ControlRegister_HHD_usx0AqrateMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0AqrateMode in AQ_PcsUsx0ControlRegister_HHD */
#define word_AQ_PcsUsx0ControlRegister_HHD_usx0AqrateMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0XgsRklMode in AQ_PcsUsx0ControlRegister_HHD */
#define AQ_PcsUsx0ControlRegister_HHD_usx0XgsRklMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0XgsRklMode in AQ_PcsUsx0ControlRegister_HHD */
#define bits_AQ_PcsUsx0ControlRegister_HHD_usx0XgsRklMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0XgsRklMode in AQ_PcsUsx0ControlRegister_HHD */
#define word_AQ_PcsUsx0ControlRegister_HHD_usx0XgsRklMode u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0LocalFaultControlRegister_HHD */
#define AQ_PcsUsx0LocalFaultControlRegister_HHD_baseRegisterAddress 0xC4C2
/*! \brief MMD address of structure AQ_PcsUsx0LocalFaultControlRegister_HHD */
#define AQ_PcsUsx0LocalFaultControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0InjectTxLocalFault in AQ_PcsUsx0LocalFaultControlRegister_HHD */
#define AQ_PcsUsx0LocalFaultControlRegister_HHD_usx0InjectTxLocalFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0InjectTxLocalFault in AQ_PcsUsx0LocalFaultControlRegister_HHD */
#define bits_AQ_PcsUsx0LocalFaultControlRegister_HHD_usx0InjectTxLocalFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0InjectTxLocalFault in AQ_PcsUsx0LocalFaultControlRegister_HHD */
#define word_AQ_PcsUsx0LocalFaultControlRegister_HHD_usx0InjectTxLocalFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LocalFaultCode in AQ_PcsUsx0LocalFaultControlRegister_HHD */
#define AQ_PcsUsx0LocalFaultControlRegister_HHD_usx0LocalFaultCode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LocalFaultCode in AQ_PcsUsx0LocalFaultControlRegister_HHD */
#define bits_AQ_PcsUsx0LocalFaultControlRegister_HHD_usx0LocalFaultCode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LocalFaultCode in AQ_PcsUsx0LocalFaultControlRegister_HHD */
#define word_AQ_PcsUsx0LocalFaultControlRegister_HHD_usx0LocalFaultCode u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0MacLocalFaultControlRegister_HHD */
#define AQ_PcsUsx0MacLocalFaultControlRegister_HHD_baseRegisterAddress 0xC4C3
/*! \brief MMD address of structure AQ_PcsUsx0MacLocalFaultControlRegister_HHD */
#define AQ_PcsUsx0MacLocalFaultControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0UserDefineCode in AQ_PcsUsx0MacLocalFaultControlRegister_HHD */
#define AQ_PcsUsx0MacLocalFaultControlRegister_HHD_usx0UserDefineCode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0UserDefineCode in AQ_PcsUsx0MacLocalFaultControlRegister_HHD */
#define bits_AQ_PcsUsx0MacLocalFaultControlRegister_HHD_usx0UserDefineCode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0UserDefineCode in AQ_PcsUsx0MacLocalFaultControlRegister_HHD */
#define word_AQ_PcsUsx0MacLocalFaultControlRegister_HHD_usx0UserDefineCode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0InjectLocalFaultSignal in AQ_PcsUsx0MacLocalFaultControlRegister_HHD */
#define AQ_PcsUsx0MacLocalFaultControlRegister_HHD_usx0InjectLocalFaultSignal 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0InjectLocalFaultSignal in AQ_PcsUsx0MacLocalFaultControlRegister_HHD */
#define bits_AQ_PcsUsx0MacLocalFaultControlRegister_HHD_usx0InjectLocalFaultSignal u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0InjectLocalFaultSignal in AQ_PcsUsx0MacLocalFaultControlRegister_HHD */
#define word_AQ_PcsUsx0MacLocalFaultControlRegister_HHD_usx0InjectLocalFaultSignal u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0NumberOfIdleCoulmn in AQ_PcsUsx0MacLocalFaultControlRegister_HHD */
#define AQ_PcsUsx0MacLocalFaultControlRegister_HHD_usx0NumberOfIdleCoulmn 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0NumberOfIdleCoulmn in AQ_PcsUsx0MacLocalFaultControlRegister_HHD */
#define bits_AQ_PcsUsx0MacLocalFaultControlRegister_HHD_usx0NumberOfIdleCoulmn u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0NumberOfIdleCoulmn in AQ_PcsUsx0MacLocalFaultControlRegister_HHD */
#define word_AQ_PcsUsx0MacLocalFaultControlRegister_HHD_usx0NumberOfIdleCoulmn u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0Auto_negControlRegister_HHD */
#define AQ_PcsUsx0Auto_negControlRegister_HHD_baseRegisterAddress 0xC4C4
/*! \brief MMD address of structure AQ_PcsUsx0Auto_negControlRegister_HHD */
#define AQ_PcsUsx0Auto_negControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0RestartAuto_negotiation in AQ_PcsUsx0Auto_negControlRegister_HHD */
#define AQ_PcsUsx0Auto_negControlRegister_HHD_usx0RestartAuto_negotiation 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RestartAuto_negotiation in AQ_PcsUsx0Auto_negControlRegister_HHD */
#define bits_AQ_PcsUsx0Auto_negControlRegister_HHD_usx0RestartAuto_negotiation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RestartAuto_negotiation in AQ_PcsUsx0Auto_negControlRegister_HHD */
#define word_AQ_PcsUsx0Auto_negControlRegister_HHD_usx0RestartAuto_negotiation u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0Auto_negEnable in AQ_PcsUsx0Auto_negControlRegister_HHD */
#define AQ_PcsUsx0Auto_negControlRegister_HHD_usx0Auto_negEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0Auto_negEnable in AQ_PcsUsx0Auto_negControlRegister_HHD */
#define bits_AQ_PcsUsx0Auto_negControlRegister_HHD_usx0Auto_negEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0Auto_negEnable in AQ_PcsUsx0Auto_negControlRegister_HHD */
#define word_AQ_PcsUsx0Auto_negControlRegister_HHD_usx0Auto_negEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0AutoNegMessageCode in AQ_PcsUsx0Auto_negControlRegister_HHD */
#define AQ_PcsUsx0Auto_negControlRegister_HHD_usx0AutoNegMessageCode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0AutoNegMessageCode in AQ_PcsUsx0Auto_negControlRegister_HHD */
#define bits_AQ_PcsUsx0Auto_negControlRegister_HHD_usx0AutoNegMessageCode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0AutoNegMessageCode in AQ_PcsUsx0Auto_negControlRegister_HHD */
#define word_AQ_PcsUsx0Auto_negControlRegister_HHD_usx0AutoNegMessageCode u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0PtpControlRegister_HHD */
#define AQ_PcsUsx0PtpControlRegister_HHD_baseRegisterAddress 0xC4C5
/*! \brief MMD address of structure AQ_PcsUsx0PtpControlRegister_HHD */
#define AQ_PcsUsx0PtpControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0TxRsvdControl in AQ_PcsUsx0PtpControlRegister_HHD */
#define AQ_PcsUsx0PtpControlRegister_HHD_usx0TxRsvdControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0TxRsvdControl in AQ_PcsUsx0PtpControlRegister_HHD */
#define bits_AQ_PcsUsx0PtpControlRegister_HHD_usx0TxRsvdControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0TxRsvdControl in AQ_PcsUsx0PtpControlRegister_HHD */
#define word_AQ_PcsUsx0PtpControlRegister_HHD_usx0TxRsvdControl u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0HeaderCrcGen in AQ_PcsUsx0PtpControlRegister_HHD */
#define AQ_PcsUsx0PtpControlRegister_HHD_usx0HeaderCrcGen 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0HeaderCrcGen in AQ_PcsUsx0PtpControlRegister_HHD */
#define bits_AQ_PcsUsx0PtpControlRegister_HHD_usx0HeaderCrcGen u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0HeaderCrcGen in AQ_PcsUsx0PtpControlRegister_HHD */
#define word_AQ_PcsUsx0PtpControlRegister_HHD_usx0HeaderCrcGen u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0EnablePtpTimestamp in AQ_PcsUsx0PtpControlRegister_HHD */
#define AQ_PcsUsx0PtpControlRegister_HHD_usx0EnablePtpTimestamp 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0EnablePtpTimestamp in AQ_PcsUsx0PtpControlRegister_HHD */
#define bits_AQ_PcsUsx0PtpControlRegister_HHD_usx0EnablePtpTimestamp u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0EnablePtpTimestamp in AQ_PcsUsx0PtpControlRegister_HHD */
#define word_AQ_PcsUsx0PtpControlRegister_HHD_usx0EnablePtpTimestamp u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0EnablePacketInformationMessage in AQ_PcsUsx0PtpControlRegister_HHD */
#define AQ_PcsUsx0PtpControlRegister_HHD_usx0EnablePacketInformationMessage 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0EnablePacketInformationMessage in AQ_PcsUsx0PtpControlRegister_HHD */
#define bits_AQ_PcsUsx0PtpControlRegister_HHD_usx0EnablePacketInformationMessage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0EnablePacketInformationMessage in AQ_PcsUsx0PtpControlRegister_HHD */
#define word_AQ_PcsUsx0PtpControlRegister_HHD_usx0EnablePacketInformationMessage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0GmiiToXgmiiConversionControl in AQ_PcsUsx0PtpControlRegister_HHD */
#define AQ_PcsUsx0PtpControlRegister_HHD_usx0GmiiToXgmiiConversionControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0GmiiToXgmiiConversionControl in AQ_PcsUsx0PtpControlRegister_HHD */
#define bits_AQ_PcsUsx0PtpControlRegister_HHD_usx0GmiiToXgmiiConversionControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0GmiiToXgmiiConversionControl in AQ_PcsUsx0PtpControlRegister_HHD */
#define word_AQ_PcsUsx0PtpControlRegister_HHD_usx0GmiiToXgmiiConversionControl u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0PktInfoMessageRegister_0_HHD */
#define AQ_PcsUsx0PktInfoMessageRegister_0_HHD_baseRegisterAddress 0xC4C6
/*! \brief MMD address of structure AQ_PcsUsx0PktInfoMessageRegister_0_HHD */
#define AQ_PcsUsx0PktInfoMessageRegister_0_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0PacketInfoMessage_15_0 in AQ_PcsUsx0PktInfoMessageRegister_0_HHD */
#define AQ_PcsUsx0PktInfoMessageRegister_0_HHD_usx0PacketInfoMessage_15_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0PacketInfoMessage_15_0 in AQ_PcsUsx0PktInfoMessageRegister_0_HHD */
#define bits_AQ_PcsUsx0PktInfoMessageRegister_0_HHD_usx0PacketInfoMessage_15_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0PacketInfoMessage_15_0 in AQ_PcsUsx0PktInfoMessageRegister_0_HHD */
#define word_AQ_PcsUsx0PktInfoMessageRegister_0_HHD_usx0PacketInfoMessage_15_0 u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0PktInfoMessageRegister_1_HHD */
#define AQ_PcsUsx0PktInfoMessageRegister_1_HHD_baseRegisterAddress 0xC4C7
/*! \brief MMD address of structure AQ_PcsUsx0PktInfoMessageRegister_1_HHD */
#define AQ_PcsUsx0PktInfoMessageRegister_1_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0PacketInfoMessage_31_16 in AQ_PcsUsx0PktInfoMessageRegister_1_HHD */
#define AQ_PcsUsx0PktInfoMessageRegister_1_HHD_usx0PacketInfoMessage_31_16 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0PacketInfoMessage_31_16 in AQ_PcsUsx0PktInfoMessageRegister_1_HHD */
#define bits_AQ_PcsUsx0PktInfoMessageRegister_1_HHD_usx0PacketInfoMessage_31_16 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0PacketInfoMessage_31_16 in AQ_PcsUsx0PktInfoMessageRegister_1_HHD */
#define word_AQ_PcsUsx0PktInfoMessageRegister_1_HHD_usx0PacketInfoMessage_31_16 u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0PktInfoMessageRegister_2_HHD */
#define AQ_PcsUsx0PktInfoMessageRegister_2_HHD_baseRegisterAddress 0xC4C8
/*! \brief MMD address of structure AQ_PcsUsx0PktInfoMessageRegister_2_HHD */
#define AQ_PcsUsx0PktInfoMessageRegister_2_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0PacketInfoMessage_47_32 in AQ_PcsUsx0PktInfoMessageRegister_2_HHD */
#define AQ_PcsUsx0PktInfoMessageRegister_2_HHD_usx0PacketInfoMessage_47_32 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0PacketInfoMessage_47_32 in AQ_PcsUsx0PktInfoMessageRegister_2_HHD */
#define bits_AQ_PcsUsx0PktInfoMessageRegister_2_HHD_usx0PacketInfoMessage_47_32 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0PacketInfoMessage_47_32 in AQ_PcsUsx0PktInfoMessageRegister_2_HHD */
#define word_AQ_PcsUsx0PktInfoMessageRegister_2_HHD_usx0PacketInfoMessage_47_32 u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0LinkFillDataRegister_0_HHD */
#define AQ_PcsUsx0LinkFillDataRegister_0_HHD_baseRegisterAddress 0xC4C9
/*! \brief MMD address of structure AQ_PcsUsx0LinkFillDataRegister_0_HHD */
#define AQ_PcsUsx0LinkFillDataRegister_0_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0XgmiiLinkFillWord in AQ_PcsUsx0LinkFillDataRegister_0_HHD */
#define AQ_PcsUsx0LinkFillDataRegister_0_HHD_usx0XgmiiLinkFillWord 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0XgmiiLinkFillWord in AQ_PcsUsx0LinkFillDataRegister_0_HHD */
#define bits_AQ_PcsUsx0LinkFillDataRegister_0_HHD_usx0XgmiiLinkFillWord u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0XgmiiLinkFillWord in AQ_PcsUsx0LinkFillDataRegister_0_HHD */
#define word_AQ_PcsUsx0LinkFillDataRegister_0_HHD_usx0XgmiiLinkFillWord u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0LinkFillDataRegister_1_HHD */
#define AQ_PcsUsx0LinkFillDataRegister_1_HHD_baseRegisterAddress 0xC4CA
/*! \brief MMD address of structure AQ_PcsUsx0LinkFillDataRegister_1_HHD */
#define AQ_PcsUsx0LinkFillDataRegister_1_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0XgmiiLinkFillWord in AQ_PcsUsx0LinkFillDataRegister_1_HHD */
#define AQ_PcsUsx0LinkFillDataRegister_1_HHD_usx0XgmiiLinkFillWord 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0XgmiiLinkFillWord in AQ_PcsUsx0LinkFillDataRegister_1_HHD */
#define bits_AQ_PcsUsx0LinkFillDataRegister_1_HHD_usx0XgmiiLinkFillWord u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0XgmiiLinkFillWord in AQ_PcsUsx0LinkFillDataRegister_1_HHD */
#define word_AQ_PcsUsx0LinkFillDataRegister_1_HHD_usx0XgmiiLinkFillWord u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define AQ_PcsUsx0LinkFifoControlRegister_HHD_baseRegisterAddress 0xC4CB
/*! \brief MMD address of structure AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define AQ_PcsUsx0LinkFifoControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0HighThreshold in AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define AQ_PcsUsx0LinkFifoControlRegister_HHD_usx0HighThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0HighThreshold in AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define bits_AQ_PcsUsx0LinkFifoControlRegister_HHD_usx0HighThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0HighThreshold in AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define word_AQ_PcsUsx0LinkFifoControlRegister_HHD_usx0HighThreshold u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LowThreshold in AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define AQ_PcsUsx0LinkFifoControlRegister_HHD_usx0LowThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LowThreshold in AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define bits_AQ_PcsUsx0LinkFifoControlRegister_HHD_usx0LowThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LowThreshold in AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define word_AQ_PcsUsx0LinkFifoControlRegister_HHD_usx0LowThreshold u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkFifoReset in AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define AQ_PcsUsx0LinkFifoControlRegister_HHD_usx0LinkFifoReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkFifoReset in AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define bits_AQ_PcsUsx0LinkFifoControlRegister_HHD_usx0LinkFifoReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkFifoReset in AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define word_AQ_PcsUsx0LinkFifoControlRegister_HHD_usx0LinkFifoReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkFillControl in AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define AQ_PcsUsx0LinkFifoControlRegister_HHD_usx0LinkFillControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkFillControl in AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define bits_AQ_PcsUsx0LinkFifoControlRegister_HHD_usx0LinkFillControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkFillControl in AQ_PcsUsx0LinkFifoControlRegister_HHD */
#define word_AQ_PcsUsx0LinkFifoControlRegister_HHD_usx0LinkFillControl u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0TxFifoControlRegister_HHD */
#define AQ_PcsUsx0TxFifoControlRegister_HHD_baseRegisterAddress 0xC4CC
/*! \brief MMD address of structure AQ_PcsUsx0TxFifoControlRegister_HHD */
#define AQ_PcsUsx0TxFifoControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0TxFifoReset in AQ_PcsUsx0TxFifoControlRegister_HHD */
#define AQ_PcsUsx0TxFifoControlRegister_HHD_usx0TxFifoReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0TxFifoReset in AQ_PcsUsx0TxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx0TxFifoControlRegister_HHD_usx0TxFifoReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0TxFifoReset in AQ_PcsUsx0TxFifoControlRegister_HHD */
#define word_AQ_PcsUsx0TxFifoControlRegister_HHD_usx0TxFifoReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0TxFifoThreshold in AQ_PcsUsx0TxFifoControlRegister_HHD */
#define AQ_PcsUsx0TxFifoControlRegister_HHD_usx0TxFifoThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0TxFifoThreshold in AQ_PcsUsx0TxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx0TxFifoControlRegister_HHD_usx0TxFifoThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0TxFifoThreshold in AQ_PcsUsx0TxFifoControlRegister_HHD */
#define word_AQ_PcsUsx0TxFifoControlRegister_HHD_usx0TxFifoThreshold u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0TxFifoIfgThreshold in AQ_PcsUsx0TxFifoControlRegister_HHD */
#define AQ_PcsUsx0TxFifoControlRegister_HHD_usx0TxFifoIfgThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0TxFifoIfgThreshold in AQ_PcsUsx0TxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx0TxFifoControlRegister_HHD_usx0TxFifoIfgThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0TxFifoIfgThreshold in AQ_PcsUsx0TxFifoControlRegister_HHD */
#define word_AQ_PcsUsx0TxFifoControlRegister_HHD_usx0TxFifoIfgThreshold u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0TxFifoHiThreshold in AQ_PcsUsx0TxFifoControlRegister_HHD */
#define AQ_PcsUsx0TxFifoControlRegister_HHD_usx0TxFifoHiThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0TxFifoHiThreshold in AQ_PcsUsx0TxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx0TxFifoControlRegister_HHD_usx0TxFifoHiThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0TxFifoHiThreshold in AQ_PcsUsx0TxFifoControlRegister_HHD */
#define word_AQ_PcsUsx0TxFifoControlRegister_HHD_usx0TxFifoHiThreshold u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx0LocalAdvertisementRegister_HHD_baseRegisterAddress 0xC4CD
/*! \brief MMD address of structure AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx0LocalAdvertisementRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0LocalAdvertisementStatus in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LocalAdvertisementStatus in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LocalAdvertisementStatus in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedUsx0LocalAdvertisement_0 in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx0LocalAdvertisementRegister_HHD_reservedUsx0LocalAdvertisement_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedUsx0LocalAdvertisement_0 in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx0LocalAdvertisementRegister_HHD_reservedUsx0LocalAdvertisement_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedUsx0LocalAdvertisement_0 in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx0LocalAdvertisementRegister_HHD_reservedUsx0LocalAdvertisement_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LocalAdvertisementDuplex in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementDuplex 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LocalAdvertisementDuplex in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementDuplex u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LocalAdvertisementDuplex in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementDuplex u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LocalAdvertisementSpeed in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementSpeed 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LocalAdvertisementSpeed in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementSpeed u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LocalAdvertisementSpeed in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementSpeed u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LocalAdvertisementEeeCapability in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementEeeCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LocalAdvertisementEeeCapability in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementEeeCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LocalAdvertisementEeeCapability in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementEeeCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LocalAdvertisementEeeClockStopCapability in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementEeeClockStopCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LocalAdvertisementEeeClockStopCapability in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementEeeClockStopCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LocalAdvertisementEeeClockStopCapability in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementEeeClockStopCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedUsx0LocalAdvertisement_1 in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx0LocalAdvertisementRegister_HHD_reservedUsx0LocalAdvertisement_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedUsx0LocalAdvertisement_1 in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx0LocalAdvertisementRegister_HHD_reservedUsx0LocalAdvertisement_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedUsx0LocalAdvertisement_1 in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx0LocalAdvertisementRegister_HHD_reservedUsx0LocalAdvertisement_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LocalAdvertisementMode in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LocalAdvertisementMode in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LocalAdvertisementMode in AQ_PcsUsx0LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx0LocalAdvertisementRegister_HHD_usx0LocalAdvertisementMode u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1MemoryControlRegister_HHD */
#define AQ_PcsUsx1MemoryControlRegister_HHD_baseRegisterAddress 0xC4E0
/*! \brief MMD address of structure AQ_PcsUsx1MemoryControlRegister_HHD */
#define AQ_PcsUsx1MemoryControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1MemoryPowerDown in AQ_PcsUsx1MemoryControlRegister_HHD */
#define AQ_PcsUsx1MemoryControlRegister_HHD_usx1MemoryPowerDown 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MemoryPowerDown in AQ_PcsUsx1MemoryControlRegister_HHD */
#define bits_AQ_PcsUsx1MemoryControlRegister_HHD_usx1MemoryPowerDown u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1MemoryPowerDown in AQ_PcsUsx1MemoryControlRegister_HHD */
#define word_AQ_PcsUsx1MemoryControlRegister_HHD_usx1MemoryPowerDown u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1MemoryRm in AQ_PcsUsx1MemoryControlRegister_HHD */
#define AQ_PcsUsx1MemoryControlRegister_HHD_usx1MemoryRm 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MemoryRm in AQ_PcsUsx1MemoryControlRegister_HHD */
#define bits_AQ_PcsUsx1MemoryControlRegister_HHD_usx1MemoryRm u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1MemoryRm in AQ_PcsUsx1MemoryControlRegister_HHD */
#define word_AQ_PcsUsx1MemoryControlRegister_HHD_usx1MemoryRm u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1ControlRegister_HHD */
#define AQ_PcsUsx1ControlRegister_HHD_baseRegisterAddress 0xC4E1
/*! \brief MMD address of structure AQ_PcsUsx1ControlRegister_HHD */
#define AQ_PcsUsx1ControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1ClockEnable in AQ_PcsUsx1ControlRegister_HHD */
#define AQ_PcsUsx1ControlRegister_HHD_usx1ClockEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1ClockEnable in AQ_PcsUsx1ControlRegister_HHD */
#define bits_AQ_PcsUsx1ControlRegister_HHD_usx1ClockEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1ClockEnable in AQ_PcsUsx1ControlRegister_HHD */
#define word_AQ_PcsUsx1ControlRegister_HHD_usx1ClockEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1Bypass in AQ_PcsUsx1ControlRegister_HHD */
#define AQ_PcsUsx1ControlRegister_HHD_usx1Bypass 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1Bypass in AQ_PcsUsx1ControlRegister_HHD */
#define bits_AQ_PcsUsx1ControlRegister_HHD_usx1Bypass u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1Bypass in AQ_PcsUsx1ControlRegister_HHD */
#define word_AQ_PcsUsx1ControlRegister_HHD_usx1Bypass u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkFifoMode in AQ_PcsUsx1ControlRegister_HHD */
#define AQ_PcsUsx1ControlRegister_HHD_usx1LinkFifoMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkFifoMode in AQ_PcsUsx1ControlRegister_HHD */
#define bits_AQ_PcsUsx1ControlRegister_HHD_usx1LinkFifoMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkFifoMode in AQ_PcsUsx1ControlRegister_HHD */
#define word_AQ_PcsUsx1ControlRegister_HHD_usx1LinkFifoMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1ReplicationMode in AQ_PcsUsx1ControlRegister_HHD */
#define AQ_PcsUsx1ControlRegister_HHD_usx1ReplicationMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1ReplicationMode in AQ_PcsUsx1ControlRegister_HHD */
#define bits_AQ_PcsUsx1ControlRegister_HHD_usx1ReplicationMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1ReplicationMode in AQ_PcsUsx1ControlRegister_HHD */
#define word_AQ_PcsUsx1ControlRegister_HHD_usx1ReplicationMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1PcsReset in AQ_PcsUsx1ControlRegister_HHD */
#define AQ_PcsUsx1ControlRegister_HHD_usx1PcsReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1PcsReset in AQ_PcsUsx1ControlRegister_HHD */
#define bits_AQ_PcsUsx1ControlRegister_HHD_usx1PcsReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1PcsReset in AQ_PcsUsx1ControlRegister_HHD */
#define word_AQ_PcsUsx1ControlRegister_HHD_usx1PcsReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1PcsLowPower in AQ_PcsUsx1ControlRegister_HHD */
#define AQ_PcsUsx1ControlRegister_HHD_usx1PcsLowPower 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1PcsLowPower in AQ_PcsUsx1ControlRegister_HHD */
#define bits_AQ_PcsUsx1ControlRegister_HHD_usx1PcsLowPower u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1PcsLowPower in AQ_PcsUsx1ControlRegister_HHD */
#define word_AQ_PcsUsx1ControlRegister_HHD_usx1PcsLowPower u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1ParityCheckSense in AQ_PcsUsx1ControlRegister_HHD */
#define AQ_PcsUsx1ControlRegister_HHD_usx1ParityCheckSense 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1ParityCheckSense in AQ_PcsUsx1ControlRegister_HHD */
#define bits_AQ_PcsUsx1ControlRegister_HHD_usx1ParityCheckSense u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1ParityCheckSense in AQ_PcsUsx1ControlRegister_HHD */
#define word_AQ_PcsUsx1ControlRegister_HHD_usx1ParityCheckSense u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1SpeedMode in AQ_PcsUsx1ControlRegister_HHD */
#define AQ_PcsUsx1ControlRegister_HHD_usx1SpeedMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1SpeedMode in AQ_PcsUsx1ControlRegister_HHD */
#define bits_AQ_PcsUsx1ControlRegister_HHD_usx1SpeedMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1SpeedMode in AQ_PcsUsx1ControlRegister_HHD */
#define word_AQ_PcsUsx1ControlRegister_HHD_usx1SpeedMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1AqrateMode in AQ_PcsUsx1ControlRegister_HHD */
#define AQ_PcsUsx1ControlRegister_HHD_usx1AqrateMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1AqrateMode in AQ_PcsUsx1ControlRegister_HHD */
#define bits_AQ_PcsUsx1ControlRegister_HHD_usx1AqrateMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1AqrateMode in AQ_PcsUsx1ControlRegister_HHD */
#define word_AQ_PcsUsx1ControlRegister_HHD_usx1AqrateMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1XgsRklMode in AQ_PcsUsx1ControlRegister_HHD */
#define AQ_PcsUsx1ControlRegister_HHD_usx1XgsRklMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1XgsRklMode in AQ_PcsUsx1ControlRegister_HHD */
#define bits_AQ_PcsUsx1ControlRegister_HHD_usx1XgsRklMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1XgsRklMode in AQ_PcsUsx1ControlRegister_HHD */
#define word_AQ_PcsUsx1ControlRegister_HHD_usx1XgsRklMode u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1LocalFaultControlRegister_HHD */
#define AQ_PcsUsx1LocalFaultControlRegister_HHD_baseRegisterAddress 0xC4E2
/*! \brief MMD address of structure AQ_PcsUsx1LocalFaultControlRegister_HHD */
#define AQ_PcsUsx1LocalFaultControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1InjectTxLocalFault in AQ_PcsUsx1LocalFaultControlRegister_HHD */
#define AQ_PcsUsx1LocalFaultControlRegister_HHD_usx1InjectTxLocalFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1InjectTxLocalFault in AQ_PcsUsx1LocalFaultControlRegister_HHD */
#define bits_AQ_PcsUsx1LocalFaultControlRegister_HHD_usx1InjectTxLocalFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1InjectTxLocalFault in AQ_PcsUsx1LocalFaultControlRegister_HHD */
#define word_AQ_PcsUsx1LocalFaultControlRegister_HHD_usx1InjectTxLocalFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LocalFaultCode in AQ_PcsUsx1LocalFaultControlRegister_HHD */
#define AQ_PcsUsx1LocalFaultControlRegister_HHD_usx1LocalFaultCode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LocalFaultCode in AQ_PcsUsx1LocalFaultControlRegister_HHD */
#define bits_AQ_PcsUsx1LocalFaultControlRegister_HHD_usx1LocalFaultCode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LocalFaultCode in AQ_PcsUsx1LocalFaultControlRegister_HHD */
#define word_AQ_PcsUsx1LocalFaultControlRegister_HHD_usx1LocalFaultCode u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1MacLocalFaultControlRegister_HHD */
#define AQ_PcsUsx1MacLocalFaultControlRegister_HHD_baseRegisterAddress 0xC4E3
/*! \brief MMD address of structure AQ_PcsUsx1MacLocalFaultControlRegister_HHD */
#define AQ_PcsUsx1MacLocalFaultControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1UserDefineCode in AQ_PcsUsx1MacLocalFaultControlRegister_HHD */
#define AQ_PcsUsx1MacLocalFaultControlRegister_HHD_usx1UserDefineCode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1UserDefineCode in AQ_PcsUsx1MacLocalFaultControlRegister_HHD */
#define bits_AQ_PcsUsx1MacLocalFaultControlRegister_HHD_usx1UserDefineCode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1UserDefineCode in AQ_PcsUsx1MacLocalFaultControlRegister_HHD */
#define word_AQ_PcsUsx1MacLocalFaultControlRegister_HHD_usx1UserDefineCode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1InjectLocalFaultSignal in AQ_PcsUsx1MacLocalFaultControlRegister_HHD */
#define AQ_PcsUsx1MacLocalFaultControlRegister_HHD_usx1InjectLocalFaultSignal 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1InjectLocalFaultSignal in AQ_PcsUsx1MacLocalFaultControlRegister_HHD */
#define bits_AQ_PcsUsx1MacLocalFaultControlRegister_HHD_usx1InjectLocalFaultSignal u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1InjectLocalFaultSignal in AQ_PcsUsx1MacLocalFaultControlRegister_HHD */
#define word_AQ_PcsUsx1MacLocalFaultControlRegister_HHD_usx1InjectLocalFaultSignal u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1NumberOfIdleCoulmn in AQ_PcsUsx1MacLocalFaultControlRegister_HHD */
#define AQ_PcsUsx1MacLocalFaultControlRegister_HHD_usx1NumberOfIdleCoulmn 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1NumberOfIdleCoulmn in AQ_PcsUsx1MacLocalFaultControlRegister_HHD */
#define bits_AQ_PcsUsx1MacLocalFaultControlRegister_HHD_usx1NumberOfIdleCoulmn u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1NumberOfIdleCoulmn in AQ_PcsUsx1MacLocalFaultControlRegister_HHD */
#define word_AQ_PcsUsx1MacLocalFaultControlRegister_HHD_usx1NumberOfIdleCoulmn u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1Auto_negControlRegister_HHD */
#define AQ_PcsUsx1Auto_negControlRegister_HHD_baseRegisterAddress 0xC4E4
/*! \brief MMD address of structure AQ_PcsUsx1Auto_negControlRegister_HHD */
#define AQ_PcsUsx1Auto_negControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1RestartAuto_negotiation in AQ_PcsUsx1Auto_negControlRegister_HHD */
#define AQ_PcsUsx1Auto_negControlRegister_HHD_usx1RestartAuto_negotiation 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RestartAuto_negotiation in AQ_PcsUsx1Auto_negControlRegister_HHD */
#define bits_AQ_PcsUsx1Auto_negControlRegister_HHD_usx1RestartAuto_negotiation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1RestartAuto_negotiation in AQ_PcsUsx1Auto_negControlRegister_HHD */
#define word_AQ_PcsUsx1Auto_negControlRegister_HHD_usx1RestartAuto_negotiation u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1Auto_negEnable in AQ_PcsUsx1Auto_negControlRegister_HHD */
#define AQ_PcsUsx1Auto_negControlRegister_HHD_usx1Auto_negEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1Auto_negEnable in AQ_PcsUsx1Auto_negControlRegister_HHD */
#define bits_AQ_PcsUsx1Auto_negControlRegister_HHD_usx1Auto_negEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1Auto_negEnable in AQ_PcsUsx1Auto_negControlRegister_HHD */
#define word_AQ_PcsUsx1Auto_negControlRegister_HHD_usx1Auto_negEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1AutoNegMessageCode in AQ_PcsUsx1Auto_negControlRegister_HHD */
#define AQ_PcsUsx1Auto_negControlRegister_HHD_usx1AutoNegMessageCode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1AutoNegMessageCode in AQ_PcsUsx1Auto_negControlRegister_HHD */
#define bits_AQ_PcsUsx1Auto_negControlRegister_HHD_usx1AutoNegMessageCode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1AutoNegMessageCode in AQ_PcsUsx1Auto_negControlRegister_HHD */
#define word_AQ_PcsUsx1Auto_negControlRegister_HHD_usx1AutoNegMessageCode u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1PtpControlRegister_HHD */
#define AQ_PcsUsx1PtpControlRegister_HHD_baseRegisterAddress 0xC4E5
/*! \brief MMD address of structure AQ_PcsUsx1PtpControlRegister_HHD */
#define AQ_PcsUsx1PtpControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1TxRsvdControl in AQ_PcsUsx1PtpControlRegister_HHD */
#define AQ_PcsUsx1PtpControlRegister_HHD_usx1TxRsvdControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1TxRsvdControl in AQ_PcsUsx1PtpControlRegister_HHD */
#define bits_AQ_PcsUsx1PtpControlRegister_HHD_usx1TxRsvdControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1TxRsvdControl in AQ_PcsUsx1PtpControlRegister_HHD */
#define word_AQ_PcsUsx1PtpControlRegister_HHD_usx1TxRsvdControl u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1HeaderCrcGen in AQ_PcsUsx1PtpControlRegister_HHD */
#define AQ_PcsUsx1PtpControlRegister_HHD_usx1HeaderCrcGen 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1HeaderCrcGen in AQ_PcsUsx1PtpControlRegister_HHD */
#define bits_AQ_PcsUsx1PtpControlRegister_HHD_usx1HeaderCrcGen u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1HeaderCrcGen in AQ_PcsUsx1PtpControlRegister_HHD */
#define word_AQ_PcsUsx1PtpControlRegister_HHD_usx1HeaderCrcGen u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1EnablePtpTimestamp in AQ_PcsUsx1PtpControlRegister_HHD */
#define AQ_PcsUsx1PtpControlRegister_HHD_usx1EnablePtpTimestamp 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1EnablePtpTimestamp in AQ_PcsUsx1PtpControlRegister_HHD */
#define bits_AQ_PcsUsx1PtpControlRegister_HHD_usx1EnablePtpTimestamp u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1EnablePtpTimestamp in AQ_PcsUsx1PtpControlRegister_HHD */
#define word_AQ_PcsUsx1PtpControlRegister_HHD_usx1EnablePtpTimestamp u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1EnablePacketInformationMessage in AQ_PcsUsx1PtpControlRegister_HHD */
#define AQ_PcsUsx1PtpControlRegister_HHD_usx1EnablePacketInformationMessage 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1EnablePacketInformationMessage in AQ_PcsUsx1PtpControlRegister_HHD */
#define bits_AQ_PcsUsx1PtpControlRegister_HHD_usx1EnablePacketInformationMessage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1EnablePacketInformationMessage in AQ_PcsUsx1PtpControlRegister_HHD */
#define word_AQ_PcsUsx1PtpControlRegister_HHD_usx1EnablePacketInformationMessage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1GmiiToXgmiiConversionControl in AQ_PcsUsx1PtpControlRegister_HHD */
#define AQ_PcsUsx1PtpControlRegister_HHD_usx1GmiiToXgmiiConversionControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1GmiiToXgmiiConversionControl in AQ_PcsUsx1PtpControlRegister_HHD */
#define bits_AQ_PcsUsx1PtpControlRegister_HHD_usx1GmiiToXgmiiConversionControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1GmiiToXgmiiConversionControl in AQ_PcsUsx1PtpControlRegister_HHD */
#define word_AQ_PcsUsx1PtpControlRegister_HHD_usx1GmiiToXgmiiConversionControl u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1PktInfoMessageRegister_0_HHD */
#define AQ_PcsUsx1PktInfoMessageRegister_0_HHD_baseRegisterAddress 0xC4E6
/*! \brief MMD address of structure AQ_PcsUsx1PktInfoMessageRegister_0_HHD */
#define AQ_PcsUsx1PktInfoMessageRegister_0_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1PacketInfoMessage_15_0 in AQ_PcsUsx1PktInfoMessageRegister_0_HHD */
#define AQ_PcsUsx1PktInfoMessageRegister_0_HHD_usx1PacketInfoMessage_15_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1PacketInfoMessage_15_0 in AQ_PcsUsx1PktInfoMessageRegister_0_HHD */
#define bits_AQ_PcsUsx1PktInfoMessageRegister_0_HHD_usx1PacketInfoMessage_15_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1PacketInfoMessage_15_0 in AQ_PcsUsx1PktInfoMessageRegister_0_HHD */
#define word_AQ_PcsUsx1PktInfoMessageRegister_0_HHD_usx1PacketInfoMessage_15_0 u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1PktInfoMessageRegister_1_HHD */
#define AQ_PcsUsx1PktInfoMessageRegister_1_HHD_baseRegisterAddress 0xC4E7
/*! \brief MMD address of structure AQ_PcsUsx1PktInfoMessageRegister_1_HHD */
#define AQ_PcsUsx1PktInfoMessageRegister_1_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1PacketInfoMessage_31_16 in AQ_PcsUsx1PktInfoMessageRegister_1_HHD */
#define AQ_PcsUsx1PktInfoMessageRegister_1_HHD_usx1PacketInfoMessage_31_16 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1PacketInfoMessage_31_16 in AQ_PcsUsx1PktInfoMessageRegister_1_HHD */
#define bits_AQ_PcsUsx1PktInfoMessageRegister_1_HHD_usx1PacketInfoMessage_31_16 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1PacketInfoMessage_31_16 in AQ_PcsUsx1PktInfoMessageRegister_1_HHD */
#define word_AQ_PcsUsx1PktInfoMessageRegister_1_HHD_usx1PacketInfoMessage_31_16 u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1PktInfoMessageRegister_2_HHD */
#define AQ_PcsUsx1PktInfoMessageRegister_2_HHD_baseRegisterAddress 0xC4E8
/*! \brief MMD address of structure AQ_PcsUsx1PktInfoMessageRegister_2_HHD */
#define AQ_PcsUsx1PktInfoMessageRegister_2_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1PacketInfoMessage_47_32 in AQ_PcsUsx1PktInfoMessageRegister_2_HHD */
#define AQ_PcsUsx1PktInfoMessageRegister_2_HHD_usx1PacketInfoMessage_47_32 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1PacketInfoMessage_47_32 in AQ_PcsUsx1PktInfoMessageRegister_2_HHD */
#define bits_AQ_PcsUsx1PktInfoMessageRegister_2_HHD_usx1PacketInfoMessage_47_32 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1PacketInfoMessage_47_32 in AQ_PcsUsx1PktInfoMessageRegister_2_HHD */
#define word_AQ_PcsUsx1PktInfoMessageRegister_2_HHD_usx1PacketInfoMessage_47_32 u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1LinkFillDataRegister_0_HHD */
#define AQ_PcsUsx1LinkFillDataRegister_0_HHD_baseRegisterAddress 0xC4E9
/*! \brief MMD address of structure AQ_PcsUsx1LinkFillDataRegister_0_HHD */
#define AQ_PcsUsx1LinkFillDataRegister_0_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1XgmiiLinkFillWord in AQ_PcsUsx1LinkFillDataRegister_0_HHD */
#define AQ_PcsUsx1LinkFillDataRegister_0_HHD_usx1XgmiiLinkFillWord 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1XgmiiLinkFillWord in AQ_PcsUsx1LinkFillDataRegister_0_HHD */
#define bits_AQ_PcsUsx1LinkFillDataRegister_0_HHD_usx1XgmiiLinkFillWord u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1XgmiiLinkFillWord in AQ_PcsUsx1LinkFillDataRegister_0_HHD */
#define word_AQ_PcsUsx1LinkFillDataRegister_0_HHD_usx1XgmiiLinkFillWord u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1LinkFillDataRegister_1_HHD */
#define AQ_PcsUsx1LinkFillDataRegister_1_HHD_baseRegisterAddress 0xC4EA
/*! \brief MMD address of structure AQ_PcsUsx1LinkFillDataRegister_1_HHD */
#define AQ_PcsUsx1LinkFillDataRegister_1_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1XgmiiLinkFillWord in AQ_PcsUsx1LinkFillDataRegister_1_HHD */
#define AQ_PcsUsx1LinkFillDataRegister_1_HHD_usx1XgmiiLinkFillWord 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1XgmiiLinkFillWord in AQ_PcsUsx1LinkFillDataRegister_1_HHD */
#define bits_AQ_PcsUsx1LinkFillDataRegister_1_HHD_usx1XgmiiLinkFillWord u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1XgmiiLinkFillWord in AQ_PcsUsx1LinkFillDataRegister_1_HHD */
#define word_AQ_PcsUsx1LinkFillDataRegister_1_HHD_usx1XgmiiLinkFillWord u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define AQ_PcsUsx1LinkFifoControlRegister_HHD_baseRegisterAddress 0xC4EB
/*! \brief MMD address of structure AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define AQ_PcsUsx1LinkFifoControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1HighThreshold in AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define AQ_PcsUsx1LinkFifoControlRegister_HHD_usx1HighThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1HighThreshold in AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define bits_AQ_PcsUsx1LinkFifoControlRegister_HHD_usx1HighThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1HighThreshold in AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define word_AQ_PcsUsx1LinkFifoControlRegister_HHD_usx1HighThreshold u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LowThreshold in AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define AQ_PcsUsx1LinkFifoControlRegister_HHD_usx1LowThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LowThreshold in AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define bits_AQ_PcsUsx1LinkFifoControlRegister_HHD_usx1LowThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LowThreshold in AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define word_AQ_PcsUsx1LinkFifoControlRegister_HHD_usx1LowThreshold u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkFifoReset in AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define AQ_PcsUsx1LinkFifoControlRegister_HHD_usx1LinkFifoReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkFifoReset in AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define bits_AQ_PcsUsx1LinkFifoControlRegister_HHD_usx1LinkFifoReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkFifoReset in AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define word_AQ_PcsUsx1LinkFifoControlRegister_HHD_usx1LinkFifoReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkFillControl in AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define AQ_PcsUsx1LinkFifoControlRegister_HHD_usx1LinkFillControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkFillControl in AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define bits_AQ_PcsUsx1LinkFifoControlRegister_HHD_usx1LinkFillControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkFillControl in AQ_PcsUsx1LinkFifoControlRegister_HHD */
#define word_AQ_PcsUsx1LinkFifoControlRegister_HHD_usx1LinkFillControl u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1TxFifoControlRegister_HHD */
#define AQ_PcsUsx1TxFifoControlRegister_HHD_baseRegisterAddress 0xC4EC
/*! \brief MMD address of structure AQ_PcsUsx1TxFifoControlRegister_HHD */
#define AQ_PcsUsx1TxFifoControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1TxFifoReset in AQ_PcsUsx1TxFifoControlRegister_HHD */
#define AQ_PcsUsx1TxFifoControlRegister_HHD_usx1TxFifoReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1TxFifoReset in AQ_PcsUsx1TxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx1TxFifoControlRegister_HHD_usx1TxFifoReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1TxFifoReset in AQ_PcsUsx1TxFifoControlRegister_HHD */
#define word_AQ_PcsUsx1TxFifoControlRegister_HHD_usx1TxFifoReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1TxFifoThreshold in AQ_PcsUsx1TxFifoControlRegister_HHD */
#define AQ_PcsUsx1TxFifoControlRegister_HHD_usx1TxFifoThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1TxFifoThreshold in AQ_PcsUsx1TxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx1TxFifoControlRegister_HHD_usx1TxFifoThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1TxFifoThreshold in AQ_PcsUsx1TxFifoControlRegister_HHD */
#define word_AQ_PcsUsx1TxFifoControlRegister_HHD_usx1TxFifoThreshold u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1TxFifoIfgThreshold in AQ_PcsUsx1TxFifoControlRegister_HHD */
#define AQ_PcsUsx1TxFifoControlRegister_HHD_usx1TxFifoIfgThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1TxFifoIfgThreshold in AQ_PcsUsx1TxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx1TxFifoControlRegister_HHD_usx1TxFifoIfgThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1TxFifoIfgThreshold in AQ_PcsUsx1TxFifoControlRegister_HHD */
#define word_AQ_PcsUsx1TxFifoControlRegister_HHD_usx1TxFifoIfgThreshold u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1TxFifoHiThreshold in AQ_PcsUsx1TxFifoControlRegister_HHD */
#define AQ_PcsUsx1TxFifoControlRegister_HHD_usx1TxFifoHiThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1TxFifoHiThreshold in AQ_PcsUsx1TxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx1TxFifoControlRegister_HHD_usx1TxFifoHiThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1TxFifoHiThreshold in AQ_PcsUsx1TxFifoControlRegister_HHD */
#define word_AQ_PcsUsx1TxFifoControlRegister_HHD_usx1TxFifoHiThreshold u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx1LocalAdvertisementRegister_HHD_baseRegisterAddress 0xC4ED
/*! \brief MMD address of structure AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx1LocalAdvertisementRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1LocalAdvertisementStatus in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LocalAdvertisementStatus in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LocalAdvertisementStatus in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedUsx1LocalAdvertisement_0 in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx1LocalAdvertisementRegister_HHD_reservedUsx1LocalAdvertisement_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedUsx1LocalAdvertisement_0 in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx1LocalAdvertisementRegister_HHD_reservedUsx1LocalAdvertisement_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedUsx1LocalAdvertisement_0 in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx1LocalAdvertisementRegister_HHD_reservedUsx1LocalAdvertisement_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LocalAdvertisementDuplex in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementDuplex 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LocalAdvertisementDuplex in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementDuplex u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LocalAdvertisementDuplex in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementDuplex u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LocalAdvertisementSpeed in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementSpeed 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LocalAdvertisementSpeed in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementSpeed u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LocalAdvertisementSpeed in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementSpeed u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LocalAdvertisementEeeCapability in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementEeeCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LocalAdvertisementEeeCapability in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementEeeCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LocalAdvertisementEeeCapability in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementEeeCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LocalAdvertisementEeeClockStopCapability in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementEeeClockStopCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LocalAdvertisementEeeClockStopCapability in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementEeeClockStopCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LocalAdvertisementEeeClockStopCapability in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementEeeClockStopCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedUsx1LocalAdvertisement_1 in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx1LocalAdvertisementRegister_HHD_reservedUsx1LocalAdvertisement_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedUsx1LocalAdvertisement_1 in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx1LocalAdvertisementRegister_HHD_reservedUsx1LocalAdvertisement_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedUsx1LocalAdvertisement_1 in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx1LocalAdvertisementRegister_HHD_reservedUsx1LocalAdvertisement_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LocalAdvertisementMode in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LocalAdvertisementMode in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define bits_AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LocalAdvertisementMode in AQ_PcsUsx1LocalAdvertisementRegister_HHD */
#define word_AQ_PcsUsx1LocalAdvertisementRegister_HHD_usx1LocalAdvertisementMode u0.word_0

/*! \brief Base register address of structure AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define AQ_PcsSerdesMuxSwapTxrxRegister_HHD_baseRegisterAddress 0xC4F0
/*! \brief MMD address of structure AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define AQ_PcsSerdesMuxSwapTxrxRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapTxLane_3 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapTxLane_3 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapTxLane_3 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapTxLane_3 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapTxLane_3 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapTxLane_3 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapTxLane_2 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapTxLane_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapTxLane_2 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapTxLane_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapTxLane_2 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapTxLane_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapTxLane_1 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapTxLane_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapTxLane_1 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapTxLane_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapTxLane_1 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapTxLane_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapTxLane_0 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapTxLane_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapTxLane_0 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapTxLane_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapTxLane_0 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapTxLane_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapRxLane_3 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapRxLane_3 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapRxLane_3 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapRxLane_3 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapRxLane_3 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapRxLane_3 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapRxLane_2 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapRxLane_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapRxLane_2 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapRxLane_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapRxLane_2 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapRxLane_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapRxLane_1 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapRxLane_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapRxLane_1 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapRxLane_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapRxLane_1 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapRxLane_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMuxSwapRxLane_0 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapRxLane_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMuxSwapRxLane_0 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define bits_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapRxLane_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMuxSwapRxLane_0 in AQ_PcsSerdesMuxSwapTxrxRegister_HHD */
#define word_AQ_PcsSerdesMuxSwapTxrxRegister_HHD_serdesMuxSwapRxLane_0 u0.word_0

/*! \brief Base register address of structure AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD */
#define AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD_baseRegisterAddress 0xC820
/*! \brief MMD address of structure AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD */
#define AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD */
#define AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD__10gbase_tGoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD */
#define bits_AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD__10gbase_tGoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD */
#define word_AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD__10gbase_tGoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD */
#define AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD__10gbase_tGoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD */
#define bits_AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD__10gbase_tGoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD */
#define word_AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD__10gbase_tGoodFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD */
#define AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD_baseRegisterAddress 0xC822
/*! \brief MMD address of structure AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD */
#define AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD */
#define AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD__10gbase_tErrorFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD */
#define bits_AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD__10gbase_tErrorFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD */
#define word_AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD__10gbase_tErrorFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD */
#define AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD__10gbase_tErrorFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD */
#define bits_AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD__10gbase_tErrorFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD */
#define word_AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD__10gbase_tErrorFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsTransmitXfi0VendorState_HHD */
#define AQ_PcsTransmitXfi0VendorState_HHD_baseRegisterAddress 0xC860
/*! \brief MMD address of structure AQ_PcsTransmitXfi0VendorState_HHD */
#define AQ_PcsTransmitXfi0VendorState_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi0GoodFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_HHD */
#define AQ_PcsTransmitXfi0VendorState_HHD_xfi0GoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0GoodFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_HHD */
#define bits_AQ_PcsTransmitXfi0VendorState_HHD_xfi0GoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi0GoodFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_HHD */
#define word_AQ_PcsTransmitXfi0VendorState_HHD_xfi0GoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi0GoodFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_HHD */
#define AQ_PcsTransmitXfi0VendorState_HHD_xfi0GoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0GoodFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_HHD */
#define bits_AQ_PcsTransmitXfi0VendorState_HHD_xfi0GoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0GoodFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_HHD */
#define word_AQ_PcsTransmitXfi0VendorState_HHD_xfi0GoodFrameCounterMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BadFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_HHD */
#define AQ_PcsTransmitXfi0VendorState_HHD_xfi0BadFrameCounterLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BadFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_HHD */
#define bits_AQ_PcsTransmitXfi0VendorState_HHD_xfi0BadFrameCounterLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BadFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_HHD */
#define word_AQ_PcsTransmitXfi0VendorState_HHD_xfi0BadFrameCounterLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BadFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_HHD */
#define AQ_PcsTransmitXfi0VendorState_HHD_xfi0BadFrameCounterMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BadFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_HHD */
#define bits_AQ_PcsTransmitXfi0VendorState_HHD_xfi0BadFrameCounterMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BadFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_HHD */
#define word_AQ_PcsTransmitXfi0VendorState_HHD_xfi0BadFrameCounterMSW u3.word_3

/*! \brief Base register address of structure AQ_PcsTransmitXfi1VendorState_HHD */
#define AQ_PcsTransmitXfi1VendorState_HHD_baseRegisterAddress 0xC870
/*! \brief MMD address of structure AQ_PcsTransmitXfi1VendorState_HHD */
#define AQ_PcsTransmitXfi1VendorState_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi1GoodFrameCounterLSW in AQ_PcsTransmitXfi1VendorState_HHD */
#define AQ_PcsTransmitXfi1VendorState_HHD_xfi1GoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1GoodFrameCounterLSW in AQ_PcsTransmitXfi1VendorState_HHD */
#define bits_AQ_PcsTransmitXfi1VendorState_HHD_xfi1GoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi1GoodFrameCounterLSW in AQ_PcsTransmitXfi1VendorState_HHD */
#define word_AQ_PcsTransmitXfi1VendorState_HHD_xfi1GoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi1GoodFrameCounterMSW in AQ_PcsTransmitXfi1VendorState_HHD */
#define AQ_PcsTransmitXfi1VendorState_HHD_xfi1GoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1GoodFrameCounterMSW in AQ_PcsTransmitXfi1VendorState_HHD */
#define bits_AQ_PcsTransmitXfi1VendorState_HHD_xfi1GoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1GoodFrameCounterMSW in AQ_PcsTransmitXfi1VendorState_HHD */
#define word_AQ_PcsTransmitXfi1VendorState_HHD_xfi1GoodFrameCounterMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BadFrameCounterLSW in AQ_PcsTransmitXfi1VendorState_HHD */
#define AQ_PcsTransmitXfi1VendorState_HHD_xfi1BadFrameCounterLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BadFrameCounterLSW in AQ_PcsTransmitXfi1VendorState_HHD */
#define bits_AQ_PcsTransmitXfi1VendorState_HHD_xfi1BadFrameCounterLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BadFrameCounterLSW in AQ_PcsTransmitXfi1VendorState_HHD */
#define word_AQ_PcsTransmitXfi1VendorState_HHD_xfi1BadFrameCounterLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BadFrameCounterMSW in AQ_PcsTransmitXfi1VendorState_HHD */
#define AQ_PcsTransmitXfi1VendorState_HHD_xfi1BadFrameCounterMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BadFrameCounterMSW in AQ_PcsTransmitXfi1VendorState_HHD */
#define bits_AQ_PcsTransmitXfi1VendorState_HHD_xfi1BadFrameCounterMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BadFrameCounterMSW in AQ_PcsTransmitXfi1VendorState_HHD */
#define word_AQ_PcsTransmitXfi1VendorState_HHD_xfi1BadFrameCounterMSW u3.word_3

/*! \brief Base register address of structure AQ_PcsTransmitXgsVendorState_HHD */
#define AQ_PcsTransmitXgsVendorState_HHD_baseRegisterAddress 0xC880
/*! \brief MMD address of structure AQ_PcsTransmitXgsVendorState_HHD */
#define AQ_PcsTransmitXgsVendorState_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_0 in AQ_PcsTransmitXgsVendorState_HHD */
#define AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_0 in AQ_PcsTransmitXgsVendorState_HHD */
#define bits_AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_0 in AQ_PcsTransmitXgsVendorState_HHD */
#define word_AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_1 in AQ_PcsTransmitXgsVendorState_HHD */
#define AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_1 in AQ_PcsTransmitXgsVendorState_HHD */
#define bits_AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_1 in AQ_PcsTransmitXgsVendorState_HHD */
#define word_AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_2 in AQ_PcsTransmitXgsVendorState_HHD */
#define AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_2 in AQ_PcsTransmitXgsVendorState_HHD */
#define bits_AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_2 in AQ_PcsTransmitXgsVendorState_HHD */
#define word_AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_2 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_3 in AQ_PcsTransmitXgsVendorState_HHD */
#define AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_3 3
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_3 in AQ_PcsTransmitXgsVendorState_HHD */
#define bits_AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_3 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_3 in AQ_PcsTransmitXgsVendorState_HHD */
#define word_AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_3 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_4 in AQ_PcsTransmitXgsVendorState_HHD */
#define AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_4 4
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_4 in AQ_PcsTransmitXgsVendorState_HHD */
#define bits_AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_4 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_4 in AQ_PcsTransmitXgsVendorState_HHD */
#define word_AQ_PcsTransmitXgsVendorState_HHD_xgsCollisionEventsCounter_4 u4.word_4

/*! \brief Base register address of structure AQ_PcsUsx0TransmitStatus_HHD */
#define AQ_PcsUsx0TransmitStatus_HHD_baseRegisterAddress 0xC8C0
/*! \brief MMD address of structure AQ_PcsUsx0TransmitStatus_HHD */
#define AQ_PcsUsx0TransmitStatus_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0TxRsvdStatus in AQ_PcsUsx0TransmitStatus_HHD */
#define AQ_PcsUsx0TransmitStatus_HHD_usx0TxRsvdStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0TxRsvdStatus in AQ_PcsUsx0TransmitStatus_HHD */
#define bits_AQ_PcsUsx0TransmitStatus_HHD_usx0TxRsvdStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0TxRsvdStatus in AQ_PcsUsx0TransmitStatus_HHD */
#define word_AQ_PcsUsx0TransmitStatus_HHD_usx0TxRsvdStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0TxIdleInsertion in AQ_PcsUsx0TransmitStatus_HHD */
#define AQ_PcsUsx0TransmitStatus_HHD_usx0TxIdleInsertion 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0TxIdleInsertion in AQ_PcsUsx0TransmitStatus_HHD */
#define bits_AQ_PcsUsx0TransmitStatus_HHD_usx0TxIdleInsertion u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0TxIdleInsertion in AQ_PcsUsx0TransmitStatus_HHD */
#define word_AQ_PcsUsx0TransmitStatus_HHD_usx0TxIdleInsertion u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0TxIdleDeletion in AQ_PcsUsx0TransmitStatus_HHD */
#define AQ_PcsUsx0TransmitStatus_HHD_usx0TxIdleDeletion 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0TxIdleDeletion in AQ_PcsUsx0TransmitStatus_HHD */
#define bits_AQ_PcsUsx0TransmitStatus_HHD_usx0TxIdleDeletion u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0TxIdleDeletion in AQ_PcsUsx0TransmitStatus_HHD */
#define word_AQ_PcsUsx0TransmitStatus_HHD_usx0TxIdleDeletion u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0TxGmiiToXgmiiConvertionStatus in AQ_PcsUsx0TransmitStatus_HHD */
#define AQ_PcsUsx0TransmitStatus_HHD_usx0TxGmiiToXgmiiConvertionStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0TxGmiiToXgmiiConvertionStatus in AQ_PcsUsx0TransmitStatus_HHD */
#define bits_AQ_PcsUsx0TransmitStatus_HHD_usx0TxGmiiToXgmiiConvertionStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0TxGmiiToXgmiiConvertionStatus in AQ_PcsUsx0TransmitStatus_HHD */
#define word_AQ_PcsUsx0TransmitStatus_HHD_usx0TxGmiiToXgmiiConvertionStatus u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1TransmitStatus_HHD */
#define AQ_PcsUsx1TransmitStatus_HHD_baseRegisterAddress 0xC8D0
/*! \brief MMD address of structure AQ_PcsUsx1TransmitStatus_HHD */
#define AQ_PcsUsx1TransmitStatus_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1TxRsvdStatus in AQ_PcsUsx1TransmitStatus_HHD */
#define AQ_PcsUsx1TransmitStatus_HHD_usx1TxRsvdStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1TxRsvdStatus in AQ_PcsUsx1TransmitStatus_HHD */
#define bits_AQ_PcsUsx1TransmitStatus_HHD_usx1TxRsvdStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1TxRsvdStatus in AQ_PcsUsx1TransmitStatus_HHD */
#define word_AQ_PcsUsx1TransmitStatus_HHD_usx1TxRsvdStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1TxIdleInsertion in AQ_PcsUsx1TransmitStatus_HHD */
#define AQ_PcsUsx1TransmitStatus_HHD_usx1TxIdleInsertion 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1TxIdleInsertion in AQ_PcsUsx1TransmitStatus_HHD */
#define bits_AQ_PcsUsx1TransmitStatus_HHD_usx1TxIdleInsertion u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1TxIdleInsertion in AQ_PcsUsx1TransmitStatus_HHD */
#define word_AQ_PcsUsx1TransmitStatus_HHD_usx1TxIdleInsertion u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1TxIdleDeletion in AQ_PcsUsx1TransmitStatus_HHD */
#define AQ_PcsUsx1TransmitStatus_HHD_usx1TxIdleDeletion 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1TxIdleDeletion in AQ_PcsUsx1TransmitStatus_HHD */
#define bits_AQ_PcsUsx1TransmitStatus_HHD_usx1TxIdleDeletion u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1TxIdleDeletion in AQ_PcsUsx1TransmitStatus_HHD */
#define word_AQ_PcsUsx1TransmitStatus_HHD_usx1TxIdleDeletion u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1TxGmiiToXgmiiConvertionStatus in AQ_PcsUsx1TransmitStatus_HHD */
#define AQ_PcsUsx1TransmitStatus_HHD_usx1TxGmiiToXgmiiConvertionStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1TxGmiiToXgmiiConvertionStatus in AQ_PcsUsx1TransmitStatus_HHD */
#define bits_AQ_PcsUsx1TransmitStatus_HHD_usx1TxGmiiToXgmiiConvertionStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1TxGmiiToXgmiiConvertionStatus in AQ_PcsUsx1TransmitStatus_HHD */
#define word_AQ_PcsUsx1TransmitStatus_HHD_usx1TxGmiiToXgmiiConvertionStatus u0.word_0

/*! \brief Base register address of structure AQ_PcsTransmitVendorSystemInterfaceState_HHD */
#define AQ_PcsTransmitVendorSystemInterfaceState_HHD_baseRegisterAddress 0xC8F0
/*! \brief MMD address of structure AQ_PcsTransmitVendorSystemInterfaceState_HHD */
#define AQ_PcsTransmitVendorSystemInterfaceState_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure systemInterfaceTransmitFault in AQ_PcsTransmitVendorSystemInterfaceState_HHD */
#define AQ_PcsTransmitVendorSystemInterfaceState_HHD_systemInterfaceTransmitFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure systemInterfaceTransmitFault in AQ_PcsTransmitVendorSystemInterfaceState_HHD */
#define bits_AQ_PcsTransmitVendorSystemInterfaceState_HHD_systemInterfaceTransmitFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure systemInterfaceTransmitFault in AQ_PcsTransmitVendorSystemInterfaceState_HHD */
#define word_AQ_PcsTransmitVendorSystemInterfaceState_HHD_systemInterfaceTransmitFault u0.word_0

/*! \brief Base register address of structure AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_baseRegisterAddress 0xC900
/*! \brief MMD address of structure AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockSecondsCountBits_15_0 in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpDigitalClockSecondsCountBits_15_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockSecondsCountBits_15_0 in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpDigitalClockSecondsCountBits_15_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockSecondsCountBits_15_0 in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpDigitalClockSecondsCountBits_15_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockSecondsCountBits_31_16 in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpDigitalClockSecondsCountBits_31_16 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockSecondsCountBits_31_16 in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpDigitalClockSecondsCountBits_31_16 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockSecondsCountBits_31_16 in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpDigitalClockSecondsCountBits_31_16 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockSecondsCountBits_47_32 in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpDigitalClockSecondsCountBits_47_32 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockSecondsCountBits_47_32 in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpDigitalClockSecondsCountBits_47_32 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockSecondsCountBits_47_32 in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpDigitalClockSecondsCountBits_47_32 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpDigitalClockNanosecondsCountLSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpDigitalClockNanosecondsCountLSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpDigitalClockNanosecondsCountLSW u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpDigitalClockNanosecondsCountMSW 4
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpDigitalClockNanosecondsCountMSW u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpDigitalClockNanosecondsCountMSW u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpDigitalClockFractionalNanosecondsCountLSW 5
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpDigitalClockFractionalNanosecondsCountLSW u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpDigitalClockFractionalNanosecondsCountLSW u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpDigitalClockFractionalNanosecondsCountMSW 6
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpDigitalClockFractionalNanosecondsCountMSW u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpDigitalClockFractionalNanosecondsCountMSW u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpDigitalClockFractionalSecondsCountLSW 7
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpDigitalClockFractionalSecondsCountLSW u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpDigitalClockFractionalSecondsCountLSW u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure ptpDigitalClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpDigitalClockFractionalSecondsCountMSW 8
/*! \brief Preprocessor variable to relate field to bit position in structure ptpDigitalClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpDigitalClockFractionalSecondsCountMSW u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure ptpDigitalClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpDigitalClockFractionalSecondsCountMSW u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockCountLSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalClockCountLSW 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockCountLSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalClockCountLSW u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockCountLSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalClockCountLSW u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockCountMSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalClockCountMSW 10
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockCountMSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalClockCountMSW u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockCountMSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalClockCountMSW u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockSecondsCountBits_15_0 in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalClockSecondsCountBits_15_0 11
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockSecondsCountBits_15_0 in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalClockSecondsCountBits_15_0 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockSecondsCountBits_15_0 in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalClockSecondsCountBits_15_0 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockSecondsCountBits_31_16 in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalClockSecondsCountBits_31_16 12
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockSecondsCountBits_31_16 in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalClockSecondsCountBits_31_16 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockSecondsCountBits_31_16 in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalClockSecondsCountBits_31_16 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockSecondsCountBits_47_32 in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalClockSecondsCountBits_47_32 13
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockSecondsCountBits_47_32 in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalClockSecondsCountBits_47_32 u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockSecondsCountBits_47_32 in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalClockSecondsCountBits_47_32 u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalClockNanosecondsCountLSW 14
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalClockNanosecondsCountLSW u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalClockNanosecondsCountLSW u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalClockNanosecondsCountMSW 15
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalClockNanosecondsCountMSW u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalClockNanosecondsCountMSW u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalClockFractionalNanosecondsCountLSW 16
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalClockFractionalNanosecondsCountLSW u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalClockFractionalNanosecondsCountLSW u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalClockFractionalNanosecondsCountMSW 17
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalClockFractionalNanosecondsCountMSW u17.bits_17
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalClockFractionalNanosecondsCountMSW u17.word_17
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalClockFractionalSecondsCountLSW 18
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalClockFractionalSecondsCountLSW u18.bits_18
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalClockFractionalSecondsCountLSW u18.word_18
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalClockFractionalSecondsCountMSW 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalClockFractionalSecondsCountMSW u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalClockFractionalSecondsCountMSW u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockSecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockSecondsCountLSW 20
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockSecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockSecondsCountLSW u20.bits_20
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockSecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockSecondsCountLSW u20.word_20
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockSecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockSecondsCountMSW 21
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockSecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockSecondsCountMSW u21.bits_21
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockSecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockSecondsCountMSW u21.word_21
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockNanosecondsCountLSW 22
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockNanosecondsCountLSW u22.bits_22
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockNanosecondsCountLSW u22.word_22
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockNanosecondsCountMSW 23
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockNanosecondsCountMSW u23.bits_23
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockNanosecondsCountMSW u23.word_23
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockFractionalNanosecondsCountLSW 24
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockFractionalNanosecondsCountLSW u24.bits_24
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockFractionalNanosecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockFractionalNanosecondsCountLSW u24.word_24
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockFractionalNanosecondsCountMSW 25
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockFractionalNanosecondsCountMSW u25.bits_25
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockFractionalNanosecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockFractionalNanosecondsCountMSW u25.word_25
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockFractionalSecondsCountLSW 26
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockFractionalSecondsCountLSW u26.bits_26
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockFractionalSecondsCountLSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockFractionalSecondsCountLSW u26.word_26
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockFractionalSecondsCountMSW 27
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockFractionalSecondsCountMSW u27.bits_27
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockFractionalSecondsCountMSW in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockFractionalSecondsCountMSW u27.word_27
/*! \brief Preprocessor variable to relate field to word number in structure ptpExternalGpioClockUpdateDone in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockUpdateDone 28
/*! \brief Preprocessor variable to relate field to bit position in structure ptpExternalGpioClockUpdateDone in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockUpdateDone u28.bits_28
/*! \brief Preprocessor variable to relate field to word position in structure ptpExternalGpioClockUpdateDone in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpExternalGpioClockUpdateDone u28.word_28
/*! \brief Preprocessor variable to relate field to word number in structure ptpUsx0RxTimestampBits_15_0 in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpUsx0RxTimestampBits_15_0 29
/*! \brief Preprocessor variable to relate field to bit position in structure ptpUsx0RxTimestampBits_15_0 in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpUsx0RxTimestampBits_15_0 u29.bits_29
/*! \brief Preprocessor variable to relate field to word position in structure ptpUsx0RxTimestampBits_15_0 in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpUsx0RxTimestampBits_15_0 u29.word_29
/*! \brief Preprocessor variable to relate field to word number in structure ptpUsx0RxTimestampBits_31_16 in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpUsx0RxTimestampBits_31_16 30
/*! \brief Preprocessor variable to relate field to bit position in structure ptpUsx0RxTimestampBits_31_16 in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpUsx0RxTimestampBits_31_16 u30.bits_30
/*! \brief Preprocessor variable to relate field to word position in structure ptpUsx0RxTimestampBits_31_16 in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpUsx0RxTimestampBits_31_16 u30.word_30
/*! \brief Preprocessor variable to relate field to word number in structure ptpUsx0RxTimestampBits_34_32 in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpUsx0RxTimestampBits_34_32 31
/*! \brief Preprocessor variable to relate field to bit position in structure ptpUsx0RxTimestampBits_34_32 in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpUsx0RxTimestampBits_34_32 u31.bits_31
/*! \brief Preprocessor variable to relate field to word position in structure ptpUsx0RxTimestampBits_34_32 in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpUsx0RxTimestampBits_34_32 u31.word_31
/*! \brief Preprocessor variable to relate field to word number in structure ptpUsx1RxTimestampBits_15_0 in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpUsx1RxTimestampBits_15_0 32
/*! \brief Preprocessor variable to relate field to bit position in structure ptpUsx1RxTimestampBits_15_0 in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpUsx1RxTimestampBits_15_0 u32.bits_32
/*! \brief Preprocessor variable to relate field to word position in structure ptpUsx1RxTimestampBits_15_0 in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpUsx1RxTimestampBits_15_0 u32.word_32
/*! \brief Preprocessor variable to relate field to word number in structure ptpUsx1RxTimestampBits_31_16 in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpUsx1RxTimestampBits_31_16 33
/*! \brief Preprocessor variable to relate field to bit position in structure ptpUsx1RxTimestampBits_31_16 in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpUsx1RxTimestampBits_31_16 u33.bits_33
/*! \brief Preprocessor variable to relate field to word position in structure ptpUsx1RxTimestampBits_31_16 in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpUsx1RxTimestampBits_31_16 u33.word_33
/*! \brief Preprocessor variable to relate field to word number in structure ptpUsx1RxTimestampBits_34_32 in AQ_PcsPtpVendorState_HHD */
#define AQ_PcsPtpVendorState_HHD_ptpUsx1RxTimestampBits_34_32 34
/*! \brief Preprocessor variable to relate field to bit position in structure ptpUsx1RxTimestampBits_34_32 in AQ_PcsPtpVendorState_HHD */
#define bits_AQ_PcsPtpVendorState_HHD_ptpUsx1RxTimestampBits_34_32 u34.bits_34
/*! \brief Preprocessor variable to relate field to word position in structure ptpUsx1RxTimestampBits_34_32 in AQ_PcsPtpVendorState_HHD */
#define word_AQ_PcsPtpVendorState_HHD_ptpUsx1RxTimestampBits_34_32 u34.word_34

/*! \brief Base register address of structure AQ_PcsPtpEgressVendorState_HHD */
#define AQ_PcsPtpEgressVendorState_HHD_baseRegisterAddress 0xC930
/*! \brief MMD address of structure AQ_PcsPtpEgressVendorState_HHD */
#define AQ_PcsPtpEgressVendorState_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketCount in AQ_PcsPtpEgressVendorState_HHD */
#define AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketCount 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketCount in AQ_PcsPtpEgressVendorState_HHD */
#define bits_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketCount u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketCount in AQ_PcsPtpEgressVendorState_HHD */
#define word_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketCount u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketDataLSW in AQ_PcsPtpEgressVendorState_HHD */
#define AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketDataLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketDataLSW in AQ_PcsPtpEgressVendorState_HHD */
#define bits_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketDataLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketDataLSW in AQ_PcsPtpEgressVendorState_HHD */
#define word_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketDataLSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketDataMSW in AQ_PcsPtpEgressVendorState_HHD */
#define AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketDataMSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketDataMSW in AQ_PcsPtpEgressVendorState_HHD */
#define bits_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketDataMSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketDataMSW in AQ_PcsPtpEgressVendorState_HHD */
#define word_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketDataMSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketTruncated in AQ_PcsPtpEgressVendorState_HHD */
#define AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketTruncated 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketTruncated in AQ_PcsPtpEgressVendorState_HHD */
#define bits_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketTruncated u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketTruncated in AQ_PcsPtpEgressVendorState_HHD */
#define word_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketTruncated u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketEop in AQ_PcsPtpEgressVendorState_HHD */
#define AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketEop 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketEop in AQ_PcsPtpEgressVendorState_HHD */
#define bits_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketEop u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketEop in AQ_PcsPtpEgressVendorState_HHD */
#define word_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketEop u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketSop in AQ_PcsPtpEgressVendorState_HHD */
#define AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketSop 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketSop in AQ_PcsPtpEgressVendorState_HHD */
#define bits_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketSop u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketSop in AQ_PcsPtpEgressVendorState_HHD */
#define word_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketSop u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketTimeStampCount in AQ_PcsPtpEgressVendorState_HHD */
#define AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketTimeStampCount 4
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketTimeStampCount in AQ_PcsPtpEgressVendorState_HHD */
#define bits_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketTimeStampCount u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketTimeStampCount in AQ_PcsPtpEgressVendorState_HHD */
#define word_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketTimeStampCount u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressPacketTimeStamp in AQ_PcsPtpEgressVendorState_HHD */
#define AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketTimeStamp 5
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressPacketTimeStamp in AQ_PcsPtpEgressVendorState_HHD */
#define bits_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketTimeStamp u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressPacketTimeStamp in AQ_PcsPtpEgressVendorState_HHD */
#define word_AQ_PcsPtpEgressVendorState_HHD_ptpEgressPacketTimeStamp u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressGapFifoError in AQ_PcsPtpEgressVendorState_HHD */
#define AQ_PcsPtpEgressVendorState_HHD_ptpEgressGapFifoError 6
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressGapFifoError in AQ_PcsPtpEgressVendorState_HHD */
#define bits_AQ_PcsPtpEgressVendorState_HHD_ptpEgressGapFifoError u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressGapFifoError in AQ_PcsPtpEgressVendorState_HHD */
#define word_AQ_PcsPtpEgressVendorState_HHD_ptpEgressGapFifoError u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure ptpEgressRxPacketInformation in AQ_PcsPtpEgressVendorState_HHD */
#define AQ_PcsPtpEgressVendorState_HHD_ptpEgressRxPacketInformation 6
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEgressRxPacketInformation in AQ_PcsPtpEgressVendorState_HHD */
#define bits_AQ_PcsPtpEgressVendorState_HHD_ptpEgressRxPacketInformation u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure ptpEgressRxPacketInformation in AQ_PcsPtpEgressVendorState_HHD */
#define word_AQ_PcsPtpEgressVendorState_HHD_ptpEgressRxPacketInformation u6.word_6

/*! \brief Base register address of structure AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_baseRegisterAddress 0xCC00
/*! \brief MMD address of structure AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_1 in AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_reservedPcsTransmitVendorAlarms_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_1 in AQ_PcsTransmitVendorAlarms_HHD */
#define bits_AQ_PcsTransmitVendorAlarms_HHD_reservedPcsTransmitVendorAlarms_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_1 in AQ_PcsTransmitVendorAlarms_HHD */
#define word_AQ_PcsTransmitVendorAlarms_HHD_reservedPcsTransmitVendorAlarms_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTransmitInvalid_64bBlockDetected in AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_xauiTransmitInvalid_64bBlockDetected 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTransmitInvalid_64bBlockDetected in AQ_PcsTransmitVendorAlarms_HHD */
#define bits_AQ_PcsTransmitVendorAlarms_HHD_xauiTransmitInvalid_64bBlockDetected u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTransmitInvalid_64bBlockDetected in AQ_PcsTransmitVendorAlarms_HHD */
#define word_AQ_PcsTransmitVendorAlarms_HHD_xauiTransmitInvalid_64bBlockDetected u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_2 in AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_reservedPcsTransmitVendorAlarms_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_2 in AQ_PcsTransmitVendorAlarms_HHD */
#define bits_AQ_PcsTransmitVendorAlarms_HHD_reservedPcsTransmitVendorAlarms_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_2 in AQ_PcsTransmitVendorAlarms_HHD */
#define word_AQ_PcsTransmitVendorAlarms_HHD_reservedPcsTransmitVendorAlarms_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_3 in AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_reservedPcsTransmitVendorAlarms_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_3 in AQ_PcsTransmitVendorAlarms_HHD */
#define bits_AQ_PcsTransmitVendorAlarms_HHD_reservedPcsTransmitVendorAlarms_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_3 in AQ_PcsTransmitVendorAlarms_HHD */
#define word_AQ_PcsTransmitVendorAlarms_HHD_reservedPcsTransmitVendorAlarms_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_xfi1TransmitInvalidXgmiiCharacterReceived 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_HHD */
#define bits_AQ_PcsTransmitVendorAlarms_HHD_xfi1TransmitInvalidXgmiiCharacterReceived u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_HHD */
#define word_AQ_PcsTransmitVendorAlarms_HHD_xfi1TransmitInvalidXgmiiCharacterReceived u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_xfi1TransmitReservedXgmiiCharacterReceived 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_HHD */
#define bits_AQ_PcsTransmitVendorAlarms_HHD_xfi1TransmitReservedXgmiiCharacterReceived u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_HHD */
#define word_AQ_PcsTransmitVendorAlarms_HHD_xfi1TransmitReservedXgmiiCharacterReceived u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_xfi1Transmit_64bEncodeError 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_HHD */
#define bits_AQ_PcsTransmitVendorAlarms_HHD_xfi1Transmit_64bEncodeError u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_HHD */
#define word_AQ_PcsTransmitVendorAlarms_HHD_xfi1Transmit_64bEncodeError u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TransmitLofDetected in AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_xfi1TransmitLofDetected 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TransmitLofDetected in AQ_PcsTransmitVendorAlarms_HHD */
#define bits_AQ_PcsTransmitVendorAlarms_HHD_xfi1TransmitLofDetected u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TransmitLofDetected in AQ_PcsTransmitVendorAlarms_HHD */
#define word_AQ_PcsTransmitVendorAlarms_HHD_xfi1TransmitLofDetected u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_xfi0TransmitInvalidXgmiiCharacterReceived 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_HHD */
#define bits_AQ_PcsTransmitVendorAlarms_HHD_xfi0TransmitInvalidXgmiiCharacterReceived u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_HHD */
#define word_AQ_PcsTransmitVendorAlarms_HHD_xfi0TransmitInvalidXgmiiCharacterReceived u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_xfi0TransmitReservedXgmiiCharacterReceived 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_HHD */
#define bits_AQ_PcsTransmitVendorAlarms_HHD_xfi0TransmitReservedXgmiiCharacterReceived u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_HHD */
#define word_AQ_PcsTransmitVendorAlarms_HHD_xfi0TransmitReservedXgmiiCharacterReceived u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_xfi0Transmit_64bEncodeError 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_HHD */
#define bits_AQ_PcsTransmitVendorAlarms_HHD_xfi0Transmit_64bEncodeError u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_HHD */
#define word_AQ_PcsTransmitVendorAlarms_HHD_xfi0Transmit_64bEncodeError u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitLofDetected in AQ_PcsTransmitVendorAlarms_HHD */
#define AQ_PcsTransmitVendorAlarms_HHD_xfi0TransmitLofDetected 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitLofDetected in AQ_PcsTransmitVendorAlarms_HHD */
#define bits_AQ_PcsTransmitVendorAlarms_HHD_xfi0TransmitLofDetected u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitLofDetected in AQ_PcsTransmitVendorAlarms_HHD */
#define word_AQ_PcsTransmitVendorAlarms_HHD_xfi0TransmitLofDetected u3.word_3

/*! \brief Base register address of structure AQ_PcsStandardInterruptMask_HHD */
#define AQ_PcsStandardInterruptMask_HHD_baseRegisterAddress 0xD000
/*! \brief MMD address of structure AQ_PcsStandardInterruptMask_HHD */
#define AQ_PcsStandardInterruptMask_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure txLpiReceivedMask in AQ_PcsStandardInterruptMask_HHD */
#define AQ_PcsStandardInterruptMask_HHD_txLpiReceivedMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure txLpiReceivedMask in AQ_PcsStandardInterruptMask_HHD */
#define bits_AQ_PcsStandardInterruptMask_HHD_txLpiReceivedMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure txLpiReceivedMask in AQ_PcsStandardInterruptMask_HHD */
#define word_AQ_PcsStandardInterruptMask_HHD_txLpiReceivedMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rxLpiReceivedMask in AQ_PcsStandardInterruptMask_HHD */
#define AQ_PcsStandardInterruptMask_HHD_rxLpiReceivedMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure rxLpiReceivedMask in AQ_PcsStandardInterruptMask_HHD */
#define bits_AQ_PcsStandardInterruptMask_HHD_rxLpiReceivedMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rxLpiReceivedMask in AQ_PcsStandardInterruptMask_HHD */
#define word_AQ_PcsStandardInterruptMask_HHD_rxLpiReceivedMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsReceiveLinkStatusMask in AQ_PcsStandardInterruptMask_HHD */
#define AQ_PcsStandardInterruptMask_HHD_pcsReceiveLinkStatusMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsReceiveLinkStatusMask in AQ_PcsStandardInterruptMask_HHD */
#define bits_AQ_PcsStandardInterruptMask_HHD_pcsReceiveLinkStatusMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsReceiveLinkStatusMask in AQ_PcsStandardInterruptMask_HHD */
#define word_AQ_PcsStandardInterruptMask_HHD_pcsReceiveLinkStatusMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitFaultMask in AQ_PcsStandardInterruptMask_HHD */
#define AQ_PcsStandardInterruptMask_HHD_transmitFaultMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure transmitFaultMask in AQ_PcsStandardInterruptMask_HHD */
#define bits_AQ_PcsStandardInterruptMask_HHD_transmitFaultMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure transmitFaultMask in AQ_PcsStandardInterruptMask_HHD */
#define word_AQ_PcsStandardInterruptMask_HHD_transmitFaultMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure receiveFaultMask in AQ_PcsStandardInterruptMask_HHD */
#define AQ_PcsStandardInterruptMask_HHD_receiveFaultMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure receiveFaultMask in AQ_PcsStandardInterruptMask_HHD */
#define bits_AQ_PcsStandardInterruptMask_HHD_receiveFaultMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure receiveFaultMask in AQ_PcsStandardInterruptMask_HHD */
#define word_AQ_PcsStandardInterruptMask_HHD_receiveFaultMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tPcsBlockLockLatchedMask in AQ_PcsStandardInterruptMask_HHD */
#define AQ_PcsStandardInterruptMask_HHD__10gbase_tPcsBlockLockLatchedMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tPcsBlockLockLatchedMask in AQ_PcsStandardInterruptMask_HHD */
#define bits_AQ_PcsStandardInterruptMask_HHD__10gbase_tPcsBlockLockLatchedMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tPcsBlockLockLatchedMask in AQ_PcsStandardInterruptMask_HHD */
#define word_AQ_PcsStandardInterruptMask_HHD__10gbase_tPcsBlockLockLatchedMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tHighBerLatchedMask in AQ_PcsStandardInterruptMask_HHD */
#define AQ_PcsStandardInterruptMask_HHD__10gbase_tHighBerLatchedMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tHighBerLatchedMask in AQ_PcsStandardInterruptMask_HHD */
#define bits_AQ_PcsStandardInterruptMask_HHD__10gbase_tHighBerLatchedMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tHighBerLatchedMask in AQ_PcsStandardInterruptMask_HHD */
#define word_AQ_PcsStandardInterruptMask_HHD__10gbase_tHighBerLatchedMask u2.word_2

/*! \brief Base register address of structure AQ_PcsTransmitVendorInterruptMask_HHD */
#define AQ_PcsTransmitVendorInterruptMask_HHD_baseRegisterAddress 0xD400
/*! \brief MMD address of structure AQ_PcsTransmitVendorInterruptMask_HHD */
#define AQ_PcsTransmitVendorInterruptMask_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_1Mask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define AQ_PcsTransmitVendorInterruptMask_HHD_reservedPcsTransmitVendorAlarms_1Mask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_1Mask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define bits_AQ_PcsTransmitVendorInterruptMask_HHD_reservedPcsTransmitVendorAlarms_1Mask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_1Mask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define word_AQ_PcsTransmitVendorInterruptMask_HHD_reservedPcsTransmitVendorAlarms_1Mask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTransmitInvalid_64bBlockDetectedMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define AQ_PcsTransmitVendorInterruptMask_HHD_xauiTransmitInvalid_64bBlockDetectedMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTransmitInvalid_64bBlockDetectedMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define bits_AQ_PcsTransmitVendorInterruptMask_HHD_xauiTransmitInvalid_64bBlockDetectedMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTransmitInvalid_64bBlockDetectedMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define word_AQ_PcsTransmitVendorInterruptMask_HHD_xauiTransmitInvalid_64bBlockDetectedMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_2Mask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define AQ_PcsTransmitVendorInterruptMask_HHD_reservedPcsTransmitVendorAlarms_2Mask 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_2Mask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define bits_AQ_PcsTransmitVendorInterruptMask_HHD_reservedPcsTransmitVendorAlarms_2Mask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_2Mask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define word_AQ_PcsTransmitVendorInterruptMask_HHD_reservedPcsTransmitVendorAlarms_2Mask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_3Mask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define AQ_PcsTransmitVendorInterruptMask_HHD_reservedPcsTransmitVendorAlarms_3Mask 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_3Mask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define bits_AQ_PcsTransmitVendorInterruptMask_HHD_reservedPcsTransmitVendorAlarms_3Mask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_3Mask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define word_AQ_PcsTransmitVendorInterruptMask_HHD_reservedPcsTransmitVendorAlarms_3Mask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define AQ_PcsTransmitVendorInterruptMask_HHD_xfi1TransmitInvalidXgmiiCharacterErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define bits_AQ_PcsTransmitVendorInterruptMask_HHD_xfi1TransmitInvalidXgmiiCharacterErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define word_AQ_PcsTransmitVendorInterruptMask_HHD_xfi1TransmitInvalidXgmiiCharacterErrorMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define AQ_PcsTransmitVendorInterruptMask_HHD_xfi1TransmitReservedXgmiiCharacterErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define bits_AQ_PcsTransmitVendorInterruptMask_HHD_xfi1TransmitReservedXgmiiCharacterErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define word_AQ_PcsTransmitVendorInterruptMask_HHD_xfi1TransmitReservedXgmiiCharacterErrorMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define AQ_PcsTransmitVendorInterruptMask_HHD_xfi1TransmitEncode_64bErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define bits_AQ_PcsTransmitVendorInterruptMask_HHD_xfi1TransmitEncode_64bErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define word_AQ_PcsTransmitVendorInterruptMask_HHD_xfi1TransmitEncode_64bErrorMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define AQ_PcsTransmitVendorInterruptMask_HHD_xfi0TransmitInvalidXgmiiCharacterErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define bits_AQ_PcsTransmitVendorInterruptMask_HHD_xfi0TransmitInvalidXgmiiCharacterErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define word_AQ_PcsTransmitVendorInterruptMask_HHD_xfi0TransmitInvalidXgmiiCharacterErrorMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define AQ_PcsTransmitVendorInterruptMask_HHD_xfi0TransmitReservedXgmiiCharacterErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define bits_AQ_PcsTransmitVendorInterruptMask_HHD_xfi0TransmitReservedXgmiiCharacterErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define word_AQ_PcsTransmitVendorInterruptMask_HHD_xfi0TransmitReservedXgmiiCharacterErrorMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define AQ_PcsTransmitVendorInterruptMask_HHD_xfi0TransmitEncode_64bErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define bits_AQ_PcsTransmitVendorInterruptMask_HHD_xfi0TransmitEncode_64bErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_HHD */
#define word_AQ_PcsTransmitVendorInterruptMask_HHD_xfi0TransmitEncode_64bErrorMask u3.word_3

/*! \brief Base register address of structure AQ_PcsTransmitVendorDebug_HHD */
#define AQ_PcsTransmitVendorDebug_HHD_baseRegisterAddress 0xD800
/*! \brief MMD address of structure AQ_PcsTransmitVendorDebug_HHD */
#define AQ_PcsTransmitVendorDebug_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsTxScramblerDisable in AQ_PcsTransmitVendorDebug_HHD */
#define AQ_PcsTransmitVendorDebug_HHD_pcsTxScramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTxScramblerDisable in AQ_PcsTransmitVendorDebug_HHD */
#define bits_AQ_PcsTransmitVendorDebug_HHD_pcsTxScramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTxScramblerDisable in AQ_PcsTransmitVendorDebug_HHD */
#define word_AQ_PcsTransmitVendorDebug_HHD_pcsTxScramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsTxInjectCrcError in AQ_PcsTransmitVendorDebug_HHD */
#define AQ_PcsTransmitVendorDebug_HHD_pcsTxInjectCrcError 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTxInjectCrcError in AQ_PcsTransmitVendorDebug_HHD */
#define bits_AQ_PcsTransmitVendorDebug_HHD_pcsTxInjectCrcError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTxInjectCrcError in AQ_PcsTransmitVendorDebug_HHD */
#define word_AQ_PcsTransmitVendorDebug_HHD_pcsTxInjectCrcError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsTxInjectFrameError in AQ_PcsTransmitVendorDebug_HHD */
#define AQ_PcsTransmitVendorDebug_HHD_pcsTxInjectFrameError 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTxInjectFrameError in AQ_PcsTransmitVendorDebug_HHD */
#define bits_AQ_PcsTransmitVendorDebug_HHD_pcsTxInjectFrameError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTxInjectFrameError in AQ_PcsTransmitVendorDebug_HHD */
#define word_AQ_PcsTransmitVendorDebug_HHD_pcsTxInjectFrameError u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorProvisioning_HHD */
#define AQ_PcsReceiveVendorProvisioning_HHD_baseRegisterAddress 0xE400
/*! \brief MMD address of structure AQ_PcsReceiveVendorProvisioning_HHD */
#define AQ_PcsReceiveVendorProvisioning_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsRxErrorLdpcFrameEnable in AQ_PcsReceiveVendorProvisioning_HHD */
#define AQ_PcsReceiveVendorProvisioning_HHD_pcsRxErrorLdpcFrameEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsRxErrorLdpcFrameEnable in AQ_PcsReceiveVendorProvisioning_HHD */
#define bits_AQ_PcsReceiveVendorProvisioning_HHD_pcsRxErrorLdpcFrameEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsRxErrorLdpcFrameEnable in AQ_PcsReceiveVendorProvisioning_HHD */
#define word_AQ_PcsReceiveVendorProvisioning_HHD_pcsRxErrorLdpcFrameEnable u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveXfi0Provisioning_HHD */
#define AQ_PcsReceiveXfi0Provisioning_HHD_baseRegisterAddress 0xE460
/*! \brief MMD address of structure AQ_PcsReceiveXfi0Provisioning_HHD */
#define AQ_PcsReceiveXfi0Provisioning_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi0RxDescramblerDisable in AQ_PcsReceiveXfi0Provisioning_HHD */
#define AQ_PcsReceiveXfi0Provisioning_HHD_xfi0RxDescramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0RxDescramblerDisable in AQ_PcsReceiveXfi0Provisioning_HHD */
#define bits_AQ_PcsReceiveXfi0Provisioning_HHD_xfi0RxDescramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi0RxDescramblerDisable in AQ_PcsReceiveXfi0Provisioning_HHD */
#define word_AQ_PcsReceiveXfi0Provisioning_HHD_xfi0RxDescramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestDataSource in AQ_PcsReceiveXfi0Provisioning_HHD */
#define AQ_PcsReceiveXfi0Provisioning_HHD_xfi0TestDataSource 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestDataSource in AQ_PcsReceiveXfi0Provisioning_HHD */
#define bits_AQ_PcsReceiveXfi0Provisioning_HHD_xfi0TestDataSource u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestDataSource in AQ_PcsReceiveXfi0Provisioning_HHD */
#define word_AQ_PcsReceiveXfi0Provisioning_HHD_xfi0TestDataSource u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestModeSelect in AQ_PcsReceiveXfi0Provisioning_HHD */
#define AQ_PcsReceiveXfi0Provisioning_HHD_xfi0TestModeSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestModeSelect in AQ_PcsReceiveXfi0Provisioning_HHD */
#define bits_AQ_PcsReceiveXfi0Provisioning_HHD_xfi0TestModeSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestModeSelect in AQ_PcsReceiveXfi0Provisioning_HHD */
#define word_AQ_PcsReceiveXfi0Provisioning_HHD_xfi0TestModeSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPatternEnable in AQ_PcsReceiveXfi0Provisioning_HHD */
#define AQ_PcsReceiveXfi0Provisioning_HHD_xfi0TestPatternEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPatternEnable in AQ_PcsReceiveXfi0Provisioning_HHD */
#define bits_AQ_PcsReceiveXfi0Provisioning_HHD_xfi0TestPatternEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPatternEnable in AQ_PcsReceiveXfi0Provisioning_HHD */
#define word_AQ_PcsReceiveXfi0Provisioning_HHD_xfi0TestPatternEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0LocalFaultInject in AQ_PcsReceiveXfi0Provisioning_HHD */
#define AQ_PcsReceiveXfi0Provisioning_HHD_xfi0LocalFaultInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0LocalFaultInject in AQ_PcsReceiveXfi0Provisioning_HHD */
#define bits_AQ_PcsReceiveXfi0Provisioning_HHD_xfi0LocalFaultInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0LocalFaultInject in AQ_PcsReceiveXfi0Provisioning_HHD */
#define word_AQ_PcsReceiveXfi0Provisioning_HHD_xfi0LocalFaultInject u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveXfi1Provisioning_HHD */
#define AQ_PcsReceiveXfi1Provisioning_HHD_baseRegisterAddress 0xE470
/*! \brief MMD address of structure AQ_PcsReceiveXfi1Provisioning_HHD */
#define AQ_PcsReceiveXfi1Provisioning_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi1RxDescramblerDisable in AQ_PcsReceiveXfi1Provisioning_HHD */
#define AQ_PcsReceiveXfi1Provisioning_HHD_xfi1RxDescramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1RxDescramblerDisable in AQ_PcsReceiveXfi1Provisioning_HHD */
#define bits_AQ_PcsReceiveXfi1Provisioning_HHD_xfi1RxDescramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi1RxDescramblerDisable in AQ_PcsReceiveXfi1Provisioning_HHD */
#define word_AQ_PcsReceiveXfi1Provisioning_HHD_xfi1RxDescramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestDataSource in AQ_PcsReceiveXfi1Provisioning_HHD */
#define AQ_PcsReceiveXfi1Provisioning_HHD_xfi1TestDataSource 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestDataSource in AQ_PcsReceiveXfi1Provisioning_HHD */
#define bits_AQ_PcsReceiveXfi1Provisioning_HHD_xfi1TestDataSource u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestDataSource in AQ_PcsReceiveXfi1Provisioning_HHD */
#define word_AQ_PcsReceiveXfi1Provisioning_HHD_xfi1TestDataSource u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestModeSelect in AQ_PcsReceiveXfi1Provisioning_HHD */
#define AQ_PcsReceiveXfi1Provisioning_HHD_xfi0TestModeSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestModeSelect in AQ_PcsReceiveXfi1Provisioning_HHD */
#define bits_AQ_PcsReceiveXfi1Provisioning_HHD_xfi0TestModeSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestModeSelect in AQ_PcsReceiveXfi1Provisioning_HHD */
#define word_AQ_PcsReceiveXfi1Provisioning_HHD_xfi0TestModeSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestPatternEnable in AQ_PcsReceiveXfi1Provisioning_HHD */
#define AQ_PcsReceiveXfi1Provisioning_HHD_xfi1TestPatternEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestPatternEnable in AQ_PcsReceiveXfi1Provisioning_HHD */
#define bits_AQ_PcsReceiveXfi1Provisioning_HHD_xfi1TestPatternEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestPatternEnable in AQ_PcsReceiveXfi1Provisioning_HHD */
#define word_AQ_PcsReceiveXfi1Provisioning_HHD_xfi1TestPatternEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1LocalFaultInject in AQ_PcsReceiveXfi1Provisioning_HHD */
#define AQ_PcsReceiveXfi1Provisioning_HHD_xfi1LocalFaultInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1LocalFaultInject in AQ_PcsReceiveXfi1Provisioning_HHD */
#define bits_AQ_PcsReceiveXfi1Provisioning_HHD_xfi1LocalFaultInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1LocalFaultInject in AQ_PcsReceiveXfi1Provisioning_HHD */
#define word_AQ_PcsReceiveXfi1Provisioning_HHD_xfi1LocalFaultInject u1.word_1

/*! \brief Base register address of structure AQ_PcsUsx0RxControlRegister_HHD */
#define AQ_PcsUsx0RxControlRegister_HHD_baseRegisterAddress 0xE4D0
/*! \brief MMD address of structure AQ_PcsUsx0RxControlRegister_HHD */
#define AQ_PcsUsx0RxControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxRsvdControl in AQ_PcsUsx0RxControlRegister_HHD */
#define AQ_PcsUsx0RxControlRegister_HHD_usx0RxRsvdControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxRsvdControl in AQ_PcsUsx0RxControlRegister_HHD */
#define bits_AQ_PcsUsx0RxControlRegister_HHD_usx0RxRsvdControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxRsvdControl in AQ_PcsUsx0RxControlRegister_HHD */
#define word_AQ_PcsUsx0RxControlRegister_HHD_usx0RxRsvdControl u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0HeaderCrcChk in AQ_PcsUsx0RxControlRegister_HHD */
#define AQ_PcsUsx0RxControlRegister_HHD_usx0HeaderCrcChk 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0HeaderCrcChk in AQ_PcsUsx0RxControlRegister_HHD */
#define bits_AQ_PcsUsx0RxControlRegister_HHD_usx0HeaderCrcChk u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0HeaderCrcChk in AQ_PcsUsx0RxControlRegister_HHD */
#define word_AQ_PcsUsx0RxControlRegister_HHD_usx0HeaderCrcChk u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxPktInfoExtensionField in AQ_PcsUsx0RxControlRegister_HHD */
#define AQ_PcsUsx0RxControlRegister_HHD_usx0RxPktInfoExtensionField 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxPktInfoExtensionField in AQ_PcsUsx0RxControlRegister_HHD */
#define bits_AQ_PcsUsx0RxControlRegister_HHD_usx0RxPktInfoExtensionField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxPktInfoExtensionField in AQ_PcsUsx0RxControlRegister_HHD */
#define word_AQ_PcsUsx0RxControlRegister_HHD_usx0RxPktInfoExtensionField u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxLocalFaultMode in AQ_PcsUsx0RxControlRegister_HHD */
#define AQ_PcsUsx0RxControlRegister_HHD_usx0RxLocalFaultMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxLocalFaultMode in AQ_PcsUsx0RxControlRegister_HHD */
#define bits_AQ_PcsUsx0RxControlRegister_HHD_usx0RxLocalFaultMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxLocalFaultMode in AQ_PcsUsx0RxControlRegister_HHD */
#define word_AQ_PcsUsx0RxControlRegister_HHD_usx0RxLocalFaultMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxIfgMode in AQ_PcsUsx0RxControlRegister_HHD */
#define AQ_PcsUsx0RxControlRegister_HHD_usx0RxIfgMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxIfgMode in AQ_PcsUsx0RxControlRegister_HHD */
#define bits_AQ_PcsUsx0RxControlRegister_HHD_usx0RxIfgMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxIfgMode in AQ_PcsUsx0RxControlRegister_HHD */
#define word_AQ_PcsUsx0RxControlRegister_HHD_usx0RxIfgMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxXgmiiToGmiiConversionControl in AQ_PcsUsx0RxControlRegister_HHD */
#define AQ_PcsUsx0RxControlRegister_HHD_usx0RxXgmiiToGmiiConversionControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxXgmiiToGmiiConversionControl in AQ_PcsUsx0RxControlRegister_HHD */
#define bits_AQ_PcsUsx0RxControlRegister_HHD_usx0RxXgmiiToGmiiConversionControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxXgmiiToGmiiConversionControl in AQ_PcsUsx0RxControlRegister_HHD */
#define word_AQ_PcsUsx0RxControlRegister_HHD_usx0RxXgmiiToGmiiConversionControl u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0RxFifoControlRegister_HHD */
#define AQ_PcsUsx0RxFifoControlRegister_HHD_baseRegisterAddress 0xE4D1
/*! \brief MMD address of structure AQ_PcsUsx0RxFifoControlRegister_HHD */
#define AQ_PcsUsx0RxFifoControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxFifoReset in AQ_PcsUsx0RxFifoControlRegister_HHD */
#define AQ_PcsUsx0RxFifoControlRegister_HHD_usx0RxFifoReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxFifoReset in AQ_PcsUsx0RxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx0RxFifoControlRegister_HHD_usx0RxFifoReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxFifoReset in AQ_PcsUsx0RxFifoControlRegister_HHD */
#define word_AQ_PcsUsx0RxFifoControlRegister_HHD_usx0RxFifoReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxFifoThreshold in AQ_PcsUsx0RxFifoControlRegister_HHD */
#define AQ_PcsUsx0RxFifoControlRegister_HHD_usx0RxFifoThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxFifoThreshold in AQ_PcsUsx0RxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx0RxFifoControlRegister_HHD_usx0RxFifoThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxFifoThreshold in AQ_PcsUsx0RxFifoControlRegister_HHD */
#define word_AQ_PcsUsx0RxFifoControlRegister_HHD_usx0RxFifoThreshold u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxFifoIfgThreshold in AQ_PcsUsx0RxFifoControlRegister_HHD */
#define AQ_PcsUsx0RxFifoControlRegister_HHD_usx0RxFifoIfgThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxFifoIfgThreshold in AQ_PcsUsx0RxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx0RxFifoControlRegister_HHD_usx0RxFifoIfgThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxFifoIfgThreshold in AQ_PcsUsx0RxFifoControlRegister_HHD */
#define word_AQ_PcsUsx0RxFifoControlRegister_HHD_usx0RxFifoIfgThreshold u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0SmControlRegister_HHD */
#define AQ_PcsUsx0SmControlRegister_HHD_baseRegisterAddress 0xE4D2
/*! \brief MMD address of structure AQ_PcsUsx0SmControlRegister_HHD */
#define AQ_PcsUsx0SmControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0SmFreeze in AQ_PcsUsx0SmControlRegister_HHD */
#define AQ_PcsUsx0SmControlRegister_HHD_usx0SmFreeze 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0SmFreeze in AQ_PcsUsx0SmControlRegister_HHD */
#define bits_AQ_PcsUsx0SmControlRegister_HHD_usx0SmFreeze u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0SmFreeze in AQ_PcsUsx0SmControlRegister_HHD */
#define word_AQ_PcsUsx0SmControlRegister_HHD_usx0SmFreeze u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0SmForce in AQ_PcsUsx0SmControlRegister_HHD */
#define AQ_PcsUsx0SmControlRegister_HHD_usx0SmForce 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0SmForce in AQ_PcsUsx0SmControlRegister_HHD */
#define bits_AQ_PcsUsx0SmControlRegister_HHD_usx0SmForce u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0SmForce in AQ_PcsUsx0SmControlRegister_HHD */
#define word_AQ_PcsUsx0SmControlRegister_HHD_usx0SmForce u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0SmRedirect in AQ_PcsUsx0SmControlRegister_HHD */
#define AQ_PcsUsx0SmControlRegister_HHD_usx0SmRedirect 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0SmRedirect in AQ_PcsUsx0SmControlRegister_HHD */
#define bits_AQ_PcsUsx0SmControlRegister_HHD_usx0SmRedirect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0SmRedirect in AQ_PcsUsx0SmControlRegister_HHD */
#define word_AQ_PcsUsx0SmControlRegister_HHD_usx0SmRedirect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0SmCurrentStateMatch in AQ_PcsUsx0SmControlRegister_HHD */
#define AQ_PcsUsx0SmControlRegister_HHD_usx0SmCurrentStateMatch 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0SmCurrentStateMatch in AQ_PcsUsx0SmControlRegister_HHD */
#define bits_AQ_PcsUsx0SmControlRegister_HHD_usx0SmCurrentStateMatch u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0SmCurrentStateMatch in AQ_PcsUsx0SmControlRegister_HHD */
#define word_AQ_PcsUsx0SmControlRegister_HHD_usx0SmCurrentStateMatch u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0SmNextStateMatch in AQ_PcsUsx0SmControlRegister_HHD */
#define AQ_PcsUsx0SmControlRegister_HHD_usx0SmNextStateMatch 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0SmNextStateMatch in AQ_PcsUsx0SmControlRegister_HHD */
#define bits_AQ_PcsUsx0SmControlRegister_HHD_usx0SmNextStateMatch u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0SmNextStateMatch in AQ_PcsUsx0SmControlRegister_HHD */
#define word_AQ_PcsUsx0SmControlRegister_HHD_usx0SmNextStateMatch u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0SmRedirectState in AQ_PcsUsx0SmControlRegister_HHD */
#define AQ_PcsUsx0SmControlRegister_HHD_usx0SmRedirectState 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0SmRedirectState in AQ_PcsUsx0SmControlRegister_HHD */
#define bits_AQ_PcsUsx0SmControlRegister_HHD_usx0SmRedirectState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0SmRedirectState in AQ_PcsUsx0SmControlRegister_HHD */
#define word_AQ_PcsUsx0SmControlRegister_HHD_usx0SmRedirectState u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0LinkTimerControlRegister_HHD */
#define AQ_PcsUsx0LinkTimerControlRegister_HHD_baseRegisterAddress 0xE4D3
/*! \brief MMD address of structure AQ_PcsUsx0LinkTimerControlRegister_HHD */
#define AQ_PcsUsx0LinkTimerControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkTimerReset in AQ_PcsUsx0LinkTimerControlRegister_HHD */
#define AQ_PcsUsx0LinkTimerControlRegister_HHD_usx0LinkTimerReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkTimerReset in AQ_PcsUsx0LinkTimerControlRegister_HHD */
#define bits_AQ_PcsUsx0LinkTimerControlRegister_HHD_usx0LinkTimerReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkTimerReset in AQ_PcsUsx0LinkTimerControlRegister_HHD */
#define word_AQ_PcsUsx0LinkTimerControlRegister_HHD_usx0LinkTimerReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkTimerFreeze in AQ_PcsUsx0LinkTimerControlRegister_HHD */
#define AQ_PcsUsx0LinkTimerControlRegister_HHD_usx0LinkTimerFreeze 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkTimerFreeze in AQ_PcsUsx0LinkTimerControlRegister_HHD */
#define bits_AQ_PcsUsx0LinkTimerControlRegister_HHD_usx0LinkTimerFreeze u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkTimerFreeze in AQ_PcsUsx0LinkTimerControlRegister_HHD */
#define word_AQ_PcsUsx0LinkTimerControlRegister_HHD_usx0LinkTimerFreeze u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkTimerThreshold in AQ_PcsUsx0LinkTimerControlRegister_HHD */
#define AQ_PcsUsx0LinkTimerControlRegister_HHD_usx0LinkTimerThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkTimerThreshold in AQ_PcsUsx0LinkTimerControlRegister_HHD */
#define bits_AQ_PcsUsx0LinkTimerControlRegister_HHD_usx0LinkTimerThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkTimerThreshold in AQ_PcsUsx0LinkTimerControlRegister_HHD */
#define word_AQ_PcsUsx0LinkTimerControlRegister_HHD_usx0LinkTimerThreshold u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0RxFaultControlRegister_HHD */
#define AQ_PcsUsx0RxFaultControlRegister_HHD_baseRegisterAddress 0xE4D4
/*! \brief MMD address of structure AQ_PcsUsx0RxFaultControlRegister_HHD */
#define AQ_PcsUsx0RxFaultControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxFaultMask in AQ_PcsUsx0RxFaultControlRegister_HHD */
#define AQ_PcsUsx0RxFaultControlRegister_HHD_usx0RxFaultMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxFaultMask in AQ_PcsUsx0RxFaultControlRegister_HHD */
#define bits_AQ_PcsUsx0RxFaultControlRegister_HHD_usx0RxFaultMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxFaultMask in AQ_PcsUsx0RxFaultControlRegister_HHD */
#define word_AQ_PcsUsx0RxFaultControlRegister_HHD_usx0RxFaultMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxFaultData in AQ_PcsUsx0RxFaultControlRegister_HHD */
#define AQ_PcsUsx0RxFaultControlRegister_HHD_usx0RxFaultData 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxFaultData in AQ_PcsUsx0RxFaultControlRegister_HHD */
#define bits_AQ_PcsUsx0RxFaultControlRegister_HHD_usx0RxFaultData u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxFaultData in AQ_PcsUsx0RxFaultControlRegister_HHD */
#define word_AQ_PcsUsx0RxFaultControlRegister_HHD_usx0RxFaultData u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1RxControlRegister_HHD */
#define AQ_PcsUsx1RxControlRegister_HHD_baseRegisterAddress 0xE4E0
/*! \brief MMD address of structure AQ_PcsUsx1RxControlRegister_HHD */
#define AQ_PcsUsx1RxControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxRsvdControl in AQ_PcsUsx1RxControlRegister_HHD */
#define AQ_PcsUsx1RxControlRegister_HHD_usx1RxRsvdControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxRsvdControl in AQ_PcsUsx1RxControlRegister_HHD */
#define bits_AQ_PcsUsx1RxControlRegister_HHD_usx1RxRsvdControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxRsvdControl in AQ_PcsUsx1RxControlRegister_HHD */
#define word_AQ_PcsUsx1RxControlRegister_HHD_usx1RxRsvdControl u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1HeaderCrcChk in AQ_PcsUsx1RxControlRegister_HHD */
#define AQ_PcsUsx1RxControlRegister_HHD_usx1HeaderCrcChk 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1HeaderCrcChk in AQ_PcsUsx1RxControlRegister_HHD */
#define bits_AQ_PcsUsx1RxControlRegister_HHD_usx1HeaderCrcChk u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1HeaderCrcChk in AQ_PcsUsx1RxControlRegister_HHD */
#define word_AQ_PcsUsx1RxControlRegister_HHD_usx1HeaderCrcChk u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxPktInfoExtensionField in AQ_PcsUsx1RxControlRegister_HHD */
#define AQ_PcsUsx1RxControlRegister_HHD_usx1RxPktInfoExtensionField 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxPktInfoExtensionField in AQ_PcsUsx1RxControlRegister_HHD */
#define bits_AQ_PcsUsx1RxControlRegister_HHD_usx1RxPktInfoExtensionField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxPktInfoExtensionField in AQ_PcsUsx1RxControlRegister_HHD */
#define word_AQ_PcsUsx1RxControlRegister_HHD_usx1RxPktInfoExtensionField u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxLocalFaultMode in AQ_PcsUsx1RxControlRegister_HHD */
#define AQ_PcsUsx1RxControlRegister_HHD_usx1RxLocalFaultMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxLocalFaultMode in AQ_PcsUsx1RxControlRegister_HHD */
#define bits_AQ_PcsUsx1RxControlRegister_HHD_usx1RxLocalFaultMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxLocalFaultMode in AQ_PcsUsx1RxControlRegister_HHD */
#define word_AQ_PcsUsx1RxControlRegister_HHD_usx1RxLocalFaultMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxIfgMode in AQ_PcsUsx1RxControlRegister_HHD */
#define AQ_PcsUsx1RxControlRegister_HHD_usx1RxIfgMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxIfgMode in AQ_PcsUsx1RxControlRegister_HHD */
#define bits_AQ_PcsUsx1RxControlRegister_HHD_usx1RxIfgMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxIfgMode in AQ_PcsUsx1RxControlRegister_HHD */
#define word_AQ_PcsUsx1RxControlRegister_HHD_usx1RxIfgMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxXgmiiToGmiiConversionControl in AQ_PcsUsx1RxControlRegister_HHD */
#define AQ_PcsUsx1RxControlRegister_HHD_usx1RxXgmiiToGmiiConversionControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxXgmiiToGmiiConversionControl in AQ_PcsUsx1RxControlRegister_HHD */
#define bits_AQ_PcsUsx1RxControlRegister_HHD_usx1RxXgmiiToGmiiConversionControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxXgmiiToGmiiConversionControl in AQ_PcsUsx1RxControlRegister_HHD */
#define word_AQ_PcsUsx1RxControlRegister_HHD_usx1RxXgmiiToGmiiConversionControl u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1RxFifoControlRegister_HHD */
#define AQ_PcsUsx1RxFifoControlRegister_HHD_baseRegisterAddress 0xE4E1
/*! \brief MMD address of structure AQ_PcsUsx1RxFifoControlRegister_HHD */
#define AQ_PcsUsx1RxFifoControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxFifoReset in AQ_PcsUsx1RxFifoControlRegister_HHD */
#define AQ_PcsUsx1RxFifoControlRegister_HHD_usx1RxFifoReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxFifoReset in AQ_PcsUsx1RxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx1RxFifoControlRegister_HHD_usx1RxFifoReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxFifoReset in AQ_PcsUsx1RxFifoControlRegister_HHD */
#define word_AQ_PcsUsx1RxFifoControlRegister_HHD_usx1RxFifoReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxFifoThreshold in AQ_PcsUsx1RxFifoControlRegister_HHD */
#define AQ_PcsUsx1RxFifoControlRegister_HHD_usx1RxFifoThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxFifoThreshold in AQ_PcsUsx1RxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx1RxFifoControlRegister_HHD_usx1RxFifoThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxFifoThreshold in AQ_PcsUsx1RxFifoControlRegister_HHD */
#define word_AQ_PcsUsx1RxFifoControlRegister_HHD_usx1RxFifoThreshold u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxFifoIfgThreshold in AQ_PcsUsx1RxFifoControlRegister_HHD */
#define AQ_PcsUsx1RxFifoControlRegister_HHD_usx1RxFifoIfgThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxFifoIfgThreshold in AQ_PcsUsx1RxFifoControlRegister_HHD */
#define bits_AQ_PcsUsx1RxFifoControlRegister_HHD_usx1RxFifoIfgThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxFifoIfgThreshold in AQ_PcsUsx1RxFifoControlRegister_HHD */
#define word_AQ_PcsUsx1RxFifoControlRegister_HHD_usx1RxFifoIfgThreshold u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1SmControlRegister_HHD */
#define AQ_PcsUsx1SmControlRegister_HHD_baseRegisterAddress 0xE4E2
/*! \brief MMD address of structure AQ_PcsUsx1SmControlRegister_HHD */
#define AQ_PcsUsx1SmControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0SmFreeze in AQ_PcsUsx1SmControlRegister_HHD */
#define AQ_PcsUsx1SmControlRegister_HHD_usx0SmFreeze 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0SmFreeze in AQ_PcsUsx1SmControlRegister_HHD */
#define bits_AQ_PcsUsx1SmControlRegister_HHD_usx0SmFreeze u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0SmFreeze in AQ_PcsUsx1SmControlRegister_HHD */
#define word_AQ_PcsUsx1SmControlRegister_HHD_usx0SmFreeze u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1SmForce in AQ_PcsUsx1SmControlRegister_HHD */
#define AQ_PcsUsx1SmControlRegister_HHD_usx1SmForce 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1SmForce in AQ_PcsUsx1SmControlRegister_HHD */
#define bits_AQ_PcsUsx1SmControlRegister_HHD_usx1SmForce u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1SmForce in AQ_PcsUsx1SmControlRegister_HHD */
#define word_AQ_PcsUsx1SmControlRegister_HHD_usx1SmForce u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1SmRedirect in AQ_PcsUsx1SmControlRegister_HHD */
#define AQ_PcsUsx1SmControlRegister_HHD_usx1SmRedirect 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1SmRedirect in AQ_PcsUsx1SmControlRegister_HHD */
#define bits_AQ_PcsUsx1SmControlRegister_HHD_usx1SmRedirect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1SmRedirect in AQ_PcsUsx1SmControlRegister_HHD */
#define word_AQ_PcsUsx1SmControlRegister_HHD_usx1SmRedirect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1SmCurrentStateMatch in AQ_PcsUsx1SmControlRegister_HHD */
#define AQ_PcsUsx1SmControlRegister_HHD_usx1SmCurrentStateMatch 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1SmCurrentStateMatch in AQ_PcsUsx1SmControlRegister_HHD */
#define bits_AQ_PcsUsx1SmControlRegister_HHD_usx1SmCurrentStateMatch u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1SmCurrentStateMatch in AQ_PcsUsx1SmControlRegister_HHD */
#define word_AQ_PcsUsx1SmControlRegister_HHD_usx1SmCurrentStateMatch u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1SmNextStateMatch in AQ_PcsUsx1SmControlRegister_HHD */
#define AQ_PcsUsx1SmControlRegister_HHD_usx1SmNextStateMatch 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1SmNextStateMatch in AQ_PcsUsx1SmControlRegister_HHD */
#define bits_AQ_PcsUsx1SmControlRegister_HHD_usx1SmNextStateMatch u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1SmNextStateMatch in AQ_PcsUsx1SmControlRegister_HHD */
#define word_AQ_PcsUsx1SmControlRegister_HHD_usx1SmNextStateMatch u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1SmRedirectState in AQ_PcsUsx1SmControlRegister_HHD */
#define AQ_PcsUsx1SmControlRegister_HHD_usx1SmRedirectState 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1SmRedirectState in AQ_PcsUsx1SmControlRegister_HHD */
#define bits_AQ_PcsUsx1SmControlRegister_HHD_usx1SmRedirectState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1SmRedirectState in AQ_PcsUsx1SmControlRegister_HHD */
#define word_AQ_PcsUsx1SmControlRegister_HHD_usx1SmRedirectState u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1LinkTimerControlRegister_HHD */
#define AQ_PcsUsx1LinkTimerControlRegister_HHD_baseRegisterAddress 0xE4E3
/*! \brief MMD address of structure AQ_PcsUsx1LinkTimerControlRegister_HHD */
#define AQ_PcsUsx1LinkTimerControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkTimerReset in AQ_PcsUsx1LinkTimerControlRegister_HHD */
#define AQ_PcsUsx1LinkTimerControlRegister_HHD_usx1LinkTimerReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkTimerReset in AQ_PcsUsx1LinkTimerControlRegister_HHD */
#define bits_AQ_PcsUsx1LinkTimerControlRegister_HHD_usx1LinkTimerReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkTimerReset in AQ_PcsUsx1LinkTimerControlRegister_HHD */
#define word_AQ_PcsUsx1LinkTimerControlRegister_HHD_usx1LinkTimerReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkTimerFreeze in AQ_PcsUsx1LinkTimerControlRegister_HHD */
#define AQ_PcsUsx1LinkTimerControlRegister_HHD_usx1LinkTimerFreeze 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkTimerFreeze in AQ_PcsUsx1LinkTimerControlRegister_HHD */
#define bits_AQ_PcsUsx1LinkTimerControlRegister_HHD_usx1LinkTimerFreeze u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkTimerFreeze in AQ_PcsUsx1LinkTimerControlRegister_HHD */
#define word_AQ_PcsUsx1LinkTimerControlRegister_HHD_usx1LinkTimerFreeze u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkTimerThreshold in AQ_PcsUsx1LinkTimerControlRegister_HHD */
#define AQ_PcsUsx1LinkTimerControlRegister_HHD_usx1LinkTimerThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkTimerThreshold in AQ_PcsUsx1LinkTimerControlRegister_HHD */
#define bits_AQ_PcsUsx1LinkTimerControlRegister_HHD_usx1LinkTimerThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkTimerThreshold in AQ_PcsUsx1LinkTimerControlRegister_HHD */
#define word_AQ_PcsUsx1LinkTimerControlRegister_HHD_usx1LinkTimerThreshold u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1RxFaultControlRegister_HHD */
#define AQ_PcsUsx1RxFaultControlRegister_HHD_baseRegisterAddress 0xE4E4
/*! \brief MMD address of structure AQ_PcsUsx1RxFaultControlRegister_HHD */
#define AQ_PcsUsx1RxFaultControlRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxFaultMask in AQ_PcsUsx1RxFaultControlRegister_HHD */
#define AQ_PcsUsx1RxFaultControlRegister_HHD_usx1RxFaultMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxFaultMask in AQ_PcsUsx1RxFaultControlRegister_HHD */
#define bits_AQ_PcsUsx1RxFaultControlRegister_HHD_usx1RxFaultMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxFaultMask in AQ_PcsUsx1RxFaultControlRegister_HHD */
#define word_AQ_PcsUsx1RxFaultControlRegister_HHD_usx1RxFaultMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxFaultData in AQ_PcsUsx1RxFaultControlRegister_HHD */
#define AQ_PcsUsx1RxFaultControlRegister_HHD_usx1RxFaultData 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxFaultData in AQ_PcsUsx1RxFaultControlRegister_HHD */
#define bits_AQ_PcsUsx1RxFaultControlRegister_HHD_usx1RxFaultData u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxFaultData in AQ_PcsUsx1RxFaultControlRegister_HHD */
#define word_AQ_PcsUsx1RxFaultControlRegister_HHD_usx1RxFaultData u0.word_0

/*! \brief Base register address of structure AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_baseRegisterAddress 0xE600
/*! \brief MMD address of structure AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressVlanTaggingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressVlanTaggingEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressVlanTaggingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressVlanTaggingEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressVlanTaggingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressVlanTaggingEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6_udpEncapsulatedEnabled in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6_udpEncapsulatedEnabled 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6_udpEncapsulatedEnabled in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6_udpEncapsulatedEnabled u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6_udpEncapsulatedEnabled in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6_udpEncapsulatedEnabled u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv4_udpEncapsulatedEnabled in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv4_udpEncapsulatedEnabled 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv4_udpEncapsulatedEnabled in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv4_udpEncapsulatedEnabled u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv4_udpEncapsulatedEnabled in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv4_udpEncapsulatedEnabled u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressEthernetEncapsulatedEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressEthernetEncapsulatedEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressEthernetEncapsulatedEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressEthernetEncapsulatedEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressEthernetEncapsulatedEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressEthernetEncapsulatedEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressNtpConfiguration in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtpConfiguration 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressNtpConfiguration in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtpConfiguration u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressNtpConfiguration in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtpConfiguration u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressBackPressureEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressBackPressureEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressBackPressureEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressBackPressureEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressBackPressureEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressBackPressureEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressNtpEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtpEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressNtpEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtpEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressNtpEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtpEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_2Enable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2Enable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_2Enable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2Enable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_2Enable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2Enable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_1Enable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_1Enable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_1Enable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_1Enable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_1Enable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_1Enable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressMatchingEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressMatchingEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressMatchingEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv4DestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv4DestinationAddressMatchingEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv4DestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv4DestinationAddressMatchingEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv4DestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv4DestinationAddressMatchingEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressMacDestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressMacDestinationAddressMatchingEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressMacDestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressMacDestinationAddressMatchingEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressMacDestinationAddressMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressMacDestinationAddressMatchingEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressEthertypeMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressEthertypeMatchingEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressEthertypeMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressEthertypeMatchingEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressEthertypeMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressEthertypeMatchingEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressNtp_sntpVersion in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtp_sntpVersion 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressNtp_sntpVersion in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtp_sntpVersion u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressNtp_sntpVersion in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtp_sntpVersion u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588_2StepEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588_2StepEnable 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588_2StepEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588_2StepEnable u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588_2StepEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588_2StepEnable u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_2DomainMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2DomainMatchingEnable 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_2DomainMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2DomainMatchingEnable u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_2DomainMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2DomainMatchingEnable u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressUdpDestinationPortMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpDestinationPortMatchingEnable 2
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressUdpDestinationPortMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpDestinationPortMatchingEnable u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressUdpDestinationPortMatchingEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpDestinationPortMatchingEnable u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressEthertype in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressEthertype 3
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressEthertype in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressEthertype u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressEthertype in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressEthertype u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressMacDestinationAddressBits_15_0 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressMacDestinationAddressBits_15_0 4
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressMacDestinationAddressBits_15_0 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressMacDestinationAddressBits_15_0 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressMacDestinationAddressBits_15_0 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressMacDestinationAddressBits_15_0 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressMacDestinationAddressBits_31_16 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressMacDestinationAddressBits_31_16 5
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressMacDestinationAddressBits_31_16 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressMacDestinationAddressBits_31_16 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressMacDestinationAddressBits_31_16 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressMacDestinationAddressBits_31_16 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressMacDestinationAddressBits_47_32 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressMacDestinationAddressBits_47_32 6
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressMacDestinationAddressBits_47_32 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressMacDestinationAddressBits_47_32 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressMacDestinationAddressBits_47_32 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressMacDestinationAddressBits_47_32 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv4DestinationAddressLSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv4DestinationAddressLSW 7
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv4DestinationAddressLSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv4DestinationAddressLSW u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv4DestinationAddressLSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv4DestinationAddressLSW u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv4DestinationAddressMSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv4DestinationAddressMSW 8
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv4DestinationAddressMSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv4DestinationAddressMSW u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv4DestinationAddressMSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv4DestinationAddressMSW u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_15_0 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_15_0 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_15_0 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_15_0 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_15_0 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_15_0 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_31_16 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_31_16 10
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_31_16 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_31_16 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_31_16 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_31_16 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_47_32 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_47_32 11
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_47_32 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_47_32 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_47_32 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_47_32 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_63_48 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_63_48 12
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_63_48 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_63_48 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_63_48 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_63_48 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_79_64 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_79_64 13
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_79_64 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_79_64 u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_79_64 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_79_64 u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_95_80 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_95_80 14
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_95_80 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_95_80 u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_95_80 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_95_80 u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_111_96 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_111_96 15
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_111_96 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_111_96 u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_111_96 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_111_96 u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressIpv6DestinationAddressBits_127_112 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_127_112 16
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressIpv6DestinationAddressBits_127_112 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_127_112 u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressIpv6DestinationAddressBits_127_112 in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressIpv6DestinationAddressBits_127_112 u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressUdpDestinationPort in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpDestinationPort 17
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressUdpDestinationPort in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpDestinationPort u17.bits_17
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressUdpDestinationPort in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpDestinationPort u17.word_17
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_2Domain in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2Domain 18
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_2Domain in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2Domain u18.bits_18
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_2Domain in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2Domain u18.word_18
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressCorrectionOffsetSign in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionOffsetSign 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressCorrectionOffsetSign in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionOffsetSign u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressCorrectionOffsetSign in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionOffsetSign u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampOffsetSign in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampOffsetSign 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampOffsetSign in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampOffsetSign u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampOffsetSign in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampOffsetSign u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressSetTimeStampOffset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressSetTimeStampOffset 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressSetTimeStampOffset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressSetTimeStampOffset u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressSetTimeStampOffset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressSetTimeStampOffset u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressByteSwap in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressByteSwap 19
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressByteSwap in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressByteSwap u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressByteSwap in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressByteSwap u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampNanosecondOffset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampNanosecondOffset 20
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampNanosecondOffset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampNanosecondOffset u20.bits_20
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampNanosecondOffset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampNanosecondOffset u20.word_20
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampFractionalSecondOffsetLSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampFractionalSecondOffsetLSW 21
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampFractionalSecondOffsetLSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampFractionalSecondOffsetLSW u21.bits_21
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampFractionalSecondOffsetLSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampFractionalSecondOffsetLSW u21.word_21
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampFractionalSecondOffsetMSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampFractionalSecondOffsetMSW 22
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampFractionalSecondOffsetMSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampFractionalSecondOffsetMSW u22.bits_22
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampFractionalSecondOffsetMSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampFractionalSecondOffsetMSW u22.word_22
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressCorrectionOffsetLSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionOffsetLSW 23
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressCorrectionOffsetLSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionOffsetLSW u23.bits_23
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressCorrectionOffsetLSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionOffsetLSW u23.word_23
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressCorrectionOffsetMSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionOffsetMSW 24
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressCorrectionOffsetMSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionOffsetMSW u24.bits_24
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressCorrectionOffsetMSW in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionOffsetMSW u24.word_24
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketAction 25
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketAction u25.bits_25
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketAction u25.word_25
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressNtp_sntpTimeStampAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtp_sntpTimeStampAction 26
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressNtp_sntpTimeStampAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtp_sntpTimeStampAction u26.bits_26
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressNtp_sntpTimeStampAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtp_sntpTimeStampAction u26.word_26
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressNtp_sntpPacketAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtp_sntpPacketAction 26
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressNtp_sntpPacketAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtp_sntpPacketAction u26.bits_26
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressNtp_sntpPacketAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressNtp_sntpPacketAction u26.word_26
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressCorrectionFractionalNanosecondTimestampeEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionFractionalNanosecondTimestampeEnable 27
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressCorrectionFractionalNanosecondTimestampeEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionFractionalNanosecondTimestampeEnable u27.bits_27
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressCorrectionFractionalNanosecondTimestampeEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionFractionalNanosecondTimestampeEnable u27.word_27
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressCorrectionClearTimestampEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionClearTimestampEnable 27
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressCorrectionClearTimestampEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionClearTimestampEnable u27.bits_27
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressCorrectionClearTimestampEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionClearTimestampEnable u27.word_27
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressCrcAppendEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCrcAppendEnable 27
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressCrcAppendEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCrcAppendEnable u27.bits_27
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressCrcAppendEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCrcAppendEnable u27.word_27
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressUdpAppendFormat in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpAppendFormat 27
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressUdpAppendFormat in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpAppendFormat u27.bits_27
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressUdpAppendFormat in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpAppendFormat u27.word_27
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressUdpAppendEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpAppendEnable 27
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressUdpAppendEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpAppendEnable u27.bits_27
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressUdpAppendEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpAppendEnable u27.word_27
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressUdpChecksumEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpChecksumEnable 27
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressUdpChecksumEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpChecksumEnable u27.bits_27
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressUdpChecksumEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressUdpChecksumEnable u27.word_27
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketPipelineReset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketPipelineReset 28
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketPipelineReset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketPipelineReset u28.bits_28
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketPipelineReset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketPipelineReset u28.word_28
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketReadyFifoReset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketReadyFifoReset 28
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketReadyFifoReset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketReadyFifoReset u28.bits_28
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketReadyFifoReset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketReadyFifoReset u28.word_28
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketPipelineThreshold in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketPipelineThreshold 29
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketPipelineThreshold in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketPipelineThreshold u29.bits_29
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketPipelineThreshold in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketPipelineThreshold u29.word_29
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketBufferReset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketBufferReset 30
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketBufferReset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketBufferReset u30.bits_30
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketBufferReset in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketBufferReset u30.word_30
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketBufferReadEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketBufferReadEnable 30
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketBufferReadEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketBufferReadEnable u30.bits_30
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketBufferReadEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketBufferReadEnable u30.word_30
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketPause in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketPause 31
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketPause in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketPause u31.bits_31
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketPause in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketPause u31.word_31
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketSizeLimit in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketSizeLimit 31
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketSizeLimit in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketSizeLimit u31.bits_31
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketSizeLimit in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketSizeLimit u31.word_31
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketTimeStampReadEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketTimeStampReadEnable 32
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketTimeStampReadEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketTimeStampReadEnable u32.bits_32
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketTimeStampReadEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketTimeStampReadEnable u32.word_32
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_1TimeStampAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_1TimeStampAction 33
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_1TimeStampAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_1TimeStampAction u33.bits_33
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_1TimeStampAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_1TimeStampAction u33.word_33
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_1PacketAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_1PacketAction 33
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_1PacketAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_1PacketAction u33.bits_33
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_1PacketAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_1PacketAction u33.word_33
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressStackedVlanID in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressStackedVlanID 34
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressStackedVlanID in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressStackedVlanID u34.bits_34
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressStackedVlanID in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressStackedVlanID u34.word_34
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressCorrectionAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionAction 35
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressCorrectionAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionAction u35.bits_35
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressCorrectionAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressCorrectionAction u35.word_35
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampAction 36
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampAction u36.bits_36
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampAction in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressTimeStampAction u36.word_36
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_2MessageType in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2MessageType 37
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_2MessageType in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2MessageType u37.bits_37
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_2MessageType in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2MessageType u37.word_37
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngress_1588Version_2MessageMask in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2MessageMask 38
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngress_1588Version_2MessageMask in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2MessageMask u38.bits_38
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngress_1588Version_2MessageMask in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngress_1588Version_2MessageMask u38.word_38
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketIfgThreshold in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketIfgThreshold 39
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketIfgThreshold in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketIfgThreshold u39.bits_39
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketIfgThreshold in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketIfgThreshold u39.word_39
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressRxMacFifoBase in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressRxMacFifoBase 40
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressRxMacFifoBase in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressRxMacFifoBase u40.bits_40
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressRxMacFifoBase in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressRxMacFifoBase u40.word_40
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressRxMacFifoCorrection in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressRxMacFifoCorrection 40
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressRxMacFifoCorrection in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressRxMacFifoCorrection u40.bits_40
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressRxMacFifoCorrection in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressRxMacFifoCorrection u40.word_40
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressRxMacFifoCorrectionEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressRxMacFifoCorrectionEnable 40
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressRxMacFifoCorrectionEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressRxMacFifoCorrectionEnable u40.bits_40
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressRxMacFifoCorrectionEnable in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressRxMacFifoCorrectionEnable u40.word_40
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressGapFifoBypass in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressGapFifoBypass 40
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressGapFifoBypass in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressGapFifoBypass u40.bits_40
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressGapFifoBypass in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressGapFifoBypass u40.word_40
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketReadyThreshold in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketReadyThreshold 40
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketReadyThreshold in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define bits_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketReadyThreshold u40.bits_40
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketReadyThreshold in AQ_PcsPtpIngressVendorProvisioning_HHD */
#define word_AQ_PcsPtpIngressVendorProvisioning_HHD_ptpIngressPacketReadyThreshold u40.word_40

/*! \brief Base register address of structure AQ_PcsReceiveVendorState_HHD */
#define AQ_PcsReceiveVendorState_HHD_baseRegisterAddress 0xE800
/*! \brief MMD address of structure AQ_PcsReceiveVendorState_HHD */
#define AQ_PcsReceiveVendorState_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsRxCurrentValueOfAuxilliaryBit in AQ_PcsReceiveVendorState_HHD */
#define AQ_PcsReceiveVendorState_HHD_pcsRxCurrentValueOfAuxilliaryBit 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsRxCurrentValueOfAuxilliaryBit in AQ_PcsReceiveVendorState_HHD */
#define bits_AQ_PcsReceiveVendorState_HHD_pcsRxCurrentValueOfAuxilliaryBit u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsRxCurrentValueOfAuxilliaryBit in AQ_PcsReceiveVendorState_HHD */
#define word_AQ_PcsReceiveVendorState_HHD_pcsRxCurrentValueOfAuxilliaryBit u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveReservedVendorState_HHD */
#define AQ_PcsReceiveReservedVendorState_HHD_baseRegisterAddress 0xE808
/*! \brief MMD address of structure AQ_PcsReceiveReservedVendorState_HHD */
#define AQ_PcsReceiveReservedVendorState_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure averageLdpcIterationCount in AQ_PcsReceiveReservedVendorState_HHD */
#define AQ_PcsReceiveReservedVendorState_HHD_averageLdpcIterationCount 0
/*! \brief Preprocessor variable to relate field to bit position in structure averageLdpcIterationCount in AQ_PcsReceiveReservedVendorState_HHD */
#define bits_AQ_PcsReceiveReservedVendorState_HHD_averageLdpcIterationCount u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure averageLdpcIterationCount in AQ_PcsReceiveReservedVendorState_HHD */
#define word_AQ_PcsReceiveReservedVendorState_HHD_averageLdpcIterationCount u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD */
#define AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD_baseRegisterAddress 0xE810
/*! \brief MMD address of structure AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD */
#define AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure crc_8ErrorCounterLSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD */
#define AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD_crc_8ErrorCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure crc_8ErrorCounterLSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD */
#define bits_AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD_crc_8ErrorCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure crc_8ErrorCounterLSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD */
#define word_AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD_crc_8ErrorCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure crc_8ErrorCounterMSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD */
#define AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD_crc_8ErrorCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure crc_8ErrorCounterMSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD */
#define bits_AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD_crc_8ErrorCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure crc_8ErrorCounterMSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD */
#define word_AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD_crc_8ErrorCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD */
#define AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD_baseRegisterAddress 0xE812
/*! \brief MMD address of structure AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD */
#define AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD */
#define AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD__10gbase_tGoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD */
#define bits_AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD__10gbase_tGoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD */
#define word_AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD__10gbase_tGoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD */
#define AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD__10gbase_tGoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD */
#define bits_AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD__10gbase_tGoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD */
#define word_AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD__10gbase_tGoodFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD */
#define AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD_baseRegisterAddress 0xE814
/*! \brief MMD address of structure AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD */
#define AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD */
#define AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD__10gbase_tErrorFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD */
#define bits_AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD__10gbase_tErrorFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD */
#define word_AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD__10gbase_tErrorFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD */
#define AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD__10gbase_tErrorFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD */
#define bits_AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD__10gbase_tErrorFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD */
#define word_AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD__10gbase_tErrorFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD */
#define AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD_baseRegisterAddress 0xE820
/*! \brief MMD address of structure AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD */
#define AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure uncorrectedFrameCounterLSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD */
#define AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD_uncorrectedFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure uncorrectedFrameCounterLSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD */
#define bits_AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD_uncorrectedFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure uncorrectedFrameCounterLSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD */
#define word_AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD_uncorrectedFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure uncorrectedFrameCounterMSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD */
#define AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD_uncorrectedFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure uncorrectedFrameCounterMSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD */
#define bits_AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD_uncorrectedFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure uncorrectedFrameCounterMSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD */
#define word_AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD_uncorrectedFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD_baseRegisterAddress 0xE840
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_1IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD_correctedFrames_1IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_1IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD_correctedFrames_1IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_1IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD */
#define word_AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD_correctedFrames_1IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_1IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD_correctedFrames_1IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_1IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD_correctedFrames_1IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_1IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD */
#define word_AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD_correctedFrames_1IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD_baseRegisterAddress 0xE842
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_2IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD_correctedFrames_2IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_2IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD_correctedFrames_2IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_2IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD */
#define word_AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD_correctedFrames_2IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_2IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD_correctedFrames_2IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_2IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD_correctedFrames_2IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_2IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD */
#define word_AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD_correctedFrames_2IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD_baseRegisterAddress 0xE844
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_3IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD_correctedFrames_3IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_3IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD_correctedFrames_3IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_3IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD */
#define word_AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD_correctedFrames_3IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_3IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD_correctedFrames_3IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_3IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD_correctedFrames_3IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_3IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD */
#define word_AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD_correctedFrames_3IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD_baseRegisterAddress 0xE846
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_4IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD_correctedFrames_4IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_4IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD_correctedFrames_4IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_4IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD */
#define word_AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD_correctedFrames_4IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_4IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD_correctedFrames_4IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_4IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD_correctedFrames_4IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_4IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD */
#define word_AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD_correctedFrames_4IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD_baseRegisterAddress 0xE848
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_5IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD_correctedFrames_5IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_5IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD_correctedFrames_5IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_5IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD */
#define word_AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD_correctedFrames_5IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_5IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD_correctedFrames_5IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_5IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD_correctedFrames_5IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_5IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD */
#define word_AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD_correctedFrames_5IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_HHD_baseRegisterAddress 0xE850
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_6IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_HHD_correctedFrames_6IterationCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_6IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_HHD */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_HHD_correctedFrames_6IterationCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_6IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_HHD */
#define word_AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_HHD_correctedFrames_6IterationCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_HHD_baseRegisterAddress 0xE851
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_7IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_HHD_correctedFrames_7IterationCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_7IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_HHD */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_HHD_correctedFrames_7IterationCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_7IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_HHD */
#define word_AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_HHD_correctedFrames_7IterationCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_HHD_baseRegisterAddress 0xE852
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_8IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_HHD */
#define AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_HHD_correctedFrames_8IterationCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_8IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_HHD */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_HHD_correctedFrames_8IterationCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_8IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_HHD */
#define word_AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_HHD_correctedFrames_8IterationCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveXfi0VendorState_HHD */
#define AQ_PcsReceiveXfi0VendorState_HHD_baseRegisterAddress 0xE860
/*! \brief MMD address of structure AQ_PcsReceiveXfi0VendorState_HHD */
#define AQ_PcsReceiveXfi0VendorState_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi0GoodFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_HHD */
#define AQ_PcsReceiveXfi0VendorState_HHD_xfi0GoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0GoodFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_HHD */
#define bits_AQ_PcsReceiveXfi0VendorState_HHD_xfi0GoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi0GoodFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_HHD */
#define word_AQ_PcsReceiveXfi0VendorState_HHD_xfi0GoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi0GoodFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_HHD */
#define AQ_PcsReceiveXfi0VendorState_HHD_xfi0GoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0GoodFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_HHD */
#define bits_AQ_PcsReceiveXfi0VendorState_HHD_xfi0GoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0GoodFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_HHD */
#define word_AQ_PcsReceiveXfi0VendorState_HHD_xfi0GoodFrameCounterMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BadFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_HHD */
#define AQ_PcsReceiveXfi0VendorState_HHD_xfi0BadFrameCounterLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BadFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_HHD */
#define bits_AQ_PcsReceiveXfi0VendorState_HHD_xfi0BadFrameCounterLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BadFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_HHD */
#define word_AQ_PcsReceiveXfi0VendorState_HHD_xfi0BadFrameCounterLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BadFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_HHD */
#define AQ_PcsReceiveXfi0VendorState_HHD_xfi0BadFrameCounterMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BadFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_HHD */
#define bits_AQ_PcsReceiveXfi0VendorState_HHD_xfi0BadFrameCounterMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BadFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_HHD */
#define word_AQ_PcsReceiveXfi0VendorState_HHD_xfi0BadFrameCounterMSW u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BerCounter in AQ_PcsReceiveXfi0VendorState_HHD */
#define AQ_PcsReceiveXfi0VendorState_HHD_xfi0BerCounter 4
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BerCounter in AQ_PcsReceiveXfi0VendorState_HHD */
#define bits_AQ_PcsReceiveXfi0VendorState_HHD_xfi0BerCounter u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BerCounter in AQ_PcsReceiveXfi0VendorState_HHD */
#define word_AQ_PcsReceiveXfi0VendorState_HHD_xfi0BerCounter u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure xfi0ErroredBlockCounter in AQ_PcsReceiveXfi0VendorState_HHD */
#define AQ_PcsReceiveXfi0VendorState_HHD_xfi0ErroredBlockCounter 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0ErroredBlockCounter in AQ_PcsReceiveXfi0VendorState_HHD */
#define bits_AQ_PcsReceiveXfi0VendorState_HHD_xfi0ErroredBlockCounter u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi0ErroredBlockCounter in AQ_PcsReceiveXfi0VendorState_HHD */
#define word_AQ_PcsReceiveXfi0VendorState_HHD_xfi0ErroredBlockCounter u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPatternErrorCounter in AQ_PcsReceiveXfi0VendorState_HHD */
#define AQ_PcsReceiveXfi0VendorState_HHD_xfi0TestPatternErrorCounter 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPatternErrorCounter in AQ_PcsReceiveXfi0VendorState_HHD */
#define bits_AQ_PcsReceiveXfi0VendorState_HHD_xfi0TestPatternErrorCounter u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPatternErrorCounter in AQ_PcsReceiveXfi0VendorState_HHD */
#define word_AQ_PcsReceiveXfi0VendorState_HHD_xfi0TestPatternErrorCounter u6.word_6

/*! \brief Base register address of structure AQ_PcsReceiveXfi1VendorState_HHD */
#define AQ_PcsReceiveXfi1VendorState_HHD_baseRegisterAddress 0xE870
/*! \brief MMD address of structure AQ_PcsReceiveXfi1VendorState_HHD */
#define AQ_PcsReceiveXfi1VendorState_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi1GoodFrameCounterLSW in AQ_PcsReceiveXfi1VendorState_HHD */
#define AQ_PcsReceiveXfi1VendorState_HHD_xfi1GoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1GoodFrameCounterLSW in AQ_PcsReceiveXfi1VendorState_HHD */
#define bits_AQ_PcsReceiveXfi1VendorState_HHD_xfi1GoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi1GoodFrameCounterLSW in AQ_PcsReceiveXfi1VendorState_HHD */
#define word_AQ_PcsReceiveXfi1VendorState_HHD_xfi1GoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi1GoodFrameCounterMSW in AQ_PcsReceiveXfi1VendorState_HHD */
#define AQ_PcsReceiveXfi1VendorState_HHD_xfi1GoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1GoodFrameCounterMSW in AQ_PcsReceiveXfi1VendorState_HHD */
#define bits_AQ_PcsReceiveXfi1VendorState_HHD_xfi1GoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1GoodFrameCounterMSW in AQ_PcsReceiveXfi1VendorState_HHD */
#define word_AQ_PcsReceiveXfi1VendorState_HHD_xfi1GoodFrameCounterMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BadFrameCounterLSW in AQ_PcsReceiveXfi1VendorState_HHD */
#define AQ_PcsReceiveXfi1VendorState_HHD_xfi1BadFrameCounterLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BadFrameCounterLSW in AQ_PcsReceiveXfi1VendorState_HHD */
#define bits_AQ_PcsReceiveXfi1VendorState_HHD_xfi1BadFrameCounterLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BadFrameCounterLSW in AQ_PcsReceiveXfi1VendorState_HHD */
#define word_AQ_PcsReceiveXfi1VendorState_HHD_xfi1BadFrameCounterLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BadFrameCounterMSW in AQ_PcsReceiveXfi1VendorState_HHD */
#define AQ_PcsReceiveXfi1VendorState_HHD_xfi1BadFrameCounterMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BadFrameCounterMSW in AQ_PcsReceiveXfi1VendorState_HHD */
#define bits_AQ_PcsReceiveXfi1VendorState_HHD_xfi1BadFrameCounterMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BadFrameCounterMSW in AQ_PcsReceiveXfi1VendorState_HHD */
#define word_AQ_PcsReceiveXfi1VendorState_HHD_xfi1BadFrameCounterMSW u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BerCounter in AQ_PcsReceiveXfi1VendorState_HHD */
#define AQ_PcsReceiveXfi1VendorState_HHD_xfi1BerCounter 4
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BerCounter in AQ_PcsReceiveXfi1VendorState_HHD */
#define bits_AQ_PcsReceiveXfi1VendorState_HHD_xfi1BerCounter u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BerCounter in AQ_PcsReceiveXfi1VendorState_HHD */
#define word_AQ_PcsReceiveXfi1VendorState_HHD_xfi1BerCounter u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure xfi1ErroredBlockCounter in AQ_PcsReceiveXfi1VendorState_HHD */
#define AQ_PcsReceiveXfi1VendorState_HHD_xfi1ErroredBlockCounter 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1ErroredBlockCounter in AQ_PcsReceiveXfi1VendorState_HHD */
#define bits_AQ_PcsReceiveXfi1VendorState_HHD_xfi1ErroredBlockCounter u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi1ErroredBlockCounter in AQ_PcsReceiveXfi1VendorState_HHD */
#define word_AQ_PcsReceiveXfi1VendorState_HHD_xfi1ErroredBlockCounter u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestPatternErrorCounter in AQ_PcsReceiveXfi1VendorState_HHD */
#define AQ_PcsReceiveXfi1VendorState_HHD_xfi1TestPatternErrorCounter 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestPatternErrorCounter in AQ_PcsReceiveXfi1VendorState_HHD */
#define bits_AQ_PcsReceiveXfi1VendorState_HHD_xfi1TestPatternErrorCounter u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestPatternErrorCounter in AQ_PcsReceiveXfi1VendorState_HHD */
#define word_AQ_PcsReceiveXfi1VendorState_HHD_xfi1TestPatternErrorCounter u6.word_6

/*! \brief Base register address of structure AQ_PcsUsx0ReceiveCrcErrorCounterRegister_HHD */
#define AQ_PcsUsx0ReceiveCrcErrorCounterRegister_HHD_baseRegisterAddress 0xE8D0
/*! \brief MMD address of structure AQ_PcsUsx0ReceiveCrcErrorCounterRegister_HHD */
#define AQ_PcsUsx0ReceiveCrcErrorCounterRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0HeaderCrcErrorCounter in AQ_PcsUsx0ReceiveCrcErrorCounterRegister_HHD */
#define AQ_PcsUsx0ReceiveCrcErrorCounterRegister_HHD_usx0HeaderCrcErrorCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0HeaderCrcErrorCounter in AQ_PcsUsx0ReceiveCrcErrorCounterRegister_HHD */
#define bits_AQ_PcsUsx0ReceiveCrcErrorCounterRegister_HHD_usx0HeaderCrcErrorCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0HeaderCrcErrorCounter in AQ_PcsUsx0ReceiveCrcErrorCounterRegister_HHD */
#define word_AQ_PcsUsx0ReceiveCrcErrorCounterRegister_HHD_usx0HeaderCrcErrorCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0ReceivePacketInfoMessage_0_HHD */
#define AQ_PcsUsx0ReceivePacketInfoMessage_0_HHD_baseRegisterAddress 0xE8D1
/*! \brief MMD address of structure AQ_PcsUsx0ReceivePacketInfoMessage_0_HHD */
#define AQ_PcsUsx0ReceivePacketInfoMessage_0_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0PacketInformationMessageToBeInjected_15_0 in AQ_PcsUsx0ReceivePacketInfoMessage_0_HHD */
#define AQ_PcsUsx0ReceivePacketInfoMessage_0_HHD_usx0PacketInformationMessageToBeInjected_15_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0PacketInformationMessageToBeInjected_15_0 in AQ_PcsUsx0ReceivePacketInfoMessage_0_HHD */
#define bits_AQ_PcsUsx0ReceivePacketInfoMessage_0_HHD_usx0PacketInformationMessageToBeInjected_15_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0PacketInformationMessageToBeInjected_15_0 in AQ_PcsUsx0ReceivePacketInfoMessage_0_HHD */
#define word_AQ_PcsUsx0ReceivePacketInfoMessage_0_HHD_usx0PacketInformationMessageToBeInjected_15_0 u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0ReceivePacketInfoMessage_1_HHD */
#define AQ_PcsUsx0ReceivePacketInfoMessage_1_HHD_baseRegisterAddress 0xE8D2
/*! \brief MMD address of structure AQ_PcsUsx0ReceivePacketInfoMessage_1_HHD */
#define AQ_PcsUsx0ReceivePacketInfoMessage_1_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0PacketInformationMessageToBeInjected_31_16 in AQ_PcsUsx0ReceivePacketInfoMessage_1_HHD */
#define AQ_PcsUsx0ReceivePacketInfoMessage_1_HHD_usx0PacketInformationMessageToBeInjected_31_16 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0PacketInformationMessageToBeInjected_31_16 in AQ_PcsUsx0ReceivePacketInfoMessage_1_HHD */
#define bits_AQ_PcsUsx0ReceivePacketInfoMessage_1_HHD_usx0PacketInformationMessageToBeInjected_31_16 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0PacketInformationMessageToBeInjected_31_16 in AQ_PcsUsx0ReceivePacketInfoMessage_1_HHD */
#define word_AQ_PcsUsx0ReceivePacketInfoMessage_1_HHD_usx0PacketInformationMessageToBeInjected_31_16 u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0ReceivePacketInfoMessage_2_HHD */
#define AQ_PcsUsx0ReceivePacketInfoMessage_2_HHD_baseRegisterAddress 0xE8D3
/*! \brief MMD address of structure AQ_PcsUsx0ReceivePacketInfoMessage_2_HHD */
#define AQ_PcsUsx0ReceivePacketInfoMessage_2_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0PacketInformationMessageToBeInjected_47_32 in AQ_PcsUsx0ReceivePacketInfoMessage_2_HHD */
#define AQ_PcsUsx0ReceivePacketInfoMessage_2_HHD_usx0PacketInformationMessageToBeInjected_47_32 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0PacketInformationMessageToBeInjected_47_32 in AQ_PcsUsx0ReceivePacketInfoMessage_2_HHD */
#define bits_AQ_PcsUsx0ReceivePacketInfoMessage_2_HHD_usx0PacketInformationMessageToBeInjected_47_32 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0PacketInformationMessageToBeInjected_47_32 in AQ_PcsUsx0ReceivePacketInfoMessage_2_HHD */
#define word_AQ_PcsUsx0ReceivePacketInfoMessage_2_HHD_usx0PacketInformationMessageToBeInjected_47_32 u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0UnidataAndSmStatusRegister_HHD */
#define AQ_PcsUsx0UnidataAndSmStatusRegister_HHD_baseRegisterAddress 0xE8D4
/*! \brief MMD address of structure AQ_PcsUsx0UnidataAndSmStatusRegister_HHD */
#define AQ_PcsUsx0UnidataAndSmStatusRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxUnidataIndication in AQ_PcsUsx0UnidataAndSmStatusRegister_HHD */
#define AQ_PcsUsx0UnidataAndSmStatusRegister_HHD_usx0RxUnidataIndication 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxUnidataIndication in AQ_PcsUsx0UnidataAndSmStatusRegister_HHD */
#define bits_AQ_PcsUsx0UnidataAndSmStatusRegister_HHD_usx0RxUnidataIndication u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxUnidataIndication in AQ_PcsUsx0UnidataAndSmStatusRegister_HHD */
#define word_AQ_PcsUsx0UnidataAndSmStatusRegister_HHD_usx0RxUnidataIndication u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0SanStateMachineCurrentState in AQ_PcsUsx0UnidataAndSmStatusRegister_HHD */
#define AQ_PcsUsx0UnidataAndSmStatusRegister_HHD_usx0SanStateMachineCurrentState 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0SanStateMachineCurrentState in AQ_PcsUsx0UnidataAndSmStatusRegister_HHD */
#define bits_AQ_PcsUsx0UnidataAndSmStatusRegister_HHD_usx0SanStateMachineCurrentState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0SanStateMachineCurrentState in AQ_PcsUsx0UnidataAndSmStatusRegister_HHD */
#define word_AQ_PcsUsx0UnidataAndSmStatusRegister_HHD_usx0SanStateMachineCurrentState u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0ReceiveStatusRegister_HHD */
#define AQ_PcsUsx0ReceiveStatusRegister_HHD_baseRegisterAddress 0xE8D5
/*! \brief MMD address of structure AQ_PcsUsx0ReceiveStatusRegister_HHD */
#define AQ_PcsUsx0ReceiveStatusRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxRsvdStatus in AQ_PcsUsx0ReceiveStatusRegister_HHD */
#define AQ_PcsUsx0ReceiveStatusRegister_HHD_usx0RxRsvdStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxRsvdStatus in AQ_PcsUsx0ReceiveStatusRegister_HHD */
#define bits_AQ_PcsUsx0ReceiveStatusRegister_HHD_usx0RxRsvdStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxRsvdStatus in AQ_PcsUsx0ReceiveStatusRegister_HHD */
#define word_AQ_PcsUsx0ReceiveStatusRegister_HHD_usx0RxRsvdStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0XgmiiToGmiiConversionStatus in AQ_PcsUsx0ReceiveStatusRegister_HHD */
#define AQ_PcsUsx0ReceiveStatusRegister_HHD_usx0XgmiiToGmiiConversionStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0XgmiiToGmiiConversionStatus in AQ_PcsUsx0ReceiveStatusRegister_HHD */
#define bits_AQ_PcsUsx0ReceiveStatusRegister_HHD_usx0XgmiiToGmiiConversionStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0XgmiiToGmiiConversionStatus in AQ_PcsUsx0ReceiveStatusRegister_HHD */
#define word_AQ_PcsUsx0ReceiveStatusRegister_HHD_usx0XgmiiToGmiiConversionStatus u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx0LinkPartnerAdvRegister_HHD_baseRegisterAddress 0xE8D6
/*! \brief MMD address of structure AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx0LinkPartnerAdvRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkPartnerAdvertisementStatus in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkPartnerAdvertisementStatus in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkPartnerAdvertisementStatus in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedUsx0LinkPartnerAdvertisement_0 in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx0LinkPartnerAdvRegister_HHD_reservedUsx0LinkPartnerAdvertisement_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedUsx0LinkPartnerAdvertisement_0 in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_reservedUsx0LinkPartnerAdvertisement_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedUsx0LinkPartnerAdvertisement_0 in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_reservedUsx0LinkPartnerAdvertisement_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkPartnerAdvertisementDuplex in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementDuplex 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkPartnerAdvertisementDuplex in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementDuplex u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkPartnerAdvertisementDuplex in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementDuplex u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkPartnerAdvertisementSpeed in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementSpeed 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkPartnerAdvertisementSpeed in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementSpeed u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkPartnerAdvertisementSpeed in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementSpeed u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkPartnerAdvertisementEeeCapability in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementEeeCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkPartnerAdvertisementEeeCapability in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementEeeCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkPartnerAdvertisementEeeCapability in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementEeeCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkPartnerAdvertisementEeeClockStopCapability in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementEeeClockStopCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkPartnerAdvertisementEeeClockStopCapability in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementEeeClockStopCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkPartnerAdvertisementEeeClockStopCapability in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementEeeClockStopCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedUsx0LinkPartnerAdvertisement_1 in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx0LinkPartnerAdvRegister_HHD_reservedUsx0LinkPartnerAdvertisement_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedUsx0LinkPartnerAdvertisement_1 in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_reservedUsx0LinkPartnerAdvertisement_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedUsx0LinkPartnerAdvertisement_1 in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_reservedUsx0LinkPartnerAdvertisement_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkPartnerAdvertisementMode in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkPartnerAdvertisementMode in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkPartnerAdvertisementMode in AQ_PcsUsx0LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx0LinkPartnerAdvRegister_HHD_usx0LinkPartnerAdvertisementMode u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1ReceiveCrcErrorCounterRegister_HHD */
#define AQ_PcsUsx1ReceiveCrcErrorCounterRegister_HHD_baseRegisterAddress 0xE8E0
/*! \brief MMD address of structure AQ_PcsUsx1ReceiveCrcErrorCounterRegister_HHD */
#define AQ_PcsUsx1ReceiveCrcErrorCounterRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1HeaderCrcErrorCounter in AQ_PcsUsx1ReceiveCrcErrorCounterRegister_HHD */
#define AQ_PcsUsx1ReceiveCrcErrorCounterRegister_HHD_usx1HeaderCrcErrorCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1HeaderCrcErrorCounter in AQ_PcsUsx1ReceiveCrcErrorCounterRegister_HHD */
#define bits_AQ_PcsUsx1ReceiveCrcErrorCounterRegister_HHD_usx1HeaderCrcErrorCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1HeaderCrcErrorCounter in AQ_PcsUsx1ReceiveCrcErrorCounterRegister_HHD */
#define word_AQ_PcsUsx1ReceiveCrcErrorCounterRegister_HHD_usx1HeaderCrcErrorCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1ReceivePacketInfoMessage_0_HHD */
#define AQ_PcsUsx1ReceivePacketInfoMessage_0_HHD_baseRegisterAddress 0xE8E1
/*! \brief MMD address of structure AQ_PcsUsx1ReceivePacketInfoMessage_0_HHD */
#define AQ_PcsUsx1ReceivePacketInfoMessage_0_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1PacketInformationMessageToBeInjected_15_0 in AQ_PcsUsx1ReceivePacketInfoMessage_0_HHD */
#define AQ_PcsUsx1ReceivePacketInfoMessage_0_HHD_usx1PacketInformationMessageToBeInjected_15_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1PacketInformationMessageToBeInjected_15_0 in AQ_PcsUsx1ReceivePacketInfoMessage_0_HHD */
#define bits_AQ_PcsUsx1ReceivePacketInfoMessage_0_HHD_usx1PacketInformationMessageToBeInjected_15_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1PacketInformationMessageToBeInjected_15_0 in AQ_PcsUsx1ReceivePacketInfoMessage_0_HHD */
#define word_AQ_PcsUsx1ReceivePacketInfoMessage_0_HHD_usx1PacketInformationMessageToBeInjected_15_0 u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1ReceivePacketInfoMessage_1_HHD */
#define AQ_PcsUsx1ReceivePacketInfoMessage_1_HHD_baseRegisterAddress 0xE8E2
/*! \brief MMD address of structure AQ_PcsUsx1ReceivePacketInfoMessage_1_HHD */
#define AQ_PcsUsx1ReceivePacketInfoMessage_1_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1PacketInformationMessageToBeInjected_31_16 in AQ_PcsUsx1ReceivePacketInfoMessage_1_HHD */
#define AQ_PcsUsx1ReceivePacketInfoMessage_1_HHD_usx1PacketInformationMessageToBeInjected_31_16 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1PacketInformationMessageToBeInjected_31_16 in AQ_PcsUsx1ReceivePacketInfoMessage_1_HHD */
#define bits_AQ_PcsUsx1ReceivePacketInfoMessage_1_HHD_usx1PacketInformationMessageToBeInjected_31_16 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1PacketInformationMessageToBeInjected_31_16 in AQ_PcsUsx1ReceivePacketInfoMessage_1_HHD */
#define word_AQ_PcsUsx1ReceivePacketInfoMessage_1_HHD_usx1PacketInformationMessageToBeInjected_31_16 u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1ReceivePacketInfoMessage_2_HHD */
#define AQ_PcsUsx1ReceivePacketInfoMessage_2_HHD_baseRegisterAddress 0xE8E3
/*! \brief MMD address of structure AQ_PcsUsx1ReceivePacketInfoMessage_2_HHD */
#define AQ_PcsUsx1ReceivePacketInfoMessage_2_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1PacketInformationMessageToBeInjected_47_32 in AQ_PcsUsx1ReceivePacketInfoMessage_2_HHD */
#define AQ_PcsUsx1ReceivePacketInfoMessage_2_HHD_usx1PacketInformationMessageToBeInjected_47_32 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1PacketInformationMessageToBeInjected_47_32 in AQ_PcsUsx1ReceivePacketInfoMessage_2_HHD */
#define bits_AQ_PcsUsx1ReceivePacketInfoMessage_2_HHD_usx1PacketInformationMessageToBeInjected_47_32 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1PacketInformationMessageToBeInjected_47_32 in AQ_PcsUsx1ReceivePacketInfoMessage_2_HHD */
#define word_AQ_PcsUsx1ReceivePacketInfoMessage_2_HHD_usx1PacketInformationMessageToBeInjected_47_32 u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1UnidataAndSmStatusRegister_HHD */
#define AQ_PcsUsx1UnidataAndSmStatusRegister_HHD_baseRegisterAddress 0xE8E4
/*! \brief MMD address of structure AQ_PcsUsx1UnidataAndSmStatusRegister_HHD */
#define AQ_PcsUsx1UnidataAndSmStatusRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxUnidataIndication in AQ_PcsUsx1UnidataAndSmStatusRegister_HHD */
#define AQ_PcsUsx1UnidataAndSmStatusRegister_HHD_usx1RxUnidataIndication 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxUnidataIndication in AQ_PcsUsx1UnidataAndSmStatusRegister_HHD */
#define bits_AQ_PcsUsx1UnidataAndSmStatusRegister_HHD_usx1RxUnidataIndication u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxUnidataIndication in AQ_PcsUsx1UnidataAndSmStatusRegister_HHD */
#define word_AQ_PcsUsx1UnidataAndSmStatusRegister_HHD_usx1RxUnidataIndication u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1SanStateMachineCurrentState in AQ_PcsUsx1UnidataAndSmStatusRegister_HHD */
#define AQ_PcsUsx1UnidataAndSmStatusRegister_HHD_usx1SanStateMachineCurrentState 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1SanStateMachineCurrentState in AQ_PcsUsx1UnidataAndSmStatusRegister_HHD */
#define bits_AQ_PcsUsx1UnidataAndSmStatusRegister_HHD_usx1SanStateMachineCurrentState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1SanStateMachineCurrentState in AQ_PcsUsx1UnidataAndSmStatusRegister_HHD */
#define word_AQ_PcsUsx1UnidataAndSmStatusRegister_HHD_usx1SanStateMachineCurrentState u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1ReceiveStatusRegister_HHD */
#define AQ_PcsUsx1ReceiveStatusRegister_HHD_baseRegisterAddress 0xE8E5
/*! \brief MMD address of structure AQ_PcsUsx1ReceiveStatusRegister_HHD */
#define AQ_PcsUsx1ReceiveStatusRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxRsvdStatus in AQ_PcsUsx1ReceiveStatusRegister_HHD */
#define AQ_PcsUsx1ReceiveStatusRegister_HHD_usx1RxRsvdStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxRsvdStatus in AQ_PcsUsx1ReceiveStatusRegister_HHD */
#define bits_AQ_PcsUsx1ReceiveStatusRegister_HHD_usx1RxRsvdStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxRsvdStatus in AQ_PcsUsx1ReceiveStatusRegister_HHD */
#define word_AQ_PcsUsx1ReceiveStatusRegister_HHD_usx1RxRsvdStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1XgmiiToGmiiConversionStatus in AQ_PcsUsx1ReceiveStatusRegister_HHD */
#define AQ_PcsUsx1ReceiveStatusRegister_HHD_usx1XgmiiToGmiiConversionStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1XgmiiToGmiiConversionStatus in AQ_PcsUsx1ReceiveStatusRegister_HHD */
#define bits_AQ_PcsUsx1ReceiveStatusRegister_HHD_usx1XgmiiToGmiiConversionStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1XgmiiToGmiiConversionStatus in AQ_PcsUsx1ReceiveStatusRegister_HHD */
#define word_AQ_PcsUsx1ReceiveStatusRegister_HHD_usx1XgmiiToGmiiConversionStatus u0.word_0

/*! \brief Base register address of structure AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx1LinkPartnerAdvRegister_HHD_baseRegisterAddress 0xE8E6
/*! \brief MMD address of structure AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx1LinkPartnerAdvRegister_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkPartnerAdvertisementStatus in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkPartnerAdvertisementStatus in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkPartnerAdvertisementStatus in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedUsx1LinkPartnerAdvertisement_0 in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx1LinkPartnerAdvRegister_HHD_reservedUsx1LinkPartnerAdvertisement_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedUsx1LinkPartnerAdvertisement_0 in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_reservedUsx1LinkPartnerAdvertisement_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedUsx1LinkPartnerAdvertisement_0 in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_reservedUsx1LinkPartnerAdvertisement_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkPartnerAdvertisementDuplex in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementDuplex 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkPartnerAdvertisementDuplex in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementDuplex u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkPartnerAdvertisementDuplex in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementDuplex u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkPartnerAdvertisementSpeed in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementSpeed 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkPartnerAdvertisementSpeed in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementSpeed u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkPartnerAdvertisementSpeed in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementSpeed u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkPartnerAdvertisementEeeCapability in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementEeeCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkPartnerAdvertisementEeeCapability in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementEeeCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkPartnerAdvertisementEeeCapability in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementEeeCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkPartnerAdvertisementEeeClockStopCapability in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementEeeClockStopCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkPartnerAdvertisementEeeClockStopCapability in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementEeeClockStopCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkPartnerAdvertisementEeeClockStopCapability in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementEeeClockStopCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedUsx1LinkPartnerAdvertisement_1 in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx1LinkPartnerAdvRegister_HHD_reservedUsx1LinkPartnerAdvertisement_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedUsx1LinkPartnerAdvertisement_1 in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_reservedUsx1LinkPartnerAdvertisement_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedUsx1LinkPartnerAdvertisement_1 in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_reservedUsx1LinkPartnerAdvertisement_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkPartnerAdvertisementMode in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkPartnerAdvertisementMode in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define bits_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkPartnerAdvertisementMode in AQ_PcsUsx1LinkPartnerAdvRegister_HHD */
#define word_AQ_PcsUsx1LinkPartnerAdvRegister_HHD_usx1LinkPartnerAdvertisementMode u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_baseRegisterAddress 0xEC00
/*! \brief MMD address of structure AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure crcError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_crcError 0
/*! \brief Preprocessor variable to relate field to bit position in structure crcError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_crcError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure crcError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_crcError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldpcDecodeFailure in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ldpcDecodeFailure 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldpcDecodeFailure in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ldpcDecodeFailure u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldpcDecodeFailure in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ldpcDecodeFailure u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure localFaultDetect in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_localFaultDetect 0
/*! \brief Preprocessor variable to relate field to bit position in structure localFaultDetect in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_localFaultDetect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure localFaultDetect in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_localFaultDetect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lofDetect in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_lofDetect 0
/*! \brief Preprocessor variable to relate field to bit position in structure lofDetect in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_lofDetect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lofDetect in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_lofDetect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _40gBipLock in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD__40gBipLock 0
/*! \brief Preprocessor variable to relate field to bit position in structure _40gBipLock in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD__40gBipLock u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _40gBipLock in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD__40gBipLock u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure invalid_65bBlock in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_invalid_65bBlock 0
/*! \brief Preprocessor variable to relate field to bit position in structure invalid_65bBlock in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_invalid_65bBlock u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure invalid_65bBlock in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_invalid_65bBlock u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiActiveOff in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiActiveOff 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiActiveOff in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiActiveOff u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiActiveOff in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiActiveOff u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiActiveOn in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiActiveOn 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiActiveOn in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiActiveOn u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiActiveOn in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiActiveOn u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldpcConsecutiveErroredFrameExceeded in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ldpcConsecutiveErroredFrameExceeded 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldpcConsecutiveErroredFrameExceeded in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ldpcConsecutiveErroredFrameExceeded u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldpcConsecutiveErroredFrameExceeded in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ldpcConsecutiveErroredFrameExceeded u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiAlert in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiAlert 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiAlert in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiAlert u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiAlert in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiAlert u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiReceivedLatchedLow in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiReceivedLatchedLow 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiReceivedLatchedLow in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiReceivedLatchedLow u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiReceivedLatchedLow in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiReceivedLatchedLow u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiReceivedLatchedHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiReceivedLatchedHigh 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiReceivedLatchedHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiReceivedLatchedHigh u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiReceivedLatchedHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_eeeRxLpiReceivedLatchedHigh u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure changeInAuxilliaryBit in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_changeInAuxilliaryBit 0
/*! \brief Preprocessor variable to relate field to bit position in structure changeInAuxilliaryBit in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_changeInAuxilliaryBit u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure changeInAuxilliaryBit in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_changeInAuxilliaryBit u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi1Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_xfi1Invalid_66bCharacterReceived 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_xfi1Invalid_66bCharacterReceived u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi1Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_xfi1Invalid_66bCharacterReceived u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi0Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_xfi0Invalid_66bCharacterReceived 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_xfi0Invalid_66bCharacterReceived u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi0Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_xfi0Invalid_66bCharacterReceived u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi1ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_xfi1ReceiveLinkStatusLatchHigh 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_xfi1ReceiveLinkStatusLatchHigh u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_xfi1ReceiveLinkStatusLatchHigh u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi1HighBerStatus in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_xfi1HighBerStatus 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1HighBerStatus in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_xfi1HighBerStatus u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1HighBerStatus in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_xfi1HighBerStatus u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BlockLockStatus in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_xfi1BlockLockStatus 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BlockLockStatus in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_xfi1BlockLockStatus u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BlockLockStatus in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_xfi1BlockLockStatus u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_xfi0ReceiveLinkStatusLatchHigh 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_xfi0ReceiveLinkStatusLatchHigh u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_xfi0ReceiveLinkStatusLatchHigh u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0HighBerStatus in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_xfi0HighBerStatus 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0HighBerStatus in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_xfi0HighBerStatus u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0HighBerStatus in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_xfi0HighBerStatus u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BlockLockStatus in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_xfi0BlockLockStatus 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BlockLockStatus in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_xfi0BlockLockStatus u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BlockLockStatus in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_xfi0BlockLockStatus u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketReadyFifoError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketReadyFifoError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketReadyFifoError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketReadyFifoError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketReadyFifoError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketReadyFifoError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketReadyFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketReadyFifoParityError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketReadyFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketReadyFifoParityError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketReadyFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketReadyFifoParityError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketRemoveError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketRemoveError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketRemoveError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketRemoveError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketRemoveError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketRemoveError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketReceived in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketReceived 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketReceived in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketReceived u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketReceived in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketReceived u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketPipelineFifoError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketPipelineFifoError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketPipelineFifoError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketPipelineFifoError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketPipelineFifoError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketPipelineFifoError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketPipelineParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketPipelineParityError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketPipelineParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketPipelineParityError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketPipelineParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketPipelineParityError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampBufferParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ptpIngressTimeStampBufferParityError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampBufferParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressTimeStampBufferParityError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampBufferParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressTimeStampBufferParityError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketBufferParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketBufferParityError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketBufferParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketBufferParityError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketBufferParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketBufferParityError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketCorrectionFieldError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketCorrectionFieldError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketCorrectionFieldError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketCorrectionFieldError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketCorrectionFieldError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketCorrectionFieldError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketBufferOverflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketBufferOverflowError 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketBufferOverflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketBufferOverflowError u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketBufferOverflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketBufferOverflowError u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressTimeStampReady in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ptpIngressTimeStampReady 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressTimeStampReady in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressTimeStampReady u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressTimeStampReady in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressTimeStampReady u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ptpIngressPacketReady in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketReady 9
/*! \brief Preprocessor variable to relate field to bit position in structure ptpIngressPacketReady in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketReady u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ptpIngressPacketReady in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_ptpIngressPacketReady u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxHeaderCrcError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0RxHeaderCrcError 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxHeaderCrcError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0RxHeaderCrcError u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxHeaderCrcError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0RxHeaderCrcError u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxUsxgmiiLocalFault in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0RxUsxgmiiLocalFault 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxUsxgmiiLocalFault in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0RxUsxgmiiLocalFault u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxUsxgmiiLocalFault in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0RxUsxgmiiLocalFault u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkFifoOverflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0LinkFifoOverflowError 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkFifoOverflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0LinkFifoOverflowError u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkFifoOverflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0LinkFifoOverflowError u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkFifoUnderflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0LinkFifoUnderflowError 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkFifoUnderflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0LinkFifoUnderflowError u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkFifoUnderflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0LinkFifoUnderflowError u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0LinkFifoParityError 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0LinkFifoParityError u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0LinkFifoParityError u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxPacketInfoMessage in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0RxPacketInfoMessage 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxPacketInfoMessage in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0RxPacketInfoMessage u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxPacketInfoMessage in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0RxPacketInfoMessage u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacRxFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0MacRxFifoParityError 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacRxFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0MacRxFifoParityError u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacRxFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0MacRxFifoParityError u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacRxFifoOverflowErr in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0MacRxFifoOverflowErr 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacRxFifoOverflowErr in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0MacRxFifoOverflowErr u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacRxFifoOverflowErr in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0MacRxFifoOverflowErr u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacRxFifoUnderflowErr in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0MacRxFifoUnderflowErr 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacRxFifoUnderflowErr in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0MacRxFifoUnderflowErr u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacRxFifoUnderflowErr in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0MacRxFifoUnderflowErr u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacRxFifoIdleDeletion in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0MacRxFifoIdleDeletion 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacRxFifoIdleDeletion in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0MacRxFifoIdleDeletion u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacRxFifoIdleDeletion in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0MacRxFifoIdleDeletion u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacTxFifoParityErr in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxFifoParityErr 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacTxFifoParityErr in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxFifoParityErr u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacTxFifoParityErr in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxFifoParityErr u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacTxFifoOverflow in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxFifoOverflow 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacTxFifoOverflow in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxFifoOverflow u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacTxFifoOverflow in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxFifoOverflow u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacTxFifoUnderflow in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxFifoUnderflow 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacTxFifoUnderflow in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxFifoUnderflow u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacTxFifoUnderflow in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxFifoUnderflow u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacTxSfdError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxSfdError 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacTxSfdError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxSfdError u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacTxSfdError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxSfdError u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacTxFifoIdleInsertion in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxFifoIdleInsertion 13
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacTxFifoIdleInsertion in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxFifoIdleInsertion u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacTxFifoIdleInsertion in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0MacTxFifoIdleInsertion u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxHeaderCrcError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1RxHeaderCrcError 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxHeaderCrcError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1RxHeaderCrcError u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxHeaderCrcError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1RxHeaderCrcError u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxUsxgmiiLocalFault in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1RxUsxgmiiLocalFault 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxUsxgmiiLocalFault in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1RxUsxgmiiLocalFault u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxUsxgmiiLocalFault in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1RxUsxgmiiLocalFault u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkFifoOverflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1LinkFifoOverflowError 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkFifoOverflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1LinkFifoOverflowError u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkFifoOverflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1LinkFifoOverflowError u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkFifoUnderflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1LinkFifoUnderflowError 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkFifoUnderflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1LinkFifoUnderflowError u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkFifoUnderflowError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1LinkFifoUnderflowError u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1LinkFifoParityError 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1LinkFifoParityError u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1LinkFifoParityError u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxPacketInfoMessage in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1RxPacketInfoMessage 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxPacketInfoMessage in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1RxPacketInfoMessage u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxPacketInfoMessage in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1RxPacketInfoMessage u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacRxFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1MacRxFifoParityError 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacRxFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1MacRxFifoParityError u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacRxFifoParityError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1MacRxFifoParityError u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacRxFifoOverflowErr in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1MacRxFifoOverflowErr 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacRxFifoOverflowErr in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1MacRxFifoOverflowErr u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacRxFifoOverflowErr in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1MacRxFifoOverflowErr u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacRxFifoUnderflowErr in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1MacRxFifoUnderflowErr 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacRxFifoUnderflowErr in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1MacRxFifoUnderflowErr u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacRxFifoUnderflowErr in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1MacRxFifoUnderflowErr u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacRxFifoIdleDeletion in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1MacRxFifoIdleDeletion 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacRxFifoIdleDeletion in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1MacRxFifoIdleDeletion u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacRxFifoIdleDeletion in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1MacRxFifoIdleDeletion u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacTxFifoParityErr in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxFifoParityErr 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacTxFifoParityErr in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxFifoParityErr u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacTxFifoParityErr in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxFifoParityErr u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacTxFifoOverflow in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxFifoOverflow 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacTxFifoOverflow in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxFifoOverflow u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacTxFifoOverflow in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxFifoOverflow u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacTxFifoUnderflow in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxFifoUnderflow 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacTxFifoUnderflow in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxFifoUnderflow u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacTxFifoUnderflow in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxFifoUnderflow u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacTxSfdError in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxSfdError 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacTxSfdError in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxSfdError u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacTxSfdError in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxSfdError u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacTxFifoIdleInsertion in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxFifoIdleInsertion 14
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacTxFifoIdleInsertion in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxFifoIdleInsertion u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacTxFifoIdleInsertion in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1MacTxFifoIdleInsertion u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure usx0AutoNegCompleteLatchLow in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0AutoNegCompleteLatchLow 15
/*! \brief Preprocessor variable to relate field to bit position in structure usx0AutoNegCompleteLatchLow in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0AutoNegCompleteLatchLow u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure usx0AutoNegCompleteLatchLow in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0AutoNegCompleteLatchLow u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure usx0AutoNegCompleteLatchHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0AutoNegCompleteLatchHigh 15
/*! \brief Preprocessor variable to relate field to bit position in structure usx0AutoNegCompleteLatchHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0AutoNegCompleteLatchHigh u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure usx0AutoNegCompleteLatchHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0AutoNegCompleteLatchHigh u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure usx0AnStateMachineInterrupt in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0AnStateMachineInterrupt 15
/*! \brief Preprocessor variable to relate field to bit position in structure usx0AnStateMachineInterrupt in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0AnStateMachineInterrupt u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure usx0AnStateMachineInterrupt in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0AnStateMachineInterrupt u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxUnidataConfigChange in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0RxUnidataConfigChange 15
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxUnidataConfigChange in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0RxUnidataConfigChange u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxUnidataConfigChange in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0RxUnidataConfigChange u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure usx0InvocationOfThePriorityResolutionFunction in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0InvocationOfThePriorityResolutionFunction 15
/*! \brief Preprocessor variable to relate field to bit position in structure usx0InvocationOfThePriorityResolutionFunction in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0InvocationOfThePriorityResolutionFunction u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure usx0InvocationOfThePriorityResolutionFunction in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0InvocationOfThePriorityResolutionFunction u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkTimerDone in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0LinkTimerDone 15
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkTimerDone in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0LinkTimerDone u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkTimerDone in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0LinkTimerDone u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure usx0AbilityMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0AbilityMatchIndication 15
/*! \brief Preprocessor variable to relate field to bit position in structure usx0AbilityMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0AbilityMatchIndication u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure usx0AbilityMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0AbilityMatchIndication u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure usx0AcknowledgementMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0AcknowledgementMatchIndication 15
/*! \brief Preprocessor variable to relate field to bit position in structure usx0AcknowledgementMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0AcknowledgementMatchIndication u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure usx0AcknowledgementMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0AcknowledgementMatchIndication u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure usx0ConsistencyMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0ConsistencyMatchIndication 15
/*! \brief Preprocessor variable to relate field to bit position in structure usx0ConsistencyMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0ConsistencyMatchIndication u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure usx0ConsistencyMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0ConsistencyMatchIndication u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure usx0IdleMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0IdleMatchIndication 15
/*! \brief Preprocessor variable to relate field to bit position in structure usx0IdleMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0IdleMatchIndication u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure usx0IdleMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0IdleMatchIndication u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkPartnerAdvChange in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx0LinkPartnerAdvChange 15
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkPartnerAdvChange in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx0LinkPartnerAdvChange u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkPartnerAdvChange in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx0LinkPartnerAdvChange u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure usx1AutoNegCompleteLatchLow in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1AutoNegCompleteLatchLow 16
/*! \brief Preprocessor variable to relate field to bit position in structure usx1AutoNegCompleteLatchLow in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1AutoNegCompleteLatchLow u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure usx1AutoNegCompleteLatchLow in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1AutoNegCompleteLatchLow u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure usx1AutoNegCompleteLatchHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1AutoNegCompleteLatchHigh 16
/*! \brief Preprocessor variable to relate field to bit position in structure usx1AutoNegCompleteLatchHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1AutoNegCompleteLatchHigh u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure usx1AutoNegCompleteLatchHigh in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1AutoNegCompleteLatchHigh u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure usx1AnStateMachineInterrupt in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1AnStateMachineInterrupt 16
/*! \brief Preprocessor variable to relate field to bit position in structure usx1AnStateMachineInterrupt in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1AnStateMachineInterrupt u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure usx1AnStateMachineInterrupt in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1AnStateMachineInterrupt u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxUnidataConfigChange in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1RxUnidataConfigChange 16
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxUnidataConfigChange in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1RxUnidataConfigChange u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxUnidataConfigChange in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1RxUnidataConfigChange u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure usx1InvocationOfThePriorityResolutionFunction in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1InvocationOfThePriorityResolutionFunction 16
/*! \brief Preprocessor variable to relate field to bit position in structure usx1InvocationOfThePriorityResolutionFunction in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1InvocationOfThePriorityResolutionFunction u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure usx1InvocationOfThePriorityResolutionFunction in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1InvocationOfThePriorityResolutionFunction u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkTimerDone in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1LinkTimerDone 16
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkTimerDone in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1LinkTimerDone u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkTimerDone in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1LinkTimerDone u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure usx1AbilityMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1AbilityMatchIndication 16
/*! \brief Preprocessor variable to relate field to bit position in structure usx1AbilityMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1AbilityMatchIndication u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure usx1AbilityMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1AbilityMatchIndication u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure usx1AcknowledgementMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1AcknowledgementMatchIndication 16
/*! \brief Preprocessor variable to relate field to bit position in structure usx1AcknowledgementMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1AcknowledgementMatchIndication u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure usx1AcknowledgementMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1AcknowledgementMatchIndication u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure usx1ConsistencyMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1ConsistencyMatchIndication 16
/*! \brief Preprocessor variable to relate field to bit position in structure usx1ConsistencyMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1ConsistencyMatchIndication u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure usx1ConsistencyMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1ConsistencyMatchIndication u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure usx1IdleMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1IdleMatchIndication 16
/*! \brief Preprocessor variable to relate field to bit position in structure usx1IdleMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1IdleMatchIndication u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure usx1IdleMatchIndication in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1IdleMatchIndication u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkPartnerAdvChange in AQ_PcsReceiveVendorAlarms_HHD */
#define AQ_PcsReceiveVendorAlarms_HHD_usx1LinkPartnerAdvChange 16
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkPartnerAdvChange in AQ_PcsReceiveVendorAlarms_HHD */
#define bits_AQ_PcsReceiveVendorAlarms_HHD_usx1LinkPartnerAdvChange u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkPartnerAdvChange in AQ_PcsReceiveVendorAlarms_HHD */
#define word_AQ_PcsReceiveVendorAlarms_HHD_usx1LinkPartnerAdvChange u16.word_16

/*! \brief Base register address of structure AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_baseRegisterAddress 0xED0D
/*! \brief MMD address of structure AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxHeaderCrcError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0RxHeaderCrcError 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxHeaderCrcError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0RxHeaderCrcError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxHeaderCrcError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0RxHeaderCrcError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxUsxgmiiLocalFault in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0RxUsxgmiiLocalFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxUsxgmiiLocalFault in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0RxUsxgmiiLocalFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxUsxgmiiLocalFault in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0RxUsxgmiiLocalFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkFifoOverflowError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkFifoOverflowError 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkFifoOverflowError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkFifoOverflowError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkFifoOverflowError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkFifoOverflowError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkFifoUnderflowError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkFifoUnderflowError 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkFifoUnderflowError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkFifoUnderflowError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkFifoUnderflowError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkFifoUnderflowError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkFifoParityError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkFifoParityError 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkFifoParityError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkFifoParityError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkFifoParityError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkFifoParityError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxPacketInfoMessage in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0RxPacketInfoMessage 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxPacketInfoMessage in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0RxPacketInfoMessage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxPacketInfoMessage in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0RxPacketInfoMessage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacRxFifoParityError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacRxFifoParityError 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacRxFifoParityError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacRxFifoParityError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacRxFifoParityError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacRxFifoParityError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacRxFifoOverflowErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacRxFifoOverflowErr 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacRxFifoOverflowErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacRxFifoOverflowErr u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacRxFifoOverflowErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacRxFifoOverflowErr u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacRxFifoUnderflowErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacRxFifoUnderflowErr 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacRxFifoUnderflowErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacRxFifoUnderflowErr u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacRxFifoUnderflowErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacRxFifoUnderflowErr u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacRxFifoIdleDeletion in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacRxFifoIdleDeletion 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacRxFifoIdleDeletion in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacRxFifoIdleDeletion u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacRxFifoIdleDeletion in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacRxFifoIdleDeletion u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacTxFifoParityErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxFifoParityErr 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacTxFifoParityErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxFifoParityErr u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacTxFifoParityErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxFifoParityErr u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacTxFifoOverflow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxFifoOverflow 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacTxFifoOverflow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxFifoOverflow u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacTxFifoOverflow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxFifoOverflow u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacTxFifoUnderflow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxFifoUnderflow 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacTxFifoUnderflow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxFifoUnderflow u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacTxFifoUnderflow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxFifoUnderflow u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacTxSfdError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxSfdError 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacTxSfdError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxSfdError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacTxSfdError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxSfdError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx0MacTxFifoIdleInsertion in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxFifoIdleInsertion 0
/*! \brief Preprocessor variable to relate field to bit position in structure usx0MacTxFifoIdleInsertion in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxFifoIdleInsertion u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure usx0MacTxFifoIdleInsertion in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0MacTxFifoIdleInsertion u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxHeaderCrcError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1RxHeaderCrcError 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxHeaderCrcError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1RxHeaderCrcError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxHeaderCrcError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1RxHeaderCrcError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxUsxgmiiLocalFault in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1RxUsxgmiiLocalFault 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxUsxgmiiLocalFault in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1RxUsxgmiiLocalFault u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxUsxgmiiLocalFault in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1RxUsxgmiiLocalFault u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkFifoOverflowError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkFifoOverflowError 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkFifoOverflowError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkFifoOverflowError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkFifoOverflowError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkFifoOverflowError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkFifoUnderflowError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkFifoUnderflowError 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkFifoUnderflowError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkFifoUnderflowError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkFifoUnderflowError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkFifoUnderflowError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkFifoParityError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkFifoParityError 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkFifoParityError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkFifoParityError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkFifoParityError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkFifoParityError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxPacketInfoMessage in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1RxPacketInfoMessage 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxPacketInfoMessage in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1RxPacketInfoMessage u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxPacketInfoMessage in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1RxPacketInfoMessage u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacRxFifoParityError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacRxFifoParityError 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacRxFifoParityError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacRxFifoParityError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacRxFifoParityError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacRxFifoParityError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacRxFifoOverflowErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacRxFifoOverflowErr 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacRxFifoOverflowErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacRxFifoOverflowErr u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacRxFifoOverflowErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacRxFifoOverflowErr u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacRxFifoUnderflowErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacRxFifoUnderflowErr 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacRxFifoUnderflowErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacRxFifoUnderflowErr u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacRxFifoUnderflowErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacRxFifoUnderflowErr u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacRxFifoIdleDeletion in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacRxFifoIdleDeletion 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacRxFifoIdleDeletion in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacRxFifoIdleDeletion u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacRxFifoIdleDeletion in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacRxFifoIdleDeletion u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacTxFifoParityErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxFifoParityErr 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacTxFifoParityErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxFifoParityErr u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacTxFifoParityErr in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxFifoParityErr u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacTxFifoOverflow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxFifoOverflow 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacTxFifoOverflow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxFifoOverflow u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacTxFifoOverflow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxFifoOverflow u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacTxFifoUnderflow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxFifoUnderflow 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacTxFifoUnderflow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxFifoUnderflow u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacTxFifoUnderflow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxFifoUnderflow u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacTxSfdError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxSfdError 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacTxSfdError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxSfdError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacTxSfdError in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxSfdError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx1MacTxFifoIdleInsertion in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxFifoIdleInsertion 1
/*! \brief Preprocessor variable to relate field to bit position in structure usx1MacTxFifoIdleInsertion in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxFifoIdleInsertion u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure usx1MacTxFifoIdleInsertion in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1MacTxFifoIdleInsertion u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure usx0AutoNegCompleteLatchLow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AutoNegCompleteLatchLow 2
/*! \brief Preprocessor variable to relate field to bit position in structure usx0AutoNegCompleteLatchLow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AutoNegCompleteLatchLow u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure usx0AutoNegCompleteLatchLow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AutoNegCompleteLatchLow u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure usx0AutoNegCompleteLatchHigh in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AutoNegCompleteLatchHigh 2
/*! \brief Preprocessor variable to relate field to bit position in structure usx0AutoNegCompleteLatchHigh in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AutoNegCompleteLatchHigh u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure usx0AutoNegCompleteLatchHigh in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AutoNegCompleteLatchHigh u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure usx0AnStateMachineInterrupt in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AnStateMachineInterrupt 2
/*! \brief Preprocessor variable to relate field to bit position in structure usx0AnStateMachineInterrupt in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AnStateMachineInterrupt u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure usx0AnStateMachineInterrupt in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AnStateMachineInterrupt u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure usx0RxUnidataConfigChange in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0RxUnidataConfigChange 2
/*! \brief Preprocessor variable to relate field to bit position in structure usx0RxUnidataConfigChange in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0RxUnidataConfigChange u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure usx0RxUnidataConfigChange in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0RxUnidataConfigChange u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure usx0InvocationOfThePriorityResolutionFunction in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0InvocationOfThePriorityResolutionFunction 2
/*! \brief Preprocessor variable to relate field to bit position in structure usx0InvocationOfThePriorityResolutionFunction in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0InvocationOfThePriorityResolutionFunction u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure usx0InvocationOfThePriorityResolutionFunction in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0InvocationOfThePriorityResolutionFunction u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkTimerDone in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkTimerDone 2
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkTimerDone in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkTimerDone u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkTimerDone in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkTimerDone u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure usx0AbilityMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AbilityMatchIndication 2
/*! \brief Preprocessor variable to relate field to bit position in structure usx0AbilityMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AbilityMatchIndication u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure usx0AbilityMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AbilityMatchIndication u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure usx0AcknowledgementMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AcknowledgementMatchIndication 2
/*! \brief Preprocessor variable to relate field to bit position in structure usx0AcknowledgementMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AcknowledgementMatchIndication u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure usx0AcknowledgementMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0AcknowledgementMatchIndication u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure usx0ConsistencyMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0ConsistencyMatchIndication 2
/*! \brief Preprocessor variable to relate field to bit position in structure usx0ConsistencyMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0ConsistencyMatchIndication u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure usx0ConsistencyMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0ConsistencyMatchIndication u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure usx0IdleMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0IdleMatchIndication 2
/*! \brief Preprocessor variable to relate field to bit position in structure usx0IdleMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0IdleMatchIndication u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure usx0IdleMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0IdleMatchIndication u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure usx0LinkPartnerAdvChange in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkPartnerAdvChange 2
/*! \brief Preprocessor variable to relate field to bit position in structure usx0LinkPartnerAdvChange in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkPartnerAdvChange u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure usx0LinkPartnerAdvChange in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx0LinkPartnerAdvChange u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure usx1AutoNegCompleteLatchLow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AutoNegCompleteLatchLow 3
/*! \brief Preprocessor variable to relate field to bit position in structure usx1AutoNegCompleteLatchLow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AutoNegCompleteLatchLow u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure usx1AutoNegCompleteLatchLow in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AutoNegCompleteLatchLow u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure usx1AutoNegCompleteLatchHigh in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AutoNegCompleteLatchHigh 3
/*! \brief Preprocessor variable to relate field to bit position in structure usx1AutoNegCompleteLatchHigh in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AutoNegCompleteLatchHigh u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure usx1AutoNegCompleteLatchHigh in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AutoNegCompleteLatchHigh u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure usx1AnStateMachineInterrupt in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AnStateMachineInterrupt 3
/*! \brief Preprocessor variable to relate field to bit position in structure usx1AnStateMachineInterrupt in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AnStateMachineInterrupt u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure usx1AnStateMachineInterrupt in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AnStateMachineInterrupt u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure usx1RxUnidataConfigChange in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1RxUnidataConfigChange 3
/*! \brief Preprocessor variable to relate field to bit position in structure usx1RxUnidataConfigChange in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1RxUnidataConfigChange u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure usx1RxUnidataConfigChange in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1RxUnidataConfigChange u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure usx1InvocationOfThePriorityResolutionFunction in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1InvocationOfThePriorityResolutionFunction 3
/*! \brief Preprocessor variable to relate field to bit position in structure usx1InvocationOfThePriorityResolutionFunction in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1InvocationOfThePriorityResolutionFunction u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure usx1InvocationOfThePriorityResolutionFunction in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1InvocationOfThePriorityResolutionFunction u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkTimerDone in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkTimerDone 3
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkTimerDone in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkTimerDone u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkTimerDone in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkTimerDone u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure usx1AbilityMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AbilityMatchIndication 3
/*! \brief Preprocessor variable to relate field to bit position in structure usx1AbilityMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AbilityMatchIndication u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure usx1AbilityMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AbilityMatchIndication u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure usx1AcknowledgementMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AcknowledgementMatchIndication 3
/*! \brief Preprocessor variable to relate field to bit position in structure usx1AcknowledgementMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AcknowledgementMatchIndication u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure usx1AcknowledgementMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1AcknowledgementMatchIndication u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure usx1ConsistencyMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1ConsistencyMatchIndication 3
/*! \brief Preprocessor variable to relate field to bit position in structure usx1ConsistencyMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1ConsistencyMatchIndication u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure usx1ConsistencyMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1ConsistencyMatchIndication u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure usx1IdleMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1IdleMatchIndication 3
/*! \brief Preprocessor variable to relate field to bit position in structure usx1IdleMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1IdleMatchIndication u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure usx1IdleMatchIndication in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1IdleMatchIndication u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure usx1LinkPartnerAdvChange in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkPartnerAdvChange 3
/*! \brief Preprocessor variable to relate field to bit position in structure usx1LinkPartnerAdvChange in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define bits_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkPartnerAdvChange u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure usx1LinkPartnerAdvChange in AQ_PcsReceiveVendorInternalAlarms_HHD */
#define word_AQ_PcsReceiveVendorInternalAlarms_HHD_usx1LinkPartnerAdvChange u3.word_3

/*! \brief Base register address of structure AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_baseRegisterAddress 0xF400
/*! \brief MMD address of structure AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure crcErrorMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_crcErrorMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure crcErrorMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_crcErrorMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure crcErrorMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_crcErrorMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldpcDecodeFailureMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_ldpcDecodeFailureMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldpcDecodeFailureMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_ldpcDecodeFailureMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldpcDecodeFailureMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_ldpcDecodeFailureMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure localFaultDetectMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_localFaultDetectMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure localFaultDetectMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_localFaultDetectMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure localFaultDetectMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_localFaultDetectMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lofDetectMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_lofDetectMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure lofDetectMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_lofDetectMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lofDetectMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_lofDetectMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _40gBipLockMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD__40gBipLockMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure _40gBipLockMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD__40gBipLockMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _40gBipLockMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD__40gBipLockMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure invalid_65bBlockMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_invalid_65bBlockMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure invalid_65bBlockMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_invalid_65bBlockMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure invalid_65bBlockMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_invalid_65bBlockMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiActiveOffMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiActiveOffMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiActiveOffMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiActiveOffMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiActiveOffMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiActiveOffMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiActiveOnMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiActiveOnMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiActiveOnMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiActiveOnMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiActiveOnMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiActiveOnMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldpcConsecutiveErroredFrameExceededMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_ldpcConsecutiveErroredFrameExceededMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldpcConsecutiveErroredFrameExceededMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_ldpcConsecutiveErroredFrameExceededMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldpcConsecutiveErroredFrameExceededMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_ldpcConsecutiveErroredFrameExceededMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiAlertMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiAlertMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiAlertMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiAlertMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiAlertMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiAlertMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiReceivedLatchedLowMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiReceivedLatchedLowMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiReceivedLatchedLowMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiReceivedLatchedLowMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiReceivedLatchedLowMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiReceivedLatchedLowMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure eeeRxLpiReceivedLatchedHighMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiReceivedLatchedHighMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeRxLpiReceivedLatchedHighMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiReceivedLatchedHighMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeRxLpiReceivedLatchedHighMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_eeeRxLpiReceivedLatchedHighMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure changeInAuxilliaryBitMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_changeInAuxilliaryBitMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure changeInAuxilliaryBitMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_changeInAuxilliaryBitMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure changeInAuxilliaryBitMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_changeInAuxilliaryBitMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi1Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_xfi1Invalid_66bCharacterReceivedMask 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_xfi1Invalid_66bCharacterReceivedMask u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi1Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_xfi1Invalid_66bCharacterReceivedMask u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi0Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_xfi0Invalid_66bCharacterReceivedMask 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_xfi0Invalid_66bCharacterReceivedMask u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi0Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_xfi0Invalid_66bCharacterReceivedMask u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi1ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_xfi1ReceiveLinkStatusLatchHighMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_xfi1ReceiveLinkStatusLatchHighMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_xfi1ReceiveLinkStatusLatchHighMask u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi1HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_xfi1HighBerStatusMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_xfi1HighBerStatusMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_xfi1HighBerStatusMask u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_xfi1BlockLockStatusMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_xfi1BlockLockStatusMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_xfi1BlockLockStatusMask u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_xfi0ReceiveLinkStatusLatchHighMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_xfi0ReceiveLinkStatusLatchHighMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_xfi0ReceiveLinkStatusLatchHighMask u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_xfi0HighBerStatusMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_xfi0HighBerStatusMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_xfi0HighBerStatusMask u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define AQ_PcsReceiveVendorInterruptMask_HHD_xfi0BlockLockStatusMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define bits_AQ_PcsReceiveVendorInterruptMask_HHD_xfi0BlockLockStatusMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_HHD */
#define word_AQ_PcsReceiveVendorInterruptMask_HHD_xfi0BlockLockStatusMask u6.word_6

/*! \brief Base register address of structure AQ_PcsReceiveVendorDebug_HHD */
#define AQ_PcsReceiveVendorDebug_HHD_baseRegisterAddress 0xF800
/*! \brief MMD address of structure AQ_PcsReceiveVendorDebug_HHD */
#define AQ_PcsReceiveVendorDebug_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsRxDescramblerDisable in AQ_PcsReceiveVendorDebug_HHD */
#define AQ_PcsReceiveVendorDebug_HHD_pcsRxDescramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsRxDescramblerDisable in AQ_PcsReceiveVendorDebug_HHD */
#define bits_AQ_PcsReceiveVendorDebug_HHD_pcsRxDescramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsRxDescramblerDisable in AQ_PcsReceiveVendorDebug_HHD */
#define word_AQ_PcsReceiveVendorDebug_HHD_pcsRxDescramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsNetworkLoopbackMerge in AQ_PcsReceiveVendorDebug_HHD */
#define AQ_PcsReceiveVendorDebug_HHD_pcsNetworkLoopbackMerge 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsNetworkLoopbackMerge in AQ_PcsReceiveVendorDebug_HHD */
#define bits_AQ_PcsReceiveVendorDebug_HHD_pcsNetworkLoopbackMerge u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsNetworkLoopbackMerge in AQ_PcsReceiveVendorDebug_HHD */
#define word_AQ_PcsReceiveVendorDebug_HHD_pcsNetworkLoopbackMerge u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsNetworkLoopbackPassThrough in AQ_PcsReceiveVendorDebug_HHD */
#define AQ_PcsReceiveVendorDebug_HHD_pcsNetworkLoopbackPassThrough 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsNetworkLoopbackPassThrough in AQ_PcsReceiveVendorDebug_HHD */
#define bits_AQ_PcsReceiveVendorDebug_HHD_pcsNetworkLoopbackPassThrough u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsNetworkLoopbackPassThrough in AQ_PcsReceiveVendorDebug_HHD */
#define word_AQ_PcsReceiveVendorDebug_HHD_pcsNetworkLoopbackPassThrough u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsNetworkLoopback in AQ_PcsReceiveVendorDebug_HHD */
#define AQ_PcsReceiveVendorDebug_HHD_pcsNetworkLoopback 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsNetworkLoopback in AQ_PcsReceiveVendorDebug_HHD */
#define bits_AQ_PcsReceiveVendorDebug_HHD_pcsNetworkLoopback u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsNetworkLoopback in AQ_PcsReceiveVendorDebug_HHD */
#define word_AQ_PcsReceiveVendorDebug_HHD_pcsNetworkLoopback u0.word_0

/*! \brief Base register address of structure AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_baseRegisterAddress 0xFC00
/*! \brief MMD address of structure AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarm_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_standardAlarm_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarm_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PcsVendorGlobalInterruptFlags_HHD_standardAlarm_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarm_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define word_AQ_PcsVendorGlobalInterruptFlags_HHD_standardAlarm_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarm_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_standardAlarm_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarm_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PcsVendorGlobalInterruptFlags_HHD_standardAlarm_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarm_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define word_AQ_PcsVendorGlobalInterruptFlags_HHD_standardAlarm_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarm_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_standardAlarm_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarm_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PcsVendorGlobalInterruptFlags_HHD_standardAlarm_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarm_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define word_AQ_PcsVendorGlobalInterruptFlags_HHD_standardAlarm_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define word_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define word_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define word_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define word_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define word_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define word_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_4Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_4Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_4Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_4Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_4Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define word_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_4Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_5Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_5Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_5Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_5Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_5Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define word_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_5Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_6Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_6Interrupt 2
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_6Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_6Interrupt u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_6Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define word_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_6Interrupt u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_7Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_7Interrupt 2
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_7Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_7Interrupt u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_7Interrupt in AQ_PcsVendorGlobalInterruptFlags_HHD */
#define word_AQ_PcsVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_7Interrupt u2.word_2
#endif
/*@}*/
/*@}*/
