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
*   for the Autonegotiation Registers block.
*/

/*! \defgroup Autonegotiation_registers_Defines Autonegotiation Registers Defines
*   This module contains the compiler assist macros and doxygen comments
*   for the Autonegotiation Registers block.
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
*   This file contains the compiler assist macros for the registers contained in the Autonegotiation Registers block.
*
*
***********************************************************************/


/*@{*/
#ifndef AQ_APPIA_ANG_REGS_DEFINES_HEADER
#define AQ_APPIA_ANG_REGS_DEFINES_HEADER


/*-----------------------------------------------------------------------------*/
/*Access macro definitions                                                     */
/*-----------------------------------------------------------------------------*/
/*! \brief Base register address of structure AQ_AutonegotiationStandardControl_1_APPIA */
#define AQ_AutonegotiationStandardControl_1_APPIA_baseRegisterAddress 0x0000
/*! \brief MMD address of structure AQ_AutonegotiationStandardControl_1_APPIA */
#define AQ_AutonegotiationStandardControl_1_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure reset in AQ_AutonegotiationStandardControl_1_APPIA */
#define AQ_AutonegotiationStandardControl_1_APPIA_reset 0
/*! \brief Preprocessor variable to relate field to bit position in structure reset in AQ_AutonegotiationStandardControl_1_APPIA */
#define bits_AQ_AutonegotiationStandardControl_1_APPIA_reset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reset in AQ_AutonegotiationStandardControl_1_APPIA */
#define word_AQ_AutonegotiationStandardControl_1_APPIA_reset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPageControl in AQ_AutonegotiationStandardControl_1_APPIA */
#define AQ_AutonegotiationStandardControl_1_APPIA_extendedNextPageControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPageControl in AQ_AutonegotiationStandardControl_1_APPIA */
#define bits_AQ_AutonegotiationStandardControl_1_APPIA_extendedNextPageControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPageControl in AQ_AutonegotiationStandardControl_1_APPIA */
#define word_AQ_AutonegotiationStandardControl_1_APPIA_extendedNextPageControl u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationEnable in AQ_AutonegotiationStandardControl_1_APPIA */
#define AQ_AutonegotiationStandardControl_1_APPIA_autonegotiationEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationEnable in AQ_AutonegotiationStandardControl_1_APPIA */
#define bits_AQ_AutonegotiationStandardControl_1_APPIA_autonegotiationEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationEnable in AQ_AutonegotiationStandardControl_1_APPIA */
#define word_AQ_AutonegotiationStandardControl_1_APPIA_autonegotiationEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure restartAutonegotiation in AQ_AutonegotiationStandardControl_1_APPIA */
#define AQ_AutonegotiationStandardControl_1_APPIA_restartAutonegotiation 0
/*! \brief Preprocessor variable to relate field to bit position in structure restartAutonegotiation in AQ_AutonegotiationStandardControl_1_APPIA */
#define bits_AQ_AutonegotiationStandardControl_1_APPIA_restartAutonegotiation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure restartAutonegotiation in AQ_AutonegotiationStandardControl_1_APPIA */
#define word_AQ_AutonegotiationStandardControl_1_APPIA_restartAutonegotiation u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationStandardStatus_1_APPIA */
#define AQ_AutonegotiationStandardStatus_1_APPIA_baseRegisterAddress 0x0001
/*! \brief MMD address of structure AQ_AutonegotiationStandardStatus_1_APPIA */
#define AQ_AutonegotiationStandardStatus_1_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPageStatus in AQ_AutonegotiationStandardStatus_1_APPIA */
#define AQ_AutonegotiationStandardStatus_1_APPIA_extendedNextPageStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPageStatus in AQ_AutonegotiationStandardStatus_1_APPIA */
#define bits_AQ_AutonegotiationStandardStatus_1_APPIA_extendedNextPageStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPageStatus in AQ_AutonegotiationStandardStatus_1_APPIA */
#define word_AQ_AutonegotiationStandardStatus_1_APPIA_extendedNextPageStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pageReceived in AQ_AutonegotiationStandardStatus_1_APPIA */
#define AQ_AutonegotiationStandardStatus_1_APPIA_pageReceived 0
/*! \brief Preprocessor variable to relate field to bit position in structure pageReceived in AQ_AutonegotiationStandardStatus_1_APPIA */
#define bits_AQ_AutonegotiationStandardStatus_1_APPIA_pageReceived u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pageReceived in AQ_AutonegotiationStandardStatus_1_APPIA */
#define word_AQ_AutonegotiationStandardStatus_1_APPIA_pageReceived u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationComplete in AQ_AutonegotiationStandardStatus_1_APPIA */
#define AQ_AutonegotiationStandardStatus_1_APPIA_autonegotiationComplete 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationComplete in AQ_AutonegotiationStandardStatus_1_APPIA */
#define bits_AQ_AutonegotiationStandardStatus_1_APPIA_autonegotiationComplete u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationComplete in AQ_AutonegotiationStandardStatus_1_APPIA */
#define word_AQ_AutonegotiationStandardStatus_1_APPIA_autonegotiationComplete u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure remoteFault in AQ_AutonegotiationStandardStatus_1_APPIA */
#define AQ_AutonegotiationStandardStatus_1_APPIA_remoteFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure remoteFault in AQ_AutonegotiationStandardStatus_1_APPIA */
#define bits_AQ_AutonegotiationStandardStatus_1_APPIA_remoteFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure remoteFault in AQ_AutonegotiationStandardStatus_1_APPIA */
#define word_AQ_AutonegotiationStandardStatus_1_APPIA_remoteFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationAbility in AQ_AutonegotiationStandardStatus_1_APPIA */
#define AQ_AutonegotiationStandardStatus_1_APPIA_autonegotiationAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationAbility in AQ_AutonegotiationStandardStatus_1_APPIA */
#define bits_AQ_AutonegotiationStandardStatus_1_APPIA_autonegotiationAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationAbility in AQ_AutonegotiationStandardStatus_1_APPIA */
#define word_AQ_AutonegotiationStandardStatus_1_APPIA_autonegotiationAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkStatus in AQ_AutonegotiationStandardStatus_1_APPIA */
#define AQ_AutonegotiationStandardStatus_1_APPIA_linkStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkStatus in AQ_AutonegotiationStandardStatus_1_APPIA */
#define bits_AQ_AutonegotiationStandardStatus_1_APPIA_linkStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkStatus in AQ_AutonegotiationStandardStatus_1_APPIA */
#define word_AQ_AutonegotiationStandardStatus_1_APPIA_linkStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerAutonegotiationAbility in AQ_AutonegotiationStandardStatus_1_APPIA */
#define AQ_AutonegotiationStandardStatus_1_APPIA_linkPartnerAutonegotiationAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerAutonegotiationAbility in AQ_AutonegotiationStandardStatus_1_APPIA */
#define bits_AQ_AutonegotiationStandardStatus_1_APPIA_linkPartnerAutonegotiationAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerAutonegotiationAbility in AQ_AutonegotiationStandardStatus_1_APPIA */
#define word_AQ_AutonegotiationStandardStatus_1_APPIA_linkPartnerAutonegotiationAbility u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationStandardDeviceIdentifier_APPIA */
#define AQ_AutonegotiationStandardDeviceIdentifier_APPIA_baseRegisterAddress 0x0002
/*! \brief MMD address of structure AQ_AutonegotiationStandardDeviceIdentifier_APPIA */
#define AQ_AutonegotiationStandardDeviceIdentifier_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdMSW in AQ_AutonegotiationStandardDeviceIdentifier_APPIA */
#define AQ_AutonegotiationStandardDeviceIdentifier_APPIA_deviceIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdMSW in AQ_AutonegotiationStandardDeviceIdentifier_APPIA */
#define bits_AQ_AutonegotiationStandardDeviceIdentifier_APPIA_deviceIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdMSW in AQ_AutonegotiationStandardDeviceIdentifier_APPIA */
#define word_AQ_AutonegotiationStandardDeviceIdentifier_APPIA_deviceIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdLSW in AQ_AutonegotiationStandardDeviceIdentifier_APPIA */
#define AQ_AutonegotiationStandardDeviceIdentifier_APPIA_deviceIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdLSW in AQ_AutonegotiationStandardDeviceIdentifier_APPIA */
#define bits_AQ_AutonegotiationStandardDeviceIdentifier_APPIA_deviceIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdLSW in AQ_AutonegotiationStandardDeviceIdentifier_APPIA */
#define word_AQ_AutonegotiationStandardDeviceIdentifier_APPIA_deviceIdLSW u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define AQ_AutonegotiationStandardDevicesInPackage_APPIA_baseRegisterAddress 0x0005
/*! \brief MMD address of structure AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define AQ_AutonegotiationStandardDevicesInPackage_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define AQ_AutonegotiationStandardDevicesInPackage_APPIA_autonegotiationPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_APPIA_autonegotiationPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define word_AQ_AutonegotiationStandardDevicesInPackage_APPIA_autonegotiationPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tcPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define AQ_AutonegotiationStandardDevicesInPackage_APPIA_tcPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure tcPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_APPIA_tcPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tcPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define word_AQ_AutonegotiationStandardDevicesInPackage_APPIA_tcPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure dteXsPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define AQ_AutonegotiationStandardDevicesInPackage_APPIA_dteXsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure dteXsPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_APPIA_dteXsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure dteXsPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define word_AQ_AutonegotiationStandardDevicesInPackage_APPIA_dteXsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_Present in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define AQ_AutonegotiationStandardDevicesInPackage_APPIA_phyXS_Present 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_Present in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_APPIA_phyXS_Present u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_Present in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define word_AQ_AutonegotiationStandardDevicesInPackage_APPIA_phyXS_Present u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define AQ_AutonegotiationStandardDevicesInPackage_APPIA_pcsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_APPIA_pcsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define word_AQ_AutonegotiationStandardDevicesInPackage_APPIA_pcsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure wisPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define AQ_AutonegotiationStandardDevicesInPackage_APPIA_wisPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure wisPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_APPIA_wisPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure wisPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define word_AQ_AutonegotiationStandardDevicesInPackage_APPIA_wisPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define AQ_AutonegotiationStandardDevicesInPackage_APPIA_pmaPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_APPIA_pmaPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define word_AQ_AutonegotiationStandardDevicesInPackage_APPIA_pmaPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clause_22RegistersPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define AQ_AutonegotiationStandardDevicesInPackage_APPIA_clause_22RegistersPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22RegistersPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_APPIA_clause_22RegistersPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clause_22RegistersPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define word_AQ_AutonegotiationStandardDevicesInPackage_APPIA_clause_22RegistersPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_2Present in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define AQ_AutonegotiationStandardDevicesInPackage_APPIA_vendorSpecificDevice_2Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_2Present in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_APPIA_vendorSpecificDevice_2Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_2Present in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define word_AQ_AutonegotiationStandardDevicesInPackage_APPIA_vendorSpecificDevice_2Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_1Present in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define AQ_AutonegotiationStandardDevicesInPackage_APPIA_vendorSpecificDevice_1Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_1Present in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_APPIA_vendorSpecificDevice_1Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_1Present in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define word_AQ_AutonegotiationStandardDevicesInPackage_APPIA_vendorSpecificDevice_1Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure clause_22ExtensionPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define AQ_AutonegotiationStandardDevicesInPackage_APPIA_clause_22ExtensionPresent 1
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22ExtensionPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_APPIA_clause_22ExtensionPresent u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure clause_22ExtensionPresent in AQ_AutonegotiationStandardDevicesInPackage_APPIA */
#define word_AQ_AutonegotiationStandardDevicesInPackage_APPIA_clause_22ExtensionPresent u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationStandardStatus_2_APPIA */
#define AQ_AutonegotiationStandardStatus_2_APPIA_baseRegisterAddress 0x0008
/*! \brief MMD address of structure AQ_AutonegotiationStandardStatus_2_APPIA */
#define AQ_AutonegotiationStandardStatus_2_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure devicePresent in AQ_AutonegotiationStandardStatus_2_APPIA */
#define AQ_AutonegotiationStandardStatus_2_APPIA_devicePresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure devicePresent in AQ_AutonegotiationStandardStatus_2_APPIA */
#define bits_AQ_AutonegotiationStandardStatus_2_APPIA_devicePresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure devicePresent in AQ_AutonegotiationStandardStatus_2_APPIA */
#define word_AQ_AutonegotiationStandardStatus_2_APPIA_devicePresent u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationStandardPackageIdentifier_APPIA */
#define AQ_AutonegotiationStandardPackageIdentifier_APPIA_baseRegisterAddress 0x000E
/*! \brief MMD address of structure AQ_AutonegotiationStandardPackageIdentifier_APPIA */
#define AQ_AutonegotiationStandardPackageIdentifier_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure packageIdMSW in AQ_AutonegotiationStandardPackageIdentifier_APPIA */
#define AQ_AutonegotiationStandardPackageIdentifier_APPIA_packageIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdMSW in AQ_AutonegotiationStandardPackageIdentifier_APPIA */
#define bits_AQ_AutonegotiationStandardPackageIdentifier_APPIA_packageIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure packageIdMSW in AQ_AutonegotiationStandardPackageIdentifier_APPIA */
#define word_AQ_AutonegotiationStandardPackageIdentifier_APPIA_packageIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure packageIdLSW in AQ_AutonegotiationStandardPackageIdentifier_APPIA */
#define AQ_AutonegotiationStandardPackageIdentifier_APPIA_packageIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdLSW in AQ_AutonegotiationStandardPackageIdentifier_APPIA */
#define bits_AQ_AutonegotiationStandardPackageIdentifier_APPIA_packageIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure packageIdLSW in AQ_AutonegotiationStandardPackageIdentifier_APPIA */
#define word_AQ_AutonegotiationStandardPackageIdentifier_APPIA_packageIdLSW u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationAdvertisementRegister_APPIA */
#define AQ_AutonegotiationAdvertisementRegister_APPIA_baseRegisterAddress 0x0010
/*! \brief MMD address of structure AQ_AutonegotiationAdvertisementRegister_APPIA */
#define AQ_AutonegotiationAdvertisementRegister_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure nextPageAbility in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define AQ_AutonegotiationAdvertisementRegister_APPIA_nextPageAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure nextPageAbility in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define bits_AQ_AutonegotiationAdvertisementRegister_APPIA_nextPageAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nextPageAbility in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define word_AQ_AutonegotiationAdvertisementRegister_APPIA_nextPageAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure advertisementRemoteFault in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define AQ_AutonegotiationAdvertisementRegister_APPIA_advertisementRemoteFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure advertisementRemoteFault in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define bits_AQ_AutonegotiationAdvertisementRegister_APPIA_advertisementRemoteFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure advertisementRemoteFault in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define word_AQ_AutonegotiationAdvertisementRegister_APPIA_advertisementRemoteFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPageAbility in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define AQ_AutonegotiationAdvertisementRegister_APPIA_extendedNextPageAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPageAbility in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define bits_AQ_AutonegotiationAdvertisementRegister_APPIA_extendedNextPageAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPageAbility in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define word_AQ_AutonegotiationAdvertisementRegister_APPIA_extendedNextPageAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure technologyAbilityField in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define AQ_AutonegotiationAdvertisementRegister_APPIA_technologyAbilityField 0
/*! \brief Preprocessor variable to relate field to bit position in structure technologyAbilityField in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define bits_AQ_AutonegotiationAdvertisementRegister_APPIA_technologyAbilityField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure technologyAbilityField in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define word_AQ_AutonegotiationAdvertisementRegister_APPIA_technologyAbilityField u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure selectorField in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define AQ_AutonegotiationAdvertisementRegister_APPIA_selectorField 0
/*! \brief Preprocessor variable to relate field to bit position in structure selectorField in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define bits_AQ_AutonegotiationAdvertisementRegister_APPIA_selectorField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure selectorField in AQ_AutonegotiationAdvertisementRegister_APPIA */
#define word_AQ_AutonegotiationAdvertisementRegister_APPIA_selectorField u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_baseRegisterAddress 0x0013
/*! \brief MMD address of structure AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerNextPageAbility in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerNextPageAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerNextPageAbility in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerNextPageAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerNextPageAbility in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerNextPageAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerBasePageAcknowledge in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerBasePageAcknowledge 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerBasePageAcknowledge in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerBasePageAcknowledge u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerBasePageAcknowledge in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerBasePageAcknowledge u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerRemoteFault in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerRemoteFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerRemoteFault in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerRemoteFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerRemoteFault in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerRemoteFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerExtendedNextPageAbility in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerExtendedNextPageAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerExtendedNextPageAbility in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerExtendedNextPageAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerExtendedNextPageAbility in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerExtendedNextPageAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTechnologyAbilityField in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerTechnologyAbilityField 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTechnologyAbilityField in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerTechnologyAbilityField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTechnologyAbilityField in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerTechnologyAbilityField u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerSelectorField in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerSelectorField 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerSelectorField in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerSelectorField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerSelectorField in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_APPIA_linkPartnerSelectorField u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_baseRegisterAddress 0x0016
/*! \brief MMD address of structure AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure nextPage in AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_nextPage 0
/*! \brief Preprocessor variable to relate field to bit position in structure nextPage in AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define bits_AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_nextPage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nextPage in AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define word_AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_nextPage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure messagePage in AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_messagePage 0
/*! \brief Preprocessor variable to relate field to bit position in structure messagePage in AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define bits_AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_messagePage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure messagePage in AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define word_AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_messagePage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure acknowledge_2 in AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_acknowledge_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure acknowledge_2 in AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define bits_AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_acknowledge_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure acknowledge_2 in AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define word_AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_acknowledge_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure messageCodeField in AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_messageCodeField 0
/*! \brief Preprocessor variable to relate field to bit position in structure messageCodeField in AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define bits_AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_messageCodeField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure messageCodeField in AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA */
#define word_AQ_AutonegotiationExtendedNextPageTransmitRegister_APPIA_messageCodeField u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA */
#define AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA_baseRegisterAddress 0x0017
/*! \brief MMD address of structure AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA */
#define AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure unformattedCodeField_1 in AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA */
#define AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA_unformattedCodeField_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure unformattedCodeField_1 in AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA */
#define bits_AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA_unformattedCodeField_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure unformattedCodeField_1 in AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA */
#define word_AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA_unformattedCodeField_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure unformattedCodeField_2 in AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA */
#define AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA_unformattedCodeField_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure unformattedCodeField_2 in AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA */
#define bits_AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA_unformattedCodeField_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure unformattedCodeField_2 in AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA */
#define word_AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_APPIA_unformattedCodeField_2 u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_baseRegisterAddress 0x0019
/*! \brief MMD address of structure AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerNextPage in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerNextPage 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerNextPage in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerNextPage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerNextPage in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerNextPage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerExtendedNextPageAcknowledge in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerExtendedNextPageAcknowledge 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerExtendedNextPageAcknowledge in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerExtendedNextPageAcknowledge u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerExtendedNextPageAcknowledge in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerExtendedNextPageAcknowledge u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerMessagePage in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerMessagePage 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerMessagePage in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerMessagePage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerMessagePage in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerMessagePage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerAcknowledge_2 in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerAcknowledge_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerAcknowledge_2 in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerAcknowledge_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerAcknowledge_2 in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerAcknowledge_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerToggle in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerToggle 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerToggle in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerToggle u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerToggle in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerToggle u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerMessageCodeField in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerMessageCodeField 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerMessageCodeField in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerMessageCodeField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerMessageCodeField in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_APPIA_linkPartnerMessageCodeField u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA_baseRegisterAddress 0x001A
/*! \brief MMD address of structure AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerUnformattedCodeField_1 in AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA_linkPartnerUnformattedCodeField_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerUnformattedCodeField_1 in AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA_linkPartnerUnformattedCodeField_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerUnformattedCodeField_1 in AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA_linkPartnerUnformattedCodeField_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerUnformattedCodeField_2 in AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA_linkPartnerUnformattedCodeField_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerUnformattedCodeField_2 in AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA_linkPartnerUnformattedCodeField_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerUnformattedCodeField_2 in AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_APPIA_linkPartnerUnformattedCodeField_2 u1.word_1

/*! \brief Base register address of structure AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_baseRegisterAddress 0x0020
/*! \brief MMD address of structure AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure master_slaveManualConfigurationEnable in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_master_slaveManualConfigurationEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure master_slaveManualConfigurationEnable in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define bits_AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_master_slaveManualConfigurationEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure master_slaveManualConfigurationEnable in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define word_AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_master_slaveManualConfigurationEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure master_slaveConfiguration in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_master_slaveConfiguration 0
/*! \brief Preprocessor variable to relate field to bit position in structure master_slaveConfiguration in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define bits_AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_master_slaveConfiguration u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure master_slaveConfiguration in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define word_AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_master_slaveConfiguration u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure portType in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_portType 0
/*! \brief Preprocessor variable to relate field to bit position in structure portType in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define bits_AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_portType u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure portType in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define word_AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_portType u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tAbility in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_ControlRegister_APPIA__10gbase_tAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tAbility in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define bits_AQ_Autonegotiation10GBaseT_ControlRegister_APPIA__10gbase_tAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tAbility in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define word_AQ_Autonegotiation10GBaseT_ControlRegister_APPIA__10gbase_tAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldPmaTrainingResetRequest in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_ldPmaTrainingResetRequest 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldPmaTrainingResetRequest in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define bits_AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_ldPmaTrainingResetRequest u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldPmaTrainingResetRequest in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define word_AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_ldPmaTrainingResetRequest u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldLoopTimingAbility in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_ldLoopTimingAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldLoopTimingAbility in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define bits_AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_ldLoopTimingAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldLoopTimingAbility in AQ_Autonegotiation10GBaseT_ControlRegister_APPIA */
#define word_AQ_Autonegotiation10GBaseT_ControlRegister_APPIA_ldLoopTimingAbility u0.word_0

