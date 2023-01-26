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
#ifndef AQ_HHD_GLOBAL_REGS_DEFINES_HEADER
#define AQ_HHD_GLOBAL_REGS_DEFINES_HEADER


/*-----------------------------------------------------------------------------*/
/*Access macro definitions                                                     */
/*-----------------------------------------------------------------------------*/
/*! \brief Base register address of structure AQ_GlobalStandardControl_1_HHD */
#define AQ_GlobalStandardControl_1_HHD_baseRegisterAddress 0x0000
/*! \brief MMD address of structure AQ_GlobalStandardControl_1_HHD */
#define AQ_GlobalStandardControl_1_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure softReset in AQ_GlobalStandardControl_1_HHD */
#define AQ_GlobalStandardControl_1_HHD_softReset 0
/*! \brief Preprocessor variable to relate field to bit position in structure softReset in AQ_GlobalStandardControl_1_HHD */
#define bits_AQ_GlobalStandardControl_1_HHD_softReset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure softReset in AQ_GlobalStandardControl_1_HHD */
#define word_AQ_GlobalStandardControl_1_HHD_softReset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowPower in AQ_GlobalStandardControl_1_HHD */
#define AQ_GlobalStandardControl_1_HHD_lowPower 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowPower in AQ_GlobalStandardControl_1_HHD */
#define bits_AQ_GlobalStandardControl_1_HHD_lowPower u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowPower in AQ_GlobalStandardControl_1_HHD */
#define word_AQ_GlobalStandardControl_1_HHD_lowPower u0.word_0

/*! \brief Base register address of structure AQ_GlobalStandardDeviceIdentifier_HHD */
#define AQ_GlobalStandardDeviceIdentifier_HHD_baseRegisterAddress 0x0002
/*! \brief MMD address of structure AQ_GlobalStandardDeviceIdentifier_HHD */
#define AQ_GlobalStandardDeviceIdentifier_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdMSW in AQ_GlobalStandardDeviceIdentifier_HHD */
#define AQ_GlobalStandardDeviceIdentifier_HHD_deviceIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdMSW in AQ_GlobalStandardDeviceIdentifier_HHD */
#define bits_AQ_GlobalStandardDeviceIdentifier_HHD_deviceIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdMSW in AQ_GlobalStandardDeviceIdentifier_HHD */
#define word_AQ_GlobalStandardDeviceIdentifier_HHD_deviceIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdLSW in AQ_GlobalStandardDeviceIdentifier_HHD */
#define AQ_GlobalStandardDeviceIdentifier_HHD_deviceIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdLSW in AQ_GlobalStandardDeviceIdentifier_HHD */
#define bits_AQ_GlobalStandardDeviceIdentifier_HHD_deviceIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdLSW in AQ_GlobalStandardDeviceIdentifier_HHD */
#define word_AQ_GlobalStandardDeviceIdentifier_HHD_deviceIdLSW u1.word_1

/*! \brief Base register address of structure AQ_GlobalStandardDevicesInPackage_HHD */
#define AQ_GlobalStandardDevicesInPackage_HHD_baseRegisterAddress 0x0005
/*! \brief MMD address of structure AQ_GlobalStandardDevicesInPackage_HHD */
#define AQ_GlobalStandardDevicesInPackage_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define AQ_GlobalStandardDevicesInPackage_HHD_autonegotiationPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define bits_AQ_GlobalStandardDevicesInPackage_HHD_autonegotiationPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define word_AQ_GlobalStandardDevicesInPackage_HHD_autonegotiationPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tcPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define AQ_GlobalStandardDevicesInPackage_HHD_tcPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure tcPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define bits_AQ_GlobalStandardDevicesInPackage_HHD_tcPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tcPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define word_AQ_GlobalStandardDevicesInPackage_HHD_tcPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure dteXsPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define AQ_GlobalStandardDevicesInPackage_HHD_dteXsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure dteXsPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define bits_AQ_GlobalStandardDevicesInPackage_HHD_dteXsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure dteXsPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define word_AQ_GlobalStandardDevicesInPackage_HHD_dteXsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_Present in AQ_GlobalStandardDevicesInPackage_HHD */
#define AQ_GlobalStandardDevicesInPackage_HHD_phyXS_Present 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_Present in AQ_GlobalStandardDevicesInPackage_HHD */
#define bits_AQ_GlobalStandardDevicesInPackage_HHD_phyXS_Present u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_Present in AQ_GlobalStandardDevicesInPackage_HHD */
#define word_AQ_GlobalStandardDevicesInPackage_HHD_phyXS_Present u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define AQ_GlobalStandardDevicesInPackage_HHD_pcsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define bits_AQ_GlobalStandardDevicesInPackage_HHD_pcsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define word_AQ_GlobalStandardDevicesInPackage_HHD_pcsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure wisPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define AQ_GlobalStandardDevicesInPackage_HHD_wisPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure wisPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define bits_AQ_GlobalStandardDevicesInPackage_HHD_wisPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure wisPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define word_AQ_GlobalStandardDevicesInPackage_HHD_wisPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define AQ_GlobalStandardDevicesInPackage_HHD_pmaPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define bits_AQ_GlobalStandardDevicesInPackage_HHD_pmaPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define word_AQ_GlobalStandardDevicesInPackage_HHD_pmaPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clause_22RegistersPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define AQ_GlobalStandardDevicesInPackage_HHD_clause_22RegistersPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22RegistersPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define bits_AQ_GlobalStandardDevicesInPackage_HHD_clause_22RegistersPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clause_22RegistersPresent in AQ_GlobalStandardDevicesInPackage_HHD */
#define word_AQ_GlobalStandardDevicesInPackage_HHD_clause_22RegistersPresent u0.word_0

/*! \brief Base register address of structure AQ_GlobalStandardVendorDevicesInPackage_HHD */
#define AQ_GlobalStandardVendorDevicesInPackage_HHD_baseRegisterAddress 0x0006
/*! \brief MMD address of structure AQ_GlobalStandardVendorDevicesInPackage_HHD */
#define AQ_GlobalStandardVendorDevicesInPackage_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_2Present in AQ_GlobalStandardVendorDevicesInPackage_HHD */
#define AQ_GlobalStandardVendorDevicesInPackage_HHD_vendorSpecificDevice_2Present 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_2Present in AQ_GlobalStandardVendorDevicesInPackage_HHD */
#define bits_AQ_GlobalStandardVendorDevicesInPackage_HHD_vendorSpecificDevice_2Present u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_2Present in AQ_GlobalStandardVendorDevicesInPackage_HHD */
#define word_AQ_GlobalStandardVendorDevicesInPackage_HHD_vendorSpecificDevice_2Present u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_1Present in AQ_GlobalStandardVendorDevicesInPackage_HHD */
#define AQ_GlobalStandardVendorDevicesInPackage_HHD_vendorSpecificDevice_1Present 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_1Present in AQ_GlobalStandardVendorDevicesInPackage_HHD */
#define bits_AQ_GlobalStandardVendorDevicesInPackage_HHD_vendorSpecificDevice_1Present u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_1Present in AQ_GlobalStandardVendorDevicesInPackage_HHD */
#define word_AQ_GlobalStandardVendorDevicesInPackage_HHD_vendorSpecificDevice_1Present u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clause_22ExtensionPresent in AQ_GlobalStandardVendorDevicesInPackage_HHD */
#define AQ_GlobalStandardVendorDevicesInPackage_HHD_clause_22ExtensionPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22ExtensionPresent in AQ_GlobalStandardVendorDevicesInPackage_HHD */
#define bits_AQ_GlobalStandardVendorDevicesInPackage_HHD_clause_22ExtensionPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clause_22ExtensionPresent in AQ_GlobalStandardVendorDevicesInPackage_HHD */
#define word_AQ_GlobalStandardVendorDevicesInPackage_HHD_clause_22ExtensionPresent u0.word_0

/*! \brief Base register address of structure AQ_GlobalStandardStatus_2_HHD */
#define AQ_GlobalStandardStatus_2_HHD_baseRegisterAddress 0x0008
/*! \brief MMD address of structure AQ_GlobalStandardStatus_2_HHD */
#define AQ_GlobalStandardStatus_2_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure devicePresent in AQ_GlobalStandardStatus_2_HHD */
#define AQ_GlobalStandardStatus_2_HHD_devicePresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure devicePresent in AQ_GlobalStandardStatus_2_HHD */
#define bits_AQ_GlobalStandardStatus_2_HHD_devicePresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure devicePresent in AQ_GlobalStandardStatus_2_HHD */
#define word_AQ_GlobalStandardStatus_2_HHD_devicePresent u0.word_0

/*! \brief Base register address of structure AQ_GlobalStandardPackageIdentifier_HHD */
#define AQ_GlobalStandardPackageIdentifier_HHD_baseRegisterAddress 0x000E
/*! \brief MMD address of structure AQ_GlobalStandardPackageIdentifier_HHD */
#define AQ_GlobalStandardPackageIdentifier_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure packageIdMSW in AQ_GlobalStandardPackageIdentifier_HHD */
#define AQ_GlobalStandardPackageIdentifier_HHD_packageIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdMSW in AQ_GlobalStandardPackageIdentifier_HHD */
#define bits_AQ_GlobalStandardPackageIdentifier_HHD_packageIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure packageIdMSW in AQ_GlobalStandardPackageIdentifier_HHD */
#define word_AQ_GlobalStandardPackageIdentifier_HHD_packageIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure packageIdLSW in AQ_GlobalStandardPackageIdentifier_HHD */
#define AQ_GlobalStandardPackageIdentifier_HHD_packageIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdLSW in AQ_GlobalStandardPackageIdentifier_HHD */
#define bits_AQ_GlobalStandardPackageIdentifier_HHD_packageIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure packageIdLSW in AQ_GlobalStandardPackageIdentifier_HHD */
#define word_AQ_GlobalStandardPackageIdentifier_HHD_packageIdLSW u1.word_1

/*! \brief Base register address of structure AQ_GlobalFirmwareID_HHD */
#define AQ_GlobalFirmwareID_HHD_baseRegisterAddress 0x0020
/*! \brief MMD address of structure AQ_GlobalFirmwareID_HHD */
#define AQ_GlobalFirmwareID_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure firmwareMajorRevisionNumber in AQ_GlobalFirmwareID_HHD */
#define AQ_GlobalFirmwareID_HHD_firmwareMajorRevisionNumber 0
/*! \brief Preprocessor variable to relate field to bit position in structure firmwareMajorRevisionNumber in AQ_GlobalFirmwareID_HHD */
#define bits_AQ_GlobalFirmwareID_HHD_firmwareMajorRevisionNumber u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure firmwareMajorRevisionNumber in AQ_GlobalFirmwareID_HHD */
#define word_AQ_GlobalFirmwareID_HHD_firmwareMajorRevisionNumber u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure firmwareMinorRevisionNumber in AQ_GlobalFirmwareID_HHD */
#define AQ_GlobalFirmwareID_HHD_firmwareMinorRevisionNumber 0
/*! \brief Preprocessor variable to relate field to bit position in structure firmwareMinorRevisionNumber in AQ_GlobalFirmwareID_HHD */
#define bits_AQ_GlobalFirmwareID_HHD_firmwareMinorRevisionNumber u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure firmwareMinorRevisionNumber in AQ_GlobalFirmwareID_HHD */
#define word_AQ_GlobalFirmwareID_HHD_firmwareMinorRevisionNumber u0.word_0

