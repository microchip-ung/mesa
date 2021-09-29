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
*   for the PMA Registers block.
*/

/*! \defgroup PMA_registers_Defines PMA Registers Defines
*   This module contains the compiler assist macros and doxygen comments
*   for the PMA Registers block.
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
*   This file contains the compiler assist macros for the registers contained in the PMA Registers block.
*
*
***********************************************************************/


/*@{*/
#ifndef AQ_HHD_PMA_REGS_DEFINES_HEADER
#define AQ_HHD_PMA_REGS_DEFINES_HEADER


/*-----------------------------------------------------------------------------*/
/*Access macro definitions                                                     */
/*-----------------------------------------------------------------------------*/
/*! \brief Base register address of structure AQ_PmaStandardControl_1_HHD */
#define AQ_PmaStandardControl_1_HHD_baseRegisterAddress 0x0000
/*! \brief MMD address of structure AQ_PmaStandardControl_1_HHD */
#define AQ_PmaStandardControl_1_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure reset in AQ_PmaStandardControl_1_HHD */
#define AQ_PmaStandardControl_1_HHD_reset 0
/*! \brief Preprocessor variable to relate field to bit position in structure reset in AQ_PmaStandardControl_1_HHD */
#define bits_AQ_PmaStandardControl_1_HHD_reset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reset in AQ_PmaStandardControl_1_HHD */
#define word_AQ_PmaStandardControl_1_HHD_reset u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure speedSelectionLsb in AQ_PmaStandardControl_1_HHD */
#define AQ_PmaStandardControl_1_HHD_speedSelectionLsb 0
/*! \brief Preprocessor variable to relate field to bit position in structure speedSelectionLsb in AQ_PmaStandardControl_1_HHD */
#define bits_AQ_PmaStandardControl_1_HHD_speedSelectionLsb u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure speedSelectionLsb in AQ_PmaStandardControl_1_HHD */
#define word_AQ_PmaStandardControl_1_HHD_speedSelectionLsb u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowPower in AQ_PmaStandardControl_1_HHD */
#define AQ_PmaStandardControl_1_HHD_lowPower 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowPower in AQ_PmaStandardControl_1_HHD */
#define bits_AQ_PmaStandardControl_1_HHD_lowPower u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowPower in AQ_PmaStandardControl_1_HHD */
#define word_AQ_PmaStandardControl_1_HHD_lowPower u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure speedSelectionMsb in AQ_PmaStandardControl_1_HHD */
#define AQ_PmaStandardControl_1_HHD_speedSelectionMsb 0
/*! \brief Preprocessor variable to relate field to bit position in structure speedSelectionMsb in AQ_PmaStandardControl_1_HHD */
#define bits_AQ_PmaStandardControl_1_HHD_speedSelectionMsb u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure speedSelectionMsb in AQ_PmaStandardControl_1_HHD */
#define word_AQ_PmaStandardControl_1_HHD_speedSelectionMsb u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10gSpeedSelection in AQ_PmaStandardControl_1_HHD */
#define AQ_PmaStandardControl_1_HHD__10gSpeedSelection 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10gSpeedSelection in AQ_PmaStandardControl_1_HHD */
#define bits_AQ_PmaStandardControl_1_HHD__10gSpeedSelection u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10gSpeedSelection in AQ_PmaStandardControl_1_HHD */
#define word_AQ_PmaStandardControl_1_HHD__10gSpeedSelection u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure loopback in AQ_PmaStandardControl_1_HHD */
#define AQ_PmaStandardControl_1_HHD_loopback 0
/*! \brief Preprocessor variable to relate field to bit position in structure loopback in AQ_PmaStandardControl_1_HHD */
#define bits_AQ_PmaStandardControl_1_HHD_loopback u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure loopback in AQ_PmaStandardControl_1_HHD */
#define word_AQ_PmaStandardControl_1_HHD_loopback u0.word_0

/*! \brief Base register address of structure AQ_PmaStandardStatus_1_HHD */
#define AQ_PmaStandardStatus_1_HHD_baseRegisterAddress 0x0001
/*! \brief MMD address of structure AQ_PmaStandardStatus_1_HHD */
#define AQ_PmaStandardStatus_1_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure fault in AQ_PmaStandardStatus_1_HHD */
#define AQ_PmaStandardStatus_1_HHD_fault 0
/*! \brief Preprocessor variable to relate field to bit position in structure fault in AQ_PmaStandardStatus_1_HHD */
#define bits_AQ_PmaStandardStatus_1_HHD_fault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure fault in AQ_PmaStandardStatus_1_HHD */
#define word_AQ_PmaStandardStatus_1_HHD_fault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaReceiveLinkStatus in AQ_PmaStandardStatus_1_HHD */
#define AQ_PmaStandardStatus_1_HHD_pmaReceiveLinkStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaReceiveLinkStatus in AQ_PmaStandardStatus_1_HHD */
#define bits_AQ_PmaStandardStatus_1_HHD_pmaReceiveLinkStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaReceiveLinkStatus in AQ_PmaStandardStatus_1_HHD */
#define word_AQ_PmaStandardStatus_1_HHD_pmaReceiveLinkStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowPowerAbility in AQ_PmaStandardStatus_1_HHD */
#define AQ_PmaStandardStatus_1_HHD_lowPowerAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowPowerAbility in AQ_PmaStandardStatus_1_HHD */
#define bits_AQ_PmaStandardStatus_1_HHD_lowPowerAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowPowerAbility in AQ_PmaStandardStatus_1_HHD */
#define word_AQ_PmaStandardStatus_1_HHD_lowPowerAbility u0.word_0

/*! \brief Base register address of structure AQ_PmaStandardDeviceIdentifier_HHD */
#define AQ_PmaStandardDeviceIdentifier_HHD_baseRegisterAddress 0x0002
/*! \brief MMD address of structure AQ_PmaStandardDeviceIdentifier_HHD */
#define AQ_PmaStandardDeviceIdentifier_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdMSW in AQ_PmaStandardDeviceIdentifier_HHD */
#define AQ_PmaStandardDeviceIdentifier_HHD_deviceIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdMSW in AQ_PmaStandardDeviceIdentifier_HHD */
#define bits_AQ_PmaStandardDeviceIdentifier_HHD_deviceIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdMSW in AQ_PmaStandardDeviceIdentifier_HHD */
#define word_AQ_PmaStandardDeviceIdentifier_HHD_deviceIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure deviceIdLSW in AQ_PmaStandardDeviceIdentifier_HHD */
#define AQ_PmaStandardDeviceIdentifier_HHD_deviceIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure deviceIdLSW in AQ_PmaStandardDeviceIdentifier_HHD */
#define bits_AQ_PmaStandardDeviceIdentifier_HHD_deviceIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure deviceIdLSW in AQ_PmaStandardDeviceIdentifier_HHD */
#define word_AQ_PmaStandardDeviceIdentifier_HHD_deviceIdLSW u1.word_1

/*! \brief Base register address of structure AQ_PmaStandardSpeedAbility_HHD */
#define AQ_PmaStandardSpeedAbility_HHD_baseRegisterAddress 0x0004
/*! \brief MMD address of structure AQ_PmaStandardSpeedAbility_HHD */
#define AQ_PmaStandardSpeedAbility_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure pma10M_Capable in AQ_PmaStandardSpeedAbility_HHD */
#define AQ_PmaStandardSpeedAbility_HHD_pma10M_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10M_Capable in AQ_PmaStandardSpeedAbility_HHD */
#define bits_AQ_PmaStandardSpeedAbility_HHD_pma10M_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10M_Capable in AQ_PmaStandardSpeedAbility_HHD */
#define word_AQ_PmaStandardSpeedAbility_HHD_pma10M_Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma100M_Capable in AQ_PmaStandardSpeedAbility_HHD */
#define AQ_PmaStandardSpeedAbility_HHD_pma100M_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma100M_Capable in AQ_PmaStandardSpeedAbility_HHD */
#define bits_AQ_PmaStandardSpeedAbility_HHD_pma100M_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma100M_Capable in AQ_PmaStandardSpeedAbility_HHD */
#define word_AQ_PmaStandardSpeedAbility_HHD_pma100M_Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma1G_Capable in AQ_PmaStandardSpeedAbility_HHD */
#define AQ_PmaStandardSpeedAbility_HHD_pma1G_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma1G_Capable in AQ_PmaStandardSpeedAbility_HHD */
#define bits_AQ_PmaStandardSpeedAbility_HHD_pma1G_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma1G_Capable in AQ_PmaStandardSpeedAbility_HHD */
#define word_AQ_PmaStandardSpeedAbility_HHD_pma1G_Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _10pass_tsCapable in AQ_PmaStandardSpeedAbility_HHD */
#define AQ_PmaStandardSpeedAbility_HHD__10pass_tsCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _10pass_tsCapable in AQ_PmaStandardSpeedAbility_HHD */
#define bits_AQ_PmaStandardSpeedAbility_HHD__10pass_tsCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _10pass_tsCapable in AQ_PmaStandardSpeedAbility_HHD */
#define word_AQ_PmaStandardSpeedAbility_HHD__10pass_tsCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure _2base_tlCapable in AQ_PmaStandardSpeedAbility_HHD */
#define AQ_PmaStandardSpeedAbility_HHD__2base_tlCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure _2base_tlCapable in AQ_PmaStandardSpeedAbility_HHD */
#define bits_AQ_PmaStandardSpeedAbility_HHD__2base_tlCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _2base_tlCapable in AQ_PmaStandardSpeedAbility_HHD */
#define word_AQ_PmaStandardSpeedAbility_HHD__2base_tlCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma10G_Capable in AQ_PmaStandardSpeedAbility_HHD */
#define AQ_PmaStandardSpeedAbility_HHD_pma10G_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10G_Capable in AQ_PmaStandardSpeedAbility_HHD */
#define bits_AQ_PmaStandardSpeedAbility_HHD_pma10G_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10G_Capable in AQ_PmaStandardSpeedAbility_HHD */
#define word_AQ_PmaStandardSpeedAbility_HHD_pma10G_Capable u0.word_0

/*! \brief Base register address of structure AQ_PmaStandardDevicesInPackage_HHD */
#define AQ_PmaStandardDevicesInPackage_HHD_baseRegisterAddress 0x0005
/*! \brief MMD address of structure AQ_PmaStandardDevicesInPackage_HHD */
#define AQ_PmaStandardDevicesInPackage_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure autonegotiationPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define AQ_PmaStandardDevicesInPackage_HHD_autonegotiationPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure autonegotiationPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define bits_AQ_PmaStandardDevicesInPackage_HHD_autonegotiationPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure autonegotiationPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define word_AQ_PmaStandardDevicesInPackage_HHD_autonegotiationPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure tcPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define AQ_PmaStandardDevicesInPackage_HHD_tcPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure tcPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define bits_AQ_PmaStandardDevicesInPackage_HHD_tcPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure tcPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define word_AQ_PmaStandardDevicesInPackage_HHD_tcPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure dteXsPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define AQ_PmaStandardDevicesInPackage_HHD_dteXsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure dteXsPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define bits_AQ_PmaStandardDevicesInPackage_HHD_dteXsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure dteXsPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define word_AQ_PmaStandardDevicesInPackage_HHD_dteXsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_Present in AQ_PmaStandardDevicesInPackage_HHD */
#define AQ_PmaStandardDevicesInPackage_HHD_phyXS_Present 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_Present in AQ_PmaStandardDevicesInPackage_HHD */
#define bits_AQ_PmaStandardDevicesInPackage_HHD_phyXS_Present u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_Present in AQ_PmaStandardDevicesInPackage_HHD */
#define word_AQ_PmaStandardDevicesInPackage_HHD_phyXS_Present u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define AQ_PmaStandardDevicesInPackage_HHD_pcsPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define bits_AQ_PmaStandardDevicesInPackage_HHD_pcsPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define word_AQ_PmaStandardDevicesInPackage_HHD_pcsPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure wisPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define AQ_PmaStandardDevicesInPackage_HHD_wisPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure wisPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define bits_AQ_PmaStandardDevicesInPackage_HHD_wisPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure wisPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define word_AQ_PmaStandardDevicesInPackage_HHD_wisPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define AQ_PmaStandardDevicesInPackage_HHD_pmaPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define bits_AQ_PmaStandardDevicesInPackage_HHD_pmaPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define word_AQ_PmaStandardDevicesInPackage_HHD_pmaPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure clause_22RegistersPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define AQ_PmaStandardDevicesInPackage_HHD_clause_22RegistersPresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22RegistersPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define bits_AQ_PmaStandardDevicesInPackage_HHD_clause_22RegistersPresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure clause_22RegistersPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define word_AQ_PmaStandardDevicesInPackage_HHD_clause_22RegistersPresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_2Present in AQ_PmaStandardDevicesInPackage_HHD */
#define AQ_PmaStandardDevicesInPackage_HHD_vendorSpecificDevice_2Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_2Present in AQ_PmaStandardDevicesInPackage_HHD */
#define bits_AQ_PmaStandardDevicesInPackage_HHD_vendorSpecificDevice_2Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_2Present in AQ_PmaStandardDevicesInPackage_HHD */
#define word_AQ_PmaStandardDevicesInPackage_HHD_vendorSpecificDevice_2Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificDevice_1Present in AQ_PmaStandardDevicesInPackage_HHD */
#define AQ_PmaStandardDevicesInPackage_HHD_vendorSpecificDevice_1Present 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificDevice_1Present in AQ_PmaStandardDevicesInPackage_HHD */
#define bits_AQ_PmaStandardDevicesInPackage_HHD_vendorSpecificDevice_1Present u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificDevice_1Present in AQ_PmaStandardDevicesInPackage_HHD */
#define word_AQ_PmaStandardDevicesInPackage_HHD_vendorSpecificDevice_1Present u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure clause_22ExtensionPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define AQ_PmaStandardDevicesInPackage_HHD_clause_22ExtensionPresent 1
/*! \brief Preprocessor variable to relate field to bit position in structure clause_22ExtensionPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define bits_AQ_PmaStandardDevicesInPackage_HHD_clause_22ExtensionPresent u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure clause_22ExtensionPresent in AQ_PmaStandardDevicesInPackage_HHD */
#define word_AQ_PmaStandardDevicesInPackage_HHD_clause_22ExtensionPresent u1.word_1

/*! \brief Base register address of structure AQ_PmaStandardControl_2_HHD */
#define AQ_PmaStandardControl_2_HHD_baseRegisterAddress 0x0007
/*! \brief MMD address of structure AQ_PmaStandardControl_2_HHD */
#define AQ_PmaStandardControl_2_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure pmaDeviceType in AQ_PmaStandardControl_2_HHD */
#define AQ_PmaStandardControl_2_HHD_pmaDeviceType 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaDeviceType in AQ_PmaStandardControl_2_HHD */
#define bits_AQ_PmaStandardControl_2_HHD_pmaDeviceType u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaDeviceType in AQ_PmaStandardControl_2_HHD */
#define word_AQ_PmaStandardControl_2_HHD_pmaDeviceType u0.word_0

/*! \brief Base register address of structure AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_baseRegisterAddress 0x0008
/*! \brief MMD address of structure AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure devicePresent in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_devicePresent 0
/*! \brief Preprocessor variable to relate field to bit position in structure devicePresent in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_devicePresent u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure devicePresent in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_devicePresent u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitFaultLocationAbility in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_transmitFaultLocationAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure transmitFaultLocationAbility in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_transmitFaultLocationAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure transmitFaultLocationAbility in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_transmitFaultLocationAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure receiveFaultLocationAbility in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_receiveFaultLocationAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure receiveFaultLocationAbility in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_receiveFaultLocationAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure receiveFaultLocationAbility in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_receiveFaultLocationAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitFault in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_transmitFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure transmitFault in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_transmitFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure transmitFault in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_transmitFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure receiveFault in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_receiveFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure receiveFault in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_receiveFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure receiveFault in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_receiveFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extendedAbilities in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_extendedAbilities 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedAbilities in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_extendedAbilities u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedAbilities in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_extendedAbilities u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmdTransmitDisableAbility in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_pmdTransmitDisableAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmdTransmitDisableAbility in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_pmdTransmitDisableAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmdTransmitDisableAbility in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_pmdTransmitDisableAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma10GBaseSR_Capable in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_pma10GBaseSR_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10GBaseSR_Capable in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_pma10GBaseSR_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10GBaseSR_Capable in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_pma10GBaseSR_Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma10GBaseLR_Capable in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_pma10GBaseLR_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10GBaseLR_Capable in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_pma10GBaseLR_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10GBaseLR_Capable in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_pma10GBaseLR_Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma10GBaseER_Capable in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_pma10GBaseER_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10GBaseER_Capable in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_pma10GBaseER_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10GBaseER_Capable in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_pma10GBaseER_Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma10G_base_lx4Capable in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_pma10G_base_lx4Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10G_base_lx4Capable in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_pma10G_base_lx4Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10G_base_lx4Capable in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_pma10G_base_lx4Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma10GBaseSW_Capable in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_pma10GBaseSW_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10GBaseSW_Capable in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_pma10GBaseSW_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10GBaseSW_Capable in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_pma10GBaseSW_Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma10GBaseLW_Capable in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_pma10GBaseLW_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10GBaseLW_Capable in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_pma10GBaseLW_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10GBaseLW_Capable in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_pma10GBaseLW_Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma10GBaseEW_Capable in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_pma10GBaseEW_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10GBaseEW_Capable in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_pma10GBaseEW_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10GBaseEW_Capable in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_pma10GBaseEW_Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaLoopbackAbility in AQ_PmaStandardStatus_2_HHD */
#define AQ_PmaStandardStatus_2_HHD_pmaLoopbackAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaLoopbackAbility in AQ_PmaStandardStatus_2_HHD */
#define bits_AQ_PmaStandardStatus_2_HHD_pmaLoopbackAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaLoopbackAbility in AQ_PmaStandardStatus_2_HHD */
#define word_AQ_PmaStandardStatus_2_HHD_pmaLoopbackAbility u0.word_0

/*! \brief Base register address of structure AQ_PmdStandardTransmitDisableControl_HHD */
#define AQ_PmdStandardTransmitDisableControl_HHD_baseRegisterAddress 0x0009
/*! \brief MMD address of structure AQ_PmdStandardTransmitDisableControl_HHD */
#define AQ_PmdStandardTransmitDisableControl_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure pmdChannel_3TransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define AQ_PmdStandardTransmitDisableControl_HHD_pmdChannel_3TransmitDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmdChannel_3TransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define bits_AQ_PmdStandardTransmitDisableControl_HHD_pmdChannel_3TransmitDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmdChannel_3TransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define word_AQ_PmdStandardTransmitDisableControl_HHD_pmdChannel_3TransmitDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmdChannel_2TransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define AQ_PmdStandardTransmitDisableControl_HHD_pmdChannel_2TransmitDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmdChannel_2TransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define bits_AQ_PmdStandardTransmitDisableControl_HHD_pmdChannel_2TransmitDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmdChannel_2TransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define word_AQ_PmdStandardTransmitDisableControl_HHD_pmdChannel_2TransmitDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmdChannel_1TransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define AQ_PmdStandardTransmitDisableControl_HHD_pmdChannel_1TransmitDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmdChannel_1TransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define bits_AQ_PmdStandardTransmitDisableControl_HHD_pmdChannel_1TransmitDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmdChannel_1TransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define word_AQ_PmdStandardTransmitDisableControl_HHD_pmdChannel_1TransmitDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmdChannel_0TransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define AQ_PmdStandardTransmitDisableControl_HHD_pmdChannel_0TransmitDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmdChannel_0TransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define bits_AQ_PmdStandardTransmitDisableControl_HHD_pmdChannel_0TransmitDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmdChannel_0TransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define word_AQ_PmdStandardTransmitDisableControl_HHD_pmdChannel_0TransmitDisable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmdGlobalTransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define AQ_PmdStandardTransmitDisableControl_HHD_pmdGlobalTransmitDisable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmdGlobalTransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define bits_AQ_PmdStandardTransmitDisableControl_HHD_pmdGlobalTransmitDisable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmdGlobalTransmitDisable in AQ_PmdStandardTransmitDisableControl_HHD */
#define word_AQ_PmdStandardTransmitDisableControl_HHD_pmdGlobalTransmitDisable u0.word_0

