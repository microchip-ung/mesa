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
*   for the PHY_XS Registers block.
*/

/*! \defgroup PHY_XS_registers_Defines PHY_XS Registers Defines
*   This module contains the compiler assist macros and doxygen comments
*   for the PHY_XS Registers block.
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
*   This file contains the compiler assist macros for the registers contained in the PHY_XS Registers block.
*
*
***********************************************************************/


/*@{*/
#ifndef AQ_APPIA_PHY_XS_REGS_DEFINES_HEADER
#define AQ_APPIA_PHY_XS_REGS_DEFINES_HEADER


/*-----------------------------------------------------------------------------*/
/*Access macro definitions                                                     */
/*-----------------------------------------------------------------------------*/
/*! \brief Base register address of structure AQ_PhyXS_StandardControl_1_APPIA */
#define AQ_PhyXS_StandardControl_1_APPIA_baseRegisterAddress 0x0000
/*! \brief MMD address of structure AQ_PhyXS_StandardControl_1_APPIA */
#define AQ_PhyXS_StandardControl_1_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure reset in AQ_PhyXS_StandardControl_1_APPIA */
#define AQ_PhyXS_StandardControl_1_APPIA_reset 0
/*! \brief Preprocessor variable to relate field to bit position in structure reset in AQ_PhyXS_StandardControl_1_APPIA */
#define bits_AQ_PhyXS_StandardControl_1_APPIA_reset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reset in AQ_PhyXS_StandardControl_1_APPIA */
#define word_AQ_PhyXS_StandardControl_1_APPIA_reset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure loopback in AQ_PhyXS_StandardControl_1_APPIA */
#define AQ_PhyXS_StandardControl_1_APPIA_loopback 0
/*! \brief Preprocessor variable to relate field to bit position in structure loopback in AQ_PhyXS_StandardControl_1_APPIA */
#define bits_AQ_PhyXS_StandardControl_1_APPIA_loopback u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure loopback in AQ_PhyXS_StandardControl_1_APPIA */
#define word_AQ_PhyXS_StandardControl_1_APPIA_loopback u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure speedSelection_0 in AQ_PhyXS_StandardControl_1_APPIA */
#define AQ_PhyXS_StandardControl_1_APPIA_speedSelection_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure speedSelection_0 in AQ_PhyXS_StandardControl_1_APPIA */
#define bits_AQ_PhyXS_StandardControl_1_APPIA_speedSelection_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure speedSelection_0 in AQ_PhyXS_StandardControl_1_APPIA */
#define word_AQ_PhyXS_StandardControl_1_APPIA_speedSelection_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowPower in AQ_PhyXS_StandardControl_1_APPIA */
#define AQ_PhyXS_StandardControl_1_APPIA_lowPower 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowPower in AQ_PhyXS_StandardControl_1_APPIA */
#define bits_AQ_PhyXS_StandardControl_1_APPIA_lowPower u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowPower in AQ_PhyXS_StandardControl_1_APPIA */
#define word_AQ_PhyXS_StandardControl_1_APPIA_lowPower u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure speedSelection_1 in AQ_PhyXS_StandardControl_1_APPIA */
#define AQ_PhyXS_StandardControl_1_APPIA_speedSelection_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure speedSelection_1 in AQ_PhyXS_StandardControl_1_APPIA */
#define bits_AQ_PhyXS_StandardControl_1_APPIA_speedSelection_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure speedSelection_1 in AQ_PhyXS_StandardControl_1_APPIA */
#define word_AQ_PhyXS_StandardControl_1_APPIA_speedSelection_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure speedSelection_2 in AQ_PhyXS_StandardControl_1_APPIA */
#define AQ_PhyXS_StandardControl_1_APPIA_speedSelection_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure speedSelection_2 in AQ_PhyXS_StandardControl_1_APPIA */
#define bits_AQ_PhyXS_StandardControl_1_APPIA_speedSelection_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure speedSelection_2 in AQ_PhyXS_StandardControl_1_APPIA */
#define word_AQ_PhyXS_StandardControl_1_APPIA_speedSelection_2 u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_StandardStatus_1_APPIA */
#define AQ_PhyXS_StandardStatus_1_APPIA_baseRegisterAddress 0x0001
/*! \brief MMD address of structure AQ_PhyXS_StandardStatus_1_APPIA */
#define AQ_PhyXS_StandardStatus_1_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure fault in AQ_PhyXS_StandardStatus_1_APPIA */
#define AQ_PhyXS_StandardStatus_1_APPIA_fault 0
/*! \brief Preprocessor variable to relate field to bit position in structure fault in AQ_PhyXS_StandardStatus_1_APPIA */
#define bits_AQ_PhyXS_StandardStatus_1_APPIA_fault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure fault in AQ_PhyXS_StandardStatus_1_APPIA */
#define word_AQ_PhyXS_StandardStatus_1_APPIA_fault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_TransmitLinkAlignmentStatus in AQ_PhyXS_StandardStatus_1_APPIA */
#define AQ_PhyXS_StandardStatus_1_APPIA_phyXS_TransmitLinkAlignmentStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_TransmitLinkAlignmentStatus in AQ_PhyXS_StandardStatus_1_APPIA */
#define bits_AQ_PhyXS_StandardStatus_1_APPIA_phyXS_TransmitLinkAlignmentStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_TransmitLinkAlignmentStatus in AQ_PhyXS_StandardStatus_1_APPIA */
#define word_AQ_PhyXS_StandardStatus_1_APPIA_phyXS_TransmitLinkAlignmentStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowPowerAbility in AQ_PhyXS_StandardStatus_1_APPIA */
#define AQ_PhyXS_StandardStatus_1_APPIA_lowPowerAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowPowerAbility in AQ_PhyXS_StandardStatus_1_APPIA */
#define bits_AQ_PhyXS_StandardStatus_1_APPIA_lowPowerAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowPowerAbility in AQ_PhyXS_StandardStatus_1_APPIA */
#define word_AQ_PhyXS_StandardStatus_1_APPIA_lowPowerAbility u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_StandardDeviceIdentifier_APPIA */
#define AQ_PhyXS_StandardDeviceIdentifier_APPIA_baseRegisterAddress 0x0002
/*! \brief MMD address of structure AQ_PhyXS_StandardDeviceIdentifier_APPIA */
#define AQ_PhyXS_StandardDeviceIdentifier_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdMSW in AQ_PhyXS_StandardDeviceIdentifier_APPIA */
#define AQ_PhyXS_StandardDeviceIdentifier_APPIA_deviceIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdMSW in AQ_PhyXS_StandardDeviceIdentifier_APPIA */
#define bits_AQ_PhyXS_StandardDeviceIdentifier_APPIA_deviceIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdMSW in AQ_PhyXS_StandardDeviceIdentifier_APPIA */
#define word_AQ_PhyXS_StandardDeviceIdentifier_APPIA_deviceIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdLSW in AQ_PhyXS_StandardDeviceIdentifier_APPIA */
#define AQ_PhyXS_StandardDeviceIdentifier_APPIA_deviceIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdLSW in AQ_PhyXS_StandardDeviceIdentifier_APPIA */
#define bits_AQ_PhyXS_StandardDeviceIdentifier_APPIA_deviceIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdLSW in AQ_PhyXS_StandardDeviceIdentifier_APPIA */
#define word_AQ_PhyXS_StandardDeviceIdentifier_APPIA_deviceIdLSW u1.word_1

