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
#ifndef AQ_HHD_ANG_REGS_DEFINES_HEADER
#define AQ_HHD_ANG_REGS_DEFINES_HEADER


/*-----------------------------------------------------------------------------*/
/*Access macro definitions                                                     */
/*-----------------------------------------------------------------------------*/
/*! \brief Base register address of structure AQ_AutonegotiationStandardControl_1_HHD */
#define AQ_AutonegotiationStandardControl_1_HHD_baseRegisterAddress 0x0000
/*! \brief MMD address of structure AQ_AutonegotiationStandardControl_1_HHD */
#define AQ_AutonegotiationStandardControl_1_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure reset in AQ_AutonegotiationStandardControl_1_HHD */
#define AQ_AutonegotiationStandardControl_1_HHD_reset 0
/*! \brief Preprocessor variable to relate field to bit position in structure reset in AQ_AutonegotiationStandardControl_1_HHD */
#define bits_AQ_AutonegotiationStandardControl_1_HHD_reset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reset in AQ_AutonegotiationStandardControl_1_HHD */
#define word_AQ_AutonegotiationStandardControl_1_HHD_reset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPageControl in AQ_AutonegotiationStandardControl_1_HHD */
#define AQ_AutonegotiationStandardControl_1_HHD_extendedNextPageControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPageControl in AQ_AutonegotiationStandardControl_1_HHD */
#define bits_AQ_AutonegotiationStandardControl_1_HHD_extendedNextPageControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPageControl in AQ_AutonegotiationStandardControl_1_HHD */
#define word_AQ_AutonegotiationStandardControl_1_HHD_extendedNextPageControl u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationEnable in AQ_AutonegotiationStandardControl_1_HHD */
#define AQ_AutonegotiationStandardControl_1_HHD_autonegotiationEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationEnable in AQ_AutonegotiationStandardControl_1_HHD */
#define bits_AQ_AutonegotiationStandardControl_1_HHD_autonegotiationEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationEnable in AQ_AutonegotiationStandardControl_1_HHD */
#define word_AQ_AutonegotiationStandardControl_1_HHD_autonegotiationEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure restartAutonegotiation in AQ_AutonegotiationStandardControl_1_HHD */
#define AQ_AutonegotiationStandardControl_1_HHD_restartAutonegotiation 0
/*! \brief Preprocessor variable to relate field to bit position in structure restartAutonegotiation in AQ_AutonegotiationStandardControl_1_HHD */
#define bits_AQ_AutonegotiationStandardControl_1_HHD_restartAutonegotiation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure restartAutonegotiation in AQ_AutonegotiationStandardControl_1_HHD */
#define word_AQ_AutonegotiationStandardControl_1_HHD_restartAutonegotiation u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationStandardStatus_1_HHD */
#define AQ_AutonegotiationStandardStatus_1_HHD_baseRegisterAddress 0x0001
/*! \brief MMD address of structure AQ_AutonegotiationStandardStatus_1_HHD */
#define AQ_AutonegotiationStandardStatus_1_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure parallelDetectionFault in AQ_AutonegotiationStandardStatus_1_HHD */
#define AQ_AutonegotiationStandardStatus_1_HHD_parallelDetectionFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure parallelDetectionFault in AQ_AutonegotiationStandardStatus_1_HHD */
#define bits_AQ_AutonegotiationStandardStatus_1_HHD_parallelDetectionFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure parallelDetectionFault in AQ_AutonegotiationStandardStatus_1_HHD */
#define word_AQ_AutonegotiationStandardStatus_1_HHD_parallelDetectionFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPageStatus in AQ_AutonegotiationStandardStatus_1_HHD */
#define AQ_AutonegotiationStandardStatus_1_HHD_extendedNextPageStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPageStatus in AQ_AutonegotiationStandardStatus_1_HHD */
#define bits_AQ_AutonegotiationStandardStatus_1_HHD_extendedNextPageStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPageStatus in AQ_AutonegotiationStandardStatus_1_HHD */
#define word_AQ_AutonegotiationStandardStatus_1_HHD_extendedNextPageStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pageReceived in AQ_AutonegotiationStandardStatus_1_HHD */
#define AQ_AutonegotiationStandardStatus_1_HHD_pageReceived 0
/*! \brief Preprocessor variable to relate field to bit position in structure pageReceived in AQ_AutonegotiationStandardStatus_1_HHD */
#define bits_AQ_AutonegotiationStandardStatus_1_HHD_pageReceived u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pageReceived in AQ_AutonegotiationStandardStatus_1_HHD */
#define word_AQ_AutonegotiationStandardStatus_1_HHD_pageReceived u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationComplete in AQ_AutonegotiationStandardStatus_1_HHD */
#define AQ_AutonegotiationStandardStatus_1_HHD_autonegotiationComplete 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationComplete in AQ_AutonegotiationStandardStatus_1_HHD */
#define bits_AQ_AutonegotiationStandardStatus_1_HHD_autonegotiationComplete u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationComplete in AQ_AutonegotiationStandardStatus_1_HHD */
#define word_AQ_AutonegotiationStandardStatus_1_HHD_autonegotiationComplete u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure remoteFault in AQ_AutonegotiationStandardStatus_1_HHD */
#define AQ_AutonegotiationStandardStatus_1_HHD_remoteFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure remoteFault in AQ_AutonegotiationStandardStatus_1_HHD */
#define bits_AQ_AutonegotiationStandardStatus_1_HHD_remoteFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure remoteFault in AQ_AutonegotiationStandardStatus_1_HHD */
#define word_AQ_AutonegotiationStandardStatus_1_HHD_remoteFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationAbility in AQ_AutonegotiationStandardStatus_1_HHD */
#define AQ_AutonegotiationStandardStatus_1_HHD_autonegotiationAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationAbility in AQ_AutonegotiationStandardStatus_1_HHD */
#define bits_AQ_AutonegotiationStandardStatus_1_HHD_autonegotiationAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationAbility in AQ_AutonegotiationStandardStatus_1_HHD */
#define word_AQ_AutonegotiationStandardStatus_1_HHD_autonegotiationAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkStatus in AQ_AutonegotiationStandardStatus_1_HHD */
#define AQ_AutonegotiationStandardStatus_1_HHD_linkStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkStatus in AQ_AutonegotiationStandardStatus_1_HHD */
#define bits_AQ_AutonegotiationStandardStatus_1_HHD_linkStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkStatus in AQ_AutonegotiationStandardStatus_1_HHD */
#define word_AQ_AutonegotiationStandardStatus_1_HHD_linkStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerAutonegotiationAbility in AQ_AutonegotiationStandardStatus_1_HHD */
#define AQ_AutonegotiationStandardStatus_1_HHD_linkPartnerAutonegotiationAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerAutonegotiationAbility in AQ_AutonegotiationStandardStatus_1_HHD */
#define bits_AQ_AutonegotiationStandardStatus_1_HHD_linkPartnerAutonegotiationAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerAutonegotiationAbility in AQ_AutonegotiationStandardStatus_1_HHD */
#define word_AQ_AutonegotiationStandardStatus_1_HHD_linkPartnerAutonegotiationAbility u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationStandardDeviceIdentifier_HHD */
#define AQ_AutonegotiationStandardDeviceIdentifier_HHD_baseRegisterAddress 0x0002
/*! \brief MMD address of structure AQ_AutonegotiationStandardDeviceIdentifier_HHD */
#define AQ_AutonegotiationStandardDeviceIdentifier_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdMSW in AQ_AutonegotiationStandardDeviceIdentifier_HHD */
#define AQ_AutonegotiationStandardDeviceIdentifier_HHD_deviceIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdMSW in AQ_AutonegotiationStandardDeviceIdentifier_HHD */
#define bits_AQ_AutonegotiationStandardDeviceIdentifier_HHD_deviceIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdMSW in AQ_AutonegotiationStandardDeviceIdentifier_HHD */
#define word_AQ_AutonegotiationStandardDeviceIdentifier_HHD_deviceIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdLSW in AQ_AutonegotiationStandardDeviceIdentifier_HHD */
#define AQ_AutonegotiationStandardDeviceIdentifier_HHD_deviceIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdLSW in AQ_AutonegotiationStandardDeviceIdentifier_HHD */
#define bits_AQ_AutonegotiationStandardDeviceIdentifier_HHD_deviceIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdLSW in AQ_AutonegotiationStandardDeviceIdentifier_HHD */
#define word_AQ_AutonegotiationStandardDeviceIdentifier_HHD_deviceIdLSW u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define AQ_AutonegotiationStandardDevicesInPackage_HHD_baseRegisterAddress 0x0005
/*! \brief MMD address of structure AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define AQ_AutonegotiationStandardDevicesInPackage_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define AQ_AutonegotiationStandardDevicesInPackage_HHD_autonegotiationPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_HHD_autonegotiationPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define word_AQ_AutonegotiationStandardDevicesInPackage_HHD_autonegotiationPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tcPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define AQ_AutonegotiationStandardDevicesInPackage_HHD_tcPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure tcPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_HHD_tcPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tcPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define word_AQ_AutonegotiationStandardDevicesInPackage_HHD_tcPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure dteXsPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define AQ_AutonegotiationStandardDevicesInPackage_HHD_dteXsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure dteXsPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_HHD_dteXsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure dteXsPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define word_AQ_AutonegotiationStandardDevicesInPackage_HHD_dteXsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_Present in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define AQ_AutonegotiationStandardDevicesInPackage_HHD_phyXS_Present 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_Present in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_HHD_phyXS_Present u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_Present in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define word_AQ_AutonegotiationStandardDevicesInPackage_HHD_phyXS_Present u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define AQ_AutonegotiationStandardDevicesInPackage_HHD_pcsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_HHD_pcsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define word_AQ_AutonegotiationStandardDevicesInPackage_HHD_pcsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure wisPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define AQ_AutonegotiationStandardDevicesInPackage_HHD_wisPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure wisPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_HHD_wisPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure wisPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define word_AQ_AutonegotiationStandardDevicesInPackage_HHD_wisPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define AQ_AutonegotiationStandardDevicesInPackage_HHD_pmaPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_HHD_pmaPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define word_AQ_AutonegotiationStandardDevicesInPackage_HHD_pmaPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clause_22RegistersPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define AQ_AutonegotiationStandardDevicesInPackage_HHD_clause_22RegistersPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22RegistersPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_HHD_clause_22RegistersPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clause_22RegistersPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define word_AQ_AutonegotiationStandardDevicesInPackage_HHD_clause_22RegistersPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_2Present in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define AQ_AutonegotiationStandardDevicesInPackage_HHD_vendorSpecificDevice_2Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_2Present in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_HHD_vendorSpecificDevice_2Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_2Present in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define word_AQ_AutonegotiationStandardDevicesInPackage_HHD_vendorSpecificDevice_2Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_1Present in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define AQ_AutonegotiationStandardDevicesInPackage_HHD_vendorSpecificDevice_1Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_1Present in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_HHD_vendorSpecificDevice_1Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_1Present in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define word_AQ_AutonegotiationStandardDevicesInPackage_HHD_vendorSpecificDevice_1Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure clause_22ExtensionPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define AQ_AutonegotiationStandardDevicesInPackage_HHD_clause_22ExtensionPresent 1
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22ExtensionPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define bits_AQ_AutonegotiationStandardDevicesInPackage_HHD_clause_22ExtensionPresent u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure clause_22ExtensionPresent in AQ_AutonegotiationStandardDevicesInPackage_HHD */
#define word_AQ_AutonegotiationStandardDevicesInPackage_HHD_clause_22ExtensionPresent u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationStandardStatus_2_HHD */
#define AQ_AutonegotiationStandardStatus_2_HHD_baseRegisterAddress 0x0008
/*! \brief MMD address of structure AQ_AutonegotiationStandardStatus_2_HHD */
#define AQ_AutonegotiationStandardStatus_2_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure devicePresent in AQ_AutonegotiationStandardStatus_2_HHD */
#define AQ_AutonegotiationStandardStatus_2_HHD_devicePresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure devicePresent in AQ_AutonegotiationStandardStatus_2_HHD */
#define bits_AQ_AutonegotiationStandardStatus_2_HHD_devicePresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure devicePresent in AQ_AutonegotiationStandardStatus_2_HHD */
#define word_AQ_AutonegotiationStandardStatus_2_HHD_devicePresent u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationStandardPackageIdentifier_HHD */
#define AQ_AutonegotiationStandardPackageIdentifier_HHD_baseRegisterAddress 0x000E
/*! \brief MMD address of structure AQ_AutonegotiationStandardPackageIdentifier_HHD */
#define AQ_AutonegotiationStandardPackageIdentifier_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure packageIdMSW in AQ_AutonegotiationStandardPackageIdentifier_HHD */
#define AQ_AutonegotiationStandardPackageIdentifier_HHD_packageIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdMSW in AQ_AutonegotiationStandardPackageIdentifier_HHD */
#define bits_AQ_AutonegotiationStandardPackageIdentifier_HHD_packageIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure packageIdMSW in AQ_AutonegotiationStandardPackageIdentifier_HHD */
#define word_AQ_AutonegotiationStandardPackageIdentifier_HHD_packageIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure packageIdLSW in AQ_AutonegotiationStandardPackageIdentifier_HHD */
#define AQ_AutonegotiationStandardPackageIdentifier_HHD_packageIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdLSW in AQ_AutonegotiationStandardPackageIdentifier_HHD */
#define bits_AQ_AutonegotiationStandardPackageIdentifier_HHD_packageIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure packageIdLSW in AQ_AutonegotiationStandardPackageIdentifier_HHD */
#define word_AQ_AutonegotiationStandardPackageIdentifier_HHD_packageIdLSW u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationAdvertisementRegister_HHD */
#define AQ_AutonegotiationAdvertisementRegister_HHD_baseRegisterAddress 0x0010
/*! \brief MMD address of structure AQ_AutonegotiationAdvertisementRegister_HHD */
#define AQ_AutonegotiationAdvertisementRegister_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure nextPageAbility in AQ_AutonegotiationAdvertisementRegister_HHD */
#define AQ_AutonegotiationAdvertisementRegister_HHD_nextPageAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure nextPageAbility in AQ_AutonegotiationAdvertisementRegister_HHD */
#define bits_AQ_AutonegotiationAdvertisementRegister_HHD_nextPageAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nextPageAbility in AQ_AutonegotiationAdvertisementRegister_HHD */
#define word_AQ_AutonegotiationAdvertisementRegister_HHD_nextPageAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure advertisementRemoteFault in AQ_AutonegotiationAdvertisementRegister_HHD */
#define AQ_AutonegotiationAdvertisementRegister_HHD_advertisementRemoteFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure advertisementRemoteFault in AQ_AutonegotiationAdvertisementRegister_HHD */
#define bits_AQ_AutonegotiationAdvertisementRegister_HHD_advertisementRemoteFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure advertisementRemoteFault in AQ_AutonegotiationAdvertisementRegister_HHD */
#define word_AQ_AutonegotiationAdvertisementRegister_HHD_advertisementRemoteFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPageAbility in AQ_AutonegotiationAdvertisementRegister_HHD */
#define AQ_AutonegotiationAdvertisementRegister_HHD_extendedNextPageAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPageAbility in AQ_AutonegotiationAdvertisementRegister_HHD */
#define bits_AQ_AutonegotiationAdvertisementRegister_HHD_extendedNextPageAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPageAbility in AQ_AutonegotiationAdvertisementRegister_HHD */
#define word_AQ_AutonegotiationAdvertisementRegister_HHD_extendedNextPageAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure technologyAbilityField in AQ_AutonegotiationAdvertisementRegister_HHD */
#define AQ_AutonegotiationAdvertisementRegister_HHD_technologyAbilityField 0
/*! \brief Preprocessor variable to relate field to bit position in structure technologyAbilityField in AQ_AutonegotiationAdvertisementRegister_HHD */
#define bits_AQ_AutonegotiationAdvertisementRegister_HHD_technologyAbilityField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure technologyAbilityField in AQ_AutonegotiationAdvertisementRegister_HHD */
#define word_AQ_AutonegotiationAdvertisementRegister_HHD_technologyAbilityField u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure selectorField in AQ_AutonegotiationAdvertisementRegister_HHD */
#define AQ_AutonegotiationAdvertisementRegister_HHD_selectorField 0
/*! \brief Preprocessor variable to relate field to bit position in structure selectorField in AQ_AutonegotiationAdvertisementRegister_HHD */
#define bits_AQ_AutonegotiationAdvertisementRegister_HHD_selectorField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure selectorField in AQ_AutonegotiationAdvertisementRegister_HHD */
#define word_AQ_AutonegotiationAdvertisementRegister_HHD_selectorField u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_baseRegisterAddress 0x0013
/*! \brief MMD address of structure AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerNextPageAbility in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerNextPageAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerNextPageAbility in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerNextPageAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerNextPageAbility in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerNextPageAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerBasePageAcknowledge in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerBasePageAcknowledge 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerBasePageAcknowledge in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerBasePageAcknowledge u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerBasePageAcknowledge in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerBasePageAcknowledge u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerRemoteFault in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerRemoteFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerRemoteFault in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerRemoteFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerRemoteFault in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerRemoteFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerExtendedNextPageAbility in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerExtendedNextPageAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerExtendedNextPageAbility in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerExtendedNextPageAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerExtendedNextPageAbility in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerExtendedNextPageAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTechnologyAbilityField in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerTechnologyAbilityField 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTechnologyAbilityField in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerTechnologyAbilityField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTechnologyAbilityField in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerTechnologyAbilityField u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerSelectorField in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerSelectorField 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerSelectorField in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerSelectorField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerSelectorField in AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_HHD_linkPartnerSelectorField u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_baseRegisterAddress 0x0016
/*! \brief MMD address of structure AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure nextPage in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_nextPage 0
/*! \brief Preprocessor variable to relate field to bit position in structure nextPage in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define bits_AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_nextPage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nextPage in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define word_AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_nextPage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure messagePage in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_messagePage 0
/*! \brief Preprocessor variable to relate field to bit position in structure messagePage in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define bits_AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_messagePage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure messagePage in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define word_AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_messagePage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure acknowledge_2 in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_acknowledge_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure acknowledge_2 in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define bits_AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_acknowledge_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure acknowledge_2 in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define word_AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_acknowledge_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure toggle in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_toggle 0
/*! \brief Preprocessor variable to relate field to bit position in structure toggle in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define bits_AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_toggle u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure toggle in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define word_AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_toggle u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure messageCodeField in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_messageCodeField 0
/*! \brief Preprocessor variable to relate field to bit position in structure messageCodeField in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define bits_AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_messageCodeField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure messageCodeField in AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD */
#define word_AQ_AutonegotiationExtendedNextPageTransmitRegister_HHD_messageCodeField u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD */
#define AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD_baseRegisterAddress 0x0017
/*! \brief MMD address of structure AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD */
#define AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure unformattedCodeField_1 in AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD */
#define AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD_unformattedCodeField_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure unformattedCodeField_1 in AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD */
#define bits_AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD_unformattedCodeField_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure unformattedCodeField_1 in AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD */
#define word_AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD_unformattedCodeField_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure unformattedCodeField_2 in AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD */
#define AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD_unformattedCodeField_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure unformattedCodeField_2 in AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD */
#define bits_AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD_unformattedCodeField_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure unformattedCodeField_2 in AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD */
#define word_AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_HHD_unformattedCodeField_2 u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_baseRegisterAddress 0x0019
/*! \brief MMD address of structure AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerNextPage in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerNextPage 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerNextPage in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerNextPage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerNextPage in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerNextPage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerExtendedNextPageAcknowledge in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerExtendedNextPageAcknowledge 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerExtendedNextPageAcknowledge in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerExtendedNextPageAcknowledge u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerExtendedNextPageAcknowledge in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerExtendedNextPageAcknowledge u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerMessagePage in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerMessagePage 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerMessagePage in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerMessagePage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerMessagePage in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerMessagePage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerAcknowledge_2 in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerAcknowledge_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerAcknowledge_2 in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerAcknowledge_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerAcknowledge_2 in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerAcknowledge_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerToggle in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerToggle 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerToggle in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerToggle u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerToggle in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerToggle u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerMessageCodeField in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerMessageCodeField 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerMessageCodeField in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerMessageCodeField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerMessageCodeField in AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_HHD_linkPartnerMessageCodeField u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD_baseRegisterAddress 0x001A
/*! \brief MMD address of structure AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerUnformattedCodeField_1 in AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD_linkPartnerUnformattedCodeField_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerUnformattedCodeField_1 in AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD_linkPartnerUnformattedCodeField_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerUnformattedCodeField_1 in AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD_linkPartnerUnformattedCodeField_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerUnformattedCodeField_2 in AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD */
#define AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD_linkPartnerUnformattedCodeField_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerUnformattedCodeField_2 in AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD */
#define bits_AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD_linkPartnerUnformattedCodeField_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerUnformattedCodeField_2 in AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD */
#define word_AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_HHD_linkPartnerUnformattedCodeField_2 u1.word_1