/*! \brief Base register address of structure AQ_PmdStandardSignalDetect_HHD */
#define AQ_PmdStandardSignalDetect_HHD_baseRegisterAddress 0x000A
/*! \brief MMD address of structure AQ_PmdStandardSignalDetect_HHD */
#define AQ_PmdStandardSignalDetect_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure pmdChannel_3SignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define AQ_PmdStandardSignalDetect_HHD_pmdChannel_3SignalDetect 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmdChannel_3SignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define bits_AQ_PmdStandardSignalDetect_HHD_pmdChannel_3SignalDetect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmdChannel_3SignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define word_AQ_PmdStandardSignalDetect_HHD_pmdChannel_3SignalDetect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmdChannel_2SignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define AQ_PmdStandardSignalDetect_HHD_pmdChannel_2SignalDetect 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmdChannel_2SignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define bits_AQ_PmdStandardSignalDetect_HHD_pmdChannel_2SignalDetect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmdChannel_2SignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define word_AQ_PmdStandardSignalDetect_HHD_pmdChannel_2SignalDetect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmdChannel_1SignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define AQ_PmdStandardSignalDetect_HHD_pmdChannel_1SignalDetect 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmdChannel_1SignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define bits_AQ_PmdStandardSignalDetect_HHD_pmdChannel_1SignalDetect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmdChannel_1SignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define word_AQ_PmdStandardSignalDetect_HHD_pmdChannel_1SignalDetect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmdChannel_0SignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define AQ_PmdStandardSignalDetect_HHD_pmdChannel_0SignalDetect 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmdChannel_0SignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define bits_AQ_PmdStandardSignalDetect_HHD_pmdChannel_0SignalDetect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmdChannel_0SignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define word_AQ_PmdStandardSignalDetect_HHD_pmdChannel_0SignalDetect u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmdGlobalSignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define AQ_PmdStandardSignalDetect_HHD_pmdGlobalSignalDetect 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmdGlobalSignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define bits_AQ_PmdStandardSignalDetect_HHD_pmdGlobalSignalDetect u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmdGlobalSignalDetect in AQ_PmdStandardSignalDetect_HHD */
#define word_AQ_PmdStandardSignalDetect_HHD_pmdGlobalSignalDetect u0.word_0

/*! \brief Base register address of structure AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_baseRegisterAddress 0x000B
/*! \brief MMD address of structure AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure pma10BaseT_Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10BaseT_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10BaseT_Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define bits_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10BaseT_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10BaseT_Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define word_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10BaseT_Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma_100base_txCapable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma_100base_txCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma_100base_txCapable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define bits_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma_100base_txCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma_100base_txCapable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define word_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma_100base_txCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma_1000base_kxCapable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma_1000base_kxCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma_1000base_kxCapable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define bits_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma_1000base_kxCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma_1000base_kxCapable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define word_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma_1000base_kxCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma1000BaseT_Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma1000BaseT_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma1000BaseT_Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define bits_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma1000BaseT_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma1000BaseT_Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define word_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma1000BaseT_Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma10GBaseK_rCapable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseK_rCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10GBaseK_rCapable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define bits_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseK_rCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10GBaseK_rCapable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define word_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseK_rCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma10GBaseK_x4Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseK_x4Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10GBaseK_x4Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define bits_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseK_x4Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10GBaseK_x4Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define word_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseK_x4Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma10GBaseT_Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseT_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10GBaseT_Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define bits_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseT_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10GBaseT_Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define word_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseT_Capable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma10GBaseLR_mCapable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseLR_mCapable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10GBaseLR_mCapable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define bits_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseLR_mCapable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10GBaseLR_mCapable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define word_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseLR_mCapable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pma10GBaseCX4_Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseCX4_Capable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pma10GBaseCX4_Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define bits_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseCX4_Capable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pma10GBaseCX4_Capable in AQ_PmdStandard10G_ExtendedAbilityRegister_HHD */
#define word_AQ_PmdStandard10G_ExtendedAbilityRegister_HHD_pma10GBaseCX4_Capable u0.word_0

/*! \brief Base register address of structure AQ_PmaStandardPackageIdentifier_HHD */
#define AQ_PmaStandardPackageIdentifier_HHD_baseRegisterAddress 0x000E
/*! \brief MMD address of structure AQ_PmaStandardPackageIdentifier_HHD */
#define AQ_PmaStandardPackageIdentifier_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure packageIdMSW in AQ_PmaStandardPackageIdentifier_HHD */
#define AQ_PmaStandardPackageIdentifier_HHD_packageIdMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdMSW in AQ_PmaStandardPackageIdentifier_HHD */
#define bits_AQ_PmaStandardPackageIdentifier_HHD_packageIdMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure packageIdMSW in AQ_PmaStandardPackageIdentifier_HHD */
#define word_AQ_PmaStandardPackageIdentifier_HHD_packageIdMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure packageIdLSW in AQ_PmaStandardPackageIdentifier_HHD */
#define AQ_PmaStandardPackageIdentifier_HHD_packageIdLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure packageIdLSW in AQ_PmaStandardPackageIdentifier_HHD */
#define bits_AQ_PmaStandardPackageIdentifier_HHD_packageIdLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure packageIdLSW in AQ_PmaStandardPackageIdentifier_HHD */
#define word_AQ_PmaStandardPackageIdentifier_HHD_packageIdLSW u1.word_1

/*! \brief Base register address of structure AQ_Pma10GBaseT_Status_HHD */
#define AQ_Pma10GBaseT_Status_HHD_baseRegisterAddress 0x0081
/*! \brief MMD address of structure AQ_Pma10GBaseT_Status_HHD */
#define AQ_Pma10GBaseT_Status_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerInformationValid in AQ_Pma10GBaseT_Status_HHD */
#define AQ_Pma10GBaseT_Status_HHD_linkPartnerInformationValid 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerInformationValid in AQ_Pma10GBaseT_Status_HHD */
#define bits_AQ_Pma10GBaseT_Status_HHD_linkPartnerInformationValid u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerInformationValid in AQ_Pma10GBaseT_Status_HHD */
#define word_AQ_Pma10GBaseT_Status_HHD_linkPartnerInformationValid u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD */
#define AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD_baseRegisterAddress 0x0082
/*! \brief MMD address of structure AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD */
#define AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure pairPolarity in AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD */
#define AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD_pairPolarity 0
/*! \brief Preprocessor variable to relate field to bit position in structure pairPolarity in AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD */
#define bits_AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD_pairPolarity u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pairPolarity in AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD */
#define word_AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD_pairPolarity u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mdi_Md_xConnectionState in AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD */
#define AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD_mdi_Md_xConnectionState 0
/*! \brief Preprocessor variable to relate field to bit position in structure mdi_Md_xConnectionState in AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD */
#define bits_AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD_mdi_Md_xConnectionState u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mdi_Md_xConnectionState in AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD */
#define word_AQ_Pma10GBaseT_PairSwapAndPolarityStatus_HHD_mdi_Md_xConnectionState u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD */
#define AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD_baseRegisterAddress 0x0083
/*! \brief MMD address of structure AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD */
#define AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure linkPartnerTxPowerBackoff in AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD */
#define AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD_linkPartnerTxPowerBackoff 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkPartnerTxPowerBackoff in AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD */
#define bits_AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD_linkPartnerTxPowerBackoff u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkPartnerTxPowerBackoff in AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD */
#define word_AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD_linkPartnerTxPowerBackoff u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure txPowerBackoff in AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD */
#define AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD_txPowerBackoff 0
/*! \brief Preprocessor variable to relate field to bit position in structure txPowerBackoff in AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD */
#define bits_AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD_txPowerBackoff u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure txPowerBackoff in AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD */
#define word_AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD_txPowerBackoff u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure shortReachMode in AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD */
#define AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD_shortReachMode 0
/*! \brief Preprocessor variable to relate field to bit position in structure shortReachMode in AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD */
#define bits_AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD_shortReachMode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure shortReachMode in AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD */
#define word_AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_HHD_shortReachMode u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_TestModes_HHD */
#define AQ_Pma10GBaseT_TestModes_HHD_baseRegisterAddress 0x0084
/*! \brief MMD address of structure AQ_Pma10GBaseT_TestModes_HHD */
#define AQ_Pma10GBaseT_TestModes_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure testModeControl in AQ_Pma10GBaseT_TestModes_HHD */
#define AQ_Pma10GBaseT_TestModes_HHD_testModeControl 0
/*! \brief Preprocessor variable to relate field to bit position in structure testModeControl in AQ_Pma10GBaseT_TestModes_HHD */
#define bits_AQ_Pma10GBaseT_TestModes_HHD_testModeControl u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure testModeControl in AQ_Pma10GBaseT_TestModes_HHD */
#define word_AQ_Pma10GBaseT_TestModes_HHD_testModeControl u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitterTestFrequencies in AQ_Pma10GBaseT_TestModes_HHD */
#define AQ_Pma10GBaseT_TestModes_HHD_transmitterTestFrequencies 0
/*! \brief Preprocessor variable to relate field to bit position in structure transmitterTestFrequencies in AQ_Pma10GBaseT_TestModes_HHD */
#define bits_AQ_Pma10GBaseT_TestModes_HHD_transmitterTestFrequencies u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure transmitterTestFrequencies in AQ_Pma10GBaseT_TestModes_HHD */
#define word_AQ_Pma10GBaseT_TestModes_HHD_transmitterTestFrequencies u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_SNR_OperatingMarginChannelA_HHD */
#define AQ_Pma10GBaseT_SNR_OperatingMarginChannelA_HHD_baseRegisterAddress 0x0085
/*! \brief MMD address of structure AQ_Pma10GBaseT_SNR_OperatingMarginChannelA_HHD */
#define AQ_Pma10GBaseT_SNR_OperatingMarginChannelA_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure channelAOperatingMargin in AQ_Pma10GBaseT_SNR_OperatingMarginChannelA_HHD */
#define AQ_Pma10GBaseT_SNR_OperatingMarginChannelA_HHD_channelAOperatingMargin 0
/*! \brief Preprocessor variable to relate field to bit position in structure channelAOperatingMargin in AQ_Pma10GBaseT_SNR_OperatingMarginChannelA_HHD */
#define bits_AQ_Pma10GBaseT_SNR_OperatingMarginChannelA_HHD_channelAOperatingMargin u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channelAOperatingMargin in AQ_Pma10GBaseT_SNR_OperatingMarginChannelA_HHD */
#define word_AQ_Pma10GBaseT_SNR_OperatingMarginChannelA_HHD_channelAOperatingMargin u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_SNR_OperatingMarginChannelB_HHD */
#define AQ_Pma10GBaseT_SNR_OperatingMarginChannelB_HHD_baseRegisterAddress 0x0086
/*! \brief MMD address of structure AQ_Pma10GBaseT_SNR_OperatingMarginChannelB_HHD */
#define AQ_Pma10GBaseT_SNR_OperatingMarginChannelB_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure channelBOperatingMargin in AQ_Pma10GBaseT_SNR_OperatingMarginChannelB_HHD */
#define AQ_Pma10GBaseT_SNR_OperatingMarginChannelB_HHD_channelBOperatingMargin 0
/*! \brief Preprocessor variable to relate field to bit position in structure channelBOperatingMargin in AQ_Pma10GBaseT_SNR_OperatingMarginChannelB_HHD */
#define bits_AQ_Pma10GBaseT_SNR_OperatingMarginChannelB_HHD_channelBOperatingMargin u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channelBOperatingMargin in AQ_Pma10GBaseT_SNR_OperatingMarginChannelB_HHD */
#define word_AQ_Pma10GBaseT_SNR_OperatingMarginChannelB_HHD_channelBOperatingMargin u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_SNR_OperatingMarginChannelC_HHD */
#define AQ_Pma10GBaseT_SNR_OperatingMarginChannelC_HHD_baseRegisterAddress 0x0087
/*! \brief MMD address of structure AQ_Pma10GBaseT_SNR_OperatingMarginChannelC_HHD */
#define AQ_Pma10GBaseT_SNR_OperatingMarginChannelC_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure channelCOperatingMargin in AQ_Pma10GBaseT_SNR_OperatingMarginChannelC_HHD */
#define AQ_Pma10GBaseT_SNR_OperatingMarginChannelC_HHD_channelCOperatingMargin 0
/*! \brief Preprocessor variable to relate field to bit position in structure channelCOperatingMargin in AQ_Pma10GBaseT_SNR_OperatingMarginChannelC_HHD */
#define bits_AQ_Pma10GBaseT_SNR_OperatingMarginChannelC_HHD_channelCOperatingMargin u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channelCOperatingMargin in AQ_Pma10GBaseT_SNR_OperatingMarginChannelC_HHD */
#define word_AQ_Pma10GBaseT_SNR_OperatingMarginChannelC_HHD_channelCOperatingMargin u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_SNR_OperatingMarginChannelD_HHD */
#define AQ_Pma10GBaseT_SNR_OperatingMarginChannelD_HHD_baseRegisterAddress 0x0088
/*! \brief MMD address of structure AQ_Pma10GBaseT_SNR_OperatingMarginChannelD_HHD */
#define AQ_Pma10GBaseT_SNR_OperatingMarginChannelD_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure channelDOperatingMargin in AQ_Pma10GBaseT_SNR_OperatingMarginChannelD_HHD */
#define AQ_Pma10GBaseT_SNR_OperatingMarginChannelD_HHD_channelDOperatingMargin 0
/*! \brief Preprocessor variable to relate field to bit position in structure channelDOperatingMargin in AQ_Pma10GBaseT_SNR_OperatingMarginChannelD_HHD */
#define bits_AQ_Pma10GBaseT_SNR_OperatingMarginChannelD_HHD_channelDOperatingMargin u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channelDOperatingMargin in AQ_Pma10GBaseT_SNR_OperatingMarginChannelD_HHD */
#define word_AQ_Pma10GBaseT_SNR_OperatingMarginChannelD_HHD_channelDOperatingMargin u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelA_HHD */
#define AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelA_HHD_baseRegisterAddress 0x0089
/*! \brief MMD address of structure AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelA_HHD */
#define AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelA_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure channelAMinimumOperatingMargin in AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelA_HHD */
#define AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelA_HHD_channelAMinimumOperatingMargin 0
/*! \brief Preprocessor variable to relate field to bit position in structure channelAMinimumOperatingMargin in AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelA_HHD */
#define bits_AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelA_HHD_channelAMinimumOperatingMargin u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channelAMinimumOperatingMargin in AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelA_HHD */
#define word_AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelA_HHD_channelAMinimumOperatingMargin u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelB_HHD */
#define AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelB_HHD_baseRegisterAddress 0x008A
/*! \brief MMD address of structure AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelB_HHD */
#define AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelB_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure channelBMinimumOperatingMargin in AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelB_HHD */
#define AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelB_HHD_channelBMinimumOperatingMargin 0
/*! \brief Preprocessor variable to relate field to bit position in structure channelBMinimumOperatingMargin in AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelB_HHD */
#define bits_AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelB_HHD_channelBMinimumOperatingMargin u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channelBMinimumOperatingMargin in AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelB_HHD */
#define word_AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelB_HHD_channelBMinimumOperatingMargin u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelC_HHD */
#define AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelC_HHD_baseRegisterAddress 0x008B
/*! \brief MMD address of structure AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelC_HHD */
#define AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelC_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure channelCMinimumOperatingMargin in AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelC_HHD */
#define AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelC_HHD_channelCMinimumOperatingMargin 0
/*! \brief Preprocessor variable to relate field to bit position in structure channelCMinimumOperatingMargin in AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelC_HHD */
#define bits_AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelC_HHD_channelCMinimumOperatingMargin u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channelCMinimumOperatingMargin in AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelC_HHD */
#define word_AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelC_HHD_channelCMinimumOperatingMargin u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelD_HHD */
#define AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelD_HHD_baseRegisterAddress 0x008C
/*! \brief MMD address of structure AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelD_HHD */
#define AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelD_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure channelDMinimumOperatingMargin in AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelD_HHD */
#define AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelD_HHD_channelDMinimumOperatingMargin 0
/*! \brief Preprocessor variable to relate field to bit position in structure channelDMinimumOperatingMargin in AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelD_HHD */
#define bits_AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelD_HHD_channelDMinimumOperatingMargin u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channelDMinimumOperatingMargin in AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelD_HHD */
#define word_AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelD_HHD_channelDMinimumOperatingMargin u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_ReceiveSignalPowerChannelA_HHD */
#define AQ_Pma10GBaseT_ReceiveSignalPowerChannelA_HHD_baseRegisterAddress 0x008D
/*! \brief MMD address of structure AQ_Pma10GBaseT_ReceiveSignalPowerChannelA_HHD */
#define AQ_Pma10GBaseT_ReceiveSignalPowerChannelA_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure channelAReceivedSignalPower in AQ_Pma10GBaseT_ReceiveSignalPowerChannelA_HHD */
#define AQ_Pma10GBaseT_ReceiveSignalPowerChannelA_HHD_channelAReceivedSignalPower 0
/*! \brief Preprocessor variable to relate field to bit position in structure channelAReceivedSignalPower in AQ_Pma10GBaseT_ReceiveSignalPowerChannelA_HHD */
#define bits_AQ_Pma10GBaseT_ReceiveSignalPowerChannelA_HHD_channelAReceivedSignalPower u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channelAReceivedSignalPower in AQ_Pma10GBaseT_ReceiveSignalPowerChannelA_HHD */
#define word_AQ_Pma10GBaseT_ReceiveSignalPowerChannelA_HHD_channelAReceivedSignalPower u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_ReceiveSignalPowerChannelB_HHD */
#define AQ_Pma10GBaseT_ReceiveSignalPowerChannelB_HHD_baseRegisterAddress 0x008E
/*! \brief MMD address of structure AQ_Pma10GBaseT_ReceiveSignalPowerChannelB_HHD */
#define AQ_Pma10GBaseT_ReceiveSignalPowerChannelB_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure channelBReceivedSignalPower in AQ_Pma10GBaseT_ReceiveSignalPowerChannelB_HHD */
#define AQ_Pma10GBaseT_ReceiveSignalPowerChannelB_HHD_channelBReceivedSignalPower 0
/*! \brief Preprocessor variable to relate field to bit position in structure channelBReceivedSignalPower in AQ_Pma10GBaseT_ReceiveSignalPowerChannelB_HHD */
#define bits_AQ_Pma10GBaseT_ReceiveSignalPowerChannelB_HHD_channelBReceivedSignalPower u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channelBReceivedSignalPower in AQ_Pma10GBaseT_ReceiveSignalPowerChannelB_HHD */
#define word_AQ_Pma10GBaseT_ReceiveSignalPowerChannelB_HHD_channelBReceivedSignalPower u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_ReceiveSignalPowerChannelC_HHD */
#define AQ_Pma10GBaseT_ReceiveSignalPowerChannelC_HHD_baseRegisterAddress 0x008F
/*! \brief MMD address of structure AQ_Pma10GBaseT_ReceiveSignalPowerChannelC_HHD */
#define AQ_Pma10GBaseT_ReceiveSignalPowerChannelC_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure channelCReceivedSignalPower in AQ_Pma10GBaseT_ReceiveSignalPowerChannelC_HHD */
#define AQ_Pma10GBaseT_ReceiveSignalPowerChannelC_HHD_channelCReceivedSignalPower 0
/*! \brief Preprocessor variable to relate field to bit position in structure channelCReceivedSignalPower in AQ_Pma10GBaseT_ReceiveSignalPowerChannelC_HHD */
#define bits_AQ_Pma10GBaseT_ReceiveSignalPowerChannelC_HHD_channelCReceivedSignalPower u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channelCReceivedSignalPower in AQ_Pma10GBaseT_ReceiveSignalPowerChannelC_HHD */
#define word_AQ_Pma10GBaseT_ReceiveSignalPowerChannelC_HHD_channelCReceivedSignalPower u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_ReceiveSignalPowerChannelD_HHD */
#define AQ_Pma10GBaseT_ReceiveSignalPowerChannelD_HHD_baseRegisterAddress 0x0090
/*! \brief MMD address of structure AQ_Pma10GBaseT_ReceiveSignalPowerChannelD_HHD */
#define AQ_Pma10GBaseT_ReceiveSignalPowerChannelD_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure channelDReceivedSignalPower in AQ_Pma10GBaseT_ReceiveSignalPowerChannelD_HHD */
#define AQ_Pma10GBaseT_ReceiveSignalPowerChannelD_HHD_channelDReceivedSignalPower 0
/*! \brief Preprocessor variable to relate field to bit position in structure channelDReceivedSignalPower in AQ_Pma10GBaseT_ReceiveSignalPowerChannelD_HHD */
#define bits_AQ_Pma10GBaseT_ReceiveSignalPowerChannelD_HHD_channelDReceivedSignalPower u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channelDReceivedSignalPower in AQ_Pma10GBaseT_ReceiveSignalPowerChannelD_HHD */
#define word_AQ_Pma10GBaseT_ReceiveSignalPowerChannelD_HHD_channelDReceivedSignalPower u0.word_0