/*! \brief Base register address of structure AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_baseRegisterAddress 0x0100
/*! \brief MMD address of structure AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure nvrExecuteOperation in AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_nvrExecuteOperation 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrExecuteOperation in AQ_GlobalNvrInterface_HHD */
#define bits_AQ_GlobalNvrInterface_HHD_nvrExecuteOperation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrExecuteOperation in AQ_GlobalNvrInterface_HHD */
#define word_AQ_GlobalNvrInterface_HHD_nvrExecuteOperation u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrWriteMode in AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_nvrWriteMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrWriteMode in AQ_GlobalNvrInterface_HHD */
#define bits_AQ_GlobalNvrInterface_HHD_nvrWriteMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrWriteMode in AQ_GlobalNvrInterface_HHD */
#define word_AQ_GlobalNvrInterface_HHD_nvrWriteMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure freezeNvrCrc in AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_freezeNvrCrc 0
/*! \brief Preprocessor variable to relate field to bit position in structure freezeNvrCrc in AQ_GlobalNvrInterface_HHD */
#define bits_AQ_GlobalNvrInterface_HHD_freezeNvrCrc u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure freezeNvrCrc in AQ_GlobalNvrInterface_HHD */
#define word_AQ_GlobalNvrInterface_HHD_freezeNvrCrc u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure resetNvrCrc in AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_resetNvrCrc 0
/*! \brief Preprocessor variable to relate field to bit position in structure resetNvrCrc in AQ_GlobalNvrInterface_HHD */
#define bits_AQ_GlobalNvrInterface_HHD_resetNvrCrc u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure resetNvrCrc in AQ_GlobalNvrInterface_HHD */
#define word_AQ_GlobalNvrInterface_HHD_resetNvrCrc u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrBurst in AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_nvrBurst 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrBurst in AQ_GlobalNvrInterface_HHD */
#define bits_AQ_GlobalNvrInterface_HHD_nvrBurst u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrBurst in AQ_GlobalNvrInterface_HHD */
#define word_AQ_GlobalNvrInterface_HHD_nvrBurst u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrBusy in AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_nvrBusy 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrBusy in AQ_GlobalNvrInterface_HHD */
#define bits_AQ_GlobalNvrInterface_HHD_nvrBusy u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrBusy in AQ_GlobalNvrInterface_HHD */
#define word_AQ_GlobalNvrInterface_HHD_nvrBusy u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrOpcode in AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_nvrOpcode 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrOpcode in AQ_GlobalNvrInterface_HHD */
#define bits_AQ_GlobalNvrInterface_HHD_nvrOpcode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrOpcode in AQ_GlobalNvrInterface_HHD */
#define word_AQ_GlobalNvrInterface_HHD_nvrOpcode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrMailboxCrc in AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_nvrMailboxCrc 1
/*! \brief Preprocessor variable to relate field to bit position in structure nvrMailboxCrc in AQ_GlobalNvrInterface_HHD */
#define bits_AQ_GlobalNvrInterface_HHD_nvrMailboxCrc u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure nvrMailboxCrc in AQ_GlobalNvrInterface_HHD */
#define word_AQ_GlobalNvrInterface_HHD_nvrMailboxCrc u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure nvrAddressMSW in AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_nvrAddressMSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure nvrAddressMSW in AQ_GlobalNvrInterface_HHD */
#define bits_AQ_GlobalNvrInterface_HHD_nvrAddressMSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure nvrAddressMSW in AQ_GlobalNvrInterface_HHD */
#define word_AQ_GlobalNvrInterface_HHD_nvrAddressMSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure nvrAddressLSW in AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_nvrAddressLSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure nvrAddressLSW in AQ_GlobalNvrInterface_HHD */
#define bits_AQ_GlobalNvrInterface_HHD_nvrAddressLSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure nvrAddressLSW in AQ_GlobalNvrInterface_HHD */
#define word_AQ_GlobalNvrInterface_HHD_nvrAddressLSW u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure nvrDataMSW in AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_nvrDataMSW 4
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDataMSW in AQ_GlobalNvrInterface_HHD */
#define bits_AQ_GlobalNvrInterface_HHD_nvrDataMSW u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure nvrDataMSW in AQ_GlobalNvrInterface_HHD */
#define word_AQ_GlobalNvrInterface_HHD_nvrDataMSW u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure nvrDataLSW in AQ_GlobalNvrInterface_HHD */
#define AQ_GlobalNvrInterface_HHD_nvrDataLSW 5
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDataLSW in AQ_GlobalNvrInterface_HHD */
#define bits_AQ_GlobalNvrInterface_HHD_nvrDataLSW u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure nvrDataLSW in AQ_GlobalNvrInterface_HHD */
#define word_AQ_GlobalNvrInterface_HHD_nvrDataLSW u5.word_5

/*! \brief Base register address of structure AQ_GlobalMailboxInterface_HHD */
#define AQ_GlobalMailboxInterface_HHD_baseRegisterAddress 0x0200
/*! \brief MMD address of structure AQ_GlobalMailboxInterface_HHD */
#define AQ_GlobalMailboxInterface_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxExecuteOperation in AQ_GlobalMailboxInterface_HHD */
#define AQ_GlobalMailboxInterface_HHD_upMailboxExecuteOperation 0
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxExecuteOperation in AQ_GlobalMailboxInterface_HHD */
#define bits_AQ_GlobalMailboxInterface_HHD_upMailboxExecuteOperation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxExecuteOperation in AQ_GlobalMailboxInterface_HHD */
#define word_AQ_GlobalMailboxInterface_HHD_upMailboxExecuteOperation u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxWriteMode in AQ_GlobalMailboxInterface_HHD */
#define AQ_GlobalMailboxInterface_HHD_upMailboxWriteMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxWriteMode in AQ_GlobalMailboxInterface_HHD */
#define bits_AQ_GlobalMailboxInterface_HHD_upMailboxWriteMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxWriteMode in AQ_GlobalMailboxInterface_HHD */
#define word_AQ_GlobalMailboxInterface_HHD_upMailboxWriteMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure resetUpMailboxCrc in AQ_GlobalMailboxInterface_HHD */
#define AQ_GlobalMailboxInterface_HHD_resetUpMailboxCrc 0
/*! \brief Preprocessor variable to relate field to bit position in structure resetUpMailboxCrc in AQ_GlobalMailboxInterface_HHD */
#define bits_AQ_GlobalMailboxInterface_HHD_resetUpMailboxCrc u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure resetUpMailboxCrc in AQ_GlobalMailboxInterface_HHD */
#define word_AQ_GlobalMailboxInterface_HHD_resetUpMailboxCrc u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxBusy in AQ_GlobalMailboxInterface_HHD */
#define AQ_GlobalMailboxInterface_HHD_upMailboxBusy 0
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxBusy in AQ_GlobalMailboxInterface_HHD */
#define bits_AQ_GlobalMailboxInterface_HHD_upMailboxBusy u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxBusy in AQ_GlobalMailboxInterface_HHD */
#define word_AQ_GlobalMailboxInterface_HHD_upMailboxBusy u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxCrc in AQ_GlobalMailboxInterface_HHD */
#define AQ_GlobalMailboxInterface_HHD_upMailboxCrc 1
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxCrc in AQ_GlobalMailboxInterface_HHD */
#define bits_AQ_GlobalMailboxInterface_HHD_upMailboxCrc u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxCrc in AQ_GlobalMailboxInterface_HHD */
#define word_AQ_GlobalMailboxInterface_HHD_upMailboxCrc u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxAddressMSW in AQ_GlobalMailboxInterface_HHD */
#define AQ_GlobalMailboxInterface_HHD_upMailboxAddressMSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxAddressMSW in AQ_GlobalMailboxInterface_HHD */
#define bits_AQ_GlobalMailboxInterface_HHD_upMailboxAddressMSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxAddressMSW in AQ_GlobalMailboxInterface_HHD */
#define word_AQ_GlobalMailboxInterface_HHD_upMailboxAddressMSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxAddressLSW in AQ_GlobalMailboxInterface_HHD */
#define AQ_GlobalMailboxInterface_HHD_upMailboxAddressLSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxAddressLSW in AQ_GlobalMailboxInterface_HHD */
#define bits_AQ_GlobalMailboxInterface_HHD_upMailboxAddressLSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxAddressLSW in AQ_GlobalMailboxInterface_HHD */
#define word_AQ_GlobalMailboxInterface_HHD_upMailboxAddressLSW u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxAddressLSW_Don_tCare in AQ_GlobalMailboxInterface_HHD */
#define AQ_GlobalMailboxInterface_HHD_upMailboxAddressLSW_Don_tCare 3
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxAddressLSW_Don_tCare in AQ_GlobalMailboxInterface_HHD */
#define bits_AQ_GlobalMailboxInterface_HHD_upMailboxAddressLSW_Don_tCare u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxAddressLSW_Don_tCare in AQ_GlobalMailboxInterface_HHD */
#define word_AQ_GlobalMailboxInterface_HHD_upMailboxAddressLSW_Don_tCare u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxDataMSW in AQ_GlobalMailboxInterface_HHD */
#define AQ_GlobalMailboxInterface_HHD_upMailboxDataMSW 4
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxDataMSW in AQ_GlobalMailboxInterface_HHD */
#define bits_AQ_GlobalMailboxInterface_HHD_upMailboxDataMSW u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxDataMSW in AQ_GlobalMailboxInterface_HHD */
#define word_AQ_GlobalMailboxInterface_HHD_upMailboxDataMSW u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxDataLSW in AQ_GlobalMailboxInterface_HHD */
#define AQ_GlobalMailboxInterface_HHD_upMailboxDataLSW 5
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxDataLSW in AQ_GlobalMailboxInterface_HHD */
#define bits_AQ_GlobalMailboxInterface_HHD_upMailboxDataLSW u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxDataLSW in AQ_GlobalMailboxInterface_HHD */
#define word_AQ_GlobalMailboxInterface_HHD_upMailboxDataLSW u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure upMailboxCrcReadEnable in AQ_GlobalMailboxInterface_HHD */
#define AQ_GlobalMailboxInterface_HHD_upMailboxCrcReadEnable 6
/*! \brief Preprocessor variable to relate field to bit position in structure upMailboxCrcReadEnable in AQ_GlobalMailboxInterface_HHD */
#define bits_AQ_GlobalMailboxInterface_HHD_upMailboxCrcReadEnable u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure upMailboxCrcReadEnable in AQ_GlobalMailboxInterface_HHD */
#define word_AQ_GlobalMailboxInterface_HHD_upMailboxCrcReadEnable u6.word_6

/*! \brief Base register address of structure AQ_GlobalMicroprocessorScratchPad_HHD */
#define AQ_GlobalMicroprocessorScratchPad_HHD_baseRegisterAddress 0x0300
/*! \brief MMD address of structure AQ_GlobalMicroprocessorScratchPad_HHD */
#define AQ_GlobalMicroprocessorScratchPad_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_1 in AQ_GlobalMicroprocessorScratchPad_HHD */
#define AQ_GlobalMicroprocessorScratchPad_HHD_scratchPad_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_1 in AQ_GlobalMicroprocessorScratchPad_HHD */
#define bits_AQ_GlobalMicroprocessorScratchPad_HHD_scratchPad_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_1 in AQ_GlobalMicroprocessorScratchPad_HHD */
#define word_AQ_GlobalMicroprocessorScratchPad_HHD_scratchPad_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure scratchPad_2 in AQ_GlobalMicroprocessorScratchPad_HHD */
#define AQ_GlobalMicroprocessorScratchPad_HHD_scratchPad_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure scratchPad_2 in AQ_GlobalMicroprocessorScratchPad_HHD */
#define bits_AQ_GlobalMicroprocessorScratchPad_HHD_scratchPad_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure scratchPad_2 in AQ_GlobalMicroprocessorScratchPad_HHD */
#define word_AQ_GlobalMicroprocessorScratchPad_HHD_scratchPad_2 u1.word_1

/*! \brief Base register address of structure AQ_GlobalCommonSerdesLane0RxEq_HHD */
#define AQ_GlobalCommonSerdesLane0RxEq_HHD_baseRegisterAddress 0x2D55
/*! \brief MMD address of structure AQ_GlobalCommonSerdesLane0RxEq_HHD */
#define AQ_GlobalCommonSerdesLane0RxEq_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure serdesLane0RxEqDone in AQ_GlobalCommonSerdesLane0RxEq_HHD */
#define AQ_GlobalCommonSerdesLane0RxEq_HHD_serdesLane0RxEqDone 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesLane0RxEqDone in AQ_GlobalCommonSerdesLane0RxEq_HHD */
#define bits_AQ_GlobalCommonSerdesLane0RxEq_HHD_serdesLane0RxEqDone u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesLane0RxEqDone in AQ_GlobalCommonSerdesLane0RxEq_HHD */
#define word_AQ_GlobalCommonSerdesLane0RxEq_HHD_serdesLane0RxEqDone u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesLane0RxEqBestEyeValue in AQ_GlobalCommonSerdesLane0RxEq_HHD */
#define AQ_GlobalCommonSerdesLane0RxEq_HHD_serdesLane0RxEqBestEyeValue 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesLane0RxEqBestEyeValue in AQ_GlobalCommonSerdesLane0RxEq_HHD */
#define bits_AQ_GlobalCommonSerdesLane0RxEq_HHD_serdesLane0RxEqBestEyeValue u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesLane0RxEqBestEyeValue in AQ_GlobalCommonSerdesLane0RxEq_HHD */
#define word_AQ_GlobalCommonSerdesLane0RxEq_HHD_serdesLane0RxEqBestEyeValue u0.word_0

/*! \brief Base register address of structure AQ_GlobalCommonSerdesLane1RxEq_HHD */
#define AQ_GlobalCommonSerdesLane1RxEq_HHD_baseRegisterAddress 0x2D65
/*! \brief MMD address of structure AQ_GlobalCommonSerdesLane1RxEq_HHD */
#define AQ_GlobalCommonSerdesLane1RxEq_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure serdesLane1RxEqDone in AQ_GlobalCommonSerdesLane1RxEq_HHD */
#define AQ_GlobalCommonSerdesLane1RxEq_HHD_serdesLane1RxEqDone 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesLane1RxEqDone in AQ_GlobalCommonSerdesLane1RxEq_HHD */
#define bits_AQ_GlobalCommonSerdesLane1RxEq_HHD_serdesLane1RxEqDone u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesLane1RxEqDone in AQ_GlobalCommonSerdesLane1RxEq_HHD */
#define word_AQ_GlobalCommonSerdesLane1RxEq_HHD_serdesLane1RxEqDone u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesLane1RxEqBestEyeValue in AQ_GlobalCommonSerdesLane1RxEq_HHD */
#define AQ_GlobalCommonSerdesLane1RxEq_HHD_serdesLane1RxEqBestEyeValue 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesLane1RxEqBestEyeValue in AQ_GlobalCommonSerdesLane1RxEq_HHD */
#define bits_AQ_GlobalCommonSerdesLane1RxEq_HHD_serdesLane1RxEqBestEyeValue u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesLane1RxEqBestEyeValue in AQ_GlobalCommonSerdesLane1RxEq_HHD */
#define word_AQ_GlobalCommonSerdesLane1RxEq_HHD_serdesLane1RxEqBestEyeValue u0.word_0

