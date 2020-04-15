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

/*! \brief Base register address of structure AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_baseRegisterAddress 0x5002
/*! \brief MMD address of structure AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressEthertypeExplicitSectagLsb in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressEthertypeExplicitSectagLsb 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressEthertypeExplicitSectagLsb in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressEthertypeExplicitSectagLsb u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressEthertypeExplicitSectagLsb in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressEthertypeExplicitSectagLsb u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressClearGlobalTime in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressClearGlobalTime 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressClearGlobalTime in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressClearGlobalTime u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressClearGlobalTime in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressClearGlobalTime u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressClearCounter in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressClearCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressClearCounter in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressClearCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressClearCounter in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressClearCounter u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressHighPriority in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressHighPriority 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressHighPriority in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressHighPriority u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressHighPriority in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressHighPriority u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressIcvLsb_8BytesEnable in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressIcvLsb_8BytesEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressIcvLsb_8BytesEnable in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressIcvLsb_8BytesEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressIcvLsb_8BytesEnable in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressIcvLsb_8BytesEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressExternalClassificationEnable in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressExternalClassificationEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressExternalClassificationEnable in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressExternalClassificationEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressExternalClassificationEnable in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressExternalClassificationEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressExplicitSectagReportShortLength in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressExplicitSectagReportShortLength 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressExplicitSectagReportShortLength in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressExplicitSectagReportShortLength u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressExplicitSectagReportShortLength in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressExplicitSectagReportShortLength u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressDropInvalidSa_scPackets in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressDropInvalidSa_scPackets 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressDropInvalidSa_scPackets in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressDropInvalidSa_scPackets u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressDropInvalidSa_scPackets in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressDropInvalidSa_scPackets u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressUnmatchedUseSc_0 in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressUnmatchedUseSc_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressUnmatchedUseSc_0 in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressUnmatchedUseSc_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressUnmatchedUseSc_0 in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressUnmatchedUseSc_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgresssGcmTestMode in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgresssGcmTestMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgresssGcmTestMode in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgresssGcmTestMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgresssGcmTestMode in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgresssGcmTestMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressGcmStart in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressGcmStart 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressGcmStart in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressGcmStart u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressGcmStart in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressGcmStart u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressDropEgprcLutMiss in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressDropEgprcLutMiss 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressDropEgprcLutMiss in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressDropEgprcLutMiss u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressDropEgprcLutMiss in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressDropEgprcLutMiss u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressDropKayPacket in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressDropKayPacket 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressDropKayPacket in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressDropKayPacket u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressDropKayPacket in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressDropKayPacket u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressSoftReset in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressSoftReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressSoftReset in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressSoftReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressSoftReset in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressSoftReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressEthertypeExplicitSectagMsb in AQ_MssEgressControlRegister_EUR */
#define AQ_MssEgressControlRegister_EUR_mssEgressEthertypeExplicitSectagMsb 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressEthertypeExplicitSectagMsb in AQ_MssEgressControlRegister_EUR */
#define bits_AQ_MssEgressControlRegister_EUR_mssEgressEthertypeExplicitSectagMsb u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressEthertypeExplicitSectagMsb in AQ_MssEgressControlRegister_EUR */
#define word_AQ_MssEgressControlRegister_EUR_mssEgressEthertypeExplicitSectagMsb u1.word_1

/*! \brief Base register address of structure AQ_MssEgressVlanTpid_0Register_EUR */
#define AQ_MssEgressVlanTpid_0Register_EUR_baseRegisterAddress 0x5008
/*! \brief MMD address of structure AQ_MssEgressVlanTpid_0Register_EUR */
#define AQ_MssEgressVlanTpid_0Register_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressVlanStagTpid in AQ_MssEgressVlanTpid_0Register_EUR */
#define AQ_MssEgressVlanTpid_0Register_EUR_mssEgressVlanStagTpid 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressVlanStagTpid in AQ_MssEgressVlanTpid_0Register_EUR */
#define bits_AQ_MssEgressVlanTpid_0Register_EUR_mssEgressVlanStagTpid u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressVlanStagTpid in AQ_MssEgressVlanTpid_0Register_EUR */
#define word_AQ_MssEgressVlanTpid_0Register_EUR_mssEgressVlanStagTpid u0.word_0

/*! \brief Base register address of structure AQ_MssEgressVlanTpid_1Register_EUR */
#define AQ_MssEgressVlanTpid_1Register_EUR_baseRegisterAddress 0x500A
/*! \brief MMD address of structure AQ_MssEgressVlanTpid_1Register_EUR */
#define AQ_MssEgressVlanTpid_1Register_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressVlanQtagTpid in AQ_MssEgressVlanTpid_1Register_EUR */
#define AQ_MssEgressVlanTpid_1Register_EUR_mssEgressVlanQtagTpid 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressVlanQtagTpid in AQ_MssEgressVlanTpid_1Register_EUR */
#define bits_AQ_MssEgressVlanTpid_1Register_EUR_mssEgressVlanQtagTpid u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressVlanQtagTpid in AQ_MssEgressVlanTpid_1Register_EUR */
#define word_AQ_MssEgressVlanTpid_1Register_EUR_mssEgressVlanQtagTpid u0.word_0

/*! \brief Base register address of structure AQ_MssEgressVlanControlRegister_EUR */
#define AQ_MssEgressVlanControlRegister_EUR_baseRegisterAddress 0x500C
/*! \brief MMD address of structure AQ_MssEgressVlanControlRegister_EUR */
#define AQ_MssEgressVlanControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressVlanUpMapTable in AQ_MssEgressVlanControlRegister_EUR */
#define AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanUpMapTable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressVlanUpMapTable in AQ_MssEgressVlanControlRegister_EUR */
#define bits_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanUpMapTable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressVlanUpMapTable in AQ_MssEgressVlanControlRegister_EUR */
#define word_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanUpMapTable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressVlanQtagParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanQtagParseEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressVlanQtagParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define bits_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanQtagParseEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressVlanQtagParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define word_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanQtagParseEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressVlanStagParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanStagParseEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressVlanStagParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define bits_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanStagParseEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressVlanStagParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define word_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanStagParseEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressVlanQinqParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanQinqParseEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressVlanQinqParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define bits_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanQinqParseEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressVlanQinqParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define word_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanQinqParseEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressVlanQtagUpParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanQtagUpParseEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressVlanQtagUpParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define bits_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanQtagUpParseEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressVlanQtagUpParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define word_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanQtagUpParseEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressVlanStagUpParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanStagUpParseEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressVlanStagUpParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define bits_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanStagUpParseEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressVlanStagUpParseEnable in AQ_MssEgressVlanControlRegister_EUR */
#define word_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanStagUpParseEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressVlanUpDefault in AQ_MssEgressVlanControlRegister_EUR */
#define AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanUpDefault 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressVlanUpDefault in AQ_MssEgressVlanControlRegister_EUR */
#define bits_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanUpDefault u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressVlanUpDefault in AQ_MssEgressVlanControlRegister_EUR */
#define word_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanUpDefault u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressVlanUpMapTableMSW in AQ_MssEgressVlanControlRegister_EUR */
#define AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanUpMapTableMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressVlanUpMapTableMSW in AQ_MssEgressVlanControlRegister_EUR */
#define bits_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanUpMapTableMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressVlanUpMapTableMSW in AQ_MssEgressVlanControlRegister_EUR */
#define word_AQ_MssEgressVlanControlRegister_EUR_mssEgressVlanUpMapTableMSW u1.word_1

/*! \brief Base register address of structure AQ_MssEgressPnControlRegister_EUR */
#define AQ_MssEgressPnControlRegister_EUR_baseRegisterAddress 0x500E
/*! \brief MMD address of structure AQ_MssEgressPnControlRegister_EUR */
#define AQ_MssEgressPnControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressSaPnThresholdLSW in AQ_MssEgressPnControlRegister_EUR */
#define AQ_MssEgressPnControlRegister_EUR_mssEgressSaPnThresholdLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressSaPnThresholdLSW in AQ_MssEgressPnControlRegister_EUR */
#define bits_AQ_MssEgressPnControlRegister_EUR_mssEgressSaPnThresholdLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressSaPnThresholdLSW in AQ_MssEgressPnControlRegister_EUR */
#define word_AQ_MssEgressPnControlRegister_EUR_mssEgressSaPnThresholdLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressSaPnThresholdMSW in AQ_MssEgressPnControlRegister_EUR */
#define AQ_MssEgressPnControlRegister_EUR_mssEgressSaPnThresholdMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressSaPnThresholdMSW in AQ_MssEgressPnControlRegister_EUR */
#define bits_AQ_MssEgressPnControlRegister_EUR_mssEgressSaPnThresholdMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressSaPnThresholdMSW in AQ_MssEgressPnControlRegister_EUR */
#define word_AQ_MssEgressPnControlRegister_EUR_mssEgressSaPnThresholdMSW u1.word_1

/*! \brief Base register address of structure AQ_MssEgressMtuSizeControlRegister_EUR */
#define AQ_MssEgressMtuSizeControlRegister_EUR_baseRegisterAddress 0x5010
/*! \brief MMD address of structure AQ_MssEgressMtuSizeControlRegister_EUR */
#define AQ_MssEgressMtuSizeControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressControlledPacketMtuSize in AQ_MssEgressMtuSizeControlRegister_EUR */
#define AQ_MssEgressMtuSizeControlRegister_EUR_mssEgressControlledPacketMtuSize 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressControlledPacketMtuSize in AQ_MssEgressMtuSizeControlRegister_EUR */
#define bits_AQ_MssEgressMtuSizeControlRegister_EUR_mssEgressControlledPacketMtuSize u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressControlledPacketMtuSize in AQ_MssEgressMtuSizeControlRegister_EUR */
#define word_AQ_MssEgressMtuSizeControlRegister_EUR_mssEgressControlledPacketMtuSize u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressUncontrolledPacketMtuSize in AQ_MssEgressMtuSizeControlRegister_EUR */
#define AQ_MssEgressMtuSizeControlRegister_EUR_mssEgressUncontrolledPacketMtuSize 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressUncontrolledPacketMtuSize in AQ_MssEgressMtuSizeControlRegister_EUR */
#define bits_AQ_MssEgressMtuSizeControlRegister_EUR_mssEgressUncontrolledPacketMtuSize u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressUncontrolledPacketMtuSize in AQ_MssEgressMtuSizeControlRegister_EUR */
#define word_AQ_MssEgressMtuSizeControlRegister_EUR_mssEgressUncontrolledPacketMtuSize u1.word_1

/*! \brief Base register address of structure AQ_MssEgressInterruptStatusRegister_EUR */
#define AQ_MssEgressInterruptStatusRegister_EUR_baseRegisterAddress 0x505C
/*! \brief MMD address of structure AQ_MssEgressInterruptStatusRegister_EUR */
#define AQ_MssEgressInterruptStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressEccErrorInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define AQ_MssEgressInterruptStatusRegister_EUR_mssEgressEccErrorInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressEccErrorInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define bits_AQ_MssEgressInterruptStatusRegister_EUR_mssEgressEccErrorInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressEccErrorInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define word_AQ_MssEgressInterruptStatusRegister_EUR_mssEgressEccErrorInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressMibSaturationInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define AQ_MssEgressInterruptStatusRegister_EUR_mssEgressMibSaturationInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressMibSaturationInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define bits_AQ_MssEgressInterruptStatusRegister_EUR_mssEgressMibSaturationInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressMibSaturationInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define word_AQ_MssEgressInterruptStatusRegister_EUR_mssEgressMibSaturationInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressSaThresholdExpiredInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define AQ_MssEgressInterruptStatusRegister_EUR_mssEgressSaThresholdExpiredInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressSaThresholdExpiredInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define bits_AQ_MssEgressInterruptStatusRegister_EUR_mssEgressSaThresholdExpiredInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressSaThresholdExpiredInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define word_AQ_MssEgressInterruptStatusRegister_EUR_mssEgressSaThresholdExpiredInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressSaExpiredInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define AQ_MssEgressInterruptStatusRegister_EUR_mssEgressSaExpiredInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressSaExpiredInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define bits_AQ_MssEgressInterruptStatusRegister_EUR_mssEgressSaExpiredInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressSaExpiredInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define word_AQ_MssEgressInterruptStatusRegister_EUR_mssEgressSaExpiredInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressMasterInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define AQ_MssEgressInterruptStatusRegister_EUR_mssEgressMasterInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressMasterInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define bits_AQ_MssEgressInterruptStatusRegister_EUR_mssEgressMasterInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressMasterInterrupt in AQ_MssEgressInterruptStatusRegister_EUR */
#define word_AQ_MssEgressInterruptStatusRegister_EUR_mssEgressMasterInterrupt u0.word_0

/*! \brief Base register address of structure AQ_MssEgressInterruptMaskRegister_EUR */
#define AQ_MssEgressInterruptMaskRegister_EUR_baseRegisterAddress 0x505E
/*! \brief MMD address of structure AQ_MssEgressInterruptMaskRegister_EUR */
#define AQ_MssEgressInterruptMaskRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressEccErrorInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define AQ_MssEgressInterruptMaskRegister_EUR_mssEgressEccErrorInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressEccErrorInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define bits_AQ_MssEgressInterruptMaskRegister_EUR_mssEgressEccErrorInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressEccErrorInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define word_AQ_MssEgressInterruptMaskRegister_EUR_mssEgressEccErrorInterruptEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressMibSaturationInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define AQ_MssEgressInterruptMaskRegister_EUR_mssEgressMibSaturationInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressMibSaturationInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define bits_AQ_MssEgressInterruptMaskRegister_EUR_mssEgressMibSaturationInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressMibSaturationInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define word_AQ_MssEgressInterruptMaskRegister_EUR_mssEgressMibSaturationInterruptEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressSaExpiredThresholdInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define AQ_MssEgressInterruptMaskRegister_EUR_mssEgressSaExpiredThresholdInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressSaExpiredThresholdInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define bits_AQ_MssEgressInterruptMaskRegister_EUR_mssEgressSaExpiredThresholdInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressSaExpiredThresholdInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define word_AQ_MssEgressInterruptMaskRegister_EUR_mssEgressSaExpiredThresholdInterruptEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressSaExpiredInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define AQ_MssEgressInterruptMaskRegister_EUR_mssEgressSaExpiredInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressSaExpiredInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define bits_AQ_MssEgressInterruptMaskRegister_EUR_mssEgressSaExpiredInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressSaExpiredInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define word_AQ_MssEgressInterruptMaskRegister_EUR_mssEgressSaExpiredInterruptEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressMasterInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define AQ_MssEgressInterruptMaskRegister_EUR_mssEgressMasterInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressMasterInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define bits_AQ_MssEgressInterruptMaskRegister_EUR_mssEgressMasterInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressMasterInterruptEnable in AQ_MssEgressInterruptMaskRegister_EUR */
#define word_AQ_MssEgressInterruptMaskRegister_EUR_mssEgressMasterInterruptEnable u0.word_0

/*! \brief Base register address of structure AQ_MssEgressSaExpiredStatusRegister_EUR */
#define AQ_MssEgressSaExpiredStatusRegister_EUR_baseRegisterAddress 0x5060
/*! \brief MMD address of structure AQ_MssEgressSaExpiredStatusRegister_EUR */
#define AQ_MssEgressSaExpiredStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressSaExpiredLSW in AQ_MssEgressSaExpiredStatusRegister_EUR */
#define AQ_MssEgressSaExpiredStatusRegister_EUR_mssEgressSaExpiredLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressSaExpiredLSW in AQ_MssEgressSaExpiredStatusRegister_EUR */
#define bits_AQ_MssEgressSaExpiredStatusRegister_EUR_mssEgressSaExpiredLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressSaExpiredLSW in AQ_MssEgressSaExpiredStatusRegister_EUR */
#define word_AQ_MssEgressSaExpiredStatusRegister_EUR_mssEgressSaExpiredLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressSaExpiredMSW in AQ_MssEgressSaExpiredStatusRegister_EUR */
#define AQ_MssEgressSaExpiredStatusRegister_EUR_mssEgressSaExpiredMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressSaExpiredMSW in AQ_MssEgressSaExpiredStatusRegister_EUR */
#define bits_AQ_MssEgressSaExpiredStatusRegister_EUR_mssEgressSaExpiredMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressSaExpiredMSW in AQ_MssEgressSaExpiredStatusRegister_EUR */
#define word_AQ_MssEgressSaExpiredStatusRegister_EUR_mssEgressSaExpiredMSW u1.word_1

/*! \brief Base register address of structure AQ_MssEgressSaThresholdExpiredStatusRegister_EUR */
#define AQ_MssEgressSaThresholdExpiredStatusRegister_EUR_baseRegisterAddress 0x5062
/*! \brief MMD address of structure AQ_MssEgressSaThresholdExpiredStatusRegister_EUR */
#define AQ_MssEgressSaThresholdExpiredStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressSaThresholdExpiredLSW in AQ_MssEgressSaThresholdExpiredStatusRegister_EUR */
#define AQ_MssEgressSaThresholdExpiredStatusRegister_EUR_mssEgressSaThresholdExpiredLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressSaThresholdExpiredLSW in AQ_MssEgressSaThresholdExpiredStatusRegister_EUR */
#define bits_AQ_MssEgressSaThresholdExpiredStatusRegister_EUR_mssEgressSaThresholdExpiredLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressSaThresholdExpiredLSW in AQ_MssEgressSaThresholdExpiredStatusRegister_EUR */
#define word_AQ_MssEgressSaThresholdExpiredStatusRegister_EUR_mssEgressSaThresholdExpiredLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressSaThresholdExpiredMSW in AQ_MssEgressSaThresholdExpiredStatusRegister_EUR */
#define AQ_MssEgressSaThresholdExpiredStatusRegister_EUR_mssEgressSaThresholdExpiredMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressSaThresholdExpiredMSW in AQ_MssEgressSaThresholdExpiredStatusRegister_EUR */
#define bits_AQ_MssEgressSaThresholdExpiredStatusRegister_EUR_mssEgressSaThresholdExpiredMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressSaThresholdExpiredMSW in AQ_MssEgressSaThresholdExpiredStatusRegister_EUR */
#define word_AQ_MssEgressSaThresholdExpiredStatusRegister_EUR_mssEgressSaThresholdExpiredMSW u1.word_1

/*! \brief Base register address of structure AQ_MssEgressEccInterruptStatusRegister_EUR */
#define AQ_MssEgressEccInterruptStatusRegister_EUR_baseRegisterAddress 0x5064
/*! \brief MMD address of structure AQ_MssEgressEccInterruptStatusRegister_EUR */
#define AQ_MssEgressEccInterruptStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressSaEccErrorInterruptLSW in AQ_MssEgressEccInterruptStatusRegister_EUR */
#define AQ_MssEgressEccInterruptStatusRegister_EUR_mssEgressSaEccErrorInterruptLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressSaEccErrorInterruptLSW in AQ_MssEgressEccInterruptStatusRegister_EUR */
#define bits_AQ_MssEgressEccInterruptStatusRegister_EUR_mssEgressSaEccErrorInterruptLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressSaEccErrorInterruptLSW in AQ_MssEgressEccInterruptStatusRegister_EUR */
#define word_AQ_MssEgressEccInterruptStatusRegister_EUR_mssEgressSaEccErrorInterruptLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressSaEccErrorInterruptMSW in AQ_MssEgressEccInterruptStatusRegister_EUR */
#define AQ_MssEgressEccInterruptStatusRegister_EUR_mssEgressSaEccErrorInterruptMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressSaEccErrorInterruptMSW in AQ_MssEgressEccInterruptStatusRegister_EUR */
#define bits_AQ_MssEgressEccInterruptStatusRegister_EUR_mssEgressSaEccErrorInterruptMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressSaEccErrorInterruptMSW in AQ_MssEgressEccInterruptStatusRegister_EUR */
#define word_AQ_MssEgressEccInterruptStatusRegister_EUR_mssEgressSaEccErrorInterruptMSW u1.word_1

/*! \brief Base register address of structure AQ_MssEgressLutAddressControlRegister_EUR */
#define AQ_MssEgressLutAddressControlRegister_EUR_baseRegisterAddress 0x5080
/*! \brief MMD address of structure AQ_MssEgressLutAddressControlRegister_EUR */
#define AQ_MssEgressLutAddressControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutSelect in AQ_MssEgressLutAddressControlRegister_EUR */
#define AQ_MssEgressLutAddressControlRegister_EUR_mssEgressLutSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutSelect in AQ_MssEgressLutAddressControlRegister_EUR */
#define bits_AQ_MssEgressLutAddressControlRegister_EUR_mssEgressLutSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutSelect in AQ_MssEgressLutAddressControlRegister_EUR */
#define word_AQ_MssEgressLutAddressControlRegister_EUR_mssEgressLutSelect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutAddress in AQ_MssEgressLutAddressControlRegister_EUR */
#define AQ_MssEgressLutAddressControlRegister_EUR_mssEgressLutAddress 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutAddress in AQ_MssEgressLutAddressControlRegister_EUR */
#define bits_AQ_MssEgressLutAddressControlRegister_EUR_mssEgressLutAddress u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutAddress in AQ_MssEgressLutAddressControlRegister_EUR */
#define word_AQ_MssEgressLutAddressControlRegister_EUR_mssEgressLutAddress u0.word_0

/*! \brief Base register address of structure AQ_MssEgressLutControlRegister_EUR */
#define AQ_MssEgressLutControlRegister_EUR_baseRegisterAddress 0x5081
/*! \brief MMD address of structure AQ_MssEgressLutControlRegister_EUR */
#define AQ_MssEgressLutControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutWrite in AQ_MssEgressLutControlRegister_EUR */
#define AQ_MssEgressLutControlRegister_EUR_mssEgressLutWrite 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutWrite in AQ_MssEgressLutControlRegister_EUR */
#define bits_AQ_MssEgressLutControlRegister_EUR_mssEgressLutWrite u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutWrite in AQ_MssEgressLutControlRegister_EUR */
#define word_AQ_MssEgressLutControlRegister_EUR_mssEgressLutWrite u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutRead in AQ_MssEgressLutControlRegister_EUR */
#define AQ_MssEgressLutControlRegister_EUR_mssEgressLutRead 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutRead in AQ_MssEgressLutControlRegister_EUR */
#define bits_AQ_MssEgressLutControlRegister_EUR_mssEgressLutRead u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutRead in AQ_MssEgressLutControlRegister_EUR */
#define word_AQ_MssEgressLutControlRegister_EUR_mssEgressLutRead u0.word_0