/*! \brief Base register address of structure AQ_Pma10GBaseT_SkewDelay_HHD */
#define AQ_Pma10GBaseT_SkewDelay_HHD_baseRegisterAddress 0x0091
/*! \brief MMD address of structure AQ_Pma10GBaseT_SkewDelay_HHD */
#define AQ_Pma10GBaseT_SkewDelay_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure skewDelayB in AQ_Pma10GBaseT_SkewDelay_HHD */
#define AQ_Pma10GBaseT_SkewDelay_HHD_skewDelayB 0
/*! \brief Preprocessor variable to relate field to bit position in structure skewDelayB in AQ_Pma10GBaseT_SkewDelay_HHD */
#define bits_AQ_Pma10GBaseT_SkewDelay_HHD_skewDelayB u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure skewDelayB in AQ_Pma10GBaseT_SkewDelay_HHD */
#define word_AQ_Pma10GBaseT_SkewDelay_HHD_skewDelayB u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure skewDelayD in AQ_Pma10GBaseT_SkewDelay_HHD */
#define AQ_Pma10GBaseT_SkewDelay_HHD_skewDelayD 1
/*! \brief Preprocessor variable to relate field to bit position in structure skewDelayD in AQ_Pma10GBaseT_SkewDelay_HHD */
#define bits_AQ_Pma10GBaseT_SkewDelay_HHD_skewDelayD u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure skewDelayD in AQ_Pma10GBaseT_SkewDelay_HHD */
#define word_AQ_Pma10GBaseT_SkewDelay_HHD_skewDelayD u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure skewDelayC in AQ_Pma10GBaseT_SkewDelay_HHD */
#define AQ_Pma10GBaseT_SkewDelay_HHD_skewDelayC 1
/*! \brief Preprocessor variable to relate field to bit position in structure skewDelayC in AQ_Pma10GBaseT_SkewDelay_HHD */
#define bits_AQ_Pma10GBaseT_SkewDelay_HHD_skewDelayC u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure skewDelayC in AQ_Pma10GBaseT_SkewDelay_HHD */
#define word_AQ_Pma10GBaseT_SkewDelay_HHD_skewDelayC u1.word_1

/*! \brief Base register address of structure AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_baseRegisterAddress 0x0093
/*! \brief MMD address of structure AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure lpFastRetrainCount in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_lpFastRetrainCount 0
/*! \brief Preprocessor variable to relate field to bit position in structure lpFastRetrainCount in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define bits_AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_lpFastRetrainCount u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lpFastRetrainCount in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define word_AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_lpFastRetrainCount u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure ldFastRetrainCount in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_ldFastRetrainCount 0
/*! \brief Preprocessor variable to relate field to bit position in structure ldFastRetrainCount in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define bits_AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_ldFastRetrainCount u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure ldFastRetrainCount in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define word_AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_ldFastRetrainCount u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure fastRetrainAbility in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_fastRetrainAbility 0
/*! \brief Preprocessor variable to relate field to bit position in structure fastRetrainAbility in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define bits_AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_fastRetrainAbility u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure fastRetrainAbility in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define word_AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_fastRetrainAbility u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure fastRetrainNegotiated in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_fastRetrainNegotiated 0
/*! \brief Preprocessor variable to relate field to bit position in structure fastRetrainNegotiated in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define bits_AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_fastRetrainNegotiated u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure fastRetrainNegotiated in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define word_AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_fastRetrainNegotiated u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure fastRetrainSignalType in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_fastRetrainSignalType 0
/*! \brief Preprocessor variable to relate field to bit position in structure fastRetrainSignalType in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define bits_AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_fastRetrainSignalType u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure fastRetrainSignalType in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define word_AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_fastRetrainSignalType u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure fastRetrainEnable in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_fastRetrainEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure fastRetrainEnable in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define bits_AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_fastRetrainEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure fastRetrainEnable in AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD */
#define word_AQ_Pma10GBaseT_FastRetrainStatusAndControl_HHD_fastRetrainEnable u0.word_0

/*! \brief Base register address of structure AQ_Phy10GBaseK_rPmdStatus_HHD */
#define AQ_Phy10GBaseK_rPmdStatus_HHD_baseRegisterAddress 0x0097
/*! \brief MMD address of structure AQ_Phy10GBaseK_rPmdStatus_HHD */
#define AQ_Phy10GBaseK_rPmdStatus_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure trainingFailure in AQ_Phy10GBaseK_rPmdStatus_HHD */
#define AQ_Phy10GBaseK_rPmdStatus_HHD_trainingFailure 0
/*! \brief Preprocessor variable to relate field to bit position in structure trainingFailure in AQ_Phy10GBaseK_rPmdStatus_HHD */
#define bits_AQ_Phy10GBaseK_rPmdStatus_HHD_trainingFailure u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure trainingFailure in AQ_Phy10GBaseK_rPmdStatus_HHD */
#define word_AQ_Phy10GBaseK_rPmdStatus_HHD_trainingFailure u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure start_upProtocolStatus in AQ_Phy10GBaseK_rPmdStatus_HHD */
#define AQ_Phy10GBaseK_rPmdStatus_HHD_start_upProtocolStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure start_upProtocolStatus in AQ_Phy10GBaseK_rPmdStatus_HHD */
#define bits_AQ_Phy10GBaseK_rPmdStatus_HHD_start_upProtocolStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure start_upProtocolStatus in AQ_Phy10GBaseK_rPmdStatus_HHD */
#define word_AQ_Phy10GBaseK_rPmdStatus_HHD_start_upProtocolStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure frameLock in AQ_Phy10GBaseK_rPmdStatus_HHD */
#define AQ_Phy10GBaseK_rPmdStatus_HHD_frameLock 0
/*! \brief Preprocessor variable to relate field to bit position in structure frameLock in AQ_Phy10GBaseK_rPmdStatus_HHD */
#define bits_AQ_Phy10GBaseK_rPmdStatus_HHD_frameLock u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure frameLock in AQ_Phy10GBaseK_rPmdStatus_HHD */
#define word_AQ_Phy10GBaseK_rPmdStatus_HHD_frameLock u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure receiverStatus in AQ_Phy10GBaseK_rPmdStatus_HHD */
#define AQ_Phy10GBaseK_rPmdStatus_HHD_receiverStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure receiverStatus in AQ_Phy10GBaseK_rPmdStatus_HHD */
#define bits_AQ_Phy10GBaseK_rPmdStatus_HHD_receiverStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure receiverStatus in AQ_Phy10GBaseK_rPmdStatus_HHD */
#define word_AQ_Phy10GBaseK_rPmdStatus_HHD_receiverStatus u0.word_0

/*! \brief Base register address of structure AQ_TimesyncPmaCapability_HHD */
#define AQ_TimesyncPmaCapability_HHD_baseRegisterAddress 0x1800
/*! \brief MMD address of structure AQ_TimesyncPmaCapability_HHD */
#define AQ_TimesyncPmaCapability_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure timesyncTransmitPathDataDelay in AQ_TimesyncPmaCapability_HHD */
#define AQ_TimesyncPmaCapability_HHD_timesyncTransmitPathDataDelay 0
/*! \brief Preprocessor variable to relate field to bit position in structure timesyncTransmitPathDataDelay in AQ_TimesyncPmaCapability_HHD */
#define bits_AQ_TimesyncPmaCapability_HHD_timesyncTransmitPathDataDelay u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure timesyncTransmitPathDataDelay in AQ_TimesyncPmaCapability_HHD */
#define word_AQ_TimesyncPmaCapability_HHD_timesyncTransmitPathDataDelay u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure timesyncReceivePathDataDelay in AQ_TimesyncPmaCapability_HHD */
#define AQ_TimesyncPmaCapability_HHD_timesyncReceivePathDataDelay 0
/*! \brief Preprocessor variable to relate field to bit position in structure timesyncReceivePathDataDelay in AQ_TimesyncPmaCapability_HHD */
#define bits_AQ_TimesyncPmaCapability_HHD_timesyncReceivePathDataDelay u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure timesyncReceivePathDataDelay in AQ_TimesyncPmaCapability_HHD */
#define word_AQ_TimesyncPmaCapability_HHD_timesyncReceivePathDataDelay u0.word_0

/*! \brief Base register address of structure AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define AQ_TimesyncPmaTransmitPathDataDelay_HHD_baseRegisterAddress 0x1801
/*! \brief MMD address of structure AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define AQ_TimesyncPmaTransmitPathDataDelay_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure maximumPmaTransmitPathDataDelayLSW in AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define AQ_TimesyncPmaTransmitPathDataDelay_HHD_maximumPmaTransmitPathDataDelayLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure maximumPmaTransmitPathDataDelayLSW in AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define bits_AQ_TimesyncPmaTransmitPathDataDelay_HHD_maximumPmaTransmitPathDataDelayLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure maximumPmaTransmitPathDataDelayLSW in AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define word_AQ_TimesyncPmaTransmitPathDataDelay_HHD_maximumPmaTransmitPathDataDelayLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure maximumPmaTransmitPathDataDelayMSW in AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define AQ_TimesyncPmaTransmitPathDataDelay_HHD_maximumPmaTransmitPathDataDelayMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure maximumPmaTransmitPathDataDelayMSW in AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define bits_AQ_TimesyncPmaTransmitPathDataDelay_HHD_maximumPmaTransmitPathDataDelayMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure maximumPmaTransmitPathDataDelayMSW in AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define word_AQ_TimesyncPmaTransmitPathDataDelay_HHD_maximumPmaTransmitPathDataDelayMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure minimumPmaTransmitPathDataDelayLSW in AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define AQ_TimesyncPmaTransmitPathDataDelay_HHD_minimumPmaTransmitPathDataDelayLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure minimumPmaTransmitPathDataDelayLSW in AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define bits_AQ_TimesyncPmaTransmitPathDataDelay_HHD_minimumPmaTransmitPathDataDelayLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure minimumPmaTransmitPathDataDelayLSW in AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define word_AQ_TimesyncPmaTransmitPathDataDelay_HHD_minimumPmaTransmitPathDataDelayLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure minimumPmaTransmitPathDataDelayMSW in AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define AQ_TimesyncPmaTransmitPathDataDelay_HHD_minimumPmaTransmitPathDataDelayMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure minimumPmaTransmitPathDataDelayMSW in AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define bits_AQ_TimesyncPmaTransmitPathDataDelay_HHD_minimumPmaTransmitPathDataDelayMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure minimumPmaTransmitPathDataDelayMSW in AQ_TimesyncPmaTransmitPathDataDelay_HHD */
#define word_AQ_TimesyncPmaTransmitPathDataDelay_HHD_minimumPmaTransmitPathDataDelayMSW u3.word_3

/*! \brief Base register address of structure AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define AQ_TimesyncPmaReceivePathDataDelay_HHD_baseRegisterAddress 0x1805
/*! \brief MMD address of structure AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define AQ_TimesyncPmaReceivePathDataDelay_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure maximumPmaReceivePathDataDelayLSW in AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define AQ_TimesyncPmaReceivePathDataDelay_HHD_maximumPmaReceivePathDataDelayLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure maximumPmaReceivePathDataDelayLSW in AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define bits_AQ_TimesyncPmaReceivePathDataDelay_HHD_maximumPmaReceivePathDataDelayLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure maximumPmaReceivePathDataDelayLSW in AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define word_AQ_TimesyncPmaReceivePathDataDelay_HHD_maximumPmaReceivePathDataDelayLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure maximumPmaReceivePathDataDelayMSW in AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define AQ_TimesyncPmaReceivePathDataDelay_HHD_maximumPmaReceivePathDataDelayMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure maximumPmaReceivePathDataDelayMSW in AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define bits_AQ_TimesyncPmaReceivePathDataDelay_HHD_maximumPmaReceivePathDataDelayMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure maximumPmaReceivePathDataDelayMSW in AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define word_AQ_TimesyncPmaReceivePathDataDelay_HHD_maximumPmaReceivePathDataDelayMSW u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure minimumPmaReceivePathDataDelayLSW in AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define AQ_TimesyncPmaReceivePathDataDelay_HHD_minimumPmaReceivePathDataDelayLSW 2
/*! \brief Preprocessor variable to relate field to bit position in structure minimumPmaReceivePathDataDelayLSW in AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define bits_AQ_TimesyncPmaReceivePathDataDelay_HHD_minimumPmaReceivePathDataDelayLSW u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure minimumPmaReceivePathDataDelayLSW in AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define word_AQ_TimesyncPmaReceivePathDataDelay_HHD_minimumPmaReceivePathDataDelayLSW u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure minimumPmaReceivePathDataDelayMSW in AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define AQ_TimesyncPmaReceivePathDataDelay_HHD_minimumPmaReceivePathDataDelayMSW 3
/*! \brief Preprocessor variable to relate field to bit position in structure minimumPmaReceivePathDataDelayMSW in AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define bits_AQ_TimesyncPmaReceivePathDataDelay_HHD_minimumPmaReceivePathDataDelayMSW u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure minimumPmaReceivePathDataDelayMSW in AQ_TimesyncPmaReceivePathDataDelay_HHD */
#define word_AQ_TimesyncPmaReceivePathDataDelay_HHD_minimumPmaReceivePathDataDelayMSW u3.word_3

/*! \brief Base register address of structure AQ_XenpakControl_HHD */
#define AQ_XenpakControl_HHD_baseRegisterAddress 0x8000
/*! \brief MMD address of structure AQ_XenpakControl_HHD */
#define AQ_XenpakControl_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecific in AQ_XenpakControl_HHD */
#define AQ_XenpakControl_HHD_vendorSpecific 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecific in AQ_XenpakControl_HHD */
#define bits_AQ_XenpakControl_HHD_vendorSpecific u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecific in AQ_XenpakControl_HHD */
#define word_AQ_XenpakControl_HHD_vendorSpecific u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure command in AQ_XenpakControl_HHD */
#define AQ_XenpakControl_HHD_command 0
/*! \brief Preprocessor variable to relate field to bit position in structure command in AQ_XenpakControl_HHD */
#define bits_AQ_XenpakControl_HHD_command u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure command in AQ_XenpakControl_HHD */
#define word_AQ_XenpakControl_HHD_command u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure commandStatus in AQ_XenpakControl_HHD */
#define AQ_XenpakControl_HHD_commandStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure commandStatus in AQ_XenpakControl_HHD */
#define bits_AQ_XenpakControl_HHD_commandStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure commandStatus in AQ_XenpakControl_HHD */
#define word_AQ_XenpakControl_HHD_commandStatus u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extendedCommands in AQ_XenpakControl_HHD */
#define AQ_XenpakControl_HHD_extendedCommands 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedCommands in AQ_XenpakControl_HHD */
#define bits_AQ_XenpakControl_HHD_extendedCommands u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedCommands in AQ_XenpakControl_HHD */
#define word_AQ_XenpakControl_HHD_extendedCommands u0.word_0

/*! \brief Base register address of structure AQ_XenpakHeader_XenpakMsaVersionSupported_HHD */
#define AQ_XenpakHeader_XenpakMsaVersionSupported_HHD_baseRegisterAddress 0x8007
/*! \brief MMD address of structure AQ_XenpakHeader_XenpakMsaVersionSupported_HHD */
#define AQ_XenpakHeader_XenpakMsaVersionSupported_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure version in AQ_XenpakHeader_XenpakMsaVersionSupported_HHD */
#define AQ_XenpakHeader_XenpakMsaVersionSupported_HHD_version 0
/*! \brief Preprocessor variable to relate field to bit position in structure version in AQ_XenpakHeader_XenpakMsaVersionSupported_HHD */
#define bits_AQ_XenpakHeader_XenpakMsaVersionSupported_HHD_version u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure version in AQ_XenpakHeader_XenpakMsaVersionSupported_HHD */
#define word_AQ_XenpakHeader_XenpakMsaVersionSupported_HHD_version u0.word_0

/*! \brief Base register address of structure AQ_XenpakHeader_NvrSize_HHD */
#define AQ_XenpakHeader_NvrSize_HHD_baseRegisterAddress 0x8008
/*! \brief MMD address of structure AQ_XenpakHeader_NvrSize_HHD */
#define AQ_XenpakHeader_NvrSize_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure nvrSizeMSW in AQ_XenpakHeader_NvrSize_HHD */
#define AQ_XenpakHeader_NvrSize_HHD_nvrSizeMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure nvrSizeMSW in AQ_XenpakHeader_NvrSize_HHD */
#define bits_AQ_XenpakHeader_NvrSize_HHD_nvrSizeMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure nvrSizeMSW in AQ_XenpakHeader_NvrSize_HHD */
#define word_AQ_XenpakHeader_NvrSize_HHD_nvrSizeMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure nvrSizeLSW in AQ_XenpakHeader_NvrSize_HHD */
#define AQ_XenpakHeader_NvrSize_HHD_nvrSizeLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure nvrSizeLSW in AQ_XenpakHeader_NvrSize_HHD */
#define bits_AQ_XenpakHeader_NvrSize_HHD_nvrSizeLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure nvrSizeLSW in AQ_XenpakHeader_NvrSize_HHD */
#define word_AQ_XenpakHeader_NvrSize_HHD_nvrSizeLSW u1.word_1

/*! \brief Base register address of structure AQ_XenpakHeader_MemoryUsed_HHD */
#define AQ_XenpakHeader_MemoryUsed_HHD_baseRegisterAddress 0x800A
/*! \brief MMD address of structure AQ_XenpakHeader_MemoryUsed_HHD */
#define AQ_XenpakHeader_MemoryUsed_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure memoryUsedMSW in AQ_XenpakHeader_MemoryUsed_HHD */
#define AQ_XenpakHeader_MemoryUsed_HHD_memoryUsedMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure memoryUsedMSW in AQ_XenpakHeader_MemoryUsed_HHD */
#define bits_AQ_XenpakHeader_MemoryUsed_HHD_memoryUsedMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure memoryUsedMSW in AQ_XenpakHeader_MemoryUsed_HHD */
#define word_AQ_XenpakHeader_MemoryUsed_HHD_memoryUsedMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure memoryUsedLSW in AQ_XenpakHeader_MemoryUsed_HHD */
#define AQ_XenpakHeader_MemoryUsed_HHD_memoryUsedLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure memoryUsedLSW in AQ_XenpakHeader_MemoryUsed_HHD */
#define bits_AQ_XenpakHeader_MemoryUsed_HHD_memoryUsedLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure memoryUsedLSW in AQ_XenpakHeader_MemoryUsed_HHD */
#define word_AQ_XenpakHeader_MemoryUsed_HHD_memoryUsedLSW u1.word_1