/*! \brief Base register address of structure AQ_GlobalControl_HHD */
#define AQ_GlobalControl_HHD_baseRegisterAddress 0xC000
/*! \brief MMD address of structure AQ_GlobalControl_HHD */
#define AQ_GlobalControl_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure upReset in AQ_GlobalControl_HHD */
#define AQ_GlobalControl_HHD_upReset 1
/*! \brief Preprocessor variable to relate field to bit position in structure upReset in AQ_GlobalControl_HHD */
#define bits_AQ_GlobalControl_HHD_upReset u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure upReset in AQ_GlobalControl_HHD */
#define word_AQ_GlobalControl_HHD_upReset u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure upRunStallOverride in AQ_GlobalControl_HHD */
#define AQ_GlobalControl_HHD_upRunStallOverride 1
/*! \brief Preprocessor variable to relate field to bit position in structure upRunStallOverride in AQ_GlobalControl_HHD */
#define bits_AQ_GlobalControl_HHD_upRunStallOverride u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure upRunStallOverride in AQ_GlobalControl_HHD */
#define word_AQ_GlobalControl_HHD_upRunStallOverride u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure upRunStall in AQ_GlobalControl_HHD */
#define AQ_GlobalControl_HHD_upRunStall 1
/*! \brief Preprocessor variable to relate field to bit position in structure upRunStall in AQ_GlobalControl_HHD */
#define bits_AQ_GlobalControl_HHD_upRunStall u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure upRunStall in AQ_GlobalControl_HHD */
#define word_AQ_GlobalControl_HHD_upRunStall u1.word_1

/*! \brief Base register address of structure AQ_GlobalResetControl_HHD */
#define AQ_GlobalResetControl_HHD_baseRegisterAddress 0xC006
/*! \brief MMD address of structure AQ_GlobalResetControl_HHD */
#define AQ_GlobalResetControl_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure globalMMD_ResetDisable in AQ_GlobalResetControl_HHD */
#define AQ_GlobalResetControl_HHD_globalMMD_ResetDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalMMD_ResetDisable in AQ_GlobalResetControl_HHD */
#define bits_AQ_GlobalResetControl_HHD_globalMMD_ResetDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalMMD_ResetDisable in AQ_GlobalResetControl_HHD */
#define word_AQ_GlobalResetControl_HHD_globalMMD_ResetDisable u0.word_0

/*! \brief Base register address of structure AQ_GlobalDiagnosticProvisioning_HHD */
#define AQ_GlobalDiagnosticProvisioning_HHD_baseRegisterAddress 0xC400
/*! \brief MMD address of structure AQ_GlobalDiagnosticProvisioning_HHD */
#define AQ_GlobalDiagnosticProvisioning_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure enableDiagnostics in AQ_GlobalDiagnosticProvisioning_HHD */
#define AQ_GlobalDiagnosticProvisioning_HHD_enableDiagnostics 0
/*! \brief Preprocessor variable to relate field to bit position in structure enableDiagnostics in AQ_GlobalDiagnosticProvisioning_HHD */
#define bits_AQ_GlobalDiagnosticProvisioning_HHD_enableDiagnostics u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure enableDiagnostics in AQ_GlobalDiagnosticProvisioning_HHD */
#define word_AQ_GlobalDiagnosticProvisioning_HHD_enableDiagnostics u0.word_0

/*! \brief Base register address of structure AQ_GlobalThermalProvisioning_HHD */
#define AQ_GlobalThermalProvisioning_HHD_baseRegisterAddress 0xC420
/*! \brief MMD address of structure AQ_GlobalThermalProvisioning_HHD */
#define AQ_GlobalThermalProvisioning_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure reserved_0 in AQ_GlobalThermalProvisioning_HHD */
#define AQ_GlobalThermalProvisioning_HHD_reserved_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_0 in AQ_GlobalThermalProvisioning_HHD */
#define bits_AQ_GlobalThermalProvisioning_HHD_reserved_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_0 in AQ_GlobalThermalProvisioning_HHD */
#define word_AQ_GlobalThermalProvisioning_HHD_reserved_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure highTempFailureThreshold in AQ_GlobalThermalProvisioning_HHD */
#define AQ_GlobalThermalProvisioning_HHD_highTempFailureThreshold 1
/*! \brief Preprocessor variable to relate field to bit position in structure highTempFailureThreshold in AQ_GlobalThermalProvisioning_HHD */
#define bits_AQ_GlobalThermalProvisioning_HHD_highTempFailureThreshold u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure highTempFailureThreshold in AQ_GlobalThermalProvisioning_HHD */
#define word_AQ_GlobalThermalProvisioning_HHD_highTempFailureThreshold u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure lowTempFailureThreshold in AQ_GlobalThermalProvisioning_HHD */
#define AQ_GlobalThermalProvisioning_HHD_lowTempFailureThreshold 2
/*! \brief Preprocessor variable to relate field to bit position in structure lowTempFailureThreshold in AQ_GlobalThermalProvisioning_HHD */
#define bits_AQ_GlobalThermalProvisioning_HHD_lowTempFailureThreshold u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure lowTempFailureThreshold in AQ_GlobalThermalProvisioning_HHD */
#define word_AQ_GlobalThermalProvisioning_HHD_lowTempFailureThreshold u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure highTempWarningThreshold in AQ_GlobalThermalProvisioning_HHD */
#define AQ_GlobalThermalProvisioning_HHD_highTempWarningThreshold 3
/*! \brief Preprocessor variable to relate field to bit position in structure highTempWarningThreshold in AQ_GlobalThermalProvisioning_HHD */
#define bits_AQ_GlobalThermalProvisioning_HHD_highTempWarningThreshold u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure highTempWarningThreshold in AQ_GlobalThermalProvisioning_HHD */
#define word_AQ_GlobalThermalProvisioning_HHD_highTempWarningThreshold u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure lowTempWarningThreshold in AQ_GlobalThermalProvisioning_HHD */
#define AQ_GlobalThermalProvisioning_HHD_lowTempWarningThreshold 4
/*! \brief Preprocessor variable to relate field to bit position in structure lowTempWarningThreshold in AQ_GlobalThermalProvisioning_HHD */
#define bits_AQ_GlobalThermalProvisioning_HHD_lowTempWarningThreshold u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure lowTempWarningThreshold in AQ_GlobalThermalProvisioning_HHD */
#define word_AQ_GlobalThermalProvisioning_HHD_lowTempWarningThreshold u4.word_4

/*! \brief Base register address of structure AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_baseRegisterAddress 0xC430
/*! \brief MMD address of structure AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure led_0_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_0_5Gb_sLinkEstablished 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_0_5Gb_sLinkEstablished u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_0_5Gb_sLinkEstablished u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_0_2_5Gb_sLinkEstablished 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_0_2_5Gb_sLinkEstablished u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_0_2_5Gb_sLinkEstablished u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioningC430 in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_reservedProvisioningC430 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioningC430 in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_reservedProvisioningC430 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioningC430 in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_reservedProvisioningC430 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0ManualSet in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_0ManualSet 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0ManualSet in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_0ManualSet u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0ManualSet in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_0ManualSet u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_0_10Gb_sLinkEstablished 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_0_10Gb_sLinkEstablished u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_0_10Gb_sLinkEstablished u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_0_1Gb_sLinkEstablished 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_0_1Gb_sLinkEstablished u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_0_1Gb_sLinkEstablished u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_0_100Mb_sLinkEstablished 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_0_100Mb_sLinkEstablished u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_0_100Mb_sLinkEstablished u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0Connecting in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_0Connecting 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0Connecting in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_0Connecting u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0Connecting in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_0Connecting u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0ReceiveActivity in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_0ReceiveActivity 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0ReceiveActivity in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_0ReceiveActivity u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0ReceiveActivity in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_0ReceiveActivity u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0TransmitActivity in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_0TransmitActivity 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0TransmitActivity in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_0TransmitActivity u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0TransmitActivity in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_0TransmitActivity u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_0ActivityStretch in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_0ActivityStretch 0
/*! \brief Preprocessor variable to relate field to bit position in structure led_0ActivityStretch in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_0ActivityStretch u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure led_0ActivityStretch in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_0ActivityStretch u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure led_1_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_1_5Gb_sLinkEstablished 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_1_5Gb_sLinkEstablished u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_1_5Gb_sLinkEstablished u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_1_2_5Gb_sLinkEstablished 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_1_2_5Gb_sLinkEstablished u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_1_2_5Gb_sLinkEstablished u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioningC431 in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_reservedProvisioningC431 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioningC431 in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_reservedProvisioningC431 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioningC431 in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_reservedProvisioningC431 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1ManualSet in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_1ManualSet 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1ManualSet in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_1ManualSet u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1ManualSet in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_1ManualSet u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_1_10Gb_sLinkEstablished 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_1_10Gb_sLinkEstablished u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_1_10Gb_sLinkEstablished u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_1_1Gb_sLinkEstablished 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_1_1Gb_sLinkEstablished u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_1_1Gb_sLinkEstablished u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_1_100Mb_sLinkEstablished 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_1_100Mb_sLinkEstablished u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_1_100Mb_sLinkEstablished u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1Connecting in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_1Connecting 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1Connecting in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_1Connecting u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1Connecting in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_1Connecting u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1ReceiveActivity in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_1ReceiveActivity 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1ReceiveActivity in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_1ReceiveActivity u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1ReceiveActivity in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_1ReceiveActivity u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1TransmitActivity in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_1TransmitActivity 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1TransmitActivity in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_1TransmitActivity u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1TransmitActivity in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_1TransmitActivity u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_1ActivityStretch in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_1ActivityStretch 1
/*! \brief Preprocessor variable to relate field to bit position in structure led_1ActivityStretch in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_1ActivityStretch u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure led_1ActivityStretch in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_1ActivityStretch u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure led_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_2_5Gb_sLinkEstablished 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_2_5Gb_sLinkEstablished u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_2_5Gb_sLinkEstablished u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_2_2_5Gb_sLinkEstablished 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_2_2_5Gb_sLinkEstablished u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2_2_5Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_2_2_5Gb_sLinkEstablished u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioningC432 in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_reservedProvisioningC432 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioningC432 in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_reservedProvisioningC432 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioningC432 in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_reservedProvisioningC432 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2ManualSet in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_2ManualSet 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2ManualSet in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_2ManualSet u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2ManualSet in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_2ManualSet u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_2_10Gb_sLinkEstablished 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_2_10Gb_sLinkEstablished u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2_10Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_2_10Gb_sLinkEstablished u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_2_1Gb_sLinkEstablished 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_2_1Gb_sLinkEstablished u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2_1Gb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_2_1Gb_sLinkEstablished u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_2_100Mb_sLinkEstablished 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_2_100Mb_sLinkEstablished u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2_100Mb_sLinkEstablished in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_2_100Mb_sLinkEstablished u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2Connecting in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_2Connecting 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2Connecting in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_2Connecting u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2Connecting in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_2Connecting u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2ReceiveActivity in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_2ReceiveActivity 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2ReceiveActivity in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_2ReceiveActivity u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2ReceiveActivity in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_2ReceiveActivity u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2TransmitActivity in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_2TransmitActivity 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2TransmitActivity in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_2TransmitActivity u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2TransmitActivity in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_2TransmitActivity u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure led_2ActivityStretch in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_led_2ActivityStretch 2
/*! \brief Preprocessor variable to relate field to bit position in structure led_2ActivityStretch in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_led_2ActivityStretch u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure led_2ActivityStretch in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_led_2ActivityStretch u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure ledOperationMode in AQ_GlobalLedProvisioning_HHD */
#define AQ_GlobalLedProvisioning_HHD_ledOperationMode 7
/*! \brief Preprocessor variable to relate field to bit position in structure ledOperationMode in AQ_GlobalLedProvisioning_HHD */
#define bits_AQ_GlobalLedProvisioning_HHD_ledOperationMode u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure ledOperationMode in AQ_GlobalLedProvisioning_HHD */
#define word_AQ_GlobalLedProvisioning_HHD_ledOperationMode u7.word_7