/*! \brief Base register address of structure AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define AQ_Autonegotiation10GBaseT_ControlRegister_HHD_baseRegisterAddress 0x0020
/*! \brief MMD address of structure AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define AQ_Autonegotiation10GBaseT_ControlRegister_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure master_slaveManualConfigurationEnable in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define AQ_Autonegotiation10GBaseT_ControlRegister_HHD_master_slaveManualConfigurationEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure master_slaveManualConfigurationEnable in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_ControlRegister_HHD_master_slaveManualConfigurationEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure master_slaveManualConfigurationEnable in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_ControlRegister_HHD_master_slaveManualConfigurationEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure master_slaveConfiguration in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define AQ_Autonegotiation10GBaseT_ControlRegister_HHD_master_slaveConfiguration 0
/*! \brief Preprocessor variable to relate field to bit position in structure master_slaveConfiguration in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_ControlRegister_HHD_master_slaveConfiguration u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure master_slaveConfiguration in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_ControlRegister_HHD_master_slaveConfiguration u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure portType in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define AQ_Autonegotiation10GBaseT_ControlRegister_HHD_portType 0
/*! \brief Preprocessor variable to relate field to bit position in structure portType in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_ControlRegister_HHD_portType u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure portType in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_ControlRegister_HHD_portType u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tAbility in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define AQ_Autonegotiation10GBaseT_ControlRegister_HHD__10gbase_tAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tAbility in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_ControlRegister_HHD__10gbase_tAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tAbility in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_ControlRegister_HHD__10gbase_tAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldPmaTrainingResetRequest in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define AQ_Autonegotiation10GBaseT_ControlRegister_HHD_ldPmaTrainingResetRequest 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldPmaTrainingResetRequest in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_ControlRegister_HHD_ldPmaTrainingResetRequest u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldPmaTrainingResetRequest in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_ControlRegister_HHD_ldPmaTrainingResetRequest u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldFastRetrainAbility in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define AQ_Autonegotiation10GBaseT_ControlRegister_HHD_ldFastRetrainAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldFastRetrainAbility in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_ControlRegister_HHD_ldFastRetrainAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldFastRetrainAbility in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_ControlRegister_HHD_ldFastRetrainAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldLoopTimingAbility in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define AQ_Autonegotiation10GBaseT_ControlRegister_HHD_ldLoopTimingAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldLoopTimingAbility in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_ControlRegister_HHD_ldLoopTimingAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldLoopTimingAbility in AQ_Autonegotiation10GBaseT_ControlRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_ControlRegister_HHD_ldLoopTimingAbility u0.word_0

/*! \brief Base register address of structure AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define AQ_Autonegotiation10GBaseT_StatusRegister_HHD_baseRegisterAddress 0x0021
/*! \brief MMD address of structure AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define AQ_Autonegotiation10GBaseT_StatusRegister_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure master_slaveConfigurationFault in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define AQ_Autonegotiation10GBaseT_StatusRegister_HHD_master_slaveConfigurationFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure master_slaveConfigurationFault in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_master_slaveConfigurationFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure master_slaveConfigurationFault in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_master_slaveConfigurationFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure master_slaveConfigurationResolution in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define AQ_Autonegotiation10GBaseT_StatusRegister_HHD_master_slaveConfigurationResolution 0
/*! \brief Preprocessor variable to relate field to bit position in structure master_slaveConfigurationResolution in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_master_slaveConfigurationResolution u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure master_slaveConfigurationResolution in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_master_slaveConfigurationResolution u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure localReceiverStatus in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define AQ_Autonegotiation10GBaseT_StatusRegister_HHD_localReceiverStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure localReceiverStatus in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_localReceiverStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure localReceiverStatus in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_localReceiverStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure remoteReceiverStatus in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define AQ_Autonegotiation10GBaseT_StatusRegister_HHD_remoteReceiverStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure remoteReceiverStatus in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_remoteReceiverStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure remoteReceiverStatus in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_remoteReceiverStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner10GBaseT_Ability in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define AQ_Autonegotiation10GBaseT_StatusRegister_HHD_linkPartner10GBaseT_Ability 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner10GBaseT_Ability in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_linkPartner10GBaseT_Ability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner10GBaseT_Ability in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_linkPartner10GBaseT_Ability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerLoopTimingAbility in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define AQ_Autonegotiation10GBaseT_StatusRegister_HHD_linkPartnerLoopTimingAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerLoopTimingAbility in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_linkPartnerLoopTimingAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerLoopTimingAbility in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_linkPartnerLoopTimingAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTrainingResetRequest in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define AQ_Autonegotiation10GBaseT_StatusRegister_HHD_linkPartnerTrainingResetRequest 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTrainingResetRequest in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_linkPartnerTrainingResetRequest u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTrainingResetRequest in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_linkPartnerTrainingResetRequest u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerFastRetrainAbility in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define AQ_Autonegotiation10GBaseT_StatusRegister_HHD_linkPartnerFastRetrainAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerFastRetrainAbility in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define bits_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_linkPartnerFastRetrainAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerFastRetrainAbility in AQ_Autonegotiation10GBaseT_StatusRegister_HHD */
#define word_AQ_Autonegotiation10GBaseT_StatusRegister_HHD_linkPartnerFastRetrainAbility u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define AQ_AutonegotiationEeeAdvertisementRegister_HHD_baseRegisterAddress 0x003C
/*! \brief MMD address of structure AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define AQ_AutonegotiationEeeAdvertisementRegister_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_krEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define AQ_AutonegotiationEeeAdvertisementRegister_HHD__10gbase_krEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_krEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define bits_AQ_AutonegotiationEeeAdvertisementRegister_HHD__10gbase_krEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_krEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define word_AQ_AutonegotiationEeeAdvertisementRegister_HHD__10gbase_krEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_kx4Eee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define AQ_AutonegotiationEeeAdvertisementRegister_HHD__10gbase_kx4Eee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_kx4Eee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define bits_AQ_AutonegotiationEeeAdvertisementRegister_HHD__10gbase_kx4Eee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_kx4Eee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define word_AQ_AutonegotiationEeeAdvertisementRegister_HHD__10gbase_kx4Eee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _1000base_kxEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define AQ_AutonegotiationEeeAdvertisementRegister_HHD__1000base_kxEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _1000base_kxEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define bits_AQ_AutonegotiationEeeAdvertisementRegister_HHD__1000base_kxEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _1000base_kxEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define word_AQ_AutonegotiationEeeAdvertisementRegister_HHD__1000base_kxEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gbase_tEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define AQ_AutonegotiationEeeAdvertisementRegister_HHD__10gbase_tEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gbase_tEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define bits_AQ_AutonegotiationEeeAdvertisementRegister_HHD__10gbase_tEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gbase_tEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define word_AQ_AutonegotiationEeeAdvertisementRegister_HHD__10gbase_tEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _1000base_tEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define AQ_AutonegotiationEeeAdvertisementRegister_HHD__1000base_tEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _1000base_tEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define bits_AQ_AutonegotiationEeeAdvertisementRegister_HHD__1000base_tEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _1000base_tEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define word_AQ_AutonegotiationEeeAdvertisementRegister_HHD__1000base_tEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _100base_txEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define AQ_AutonegotiationEeeAdvertisementRegister_HHD__100base_txEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _100base_txEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define bits_AQ_AutonegotiationEeeAdvertisementRegister_HHD__100base_txEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _100base_txEee in AQ_AutonegotiationEeeAdvertisementRegister_HHD */
#define word_AQ_AutonegotiationEeeAdvertisementRegister_HHD__100base_txEee u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_baseRegisterAddress 0x003D
/*! \brief MMD address of structure AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner10GBaseK_rEee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner10GBaseK_rEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner10GBaseK_rEee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define bits_AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner10GBaseK_rEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner10GBaseK_rEee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define word_AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner10GBaseK_rEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner10GBaseK_x4Eee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner10GBaseK_x4Eee 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner10GBaseK_x4Eee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define bits_AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner10GBaseK_x4Eee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner10GBaseK_x4Eee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define word_AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner10GBaseK_x4Eee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner_1000base_kxEee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner_1000base_kxEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner_1000base_kxEee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define bits_AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner_1000base_kxEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner_1000base_kxEee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define word_AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner_1000base_kxEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner10GBaseT_Eee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner10GBaseT_Eee 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner10GBaseT_Eee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define bits_AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner10GBaseT_Eee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner10GBaseT_Eee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define word_AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner10GBaseT_Eee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner1000BaseT_Eee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner1000BaseT_Eee 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner1000BaseT_Eee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define bits_AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner1000BaseT_Eee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner1000BaseT_Eee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define word_AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner1000BaseT_Eee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner_100base_txEee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner_100base_txEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner_100base_txEee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define bits_AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner_100base_txEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner_100base_txEee in AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD */
#define word_AQ_AutonegotiationEeeLinkPartnerAbilityRegister_HHD_linkPartner_100base_txEee u0.word_0