/*! \brief Base register address of structure AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_baseRegisterAddress 0x0021
/*! \brief MMD address of structure AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure master_slaveConfigurationFault in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_master_slaveConfigurationFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure master_slaveConfigurationFault in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_master_slaveConfigurationFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure master_slaveConfigurationFault in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_master_slaveConfigurationFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure master_slaveConfigurationResolution in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_master_slaveConfigurationResolution 0
/*! \brief Preprocessor variable to relate field to bit position in structure master_slaveConfigurationResolution in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_master_slaveConfigurationResolution u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure master_slaveConfigurationResolution in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_master_slaveConfigurationResolution u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure localReceiverStatus in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_localReceiverStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure localReceiverStatus in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_localReceiverStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure localReceiverStatus in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_localReceiverStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure remoteReceiverStatus in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_remoteReceiverStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure remoteReceiverStatus in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_remoteReceiverStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure remoteReceiverStatus in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_remoteReceiverStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner10GBaseT_Ability in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_linkPartner10GBaseT_Ability 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner10GBaseT_Ability in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_linkPartner10GBaseT_Ability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner10GBaseT_Ability in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_linkPartner10GBaseT_Ability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerLoopTimingAbility in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_linkPartnerLoopTimingAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerLoopTimingAbility in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_linkPartnerLoopTimingAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerLoopTimingAbility in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_linkPartnerLoopTimingAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTrainingResetRequest in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_linkPartnerTrainingResetRequest 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTrainingResetRequest in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_linkPartnerTrainingResetRequest u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTrainingResetRequest in AQ_Autonegotiation10GBaseT_StatusRegister_APPIA */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_APPIA_linkPartnerTrainingResetRequest u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationVendorProvisioning_APPIA */
#define AQ_AutonegotiationVendorProvisioning_APPIA_baseRegisterAddress 0xC400
/*! \brief MMD address of structure AQ_AutonegotiationVendorProvisioning_APPIA */
#define AQ_AutonegotiationVendorProvisioning_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure _1000base_tFullDuplexAbility in AQ_AutonegotiationVendorProvisioning_APPIA */
#define AQ_AutonegotiationVendorProvisioning_APPIA__1000base_tFullDuplexAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _1000base_tFullDuplexAbility in AQ_AutonegotiationVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationVendorProvisioning_APPIA__1000base_tFullDuplexAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _1000base_tFullDuplexAbility in AQ_AutonegotiationVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationVendorProvisioning_APPIA__1000base_tFullDuplexAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _1000base_tHalfDuplexAbility in AQ_AutonegotiationVendorProvisioning_APPIA */
#define AQ_AutonegotiationVendorProvisioning_APPIA__1000base_tHalfDuplexAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _1000base_tHalfDuplexAbility in AQ_AutonegotiationVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationVendorProvisioning_APPIA__1000base_tHalfDuplexAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _1000base_tHalfDuplexAbility in AQ_AutonegotiationVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationVendorProvisioning_APPIA__1000base_tHalfDuplexAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure short_reach in AQ_AutonegotiationVendorProvisioning_APPIA */
#define AQ_AutonegotiationVendorProvisioning_APPIA_short_reach 0
/*! \brief Preprocessor variable to relate field to bit position in structure short_reach in AQ_AutonegotiationVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationVendorProvisioning_APPIA_short_reach u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure short_reach in AQ_AutonegotiationVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationVendorProvisioning_APPIA_short_reach u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure exchangePhyIdInformation in AQ_AutonegotiationVendorProvisioning_APPIA */
#define AQ_AutonegotiationVendorProvisioning_APPIA_exchangePhyIdInformation 0
/*! \brief Preprocessor variable to relate field to bit position in structure exchangePhyIdInformation in AQ_AutonegotiationVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationVendorProvisioning_APPIA_exchangePhyIdInformation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure exchangePhyIdInformation in AQ_AutonegotiationVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationVendorProvisioning_APPIA_exchangePhyIdInformation u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure userProvidedAutonegotiationData in AQ_AutonegotiationVendorProvisioning_APPIA */
#define AQ_AutonegotiationVendorProvisioning_APPIA_userProvidedAutonegotiationData 0
/*! \brief Preprocessor variable to relate field to bit position in structure userProvidedAutonegotiationData in AQ_AutonegotiationVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationVendorProvisioning_APPIA_userProvidedAutonegotiationData u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure userProvidedAutonegotiationData in AQ_AutonegotiationVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationVendorProvisioning_APPIA_userProvidedAutonegotiationData u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure automaticDownshiftEnable in AQ_AutonegotiationVendorProvisioning_APPIA */
#define AQ_AutonegotiationVendorProvisioning_APPIA_automaticDownshiftEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure automaticDownshiftEnable in AQ_AutonegotiationVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationVendorProvisioning_APPIA_automaticDownshiftEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure automaticDownshiftEnable in AQ_AutonegotiationVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationVendorProvisioning_APPIA_automaticDownshiftEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure retryAttemptsBeforeDownshift in AQ_AutonegotiationVendorProvisioning_APPIA */
#define AQ_AutonegotiationVendorProvisioning_APPIA_retryAttemptsBeforeDownshift 0
/*! \brief Preprocessor variable to relate field to bit position in structure retryAttemptsBeforeDownshift in AQ_AutonegotiationVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationVendorProvisioning_APPIA_retryAttemptsBeforeDownshift u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure retryAttemptsBeforeDownshift in AQ_AutonegotiationVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationVendorProvisioning_APPIA_retryAttemptsBeforeDownshift u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_baseRegisterAddress 0xC410
/*! \brief MMD address of structure AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure serdesStart_upMode in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_serdesStart_upMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesStart_upMode in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_APPIA_serdesStart_upMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesStart_upMode in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReservedVendorProvisioning_APPIA_serdesStart_upMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_0 in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_reservedProvisioning_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_0 in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_APPIA_reservedProvisioning_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_0 in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReservedVendorProvisioning_APPIA_reservedProvisioning_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure semi_crossLinkAttemptPeriod in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_semi_crossLinkAttemptPeriod 0
/*! \brief Preprocessor variable to relate field to bit position in structure semi_crossLinkAttemptPeriod in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_APPIA_semi_crossLinkAttemptPeriod u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure semi_crossLinkAttemptPeriod in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReservedVendorProvisioning_APPIA_semi_crossLinkAttemptPeriod u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure wolMode in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_wolMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure wolMode in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_APPIA_wolMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure wolMode in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReservedVendorProvisioning_APPIA_wolMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure wolEnable in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_wolEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure wolEnable in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_APPIA_wolEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure wolEnable in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReservedVendorProvisioning_APPIA_wolEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extraPageCount in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_extraPageCount 0
/*! \brief Preprocessor variable to relate field to bit position in structure extraPageCount in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_APPIA_extraPageCount u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extraPageCount in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReservedVendorProvisioning_APPIA_extraPageCount u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mdi_Mdi_xControl in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_mdi_Mdi_xControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure mdi_Mdi_xControl in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_APPIA_mdi_Mdi_xControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mdi_Mdi_xControl in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReservedVendorProvisioning_APPIA_mdi_Mdi_xControl u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationTimeout in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_autonegotiationTimeout 1
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationTimeout in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_APPIA_autonegotiationTimeout u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationTimeout in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReservedVendorProvisioning_APPIA_autonegotiationTimeout u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationTimeoutMode in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_autonegotiationTimeoutMode 1
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationTimeoutMode in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_APPIA_autonegotiationTimeoutMode u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationTimeoutMode in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReservedVendorProvisioning_APPIA_autonegotiationTimeoutMode u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationTimeoutStatus in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_autonegotiationTimeoutStatus 1
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationTimeoutStatus in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_APPIA_autonegotiationTimeoutStatus u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationTimeoutStatus in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReservedVendorProvisioning_APPIA_autonegotiationTimeoutStatus u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure low_powerLink_upUpshiftThreshold in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_low_powerLink_upUpshiftThreshold 1
/*! \brief Preprocessor variable to relate field to bit position in structure low_powerLink_upUpshiftThreshold in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_APPIA_low_powerLink_upUpshiftThreshold u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure low_powerLink_upUpshiftThreshold in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReservedVendorProvisioning_APPIA_low_powerLink_upUpshiftThreshold u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure low_powerLink_upUpshiftEnable in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReservedVendorProvisioning_APPIA_low_powerLink_upUpshiftEnable 1
/*! \brief Preprocessor variable to relate field to bit position in structure low_powerLink_upUpshiftEnable in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_APPIA_low_powerLink_upUpshiftEnable u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure low_powerLink_upUpshiftEnable in AQ_AutonegotiationReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReservedVendorProvisioning_APPIA_low_powerLink_upUpshiftEnable u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationVendorStatus_APPIA */
#define AQ_AutonegotiationVendorStatus_APPIA_baseRegisterAddress 0xC800
/*! \brief MMD address of structure AQ_AutonegotiationVendorStatus_APPIA */
#define AQ_AutonegotiationVendorStatus_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure connectRate in AQ_AutonegotiationVendorStatus_APPIA */
#define AQ_AutonegotiationVendorStatus_APPIA_connectRate 0
/*! \brief Preprocessor variable to relate field to bit position in structure connectRate in AQ_AutonegotiationVendorStatus_APPIA */
#define bits_AQ_AutonegotiationVendorStatus_APPIA_connectRate u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure connectRate in AQ_AutonegotiationVendorStatus_APPIA */
#define word_AQ_AutonegotiationVendorStatus_APPIA_connectRate u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure connectType in AQ_AutonegotiationVendorStatus_APPIA */
#define AQ_AutonegotiationVendorStatus_APPIA_connectType 0
/*! \brief Preprocessor variable to relate field to bit position in structure connectType in AQ_AutonegotiationVendorStatus_APPIA */
#define bits_AQ_AutonegotiationVendorStatus_APPIA_connectType u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure connectType in AQ_AutonegotiationVendorStatus_APPIA */
#define word_AQ_AutonegotiationVendorStatus_APPIA_connectType u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_baseRegisterAddress 0xC810
/*! \brief MMD address of structure AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure energyOnLine in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_energyOnLine 0
/*! \brief Preprocessor variable to relate field to bit position in structure energyOnLine in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReservedVendorStatus_APPIA_energyOnLine u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure energyOnLine in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReservedVendorStatus_APPIA_energyOnLine u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure devicePresent in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_devicePresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure devicePresent in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReservedVendorStatus_APPIA_devicePresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure devicePresent in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReservedVendorStatus_APPIA_devicePresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure connectionState in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_connectionState 0
/*! \brief Preprocessor variable to relate field to bit position in structure connectionState in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReservedVendorStatus_APPIA_connectionState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure connectionState in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReservedVendorStatus_APPIA_connectionState u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mdi_mdi_x in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_mdi_mdi_x 0
/*! \brief Preprocessor variable to relate field to bit position in structure mdi_mdi_x in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReservedVendorStatus_APPIA_mdi_mdi_x u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mdi_mdi_x in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReservedVendorStatus_APPIA_mdi_mdi_x u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure duplicateLinkPartnerAutonegotiationAbility in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_duplicateLinkPartnerAutonegotiationAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure duplicateLinkPartnerAutonegotiationAbility in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReservedVendorStatus_APPIA_duplicateLinkPartnerAutonegotiationAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure duplicateLinkPartnerAutonegotiationAbility in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReservedVendorStatus_APPIA_duplicateLinkPartnerAutonegotiationAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedStatus_1 in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_reservedStatus_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedStatus_1 in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReservedVendorStatus_APPIA_reservedStatus_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedStatus_1 in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReservedVendorStatus_APPIA_reservedStatus_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure receivePauseResolution in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_receivePauseResolution 0
/*! \brief Preprocessor variable to relate field to bit position in structure receivePauseResolution in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReservedVendorStatus_APPIA_receivePauseResolution u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure receivePauseResolution in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReservedVendorStatus_APPIA_receivePauseResolution u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitPauseResolution in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_transmitPauseResolution 0
/*! \brief Preprocessor variable to relate field to bit position in structure transmitPauseResolution in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReservedVendorStatus_APPIA_transmitPauseResolution u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure transmitPauseResolution in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReservedVendorStatus_APPIA_transmitPauseResolution u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationAttempts in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_autonegotiationAttempts 1
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationAttempts in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReservedVendorStatus_APPIA_autonegotiationAttempts u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationAttempts in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReservedVendorStatus_APPIA_autonegotiationAttempts u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedState_3 in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_reservedState_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedState_3 in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReservedVendorStatus_APPIA_reservedState_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedState_3 in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReservedVendorStatus_APPIA_reservedState_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedState_4 in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_reservedState_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedState_4 in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReservedVendorStatus_APPIA_reservedState_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedState_4 in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReservedVendorStatus_APPIA_reservedState_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reservedState_5 in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReservedVendorStatus_APPIA_reservedState_5 4
/*! \brief Preprocessor variable to relate field to bit position in structure reservedState_5 in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReservedVendorStatus_APPIA_reservedState_5 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure reservedState_5 in AQ_AutonegotiationReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReservedVendorStatus_APPIA_reservedState_5 u4.word_4

/*! \brief Base register address of structure AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define AQ_AutonegotiationTransmitVendorAlarms_APPIA_baseRegisterAddress 0xCC00
/*! \brief MMD address of structure AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define AQ_AutonegotiationTransmitVendorAlarms_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationCompletedForNon_supportedRate in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define AQ_AutonegotiationTransmitVendorAlarms_APPIA_autonegotiationCompletedForNon_supportedRate 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationCompletedForNon_supportedRate in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_APPIA_autonegotiationCompletedForNon_supportedRate u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationCompletedForNon_supportedRate in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define word_AQ_AutonegotiationTransmitVendorAlarms_APPIA_autonegotiationCompletedForNon_supportedRate u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationCompletedForSupportedRate in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define AQ_AutonegotiationTransmitVendorAlarms_APPIA_autonegotiationCompletedForSupportedRate 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationCompletedForSupportedRate in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_APPIA_autonegotiationCompletedForSupportedRate u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationCompletedForSupportedRate in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define word_AQ_AutonegotiationTransmitVendorAlarms_APPIA_autonegotiationCompletedForSupportedRate u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure automaticDownshift in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define AQ_AutonegotiationTransmitVendorAlarms_APPIA_automaticDownshift 0
/*! \brief Preprocessor variable to relate field to bit position in structure automaticDownshift in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_APPIA_automaticDownshift u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure automaticDownshift in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define word_AQ_AutonegotiationTransmitVendorAlarms_APPIA_automaticDownshift u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure connectionStateChange in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define AQ_AutonegotiationTransmitVendorAlarms_APPIA_connectionStateChange 0
/*! \brief Preprocessor variable to relate field to bit position in structure connectionStateChange in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_APPIA_connectionStateChange u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure connectionStateChange in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define word_AQ_AutonegotiationTransmitVendorAlarms_APPIA_connectionStateChange u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedVendorAlarms_2 in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define AQ_AutonegotiationTransmitVendorAlarms_APPIA_reservedVendorAlarms_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedVendorAlarms_2 in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_APPIA_reservedVendorAlarms_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedVendorAlarms_2 in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define word_AQ_AutonegotiationTransmitVendorAlarms_APPIA_reservedVendorAlarms_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkConnect_Disconnect in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define AQ_AutonegotiationTransmitVendorAlarms_APPIA_linkConnect_Disconnect 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkConnect_Disconnect in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_APPIA_linkConnect_Disconnect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkConnect_Disconnect in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define word_AQ_AutonegotiationTransmitVendorAlarms_APPIA_linkConnect_Disconnect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedVendorAlarms_3 in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define AQ_AutonegotiationTransmitVendorAlarms_APPIA_reservedVendorAlarms_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedVendorAlarms_3 in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_APPIA_reservedVendorAlarms_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedVendorAlarms_3 in AQ_AutonegotiationTransmitVendorAlarms_APPIA */
#define word_AQ_AutonegotiationTransmitVendorAlarms_APPIA_reservedVendorAlarms_3 u2.word_2

