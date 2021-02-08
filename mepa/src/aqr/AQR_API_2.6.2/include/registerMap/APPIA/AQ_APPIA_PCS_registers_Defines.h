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
#ifndef AQ_APPIA_PCS_REGS_DEFINES_HEADER
#define AQ_APPIA_PCS_REGS_DEFINES_HEADER


/*-----------------------------------------------------------------------------*/
/*Access macro definitions                                                     */
/*-----------------------------------------------------------------------------*/
/*! \brief Base register address of structure AQ_PcsStandardControl_1_APPIA */
#define AQ_PcsStandardControl_1_APPIA_baseRegisterAddress 0x0000
/*! \brief MMD address of structure AQ_PcsStandardControl_1_APPIA */
#define AQ_PcsStandardControl_1_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reset in AQ_PcsStandardControl_1_APPIA */
#define AQ_PcsStandardControl_1_APPIA_reset 0
/*! \brief Preprocessor variable to relate field to bit position in structure reset in AQ_PcsStandardControl_1_APPIA */
#define bits_AQ_PcsStandardControl_1_APPIA_reset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reset in AQ_PcsStandardControl_1_APPIA */
#define word_AQ_PcsStandardControl_1_APPIA_reset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure loopback in AQ_PcsStandardControl_1_APPIA */
#define AQ_PcsStandardControl_1_APPIA_loopback 0
/*! \brief Preprocessor variable to relate field to bit position in structure loopback in AQ_PcsStandardControl_1_APPIA */
#define bits_AQ_PcsStandardControl_1_APPIA_loopback u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure loopback in AQ_PcsStandardControl_1_APPIA */
#define word_AQ_PcsStandardControl_1_APPIA_loopback u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure speedSelectionLsb in AQ_PcsStandardControl_1_APPIA */
#define AQ_PcsStandardControl_1_APPIA_speedSelectionLsb 0
/*! \brief Preprocessor variable to relate field to bit position in structure speedSelectionLsb in AQ_PcsStandardControl_1_APPIA */
#define bits_AQ_PcsStandardControl_1_APPIA_speedSelectionLsb u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure speedSelectionLsb in AQ_PcsStandardControl_1_APPIA */
#define word_AQ_PcsStandardControl_1_APPIA_speedSelectionLsb u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowPower in AQ_PcsStandardControl_1_APPIA */
#define AQ_PcsStandardControl_1_APPIA_lowPower 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowPower in AQ_PcsStandardControl_1_APPIA */
#define bits_AQ_PcsStandardControl_1_APPIA_lowPower u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowPower in AQ_PcsStandardControl_1_APPIA */
#define word_AQ_PcsStandardControl_1_APPIA_lowPower u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure speedSelectionMsb in AQ_PcsStandardControl_1_APPIA */
#define AQ_PcsStandardControl_1_APPIA_speedSelectionMsb 0
/*! \brief Preprocessor variable to relate field to bit position in structure speedSelectionMsb in AQ_PcsStandardControl_1_APPIA */
#define bits_AQ_PcsStandardControl_1_APPIA_speedSelectionMsb u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure speedSelectionMsb in AQ_PcsStandardControl_1_APPIA */
#define word_AQ_PcsStandardControl_1_APPIA_speedSelectionMsb u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gSpeedSelection in AQ_PcsStandardControl_1_APPIA */
#define AQ_PcsStandardControl_1_APPIA__10gSpeedSelection 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gSpeedSelection in AQ_PcsStandardControl_1_APPIA */
#define bits_AQ_PcsStandardControl_1_APPIA__10gSpeedSelection u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gSpeedSelection in AQ_PcsStandardControl_1_APPIA */
#define word_AQ_PcsStandardControl_1_APPIA__10gSpeedSelection u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardStatus_1_APPIA */
#define AQ_PcsStandardStatus_1_APPIA_baseRegisterAddress 0x0001
/*! \brief MMD address of structure AQ_PcsStandardStatus_1_APPIA */
#define AQ_PcsStandardStatus_1_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure fault in AQ_PcsStandardStatus_1_APPIA */
#define AQ_PcsStandardStatus_1_APPIA_fault 0
/*! \brief Preprocessor variable to relate field to bit position in structure fault in AQ_PcsStandardStatus_1_APPIA */
#define bits_AQ_PcsStandardStatus_1_APPIA_fault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure fault in AQ_PcsStandardStatus_1_APPIA */
#define word_AQ_PcsStandardStatus_1_APPIA_fault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsReceiveLinkStatus in AQ_PcsStandardStatus_1_APPIA */
#define AQ_PcsStandardStatus_1_APPIA_pcsReceiveLinkStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsReceiveLinkStatus in AQ_PcsStandardStatus_1_APPIA */
#define bits_AQ_PcsStandardStatus_1_APPIA_pcsReceiveLinkStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsReceiveLinkStatus in AQ_PcsStandardStatus_1_APPIA */
#define word_AQ_PcsStandardStatus_1_APPIA_pcsReceiveLinkStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowPowerAbility in AQ_PcsStandardStatus_1_APPIA */
#define AQ_PcsStandardStatus_1_APPIA_lowPowerAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowPowerAbility in AQ_PcsStandardStatus_1_APPIA */
#define bits_AQ_PcsStandardStatus_1_APPIA_lowPowerAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowPowerAbility in AQ_PcsStandardStatus_1_APPIA */
#define word_AQ_PcsStandardStatus_1_APPIA_lowPowerAbility u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardDeviceIdentifier_APPIA */
#define AQ_PcsStandardDeviceIdentifier_APPIA_baseRegisterAddress 0x0002
/*! \brief MMD address of structure AQ_PcsStandardDeviceIdentifier_APPIA */
#define AQ_PcsStandardDeviceIdentifier_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdMSW in AQ_PcsStandardDeviceIdentifier_APPIA */
#define AQ_PcsStandardDeviceIdentifier_APPIA_deviceIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdMSW in AQ_PcsStandardDeviceIdentifier_APPIA */
#define bits_AQ_PcsStandardDeviceIdentifier_APPIA_deviceIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdMSW in AQ_PcsStandardDeviceIdentifier_APPIA */
#define word_AQ_PcsStandardDeviceIdentifier_APPIA_deviceIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdLSW in AQ_PcsStandardDeviceIdentifier_APPIA */
#define AQ_PcsStandardDeviceIdentifier_APPIA_deviceIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdLSW in AQ_PcsStandardDeviceIdentifier_APPIA */
#define bits_AQ_PcsStandardDeviceIdentifier_APPIA_deviceIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdLSW in AQ_PcsStandardDeviceIdentifier_APPIA */
#define word_AQ_PcsStandardDeviceIdentifier_APPIA_deviceIdLSW u1.word_1

/*! \brief Base register address of structure AQ_PcsStandardSpeedAbility_APPIA */
#define AQ_PcsStandardSpeedAbility_APPIA_baseRegisterAddress 0x0004
/*! \brief MMD address of structure AQ_PcsStandardSpeedAbility_APPIA */
#define AQ_PcsStandardSpeedAbility_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gCapable in AQ_PcsStandardSpeedAbility_APPIA */
#define AQ_PcsStandardSpeedAbility_APPIA__10gCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gCapable in AQ_PcsStandardSpeedAbility_APPIA */
#define bits_AQ_PcsStandardSpeedAbility_APPIA__10gCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gCapable in AQ_PcsStandardSpeedAbility_APPIA */
#define word_AQ_PcsStandardSpeedAbility_APPIA__10gCapable u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardDevicesInPackage_APPIA */
#define AQ_PcsStandardDevicesInPackage_APPIA_baseRegisterAddress 0x0005
/*! \brief MMD address of structure AQ_PcsStandardDevicesInPackage_APPIA */
#define AQ_PcsStandardDevicesInPackage_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define AQ_PcsStandardDevicesInPackage_APPIA_autonegotiationPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define bits_AQ_PcsStandardDevicesInPackage_APPIA_autonegotiationPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define word_AQ_PcsStandardDevicesInPackage_APPIA_autonegotiationPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tcPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define AQ_PcsStandardDevicesInPackage_APPIA_tcPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure tcPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define bits_AQ_PcsStandardDevicesInPackage_APPIA_tcPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tcPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define word_AQ_PcsStandardDevicesInPackage_APPIA_tcPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure dteXsPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define AQ_PcsStandardDevicesInPackage_APPIA_dteXsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure dteXsPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define bits_AQ_PcsStandardDevicesInPackage_APPIA_dteXsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure dteXsPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define word_AQ_PcsStandardDevicesInPackage_APPIA_dteXsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_Present in AQ_PcsStandardDevicesInPackage_APPIA */
#define AQ_PcsStandardDevicesInPackage_APPIA_phyXS_Present 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_Present in AQ_PcsStandardDevicesInPackage_APPIA */
#define bits_AQ_PcsStandardDevicesInPackage_APPIA_phyXS_Present u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_Present in AQ_PcsStandardDevicesInPackage_APPIA */
#define word_AQ_PcsStandardDevicesInPackage_APPIA_phyXS_Present u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define AQ_PcsStandardDevicesInPackage_APPIA_pcsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define bits_AQ_PcsStandardDevicesInPackage_APPIA_pcsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define word_AQ_PcsStandardDevicesInPackage_APPIA_pcsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure wisPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define AQ_PcsStandardDevicesInPackage_APPIA_wisPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure wisPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define bits_AQ_PcsStandardDevicesInPackage_APPIA_wisPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure wisPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define word_AQ_PcsStandardDevicesInPackage_APPIA_wisPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define AQ_PcsStandardDevicesInPackage_APPIA_pmaPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define bits_AQ_PcsStandardDevicesInPackage_APPIA_pmaPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define word_AQ_PcsStandardDevicesInPackage_APPIA_pmaPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clause_22RegistersPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define AQ_PcsStandardDevicesInPackage_APPIA_clause_22RegistersPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22RegistersPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define bits_AQ_PcsStandardDevicesInPackage_APPIA_clause_22RegistersPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clause_22RegistersPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define word_AQ_PcsStandardDevicesInPackage_APPIA_clause_22RegistersPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_2Present in AQ_PcsStandardDevicesInPackage_APPIA */
#define AQ_PcsStandardDevicesInPackage_APPIA_vendorSpecificDevice_2Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_2Present in AQ_PcsStandardDevicesInPackage_APPIA */
#define bits_AQ_PcsStandardDevicesInPackage_APPIA_vendorSpecificDevice_2Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_2Present in AQ_PcsStandardDevicesInPackage_APPIA */
#define word_AQ_PcsStandardDevicesInPackage_APPIA_vendorSpecificDevice_2Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_1Present in AQ_PcsStandardDevicesInPackage_APPIA */
#define AQ_PcsStandardDevicesInPackage_APPIA_vendorSpecificDevice_1Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_1Present in AQ_PcsStandardDevicesInPackage_APPIA */
#define bits_AQ_PcsStandardDevicesInPackage_APPIA_vendorSpecificDevice_1Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_1Present in AQ_PcsStandardDevicesInPackage_APPIA */
#define word_AQ_PcsStandardDevicesInPackage_APPIA_vendorSpecificDevice_1Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure clause_22ExtensionPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define AQ_PcsStandardDevicesInPackage_APPIA_clause_22ExtensionPresent 1
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22ExtensionPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define bits_AQ_PcsStandardDevicesInPackage_APPIA_clause_22ExtensionPresent u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure clause_22ExtensionPresent in AQ_PcsStandardDevicesInPackage_APPIA */
#define word_AQ_PcsStandardDevicesInPackage_APPIA_clause_22ExtensionPresent u1.word_1

