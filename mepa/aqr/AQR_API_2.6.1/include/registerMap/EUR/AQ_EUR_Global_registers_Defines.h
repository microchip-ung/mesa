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
*   for the Global Registers block.
*/

/*! \defgroup Global_registers_Defines Global Registers Defines
*   This module contains the compiler assist macros and doxygen comments
*   for the Global Registers block.
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
*   This file contains the compiler assist macros for the registers contained in the Global Registers block.
*
*
***********************************************************************/


/*@{*/
#ifndef AQ_EUR_GLOBAL_REGS_DEFINES_HEADER
#define AQ_EUR_GLOBAL_REGS_DEFINES_HEADER


/*-----------------------------------------------------------------------------*/
/*Access macro definitions                                                     */
/*-----------------------------------------------------------------------------*/
/*! \brief Base register address of structure AQ_GlobalStandardControl_1_EUR */
#define AQ_GlobalStandardControl_1_EUR_baseRegisterAddress 0x0000
/*! \brief MMD address of structure AQ_GlobalStandardControl_1_EUR */
#define AQ_GlobalStandardControl_1_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure softReset in AQ_GlobalStandardControl_1_EUR */
#define AQ_GlobalStandardControl_1_EUR_softReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure softReset in AQ_GlobalStandardControl_1_EUR */
#define bits_AQ_GlobalStandardControl_1_EUR_softReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure softReset in AQ_GlobalStandardControl_1_EUR */
#define word_AQ_GlobalStandardControl_1_EUR_softReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowPower in AQ_GlobalStandardControl_1_EUR */
#define AQ_GlobalStandardControl_1_EUR_lowPower 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowPower in AQ_GlobalStandardControl_1_EUR */
#define bits_AQ_GlobalStandardControl_1_EUR_lowPower u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowPower in AQ_GlobalStandardControl_1_EUR */
#define word_AQ_GlobalStandardControl_1_EUR_lowPower u0.word_0

/*! \brief Base register address of structure AQ_GlobalStandardDeviceIdentifier_EUR */
#define AQ_GlobalStandardDeviceIdentifier_EUR_baseRegisterAddress 0x0002
/*! \brief MMD address of structure AQ_GlobalStandardDeviceIdentifier_EUR */
#define AQ_GlobalStandardDeviceIdentifier_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdMSW in AQ_GlobalStandardDeviceIdentifier_EUR */
#define AQ_GlobalStandardDeviceIdentifier_EUR_deviceIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdMSW in AQ_GlobalStandardDeviceIdentifier_EUR */
#define bits_AQ_GlobalStandardDeviceIdentifier_EUR_deviceIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdMSW in AQ_GlobalStandardDeviceIdentifier_EUR */
#define word_AQ_GlobalStandardDeviceIdentifier_EUR_deviceIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdLSW in AQ_GlobalStandardDeviceIdentifier_EUR */
#define AQ_GlobalStandardDeviceIdentifier_EUR_deviceIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdLSW in AQ_GlobalStandardDeviceIdentifier_EUR */
#define bits_AQ_GlobalStandardDeviceIdentifier_EUR_deviceIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdLSW in AQ_GlobalStandardDeviceIdentifier_EUR */
#define word_AQ_GlobalStandardDeviceIdentifier_EUR_deviceIdLSW u1.word_1

/*! \brief Base register address of structure AQ_GlobalStandardDevicesInPackage_EUR */
#define AQ_GlobalStandardDevicesInPackage_EUR_baseRegisterAddress 0x0005
/*! \brief MMD address of structure AQ_GlobalStandardDevicesInPackage_EUR */
#define AQ_GlobalStandardDevicesInPackage_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define AQ_GlobalStandardDevicesInPackage_EUR_autonegotiationPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define bits_AQ_GlobalStandardDevicesInPackage_EUR_autonegotiationPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define word_AQ_GlobalStandardDevicesInPackage_EUR_autonegotiationPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tcPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define AQ_GlobalStandardDevicesInPackage_EUR_tcPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure tcPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define bits_AQ_GlobalStandardDevicesInPackage_EUR_tcPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tcPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define word_AQ_GlobalStandardDevicesInPackage_EUR_tcPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure dteXsPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define AQ_GlobalStandardDevicesInPackage_EUR_dteXsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure dteXsPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define bits_AQ_GlobalStandardDevicesInPackage_EUR_dteXsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure dteXsPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define word_AQ_GlobalStandardDevicesInPackage_EUR_dteXsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_Present in AQ_GlobalStandardDevicesInPackage_EUR */
#define AQ_GlobalStandardDevicesInPackage_EUR_phyXS_Present 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_Present in AQ_GlobalStandardDevicesInPackage_EUR */
#define bits_AQ_GlobalStandardDevicesInPackage_EUR_phyXS_Present u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_Present in AQ_GlobalStandardDevicesInPackage_EUR */
#define word_AQ_GlobalStandardDevicesInPackage_EUR_phyXS_Present u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define AQ_GlobalStandardDevicesInPackage_EUR_pcsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define bits_AQ_GlobalStandardDevicesInPackage_EUR_pcsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define word_AQ_GlobalStandardDevicesInPackage_EUR_pcsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure wisPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define AQ_GlobalStandardDevicesInPackage_EUR_wisPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure wisPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define bits_AQ_GlobalStandardDevicesInPackage_EUR_wisPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure wisPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define word_AQ_GlobalStandardDevicesInPackage_EUR_wisPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define AQ_GlobalStandardDevicesInPackage_EUR_pmaPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define bits_AQ_GlobalStandardDevicesInPackage_EUR_pmaPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define word_AQ_GlobalStandardDevicesInPackage_EUR_pmaPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clause_22RegistersPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define AQ_GlobalStandardDevicesInPackage_EUR_clause_22RegistersPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22RegistersPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define bits_AQ_GlobalStandardDevicesInPackage_EUR_clause_22RegistersPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clause_22RegistersPresent in AQ_GlobalStandardDevicesInPackage_EUR */
#define word_AQ_GlobalStandardDevicesInPackage_EUR_clause_22RegistersPresent u0.word_0

/*! \brief Base register address of structure AQ_GlobalStandardVendorDevicesInPackage_EUR */
#define AQ_GlobalStandardVendorDevicesInPackage_EUR_baseRegisterAddress 0x0006
/*! \brief MMD address of structure AQ_GlobalStandardVendorDevicesInPackage_EUR */
#define AQ_GlobalStandardVendorDevicesInPackage_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_2Present in AQ_GlobalStandardVendorDevicesInPackage_EUR */
#define AQ_GlobalStandardVendorDevicesInPackage_EUR_vendorSpecificDevice_2Present 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_2Present in AQ_GlobalStandardVendorDevicesInPackage_EUR */
#define bits_AQ_GlobalStandardVendorDevicesInPackage_EUR_vendorSpecificDevice_2Present u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_2Present in AQ_GlobalStandardVendorDevicesInPackage_EUR */
#define word_AQ_GlobalStandardVendorDevicesInPackage_EUR_vendorSpecificDevice_2Present u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_1Present in AQ_GlobalStandardVendorDevicesInPackage_EUR */
#define AQ_GlobalStandardVendorDevicesInPackage_EUR_vendorSpecificDevice_1Present 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_1Present in AQ_GlobalStandardVendorDevicesInPackage_EUR */
#define bits_AQ_GlobalStandardVendorDevicesInPackage_EUR_vendorSpecificDevice_1Present u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_1Present in AQ_GlobalStandardVendorDevicesInPackage_EUR */
#define word_AQ_GlobalStandardVendorDevicesInPackage_EUR_vendorSpecificDevice_1Present u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clause_22ExtensionPresent in AQ_GlobalStandardVendorDevicesInPackage_EUR */
#define AQ_GlobalStandardVendorDevicesInPackage_EUR_clause_22ExtensionPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22ExtensionPresent in AQ_GlobalStandardVendorDevicesInPackage_EUR */
#define bits_AQ_GlobalStandardVendorDevicesInPackage_EUR_clause_22ExtensionPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clause_22ExtensionPresent in AQ_GlobalStandardVendorDevicesInPackage_EUR */
#define word_AQ_GlobalStandardVendorDevicesInPackage_EUR_clause_22ExtensionPresent u0.word_0

/*! \brief Base register address of structure AQ_GlobalStandardStatus_2_EUR */
#define AQ_GlobalStandardStatus_2_EUR_baseRegisterAddress 0x0008
/*! \brief MMD address of structure AQ_GlobalStandardStatus_2_EUR */
#define AQ_GlobalStandardStatus_2_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure devicePresent in AQ_GlobalStandardStatus_2_EUR */
#define AQ_GlobalStandardStatus_2_EUR_devicePresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure devicePresent in AQ_GlobalStandardStatus_2_EUR */
#define bits_AQ_GlobalStandardStatus_2_EUR_devicePresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure devicePresent in AQ_GlobalStandardStatus_2_EUR */
#define word_AQ_GlobalStandardStatus_2_EUR_devicePresent u0.word_0

/*! \brief Base register address of structure AQ_GlobalStandardPackageIdentifier_EUR */
#define AQ_GlobalStandardPackageIdentifier_EUR_baseRegisterAddress 0x000E
/*! \brief MMD address of structure AQ_GlobalStandardPackageIdentifier_EUR */
#define AQ_GlobalStandardPackageIdentifier_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure packageIdMSW in AQ_GlobalStandardPackageIdentifier_EUR */
#define AQ_GlobalStandardPackageIdentifier_EUR_packageIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdMSW in AQ_GlobalStandardPackageIdentifier_EUR */
#define bits_AQ_GlobalStandardPackageIdentifier_EUR_packageIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure packageIdMSW in AQ_GlobalStandardPackageIdentifier_EUR */
#define word_AQ_GlobalStandardPackageIdentifier_EUR_packageIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure packageIdLSW in AQ_GlobalStandardPackageIdentifier_EUR */
#define AQ_GlobalStandardPackageIdentifier_EUR_packageIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdLSW in AQ_GlobalStandardPackageIdentifier_EUR */
#define bits_AQ_GlobalStandardPackageIdentifier_EUR_packageIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure packageIdLSW in AQ_GlobalStandardPackageIdentifier_EUR */
#define word_AQ_GlobalStandardPackageIdentifier_EUR_packageIdLSW u1.word_1

/*! \brief Base register address of structure AQ_GlobalFirmwareID_EUR */
#define AQ_GlobalFirmwareID_EUR_baseRegisterAddress 0x0020
/*! \brief MMD address of structure AQ_GlobalFirmwareID_EUR */
#define AQ_GlobalFirmwareID_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure firmwareMajorRevisionNumber in AQ_GlobalFirmwareID_EUR */
#define AQ_GlobalFirmwareID_EUR_firmwareMajorRevisionNumber 0
/*! \brief Preprocessor variable to relate field to bit position in structure firmwareMajorRevisionNumber in AQ_GlobalFirmwareID_EUR */
#define bits_AQ_GlobalFirmwareID_EUR_firmwareMajorRevisionNumber u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure firmwareMajorRevisionNumber in AQ_GlobalFirmwareID_EUR */
#define word_AQ_GlobalFirmwareID_EUR_firmwareMajorRevisionNumber u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure firmwareMinorRevisionNumber in AQ_GlobalFirmwareID_EUR */
#define AQ_GlobalFirmwareID_EUR_firmwareMinorRevisionNumber 0
/*! \brief Preprocessor variable to relate field to bit position in structure firmwareMinorRevisionNumber in AQ_GlobalFirmwareID_EUR */
#define bits_AQ_GlobalFirmwareID_EUR_firmwareMinorRevisionNumber u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure firmwareMinorRevisionNumber in AQ_GlobalFirmwareID_EUR */
#define word_AQ_GlobalFirmwareID_EUR_firmwareMinorRevisionNumber u0.word_0

/*! \brief Base register address of structure AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_baseRegisterAddress 0x0080
/*! \brief MMD address of structure AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure matchingDeviceAddress_0 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure matchingDeviceAddress_0 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure matchingDeviceAddress_0 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure remappedMMD_Address_0 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure remappedMMD_Address_0 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure remappedMMD_Address_0 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure matchingMMD_Address_0 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_0 1
/*! \brief Preprocessor variable to relate field to bit position in structure matchingMMD_Address_0 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_0 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure matchingMMD_Address_0 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_0 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure matchingDeviceAddress_1 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_1 2
/*! \brief Preprocessor variable to relate field to bit position in structure matchingDeviceAddress_1 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_1 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure matchingDeviceAddress_1 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_1 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure remappedMMD_Address_1 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_1 2
/*! \brief Preprocessor variable to relate field to bit position in structure remappedMMD_Address_1 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_1 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure remappedMMD_Address_1 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_1 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure matchingMMD_Address_1 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_1 3
/*! \brief Preprocessor variable to relate field to bit position in structure matchingMMD_Address_1 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_1 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure matchingMMD_Address_1 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_1 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure matchingDeviceAddress_2 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_2 4
/*! \brief Preprocessor variable to relate field to bit position in structure matchingDeviceAddress_2 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_2 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure matchingDeviceAddress_2 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_2 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure remappedMMD_Address_2 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_2 4
/*! \brief Preprocessor variable to relate field to bit position in structure remappedMMD_Address_2 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_2 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure remappedMMD_Address_2 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_2 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure matchingMMD_Address_2 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_2 5
/*! \brief Preprocessor variable to relate field to bit position in structure matchingMMD_Address_2 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_2 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure matchingMMD_Address_2 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_2 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure matchingDeviceAddress_3 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_3 6
/*! \brief Preprocessor variable to relate field to bit position in structure matchingDeviceAddress_3 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_3 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure matchingDeviceAddress_3 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_3 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure remappedMMD_Address_3 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_3 6
/*! \brief Preprocessor variable to relate field to bit position in structure remappedMMD_Address_3 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_3 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure remappedMMD_Address_3 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_3 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure matchingMMD_Address_3 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_3 7
/*! \brief Preprocessor variable to relate field to bit position in structure matchingMMD_Address_3 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_3 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure matchingMMD_Address_3 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_3 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure matchingDeviceAddress_4 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_4 8
/*! \brief Preprocessor variable to relate field to bit position in structure matchingDeviceAddress_4 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_4 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure matchingDeviceAddress_4 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_4 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure remappedMMD_Address_4 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_4 8
/*! \brief Preprocessor variable to relate field to bit position in structure remappedMMD_Address_4 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_4 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure remappedMMD_Address_4 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_4 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure matchingMMD_Address_4 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_4 9
/*! \brief Preprocessor variable to relate field to bit position in structure matchingMMD_Address_4 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_4 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure matchingMMD_Address_4 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_4 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure matchingDeviceAddress_5 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_5 10
/*! \brief Preprocessor variable to relate field to bit position in structure matchingDeviceAddress_5 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_5 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure matchingDeviceAddress_5 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_5 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure remappedMMD_Address_5 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_5 10
/*! \brief Preprocessor variable to relate field to bit position in structure remappedMMD_Address_5 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_5 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure remappedMMD_Address_5 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_5 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure matchingMMD_Address_5 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_5 11
/*! \brief Preprocessor variable to relate field to bit position in structure matchingMMD_Address_5 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_5 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure matchingMMD_Address_5 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_5 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure matchingDeviceAddress_6 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_6 12
/*! \brief Preprocessor variable to relate field to bit position in structure matchingDeviceAddress_6 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_6 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure matchingDeviceAddress_6 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_6 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure remappedMMD_Address_6 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_6 12
/*! \brief Preprocessor variable to relate field to bit position in structure remappedMMD_Address_6 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_6 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure remappedMMD_Address_6 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_6 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure matchingMMD_Address_6 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_6 13
/*! \brief Preprocessor variable to relate field to bit position in structure matchingMMD_Address_6 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_6 u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure matchingMMD_Address_6 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_6 u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure matchingDeviceAddress_7 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_7 14
/*! \brief Preprocessor variable to relate field to bit position in structure matchingDeviceAddress_7 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_7 u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure matchingDeviceAddress_7 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingDeviceAddress_7 u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure remappedMMD_Address_7 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_7 14
/*! \brief Preprocessor variable to relate field to bit position in structure remappedMMD_Address_7 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_7 u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure remappedMMD_Address_7 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_remappedMMD_Address_7 u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure matchingMMD_Address_7 in AQ_GlobalProgrammableMMD_Register_EUR */
#define AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_7 15
/*! \brief Preprocessor variable to relate field to bit position in structure matchingMMD_Address_7 in AQ_GlobalProgrammableMMD_Register_EUR */
#define bits_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_7 u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure matchingMMD_Address_7 in AQ_GlobalProgrammableMMD_Register_EUR */
#define word_AQ_GlobalProgrammableMMD_Register_EUR_matchingMMD_Address_7 u15.word_15