/*! \brief Base register address of structure AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_baseRegisterAddress 0x50A0
/*! \brief MMD address of structure AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_0 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_0 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_0 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_1 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_1 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_1 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_2 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_2 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_2 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_2 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_3 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_3 3
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_3 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_3 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_3 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_3 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_4 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_4 4
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_4 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_4 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_4 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_4 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_5 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_5 5
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_5 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_5 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_5 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_5 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_6 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_6 6
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_6 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_6 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_6 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_6 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_7 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_7 7
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_7 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_7 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_7 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_7 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_8 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_8 8
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_8 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_8 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_8 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_8 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_9 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_9 9
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_9 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_9 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_9 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_9 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_10 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_10 10
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_10 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_10 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_10 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_10 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_11 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_11 11
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_11 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_11 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_11 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_11 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_12 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_12 12
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_12 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_12 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_12 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_12 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_13 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_13 13
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_13 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_13 u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_13 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_13 u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_14 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_14 14
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_14 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_14 u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_14 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_14 u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_15 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_15 15
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_15 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_15 u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_15 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_15 u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_16 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_16 16
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_16 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_16 u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_16 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_16 u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_17 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_17 17
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_17 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_17 u17.bits_17
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_17 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_17 u17.word_17
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_18 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_18 18
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_18 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_18 u18.bits_18
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_18 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_18 u18.word_18
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_19 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_19 19
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_19 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_19 u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_19 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_19 u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_20 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_20 20
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_20 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_20 u20.bits_20
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_20 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_20 u20.word_20
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_21 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_21 21
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_21 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_21 u21.bits_21
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_21 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_21 u21.word_21
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_22 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_22 22
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_22 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_22 u22.bits_22
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_22 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_22 u22.word_22
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_23 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_23 23
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_23 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_23 u23.bits_23
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_23 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_23 u23.word_23
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_24 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_24 24
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_24 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_24 u24.bits_24
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_24 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_24 u24.word_24
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_25 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_25 25
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_25 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_25 u25.bits_25
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_25 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_25 u25.word_25
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_26 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_26 26
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_26 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_26 u26.bits_26
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_26 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_26 u26.word_26
/*! \brief Preprocessor variable to relate field to word number in structure mssEgressLutData_27 in AQ_MssEgressLutDataControlRegister_EUR */
#define AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_27 27
/*! \brief Preprocessor variable to relate field to bit position in structure mssEgressLutData_27 in AQ_MssEgressLutDataControlRegister_EUR */
#define bits_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_27 u27.bits_27
/*! \brief Preprocessor variable to relate field to word position in structure mssEgressLutData_27 in AQ_MssEgressLutDataControlRegister_EUR */
#define word_AQ_MssEgressLutDataControlRegister_EUR_mssEgressLutData_27 u27.word_27

/*! \brief Base register address of structure AQ_MsmSystemRevisionRegister_EUR */
#define AQ_MsmSystemRevisionRegister_EUR_baseRegisterAddress 0x6000
/*! \brief MMD address of structure AQ_MsmSystemRevisionRegister_EUR */
#define AQ_MsmSystemRevisionRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemCoreRevision in AQ_MsmSystemRevisionRegister_EUR */
#define AQ_MsmSystemRevisionRegister_EUR_msmSystemCoreRevision 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemCoreRevision in AQ_MsmSystemRevisionRegister_EUR */
#define bits_AQ_MsmSystemRevisionRegister_EUR_msmSystemCoreRevision u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemCoreRevision in AQ_MsmSystemRevisionRegister_EUR */
#define word_AQ_MsmSystemRevisionRegister_EUR_msmSystemCoreRevision u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemCoreVersion in AQ_MsmSystemRevisionRegister_EUR */
#define AQ_MsmSystemRevisionRegister_EUR_msmSystemCoreVersion 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemCoreVersion in AQ_MsmSystemRevisionRegister_EUR */
#define bits_AQ_MsmSystemRevisionRegister_EUR_msmSystemCoreVersion u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemCoreVersion in AQ_MsmSystemRevisionRegister_EUR */
#define word_AQ_MsmSystemRevisionRegister_EUR_msmSystemCoreVersion u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemCustomerRevision in AQ_MsmSystemRevisionRegister_EUR */
#define AQ_MsmSystemRevisionRegister_EUR_msmSystemCustomerRevision 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemCustomerRevision in AQ_MsmSystemRevisionRegister_EUR */
#define bits_AQ_MsmSystemRevisionRegister_EUR_msmSystemCustomerRevision u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemCustomerRevision in AQ_MsmSystemRevisionRegister_EUR */
#define word_AQ_MsmSystemRevisionRegister_EUR_msmSystemCustomerRevision u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemScratchpadRegister_EUR */
#define AQ_MsmSystemScratchpadRegister_EUR_baseRegisterAddress 0x6002
/*! \brief MMD address of structure AQ_MsmSystemScratchpadRegister_EUR */
#define AQ_MsmSystemScratchpadRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemScratch_0 in AQ_MsmSystemScratchpadRegister_EUR */
#define AQ_MsmSystemScratchpadRegister_EUR_msmSystemScratch_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemScratch_0 in AQ_MsmSystemScratchpadRegister_EUR */
#define bits_AQ_MsmSystemScratchpadRegister_EUR_msmSystemScratch_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemScratch_0 in AQ_MsmSystemScratchpadRegister_EUR */
#define word_AQ_MsmSystemScratchpadRegister_EUR_msmSystemScratch_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemScratch_1 in AQ_MsmSystemScratchpadRegister_EUR */
#define AQ_MsmSystemScratchpadRegister_EUR_msmSystemScratch_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemScratch_1 in AQ_MsmSystemScratchpadRegister_EUR */
#define bits_AQ_MsmSystemScratchpadRegister_EUR_msmSystemScratch_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemScratch_1 in AQ_MsmSystemScratchpadRegister_EUR */
#define word_AQ_MsmSystemScratchpadRegister_EUR_msmSystemScratch_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_baseRegisterAddress 0x6004
/*! \brief MMD address of structure AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemPhyTxEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPhyTxEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemPhyTxEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPhyTxEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemPhyTxEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPhyTxEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxErrorDiscard in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemRxErrorDiscard 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxErrorDiscard in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemRxErrorDiscard u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxErrorDiscard in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemRxErrorDiscard u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemControlFrameEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemControlFrameEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemControlFrameEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemControlFrameEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemControlFrameEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemControlFrameEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSoftReset in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemSoftReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSoftReset in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemSoftReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSoftReset in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemSoftReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxPadEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxPadEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxPadEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxPadEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxPadEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxPadEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxCrcAppend in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxCrcAppend 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxCrcAppend in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxCrcAppend u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxCrcAppend in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxCrcAppend u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxAddressInsertEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxAddressInsertEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxAddressInsertEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxAddressInsertEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxAddressInsertEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxAddressInsertEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemPauseIgnore in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPauseIgnore 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemPauseIgnore in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPauseIgnore u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemPauseIgnore in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPauseIgnore u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemPauseForward in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPauseForward 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemPauseForward in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPauseForward u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemPauseForward in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPauseForward u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemCrcForward in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemCrcForward 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemCrcForward in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemCrcForward u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemCrcForward in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemCrcForward u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemPadEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPadEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemPadEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPadEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemPadEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPadEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemPromiscuousMode in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPromiscuousMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemPromiscuousMode in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPromiscuousMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemPromiscuousMode in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPromiscuousMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemWanMode in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemWanMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemWanMode in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemWanMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemWanMode in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemWanMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemRxEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemRxEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemRxEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemStatisticCounterReset in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemStatisticCounterReset 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemStatisticCounterReset in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemStatisticCounterReset u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemStatisticCounterReset in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemStatisticCounterReset u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemCrcCorruptionDisable in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemCrcCorruptionDisable 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemCrcCorruptionDisable in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemCrcCorruptionDisable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemCrcCorruptionDisable in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemCrcCorruptionDisable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxLowPowerIdleEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxLowPowerIdleEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxLowPowerIdleEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxLowPowerIdleEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxLowPowerIdleEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemTxLowPowerIdleEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSfdCheckDisable in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemSfdCheckDisable 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSfdCheckDisable in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemSfdCheckDisable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSfdCheckDisable in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemSfdCheckDisable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemPriorityFlowControlEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPriorityFlowControlEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemPriorityFlowControlEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPriorityFlowControlEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemPriorityFlowControlEnable in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemPriorityFlowControlEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemIdleColumnCountExtend in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemIdleColumnCountExtend 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemIdleColumnCountExtend in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemIdleColumnCountExtend u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemIdleColumnCountExtend in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemIdleColumnCountExtend u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemLengthCheckDisable in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemLengthCheckDisable 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemLengthCheckDisable in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemLengthCheckDisable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemLengthCheckDisable in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemLengthCheckDisable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemForceSendIdle in AQ_MsmSystemGeneralControlRegister_EUR */
#define AQ_MsmSystemGeneralControlRegister_EUR_msmSystemForceSendIdle 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemForceSendIdle in AQ_MsmSystemGeneralControlRegister_EUR */
#define bits_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemForceSendIdle u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemForceSendIdle in AQ_MsmSystemGeneralControlRegister_EUR */
#define word_AQ_MsmSystemGeneralControlRegister_EUR_msmSystemForceSendIdle u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemAddressRegister_EUR */
#define AQ_MsmSystemAddressRegister_EUR_baseRegisterAddress 0x6006
/*! \brief MMD address of structure AQ_MsmSystemAddressRegister_EUR */
#define AQ_MsmSystemAddressRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemAddress_0 in AQ_MsmSystemAddressRegister_EUR */
#define AQ_MsmSystemAddressRegister_EUR_msmSystemAddress_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemAddress_0 in AQ_MsmSystemAddressRegister_EUR */
#define bits_AQ_MsmSystemAddressRegister_EUR_msmSystemAddress_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemAddress_0 in AQ_MsmSystemAddressRegister_EUR */
#define word_AQ_MsmSystemAddressRegister_EUR_msmSystemAddress_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemAddress_1 in AQ_MsmSystemAddressRegister_EUR */
#define AQ_MsmSystemAddressRegister_EUR_msmSystemAddress_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemAddress_1 in AQ_MsmSystemAddressRegister_EUR */
#define bits_AQ_MsmSystemAddressRegister_EUR_msmSystemAddress_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemAddress_1 in AQ_MsmSystemAddressRegister_EUR */
#define word_AQ_MsmSystemAddressRegister_EUR_msmSystemAddress_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemAddress_2 in AQ_MsmSystemAddressRegister_EUR */
#define AQ_MsmSystemAddressRegister_EUR_msmSystemAddress_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemAddress_2 in AQ_MsmSystemAddressRegister_EUR */
#define bits_AQ_MsmSystemAddressRegister_EUR_msmSystemAddress_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemAddress_2 in AQ_MsmSystemAddressRegister_EUR */
#define word_AQ_MsmSystemAddressRegister_EUR_msmSystemAddress_2 u2.word_2

/*! \brief Base register address of structure AQ_MsmSystemFrameControlRegister_EUR */
#define AQ_MsmSystemFrameControlRegister_EUR_baseRegisterAddress 0x600A
/*! \brief MMD address of structure AQ_MsmSystemFrameControlRegister_EUR */
#define AQ_MsmSystemFrameControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMaximumFrameLength in AQ_MsmSystemFrameControlRegister_EUR */
#define AQ_MsmSystemFrameControlRegister_EUR_msmSystemMaximumFrameLength 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMaximumFrameLength in AQ_MsmSystemFrameControlRegister_EUR */
#define bits_AQ_MsmSystemFrameControlRegister_EUR_msmSystemMaximumFrameLength u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMaximumFrameLength in AQ_MsmSystemFrameControlRegister_EUR */
#define word_AQ_MsmSystemFrameControlRegister_EUR_msmSystemMaximumFrameLength u0.word_0

/*! \brief Base register address of structure AQ_MsmSystemFifoControlRegister_EUR */
#define AQ_MsmSystemFifoControlRegister_EUR_baseRegisterAddress 0x600E
/*! \brief MMD address of structure AQ_MsmSystemFifoControlRegister_EUR */
#define AQ_MsmSystemFifoControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxFifoFullThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define AQ_MsmSystemFifoControlRegister_EUR_msmSystemRxFifoFullThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxFifoFullThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define bits_AQ_MsmSystemFifoControlRegister_EUR_msmSystemRxFifoFullThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxFifoFullThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define word_AQ_MsmSystemFifoControlRegister_EUR_msmSystemRxFifoFullThreshold u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxFifoEmptyThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define AQ_MsmSystemFifoControlRegister_EUR_msmSystemRxFifoEmptyThreshold 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxFifoEmptyThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define bits_AQ_MsmSystemFifoControlRegister_EUR_msmSystemRxFifoEmptyThreshold u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxFifoEmptyThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define word_AQ_MsmSystemFifoControlRegister_EUR_msmSystemRxFifoEmptyThreshold u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxFifoFullThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define AQ_MsmSystemFifoControlRegister_EUR_msmSystemTxFifoFullThreshold 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxFifoFullThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define bits_AQ_MsmSystemFifoControlRegister_EUR_msmSystemTxFifoFullThreshold u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxFifoFullThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define word_AQ_MsmSystemFifoControlRegister_EUR_msmSystemTxFifoFullThreshold u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxFifoEmptyThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define AQ_MsmSystemFifoControlRegister_EUR_msmSystemTxFifoEmptyThreshold 3
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxFifoEmptyThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define bits_AQ_MsmSystemFifoControlRegister_EUR_msmSystemTxFifoEmptyThreshold u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxFifoEmptyThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define word_AQ_MsmSystemFifoControlRegister_EUR_msmSystemTxFifoEmptyThreshold u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxFifoAlmostFullThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define AQ_MsmSystemFifoControlRegister_EUR_msmSystemRxFifoAlmostFullThreshold 4
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxFifoAlmostFullThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define bits_AQ_MsmSystemFifoControlRegister_EUR_msmSystemRxFifoAlmostFullThreshold u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxFifoAlmostFullThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define word_AQ_MsmSystemFifoControlRegister_EUR_msmSystemRxFifoAlmostFullThreshold u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxFifoAlmostEmptyThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define AQ_MsmSystemFifoControlRegister_EUR_msmSystemRxFifoAlmostEmptyThreshold 5
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxFifoAlmostEmptyThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define bits_AQ_MsmSystemFifoControlRegister_EUR_msmSystemRxFifoAlmostEmptyThreshold u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxFifoAlmostEmptyThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define word_AQ_MsmSystemFifoControlRegister_EUR_msmSystemRxFifoAlmostEmptyThreshold u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxFifoAlmostFullThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define AQ_MsmSystemFifoControlRegister_EUR_msmSystemTxFifoAlmostFullThreshold 6
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxFifoAlmostFullThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define bits_AQ_MsmSystemFifoControlRegister_EUR_msmSystemTxFifoAlmostFullThreshold u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxFifoAlmostFullThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define word_AQ_MsmSystemFifoControlRegister_EUR_msmSystemTxFifoAlmostFullThreshold u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxFifoAlmostEmptyThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define AQ_MsmSystemFifoControlRegister_EUR_msmSystemTxFifoAlmostEmptyThreshold 7
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxFifoAlmostEmptyThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define bits_AQ_MsmSystemFifoControlRegister_EUR_msmSystemTxFifoAlmostEmptyThreshold u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxFifoAlmostEmptyThreshold in AQ_MsmSystemFifoControlRegister_EUR */
#define word_AQ_MsmSystemFifoControlRegister_EUR_msmSystemTxFifoAlmostEmptyThreshold u7.word_7

/*! \brief Base register address of structure AQ_MsmSystemHashControlRegister_EUR */
#define AQ_MsmSystemHashControlRegister_EUR_baseRegisterAddress 0x6016
/*! \brief MMD address of structure AQ_MsmSystemHashControlRegister_EUR */
#define AQ_MsmSystemHashControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMulticastEnable in AQ_MsmSystemHashControlRegister_EUR */
#define AQ_MsmSystemHashControlRegister_EUR_msmSystemMulticastEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMulticastEnable in AQ_MsmSystemHashControlRegister_EUR */
#define bits_AQ_MsmSystemHashControlRegister_EUR_msmSystemMulticastEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMulticastEnable in AQ_MsmSystemHashControlRegister_EUR */
#define word_AQ_MsmSystemHashControlRegister_EUR_msmSystemMulticastEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemHashTable in AQ_MsmSystemHashControlRegister_EUR */
#define AQ_MsmSystemHashControlRegister_EUR_msmSystemHashTable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemHashTable in AQ_MsmSystemHashControlRegister_EUR */
#define bits_AQ_MsmSystemHashControlRegister_EUR_msmSystemHashTable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemHashTable in AQ_MsmSystemHashControlRegister_EUR */
#define word_AQ_MsmSystemHashControlRegister_EUR_msmSystemHashTable u0.word_0

/*! \brief Base register address of structure AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_baseRegisterAddress 0x6018
/*! \brief MMD address of structure AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMdioClockDividerConfiguration in AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioClockDividerConfiguration 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMdioClockDividerConfiguration in AQ_MsmSystemMdioControlRegister_EUR */
#define bits_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioClockDividerConfiguration u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMdioClockDividerConfiguration in AQ_MsmSystemMdioControlRegister_EUR */
#define word_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioClockDividerConfiguration u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMdioClause_45Enable in AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioClause_45Enable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMdioClause_45Enable in AQ_MsmSystemMdioControlRegister_EUR */
#define bits_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioClause_45Enable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMdioClause_45Enable in AQ_MsmSystemMdioControlRegister_EUR */
#define word_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioClause_45Enable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMdioHoldTimeConfiguration in AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioHoldTimeConfiguration 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMdioHoldTimeConfiguration in AQ_MsmSystemMdioControlRegister_EUR */
#define bits_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioHoldTimeConfiguration u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMdioHoldTimeConfiguration in AQ_MsmSystemMdioControlRegister_EUR */
#define word_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioHoldTimeConfiguration u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMdioReadError in AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioReadError 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMdioReadError in AQ_MsmSystemMdioControlRegister_EUR */
#define bits_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioReadError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMdioReadError in AQ_MsmSystemMdioControlRegister_EUR */
#define word_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioReadError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMdioBusy_0 in AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioBusy_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMdioBusy_0 in AQ_MsmSystemMdioControlRegister_EUR */
#define bits_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioBusy_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMdioBusy_0 in AQ_MsmSystemMdioControlRegister_EUR */
#define word_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioBusy_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMdioBusy_1 in AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioBusy_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMdioBusy_1 in AQ_MsmSystemMdioControlRegister_EUR */
#define bits_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioBusy_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMdioBusy_1 in AQ_MsmSystemMdioControlRegister_EUR */
#define word_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioBusy_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMdioRead in AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioRead 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMdioRead in AQ_MsmSystemMdioControlRegister_EUR */
#define bits_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioRead u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMdioRead in AQ_MsmSystemMdioControlRegister_EUR */
#define word_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioRead u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMdioReadAddressPostIncrement in AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioReadAddressPostIncrement 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMdioReadAddressPostIncrement in AQ_MsmSystemMdioControlRegister_EUR */
#define bits_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioReadAddressPostIncrement u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMdioReadAddressPostIncrement in AQ_MsmSystemMdioControlRegister_EUR */
#define word_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioReadAddressPostIncrement u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMdioPortAddress in AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioPortAddress 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMdioPortAddress in AQ_MsmSystemMdioControlRegister_EUR */
#define bits_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioPortAddress u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMdioPortAddress in AQ_MsmSystemMdioControlRegister_EUR */
#define word_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioPortAddress u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMdioDeviceAddress in AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioDeviceAddress 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMdioDeviceAddress in AQ_MsmSystemMdioControlRegister_EUR */
#define bits_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioDeviceAddress u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMdioDeviceAddress in AQ_MsmSystemMdioControlRegister_EUR */
#define word_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioDeviceAddress u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMdioData in AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioData 4
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMdioData in AQ_MsmSystemMdioControlRegister_EUR */
#define bits_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioData u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMdioData in AQ_MsmSystemMdioControlRegister_EUR */
#define word_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioData u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemMdioRegisterAddress in AQ_MsmSystemMdioControlRegister_EUR */
#define AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioRegisterAddress 6
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemMdioRegisterAddress in AQ_MsmSystemMdioControlRegister_EUR */
#define bits_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioRegisterAddress u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemMdioRegisterAddress in AQ_MsmSystemMdioControlRegister_EUR */
#define word_AQ_MsmSystemMdioControlRegister_EUR_msmSystemMdioRegisterAddress u6.word_6