/*! \brief Base register address of structure AQ_XenpakHeader_BasicMemoryStartAddress_HHD */
#define AQ_XenpakHeader_BasicMemoryStartAddress_HHD_baseRegisterAddress 0x800C
/*! \brief MMD address of structure AQ_XenpakHeader_BasicMemoryStartAddress_HHD */
#define AQ_XenpakHeader_BasicMemoryStartAddress_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure basicMemoryOffset in AQ_XenpakHeader_BasicMemoryStartAddress_HHD */
#define AQ_XenpakHeader_BasicMemoryStartAddress_HHD_basicMemoryOffset 0
/*! \brief Preprocessor variable to relate field to bit position in structure basicMemoryOffset in AQ_XenpakHeader_BasicMemoryStartAddress_HHD */
#define bits_AQ_XenpakHeader_BasicMemoryStartAddress_HHD_basicMemoryOffset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure basicMemoryOffset in AQ_XenpakHeader_BasicMemoryStartAddress_HHD */
#define word_AQ_XenpakHeader_BasicMemoryStartAddress_HHD_basicMemoryOffset u0.word_0

/*! \brief Base register address of structure AQ_XenpakHeader_CustomerMemoryOffset_HHD */
#define AQ_XenpakHeader_CustomerMemoryOffset_HHD_baseRegisterAddress 0x800D
/*! \brief MMD address of structure AQ_XenpakHeader_CustomerMemoryOffset_HHD */
#define AQ_XenpakHeader_CustomerMemoryOffset_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure customerMemoryOffset in AQ_XenpakHeader_CustomerMemoryOffset_HHD */
#define AQ_XenpakHeader_CustomerMemoryOffset_HHD_customerMemoryOffset 0
/*! \brief Preprocessor variable to relate field to bit position in structure customerMemoryOffset in AQ_XenpakHeader_CustomerMemoryOffset_HHD */
#define bits_AQ_XenpakHeader_CustomerMemoryOffset_HHD_customerMemoryOffset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure customerMemoryOffset in AQ_XenpakHeader_CustomerMemoryOffset_HHD */
#define word_AQ_XenpakHeader_CustomerMemoryOffset_HHD_customerMemoryOffset u0.word_0

/*! \brief Base register address of structure AQ_XenpakHeader_VendorMemoryStartAddress_HHD */
#define AQ_XenpakHeader_VendorMemoryStartAddress_HHD_baseRegisterAddress 0x800E
/*! \brief MMD address of structure AQ_XenpakHeader_VendorMemoryStartAddress_HHD */
#define AQ_XenpakHeader_VendorMemoryStartAddress_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure vendorMemoryOffset in AQ_XenpakHeader_VendorMemoryStartAddress_HHD */
#define AQ_XenpakHeader_VendorMemoryStartAddress_HHD_vendorMemoryOffset 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorMemoryOffset in AQ_XenpakHeader_VendorMemoryStartAddress_HHD */
#define bits_AQ_XenpakHeader_VendorMemoryStartAddress_HHD_vendorMemoryOffset u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorMemoryOffset in AQ_XenpakHeader_VendorMemoryStartAddress_HHD */
#define word_AQ_XenpakHeader_VendorMemoryStartAddress_HHD_vendorMemoryOffset u0.word_0

/*! \brief Base register address of structure AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD */
#define AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD_baseRegisterAddress 0x800F
/*! \brief MMD address of structure AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD */
#define AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure extendedVendorOffsetLSW in AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD */
#define AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD_extendedVendorOffsetLSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure extendedVendorOffsetLSW in AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD */
#define bits_AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD_extendedVendorOffsetLSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure extendedVendorOffsetLSW in AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD */
#define word_AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD_extendedVendorOffsetLSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure extendedVendorOffsetMSW in AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD */
#define AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD_extendedVendorOffsetMSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure extendedVendorOffsetMSW in AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD */
#define bits_AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD_extendedVendorOffsetMSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure extendedVendorOffsetMSW in AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD */
#define word_AQ_XenpakHeader_ExtendedVendorMemoryOffset_HHD_extendedVendorOffsetMSW u1.word_1

/*! \brief Base register address of structure AQ_XenpakBasic_Reserved_0x11_HHD */
#define AQ_XenpakBasic_Reserved_0x11_HHD_baseRegisterAddress 0x8011
/*! \brief MMD address of structure AQ_XenpakBasic_Reserved_0x11_HHD */
#define AQ_XenpakBasic_Reserved_0x11_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x11 in AQ_XenpakBasic_Reserved_0x11_HHD */
#define AQ_XenpakBasic_Reserved_0x11_HHD_basicReserved_0x11 0
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x11 in AQ_XenpakBasic_Reserved_0x11_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x11_HHD_basicReserved_0x11 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x11 in AQ_XenpakBasic_Reserved_0x11_HHD */
#define word_AQ_XenpakBasic_Reserved_0x11_HHD_basicReserved_0x11 u0.word_0

/*! \brief Base register address of structure AQ_XenpakBasic_TransceiverType_HHD */
#define AQ_XenpakBasic_TransceiverType_HHD_baseRegisterAddress 0x8012
/*! \brief MMD address of structure AQ_XenpakBasic_TransceiverType_HHD */
#define AQ_XenpakBasic_TransceiverType_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure transceiverType in AQ_XenpakBasic_TransceiverType_HHD */
#define AQ_XenpakBasic_TransceiverType_HHD_transceiverType 0
/*! \brief Preprocessor variable to relate field to bit position in structure transceiverType in AQ_XenpakBasic_TransceiverType_HHD */
#define bits_AQ_XenpakBasic_TransceiverType_HHD_transceiverType u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure transceiverType in AQ_XenpakBasic_TransceiverType_HHD */
#define word_AQ_XenpakBasic_TransceiverType_HHD_transceiverType u0.word_0

/*! \brief Base register address of structure AQ_XenpakBasic_ConnectorType_HHD */
#define AQ_XenpakBasic_ConnectorType_HHD_baseRegisterAddress 0x8013
/*! \brief MMD address of structure AQ_XenpakBasic_ConnectorType_HHD */
#define AQ_XenpakBasic_ConnectorType_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure connectorType in AQ_XenpakBasic_ConnectorType_HHD */
#define AQ_XenpakBasic_ConnectorType_HHD_connectorType 0
/*! \brief Preprocessor variable to relate field to bit position in structure connectorType in AQ_XenpakBasic_ConnectorType_HHD */
#define bits_AQ_XenpakBasic_ConnectorType_HHD_connectorType u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure connectorType in AQ_XenpakBasic_ConnectorType_HHD */
#define word_AQ_XenpakBasic_ConnectorType_HHD_connectorType u0.word_0

/*! \brief Base register address of structure AQ_XenpakBasic_Encoding_HHD */
#define AQ_XenpakBasic_Encoding_HHD_baseRegisterAddress 0x8014
/*! \brief MMD address of structure AQ_XenpakBasic_Encoding_HHD */
#define AQ_XenpakBasic_Encoding_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure encoding in AQ_XenpakBasic_Encoding_HHD */
#define AQ_XenpakBasic_Encoding_HHD_encoding 0
/*! \brief Preprocessor variable to relate field to bit position in structure encoding in AQ_XenpakBasic_Encoding_HHD */
#define bits_AQ_XenpakBasic_Encoding_HHD_encoding u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure encoding in AQ_XenpakBasic_Encoding_HHD */
#define word_AQ_XenpakBasic_Encoding_HHD_encoding u0.word_0

/*! \brief Base register address of structure AQ_XenpakBasic_BitRate_HHD */
#define AQ_XenpakBasic_BitRate_HHD_baseRegisterAddress 0x8015
/*! \brief MMD address of structure AQ_XenpakBasic_BitRate_HHD */
#define AQ_XenpakBasic_BitRate_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure bitRateMSW in AQ_XenpakBasic_BitRate_HHD */
#define AQ_XenpakBasic_BitRate_HHD_bitRateMSW 0
/*! \brief Preprocessor variable to relate field to bit position in structure bitRateMSW in AQ_XenpakBasic_BitRate_HHD */
#define bits_AQ_XenpakBasic_BitRate_HHD_bitRateMSW u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure bitRateMSW in AQ_XenpakBasic_BitRate_HHD */
#define word_AQ_XenpakBasic_BitRate_HHD_bitRateMSW u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure bitRateLSW in AQ_XenpakBasic_BitRate_HHD */
#define AQ_XenpakBasic_BitRate_HHD_bitRateLSW 1
/*! \brief Preprocessor variable to relate field to bit position in structure bitRateLSW in AQ_XenpakBasic_BitRate_HHD */
#define bits_AQ_XenpakBasic_BitRate_HHD_bitRateLSW u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure bitRateLSW in AQ_XenpakBasic_BitRate_HHD */
#define word_AQ_XenpakBasic_BitRate_HHD_bitRateLSW u1.word_1

/*! \brief Base register address of structure AQ_XenpakBasic_Protocol_HHD */
#define AQ_XenpakBasic_Protocol_HHD_baseRegisterAddress 0x8017
/*! \brief MMD address of structure AQ_XenpakBasic_Protocol_HHD */
#define AQ_XenpakBasic_Protocol_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure protocol in AQ_XenpakBasic_Protocol_HHD */
#define AQ_XenpakBasic_Protocol_HHD_protocol 0
/*! \brief Preprocessor variable to relate field to bit position in structure protocol in AQ_XenpakBasic_Protocol_HHD */
#define bits_AQ_XenpakBasic_Protocol_HHD_protocol u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure protocol in AQ_XenpakBasic_Protocol_HHD */
#define word_AQ_XenpakBasic_Protocol_HHD_protocol u0.word_0

/*! \brief Base register address of structure AQ_XenpakBasic_StandardsComplianceCodes_HHD */
#define AQ_XenpakBasic_StandardsComplianceCodes_HHD_baseRegisterAddress 0x8018
/*! \brief MMD address of structure AQ_XenpakBasic_StandardsComplianceCodes_HHD */
#define AQ_XenpakBasic_StandardsComplianceCodes_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure standardCode in AQ_XenpakBasic_StandardsComplianceCodes_HHD */
#define AQ_XenpakBasic_StandardsComplianceCodes_HHD_standardCode 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardCode in AQ_XenpakBasic_StandardsComplianceCodes_HHD */
#define bits_AQ_XenpakBasic_StandardsComplianceCodes_HHD_standardCode u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardCode in AQ_XenpakBasic_StandardsComplianceCodes_HHD */
#define word_AQ_XenpakBasic_StandardsComplianceCodes_HHD_standardCode u0.word_0

/*! \brief Base register address of structure AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_baseRegisterAddress 0x8019
/*! \brief MMD address of structure AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x19 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x19 0
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x19 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x19 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x19 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x19 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x1a in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1a 1
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x1a in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1a u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x1a in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1a u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x1b in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1b 2
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x1b in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1b u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x1b in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1b u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x1c in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1c 3
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x1c in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1c u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x1c in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1c u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x1d in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1d 4
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x1d in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1d u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x1d in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1d u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x1e in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1e 5
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x1e in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1e u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x1e in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1e u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x1f in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1f 6
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x1f in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1f u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x1f in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x1f u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x20 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x20 7
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x20 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x20 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x20 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x20 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x21 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x21 8
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x21 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x21 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x21 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x21 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x22 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x22 9
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x22 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x22 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x22 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x22 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x23 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x23 10
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x23 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x23 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x23 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x23 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x24 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x24 11
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x24 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x24 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x24 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x24 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x25 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x25 12
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x25 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x25 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x25 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x25 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x26 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x26 13
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x26 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x26 u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x26 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x26 u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x27 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x27 14
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x27 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x27 u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x27 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x27 u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x28 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x28 15
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x28 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x28 u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x28 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x28 u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x29 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x29 16
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x29 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x29 u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x29 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x29 u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x2a in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2a 17
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x2a in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2a u17.bits_17
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x2a in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2a u17.word_17
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x2b in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2b 18
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x2b in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2b u18.bits_18
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x2b in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2b u18.word_18
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x2c in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2c 19
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x2c in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2c u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x2c in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2c u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x2d in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2d 20
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x2d in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2d u20.bits_20
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x2d in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2d u20.word_20
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x2e in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2e 21
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x2e in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2e u21.bits_21
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x2e in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2e u21.word_21
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x2f in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2f 22
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x2f in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2f u22.bits_22
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x2f in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x2f u22.word_22
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x30 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x30 23
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x30 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x30 u23.bits_23
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x30 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x30 u23.word_23
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x31 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x31 24
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x31 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x31 u24.bits_24
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x31 in AQ_XenpakBasic_Reserved_0x19_HHD */
#define word_AQ_XenpakBasic_Reserved_0x19_HHD_basicReserved_0x31 u24.word_24

/*! \brief Base register address of structure AQ_XenpakBasic_PackageIdentifier_HHD */
#define AQ_XenpakBasic_PackageIdentifier_HHD_baseRegisterAddress 0x8032
/*! \brief MMD address of structure AQ_XenpakBasic_PackageIdentifier_HHD */
#define AQ_XenpakBasic_PackageIdentifier_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure packageID_1 in AQ_XenpakBasic_PackageIdentifier_HHD */
#define AQ_XenpakBasic_PackageIdentifier_HHD_packageID_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure packageID_1 in AQ_XenpakBasic_PackageIdentifier_HHD */
#define bits_AQ_XenpakBasic_PackageIdentifier_HHD_packageID_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure packageID_1 in AQ_XenpakBasic_PackageIdentifier_HHD */
#define word_AQ_XenpakBasic_PackageIdentifier_HHD_packageID_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure packageID_2 in AQ_XenpakBasic_PackageIdentifier_HHD */
#define AQ_XenpakBasic_PackageIdentifier_HHD_packageID_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure packageID_2 in AQ_XenpakBasic_PackageIdentifier_HHD */
#define bits_AQ_XenpakBasic_PackageIdentifier_HHD_packageID_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure packageID_2 in AQ_XenpakBasic_PackageIdentifier_HHD */
#define word_AQ_XenpakBasic_PackageIdentifier_HHD_packageID_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure packageID_3 in AQ_XenpakBasic_PackageIdentifier_HHD */
#define AQ_XenpakBasic_PackageIdentifier_HHD_packageID_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure packageID_3 in AQ_XenpakBasic_PackageIdentifier_HHD */
#define bits_AQ_XenpakBasic_PackageIdentifier_HHD_packageID_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure packageID_3 in AQ_XenpakBasic_PackageIdentifier_HHD */
#define word_AQ_XenpakBasic_PackageIdentifier_HHD_packageID_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure packageID_4 in AQ_XenpakBasic_PackageIdentifier_HHD */
#define AQ_XenpakBasic_PackageIdentifier_HHD_packageID_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure packageID_4 in AQ_XenpakBasic_PackageIdentifier_HHD */
#define bits_AQ_XenpakBasic_PackageIdentifier_HHD_packageID_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure packageID_4 in AQ_XenpakBasic_PackageIdentifier_HHD */
#define word_AQ_XenpakBasic_PackageIdentifier_HHD_packageID_4 u3.word_3

/*! \brief Base register address of structure AQ_XenpakBasic_VendorIdentifier_HHD */
#define AQ_XenpakBasic_VendorIdentifier_HHD_baseRegisterAddress 0x8036
/*! \brief MMD address of structure AQ_XenpakBasic_VendorIdentifier_HHD */
#define AQ_XenpakBasic_VendorIdentifier_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure vendorID_1 in AQ_XenpakBasic_VendorIdentifier_HHD */
#define AQ_XenpakBasic_VendorIdentifier_HHD_vendorID_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorID_1 in AQ_XenpakBasic_VendorIdentifier_HHD */
#define bits_AQ_XenpakBasic_VendorIdentifier_HHD_vendorID_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorID_1 in AQ_XenpakBasic_VendorIdentifier_HHD */
#define word_AQ_XenpakBasic_VendorIdentifier_HHD_vendorID_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorID_2 in AQ_XenpakBasic_VendorIdentifier_HHD */
#define AQ_XenpakBasic_VendorIdentifier_HHD_vendorID_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorID_2 in AQ_XenpakBasic_VendorIdentifier_HHD */
#define bits_AQ_XenpakBasic_VendorIdentifier_HHD_vendorID_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorID_2 in AQ_XenpakBasic_VendorIdentifier_HHD */
#define word_AQ_XenpakBasic_VendorIdentifier_HHD_vendorID_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure vendorID_3 in AQ_XenpakBasic_VendorIdentifier_HHD */
#define AQ_XenpakBasic_VendorIdentifier_HHD_vendorID_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure vendorID_3 in AQ_XenpakBasic_VendorIdentifier_HHD */
#define bits_AQ_XenpakBasic_VendorIdentifier_HHD_vendorID_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure vendorID_3 in AQ_XenpakBasic_VendorIdentifier_HHD */
#define word_AQ_XenpakBasic_VendorIdentifier_HHD_vendorID_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure vendorID_4 in AQ_XenpakBasic_VendorIdentifier_HHD */
#define AQ_XenpakBasic_VendorIdentifier_HHD_vendorID_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure vendorID_4 in AQ_XenpakBasic_VendorIdentifier_HHD */
#define bits_AQ_XenpakBasic_VendorIdentifier_HHD_vendorID_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure vendorID_4 in AQ_XenpakBasic_VendorIdentifier_HHD */
#define word_AQ_XenpakBasic_VendorIdentifier_HHD_vendorID_4 u3.word_3

/*! \brief Base register address of structure AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_baseRegisterAddress 0x803A
/*! \brief MMD address of structure AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_1 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_1 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_1 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_2 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_2 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_2 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_3 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_3 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_3 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_4 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_4 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_4 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_5 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_5 4
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_5 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_5 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_5 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_5 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_6 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_6 5
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_6 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_6 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_6 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_6 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_7 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_7 6
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_7 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_7 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_7 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_7 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_8 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_8 7
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_8 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_8 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_8 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_8 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_9 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_9 8
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_9 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_9 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_9 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_9 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_10 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_10 9
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_10 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_10 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_10 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_10 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_11 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_11 10
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_11 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_11 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_11 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_11 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_12 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_12 11
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_12 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_12 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_12 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_12 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_13 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_13 12
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_13 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_13 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_13 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_13 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_14 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_14 13
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_14 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_14 u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_14 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_14 u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_15 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_15 14
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_15 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_15 u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_15 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_15 u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure vendorName_16 in AQ_XenpakBasic_VendorName_HHD */
#define AQ_XenpakBasic_VendorName_HHD_vendorName_16 15
/*! \brief Preprocessor variable to relate field to bit position in structure vendorName_16 in AQ_XenpakBasic_VendorName_HHD */
#define bits_AQ_XenpakBasic_VendorName_HHD_vendorName_16 u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure vendorName_16 in AQ_XenpakBasic_VendorName_HHD */
#define word_AQ_XenpakBasic_VendorName_HHD_vendorName_16 u15.word_15

/*! \brief Base register address of structure AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_baseRegisterAddress 0x804A
/*! \brief MMD address of structure AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_1 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_1 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_1 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_2 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_2 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_2 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_3 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_3 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_3 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_4 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_4 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_4 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_5 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_5 4
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_5 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_5 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_5 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_5 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_6 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_6 5
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_6 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_6 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_6 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_6 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_7 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_7 6
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_7 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_7 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_7 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_7 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_8 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_8 7
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_8 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_8 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_8 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_8 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_9 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_9 8
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_9 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_9 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_9 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_9 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_10 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_10 9
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_10 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_10 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_10 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_10 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_11 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_11 10
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_11 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_11 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_11 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_11 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_12 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_12 11
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_12 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_12 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_12 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_12 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_13 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_13 12
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_13 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_13 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_13 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_13 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_14 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_14 13
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_14 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_14 u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_14 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_14 u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_15 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_15 14
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_15 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_15 u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_15 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_15 u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure vendorPN_16 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_16 15
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPN_16 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_16 u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure vendorPN_16 in AQ_XenpakBasic_VendorPartNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartNumber_HHD_vendorPN_16 u15.word_15

/*! \brief Base register address of structure AQ_XenpakBasic_VendorPartRevisionNumber_HHD */
#define AQ_XenpakBasic_VendorPartRevisionNumber_HHD_baseRegisterAddress 0x805A
/*! \brief MMD address of structure AQ_XenpakBasic_VendorPartRevisionNumber_HHD */
#define AQ_XenpakBasic_VendorPartRevisionNumber_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure vendorPartRN_1 in AQ_XenpakBasic_VendorPartRevisionNumber_HHD */
#define AQ_XenpakBasic_VendorPartRevisionNumber_HHD_vendorPartRN_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPartRN_1 in AQ_XenpakBasic_VendorPartRevisionNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartRevisionNumber_HHD_vendorPartRN_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorPartRN_1 in AQ_XenpakBasic_VendorPartRevisionNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartRevisionNumber_HHD_vendorPartRN_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorPartRN_2 in AQ_XenpakBasic_VendorPartRevisionNumber_HHD */
#define AQ_XenpakBasic_VendorPartRevisionNumber_HHD_vendorPartRN_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorPartRN_2 in AQ_XenpakBasic_VendorPartRevisionNumber_HHD */
#define bits_AQ_XenpakBasic_VendorPartRevisionNumber_HHD_vendorPartRN_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorPartRN_2 in AQ_XenpakBasic_VendorPartRevisionNumber_HHD */
#define word_AQ_XenpakBasic_VendorPartRevisionNumber_HHD_vendorPartRN_2 u1.word_1