/*! \brief Base register address of structure AQ_GlobalGeneralProvisioning_HHD */
#define AQ_GlobalGeneralProvisioning_HHD_baseRegisterAddress 0xC440
/*! \brief MMD address of structure AQ_GlobalGeneralProvisioning_HHD */
#define AQ_GlobalGeneralProvisioning_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure mdioBroadcastModeEnable in AQ_GlobalGeneralProvisioning_HHD */
#define AQ_GlobalGeneralProvisioning_HHD_mdioBroadcastModeEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mdioBroadcastModeEnable in AQ_GlobalGeneralProvisioning_HHD */
#define bits_AQ_GlobalGeneralProvisioning_HHD_mdioBroadcastModeEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mdioBroadcastModeEnable in AQ_GlobalGeneralProvisioning_HHD */
#define word_AQ_GlobalGeneralProvisioning_HHD_mdioBroadcastModeEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mdioReadMSW_FirstEnable in AQ_GlobalGeneralProvisioning_HHD */
#define AQ_GlobalGeneralProvisioning_HHD_mdioReadMSW_FirstEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mdioReadMSW_FirstEnable in AQ_GlobalGeneralProvisioning_HHD */
#define bits_AQ_GlobalGeneralProvisioning_HHD_mdioReadMSW_FirstEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mdioReadMSW_FirstEnable in AQ_GlobalGeneralProvisioning_HHD */
#define word_AQ_GlobalGeneralProvisioning_HHD_mdioReadMSW_FirstEnable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mdioDriveConfiguration in AQ_GlobalGeneralProvisioning_HHD */
#define AQ_GlobalGeneralProvisioning_HHD_mdioDriveConfiguration 1
/*! \brief Preprocessor variable to relate field to bit position in structure mdioDriveConfiguration in AQ_GlobalGeneralProvisioning_HHD */
#define bits_AQ_GlobalGeneralProvisioning_HHD_mdioDriveConfiguration u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mdioDriveConfiguration in AQ_GlobalGeneralProvisioning_HHD */
#define word_AQ_GlobalGeneralProvisioning_HHD_mdioDriveConfiguration u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mdioPreambleDetectionDisable in AQ_GlobalGeneralProvisioning_HHD */
#define AQ_GlobalGeneralProvisioning_HHD_mdioPreambleDetectionDisable 1
/*! \brief Preprocessor variable to relate field to bit position in structure mdioPreambleDetectionDisable in AQ_GlobalGeneralProvisioning_HHD */
#define bits_AQ_GlobalGeneralProvisioning_HHD_mdioPreambleDetectionDisable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mdioPreambleDetectionDisable in AQ_GlobalGeneralProvisioning_HHD */
#define word_AQ_GlobalGeneralProvisioning_HHD_mdioPreambleDetectionDisable u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure daisyChainReset in AQ_GlobalGeneralProvisioning_HHD */
#define AQ_GlobalGeneralProvisioning_HHD_daisyChainReset 2
/*! \brief Preprocessor variable to relate field to bit position in structure daisyChainReset in AQ_GlobalGeneralProvisioning_HHD */
#define bits_AQ_GlobalGeneralProvisioning_HHD_daisyChainReset u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure daisyChainReset in AQ_GlobalGeneralProvisioning_HHD */
#define word_AQ_GlobalGeneralProvisioning_HHD_daisyChainReset u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mdioBroadcastAddressConfiguration in AQ_GlobalGeneralProvisioning_HHD */
#define AQ_GlobalGeneralProvisioning_HHD_mdioBroadcastAddressConfiguration 7
/*! \brief Preprocessor variable to relate field to bit position in structure mdioBroadcastAddressConfiguration in AQ_GlobalGeneralProvisioning_HHD */
#define bits_AQ_GlobalGeneralProvisioning_HHD_mdioBroadcastAddressConfiguration u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure mdioBroadcastAddressConfiguration in AQ_GlobalGeneralProvisioning_HHD */
#define word_AQ_GlobalGeneralProvisioning_HHD_mdioBroadcastAddressConfiguration u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure mdioPreambleLength in AQ_GlobalGeneralProvisioning_HHD */
#define AQ_GlobalGeneralProvisioning_HHD_mdioPreambleLength 9
/*! \brief Preprocessor variable to relate field to bit position in structure mdioPreambleLength in AQ_GlobalGeneralProvisioning_HHD */
#define bits_AQ_GlobalGeneralProvisioning_HHD_mdioPreambleLength u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure mdioPreambleLength in AQ_GlobalGeneralProvisioning_HHD */
#define word_AQ_GlobalGeneralProvisioning_HHD_mdioPreambleLength u9.word_9

/*! \brief Base register address of structure AQ_GlobalNvrProvisioning_HHD */
#define AQ_GlobalNvrProvisioning_HHD_baseRegisterAddress 0xC450
/*! \brief MMD address of structure AQ_GlobalNvrProvisioning_HHD */
#define AQ_GlobalNvrProvisioning_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure nvrDataLength in AQ_GlobalNvrProvisioning_HHD */
#define AQ_GlobalNvrProvisioning_HHD_nvrDataLength 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDataLength in AQ_GlobalNvrProvisioning_HHD */
#define bits_AQ_GlobalNvrProvisioning_HHD_nvrDataLength u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrDataLength in AQ_GlobalNvrProvisioning_HHD */
#define word_AQ_GlobalNvrProvisioning_HHD_nvrDataLength u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrDummyLength in AQ_GlobalNvrProvisioning_HHD */
#define AQ_GlobalNvrProvisioning_HHD_nvrDummyLength 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDummyLength in AQ_GlobalNvrProvisioning_HHD */
#define bits_AQ_GlobalNvrProvisioning_HHD_nvrDummyLength u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrDummyLength in AQ_GlobalNvrProvisioning_HHD */
#define word_AQ_GlobalNvrProvisioning_HHD_nvrDummyLength u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrAddressLength in AQ_GlobalNvrProvisioning_HHD */
#define AQ_GlobalNvrProvisioning_HHD_nvrAddressLength 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrAddressLength in AQ_GlobalNvrProvisioning_HHD */
#define bits_AQ_GlobalNvrProvisioning_HHD_nvrAddressLength u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrAddressLength in AQ_GlobalNvrProvisioning_HHD */
#define word_AQ_GlobalNvrProvisioning_HHD_nvrAddressLength u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrAddressLengthOverride in AQ_GlobalNvrProvisioning_HHD */
#define AQ_GlobalNvrProvisioning_HHD_nvrAddressLengthOverride 1
/*! \brief Preprocessor variable to relate field to bit position in structure nvrAddressLengthOverride in AQ_GlobalNvrProvisioning_HHD */
#define bits_AQ_GlobalNvrProvisioning_HHD_nvrAddressLengthOverride u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure nvrAddressLengthOverride in AQ_GlobalNvrProvisioning_HHD */
#define word_AQ_GlobalNvrProvisioning_HHD_nvrAddressLengthOverride u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure nvrClockDivide in AQ_GlobalNvrProvisioning_HHD */
#define AQ_GlobalNvrProvisioning_HHD_nvrClockDivide 1
/*! \brief Preprocessor variable to relate field to bit position in structure nvrClockDivide in AQ_GlobalNvrProvisioning_HHD */
#define bits_AQ_GlobalNvrProvisioning_HHD_nvrClockDivide u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure nvrClockDivide in AQ_GlobalNvrProvisioning_HHD */
#define word_AQ_GlobalNvrProvisioning_HHD_nvrClockDivide u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure nvrDaisyChainClockDivideOverride in AQ_GlobalNvrProvisioning_HHD */
#define AQ_GlobalNvrProvisioning_HHD_nvrDaisyChainClockDivideOverride 2
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDaisyChainClockDivideOverride in AQ_GlobalNvrProvisioning_HHD */
#define bits_AQ_GlobalNvrProvisioning_HHD_nvrDaisyChainClockDivideOverride u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure nvrDaisyChainClockDivideOverride in AQ_GlobalNvrProvisioning_HHD */
#define word_AQ_GlobalNvrProvisioning_HHD_nvrDaisyChainClockDivideOverride u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure nvrDaisyChainDisable in AQ_GlobalNvrProvisioning_HHD */
#define AQ_GlobalNvrProvisioning_HHD_nvrDaisyChainDisable 2
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDaisyChainDisable in AQ_GlobalNvrProvisioning_HHD */
#define bits_AQ_GlobalNvrProvisioning_HHD_nvrDaisyChainDisable u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure nvrDaisyChainDisable in AQ_GlobalNvrProvisioning_HHD */
#define word_AQ_GlobalNvrProvisioning_HHD_nvrDaisyChainDisable u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure nvrReset in AQ_GlobalNvrProvisioning_HHD */
#define AQ_GlobalNvrProvisioning_HHD_nvrReset 3
/*! \brief Preprocessor variable to relate field to bit position in structure nvrReset in AQ_GlobalNvrProvisioning_HHD */
#define bits_AQ_GlobalNvrProvisioning_HHD_nvrReset u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure nvrReset in AQ_GlobalNvrProvisioning_HHD */
#define word_AQ_GlobalNvrProvisioning_HHD_nvrReset u3.word_3

/*! \brief Base register address of structure AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_baseRegisterAddress 0xC470
/*! \brief MMD address of structure AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure diagnosticsSelect in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_diagnosticsSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure diagnosticsSelect in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_diagnosticsSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure diagnosticsSelect in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_diagnosticsSelect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extendedMdiDiagnosticsSelect in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_extendedMdiDiagnosticsSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedMdiDiagnosticsSelect in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_extendedMdiDiagnosticsSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedMdiDiagnosticsSelect in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_extendedMdiDiagnosticsSelect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure triggerDiagnosticInterrupt in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_triggerDiagnosticInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure triggerDiagnosticInterrupt in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_triggerDiagnosticInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure triggerDiagnosticInterrupt in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_triggerDiagnosticInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure initiateCableDiagnostics in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_initiateCableDiagnostics 0
/*! \brief Preprocessor variable to relate field to bit position in structure initiateCableDiagnostics in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_initiateCableDiagnostics u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure initiateCableDiagnostics in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_initiateCableDiagnostics u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure enableDaisy_chainHop_countOverride in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_enableDaisy_chainHop_countOverride 1
/*! \brief Preprocessor variable to relate field to bit position in structure enableDaisy_chainHop_countOverride in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_enableDaisy_chainHop_countOverride u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure enableDaisy_chainHop_countOverride in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_enableDaisy_chainHop_countOverride u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure daisy_chainHop_countOverrideValue in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_daisy_chainHop_countOverrideValue 1
/*! \brief Preprocessor variable to relate field to bit position in structure daisy_chainHop_countOverrideValue in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_daisy_chainHop_countOverrideValue u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure daisy_chainHop_countOverrideValue in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_daisy_chainHop_countOverrideValue u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure enableVddPowerSupplyTuning in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_enableVddPowerSupplyTuning 2
/*! \brief Preprocessor variable to relate field to bit position in structure enableVddPowerSupplyTuning in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_enableVddPowerSupplyTuning u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure enableVddPowerSupplyTuning in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_enableVddPowerSupplyTuning u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure tunableExternalVddPowerSupplyPresent in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_tunableExternalVddPowerSupplyPresent 2
/*! \brief Preprocessor variable to relate field to bit position in structure tunableExternalVddPowerSupplyPresent in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_tunableExternalVddPowerSupplyPresent u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure tunableExternalVddPowerSupplyPresent in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_tunableExternalVddPowerSupplyPresent u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure externalVddChangeRequest in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_externalVddChangeRequest 2
/*! \brief Preprocessor variable to relate field to bit position in structure externalVddChangeRequest in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_externalVddChangeRequest u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure externalVddChangeRequest in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_externalVddChangeRequest u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure enableXenpakRegisterSpace in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_enableXenpakRegisterSpace 2
/*! \brief Preprocessor variable to relate field to bit position in structure enableXenpakRegisterSpace in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_enableXenpakRegisterSpace u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure enableXenpakRegisterSpace in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_enableXenpakRegisterSpace u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure enable_5thChannelRfiCancellation in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_enable_5thChannelRfiCancellation 2
/*! \brief Preprocessor variable to relate field to bit position in structure enable_5thChannelRfiCancellation in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_enable_5thChannelRfiCancellation u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure enable_5thChannelRfiCancellation in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_enable_5thChannelRfiCancellation u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure rateTransitionRequest in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_rateTransitionRequest 3
/*! \brief Preprocessor variable to relate field to bit position in structure rateTransitionRequest in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_rateTransitionRequest u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure rateTransitionRequest in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_rateTransitionRequest u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure trainingSNR in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_trainingSNR 3
/*! \brief Preprocessor variable to relate field to bit position in structure trainingSNR in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_trainingSNR u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure trainingSNR in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_trainingSNR u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_5 in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_5 4
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_5 in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_5 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_5 in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_5 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure nvrDaisyChainKickstart in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_nvrDaisyChainKickstart 4
/*! \brief Preprocessor variable to relate field to bit position in structure nvrDaisyChainKickstart in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_nvrDaisyChainKickstart u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure nvrDaisyChainKickstart in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_nvrDaisyChainKickstart u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure smartPower_downStatus in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_smartPower_downStatus 5
/*! \brief Preprocessor variable to relate field to bit position in structure smartPower_downStatus in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_smartPower_downStatus u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure smartPower_downStatus in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_smartPower_downStatus u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_6 in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_6 5
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_6 in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_6 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_6 in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_6 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrLpDisableTimer in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_cfrLpDisableTimer 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrLpDisableTimer in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_cfrLpDisableTimer u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrLpDisableTimer in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_cfrLpDisableTimer u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrLpExtendedMaxwait in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_cfrLpExtendedMaxwait 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrLpExtendedMaxwait in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_cfrLpExtendedMaxwait u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrLpExtendedMaxwait in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_cfrLpExtendedMaxwait u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrLpTHP in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_cfrLpTHP 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrLpTHP in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_cfrLpTHP u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrLpTHP in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_cfrLpTHP u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrLpSupport in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_cfrLpSupport 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrLpSupport in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_cfrLpSupport u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrLpSupport in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_cfrLpSupport u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrDisableTimer in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_cfrDisableTimer 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrDisableTimer in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_cfrDisableTimer u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrDisableTimer in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_cfrDisableTimer u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrExtendedMaxwait in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_cfrExtendedMaxwait 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrExtendedMaxwait in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_cfrExtendedMaxwait u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrExtendedMaxwait in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_cfrExtendedMaxwait u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrTHP in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_cfrTHP 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrTHP in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_cfrTHP u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrTHP in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_cfrTHP u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure cfrSupport in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_cfrSupport 5
/*! \brief Preprocessor variable to relate field to bit position in structure cfrSupport in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_cfrSupport u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure cfrSupport in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_cfrSupport u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure deadlockAvoidanceEnable in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_deadlockAvoidanceEnable 5
/*! \brief Preprocessor variable to relate field to bit position in structure deadlockAvoidanceEnable in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_deadlockAvoidanceEnable u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure deadlockAvoidanceEnable in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_deadlockAvoidanceEnable u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure smartPower_downEnable in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_smartPower_downEnable 5
/*! \brief Preprocessor variable to relate field to bit position in structure smartPower_downEnable in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_smartPower_downEnable u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure smartPower_downEnable in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_smartPower_downEnable u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure dteEnable in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_dteEnable 8
/*! \brief Preprocessor variable to relate field to bit position in structure dteEnable in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_dteEnable u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure dteEnable in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_dteEnable u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure dteDropReportingTimer in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_dteDropReportingTimer 8
/*! \brief Preprocessor variable to relate field to bit position in structure dteDropReportingTimer in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_dteDropReportingTimer u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure dteDropReportingTimer in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_dteDropReportingTimer u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure thermalShutdownEnable in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_thermalShutdownEnable 8
/*! \brief Preprocessor variable to relate field to bit position in structure thermalShutdownEnable in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_thermalShutdownEnable u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure thermalShutdownEnable in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_thermalShutdownEnable u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_9 in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_9 8
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_9 in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_9 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_9 in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_9 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure powerUpStall in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_powerUpStall 9
/*! \brief Preprocessor variable to relate field to bit position in structure powerUpStall in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_powerUpStall u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure powerUpStall in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_powerUpStall u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_10 in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_10 9
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_10 in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_10 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_10 in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_10 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure loopbackControl in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_loopbackControl 10
/*! \brief Preprocessor variable to relate field to bit position in structure loopbackControl in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_loopbackControl u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure loopbackControl in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_loopbackControl u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_11 in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_11 10
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_11 in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_11 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_11 in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_11 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure mdiPacketGeneration in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_mdiPacketGeneration 10
/*! \brief Preprocessor variable to relate field to bit position in structure mdiPacketGeneration in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_mdiPacketGeneration u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure mdiPacketGeneration in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_mdiPacketGeneration u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure look_asidePortPacketGeneration in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_look_asidePortPacketGeneration 10
/*! \brief Preprocessor variable to relate field to bit position in structure look_asidePortPacketGeneration in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_look_asidePortPacketGeneration u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure look_asidePortPacketGeneration in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_look_asidePortPacketGeneration u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure systemI_fPacketGeneration in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_systemI_fPacketGeneration 10
/*! \brief Preprocessor variable to relate field to bit position in structure systemI_fPacketGeneration in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_systemI_fPacketGeneration u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure systemI_fPacketGeneration in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_systemI_fPacketGeneration u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure rate in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_rate 10
/*! \brief Preprocessor variable to relate field to bit position in structure rate in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_rate u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure rate in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_rate u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_12 in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_12 11
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_12 in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_12 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_12 in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_reservedProvisioning_12 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure enableMacsec in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_enableMacsec 11
/*! \brief Preprocessor variable to relate field to bit position in structure enableMacsec in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_enableMacsec u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure enableMacsec in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_enableMacsec u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure enablePtp in AQ_GlobalReservedProvisioning_HHD */
#define AQ_GlobalReservedProvisioning_HHD_enablePtp 11
/*! \brief Preprocessor variable to relate field to bit position in structure enablePtp in AQ_GlobalReservedProvisioning_HHD */
#define bits_AQ_GlobalReservedProvisioning_HHD_enablePtp u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure enablePtp in AQ_GlobalReservedProvisioning_HHD */
#define word_AQ_GlobalReservedProvisioning_HHD_enablePtp u11.word_11