/*! \brief Base register address of structure AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_baseRegisterAddress 0x0100
/*! \brief MMD address of structure AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure nvrExecuteOperation in AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_nvrExecuteOperation 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrExecuteOperation in AQ_GlobalNvrInterface_EUR */
#define bits_AQ_GlobalNvrInterface_EUR_nvrExecuteOperation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrExecuteOperation in AQ_GlobalNvrInterface_EUR */
#define word_AQ_GlobalNvrInterface_EUR_nvrExecuteOperation u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrWriteMode in AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_nvrWriteMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrWriteMode in AQ_GlobalNvrInterface_EUR */
#define bits_AQ_GlobalNvrInterface_EUR_nvrWriteMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrWriteMode in AQ_GlobalNvrInterface_EUR */
#define word_AQ_GlobalNvrInterface_EUR_nvrWriteMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure freezeNvrCrc in AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_freezeNvrCrc 0
/*! \brief Preprocessor variable to relate field to bit position in structure freezeNvrCrc in AQ_GlobalNvrInterface_EUR */
#define bits_AQ_GlobalNvrInterface_EUR_freezeNvrCrc u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure freezeNvrCrc in AQ_GlobalNvrInterface_EUR */
#define word_AQ_GlobalNvrInterface_EUR_freezeNvrCrc u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure resetNvrCrc in AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_resetNvrCrc 0
/*! \brief Preprocessor variable to relate field to bit position in structure resetNvrCrc in AQ_GlobalNvrInterface_EUR */
#define bits_AQ_GlobalNvrInterface_EUR_resetNvrCrc u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure resetNvrCrc in AQ_GlobalNvrInterface_EUR */
#define word_AQ_GlobalNvrInterface_EUR_resetNvrCrc u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrBurst in AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_nvrBurst 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrBurst in AQ_GlobalNvrInterface_EUR */
#define bits_AQ_GlobalNvrInterface_EUR_nvrBurst u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrBurst in AQ_GlobalNvrInterface_EUR */
#define word_AQ_GlobalNvrInterface_EUR_nvrBurst u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrBusy in AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_nvrBusy 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrBusy in AQ_GlobalNvrInterface_EUR */
#define bits_AQ_GlobalNvrInterface_EUR_nvrBusy u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrBusy in AQ_GlobalNvrInterface_EUR */
#define word_AQ_GlobalNvrInterface_EUR_nvrBusy u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrOpcode in AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_nvrOpcode 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrOpcode in AQ_GlobalNvrInterface_EUR */
#define bits_AQ_GlobalNvrInterface_EUR_nvrOpcode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrOpcode in AQ_GlobalNvrInterface_EUR */
#define word_AQ_GlobalNvrInterface_EUR_nvrOpcode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrMailboxCrc in AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_nvrMailboxCrc 1
/*! \brief Preprocessor variable to relate field to bit position in structure nvrMailboxCrc in AQ_GlobalNvrInterface_EUR */
#define bits_AQ_GlobalNvrInterface_EUR_nvrMailboxCrc u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure nvrMailboxCrc in AQ_GlobalNvrInterface_EUR */
#define word_AQ_GlobalNvrInterface_EUR_nvrMailboxCrc u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure nvrAddressMSW in AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_nvrAddressMSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure nvrAddressMSW in AQ_GlobalNvrInterface_EUR */
#define bits_AQ_GlobalNvrInterface_EUR_nvrAddressMSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure nvrAddressMSW in AQ_GlobalNvrInterface_EUR */
#define word_AQ_GlobalNvrInterface_EUR_nvrAddressMSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure nvrAddressLSW in AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_nvrAddressLSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure nvrAddressLSW in AQ_GlobalNvrInterface_EUR */
#define bits_AQ_GlobalNvrInterface_EUR_nvrAddressLSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure nvrAddressLSW in AQ_GlobalNvrInterface_EUR */
#define word_AQ_GlobalNvrInterface_EUR_nvrAddressLSW u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure nvrDataMSW in AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_nvrDataMSW 4
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDataMSW in AQ_GlobalNvrInterface_EUR */
#define bits_AQ_GlobalNvrInterface_EUR_nvrDataMSW u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure nvrDataMSW in AQ_GlobalNvrInterface_EUR */
#define word_AQ_GlobalNvrInterface_EUR_nvrDataMSW u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure nvrDataLSW in AQ_GlobalNvrInterface_EUR */
#define AQ_GlobalNvrInterface_EUR_nvrDataLSW 5
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDataLSW in AQ_GlobalNvrInterface_EUR */
#define bits_AQ_GlobalNvrInterface_EUR_nvrDataLSW u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure nvrDataLSW in AQ_GlobalNvrInterface_EUR */
#define word_AQ_GlobalNvrInterface_EUR_nvrDataLSW u5.word_5

/*! \brief Base register address of structure AQ_GlobalMailboxInterface_EUR */
#define AQ_GlobalMailboxInterface_EUR_baseRegisterAddress 0x0200
/*! \brief MMD address of structure AQ_GlobalMailboxInterface_EUR */
#define AQ_GlobalMailboxInterface_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxExecuteOperation in AQ_GlobalMailboxInterface_EUR */
#define AQ_GlobalMailboxInterface_EUR_upMailboxExecuteOperation 0
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxExecuteOperation in AQ_GlobalMailboxInterface_EUR */
#define bits_AQ_GlobalMailboxInterface_EUR_upMailboxExecuteOperation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxExecuteOperation in AQ_GlobalMailboxInterface_EUR */
#define word_AQ_GlobalMailboxInterface_EUR_upMailboxExecuteOperation u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxWriteMode in AQ_GlobalMailboxInterface_EUR */
#define AQ_GlobalMailboxInterface_EUR_upMailboxWriteMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxWriteMode in AQ_GlobalMailboxInterface_EUR */
#define bits_AQ_GlobalMailboxInterface_EUR_upMailboxWriteMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxWriteMode in AQ_GlobalMailboxInterface_EUR */
#define word_AQ_GlobalMailboxInterface_EUR_upMailboxWriteMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure resetUpMailboxCrc in AQ_GlobalMailboxInterface_EUR */
#define AQ_GlobalMailboxInterface_EUR_resetUpMailboxCrc 0
/*! \brief Preprocessor variable to relate field to bit position in structure resetUpMailboxCrc in AQ_GlobalMailboxInterface_EUR */
#define bits_AQ_GlobalMailboxInterface_EUR_resetUpMailboxCrc u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure resetUpMailboxCrc in AQ_GlobalMailboxInterface_EUR */
#define word_AQ_GlobalMailboxInterface_EUR_resetUpMailboxCrc u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxBusy in AQ_GlobalMailboxInterface_EUR */
#define AQ_GlobalMailboxInterface_EUR_upMailboxBusy 0
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxBusy in AQ_GlobalMailboxInterface_EUR */
#define bits_AQ_GlobalMailboxInterface_EUR_upMailboxBusy u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxBusy in AQ_GlobalMailboxInterface_EUR */
#define word_AQ_GlobalMailboxInterface_EUR_upMailboxBusy u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxCrc in AQ_GlobalMailboxInterface_EUR */
#define AQ_GlobalMailboxInterface_EUR_upMailboxCrc 1
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxCrc in AQ_GlobalMailboxInterface_EUR */
#define bits_AQ_GlobalMailboxInterface_EUR_upMailboxCrc u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxCrc in AQ_GlobalMailboxInterface_EUR */
#define word_AQ_GlobalMailboxInterface_EUR_upMailboxCrc u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxAddressMSW in AQ_GlobalMailboxInterface_EUR */
#define AQ_GlobalMailboxInterface_EUR_upMailboxAddressMSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxAddressMSW in AQ_GlobalMailboxInterface_EUR */
#define bits_AQ_GlobalMailboxInterface_EUR_upMailboxAddressMSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxAddressMSW in AQ_GlobalMailboxInterface_EUR */
#define word_AQ_GlobalMailboxInterface_EUR_upMailboxAddressMSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxAddressLSW in AQ_GlobalMailboxInterface_EUR */
#define AQ_GlobalMailboxInterface_EUR_upMailboxAddressLSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxAddressLSW in AQ_GlobalMailboxInterface_EUR */
#define bits_AQ_GlobalMailboxInterface_EUR_upMailboxAddressLSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxAddressLSW in AQ_GlobalMailboxInterface_EUR */
#define word_AQ_GlobalMailboxInterface_EUR_upMailboxAddressLSW u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxAddressLSW_Don_tCare in AQ_GlobalMailboxInterface_EUR */
#define AQ_GlobalMailboxInterface_EUR_upMailboxAddressLSW_Don_tCare 3
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxAddressLSW_Don_tCare in AQ_GlobalMailboxInterface_EUR */
#define bits_AQ_GlobalMailboxInterface_EUR_upMailboxAddressLSW_Don_tCare u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxAddressLSW_Don_tCare in AQ_GlobalMailboxInterface_EUR */
#define word_AQ_GlobalMailboxInterface_EUR_upMailboxAddressLSW_Don_tCare u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxDataMSW in AQ_GlobalMailboxInterface_EUR */
#define AQ_GlobalMailboxInterface_EUR_upMailboxDataMSW 4
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxDataMSW in AQ_GlobalMailboxInterface_EUR */
#define bits_AQ_GlobalMailboxInterface_EUR_upMailboxDataMSW u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxDataMSW in AQ_GlobalMailboxInterface_EUR */
#define word_AQ_GlobalMailboxInterface_EUR_upMailboxDataMSW u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxDataLSW in AQ_GlobalMailboxInterface_EUR */
#define AQ_GlobalMailboxInterface_EUR_upMailboxDataLSW 5
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxDataLSW in AQ_GlobalMailboxInterface_EUR */
#define bits_AQ_GlobalMailboxInterface_EUR_upMailboxDataLSW u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxDataLSW in AQ_GlobalMailboxInterface_EUR */
#define word_AQ_GlobalMailboxInterface_EUR_upMailboxDataLSW u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxCrcReadEnable in AQ_GlobalMailboxInterface_EUR */
#define AQ_GlobalMailboxInterface_EUR_upMailboxCrcReadEnable 6
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxCrcReadEnable in AQ_GlobalMailboxInterface_EUR */
#define bits_AQ_GlobalMailboxInterface_EUR_upMailboxCrcReadEnable u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxCrcReadEnable in AQ_GlobalMailboxInterface_EUR */
#define word_AQ_GlobalMailboxInterface_EUR_upMailboxCrcReadEnable u6.word_6

/*! \brief Base register address of structure AQ_GlobalMicroprocessorScratchPad_EUR */
#define AQ_GlobalMicroprocessorScratchPad_EUR_baseRegisterAddress 0x0300
/*! \brief MMD address of structure AQ_GlobalMicroprocessorScratchPad_EUR */
#define AQ_GlobalMicroprocessorScratchPad_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_1 in AQ_GlobalMicroprocessorScratchPad_EUR */
#define AQ_GlobalMicroprocessorScratchPad_EUR_scratchPad_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_1 in AQ_GlobalMicroprocessorScratchPad_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_EUR_scratchPad_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_1 in AQ_GlobalMicroprocessorScratchPad_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_EUR_scratchPad_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_2 in AQ_GlobalMicroprocessorScratchPad_EUR */
#define AQ_GlobalMicroprocessorScratchPad_EUR_scratchPad_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_2 in AQ_GlobalMicroprocessorScratchPad_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_EUR_scratchPad_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_2 in AQ_GlobalMicroprocessorScratchPad_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_EUR_scratchPad_2 u1.word_1

/*! \brief Base register address of structure AQ_GlobalStartupRate_EUR */
#define AQ_GlobalStartupRate_EUR_baseRegisterAddress 0x031A
/*! \brief MMD address of structure AQ_GlobalStartupRate_EUR */
#define AQ_GlobalStartupRate_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure reservedSp27 in AQ_GlobalStartupRate_EUR */
#define AQ_GlobalStartupRate_EUR_reservedSp27 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedSp27 in AQ_GlobalStartupRate_EUR */
#define bits_AQ_GlobalStartupRate_EUR_reservedSp27 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedSp27 in AQ_GlobalStartupRate_EUR */
#define word_AQ_GlobalStartupRate_EUR_reservedSp27 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure startupRate in AQ_GlobalStartupRate_EUR */
#define AQ_GlobalStartupRate_EUR_startupRate 0
/*! \brief Preprocessor variable to relate field to bit position in structure startupRate in AQ_GlobalStartupRate_EUR */
#define bits_AQ_GlobalStartupRate_EUR_startupRate u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure startupRate in AQ_GlobalStartupRate_EUR */
#define word_AQ_GlobalStartupRate_EUR_startupRate u0.word_0

/*! \brief Base register address of structure AQ_GlobalSystemConfigurationFor100M_EUR */
#define AQ_GlobalSystemConfigurationFor100M_EUR_baseRegisterAddress 0x031B
/*! \brief MMD address of structure AQ_GlobalSystemConfigurationFor100M_EUR */
#define AQ_GlobalSystemConfigurationFor100M_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure reservedSp28 in AQ_GlobalSystemConfigurationFor100M_EUR */
#define AQ_GlobalSystemConfigurationFor100M_EUR_reservedSp28 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedSp28 in AQ_GlobalSystemConfigurationFor100M_EUR */
#define bits_AQ_GlobalSystemConfigurationFor100M_EUR_reservedSp28 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedSp28 in AQ_GlobalSystemConfigurationFor100M_EUR */
#define word_AQ_GlobalSystemConfigurationFor100M_EUR_reservedSp28 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define AQ_GlobalSystemConfigurationFor100M_EUR_ptpEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define bits_AQ_GlobalSystemConfigurationFor100M_EUR_ptpEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define word_AQ_GlobalSystemConfigurationFor100M_EUR_ptpEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure securityEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define AQ_GlobalSystemConfigurationFor100M_EUR_securityEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure securityEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define bits_AQ_GlobalSystemConfigurationFor100M_EUR_securityEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure securityEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define word_AQ_GlobalSystemConfigurationFor100M_EUR_securityEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor100M_EUR */
#define AQ_GlobalSystemConfigurationFor100M_EUR_rateAdaptationMethod 0
/*! \brief Preprocessor variable to relate field to bit position in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor100M_EUR */
#define bits_AQ_GlobalSystemConfigurationFor100M_EUR_rateAdaptationMethod u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor100M_EUR */
#define word_AQ_GlobalSystemConfigurationFor100M_EUR_rateAdaptationMethod u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define AQ_GlobalSystemConfigurationFor100M_EUR_serdesSilenceEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define bits_AQ_GlobalSystemConfigurationFor100M_EUR_serdesSilenceEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define word_AQ_GlobalSystemConfigurationFor100M_EUR_serdesSilenceEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define AQ_GlobalSystemConfigurationFor100M_EUR_resetOnTransitionEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define bits_AQ_GlobalSystemConfigurationFor100M_EUR_resetOnTransitionEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define word_AQ_GlobalSystemConfigurationFor100M_EUR_resetOnTransitionEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure trainingEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define AQ_GlobalSystemConfigurationFor100M_EUR_trainingEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure trainingEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define bits_AQ_GlobalSystemConfigurationFor100M_EUR_trainingEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure trainingEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define word_AQ_GlobalSystemConfigurationFor100M_EUR_trainingEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define AQ_GlobalSystemConfigurationFor100M_EUR_autonegEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define bits_AQ_GlobalSystemConfigurationFor100M_EUR_autonegEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegEnable in AQ_GlobalSystemConfigurationFor100M_EUR */
#define word_AQ_GlobalSystemConfigurationFor100M_EUR_autonegEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMode in AQ_GlobalSystemConfigurationFor100M_EUR */
#define AQ_GlobalSystemConfigurationFor100M_EUR_serdesMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMode in AQ_GlobalSystemConfigurationFor100M_EUR */
#define bits_AQ_GlobalSystemConfigurationFor100M_EUR_serdesMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMode in AQ_GlobalSystemConfigurationFor100M_EUR */
#define word_AQ_GlobalSystemConfigurationFor100M_EUR_serdesMode u0.word_0