/*! \brief Base register address of structure AQ_Kr0AutonegotiationControl_HHD */
#define AQ_Kr0AutonegotiationControl_HHD_baseRegisterAddress 0xC200
/*! \brief MMD address of structure AQ_Kr0AutonegotiationControl_HHD */
#define AQ_Kr0AutonegotiationControl_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure reset in AQ_Kr0AutonegotiationControl_HHD */
#define AQ_Kr0AutonegotiationControl_HHD_reset 0
/*! \brief Preprocessor variable to relate field to bit position in structure reset in AQ_Kr0AutonegotiationControl_HHD */
#define bits_AQ_Kr0AutonegotiationControl_HHD_reset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reset in AQ_Kr0AutonegotiationControl_HHD */
#define word_AQ_Kr0AutonegotiationControl_HHD_reset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_0 in AQ_Kr0AutonegotiationControl_HHD */
#define AQ_Kr0AutonegotiationControl_HHD_reserved_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_0 in AQ_Kr0AutonegotiationControl_HHD */
#define bits_AQ_Kr0AutonegotiationControl_HHD_reserved_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_0 in AQ_Kr0AutonegotiationControl_HHD */
#define word_AQ_Kr0AutonegotiationControl_HHD_reserved_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationEnable in AQ_Kr0AutonegotiationControl_HHD */
#define AQ_Kr0AutonegotiationControl_HHD_autonegotiationEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationEnable in AQ_Kr0AutonegotiationControl_HHD */
#define bits_AQ_Kr0AutonegotiationControl_HHD_autonegotiationEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationEnable in AQ_Kr0AutonegotiationControl_HHD */
#define word_AQ_Kr0AutonegotiationControl_HHD_autonegotiationEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_1 in AQ_Kr0AutonegotiationControl_HHD */
#define AQ_Kr0AutonegotiationControl_HHD_reserved_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_1 in AQ_Kr0AutonegotiationControl_HHD */
#define bits_AQ_Kr0AutonegotiationControl_HHD_reserved_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_1 in AQ_Kr0AutonegotiationControl_HHD */
#define word_AQ_Kr0AutonegotiationControl_HHD_reserved_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationRestart in AQ_Kr0AutonegotiationControl_HHD */
#define AQ_Kr0AutonegotiationControl_HHD_autonegotiationRestart 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationRestart in AQ_Kr0AutonegotiationControl_HHD */
#define bits_AQ_Kr0AutonegotiationControl_HHD_autonegotiationRestart u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationRestart in AQ_Kr0AutonegotiationControl_HHD */
#define word_AQ_Kr0AutonegotiationControl_HHD_autonegotiationRestart u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_2 in AQ_Kr0AutonegotiationControl_HHD */
#define AQ_Kr0AutonegotiationControl_HHD_reserved_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_2 in AQ_Kr0AutonegotiationControl_HHD */
#define bits_AQ_Kr0AutonegotiationControl_HHD_reserved_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_2 in AQ_Kr0AutonegotiationControl_HHD */
#define word_AQ_Kr0AutonegotiationControl_HHD_reserved_2 u0.word_0

/*! \brief Base register address of structure AQ_Kr0AutonegotiationStatus_HHD */
#define AQ_Kr0AutonegotiationStatus_HHD_baseRegisterAddress 0xC201
/*! \brief MMD address of structure AQ_Kr0AutonegotiationStatus_HHD */
#define AQ_Kr0AutonegotiationStatus_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure reserved_0 in AQ_Kr0AutonegotiationStatus_HHD */
#define AQ_Kr0AutonegotiationStatus_HHD_reserved_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_0 in AQ_Kr0AutonegotiationStatus_HHD */
#define bits_AQ_Kr0AutonegotiationStatus_HHD_reserved_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_0 in AQ_Kr0AutonegotiationStatus_HHD */
#define word_AQ_Kr0AutonegotiationStatus_HHD_reserved_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure parallelDetectionFault in AQ_Kr0AutonegotiationStatus_HHD */
#define AQ_Kr0AutonegotiationStatus_HHD_parallelDetectionFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure parallelDetectionFault in AQ_Kr0AutonegotiationStatus_HHD */
#define bits_AQ_Kr0AutonegotiationStatus_HHD_parallelDetectionFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure parallelDetectionFault in AQ_Kr0AutonegotiationStatus_HHD */
#define word_AQ_Kr0AutonegotiationStatus_HHD_parallelDetectionFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_1 in AQ_Kr0AutonegotiationStatus_HHD */
#define AQ_Kr0AutonegotiationStatus_HHD_reserved_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_1 in AQ_Kr0AutonegotiationStatus_HHD */
#define bits_AQ_Kr0AutonegotiationStatus_HHD_reserved_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_1 in AQ_Kr0AutonegotiationStatus_HHD */
#define word_AQ_Kr0AutonegotiationStatus_HHD_reserved_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pageReceived in AQ_Kr0AutonegotiationStatus_HHD */
#define AQ_Kr0AutonegotiationStatus_HHD_pageReceived 0
/*! \brief Preprocessor variable to relate field to bit position in structure pageReceived in AQ_Kr0AutonegotiationStatus_HHD */
#define bits_AQ_Kr0AutonegotiationStatus_HHD_pageReceived u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pageReceived in AQ_Kr0AutonegotiationStatus_HHD */
#define word_AQ_Kr0AutonegotiationStatus_HHD_pageReceived u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationComplete in AQ_Kr0AutonegotiationStatus_HHD */
#define AQ_Kr0AutonegotiationStatus_HHD_autonegotiationComplete 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationComplete in AQ_Kr0AutonegotiationStatus_HHD */
#define bits_AQ_Kr0AutonegotiationStatus_HHD_autonegotiationComplete u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationComplete in AQ_Kr0AutonegotiationStatus_HHD */
#define word_AQ_Kr0AutonegotiationStatus_HHD_autonegotiationComplete u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_2 in AQ_Kr0AutonegotiationStatus_HHD */
#define AQ_Kr0AutonegotiationStatus_HHD_reserved_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_2 in AQ_Kr0AutonegotiationStatus_HHD */
#define bits_AQ_Kr0AutonegotiationStatus_HHD_reserved_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_2 in AQ_Kr0AutonegotiationStatus_HHD */
#define word_AQ_Kr0AutonegotiationStatus_HHD_reserved_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationAbility in AQ_Kr0AutonegotiationStatus_HHD */
#define AQ_Kr0AutonegotiationStatus_HHD_autonegotiationAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationAbility in AQ_Kr0AutonegotiationStatus_HHD */
#define bits_AQ_Kr0AutonegotiationStatus_HHD_autonegotiationAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationAbility in AQ_Kr0AutonegotiationStatus_HHD */
#define word_AQ_Kr0AutonegotiationStatus_HHD_autonegotiationAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_3 in AQ_Kr0AutonegotiationStatus_HHD */
#define AQ_Kr0AutonegotiationStatus_HHD_reserved_3 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_3 in AQ_Kr0AutonegotiationStatus_HHD */
#define bits_AQ_Kr0AutonegotiationStatus_HHD_reserved_3 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_3 in AQ_Kr0AutonegotiationStatus_HHD */
#define word_AQ_Kr0AutonegotiationStatus_HHD_reserved_3 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerAutonegotiationAbility in AQ_Kr0AutonegotiationStatus_HHD */
#define AQ_Kr0AutonegotiationStatus_HHD_linkPartnerAutonegotiationAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerAutonegotiationAbility in AQ_Kr0AutonegotiationStatus_HHD */
#define bits_AQ_Kr0AutonegotiationStatus_HHD_linkPartnerAutonegotiationAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerAutonegotiationAbility in AQ_Kr0AutonegotiationStatus_HHD */
#define word_AQ_Kr0AutonegotiationStatus_HHD_linkPartnerAutonegotiationAbility u0.word_0