/*! \brief Base register address of structure AQ_MsmSystemGeneralStatusRegister_EUR */
#define AQ_MsmSystemGeneralStatusRegister_EUR_baseRegisterAddress 0x6020
/*! \brief MMD address of structure AQ_MsmSystemGeneralStatusRegister_EUR */
#define AQ_MsmSystemGeneralStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxFifoEmpty in AQ_MsmSystemGeneralStatusRegister_EUR */
#define AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemTxFifoEmpty 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxFifoEmpty in AQ_MsmSystemGeneralStatusRegister_EUR */
#define bits_AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemTxFifoEmpty u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxFifoEmpty in AQ_MsmSystemGeneralStatusRegister_EUR */
#define word_AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemTxFifoEmpty u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxLowPowerIdle in AQ_MsmSystemGeneralStatusRegister_EUR */
#define AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemRxLowPowerIdle 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxLowPowerIdle in AQ_MsmSystemGeneralStatusRegister_EUR */
#define bits_AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemRxLowPowerIdle u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxLowPowerIdle in AQ_MsmSystemGeneralStatusRegister_EUR */
#define word_AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemRxLowPowerIdle u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTimestampAvailable in AQ_MsmSystemGeneralStatusRegister_EUR */
#define AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemTimestampAvailable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTimestampAvailable in AQ_MsmSystemGeneralStatusRegister_EUR */
#define bits_AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemTimestampAvailable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTimestampAvailable in AQ_MsmSystemGeneralStatusRegister_EUR */
#define word_AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemTimestampAvailable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemPhyLossOfSignal in AQ_MsmSystemGeneralStatusRegister_EUR */
#define AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemPhyLossOfSignal 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemPhyLossOfSignal in AQ_MsmSystemGeneralStatusRegister_EUR */
#define bits_AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemPhyLossOfSignal u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemPhyLossOfSignal in AQ_MsmSystemGeneralStatusRegister_EUR */
#define word_AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemPhyLossOfSignal u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxRemoteFault in AQ_MsmSystemGeneralStatusRegister_EUR */
#define AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemRxRemoteFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxRemoteFault in AQ_MsmSystemGeneralStatusRegister_EUR */
#define bits_AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemRxRemoteFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxRemoteFault in AQ_MsmSystemGeneralStatusRegister_EUR */
#define word_AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemRxRemoteFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxLocalFault in AQ_MsmSystemGeneralStatusRegister_EUR */
#define AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemRxLocalFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxLocalFault in AQ_MsmSystemGeneralStatusRegister_EUR */
#define bits_AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemRxLocalFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxLocalFault in AQ_MsmSystemGeneralStatusRegister_EUR */
#define word_AQ_MsmSystemGeneralStatusRegister_EUR_msmSystemRxLocalFault u0.word_0

/*! \brief Base register address of structure AQ_MsmSystemTxIpgControlRegister_EUR */
#define AQ_MsmSystemTxIpgControlRegister_EUR_baseRegisterAddress 0x6022
/*! \brief MMD address of structure AQ_MsmSystemTxIpgControlRegister_EUR */
#define AQ_MsmSystemTxIpgControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxIpgLength in AQ_MsmSystemTxIpgControlRegister_EUR */
#define AQ_MsmSystemTxIpgControlRegister_EUR_msmSystemTxIpgLength 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxIpgLength in AQ_MsmSystemTxIpgControlRegister_EUR */
#define bits_AQ_MsmSystemTxIpgControlRegister_EUR_msmSystemTxIpgLength u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxIpgLength in AQ_MsmSystemTxIpgControlRegister_EUR */
#define word_AQ_MsmSystemTxIpgControlRegister_EUR_msmSystemTxIpgLength u0.word_0

/*! \brief Base register address of structure AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_baseRegisterAddress 0x602A
/*! \brief MMD address of structure AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_0PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_0PauseQuanta 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_0PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_0PauseQuanta u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_0PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_0PauseQuanta u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_1PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_1PauseQuanta 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_1PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_1PauseQuanta u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_1PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_1PauseQuanta u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_2PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_2PauseQuanta 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_2PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_2PauseQuanta u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_2PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_2PauseQuanta u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_3PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_3PauseQuanta 3
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_3PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_3PauseQuanta u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_3PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_3PauseQuanta u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_4PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_4PauseQuanta 4
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_4PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_4PauseQuanta u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_4PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_4PauseQuanta u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_5PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_5PauseQuanta 5
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_5PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_5PauseQuanta u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_5PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_5PauseQuanta u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_6PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_6PauseQuanta 6
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_6PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_6PauseQuanta u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_6PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_6PauseQuanta u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_7PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_7PauseQuanta 7
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_7PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_7PauseQuanta u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_7PauseQuanta in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_7PauseQuanta u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_0PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_0PauseQuantaThreshold 8
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_0PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_0PauseQuantaThreshold u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_0PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_0PauseQuantaThreshold u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_1PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_1PauseQuantaThreshold 9
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_1PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_1PauseQuantaThreshold u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_1PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_1PauseQuantaThreshold u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_2PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_2PauseQuantaThreshold 10
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_2PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_2PauseQuantaThreshold u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_2PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_2PauseQuantaThreshold u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_3PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_3PauseQuantaThreshold 11
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_3PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_3PauseQuantaThreshold u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_3PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_3PauseQuantaThreshold u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_4PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_4PauseQuantaThreshold 12
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_4PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_4PauseQuantaThreshold u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_4PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_4PauseQuantaThreshold u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_5PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_5PauseQuantaThreshold 13
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_5PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_5PauseQuantaThreshold u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_5PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_5PauseQuantaThreshold u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_6PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_6PauseQuantaThreshold 14
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_6PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_6PauseQuantaThreshold u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_6PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_6PauseQuantaThreshold u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemClass_7PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_7PauseQuantaThreshold 15
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemClass_7PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define bits_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_7PauseQuantaThreshold u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemClass_7PauseQuantaThreshold in AQ_MsmSystemPauseControlRegister_EUR */
#define word_AQ_MsmSystemPauseControlRegister_EUR_msmSystemClass_7PauseQuantaThreshold u15.word_15

/*! \brief Base register address of structure AQ_MsmSystemPauseStatusRegister_EUR */
#define AQ_MsmSystemPauseStatusRegister_EUR_baseRegisterAddress 0x603A
/*! \brief MMD address of structure AQ_MsmSystemPauseStatusRegister_EUR */
#define AQ_MsmSystemPauseStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemPauseStatus in AQ_MsmSystemPauseStatusRegister_EUR */
#define AQ_MsmSystemPauseStatusRegister_EUR_msmSystemPauseStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemPauseStatus in AQ_MsmSystemPauseStatusRegister_EUR */
#define bits_AQ_MsmSystemPauseStatusRegister_EUR_msmSystemPauseStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemPauseStatus in AQ_MsmSystemPauseStatusRegister_EUR */
#define word_AQ_MsmSystemPauseStatusRegister_EUR_msmSystemPauseStatus u0.word_0

/*! \brief Base register address of structure AQ_MsmSystemTimeStampStatusRegister_EUR */
#define AQ_MsmSystemTimeStampStatusRegister_EUR_baseRegisterAddress 0x603E
/*! \brief MMD address of structure AQ_MsmSystemTimeStampStatusRegister_EUR */
#define AQ_MsmSystemTimeStampStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTimestampStatus_0 in AQ_MsmSystemTimeStampStatusRegister_EUR */
#define AQ_MsmSystemTimeStampStatusRegister_EUR_msmSystemTimestampStatus_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTimestampStatus_0 in AQ_MsmSystemTimeStampStatusRegister_EUR */
#define bits_AQ_MsmSystemTimeStampStatusRegister_EUR_msmSystemTimestampStatus_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTimestampStatus_0 in AQ_MsmSystemTimeStampStatusRegister_EUR */
#define word_AQ_MsmSystemTimeStampStatusRegister_EUR_msmSystemTimestampStatus_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTimestampStatus_1 in AQ_MsmSystemTimeStampStatusRegister_EUR */
#define AQ_MsmSystemTimeStampStatusRegister_EUR_msmSystemTimestampStatus_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTimestampStatus_1 in AQ_MsmSystemTimeStampStatusRegister_EUR */
#define bits_AQ_MsmSystemTimeStampStatusRegister_EUR_msmSystemTimestampStatus_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTimestampStatus_1 in AQ_MsmSystemTimeStampStatusRegister_EUR */
#define word_AQ_MsmSystemTimeStampStatusRegister_EUR_msmSystemTimestampStatus_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemTxGoodFramesCounterRegister_EUR */
#define AQ_MsmSystemTxGoodFramesCounterRegister_EUR_baseRegisterAddress 0x6040
/*! \brief MMD address of structure AQ_MsmSystemTxGoodFramesCounterRegister_EUR */
#define AQ_MsmSystemTxGoodFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxGoodFramesCounter_0 in AQ_MsmSystemTxGoodFramesCounterRegister_EUR */
#define AQ_MsmSystemTxGoodFramesCounterRegister_EUR_msmSystemTxGoodFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxGoodFramesCounter_0 in AQ_MsmSystemTxGoodFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemTxGoodFramesCounterRegister_EUR_msmSystemTxGoodFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxGoodFramesCounter_0 in AQ_MsmSystemTxGoodFramesCounterRegister_EUR */
#define word_AQ_MsmSystemTxGoodFramesCounterRegister_EUR_msmSystemTxGoodFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxGoodFramesCounter_1 in AQ_MsmSystemTxGoodFramesCounterRegister_EUR */
#define AQ_MsmSystemTxGoodFramesCounterRegister_EUR_msmSystemTxGoodFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxGoodFramesCounter_1 in AQ_MsmSystemTxGoodFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemTxGoodFramesCounterRegister_EUR_msmSystemTxGoodFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxGoodFramesCounter_1 in AQ_MsmSystemTxGoodFramesCounterRegister_EUR */
#define word_AQ_MsmSystemTxGoodFramesCounterRegister_EUR_msmSystemTxGoodFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemRxGoodFramesCounterRegister_EUR */
#define AQ_MsmSystemRxGoodFramesCounterRegister_EUR_baseRegisterAddress 0x6044
/*! \brief MMD address of structure AQ_MsmSystemRxGoodFramesCounterRegister_EUR */
#define AQ_MsmSystemRxGoodFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxGoodFramesCounter_0 in AQ_MsmSystemRxGoodFramesCounterRegister_EUR */
#define AQ_MsmSystemRxGoodFramesCounterRegister_EUR_msmSystemRxGoodFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxGoodFramesCounter_0 in AQ_MsmSystemRxGoodFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemRxGoodFramesCounterRegister_EUR_msmSystemRxGoodFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxGoodFramesCounter_0 in AQ_MsmSystemRxGoodFramesCounterRegister_EUR */
#define word_AQ_MsmSystemRxGoodFramesCounterRegister_EUR_msmSystemRxGoodFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxGoodFramesCounter_1 in AQ_MsmSystemRxGoodFramesCounterRegister_EUR */
#define AQ_MsmSystemRxGoodFramesCounterRegister_EUR_msmSystemRxGoodFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxGoodFramesCounter_1 in AQ_MsmSystemRxGoodFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemRxGoodFramesCounterRegister_EUR_msmSystemRxGoodFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxGoodFramesCounter_1 in AQ_MsmSystemRxGoodFramesCounterRegister_EUR */
#define word_AQ_MsmSystemRxGoodFramesCounterRegister_EUR_msmSystemRxGoodFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemRxFcsErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxFcsErrorsCounterRegister_EUR_baseRegisterAddress 0x6048
/*! \brief MMD address of structure AQ_MsmSystemRxFcsErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxFcsErrorsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemFcsErrorCounter_0 in AQ_MsmSystemRxFcsErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxFcsErrorsCounterRegister_EUR_msmSystemFcsErrorCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemFcsErrorCounter_0 in AQ_MsmSystemRxFcsErrorsCounterRegister_EUR */
#define bits_AQ_MsmSystemRxFcsErrorsCounterRegister_EUR_msmSystemFcsErrorCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemFcsErrorCounter_0 in AQ_MsmSystemRxFcsErrorsCounterRegister_EUR */
#define word_AQ_MsmSystemRxFcsErrorsCounterRegister_EUR_msmSystemFcsErrorCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemFcsErrorCounter_1 in AQ_MsmSystemRxFcsErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxFcsErrorsCounterRegister_EUR_msmSystemFcsErrorCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemFcsErrorCounter_1 in AQ_MsmSystemRxFcsErrorsCounterRegister_EUR */
#define bits_AQ_MsmSystemRxFcsErrorsCounterRegister_EUR_msmSystemFcsErrorCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemFcsErrorCounter_1 in AQ_MsmSystemRxFcsErrorsCounterRegister_EUR */
#define word_AQ_MsmSystemRxFcsErrorsCounterRegister_EUR_msmSystemFcsErrorCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR_baseRegisterAddress 0x604C
/*! \brief MMD address of structure AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemAlignmentErrorCounter_0 in AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR_msmSystemAlignmentErrorCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemAlignmentErrorCounter_0 in AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR */
#define bits_AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR_msmSystemAlignmentErrorCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemAlignmentErrorCounter_0 in AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR */
#define word_AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR_msmSystemAlignmentErrorCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemAlignmentErrorCounter_1 in AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR_msmSystemAlignmentErrorCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemAlignmentErrorCounter_1 in AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR */
#define bits_AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR_msmSystemAlignmentErrorCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemAlignmentErrorCounter_1 in AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR */
#define word_AQ_MsmSystemRxAlignmentErrorsCounterRegister_EUR_msmSystemAlignmentErrorCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemTxPauseFramesCounterRegister_EUR */
#define AQ_MsmSystemTxPauseFramesCounterRegister_EUR_baseRegisterAddress 0x6050
/*! \brief MMD address of structure AQ_MsmSystemTxPauseFramesCounterRegister_EUR */
#define AQ_MsmSystemTxPauseFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxPauseFramesCounter_0 in AQ_MsmSystemTxPauseFramesCounterRegister_EUR */
#define AQ_MsmSystemTxPauseFramesCounterRegister_EUR_msmSystemTxPauseFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxPauseFramesCounter_0 in AQ_MsmSystemTxPauseFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemTxPauseFramesCounterRegister_EUR_msmSystemTxPauseFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxPauseFramesCounter_0 in AQ_MsmSystemTxPauseFramesCounterRegister_EUR */
#define word_AQ_MsmSystemTxPauseFramesCounterRegister_EUR_msmSystemTxPauseFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxPauseFramesCounter_1 in AQ_MsmSystemTxPauseFramesCounterRegister_EUR */
#define AQ_MsmSystemTxPauseFramesCounterRegister_EUR_msmSystemTxPauseFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxPauseFramesCounter_1 in AQ_MsmSystemTxPauseFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemTxPauseFramesCounterRegister_EUR_msmSystemTxPauseFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxPauseFramesCounter_1 in AQ_MsmSystemTxPauseFramesCounterRegister_EUR */
#define word_AQ_MsmSystemTxPauseFramesCounterRegister_EUR_msmSystemTxPauseFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemRxPauseFramesCounterRegister_EUR */
#define AQ_MsmSystemRxPauseFramesCounterRegister_EUR_baseRegisterAddress 0x6054
/*! \brief MMD address of structure AQ_MsmSystemRxPauseFramesCounterRegister_EUR */
#define AQ_MsmSystemRxPauseFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxPauseFramesCounter_0 in AQ_MsmSystemRxPauseFramesCounterRegister_EUR */
#define AQ_MsmSystemRxPauseFramesCounterRegister_EUR_msmSystemRxPauseFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxPauseFramesCounter_0 in AQ_MsmSystemRxPauseFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemRxPauseFramesCounterRegister_EUR_msmSystemRxPauseFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxPauseFramesCounter_0 in AQ_MsmSystemRxPauseFramesCounterRegister_EUR */
#define word_AQ_MsmSystemRxPauseFramesCounterRegister_EUR_msmSystemRxPauseFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxPauseFramesCounter_1 in AQ_MsmSystemRxPauseFramesCounterRegister_EUR */
#define AQ_MsmSystemRxPauseFramesCounterRegister_EUR_msmSystemRxPauseFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxPauseFramesCounter_1 in AQ_MsmSystemRxPauseFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemRxPauseFramesCounterRegister_EUR_msmSystemRxPauseFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxPauseFramesCounter_1 in AQ_MsmSystemRxPauseFramesCounterRegister_EUR */
#define word_AQ_MsmSystemRxPauseFramesCounterRegister_EUR_msmSystemRxPauseFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR_baseRegisterAddress 0x6058
/*! \brief MMD address of structure AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxTooLongErrorsCounter_0 in AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR_msmSystemRxTooLongErrorsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxTooLongErrorsCounter_0 in AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR */
#define bits_AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR_msmSystemRxTooLongErrorsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxTooLongErrorsCounter_0 in AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR */
#define word_AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR_msmSystemRxTooLongErrorsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxTooLongErrorsCounter_1 in AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR_msmSystemRxTooLongErrorsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxTooLongErrorsCounter_1 in AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR */
#define bits_AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR_msmSystemRxTooLongErrorsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxTooLongErrorsCounter_1 in AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR */
#define word_AQ_MsmSystemRxTooLongErrorsCounterRegister_EUR_msmSystemRxTooLongErrorsCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR_baseRegisterAddress 0x605C
/*! \brief MMD address of structure AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxInRangeLengthErrorsCounter_0 in AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR_msmSystemRxInRangeLengthErrorsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxInRangeLengthErrorsCounter_0 in AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR */
#define bits_AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR_msmSystemRxInRangeLengthErrorsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxInRangeLengthErrorsCounter_0 in AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR */
#define word_AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR_msmSystemRxInRangeLengthErrorsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxInRangeLengthErrorsCounter_1 in AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR_msmSystemRxInRangeLengthErrorsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxInRangeLengthErrorsCounter_1 in AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR */
#define bits_AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR_msmSystemRxInRangeLengthErrorsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxInRangeLengthErrorsCounter_1 in AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR */
#define word_AQ_MsmSystemRxInRangeLengthErrorsCounterRegister_EUR_msmSystemRxInRangeLengthErrorsCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemTxVlanFramesCounterRegister_EUR */
#define AQ_MsmSystemTxVlanFramesCounterRegister_EUR_baseRegisterAddress 0x6060
/*! \brief MMD address of structure AQ_MsmSystemTxVlanFramesCounterRegister_EUR */
#define AQ_MsmSystemTxVlanFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxVlanFramesCounter_0 in AQ_MsmSystemTxVlanFramesCounterRegister_EUR */
#define AQ_MsmSystemTxVlanFramesCounterRegister_EUR_msmSystemTxVlanFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxVlanFramesCounter_0 in AQ_MsmSystemTxVlanFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemTxVlanFramesCounterRegister_EUR_msmSystemTxVlanFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxVlanFramesCounter_0 in AQ_MsmSystemTxVlanFramesCounterRegister_EUR */
#define word_AQ_MsmSystemTxVlanFramesCounterRegister_EUR_msmSystemTxVlanFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxVlanFramesCounter_1 in AQ_MsmSystemTxVlanFramesCounterRegister_EUR */
#define AQ_MsmSystemTxVlanFramesCounterRegister_EUR_msmSystemTxVlanFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxVlanFramesCounter_1 in AQ_MsmSystemTxVlanFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemTxVlanFramesCounterRegister_EUR_msmSystemTxVlanFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxVlanFramesCounter_1 in AQ_MsmSystemTxVlanFramesCounterRegister_EUR */
#define word_AQ_MsmSystemTxVlanFramesCounterRegister_EUR_msmSystemTxVlanFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemRxVlanFramesCounterRegister_EUR */
#define AQ_MsmSystemRxVlanFramesCounterRegister_EUR_baseRegisterAddress 0x6064
/*! \brief MMD address of structure AQ_MsmSystemRxVlanFramesCounterRegister_EUR */
#define AQ_MsmSystemRxVlanFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxVlanFramesCounter_0 in AQ_MsmSystemRxVlanFramesCounterRegister_EUR */
#define AQ_MsmSystemRxVlanFramesCounterRegister_EUR_msmSystemRxVlanFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxVlanFramesCounter_0 in AQ_MsmSystemRxVlanFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemRxVlanFramesCounterRegister_EUR_msmSystemRxVlanFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxVlanFramesCounter_0 in AQ_MsmSystemRxVlanFramesCounterRegister_EUR */
#define word_AQ_MsmSystemRxVlanFramesCounterRegister_EUR_msmSystemRxVlanFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxVlanFramesCounter_1 in AQ_MsmSystemRxVlanFramesCounterRegister_EUR */
#define AQ_MsmSystemRxVlanFramesCounterRegister_EUR_msmSystemRxVlanFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxVlanFramesCounter_1 in AQ_MsmSystemRxVlanFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemRxVlanFramesCounterRegister_EUR_msmSystemRxVlanFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxVlanFramesCounter_1 in AQ_MsmSystemRxVlanFramesCounterRegister_EUR */
#define word_AQ_MsmSystemRxVlanFramesCounterRegister_EUR_msmSystemRxVlanFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define AQ_MsmSystemTxOctetsCounterRegister_EUR_baseRegisterAddress 0x6068
/*! \brief MMD address of structure AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define AQ_MsmSystemTxOctetsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxOctetsCounter_0 in AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define AQ_MsmSystemTxOctetsCounterRegister_EUR_msmSystemTxOctetsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxOctetsCounter_0 in AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define bits_AQ_MsmSystemTxOctetsCounterRegister_EUR_msmSystemTxOctetsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxOctetsCounter_0 in AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define word_AQ_MsmSystemTxOctetsCounterRegister_EUR_msmSystemTxOctetsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxOctetsCounter_1 in AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define AQ_MsmSystemTxOctetsCounterRegister_EUR_msmSystemTxOctetsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxOctetsCounter_1 in AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define bits_AQ_MsmSystemTxOctetsCounterRegister_EUR_msmSystemTxOctetsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxOctetsCounter_1 in AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define word_AQ_MsmSystemTxOctetsCounterRegister_EUR_msmSystemTxOctetsCounter_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxOctetsCounter_2 in AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define AQ_MsmSystemTxOctetsCounterRegister_EUR_msmSystemTxOctetsCounter_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxOctetsCounter_2 in AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define bits_AQ_MsmSystemTxOctetsCounterRegister_EUR_msmSystemTxOctetsCounter_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxOctetsCounter_2 in AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define word_AQ_MsmSystemTxOctetsCounterRegister_EUR_msmSystemTxOctetsCounter_2 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxOctetsCounter_3 in AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define AQ_MsmSystemTxOctetsCounterRegister_EUR_msmSystemTxOctetsCounter_3 3
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxOctetsCounter_3 in AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define bits_AQ_MsmSystemTxOctetsCounterRegister_EUR_msmSystemTxOctetsCounter_3 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxOctetsCounter_3 in AQ_MsmSystemTxOctetsCounterRegister_EUR */
#define word_AQ_MsmSystemTxOctetsCounterRegister_EUR_msmSystemTxOctetsCounter_3 u3.word_3