/*! \brief Base register address of structure AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_baseRegisterAddress 0x805C
/*! \brief MMD address of structure AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_1 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_1 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_1 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_2 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_2 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_2 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_3 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_3 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_3 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_4 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_4 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_4 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_5 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_5 4
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_5 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_5 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_5 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_5 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_6 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_6 5
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_6 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_6 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_6 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_6 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_7 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_7 6
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_7 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_7 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_7 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_7 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_8 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_8 7
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_8 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_8 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_8 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_8 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_9 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_9 8
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_9 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_9 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_9 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_9 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_10 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_10 9
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_10 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_10 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_10 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_10 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_11 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_11 10
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_11 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_11 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_11 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_11 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_12 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_12 11
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_12 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_12 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_12 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_12 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_13 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_13 12
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_13 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_13 u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_13 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_13 u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_14 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_14 13
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_14 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_14 u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_14 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_14 u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_15 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_15 14
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_15 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_15 u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_15 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_15 u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure vendorSN_16 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_16 15
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSN_16 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define bits_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_16 u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure vendorSN_16 in AQ_XenpakBasic_VendorSerialNumber_HHD */
#define word_AQ_XenpakBasic_VendorSerialNumber_HHD_vendorSN_16 u15.word_15

/*! \brief Base register address of structure AQ_XenpakBasic_VendorDateCode_HHD */
#define AQ_XenpakBasic_VendorDateCode_HHD_baseRegisterAddress 0x806C
/*! \brief MMD address of structure AQ_XenpakBasic_VendorDateCode_HHD */
#define AQ_XenpakBasic_VendorDateCode_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure year_1 in AQ_XenpakBasic_VendorDateCode_HHD */
#define AQ_XenpakBasic_VendorDateCode_HHD_year_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure year_1 in AQ_XenpakBasic_VendorDateCode_HHD */
#define bits_AQ_XenpakBasic_VendorDateCode_HHD_year_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure year_1 in AQ_XenpakBasic_VendorDateCode_HHD */
#define word_AQ_XenpakBasic_VendorDateCode_HHD_year_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure year_2 in AQ_XenpakBasic_VendorDateCode_HHD */
#define AQ_XenpakBasic_VendorDateCode_HHD_year_2 1
/*! \brief Preprocessor variable to relate field to bit position in structure year_2 in AQ_XenpakBasic_VendorDateCode_HHD */
#define bits_AQ_XenpakBasic_VendorDateCode_HHD_year_2 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure year_2 in AQ_XenpakBasic_VendorDateCode_HHD */
#define word_AQ_XenpakBasic_VendorDateCode_HHD_year_2 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure year_3 in AQ_XenpakBasic_VendorDateCode_HHD */
#define AQ_XenpakBasic_VendorDateCode_HHD_year_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure year_3 in AQ_XenpakBasic_VendorDateCode_HHD */
#define bits_AQ_XenpakBasic_VendorDateCode_HHD_year_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure year_3 in AQ_XenpakBasic_VendorDateCode_HHD */
#define word_AQ_XenpakBasic_VendorDateCode_HHD_year_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure year_4 in AQ_XenpakBasic_VendorDateCode_HHD */
#define AQ_XenpakBasic_VendorDateCode_HHD_year_4 3
/*! \brief Preprocessor variable to relate field to bit position in structure year_4 in AQ_XenpakBasic_VendorDateCode_HHD */
#define bits_AQ_XenpakBasic_VendorDateCode_HHD_year_4 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure year_4 in AQ_XenpakBasic_VendorDateCode_HHD */
#define word_AQ_XenpakBasic_VendorDateCode_HHD_year_4 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure month_1 in AQ_XenpakBasic_VendorDateCode_HHD */
#define AQ_XenpakBasic_VendorDateCode_HHD_month_1 4
/*! \brief Preprocessor variable to relate field to bit position in structure month_1 in AQ_XenpakBasic_VendorDateCode_HHD */
#define bits_AQ_XenpakBasic_VendorDateCode_HHD_month_1 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure month_1 in AQ_XenpakBasic_VendorDateCode_HHD */
#define word_AQ_XenpakBasic_VendorDateCode_HHD_month_1 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure month_2 in AQ_XenpakBasic_VendorDateCode_HHD */
#define AQ_XenpakBasic_VendorDateCode_HHD_month_2 5
/*! \brief Preprocessor variable to relate field to bit position in structure month_2 in AQ_XenpakBasic_VendorDateCode_HHD */
#define bits_AQ_XenpakBasic_VendorDateCode_HHD_month_2 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure month_2 in AQ_XenpakBasic_VendorDateCode_HHD */
#define word_AQ_XenpakBasic_VendorDateCode_HHD_month_2 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure day_1 in AQ_XenpakBasic_VendorDateCode_HHD */
#define AQ_XenpakBasic_VendorDateCode_HHD_day_1 6
/*! \brief Preprocessor variable to relate field to bit position in structure day_1 in AQ_XenpakBasic_VendorDateCode_HHD */
#define bits_AQ_XenpakBasic_VendorDateCode_HHD_day_1 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure day_1 in AQ_XenpakBasic_VendorDateCode_HHD */
#define word_AQ_XenpakBasic_VendorDateCode_HHD_day_1 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure day_2 in AQ_XenpakBasic_VendorDateCode_HHD */
#define AQ_XenpakBasic_VendorDateCode_HHD_day_2 7
/*! \brief Preprocessor variable to relate field to bit position in structure day_2 in AQ_XenpakBasic_VendorDateCode_HHD */
#define bits_AQ_XenpakBasic_VendorDateCode_HHD_day_2 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure day_2 in AQ_XenpakBasic_VendorDateCode_HHD */
#define word_AQ_XenpakBasic_VendorDateCode_HHD_day_2 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure lot_1 in AQ_XenpakBasic_VendorDateCode_HHD */
#define AQ_XenpakBasic_VendorDateCode_HHD_lot_1 8
/*! \brief Preprocessor variable to relate field to bit position in structure lot_1 in AQ_XenpakBasic_VendorDateCode_HHD */
#define bits_AQ_XenpakBasic_VendorDateCode_HHD_lot_1 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure lot_1 in AQ_XenpakBasic_VendorDateCode_HHD */
#define word_AQ_XenpakBasic_VendorDateCode_HHD_lot_1 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure lot_2 in AQ_XenpakBasic_VendorDateCode_HHD */
#define AQ_XenpakBasic_VendorDateCode_HHD_lot_2 9
/*! \brief Preprocessor variable to relate field to bit position in structure lot_2 in AQ_XenpakBasic_VendorDateCode_HHD */
#define bits_AQ_XenpakBasic_VendorDateCode_HHD_lot_2 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure lot_2 in AQ_XenpakBasic_VendorDateCode_HHD */
#define word_AQ_XenpakBasic_VendorDateCode_HHD_lot_2 u9.word_9

/*! \brief Base register address of structure AQ_XenpakBasic__5vLoading_HHD */
#define AQ_XenpakBasic__5vLoading_HHD_baseRegisterAddress 0x8076
/*! \brief MMD address of structure AQ_XenpakBasic__5vLoading_HHD */
#define AQ_XenpakBasic__5vLoading_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure _5vLoading in AQ_XenpakBasic__5vLoading_HHD */
#define AQ_XenpakBasic__5vLoading_HHD__5vLoading 0
/*! \brief Preprocessor variable to relate field to bit position in structure _5vLoading in AQ_XenpakBasic__5vLoading_HHD */
#define bits_AQ_XenpakBasic__5vLoading_HHD__5vLoading u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _5vLoading in AQ_XenpakBasic__5vLoading_HHD */
#define word_AQ_XenpakBasic__5vLoading_HHD__5vLoading u0.word_0

/*! \brief Base register address of structure AQ_XenpakBasic__3_3vLoading_HHD */
#define AQ_XenpakBasic__3_3vLoading_HHD_baseRegisterAddress 0x8077
/*! \brief MMD address of structure AQ_XenpakBasic__3_3vLoading_HHD */
#define AQ_XenpakBasic__3_3vLoading_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure _3_3vLoading in AQ_XenpakBasic__3_3vLoading_HHD */
#define AQ_XenpakBasic__3_3vLoading_HHD__3_3vLoading 0
/*! \brief Preprocessor variable to relate field to bit position in structure _3_3vLoading in AQ_XenpakBasic__3_3vLoading_HHD */
#define bits_AQ_XenpakBasic__3_3vLoading_HHD__3_3vLoading u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure _3_3vLoading in AQ_XenpakBasic__3_3vLoading_HHD */
#define word_AQ_XenpakBasic__3_3vLoading_HHD__3_3vLoading u0.word_0

/*! \brief Base register address of structure AQ_XenpakBasic_ApsLoading_HHD */
#define AQ_XenpakBasic_ApsLoading_HHD_baseRegisterAddress 0x8078
/*! \brief MMD address of structure AQ_XenpakBasic_ApsLoading_HHD */
#define AQ_XenpakBasic_ApsLoading_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure apsLoading in AQ_XenpakBasic_ApsLoading_HHD */
#define AQ_XenpakBasic_ApsLoading_HHD_apsLoading 0
/*! \brief Preprocessor variable to relate field to bit position in structure apsLoading in AQ_XenpakBasic_ApsLoading_HHD */
#define bits_AQ_XenpakBasic_ApsLoading_HHD_apsLoading u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure apsLoading in AQ_XenpakBasic_ApsLoading_HHD */
#define word_AQ_XenpakBasic_ApsLoading_HHD_apsLoading u0.word_0

/*! \brief Base register address of structure AQ_XenpakBasic_ApsVoltage_HHD */
#define AQ_XenpakBasic_ApsVoltage_HHD_baseRegisterAddress 0x8079
/*! \brief MMD address of structure AQ_XenpakBasic_ApsVoltage_HHD */
#define AQ_XenpakBasic_ApsVoltage_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure apsVoltage in AQ_XenpakBasic_ApsVoltage_HHD */
#define AQ_XenpakBasic_ApsVoltage_HHD_apsVoltage 0
/*! \brief Preprocessor variable to relate field to bit position in structure apsVoltage in AQ_XenpakBasic_ApsVoltage_HHD */
#define bits_AQ_XenpakBasic_ApsVoltage_HHD_apsVoltage u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure apsVoltage in AQ_XenpakBasic_ApsVoltage_HHD */
#define word_AQ_XenpakBasic_ApsVoltage_HHD_apsVoltage u0.word_0

/*! \brief Base register address of structure AQ_XenpakBasic_DomCapability_HHD */
#define AQ_XenpakBasic_DomCapability_HHD_baseRegisterAddress 0x807A
/*! \brief MMD address of structure AQ_XenpakBasic_DomCapability_HHD */
#define AQ_XenpakBasic_DomCapability_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure domControlCapability in AQ_XenpakBasic_DomCapability_HHD */
#define AQ_XenpakBasic_DomCapability_HHD_domControlCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure domControlCapability in AQ_XenpakBasic_DomCapability_HHD */
#define bits_AQ_XenpakBasic_DomCapability_HHD_domControlCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure domControlCapability in AQ_XenpakBasic_DomCapability_HHD */
#define word_AQ_XenpakBasic_DomCapability_HHD_domControlCapability u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure domCapability in AQ_XenpakBasic_DomCapability_HHD */
#define AQ_XenpakBasic_DomCapability_HHD_domCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure domCapability in AQ_XenpakBasic_DomCapability_HHD */
#define bits_AQ_XenpakBasic_DomCapability_HHD_domCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure domCapability in AQ_XenpakBasic_DomCapability_HHD */
#define word_AQ_XenpakBasic_DomCapability_HHD_domCapability u0.word_0

/*! \brief Base register address of structure AQ_XenpakBasic_Low_powerStartupCapability_HHD */
#define AQ_XenpakBasic_Low_powerStartupCapability_HHD_baseRegisterAddress 0x807B
/*! \brief MMD address of structure AQ_XenpakBasic_Low_powerStartupCapability_HHD */
#define AQ_XenpakBasic_Low_powerStartupCapability_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure lowPowerStart_upCapability in AQ_XenpakBasic_Low_powerStartupCapability_HHD */
#define AQ_XenpakBasic_Low_powerStartupCapability_HHD_lowPowerStart_upCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowPowerStart_upCapability in AQ_XenpakBasic_Low_powerStartupCapability_HHD */
#define bits_AQ_XenpakBasic_Low_powerStartupCapability_HHD_lowPowerStart_upCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowPowerStart_upCapability in AQ_XenpakBasic_Low_powerStartupCapability_HHD */
#define word_AQ_XenpakBasic_Low_powerStartupCapability_HHD_lowPowerStart_upCapability u0.word_0

/*! \brief Base register address of structure AQ_XenpakBasic_Reserved_0x7c_HHD */
#define AQ_XenpakBasic_Reserved_0x7c_HHD_baseRegisterAddress 0x807C
/*! \brief MMD address of structure AQ_XenpakBasic_Reserved_0x7c_HHD */
#define AQ_XenpakBasic_Reserved_0x7c_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure basicReserved_0x7c in AQ_XenpakBasic_Reserved_0x7c_HHD */
#define AQ_XenpakBasic_Reserved_0x7c_HHD_basicReserved_0x7c 0
/*! \brief Preprocessor variable to relate field to bit position in structure basicReserved_0x7c in AQ_XenpakBasic_Reserved_0x7c_HHD */
#define bits_AQ_XenpakBasic_Reserved_0x7c_HHD_basicReserved_0x7c u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure basicReserved_0x7c in AQ_XenpakBasic_Reserved_0x7c_HHD */
#define word_AQ_XenpakBasic_Reserved_0x7c_HHD_basicReserved_0x7c u0.word_0

/*! \brief Base register address of structure AQ_XenpakBasic_Checksum_HHD */
#define AQ_XenpakBasic_Checksum_HHD_baseRegisterAddress 0x807D
/*! \brief MMD address of structure AQ_XenpakBasic_Checksum_HHD */
#define AQ_XenpakBasic_Checksum_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure checksum in AQ_XenpakBasic_Checksum_HHD */
#define AQ_XenpakBasic_Checksum_HHD_checksum 0
/*! \brief Preprocessor variable to relate field to bit position in structure checksum in AQ_XenpakBasic_Checksum_HHD */
#define bits_AQ_XenpakBasic_Checksum_HHD_checksum u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure checksum in AQ_XenpakBasic_Checksum_HHD */
#define word_AQ_XenpakBasic_Checksum_HHD_checksum u0.word_0

/*! \brief Base register address of structure AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_baseRegisterAddress 0x807E
/*! \brief MMD address of structure AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x7e in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x7e 0
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x7e in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x7e u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x7e in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x7e u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x7f in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x7f 1
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x7f in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x7f u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x7f in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x7f u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x80 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x80 2
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x80 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x80 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x80 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x80 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x81 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x81 3
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x81 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x81 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x81 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x81 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x82 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x82 4
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x82 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x82 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x82 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x82 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x83 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x83 5
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x83 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x83 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x83 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x83 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x84 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x84 6
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x84 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x84 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x84 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x84 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x85 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x85 7
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x85 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x85 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x85 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x85 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x86 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x86 8
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x86 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x86 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x86 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x86 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x87 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x87 9
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x87 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x87 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x87 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x87 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x88 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x88 10
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x88 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x88 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x88 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x88 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x89 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x89 11
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x89 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x89 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x89 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x89 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x8a in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8a 12
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x8a in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8a u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x8a in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8a u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x8b in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8b 13
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x8b in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8b u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x8b in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8b u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x8c in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8c 14
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x8c in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8c u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x8c in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8c u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x8d in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8d 15
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x8d in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8d u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x8d in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8d u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x8e in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8e 16
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x8e in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8e u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x8e in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8e u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x8f in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8f 17
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x8f in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8f u17.bits_17
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x8f in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x8f u17.word_17
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x90 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x90 18
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x90 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x90 u18.bits_18
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x90 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x90 u18.word_18
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x91 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x91 19
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x91 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x91 u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x91 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x91 u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x92 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x92 20
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x92 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x92 u20.bits_20
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x92 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x92 u20.word_20
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x93 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x93 21
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x93 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x93 u21.bits_21
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x93 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x93 u21.word_21
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x94 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x94 22
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x94 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x94 u22.bits_22
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x94 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x94 u22.word_22
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x95 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x95 23
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x95 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x95 u23.bits_23
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x95 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x95 u23.word_23
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x96 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x96 24
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x96 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x96 u24.bits_24
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x96 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x96 u24.word_24
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x97 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x97 25
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x97 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x97 u25.bits_25
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x97 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x97 u25.word_25
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x98 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x98 26
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x98 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x98 u26.bits_26
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x98 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x98 u26.word_26
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x99 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x99 27
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x99 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x99 u27.bits_27
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x99 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x99 u27.word_27
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x9a in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9a 28
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x9a in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9a u28.bits_28
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x9a in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9a u28.word_28
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x9b in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9b 29
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x9b in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9b u29.bits_29
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x9b in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9b u29.word_29
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x9c in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9c 30
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x9c in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9c u30.bits_30
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x9c in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9c u30.word_30
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x9d in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9d 31
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x9d in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9d u31.bits_31
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x9d in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9d u31.word_31
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x9e in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9e 32
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x9e in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9e u32.bits_32
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x9e in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9e u32.word_32
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0x9f in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9f 33
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0x9f in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9f u33.bits_33
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0x9f in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0x9f u33.word_33
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xa0 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa0 34
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xa0 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa0 u34.bits_34
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xa0 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa0 u34.word_34
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xa1 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa1 35
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xa1 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa1 u35.bits_35
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xa1 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa1 u35.word_35
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xa2 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa2 36
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xa2 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa2 u36.bits_36
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xa2 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa2 u36.word_36
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xa3 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa3 37
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xa3 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa3 u37.bits_37
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xa3 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa3 u37.word_37
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xa4 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa4 38
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xa4 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa4 u38.bits_38
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xa4 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa4 u38.word_38
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xa5 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa5 39
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xa5 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa5 u39.bits_39
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xa5 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa5 u39.word_39
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xa6 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa6 40
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xa6 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa6 u40.bits_40
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xa6 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa6 u40.word_40
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xa7 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa7 41
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xa7 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa7 u41.bits_41
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xa7 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa7 u41.word_41
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xa8 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa8 42
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xa8 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa8 u42.bits_42
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xa8 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa8 u42.word_42
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xa9 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa9 43
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xa9 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa9 u43.bits_43
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xa9 in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xa9 u43.word_43
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xaa in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xaa 44
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xaa in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xaa u44.bits_44
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xaa in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xaa u44.word_44
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xab in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xab 45
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xab in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xab u45.bits_45
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xab in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xab u45.word_45
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xac in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xac 46
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xac in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xac u46.bits_46
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xac in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xac u46.word_46
/*! \brief Preprocessor variable to relate field to word number in structure customerReserved_0xad in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xad 47
/*! \brief Preprocessor variable to relate field to bit position in structure customerReserved_0xad in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define bits_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xad u47.bits_47
/*! \brief Preprocessor variable to relate field to word position in structure customerReserved_0xad in AQ_XenpakCustomer_Reserved_0x7e_HHD */
#define word_AQ_XenpakCustomer_Reserved_0x7e_HHD_customerReserved_0xad u47.word_47