/*! \brief Base register address of structure AQ_AutonegotiationStandardInterruptMask_APPIA */
#define AQ_AutonegotiationStandardInterruptMask_APPIA_baseRegisterAddress 0xD000
/*! \brief MMD address of structure AQ_AutonegotiationStandardInterruptMask_APPIA */
#define AQ_AutonegotiationStandardInterruptMask_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPageReceivedMask in AQ_AutonegotiationStandardInterruptMask_APPIA */
#define AQ_AutonegotiationStandardInterruptMask_APPIA_extendedNextPageReceivedMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPageReceivedMask in AQ_AutonegotiationStandardInterruptMask_APPIA */
#define bits_AQ_AutonegotiationStandardInterruptMask_APPIA_extendedNextPageReceivedMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPageReceivedMask in AQ_AutonegotiationStandardInterruptMask_APPIA */
#define word_AQ_AutonegotiationStandardInterruptMask_APPIA_extendedNextPageReceivedMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure remoteFaultMask in AQ_AutonegotiationStandardInterruptMask_APPIA */
#define AQ_AutonegotiationStandardInterruptMask_APPIA_remoteFaultMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure remoteFaultMask in AQ_AutonegotiationStandardInterruptMask_APPIA */
#define bits_AQ_AutonegotiationStandardInterruptMask_APPIA_remoteFaultMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure remoteFaultMask in AQ_AutonegotiationStandardInterruptMask_APPIA */
#define word_AQ_AutonegotiationStandardInterruptMask_APPIA_remoteFaultMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkStatusMask in AQ_AutonegotiationStandardInterruptMask_APPIA */
#define AQ_AutonegotiationStandardInterruptMask_APPIA_linkStatusMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkStatusMask in AQ_AutonegotiationStandardInterruptMask_APPIA */
#define bits_AQ_AutonegotiationStandardInterruptMask_APPIA_linkStatusMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkStatusMask in AQ_AutonegotiationStandardInterruptMask_APPIA */
#define word_AQ_AutonegotiationStandardInterruptMask_APPIA_linkStatusMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure master_slaveConfigurationFaultMask in AQ_AutonegotiationStandardInterruptMask_APPIA */
#define AQ_AutonegotiationStandardInterruptMask_APPIA_master_slaveConfigurationFaultMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure master_slaveConfigurationFaultMask in AQ_AutonegotiationStandardInterruptMask_APPIA */
#define bits_AQ_AutonegotiationStandardInterruptMask_APPIA_master_slaveConfigurationFaultMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure master_slaveConfigurationFaultMask in AQ_AutonegotiationStandardInterruptMask_APPIA */
#define word_AQ_AutonegotiationStandardInterruptMask_APPIA_master_slaveConfigurationFaultMask u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_baseRegisterAddress 0xD400
/*! \brief MMD address of structure AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationCompletedForNon_supportedRateMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_autonegotiationCompletedForNon_supportedRateMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationCompletedForNon_supportedRateMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define bits_AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_autonegotiationCompletedForNon_supportedRateMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationCompletedForNon_supportedRateMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define word_AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_autonegotiationCompletedForNon_supportedRateMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationCompletedForSupportedRateMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_autonegotiationCompletedForSupportedRateMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationCompletedForSupportedRateMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define bits_AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_autonegotiationCompletedForSupportedRateMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationCompletedForSupportedRateMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define word_AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_autonegotiationCompletedForSupportedRateMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure automaticDownshiftMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_automaticDownshiftMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure automaticDownshiftMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define bits_AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_automaticDownshiftMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure automaticDownshiftMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define word_AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_automaticDownshiftMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure connectionStateChangeMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_connectionStateChangeMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure connectionStateChangeMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define bits_AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_connectionStateChangeMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure connectionStateChangeMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define word_AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_connectionStateChangeMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedVendorAlarms_2Mask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_reservedVendorAlarms_2Mask 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedVendorAlarms_2Mask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define bits_AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_reservedVendorAlarms_2Mask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedVendorAlarms_2Mask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define word_AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_reservedVendorAlarms_2Mask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkConnect_DisconnectMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_linkConnect_DisconnectMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkConnect_DisconnectMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define bits_AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_linkConnect_DisconnectMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkConnect_DisconnectMask in AQ_AutonegotiationTransmitVendorInterruptMask_APPIA */
#define word_AQ_AutonegotiationTransmitVendorInterruptMask_APPIA_linkConnect_DisconnectMask u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA_baseRegisterAddress 0xE410
/*! \brief MMD address of structure AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveProvisioning_1 in AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA_reservedReceiveProvisioning_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveProvisioning_1 in AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA_reservedReceiveProvisioning_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveProvisioning_1 in AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA_reservedReceiveProvisioning_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure disable_100base_txParallelDetection in AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA_disable_100base_txParallelDetection 0
/*! \brief Preprocessor variable to relate field to bit position in structure disable_100base_txParallelDetection in AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA_disable_100base_txParallelDetection u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure disable_100base_txParallelDetection in AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_APPIA_disable_100base_txParallelDetection u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_baseRegisterAddress 0xE820
/*! \brief MMD address of structure AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner1000BaseT_FullDuplexAbility in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartner1000BaseT_FullDuplexAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner1000BaseT_FullDuplexAbility in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartner1000BaseT_FullDuplexAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner1000BaseT_FullDuplexAbility in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartner1000BaseT_FullDuplexAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner1000BaseT_HalfDuplexAbility in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartner1000BaseT_HalfDuplexAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner1000BaseT_HalfDuplexAbility in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartner1000BaseT_HalfDuplexAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner1000BaseT_HalfDuplexAbility in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartner1000BaseT_HalfDuplexAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerShort_reach in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartnerShort_reach 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerShort_reach in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartnerShort_reach u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerShort_reach in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartnerShort_reach u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure aquantia_TwinvilleLinkPartner in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_aquantia_TwinvilleLinkPartner 0
/*! \brief Preprocessor variable to relate field to bit position in structure aquantia_TwinvilleLinkPartner in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_aquantia_TwinvilleLinkPartner u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure aquantia_TwinvilleLinkPartner in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_aquantia_TwinvilleLinkPartner u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerFirmwareMajorRevisionNumber in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartnerFirmwareMajorRevisionNumber 3
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerFirmwareMajorRevisionNumber in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartnerFirmwareMajorRevisionNumber u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerFirmwareMajorRevisionNumber in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartnerFirmwareMajorRevisionNumber u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerFirmwareMinorRevisionNumber in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartnerFirmwareMinorRevisionNumber 3
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerFirmwareMinorRevisionNumber in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartnerFirmwareMinorRevisionNumber u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerFirmwareMinorRevisionNumber in AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_APPIA_linkPartnerFirmwareMinorRevisionNumber u3.word_3

/*! \brief Base register address of structure AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_baseRegisterAddress 0xE830
/*! \brief MMD address of structure AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkAttempts in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_linkAttempts 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkAttempts in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_linkAttempts u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkAttempts in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_linkAttempts u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerPhyTag in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_linkPartnerPhyTag 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerPhyTag in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_linkPartnerPhyTag u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerPhyTag in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_linkPartnerPhyTag u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveStatus_1 in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_reservedReceiveStatus_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveStatus_1 in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_reservedReceiveStatus_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveStatus_1 in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_reservedReceiveStatus_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationProtocolErrorState in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_autonegotiationProtocolErrorState 1
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationProtocolErrorState in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_autonegotiationProtocolErrorState u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationProtocolErrorState in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_autonegotiationProtocolErrorState u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure flpIdleErrorState in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_flpIdleErrorState 1
/*! \brief Preprocessor variable to relate field to bit position in structure flpIdleErrorState in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_flpIdleErrorState u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure flpIdleErrorState in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_flpIdleErrorState u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveState_2 in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_reservedReceiveState_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveState_2 in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_reservedReceiveState_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveState_2 in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_reservedReceiveState_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveState_3 in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_reservedReceiveState_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveState_3 in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_reservedReceiveState_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveState_3 in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_reservedReceiveState_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerAfrEnabled in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_linkPartnerAfrEnabled 2
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerAfrEnabled in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_linkPartnerAfrEnabled u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerAfrEnabled in AQ_AutonegotiationReceiveReservedVendorStatus_APPIA */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_APPIA_linkPartnerAfrEnabled u2.word_2