/*! \brief Base register address of structure AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_baseRegisterAddress 0xC210
/*! \brief MMD address of structure AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure nextPage in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_nextPage 0
/*! \brief Preprocessor variable to relate field to bit position in structure nextPage in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_nextPage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nextPage in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_nextPage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure acknowledge in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_acknowledge 0
/*! \brief Preprocessor variable to relate field to bit position in structure acknowledge in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_acknowledge u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure acknowledge in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_acknowledge u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure remoteFault in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_remoteFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure remoteFault in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_remoteFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure remoteFault in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_remoteFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_0 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_reserved_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_0 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_reserved_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_0 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_reserved_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pauseCapability in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_pauseCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure pauseCapability in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_pauseCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pauseCapability in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_pauseCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure echoedNonce in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_echoedNonce 0
/*! \brief Preprocessor variable to relate field to bit position in structure echoedNonce in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_echoedNonce u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure echoedNonce in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_echoedNonce u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure selectorField in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_selectorField 0
/*! \brief Preprocessor variable to relate field to bit position in structure selectorField in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_selectorField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure selectorField in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_selectorField u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure technologyAbilityBitsA3ToA10 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitsA3ToA10 1
/*! \brief Preprocessor variable to relate field to bit position in structure technologyAbilityBitsA3ToA10 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitsA3ToA10 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure technologyAbilityBitsA3ToA10 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitsA3ToA10 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure technologyAbilityBitA2 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA2 1
/*! \brief Preprocessor variable to relate field to bit position in structure technologyAbilityBitA2 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure technologyAbilityBitA2 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure technologyAbilityBitA1 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA1 1
/*! \brief Preprocessor variable to relate field to bit position in structure technologyAbilityBitA1 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure technologyAbilityBitA1 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure technologyAbilityBitA0 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA0 1
/*! \brief Preprocessor variable to relate field to bit position in structure technologyAbilityBitA0 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA0 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure technologyAbilityBitA0 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA0 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure transmittedNonce in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_transmittedNonce 1
/*! \brief Preprocessor variable to relate field to bit position in structure transmittedNonce in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_transmittedNonce u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure transmittedNonce in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_transmittedNonce u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure fecRequested in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_fecRequested 2
/*! \brief Preprocessor variable to relate field to bit position in structure fecRequested in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_fecRequested u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure fecRequested in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_fecRequested u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure fecAbility in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_fecAbility 2
/*! \brief Preprocessor variable to relate field to bit position in structure fecAbility in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_fecAbility u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure fecAbility in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_fecAbility u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure technologyAbilityBitsA11ToA24 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitsA11ToA24 2
/*! \brief Preprocessor variable to relate field to bit position in structure technologyAbilityBitsA11ToA24 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitsA11ToA24 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure technologyAbilityBitsA11ToA24 in AQ_Kr0AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationAdvertisementWord_HHD_technologyAbilityBitsA11ToA24 u2.word_2

/*! \brief Base register address of structure AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_baseRegisterAddress 0xC213
/*! \brief MMD address of structure AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerNextPage in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerNextPage 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerNextPage in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerNextPage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerNextPage in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerNextPage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerAcknowledge in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerAcknowledge 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerAcknowledge in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerAcknowledge u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerAcknowledge in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerAcknowledge u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerRemoteFault in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerRemoteFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerRemoteFault in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerRemoteFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerRemoteFault in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerRemoteFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_0 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_reserved_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_0 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_reserved_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_0 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_reserved_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerPauseCapability in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerPauseCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerPauseCapability in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerPauseCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerPauseCapability in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerPauseCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerEchoedNonce in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerEchoedNonce 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerEchoedNonce in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerEchoedNonce u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerEchoedNonce in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerEchoedNonce u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerSelectorField in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerSelectorField 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerSelectorField in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerSelectorField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerSelectorField in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerSelectorField u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTechnologyAbilityBitsA3ToA10 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitsA3ToA10 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTechnologyAbilityBitsA3ToA10 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitsA3ToA10 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTechnologyAbilityBitsA3ToA10 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitsA3ToA10 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTechnologyAbilityBitA2 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA2 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTechnologyAbilityBitA2 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTechnologyAbilityBitA2 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTechnologyAbilityBitA1 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA1 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTechnologyAbilityBitA1 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTechnologyAbilityBitA1 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTechnologyAbilityBitA0 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA0 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTechnologyAbilityBitA0 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA0 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTechnologyAbilityBitA0 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA0 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTransmittedNonce in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTransmittedNonce 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTransmittedNonce in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTransmittedNonce u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTransmittedNonce in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTransmittedNonce u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerFecRequested in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerFecRequested 2
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerFecRequested in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerFecRequested u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerFecRequested in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerFecRequested u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerFecAbility in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerFecAbility 2
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerFecAbility in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerFecAbility u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerFecAbility in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerFecAbility u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTechnologyAbilityBitsA11ToA24 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitsA11ToA24 2
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTechnologyAbilityBitsA11ToA24 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitsA11ToA24 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTechnologyAbilityBitsA11ToA24 in AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitsA11ToA24 u2.word_2

/*! \brief Base register address of structure AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD_baseRegisterAddress 0xC216
/*! \brief MMD address of structure AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPage_0 in AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPage_0 in AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPage_0 in AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPage_1 in AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPage_1 in AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPage_1 in AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPage_2 in AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPage_2 in AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define bits_AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPage_2 in AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define word_AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_2 u2.word_2

/*! \brief Base register address of structure AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_baseRegisterAddress 0xC219
/*! \brief MMD address of structure AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerExtendedNextPage_0 in AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerExtendedNextPage_0 in AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerExtendedNextPage_0 in AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerExtendedNextPage_1 in AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerExtendedNextPage_1 in AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerExtendedNextPage_1 in AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerExtendedNextPage_2 in AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerExtendedNextPage_2 in AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define bits_AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerExtendedNextPage_2 in AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define word_AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_2 u2.word_2

/*! \brief Base register address of structure AQ_Kr1AutonegotiationControl_HHD */
#define AQ_Kr1AutonegotiationControl_HHD_baseRegisterAddress 0xC300
/*! \brief MMD address of structure AQ_Kr1AutonegotiationControl_HHD */
#define AQ_Kr1AutonegotiationControl_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure reset in AQ_Kr1AutonegotiationControl_HHD */
#define AQ_Kr1AutonegotiationControl_HHD_reset 0
/*! \brief Preprocessor variable to relate field to bit position in structure reset in AQ_Kr1AutonegotiationControl_HHD */
#define bits_AQ_Kr1AutonegotiationControl_HHD_reset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reset in AQ_Kr1AutonegotiationControl_HHD */
#define word_AQ_Kr1AutonegotiationControl_HHD_reset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_0 in AQ_Kr1AutonegotiationControl_HHD */
#define AQ_Kr1AutonegotiationControl_HHD_reserved_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_0 in AQ_Kr1AutonegotiationControl_HHD */
#define bits_AQ_Kr1AutonegotiationControl_HHD_reserved_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_0 in AQ_Kr1AutonegotiationControl_HHD */
#define word_AQ_Kr1AutonegotiationControl_HHD_reserved_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationEnable in AQ_Kr1AutonegotiationControl_HHD */
#define AQ_Kr1AutonegotiationControl_HHD_autonegotiationEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationEnable in AQ_Kr1AutonegotiationControl_HHD */
#define bits_AQ_Kr1AutonegotiationControl_HHD_autonegotiationEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationEnable in AQ_Kr1AutonegotiationControl_HHD */
#define word_AQ_Kr1AutonegotiationControl_HHD_autonegotiationEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_1 in AQ_Kr1AutonegotiationControl_HHD */
#define AQ_Kr1AutonegotiationControl_HHD_reserved_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_1 in AQ_Kr1AutonegotiationControl_HHD */
#define bits_AQ_Kr1AutonegotiationControl_HHD_reserved_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_1 in AQ_Kr1AutonegotiationControl_HHD */
#define word_AQ_Kr1AutonegotiationControl_HHD_reserved_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationRestart in AQ_Kr1AutonegotiationControl_HHD */
#define AQ_Kr1AutonegotiationControl_HHD_autonegotiationRestart 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationRestart in AQ_Kr1AutonegotiationControl_HHD */
#define bits_AQ_Kr1AutonegotiationControl_HHD_autonegotiationRestart u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationRestart in AQ_Kr1AutonegotiationControl_HHD */
#define word_AQ_Kr1AutonegotiationControl_HHD_autonegotiationRestart u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_2 in AQ_Kr1AutonegotiationControl_HHD */
#define AQ_Kr1AutonegotiationControl_HHD_reserved_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_2 in AQ_Kr1AutonegotiationControl_HHD */
#define bits_AQ_Kr1AutonegotiationControl_HHD_reserved_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_2 in AQ_Kr1AutonegotiationControl_HHD */
#define word_AQ_Kr1AutonegotiationControl_HHD_reserved_2 u0.word_0