/*! \brief Base register address of structure AQ_PhyXS_StandardSpeedAbility_APPIA */
#define AQ_PhyXS_StandardSpeedAbility_APPIA_baseRegisterAddress 0x0004
/*! \brief MMD address of structure AQ_PhyXS_StandardSpeedAbility_APPIA */
#define AQ_PhyXS_StandardSpeedAbility_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure _10gCapable in AQ_PhyXS_StandardSpeedAbility_APPIA */
#define AQ_PhyXS_StandardSpeedAbility_APPIA__10gCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gCapable in AQ_PhyXS_StandardSpeedAbility_APPIA */
#define bits_AQ_PhyXS_StandardSpeedAbility_APPIA__10gCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gCapable in AQ_PhyXS_StandardSpeedAbility_APPIA */
#define word_AQ_PhyXS_StandardSpeedAbility_APPIA__10gCapable u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define AQ_PhyXS_StandardDevicesInPackage_APPIA_baseRegisterAddress 0x0005
/*! \brief MMD address of structure AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define AQ_PhyXS_StandardDevicesInPackage_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define AQ_PhyXS_StandardDevicesInPackage_APPIA_autonegotiationPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define bits_AQ_PhyXS_StandardDevicesInPackage_APPIA_autonegotiationPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define word_AQ_PhyXS_StandardDevicesInPackage_APPIA_autonegotiationPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tcPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define AQ_PhyXS_StandardDevicesInPackage_APPIA_tcPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure tcPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define bits_AQ_PhyXS_StandardDevicesInPackage_APPIA_tcPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tcPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define word_AQ_PhyXS_StandardDevicesInPackage_APPIA_tcPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure dteXsPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define AQ_PhyXS_StandardDevicesInPackage_APPIA_dteXsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure dteXsPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define bits_AQ_PhyXS_StandardDevicesInPackage_APPIA_dteXsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure dteXsPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define word_AQ_PhyXS_StandardDevicesInPackage_APPIA_dteXsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_Present in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define AQ_PhyXS_StandardDevicesInPackage_APPIA_phyXS_Present 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_Present in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define bits_AQ_PhyXS_StandardDevicesInPackage_APPIA_phyXS_Present u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_Present in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define word_AQ_PhyXS_StandardDevicesInPackage_APPIA_phyXS_Present u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define AQ_PhyXS_StandardDevicesInPackage_APPIA_pcsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define bits_AQ_PhyXS_StandardDevicesInPackage_APPIA_pcsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define word_AQ_PhyXS_StandardDevicesInPackage_APPIA_pcsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure wisPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define AQ_PhyXS_StandardDevicesInPackage_APPIA_wisPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure wisPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define bits_AQ_PhyXS_StandardDevicesInPackage_APPIA_wisPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure wisPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define word_AQ_PhyXS_StandardDevicesInPackage_APPIA_wisPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define AQ_PhyXS_StandardDevicesInPackage_APPIA_pmaPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define bits_AQ_PhyXS_StandardDevicesInPackage_APPIA_pmaPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define word_AQ_PhyXS_StandardDevicesInPackage_APPIA_pmaPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clause_22RegistersPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define AQ_PhyXS_StandardDevicesInPackage_APPIA_clause_22RegistersPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22RegistersPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define bits_AQ_PhyXS_StandardDevicesInPackage_APPIA_clause_22RegistersPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clause_22RegistersPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define word_AQ_PhyXS_StandardDevicesInPackage_APPIA_clause_22RegistersPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_2Present in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define AQ_PhyXS_StandardDevicesInPackage_APPIA_vendorSpecificDevice_2Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_2Present in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define bits_AQ_PhyXS_StandardDevicesInPackage_APPIA_vendorSpecificDevice_2Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_2Present in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define word_AQ_PhyXS_StandardDevicesInPackage_APPIA_vendorSpecificDevice_2Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_1Present in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define AQ_PhyXS_StandardDevicesInPackage_APPIA_vendorSpecificDevice_1Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_1Present in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define bits_AQ_PhyXS_StandardDevicesInPackage_APPIA_vendorSpecificDevice_1Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_1Present in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define word_AQ_PhyXS_StandardDevicesInPackage_APPIA_vendorSpecificDevice_1Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure clause_22ExtensionPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define AQ_PhyXS_StandardDevicesInPackage_APPIA_clause_22ExtensionPresent 1
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22ExtensionPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define bits_AQ_PhyXS_StandardDevicesInPackage_APPIA_clause_22ExtensionPresent u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure clause_22ExtensionPresent in AQ_PhyXS_StandardDevicesInPackage_APPIA */
#define word_AQ_PhyXS_StandardDevicesInPackage_APPIA_clause_22ExtensionPresent u1.word_1

/*! \brief Base register address of structure AQ_PhyXS_StandardStatus_2_APPIA */
#define AQ_PhyXS_StandardStatus_2_APPIA_baseRegisterAddress 0x0008
/*! \brief MMD address of structure AQ_PhyXS_StandardStatus_2_APPIA */
#define AQ_PhyXS_StandardStatus_2_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure devicePresent in AQ_PhyXS_StandardStatus_2_APPIA */
#define AQ_PhyXS_StandardStatus_2_APPIA_devicePresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure devicePresent in AQ_PhyXS_StandardStatus_2_APPIA */
#define bits_AQ_PhyXS_StandardStatus_2_APPIA_devicePresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure devicePresent in AQ_PhyXS_StandardStatus_2_APPIA */
#define word_AQ_PhyXS_StandardStatus_2_APPIA_devicePresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitFault in AQ_PhyXS_StandardStatus_2_APPIA */
#define AQ_PhyXS_StandardStatus_2_APPIA_transmitFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure transmitFault in AQ_PhyXS_StandardStatus_2_APPIA */
#define bits_AQ_PhyXS_StandardStatus_2_APPIA_transmitFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure transmitFault in AQ_PhyXS_StandardStatus_2_APPIA */
#define word_AQ_PhyXS_StandardStatus_2_APPIA_transmitFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure receiveFault in AQ_PhyXS_StandardStatus_2_APPIA */
#define AQ_PhyXS_StandardStatus_2_APPIA_receiveFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure receiveFault in AQ_PhyXS_StandardStatus_2_APPIA */
#define bits_AQ_PhyXS_StandardStatus_2_APPIA_receiveFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure receiveFault in AQ_PhyXS_StandardStatus_2_APPIA */
#define word_AQ_PhyXS_StandardStatus_2_APPIA_receiveFault u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_StandardPackageIdentifier_APPIA */
#define AQ_PhyXS_StandardPackageIdentifier_APPIA_baseRegisterAddress 0x000E
/*! \brief MMD address of structure AQ_PhyXS_StandardPackageIdentifier_APPIA */
#define AQ_PhyXS_StandardPackageIdentifier_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure packageIdMSW in AQ_PhyXS_StandardPackageIdentifier_APPIA */
#define AQ_PhyXS_StandardPackageIdentifier_APPIA_packageIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdMSW in AQ_PhyXS_StandardPackageIdentifier_APPIA */
#define bits_AQ_PhyXS_StandardPackageIdentifier_APPIA_packageIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure packageIdMSW in AQ_PhyXS_StandardPackageIdentifier_APPIA */
#define word_AQ_PhyXS_StandardPackageIdentifier_APPIA_packageIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure packageIdLSW in AQ_PhyXS_StandardPackageIdentifier_APPIA */
#define AQ_PhyXS_StandardPackageIdentifier_APPIA_packageIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdLSW in AQ_PhyXS_StandardPackageIdentifier_APPIA */
#define bits_AQ_PhyXS_StandardPackageIdentifier_APPIA_packageIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure packageIdLSW in AQ_PhyXS_StandardPackageIdentifier_APPIA */
#define word_AQ_PhyXS_StandardPackageIdentifier_APPIA_packageIdLSW u1.word_1