/*! \brief Base register address of structure AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define AQ_AutonegotiationReceiveVendorAlarms_APPIA_baseRegisterAddress 0xEC00
/*! \brief MMD address of structure AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define AQ_AutonegotiationReceiveVendorAlarms_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveVendorAlarms_1 in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define AQ_AutonegotiationReceiveVendorAlarms_APPIA_reservedReceiveVendorAlarms_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveVendorAlarms_1 in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorAlarms_APPIA_reservedReceiveVendorAlarms_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveVendorAlarms_1 in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define word_AQ_AutonegotiationReceiveVendorAlarms_APPIA_reservedReceiveVendorAlarms_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationProtocolError in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define AQ_AutonegotiationReceiveVendorAlarms_APPIA_autonegotiationProtocolError 1
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationProtocolError in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorAlarms_APPIA_autonegotiationProtocolError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationProtocolError in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define word_AQ_AutonegotiationReceiveVendorAlarms_APPIA_autonegotiationProtocolError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure flpIdleError in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define AQ_AutonegotiationReceiveVendorAlarms_APPIA_flpIdleError 1
/*! \brief Preprocessor variable to relate field to bit position in structure flpIdleError in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorAlarms_APPIA_flpIdleError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure flpIdleError in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define word_AQ_AutonegotiationReceiveVendorAlarms_APPIA_flpIdleError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveVendorAlarms_2 in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define AQ_AutonegotiationReceiveVendorAlarms_APPIA_reservedReceiveVendorAlarms_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveVendorAlarms_2 in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorAlarms_APPIA_reservedReceiveVendorAlarms_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveVendorAlarms_2 in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define word_AQ_AutonegotiationReceiveVendorAlarms_APPIA_reservedReceiveVendorAlarms_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure _10base_tDeviceDetect in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define AQ_AutonegotiationReceiveVendorAlarms_APPIA__10base_tDeviceDetect 2
/*! \brief Preprocessor variable to relate field to bit position in structure _10base_tDeviceDetect in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorAlarms_APPIA__10base_tDeviceDetect u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure _10base_tDeviceDetect in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define word_AQ_AutonegotiationReceiveVendorAlarms_APPIA__10base_tDeviceDetect u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveVendorAlarms_4 in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define AQ_AutonegotiationReceiveVendorAlarms_APPIA_reservedReceiveVendorAlarms_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveVendorAlarms_4 in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorAlarms_APPIA_reservedReceiveVendorAlarms_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveVendorAlarms_4 in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define word_AQ_AutonegotiationReceiveVendorAlarms_APPIA_reservedReceiveVendorAlarms_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure _100base_txParallelDetect in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define AQ_AutonegotiationReceiveVendorAlarms_APPIA__100base_txParallelDetect 3
/*! \brief Preprocessor variable to relate field to bit position in structure _100base_txParallelDetect in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorAlarms_APPIA__100base_txParallelDetect u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure _100base_txParallelDetect in AQ_AutonegotiationReceiveVendorAlarms_APPIA */
#define word_AQ_AutonegotiationReceiveVendorAlarms_APPIA__100base_txParallelDetect u3.word_3