/*! \brief Base register address of structure AQ_PcsStandardControl_2_APPIA */
#define AQ_PcsStandardControl_2_APPIA_baseRegisterAddress 0x0007
/*! \brief MMD address of structure AQ_PcsStandardControl_2_APPIA */
#define AQ_PcsStandardControl_2_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsDeviceType in AQ_PcsStandardControl_2_APPIA */
#define AQ_PcsStandardControl_2_APPIA_pcsDeviceType 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsDeviceType in AQ_PcsStandardControl_2_APPIA */
#define bits_AQ_PcsStandardControl_2_APPIA_pcsDeviceType u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsDeviceType in AQ_PcsStandardControl_2_APPIA */
#define word_AQ_PcsStandardControl_2_APPIA_pcsDeviceType u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardStatus_2_APPIA */
#define AQ_PcsStandardStatus_2_APPIA_baseRegisterAddress 0x0008
/*! \brief MMD address of structure AQ_PcsStandardStatus_2_APPIA */
#define AQ_PcsStandardStatus_2_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure devicePresent in AQ_PcsStandardStatus_2_APPIA */
#define AQ_PcsStandardStatus_2_APPIA_devicePresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure devicePresent in AQ_PcsStandardStatus_2_APPIA */
#define bits_AQ_PcsStandardStatus_2_APPIA_devicePresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure devicePresent in AQ_PcsStandardStatus_2_APPIA */
#define word_AQ_PcsStandardStatus_2_APPIA_devicePresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitFault in AQ_PcsStandardStatus_2_APPIA */
#define AQ_PcsStandardStatus_2_APPIA_transmitFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure transmitFault in AQ_PcsStandardStatus_2_APPIA */
#define bits_AQ_PcsStandardStatus_2_APPIA_transmitFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure transmitFault in AQ_PcsStandardStatus_2_APPIA */
#define word_AQ_PcsStandardStatus_2_APPIA_transmitFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure receiveFault in AQ_PcsStandardStatus_2_APPIA */
#define AQ_PcsStandardStatus_2_APPIA_receiveFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure receiveFault in AQ_PcsStandardStatus_2_APPIA */
#define bits_AQ_PcsStandardStatus_2_APPIA_receiveFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure receiveFault in AQ_PcsStandardStatus_2_APPIA */
#define word_AQ_PcsStandardStatus_2_APPIA_receiveFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tCapable in AQ_PcsStandardStatus_2_APPIA */
#define AQ_PcsStandardStatus_2_APPIA__10gbase_tCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tCapable in AQ_PcsStandardStatus_2_APPIA */
#define bits_AQ_PcsStandardStatus_2_APPIA__10gbase_tCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tCapable in AQ_PcsStandardStatus_2_APPIA */
#define word_AQ_PcsStandardStatus_2_APPIA__10gbase_tCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_wCapable in AQ_PcsStandardStatus_2_APPIA */
#define AQ_PcsStandardStatus_2_APPIA__10gbase_wCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_wCapable in AQ_PcsStandardStatus_2_APPIA */
#define bits_AQ_PcsStandardStatus_2_APPIA__10gbase_wCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_wCapable in AQ_PcsStandardStatus_2_APPIA */
#define word_AQ_PcsStandardStatus_2_APPIA__10gbase_wCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_xCapable in AQ_PcsStandardStatus_2_APPIA */
#define AQ_PcsStandardStatus_2_APPIA__10gbase_xCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_xCapable in AQ_PcsStandardStatus_2_APPIA */
#define bits_AQ_PcsStandardStatus_2_APPIA__10gbase_xCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_xCapable in AQ_PcsStandardStatus_2_APPIA */
#define word_AQ_PcsStandardStatus_2_APPIA__10gbase_xCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_rCapable in AQ_PcsStandardStatus_2_APPIA */
#define AQ_PcsStandardStatus_2_APPIA__10gbase_rCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_rCapable in AQ_PcsStandardStatus_2_APPIA */
#define bits_AQ_PcsStandardStatus_2_APPIA__10gbase_rCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_rCapable in AQ_PcsStandardStatus_2_APPIA */
#define word_AQ_PcsStandardStatus_2_APPIA__10gbase_rCapable u0.word_0

/*! \brief Base register address of structure AQ_PcsStandardPackageIdentifier_APPIA */
#define AQ_PcsStandardPackageIdentifier_APPIA_baseRegisterAddress 0x000E
/*! \brief MMD address of structure AQ_PcsStandardPackageIdentifier_APPIA */
#define AQ_PcsStandardPackageIdentifier_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure packageIdMSW in AQ_PcsStandardPackageIdentifier_APPIA */
#define AQ_PcsStandardPackageIdentifier_APPIA_packageIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdMSW in AQ_PcsStandardPackageIdentifier_APPIA */
#define bits_AQ_PcsStandardPackageIdentifier_APPIA_packageIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure packageIdMSW in AQ_PcsStandardPackageIdentifier_APPIA */
#define word_AQ_PcsStandardPackageIdentifier_APPIA_packageIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure packageIdLSW in AQ_PcsStandardPackageIdentifier_APPIA */
#define AQ_PcsStandardPackageIdentifier_APPIA_packageIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdLSW in AQ_PcsStandardPackageIdentifier_APPIA */
#define bits_AQ_PcsStandardPackageIdentifier_APPIA_packageIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure packageIdLSW in AQ_PcsStandardPackageIdentifier_APPIA */
#define word_AQ_PcsStandardPackageIdentifier_APPIA_packageIdLSW u1.word_1