/*! \brief Base register address of structure AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_baseRegisterAddress 0x0018
/*! \brief MMD address of structure AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure phyXGXS_LaneAlignmentStatus in AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_phyXGXS_LaneAlignmentStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXGXS_LaneAlignmentStatus in AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define bits_AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_phyXGXS_LaneAlignmentStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXGXS_LaneAlignmentStatus in AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define word_AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_phyXGXS_LaneAlignmentStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXGXS_PatternTestingAbility in AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_phyXGXS_PatternTestingAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXGXS_PatternTestingAbility in AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define bits_AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_phyXGXS_PatternTestingAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXGXS_PatternTestingAbility in AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define word_AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_phyXGXS_PatternTestingAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXGXS_LoopbackAbility in AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_phyXGXS_LoopbackAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXGXS_LoopbackAbility in AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define bits_AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_phyXGXS_LoopbackAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXGXS_LoopbackAbility in AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define word_AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_phyXGXS_LoopbackAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure laneSync in AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_laneSync 0
/*! \brief Preprocessor variable to relate field to bit position in structure laneSync in AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define bits_AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_laneSync u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure laneSync in AQ_PhyXS_StandardXGXS_LaneStatus_APPIA */
#define word_AQ_PhyXS_StandardXGXS_LaneStatus_APPIA_laneSync u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_StandardXGXS_TestControl_APPIA */
#define AQ_PhyXS_StandardXGXS_TestControl_APPIA_baseRegisterAddress 0x0019
/*! \brief MMD address of structure AQ_PhyXS_StandardXGXS_TestControl_APPIA */
#define AQ_PhyXS_StandardXGXS_TestControl_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure receiveTest_PatternEnable in AQ_PhyXS_StandardXGXS_TestControl_APPIA */
#define AQ_PhyXS_StandardXGXS_TestControl_APPIA_receiveTest_PatternEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure receiveTest_PatternEnable in AQ_PhyXS_StandardXGXS_TestControl_APPIA */
#define bits_AQ_PhyXS_StandardXGXS_TestControl_APPIA_receiveTest_PatternEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure receiveTest_PatternEnable in AQ_PhyXS_StandardXGXS_TestControl_APPIA */
#define word_AQ_PhyXS_StandardXGXS_TestControl_APPIA_receiveTest_PatternEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure test_patternSelect in AQ_PhyXS_StandardXGXS_TestControl_APPIA */
#define AQ_PhyXS_StandardXGXS_TestControl_APPIA_test_patternSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure test_patternSelect in AQ_PhyXS_StandardXGXS_TestControl_APPIA */
#define bits_AQ_PhyXS_StandardXGXS_TestControl_APPIA_test_patternSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure test_patternSelect in AQ_PhyXS_StandardXGXS_TestControl_APPIA */
#define word_AQ_PhyXS_StandardXGXS_TestControl_APPIA_test_patternSelect u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_SerdesConfiguration_APPIA */
#define AQ_PhyXS_SerdesConfiguration_APPIA_baseRegisterAddress 0xC180
/*! \brief MMD address of structure AQ_PhyXS_SerdesConfiguration_APPIA */
#define AQ_PhyXS_SerdesConfiguration_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure serdesAhbAddress_8 in AQ_PhyXS_SerdesConfiguration_APPIA */
#define AQ_PhyXS_SerdesConfiguration_APPIA_serdesAhbAddress_8 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesAhbAddress_8 in AQ_PhyXS_SerdesConfiguration_APPIA */
#define bits_AQ_PhyXS_SerdesConfiguration_APPIA_serdesAhbAddress_8 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesAhbAddress_8 in AQ_PhyXS_SerdesConfiguration_APPIA */
#define word_AQ_PhyXS_SerdesConfiguration_APPIA_serdesAhbAddress_8 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure serdesDeviceSelection in AQ_PhyXS_SerdesConfiguration_APPIA */
#define AQ_PhyXS_SerdesConfiguration_APPIA_serdesDeviceSelection 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesDeviceSelection in AQ_PhyXS_SerdesConfiguration_APPIA */
#define bits_AQ_PhyXS_SerdesConfiguration_APPIA_serdesDeviceSelection u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesDeviceSelection in AQ_PhyXS_SerdesConfiguration_APPIA */
#define word_AQ_PhyXS_SerdesConfiguration_APPIA_serdesDeviceSelection u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_SerdesLane_0Configuration_APPIA */
#define AQ_PhyXS_SerdesLane_0Configuration_APPIA_baseRegisterAddress 0xC1C0
/*! \brief MMD address of structure AQ_PhyXS_SerdesLane_0Configuration_APPIA */
#define AQ_PhyXS_SerdesLane_0Configuration_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure serdesLane_0Reset in AQ_PhyXS_SerdesLane_0Configuration_APPIA */
#define AQ_PhyXS_SerdesLane_0Configuration_APPIA_serdesLane_0Reset 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesLane_0Reset in AQ_PhyXS_SerdesLane_0Configuration_APPIA */
#define bits_AQ_PhyXS_SerdesLane_0Configuration_APPIA_serdesLane_0Reset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesLane_0Reset in AQ_PhyXS_SerdesLane_0Configuration_APPIA */
#define word_AQ_PhyXS_SerdesLane_0Configuration_APPIA_serdesLane_0Reset u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_SerdesLane_1Configuration_APPIA */
#define AQ_PhyXS_SerdesLane_1Configuration_APPIA_baseRegisterAddress 0xC1D0
/*! \brief MMD address of structure AQ_PhyXS_SerdesLane_1Configuration_APPIA */
#define AQ_PhyXS_SerdesLane_1Configuration_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure serdesLane_1Reset in AQ_PhyXS_SerdesLane_1Configuration_APPIA */
#define AQ_PhyXS_SerdesLane_1Configuration_APPIA_serdesLane_1Reset 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesLane_1Reset in AQ_PhyXS_SerdesLane_1Configuration_APPIA */
#define bits_AQ_PhyXS_SerdesLane_1Configuration_APPIA_serdesLane_1Reset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesLane_1Reset in AQ_PhyXS_SerdesLane_1Configuration_APPIA */
#define word_AQ_PhyXS_SerdesLane_1Configuration_APPIA_serdesLane_1Reset u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_SerdesLane_2Configuration_APPIA */
#define AQ_PhyXS_SerdesLane_2Configuration_APPIA_baseRegisterAddress 0xC1E0
/*! \brief MMD address of structure AQ_PhyXS_SerdesLane_2Configuration_APPIA */
#define AQ_PhyXS_SerdesLane_2Configuration_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure serdesLane_2Reset in AQ_PhyXS_SerdesLane_2Configuration_APPIA */
#define AQ_PhyXS_SerdesLane_2Configuration_APPIA_serdesLane_2Reset 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesLane_2Reset in AQ_PhyXS_SerdesLane_2Configuration_APPIA */
#define bits_AQ_PhyXS_SerdesLane_2Configuration_APPIA_serdesLane_2Reset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesLane_2Reset in AQ_PhyXS_SerdesLane_2Configuration_APPIA */
#define word_AQ_PhyXS_SerdesLane_2Configuration_APPIA_serdesLane_2Reset u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_SerdesLane_3Configuration_APPIA */
#define AQ_PhyXS_SerdesLane_3Configuration_APPIA_baseRegisterAddress 0xC1F0
/*! \brief MMD address of structure AQ_PhyXS_SerdesLane_3Configuration_APPIA */
#define AQ_PhyXS_SerdesLane_3Configuration_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure serdesLane_3Reset in AQ_PhyXS_SerdesLane_3Configuration_APPIA */
#define AQ_PhyXS_SerdesLane_3Configuration_APPIA_serdesLane_3Reset 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesLane_3Reset in AQ_PhyXS_SerdesLane_3Configuration_APPIA */
#define bits_AQ_PhyXS_SerdesLane_3Configuration_APPIA_serdesLane_3Reset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesLane_3Reset in AQ_PhyXS_SerdesLane_3Configuration_APPIA */
#define word_AQ_PhyXS_SerdesLane_3Configuration_APPIA_serdesLane_3Reset u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_SerdesLut_APPIA */
#define AQ_PhyXS_SerdesLut_APPIA_baseRegisterAddress 0xC200
/*! \brief MMD address of structure AQ_PhyXS_SerdesLut_APPIA */
#define AQ_PhyXS_SerdesLut_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure serdesAhbData in AQ_PhyXS_SerdesLut_APPIA */
#define AQ_PhyXS_SerdesLut_APPIA_serdesAhbData 0
/*! \brief Preprocessor variable to relate field to bit position in structure serdesAhbData in AQ_PhyXS_SerdesLut_APPIA */
#define bits_AQ_PhyXS_SerdesLut_APPIA_serdesAhbData u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure serdesAhbData in AQ_PhyXS_SerdesLut_APPIA */
#define word_AQ_PhyXS_SerdesLut_APPIA_serdesAhbData u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_baseRegisterAddress 0xC440
/*! \brief MMD address of structure AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure high_speedClockOutputSelect in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_high_speedClockOutputSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure high_speedClockOutputSelect in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_high_speedClockOutputSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure high_speedClockOutputSelect in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_high_speedClockOutputSelect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure high_speedClockOutputSource in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_high_speedClockOutputSource 0
/*! \brief Preprocessor variable to relate field to bit position in structure high_speedClockOutputSource in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_high_speedClockOutputSource u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure high_speedClockOutputSource in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_high_speedClockOutputSource u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _25MhzDisable in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA__25MhzDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _25MhzDisable in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA__25MhzDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _25MhzDisable in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA__25MhzDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _25MhzClockOutputSource in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA__25MhzClockOutputSource 0
/*! \brief Preprocessor variable to relate field to bit position in structure _25MhzClockOutputSource in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA__25MhzClockOutputSource u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _25MhzClockOutputSource in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA__25MhzClockOutputSource u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedTransmitProvisioning_1 in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedTransmitProvisioning_1 in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedTransmitProvisioning_1 in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure loadSerdesParameters in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_loadSerdesParameters 0
/*! \brief Preprocessor variable to relate field to bit position in structure loadSerdesParameters in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_loadSerdesParameters u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure loadSerdesParameters in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_loadSerdesParameters u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure systemI_f10G_OperatingMode in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemI_f10G_OperatingMode 1
/*! \brief Preprocessor variable to relate field to bit position in structure systemI_f10G_OperatingMode in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemI_f10G_OperatingMode u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure systemI_f10G_OperatingMode in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemI_f10G_OperatingMode u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedTransmitProvisioning_2a in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_2a 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedTransmitProvisioning_2a in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_2a u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedTransmitProvisioning_2a in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_2a u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure phyOperatingMode in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_phyOperatingMode 1
/*! \brief Preprocessor variable to relate field to bit position in structure phyOperatingMode in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_phyOperatingMode u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure phyOperatingMode in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_phyOperatingMode u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure rxauiOperatingMode in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rxauiOperatingMode 1
/*! \brief Preprocessor variable to relate field to bit position in structure rxauiOperatingMode in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rxauiOperatingMode u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure rxauiOperatingMode in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rxauiOperatingMode u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure _1_1WorkingChannel in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA__1_1WorkingChannel 1
/*! \brief Preprocessor variable to relate field to bit position in structure _1_1WorkingChannel in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA__1_1WorkingChannel u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure _1_1WorkingChannel in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA__1_1WorkingChannel u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedTransmitProvisioning_2b in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_2b 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedTransmitProvisioning_2b in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_2b u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedTransmitProvisioning_2b in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_2b u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure lookasidePortOperatingMode in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_lookasidePortOperatingMode 1
/*! \brief Preprocessor variable to relate field to bit position in structure lookasidePortOperatingMode in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_lookasidePortOperatingMode u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure lookasidePortOperatingMode in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_lookasidePortOperatingMode u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxLane_3Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLane_3Serdes 2
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxLane_3Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLane_3Serdes u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxLane_3Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLane_3Serdes u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxLane_2Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLane_2Serdes 2
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxLane_2Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLane_2Serdes u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxLane_2Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLane_2Serdes u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxLane_1Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLane_1Serdes 2
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxLane_1Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLane_1Serdes u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxLane_1Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLane_1Serdes u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxLane_0Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLane_0Serdes 2
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxLane_0Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLane_0Serdes u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxLane_0Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLane_0Serdes u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxLaneInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLaneInvert 2
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxLaneInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLaneInvert u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxLaneInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_xauiRxLaneInvert u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure systemSgmiiRxSerdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemSgmiiRxSerdes 2
/*! \brief Preprocessor variable to relate field to bit position in structure systemSgmiiRxSerdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemSgmiiRxSerdes u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure systemSgmiiRxSerdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemSgmiiRxSerdes u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure systemSgmiiRxInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemSgmiiRxInvert 2
/*! \brief Preprocessor variable to relate field to bit position in structure systemSgmiiRxInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemSgmiiRxInvert u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure systemSgmiiRxInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemSgmiiRxInvert u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure rxauiRxLane_1Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rxauiRxLane_1Serdes 3
/*! \brief Preprocessor variable to relate field to bit position in structure rxauiRxLane_1Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rxauiRxLane_1Serdes u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure rxauiRxLane_1Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rxauiRxLane_1Serdes u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure rxauiRxLane_0Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rxauiRxLane_0Serdes 3
/*! \brief Preprocessor variable to relate field to bit position in structure rxauiRxLane_0Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rxauiRxLane_0Serdes u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure rxauiRxLane_0Serdes in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rxauiRxLane_0Serdes u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure rxauiRxLaneInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rxauiRxLaneInvert 3
/*! \brief Preprocessor variable to relate field to bit position in structure rxauiRxLaneInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rxauiRxLaneInvert u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure rxauiRxLaneInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rxauiRxLaneInvert u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure systemXfiRxInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemXfiRxInvert 3
/*! \brief Preprocessor variable to relate field to bit position in structure systemXfiRxInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemXfiRxInvert u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure systemXfiRxInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemXfiRxInvert u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure lookasidePortRxInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_lookasidePortRxInvert 3
/*! \brief Preprocessor variable to relate field to bit position in structure lookasidePortRxInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_lookasidePortRxInvert u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure lookasidePortRxInvert in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_lookasidePortRxInvert u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure reservedTransmitProvisioning_4 in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure reservedTransmitProvisioning_4 in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure reservedTransmitProvisioning_4 in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure serdesRxTerminationImpedanceControl in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_serdesRxTerminationImpedanceControl 3
/*! \brief Preprocessor variable to relate field to bit position in structure serdesRxTerminationImpedanceControl in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_serdesRxTerminationImpedanceControl u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure serdesRxTerminationImpedanceControl in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_serdesRxTerminationImpedanceControl u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure loopbackControl in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_loopbackControl 4
/*! \brief Preprocessor variable to relate field to bit position in structure loopbackControl in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_loopbackControl u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure loopbackControl in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_loopbackControl u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure reservedTransmitProvisioning_5 in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_5 4
/*! \brief Preprocessor variable to relate field to bit position in structure reservedTransmitProvisioning_5 in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_5 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure reservedTransmitProvisioning_5 in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_5 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure mdiPacketGeneration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_mdiPacketGeneration 4
/*! \brief Preprocessor variable to relate field to bit position in structure mdiPacketGeneration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_mdiPacketGeneration u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure mdiPacketGeneration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_mdiPacketGeneration u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure look_asidePortPacketGeneration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_look_asidePortPacketGeneration 4
/*! \brief Preprocessor variable to relate field to bit position in structure look_asidePortPacketGeneration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_look_asidePortPacketGeneration u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure look_asidePortPacketGeneration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_look_asidePortPacketGeneration u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure systemI_fPacketGeneration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemI_fPacketGeneration 4
/*! \brief Preprocessor variable to relate field to bit position in structure systemI_fPacketGeneration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemI_fPacketGeneration u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure systemI_fPacketGeneration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_systemI_fPacketGeneration u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure rate in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rate 4
/*! \brief Preprocessor variable to relate field to bit position in structure rate in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rate u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure rate in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_rate u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure disableAutomaticAttenuationCalibration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_disableAutomaticAttenuationCalibration 5
/*! \brief Preprocessor variable to relate field to bit position in structure disableAutomaticAttenuationCalibration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_disableAutomaticAttenuationCalibration u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure disableAutomaticAttenuationCalibration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_disableAutomaticAttenuationCalibration u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure disableAutomaticBoostCalibration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_disableAutomaticBoostCalibration 5
/*! \brief Preprocessor variable to relate field to bit position in structure disableAutomaticBoostCalibration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_disableAutomaticBoostCalibration u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure disableAutomaticBoostCalibration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_disableAutomaticBoostCalibration u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure disableAutomaticTerminationCalibration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_disableAutomaticTerminationCalibration 5
/*! \brief Preprocessor variable to relate field to bit position in structure disableAutomaticTerminationCalibration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_disableAutomaticTerminationCalibration u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure disableAutomaticTerminationCalibration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_disableAutomaticTerminationCalibration u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure forceRxRe_calibration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_forceRxRe_calibration 5
/*! \brief Preprocessor variable to relate field to bit position in structure forceRxRe_calibration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_forceRxRe_calibration u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure forceRxRe_calibration in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_forceRxRe_calibration u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure reservedTransmitProvisioning_6 in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_6 5
/*! \brief Preprocessor variable to relate field to bit position in structure reservedTransmitProvisioning_6 in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_6 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure reservedTransmitProvisioning_6 in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_reservedTransmitProvisioning_6 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure commonRxAttenuation in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_commonRxAttenuation 5
/*! \brief Preprocessor variable to relate field to bit position in structure commonRxAttenuation in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_commonRxAttenuation u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure commonRxAttenuation in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_commonRxAttenuation u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure commonRxBoost in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_commonRxBoost 5
/*! \brief Preprocessor variable to relate field to bit position in structure commonRxBoost in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_commonRxBoost u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure commonRxBoost in AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA_commonRxBoost u5.word_5

/*! \brief Base register address of structure AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_baseRegisterAddress 0xC802
/*! \brief MMD address of structure AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure txFrameCounterLSW in AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_txFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure txFrameCounterLSW in AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_txFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure txFrameCounterLSW in AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_txFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure txFrameCounterMSW in AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_txFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure txFrameCounterMSW in AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_txFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure txFrameCounterMSW in AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_txFrameCounterMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure txFrameErrorCounterLSW in AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_txFrameErrorCounterLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure txFrameErrorCounterLSW in AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_txFrameErrorCounterLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure txFrameErrorCounterLSW in AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_txFrameErrorCounterLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure txFrameErrorCounterMSW in AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_txFrameErrorCounterMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure txFrameErrorCounterMSW in AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_txFrameErrorCounterMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure txFrameErrorCounterMSW in AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA_txFrameErrorCounterMSW u3.word_3

/*! \brief Base register address of structure AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_baseRegisterAddress 0xCC00
/*! \brief MMD address of structure AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure crpatTestPatternCheckerSyncError in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_crpatTestPatternCheckerSyncError 0
/*! \brief Preprocessor variable to relate field to bit position in structure crpatTestPatternCheckerSyncError in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_crpatTestPatternCheckerSyncError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure crpatTestPatternCheckerSyncError in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_crpatTestPatternCheckerSyncError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure prbsTestPatternCheckerSyncError in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_prbsTestPatternCheckerSyncError 0
/*! \brief Preprocessor variable to relate field to bit position in structure prbsTestPatternCheckerSyncError in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_prbsTestPatternCheckerSyncError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure prbsTestPatternCheckerSyncError in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_prbsTestPatternCheckerSyncError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxSequenceOrderedSetDeletion in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxSequenceOrderedSetDeletion 1
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxSequenceOrderedSetDeletion in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxSequenceOrderedSetDeletion u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxSequenceOrderedSetDeletion in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxSequenceOrderedSetDeletion u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxRxauiLaneAlignmentLockStatus in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxRxauiLaneAlignmentLockStatus 1
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxRxauiLaneAlignmentLockStatus in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxRxauiLaneAlignmentLockStatus u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxRxauiLaneAlignmentLockStatus in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxRxauiLaneAlignmentLockStatus u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxReservedXgmiiCharacterReceived in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxReservedXgmiiCharacterReceived 1
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxReservedXgmiiCharacterReceived in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxReservedXgmiiCharacterReceived u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxReservedXgmiiCharacterReceived in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxReservedXgmiiCharacterReceived u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxInvalidXgmiiCharacterReceived in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxInvalidXgmiiCharacterReceived 1
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxInvalidXgmiiCharacterReceived in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxInvalidXgmiiCharacterReceived u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxInvalidXgmiiCharacterReceived in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxInvalidXgmiiCharacterReceived u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxCodeViolationError in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxCodeViolationError 1
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxCodeViolationError in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxCodeViolationError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxCodeViolationError in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxCodeViolationError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxRunningDisparityError in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxRunningDisparityError 1
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxRunningDisparityError in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxRunningDisparityError u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxRunningDisparityError in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_xauiRxRunningDisparityError u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure lossOfSignal in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_lossOfSignal 2
/*! \brief Preprocessor variable to relate field to bit position in structure lossOfSignal in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_lossOfSignal u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure lossOfSignal in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_lossOfSignal u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedPhyXsTransmitAlarms in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_reservedPhyXsTransmitAlarms 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPhyXsTransmitAlarms in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_reservedPhyXsTransmitAlarms u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedPhyXsTransmitAlarms in AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA_reservedPhyXsTransmitAlarms u2.word_2

/*! \brief Base register address of structure AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA_baseRegisterAddress 0xD000
/*! \brief MMD address of structure AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_TransmitLinkAlignmentStatusMask in AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA_phyXS_TransmitLinkAlignmentStatusMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_TransmitLinkAlignmentStatusMask in AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA_phyXS_TransmitLinkAlignmentStatusMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_TransmitLinkAlignmentStatusMask in AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA_phyXS_TransmitLinkAlignmentStatusMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitFaultMask in AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA_transmitFaultMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure transmitFaultMask in AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA_transmitFaultMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure transmitFaultMask in AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA_transmitFaultMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure receiveFaultMask in AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA_receiveFaultMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure receiveFaultMask in AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA_receiveFaultMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure receiveFaultMask in AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA_receiveFaultMask u1.word_1

/*! \brief Base register address of structure AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_baseRegisterAddress 0xD400
/*! \brief MMD address of structure AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure crpatTestPatternCheckerSyncErrorMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_crpatTestPatternCheckerSyncErrorMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure crpatTestPatternCheckerSyncErrorMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_crpatTestPatternCheckerSyncErrorMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure crpatTestPatternCheckerSyncErrorMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_crpatTestPatternCheckerSyncErrorMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure prbsTestPatternCheckerSyncErrorMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_prbsTestPatternCheckerSyncErrorMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure prbsTestPatternCheckerSyncErrorMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_prbsTestPatternCheckerSyncErrorMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure prbsTestPatternCheckerSyncErrorMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_prbsTestPatternCheckerSyncErrorMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxSequenceOrderedSetDeletionMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxSequenceOrderedSetDeletionMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxSequenceOrderedSetDeletionMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxSequenceOrderedSetDeletionMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxSequenceOrderedSetDeletionMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxSequenceOrderedSetDeletionMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxRxauiLaneAlignmentLockStatusMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxRxauiLaneAlignmentLockStatusMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxRxauiLaneAlignmentLockStatusMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxRxauiLaneAlignmentLockStatusMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxRxauiLaneAlignmentLockStatusMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxRxauiLaneAlignmentLockStatusMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxReservedXgmiiCharacterReceivedMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxReservedXgmiiCharacterReceivedMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxReservedXgmiiCharacterReceivedMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxReservedXgmiiCharacterReceivedMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxReservedXgmiiCharacterReceivedMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxReservedXgmiiCharacterReceivedMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxInvalidXgmiiCharacterReceivedMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxInvalidXgmiiCharacterReceivedMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxInvalidXgmiiCharacterReceivedMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxInvalidXgmiiCharacterReceivedMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxInvalidXgmiiCharacterReceivedMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxInvalidXgmiiCharacterReceivedMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxCodeViolationErrorMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxCodeViolationErrorMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxCodeViolationErrorMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxCodeViolationErrorMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxCodeViolationErrorMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxCodeViolationErrorMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxRunningDisparityErrorMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxRunningDisparityErrorMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxRunningDisparityErrorMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxRunningDisparityErrorMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxRunningDisparityErrorMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_xauiRxRunningDisparityErrorMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure lossOfSignalMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_lossOfSignalMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure lossOfSignalMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_lossOfSignalMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure lossOfSignalMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_lossOfSignalMask u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reservedPhyXsTransmitAlarmsMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_reservedPhyXsTransmitAlarmsMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPhyXsTransmitAlarmsMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_reservedPhyXsTransmitAlarmsMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedPhyXsTransmitAlarmsMask in AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA_reservedPhyXsTransmitAlarmsMask u2.word_2

/*! \brief Base register address of structure AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_baseRegisterAddress 0xD800
/*! \brief MMD address of structure AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure testPatternForceError in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternForceError 0
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternForceError in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternForceError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure testPatternForceError in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternForceError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure testPatternMode_7ForceError in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternMode_7ForceError 0
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternMode_7ForceError in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternMode_7ForceError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure testPatternMode_7ForceError in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternMode_7ForceError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiRxLocalFaultInjection in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_xauiRxLocalFaultInjection 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiRxLocalFaultInjection in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_xauiRxLocalFaultInjection u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiRxLocalFaultInjection in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_xauiRxLocalFaultInjection u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure test_patternExtendedSelect in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_test_patternExtendedSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure test_patternExtendedSelect in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_test_patternExtendedSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure test_patternExtendedSelect in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_test_patternExtendedSelect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure testPatternCheckEnable in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternCheckEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternCheckEnable in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternCheckEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure testPatternCheckEnable in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternCheckEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure testPatternCheckPoint in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternCheckPoint 0
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternCheckPoint in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternCheckPoint u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure testPatternCheckPoint in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternCheckPoint u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure testPatternMode_7CheckEnable in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternMode_7CheckEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternMode_7CheckEnable in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternMode_7CheckEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure testPatternMode_7CheckEnable in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternMode_7CheckEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure testPatternInvert in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternInvert 0
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternInvert in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternInvert u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure testPatternInvert in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternInvert u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure testPatternSynchronizationThreshold in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternSynchronizationThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternSynchronizationThreshold in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternSynchronizationThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure testPatternSynchronizationThreshold in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternSynchronizationThreshold u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure testPatternInsertExtraIdles in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternInsertExtraIdles 1
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternInsertExtraIdles in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternInsertExtraIdles u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure testPatternInsertExtraIdles in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternInsertExtraIdles u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure testPatternCheckSelect in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternCheckSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternCheckSelect in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternCheckSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure testPatternCheckSelect in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternCheckSelect u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure testPatternChannelSelect in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternChannelSelect 1
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternChannelSelect in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternChannelSelect u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure testPatternChannelSelect in AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA_testPatternChannelSelect u1.word_1

/*! \brief Base register address of structure AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_baseRegisterAddress 0xD810
/*! \brief MMD address of structure AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure channel_0TestPatternErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_channel_0TestPatternErrorCounter 0
/*! \brief Preprocessor variable to relate field to bit position in structure channel_0TestPatternErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_channel_0TestPatternErrorCounter u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channel_0TestPatternErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_channel_0TestPatternErrorCounter u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure channel_1TestPatternErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_channel_1TestPatternErrorCounter 1
/*! \brief Preprocessor variable to relate field to bit position in structure channel_1TestPatternErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_channel_1TestPatternErrorCounter u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure channel_1TestPatternErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_channel_1TestPatternErrorCounter u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure channel_2TestPatternErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_channel_2TestPatternErrorCounter 2
/*! \brief Preprocessor variable to relate field to bit position in structure channel_2TestPatternErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_channel_2TestPatternErrorCounter u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure channel_2TestPatternErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_channel_2TestPatternErrorCounter u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure channel_3TestPatternErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_channel_3TestPatternErrorCounter 3
/*! \brief Preprocessor variable to relate field to bit position in structure channel_3TestPatternErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_channel_3TestPatternErrorCounter u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure channel_3TestPatternErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_channel_3TestPatternErrorCounter u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure testPatternMode_7ErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_testPatternMode_7ErrorCounter 4
/*! \brief Preprocessor variable to relate field to bit position in structure testPatternMode_7ErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define bits_AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_testPatternMode_7ErrorCounter u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure testPatternMode_7ErrorCounter in AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA */
#define word_AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA_testPatternMode_7ErrorCounter u4.word_4