/*! \brief Base register address of structure AQ_PifMailboxControl_HHD */
#define AQ_PifMailboxControl_HHD_baseRegisterAddress 0xC47C
/*! \brief MMD address of structure AQ_PifMailboxControl_HHD */
#define AQ_PifMailboxControl_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure pifMailboxAddress in AQ_PifMailboxControl_HHD */
#define AQ_PifMailboxControl_HHD_pifMailboxAddress 0
/*! \brief Preprocessor variable to relate field to bit position in structure pifMailboxAddress in AQ_PifMailboxControl_HHD */
#define bits_AQ_PifMailboxControl_HHD_pifMailboxAddress u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pifMailboxAddress in AQ_PifMailboxControl_HHD */
#define word_AQ_PifMailboxControl_HHD_pifMailboxAddress u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pifMailboxData in AQ_PifMailboxControl_HHD */
#define AQ_PifMailboxControl_HHD_pifMailboxData 1
/*! \brief Preprocessor variable to relate field to bit position in structure pifMailboxData in AQ_PifMailboxControl_HHD */
#define bits_AQ_PifMailboxControl_HHD_pifMailboxData u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pifMailboxData in AQ_PifMailboxControl_HHD */
#define word_AQ_PifMailboxControl_HHD_pifMailboxData u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedPifMailboxControl_3 in AQ_PifMailboxControl_HHD */
#define AQ_PifMailboxControl_HHD_reservedPifMailboxControl_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPifMailboxControl_3 in AQ_PifMailboxControl_HHD */
#define bits_AQ_PifMailboxControl_HHD_reservedPifMailboxControl_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedPifMailboxControl_3 in AQ_PifMailboxControl_HHD */
#define word_AQ_PifMailboxControl_HHD_reservedPifMailboxControl_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure serviceSecondRegister in AQ_PifMailboxControl_HHD */
#define AQ_PifMailboxControl_HHD_serviceSecondRegister 2
/*! \brief Preprocessor variable to relate field to bit position in structure serviceSecondRegister in AQ_PifMailboxControl_HHD */
#define bits_AQ_PifMailboxControl_HHD_serviceSecondRegister u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure serviceSecondRegister in AQ_PifMailboxControl_HHD */
#define word_AQ_PifMailboxControl_HHD_serviceSecondRegister u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pifMailboxCommandType in AQ_PifMailboxControl_HHD */
#define AQ_PifMailboxControl_HHD_pifMailboxCommandType 2
/*! \brief Preprocessor variable to relate field to bit position in structure pifMailboxCommandType in AQ_PifMailboxControl_HHD */
#define bits_AQ_PifMailboxControl_HHD_pifMailboxCommandType u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure pifMailboxCommandType in AQ_PifMailboxControl_HHD */
#define word_AQ_PifMailboxControl_HHD_pifMailboxCommandType u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pifMailboxMMD in AQ_PifMailboxControl_HHD */
#define AQ_PifMailboxControl_HHD_pifMailboxMMD 2
/*! \brief Preprocessor variable to relate field to bit position in structure pifMailboxMMD in AQ_PifMailboxControl_HHD */
#define bits_AQ_PifMailboxControl_HHD_pifMailboxMMD u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure pifMailboxMMD in AQ_PifMailboxControl_HHD */
#define word_AQ_PifMailboxControl_HHD_pifMailboxMMD u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedPifMailboxControl_4 in AQ_PifMailboxControl_HHD */
#define AQ_PifMailboxControl_HHD_reservedPifMailboxControl_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPifMailboxControl_4 in AQ_PifMailboxControl_HHD */
#define bits_AQ_PifMailboxControl_HHD_reservedPifMailboxControl_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedPifMailboxControl_4 in AQ_PifMailboxControl_HHD */
#define word_AQ_PifMailboxControl_HHD_reservedPifMailboxControl_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure pifMailboxCommandStatus in AQ_PifMailboxControl_HHD */
#define AQ_PifMailboxControl_HHD_pifMailboxCommandStatus 3
/*! \brief Preprocessor variable to relate field to bit position in structure pifMailboxCommandStatus in AQ_PifMailboxControl_HHD */
#define bits_AQ_PifMailboxControl_HHD_pifMailboxCommandStatus u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pifMailboxCommandStatus in AQ_PifMailboxControl_HHD */
#define word_AQ_PifMailboxControl_HHD_pifMailboxCommandStatus u3.word_3

/*! \brief Base register address of structure AQ_GlobalSmbus_0Provisioning_HHD */
#define AQ_GlobalSmbus_0Provisioning_HHD_baseRegisterAddress 0xC485
/*! \brief MMD address of structure AQ_GlobalSmbus_0Provisioning_HHD */
#define AQ_GlobalSmbus_0Provisioning_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure smb_0SlaveAddress in AQ_GlobalSmbus_0Provisioning_HHD */
#define AQ_GlobalSmbus_0Provisioning_HHD_smb_0SlaveAddress 0
/*! \brief Preprocessor variable to relate field to bit position in structure smb_0SlaveAddress in AQ_GlobalSmbus_0Provisioning_HHD */
#define bits_AQ_GlobalSmbus_0Provisioning_HHD_smb_0SlaveAddress u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure smb_0SlaveAddress in AQ_GlobalSmbus_0Provisioning_HHD */
#define word_AQ_GlobalSmbus_0Provisioning_HHD_smb_0SlaveAddress u0.word_0

/*! \brief Base register address of structure AQ_GlobalSmbus_1Provisioning_HHD */
#define AQ_GlobalSmbus_1Provisioning_HHD_baseRegisterAddress 0xC495
/*! \brief MMD address of structure AQ_GlobalSmbus_1Provisioning_HHD */
#define AQ_GlobalSmbus_1Provisioning_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure smb_1SlaveAddress in AQ_GlobalSmbus_1Provisioning_HHD */
#define AQ_GlobalSmbus_1Provisioning_HHD_smb_1SlaveAddress 0
/*! \brief Preprocessor variable to relate field to bit position in structure smb_1SlaveAddress in AQ_GlobalSmbus_1Provisioning_HHD */
#define bits_AQ_GlobalSmbus_1Provisioning_HHD_smb_1SlaveAddress u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure smb_1SlaveAddress in AQ_GlobalSmbus_1Provisioning_HHD */
#define word_AQ_GlobalSmbus_1Provisioning_HHD_smb_1SlaveAddress u0.word_0

/*! \brief Base register address of structure AQ_GlobalEeeProvisioning_HHD */
#define AQ_GlobalEeeProvisioning_HHD_baseRegisterAddress 0xC4A0
/*! \brief MMD address of structure AQ_GlobalEeeProvisioning_HHD */
#define AQ_GlobalEeeProvisioning_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure eeeMode in AQ_GlobalEeeProvisioning_HHD */
#define AQ_GlobalEeeProvisioning_HHD_eeeMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure eeeMode in AQ_GlobalEeeProvisioning_HHD */
#define bits_AQ_GlobalEeeProvisioning_HHD_eeeMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure eeeMode in AQ_GlobalEeeProvisioning_HHD */
#define word_AQ_GlobalEeeProvisioning_HHD_eeeMode u0.word_0

/*! \brief Base register address of structure AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_baseRegisterAddress 0xC800
/*! \brief MMD address of structure AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure pairAStatus in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_pairAStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairAStatus in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_pairAStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairAStatus in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_pairAStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairBStatus in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_pairBStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairBStatus in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_pairBStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairBStatus in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_pairBStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairCStatus in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_pairCStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairCStatus in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_pairCStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairCStatus in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_pairCStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairDStatus in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_pairDStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairDStatus in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_pairDStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairDStatus in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_pairDStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairAReflection_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_pairAReflection_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure pairAReflection_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_pairAReflection_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pairAReflection_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_pairAReflection_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure pairAReflection_2 in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_pairAReflection_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure pairAReflection_2 in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_pairAReflection_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pairAReflection_2 in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_pairAReflection_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure impulseResponseMSW in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_impulseResponseMSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure impulseResponseMSW in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_impulseResponseMSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure impulseResponseMSW in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_impulseResponseMSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pairBReflection_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_pairBReflection_1 3
/*! \brief Preprocessor variable to relate field to bit position in structure pairBReflection_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_pairBReflection_1 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pairBReflection_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_pairBReflection_1 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure pairBReflection_2 in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_pairBReflection_2 3
/*! \brief Preprocessor variable to relate field to bit position in structure pairBReflection_2 in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_pairBReflection_2 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pairBReflection_2 in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_pairBReflection_2 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure impulseResponseLSW in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_impulseResponseLSW 4
/*! \brief Preprocessor variable to relate field to bit position in structure impulseResponseLSW in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_impulseResponseLSW u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure impulseResponseLSW in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_impulseResponseLSW u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure pairCReflection_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_pairCReflection_1 5
/*! \brief Preprocessor variable to relate field to bit position in structure pairCReflection_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_pairCReflection_1 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure pairCReflection_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_pairCReflection_1 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure pairCReflection_2 in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_pairCReflection_2 5
/*! \brief Preprocessor variable to relate field to bit position in structure pairCReflection_2 in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_pairCReflection_2 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure pairCReflection_2 in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_pairCReflection_2 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure reserved_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_reserved_1 6
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_reserved_1 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure reserved_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_reserved_1 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure pairDReflection_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_pairDReflection_1 7
/*! \brief Preprocessor variable to relate field to bit position in structure pairDReflection_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_pairDReflection_1 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure pairDReflection_1 in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_pairDReflection_1 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure pairDReflection_2 in AQ_GlobalCableDiagnosticStatus_HHD */
#define AQ_GlobalCableDiagnosticStatus_HHD_pairDReflection_2 7
/*! \brief Preprocessor variable to relate field to bit position in structure pairDReflection_2 in AQ_GlobalCableDiagnosticStatus_HHD */
#define bits_AQ_GlobalCableDiagnosticStatus_HHD_pairDReflection_2 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure pairDReflection_2 in AQ_GlobalCableDiagnosticStatus_HHD */
#define word_AQ_GlobalCableDiagnosticStatus_HHD_pairDReflection_2 u7.word_7