/*! \brief Base register address of structure AQ_Pcs10GBaseT_Status_APPIA */
#define AQ_Pcs10GBaseT_Status_APPIA_baseRegisterAddress 0x0020
/*! \brief MMD address of structure AQ_Pcs10GBaseT_Status_APPIA */
#define AQ_Pcs10GBaseT_Status_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tReceiveLinkStatus in AQ_Pcs10GBaseT_Status_APPIA */
#define AQ_Pcs10GBaseT_Status_APPIA__10gbase_tReceiveLinkStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tReceiveLinkStatus in AQ_Pcs10GBaseT_Status_APPIA */
#define bits_AQ_Pcs10GBaseT_Status_APPIA__10gbase_tReceiveLinkStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tReceiveLinkStatus in AQ_Pcs10GBaseT_Status_APPIA */
#define word_AQ_Pcs10GBaseT_Status_APPIA__10gbase_tReceiveLinkStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tHighBer in AQ_Pcs10GBaseT_Status_APPIA */
#define AQ_Pcs10GBaseT_Status_APPIA__10gbase_tHighBer 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tHighBer in AQ_Pcs10GBaseT_Status_APPIA */
#define bits_AQ_Pcs10GBaseT_Status_APPIA__10gbase_tHighBer u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tHighBer in AQ_Pcs10GBaseT_Status_APPIA */
#define word_AQ_Pcs10GBaseT_Status_APPIA__10gbase_tHighBer u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tPcsBlockLock in AQ_Pcs10GBaseT_Status_APPIA */
#define AQ_Pcs10GBaseT_Status_APPIA__10gbase_tPcsBlockLock 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tPcsBlockLock in AQ_Pcs10GBaseT_Status_APPIA */
#define bits_AQ_Pcs10GBaseT_Status_APPIA__10gbase_tPcsBlockLock u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tPcsBlockLock in AQ_Pcs10GBaseT_Status_APPIA */
#define word_AQ_Pcs10GBaseT_Status_APPIA__10gbase_tPcsBlockLock u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tPcsBlockLockLatched in AQ_Pcs10GBaseT_Status_APPIA */
#define AQ_Pcs10GBaseT_Status_APPIA__10gbase_tPcsBlockLockLatched 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tPcsBlockLockLatched in AQ_Pcs10GBaseT_Status_APPIA */
#define bits_AQ_Pcs10GBaseT_Status_APPIA__10gbase_tPcsBlockLockLatched u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tPcsBlockLockLatched in AQ_Pcs10GBaseT_Status_APPIA */
#define word_AQ_Pcs10GBaseT_Status_APPIA__10gbase_tPcsBlockLockLatched u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tHighBerLatched in AQ_Pcs10GBaseT_Status_APPIA */
#define AQ_Pcs10GBaseT_Status_APPIA__10gbase_tHighBerLatched 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tHighBerLatched in AQ_Pcs10GBaseT_Status_APPIA */
#define bits_AQ_Pcs10GBaseT_Status_APPIA__10gbase_tHighBerLatched u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tHighBerLatched in AQ_Pcs10GBaseT_Status_APPIA */
#define word_AQ_Pcs10GBaseT_Status_APPIA__10gbase_tHighBerLatched u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ldpcErroredFrameCounter in AQ_Pcs10GBaseT_Status_APPIA */
#define AQ_Pcs10GBaseT_Status_APPIA_ldpcErroredFrameCounter 1
/*! \brief Preprocessor variable to relate field to bit position in structure ldpcErroredFrameCounter in AQ_Pcs10GBaseT_Status_APPIA */
#define bits_AQ_Pcs10GBaseT_Status_APPIA_ldpcErroredFrameCounter u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ldpcErroredFrameCounter in AQ_Pcs10GBaseT_Status_APPIA */
#define word_AQ_Pcs10GBaseT_Status_APPIA_ldpcErroredFrameCounter u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure errored_65bBlockCounter in AQ_Pcs10GBaseT_Status_APPIA */
#define AQ_Pcs10GBaseT_Status_APPIA_errored_65bBlockCounter 1
/*! \brief Preprocessor variable to relate field to bit position in structure errored_65bBlockCounter in AQ_Pcs10GBaseT_Status_APPIA */
#define bits_AQ_Pcs10GBaseT_Status_APPIA_errored_65bBlockCounter u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure errored_65bBlockCounter in AQ_Pcs10GBaseT_Status_APPIA */
#define word_AQ_Pcs10GBaseT_Status_APPIA_errored_65bBlockCounter u1.word_1

/*! \brief Base register address of structure AQ_PcsTransmitVendorProvisioning_APPIA */
#define AQ_PcsTransmitVendorProvisioning_APPIA_baseRegisterAddress 0xC400
/*! \brief MMD address of structure AQ_PcsTransmitVendorProvisioning_APPIA */
#define AQ_PcsTransmitVendorProvisioning_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsTxAuxilliaryBitValue in AQ_PcsTransmitVendorProvisioning_APPIA */
#define AQ_PcsTransmitVendorProvisioning_APPIA_pcsTxAuxilliaryBitValue 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTxAuxilliaryBitValue in AQ_PcsTransmitVendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitVendorProvisioning_APPIA_pcsTxAuxilliaryBitValue u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTxAuxilliaryBitValue in AQ_PcsTransmitVendorProvisioning_APPIA */
#define word_AQ_PcsTransmitVendorProvisioning_APPIA_pcsTxAuxilliaryBitValue u0.word_0

/*! \brief Base register address of structure AQ_PcsTransmitReservedVendorProvisioning_APPIA */
#define AQ_PcsTransmitReservedVendorProvisioning_APPIA_baseRegisterAddress 0xC410
/*! \brief MMD address of structure AQ_PcsTransmitReservedVendorProvisioning_APPIA */
#define AQ_PcsTransmitReservedVendorProvisioning_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reservedTransmitProvisioning_1 in AQ_PcsTransmitReservedVendorProvisioning_APPIA */
#define AQ_PcsTransmitReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedTransmitProvisioning_1 in AQ_PcsTransmitReservedVendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedTransmitProvisioning_1 in AQ_PcsTransmitReservedVendorProvisioning_APPIA */
#define word_AQ_PcsTransmitReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsIEEE_LoopbackPassthroughDisable in AQ_PcsTransmitReservedVendorProvisioning_APPIA */
#define AQ_PcsTransmitReservedVendorProvisioning_APPIA_pcsIEEE_LoopbackPassthroughDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsIEEE_LoopbackPassthroughDisable in AQ_PcsTransmitReservedVendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitReservedVendorProvisioning_APPIA_pcsIEEE_LoopbackPassthroughDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsIEEE_LoopbackPassthroughDisable in AQ_PcsTransmitReservedVendorProvisioning_APPIA */
#define word_AQ_PcsTransmitReservedVendorProvisioning_APPIA_pcsIEEE_LoopbackPassthroughDisable u0.word_0

/*! \brief Base register address of structure AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define AQ_PcsTransmitXfiVendorProvisioning_APPIA_baseRegisterAddress 0xC455
/*! \brief MMD address of structure AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define AQ_PcsTransmitXfiVendorProvisioning_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedAWord_0 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedAWord_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedAWord_0 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedAWord_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedAWord_0 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedAWord_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedAWord_1 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedAWord_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedAWord_1 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedAWord_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedAWord_1 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedAWord_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedAWord_2 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedAWord_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedAWord_2 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedAWord_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedAWord_2 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedAWord_2 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedAWord_3 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedAWord_3 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedAWord_3 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedAWord_3 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedAWord_3 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedAWord_3 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedBWord_0 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedBWord_0 4
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedBWord_0 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedBWord_0 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedBWord_0 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedBWord_0 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedBWord_1 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedBWord_1 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedBWord_1 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedBWord_1 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedBWord_1 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedBWord_1 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedBWord_2 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedBWord_2 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedBWord_2 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedBWord_2 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedBWord_2 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedBWord_2 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfiTestPatternSeedBWord_3 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedBWord_3 7
/*! \brief Preprocessor variable to relate field to bit position in structure xfiTestPatternSeedBWord_3 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedBWord_3 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure xfiTestPatternSeedBWord_3 in AQ_PcsTransmitXfiVendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfiVendorProvisioning_APPIA_xfiTestPatternSeedBWord_3 u7.word_7

/*! \brief Base register address of structure AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi0VendorProvisioning_APPIA_baseRegisterAddress 0xC460
/*! \brief MMD address of structure AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi0VendorProvisioning_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi0PcsScramblerDisable in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0PcsScramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0PcsScramblerDisable in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0PcsScramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi0PcsScramblerDisable in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0PcsScramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestSqaureWaveTestDuration in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestSqaureWaveTestDuration 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestSqaureWaveTestDuration in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestSqaureWaveTestDuration u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestSqaureWaveTestDuration in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestSqaureWaveTestDuration u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestDataSelect in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestDataSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestDataSelect in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestDataSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestDataSelect in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestDataSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestModeSelect in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestModeSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestModeSelect in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestModeSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestModeSelect in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestModeSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPrbs_9Enable in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestPrbs_9Enable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPrbs_9Enable in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestPrbs_9Enable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPrbs_9Enable in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestPrbs_9Enable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPrbs_31Enable in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestPrbs_31Enable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPrbs_31Enable in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestPrbs_31Enable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPrbs_31Enable in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestPrbs_31Enable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPatternEnable in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestPatternEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPatternEnable in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestPatternEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPatternEnable in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0TestPatternEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0LocalFaultInject in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0LocalFaultInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0LocalFaultInject in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0LocalFaultInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0LocalFaultInject in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0LocalFaultInject u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0InjectSingleError in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0InjectSingleError 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0InjectSingleError in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0InjectSingleError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0InjectSingleError in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0InjectSingleError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0PcsHighBerInject in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0PcsHighBerInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0PcsHighBerInject in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0PcsHighBerInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0PcsHighBerInject in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0PcsHighBerInject u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0PcsLossOfLockInject in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0PcsLossOfLockInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0PcsLossOfLockInject in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0PcsLossOfLockInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0PcsLossOfLockInject in AQ_PcsTransmitXfi0VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi0VendorProvisioning_APPIA_xfi0PcsLossOfLockInject u1.word_1

/*! \brief Base register address of structure AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi1VendorProvisioning_APPIA_baseRegisterAddress 0xC470
/*! \brief MMD address of structure AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi1VendorProvisioning_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi1PcsScramblerDisable in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1PcsScramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1PcsScramblerDisable in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1PcsScramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi1PcsScramblerDisable in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1PcsScramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestSqaureWaveTestDuration in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestSqaureWaveTestDuration 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestSqaureWaveTestDuration in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestSqaureWaveTestDuration u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestSqaureWaveTestDuration in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestSqaureWaveTestDuration u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestDataSelect in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestDataSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestDataSelect in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestDataSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestDataSelect in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestDataSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestModeSelect in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestModeSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestModeSelect in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestModeSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestModeSelect in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestModeSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestPrbs_9Enable in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestPrbs_9Enable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestPrbs_9Enable in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestPrbs_9Enable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestPrbs_9Enable in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestPrbs_9Enable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestPrbs_31Enable in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestPrbs_31Enable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestPrbs_31Enable in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestPrbs_31Enable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestPrbs_31Enable in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestPrbs_31Enable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestPatternEnable in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestPatternEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestPatternEnable in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestPatternEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestPatternEnable in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1TestPatternEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1LocalFaultInject in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1LocalFaultInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1LocalFaultInject in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1LocalFaultInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1LocalFaultInject in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1LocalFaultInject u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1InjectSingleError in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1InjectSingleError 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1InjectSingleError in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1InjectSingleError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1InjectSingleError in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1InjectSingleError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1PcsHighBerInject in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1PcsHighBerInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1PcsHighBerInject in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1PcsHighBerInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1PcsHighBerInject in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1PcsHighBerInject u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1PcsLossOfLockInject in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1PcsLossOfLockInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1PcsLossOfLockInject in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1PcsLossOfLockInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1PcsLossOfLockInject in AQ_PcsTransmitXfi1VendorProvisioning_APPIA */
#define word_AQ_PcsTransmitXfi1VendorProvisioning_APPIA_xfi1PcsLossOfLockInject u1.word_1