/*! \brief Base register address of structure AQ_MsmSystemRxOctetsCounterRegister_EUR */
#define AQ_MsmSystemRxOctetsCounterRegister_EUR_baseRegisterAddress 0x606C
/*! \brief MMD address of structure AQ_MsmSystemRxOctetsCounterRegister_EUR */
#define AQ_MsmSystemRxOctetsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxOctetsCounter_0 in AQ_MsmSystemRxOctetsCounterRegister_EUR */
#define AQ_MsmSystemRxOctetsCounterRegister_EUR_msmSystemRxOctetsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxOctetsCounter_0 in AQ_MsmSystemRxOctetsCounterRegister_EUR */
#define bits_AQ_MsmSystemRxOctetsCounterRegister_EUR_msmSystemRxOctetsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxOctetsCounter_0 in AQ_MsmSystemRxOctetsCounterRegister_EUR */
#define word_AQ_MsmSystemRxOctetsCounterRegister_EUR_msmSystemRxOctetsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxOctetsCounter_1 in AQ_MsmSystemRxOctetsCounterRegister_EUR */
#define AQ_MsmSystemRxOctetsCounterRegister_EUR_msmSystemRxOctetsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxOctetsCounter_1 in AQ_MsmSystemRxOctetsCounterRegister_EUR */
#define bits_AQ_MsmSystemRxOctetsCounterRegister_EUR_msmSystemRxOctetsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxOctetsCounter_1 in AQ_MsmSystemRxOctetsCounterRegister_EUR */
#define word_AQ_MsmSystemRxOctetsCounterRegister_EUR_msmSystemRxOctetsCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemRxUnicastFramesCounterRegister_EUR */
#define AQ_MsmSystemRxUnicastFramesCounterRegister_EUR_baseRegisterAddress 0x6070
/*! \brief MMD address of structure AQ_MsmSystemRxUnicastFramesCounterRegister_EUR */
#define AQ_MsmSystemRxUnicastFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxUnicastFramesCounter_0 in AQ_MsmSystemRxUnicastFramesCounterRegister_EUR */
#define AQ_MsmSystemRxUnicastFramesCounterRegister_EUR_msmSystemRxUnicastFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxUnicastFramesCounter_0 in AQ_MsmSystemRxUnicastFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemRxUnicastFramesCounterRegister_EUR_msmSystemRxUnicastFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxUnicastFramesCounter_0 in AQ_MsmSystemRxUnicastFramesCounterRegister_EUR */
#define word_AQ_MsmSystemRxUnicastFramesCounterRegister_EUR_msmSystemRxUnicastFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxUnicastFramesCounter_1 in AQ_MsmSystemRxUnicastFramesCounterRegister_EUR */
#define AQ_MsmSystemRxUnicastFramesCounterRegister_EUR_msmSystemRxUnicastFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxUnicastFramesCounter_1 in AQ_MsmSystemRxUnicastFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemRxUnicastFramesCounterRegister_EUR_msmSystemRxUnicastFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxUnicastFramesCounter_1 in AQ_MsmSystemRxUnicastFramesCounterRegister_EUR */
#define word_AQ_MsmSystemRxUnicastFramesCounterRegister_EUR_msmSystemRxUnicastFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemRxMulticastFramesCounterRegister_EUR */
#define AQ_MsmSystemRxMulticastFramesCounterRegister_EUR_baseRegisterAddress 0x6074
/*! \brief MMD address of structure AQ_MsmSystemRxMulticastFramesCounterRegister_EUR */
#define AQ_MsmSystemRxMulticastFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxMulticastFramesCounter_0 in AQ_MsmSystemRxMulticastFramesCounterRegister_EUR */
#define AQ_MsmSystemRxMulticastFramesCounterRegister_EUR_msmSystemRxMulticastFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxMulticastFramesCounter_0 in AQ_MsmSystemRxMulticastFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemRxMulticastFramesCounterRegister_EUR_msmSystemRxMulticastFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxMulticastFramesCounter_0 in AQ_MsmSystemRxMulticastFramesCounterRegister_EUR */
#define word_AQ_MsmSystemRxMulticastFramesCounterRegister_EUR_msmSystemRxMulticastFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxMulticastFramesCounter_1 in AQ_MsmSystemRxMulticastFramesCounterRegister_EUR */
#define AQ_MsmSystemRxMulticastFramesCounterRegister_EUR_msmSystemRxMulticastFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxMulticastFramesCounter_1 in AQ_MsmSystemRxMulticastFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemRxMulticastFramesCounterRegister_EUR_msmSystemRxMulticastFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxMulticastFramesCounter_1 in AQ_MsmSystemRxMulticastFramesCounterRegister_EUR */
#define word_AQ_MsmSystemRxMulticastFramesCounterRegister_EUR_msmSystemRxMulticastFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR_baseRegisterAddress 0x6078
/*! \brief MMD address of structure AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxBroadcastFramesCounter_0 in AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR_msmSystemRxBroadcastFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxBroadcastFramesCounter_0 in AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR_msmSystemRxBroadcastFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxBroadcastFramesCounter_0 in AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR */
#define word_AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR_msmSystemRxBroadcastFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxBroadcastFramesCounter_1 in AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR_msmSystemRxBroadcastFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxBroadcastFramesCounter_1 in AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR_msmSystemRxBroadcastFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxBroadcastFramesCounter_1 in AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR */
#define word_AQ_MsmSystemRxBroadcastFramesCounterRegister_EUR_msmSystemRxBroadcastFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemTxErrorsCounterRegister_EUR */
#define AQ_MsmSystemTxErrorsCounterRegister_EUR_baseRegisterAddress 0x607C
/*! \brief MMD address of structure AQ_MsmSystemTxErrorsCounterRegister_EUR */
#define AQ_MsmSystemTxErrorsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxErrorsCounter_0 in AQ_MsmSystemTxErrorsCounterRegister_EUR */
#define AQ_MsmSystemTxErrorsCounterRegister_EUR_msmSystemTxErrorsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxErrorsCounter_0 in AQ_MsmSystemTxErrorsCounterRegister_EUR */
#define bits_AQ_MsmSystemTxErrorsCounterRegister_EUR_msmSystemTxErrorsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxErrorsCounter_0 in AQ_MsmSystemTxErrorsCounterRegister_EUR */
#define word_AQ_MsmSystemTxErrorsCounterRegister_EUR_msmSystemTxErrorsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxErrorsCounter_1 in AQ_MsmSystemTxErrorsCounterRegister_EUR */
#define AQ_MsmSystemTxErrorsCounterRegister_EUR_msmSystemTxErrorsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxErrorsCounter_1 in AQ_MsmSystemTxErrorsCounterRegister_EUR */
#define bits_AQ_MsmSystemTxErrorsCounterRegister_EUR_msmSystemTxErrorsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxErrorsCounter_1 in AQ_MsmSystemTxErrorsCounterRegister_EUR */
#define word_AQ_MsmSystemTxErrorsCounterRegister_EUR_msmSystemTxErrorsCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemTxUnicastFramesCounterRegister_EUR */
#define AQ_MsmSystemTxUnicastFramesCounterRegister_EUR_baseRegisterAddress 0x6084
/*! \brief MMD address of structure AQ_MsmSystemTxUnicastFramesCounterRegister_EUR */
#define AQ_MsmSystemTxUnicastFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxUnicastFramesCounter_0 in AQ_MsmSystemTxUnicastFramesCounterRegister_EUR */
#define AQ_MsmSystemTxUnicastFramesCounterRegister_EUR_msmSystemTxUnicastFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxUnicastFramesCounter_0 in AQ_MsmSystemTxUnicastFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemTxUnicastFramesCounterRegister_EUR_msmSystemTxUnicastFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxUnicastFramesCounter_0 in AQ_MsmSystemTxUnicastFramesCounterRegister_EUR */
#define word_AQ_MsmSystemTxUnicastFramesCounterRegister_EUR_msmSystemTxUnicastFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxUnicastFramesCounter_1 in AQ_MsmSystemTxUnicastFramesCounterRegister_EUR */
#define AQ_MsmSystemTxUnicastFramesCounterRegister_EUR_msmSystemTxUnicastFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxUnicastFramesCounter_1 in AQ_MsmSystemTxUnicastFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemTxUnicastFramesCounterRegister_EUR_msmSystemTxUnicastFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxUnicastFramesCounter_1 in AQ_MsmSystemTxUnicastFramesCounterRegister_EUR */
#define word_AQ_MsmSystemTxUnicastFramesCounterRegister_EUR_msmSystemTxUnicastFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemTxMulticastFramesCounterRegister_EUR */
#define AQ_MsmSystemTxMulticastFramesCounterRegister_EUR_baseRegisterAddress 0x6088
/*! \brief MMD address of structure AQ_MsmSystemTxMulticastFramesCounterRegister_EUR */
#define AQ_MsmSystemTxMulticastFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxMulticastFramesCounter_0 in AQ_MsmSystemTxMulticastFramesCounterRegister_EUR */
#define AQ_MsmSystemTxMulticastFramesCounterRegister_EUR_msmSystemTxMulticastFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxMulticastFramesCounter_0 in AQ_MsmSystemTxMulticastFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemTxMulticastFramesCounterRegister_EUR_msmSystemTxMulticastFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxMulticastFramesCounter_0 in AQ_MsmSystemTxMulticastFramesCounterRegister_EUR */
#define word_AQ_MsmSystemTxMulticastFramesCounterRegister_EUR_msmSystemTxMulticastFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxMulticastFramesCounter_1 in AQ_MsmSystemTxMulticastFramesCounterRegister_EUR */
#define AQ_MsmSystemTxMulticastFramesCounterRegister_EUR_msmSystemTxMulticastFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxMulticastFramesCounter_1 in AQ_MsmSystemTxMulticastFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemTxMulticastFramesCounterRegister_EUR_msmSystemTxMulticastFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxMulticastFramesCounter_1 in AQ_MsmSystemTxMulticastFramesCounterRegister_EUR */
#define word_AQ_MsmSystemTxMulticastFramesCounterRegister_EUR_msmSystemTxMulticastFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR_baseRegisterAddress 0x608C
/*! \brief MMD address of structure AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxBroadcastFramesCounter_0 in AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR_msmSystemTxBroadcastFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxBroadcastFramesCounter_0 in AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR_msmSystemTxBroadcastFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxBroadcastFramesCounter_0 in AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR */
#define word_AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR_msmSystemTxBroadcastFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemTxBroadcastFramesCounter_1 in AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR_msmSystemTxBroadcastFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemTxBroadcastFramesCounter_1 in AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR */
#define bits_AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR_msmSystemTxBroadcastFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemTxBroadcastFramesCounter_1 in AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR */
#define word_AQ_MsmSystemTxBroadcastFramesCounterRegister_EUR_msmSystemTxBroadcastFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemRxErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxErrorsCounterRegister_EUR_baseRegisterAddress 0x60C8
/*! \brief MMD address of structure AQ_MsmSystemRxErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxErrorsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxErrorsCounter_0 in AQ_MsmSystemRxErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxErrorsCounterRegister_EUR_msmSystemRxErrorsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxErrorsCounter_0 in AQ_MsmSystemRxErrorsCounterRegister_EUR */
#define bits_AQ_MsmSystemRxErrorsCounterRegister_EUR_msmSystemRxErrorsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxErrorsCounter_0 in AQ_MsmSystemRxErrorsCounterRegister_EUR */
#define word_AQ_MsmSystemRxErrorsCounterRegister_EUR_msmSystemRxErrorsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemRxErrorsCounter_1 in AQ_MsmSystemRxErrorsCounterRegister_EUR */
#define AQ_MsmSystemRxErrorsCounterRegister_EUR_msmSystemRxErrorsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemRxErrorsCounter_1 in AQ_MsmSystemRxErrorsCounterRegister_EUR */
#define bits_AQ_MsmSystemRxErrorsCounterRegister_EUR_msmSystemRxErrorsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemRxErrorsCounter_1 in AQ_MsmSystemRxErrorsCounterRegister_EUR */
#define word_AQ_MsmSystemRxErrorsCounterRegister_EUR_msmSystemRxErrorsCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmSystemSgmiiControlRegister_EUR */
#define AQ_MsmSystemSgmiiControlRegister_EUR_baseRegisterAddress 0x6180
/*! \brief MMD address of structure AQ_MsmSystemSgmiiControlRegister_EUR */
#define AQ_MsmSystemSgmiiControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiReset in AQ_MsmSystemSgmiiControlRegister_EUR */
#define AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiReset in AQ_MsmSystemSgmiiControlRegister_EUR */
#define bits_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiReset in AQ_MsmSystemSgmiiControlRegister_EUR */
#define word_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiLoopback in AQ_MsmSystemSgmiiControlRegister_EUR */
#define AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiLoopback 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiLoopback in AQ_MsmSystemSgmiiControlRegister_EUR */
#define bits_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiLoopback u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiLoopback in AQ_MsmSystemSgmiiControlRegister_EUR */
#define word_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiLoopback u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiSpeedSelection_2 in AQ_MsmSystemSgmiiControlRegister_EUR */
#define AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiSpeedSelection_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiSpeedSelection_2 in AQ_MsmSystemSgmiiControlRegister_EUR */
#define bits_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiSpeedSelection_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiSpeedSelection_2 in AQ_MsmSystemSgmiiControlRegister_EUR */
#define word_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiSpeedSelection_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiAutonegotationEnable in AQ_MsmSystemSgmiiControlRegister_EUR */
#define AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiAutonegotationEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiAutonegotationEnable in AQ_MsmSystemSgmiiControlRegister_EUR */
#define bits_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiAutonegotationEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiAutonegotationEnable in AQ_MsmSystemSgmiiControlRegister_EUR */
#define word_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiAutonegotationEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiPowerDown in AQ_MsmSystemSgmiiControlRegister_EUR */
#define AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiPowerDown 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiPowerDown in AQ_MsmSystemSgmiiControlRegister_EUR */
#define bits_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiPowerDown u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiPowerDown in AQ_MsmSystemSgmiiControlRegister_EUR */
#define word_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiPowerDown u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiIsolate in AQ_MsmSystemSgmiiControlRegister_EUR */
#define AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiIsolate 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiIsolate in AQ_MsmSystemSgmiiControlRegister_EUR */
#define bits_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiIsolate u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiIsolate in AQ_MsmSystemSgmiiControlRegister_EUR */
#define word_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiIsolate u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiRestartAutonegotiation in AQ_MsmSystemSgmiiControlRegister_EUR */
#define AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiRestartAutonegotiation 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiRestartAutonegotiation in AQ_MsmSystemSgmiiControlRegister_EUR */
#define bits_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiRestartAutonegotiation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiRestartAutonegotiation in AQ_MsmSystemSgmiiControlRegister_EUR */
#define word_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiRestartAutonegotiation u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiDuplexMode in AQ_MsmSystemSgmiiControlRegister_EUR */
#define AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiDuplexMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiDuplexMode in AQ_MsmSystemSgmiiControlRegister_EUR */
#define bits_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiDuplexMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiDuplexMode in AQ_MsmSystemSgmiiControlRegister_EUR */
#define word_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiDuplexMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiCollisionTest in AQ_MsmSystemSgmiiControlRegister_EUR */
#define AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiCollisionTest 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiCollisionTest in AQ_MsmSystemSgmiiControlRegister_EUR */
#define bits_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiCollisionTest u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiCollisionTest in AQ_MsmSystemSgmiiControlRegister_EUR */
#define word_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiCollisionTest u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiSpeedSelection_1 in AQ_MsmSystemSgmiiControlRegister_EUR */
#define AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiSpeedSelection_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiSpeedSelection_1 in AQ_MsmSystemSgmiiControlRegister_EUR */
#define bits_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiSpeedSelection_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiSpeedSelection_1 in AQ_MsmSystemSgmiiControlRegister_EUR */
#define word_AQ_MsmSystemSgmiiControlRegister_EUR_msmSystemSgmiiSpeedSelection_1 u0.word_0

/*! \brief Base register address of structure AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define AQ_MsmSystemSgmiiIfModeRegister_EUR_baseRegisterAddress 0x61A8
/*! \brief MMD address of structure AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define AQ_MsmSystemSgmiiIfModeRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiPcsEnable in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemSgmiiPcsEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiPcsEnable in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define bits_AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemSgmiiPcsEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiPcsEnable in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define word_AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemSgmiiPcsEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiHalfDuplex in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemSgmiiHalfDuplex 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiHalfDuplex in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define bits_AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemSgmiiHalfDuplex u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiHalfDuplex in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define word_AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemSgmiiHalfDuplex u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiSpeed in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemSgmiiSpeed 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiSpeed in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define bits_AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemSgmiiSpeed u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiSpeed in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define word_AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemSgmiiSpeed u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemUseSgmiiAutonegotiation in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemUseSgmiiAutonegotiation 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemUseSgmiiAutonegotiation in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define bits_AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemUseSgmiiAutonegotiation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemUseSgmiiAutonegotiation in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define word_AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemUseSgmiiAutonegotiation u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmSystemSgmiiEnable in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemSgmiiEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmSystemSgmiiEnable in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define bits_AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemSgmiiEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmSystemSgmiiEnable in AQ_MsmSystemSgmiiIfModeRegister_EUR */
#define word_AQ_MsmSystemSgmiiIfModeRegister_EUR_msmSystemSgmiiEnable u0.word_0

/*! \brief Base register address of structure AQ_MssIngressVlanTpid_0Register_EUR */
#define AQ_MssIngressVlanTpid_0Register_EUR_baseRegisterAddress 0x8006
/*! \brief MMD address of structure AQ_MssIngressVlanTpid_0Register_EUR */
#define AQ_MssIngressVlanTpid_0Register_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressVlanStag in AQ_MssIngressVlanTpid_0Register_EUR */
#define AQ_MssIngressVlanTpid_0Register_EUR_mssIngressVlanStag 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressVlanStag in AQ_MssIngressVlanTpid_0Register_EUR */
#define bits_AQ_MssIngressVlanTpid_0Register_EUR_mssIngressVlanStag u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressVlanStag in AQ_MssIngressVlanTpid_0Register_EUR */
#define word_AQ_MssIngressVlanTpid_0Register_EUR_mssIngressVlanStag u0.word_0

/*! \brief Base register address of structure AQ_MssIngressVlanTpid_1Register_EUR */
#define AQ_MssIngressVlanTpid_1Register_EUR_baseRegisterAddress 0x8008
/*! \brief MMD address of structure AQ_MssIngressVlanTpid_1Register_EUR */
#define AQ_MssIngressVlanTpid_1Register_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressVlanQtag in AQ_MssIngressVlanTpid_1Register_EUR */
#define AQ_MssIngressVlanTpid_1Register_EUR_mssIngressVlanQtag 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressVlanQtag in AQ_MssIngressVlanTpid_1Register_EUR */
#define bits_AQ_MssIngressVlanTpid_1Register_EUR_mssIngressVlanQtag u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressVlanQtag in AQ_MssIngressVlanTpid_1Register_EUR */
#define word_AQ_MssIngressVlanTpid_1Register_EUR_mssIngressVlanQtag u0.word_0

/*! \brief Base register address of structure AQ_MssIngressVlanControlRegister_EUR */
#define AQ_MssIngressVlanControlRegister_EUR_baseRegisterAddress 0x800A
/*! \brief MMD address of structure AQ_MssIngressVlanControlRegister_EUR */
#define AQ_MssIngressVlanControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressVlanUpMapTableLSW in AQ_MssIngressVlanControlRegister_EUR */
#define AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanUpMapTableLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressVlanUpMapTableLSW in AQ_MssIngressVlanControlRegister_EUR */
#define bits_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanUpMapTableLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressVlanUpMapTableLSW in AQ_MssIngressVlanControlRegister_EUR */
#define word_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanUpMapTableLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressVlanQtagParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanQtagParseEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressVlanQtagParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define bits_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanQtagParseEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressVlanQtagParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define word_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanQtagParseEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressVlanStagParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanStagParseEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressVlanStagParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define bits_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanStagParseEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressVlanStagParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define word_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanStagParseEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressVlanQinqParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanQinqParseEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressVlanQinqParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define bits_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanQinqParseEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressVlanQinqParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define word_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanQinqParseEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressVlanQtagUpParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanQtagUpParseEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressVlanQtagUpParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define bits_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanQtagUpParseEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressVlanQtagUpParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define word_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanQtagUpParseEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressVlanStagUpParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanStagUpParseEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressVlanStagUpParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define bits_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanStagUpParseEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressVlanStagUpParseEnable in AQ_MssIngressVlanControlRegister_EUR */
#define word_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanStagUpParseEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressVlanUpDefault in AQ_MssIngressVlanControlRegister_EUR */
#define AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanUpDefault 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressVlanUpDefault in AQ_MssIngressVlanControlRegister_EUR */
#define bits_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanUpDefault u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressVlanUpDefault in AQ_MssIngressVlanControlRegister_EUR */
#define word_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanUpDefault u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressVlanUpMapTableMSW in AQ_MssIngressVlanControlRegister_EUR */
#define AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanUpMapTableMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressVlanUpMapTableMSW in AQ_MssIngressVlanControlRegister_EUR */
#define bits_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanUpMapTableMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressVlanUpMapTableMSW in AQ_MssIngressVlanControlRegister_EUR */
#define word_AQ_MssIngressVlanControlRegister_EUR_mssIngressVlanUpMapTableMSW u1.word_1

/*! \brief Base register address of structure AQ_MssIngressMtuSizeControlRegister_EUR */
#define AQ_MssIngressMtuSizeControlRegister_EUR_baseRegisterAddress 0x800C
/*! \brief MMD address of structure AQ_MssIngressMtuSizeControlRegister_EUR */
#define AQ_MssIngressMtuSizeControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressControlledPacketMtuSize in AQ_MssIngressMtuSizeControlRegister_EUR */
#define AQ_MssIngressMtuSizeControlRegister_EUR_mssIngressControlledPacketMtuSize 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressControlledPacketMtuSize in AQ_MssIngressMtuSizeControlRegister_EUR */
#define bits_AQ_MssIngressMtuSizeControlRegister_EUR_mssIngressControlledPacketMtuSize u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressControlledPacketMtuSize in AQ_MssIngressMtuSizeControlRegister_EUR */
#define word_AQ_MssIngressMtuSizeControlRegister_EUR_mssIngressControlledPacketMtuSize u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressUncontrolledPacketMtuSize in AQ_MssIngressMtuSizeControlRegister_EUR */
#define AQ_MssIngressMtuSizeControlRegister_EUR_mssIngressUncontrolledPacketMtuSize 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressUncontrolledPacketMtuSize in AQ_MssIngressMtuSizeControlRegister_EUR */
#define bits_AQ_MssIngressMtuSizeControlRegister_EUR_mssIngressUncontrolledPacketMtuSize u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressUncontrolledPacketMtuSize in AQ_MssIngressMtuSizeControlRegister_EUR */
#define word_AQ_MssIngressMtuSizeControlRegister_EUR_mssIngressUncontrolledPacketMtuSize u1.word_1