/*! \brief Base register address of structure AQ_GlobalSystemConfigurationFor1G_EUR */
#define AQ_GlobalSystemConfigurationFor1G_EUR_baseRegisterAddress 0x031C
/*! \brief MMD address of structure AQ_GlobalSystemConfigurationFor1G_EUR */
#define AQ_GlobalSystemConfigurationFor1G_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure reservedSp29 in AQ_GlobalSystemConfigurationFor1G_EUR */
#define AQ_GlobalSystemConfigurationFor1G_EUR_reservedSp29 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedSp29 in AQ_GlobalSystemConfigurationFor1G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor1G_EUR_reservedSp29 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedSp29 in AQ_GlobalSystemConfigurationFor1G_EUR */
#define word_AQ_GlobalSystemConfigurationFor1G_EUR_reservedSp29 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define AQ_GlobalSystemConfigurationFor1G_EUR_ptpEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor1G_EUR_ptpEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define word_AQ_GlobalSystemConfigurationFor1G_EUR_ptpEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure securityEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define AQ_GlobalSystemConfigurationFor1G_EUR_securityEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure securityEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor1G_EUR_securityEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure securityEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define word_AQ_GlobalSystemConfigurationFor1G_EUR_securityEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor1G_EUR */
#define AQ_GlobalSystemConfigurationFor1G_EUR_rateAdaptationMethod 0
/*! \brief Preprocessor variable to relate field to bit position in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor1G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor1G_EUR_rateAdaptationMethod u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor1G_EUR */
#define word_AQ_GlobalSystemConfigurationFor1G_EUR_rateAdaptationMethod u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define AQ_GlobalSystemConfigurationFor1G_EUR_serdesSilenceEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor1G_EUR_serdesSilenceEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define word_AQ_GlobalSystemConfigurationFor1G_EUR_serdesSilenceEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define AQ_GlobalSystemConfigurationFor1G_EUR_resetOnTransitionEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor1G_EUR_resetOnTransitionEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define word_AQ_GlobalSystemConfigurationFor1G_EUR_resetOnTransitionEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure trainingEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define AQ_GlobalSystemConfigurationFor1G_EUR_trainingEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure trainingEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor1G_EUR_trainingEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure trainingEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define word_AQ_GlobalSystemConfigurationFor1G_EUR_trainingEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define AQ_GlobalSystemConfigurationFor1G_EUR_autonegEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor1G_EUR_autonegEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegEnable in AQ_GlobalSystemConfigurationFor1G_EUR */
#define word_AQ_GlobalSystemConfigurationFor1G_EUR_autonegEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMode in AQ_GlobalSystemConfigurationFor1G_EUR */
#define AQ_GlobalSystemConfigurationFor1G_EUR_serdesMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMode in AQ_GlobalSystemConfigurationFor1G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor1G_EUR_serdesMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMode in AQ_GlobalSystemConfigurationFor1G_EUR */
#define word_AQ_GlobalSystemConfigurationFor1G_EUR_serdesMode u0.word_0

/*! \brief Base register address of structure AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_2_5g_EUR_baseRegisterAddress 0x031D
/*! \brief MMD address of structure AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_2_5g_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure reservedSp30 in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_2_5g_EUR_reservedSp30 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedSp30 in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_2_5g_EUR_reservedSp30 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedSp30 in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_2_5g_EUR_reservedSp30 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_2_5g_EUR_ptpEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_2_5g_EUR_ptpEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_2_5g_EUR_ptpEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure securityEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_2_5g_EUR_securityEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure securityEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_2_5g_EUR_securityEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure securityEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_2_5g_EUR_securityEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_2_5g_EUR_rateAdaptationMethod 0
/*! \brief Preprocessor variable to relate field to bit position in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_2_5g_EUR_rateAdaptationMethod u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_2_5g_EUR_rateAdaptationMethod u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_2_5g_EUR_serdesSilenceEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_2_5g_EUR_serdesSilenceEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_2_5g_EUR_serdesSilenceEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_2_5g_EUR_resetOnTransitionEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_2_5g_EUR_resetOnTransitionEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_2_5g_EUR_resetOnTransitionEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure trainingEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_2_5g_EUR_trainingEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure trainingEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_2_5g_EUR_trainingEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure trainingEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_2_5g_EUR_trainingEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_2_5g_EUR_autonegEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_2_5g_EUR_autonegEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegEnable in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_2_5g_EUR_autonegEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMode in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_2_5g_EUR_serdesMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMode in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_2_5g_EUR_serdesMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMode in AQ_GlobalSystemConfigurationFor_2_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_2_5g_EUR_serdesMode u0.word_0

/*! \brief Base register address of structure AQ_GlobalSystemConfigurationFor_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_5g_EUR_baseRegisterAddress 0x031E
/*! \brief MMD address of structure AQ_GlobalSystemConfigurationFor_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_5g_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure reservedSp31 in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_5g_EUR_reservedSp31 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedSp31 in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_5g_EUR_reservedSp31 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedSp31 in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_5g_EUR_reservedSp31 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_5g_EUR_ptpEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_5g_EUR_ptpEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_5g_EUR_ptpEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure securityEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_5g_EUR_securityEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure securityEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_5g_EUR_securityEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure securityEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_5g_EUR_securityEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_5g_EUR_rateAdaptationMethod 0
/*! \brief Preprocessor variable to relate field to bit position in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_5g_EUR_rateAdaptationMethod u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_5g_EUR_rateAdaptationMethod u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_5g_EUR_serdesSilenceEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_5g_EUR_serdesSilenceEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_5g_EUR_serdesSilenceEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_5g_EUR_resetOnTransitionEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_5g_EUR_resetOnTransitionEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_5g_EUR_resetOnTransitionEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure trainingEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_5g_EUR_trainingEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure trainingEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_5g_EUR_trainingEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure trainingEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_5g_EUR_trainingEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_5g_EUR_autonegEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_5g_EUR_autonegEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegEnable in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_5g_EUR_autonegEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMode in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define AQ_GlobalSystemConfigurationFor_5g_EUR_serdesMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMode in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define bits_AQ_GlobalSystemConfigurationFor_5g_EUR_serdesMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMode in AQ_GlobalSystemConfigurationFor_5g_EUR */
#define word_AQ_GlobalSystemConfigurationFor_5g_EUR_serdesMode u0.word_0

/*! \brief Base register address of structure AQ_GlobalSystemConfigurationFor10G_EUR */
#define AQ_GlobalSystemConfigurationFor10G_EUR_baseRegisterAddress 0x031F
/*! \brief MMD address of structure AQ_GlobalSystemConfigurationFor10G_EUR */
#define AQ_GlobalSystemConfigurationFor10G_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure reservedSp32 in AQ_GlobalSystemConfigurationFor10G_EUR */
#define AQ_GlobalSystemConfigurationFor10G_EUR_reservedSp32 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedSp32 in AQ_GlobalSystemConfigurationFor10G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor10G_EUR_reservedSp32 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedSp32 in AQ_GlobalSystemConfigurationFor10G_EUR */
#define word_AQ_GlobalSystemConfigurationFor10G_EUR_reservedSp32 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ptpEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define AQ_GlobalSystemConfigurationFor10G_EUR_ptpEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure ptpEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor10G_EUR_ptpEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ptpEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define word_AQ_GlobalSystemConfigurationFor10G_EUR_ptpEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure securityEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define AQ_GlobalSystemConfigurationFor10G_EUR_securityEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure securityEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor10G_EUR_securityEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure securityEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define word_AQ_GlobalSystemConfigurationFor10G_EUR_securityEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor10G_EUR */
#define AQ_GlobalSystemConfigurationFor10G_EUR_rateAdaptationMethod 0
/*! \brief Preprocessor variable to relate field to bit position in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor10G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor10G_EUR_rateAdaptationMethod u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rateAdaptationMethod in AQ_GlobalSystemConfigurationFor10G_EUR */
#define word_AQ_GlobalSystemConfigurationFor10G_EUR_rateAdaptationMethod u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define AQ_GlobalSystemConfigurationFor10G_EUR_serdesSilenceEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor10G_EUR_serdesSilenceEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesSilenceEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define word_AQ_GlobalSystemConfigurationFor10G_EUR_serdesSilenceEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define AQ_GlobalSystemConfigurationFor10G_EUR_resetOnTransitionEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor10G_EUR_resetOnTransitionEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure resetOnTransitionEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define word_AQ_GlobalSystemConfigurationFor10G_EUR_resetOnTransitionEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure trainingEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define AQ_GlobalSystemConfigurationFor10G_EUR_trainingEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure trainingEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor10G_EUR_trainingEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure trainingEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define word_AQ_GlobalSystemConfigurationFor10G_EUR_trainingEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define AQ_GlobalSystemConfigurationFor10G_EUR_autonegEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor10G_EUR_autonegEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegEnable in AQ_GlobalSystemConfigurationFor10G_EUR */
#define word_AQ_GlobalSystemConfigurationFor10G_EUR_autonegEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesMode in AQ_GlobalSystemConfigurationFor10G_EUR */
#define AQ_GlobalSystemConfigurationFor10G_EUR_serdesMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesMode in AQ_GlobalSystemConfigurationFor10G_EUR */
#define bits_AQ_GlobalSystemConfigurationFor10G_EUR_serdesMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesMode in AQ_GlobalSystemConfigurationFor10G_EUR */
#define word_AQ_GlobalSystemConfigurationFor10G_EUR_serdesMode u0.word_0

/*! \brief Base register address of structure AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_baseRegisterAddress 0x0380
/*! \brief MMD address of structure AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_33 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_33 0
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_33 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_33 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_33 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_33 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_34 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_34 1
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_34 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_34 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_34 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_34 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_35 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_35 2
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_35 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_35 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_35 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_35 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_36 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_36 3
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_36 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_36 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_36 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_36 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_37 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_37 4
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_37 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_37 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_37 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_37 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_38 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_38 5
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_38 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_38 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_38 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_38 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_39 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_39 6
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_39 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_39 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_39 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_39 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_40 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_40 7
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_40 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_40 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_40 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_40 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_41 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_41 8
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_41 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_41 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_41 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_41 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_42 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_42 9
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_42 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_42 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_42 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_42 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_43 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_43 10
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_43 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_43 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_43 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_43 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_44 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_44 11
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_44 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_44 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_44 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_44 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_45 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_45 12
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_45 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_45 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_45 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_45 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_46 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_46 13
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_46 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_46 u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_46 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_46 u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_47 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_47 14
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_47 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_47 u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_47 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_47 u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_48 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_48 15
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_48 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_48 u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_48 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_48 u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_49 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_49 16
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_49 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_49 u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_49 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_49 u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_50 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_50 17
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_50 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_50 u17.bits_17
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_50 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_50 u17.word_17
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_51 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_51 18
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_51 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_51 u18.bits_18
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_51 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_51 u18.word_18
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_52 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_52 19
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_52 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_52 u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_52 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_52 u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_53 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_53 20
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_53 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_53 u20.bits_20
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_53 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_53 u20.word_20
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_54 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_54 21
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_54 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_54 u21.bits_21
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_54 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_54 u21.word_21
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_55 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_55 22
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_55 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_55 u22.bits_22
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_55 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_55 u22.word_22
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_56 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_56 23
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_56 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_56 u23.bits_23
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_56 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_56 u23.word_23
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_57 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_57 24
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_57 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_57 u24.bits_24
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_57 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_57 u24.word_24
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_58 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_58 25
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_58 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_58 u25.bits_25
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_58 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_58 u25.word_25
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_59 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_59 26
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_59 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_59 u26.bits_26
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_59 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_59 u26.word_26
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_60 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_60 27
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_60 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_60 u27.bits_27
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_60 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_60 u27.word_27
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_61 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_61 28
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_61 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_61 u28.bits_28
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_61 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_61 u28.word_28
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_62 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_62 29
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_62 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_62 u29.bits_29
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_62 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_62 u29.word_29
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_63 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_63 30
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_63 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_63 u30.bits_30
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_63 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_63 u30.word_30
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_64 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_64 31
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_64 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define bits_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_64 u31.bits_31
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_64 in AQ_GlobalMicroprocessorScratchPad_2_EUR */
#define word_AQ_GlobalMicroprocessorScratchPad_2_EUR_scratchPad_64 u31.word_31

/*! \brief Base register address of structure AQ_GlobalControl_EUR */
#define AQ_GlobalControl_EUR_baseRegisterAddress 0xC000
/*! \brief MMD address of structure AQ_GlobalControl_EUR */
#define AQ_GlobalControl_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure upReset in AQ_GlobalControl_EUR */
#define AQ_GlobalControl_EUR_upReset 1
/*! \brief Preprocessor variable to relate field to bit position in structure upReset in AQ_GlobalControl_EUR */
#define bits_AQ_GlobalControl_EUR_upReset u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure upReset in AQ_GlobalControl_EUR */
#define word_AQ_GlobalControl_EUR_upReset u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure upRunStallOverride in AQ_GlobalControl_EUR */
#define AQ_GlobalControl_EUR_upRunStallOverride 1
/*! \brief Preprocessor variable to relate field to bit position in structure upRunStallOverride in AQ_GlobalControl_EUR */
#define bits_AQ_GlobalControl_EUR_upRunStallOverride u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure upRunStallOverride in AQ_GlobalControl_EUR */
#define word_AQ_GlobalControl_EUR_upRunStallOverride u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure upRunStall in AQ_GlobalControl_EUR */
#define AQ_GlobalControl_EUR_upRunStall 1
/*! \brief Preprocessor variable to relate field to bit position in structure upRunStall in AQ_GlobalControl_EUR */
#define bits_AQ_GlobalControl_EUR_upRunStall u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure upRunStall in AQ_GlobalControl_EUR */
#define word_AQ_GlobalControl_EUR_upRunStall u1.word_1

/*! \brief Base register address of structure AQ_GlobalResetControl_EUR */
#define AQ_GlobalResetControl_EUR_baseRegisterAddress 0xC006
/*! \brief MMD address of structure AQ_GlobalResetControl_EUR */
#define AQ_GlobalResetControl_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure globalMMD_ResetDisable in AQ_GlobalResetControl_EUR */
#define AQ_GlobalResetControl_EUR_globalMMD_ResetDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalMMD_ResetDisable in AQ_GlobalResetControl_EUR */
#define bits_AQ_GlobalResetControl_EUR_globalMMD_ResetDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalMMD_ResetDisable in AQ_GlobalResetControl_EUR */
#define word_AQ_GlobalResetControl_EUR_globalMMD_ResetDisable u0.word_0

/*! \brief Base register address of structure AQ_GlobalDiagnosticProvisioning_EUR */
#define AQ_GlobalDiagnosticProvisioning_EUR_baseRegisterAddress 0xC400
/*! \brief MMD address of structure AQ_GlobalDiagnosticProvisioning_EUR */
#define AQ_GlobalDiagnosticProvisioning_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure enableDiagnostics in AQ_GlobalDiagnosticProvisioning_EUR */
#define AQ_GlobalDiagnosticProvisioning_EUR_enableDiagnostics 0
/*! \brief Preprocessor variable to relate field to bit position in structure enableDiagnostics in AQ_GlobalDiagnosticProvisioning_EUR */
#define bits_AQ_GlobalDiagnosticProvisioning_EUR_enableDiagnostics u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure enableDiagnostics in AQ_GlobalDiagnosticProvisioning_EUR */
#define word_AQ_GlobalDiagnosticProvisioning_EUR_enableDiagnostics u0.word_0