/*! \brief Base register address of structure AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_baseRegisterAddress 0xE410
/*! \brief MMD address of structure AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure xauiTxLane_3Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLane_3Serdes 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTxLane_3Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLane_3Serdes u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTxLane_3Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLane_3Serdes u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTxLane_2Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLane_2Serdes 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTxLane_2Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLane_2Serdes u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTxLane_2Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLane_2Serdes u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTxLane_1Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLane_1Serdes 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTxLane_1Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLane_1Serdes u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTxLane_1Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLane_1Serdes u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTxLane_0Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLane_0Serdes 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTxLane_0Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLane_0Serdes u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTxLane_0Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLane_0Serdes u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTxLaneInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLaneInvert 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTxLaneInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLaneInvert u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTxLaneInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_xauiTxLaneInvert u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure systemSgmiiTxSerdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_systemSgmiiTxSerdes 0
/*! \brief Preprocessor variable to relate field to bit position in structure systemSgmiiTxSerdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_systemSgmiiTxSerdes u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure systemSgmiiTxSerdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_systemSgmiiTxSerdes u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure systemSgmiiTxInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_systemSgmiiTxInvert 0
/*! \brief Preprocessor variable to relate field to bit position in structure systemSgmiiTxInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_systemSgmiiTxInvert u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure systemSgmiiTxInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_systemSgmiiTxInvert u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveProvisioning_1 in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_reservedReceiveProvisioning_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveProvisioning_1 in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_reservedReceiveProvisioning_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveProvisioning_1 in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_reservedReceiveProvisioning_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rxauiTxLane_1Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_rxauiTxLane_1Serdes 1
/*! \brief Preprocessor variable to relate field to bit position in structure rxauiTxLane_1Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_rxauiTxLane_1Serdes u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure rxauiTxLane_1Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_rxauiTxLane_1Serdes u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure rxauiTxLane_0Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_rxauiTxLane_0Serdes 1
/*! \brief Preprocessor variable to relate field to bit position in structure rxauiTxLane_0Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_rxauiTxLane_0Serdes u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure rxauiTxLane_0Serdes in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_rxauiTxLane_0Serdes u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure rxauiTxLaneInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_rxauiTxLaneInvert 1
/*! \brief Preprocessor variable to relate field to bit position in structure rxauiTxLaneInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_rxauiTxLaneInvert u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure rxauiTxLaneInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_rxauiTxLaneInvert u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure systemXfiTxInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_systemXfiTxInvert 1
/*! \brief Preprocessor variable to relate field to bit position in structure systemXfiTxInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_systemXfiTxInvert u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure systemXfiTxInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_systemXfiTxInvert u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure lookasidePortTxInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lookasidePortTxInvert 1
/*! \brief Preprocessor variable to relate field to bit position in structure lookasidePortTxInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lookasidePortTxInvert u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure lookasidePortTxInvert in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lookasidePortTxInvert u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveProvisioning_2 in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_reservedReceiveProvisioning_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveProvisioning_2 in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_reservedReceiveProvisioning_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveProvisioning_2 in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_reservedReceiveProvisioning_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure serdesTxTerminationImpedanceControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_serdesTxTerminationImpedanceControl 1
/*! \brief Preprocessor variable to relate field to bit position in structure serdesTxTerminationImpedanceControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_serdesTxTerminationImpedanceControl u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure serdesTxTerminationImpedanceControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_serdesTxTerminationImpedanceControl u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure lane_0Pre_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0Pre_cursorTapWeight 2
/*! \brief Preprocessor variable to relate field to bit position in structure lane_0Pre_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0Pre_cursorTapWeight u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure lane_0Pre_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0Pre_cursorTapWeight u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure lane_0N_1Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0N_1Post_cursorTapWeight 2
/*! \brief Preprocessor variable to relate field to bit position in structure lane_0N_1Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0N_1Post_cursorTapWeight u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure lane_0N_1Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0N_1Post_cursorTapWeight u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure lane_0N_2Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0N_2Post_cursorTapWeight 2
/*! \brief Preprocessor variable to relate field to bit position in structure lane_0N_2Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0N_2Post_cursorTapWeight u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure lane_0N_2Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0N_2Post_cursorTapWeight u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure lane_0DifferentialOutputVoltage in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0DifferentialOutputVoltage 2
/*! \brief Preprocessor variable to relate field to bit position in structure lane_0DifferentialOutputVoltage in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0DifferentialOutputVoltage u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure lane_0DifferentialOutputVoltage in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0DifferentialOutputVoltage u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure lane_0SlewRateControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0SlewRateControl 2
/*! \brief Preprocessor variable to relate field to bit position in structure lane_0SlewRateControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0SlewRateControl u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure lane_0SlewRateControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0SlewRateControl u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure lane_0PowerDown in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0PowerDown 2
/*! \brief Preprocessor variable to relate field to bit position in structure lane_0PowerDown in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0PowerDown u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure lane_0PowerDown in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_0PowerDown u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure lane_1Pre_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1Pre_cursorTapWeight 3
/*! \brief Preprocessor variable to relate field to bit position in structure lane_1Pre_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1Pre_cursorTapWeight u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure lane_1Pre_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1Pre_cursorTapWeight u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure lane_1N_1Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1N_1Post_cursorTapWeight 3
/*! \brief Preprocessor variable to relate field to bit position in structure lane_1N_1Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1N_1Post_cursorTapWeight u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure lane_1N_1Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1N_1Post_cursorTapWeight u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure lane_1N_2Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1N_2Post_cursorTapWeight 3
/*! \brief Preprocessor variable to relate field to bit position in structure lane_1N_2Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1N_2Post_cursorTapWeight u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure lane_1N_2Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1N_2Post_cursorTapWeight u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure lane_1DifferentialOutputVoltage in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1DifferentialOutputVoltage 3
/*! \brief Preprocessor variable to relate field to bit position in structure lane_1DifferentialOutputVoltage in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1DifferentialOutputVoltage u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure lane_1DifferentialOutputVoltage in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1DifferentialOutputVoltage u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure lane_1SlewRateControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1SlewRateControl 3
/*! \brief Preprocessor variable to relate field to bit position in structure lane_1SlewRateControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1SlewRateControl u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure lane_1SlewRateControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1SlewRateControl u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure lane_1PowerDown in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1PowerDown 3
/*! \brief Preprocessor variable to relate field to bit position in structure lane_1PowerDown in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1PowerDown u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure lane_1PowerDown in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_1PowerDown u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure lane_2Pre_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2Pre_cursorTapWeight 4
/*! \brief Preprocessor variable to relate field to bit position in structure lane_2Pre_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2Pre_cursorTapWeight u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure lane_2Pre_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2Pre_cursorTapWeight u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure lane_2N_1Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2N_1Post_cursorTapWeight 4
/*! \brief Preprocessor variable to relate field to bit position in structure lane_2N_1Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2N_1Post_cursorTapWeight u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure lane_2N_1Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2N_1Post_cursorTapWeight u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure lane_2N_2Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2N_2Post_cursorTapWeight 4
/*! \brief Preprocessor variable to relate field to bit position in structure lane_2N_2Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2N_2Post_cursorTapWeight u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure lane_2N_2Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2N_2Post_cursorTapWeight u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure lane_2DifferentialOutputVoltage in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2DifferentialOutputVoltage 4
/*! \brief Preprocessor variable to relate field to bit position in structure lane_2DifferentialOutputVoltage in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2DifferentialOutputVoltage u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure lane_2DifferentialOutputVoltage in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2DifferentialOutputVoltage u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure lane_2SlewRateControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2SlewRateControl 4
/*! \brief Preprocessor variable to relate field to bit position in structure lane_2SlewRateControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2SlewRateControl u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure lane_2SlewRateControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2SlewRateControl u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure lane_2PowerDown in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2PowerDown 4
/*! \brief Preprocessor variable to relate field to bit position in structure lane_2PowerDown in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2PowerDown u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure lane_2PowerDown in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_2PowerDown u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure lane_3Pre_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3Pre_cursorTapWeight 5
/*! \brief Preprocessor variable to relate field to bit position in structure lane_3Pre_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3Pre_cursorTapWeight u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure lane_3Pre_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3Pre_cursorTapWeight u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure lane_3N_1Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3N_1Post_cursorTapWeight 5
/*! \brief Preprocessor variable to relate field to bit position in structure lane_3N_1Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3N_1Post_cursorTapWeight u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure lane_3N_1Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3N_1Post_cursorTapWeight u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure lane_3N_2Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3N_2Post_cursorTapWeight 5
/*! \brief Preprocessor variable to relate field to bit position in structure lane_3N_2Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3N_2Post_cursorTapWeight u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure lane_3N_2Post_cursorTapWeight in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3N_2Post_cursorTapWeight u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure lane_3DifferentialOutputVoltage in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3DifferentialOutputVoltage 5
/*! \brief Preprocessor variable to relate field to bit position in structure lane_3DifferentialOutputVoltage in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3DifferentialOutputVoltage u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure lane_3DifferentialOutputVoltage in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3DifferentialOutputVoltage u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure lane_3SlewRateControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3SlewRateControl 5
/*! \brief Preprocessor variable to relate field to bit position in structure lane_3SlewRateControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3SlewRateControl u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure lane_3SlewRateControl in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3SlewRateControl u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure lane_3PowerDown in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3PowerDown 5
/*! \brief Preprocessor variable to relate field to bit position in structure lane_3PowerDown in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3PowerDown u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure lane_3PowerDown in AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA_lane_3PowerDown u5.word_5

/*! \brief Base register address of structure AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_baseRegisterAddress 0xE802
/*! \brief MMD address of structure AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure rxFrameCounterLSW in AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_rxFrameCounterLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure rxFrameCounterLSW in AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_rxFrameCounterLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rxFrameCounterLSW in AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_rxFrameCounterLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure rxFrameCounterMSW in AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_rxFrameCounterMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure rxFrameCounterMSW in AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_rxFrameCounterMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure rxFrameCounterMSW in AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_rxFrameCounterMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure rxFrameErrorCounterLSW in AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_rxFrameErrorCounterLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure rxFrameErrorCounterLSW in AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_rxFrameErrorCounterLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure rxFrameErrorCounterLSW in AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_rxFrameErrorCounterLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure rxFrameErrorCounterMSW in AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_rxFrameErrorCounterMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure rxFrameErrorCounterMSW in AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_rxFrameErrorCounterMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure rxFrameErrorCounterMSW in AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA_rxFrameErrorCounterMSW u3.word_3

/*! \brief Base register address of structure AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA_baseRegisterAddress 0xEC00
/*! \brief MMD address of structure AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure reservedXgmiiCharacterReceivedFromPcs in AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA_reservedXgmiiCharacterReceivedFromPcs 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedXgmiiCharacterReceivedFromPcs in AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA_reservedXgmiiCharacterReceivedFromPcs u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedXgmiiCharacterReceivedFromPcs in AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA_reservedXgmiiCharacterReceivedFromPcs u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure invalidXgmiiCharacterReceivedFromPcs in AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA_invalidXgmiiCharacterReceivedFromPcs 0
/*! \brief Preprocessor variable to relate field to bit position in structure invalidXgmiiCharacterReceivedFromPcs in AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA_invalidXgmiiCharacterReceivedFromPcs u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure invalidXgmiiCharacterReceivedFromPcs in AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA_invalidXgmiiCharacterReceivedFromPcs u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkStatusMessageReceivedFromPcs in AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA_linkStatusMessageReceivedFromPcs 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkStatusMessageReceivedFromPcs in AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA_linkStatusMessageReceivedFromPcs u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkStatusMessageReceivedFromPcs in AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA_linkStatusMessageReceivedFromPcs u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA_baseRegisterAddress 0xF400
/*! \brief MMD address of structure AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure reservedXgmiiCharacterReceivedFromPcsMask in AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA_reservedXgmiiCharacterReceivedFromPcsMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedXgmiiCharacterReceivedFromPcsMask in AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA_reservedXgmiiCharacterReceivedFromPcsMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedXgmiiCharacterReceivedFromPcsMask in AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA_reservedXgmiiCharacterReceivedFromPcsMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure invalidXgmiiCharacterReceivedFromPcsMask in AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA_invalidXgmiiCharacterReceivedFromPcsMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure invalidXgmiiCharacterReceivedFromPcsMask in AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA_invalidXgmiiCharacterReceivedFromPcsMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure invalidXgmiiCharacterReceivedFromPcsMask in AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA_invalidXgmiiCharacterReceivedFromPcsMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkStatusMessageReceivedFromPcsMask in AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA_linkStatusMessageReceivedFromPcsMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkStatusMessageReceivedFromPcsMask in AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA_linkStatusMessageReceivedFromPcsMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkStatusMessageReceivedFromPcsMask in AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA_linkStatusMessageReceivedFromPcsMask u0.word_0

/*! \brief Base register address of structure AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_baseRegisterAddress 0xF800
/*! \brief MMD address of structure AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure xauiTxErrorInjectionLaneSelect in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxErrorInjectionLaneSelect 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTxErrorInjectionLaneSelect in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxErrorInjectionLaneSelect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTxErrorInjectionLaneSelect in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxErrorInjectionLaneSelect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTxInjectSynchronizationError in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxInjectSynchronizationError 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTxInjectSynchronizationError in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxInjectSynchronizationError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTxInjectSynchronizationError in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxInjectSynchronizationError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTxInjectAlignmentError in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxInjectAlignmentError 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTxInjectAlignmentError in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxInjectAlignmentError u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTxInjectAlignmentError in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxInjectAlignmentError u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTxInjectCodeViolation in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxInjectCodeViolation 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTxInjectCodeViolation in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxInjectCodeViolation u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTxInjectCodeViolation in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxInjectCodeViolation u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure xauiTx_10bViolationCodeword in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTx_10bViolationCodeword 0
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTx_10bViolationCodeword in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTx_10bViolationCodeword u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure xauiTx_10bViolationCodeword in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTx_10bViolationCodeword u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_SystemLoopbackPassThrough in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_phyXS_SystemLoopbackPassThrough 2
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_SystemLoopbackPassThrough in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_phyXS_SystemLoopbackPassThrough u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_SystemLoopbackPassThrough in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_phyXS_SystemLoopbackPassThrough u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_SystemLoopbackEnable in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_phyXS_SystemLoopbackEnable 2
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_SystemLoopbackEnable in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_phyXS_SystemLoopbackEnable u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_SystemLoopbackEnable in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_phyXS_SystemLoopbackEnable u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure xauiTxLocalFaultInjection in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxLocalFaultInjection 2
/*! \brief Preprocessor variable to relate field to bit position in structure xauiTxLocalFaultInjection in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxLocalFaultInjection u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure xauiTxLocalFaultInjection in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_xauiTxLocalFaultInjection u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure reserved_4 in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_reserved_4 2
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_4 in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define bits_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_reserved_4 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reserved_4 in AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA */
#define word_AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA_reserved_4 u2.word_2

/*! \brief Base register address of structure AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_baseRegisterAddress 0xFC00
/*! \brief MMD address of structure AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_mmdAddress 0x04
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarms_1Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_standardAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarms_1Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_standardAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarms_1Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define word_AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_standardAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarms_2Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_standardAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarms_2Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_standardAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarms_2Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define word_AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_standardAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_1Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_1Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_1Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define word_AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_2Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_2Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_2Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define word_AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_3Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_3Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_3Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define word_AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_vendorSpecificTxAlarms_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificRxAlarms_1Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificRxAlarms_1Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define bits_AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificRxAlarms_1Interrupt in AQ_PhyXS_VendorGlobalInterruptFlags_APPIA */
#define word_AQ_PhyXS_VendorGlobalInterruptFlags_APPIA_vendorSpecificRxAlarms_1Interrupt u0.word_0
#endif
/*@}*/
/*@}*/