/*! \brief Base register address of structure AQ_Kr1AutonegotiationStatus_HHD */
#define AQ_Kr1AutonegotiationStatus_HHD_baseRegisterAddress 0xC301
/*! \brief MMD address of structure AQ_Kr1AutonegotiationStatus_HHD */
#define AQ_Kr1AutonegotiationStatus_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure reserved_0 in AQ_Kr1AutonegotiationStatus_HHD */
#define AQ_Kr1AutonegotiationStatus_HHD_reserved_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_0 in AQ_Kr1AutonegotiationStatus_HHD */
#define bits_AQ_Kr1AutonegotiationStatus_HHD_reserved_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_0 in AQ_Kr1AutonegotiationStatus_HHD */
#define word_AQ_Kr1AutonegotiationStatus_HHD_reserved_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure parallelDetectionFault in AQ_Kr1AutonegotiationStatus_HHD */
#define AQ_Kr1AutonegotiationStatus_HHD_parallelDetectionFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure parallelDetectionFault in AQ_Kr1AutonegotiationStatus_HHD */
#define bits_AQ_Kr1AutonegotiationStatus_HHD_parallelDetectionFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure parallelDetectionFault in AQ_Kr1AutonegotiationStatus_HHD */
#define word_AQ_Kr1AutonegotiationStatus_HHD_parallelDetectionFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_1 in AQ_Kr1AutonegotiationStatus_HHD */
#define AQ_Kr1AutonegotiationStatus_HHD_reserved_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_1 in AQ_Kr1AutonegotiationStatus_HHD */
#define bits_AQ_Kr1AutonegotiationStatus_HHD_reserved_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_1 in AQ_Kr1AutonegotiationStatus_HHD */
#define word_AQ_Kr1AutonegotiationStatus_HHD_reserved_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pageReceived in AQ_Kr1AutonegotiationStatus_HHD */
#define AQ_Kr1AutonegotiationStatus_HHD_pageReceived 0
/*! \brief Preprocessor variable to relate field to bit position in structure pageReceived in AQ_Kr1AutonegotiationStatus_HHD */
#define bits_AQ_Kr1AutonegotiationStatus_HHD_pageReceived u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pageReceived in AQ_Kr1AutonegotiationStatus_HHD */
#define word_AQ_Kr1AutonegotiationStatus_HHD_pageReceived u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationComplete in AQ_Kr1AutonegotiationStatus_HHD */
#define AQ_Kr1AutonegotiationStatus_HHD_autonegotiationComplete 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationComplete in AQ_Kr1AutonegotiationStatus_HHD */
#define bits_AQ_Kr1AutonegotiationStatus_HHD_autonegotiationComplete u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationComplete in AQ_Kr1AutonegotiationStatus_HHD */
#define word_AQ_Kr1AutonegotiationStatus_HHD_autonegotiationComplete u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_2 in AQ_Kr1AutonegotiationStatus_HHD */
#define AQ_Kr1AutonegotiationStatus_HHD_reserved_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_2 in AQ_Kr1AutonegotiationStatus_HHD */
#define bits_AQ_Kr1AutonegotiationStatus_HHD_reserved_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_2 in AQ_Kr1AutonegotiationStatus_HHD */
#define word_AQ_Kr1AutonegotiationStatus_HHD_reserved_2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationAbility in AQ_Kr1AutonegotiationStatus_HHD */
#define AQ_Kr1AutonegotiationStatus_HHD_autonegotiationAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationAbility in AQ_Kr1AutonegotiationStatus_HHD */
#define bits_AQ_Kr1AutonegotiationStatus_HHD_autonegotiationAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationAbility in AQ_Kr1AutonegotiationStatus_HHD */
#define word_AQ_Kr1AutonegotiationStatus_HHD_autonegotiationAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_3 in AQ_Kr1AutonegotiationStatus_HHD */
#define AQ_Kr1AutonegotiationStatus_HHD_reserved_3 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_3 in AQ_Kr1AutonegotiationStatus_HHD */
#define bits_AQ_Kr1AutonegotiationStatus_HHD_reserved_3 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_3 in AQ_Kr1AutonegotiationStatus_HHD */
#define word_AQ_Kr1AutonegotiationStatus_HHD_reserved_3 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerAutonegotiationAbility in AQ_Kr1AutonegotiationStatus_HHD */
#define AQ_Kr1AutonegotiationStatus_HHD_linkPartnerAutonegotiationAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerAutonegotiationAbility in AQ_Kr1AutonegotiationStatus_HHD */
#define bits_AQ_Kr1AutonegotiationStatus_HHD_linkPartnerAutonegotiationAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerAutonegotiationAbility in AQ_Kr1AutonegotiationStatus_HHD */
#define word_AQ_Kr1AutonegotiationStatus_HHD_linkPartnerAutonegotiationAbility u0.word_0

/*! \brief Base register address of structure AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_baseRegisterAddress 0xC310
/*! \brief MMD address of structure AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure nextPage in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_nextPage 0
/*! \brief Preprocessor variable to relate field to bit position in structure nextPage in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_nextPage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nextPage in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_nextPage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure acknowledge in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_acknowledge 0
/*! \brief Preprocessor variable to relate field to bit position in structure acknowledge in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_acknowledge u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure acknowledge in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_acknowledge u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure remoteFault in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_remoteFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure remoteFault in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_remoteFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure remoteFault in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_remoteFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_0 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_reserved_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_0 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_reserved_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_0 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_reserved_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pauseCapability in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_pauseCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure pauseCapability in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_pauseCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pauseCapability in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_pauseCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure echoedNonce in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_echoedNonce 0
/*! \brief Preprocessor variable to relate field to bit position in structure echoedNonce in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_echoedNonce u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure echoedNonce in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_echoedNonce u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure selectorField in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_selectorField 0
/*! \brief Preprocessor variable to relate field to bit position in structure selectorField in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_selectorField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure selectorField in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_selectorField u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure technologyAbilityBitsA3ToA10 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitsA3ToA10 1
/*! \brief Preprocessor variable to relate field to bit position in structure technologyAbilityBitsA3ToA10 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitsA3ToA10 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure technologyAbilityBitsA3ToA10 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitsA3ToA10 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure technologyAbilityBitA2 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA2 1
/*! \brief Preprocessor variable to relate field to bit position in structure technologyAbilityBitA2 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure technologyAbilityBitA2 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure technologyAbilityBitA1 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA1 1
/*! \brief Preprocessor variable to relate field to bit position in structure technologyAbilityBitA1 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure technologyAbilityBitA1 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure technologyAbilityBitA0 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA0 1
/*! \brief Preprocessor variable to relate field to bit position in structure technologyAbilityBitA0 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA0 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure technologyAbilityBitA0 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitA0 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure transmittedNonce in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_transmittedNonce 1
/*! \brief Preprocessor variable to relate field to bit position in structure transmittedNonce in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_transmittedNonce u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure transmittedNonce in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_transmittedNonce u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure fecRequested in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_fecRequested 2
/*! \brief Preprocessor variable to relate field to bit position in structure fecRequested in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_fecRequested u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure fecRequested in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_fecRequested u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure fecAbility in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_fecAbility 2
/*! \brief Preprocessor variable to relate field to bit position in structure fecAbility in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_fecAbility u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure fecAbility in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_fecAbility u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure technologyAbilityBitsA11ToA24 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitsA11ToA24 2
/*! \brief Preprocessor variable to relate field to bit position in structure technologyAbilityBitsA11ToA24 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitsA11ToA24 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure technologyAbilityBitsA11ToA24 in AQ_Kr1AutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationAdvertisementWord_HHD_technologyAbilityBitsA11ToA24 u2.word_2

/*! \brief Base register address of structure AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_baseRegisterAddress 0xC313
/*! \brief MMD address of structure AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerNextPage in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerNextPage 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerNextPage in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerNextPage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerNextPage in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerNextPage u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerAcknowledge in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerAcknowledge 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerAcknowledge in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerAcknowledge u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerAcknowledge in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerAcknowledge u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerRemoteFault in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerRemoteFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerRemoteFault in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerRemoteFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerRemoteFault in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerRemoteFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_0 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_reserved_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_0 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_reserved_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_0 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_reserved_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerPauseCapability in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerPauseCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerPauseCapability in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerPauseCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerPauseCapability in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerPauseCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerEchoedNonce in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerEchoedNonce 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerEchoedNonce in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerEchoedNonce u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerEchoedNonce in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerEchoedNonce u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerSelectorField in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerSelectorField 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerSelectorField in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerSelectorField u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerSelectorField in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerSelectorField u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTechnologyAbilityBitsA3ToA10 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitsA3ToA10 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTechnologyAbilityBitsA3ToA10 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitsA3ToA10 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTechnologyAbilityBitsA3ToA10 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitsA3ToA10 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTechnologyAbilityBitA2 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA2 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTechnologyAbilityBitA2 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTechnologyAbilityBitA2 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTechnologyAbilityBitA1 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA1 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTechnologyAbilityBitA1 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTechnologyAbilityBitA1 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTechnologyAbilityBitA0 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA0 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTechnologyAbilityBitA0 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA0 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTechnologyAbilityBitA0 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitA0 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTransmittedNonce in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTransmittedNonce 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTransmittedNonce in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTransmittedNonce u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTransmittedNonce in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTransmittedNonce u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerFecRequested in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerFecRequested 2
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerFecRequested in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerFecRequested u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerFecRequested in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerFecRequested u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerFecAbility in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerFecAbility 2
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerFecAbility in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerFecAbility u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerFecAbility in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerFecAbility u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTechnologyAbilityBitsA11ToA24 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitsA11ToA24 2
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTechnologyAbilityBitsA11ToA24 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitsA11ToA24 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTechnologyAbilityBitsA11ToA24 in AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_HHD_linkPartnerTechnologyAbilityBitsA11ToA24 u2.word_2

/*! \brief Base register address of structure AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD_baseRegisterAddress 0xC316
/*! \brief MMD address of structure AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPage_0 in AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPage_0 in AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPage_0 in AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPage_1 in AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPage_1 in AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPage_1 in AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPage_2 in AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPage_2 in AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define bits_AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPage_2 in AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define word_AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_HHD_extendedNextPage_2 u2.word_2

/*! \brief Base register address of structure AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_baseRegisterAddress 0xC319
/*! \brief MMD address of structure AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerExtendedNextPage_0 in AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerExtendedNextPage_0 in AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerExtendedNextPage_0 in AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerExtendedNextPage_1 in AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerExtendedNextPage_1 in AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerExtendedNextPage_1 in AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerExtendedNextPage_2 in AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_2 2
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerExtendedNextPage_2 in AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define bits_AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_2 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerExtendedNextPage_2 in AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD */
#define word_AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_HHD_linkPartnerExtendedNextPage_2 u2.word_2