/*! \brief Base register address of structure AQ_GlobalThermalStatus_HHD */
#define AQ_GlobalThermalStatus_HHD_baseRegisterAddress 0xC820
/*! \brief MMD address of structure AQ_GlobalThermalStatus_HHD */
#define AQ_GlobalThermalStatus_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure temperature in AQ_GlobalThermalStatus_HHD */
#define AQ_GlobalThermalStatus_HHD_temperature 0
/*! \brief Preprocessor variable to relate field to bit position in structure temperature in AQ_GlobalThermalStatus_HHD */
#define bits_AQ_GlobalThermalStatus_HHD_temperature u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure temperature in AQ_GlobalThermalStatus_HHD */
#define word_AQ_GlobalThermalStatus_HHD_temperature u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure temperatureReady in AQ_GlobalThermalStatus_HHD */
#define AQ_GlobalThermalStatus_HHD_temperatureReady 1
/*! \brief Preprocessor variable to relate field to bit position in structure temperatureReady in AQ_GlobalThermalStatus_HHD */
#define bits_AQ_GlobalThermalStatus_HHD_temperatureReady u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure temperatureReady in AQ_GlobalThermalStatus_HHD */
#define word_AQ_GlobalThermalStatus_HHD_temperatureReady u1.word_1

/*! \brief Base register address of structure AQ_GlobalGeneralStatus_HHD */
#define AQ_GlobalGeneralStatus_HHD_baseRegisterAddress 0xC830
/*! \brief MMD address of structure AQ_GlobalGeneralStatus_HHD */
#define AQ_GlobalGeneralStatus_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureFailureState in AQ_GlobalGeneralStatus_HHD */
#define AQ_GlobalGeneralStatus_HHD_highTemperatureFailureState 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureFailureState in AQ_GlobalGeneralStatus_HHD */
#define bits_AQ_GlobalGeneralStatus_HHD_highTemperatureFailureState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureFailureState in AQ_GlobalGeneralStatus_HHD */
#define word_AQ_GlobalGeneralStatus_HHD_highTemperatureFailureState u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureFailureState in AQ_GlobalGeneralStatus_HHD */
#define AQ_GlobalGeneralStatus_HHD_lowTemperatureFailureState 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureFailureState in AQ_GlobalGeneralStatus_HHD */
#define bits_AQ_GlobalGeneralStatus_HHD_lowTemperatureFailureState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureFailureState in AQ_GlobalGeneralStatus_HHD */
#define word_AQ_GlobalGeneralStatus_HHD_lowTemperatureFailureState u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureWarningState in AQ_GlobalGeneralStatus_HHD */
#define AQ_GlobalGeneralStatus_HHD_highTemperatureWarningState 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureWarningState in AQ_GlobalGeneralStatus_HHD */
#define bits_AQ_GlobalGeneralStatus_HHD_highTemperatureWarningState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureWarningState in AQ_GlobalGeneralStatus_HHD */
#define word_AQ_GlobalGeneralStatus_HHD_highTemperatureWarningState u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureWarningState in AQ_GlobalGeneralStatus_HHD */
#define AQ_GlobalGeneralStatus_HHD_lowTemperatureWarningState 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureWarningState in AQ_GlobalGeneralStatus_HHD */
#define bits_AQ_GlobalGeneralStatus_HHD_lowTemperatureWarningState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureWarningState in AQ_GlobalGeneralStatus_HHD */
#define word_AQ_GlobalGeneralStatus_HHD_lowTemperatureWarningState u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure processorIntensiveMdioOperationIn_Progress in AQ_GlobalGeneralStatus_HHD */
#define AQ_GlobalGeneralStatus_HHD_processorIntensiveMdioOperationIn_Progress 1
/*! \brief Preprocessor variable to relate field to bit position in structure processorIntensiveMdioOperationIn_Progress in AQ_GlobalGeneralStatus_HHD */
#define bits_AQ_GlobalGeneralStatus_HHD_processorIntensiveMdioOperationIn_Progress u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure processorIntensiveMdioOperationIn_Progress in AQ_GlobalGeneralStatus_HHD */
#define word_AQ_GlobalGeneralStatus_HHD_processorIntensiveMdioOperationIn_Progress u1.word_1

/*! \brief Base register address of structure AQ_GlobalPinStatus_HHD */
#define AQ_GlobalPinStatus_HHD_baseRegisterAddress 0xC840
/*! \brief MMD address of structure AQ_GlobalPinStatus_HHD */
#define AQ_GlobalPinStatus_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure dcMasterN in AQ_GlobalPinStatus_HHD */
#define AQ_GlobalPinStatus_HHD_dcMasterN 0
/*! \brief Preprocessor variable to relate field to bit position in structure dcMasterN in AQ_GlobalPinStatus_HHD */
#define bits_AQ_GlobalPinStatus_HHD_dcMasterN u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure dcMasterN in AQ_GlobalPinStatus_HHD */
#define word_AQ_GlobalPinStatus_HHD_dcMasterN u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure packageConnectivity in AQ_GlobalPinStatus_HHD */
#define AQ_GlobalPinStatus_HHD_packageConnectivity 0
/*! \brief Preprocessor variable to relate field to bit position in structure packageConnectivity in AQ_GlobalPinStatus_HHD */
#define bits_AQ_GlobalPinStatus_HHD_packageConnectivity u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure packageConnectivity in AQ_GlobalPinStatus_HHD */
#define word_AQ_GlobalPinStatus_HHD_packageConnectivity u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure txEnable in AQ_GlobalPinStatus_HHD */
#define AQ_GlobalPinStatus_HHD_txEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure txEnable in AQ_GlobalPinStatus_HHD */
#define bits_AQ_GlobalPinStatus_HHD_txEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure txEnable in AQ_GlobalPinStatus_HHD */
#define word_AQ_GlobalPinStatus_HHD_txEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ledPullupState in AQ_GlobalPinStatus_HHD */
#define AQ_GlobalPinStatus_HHD_ledPullupState 0
/*! \brief Preprocessor variable to relate field to bit position in structure ledPullupState in AQ_GlobalPinStatus_HHD */
#define bits_AQ_GlobalPinStatus_HHD_ledPullupState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ledPullupState in AQ_GlobalPinStatus_HHD */
#define word_AQ_GlobalPinStatus_HHD_ledPullupState u0.word_0

/*! \brief Base register address of structure AQ_GlobalDaisyChainStatus_HHD */
#define AQ_GlobalDaisyChainStatus_HHD_baseRegisterAddress 0xC842
/*! \brief MMD address of structure AQ_GlobalDaisyChainStatus_HHD */
#define AQ_GlobalDaisyChainStatus_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure rxDaisyChainCalculatedCrc in AQ_GlobalDaisyChainStatus_HHD */
#define AQ_GlobalDaisyChainStatus_HHD_rxDaisyChainCalculatedCrc 0
/*! \brief Preprocessor variable to relate field to bit position in structure rxDaisyChainCalculatedCrc in AQ_GlobalDaisyChainStatus_HHD */
#define bits_AQ_GlobalDaisyChainStatus_HHD_rxDaisyChainCalculatedCrc u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rxDaisyChainCalculatedCrc in AQ_GlobalDaisyChainStatus_HHD */
#define word_AQ_GlobalDaisyChainStatus_HHD_rxDaisyChainCalculatedCrc u0.word_0

/*! \brief Base register address of structure AQ_GlobalDaisyChainHopCount_HHD */
#define AQ_GlobalDaisyChainHopCount_HHD_baseRegisterAddress 0xC84E
/*! \brief MMD address of structure AQ_GlobalDaisyChainHopCount_HHD */
#define AQ_GlobalDaisyChainHopCount_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure daisyChainHopCount in AQ_GlobalDaisyChainHopCount_HHD */
#define AQ_GlobalDaisyChainHopCount_HHD_daisyChainHopCount 0
/*! \brief Preprocessor variable to relate field to bit position in structure daisyChainHopCount in AQ_GlobalDaisyChainHopCount_HHD */
#define bits_AQ_GlobalDaisyChainHopCount_HHD_daisyChainHopCount u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure daisyChainHopCount in AQ_GlobalDaisyChainHopCount_HHD */
#define word_AQ_GlobalDaisyChainHopCount_HHD_daisyChainHopCount u0.word_0

/*! \brief Base register address of structure AQ_GlobalFaultMessage_HHD */
#define AQ_GlobalFaultMessage_HHD_baseRegisterAddress 0xC850
/*! \brief MMD address of structure AQ_GlobalFaultMessage_HHD */
#define AQ_GlobalFaultMessage_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure message in AQ_GlobalFaultMessage_HHD */
#define AQ_GlobalFaultMessage_HHD_message 0
/*! \brief Preprocessor variable to relate field to bit position in structure message in AQ_GlobalFaultMessage_HHD */
#define bits_AQ_GlobalFaultMessage_HHD_message u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure message in AQ_GlobalFaultMessage_HHD */
#define word_AQ_GlobalFaultMessage_HHD_message u0.word_0

/*! \brief Base register address of structure AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_baseRegisterAddress 0xC880
/*! \brief MMD address of structure AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure reserved_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairAReflection_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairAReflection_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairAReflection_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairAReflection_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairAReflection_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairAReflection_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairAReflection_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairAReflection_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairAReflection_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairAReflection_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairAReflection_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairAReflection_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_3 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_3 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_3 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairAReflection_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairAReflection_3 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairAReflection_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairAReflection_3 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairAReflection_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairAReflection_3 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_4 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_4 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_4 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pairAReflection_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairAReflection_4 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairAReflection_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairAReflection_4 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairAReflection_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairAReflection_4 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_5 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_5 1
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_5 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_5 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reserved_5 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_5 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure pairBReflection_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairBReflection_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure pairBReflection_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairBReflection_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pairBReflection_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairBReflection_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reserved_6 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_6 1
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_6 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_6 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reserved_6 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_6 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure pairBReflection_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairBReflection_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure pairBReflection_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairBReflection_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pairBReflection_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairBReflection_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reserved_7 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_7 1
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_7 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_7 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reserved_7 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_7 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure pairBReflection_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairBReflection_3 1
/*! \brief Preprocessor variable to relate field to bit position in structure pairBReflection_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairBReflection_3 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pairBReflection_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairBReflection_3 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reserved_8 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_8 1
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_8 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_8 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reserved_8 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_8 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure pairBReflection_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairBReflection_4 1
/*! \brief Preprocessor variable to relate field to bit position in structure pairBReflection_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairBReflection_4 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure pairBReflection_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairBReflection_4 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reserved_9 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_9 2
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_9 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_9 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reserved_9 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_9 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pairCReflection_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairCReflection_1 2
/*! \brief Preprocessor variable to relate field to bit position in structure pairCReflection_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairCReflection_1 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure pairCReflection_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairCReflection_1 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reserved_10 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_10 2
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_10 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_10 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reserved_10 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_10 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pairCReflection_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairCReflection_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure pairCReflection_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairCReflection_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure pairCReflection_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairCReflection_2 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reserved_11 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_11 2
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_11 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_11 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reserved_11 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_11 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pairCReflection_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairCReflection_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure pairCReflection_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairCReflection_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure pairCReflection_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairCReflection_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reserved_12 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_12 2
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_12 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_12 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reserved_12 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_12 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure pairCReflection_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairCReflection_4 2
/*! \brief Preprocessor variable to relate field to bit position in structure pairCReflection_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairCReflection_4 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure pairCReflection_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairCReflection_4 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reserved_13 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_13 3
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_13 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_13 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reserved_13 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_13 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure pairDReflection_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairDReflection_1 3
/*! \brief Preprocessor variable to relate field to bit position in structure pairDReflection_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairDReflection_1 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pairDReflection_1 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairDReflection_1 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reserved_14 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_14 3
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_14 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_14 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reserved_14 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_14 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure pairDReflection_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairDReflection_2 3
/*! \brief Preprocessor variable to relate field to bit position in structure pairDReflection_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairDReflection_2 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pairDReflection_2 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairDReflection_2 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reserved_15 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_15 3
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_15 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_15 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reserved_15 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_15 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure pairDReflection_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairDReflection_3 3
/*! \brief Preprocessor variable to relate field to bit position in structure pairDReflection_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairDReflection_3 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pairDReflection_3 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairDReflection_3 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reserved_16 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_reserved_16 3
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_16 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_16 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reserved_16 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_reserved_16 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure pairDReflection_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define AQ_GlobalCableDiagnosticImpedance_HHD_pairDReflection_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure pairDReflection_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define bits_AQ_GlobalCableDiagnosticImpedance_HHD_pairDReflection_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure pairDReflection_4 in AQ_GlobalCableDiagnosticImpedance_HHD */
#define word_AQ_GlobalCableDiagnosticImpedance_HHD_pairDReflection_4 u3.word_3