/*! \brief Base register address of structure AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_baseRegisterAddress 0xF400
/*! \brief MMD address of structure AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveVendorAlarms_1Mask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_reservedReceiveVendorAlarms_1Mask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveVendorAlarms_1Mask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_reservedReceiveVendorAlarms_1Mask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveVendorAlarms_1Mask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_reservedReceiveVendorAlarms_1Mask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationProtocolErrorMask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_autonegotiationProtocolErrorMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationProtocolErrorMask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_autonegotiationProtocolErrorMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationProtocolErrorMask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_autonegotiationProtocolErrorMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure flpIdleErrorMask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_flpIdleErrorMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure flpIdleErrorMask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_flpIdleErrorMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure flpIdleErrorMask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_flpIdleErrorMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveVendorAlarms_2Mask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_reservedReceiveVendorAlarms_2Mask 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveVendorAlarms_2Mask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_reservedReceiveVendorAlarms_2Mask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveVendorAlarms_2Mask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_reservedReceiveVendorAlarms_2Mask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure _10base_tDeviceDetectMask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define AQ_AutonegotiationReceiveVendorInterruptMask_APPIA__10base_tDeviceDetectMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure _10base_tDeviceDetectMask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA__10base_tDeviceDetectMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure _10base_tDeviceDetectMask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA__10base_tDeviceDetectMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveVendorAlarms_4Mask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_reservedReceiveVendorAlarms_4Mask 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveVendorAlarms_4Mask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_reservedReceiveVendorAlarms_4Mask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveVendorAlarms_4Mask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA_reservedReceiveVendorAlarms_4Mask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure _100base_txParallelDetectMask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define AQ_AutonegotiationReceiveVendorInterruptMask_APPIA__100base_txParallelDetectMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure _100base_txParallelDetectMask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA__100base_txParallelDetectMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure _100base_txParallelDetectMask in AQ_AutonegotiationReceiveVendorInterruptMask_APPIA */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_APPIA__100base_txParallelDetectMask u3.word_3

/*! \brief Base register address of structure AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_baseRegisterAddress 0xFC00
/*! \brief MMD address of structure AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_standardAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_standardAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_standardAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_standardAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_standardAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_standardAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificAlarms_3Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificAlarms_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificAlarms_3Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificAlarms_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificAlarms_3Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificAlarms_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_3Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_3Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_3Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_4Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_4Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_4Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_4Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_4Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_4Interrupt u0.word_0
#endif
/*@}*/
/*@}*/