/*! \brief Base register address of structure AQ_AutonegotiationVendorProvisioning_HHD */
#define AQ_AutonegotiationVendorProvisioning_HHD_baseRegisterAddress 0xC400
/*! \brief MMD address of structure AQ_AutonegotiationVendorProvisioning_HHD */
#define AQ_AutonegotiationVendorProvisioning_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure _1000base_tFullDuplexAbility in AQ_AutonegotiationVendorProvisioning_HHD */
#define AQ_AutonegotiationVendorProvisioning_HHD__1000base_tFullDuplexAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _1000base_tFullDuplexAbility in AQ_AutonegotiationVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationVendorProvisioning_HHD__1000base_tFullDuplexAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _1000base_tFullDuplexAbility in AQ_AutonegotiationVendorProvisioning_HHD */
#define word_AQ_AutonegotiationVendorProvisioning_HHD__1000base_tFullDuplexAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _1000base_tHalfDuplexAbility in AQ_AutonegotiationVendorProvisioning_HHD */
#define AQ_AutonegotiationVendorProvisioning_HHD__1000base_tHalfDuplexAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _1000base_tHalfDuplexAbility in AQ_AutonegotiationVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationVendorProvisioning_HHD__1000base_tHalfDuplexAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _1000base_tHalfDuplexAbility in AQ_AutonegotiationVendorProvisioning_HHD */
#define word_AQ_AutonegotiationVendorProvisioning_HHD__1000base_tHalfDuplexAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure short_reach in AQ_AutonegotiationVendorProvisioning_HHD */
#define AQ_AutonegotiationVendorProvisioning_HHD_short_reach 0
/*! \brief Preprocessor variable to relate field to bit position in structure short_reach in AQ_AutonegotiationVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationVendorProvisioning_HHD_short_reach u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure short_reach in AQ_AutonegotiationVendorProvisioning_HHD */
#define word_AQ_AutonegotiationVendorProvisioning_HHD_short_reach u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure aqrateDownshiftCapability in AQ_AutonegotiationVendorProvisioning_HHD */
#define AQ_AutonegotiationVendorProvisioning_HHD_aqrateDownshiftCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure aqrateDownshiftCapability in AQ_AutonegotiationVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationVendorProvisioning_HHD_aqrateDownshiftCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure aqrateDownshiftCapability in AQ_AutonegotiationVendorProvisioning_HHD */
#define word_AQ_AutonegotiationVendorProvisioning_HHD_aqrateDownshiftCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _5g in AQ_AutonegotiationVendorProvisioning_HHD */
#define AQ_AutonegotiationVendorProvisioning_HHD__5g 0
/*! \brief Preprocessor variable to relate field to bit position in structure _5g in AQ_AutonegotiationVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationVendorProvisioning_HHD__5g u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _5g in AQ_AutonegotiationVendorProvisioning_HHD */
#define word_AQ_AutonegotiationVendorProvisioning_HHD__5g u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _2_5g in AQ_AutonegotiationVendorProvisioning_HHD */
#define AQ_AutonegotiationVendorProvisioning_HHD__2_5g 0
/*! \brief Preprocessor variable to relate field to bit position in structure _2_5g in AQ_AutonegotiationVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationVendorProvisioning_HHD__2_5g u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _2_5g in AQ_AutonegotiationVendorProvisioning_HHD */
#define word_AQ_AutonegotiationVendorProvisioning_HHD__2_5g u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved1 in AQ_AutonegotiationVendorProvisioning_HHD */
#define AQ_AutonegotiationVendorProvisioning_HHD_reserved1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved1 in AQ_AutonegotiationVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationVendorProvisioning_HHD_reserved1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved1 in AQ_AutonegotiationVendorProvisioning_HHD */
#define word_AQ_AutonegotiationVendorProvisioning_HHD_reserved1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure exchangePhyIdInformation in AQ_AutonegotiationVendorProvisioning_HHD */
#define AQ_AutonegotiationVendorProvisioning_HHD_exchangePhyIdInformation 0
/*! \brief Preprocessor variable to relate field to bit position in structure exchangePhyIdInformation in AQ_AutonegotiationVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationVendorProvisioning_HHD_exchangePhyIdInformation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure exchangePhyIdInformation in AQ_AutonegotiationVendorProvisioning_HHD */
#define word_AQ_AutonegotiationVendorProvisioning_HHD_exchangePhyIdInformation u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure userProvidedAutonegotiationData in AQ_AutonegotiationVendorProvisioning_HHD */
#define AQ_AutonegotiationVendorProvisioning_HHD_userProvidedAutonegotiationData 0
/*! \brief Preprocessor variable to relate field to bit position in structure userProvidedAutonegotiationData in AQ_AutonegotiationVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationVendorProvisioning_HHD_userProvidedAutonegotiationData u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure userProvidedAutonegotiationData in AQ_AutonegotiationVendorProvisioning_HHD */
#define word_AQ_AutonegotiationVendorProvisioning_HHD_userProvidedAutonegotiationData u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure automaticDownshiftEnable in AQ_AutonegotiationVendorProvisioning_HHD */
#define AQ_AutonegotiationVendorProvisioning_HHD_automaticDownshiftEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure automaticDownshiftEnable in AQ_AutonegotiationVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationVendorProvisioning_HHD_automaticDownshiftEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure automaticDownshiftEnable in AQ_AutonegotiationVendorProvisioning_HHD */
#define word_AQ_AutonegotiationVendorProvisioning_HHD_automaticDownshiftEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure retryAttemptsBeforeDownshift in AQ_AutonegotiationVendorProvisioning_HHD */
#define AQ_AutonegotiationVendorProvisioning_HHD_retryAttemptsBeforeDownshift 0
/*! \brief Preprocessor variable to relate field to bit position in structure retryAttemptsBeforeDownshift in AQ_AutonegotiationVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationVendorProvisioning_HHD_retryAttemptsBeforeDownshift u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure retryAttemptsBeforeDownshift in AQ_AutonegotiationVendorProvisioning_HHD */
#define word_AQ_AutonegotiationVendorProvisioning_HHD_retryAttemptsBeforeDownshift u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReservedVendorProvisioning_HHD_baseRegisterAddress 0xC410
/*! \brief MMD address of structure AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReservedVendorProvisioning_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure serdesStart_upMode in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReservedVendorProvisioning_HHD_serdesStart_upMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesStart_upMode in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_HHD_serdesStart_upMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesStart_upMode in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReservedVendorProvisioning_HHD_serdesStart_upMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedProvisioning_0 in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReservedVendorProvisioning_HHD_reservedProvisioning_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedProvisioning_0 in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_HHD_reservedProvisioning_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedProvisioning_0 in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReservedVendorProvisioning_HHD_reservedProvisioning_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure semi_crossLinkAttemptPeriod in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReservedVendorProvisioning_HHD_semi_crossLinkAttemptPeriod 0
/*! \brief Preprocessor variable to relate field to bit position in structure semi_crossLinkAttemptPeriod in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_HHD_semi_crossLinkAttemptPeriod u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure semi_crossLinkAttemptPeriod in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReservedVendorProvisioning_HHD_semi_crossLinkAttemptPeriod u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure wolMode in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReservedVendorProvisioning_HHD_wolMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure wolMode in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_HHD_wolMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure wolMode in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReservedVendorProvisioning_HHD_wolMode u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure wolEnable in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReservedVendorProvisioning_HHD_wolEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure wolEnable in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_HHD_wolEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure wolEnable in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReservedVendorProvisioning_HHD_wolEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extraPageCount in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReservedVendorProvisioning_HHD_extraPageCount 0
/*! \brief Preprocessor variable to relate field to bit position in structure extraPageCount in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_HHD_extraPageCount u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extraPageCount in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReservedVendorProvisioning_HHD_extraPageCount u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mdi_Mdi_xControl in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReservedVendorProvisioning_HHD_mdi_Mdi_xControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure mdi_Mdi_xControl in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_HHD_mdi_Mdi_xControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mdi_Mdi_xControl in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReservedVendorProvisioning_HHD_mdi_Mdi_xControl u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationTimeout in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReservedVendorProvisioning_HHD_autonegotiationTimeout 1
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationTimeout in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_HHD_autonegotiationTimeout u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationTimeout in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReservedVendorProvisioning_HHD_autonegotiationTimeout u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationTimeoutMode in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReservedVendorProvisioning_HHD_autonegotiationTimeoutMode 1
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationTimeoutMode in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReservedVendorProvisioning_HHD_autonegotiationTimeoutMode u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationTimeoutMode in AQ_AutonegotiationReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReservedVendorProvisioning_HHD_autonegotiationTimeoutMode u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationVendorStatus_HHD */
#define AQ_AutonegotiationVendorStatus_HHD_baseRegisterAddress 0xC800
/*! \brief MMD address of structure AQ_AutonegotiationVendorStatus_HHD */
#define AQ_AutonegotiationVendorStatus_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure connectRate in AQ_AutonegotiationVendorStatus_HHD */
#define AQ_AutonegotiationVendorStatus_HHD_connectRate 0
/*! \brief Preprocessor variable to relate field to bit position in structure connectRate in AQ_AutonegotiationVendorStatus_HHD */
#define bits_AQ_AutonegotiationVendorStatus_HHD_connectRate u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure connectRate in AQ_AutonegotiationVendorStatus_HHD */
#define word_AQ_AutonegotiationVendorStatus_HHD_connectRate u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure connectType in AQ_AutonegotiationVendorStatus_HHD */
#define AQ_AutonegotiationVendorStatus_HHD_connectType 0
/*! \brief Preprocessor variable to relate field to bit position in structure connectType in AQ_AutonegotiationVendorStatus_HHD */
#define bits_AQ_AutonegotiationVendorStatus_HHD_connectType u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure connectType in AQ_AutonegotiationVendorStatus_HHD */
#define word_AQ_AutonegotiationVendorStatus_HHD_connectType u0.word_0

/*! \brief Base register address of structure AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_baseRegisterAddress 0xC810
/*! \brief MMD address of structure AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure energyOnLine in AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_energyOnLine 0
/*! \brief Preprocessor variable to relate field to bit position in structure energyOnLine in AQ_AutonegotiationReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReservedVendorStatus_HHD_energyOnLine u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure energyOnLine in AQ_AutonegotiationReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReservedVendorStatus_HHD_energyOnLine u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure devicePresent in AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_devicePresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure devicePresent in AQ_AutonegotiationReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReservedVendorStatus_HHD_devicePresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure devicePresent in AQ_AutonegotiationReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReservedVendorStatus_HHD_devicePresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure connectionState in AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_connectionState 0
/*! \brief Preprocessor variable to relate field to bit position in structure connectionState in AQ_AutonegotiationReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReservedVendorStatus_HHD_connectionState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure connectionState in AQ_AutonegotiationReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReservedVendorStatus_HHD_connectionState u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mdi_mdi_x in AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_mdi_mdi_x 0
/*! \brief Preprocessor variable to relate field to bit position in structure mdi_mdi_x in AQ_AutonegotiationReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReservedVendorStatus_HHD_mdi_mdi_x u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mdi_mdi_x in AQ_AutonegotiationReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReservedVendorStatus_HHD_mdi_mdi_x u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure duplicateLinkPartnerAutonegotiationAbility in AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_duplicateLinkPartnerAutonegotiationAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure duplicateLinkPartnerAutonegotiationAbility in AQ_AutonegotiationReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReservedVendorStatus_HHD_duplicateLinkPartnerAutonegotiationAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure duplicateLinkPartnerAutonegotiationAbility in AQ_AutonegotiationReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReservedVendorStatus_HHD_duplicateLinkPartnerAutonegotiationAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedStatus_1 in AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_reservedStatus_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedStatus_1 in AQ_AutonegotiationReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReservedVendorStatus_HHD_reservedStatus_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedStatus_1 in AQ_AutonegotiationReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReservedVendorStatus_HHD_reservedStatus_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure receivePauseResolution in AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_receivePauseResolution 0
/*! \brief Preprocessor variable to relate field to bit position in structure receivePauseResolution in AQ_AutonegotiationReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReservedVendorStatus_HHD_receivePauseResolution u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure receivePauseResolution in AQ_AutonegotiationReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReservedVendorStatus_HHD_receivePauseResolution u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitPauseResolution in AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_transmitPauseResolution 0
/*! \brief Preprocessor variable to relate field to bit position in structure transmitPauseResolution in AQ_AutonegotiationReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReservedVendorStatus_HHD_transmitPauseResolution u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure transmitPauseResolution in AQ_AutonegotiationReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReservedVendorStatus_HHD_transmitPauseResolution u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationAttempts in AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_autonegotiationAttempts 1
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationAttempts in AQ_AutonegotiationReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReservedVendorStatus_HHD_autonegotiationAttempts u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationAttempts in AQ_AutonegotiationReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReservedVendorStatus_HHD_autonegotiationAttempts u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkPulseDetectedStatus in AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_linkPulseDetectedStatus 2
/*! \brief Preprocessor variable to relate field to bit position in structure linkPulseDetectedStatus in AQ_AutonegotiationReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReservedVendorStatus_HHD_linkPulseDetectedStatus u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure linkPulseDetectedStatus in AQ_AutonegotiationReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReservedVendorStatus_HHD_linkPulseDetectedStatus u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedState_3 in AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_reservedState_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedState_3 in AQ_AutonegotiationReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReservedVendorStatus_HHD_reservedState_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedState_3 in AQ_AutonegotiationReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReservedVendorStatus_HHD_reservedState_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationRestartsHandled in AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_autonegotiationRestartsHandled 3
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationRestartsHandled in AQ_AutonegotiationReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReservedVendorStatus_HHD_autonegotiationRestartsHandled u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationRestartsHandled in AQ_AutonegotiationReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReservedVendorStatus_HHD_autonegotiationRestartsHandled u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationAttemptsSinceReset in AQ_AutonegotiationReservedVendorStatus_HHD */
#define AQ_AutonegotiationReservedVendorStatus_HHD_autonegotiationAttemptsSinceReset 4
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationAttemptsSinceReset in AQ_AutonegotiationReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReservedVendorStatus_HHD_autonegotiationAttemptsSinceReset u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationAttemptsSinceReset in AQ_AutonegotiationReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReservedVendorStatus_HHD_autonegotiationAttemptsSinceReset u4.word_4