/*! \brief Base register address of structure AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_baseRegisterAddress 0x800E
/*! \brief MMD address of structure AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressIcvLsb_8BytesEnable in AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mssIngressIcvLsb_8BytesEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressIcvLsb_8BytesEnable in AQ_MssIngressControlRegister_EUR */
#define bits_AQ_MssIngressControlRegister_EUR_mssIngressIcvLsb_8BytesEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressIcvLsb_8BytesEnable in AQ_MssIngressControlRegister_EUR */
#define word_AQ_MssIngressControlRegister_EUR_mssIngressIcvLsb_8BytesEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressGlobalValidateFrames in AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mssIngressGlobalValidateFrames 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressGlobalValidateFrames in AQ_MssIngressControlRegister_EUR */
#define bits_AQ_MssIngressControlRegister_EUR_mssIngressGlobalValidateFrames u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressGlobalValidateFrames in AQ_MssIngressControlRegister_EUR */
#define word_AQ_MssIngressControlRegister_EUR_mssIngressGlobalValidateFrames u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressRemoveSectag in AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mssIngressRemoveSectag 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressRemoveSectag in AQ_MssIngressControlRegister_EUR */
#define bits_AQ_MssIngressControlRegister_EUR_mssIngressRemoveSectag u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressRemoveSectag in AQ_MssIngressControlRegister_EUR */
#define word_AQ_MssIngressControlRegister_EUR_mssIngressRemoveSectag u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressHighPriority in AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mssIngressHighPriority 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressHighPriority in AQ_MssIngressControlRegister_EUR */
#define bits_AQ_MssIngressControlRegister_EUR_mssIngressHighPriority u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressHighPriority in AQ_MssIngressControlRegister_EUR */
#define word_AQ_MssIngressControlRegister_EUR_mssIngressHighPriority u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressClearCount in AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mssIngressClearCount 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressClearCount in AQ_MssIngressControlRegister_EUR */
#define bits_AQ_MssIngressControlRegister_EUR_mssIngressClearCount u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressClearCount in AQ_MssIngressControlRegister_EUR */
#define word_AQ_MssIngressControlRegister_EUR_mssIngressClearCount u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressClearGlobalTime in AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mssIngressClearGlobalTime 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressClearGlobalTime in AQ_MssIngressControlRegister_EUR */
#define bits_AQ_MssIngressControlRegister_EUR_mssIngressClearGlobalTime u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressClearGlobalTime in AQ_MssIngressControlRegister_EUR */
#define word_AQ_MssIngressControlRegister_EUR_mssIngressClearGlobalTime u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressCheckIcv in AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mssIngressCheckIcv 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressCheckIcv in AQ_MssIngressControlRegister_EUR */
#define bits_AQ_MssIngressControlRegister_EUR_mssIngressCheckIcv u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressCheckIcv in AQ_MssIngressControlRegister_EUR */
#define word_AQ_MssIngressControlRegister_EUR_mssIngressCheckIcv u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressDropIgprcMiss in AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mssIngressDropIgprcMiss 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressDropIgprcMiss in AQ_MssIngressControlRegister_EUR */
#define bits_AQ_MssIngressControlRegister_EUR_mssIngressDropIgprcMiss u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressDropIgprcMiss in AQ_MssIngressControlRegister_EUR */
#define word_AQ_MssIngressControlRegister_EUR_mssIngressDropIgprcMiss u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressDropKayPacket in AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mssIngressDropKayPacket 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressDropKayPacket in AQ_MssIngressControlRegister_EUR */
#define bits_AQ_MssIngressControlRegister_EUR_mssIngressDropKayPacket u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressDropKayPacket in AQ_MssIngressControlRegister_EUR */
#define word_AQ_MssIngressControlRegister_EUR_mssIngressDropKayPacket u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressMaskShortLengthError in AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mssIngressMaskShortLengthError 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressMaskShortLengthError in AQ_MssIngressControlRegister_EUR */
#define bits_AQ_MssIngressControlRegister_EUR_mssIngressMaskShortLengthError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressMaskShortLengthError in AQ_MssIngressControlRegister_EUR */
#define word_AQ_MssIngressControlRegister_EUR_mssIngressMaskShortLengthError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressCreateSci in AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mssIngressCreateSci 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressCreateSci in AQ_MssIngressControlRegister_EUR */
#define bits_AQ_MssIngressControlRegister_EUR_mssIngressCreateSci u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressCreateSci in AQ_MssIngressControlRegister_EUR */
#define word_AQ_MssIngressControlRegister_EUR_mssIngressCreateSci u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressOperationPointToPoint in AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mssIngressOperationPointToPoint 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressOperationPointToPoint in AQ_MssIngressControlRegister_EUR */
#define bits_AQ_MssIngressControlRegister_EUR_mssIngressOperationPointToPoint u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressOperationPointToPoint in AQ_MssIngressControlRegister_EUR */
#define word_AQ_MssIngressControlRegister_EUR_mssIngressOperationPointToPoint u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSoftReset in AQ_MssIngressControlRegister_EUR */
#define AQ_MssIngressControlRegister_EUR_mssIngressSoftReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSoftReset in AQ_MssIngressControlRegister_EUR */
#define bits_AQ_MssIngressControlRegister_EUR_mssIngressSoftReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSoftReset in AQ_MssIngressControlRegister_EUR */
#define word_AQ_MssIngressControlRegister_EUR_mssIngressSoftReset u0.word_0

/*! \brief Base register address of structure AQ_MssIngressSaControlRegister_EUR */
#define AQ_MssIngressSaControlRegister_EUR_baseRegisterAddress 0x8010
/*! \brief MMD address of structure AQ_MssIngressSaControlRegister_EUR */
#define AQ_MssIngressSaControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaThresholdLSW in AQ_MssIngressSaControlRegister_EUR */
#define AQ_MssIngressSaControlRegister_EUR_mssIngressSaThresholdLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaThresholdLSW in AQ_MssIngressSaControlRegister_EUR */
#define bits_AQ_MssIngressSaControlRegister_EUR_mssIngressSaThresholdLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaThresholdLSW in AQ_MssIngressSaControlRegister_EUR */
#define word_AQ_MssIngressSaControlRegister_EUR_mssIngressSaThresholdLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaThresholdMSW in AQ_MssIngressSaControlRegister_EUR */
#define AQ_MssIngressSaControlRegister_EUR_mssIngressSaThresholdMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaThresholdMSW in AQ_MssIngressSaControlRegister_EUR */
#define bits_AQ_MssIngressSaControlRegister_EUR_mssIngressSaThresholdMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaThresholdMSW in AQ_MssIngressSaControlRegister_EUR */
#define word_AQ_MssIngressSaControlRegister_EUR_mssIngressSaThresholdMSW u1.word_1

/*! \brief Base register address of structure AQ_MssIngressInterruptStatusRegister_EUR */
#define AQ_MssIngressInterruptStatusRegister_EUR_baseRegisterAddress 0x802E
/*! \brief MMD address of structure AQ_MssIngressInterruptStatusRegister_EUR */
#define AQ_MssIngressInterruptStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressIgpocMissInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define AQ_MssIngressInterruptStatusRegister_EUR_mssIngressIgpocMissInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressIgpocMissInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define bits_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressIgpocMissInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressIgpocMissInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define word_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressIgpocMissInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressTciE_cErrorInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define AQ_MssIngressInterruptStatusRegister_EUR_mssIngressTciE_cErrorInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressTciE_cErrorInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define bits_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressTciE_cErrorInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressTciE_cErrorInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define word_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressTciE_cErrorInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressEccErrorInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define AQ_MssIngressInterruptStatusRegister_EUR_mssIngressEccErrorInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressEccErrorInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define bits_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressEccErrorInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressEccErrorInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define word_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressEccErrorInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressMibSaturationInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define AQ_MssIngressInterruptStatusRegister_EUR_mssIngressMibSaturationInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressMibSaturationInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define bits_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressMibSaturationInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressMibSaturationInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define word_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressMibSaturationInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressReplayErrorInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define AQ_MssIngressInterruptStatusRegister_EUR_mssIngressReplayErrorInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressReplayErrorInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define bits_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressReplayErrorInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressReplayErrorInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define word_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressReplayErrorInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressIcvErrorInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define AQ_MssIngressInterruptStatusRegister_EUR_mssIngressIcvErrorInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressIcvErrorInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define bits_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressIcvErrorInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressIcvErrorInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define word_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressIcvErrorInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaThresholdExpiredInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define AQ_MssIngressInterruptStatusRegister_EUR_mssIngressSaThresholdExpiredInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaThresholdExpiredInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define bits_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressSaThresholdExpiredInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaThresholdExpiredInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define word_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressSaThresholdExpiredInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaExpiredInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define AQ_MssIngressInterruptStatusRegister_EUR_mssIngressSaExpiredInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaExpiredInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define bits_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressSaExpiredInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaExpiredInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define word_AQ_MssIngressInterruptStatusRegister_EUR_mssIngressSaExpiredInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssMasterIngressInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define AQ_MssIngressInterruptStatusRegister_EUR_mssMasterIngressInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssMasterIngressInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define bits_AQ_MssIngressInterruptStatusRegister_EUR_mssMasterIngressInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssMasterIngressInterrupt in AQ_MssIngressInterruptStatusRegister_EUR */
#define word_AQ_MssIngressInterruptStatusRegister_EUR_mssMasterIngressInterrupt u0.word_0

/*! \brief Base register address of structure AQ_MssIngressInterruptMaskRegister_EUR */
#define AQ_MssIngressInterruptMaskRegister_EUR_baseRegisterAddress 0x8030
/*! \brief MMD address of structure AQ_MssIngressInterruptMaskRegister_EUR */
#define AQ_MssIngressInterruptMaskRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressIgpocMissInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define AQ_MssIngressInterruptMaskRegister_EUR_mssIngressIgpocMissInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressIgpocMissInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define bits_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressIgpocMissInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressIgpocMissInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define word_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressIgpocMissInterruptEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressTciE_cErrorInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define AQ_MssIngressInterruptMaskRegister_EUR_mssIngressTciE_cErrorInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressTciE_cErrorInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define bits_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressTciE_cErrorInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressTciE_cErrorInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define word_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressTciE_cErrorInterruptEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressEccErrorInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define AQ_MssIngressInterruptMaskRegister_EUR_mssIngressEccErrorInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressEccErrorInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define bits_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressEccErrorInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressEccErrorInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define word_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressEccErrorInterruptEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressMibSaturationInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define AQ_MssIngressInterruptMaskRegister_EUR_mssIngressMibSaturationInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressMibSaturationInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define bits_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressMibSaturationInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressMibSaturationInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define word_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressMibSaturationInterruptEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressReplayErrorInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define AQ_MssIngressInterruptMaskRegister_EUR_mssIngressReplayErrorInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressReplayErrorInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define bits_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressReplayErrorInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressReplayErrorInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define word_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressReplayErrorInterruptEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressIcvErrorInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define AQ_MssIngressInterruptMaskRegister_EUR_mssIngressIcvErrorInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressIcvErrorInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define bits_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressIcvErrorInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressIcvErrorInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define word_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressIcvErrorInterruptEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaThresholdExpiredInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define AQ_MssIngressInterruptMaskRegister_EUR_mssIngressSaThresholdExpiredInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaThresholdExpiredInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define bits_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressSaThresholdExpiredInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaThresholdExpiredInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define word_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressSaThresholdExpiredInterruptEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaExpiredInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define AQ_MssIngressInterruptMaskRegister_EUR_mssIngressSaExpiredInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaExpiredInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define bits_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressSaExpiredInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaExpiredInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define word_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressSaExpiredInterruptEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressMasterInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define AQ_MssIngressInterruptMaskRegister_EUR_mssIngressMasterInterruptEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressMasterInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define bits_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressMasterInterruptEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressMasterInterruptEnable in AQ_MssIngressInterruptMaskRegister_EUR */
#define word_AQ_MssIngressInterruptMaskRegister_EUR_mssIngressMasterInterruptEnable u0.word_0

/*! \brief Base register address of structure AQ_MssIngressSaIcvErrorStatusRegister_EUR */
#define AQ_MssIngressSaIcvErrorStatusRegister_EUR_baseRegisterAddress 0x8032
/*! \brief MMD address of structure AQ_MssIngressSaIcvErrorStatusRegister_EUR */
#define AQ_MssIngressSaIcvErrorStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaIcvErrorLSW in AQ_MssIngressSaIcvErrorStatusRegister_EUR */
#define AQ_MssIngressSaIcvErrorStatusRegister_EUR_mssIngressSaIcvErrorLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaIcvErrorLSW in AQ_MssIngressSaIcvErrorStatusRegister_EUR */
#define bits_AQ_MssIngressSaIcvErrorStatusRegister_EUR_mssIngressSaIcvErrorLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaIcvErrorLSW in AQ_MssIngressSaIcvErrorStatusRegister_EUR */
#define word_AQ_MssIngressSaIcvErrorStatusRegister_EUR_mssIngressSaIcvErrorLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaIcvErrorMSW in AQ_MssIngressSaIcvErrorStatusRegister_EUR */
#define AQ_MssIngressSaIcvErrorStatusRegister_EUR_mssIngressSaIcvErrorMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaIcvErrorMSW in AQ_MssIngressSaIcvErrorStatusRegister_EUR */
#define bits_AQ_MssIngressSaIcvErrorStatusRegister_EUR_mssIngressSaIcvErrorMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaIcvErrorMSW in AQ_MssIngressSaIcvErrorStatusRegister_EUR */
#define word_AQ_MssIngressSaIcvErrorStatusRegister_EUR_mssIngressSaIcvErrorMSW u1.word_1

/*! \brief Base register address of structure AQ_MssIngressSaReplayErrorStatusRegister_EUR */
#define AQ_MssIngressSaReplayErrorStatusRegister_EUR_baseRegisterAddress 0x8034
/*! \brief MMD address of structure AQ_MssIngressSaReplayErrorStatusRegister_EUR */
#define AQ_MssIngressSaReplayErrorStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaReplayErrorLSW in AQ_MssIngressSaReplayErrorStatusRegister_EUR */
#define AQ_MssIngressSaReplayErrorStatusRegister_EUR_mssIngressSaReplayErrorLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaReplayErrorLSW in AQ_MssIngressSaReplayErrorStatusRegister_EUR */
#define bits_AQ_MssIngressSaReplayErrorStatusRegister_EUR_mssIngressSaReplayErrorLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaReplayErrorLSW in AQ_MssIngressSaReplayErrorStatusRegister_EUR */
#define word_AQ_MssIngressSaReplayErrorStatusRegister_EUR_mssIngressSaReplayErrorLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaReplayErrorMSW in AQ_MssIngressSaReplayErrorStatusRegister_EUR */
#define AQ_MssIngressSaReplayErrorStatusRegister_EUR_mssIngressSaReplayErrorMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaReplayErrorMSW in AQ_MssIngressSaReplayErrorStatusRegister_EUR */
#define bits_AQ_MssIngressSaReplayErrorStatusRegister_EUR_mssIngressSaReplayErrorMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaReplayErrorMSW in AQ_MssIngressSaReplayErrorStatusRegister_EUR */
#define word_AQ_MssIngressSaReplayErrorStatusRegister_EUR_mssIngressSaReplayErrorMSW u1.word_1

/*! \brief Base register address of structure AQ_MssIngressSaExpiredStatusRegister_EUR */
#define AQ_MssIngressSaExpiredStatusRegister_EUR_baseRegisterAddress 0x8036
/*! \brief MMD address of structure AQ_MssIngressSaExpiredStatusRegister_EUR */
#define AQ_MssIngressSaExpiredStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaExpiredLSW in AQ_MssIngressSaExpiredStatusRegister_EUR */
#define AQ_MssIngressSaExpiredStatusRegister_EUR_mssIngressSaExpiredLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaExpiredLSW in AQ_MssIngressSaExpiredStatusRegister_EUR */
#define bits_AQ_MssIngressSaExpiredStatusRegister_EUR_mssIngressSaExpiredLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaExpiredLSW in AQ_MssIngressSaExpiredStatusRegister_EUR */
#define word_AQ_MssIngressSaExpiredStatusRegister_EUR_mssIngressSaExpiredLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaExpiredMSW in AQ_MssIngressSaExpiredStatusRegister_EUR */
#define AQ_MssIngressSaExpiredStatusRegister_EUR_mssIngressSaExpiredMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaExpiredMSW in AQ_MssIngressSaExpiredStatusRegister_EUR */
#define bits_AQ_MssIngressSaExpiredStatusRegister_EUR_mssIngressSaExpiredMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaExpiredMSW in AQ_MssIngressSaExpiredStatusRegister_EUR */
#define word_AQ_MssIngressSaExpiredStatusRegister_EUR_mssIngressSaExpiredMSW u1.word_1

/*! \brief Base register address of structure AQ_MssIngressSaThresholdExpiredStatusRegister_EUR */
#define AQ_MssIngressSaThresholdExpiredStatusRegister_EUR_baseRegisterAddress 0x8038
/*! \brief MMD address of structure AQ_MssIngressSaThresholdExpiredStatusRegister_EUR */
#define AQ_MssIngressSaThresholdExpiredStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaThresholdExpiredLSW in AQ_MssIngressSaThresholdExpiredStatusRegister_EUR */
#define AQ_MssIngressSaThresholdExpiredStatusRegister_EUR_mssIngressSaThresholdExpiredLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaThresholdExpiredLSW in AQ_MssIngressSaThresholdExpiredStatusRegister_EUR */
#define bits_AQ_MssIngressSaThresholdExpiredStatusRegister_EUR_mssIngressSaThresholdExpiredLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaThresholdExpiredLSW in AQ_MssIngressSaThresholdExpiredStatusRegister_EUR */
#define word_AQ_MssIngressSaThresholdExpiredStatusRegister_EUR_mssIngressSaThresholdExpiredLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaThresholdExpiredMSW in AQ_MssIngressSaThresholdExpiredStatusRegister_EUR */
#define AQ_MssIngressSaThresholdExpiredStatusRegister_EUR_mssIngressSaThresholdExpiredMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaThresholdExpiredMSW in AQ_MssIngressSaThresholdExpiredStatusRegister_EUR */
#define bits_AQ_MssIngressSaThresholdExpiredStatusRegister_EUR_mssIngressSaThresholdExpiredMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaThresholdExpiredMSW in AQ_MssIngressSaThresholdExpiredStatusRegister_EUR */
#define word_AQ_MssIngressSaThresholdExpiredStatusRegister_EUR_mssIngressSaThresholdExpiredMSW u1.word_1

/*! \brief Base register address of structure AQ_MssIngressEccInterruptStatusRegister_EUR */
#define AQ_MssIngressEccInterruptStatusRegister_EUR_baseRegisterAddress 0x803A
/*! \brief MMD address of structure AQ_MssIngressEccInterruptStatusRegister_EUR */
#define AQ_MssIngressEccInterruptStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaEccErrorInterruptLSW in AQ_MssIngressEccInterruptStatusRegister_EUR */
#define AQ_MssIngressEccInterruptStatusRegister_EUR_mssIngressSaEccErrorInterruptLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaEccErrorInterruptLSW in AQ_MssIngressEccInterruptStatusRegister_EUR */
#define bits_AQ_MssIngressEccInterruptStatusRegister_EUR_mssIngressSaEccErrorInterruptLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaEccErrorInterruptLSW in AQ_MssIngressEccInterruptStatusRegister_EUR */
#define word_AQ_MssIngressEccInterruptStatusRegister_EUR_mssIngressSaEccErrorInterruptLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressSaEccErrorInterruptMSW in AQ_MssIngressEccInterruptStatusRegister_EUR */
#define AQ_MssIngressEccInterruptStatusRegister_EUR_mssIngressSaEccErrorInterruptMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressSaEccErrorInterruptMSW in AQ_MssIngressEccInterruptStatusRegister_EUR */
#define bits_AQ_MssIngressEccInterruptStatusRegister_EUR_mssIngressSaEccErrorInterruptMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressSaEccErrorInterruptMSW in AQ_MssIngressEccInterruptStatusRegister_EUR */
#define word_AQ_MssIngressEccInterruptStatusRegister_EUR_mssIngressSaEccErrorInterruptMSW u1.word_1

/*! \brief Base register address of structure AQ_MssIngressLutAddressControlRegister_EUR */
#define AQ_MssIngressLutAddressControlRegister_EUR_baseRegisterAddress 0x8080
/*! \brief MMD address of structure AQ_MssIngressLutAddressControlRegister_EUR */
#define AQ_MssIngressLutAddressControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutSelect in AQ_MssIngressLutAddressControlRegister_EUR */
#define AQ_MssIngressLutAddressControlRegister_EUR_mssIngressLutSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutSelect in AQ_MssIngressLutAddressControlRegister_EUR */
#define bits_AQ_MssIngressLutAddressControlRegister_EUR_mssIngressLutSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutSelect in AQ_MssIngressLutAddressControlRegister_EUR */
#define word_AQ_MssIngressLutAddressControlRegister_EUR_mssIngressLutSelect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutAddress in AQ_MssIngressLutAddressControlRegister_EUR */
#define AQ_MssIngressLutAddressControlRegister_EUR_mssIngressLutAddress 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutAddress in AQ_MssIngressLutAddressControlRegister_EUR */
#define bits_AQ_MssIngressLutAddressControlRegister_EUR_mssIngressLutAddress u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutAddress in AQ_MssIngressLutAddressControlRegister_EUR */
#define word_AQ_MssIngressLutAddressControlRegister_EUR_mssIngressLutAddress u0.word_0