/*! \brief Base register address of structure AQ_GlobalStatus_HHD */
#define AQ_GlobalStatus_HHD_baseRegisterAddress 0xC884
/*! \brief MMD address of structure AQ_GlobalStatus_HHD */
#define AQ_GlobalStatus_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure reservedStatus_0 in AQ_GlobalStatus_HHD */
#define AQ_GlobalStatus_HHD_reservedStatus_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedStatus_0 in AQ_GlobalStatus_HHD */
#define bits_AQ_GlobalStatus_HHD_reservedStatus_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedStatus_0 in AQ_GlobalStatus_HHD */
#define word_AQ_GlobalStatus_HHD_reservedStatus_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure cableLength in AQ_GlobalStatus_HHD */
#define AQ_GlobalStatus_HHD_cableLength 0
/*! \brief Preprocessor variable to relate field to bit position in structure cableLength in AQ_GlobalStatus_HHD */
#define bits_AQ_GlobalStatus_HHD_cableLength u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure cableLength in AQ_GlobalStatus_HHD */
#define word_AQ_GlobalStatus_HHD_cableLength u0.word_0

/*! \brief Base register address of structure AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_baseRegisterAddress 0xC885
/*! \brief MMD address of structure AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure nearlySecondsMSW in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_nearlySecondsMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure nearlySecondsMSW in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_nearlySecondsMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nearlySecondsMSW in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_nearlySecondsMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xenpakNvrStatus in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_xenpakNvrStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure xenpakNvrStatus in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_xenpakNvrStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xenpakNvrStatus in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_xenpakNvrStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure firmwareBuildID in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_firmwareBuildID 0
/*! \brief Preprocessor variable to relate field to bit position in structure firmwareBuildID in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_firmwareBuildID u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure firmwareBuildID in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_firmwareBuildID u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure provisioningID in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_provisioningID 0
/*! \brief Preprocessor variable to relate field to bit position in structure provisioningID in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_provisioningID u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure provisioningID in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_provisioningID u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nearlySecondsLSW in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_nearlySecondsLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure nearlySecondsLSW in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_nearlySecondsLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure nearlySecondsLSW in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_nearlySecondsLSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure dteStatus in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_dteStatus 2
/*! \brief Preprocessor variable to relate field to bit position in structure dteStatus in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_dteStatus u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure dteStatus in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_dteStatus u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure powerUpStallStatus in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_powerUpStallStatus 2
/*! \brief Preprocessor variable to relate field to bit position in structure powerUpStallStatus in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_powerUpStallStatus u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure powerUpStallStatus in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_powerUpStallStatus u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedStatus_3 in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_reservedStatus_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedStatus_3 in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_reservedStatus_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedStatus_3 in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_reservedStatus_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure loopbackStatus in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_loopbackStatus 3
/*! \brief Preprocessor variable to relate field to bit position in structure loopbackStatus in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_loopbackStatus u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure loopbackStatus in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_loopbackStatus u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reservedStatus_4 in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_reservedStatus_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedStatus_4 in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_reservedStatus_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedStatus_4 in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_reservedStatus_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure mdiPacketGenerationStatus in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_mdiPacketGenerationStatus 3
/*! \brief Preprocessor variable to relate field to bit position in structure mdiPacketGenerationStatus in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_mdiPacketGenerationStatus u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure mdiPacketGenerationStatus in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_mdiPacketGenerationStatus u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure look_asidePortPacketGenerationStatus in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_look_asidePortPacketGenerationStatus 3
/*! \brief Preprocessor variable to relate field to bit position in structure look_asidePortPacketGenerationStatus in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_look_asidePortPacketGenerationStatus u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure look_asidePortPacketGenerationStatus in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_look_asidePortPacketGenerationStatus u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure systemI_fPacketGenerationStatus in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_systemI_fPacketGenerationStatus 3
/*! \brief Preprocessor variable to relate field to bit position in structure systemI_fPacketGenerationStatus in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_systemI_fPacketGenerationStatus u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure systemI_fPacketGenerationStatus in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_systemI_fPacketGenerationStatus u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure rate in AQ_GlobalReservedStatus_HHD */
#define AQ_GlobalReservedStatus_HHD_rate 3
/*! \brief Preprocessor variable to relate field to bit position in structure rate in AQ_GlobalReservedStatus_HHD */
#define bits_AQ_GlobalReservedStatus_HHD_rate u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure rate in AQ_GlobalReservedStatus_HHD */
#define word_AQ_GlobalReservedStatus_HHD_rate u3.word_3

/*! \brief Base register address of structure AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_baseRegisterAddress 0xCC00
/*! \brief MMD address of structure AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureFailure in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_highTemperatureFailure 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureFailure in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_highTemperatureFailure u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureFailure in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_highTemperatureFailure u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureFailure in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_lowTemperatureFailure 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureFailure in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_lowTemperatureFailure u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureFailure in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_lowTemperatureFailure u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureWarning in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_highTemperatureWarning 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureWarning in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_highTemperatureWarning u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureWarning in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_highTemperatureWarning u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureWarning in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_lowTemperatureWarning 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureWarning in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_lowTemperatureWarning u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureWarning in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_lowTemperatureWarning u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure resetCompleted in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_resetCompleted 0
/*! \brief Preprocessor variable to relate field to bit position in structure resetCompleted in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_resetCompleted u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure resetCompleted in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_resetCompleted u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure deviceFault in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_deviceFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure deviceFault in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_deviceFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure deviceFault in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_deviceFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmA in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_reservedAlarmA 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmA in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_reservedAlarmA u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmA in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_reservedAlarmA u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmB in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_reservedAlarmB 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmB in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_reservedAlarmB u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmB in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_reservedAlarmB u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmC in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_reservedAlarmC 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmC in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_reservedAlarmC u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmC in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_reservedAlarmC u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmD in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_reservedAlarmD 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmD in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_reservedAlarmD u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmD in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_reservedAlarmD u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure smartPower_downEntered in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_smartPower_downEntered 1
/*! \brief Preprocessor variable to relate field to bit position in structure smartPower_downEntered in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_smartPower_downEntered u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure smartPower_downEntered in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_smartPower_downEntered u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xenpakAlarm in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_xenpakAlarm 1
/*! \brief Preprocessor variable to relate field to bit position in structure xenpakAlarm in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_xenpakAlarm u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xenpakAlarm in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_xenpakAlarm u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ipPhoneDetect in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_ipPhoneDetect 1
/*! \brief Preprocessor variable to relate field to bit position in structure ipPhoneDetect in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_ipPhoneDetect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ipPhoneDetect in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_ipPhoneDetect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure dteStatusChange in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_dteStatusChange 1
/*! \brief Preprocessor variable to relate field to bit position in structure dteStatusChange in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_dteStatusChange u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure dteStatusChange in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_dteStatusChange u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure fastLinkDrop in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_fastLinkDrop 1
/*! \brief Preprocessor variable to relate field to bit position in structure fastLinkDrop in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_fastLinkDrop u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure fastLinkDrop in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_fastLinkDrop u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarms in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_reservedAlarms 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarms in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_reservedAlarms u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarms in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_reservedAlarms u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mdioCommandHandlingOverflow in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_mdioCommandHandlingOverflow 1
/*! \brief Preprocessor variable to relate field to bit position in structure mdioCommandHandlingOverflow in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_mdioCommandHandlingOverflow u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mdioCommandHandlingOverflow in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_mdioCommandHandlingOverflow u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure diagnosticAlarm in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_diagnosticAlarm 1
/*! \brief Preprocessor variable to relate field to bit position in structure diagnosticAlarm in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_diagnosticAlarm u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure diagnosticAlarm in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_diagnosticAlarm u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure nvrOperationComplete in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_nvrOperationComplete 2
/*! \brief Preprocessor variable to relate field to bit position in structure nvrOperationComplete in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_nvrOperationComplete u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure nvrOperationComplete in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_nvrOperationComplete u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mailboxOperation_Complete in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_mailboxOperation_Complete 2
/*! \brief Preprocessor variable to relate field to bit position in structure mailboxOperation_Complete in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_mailboxOperation_Complete u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mailboxOperation_Complete in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_mailboxOperation_Complete u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure upDramParityError in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_upDramParityError 2
/*! \brief Preprocessor variable to relate field to bit position in structure upDramParityError in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_upDramParityError u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure upDramParityError in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_upDramParityError u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure upIramParityError in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_upIramParityError 2
/*! \brief Preprocessor variable to relate field to bit position in structure upIramParityError in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_upIramParityError u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure upIramParityError in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_upIramParityError u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure txEnableStateChange in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_txEnableStateChange 2
/*! \brief Preprocessor variable to relate field to bit position in structure txEnableStateChange in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_txEnableStateChange u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure txEnableStateChange in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_txEnableStateChange u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mdioMMD_Error in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_mdioMMD_Error 2
/*! \brief Preprocessor variable to relate field to bit position in structure mdioMMD_Error in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_mdioMMD_Error u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mdioMMD_Error in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_mdioMMD_Error u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mdioTimeoutError in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_mdioTimeoutError 2
/*! \brief Preprocessor variable to relate field to bit position in structure mdioTimeoutError in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_mdioTimeoutError u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mdioTimeoutError in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_mdioTimeoutError u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure watchdogTimerAlarm in AQ_GlobalAlarms_HHD */
#define AQ_GlobalAlarms_HHD_watchdogTimerAlarm 2
/*! \brief Preprocessor variable to relate field to bit position in structure watchdogTimerAlarm in AQ_GlobalAlarms_HHD */
#define bits_AQ_GlobalAlarms_HHD_watchdogTimerAlarm u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure watchdogTimerAlarm in AQ_GlobalAlarms_HHD */
#define word_AQ_GlobalAlarms_HHD_watchdogTimerAlarm u2.word_2

/*! \brief Base register address of structure AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_baseRegisterAddress 0xD400
/*! \brief MMD address of structure AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureFailureMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_highTemperatureFailureMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureFailureMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_highTemperatureFailureMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureFailureMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_highTemperatureFailureMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureFailureMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_lowTemperatureFailureMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureFailureMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_lowTemperatureFailureMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureFailureMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_lowTemperatureFailureMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureWarningMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_highTemperatureWarningMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureWarningMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_highTemperatureWarningMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureWarningMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_highTemperatureWarningMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureWarningMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_lowTemperatureWarningMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureWarningMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_lowTemperatureWarningMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureWarningMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_lowTemperatureWarningMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure resetCompletedMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_resetCompletedMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure resetCompletedMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_resetCompletedMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure resetCompletedMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_resetCompletedMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure deviceFaultMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_deviceFaultMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure deviceFaultMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_deviceFaultMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure deviceFaultMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_deviceFaultMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmAMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_reservedAlarmAMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmAMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_reservedAlarmAMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmAMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_reservedAlarmAMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmBMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_reservedAlarmBMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmBMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_reservedAlarmBMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmBMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_reservedAlarmBMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmCMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_reservedAlarmCMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmCMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_reservedAlarmCMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmCMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_reservedAlarmCMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmDMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_reservedAlarmDMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmDMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_reservedAlarmDMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmDMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_reservedAlarmDMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure smartPower_downEnteredMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_smartPower_downEnteredMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure smartPower_downEnteredMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_smartPower_downEnteredMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure smartPower_downEnteredMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_smartPower_downEnteredMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xenpakAlarmMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_xenpakAlarmMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure xenpakAlarmMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_xenpakAlarmMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xenpakAlarmMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_xenpakAlarmMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure ipPhoneDetectMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_ipPhoneDetectMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure ipPhoneDetectMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_ipPhoneDetectMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure ipPhoneDetectMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_ipPhoneDetectMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure dteStatusChangeMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_dteStatusChangeMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure dteStatusChangeMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_dteStatusChangeMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure dteStatusChangeMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_dteStatusChangeMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure fastLinkDropMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_fastLinkDropMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure fastLinkDropMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_fastLinkDropMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure fastLinkDropMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_fastLinkDropMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedAlarmsMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_reservedAlarmsMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedAlarmsMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_reservedAlarmsMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedAlarmsMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_reservedAlarmsMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure mdioCommandHandlingOverflowMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_mdioCommandHandlingOverflowMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure mdioCommandHandlingOverflowMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_mdioCommandHandlingOverflowMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure mdioCommandHandlingOverflowMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_mdioCommandHandlingOverflowMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure diagnosticAlarmMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_diagnosticAlarmMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure diagnosticAlarmMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_diagnosticAlarmMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure diagnosticAlarmMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_diagnosticAlarmMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure nvrOperationCompleteMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_nvrOperationCompleteMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure nvrOperationCompleteMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_nvrOperationCompleteMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure nvrOperationCompleteMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_nvrOperationCompleteMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mailboxOperationCompleteMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_mailboxOperationCompleteMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure mailboxOperationCompleteMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_mailboxOperationCompleteMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mailboxOperationCompleteMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_mailboxOperationCompleteMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure upDramParityErrorMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_upDramParityErrorMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure upDramParityErrorMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_upDramParityErrorMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure upDramParityErrorMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_upDramParityErrorMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure upIramParityErrorMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_upIramParityErrorMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure upIramParityErrorMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_upIramParityErrorMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure upIramParityErrorMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_upIramParityErrorMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure txEnableStateChangeMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_txEnableStateChangeMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure txEnableStateChangeMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_txEnableStateChangeMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure txEnableStateChangeMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_txEnableStateChangeMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mdioMMD_ErrorMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_mdioMMD_ErrorMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure mdioMMD_ErrorMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_mdioMMD_ErrorMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mdioMMD_ErrorMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_mdioMMD_ErrorMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure mdioTimeoutErrorMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_mdioTimeoutErrorMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure mdioTimeoutErrorMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_mdioTimeoutErrorMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure mdioTimeoutErrorMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_mdioTimeoutErrorMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure watchdogTimerAlarmMask in AQ_GlobalInterruptMask_HHD */
#define AQ_GlobalInterruptMask_HHD_watchdogTimerAlarmMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure watchdogTimerAlarmMask in AQ_GlobalInterruptMask_HHD */
#define bits_AQ_GlobalInterruptMask_HHD_watchdogTimerAlarmMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure watchdogTimerAlarmMask in AQ_GlobalInterruptMask_HHD */
#define word_AQ_GlobalInterruptMask_HHD_watchdogTimerAlarmMask u2.word_2