/*! \brief Base register address of structure AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA */
#define AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA_baseRegisterAddress 0xC820
/*! \brief MMD address of structure AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA */
#define AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA */
#define AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA__10gbase_tGoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA */
#define bits_AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA__10gbase_tGoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA */
#define word_AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA__10gbase_tGoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA */
#define AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA__10gbase_tGoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA */
#define bits_AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA__10gbase_tGoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA */
#define word_AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA__10gbase_tGoodFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA */
#define AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA_baseRegisterAddress 0xC822
/*! \brief MMD address of structure AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA */
#define AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA */
#define AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA__10gbase_tErrorFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA */
#define bits_AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA__10gbase_tErrorFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA */
#define word_AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA__10gbase_tErrorFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA */
#define AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA__10gbase_tErrorFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA */
#define bits_AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA__10gbase_tErrorFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA */
#define word_AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA__10gbase_tErrorFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsTransmitXfi0VendorState_APPIA */
#define AQ_PcsTransmitXfi0VendorState_APPIA_baseRegisterAddress 0xC860
/*! \brief MMD address of structure AQ_PcsTransmitXfi0VendorState_APPIA */
#define AQ_PcsTransmitXfi0VendorState_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi0GoodFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_APPIA */
#define AQ_PcsTransmitXfi0VendorState_APPIA_xfi0GoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0GoodFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorState_APPIA_xfi0GoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi0GoodFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_APPIA */
#define word_AQ_PcsTransmitXfi0VendorState_APPIA_xfi0GoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi0GoodFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_APPIA */
#define AQ_PcsTransmitXfi0VendorState_APPIA_xfi0GoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0GoodFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorState_APPIA_xfi0GoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0GoodFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_APPIA */
#define word_AQ_PcsTransmitXfi0VendorState_APPIA_xfi0GoodFrameCounterMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BadFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_APPIA */
#define AQ_PcsTransmitXfi0VendorState_APPIA_xfi0BadFrameCounterLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BadFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorState_APPIA_xfi0BadFrameCounterLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BadFrameCounterLSW in AQ_PcsTransmitXfi0VendorState_APPIA */
#define word_AQ_PcsTransmitXfi0VendorState_APPIA_xfi0BadFrameCounterLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BadFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_APPIA */
#define AQ_PcsTransmitXfi0VendorState_APPIA_xfi0BadFrameCounterMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BadFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_APPIA */
#define bits_AQ_PcsTransmitXfi0VendorState_APPIA_xfi0BadFrameCounterMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BadFrameCounterMSW in AQ_PcsTransmitXfi0VendorState_APPIA */
#define word_AQ_PcsTransmitXfi0VendorState_APPIA_xfi0BadFrameCounterMSW u3.word_3

/*! \brief Base register address of structure AQ_PcsTransmitXfi1VendorState_APPIA */
#define AQ_PcsTransmitXfi1VendorState_APPIA_baseRegisterAddress 0xC870
/*! \brief MMD address of structure AQ_PcsTransmitXfi1VendorState_APPIA */
#define AQ_PcsTransmitXfi1VendorState_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi1GoodFrameCounterLSW in AQ_PcsTransmitXfi1VendorState_APPIA */
#define AQ_PcsTransmitXfi1VendorState_APPIA_xfi1GoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1GoodFrameCounterLSW in AQ_PcsTransmitXfi1VendorState_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorState_APPIA_xfi1GoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi1GoodFrameCounterLSW in AQ_PcsTransmitXfi1VendorState_APPIA */
#define word_AQ_PcsTransmitXfi1VendorState_APPIA_xfi1GoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi1GoodFrameCounterMSW in AQ_PcsTransmitXfi1VendorState_APPIA */
#define AQ_PcsTransmitXfi1VendorState_APPIA_xfi1GoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1GoodFrameCounterMSW in AQ_PcsTransmitXfi1VendorState_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorState_APPIA_xfi1GoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1GoodFrameCounterMSW in AQ_PcsTransmitXfi1VendorState_APPIA */
#define word_AQ_PcsTransmitXfi1VendorState_APPIA_xfi1GoodFrameCounterMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BadFrameCounterLSW in AQ_PcsTransmitXfi1VendorState_APPIA */
#define AQ_PcsTransmitXfi1VendorState_APPIA_xfi1BadFrameCounterLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BadFrameCounterLSW in AQ_PcsTransmitXfi1VendorState_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorState_APPIA_xfi1BadFrameCounterLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BadFrameCounterLSW in AQ_PcsTransmitXfi1VendorState_APPIA */
#define word_AQ_PcsTransmitXfi1VendorState_APPIA_xfi1BadFrameCounterLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BadFrameCounterMSW in AQ_PcsTransmitXfi1VendorState_APPIA */
#define AQ_PcsTransmitXfi1VendorState_APPIA_xfi1BadFrameCounterMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BadFrameCounterMSW in AQ_PcsTransmitXfi1VendorState_APPIA */
#define bits_AQ_PcsTransmitXfi1VendorState_APPIA_xfi1BadFrameCounterMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BadFrameCounterMSW in AQ_PcsTransmitXfi1VendorState_APPIA */
#define word_AQ_PcsTransmitXfi1VendorState_APPIA_xfi1BadFrameCounterMSW u3.word_3

/*! \brief Base register address of structure AQ_PcsTransmitXgsVendorState_APPIA */
#define AQ_PcsTransmitXgsVendorState_APPIA_baseRegisterAddress 0xC880
/*! \brief MMD address of structure AQ_PcsTransmitXgsVendorState_APPIA */
#define AQ_PcsTransmitXgsVendorState_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_0 in AQ_PcsTransmitXgsVendorState_APPIA */
#define AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_0 in AQ_PcsTransmitXgsVendorState_APPIA */
#define bits_AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_0 in AQ_PcsTransmitXgsVendorState_APPIA */
#define word_AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_1 in AQ_PcsTransmitXgsVendorState_APPIA */
#define AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_1 in AQ_PcsTransmitXgsVendorState_APPIA */
#define bits_AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_1 in AQ_PcsTransmitXgsVendorState_APPIA */
#define word_AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_2 in AQ_PcsTransmitXgsVendorState_APPIA */
#define AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_2 in AQ_PcsTransmitXgsVendorState_APPIA */
#define bits_AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_2 in AQ_PcsTransmitXgsVendorState_APPIA */
#define word_AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_2 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_3 in AQ_PcsTransmitXgsVendorState_APPIA */
#define AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_3 3
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_3 in AQ_PcsTransmitXgsVendorState_APPIA */
#define bits_AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_3 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_3 in AQ_PcsTransmitXgsVendorState_APPIA */
#define word_AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_3 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xgsCollisionEventsCounter_4 in AQ_PcsTransmitXgsVendorState_APPIA */
#define AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_4 4
/*! \brief Preprocessor variable to relate field to bit position in structure xgsCollisionEventsCounter_4 in AQ_PcsTransmitXgsVendorState_APPIA */
#define bits_AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_4 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure xgsCollisionEventsCounter_4 in AQ_PcsTransmitXgsVendorState_APPIA */
#define word_AQ_PcsTransmitXgsVendorState_APPIA_xgsCollisionEventsCounter_4 u4.word_4

/*! \brief Base register address of structure AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_baseRegisterAddress 0xCC00
/*! \brief MMD address of structure AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_1 in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_1 in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_1 in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTransmitInvalid_64bBlockDetected in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_xauiTransmitInvalid_64bBlockDetected 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTransmitInvalid_64bBlockDetected in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_xauiTransmitInvalid_64bBlockDetected u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTransmitInvalid_64bBlockDetected in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_xauiTransmitInvalid_64bBlockDetected u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_2 in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_2 in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_2 in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_3 in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_3 in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_3 in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_4 in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_4 in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_4 in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_xfi1TransmitInvalidXgmiiCharacterReceived 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_xfi1TransmitInvalidXgmiiCharacterReceived u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_xfi1TransmitInvalidXgmiiCharacterReceived u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_xfi1TransmitReservedXgmiiCharacterReceived 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_xfi1TransmitReservedXgmiiCharacterReceived u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_xfi1TransmitReservedXgmiiCharacterReceived u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_xfi1Transmit_64bEncodeError 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_xfi1Transmit_64bEncodeError u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_xfi1Transmit_64bEncodeError u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TransmitLofDetected in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_xfi1TransmitLofDetected 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TransmitLofDetected in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_xfi1TransmitLofDetected u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TransmitLofDetected in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_xfi1TransmitLofDetected u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_xfi0TransmitInvalidXgmiiCharacterReceived 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_xfi0TransmitInvalidXgmiiCharacterReceived u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitInvalidXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_xfi0TransmitInvalidXgmiiCharacterReceived u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_xfi0TransmitReservedXgmiiCharacterReceived 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_xfi0TransmitReservedXgmiiCharacterReceived u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitReservedXgmiiCharacterReceived in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_xfi0TransmitReservedXgmiiCharacterReceived u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_xfi0Transmit_64bEncodeError 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_xfi0Transmit_64bEncodeError u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0Transmit_64bEncodeError in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_xfi0Transmit_64bEncodeError u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitLofDetected in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_xfi0TransmitLofDetected 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitLofDetected in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_xfi0TransmitLofDetected u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitLofDetected in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_xfi0TransmitLofDetected u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_5 in AQ_PcsTransmitVendorAlarms_APPIA */
#define AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_5 4
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_5 in AQ_PcsTransmitVendorAlarms_APPIA */
#define bits_AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_5 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_5 in AQ_PcsTransmitVendorAlarms_APPIA */
#define word_AQ_PcsTransmitVendorAlarms_APPIA_reservedPcsTransmitVendorAlarms_5 u4.word_4