/*! \brief Base register address of structure AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_baseRegisterAddress 0x80AE
/*! \brief MMD address of structure AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xae in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xae 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xae in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xae u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xae in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xae u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xaf in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xaf 1
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xaf in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xaf u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xaf in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xaf u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xbo in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbo 2
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xbo in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbo u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xbo in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbo u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xb1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb1 3
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xb1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb1 u3.bits_3
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xb1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb1 u3.word_3
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xb2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb2 4
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xb2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb2 u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xb2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb2 u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xb3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb3 5
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xb3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb3 u5.bits_5
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xb3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb3 u5.word_5
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xb4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb4 6
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xb4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb4 u6.bits_6
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xb4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb4 u6.word_6
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xb5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb5 7
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xb5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb5 u7.bits_7
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xb5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb5 u7.word_7
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xb6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb6 8
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xb6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb6 u8.bits_8
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xb6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb6 u8.word_8
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xb7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb7 9
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xb7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb7 u9.bits_9
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xb7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb7 u9.word_9
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xb8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb8 10
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xb8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb8 u10.bits_10
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xb8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb8 u10.word_10
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xb9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb9 11
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xb9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb9 u11.bits_11
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xb9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xb9 u11.word_11
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xba in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xba 12
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xba in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xba u12.bits_12
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xba in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xba u12.word_12
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xbb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbb 13
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xbb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbb u13.bits_13
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xbb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbb u13.word_13
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xbc in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbc 14
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xbc in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbc u14.bits_14
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xbc in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbc u14.word_14
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xbd in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbd 15
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xbd in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbd u15.bits_15
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xbd in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbd u15.word_15
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xbe in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbe 16
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xbe in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbe u16.bits_16
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xbe in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbe u16.word_16
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xbf in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbf 17
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xbf in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbf u17.bits_17
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xbf in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xbf u17.word_17
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xc0 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc0 18
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xc0 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc0 u18.bits_18
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xc0 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc0 u18.word_18
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xc1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc1 19
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xc1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc1 u19.bits_19
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xc1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc1 u19.word_19
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xc2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc2 20
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xc2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc2 u20.bits_20
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xc2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc2 u20.word_20
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xc3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc3 21
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xc3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc3 u21.bits_21
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xc3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc3 u21.word_21
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xc4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc4 22
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xc4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc4 u22.bits_22
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xc4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc4 u22.word_22
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xc5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc5 23
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xc5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc5 u23.bits_23
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xc5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc5 u23.word_23
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xc6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc6 24
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xc6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc6 u24.bits_24
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xc6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc6 u24.word_24
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xc7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc7 25
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xc7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc7 u25.bits_25
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xc7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc7 u25.word_25
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xc8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc8 26
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xc8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc8 u26.bits_26
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xc8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc8 u26.word_26
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xc9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc9 27
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xc9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc9 u27.bits_27
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xc9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xc9 u27.word_27
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xca in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xca 28
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xca in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xca u28.bits_28
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xca in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xca u28.word_28
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xcb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xcb 29
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xcb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xcb u29.bits_29
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xcb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xcb u29.word_29
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xcc in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xcc 30
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xcc in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xcc u30.bits_30
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xcc in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xcc u30.word_30
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xcd in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xcd 31
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xcd in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xcd u31.bits_31
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xcd in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xcd u31.word_31
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xce in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xce 32
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xce in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xce u32.bits_32
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xce in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xce u32.word_32
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xcf in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xcf 33
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xcf in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xcf u33.bits_33
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xcf in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xcf u33.word_33
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xd0 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd0 34
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xd0 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd0 u34.bits_34
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xd0 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd0 u34.word_34
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xd1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd1 35
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xd1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd1 u35.bits_35
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xd1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd1 u35.word_35
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xd2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd2 36
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xd2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd2 u36.bits_36
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xd2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd2 u36.word_36
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xd3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd3 37
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xd3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd3 u37.bits_37
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xd3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd3 u37.word_37
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xd4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd4 38
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xd4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd4 u38.bits_38
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xd4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd4 u38.word_38
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xd5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd5 39
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xd5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd5 u39.bits_39
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xd5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd5 u39.word_39
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xd6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd6 40
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xd6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd6 u40.bits_40
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xd6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd6 u40.word_40
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xd7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd7 41
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xd7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd7 u41.bits_41
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xd7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd7 u41.word_41
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xd8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd8 42
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xd8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd8 u42.bits_42
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xd8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd8 u42.word_42
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xd9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd9 43
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xd9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd9 u43.bits_43
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xd9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xd9 u43.word_43
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xda in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xda 44
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xda in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xda u44.bits_44
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xda in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xda u44.word_44
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xdb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xdb 45
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xdb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xdb u45.bits_45
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xdb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xdb u45.word_45
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xdc in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xdc 46
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xdc in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xdc u46.bits_46
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xdc in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xdc u46.word_46
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xdd in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xdd 47
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xdd in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xdd u47.bits_47
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xdd in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xdd u47.word_47
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xde in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xde 48
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xde in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xde u48.bits_48
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xde in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xde u48.word_48
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xdf in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xdf 49
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xdf in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xdf u49.bits_49
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xdf in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xdf u49.word_49
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xe0 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe0 50
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xe0 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe0 u50.bits_50
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xe0 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe0 u50.word_50
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xe1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe1 51
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xe1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe1 u51.bits_51
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xe1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe1 u51.word_51
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xe2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe2 52
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xe2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe2 u52.bits_52
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xe2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe2 u52.word_52
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xe3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe3 53
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xe3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe3 u53.bits_53
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xe3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe3 u53.word_53
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xe4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe4 54
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xe4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe4 u54.bits_54
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xe4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe4 u54.word_54
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xe5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe5 55
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xe5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe5 u55.bits_55
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xe5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe5 u55.word_55
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xe6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe6 56
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xe6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe6 u56.bits_56
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xe6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe6 u56.word_56
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xe7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe7 57
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xe7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe7 u57.bits_57
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xe7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe7 u57.word_57
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xe8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe8 58
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xe8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe8 u58.bits_58
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xe8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe8 u58.word_58
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xe9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe9 59
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xe9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe9 u59.bits_59
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xe9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xe9 u59.word_59
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xea in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xea 60
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xea in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xea u60.bits_60
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xea in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xea u60.word_60
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xeb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xeb 61
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xeb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xeb u61.bits_61
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xeb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xeb u61.word_61
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xec in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xec 62
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xec in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xec u62.bits_62
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xec in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xec u62.word_62
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xed in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xed 63
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xed in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xed u63.bits_63
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xed in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xed u63.word_63
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xee in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xee 64
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xee in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xee u64.bits_64
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xee in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xee u64.word_64
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xef in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xef 65
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xef in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xef u65.bits_65
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xef in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xef u65.word_65
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xf0 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf0 66
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xf0 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf0 u66.bits_66
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xf0 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf0 u66.word_66
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xf1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf1 67
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xf1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf1 u67.bits_67
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xf1 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf1 u67.word_67
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xf2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf2 68
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xf2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf2 u68.bits_68
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xf2 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf2 u68.word_68
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xf3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf3 69
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xf3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf3 u69.bits_69
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xf3 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf3 u69.word_69
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xf4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf4 70
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xf4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf4 u70.bits_70
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xf4 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf4 u70.word_70
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xf5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf5 71
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xf5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf5 u71.bits_71
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xf5 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf5 u71.word_71
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xf6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf6 72
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xf6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf6 u72.bits_72
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xf6 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf6 u72.word_72
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xf7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf7 73
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xf7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf7 u73.bits_73
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xf7 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf7 u73.word_73
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xf8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf8 74
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xf8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf8 u74.bits_74
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xf8 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf8 u74.word_74
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xf9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf9 75
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xf9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf9 u75.bits_75
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xf9 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xf9 u75.word_75
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xfa in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfa 76
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xfa in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfa u76.bits_76
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xfa in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfa u76.word_76
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xfb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfb 77
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xfb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfb u77.bits_77
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xfb in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfb u77.word_77
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xfc in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfc 78
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xfc in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfc u78.bits_78
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xfc in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfc u78.word_78
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xfd in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfd 79
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xfd in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfd u79.bits_79
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xfd in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfd u79.word_79
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xfe in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfe 80
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xfe in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfe u80.bits_80
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xfe in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xfe u80.word_80
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0xff in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xff 81
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0xff in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xff u81.bits_81
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0xff in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0xff u81.word_81
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0x100 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x100 82
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0x100 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x100 u82.bits_82
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0x100 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x100 u82.word_82
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0x101 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x101 83
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0x101 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x101 u83.bits_83
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0x101 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x101 u83.word_83
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0x102 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x102 84
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0x102 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x102 u84.bits_84
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0x102 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x102 u84.word_84
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0x103 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x103 85
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0x103 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x103 u85.bits_85
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0x103 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x103 u85.word_85
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0x104 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x104 86
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0x104 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x104 u86.bits_86
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0x104 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x104 u86.word_86
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0x105 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x105 87
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0x105 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x105 u87.bits_87
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0x105 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x105 u87.word_87
/*! \brief Preprocessor variable to relate field to word number in structure vendorReserved_0x106 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x106 88
/*! \brief Preprocessor variable to relate field to bit position in structure vendorReserved_0x106 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define bits_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x106 u88.bits_88
/*! \brief Preprocessor variable to relate field to word position in structure vendorReserved_0x106 in AQ_XenpakVendor_Reserved_0xae_HHD */
#define word_AQ_XenpakVendor_Reserved_0xae_HHD_vendorReserved_0x106 u88.word_88

/*! \brief Base register address of structure AQ_XenpakRxAlarm_Control_HHD */
#define AQ_XenpakRxAlarm_Control_HHD_baseRegisterAddress 0x9000
/*! \brief MMD address of structure AQ_XenpakRxAlarm_Control_HHD */
#define AQ_XenpakRxAlarm_Control_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure reserved_1 in AQ_XenpakRxAlarm_Control_HHD */
#define AQ_XenpakRxAlarm_Control_HHD_reserved_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_1 in AQ_XenpakRxAlarm_Control_HHD */
#define bits_AQ_XenpakRxAlarm_Control_HHD_reserved_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_1 in AQ_XenpakRxAlarm_Control_HHD */
#define word_AQ_XenpakRxAlarm_Control_HHD_reserved_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaReceiveFaultEnable in AQ_XenpakRxAlarm_Control_HHD */
#define AQ_XenpakRxAlarm_Control_HHD_pmaReceiveFaultEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaReceiveFaultEnable in AQ_XenpakRxAlarm_Control_HHD */
#define bits_AQ_XenpakRxAlarm_Control_HHD_pmaReceiveFaultEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaReceiveFaultEnable in AQ_XenpakRxAlarm_Control_HHD */
#define word_AQ_XenpakRxAlarm_Control_HHD_pmaReceiveFaultEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsReceiveFaultEnable in AQ_XenpakRxAlarm_Control_HHD */
#define AQ_XenpakRxAlarm_Control_HHD_pcsReceiveFaultEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsReceiveFaultEnable in AQ_XenpakRxAlarm_Control_HHD */
#define bits_AQ_XenpakRxAlarm_Control_HHD_pcsReceiveFaultEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsReceiveFaultEnable in AQ_XenpakRxAlarm_Control_HHD */
#define word_AQ_XenpakRxAlarm_Control_HHD_pcsReceiveFaultEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_ReceiveFaultEnable in AQ_XenpakRxAlarm_Control_HHD */
#define AQ_XenpakRxAlarm_Control_HHD_phyXS_ReceiveFaultEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_ReceiveFaultEnable in AQ_XenpakRxAlarm_Control_HHD */
#define bits_AQ_XenpakRxAlarm_Control_HHD_phyXS_ReceiveFaultEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_ReceiveFaultEnable in AQ_XenpakRxAlarm_Control_HHD */
#define word_AQ_XenpakRxAlarm_Control_HHD_phyXS_ReceiveFaultEnable u0.word_0

/*! \brief Base register address of structure AQ_XenpakTxAlarm_Control_HHD */
#define AQ_XenpakTxAlarm_Control_HHD_baseRegisterAddress 0x9001
/*! \brief MMD address of structure AQ_XenpakTxAlarm_Control_HHD */
#define AQ_XenpakTxAlarm_Control_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure temperatureFaultEnable in AQ_XenpakTxAlarm_Control_HHD */
#define AQ_XenpakTxAlarm_Control_HHD_temperatureFaultEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure temperatureFaultEnable in AQ_XenpakTxAlarm_Control_HHD */
#define bits_AQ_XenpakTxAlarm_Control_HHD_temperatureFaultEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure temperatureFaultEnable in AQ_XenpakTxAlarm_Control_HHD */
#define word_AQ_XenpakTxAlarm_Control_HHD_temperatureFaultEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_1 in AQ_XenpakTxAlarm_Control_HHD */
#define AQ_XenpakTxAlarm_Control_HHD_reserved_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_1 in AQ_XenpakTxAlarm_Control_HHD */
#define bits_AQ_XenpakTxAlarm_Control_HHD_reserved_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_1 in AQ_XenpakTxAlarm_Control_HHD */
#define word_AQ_XenpakTxAlarm_Control_HHD_reserved_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaTransmitFaultEnable in AQ_XenpakTxAlarm_Control_HHD */
#define AQ_XenpakTxAlarm_Control_HHD_pmaTransmitFaultEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaTransmitFaultEnable in AQ_XenpakTxAlarm_Control_HHD */
#define bits_AQ_XenpakTxAlarm_Control_HHD_pmaTransmitFaultEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaTransmitFaultEnable in AQ_XenpakTxAlarm_Control_HHD */
#define word_AQ_XenpakTxAlarm_Control_HHD_pmaTransmitFaultEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsTransmitFaultEnable in AQ_XenpakTxAlarm_Control_HHD */
#define AQ_XenpakTxAlarm_Control_HHD_pcsTransmitFaultEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTransmitFaultEnable in AQ_XenpakTxAlarm_Control_HHD */
#define bits_AQ_XenpakTxAlarm_Control_HHD_pcsTransmitFaultEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTransmitFaultEnable in AQ_XenpakTxAlarm_Control_HHD */
#define word_AQ_XenpakTxAlarm_Control_HHD_pcsTransmitFaultEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_TransmitFaultEnable in AQ_XenpakTxAlarm_Control_HHD */
#define AQ_XenpakTxAlarm_Control_HHD_phyXS_TransmitFaultEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_TransmitFaultEnable in AQ_XenpakTxAlarm_Control_HHD */
#define bits_AQ_XenpakTxAlarm_Control_HHD_phyXS_TransmitFaultEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_TransmitFaultEnable in AQ_XenpakTxAlarm_Control_HHD */
#define word_AQ_XenpakTxAlarm_Control_HHD_phyXS_TransmitFaultEnable u0.word_0

/*! \brief Base register address of structure AQ_XenpakLASI__Control_HHD */
#define AQ_XenpakLASI__Control_HHD_baseRegisterAddress 0x9002
/*! \brief MMD address of structure AQ_XenpakLASI__Control_HHD */
#define AQ_XenpakLASI__Control_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure rxAlarmEnable in AQ_XenpakLASI__Control_HHD */
#define AQ_XenpakLASI__Control_HHD_rxAlarmEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure rxAlarmEnable in AQ_XenpakLASI__Control_HHD */
#define bits_AQ_XenpakLASI__Control_HHD_rxAlarmEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rxAlarmEnable in AQ_XenpakLASI__Control_HHD */
#define word_AQ_XenpakLASI__Control_HHD_rxAlarmEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure txAlarmEnable in AQ_XenpakLASI__Control_HHD */
#define AQ_XenpakLASI__Control_HHD_txAlarmEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure txAlarmEnable in AQ_XenpakLASI__Control_HHD */
#define bits_AQ_XenpakLASI__Control_HHD_txAlarmEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure txAlarmEnable in AQ_XenpakLASI__Control_HHD */
#define word_AQ_XenpakLASI__Control_HHD_txAlarmEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkStatusAlarmEnable in AQ_XenpakLASI__Control_HHD */
#define AQ_XenpakLASI__Control_HHD_linkStatusAlarmEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkStatusAlarmEnable in AQ_XenpakLASI__Control_HHD */
#define bits_AQ_XenpakLASI__Control_HHD_linkStatusAlarmEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkStatusAlarmEnable in AQ_XenpakLASI__Control_HHD */
#define word_AQ_XenpakLASI__Control_HHD_linkStatusAlarmEnable u0.word_0

/*! \brief Base register address of structure AQ_XenpakRxAlarm_Status_HHD */
#define AQ_XenpakRxAlarm_Status_HHD_baseRegisterAddress 0x9003
/*! \brief MMD address of structure AQ_XenpakRxAlarm_Status_HHD */
#define AQ_XenpakRxAlarm_Status_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure reserved_1 in AQ_XenpakRxAlarm_Status_HHD */
#define AQ_XenpakRxAlarm_Status_HHD_reserved_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_1 in AQ_XenpakRxAlarm_Status_HHD */
#define bits_AQ_XenpakRxAlarm_Status_HHD_reserved_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_1 in AQ_XenpakRxAlarm_Status_HHD */
#define word_AQ_XenpakRxAlarm_Status_HHD_reserved_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaReceiveFault in AQ_XenpakRxAlarm_Status_HHD */
#define AQ_XenpakRxAlarm_Status_HHD_pmaReceiveFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaReceiveFault in AQ_XenpakRxAlarm_Status_HHD */
#define bits_AQ_XenpakRxAlarm_Status_HHD_pmaReceiveFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaReceiveFault in AQ_XenpakRxAlarm_Status_HHD */
#define word_AQ_XenpakRxAlarm_Status_HHD_pmaReceiveFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsReceiveFault in AQ_XenpakRxAlarm_Status_HHD */
#define AQ_XenpakRxAlarm_Status_HHD_pcsReceiveFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsReceiveFault in AQ_XenpakRxAlarm_Status_HHD */
#define bits_AQ_XenpakRxAlarm_Status_HHD_pcsReceiveFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsReceiveFault in AQ_XenpakRxAlarm_Status_HHD */
#define word_AQ_XenpakRxAlarm_Status_HHD_pcsReceiveFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_ReceiveFault in AQ_XenpakRxAlarm_Status_HHD */
#define AQ_XenpakRxAlarm_Status_HHD_phyXS_ReceiveFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_ReceiveFault in AQ_XenpakRxAlarm_Status_HHD */
#define bits_AQ_XenpakRxAlarm_Status_HHD_phyXS_ReceiveFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_ReceiveFault in AQ_XenpakRxAlarm_Status_HHD */
#define word_AQ_XenpakRxAlarm_Status_HHD_phyXS_ReceiveFault u0.word_0