/*! \brief Base register address of structure AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define AQ_GlobalChip_wideStandardInterruptFlags_HHD_baseRegisterAddress 0xFC00
/*! \brief MMD address of structure AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define AQ_GlobalChip_wideStandardInterruptFlags_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure pmaStandardAlarm_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define AQ_GlobalChip_wideStandardInterruptFlags_HHD_pmaStandardAlarm_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaStandardAlarm_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_HHD_pmaStandardAlarm_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaStandardAlarm_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_HHD_pmaStandardAlarm_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaStandardAlarm_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define AQ_GlobalChip_wideStandardInterruptFlags_HHD_pmaStandardAlarm_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaStandardAlarm_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_HHD_pmaStandardAlarm_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaStandardAlarm_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_HHD_pmaStandardAlarm_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsStandardAlarm_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define AQ_GlobalChip_wideStandardInterruptFlags_HHD_pcsStandardAlarm_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsStandardAlarm_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_HHD_pcsStandardAlarm_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsStandardAlarm_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_HHD_pcsStandardAlarm_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsStandardAlarm_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define AQ_GlobalChip_wideStandardInterruptFlags_HHD_pcsStandardAlarm_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsStandardAlarm_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_HHD_pcsStandardAlarm_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsStandardAlarm_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_HHD_pcsStandardAlarm_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsStandardAlarm_3Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define AQ_GlobalChip_wideStandardInterruptFlags_HHD_pcsStandardAlarm_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsStandardAlarm_3Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_HHD_pcsStandardAlarm_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsStandardAlarm_3Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_HHD_pcsStandardAlarm_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_StandardAlarms_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define AQ_GlobalChip_wideStandardInterruptFlags_HHD_phyXS_StandardAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_StandardAlarms_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_HHD_phyXS_StandardAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_StandardAlarms_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_HHD_phyXS_StandardAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_StandardAlarms_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define AQ_GlobalChip_wideStandardInterruptFlags_HHD_phyXS_StandardAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_StandardAlarms_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_HHD_phyXS_StandardAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_StandardAlarms_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_HHD_phyXS_StandardAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationStandardAlarms_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define AQ_GlobalChip_wideStandardInterruptFlags_HHD_autonegotiationStandardAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationStandardAlarms_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_HHD_autonegotiationStandardAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationStandardAlarms_1Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_HHD_autonegotiationStandardAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationStandardAlarms_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define AQ_GlobalChip_wideStandardInterruptFlags_HHD_autonegotiationStandardAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationStandardAlarms_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_HHD_autonegotiationStandardAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationStandardAlarms_2Interrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_HHD_autonegotiationStandardAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure gbeStandardAlarmsInterrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define AQ_GlobalChip_wideStandardInterruptFlags_HHD_gbeStandardAlarmsInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure gbeStandardAlarmsInterrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_HHD_gbeStandardAlarmsInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure gbeStandardAlarmsInterrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_HHD_gbeStandardAlarmsInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure allVendorAlarmsInterrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define AQ_GlobalChip_wideStandardInterruptFlags_HHD_allVendorAlarmsInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure allVendorAlarmsInterrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideStandardInterruptFlags_HHD_allVendorAlarmsInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure allVendorAlarmsInterrupt in AQ_GlobalChip_wideStandardInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideStandardInterruptFlags_HHD_allVendorAlarmsInterrupt u0.word_0

/*! \brief Base register address of structure AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define AQ_GlobalChip_wideVendorInterruptFlags_HHD_baseRegisterAddress 0xFC01
/*! \brief MMD address of structure AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define AQ_GlobalChip_wideVendorInterruptFlags_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure pmaVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define AQ_GlobalChip_wideVendorInterruptFlags_HHD_pmaVendorAlarmInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_HHD_pmaVendorAlarmInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_HHD_pmaVendorAlarmInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define AQ_GlobalChip_wideVendorInterruptFlags_HHD_pcsVendorAlarmInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_HHD_pcsVendorAlarmInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_HHD_pcsVendorAlarmInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_VendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define AQ_GlobalChip_wideVendorInterruptFlags_HHD_phyXS_VendorAlarmInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_VendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_HHD_phyXS_VendorAlarmInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_VendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_HHD_phyXS_VendorAlarmInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define AQ_GlobalChip_wideVendorInterruptFlags_HHD_autonegotiationVendorAlarmInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_HHD_autonegotiationVendorAlarmInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_HHD_autonegotiationVendorAlarmInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure gbeVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define AQ_GlobalChip_wideVendorInterruptFlags_HHD_gbeVendorAlarmInterrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure gbeVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_HHD_gbeVendorAlarmInterrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure gbeVendorAlarmInterrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_HHD_gbeVendorAlarmInterrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure globalAlarms_1Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define AQ_GlobalChip_wideVendorInterruptFlags_HHD_globalAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalAlarms_1Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_HHD_globalAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalAlarms_1Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_HHD_globalAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure globalAlarms_2Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define AQ_GlobalChip_wideVendorInterruptFlags_HHD_globalAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalAlarms_2Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_HHD_globalAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalAlarms_2Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_HHD_globalAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure globalAlarms_3Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define AQ_GlobalChip_wideVendorInterruptFlags_HHD_globalAlarms_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalAlarms_3Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define bits_AQ_GlobalChip_wideVendorInterruptFlags_HHD_globalAlarms_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalAlarms_3Interrupt in AQ_GlobalChip_wideVendorInterruptFlags_HHD */
#define word_AQ_GlobalChip_wideVendorInterruptFlags_HHD_globalAlarms_3Interrupt u0.word_0

/*! \brief Base register address of structure AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define AQ_GlobalInterruptChip_wideStandardMask_HHD_baseRegisterAddress 0xFF00
/*! \brief MMD address of structure AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define AQ_GlobalInterruptChip_wideStandardMask_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure pmaStandardAlarm_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define AQ_GlobalInterruptChip_wideStandardMask_HHD_pmaStandardAlarm_1InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaStandardAlarm_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_HHD_pmaStandardAlarm_1InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaStandardAlarm_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define word_AQ_GlobalInterruptChip_wideStandardMask_HHD_pmaStandardAlarm_1InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaStandardAlarm_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define AQ_GlobalInterruptChip_wideStandardMask_HHD_pmaStandardAlarm_2InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaStandardAlarm_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_HHD_pmaStandardAlarm_2InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaStandardAlarm_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define word_AQ_GlobalInterruptChip_wideStandardMask_HHD_pmaStandardAlarm_2InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsStandardAlarm_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define AQ_GlobalInterruptChip_wideStandardMask_HHD_pcsStandardAlarm_1InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsStandardAlarm_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_HHD_pcsStandardAlarm_1InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsStandardAlarm_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define word_AQ_GlobalInterruptChip_wideStandardMask_HHD_pcsStandardAlarm_1InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsStandardAlarm_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define AQ_GlobalInterruptChip_wideStandardMask_HHD_pcsStandardAlarm_2InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsStandardAlarm_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_HHD_pcsStandardAlarm_2InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsStandardAlarm_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define word_AQ_GlobalInterruptChip_wideStandardMask_HHD_pcsStandardAlarm_2InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsStandardAlarm_3InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define AQ_GlobalInterruptChip_wideStandardMask_HHD_pcsStandardAlarm_3InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsStandardAlarm_3InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_HHD_pcsStandardAlarm_3InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsStandardAlarm_3InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define word_AQ_GlobalInterruptChip_wideStandardMask_HHD_pcsStandardAlarm_3InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_StandardAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define AQ_GlobalInterruptChip_wideStandardMask_HHD_phyXS_StandardAlarms_1InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_StandardAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_HHD_phyXS_StandardAlarms_1InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_StandardAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define word_AQ_GlobalInterruptChip_wideStandardMask_HHD_phyXS_StandardAlarms_1InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_StandardAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define AQ_GlobalInterruptChip_wideStandardMask_HHD_phyXS_StandardAlarms_2InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_StandardAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_HHD_phyXS_StandardAlarms_2InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_StandardAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define word_AQ_GlobalInterruptChip_wideStandardMask_HHD_phyXS_StandardAlarms_2InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationStandardAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define AQ_GlobalInterruptChip_wideStandardMask_HHD_autonegotiationStandardAlarms_1InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationStandardAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_HHD_autonegotiationStandardAlarms_1InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationStandardAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define word_AQ_GlobalInterruptChip_wideStandardMask_HHD_autonegotiationStandardAlarms_1InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationStandardAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define AQ_GlobalInterruptChip_wideStandardMask_HHD_autonegotiationStandardAlarms_2InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationStandardAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_HHD_autonegotiationStandardAlarms_2InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationStandardAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define word_AQ_GlobalInterruptChip_wideStandardMask_HHD_autonegotiationStandardAlarms_2InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure gbeStandardAlarmsInterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define AQ_GlobalInterruptChip_wideStandardMask_HHD_gbeStandardAlarmsInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure gbeStandardAlarmsInterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_HHD_gbeStandardAlarmsInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure gbeStandardAlarmsInterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define word_AQ_GlobalInterruptChip_wideStandardMask_HHD_gbeStandardAlarmsInterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure allVendorAlarmsInterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define AQ_GlobalInterruptChip_wideStandardMask_HHD_allVendorAlarmsInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure allVendorAlarmsInterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideStandardMask_HHD_allVendorAlarmsInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure allVendorAlarmsInterruptMask in AQ_GlobalInterruptChip_wideStandardMask_HHD */
#define word_AQ_GlobalInterruptChip_wideStandardMask_HHD_allVendorAlarmsInterruptMask u0.word_0

/*! \brief Base register address of structure AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define AQ_GlobalInterruptChip_wideVendorMask_HHD_baseRegisterAddress 0xFF01
/*! \brief MMD address of structure AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define AQ_GlobalInterruptChip_wideVendorMask_HHD_mmdAddress 0x1E
/*! \brief Preprocessor variable to relate field to word number in structure pmaVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define AQ_GlobalInterruptChip_wideVendorMask_HHD_pmaVendorAlarmInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_HHD_pmaVendorAlarmInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define word_AQ_GlobalInterruptChip_wideVendorMask_HHD_pmaVendorAlarmInterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define AQ_GlobalInterruptChip_wideVendorMask_HHD_pcsVendorAlarmInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_HHD_pcsVendorAlarmInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define word_AQ_GlobalInterruptChip_wideVendorMask_HHD_pcsVendorAlarmInterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_VendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define AQ_GlobalInterruptChip_wideVendorMask_HHD_phyXS_VendorAlarmInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_VendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_HHD_phyXS_VendorAlarmInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_VendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define word_AQ_GlobalInterruptChip_wideVendorMask_HHD_phyXS_VendorAlarmInterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define AQ_GlobalInterruptChip_wideVendorMask_HHD_autonegotiationVendorAlarmInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_HHD_autonegotiationVendorAlarmInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define word_AQ_GlobalInterruptChip_wideVendorMask_HHD_autonegotiationVendorAlarmInterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure gbeVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define AQ_GlobalInterruptChip_wideVendorMask_HHD_gbeVendorAlarmInterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure gbeVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_HHD_gbeVendorAlarmInterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure gbeVendorAlarmInterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define word_AQ_GlobalInterruptChip_wideVendorMask_HHD_gbeVendorAlarmInterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure globalAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define AQ_GlobalInterruptChip_wideVendorMask_HHD_globalAlarms_1InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_HHD_globalAlarms_1InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalAlarms_1InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define word_AQ_GlobalInterruptChip_wideVendorMask_HHD_globalAlarms_1InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure globalAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define AQ_GlobalInterruptChip_wideVendorMask_HHD_globalAlarms_2InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_HHD_globalAlarms_2InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalAlarms_2InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define word_AQ_GlobalInterruptChip_wideVendorMask_HHD_globalAlarms_2InterruptMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure globalAlarms_3InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define AQ_GlobalInterruptChip_wideVendorMask_HHD_globalAlarms_3InterruptMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure globalAlarms_3InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define bits_AQ_GlobalInterruptChip_wideVendorMask_HHD_globalAlarms_3InterruptMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure globalAlarms_3InterruptMask in AQ_GlobalInterruptChip_wideVendorMask_HHD */
#define word_AQ_GlobalInterruptChip_wideVendorMask_HHD_globalAlarms_3InterruptMask u0.word_0
#endif
/*@}*/
/*@}*/