/*! \brief Base register address of structure AQ_GlobalThermalProvisioning_EUR */
#define AQ_GlobalThermalProvisioning_EUR_baseRegisterAddress 0xC420
/*! \brief MMD address of structure AQ_GlobalThermalProvisioning_EUR */
#define AQ_GlobalThermalProvisioning_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure reserved_0 in AQ_GlobalThermalProvisioning_EUR */
#define AQ_GlobalThermalProvisioning_EUR_reserved_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_0 in AQ_GlobalThermalProvisioning_EUR */
#define bits_AQ_GlobalThermalProvisioning_EUR_reserved_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_0 in AQ_GlobalThermalProvisioning_EUR */
#define word_AQ_GlobalThermalProvisioning_EUR_reserved_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure highTempFailureThreshold in AQ_GlobalThermalProvisioning_EUR */
#define AQ_GlobalThermalProvisioning_EUR_highTempFailureThreshold 1
/*! \brief Preprocessor variable to relate field to bit position in structure highTempFailureThreshold in AQ_GlobalThermalProvisioning_EUR */
#define bits_AQ_GlobalThermalProvisioning_EUR_highTempFailureThreshold u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure highTempFailureThreshold in AQ_GlobalThermalProvisioning_EUR */
#define word_AQ_GlobalThermalProvisioning_EUR_highTempFailureThreshold u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure lowTempFailureThreshold in AQ_GlobalThermalProvisioning_EUR */
#define AQ_GlobalThermalProvisioning_EUR_lowTempFailureThreshold 2
/*! \brief Preprocessor variable to relate field to bit position in structure lowTempFailureThreshold in AQ_GlobalThermalProvisioning_EUR */
#define bits_AQ_GlobalThermalProvisioning_EUR_lowTempFailureThreshold u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure lowTempFailureThreshold in AQ_GlobalThermalProvisioning_EUR */
#define word_AQ_GlobalThermalProvisioning_EUR_lowTempFailureThreshold u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure highTempWarningThreshold in AQ_GlobalThermalProvisioning_EUR */
#define AQ_GlobalThermalProvisioning_EUR_highTempWarningThreshold 3
/*! \brief Preprocessor variable to relate field to bit position in structure highTempWarningThreshold in AQ_GlobalThermalProvisioning_EUR */
#define bits_AQ_GlobalThermalProvisioning_EUR_highTempWarningThreshold u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure highTempWarningThreshold in AQ_GlobalThermalProvisioning_EUR */
#define word_AQ_GlobalThermalProvisioning_EUR_highTempWarningThreshold u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure lowTempWarningThreshold in AQ_GlobalThermalProvisioning_EUR */
#define AQ_GlobalThermalProvisioning_EUR_lowTempWarningThreshold 4
/*! \brief Preprocessor variable to relate field to bit position in structure lowTempWarningThreshold in AQ_GlobalThermalProvisioning_EUR */
#define bits_AQ_GlobalThermalProvisioning_EUR_lowTempWarningThreshold u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure lowTempWarningThreshold in AQ_GlobalThermalProvisioning_EUR */
#define word_AQ_GlobalThermalProvisioning_EUR_lowTempWarningThreshold u4.word_4

/*! \brief Base register address of structure AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_baseRegisterAddress 0xC425
/*! \brief MMD address of structure AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure ledTimerOnDuration_0 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledTimerOnDuration_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure ledTimerOnDuration_0 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledTimerOnDuration_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ledTimerOnDuration_0 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledTimerOnDuration_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ledTimerOffDuration_0 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledTimerOffDuration_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure ledTimerOffDuration_0 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledTimerOffDuration_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ledTimerOffDuration_0 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledTimerOffDuration_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ledTimerOnDuration_1 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledTimerOnDuration_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure ledTimerOnDuration_1 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledTimerOnDuration_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ledTimerOnDuration_1 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledTimerOnDuration_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ledTimerOffDuration_1 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledTimerOffDuration_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure ledTimerOffDuration_1 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledTimerOffDuration_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ledTimerOffDuration_1 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledTimerOffDuration_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityMode in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityMode 2
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityMode in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityMode u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityMode in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityMode u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_1Mode in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_led_1Mode 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_1Mode in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_led_1Mode u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_1Mode in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_led_1Mode u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_0Mode in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_led_0Mode 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_0Mode in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_led_0Mode u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_0Mode in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_led_0Mode u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_0 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_0 3
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_0 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_0 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_0 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_0 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_1 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_1 3
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_1 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_1 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_1 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_1 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_2 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_2 4
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_2 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_2 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_2 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_2 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_3 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_3 4
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_3 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_3 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_3 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_3 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_4 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_4 5
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_4 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_4 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_4 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_4 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_5 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_5 5
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_5 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_5 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_5 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_5 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_6 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_6 6
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_6 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_6 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_6 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_6 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_7 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_7 6
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_7 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_7 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_7 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_7 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_8 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_8 7
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_8 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_8 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_8 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_8 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_9 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_9 7
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_9 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_9 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_9 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_9 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_10 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_10 8
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_10 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_10 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_10 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_10 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_11 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_11 8
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_11 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_11 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_11 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_11 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_12 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_12 9
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_12 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_12 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_12 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_12 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_13 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_13 9
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_13 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_13 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_13 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_13 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ledLinkActivityLut_14 in AQ_CiscoLedProvisioning_EUR */
#define AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_14 10
/*! \brief Preprocessor variable to relate field to bit position in structure ledLinkActivityLut_14 in AQ_CiscoLedProvisioning_EUR */
#define bits_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_14 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure ledLinkActivityLut_14 in AQ_CiscoLedProvisioning_EUR */
#define word_AQ_CiscoLedProvisioning_EUR_ledLinkActivityLut_14 u10.word_10

/*! \brief Base register address of structure AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_baseRegisterAddress 0xC430
/*! \brief MMD address of structure AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure led_0_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_0_5Gb_sLinkEstablished 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_0_5Gb_sLinkEstablished u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_0_5Gb_sLinkEstablished u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_0_2_5Gb_sLinkEstablished 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_0_2_5Gb_sLinkEstablished u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_0_2_5Gb_sLinkEstablished u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioningC430 in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_reservedProvisioningC430 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioningC430 in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_reservedProvisioningC430 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioningC430 in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_reservedProvisioningC430 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0ManualSet in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_0ManualSet 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0ManualSet in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_0ManualSet u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0ManualSet in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_0ManualSet u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_0_10Gb_sLinkEstablished 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_0_10Gb_sLinkEstablished u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_0_10Gb_sLinkEstablished u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_0_1Gb_sLinkEstablished 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_0_1Gb_sLinkEstablished u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_0_1Gb_sLinkEstablished u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_0_100Mb_sLinkEstablished 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_0_100Mb_sLinkEstablished u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_0_100Mb_sLinkEstablished u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0Connecting in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_0Connecting 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0Connecting in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_0Connecting u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0Connecting in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_0Connecting u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0ReceiveActivity in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_0ReceiveActivity 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0ReceiveActivity in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_0ReceiveActivity u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0ReceiveActivity in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_0ReceiveActivity u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0TransmitActivity in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_0TransmitActivity 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0TransmitActivity in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_0TransmitActivity u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0TransmitActivity in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_0TransmitActivity u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0ActivityStretch in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_0ActivityStretch 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0ActivityStretch in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_0ActivityStretch u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0ActivityStretch in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_0ActivityStretch u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_1_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_1_5Gb_sLinkEstablished 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_1_5Gb_sLinkEstablished u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_1_5Gb_sLinkEstablished u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_1_2_5Gb_sLinkEstablished 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_1_2_5Gb_sLinkEstablished u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_1_2_5Gb_sLinkEstablished u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioningC431 in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_reservedProvisioningC431 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioningC431 in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_reservedProvisioningC431 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioningC431 in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_reservedProvisioningC431 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1ManualSet in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_1ManualSet 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1ManualSet in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_1ManualSet u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1ManualSet in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_1ManualSet u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_1_10Gb_sLinkEstablished 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_1_10Gb_sLinkEstablished u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_1_10Gb_sLinkEstablished u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_1_1Gb_sLinkEstablished 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_1_1Gb_sLinkEstablished u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_1_1Gb_sLinkEstablished u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_1_100Mb_sLinkEstablished 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_1_100Mb_sLinkEstablished u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_1_100Mb_sLinkEstablished u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1Connecting in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_1Connecting 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1Connecting in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_1Connecting u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1Connecting in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_1Connecting u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1ReceiveActivity in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_1ReceiveActivity 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1ReceiveActivity in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_1ReceiveActivity u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1ReceiveActivity in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_1ReceiveActivity u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1TransmitActivity in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_1TransmitActivity 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1TransmitActivity in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_1TransmitActivity u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1TransmitActivity in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_1TransmitActivity u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1ActivityStretch in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_1ActivityStretch 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1ActivityStretch in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_1ActivityStretch u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1ActivityStretch in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_1ActivityStretch u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_2_5Gb_sLinkEstablished 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_2_5Gb_sLinkEstablished u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_2_5Gb_sLinkEstablished u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_2_2_5Gb_sLinkEstablished 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_2_2_5Gb_sLinkEstablished u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_2_2_5Gb_sLinkEstablished u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioningC432 in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_reservedProvisioningC432 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioningC432 in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_reservedProvisioningC432 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioningC432 in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_reservedProvisioningC432 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2ManualSet in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_2ManualSet 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2ManualSet in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_2ManualSet u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2ManualSet in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_2ManualSet u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_2_10Gb_sLinkEstablished 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_2_10Gb_sLinkEstablished u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_2_10Gb_sLinkEstablished u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_2_1Gb_sLinkEstablished 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_2_1Gb_sLinkEstablished u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_2_1Gb_sLinkEstablished u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_2_100Mb_sLinkEstablished 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_2_100Mb_sLinkEstablished u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_2_100Mb_sLinkEstablished u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2Connecting in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_2Connecting 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2Connecting in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_2Connecting u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2Connecting in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_2Connecting u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2ReceiveActivity in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_2ReceiveActivity 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2ReceiveActivity in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_2ReceiveActivity u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2ReceiveActivity in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_2ReceiveActivity u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2TransmitActivity in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_2TransmitActivity 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2TransmitActivity in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_2TransmitActivity u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2TransmitActivity in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_2TransmitActivity u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2ActivityStretch in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_led_2ActivityStretch 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2ActivityStretch in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_led_2ActivityStretch u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2ActivityStretch in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_led_2ActivityStretch u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ledOperationMode_1 in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_ledOperationMode_1 7
/*! \brief Preprocessor variable to relate field to bit position in structure ledOperationMode_1 in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_ledOperationMode_1 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure ledOperationMode_1 in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_ledOperationMode_1 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure ledOperationMode_0 in AQ_GlobalLedProvisioning_EUR */
#define AQ_GlobalLedProvisioning_EUR_ledOperationMode_0 7
/*! \brief Preprocessor variable to relate field to bit position in structure ledOperationMode_0 in AQ_GlobalLedProvisioning_EUR */
#define bits_AQ_GlobalLedProvisioning_EUR_ledOperationMode_0 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure ledOperationMode_0 in AQ_GlobalLedProvisioning_EUR */
#define word_AQ_GlobalLedProvisioning_EUR_ledOperationMode_0 u7.word_7

/*! \brief Base register address of structure AQ_GlobalGeneralProvisioning_EUR */
#define AQ_GlobalGeneralProvisioning_EUR_baseRegisterAddress 0xC440
/*! \brief MMD address of structure AQ_GlobalGeneralProvisioning_EUR */
#define AQ_GlobalGeneralProvisioning_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mdioBroadcastModeEnable in AQ_GlobalGeneralProvisioning_EUR */
#define AQ_GlobalGeneralProvisioning_EUR_mdioBroadcastModeEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mdioBroadcastModeEnable in AQ_GlobalGeneralProvisioning_EUR */
#define bits_AQ_GlobalGeneralProvisioning_EUR_mdioBroadcastModeEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mdioBroadcastModeEnable in AQ_GlobalGeneralProvisioning_EUR */
#define word_AQ_GlobalGeneralProvisioning_EUR_mdioBroadcastModeEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mdioReadMSW_FirstEnable in AQ_GlobalGeneralProvisioning_EUR */
#define AQ_GlobalGeneralProvisioning_EUR_mdioReadMSW_FirstEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mdioReadMSW_FirstEnable in AQ_GlobalGeneralProvisioning_EUR */
#define bits_AQ_GlobalGeneralProvisioning_EUR_mdioReadMSW_FirstEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mdioReadMSW_FirstEnable in AQ_GlobalGeneralProvisioning_EUR */
#define word_AQ_GlobalGeneralProvisioning_EUR_mdioReadMSW_FirstEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mdioDriveConfiguration in AQ_GlobalGeneralProvisioning_EUR */
#define AQ_GlobalGeneralProvisioning_EUR_mdioDriveConfiguration 1
/*! \brief Preprocessor variable to relate field to bit position in structure mdioDriveConfiguration in AQ_GlobalGeneralProvisioning_EUR */
#define bits_AQ_GlobalGeneralProvisioning_EUR_mdioDriveConfiguration u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mdioDriveConfiguration in AQ_GlobalGeneralProvisioning_EUR */
#define word_AQ_GlobalGeneralProvisioning_EUR_mdioDriveConfiguration u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mdioPreambleDetectionDisable in AQ_GlobalGeneralProvisioning_EUR */
#define AQ_GlobalGeneralProvisioning_EUR_mdioPreambleDetectionDisable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mdioPreambleDetectionDisable in AQ_GlobalGeneralProvisioning_EUR */
#define bits_AQ_GlobalGeneralProvisioning_EUR_mdioPreambleDetectionDisable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mdioPreambleDetectionDisable in AQ_GlobalGeneralProvisioning_EUR */
#define word_AQ_GlobalGeneralProvisioning_EUR_mdioPreambleDetectionDisable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure daisyChainReset in AQ_GlobalGeneralProvisioning_EUR */
#define AQ_GlobalGeneralProvisioning_EUR_daisyChainReset 2
/*! \brief Preprocessor variable to relate field to bit position in structure daisyChainReset in AQ_GlobalGeneralProvisioning_EUR */
#define bits_AQ_GlobalGeneralProvisioning_EUR_daisyChainReset u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure daisyChainReset in AQ_GlobalGeneralProvisioning_EUR */
#define word_AQ_GlobalGeneralProvisioning_EUR_daisyChainReset u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mdioBroadcastAddressConfiguration in AQ_GlobalGeneralProvisioning_EUR */
#define AQ_GlobalGeneralProvisioning_EUR_mdioBroadcastAddressConfiguration 7
/*! \brief Preprocessor variable to relate field to bit position in structure mdioBroadcastAddressConfiguration in AQ_GlobalGeneralProvisioning_EUR */
#define bits_AQ_GlobalGeneralProvisioning_EUR_mdioBroadcastAddressConfiguration u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure mdioBroadcastAddressConfiguration in AQ_GlobalGeneralProvisioning_EUR */
#define word_AQ_GlobalGeneralProvisioning_EUR_mdioBroadcastAddressConfiguration u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure mdioPreambleLength in AQ_GlobalGeneralProvisioning_EUR */
#define AQ_GlobalGeneralProvisioning_EUR_mdioPreambleLength 9
/*! \brief Preprocessor variable to relate field to bit position in structure mdioPreambleLength in AQ_GlobalGeneralProvisioning_EUR */
#define bits_AQ_GlobalGeneralProvisioning_EUR_mdioPreambleLength u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure mdioPreambleLength in AQ_GlobalGeneralProvisioning_EUR */
#define word_AQ_GlobalGeneralProvisioning_EUR_mdioPreambleLength u9.word_9