/*! \brief Base register address of structure AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_baseRegisterAddress 0xD400
/*! \brief MMD address of structure AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_1Mask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_reservedPcsTransmitVendorAlarms_1Mask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_1Mask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define bits_AQ_PcsTransmitVendorInterruptMask_APPIA_reservedPcsTransmitVendorAlarms_1Mask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_1Mask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define word_AQ_PcsTransmitVendorInterruptMask_APPIA_reservedPcsTransmitVendorAlarms_1Mask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTransmitInvalid_64bBlockDetectedMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_xauiTransmitInvalid_64bBlockDetectedMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTransmitInvalid_64bBlockDetectedMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define bits_AQ_PcsTransmitVendorInterruptMask_APPIA_xauiTransmitInvalid_64bBlockDetectedMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTransmitInvalid_64bBlockDetectedMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define word_AQ_PcsTransmitVendorInterruptMask_APPIA_xauiTransmitInvalid_64bBlockDetectedMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_2Mask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_reservedPcsTransmitVendorAlarms_2Mask 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_2Mask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define bits_AQ_PcsTransmitVendorInterruptMask_APPIA_reservedPcsTransmitVendorAlarms_2Mask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_2Mask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define word_AQ_PcsTransmitVendorInterruptMask_APPIA_reservedPcsTransmitVendorAlarms_2Mask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_3Mask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_reservedPcsTransmitVendorAlarms_3Mask 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_3Mask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define bits_AQ_PcsTransmitVendorInterruptMask_APPIA_reservedPcsTransmitVendorAlarms_3Mask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_3Mask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define word_AQ_PcsTransmitVendorInterruptMask_APPIA_reservedPcsTransmitVendorAlarms_3Mask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_xfi1TransmitInvalidXgmiiCharacterErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define bits_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi1TransmitInvalidXgmiiCharacterErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define word_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi1TransmitInvalidXgmiiCharacterErrorMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_xfi1TransmitReservedXgmiiCharacterErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define bits_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi1TransmitReservedXgmiiCharacterErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define word_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi1TransmitReservedXgmiiCharacterErrorMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_xfi1TransmitEncode_64bErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define bits_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi1TransmitEncode_64bErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define word_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi1TransmitEncode_64bErrorMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TransmitLofDetectedMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_xfi1TransmitLofDetectedMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TransmitLofDetectedMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define bits_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi1TransmitLofDetectedMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TransmitLofDetectedMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define word_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi1TransmitLofDetectedMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_xfi0TransmitInvalidXgmiiCharacterErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define bits_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi0TransmitInvalidXgmiiCharacterErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitInvalidXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define word_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi0TransmitInvalidXgmiiCharacterErrorMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_xfi0TransmitReservedXgmiiCharacterErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define bits_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi0TransmitReservedXgmiiCharacterErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitReservedXgmiiCharacterErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define word_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi0TransmitReservedXgmiiCharacterErrorMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_xfi0TransmitEncode_64bErrorMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define bits_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi0TransmitEncode_64bErrorMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitEncode_64bErrorMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define word_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi0TransmitEncode_64bErrorMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TransmitLofDetectedMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_xfi0TransmitLofDetectedMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TransmitLofDetectedMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define bits_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi0TransmitLofDetectedMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TransmitLofDetectedMask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define word_AQ_PcsTransmitVendorInterruptMask_APPIA_xfi0TransmitLofDetectedMask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsTransmitVendorAlarms_5Mask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define AQ_PcsTransmitVendorInterruptMask_APPIA_reservedPcsTransmitVendorAlarms_5Mask 4
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsTransmitVendorAlarms_5Mask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define bits_AQ_PcsTransmitVendorInterruptMask_APPIA_reservedPcsTransmitVendorAlarms_5Mask u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsTransmitVendorAlarms_5Mask in AQ_PcsTransmitVendorInterruptMask_APPIA */
#define word_AQ_PcsTransmitVendorInterruptMask_APPIA_reservedPcsTransmitVendorAlarms_5Mask u4.word_4