/*! \brief Base register address of structure AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define AQ_AutonegotiationTransmitVendorAlarms_HHD_baseRegisterAddress 0xCC00
/*! \brief MMD address of structure AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define AQ_AutonegotiationTransmitVendorAlarms_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationCompletedForNon_supportedRate in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define AQ_AutonegotiationTransmitVendorAlarms_HHD_autonegotiationCompletedForNon_supportedRate 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationCompletedForNon_supportedRate in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_HHD_autonegotiationCompletedForNon_supportedRate u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationCompletedForNon_supportedRate in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define word_AQ_AutonegotiationTransmitVendorAlarms_HHD_autonegotiationCompletedForNon_supportedRate u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationCompletedForSupportedRate in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define AQ_AutonegotiationTransmitVendorAlarms_HHD_autonegotiationCompletedForSupportedRate 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationCompletedForSupportedRate in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_HHD_autonegotiationCompletedForSupportedRate u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationCompletedForSupportedRate in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define word_AQ_AutonegotiationTransmitVendorAlarms_HHD_autonegotiationCompletedForSupportedRate u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure automaticDownshift in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define AQ_AutonegotiationTransmitVendorAlarms_HHD_automaticDownshift 0
/*! \brief Preprocessor variable to relate field to bit position in structure automaticDownshift in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_HHD_automaticDownshift u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure automaticDownshift in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define word_AQ_AutonegotiationTransmitVendorAlarms_HHD_automaticDownshift u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure connectionStateChange in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define AQ_AutonegotiationTransmitVendorAlarms_HHD_connectionStateChange 0
/*! \brief Preprocessor variable to relate field to bit position in structure connectionStateChange in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_HHD_connectionStateChange u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure connectionStateChange in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define word_AQ_AutonegotiationTransmitVendorAlarms_HHD_connectionStateChange u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPulseDetect in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define AQ_AutonegotiationTransmitVendorAlarms_HHD_linkPulseDetect 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPulseDetect in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_HHD_linkPulseDetect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPulseDetect in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define word_AQ_AutonegotiationTransmitVendorAlarms_HHD_linkPulseDetect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedVendorAlarms_2 in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define AQ_AutonegotiationTransmitVendorAlarms_HHD_reservedVendorAlarms_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedVendorAlarms_2 in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_HHD_reservedVendorAlarms_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedVendorAlarms_2 in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define word_AQ_AutonegotiationTransmitVendorAlarms_HHD_reservedVendorAlarms_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkConnect_Disconnect in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define AQ_AutonegotiationTransmitVendorAlarms_HHD_linkConnect_Disconnect 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkConnect_Disconnect in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define bits_AQ_AutonegotiationTransmitVendorAlarms_HHD_linkConnect_Disconnect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkConnect_Disconnect in AQ_AutonegotiationTransmitVendorAlarms_HHD */
#define word_AQ_AutonegotiationTransmitVendorAlarms_HHD_linkConnect_Disconnect u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationStandardInterruptMask_HHD */
#define AQ_AutonegotiationStandardInterruptMask_HHD_baseRegisterAddress 0xD000
/*! \brief MMD address of structure AQ_AutonegotiationStandardInterruptMask_HHD */
#define AQ_AutonegotiationStandardInterruptMask_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure parallelDetectionFaultMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define AQ_AutonegotiationStandardInterruptMask_HHD_parallelDetectionFaultMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure parallelDetectionFaultMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define bits_AQ_AutonegotiationStandardInterruptMask_HHD_parallelDetectionFaultMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure parallelDetectionFaultMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define word_AQ_AutonegotiationStandardInterruptMask_HHD_parallelDetectionFaultMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extendedNextPageReceivedMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define AQ_AutonegotiationStandardInterruptMask_HHD_extendedNextPageReceivedMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedNextPageReceivedMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define bits_AQ_AutonegotiationStandardInterruptMask_HHD_extendedNextPageReceivedMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedNextPageReceivedMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define word_AQ_AutonegotiationStandardInterruptMask_HHD_extendedNextPageReceivedMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure remoteFaultMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define AQ_AutonegotiationStandardInterruptMask_HHD_remoteFaultMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure remoteFaultMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define bits_AQ_AutonegotiationStandardInterruptMask_HHD_remoteFaultMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure remoteFaultMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define word_AQ_AutonegotiationStandardInterruptMask_HHD_remoteFaultMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkStatusMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define AQ_AutonegotiationStandardInterruptMask_HHD_linkStatusMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkStatusMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define bits_AQ_AutonegotiationStandardInterruptMask_HHD_linkStatusMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkStatusMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define word_AQ_AutonegotiationStandardInterruptMask_HHD_linkStatusMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure master_slaveConfigurationFaultMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define AQ_AutonegotiationStandardInterruptMask_HHD_master_slaveConfigurationFaultMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure master_slaveConfigurationFaultMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define bits_AQ_AutonegotiationStandardInterruptMask_HHD_master_slaveConfigurationFaultMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure master_slaveConfigurationFaultMask in AQ_AutonegotiationStandardInterruptMask_HHD */
#define word_AQ_AutonegotiationStandardInterruptMask_HHD_master_slaveConfigurationFaultMask u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define AQ_AutonegotiationTransmitVendorInterruptMask_HHD_baseRegisterAddress 0xD400
/*! \brief MMD address of structure AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define AQ_AutonegotiationTransmitVendorInterruptMask_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationCompletedForNon_supportedRateMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define AQ_AutonegotiationTransmitVendorInterruptMask_HHD_autonegotiationCompletedForNon_supportedRateMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationCompletedForNon_supportedRateMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_autonegotiationCompletedForNon_supportedRateMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationCompletedForNon_supportedRateMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_autonegotiationCompletedForNon_supportedRateMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationCompletedForSupportedRateMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define AQ_AutonegotiationTransmitVendorInterruptMask_HHD_autonegotiationCompletedForSupportedRateMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationCompletedForSupportedRateMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_autonegotiationCompletedForSupportedRateMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationCompletedForSupportedRateMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_autonegotiationCompletedForSupportedRateMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure automaticDownshiftMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define AQ_AutonegotiationTransmitVendorInterruptMask_HHD_automaticDownshiftMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure automaticDownshiftMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_automaticDownshiftMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure automaticDownshiftMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_automaticDownshiftMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure connectionStateChangeMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define AQ_AutonegotiationTransmitVendorInterruptMask_HHD_connectionStateChangeMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure connectionStateChangeMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_connectionStateChangeMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure connectionStateChangeMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_connectionStateChangeMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPulseDetectMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define AQ_AutonegotiationTransmitVendorInterruptMask_HHD_linkPulseDetectMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkPulseDetectMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_linkPulseDetectMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkPulseDetectMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_linkPulseDetectMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedVendorAlarms_2Mask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define AQ_AutonegotiationTransmitVendorInterruptMask_HHD_reservedVendorAlarms_2Mask 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedVendorAlarms_2Mask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_reservedVendorAlarms_2Mask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedVendorAlarms_2Mask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_reservedVendorAlarms_2Mask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure linkConnect_DisconnectMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define AQ_AutonegotiationTransmitVendorInterruptMask_HHD_linkConnect_DisconnectMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure linkConnect_DisconnectMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_linkConnect_DisconnectMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure linkConnect_DisconnectMask in AQ_AutonegotiationTransmitVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationTransmitVendorInterruptMask_HHD_linkConnect_DisconnectMask u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_baseRegisterAddress 0xE410
/*! \brief MMD address of structure AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveProvisioning_1 in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_reservedReceiveProvisioning_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveProvisioning_1 in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_reservedReceiveProvisioning_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveProvisioning_1 in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_reservedReceiveProvisioning_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _2_5gbase_tTHP_BypassRequest in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__2_5gbase_tTHP_BypassRequest 0
/*! \brief Preprocessor variable to relate field to bit position in structure _2_5gbase_tTHP_BypassRequest in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__2_5gbase_tTHP_BypassRequest u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _2_5gbase_tTHP_BypassRequest in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__2_5gbase_tTHP_BypassRequest u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _5gbase_tTHP_BypassRequest in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__5gbase_tTHP_BypassRequest 0
/*! \brief Preprocessor variable to relate field to bit position in structure _5gbase_tTHP_BypassRequest in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__5gbase_tTHP_BypassRequest u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _5gbase_tTHP_BypassRequest in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__5gbase_tTHP_BypassRequest u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _5gbase_tFastRetrainAbility in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__5gbase_tFastRetrainAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _5gbase_tFastRetrainAbility in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__5gbase_tFastRetrainAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _5gbase_tFastRetrainAbility in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__5gbase_tFastRetrainAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _2_5gbase_tFastRetrainAbility in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__2_5gbase_tFastRetrainAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _2_5gbase_tFastRetrainAbility in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__2_5gbase_tFastRetrainAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _2_5gbase_tFastRetrainAbility in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__2_5gbase_tFastRetrainAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _5gbase_tEee in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__5gbase_tEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _5gbase_tEee in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__5gbase_tEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _5gbase_tEee in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__5gbase_tEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _2_5gbase_tEee in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__2_5gbase_tEee 0
/*! \brief Preprocessor variable to relate field to bit position in structure _2_5gbase_tEee in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__2_5gbase_tEee u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _2_5gbase_tEee in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__2_5gbase_tEee u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _5gbase_tAbility in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__5gbase_tAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _5gbase_tAbility in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__5gbase_tAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _5gbase_tAbility in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__5gbase_tAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _2_5gbase_tAbility in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__2_5gbase_tAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure _2_5gbase_tAbility in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__2_5gbase_tAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _2_5gbase_tAbility in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD__2_5gbase_tAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure disable_100base_txParallelDetection in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_disable_100base_txParallelDetection 0
/*! \brief Preprocessor variable to relate field to bit position in structure disable_100base_txParallelDetection in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_disable_100base_txParallelDetection u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure disable_100base_txParallelDetection in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_disable_100base_txParallelDetection u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveProvisioning_2 in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_reservedReceiveProvisioning_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveProvisioning_2 in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_reservedReceiveProvisioning_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveProvisioning_2 in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_reservedReceiveProvisioning_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure downshiftFrom10G in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_downshiftFrom10G 1
/*! \brief Preprocessor variable to relate field to bit position in structure downshiftFrom10G in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_downshiftFrom10G u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure downshiftFrom10G in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_downshiftFrom10G u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure downshiftFrom_5g in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_downshiftFrom_5g 1
/*! \brief Preprocessor variable to relate field to bit position in structure downshiftFrom_5g in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_downshiftFrom_5g u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure downshiftFrom_5g in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_downshiftFrom_5g u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure downshiftFrom_2_5g in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_downshiftFrom_2_5g 1
/*! \brief Preprocessor variable to relate field to bit position in structure downshiftFrom_2_5g in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_downshiftFrom_2_5g u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure downshiftFrom_2_5g in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_downshiftFrom_2_5g u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure downshiftFrom1G in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_downshiftFrom1G 1
/*! \brief Preprocessor variable to relate field to bit position in structure downshiftFrom1G in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_downshiftFrom1G u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure downshiftFrom1G in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_downshiftFrom1G u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure maxAdvertisedRate in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_maxAdvertisedRate 1
/*! \brief Preprocessor variable to relate field to bit position in structure maxAdvertisedRate in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_maxAdvertisedRate u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure maxAdvertisedRate in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_maxAdvertisedRate u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure maxRateTrainingCnt in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_maxRateTrainingCnt 1
/*! \brief Preprocessor variable to relate field to bit position in structure maxRateTrainingCnt in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_maxRateTrainingCnt u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure maxRateTrainingCnt in AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorProvisioning_HHD_maxRateTrainingCnt u1.word_1

/*! \brief Base register address of structure AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_baseRegisterAddress 0xE820
/*! \brief MMD address of structure AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner1000BaseT_FullDuplexAbility in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartner1000BaseT_FullDuplexAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner1000BaseT_FullDuplexAbility in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartner1000BaseT_FullDuplexAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner1000BaseT_FullDuplexAbility in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartner1000BaseT_FullDuplexAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner1000BaseT_HalfDuplexAbility in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartner1000BaseT_HalfDuplexAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner1000BaseT_HalfDuplexAbility in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartner1000BaseT_HalfDuplexAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner1000BaseT_HalfDuplexAbility in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartner1000BaseT_HalfDuplexAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerShort_reach in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartnerShort_reach 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerShort_reach in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartnerShort_reach u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerShort_reach in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartnerShort_reach u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerAqrateDownshiftCapability in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartnerAqrateDownshiftCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerAqrateDownshiftCapability in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartnerAqrateDownshiftCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerAqrateDownshiftCapability in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartnerAqrateDownshiftCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner_5g in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartner_5g 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner_5g in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartner_5g u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner_5g in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartner_5g u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner_2_5g in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartner_2_5g 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner_2_5g in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartner_2_5g u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner_2_5g in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartner_2_5g u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved2 in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_reserved2 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved2 in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_reserved2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved2 in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_reserved2 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure aquantiaLinkPartner in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_aquantiaLinkPartner 0
/*! \brief Preprocessor variable to relate field to bit position in structure aquantiaLinkPartner in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_aquantiaLinkPartner u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure aquantiaLinkPartner in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_aquantiaLinkPartner u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerFirmwareMajorRevisionNumber in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartnerFirmwareMajorRevisionNumber 3
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerFirmwareMajorRevisionNumber in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartnerFirmwareMajorRevisionNumber u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerFirmwareMajorRevisionNumber in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartnerFirmwareMajorRevisionNumber u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerFirmwareMinorRevisionNumber in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartnerFirmwareMinorRevisionNumber 3
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerFirmwareMinorRevisionNumber in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define bits_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartnerFirmwareMinorRevisionNumber u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerFirmwareMinorRevisionNumber in AQ_AutonegotiationReceiveLinkPartnerStatus_HHD */
#define word_AQ_AutonegotiationReceiveLinkPartnerStatus_HHD_linkPartnerFirmwareMinorRevisionNumber u3.word_3