/*! \brief Base register address of structure AQ_GlobalNvrProvisioning_EUR */
#define AQ_GlobalNvrProvisioning_EUR_baseRegisterAddress 0xC450
/*! \brief MMD address of structure AQ_GlobalNvrProvisioning_EUR */
#define AQ_GlobalNvrProvisioning_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure nvrDataLength in AQ_GlobalNvrProvisioning_EUR */
#define AQ_GlobalNvrProvisioning_EUR_nvrDataLength 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDataLength in AQ_GlobalNvrProvisioning_EUR */
#define bits_AQ_GlobalNvrProvisioning_EUR_nvrDataLength u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrDataLength in AQ_GlobalNvrProvisioning_EUR */
#define word_AQ_GlobalNvrProvisioning_EUR_nvrDataLength u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrDummyLength in AQ_GlobalNvrProvisioning_EUR */
#define AQ_GlobalNvrProvisioning_EUR_nvrDummyLength 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDummyLength in AQ_GlobalNvrProvisioning_EUR */
#define bits_AQ_GlobalNvrProvisioning_EUR_nvrDummyLength u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrDummyLength in AQ_GlobalNvrProvisioning_EUR */
#define word_AQ_GlobalNvrProvisioning_EUR_nvrDummyLength u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrAddressLength in AQ_GlobalNvrProvisioning_EUR */
#define AQ_GlobalNvrProvisioning_EUR_nvrAddressLength 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrAddressLength in AQ_GlobalNvrProvisioning_EUR */
#define bits_AQ_GlobalNvrProvisioning_EUR_nvrAddressLength u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrAddressLength in AQ_GlobalNvrProvisioning_EUR */
#define word_AQ_GlobalNvrProvisioning_EUR_nvrAddressLength u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrAddressLengthOverride in AQ_GlobalNvrProvisioning_EUR */
#define AQ_GlobalNvrProvisioning_EUR_nvrAddressLengthOverride 1
/*! \brief Preprocessor variable to relate field to bit position in structure nvrAddressLengthOverride in AQ_GlobalNvrProvisioning_EUR */
#define bits_AQ_GlobalNvrProvisioning_EUR_nvrAddressLengthOverride u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure nvrAddressLengthOverride in AQ_GlobalNvrProvisioning_EUR */
#define word_AQ_GlobalNvrProvisioning_EUR_nvrAddressLengthOverride u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure nvrClockDivide in AQ_GlobalNvrProvisioning_EUR */
#define AQ_GlobalNvrProvisioning_EUR_nvrClockDivide 1
/*! \brief Preprocessor variable to relate field to bit position in structure nvrClockDivide in AQ_GlobalNvrProvisioning_EUR */
#define bits_AQ_GlobalNvrProvisioning_EUR_nvrClockDivide u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure nvrClockDivide in AQ_GlobalNvrProvisioning_EUR */
#define word_AQ_GlobalNvrProvisioning_EUR_nvrClockDivide u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure nvrDaisyChainClockDivideOverride in AQ_GlobalNvrProvisioning_EUR */
#define AQ_GlobalNvrProvisioning_EUR_nvrDaisyChainClockDivideOverride 2
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDaisyChainClockDivideOverride in AQ_GlobalNvrProvisioning_EUR */
#define bits_AQ_GlobalNvrProvisioning_EUR_nvrDaisyChainClockDivideOverride u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure nvrDaisyChainClockDivideOverride in AQ_GlobalNvrProvisioning_EUR */
#define word_AQ_GlobalNvrProvisioning_EUR_nvrDaisyChainClockDivideOverride u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure nvrDaisyChainDisable in AQ_GlobalNvrProvisioning_EUR */
#define AQ_GlobalNvrProvisioning_EUR_nvrDaisyChainDisable 2
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDaisyChainDisable in AQ_GlobalNvrProvisioning_EUR */
#define bits_AQ_GlobalNvrProvisioning_EUR_nvrDaisyChainDisable u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure nvrDaisyChainDisable in AQ_GlobalNvrProvisioning_EUR */
#define word_AQ_GlobalNvrProvisioning_EUR_nvrDaisyChainDisable u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure nvrReset in AQ_GlobalNvrProvisioning_EUR */
#define AQ_GlobalNvrProvisioning_EUR_nvrReset 3
/*! \brief Preprocessor variable to relate field to bit position in structure nvrReset in AQ_GlobalNvrProvisioning_EUR */
#define bits_AQ_GlobalNvrProvisioning_EUR_nvrReset u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure nvrReset in AQ_GlobalNvrProvisioning_EUR */
#define word_AQ_GlobalNvrProvisioning_EUR_nvrReset u3.word_3

/*! \brief Base register address of structure AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_baseRegisterAddress 0xC470
/*! \brief MMD address of structure AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure diagnosticsSelect in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_diagnosticsSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure diagnosticsSelect in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_diagnosticsSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure diagnosticsSelect in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_diagnosticsSelect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extendedMdiDiagnosticsSelect in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_extendedMdiDiagnosticsSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedMdiDiagnosticsSelect in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_extendedMdiDiagnosticsSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedMdiDiagnosticsSelect in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_extendedMdiDiagnosticsSelect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure triggerDiagnosticInterrupt in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_triggerDiagnosticInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure triggerDiagnosticInterrupt in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_triggerDiagnosticInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure triggerDiagnosticInterrupt in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_triggerDiagnosticInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure initiateCableDiagnostics in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_initiateCableDiagnostics 0
/*! \brief Preprocessor variable to relate field to bit position in structure initiateCableDiagnostics in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_initiateCableDiagnostics u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure initiateCableDiagnostics in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_initiateCableDiagnostics u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_1 in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_1 in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_1 in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure cableDiagnosticBaudRate in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_cableDiagnosticBaudRate 0
/*! \brief Preprocessor variable to relate field to bit position in structure cableDiagnosticBaudRate in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_cableDiagnosticBaudRate u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure cableDiagnosticBaudRate in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_cableDiagnosticBaudRate u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure enableDaisy_chainHop_countOverride in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_enableDaisy_chainHop_countOverride 1
/*! \brief Preprocessor variable to relate field to bit position in structure enableDaisy_chainHop_countOverride in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_enableDaisy_chainHop_countOverride u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure enableDaisy_chainHop_countOverride in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_enableDaisy_chainHop_countOverride u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure daisy_chainHop_countOverrideValue in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_daisy_chainHop_countOverrideValue 1
/*! \brief Preprocessor variable to relate field to bit position in structure daisy_chainHop_countOverrideValue in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_daisy_chainHop_countOverrideValue u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure daisy_chainHop_countOverrideValue in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_daisy_chainHop_countOverrideValue u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure enableVddPowerSupplyTuning in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_enableVddPowerSupplyTuning 2
/*! \brief Preprocessor variable to relate field to bit position in structure enableVddPowerSupplyTuning in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_enableVddPowerSupplyTuning u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure enableVddPowerSupplyTuning in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_enableVddPowerSupplyTuning u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure tunableExternalVddPowerSupplyPresent in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_tunableExternalVddPowerSupplyPresent 2
/*! \brief Preprocessor variable to relate field to bit position in structure tunableExternalVddPowerSupplyPresent in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_tunableExternalVddPowerSupplyPresent u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure tunableExternalVddPowerSupplyPresent in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_tunableExternalVddPowerSupplyPresent u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure externalVddChangeRequest in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_externalVddChangeRequest 2
/*! \brief Preprocessor variable to relate field to bit position in structure externalVddChangeRequest in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_externalVddChangeRequest u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure externalVddChangeRequest in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_externalVddChangeRequest u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure enableXenpakRegisterSpace in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_enableXenpakRegisterSpace 2
/*! \brief Preprocessor variable to relate field to bit position in structure enableXenpakRegisterSpace in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_enableXenpakRegisterSpace u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure enableXenpakRegisterSpace in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_enableXenpakRegisterSpace u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure enable_5thChannelRfiCancellation in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_enable_5thChannelRfiCancellation 2
/*! \brief Preprocessor variable to relate field to bit position in structure enable_5thChannelRfiCancellation in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_enable_5thChannelRfiCancellation u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure enable_5thChannelRfiCancellation in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_enable_5thChannelRfiCancellation u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure rateTransitionRequest in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_rateTransitionRequest 3
/*! \brief Preprocessor variable to relate field to bit position in structure rateTransitionRequest in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_rateTransitionRequest u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure rateTransitionRequest in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_rateTransitionRequest u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure trainingSNR in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_trainingSNR 3
/*! \brief Preprocessor variable to relate field to bit position in structure trainingSNR in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_trainingSNR u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure trainingSNR in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_trainingSNR u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_5 in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_5 4
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_5 in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_5 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_5 in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_5 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure nvrDaisyChainKickstart in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_nvrDaisyChainKickstart 4
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDaisyChainKickstart in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_nvrDaisyChainKickstart u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure nvrDaisyChainKickstart in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_nvrDaisyChainKickstart u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure smartPower_downStatus in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_smartPower_downStatus 5
/*! \brief Preprocessor variable to relate field to bit position in structure smartPower_downStatus in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_smartPower_downStatus u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure smartPower_downStatus in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_smartPower_downStatus u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_6 in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_6 5
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_6 in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_6 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_6 in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_6 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrLpDisableTimer in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_cfrLpDisableTimer 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrLpDisableTimer in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_cfrLpDisableTimer u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrLpDisableTimer in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_cfrLpDisableTimer u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrLpExtendedMaxwait in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_cfrLpExtendedMaxwait 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrLpExtendedMaxwait in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_cfrLpExtendedMaxwait u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrLpExtendedMaxwait in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_cfrLpExtendedMaxwait u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrLpTHP in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_cfrLpTHP 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrLpTHP in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_cfrLpTHP u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrLpTHP in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_cfrLpTHP u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrLpSupport in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_cfrLpSupport 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrLpSupport in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_cfrLpSupport u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrLpSupport in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_cfrLpSupport u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrDisableTimer in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_cfrDisableTimer 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrDisableTimer in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_cfrDisableTimer u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrDisableTimer in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_cfrDisableTimer u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrExtendedMaxwait in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_cfrExtendedMaxwait 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrExtendedMaxwait in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_cfrExtendedMaxwait u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrExtendedMaxwait in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_cfrExtendedMaxwait u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrTHP in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_cfrTHP 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrTHP in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_cfrTHP u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrTHP in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_cfrTHP u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrSupport in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_cfrSupport 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrSupport in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_cfrSupport u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrSupport in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_cfrSupport u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure deadlockAvoidanceEnable in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_deadlockAvoidanceEnable 5
/*! \brief Preprocessor variable to relate field to bit position in structure deadlockAvoidanceEnable in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_deadlockAvoidanceEnable u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure deadlockAvoidanceEnable in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_deadlockAvoidanceEnable u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure smartPower_downEnable in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_smartPower_downEnable 5
/*! \brief Preprocessor variable to relate field to bit position in structure smartPower_downEnable in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_smartPower_downEnable u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure smartPower_downEnable in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_smartPower_downEnable u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure dteEnable in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_dteEnable 8
/*! \brief Preprocessor variable to relate field to bit position in structure dteEnable in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_dteEnable u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure dteEnable in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_dteEnable u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure dteDropReportingTimer in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_dteDropReportingTimer 8
/*! \brief Preprocessor variable to relate field to bit position in structure dteDropReportingTimer in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_dteDropReportingTimer u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure dteDropReportingTimer in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_dteDropReportingTimer u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure thermalShutdownEnable in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_thermalShutdownEnable 8
/*! \brief Preprocessor variable to relate field to bit position in structure thermalShutdownEnable in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_thermalShutdownEnable u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure thermalShutdownEnable in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_thermalShutdownEnable u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure sfp_ddmiEnable in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_sfp_ddmiEnable 8
/*! \brief Preprocessor variable to relate field to bit position in structure sfp_ddmiEnable in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_sfp_ddmiEnable u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure sfp_ddmiEnable in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_sfp_ddmiEnable u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_9 in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_9 8
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_9 in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_9 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_9 in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_9 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure powerUpStall in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_powerUpStall 9
/*! \brief Preprocessor variable to relate field to bit position in structure powerUpStall in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_powerUpStall u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure powerUpStall in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_powerUpStall u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_10 in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_10 9
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_10 in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_10 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_10 in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_10 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure ciscoLedModes in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_ciscoLedModes 9
/*! \brief Preprocessor variable to relate field to bit position in structure ciscoLedModes in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_ciscoLedModes u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure ciscoLedModes in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_ciscoLedModes u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure loopbackControl in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_loopbackControl 10
/*! \brief Preprocessor variable to relate field to bit position in structure loopbackControl in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_loopbackControl u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure loopbackControl in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_loopbackControl u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_11 in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_11 10
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_11 in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_11 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_11 in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_11 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure mdiPacketGeneration in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_mdiPacketGeneration 10
/*! \brief Preprocessor variable to relate field to bit position in structure mdiPacketGeneration in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_mdiPacketGeneration u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure mdiPacketGeneration in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_mdiPacketGeneration u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure look_asidePortPacketGeneration in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_look_asidePortPacketGeneration 10
/*! \brief Preprocessor variable to relate field to bit position in structure look_asidePortPacketGeneration in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_look_asidePortPacketGeneration u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure look_asidePortPacketGeneration in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_look_asidePortPacketGeneration u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure systemI_fPacketGeneration in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_systemI_fPacketGeneration 10
/*! \brief Preprocessor variable to relate field to bit position in structure systemI_fPacketGeneration in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_systemI_fPacketGeneration u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure systemI_fPacketGeneration in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_systemI_fPacketGeneration u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure rate in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_rate 10
/*! \brief Preprocessor variable to relate field to bit position in structure rate in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_rate u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure rate in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_rate u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_12 in AQ_GlobalReservedProvisioning_EUR */
#define AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_12 11
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_12 in AQ_GlobalReservedProvisioning_EUR */
#define bits_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_12 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_12 in AQ_GlobalReservedProvisioning_EUR */
#define word_AQ_GlobalReservedProvisioning_EUR_reservedProvisioning_12 u11.word_11

/*! \brief Base register address of structure AQ_PifMailboxControl_EUR */
#define AQ_PifMailboxControl_EUR_baseRegisterAddress 0xC47C
/*! \brief MMD address of structure AQ_PifMailboxControl_EUR */
#define AQ_PifMailboxControl_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure pifMailboxAddress in AQ_PifMailboxControl_EUR */
#define AQ_PifMailboxControl_EUR_pifMailboxAddress 0
/*! \brief Preprocessor variable to relate field to bit position in structure pifMailboxAddress in AQ_PifMailboxControl_EUR */
#define bits_AQ_PifMailboxControl_EUR_pifMailboxAddress u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pifMailboxAddress in AQ_PifMailboxControl_EUR */
#define word_AQ_PifMailboxControl_EUR_pifMailboxAddress u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pifMailboxData in AQ_PifMailboxControl_EUR */
#define AQ_PifMailboxControl_EUR_pifMailboxData 1
/*! \brief Preprocessor variable to relate field to bit position in structure pifMailboxData in AQ_PifMailboxControl_EUR */
#define bits_AQ_PifMailboxControl_EUR_pifMailboxData u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pifMailboxData in AQ_PifMailboxControl_EUR */
#define word_AQ_PifMailboxControl_EUR_pifMailboxData u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedPifMailboxControl_3 in AQ_PifMailboxControl_EUR */
#define AQ_PifMailboxControl_EUR_reservedPifMailboxControl_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPifMailboxControl_3 in AQ_PifMailboxControl_EUR */
#define bits_AQ_PifMailboxControl_EUR_reservedPifMailboxControl_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedPifMailboxControl_3 in AQ_PifMailboxControl_EUR */
#define word_AQ_PifMailboxControl_EUR_reservedPifMailboxControl_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure serviceSecondRegister in AQ_PifMailboxControl_EUR */
#define AQ_PifMailboxControl_EUR_serviceSecondRegister 2
/*! \brief Preprocessor variable to relate field to bit position in structure serviceSecondRegister in AQ_PifMailboxControl_EUR */
#define bits_AQ_PifMailboxControl_EUR_serviceSecondRegister u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure serviceSecondRegister in AQ_PifMailboxControl_EUR */
#define word_AQ_PifMailboxControl_EUR_serviceSecondRegister u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pifMailboxCommandType in AQ_PifMailboxControl_EUR */
#define AQ_PifMailboxControl_EUR_pifMailboxCommandType 2
/*! \brief Preprocessor variable to relate field to bit position in structure pifMailboxCommandType in AQ_PifMailboxControl_EUR */
#define bits_AQ_PifMailboxControl_EUR_pifMailboxCommandType u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure pifMailboxCommandType in AQ_PifMailboxControl_EUR */
#define word_AQ_PifMailboxControl_EUR_pifMailboxCommandType u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pifMailboxMMD in AQ_PifMailboxControl_EUR */
#define AQ_PifMailboxControl_EUR_pifMailboxMMD 2
/*! \brief Preprocessor variable to relate field to bit position in structure pifMailboxMMD in AQ_PifMailboxControl_EUR */
#define bits_AQ_PifMailboxControl_EUR_pifMailboxMMD u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure pifMailboxMMD in AQ_PifMailboxControl_EUR */
#define word_AQ_PifMailboxControl_EUR_pifMailboxMMD u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedPifMailboxControl_4 in AQ_PifMailboxControl_EUR */
#define AQ_PifMailboxControl_EUR_reservedPifMailboxControl_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPifMailboxControl_4 in AQ_PifMailboxControl_EUR */
#define bits_AQ_PifMailboxControl_EUR_reservedPifMailboxControl_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedPifMailboxControl_4 in AQ_PifMailboxControl_EUR */
#define word_AQ_PifMailboxControl_EUR_reservedPifMailboxControl_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure pifMailboxCommandStatus in AQ_PifMailboxControl_EUR */
#define AQ_PifMailboxControl_EUR_pifMailboxCommandStatus 3
/*! \brief Preprocessor variable to relate field to bit position in structure pifMailboxCommandStatus in AQ_PifMailboxControl_EUR */
#define bits_AQ_PifMailboxControl_EUR_pifMailboxCommandStatus u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pifMailboxCommandStatus in AQ_PifMailboxControl_EUR */
#define word_AQ_PifMailboxControl_EUR_pifMailboxCommandStatus u3.word_3