/*! \brief Base register address of structure AQ_XenpakTxAlarm_Status_HHD */
#define AQ_XenpakTxAlarm_Status_HHD_baseRegisterAddress 0x9004
/*! \brief MMD address of structure AQ_XenpakTxAlarm_Status_HHD */
#define AQ_XenpakTxAlarm_Status_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure temperatureFault in AQ_XenpakTxAlarm_Status_HHD */
#define AQ_XenpakTxAlarm_Status_HHD_temperatureFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure temperatureFault in AQ_XenpakTxAlarm_Status_HHD */
#define bits_AQ_XenpakTxAlarm_Status_HHD_temperatureFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure temperatureFault in AQ_XenpakTxAlarm_Status_HHD */
#define word_AQ_XenpakTxAlarm_Status_HHD_temperatureFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_1 in AQ_XenpakTxAlarm_Status_HHD */
#define AQ_XenpakTxAlarm_Status_HHD_reserved_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_1 in AQ_XenpakTxAlarm_Status_HHD */
#define bits_AQ_XenpakTxAlarm_Status_HHD_reserved_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_1 in AQ_XenpakTxAlarm_Status_HHD */
#define word_AQ_XenpakTxAlarm_Status_HHD_reserved_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pmaTransmitFault in AQ_XenpakTxAlarm_Status_HHD */
#define AQ_XenpakTxAlarm_Status_HHD_pmaTransmitFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaTransmitFault in AQ_XenpakTxAlarm_Status_HHD */
#define bits_AQ_XenpakTxAlarm_Status_HHD_pmaTransmitFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaTransmitFault in AQ_XenpakTxAlarm_Status_HHD */
#define word_AQ_XenpakTxAlarm_Status_HHD_pmaTransmitFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure pcsTransmitFault in AQ_XenpakTxAlarm_Status_HHD */
#define AQ_XenpakTxAlarm_Status_HHD_pcsTransmitFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure pcsTransmitFault in AQ_XenpakTxAlarm_Status_HHD */
#define bits_AQ_XenpakTxAlarm_Status_HHD_pcsTransmitFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pcsTransmitFault in AQ_XenpakTxAlarm_Status_HHD */
#define word_AQ_XenpakTxAlarm_Status_HHD_pcsTransmitFault u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure phyXS_TransmitFault in AQ_XenpakTxAlarm_Status_HHD */
#define AQ_XenpakTxAlarm_Status_HHD_phyXS_TransmitFault 0
/*! \brief Preprocessor variable to relate field to bit position in structure phyXS_TransmitFault in AQ_XenpakTxAlarm_Status_HHD */
#define bits_AQ_XenpakTxAlarm_Status_HHD_phyXS_TransmitFault u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure phyXS_TransmitFault in AQ_XenpakTxAlarm_Status_HHD */
#define word_AQ_XenpakTxAlarm_Status_HHD_phyXS_TransmitFault u0.word_0

/*! \brief Base register address of structure AQ_XenpakLASI__Status_HHD */
#define AQ_XenpakLASI__Status_HHD_baseRegisterAddress 0x9005
/*! \brief MMD address of structure AQ_XenpakLASI__Status_HHD */
#define AQ_XenpakLASI__Status_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure rxAlarm in AQ_XenpakLASI__Status_HHD */
#define AQ_XenpakLASI__Status_HHD_rxAlarm 0
/*! \brief Preprocessor variable to relate field to bit position in structure rxAlarm in AQ_XenpakLASI__Status_HHD */
#define bits_AQ_XenpakLASI__Status_HHD_rxAlarm u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure rxAlarm in AQ_XenpakLASI__Status_HHD */
#define word_AQ_XenpakLASI__Status_HHD_rxAlarm u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure txAlarm in AQ_XenpakLASI__Status_HHD */
#define AQ_XenpakLASI__Status_HHD_txAlarm 0
/*! \brief Preprocessor variable to relate field to bit position in structure txAlarm in AQ_XenpakLASI__Status_HHD */
#define bits_AQ_XenpakLASI__Status_HHD_txAlarm u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure txAlarm in AQ_XenpakLASI__Status_HHD */
#define word_AQ_XenpakLASI__Status_HHD_txAlarm u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure linkStatusAlarm in AQ_XenpakLASI__Status_HHD */
#define AQ_XenpakLASI__Status_HHD_linkStatusAlarm 0
/*! \brief Preprocessor variable to relate field to bit position in structure linkStatusAlarm in AQ_XenpakLASI__Status_HHD */
#define bits_AQ_XenpakLASI__Status_HHD_linkStatusAlarm u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure linkStatusAlarm in AQ_XenpakLASI__Status_HHD */
#define word_AQ_XenpakLASI__Status_HHD_linkStatusAlarm u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_TxControl_HHD */
#define AQ_XenpakDom_TxControl_HHD_baseRegisterAddress 0x9006
/*! \brief MMD address of structure AQ_XenpakDom_TxControl_HHD */
#define AQ_XenpakDom_TxControl_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureAlarmEnable in AQ_XenpakDom_TxControl_HHD */
#define AQ_XenpakDom_TxControl_HHD_highTemperatureAlarmEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureAlarmEnable in AQ_XenpakDom_TxControl_HHD */
#define bits_AQ_XenpakDom_TxControl_HHD_highTemperatureAlarmEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureAlarmEnable in AQ_XenpakDom_TxControl_HHD */
#define word_AQ_XenpakDom_TxControl_HHD_highTemperatureAlarmEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureAlarmEnable in AQ_XenpakDom_TxControl_HHD */
#define AQ_XenpakDom_TxControl_HHD_lowTemperatureAlarmEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureAlarmEnable in AQ_XenpakDom_TxControl_HHD */
#define bits_AQ_XenpakDom_TxControl_HHD_lowTemperatureAlarmEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureAlarmEnable in AQ_XenpakDom_TxControl_HHD */
#define word_AQ_XenpakDom_TxControl_HHD_lowTemperatureAlarmEnable u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_HighTemperatureAlarmThresholdLSW_HHD */
#define AQ_XenpakDom_HighTemperatureAlarmThresholdLSW_HHD_baseRegisterAddress 0xA000
/*! \brief MMD address of structure AQ_XenpakDom_HighTemperatureAlarmThresholdLSW_HHD */
#define AQ_XenpakDom_HighTemperatureAlarmThresholdLSW_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure highTempThreshold in AQ_XenpakDom_HighTemperatureAlarmThresholdLSW_HHD */
#define AQ_XenpakDom_HighTemperatureAlarmThresholdLSW_HHD_highTempThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTempThreshold in AQ_XenpakDom_HighTemperatureAlarmThresholdLSW_HHD */
#define bits_AQ_XenpakDom_HighTemperatureAlarmThresholdLSW_HHD_highTempThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTempThreshold in AQ_XenpakDom_HighTemperatureAlarmThresholdLSW_HHD */
#define word_AQ_XenpakDom_HighTemperatureAlarmThresholdLSW_HHD_highTempThreshold u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_HighTemperatureAlarmThresholdMSW_HHD */
#define AQ_XenpakDom_HighTemperatureAlarmThresholdMSW_HHD_baseRegisterAddress 0xA001
/*! \brief MMD address of structure AQ_XenpakDom_HighTemperatureAlarmThresholdMSW_HHD */
#define AQ_XenpakDom_HighTemperatureAlarmThresholdMSW_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure highTempThreshold in AQ_XenpakDom_HighTemperatureAlarmThresholdMSW_HHD */
#define AQ_XenpakDom_HighTemperatureAlarmThresholdMSW_HHD_highTempThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTempThreshold in AQ_XenpakDom_HighTemperatureAlarmThresholdMSW_HHD */
#define bits_AQ_XenpakDom_HighTemperatureAlarmThresholdMSW_HHD_highTempThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTempThreshold in AQ_XenpakDom_HighTemperatureAlarmThresholdMSW_HHD */
#define word_AQ_XenpakDom_HighTemperatureAlarmThresholdMSW_HHD_highTempThreshold u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_LowTemperatureAlarmThresholdLSW_HHD */
#define AQ_XenpakDom_LowTemperatureAlarmThresholdLSW_HHD_baseRegisterAddress 0xA002
/*! \brief MMD address of structure AQ_XenpakDom_LowTemperatureAlarmThresholdLSW_HHD */
#define AQ_XenpakDom_LowTemperatureAlarmThresholdLSW_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure lowTempThreshold in AQ_XenpakDom_LowTemperatureAlarmThresholdLSW_HHD */
#define AQ_XenpakDom_LowTemperatureAlarmThresholdLSW_HHD_lowTempThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTempThreshold in AQ_XenpakDom_LowTemperatureAlarmThresholdLSW_HHD */
#define bits_AQ_XenpakDom_LowTemperatureAlarmThresholdLSW_HHD_lowTempThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTempThreshold in AQ_XenpakDom_LowTemperatureAlarmThresholdLSW_HHD */
#define word_AQ_XenpakDom_LowTemperatureAlarmThresholdLSW_HHD_lowTempThreshold u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_LowTemperatureAlarmThresholdMSW_HHD */
#define AQ_XenpakDom_LowTemperatureAlarmThresholdMSW_HHD_baseRegisterAddress 0xA003
/*! \brief MMD address of structure AQ_XenpakDom_LowTemperatureAlarmThresholdMSW_HHD */
#define AQ_XenpakDom_LowTemperatureAlarmThresholdMSW_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure lowTempThreshold in AQ_XenpakDom_LowTemperatureAlarmThresholdMSW_HHD */
#define AQ_XenpakDom_LowTemperatureAlarmThresholdMSW_HHD_lowTempThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTempThreshold in AQ_XenpakDom_LowTemperatureAlarmThresholdMSW_HHD */
#define bits_AQ_XenpakDom_LowTemperatureAlarmThresholdMSW_HHD_lowTempThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTempThreshold in AQ_XenpakDom_LowTemperatureAlarmThresholdMSW_HHD */
#define word_AQ_XenpakDom_LowTemperatureAlarmThresholdMSW_HHD_lowTempThreshold u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_HighTemperatureWarningThresholdLSW_HHD */
#define AQ_XenpakDom_HighTemperatureWarningThresholdLSW_HHD_baseRegisterAddress 0xA004
/*! \brief MMD address of structure AQ_XenpakDom_HighTemperatureWarningThresholdLSW_HHD */
#define AQ_XenpakDom_HighTemperatureWarningThresholdLSW_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure highTempWarningThreshold in AQ_XenpakDom_HighTemperatureWarningThresholdLSW_HHD */
#define AQ_XenpakDom_HighTemperatureWarningThresholdLSW_HHD_highTempWarningThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTempWarningThreshold in AQ_XenpakDom_HighTemperatureWarningThresholdLSW_HHD */
#define bits_AQ_XenpakDom_HighTemperatureWarningThresholdLSW_HHD_highTempWarningThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTempWarningThreshold in AQ_XenpakDom_HighTemperatureWarningThresholdLSW_HHD */
#define word_AQ_XenpakDom_HighTemperatureWarningThresholdLSW_HHD_highTempWarningThreshold u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_HighTemperatureWarningThresholdMSW_HHD */
#define AQ_XenpakDom_HighTemperatureWarningThresholdMSW_HHD_baseRegisterAddress 0xA005
/*! \brief MMD address of structure AQ_XenpakDom_HighTemperatureWarningThresholdMSW_HHD */
#define AQ_XenpakDom_HighTemperatureWarningThresholdMSW_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure highTempWarningThreshold in AQ_XenpakDom_HighTemperatureWarningThresholdMSW_HHD */
#define AQ_XenpakDom_HighTemperatureWarningThresholdMSW_HHD_highTempWarningThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTempWarningThreshold in AQ_XenpakDom_HighTemperatureWarningThresholdMSW_HHD */
#define bits_AQ_XenpakDom_HighTemperatureWarningThresholdMSW_HHD_highTempWarningThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTempWarningThreshold in AQ_XenpakDom_HighTemperatureWarningThresholdMSW_HHD */
#define word_AQ_XenpakDom_HighTemperatureWarningThresholdMSW_HHD_highTempWarningThreshold u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_LowTemperatureWarningThresholdLSW_HHD */
#define AQ_XenpakDom_LowTemperatureWarningThresholdLSW_HHD_baseRegisterAddress 0xA006
/*! \brief MMD address of structure AQ_XenpakDom_LowTemperatureWarningThresholdLSW_HHD */
#define AQ_XenpakDom_LowTemperatureWarningThresholdLSW_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure lowTempWarningThreshold in AQ_XenpakDom_LowTemperatureWarningThresholdLSW_HHD */
#define AQ_XenpakDom_LowTemperatureWarningThresholdLSW_HHD_lowTempWarningThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTempWarningThreshold in AQ_XenpakDom_LowTemperatureWarningThresholdLSW_HHD */
#define bits_AQ_XenpakDom_LowTemperatureWarningThresholdLSW_HHD_lowTempWarningThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTempWarningThreshold in AQ_XenpakDom_LowTemperatureWarningThresholdLSW_HHD */
#define word_AQ_XenpakDom_LowTemperatureWarningThresholdLSW_HHD_lowTempWarningThreshold u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_LowTemperatureWarningThresholdMSW_HHD */
#define AQ_XenpakDom_LowTemperatureWarningThresholdMSW_HHD_baseRegisterAddress 0xA007
/*! \brief MMD address of structure AQ_XenpakDom_LowTemperatureWarningThresholdMSW_HHD */
#define AQ_XenpakDom_LowTemperatureWarningThresholdMSW_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure lowTempWarningThreshold in AQ_XenpakDom_LowTemperatureWarningThresholdMSW_HHD */
#define AQ_XenpakDom_LowTemperatureWarningThresholdMSW_HHD_lowTempWarningThreshold 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTempWarningThreshold in AQ_XenpakDom_LowTemperatureWarningThresholdMSW_HHD */
#define bits_AQ_XenpakDom_LowTemperatureWarningThresholdMSW_HHD_lowTempWarningThreshold u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTempWarningThreshold in AQ_XenpakDom_LowTemperatureWarningThresholdMSW_HHD */
#define word_AQ_XenpakDom_LowTemperatureWarningThresholdMSW_HHD_lowTempWarningThreshold u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_TemperatureLSW_HHD */
#define AQ_XenpakDom_TemperatureLSW_HHD_baseRegisterAddress 0xA060
/*! \brief MMD address of structure AQ_XenpakDom_TemperatureLSW_HHD */
#define AQ_XenpakDom_TemperatureLSW_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure temperature in AQ_XenpakDom_TemperatureLSW_HHD */
#define AQ_XenpakDom_TemperatureLSW_HHD_temperature 0
/*! \brief Preprocessor variable to relate field to bit position in structure temperature in AQ_XenpakDom_TemperatureLSW_HHD */
#define bits_AQ_XenpakDom_TemperatureLSW_HHD_temperature u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure temperature in AQ_XenpakDom_TemperatureLSW_HHD */
#define word_AQ_XenpakDom_TemperatureLSW_HHD_temperature u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_TemperatureMSW_HHD */
#define AQ_XenpakDom_TemperatureMSW_HHD_baseRegisterAddress 0xA061
/*! \brief MMD address of structure AQ_XenpakDom_TemperatureMSW_HHD */
#define AQ_XenpakDom_TemperatureMSW_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure temperature in AQ_XenpakDom_TemperatureMSW_HHD */
#define AQ_XenpakDom_TemperatureMSW_HHD_temperature 0
/*! \brief Preprocessor variable to relate field to bit position in structure temperature in AQ_XenpakDom_TemperatureMSW_HHD */
#define bits_AQ_XenpakDom_TemperatureMSW_HHD_temperature u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure temperature in AQ_XenpakDom_TemperatureMSW_HHD */
#define word_AQ_XenpakDom_TemperatureMSW_HHD_temperature u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_Status_HHD */
#define AQ_XenpakDom_Status_HHD_baseRegisterAddress 0xA06E
/*! \brief MMD address of structure AQ_XenpakDom_Status_HHD */
#define AQ_XenpakDom_Status_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure temperatureReady in AQ_XenpakDom_Status_HHD */
#define AQ_XenpakDom_Status_HHD_temperatureReady 0
/*! \brief Preprocessor variable to relate field to bit position in structure temperatureReady in AQ_XenpakDom_Status_HHD */
#define bits_AQ_XenpakDom_Status_HHD_temperatureReady u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure temperatureReady in AQ_XenpakDom_Status_HHD */
#define word_AQ_XenpakDom_Status_HHD_temperatureReady u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_Capability_HHD */
#define AQ_XenpakDom_Capability_HHD_baseRegisterAddress 0xA06F
/*! \brief MMD address of structure AQ_XenpakDom_Capability_HHD */
#define AQ_XenpakDom_Capability_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure temperatureCapability in AQ_XenpakDom_Capability_HHD */
#define AQ_XenpakDom_Capability_HHD_temperatureCapability 0
/*! \brief Preprocessor variable to relate field to bit position in structure temperatureCapability in AQ_XenpakDom_Capability_HHD */
#define bits_AQ_XenpakDom_Capability_HHD_temperatureCapability u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure temperatureCapability in AQ_XenpakDom_Capability_HHD */
#define word_AQ_XenpakDom_Capability_HHD_temperatureCapability u0.word_0

/*! \brief Base register address of structure AQ_XenpakDom_Alarms_HHD */
#define AQ_XenpakDom_Alarms_HHD_baseRegisterAddress 0xA070
/*! \brief MMD address of structure AQ_XenpakDom_Alarms_HHD */
#define AQ_XenpakDom_Alarms_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureAlarm in AQ_XenpakDom_Alarms_HHD */
#define AQ_XenpakDom_Alarms_HHD_highTemperatureAlarm 0
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureAlarm in AQ_XenpakDom_Alarms_HHD */
#define bits_AQ_XenpakDom_Alarms_HHD_highTemperatureAlarm u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureAlarm in AQ_XenpakDom_Alarms_HHD */
#define word_AQ_XenpakDom_Alarms_HHD_highTemperatureAlarm u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureAlarm in AQ_XenpakDom_Alarms_HHD */
#define AQ_XenpakDom_Alarms_HHD_lowTemperatureAlarm 0
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureAlarm in AQ_XenpakDom_Alarms_HHD */
#define bits_AQ_XenpakDom_Alarms_HHD_lowTemperatureAlarm u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureAlarm in AQ_XenpakDom_Alarms_HHD */
#define word_AQ_XenpakDom_Alarms_HHD_lowTemperatureAlarm u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure highTemperatureWarning in AQ_XenpakDom_Alarms_HHD */
#define AQ_XenpakDom_Alarms_HHD_highTemperatureWarning 4
/*! \brief Preprocessor variable to relate field to bit position in structure highTemperatureWarning in AQ_XenpakDom_Alarms_HHD */
#define bits_AQ_XenpakDom_Alarms_HHD_highTemperatureWarning u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure highTemperatureWarning in AQ_XenpakDom_Alarms_HHD */
#define word_AQ_XenpakDom_Alarms_HHD_highTemperatureWarning u4.word_4
/*! \brief Preprocessor variable to relate field to word number in structure lowTemperatureWarning in AQ_XenpakDom_Alarms_HHD */
#define AQ_XenpakDom_Alarms_HHD_lowTemperatureWarning 4
/*! \brief Preprocessor variable to relate field to bit position in structure lowTemperatureWarning in AQ_XenpakDom_Alarms_HHD */
#define bits_AQ_XenpakDom_Alarms_HHD_lowTemperatureWarning u4.bits_4
/*! \brief Preprocessor variable to relate field to word position in structure lowTemperatureWarning in AQ_XenpakDom_Alarms_HHD */
#define word_AQ_XenpakDom_Alarms_HHD_lowTemperatureWarning u4.word_4

/*! \brief Base register address of structure AQ_XenpakDom_ControlAndStatus_HHD */
#define AQ_XenpakDom_ControlAndStatus_HHD_baseRegisterAddress 0xA100
/*! \brief MMD address of structure AQ_XenpakDom_ControlAndStatus_HHD */
#define AQ_XenpakDom_ControlAndStatus_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure reserved_1 in AQ_XenpakDom_ControlAndStatus_HHD */
#define AQ_XenpakDom_ControlAndStatus_HHD_reserved_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_1 in AQ_XenpakDom_ControlAndStatus_HHD */
#define bits_AQ_XenpakDom_ControlAndStatus_HHD_reserved_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_1 in AQ_XenpakDom_ControlAndStatus_HHD */
#define word_AQ_XenpakDom_ControlAndStatus_HHD_reserved_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reserved_2 in AQ_XenpakDom_ControlAndStatus_HHD */
#define AQ_XenpakDom_ControlAndStatus_HHD_reserved_2 0
/*! \brief Preprocessor variable to relate field to bit position in structure reserved_2 in AQ_XenpakDom_ControlAndStatus_HHD */
#define bits_AQ_XenpakDom_ControlAndStatus_HHD_reserved_2 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reserved_2 in AQ_XenpakDom_ControlAndStatus_HHD */
#define word_AQ_XenpakDom_ControlAndStatus_HHD_reserved_2 u0.word_0