/*! \brief Base register address of structure AQ_MssIngressLutControlRegister_EUR */
#define AQ_MssIngressLutControlRegister_EUR_baseRegisterAddress 0x8081
/*! \brief MMD address of structure AQ_MssIngressLutControlRegister_EUR */
#define AQ_MssIngressLutControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutWrite in AQ_MssIngressLutControlRegister_EUR */
#define AQ_MssIngressLutControlRegister_EUR_mssIngressLutWrite 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutWrite in AQ_MssIngressLutControlRegister_EUR */
#define bits_AQ_MssIngressLutControlRegister_EUR_mssIngressLutWrite u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutWrite in AQ_MssIngressLutControlRegister_EUR */
#define word_AQ_MssIngressLutControlRegister_EUR_mssIngressLutWrite u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutRead in AQ_MssIngressLutControlRegister_EUR */
#define AQ_MssIngressLutControlRegister_EUR_mssIngressLutRead 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutRead in AQ_MssIngressLutControlRegister_EUR */
#define bits_AQ_MssIngressLutControlRegister_EUR_mssIngressLutRead u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutRead in AQ_MssIngressLutControlRegister_EUR */
#define word_AQ_MssIngressLutControlRegister_EUR_mssIngressLutRead u0.word_0

/*! \brief Base register address of structure AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_baseRegisterAddress 0x80A0
/*! \brief MMD address of structure AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_0 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_0 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_0 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_1 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_1 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_1 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_2 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_2 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_2 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_2 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_3 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_3 3
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_3 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_3 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_3 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_3 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_4 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_4 4
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_4 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_4 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_4 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_4 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_5 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_5 5
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_5 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_5 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_5 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_5 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_6 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_6 6
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_6 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_6 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_6 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_6 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_7 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_7 7
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_7 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_7 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_7 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_7 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_8 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_8 8
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_8 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_8 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_8 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_8 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_9 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_9 9
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_9 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_9 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_9 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_9 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_10 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_10 10
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_10 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_10 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_10 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_10 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_11 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_11 11
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_11 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_11 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_11 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_11 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_12 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_12 12
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_12 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_12 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_12 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_12 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_13 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_13 13
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_13 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_13 u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_13 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_13 u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_14 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_14 14
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_14 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_14 u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_14 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_14 u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_15 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_15 15
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_15 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_15 u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_15 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_15 u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_16 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_16 16
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_16 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_16 u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_16 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_16 u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_17 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_17 17
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_17 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_17 u17.bits_17
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_17 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_17 u17.word_17
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_18 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_18 18
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_18 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_18 u18.bits_18
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_18 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_18 u18.word_18
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_19 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_19 19
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_19 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_19 u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_19 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_19 u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_20 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_20 20
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_20 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_20 u20.bits_20
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_20 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_20 u20.word_20
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_21 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_21 21
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_21 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_21 u21.bits_21
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_21 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_21 u21.word_21
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_22 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_22 22
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_22 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_22 u22.bits_22
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_22 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_22 u22.word_22
/*! \brief Preprocessor variable to relate field to word number in structure mssIngressLutData_23 in AQ_MssIngressLutDataControlRegister_EUR */
#define AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_23 23
/*! \brief Preprocessor variable to relate field to bit position in structure mssIngressLutData_23 in AQ_MssIngressLutDataControlRegister_EUR */
#define bits_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_23 u23.bits_23
/*! \brief Preprocessor variable to relate field to word position in structure mssIngressLutData_23 in AQ_MssIngressLutDataControlRegister_EUR */
#define word_AQ_MssIngressLutDataControlRegister_EUR_mssIngressLutData_23 u23.word_23

/*! \brief Base register address of structure AQ_MsmLineRevisionRegister_EUR */
#define AQ_MsmLineRevisionRegister_EUR_baseRegisterAddress 0x9000
/*! \brief MMD address of structure AQ_MsmLineRevisionRegister_EUR */
#define AQ_MsmLineRevisionRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineCoreRevision in AQ_MsmLineRevisionRegister_EUR */
#define AQ_MsmLineRevisionRegister_EUR_msmLineCoreRevision 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineCoreRevision in AQ_MsmLineRevisionRegister_EUR */
#define bits_AQ_MsmLineRevisionRegister_EUR_msmLineCoreRevision u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineCoreRevision in AQ_MsmLineRevisionRegister_EUR */
#define word_AQ_MsmLineRevisionRegister_EUR_msmLineCoreRevision u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineCoreVersion in AQ_MsmLineRevisionRegister_EUR */
#define AQ_MsmLineRevisionRegister_EUR_msmLineCoreVersion 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineCoreVersion in AQ_MsmLineRevisionRegister_EUR */
#define bits_AQ_MsmLineRevisionRegister_EUR_msmLineCoreVersion u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineCoreVersion in AQ_MsmLineRevisionRegister_EUR */
#define word_AQ_MsmLineRevisionRegister_EUR_msmLineCoreVersion u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineCustomerRevision in AQ_MsmLineRevisionRegister_EUR */
#define AQ_MsmLineRevisionRegister_EUR_msmLineCustomerRevision 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineCustomerRevision in AQ_MsmLineRevisionRegister_EUR */
#define bits_AQ_MsmLineRevisionRegister_EUR_msmLineCustomerRevision u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineCustomerRevision in AQ_MsmLineRevisionRegister_EUR */
#define word_AQ_MsmLineRevisionRegister_EUR_msmLineCustomerRevision u1.word_1

/*! \brief Base register address of structure AQ_MsmLineScratchpadRegister_EUR */
#define AQ_MsmLineScratchpadRegister_EUR_baseRegisterAddress 0x9002
/*! \brief MMD address of structure AQ_MsmLineScratchpadRegister_EUR */
#define AQ_MsmLineScratchpadRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineScratch_0 in AQ_MsmLineScratchpadRegister_EUR */
#define AQ_MsmLineScratchpadRegister_EUR_msmLineScratch_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineScratch_0 in AQ_MsmLineScratchpadRegister_EUR */
#define bits_AQ_MsmLineScratchpadRegister_EUR_msmLineScratch_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineScratch_0 in AQ_MsmLineScratchpadRegister_EUR */
#define word_AQ_MsmLineScratchpadRegister_EUR_msmLineScratch_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineScratch_1 in AQ_MsmLineScratchpadRegister_EUR */
#define AQ_MsmLineScratchpadRegister_EUR_msmLineScratch_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineScratch_1 in AQ_MsmLineScratchpadRegister_EUR */
#define bits_AQ_MsmLineScratchpadRegister_EUR_msmLineScratch_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineScratch_1 in AQ_MsmLineScratchpadRegister_EUR */
#define word_AQ_MsmLineScratchpadRegister_EUR_msmLineScratch_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_baseRegisterAddress 0x9004
/*! \brief MMD address of structure AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLinePhyTxEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLinePhyTxEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLinePhyTxEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLinePhyTxEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLinePhyTxEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLinePhyTxEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxErrorDiscard in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineRxErrorDiscard 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxErrorDiscard in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineRxErrorDiscard u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxErrorDiscard in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineRxErrorDiscard u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineControlFrameEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineControlFrameEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineControlFrameEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineControlFrameEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineControlFrameEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineControlFrameEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSoftReset in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineSoftReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSoftReset in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineSoftReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSoftReset in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineSoftReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxPadEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineTxPadEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxPadEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineTxPadEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxPadEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineTxPadEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxCrcAppend in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineTxCrcAppend 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxCrcAppend in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineTxCrcAppend u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxCrcAppend in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineTxCrcAppend u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxAddressInsertEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineTxAddressInsertEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxAddressInsertEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineTxAddressInsertEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxAddressInsertEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineTxAddressInsertEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLinePauseIgnore in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLinePauseIgnore 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLinePauseIgnore in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLinePauseIgnore u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLinePauseIgnore in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLinePauseIgnore u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLinePauseForward in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLinePauseForward 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLinePauseForward in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLinePauseForward u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLinePauseForward in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLinePauseForward u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineCrcForward in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineCrcForward 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineCrcForward in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineCrcForward u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineCrcForward in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineCrcForward u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLinePadEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLinePadEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLinePadEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLinePadEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLinePadEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLinePadEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLinePromiscuousMode in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLinePromiscuousMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLinePromiscuousMode in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLinePromiscuousMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLinePromiscuousMode in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLinePromiscuousMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineWanMode in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineWanMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineWanMode in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineWanMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineWanMode in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineWanMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineRxEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineRxEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineRxEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineTxEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineTxEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineTxEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineStatisticCounterReset in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineStatisticCounterReset 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineStatisticCounterReset in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineStatisticCounterReset u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineStatisticCounterReset in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineStatisticCounterReset u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmLineCrcCorruptionDisable in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineCrcCorruptionDisable 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineCrcCorruptionDisable in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineCrcCorruptionDisable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineCrcCorruptionDisable in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineCrcCorruptionDisable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxLowPowerIdleEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineTxLowPowerIdleEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxLowPowerIdleEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineTxLowPowerIdleEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxLowPowerIdleEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineTxLowPowerIdleEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSfdCheckDisable in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineSfdCheckDisable 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSfdCheckDisable in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineSfdCheckDisable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSfdCheckDisable in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineSfdCheckDisable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmLinePriorityFlowControlEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLinePriorityFlowControlEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLinePriorityFlowControlEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLinePriorityFlowControlEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLinePriorityFlowControlEnable in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLinePriorityFlowControlEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmLineIdleColumnCountExtend in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineIdleColumnCountExtend 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineIdleColumnCountExtend in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineIdleColumnCountExtend u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineIdleColumnCountExtend in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineIdleColumnCountExtend u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmLineLengthCheckDisable in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineLengthCheckDisable 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineLengthCheckDisable in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineLengthCheckDisable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineLengthCheckDisable in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineLengthCheckDisable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmLineForceSendIdle in AQ_MsmLineGeneralControlRegister_EUR */
#define AQ_MsmLineGeneralControlRegister_EUR_msmLineForceSendIdle 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineForceSendIdle in AQ_MsmLineGeneralControlRegister_EUR */
#define bits_AQ_MsmLineGeneralControlRegister_EUR_msmLineForceSendIdle u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineForceSendIdle in AQ_MsmLineGeneralControlRegister_EUR */
#define word_AQ_MsmLineGeneralControlRegister_EUR_msmLineForceSendIdle u1.word_1

/*! \brief Base register address of structure AQ_MsmLineAddressRegister_EUR */
#define AQ_MsmLineAddressRegister_EUR_baseRegisterAddress 0x9006
/*! \brief MMD address of structure AQ_MsmLineAddressRegister_EUR */
#define AQ_MsmLineAddressRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineAddress_0 in AQ_MsmLineAddressRegister_EUR */
#define AQ_MsmLineAddressRegister_EUR_msmLineAddress_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineAddress_0 in AQ_MsmLineAddressRegister_EUR */
#define bits_AQ_MsmLineAddressRegister_EUR_msmLineAddress_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineAddress_0 in AQ_MsmLineAddressRegister_EUR */
#define word_AQ_MsmLineAddressRegister_EUR_msmLineAddress_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineAddress_1 in AQ_MsmLineAddressRegister_EUR */
#define AQ_MsmLineAddressRegister_EUR_msmLineAddress_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineAddress_1 in AQ_MsmLineAddressRegister_EUR */
#define bits_AQ_MsmLineAddressRegister_EUR_msmLineAddress_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineAddress_1 in AQ_MsmLineAddressRegister_EUR */
#define word_AQ_MsmLineAddressRegister_EUR_msmLineAddress_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmLineAddress_2 in AQ_MsmLineAddressRegister_EUR */
#define AQ_MsmLineAddressRegister_EUR_msmLineAddress_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineAddress_2 in AQ_MsmLineAddressRegister_EUR */
#define bits_AQ_MsmLineAddressRegister_EUR_msmLineAddress_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmLineAddress_2 in AQ_MsmLineAddressRegister_EUR */
#define word_AQ_MsmLineAddressRegister_EUR_msmLineAddress_2 u2.word_2

/*! \brief Base register address of structure AQ_MsmLineFrameControlRegister_EUR */
#define AQ_MsmLineFrameControlRegister_EUR_baseRegisterAddress 0x900A
/*! \brief MMD address of structure AQ_MsmLineFrameControlRegister_EUR */
#define AQ_MsmLineFrameControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMaximumFrameLength in AQ_MsmLineFrameControlRegister_EUR */
#define AQ_MsmLineFrameControlRegister_EUR_msmLineMaximumFrameLength 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMaximumFrameLength in AQ_MsmLineFrameControlRegister_EUR */
#define bits_AQ_MsmLineFrameControlRegister_EUR_msmLineMaximumFrameLength u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMaximumFrameLength in AQ_MsmLineFrameControlRegister_EUR */
#define word_AQ_MsmLineFrameControlRegister_EUR_msmLineMaximumFrameLength u0.word_0

/*! \brief Base register address of structure AQ_MsmLineFifoControlRegister_EUR */
#define AQ_MsmLineFifoControlRegister_EUR_baseRegisterAddress 0x900E
/*! \brief MMD address of structure AQ_MsmLineFifoControlRegister_EUR */
#define AQ_MsmLineFifoControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxFifoFullThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define AQ_MsmLineFifoControlRegister_EUR_msmLineRxFifoFullThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxFifoFullThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define bits_AQ_MsmLineFifoControlRegister_EUR_msmLineRxFifoFullThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxFifoFullThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define word_AQ_MsmLineFifoControlRegister_EUR_msmLineRxFifoFullThreshold u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxFifoEmptyThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define AQ_MsmLineFifoControlRegister_EUR_msmLineRxFifoEmptyThreshold 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxFifoEmptyThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define bits_AQ_MsmLineFifoControlRegister_EUR_msmLineRxFifoEmptyThreshold u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxFifoEmptyThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define word_AQ_MsmLineFifoControlRegister_EUR_msmLineRxFifoEmptyThreshold u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxFifoFullThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define AQ_MsmLineFifoControlRegister_EUR_msmLineTxFifoFullThreshold 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxFifoFullThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define bits_AQ_MsmLineFifoControlRegister_EUR_msmLineTxFifoFullThreshold u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxFifoFullThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define word_AQ_MsmLineFifoControlRegister_EUR_msmLineTxFifoFullThreshold u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxFifoEmptyThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define AQ_MsmLineFifoControlRegister_EUR_msmLineTxFifoEmptyThreshold 3
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxFifoEmptyThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define bits_AQ_MsmLineFifoControlRegister_EUR_msmLineTxFifoEmptyThreshold u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxFifoEmptyThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define word_AQ_MsmLineFifoControlRegister_EUR_msmLineTxFifoEmptyThreshold u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxFifoAlmostFullThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define AQ_MsmLineFifoControlRegister_EUR_msmLineRxFifoAlmostFullThreshold 4
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxFifoAlmostFullThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define bits_AQ_MsmLineFifoControlRegister_EUR_msmLineRxFifoAlmostFullThreshold u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxFifoAlmostFullThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define word_AQ_MsmLineFifoControlRegister_EUR_msmLineRxFifoAlmostFullThreshold u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxFifoAlmostEmptyThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define AQ_MsmLineFifoControlRegister_EUR_msmLineRxFifoAlmostEmptyThreshold 5
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxFifoAlmostEmptyThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define bits_AQ_MsmLineFifoControlRegister_EUR_msmLineRxFifoAlmostEmptyThreshold u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxFifoAlmostEmptyThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define word_AQ_MsmLineFifoControlRegister_EUR_msmLineRxFifoAlmostEmptyThreshold u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxFifoAlmostFullThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define AQ_MsmLineFifoControlRegister_EUR_msmLineTxFifoAlmostFullThreshold 6
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxFifoAlmostFullThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define bits_AQ_MsmLineFifoControlRegister_EUR_msmLineTxFifoAlmostFullThreshold u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxFifoAlmostFullThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define word_AQ_MsmLineFifoControlRegister_EUR_msmLineTxFifoAlmostFullThreshold u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxFifoAlmostEmptyThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define AQ_MsmLineFifoControlRegister_EUR_msmLineTxFifoAlmostEmptyThreshold 7
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxFifoAlmostEmptyThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define bits_AQ_MsmLineFifoControlRegister_EUR_msmLineTxFifoAlmostEmptyThreshold u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxFifoAlmostEmptyThreshold in AQ_MsmLineFifoControlRegister_EUR */
#define word_AQ_MsmLineFifoControlRegister_EUR_msmLineTxFifoAlmostEmptyThreshold u7.word_7

/*! \brief Base register address of structure AQ_MsmLineHashControlRegister_EUR */
#define AQ_MsmLineHashControlRegister_EUR_baseRegisterAddress 0x9016
/*! \brief MMD address of structure AQ_MsmLineHashControlRegister_EUR */
#define AQ_MsmLineHashControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMulticastEnable in AQ_MsmLineHashControlRegister_EUR */
#define AQ_MsmLineHashControlRegister_EUR_msmLineMulticastEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMulticastEnable in AQ_MsmLineHashControlRegister_EUR */
#define bits_AQ_MsmLineHashControlRegister_EUR_msmLineMulticastEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMulticastEnable in AQ_MsmLineHashControlRegister_EUR */
#define word_AQ_MsmLineHashControlRegister_EUR_msmLineMulticastEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineHashTable in AQ_MsmLineHashControlRegister_EUR */
#define AQ_MsmLineHashControlRegister_EUR_msmLineHashTable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineHashTable in AQ_MsmLineHashControlRegister_EUR */
#define bits_AQ_MsmLineHashControlRegister_EUR_msmLineHashTable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineHashTable in AQ_MsmLineHashControlRegister_EUR */
#define word_AQ_MsmLineHashControlRegister_EUR_msmLineHashTable u0.word_0

/*! \brief Base register address of structure AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_baseRegisterAddress 0x9018
/*! \brief MMD address of structure AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMdioClockDividerConfiguration in AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_msmLineMdioClockDividerConfiguration 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMdioClockDividerConfiguration in AQ_MsmLineMdioControlRegister_EUR */
#define bits_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioClockDividerConfiguration u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMdioClockDividerConfiguration in AQ_MsmLineMdioControlRegister_EUR */
#define word_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioClockDividerConfiguration u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMdioClause_45Enable in AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_msmLineMdioClause_45Enable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMdioClause_45Enable in AQ_MsmLineMdioControlRegister_EUR */
#define bits_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioClause_45Enable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMdioClause_45Enable in AQ_MsmLineMdioControlRegister_EUR */
#define word_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioClause_45Enable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMdioHoldTimeConfiguration in AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_msmLineMdioHoldTimeConfiguration 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMdioHoldTimeConfiguration in AQ_MsmLineMdioControlRegister_EUR */
#define bits_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioHoldTimeConfiguration u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMdioHoldTimeConfiguration in AQ_MsmLineMdioControlRegister_EUR */
#define word_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioHoldTimeConfiguration u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMdioReadError in AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_msmLineMdioReadError 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMdioReadError in AQ_MsmLineMdioControlRegister_EUR */
#define bits_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioReadError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMdioReadError in AQ_MsmLineMdioControlRegister_EUR */
#define word_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioReadError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMdioBusy_0 in AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_msmLineMdioBusy_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMdioBusy_0 in AQ_MsmLineMdioControlRegister_EUR */
#define bits_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioBusy_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMdioBusy_0 in AQ_MsmLineMdioControlRegister_EUR */
#define word_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioBusy_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMdioBusy_1 in AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_msmLineMdioBusy_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMdioBusy_1 in AQ_MsmLineMdioControlRegister_EUR */
#define bits_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioBusy_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMdioBusy_1 in AQ_MsmLineMdioControlRegister_EUR */
#define word_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioBusy_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMdioRead in AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_msmLineMdioRead 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMdioRead in AQ_MsmLineMdioControlRegister_EUR */
#define bits_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioRead u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMdioRead in AQ_MsmLineMdioControlRegister_EUR */
#define word_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioRead u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMdioReadAddressPostIncrement in AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_msmLineMdioReadAddressPostIncrement 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMdioReadAddressPostIncrement in AQ_MsmLineMdioControlRegister_EUR */
#define bits_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioReadAddressPostIncrement u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMdioReadAddressPostIncrement in AQ_MsmLineMdioControlRegister_EUR */
#define word_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioReadAddressPostIncrement u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMdioPortAddress in AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_msmLineMdioPortAddress 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMdioPortAddress in AQ_MsmLineMdioControlRegister_EUR */
#define bits_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioPortAddress u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMdioPortAddress in AQ_MsmLineMdioControlRegister_EUR */
#define word_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioPortAddress u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMdioDeviceAddress in AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_msmLineMdioDeviceAddress 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMdioDeviceAddress in AQ_MsmLineMdioControlRegister_EUR */
#define bits_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioDeviceAddress u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMdioDeviceAddress in AQ_MsmLineMdioControlRegister_EUR */
#define word_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioDeviceAddress u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMdioData in AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_msmLineMdioData 4
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMdioData in AQ_MsmLineMdioControlRegister_EUR */
#define bits_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioData u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMdioData in AQ_MsmLineMdioControlRegister_EUR */
#define word_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioData u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure msmLineMdioRegisterAddress in AQ_MsmLineMdioControlRegister_EUR */
#define AQ_MsmLineMdioControlRegister_EUR_msmLineMdioRegisterAddress 6
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineMdioRegisterAddress in AQ_MsmLineMdioControlRegister_EUR */
#define bits_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioRegisterAddress u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure msmLineMdioRegisterAddress in AQ_MsmLineMdioControlRegister_EUR */
#define word_AQ_MsmLineMdioControlRegister_EUR_msmLineMdioRegisterAddress u6.word_6