/*! \brief Base register address of structure AQ_GlobalSmbus_0Provisioning_EUR */
#define AQ_GlobalSmbus_0Provisioning_EUR_baseRegisterAddress 0xC485
/*! \brief MMD address of structure AQ_GlobalSmbus_0Provisioning_EUR */
#define AQ_GlobalSmbus_0Provisioning_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure smb_0SlaveAddress in AQ_GlobalSmbus_0Provisioning_EUR */
#define AQ_GlobalSmbus_0Provisioning_EUR_smb_0SlaveAddress 0
/*! \brief Preprocessor variable to relate field to bit position in structure smb_0SlaveAddress in AQ_GlobalSmbus_0Provisioning_EUR */
#define bits_AQ_GlobalSmbus_0Provisioning_EUR_smb_0SlaveAddress u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure smb_0SlaveAddress in AQ_GlobalSmbus_0Provisioning_EUR */
#define word_AQ_GlobalSmbus_0Provisioning_EUR_smb_0SlaveAddress u0.word_0

/*! \brief Base register address of structure AQ_GlobalSmbus_1Provisioning_EUR */
#define AQ_GlobalSmbus_1Provisioning_EUR_baseRegisterAddress 0xC495
/*! \brief MMD address of structure AQ_GlobalSmbus_1Provisioning_EUR */
#define AQ_GlobalSmbus_1Provisioning_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure smb_1SlaveAddress in AQ_GlobalSmbus_1Provisioning_EUR */
#define AQ_GlobalSmbus_1Provisioning_EUR_smb_1SlaveAddress 0
/*! \brief Preprocessor variable to relate field to bit position in structure smb_1SlaveAddress in AQ_GlobalSmbus_1Provisioning_EUR */
#define bits_AQ_GlobalSmbus_1Provisioning_EUR_smb_1SlaveAddress u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure smb_1SlaveAddress in AQ_GlobalSmbus_1Provisioning_EUR */
#define word_AQ_GlobalSmbus_1Provisioning_EUR_smb_1SlaveAddress u0.word_0

/*! \brief Base register address of structure AQ_GlobalEeeProvisioning_EUR */
#define AQ_GlobalEeeProvisioning_EUR_baseRegisterAddress 0xC4A0
/*! \brief MMD address of structure AQ_GlobalEeeProvisioning_EUR */
#define AQ_GlobalEeeProvisioning_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure eeeMode in AQ_GlobalEeeProvisioning_EUR */
#define AQ_GlobalEeeProvisioning_EUR_eeeMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeMode in AQ_GlobalEeeProvisioning_EUR */
#define bits_AQ_GlobalEeeProvisioning_EUR_eeeMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeMode in AQ_GlobalEeeProvisioning_EUR */
#define word_AQ_GlobalEeeProvisioning_EUR_eeeMode u0.word_0

/*! \brief Base register address of structure AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_baseRegisterAddress 0xC800
/*! \brief MMD address of structure AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure pairAStatus in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairAStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairAStatus in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairAStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairAStatus in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairAStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairBStatus in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairBStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairBStatus in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairBStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairBStatus in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairBStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairCStatus in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairCStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairCStatus in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairCStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairCStatus in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairCStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairDStatus in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairDStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairDStatus in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairDStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairDStatus in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairDStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairAReflection_1 in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairAReflection_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure pairAReflection_1 in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairAReflection_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pairAReflection_1 in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairAReflection_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure pairAReflection_2 in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairAReflection_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure pairAReflection_2 in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairAReflection_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pairAReflection_2 in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairAReflection_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure impulseResponseMSW in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_impulseResponseMSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure impulseResponseMSW in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_impulseResponseMSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure impulseResponseMSW in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_impulseResponseMSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pairBReflection_1 in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairBReflection_1 3
/*! \brief Preprocessor variable to relate field to bit position in structure pairBReflection_1 in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairBReflection_1 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pairBReflection_1 in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairBReflection_1 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure pairBReflection_2 in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairBReflection_2 3
/*! \brief Preprocessor variable to relate field to bit position in structure pairBReflection_2 in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairBReflection_2 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pairBReflection_2 in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairBReflection_2 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure impulseResponseLSW in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_impulseResponseLSW 4
/*! \brief Preprocessor variable to relate field to bit position in structure impulseResponseLSW in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_impulseResponseLSW u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure impulseResponseLSW in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_impulseResponseLSW u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure pairCReflection_1 in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairCReflection_1 5
/*! \brief Preprocessor variable to relate field to bit position in structure pairCReflection_1 in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairCReflection_1 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure pairCReflection_1 in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairCReflection_1 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure pairCReflection_2 in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairCReflection_2 5
/*! \brief Preprocessor variable to relate field to bit position in structure pairCReflection_2 in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairCReflection_2 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure pairCReflection_2 in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairCReflection_2 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure pairBLength in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairBLength 6
/*! \brief Preprocessor variable to relate field to bit position in structure pairBLength in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairBLength u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure pairBLength in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairBLength u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure pairALength in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairALength 6
/*! \brief Preprocessor variable to relate field to bit position in structure pairALength in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairALength u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure pairALength in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairALength u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure pairDReflection_1 in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairDReflection_1 7
/*! \brief Preprocessor variable to relate field to bit position in structure pairDReflection_1 in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairDReflection_1 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure pairDReflection_1 in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairDReflection_1 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure pairDReflection_2 in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairDReflection_2 7
/*! \brief Preprocessor variable to relate field to bit position in structure pairDReflection_2 in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairDReflection_2 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure pairDReflection_2 in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairDReflection_2 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure pairDLength in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairDLength 8
/*! \brief Preprocessor variable to relate field to bit position in structure pairDLength in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairDLength u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure pairDLength in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairDLength u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure pairCLength in AQ_GlobalCableDiagnosticStatus_EUR */
#define AQ_GlobalCableDiagnosticStatus_EUR_pairCLength 8
/*! \brief Preprocessor variable to relate field to bit position in structure pairCLength in AQ_GlobalCableDiagnosticStatus_EUR */
#define bits_AQ_GlobalCableDiagnosticStatus_EUR_pairCLength u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure pairCLength in AQ_GlobalCableDiagnosticStatus_EUR */
#define word_AQ_GlobalCableDiagnosticStatus_EUR_pairCLength u8.word_8

/*! \brief Base register address of structure AQ_GlobalThermalStatus_EUR */
#define AQ_GlobalThermalStatus_EUR_baseRegisterAddress 0xC820
/*! \brief MMD address of structure AQ_GlobalThermalStatus_EUR */
#define AQ_GlobalThermalStatus_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure temperature in AQ_GlobalThermalStatus_EUR */
#define AQ_GlobalThermalStatus_EUR_temperature 0
/*! \brief Preprocessor variable to relate field to bit position in structure temperature in AQ_GlobalThermalStatus_EUR */
#define bits_AQ_GlobalThermalStatus_EUR_temperature u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure temperature in AQ_GlobalThermalStatus_EUR */
#define word_AQ_GlobalThermalStatus_EUR_temperature u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure temperatureReady in AQ_GlobalThermalStatus_EUR */
#define AQ_GlobalThermalStatus_EUR_temperatureReady 1
/*! \brief Preprocessor variable to relate field to bit position in structure temperatureReady in AQ_GlobalThermalStatus_EUR */
#define bits_AQ_GlobalThermalStatus_EUR_temperatureReady u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure temperatureReady in AQ_GlobalThermalStatus_EUR */
#define word_AQ_GlobalThermalStatus_EUR_temperatureReady u1.word_1

/*! \brief Base register address of structure AQ_GlobalGeneralStatus_EUR */
#define AQ_GlobalGeneralStatus_EUR_baseRegisterAddress 0xC830
/*! \brief MMD address of structure AQ_GlobalGeneralStatus_EUR */
#define AQ_GlobalGeneralStatus_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureFailureState in AQ_GlobalGeneralStatus_EUR */
#define AQ_GlobalGeneralStatus_EUR_highTemperatureFailureState 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureFailureState in AQ_GlobalGeneralStatus_EUR */
#define bits_AQ_GlobalGeneralStatus_EUR_highTemperatureFailureState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureFailureState in AQ_GlobalGeneralStatus_EUR */
#define word_AQ_GlobalGeneralStatus_EUR_highTemperatureFailureState u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureFailureState in AQ_GlobalGeneralStatus_EUR */
#define AQ_GlobalGeneralStatus_EUR_lowTemperatureFailureState 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureFailureState in AQ_GlobalGeneralStatus_EUR */
#define bits_AQ_GlobalGeneralStatus_EUR_lowTemperatureFailureState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureFailureState in AQ_GlobalGeneralStatus_EUR */
#define word_AQ_GlobalGeneralStatus_EUR_lowTemperatureFailureState u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureWarningState in AQ_GlobalGeneralStatus_EUR */
#define AQ_GlobalGeneralStatus_EUR_highTemperatureWarningState 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureWarningState in AQ_GlobalGeneralStatus_EUR */
#define bits_AQ_GlobalGeneralStatus_EUR_highTemperatureWarningState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureWarningState in AQ_GlobalGeneralStatus_EUR */
#define word_AQ_GlobalGeneralStatus_EUR_highTemperatureWarningState u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureWarningState in AQ_GlobalGeneralStatus_EUR */
#define AQ_GlobalGeneralStatus_EUR_lowTemperatureWarningState 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureWarningState in AQ_GlobalGeneralStatus_EUR */
#define bits_AQ_GlobalGeneralStatus_EUR_lowTemperatureWarningState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureWarningState in AQ_GlobalGeneralStatus_EUR */
#define word_AQ_GlobalGeneralStatus_EUR_lowTemperatureWarningState u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure processorIntensiveMdioOperationIn_Progress in AQ_GlobalGeneralStatus_EUR */
#define AQ_GlobalGeneralStatus_EUR_processorIntensiveMdioOperationIn_Progress 1
/*! \brief Preprocessor variable to relate field to bit position in structure processorIntensiveMdioOperationIn_Progress in AQ_GlobalGeneralStatus_EUR */
#define bits_AQ_GlobalGeneralStatus_EUR_processorIntensiveMdioOperationIn_Progress u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure processorIntensiveMdioOperationIn_Progress in AQ_GlobalGeneralStatus_EUR */
#define word_AQ_GlobalGeneralStatus_EUR_processorIntensiveMdioOperationIn_Progress u1.word_1

/*! \brief Base register address of structure AQ_GlobalPinStatus_EUR */
#define AQ_GlobalPinStatus_EUR_baseRegisterAddress 0xC840
/*! \brief MMD address of structure AQ_GlobalPinStatus_EUR */
#define AQ_GlobalPinStatus_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure dcMasterN in AQ_GlobalPinStatus_EUR */
#define AQ_GlobalPinStatus_EUR_dcMasterN 0
/*! \brief Preprocessor variable to relate field to bit position in structure dcMasterN in AQ_GlobalPinStatus_EUR */
#define bits_AQ_GlobalPinStatus_EUR_dcMasterN u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure dcMasterN in AQ_GlobalPinStatus_EUR */
#define word_AQ_GlobalPinStatus_EUR_dcMasterN u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure packageConnectivity in AQ_GlobalPinStatus_EUR */
#define AQ_GlobalPinStatus_EUR_packageConnectivity 0
/*! \brief Preprocessor variable to relate field to bit position in structure packageConnectivity in AQ_GlobalPinStatus_EUR */
#define bits_AQ_GlobalPinStatus_EUR_packageConnectivity u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure packageConnectivity in AQ_GlobalPinStatus_EUR */
#define word_AQ_GlobalPinStatus_EUR_packageConnectivity u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure txEnable in AQ_GlobalPinStatus_EUR */
#define AQ_GlobalPinStatus_EUR_txEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure txEnable in AQ_GlobalPinStatus_EUR */
#define bits_AQ_GlobalPinStatus_EUR_txEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure txEnable in AQ_GlobalPinStatus_EUR */
#define word_AQ_GlobalPinStatus_EUR_txEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ledPullupState in AQ_GlobalPinStatus_EUR */
#define AQ_GlobalPinStatus_EUR_ledPullupState 0
/*! \brief Preprocessor variable to relate field to bit position in structure ledPullupState in AQ_GlobalPinStatus_EUR */
#define bits_AQ_GlobalPinStatus_EUR_ledPullupState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ledPullupState in AQ_GlobalPinStatus_EUR */
#define word_AQ_GlobalPinStatus_EUR_ledPullupState u0.word_0

/*! \brief Base register address of structure AQ_GlobalDaisyChainStatus_EUR */
#define AQ_GlobalDaisyChainStatus_EUR_baseRegisterAddress 0xC842
/*! \brief MMD address of structure AQ_GlobalDaisyChainStatus_EUR */
#define AQ_GlobalDaisyChainStatus_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure rxDaisyChainCalculatedCrc in AQ_GlobalDaisyChainStatus_EUR */
#define AQ_GlobalDaisyChainStatus_EUR_rxDaisyChainCalculatedCrc 0
/*! \brief Preprocessor variable to relate field to bit position in structure rxDaisyChainCalculatedCrc in AQ_GlobalDaisyChainStatus_EUR */
#define bits_AQ_GlobalDaisyChainStatus_EUR_rxDaisyChainCalculatedCrc u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rxDaisyChainCalculatedCrc in AQ_GlobalDaisyChainStatus_EUR */
#define word_AQ_GlobalDaisyChainStatus_EUR_rxDaisyChainCalculatedCrc u0.word_0

/*! \brief Base register address of structure AQ_GlobalDaisyChainHopCount_EUR */
#define AQ_GlobalDaisyChainHopCount_EUR_baseRegisterAddress 0xC84E
/*! \brief MMD address of structure AQ_GlobalDaisyChainHopCount_EUR */
#define AQ_GlobalDaisyChainHopCount_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure daisyChainHopCount in AQ_GlobalDaisyChainHopCount_EUR */
#define AQ_GlobalDaisyChainHopCount_EUR_daisyChainHopCount 0
/*! \brief Preprocessor variable to relate field to bit position in structure daisyChainHopCount in AQ_GlobalDaisyChainHopCount_EUR */
#define bits_AQ_GlobalDaisyChainHopCount_EUR_daisyChainHopCount u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure daisyChainHopCount in AQ_GlobalDaisyChainHopCount_EUR */
#define word_AQ_GlobalDaisyChainHopCount_EUR_daisyChainHopCount u0.word_0

/*! \brief Base register address of structure AQ_GlobalFaultMessage_EUR */
#define AQ_GlobalFaultMessage_EUR_baseRegisterAddress 0xC850
/*! \brief MMD address of structure AQ_GlobalFaultMessage_EUR */
#define AQ_GlobalFaultMessage_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure message in AQ_GlobalFaultMessage_EUR */
#define AQ_GlobalFaultMessage_EUR_message 0
/*! \brief Preprocessor variable to relate field to bit position in structure message in AQ_GlobalFaultMessage_EUR */
#define bits_AQ_GlobalFaultMessage_EUR_message u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure message in AQ_GlobalFaultMessage_EUR */
#define word_AQ_GlobalFaultMessage_EUR_message u0.word_0