/*! \brief Base register address of structure AQ_PcsTransmitVendorDebug_APPIA */
#define AQ_PcsTransmitVendorDebug_APPIA_baseRegisterAddress 0xD800
/*! \brief MMD address of structure AQ_PcsTransmitVendorDebug_APPIA */
#define AQ_PcsTransmitVendorDebug_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsTxScramblerDisable in AQ_PcsTransmitVendorDebug_APPIA */
#define AQ_PcsTransmitVendorDebug_APPIA_pcsTxScramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTxScramblerDisable in AQ_PcsTransmitVendorDebug_APPIA */
#define bits_AQ_PcsTransmitVendorDebug_APPIA_pcsTxScramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTxScramblerDisable in AQ_PcsTransmitVendorDebug_APPIA */
#define word_AQ_PcsTransmitVendorDebug_APPIA_pcsTxScramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsTxInjectCrcError in AQ_PcsTransmitVendorDebug_APPIA */
#define AQ_PcsTransmitVendorDebug_APPIA_pcsTxInjectCrcError 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTxInjectCrcError in AQ_PcsTransmitVendorDebug_APPIA */
#define bits_AQ_PcsTransmitVendorDebug_APPIA_pcsTxInjectCrcError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTxInjectCrcError in AQ_PcsTransmitVendorDebug_APPIA */
#define word_AQ_PcsTransmitVendorDebug_APPIA_pcsTxInjectCrcError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsTxInjectFrameError in AQ_PcsTransmitVendorDebug_APPIA */
#define AQ_PcsTransmitVendorDebug_APPIA_pcsTxInjectFrameError 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTxInjectFrameError in AQ_PcsTransmitVendorDebug_APPIA */
#define bits_AQ_PcsTransmitVendorDebug_APPIA_pcsTxInjectFrameError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTxInjectFrameError in AQ_PcsTransmitVendorDebug_APPIA */
#define word_AQ_PcsTransmitVendorDebug_APPIA_pcsTxInjectFrameError u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorProvisioning_APPIA */
#define AQ_PcsReceiveVendorProvisioning_APPIA_baseRegisterAddress 0xE400
/*! \brief MMD address of structure AQ_PcsReceiveVendorProvisioning_APPIA */
#define AQ_PcsReceiveVendorProvisioning_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsRxLdpcDecoderControl in AQ_PcsReceiveVendorProvisioning_APPIA */
#define AQ_PcsReceiveVendorProvisioning_APPIA_pcsRxLdpcDecoderControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsRxLdpcDecoderControl in AQ_PcsReceiveVendorProvisioning_APPIA */
#define bits_AQ_PcsReceiveVendorProvisioning_APPIA_pcsRxLdpcDecoderControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsRxLdpcDecoderControl in AQ_PcsReceiveVendorProvisioning_APPIA */
#define word_AQ_PcsReceiveVendorProvisioning_APPIA_pcsRxLdpcDecoderControl u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsRxErrorLdpcFrameEnable in AQ_PcsReceiveVendorProvisioning_APPIA */
#define AQ_PcsReceiveVendorProvisioning_APPIA_pcsRxErrorLdpcFrameEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsRxErrorLdpcFrameEnable in AQ_PcsReceiveVendorProvisioning_APPIA */
#define bits_AQ_PcsReceiveVendorProvisioning_APPIA_pcsRxErrorLdpcFrameEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsRxErrorLdpcFrameEnable in AQ_PcsReceiveVendorProvisioning_APPIA */
#define word_AQ_PcsReceiveVendorProvisioning_APPIA_pcsRxErrorLdpcFrameEnable u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveXfi0Provisioning_APPIA */
#define AQ_PcsReceiveXfi0Provisioning_APPIA_baseRegisterAddress 0xE460
/*! \brief MMD address of structure AQ_PcsReceiveXfi0Provisioning_APPIA */
#define AQ_PcsReceiveXfi0Provisioning_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi0RxDescramblerDisable in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define AQ_PcsReceiveXfi0Provisioning_APPIA_xfi0RxDescramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0RxDescramblerDisable in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define bits_AQ_PcsReceiveXfi0Provisioning_APPIA_xfi0RxDescramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi0RxDescramblerDisable in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define word_AQ_PcsReceiveXfi0Provisioning_APPIA_xfi0RxDescramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestDataSource in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define AQ_PcsReceiveXfi0Provisioning_APPIA_xfi0TestDataSource 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestDataSource in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define bits_AQ_PcsReceiveXfi0Provisioning_APPIA_xfi0TestDataSource u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestDataSource in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define word_AQ_PcsReceiveXfi0Provisioning_APPIA_xfi0TestDataSource u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestModeSelect in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define AQ_PcsReceiveXfi0Provisioning_APPIA_xfi0TestModeSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestModeSelect in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define bits_AQ_PcsReceiveXfi0Provisioning_APPIA_xfi0TestModeSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestModeSelect in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define word_AQ_PcsReceiveXfi0Provisioning_APPIA_xfi0TestModeSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure testPatternEnable in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define AQ_PcsReceiveXfi0Provisioning_APPIA_testPatternEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternEnable in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define bits_AQ_PcsReceiveXfi0Provisioning_APPIA_testPatternEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure testPatternEnable in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define word_AQ_PcsReceiveXfi0Provisioning_APPIA_testPatternEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0LocalFaultInject in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define AQ_PcsReceiveXfi0Provisioning_APPIA_xfi0LocalFaultInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0LocalFaultInject in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define bits_AQ_PcsReceiveXfi0Provisioning_APPIA_xfi0LocalFaultInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0LocalFaultInject in AQ_PcsReceiveXfi0Provisioning_APPIA */
#define word_AQ_PcsReceiveXfi0Provisioning_APPIA_xfi0LocalFaultInject u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveXfi1Provisioning_APPIA */
#define AQ_PcsReceiveXfi1Provisioning_APPIA_baseRegisterAddress 0xE470
/*! \brief MMD address of structure AQ_PcsReceiveXfi1Provisioning_APPIA */
#define AQ_PcsReceiveXfi1Provisioning_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi1RxDescramblerDisable in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define AQ_PcsReceiveXfi1Provisioning_APPIA_xfi1RxDescramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1RxDescramblerDisable in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define bits_AQ_PcsReceiveXfi1Provisioning_APPIA_xfi1RxDescramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi1RxDescramblerDisable in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define word_AQ_PcsReceiveXfi1Provisioning_APPIA_xfi1RxDescramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestDataSource in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define AQ_PcsReceiveXfi1Provisioning_APPIA_xfi1TestDataSource 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestDataSource in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define bits_AQ_PcsReceiveXfi1Provisioning_APPIA_xfi1TestDataSource u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestDataSource in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define word_AQ_PcsReceiveXfi1Provisioning_APPIA_xfi1TestDataSource u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestModeSelect in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define AQ_PcsReceiveXfi1Provisioning_APPIA_xfi1TestModeSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestModeSelect in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define bits_AQ_PcsReceiveXfi1Provisioning_APPIA_xfi1TestModeSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestModeSelect in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define word_AQ_PcsReceiveXfi1Provisioning_APPIA_xfi1TestModeSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure testPatternEnable in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define AQ_PcsReceiveXfi1Provisioning_APPIA_testPatternEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternEnable in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define bits_AQ_PcsReceiveXfi1Provisioning_APPIA_testPatternEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure testPatternEnable in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define word_AQ_PcsReceiveXfi1Provisioning_APPIA_testPatternEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1LocalFaultInject in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define AQ_PcsReceiveXfi1Provisioning_APPIA_xfi1LocalFaultInject 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1LocalFaultInject in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define bits_AQ_PcsReceiveXfi1Provisioning_APPIA_xfi1LocalFaultInject u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1LocalFaultInject in AQ_PcsReceiveXfi1Provisioning_APPIA */
#define word_AQ_PcsReceiveXfi1Provisioning_APPIA_xfi1LocalFaultInject u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorState_APPIA */
#define AQ_PcsReceiveVendorState_APPIA_baseRegisterAddress 0xE800
/*! \brief MMD address of structure AQ_PcsReceiveVendorState_APPIA */
#define AQ_PcsReceiveVendorState_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsRxCurrentValueOfAuxilliaryBit in AQ_PcsReceiveVendorState_APPIA */
#define AQ_PcsReceiveVendorState_APPIA_pcsRxCurrentValueOfAuxilliaryBit 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsRxCurrentValueOfAuxilliaryBit in AQ_PcsReceiveVendorState_APPIA */
#define bits_AQ_PcsReceiveVendorState_APPIA_pcsRxCurrentValueOfAuxilliaryBit u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsRxCurrentValueOfAuxilliaryBit in AQ_PcsReceiveVendorState_APPIA */
#define word_AQ_PcsReceiveVendorState_APPIA_pcsRxCurrentValueOfAuxilliaryBit u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA */
#define AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA_baseRegisterAddress 0xE810
/*! \brief MMD address of structure AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA */
#define AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure crc_8ErrorCounterLSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA */
#define AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA_crc_8ErrorCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure crc_8ErrorCounterLSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA_crc_8ErrorCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure crc_8ErrorCounterLSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA */
#define word_AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA_crc_8ErrorCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure crc_8ErrorCounterMSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA */
#define AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA_crc_8ErrorCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure crc_8ErrorCounterMSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA_crc_8ErrorCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure crc_8ErrorCounterMSW in AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA */
#define word_AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA_crc_8ErrorCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA */
#define AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA_baseRegisterAddress 0xE812
/*! \brief MMD address of structure AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA */
#define AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA */
#define AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA__10gbase_tGoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA */
#define bits_AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA__10gbase_tGoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tGoodFrameCounterLSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA */
#define word_AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA__10gbase_tGoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA */
#define AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA__10gbase_tGoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA */
#define bits_AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA__10gbase_tGoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tGoodFrameCounterMSW in AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA */
#define word_AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA__10gbase_tGoodFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA */
#define AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA_baseRegisterAddress 0xE814
/*! \brief MMD address of structure AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA */
#define AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA */
#define AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA__10gbase_tErrorFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA */
#define bits_AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA__10gbase_tErrorFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tErrorFrameCounterLSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA */
#define word_AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA__10gbase_tErrorFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA */
#define AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA__10gbase_tErrorFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA */
#define bits_AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA__10gbase_tErrorFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tErrorFrameCounterMSW in AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA */
#define word_AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA__10gbase_tErrorFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA */
#define AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA_baseRegisterAddress 0xE820
/*! \brief MMD address of structure AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA */
#define AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure uncorrectedFrameCounterLSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA */
#define AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA_uncorrectedFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure uncorrectedFrameCounterLSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA */
#define bits_AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA_uncorrectedFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure uncorrectedFrameCounterLSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA */
#define word_AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA_uncorrectedFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure uncorrectedFrameCounterMSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA */
#define AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA_uncorrectedFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure uncorrectedFrameCounterMSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA */
#define bits_AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA_uncorrectedFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure uncorrectedFrameCounterMSW in AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA */
#define word_AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA_uncorrectedFrameCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA_baseRegisterAddress 0xE840
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_1IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA_correctedFrames_1IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_1IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA_correctedFrames_1IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_1IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA */
#define word_AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA_correctedFrames_1IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_1IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA_correctedFrames_1IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_1IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA_correctedFrames_1IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_1IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA */
#define word_AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA_correctedFrames_1IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA_baseRegisterAddress 0xE842
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_2IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA_correctedFrames_2IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_2IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA_correctedFrames_2IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_2IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA */
#define word_AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA_correctedFrames_2IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_2IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA_correctedFrames_2IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_2IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA_correctedFrames_2IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_2IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA */
#define word_AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA_correctedFrames_2IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA_baseRegisterAddress 0xE844
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_3IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA_correctedFrames_3IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_3IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA_correctedFrames_3IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_3IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA */
#define word_AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA_correctedFrames_3IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_3IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA_correctedFrames_3IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_3IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA_correctedFrames_3IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_3IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA */
#define word_AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA_correctedFrames_3IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA_baseRegisterAddress 0xE846
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_4IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA_correctedFrames_4IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_4IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA_correctedFrames_4IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_4IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA */
#define word_AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA_correctedFrames_4IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_4IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA_correctedFrames_4IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_4IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA_correctedFrames_4IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_4IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA */
#define word_AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA_correctedFrames_4IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA_baseRegisterAddress 0xE848
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_5IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA_correctedFrames_5IterationCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_5IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA_correctedFrames_5IterationCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_5IterationCounterLSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA */
#define word_AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA_correctedFrames_5IterationCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_5IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA_correctedFrames_5IterationCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_5IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA_correctedFrames_5IterationCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_5IterationCounterMSW in AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA */
#define word_AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA_correctedFrames_5IterationCounterMSW u1.word_1

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_APPIA_baseRegisterAddress 0xE850
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_6IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_APPIA_correctedFrames_6IterationCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_6IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_APPIA_correctedFrames_6IterationCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_6IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_APPIA */
#define word_AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_APPIA_correctedFrames_6IterationCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_APPIA_baseRegisterAddress 0xE851
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_7IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_APPIA_correctedFrames_7IterationCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_7IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_APPIA_correctedFrames_7IterationCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_7IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_APPIA */
#define word_AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_APPIA_correctedFrames_7IterationCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_APPIA_baseRegisterAddress 0xE852
/*! \brief MMD address of structure AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure correctedFrames_8IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_APPIA */
#define AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_APPIA_correctedFrames_8IterationCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure correctedFrames_8IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_APPIA */
#define bits_AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_APPIA_correctedFrames_8IterationCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure correctedFrames_8IterationCounter in AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_APPIA */
#define word_AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_APPIA_correctedFrames_8IterationCounter u0.word_0