/*! \brief Base register address of structure AQ_MsmLineGeneralStatusRegister_EUR */
#define AQ_MsmLineGeneralStatusRegister_EUR_baseRegisterAddress 0x9020
/*! \brief MMD address of structure AQ_MsmLineGeneralStatusRegister_EUR */
#define AQ_MsmLineGeneralStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxFifoEmpty in AQ_MsmLineGeneralStatusRegister_EUR */
#define AQ_MsmLineGeneralStatusRegister_EUR_msmLineTxFifoEmpty 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxFifoEmpty in AQ_MsmLineGeneralStatusRegister_EUR */
#define bits_AQ_MsmLineGeneralStatusRegister_EUR_msmLineTxFifoEmpty u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxFifoEmpty in AQ_MsmLineGeneralStatusRegister_EUR */
#define word_AQ_MsmLineGeneralStatusRegister_EUR_msmLineTxFifoEmpty u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxLowPowerIdle in AQ_MsmLineGeneralStatusRegister_EUR */
#define AQ_MsmLineGeneralStatusRegister_EUR_msmLineRxLowPowerIdle 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxLowPowerIdle in AQ_MsmLineGeneralStatusRegister_EUR */
#define bits_AQ_MsmLineGeneralStatusRegister_EUR_msmLineRxLowPowerIdle u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxLowPowerIdle in AQ_MsmLineGeneralStatusRegister_EUR */
#define word_AQ_MsmLineGeneralStatusRegister_EUR_msmLineRxLowPowerIdle u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTimestampAvailable in AQ_MsmLineGeneralStatusRegister_EUR */
#define AQ_MsmLineGeneralStatusRegister_EUR_msmLineTimestampAvailable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTimestampAvailable in AQ_MsmLineGeneralStatusRegister_EUR */
#define bits_AQ_MsmLineGeneralStatusRegister_EUR_msmLineTimestampAvailable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTimestampAvailable in AQ_MsmLineGeneralStatusRegister_EUR */
#define word_AQ_MsmLineGeneralStatusRegister_EUR_msmLineTimestampAvailable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLinePhyLossOfSignal in AQ_MsmLineGeneralStatusRegister_EUR */
#define AQ_MsmLineGeneralStatusRegister_EUR_msmLinePhyLossOfSignal 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLinePhyLossOfSignal in AQ_MsmLineGeneralStatusRegister_EUR */
#define bits_AQ_MsmLineGeneralStatusRegister_EUR_msmLinePhyLossOfSignal u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLinePhyLossOfSignal in AQ_MsmLineGeneralStatusRegister_EUR */
#define word_AQ_MsmLineGeneralStatusRegister_EUR_msmLinePhyLossOfSignal u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxRemoteFault in AQ_MsmLineGeneralStatusRegister_EUR */
#define AQ_MsmLineGeneralStatusRegister_EUR_msmLineRxRemoteFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxRemoteFault in AQ_MsmLineGeneralStatusRegister_EUR */
#define bits_AQ_MsmLineGeneralStatusRegister_EUR_msmLineRxRemoteFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxRemoteFault in AQ_MsmLineGeneralStatusRegister_EUR */
#define word_AQ_MsmLineGeneralStatusRegister_EUR_msmLineRxRemoteFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxLocalFault in AQ_MsmLineGeneralStatusRegister_EUR */
#define AQ_MsmLineGeneralStatusRegister_EUR_msmLineRxLocalFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxLocalFault in AQ_MsmLineGeneralStatusRegister_EUR */
#define bits_AQ_MsmLineGeneralStatusRegister_EUR_msmLineRxLocalFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxLocalFault in AQ_MsmLineGeneralStatusRegister_EUR */
#define word_AQ_MsmLineGeneralStatusRegister_EUR_msmLineRxLocalFault u0.word_0

/*! \brief Base register address of structure AQ_MsmLineTxIpgControlRegister_EUR */
#define AQ_MsmLineTxIpgControlRegister_EUR_baseRegisterAddress 0x9022
/*! \brief MMD address of structure AQ_MsmLineTxIpgControlRegister_EUR */
#define AQ_MsmLineTxIpgControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxIpgLength in AQ_MsmLineTxIpgControlRegister_EUR */
#define AQ_MsmLineTxIpgControlRegister_EUR_msmLineTxIpgLength 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxIpgLength in AQ_MsmLineTxIpgControlRegister_EUR */
#define bits_AQ_MsmLineTxIpgControlRegister_EUR_msmLineTxIpgLength u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxIpgLength in AQ_MsmLineTxIpgControlRegister_EUR */
#define word_AQ_MsmLineTxIpgControlRegister_EUR_msmLineTxIpgLength u0.word_0

/*! \brief Base register address of structure AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_baseRegisterAddress 0x902A
/*! \brief MMD address of structure AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_0PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_0PauseQuanta 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_0PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_0PauseQuanta u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_0PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_0PauseQuanta u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_1PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_1PauseQuanta 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_1PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_1PauseQuanta u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_1PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_1PauseQuanta u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_2PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_2PauseQuanta 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_2PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_2PauseQuanta u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_2PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_2PauseQuanta u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_3PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_3PauseQuanta 3
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_3PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_3PauseQuanta u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_3PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_3PauseQuanta u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_4PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_4PauseQuanta 4
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_4PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_4PauseQuanta u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_4PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_4PauseQuanta u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_5PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_5PauseQuanta 5
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_5PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_5PauseQuanta u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_5PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_5PauseQuanta u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_6PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_6PauseQuanta 6
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_6PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_6PauseQuanta u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_6PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_6PauseQuanta u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_7PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_7PauseQuanta 7
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_7PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_7PauseQuanta u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_7PauseQuanta in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_7PauseQuanta u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_0PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_0PauseQuantaThreshold 8
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_0PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_0PauseQuantaThreshold u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_0PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_0PauseQuantaThreshold u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_1PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_1PauseQuantaThreshold 9
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_1PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_1PauseQuantaThreshold u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_1PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_1PauseQuantaThreshold u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_2PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_2PauseQuantaThreshold 10
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_2PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_2PauseQuantaThreshold u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_2PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_2PauseQuantaThreshold u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_3PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_3PauseQuantaThreshold 11
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_3PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_3PauseQuantaThreshold u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_3PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_3PauseQuantaThreshold u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_4PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_4PauseQuantaThreshold 12
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_4PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_4PauseQuantaThreshold u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_4PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_4PauseQuantaThreshold u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_5PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_5PauseQuantaThreshold 13
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_5PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_5PauseQuantaThreshold u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_5PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_5PauseQuantaThreshold u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_6PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_6PauseQuantaThreshold 14
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_6PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_6PauseQuantaThreshold u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_6PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_6PauseQuantaThreshold u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure msmLineClass_7PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define AQ_MsmLinePauseControlRegister_EUR_msmLineClass_7PauseQuantaThreshold 15
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineClass_7PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define bits_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_7PauseQuantaThreshold u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure msmLineClass_7PauseQuantaThreshold in AQ_MsmLinePauseControlRegister_EUR */
#define word_AQ_MsmLinePauseControlRegister_EUR_msmLineClass_7PauseQuantaThreshold u15.word_15

/*! \brief Base register address of structure AQ_MsmLinePauseStatusRegister_EUR */
#define AQ_MsmLinePauseStatusRegister_EUR_baseRegisterAddress 0x903A
/*! \brief MMD address of structure AQ_MsmLinePauseStatusRegister_EUR */
#define AQ_MsmLinePauseStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLinePauseStatus in AQ_MsmLinePauseStatusRegister_EUR */
#define AQ_MsmLinePauseStatusRegister_EUR_msmLinePauseStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLinePauseStatus in AQ_MsmLinePauseStatusRegister_EUR */
#define bits_AQ_MsmLinePauseStatusRegister_EUR_msmLinePauseStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLinePauseStatus in AQ_MsmLinePauseStatusRegister_EUR */
#define word_AQ_MsmLinePauseStatusRegister_EUR_msmLinePauseStatus u0.word_0

/*! \brief Base register address of structure AQ_MsmLineTimeStampStatusRegister_EUR */
#define AQ_MsmLineTimeStampStatusRegister_EUR_baseRegisterAddress 0x903E
/*! \brief MMD address of structure AQ_MsmLineTimeStampStatusRegister_EUR */
#define AQ_MsmLineTimeStampStatusRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTimestampStatus_0 in AQ_MsmLineTimeStampStatusRegister_EUR */
#define AQ_MsmLineTimeStampStatusRegister_EUR_msmLineTimestampStatus_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTimestampStatus_0 in AQ_MsmLineTimeStampStatusRegister_EUR */
#define bits_AQ_MsmLineTimeStampStatusRegister_EUR_msmLineTimestampStatus_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTimestampStatus_0 in AQ_MsmLineTimeStampStatusRegister_EUR */
#define word_AQ_MsmLineTimeStampStatusRegister_EUR_msmLineTimestampStatus_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTimestampStatus_1 in AQ_MsmLineTimeStampStatusRegister_EUR */
#define AQ_MsmLineTimeStampStatusRegister_EUR_msmLineTimestampStatus_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTimestampStatus_1 in AQ_MsmLineTimeStampStatusRegister_EUR */
#define bits_AQ_MsmLineTimeStampStatusRegister_EUR_msmLineTimestampStatus_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTimestampStatus_1 in AQ_MsmLineTimeStampStatusRegister_EUR */
#define word_AQ_MsmLineTimeStampStatusRegister_EUR_msmLineTimestampStatus_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineTxGoodFramesCounterRegister_EUR */
#define AQ_MsmLineTxGoodFramesCounterRegister_EUR_baseRegisterAddress 0x9040
/*! \brief MMD address of structure AQ_MsmLineTxGoodFramesCounterRegister_EUR */
#define AQ_MsmLineTxGoodFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxGoodFramesCounter_0 in AQ_MsmLineTxGoodFramesCounterRegister_EUR */
#define AQ_MsmLineTxGoodFramesCounterRegister_EUR_msmLineTxGoodFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxGoodFramesCounter_0 in AQ_MsmLineTxGoodFramesCounterRegister_EUR */
#define bits_AQ_MsmLineTxGoodFramesCounterRegister_EUR_msmLineTxGoodFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxGoodFramesCounter_0 in AQ_MsmLineTxGoodFramesCounterRegister_EUR */
#define word_AQ_MsmLineTxGoodFramesCounterRegister_EUR_msmLineTxGoodFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxGoodFramesCounter_1 in AQ_MsmLineTxGoodFramesCounterRegister_EUR */
#define AQ_MsmLineTxGoodFramesCounterRegister_EUR_msmLineTxGoodFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxGoodFramesCounter_1 in AQ_MsmLineTxGoodFramesCounterRegister_EUR */
#define bits_AQ_MsmLineTxGoodFramesCounterRegister_EUR_msmLineTxGoodFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxGoodFramesCounter_1 in AQ_MsmLineTxGoodFramesCounterRegister_EUR */
#define word_AQ_MsmLineTxGoodFramesCounterRegister_EUR_msmLineTxGoodFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineRxGoodFramesCounterRegister_EUR */
#define AQ_MsmLineRxGoodFramesCounterRegister_EUR_baseRegisterAddress 0x9044
/*! \brief MMD address of structure AQ_MsmLineRxGoodFramesCounterRegister_EUR */
#define AQ_MsmLineRxGoodFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxGoodFramesCounter_0 in AQ_MsmLineRxGoodFramesCounterRegister_EUR */
#define AQ_MsmLineRxGoodFramesCounterRegister_EUR_msmLineRxGoodFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxGoodFramesCounter_0 in AQ_MsmLineRxGoodFramesCounterRegister_EUR */
#define bits_AQ_MsmLineRxGoodFramesCounterRegister_EUR_msmLineRxGoodFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxGoodFramesCounter_0 in AQ_MsmLineRxGoodFramesCounterRegister_EUR */
#define word_AQ_MsmLineRxGoodFramesCounterRegister_EUR_msmLineRxGoodFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxGoodFramesCounter_1 in AQ_MsmLineRxGoodFramesCounterRegister_EUR */
#define AQ_MsmLineRxGoodFramesCounterRegister_EUR_msmLineRxGoodFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxGoodFramesCounter_1 in AQ_MsmLineRxGoodFramesCounterRegister_EUR */
#define bits_AQ_MsmLineRxGoodFramesCounterRegister_EUR_msmLineRxGoodFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxGoodFramesCounter_1 in AQ_MsmLineRxGoodFramesCounterRegister_EUR */
#define word_AQ_MsmLineRxGoodFramesCounterRegister_EUR_msmLineRxGoodFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineRxFcsErrorsCounterRegister_EUR */
#define AQ_MsmLineRxFcsErrorsCounterRegister_EUR_baseRegisterAddress 0x9048
/*! \brief MMD address of structure AQ_MsmLineRxFcsErrorsCounterRegister_EUR */
#define AQ_MsmLineRxFcsErrorsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineFcsErrorCounter_0 in AQ_MsmLineRxFcsErrorsCounterRegister_EUR */
#define AQ_MsmLineRxFcsErrorsCounterRegister_EUR_msmLineFcsErrorCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineFcsErrorCounter_0 in AQ_MsmLineRxFcsErrorsCounterRegister_EUR */
#define bits_AQ_MsmLineRxFcsErrorsCounterRegister_EUR_msmLineFcsErrorCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineFcsErrorCounter_0 in AQ_MsmLineRxFcsErrorsCounterRegister_EUR */
#define word_AQ_MsmLineRxFcsErrorsCounterRegister_EUR_msmLineFcsErrorCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineFcsErrorCounter_1 in AQ_MsmLineRxFcsErrorsCounterRegister_EUR */
#define AQ_MsmLineRxFcsErrorsCounterRegister_EUR_msmLineFcsErrorCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineFcsErrorCounter_1 in AQ_MsmLineRxFcsErrorsCounterRegister_EUR */
#define bits_AQ_MsmLineRxFcsErrorsCounterRegister_EUR_msmLineFcsErrorCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineFcsErrorCounter_1 in AQ_MsmLineRxFcsErrorsCounterRegister_EUR */
#define word_AQ_MsmLineRxFcsErrorsCounterRegister_EUR_msmLineFcsErrorCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR */
#define AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR_baseRegisterAddress 0x904C
/*! \brief MMD address of structure AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR */
#define AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineAlignmentErrorCounter_0 in AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR */
#define AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR_msmLineAlignmentErrorCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineAlignmentErrorCounter_0 in AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR */
#define bits_AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR_msmLineAlignmentErrorCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineAlignmentErrorCounter_0 in AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR */
#define word_AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR_msmLineAlignmentErrorCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineAlignmentErrorCounter_1 in AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR */
#define AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR_msmLineAlignmentErrorCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineAlignmentErrorCounter_1 in AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR */
#define bits_AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR_msmLineAlignmentErrorCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineAlignmentErrorCounter_1 in AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR */
#define word_AQ_MsmLineRxAlignmentErrorsCounterRegister_EUR_msmLineAlignmentErrorCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineTxPauseFramesCounterRegister_EUR */
#define AQ_MsmLineTxPauseFramesCounterRegister_EUR_baseRegisterAddress 0x9050
/*! \brief MMD address of structure AQ_MsmLineTxPauseFramesCounterRegister_EUR */
#define AQ_MsmLineTxPauseFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxPauseFramesCounter_0 in AQ_MsmLineTxPauseFramesCounterRegister_EUR */
#define AQ_MsmLineTxPauseFramesCounterRegister_EUR_msmLineTxPauseFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxPauseFramesCounter_0 in AQ_MsmLineTxPauseFramesCounterRegister_EUR */
#define bits_AQ_MsmLineTxPauseFramesCounterRegister_EUR_msmLineTxPauseFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxPauseFramesCounter_0 in AQ_MsmLineTxPauseFramesCounterRegister_EUR */
#define word_AQ_MsmLineTxPauseFramesCounterRegister_EUR_msmLineTxPauseFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxPauseFramesCounter_1 in AQ_MsmLineTxPauseFramesCounterRegister_EUR */
#define AQ_MsmLineTxPauseFramesCounterRegister_EUR_msmLineTxPauseFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxPauseFramesCounter_1 in AQ_MsmLineTxPauseFramesCounterRegister_EUR */
#define bits_AQ_MsmLineTxPauseFramesCounterRegister_EUR_msmLineTxPauseFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxPauseFramesCounter_1 in AQ_MsmLineTxPauseFramesCounterRegister_EUR */
#define word_AQ_MsmLineTxPauseFramesCounterRegister_EUR_msmLineTxPauseFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineRxPauseFramesCounterRegister_EUR */
#define AQ_MsmLineRxPauseFramesCounterRegister_EUR_baseRegisterAddress 0x9054
/*! \brief MMD address of structure AQ_MsmLineRxPauseFramesCounterRegister_EUR */
#define AQ_MsmLineRxPauseFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxPauseFramesCounter_0 in AQ_MsmLineRxPauseFramesCounterRegister_EUR */
#define AQ_MsmLineRxPauseFramesCounterRegister_EUR_msmLineRxPauseFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxPauseFramesCounter_0 in AQ_MsmLineRxPauseFramesCounterRegister_EUR */
#define bits_AQ_MsmLineRxPauseFramesCounterRegister_EUR_msmLineRxPauseFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxPauseFramesCounter_0 in AQ_MsmLineRxPauseFramesCounterRegister_EUR */
#define word_AQ_MsmLineRxPauseFramesCounterRegister_EUR_msmLineRxPauseFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxPauseFramesCounter_1 in AQ_MsmLineRxPauseFramesCounterRegister_EUR */
#define AQ_MsmLineRxPauseFramesCounterRegister_EUR_msmLineRxPauseFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxPauseFramesCounter_1 in AQ_MsmLineRxPauseFramesCounterRegister_EUR */
#define bits_AQ_MsmLineRxPauseFramesCounterRegister_EUR_msmLineRxPauseFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxPauseFramesCounter_1 in AQ_MsmLineRxPauseFramesCounterRegister_EUR */
#define word_AQ_MsmLineRxPauseFramesCounterRegister_EUR_msmLineRxPauseFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineRxTooLongErrorsCounterRegister_EUR */
#define AQ_MsmLineRxTooLongErrorsCounterRegister_EUR_baseRegisterAddress 0x9058
/*! \brief MMD address of structure AQ_MsmLineRxTooLongErrorsCounterRegister_EUR */
#define AQ_MsmLineRxTooLongErrorsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxTooLongErrorsCounter_0 in AQ_MsmLineRxTooLongErrorsCounterRegister_EUR */
#define AQ_MsmLineRxTooLongErrorsCounterRegister_EUR_msmLineRxTooLongErrorsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxTooLongErrorsCounter_0 in AQ_MsmLineRxTooLongErrorsCounterRegister_EUR */
#define bits_AQ_MsmLineRxTooLongErrorsCounterRegister_EUR_msmLineRxTooLongErrorsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxTooLongErrorsCounter_0 in AQ_MsmLineRxTooLongErrorsCounterRegister_EUR */
#define word_AQ_MsmLineRxTooLongErrorsCounterRegister_EUR_msmLineRxTooLongErrorsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxTooLongErrorsCounter_1 in AQ_MsmLineRxTooLongErrorsCounterRegister_EUR */
#define AQ_MsmLineRxTooLongErrorsCounterRegister_EUR_msmLineRxTooLongErrorsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxTooLongErrorsCounter_1 in AQ_MsmLineRxTooLongErrorsCounterRegister_EUR */
#define bits_AQ_MsmLineRxTooLongErrorsCounterRegister_EUR_msmLineRxTooLongErrorsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxTooLongErrorsCounter_1 in AQ_MsmLineRxTooLongErrorsCounterRegister_EUR */
#define word_AQ_MsmLineRxTooLongErrorsCounterRegister_EUR_msmLineRxTooLongErrorsCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR */
#define AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR_baseRegisterAddress 0x905C
/*! \brief MMD address of structure AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR */
#define AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxInRangeLengthErrorsCounter_0 in AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR */
#define AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR_msmLineRxInRangeLengthErrorsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxInRangeLengthErrorsCounter_0 in AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR */
#define bits_AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR_msmLineRxInRangeLengthErrorsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxInRangeLengthErrorsCounter_0 in AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR */
#define word_AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR_msmLineRxInRangeLengthErrorsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxInRangeLengthErrorsCounter_1 in AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR */
#define AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR_msmLineRxInRangeLengthErrorsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxInRangeLengthErrorsCounter_1 in AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR */
#define bits_AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR_msmLineRxInRangeLengthErrorsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxInRangeLengthErrorsCounter_1 in AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR */
#define word_AQ_MsmLineRxInRangeLengthErrorsCounterRegister_EUR_msmLineRxInRangeLengthErrorsCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineTxVlanFramesCounterRegister_EUR */
#define AQ_MsmLineTxVlanFramesCounterRegister_EUR_baseRegisterAddress 0x9060
/*! \brief MMD address of structure AQ_MsmLineTxVlanFramesCounterRegister_EUR */
#define AQ_MsmLineTxVlanFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxVlanFramesCounter_0 in AQ_MsmLineTxVlanFramesCounterRegister_EUR */
#define AQ_MsmLineTxVlanFramesCounterRegister_EUR_msmLineTxVlanFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxVlanFramesCounter_0 in AQ_MsmLineTxVlanFramesCounterRegister_EUR */
#define bits_AQ_MsmLineTxVlanFramesCounterRegister_EUR_msmLineTxVlanFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxVlanFramesCounter_0 in AQ_MsmLineTxVlanFramesCounterRegister_EUR */
#define word_AQ_MsmLineTxVlanFramesCounterRegister_EUR_msmLineTxVlanFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxVlanFramesCounter_1 in AQ_MsmLineTxVlanFramesCounterRegister_EUR */
#define AQ_MsmLineTxVlanFramesCounterRegister_EUR_msmLineTxVlanFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxVlanFramesCounter_1 in AQ_MsmLineTxVlanFramesCounterRegister_EUR */
#define bits_AQ_MsmLineTxVlanFramesCounterRegister_EUR_msmLineTxVlanFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxVlanFramesCounter_1 in AQ_MsmLineTxVlanFramesCounterRegister_EUR */
#define word_AQ_MsmLineTxVlanFramesCounterRegister_EUR_msmLineTxVlanFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineRxVlanFramesCounterRegister_EUR */
#define AQ_MsmLineRxVlanFramesCounterRegister_EUR_baseRegisterAddress 0x9064
/*! \brief MMD address of structure AQ_MsmLineRxVlanFramesCounterRegister_EUR */
#define AQ_MsmLineRxVlanFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxVlanFramesCounter_0 in AQ_MsmLineRxVlanFramesCounterRegister_EUR */
#define AQ_MsmLineRxVlanFramesCounterRegister_EUR_msmLineRxVlanFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxVlanFramesCounter_0 in AQ_MsmLineRxVlanFramesCounterRegister_EUR */
#define bits_AQ_MsmLineRxVlanFramesCounterRegister_EUR_msmLineRxVlanFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxVlanFramesCounter_0 in AQ_MsmLineRxVlanFramesCounterRegister_EUR */
#define word_AQ_MsmLineRxVlanFramesCounterRegister_EUR_msmLineRxVlanFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxVlanFramesCounter_1 in AQ_MsmLineRxVlanFramesCounterRegister_EUR */
#define AQ_MsmLineRxVlanFramesCounterRegister_EUR_msmLineRxVlanFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxVlanFramesCounter_1 in AQ_MsmLineRxVlanFramesCounterRegister_EUR */
#define bits_AQ_MsmLineRxVlanFramesCounterRegister_EUR_msmLineRxVlanFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxVlanFramesCounter_1 in AQ_MsmLineRxVlanFramesCounterRegister_EUR */
#define word_AQ_MsmLineRxVlanFramesCounterRegister_EUR_msmLineRxVlanFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineTxOctetsCounterRegister_EUR */
#define AQ_MsmLineTxOctetsCounterRegister_EUR_baseRegisterAddress 0x9068
/*! \brief MMD address of structure AQ_MsmLineTxOctetsCounterRegister_EUR */
#define AQ_MsmLineTxOctetsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxOctetsCounter_0 in AQ_MsmLineTxOctetsCounterRegister_EUR */
#define AQ_MsmLineTxOctetsCounterRegister_EUR_msmLineTxOctetsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxOctetsCounter_0 in AQ_MsmLineTxOctetsCounterRegister_EUR */
#define bits_AQ_MsmLineTxOctetsCounterRegister_EUR_msmLineTxOctetsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxOctetsCounter_0 in AQ_MsmLineTxOctetsCounterRegister_EUR */
#define word_AQ_MsmLineTxOctetsCounterRegister_EUR_msmLineTxOctetsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxOctetsCounter_1 in AQ_MsmLineTxOctetsCounterRegister_EUR */
#define AQ_MsmLineTxOctetsCounterRegister_EUR_msmLineTxOctetsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxOctetsCounter_1 in AQ_MsmLineTxOctetsCounterRegister_EUR */
#define bits_AQ_MsmLineTxOctetsCounterRegister_EUR_msmLineTxOctetsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxOctetsCounter_1 in AQ_MsmLineTxOctetsCounterRegister_EUR */
#define word_AQ_MsmLineTxOctetsCounterRegister_EUR_msmLineTxOctetsCounter_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxOctetsCounter_2 in AQ_MsmLineTxOctetsCounterRegister_EUR */
#define AQ_MsmLineTxOctetsCounterRegister_EUR_msmLineTxOctetsCounter_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxOctetsCounter_2 in AQ_MsmLineTxOctetsCounterRegister_EUR */
#define bits_AQ_MsmLineTxOctetsCounterRegister_EUR_msmLineTxOctetsCounter_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxOctetsCounter_2 in AQ_MsmLineTxOctetsCounterRegister_EUR */
#define word_AQ_MsmLineTxOctetsCounterRegister_EUR_msmLineTxOctetsCounter_2 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxOctetsCounter_3 in AQ_MsmLineTxOctetsCounterRegister_EUR */
#define AQ_MsmLineTxOctetsCounterRegister_EUR_msmLineTxOctetsCounter_3 3
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxOctetsCounter_3 in AQ_MsmLineTxOctetsCounterRegister_EUR */
#define bits_AQ_MsmLineTxOctetsCounterRegister_EUR_msmLineTxOctetsCounter_3 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxOctetsCounter_3 in AQ_MsmLineTxOctetsCounterRegister_EUR */
#define word_AQ_MsmLineTxOctetsCounterRegister_EUR_msmLineTxOctetsCounter_3 u3.word_3