/*! \brief Base register address of structure AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_baseRegisterAddress 0xC880
/*! \brief MMD address of structure AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure reserved_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairAReflection_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairAReflection_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairAReflection_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairAReflection_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairAReflection_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairAReflection_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairAReflection_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairAReflection_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairAReflection_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairAReflection_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairAReflection_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairAReflection_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_3 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_3 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_3 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairAReflection_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairAReflection_3 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairAReflection_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairAReflection_3 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairAReflection_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairAReflection_3 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_4 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_4 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_4 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairAReflection_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairAReflection_4 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairAReflection_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairAReflection_4 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairAReflection_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairAReflection_4 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_5 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_5 1
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_5 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_5 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reserved_5 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_5 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure pairBReflection_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairBReflection_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure pairBReflection_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairBReflection_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pairBReflection_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairBReflection_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reserved_6 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_6 1
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_6 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_6 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reserved_6 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_6 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure pairBReflection_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairBReflection_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure pairBReflection_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairBReflection_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pairBReflection_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairBReflection_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reserved_7 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_7 1
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_7 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_7 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reserved_7 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_7 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure pairBReflection_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairBReflection_3 1
/*! \brief Preprocessor variable to relate field to bit position in structure pairBReflection_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairBReflection_3 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pairBReflection_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairBReflection_3 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reserved_8 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_8 1
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_8 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_8 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reserved_8 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_8 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure pairBReflection_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairBReflection_4 1
/*! \brief Preprocessor variable to relate field to bit position in structure pairBReflection_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairBReflection_4 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pairBReflection_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairBReflection_4 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reserved_9 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_9 2
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_9 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_9 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reserved_9 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_9 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pairCReflection_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairCReflection_1 2
/*! \brief Preprocessor variable to relate field to bit position in structure pairCReflection_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairCReflection_1 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure pairCReflection_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairCReflection_1 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reserved_10 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_10 2
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_10 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_10 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reserved_10 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_10 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pairCReflection_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairCReflection_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure pairCReflection_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairCReflection_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure pairCReflection_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairCReflection_2 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reserved_11 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_11 2
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_11 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_11 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reserved_11 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_11 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pairCReflection_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairCReflection_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure pairCReflection_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairCReflection_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure pairCReflection_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairCReflection_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reserved_12 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_12 2
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_12 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_12 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reserved_12 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_12 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pairCReflection_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairCReflection_4 2
/*! \brief Preprocessor variable to relate field to bit position in structure pairCReflection_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairCReflection_4 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure pairCReflection_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairCReflection_4 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reserved_13 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_13 3
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_13 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_13 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reserved_13 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_13 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure pairDReflection_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairDReflection_1 3
/*! \brief Preprocessor variable to relate field to bit position in structure pairDReflection_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairDReflection_1 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pairDReflection_1 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairDReflection_1 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reserved_14 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_14 3
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_14 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_14 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reserved_14 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_14 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure pairDReflection_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairDReflection_2 3
/*! \brief Preprocessor variable to relate field to bit position in structure pairDReflection_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairDReflection_2 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pairDReflection_2 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairDReflection_2 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reserved_15 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_15 3
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_15 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_15 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reserved_15 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_15 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure pairDReflection_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairDReflection_3 3
/*! \brief Preprocessor variable to relate field to bit position in structure pairDReflection_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairDReflection_3 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pairDReflection_3 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairDReflection_3 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reserved_16 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_reserved_16 3
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_16 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_16 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reserved_16 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_reserved_16 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure pairDReflection_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define AQ_GlobalCableDiagnosticImpedance_EUR_pairDReflection_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure pairDReflection_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define bits_AQ_GlobalCableDiagnosticImpedance_EUR_pairDReflection_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pairDReflection_4 in AQ_GlobalCableDiagnosticImpedance_EUR */
#define word_AQ_GlobalCableDiagnosticImpedance_EUR_pairDReflection_4 u3.word_3

/*! \brief Base register address of structure AQ_GlobalStatus_EUR */
#define AQ_GlobalStatus_EUR_baseRegisterAddress 0xC884
/*! \brief MMD address of structure AQ_GlobalStatus_EUR */
#define AQ_GlobalStatus_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure reservedStatus_0 in AQ_GlobalStatus_EUR */
#define AQ_GlobalStatus_EUR_reservedStatus_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedStatus_0 in AQ_GlobalStatus_EUR */
#define bits_AQ_GlobalStatus_EUR_reservedStatus_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedStatus_0 in AQ_GlobalStatus_EUR */
#define word_AQ_GlobalStatus_EUR_reservedStatus_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure cableLength in AQ_GlobalStatus_EUR */
#define AQ_GlobalStatus_EUR_cableLength 0
/*! \brief Preprocessor variable to relate field to bit position in structure cableLength in AQ_GlobalStatus_EUR */
#define bits_AQ_GlobalStatus_EUR_cableLength u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure cableLength in AQ_GlobalStatus_EUR */
#define word_AQ_GlobalStatus_EUR_cableLength u0.word_0

/*! \brief Base register address of structure AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_baseRegisterAddress 0xC885
/*! \brief MMD address of structure AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure nearlySecondsMSW in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_nearlySecondsMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure nearlySecondsMSW in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_nearlySecondsMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nearlySecondsMSW in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_nearlySecondsMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xenpakNvrStatus in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_xenpakNvrStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure xenpakNvrStatus in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_xenpakNvrStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xenpakNvrStatus in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_xenpakNvrStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure firmwareBuildID in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_firmwareBuildID 0
/*! \brief Preprocessor variable to relate field to bit position in structure firmwareBuildID in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_firmwareBuildID u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure firmwareBuildID in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_firmwareBuildID u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure provisioningID in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_provisioningID 0
/*! \brief Preprocessor variable to relate field to bit position in structure provisioningID in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_provisioningID u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure provisioningID in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_provisioningID u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nearlySecondsLSW in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_nearlySecondsLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure nearlySecondsLSW in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_nearlySecondsLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure nearlySecondsLSW in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_nearlySecondsLSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure dteStatus in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_dteStatus 2
/*! \brief Preprocessor variable to relate field to bit position in structure dteStatus in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_dteStatus u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure dteStatus in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_dteStatus u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure powerUpStallStatus in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_powerUpStallStatus 2
/*! \brief Preprocessor variable to relate field to bit position in structure powerUpStallStatus in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_powerUpStallStatus u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure powerUpStallStatus in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_powerUpStallStatus u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedStatus_3 in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_reservedStatus_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedStatus_3 in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_reservedStatus_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedStatus_3 in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_reservedStatus_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure loopbackStatus in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_loopbackStatus 3
/*! \brief Preprocessor variable to relate field to bit position in structure loopbackStatus in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_loopbackStatus u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure loopbackStatus in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_loopbackStatus u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reservedStatus_4 in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_reservedStatus_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedStatus_4 in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_reservedStatus_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedStatus_4 in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_reservedStatus_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure mdiPacketGenerationStatus in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_mdiPacketGenerationStatus 3
/*! \brief Preprocessor variable to relate field to bit position in structure mdiPacketGenerationStatus in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_mdiPacketGenerationStatus u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure mdiPacketGenerationStatus in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_mdiPacketGenerationStatus u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure look_asidePortPacketGenerationStatus in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_look_asidePortPacketGenerationStatus 3
/*! \brief Preprocessor variable to relate field to bit position in structure look_asidePortPacketGenerationStatus in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_look_asidePortPacketGenerationStatus u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure look_asidePortPacketGenerationStatus in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_look_asidePortPacketGenerationStatus u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure systemI_fPacketGenerationStatus in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_systemI_fPacketGenerationStatus 3
/*! \brief Preprocessor variable to relate field to bit position in structure systemI_fPacketGenerationStatus in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_systemI_fPacketGenerationStatus u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure systemI_fPacketGenerationStatus in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_systemI_fPacketGenerationStatus u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure rate in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_rate 3
/*! \brief Preprocessor variable to relate field to bit position in structure rate in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_rate u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure rate in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_rate u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reservedStatus_5 in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_reservedStatus_5 4
/*! \brief Preprocessor variable to relate field to bit position in structure reservedStatus_5 in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_reservedStatus_5 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure reservedStatus_5 in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_reservedStatus_5 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure reservedStatus_6 in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_reservedStatus_6 5
/*! \brief Preprocessor variable to relate field to bit position in structure reservedStatus_6 in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_reservedStatus_6 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure reservedStatus_6 in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_reservedStatus_6 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure reservedStatus_7 in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_reservedStatus_7 6
/*! \brief Preprocessor variable to relate field to bit position in structure reservedStatus_7 in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_reservedStatus_7 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure reservedStatus_7 in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_reservedStatus_7 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure reservedStatus_8 in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_reservedStatus_8 7
/*! \brief Preprocessor variable to relate field to bit position in structure reservedStatus_8 in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_reservedStatus_8 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure reservedStatus_8 in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_reservedStatus_8 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure reservedStatus_9 in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_reservedStatus_9 8
/*! \brief Preprocessor variable to relate field to bit position in structure reservedStatus_9 in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_reservedStatus_9 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure reservedStatus_9 in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_reservedStatus_9 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure resolvedConstellation in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_resolvedConstellation 8
/*! \brief Preprocessor variable to relate field to bit position in structure resolvedConstellation in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_resolvedConstellation u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure resolvedConstellation in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_resolvedConstellation u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure resolvedActiveLaneCapability in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_resolvedActiveLaneCapability 8
/*! \brief Preprocessor variable to relate field to bit position in structure resolvedActiveLaneCapability in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_resolvedActiveLaneCapability u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure resolvedActiveLaneCapability in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_resolvedActiveLaneCapability u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure resolvedBaudRate in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_resolvedBaudRate 9
/*! \brief Preprocessor variable to relate field to bit position in structure resolvedBaudRate in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_resolvedBaudRate u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure resolvedBaudRate in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_resolvedBaudRate u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure customerProvisioningID in AQ_GlobalReservedStatus_EUR */
#define AQ_GlobalReservedStatus_EUR_customerProvisioningID 10
/*! \brief Preprocessor variable to relate field to bit position in structure customerProvisioningID in AQ_GlobalReservedStatus_EUR */
#define bits_AQ_GlobalReservedStatus_EUR_customerProvisioningID u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure customerProvisioningID in AQ_GlobalReservedStatus_EUR */
#define word_AQ_GlobalReservedStatus_EUR_customerProvisioningID u10.word_10

/*! \brief Base register address of structure AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_baseRegisterAddress 0xCC00
/*! \brief MMD address of structure AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureFailure in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_highTemperatureFailure 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureFailure in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_highTemperatureFailure u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureFailure in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_highTemperatureFailure u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureFailure in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_lowTemperatureFailure 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureFailure in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_lowTemperatureFailure u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureFailure in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_lowTemperatureFailure u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureWarning in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_highTemperatureWarning 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureWarning in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_highTemperatureWarning u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureWarning in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_highTemperatureWarning u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureWarning in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_lowTemperatureWarning 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureWarning in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_lowTemperatureWarning u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureWarning in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_lowTemperatureWarning u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure resetCompleted in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_resetCompleted 0
/*! \brief Preprocessor variable to relate field to bit position in structure resetCompleted in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_resetCompleted u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure resetCompleted in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_resetCompleted u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure deviceFault in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_deviceFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure deviceFault in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_deviceFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure deviceFault in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_deviceFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmA in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_reservedAlarmA 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmA in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_reservedAlarmA u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmA in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_reservedAlarmA u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmB in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_reservedAlarmB 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmB in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_reservedAlarmB u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmB in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_reservedAlarmB u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmC in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_reservedAlarmC 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmC in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_reservedAlarmC u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmC in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_reservedAlarmC u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmD in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_reservedAlarmD 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmD in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_reservedAlarmD u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmD in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_reservedAlarmD u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure smartPower_downEntered in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_smartPower_downEntered 1
/*! \brief Preprocessor variable to relate field to bit position in structure smartPower_downEntered in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_smartPower_downEntered u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure smartPower_downEntered in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_smartPower_downEntered u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xenpakAlarm in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_xenpakAlarm 1
/*! \brief Preprocessor variable to relate field to bit position in structure xenpakAlarm in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_xenpakAlarm u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xenpakAlarm in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_xenpakAlarm u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ipPhoneDetect in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_ipPhoneDetect 1
/*! \brief Preprocessor variable to relate field to bit position in structure ipPhoneDetect in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_ipPhoneDetect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ipPhoneDetect in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_ipPhoneDetect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure dteStatusChange in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_dteStatusChange 1
/*! \brief Preprocessor variable to relate field to bit position in structure dteStatusChange in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_dteStatusChange u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure dteStatusChange in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_dteStatusChange u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure fastLinkDrop in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_fastLinkDrop 1
/*! \brief Preprocessor variable to relate field to bit position in structure fastLinkDrop in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_fastLinkDrop u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure fastLinkDrop in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_fastLinkDrop u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure sfpDdmiMemoryLoadFailed in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_sfpDdmiMemoryLoadFailed 1
/*! \brief Preprocessor variable to relate field to bit position in structure sfpDdmiMemoryLoadFailed in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_sfpDdmiMemoryLoadFailed u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure sfpDdmiMemoryLoadFailed in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_sfpDdmiMemoryLoadFailed u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure smb0StateMachineTimeout in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_smb0StateMachineTimeout 1
/*! \brief Preprocessor variable to relate field to bit position in structure smb0StateMachineTimeout in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_smb0StateMachineTimeout u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure smb0StateMachineTimeout in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_smb0StateMachineTimeout u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mdioCommandHandlingOverflow in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_mdioCommandHandlingOverflow 1
/*! \brief Preprocessor variable to relate field to bit position in structure mdioCommandHandlingOverflow in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_mdioCommandHandlingOverflow u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mdioCommandHandlingOverflow in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_mdioCommandHandlingOverflow u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure diagnosticAlarm in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_diagnosticAlarm 1
/*! \brief Preprocessor variable to relate field to bit position in structure diagnosticAlarm in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_diagnosticAlarm u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure diagnosticAlarm in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_diagnosticAlarm u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure nvrOperationComplete in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_nvrOperationComplete 2
/*! \brief Preprocessor variable to relate field to bit position in structure nvrOperationComplete in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_nvrOperationComplete u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure nvrOperationComplete in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_nvrOperationComplete u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mailboxOperation_Complete in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_mailboxOperation_Complete 2
/*! \brief Preprocessor variable to relate field to bit position in structure mailboxOperation_Complete in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_mailboxOperation_Complete u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mailboxOperation_Complete in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_mailboxOperation_Complete u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure upDramParityError in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_upDramParityError 2
/*! \brief Preprocessor variable to relate field to bit position in structure upDramParityError in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_upDramParityError u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure upDramParityError in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_upDramParityError u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure upIramParityError in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_upIramParityError 2
/*! \brief Preprocessor variable to relate field to bit position in structure upIramParityError in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_upIramParityError u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure upIramParityError in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_upIramParityError u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure txEnableStateChange in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_txEnableStateChange 2
/*! \brief Preprocessor variable to relate field to bit position in structure txEnableStateChange in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_txEnableStateChange u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure txEnableStateChange in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_txEnableStateChange u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mdioMMD_Error in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_mdioMMD_Error 2
/*! \brief Preprocessor variable to relate field to bit position in structure mdioMMD_Error in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_mdioMMD_Error u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mdioMMD_Error in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_mdioMMD_Error u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mdioTimeoutError in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_mdioTimeoutError 2
/*! \brief Preprocessor variable to relate field to bit position in structure mdioTimeoutError in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_mdioTimeoutError u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mdioTimeoutError in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_mdioTimeoutError u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure watchdogTimerAlarm in AQ_GlobalAlarms_EUR */
#define AQ_GlobalAlarms_EUR_watchdogTimerAlarm 2
/*! \brief Preprocessor variable to relate field to bit position in structure watchdogTimerAlarm in AQ_GlobalAlarms_EUR */
#define bits_AQ_GlobalAlarms_EUR_watchdogTimerAlarm u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure watchdogTimerAlarm in AQ_GlobalAlarms_EUR */
#define word_AQ_GlobalAlarms_EUR_watchdogTimerAlarm u2.word_2

