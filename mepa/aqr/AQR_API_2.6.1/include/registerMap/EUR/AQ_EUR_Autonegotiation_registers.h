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
*   This file contains the data structures and doxygen comments
*   for the Autonegotiation Registers block.
 */        

/*! \addtogroup registerMap
  @{
*/

/*! \defgroup Autonegotiation_registers Autonegotiation Registers
*   This module contains the data structures and doxygen comments
*   for the Autonegotiation Registers block.
 */        
/***********************************************************************
*                     Copyright Aquantia Corp.
*                             Freeware
*
* $Date: 2016/09/23 $
*
* $Label: $
*
* Description:
*
*   This file contains the c header structures for the registers contained in the Autonegotiation Registers block.
*
*   The bit fields in this structure are from LSbit to MSbit
*
***********************************************************************/


/*@{*/
#ifndef AQ_EUR_ANG_REGS_HEADER
#define AQ_EUR_ANG_REGS_HEADER


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Standard Control 1: 07.0000 */
/*                  Autonegotiation Standard Control 1: 07.0000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Standard Control 1 */
  union
  {
    struct
    {
                    /*! \brief 07.0000.8:0 R/WPD Reserved_0c [8:0]
                        AQ_AutonegotiationStandardControl_1_EUR.u0.bits_0.reserved0c

                        Provisionable Default = 0x000

                        Reserved bits 8 to 0
  */
      unsigned int   reserved0c : 9;    /* 07.0000.8:0  R/WPD      Provisionable Default = 0x000 */
                     /* Reserved bits 8 to 0  */
                    /*! \brief 07.0000.9 R/WSC Restart Autonegotiation
                        AQ_AutonegotiationStandardControl_1_EUR.u0.bits_0.restartAutonegotiation

                        Default = 0x0

                        1 = Restart autonegotiation process
                        0 = Normal operation

                 <B>Notes:</B>
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   restartAutonegotiation : 1;    /* 07.0000.9  R/WSC      Default = 0x0 */
                     /* 1 = Restart autonegotiation process
                        0 = Normal operation  */
                    /*! \brief 07.0000.B:A R/WPD Reserved_0b [B:A]
                        AQ_AutonegotiationStandardControl_1_EUR.u0.bits_0.reserved0b

                        Provisionable Default = 0x0

                        Reserved bits 11 to 10
  */
      unsigned int   reserved0b : 2;    /* 07.0000.B:A  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bits 11 to 10  */
                    /*! \brief 07.0000.C R/WPD Autonegotiation Enable
                        AQ_AutonegotiationStandardControl_1_EUR.u0.bits_0.autonegotiationEnable

                        Provisionable Default = 0x1

                        1 = Enable autonegotiation
                        0 = Disable autonegotiation

                 <B>Notes:</B>
                        When enabled, autonegotiation determines the link speed. If this bit is disabled, autonegotiation is disabled.  */
      unsigned int   autonegotiationEnable : 1;    /* 07.0000.C  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = Enable autonegotiation
                        0 = Disable autonegotiation  */
                    /*! \brief 07.0000.D R/WPD Extended Next Page Control
                        AQ_AutonegotiationStandardControl_1_EUR.u0.bits_0.extendedNextPageControl

                        Provisionable Default = 0x1

                        1 = Extended next pages are enabled
                        0 = Extended next pages are disabled

                 <B>Notes:</B>
                        This bit is OR'ed with bit 7.10.C.  */
      unsigned int   extendedNextPageControl : 1;    /* 07.0000.D  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = Extended next pages are enabled
                        0 = Extended next pages are disabled  */
                    /*! \brief 07.0000.E R/WPD Reserved_0a
                        AQ_AutonegotiationStandardControl_1_EUR.u0.bits_0.reserved0a

                        Provisionable Default = 0x0

                        Reserved bit 14
  */
      unsigned int   reserved0a : 1;    /* 07.0000.E  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bit 14  */
                    /*! \brief 07.0000.F R/WSC Reset
                        AQ_AutonegotiationStandardControl_1_EUR.u0.bits_0.reset

                        Default = 0x1

                        1 = Autonegotiation reset
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        Resets the entire PHY.
                        The reset bit is automatically cleared upon completion of the reset sequence by the microcontroller. This bit is set to 1 during reset. The reset is internally stretched by approximately 1.7 us. Therefore the MDIO or uP should allow for 1.7 us before writing any Autonegotiation registers after this bit is set.
                        
                          */
      unsigned int   reset : 1;    /* 07.0000.F  R/WSC      Default = 0x1 */
                     /* 1 = Autonegotiation reset
                        0 = Normal operation
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationStandardControl_1_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Standard Status 1: 07.0001 */
/*                  Autonegotiation Standard Status 1: 07.0001 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Standard Status 1 */
  union
  {
    struct
    {
                    /*! \brief 07.0001.0 RO Link Partner Autonegotiation Ability
                        AQ_AutonegotiationStandardStatus_1_EUR.u0.bits_0.linkPartnerAutonegotiationAbility

                        

                        1 = Link Partner able to perform autonegotiation
                        0 = Link Partner not able to perform autonegotiation
  */
      unsigned int   linkPartnerAutonegotiationAbility : 1;    /* 07.0001.0  RO       */
                     /* 1 = Link Partner able to perform autonegotiation
                        0 = Link Partner not able to perform autonegotiation  */
                    /*! \brief 07.0001.1 R/W Reserved_1c
                        AQ_AutonegotiationStandardStatus_1_EUR.u0.bits_0.reserved1c

                        Default = 0x0

                        Reserved bit 1
  */
      unsigned int   reserved1c : 1;    /* 07.0001.1  R/W      Default = 0x0 */
                     /* Reserved bit 1  */
                    /*! \brief 07.0001.2 LL Link Status
                        AQ_AutonegotiationStandardStatus_1_EUR.u0.bits_0.linkStatus

                        

                        1 = Link is up
                        0 = Link lost since last read
                        

                 <B>Notes:</B>
                        This bit it is a duplicate of the PMA link status bit in 1.1.2. Note that this is latching low, so it can only be used to detect link drops, and not the current status of the link without performing back-to-back reads.  */
      unsigned int   linkStatus : 1;    /* 07.0001.2  LL       */
                     /* 1 = Link is up
                        0 = Link lost since last read
                          */
                    /*! \brief 07.0001.3 ROS Autonegotiation Ability
                        AQ_AutonegotiationStandardStatus_1_EUR.u0.bits_0.autonegotiationAbility

                        Default = 0x1

                        1 = PHY is able to perform autonegotiation
                        0 = PHY is not able to perform autonegotiation

                 <B>Notes:</B>
                        Always set as 1 as the local device has autonegotiation ability.  */
      unsigned int   autonegotiationAbility : 1;    /* 07.0001.3  ROS      Default = 0x1 */
                     /* 1 = PHY is able to perform autonegotiation
                        0 = PHY is not able to perform autonegotiation  */
                    /*! \brief 07.0001.4 LH Remote Fault
                        AQ_AutonegotiationStandardStatus_1_EUR.u0.bits_0.remoteFault

                        

                        1 = Remote fault condition detected
                        0 = No remote fault condition detected
                        

                 <B>Notes:</B>
                        This indicates that the remote PHY has a fault.   */
      unsigned int   remoteFault : 1;    /* 07.0001.4  LH       */
                     /* 1 = Remote fault condition detected
                        0 = No remote fault condition detected
                          */
                    /*! \brief 07.0001.5 RO Autonegotiation Complete
                        AQ_AutonegotiationStandardStatus_1_EUR.u0.bits_0.autonegotiationComplete

                        

                        1 = Autonegotiation complete
                        0 = Autonegotiation in process

                 <B>Notes:</B>
                        This indicates the status of the Autonegotiation receive link.  */
      unsigned int   autonegotiationComplete : 1;    /* 07.0001.5  RO       */
                     /* 1 = Autonegotiation complete
                        0 = Autonegotiation in process  */
                    /*! \brief 07.0001.6 LH Page Received
                        AQ_AutonegotiationStandardStatus_1_EUR.u0.bits_0.pageReceived

                        

                        1 = A page has been received
                        0 = A page has not been received
                        

                 <B>Notes:</B>
                        Indicates that a page has been received. If a regular page, it is placed in 7.13 ->7.15. If an extended next page it is placed in registers 7.19 -> 7.1B  */
      unsigned int   pageReceived : 1;    /* 07.0001.6  LH       */
                     /* 1 = A page has been received
                        0 = A page has not been received
                          */
                    /*! \brief 07.0001.7 RO Extended Next Page Status
                        AQ_AutonegotiationStandardStatus_1_EUR.u0.bits_0.extendedNextPageStatus

                        

                        1 = Extended next page will be used
                        0 = Extended next page will not be used

                 <B>Notes:</B>
                        Indicates that both the local device and the link partner have indicated support for extended next page.  */
      unsigned int   extendedNextPageStatus : 1;    /* 07.0001.7  RO       */
                     /* 1 = Extended next page will be used
                        0 = Extended next page will not be used  */
                    /*! \brief 07.0001.8 R/W Reserved_1b
                        AQ_AutonegotiationStandardStatus_1_EUR.u0.bits_0.reserved1b

                        Default = 0x0

                        Reserved bit 8
  */
      unsigned int   reserved1b : 1;    /* 07.0001.8  R/W      Default = 0x0 */
                     /* Reserved bit 8  */
                    /*! \brief 07.0001.9 LH Parallel Detection Fault
                        AQ_AutonegotiationStandardStatus_1_EUR.u0.bits_0.parallelDetectionFault

                        

                        1 = A fault has been detected via the parallel detection function
                        0 = A fault has not been detected via the parallel detection function
  */
      unsigned int   parallelDetectionFault : 1;    /* 07.0001.9  LH       */
                     /* 1 = A fault has been detected via the parallel detection function
                        0 = A fault has not been detected via the parallel detection function  */
                    /*! \brief 07.0001.F:A R/W Reserved_1a [F:A]
                        AQ_AutonegotiationStandardStatus_1_EUR.u0.bits_0.reserved1a

                        Default = 0x00

                        Reserved bits 15 to 10
  */
      unsigned int   reserved1a : 6;    /* 07.0001.F:A  R/W      Default = 0x00 */
                     /* Reserved bits 15 to 10  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationStandardStatus_1_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Standard Device Identifier: 07.0002 */
/*                  Autonegotiation Standard Device Identifier: 07.0002 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 07.0002.F:0 RO Device ID MSW [1F:10]
                        AQ_AutonegotiationStandardDeviceIdentifier_EUR.u0.bits_0.deviceIdMSW

                        

                        Bits 31 - 16 of Device ID
  */
      unsigned int   deviceIdMSW : 16;    /* 07.0002.F:0  RO       */
                     /* Bits 31 - 16 of Device ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 07.0003.F:0 RO Device ID LSW [F:0]
                        AQ_AutonegotiationStandardDeviceIdentifier_EUR.u1.bits_1.deviceIdLSW

                        

                        Bits 15 - 0 of Device ID
  */
      unsigned int   deviceIdLSW : 16;    /* 07.0003.F:0  RO       */
                     /* Bits 15 - 0 of Device ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_AutonegotiationStandardDeviceIdentifier_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Standard Devices in Package: 07.0005 */
/*                  Autonegotiation Standard Devices in Package: 07.0005 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Standard Devices in Package */
  union
  {
    struct
    {
                    /*! \brief 07.0005.0 ROS Clause 22 Registers Present
                        AQ_AutonegotiationStandardDevicesInPackage_EUR.u0.bits_0.clause_22RegistersPresent

                        Default = 0x0

                        1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package

                 <B>Notes:</B>
                        This is always set to 0 in the PHY, as there are no Clause 22 registers in the device.  */
      unsigned int   clause_22RegistersPresent : 1;    /* 07.0005.0  ROS      Default = 0x0 */
                     /* 1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package  */
                    /*! \brief 07.0005.1 ROS PMA Present
                        AQ_AutonegotiationStandardDevicesInPackage_EUR.u0.bits_0.pmaPresent

                        Default = 0x1

                        1 = PMA is present in package
                        0 = PMA is not present 

                 <B>Notes:</B>
                        This is always set to 1 as there is PMA functionality in the PHY.  */
      unsigned int   pmaPresent : 1;    /* 07.0005.1  ROS      Default = 0x1 */
                     /* 1 = PMA is present in package
                        0 = PMA is not present   */
                    /*! \brief 07.0005.2 ROS WIS Present
                        AQ_AutonegotiationStandardDevicesInPackage_EUR.u0.bits_0.wisPresent

                        Default = 0x0

                        1 = WIS is present in package
                        0 = WIS is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no WIS functionality in the PHY.  */
      unsigned int   wisPresent : 1;    /* 07.0005.2  ROS      Default = 0x0 */
                     /* 1 = WIS is present in package
                        0 = WIS is not present in package  */
                    /*! \brief 07.0005.3 ROS PCS Present
                        AQ_AutonegotiationStandardDevicesInPackage_EUR.u0.bits_0.pcsPresent

                        Default = 0x1

                        1 = PCS is present in package
                        0 = PCS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is PCS functionality in the PHY.  */
      unsigned int   pcsPresent : 1;    /* 07.0005.3  ROS      Default = 0x1 */
                     /* 1 = PCS is present in package
                        0 = PCS is not present in package  */
                    /*! \brief 07.0005.4 ROS PHY XS Present
                        AQ_AutonegotiationStandardDevicesInPackage_EUR.u0.bits_0.phyXS_Present

                        Default = 0x1

                        1 = PHY XS is present in package
                        0 = PHY XS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is a PHY XS interface in the PHY.  */
      unsigned int   phyXS_Present : 1;    /* 07.0005.4  ROS      Default = 0x1 */
                     /* 1 = PHY XS is present in package
                        0 = PHY XS is not present in package  */
                    /*! \brief 07.0005.5 ROS DTE XS Present
                        AQ_AutonegotiationStandardDevicesInPackage_EUR.u0.bits_0.dteXsPresent

                        Default = 0x0

                        1 = DTE XS is present in package
                        0 = DTE XS is not present in package
                        

                 <B>Notes:</B>
                        This is always set to 0, as there is no DTE XAUI interface in the PHY.  */
      unsigned int   dteXsPresent : 1;    /* 07.0005.5  ROS      Default = 0x0 */
                     /* 1 = DTE XS is present in package
                        0 = DTE XS is not present in package
                          */
                    /*! \brief 07.0005.6 ROS TC Present
                        AQ_AutonegotiationStandardDevicesInPackage_EUR.u0.bits_0.tcPresent

                        Default = 0x0

                        1 = TC is present in package
                        0 = TC is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no TC functionality in the PHY.  */
      unsigned int   tcPresent : 1;    /* 07.0005.6  ROS      Default = 0x0 */
                     /* 1 = TC is present in package
                        0 = TC is not present in package  */
                    /*! \brief 07.0005.7 ROS Autonegotiation Present
                        AQ_AutonegotiationStandardDevicesInPackage_EUR.u0.bits_0.autonegotiationPresent

                        Default = 0x1

                        1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package

                 <B>Notes:</B>
                        This is always set to 1, as there is Autonegotiation in the PHY.  */
      unsigned int   autonegotiationPresent : 1;    /* 07.0005.7  ROS      Default = 0x1 */
                     /* 1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package  */
      unsigned int   reserved0 : 8;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Standard Devices in Package */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 07.0006.D ROS Clause 22 Extension Present
                        AQ_AutonegotiationStandardDevicesInPackage_EUR.u1.bits_1.clause_22ExtensionPresent

                        Default = 0x1

                        1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the GbE registers.  */
      unsigned int   clause_22ExtensionPresent : 1;    /* 07.0006.D  ROS      Default = 0x1 */
                     /* 1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package  */
                    /*! \brief 07.0006.E ROS Vendor Specific Device #1 Present
                        AQ_AutonegotiationStandardDevicesInPackage_EUR.u1.bits_1.vendorSpecificDevice_1Present

                        Default = 0x1

                        1 = Device #1 is present in package
                        0 = Device #1 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the global control registers.  */
      unsigned int   vendorSpecificDevice_1Present : 1;    /* 07.0006.E  ROS      Default = 0x1 */
                     /* 1 = Device #1 is present in package
                        0 = Device #1 is not present in package  */
                    /*! \brief 07.0006.F ROS Vendor Specific Device #2 Present
                        AQ_AutonegotiationStandardDevicesInPackage_EUR.u1.bits_1.vendorSpecificDevice_2Present

                        Default = 0x1

                        1 = Device #2 is present in package
                        0 = Device #2 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the DSP PMA registers.  */
      unsigned int   vendorSpecificDevice_2Present : 1;    /* 07.0006.F  ROS      Default = 0x1 */
                     /* 1 = Device #2 is present in package
                        0 = Device #2 is not present in package  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_AutonegotiationStandardDevicesInPackage_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Standard Status 2: 07.0008 */
/*                  Autonegotiation Standard Status 2: 07.0008 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Standard Status 2 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 07.0008.F:E ROS Device Present [1:0]
                        AQ_AutonegotiationStandardStatus_2_EUR.u0.bits_0.devicePresent

                        Default = 0x2

                        [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address

                 <B>Notes:</B>
                        This field is always set to 0x2, as the Autonegotiation resides here in the PHY.  */
      unsigned int   devicePresent : 2;    /* 07.0008.F:E  ROS      Default = 0x2 */
                     /* [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationStandardStatus_2_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Standard Package Identifier: 07.000E */
/*                  Autonegotiation Standard Package Identifier: 07.000E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 07.000E.F:0 RO Package ID MSW [1F:10]
                        AQ_AutonegotiationStandardPackageIdentifier_EUR.u0.bits_0.packageIdMSW

                        

                        Bits 31- 16 of Package ID
  */
      unsigned int   packageIdMSW : 16;    /* 07.000E.F:0  RO       */
                     /* Bits 31- 16 of Package ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 07.000F.F:0 RO Package ID LSW [F:0]
                        AQ_AutonegotiationStandardPackageIdentifier_EUR.u1.bits_1.packageIdLSW

                        

                        Bits 15 - 0 of Package ID
  */
      unsigned int   packageIdLSW : 16;    /* 07.000F.F:0  RO       */
                     /* Bits 15 - 0 of Package ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_AutonegotiationStandardPackageIdentifier_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Advertisement Register: 07.0010 */
/*                  Autonegotiation Advertisement Register: 07.0010 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Advertisement Register */
  union
  {
    struct
    {
                    /*! \brief 07.0010.4:0 R/WPD Selector Field [4:0]
                        AQ_AutonegotiationAdvertisementRegister_EUR.u0.bits_0.selectorField

                        Provisionable Default = 0x01

                        This defines the device compatibility:
                        0x00 = Reserved
                        0x01 = IEEE 802.3
                        0x02 = IEEE 802.9 ISLAN-16T
                        0x03 = IEEE 802.5
                        0x04 = IEEE 1394
                        0x05 -> 0x1F = Reserved

                 <B>Notes:</B>
                        This field should always be set to 0x01 as the PHY is only capable of handling 802.3 Ethernet.  */
      unsigned int   selectorField : 5;    /* 07.0010.4:0  R/WPD      Provisionable Default = 0x01 */
                     /* This defines the device compatibility:
                        0x00 = Reserved
                        0x01 = IEEE 802.3
                        0x02 = IEEE 802.9 ISLAN-16T
                        0x03 = IEEE 802.5
                        0x04 = IEEE 1394
                        0x05 -> 0x1F = Reserved  */
                    /*! \brief 07.0010.B:5 R/WPD Technology Ability Field [6:0]
                        AQ_AutonegotiationAdvertisementRegister_EUR.u0.bits_0.technologyAbilityField

                        Provisionable Default = 0x00

                        Bit 0: 10BASE-T
                        Bit 1: 10BASE-T full duplex
                        Bit 2: 100BASE-TX
                        Bit 3: 100BASE-TX full duplex
                        Bit 4: 100BASE-T4
                        Bit 5: PAUSE operation for full duplex links
                        Bit 6: Asymmetric PAUSE operation for full duplex links

                 <B>Notes:</B>
                        The Technology Ability Field contains information indicating supported technologies defined in Annex 28B.2 and Annex 28D. Multiple technologies may be advertised in the link code word. A device shall support the data service ability for a technology it advertises.
                        
                        Since the PHY does not support 10BASE-T or 100BASE-T4, these bits (0, 1, 4) should always be set to zero.  */
      unsigned int   technologyAbilityField : 7;    /* 07.0010.B:5  R/WPD      Provisionable Default = 0x00 */
                     /* Bit 0: 10BASE-T
                        Bit 1: 10BASE-T full duplex
                        Bit 2: 100BASE-TX
                        Bit 3: 100BASE-TX full duplex
                        Bit 4: 100BASE-T4
                        Bit 5: PAUSE operation for full duplex links
                        Bit 6: Asymmetric PAUSE operation for full duplex links  */
                    /*! \brief 07.0010.C R/WPD Extended Next Page Ability
                        AQ_AutonegotiationAdvertisementRegister_EUR.u0.bits_0.extendedNextPageAbility

                        Provisionable Default = 0x1

                        1 = Extended next page capable
                        0 = Not capable of extended next pages

                 <B>Notes:</B>
                        The Extended Next Page (XNP) bit indicates that the local device supports transmission of extended next pages when set to 1 and indicates that the local device does not support extended next pages when set to 0.  */
      unsigned int   extendedNextPageAbility : 1;    /* 07.0010.C  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = Extended next page capable
                        0 = Not capable of extended next pages  */
                    /*! \brief 07.0010.D R/W Advertisement Remote Fault
                        AQ_AutonegotiationAdvertisementRegister_EUR.u0.bits_0.advertisementRemoteFault

                        Default = 0x0

                        1 = Remote fault

                 <B>Notes:</B>
                        The remote fault bit provides a standard transport mechanism for the transmission of simple fault information. When the RF bit in the received base link code word is set to 1, the RF bit will be set to 1.
                        
                        Note: The PHY does not support a remote fault sensing function.  */
      unsigned int   advertisementRemoteFault : 1;    /* 07.0010.D  R/W      Default = 0x0 */
                     /* 1 = Remote fault  */
                    /*! \brief 07.0010.E R/WPD Reserved_7a
                        AQ_AutonegotiationAdvertisementRegister_EUR.u0.bits_0.reserved7a

                        Provisionable Default = 0x0

                        Reserved bit 14
  */
      unsigned int   reserved7a : 1;    /* 07.0010.E  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bit 14  */
                    /*! \brief 07.0010.F R/WPD Next page Ability
                        AQ_AutonegotiationAdvertisementRegister_EUR.u0.bits_0.nextPageAbility

                        Provisionable Default = 0x1

                        1 = Next page ability

                 <B>Notes:</B>
                        If a device implements Next Page ability and wishes to engage in Next Page exchange, it shall set the NP bit to 1. A device may implement Next Page ability and choose not to engage in Next Page exchange by setting the NP bit to a 0.  */
      unsigned int   nextPageAbility : 1;    /* 07.0010.F  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = Next page ability  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationAdvertisementRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Link Partner Base Page Ability Register: 07.0013 */
/*                  Autonegotiation Link Partner Base Page Ability Register: 07.0013 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Link Partner Base Page Ability Register */
  union
  {
    struct
    {
                    /*! \brief 07.0013.4:0 RO Link Partner Selector Field [4:0]
                        AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_EUR.u0.bits_0.linkPartnerSelectorField

                        

                        This defines the device compatibility:
                        0x00 = Reserved
                        0x01 = IEEE 802.3
                        0x02 = IEEE 802.9 ISLAN-16T
                        0x03 = IEEE 802.5
                        0x04 = IEEE 1394
                        0x05 -> 0x1F = Reserved

                 <B>Notes:</B>
                        Selector field encodes 32 possible messages defined in Annex 28A. Combinations not specified are reserved for future use and shall not be transmitted.  */
      unsigned int   linkPartnerSelectorField : 5;    /* 07.0013.4:0  RO       */
                     /* This defines the device compatibility:
                        0x00 = Reserved
                        0x01 = IEEE 802.3
                        0x02 = IEEE 802.9 ISLAN-16T
                        0x03 = IEEE 802.5
                        0x04 = IEEE 1394
                        0x05 -> 0x1F = Reserved  */
                    /*! \brief 07.0013.B:5 RO Link Partner Technology Ability Field [6:0]
                        AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_EUR.u0.bits_0.linkPartnerTechnologyAbilityField

                        

                        Bit 0: 10BASE-T
                        Bit 1: 10BASE-T full duplex
                        Bit 2: 100BASE-TX
                        Bit 3: 100BASE-TX full duplex
                        Bit 4: 100BASE-T4
                        Bit 5: PAUSE operation for full duplex links
                        Bit 6: Asymmetric PAUSE operation for full duplex links

                 <B>Notes:</B>
                        Technology ability field contains information indicating supported technologies defined in Annex 28B.2 and Annex 28D. Multiple technologies may be advertised in the link code word. A device shall support the data service ability for a technology it advertises. The arbitration function determines the common mode of operation shared by a link partner and resolves the multiple common modes.  */
      unsigned int   linkPartnerTechnologyAbilityField : 7;    /* 07.0013.B:5  RO       */
                     /* Bit 0: 10BASE-T
                        Bit 1: 10BASE-T full duplex
                        Bit 2: 100BASE-TX
                        Bit 3: 100BASE-TX full duplex
                        Bit 4: 100BASE-T4
                        Bit 5: PAUSE operation for full duplex links
                        Bit 6: Asymmetric PAUSE operation for full duplex links  */
                    /*! \brief 07.0013.C RO Link Partner Extended Next Page Ability
                        AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_EUR.u0.bits_0.linkPartnerExtendedNextPageAbility

                        

                        1 = Extended next page capable
                        0 = Not capable of extended next pages

                 <B>Notes:</B>
                        The extended next page indicates that the link partner has indicated support for the extended next page when set to 1. When set to 0, the link partner does not support extended next page.  */
      unsigned int   linkPartnerExtendedNextPageAbility : 1;    /* 07.0013.C  RO       */
                     /* 1 = Extended next page capable
                        0 = Not capable of extended next pages  */
                    /*! \brief 07.0013.D RO Link Partner Remote Fault
                        AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_EUR.u0.bits_0.linkPartnerRemoteFault

                        

                        1 = Remote fault

                 <B>Notes:</B>
                        The remote fault bit provides a standard transport mechanism for the transmission of simple fault information. When the RF bit in the received base link code word is set to 1, the RF bit will be set to 1.  */
      unsigned int   linkPartnerRemoteFault : 1;    /* 07.0013.D  RO       */
                     /* 1 = Remote fault  */
                    /*! \brief 07.0013.E RO Link Partner Base Page Acknowledge
                        AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_EUR.u0.bits_0.linkPartnerBasePageAcknowledge

                        

                        1 = Acknowledge

                 <B>Notes:</B>
                        The Acknowledge (ACK) is used by the Auto-Negotiation function to indicate that a device has successfully received its Link Partner's Link Code Word.  */
      unsigned int   linkPartnerBasePageAcknowledge : 1;    /* 07.0013.E  RO       */
                     /* 1 = Acknowledge  */
                    /*! \brief 07.0013.F RO Link Partner Next Page Ability
                        AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_EUR.u0.bits_0.linkPartnerNextPageAbility

                        

                        1 = Next page ability
                        0 = Next page ability not supported or not engaged

                 <B>Notes:</B>
                        If Next Page ability is not supported, the NP bit shall always be set to 0. If a device implements Next Page ability and wishes to engage in Next Page exchange, it shall set the NP bit to logic 1.  */
      unsigned int   linkPartnerNextPageAbility : 1;    /* 07.0013.F  RO       */
                     /* 1 = Next page ability
                        0 = Next page ability not supported or not engaged  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationLinkPartnerBasePageAbilityRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Extended Next Page Transmit Register: 07.0016 */
/*                  Autonegotiation Extended Next Page Transmit Register: 07.0016 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Extended Next Page Transmit Register */
  union
  {
    struct
    {
                    /*! \brief 07.0016.A:0 R/WPD Message Code Field [A:0]
                        AQ_AutonegotiationExtendedNextPageTransmitRegister_EUR.u0.bits_0.messageCodeField

                        Provisionable Default = 0x001

                        [A:0] = Message Code Field:
                        
                        0x0 = Reserved
                        0x1 = Null message
                        0x2 -> 0x3 Reserved Expansion message
                        0x4 = Remote fault details message
                        0x5 = OUI message
                        0x6 = PHY ID message
                        0x7 = 100BASE-T2 message
                        0x8 = 1000BASE-T message
                        0x9 = 10GBASE-T message

                 <B>Notes:</B>
                        Interpreted as message code (see 802.3 Appendix 28C) if Message Page bit is set to one (7.16:1). Otherwise interpreted as an unformatted code field.  */
      unsigned int   messageCodeField : 11;    /* 07.0016.A:0  R/WPD      Provisionable Default = 0x001 */
                     /* [A:0] = Message Code Field:
                        
                        0x0 = Reserved
                        0x1 = Null message
                        0x2 -> 0x3 Reserved Expansion message
                        0x4 = Remote fault details message
                        0x5 = OUI message
                        0x6 = PHY ID message
                        0x7 = 100BASE-T2 message
                        0x8 = 1000BASE-T message
                        0x9 = 10GBASE-T message  */
                    /*! \brief 07.0016.B RO Toggle
                        AQ_AutonegotiationExtendedNextPageTransmitRegister_EUR.u0.bits_0.toggle

                        

                        Value of toggle bit

                 <B>Notes:</B>
                        Set to opposite of corresponding bit in previous page.  */
      unsigned int   toggle : 1;    /* 07.0016.B  RO       */
                     /* Value of toggle bit  */
                    /*! \brief 07.0016.C R/W Acknowledge 2
                        AQ_AutonegotiationExtendedNextPageTransmitRegister_EUR.u0.bits_0.acknowledge_2

                        Default = 0x0

                        1 = Will comply with corresponding message
                        0 = Cannot comply with corresponding message

                 <B>Notes:</B>
                        Acknowledge 2 is used by the next page function to indicate that a device has the ability to comply with the message.  */
      unsigned int   acknowledge_2 : 1;    /* 07.0016.C  R/W      Default = 0x0 */
                     /* 1 = Will comply with corresponding message
                        0 = Cannot comply with corresponding message  */
                    /*! \brief 07.0016.D R/W Message Page
                        AQ_AutonegotiationExtendedNextPageTransmitRegister_EUR.u0.bits_0.messagePage

                        Default = 0x0

                        1 = Message page
                        0 = Unformatted page

                 <B>Notes:</B>
                        Message page is used by the next page function to differentiate a message page from an unformatted page.  */
      unsigned int   messagePage : 1;    /* 07.0016.D  R/W      Default = 0x0 */
                     /* 1 = Message page
                        0 = Unformatted page  */
                    /*! \brief 07.0016.E R/W Reserved_16a
                        AQ_AutonegotiationExtendedNextPageTransmitRegister_EUR.u0.bits_0.reserved16a

                        Default = 0x0

                        Reserved bit 14
  */
      unsigned int   reserved16a : 1;    /* 07.0016.E  R/W      Default = 0x0 */
                     /* Reserved bit 14  */
                    /*! \brief 07.0016.F R/W Next Page
                        AQ_AutonegotiationExtendedNextPageTransmitRegister_EUR.u0.bits_0.nextPage

                        Default = 0x0

                        1 = Additional next page will follow
                        0 = Last page

                 <B>Notes:</B>
                        Next page is used by the next page function to indicate whether or not this is the last next page to be transmitted.  */
      unsigned int   nextPage : 1;    /* 07.0016.F  R/W      Default = 0x0 */
                     /* 1 = Additional next page will follow
                        0 = Last page  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationExtendedNextPageTransmitRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Extended Next Page Unformatted Code Register: 07.0017 */
/*                  Autonegotiation Extended Next Page Unformatted Code Register: 07.0017 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Extended Next Page Unformatted Code Register */
  union
  {
    struct
    {
                    /*! \brief 07.0017.F:0 R/WPD Unformatted Code Field 1 [1F:10]
                        AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_EUR.u0.bits_0.unformattedCodeField_1

                        Provisionable Default = 0x0000

                        [F:0] = Unformatted Code Field 1
  */
      unsigned int   unformattedCodeField_1 : 16;    /* 07.0017.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* [F:0] = Unformatted Code Field 1  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Extended Next Page Unformatted Code Register */
  union
  {
    struct
    {
                    /*! \brief 07.0018.F:0 R/WPD Unformatted Code Field 2 [2F:20]
                        AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_EUR.u1.bits_1.unformattedCodeField_2

                        Provisionable Default = 0x0000

                        [F:0] = Unformatted Code Field 2
  */
      unsigned int   unformattedCodeField_2 : 16;    /* 07.0018.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* [F:0] = Unformatted Code Field 2  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_AutonegotiationExtendedNextPageUnformattedCodeRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Link Partner Extended Next Page Ability Register: 07.0019 */
/*                  Autonegotiation Link Partner Extended Next Page Ability Register: 07.0019 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Link Partner Extended Next Page Ability Register */
  union
  {
    struct
    {
                    /*! \brief 07.0019.A:0 RO Link Partner Message Code Field [A:0]
                        AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_EUR.u0.bits_0.linkPartnerMessageCodeField

                        

                        [A:0] = Message Code Field:
                        
                        0x0 = Reserved
                        0x1 = Null message
                        0x2 -> 0x3 Reserved Expansion message
                        0x4 = Remote fault details message
                        0x5 = OUI message
                        0x6 = PHY ID message
                        0x7 = 100BASE-T2 message
                        0x8 = 1000BASE-T message
                        0x9 = 10GBASE-T message

                 <B>Notes:</B>
                        Interpreted as message code (see 802.3 Appendix 28C) if Message Page bit is set to one (7.16:1). Otherwise interpreted as an unformatted code field.  */
      unsigned int   linkPartnerMessageCodeField : 11;    /* 07.0019.A:0  RO       */
                     /* [A:0] = Message Code Field:
                        
                        0x0 = Reserved
                        0x1 = Null message
                        0x2 -> 0x3 Reserved Expansion message
                        0x4 = Remote fault details message
                        0x5 = OUI message
                        0x6 = PHY ID message
                        0x7 = 100BASE-T2 message
                        0x8 = 1000BASE-T message
                        0x9 = 10GBASE-T message  */
                    /*! \brief 07.0019.B RO Link Partner Toggle
                        AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_EUR.u0.bits_0.linkPartnerToggle

                        

                        Value of link partner's toggle bit

                 <B>Notes:</B>
                        Set to opposite of corresponding bit in previous page.  */
      unsigned int   linkPartnerToggle : 1;    /* 07.0019.B  RO       */
                     /* Value of link partner's toggle bit  */
                    /*! \brief 07.0019.C RO Link Partner Acknowledge 2
                        AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_EUR.u0.bits_0.linkPartnerAcknowledge_2

                        

                        1 = Link partner acknowledges that they can comply with the current next page
                        0 = Link partner cannot comply with the current next page
  */
      unsigned int   linkPartnerAcknowledge_2 : 1;    /* 07.0019.C  RO       */
                     /* 1 = Link partner acknowledges that they can comply with the current next page
                        0 = Link partner cannot comply with the current next page  */
                    /*! \brief 07.0019.D RO Link Partner Message Page
                        AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_EUR.u0.bits_0.linkPartnerMessagePage

                        

                        1 = Message page
                        0 = Unformatted page
  */
      unsigned int   linkPartnerMessagePage : 1;    /* 07.0019.D  RO       */
                     /* 1 = Message page
                        0 = Unformatted page  */
                    /*! \brief 07.0019.E RO Link Partner Extended Next Page Acknowledge
                        AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_EUR.u0.bits_0.linkPartnerExtendedNextPageAcknowledge

                        

                        1 = Link Partner acknowledges receipt of corresponding page

                 <B>Notes:</B>
                        Acknowledge is used by the autonegotiation function to indicate that a device has successfully received its link partners link code word.   */
      unsigned int   linkPartnerExtendedNextPageAcknowledge : 1;    /* 07.0019.E  RO       */
                     /* 1 = Link Partner acknowledges receipt of corresponding page  */
                    /*! \brief 07.0019.F RO Link Partner Next Page
                        AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_EUR.u0.bits_0.linkPartnerNextPage

                        

                        1 = Next page ability
  */
      unsigned int   linkPartnerNextPage : 1;    /* 07.0019.F  RO       */
                     /* 1 = Next page ability  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationLinkPartnerExtendedNextPageAbilityRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Link Partner Extended Next Page Unformatted Code Register: 07.001A */
/*                  Autonegotiation Link Partner Extended Next Page Unformatted Code Register: 07.001A */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Link Partner Extended Next Page Unformatted Code Register */
  union
  {
    struct
    {
                    /*! \brief 07.001A.F:0 RO Link Partner Unformatted Code Field 1 [F:0]
                        AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_EUR.u0.bits_0.linkPartnerUnformattedCodeField_1

                        

                        [F:0] = Unformatted Code Field 1 [15:0]
                        
  */
      unsigned int   linkPartnerUnformattedCodeField_1 : 16;    /* 07.001A.F:0  RO       */
                     /* [F:0] = Unformatted Code Field 1 [15:0]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Link Partner Extended Next Page Unformatted Code Register */
  union
  {
    struct
    {
                    /*! \brief 07.001B.F:0 RO Link Partner Unformatted Code Field 2 [F:0]
                        AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_EUR.u1.bits_1.linkPartnerUnformattedCodeField_2

                        

                        [F:0] = Unformatted Code Field 2 [15:0]
                        
  */
      unsigned int   linkPartnerUnformattedCodeField_2 : 16;    /* 07.001B.F:0  RO       */
                     /* [F:0] = Unformatted Code Field 2 [15:0]
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_AutonegotiationLinkPartnerExtendedNextPageUnformattedCodeRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation 10GBASE-T Control Register: 07.0020 */
/*                  Autonegotiation 10GBASE-T Control Register: 07.0020 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation 10GBASE-T Control Register */
  union
  {
    struct
    {
                    /*! \brief 07.0020.0 R/WPD LD Loop Timing Ability
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0.ldLoopTimingAbility

                        Provisionable Default = 0x1

                        1 = Advertise PHY as capable of loop timing
                        0 = Do not advertise PHY as capable of loop timing
  */
      unsigned int   ldLoopTimingAbility : 1;    /* 07.0020.0  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = Advertise PHY as capable of loop timing
                        0 = Do not advertise PHY as capable of loop timing  */
                    /*! \brief 07.0020.1 R/WPD LD Fast Retrain Ability
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0.ldFastRetrainAbility

                        Provisionable Default = 0x0

                        1 = Advertise PHY as 10GBASE-T fast retrain capable
                        0 = Do not advertise PHY as 10GBASE-T fast retrain capable
  */
      unsigned int   ldFastRetrainAbility : 1;    /* 07.0020.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise PHY as 10GBASE-T fast retrain capable
                        0 = Do not advertise PHY as 10GBASE-T fast retrain capable  */
                    /*! \brief 07.0020.2 R/WPD LD PMA Training Reset Request
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0.ldPmaTrainingResetRequest

                        Provisionable Default = 0x0

                        1 = Local device requests that Link Partner reset PMA training PRBS every frame
                        0 = Local device requests that Link Partner run PMA training PRBS continuously
  */
      unsigned int   ldPmaTrainingResetRequest : 1;    /* 07.0020.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Local device requests that Link Partner reset PMA training PRBS every frame
                        0 = Local device requests that Link Partner run PMA training PRBS continuously  */
                    /*! \brief 07.0020.3 R/WPD 40GBASE-T Fast Retrain Ability
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0._40gbase_tFastRetrainAbility

                        Provisionable Default = 0x0

                        1 = Advertise PHY as 40GBASE-T fast retrain capable
                        0 = Do not advertise PHY as 40GBASE-T fast retrain capable
  */
      unsigned int   _40gbase_tFastRetrainAbility : 1;    /* 07.0020.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise PHY as 40GBASE-T fast retrain capable
                        0 = Do not advertise PHY as 40GBASE-T fast retrain capable  */
                    /*! \brief 07.0020.4 R/WPD Reserved_20_4
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0.reserved204

                        Provisionable Default = 0x0

                        Reserved bit 4
  */
      unsigned int   reserved204 : 1;    /* 07.0020.4  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bit 4  */
                    /*! \brief 07.0020.5 R/WPD 2.5GBASE-T Fast Retrain Ability
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0._2_5gbase_tFastRetrainAbility

                        Provisionable Default = 0x0

                        1 = Advertise PHY as 2.5GBASE-T fast retrain capable
                        0 = Do not advertise PHY as 2.5GBASE-T fast retrain capable
  */
      unsigned int   _2_5gbase_tFastRetrainAbility : 1;    /* 07.0020.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise PHY as 2.5GBASE-T fast retrain capable
                        0 = Do not advertise PHY as 2.5GBASE-T fast retrain capable  */
                    /*! \brief 07.0020.6 R/WPD 5GBASE-T Fast Retrain Ability
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0._5gbase_tFastRetrainAbility

                        Provisionable Default = 0x0

                        1 = Advertise PHY as 5GBASE-T fast retrain capable
                        0 = Do not advertise PHY as 5GBASE-T fast retrain capable
  */
      unsigned int   _5gbase_tFastRetrainAbility : 1;    /* 07.0020.6  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise PHY as 5GBASE-T fast retrain capable
                        0 = Do not advertise PHY as 5GBASE-T fast retrain capable  */
                    /*! \brief 07.0020.7 R/WPD 2.5GBASE-T Ability
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0._2_5gbase_tAbility

                        Provisionable Default = 0x1

                        1 = Advertise PHY as 2.5GBASE-T capable
                        0 = Do not advertise PHY as 2.5GBASE-T capable
  */
      unsigned int   _2_5gbase_tAbility : 1;    /* 07.0020.7  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = Advertise PHY as 2.5GBASE-T capable
                        0 = Do not advertise PHY as 2.5GBASE-T capable  */
                    /*! \brief 07.0020.8 R/WPD 5GBASE-T Ability
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0._5gbase_tAbility

                        Provisionable Default = 0x1

                        1 = Advertise PHY as 5GBASE-T capable
                        0 = Do not advertise PHY as 5GBASE-T capable
  */
      unsigned int   _5gbase_tAbility : 1;    /* 07.0020.8  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = Advertise PHY as 5GBASE-T capable
                        0 = Do not advertise PHY as 5GBASE-T capable  */
                    /*! \brief 07.0020.9 R/WPD 25GBASE-T Fast Retrain Ability
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0._25gbase_tFastRetrainAbility

                        Provisionable Default = 0x0

                        1 = Advertise PHY as 25GBASE-T fast retrain capable
                        0 = Do not advertise PHY as 25GBASE-T fast retrain capable
  */
      unsigned int   _25gbase_tFastRetrainAbility : 1;    /* 07.0020.9  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise PHY as 25GBASE-T fast retrain capable
                        0 = Do not advertise PHY as 25GBASE-T fast retrain capable  */
                    /*! \brief 07.0020.A R/WPD 25GBASE-T Ability
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0._25gbase_tAbility

                        Provisionable Default = 0x0

                        1 = Advertise PHY as 25GBASE-T capable
                        0 = Do not advertise PHY as 25GBASE-T capable
  */
      unsigned int   _25gbase_tAbility : 1;    /* 07.0020.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise PHY as 25GBASE-T capable
                        0 = Do not advertise PHY as 25GBASE-T capable  */
                    /*! \brief 07.0020.B R/WPD 40GBASE-T Ability
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0._40gbase_tAbility

                        Provisionable Default = 0x0

                        1 = Advertise PHY as 40GBASE-T capable
                        0 = Do not advertise PHY as 40GBASE-T capable
  */
      unsigned int   _40gbase_tAbility : 1;    /* 07.0020.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise PHY as 40GBASE-T capable
                        0 = Do not advertise PHY as 40GBASE-T capable  */
                    /*! \brief 07.0020.C R/WPD 10GBASE-T Ability
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0._10gbase_tAbility

                        Provisionable Default = 0x1

                        1 = Advertise PHY as 10GBASE-T capable
                        0 = Do not advertise PHY as 10GBASE-T capable
  */
      unsigned int   _10gbase_tAbility : 1;    /* 07.0020.C  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = Advertise PHY as 10GBASE-T capable
                        0 = Do not advertise PHY as 10GBASE-T capable  */
                    /*! \brief 07.0020.D R/WPD Port Type
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0.portType

                        Provisionable Default = 0x0

                        1 = Multiport device
                        0 = Single port device
  */
      unsigned int   portType : 1;    /* 07.0020.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Multiport device
                        0 = Single port device  */
                    /*! \brief 07.0020.E R/WPD MASTER-SLAVE Configuration
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0.master_slaveConfiguration

                        Provisionable Default = 0x0

                        1 = MASTER
                        0 = SLAVE
  */
      unsigned int   master_slaveConfiguration : 1;    /* 07.0020.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = MASTER
                        0 = SLAVE  */
                    /*! \brief 07.0020.F R/WPD MASTER-SLAVE Manual Configuration Enable
                        AQ_Autonegotiation10GBaseT_ControlRegister_EUR.u0.bits_0.master_slaveManualConfigurationEnable

                        Provisionable Default = 0x0

                        1 = Enable MASTER-SLAVE Manual configuration
                        0 = Disable MASTER-SLAVE Manual configuration
  */
      unsigned int   master_slaveManualConfigurationEnable : 1;    /* 07.0020.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable MASTER-SLAVE Manual configuration
                        0 = Disable MASTER-SLAVE Manual configuration  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Autonegotiation10GBaseT_ControlRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation 10GBASE-T Status Register: 07.0021 */
/*                  Autonegotiation 10GBASE-T Status Register: 07.0021 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation 10GBASE-T Status Register */
  union
  {
    struct
    {
                    /*! \brief 07.0021.0 RO Link Partner 40GBASE-T Fast Retrain Ability
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.linkPartner_40gbase_tFastRetrainAbility

                        

                        1 = Link partner is capable of 40GBASE-T fast retrain
                        0 = Link partner is not capable of 40GBASE-T fast retrain.
  */
      unsigned int   linkPartner_40gbase_tFastRetrainAbility : 1;    /* 07.0021.0  RO       */
                     /* 1 = Link partner is capable of 40GBASE-T fast retrain
                        0 = Link partner is not capable of 40GBASE-T fast retrain.  */
                    /*! \brief 07.0021.1 RO Link Partner 10GBASE-T Fast Retrain Ability
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.linkPartner10GBaseT_FastRetrainAbility

                        

                        1 = Link partner is capable of 10GBASE-T fast retrain
                        0 = Link partner is not capable of 10GBASE-T fast retrain.
  */
      unsigned int   linkPartner10GBaseT_FastRetrainAbility : 1;    /* 07.0021.1  RO       */
                     /* 1 = Link partner is capable of 10GBASE-T fast retrain
                        0 = Link partner is not capable of 10GBASE-T fast retrain.  */
                    /*! \brief 07.0021.2 RO Link Partner 25GBASE-T Fast Retrain Ability
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.linkPartner_25gbase_tFastRetrainAbility

                        

                        1 = Link partner is 25GBASE-T fast retrain capable
                        0 = Link partner is not 25GBASE-T fast retrain capable
  */
      unsigned int   linkPartner_25gbase_tFastRetrainAbility : 1;    /* 07.0021.2  RO       */
                     /* 1 = Link partner is 25GBASE-T fast retrain capable
                        0 = Link partner is not 25GBASE-T fast retrain capable  */
                    /*! \brief 07.0021.3 RO Link Partner 2.5GBASE-T Fast Retrain Ability
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.linkPartner_2_5gbase_tFastRetrainAbility

                        

                        1 = Link partner is 2.5GBASE-T fast retrain capable
                        0 = Link partner is not 2.5GBASE-T fast retrain capable
  */
      unsigned int   linkPartner_2_5gbase_tFastRetrainAbility : 1;    /* 07.0021.3  RO       */
                     /* 1 = Link partner is 2.5GBASE-T fast retrain capable
                        0 = Link partner is not 2.5GBASE-T fast retrain capable  */
                    /*! \brief 07.0021.4 RO Link Partner 5GBASE-T Fast Retrain Ability
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.linkPartner_5gbase_tFastRetrainAbility

                        

                        1 = Link partner is 5GBASE-T fast retrain capable
                        0 = Link partner is not 5GBASE-T fast retrain capable
  */
      unsigned int   linkPartner_5gbase_tFastRetrainAbility : 1;    /* 07.0021.4  RO       */
                     /* 1 = Link partner is 5GBASE-T fast retrain capable
                        0 = Link partner is not 5GBASE-T fast retrain capable  */
                    /*! \brief 07.0021.5 RO Link Partner 2.5GBASE-T Ability
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.linkPartner_2_5gbase_tAbility

                        

                        1 = Link partner is 2.5GBASE-T capable
                        0 = Link partner is not 2.5GBASE-T capable
  */
      unsigned int   linkPartner_2_5gbase_tAbility : 1;    /* 07.0021.5  RO       */
                     /* 1 = Link partner is 2.5GBASE-T capable
                        0 = Link partner is not 2.5GBASE-T capable  */
                    /*! \brief 07.0021.6 RO Link Partner 5GBASE-T Ability
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.linkPartner_5gbase_tAbility

                        

                        1 = Link partner is 5GBASE-T capable
                        0 = Link partner is not 5GBASE-T capable
  */
      unsigned int   linkPartner_5gbase_tAbility : 1;    /* 07.0021.6  RO       */
                     /* 1 = Link partner is 5GBASE-T capable
                        0 = Link partner is not 5GBASE-T capable  */
                    /*! \brief 07.0021.7 RO Link Partner 25GBASE-T Ability
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.linkPartner_25gbase_tAbility

                        

                        1 = Link partner is 25GBASE-T capable
                        0 = Link partner is not 25GBASE-T capable
  */
      unsigned int   linkPartner_25gbase_tAbility : 1;    /* 07.0021.7  RO       */
                     /* 1 = Link partner is 25GBASE-T capable
                        0 = Link partner is not 25GBASE-T capable  */
                    /*! \brief 07.0021.8 RO Link Partner 40GBASE-T Ability
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.linkPartner_40gbase_tAbility

                        

                        1 = Link partner is 40GBASE-T capable
                        0 = Link partner is not 40GBASE-T capable
  */
      unsigned int   linkPartner_40gbase_tAbility : 1;    /* 07.0021.8  RO       */
                     /* 1 = Link partner is 40GBASE-T capable
                        0 = Link partner is not 40GBASE-T capable  */
                    /*! \brief 07.0021.9 RO Link Partner Training Reset Request
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.linkPartnerTrainingResetRequest

                        

                        1 = Link partner has requested that PMA PRBS training be reset every frame
                        0 = Link partner has requested that PMA PRBS training run continuously.
  */
      unsigned int   linkPartnerTrainingResetRequest : 1;    /* 07.0021.9  RO       */
                     /* 1 = Link partner has requested that PMA PRBS training be reset every frame
                        0 = Link partner has requested that PMA PRBS training run continuously.  */
                    /*! \brief 07.0021.A RO Link Partner Loop Timing Ability
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.linkPartnerLoopTimingAbility

                        

                        1 = Link partner is capable of loop timing
                        0 = Link partner is not capable of loop timing
  */
      unsigned int   linkPartnerLoopTimingAbility : 1;    /* 07.0021.A  RO       */
                     /* 1 = Link partner is capable of loop timing
                        0 = Link partner is not capable of loop timing  */
                    /*! \brief 07.0021.B RO Link Partner 10GBASE-T Ability
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.linkPartner10GBaseT_Ability

                        

                        1 = Link partner is 10GBASE-T capable
                        0 = Link partner is not 10GBASE-T capable

                 <B>Notes:</B>
                        This bit is only valid when the Page received bit 7.1.6 is set to 1.  */
      unsigned int   linkPartner10GBaseT_Ability : 1;    /* 07.0021.B  RO       */
                     /* 1 = Link partner is 10GBASE-T capable
                        0 = Link partner is not 10GBASE-T capable  */
                    /*! \brief 07.0021.C RO Remote Receiver Status
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.remoteReceiverStatus

                        

                        1 = Remote receiver OK
                        0 = Remote receiver not OK

                 <B>Notes:</B>
                        Set by microcontroller  */
      unsigned int   remoteReceiverStatus : 1;    /* 07.0021.C  RO       */
                     /* 1 = Remote receiver OK
                        0 = Remote receiver not OK  */
                    /*! \brief 07.0021.D RO Local Receiver Status
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.localReceiverStatus

                        

                        1 = Local receiver OK
                        0 = Local receiver not OK

                 <B>Notes:</B>
                        Set by microcontroller  */
      unsigned int   localReceiverStatus : 1;    /* 07.0021.D  RO       */
                     /* 1 = Local receiver OK
                        0 = Local receiver not OK  */
                    /*! \brief 07.0021.E RO MASTER-SLAVE Configuration Resolution
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.master_slaveConfigurationResolution

                        

                        1 = Local PHY resolved to MASTER
                        0 = Local PHY resolved to SLAVE
  */
      unsigned int   master_slaveConfigurationResolution : 1;    /* 07.0021.E  RO       */
                     /* 1 = Local PHY resolved to MASTER
                        0 = Local PHY resolved to SLAVE  */
                    /*! \brief 07.0021.F LH MASTER-SLAVE Configuration Fault
                        AQ_Autonegotiation10GBaseT_StatusRegister_EUR.u0.bits_0.master_slaveConfigurationFault

                        

                        1 = MASTER-SLAVE configuration fault
  */
      unsigned int   master_slaveConfigurationFault : 1;    /* 07.0021.F  LH       */
                     /* 1 = MASTER-SLAVE configuration fault  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Autonegotiation10GBaseT_StatusRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Reserved 22 Register: 07.0022 */
/*                  Autonegotiation Reserved 22 Register: 07.0022 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Reserved 22 Register */
  union
  {
    struct
    {
                    /*! \brief 07.0022.F:0 R/W Reserved_22 [F:0]
                        AQ_AutonegotiationReserved_22Register_EUR.u0.bits_0.reserved22

                        Default = 0x0000

                        Reserved bits 15 to 0
  */
      unsigned int   reserved22 : 16;    /* 07.0022.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits 15 to 0  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationReserved_22Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Reserved 23 Register: 07.0023 */
/*                  Autonegotiation Reserved 23 Register: 07.0023 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Reserved 23 Register */
  union
  {
    struct
    {
                    /*! \brief 07.0023.F:0 R/W Reserved_23 [F:0]
                        AQ_AutonegotiationReserved_23Register_EUR.u0.bits_0.reserved23

                        Default = 0x0000

                        Reserved bits 15 to 0
  */
      unsigned int   reserved23 : 16;    /* 07.0023.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits 15 to 0  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationReserved_23Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Reserved 31 Register: 07.0031 */
/*                  Autonegotiation Reserved 31 Register: 07.0031 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Reserved 31 Register */
  union
  {
    struct
    {
                    /*! \brief 07.0031.F:0 R/W Reserved_31 [F:0]
                        AQ_AutonegotiationReserved_31Register_EUR.u0.bits_0.reserved31

                        Default = 0x0000

                        Reserved bits 15 to 0
  */
      unsigned int   reserved31 : 16;    /* 07.0031.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits 15 to 0  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationReserved_31Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Reserved 32 Register: 07.0032 */
/*                  Autonegotiation Reserved 32 Register: 07.0032 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Reserved 32 Register */
  union
  {
    struct
    {
                    /*! \brief 07.0032.F:0 R/W Reserved_32 [F:0]
                        AQ_AutonegotiationReserved_32Register_EUR.u0.bits_0.reserved32

                        Default = 0x0000

                        Reserved bits 15 to 0
  */
      unsigned int   reserved32 : 16;    /* 07.0032.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits 15 to 0  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationReserved_32Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation EEE Advertisement Register: 07.003C */
/*                  Autonegotiation EEE Advertisement Register: 07.003C */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation EEE Advertisement Register */
  union
  {
    struct
    {
                    /*! \brief 07.003C.0 R/W Reserved_3C 0
                        AQ_AutonegotiationEeeAdvertisementRegister_EUR.u0.bits_0.reserved3c_0

                        Default = 0x0

                        Reserved bit 0
  */
      unsigned int   reserved3c_0 : 1;    /* 07.003C.0  R/W      Default = 0x0 */
                     /* Reserved bit 0  */
                    /*! \brief 07.003C.1 R/W 100BASE-TX EEE
                        AQ_AutonegotiationEeeAdvertisementRegister_EUR.u0.bits_0._100base_txEee

                        Default = 0x0

                        1 = Advertise that the 100BASE-TX has EEE capability
                        0 = Do not advertise that the 100BASE-TX has EEE capability
  */
      unsigned int   _100base_txEee : 1;    /* 07.003C.1  R/W      Default = 0x0 */
                     /* 1 = Advertise that the 100BASE-TX has EEE capability
                        0 = Do not advertise that the 100BASE-TX has EEE capability  */
                    /*! \brief 07.003C.2 R/W 1000BASE-T EEE
                        AQ_AutonegotiationEeeAdvertisementRegister_EUR.u0.bits_0._1000base_tEee

                        Default = 0x1

                        1 = Advertise that the 1000BASE-T has EEE capability
                        0 = Do not advertise that the 1000BASE-T has EEE capability
  */
      unsigned int   _1000base_tEee : 1;    /* 07.003C.2  R/W      Default = 0x1 */
                     /* 1 = Advertise that the 1000BASE-T has EEE capability
                        0 = Do not advertise that the 1000BASE-T has EEE capability  */
                    /*! \brief 07.003C.3 R/W 10GBASE-T EEE
                        AQ_AutonegotiationEeeAdvertisementRegister_EUR.u0.bits_0._10gbase_tEee

                        Default = 0x1

                        1 = Advertise that the 10GBASE-T has EEE capability
                        0 = Do not advertise that the 10GBASE-T has EEE capability
  */
      unsigned int   _10gbase_tEee : 1;    /* 07.003C.3  R/W      Default = 0x1 */
                     /* 1 = Advertise that the 10GBASE-T has EEE capability
                        0 = Do not advertise that the 10GBASE-T has EEE capability  */
                    /*! \brief 07.003C.4 R/W 1000BASE-KX EEE
                        AQ_AutonegotiationEeeAdvertisementRegister_EUR.u0.bits_0._1000base_kxEee

                        Default = 0x0

                        1 = Advertise that the 1000BASE-KX has EEE capability
                        0 = Do not advertise that the 1000BASE-KX has EEE capability
  */
      unsigned int   _1000base_kxEee : 1;    /* 07.003C.4  R/W      Default = 0x0 */
                     /* 1 = Advertise that the 1000BASE-KX has EEE capability
                        0 = Do not advertise that the 1000BASE-KX has EEE capability  */
                    /*! \brief 07.003C.5 R/W 10GBASE-KX4 EEE
                        AQ_AutonegotiationEeeAdvertisementRegister_EUR.u0.bits_0._10gbase_kx4Eee

                        Default = 0x0

                        1 = Advertise that the 10GBASE-KX4 has EEE capability
                        0 = Do not advertise that the 10GBASE-KX4 has EEE capability
  */
      unsigned int   _10gbase_kx4Eee : 1;    /* 07.003C.5  R/W      Default = 0x0 */
                     /* 1 = Advertise that the 10GBASE-KX4 has EEE capability
                        0 = Do not advertise that the 10GBASE-KX4 has EEE capability  */
                    /*! \brief 07.003C.6 R/W 10GBASE-KR EEE
                        AQ_AutonegotiationEeeAdvertisementRegister_EUR.u0.bits_0._10gbase_krEee

                        Default = 0x0

                        1 = Advertise that the 10GBASE-KR has EEE capability
                        0 = Do not advertise that the 10GBASE-KR has EEE capability
  */
      unsigned int   _10gbase_krEee : 1;    /* 07.003C.6  R/W      Default = 0x0 */
                     /* 1 = Advertise that the 10GBASE-KR has EEE capability
                        0 = Do not advertise that the 10GBASE-KR has EEE capability  */
                    /*! \brief 07.003C.F:7 R/W Reserved_3C [F:7]
                        AQ_AutonegotiationEeeAdvertisementRegister_EUR.u0.bits_0.reserved3c

                        Default = 0x000

                        Reserved bits 15 to 7
  */
      unsigned int   reserved3c : 9;    /* 07.003C.F:7  R/W      Default = 0x000 */
                     /* Reserved bits 15 to 7  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationEeeAdvertisementRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation EEE Link Partner Ability Register: 07.003D */
/*                  Autonegotiation EEE Link Partner Ability Register: 07.003D */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation EEE Link Partner Ability Register */
  union
  {
    struct
    {
                    /*! \brief 07.003D.0 RO Reserved_3D 0
                        AQ_AutonegotiationEeeLinkPartnerAbilityRegister_EUR.u0.bits_0.reserved3d_0

                        

                        Reserved bit 0
  */
      unsigned int   reserved3d_0 : 1;    /* 07.003D.0  RO       */
                     /* Reserved bit 0  */
                    /*! \brief 07.003D.1 RO Link Partner 100BASE-TX EEE
                        AQ_AutonegotiationEeeLinkPartnerAbilityRegister_EUR.u0.bits_0.linkPartner_100base_txEee

                        

                        1 = Link partner is advertising that its 100BASE-TX has EEE capability
                        0 = Link partner is advertising that its 100BASE-TX does not have EEE capability
  */
      unsigned int   linkPartner_100base_txEee : 1;    /* 07.003D.1  RO       */
                     /* 1 = Link partner is advertising that its 100BASE-TX has EEE capability
                        0 = Link partner is advertising that its 100BASE-TX does not have EEE capability  */
                    /*! \brief 07.003D.2 RO Link Partner 1000BASE-T EEE
                        AQ_AutonegotiationEeeLinkPartnerAbilityRegister_EUR.u0.bits_0.linkPartner1000BaseT_Eee

                        

                        1 = Link partner is advertising that its 1000BASE-T has EEE capability
                        0 = Link partner is advertising that its 1000BASE-T does not have EEE capability
  */
      unsigned int   linkPartner1000BaseT_Eee : 1;    /* 07.003D.2  RO       */
                     /* 1 = Link partner is advertising that its 1000BASE-T has EEE capability
                        0 = Link partner is advertising that its 1000BASE-T does not have EEE capability  */
                    /*! \brief 07.003D.3 RO Link Partner 10GBASE-T EEE
                        AQ_AutonegotiationEeeLinkPartnerAbilityRegister_EUR.u0.bits_0.linkPartner10GBaseT_Eee

                        

                        1 = Link partner is advertising that its 10GBASE-T has EEE capability
                        0 = Link partner is advertising that its 10GBASE-T does not have EEE capability
  */
      unsigned int   linkPartner10GBaseT_Eee : 1;    /* 07.003D.3  RO       */
                     /* 1 = Link partner is advertising that its 10GBASE-T has EEE capability
                        0 = Link partner is advertising that its 10GBASE-T does not have EEE capability  */
                    /*! \brief 07.003D.4 RO Link Partner 1000BASE-KX EEE
                        AQ_AutonegotiationEeeLinkPartnerAbilityRegister_EUR.u0.bits_0.linkPartner_1000base_kxEee

                        

                        1 = Link partner is advertising that its 1000BASE-KX has EEE capability
                        0 = Link partner is advertising that its 1000BASE-KX does not have EEE capability
  */
      unsigned int   linkPartner_1000base_kxEee : 1;    /* 07.003D.4  RO       */
                     /* 1 = Link partner is advertising that its 1000BASE-KX has EEE capability
                        0 = Link partner is advertising that its 1000BASE-KX does not have EEE capability  */
                    /*! \brief 07.003D.5 RO Link Partner 10GBASE-KX4 EEE
                        AQ_AutonegotiationEeeLinkPartnerAbilityRegister_EUR.u0.bits_0.linkPartner10GBaseK_x4Eee

                        

                        1 = Link partner is advertising that its 10GBASE-KX4 has EEE capability
                        0 = Link partner is advertising that its 10GBASE-KX4 does not have EEE capability
  */
      unsigned int   linkPartner10GBaseK_x4Eee : 1;    /* 07.003D.5  RO       */
                     /* 1 = Link partner is advertising that its 10GBASE-KX4 has EEE capability
                        0 = Link partner is advertising that its 10GBASE-KX4 does not have EEE capability  */
                    /*! \brief 07.003D.6 RO Link Partner 10GBASE-KR EEE
                        AQ_AutonegotiationEeeLinkPartnerAbilityRegister_EUR.u0.bits_0.linkPartner10GBaseK_rEee

                        

                        1 = Link partner is advertising that its 10GBASE-KR has EEE capability
                        0 = Link partner is advertising that its 10GBASE-KR does not have EEE capability
  */
      unsigned int   linkPartner10GBaseK_rEee : 1;    /* 07.003D.6  RO       */
                     /* 1 = Link partner is advertising that its 10GBASE-KR has EEE capability
                        0 = Link partner is advertising that its 10GBASE-KR does not have EEE capability  */
                    /*! \brief 07.003D.F:7 RO Reserved_3D [F:7]
                        AQ_AutonegotiationEeeLinkPartnerAbilityRegister_EUR.u0.bits_0.reserved3d

                        

                        Reserved bits 15 to 7
  */
      unsigned int   reserved3d : 9;    /* 07.003D.F:7  RO       */
                     /* Reserved bits 15 to 7  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationEeeLinkPartnerAbilityRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation EEE Advertisement 2 Register: 07.003E */
/*                  Autonegotiation EEE Advertisement 2 Register: 07.003E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation EEE Advertisement 2 Register */
  union
  {
    struct
    {
                    /*! \brief 07.003E.0 R/W 2.5GBASE-T EEE
                        AQ_AutonegotiationEeeAdvertisement_2Register_EUR.u0.bits_0._2_5gbase_tEee

                        Default = 0x1

                        1 = Advertise that the 2.5GBASE-T has EEE capability
                        0 = Do not advertise that the 2.5GBASE-T has EEE capability
  */
      unsigned int   _2_5gbase_tEee : 1;    /* 07.003E.0  R/W      Default = 0x1 */
                     /* 1 = Advertise that the 2.5GBASE-T has EEE capability
                        0 = Do not advertise that the 2.5GBASE-T has EEE capability  */
                    /*! \brief 07.003E.1 R/W 5GBASE-T EEE
                        AQ_AutonegotiationEeeAdvertisement_2Register_EUR.u0.bits_0._5gbase_tEee

                        Default = 0x1

                        1 = Advertise that the 5BASE-T has EEE capability
                        0 = Do not advertise that the 5BASE-T has EEE capability
  */
      unsigned int   _5gbase_tEee : 1;    /* 07.003E.1  R/W      Default = 0x1 */
                     /* 1 = Advertise that the 5BASE-T has EEE capability
                        0 = Do not advertise that the 5BASE-T has EEE capability  */
                    /*! \brief 07.003E.F:2 R/W Reserved_3E [F:2]
                        AQ_AutonegotiationEeeAdvertisement_2Register_EUR.u0.bits_0.reserved3e

                        Default = 0x0000

                        Reserved bits 15 to 2
  */
      unsigned int   reserved3e : 14;    /* 07.003E.F:2  R/W      Default = 0x0000 */
                     /* Reserved bits 15 to 2  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationEeeAdvertisement_2Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation EEE Link Partner Ability 2 Register: 07.003F */
/*                  Autonegotiation EEE Link Partner Ability 2 Register: 07.003F */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation EEE Link Partner Ability 2 Register */
  union
  {
    struct
    {
                    /*! \brief 07.003F.0 RO Link Partner 2.5GBASE-T EEE
                        AQ_AutonegotiationEeeLinkPartnerAbility_2Register_EUR.u0.bits_0.linkPartner_2_5gbase_tEee

                        

                        1 = Link partner is advertising that its 2.5GBASE-T has EEE capability
                        0 = Link partner is advertising that its 2.5GBASE-T does not have EEE capability
  */
      unsigned int   linkPartner_2_5gbase_tEee : 1;    /* 07.003F.0  RO       */
                     /* 1 = Link partner is advertising that its 2.5GBASE-T has EEE capability
                        0 = Link partner is advertising that its 2.5GBASE-T does not have EEE capability  */
                    /*! \brief 07.003F.1 RO Link Partner 5GBASE-T EEE
                        AQ_AutonegotiationEeeLinkPartnerAbility_2Register_EUR.u0.bits_0.linkPartner_5gbase_tEee

                        

                        1 = Link partner is advertising that its 5BASE-T has EEE capability
                        0 = Link partner is advertising that its 5BASE-T does not have EEE capability
  */
      unsigned int   linkPartner_5gbase_tEee : 1;    /* 07.003F.1  RO       */
                     /* 1 = Link partner is advertising that its 5BASE-T has EEE capability
                        0 = Link partner is advertising that its 5BASE-T does not have EEE capability  */
                    /*! \brief 07.003F.F:2 RO Reserved_3F [F:2]
                        AQ_AutonegotiationEeeLinkPartnerAbility_2Register_EUR.u0.bits_0.reserved3f

                        

                        Reserved bits 15 to 2
  */
      unsigned int   reserved3f : 14;    /* 07.003F.F:2  RO       */
                     /* Reserved bits 15 to 2  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationEeeLinkPartnerAbility_2Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation 10GBASE-T Control 2 Register: 07.0040 */
/*                  Autonegotiation 10GBASE-T Control 2 Register: 07.0040 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation 10GBASE-T Control 2 Register */
  union
  {
    struct
    {
                    /*! \brief 07.0040.0 R/WPD 40GBASE-T THP Bypass Request
                        AQ_Autonegotiation10GBaseT_Control_2Register_EUR.u0.bits_0._40gbase_tTHP_BypassRequest

                        Provisionable Default = 0x0

                        1 = Request to reset THP during fast retrain for 40GBASE-T
                        0 = Request not to reset THP during fast retrain for 40GBASE-T
  */
      unsigned int   _40gbase_tTHP_BypassRequest : 1;    /* 07.0040.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Request to reset THP during fast retrain for 40GBASE-T
                        0 = Request not to reset THP during fast retrain for 40GBASE-T  */
                    /*! \brief 07.0040.1 R/WPD 25GBASE-T THP Bypass Request
                        AQ_Autonegotiation10GBaseT_Control_2Register_EUR.u0.bits_0._25gbase_tTHP_BypassRequest

                        Provisionable Default = 0x0

                        1 = Request to reset THP during fast retrain for 25GBASE-T
                        0 = Request not to reset THP during fast retrain for 25GBASE-T
  */
      unsigned int   _25gbase_tTHP_BypassRequest : 1;    /* 07.0040.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Request to reset THP during fast retrain for 25GBASE-T
                        0 = Request not to reset THP during fast retrain for 25GBASE-T  */
                    /*! \brief 07.0040.2 R/WPD 5GBASE-T THP Bypass Request
                        AQ_Autonegotiation10GBaseT_Control_2Register_EUR.u0.bits_0._5gbase_tTHP_BypassRequest

                        Provisionable Default = 0x0

                        1 = Request to reset THP during fast retrain for 5GBASE-T
                        0 = Request not to reset THP during fast retrain for 5GBASE-T
  */
      unsigned int   _5gbase_tTHP_BypassRequest : 1;    /* 07.0040.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Request to reset THP during fast retrain for 5GBASE-T
                        0 = Request not to reset THP during fast retrain for 5GBASE-T  */
                    /*! \brief 07.0040.3 R/WPD 2.5GBASE-T THP Bypass Request
                        AQ_Autonegotiation10GBaseT_Control_2Register_EUR.u0.bits_0._2_5gbase_tTHP_BypassRequest

                        Provisionable Default = 0x0

                        1 = Request to reset THP during fast retrain for 2.5GBASE-T
                        0 = Request not to reset THP during fast retrain for 2.5GBASE-T
  */
      unsigned int   _2_5gbase_tTHP_BypassRequest : 1;    /* 07.0040.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Request to reset THP during fast retrain for 2.5GBASE-T
                        0 = Request not to reset THP during fast retrain for 2.5GBASE-T  */
                    /*! \brief 07.0040.F:4 R/W Reserved_40 [F:4]
                        AQ_Autonegotiation10GBaseT_Control_2Register_EUR.u0.bits_0.reserved40

                        Default = 0x000

                        Reserved bits 15 to 4
  */
      unsigned int   reserved40 : 12;    /* 07.0040.F:4  R/W      Default = 0x000 */
                     /* Reserved bits 15 to 4  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Autonegotiation10GBaseT_Control_2Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation 10GBASE-T Status 2 Register: 07.0041 */
/*                  Autonegotiation 10GBASE-T Status 2 Register: 07.0041 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation 10GBASE-T Status 2 Register */
  union
  {
    struct
    {
                    /*! \brief 07.0041.0 RO Link Partner 40GBASE-T THP Bypass Request
                        AQ_Autonegotiation10GBaseT_Status_2Register_EUR.u0.bits_0.linkPartner_40gbase_tTHP_BypassRequest

                        

                        1 = Link Partner requests to reset THP during fast retrain for 40GBASE-T
                        0 = No Link Partner requests not to reset THP during fast retrain for 40GBASE-T
  */
      unsigned int   linkPartner_40gbase_tTHP_BypassRequest : 1;    /* 07.0041.0  RO       */
                     /* 1 = Link Partner requests to reset THP during fast retrain for 40GBASE-T
                        0 = No Link Partner requests not to reset THP during fast retrain for 40GBASE-T  */
                    /*! \brief 07.0041.1 RO Link Partner 25GBASE-T THP Bypass Request
                        AQ_Autonegotiation10GBaseT_Status_2Register_EUR.u0.bits_0.linkPartner_25gbase_tTHP_BypassRequest

                        

                        1 = Link Partner requests to reset THP during fast retrain for 25GBASE-T
                        0 = No Link Partner requests not to reset THP during fast retrain for 25GBASE-T
  */
      unsigned int   linkPartner_25gbase_tTHP_BypassRequest : 1;    /* 07.0041.1  RO       */
                     /* 1 = Link Partner requests to reset THP during fast retrain for 25GBASE-T
                        0 = No Link Partner requests not to reset THP during fast retrain for 25GBASE-T  */
                    /*! \brief 07.0041.2 RO Link Partner 5GBASE-T THP Bypass Request
                        AQ_Autonegotiation10GBaseT_Status_2Register_EUR.u0.bits_0.linkPartner_5gbase_tTHP_BypassRequest

                        

                        1 = Link Partner requests to reset THP during fast retrain or 5GBASE-T
                        0 = No Link Partner requests not to reset THP during fast retrain for 5GBASE-T
  */
      unsigned int   linkPartner_5gbase_tTHP_BypassRequest : 1;    /* 07.0041.2  RO       */
                     /* 1 = Link Partner requests to reset THP during fast retrain or 5GBASE-T
                        0 = No Link Partner requests not to reset THP during fast retrain for 5GBASE-T  */
                    /*! \brief 07.0041.3 RO Link Partner 2.5GBASE-T THP Bypass Request
                        AQ_Autonegotiation10GBaseT_Status_2Register_EUR.u0.bits_0.linkPartner_2_5gbase_tTHP_BypassRequest

                        

                        1 = Link Partner requests to reset THP during fast retrain for 2.5GBASE-T
                        0 = No Link Partner requests not to reset THP during fast retrain for 2.5GBASE-T
  */
      unsigned int   linkPartner_2_5gbase_tTHP_BypassRequest : 1;    /* 07.0041.3  RO       */
                     /* 1 = Link Partner requests to reset THP during fast retrain for 2.5GBASE-T
                        0 = No Link Partner requests not to reset THP during fast retrain for 2.5GBASE-T  */
                    /*! \brief 07.0041.F:4 RO Reserved_41 [F:4]
                        AQ_Autonegotiation10GBaseT_Status_2Register_EUR.u0.bits_0.reserved41

                        

                        Reserved bits 15 to 4
  */
      unsigned int   reserved41 : 12;    /* 07.0041.F:4  RO       */
                     /* Reserved bits 15 to 4  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Autonegotiation10GBaseT_Status_2Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Reserved 42 Register: 07.0042 */
/*                  Autonegotiation Reserved 42 Register: 07.0042 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Reserved 42 Register */
  union
  {
    struct
    {
                    /*! \brief 07.0042.F:0 R/W Reserved_42 [F:0]
                        AQ_AutonegotiationReserved_42Register_EUR.u0.bits_0.reserved42

                        Default = 0x0000

                        Reserved bits 15 to 0
  */
      unsigned int   reserved42 : 16;    /* 07.0042.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits 15 to 0  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationReserved_42Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Reserved 43 Register: 07.0043 */
/*                  Autonegotiation Reserved 43 Register: 07.0043 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Reserved 43 Register */
  union
  {
    struct
    {
                    /*! \brief 07.0043.F:0 R/W Reserved_43 [F:0]
                        AQ_AutonegotiationReserved_43Register_EUR.u0.bits_0.reserved43

                        Default = 0x0000

                        Reserved bits 15 to 0
  */
      unsigned int   reserved43 : 16;    /* 07.0043.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits 15 to 0  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationReserved_43Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Reserved 44 Register: 07.0044 */
/*                  Autonegotiation Reserved 44 Register: 07.0044 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Reserved 44 Register */
  union
  {
    struct
    {
                    /*! \brief 07.0044.F:0 R/W Reserved_44 [F:0]
                        AQ_AutonegotiationReserved_44Register_EUR.u0.bits_0.reserved44

                        Default = 0x0000

                        Reserved bits 15 to 0
  */
      unsigned int   reserved44 : 16;    /* 07.0044.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits 15 to 0  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationReserved_44Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Reserved 45 Register: 07.0045 */
/*                  Autonegotiation Reserved 45 Register: 07.0045 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Reserved 45 Register */
  union
  {
    struct
    {
                    /*! \brief 07.0045.F:0 R/W Reserved_45 [F:0]
                        AQ_AutonegotiationReserved_45Register_EUR.u0.bits_0.reserved45

                        Default = 0x0000

                        Reserved bits 15 to 0
  */
      unsigned int   reserved45 : 16;    /* 07.0045.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits 15 to 0  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationReserved_45Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                KR0 Autonegotiation Control: 07.C200 */
/*                  KR0 Autonegotiation Control: 07.C200 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of KR0 Autonegotiation Control */
  union
  {
    struct
    {
                    /*! \brief 07.C200.8:0 R/WPD Reserved 2 [8:0]
                        AQ_Kr0AutonegotiationControl_EUR.u0.bits_0.reserved_2

                        Provisionable Default = 0x000

                        Reserved for future use
                        
  */
      unsigned int   reserved_2 : 9;    /* 07.C200.8:0  R/WPD      Provisionable Default = 0x000 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C200.9 R/WSC Autonegotiation Restart
                        AQ_Kr0AutonegotiationControl_EUR.u0.bits_0.autonegotiationRestart

                        Default = 0x0

                        1 = Restart autonegotiation
                        0 = Normal operation
                        
  */
      unsigned int   autonegotiationRestart : 1;    /* 07.C200.9  R/WSC      Default = 0x0 */
                     /* 1 = Restart autonegotiation
                        0 = Normal operation
                          */
                    /*! \brief 07.C200.B:A R/WPD Reserved 1 [1:0]
                        AQ_Kr0AutonegotiationControl_EUR.u0.bits_0.reserved_1

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_1 : 2;    /* 07.C200.B:A  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C200.C R/WPD Autonegotiation Enable
                        AQ_Kr0AutonegotiationControl_EUR.u0.bits_0.autonegotiationEnable

                        Provisionable Default = 0x0

                        1 = Enable autonegotiation
                        0 = Disable autonegotiation
                        
  */
      unsigned int   autonegotiationEnable : 1;    /* 07.C200.C  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable autonegotiation
                        0 = Disable autonegotiation
                          */
                    /*! \brief 07.C200.E:D R/WPD Reserved 0 [1:0]
                        AQ_Kr0AutonegotiationControl_EUR.u0.bits_0.reserved_0

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_0 : 2;    /* 07.C200.E:D  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C200.F R/WSC Reset
                        AQ_Kr0AutonegotiationControl_EUR.u0.bits_0.reset

                        Default = 0x1

                        1 = Autonegotiation reset
                        0 = Normal operation
                        
  */
      unsigned int   reset : 1;    /* 07.C200.F  R/WSC      Default = 0x1 */
                     /* 1 = Autonegotiation reset
                        0 = Normal operation
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Kr0AutonegotiationControl_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                KR0 Autonegotiation Status: 07.C201 */
/*                  KR0 Autonegotiation Status: 07.C201 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of KR0 Autonegotiation Status */
  union
  {
    struct
    {
                    /*! \brief 07.C201.0 ROS Link Partner Autonegotiation Ability
                        AQ_Kr0AutonegotiationStatus_EUR.u0.bits_0.linkPartnerAutonegotiationAbility

                        Default = 0x0

                        1 = Link partner is able to perform autonegotiation 
                        0 = Link partner is not able to perform autonegotiation
                        
  */
      unsigned int   linkPartnerAutonegotiationAbility : 1;    /* 07.C201.0  ROS      Default = 0x0 */
                     /* 1 = Link partner is able to perform autonegotiation 
                        0 = Link partner is not able to perform autonegotiation
                          */
                    /*! \brief 07.C201.2:1 R/WPD Reserved 3 [1:0]
                        AQ_Kr0AutonegotiationStatus_EUR.u0.bits_0.reserved_3

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_3 : 2;    /* 07.C201.2:1  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C201.3 ROS Autonegotiation Ability
                        AQ_Kr0AutonegotiationStatus_EUR.u0.bits_0.autonegotiationAbility

                        Default = 0x1

                        1 = PHY is able to perform autonegotiation 
                        0 = PHY is not able to perform autonegotiation 
                        

                 <B>Notes:</B>
                        Always set as 1 as the local device has autonegotiation  ability.  */
      unsigned int   autonegotiationAbility : 1;    /* 07.C201.3  ROS      Default = 0x1 */
                     /* 1 = PHY is able to perform autonegotiation 
                        0 = PHY is not able to perform autonegotiation 
                          */
                    /*! \brief 07.C201.4 R/WPD Reserved 2
                        AQ_Kr0AutonegotiationStatus_EUR.u0.bits_0.reserved_2

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_2 : 1;    /* 07.C201.4  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C201.5 LH Autonegotiation Complete
                        AQ_Kr0AutonegotiationStatus_EUR.u0.bits_0.autonegotiationComplete

                        

                        1 = Autonegotiation complete
                        0 = Normal operation
                        
  */
      unsigned int   autonegotiationComplete : 1;    /* 07.C201.5  LH       */
                     /* 1 = Autonegotiation complete
                        0 = Normal operation
                          */
                    /*! \brief 07.C201.6 LH Page Received
                        AQ_Kr0AutonegotiationStatus_EUR.u0.bits_0.pageReceived

                        

                        1 = A new DME page has been received
                        0 = Normal operation
                        
  */
      unsigned int   pageReceived : 1;    /* 07.C201.6  LH       */
                     /* 1 = A new DME page has been received
                        0 = Normal operation
                          */
                    /*! \brief 07.C201.8:7 R/WPD Reserved 1 [1:0]
                        AQ_Kr0AutonegotiationStatus_EUR.u0.bits_0.reserved_1

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_1 : 2;    /* 07.C201.8:7  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C201.9 LH Parallel Detection Fault
                        AQ_Kr0AutonegotiationStatus_EUR.u0.bits_0.parallelDetectionFault

                        

                        1 = Fault detected
                        0 = No fault detected
                        
  */
      unsigned int   parallelDetectionFault : 1;    /* 07.C201.9  LH       */
                     /* 1 = Fault detected
                        0 = No fault detected
                          */
                    /*! \brief 07.C201.F:A R/WPD Reserved 0 [5:0]
                        AQ_Kr0AutonegotiationStatus_EUR.u0.bits_0.reserved_0

                        Provisionable Default = 0x00

                        Reserved for future use
                        
  */
      unsigned int   reserved_0 : 6;    /* 07.C201.F:A  R/WPD      Provisionable Default = 0x00 */
                     /* Reserved for future use
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Kr0AutonegotiationStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                KR0 Autonegotiation Advertisement Word: 07.C210 */
/*                  KR0 Autonegotiation Advertisement Word: 07.C210 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of KR0 Autonegotiation Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C210.4:0 R/WPD Selector Field [4:0]
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u0.bits_0.selectorField

                        Provisionable Default = 0x01

                        This defines the device compatibility:
                        0x00 = Reserved
                        0x01 = IEEE 802.3
                        0x02 = IEEE 802.9 ISLAN-16T
                        0x03 = IEEE 802.5
                        0x04 = IEEE 1394
                        0x05 -> 0x1F = Reserved
                        

                 <B>Notes:</B>
                        This field should always be set to 0x01 as the PHY is only capable of handling 802.3 Ethernet.  */
      unsigned int   selectorField : 5;    /* 07.C210.4:0  R/WPD      Provisionable Default = 0x01 */
                     /* This defines the device compatibility:
                        0x00 = Reserved
                        0x01 = IEEE 802.3
                        0x02 = IEEE 802.9 ISLAN-16T
                        0x03 = IEEE 802.5
                        0x04 = IEEE 1394
                        0x05 -> 0x1F = Reserved
                          */
                    /*! \brief 07.C210.9:5 R/WPD Echoed Nonce [4:0]
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u0.bits_0.echoedNonce

                        Provisionable Default = 0x00

                        Echoed nonce
                        
  */
      unsigned int   echoedNonce : 5;    /* 07.C210.9:5  R/WPD      Provisionable Default = 0x00 */
                     /* Echoed nonce
                          */
                    /*! \brief 07.C210.B:A R/WPD Pause Capability [1:0]
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u0.bits_0.pauseCapability

                        Provisionable Default = 0x0

                        Bit B: PAUSE operation for full duplex links
                        Bit A: Asymmetric PAUSE operation for full duplex links
                        
  */
      unsigned int   pauseCapability : 2;    /* 07.C210.B:A  R/WPD      Provisionable Default = 0x0 */
                     /* Bit B: PAUSE operation for full duplex links
                        Bit A: Asymmetric PAUSE operation for full duplex links
                          */
                    /*! \brief 07.C210.C R/WPD Reserved 0
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u0.bits_0.reserved_0

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_0 : 1;    /* 07.C210.C  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C210.D R/W Remote Fault
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u0.bits_0.remoteFault

                        Default = 0x0

                        1 = Remote fault
                        

                 <B>Notes:</B>
                        The remote fault bit provides a standard transport mechanism for the transmission of simple fault information. When the RF bit in the received base link code word is set to 1, the RF bit will be set to 1.  */
      unsigned int   remoteFault : 1;    /* 07.C210.D  R/W      Default = 0x0 */
                     /* 1 = Remote fault
                          */
                    /*! \brief 07.C210.E R/WPD Acknowledge
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u0.bits_0.acknowledge

                        Provisionable Default = 0x0

                        1 = Acknowledge
                        0 = No fault detected
                        

                 <B>Notes:</B>
                        The Acknowledge (Ack) is used by the Autonegotiation  function to indicate that a device has successfully received its Link Partner's Link Code Word.  */
      unsigned int   acknowledge : 1;    /* 07.C210.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Acknowledge
                        0 = No fault detected
                          */
                    /*! \brief 07.C210.F R/WPD Next Page
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u0.bits_0.nextPage

                        Provisionable Default = 0x0

                        1 = Next page ability
                        0 = Next page ability not supported or not engaged
                        
  */
      unsigned int   nextPage : 1;    /* 07.C210.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Next page ability
                        0 = Next page ability not supported or not engaged
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of KR0 Autonegotiation Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C211.4:0 R/WPD Transmitted Nonce [4:0]
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u1.bits_1.transmittedNonce

                        Provisionable Default = 0x00

                        Transmitted nonce
                        
  */
      unsigned int   transmittedNonce : 5;    /* 07.C211.4:0  R/WPD      Provisionable Default = 0x00 */
                     /* Transmitted nonce
                          */
                    /*! \brief 07.C211.5 R/WPD Technology Ability Bit A0
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u1.bits_1.technologyAbilityBitA0

                        Provisionable Default = 0x1

                        1 = 10GBASE-KX is supported
                        0 = 10GBASE-KX is not supported
                        
  */
      unsigned int   technologyAbilityBitA0 : 1;    /* 07.C211.5  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = 10GBASE-KX is supported
                        0 = 10GBASE-KX is not supported
                          */
                    /*! \brief 07.C211.6 R/WPD Technology Ability Bit A1
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u1.bits_1.technologyAbilityBitA1

                        Provisionable Default = 0x0

                        1 = 10GBASE-KX4 is supported
                        0 = 10GBASE-KX4 is not supported
                        
  */
      unsigned int   technologyAbilityBitA1 : 1;    /* 07.C211.6  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = 10GBASE-KX4 is supported
                        0 = 10GBASE-KX4 is not supported
                          */
                    /*! \brief 07.C211.7 R/WPD Technology Ability Bit A2
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u1.bits_1.technologyAbilityBitA2

                        Provisionable Default = 0x1

                        1 = 10GBASE-KR is supported
                        0 = 10GBASE-KR is not supported
                        
  */
      unsigned int   technologyAbilityBitA2 : 1;    /* 07.C211.7  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = 10GBASE-KR is supported
                        0 = 10GBASE-KR is not supported
                          */
                    /*! \brief 07.C211.F:8 R/WPD Technology Ability Bits A3 to A10 [7:0]
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u1.bits_1.technologyAbilityBitsA3ToA10

                        Provisionable Default = 0x00

                        Reserved for future technology
                        
  */
      unsigned int   technologyAbilityBitsA3ToA10 : 8;    /* 07.C211.F:8  R/WPD      Provisionable Default = 0x00 */
                     /* Reserved for future technology
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of KR0 Autonegotiation Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C212.D:0 R/WPD Technology Ability Bits A11 to A24 [D:0]
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u2.bits_2.technologyAbilityBitsA11ToA24

                        Provisionable Default = 0x0000

                        Reserved for future technology
                        
  */
      unsigned int   technologyAbilityBitsA11ToA24 : 14;    /* 07.C212.D:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Reserved for future technology
                          */
                    /*! \brief 07.C212.E R/WPD FEC Ability
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u2.bits_2.fecAbility

                        Provisionable Default = 0x0

                        1 = 10GBASE-KR PHY has FEC capability.
                        0 = 10GBASE-KR PHY does not have FEC capability.
                        
  */
      unsigned int   fecAbility : 1;    /* 07.C212.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = 10GBASE-KR PHY has FEC capability.
                        0 = 10GBASE-KR PHY does not have FEC capability.
                          */
                    /*! \brief 07.C212.F R/WPD FEC Requested
                        AQ_Kr0AutonegotiationAdvertisementWord_EUR.u2.bits_2.fecRequested

                        Provisionable Default = 0x0

                        1 = Enable 10GBASE-KR FEC ability.
                        0 = Disable 10GBASE-KR FEC ability.
                        
  */
      unsigned int   fecRequested : 1;    /* 07.C212.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable 10GBASE-KR FEC ability.
                        0 = Disable 10GBASE-KR FEC ability.
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_Kr0AutonegotiationAdvertisementWord_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                KR0 Link Partner Autonegotiation Advertisement Word: 07.C213 */
/*                  KR0 Link Partner Autonegotiation Advertisement Word: 07.C213 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of KR0 Link Partner Autonegotiation Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C213.4:0 RO Link Partner Selector Field [4:0]
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.linkPartnerSelectorField

                        

                        This defines the device compatibility:
                        0x00 = Reserved
                        0x01 = IEEE 802.3
                        0x02 = IEEE 802.9 ISLAN-16T
                        0x03 = IEEE 802.5
                        0x04 = IEEE 1394
                        0x05 -> 0x1F = Reserved
                        

                 <B>Notes:</B>
                        This field should always be set to 0x01 as the PHY is only capable of handling 802.3 Ethernet.  */
      unsigned int   linkPartnerSelectorField : 5;    /* 07.C213.4:0  RO       */
                     /* This defines the device compatibility:
                        0x00 = Reserved
                        0x01 = IEEE 802.3
                        0x02 = IEEE 802.9 ISLAN-16T
                        0x03 = IEEE 802.5
                        0x04 = IEEE 1394
                        0x05 -> 0x1F = Reserved
                          */
                    /*! \brief 07.C213.9:5 RO Link Partner Echoed Nonce [4:0]
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.linkPartnerEchoedNonce

                        

                        Echoed nonce
                        
  */
      unsigned int   linkPartnerEchoedNonce : 5;    /* 07.C213.9:5  RO       */
                     /* Echoed nonce
                          */
                    /*! \brief 07.C213.B:A RO Link Partner Pause Capability [1:0]
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.linkPartnerPauseCapability

                        

                        Bit B: PAUSE operation for full duplex links
                        Bit A: Asymmetric PAUSE operation for full duplex links
                        
  */
      unsigned int   linkPartnerPauseCapability : 2;    /* 07.C213.B:A  RO       */
                     /* Bit B: PAUSE operation for full duplex links
                        Bit A: Asymmetric PAUSE operation for full duplex links
                          */
                    /*! \brief 07.C213.C RO Reserved 0
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.reserved_0

                        

                        Reserved for future use
                        
  */
      unsigned int   reserved_0 : 1;    /* 07.C213.C  RO       */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C213.D RO Link Partner Remote Fault
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.linkPartnerRemoteFault

                        

                        1 = Remote fault
                        

                 <B>Notes:</B>
                        The remote fault bit provides a standard transport mechanism for the transmission of simple fault information. When the RF bit in the received base link code word is set to 1, the RF bit will be set to 1.  */
      unsigned int   linkPartnerRemoteFault : 1;    /* 07.C213.D  RO       */
                     /* 1 = Remote fault
                          */
                    /*! \brief 07.C213.E RO Link Partner Acknowledge
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.linkPartnerAcknowledge

                        

                        1 = Acknowledge
                        0 = No fault detected
                        

                 <B>Notes:</B>
                        The Acknowledge (Ack) is used by the Autonegotiation  function to indicate that a device has successfully received its Link Partner's Link Code Word.  */
      unsigned int   linkPartnerAcknowledge : 1;    /* 07.C213.E  RO       */
                     /* 1 = Acknowledge
                        0 = No fault detected
                          */
                    /*! \brief 07.C213.F RO Link Partner Next Page
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.linkPartnerNextPage

                        

                        1 = Next page ability
                        0 = Next page ability not supported or not engaged
                        
  */
      unsigned int   linkPartnerNextPage : 1;    /* 07.C213.F  RO       */
                     /* 1 = Next page ability
                        0 = Next page ability not supported or not engaged
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of KR0 Link Partner Autonegotiation Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C214.4:0 RO Link Partner Transmitted Nonce [4:0]
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u1.bits_1.linkPartnerTransmittedNonce

                        

                        Transmitted nonce
                        
  */
      unsigned int   linkPartnerTransmittedNonce : 5;    /* 07.C214.4:0  RO       */
                     /* Transmitted nonce
                          */
                    /*! \brief 07.C214.5 RO Link Partner Technology Ability Bit A0
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u1.bits_1.linkPartnerTechnologyAbilityBitA0

                        

                        1 = 10GBASE-KX is supported
                        0 = 10GBASE-KX is not supported
                        
  */
      unsigned int   linkPartnerTechnologyAbilityBitA0 : 1;    /* 07.C214.5  RO       */
                     /* 1 = 10GBASE-KX is supported
                        0 = 10GBASE-KX is not supported
                          */
                    /*! \brief 07.C214.6 RO Link Partner Technology Ability bit A1
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u1.bits_1.linkPartnerTechnologyAbilityBitA1

                        

                        1 = 10GBASE-KX4 is supported
                        0 = 10GBASE-KX4 is not supported
                        
  */
      unsigned int   linkPartnerTechnologyAbilityBitA1 : 1;    /* 07.C214.6  RO       */
                     /* 1 = 10GBASE-KX4 is supported
                        0 = 10GBASE-KX4 is not supported
                          */
                    /*! \brief 07.C214.7 RO Link Partner Technology Ability bit A2
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u1.bits_1.linkPartnerTechnologyAbilityBitA2

                        

                        1 = 10GBASE-KR is supported
                        0 = 10GBASE-KR is not supported
                        
  */
      unsigned int   linkPartnerTechnologyAbilityBitA2 : 1;    /* 07.C214.7  RO       */
                     /* 1 = 10GBASE-KR is supported
                        0 = 10GBASE-KR is not supported
                          */
                    /*! \brief 07.C214.F:8 RO Link Partner Technology Ability bits A3 to A10 [7:0]
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u1.bits_1.linkPartnerTechnologyAbilityBitsA3ToA10

                        

                        Reserved for future technology
                        
  */
      unsigned int   linkPartnerTechnologyAbilityBitsA3ToA10 : 8;    /* 07.C214.F:8  RO       */
                     /* Reserved for future technology
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of KR0 Link Partner Autonegotiation Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C215.D:0 RO Link Partner Technology Ability Bits A11 to A24 [D:0]
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u2.bits_2.linkPartnerTechnologyAbilityBitsA11ToA24

                        

                        Reserved for future technology
                        
  */
      unsigned int   linkPartnerTechnologyAbilityBitsA11ToA24 : 14;    /* 07.C215.D:0  RO       */
                     /* Reserved for future technology
                          */
                    /*! \brief 07.C215.E RO Link Partner FEC Ability
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u2.bits_2.linkPartnerFecAbility

                        

                        1 = 10GBASE-KR PHY has FEC capability.
                        0 = 10GBASE-KR PHY does not have FEC capability.
                        
  */
      unsigned int   linkPartnerFecAbility : 1;    /* 07.C215.E  RO       */
                     /* 1 = 10GBASE-KR PHY has FEC capability.
                        0 = 10GBASE-KR PHY does not have FEC capability.
                          */
                    /*! \brief 07.C215.F RO Link Partner FEC Requested
                        AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR.u2.bits_2.linkPartnerFecRequested

                        

                        1 = Enable 10GBASE-KR FEC ability.
                        0 = Disable 10GBASE-KR FEC ability.
                        
  */
      unsigned int   linkPartnerFecRequested : 1;    /* 07.C215.F  RO       */
                     /* 1 = Enable 10GBASE-KR FEC ability.
                        0 = Disable 10GBASE-KR FEC ability.
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_Kr0LinkPartnerAutonegotiationAdvertisementWord_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                KR0 Autonegotiation Extended Next Page Advertisement Word: 07.C216 */
/*                  KR0 Autonegotiation Extended Next Page Advertisement Word: 07.C216 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of KR0 Autonegotiation Extended Next Page Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C216.F:0 R/WPD Extended Next Page 0 [F:0]
                        AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_EUR.u0.bits_0.extendedNextPage_0

                        Provisionable Default = 0x0000

                        Extended next page bits [F:0]
                        
  */
      unsigned int   extendedNextPage_0 : 16;    /* 07.C216.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Extended next page bits [F:0]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of KR0 Autonegotiation Extended Next Page Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C217.F:0 R/WPD Extended Next Page 1 [1F:10]
                        AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_EUR.u1.bits_1.extendedNextPage_1

                        Provisionable Default = 0x0000

                        Extended next page bits [1F:10]
                        
  */
      unsigned int   extendedNextPage_1 : 16;    /* 07.C217.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Extended next page bits [1F:10]
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of KR0 Autonegotiation Extended Next Page Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C218.F:0 R/WPD Extended Next Page 2 [2F:20]
                        AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_EUR.u2.bits_2.extendedNextPage_2

                        Provisionable Default = 0x0000

                        Extended next page bits [2F:20]
                        
  */
      unsigned int   extendedNextPage_2 : 16;    /* 07.C218.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Extended next page bits [2F:20]
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_Kr0AutonegotiationExtendedNextPageAdvertisementWord_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                KR0 Link Partner Autonegotiation Extended Next Page Advertisement Word: 07.C219 */
/*                  KR0 Link Partner Autonegotiation Extended Next Page Advertisement Word: 07.C219 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of KR0 Link Partner Autonegotiation Extended Next Page Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C219.F:0 RO Link Partner Extended Next Page 0 [F:0]
                        AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_EUR.u0.bits_0.linkPartnerExtendedNextPage_0

                        

                        Extended next page bits [F:0]
                        
  */
      unsigned int   linkPartnerExtendedNextPage_0 : 16;    /* 07.C219.F:0  RO       */
                     /* Extended next page bits [F:0]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of KR0 Link Partner Autonegotiation Extended Next Page Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C21A.F:0 RO Link Partner Extended Next Page 1 [1F:10]
                        AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_EUR.u1.bits_1.linkPartnerExtendedNextPage_1

                        

                        Extended next page bits [1F:10]
                        
  */
      unsigned int   linkPartnerExtendedNextPage_1 : 16;    /* 07.C21A.F:0  RO       */
                     /* Extended next page bits [1F:10]
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of KR0 Link Partner Autonegotiation Extended Next Page Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C21B.F:0 RO Link Partner Extended Next Page 2 [2F:20]
                        AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_EUR.u2.bits_2.linkPartnerExtendedNextPage_2

                        

                        Extended next page bits [2F:20]
                        
  */
      unsigned int   linkPartnerExtendedNextPage_2 : 16;    /* 07.C21B.F:0  RO       */
                     /* Extended next page bits [2F:20]
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_Kr0LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                KR1 Autonegotiation Control: 07.C300 */
/*                  KR1 Autonegotiation Control: 07.C300 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of KR1 Autonegotiation Control */
  union
  {
    struct
    {
                    /*! \brief 07.C300.8:0 R/WPD Reserved 2 [8:0]
                        AQ_Kr1AutonegotiationControl_EUR.u0.bits_0.reserved_2

                        Provisionable Default = 0x000

                        Reserved for future use
                        
  */
      unsigned int   reserved_2 : 9;    /* 07.C300.8:0  R/WPD      Provisionable Default = 0x000 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C300.9 R/WSC Autonegotiation Restart
                        AQ_Kr1AutonegotiationControl_EUR.u0.bits_0.autonegotiationRestart

                        Default = 0x0

                        1 = Restart autonegotiation
                        0 = Normal operation
                        
  */
      unsigned int   autonegotiationRestart : 1;    /* 07.C300.9  R/WSC      Default = 0x0 */
                     /* 1 = Restart autonegotiation
                        0 = Normal operation
                          */
                    /*! \brief 07.C300.B:A R/WPD Reserved 1 [1:0]
                        AQ_Kr1AutonegotiationControl_EUR.u0.bits_0.reserved_1

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_1 : 2;    /* 07.C300.B:A  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C300.C R/WPD Autonegotiation Enable
                        AQ_Kr1AutonegotiationControl_EUR.u0.bits_0.autonegotiationEnable

                        Provisionable Default = 0x0

                        1 = Enable autonegotiation
                        0 = Disable autonegotiation
                        
  */
      unsigned int   autonegotiationEnable : 1;    /* 07.C300.C  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable autonegotiation
                        0 = Disable autonegotiation
                          */
                    /*! \brief 07.C300.E:D R/WPD Reserved 0 [1:0]
                        AQ_Kr1AutonegotiationControl_EUR.u0.bits_0.reserved_0

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_0 : 2;    /* 07.C300.E:D  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C300.F R/WSC Reset
                        AQ_Kr1AutonegotiationControl_EUR.u0.bits_0.reset

                        Default = 0x1

                        1 = Autonegotiation reset
                        0 = Normal operation
                        
  */
      unsigned int   reset : 1;    /* 07.C300.F  R/WSC      Default = 0x1 */
                     /* 1 = Autonegotiation reset
                        0 = Normal operation
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Kr1AutonegotiationControl_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                KR1 Autonegotiation Status: 07.C301 */
/*                  KR1 Autonegotiation Status: 07.C301 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of KR1 Autonegotiation Status */
  union
  {
    struct
    {
                    /*! \brief 07.C301.0 ROS Link Partner Autonegotiation Ability
                        AQ_Kr1AutonegotiationStatus_EUR.u0.bits_0.linkPartnerAutonegotiationAbility

                        Default = 0x0

                        1 = Link partner is able to perform autonegotiation 
                        0 = Link partner is not able to perform autonegotiation
                        
  */
      unsigned int   linkPartnerAutonegotiationAbility : 1;    /* 07.C301.0  ROS      Default = 0x0 */
                     /* 1 = Link partner is able to perform autonegotiation 
                        0 = Link partner is not able to perform autonegotiation
                          */
                    /*! \brief 07.C301.2:1 R/WPD Reserved 3 [1:0]
                        AQ_Kr1AutonegotiationStatus_EUR.u0.bits_0.reserved_3

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_3 : 2;    /* 07.C301.2:1  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C301.3 ROS Autonegotiation Ability
                        AQ_Kr1AutonegotiationStatus_EUR.u0.bits_0.autonegotiationAbility

                        Default = 0x1

                        1 = PHY is able to perform autonegotiation 
                        0 = PHY is not able to perform autonegotiation 
                        

                 <B>Notes:</B>
                        Always set as 1 as the local device has autonegotiation  ability.  */
      unsigned int   autonegotiationAbility : 1;    /* 07.C301.3  ROS      Default = 0x1 */
                     /* 1 = PHY is able to perform autonegotiation 
                        0 = PHY is not able to perform autonegotiation 
                          */
                    /*! \brief 07.C301.4 R/WPD Reserved 2
                        AQ_Kr1AutonegotiationStatus_EUR.u0.bits_0.reserved_2

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_2 : 1;    /* 07.C301.4  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C301.5 LH Autonegotiation Complete
                        AQ_Kr1AutonegotiationStatus_EUR.u0.bits_0.autonegotiationComplete

                        

                        1 = Autonegotiation complete
                        0 = Normal operation
                        
  */
      unsigned int   autonegotiationComplete : 1;    /* 07.C301.5  LH       */
                     /* 1 = Autonegotiation complete
                        0 = Normal operation
                          */
                    /*! \brief 07.C301.6 LH Page Received
                        AQ_Kr1AutonegotiationStatus_EUR.u0.bits_0.pageReceived

                        

                        1 = A new DME page has been received
                        0 = Normal operation
                        
  */
      unsigned int   pageReceived : 1;    /* 07.C301.6  LH       */
                     /* 1 = A new DME page has been received
                        0 = Normal operation
                          */
                    /*! \brief 07.C301.8:7 R/WPD Reserved 1 [1:0]
                        AQ_Kr1AutonegotiationStatus_EUR.u0.bits_0.reserved_1

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_1 : 2;    /* 07.C301.8:7  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C301.9 LH Parallel Detection Fault
                        AQ_Kr1AutonegotiationStatus_EUR.u0.bits_0.parallelDetectionFault

                        

                        1 = Fault detected
                        0 = No fault detected
                        
  */
      unsigned int   parallelDetectionFault : 1;    /* 07.C301.9  LH       */
                     /* 1 = Fault detected
                        0 = No fault detected
                          */
                    /*! \brief 07.C301.F:A R/WPD Reserved 0 [5:0]
                        AQ_Kr1AutonegotiationStatus_EUR.u0.bits_0.reserved_0

                        Provisionable Default = 0x00

                        Reserved for future use
                        
  */
      unsigned int   reserved_0 : 6;    /* 07.C301.F:A  R/WPD      Provisionable Default = 0x00 */
                     /* Reserved for future use
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Kr1AutonegotiationStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                KR1 Autonegotiation Advertisement Word: 07.C310 */
/*                  KR1 Autonegotiation Advertisement Word: 07.C310 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of KR1 Autonegotiation Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C310.4:0 R/WPD Selector Field [4:0]
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u0.bits_0.selectorField

                        Provisionable Default = 0x01

                        This defines the device compatibility:
                        0x00 = Reserved
                        0x01 = IEEE 802.3
                        0x02 = IEEE 802.9 ISLAN-16T
                        0x03 = IEEE 802.5
                        0x04 = IEEE 1394
                        0x05 -> 0x1F = Reserved
                        

                 <B>Notes:</B>
                        This field should always be set to 0x01 as the PHY is only capable of handling 802.3 Ethernet.  */
      unsigned int   selectorField : 5;    /* 07.C310.4:0  R/WPD      Provisionable Default = 0x01 */
                     /* This defines the device compatibility:
                        0x00 = Reserved
                        0x01 = IEEE 802.3
                        0x02 = IEEE 802.9 ISLAN-16T
                        0x03 = IEEE 802.5
                        0x04 = IEEE 1394
                        0x05 -> 0x1F = Reserved
                          */
                    /*! \brief 07.C310.9:5 R/WPD Echoed Nonce [4:0]
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u0.bits_0.echoedNonce

                        Provisionable Default = 0x00

                        Echoed nonce
                        
  */
      unsigned int   echoedNonce : 5;    /* 07.C310.9:5  R/WPD      Provisionable Default = 0x00 */
                     /* Echoed nonce
                          */
                    /*! \brief 07.C310.B:A R/WPD Pause Capability [1:0]
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u0.bits_0.pauseCapability

                        Provisionable Default = 0x0

                        Bit B: PAUSE operation for full duplex links
                        Bit A: Asymmetric PAUSE operation for full duplex links
                        
  */
      unsigned int   pauseCapability : 2;    /* 07.C310.B:A  R/WPD      Provisionable Default = 0x0 */
                     /* Bit B: PAUSE operation for full duplex links
                        Bit A: Asymmetric PAUSE operation for full duplex links
                          */
                    /*! \brief 07.C310.C R/WPD Reserved 0
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u0.bits_0.reserved_0

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_0 : 1;    /* 07.C310.C  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C310.D R/W Remote Fault
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u0.bits_0.remoteFault

                        Default = 0x0

                        1 = Remote fault
                        

                 <B>Notes:</B>
                        The remote fault bit provides a standard transport mechanism for the transmission of simple fault information. When the RF bit in the received base link code word is set to 1, the RF bit will be set to 1.  */
      unsigned int   remoteFault : 1;    /* 07.C310.D  R/W      Default = 0x0 */
                     /* 1 = Remote fault
                          */
                    /*! \brief 07.C310.E R/WPD Acknowledge
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u0.bits_0.acknowledge

                        Provisionable Default = 0x0

                        1 = Acknowledge
                        0 = No fault detected
                        

                 <B>Notes:</B>
                        The Acknowledge (Ack) is used by the Autonegotiation  function to indicate that a device has successfully received its Link Partner's Link Code Word.  */
      unsigned int   acknowledge : 1;    /* 07.C310.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Acknowledge
                        0 = No fault detected
                          */
                    /*! \brief 07.C310.F R/WPD Next Page
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u0.bits_0.nextPage

                        Provisionable Default = 0x0

                        1 = Next page ability
                        0 = Next page ability not supported or not engaged
                        
  */
      unsigned int   nextPage : 1;    /* 07.C310.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Next page ability
                        0 = Next page ability not supported or not engaged
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of KR1 Autonegotiation Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C311.4:0 R/WPD Transmitted Nonce [4:0]
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u1.bits_1.transmittedNonce

                        Provisionable Default = 0x00

                        Transmitted nonce
                        
  */
      unsigned int   transmittedNonce : 5;    /* 07.C311.4:0  R/WPD      Provisionable Default = 0x00 */
                     /* Transmitted nonce
                          */
                    /*! \brief 07.C311.5 R/WPD Technology Ability Bit A0
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u1.bits_1.technologyAbilityBitA0

                        Provisionable Default = 0x1

                        1 = 10GBASE-KX is supported
                        0 = 10GBASE-KX is not supported
                        
  */
      unsigned int   technologyAbilityBitA0 : 1;    /* 07.C311.5  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = 10GBASE-KX is supported
                        0 = 10GBASE-KX is not supported
                          */
                    /*! \brief 07.C311.6 R/WPD Technology Ability Bit A1
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u1.bits_1.technologyAbilityBitA1

                        Provisionable Default = 0x0

                        1 = 10GBASE-KX4 is supported
                        0 = 10GBASE-KX4 is not supported
                        
  */
      unsigned int   technologyAbilityBitA1 : 1;    /* 07.C311.6  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = 10GBASE-KX4 is supported
                        0 = 10GBASE-KX4 is not supported
                          */
                    /*! \brief 07.C311.7 R/WPD Technology Ability Bit A2
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u1.bits_1.technologyAbilityBitA2

                        Provisionable Default = 0x1

                        1 = 10GBASE-KR is supported
                        0 = 10GBASE-KR is not supported
                        
  */
      unsigned int   technologyAbilityBitA2 : 1;    /* 07.C311.7  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = 10GBASE-KR is supported
                        0 = 10GBASE-KR is not supported
                          */
                    /*! \brief 07.C311.F:8 R/WPD Technology Ability Bits A3 to A10 [7:0]
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u1.bits_1.technologyAbilityBitsA3ToA10

                        Provisionable Default = 0x00

                        Reserved for future technology
                        
  */
      unsigned int   technologyAbilityBitsA3ToA10 : 8;    /* 07.C311.F:8  R/WPD      Provisionable Default = 0x00 */
                     /* Reserved for future technology
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of KR1 Autonegotiation Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C312.D:0 R/WPD Technology Ability Bits A11 to A24 [D:0]
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u2.bits_2.technologyAbilityBitsA11ToA24

                        Provisionable Default = 0x0000

                        Reserved for future technology
                        
  */
      unsigned int   technologyAbilityBitsA11ToA24 : 14;    /* 07.C312.D:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Reserved for future technology
                          */
                    /*! \brief 07.C312.E R/WPD FEC Ability
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u2.bits_2.fecAbility

                        Provisionable Default = 0x0

                        1 = 10GBASE-KR PHY has FEC capability.
                        0 = 10GBASE-KR PHY does not have FEC capability.
                        
  */
      unsigned int   fecAbility : 1;    /* 07.C312.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = 10GBASE-KR PHY has FEC capability.
                        0 = 10GBASE-KR PHY does not have FEC capability.
                          */
                    /*! \brief 07.C312.F R/WPD FEC Requested
                        AQ_Kr1AutonegotiationAdvertisementWord_EUR.u2.bits_2.fecRequested

                        Provisionable Default = 0x0

                        1 = Enable 10GBASE-KR FEC ability.
                        0 = Disable 10GBASE-KR FEC ability.
                        
  */
      unsigned int   fecRequested : 1;    /* 07.C312.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable 10GBASE-KR FEC ability.
                        0 = Disable 10GBASE-KR FEC ability.
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_Kr1AutonegotiationAdvertisementWord_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                KR1 Link Partner Autonegotiation Advertisement Word: 07.C313 */
/*                  KR1 Link Partner Autonegotiation Advertisement Word: 07.C313 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of KR1 Link Partner Autonegotiation Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C313.4:0 RO Link Partner Selector Field [4:0]
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.linkPartnerSelectorField

                        

                        This defines the device compatibility:
                        0x00 = Reserved
                        0x01 = IEEE 802.3
                        0x02 = IEEE 802.9 ISLAN-16T
                        0x03 = IEEE 802.5
                        0x04 = IEEE 1394
                        0x05 -> 0x1F = Reserved
                        

                 <B>Notes:</B>
                        This field should always be set to 0x01 as the PHY is only capable of handling 802.3 Ethernet.  */
      unsigned int   linkPartnerSelectorField : 5;    /* 07.C313.4:0  RO       */
                     /* This defines the device compatibility:
                        0x00 = Reserved
                        0x01 = IEEE 802.3
                        0x02 = IEEE 802.9 ISLAN-16T
                        0x03 = IEEE 802.5
                        0x04 = IEEE 1394
                        0x05 -> 0x1F = Reserved
                          */
                    /*! \brief 07.C313.9:5 RO Link Partner Echoed Nonce [4:0]
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.linkPartnerEchoedNonce

                        

                        Echoed nonce
                        
  */
      unsigned int   linkPartnerEchoedNonce : 5;    /* 07.C313.9:5  RO       */
                     /* Echoed nonce
                          */
                    /*! \brief 07.C313.B:A RO Link Partner Pause Capability [1:0]
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.linkPartnerPauseCapability

                        

                        Bit B: PAUSE operation for full duplex links
                        Bit A: Asymmetric PAUSE operation for full duplex links
                        
  */
      unsigned int   linkPartnerPauseCapability : 2;    /* 07.C313.B:A  RO       */
                     /* Bit B: PAUSE operation for full duplex links
                        Bit A: Asymmetric PAUSE operation for full duplex links
                          */
                    /*! \brief 07.C313.C RO Reserved 0
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.reserved_0

                        

                        Reserved for future use
                        
  */
      unsigned int   reserved_0 : 1;    /* 07.C313.C  RO       */
                     /* Reserved for future use
                          */
                    /*! \brief 07.C313.D RO Link Partner Remote Fault
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.linkPartnerRemoteFault

                        

                        1 = Remote fault
                        

                 <B>Notes:</B>
                        The remote fault bit provides a standard transport mechanism for the transmission of simple fault information. When the RF bit in the received base link code word is set to 1, the RF bit will be set to 1.  */
      unsigned int   linkPartnerRemoteFault : 1;    /* 07.C313.D  RO       */
                     /* 1 = Remote fault
                          */
                    /*! \brief 07.C313.E RO Link Partner Acknowledge
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.linkPartnerAcknowledge

                        

                        1 = Acknowledge
                        0 = No fault detected
                        

                 <B>Notes:</B>
                        The Acknowledge (Ack) is used by the Autonegotiation  function to indicate that a device has successfully received its Link Partner's Link Code Word.  */
      unsigned int   linkPartnerAcknowledge : 1;    /* 07.C313.E  RO       */
                     /* 1 = Acknowledge
                        0 = No fault detected
                          */
                    /*! \brief 07.C313.F RO Link Partner Next Page
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u0.bits_0.linkPartnerNextPage

                        

                        1 = Next page ability
                        0 = Next page ability not supported or not engaged
                        
  */
      unsigned int   linkPartnerNextPage : 1;    /* 07.C313.F  RO       */
                     /* 1 = Next page ability
                        0 = Next page ability not supported or not engaged
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of KR1 Link Partner Autonegotiation Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C314.4:0 RO Link Partner Transmitted Nonce [4:0]
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u1.bits_1.linkPartnerTransmittedNonce

                        

                        Transmitted nonce
                        
  */
      unsigned int   linkPartnerTransmittedNonce : 5;    /* 07.C314.4:0  RO       */
                     /* Transmitted nonce
                          */
                    /*! \brief 07.C314.5 RO Link Partner Technology Ability Bit A0
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u1.bits_1.linkPartnerTechnologyAbilityBitA0

                        

                        1 = 10GBASE-KX is supported
                        0 = 10GBASE-KX is not supported
                        
  */
      unsigned int   linkPartnerTechnologyAbilityBitA0 : 1;    /* 07.C314.5  RO       */
                     /* 1 = 10GBASE-KX is supported
                        0 = 10GBASE-KX is not supported
                          */
                    /*! \brief 07.C314.6 RO Link Partner Technology Ability Bit A1
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u1.bits_1.linkPartnerTechnologyAbilityBitA1

                        

                        1 = 10GBASE-KX4 is supported
                        0 = 10GBASE-KX4 is not supported
                        
  */
      unsigned int   linkPartnerTechnologyAbilityBitA1 : 1;    /* 07.C314.6  RO       */
                     /* 1 = 10GBASE-KX4 is supported
                        0 = 10GBASE-KX4 is not supported
                          */
                    /*! \brief 07.C314.7 RO Link Partner Technology Ability Bit A2
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u1.bits_1.linkPartnerTechnologyAbilityBitA2

                        

                        1 = 10GBASE-KR is supported
                        0 = 10GBASE-KR is not supported
                        
  */
      unsigned int   linkPartnerTechnologyAbilityBitA2 : 1;    /* 07.C314.7  RO       */
                     /* 1 = 10GBASE-KR is supported
                        0 = 10GBASE-KR is not supported
                          */
                    /*! \brief 07.C314.F:8 RO Link Partner Technology Ability Bits A3 to A10 [7:0]
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u1.bits_1.linkPartnerTechnologyAbilityBitsA3ToA10

                        

                        Reserved for future technology
                        
  */
      unsigned int   linkPartnerTechnologyAbilityBitsA3ToA10 : 8;    /* 07.C314.F:8  RO       */
                     /* Reserved for future technology
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of KR1 Link Partner Autonegotiation Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C315.D:0 RO Link Partner Technology Ability Bits A11 to A24 [D:0]
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u2.bits_2.linkPartnerTechnologyAbilityBitsA11ToA24

                        

                        Reserved for future technology
                        
  */
      unsigned int   linkPartnerTechnologyAbilityBitsA11ToA24 : 14;    /* 07.C315.D:0  RO       */
                     /* Reserved for future technology
                          */
                    /*! \brief 07.C315.E RO Link Partner FEC Ability
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u2.bits_2.linkPartnerFecAbility

                        

                        1 = 10GBASE-KR PHY has FEC capability.
                        0 = 10GBASE-KR PHY does not have FEC capability.
                        
  */
      unsigned int   linkPartnerFecAbility : 1;    /* 07.C315.E  RO       */
                     /* 1 = 10GBASE-KR PHY has FEC capability.
                        0 = 10GBASE-KR PHY does not have FEC capability.
                          */
                    /*! \brief 07.C315.F RO Link Partner FEC Requested
                        AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR.u2.bits_2.linkPartnerFecRequested

                        

                        1 = Enable 10GBASE-KR FEC ability.
                        0 = Disable 10GBASE-KR FEC ability.
                        
  */
      unsigned int   linkPartnerFecRequested : 1;    /* 07.C315.F  RO       */
                     /* 1 = Enable 10GBASE-KR FEC ability.
                        0 = Disable 10GBASE-KR FEC ability.
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_Kr1LinkPartnerAutonegotiationAdvertisementWord_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                KR1 Autonegotiation Extended Next Page Advertisement Word: 07.C316 */
/*                  KR1 Autonegotiation Extended Next Page Advertisement Word: 07.C316 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of KR1 Autonegotiation Extended Next Page Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C316.F:0 R/WPD Extended Next Page 0 [F:0]
                        AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_EUR.u0.bits_0.extendedNextPage_0

                        Provisionable Default = 0x0000

                        Extended next page bits [F:0]
                        
  */
      unsigned int   extendedNextPage_0 : 16;    /* 07.C316.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Extended next page bits [F:0]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of KR1 Autonegotiation Extended Next Page Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C317.F:0 R/WPD Extended Next Page 1 [1F:10]
                        AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_EUR.u1.bits_1.extendedNextPage_1

                        Provisionable Default = 0x0000

                        Extended next page bits [1F:10]
                        
  */
      unsigned int   extendedNextPage_1 : 16;    /* 07.C317.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Extended next page bits [1F:10]
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of KR1 Autonegotiation Extended Next Page Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C318.F:0 R/WPD Extended Next Page 2 [2F:20]
                        AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_EUR.u2.bits_2.extendedNextPage_2

                        Provisionable Default = 0x0000

                        Extended next page bits [2F:20]
                        
  */
      unsigned int   extendedNextPage_2 : 16;    /* 07.C318.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Extended next page bits [2F:20]
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_Kr1AutonegotiationExtendedNextPageAdvertisementWord_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                KR1 Link Partner Autonegotiation Extended Next Page Advertisement Word: 07.C319 */
/*                  KR1 Link Partner Autonegotiation Extended Next Page Advertisement Word: 07.C319 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of KR1 Link Partner Autonegotiation Extended Next Page Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C319.F:0 RO Link Partner Extended Next Page 0 [F:0]
                        AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_EUR.u0.bits_0.linkPartnerExtendedNextPage_0

                        

                        Extended next page bits [F:0]
                        
  */
      unsigned int   linkPartnerExtendedNextPage_0 : 16;    /* 07.C319.F:0  RO       */
                     /* Extended next page bits [F:0]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of KR1 Link Partner Autonegotiation Extended Next Page Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C31A.F:0 RO Link Partner Extended Next Page 1 [1F:10]
                        AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_EUR.u1.bits_1.linkPartnerExtendedNextPage_1

                        

                        Extended next page bits [1F:10]
                        
  */
      unsigned int   linkPartnerExtendedNextPage_1 : 16;    /* 07.C31A.F:0  RO       */
                     /* Extended next page bits [1F:10]
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of KR1 Link Partner Autonegotiation Extended Next Page Advertisement Word */
  union
  {
    struct
    {
                    /*! \brief 07.C31B.F:0 RO Link Partner Extended Next Page 2 [2F:20]
                        AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_EUR.u2.bits_2.linkPartnerExtendedNextPage_2

                        

                        Extended next page bits [2F:20]
                        
  */
      unsigned int   linkPartnerExtendedNextPage_2 : 16;    /* 07.C31B.F:0  RO       */
                     /* Extended next page bits [2F:20]
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_Kr1LinkPartnerAutonegotiationExtendedNextPageAdvertisementWord_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Vendor Provisioning: 07.C400 */
/*                  Autonegotiation Vendor Provisioning: 07.C400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 07.C400.3:0 R/WPD Retry Attempts Before Downshift [3:0]
                        AQ_AutonegotiationVendorProvisioning_EUR.u0.bits_0.retryAttemptsBeforeDownshift

                        Provisionable Default = 0x4

                        Number of retry attempts before downshift

                 <B>Notes:</B>
                        If Automatic Downshifting is enabled, this is the number of retry attempts the PHY will make to connect at the maximum mutually acceptable rate, before removing this rate from the list and trying the next lower rate.  */
      unsigned int   retryAttemptsBeforeDownshift : 4;    /* 07.C400.3:0  R/WPD      Provisionable Default = 0x4 */
                     /* Number of retry attempts before downshift  */
                    /*! \brief 07.C400.4 R/WPD Automatic Downshift Enable
                        AQ_AutonegotiationVendorProvisioning_EUR.u0.bits_0.automaticDownshiftEnable

                        Provisionable Default = 0x1

                        1 = Enable automatic downshift
                        0 = Manual downshift
                        
  */
      unsigned int   automaticDownshiftEnable : 1;    /* 07.C400.4  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = Enable automatic downshift
                        0 = Manual downshift
                          */
                    /*! \brief 07.C400.5 R/WPD User Provided Autonegotiation Data
                        AQ_AutonegotiationVendorProvisioning_EUR.u0.bits_0.userProvidedAutonegotiationData

                        Provisionable Default = 0x0

                        1 = User provides the next page or extended next page data directly (7.16 -> 7.18), and the configuration info in 7.20 and 7.C400 is ignored.
                        0 = Construct the correct autonegotiation words based on the register settings of 7.10, 7.20, and 7.C400

                 <B>Notes:</B>
                        If this bit is set, the PHY will attempt to use the user provided autonegotiation words. If there is a mismatch (such as a legacy 1GBASE-T device attempting connect), the PHY will then attempt to construct a new set of autonegotiation words from the data provided in these words.
                        
                        Otherwise, the PHY will construct the correct autonegotiation words based on the provisioned values.  */
      unsigned int   userProvidedAutonegotiationData : 1;    /* 07.C400.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = User provides the next page or extended next page data directly (7.16 -> 7.18), and the configuration info in 7.20 and 7.C400 is ignored.
                        0 = Construct the correct autonegotiation words based on the register settings of 7.10, 7.20, and 7.C400  */
                    /*! \brief 07.C400.6 R/WPD Exchange PHY ID Information
                        AQ_AutonegotiationVendorProvisioning_EUR.u0.bits_0.exchangePhyIdInformation

                        Provisionable Default = 0x1

                        1 = Exchange PHY ID Information
  */
      unsigned int   exchangePhyIdInformation : 1;    /* 07.C400.6  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = Exchange PHY ID Information  */
                    /*! \brief 07.C400.9:7 R/WPD Reserved1 [2:0]
                        AQ_AutonegotiationVendorProvisioning_EUR.u0.bits_0.reserved1

                        Provisionable Default = 0x0

                        Reserved for future use
  */
      unsigned int   reserved1 : 3;    /* 07.C400.9:7  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use  */
                    /*! \brief 07.C400.A R/WPD 2.5G
                        AQ_AutonegotiationVendorProvisioning_EUR.u0.bits_0._2_5g

                        Provisionable Default = 0x0

                        1 = Advertise PHY as supporting 2.5G
                        0 = Do not advertise PHY as supporting 2.55G
  */
      unsigned int   _2_5g : 1;    /* 07.C400.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise PHY as supporting 2.5G
                        0 = Do not advertise PHY as supporting 2.55G  */
                    /*! \brief 07.C400.B R/WPD 5G
                        AQ_AutonegotiationVendorProvisioning_EUR.u0.bits_0._5g

                        Provisionable Default = 0x0

                        1 = Advertise PHY as supporting 5G
                        0 = Do not advertise PHY as supporting 5G
  */
      unsigned int   _5g : 1;    /* 07.C400.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise PHY as supporting 5G
                        0 = Do not advertise PHY as supporting 5G  */
                    /*! \brief 07.C400.C R/WPD AQRate Downshift Capability
                        AQ_AutonegotiationVendorProvisioning_EUR.u0.bits_0.aqrateDownshiftCapability

                        Provisionable Default = 0x0

                        1 = Advertise PHY as supporting AQRate
                        0 = Do not advertise PHY as supporting AQRate
  */
      unsigned int   aqrateDownshiftCapability : 1;    /* 07.C400.C  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise PHY as supporting AQRate
                        0 = Do not advertise PHY as supporting AQRate  */
                    /*! \brief 07.C400.D R/WPD Short-Reach
                        AQ_AutonegotiationVendorProvisioning_EUR.u0.bits_0.short_reach

                        Provisionable Default = 0x0

                        1 = Advertise PHY as operating in short-reach mode
                        0 = Do not advertise PHY as operating in short-reach mode
  */
      unsigned int   short_reach : 1;    /* 07.C400.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise PHY as operating in short-reach mode
                        0 = Do not advertise PHY as operating in short-reach mode  */
                    /*! \brief 07.C400.E R/WPD 1000BASE-T Half Duplex Ability
                        AQ_AutonegotiationVendorProvisioning_EUR.u0.bits_0._1000base_tHalfDuplexAbility

                        Provisionable Default = 0x0

                        1 = Advertise PHY as 1000BASE-T Half Duplex capable
                        0 = Do not advertise PHY as 1000BASE-T Half Duplex capable
  */
      unsigned int   _1000base_tHalfDuplexAbility : 1;    /* 07.C400.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise PHY as 1000BASE-T Half Duplex capable
                        0 = Do not advertise PHY as 1000BASE-T Half Duplex capable  */
                    /*! \brief 07.C400.F R/WPD 1000BASE-T Full Duplex Ability
                        AQ_AutonegotiationVendorProvisioning_EUR.u0.bits_0._1000base_tFullDuplexAbility

                        Provisionable Default = 0x0

                        1 = Advertise PHY as 1000BASE-T Full Duplex capable
                        0 = Do not advertise PHY as 1000BASE-T Full Duplex capable
  */
      unsigned int   _1000base_tFullDuplexAbility : 1;    /* 07.C400.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise PHY as 1000BASE-T Full Duplex capable
                        0 = Do not advertise PHY as 1000BASE-T Full Duplex capable  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationVendorProvisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Reserved Vendor Provisioning: 07.C410 */
/*                  Autonegotiation Reserved Vendor Provisioning: 07.C410 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 07.C410.1:0 R/WPD MDI / MDI-X Control [1:0]
                        AQ_AutonegotiationReservedVendorProvisioning_EUR.u0.bits_0.mdi_Mdi_xControl

                        Provisionable Default = 0x0

                        0x0 = Automatic MDI / MDI-X operation
                        0x1 = Manual MDI
                        0x2 = Manual MDI-X
                        0x3 = Reserved
                        

                 <B>Notes:</B>
                        These bits are used to force a manual MDI or MDI-X configuration  */
      unsigned int   mdi_Mdi_xControl : 2;    /* 07.C410.1:0  R/WPD      Provisionable Default = 0x0 */
                     /* 0x0 = Automatic MDI / MDI-X operation
                        0x1 = Manual MDI
                        0x2 = Manual MDI-X
                        0x3 = Reserved
                          */
                    /*! \brief 07.C410.5:2 R/WPD Extra Page Count [3:0]
                        AQ_AutonegotiationReservedVendorProvisioning_EUR.u0.bits_0.extraPageCount

                        Provisionable Default = 0x0

                        Number of extra pages to send at end of auto-negotiation sequence when link partner is legacy gigabit PHY.
                        

                 <B>Notes:</B>
                        Intervals between pages for GbE PHYs may be much longer. When this is the case, the link partner may still be in auto-negotiation when the PHY has started training. This may confuse the link partner MDI/MDI-X state machine. Sending extra pages seems to solve this problem.  */
      unsigned int   extraPageCount : 4;    /* 07.C410.5:2  R/WPD      Provisionable Default = 0x0 */
                     /* Number of extra pages to send at end of auto-negotiation sequence when link partner is legacy gigabit PHY.
                          */
                    /*! \brief 07.C410.6 R/WPD WoL Enable
                        AQ_AutonegotiationReservedVendorProvisioning_EUR.u0.bits_0.wolEnable

                        Provisionable Default = 0x0

                        1 = Enable Wake-On-LAN operation
                        0 = Normal Operation
                        

                 <B>Notes:</B>
                        Setting this bit enables Wake-On-LAN operation. In this state, power is minimized by turning all interfaces except the MDI receive path and the MDIO interface off.  */
      unsigned int   wolEnable : 1;    /* 07.C410.6  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable Wake-On-LAN operation
                        0 = Normal Operation
                          */
                    /*! \brief 07.C410.7 R/WPD WoL Mode
                        AQ_AutonegotiationReservedVendorProvisioning_EUR.u0.bits_0.wolMode

                        Provisionable Default = 0x0

                        0 = 100BASE-TX
                        1 = 1000BASE-T
                        

                 <B>Notes:</B>
                        This bit indicates whether the PHY is going to go into 100BASE-TX or 1000BASE-T Wake-On-LAN operation.  */
      unsigned int   wolMode : 1;    /* 07.C410.7  R/WPD      Provisionable Default = 0x0 */
                     /* 0 = 100BASE-TX
                        1 = 1000BASE-T
                          */
                    /*! \brief 07.C410.A:8 R/WPD Semi-Cross Link Attempt Period [2:0]
                        AQ_AutonegotiationReservedVendorProvisioning_EUR.u0.bits_0.semi_crossLinkAttemptPeriod

                        Provisionable Default = 0x0

                        Number of failed link attempts before trying semi cross
                        

                 <B>Notes:</B>
                        Set to zero (0) to disable semi-cross. Set to 0x7 to always use semi-cross.  */
      unsigned int   semi_crossLinkAttemptPeriod : 3;    /* 07.C410.A:8  R/WPD      Provisionable Default = 0x0 */
                     /* Number of failed link attempts before trying semi cross
                          */
                    /*! \brief 07.C410.B R/WPD 1G2P EEE
                        AQ_AutonegotiationReservedVendorProvisioning_EUR.u0.bits_0._1g2pEee

                        Provisionable Default = 0x0

                        1 = Advertise that the 1G2P has EEE capability
                        0 = Do not advertise that the 1G2P has EEE capability
                        
  */
      unsigned int   _1g2pEee : 1;    /* 07.C410.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Advertise that the 1G2P has EEE capability
                        0 = Do not advertise that the 1G2P has EEE capability
                          */
                    /*! \brief 07.C410.F:C R/WPD Reserved Provisioning 0 [3:0]
                        AQ_AutonegotiationReservedVendorProvisioning_EUR.u0.bits_0.reservedProvisioning_0

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reservedProvisioning_0 : 4;    /* 07.C410.F:C  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationReservedVendorProvisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Vendor Status: 07.C800 */
/*                  Autonegotiation Vendor Status: 07.C800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Vendor Status */
  union
  {
    struct
    {
                    /*! \brief 07.C800.0 RO Connect Type
                        AQ_AutonegotiationVendorStatus_EUR.u0.bits_0.connectType

                        

                        The duplex method the PHY connected or attempting to connect at:
                        
                        1 = Full Duplex
                        0 = Half-Duplex

                 <B>Notes:</B>
                        This field is used in conjunction with Connection State in  See Autonegotiation Reserved Vendor Status 1: Address 7.C810 to indicated the duplex method the PHY is connected or attempting to connect at.  */
      unsigned int   connectType : 1;    /* 07.C800.0  RO       */
                     /* The duplex method the PHY connected or attempting to connect at:
                        
                        1 = Full Duplex
                        0 = Half-Duplex  */
                    /*! \brief 07.C800.3:1 RO Connect Rate [2:0]
                        AQ_AutonegotiationVendorStatus_EUR.u0.bits_0.connectRate

                        

                        The rate the PHY connected or attempting to connect at:
                        0x5 = 5G
                        0x4 = 2.5G
                        0x3 = 10GBASE-T
                        0x2 = 1000BASE-T
                        0x1 = 100BASE-TX
                        0x0 = 10BASE-T

                 <B>Notes:</B>
                        This field is used in conjunction with Connection State in  See Autonegotiation Reserved Vendor Status 1: Address 7.C810 to indicated the rate the PHY is connected or attempting to connect at.  */
      unsigned int   connectRate : 3;    /* 07.C800.3:1  RO       */
                     /* The rate the PHY connected or attempting to connect at:
                        0x5 = 5G
                        0x4 = 2.5G
                        0x3 = 10GBASE-T
                        0x2 = 1000BASE-T
                        0x1 = 100BASE-TX
                        0x0 = 10BASE-T  */
      unsigned int   reserved0 : 12;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationVendorStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Reserved Vendor Status: 07.C810 */
/*                  Autonegotiation Reserved Vendor Status: 07.C810 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Reserved Vendor Status */
  union
  {
    struct
    {
                    /*! \brief 07.C810.0 RO Transmit PAUSE Resolution
                        AQ_AutonegotiationReservedVendorStatus_EUR.u0.bits_0.transmitPauseResolution

                        

                        1 = Transmit PAUSE Enabled
                        0 = Transmit PAUSE Disabled
                        

                 <B>Notes:</B>
                        
                        
                        
                        PAUSE resolution from 28B-3  */
      unsigned int   transmitPauseResolution : 1;    /* 07.C810.0  RO       */
                     /* 1 = Transmit PAUSE Enabled
                        0 = Transmit PAUSE Disabled
                          */
                    /*! \brief 07.C810.1 RO Receive PAUSE Resolution
                        AQ_AutonegotiationReservedVendorStatus_EUR.u0.bits_0.receivePauseResolution

                        

                        1 = Receive PAUSE Enabled
                        0 = Receive PAUSE Disabled
                        

                 <B>Notes:</B>
                        
                        
                        
                        PAUSE resolution from 28B-3  */
      unsigned int   receivePauseResolution : 1;    /* 07.C810.1  RO       */
                     /* 1 = Receive PAUSE Enabled
                        0 = Receive PAUSE Disabled
                          */
                    /*! \brief 07.C810.6:2 RO Reserved Status 1 [6:2]
                        AQ_AutonegotiationReservedVendorStatus_EUR.u0.bits_0.reservedStatus_1

                        

                        Reserved for future use
  */
      unsigned int   reservedStatus_1 : 5;    /* 07.C810.6:2  RO       */
                     /* Reserved for future use  */
                    /*! \brief 07.C810.7 RO Duplicate Link Partner Autonegotiation Ability
                        AQ_AutonegotiationReservedVendorStatus_EUR.u0.bits_0.duplicateLinkPartnerAutonegotiationAbility

                        

                        Link Partner is capable of Autonegotiation.
                        

                 <B>Notes:</B>
                        This is a duplicate of the bit at 07.0001.0.  */
      unsigned int   duplicateLinkPartnerAutonegotiationAbility : 1;    /* 07.C810.7  RO       */
                     /* Link Partner is capable of Autonegotiation.
                          */
                    /*! \brief 07.C810.8 RO MDI/MDI-X
                        AQ_AutonegotiationReservedVendorStatus_EUR.u0.bits_0.mdi_mdi_x

                        

                        0 = MDI
                        1 = MDI-X
                        

                 <B>Notes:</B>
                        When autonegotiation is completed, this register indicates whether the connection was made as an MDI or MDI-X connection.  */
      unsigned int   mdi_mdi_x : 1;    /* 07.C810.8  RO       */
                     /* 0 = MDI
                        1 = MDI-X
                          */
                    /*! \brief 07.C810.D:9 RO Connection State [4:0]
                        AQ_AutonegotiationReservedVendorStatus_EUR.u0.bits_0.connectionState

                        

                        The current state of the connection:
                        0x00 = Inactive (i.e. high-impedance)
                        0x01 = Cable diagnostics
                        0x02 = Autonegotiation
                        0x03 = Training (10G and 1G only)
                        0x04 = Connected
                        0x05 = Fail (Autonegotiation Break Link)
                        0x06 = Test Mode
                        0x07 = Loopback Mode
                        0x08 = Low Power Mode
                        0x09 = Connected Wake-On-LAN Mode
                        0x0A = System Calibrating
                        0x0B = Cable Disconnected
                        0x0C -> 0x1E = Reserved
                        0x1F = Invalid
                        

                 <B>Notes:</B>
                        This field is used in conjunction with Connect Rate and Connect Type in  See Autonegotiation Vendor Status 1: Address 7.C800 to indicated the current state the PHY is in.  */
      unsigned int   connectionState : 5;    /* 07.C810.D:9  RO       */
                     /* The current state of the connection:
                        0x00 = Inactive (i.e. high-impedance)
                        0x01 = Cable diagnostics
                        0x02 = Autonegotiation
                        0x03 = Training (10G and 1G only)
                        0x04 = Connected
                        0x05 = Fail (Autonegotiation Break Link)
                        0x06 = Test Mode
                        0x07 = Loopback Mode
                        0x08 = Low Power Mode
                        0x09 = Connected Wake-On-LAN Mode
                        0x0A = System Calibrating
                        0x0B = Cable Disconnected
                        0x0C -> 0x1E = Reserved
                        0x1F = Invalid
                          */
                    /*! \brief 07.C810.E RO Device Present
                        AQ_AutonegotiationReservedVendorStatus_EUR.u0.bits_0.devicePresent

                        

                        1 = Far-end Ethernet device present
                        0 = No far-end Ethernet device detected
                        

                 <B>Notes:</B>
                        If true, a far-end Ethernet device exists, as valid link pulses have been detected in the most recent autonegotiation session, or a valid Ethernet connection has been established. If false, no connection is established, and the most recent attempt at autonegotiation failed to detect any valid link pulses. Specifically, when MDI/MDI-X resolution has completed, this bit is true. This bit will be set false before entering autonegotiation.  */
      unsigned int   devicePresent : 1;    /* 07.C810.E  RO       */
                     /* 1 = Far-end Ethernet device present
                        0 = No far-end Ethernet device detected
                          */
                    /*! \brief 07.C810.F RO Energy On Line
                        AQ_AutonegotiationReservedVendorStatus_EUR.u0.bits_0.energyOnLine

                        

                        1 = Energy detected on line
                        0 = No energy detected on line
                        

                 <B>Notes:</B>
                        This bit is used to indicate that the PHY has detected energy on the line. Specifically, when MDI/MDI-X resolution has completed, this bit is true. This bit will be set false before entering autonegotiation.  */
      unsigned int   energyOnLine : 1;    /* 07.C810.F  RO       */
                     /* 1 = Energy detected on line
                        0 = No energy detected on line
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Reserved Vendor Status */
  union
  {
    struct
    {
                    /*! \brief 07.C811.F:0 RO Autonegotiation Attempts [F:0]
                        AQ_AutonegotiationReservedVendorStatus_EUR.u1.bits_1.autonegotiationAttempts

                        

                        The number of autonegotiation attempts since the last successful connection (or power-up)
                        

                 <B>Notes:</B>
                        This is a rolling counter (i.e. upon saturation it reverts to zero). It is cleared upon reset, or the completion of a successful connection.  */
      unsigned int   autonegotiationAttempts : 16;    /* 07.C811.F:0  RO       */
                     /* The number of autonegotiation attempts since the last successful connection (or power-up)
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of Autonegotiation Reserved Vendor Status */
  union
  {
    struct
    {
                    /*! \brief 07.C812.0 RO WoL Ready
                        AQ_AutonegotiationReservedVendorStatus_EUR.u2.bits_2.wolReady

                        

                        1 = Preparations for Wake-on-LAN mode are complete
                        0 = Wake-on-LAN mode has not been requested, or preparations for Wake-on-LAN mode are not yet complete
                        

                 <B>Notes:</B>
                        When the system enables Wake-on-LAN and restarts autonegotiation, the PHY FW will power down blocks that are not needed for Wake-on-LAN mode, in preparation for switching to auxiliary supplies. This status flag indicates that this work has been completed, and the system should confirm that this flag has been set before the switchover occurs. 
                        
                        Note that this field is independent of the link state.  */
      unsigned int   wolReady : 1;    /* 07.C812.0  RO       */
                     /* 1 = Preparations for Wake-on-LAN mode are complete
                        0 = Wake-on-LAN mode has not been requested, or preparations for Wake-on-LAN mode are not yet complete
                          */
                    /*! \brief 07.C812.1 RO Link Partner 1G2P EEE
                        AQ_AutonegotiationReservedVendorStatus_EUR.u2.bits_2.linkPartner1G_2pEee

                        

                        1 = Link partner is advertising that its 1G2P has EEE capability
                        0 = Link partner is advertising that its 1G2P does not have EEE capability
                        
  */
      unsigned int   linkPartner1G_2pEee : 1;    /* 07.C812.1  RO       */
                     /* 1 = Link partner is advertising that its 1G2P has EEE capability
                        0 = Link partner is advertising that its 1G2P does not have EEE capability
                          */
                    /*! \brief 07.C812.E:2 RO Reserved State 3 [C:0]
                        AQ_AutonegotiationReservedVendorStatus_EUR.u2.bits_2.reservedState_3

                        

                        Reserved for future use
                        
                        
  */
      unsigned int   reservedState_3 : 13;    /* 07.C812.E:2  RO       */
                     /* Reserved for future use
                        
                          */
                    /*! \brief 07.C812.F RO Link Pulse Detected Status
                        AQ_AutonegotiationReservedVendorStatus_EUR.u2.bits_2.linkPulseDetectedStatus

                        

                        1 = Link Pulse Detected
                        0 = Link Pulse not Detected
                        
  */
      unsigned int   linkPulseDetectedStatus : 1;    /* 07.C812.F  RO       */
                     /* 1 = Link Pulse Detected
                        0 = Link Pulse not Detected
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of Autonegotiation Reserved Vendor Status */
  union
  {
    struct
    {
                    /*! \brief 07.C813.F:0 RO Autonegotiation Restarts Handled [F:0]
                        AQ_AutonegotiationReservedVendorStatus_EUR.u3.bits_3.autonegotiationRestartsHandled

                        

                        The number of line-side autonegotiation restart commands received.
                        

                 <B>Notes:</B>
                        This is a rolling counter (i.e. upon saturation it reverts to zero). It is cleared upon reset.  */
      unsigned int   autonegotiationRestartsHandled : 16;    /* 07.C813.F:0  RO       */
                     /* The number of line-side autonegotiation restart commands received.
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of Autonegotiation Reserved Vendor Status */
  union
  {
    struct
    {
                    /*! \brief 07.C814.F:0 RO Autonegotiation Attempts Since Reset [F:0]
                        AQ_AutonegotiationReservedVendorStatus_EUR.u4.bits_4.autonegotiationAttemptsSinceReset

                        

                        The number of autonegotiation attempts since the last PHY reset (or power-up).
                        

                 <B>Notes:</B>
                        Increments when the line-side goes back to `break-link' state and then re-negotiates.
                        
                        This is a rolling counter (i.e. upon saturation it reverts to zero). It is cleared upon reset.  */
      unsigned int   autonegotiationAttemptsSinceReset : 16;    /* 07.C814.F:0  RO       */
                     /* The number of autonegotiation attempts since the last PHY reset (or power-up).
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
} AQ_AutonegotiationReservedVendorStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Transmit Vendor Alarms: 07.CC00 */
/*                  Autonegotiation Transmit Vendor Alarms: 07.CC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Transmit Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 07.CC00.0 LH Connection State Change
                        AQ_AutonegotiationTransmitVendorAlarms_EUR.u0.bits_0.connectionStateChange

                        

                        1 = The connection state has changed
                        

                 <B>Notes:</B>
                        This interrupt indicates a change in Connection State [D:B] in  See Autonegotiation Reserved Vendor Status 1: Address 7.C810 . Note that this indicates any state change, versus 7.CC01.0 which indicates a connect or disconnect event.  */
      unsigned int   connectionStateChange : 1;    /* 07.CC00.0  LH       */
                     /* 1 = The connection state has changed
                          */
                    /*! \brief 07.CC00.1 LH Automatic Downshift
                        AQ_AutonegotiationTransmitVendorAlarms_EUR.u0.bits_0.automaticDownshift

                        

                        1 = Automatic downshift has occurred
  */
      unsigned int   automaticDownshift : 1;    /* 07.CC00.1  LH       */
                     /* 1 = Automatic downshift has occurred  */
                    /*! \brief 07.CC00.2 LH Autonegotiation Completed for Supported Rate
                        AQ_AutonegotiationTransmitVendorAlarms_EUR.u0.bits_0.autonegotiationCompletedForSupportedRate

                        

                        1 = Autonegotiation has completed successfully for a rate that is supported by the PHY
  */
      unsigned int   autonegotiationCompletedForSupportedRate : 1;    /* 07.CC00.2  LH       */
                     /* 1 = Autonegotiation has completed successfully for a rate that is supported by the PHY  */
                    /*! \brief 07.CC00.3 LH Autonegotiation Completed For Non-supported Rate
                        AQ_AutonegotiationTransmitVendorAlarms_EUR.u0.bits_0.autonegotiationCompletedForNon_supportedRate

                        

                        1 = Autonegotiation has completed for a rate that is not supported by the PHY

                 <B>Notes:</B>
                        This means that the PHY has completed autonegotiation, and was unable to agree on a rate that both could operate at. Indication should be ignored in case of Master/Slave resolution fault  */
      unsigned int   autonegotiationCompletedForNon_supportedRate : 1;    /* 07.CC00.3  LH       */
                     /* 1 = Autonegotiation has completed for a rate that is not supported by the PHY  */
      unsigned int   reserved0 : 12;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Transmit Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 07.CC01.0 LH Link Connect / Disconnect
                        AQ_AutonegotiationTransmitVendorAlarms_EUR.u1.bits_1.linkConnect_Disconnect

                        

                        1 = MDI Link has either connected or disconnected
                        

                 <B>Notes:</B>
                        This indicates whether the link has achieved a connect state, or was in a connect state and disconnected.  */
      unsigned int   linkConnect_Disconnect : 1;    /* 07.CC01.0  LH       */
                     /* 1 = MDI Link has either connected or disconnected
                          */
                    /*! \brief 07.CC01.E:1 LH Reserved Vendor Alarms 2 [D:0]
                        AQ_AutonegotiationTransmitVendorAlarms_EUR.u1.bits_1.reservedVendorAlarms_2

                        

                        Reserved for future use
                        
  */
      unsigned int   reservedVendorAlarms_2 : 14;    /* 07.CC01.E:1  LH       */
                     /* Reserved for future use
                          */
                    /*! \brief 07.CC01.F LH Link Pulse Detect
                        AQ_AutonegotiationTransmitVendorAlarms_EUR.u1.bits_1.linkPulseDetect

                        

                        1 = Link Pulse Detected
                        
  */
      unsigned int   linkPulseDetect : 1;    /* 07.CC01.F  LH       */
                     /* 1 = Link Pulse Detected
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_AutonegotiationTransmitVendorAlarms_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Standard Interrupt Mask: 07.D000 */
/*                  Autonegotiation Standard Interrupt Mask: 07.D000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved4 : 2;
                    /*! \brief 07.D000.2 R/WPD Link Status Mask
                        AQ_AutonegotiationStandardInterruptMask_EUR.u0.bits_0.linkStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   linkStatusMask : 1;    /* 07.D000.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved3 : 1;
                    /*! \brief 07.D000.4 R/WPD Remote Fault Mask
                        AQ_AutonegotiationStandardInterruptMask_EUR.u0.bits_0.remoteFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   remoteFaultMask : 1;    /* 07.D000.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved2 : 1;
                    /*! \brief 07.D000.6 R/WPD Extended Next Page Received Mask
                        AQ_AutonegotiationStandardInterruptMask_EUR.u0.bits_0.extendedNextPageReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   extendedNextPageReceivedMask : 1;    /* 07.D000.6  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved1 : 2;
                    /*! \brief 07.D000.9 R/WPD Parallel Detection Fault Mask
                        AQ_AutonegotiationStandardInterruptMask_EUR.u0.bits_0.parallelDetectionFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   parallelDetectionFaultMask : 1;    /* 07.D000.9  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved0 : 6;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 07.D001.F R/WPD MASTER-SLAVE Configuration Fault Mask
                        AQ_AutonegotiationStandardInterruptMask_EUR.u1.bits_1.master_slaveConfigurationFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   master_slaveConfigurationFaultMask : 1;    /* 07.D001.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_AutonegotiationStandardInterruptMask_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Transmit Vendor Interrupt Mask: 07.D400 */
/*                  Autonegotiation Transmit Vendor Interrupt Mask: 07.D400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 07.D400.0 R/WPD Connection State Change Mask
                        AQ_AutonegotiationTransmitVendorInterruptMask_EUR.u0.bits_0.connectionStateChangeMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   connectionStateChangeMask : 1;    /* 07.D400.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 07.D400.1 R/WPD Automatic Downshift Mask
                        AQ_AutonegotiationTransmitVendorInterruptMask_EUR.u0.bits_0.automaticDownshiftMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   automaticDownshiftMask : 1;    /* 07.D400.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 07.D400.2 R/WPD Autonegotiation Completed for Supported Rate Mask
                        AQ_AutonegotiationTransmitVendorInterruptMask_EUR.u0.bits_0.autonegotiationCompletedForSupportedRateMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   autonegotiationCompletedForSupportedRateMask : 1;    /* 07.D400.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 07.D400.3 R/WPD Autonegotiation Completed For Non-supported Rate Mask
                        AQ_AutonegotiationTransmitVendorInterruptMask_EUR.u0.bits_0.autonegotiationCompletedForNon_supportedRateMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   autonegotiationCompletedForNon_supportedRateMask : 1;    /* 07.D400.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved0 : 12;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 07.D401.0 R/WPD Link Connect / Disconnect Mask
                        AQ_AutonegotiationTransmitVendorInterruptMask_EUR.u1.bits_1.linkConnect_DisconnectMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   linkConnect_DisconnectMask : 1;    /* 07.D401.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 07.D401.E:1 R/WPD Reserved Vendor Alarms 2 Mask [D:0]
                        AQ_AutonegotiationTransmitVendorInterruptMask_EUR.u1.bits_1.reservedVendorAlarms_2Mask

                        Provisionable Default = 0x0000

                        Reserved for future use
                        
  */
      unsigned int   reservedVendorAlarms_2Mask : 14;    /* 07.D401.E:1  R/WPD      Provisionable Default = 0x0000 */
                     /* Reserved for future use
                          */
                    /*! \brief 07.D401.F R/WPD Link Pulse Detect Mask
                        AQ_AutonegotiationTransmitVendorInterruptMask_EUR.u1.bits_1.linkPulseDetectMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   linkPulseDetectMask : 1;    /* 07.D401.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of Autonegotiation Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_AutonegotiationTransmitVendorInterruptMask_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Receive Reserved Vendor Provisioning: 07.E410 */
/*                  Autonegotiation Receive Reserved Vendor Provisioning: 07.E410 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Receive Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 07.E410.0 R/WPD Disable 100BASE-TX Parallel Detection
                        AQ_AutonegotiationReceiveReservedVendorProvisioning_EUR.u0.bits_0.disable_100base_txParallelDetection

                        Provisionable Default = 0x0

                        1 = Disable 100BASE-TX Parallel Detection
                        0 = Normal operation (100BASE-TX Parallel Detection enabled)
                        

                 <B>Notes:</B>
                        NOTE! If this bit is toggled during operation, autonegotiation must be restarted in order for this change to take effect.  */
      unsigned int   disable_100base_txParallelDetection : 1;    /* 07.E410.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable 100BASE-TX Parallel Detection
                        0 = Normal operation (100BASE-TX Parallel Detection enabled)
                          */
                    /*! \brief 07.E410.F:1 R/WPD Reserved Receive Provisioning 1 [E:0]
                        AQ_AutonegotiationReceiveReservedVendorProvisioning_EUR.u0.bits_0.reservedReceiveProvisioning_1

                        Provisionable Default = 0x0000

                        Reserved for future use
                        
  */
      unsigned int   reservedReceiveProvisioning_1 : 15;    /* 07.E410.F:1  R/WPD      Provisionable Default = 0x0000 */
                     /* Reserved for future use
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Receive Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 07.E411.3:0 R/WPD Max Rate Training Cnt [3:0]
                        AQ_AutonegotiationReceiveReservedVendorProvisioning_EUR.u1.bits_1.maxRateTrainingCnt

                        Provisionable Default = 0x0

                        Training attempt count at max advertised rate reported in 7.E411.7:4. This counter is set to zero for the first training attempt.
                        
  */
      unsigned int   maxRateTrainingCnt : 4;    /* 07.E411.3:0  R/WPD      Provisionable Default = 0x0 */
                     /* Training attempt count at max advertised rate reported in 7.E411.7:4. This counter is set to zero for the first training attempt.
                          */
                    /*! \brief 07.E411.7:4 R/WPD Max Advertised Rate [3:0]
                        AQ_AutonegotiationReceiveReservedVendorProvisioning_EUR.u1.bits_1.maxAdvertisedRate

                        Provisionable Default = 0x0

                        Maximum advertised rate sent to the link partner through Autonegotiation.
                        0x5 = 5G
                        0x4 = 2.5G
                        0x3 = 10GBASE-T
                        0x2 = 1000BASE-T
                        0x1 = 100BASE-TX
                        0x0 = 10BASE-T
                        

                 <B>Notes:</B>
                        When downshift is enabled (7.C400.4) Max advertised rate may be different from the provisioned max rate in the autonegotiation capability registers (7.0020, 7.0010, 7.C400).  */
      unsigned int   maxAdvertisedRate : 4;    /* 07.E411.7:4  R/WPD      Provisionable Default = 0x0 */
                     /* Maximum advertised rate sent to the link partner through Autonegotiation.
                        0x5 = 5G
                        0x4 = 2.5G
                        0x3 = 10GBASE-T
                        0x2 = 1000BASE-T
                        0x1 = 100BASE-TX
                        0x0 = 10BASE-T
                          */
                    /*! \brief 07.E411.8 R/WPD Downshift From 1G
                        AQ_AutonegotiationReceiveReservedVendorProvisioning_EUR.u1.bits_1.downshiftFrom1G

                        Provisionable Default = 0x0

                        Max advertised rate downshifted from 1G.
                        
  */
      unsigned int   downshiftFrom1G : 1;    /* 07.E411.8  R/WPD      Provisionable Default = 0x0 */
                     /* Max advertised rate downshifted from 1G.
                          */
                    /*! \brief 07.E411.9 R/WPD Downshift From 2.5G
                        AQ_AutonegotiationReceiveReservedVendorProvisioning_EUR.u1.bits_1.downshiftFrom_2_5g

                        Provisionable Default = 0x0

                        Max advertised rate downshifted from 2.5G.
                        
  */
      unsigned int   downshiftFrom_2_5g : 1;    /* 07.E411.9  R/WPD      Provisionable Default = 0x0 */
                     /* Max advertised rate downshifted from 2.5G.
                          */
                    /*! \brief 07.E411.A R/WPD Downshift From 5G
                        AQ_AutonegotiationReceiveReservedVendorProvisioning_EUR.u1.bits_1.downshiftFrom_5g

                        Provisionable Default = 0x0

                        Max advertised rate downshifted from 5G.
                        
  */
      unsigned int   downshiftFrom_5g : 1;    /* 07.E411.A  R/WPD      Provisionable Default = 0x0 */
                     /* Max advertised rate downshifted from 5G.
                          */
                    /*! \brief 07.E411.B R/WPD Downshift From 10G
                        AQ_AutonegotiationReceiveReservedVendorProvisioning_EUR.u1.bits_1.downshiftFrom10G

                        Provisionable Default = 0x0

                        Max advertised rate downshifted from 10G.
                        
  */
      unsigned int   downshiftFrom10G : 1;    /* 07.E411.B  R/WPD      Provisionable Default = 0x0 */
                     /* Max advertised rate downshifted from 10G.
                          */
                    /*! \brief 07.E411.F:C R/WPD Reserved Receive Provisioning 2 [3:0]
                        AQ_AutonegotiationReceiveReservedVendorProvisioning_EUR.u1.bits_1.reservedReceiveProvisioning_2

                        Provisionable Default = 0x0

                        Reserved for future use
                        
                        
  */
      unsigned int   reservedReceiveProvisioning_2 : 4;    /* 07.E411.F:C  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                        
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_AutonegotiationReceiveReservedVendorProvisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Receive Link Partner Status: 07.E820 */
/*                  Autonegotiation Receive Link Partner Status: 07.E820 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Receive Link Partner Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 07.E820.2 RO Aquantia Link Partner
                        AQ_AutonegotiationReceiveLinkPartnerStatus_EUR.u0.bits_0.aquantiaLinkPartner

                        

                        1 = Link Partner is an Aquantia PHY
                        0 = Link Partner is not an Aquantia PHY
                        
  */
      unsigned int   aquantiaLinkPartner : 1;    /* 07.E820.2  RO       */
                     /* 1 = Link Partner is an Aquantia PHY
                        0 = Link Partner is not an Aquantia PHY
                          */
                    /*! \brief 07.E820.9:3 RO Reserved2 [6:0]
                        AQ_AutonegotiationReceiveLinkPartnerStatus_EUR.u0.bits_0.reserved2

                        

                        Reserved for future use
  */
      unsigned int   reserved2 : 7;    /* 07.E820.9:3  RO       */
                     /* Reserved for future use  */
                    /*! \brief 07.E820.A R/WPD Link Partner 2.5G
                        AQ_AutonegotiationReceiveLinkPartnerStatus_EUR.u0.bits_0.linkPartner_2_5g

                        Provisionable Default = 0x0

                        1 = Link Partner PHY is 5G capable
                        0 = Link Partner PHY is not 5G capable
  */
      unsigned int   linkPartner_2_5g : 1;    /* 07.E820.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Link Partner PHY is 5G capable
                        0 = Link Partner PHY is not 5G capable  */
                    /*! \brief 07.E820.B R/WPD Link Partner 5G
                        AQ_AutonegotiationReceiveLinkPartnerStatus_EUR.u0.bits_0.linkPartner_5g

                        Provisionable Default = 0x0

                        1 = Link Partner PHY is 5G capable
                        0 = Link Partner PHY is not 5G capable
  */
      unsigned int   linkPartner_5g : 1;    /* 07.E820.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Link Partner PHY is 5G capable
                        0 = Link Partner PHY is not 5G capable  */
                    /*! \brief 07.E820.C R/WPD Link Partner AQRate Downshift Capability
                        AQ_AutonegotiationReceiveLinkPartnerStatus_EUR.u0.bits_0.linkPartnerAqrateDownshiftCapability

                        Provisionable Default = 0x0

                        1 = Link Partner PHY supports AQRate fast-retrain downshift mechanism
                        0 = Link Partner PHY does not support AQRate fast-retrain downshift mechanism
  */
      unsigned int   linkPartnerAqrateDownshiftCapability : 1;    /* 07.E820.C  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Link Partner PHY supports AQRate fast-retrain downshift mechanism
                        0 = Link Partner PHY does not support AQRate fast-retrain downshift mechanism  */
                    /*! \brief 07.E820.D RO Link Partner Short-Reach
                        AQ_AutonegotiationReceiveLinkPartnerStatus_EUR.u0.bits_0.linkPartnerShort_reach

                        

                        1 = Link Partner is operating in short-reach mode
                        0 = Link Partner is not operating in short-reach mode
  */
      unsigned int   linkPartnerShort_reach : 1;    /* 07.E820.D  RO       */
                     /* 1 = Link Partner is operating in short-reach mode
                        0 = Link Partner is not operating in short-reach mode  */
                    /*! \brief 07.E820.E RO Link Partner 1000BASE-T Half Duplex Ability
                        AQ_AutonegotiationReceiveLinkPartnerStatus_EUR.u0.bits_0.linkPartner1000BaseT_HalfDuplexAbility

                        

                        1 = Link Partner is 1000BASE-T Half-Duplex capable
                        0 = Link Partner is not 1000BASE-T Half-Duplex capable
  */
      unsigned int   linkPartner1000BaseT_HalfDuplexAbility : 1;    /* 07.E820.E  RO       */
                     /* 1 = Link Partner is 1000BASE-T Half-Duplex capable
                        0 = Link Partner is not 1000BASE-T Half-Duplex capable  */
                    /*! \brief 07.E820.F RO Link Partner 1000BASE-T Full Duplex Ability
                        AQ_AutonegotiationReceiveLinkPartnerStatus_EUR.u0.bits_0.linkPartner1000BaseT_FullDuplexAbility

                        

                        1 = Link Partner is 1000BASE-T Full Duplex capable
                        0 = Link Partner is not 1000BASE-T Full Duplex capable
  */
      unsigned int   linkPartner1000BaseT_FullDuplexAbility : 1;    /* 07.E820.F  RO       */
                     /* 1 = Link Partner is 1000BASE-T Full Duplex capable
                        0 = Link Partner is not 1000BASE-T Full Duplex capable  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Receive Link Partner Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of Autonegotiation Receive Link Partner Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of Autonegotiation Receive Link Partner Status */
  union
  {
    struct
    {
                    /*! \brief 07.E823.7:0 RO Link Partner Firmware Minor Revision Number [7:0]
                        AQ_AutonegotiationReceiveLinkPartnerStatus_EUR.u3.bits_3.linkPartnerFirmwareMinorRevisionNumber

                        

                        [7:0] = Link partner firmware minor revision number

                 <B>Notes:</B>
                        Only the lower six bits of major and minor firmware revision are exchanged in autonegotiation when the PHYID message is sent. Consequently the upper 2 bits of the major and minor revision should always be zero.  */
      unsigned int   linkPartnerFirmwareMinorRevisionNumber : 8;    /* 07.E823.7:0  RO       */
                     /* [7:0] = Link partner firmware minor revision number  */
                    /*! \brief 07.E823.F:8 RO Link Partner Firmware Major Revision Number [7:0]
                        AQ_AutonegotiationReceiveLinkPartnerStatus_EUR.u3.bits_3.linkPartnerFirmwareMajorRevisionNumber

                        

                        [F:8] = Link partner firmware major revision number

                 <B>Notes:</B>
                        Only the lower six bits of major and minor firmware revision are exchanged in autonegotiation when the PHYID message is sent. Consequently the upper 2 bits of the major and minor revision should always be zero.  */
      unsigned int   linkPartnerFirmwareMajorRevisionNumber : 8;    /* 07.E823.F:8  RO       */
                     /* [F:8] = Link partner firmware major revision number  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_AutonegotiationReceiveLinkPartnerStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Receive Reserved Vendor Status: 07.E830 */
/*                  Autonegotiation Receive Reserved Vendor Status: 07.E830 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Receive Reserved Vendor Status */
  union
  {
    struct
    {
                    /*! \brief 07.E830.8:0 RO Reserved Receive Status 1 [8:0]
                        AQ_AutonegotiationReceiveReservedVendorStatus_EUR.u0.bits_0.reservedReceiveStatus_1

                        

                        Reserved for future use
                        
  */
      unsigned int   reservedReceiveStatus_1 : 9;    /* 07.E830.8:0  RO       */
                     /* Reserved for future use
                          */
                    /*! \brief 07.E830.B:9 RORW Link Partner PHY Tag [2:0]
                        AQ_AutonegotiationReceiveReservedVendorStatus_EUR.u0.bits_0.linkPartnerPhyTag

                        

                        When the link partner is Aquantia and PHY ID pages have been exchanged this field contains the vendor specific link partner PHY tag value
                        

                 <B>Notes:</B>
                        This field is only valid if the link partner is Aquantia / Twinville and PHY ID link pages have been exchanged during Autonegotiation.  */
      unsigned int   linkPartnerPhyTag : 3;    /* 07.E830.B:9  RORW       */
                     /* When the link partner is Aquantia and PHY ID pages have been exchanged this field contains the vendor specific link partner PHY tag value
                          */
                    /*! \brief 07.E830.F:C RORW Link Attempts[3:0]
                        AQ_AutonegotiationReceiveReservedVendorStatus_EUR.u0.bits_0.linkAttempts

                        

                        Number of attempts needed to establish current link
                        

                 <B>Notes:</B>
                        Once a link has been established, save the total number of auto-negotiation and training sequence passes.  */
      unsigned int   linkAttempts : 4;    /* 07.E830.F:C  RORW       */
                     /* Number of attempts needed to establish current link
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Receive Reserved Vendor Status */
  union
  {
    struct
    {
                    /*! \brief 07.E831.B:0 RO Reserved Receive State 2 [B:0]
                        AQ_AutonegotiationReceiveReservedVendorStatus_EUR.u1.bits_1.reservedReceiveState_2

                        

                        Reserved for future use
                        

                 <B>Notes:</B>
                        This is the state bit associated with  See Reserved Spare Receive Vendor Alarms 2 [9:0] ( See Autonegotiation Receive Vendor Alarms 2: Address 7.EC01 )  */
      unsigned int   reservedReceiveState_2 : 12;    /* 07.E831.B:0  RO       */
                     /* Reserved for future use
                          */
                    /*! \brief 07.E831.C RO FLP Idle Error State
                        AQ_AutonegotiationReceiveReservedVendorStatus_EUR.u1.bits_1.flpIdleErrorState

                        

                        1 = No FLP Burst has been seen for 50 milliseconds forcing the receive state machine back to the Idle state
                        

                 <B>Notes:</B>
                        This is the state bit associated with  See FLP Idle Error ( See Autonegotiation Receive Vendor Alarms 2: Address 7.EC01 )  */
      unsigned int   flpIdleErrorState : 1;    /* 07.E831.C  RO       */
                     /* 1 = No FLP Burst has been seen for 50 milliseconds forcing the receive state machine back to the Idle state
                          */
                    /*! \brief 07.E831.D RO Autonegotiation Protocol Error State
                        AQ_AutonegotiationReceiveReservedVendorStatus_EUR.u1.bits_1.autonegotiationProtocolErrorState

                        

                        1 = Link partner has violated the Autonegotation protocol
                        

                 <B>Notes:</B>
                        This is the state bit associated with  See Autonegotiation Protocol Error ( See Autonegotiation Receive Vendor Alarms 2: Address 7.EC01 )  */
      unsigned int   autonegotiationProtocolErrorState : 1;    /* 07.E831.D  RO       */
                     /* 1 = Link partner has violated the Autonegotation protocol
                          */
      unsigned int   reserved0 : 2;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of Autonegotiation Receive Reserved Vendor Status */
  union
  {
    struct
    {
                    /*! \brief 07.E832.0 RO Link Partner AFR Enabled
                        AQ_AutonegotiationReceiveReservedVendorStatus_EUR.u2.bits_2.linkPartnerAfrEnabled

                        

                        1 = The link partner has Aquantia Fast Reframe capability enabled
                        
  */
      unsigned int   linkPartnerAfrEnabled : 1;    /* 07.E832.0  RO       */
                     /* 1 = The link partner has Aquantia Fast Reframe capability enabled
                          */
                    /*! \brief 07.E832.1 RO MultiGig Mode Selected
                        AQ_AutonegotiationReceiveReservedVendorStatus_EUR.u2.bits_2.multigigModeSelected

                        

                        1 = Indicates that MultiGig 2.5G or 5G mode was selected during autonegotiation process
                        0 = Indicates that MultiGig 2.5G or 5G mode was NOT selected.
                        

                 <B>Notes:</B>
                        Provides indication of whether MultiGig mode 5G or 2.5G was selected during MDI autonegotiation process.
                          */
      unsigned int   multigigModeSelected : 1;    /* 07.E832.1  RO       */
                     /* 1 = Indicates that MultiGig 2.5G or 5G mode was selected during autonegotiation process
                        0 = Indicates that MultiGig 2.5G or 5G mode was NOT selected.
                          */
                    /*! \brief 07.E832.F:2 RO Reserved Receive State 3 [D:0]
                        AQ_AutonegotiationReceiveReservedVendorStatus_EUR.u2.bits_2.reservedReceiveState_3

                        

                        Reserved for future use
                        
  */
      unsigned int   reservedReceiveState_3 : 14;    /* 07.E832.F:2  RO       */
                     /* Reserved for future use
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_AutonegotiationReceiveReservedVendorStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Receive Vendor Alarms: 07.EC00 */
/*                  Autonegotiation Receive Vendor Alarms: 07.EC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Receive Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 07.EC01.B:0 LH Reserved Receive Vendor Alarms 2 [B:0]
                        AQ_AutonegotiationReceiveVendorAlarms_EUR.u1.bits_1.reservedReceiveVendorAlarms_2

                        

                        Reserved for future use
                        
  */
      unsigned int   reservedReceiveVendorAlarms_2 : 12;    /* 07.EC01.B:0  LH       */
                     /* Reserved for future use
                          */
                    /*! \brief 07.EC01.C LH FLP Idle Error
                        AQ_AutonegotiationReceiveVendorAlarms_EUR.u1.bits_1.flpIdleError

                        

                        1 = No FLP Burst has been seen for 50 milliseconds forcing the receive state machine back to the Idle state
                        

                 <B>Notes:</B>
                        Once FLP bursts are detected on any receive channel, they must keep coming. If no burst has been detected for a period of 50 milliseconds, the Autonegotiation process resets itself and goes back to the "break link" state.
                          */
      unsigned int   flpIdleError : 1;    /* 07.EC01.C  LH       */
                     /* 1 = No FLP Burst has been seen for 50 milliseconds forcing the receive state machine back to the Idle state
                          */
                    /*! \brief 07.EC01.D LH Autonegotiation Protocol Error
                        AQ_AutonegotiationReceiveVendorAlarms_EUR.u1.bits_1.autonegotiationProtocolError

                        

                        1 = Link partner has violated the Autonegotation protocol
                        

                 <B>Notes:</B>
                        If the Arbiter state machine detects a protocol violation, the Autonegotiation process resets itself and goes back to the "break link" state.
                          */
      unsigned int   autonegotiationProtocolError : 1;    /* 07.EC01.D  LH       */
                     /* 1 = Link partner has violated the Autonegotation protocol
                          */
      unsigned int   reserved0 : 2;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of Autonegotiation Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved1 : 2;
                    /*! \brief 07.EC02.2 LL 10BASE-T Device Detect
                        AQ_AutonegotiationReceiveVendorAlarms_EUR.u2.bits_2._10base_tDeviceDetect

                        

                        0 = 10BASE-T device detected
                        

                 <B>Notes:</B>
                        This bit indicates that the detected far-end device is 10BASE-T when it is 0. This bit is 1 when link pulses are no longer received  */
      unsigned int   _10base_tDeviceDetect : 1;    /* 07.EC02.2  LL       */
                     /* 0 = 10BASE-T device detected
                          */
      unsigned int   reserved0 : 13;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of Autonegotiation Receive Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 07.EC03.0 LH 100BASE-TX Parallel Detect
                        AQ_AutonegotiationReceiveVendorAlarms_EUR.u3.bits_3._100base_txParallelDetect

                        

                        1 = 100BASE-TX parallel event detection occurred
                        
  */
      unsigned int   _100base_txParallelDetect : 1;    /* 07.EC03.0  LH       */
                     /* 1 = 100BASE-TX parallel event detection occurred
                          */
                    /*! \brief 07.EC03.F:1 LH Reserved Receive Vendor Alarms 4 [E:0]
                        AQ_AutonegotiationReceiveVendorAlarms_EUR.u3.bits_3.reservedReceiveVendorAlarms_4

                        

                        Reserved
                        
  */
      unsigned int   reservedReceiveVendorAlarms_4 : 15;    /* 07.EC03.F:1  LH       */
                     /* Reserved
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_AutonegotiationReceiveVendorAlarms_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Receive Vendor Interrupt Mask: 07.F400 */
/*                  Autonegotiation Receive Vendor Interrupt Mask: 07.F400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 07.F400.F:0 R/WPD Reserved Receive Vendor Alarms 1 Mask [F:0]
                        AQ_AutonegotiationReceiveVendorInterruptMask_EUR.u0.bits_0.reservedReceiveVendorAlarms_1Mask

                        Provisionable Default = 0x0000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedReceiveVendorAlarms_1Mask : 16;    /* 07.F400.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of Autonegotiation Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 07.F401.B:0 R/WPD Reserved Receive Vendor Alarms 2  Mask [B:0]
                        AQ_AutonegotiationReceiveVendorInterruptMask_EUR.u1.bits_1.reservedReceiveVendorAlarms_2Mask

                        Provisionable Default = 0x000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   reservedReceiveVendorAlarms_2Mask : 12;    /* 07.F401.B:0  R/WPD      Provisionable Default = 0x000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 07.F401.C R/WPD FLP Idle Error Mask
                        AQ_AutonegotiationReceiveVendorInterruptMask_EUR.u1.bits_1.flpIdleErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   flpIdleErrorMask : 1;    /* 07.F401.C  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 07.F401.D R/WPD Autonegotiation Protocol Error Mask
                        AQ_AutonegotiationReceiveVendorInterruptMask_EUR.u1.bits_1.autonegotiationProtocolErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   autonegotiationProtocolErrorMask : 1;    /* 07.F401.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved0 : 2;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of Autonegotiation Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved1 : 2;
                    /*! \brief 07.F402.2 R/WPD 10BASE-T Device Detect Mask
                        AQ_AutonegotiationReceiveVendorInterruptMask_EUR.u2.bits_2._10base_tDeviceDetectMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   _10base_tDeviceDetectMask : 1;    /* 07.F402.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved0 : 13;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of Autonegotiation Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 07.F403.0 R/WPD 100BASE-TX Parallel Detect Mask
                        AQ_AutonegotiationReceiveVendorInterruptMask_EUR.u3.bits_3._100base_txParallelDetectMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   _100base_txParallelDetectMask : 1;    /* 07.F403.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 07.F403.F:1 R/WPD Reserved Receive Vendor Alarms 4 Mask [E:0]
                        AQ_AutonegotiationReceiveVendorInterruptMask_EUR.u3.bits_3.reservedReceiveVendorAlarms_4Mask

                        Provisionable Default = 0x0000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   reservedReceiveVendorAlarms_4Mask : 15;    /* 07.F403.F:1  R/WPD      Provisionable Default = 0x0000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_AutonegotiationReceiveVendorInterruptMask_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                Autonegotiation Vendor Global Interrupt Flags: 07.FC00 */
/*                  Autonegotiation Vendor Global Interrupt Flags: 07.FC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of Autonegotiation Vendor Global Interrupt Flags */
  union
  {
    struct
    {
                    /*! \brief 07.FC00.0 RO Vendor Specific Rx Alarms 4 Interrupt
                        AQ_AutonegotiationVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificRxAlarms_4Interrupt

                        

                        1 = Interrupt
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See Autonegotiation Receive Vendor Alarms 4: Address 7.EC03 ) and the corresponding mask register ( See Autonegotiation Receive Vendor LASI Interrupt Mask 4: Address 7.F403 ).  */
      unsigned int   vendorSpecificRxAlarms_4Interrupt : 1;    /* 07.FC00.0  RO       */
                     /* 1 = Interrupt
                          */
                    /*! \brief 07.FC00.1 RO Vendor Specific Rx Alarms 3 Interrupt
                        AQ_AutonegotiationVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificRxAlarms_3Interrupt

                        

                        1 = Interrupt
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See Autonegotiation Receive Vendor Alarms 3: Address 7.EC02 ) and the corresponding mask register ( See Autonegotiation Receive Vendor LASI Interrupt Mask 3: Address 7.F402 ).  */
      unsigned int   vendorSpecificRxAlarms_3Interrupt : 1;    /* 07.FC00.1  RO       */
                     /* 1 = Interrupt
                          */
                    /*! \brief 07.FC00.2 RO Vendor Specific Rx Alarms 2 Interrupt
                        AQ_AutonegotiationVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificRxAlarms_2Interrupt

                        

                        1 = Interrupt
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See Autonegotiation Receive Vendor Alarms 2: Address 7.EC01 ) and the corresponding mask register ( See Autonegotiation Receive Vendor LASI Interrupt Mask 2: Address 7.F401 ).  */
      unsigned int   vendorSpecificRxAlarms_2Interrupt : 1;    /* 07.FC00.2  RO       */
                     /* 1 = Interrupt
                          */
                    /*! \brief 07.FC00.3 RO Vendor Specific Rx Alarms 1 Interrupt
                        AQ_AutonegotiationVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificRxAlarms_1Interrupt

                        

                        1 = Interrupt
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See Autonegotiation Receive Vendor Alarms 1- Address 7.EC00 ) and the corresponding mask register ( See Autonegotiation Receive Vendor Interrupt Mask 1- Address 7.F400 ).  */
      unsigned int   vendorSpecificRxAlarms_1Interrupt : 1;    /* 07.FC00.3  RO       */
                     /* 1 = Interrupt
                          */
      unsigned int   reserved1 : 5;
                    /*! \brief 07.FC00.9 RO Vendor Specific Alarms 2 Interrupt
                        AQ_AutonegotiationVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificAlarms_2Interrupt

                        

                        1 = Interrupt
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See Autonegotiation Vendor Alarms 3: Address 1E.CC02 ) and the corresponding mask register ( See Autonegotiation Vendor LASI Interrupt Mask 2: Address 7.D401 ).  */
      unsigned int   vendorSpecificAlarms_2Interrupt : 1;    /* 07.FC00.9  RO       */
                     /* 1 = Interrupt
                          */
                    /*! \brief 07.FC00.A RO Vendor Specific Alarms 1 Interrupt
                        AQ_AutonegotiationVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificAlarms_1Interrupt

                        

                        1 = Interrupt
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See Autonegotiation Vendor Alarms 1: Address 7.CC00 ) and the corresponding mask register ( See PCS Vendor Transmit PCS Interrupt Mask 1 - Address 3.A800 ).  */
      unsigned int   vendorSpecificAlarms_1Interrupt : 1;    /* 07.FC00.A  RO       */
                     /* 1 = Interrupt
                          */
      unsigned int   reserved0 : 3;
                    /*! \brief 07.FC00.E RO Standard Alarms 2 Interrupt
                        AQ_AutonegotiationVendorGlobalInterruptFlags_EUR.u0.bits_0.standardAlarms_2Interrupt

                        

                        1 = Interrupt
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See Autonegotiation 10GBASE-T Status Register - Address 7.21 ) and the corresponding mask register ( See PHY XS Standard Transmit XAUI Rx Interrupt Mask 8 - Address 4.A008 ).  */
      unsigned int   standardAlarms_2Interrupt : 1;    /* 07.FC00.E  RO       */
                     /* 1 = Interrupt
                          */
                    /*! \brief 07.FC00.F RO Standard Alarms 1 Interrupt
                        AQ_AutonegotiationVendorGlobalInterruptFlags_EUR.u0.bits_0.standardAlarms_1Interrupt

                        

                        1 = Interrupt
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PHY XS Standard Status 1 - Address 4.1 ) and the corresponding mask register ( See Autonegotiation Standard LASI Interrupt Mask 1: Address 7.D000 ).  */
      unsigned int   standardAlarms_1Interrupt : 1;    /* 07.FC00.F  RO       */
                     /* 1 = Interrupt
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_AutonegotiationVendorGlobalInterruptFlags_EUR;

#endif
/*@}*/
/*@}*/