/*! \brief Base register address of structure AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_baseRegisterAddress 0xE830
/*! \brief MMD address of structure AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure linkAttempts in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkAttempts 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkAttempts in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkAttempts u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkAttempts in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkAttempts u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerPhyTag in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartnerPhyTag 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerPhyTag in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartnerPhyTag u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerPhyTag in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartnerPhyTag u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveStatus_1 in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveStatus_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveStatus_1 in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveStatus_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveStatus_1 in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveStatus_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationProtocolErrorState in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_autonegotiationProtocolErrorState 1
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationProtocolErrorState in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_autonegotiationProtocolErrorState u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationProtocolErrorState in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_autonegotiationProtocolErrorState u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure flpIdleErrorState in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_flpIdleErrorState 1
/*! \brief Preprocessor variable to relate field to bit position in structure flpIdleErrorState in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_flpIdleErrorState u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure flpIdleErrorState in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_flpIdleErrorState u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveState_2 in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveState_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveState_2 in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveState_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveState_2 in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveState_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveState_3 in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveState_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveState_3 in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveState_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveState_3 in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveState_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure multigigModeSelected in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_multigigModeSelected 2
/*! \brief Preprocessor variable to relate field to bit position in structure multigigModeSelected in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_multigigModeSelected u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure multigigModeSelected in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_multigigModeSelected u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerAfrEnabled in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartnerAfrEnabled 2
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerAfrEnabled in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartnerAfrEnabled u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerAfrEnabled in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartnerAfrEnabled u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveState_4 in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveState_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveState_4 in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveState_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveState_4 in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveState_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner_2_5gbase_tTHP_BypassRequest in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_2_5gbase_tTHP_BypassRequest 3
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner_2_5gbase_tTHP_BypassRequest in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_2_5gbase_tTHP_BypassRequest u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner_2_5gbase_tTHP_BypassRequest in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_2_5gbase_tTHP_BypassRequest u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner_5gbase_tTHP_BypassRequest in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_5gbase_tTHP_BypassRequest 3
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner_5gbase_tTHP_BypassRequest in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_5gbase_tTHP_BypassRequest u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner_5gbase_tTHP_BypassRequest in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_5gbase_tTHP_BypassRequest u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner_5gbase_tFastRetrainAbility in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_5gbase_tFastRetrainAbility 3
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner_5gbase_tFastRetrainAbility in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_5gbase_tFastRetrainAbility u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner_5gbase_tFastRetrainAbility in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_5gbase_tFastRetrainAbility u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner_2_5gbase_tFastRetrainAbility in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_2_5gbase_tFastRetrainAbility 3
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner_2_5gbase_tFastRetrainAbility in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_2_5gbase_tFastRetrainAbility u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner_2_5gbase_tFastRetrainAbility in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_2_5gbase_tFastRetrainAbility u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner_5gbase_tEee in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_5gbase_tEee 3
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner_5gbase_tEee in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_5gbase_tEee u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner_5gbase_tEee in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_5gbase_tEee u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner_2_5gbase_tEee in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_2_5gbase_tEee 3
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner_2_5gbase_tEee in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_2_5gbase_tEee u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner_2_5gbase_tEee in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_2_5gbase_tEee u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner_5gbase_tAbility in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_5gbase_tAbility 3
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner_5gbase_tAbility in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_5gbase_tAbility u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner_5gbase_tAbility in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_5gbase_tAbility u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure linkPartner_2_5gbase_tAbility in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_2_5gbase_tAbility 3
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartner_2_5gbase_tAbility in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_2_5gbase_tAbility u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure linkPartner_2_5gbase_tAbility in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_linkPartner_2_5gbase_tAbility u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveState_4a in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveState_4a 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveState_4a in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define bits_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveState_4a u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveState_4a in AQ_AutonegotiationReceiveReservedVendorStatus_HHD */
#define word_AQ_AutonegotiationReceiveReservedVendorStatus_HHD_reservedReceiveState_4a u3.word_3

/*! \brief Base register address of structure AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define AQ_AutonegotiationReceiveVendorAlarms_HHD_baseRegisterAddress 0xEC00
/*! \brief MMD address of structure AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define AQ_AutonegotiationReceiveVendorAlarms_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationProtocolError in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define AQ_AutonegotiationReceiveVendorAlarms_HHD_autonegotiationProtocolError 1
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationProtocolError in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define bits_AQ_AutonegotiationReceiveVendorAlarms_HHD_autonegotiationProtocolError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationProtocolError in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define word_AQ_AutonegotiationReceiveVendorAlarms_HHD_autonegotiationProtocolError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure flpIdleError in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define AQ_AutonegotiationReceiveVendorAlarms_HHD_flpIdleError 1
/*! \brief Preprocessor variable to relate field to bit position in structure flpIdleError in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define bits_AQ_AutonegotiationReceiveVendorAlarms_HHD_flpIdleError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure flpIdleError in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define word_AQ_AutonegotiationReceiveVendorAlarms_HHD_flpIdleError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveVendorAlarms_2 in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define AQ_AutonegotiationReceiveVendorAlarms_HHD_reservedReceiveVendorAlarms_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveVendorAlarms_2 in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define bits_AQ_AutonegotiationReceiveVendorAlarms_HHD_reservedReceiveVendorAlarms_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveVendorAlarms_2 in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define word_AQ_AutonegotiationReceiveVendorAlarms_HHD_reservedReceiveVendorAlarms_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure _10base_tDeviceDetect in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define AQ_AutonegotiationReceiveVendorAlarms_HHD__10base_tDeviceDetect 2
/*! \brief Preprocessor variable to relate field to bit position in structure _10base_tDeviceDetect in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define bits_AQ_AutonegotiationReceiveVendorAlarms_HHD__10base_tDeviceDetect u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure _10base_tDeviceDetect in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define word_AQ_AutonegotiationReceiveVendorAlarms_HHD__10base_tDeviceDetect u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveVendorAlarms_4 in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define AQ_AutonegotiationReceiveVendorAlarms_HHD_reservedReceiveVendorAlarms_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveVendorAlarms_4 in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define bits_AQ_AutonegotiationReceiveVendorAlarms_HHD_reservedReceiveVendorAlarms_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveVendorAlarms_4 in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define word_AQ_AutonegotiationReceiveVendorAlarms_HHD_reservedReceiveVendorAlarms_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure _100base_txParallelDetect in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define AQ_AutonegotiationReceiveVendorAlarms_HHD__100base_txParallelDetect 3
/*! \brief Preprocessor variable to relate field to bit position in structure _100base_txParallelDetect in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define bits_AQ_AutonegotiationReceiveVendorAlarms_HHD__100base_txParallelDetect u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure _100base_txParallelDetect in AQ_AutonegotiationReceiveVendorAlarms_HHD */
#define word_AQ_AutonegotiationReceiveVendorAlarms_HHD__100base_txParallelDetect u3.word_3

/*! \brief Base register address of structure AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define AQ_AutonegotiationReceiveVendorInterruptMask_HHD_baseRegisterAddress 0xF400
/*! \brief MMD address of structure AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define AQ_AutonegotiationReceiveVendorInterruptMask_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveVendorAlarms_1Mask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define AQ_AutonegotiationReceiveVendorInterruptMask_HHD_reservedReceiveVendorAlarms_1Mask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveVendorAlarms_1Mask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_HHD_reservedReceiveVendorAlarms_1Mask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveVendorAlarms_1Mask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_HHD_reservedReceiveVendorAlarms_1Mask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationProtocolErrorMask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define AQ_AutonegotiationReceiveVendorInterruptMask_HHD_autonegotiationProtocolErrorMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationProtocolErrorMask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_HHD_autonegotiationProtocolErrorMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationProtocolErrorMask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_HHD_autonegotiationProtocolErrorMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure flpIdleErrorMask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define AQ_AutonegotiationReceiveVendorInterruptMask_HHD_flpIdleErrorMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure flpIdleErrorMask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_HHD_flpIdleErrorMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure flpIdleErrorMask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_HHD_flpIdleErrorMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveVendorAlarms_2Mask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define AQ_AutonegotiationReceiveVendorInterruptMask_HHD_reservedReceiveVendorAlarms_2Mask 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveVendorAlarms_2Mask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_HHD_reservedReceiveVendorAlarms_2Mask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveVendorAlarms_2Mask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_HHD_reservedReceiveVendorAlarms_2Mask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure _10base_tDeviceDetectMask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define AQ_AutonegotiationReceiveVendorInterruptMask_HHD__10base_tDeviceDetectMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure _10base_tDeviceDetectMask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_HHD__10base_tDeviceDetectMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure _10base_tDeviceDetectMask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_HHD__10base_tDeviceDetectMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveVendorAlarms_4Mask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define AQ_AutonegotiationReceiveVendorInterruptMask_HHD_reservedReceiveVendorAlarms_4Mask 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveVendorAlarms_4Mask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_HHD_reservedReceiveVendorAlarms_4Mask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveVendorAlarms_4Mask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_HHD_reservedReceiveVendorAlarms_4Mask u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure _100base_txParallelDetectMask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define AQ_AutonegotiationReceiveVendorInterruptMask_HHD__100base_txParallelDetectMask 3
/*! \brief Preprocessor variable to relate field to bit position in structure _100base_txParallelDetectMask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define bits_AQ_AutonegotiationReceiveVendorInterruptMask_HHD__100base_txParallelDetectMask u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure _100base_txParallelDetectMask in AQ_AutonegotiationReceiveVendorInterruptMask_HHD */
#define word_AQ_AutonegotiationReceiveVendorInterruptMask_HHD__100base_txParallelDetectMask u3.word_3

/*! \brief Base register address of structure AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_baseRegisterAddress 0xFC00
/*! \brief MMD address of structure AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_mmdAddress 0x07
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_standardAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_standardAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_standardAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_standardAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_standardAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_standardAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_1Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_2Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_3Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_3Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_3Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_4Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_4Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_4Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define bits_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_4Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_4Interrupt in AQ_AutonegotiationVendorGlobalInterruptFlags_HHD */
#define word_AQ_AutonegotiationVendorGlobalInterruptFlags_HHD_vendorSpecificRxAlarms_4Interrupt u0.word_0
#endif
/*@}*/
/*@}*/