/*! \brief Base register address of structure AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define AQ_PmaTransmitClockPhaseSelectionControl_HHD_baseRegisterAddress 0xC142
/*! \brief MMD address of structure AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define AQ_PmaTransmitClockPhaseSelectionControl_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure channel_3TxClockPhaseSelection in AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define AQ_PmaTransmitClockPhaseSelectionControl_HHD_channel_3TxClockPhaseSelection 0
/*! \brief Preprocessor variable to relate field to bit position in structure channel_3TxClockPhaseSelection in AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define bits_AQ_PmaTransmitClockPhaseSelectionControl_HHD_channel_3TxClockPhaseSelection u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channel_3TxClockPhaseSelection in AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define word_AQ_PmaTransmitClockPhaseSelectionControl_HHD_channel_3TxClockPhaseSelection u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure channel_2TxClockPhaseSelection in AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define AQ_PmaTransmitClockPhaseSelectionControl_HHD_channel_2TxClockPhaseSelection 0
/*! \brief Preprocessor variable to relate field to bit position in structure channel_2TxClockPhaseSelection in AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define bits_AQ_PmaTransmitClockPhaseSelectionControl_HHD_channel_2TxClockPhaseSelection u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channel_2TxClockPhaseSelection in AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define word_AQ_PmaTransmitClockPhaseSelectionControl_HHD_channel_2TxClockPhaseSelection u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure channel_1TxClockPhaseSelection in AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define AQ_PmaTransmitClockPhaseSelectionControl_HHD_channel_1TxClockPhaseSelection 0
/*! \brief Preprocessor variable to relate field to bit position in structure channel_1TxClockPhaseSelection in AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define bits_AQ_PmaTransmitClockPhaseSelectionControl_HHD_channel_1TxClockPhaseSelection u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channel_1TxClockPhaseSelection in AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define word_AQ_PmaTransmitClockPhaseSelectionControl_HHD_channel_1TxClockPhaseSelection u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure channel_0TxClockPhaseSelection in AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define AQ_PmaTransmitClockPhaseSelectionControl_HHD_channel_0TxClockPhaseSelection 0
/*! \brief Preprocessor variable to relate field to bit position in structure channel_0TxClockPhaseSelection in AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define bits_AQ_PmaTransmitClockPhaseSelectionControl_HHD_channel_0TxClockPhaseSelection u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure channel_0TxClockPhaseSelection in AQ_PmaTransmitClockPhaseSelectionControl_HHD */
#define word_AQ_PmaTransmitClockPhaseSelectionControl_HHD_channel_0TxClockPhaseSelection u0.word_0

/*! \brief Base register address of structure AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define AQ_PmaTransmitReservedVendorProvisioning_HHD_baseRegisterAddress 0xC412
/*! \brief MMD address of structure AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define AQ_PmaTransmitReservedVendorProvisioning_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure testModeRate in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define AQ_PmaTransmitReservedVendorProvisioning_HHD_testModeRate 0
/*! \brief Preprocessor variable to relate field to bit position in structure testModeRate in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define bits_AQ_PmaTransmitReservedVendorProvisioning_HHD_testModeRate u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure testModeRate in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define word_AQ_PmaTransmitReservedVendorProvisioning_HHD_testModeRate u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedSpareTransmitProvisioning_0 in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define AQ_PmaTransmitReservedVendorProvisioning_HHD_reservedSpareTransmitProvisioning_0 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedSpareTransmitProvisioning_0 in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define bits_AQ_PmaTransmitReservedVendorProvisioning_HHD_reservedSpareTransmitProvisioning_0 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedSpareTransmitProvisioning_0 in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define word_AQ_PmaTransmitReservedVendorProvisioning_HHD_reservedSpareTransmitProvisioning_0 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure txPolarityInvertEnable in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define AQ_PmaTransmitReservedVendorProvisioning_HHD_txPolarityInvertEnable 0
/*! \brief Preprocessor variable to relate field to bit position in structure txPolarityInvertEnable in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define bits_AQ_PmaTransmitReservedVendorProvisioning_HHD_txPolarityInvertEnable u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure txPolarityInvertEnable in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define word_AQ_PmaTransmitReservedVendorProvisioning_HHD_txPolarityInvertEnable u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure channelMask in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define AQ_PmaTransmitReservedVendorProvisioning_HHD_channelMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure channelMask in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define bits_AQ_PmaTransmitReservedVendorProvisioning_HHD_channelMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure channelMask in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define word_AQ_PmaTransmitReservedVendorProvisioning_HHD_channelMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure reservedSpareTransmitProvisioning_1 in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define AQ_PmaTransmitReservedVendorProvisioning_HHD_reservedSpareTransmitProvisioning_1 1
/*! \brief Preprocessor variable to relate field to bit position in structure reservedSpareTransmitProvisioning_1 in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define bits_AQ_PmaTransmitReservedVendorProvisioning_HHD_reservedSpareTransmitProvisioning_1 u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure reservedSpareTransmitProvisioning_1 in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define word_AQ_PmaTransmitReservedVendorProvisioning_HHD_reservedSpareTransmitProvisioning_1 u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure incrementalTxPsdTarget in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define AQ_PmaTransmitReservedVendorProvisioning_HHD_incrementalTxPsdTarget 1
/*! \brief Preprocessor variable to relate field to bit position in structure incrementalTxPsdTarget in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define bits_AQ_PmaTransmitReservedVendorProvisioning_HHD_incrementalTxPsdTarget u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure incrementalTxPsdTarget in AQ_PmaTransmitReservedVendorProvisioning_HHD */
#define word_AQ_PmaTransmitReservedVendorProvisioning_HHD_incrementalTxPsdTarget u1.word_1

/*! \brief Base register address of structure AQ_PmaTransmitVendorAlarms_HHD */
#define AQ_PmaTransmitVendorAlarms_HHD_baseRegisterAddress 0xCC00
/*! \brief MMD address of structure AQ_PmaTransmitVendorAlarms_HHD */
#define AQ_PmaTransmitVendorAlarms_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure reservedPmaTransmitAlarms_3 in AQ_PmaTransmitVendorAlarms_HHD */
#define AQ_PmaTransmitVendorAlarms_HHD_reservedPmaTransmitAlarms_3 2
/*! \brief Preprocessor variable to relate field to bit position in structure reservedPmaTransmitAlarms_3 in AQ_PmaTransmitVendorAlarms_HHD */
#define bits_AQ_PmaTransmitVendorAlarms_HHD_reservedPmaTransmitAlarms_3 u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure reservedPmaTransmitAlarms_3 in AQ_PmaTransmitVendorAlarms_HHD */
#define word_AQ_PmaTransmitVendorAlarms_HHD_reservedPmaTransmitAlarms_3 u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure zero in AQ_PmaTransmitVendorAlarms_HHD */
#define AQ_PmaTransmitVendorAlarms_HHD_zero 2
/*! \brief Preprocessor variable to relate field to bit position in structure zero in AQ_PmaTransmitVendorAlarms_HHD */
#define bits_AQ_PmaTransmitVendorAlarms_HHD_zero u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure zero in AQ_PmaTransmitVendorAlarms_HHD */
#define word_AQ_PmaTransmitVendorAlarms_HHD_zero u2.word_2
/*! \brief Preprocessor variable to relate field to word number in structure resetComplete in AQ_PmaTransmitVendorAlarms_HHD */
#define AQ_PmaTransmitVendorAlarms_HHD_resetComplete 2
/*! \brief Preprocessor variable to relate field to bit position in structure resetComplete in AQ_PmaTransmitVendorAlarms_HHD */
#define bits_AQ_PmaTransmitVendorAlarms_HHD_resetComplete u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure resetComplete in AQ_PmaTransmitVendorAlarms_HHD */
#define word_AQ_PmaTransmitVendorAlarms_HHD_resetComplete u2.word_2

/*! \brief Base register address of structure AQ_PmaTransmitStandardInterruptMask_HHD */
#define AQ_PmaTransmitStandardInterruptMask_HHD_baseRegisterAddress 0xD000
/*! \brief MMD address of structure AQ_PmaTransmitStandardInterruptMask_HHD */
#define AQ_PmaTransmitStandardInterruptMask_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure pmaReceiveLinkStatusMask in AQ_PmaTransmitStandardInterruptMask_HHD */
#define AQ_PmaTransmitStandardInterruptMask_HHD_pmaReceiveLinkStatusMask 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaReceiveLinkStatusMask in AQ_PmaTransmitStandardInterruptMask_HHD */
#define bits_AQ_PmaTransmitStandardInterruptMask_HHD_pmaReceiveLinkStatusMask u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaReceiveLinkStatusMask in AQ_PmaTransmitStandardInterruptMask_HHD */
#define word_AQ_PmaTransmitStandardInterruptMask_HHD_pmaReceiveLinkStatusMask u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure transmitFaultMask in AQ_PmaTransmitStandardInterruptMask_HHD */
#define AQ_PmaTransmitStandardInterruptMask_HHD_transmitFaultMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure transmitFaultMask in AQ_PmaTransmitStandardInterruptMask_HHD */
#define bits_AQ_PmaTransmitStandardInterruptMask_HHD_transmitFaultMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure transmitFaultMask in AQ_PmaTransmitStandardInterruptMask_HHD */
#define word_AQ_PmaTransmitStandardInterruptMask_HHD_transmitFaultMask u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure receiveFaultMask in AQ_PmaTransmitStandardInterruptMask_HHD */
#define AQ_PmaTransmitStandardInterruptMask_HHD_receiveFaultMask 1
/*! \brief Preprocessor variable to relate field to bit position in structure receiveFaultMask in AQ_PmaTransmitStandardInterruptMask_HHD */
#define bits_AQ_PmaTransmitStandardInterruptMask_HHD_receiveFaultMask u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure receiveFaultMask in AQ_PmaTransmitStandardInterruptMask_HHD */
#define word_AQ_PmaTransmitStandardInterruptMask_HHD_receiveFaultMask u1.word_1

/*! \brief Base register address of structure AQ_PmaTransmitVendorInterruptMask_HHD */
#define AQ_PmaTransmitVendorInterruptMask_HHD_baseRegisterAddress 0xD400
/*! \brief MMD address of structure AQ_PmaTransmitVendorInterruptMask_HHD */
#define AQ_PmaTransmitVendorInterruptMask_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure resetCompleteMask in AQ_PmaTransmitVendorInterruptMask_HHD */
#define AQ_PmaTransmitVendorInterruptMask_HHD_resetCompleteMask 2
/*! \brief Preprocessor variable to relate field to bit position in structure resetCompleteMask in AQ_PmaTransmitVendorInterruptMask_HHD */
#define bits_AQ_PmaTransmitVendorInterruptMask_HHD_resetCompleteMask u2.bits_2
/*! \brief Preprocessor variable to relate field to word position in structure resetCompleteMask in AQ_PmaTransmitVendorInterruptMask_HHD */
#define word_AQ_PmaTransmitVendorInterruptMask_HHD_resetCompleteMask u2.word_2

/*! \brief Base register address of structure AQ_PmaTransmitVendorDebug_HHD */
#define AQ_PmaTransmitVendorDebug_HHD_baseRegisterAddress 0xD800
/*! \brief MMD address of structure AQ_PmaTransmitVendorDebug_HHD */
#define AQ_PmaTransmitVendorDebug_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure pmaDigitalSystemLoopback in AQ_PmaTransmitVendorDebug_HHD */
#define AQ_PmaTransmitVendorDebug_HHD_pmaDigitalSystemLoopback 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaDigitalSystemLoopback in AQ_PmaTransmitVendorDebug_HHD */
#define bits_AQ_PmaTransmitVendorDebug_HHD_pmaDigitalSystemLoopback u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaDigitalSystemLoopback in AQ_PmaTransmitVendorDebug_HHD */
#define word_AQ_PmaTransmitVendorDebug_HHD_pmaDigitalSystemLoopback u0.word_0

/*! \brief Base register address of structure AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define AQ_PmaReceiveReservedVendorProvisioning_HHD_baseRegisterAddress 0xE400
/*! \brief MMD address of structure AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define AQ_PmaReceiveReservedVendorProvisioning_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure externalPhyLoopback in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define AQ_PmaReceiveReservedVendorProvisioning_HHD_externalPhyLoopback 0
/*! \brief Preprocessor variable to relate field to bit position in structure externalPhyLoopback in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_PmaReceiveReservedVendorProvisioning_HHD_externalPhyLoopback u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure externalPhyLoopback in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define word_AQ_PmaReceiveReservedVendorProvisioning_HHD_externalPhyLoopback u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure reservedReceiveProvisioning_1 in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define AQ_PmaReceiveReservedVendorProvisioning_HHD_reservedReceiveProvisioning_1 0
/*! \brief Preprocessor variable to relate field to bit position in structure reservedReceiveProvisioning_1 in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_PmaReceiveReservedVendorProvisioning_HHD_reservedReceiveProvisioning_1 u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure reservedReceiveProvisioning_1 in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define word_AQ_PmaReceiveReservedVendorProvisioning_HHD_reservedReceiveProvisioning_1 u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure enableAquantiaFastRetrain in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define AQ_PmaReceiveReservedVendorProvisioning_HHD_enableAquantiaFastRetrain 0
/*! \brief Preprocessor variable to relate field to bit position in structure enableAquantiaFastRetrain in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_PmaReceiveReservedVendorProvisioning_HHD_enableAquantiaFastRetrain u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure enableAquantiaFastRetrain in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define word_AQ_PmaReceiveReservedVendorProvisioning_HHD_enableAquantiaFastRetrain u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure forceMdiConfiguration in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define AQ_PmaReceiveReservedVendorProvisioning_HHD_forceMdiConfiguration 0
/*! \brief Preprocessor variable to relate field to bit position in structure forceMdiConfiguration in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_PmaReceiveReservedVendorProvisioning_HHD_forceMdiConfiguration u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure forceMdiConfiguration in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define word_AQ_PmaReceiveReservedVendorProvisioning_HHD_forceMdiConfiguration u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure mdiConfiguration in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define AQ_PmaReceiveReservedVendorProvisioning_HHD_mdiConfiguration 0
/*! \brief Preprocessor variable to relate field to bit position in structure mdiConfiguration in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define bits_AQ_PmaReceiveReservedVendorProvisioning_HHD_mdiConfiguration u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure mdiConfiguration in AQ_PmaReceiveReservedVendorProvisioning_HHD */
#define word_AQ_PmaReceiveReservedVendorProvisioning_HHD_mdiConfiguration u0.word_0

/*! \brief Base register address of structure AQ_PmaReceiveVendorState_HHD */
#define AQ_PmaReceiveVendorState_HHD_baseRegisterAddress 0xE800
/*! \brief MMD address of structure AQ_PmaReceiveVendorState_HHD */
#define AQ_PmaReceiveVendorState_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure pmaReceiveLinkCurrentStatus in AQ_PmaReceiveVendorState_HHD */
#define AQ_PmaReceiveVendorState_HHD_pmaReceiveLinkCurrentStatus 0
/*! \brief Preprocessor variable to relate field to bit position in structure pmaReceiveLinkCurrentStatus in AQ_PmaReceiveVendorState_HHD */
#define bits_AQ_PmaReceiveVendorState_HHD_pmaReceiveLinkCurrentStatus u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure pmaReceiveLinkCurrentStatus in AQ_PmaReceiveVendorState_HHD */
#define word_AQ_PmaReceiveVendorState_HHD_pmaReceiveLinkCurrentStatus u0.word_0

/*! \brief Base register address of structure AQ_PmaReceiveReservedVendorState_HHD */
#define AQ_PmaReceiveReservedVendorState_HHD_baseRegisterAddress 0xE810
/*! \brief MMD address of structure AQ_PmaReceiveReservedVendorState_HHD */
#define AQ_PmaReceiveReservedVendorState_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure accumulatedFastRetrainTime in AQ_PmaReceiveReservedVendorState_HHD */
#define AQ_PmaReceiveReservedVendorState_HHD_accumulatedFastRetrainTime 0
/*! \brief Preprocessor variable to relate field to bit position in structure accumulatedFastRetrainTime in AQ_PmaReceiveReservedVendorState_HHD */
#define bits_AQ_PmaReceiveReservedVendorState_HHD_accumulatedFastRetrainTime u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure accumulatedFastRetrainTime in AQ_PmaReceiveReservedVendorState_HHD */
#define word_AQ_PmaReceiveReservedVendorState_HHD_accumulatedFastRetrainTime u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure totalNumberOfLinkRecoveryEventsSinceLastAutoneg in AQ_PmaReceiveReservedVendorState_HHD */
#define AQ_PmaReceiveReservedVendorState_HHD_totalNumberOfLinkRecoveryEventsSinceLastAutoneg 1
/*! \brief Preprocessor variable to relate field to bit position in structure totalNumberOfLinkRecoveryEventsSinceLastAutoneg in AQ_PmaReceiveReservedVendorState_HHD */
#define bits_AQ_PmaReceiveReservedVendorState_HHD_totalNumberOfLinkRecoveryEventsSinceLastAutoneg u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure totalNumberOfLinkRecoveryEventsSinceLastAutoneg in AQ_PmaReceiveReservedVendorState_HHD */
#define word_AQ_PmaReceiveReservedVendorState_HHD_totalNumberOfLinkRecoveryEventsSinceLastAutoneg u1.word_1
/*! \brief Preprocessor variable to relate field to word number in structure totalNumberOfRfiTrainingLinkRecoveryEventsSinceLastAutoneg in AQ_PmaReceiveReservedVendorState_HHD */
#define AQ_PmaReceiveReservedVendorState_HHD_totalNumberOfRfiTrainingLinkRecoveryEventsSinceLastAutoneg 1
/*! \brief Preprocessor variable to relate field to bit position in structure totalNumberOfRfiTrainingLinkRecoveryEventsSinceLastAutoneg in AQ_PmaReceiveReservedVendorState_HHD */
#define bits_AQ_PmaReceiveReservedVendorState_HHD_totalNumberOfRfiTrainingLinkRecoveryEventsSinceLastAutoneg u1.bits_1
/*! \brief Preprocessor variable to relate field to word position in structure totalNumberOfRfiTrainingLinkRecoveryEventsSinceLastAutoneg in AQ_PmaReceiveReservedVendorState_HHD */
#define word_AQ_PmaReceiveReservedVendorState_HHD_totalNumberOfRfiTrainingLinkRecoveryEventsSinceLastAutoneg u1.word_1

/*! \brief Base register address of structure AQ_PmaVendorGlobalInterruptFlags_HHD */
#define AQ_PmaVendorGlobalInterruptFlags_HHD_baseRegisterAddress 0xFC00
/*! \brief MMD address of structure AQ_PmaVendorGlobalInterruptFlags_HHD */
#define AQ_PmaVendorGlobalInterruptFlags_HHD_mmdAddress 0x01
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_1Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define AQ_PmaVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_1Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PmaVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_1Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define word_AQ_PmaVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_2Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define AQ_PmaVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_2Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PmaVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_2Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define word_AQ_PmaVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_2Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure vendorSpecificTxAlarms_3Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define AQ_PmaVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_3Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure vendorSpecificTxAlarms_3Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PmaVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_3Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure vendorSpecificTxAlarms_3Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define word_AQ_PmaVendorGlobalInterruptFlags_HHD_vendorSpecificTxAlarms_3Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarm_1Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define AQ_PmaVendorGlobalInterruptFlags_HHD_standardAlarm_1Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarm_1Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PmaVendorGlobalInterruptFlags_HHD_standardAlarm_1Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarm_1Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define word_AQ_PmaVendorGlobalInterruptFlags_HHD_standardAlarm_1Interrupt u0.word_0
/*! \brief Preprocessor variable to relate field to word number in structure standardAlarm_2Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define AQ_PmaVendorGlobalInterruptFlags_HHD_standardAlarm_2Interrupt 0
/*! \brief Preprocessor variable to relate field to bit position in structure standardAlarm_2Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define bits_AQ_PmaVendorGlobalInterruptFlags_HHD_standardAlarm_2Interrupt u0.bits_0
/*! \brief Preprocessor variable to relate field to word position in structure standardAlarm_2Interrupt in AQ_PmaVendorGlobalInterruptFlags_HHD */
#define word_AQ_PmaVendorGlobalInterruptFlags_HHD_standardAlarm_2Interrupt u0.word_0
#endif
/*@}*/
/*@}*/