/*! \brief Base register address of structure AQ_PcsReceiveXfi0VendorState_APPIA */
#define AQ_PcsReceiveXfi0VendorState_APPIA_baseRegisterAddress 0xE860
/*! \brief MMD address of structure AQ_PcsReceiveXfi0VendorState_APPIA */
#define AQ_PcsReceiveXfi0VendorState_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi0GoodFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_APPIA */
#define AQ_PcsReceiveXfi0VendorState_APPIA_xfi0GoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0GoodFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0GoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi0GoodFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_APPIA */
#define word_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0GoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi0GoodFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_APPIA */
#define AQ_PcsReceiveXfi0VendorState_APPIA_xfi0GoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0GoodFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0GoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi0GoodFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_APPIA */
#define word_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0GoodFrameCounterMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BadFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_APPIA */
#define AQ_PcsReceiveXfi0VendorState_APPIA_xfi0BadFrameCounterLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BadFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0BadFrameCounterLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BadFrameCounterLSW in AQ_PcsReceiveXfi0VendorState_APPIA */
#define word_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0BadFrameCounterLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BadFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_APPIA */
#define AQ_PcsReceiveXfi0VendorState_APPIA_xfi0BadFrameCounterMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BadFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0BadFrameCounterMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BadFrameCounterMSW in AQ_PcsReceiveXfi0VendorState_APPIA */
#define word_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0BadFrameCounterMSW u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BerCounter in AQ_PcsReceiveXfi0VendorState_APPIA */
#define AQ_PcsReceiveXfi0VendorState_APPIA_xfi0BerCounter 4
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BerCounter in AQ_PcsReceiveXfi0VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0BerCounter u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BerCounter in AQ_PcsReceiveXfi0VendorState_APPIA */
#define word_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0BerCounter u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure xfi0ErroredBlockCounter in AQ_PcsReceiveXfi0VendorState_APPIA */
#define AQ_PcsReceiveXfi0VendorState_APPIA_xfi0ErroredBlockCounter 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0ErroredBlockCounter in AQ_PcsReceiveXfi0VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0ErroredBlockCounter u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi0ErroredBlockCounter in AQ_PcsReceiveXfi0VendorState_APPIA */
#define word_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0ErroredBlockCounter u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi0TestPatternErrorCounter in AQ_PcsReceiveXfi0VendorState_APPIA */
#define AQ_PcsReceiveXfi0VendorState_APPIA_xfi0TestPatternErrorCounter 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0TestPatternErrorCounter in AQ_PcsReceiveXfi0VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0TestPatternErrorCounter u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0TestPatternErrorCounter in AQ_PcsReceiveXfi0VendorState_APPIA */
#define word_AQ_PcsReceiveXfi0VendorState_APPIA_xfi0TestPatternErrorCounter u6.word_6

/*! \brief Base register address of structure AQ_PcsReceiveXfi1VendorState_APPIA */
#define AQ_PcsReceiveXfi1VendorState_APPIA_baseRegisterAddress 0xE870
/*! \brief MMD address of structure AQ_PcsReceiveXfi1VendorState_APPIA */
#define AQ_PcsReceiveXfi1VendorState_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure xfi1GoodFrameCounterLSW in AQ_PcsReceiveXfi1VendorState_APPIA */
#define AQ_PcsReceiveXfi1VendorState_APPIA_xfi1GoodFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1GoodFrameCounterLSW in AQ_PcsReceiveXfi1VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1GoodFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xfi1GoodFrameCounterLSW in AQ_PcsReceiveXfi1VendorState_APPIA */
#define word_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1GoodFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xfi1GoodFrameCounterMSW in AQ_PcsReceiveXfi1VendorState_APPIA */
#define AQ_PcsReceiveXfi1VendorState_APPIA_xfi1GoodFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1GoodFrameCounterMSW in AQ_PcsReceiveXfi1VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1GoodFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xfi1GoodFrameCounterMSW in AQ_PcsReceiveXfi1VendorState_APPIA */
#define word_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1GoodFrameCounterMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BadFrameCounterLSW in AQ_PcsReceiveXfi1VendorState_APPIA */
#define AQ_PcsReceiveXfi1VendorState_APPIA_xfi1BadFrameCounterLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BadFrameCounterLSW in AQ_PcsReceiveXfi1VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1BadFrameCounterLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BadFrameCounterLSW in AQ_PcsReceiveXfi1VendorState_APPIA */
#define word_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1BadFrameCounterLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BadFrameCounterMSW in AQ_PcsReceiveXfi1VendorState_APPIA */
#define AQ_PcsReceiveXfi1VendorState_APPIA_xfi1BadFrameCounterMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BadFrameCounterMSW in AQ_PcsReceiveXfi1VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1BadFrameCounterMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BadFrameCounterMSW in AQ_PcsReceiveXfi1VendorState_APPIA */
#define word_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1BadFrameCounterMSW u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BerCounter in AQ_PcsReceiveXfi1VendorState_APPIA */
#define AQ_PcsReceiveXfi1VendorState_APPIA_xfi1BerCounter 4
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BerCounter in AQ_PcsReceiveXfi1VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1BerCounter u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BerCounter in AQ_PcsReceiveXfi1VendorState_APPIA */
#define word_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1BerCounter u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure xfi1ErroredBlockCounter in AQ_PcsReceiveXfi1VendorState_APPIA */
#define AQ_PcsReceiveXfi1VendorState_APPIA_xfi1ErroredBlockCounter 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1ErroredBlockCounter in AQ_PcsReceiveXfi1VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1ErroredBlockCounter u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi1ErroredBlockCounter in AQ_PcsReceiveXfi1VendorState_APPIA */
#define word_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1ErroredBlockCounter u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi1TestPatternErrorCounter in AQ_PcsReceiveXfi1VendorState_APPIA */
#define AQ_PcsReceiveXfi1VendorState_APPIA_xfi1TestPatternErrorCounter 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1TestPatternErrorCounter in AQ_PcsReceiveXfi1VendorState_APPIA */
#define bits_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1TestPatternErrorCounter u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1TestPatternErrorCounter in AQ_PcsReceiveXfi1VendorState_APPIA */
#define word_AQ_PcsReceiveXfi1VendorState_APPIA_xfi1TestPatternErrorCounter u6.word_6

/*! \brief Base register address of structure AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_baseRegisterAddress 0xEC00
/*! \brief MMD address of structure AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure crcError in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_crcError 0
/*! \brief Preprocessor variable to relate field to bit position in structure crcError in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_crcError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure crcError in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_crcError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldpcDecodeFailure in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_ldpcDecodeFailure 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldpcDecodeFailure in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_ldpcDecodeFailure u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldpcDecodeFailure in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_ldpcDecodeFailure u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure invalid_65bBlock in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_invalid_65bBlock 0
/*! \brief Preprocessor variable to relate field to bit position in structure invalid_65bBlock in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_invalid_65bBlock u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure invalid_65bBlock in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_invalid_65bBlock u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure changeInAuxilliaryBit in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_changeInAuxilliaryBit 0
/*! \brief Preprocessor variable to relate field to bit position in structure changeInAuxilliaryBit in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_changeInAuxilliaryBit u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure changeInAuxilliaryBit in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_changeInAuxilliaryBit u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsReceiveVendorAlarms_2 in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_reservedPcsReceiveVendorAlarms_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsReceiveVendorAlarms_2 in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_reservedPcsReceiveVendorAlarms_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsReceiveVendorAlarms_2 in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_reservedPcsReceiveVendorAlarms_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsReceiveVendorAlarms_3 in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_reservedPcsReceiveVendorAlarms_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsReceiveVendorAlarms_3 in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_reservedPcsReceiveVendorAlarms_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsReceiveVendorAlarms_3 in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_reservedPcsReceiveVendorAlarms_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsReceiveVendorAlarms_4 in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_reservedPcsReceiveVendorAlarms_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsReceiveVendorAlarms_4 in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_reservedPcsReceiveVendorAlarms_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsReceiveVendorAlarms_4 in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_reservedPcsReceiveVendorAlarms_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsReceiveVendorAlarms_5 in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_reservedPcsReceiveVendorAlarms_5 4
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsReceiveVendorAlarms_5 in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_reservedPcsReceiveVendorAlarms_5 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsReceiveVendorAlarms_5 in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_reservedPcsReceiveVendorAlarms_5 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure xfi1Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_xfi1Invalid_66bCharacterReceived 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_xfi1Invalid_66bCharacterReceived u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi1Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_xfi1Invalid_66bCharacterReceived u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi0Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_xfi0Invalid_66bCharacterReceived 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_xfi0Invalid_66bCharacterReceived u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi0Invalid_66bCharacterReceived in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_xfi0Invalid_66bCharacterReceived u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi1ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_xfi1ReceiveLinkStatusLatchHigh 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_xfi1ReceiveLinkStatusLatchHigh u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_xfi1ReceiveLinkStatusLatchHigh u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi1HighBerStatus in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_xfi1HighBerStatus 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1HighBerStatus in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_xfi1HighBerStatus u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1HighBerStatus in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_xfi1HighBerStatus u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BlockLockStatus in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_xfi1BlockLockStatus 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BlockLockStatus in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_xfi1BlockLockStatus u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BlockLockStatus in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_xfi1BlockLockStatus u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_xfi0ReceiveLinkStatusLatchHigh 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_xfi0ReceiveLinkStatusLatchHigh u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0ReceiveLinkStatusLatchHigh in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_xfi0ReceiveLinkStatusLatchHigh u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0HighBerStatus in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_xfi0HighBerStatus 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0HighBerStatus in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_xfi0HighBerStatus u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0HighBerStatus in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_xfi0HighBerStatus u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BlockLockStatus in AQ_PcsReceiveVendorAlarms_APPIA */
#define AQ_PcsReceiveVendorAlarms_APPIA_xfi0BlockLockStatus 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BlockLockStatus in AQ_PcsReceiveVendorAlarms_APPIA */
#define bits_AQ_PcsReceiveVendorAlarms_APPIA_xfi0BlockLockStatus u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BlockLockStatus in AQ_PcsReceiveVendorAlarms_APPIA */
#define word_AQ_PcsReceiveVendorAlarms_APPIA_xfi0BlockLockStatus u6.word_6