/*! \brief Base register address of structure AQ_MsmLineRxOctetsCounterRegister_EUR */
#define AQ_MsmLineRxOctetsCounterRegister_EUR_baseRegisterAddress 0x906C
/*! \brief MMD address of structure AQ_MsmLineRxOctetsCounterRegister_EUR */
#define AQ_MsmLineRxOctetsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxOctetsCounter_0 in AQ_MsmLineRxOctetsCounterRegister_EUR */
#define AQ_MsmLineRxOctetsCounterRegister_EUR_msmLineRxOctetsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxOctetsCounter_0 in AQ_MsmLineRxOctetsCounterRegister_EUR */
#define bits_AQ_MsmLineRxOctetsCounterRegister_EUR_msmLineRxOctetsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxOctetsCounter_0 in AQ_MsmLineRxOctetsCounterRegister_EUR */
#define word_AQ_MsmLineRxOctetsCounterRegister_EUR_msmLineRxOctetsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxOctetsCounter_1 in AQ_MsmLineRxOctetsCounterRegister_EUR */
#define AQ_MsmLineRxOctetsCounterRegister_EUR_msmLineRxOctetsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxOctetsCounter_1 in AQ_MsmLineRxOctetsCounterRegister_EUR */
#define bits_AQ_MsmLineRxOctetsCounterRegister_EUR_msmLineRxOctetsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxOctetsCounter_1 in AQ_MsmLineRxOctetsCounterRegister_EUR */
#define word_AQ_MsmLineRxOctetsCounterRegister_EUR_msmLineRxOctetsCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineRxUnicastFramesCounterRegister_EUR */
#define AQ_MsmLineRxUnicastFramesCounterRegister_EUR_baseRegisterAddress 0x9070
/*! \brief MMD address of structure AQ_MsmLineRxUnicastFramesCounterRegister_EUR */
#define AQ_MsmLineRxUnicastFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxUnicastFramesCounter_0 in AQ_MsmLineRxUnicastFramesCounterRegister_EUR */
#define AQ_MsmLineRxUnicastFramesCounterRegister_EUR_msmLineRxUnicastFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxUnicastFramesCounter_0 in AQ_MsmLineRxUnicastFramesCounterRegister_EUR */
#define bits_AQ_MsmLineRxUnicastFramesCounterRegister_EUR_msmLineRxUnicastFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxUnicastFramesCounter_0 in AQ_MsmLineRxUnicastFramesCounterRegister_EUR */
#define word_AQ_MsmLineRxUnicastFramesCounterRegister_EUR_msmLineRxUnicastFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxUnicastFramesCounter_1 in AQ_MsmLineRxUnicastFramesCounterRegister_EUR */
#define AQ_MsmLineRxUnicastFramesCounterRegister_EUR_msmLineRxUnicastFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxUnicastFramesCounter_1 in AQ_MsmLineRxUnicastFramesCounterRegister_EUR */
#define bits_AQ_MsmLineRxUnicastFramesCounterRegister_EUR_msmLineRxUnicastFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxUnicastFramesCounter_1 in AQ_MsmLineRxUnicastFramesCounterRegister_EUR */
#define word_AQ_MsmLineRxUnicastFramesCounterRegister_EUR_msmLineRxUnicastFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineRxMulticastFramesCounterRegister_EUR */
#define AQ_MsmLineRxMulticastFramesCounterRegister_EUR_baseRegisterAddress 0x9074
/*! \brief MMD address of structure AQ_MsmLineRxMulticastFramesCounterRegister_EUR */
#define AQ_MsmLineRxMulticastFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxMulticastFramesCounter_0 in AQ_MsmLineRxMulticastFramesCounterRegister_EUR */
#define AQ_MsmLineRxMulticastFramesCounterRegister_EUR_msmLineRxMulticastFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxMulticastFramesCounter_0 in AQ_MsmLineRxMulticastFramesCounterRegister_EUR */
#define bits_AQ_MsmLineRxMulticastFramesCounterRegister_EUR_msmLineRxMulticastFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxMulticastFramesCounter_0 in AQ_MsmLineRxMulticastFramesCounterRegister_EUR */
#define word_AQ_MsmLineRxMulticastFramesCounterRegister_EUR_msmLineRxMulticastFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxMulticastFramesCounter_1 in AQ_MsmLineRxMulticastFramesCounterRegister_EUR */
#define AQ_MsmLineRxMulticastFramesCounterRegister_EUR_msmLineRxMulticastFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxMulticastFramesCounter_1 in AQ_MsmLineRxMulticastFramesCounterRegister_EUR */
#define bits_AQ_MsmLineRxMulticastFramesCounterRegister_EUR_msmLineRxMulticastFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxMulticastFramesCounter_1 in AQ_MsmLineRxMulticastFramesCounterRegister_EUR */
#define word_AQ_MsmLineRxMulticastFramesCounterRegister_EUR_msmLineRxMulticastFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineRxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmLineRxBroadcastFramesCounterRegister_EUR_baseRegisterAddress 0x9078
/*! \brief MMD address of structure AQ_MsmLineRxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmLineRxBroadcastFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxBroadcastFramesCounter_0 in AQ_MsmLineRxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmLineRxBroadcastFramesCounterRegister_EUR_msmLineRxBroadcastFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxBroadcastFramesCounter_0 in AQ_MsmLineRxBroadcastFramesCounterRegister_EUR */
#define bits_AQ_MsmLineRxBroadcastFramesCounterRegister_EUR_msmLineRxBroadcastFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxBroadcastFramesCounter_0 in AQ_MsmLineRxBroadcastFramesCounterRegister_EUR */
#define word_AQ_MsmLineRxBroadcastFramesCounterRegister_EUR_msmLineRxBroadcastFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxBroadcastFramesCounter_1 in AQ_MsmLineRxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmLineRxBroadcastFramesCounterRegister_EUR_msmLineRxBroadcastFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxBroadcastFramesCounter_1 in AQ_MsmLineRxBroadcastFramesCounterRegister_EUR */
#define bits_AQ_MsmLineRxBroadcastFramesCounterRegister_EUR_msmLineRxBroadcastFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxBroadcastFramesCounter_1 in AQ_MsmLineRxBroadcastFramesCounterRegister_EUR */
#define word_AQ_MsmLineRxBroadcastFramesCounterRegister_EUR_msmLineRxBroadcastFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineTxErrorsCounterRegister_EUR */
#define AQ_MsmLineTxErrorsCounterRegister_EUR_baseRegisterAddress 0x907C
/*! \brief MMD address of structure AQ_MsmLineTxErrorsCounterRegister_EUR */
#define AQ_MsmLineTxErrorsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxErrorsCounter_0 in AQ_MsmLineTxErrorsCounterRegister_EUR */
#define AQ_MsmLineTxErrorsCounterRegister_EUR_msmLineTxErrorsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxErrorsCounter_0 in AQ_MsmLineTxErrorsCounterRegister_EUR */
#define bits_AQ_MsmLineTxErrorsCounterRegister_EUR_msmLineTxErrorsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxErrorsCounter_0 in AQ_MsmLineTxErrorsCounterRegister_EUR */
#define word_AQ_MsmLineTxErrorsCounterRegister_EUR_msmLineTxErrorsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxErrorsCounter_1 in AQ_MsmLineTxErrorsCounterRegister_EUR */
#define AQ_MsmLineTxErrorsCounterRegister_EUR_msmLineTxErrorsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxErrorsCounter_1 in AQ_MsmLineTxErrorsCounterRegister_EUR */
#define bits_AQ_MsmLineTxErrorsCounterRegister_EUR_msmLineTxErrorsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxErrorsCounter_1 in AQ_MsmLineTxErrorsCounterRegister_EUR */
#define word_AQ_MsmLineTxErrorsCounterRegister_EUR_msmLineTxErrorsCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineTxUnicastFramesCounterRegister_EUR */
#define AQ_MsmLineTxUnicastFramesCounterRegister_EUR_baseRegisterAddress 0x9084
/*! \brief MMD address of structure AQ_MsmLineTxUnicastFramesCounterRegister_EUR */
#define AQ_MsmLineTxUnicastFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxUnicastFramesCounter_0 in AQ_MsmLineTxUnicastFramesCounterRegister_EUR */
#define AQ_MsmLineTxUnicastFramesCounterRegister_EUR_msmLineTxUnicastFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxUnicastFramesCounter_0 in AQ_MsmLineTxUnicastFramesCounterRegister_EUR */
#define bits_AQ_MsmLineTxUnicastFramesCounterRegister_EUR_msmLineTxUnicastFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxUnicastFramesCounter_0 in AQ_MsmLineTxUnicastFramesCounterRegister_EUR */
#define word_AQ_MsmLineTxUnicastFramesCounterRegister_EUR_msmLineTxUnicastFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxUnicastFramesCounter_1 in AQ_MsmLineTxUnicastFramesCounterRegister_EUR */
#define AQ_MsmLineTxUnicastFramesCounterRegister_EUR_msmLineTxUnicastFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxUnicastFramesCounter_1 in AQ_MsmLineTxUnicastFramesCounterRegister_EUR */
#define bits_AQ_MsmLineTxUnicastFramesCounterRegister_EUR_msmLineTxUnicastFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxUnicastFramesCounter_1 in AQ_MsmLineTxUnicastFramesCounterRegister_EUR */
#define word_AQ_MsmLineTxUnicastFramesCounterRegister_EUR_msmLineTxUnicastFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineTxMulticastFramesCounterRegister_EUR */
#define AQ_MsmLineTxMulticastFramesCounterRegister_EUR_baseRegisterAddress 0x9088
/*! \brief MMD address of structure AQ_MsmLineTxMulticastFramesCounterRegister_EUR */
#define AQ_MsmLineTxMulticastFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxMulticastFramesCounter_0 in AQ_MsmLineTxMulticastFramesCounterRegister_EUR */
#define AQ_MsmLineTxMulticastFramesCounterRegister_EUR_msmLineTxMulticastFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxMulticastFramesCounter_0 in AQ_MsmLineTxMulticastFramesCounterRegister_EUR */
#define bits_AQ_MsmLineTxMulticastFramesCounterRegister_EUR_msmLineTxMulticastFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxMulticastFramesCounter_0 in AQ_MsmLineTxMulticastFramesCounterRegister_EUR */
#define word_AQ_MsmLineTxMulticastFramesCounterRegister_EUR_msmLineTxMulticastFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxMulticastFramesCounter_1 in AQ_MsmLineTxMulticastFramesCounterRegister_EUR */
#define AQ_MsmLineTxMulticastFramesCounterRegister_EUR_msmLineTxMulticastFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxMulticastFramesCounter_1 in AQ_MsmLineTxMulticastFramesCounterRegister_EUR */
#define bits_AQ_MsmLineTxMulticastFramesCounterRegister_EUR_msmLineTxMulticastFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxMulticastFramesCounter_1 in AQ_MsmLineTxMulticastFramesCounterRegister_EUR */
#define word_AQ_MsmLineTxMulticastFramesCounterRegister_EUR_msmLineTxMulticastFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineTxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmLineTxBroadcastFramesCounterRegister_EUR_baseRegisterAddress 0x908C
/*! \brief MMD address of structure AQ_MsmLineTxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmLineTxBroadcastFramesCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxBroadcastFramesCounter_0 in AQ_MsmLineTxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmLineTxBroadcastFramesCounterRegister_EUR_msmLineTxBroadcastFramesCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxBroadcastFramesCounter_0 in AQ_MsmLineTxBroadcastFramesCounterRegister_EUR */
#define bits_AQ_MsmLineTxBroadcastFramesCounterRegister_EUR_msmLineTxBroadcastFramesCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxBroadcastFramesCounter_0 in AQ_MsmLineTxBroadcastFramesCounterRegister_EUR */
#define word_AQ_MsmLineTxBroadcastFramesCounterRegister_EUR_msmLineTxBroadcastFramesCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineTxBroadcastFramesCounter_1 in AQ_MsmLineTxBroadcastFramesCounterRegister_EUR */
#define AQ_MsmLineTxBroadcastFramesCounterRegister_EUR_msmLineTxBroadcastFramesCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineTxBroadcastFramesCounter_1 in AQ_MsmLineTxBroadcastFramesCounterRegister_EUR */
#define bits_AQ_MsmLineTxBroadcastFramesCounterRegister_EUR_msmLineTxBroadcastFramesCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineTxBroadcastFramesCounter_1 in AQ_MsmLineTxBroadcastFramesCounterRegister_EUR */
#define word_AQ_MsmLineTxBroadcastFramesCounterRegister_EUR_msmLineTxBroadcastFramesCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineRxErrorsCounterRegister_EUR */
#define AQ_MsmLineRxErrorsCounterRegister_EUR_baseRegisterAddress 0x90C8
/*! \brief MMD address of structure AQ_MsmLineRxErrorsCounterRegister_EUR */
#define AQ_MsmLineRxErrorsCounterRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxErrorsCounter_0 in AQ_MsmLineRxErrorsCounterRegister_EUR */
#define AQ_MsmLineRxErrorsCounterRegister_EUR_msmLineRxErrorsCounter_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxErrorsCounter_0 in AQ_MsmLineRxErrorsCounterRegister_EUR */
#define bits_AQ_MsmLineRxErrorsCounterRegister_EUR_msmLineRxErrorsCounter_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxErrorsCounter_0 in AQ_MsmLineRxErrorsCounterRegister_EUR */
#define word_AQ_MsmLineRxErrorsCounterRegister_EUR_msmLineRxErrorsCounter_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineRxErrorsCounter_1 in AQ_MsmLineRxErrorsCounterRegister_EUR */
#define AQ_MsmLineRxErrorsCounterRegister_EUR_msmLineRxErrorsCounter_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineRxErrorsCounter_1 in AQ_MsmLineRxErrorsCounterRegister_EUR */
#define bits_AQ_MsmLineRxErrorsCounterRegister_EUR_msmLineRxErrorsCounter_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure msmLineRxErrorsCounter_1 in AQ_MsmLineRxErrorsCounterRegister_EUR */
#define word_AQ_MsmLineRxErrorsCounterRegister_EUR_msmLineRxErrorsCounter_1 u1.word_1

/*! \brief Base register address of structure AQ_MsmLineSgmiiControlRegister_EUR */
#define AQ_MsmLineSgmiiControlRegister_EUR_baseRegisterAddress 0x9180
/*! \brief MMD address of structure AQ_MsmLineSgmiiControlRegister_EUR */
#define AQ_MsmLineSgmiiControlRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiReset in AQ_MsmLineSgmiiControlRegister_EUR */
#define AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiReset in AQ_MsmLineSgmiiControlRegister_EUR */
#define bits_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiReset in AQ_MsmLineSgmiiControlRegister_EUR */
#define word_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiLoopback in AQ_MsmLineSgmiiControlRegister_EUR */
#define AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiLoopback 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiLoopback in AQ_MsmLineSgmiiControlRegister_EUR */
#define bits_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiLoopback u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiLoopback in AQ_MsmLineSgmiiControlRegister_EUR */
#define word_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiLoopback u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiSpeedSelection_2 in AQ_MsmLineSgmiiControlRegister_EUR */
#define AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiSpeedSelection_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiSpeedSelection_2 in AQ_MsmLineSgmiiControlRegister_EUR */
#define bits_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiSpeedSelection_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiSpeedSelection_2 in AQ_MsmLineSgmiiControlRegister_EUR */
#define word_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiSpeedSelection_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiAutonegotationEnable in AQ_MsmLineSgmiiControlRegister_EUR */
#define AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiAutonegotationEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiAutonegotationEnable in AQ_MsmLineSgmiiControlRegister_EUR */
#define bits_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiAutonegotationEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiAutonegotationEnable in AQ_MsmLineSgmiiControlRegister_EUR */
#define word_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiAutonegotationEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiPowerDown in AQ_MsmLineSgmiiControlRegister_EUR */
#define AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiPowerDown 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiPowerDown in AQ_MsmLineSgmiiControlRegister_EUR */
#define bits_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiPowerDown u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiPowerDown in AQ_MsmLineSgmiiControlRegister_EUR */
#define word_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiPowerDown u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiIsolate in AQ_MsmLineSgmiiControlRegister_EUR */
#define AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiIsolate 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiIsolate in AQ_MsmLineSgmiiControlRegister_EUR */
#define bits_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiIsolate u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiIsolate in AQ_MsmLineSgmiiControlRegister_EUR */
#define word_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiIsolate u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiRestartAutonegotiation in AQ_MsmLineSgmiiControlRegister_EUR */
#define AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiRestartAutonegotiation 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiRestartAutonegotiation in AQ_MsmLineSgmiiControlRegister_EUR */
#define bits_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiRestartAutonegotiation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiRestartAutonegotiation in AQ_MsmLineSgmiiControlRegister_EUR */
#define word_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiRestartAutonegotiation u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiDuplexMode in AQ_MsmLineSgmiiControlRegister_EUR */
#define AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiDuplexMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiDuplexMode in AQ_MsmLineSgmiiControlRegister_EUR */
#define bits_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiDuplexMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiDuplexMode in AQ_MsmLineSgmiiControlRegister_EUR */
#define word_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiDuplexMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiCollisionTest in AQ_MsmLineSgmiiControlRegister_EUR */
#define AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiCollisionTest 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiCollisionTest in AQ_MsmLineSgmiiControlRegister_EUR */
#define bits_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiCollisionTest u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiCollisionTest in AQ_MsmLineSgmiiControlRegister_EUR */
#define word_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiCollisionTest u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiSpeedSelection_1 in AQ_MsmLineSgmiiControlRegister_EUR */
#define AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiSpeedSelection_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiSpeedSelection_1 in AQ_MsmLineSgmiiControlRegister_EUR */
#define bits_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiSpeedSelection_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiSpeedSelection_1 in AQ_MsmLineSgmiiControlRegister_EUR */
#define word_AQ_MsmLineSgmiiControlRegister_EUR_msmLineSgmiiSpeedSelection_1 u0.word_0

/*! \brief Base register address of structure AQ_MsmLineSgmiiIfModeRegister_EUR */
#define AQ_MsmLineSgmiiIfModeRegister_EUR_baseRegisterAddress 0x91A8
/*! \brief MMD address of structure AQ_MsmLineSgmiiIfModeRegister_EUR */
#define AQ_MsmLineSgmiiIfModeRegister_EUR_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiPcsEnable in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineSgmiiPcsEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiPcsEnable in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define bits_AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineSgmiiPcsEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiPcsEnable in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define word_AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineSgmiiPcsEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiHalfDuplex in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineSgmiiHalfDuplex 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiHalfDuplex in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define bits_AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineSgmiiHalfDuplex u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiHalfDuplex in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define word_AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineSgmiiHalfDuplex u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiSpeed in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineSgmiiSpeed 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiSpeed in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define bits_AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineSgmiiSpeed u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiSpeed in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define word_AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineSgmiiSpeed u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineUseSgmiiAutonegotiation in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineUseSgmiiAutonegotiation 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineUseSgmiiAutonegotiation in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define bits_AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineUseSgmiiAutonegotiation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineUseSgmiiAutonegotiation in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define word_AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineUseSgmiiAutonegotiation u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure msmLineSgmiiEnable in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineSgmiiEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure msmLineSgmiiEnable in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define bits_AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineSgmiiEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure msmLineSgmiiEnable in AQ_MsmLineSgmiiIfModeRegister_EUR */
#define word_AQ_MsmLineSgmiiIfModeRegister_EUR_msmLineSgmiiEnable u0.word_0

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