/*! \brief Base register address of structure AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_baseRegisterAddress 0xD400
/*! \brief MMD address of structure AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureFailureMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_highTemperatureFailureMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureFailureMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_highTemperatureFailureMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureFailureMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_highTemperatureFailureMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureFailureMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_lowTemperatureFailureMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureFailureMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_lowTemperatureFailureMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureFailureMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_lowTemperatureFailureMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureWarningMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_highTemperatureWarningMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureWarningMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_highTemperatureWarningMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureWarningMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_highTemperatureWarningMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureWarningMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_lowTemperatureWarningMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureWarningMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_lowTemperatureWarningMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureWarningMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_lowTemperatureWarningMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure resetCompletedMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_resetCompletedMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure resetCompletedMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_resetCompletedMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure resetCompletedMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_resetCompletedMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure deviceFaultMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_deviceFaultMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure deviceFaultMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_deviceFaultMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure deviceFaultMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_deviceFaultMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmAMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_reservedAlarmAMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmAMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_reservedAlarmAMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmAMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_reservedAlarmAMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmBMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_reservedAlarmBMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmBMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_reservedAlarmBMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmBMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_reservedAlarmBMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmCMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_reservedAlarmCMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmCMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_reservedAlarmCMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmCMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_reservedAlarmCMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmDMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_reservedAlarmDMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmDMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_reservedAlarmDMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmDMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_reservedAlarmDMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure smartPower_downEnteredMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_smartPower_downEnteredMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure smartPower_downEnteredMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_smartPower_downEnteredMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure smartPower_downEnteredMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_smartPower_downEnteredMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xenpakAlarmMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_xenpakAlarmMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure xenpakAlarmMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_xenpakAlarmMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xenpakAlarmMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_xenpakAlarmMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ipPhoneDetectMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_ipPhoneDetectMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure ipPhoneDetectMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_ipPhoneDetectMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ipPhoneDetectMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_ipPhoneDetectMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure dteStatusChangeMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_dteStatusChangeMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure dteStatusChangeMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_dteStatusChangeMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure dteStatusChangeMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_dteStatusChangeMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure fastLinkDropMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_fastLinkDropMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure fastLinkDropMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_fastLinkDropMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure fastLinkDropMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_fastLinkDropMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure sfpDdmiMemoryLoadMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_sfpDdmiMemoryLoadMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure sfpDdmiMemoryLoadMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_sfpDdmiMemoryLoadMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure sfpDdmiMemoryLoadMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_sfpDdmiMemoryLoadMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure smb0StateMachineTimeoutMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_smb0StateMachineTimeoutMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure smb0StateMachineTimeoutMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_smb0StateMachineTimeoutMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure smb0StateMachineTimeoutMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_smb0StateMachineTimeoutMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mdioCommandHandlingOverflowMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_mdioCommandHandlingOverflowMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure mdioCommandHandlingOverflowMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_mdioCommandHandlingOverflowMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mdioCommandHandlingOverflowMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_mdioCommandHandlingOverflowMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure diagnosticAlarmMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_diagnosticAlarmMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure diagnosticAlarmMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_diagnosticAlarmMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure diagnosticAlarmMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_diagnosticAlarmMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure nvrOperationCompleteMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_nvrOperationCompleteMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure nvrOperationCompleteMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_nvrOperationCompleteMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure nvrOperationCompleteMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_nvrOperationCompleteMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mailboxOperationCompleteMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_mailboxOperationCompleteMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure mailboxOperationCompleteMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_mailboxOperationCompleteMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mailboxOperationCompleteMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_mailboxOperationCompleteMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure upDramParityErrorMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_upDramParityErrorMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure upDramParityErrorMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_upDramParityErrorMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure upDramParityErrorMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_upDramParityErrorMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure upIramParityErrorMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_upIramParityErrorMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure upIramParityErrorMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_upIramParityErrorMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure upIramParityErrorMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_upIramParityErrorMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure txEnableStateChangeMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_txEnableStateChangeMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure txEnableStateChangeMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_txEnableStateChangeMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure txEnableStateChangeMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_txEnableStateChangeMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mdioMMD_ErrorMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_mdioMMD_ErrorMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure mdioMMD_ErrorMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_mdioMMD_ErrorMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mdioMMD_ErrorMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_mdioMMD_ErrorMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mdioTimeoutErrorMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_mdioTimeoutErrorMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure mdioTimeoutErrorMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_mdioTimeoutErrorMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mdioTimeoutErrorMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_mdioTimeoutErrorMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure watchdogTimerAlarmMask in AQ_GlobalInterruptMask_EUR */
#define AQ_GlobalInterruptMask_EUR_watchdogTimerAlarmMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure watchdogTimerAlarmMask in AQ_GlobalInterruptMask_EUR */
#define bits_AQ_GlobalInterruptMask_EUR_watchdogTimerAlarmMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure watchdogTimerAlarmMask in AQ_GlobalInterruptMask_EUR */
#define word_AQ_GlobalInterruptMask_EUR_watchdogTimerAlarmMask u2.word_2

/*! \brief Base register address of structure AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define AQ_GlobalChip_wideStandardInterruptFlags_EUR_baseRegisterAddress 0xFC00
/*! \brief MMD address of structure AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define AQ_GlobalChip_wideStandardInterruptFlags_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure pmaStandardAlarm_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define AQ_GlobalChip_wideStandardInterruptFlags_EUR_pmaStandardAlarm_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaStandardAlarm_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_EUR_pmaStandardAlarm_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaStandardAlarm_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_EUR_pmaStandardAlarm_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaStandardAlarm_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define AQ_GlobalChip_wideStandardInterruptFlags_EUR_pmaStandardAlarm_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaStandardAlarm_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_EUR_pmaStandardAlarm_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaStandardAlarm_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_EUR_pmaStandardAlarm_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsStandardAlarm_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define AQ_GlobalChip_wideStandardInterruptFlags_EUR_pcsStandardAlarm_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsStandardAlarm_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_EUR_pcsStandardAlarm_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsStandardAlarm_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_EUR_pcsStandardAlarm_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsStandardAlarm_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define AQ_GlobalChip_wideStandardInterruptFlags_EUR_pcsStandardAlarm_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsStandardAlarm_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_EUR_pcsStandardAlarm_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsStandardAlarm_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_EUR_pcsStandardAlarm_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsStandardAlarm_3Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define AQ_GlobalChip_wideStandardInterruptFlags_EUR_pcsStandardAlarm_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsStandardAlarm_3Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_EUR_pcsStandardAlarm_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsStandardAlarm_3Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_EUR_pcsStandardAlarm_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_StandardAlarms_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define AQ_GlobalChip_wideStandardInterruptFlags_EUR_phyXS_StandardAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_StandardAlarms_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_EUR_phyXS_StandardAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_StandardAlarms_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_EUR_phyXS_StandardAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_StandardAlarms_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define AQ_GlobalChip_wideStandardInterruptFlags_EUR_phyXS_StandardAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_StandardAlarms_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_EUR_phyXS_StandardAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_StandardAlarms_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_EUR_phyXS_StandardAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationStandardAlarms_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define AQ_GlobalChip_wideStandardInterruptFlags_EUR_autonegotiationStandardAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationStandardAlarms_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_EUR_autonegotiationStandardAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationStandardAlarms_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_EUR_autonegotiationStandardAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationStandardAlarms_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define AQ_GlobalChip_wideStandardInterruptFlags_EUR_autonegotiationStandardAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationStandardAlarms_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_EUR_autonegotiationStandardAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationStandardAlarms_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_EUR_autonegotiationStandardAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure gbeStandardAlarmsInterrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define AQ_GlobalChip_wideStandardInterruptFlags_EUR_gbeStandardAlarmsInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure gbeStandardAlarmsInterrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_EUR_gbeStandardAlarmsInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure gbeStandardAlarmsInterrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_EUR_gbeStandardAlarmsInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure allVendorAlarmsInterrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define AQ_GlobalChip_wideStandardInterruptFlags_EUR_allVendorAlarmsInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure allVendorAlarmsInterrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_EUR_allVendorAlarmsInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure allVendorAlarmsInterrupt in AQ_GlobalChip_wideStandardInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_EUR_allVendorAlarmsInterrupt u0.word_0

/*! \brief Base register address of structure AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define AQ_GlobalChip_wideVendorInterruptFlags_EUR_baseRegisterAddress 0xFC01
/*! \brief MMD address of structure AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define AQ_GlobalChip_wideVendorInterruptFlags_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure pmaVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define AQ_GlobalChip_wideVendorInterruptFlags_EUR_pmaVendorAlarmInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_EUR_pmaVendorAlarmInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_EUR_pmaVendorAlarmInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define AQ_GlobalChip_wideVendorInterruptFlags_EUR_pcsVendorAlarmInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_EUR_pcsVendorAlarmInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_EUR_pcsVendorAlarmInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_VendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define AQ_GlobalChip_wideVendorInterruptFlags_EUR_phyXS_VendorAlarmInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_VendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_EUR_phyXS_VendorAlarmInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_VendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_EUR_phyXS_VendorAlarmInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define AQ_GlobalChip_wideVendorInterruptFlags_EUR_autonegotiationVendorAlarmInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_EUR_autonegotiationVendorAlarmInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_EUR_autonegotiationVendorAlarmInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure gbeVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define AQ_GlobalChip_wideVendorInterruptFlags_EUR_gbeVendorAlarmInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure gbeVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_EUR_gbeVendorAlarmInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure gbeVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_EUR_gbeVendorAlarmInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure globalAlarms_1Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define AQ_GlobalChip_wideVendorInterruptFlags_EUR_globalAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalAlarms_1Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_EUR_globalAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalAlarms_1Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_EUR_globalAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure globalAlarms_2Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define AQ_GlobalChip_wideVendorInterruptFlags_EUR_globalAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalAlarms_2Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_EUR_globalAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalAlarms_2Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_EUR_globalAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure globalAlarms_3Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define AQ_GlobalChip_wideVendorInterruptFlags_EUR_globalAlarms_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalAlarms_3Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_EUR_globalAlarms_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalAlarms_3Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_EUR */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_EUR_globalAlarms_3Interrupt u0.word_0

/*! \brief Base register address of structure AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define AQ_GlobalInterruptChip_wideStandardMask_EUR_baseRegisterAddress 0xFF00
/*! \brief MMD address of structure AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define AQ_GlobalInterruptChip_wideStandardMask_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure pmaStandardAlarm_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define AQ_GlobalInterruptChip_wideStandardMask_EUR_pmaStandardAlarm_1InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaStandardAlarm_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_EUR_pmaStandardAlarm_1InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaStandardAlarm_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define word_AQ_GlobalInterruptChip_wideStandardMask_EUR_pmaStandardAlarm_1InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaStandardAlarm_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define AQ_GlobalInterruptChip_wideStandardMask_EUR_pmaStandardAlarm_2InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaStandardAlarm_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_EUR_pmaStandardAlarm_2InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaStandardAlarm_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define word_AQ_GlobalInterruptChip_wideStandardMask_EUR_pmaStandardAlarm_2InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsStandardAlarm_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define AQ_GlobalInterruptChip_wideStandardMask_EUR_pcsStandardAlarm_1InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsStandardAlarm_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_EUR_pcsStandardAlarm_1InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsStandardAlarm_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define word_AQ_GlobalInterruptChip_wideStandardMask_EUR_pcsStandardAlarm_1InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsStandardAlarm_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define AQ_GlobalInterruptChip_wideStandardMask_EUR_pcsStandardAlarm_2InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsStandardAlarm_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_EUR_pcsStandardAlarm_2InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsStandardAlarm_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define word_AQ_GlobalInterruptChip_wideStandardMask_EUR_pcsStandardAlarm_2InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsStandardAlarm_3InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define AQ_GlobalInterruptChip_wideStandardMask_EUR_pcsStandardAlarm_3InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsStandardAlarm_3InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_EUR_pcsStandardAlarm_3InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsStandardAlarm_3InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define word_AQ_GlobalInterruptChip_wideStandardMask_EUR_pcsStandardAlarm_3InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_StandardAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define AQ_GlobalInterruptChip_wideStandardMask_EUR_phyXS_StandardAlarms_1InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_StandardAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_EUR_phyXS_StandardAlarms_1InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_StandardAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define word_AQ_GlobalInterruptChip_wideStandardMask_EUR_phyXS_StandardAlarms_1InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_StandardAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define AQ_GlobalInterruptChip_wideStandardMask_EUR_phyXS_StandardAlarms_2InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_StandardAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_EUR_phyXS_StandardAlarms_2InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_StandardAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define word_AQ_GlobalInterruptChip_wideStandardMask_EUR_phyXS_StandardAlarms_2InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationStandardAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define AQ_GlobalInterruptChip_wideStandardMask_EUR_autonegotiationStandardAlarms_1InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationStandardAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_EUR_autonegotiationStandardAlarms_1InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationStandardAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define word_AQ_GlobalInterruptChip_wideStandardMask_EUR_autonegotiationStandardAlarms_1InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationStandardAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define AQ_GlobalInterruptChip_wideStandardMask_EUR_autonegotiationStandardAlarms_2InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationStandardAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_EUR_autonegotiationStandardAlarms_2InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationStandardAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define word_AQ_GlobalInterruptChip_wideStandardMask_EUR_autonegotiationStandardAlarms_2InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure gbeStandardAlarmsInterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define AQ_GlobalInterruptChip_wideStandardMask_EUR_gbeStandardAlarmsInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure gbeStandardAlarmsInterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_EUR_gbeStandardAlarmsInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure gbeStandardAlarmsInterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define word_AQ_GlobalInterruptChip_wideStandardMask_EUR_gbeStandardAlarmsInterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure allVendorAlarmsInterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define AQ_GlobalInterruptChip_wideStandardMask_EUR_allVendorAlarmsInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure allVendorAlarmsInterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_EUR_allVendorAlarmsInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure allVendorAlarmsInterruptMask in AQ_GlobalInterruptChip_wideStandardMask_EUR */
#define word_AQ_GlobalInterruptChip_wideStandardMask_EUR_allVendorAlarmsInterruptMask u0.word_0

/*! \brief Base register address of structure AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define AQ_GlobalInterruptChip_wideVendorMask_EUR_baseRegisterAddress 0xFF01
/*! \brief MMD address of structure AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define AQ_GlobalInterruptChip_wideVendorMask_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure pmaVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define AQ_GlobalInterruptChip_wideVendorMask_EUR_pmaVendorAlarmInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_EUR_pmaVendorAlarmInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define word_AQ_GlobalInterruptChip_wideVendorMask_EUR_pmaVendorAlarmInterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define AQ_GlobalInterruptChip_wideVendorMask_EUR_pcsVendorAlarmInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_EUR_pcsVendorAlarmInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define word_AQ_GlobalInterruptChip_wideVendorMask_EUR_pcsVendorAlarmInterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_VendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define AQ_GlobalInterruptChip_wideVendorMask_EUR_phyXS_VendorAlarmInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_VendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_EUR_phyXS_VendorAlarmInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_VendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define word_AQ_GlobalInterruptChip_wideVendorMask_EUR_phyXS_VendorAlarmInterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define AQ_GlobalInterruptChip_wideVendorMask_EUR_autonegotiationVendorAlarmInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_EUR_autonegotiationVendorAlarmInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define word_AQ_GlobalInterruptChip_wideVendorMask_EUR_autonegotiationVendorAlarmInterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure gbeVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define AQ_GlobalInterruptChip_wideVendorMask_EUR_gbeVendorAlarmInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure gbeVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_EUR_gbeVendorAlarmInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure gbeVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define word_AQ_GlobalInterruptChip_wideVendorMask_EUR_gbeVendorAlarmInterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure globalAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define AQ_GlobalInterruptChip_wideVendorMask_EUR_globalAlarms_1InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_EUR_globalAlarms_1InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define word_AQ_GlobalInterruptChip_wideVendorMask_EUR_globalAlarms_1InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure globalAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define AQ_GlobalInterruptChip_wideVendorMask_EUR_globalAlarms_2InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_EUR_globalAlarms_2InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define word_AQ_GlobalInterruptChip_wideVendorMask_EUR_globalAlarms_2InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure globalAlarms_3InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define AQ_GlobalInterruptChip_wideVendorMask_EUR_globalAlarms_3InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalAlarms_3InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_EUR_globalAlarms_3InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalAlarms_3InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_EUR */
#define word_AQ_GlobalInterruptChip_wideVendorMask_EUR_globalAlarms_3InterruptMask u0.word_0
#endif
/*@}*/
/*@}*/