/*! \brief Base register address of structure AQ_PcsReceiveStandardInterruptMask_APPIA */
#define AQ_PcsReceiveStandardInterruptMask_APPIA_baseRegisterAddress 0xF000
/*! \brief MMD address of structure AQ_PcsReceiveStandardInterruptMask_APPIA */
#define AQ_PcsReceiveStandardInterruptMask_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsReceiveLinkStatusMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define AQ_PcsReceiveStandardInterruptMask_APPIA_pcsReceiveLinkStatusMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsReceiveLinkStatusMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define bits_AQ_PcsReceiveStandardInterruptMask_APPIA_pcsReceiveLinkStatusMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsReceiveLinkStatusMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define word_AQ_PcsReceiveStandardInterruptMask_APPIA_pcsReceiveLinkStatusMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitFaultMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define AQ_PcsReceiveStandardInterruptMask_APPIA_transmitFaultMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure transmitFaultMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define bits_AQ_PcsReceiveStandardInterruptMask_APPIA_transmitFaultMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure transmitFaultMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define word_AQ_PcsReceiveStandardInterruptMask_APPIA_transmitFaultMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure receiveFaultMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define AQ_PcsReceiveStandardInterruptMask_APPIA_receiveFaultMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure receiveFaultMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define bits_AQ_PcsReceiveStandardInterruptMask_APPIA_receiveFaultMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure receiveFaultMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define word_AQ_PcsReceiveStandardInterruptMask_APPIA_receiveFaultMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tPcsBlockLockLatchedMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define AQ_PcsReceiveStandardInterruptMask_APPIA__10gbase_tPcsBlockLockLatchedMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tPcsBlockLockLatchedMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define bits_AQ_PcsReceiveStandardInterruptMask_APPIA__10gbase_tPcsBlockLockLatchedMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tPcsBlockLockLatchedMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define word_AQ_PcsReceiveStandardInterruptMask_APPIA__10gbase_tPcsBlockLockLatchedMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tHighBerLatchedMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define AQ_PcsReceiveStandardInterruptMask_APPIA__10gbase_tHighBerLatchedMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tHighBerLatchedMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define bits_AQ_PcsReceiveStandardInterruptMask_APPIA__10gbase_tHighBerLatchedMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tHighBerLatchedMask in AQ_PcsReceiveStandardInterruptMask_APPIA */
#define word_AQ_PcsReceiveStandardInterruptMask_APPIA__10gbase_tHighBerLatchedMask u2.word_2

/*! \brief Base register address of structure AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_baseRegisterAddress 0xF400
/*! \brief MMD address of structure AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure crcErrorMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_crcErrorMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure crcErrorMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_crcErrorMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure crcErrorMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_crcErrorMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldpcDecodeFailureMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_ldpcDecodeFailureMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldpcDecodeFailureMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_ldpcDecodeFailureMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldpcDecodeFailureMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_ldpcDecodeFailureMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure invalid_65bBlockMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_invalid_65bBlockMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure invalid_65bBlockMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_invalid_65bBlockMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure invalid_65bBlockMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_invalid_65bBlockMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure changeInAuxilliaryBitMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_changeInAuxilliaryBitMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure changeInAuxilliaryBitMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_changeInAuxilliaryBitMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure changeInAuxilliaryBitMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_changeInAuxilliaryBitMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsReceiveVendorAlarms_2Mask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_reservedPcsReceiveVendorAlarms_2Mask 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsReceiveVendorAlarms_2Mask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_reservedPcsReceiveVendorAlarms_2Mask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsReceiveVendorAlarms_2Mask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_reservedPcsReceiveVendorAlarms_2Mask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsReceiveVendorAlarms_3Mask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_reservedPcsReceiveVendorAlarms_3Mask 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsReceiveVendorAlarms_3Mask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_reservedPcsReceiveVendorAlarms_3Mask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsReceiveVendorAlarms_3Mask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_reservedPcsReceiveVendorAlarms_3Mask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsReceiveVendorAlarms_4Mask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_reservedPcsReceiveVendorAlarms_4Mask 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsReceiveVendorAlarms_4Mask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_reservedPcsReceiveVendorAlarms_4Mask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsReceiveVendorAlarms_4Mask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_reservedPcsReceiveVendorAlarms_4Mask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reservedPcsReceiveVendorAlarms_5Mask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_reservedPcsReceiveVendorAlarms_5Mask 4
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPcsReceiveVendorAlarms_5Mask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_reservedPcsReceiveVendorAlarms_5Mask u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure reservedPcsReceiveVendorAlarms_5Mask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_reservedPcsReceiveVendorAlarms_5Mask u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure xfi1Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_xfi1Invalid_66bCharacterReceivedMask 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi1Invalid_66bCharacterReceivedMask u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi1Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi1Invalid_66bCharacterReceivedMask u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi0Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_xfi0Invalid_66bCharacterReceivedMask 5
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi0Invalid_66bCharacterReceivedMask u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure xfi0Invalid_66bCharacterReceivedMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi0Invalid_66bCharacterReceivedMask u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure xfi1ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_xfi1ReceiveLinkStatusLatchHighMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi1ReceiveLinkStatusLatchHighMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi1ReceiveLinkStatusLatchHighMask u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi1HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_xfi1HighBerStatusMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi1HighBerStatusMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi1HighBerStatusMask u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi1BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_xfi1BlockLockStatusMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi1BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi1BlockLockStatusMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi1BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi1BlockLockStatusMask u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_xfi0ReceiveLinkStatusLatchHighMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi0ReceiveLinkStatusLatchHighMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0ReceiveLinkStatusLatchHighMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi0ReceiveLinkStatusLatchHighMask u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_xfi0HighBerStatusMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi0HighBerStatusMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0HighBerStatusMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi0HighBerStatusMask u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure xfi0BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define AQ_PcsReceiveVendorInterruptMask_APPIA_xfi0BlockLockStatusMask 6
/*! \brief Preprocessor variable to relate field to bit position in structure xfi0BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define bits_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi0BlockLockStatusMask u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure xfi0BlockLockStatusMask in AQ_PcsReceiveVendorInterruptMask_APPIA */
#define word_AQ_PcsReceiveVendorInterruptMask_APPIA_xfi0BlockLockStatusMask u6.word_6

/*! \brief Base register address of structure AQ_PcsReceiveVendorDebug_APPIA */
#define AQ_PcsReceiveVendorDebug_APPIA_baseRegisterAddress 0xF800
/*! \brief MMD address of structure AQ_PcsReceiveVendorDebug_APPIA */
#define AQ_PcsReceiveVendorDebug_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure pcsRxDescramblerDisable in AQ_PcsReceiveVendorDebug_APPIA */
#define AQ_PcsReceiveVendorDebug_APPIA_pcsRxDescramblerDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsRxDescramblerDisable in AQ_PcsReceiveVendorDebug_APPIA */
#define bits_AQ_PcsReceiveVendorDebug_APPIA_pcsRxDescramblerDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsRxDescramblerDisable in AQ_PcsReceiveVendorDebug_APPIA */
#define word_AQ_PcsReceiveVendorDebug_APPIA_pcsRxDescramblerDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsNetworkLoopbackMerge in AQ_PcsReceiveVendorDebug_APPIA */
#define AQ_PcsReceiveVendorDebug_APPIA_pcsNetworkLoopbackMerge 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsNetworkLoopbackMerge in AQ_PcsReceiveVendorDebug_APPIA */
#define bits_AQ_PcsReceiveVendorDebug_APPIA_pcsNetworkLoopbackMerge u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsNetworkLoopbackMerge in AQ_PcsReceiveVendorDebug_APPIA */
#define word_AQ_PcsReceiveVendorDebug_APPIA_pcsNetworkLoopbackMerge u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsNetworkLoopbackPassThrough in AQ_PcsReceiveVendorDebug_APPIA */
#define AQ_PcsReceiveVendorDebug_APPIA_pcsNetworkLoopbackPassThrough 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsNetworkLoopbackPassThrough in AQ_PcsReceiveVendorDebug_APPIA */
#define bits_AQ_PcsReceiveVendorDebug_APPIA_pcsNetworkLoopbackPassThrough u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsNetworkLoopbackPassThrough in AQ_PcsReceiveVendorDebug_APPIA */
#define word_AQ_PcsReceiveVendorDebug_APPIA_pcsNetworkLoopbackPassThrough u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsNetworkLoopback in AQ_PcsReceiveVendorDebug_APPIA */
#define AQ_PcsReceiveVendorDebug_APPIA_pcsNetworkLoopback 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsNetworkLoopback in AQ_PcsReceiveVendorDebug_APPIA */
#define bits_AQ_PcsReceiveVendorDebug_APPIA_pcsNetworkLoopback u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsNetworkLoopback in AQ_PcsReceiveVendorDebug_APPIA */
#define word_AQ_PcsReceiveVendorDebug_APPIA_pcsNetworkLoopback u0.word_0

/*! \brief Base register address of structure AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_baseRegisterAddress 0xFC00
/*! \brief MMD address of structure AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_mmdAddress 0x03
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarm_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_standardAlarm_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarm_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_standardAlarm_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarm_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_standardAlarm_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarm_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_standardAlarm_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarm_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_standardAlarm_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarm_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_standardAlarm_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarm_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_standardAlarm_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarm_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_standardAlarm_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarm_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_standardAlarm_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_4Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_4Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_4Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_4Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_4Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_4Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_5Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_5Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_5Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_5Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_5Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_5Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_1Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_2Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_3Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_4Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_4Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_4Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_4Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_4Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_4Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_5Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_5Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_5Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_5Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_5Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_5Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_6Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_6Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_6Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_6Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_6Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_6Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_7Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_7Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_7Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_7Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_7Interrupt in AQ_PcsVendorGlobalInterruptFlags_APPIA */
#define word_AQ_PcsVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_7Interrupt u0.word_0
#endif
/*@}*/
/*@}*/
